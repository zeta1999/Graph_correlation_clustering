#include <vector>
#include <thread>
#include <climits>

#include "../../../../include/solvers/non_strict_two_correlation_clustering/clust_algoritms/NAlgorithmForNS2CC.hpp"

IClustPtr ns2cc::NAlgorithmForNS2CC::getBestNeighborhoodClustering(const IGraph &graph) const {
  std::vector<IClustPtr> local_best_clustering_vector;
  for (unsigned i = 0; i < num_threads_; i++) {
    auto instance = clustering_factory_->CreateClustering(graph.Size());
    local_best_clustering_vector.push_back(instance);
  }
  std::vector<std::thread> thread_vector(num_threads_);
  for (unsigned i = 0; i < num_threads_; i++) {
    thread_vector[i] = std::thread(
        &NAlgorithmForNS2CC::BestNeighborhoodClusteringThreadWorker,
        this,
        std::ref(graph),
        i,
        std::ref(local_best_clustering_vector[i])
    );
  }
  for (auto &it: thread_vector) {
    it.join();
  }
  IClustPtr best_neighborhood_clustering = local_best_clustering_vector[0];
  unsigned best_distance = best_neighborhood_clustering->GetDistanceToGraph(graph);
  for (auto &it: local_best_clustering_vector) {
    auto tmp_distance = it->GetDistanceToGraph(graph);
    if (tmp_distance < best_distance) {
      best_distance = tmp_distance;
      best_neighborhood_clustering = it;
    }
  }
  return best_neighborhood_clustering;
}

void ns2cc::NAlgorithmForNS2CC::BestNeighborhoodClusteringThreadWorker(const IGraph &graph,
                                                                       const unsigned threadId,
                                                                       IClustPtr &local_best_clustering) const {
  unsigned best_distance = UINT_MAX;
  for (unsigned i = threadId; i < graph.Size(); i += num_threads_) {
    auto tmp_neighborhood_clustering = neighbor_splitter_.SplitGraphByVertex(graph, i);
    unsigned tmp_distance = tmp_neighborhood_clustering->GetDistanceToGraph(graph);
    if (tmp_distance < best_distance) {
      best_distance = tmp_distance;
      local_best_clustering = std::move(tmp_neighborhood_clustering);
    }
  }
}

ns2cc::NAlgorithmForNS2CC::NAlgorithmForNS2CC(const unsigned num_threads,
                                              const IClustFactoryPtr &clustering_factory)
    : num_threads_(num_threads),
      clustering_factory_(clustering_factory),
      neighbor_splitter_(NSplitterForNS2CC(clustering_factory)) {
}
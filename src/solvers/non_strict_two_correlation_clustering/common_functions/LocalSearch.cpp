#include <climits>
#include <iostream>

#include "../../../../include/solvers/non_strict_two_correlation_clustering/common_functions/LocalSearch.hpp"

IClustPtr non_strict_2cc::LocalSearch::ComputeLocalOptimum(const IGraph &graph,
                                                           const IClustPtr &cur_clustering) {
  auto result = cur_clustering->GetCopy();
  while (true) {
    int local_improvement = INT_MIN;
    unsigned candidate = UINT_MAX;
    for (unsigned i = 0; i < graph.Size(); i++) {
      auto tmp_local_improvement = ComputeLocalImprovement(graph, result, i);
      if (tmp_local_improvement > local_improvement) {
        local_improvement = tmp_local_improvement;
        candidate = i;
      }
    }
    if (local_improvement <= 0) {
      break;
    }
    if (result->GetLabel(candidate) == FIRST_CLUSTER) {
      result->SetupLabelForVertex(candidate, SECOND_CLUSTER);
    } else {
      result->SetupLabelForVertex(candidate, FIRST_CLUSTER);
    }
  }
  return result;
}

int non_strict_2cc::LocalSearch::ComputeLocalImprovement(const IGraph &graph,
                                                         const IClustPtr &cur_clustering,
                                                         const unsigned vertex) {
  int local_improvement = 0;
  for (unsigned i = 0; i < graph.Size(); i++) {
    if (i == vertex) {
      continue;
    }
    bool is_same_clustered = cur_clustering->IsSameClustered(i, vertex);
    bool is_joined = graph.IsJoined(i, vertex);
    if (is_same_clustered) {
      local_improvement += is_joined ? -1 : 1;
    } else {
      local_improvement += is_joined ? 1 : -1;
    }
  }
  return local_improvement;
}

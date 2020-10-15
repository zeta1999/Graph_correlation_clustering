#pragma once

#include <vector>
#include "../../../graphs/IGraph.hpp"
#include "../../../clustering/IClustering.hpp"
namespace non_strict_3cc {

class LocalSearch {
 private:
  /**
   * Compute local improvement of tossing vertex from one cluster to another.
   *
   * @param graph source graph.
   * @param cur_clustering current clustering.
   * @param vertex vertex to toss.
   * @return local improvement of tossing vertex from one cluster to another.
   */
  static int ComputeLocalImprovement(const IGraph &graph,
                                     const IClustPtr &cur_clustering,
                                     unsigned vertex,
                                     ClusterLabels first_label,
                                     ClusterLabels second_label);

  static std::vector<int> ComputeLocalImprovement(const IGraph &graph,
                                                  const IClustPtr &cur_clustering,
                                                  unsigned vertex);

  static bool IsSkipLabelForVertex(ClusterLabels label, unsigned idx);

  static unsigned GetIdxByLabel(ClusterLabels labels);

  static ClusterLabels GetLabelByIdx(unsigned idx);

 public:
  /**
   * Compute local optimal solution for the source graph.
   *
   * @param graph source graph.
   * @param cur_clustering init clustering.
   * @return local optimal clustering.
   */
  static IClustPtr ComputeLocalOptimum(const IGraph &graph,
                                       const IClustPtr &cur_clustering,
                                       ClusterLabels first_label,
                                       ClusterLabels second_label);

  static IClustPtr ComputeLocalOptimum(const IGraph &graph,
                                       const IClustPtr &cur_clustering);
};

}

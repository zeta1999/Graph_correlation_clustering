#pragma once

#include <memory>

#include "../../../clustering/factories/IClusteringFactory.hpp"

namespace ns2cc {

  /**
   * Local search for NS2CC.
   * @see Coleman, Saunderson and Wirth. A Local-Search 2-Approximation for 2-Correlation-Clustering.
   */
  class LSAlgorithmForNS2CC {

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
                                       const unsigned vertex);

   public:
    /**
     * Compute local optimal solution for the source graph.
     *
     * @param graph source graph.
     * @param cur_clustering init clustering.
     * @return local optimal clustering.
     */
    static IClustPtr ComputeLocalOptimum(const IGraph &graph,
                                         const IClustPtr &cur_clustering);
};
}



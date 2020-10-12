#pragma once

#include "BinaryClusteringVector.hpp"

/**
 * Special binary clustering vector for branch and bounds algorithm.
 *
 * It computes specific only for BB algorithm values which allowed algorithm to work faster.
 */
class BBBinaryClusteringVector : public BinaryClusteringVector {
 private:
  /**
   * Value of objective function on the partially build feasible solution.
   */
  unsigned obj_func_value_on_partially_built_clustering_{0};
  /**
   * Num of edges in non-constructed part of the graph.
   */
  int num_of_edges_of_non_constructed_graph_{0};
  /**
   * For each vertex contains current value of objective function, which this vertex
   * will contribute if it lies down in first cluster.
   */
  std::vector<int> obj_func_value_increase_relatively_to_first_cluster_;
  /**
   * For each vertex contains current value of objective function, which this vertex
   * will contribute if it lies down in second cluster.
  */
  std::vector<int> obj_func_value_increase_relatively_to_second_cluster_;
  /**
   * For each vertex contains number of neighbours if non-clustered part of graph.
   */
  std::vector<int> number_of_neighbours_in_non_clustered_graph_;
  /**
   * Graph pointer.
   */
  IGraphPtr graph_;

 protected:
  BBBinaryClusteringVector() = delete;
  BBBinaryClusteringVector(const BBBinaryClusteringVector &&) = delete;
  BBBinaryClusteringVector &operator=(const BBBinaryClusteringVector &&) = delete;

 public:
  BBBinaryClusteringVector(const BBBinaryClusteringVector &) = default;
  BBBinaryClusteringVector &operator=(const BBBinaryClusteringVector &) = default;
  BBBinaryClusteringVector(const unsigned size,
                           const IGraphPtr &graph);
  void SetupLabelForVertex(const unsigned vertex,
                           const ClusterLabels label) override;
  /**
   * Choose next vertex for branch.
   *
   * @return next vertex for branch.
   */
  unsigned Choose() const;
  /**
   * Compute bound of current clustering.
   *
   * @param record value of current record.
   * @return bound of current clustering.
   */
  int Bound(const unsigned record) const;
  /**
   * Get copy of this clustering vector.
   *
   * @return copy of this clustering vector.
   */
  BBBinaryClusteringVector Copy() const;
};

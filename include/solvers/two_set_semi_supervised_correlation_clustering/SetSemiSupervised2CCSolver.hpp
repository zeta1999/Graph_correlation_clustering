#pragma once

#include <vector>
#include <string>
#include <chrono>
#include <iostream>
#include <sstream>

#include "../../graphs/IGraph.hpp"
#include "../../clustering/factories/IClusteringFactory.hpp"

namespace set_semi_supervised_2cc {

struct ClusteringInfo {
  std::string name;
  std::shared_ptr<IClustering> clustering;
  unsigned objective_function_value;
  std::chrono::seconds computation_time;

  ClusteringInfo(std::string name,
                 std::shared_ptr<IClustering> clustering,
                 unsigned int objective_function_value,
                 std::chrono::seconds computation_time)
      : name(std::move(name)),
        clustering(std::move(clustering)),
        objective_function_value(objective_function_value),
        computation_time(computation_time) {}

  std::string ToJson() const {
    std::stringstream ss;
    ss << "\"" << name << "\": {\n";
    ss << clustering->ToJson() << "," << std::endl;
    ss << "\"objective function value\": " << objective_function_value << "," << std::endl;
    ss << "\"computation time seconds\": " << computation_time.count() << "}";
    return ss.str();
  }
};

class SetSemiSupervised2CCSolver {
 private:
  const std::vector<std::string> allowed_algorithms{
      "NeighborhoodWithManyLocalSearches",
      "NeighborhoodWithOneLocalSearch",
      "Neighborhood",
      "BranchAndBounds"};
  unsigned num_threads_;
  IClustFactoryPtr factory_;

 private:
  static std::string FormatComputationToJson(const IGraph &graph,
                                             const std::vector<ClusteringInfo> &computation_results,
                                             unsigned size,
                                             double density,
                                             const std::vector<unsigned> &first_cluster_vertices,
                                             const std::vector<unsigned> &second_cluster_vertices);

 public:
  SetSemiSupervised2CCSolver(unsigned num_threads,
                             IClustFactoryPtr factory);

  [[nodiscard]] std::string solve(const IGraphPtr &graph,
                                  double density,
                                  std::vector<std::string> used_algorithms,
                                  const std::vector<unsigned> &first_cluster_vertices,
                                  const std::vector<unsigned> &second_cluster_vertices) const;
};

}

#pragma once

#include <random>
#include "../AdjacencyMatrixGraph.hpp"
#include "IGraphFactory.hpp"
class ErdosRenyiRandomGraphFactory : IGraphFactory {
 private:
  std::random_device rd_;
  std::default_random_engine gen_{rd_()};
  std::uniform_real_distribution<> dis_{0.0, 1.0};
  double density_;

 public:
  ErdosRenyiRandomGraphFactory(const double density);
  std::shared_ptr<IGraph> CreateGraph(const unsigned size) override;
};




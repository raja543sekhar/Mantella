#pragma once

// Mantella
#include <mantella_bits/propertiesAnalysis/passivePropertiesAnalysis/functionModelAnalysis/linearModelAnalysis.hpp>
#include <mantella_bits/distanceFunction/euclideanDistance.hpp>

namespace mant {
  class LinearOrdinaryLeastSquares : public LinearModelAnalysis<double, EuclideanDistance> {
    public:
      using LinearModelAnalysis<double, EuclideanDistance>::LinearModelAnalysis;

    protected:
      void analyseImplementation(
          const std::shared_ptr<OptimisationProblem<double>> optimisationProblem) noexcept override;
      void analyseImplementation(
          const std::unordered_map<arma::Col<double>, double, Hash<arma::Col<double>>, IsKeyEqual<arma::Col<double>>>& parameterToObjectiveValueMappings) noexcept override;
      void analyseImplementation(
          const std::pair<arma::Col<double>, double>& parameterToObjectiveValueMapping) noexcept override;
  };
}

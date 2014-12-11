#pragma once

// HOP
#include <hop_bits/propertiesAnalysis/passivePropertiesAnalysis/functionModelAnalysis/quadraticModelAnalysis.hpp>

namespace hop {
  class QuadraticOrdinaryLeastSquares : public QuadraticModelAnalysis {
    public:
      using QuadraticModelAnalysis::QuadraticModelAnalysis;

    protected:
      void analyseImplementation(
          const std::shared_ptr<OptimisationProblem> optimisationProblem) noexcept override;
      void analyseImplementation(
          const std::pair<arma::Col<double>, double>& parameterToObjectiveValueMapping) noexcept override;
  };
}
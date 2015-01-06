#include <hop_bits/optimisationProblem/blackBoxOptimisationBenchmark2013/stepEllipsoidalFunction.hpp>

// C++ Standard Library
#include <algorithm>

// Cereal
#include <cereal/archives/json.hpp>
#include <cereal/types/polymorphic.hpp>

namespace hop {
  namespace bbob2013 {
    double StepEllipsoidalFunction::getObjectiveValueImplementation(
        const arma::Col<double>& parameter) const noexcept {
      const arma::Col<double>& zHat = delta_ % (rotationR_ * (parameter - translation_));

      arma::Col<double> zTilde(zHat);
      for (std::size_t n = 0; n < zTilde.n_elem; ++n) {
        const double& value = zHat.at(n);

        if (std::abs(value) > 0.5) {
          zTilde.at(n) = std::round(value);
        } else {
          zTilde.at(n) = std::round(value * 10.0) / 10.0;
        }
      }

      return 0.1 * std::max(std::abs(zHat.at(0)) / 10000.0, arma::dot(scaling_, arma::square(rotationQ_ * zTilde))) + getPenality(parameter);
    }

    std::string StepEllipsoidalFunction::to_string() const noexcept {
      return "StepEllipsoidalFunction";
    }
  }
}

CEREAL_REGISTER_TYPE(hop::bbob2013::StepEllipsoidalFunction)
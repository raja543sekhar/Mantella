#include <mantella_bits/optimisationProblem/blackBoxOptimisationBenchmark2009/rastriginFunction.hpp>

// Cereal
#include <cereal/archives/json.hpp>
#include <cereal/types/polymorphic.hpp>

namespace mant {
  namespace bbob2009 {
    double RastriginFunction::getObjectiveValueImplementation(
        const arma::Col<double>& parameter) const noexcept {
      const arma::Col<double>& z = delta_ % getAsymmetricTransformation(0.2, getOscillationTransformation(parameter - translation_));

      return 10.0 * (static_cast<double>(numberOfDimensions_) - arma::accu(arma::cos(2.0 * arma::datum::pi * z))) + std::pow(arma::norm(z), 2.0);
    }

    std::string RastriginFunction::to_string() const noexcept {
      return "RastriginFunction";
    }
  }
}

CEREAL_REGISTER_TYPE(mant::bbob2009::RastriginFunction)
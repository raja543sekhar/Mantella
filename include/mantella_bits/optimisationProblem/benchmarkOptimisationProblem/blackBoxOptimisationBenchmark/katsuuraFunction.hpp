#pragma once

// Armadillo
#include <armadillo>

// Mantella
#include "mantella_bits/optimisationProblem/benchmarkOptimisationProblem/blackBoxOptimisationBenchmark.hpp"

namespace mant {
  namespace bbob {
    class KatsuuraFunction : public BlackBoxOptimisationBenchmark {
     public:
      explicit KatsuuraFunction(
          const arma::uword numberOfDimensions);

     protected:
      const arma::Col<double> parameterConditioning_;
      // Cannot be *const*, as it is shared/set over MPI, to synchronise all problems.
      arma::Mat<double> rotationQ_;
    };
  }
}

#pragma once

// C++ Standard Library
#include <cmath>

// Mantella
#include <mantella_bits/optimisationProblem/blackBoxOptimisationBenchmark2015.hpp>

namespace mant {
  namespace bbob2015 {
    class SharpRidgeFunction : public BlackBoxOptimisationBenchmark2015 {
      public:
        using BlackBoxOptimisationBenchmark2015::BlackBoxOptimisationBenchmark2015;

        SharpRidgeFunction(const SharpRidgeFunction&) = delete;
        SharpRidgeFunction& operator=(const SharpRidgeFunction&) = delete;

        std::string to_string() const noexcept override;

      protected:
        const arma::Col<double> delta_ = getScaling(std::sqrt(10.0));

        double getObjectiveValueImplementation(
            const arma::Col<double>& parameter) const noexcept override;

        friend class cereal::access;

        template <typename Archive>
        void serialize(
            Archive& archive) noexcept {
          archive(cereal::make_nvp("BlackBoxOptimisationBenchmark2015", cereal::base_class<BlackBoxOptimisationBenchmark2015>(this)));
          archive(cereal::make_nvp("numberOfDimensions", numberOfDimensions_));;
          archive(cereal::make_nvp("translation", translation_));
          archive(cereal::make_nvp("rotationR", rotationR_));
          archive(cereal::make_nvp("rotationQ", rotationQ_));
        }

        template <typename Archive>
        static void load_and_construct(
            Archive& archive,
            cereal::construct<SharpRidgeFunction>& construct) noexcept {
          unsigned int numberOfDimensions;
          archive(cereal::make_nvp("numberOfDimensions", numberOfDimensions));
          construct(numberOfDimensions);

          archive(cereal::make_nvp("BlackBoxOptimisationBenchmark2015", cereal::base_class<BlackBoxOptimisationBenchmark2015>(construct.ptr())));
          archive(cereal::make_nvp("translation", construct->translation_));
          archive(cereal::make_nvp("rotationR", construct->rotationR_));
          archive(cereal::make_nvp("rotationQ", construct->rotationQ_));
        }
    };
  }
}

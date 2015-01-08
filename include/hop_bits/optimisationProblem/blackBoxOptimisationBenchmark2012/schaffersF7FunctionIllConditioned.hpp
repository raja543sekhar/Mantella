#pragma once

// C++ Standard Library
#include <cmath>

// HOP
#include <hop_bits/optimisationProblem/blackBoxOptimisationBenchmark2012.hpp>

namespace hop {
  namespace bbob2012 {
    class SchaffersF7FunctionIllConditioned : public BlackBoxOptimisationBenchmark2012 {
      public:
        using BlackBoxOptimisationBenchmark2012::BlackBoxOptimisationBenchmark2012;

        SchaffersF7FunctionIllConditioned(const SchaffersF7FunctionIllConditioned&) = delete;
        SchaffersF7FunctionIllConditioned& operator=(const SchaffersF7FunctionIllConditioned&) = delete;

        std::string to_string() const noexcept override;

      protected:
        const arma::Col<double> delta_ = getScaling(std::sqrt(1000.0));

        double getObjectiveValueImplementation(
            const arma::Col<double>& parameter) const noexcept override;

        friend class cereal::access;

        template <typename Archive>
        void serialize(
            Archive& archive) noexcept {
          archive(cereal::make_nvp("BlackBoxOptimisationBenchmark2012", cereal::base_class<BlackBoxOptimisationBenchmark2012>(this)));
          archive(cereal::make_nvp("numberOfDimensions", numberOfDimensions_));
          archive(cereal::make_nvp("translation", translation_));
          archive(cereal::make_nvp("rotationR", rotationR_));
          archive(cereal::make_nvp("rotationQ", rotationQ_));
        }

        template <typename Archive>
        static void load_and_construct(
            Archive& archive,
            cereal::construct<SchaffersF7FunctionIllConditioned>& construct) noexcept {
          unsigned int numberOfDimensions;
          archive(cereal::make_nvp("numberOfDimensions", numberOfDimensions));
          construct(numberOfDimensions);

          archive(cereal::make_nvp("BlackBoxOptimisationBenchmark2012", cereal::base_class<BlackBoxOptimisationBenchmark2012>(construct.ptr())));
          archive(cereal::make_nvp("translation", construct->translation_));
          archive(cereal::make_nvp("rotationR", construct->rotationR_));
          archive(cereal::make_nvp("rotationQ", construct->rotationQ_));
        }
    };
  }
}

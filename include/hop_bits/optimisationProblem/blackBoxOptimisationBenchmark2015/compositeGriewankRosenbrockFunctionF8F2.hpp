#pragma once

// C++ Standard Library
#include <algorithm>
#include <cmath>

// HOP
#include <hop_bits/optimisationProblem/blackBoxOptimisationBenchmark2015.hpp>

namespace hop {
  namespace bbob2015 {
    class CompositeGriewankRosenbrockFunctionF8F2 : public BlackBoxOptimisationBenchmark2015 {
      public:
        using BlackBoxOptimisationBenchmark2015::BlackBoxOptimisationBenchmark2015;

        CompositeGriewankRosenbrockFunctionF8F2(const CompositeGriewankRosenbrockFunctionF8F2&) = delete;
        CompositeGriewankRosenbrockFunctionF8F2& operator=(const CompositeGriewankRosenbrockFunctionF8F2&) = delete;

        std::string to_string() const noexcept override;

      protected:
        const double max_ = std::max(1.0, std::sqrt(static_cast<double>(numberOfDimensions_)) / 8.0);

        double getObjectiveValueImplementation(
            const arma::Col<double>& parameter) const noexcept override;

        friend class cereal::access;

        template <typename Archive>
        void serialize(
            Archive& archive) noexcept {
          archive(cereal::make_nvp("BlackBoxOptimisationBenchmark2015", cereal::base_class<BlackBoxOptimisationBenchmark2015>(this)));
          archive(cereal::make_nvp("numberOfDimensions", numberOfDimensions_));
          archive(cereal::make_nvp("rotationR", rotationR_));
        }

        template <typename Archive>
        static void load_and_construct(
            Archive& archive,
            cereal::construct<CompositeGriewankRosenbrockFunctionF8F2>& construct) noexcept {
          unsigned int numberOfDimensions;
          archive(cereal::make_nvp("numberOfDimensions", numberOfDimensions));
          construct(numberOfDimensions);

          archive(cereal::make_nvp("BlackBoxOptimisationBenchmark2015", cereal::base_class<BlackBoxOptimisationBenchmark2015>(construct.ptr())));
          archive(cereal::make_nvp("rotationR", construct->rotationR_));
        }
    };
  }
}

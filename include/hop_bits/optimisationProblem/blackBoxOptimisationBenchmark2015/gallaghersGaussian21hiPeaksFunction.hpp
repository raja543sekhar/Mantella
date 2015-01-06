#pragma once

// HOP
#include <hop_bits/optimisationProblem/blackBoxOptimisationBenchmark2015.hpp>

namespace hop {
  namespace bbob2015 {
    class GallaghersGaussian21hiPeaksFunction : public BlackBoxOptimisationBenchmark2015 {
      public:
        explicit GallaghersGaussian21hiPeaksFunction(
            const unsigned int& numberOfDimensions) noexcept;

        GallaghersGaussian21hiPeaksFunction(const GallaghersGaussian21hiPeaksFunction&) = delete;
        GallaghersGaussian21hiPeaksFunction& operator=(const GallaghersGaussian21hiPeaksFunction&) = delete;

        std::string to_string() const noexcept override;

      protected:
        arma::Col<double> weight_;

        double getObjectiveValueImplementation(
            const arma::Col<double>& parameter) const noexcept override;

        friend class cereal::access;

        template <typename Archive>
        void serialize(
            Archive& archive) noexcept {
          archive(cereal::make_nvp("BlackBoxOptimisationBenchmark2015", cereal::base_class<BlackBoxOptimisationBenchmark2015>(this)));
          archive(cereal::make_nvp("numberOfDimensions", numberOfDimensions_));
          archive(cereal::make_nvp("rotationR", rotationR_));
          archive(cereal::make_nvp("deltaC21", deltaC21_));
          archive(cereal::make_nvp("localOptimaY21", localOptimaY21_));
          archive(cereal::make_nvp("weight", weight_));
        }

        template <typename Archive>
        static void load_and_construct(
            Archive& archive,
            cereal::construct<GallaghersGaussian21hiPeaksFunction>& construct) noexcept {
          unsigned int numberOfDimensions;
          archive(cereal::make_nvp("numberOfDimensions", numberOfDimensions));
          construct(numberOfDimensions);

          archive(cereal::make_nvp("BlackBoxOptimisationBenchmark2015", cereal::base_class<BlackBoxOptimisationBenchmark2015>(construct.ptr())));
          archive(cereal::make_nvp("rotationR", construct->rotationR_));
          archive(cereal::make_nvp("deltaC21", construct->deltaC21_));
          archive(cereal::make_nvp("localOptimaY21", construct->localOptimaY21_));
          archive(cereal::make_nvp("weight", construct->weight_));
        }
    };
  }
}

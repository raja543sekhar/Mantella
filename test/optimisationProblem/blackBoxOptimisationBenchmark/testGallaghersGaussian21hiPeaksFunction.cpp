// Catch
#include <catch.hpp>

// C++ Standard Library
#include <cstdlib>
#include <string>

// Armadillo
#include <armadillo>

// Mantella
#include <mantella>

extern std::string testDirectory;

TEST_CASE("bbob::GallaghersGaussian21hiPeaksFunction", "") {
  for (const auto& numberOfDimensions : {2, 40}) {
    mant::bbob::GallaghersGaussian21hiPeaksFunction gallaghersGaussian21hiPeaksFunction(numberOfDimensions);

    arma::Mat<double> parameters;
    parameters.load(testDirectory + "/data/optimisationProblem/blackBoxOptimisationBenchmark/parameters,dim" + std::to_string(numberOfDimensions) +".mat");

    arma::Mat<double> rotationR;
    rotationR.load(testDirectory + "/data/optimisationProblem/blackBoxOptimisationBenchmark/rotationR,dim" + std::to_string(numberOfDimensions) +".mat");

    arma::Col<double> deltaC21;
    deltaC21.load(testDirectory + "/data/optimisationProblem/blackBoxOptimisationBenchmark/deltaC21,dim" + std::to_string(numberOfDimensions) +".mat");

    arma::Mat<double> localOptimaY21;
    localOptimaY21.load(testDirectory + "/data/optimisationProblem/blackBoxOptimisationBenchmark/localOptimaY21,dim" + std::to_string(numberOfDimensions) +".mat");

    arma::Col<double> expected;
    expected.load(testDirectory + "/data/optimisationProblem/blackBoxOptimisationBenchmark/expectedGallaghersGaussian21hiPeaksFunction,dim" + std::to_string(numberOfDimensions) +".mat");

    gallaghersGaussian21hiPeaksFunction.setObjectiveValueTranslation(0);
    gallaghersGaussian21hiPeaksFunction.setParameterRotationR(rotationR);
    gallaghersGaussian21hiPeaksFunction.setLocalParameterTranslation(localOptimaY21);
    gallaghersGaussian21hiPeaksFunction.setLocalParameterConditioning(deltaC21);

    for (std::size_t n = 0; n < parameters.n_cols; ++n) {
      CHECK(gallaghersGaussian21hiPeaksFunction.getObjectiveValue(parameters.col(n)) == Approx(expected.at(n)));
    }
  }

  SECTION("Returns the specified class name.") {
    CHECK(mant::bbob::GallaghersGaussian21hiPeaksFunction(5).toString() == "gallaghers-gaussian-21hi-peaks-function");
  }
}

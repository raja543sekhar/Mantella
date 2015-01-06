// Catch
#include <catch.hpp>

// C++ Standard Library
#include <cstdlib>
#include <string>

// Armadillo
#include <armadillo>

// Boost
#include <boost/filesystem.hpp>

// HOP
#include <hop>

extern boost::filesystem::path testDirectory;

TEST_CASE("RosenbrockFunctionRotated", "") {
  for (const auto& numberOfDimensions : {2, 40}) {
    hop::bbob2013::RosenbrockFunctionRotated rosenbrockFunctionRotated(numberOfDimensions);

    arma::Mat<double> parameters;
    parameters.load(testDirectory.string() + "/data/optimisationProblem/blackBoxOptimisationBenchmark2013/parameters,dim" + std::to_string(numberOfDimensions) +".mat");

    arma::Mat<double> rotationR;
    rotationR.load(testDirectory.string() + "/data/optimisationProblem/blackBoxOptimisationBenchmark2013/rotationR,dim" + std::to_string(numberOfDimensions) +".mat");

    arma::Col<double> expected;
    expected.load(testDirectory.string() + "/data/optimisationProblem/blackBoxOptimisationBenchmark2013/expectedRosenbrockFunctionRotated,dim" + std::to_string(numberOfDimensions) +".mat");

    rosenbrockFunctionRotated.setObjectiveValueTranslation(0);
    rosenbrockFunctionRotated.setRotationR(rotationR);

    for (std::size_t n = 0; n < parameters.n_cols; ++n) {
      CHECK(rosenbrockFunctionRotated.getObjectiveValue(parameters.col(n)) == Approx(expected.at(n)));
    }
  }
}
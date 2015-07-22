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

TEST_CASE("bbob::RastriginFunction", "") {
  for (const auto& numberOfDimensions : {2, 40}) {
    mant::bbob::RastriginFunction<> rastriginFunction(numberOfDimensions);

    arma::Mat<double> parameters;
    REQUIRE(parameters.load(testDirectory + "/data/optimisationProblem/blackBoxOptimisationBenchmark/_parameters_" + std::to_string(numberOfDimensions) + "x10.input"));

    arma::Col<double> translation;
    REQUIRE(translation.load(testDirectory + "/data/optimisationProblem/blackBoxOptimisationBenchmark/_translation_" + std::to_string(numberOfDimensions) + "x1.input"));

    arma::Col<double> expected;
    REQUIRE(expected.load(testDirectory + "/data/optimisationProblem/blackBoxOptimisationBenchmark/bbob_rastriginFunction_dim" + std::to_string(numberOfDimensions) +".expected"));

    rastriginFunction.setObjectiveValueTranslation(0);
    rastriginFunction.setParameterTranslation(translation);

    for (std::size_t n = 0; n < parameters.n_cols; ++n) {
      CHECK(rastriginFunction.getObjectiveValue(parameters.col(n)) == Approx(expected.at(n)));
    }
  }

  SECTION("Returns the specified class name.") {
    CHECK(mant::bbob::RastriginFunction<>(5).toString() == "bbob_rastrigin_function");
  }
}
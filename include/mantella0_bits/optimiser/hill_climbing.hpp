/**
Hill climbing
-------------

.. cpp:class:: hill_climbing : public optimiser

  .. versionadded:: 1.0.0

  Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

  Duis autem vel eum iriure dolor in hendrerit in vulputate velit esse molestie consequat, vel illum dolore eu feugiat nulla facilisis at vero eros et accumsan et iusto odio dignissim qui blandit praesent luptatum zzril delenit augue duis dolore te feugait nulla facilisi. Lorem ipsum dolor sit amet, consectetuer adipiscing elit, sed diam nonummy nibh euismod tincidunt ut laoreet dolore magna aliquam erat volutpat.

  .. list-table:: Template parameters

    * - T

        Any floating point type
      - The value type of the parameter and objective value.
    * - N

        ``std::size_t``
      - The number of dimensions.

        Must be within ``[1, std::numeric_limits<std::size_t>::max()]``.

  .. list-table:: Member variables

    * - minimal_stepsize

        ``T``
      - Lorem ipsum dolor sit amet

    * - maximal_stepsize

        ``T``
      - Lorem ipsum dolor sit amet

  .. list-table:: Member functions

    * - hill_climbing

        Constructor
      - Initialises all member variables to their default value.

        Will never throw an exception.
*/
template <typename T, std::size_t N>
struct hill_climbing : optimiser<T, N> {
  T minimal_stepsize;
  T maximal_stepsize;

  hill_climbing() noexcept;
};

//
// Implementation
//

template <typename T, std::size_t N>
hill_climbing<T, N>::hill_climbing() noexcept
    : optimiser<T, N>(),
      minimal_stepsize(T(0.0)),
      maximal_stepsize(T(0.1)) {
  this->optimisation_function = [this](const mant::problem<T, N>& problem, const std::vector<std::array<T, N>>& initial_parameters) {
    assert(T(0.0) <= minimal_stepsize && minimal_stepsize <= maximal_stepsize && minimal_stepsize <= T(1.0));
    assert(maximal_stepsize > T(0.0));

    auto&& start_time  = std::chrono::steady_clock::now();
    optimise_result<T, N> result;

    for (const auto& parameter : initial_parameters) {
      const auto objective_value = problem.objective_function(parameter);
      ++result.evaluations;
      result.duration = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - start_time);

      if (objective_value <= result.objective_value) {
        result.parameter = parameter;
        result.objective_value = objective_value;

        if (result.objective_value <= this->acceptable_objective_value) {
          return result;
        }
      }

      if (result.evaluations >= this->maximal_evaluations) {
        return result;
      } else if (result.duration >= this->maximal_duration) {
        return result;
      }
    }

    while (result.duration < this->maximal_duration && result.evaluations < this->maximal_evaluations && result.objective_value > this->acceptable_objective_value) {
      auto&& parameter = random_neighbour(result.parameter, minimal_stepsize, maximal_stepsize, this->active_dimensions.size());

      std::transform(
        parameter.cbegin(), parameter.cend(),
        parameter.begin(),
        [](const auto element) {
          return std::fmin(std::fmax(element, T(0.0)), T(1.0));
        });

      const auto objective_value = problem.objective_function(parameter);
      ++result.evaluations;
      result.duration = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - start_time);

      if (objective_value < result.objective_value) {
        result.parameter = parameter;
        result.objective_value = objective_value;
      }
    }

    return result;
  };
}

//
// Unit tests
//

#if defined(MANTELLA_BUILD_TESTS)
TEST_CASE("hill_climbing", "[optimser][hill_climbing]") {
  constexpr std::size_t dimensions = 3;
  mant::hill_climbing<double, dimensions> optimiser;

  SECTION("Default configuration") {
    CHECK(optimiser.minimal_stepsize == 0.0);
    CHECK(optimiser.maximal_stepsize == 0.1);
  }

  SECTION("Boundary handling") {
    mant::problem<double, dimensions> problem;
    problem.objective_function = [](const auto& parameter) {
      return std::accumulate(parameter.cbegin(), parameter.cend(), 0.0);
    };

    const auto&& result = optimiser.optimisation_function(problem, {{0.0, 0.0, 0.0}});
    CHECK(std::all_of(
      result.parameter.cbegin(), std::next(result.parameter.cbegin(), optimiser.active_dimensions.size()),
      std::bind(std::greater_equal<double>{}, std::placeholders::_1, 0.0)
    ) == true);
  }

  SECTION("Stopping criteria") {
    optimiser.maximal_duration = std::chrono::seconds(10);
    optimiser.maximal_evaluations = 1000;
    auto&& result = optimiser.optimisation_function(mant::sphere_function<double, dimensions>(), {{0.0, 0.0, 0.0}});
    CHECK(result.evaluations == 1000);
    optimiser.maximal_duration = std::chrono::microseconds(1);
    result = optimiser.optimisation_function(mant::sphere_function<double, dimensions>(), {{0.0, 0.0, 0.0}});
    CHECK(result.duration >= std::chrono::microseconds(1));
    CHECK(result.duration < std::chrono::milliseconds(1));
  }
}
#endif

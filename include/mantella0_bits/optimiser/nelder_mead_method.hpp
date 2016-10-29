/**

*/
template <typename T, std::size_t N>
struct nelder_mead_method : optimiser<T, N> {
  T reflection_weight;
  T expansion_weight;
  T contraction_weight;
  T shrinking_weight;

  nelder_mead_method() noexcept;
};

//
// Implementation
//

template <typename T, std::size_t N>
nelder_mead_method<T, N>::nelder_mead_method() noexcept 
    : optimiser<T, N>(),
      reflection_weight(T(1.0)),
      expansion_weight(T(2.0)),
      contraction_weight(T(0.5)),
      shrinking_weight(T(0.5)) {
  this->optimisation_function = [this](const mant::problem<T, N>& problem, const std::vector<std::array<T, N>>& initial_parameters) {
    assert(initial_parameters.size() == N + 1);
    assert(reflection_weight > T(0.0));
    assert(expansion_weight > T(0.0));
    assert(contraction_weight > T(0.0));
    assert(shrinking_weight > T(0.0));
    
    auto&& start_time  = std::chrono::steady_clock::now();
    optimise_result<T, N> result;
    
    result.best_parameter = initial_parameters.at(0);
    result.best_objective_value = problem.objective_function(initial_parameters.at(0));
    ++result.number_of_evaluations;
    result.duration = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - start_time);
        
    if (result.best_objective_value <= this->acceptable_objective_value) {
      return result;
    } else if (result.number_of_evaluations >= this->maximal_number_of_evaluations) {
      return result;
    } else if (result.duration >= this->maximal_duration) {
      return result;
    }

    std::array<std::pair<std::array<T, N>, T>, N> simplex;
    for (std::size_t n = 1; n < initial_parameters.size(); ++n) {
      const auto& parameter = initial_parameters.at(n);
      const auto objective_value = problem.objective_function(parameter);
      ++result.number_of_evaluations;
      result.duration = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - start_time);
      
      simplex.at(n - 1) = {parameter, objective_value};
      
      if (objective_value < result.best_objective_value) {
        result.best_parameter = parameter;
        result.best_objective_value = objective_value;
        
        if (result.best_objective_value <= this->acceptable_objective_value) {
          return result;
        }
      }
      
      if (result.number_of_evaluations >= this->maximal_number_of_evaluations) {
        return result;
      } else if (result.duration >= this->maximal_duration) {
        return result;
      }
    }
    
    std::sort(
      simplex.begin(), simplex.end(),
      [](const auto& simplex, const auto& other_simplex){
        return std::get<1>(simplex) < std::get<1>(other_simplex);
      });
    
    std::array<T, N> centroid = result.best_parameter;
    std::for_each(
      simplex.cbegin(), std::prev(simplex.cend()),
      [this, &centroid](const auto& point) {
        for (std::size_t n = 0; n < this->active_dimensions.size(); ++n) {
          centroid.at(n) += std::get<0>(point).at(n) / static_cast<T>(N);
        }
      });
    
    while (result.duration < this->maximal_duration && result.number_of_evaluations < this->maximal_number_of_evaluations && result.best_objective_value > this->acceptable_objective_value) {
      std::array<T, N> reflected_point;
      std::transform(
        centroid.cbegin(), std::next(centroid.cbegin(), this->active_dimensions.size()),
        result.best_parameter.cbegin(),
        reflected_point.begin(),
        [this](const auto centroid, const auto best_parameter) {
          return std::fmin(std::fmax(centroid + reflection_weight * (centroid - best_parameter), T(0.0)), T(1.0));
        });
      
      auto objective_value = problem.objective_function(reflected_point);
      ++result.number_of_evaluations;
      result.duration = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - start_time);
      
      if (objective_value < result.best_objective_value) {
        for (std::size_t n = 0; n < N; ++n) {
          centroid.at(n) += (reflected_point.at(n) - result.best_parameter.at(n)) / static_cast<T>(N);
        }
        
        result.best_parameter = reflected_point;
        result.best_objective_value = objective_value;
        
        if (result.best_objective_value <= this->acceptable_objective_value) {
          return result;
        } else if (result.number_of_evaluations >= this->maximal_number_of_evaluations) {
          return result;
        } else if (result.duration >= this->maximal_duration) {
          return result;
        }
        
        std::array<T, N> expanded_point;
        std::transform(
          centroid.cbegin(), std::next(centroid.cbegin(), this->active_dimensions.size()),
          reflected_point.cbegin(),
          expanded_point.begin(),
          [this](const auto centroid, const auto reflected_point) {
            return std::fmin(std::fmax(centroid + expansion_weight * (reflected_point - centroid), T(0.0)), T(1.0));
          });
          
        objective_value = problem.objective_function(expanded_point);
        ++result.number_of_evaluations;
        result.duration = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - start_time);
        
        if (objective_value < result.best_objective_value) {
          for (std::size_t n = 0; n < N; ++n) {
            centroid.at(n) += (expanded_point.at(n) - result.best_parameter.at(n)) / static_cast<T>(N);
          }
        
          result.best_parameter = expanded_point;
          result.best_objective_value = objective_value;
        }
      
        continue;
      }
      
      if (result.number_of_evaluations >= this->maximal_number_of_evaluations) {
        return result;
      } else if (result.duration >= this->maximal_duration) {
        return result;
      }
      
      if (objective_value < std::get<1>(std::get<N-1>(simplex))) {
        auto position = std::find_if(
          simplex.begin(), std::prev(simplex.end()),
          [objective_value](const auto& point) {
            return objective_value < std::get<1>(point);
          });
          
        for (std::size_t n = 0; n < N; ++n) {
          centroid.at(n) += (reflected_point.at(n) - std::get<0>(*position).at(n)) / static_cast<T>(N);
        }
          
        std::copy_backward(position, std::prev(simplex.end()), simplex.end());
        *position = {reflected_point, objective_value};
      } else {
        std::array<T, N> contracted_point;
        std::transform(
          centroid.cbegin(), std::next(centroid.cbegin(), this->active_dimensions.size()),
          std::get<0>(std::get<N-1>(simplex)).cbegin(),
          contracted_point.begin(),
          [this](const auto centroid, const auto worst_parameter) {
            return centroid + contraction_weight * (worst_parameter - centroid);
          });
        
        auto objective_value = problem.objective_function(contracted_point);
        ++result.number_of_evaluations;
        result.duration = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - start_time);
        
        if (objective_value < result.best_objective_value) {
          for (std::size_t n = 0; n < N; ++n) {
            centroid.at(n) += (contracted_point.at(n) - result.best_parameter.at(n)) / static_cast<T>(N);
          }
        
          result.best_parameter = contracted_point;
          result.best_objective_value = objective_value;
        } else if (objective_value < std::get<1>(std::get<N-1>(simplex))) {
          auto position = std::find_if(
            simplex.begin(), std::prev(simplex.end()),
            [objective_value](const auto& point) {
              return objective_value < std::get<1>(point);
            });
            
          for (std::size_t n = 0; n < N; ++n) {
            centroid.at(n) += (contracted_point.at(n) - std::get<0>(*position).at(n)) / static_cast<T>(N);
          }
            
          std::copy_backward(position, std::prev(simplex.end()), simplex.end());
          *position = {contracted_point, objective_value};
        } else {
          for (auto& point : simplex) {
            std::transform(
              result.best_parameter.cbegin(), std::next(result.best_parameter.cbegin(), this->active_dimensions.size()),
              std::get<0>(point).cbegin(),
              std::get<0>(point).begin(),
              [this](const auto best_parameter, const auto point) {
                return best_parameter + shrinking_weight * (point - best_parameter);
              });
              
            point = {std::get<0>(point), problem.objective_function(std::get<0>(point))};
            ++result.number_of_evaluations;
      
            if (result.number_of_evaluations >= this->maximal_number_of_evaluations) {
              return result;
            } else if (result.duration >= this->maximal_duration) {
              return result;
            }
          }
          
          std::sort(
            simplex.begin(), simplex.end(),
            [](const auto& simplex, const auto& other_simplex){
              return std::get<1>(simplex) < std::get<1>(other_simplex);
            });
          
          std::array<T, N> centroid = result.best_parameter;
          std::for_each(
            simplex.cbegin(), std::prev(simplex.cend()),
            [this, &centroid](const auto& point) {
              for (std::size_t n = 0; n < this->active_dimensions.size(); ++n) {
                centroid.at(n) += std::get<0>(point).at(n) / static_cast<T>(N);
              }
            });
        }
      }
    }
    
    return result;
  };
}

//
// Unit tests
//

#if defined(MANTELLA_BUILD_TESTS)
TEST_CASE("nelder_mead_method", "[nelder_mead_method]") {
  constexpr std::size_t number_of_dimensions = 3;
  const mant::nelder_mead_method<double, number_of_dimensions> optimiser; 
  
  SECTION("Default configuration") {
    CHECK(optimiser.reflection_weight == Approx(1.0));
    CHECK(optimiser.expansion_weight == Approx(2.0));
    CHECK(optimiser.contraction_weight == Approx(0.5));
    CHECK(optimiser.shrinking_weight == Approx(0.5));
  }
  
  SECTION("Benchmarking") {
    const std::array<std::unique_ptr<mant::problem<double, number_of_dimensions>>, 5> problems = {
      std::unique_ptr<mant::problem<double, number_of_dimensions>>(new mant::ackley_function<double, number_of_dimensions>),
      std::unique_ptr<mant::problem<double, number_of_dimensions>>(new mant::rastrigin_function<double, number_of_dimensions>),
      std::unique_ptr<mant::problem<double, number_of_dimensions>>(new mant::rosenbrock_function<double, number_of_dimensions>),
      std::unique_ptr<mant::problem<double, number_of_dimensions>>(new mant::sphere_function<double, number_of_dimensions>),
      std::unique_ptr<mant::problem<double, number_of_dimensions>>(new mant::sum_of_different_powers_function<double, number_of_dimensions>)
    };
    
    std::vector<std::array<double, number_of_dimensions>> initial_parameters(number_of_dimensions + 1);
    for (auto& parameter : initial_parameters) {
      std::generate(
        parameter.begin(), std::next(parameter.begin(), optimiser.active_dimensions.size()),
        std::bind(
          std::uniform_real_distribution<double>(0.0, 1.0),
          std::ref(random_number_generator())));
    }
    
    std::array<mant::optimise_result<double, number_of_dimensions>, problems.size()> results;
    std::transform(
      problems.cbegin(), problems.cend(),
      results.begin(),
      [&optimiser, &initial_parameters](auto&& problem) {
        return optimiser.optimisation_function(*problem, initial_parameters);
      }
    );
    
    std::cout << "Nelder-Mead method" << std::endl;
    for (auto&& result : results) {
      std::cout << "best_parameter: [ ";
      std::copy(result.best_parameter.cbegin(), result.best_parameter.cend(), std::ostream_iterator<double>(std::cout, " "));
      std::cout << "], best_objective_value: " << result.best_objective_value
                << ", number_of_evaluations: " << result.number_of_evaluations
                << ", duration: " << result.duration.count() << "ns" << std::endl;
    }
  }
  
  SECTION("Boundary handling") {
    mant::problem<double, number_of_dimensions> problem;
    problem.objective_function = [](const auto& parameter) {
      return std::accumulate(parameter.cbegin(), parameter.cend(), 0.0);
    };
    
    std::vector<std::array<double, number_of_dimensions>> initial_parameters(number_of_dimensions + 1);
    for (auto& parameter : initial_parameters) {
      std::generate(
        parameter.begin(), std::next(parameter.begin(), optimiser.active_dimensions.size()),
        std::bind(
          std::uniform_real_distribution<double>(0.0, 1.0),
          std::ref(random_number_generator())));
    }
    
    const auto&& result = optimiser.optimisation_function(problem, initial_parameters);
    CHECK(std::all_of(
      result.best_parameter.cbegin(), std::next(result.best_parameter.cbegin(), optimiser.active_dimensions.size()),
      [](const auto element) { 
        return element >= 0.0;
      }
    ) == true);
  }
}
#endif
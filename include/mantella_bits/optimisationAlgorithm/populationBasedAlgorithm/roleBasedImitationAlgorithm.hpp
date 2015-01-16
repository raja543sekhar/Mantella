#pragma once

// Mantella
#include <mantella_bits/optimisationAlgorithm/populationBasedAlgorithm.hpp>
#include <mantella_bits/distanceFunction/euclideanDistance.hpp>
#include <mantella_bits/helper/random.hpp>
#include <mantella_bits/helper/rng.hpp>

namespace mant {
  template<class DistanceFunction>
  class RoleBasedImitationAlgorithm : public PopulationBasedAlgorithm<double, DistanceFunction> {
    public:
      explicit RoleBasedImitationAlgorithm(
          const std::shared_ptr<OptimisationProblem<double>> optimisationProblem,
          const unsigned int& populationSize) noexcept;

      RoleBasedImitationAlgorithm(const RoleBasedImitationAlgorithm&) = delete;
      RoleBasedImitationAlgorithm& operator=(const RoleBasedImitationAlgorithm&) = delete;

      void setNeighbourhoodSize(
          const unsigned int& neighbourhoodSize) noexcept;
      void setStepSize(
          const double& stepSize) noexcept;
      void setMaximalNeighourhoodConvergence(
          const arma::Col<double>& maximalNeighourhoodConvergence) noexcept;

      std::string to_string() const noexcept override;

    protected:
      arma::Col<double> stepSize_;
      unsigned int neighbourhoodSize_;
      arma::Col<double> maximalNeighourhoodConvergence_;

      void optimiseImplementation() noexcept override;
  };

  template<class DistanceFunction>
  RoleBasedImitationAlgorithm<DistanceFunction>::RoleBasedImitationAlgorithm(
      const std::shared_ptr<OptimisationProblem<double>> optimisationProblem,
      const unsigned int& populationSize) noexcept
    : PopulationBasedAlgorithm<double, EuclideanDistance>(optimisationProblem, populationSize),
      maximalNeighourhoodConvergence_(this->populationSize_),
      neighbourhoodSize_(0),
      stepSize_(arma::square((this->optimisationProblem_->getUpperBounds() - this->optimisationProblem_->getLowerBounds()) / 100)) {

  }

  template<class DistanceFunction>
  void RoleBasedImitationAlgorithm<DistanceFunction>::optimiseImplementation() noexcept {
    arma::Mat<double> agents = arma::randu<arma::Mat<double>>(this->optimisationProblem_->getNumberOfDimensions(), this->populationSize_);
    agents.each_col() %= this->optimisationProblem_->getUpperBounds() - this->optimisationProblem_->getLowerBounds();
    agents.each_col() += this->optimisationProblem_->getLowerBounds();

    arma::Col<double> objectiveValues(this->populationSize_);
    for (std::size_t n = 0; n < this->populationSize_; ++n) {
      ++this->numberOfIterations_;

      arma::Col<double> solution = agents.col(n);
      double objectiveValue = this->optimisationProblem_->getObjectiveValue(solution) + this->optimisationProblem_->getSoftConstraintsValue(solution);
      objectiveValues.at(n) = objectiveValue;

      if (objectiveValue < this->bestObjectiveValue_) {
        this->bestParameter_ = solution;
        this->bestObjectiveValue_ = objectiveValue;
      }

      if (this->isFinished() || this->isTerminated()) {
        break;
      }
    }

    while (!this->isFinished() && !this->isTerminated()) {
      arma::Col<unsigned int> permutation = getRandomPermutation(this->populationSize_);
      for (std::size_t n = 0; n < this->populationSize_; ++n) {
        ++this->numberOfIterations_;

        std::size_t k = permutation.at(n);
        arma::Col<double> currentSolution = agents.col(k);
        double currentObjectiveValue = objectiveValues.at(k);

        arma::Col<unsigned int> parametersToMutate = getRandomPermutation(this->optimisationProblem_->getNumberOfDimensions(), std::uniform_int_distribution<unsigned int>(0, this->optimisationProblem_->getNumberOfDimensions())(Rng::generator));

        arma::Col<unsigned int> neighbourIndicies = getRandomPermutation(this->populationSize_ - 1, neighbourhoodSize_);
        neighbourIndicies.elem(arma::find(neighbourIndicies >= k)) += 1;

        arma::Col<double> neighbourParameters = agents.elem(neighbourIndicies);
        arma::Col<double> neighbourObjectiveValues = objectiveValues.elem(neighbourIndicies);

        double meanNeighbourFitness = arma::mean(neighbourObjectiveValues);
        arma::Col<double> meanNeighbourParameters = arma::mean(neighbourParameters.rows(parametersToMutate), 1);
        arma::Col<double> stddevNeighbourParameters = arma::stddev(neighbourParameters.rows(parametersToMutate), 1);

        arma::Col<unsigned int> betterNeighbourIndicies = arma::find(neighbourObjectiveValues < currentObjectiveValue);
        arma::Col<unsigned int> worseOrEqualNeighbourIndicies = arma::find(neighbourObjectiveValues >= currentObjectiveValue);

        if (betterNeighbourIndicies.n_elem > 0) {
          arma::Col<double> betterNeighbourFitness = neighbourObjectiveValues.elem(betterNeighbourIndicies);

          double meanBetterNeighbourFitness = arma::mean(betterNeighbourFitness);
          double stddevBetterNeighbourFitness = arma::stddev(betterNeighbourFitness);

          arma::Col<double> meanBetterParameters = arma::mean(neighbourParameters.submat(parametersToMutate, betterNeighbourIndicies), 1);
        }

        if (worseOrEqualNeighbourIndicies.n_elem > 0) {
          arma::Col<double> meanWorseParameters = arma::mean(neighbourParameters.submat(parametersToMutate, worseOrEqualNeighbourIndicies), 1);
        }

        if (betterNeighbourIndicies.n_elem > 0) {
          for (const auto& parameterToMutate : parametersToMutate) {
            if (stddevNeighbourParameters.at(parameterToMutate) < stepSize_.at(parameterToMutate)) {

            }
          }
        } else {

        }

        //                if convergedSize > 0

        //                    convergedParameter = parametersToMutate(converged);

        //                    % notNeighbours = setdiff(agents, [neighbours(:); agent]);
        //                    notNeighbours = agents(~ismembc(agents, sort([neighbours(:); agent])));

        //                    factor = ones(1, convergedSize);
        //                    factor(randperm(convergedSize, randi(convergedSize))) = -1;

        //                    p = rand(1, convergedSize);

        //                    other_k = parameters(sub2ind(size(parameters), notNeighbours(randi(size(notNeighbours, 2), 1, convergedSize)), convergedParameter));
        //                    other_j = parameters(sub2ind(size(parameters), notNeighbours(randi(size(notNeighbours, 2), 1, convergedSize)), convergedParameter));
        //                    x = other_k .* (1 - p) + other_j .* p;

        //                    parametersCandidate = x + factor .* abs(x - factor .* max(factor .* other_k, factor .* other_j)) .* rand(1, convergedSize) * 2;
        //                    withinBoundary = parametersCandidate >= lowerBounds(convergedParameter) & parametersCandidate <= upperBounds(convergedParameter);
        //                    parameters(agent, convergedParameter(withinBoundary)) = parametersCandidate(withinBoundary);
        //                else
        //                    static = true;
        //                end
      }
    }
  }

  template<class DistanceFunction>
  void RoleBasedImitationAlgorithm<DistanceFunction>::setNeighbourhoodSize(
      const unsigned int& neighbourhoodSize) noexcept {
    neighbourhoodSize_ = neighbourhoodSize;
  }

  template<class DistanceFunction>
  void RoleBasedImitationAlgorithm<DistanceFunction>::setMaximalNeighourhoodConvergence(
      const arma::Col<double>& maximalNeighourhoodConvergence) noexcept {
    maximalNeighourhoodConvergence_ = maximalNeighourhoodConvergence;
  }

  template<class DistanceFunction>
  std::string RoleBasedImitationAlgorithm<DistanceFunction>::to_string() const noexcept {
    return "RoleBasedImitationAlgorithm";
  }
}

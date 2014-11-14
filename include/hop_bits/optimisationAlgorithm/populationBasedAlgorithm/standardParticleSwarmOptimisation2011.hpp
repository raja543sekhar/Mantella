#pragma once

// HOP
#include <hop_bits/optimisationAlgorithm/populationBasedAlgorithm.hpp>

namespace hop {
  class StandardParticleSwarmOptimisation2011 : public PopulationBasedAlgorithm {
    public:
      explicit StandardParticleSwarmOptimisation2011(
          const std::shared_ptr<OptimisationProblem> optimisationProblem, const unsigned int& populationSize);

      StandardParticleSwarmOptimisation2011(const StandardParticleSwarmOptimisation2011&) = delete;
      StandardParticleSwarmOptimisation2011& operator=(const StandardParticleSwarmOptimisation2011&) = delete;

      void setNeighbourhoodProbability(
          const double& neighbourhoodProbability);
      void setAcceleration(
          const double& acceleration);
      void setLocalAttraction(
          const double& localAttraction);
      void setGlobalAttraction(
          const double& globalAttraction);

      void setMaximalSwarmConvergence(
          const double& swarmConvergence);

      std::string to_string() const override;

    protected:
      arma::Mat<double> particles_;
      arma::Mat<double> velocities_;

      arma::Mat<double> localBestSolutions_;
      arma::Row<double> localBestObjectiveValues_;

      double neighbourhoodProbability_;
      double acceleration_;
      double localAttraction_;
      double globalAttraction_;

      double maximalSwarmConvergence_;

      bool randomizeTopology_;

      arma::Mat<arma::uword> topology_;

      void optimiseImplementation() override;

      void initialiseSwarm();
  };
}
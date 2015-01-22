namespace mant {
  template <typename ParameterType, class DistanceFunction>
  class DirectLipschitzContinuityAnalysis : public LipschitzContinuityAnalysis<ParameterType, DistanceFunction> {
    public:
      using LipschitzContinuityAnalysis<ParameterType, DistanceFunction>::LipschitzContinuityAnalysis;

    protected:
      void analyseImplementation(
          const std::shared_ptr<OptimisationProblem<ParameterType>> optimisationProblem)  override;
      void analyseImplementation(
          const std::unordered_map<arma::Col<ParameterType>, double, Hash, IsKeyEqual>& parameterToObjectiveValueMappings)  override;
      void analyseImplementation(
          const std::pair<arma::Col<ParameterType>, double>& parameterToObjectiveValueMapping)  override;
  };

  template <>
  inline void DirectLipschitzContinuityAnalysis<double, EuclideanDistance>::analyseImplementation(
      const std::shared_ptr<OptimisationProblem<double>> optimisationProblem) ;

  template <typename ParameterType, class DistanceFunction>
  void DirectLipschitzContinuityAnalysis<ParameterType, DistanceFunction>::analyseImplementation(
      const std::shared_ptr<OptimisationProblem<ParameterType>> optimisationProblem)  {
    this->lipschitzConstant_ = 0.0;

    const std::unordered_map<arma::Col<ParameterType>, double, Hash, IsKeyEqual>& parameterToObjectiveValueMappings = optimisationProblem->getCachedObjectiveValues();

    DistanceFunction distanceFunction;
    for (auto n = parameterToObjectiveValueMappings.cbegin(); n != parameterToObjectiveValueMappings.cend();) {
      const arma::Col<ParameterType>& parameter = n->first;
      const double& objectiveValue = n->second;
      for (auto k = ++n; k != parameterToObjectiveValueMappings.cend(); ++k) {
        this->lipschitzConstant_ = std::max(this->lipschitzConstant_, std::abs(k->second - objectiveValue) / distanceFunction.getDistance(parameter, k->first));
      }
    }
  }

  template <typename ParameterType, class DistanceFunction>
  void DirectLipschitzContinuityAnalysis<ParameterType, DistanceFunction>::analyseImplementation(
      const std::unordered_map<arma::Col<ParameterType>, double, Hash, IsKeyEqual>& parameterToObjectiveValueMappings)  {

  }

  template <typename ParameterType, class DistanceFunction>
  void DirectLipschitzContinuityAnalysis<ParameterType, DistanceFunction>::analyseImplementation(
      const std::pair<arma::Col<ParameterType>, double>& parameterToObjectiveValueMapping)  {

  }

  template <>
  inline void DirectLipschitzContinuityAnalysis<double, EuclideanDistance>::analyseImplementation(
      const std::shared_ptr<OptimisationProblem<double>> optimisationProblem)  {
    lipschitzConstant_ = 0.0;

    const std::unordered_map<arma::Col<double>, double, Hash, IsKeyEqual>& parameterToObjectiveValueMappings = optimisationProblem->getCachedObjectiveValues();

    for (auto n = parameterToObjectiveValueMappings.cbegin(); n != parameterToObjectiveValueMappings.cend();) {
      const arma::Col<double>& parameter = n->first;
      const double& objectiveValue = n->second;
      for (auto k = ++n; k != parameterToObjectiveValueMappings.cend(); ++k) {
        lipschitzConstant_ = std::max(lipschitzConstant_, std::abs(k->second - objectiveValue) / arma::norm(k->first - parameter));
      }
    }
  }
}

namespace mant {
  namespace bbob {
    template <typename T = double>
    class AttractiveSectorFunction : public BlackBoxOptimisationBenchmark<T> {
      static_assert(std::is_floating_point<T>::value, "T must be a floating point type.");
    
      public:
        explicit AttractiveSectorFunction(
            const std::size_t numberOfDimensions) noexcept;

        void setRotationQ(
            const arma::Mat<T>& rotationQ);

        std::string toString() const noexcept override;

      protected:
        const arma::Col<T> parameterConditioning_;

        arma::Mat<T> rotationQ_;

        T getObjectiveValueImplementation(
            const arma::Col<T>& parameter) const noexcept override;
        
#if defined(MANTELLA_USE_PARALLEL_ALGORITHMS)
        friend class OptimisationAlgorithm;
        
        std::vector<long double> serialise() const noexcept;

        void deserialise(
            const std::vector<long double>& serialisedOptimisationProblem);
#endif
    };
  
    //
    // Implementation
    //

    template <typename T>
    AttractiveSectorFunction<T>::AttractiveSectorFunction(
        const std::size_t numberOfDimensions) noexcept
      : BlackBoxOptimisationBenchmark<T>(numberOfDimensions),
        parameterConditioning_(this->getParameterConditioning(std::sqrt(static_cast<T>(10.0L)))) {
      this->setParameterTranslation(this->getRandomParameterTranslation());
      this->setParameterRotation(getRandomRotationMatrix(this->numberOfDimensions_));
      setRotationQ(getRandomRotationMatrix(this->numberOfDimensions_));
    }

    template <typename T>
    void AttractiveSectorFunction<T>::setRotationQ(
        const arma::Mat<T>& rotationQ) {
      verify(rotationQ.n_rows == this->numberOfDimensions_, "The number of rows must be equal to the number of dimensions");
      verify(isRotationMatrix(rotationQ), "The parameter must be a rotation matrix.");

      rotationQ_ = rotationQ;
    }

    template <typename T>
    T AttractiveSectorFunction<T>::getObjectiveValueImplementation(
        const arma::Col<T>& parameter) const noexcept {
      arma::Col<T> z = rotationQ_ * (parameterConditioning_ % parameter);
      z.elem(arma::find(z % this->parameterTranslation_ > static_cast<T>(0.0L))) *= static_cast<T>(100.0L);

      return std::pow(this->getOscillatedValue(std::pow(arma::norm(z), static_cast<T>(2.0L))), static_cast<T>(0.9L));
    }

    template <typename T>
    std::string AttractiveSectorFunction<T>::toString() const noexcept {
      return "bbob_attractive_sector_function";
    }

#if defined(MANTELLA_USE_PARALLEL_ALGORITHMS)
    template <typename T>
    std::vector<long double> AttractiveSectorFunction<T>::serialise() const noexcept {
      std::vector<long double> serialisedOptimisationProblem = BlackBoxOptimisationBenchmark<T, T>::serialise();
      
      for(std::size_t n = 0; n < rotationQ_.n_elem; ++n) {
        serialisedOptimisationProblem.push_back(rotationQ_(n));
      }
      
      return serialisedOptimisationProblem;
    }

    template <typename T>
    void AttractiveSectorFunction<T>::deserialise(
        const std::vector<long double>& serialisedOptimisationProblem) {
      rotationQ_.set_size(this->numberOfDimensions_, this->numberOfDimensions_);
      for(std::size_t n = 0; n < rotationQ_.n_elem; ++n) {
        rotationQ_(n) = serialisedOptimisationProblem.pop_back();
      }
        
      BlackBoxOptimisationBenchmark<T, T>::deserialise(serialisedOptimisationProblem);
    }
#endif
  }
}
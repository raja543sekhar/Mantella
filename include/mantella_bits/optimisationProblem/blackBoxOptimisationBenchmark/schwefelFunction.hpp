namespace mant {
  namespace bbob {
    template <typename T = double>
    class SchwefelFunction : public BlackBoxOptimisationBenchmark<T> {
      static_assert(std::is_floating_point<T>::value, "T must be a floating point type.");
    
      public:
        explicit SchwefelFunction(
            const std::size_t numberOfDimensions) noexcept;

        std::string toString() const noexcept override;

      protected:
        const arma::Col<T> parameterConditioning_;

        T getObjectiveValueImplementation(
            const arma::Col<T>& parameter) const noexcept override;

#if defined(MANTELLA_USE_PARALLEL)
        friend class cereal::access;

        template <typename Archive>
        void serialize(
            Archive& archive) noexcept {
          archive(cereal::make_nvp("BlackBoxOptimisationBenchmark", cereal::base_class<BlackBoxOptimisationBenchmark>(this)));
          archive(cereal::make_nvp("numberOfDimensions", numberOfDimensions_));
        }

        template <typename Archive>
        static void load_and_construct(
            Archive& archive,
            cereal::construct<SchwefelFunction>& construct) noexcept {
          unsigned int numberOfDimensions;
          archive(cereal::make_nvp("numberOfDimensions", numberOfDimensions));
          construct(numberOfDimensions);

          archive(cereal::make_nvp("BlackBoxOptimisationBenchmark", cereal::base_class<BlackBoxOptimisationBenchmark>(construct.ptr())));
        }
#endif
    };

    //
    // Implementation
    //

    template <typename T>
    SchwefelFunction<T>::SchwefelFunction(
        const std::size_t numberOfDimensions) noexcept
      : BlackBoxOptimisationBenchmark<T>(numberOfDimensions),
        parameterConditioning_(this->getParameterConditioning(std::sqrt(static_cast<T>(10.0L)))) {
      // A vector with all elements randomly and uniformly set to either 2 or -2.
      this->setParameterScaling(arma::zeros<arma::Col<T>>(this->numberOfDimensions_) + (std::bernoulli_distribution(0.5)(Rng::getGenerator()) ? static_cast<T>(2.0L) : static_cast<T>(-2.0L)));
    }

    template <typename T>
    T SchwefelFunction<T>::getObjectiveValueImplementation(
        const arma::Col<T>& parameter) const noexcept {
      arma::Col<T> s = parameter;
      s.tail(s.n_elem - 1) += static_cast<T>(0.25L) * (s.head(s.n_elem - 1) - static_cast<T>(4.2096874633L));

      const arma::Col<T>& z = static_cast<T>(100.0L) * (parameterConditioning_ % (s - static_cast<T>(4.2096874633L)) + static_cast<T>(4.2096874633L));

      return static_cast<T>(0.01L) * (static_cast<T>(418.9828872724339L) - arma::dot(z, arma::sin(arma::sqrt(arma::abs(z)))) / static_cast<T>(this->numberOfDimensions_)) + static_cast<T>(100.0L) * this->getBoundConstraintsValue(z / static_cast<T>(100.0L));
    }

    template <typename T>
    std::string SchwefelFunction<T>::toString() const noexcept {
      return "bbob_schwefel_function";
    }
  }
}
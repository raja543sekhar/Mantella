namespace mant {
  namespace bbob {
    template <typename T = double>
    class GallaghersGaussian101mePeaksFunction : public BlackBoxOptimisationBenchmark<T> {
      static_assert(std::is_floating_point<T>::value, "T must be a floating point type.");
    
      public:
        explicit GallaghersGaussian101mePeaksFunction(
            const std::size_t numberOfDimensions) noexcept;

        virtual void setRotationQ(
            const arma::Mat<T>& rotationQ);

        virtual void setLocalParameterConditionings(
            const arma::Mat<T>& localParameterConditionings);

        virtual void setLocalParameterTranslations(
            const arma::Mat<T>& localParameterTranslations);

        std::string toString() const noexcept override;

      protected:
        const typename arma::Col<T>::template fixed<101> weight_;

        arma::Mat<T> rotationQ_;
        arma::Mat<T> localParameterConditionings_;
        arma::Mat<T> localParameterTranslations_;

        arma::Mat<T> getRandomLocalParameterConditionings() const noexcept;

        arma::Mat<T> getRandomLocalParameterTranslations() const noexcept;

        T getSoftConstraintsValueImplementation(
            const arma::Col<T>& parameter) const noexcept override;

        T getObjectiveValueImplementation(
            const arma::Col<T>& parameter) const noexcept override;

#if defined(MANTELLA_USE_PARALLEL)
        friend class cereal::access;

        template <typename Archive>
        void serialize(
            Archive& archive) noexcept {
          archive(cereal::make_nvp("BlackBoxOptimisationBenchmark", cereal::base_class<BlackBoxOptimisationBenchmark>(this)));
          archive(cereal::make_nvp("numberOfDimensions", numberOfDimensions_));
          archive(cereal::make_nvp("rotationQ", rotationQ_));
          archive(cereal::make_nvp("localParameterConditionings", localParameterConditionings_));
          archive(cereal::make_nvp("localParameterTranslations", localParameterTranslations_));
        }

        template <typename Archive>
        static void load_and_construct(
            Archive& archive,
            cereal::construct<GallaghersGaussian101mePeaksFunction>& construct) noexcept {
          unsigned int numberOfDimensions;
          archive(cereal::make_nvp("numberOfDimensions", numberOfDimensions));
          construct(numberOfDimensions);

          archive(cereal::make_nvp("BlackBoxOptimisationBenchmark", cereal::base_class<BlackBoxOptimisationBenchmark>(construct.ptr())));
          archive(cereal::make_nvp("rotationQ", construct->rotationQ_));
          archive(cereal::make_nvp("localParameterConditionings", construct->localParameterConditionings_));
          archive(cereal::make_nvp("localParameterTranslations", construct->localParameterTranslations_));
        }
#endif
    };

    //
    // Implementation
    //

    template <typename T>
    GallaghersGaussian101mePeaksFunction<T>::GallaghersGaussian101mePeaksFunction(
        const std::size_t numberOfDimensions) noexcept
      : BlackBoxOptimisationBenchmark<T>(numberOfDimensions),
        weight_(arma::join_cols(arma::Col<T>({static_cast<T>(10.0L)}), arma::linspace<arma::Col<T>>(static_cast<T>(1.1L), static_cast<T>(9.1L), 100))) {
      setRotationQ(getRandomRotationMatrix(this->numberOfDimensions_));
      setLocalParameterConditionings(getRandomLocalParameterConditionings());
      setLocalParameterTranslations(getRandomLocalParameterTranslations());
    }

    template <typename T>
    void GallaghersGaussian101mePeaksFunction<T>::setRotationQ(
        const arma::Mat<T>& rotationQ) {
      verify(rotationQ.n_rows == this->numberOfDimensions_, "The number of rows must be equal to the number of dimensions");
      verify(isRotationMatrix(rotationQ), "The parameter must be a rotation matrix.");

      rotationQ_ = rotationQ;
    }

    template <typename T>
    void GallaghersGaussian101mePeaksFunction<T>::setLocalParameterConditionings(
        const arma::Mat<T>& localParameterConditionings) {
      verify(localParameterConditionings.n_rows == this->numberOfDimensions_, "The number of rows must be equal to the number of dimensions");
      verify(localParameterConditionings.n_cols == 101, "The number of columns must be equal to the number of peaks (101).");

      localParameterConditionings_ = localParameterConditionings;
    }

    template <typename T>
    void GallaghersGaussian101mePeaksFunction<T>::setLocalParameterTranslations(
        const arma::Mat<T>& localParameterTranslations) {
      verify(localParameterTranslations.n_rows == this->numberOfDimensions_, "The number of rows must be equal to the number of dimensions");
      verify(localParameterTranslations.n_cols == 101, "The number of columns must be equal to the number of peaks (101).");

      localParameterTranslations_ = localParameterTranslations;
    }

    template <typename T>
    arma::Mat<T> GallaghersGaussian101mePeaksFunction<T>::getRandomLocalParameterConditionings() const noexcept {
      arma::Col<T> conditions(101);
      conditions(0) = static_cast<T>(49.5L);
      conditions.tail(conditions.n_elem - 1) = arma::conv_to<arma::Col<T>>::from(getRandomPermutation(conditions.n_elem - 1));

      arma::Mat<T> localParameterConditionings(this->numberOfDimensions_, conditions.n_elem);
      for (std::size_t n = 0; n < conditions.n_elem; ++n) {
        const T& condition = std::pow(static_cast<T>(10.0L), conditions(n) / static_cast<T>(33.0L));
        localParameterConditionings.col(n) = this->getParameterConditioning(condition) / std::sqrt(condition);
      }

      return localParameterConditionings;
    }

    template <typename T>
    arma::Mat<T> GallaghersGaussian101mePeaksFunction<T>::getRandomLocalParameterTranslations() const noexcept {
      arma::Mat<T> localParameterTranslations = arma::randu<arma::Mat<T>>(this->numberOfDimensions_, 101) * static_cast<T>(10.0L) - static_cast<T>(5.0L);
      localParameterTranslations.col(0) = static_cast<T>(0.8L) * localParameterTranslations.col(0);

      return localParameterTranslations;
    }

    template <typename T>
    T GallaghersGaussian101mePeaksFunction<T>::getSoftConstraintsValueImplementation(
        const arma::Col<T>& parameter) const noexcept {
      return this->getBoundConstraintsValue(parameter);
    }

    template <typename T>
    T GallaghersGaussian101mePeaksFunction<T>::getObjectiveValueImplementation(
        const arma::Col<T>& parameter) const noexcept {
      T maximalValue = std::numeric_limits<T>::lowest();
      for (std::size_t k = 0; k < 101; ++k) {
        const arma::Col<T>& locallyTranslatedParameter = parameter - localParameterTranslations_.col(k);
        maximalValue = std::max(maximalValue, weight_(k) * std::exp(static_cast<T>(-0.5L) / static_cast<T>(this->numberOfDimensions_) * arma::dot(locallyTranslatedParameter, rotationQ_.t() * arma::diagmat(localParameterConditionings_.col(k)) * rotationQ_ * locallyTranslatedParameter)));
      }

      return std::pow(this->getOscillatedValue(static_cast<T>(10.0L) - maximalValue), static_cast<T>(2.0L));
    }

    template <typename T>
    std::string GallaghersGaussian101mePeaksFunction<T>::toString() const noexcept {
      return "bbob_gallaghers_gaussian_101me_peaks_function";
    }
  }
}
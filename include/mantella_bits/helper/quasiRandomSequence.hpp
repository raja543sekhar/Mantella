#pragma once

// Armadillo
#include <armadillo>

namespace mant {
   arma::Mat<double> getHaltonSequence(
       const arma::Col<unsigned int>& base,
       const arma::Col<unsigned int>& seed,
       const unsigned int& numberOfColumms);

   arma::Col<double> getVanDerCorputSequence(
       const unsigned int& base,
       const unsigned int& seed,
       const unsigned int& numberOfColumms) noexcept;
}

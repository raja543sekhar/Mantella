#pragma once

// C++ standard library
#include <atomic>

namespace mant { 
  extern std::atomic<bool> cacheSamples; /* = true (default) */
  extern std::atomic<bool> recordSamples; /* = false (default) */
}

// MPI
#cmakedefine SUPPORT_MPI
#if defined(SUPPORT_MPI)
  #include <mpi.h>
#endif
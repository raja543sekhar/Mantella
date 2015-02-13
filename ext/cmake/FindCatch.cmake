find_path(CATCH_INCLUDE_DIRS catch.hpp
  PATHS "$ENV{ProgramFiles}/Catch")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Catch DEFAULT_MSG CATCH_INCLUDE_DIRS)

mark_as_advanced(CATCH_INCLUDE_DIRS)

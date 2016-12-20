#----------------------------------------------------------------
# Generated CMake target import file for configuration "".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "genericCpp" for configuration ""
set_property(TARGET genericCpp APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(genericCpp PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libgenericCpp.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS genericCpp )
list(APPEND _IMPORT_CHECK_FILES_FOR_genericCpp "${_IMPORT_PREFIX}/lib/libgenericCpp.a" )

# Import target "genericFor" for configuration ""
set_property(TARGET genericFor APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(genericFor PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "Fortran"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libgenericFor.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS genericFor )
list(APPEND _IMPORT_CHECK_FILES_FOR_genericFor "${_IMPORT_PREFIX}/lib/libgenericFor.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

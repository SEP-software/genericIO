# - Config file for the FooBar package
# It defines the following variables


####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was genericIOConfig.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

  INCLUDE(${CMAKE_CURRENT_LIST_DIR}/genericIOExports.cmake)



set_and_check(genericIO_DIRNAME_include "${PACKAGE_PREFIX_DIR}/include")
set(GENERIC_EXPORT_INC_DIRS )
set(GENERIC_EXPORT_LIB_DIRS )
set(GENERIC_EXPORT_LIBS )
FOREACH(inc ${GENERIC_EXPORT_INC_DIRS})
  INCLUDE_DIRECTORIES(${inc})
ENDFOREACH(inc)

set_target_properties(genericCpp PROPERTIES
IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
)
set_target_properties(genericFor PROPERTIES
IMPORTED_LINK_INTERFACE_LANGUAGES "Fortran"
)
FOREACH(libd ${GENERIC_EXPORT_LIB_DIRS})
  link_directories(${libd})
ENDFOREACH(libd)








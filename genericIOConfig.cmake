



check_required_components(genericIO)

if(NOT TARGET SEP:IO:genericCpp)
  include("${CMAKE_CURRENT_LIST_DIR}/genericIOTargets.cmake")
endif()

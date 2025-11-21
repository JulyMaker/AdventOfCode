#Keep directories structure for Visual Studio
function(assign_source_group)
      foreach(_file IN ITEMS ${ARGN})
      # Get the directory of the source file
      get_filename_component(_parentDir "${_file}" DIRECTORY)
      
      # Remove common directory prefix to make the group
      string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" _group "${_parentDir}")

      # Make sure we are using my and not ..
      string(REPLACE ".." "_myJuly" _group "${_group}")

      # Make sure we are using windows slashes
      string(REPLACE "/" "\\" _group "${_group}")

      source_group("${_group}" FILES "${_file}")
  endforeach()
endfunction(assign_source_group)
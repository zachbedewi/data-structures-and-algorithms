include(cmake/CPM.cmake)

function(myproject_setup_dependencies)
  if(NOT TARGET Catch2::Catch2WithMain)
    cpmaddpackage(
      NAME Catch2
      VERSION 3.12.0
      GITHUB_REPOSITORY "catchorg/Catch2"
      SYSTEM YES)
  endif()
endfunction()

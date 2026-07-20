add_library(variant variant.cpp)
target_link_libraries(variant PRIVATE myproject::myproject_options myproject::myproject_warnings)
target_include_directories(variant PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)

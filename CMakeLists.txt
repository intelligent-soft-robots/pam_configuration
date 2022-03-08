cmake_minimum_required(VERSION 3.10.2)
project(pam_configuration)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)
find_package(mpi_cmake_modules REQUIRED)
find_package(pybind11 REQUIRED)

# prepare to export all needed targets
set(all_targets)
set(all_target_exports)


###################################
# Configuration file installation #
###################################

# calling the "install" script, which copy all
# configuration files to either ~/.mpi-is or
# /opt/mpi-is (if called by root)
execute_process(COMMAND "bash"
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  INPUT_FILE install
  TIMEOUT 5
  RESULTS_VARIABLE install_results
  OUTPUT_VARIABLE install_stdout
  ERROR_VARIABLE install_stderr)
if(${install_results} EQUAL 0)
  message(STATUS "copied configuration files: ${install_stdout}")
else()
  message(FATAL_ERROR "failed to copy configuration files: ${install_stderr}")
endif()


###########
# Library #
###########

add_library(${PROJECT_NAME} SHARED
  src/pam_configuration.cpp)
target_include_directories(
  ${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
ament_export_interfaces(export_${PROJECT_NAME} HAS_LIBRARY_TARGET)
list(APPEND all_targets ${PROJECT_NAME})
list(APPEND all_target_exports export_${PROJECT_NAME})


###################
# Python wrappers #
###################

add_library(${PROJECT_NAME}_cpp_bindings MODULE srcpy/wrappers.cpp)
target_link_libraries(${PROJECT_NAME}_cpp_bindings PRIVATE pybind11::module)
target_link_libraries(${PROJECT_NAME}_cpp_bindings PRIVATE ${PYTHON_LIBRARIES})
target_link_libraries(${PROJECT_NAME}_cpp_bindings PRIVATE ${PROJECT_NAME})
set_target_properties(
  ${PROJECT_NAME}_cpp_bindings
  PROPERTIES PREFIX ""
             SUFFIX "${PYTHON_MODULE_EXTENSION}"
             OUTPUT_NAME ${PROJECT_NAME})
target_include_directories(
  ${PROJECT_NAME}_cpp_bindings
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
         $<INSTALL_INTERFACE:include> SYSTEM
  PUBLIC ${PYTHON_INCLUDE_DIRS})
get_python_install_dir(python_install_dir)
install(TARGETS ${PROJECT_NAME}_cpp_bindings DESTINATION ${python_install_dir})


######################
# Install and export #
######################

install(DIRECTORY include/ DESTINATION include)
install(
  TARGETS ${all_targets}
  EXPORT ${all_target_exports}
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES
  DESTINATION include)
ament_package()



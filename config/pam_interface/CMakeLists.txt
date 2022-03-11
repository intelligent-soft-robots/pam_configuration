cmake_minimum_required(VERSION 3.10.2)
project(pam_configuration)



#
# PAMY 1
#
get_filename_component(PAMY1_BITFILE_PATH pamy1/bitfile ABSOLUTE)
get_filename_component(PAMY1_JSON_CONFIG_DIR pamy1/config ABSOLUTE)
get_filename_component(PAMY2_JSON_CONFIG_DIR pamy2/config ABSOLUTE)
# installing files in /opt/mpi-is/ if exists
if (EXISTS "/opt/mpi-is")
  install(FILES
    "${PAMY1_BITFILE_PATH}/pam_robot.lvbitx"
    "${PAMY1_JSON_CONFIG_DIR}/pam.json"
    "${PAMY1_JSON_CONFIG_DIR}/pam_sim.json"
    DESTINATION /opt/mpi-is/pam_interface/pamy1)
  install(FILES
    "${PAMY2_JSON_CONFIG_DIR}/pam.json"
    DESTINATION /opt/mpi-is/pam_interface/pamy2)
  set(PAMY1_JSON_DEFAULT_CONFIG_FILE "/opt/mpi-is/pam_interface/pamy1/pam.json")
  set(PAMY2_JSON_DEFAULT_CONFIG_FILE "/opt/mpi-is/pam_interface/pamy2/pam.json")
  set(PAM_BITFILE "/opt/mpi-is/pam_interface/pamy1/pam_robot.lvbitx")
else()
  set(PAMY1_JSON_DEFAULT_CONFIG_FILE "${CMAKE_INSTALL_PREFIX}/opt/mpi-is/pam_interface/pamy1/pam.json")
  set(PAMY2_JSON_DEFAULT_CONFIG_FILE "${CMAKE_INSTALL_PREFIX}/opt/mpi-is/pam_interface/pamy2/pam.json")
  set(PAM_BITFILE "${CMAKE_INSTALL_PREFIX}/opt/mpi-is/pam_interface/pamy1/pam_robot.lvbitx")
endif()
# also installing in the workspace/install folder  
install(FILES
  "${PAMY1_BITFILE_PATH}/pam_robot.lvbitx"
  "${PAMY1_JSON_CONFIG_DIR}/pam.json"
  DESTINATION ${CMAKE_INSTALL_PREFIX}/opt/mpi-is/pam_interface/pamy1)
install(FILES
  "${PAMY2_JSON_CONFIG_DIR}/pam.json"
  DESTINATION ${CMAKE_INSTALL_PREFIX}/opt/mpi-is/pam_interface/pamy2)


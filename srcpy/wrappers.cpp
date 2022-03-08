#include <pybind11/pybind11.h>
#include "pam_configuration/pam_configuration.hpp"

using namespace pam_configuration;

PYBIND11_MODULE(pam_configuration, m)
{
    // TODO: currently converting std::filesystem::path to string
    // but more recent version of pybind11 would convert automatically
    // to pathlib.Path

    pybind11::class_<PamConfigurationNotFoundError>(
        m, "PamConfigurationNotFoundError")
        .def("__str__", &PamConfigurationNotFoundError::what);

    m.def(
        "get_user_path",
        []() { return get_user_path().string(); },
        "returns the path (as string) to the expected user configuration "
        "folder, i.e. ~/.mpi-is/pam");

    m.def(
        "user_path_exists",
        []() { return user_path_exists(); },
        "returns true if the user configuration folder (i.e. ~/.mpi-is/pam) "
        "exists");

    m.def(
        "get_global_path",
        []() { return get_global_path().string(); },
        "returns the path (as string) to the expected global configuration "
        "folder, i.e. /opt/mpi-is/pam");

    m.def(
        "get_path",
        []() { return get_path().string(); },
        "returns the path (as string) to the user config folder (~/.mpi-is/pam) if "
        "it exists, otherwise to the global "
        "config folder (/opt/mpi-is/pam). If neither exists, raise a "
        "PamConfigurationNotFoundError");
}

#pragma once

#include <unistd.h>
#include <filesystem>
#include <string>

#define PAM_GLOBAL_CONFIG "/opt/mpi-is/pam"
#define PAM_USER_CONFIG ".mpi-is/pam"

namespace pam_configuration
{
/**
 * To be thrown to indicate no configuration folder
 * could be found.
 */
class PamConfigurationNotFoundError : public std::runtime_error
{
public:
    PamConfigurationNotFoundError(std::string error);
    char const* what() const throw();

private:
    std::string message_;
};

/**
 * Return the expected path to the user configuration
 * folder, i.e. ~/.mpi-is/pam
 * Raise a runtime_error if there is no
 * home directory (according to the $HOME
 * environment variable.
 */
std::filesystem::path get_user_path();

/**
 * Return true if there is a user configuration
 * path (i.e. ~/.mpi-is/pam exists and is a folder),
 * false otherwise.
 */
bool user_path_exists();

/**
 * Return the expected path of a global
 * configuration folder, i.e. /opt/mpi-is/pam
 */
std::filesystem::path get_global_path();

/**
 * Returns the path to a user configuration
 * folder (if it exists), otherwise the path
 * to a global configuration server.
 * Raise a PamConfigurationNotFoundError if
 * neither a user nor a global folder exist.
 */
std::filesystem::path get_path();

}  // namespace pam_configuration

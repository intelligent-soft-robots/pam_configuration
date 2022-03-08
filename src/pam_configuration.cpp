#include "pam_configuration/pam_configuration.hpp"

namespace pam_configuration
{
PamConfigurationNotFoundError::PamConfigurationNotFoundError(std::string error)
    : std::runtime_error(error.c_str())
{
}

char const* PamConfigurationNotFoundError::what() const throw()
{
    return exception::what();
}

std::filesystem::path get_user_path()
{
    const char* home = getenv("HOME");
    if (home == NULL)
    {
        throw std::runtime_error("No home directory found");
    }
    std::string homedir(home);
    std::string subdir(PAM_USER_CONFIG);
    std::filesystem::path user_config(homedir);
    user_config /= subdir;
    return user_config;
}

bool user_path_exists()
{
    {
        std::filesystem::path p = get_user_path();
        if (std::filesystem::is_directory(p))
        {
            return true;
        }
    }
    return false;
}

std::filesystem::path get_global_path()
{
    std::string global_path_str(PAM_GLOBAL_CONFIG);
    std::filesystem::path global_path(global_path_str);
    return global_path;
}

std::filesystem::path get_path()
{
    if (user_path_exists())
    {
        return get_user_path().string();
    }
    std::filesystem::path global_path = get_global_path();
    if (std::filesystem::is_directory(global_path))
    {
        return global_path.string();
    }
    std::string error =
        std::string("Failed to find pam configuration folder ") +
        std::string("in either a folder ") + std::string(PAM_USER_CONFIG) +
        std::string(" in the home user directory ") + std::string("or in ") +
        global_path.string();
    throw PamConfigurationNotFoundError(error);
}

}  // namespace pam_configuration

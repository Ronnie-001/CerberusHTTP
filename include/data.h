#ifndef DATA_H
#define DATA_H

#include <string>
#include <nlohmann/json.hpp>

namespace cerberus
{

// Represents each JSON entry.
struct User
{
    std::string username;
    std::string password;
};

class Data
{
public:
    Data(std::string_view file_path);
    
    // Note: made return type void for now; subject to change.
    void addUser(const cerberus::User& user);

    void updateUser();

    void deleteUser();

    void toJson(nlohmann::json& json, const User& user);

    void fromJson(const nlohmann::json& json, User& user); 

private:
    std::string _file_path;
};
}

#endif // !DATA_H

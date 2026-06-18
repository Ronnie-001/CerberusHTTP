#ifndef DATA_H
#define DATA_H

#include <mutex>
#include <string>
#include <unordered_map>

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
    Data();

    // Methods updating the map.
    void addUser(const cerberus::User& user, const std::string& file_path);

    void updateUser();

    void deleteUser();

    cerberus::User getUser();

    void toJson(nlohmann::json& json, const User& user);

    void fromJson(const nlohmann::json& json, User& user); 

private:
    std::unordered_map<std::string, cerberus::User> _user_map;
    std::unique_lock<std::mutex> _map_mutex;

    std::unique_lock<std::mutex> _file_mutex;
};
}

#endif // !DATA_H

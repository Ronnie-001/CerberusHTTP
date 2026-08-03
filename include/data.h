#ifndef DATA_H
#define DATA_H

#include <mutex>
#include <string>
#include <unordered_map>
#include <cstdint>

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
    
    // Interactions with the user_map.
    cerberus::User getUser(const std::uint64_t id);
    void updateUser(const std::uint64_t id, const cerberus::User user);
    void addUser(const std::uint64_t id, const cerberus::User user);
    void deleteUser(const std::uint64_t id);

    void addToJsonFile(const cerberus::User& user, const std::string& file_path);
    void updateJsonFile(const cerberus::User& user, const std::string& file_path);
    void removeFromJsonFile(const cerberus::User& user, const std::string& file_path);
    
    void toJson(nlohmann::json& json, const User& user);
    void fromJson(const nlohmann::json& json, User& user); 

private:
    std::unordered_map<std::uint64_t, cerberus::User> _user_map;
    std::unique_lock<std::mutex> _map_mutex;

    std::unique_lock<std::mutex> _file_mutex;
};
}

#endif // !DATA_H

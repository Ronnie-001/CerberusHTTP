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
    
    // GET 
    cerberus::User getUser();
    // PUT 
    void updateUser();
    // POST 
    void addUser(const cerberus::User& user, const std::string& file_path);
    // DELETE
    void deleteUser();

    void addToJsonFile();
    void updateJsonFile();
    void removeFromJsonFile();

    void toJson(nlohmann::json& json, const User& user);
    void fromJson(const nlohmann::json& json, User& user); 

private:
    std::unordered_map<std::string, cerberus::User> _user_map;
    std::unique_lock<std::mutex> _map_mutex;

    std::unique_lock<std::mutex> _file_mutex;
};
}

#endif // !DATA_H

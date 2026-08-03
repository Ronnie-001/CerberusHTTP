#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

#include "data.h"

cerberus::Data::Data() {}

cerberus::User cerberus::Data::getUser(const std::uint64_t id) 
{
    return _user_map[id];    
}

void cerberus::Data::updateUser(const std::uint64_t id, const cerberus::User user)
{
    _user_map[id] = user;
}

void cerberus::Data::addUser(const std::uint64_t id, const cerberus::User user) 
{
    _user_map[id] = user; 
}

void cerberus::Data::deleteUser(const std::uint64_t id)
{
    _user_map.erase(id);     
}

void cerberus::Data::addToJsonFile(const cerberus::User& user, const std::string& file_path) 
{
    nlohmann::json user_json;
    toJson(user_json, user);

    // Create the json array
    nlohmann::json array = nlohmann::json::array();
    array.push_back(user_json);
    
    // Read the data from the file
    nlohmann::json file_data;
    std::ifstream infile(file_path); // Takes in the relative file path
    if (infile.is_open()) {
        infile >> file_data; 
        infile.close();
    } else {
       file_data["users"] = nlohmann::json::array(); 
    }

    file_data["users"].push_back(user_json);
    
    std::ofstream outfile(file_path);
    if (outfile.is_open()) {
        outfile << file_data.dump(4) << '\n';
        outfile.close(); 
    } else {
        std::cerr << "[ERROR] Failed to write user to file." << '\n';
    }
}

void cerberus::Data::toJson(nlohmann::json& json, const User& user) 
{
    json = nlohmann::json{ {"username", user.username}, {"password", user.password} };    


}

void cerberus::Data::fromJson(const nlohmann::json& json, User& user) 
{
    json.at("username").get_to(user.username);
    json.at("password").get_to(user.password);
}

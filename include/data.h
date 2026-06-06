#ifndef DATA_H
#define DATA_H

#include <string>

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
    void addUser();

    void updateUser();

    void deleteUser();

private:
    std::string _file_path;
};
}

#endif // !DATA_H

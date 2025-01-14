#pragma once
#include <pqxx/pqxx>
#include <iostream>
#include <string>
constexpr char* connectionParams = "dbname = app user = user password = postgres \ hostaddr = 127.0.0.1 port = 5432";
struct Video{
    int videoId;
    std::string title;
    std::string description;
};
struct User{
    std::string userName;
    std::string pictureUrl;
    int subs;
    int userID;
};
namespace Repo{
    
    void connectToDatabase();
    //Video getVideoFromDatabase();
    void insertUserIntoDatabase(std::string pUserName,std::string pictureUrl);
};


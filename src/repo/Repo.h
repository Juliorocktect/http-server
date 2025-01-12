#pragma once
#include <pqxx/pqxx>
#include <iostream>
#include <string>

void connectToDatabase();

struct Video{
    int videoId;
    std::string title;
    std::string description;
};

Video getVideoFromDatabase();
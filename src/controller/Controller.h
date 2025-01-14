#pragma once
#include "../http/HTTP.h"
#include <map>
#include <sstream>
#include <string>
#include <fstream>
#include "../httpHandler/Handler.h"
#include "../repo/Repo.h"

std::string buildJson();
void linkFunctions(PathListener *lis);
HTTP::Response homeResponse(std::map<std::string, std::string> &m);
std::string jsonResponse(std::map<std::string, std::string> &m);
HTTP::Response processParams(std::map<std::string, std::string> &m);
HTTP::Response addUser(std::map<std::string, std::string> &m);
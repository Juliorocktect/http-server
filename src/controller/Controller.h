#pragma once
#include "../http/HTTP.h"
#include <map>
#include <sstream>
#include <string>
#include <fstream>
#include "../httpHandler/Handler.h"

std::string buildJson();
void linkFunctions(PathListener *lis);
std::string homeResponse(std::map<std::string, std::string> &m);
std::string jsonResponse(std::map<std::string, std::string> &m);
std::string processParams(std::map<std::string, std::string> &m);
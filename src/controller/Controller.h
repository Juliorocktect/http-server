#pragma once
#include "../http/HTTP.h"
#include <map>
#include <sstream>
#include <string>
#include <fstream>
#include "../httpHandler/Handler.h"

void linkFunctions(PathListener *lis);
std::string homeResponse(std::map<std::string, std::string> &m);
#include "HTTP.h"

namespace HTTP
{
    HTTP::Date::Date() {}
    Date::Date(HTTP::WeekDay pWeekDay, unsigned int pDay, Month pMonth, unsigned int pYear)
    {
        weekDay = pWeekDay;
        day = pDay;
        month = pMonth;
        year = pYear;
    }
    Date::~Date() {}
    HeaderRequest::HeaderRequest()
    {
        //muss man die atrribute initialisieren?
    }
    Method HTTP::HeaderRequest::getMethodByString(std::string methodStr)
    {
        if (methodStr == "GET")
            return HTTP::Method::GET;
        if (methodStr == "POST")
            return HTTP::Method::POST;
        if (methodStr == "DELETE")
            return HTTP::Method::DELETE;
        if (methodStr == "PUT")
            return HTTP::Method::PUT;
    }
    void HTTP::HeaderRequest::parseVector(std::vector<std::string> &httpRequest)
    {
        for (int i = 1; i < httpRequest.size(); i++)
        {
            std::string headerStr = httpRequest[i].substr(0, httpRequest[i].find(':'));
            std::string::size_type beginHeaderStr = httpRequest[i].find(headerStr);
            std::string headerContent = httpRequest[i].erase(beginHeaderStr, headerStr.length() + 2);
            if (headerStr == ("Host"))
            {
                host = headerContent;
            }
            if (headerStr == ("User-Agent"))
            {
                userAgent = headerContent;
            }
            if (headerStr == "Accept")
            {
                accept = headerContent;
            }
            if (headerStr == ("Accept-Language"))
            {
                acceptLanguage = headerContent;
            }
            if (headerStr == ("Accept-Encoding"))
            {
                acceptEncoding = headerContent;
            }
            if (headerStr == ("Referer"))
            {
                referer = headerContent;
            }
            if (headerStr == ("Connection"))
            {
                connection = headerContent;
            }
        }
    }
    void HTTP::HeaderRequest::processRequest(std::string data)
    {
        std::istringstream issFromData(data);
        std::string line;
        std::vector<std::string> lines; //read out lines and store in vector

        while (getline(issFromData, line))
        {
            lines.push_back(line);
        }

        //parse first line
        std::string paramsStr = lines[0].substr(0, lines[0].find('?'));
        this->params = paramsStr;
        std::string methodStr = lines[0].substr(0, lines[0].find(' '));
        std::string::size_type begin = lines[0].find(methodStr);
        if (begin != std::string::npos)
        {
            lines[0].erase(begin, methodStr.length() + 1); //save the params and not only the path
        }
        method = getMethodByString(methodStr);
        path = lines[0].substr(0, lines[0].find(' '));
        std::cout << path;
        this->parseVector(lines);
    }
    void HeaderRequest::printFile()
    {
        std::cout << host << "\n"
                  << path << "\n"
                  << userAgent << "\n"
                  << accept << "\n"
                  << acceptLanguage << "\n"
                  << acceptEncoding << "\n"
                  << referer << "\n"
                  << connection << "\n";
    }
};
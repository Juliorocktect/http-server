#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
namespace HTTP
{
    enum Method // TODO: muss mir da was einfallen lassen
    {
        GET,
        POST,
        PUT,
        DELETE
    };
    enum WeekDay
    {
        Mon,
        Tue,
        Wen,
        Thu,
        Fri,
        Sat,
        Sun
    };
    enum Month
    {
        Jan,
        Feb,
        Mar,
        Apr,
        May,
        Jun,
        Jul,
        Aug,
        Sep,
        Okt,
        Nov,
        Dec
    };
    class Date
    {
    public:
        WeekDay weekDay;
        unsigned int day;
        Month month;
        unsigned int year;
        Date();
        Date(WeekDay pWeekDay, unsigned int pDay, Month pMonth, unsigned int year);
        //current daytime
        ~Date();
        Date(std::string);
    };
    class HeaderRequest
    {
    private:
        Method getMethodByString(std::string methdStr);
        void parseVector(std::vector<std::string> &httpRequest);

    public:
        std::string host;
        Method method;
        std::string path;
        std::string userAgent;
        std::string accept;
        std::string acceptLanguage;
        std::string acceptEncoding;
        std::string referer;
        std::string connection;
        HeaderRequest();
        void processRequest(std::string fileLocation);
        void printFile();
        //TODO: body content
    };
    class Response
    {
    public:
        int statusCode;
        Date date;
        std::string contentEncoding;
        std::string contentType;
        std::string Server;
        unsigned int contentLength;
        Response();
        std::string buildResponse();
    };
}

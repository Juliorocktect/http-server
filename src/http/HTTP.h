#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <ctime>
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
        // current daytime
        ~Date();
        Date(std::string);
        std::string getCurrentDateTime();
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
        std::string params;
        std::string userAgent;
        std::string accept;
        std::string acceptLanguage;
        std::string acceptEncoding;
        std::string referer;
        std::string connection;
        HeaderRequest();
        void processRequest(std::string fileLocation);
        void printFile();
        // TODO: body content
    };
    class Codes
    {
    public:
        const char *OK = "OK 200";
        const char *BAD_REQUEST = "Bad Request 400";
    };
    class ContentTypes
    {
    };
    class Response
    {
    public:
        // last modified?
        const char *statusCode;
        Date date;
        std::string contentEncoding;
        std::string contentType;
        const std::string SERVER = "juli";
        unsigned int contentLength;
        std::string connection;
        std::string body;
        Response();
        std::string buildResponse();
        std::string badRequest();
        std::string notFound();
    };
}

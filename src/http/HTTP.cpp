#include "HTTP.h"

namespace HTTP{
     Date::Date() {}
    Date::Date(WeekDay pWeekDay, unsigned int pDay, Month pMonth, unsigned int pYear)
    {
        weekDay = pWeekDay;
        day = pDay;
        month = pMonth;
        year = pYear;
    }
    HTTP::Date::~Date() {}
    HTTP::HeaderRequest::HeaderRequest()
    {
        // muss man die atrribute initialisieren?
    }
    HTTP::Method HTTP::HeaderRequest::getMethodByString(std::string methodStr)
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
        std::vector<std::string> lines; // read out lines and store in vector

        while (getline(issFromData, line))
        {
            lines.push_back(line);
        }

        // parse first line
        std::string paramsStr = lines[0].substr(0, lines[0].find('?'));
        this->params = paramsStr;
        std::string methodStr = lines[0].substr(0, lines[0].find(' '));
        std::string::size_type begin = lines[0].find(methodStr);
        if (begin != std::string::npos)
        {
            lines[0].erase(begin, methodStr.length() + 1); // save the params and not only the path
        }
        method = getMethodByString(methodStr);
        path = lines[0].substr(0, lines[0].find(' '));
        this->parseVector(lines);
    }
    
    void HTTP::HeaderRequest::printFile()
    {
        std::cout << "[Host]\t" << host << "\n"
                  << "[Path]\t" << path << "\n"
                  << "[userAgent]\t" << userAgent << "\n"
                  << "[accept]\t" << accept << "\n"
                  << "[accept-language]\t" << acceptLanguage << "\n"
                  << "[accept-encoding]\t" << acceptEncoding << "\n"
                  << "[referer]\t" << referer << "\n"
                  << "[connection]\t" << connection << "\n";
    }
    HTTP::Response::Response() {}
    std::string HTTP::Response::buildResponse()
    {
        std::string res;
        res.append(std::string("HTTP/1.1 "));
        res.append(statusCode + std::string("\n"));
        res.append("Date: xxx" + std::string("\n"));
        res.append("Server: " + this->SERVER + std::string("\n"));
        res.append("Content-Length: " + std::to_string(contentLength) + std::string("\n"));
        res += "Content-Type: " + this->contentType + std::string("\n");
        res += "Connection: " + this->connection + std::string("\n");
        if (this->connection.compare("keep-alive") == 0)
        {
            std::string keepConnection;
            keepConnection.append("Keep-Alive: timeout=");
            keepConnection.append(std::to_string(keepALiveTimeout));
            keepConnection.append(",max=" +  std::to_string(keepAliveMax));
            res.append(keepConnection);
            res.append(std::string("\n"));
        }
        res.append(std::string("\n"));
        res.append(body);
        return res;
    }
    std::string HTTP::Response::badRequest()
    {
        std::string res;
        res.append(std::string("HTTP/1.1 "));
        res.append(std::string("400 Bad Request\n"));
        res.append("Date: xxx" + std::string("\n"));
        res.append("Server: " + this->SERVER + std::string("\n"));
        res += "Connection: " + std::string("close\n");
        res.append(std::string("\n"));
        res.append(body);
        return res;
    }
    std::string Response::notFound()
    {
        std::string res;
        res.append(std::string("HTTP/1.1 "));
        res.append(std::string("404 Not Found\n"));
        res.append("Date: xxx" + std::string("\n"));
        res.append("Server: " + this->SERVER + std::string("\n"));
        res += "Connection: " + std::string("close\n");
        res.append(std::string("\n"));
        res.append(body);
        return res;
    }

};
   
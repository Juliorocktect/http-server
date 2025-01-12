#include "Repo.h" 


void connectToDatabase()
{
    try
    {
        pqxx::connection c("dbname = app user = user password = postgres \ hostaddr = 127.0.0.1 port = 5432");
        if (c.is_open()){
            std::cout << "Connected" << std::endl;
        } else {
            std::cout << "Couldn't connect to Database\n";
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

Video getVideoFromDatabase()
{
    Video vid;
    try
    {
        
        pqxx::connection connection("dbname = app user = user password = postgres \ hostaddr = 127.0.0.1 port = 5432");
        if (connection.is_open()){
            std::cout << "Connected" << std::endl;
        } else {
            std::cout << "Couldn't connect to Database\n";
            return vid;
        }

        pqxx::work transaction(connection);

        pqxx::result result = transaction.exec("SELECT * FROM videos;");

        vid.videoId  = result[0]["videoid"].as<int>();
        vid.title = result[0]["title"].as<std::string>();
        vid.description = result[0]["description"].as<std::string>();

        transaction.commit();
        connection.close();
        return vid;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return vid;
}
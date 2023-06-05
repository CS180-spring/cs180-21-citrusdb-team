#include <crow.h>
#include "/home/ec2-user/server/backend/databaseEngine.hpp"
int main()
{
    crow::SimpleApp app;
    DatabaseEngine dbEngine;

    // Route for creating a new user
    CROW_ROUTE(app, "/create")
        .methods("POST"_method)
        ([&dbEngine](const crow::request& req) {
            // Extract data from the request body
            std::string username = req.body["username"].s();
            std::string email = req.body["email"].s();
            std::string p
            assword = req.body["password"].s();

            // Call the createUser function of DatabaseEngine
            int result = dbEngine.createUser(username, email, password);

            // Return the result as a response
            crow::json::wvalue response;
            response["result"] = result;
            return response;
        });

    // Route for checking login credentials
    CROW_ROUTE(app, "/login")
        .methods("POST"_method)
        ([&dbEngine](const crow::request& req) {
            // Extract data from the request body
            std::string username = req.body["username"].s();
            std::string password = req.body["password"].s();

            // Call the loginCheck function of DatabaseEngine
            bool isValid = dbEngine.loginCheck(username, password);

            // Return the result as a response
            crow::json::wvalue response;
            response["isValid"] = isValid;
            return response;
        });

    // Start the server
    app.port(80).multithreaded().run();

    return 0;
}

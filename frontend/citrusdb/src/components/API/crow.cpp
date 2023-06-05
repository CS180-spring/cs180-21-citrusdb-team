#include <crow.h>
#include "../../../../../server/backend/databaseEngine.hpp"
#include "../../../../../nlohmann/json.hpp"
int main()
{
    crow::SimpleApp app;
    DatabaseEngine dbEngine;

    // Route for creating a new user
    CROW_ROUTE(app, "/create")
    .methods("POST"_method)
    ([&dbEngine](const crow::request& req) {
        // Parse the request body as JSON
        json body;
        try {
            body = json::parse(req.body);
        } catch (const json::parse_error& e) {
            // Return an error response if the body is not valid JSON
            return crow::response(400, "Invalid JSON");
        }

        // Extract data from the JSON object
        std::string username = body["username"].get<std::string>();
        std::string email = body["email"].get<std::string>();
        std::string password = body["password"].get<std::string>();

        // Call the createUser function of DatabaseEngine
        int result = dbEngine.createUser(username, email, password);

        // Create a response with the serialized JSON body
        crow::response response;
        response.body = json({{"result", result}}).dump();
        response.set_header("Content-Type", "application/json");

        return response;
    });

    // // Route for checking login credentials
    // CROW_ROUTE(app, "/login")
    //     .methods("POST"_method)
    //     ([&dbEngine](const crow::request& req) {
    //         // Extract data from the request body
    //         std::string username = req.body["username"].s();
    //         std::string password = req.body["password"].s();

    //         // Call the loginCheck function of DatabaseEngine
    //         bool isValid = dbEngine.loginCheck(username, password);

    //         // Return the result as a response
    //         crow::json::wvalue response;
    //         response["isValid"] = isValid;
    //         return response;
    //     });

    // Start the server
    app.port(80).multithreaded().run();

    return 0;
}

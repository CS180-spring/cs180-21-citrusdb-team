#include "crow.h"
#include "../../../../../backend/databaseEngine.hpp"
#include "../../../../../backend/nlohmann/json.hpp"

using json = nlohmann::json;

int main() {
    crow::SimpleApp app;
    DatabaseEngine dbEngine;

    CROW_ROUTE(app, "/createUser")
    .methods("POST"_method)
    ([&dbEngine](const crow::request& req) {
        // Parse the request body as JSON
        json body;
        try {
            body = json::parse(req.body);
        } catch (const json::parse_error& error) {
            return crow::response(400, "Invalid JSON");
        }

        // Extract data from the JSON object
        std::string username = body["username"].get<std::string>();
        std::string email = body["email"].get<std::string>();
        std::string password = body["password"].get<std::string>();

        // Call the createUser function of DatabaseEngine
        int result = dbEngine.createUser(username, email, password);

        /* if needed:
        // Create a response with the serialized JSON body
        crow::response response;
        response.body = json({{"result", result}}).dump();
        response.set_header("Content-Type", "application/json");
        */

        return crow::response(200, std::to_string(result));
    });

}


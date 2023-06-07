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

    CROW_ROUTE(app, "/loginCheck")
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
        std::string password = body["password"].get<std::string>();

        // Call the loginCheck function of DatabaseEngine
        bool result = dbEngine.loginCheck(username, password);

        return crow::response(200, result ? "true" : "false");
    });


    CROW_ROUTE(app, "/resetPassword")
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

        // Call the resetPassword function of DatabaseEngine
        bool result = dbEngine.resetPassword(username, email);

        return crow::response(200, result ? "true" : "false");
    });

    CROW_ROUTE(app, "/updatePassword")
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
        std::string newPassword = body["newPassword"].get<std::string>();

        // Call the updatePassword function of DatabaseEngine
        bool result = dbEngine.updatePassword(username, newPassword);

        return crow::response(200, result ? "true" : "false");
    });


    CROW_ROUTE(app, "/deleteUser")
    .methods("POST"_method)
    ([&dbEngine](const crow::request& req) {
        json body;
        try {
            body = json::parse(req.body);
        } catch (const json::parse_error& error) {
            return crow::response(400, "Invalid JSON");
        }

        std::string username = body["username"].get<std::string>();

        bool result = dbEngine.deleteUser(username);

        return crow::response(200, result ? "true" : "false");
    });


    CROW_ROUTE(app, "/createCollection")
    .methods("POST"_method)
    ([&dbEngine](const crow::request& req) {
        json body;
        try {
            body = json::parse(req.body);
        } catch (const json::parse_error& error) {
            return crow::response(400, "Invalid JSON");
        }

        std::string username = body["username"].get<std::string>();
        std::string collection = body["collection"].get<std::string>();
        std::string labels = body["labels"].get<std::string>();

        int result = dbEngine.createCollection(username, collection, labels);

        return crow::response(200, std::to_string(result));
    });

    CROW_ROUTE(app, "/deleteCollection")
    .methods("POST"_method)
    ([&dbEngine](const crow::request& req) {
        json body;
        try {
            body = json::parse(req.body);
        } catch (const json::parse_error& error) {
            return crow::response(400, "Invalid JSON");
        }

        std::string username = body["username"].get<std::string>();
        std::string collection = body["collection"].get<std::string>();

        int result = dbEngine.deleteCollection(username, collection);

        return crow::response(200, std::to_string(result));
    });

    CROW_ROUTE(app, "/renameCollection")
    .methods("POST"_method)
    ([&dbEngine](const crow::request& req) {
        json body;
        try {
            body = json::parse(req.body);
        } catch (const json::parse_error& error) {
            return crow::response(400, "Invalid JSON");
        }

        std::string username = body["username"].get<std::string>();
        std::string oldName = body["oldName"].get<std::string>();
        std::string newName = body["newName"].get<std::string>();

        int result = dbEngine.renameCollection(username, oldName, newName);

        return crow::response(200, std::to_string(result));
    });

    CROW_ROUTE(app, "/getCollection")
    .methods("POST"_method)
    ([&dbEngine](const crow::request& req) {
        json body;
        try {
            body = json::parse(req.body);
        } catch (const json::parse_error& error) {
            return crow::response(400, "Invalid JSON");
        }

        std::string username = body["username"].get<std::string>();
        std::string collection = body["collection"].get<std::string>();

        Collection* result = dbEngine.getCollection(username, collection);

        if (result == nullptr) {
            return crow::response(404, "Collection not found");
        } else {
            return crow::response(200);
        }
    });

    CROW_ROUTE(app, "/getCollections")
    .methods("POST"_method)
    ([&dbEngine](const crow::request& req) {
        json body;
        try {
            body = json::parse(req.body);
        } catch (const json::parse_error& error) {
            return crow::response(400, "Invalid JSON");
        }

        std::string username = body["username"].get<std::string>();

        std::unordered_map<std::string, Collection>* result = dbEngine.getCollections(username);

        if (result == nullptr) {
            return crow::response(404, "User not found");
        } else {
            return crow::response(200);
        }
    });

    CROW_ROUTE(app, "/createDocument")
    .methods("POST"_method)
    ([&dbEngine](const crow::request& req) {
        json body;
        try {
            body = json::parse(req.body);
        } catch (const json::parse_error& error) {
            return crow::response(400, "Invalid JSON");
        }

        std::string username = body["username"].get<std::string>();
        std::string collection = body["collection"].get<std::string>();
        std::string document = body["document"].get<std::string>();
        json object = body["object"];

        int result = dbEngine.createDocument(username, collection, document, object);

        return crow::response(200, std::to_string(result));
    });

    CROW_ROUTE(app, "/deleteDocument")
    .methods("POST"_method)
    ([&dbEngine](const crow::request& req) {
        json body;
        try {
            body = json::parse(req.body);
        } catch (const json::parse_error& error) {
            return crow::response(400, "Invalid JSON");
        }

        std::string username = body["username"].get<std::string>();
        std::string collection = body["collection"].get<std::string>();
        std::string document = body["document"].get<std::string>();

        int result = dbEngine.deleteDocument(username, collection, document);

        return crow::response(200, std::to_string(result));
    });

    CROW_ROUTE(app, "/renameDocument")
    .methods("POST"_method)
    ([&dbEngine](const crow::request& req) {
        json body;
        try {
            body = json::parse(req.body);
        } catch (const json::parse_error& error) {
            return crow::response(400, "Invalid JSON");
        }

        std::string username = body["username"].get<std::string>();
        std::string collection = body["collection"].get<std::string>();
        std::string oldDoc = body["oldDoc"].get<std::string>();
        std::string newDoc = body["newDoc"].get<std::string>();

        int result = dbEngine.renameDocument(username, collection, oldDoc, newDoc);

        return crow::response(200, std::to_string(result));
    });

    CROW_ROUTE(app, "/replaceDocument")
    .methods("POST"_method)
    ([&dbEngine](const crow::request& req) {
        json body;
        try {
            body = json::parse(req.body);
        } catch (const json::parse_error& error) {
            return crow::response(400, "Invalid JSON");
        }

        std::string username = body["username"].get<std::string>();
        std::string collection = body["collection"].get<std::string>();
        std::string document = body["document"].get<std::string>();
        json object = body["object"];

        int result = dbEngine.replaceDocument(username, collection, document, object);

        return crow::response(200, std::to_string(result));
    });

    CROW_ROUTE(app, "/updateDocument")
    .methods("POST"_method)
    ([&dbEngine](const crow::request& req) {
        json body;
        try {
            body = json::parse(req.body);
        } catch (const json::parse_error& error) {
            return crow::response(400, "Invalid JSON");
        }

        std::string username = body["username"].get<std::string>();
        std::string collection = body["collection"].get<std::string>();
        std::string document = body["document"].get<std::string>();
        json object = body["object"];

        // int result = dbEngine.updateDocument(username, collection, document, object); 
        // waiting on backend fix

        return crow::response(200, std::to_string(result));
    });






}




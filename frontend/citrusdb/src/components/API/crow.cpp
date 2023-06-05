#include <crow.h>
#include "../../../../../backend/databaseEngine.hpp"
#include "../../../../../nlohmann/json.hpp"

void handleRequest(const crow::request& req, crow::response& res) {
    std::cout << "Received " << crow::method_name(req.method) << " request to " << req.url << std::endl;
    
    // Check if the request method is POST
    if (req.method == crow::HTTPMethod::POST) {
        res.code = 200;
        res.write("test");
    }
    else {
        // Set the response status code to 405 (Method Not Allowed)
        res.code = 405;
        res.write("Only POST requests are allowed for this resource!");
    }
    
    // Send the response
    res.end();
}


int main() {
    // Create a Crow server instance
    crow::SimpleApp app;
    
    // Define the route and bind it to the handleRequest function
    CROW_ROUTE(app, "/")
        .methods(crow::HTTPMethod::POST, crow::HTTPMethod::GET)(handleRequest);
    
    // Start the server on port 8080
    app.port(80).multithreaded().run();
    
    return 0;
}


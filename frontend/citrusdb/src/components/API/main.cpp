// To Compile
// g++ main.cpp -I/home/linuxbrew/.linuxbrew/opt/asio/include -L/home/linuxbrew/.linuxbrew/lib -lboost_system

#include "crow.h"

using namespace std;

int main() {
    crow::SimpleApp app; 

    
    CROW_ROUTE(app, "/")([](){
        return "Hello world";
    });

    //set the port, set the app to run on multiple threads, and run the app
    cout << "Listening on port 8080;" << endl;
    app.port(8080).multithreaded().run();
    return 0;
}
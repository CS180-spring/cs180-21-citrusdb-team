#include "backend/databaseEngine.hpp"
#include <iostream>

int main(){
    DatabaseEngine dbe;
    dbe.createUser("eve123", "eves@dropper.com", "password123");
    dbe.createCollection("eve123", "myCollection", "Month\nDay\nYear\n_id\n_originFile");
    json date;
    date["id"]["Month"] = "Jan";
    date["id"]["Day"] = "12";
    date["id"]["Year"] = "1999";
    date["id"]["_id"] = "id";
    date["id"]["_originFile"] = "visits";
    dbe.createDocument("eve123", "myCollection", "visits", date);
    json date2;
    date2["Month"] = "Feb";
    date2["Day"] = "25";
    date2["Year"] = "2005";
    date2["_id"] = "unique";
    date2["_originFile"] = "visits";
    dbe.createObject("eve123", "myCollection", "visits", date2);
    dbe.deleteObject("eve123", "myCollection", "visits", "id");
    
    return 0;
}
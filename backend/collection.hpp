#ifndef COLLECTION_HPP
#define COLLECTION_HPP
#include <string>
#include <vector>
#include "document.hpp"
using namespace std;

class Collection {
public:
    Collection();
    
    // CRUD
    void createDocument();
    void deleteDocument();
    void renameDocument();
    void replaceDocument();
    string getDocument();

    vector<string> getDocumentIDs();

private:
    vector<Document> documents;
};
#endif
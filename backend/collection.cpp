#include "collection.hpp"

Collection::Collection(std::string filepath, std::string collectionName) : collectionName(collectionName)
{
    std::string metaPath = filepath + "/" + collectionName + "/_meta.json"; // metaPath = ./database/[username]/[collectionName]/_meta.json
    std::ifstream fin(metaPath);

    json content = json::parse(fin);
    json::iterator i = content.begin();
    for (i++; i != content.end(); i++)
    {
        (*this->getDocuments()).emplace(i.value(), Document(i.value()));
    }
}

Collection::Collection(std::string filepath, std::string collectionName, std::string templateVariables) : collectionName(collectionName)
{
    json metaContent;
    std::istringstream sin(templateVariables);
    std::string metaPath = filepath + "/" + collectionName + "/_meta.json";
    std::string workingPath = filepath + "/" + collectionName;
    std::string temp = "";
    // build the template using string input
    std::getline(sin, temp);
    while (!sin.eof())
    {

        metaContent[temp] = temp;
        std::getline(sin, temp);
    }
    metaContent[temp] = temp;
    // create metadata json file.
    json content;
    content["_meta.json"] = metaContent;

    // create collection folder is file cirectory
    std::filesystem::create_directory(workingPath);

    // output metadata file
    std::ofstream fout(metaPath);
    fout << content;
}

int Collection::renameCollection(std::string filepath, std::string oldCollectionName, std::string newCollectionName)
{
    std::string currentPath = filepath + "/" + oldCollectionName; // currentPath = ./database/[username]/[oldCollectionName]
    std::string newPath = filepath + "/" + newCollectionName;     // newPath = ./database/[username]/[newCollecitonName]

    std::filesystem::rename(currentPath, newPath); // cannot verify if operation was conducted successfully, must check that it is possible before calling function.
    this->setCollectionName(newCollectionName);

    return 1;
}

int Collection::createDocument(std::string filepath, std::string documentName, json content)
{
    // check if document name is taken, if it is return error code
    if (this->checkDocument(documentName))
    {
        return -1;
    }

    std::string workingPath = filepath + "/" + this->getCollectionName(); // workingPath = ./database/[username]/[collectionName]
    std::string metaPath = workingPath + "/_meta.json";                   // metaPath = ./database/[username]/[collectionName]/_meta.json
    std::ifstream fin(metaPath);

    // parse metadata file into template info variable
    json templateInfo = json::parse(fin);
    templateInfo = templateInfo["_meta.json"];

    // if contact is empty, no need to check for formatting. This if statement should always be true.
    if (!content.empty())
    {
        // iterate through every json object within content
        for (json::iterator i = content.begin(); i != content.end(); i++)
        {
            // ensure each object has all template parameters
            for (json::iterator j = templateInfo.begin(); j != templateInfo.end(); j++)
            {
                if (!i.value().contains(j.key()))
                {
                    return -2;
                }
            }
        }
    }
    else
    {
        return -1;
    }

    // add collection to documents map
    this->getDocuments()->emplace(documentName, Document(documentName, workingPath, content));

    return 1;
}

int Collection::deleteDocument(std::string filepath, std::string documentName)
{
    // make sure document to be deleted is actually in the database
    if (this->checkDocument(documentName))
    {
        std::string workingPath = filepath + "/" + this->getCollectionName() + "/" + documentName; // workingPath = ./database/[username]/[collectionName]/[documentName]

        // delete file from directory
        std::filesystem::remove(workingPath);

        // update map to remove document
        this->getDocuments()->erase(documentName);

        // read in metadata file to content
        std::string metaPath = filepath + "/" = this->getCollectionName() + "/_meta.json"; // metapath = ./database/[username]/[collectionName]/_meta.json
        std::ifstream fin(metaPath);
        json content = json::parse(fin);

        // remove deleted document from metadata
        content.erase(documentName);

        // output metadata back to file directory
        std::ofstream fout;
        fout.open(metaPath, std::ofstream::trunc);

        fout << content;

        return 1;
    }
    else
    {
        return -1;
    }
}

int Collection::replaceDocument(std::string filepath, std::string documentName, json content)
{
    if (this->getDocuments()->find(documentName) != this->getDocuments()->end())
    {
        std::string workingPath = filepath + "/" + this->getCollectionName() + "/" + documentName; // workingPath = ./databse/[username]/[collectionName]/[documentName]

        // make sure json object has objest, must be true as cannot replace a document with an empty document
        if (!content.empty())
        {
            // read in metadata file to tempalteInfo variable and then set it equal to templateInf
            std::string metaPath = filepath + "/" + this->getCollectionName() + "/_meta.json"; // metapath = ./database/[usernmae]/[collectionName]/_meta.json
            std::ifstream fin(metaPath);
            json templateInfo = json::parse(fin);
            templateInfo = templateInfo["_meta.json"];

            // ensure each object in content has each required field
            for (json::iterator i = content.begin(); i != content.end(); i++)
            {
                for (json::iterator j = templateInfo.begin(); j != templateInfo.end(); j++)
                {
                    if (!i.value().contains(j.key()))
                    {
                        return -2;
                    }
                }
            }
        }
        else
        {
            return -4;
        }

        // output content to document in file directory
        std::ofstream fout;
        fout.open(workingPath, std::ofstream::trunc);

        if (fout)
        {
            fout << content;

            return 1;
        }
        else
        {
            return -3;
        }
    }
    else
    {
        return -1;
    }
}

json Collection::displayObjects(std::string filepath)
{
    std::string workingPath = filepath + "/" + this->getCollectionName(); // workingPath = ./database/[username]/[collectionName]
    json output;

    // iterate through all documents, combining contents into one large json object
    for (auto i : *this->getDocuments())
    {
        output.merge_patch(i.second.getContent(workingPath));
    }

    return output;
}

json Collection::filterDisplay(std::string filepath, json query)
{
    json output = this->displayObjects(filepath); // gather what would be displayed normally

    // filter each object and include it if queried field matches query
    for (json::iterator i = output.begin(); i != output.end(); i++)
    {
        if (i.value()[query["filter"]] == query["query"])
        {
            output[i.key()] = i.value();
        }
    }

    return output;
}

json Collection::getTemplate(std::string filepath)
{
    std::string metaPath = filepath + "/" + this->getCollectionName() + "/_meta.json"; // metaPath = ./database/[username]/[collectionName]/_meta.json
    std::ifstream fin(metaPath);

    json content = json::parse(fin);

    json output;
    output["_meta.json"] = content["_meta.json"];

    return output;
}

bool Collection::checkDocument(std::string documentName)
{
    if (this->getDocuments()->find(documentName) != this->getDocuments()->end())
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

Document *Collection::getDocument(std::string documentName)
{
    return &((*this->getDocuments())[documentName]);
}

std::string Collection::getCollectionName()
{
    return this->collectionName;
}

void Collection::setCollectionName(std::string newCollectionName)
{
    this->collectionName = newCollectionName;
}

std::unordered_map<std::string, Document> *Collection::getDocuments()
{
    return &this->documents;
}

// start passthrough functions to Document

int Collection::renameDocument(std::string filepath, std::string oldDocumentName, std::string newDocumentName)
{
    // make sure old name exists in the collection and new name is not in the collection
    if (this->checkDocument(oldDocumentName) && !this->checkDocument(newDocumentName))
    {
        std::string workingPath = filepath + "/" + this->getCollectionName(); // workingPath = ./database/[username]/[collectionName]
        std::string metaPath = workingPath + "/_meta.json";                   // metaPath = ./database/[username]/[collectionName]/_meta.json

        std::ifstream fin(metaPath);

        if (!fin)
        {
            return -3;
        }
        else
        {
            // call rename function at document level, ocntinue base don result
            if (this->getDocument(oldDocumentName)->renameDocument(workingPath, newDocumentName) == 1)
            {
                json content = json::parse(fin);
                fin.close();

                // erase old document name form metadata, replace with new name
                content.erase(oldDocumentName);
                content[newDocumentName] = newDocumentName;

                // output metadata back to file
                std::ofstream fout;
                fout.open(metaPath, std::ofstream::trunc);

                fout << content;

                // update unordered_map for collection
                Document temp = *this->getDocument(oldDocumentName);
                this->getDocuments()->erase(oldDocumentName);
                this->getDocuments()->emplace(newDocumentName, temp);

                return 1;
            }
            else
            {
                return -2;
            }
        }
    }
    else
    {
        return -1;
    }
}

int Collection::createObject(std::string filepath, std::string documentName, json object)
{
    // if object not exist, it will never satisy any other condition
    if (object.empty())
    {
        return -1;
    }

    std::string metaPath = filepath + "/" + this->getCollectionName() + "/_meta.json"; // metaPath = ./database/[username]/[collectionName]/_meta.json
    std::ifstream fin(metaPath);

    // parses in entire metadate file, then becomes just templateInfo.
    json templateInfo = json::parse(fin);
    templateInfo = templateInfo["_meta.json"];

    fin.close();

    // make sure object meets templating requirements of collection, else returns error code.
    for (json::iterator j = templateInfo.begin(); j != templateInfo.end(); j++)
    {
        if (!object.contains(j.key()))
        {
            return -2;
        }
    }

    // check if document name is valid, else return error code
    if (this->checkDocument(documentName) == 1)
    {
        std::string workingPath = filepath + "/" + this->getCollectionName(); // workingPath = ./database/[username]/[collectionName]

        // iterate through documents
        for (auto i : *this->getDocuments())
        {
            // check if object exists in document, if so go into inner if statement
            if (i.second.checkObject(workingPath, object["_id"]) == 1)
            {
                // make sure document that contains object matches document requested, else return error code
                if (i.first == documentName)
                {
                    return this->getDocument(documentName)->createObject(workingPath, object);
                }
                else
                {
                    return -3;
                }
            }
        }
    }
    // if document does not exist, creates noew document to store object.
    else
    {
        return this->createDocument(filepath, documentName, object);
    }

    return -4;
}

int Collection::deleteObject(std::string filepath, std::string documentName, std::string objectID)
{
    // make sure document exists in collection.
    if (this->checkDocument(documentName))
    {
        std::string workingPath = filepath + "/" + this->getCollectionName(); // working path = ./database/[username]/[collectionName]

        // make sure object exists in the document, else return an error code.
        if (!this->getDocument(documentName)->checkObject(workingPath, objectID))
        {
            return this->getDocument(documentName)->deleteObject(workingPath, objectID);
        }
        else
        {
            return -1;
        }
    }
    else
    {
        return -1;
    }
}
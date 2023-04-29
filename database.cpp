#include "database.hpp"

Database::Database(){

}

Database::~Database(){

}

bool Database::deleteDocument(const std::string filename) {
    if (!this->isInDatabase(filename)) {
        std::cout << "Error: Database file not found" << std::endl;
        return false;
    }
    remove(filename.c_str());
    std::cout << "Document " << filename << " has been deleted" << std::endl;
    data.erase(filename);
    return true;
}

bool Database::isInDatabase(const std::string fileName) {
    if (this->data.find(fileName) == this->data.end()) {
        return false;
    }
    else {
        return true;
    }
}

std::string Database::readFile(const std::string filepath){
    std::ifstream input;
    input.open(filepath);
    std::ostringstream sstr;
    sstr << input.rdbuf();
    std::cout << sstr.str() << std::endl;
    return sstr.str();
}

bool Database::uploadFile(const std::string filename){
    std::string line;

    std::string inputPath = ".\\upload\\" + filename;
    std::string outputPath = ".\\database\\" + filename;

    std::ifstream fin(inputPath);
    std::ofstream fout(outputPath);

    if(fin && fout){
        while(std::getline(fin, line)){
            fout << line << "\n";
        }
        
        data.insert(filename, outputPath);

        return 1;
    }
    else{
        return 0;
    }

    return true;
}
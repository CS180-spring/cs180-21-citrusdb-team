#include "database.hpp"

bool Database::deleteDocument(const std::string filepath) {
    if (!this->isInDatabase(filepath)) {
        std::cout << "Error: Database file not found" << std::endl;
        return false;
    }
    remove(filepath.c_str());
    std::cout << "Document " << filepath << " has been deleted" << std::endl;
    return true;
}

bool Database::isInDatabase(const std::string fileName) {
    if (this->database.find(fileName) == this->database.end()) {
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
        return 1;
    }
    else{
        return 0;
    }

    return true;
}
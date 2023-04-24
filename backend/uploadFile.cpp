#include "uploadFile.hpp"

//@brief Upload a file that is stored in the upload folder into the database folder
    //Assumes that file to be uploaded is present in the upload folder.
//@param filename of the file to be uploaded from upload to database.
//@return true if file was able to be successfully opened and transferred, false if there was an error opening either file. 
bool uploadFile(const std::string filename){
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

//int main(int argc, char** argv){
//    if(argc != 2){
//        std::cout << "Improper number of arguments. Send the filename" << std::endl;
//    }
//
//    if(uploadFile(argv[1])){
//        std::cout << "Error Opening Files" << std::endl;
//    }
//    else{
//        std::cout << "Upload Complete" << std::endl;
//    }
//
//    return 0;
//}
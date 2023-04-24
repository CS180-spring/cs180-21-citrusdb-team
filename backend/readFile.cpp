#include "readFile.hpp"

using namespace std;

bool isInDatabase(const string filepath) {
    // placeholder
    return true;
}

string readFile(const string filepath){
    ifstream input;
    input.open(filepath);
    ostringstream sstr;
    sstr << input.rdbuf();
    return sstr.str();
}

// int main(int argc, char** argv){
//     if (argc != 2){
//         cout << "Improper number of arguments. Send the filepath" << endl;
//         return 1;
//     }
//     cout << readFile(argv[1]);
//     return 0;
// }
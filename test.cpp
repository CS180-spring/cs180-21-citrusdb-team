#include <gtest/gtest.h>
#include <string>
#include <variant>
#include "backend/file.hpp"

using namespace std;

// TEST(BasicDatabaseOperations, SingleTypeEntryObject){
//     vector<variant<int, double>> v = {2, 4, 6, 8, 0};
//     string uniqueId = "13579";
//     Entry nums = Entry(uniqueId, v);
//     EXPECT_EQ(uniqueId, nums.getId());
//     for (size_t i = 0; i < v.size(); i++){
//         EXPECT_EQ(nums.getElement(i), v.at(i));
//     }
// }

TEST(BasicOperations, ReadFile)
{
    // regex helps
    string raw = "";
    raw += "{\r\n";
    raw +=
        "    \"_id\": \"jkl321\",\r\n";
    raw +=
        "    \"science fiction authors\": [\r\n";
    raw +=
        "        {\r\n";
    raw +=
        "            \"_id\": \"abc123\",\r\n";
    raw +=
        "            \"first name\": \"Isaac\",\r\n";
    raw +=
        "            \"last name\": \"Asimov\",\r\n";
    raw +=
        "            \"birth date\": {\r\n";
    raw +=
        "                \"Year\": 1920,\r\n";
    raw +=
        "                \"Month\": \"January\",\r\n";
    raw +=
        "                \"Day\": 2\r\n";
    raw +=
        "            }\r\n";
    raw +=
        "        },\r\n";
    raw +=
        "        {\r\n";
    raw +=
        "            \"_id\": \"xyz098\",\r\n";
    raw +=
        "            \"first name\": \"Arthur\",\r\n";
    raw +=
        "            \"middle initial\": \"C\",\r\n";
    raw +=
        "            \"last name\": \"Clark\",\r\n";
    raw +=
        "            \"famous books\": [\r\n";
    raw +=
        "                \"2001: A Space Odyssey\",\r\n";
    raw +=
        "                \"The Songs of Distant Earth\"\r\n";
    raw +=
        "            ]\r\n";
    raw +=
        "        }\r\n";
    raw +=
        "    ]\r\n";
    raw +=
        "}";
        // readFile("database/people.json")
    EXPECT_EQ(raw, readFile("database/people.json"));
}

TEST(BasicOperations, DeleteFile) {
    string file = "test.txt";
    ofstream outFile(file);
    outFile << "Test file opened";
    outFile.close();

    ifstream inFile(file);
    ASSERT_TRUE(inFile.good());
    inFile.close();

    deleteDocument(file);

    inFile.open(file);
    ASSERT_FALSE(inFile.good());
    inFile.close();
}

TEST(BasicOperations, ReadAndDelete) {
    string input = "\t\nqwertyuiopasdfghjklzxcvbnm!@#$%^&*()_+1234567890";
    string filename = "testRead.txt";
    ofstream outFile(filename);
    outFile << input;
    outFile.close();

    string read = readFile(filename);
    EXPECT_EQ(read, input);

    deleteDocument(filename);

    ifstream inFile(filename);
    ASSERT_FALSE(inFile.good());
    inFile.close();


}

TEST(BasicOperations, MultipleReadAndDelete) { 
    string input = string("\'\"?\a\t\n\n\n\nthe quick brown fox jumps over the lazy dog\n")+
        "THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG";
    string filename = "multiRead.txt";
    ofstream outFile(filename);
    outFile << input;
    outFile.close();
    for (int i = 0; i < 100; i++){
        string read = readFile(filename);
        EXPECT_EQ(read, input);
    }
    deleteDocument(filename);

    ifstream inFile(filename);
    ASSERT_FALSE(inFile.good());
    inFile.close();


}

TEST(BasicOperations, UploadFile){
    uploadFile("upload/people.json");
    EXPECT_EQ(readFile("upload/people.json") ,readFile("database/people.json"));
}
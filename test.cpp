#include <gtest/gtest.h>
#include <string>
#include "engine.hpp"
#include "database.hpp"

using namespace std;

TEST(ReadFile, BasicOperations)
{
    // regex helps
    string raw = "";
    raw += "{\n";
    raw +=
        "    \"_id\": \"jkl321\",\n";
    raw +=
        "    \"science fiction authors\": [\n";
    raw +=
        "        {\n";
    raw +=
        "            \"_id\": \"abc123\",\n";
    raw +=
        "            \"first name\": \"Isaac\",\n";
    raw +=
        "            \"last name\": \"Asimov\",\n";
    raw +=
        "            \"birth date\": {\n";
    raw +=
        "                \"Year\": 1920,\n";
    raw +=
        "                \"Month\": \"January\",\n";
    raw +=
        "                \"Day\": 2\n";
    raw +=
        "            }\n";
    raw +=
        "        },\n";
    raw +=
        "        {\n";
    raw +=
        "            \"_id\": \"xyz098\",\n";
    raw +=
        "            \"first name\": \"Arthur\",\n";
    raw +=
        "            \"middle initial\": \"C\",\n";
    raw +=
        "            \"last name\": \"Clark\",\n";
    raw +=
        "            \"famous books\": [\n";
    raw +=
        "                \"2001: A Space Odyssey\",\n";
    raw +=
        "                \"The Songs of Distant Earth\"\n";
    raw +=
        "            ]\n";
    raw +=
        "        }\n";
    raw +=
        "    ]\n";
    raw +=
        "}";
    EXPECT_EQ(raw, readFile("database/people.json"));
}

TEST(DeleteFile, BasicOperations) {
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

TEST(ReadAndDelete, BasicOperations) {
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

TEST(MultipleReadAndDelete, BasicOperations) { 
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

TEST(UploadFile, BasicOperations){
    uploadFile("upload/people.json");
    EXPECT_EQ(readFile("upload/people.json") ,readFile("database/people.json"));
}
#include <gtest/gtest.h>
#include <string>
#include "backend/readFile.hpp"
#include "backend/deleteFile.hpp"
#include "backend/uploadFile.hpp"
#include "backend/jsonStrings.hpp"

using namespace std;

TEST(ReadFile, BasicOperations)
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

TEST(JsonStrings, BasicOperations)
{
    // input file
    string inputFile = "database/people.json";

    // expected output
    vector<Entry<string>> expectedEntries = {
        {
            "abc123",
            {
                {"_id", "\"abc123\""},
                {"first name", "\"Isaac\""},
                {"last name", "\"Asimov\""},
                {"birth date", "{\"Year\":1920,\"Month\":\"January\",\"Day\":2}"}
            }
        },
        {
            "xyz098",
            {
                {"_id", "\"xyz098\""},
                {"first name", "\"Arthur\""},
                {"middle initial", "\"C\""},
                {"last name", "\"Clark\""},
                {"famous books", "[\"2001: A Space Odyssey\",\"The Songs of Distant Earth\"]"}
            }
        }
    };

    // call the function
    vector<Entry<string>> actualEntries;
    jsonStrings(inputFile, actualEntries);

    // compare the actual output to the expected output
    ASSERT_EQ(actualEntries.size(), expectedEntries.size());
    for (size_t i = 0; i < actualEntries.size(); ++i) {
        ASSERT_EQ(actualEntries[i].id, expectedEntries[i].id);
        ASSERT_EQ(actualEntries[i].attributes.size(), expectedEntries[i].attributes.size());
        for (size_t j = 0; j < actualEntries[i].attributes.size(); ++j) {
            ASSERT_EQ(actualEntries[i].attributes[j].name, expectedEntries[i].attributes[j].name);
            ASSERT_EQ(actualEntries[i].attributes[j].value, expectedEntries[i].attributes[j].value);
        }
    }
}


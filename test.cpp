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
    Database test;
    EXPECT_EQ(raw, test.readFile("database/people.json"));
}

TEST(UploadFile, BasicOperations){
    Database test;
    test.uploadFile("people.json");
    EXPECT_EQ(test.readFile("upload/people.json") ,test.readFile("database/people.json"));
}

TEST(DeleteFile, BasicOperations) {
    Database test;

    test.uploadFile("test.txt");

    test.deleteDocument("test.txt");

    ASSERT_FALSE(test.isInDatabase("test.txt"));
}

TEST(ReadAndDelete, BasicOperations) {
    Database test;
    string input = "\n\tqwertyuiopasdfghjklzxcvbnm!@#$%^&*()_+1234567890";

    test.uploadFile("testread.txt");

    string read = test.readFile("testread.txt");
    EXPECT_EQ(read, input);

    test.deleteDocument("testread.txt");

    ASSERT_FALSE(test.isInDatabase("testread.txt"));
}

TEST(MultipleReadAndDelete, BasicOperations) { 
    Database test;
    string input = "the quick brown fox jumps over the lazy dog. \n THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG.";
    string filename = "multiRead.txt";

    test.uploadFile(filename);

    for (int i = 0; i < 100; i++){
        string read = test.readFile(filename);
        EXPECT_EQ(read, input);
    }
    test.deleteDocument(filename);

    ASSERT_FALSE(test.isInDatabase(filename));
}
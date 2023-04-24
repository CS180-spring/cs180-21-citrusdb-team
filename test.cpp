#include <gtest/gtest.h>
#include <string>
#include "backend/readFile.hpp"
#include "backend/deleteFile.hpp"

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

// TEST(COMPILE, StringTest) {
//     EXPECT_EQ("\n", "%n");
// }
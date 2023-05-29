#include <gtest/gtest.h>
#include <string>
#include <variant>
#include "backend/jsonStrings.hpp"
#include "backend/document.hpp"
#include "backend/file.hpp"
#include "backend/databaseEngine.hpp"

using namespace std;

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


TEST(DBEngine, Logins){
    DatabaseEngine dbe;
    ASSERT_TRUE(dbe.loginCheck("alice", "m"));
    ASSERT_FALSE(dbe.loginCheck("nonexistent", "m"));
}

TEST(DBEngine, AddUsers){
    DatabaseEngine dbe;
    // back up file and rewrite it once the test case is done 
    string backup = readFile("database/_metaDB.json");
    int passed = dbe.createUser("user1", "temp@example.com", "pwd123");
    EXPECT_EQ(passed, 1);
    int fail_existing_username = dbe.createUser("user1", "12345@example.edu", "qwerty");
    EXPECT_EQ(fail_existing_username, 0);
    int fail_existing_email = dbe.createUser("user2", "temp@example.com", "asdfjkl;");
    EXPECT_EQ(fail_existing_email, -1);
    ASSERT_FALSE(dbe.deleteUser("user2"));
    int fail_bad_password = dbe.createUser("user3", "temporary@not-real.com", ".");
    EXPECT_EQ(fail_bad_password, -2);
    ofstream o;
    o.open("../_metaDB.json");
    o << backup;
    o.close();
}

TEST(DBEngine, AddAndDeleteUsers){
    // back up file and rewrite it once the test case is done 
    string backup = readFile("database/_metaDB.json");
    DatabaseEngine dbe;
    ASSERT_TRUE(dbe.deleteUser("alice"));
    ASSERT_FALSE(dbe.deleteUser("alice"));
    int passed = dbe.createUser("user1", "temp@example.com", "pwd123");
    EXPECT_EQ(passed, 1);
    ASSERT_TRUE(dbe.deleteUser("user1"));
    ASSERT_FALSE(dbe.deleteUser("user1"));
    ASSERT_TRUE(dbe.deleteUser("bob"));
    ASSERT_FALSE(dbe.deleteUser("bob"));
    ofstream o;
    o.open("../_metaDB.json");
    o << backup;
    o.close();
}

TEST(DBEngine, Logins){
    string backup = readFile("database/_metaDB.json");
    DatabaseEngine dbe;
    ASSERT_TRUE(dbe.loginCheck("alice", "m"));
    ASSERT_FALSE(dbe.loginCheck("alice", "wrong"));
    ASSERT_FALSE(dbe.loginCheck("not_existent", "m"));
    ofstream o;
    o.open("../_metaDB.json");
    o << backup;
    o.close();
}

TEST(DBEngine, ChangePasswords){
    string backup = readFile("database/_metaDB.json");
    DatabaseEngine dbe;
    ASSERT_TRUE(dbe.resetPassword("alice", "alice@example.com"));
    ASSERT_FALSE(dbe.resetPassword("not_exist", "alice@example.com"));
    ASSERT_FALSE(dbe.resetPassword("alice", "not_existent@email.com"));
    ASSERT_FALSE(dbe.updatePassword("not_existent", "123456789"));
    ASSERT_FALSE(dbe.updatePassword("alice", "b"));
    string pwd = "strong_password";
    ASSERT_TRUE(dbe.updatePassword("alice", pwd));
    EXPECT_EQ(pwd, dbe.getUser("alice").getPassword());
    ofstream o;
    o.open("../_metaDB.json");
    o << backup;
    o.close();
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

TEST(DocumentTest, CreateAndGet) {
    Document doc("test.json");

    string objectId = "Object_1";
    json obj = {
        {"name", "John"},
        {"age", 30}
    };
    doc.createObject(objectId, obj);
    json getObj = doc.getObject(objectId);

    EXPECT_EQ(obj, getObj);
}

TEST(DocumentTest, DeleteObject) {
    Document doc("test.json");

    string objectId = "Object_1";
    json obj = {
        {"name", "John"},
        {"age", 30}
    };
    doc.createObject(objectId, obj);
    doc.deleteObject(objectId);

    json getObj = doc.getObject(objectId);
    EXPECT_TRUE(getObj.empty());
}

TEST(DocumentTest, UpdateDocument) {
    Document doc("test.json");

    string objectId = "Object_1";
    json obj = {
        {"name", "John"},
        {"age", 30}
    };
    doc.createObject(objectId, obj);
    doc.updateDocument();

    Document updatedDoc("test.json");

    json getObj = updatedDoc.getObject(objectId);
    EXPECT_EQ(getObj, obj);
}

TEST(DocumentTest, ListObjectIDs) {
    Document doc("test.json");

    string objectId1 = "Object_1";
    json obj1 = {
        {"name", "John"},
        {"age", 30}       
    };
    doc.createObject(objectId1, obj1);

    string objectId2 = "Object_2";
    json obj2 = {
        {"name", "Jeff"},
        {"age", 28}
    };
    doc.createObject(objectId2, obj2);

    vector<string> objectIDs = doc.listObjectIDs();

    EXPECT_EQ(objectIDs.size(), 2);
    EXPECT_EQ(objectIDs[0], objectId1);
    EXPECT_EQ(objectIDs[1], objectId2);
}

TEST(DocumentTest, ClearContent) {
    Document doc("test.json");

    string objectId = "Object_1";
    json obj = {
        {"name", "John"},
        {"age", 30}        
    };
    doc.createObject(objectId, obj);
    doc.clearContent();

    json getObj = doc.getObject(objectId);
    EXPECT_TRUE(getObj.empty());
}

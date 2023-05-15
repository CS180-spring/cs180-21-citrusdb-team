#include <gtest/gtest.h>
#include <string>
#include <variant>
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

TEST(DBEngine, Initilization){
    DatabaseEngine dbe;
    ASSERT_TRUE(dbe.loginCheck("alice", "m"));
    ASSERT_FALSE(dbe.loginCheck("nonexistent", "m"));
}

TEST(DBEngine, AddUsers){
    DatabaseEngine dbe;
    int passed = dbe.createUser("user1", "temp@example.com", "pwd123");
    EXPECT_EQ(passed, 1);
    int fail_existing_username = dbe.createUser("user1", "12345@example.edu", "qwerty");
    EXPECT_EQ(fail_existing_username, 0);
    int fail_existing_email = dbe.createUser("user2", "temp@example.com", "asdfjkl;");
    EXPECT_EQ(fail_existing_email, -1);
    ASSERT_FALSE(dbe.deleteUser("user2"));
    int fail_bad_password = dbe.createUser("user3", "temporary@not-real.com", ".");
    EXPECT_EQ(fail_bad_password, -2);
}

TEST(DBEngine, AddAndDeleteUsers){
    DatabaseEngine dbe;
    ASSERT_TRUE(dbe.deleteUser("alice"));
    ASSERT_FALSE(dbe.deleteUser("alice"));
    int passed = dbe.createUser("user1", "temp@example.com", "pwd123");
    EXPECT_EQ(passed, 1);
    ASSERT_TRUE(dbe.deleteUser("user1"));
    ASSERT_FALSE(dbe.deleteUser("user1"));
    ASSERT_TRUE(dbe.deleteUser("bob"));
    ASSERT_FALSE(dbe.deleteUser("bob"));
}

TEST(DBEngine, Logins){
    DatabaseEngine dbe;
    ASSERT_TRUE(dbe.loginCheck("alice", "m"));
    ASSERT_FALSE(dbe.loginCheck("alice", "wrong"));
    ASSERT_FALSE(dbe.loginCheck("not_existent", "m"));

}

TEST(DBEngine, ChangePasswords){
    DatabaseEngine dbe;
    ASSERT_TRUE(dbe.resetPassword("alice", "alice@example.com"));
    ASSERT_FALSE(dbe.resetPassword("not_exist", "alice@example.com"));
    ASSERT_FALSE(dbe.resetPassword("alice", "not_existent@email.com"));
    ASSERT_FALSE(dbe.updatePassword("not_existent", "123456789"));
    ASSERT_FALSE(dbe.updatePassword("alice", "b"));
    string pwd = "strong_password";
    ASSERT_TRUE(dbe.updatePassword("alice", pwd));
    EXPECT_EQ(pwd, dbe.getUser("alice").getPassword());
}
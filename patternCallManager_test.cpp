#include <gtest/gtest.h>
#include "patternCallManager.h"
#include <fstream>
#include <cstdio>
#include <algorithm>

class PatternCallManagerTest : public ::testing::Test {
protected:
    patternCallManager utManager;

    Data createTestData(int id, string name, string path, bool flag) {
        return Data{id, name, path, flag};
    }
};

TEST_F(PatternCallManagerTest, GetDataFromFile_ReadsDataCorrectly) {
    string filename = "test_input.txt";
    std::ofstream outFile(filename);
    outFile << "1,TestName,/some/path,true\n";  // Adjust format to match your parser
    outFile.close();

    map<int, Data> result = utManager.getDataFromFile(filename);
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[1].name, "TestName");
    EXPECT_EQ(result[1].filepath, "/some/path");
    EXPECT_EQ(result[1].flag, true);

    std::remove(filename.c_str());
}

TEST_F(PatternCallManagerTest, WriteDataToFile_CreatesFile) {
    Data d = createTestData(1, "TestName", "/test/path", true);
    list<Data> dataList = {d};
    string filename = "test_output.txt";

    utManager.writeDataToFile(filename, dataList);

    std::ifstream inFile(filename);
    ASSERT_TRUE(inFile.is_open());

    std::string line;
    std::getline(inFile, line);
    ASSERT_FALSE(line.empty()); // Basic content check
    inFile.close();

    std::remove(filename.c_str()); // Clean up
}

TEST_F(PatternCallManagerTest, AddDummyData_AddsToEmptyMap) {
    Data d = createTestData(1, "test", "/path/test", true);
    map<int, Data> original;
    auto result = utManager.addDummyData(d, original);

    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[1], d);
}

TEST_F(PatternCallManagerTest, GetById_ReturnsMatchingData) {
    Data d1 = createTestData(1, "a", "/a", true);
    Data d2 = createTestData(2, "b", "/b", false);
    map<int, Data> db = {{1, d1}, {2, d2}};

    list<Data> result = utManager.getById(db, 1);
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result.front(), d1);
}

TEST_F(PatternCallManagerTest, GetByName_ReturnsMatchingName) {
    Data d1 = createTestData(1, "alpha", "/a", true);
    Data d2 = createTestData(2, "beta", "/b", false);
    Data d3 = createTestData(3, "alpha", "/c", true);

    map<int, Data> db = {{1, d1}, {2, d2}, {3, d3}};
    list<Data> result = utManager.getByName(db, "alpha");

    ASSERT_EQ(result.size(), 2);
    EXPECT_TRUE(find(result.begin(), result.end(), d1) != result.end());
    EXPECT_TRUE(find(result.begin(), result.end(), d3) != result.end());
}

TEST_F(PatternCallManagerTest, GetByPath_ReturnsMatchingPath) {
    Data d1 = createTestData(1, "A", "/x", true);
    Data d2 = createTestData(2, "B", "/y", false);
    Data d3 = createTestData(3, "C", "/x", true);

    map<int, Data> db = {{1, d1}, {2, d2}, {3, d3}};
    list<Data> result = utManager.getByPath(db, "/x");

    ASSERT_EQ(result.size(), 2);
    EXPECT_TRUE(find(result.begin(), result.end(), d1) != result.end());
    EXPECT_TRUE(find(result.begin(), result.end(), d3) != result.end());
}

TEST_F(PatternCallManagerTest, GetByFlag_ReturnsOnlyTrueFlaggedData) {
    Data d1 = createTestData(1, "A", "/x", true);
    Data d2 = createTestData(2, "B", "/y", false);
    Data d3 = createTestData(3, "C", "/z", true);

    map<int, Data> db = {{1, d1}, {2, d2}, {3, d3}};
    list<Data> result = utManager.getByFlag(db, true);

    ASSERT_EQ(result.size(), 2);
    EXPECT_TRUE(find(result.begin(), result.end(), d1) != result.end());
    EXPECT_TRUE(find(result.begin(), result.end(), d3) != result.end());
}

TEST_F(PatternCallManagerTest, GetByFlag_ReturnsOnlyFalseFlaggedData) {
    Data d1 = createTestData(1, "A", "/x", true);
    Data d2 = createTestData(2, "B", "/y", false);
    Data d3 = createTestData(3, "C", "/z", true);

    map<int, Data> db = {{1, d1}, {2, d2}, {3, d3}};
    list<Data> result = utManager.getByFlag(db, false);

    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result.front(), d2);
}
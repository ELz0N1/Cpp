#include <gtest/gtest.h>

#include <fstream>

#include "../src/headers/file.hpp"
#include "../src/headers/string.hpp"

TEST(StringTest, StringReaderTest) {
  std::string input = "Hello 123 c";
  StringReader sr{input};

  std::string s;
  int i;
  char c;

  sr >> s >> i >> c;

  EXPECT_EQ(s, "Hello");
  EXPECT_EQ(i, 123);
  EXPECT_EQ(c, 'c');
}

TEST(StringTest, StringReaderWriterTest) {
  std::string input = "";
  StringReaderWriter srw{input};

  std::string s = "Hello";
  int i = 123;
  char c = 'c';

  srw << s << i << c;

  std::string result;

  srw >> result;

  EXPECT_EQ(result, "Hello123c");
}

class FileTest : public ::testing::Test {
 protected:
  const std::string path = "empty_test_file.txt";

  void TearDown() override { std::remove(path.c_str()); }

  void CreateTestFile(const std::string& content) {
    std::ofstream ofs(path);
    ofs << content;
    ofs.close();
  }
};

TEST_F(FileTest, ThrowsOnInvalidPath) {
  EXPECT_THROW(FileReader fr("non_existent_file.txt"), FileNotFoundException);
}

TEST_F(FileTest, FileReaderTest) {
  CreateTestFile("Hello 123 c");
  FileReader fr{path};

  std::string s;
  int i;
  char c;

  fr >> s >> i >> c;

  EXPECT_EQ(s, "Hello");
  EXPECT_EQ(i, 123);
  EXPECT_EQ(c, 'c');
}

TEST_F(FileTest, FileReaderWriterTest) {
  CreateTestFile("");
  FileReaderWriter frw{path};

  std::string s = "Hello";
  int i = 123;
  char c = 'c';

  frw << s << i << c;

  frw.rewind();

  std::string result;

  frw >> result;

  EXPECT_EQ(result, "Hello123c");
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
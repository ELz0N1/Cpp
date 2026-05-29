#include <gtest/gtest.h>

#include <fstream>

#include "../src/headers/buffered_file.hpp"
#include "../src/headers/buffered_string.hpp"
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

TEST(BufferedStringTest, BufferedStringReaderTest) {
  std::string input = "Hello 123 c";
  BufferedStringReader sr{input};

  std::string s;
  int i;
  char c;

  sr >> s >> i >> c;

  EXPECT_EQ(s, "Hello");
  EXPECT_EQ(i, 123);
  EXPECT_EQ(c, 'c');
}

TEST(BufferedStringTest, BufferedStringReaderWriterTest) {
  BufferedStringReaderWriter srw{""};

  std::string s = "Hello";
  int i = 123;
  char c = 'c';

  srw << s << i << c;

  std::string result;
  srw >> result;

  EXPECT_EQ(result, "Hello123c");
}

TEST(BufferedStringTest, BufferedStringReaderLargeInputTest) {
  std::string input(5000, 'a');
  input += " 99 z";

  BufferedStringReader sr{input};

  std::string s;
  int i;
  char c;

  sr >> s >> i >> c;

  EXPECT_EQ(s, std::string(5000, 'a'));
  EXPECT_EQ(i, 99);
  EXPECT_EQ(c, 'z');
}

TEST(BufferedStringTest, BufferedStringWriterLargePayloadTest) {
  BufferedStringReaderWriter srw{""};

  std::string payload(5000, 'x');
  srw << payload;

  std::string result;
  srw >> result;

  EXPECT_EQ(result, payload);
}

TEST(BufferedStringTest, BufferedStringReaderEofTest) {
  BufferedStringReader sr{"Hello"};

  std::string s;
  sr >> s;

  EXPECT_EQ(s, "Hello");

  std::string extra;
  sr >> extra;

  EXPECT_TRUE(extra.empty());
}

class BufferedFileTest : public ::testing::Test {
 protected:
  const std::string path = "buffered_test_file.txt";

  void TearDown() override { std::remove(path.c_str()); }

  void CreateTestFile(const std::string& content) {
    std::ofstream ofs(path);
    ofs << content;
    ofs.close();
  }
};

TEST_F(BufferedFileTest, ThrowsOnInvalidPath) {
  EXPECT_THROW(BufferedFileReader fr("non_existent_buffered_file.txt"),
               FileNotFoundException);
}

TEST_F(BufferedFileTest, BufferedFileReaderTest) {
  CreateTestFile("Hello 123 c");
  BufferedFileReader fr{path};

  std::string s;
  int i;
  char c;

  fr >> s >> i >> c;

  EXPECT_EQ(s, "Hello");
  EXPECT_EQ(i, 123);
  EXPECT_EQ(c, 'c');
}

TEST_F(BufferedFileTest, BufferedFileReaderWriterTest) {
  CreateTestFile("");
  BufferedFileReaderWriter frw{path};

  std::string s = "Hello";
  int i = 123;
  char c = 'c';

  frw << s << i << c;

  frw.rewind();

  std::string result;
  frw >> result;

  EXPECT_EQ(result, "Hello123c");
}

TEST_F(BufferedFileTest, BufferedFileReaderLargeInputTest) {
  std::string content(5000, 'a');
  content += " 42 q";
  CreateTestFile(content);

  BufferedFileReader fr{path};

  std::string s;
  int i;
  char c;

  fr >> s >> i >> c;

  EXPECT_EQ(s, std::string(5000, 'a'));
  EXPECT_EQ(i, 42);
  EXPECT_EQ(c, 'q');
}

TEST_F(BufferedFileTest, BufferedFileWriterLargePayloadTest) {
  CreateTestFile("");
  BufferedFileReaderWriter frw{path};

  std::string payload(5000, 'm');
  frw << payload;

  frw.rewind();

  std::string result;
  frw >> result;

  EXPECT_EQ(result, payload);
}

TEST_F(BufferedFileTest, BufferedFileReaderEofTest) {
  CreateTestFile("Hello");
  BufferedFileReader fr{path};

  std::string s;
  fr >> s;

  EXPECT_EQ(s, "Hello");

  std::string extra;
  fr >> extra;

  EXPECT_TRUE(extra.empty());
}

TEST_F(BufferedFileTest, BufferedFileWriterDestructorTest) {
  {
    BufferedFileWriter fw{path};
    std::string data = "abc";
    fw << data;
  }

  std::ifstream ifs(path);
  std::string content((std::istreambuf_iterator<char>(ifs)),
                      std::istreambuf_iterator<char>());
  EXPECT_EQ(content, "abc");
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
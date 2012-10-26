#include <iostream>
#include <sstream>

#include <gtest/gtest.h>
#include <jellyfish/file_header.hpp>

namespace {
using jellyfish::generic_file_header;
using std::ostringstream;
using std::istringstream;
using std::string;

TEST(FileHeader, Standard) {
  generic_file_header h;

  EXPECT_EQ("", h["hostname"]);
  EXPECT_EQ("", h["pwd"]);
  EXPECT_EQ("", h["time"]);
  EXPECT_EQ("", h["exe_path"]);

  h.fill_standard();

  EXPECT_NE("", h["hostname"]);
  EXPECT_NE("", h["pwd"]);
  EXPECT_NE("", h["time"]);
  EXPECT_NE("", h["exe_path"]);
}

TEST(FileHeader, WriteRead) {
  generic_file_header hw;
  ostringstream os;

  hw.fill_standard();
  hw.write(os);
  EXPECT_EQ(0, os.tellp() % 8);
  const string ah("After header");
  os << ah;

  istringstream is(os.str());

  generic_file_header hr;
  EXPECT_TRUE(hr.read(is));
  EXPECT_EQ(0, is.tellg() % 8);

  EXPECT_EQ(hw, hr);
  string line;
  getline(is, line);
  EXPECT_EQ(ah, line);
}
} // namespace {

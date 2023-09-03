#include <unicode_formal/unicode_formal.h>

#include <gtest/gtest.h>

using namespace unicode_formal;

TEST(Unicode_FormalTest, TestGTest) {
    ASSERT_EQ(1, 1);
}

TEST(Unicode_FormalTest, Breathing) {}

TEST(Unicode_FomralTest, utf) {
  ASSERT_FALSE(is_unicode_nonchar(0));
  ASSERT_TRUE( is_unicode_nonchar(0xfffe));
  char32_t high = 0x10ffff;
  ASSERT_TRUE( is_unicode_nonchar(high ));
  ASSERT_FALSE(is_unicode_nonchar(U'a' ));


  ASSERT_TRUE(is_unicode_char(0));
  ASSERT_TRUE(is_unicode_char(U'a'));
  ASSERT_TRUE(is_unicode_char(u'a'));
  ASSERT_FALSE(is_unicode_char(high));

}

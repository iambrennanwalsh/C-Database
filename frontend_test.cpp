#include "gtest/gtest.h"

extern "C" {
  #include "frontend.h"
}

class FrontendTest: public testing::Test {};

TEST(FrontendTest, new_table) {
    struct Table* got = new_table();
    int size = sizeof(got->pages) / sizeof(got->pages[0]);
    EXPECT_EQ(got->num_rows, 0);
    EXPECT_EQ(size, TABLE_MAX_PAGES);
}

TEST(FrontendTest, new_input_buffer) {
    struct InputBuffer* input_buffer = new_input_buffer();
    EXPECT_EQ(input_buffer->buffer_length, 0);
    EXPECT_EQ(input_buffer->input_length, 0);
}

TEST(FrontendTest, get_prompt) {
    char* got = get_prompt();
    EXPECT_EQ(got, "db > ");
}

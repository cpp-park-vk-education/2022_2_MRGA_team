#include <gtest/gtest.h>

// extern "CPP" {

// }

TEST(INTERFACE, create_interface) {
    int* new_list = NULL;
    EXPECT_TRUE(new_list == NULL);

    new_list = new int[5];
    EXPECT_FALSE(new_list == NULL);

    delete[] new_list;
}

TEST(INTERFACE, free_interface) {
//    EXPECT_EQ(free_interface(), SUCCESS);
}

TEST(INTERFACE, draw_event) {
//    EXPECT_EQ(draw_event(), SUCCESS);
}

TEST(LOGIC, order_events) {
//    EXPECT_EQ(order_events(), SUCCESS);
}

TEST(LOGIC, form_check) {
//    EXPECT_EQ(form_check(), SUCCESS);
}

TEST(LOGIC, check_input) {
//    EXPECT_EQ(check_input(), SUCCESS);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

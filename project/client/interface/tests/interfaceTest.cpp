#include <gtest/gtest.h>


TEST(INTERFACE, create_interface) {
    // int *arr = new int[5];
    // for (size_t i = 0; i < 5; ++i) {
    //     arr[i] = i;
    // }
    int a = 1;
    EXPECT_EQ(1, a);
    // delete[] arr;
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

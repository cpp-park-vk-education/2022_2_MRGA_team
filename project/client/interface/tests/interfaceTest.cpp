#include <gtest/gtest.h>
// #include <authorization.hpp>
// #include <QApplication>

TEST(INTERFACE, create_interface) {
    // authorization* page = new authorization();
    // EXPECT_FALSE(page == nullptr);
    // delete page;
}

TEST(INTERFACE, free_interface) {
//    EXPECT_EQ(free_interface(), SUCCESS);
}

TEST(LOGIC, order_events) {
//    EXPECT_EQ(order_events(), SUCCESS);
}

TEST(LOGIC, form_check) {
//    EXPECT_EQ(form_check(), SUCCESS);
}

TEST(INTERFACE, draw_event) {
//    EXPECT_EQ(draw_event(), SUCCESS);
}

TEST(LOGIC, check_input) {
//    EXPECT_EQ(check_input(), SUCCESS);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#include <iostream>
#include "structs.hpp"

int main() {
    User user;
    user._birthDate = "20-12-2011";
    user._description = "I aadsfm adsf";
    user._email = "fasd@adf.ru";
    user._nickname = "sadfdf";
    user._password = "fajlkdf";
    // std::cout << user.toJSON();

    User from_string(user.toJSON());
    std::cout << from_string._nickname << std::endl;
}
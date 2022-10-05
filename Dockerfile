FROM manjarolinux/base
RUN sudo pacman -Sy --noconfirm
RUN sudo pacman -S git --noconfirm
RUN sudo pacman -S which --noconfirm
RUN sudo pacman -S gtest --noconfirm
RUN sudo pacman -S lcov --noconfirm
RUN sudo pacman -S restinio --noconfirm
RUN sudo pacman -S nlohmann-json --noconfirm
RUN sudo pacman -S libpqxx --noconfirm
RUN sudo pacman -S valgrind --noconfirm
RUN sudo pacman -S cppcheck --noconfirm
RUN sudo pacman -S cpplint --noconfirm
RUN sudo pacman -S python-pip --noconfirm
RUN sudo pacman -S make --noconfirm
RUN sudo pacman -S cmake --noconfirm
RUN sudo pacman -S clang-tools-extra --noconfirm
RUN sudo pacman -S qt6 --noconfirm



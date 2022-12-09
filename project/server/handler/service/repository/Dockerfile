FROM gcc:latest
RUN apt update -y
RUN git clone https://github.com/jtv/libpqxx.git && \
    cd libpqxx && \
    ./configure  && \
    make -j4 && \
    make install
RUN apt install cppcheck -y
RUN apt install clang-tidy -y
RUN apt install python3-pip -y
RUN apt install libc6-dbg -y
RUN apt install cmake -y
RUN apt install lcov -y
RUN apt install cppcheck -y
RUN apt install clang-format -y
RUN apt install libgtest-dev -y
RUN apt install libpq-dev -y
RUN apt install libpqxx-dev -y
RUN apt-get install postgresql postgresql-contrib -y

RUN pip install cpplint
RUN wget https://sourceware.org/pub/valgrind/valgrind-3.18.1.tar.bz2 && \
    tar xfv valgrind-3.18.1.tar.bz2 && \
    cd valgrind-3.18.1 && \
    ./autogen.sh && \
    ./configure&& \
    make && \
    make install
    
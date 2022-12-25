set(cxx_flags "-Werror -Wall -Wextra -Wpedantic\
        -Wredundant-decls -Wsign-conversion\
        -Wcast-align -Wcast-qual -Wconversion -Wfloat-equal -Wno-braced-scalar-init" CACHE STRING cxx_flags FORCE)


set(sanitizers_flags "-fsanitize=address -fsanitize-undefined-trap-on-error -fno-sanitize-recover=all -g -O0 "
        CACHE STRING sanitizers_flags FORCE)

set(testing_flags "-fprofile-arcs -ftest-coverage -fPIC -O0 -coverage" CACHE STRING testing_flags FORCE)

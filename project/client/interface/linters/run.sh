# CLIENT_INTERFACE_HPP = "-I PartyTime/painter.hpp -I PartyTime/base.h -I PartyTime/*/*/.hpp -I PartyTime/*/*/*/.hpp"
# CLIENT_INTERFACE_CPP = "PartyTime/painter.cpp PartyTime/base.cpp PartyTime/*/*/.cpp PartyTime/*/*/*/.cpp"

# SUM_HPP = "${CLIENT_INTERFACE_HPP}"
# SUM_CPP = "${CLIENT_INTERFACE_CPP}"

function print_header() {
    echo -e "\n***** ${1} *****"
}

function check_log() {
    LOG=$( { ${1}; } 2>&1 )
    STATUS=$?
    echo "$LOG"
    if echo "$LOG" | grep -q -E "${2}"
    then
        exit 1
    fi

    if [ $STATUS -ne 0 ]
    then
        exit $STATUS
    fi
}

print_header "RUN cppcheck"
check_log "cppcheck PartyTime/painter.cpp PartyTime/base.cpp -I PartyTime/painter.hpp -I PartyTime/base.h - --suppress=missingIncludeSystem" "\(information\)"

print_header "RUN clang-tidy"
# check_log "clang-tidy ${SUM_CPP} ${SUM_HPP} -warnings-as-errors=* -extra-arg=-std=c99 -- -Iproject/include" "Error (?:reading|while processing)"

# print_header "RUN cpplint"
# check_log "cpplint --extensions=c PartyTime/painter.cpp PartyTime/base.cpp PartyTime/*/*/.cpp PartyTime/*/*/*/.cpp -I PartyTime/painter.hpp -I PartyTime/base.h -I PartyTime/*/*/.hpp -I PartyTime/*/*/*/.hpp" "Can't open for reading"

print_header "SUCCESS"
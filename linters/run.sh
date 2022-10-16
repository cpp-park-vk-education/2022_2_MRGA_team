# CLIENT_INTERFACE_HPP = "-I project/client/interface/PartyTime/painter.hpp -I project/client/interface/PartyTime/base.h -I project/client/interface/PartyTime/*/*/.hpp -I project/client/interface/PartyTime/*/*/*/.hpp"
# CLIENT_INTERFACE_CPP = "project/client/interface/PartyTime/painter.cpp project/client/interface/PartyTime/base.cpp project/client/interface/PartyTime/*/*/.cpp project/client/interface/PartyTime/*/*/*/.cpp"

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

# print_header "RUN cppcheck"
# check_log "cppcheck project/client/interface/PartyTime/painter.cpp project/client/interface/PartyTime/base.cpp project/client/interface/PartyTime/*/*/.cpp project/client/interface/PartyTime/*/*/*/.cpp -I project/client/interface/PartyTime/painter.hpp -I project/client/interface/PartyTime/base.h -I project/client/interface/PartyTime/*/*/.hpp -I project/client/interface/PartyTime/*/*/*/.hpp --enable=all --inconclusive --error-exitcode=1 -I project/client/interface/PartyTime/painter.hpp -I project/client/interface/PartyTime/base.h -I project/client/interface/PartyTime/*/*/.hpp -I project/client/interface/PartyTime/*/*/*/.hpp --suppress=missingIncludeSystem" "\(information\)"

# print_header "RUN clang-tidy"
# check_log "clang-tidy ${SUM_CPP} ${SUM_HPP} -warnings-as-errors=* -extra-arg=-std=c99 -- -Iproject/include" "Error (?:reading|while processing)"

# print_header "RUN cpplint"
# check_log "cpplint --extensions=c project/client/interface/PartyTime/painter.cpp project/client/interface/PartyTime/base.cpp project/client/interface/PartyTime/*/*/.cpp project/client/interface/PartyTime/*/*/*/.cpp -I project/client/interface/PartyTime/painter.hpp -I project/client/interface/PartyTime/base.h -I project/client/interface/PartyTime/*/*/.hpp -I project/client/interface/PartyTime/*/*/*/.hpp" "Can't open for reading"

print_header "SUCCESS"
# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/PartyTime_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/PartyTime_autogen.dir/ParseCache.txt"
  "PartyTime_autogen"
  )
endif()

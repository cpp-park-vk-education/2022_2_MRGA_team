# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "API/CMakeFiles/api_autogen.dir/AutogenUsed.txt"
  "API/CMakeFiles/api_autogen.dir/ParseCache.txt"
  "API/api_autogen"
  "CMakeFiles/PartyTime_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/PartyTime_autogen.dir/ParseCache.txt"
  "Components/CMakeFiles/components_autogen.dir/AutogenUsed.txt"
  "Components/CMakeFiles/components_autogen.dir/ParseCache.txt"
  "Components/UI/CMakeFiles/ui_autogen.dir/AutogenUsed.txt"
  "Components/UI/CMakeFiles/ui_autogen.dir/ParseCache.txt"
  "Components/UI/ui_autogen"
  "Components/components_autogen"
  "Pages/CMakeFiles/pages_autogen.dir/AutogenUsed.txt"
  "Pages/CMakeFiles/pages_autogen.dir/ParseCache.txt"
  "Pages/pages_autogen"
  "PartyTime_autogen"
  )
endif()

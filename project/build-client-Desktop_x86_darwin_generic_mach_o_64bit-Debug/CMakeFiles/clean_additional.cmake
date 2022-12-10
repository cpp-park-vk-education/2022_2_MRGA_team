# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "PartyTime/CMakeFiles/PartyTime_autogen.dir/AutogenUsed.txt"
  "PartyTime/CMakeFiles/PartyTime_autogen.dir/ParseCache.txt"
  "PartyTime/Components/CMakeFiles/components_autogen.dir/AutogenUsed.txt"
  "PartyTime/Components/CMakeFiles/components_autogen.dir/ParseCache.txt"
  "PartyTime/Components/UI/CMakeFiles/ui_autogen.dir/AutogenUsed.txt"
  "PartyTime/Components/UI/CMakeFiles/ui_autogen.dir/ParseCache.txt"
  "PartyTime/Components/UI/ui_autogen"
  "PartyTime/Components/components_autogen"
  "PartyTime/Pages/CMakeFiles/pages_autogen.dir/AutogenUsed.txt"
  "PartyTime/Pages/CMakeFiles/pages_autogen.dir/ParseCache.txt"
  "PartyTime/Pages/pages_autogen"
  "PartyTime/PartyTime_autogen"
  "PartyTime/connector/lib/HttpConnector/CMakeFiles/HttpConnector_autogen.dir/AutogenUsed.txt"
  "PartyTime/connector/lib/HttpConnector/CMakeFiles/HttpConnector_autogen.dir/ParseCache.txt"
  "PartyTime/connector/lib/HttpConnector/HttpConnector_autogen"
  "PartyTime/connector/lib/LocalStorage/CMakeFiles/LocalStorage_autogen.dir/AutogenUsed.txt"
  "PartyTime/connector/lib/LocalStorage/CMakeFiles/LocalStorage_autogen.dir/ParseCache.txt"
  "PartyTime/connector/lib/LocalStorage/LocalStorage_autogen"
  "PartyTime/connector/lib/PartyTimeConnector/CMakeFiles/PartyTimeConnector_autogen.dir/AutogenUsed.txt"
  "PartyTime/connector/lib/PartyTimeConnector/CMakeFiles/PartyTimeConnector_autogen.dir/ParseCache.txt"
  "PartyTime/connector/lib/PartyTimeConnector/PartyTimeConnector_autogen"
  "PartyTime/connector/tests/CMakeFiles/connector_test_autogen.dir/AutogenUsed.txt"
  "PartyTime/connector/tests/CMakeFiles/connector_test_autogen.dir/ParseCache.txt"
  "PartyTime/connector/tests/connector_test_autogen"
  )
endif()

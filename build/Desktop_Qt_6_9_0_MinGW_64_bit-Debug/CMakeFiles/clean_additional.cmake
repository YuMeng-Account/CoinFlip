# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\CoinFlip_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\CoinFlip_autogen.dir\\ParseCache.txt"
  "CoinFlip_autogen"
  )
endif()

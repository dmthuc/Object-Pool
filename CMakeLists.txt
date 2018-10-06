cmake_minimum_required(VERSION 3.5)
set (CMAKE_CXX_STANDARD 14)
SET(THREAD_SANITIZER "OFF")
SET(ADDRESS_SANITIZER "OFF")

IF(${THREAD_SANITIZER} STREQUAL "ON" AND ${ADDRESS_SANITIZER} STREQUAL "ON")
    MESSAGE(SEND_ERROR "You can't use thread sanitizer and address sanitizer simultaniously, check your CMakeLists.txt THREAD_SANITIZER and ADDRESS_SANITIZER vars!")
ENDIF()

IF(${THREAD_SANITIZER} STREQUAL "ON")
    MESSAGE(STATUS "===> Thread sanitizer: ON.")
ELSE()
    MESSAGE(STATUS "===> Thread sanitizer: OFF.")
ENDIF()

IF(${ADDRESS_SANITIZER} STREQUAL "ON")
    MESSAGE(STATUS "===> Address sanitizer: ON.")
ELSE()
    MESSAGE(STATUS "===> Address sanitizer: OFF.")
ENDIF()

#SET(CMAKE_CXX_FLAGS "-g -Wall -Wnon-virtual-dtor -Werror -O3 -DNDEBUG -Wno-unused-function -pedantic -march=native")

ADD_EXECUTABLE(test_lib test.cpp)

SET_TARGET_PROPERTIES(test_lib PROPERTIES
    COMPILE_FLAGS "${COMPILATION_FLAGS} ${SANITIZER_CFLAGS} -fPIE"
    LINK_FLAGS "${LINK_FLAGS} ${SANITIZER_LFLAGS} -pie"
)

IF(${THREAD_SANITIZER} STREQUAL "ON")
    TARGET_LINK_LIBRARIES(test_lib
                          tsan)
ELSEIF(${ADDRESS_SANITIZER} STREQUAL "ON")
    TARGET_LINK_LIBRARIES(test_lib
                          asan)
ENDIF()

ADD_CUSTOM_COMMAND(TARGET test_lib POST_BUILD COMMAND ./test_lib --build_info --show_progress)


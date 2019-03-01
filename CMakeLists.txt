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
FIND_PACKAGE(Boost REQUIRED
    COMPONENTS
        unit_test_framework 
)
MESSAGE(STATUS "Boost headers found at: ${Boost_INCLUDE_DIRS}")
MESSAGE(STATUS "Boost libs found at: ${Boost_LIBRARY_DIRS}")


ADD_EXECUTABLE(test_pool test/test.cpp)

TARGET_INCLUDE_DIRECTORIES(test_pool PRIVATE ./)

SET_TARGET_PROPERTIES(test_pool PROPERTIES
    COMPILE_FLAGS "${COMPILATION_FLAGS} ${SANITIZER_CFLAGS} -fPIE"
    LINK_FLAGS "${LINK_FLAGS} ${SANITIZER_LFLAGS} -pie"
)

IF(${THREAD_SANITIZER} STREQUAL "ON")
    TARGET_LINK_LIBRARIES(test_pool
                          tsan)
ELSEIF(${ADDRESS_SANITIZER} STREQUAL "ON")
    TARGET_LINK_LIBRARIES(test_pool
                          asan)
ENDIF()

TARGET_LINK_LIBRARIES(test_pool
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)

ADD_CUSTOM_COMMAND(TARGET test_pool POST_BUILD COMMAND ./test_pool --build_info --show_progress)


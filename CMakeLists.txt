cmake_minimum_required(VERSION 3.20)
project(ChessProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)     # Enable VS filters

option (ChessProject_Vendored "Use vendored libs" OFF)

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

# ---------- Shared Library ----------
file(GLOB_RECURSE SHARED_SRC CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Shared/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Shared/*.h"
)

add_library(chess_shared STATIC ${SHARED_SRC})
target_include_directories(chess_shared PUBLIC src/Shared)

# Create filters that match src/shared/<subdir>
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src/Shared PREFIX "Shared" FILES ${SHARED_SRC})

# ---------- Server ----------
file(GLOB_RECURSE SERVER_SRC CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Server/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Server/*.h"
)

add_executable(chess_server ${SERVER_SRC})
target_link_libraries(chess_server PRIVATE chess_shared)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src/Server PREFIX "Server" FILES ${SERVER_SRC})

# ---------- Client ----------
if (ChessProject_Vendored)
    add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
else()
    find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
endif()

file(GLOB_RECURSE CLIENT_SRC CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Client/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Client/*.h"
)

add_executable(chess_client ${CLIENT_SRC})
target_link_libraries(chess_client PRIVATE chess_shared SDL3::SDL3)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src/Client PREFIX "Client" FILES ${CLIENT_SRC})

# ---------- Tests ----------
find_package(Catch2 REQUIRED)
enable_testing()

file(GLOB_RECURSE TEST_SRC CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/Tests/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Tests/*.h"
)

add_executable(chess_tests ${TEST_SRC})
target_link_libraries(chess_tests PRIVATE chess_shared Catch2::Catch2WithMain)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/Tests PREFIX "Tests" FILES ${TEST_SRC})

include(CTest)
include(Catch)
catch_discover_tests(chess_tests)

set_target_properties(chess_client PROPERTIES FOLDER "Applications")
set_target_properties(chess_server PROPERTIES FOLDER "Applications")
set_target_properties(chess_shared PROPERTIES FOLDER "Libraries")
set_target_properties(chess_tests  PROPERTIES FOLDER "Tests")
cmake_minimum_required(VERSION 3.14.4)

project(poco-example)

include(FetchContent)
FetchContent_Declare(
  Poco
  URL https://github.com/pocoproject/poco/archive/refs/tags/poco-1.10.1-release.zip
)
FetchContent_MakeAvailable(Poco)

add_executable(pocoex_client client/main.cpp)
target_link_libraries(pocoex_client PUBLIC Poco::Foundation Poco::Net Poco::Util)

add_executable(pocoex_server server/main.cpp)
target_link_libraries(pocoex_server PUBLIC Poco::Foundation Poco::Net Poco::Util)

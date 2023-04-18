set(BIN_NAME proxy-bin)

# find all source files
file(GLOB_RECURSE PROXY_SRCS "*.cpp" "*.cc")

# make executable
add_executable(${BIN_NAME} ${PROXY_SRCS})

message(STATUS "Proxy sources: ${PROXY_SRCS}")

find_package(Boost 1.71.0 REQUIRED system coroutine regex program_options serialization log)

# make relative include working
target_include_directories(${BIN_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

# link with dependencies
target_link_libraries(${BIN_NAME} PRIVATE Boost::headers Boost::system Boost::coroutine Boost::regex Boost::program_options Boost::serialization Boost::log)
target_link_libraries(${BIN_NAME} PRIVATE fmt)
target_link_libraries(${BIN_NAME} PRIVATE common_lib)
target_link_libraries(${BIN_NAME} PRIVATE nlohmann_json)

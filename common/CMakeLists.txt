set(LIB_NAME common_lib)

# find all source files
file(GLOB_RECURSE COMMON_LIB_SRCS "*.cpp" "*.cc")

# make library
add_library(${LIB_NAME} ${COMMON_LIB_SRCS})

# make relative include working
target_include_directories(${LIB_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

find_package(Boost 1.71.0 REQUIRED system coroutine regex program_options serialization log)

# link with dependencies
target_link_libraries(${LIB_NAME} PRIVATE nlohmann_json)
target_link_libraries(${LIB_NAME} PRIVATE Boost::headers Boost::system Boost::coroutine Boost::regex Boost::program_options Boost::serialization Boost::log)

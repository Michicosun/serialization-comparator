include(FetchContent)

message(STATUS "Fetch dependencies")

# Formatting

FetchContent_Declare(
        fmt
        GIT_REPOSITORY  https://github.com/fmtlib/fmt.git
        GIT_TAG         33f715077832d4f54bb51aa5aaf5b769fec97b67
)
FetchContent_MakeAvailable(fmt)

# Message pack

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY  https://github.com/catchorg/Catch2.git
        GIT_TAG         c359076e8ad5d8be45a56dee013f414a5485050b
)
FetchContent_MakeAvailable(Catch2)

FetchContent_Declare(
        Msgpack
        GIT_REPOSITORY  https://github.com/mikeloomisgg/cppack.git
        GIT_TAG         51655ec8f2b8fed84f685e3bcf8f226b139a263b
)
FetchContent_MakeAvailable(Msgpack)

# json

FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY  https://github.com/nlohmann/json.git
        GIT_TAG         6af826d0bdb55e4b69e3ad817576745335f243ca
)
FetchContent_MakeAvailable(nlohmann_json)

# yaml

FetchContent_Declare(
        yaml-cpp
        GIT_REPOSITORY  https://github.com/jbeder/yaml-cpp.git
        GIT_TAG         0e6e28d1a38224fc8172fae0109ea7f673c096db
)
FetchContent_MakeAvailable(yaml-cpp)

# protocol-buffers

FetchContent_Declare(
        protobuf
        GIT_REPOSITORY  https://github.com/protocolbuffers/protobuf.git
        GIT_TAG         bd52d0483987f1a5186fc3daa261d1d76a787bcf
)
FetchContent_MakeAvailable(protobuf)

# avro

FetchContent_Declare(
        avro
        GIT_REPOSITORY  https://github.com/apache/avro.git
        GIT_TAG         0c53710f511e36340d73c3f96aef02771d886156
)
FetchContent_MakeAvailable(avro)
add_subdirectory(${avro_SOURCE_DIR}/lang/c++ ${avro_BINARY_DIR}/lang/c++)
set(avro_SOURCE_DIR ${avro_SOURCE_DIR}/lang/c++ PARENT_SCOPE)

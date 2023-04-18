FROM ubuntu:20.04

WORKDIR /serialization-comparator

# Install package dependencies
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        build-essential \
        software-properties-common \
        autoconf \
        automake \
        libtool \
        pkg-config \
        ca-certificates \
        libssl-dev \
        wget \
        git \
        curl \
        language-pack-en \
        locales \
        locales-all \
        vim \
        gdb \
        cmake \
        libboost-all-dev \
        libprotobuf-dev \
        protobuf-compiler \
        valgrind && \
    apt-get clean

COPY . .

RUN rm -rf build && mkdir build && cd build && cmake .. && make -j 20 worker-bin proxy-bin

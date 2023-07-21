# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(hello_world_user)

target_sources(app PRIVATE src/main.c src/support.cpp)

set(Rust_CARGO_TARGET thumbv7em-none-eabi)
include(FetchContent)

FetchContent_Declare(
    Corrosion
    GIT_REPOSITORY https://github.com/corrosion-rs/corrosion.git
#    GIT_TAG v0.3.5 # Optionally specify a commit hash, version tag or branch here
)

FetchContent_MakeAvailable(Corrosion)

corrosion_import_crate(MANIFEST_PATH ${CMAKE_CURRENT_LIST_DIR}/../rust_app/Cargo.toml)

target_link_libraries(app PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../app/build/librust_app.a)

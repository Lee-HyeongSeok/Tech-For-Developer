cmake_minimum_required(VERSION 3.11)

project(
    NTMulticastTest
    LANGUAGES CXX
)


# 라이브러리 파일은 빌드 디렉토리 안에 lib 폴더에 출력
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

message("cmake_binary_dir : " ${CMAKE_BINARY_DIR})

# 실행 파일은 빌드 디렉토리 안에 bin 폴더에 출력
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(app)
add_subdirectory(lib)

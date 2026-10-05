set(INC ${PROJECT_SOURCE_DIR}/inc)

set(SRC main.cpp display.cpp matrix.cpp point.cpp)

add_executable(hello.out ${SRC})

target_include_directories(hello.out PUBLIC ${INC})

target_sources(hello.out PUBLIC ${SRC})
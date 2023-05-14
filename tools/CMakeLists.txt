add_executable(test1
    test1.cpp
)

add_executable(test2
    test2.cpp
)

target_link_libraries(test1 cfg-lib)
target_link_libraries(test2 cfg-lib)
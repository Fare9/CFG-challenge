add_executable(test1
    test1.cpp
)

add_executable(test2
    test2.cpp
)

add_executable(test3
    test3.cpp
)

target_link_libraries(test1 cfg-lib)
target_link_libraries(test2 cfg-lib)
target_link_libraries(test3 cfg-lib)

target_compile_features(test1 PUBLIC cxx_std_20)
target_compile_features(test2 PUBLIC cxx_std_20)
target_compile_features(test2 PUBLIC cxx_std_20)


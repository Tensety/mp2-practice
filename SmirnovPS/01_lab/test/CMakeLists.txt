set(target ${MP2_TESTS})

file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")

add_executable(${target} ${srcs} ${hdrs})
target_link_libraries(${target} PRIVATE GTest::gtest_main ${MP2_LIBRARY})

include(GoogleTest)
gtest_discover_tests(${target})

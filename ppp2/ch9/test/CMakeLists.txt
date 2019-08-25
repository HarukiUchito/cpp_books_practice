find_package(GTest REQUIRED)

include(GoogleTest)

enable_testing()

include_directories(../src)

function(add_unit_test name mylib)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name}
        GTest::GTest
        GTest::Main
        ${mylib}
        )
    add_test(
        NAME ${name}
        COMMAND ${name}
    )
endfunction()

add_unit_test(test_Rational_number RationalNumber)

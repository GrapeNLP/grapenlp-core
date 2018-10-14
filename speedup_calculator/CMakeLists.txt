project(speedup_calculator VERSION 0.1 LANGUAGES CXX)

add_executable(speedup_calculator src/speedup_calculator.cpp)
target_link_libraries(speedup_calculator
        stats
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
        )

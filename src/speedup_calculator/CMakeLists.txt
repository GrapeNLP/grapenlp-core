project(speedup_calculator VERSION ${GRAPENLP_VERSION_MAJOR}.${GRAPENLP_VERSION_MINOR}.${GRAPENLP_VERSION_PATCH} LANGUAGES CXX)

add_executable(speedup_calculator src/speedup_calculator.cpp)
target_link_libraries(speedup_calculator
        stats
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
        )

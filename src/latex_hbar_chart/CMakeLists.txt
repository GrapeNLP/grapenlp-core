project(latex_hbar_chart VERSION ${GRAPENLP_VERSION_MAJOR}.${GRAPENLP_VERSION_MINOR}.${GRAPENLP_VERSION_PATCH} LANGUAGES CXX)

add_executable(latex_hbar_chart src/latex_hbar_chart.cpp)
target_link_libraries(latex_hbar_chart
        stats
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
        )

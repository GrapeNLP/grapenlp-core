project(to_gnuplot VERSION ${GRAPENLP_VERSION_MAJOR}.${GRAPENLP_VERSION_MINOR}.${GRAPENLP_VERSION_PATCH} LANGUAGES CXX)

add_executable(to_gnuplot src/to_gnuplot.cpp)
target_link_libraries(to_gnuplot
        util
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
        )
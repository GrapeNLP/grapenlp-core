project(to_gnuplot VERSION 0.1 LANGUAGES CXX)

add_executable(to_gnuplot src/to_gnuplot.cpp)
target_link_libraries(to_gnuplot
        util
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
        )
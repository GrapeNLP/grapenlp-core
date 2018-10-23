project(latex_hbar_chart VERSION ${GRAPENLP_VERSION_MAJOR}.${GRAPENLP_VERSION_MINOR}.${GRAPENLP_VERSION_PATCH} LANGUAGES CXX)

add_executable(latex_hbar_chart src/latex_hbar_chart.cpp)
target_link_libraries(latex_hbar_chart
        stats
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
        )

install(TARGETS latex_hbar_chart EXPORT latex_hbar_chartConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT latex_hbar_chartConfig DESTINATION share/latex_hbar_chart/cmake)
export(TARGETS latex_hbar_chart FILE latex_hbar_chartConfig.cmake)


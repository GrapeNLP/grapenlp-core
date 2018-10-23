project(cgrapenlp VERSION 0.1 LANGUAGES CXX)

add_executable(nlp src/nlp.cpp)
target_link_libraries(nlp
        grapenlp
        ${Boost_PROGRAM_OPTIONS_LIBRARY})

install(TARGETS nlp EXPORT nlpConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
#install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT nlpConfig DESTINATION share/nlp/cmake)
export(TARGETS nlp FILE nlpConfig.cmake)

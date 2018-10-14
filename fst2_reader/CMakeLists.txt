project(fst2_reader VERSION 0.1 LANGUAGES CXX)

add_library(fst2_reader STATIC
        src/ul_fst2_reader.cpp
        src/ulua_fst2_reader.cpp
        src/uluaw_fst2_reader.cpp
        src/ulw_fst2_reader.cpp
        src/ult_fst2_reader.cpp
        src/ultw_fst2_reader.cpp
        src/ulx_fst2_reader.cpp
        src/ulxw_fst2_reader.cpp
        src/ua_fst2_tag_output_reader.cpp
        src/uaw_fst2_tag_output_reader.cpp
        src/t_fst2_tag_output_reader.cpp
        src/x_fst2_tag_output_reader.cpp
        src/int_w_fst2_tag_output_reader.cpp
        src/float_w_fst2_tag_output_reader.cpp
        src/w_fst2_tag_output_reader.cpp
        src/tw_fst2_tag_output_reader.cpp
        src/xw_fst2_tag_output_reader.cpp
        )
target_include_directories(fst2_reader PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(fst2_reader
        machine
        rtno
        fst2_constants
        )

install(TARGETS fst2_reader EXPORT fst2_readerConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT fst2_readerConfig DESTINATION share/fst2_reader/cmake)
export(TARGETS fst2_reader FILE fst2_readerConfig.cmake)

#Test files
add_executable(test_reader test/test_reader.cpp)
target_link_libraries(test_reader
        fst2_reader
        rtno_to_dot_serializer
        )

add_executable(test_wreader test/test_wreader.cpp)
target_link_libraries(test_wreader
        fst2_reader
        rtno_to_dot_serializer
        )

add_executable(test_creader test/test_creader.cpp)
target_link_libraries(test_creader
        fst2_reader
        rtno_to_dot_serializer
        )

add_executable(test_cwreader test/test_cwreader.cpp)
target_link_libraries(test_cwreader
        fst2_reader
        rtno_to_dot_serializer
        )

add_executable(test_treader test/test_treader.cpp)
target_link_libraries(test_treader
        fst2_reader
        rtno_to_dot_serializer
        )

add_executable(test_ctreader test/test_ctreader.cpp)
target_link_libraries(test_ctreader
        fst2_reader
        rtno_to_dot_serializer
        )

add_executable(test_twreader test/test_twreader.cpp)
target_link_libraries(test_twreader
        fst2_reader
        rtno_to_dot_serializer
        )

add_executable(test_ctwreader test/test_ctwreader.cpp)
target_link_libraries(test_ctwreader
        fst2_reader
        rtno_to_dot_serializer
        )

add_executable(test_xreader test/test_xreader.cpp)
target_link_libraries(test_xreader
        fst2_reader
        rtno_to_dot_serializer
        )

add_executable(test_cxreader test/test_cxreader.cpp)
target_link_libraries(test_cxreader
        fst2_reader
        rtno_to_dot_serializer
        )

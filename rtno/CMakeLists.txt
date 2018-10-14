project(rtno VERSION 0.1 LANGUAGES CXX)

add_library(rtno STATIC
        src/l_rtno.cpp
        src/lua_rtno.cpp
        src/luaw_rtno.cpp
        src/lux_rtno.cpp
        src/luxw_rtno.cpp
        src/lw_rtno_weight_tagger.cpp
        src/lw_rtno.cpp
        src/lt_rtno.cpp
        src/ltw_rtno.cpp
        src/lx_rtno.cpp
        src/lxw_rtno.cpp
        src/rtno_type.cpp
        src/rtno.cpp
        )
target_include_directories(rtno PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(rtno
        lrb_tree
        lexmask
        segment
        )

install(TARGETS rtno EXPORT rtnoConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT rtnoConfig DESTINATION share/rtno/cmake)
export(TARGETS rtno FILE rtnoConfig.cmake)

add_executable(set_default_weights src/set_default_weights.cpp)
target_link_libraries(set_default_weights
        rtno
        fst2_reader
        rtno_to_dot_serializer
        )

#add_executable(c_set_default_weights src/c_set_default_weights.cpp)
#target_link_libraries(c_set_default_weights
#        rtno
#        fst2_reader
#        rtno_to_dot_serializer
#        )

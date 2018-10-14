project(output_fprtn VERSION 0.1 LANGUAGES CXX)

add_library(output_fprtn STATIC
        src/output_fprtn.cpp
        src/a_output_fprtn.cpp
        src/ua_output_fprtn.cpp
        src/lua_output_fprtn.cpp
        src/aw_output_fprtn.cpp
        src/uaw_output_fprtn.cpp
        src/luaw_output_fprtn.cpp
        src/x_output_fprtn.cpp
        src/xw_output_fprtn.cpp
        src/ux_output_fprtn.cpp
        src/lux_output_fprtn.cpp
        src/uxw_output_fprtn.cpp
        src/luxw_output_fprtn.cpp
        )
target_include_directories(output_fprtn PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(output_fprtn
        assoc_container_impl_selector
        lexmask
        segment
        earley_parsing
        )

install(TARGETS output_fprtn EXPORT output_fprtnConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT output_fprtnConfig DESTINATION share/output_fprtn/cmake)
export(TARGETS output_fprtn FILE output_fprtnConfig.cmake)


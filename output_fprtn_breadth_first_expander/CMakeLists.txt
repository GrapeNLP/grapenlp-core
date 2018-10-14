project(output_fprtn_breadth_first_expander VERSION 0.1 LANGUAGES CXX)

add_library(output_fprtn_breadth_first_expander STATIC
        src/fprtn_breadth_first_expander.cpp
        src/a_fprtn_breadth_first_expander.cpp
        src/ua_fprtn_breadth_first_expander.cpp
        src/lua_fprtn_breadth_first_expander.cpp
        src/aw_fprtn_breadth_first_expander.cpp
        src/uaw_fprtn_breadth_first_expander.cpp
        src/luaw_fprtn_breadth_first_expander.cpp
        src/x_fprtn_breadth_first_expander.cpp
        src/ux_fprtn_breadth_first_expander.cpp
        src/lux_fprtn_breadth_first_expander.cpp
        src/xw_fprtn_breadth_first_expander.cpp
        src/uxw_fprtn_breadth_first_expander.cpp
        src/luxw_fprtn_breadth_first_expander.cpp
        )
target_include_directories(output_fprtn_breadth_first_expander PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(output_fprtn_breadth_first_expander
        util
        machine
        output_fprtn
        )

install(TARGETS output_fprtn_breadth_first_expander EXPORT output_fprtn_breadth_first_expanderConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT output_fprtn_breadth_first_expanderConfig DESTINATION share/output_fprtn_breadth_first_expander/cmake)
export(TARGETS output_fprtn_breadth_first_expander FILE output_fprtn_breadth_first_expanderConfig.cmake)

project(output_fprtn_blackboard_set_expander VERSION 0.1 LANGUAGES CXX)

add_library(output_fprtn_blackboard_set_expander STATIC
        src/fprtn_blackboard_set_expander.cpp
        src/a_fprtn_blackboard_set_expander.cpp
        src/ua_fprtn_blackboard_set_expander.cpp
        src/lua_fprtn_blackboard_set_expander.cpp
        src/aw_fprtn_blackboard_set_expander.cpp
        src/uaw_fprtn_blackboard_set_expander.cpp
        src/luaw_fprtn_blackboard_set_expander.cpp
        src/x_fprtn_blackboard_set_expander.cpp
        src/ux_fprtn_blackboard_set_expander.cpp
        src/lux_fprtn_blackboard_set_expander.cpp
        src/xw_fprtn_blackboard_set_expander.cpp
        src/uxw_fprtn_blackboard_set_expander.cpp
        src/luxw_fprtn_blackboard_set_expander.cpp
        )
target_include_directories(output_fprtn_blackboard_set_expander PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(output_fprtn_blackboard_set_expander
        util
        machine
        output_fprtn_zpps
        )

install(TARGETS output_fprtn_blackboard_set_expander EXPORT output_fprtn_blackboard_set_expanderConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT output_fprtn_blackboard_set_expanderConfig DESTINATION share/output_fprtn_blackboard_set_expander/cmake)
export(TARGETS output_fprtn_blackboard_set_expander FILE output_fprtn_blackboard_set_expanderConfig.cmake)

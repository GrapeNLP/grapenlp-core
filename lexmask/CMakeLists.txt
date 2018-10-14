project(lexmask VERSION 0.1 LANGUAGES CXX)

add_library(lexmask STATIC
        src/meta_code_dico.cpp
        src/lexmask.cpp
        src/lexmask_and_coarse_type.cpp
        src/u_lexmask_factory.cpp
        src/lexmask_default_weight.cpp
        )
target_include_directories(lexmask PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
target_link_libraries(lexmask
        compressed_delaf
        text_delaf
        token
        machine
        )

install(TARGETS lexmask EXPORT lexmaskConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT lexmaskConfig DESTINATION share/lexmask/cmake)
export(TARGETS lexmask FILE lexmaskConfig.cmake)

#Test files
add_executable(lexmask_test test/lexmask_test.cpp)
target_link_libraries(lexmask_test lexmask)

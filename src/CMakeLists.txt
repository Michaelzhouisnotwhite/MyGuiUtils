# add_library()
project(_src)

if(WIN32)
    set(src_win_prefix platforms/win)
    set(srcs
        "${src_win_prefix}/common.cpp"
    )
    
    add_library(${PROJECT_NAME} STATIC ${srcs})
    target_link_libraries(${PROJECT_NAME} PRIVATE wsock32 ws2_32 User32)
    target_include_directories(${PROJECT_NAME} PUBLIC ${include_dir})

    # add_library(KeyBoardListening SHARED win/KeyBoardListening.cpp)
endif()

add_library(lib::gui_utils ALIAS _src)
target_link_libraries(${PROJECT_NAME} PRIVATE toy::generic)
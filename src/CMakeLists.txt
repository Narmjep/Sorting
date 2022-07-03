project(Sorting)

set(SDL2_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/SDL2/x86_64-w64-mingw32/lib/cmake/SDL2)
set(SDLIMG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/SDL2/sdlimage/x86_64-w64-mingw32)
set(link_dir ${SDL2_DIR}/../../../lib)
set(SDLIMG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/SDL2/sdlimage/x86_64-w64-mingw32/)
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/imgui)

find_package(SDL2 REQUIRED)

include_directories(
    ${SDL2_DIR}/../../../include/SDL2/
    ${SDLIMG_DIR}/include/SDL2
    ${SDL2_INCLUDE_DIRS}
    ${SDLIMG_DIR}/include/SDL2/
    ${IMGUI_DIR}
)

add_executable(Sorting
    ${CMAKE_CURRENT_SOURCE_DIR}/../res/Icon.rc
    main.cpp
    Renderer.cpp
    Block.cpp
    Sorter.cpp
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_impl_sdl.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_impl_sdlrenderer.cpp
    ImguiWrapper.cpp
)

add_executable(Example
    example.cpp
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_impl_sdl.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_impl_sdlrenderer.cpp
    ImguiWrapper.cpp
)


message(${SDL2_DIR})

target_link_libraries(Sorting
    SDL2::SDL2
    SDL2::SDL2main
    ${SDL2_LIBRARIES}
    ${CMAKE_CURRENT_BINARY_DIR}/SDL2_image.dll
    ${CMAKE_CURRENT_BINARY_DIR}/zlib1.dll
    #${OPENGL_LIBRARIES}
)

target_link_libraries(Example
    SDL2::SDL2
    SDL2::SDL2main
    ${SDL2_LIBRARIES}
)


file(COPY ${SDL2_DIR}/../../../bin/SDL2.dll
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${SDLIMG_DIR}/bin/zlib1.dll
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${SDLIMG_DIR}/bin/libpng16-16.dll
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${SDLIMG_DIR}/bin/SDL2_image.dll
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../res/block.png
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
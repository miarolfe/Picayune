cmake_minimum_required(VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("Picayune")

add_subdirectory(vendor/EAAssert)
add_subdirectory(vendor/EAStdC)
add_subdirectory(vendor/EASTL)
add_subdirectory(vendor/EAThread)

set (WIN32_LIBRARIES
	user32
)

set(EA_LIBRARIES
	EAAssert
	EAStdC
	EASTL
	EAThread
)

set(IMGUI_SOURCE
    vendor/imgui/imgui.cpp
    vendor/imgui/imgui_demo.cpp
    vendor/imgui/imgui_draw.cpp
    vendor/imgui/backends/imgui_impl_win32.cpp
    vendor/imgui/backends/imgui_impl_dx11.cpp
    vendor/imgui/imgui_tables.cpp
    vendor/imgui/imgui_widgets.cpp
)

set(IMGUI_HEADERS
    vendor/imgui/imconfig.h
    vendor/imgui/imgui.h
    vendor/imgui/backends/imgui_impl_win32.h
    vendor/imgui/backends/imgui_impl_dx11.h
    vendor/imgui/imgui_internal.h
    vendor/imgui/imstb_rectpack.h
    vendor/imgui/imstb_textedit.h
    vendor/imgui/imstb_truetype.h
)

add_executable(PicayuneDX11 "src/Picayune.cpp" "src/D3D11Window.cpp" "src/D3D11Window.h" "src/Window.h" "src/Win32Window.cpp" "src/Win32Window.h" ${IMGUI_SOURCE} ${IMGUI_HEADERS} "src/Win32Window.h")
add_executable(PicayuneDX12 "src/Picayune.cpp" ${IMGUI_SOURCE} ${IMGUI_HEADERS} "src/Win32Window.h")
add_executable(PicayuneOpenGL "src/Picayune.cpp" ${IMGUI_SOURCE} ${IMGUI_HEADERS} "src/Win32Window.h")

target_compile_definitions(PicayuneDX11 PRIVATE DX11_BUILD)
target_compile_definitions(PicayuneDX12 PRIVATE DX12_BUILD)
target_compile_definitions(PicayuneOpenGL PRIVATE OPENGL_BUILD)

target_include_directories(PicayuneDX11 PRIVATE vendor/ vendor/imgui)
target_include_directories(PicayuneDX12 PRIVATE vendor/ vendor/imgui)
target_include_directories(PicayuneOpenGL PRIVATE vendor/ vendor/imgui)

target_link_libraries(PicayuneDX11 d3d11 ${WIN32_LIBRARIES} ${EA_LIBRARIES})
target_link_libraries(PicayuneDX12 d3d12 ${WIN32_LIBRARIES} ${EA_LIBRARIES})
target_link_libraries(PicayuneOpenGL opengl32 ${WIN32_LIBRARIES} ${EA_LIBRARIES})

set_target_properties(
    PicayuneDX11 PicayuneDX12 PicayuneOpenGL
    PROPERTIES
    WIN32_EXECUTABLE TRUE
    CXX_STANDARD 20
)

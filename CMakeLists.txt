# CMakeList.txt : CMake project for Picayune, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Picayune")

add_subdirectory(vendor/EAAssert)
# add_subdirectory(vendor/EABase)
add_subdirectory(vendor/EAStdC)
add_subdirectory(vendor/EASTL)
add_subdirectory(vendor/EAThread)

set(IMGUI_SOURCE
        vendor/imgui/imgui.cpp
        vendor/imgui/imgui_demo.cpp
        vendor/imgui/imgui_draw.cpp
        vendor/imgui/backends/imgui_impl_win32.cpp
        vendor/imgui/backends/imgui_impl_dx11.cpp
        vendor/imgui/imgui_tables.cpp
        vendor/imgui/imgui_widgets.cpp)

set(IMGUI_HEADERS
        vendor/imgui/imconfig.h
        vendor/imgui/imgui.h
        vendor/imgui/backends/imgui_impl_win32.h
        vendor/imgui/backends/imgui_impl_dx11.h
        vendor/imgui/imgui_internal.h
        vendor/imgui/imstb_rectpack.h
        vendor/imgui/imstb_textedit.h
        vendor/imgui/imstb_truetype.h)



# Add source to this project's executable.
add_executable(PicayuneSW "src/Picayune.cpp" "src/Picayune.h" "vendor/stb/stb_image.cpp")
add_executable(PicayuneD3D11 "src/D3D11Window.cpp" "src/D3D11Window.h" ${IMGUI_SOURCE} ${IMGUI_HEADERS})

target_include_directories(PicayuneD3D11 PRIVATE vendor/ vendor/imgui)
target_link_libraries(PicayuneD3D11 user32 d3d11 EAAssert EAStdC EASTL EAThread)

set_property(TARGET PicayuneSW PROPERTY WIN32_EXECUTABLE TRUE)
set_property(TARGET PicayuneD3D11 PROPERTY WIN32_EXECUTABLE TRUE)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET PicayuneSW PROPERTY CXX_STANDARD 20)
  set_property(TARGET PicayuneD3D11 PROPERTY CXX_STANDARD 20)
endif()
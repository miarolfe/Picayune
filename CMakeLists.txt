cmake_minimum_required(VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("Picayune")

set(ASSIMP_BUILD_STATIC_LIB ON)
set(ASSIMP_BUILD_SHARED_LIBS OFF)
set(ASSIMP_NO_EXPORT ON)
add_subdirectory(vendor/assimp)
# add_subdirectory(vendor/EAAssert)
# add_subdirectory(vendor/EAStdC)
# add_subdirectory(vendor/EASTL)
# add_subdirectory(vendor/EAThread)
add_subdirectory(vendor/glm)

set (WIN32_LIBRARIES
	user32
)

set (ASSIMP_LIBRARIES
	assimp
)

set (ASSIMP_HEADERS
	
)

set(EA_LIBRARIES
	EAAssert
	EAStdC
	EASTL
	EAThread
)

set(GLM_HEADERS
	vendor/glm/glm/glm.hpp
	vendor/glm/glm/gtc/matrix_transform.hpp
)

set(IMGUI_SOURCE
    vendor/imgui/imgui.cpp
    vendor/imgui/imgui_demo.cpp
    vendor/imgui/imgui_draw.cpp
    vendor/imgui/backends/imgui_impl_win32.cpp
    vendor/imgui/imgui_tables.cpp
    vendor/imgui/imgui_widgets.cpp
)

set(IMGUI_HEADERS
    vendor/imgui/imconfig.h
    vendor/imgui/imgui.h
    vendor/imgui/backends/imgui_impl_win32.h
    vendor/imgui/imgui_internal.h
    vendor/imgui/imstb_rectpack.h
    vendor/imgui/imstb_textedit.h
    vendor/imgui/imstb_truetype.h
)

set(CORE_SOURCE
	src/Picayune.cpp
	src/Win32Window.cpp
	src/Camera.cpp
)

set(CORE_HEADERS
	src/Picayune.h
	src/Window.h
	src/Win32Window.h
	src/Camera.h
)

set(D3D11_SOURCE
	src/D3D11Window.cpp
	vendor/imgui/backends/imgui_impl_dx11.cpp
)

set(D3D11_HEADERS
	src/D3D11Window.h
	vendor/imgui/backends/imgui_impl_dx11.h
)

set(D3D12_SOURCE
	src/D3D12Window.cpp
	vendor/imgui/backends/imgui_impl_dx12.cpp
)

set(D3D12_HEADERS
	src/D3D12Window.h
	vendor/imgui/backends/imgui_impl_dx12.h
)

set(OPENGL_SOURCE
	src/OpenGLWindow.cpp
	src/glad.c
	vendor/imgui/backends/imgui_impl_opengl3.cpp
)

set(OPENGL_HEADERS
	src/OpenGLWindow.h
	vendor/imgui/backends/imgui_impl_opengl3.h
	vendor/glad/glad.h
	vendor/KHR/khrplatform.h
)

add_executable(PicayuneDX11 ${D3D11_SOURCE} ${D3D11_HEADERS} ${CORE_SOURCE} ${CORE_HEADERS} ${IMGUI_SOURCE} ${IMGUI_HEADERS} ${GLM_HEADERS} ${ASSIMP_HEADERS} )
add_executable(PicayuneDX12 ${D3D12_SOURCE} ${D3D12_HEADERS} ${CORE_SOURCE} ${CORE_HEADERS} ${IMGUI_SOURCE} ${IMGUI_HEADERS} ${GLM_HEADERS} ${ASSIMP_HEADERS} )
add_executable(PicayuneOpenGL ${OPENGL_SOURCE} ${OPENGL_HEADERS} ${CORE_SOURCE} ${CORE_HEADERS} ${IMGUI_SOURCE} ${IMGUI_HEADERS} ${GLM_HEADERS} ${ASSIMP_HEADERS} )

target_compile_definitions(PicayuneDX11 PRIVATE DX11_BUILD)
target_compile_definitions(PicayuneDX12 PRIVATE DX12_BUILD)
target_compile_definitions(PicayuneOpenGL PRIVATE OPENGL_BUILD)

target_include_directories(PicayuneDX11 PRIVATE vendor/ vendor/assimp/include vendor/imgui vendor/glm)
target_include_directories(PicayuneDX12 PRIVATE vendor/ vendor/assimp/include vendor/imgui vendor/glm)
target_include_directories(PicayuneOpenGL PRIVATE vendor/ vendor/assimp/include vendor/imgui vendor/glm)

target_link_libraries(PicayuneDX11 d3d11 ${WIN32_LIBRARIES} ${ASSIMP_LIBRARIES}) # ${EA_LIBRARIES} )
target_link_libraries(PicayuneDX12 d3d12 ${WIN32_LIBRARIES} ${ASSIMP_LIBRARIES}) # ${EA_LIBRARIES} )
target_link_libraries(PicayuneOpenGL opengl32 ${WIN32_LIBRARIES} ${ASSIMP_LIBRARIES}) # ${EA_LIBRARIES} )

set_target_properties(
    PicayuneDX11 PicayuneDX12 PicayuneOpenGL
    PROPERTIES
    WIN32_EXECUTABLE TRUE
    CXX_STANDARD 20
)

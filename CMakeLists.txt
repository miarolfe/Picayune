cmake_minimum_required(VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("Picayune")

set(BUILD_SHARED_LIBS OFF)
set(ASSIMP_INSTALL OFF)
set(ASSIMP_BUILD_TESTS OFF)
set(ASSIMP_NO_EXPORT ON)
set(ASSIMP_BUILD_IFC_IMPORTER OFF)
add_subdirectory(vendor/assimp)
# add_subdirectory(vendor/EABase)
# add_subdirectory(vendor/EASTL)
# add_subdirectory(vendor/glm)

set (WIN32_LIBRARIES
	user32
)

set (ASSIMP_LIBRARIES
	assimp
)

set (ASSIMP_HEADERS
	vendor/assimp/include/assimp/scene.h
	vendor/assimp/include/assimp/Importer.hpp
	vendor/assimp/include/assimp/postprocess.h
)

set(EA_LIBRARIES
	EABase
	EASTL
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
	src/Mesh.cpp
	src/Model.cpp
)

set(CORE_HEADERS
	src/Picayune.h
	src/Window.h
	src/Win32Window.h
	src/Camera.h
	src/Vertex.h
	src/Texture.h
	src/Mesh.h
	src/Model.h
)

set(D3D11_SOURCE
	src/backends/DX11/D3D11IndexBuffer.cpp
	src/backends/DX11/D3D11InputLayout.cpp
	src/backends/DX11/D3D11InputLayoutManager.cpp
	src/backends/DX11/D3D11PixelShader.cpp
	src/backends/DX11/D3D11Shader.cpp
	src/backends/DX11/D3D11ShaderProgram.cpp
	src/backends/DX11/D3D11VertexBuffer.cpp
	src/backends/DX11/D3D11VertexShader.cpp
	src/backends/DX11/D3D11Window.cpp
	vendor/imgui/backends/imgui_impl_dx11.cpp
)

set(D3D11_HEADERS
	src/backends/DX11/D3D11IndexBuffer.h
	src/backends/DX11/D3D11InputLayout.h
	src/backends/DX11/D3D11InputLayoutManager.h
	src/backends/DX11/D3D11PixelShader.h
	src/backends/DX11/D3D11Shader.h
	src/backends/DX11/D3D11ShaderProgram.h
	src/backends/DX11/D3D11VertexBuffer.h
	src/backends/DX11/D3D11VertexShader.h
	src/backends/DX11/D3D11Window.h
	vendor/imgui/backends/imgui_impl_dx11.h
)

set(D3D12_SOURCE
	src/backends/DX12/D3D12IndexBuffer.cpp
	src/backends/DX12/D3D12InputLayout.cpp
	src/backends/DX12/D3D12InputLayoutManager.cpp
	src/backends/DX12/D3D12PixelShader.cpp
	src/backends/DX12/D3D12Shader.cpp
	src/backends/DX12/D3D12ShaderProgram.cpp
	src/backends/DX12/D3D12VertexBuffer.cpp
	src/backends/DX12/D3D12VertexShader.cpp
	src/backends/DX12/D3D12Window.cpp
	vendor/imgui/backends/imgui_impl_dx12.cpp
)

set(D3D12_HEADERS
	src/backends/DX12/D3D12IndexBuffer.h
	src/backends/DX12/D3D12InputLayout.h
	src/backends/DX12/D3D12InputLayoutManager.h
	src/backends/DX12/D3D12PixelShader.h
	src/backends/DX12/D3D12Shader.h
	src/backends/DX12/D3D12ShaderProgram.h
	src/backends/DX12/D3D12VertexBuffer.h
	src/backends/DX12/D3D12VertexShader.h
	src/backends/DX12/D3D12Window.h
	vendor/imgui/backends/imgui_impl_dx12.h
)

set(OPENGL_SOURCE
	src/backends/OpenGL/glad.c
	src/backends/OpenGL/OpenGLIndexBuffer.cpp
	src/backends/OpenGL/OpenGLInputLayout.cpp
	src/backends/OpenGL/OpenGLInputLayoutManager.cpp
	src/backends/OpenGL/OpenGLPixelShader.cpp
	src/backends/OpenGL/OpenGLShader.cpp
	src/backends/OpenGL/OpenGLShaderProgram.cpp
	src/backends/OpenGL/OpenGLVertexBuffer.cpp
	src/backends/OpenGL/OpenGLVertexShader.cpp
	src/backends/OpenGL/OpenGLWindow.cpp
	vendor/imgui/backends/imgui_impl_opengl3.cpp
)

set(OPENGL_HEADERS
	src/backends/OpenGL/OpenGLIndexBuffer.h
	src/backends/OpenGL/OpenGLInputLayout.h
	src/backends/OpenGL/OpenGLInputLayoutManager.h
	src/backends/OpenGL/OpenGLPixelShader.h
	src/backends/OpenGL/OpenGLShader.h
	src/backends/OpenGL/OpenGLShaderProgram.h
	src/backends/OpenGL/OpenGLVertexBuffer.h
	src/backends/OpenGL/OpenGLVertexShader.h
	src/backends/OpenGL/OpenGLWindow.h
	vendor/glad/glad.h
	vendor/imgui/backends/imgui_impl_opengl3.h
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

target_link_libraries(PicayuneDX11 d3d11 ${WIN32_LIBRARIES} ${ASSIMP_LIBRARIES})# ${EA_LIBRARIES})
target_link_libraries(PicayuneDX12 d3d12 ${WIN32_LIBRARIES} ${ASSIMP_LIBRARIES})# ${EA_LIBRARIES})
target_link_libraries(PicayuneOpenGL opengl32 ${WIN32_LIBRARIES} ${ASSIMP_LIBRARIES})# ${EA_LIBRARIES})

set_target_properties(
    PicayuneDX11 PicayuneDX12 PicayuneOpenGL
    PROPERTIES
    WIN32_EXECUTABLE TRUE
    CXX_STANDARD 20
)

add_custom_command(
	TARGET PicayuneDX11 POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets/ ${CMAKE_BINARY_DIR}/assets
)

add_custom_command(
	TARGET PicayuneDX12 POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets/ ${CMAKE_BINARY_DIR}/assets
)

add_custom_command(
	TARGET PicayuneOpenGL POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets/ ${CMAKE_BINARY_DIR}/assets
)

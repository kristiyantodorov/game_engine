cmake_minimum_required (VERSION 3.5)
project (game_engine)

add_compile_options(--std=c++11)

set(SRCS
    src/main.cpp
    src/ShaderHelper.cpp
    src/VertexBuffer.cpp
    src/VertexArray.cpp
    src/VertexBufferLayout.cpp
    src/TextureLoader.cpp
    src/Triangle.cpp
    src/Camera.cpp
    
    src/vendor/stb_image/stb_image.cpp
)

add_executable(${PROJECT_NAME} ${SRCS})

link_directories(/usr/lib/x86_64-linux-gnu/mesa /usr/lib/x86_64-linux-gnu)

target_link_libraries(${PROJECT_NAME}
    glfw
    GL
    GLEW
)
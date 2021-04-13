set(SRC_LIST 
  Game.cpp 
  Shader.cpp
  Texture.cpp
  ResourceManager.cpp
  stb_image.cpp
  SpriteRenderer.cpp
  GameObject.cpp
  GameLevel.cpp
)

# add include
set(INCLUDE_LIST ${PROJECT_SOURCE_DIR}/include)
include_directories(${INCLUDE_LIST})

# add library
set(LIB_GLFW ${PROJECT_SOURCE_DIR}/lib/libglfw3.a)
link_libraries(${LIB_GLFW} glad glm)

add_library(game ${SRC_LIST})

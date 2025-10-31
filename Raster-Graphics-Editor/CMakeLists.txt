# Add source to this project's executable.
add_executable (${PROJECT_NAME} "main.cpp"  "Core/IWindow.h" "Platforms/SDL/SDLWindow.cpp" "Platforms/SDL/SDLWindow.h" "Core/IRenderer.h" "Core/ITexture.h" "Platforms/SDL/SDLRenderer.h" "Platforms/SDL/SDLRenderer.cpp" "Platforms/SDL/SDLTexture.h" "Platforms/SDL/SDLTexture.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE vendor)
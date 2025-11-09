set(SDL_TEST OFF)
add_subdirectory(SDL)

# ---- ImGui ----
file(GLOB IMGUI_SOURCES
    ImGui/*.cpp
)

add_library(ImGui ${IMGUI_SOURCES})
target_include_directories(ImGui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/ImGui
    ${CMAKE_CURRENT_SOURCE_DIR}/ImGui/backends
)

target_link_libraries(ImGui PUBLIC SDL3::SDL3)

# ---- Vendor interface ----
add_library(vendor INTERFACE)
target_link_libraries(vendor INTERFACE SDL3::SDL3 ImGui)
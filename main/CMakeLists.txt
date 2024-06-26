project("main")
enable_language(C CXX ASM_MASM)

file(GLOB MAIN_SOURCE_FILES
    "source/*.*"
    "source/features/*.*"
    "source/hooks/*.*"
    "source/hooks/detours/*.*"
    "source/gui/*.*"
    "source/gui/submenus/*.*"
    "source/script/*.*"
    "source/features/*.*"
    "utility/*.*"
    "utility/logger/*.*"
    "utility/signatures/*.*"
    "utility/rage/*.*"
    "utility/rage/invoker/*.*"
    "utility/rage/invoker/natives/*.*"
    "utility/config/*.*"
)

include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)
link_directories(SYSTEM "C:\\Program Files (x86)\\Microsoft DirectX SDK (June 2010)\\Lib\\x64")
include_directories(SYSTEM "C:\\Program Files (x86)\\Microsoft DirectX SDK (June 2010)\\Include")

add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_library(${PROJECT_NAME} SHARED ${MAIN_SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE minhook)
target_link_libraries(${PROJECT_NAME} PRIVATE d3d11 d3dx11)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui)
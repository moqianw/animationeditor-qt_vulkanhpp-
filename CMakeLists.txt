cmake_minimum_required(VERSION 3.16)

project(qvulkan VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "D:/Qt/6.9.3/msvc2022_64")
find_package(Qt6 REQUIRED COMPONENTS Quick Widgets)

qt_standard_project_setup(REQUIRES 6.8)



qt_add_executable(appqvulkan
    src/main.cpp
    src/core/VulkanWindow.cpp
    src/core/VulkanContaxt.cpp
    src/ui/MainWindow.cpp
    src/core/engine/Mapping.hpp
    src/core/utils/CommandPool.cpp
    src/core/VulkanRenderer.cpp
    src/core/resource/ResourceManager.cpp
    src/core/resource/PipelineManager.cpp
    src/core/resource/ShaderManager.cpp
    src/core/resource/DescriptorSetManager.cpp
    src/core/resource/MaterialManager.cpp
    src/core/resource/RenderPassManager.cpp
    src/core/resource/FrameBufferManager.cpp
    
)
target_include_directories(appqvulkan PRIVATE
    "${CMAKE_SOURCE_DIR}/Thirdparty/Include"
)
# 添加搜索路径
link_directories("${CMAKE_SOURCE_DIR}/Thirdparty/Lib")

# 链接库
target_link_libraries(appqvulkan PRIVATE 
    ${CMAKE_SOURCE_DIR}/Thirdparty/Lib/vulkan-1.lib
    ${CMAKE_SOURCE_DIR}/Thirdparty/Lib/glm.lib
)

qt_add_qml_module(appqvulkan
    URI qvulkan
    VERSION 1.0
    QML_FILES
        Main.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appqvulkan PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appqvulkan
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appqvulkan
    PRIVATE Qt6::Quick Qt::Widgets
)

include(GNUInstallDirs)
install(TARGETS appqvulkan
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

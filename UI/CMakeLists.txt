# Qt sẽ tạo ra mã code trong quá trình build
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Thêm các file nguồn cho UI
set(UI_SOURCES
    src/main.cpp
    # src/UIApplication.cpp
    # src/CpuDataModel.cpp
    # src/MemoryDataModel.cpp
    # src/IpcClientManager.cpp
    # src/UpdateManager.cpp
)

# Thêm các file header
set(UI_HEADERS
    include/UIApplication.h
    include/CpuDataModel.h
    include/MemoryDataModel.h
    include/IpcClientManager.h
    include/UpdateManager.h
)

# Tạo danh sách các file QML
set(QML_FILES
    qml/main.qml
    # qml/CpuMonitorView.qml
    # qml/MemoryMonitorView.qml
    # qml/Charts/LineChart.qml
    # qml/Theme.qml
)

# Tạo resource file cho QML
qt_add_resources(RESOURCES
    UI_RESOURCES
    #PREFIX "/"
    FILES ${QML_FILES}
)

# Tạo executable cho UI
add_executable(ResourceMonitorUI
    ${UI_SOURCES}
    ${UI_HEADERS}
    ${RESOURCES}
)

# Thêm thư mục include
target_include_directories(ResourceMonitorUI PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Liên kết với Common và các thư viện Qt
target_link_libraries(ResourceMonitorUI PRIVATE
    Common
    ${QT_LIBS}
)

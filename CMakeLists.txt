cmake_minimum_required(VERSION 3.16)

project(SystemResourceMonitor VERSION 1.0.0 LANGUAGES CXX)

# Yêu cầu sử dụng C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Tìm các package Qt cần thiết
find_package(Qt6 REQUIRED COMPONENTS Core Quick Widgets Charts)
if (NOT Qt6_FOUND)
    find_package(Qt5 5.15 REQUIRED COMPONENTS Core Quick Widgets Charts)
endif()

# Biến để lưu trữ các thư viện Qt cần sử dụng
set(QT_LIBS
    Qt::Core
    Qt::Quick
    Qt::Widgets
    Qt::Charts
)

# Biến cho thông tin IPC
set(IPC_SOCKET_NAME "SystemResourceMonitorSocket")

# Thêm các thư mục con
add_subdirectory(Common)
add_subdirectory(Service)
add_subdirectory(UI)
# Thêm các file nguồn cho service
set(SERVICE_SOURCES
    src/main.cpp
    src/ServiceApplication.cpp
    src/CpuDataCollector.cpp
    # src/MemoryDataCollector.cpp
    # src/SystemDataAggregator.cpp
    # src/IpcServerManager.cpp
)

# Thêm các file header
set(SERVICE_HEADERS
    include/ServiceApplication.h
    include/CpuDataCollector.h
    include/MemoryDataCollector.h
    include/SystemDataAggregator.h
    include/IpcServerManager.h
)

# Tạo executable cho service
add_executable(ResourceMonitorService
    ${SERVICE_SOURCES}
    ${SERVICE_HEADERS}
)

# Thêm thư mục include
target_include_directories(ResourceMonitorService PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Liên kết với Common và các thư viện Qt
target_link_libraries(ResourceMonitorService PRIVATE
#     Common
    ${QT_LIBS}
)

# Nếu là Windows, thêm các thư viện Windows cần thiết
if(WIN32)
    target_link_libraries(ResourceMonitorService PRIVATE
        wbemuuid
    )
endif()

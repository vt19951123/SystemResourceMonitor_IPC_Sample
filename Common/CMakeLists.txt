# Tạo thư viện Common
# add_library(Common STATIC
    # include/DataStructures.h
    # include/Constants.h
    # src/DataSerializer.cpp
    # include/DataSerializer.h
# )

# Thêm thư mục include
# target_include_directories(Common PUBLIC
#     ${CMAKE_CURRENT_SOURCE_DIR}/include
# )

# Liên kết với các thư viện Qt
# target_link_libraries(Common PUBLIC ${QT_LIBS})

# Định nghĩa IPC_SOCKET_NAME từ biến của dự án
# target_compile_definitions(Common PUBLIC
#     IPC_SOCKET_NAME="${IPC_SOCKET_NAME}"
# )

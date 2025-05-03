#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>

namespace Common {
namespace Constants {

// Tên socket IPC
// Được định nghĩa trong CMake qua IPC_SOCKET_NAME
const QString IPC_SOCKET_NAME = QString(IPC_SOCKET_NAME);

// Các hằng số liên quan đến thu thập dữ liệu
const int DEFAULT_DATA_COLLECTION_INTERVAL_MS = 1000;      // 1 giây
const int MIN_DATA_COLLECTION_INTERVAL_MS = 500;           // 0.5 giây
const int MAX_DATA_COLLECTION_INTERVAL_MS = 5000;          // 5 giây

// Các hằng số liên quan đến đồ thị
const int MAX_CHART_HISTORY_POINTS = 60;                  // 60 điểm dữ liệu (1 phút với tốc độ 1s/điểm)
const int CHART_UPDATE_INTERVAL_MS = 1000;                // Cập nhật đồ thị mỗi 1 giây

// Giá trị thời gian chờ kết nối IPC
const int IPC_CONNECTION_TIMEOUT_MS = 3000;               // 3 giây

// Kích thước tối đa cho các gói tin IPC
const int MAX_IPC_MESSAGE_SIZE = 1024 * 10;               // 10 KB

// Các khóa JSON cho dữ liệu truyền qua IPC
namespace JsonKeys {
    // Khóa gói tin
    const QString TYPE = "type";
    const QString TIMESTAMP = "timestamp";
    
    // Khóa dữ liệu CPU
    const QString CPU = "cpu";
    const QString CPU_USAGE = "usage";
    const QString CPU_SPEED = "speed";
    
    // Khóa dữ liệu RAM
    const QString MEMORY = "memory";
    const QString MEMORY_TOTAL = "total";
    const QString MEMORY_USED = "used";
    const QString MEMORY_PERCENT = "percent";
    
    // Khóa lệnh
    const QString COMMAND = "command";
    const QString COMMAND_PARAM = "parameter";
}

// Các chuỗi dùng cho loại thông điệp IPC
namespace MessageTypeStrings {
    const QString DATA_UPDATE = "data_update";
    const QString COMMAND = "command";
    const QString RESPONSE = "response";
    const QString ERROR = "error";
}

// Các chuỗi dùng cho loại lệnh
namespace CommandTypeStrings {
    const QString REQUEST_DATA = "request_data";
    const QString SET_INTERVAL = "set_interval";
    const QString START_MONITOR = "start_monitor";
    const QString STOP_MONITOR = "stop_monitor";
}

} // namespace Constants
} // namespace Common

#endif // CONSTANTS_H
#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <QString>
#include <QDateTime>

namespace Common {

/**
 * @brief Cấu trúc dữ liệu CPU
 */
struct CpuData {
    double usagePercent = 0.0;    // Phần trăm sử dụng CPU (0-100)
    double speed = 0.0;           // Tốc độ CPU (GHz)
    
    // Constructor mặc định
    CpuData() = default;
    
    // Constructor với tham số
    CpuData(double usage, double cpuSpeed)
        : usagePercent(usage), speed(cpuSpeed) {}
};

/**
 * @brief Cấu trúc dữ liệu RAM
 */
struct MemoryData {
    double totalMB = 0.0;         // Tổng dung lượng RAM (MB)
    double usedMB = 0.0;          // Dung lượng RAM đã sử dụng (MB)
    double usagePercent = 0.0;    // Phần trăm sử dụng RAM (0-100)
    
    // Constructor mặc định
    MemoryData() = default;
    
    // Constructor với tham số
    MemoryData(double total, double used, double percent)
        : totalMB(total), usedMB(used), usagePercent(percent) {}
    
    // Phương thức tính dung lượng RAM còn trống
    double getFreeMB() const {
        return totalMB - usedMB;
    }
};

/**
 * @brief Cấu trúc dữ liệu hệ thống tổng hợp
 */
struct SystemData {
    QDateTime timestamp;        // Thời điểm thu thập dữ liệu
    CpuData cpu;                // Dữ liệu CPU
    MemoryData memory;          // Dữ liệu RAM
    
    // Constructor mặc định
    SystemData() = default;
    
    // Constructor với tham số
    SystemData(const QDateTime& time, const CpuData& cpuData, const MemoryData& memData)
        : timestamp(time), cpu(cpuData), memory(memData) {}
};

/**
 * @brief Enum định nghĩa các loại thông điệp IPC
 */
enum class MessageType {
    DataUpdate,     // Cập nhật dữ liệu
    Command,        // Lệnh từ UI đến Service
    Response,       // Phản hồi từ Service đến UI
    Error           // Thông báo lỗi
};

/**
 * @brief Enum định nghĩa các loại lệnh có thể gửi từ UI đến Service
 */
enum class CommandType {
    RequestData,    // Yêu cầu dữ liệu mới nhất
    SetInterval,    // Thiết lập khoảng thời gian cập nhật
    StartMonitor,   // Bắt đầu theo dõi
    StopMonitor     // Dừng theo dõi
};

} // namespace Common

#endif // DATASTRUCTURES_H
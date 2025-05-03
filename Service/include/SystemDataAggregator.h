#ifndef SYSTEMDATAAGGREGATOR_H
#define SYSTEMDATAAGGREGATOR_H

#include <QObject>
#include <QDateTime>

// Forward declarations
class CpuDataCollector;
class MemoryDataCollector;

/**
 * @brief Cấu trúc dữ liệu chứa thông tin hệ thống
 */
struct SystemData {
    QDateTime timestamp;          // Thời điểm thu thập dữ liệu
    
    // Dữ liệu CPU
    double cpuUsagePercent = 0.0; // Phần trăm sử dụng CPU
    double cpuSpeed = 0.0;        // Tốc độ CPU (GHz)
    
    // Dữ liệu RAM
    double totalMemory = 0.0;     // Tổng dung lượng RAM (MB)
    double usedMemory = 0.0;      // Dung lượng RAM đã sử dụng (MB)
    double memoryUsagePercent = 0.0; // Phần trăm sử dụng RAM
};

/**
 * @brief Class tổng hợp dữ liệu từ các bộ thu thập dữ liệu khác nhau
 */
class SystemDataAggregator : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     * @param cpuCollector Con trỏ đến bộ thu thập dữ liệu CPU
     * @param memoryCollector Con trỏ đến bộ thu thập dữ liệu RAM
     * @param parent QObject parent
     */
    explicit SystemDataAggregator(
        CpuDataCollector* cpuCollector,
        MemoryDataCollector* memoryCollector,
        QObject *parent = nullptr
    );
    
    /**
     * @brief Thu thập dữ liệu từ tất cả các bộ thu thập
     * @return true nếu thu thập thành công, false nếu thất bại
     */
    bool collectData();
    
    /**
     * @brief Kiểm tra xem đã có dữ liệu hay chưa
     * @return true nếu đã có dữ liệu, false nếu chưa có
     */
    bool hasData() const;
    
    /**
     * @brief Lấy dữ liệu mới nhất
     * @return Cấu trúc SystemData chứa dữ liệu mới nhất
     */
    SystemData getLatestData() const;

private:
    // Con trỏ đến bộ thu thập dữ liệu CPU
    CpuDataCollector* m_cpuCollector;
    
    // Con trỏ đến bộ thu thập dữ liệu RAM
    MemoryDataCollector* m_memoryCollector;
    
    // Dữ liệu hệ thống mới nhất
    SystemData m_latestData;
    
    // Biến đánh dấu đã có dữ liệu hay chưa
    bool m_hasData = false;
};

#endif // SYSTEMDATAAGGREGATOR_H
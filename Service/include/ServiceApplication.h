#ifndef SERVICEAPPLICATION_H
#define SERVICEAPPLICATION_H

#include <QObject>
#include <QTimer>
#include <memory>

// Forward declarations để tối ưu thời gian biên dịch
class CpuDataCollector;
class MemoryDataCollector;
class SystemDataAggregator;
class IpcServerManager;

/**
 * @brief Class chính của ứng dụng service, quản lý các thành phần thu thập dữ liệu và IPC
 */
class ServiceApplication : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     * @param parent QObject parent
     */
    explicit ServiceApplication(QObject *parent = nullptr);

    /**
     * @brief Destructor
     */
    ~ServiceApplication();

    /**
     * @brief Khởi tạo các thành phần của ứng dụng
     * @return true nếu khởi tạo thành công, false nếu thất bại
     */
    bool initialize();

private slots:
    /**
     * @brief Xử lý việc thu thập và gửi dữ liệu mới
     */
    void onDataCollectionTimerTick();

    /**
     * @brief Xử lý khi có client kết nối mới
     */
    void onClientConnected();

    /**
     * @brief Xử lý khi client ngắt kết nối
     */
    void onClientDisconnected();

private:
    // Thời gian giữa các lần thu thập dữ liệu (ms)
    static constexpr int DATA_COLLECTION_INTERVAL = 1000;

    // Thành phần thu thập dữ liệu CPU
    std::unique_ptr<CpuDataCollector> m_cpuDataCollector;

    // Thành phần thu thập dữ liệu RAM
    std::unique_ptr<MemoryDataCollector> m_memoryDataCollector;

    // Thành phần tổng hợp dữ liệu hệ thống
    std::unique_ptr<SystemDataAggregator> m_systemDataAggregator;

    // Thành phần quản lý IPC server
    std::unique_ptr<IpcServerManager> m_ipcServerManager;

    // Timer để thu thập dữ liệu định kỳ
    QTimer m_dataCollectionTimer;

    // Biến đánh dấu trạng thái khởi tạo
    bool m_initialized = false;
};

#endif // SERVICEAPPLICATION_H

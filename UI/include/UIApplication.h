#ifndef UIAPPLICATION_H
#define UIAPPLICATION_H

#include <QObject>
#include <memory>

// Forward declarations để tối ưu thời gian biên dịch
class CpuDataModel;
class MemoryDataModel;
class IpcClientManager;
class UpdateManager;

/**
 * @brief Class chính của ứng dụng UI, quản lý các thành phần và kết nối với service
 */
class UIApplication : public QObject
{
    Q_OBJECT
    
    // Properties cho QML để truy cập trạng thái kết nối
    Q_PROPERTY(bool connected READ isConnected NOTIFY connectionStatusChanged)
    Q_PROPERTY(QString connectionStatus READ getConnectionStatus NOTIFY connectionStatusChanged)

public:
    /**
     * @brief Constructor
     * @param parent QObject parent
     */
    explicit UIApplication(QObject *parent = nullptr);
    
    /**
     * @brief Destructor
     */
    ~UIApplication();
    
    /**
     * @brief Khởi tạo các thành phần của ứng dụng
     * @return true nếu khởi tạo thành công, false nếu thất bại
     */
    bool initialize();
    
    /**
     * @brief Lấy con trỏ đến CpuDataModel
     * @return Con trỏ đến model dữ liệu CPU
     */
    CpuDataModel* getCpuDataModel() const;
    
    /**
     * @brief Lấy con trỏ đến MemoryDataModel
     * @return Con trỏ đến model dữ liệu RAM
     */
    MemoryDataModel* getMemoryDataModel() const;
    
    /**
     * @brief Kiểm tra xem có kết nối đến service hay không
     * @return true nếu đã kết nối, false nếu chưa kết nối
     */
    bool isConnected() const;
    
    /**
     * @brief Lấy trạng thái kết nối dưới dạng chuỗi
     * @return Chuỗi mô tả trạng thái kết nối
     */
    QString getConnectionStatus() const;

public slots:
    /**
     * @brief Thử kết nối lại với service (có thể gọi từ QML)
     */
    Q_INVOKABLE void reconnect();

signals:
    /**
     * @brief Signal phát ra khi trạng thái kết nối thay đổi
     */
    void connectionStatusChanged();

private slots:
    /**
     * @brief Xử lý khi kết nối thành công đến service
     */
    void onConnected();
    
    /**
     * @brief Xử lý khi mất kết nối với service
     */
    void onDisconnected();
    
    /**
     * @brief Xử lý khi nhận được dữ liệu mới từ service
     */
    void onDataReceived();

private:
    // Model dữ liệu CPU
    std::unique_ptr<CpuDataModel> m_cpuDataModel;
    
    // Model dữ liệu RAM
    std::unique_ptr<MemoryDataModel> m_memoryDataModel;
    
    // Thành phần quản lý kết nối IPC client
    std::unique_ptr<IpcClientManager> m_ipcClientManager;
    
    // Thành phần quản lý cập nhật UI
    std::unique_ptr<UpdateManager> m_updateManager;
    
    // Biến đánh dấu trạng thái khởi tạo
    bool m_initialized = false;
    
    // Biến lưu trạng thái kết nối
    bool m_connected = false;
    
    // Chuỗi mô tả trạng thái kết nối
    QString m_connectionStatus = "Disconnected";
};

#endif // UIAPPLICATION_H
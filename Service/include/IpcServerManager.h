#ifndef IPCSERVERMANAGER_H
#define IPCSERVERMANAGER_H

#include <QObject>
#include <QLocalServer>
#include <QLocalSocket>
#include <QList>

// Forward declaration
struct SystemData;

/**
 * @brief Class quản lý server IPC để giao tiếp với client UI
 */
class IpcServerManager : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     * @param parent QObject parent
     */
    explicit IpcServerManager(QObject *parent = nullptr);
    
    /**
     * @brief Destructor
     */
    ~IpcServerManager();
    
    /**
     * @brief Bắt đầu IPC server
     * @return true nếu khởi động thành công, false nếu thất bại
     */
    bool startServer();
    
    /**
     * @brief Dừng IPC server
     */
    void stopServer();
    
    /**
     * @brief Gửi dữ liệu hệ thống đến tất cả các client đã kết nối
     * @param data Dữ liệu hệ thống cần gửi
     * @return true nếu gửi thành công đến ít nhất một client, false nếu không có client nào nhận được dữ liệu
     */
    bool sendDataToClients(const SystemData& data);
    
    /**
     * @brief Kiểm tra xem có client nào đang kết nối hay không
     * @return true nếu có ít nhất một client đang kết nối, false nếu không có client nào
     */
    bool hasConnectedClients() const;

signals:
    /**
     * @brief Signal phát ra khi có client kết nối mới
     */
    void clientConnected();
    
    /**
     * @brief Signal phát ra khi client ngắt kết nối
     */
    void clientDisconnected();

private slots:
    /**
     * @brief Xử lý khi có kết nối mới đến server
     */
    void onNewConnection();
    
    /**
     * @brief Xử lý khi client ngắt kết nối
     */
    void onClientDisconnected();
    
    /**
     * @brief Xử lý lỗi xảy ra với server
     * @param error Loại lỗi
     */
    void onServerError(QAbstractSocket::SocketError error);

private:
    // Server IPC
    QLocalServer m_server;
    
    // Danh sách các client đã kết nối
    QList<QLocalSocket*> m_connectedClients;
    
    // Tên socket sử dụng cho IPC
    QString m_socketName;
};

#endif // IPCSERVERMANAGER_H

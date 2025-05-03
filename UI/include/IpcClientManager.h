#ifndef IPCCLIENTMANAGER_H
#define IPCCLIENTMANAGER_H

#include <QObject>
#include <QLocalSocket>
#include <QJsonObject>

/**
 * @brief Class quản lý client IPC để giao tiếp với service
 */
class IpcClientManager : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     * @param parent QObject parent
     */
    explicit IpcClientManager(QObject *parent = nullptr);
    
    /**
     * @brief Destructor
     */
    ~IpcClientManager();
    
    /**
     * @brief Kết nối đến service thông qua IPC
     * @return true nếu yêu cầu kết nối thành công, false nếu không thể kết nối
     */
    bool connectToService();
    
    /**
     * @brief Ngắt kết nối với service
     */
    void disconnectFromService();
    
    /**
     * @brief Kiểm tra xem đã kết nối đến service hay chưa
     * @return true nếu đã kết nối, false nếu chưa kết nối
     */
    bool isConnected() const;
    
    /**
     * @brief Lấy dữ liệu JSON mới nhất đã nhận được
     * @return Đối tượng JSON chứa dữ liệu mới nhất
     */
    QJsonObject getLatestData() const;

signals:
    /**
     * @brief Signal phát ra khi kết nối thành công đến service
     */
    void connected();
    
    /**
     * @brief Signal phát ra khi ngắt kết nối với service
     */
    void disconnected();
    
    /**
     * @brief Signal phát ra khi nhận được dữ liệu mới từ service
     */
    void dataReceived(const QJsonObject& data);

private slots:
    /**
     * @brief Xử lý khi có dữ liệu mới từ socket
     */
    void onReadyRead();
    
    /**
     * @brief Xử lý khi trạng thái kết nối thay đổi
     * @param state Trạng thái kết nối mới
     */
    void onStateChanged(QLocalSocket::LocalSocketState state);
    
    /**
     * @brief Xử lý khi có lỗi xảy ra với socket
     * @param error Loại lỗi
     */
    void onError(QLocalSocket::LocalSocketError error);

private:
    // Socket IPC
    QLocalSocket m_socket;
    
    // Tên socket sử dụng cho IPC
    QString m_socketName;
    
    // Buffer chứa dữ liệu đang nhận từ socket
    QByteArray m_buffer;
    
    // Dữ liệu JSON mới nhất đã nhận được
    QJsonObject m_latestData;
    
    /**
     * @brief Xử lý dữ liệu thô nhận được từ socket
     * @param data Dữ liệu nhận được
     */
    void processIncomingData(const QByteArray& data);
};

#endif // IPCCLIENTMANAGER_H
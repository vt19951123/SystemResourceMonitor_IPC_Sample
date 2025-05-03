#ifndef UPDATEMANAGER_H
#define UPDATEMANAGER_H

#include <QObject>
#include <QJsonObject>

// Forward declarations
class CpuDataModel;
class MemoryDataModel;
class IpcClientManager;

/**
 * @brief Class quản lý cập nhật dữ liệu từ IPC đến các models
 */
class UpdateManager : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     * @param cpuModel Con trỏ đến model dữ liệu CPU
     * @param memoryModel Con trỏ đến model dữ liệu RAM
     * @param ipcClient Con trỏ đến IPC client manager
     * @param parent QObject parent
     */
    explicit UpdateManager(
        CpuDataModel* cpuModel,
        MemoryDataModel* memoryModel,
        IpcClientManager* ipcClient,
        QObject *parent = nullptr
    );

signals:
    /**
     * @brief Signal phát ra khi nhận được dữ liệu mới
     */
    void dataReceived();

private slots:
    /**
     * @brief Xử lý khi nhận được dữ liệu mới từ IPC
     * @param data Dữ liệu JSON nhận được
     */
    void onIpcDataReceived(const QJsonObject& data);

private:
    // Con trỏ đến model dữ liệu CPU
    CpuDataModel* m_cpuModel;
    
    // Con trỏ đến model dữ liệu RAM
    MemoryDataModel* m_memoryModel;
    
    // Con trỏ đến IPC client manager
    IpcClientManager* m_ipcClient;
    
    /**
     * @brief Cập nhật models với dữ liệu mới
     * @param data Dữ liệu JSON mới
     */
    void updateModels(const QJsonObject& data);
};

#endif // UPDATEMANAGER_H
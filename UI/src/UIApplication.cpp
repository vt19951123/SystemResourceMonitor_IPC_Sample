#include "UIApplication.h"
#include "CpuDataModel.h"
#include "MemoryDataModel.h"
#include "IpcClientManager.h"
#include "UpdateManager.h"
#include <QDebug>

UIApplication::UIApplication(QObject *parent)
    : QObject(parent)
{
    // Constructor implementation
}

UIApplication::~UIApplication()
{
    qInfo() << "UI application shutting down...";
}

bool UIApplication::initialize()
{
    // Tránh khởi tạo lại nếu đã được khởi tạo trước đó
    if (m_initialized) {
        return true;
    }
    
    try {
        // Khởi tạo các models dữ liệu
        qInfo() << "Initializing data models...";
        m_cpuDataModel = std::make_unique<CpuDataModel>();
        m_memoryDataModel = std::make_unique<MemoryDataModel>();
        
        // Khởi tạo IPC client manager
        qInfo() << "Initializing IPC client manager...";
        m_ipcClientManager = std::make_unique<IpcClientManager>();
        
        // Khởi tạo update manager
        qInfo() << "Initializing update manager...";
        m_updateManager = std::make_unique<UpdateManager>(
            m_cpuDataModel.get(),
            m_memoryDataModel.get(),
            m_ipcClientManager.get()
        );
        
        // Kết nối signals và slots
        connect(m_ipcClientManager.get(), &IpcClientManager::connected,
                this, &UIApplication::onConnected);
        
        connect(m_ipcClientManager.get(), &IpcClientManager::disconnected,
                this, &UIApplication::onDisconnected);
        
        connect(m_updateManager.get(), &UpdateManager::dataReceived,
                this, &UIApplication::onDataReceived);
        
        // Kết nối đến service
        qInfo() << "Connecting to service...";
        m_ipcClientManager->connectToService();
        
        m_initialized = true;
        qInfo() << "UI application initialized successfully";
        return true;
    }
    catch (const std::exception& e) {
        qCritical() << "Exception during initialization:" << e.what();
        return false;
    }
    catch (...) {
        qCritical() << "Unknown exception during initialization";
        return false;
    }
}

CpuDataModel* UIApplication::getCpuDataModel() const
{
    return m_cpuDataModel.get();
}

MemoryDataModel* UIApplication::getMemoryDataModel() const
{
    return m_memoryDataModel.get();
}

bool UIApplication::isConnected() const
{
    return m_connected;
}

QString UIApplication::getConnectionStatus() const
{
    return m_connectionStatus;
}

void UIApplication::reconnect()
{
    if (m_ipcClientManager) {
        m_connectionStatus = "Connecting...";
        emit connectionStatusChanged();
        m_ipcClientManager->connectToService();
    }
}

void UIApplication::onConnected()
{
    qInfo() << "Connected to service";
    m_connected = true;
    m_connectionStatus = "Connected";
    emit connectionStatusChanged();
}

void UIApplication::onDisconnected()
{
    qInfo() << "Disconnected from service";
    m_connected = false;
    m_connectionStatus = "Disconnected";
    emit connectionStatusChanged();
}

void UIApplication::onDataReceived()
{
    // Khi nhận được dữ liệu mới, không cần thực hiện gì ở đây
    // UpdateManager đã tự động cập nhật models
}
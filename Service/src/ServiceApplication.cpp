#include "ServiceApplication.h"
#include "CpuDataCollector.h"
#include "MemoryDataCollector.h"
#include "SystemDataAggregator.h"
#include "IpcServerManager.h"
#include <QDebug>

ServiceApplication::ServiceApplication(QObject *parent)
    : QObject(parent)
{
    // Constructor implementation
}

ServiceApplication::~ServiceApplication()
{
    // Dừng timer trước khi hủy đối tượng
    m_dataCollectionTimer.stop();

    qInfo() << "Service application shutting down...";
}

bool ServiceApplication::initialize()
{
    // Tránh khởi tạo lại nếu đã được khởi tạo trước đó
    if (m_initialized) {
        return true;
    }

    try {
        // Khởi tạo các thành phần thu thập dữ liệu
        qInfo() << "Initializing data collectors...";
        m_cpuDataCollector = std::make_unique<CpuDataCollector>();
        m_memoryDataCollector = std::make_unique<MemoryDataCollector>();

        // Khởi tạo thành phần tổng hợp dữ liệu
        qInfo() << "Initializing system data aggregator...";
        m_systemDataAggregator = std::make_unique<SystemDataAggregator>(
            m_cpuDataCollector.get(),
            m_memoryDataCollector.get()
            );

        // Khởi tạo IPC server manager
        qInfo() << "Initializing IPC server manager...";
        m_ipcServerManager = std::make_unique<IpcServerManager>();
        if (!m_ipcServerManager->startServer()) {
            qCritical() << "Failed to start IPC server";
            return false;
        }

        // Kết nối signals và slots
        connect(&m_dataCollectionTimer, &QTimer::timeout,
                this, &ServiceApplication::onDataCollectionTimerTick);

        connect(m_ipcServerManager.get(), &IpcServerManager::clientConnected,
                this, &ServiceApplication::onClientConnected);

        connect(m_ipcServerManager.get(), &IpcServerManager::clientDisconnected,
                this, &ServiceApplication::onClientDisconnected);

        // Bắt đầu timer thu thập dữ liệu
        qInfo() << "Starting data collection timer...";
        m_dataCollectionTimer.start(DATA_COLLECTION_INTERVAL);

        m_initialized = true;
        qInfo() << "Service application initialized successfully";
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

void ServiceApplication::onDataCollectionTimerTick()
{
    // Kiểm tra nếu có client kết nối
    if (!m_ipcServerManager->hasConnectedClients()) {
        // Không có client, chỉ log và không thực hiện thu thập dữ liệu
        qDebug() << "No clients connected, skipping data collection";
        return;
    }

    try {
        // Thu thập dữ liệu mới
        m_systemDataAggregator->collectData();

        // Lấy dữ liệu đã thu thập
        auto systemData = m_systemDataAggregator->getLatestData();

        // Gửi dữ liệu qua IPC
        m_ipcServerManager->sendDataToClients(systemData);
    }
    catch (const std::exception& e) {
        qWarning() << "Error during data collection:" << e.what();
    }
}

void ServiceApplication::onClientConnected()
{
    qInfo() << "Client connected to service";

    // Gửi dữ liệu hiện tại ngay lập tức nếu có
    if (m_systemDataAggregator->hasData()) {
        auto systemData = m_systemDataAggregator->getLatestData();
        m_ipcServerManager->sendDataToClients(systemData);
    }
}

void ServiceApplication::onClientDisconnected()
{
    qInfo() << "Client disconnected from service";
}

#include <QCoreApplication>
#include <QDebug>
#include "ServiceApplication.h"

int main(int argc, char *argv[])
{
    // Tạo ứng dụng dòng lệnh Qt (không có giao diện đồ họa)
    QCoreApplication app(argc, argv);

    // Thiết lập thông tin ứng dụng
    QCoreApplication::setApplicationName("ResourceMonitorService");
    QCoreApplication::setApplicationVersion("1.0.0");
    QCoreApplication::setOrganizationName("YourOrganization");
    QCoreApplication::setOrganizationDomain("yourorganization.com");

    qInfo() << "Starting Resource Monitor Service...";

    // Khởi tạo ứng dụng service
    ServiceApplication serviceApp;
    if (!serviceApp.initialize()) {
        qCritical() << "Failed to initialize service application";
        return 1;
    }

    qInfo() << "Resource Monitor Service started successfully";

    // Bắt đầu vòng lặp sự kiện của ứng dụng
    return app.exec();
}

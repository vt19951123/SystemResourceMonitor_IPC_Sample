#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>
#include "UIApplication.h"
#include "CpuDataModel.h"
#include "MemoryDataModel.h"

int main(int argc, char *argv[])
{
    // Đặt thuộc tính ứng dụng trước khi tạo ứng dụng
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    // Tạo ứng dụng đồ họa Qt
    QGuiApplication app(argc, argv);

    // Thiết lập thông tin ứng dụng
    QGuiApplication::setApplicationName("ResourceMonitorUI");
    QGuiApplication::setApplicationVersion("1.0.0");
    QGuiApplication::setOrganizationName("YourOrganization");
    QGuiApplication::setOrganizationDomain("yourorganization.com");

    qInfo() << "Starting Resource Monitor UI application...";

    // Khởi tạo ứng dụng UI
    UIApplication uiApp;
    if (!uiApp.initialize()) {
        qCritical() << "Failed to initialize UI application";
        return 1;
    }

    // Tạo QML engine
    QQmlApplicationEngine engine;

    // Đăng ký các models với QML engine
    engine.rootContext()->setContextProperty("cpuModel", uiApp.getCpuDataModel());
    engine.rootContext()->setContextProperty("memoryModel", uiApp.getMemoryDataModel());

    // Đăng ký singleton để UI có thể sử dụng các hàm tiện ích
    qmlRegisterSingletonInstance("com.app.uiapp", 1, 0, "UIApplication", &uiApp);

    // Tải file main.qml
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    // Kiểm tra xem QML có được tải thành công hay không
    if (engine.rootObjects().isEmpty()) {
        qCritical() << "Failed to load QML";
        return 1;
    }

    qInfo() << "Resource Monitor UI application started successfully";

    // Bắt đầu vòng lặp sự kiện của ứng dụng
    return app.exec();
}

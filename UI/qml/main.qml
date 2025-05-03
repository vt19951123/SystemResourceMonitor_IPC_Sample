import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Window {
    id: mainWindow

    width: 800
    height: 600
    visible: true
    title: "System Resource Monitor"

    // Sử dụng properties từ UIApplication singleton
    property bool isConnected: UIApplication.connected
    property string connectionStatus: UIApplication.connectionStatus

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 10

        // Header với trạng thái kết nối
        Rectangle {
            Layout.fillWidth: true
            height: 40
            color: isConnected ? "#4CAF50" : "#F44336"
            radius: 5

            RowLayout {
                anchors.fill: parent
                anchors.margins: 10

                Text {
                    text: "System Resource Monitor"
                    font.pixelSize: 16
                    font.bold: true
                    color: "white"
                }

                Item { Layout.fillWidth: true }

                Text {
                    text: "Status: " + connectionStatus
                    font.pixelSize: 14
                    color: "white"
                }

                Button {
                    text: "Reconnect"
                    visible: !isConnected
                    onClicked: UIApplication.reconnect()
                }
            }
        }

        // Nội dung chính với TabBar
        TabBar {
            id: tabBar
            Layout.fillWidth: true

            TabButton {
                text: "CPU"
            }

            TabButton {
                text: "Memory"
            }
        }

        // StackLayout để chuyển đổi giữa các tab
        StackLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            currentIndex: tabBar.currentIndex

            // Tab CPU
            Rectangle {
                color: "#f0f0f0"
                radius: 5

                // Sẽ được thay thế bằng CpuMonitorView
                Text {
                    anchors.centerIn: parent
                    text: "CPU Monitor View will be implemented"
                    font.pixelSize: 18
                }
            }

            // Tab Memory
            Rectangle {
                color: "#f0f0f0"
                radius: 5

                // Sẽ được thay thế bằng MemoryMonitorView
                Text {
                    anchors.centerIn: parent
                    text: "Memory Monitor View will be implemented"
                    font.pixelSize: 18
                }
            }
        }

        // Footer
        Text {
            Layout.fillWidth: true
            text: "System Resource Monitor - v1.0.0"
            font.pixelSize: 12
            color: "#666666"
            horizontalAlignment: Text.AlignRight
        }
    }
}

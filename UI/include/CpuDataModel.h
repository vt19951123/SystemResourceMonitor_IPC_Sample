#ifndef CPUDATAMODEL_H
#define CPUDATAMODEL_H

#include <QObject>
#include <QVector>
#include <QPair>

/**
 * @brief Model dữ liệu CPU cho QML
 */
class CpuDataModel : public QObject
{
    Q_OBJECT
    
    // Properties cho QML
    Q_PROPERTY(double cpuUsage READ getCpuUsage NOTIFY cpuUsageChanged)
    Q_PROPERTY(double cpuSpeed READ getCpuSpeed NOTIFY cpuSpeedChanged)
    Q_PROPERTY(QVector<QPointF> usageHistory READ getUsageHistory NOTIFY usageHistoryChanged)

public:
    /**
     * @brief Constructor
     * @param parent QObject parent
     */
    explicit CpuDataModel(QObject *parent = nullptr);
    
    /**
     * @brief Lấy phần trăm sử dụng CPU hiện tại
     * @return Phần trăm sử dụng CPU (0-100)
     */
    double getCpuUsage() const;
    
    /**
     * @brief Lấy tốc độ CPU hiện tại
     * @return Tốc độ CPU (GHz)
     */
    double getCpuSpeed() const;
    
    /**
     * @brief Lấy lịch sử sử dụng CPU
     * @return Vector các điểm (thời gian, giá trị) cho đồ thị
     */
    QVector<QPointF> getUsageHistory() const;
    
    /**
     * @brief Cập nhật dữ liệu CPU
     * @param usage Phần trăm sử dụng CPU (0-100)
     * @param speed Tốc độ CPU (GHz)
     */
    void updateData(double usage, double speed);

signals:
    /**
     * @brief Signal phát ra khi phần trăm sử dụng CPU thay đổi
     */
    void cpuUsageChanged();
    
    /**
     * @brief Signal phát ra khi tốc độ CPU thay đổi
     */
    void cpuSpeedChanged();
    
    /**
     * @brief Signal phát ra khi lịch sử sử dụng CPU thay đổi
     */
    void usageHistoryChanged();

private:
    // Số điểm dữ liệu tối đa lưu trong lịch sử
    static constexpr int MAX_HISTORY_SIZE = 60;
    
    // Phần trăm sử dụng CPU hiện tại
    double m_cpuUsage = 0.0;
    
    // Tốc độ CPU hiện tại (GHz)
    double m_cpuSpeed = 0.0;
    
    // Lịch sử sử dụng CPU (thời gian, giá trị)
    QVector<QPointF> m_usageHistory;
};

#endif // CPUDATAMODEL_H
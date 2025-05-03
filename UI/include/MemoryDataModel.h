#ifndef MEMORYDATAMODEL_H
#define MEMORYDATAMODEL_H

#include <QObject>
#include <QVector>
#include <QPair>

/**
 * @brief Model dữ liệu RAM cho QML
 */
class MemoryDataModel : public QObject
{
    Q_OBJECT
    
    // Properties cho QML
    Q_PROPERTY(double totalMemory READ getTotalMemory NOTIFY totalMemoryChanged)
    Q_PROPERTY(double usedMemory READ getUsedMemory NOTIFY usedMemoryChanged)
    Q_PROPERTY(double memoryUsage READ getMemoryUsage NOTIFY memoryUsageChanged)
    Q_PROPERTY(double freeMemory READ getFreeMemory NOTIFY memoryDataChanged)
    Q_PROPERTY(QVector<QPointF> usageHistory READ getUsageHistory NOTIFY usageHistoryChanged)

public:
    /**
     * @brief Constructor
     * @param parent QObject parent
     */
    explicit MemoryDataModel(QObject *parent = nullptr);
    
    /**
     * @brief Lấy tổng dung lượng RAM
     * @return Tổng dung lượng RAM (MB)
     */
    double getTotalMemory() const;
    
    /**
     * @brief Lấy dung lượng RAM đã sử dụng
     * @return Dung lượng RAM đã sử dụng (MB)
     */
    double getUsedMemory() const;
    
    /**
     * @brief Lấy phần trăm sử dụng RAM
     * @return Phần trăm sử dụng RAM (0-100)
     */
    double getMemoryUsage() const;
    
    /**
     * @brief Lấy dung lượng RAM còn trống
     * @return Dung lượng RAM còn trống (MB)
     */
    double getFreeMemory() const;
    
    /**
     * @brief Lấy lịch sử sử dụng RAM
     * @return Vector các điểm (thời gian, giá trị) cho đồ thị
     */
    QVector<QPointF> getUsageHistory() const;
    
    /**
     * @brief Cập nhật dữ liệu RAM
     * @param total Tổng dung lượng RAM (MB)
     * @param used Dung lượng RAM đã sử dụng (MB)
     * @param percent Phần trăm sử dụng RAM (0-100)
     */
    void updateData(double total, double used, double percent);

signals:
    /**
     * @brief Signal phát ra khi tổng dung lượng RAM thay đổi
     */
    void totalMemoryChanged();
    
    /**
     * @brief Signal phát ra khi dung lượng RAM đã sử dụng thay đổi
     */
    void usedMemoryChanged();
    
    /**
     * @brief Signal phát ra khi phần trăm sử dụng RAM thay đổi
     */
    void memoryUsageChanged();
    
    /**
     * @brief Signal phát ra khi bất kỳ dữ liệu RAM nào thay đổi
     */
    void memoryDataChanged();
    
    /**
     * @brief Signal phát ra khi lịch sử sử dụng RAM thay đổi
     */
    void usageHistoryChanged();

private:
    // Số điểm dữ liệu tối đa lưu trong lịch sử
    static constexpr int MAX_HISTORY_SIZE = 60;
    
    // Tổng dung lượng RAM (MB)
    double m_totalMemory = 0.0;
    
    // Dung lượng RAM đã sử dụng (MB)
    double m_usedMemory = 0.0;
    
    // Phần trăm sử dụng RAM
    double m_memoryUsage = 0.0;
    
    // Lịch sử sử dụng RAM (thời gian, giá trị)
    QVector<QPointF> m_usageHistory;
};

#endif // MEMORYDATAMODEL_H
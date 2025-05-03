#ifndef MEMORYDATACOLLECTOR_H
#define MEMORYDATACOLLECTOR_H

#include <QObject>

/**
 * @brief Class thu thập dữ liệu RAM từ hệ thống
 */
class MemoryDataCollector : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     * @param parent QObject parent
     */
    explicit MemoryDataCollector(QObject *parent = nullptr);
    
    /**
     * @brief Destructor
     */
    ~MemoryDataCollector();
    
    /**
     * @brief Thu thập dữ liệu RAM mới
     * @return true nếu thu thập thành công, false nếu thất bại
     */
    bool collectData();
    
    /**
     * @brief Lấy tổng dung lượng RAM (MB)
     * @return Tổng dung lượng RAM theo MB
     */
    double getTotalMemory() const;
    
    /**
     * @brief Lấy dung lượng RAM đã sử dụng (MB)
     * @return Dung lượng RAM đã sử dụng theo MB
     */
    double getUsedMemory() const;
    
    /**
     * @brief Lấy phần trăm sử dụng RAM
     * @return Phần trăm sử dụng RAM (0-100)
     */
    double getMemoryUsagePercent() const;

private:
    // Tổng dung lượng RAM (MB)
    double m_totalMemory = 0.0;
    
    // Dung lượng RAM đã sử dụng (MB)
    double m_usedMemory = 0.0;
    
    // Phần trăm sử dụng RAM
    double m_usagePercent = 0.0;
};

#endif // MEMORYDATACOLLECTOR_H
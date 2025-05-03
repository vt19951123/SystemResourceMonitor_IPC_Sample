#ifndef DATASERIALIZER_H
#define DATASERIALIZER_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include "DataStructures.h"

namespace Common {

/**
 * @brief Class cung cấp các phương thức chuyển đổi dữ liệu giữa các định dạng
 */
class DataSerializer
{
public:
    /**
     * @brief Chuyển đổi dữ liệu hệ thống thành đối tượng JSON
     * @param data Dữ liệu hệ thống cần chuyển đổi
     * @return Đối tượng JSON chứa dữ liệu hệ thống
     */
    static QJsonObject systemDataToJson(const SystemData& data);
    
    /**
     * @brief Chuyển đổi đối tượng JSON thành dữ liệu hệ thống
     * @param json Đối tượng JSON cần chuyển đổi
     * @return Dữ liệu hệ thống từ JSON
     */
    static SystemData jsonToSystemData(const QJsonObject& json);
    
    /**
     * @brief Chuyển đổi đối tượng JSON thành dữ liệu nhị phân để truyền qua IPC
     * @param json Đối tượng JSON cần chuyển đổi
     * @return Dữ liệu nhị phân
     */
    static QByteArray jsonToByteArray(const QJsonObject& json);
    
    /**
     * @brief Chuyển đổi dữ liệu nhị phân thành đối tượng JSON
     * @param data Dữ liệu nhị phân cần chuyển đổi
     * @return Đối tượng JSON từ dữ liệu nhị phân
     */
    static QJsonObject byteArrayToJson(const QByteArray& data);
    
    /**
     * @brief Tạo thông điệp cập nhật dữ liệu
     * @param data Dữ liệu hệ thống cần gửi
     * @return Dữ liệu nhị phân chứa thông điệp cập nhật
     */
    static QByteArray createDataUpdateMessage(const SystemData& data);
    
    /**
     * @brief Tạo thông điệp lệnh
     * @param commandType Loại lệnh cần gửi
     * @param parameter Tham số cho lệnh (tùy chọn)
     * @return Dữ liệu nhị phân chứa thông điệp lệnh
     */
    static QByteArray createCommandMessage(CommandType commandType, const QJsonValue& parameter = QJsonValue());
    
    /**
     * @brief Lấy loại thông điệp từ đối tượng JSON
     * @param json Đối tượng JSON cần kiểm tra
     * @return Loại thông điệp
     */
    static MessageType getMessageType(const QJsonObject& json);
    
    /**
     * @brief Lấy loại lệnh từ đối tượng JSON
     * @param json Đối tượng JSON cần kiểm tra
     * @return Loại lệnh
     */
    static CommandType getCommandType(const QJsonObject& json);
};

} // namespace Common

#endif // DATASERIALIZER_H
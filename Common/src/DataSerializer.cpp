#include "DataSerializer.h"
#include "Constants.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QDateTime>

namespace Common {

QJsonObject DataSerializer::systemDataToJson(const SystemData& data)
{
    // Tạo đối tượng JSON chứa dữ liệu hệ thống
    QJsonObject json;
    
    // Thêm thời gian
    json[Constants::JsonKeys::TIMESTAMP] = data.timestamp.toMSecsSinceEpoch();
    
    // Thêm dữ liệu CPU
    QJsonObject cpuJson;
    cpuJson[Constants::JsonKeys::CPU_USAGE] = data.cpu.usagePercent;
    cpuJson[Constants::JsonKeys::CPU_SPEED] = data.cpu.speed;
    json[Constants::JsonKeys::CPU] = cpuJson;
    
    // Thêm dữ liệu RAM
    QJsonObject memoryJson;
    memoryJson[Constants::JsonKeys::MEMORY_TOTAL] = data.memory.totalMB;
    memoryJson[Constants::JsonKeys::MEMORY_USED] = data.memory.usedMB;
    memoryJson[Constants::JsonKeys::MEMORY_PERCENT] = data.memory.usagePercent;
    json[Constants::JsonKeys::MEMORY] = memoryJson;
    
    return json;
}

SystemData DataSerializer::jsonToSystemData(const QJsonObject& json)
{
    SystemData data;
    
    // Lấy thời gian
    qint64 timestamp = json[Constants::JsonKeys::TIMESTAMP].toVariant().toLongLong();
    data.timestamp = QDateTime::fromMSecsSinceEpoch(timestamp);
    
    // Lấy dữ liệu CPU
    QJsonObject cpuJson = json[Constants::JsonKeys::CPU].toObject();
    data.cpu.usagePercent = cpuJson[Constants::JsonKeys::CPU_USAGE].toDouble();
    data.cpu.speed = cpuJson[Constants::JsonKeys::CPU_SPEED].toDouble();
    
    // Lấy dữ liệu RAM
    QJsonObject memoryJson = json[Constants::JsonKeys::MEMORY].toObject();
    data.memory.totalMB = memoryJson[Constants::JsonKeys::MEMORY_TOTAL].toDouble();
    data.memory.usedMB = memoryJson[Constants::JsonKeys::MEMORY_USED].toDouble();
    data.memory.usagePercent = memoryJson[Constants::JsonKeys::MEMORY_PERCENT].toDouble();
    
    return data;
}

QByteArray DataSerializer::jsonToByteArray(const QJsonObject& json)
{
    QJsonDocument doc(json);
    return doc.toJson(QJsonDocument::Compact);
}

QJsonObject DataSerializer::byteArrayToJson(const QByteArray& data)
{
    QJsonDocument doc = QJsonDocument::fromJson(data);
    return doc.object();
}

QByteArray DataSerializer::createDataUpdateMessage(const SystemData& data)
{
    QJsonObject json = systemDataToJson(data);
    
    // Thêm loại thông điệp
    json[Constants::JsonKeys::TYPE] = Constants::MessageTypeStrings::DATA_UPDATE;
    
    return jsonToByteArray(json);
}

QByteArray DataSerializer::createCommandMessage(CommandType commandType, const QJsonValue& parameter)
{
    QJsonObject json;
    
    // Thêm loại thông điệp
    json[Constants::JsonKeys::TYPE] = Constants::MessageTypeStrings::COMMAND;
    
    // Thêm thời gian
    json[Constants::JsonKeys::TIMESTAMP] = QDateTime::currentDateTime().toMSecsSinceEpoch();
    
    // Thêm loại lệnh
    switch (commandType) {
        case CommandType::RequestData:
            json[Constants::JsonKeys::COMMAND] = Constants::CommandTypeStrings::REQUEST_DATA;
            break;
        case CommandType::SetInterval:
            json[Constants::JsonKeys::COMMAND] = Constants::CommandTypeStrings::SET_INTERVAL;
            break;
        case CommandType::StartMonitor:
            json[Constants::JsonKeys::COMMAND] = Constants::CommandTypeStrings::START_MONITOR;
            break;
        case CommandType::StopMonitor:
            json[Constants::JsonKeys::COMMAND] = Constants::CommandTypeStrings::STOP_MONITOR;
            break;
    }
    
    // Thêm tham số nếu có
    if (!parameter.isNull()) {
        json[Constants::JsonKeys::COMMAND_PARAM] = parameter;
    }
    
    return jsonToByteArray(json);
}

MessageType DataSerializer::getMessageType(const QJsonObject& json)
{
    QString typeStr = json[Constants::JsonKeys::TYPE].toString();
    
    if (typeStr == Constants::MessageTypeStrings::DATA_UPDATE) {
        return MessageType::DataUpdate;
    } else if (typeStr == Constants::MessageTypeStrings::COMMAND) {
        return MessageType::Command;
    } else if (typeStr == Constants::MessageTypeStrings::RESPONSE) {
        return MessageType::Response;
    } else if (typeStr == Constants::MessageTypeStrings::ERROR) {
        return MessageType::Error;
    } else {
        // Mặc định trả về Error nếu không nhận dạng được loại
        return MessageType::Error;
    }
}

CommandType DataSerializer::getCommandType(const QJsonObject& json)
{
    QString commandStr = json[Constants::JsonKeys::COMMAND].toString();
    
    if (commandStr == Constants::CommandTypeStrings::REQUEST_DATA) {
        return CommandType::RequestData;
    } else if (commandStr == Constants::CommandTypeStrings::SET_INTERVAL) {
        return CommandType::SetInterval;
    } else if (commandStr == Constants::CommandTypeStrings::START_MONITOR) {
        return CommandType::StartMonitor;
    } else if (commandStr == Constants::CommandTypeStrings::STOP_MONITOR) {
        return CommandType::StopMonitor;
    } else {
        // Mặc định trả về RequestData nếu không nhận dạng được loại
        return CommandType::RequestData;
    }
}

} // namespace Common
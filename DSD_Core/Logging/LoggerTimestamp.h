//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 04.11.2017
//

#ifndef DSD_GAMEENGINE_LOGGERTIMESTAMPTYPE_H
#define DSD_GAMEENGINE_LOGGERTIMESTAMPTYPE_H

#include <chrono>
#include <string>

/**
 * @addtogroup Logger
 * @{
 */

/**
 * @brief Class defining timestamp format
 */
class LoggerTimestamp
{
public:
    /**
     * Defines timestamp formats
     */
    enum Type
    {
        ENGINE_LOCAL_TIME, ///< Time from engine start
        GLOBAL_TIME ///< System time
    };

    /**
     * Constructor
     * @param type Defines timestamp format
     */
    explicit LoggerTimestamp(const LoggerTimestamp::Type& type) :
            m_engineLocalTime(std::chrono::steady_clock::now()),
            m_globalTime(std::chrono::system_clock::now()),
            m_type(type) {}

    /**
     * @brief Returns string representation of timestamp
     */
    std::string GetString() const
    {
        switch (m_type)
        {
            case ENGINE_LOCAL_TIME:
                return EngineLocalTimeString();
            case GLOBAL_TIME:
                return GlobalTimeString();
        }
    }

private:
    std::string EngineLocalTimeString() const
    {
        std::chrono::duration<double> engineLocalTime = m_engineLocalTime - m_initTimePoint;
        auto diffM = std::chrono::duration_cast<std::chrono::minutes>(engineLocalTime);
        auto diffH = std::chrono::duration_cast<std::chrono::hours>(engineLocalTime);

        std::string result = std::to_string(diffH.count()) + ":" +
                             std::to_string(diffM.count() - diffH.count()*60) + ":" +
                             std::to_string(engineLocalTime.count() - diffM.count()*60);
        return result;
    }

    std::string GlobalTimeString() const
    {
        std::time_t time = std::chrono::system_clock::to_time_t(m_globalTime);
        char str[25];
        std::strftime(str, sizeof(str), "%F %T", localtime(&time));
        return std::string(str);
    }

    const LoggerTimestamp::Type m_type;
    const std::chrono::steady_clock::time_point m_engineLocalTime;
    const std::chrono::system_clock::time_point m_globalTime;
    static std::chrono::steady_clock::time_point m_initTimePoint;
};

/**
 * @}
 */

#endif //DSD_GAMEENGINE_LOGGERTIMESTAMPTYPE_H

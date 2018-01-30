//
//  log-request.h
//  Residue
//
//  Copyright © 2017 Muflihun Labs
//

#ifndef LogRequest_h
#define LogRequest_h

#include "include/log.h"
#include "src/core/request.h"
#include "src/core/json-object.h"

namespace residue {

///
/// A simple representation of log request field and default value
///
template<typename TDefaultValue>
struct LogRequestField
{
    const char* name;
    TDefaultValue defaultValue;
};

static const LogRequestField<std::string> LogRequestFieldToken = { "token", "" };
static const LogRequestField<unsigned long> LogRequestFieldDateTime = { "datetime", 0UL };
static const LogRequestField<el::base::type::string_t> LogRequestFieldMessage = { "msg", ELPP_LITERAL("") };
static const LogRequestField<std::string> LogRequestFieldLogger = { "logger", "default" };
static const LogRequestField<std::string> LogRequestFieldApplicationName = { "app", "" };
static const LogRequestField<std::string> LogRequestFieldFunction = { "func", "" };
static const LogRequestField<std::string> LogRequestFieldFile = { "file", "" };
static const LogRequestField<std::string> LogRequestFieldThreadId = { "thread", "" };
static const LogRequestField<el::base::type::LineNumber> LogRequestFieldLine = { "line",
    static_cast<el::base::type::LineNumber>(0) };
static const LogRequestField<el::base::type::VerboseLevel> LogRequestFieldVLevel = { "vlevel",
    static_cast<el::base::type::VerboseLevel>(9) };
static const LogRequestField<el::base::type::EnumType> LogRequestFieldLevel = { "level",
    static_cast<el::base::type::EnumType>(el::Level::Unknown) };

///
/// \brief Request to write log
///
class LogRequest final : public Request
{
public:
    using MillisecondsEpoch = unsigned long;

    LogRequest(const Configuration* conf);

    std::string formattedDatetime(const char* format,
                                  const el::base::MillisecondsWidth* msWidth) const;

    inline const LogRequest::MillisecondsEpoch& datetime() const
    {
        return m_datetime;
    }

    inline const el::Level& level() const
    {
        return m_level;
    }

    inline const std::string& token() const
    {
        return m_token;
    }

    inline const el::base::type::string_t& msg() const
    {
        return m_msg;
    }

    inline const std::string& clientId() const
    {
        return m_clientId;
    }

    inline const std::string& loggerId() const
    {
        return m_loggerId;
    }

    inline const std::string& filename() const
    {
        return m_filename;
    }

    inline const std::string& function() const
    {
        return m_function;
    }

    inline const std::string& threadId() const
    {
        return m_threadId;
    }

    inline const std::string& threadName() const
    {
        return m_threadName;
    }

    inline const std::string& applicationName() const
    {
        return m_applicationName;
    }

    inline const el::base::type::LineNumber& lineNumber() const
    {
        return m_lineNumber;
    }

    inline const el::base::type::VerboseLevel& verboseLevel() const
    {
        return m_verboseLevel;
    }

    inline bool isValid() const
    {
        return m_isValid;
    }

    inline void setClientId(const std::string& clientId)
    {
        m_clientId = clientId;
    }

    inline bool isBulk()
    {
        return Request::isValid() && !m_jsonObject.jsonStr().empty() && m_jsonObject.jsonStr().at(0) == '[';
    }

    bool deserialize(std::string&& json);
    bool validateTimestamp() const override;

private:
    template <typename T>
    inline T resolveValue(JsonObject *packet, const LogRequestField<T>* requestType) const
    {
        return packet->get<T>(requestType->name, requestType->defaultValue);
    }

    std::string m_clientId;
    std::string m_token;
    LogRequest::MillisecondsEpoch m_datetime;
    el::base::type::string_t m_msg;
    std::string m_loggerId;
    std::string m_filename;
    std::string m_function;
    std::string m_threadId;
    std::string m_threadName;
    std::string m_applicationName;
    el::Level m_level;
    el::base::type::LineNumber m_lineNumber;
    el::base::type::VerboseLevel m_verboseLevel;

    bool m_isValid;
};
}
#endif /* LogRequest_h */
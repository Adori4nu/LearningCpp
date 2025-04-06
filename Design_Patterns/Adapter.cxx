#include <iostream>
#include <string>

class JsonLogger
{
public:
    virtual void logMessage(const std::string &message) = 0;
};

class XmlLogger
{
public:
    void log(const std::string &xmlMessage)
    {
        std::cout << xmlMessage << std::endl;
    }
};

class LoggerAdapter: public JsonLogger
{
    XmlLogger xmlLogger;

public:

    LoggerAdapter(const XmlLogger &xmlLogger) : xmlLogger{xmlLogger} {}

    void logMessage(const std::string &message) override
    {
        xmlLogger.log(message);
    }
};

auto main() -> int
{
    LoggerAdapter logger{ XmlLogger() };

    logger.logMessage("<message>hello</message>");

    return 0;
}
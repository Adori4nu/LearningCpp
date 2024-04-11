#include <iostream>
#include <vector>

class Log
{
public:
    enum Level
    {
        LevelError = 0, LevelWarining, LevelInfo
    };
private:
    Level m_LogLevel = LevelInfo;
public:
    void SetLevel(Level level)
    {
        m_LogLevel = level;
    }

    void Error(const char* message)
    {
        if (m_LogLevel >= LevelError)
            std::cout << "[ERROR]: "<< message << std::endl;
    }

    void Warn(const char* message)
    {
        if (m_LogLevel >= LevelWarining)
            std::cout << "[WARNING]: "<< message << std::endl;
    }

    void Info(const char* message)
    {
        if (m_LogLevel >= LevelInfo)
            std::cout << "[INFO]: "<< message << std::endl;
    }
};

#include <map>
#include <type_traits>
#include <utility>

int main(ParamWraper& bootParams)
{
    enum class checkT
    {
        a,
        i,
        i_e
    };

    Log log;
    log.SetLevel(Log::LevelError);
    log.Error("Hello Darknes!");
    log.Warn("Hello Darknes!");
    log.Info("Hello Darknes!");

    size_t params_count = bootParams.getArgsCount();

    //std::vector<const char*> consol_params;
    std :: vector<std :: remove_cvref_t<decltype(bootParams.getParam(std :: declval<std :: size_t>()))> > console_params;
    console_params.reserve(params_count);

    for (size_t i = 0; i < params_count; ++i)
    {
        //consol_params.at(i) = bootParams.getParam(i);
        consol_params.emplace_back(bootParams.getParam(i));   
    }

    static std :: map string_mapping =
    {
        std :: pair{"a", checkT :: a},
        std :: pair{"i", checkT :: i},
        std :: pair("i_e", checkT :: i_e)
    };

    for (const auto& param : console_params)
    {
        switch (string_mapping.find(param)) // or add
        {
        case /* constant-expression */:
            /* code */
            break;
        
        default:
            break;
        }
    }
    
    
}
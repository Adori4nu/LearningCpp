#include "quickMath.cpp"
#include "parser.cpp"
#include <cstring>

#define MultiplyR Multiply
#define LOG(x) std::cout << x << std::endl

// void Increment(int value)
// {
//     value++;
//     LOG(value);
// }
// Pass by reference
void Increment(int& value)
{
    value++;
    LOG(value);
}
// Pass by pointer
// void Increment(int* value)
// {
//     (*value)++;
//     LOG(*value);
// }

class Player
{
public:
    int x, y;
private:
    int speed;
public:
    void SetSpeed(int speed) { Player::speed = speed; }

    inline int GetSpeed() { return speed; }
};

struct Vec2
{
    int x, y;

    void Add(const Vec2& other)
    {
        x += other.x;
        y += other.y;
    }
};

void Move(Player& player, int xa, int ya)
{
    player.x += xa * player.GetSpeed();
    player.y += ya * player.GetSpeed();
}

class Log
{
public:
    const int LogLevelError = 0;
    const int LogLevelWarning = 1;
    const int LogLevelInfo = 2;
private:
    int m_LogLevel = LogLevelInfo;
public:
    void SetLevel(int level)
    {
        m_LogLevel = level;
    }

    void Error(const char* message)
    {
        if (m_LogLevel >= LogLevelError)
            std::cout << "[ERROR]: "<< message << std::endl;
    }

    void Warn(const char* message)
    {
        if (m_LogLevel >= LogLevelWarning)
            std::cout << "[WARNING]: "<< message << std::endl;
    }

    void Info(const char* message)
    {
        if (m_LogLevel >= LogLevelInfo)
            std::cout << "[INFO]: "<< message << std::endl;
    }
};

int main()
{
    // pointers
    int var = 8;
    int* ptr = &var;
    *ptr = 10;
    LOG(var);
    // pointer to array of chars
    char* buffer = new char[8];
    memset(buffer, 0, 8);

    // pointer to char pointer
    char** ptrPtr = &buffer;

    delete[] buffer;

    // reference
    int a = 5;
    // For passing by value or reference
    Increment(a);
    // For passing by pointer
    // Increment(&a);
    LOG(a);
    int& ref = a;
    ref = 2;
    LOG(a);

    int b = 8;
    // pointer to address of a
    int* ref2 = &a;
    // changing value of what is ref2 pointing to 9
    *ref2 = 9;
    // changing to what ref2 is pointing to to adress of b
    ref2 = &b;
    // changing value of what is ref2 pointing to 1
    *ref2 = 1;

    {
        int PlayerX0, PlayerY0;
        int PlayerSpeed0 = 2;

        int PlayerX1, PlayerY1;
        int PlayerSpeed1 = 2;

        Player player;
        // x is private we can not access it directly outside class
        // player.x = 5;
        player.SetSpeed(5);
        Move(player, 1, -1);

    }

    Log log;
    log.SetLevel(log.LogLevelWarning);
    log.Error("Hello Darknes!");
    log.Warn("Hello Darknes!");
    log.Info("Hello Darknes!");
    std::cout << "Hello world!" << std::endl;
    std::cin.get();
    std::cout << MultiplyR(2,2);
    std::cout << Parser::parse();
}
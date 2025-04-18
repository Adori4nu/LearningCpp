#include "quickMath.cpp"
#include "parser.cpp"
#include "static.cpp"
#include "entity.hpp"
#include "player.hpp"
#include <cstring>
#include "Vector.hpp"
#include "Stack.hpp"

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
    enum Level
    {
        LevelError = 0, LevelWarining, LevelInfo
    };
    // const int LogLevelError = 0;
    // const int LogLevelWarning = 1;
    // const int LogLevelInfo = 2;
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

extern int s_Variable;

struct Entity
{
    static int x,y;

    static void Print()
    {
        std::cout << x << ", " << y << std::endl;
    }
};

int Entity::x;
int Entity::y;

void PrintName (EntityVirtual* entity)
{
    std::cout << entity->GetName() << std::endl;
}


template<typename T>
void PrintVector(const Vector<T>& vector)
{
    for (size_t i = 0; i < vector.Size(); i++)
        std::cout << vector[i] << "\t";

    std::cout << std::endl << "-----------------------------\n";
}

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
    log.SetLevel(Log::LevelError);
    log.Error("Hello Darknes!");
    log.Warn("Hello Darknes!");
    log.Info("Hello Darknes!");

    // static outside the class means only for this translation
    // unit "cpp" file if it's not including other cpp files basicly like private var
    std::cout << "External static var:" << s_Variable << std::endl;

    Entity e;
    e.x = 2;
    e.y = 3;

    Entity e1;

    Entity::x = 6;
    Entity::y = 9;

    e.Print();
    Entity::Print();

    EntityClass Ec;
    std::cout << Ec.X << std::endl;
    Ec.Print();

    // Won't work because we have pure virtual function that is not implemented
    // EntityVirtual* ev = new EntityVirtual();
    EntityVirtual* ev = new PlayerVirtual("");
    std::cout << ev->GetName() << std::endl;

    PlayerVirtual* pv = new PlayerVirtual("Cherno");
    std::cout << pv->GetName() << std::endl;

    EntityVirtual* pev = new PlayerVirtual("AK");
    std::cout << pev->GetName() << std::endl;

    int example[5];
    int* ptrEx = example;
    for (int i = 0; i < 5; i++)
    {
        example[i] = 2;
    }
    example[2] = 5;
    *(ptrEx + 2) = 6;
    *(int*)((char*)ptrEx + 8) = 69;
    int* another = new int[5];
    delete[] another;

    // std::cout << "Hello world!" << std::endl;
    std::cin.get();
    std::cout << MultiplyR(2,2);
    std::cout << Parser::parse();

    Vector<int> my_vec;
    my_vec.EmplaceBack(1);
    my_vec.EmplaceBack(2);
    my_vec.EmplaceBack(3);

    Vector<std::string> my_vec_of_strings;
    my_vec_of_strings.EmplaceBack("KxZ");
    my_vec_of_strings.EmplaceBack("KxZ");
    my_vec_of_strings.EmplaceBack("AxZ");
    
    std::cin.get();

    PrintVector(my_vec);
    PrintVector(my_vec_of_strings);

    for (Vector<int>::Iterator it = my_vec.begin(); it != my_vec.end(); it++)
    {
        std::cout << *it << std::endl;
    }

    Stack<int> my_stk;
    my_stk.push(5);

    std::cout << "My stack peek: " << my_stk.peek() << std::endl;
    my_stk.push(42);
    my_stk.push(69);
    std::cout << "My stack peek: " << my_stk.peek() << std::endl;
    std::cout << "My stack pop: " << my_stk.pop() << std::endl;
    std::cout << "My stack peek: " << my_stk.peek() << std::endl;
}
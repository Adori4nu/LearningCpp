#include <iostream>

#pragma region orange struct to float
struct Orange
{
    operator float() { return 5.5f; }
};

void PrintFloat(float value)
{
    std::cout << value << std::endl;
}
#pragma endregion

#pragma region scoped_ptr example
template<typename T>
class ScopedPtr
{
    T* m_Ptr{ nullptr };

public:
    ScopedPtr() = default;
    ScopedPtr(T* ptr) : m_Ptr(ptr) {}
    ~ScopedPtr() { delete m_Ptr; }

    bool IsValid() const { return m_Ptr != nullptr; }

    T* Get() { return m_Ptr; }
    const T* Get() const { return m_Ptr; }
    operator bool() const { return IsValid(); }
};

struct Entity
{
    float X = 0.0f, Y = 0.0f;
};

void ProcessEntity(const ScopedPtr<Entity>& e)
{
    if (e)
    {
        std::cout << "Conversion operator work example" << std::endl;
    }
}

void ProcessEntity(ScopedPtr<Entity>& e)
{
    if (e)
    {
        std::cout << "Conversion operator work example" << std::endl;
    }
}
#pragma endregion

int main()
{
    Orange orange;

    std::cout << float(orange) << std::endl;
    PrintFloat(orange);

    ScopedPtr<Entity> e = new Entity();
    Entity* entity = new Entity();

    delete entity;
    entity = nullptr;

    ProcessEntity(e);

    return 0;
}
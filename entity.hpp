#include <iostream>

class EntityClass
{
public:
    float X, Y;

    EntityClass()
    {
        X = 0.0f;
        Y = 0.0f;
    }

    EntityClass(float x, float y)
    {
        X = x;
        Y = y;
    }

    ~EntityClass()
    {
    }

    void Print()
    {
        std::cout << X << ", " << Y << std::endl;
    }

    void Move(float xa, float ya)
    {
        X += xa;
        Y += ya;
    }
};
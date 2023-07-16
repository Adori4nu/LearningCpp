#include <iostream>

int main()
{
    std::cout << "result : " << [](double a, double b){
        return a + b;
    }(10.0, 69.9) << std::endl; // anonymous 1 time use

    // with a name handle for multiple uses return type can be omited because will be deduced
    auto func = [](auto a, auto b){
        return a + b;
    };

    // this will return an int
    auto func1 = [](auto a, auto b)-> int{
        return a + b;
    };

    int a{}, b{};
    // captue list by reference default is by value copy
    auto func1 = [&a, &b]()-> int{
        return a + b;
    };
}
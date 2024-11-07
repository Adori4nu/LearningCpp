#include <iostream>
// import std; // słowo kluczowe import służy do dołączania modułów lecz moduł std nie jest jeszcze dostępny

using namespace std;

template<typename T>
T square(T x)
{
    return x * x;
}

template<typename T>
void print_square(T x)
{
    cout << "Square of nubmer: " << x << " is " << square(x) << std::endl;
}

int main()
{
    print_square(1.234);
    
    std::cin.get();
}
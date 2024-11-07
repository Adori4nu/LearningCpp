#include <cmath>
#include <cstdint>
#include <vector>

constexpr int32_t dmv{ 17 };         // stała mająca nazwę
int32_t var{ 17 };                   // var nie jest stałą jest zmienną
const double sqv{ sqrt(var) }; // sqv jest stałą o wartości obliczanej prawdopodobnie
// podczas działania programu lecz przy odpowiedniej optymalizacji może zostać obliczona podczas kompilacji

template<typename T>
T sum(const std::vector<T>& data)
{
    T result{};
    for(auto& v : data)
        result += v;
    return result;
}

template<typename T>
constexpr T square(T x) // funkcja możliwa do użycia wyłącznie w wyrażeniu stałym obliczanym w czasie kompilacj
{                               // funkcji constrexpr można używać wywołując ją z argumentami które nie są stałe
    return x * x;               // wuwczas funkcja nie jest wyrażeniem stałym ale funkcją runtime
}

template<typename T>
consteval T square_eval(T x) // funkcja możliwa do użycia w wyrażeniu stałym obliczanym w czasie kompilacj
{
    return x * x;
}

int main()
{
    std::vector<double> v{ 1.2, 3.4, 4.5 };
    const double s1{ sum(v) };      // ok wartość obliczana w runtime
    // constexpr double s2{ sum(v) };  // błąd nie da się utworzyć wartości w czasie kompilacji z funkcji runtime'owej
    int var{ 17 };
    constexpr double max1{ 1.4 * square(17) };     // ok wartość może zostać obliczona w czasie kompilacji
    // constexpr double max2{ 1.4 * square(var) }; // błąd var nie jest stałą i mogła by zostać zmieniona w trakcie trwania programu
    const double max3{ 1.4 * square(var) };        // ok constexpr w funkcji zostanie ignorowany i wartość zostanie
    // obliczona w runtime jak przy użyciu normalnej funkcji. Funkcja constexprowa może być używana również jako funkcja runtime'owa
    constexpr double max4{ 1.4 * square_eval(17) };
    // const double max5{ 1.4 * square_eval(var) }; // błąd var nie jest wyrażeniem stałym
}
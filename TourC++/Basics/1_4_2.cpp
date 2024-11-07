int main()
{
    int i1 = 7.8; // inicjalizacja tradycyjna wywodząca się z C przy której nastąpi konwersja zwężająca z double do int 7
    int i2{ 7.8 }; // initializer list nie powinien pozwolić na niejawną konwersję bez explicit cast utworzenie tego inta nie powinno być możliwe
}
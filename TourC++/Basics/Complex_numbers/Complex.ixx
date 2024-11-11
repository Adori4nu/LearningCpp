module;



export module Complex;
#ifndef COMPLEX_IMP
    #define COMPLEX_IMP == 52
#endif
#if COMPLEX_IMP == 52
#pragma region 5_2_Complex
export class complex{
    double re, im;
public:
    complex(double r, double i) : re{r}, im{i} {}
    complex(double r) : re{r}, im{0} {}
    comlex(complex z): re{z.re}, im{z.im} {}

    double real() const { return re; }
    void real(double d) { re = d; }
    double imag() const { return im; }
    void imag(double d) { im = d; }

    complex& operator+=(complex z)
    {
        re+=z.re;
        im+=z.im;
        return *this;
    }

    complex& operator-=(complex z)
    {
        re-=z.re;
        im-=z.im;
        return *this;
    }

    complex& operator*=(complex);
    complex& operator/=(complex);
};
#pragma endregion
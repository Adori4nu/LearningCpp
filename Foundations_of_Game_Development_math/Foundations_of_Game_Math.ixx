module;

#include <concepts>

export module GameMath;

#pragma region Chapter 1
template <typename T>
    requires std::floating_point<T>
struct Vector3D
{
    T x, y, z;

    Vector3D() = default;
    
    Vector3D(T a, T b, T c) : x{a}, y{b}, z{c} {}

    T& operator[](int i)
    {
        return ((&x)[i]);
    }

    const T& operator[](int i) const
    {
        return ((&x)[i]);
    }

    Vector3D& operator *=(T s)
    {
        x *= s; y *= s; z *=  s;
        return (*this);
    }

    Vector3D& operator /=(T s)
    {
        s = T(1) / s;
        x *= s; y *= s; z *=  s;
        return (*this);
    }

    Vector3D& operator +=(const Vector3D& v)
    {
        x += v.x; y += v.y; z += v.z;
        return (*this);
    }

    Vector3D& operator -=(const Vector3D& v)
    {
        x -= v.x; y -= v.y; z -= v.z;
        return (*this);
    }
};

inline Vector3D operator *(const Vector3D& v, float s)
{
    return (Vector3D(v.x * s, v.y * s, v.z * s));
}

inline Vector3D operator /(const Vector3D& v, float s)
{
    s = 1.0f / s;
    return (Vector3D(v.x * s, v.y * s, v.z * s));
}

inline Vector3D operator -(const Vector3D& v)
{
    return (Vector3D(-v.x, -v.y, -v.z));
}

inline Vector3D operator +(const Vector3D& a, const Vector3D& b)
{
    return (Vector3D(a.x + b.x, a.y + b.y, a.z + b.z));
}

inline Vector3D operator -(const Vector3D& a, const Vector3D& b)
{
    return (Vector3D(a.x - b.x, a.y - b.y, a.z - b.z));
}

inline float Magnitude(const Vector3D& v)
{
    return (sqrt(v.x * v.x, v.y * v.y, v.z * v.z));
}

inline Vector3D Normalize(const Vector3D& v)
{
    return (v / Magnitude(v));
}

template <typename T>
    requires std::floating_point<T>
struct Matrix3D
{
private:

    T n[3][3];

public:

    Matrix3D() = default;
    
    Matrix3D(T n00, T n01, T n02
            , T n10, T n11, T n12
            , T n20, T n21, T n22)
    {
        n[0][0] = n00; n[0][1] = n01; n[0][2] = n02;
        n[1][0] = n10; n[1][1] = n11; n[1][2] = n12;
        n[2][0] = n20; n[2][1] = n21; n[2][2] = n22;
    }

    Martix3D(const Vector3D& a, const Vector3D& b, const Vector3D& c)
    {
        n[0][0] = a.x; n[0][1] = a.y; n[0][2] = a.z;
        n[1][0] = b.x; n[1][1] = b.y; n[1][2] = b.z;
        n[2][0] = c.x; n[2][1] = c.y; n[2][2] = c.z;
    }

    T& operator ()(size_t i, size_t j)
    {
        return (n[j][i]);
    }

    const T& operator ()(size_t i, size_t j) const
    {
        return (n[j][i]);
    }

    Vector3D& operator [](int j)
    {
        return (*reinterpret_cast<Vector3D *>(n[j]));
    }

    const Vector3D& operator [](int j) const
    {
        return (*reinterpret_cast<const Vector3D *>(n[j]));
    }

    Martix3D operator *(const Matrix3D& A, const Matrix3D& B)
    {
        return Matrix3D(A(0,0) * B(0,0) + A(0,1) * B(1,0) + A(0,2) * B(2,0),
                        A(0,0) * B(0,1) + A(0,1) * B(1,1) + A(0,2) * B(2,1),
                        A(0,0) * B(0,2) + A(0,1) * B(1,2) + A(0,2) * B(2,2),
                        A(1,0) * B(0,0) + A(1,1) * B(1,0) + A(1,2) * B(2,0),
                        A(1,0) * B(0,1) + A(1,1) * B(1,1) + A(1,2) * B(2,1),
                        A(1,0) * B(0,2) + A(1,1) * B(1,2) + A(1,2) * B(2,2),
                        A(2,0) * B(0,0) + A(2,1) * B(1,0) + A(2,2) * B(2,0),
                        A(2,0) * B(0,1) + A(2,1) * B(1,1) + A(2,2) * B(2,1),
                        A(2,0) * B(0,2) + A(2,1) * B(1,2) + A(2,2) * B(2,2));
    }

    Vector3D operator *(const Matrix3D& M, const Vector3D& v)
    {
        return Vector3D(M(0,0) * v.x + M(0,1) * v.y + M(0,2) * v.z,
                        M(1,0) * v.x + M(1,1) * v.y + M(1,2) * v.z,
                        M(2,0) * v.x + M(2,1) * v.y + M(2,2) * v.z);
    }
};

#pragma endregion
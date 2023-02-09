#pragma once
#define eps 1.0e-6

/**
 * @brief the class vector_c illustrate a 3d vector
 * @author Liu Zhixing, liuzhixing0525@163.com
 * @date 2022-10-01
 * 
 */
class vector_c{
public:
    vector_c() {}
    ~vector_c() {}

    vector_c(const double& X, const double& Y, const double& Z)
        : x(X), y(Y), z(Z) {}
    vector_c(const vector_c& vct);

    int set_x(const double& X);
    int set_y(const double& Y);
    int set_z(const double& Z);
    int set_vector(const vector_c& vct);

    int normalize();

    double get_x() const;
    double get_y() const;
    double get_z() const;
    double get_magnitude() const;

    const vector_c& operator = (const vector_c& vct);

    const vector_c operator + (const vector_c& vct) const;
    const vector_c operator - (const vector_c& vct) const;
    const vector_c operator * (const double& s) const;
    const vector_c operator / (const double& s) const;

    double operator * (const vector_c& vct) const;
    const vector_c operator ^ (const vector_c& vct) const;

    const vector_c& operator += (const vector_c& vct);
    const vector_c& operator -= (const vector_c& vct);
    const vector_c& operator += (const double& s);
    const vector_c& operator -= (const double& s);
    const vector_c& operator *= (const double& s);
    const vector_c& operator /= (const double& s);


private:
    double x{0.0}, y{0.0}, z{0.0};
};
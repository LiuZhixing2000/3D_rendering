#include "vector.h"
#include <cmath>

vector_c::vector_c(const vector_c& vct){
    x = vct.get_x();
    y = vct.get_y();
    z = vct.get_z();
}

int vector_c::set_x(const double& X){
    x = X;
    return 1;
}

int vector_c::set_y(const double& Y){
    y = Y;
    return 1;
}

int vector_c::set_z(const double& Z){
    z = Z;
    return 1;
}

int vector_c::set_vector(const vector_c& vct){
    x = vct.get_x();
    y = vct.get_y();
    z = vct.get_z();
    return 1;    
}

int vector_c::normalize(){
    double m = get_magnitude();
    if(std::abs(m) < eps)
        return 0;
    *this /= m;
    return 1;
}

double vector_c::get_x() const{
    return x;
}

double vector_c::get_y() const{
    return y;
}

double vector_c::get_z() const{
    return z;
}

double vector_c::get_magnitude() const{
    return sqrt(x*x + y*y + z*z);
}

const vector_c& vector_c::operator=(const vector_c& vct){
    set_vector(vct);
    return *this;
}

const vector_c vector_c::operator+(const vector_c& vct) const{
    vector_c result(*this);
    result.set_x(result.get_x() + vct.get_x());
    result.set_y(result.get_y() + vct.get_y());
    result.set_z(result.get_z() + vct.get_z());
    return result;
}

const vector_c vector_c::operator-(const vector_c& vct) const{
    vector_c result(*this);
    result.set_x(result.get_x() - vct.get_x());
    result.set_y(result.get_y() - vct.get_y());
    result.set_z(result.get_z() - vct.get_z());
    return result;
}

const vector_c vector_c::operator*(const double& s) const{
    vector_c result(*this);
    result.set_x(result.get_x() * s);
    result.set_y(result.get_y() * s);
    result.set_z(result.get_z() * s);
    return result;
}

const vector_c vector_c::operator/(const double& s) const{
    if(std::abs(s) < eps)
        return vector_c();
    vector_c result(*this);
    result.set_x(result.get_x() / s);
    result.set_y(result.get_y() / s);
    result.set_z(result.get_z() / s);
    return result;
}

double vector_c::operator*(const vector_c& vct) const{
    return get_x() * vct.get_x() + get_y() * vct.get_y() + get_z() * vct.get_z();
}

const vector_c vector_c::operator ^ (const vector_c& vct) const{
    vector_c result;
    result.set_x(get_y() * vct.get_z() - vct.get_y() * get_z());
    result.set_y(get_z() * vct.get_x() - vct.get_z() * get_x());
    result.set_z(get_x() * vct.get_y() - vct.get_x() * get_y());
    return result;
}

const vector_c& vector_c::operator += (const vector_c& vct){
    set_x(get_x() + vct.get_x());
    set_y(get_y() + vct.get_y());
    set_z(get_z() + vct.get_z());
    return *this;
}

const vector_c& vector_c::operator -= (const vector_c& vct){
    set_x(get_x() - vct.get_x());
    set_y(get_y() - vct.get_y());
    set_z(get_z() - vct.get_z());
    return *this;    
}

const vector_c& vector_c::operator += (const double& s){
    set_x(get_x() + s);
    set_y(get_y() + s);
    set_z(get_z() + s);
    return *this;    
}

const vector_c& vector_c::operator -= (const double& s){
    set_x(get_x() - s);
    set_y(get_y() - s);
    set_z(get_z() - s);
    return *this;    
}

const vector_c& vector_c::operator *= (const double& s){
    set_x(get_x() * s);
    set_y(get_y() * s);
    set_z(get_z() * s);
    return *this;        
}

const vector_c& vector_c::operator /= (const double& s){
    if(std::abs(s) < eps)
        return *this;
        
    set_x(get_x() / s);
    set_y(get_y() / s);
    set_z(get_z() / s);
    return *this;        
}
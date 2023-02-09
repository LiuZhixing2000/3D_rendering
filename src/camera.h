#pragma once
#include "vector.h"

/**
 * @brief the class camera_c illustrate a camera
 * @author Liu Zhixing, liuzhixing0525@163.com
 * @date 2022-10-02
 * 
 */
class camera_c{
public:
    camera_c() {}
    ~camera_c() {}

    int read_camera_from_xml_file(const char* file_name);

    vector_c get_eye() const;
    vector_c get_look_at() const;
    vector_c get_up() const;
    double get_fovy() const;
    int get_width() const;
    int get_height() const;

    int set_eye(const vector_c& vct);
    int set_look_at(const vector_c& vct);
    int set_up(const vector_c& vct);
    int set_fovy(const double& f);
    int set_width(const int& w);
    int set_height(const int& h);

private:
    vector_c eye;
    vector_c look_at;
    vector_c up;
    double fovy{0.};
    int width{0};
    int height{0};
};
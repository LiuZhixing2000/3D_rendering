#include "camera.h"
#include "string_reader.h"
#include <fstream>
#include <iostream>
#include <cmath>

vector_c camera_c::get_eye() const{
    return eye;
}

vector_c camera_c::get_look_at() const{
    return look_at;
}

vector_c camera_c::get_up() const{
    return up;
}

double camera_c::get_fovy() const{
    return fovy;
}

int camera_c::get_width() const{
    return width;
}

int camera_c::get_height() const{
    return height;
}

int camera_c::set_eye(const vector_c& vct){
    eye = vct;
    return 1;
}

int camera_c::set_look_at(const vector_c& vct){
    look_at = vct;
    return 1;
}

int camera_c::set_up(const vector_c& vct){
    up = vct;
    return 1;
}

int camera_c::set_fovy(const double& f){
    fovy = f;
    return 1;
}

int camera_c::set_width(const int& w){
    width = w;
    return 1;
}

int camera_c::set_height(const int& h){
    height = h;
    return 1;
}

int camera_c::read_camera_from_xml_file(const char* file_name) {
	std::string stringfilename(file_name);
	if (!(stringfilename.substr(stringfilename.size() - 3, 3) == "xml"))
		stringfilename.append(".xml");
	std::ifstream fp(stringfilename);
	if (!fp) {
		std::cout << "No such .xml file - " << stringfilename << std::endl;
		return 0;
	}
	else
		std::cout << "Successfully open file -" << stringfilename << std::endl;
	char buffer[1024];
	std::string tempstr;
	// the first line: version, encoding
	fp.getline(buffer, 1024);
	// the second line: camera type
	fp.getline(buffer, 1024);
	// the third line: eye
	fp.getline(buffer, 1024);
	tempstr = buffer;
	std::vector<double> words = string2Doubles(tempstr);
    eye.set_vector(vector_c(words[0], words[1], words[2]));
	// the fourth line: lookat
	fp.getline(buffer, 1024);
	tempstr = buffer;
	words = string2Doubles(tempstr);
    look_at.set_vector(vector_c(words[0], words[1], words[2]));
	// the fifth line: up
	fp.getline(buffer, 1024);
	tempstr = buffer;
	words = string2Doubles(tempstr);
    up.set_vector(vector_c(words[0], words[1], words[2]));
	// the sixth line: fovy
	fp.getline(buffer, 1024);
	tempstr = buffer;
	words = string2Doubles(tempstr);
	fovy = words[0];
	// the seventh line: width
	fp.getline(buffer, 1024);
	tempstr = buffer;
	words = string2Doubles(tempstr);
	width = std::round(words[0]);
	// the eighth line: height
	fp.getline(buffer, 1024);
	tempstr = buffer;
	words = string2Doubles(tempstr);
	height = std::round(words[0]);

	std::cout << "Successfully read camera." << std::endl;

	return 1;
}
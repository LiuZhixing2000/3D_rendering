#include "light.h"
#include "string_reader.h"
#include <fstream>
#include <iostream>

int light_c::read_light_from_xml_file(const char* file_name) {
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
	for(int i = 0; i < 9; i++)
		fp.getline(buffer, 1024);
	while (!fp.eof()) {
		fp.getline(buffer, 1024);
		tempstr = buffer;
		int begin, end;
		for (int i = 0; i < tempstr.size(); i++) {
			if (tempstr[i] == '"') {
				begin = i;
				break;
			}
		}
		for (int i = begin + 1; i < tempstr.size(); i++) {
			if (tempstr[i] == '"') {
				end = i;
				break;
			}
		}
		light_unit_c light;
		
		light.name = tempstr.substr(begin + 1, end - begin - 1);
		tempstr = tempstr.substr(end + 1, tempstr.size() - 1);
		std::vector<double> words = string2Doubles(tempstr);
        light.radiance.set_vector(vector_c(words[0], words[1], words[2]));
		light_units.push_back(light);
	}

	std::cout << "Successfully read light." << std::endl;
	return 1;
}

const std::vector<light_unit_c>& light_c::get_light() const{
    return light_units;
}

int light_c::set_light_unit_facet_id(const int& light_unit_id, const int& facet_id){
	light_units[light_unit_id].facet_id.push_back(facet_id);
	return 1;
}
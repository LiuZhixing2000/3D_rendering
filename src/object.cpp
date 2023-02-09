#include "object.h"
#include <iostream>
#include <string>

int object_c::read_object_from_obj_file(const char* file_name) {
	std::string inputFileName = file_name;
	tinyobj::ObjReaderConfig reader_config;

	tinyobj::ObjReader reader;

	if (!reader.ParseFromFile(inputFileName, reader_config)) {
		if (!reader.Error().empty()) {
			std::cerr << "TinyObjReader: " << reader.Error();
		}
		exit(0);
	}

	if (!reader.Warning().empty()) {
		std::cout << "TinyObjReader: " << reader.Warning();
	}

	attrib = reader.GetAttrib();
	shapes = reader.GetShapes();
	materials = reader.GetMaterials();
	
	std::cout << "Successfully read object." << std::endl;
	return 1;
}

const tinyobj::attrib_t& object_c::get_attrib() const{
    return attrib;
}

const std::vector<tinyobj::shape_t>& object_c::get_shapes() const{
    return shapes;
}

const std::vector<tinyobj::material_t>& object_c::get_materials() const{
    return materials;
}
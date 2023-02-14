#include "object.h"
#include <iostream>
#include <fstream>
#include <string>

int object_c::read_object_from_obj_file(const char* file_name) {
	std::string inputFileName = file_name;

	object_file_name = inputFileName;
	int end = object_file_name.size() - 1;
	while(object_file_name[end] != '/')
		end--;
	end++;
	object_path_name = object_file_name.substr(0, end);

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

int object_c::read_tex_picture_from_mtl_file(){
	auto& materials = get_materials();
	for(auto& material : materials){
		if(material.diffuse_texname.empty())
			continue;
		int tex_width, tex_height, channels;
		unsigned char* tex = read_jpg((object_path_name + material.diffuse_texname).c_str(), &tex_width, &tex_height, &channels);
		if(!tex){
			std::cout << "Read texture picture failed." << std::endl;
			return 0;
		}
		textures[material.diffuse_texname] = tex;
		textures_info[material.diffuse_texname] = std::vector<int>({tex_width, tex_height});
	}
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

const std::unordered_map<std::string, unsigned char*> &object_c::get_textures() const{
	return textures;
}

const std::unordered_map<std::string, std::vector<int> > &object_c::get_textures_info() const{
	return textures_info;
}


unsigned char* object_c::get_texture(const std::string& tex_name){
	return textures[tex_name];
}
std::pair<int, int> object_c::get_texture_info(const std::string& tex_name){
	auto tmp = textures_info[tex_name];
	return std::pair<int, int>(tmp[0], tmp[1]);
}
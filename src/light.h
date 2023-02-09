#pragma once
#include <string>
#include <vector>
#include "vector.h"
struct light_unit_c{
    std::string name;
    vector_c radiance;
    std::vector<int> facet_id;
};

class light_c{
public:
    light_c() {}
    ~light_c() {}

    int read_light_from_xml_file(const char* file_name);

    const std::vector<light_unit_c>& get_light() const;

    int set_light_unit_facet_id(const int& light_unit_id, const int& facet_id);

private:
    std::vector<light_unit_c> light_units;
};
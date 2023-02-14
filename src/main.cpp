#include <iostream>
#include "renderer.h"

int main(int argc, char** argv){
    renderer path_tracing;
    std::string case_name = "./cases/cornell-box/cornell-box";
    path_tracing.set_case_file_name(case_name);
    path_tracing.load_case();
    path_tracing.rendering();
    path_tracing.normalize_color();
    path_tracing.gamma_correction();
    path_tracing.write2jpg();
    return 0;
}
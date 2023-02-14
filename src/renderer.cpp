#include "renderer.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <string>
#include <random>
#include <set>

int renderer::set_case_file_name(const std::string &case_name)
{
    case_file_name = case_name;
    return 1;
}

int renderer::load_case()
{
    if (case_file_name.empty())
    {
        std::cout << "No case file name." << std::endl;
        return 0;
    }
    std::string xml_name = case_file_name + ".xml";
    std::string obj_name = case_file_name + ".obj";
    std::string mtl_name = case_file_name + ".mtl";
    if (!camera.read_camera_from_xml_file(xml_name.c_str()))
    {
        std::cout << "Read camera failed." << std::endl;
        return 0;
    }
    if (!light.read_light_from_xml_file(xml_name.c_str()))
    {
        std::cout << "Read light failed." << std::endl;
        return 0;
    }
    if (!object.read_object_from_obj_file(obj_name.c_str()))
    {
        std::cout << "Read object failed." << std::endl;
        return 0;
    }
    if (!object.read_tex_picture_from_mtl_file())
    {
        std::cout << "Read texure failed." << std::endl;
        return 0;
    }
    std::cout << "Picture size: " << camera.get_width() << "x" << camera.get_height() << std::endl;
    initialize_light();
    return 1;
}

int renderer::get_screen_position()
{
    // height of camera
    int camera_height = camera.get_height();
    // fovy of camera
    double camera_fovy = camera.get_fovy();
    // distance between camera and screen
    double camera_distance = camera_height / (2.0 * std::tan(camera_fovy / 2.0 * M_PI / 180.0));
    // look at of camera
    vector_c camera_look_at = camera.get_look_at() - camera.get_eye();
    camera_look_at.normalize();
    // up direction of camera
    vector_c camera_up = camera.get_up();
    camera_up.normalize();
    // side(right) direction of camera
    // look_at ^ side = up
    vector_c camera_side = camera_up ^ camera_look_at;
    camera_side.normalize();

    // center of screen
    vector_c screen_center = camera.get_eye() + camera_look_at * camera_distance;
    // lefttop of screen
    screen_top = screen_center + camera_side * camera.get_width() / 2.0 + camera_up * camera_height / 2.0;

    return 1;
}

int renderer::rendering()
{
    // eye of camera
    vector_c camera_eye = camera.get_eye();
    // height and width of screen
    int screen_height = camera.get_height(), screen_width = camera.get_width();
    // look at of camera
    vector_c camera_look_at = camera.get_look_at() - camera.get_eye();
    camera_look_at.normalize();
    // up direction of camera
    vector_c camera_up = camera.get_up();
    camera_up.normalize();
    // side(right) direction of camera
    // look_at ^ side = up
    vector_c camera_side = camera_up ^ camera_look_at;
    camera_side.normalize();

    get_screen_position();

    r_values.resize(screen_height * screen_width);
    g_values.resize(screen_height * screen_width);
    b_values.resize(screen_height * screen_width);

    const tinyobj::attrib_t tinyobj_attrib = object.get_attrib();
    std::vector<tinyobj::index_t> tinyobj_indices = object.get_shapes()[0].mesh.indices;
    std::vector<float> vertices = object.get_attrib().vertices;
    std::vector<int> facets;
    for (int i = 0; i < tinyobj_indices.size(); i++)
    {
        facets.push_back(tinyobj_indices[i].vertex_index);
    }

    bvh_tree = new bvh_tree_;
    bvh_tree->set_object(vertices, facets);
    bvh_tree->build_root();
    bvh_tree->grow_tree();

    // for each pixel
    for (int line = 0; line < screen_height; line++)
    {
        for (int row = 0; row < screen_width; row++)
        {
            vector_c top_position = screen_top - camera_side * row - camera_up * line;
            vector_c pixel_radiance(0., 0., 0.);
            int sample_time = 0;
            while (sample_time < sample_time_each_pixel)
            {
                sample_time++;
                // sample randomly
                // generate doubles randomly between 0 and 1
                std::default_random_engine random_engine;
                std::uniform_real_distribution<double> generate_random_double(0.0, 1.0);
                double side_offset = generate_random_double(random_engine);
                double up_offset = generate_random_double(random_engine);

                // get the position of sample point
                vector_c sample_position = top_position - camera_side * side_offset - camera_up * up_offset;
                // get the sample ray
                vector_c ray_starting = camera_eye;
                vector_c ray_direction = sample_position - camera_eye;
                ray_direction.normalize();

                // 计算得辐射度
                vector_c sample_radiance = path_tracing(ray_starting, ray_direction);
                pixel_radiance += sample_radiance;
            }
            pixel_radiance /= (double)sample_time_each_pixel;
            r_values[line * screen_width + row] = pixel_radiance.get_x();
            g_values[line * screen_width + row] = pixel_radiance.get_y();
            b_values[line * screen_width + row] = pixel_radiance.get_z();
        }
        std::cout << "line " << line << " rendering end." << std::endl;
    }
    return 1;
}

vector_c renderer::path_tracing(
    const vector_c &ray_starting, const vector_c &ray_direction)
{
    int intersection_triangle;
    double intersection_t;
    if (!intersection_detection(ray_starting, ray_direction, intersection_triangle, intersection_t))
    {
        return background_color;
    }
    vector_c intersection_point = ray_starting + ray_direction * intersection_t;

    // 照射到光源上，返回最亮的白色
    vector_c light_radiance(1.0, 1.0, 1.0);
    if (is_light(intersection_triangle, light_radiance))
        return light_radiance;

    int intersection_triangle_pa_normal_id = object.get_shapes()[0].mesh.indices[3 * intersection_triangle].normal_index;
    int intersection_triangle_pb_normal_id = object.get_shapes()[0].mesh.indices[3 * intersection_triangle + 1].normal_index;
    int intersection_triangle_pc_normal_id = object.get_shapes()[0].mesh.indices[3 * intersection_triangle + 2].normal_index;
    vector_c intersection_triangle_pa_normal(
        object.get_attrib().normals[3 * intersection_triangle_pa_normal_id],
        object.get_attrib().normals[3 * intersection_triangle_pa_normal_id + 1],
        object.get_attrib().normals[3 * intersection_triangle_pa_normal_id + 2]);
    vector_c intersection_triangle_pb_normal(
        object.get_attrib().normals[3 * intersection_triangle_pb_normal_id],
        object.get_attrib().normals[3 * intersection_triangle_pb_normal_id + 1],
        object.get_attrib().normals[3 * intersection_triangle_pb_normal_id + 2]);
    vector_c intersection_triangle_pc_normal(
        object.get_attrib().normals[3 * intersection_triangle_pc_normal_id],
        object.get_attrib().normals[3 * intersection_triangle_pc_normal_id + 1],
        object.get_attrib().normals[3 * intersection_triangle_pc_normal_id + 2]);
    vector_c intersection_triangle_normal =
        (intersection_triangle_pa_normal + intersection_triangle_pb_normal + intersection_triangle_pc_normal) / 3.0;
    intersection_triangle_normal.normalize();

    if (intersection_triangle_normal * ray_direction > 0)
        return vector_c(0.0, 0.0, 0.0);

    return shade(intersection_point, intersection_triangle, ray_direction * (-1.0));
}

bool renderer::intersection_detection(
    const vector_c &ray_starting, const vector_c &ray_direction,
    int &triangle_id, double &intersection_t) const
{
    std::vector<int> possibly_intersecting_facets = bvh_tree->intersection_detection_with_a_ray(
        ray_starting, ray_direction);

    if (possibly_intersecting_facets.empty())
        return false;

    std::set<std::pair<double, int>> facets_ordered_by_intersection_t;
    for (int facet_id : possibly_intersecting_facets)
    {
        double t;
        if (intersection_detection_ray_triangle(
                ray_starting, ray_direction, facet_id, t) &&
            t > 0)
        {
            facets_ordered_by_intersection_t.insert(std::pair<double, int>(t, facet_id));
        }
    }

    if (facets_ordered_by_intersection_t.empty())
        return false;
    else
    {
        intersection_t = facets_ordered_by_intersection_t.begin()->first;
        triangle_id = facets_ordered_by_intersection_t.begin()->second;
        return true;
    }
}

bool renderer::intersection_detection_ray_triangle(
    const vector_c &ray_starting, const vector_c &ray_direction,
    const int &triangle_id,
    double &intersection_t) const
{
    int pa_id = object.get_shapes()[0].mesh.indices[3 * triangle_id].vertex_index;
    int pb_id = object.get_shapes()[0].mesh.indices[3 * triangle_id + 1].vertex_index;
    int pc_id = object.get_shapes()[0].mesh.indices[3 * triangle_id + 2].vertex_index;
    vector_c pa(object.get_attrib().vertices[3 * pa_id], object.get_attrib().vertices[3 * pa_id + 1], object.get_attrib().vertices[3 * pa_id + 2]);
    vector_c pb(object.get_attrib().vertices[3 * pb_id], object.get_attrib().vertices[3 * pb_id + 1], object.get_attrib().vertices[3 * pb_id + 2]);
    vector_c pc(object.get_attrib().vertices[3 * pc_id], object.get_attrib().vertices[3 * pc_id + 1], object.get_attrib().vertices[3 * pc_id + 2]);

    double AA, BB, CC, DD;
    plane(pa, pb, pc, AA, BB, CC, DD);

    intersection_t = (0 - AA * ray_starting.get_x() - BB * ray_starting.get_y() - CC * ray_starting.get_z() - DD) / (AA * ray_direction.get_x() + BB * ray_direction.get_y() + CC * ray_direction.get_z());

    if (intersection_t < 0)
        return false;

    // tell if intersection point inside triangle
    vector_c intersection_point = ray_starting + ray_direction * intersection_t;
    if (point_inside_triangle(intersection_point, pa, pb, pc) > 0)
        return true;
    else
        return false;
}

int renderer::plane(
    const vector_c &pa, const vector_c &pb, const vector_c &pc,
    double &AA, double &BB, double &CC, double &DD) const
{
    // todo, return 0

    AA = pa.get_y() * (pb.get_z() - pc.get_z()) + pb.get_y() * (pc.get_z() - pa.get_z()) + pc.get_y() * (pa.get_z() - pb.get_z());
    BB = pa.get_z() * (pb.get_x() - pc.get_x()) + pb.get_z() * (pc.get_x() - pa.get_x()) + pc.get_z() * (pa.get_x() - pb.get_x());
    CC = pa.get_x() * (pb.get_y() - pc.get_y()) + pb.get_x() * (pc.get_y() - pa.get_y()) + pc.get_x() * (pa.get_y() - pb.get_y());
    DD = 0 - AA * pa.get_x() - BB * pa.get_y() - CC * pa.get_z();
    return 1;
}

double renderer::triangle_area(
    const vector_c &pa, const vector_c &pb, const vector_c &pc) const
{
    double dab = std::sqrt((pa.get_x() - pb.get_x()) * (pa.get_x() - pb.get_x()) + (pa.get_y() - pb.get_y()) * (pa.get_y() - pb.get_y()) + (pa.get_z() - pb.get_z()) * (pa.get_z() - pb.get_z()));
    double dbc = std::sqrt((pc.get_x() - pb.get_x()) * (pc.get_x() - pb.get_x()) + (pc.get_y() - pb.get_y()) * (pc.get_y() - pb.get_y()) + (pc.get_z() - pb.get_z()) * (pc.get_z() - pb.get_z()));
    double dca = std::sqrt((pc.get_x() - pa.get_x()) * (pc.get_x() - pa.get_x()) + (pc.get_y() - pa.get_y()) * (pc.get_y() - pa.get_y()) + (pc.get_z() - pa.get_z()) * (pc.get_z() - pa.get_z()));
    double dpp = (dab + dbc + dca) / 2;
    double area = std::sqrt(dpp * (dpp - dab) * (dpp - dbc) * (dpp - dca));
    return area;
}

int renderer::point_inside_triangle(
    const vector_c &ps,
    const vector_c &pa, const vector_c &pb, const vector_c &pc) const
{
    double area_abc = triangle_area(pa, pb, pc);
    double area_sab = triangle_area(ps, pa, pb);
    if (std::abs(area_sab) < EPS)
        return 0;
    double area_sbc = triangle_area(ps, pb, pc);
    if (std::abs(area_sbc) < EPS)
        return 0;
    double area_sca = triangle_area(ps, pc, pa);
    if (std::abs(area_sca) < EPS)
        return 0;

    if (std::abs(area_abc - area_sab - area_sbc - area_sca) < EPS)
        return 1;
    else
        return -1;
}

vector_c renderer::shade(
    const vector_c &p, const int &p_triangle_id,
    const vector_c &wo) const
{
    // direct radiance: sampling the light
    vector_c direct_radiance = shade_direct_light(p, p_triangle_id, wo);

    // indirect radiance: path tracing, Russian Roulette
    vector_c indirect_radiance = shade_indirect_light(p, p_triangle_id, wo);

    return direct_radiance + indirect_radiance;
}

bool renderer::is_light(const int &facet_id, vector_c &light_radiance) const
{
    int facet_material = object.get_shapes()[0].mesh.material_ids[facet_id];
    std::string material_name = object.get_materials()[facet_material].name;
    for (auto light_unit : light.get_light())
    {
        if (light_unit.name == material_name)
        {
            light_radiance = light_unit.radiance;
            return true;
        }
    }
    return false;
}

int renderer::initialize_light()
{
    std::vector<int> material_ids_all_facets = object.get_shapes()[0].mesh.material_ids;
    for (int i = 0; i < material_ids_all_facets.size(); i++)
    {
        int material_id = material_ids_all_facets[i];
        std::string material_name = object.get_materials()[material_id].name;
        for (int j = 0; j < light.get_light().size(); j++)
        {
            auto &light_unit = light.get_light()[j];
            if (light_unit.name == material_name)
            {
                light.set_light_unit_facet_id(j, i);
                break;
            }
        }
    }
    return 1;
}

vector_c renderer::shade_direct_light(
    const vector_c &p, const int &p_triangle_id,
    const vector_c &wo) const
{
    double total_radiance_r = 0.0, total_radiance_g = 0.0, total_radiance_b = 0.0;
    int triangle_material_id = object.get_shapes()[0].mesh.material_ids[p_triangle_id];
    vector_c brdf_diffuse(
        object.get_materials()[triangle_material_id].diffuse[0],
        object.get_materials()[triangle_material_id].diffuse[1],
        object.get_materials()[triangle_material_id].diffuse[2]);
    vector_c brdf_specular(
        object.get_materials()[triangle_material_id].specular[0],
        object.get_materials()[triangle_material_id].specular[1],
        object.get_materials()[triangle_material_id].specular[2]);
    return sampling_light_source(p, p_triangle_id, wo);
}

vector_c renderer::sampling_light_source(
        const vector_c &p, const int &p_triangle_id,
        const vector_c &wo
)const{
    double total_radiance_r = 0.0, total_radiance_g = 0.0, total_radiance_b = 0.0;
    // method: sampling the light source
    // for each light
    for (auto &light_unit : light.get_light())
    {
        std::vector<int> light_facet_ids = light_unit.facet_id;
        // p点接受到的一个光源单元发出的radiance，由一组光源面片组成
        double light_radiance_r = 0.0, light_radiance_g = 0.0, light_radiance_b = 0.0;
        // triangle information
        int triangle_pa_id = object.get_shapes()[0].mesh.indices[3 * p_triangle_id].vertex_index;
        int triangle_pb_id = object.get_shapes()[0].mesh.indices[3 * p_triangle_id + 1].vertex_index;
        int triangle_pc_id = object.get_shapes()[0].mesh.indices[3 * p_triangle_id + 2].vertex_index;

        int triangle_pa_normal_id = object.get_shapes()[0].mesh.indices[3 * p_triangle_id].normal_index;
        int triangle_pb_normal_id = object.get_shapes()[0].mesh.indices[3 * p_triangle_id + 1].normal_index;
        int triangle_pc_normal_id = object.get_shapes()[0].mesh.indices[3 * p_triangle_id + 2].normal_index;

        vector_c triangle_pa_normal(
            object.get_attrib().normals[3 * triangle_pa_normal_id],
            object.get_attrib().normals[3 * triangle_pa_normal_id + 1],
            object.get_attrib().normals[3 * triangle_pa_normal_id + 2]);
        vector_c triangle_pb_normal(
            object.get_attrib().normals[3 * triangle_pb_normal_id],
            object.get_attrib().normals[3 * triangle_pb_normal_id + 1],
            object.get_attrib().normals[3 * triangle_pb_normal_id + 2]);
        vector_c triangle_pc_normal(
            object.get_attrib().normals[3 * triangle_pc_normal_id],
            object.get_attrib().normals[3 * triangle_pc_normal_id + 1],
            object.get_attrib().normals[3 * triangle_pc_normal_id + 2]);

        vector_c triangle_pa(
            object.get_attrib().vertices[3 * triangle_pa_id],
            object.get_attrib().vertices[3 * triangle_pa_id + 1],
            object.get_attrib().vertices[3 * triangle_pa_id + 2]);
        vector_c triangle_pb(
            object.get_attrib().vertices[3 * triangle_pb_id],
            object.get_attrib().vertices[3 * triangle_pb_id + 1],
            object.get_attrib().vertices[3 * triangle_pb_id + 2]);
        vector_c triangle_pc(
            object.get_attrib().vertices[3 * triangle_pc_id],
            object.get_attrib().vertices[3 * triangle_pc_id + 1],
            object.get_attrib().vertices[3 * triangle_pc_id + 2]);

        int triangle_material_id = object.get_shapes()[0].mesh.material_ids[p_triangle_id];
        vector_c triangle_normal = (triangle_pa_normal + triangle_pb_normal + triangle_pc_normal) / 3.0;
        triangle_normal.normalize();
        vector_c &p_normal = triangle_normal;
        for (int light_facet_id : light_facet_ids)
        {
            vector_c light_radiance = light_unit.radiance;

            // light information
            int light_pa_id = object.get_shapes()[0].mesh.indices[3 * light_facet_id].vertex_index;
            int light_pb_id = object.get_shapes()[0].mesh.indices[3 * light_facet_id + 1].vertex_index;
            int light_pc_id = object.get_shapes()[0].mesh.indices[3 * light_facet_id + 2].vertex_index;

            int light_pa_normal_id = object.get_shapes()[0].mesh.indices[3 * light_facet_id].normal_index;
            int light_pb_normal_id = object.get_shapes()[0].mesh.indices[3 * light_facet_id + 1].normal_index;
            int light_pc_normal_id = object.get_shapes()[0].mesh.indices[3 * light_facet_id + 1].normal_index;

            vector_c light_pa_normal(
                object.get_attrib().normals[3 * light_pa_normal_id],
                object.get_attrib().normals[3 * light_pa_normal_id + 1],
                object.get_attrib().normals[3 * light_pa_normal_id + 2]);
            vector_c light_pb_normal(
                object.get_attrib().normals[3 * light_pb_normal_id],
                object.get_attrib().normals[3 * light_pb_normal_id + 1],
                object.get_attrib().normals[3 * light_pb_normal_id + 2]);
            vector_c light_pc_normal(
                object.get_attrib().normals[3 * light_pc_normal_id],
                object.get_attrib().normals[3 * light_pc_normal_id + 1],
                object.get_attrib().normals[3 * light_pc_normal_id + 2]);

            vector_c light_pa(
                object.get_attrib().vertices[3 * light_pa_id],
                object.get_attrib().vertices[3 * light_pa_id + 1],
                object.get_attrib().vertices[3 * light_pa_id + 2]);
            vector_c light_pb(
                object.get_attrib().vertices[3 * light_pb_id],
                object.get_attrib().vertices[3 * light_pb_id + 1],
                object.get_attrib().vertices[3 * light_pb_id + 2]);
            vector_c light_pc(
                object.get_attrib().vertices[3 * light_pc_id],
                object.get_attrib().vertices[3 * light_pc_id + 1],
                object.get_attrib().vertices[3 * light_pc_id + 2]);

            vector_c light_normal = (light_pa_normal + light_pb_normal + light_pc_normal) / 3.0;
            light_normal.normalize();

            double light_area = triangle_area(light_pa, light_pb, light_pc);

            if (p_normal * light_normal > 0)
                continue;

            // p点接受到的一个光源面片发出的radiance
            double diffuse_coefficient = 0.0;
            double specular_coefficient = 0.0;
            double specular_r = 0.0, specular_g = 0.0, specular_b = 0.0;
            vector_c brdf_diffuse;
            if(object.get_materials()[triangle_material_id].diffuse_texname.empty())
                brdf_diffuse = vector_c(
                    object.get_materials()[triangle_material_id].diffuse[0],
                    object.get_materials()[triangle_material_id].diffuse[1],
                    object.get_materials()[triangle_material_id].diffuse[2]);
            else{
                std::string tex_name = object.get_materials()[triangle_material_id].diffuse_texname;
                int tex_index_a = object.get_shapes()[0].mesh.indices[3*p_triangle_id].texcoord_index;
                int tex_index_b = object.get_shapes()[0].mesh.indices[3*p_triangle_id + 1].texcoord_index;
                int tex_index_c = object.get_shapes()[0].mesh.indices[3*p_triangle_id + 2].texcoord_index;
                double tex_coord_width_a = object.get_attrib().texcoords[2*tex_index_a];
                double tex_coord_height_a = object.get_attrib().texcoords[2*tex_index_a + 1];
                double tex_coord_width_b = object.get_attrib().texcoords[2*tex_index_b];
                double tex_coord_height_b = object.get_attrib().texcoords[2*tex_index_b + 1];
                double tex_coord_width_c = object.get_attrib().texcoords[2*tex_index_c];
                double tex_coord_height_c = object.get_attrib().texcoords[2*tex_index_c + 1];
                double tex_coord_width = (tex_coord_width_a + tex_coord_width_b + tex_coord_width_c) / 3.0;
                double tex_coord_height = (tex_coord_height_a + tex_coord_height_b + tex_coord_width_c) / 3.0;

                auto textures = object.get_textures();
                unsigned char* texture = textures[tex_name];
                auto textures_info = object.get_textures_info();
                auto texture_info = textures_info[tex_name];
                int texture_width = texture_info[0], texture_height = texture_info[1];

                int pos_i = (int)(texture_width * tex_coord_width), pos_j = (int)(texture_height * tex_coord_height);
                int r_diffuse_value = (int)(texture[3 * (texture_width * pos_j + pos_i)]);
                int g_diffuse_value = (int)(texture[3 * (texture_width * pos_j + pos_i) + 1]);
                int b_diffuse_value = (int)(texture[3 * (texture_width * pos_j + pos_i) + 2]);

                brdf_diffuse = vector_c(
                    r_diffuse_value / 256.0, g_diffuse_value / 256.0, b_diffuse_value / 256.0
                );
            }
            vector_c brdf_specular(
                object.get_materials()[triangle_material_id].specular[0],
                object.get_materials()[triangle_material_id].specular[1],
                object.get_materials()[triangle_material_id].specular[2]);
            double shininess = object.get_materials()[triangle_material_id].shininess;
            for (int sample_time = 0; sample_time < sample_time_each_facet_light_unit; sample_time++)
            {
                // 在光源三角形内采样一个点作为采样点
                // 过采样点射出一条光线作为采样光线
                std::default_random_engine random_engine;
                std::uniform_real_distribution<double> generate_random_double(0.0, 1.0);
                double random_param_1 = generate_random_double(random_engine);
                generate_random_double = std::uniform_real_distribution<double>(0.0, 1.0 - random_param_1);
                double random_param_2 = generate_random_double(random_engine);
                double random_param_3 = 1.0 - random_param_1 - random_param_2;

                vector_c sample_point = light_pa * random_param_1 + light_pb * random_param_2 + light_pc * random_param_3;
                vector_c sample_ray_direction = p - sample_point;
                sample_ray_direction.normalize();
                vector_c sample_ray_starting = sample_point + sample_ray_direction * 0.001;

                // 光源发出的本采样光线可以照射到p上，之间没有遮挡
                int test_id;
                double test_t;
                if (!intersection_detection(sample_ray_starting, sample_ray_direction, test_id, test_t))
                    continue;
                if (test_id != p_triangle_id)
                    continue;

                double cos_theta = p_normal * sample_ray_direction * (-1.0);
                double cos_theta_ = light_normal * sample_ray_direction;
                double distance = (sample_point - p).get_magnitude();

                // 漫反射部分: diffuse
                // Li * (diffuse / pi) * A * cos(theta) * cos(theta') / distance^2 
                // 一样的 Li, fr, A
                // 不一样的 theta, theta', distance
                diffuse_coefficient += cos_theta * cos_theta_ / distance / distance;

                // 镜面反射部分: specular
                // bsdf sampling
                // Li * (specular * cos(alpha) ^ shiness) * cos(theta) / pdf, pdf = cos(alpha)
                // 不一样的: cos_alpha, cos_theta, shiness
                // 一样的: li, specular

                // light source sampling
                // Li * (specular * cos(alpha) ^ shiness) * A * cos(theta) * cos(theta') / distance^2
                // 不一样的: cos_alpha, theta, theta', distance, shiness
                // 一样的: Li, specular, A
                vector_c half_vector = wo - sample_ray_direction;
                half_vector.normalize();
                double cos_alpha = half_vector * p_normal;

                specular_coefficient += std::pow(std::max(cos_alpha, 0.), shininess) * cos_theta * cos_theta_ / distance / distance;
            }
            double radiance_diffuse_r = light_radiance.get_x() * brdf_diffuse.get_x() / M_PI * light_area * diffuse_coefficient;
            double radiance_diffuse_g = light_radiance.get_y() * brdf_diffuse.get_y() / M_PI * light_area * diffuse_coefficient;
            double radiance_diffuse_b = light_radiance.get_z() * brdf_diffuse.get_z() / M_PI * light_area * diffuse_coefficient;
            double radiance_specular_r = light_radiance.get_x() * brdf_specular.get_x() * specular_coefficient * light_area;
            double radiance_specular_g = light_radiance.get_y() * brdf_specular.get_y() * specular_coefficient * light_area;
            double radiance_specular_b = light_radiance.get_z() * brdf_specular.get_z() * specular_coefficient * light_area;
            // radiance / N
            double radiance_r = (radiance_diffuse_r + radiance_specular_r) / (double)sample_time_each_facet_light_unit;
            double radiance_g = (radiance_diffuse_g + radiance_specular_g) / (double)sample_time_each_facet_light_unit;
            double radiance_b = (radiance_diffuse_b + radiance_specular_b) / (double)sample_time_each_facet_light_unit;

            light_radiance_r += radiance_r;
            light_radiance_g += radiance_g;
            light_radiance_b += radiance_b;
        }
        total_radiance_r += light_radiance_r;
        total_radiance_g += light_radiance_g;
        total_radiance_b += light_radiance_b;
    }

    return vector_c(total_radiance_r, total_radiance_g, total_radiance_b);
}

vector_c renderer::shade_indirect_light(
    const vector_c &p, const int &p_triangle_id,
    const vector_c &wo) const
{
    // Russian Roulette
    // 以一定概率发出一条光线
    double p_rr = 0.5;

    int random_number = std::rand();
    if (random_number > RAND_MAX * p_rr)
        return vector_c(0.0, 0.0, 0.0);

    int triangle_pa_normal_id = object.get_shapes()[0].mesh.indices[3 * p_triangle_id].normal_index;
    int triangle_pb_normal_id = object.get_shapes()[0].mesh.indices[3 * p_triangle_id + 1].normal_index;
    int triangle_pc_normal_id = object.get_shapes()[0].mesh.indices[3 * p_triangle_id + 2].normal_index;

    vector_c triangle_pa_normal(
        object.get_attrib().normals[3 * triangle_pa_normal_id],
        object.get_attrib().normals[3 * triangle_pa_normal_id + 1],
        object.get_attrib().normals[3 * triangle_pa_normal_id + 2]);
    vector_c triangle_pb_normal(
        object.get_attrib().normals[3 * triangle_pb_normal_id],
        object.get_attrib().normals[3 * triangle_pb_normal_id + 1],
        object.get_attrib().normals[3 * triangle_pb_normal_id + 2]);
    vector_c triangle_pc_normal(
        object.get_attrib().normals[3 * triangle_pc_normal_id],
        object.get_attrib().normals[3 * triangle_pc_normal_id + 1],
        object.get_attrib().normals[3 * triangle_pc_normal_id + 2]);

    int triangle_material_id = object.get_shapes()[0].mesh.material_ids[p_triangle_id];
    vector_c triangle_normal = (triangle_pa_normal + triangle_pb_normal + triangle_pc_normal) / 3.0;
    triangle_normal.normalize();
    vector_c &p_normal = triangle_normal;

    // 随机发射一条光线
    vector_c ray_start = p;
    vector_c ray_direction = generate_ray_randomly(p, p_triangle_id);
    // 采样光线所携带的radiance
    vector_c ray_radiance = background_color;

    // 计算是否相交
    int intersection_triangle_id;
    double intersection_t;
    if (!intersection_detection(ray_start, ray_direction, intersection_triangle_id, intersection_t))
        return vector_c(0., 0., 0.);

    // 若相交 计算radiance
    vector_c intersection_point = ray_start + ray_direction * intersection_t;
    // shade
    ray_radiance = shade(intersection_point, intersection_triangle_id, ray_direction * (-1.0));
    vector_c brdf_diffuse(
        object.get_materials()[triangle_material_id].diffuse[0],
        object.get_materials()[triangle_material_id].diffuse[1],
        object.get_materials()[triangle_material_id].diffuse[2]);
    vector_c brdf_specular(
        object.get_materials()[triangle_material_id].specular[0],
        object.get_materials()[triangle_material_id].specular[1],
        object.get_materials()[triangle_material_id].specular[2]);
    double shininess = object.get_materials()[triangle_material_id].shininess;
    double cos_theta = p_normal * ray_direction;
    // 漫反射部分: diffuse
    // Li * brdf_diffuse  * cos(theta) * 2
    double indirect_radiance_r = ray_radiance.get_x() * brdf_diffuse.get_x() * cos_theta *2;
    double indirect_radiance_g = ray_radiance.get_y() * brdf_diffuse.get_y() * cos_theta *2;
    double indirect_radiance_b = ray_radiance.get_z() * brdf_diffuse.get_z() * cos_theta *2;
    // 镜面反射部分: specular
    // Li * fr * cos(alpha)^shi * cos(theta) * 2pi
    vector_c half_vector = wo + ray_direction;
    half_vector.normalize();
    double cos_alpha = half_vector * p_normal;
    indirect_radiance_r += ray_radiance.get_x() * brdf_specular.get_x() * (2* M_PI) * std::pow(cos_alpha, shininess) * cos_theta;
    indirect_radiance_g += ray_radiance.get_y() * brdf_specular.get_y() * (2* M_PI) * std::pow(cos_alpha, shininess) * cos_theta;
    indirect_radiance_b += ray_radiance.get_z() * brdf_specular.get_z() * (2* M_PI) * std::pow(cos_alpha, shininess) * cos_theta;

    // 除以prr
    indirect_radiance_r /= p_rr;
    indirect_radiance_g /= p_rr;
    indirect_radiance_b /= p_rr;

    return vector_c(indirect_radiance_r, indirect_radiance_g, indirect_radiance_b);
}

int renderer::gamma_correction(const double &gamma)
{
    for (int i = 0; i < r_values.size(); i++)
    {
        r_values[i] = std::pow(r_values[i], 1.0 / gamma);
        g_values[i] = std::pow(g_values[i], 1.0 / gamma);
        b_values[i] = std::pow(b_values[i], 1.0 / gamma);
    }
    return 1;
}

int renderer::write2jpg()
{
    std::string picture_file_name = case_file_name + ".jpg";
    int camera_height = camera.get_height(), camera_width = camera.get_width();
    unsigned char *colorData = new unsigned char[camera_height * camera_width * 3];
    for (int ii = 0; ii < camera_height; ii++)
    {
        for (int jj = 0; jj < camera_width; jj++)
        {
            colorData[3 * ii * camera_width + 3 * jj] = std::round(255.0 * r_values[camera_width * ii + jj]);
            colorData[3 * ii * camera_width + 3 * jj + 1] = std::round(255.0 * g_values[camera_width * ii + jj]);
            colorData[3 * ii * camera_width + 3 * jj + 2] = std::round(255.0 * b_values[camera_width * ii + jj]);
        }
    }
    write_jpg(picture_file_name.c_str(), camera_width, camera_height, 3, colorData, camera_width * camera_height);
    delete[] colorData;
    colorData = nullptr;
    return 1;
}

int renderer::normalize_color()
{
    for (int i = 0; i < r_values.size(); i++)
    {
        if (r_values[i] >= 1.0)
            r_values[i] = 1.0;
        if (g_values[i] >= 1.0)
            g_values[i] = 1.0;
        if (b_values[i] >= 1.0)
            b_values[i] = 1.0;
    }
    return 1;
}

int renderer::get_sampling_strategy() const{
    return sampling_strategy;
}

int renderer::set_sampling_strategy(const int& strategy){
    sampling_strategy = strategy;
    return 1;
}

vector_c renderer::generate_ray_randomly(
    const vector_c &p, const int &p_triangle_id
)const{
    // 计算p点法向和平面极轴
    int triangle_pa_id = object.get_shapes()[0].mesh.indices[3 * p_triangle_id].vertex_index;
    // int triangle_pb_id = object.get_shapes()[0].mesh.indices[3 * p_triangle_id + 1].vertex_index;
    // int triangle_pc_id = object.get_shapes()[0].mesh.indices[3 * p_triangle_id + 2].vertex_index;

    int triangle_pa_normal_id = object.get_shapes()[0].mesh.indices[3 * p_triangle_id].normal_index;
    int triangle_pb_normal_id = object.get_shapes()[0].mesh.indices[3 * p_triangle_id + 1].normal_index;
    int triangle_pc_normal_id = object.get_shapes()[0].mesh.indices[3 * p_triangle_id + 2].normal_index;

    vector_c triangle_pa_normal(
        object.get_attrib().normals[3 * triangle_pa_normal_id],
        object.get_attrib().normals[3 * triangle_pa_normal_id + 1],
        object.get_attrib().normals[3 * triangle_pa_normal_id + 2]);
    vector_c triangle_pb_normal(
        object.get_attrib().normals[3 * triangle_pb_normal_id],
        object.get_attrib().normals[3 * triangle_pb_normal_id + 1],
        object.get_attrib().normals[3 * triangle_pb_normal_id + 2]);
    vector_c triangle_pc_normal(
        object.get_attrib().normals[3 * triangle_pc_normal_id],
        object.get_attrib().normals[3 * triangle_pc_normal_id + 1],
        object.get_attrib().normals[3 * triangle_pc_normal_id + 2]);

    vector_c triangle_normal = triangle_pa_normal + triangle_pb_normal + triangle_pc_normal;
    triangle_normal /= 3.0;
    triangle_normal.normalize();

    vector_c triangle_pa(
        object.get_attrib().vertices[3 * triangle_pa_id],
        object.get_attrib().vertices[3 * triangle_pa_id + 1],
        object.get_attrib().vertices[3 * triangle_pa_id + 2]);
    vector_c triangle_x = triangle_pa - p;
    triangle_x.normalize();

    vector_c triangle_y = triangle_x ^ triangle_normal;

    double theta = (double)std::rand() / (double)RAND_MAX * (2*M_PI);
    double alpha = (double)std::rand() / (double)RAND_MAX * M_PI;

    vector_c temp =  triangle_y * (- std::tan(theta));
    temp = temp + triangle_x;
    temp.normalize();
    vector_c ray = triangle_normal * std::tan(alpha);
    ray = ray + temp;
    ray.normalize();

    return ray;
}
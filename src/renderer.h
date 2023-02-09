#pragma once
#include "camera.h"
#include "light.h"
#include "object.h"
#include <string>
#include "bvh_tree.h"

/**
 * @brief renderer class
 * @author Liu Zhixing, liuzhixing0525@163.com
 * @date 2022-10-06
 * 
 */
class renderer{
public:
    renderer() {}
    ~renderer() {}

    int set_case_file_name(const std::string& case_name);
    int load_case();

    /**
     * @brief the rendering process
     * 
     * @return int 1: success
     */
    int rendering();

    /**
     * @brief trace a ray, get the radiance
     * 
     * @param ray_starting starting point of ray
     * @param ray_direction direction of ray
     * @return vector_c radiance of this ray, rgb
     */
    vector_c path_tracing(
        const vector_c& ray_starting, const vector_c& ray_direction
    );

    /**
     * @brief intersection detection between a ray and object
     * 
     * @param ray_starting starting point of ray
     * @param ray_direction direction of ray
     * @param triangle_id id of the intersected triangle
     * @param if true, intersection_t position of intersection point
     * @return true intersection exists
     * @return false no intersection
     */
    bool intersection_detection(
        const vector_c& ray_starting, const vector_c& ray_direction,
        int& triangle_id, double& intersection_t
    ) const;

    /**
     * @brief intersection detection between a ray and a triangle
     * 
     * @param ray_starting 
     * @param ray_direction 
     * @param triangle_id 
     * @param intersection_t if intersection exists, the intersection time
     * @return true intersection exists
     * @return false no intersection
     */
    bool intersection_detection_ray_triangle(
        const vector_c& ray_starting, const vector_c& ray_direction,
        const int& triangle_id,
        double& intersection_t
    ) const;

    /**
     * @brief Get the first pixel of camera screen
     * 
     * @return 1 success
     */
    int get_screen_position();

    /**
     * @brief three points define a plane
     * 
     * @param pa triangle vertex
     * @param pb triangle vertex
     * @param pc triangle vertex
     * @param AA parameter of plane equation
     * @param BB parameter of plane equation
     * @param CC parameter of plane equation
     * @param DD parameter of plane equation
     * @return 1 success
     * @return 0 three points locating on a line
     */
    int plane(
        const vector_c& pa, const vector_c& pb, const vector_c& pc,
        double& AA, double& BB, double& CC, double& DD
    ) const;

    /**
     * @brief tell if point inside triangle
     * 
     * @param ps point to be told
     * @param pa triangle vertex
     * @param pb triangle vertex
     * @param pc triangle vertex
     * @return 1 inside
     * @return 0 located on boundary
     * @return -1 outside
     */
    int point_inside_triangle(
        const vector_c& ps,
        const vector_c& pa, const vector_c& pb, const vector_c& pc
    ) const;

    /**
     * @brief solve the rendering equation
     * 
     * @param p shading point
     * @param p_triangle_id the triangle p located on
     * @param wo direction of out ray
     * @return vector_c radiance, rgb
     */
    vector_c shade(
        const vector_c& p, const int& p_triangle_id,
        const vector_c& wo
    ) const;

    /**
     * @brief solve the direct light part of rendering equation
     * 
     * @param p 
     * @param p_triangle_id 
     * @param wo 
     * @return vector_c 
     */
    vector_c shade_direct_light(
        const vector_c& p, const int& p_triangle_id,
        const vector_c& wo
    )const;

    vector_c shade_indirect_light(
        const vector_c&p, const int& p_triangle_id,
        const vector_c& wo
    )const;

    vector_c sampling_light_source(
        const vector_c &p, const int &p_triangle_id,
        const vector_c &wo
    )const;

    vector_c sampling_bsdf(
        const vector_c &p, const int &p_triangle_id,
        const vector_c &wo
    )const;

    vector_c generate_ray_randomly(
        const vector_c &p, const int &p_triangle_id
    )const;

    vector_c calculate_lo(
        const vector_c &p, const int &p_triangle_id, const vector_c& wo_direction,
        const vector_c &wi_direction, const vector_c& wi_radiance
    )const;

    /**
     * @brief tell if a facet is light
     * 
     * @param facet_id facet
     * @param light_radiance if is light, saving the radiance
     * @return true is light
     * @return false is not light
     */
    bool is_light(const int& facet_id, vector_c& light_radiance) const;

    /**
     * @brief calculate the area of a triangle
     * 
     * @param pa triangle vertex
     * @param pb triangle vertex
     * @param pc triangle vertex
     * @return double triangle area
     */
    double triangle_area(
        const vector_c& pa, const vector_c& pb, const vector_c& pc
    ) const;

    /**
     * @brief initialize light, get the facet ids of light units
     * 
     * @return 1 success
     */
    int initialize_light();

    /**
     * @brief color gamma correction
     * 
     * @return 1 success
     */
    int gamma_correction(const double& gamma = 2.2);

    int normalize_color();

    int write2jpg();

    int get_sampling_strategy() const;

    int set_sampling_strategy(const int& strategy = 0);
private:
    camera_c camera;                                        /* camera: only one camera supported */
    light_c light;                                          /* light: a group of facet lights */
    object_c object;                                        /* object: vertices and triangle facets */

    std::string case_file_name;                             /* case: name of obj and other files */

    int sample_time_each_pixel{1};                          /* sample times when Monte Carlo */
    int sample_time_each_facet_light_unit{1};               /* sample times when sampling light source */
    int sample_time_bsdf{100};                                /* sample time when bsdf sampling */

    vector_c screen_top;                                    /* top-left position of camera screen */

    vector_c background_color{ vector_c(1.0, 1.0, 1.0) };   /* background color: dark */
    std::vector<float> r_values;                            /* render result */
    std::vector<float> g_values;                            /* render result */
    std::vector<float> b_values;                            /* render result */

    bvh_tree_* bvh_tree{nullptr};                           /* accelerating data structure */

    double EPS{ 1e-6 };                                     /* epsiron */

    int sampling_strategy{0};                               /* sampling strageties, 0: light source, 1: BSDF */
};
#pragma once
#include "tiny_obj_loader.h"
#include <vector>

class object_c
{
public:
    object_c() {}
    ~object_c() {}

    int read_object_from_obj_file(const char *file_name);

    const tinyobj::attrib_t &get_attrib() const;
    const std::vector<tinyobj::shape_t> &get_shapes() const;
    const std::vector<tinyobj::material_t> &get_materials() const;

private:
    // attrib_t::vertices => 3 floats per vertex

    //        v[0]        v[1]        v[2]        v[3]               v[n-1]
    //   +-----------+-----------+-----------+-----------+      +-----------+
    //   | x | y | z | x | y | z | x | y | z | x | y | z | .... | x | y | z |
    //   +-----------+-----------+-----------+-----------+      +-----------+

    // attrib_t::normals => 3 floats per vertex

    //        n[0]        n[1]        n[2]        n[3]               n[n-1]
    //   +-----------+-----------+-----------+-----------+      +-----------+
    //   | x | y | z | x | y | z | x | y | z | x | y | z | .... | x | y | z |
    //   +-----------+-----------+-----------+-----------+      +-----------+

    // attrib_t::texcoords => 2 floats per vertex

    //        t[0]        t[1]        t[2]        t[3]               t[n-1]
    //   +-----------+-----------+-----------+-----------+      +-----------+
    //   |  u  |  v  |  u  |  v  |  u  |  v  |  u  |  v  | .... |  u  |  v  |
    //   +-----------+-----------+-----------+-----------+      +-----------+

    // attrib_t::colors => 3 floats per vertex(vertex color. optional)

    //        c[0]        c[1]        c[2]        c[3]               c[n-1]
    //   +-----------+-----------+-----------+-----------+      +-----------+
    //   | x | y | z | x | y | z | x | y | z | x | y | z | .... | x | y | z |
    //   +-----------+-----------+-----------+-----------+      +-----------+
    tinyobj::attrib_t attrib;

    // mesh_t::indices => array of vertex indices.

    //   +----+----+----+----+----+----+----+----+----+----+     +--------+
    //   | i0 | i1 | i2 | i3 | i4 | i5 | i6 | i7 | i8 | i9 | ... | i(n-1) |
    //   +----+----+----+----+----+----+----+----+----+----+     +--------+

    // Each index has an array index to attrib_t::vertices, attrib_t::normals and attrib_t::texcoords.

    // mesh_t::num_face_vertices => array of the number of vertices per face(e.g. 3 = triangle, 4 = quad , 5 or more = N-gons).

    //   +---+---+---+        +---+
    //   | 3 | 4 | 3 | ...... | 3 |
    //   +---+---+---+        +---+
    //     |   |   |            |
    //     |   |   |            +-----------------------------------------+
    //     |   |   |                                                      |
    //     |   |   +------------------------------+                       |
    //     |   |                                  |                       |
    //     |   +------------------+               |                       |
    //     |                      |               |                       |
    //     |/                     |/              |/                      |/

    //  mesh_t::indices

    //   |    face[0]   |       face[1]     |    face[2]   |     |      face[n-1]           |
    //   +----+----+----+----+----+----+----+----+----+----+     +--------+--------+--------+
    //   | i0 | i1 | i2 | i3 | i4 | i5 | i6 | i7 | i8 | i9 | ... | i(n-3) | i(n-2) | i(n-1) |
    //   +----+----+----+----+----+----+----+----+----+----+     +--------+--------+--------+
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
};
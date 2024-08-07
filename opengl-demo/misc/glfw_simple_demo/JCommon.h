#ifndef JCOMMON_H_
#define JCOMMON_H_

enum ShaderType {
    ShaderType_Vertex,
    ShaderType_Fragment,
};

/*
struct Vertex {
    vec2 pos; // position in 2d
    vec3 col; // color (RGB)
};*/

struct Vertex {
    float x, y, z;

    Vertex(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};

struct LineSegment {
    Vertex start;
    Vertex end;
};


#endif //JCOMMON_H_

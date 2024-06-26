#ifndef JCOMMON_H_
#define JCOMMON_H_

enum ShaderType {
    ShaderType_Vertex,
    ShaderType_Fragment,
};

struct Vert {
    float x, y, z;

    Vert(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};

#endif //JCOMMON_H_

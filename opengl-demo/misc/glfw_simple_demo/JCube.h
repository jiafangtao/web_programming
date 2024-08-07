#pragma once

#include <vector>
#include "JRenderObject.h"


class Cube : public JRenderObject {
public:
    static Cube makeCube(float x, float y, float z, float l, float w, float h);
    Cube(const Cube& other);
    void operator=(const Cube& other);

    virtual int vertexCount() const override { return 8; }
    virtual std::vector<Vertex> getVertices() const override;

    virtual int lineCount() const override { return 12; }
    virtual std::vector<int> getLines() const = 0;

    /// <summary>
    /// Returns the count of triangles in this object
    /// </summary>
    /// <returns></returns>
    virtual int triangleCount() const override { return 12; }

    /// <summary>
    /// Returns vertex ids of the triangles. The IDs are subset of the vertex set.
    /// </summary>
    /// <returns></returns>
    virtual std::vector<int> getTriangles() const = 0;

private:
    Cube();

    // base point
    float baseX, baseY, baseZ;
    float length, width, height;
};

#ifndef JRENDEROBJECT_H_
#define JRENDEROBJECT_H_

#include <vector>

#include "JCommon.h"

class JRenderObject {
public:
    virtual ~JRenderObject() = default;

    virtual int vertexCount() const = 0;
    virtual std::vector<Vertex> getVertices() const = 0;

    virtual int lineCount() const = 0;
    virtual std::vector<int> getLines() const = 0;

    /// <summary>
    /// Returns the count of triangles in this object
    /// </summary>
    /// <returns></returns>
    virtual int triangleCount() const = 0;

    /// <summary>
    /// Returns vertex ids of the triangles. The IDs are subset of the vertex set.
    /// </summary>
    /// <returns></returns>
    virtual std::vector<int> getTriangles() const = 0;
    
    /// <summary>
    /// Render the object in current GL context.
    /// </summary>
    virtual void render() = 0;
};

#endif //JRENDEROBJECT_H_

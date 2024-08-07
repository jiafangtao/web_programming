#pragma once

#include "JRenderObject.h"

class JPoints : public JRenderObject
{
public:
    JPoints(const Vertex&);
    JPoints(float x, float y, float z);

    virtual int vertexCount() const override;
    virtual std::vector<Vertex> getVertices() const override;

    virtual int lineCount() const override { return 0; }
    virtual std::vector<int> getLines() const override {
        return std::vector<int>();
    }

    virtual int triangleCount() const override { return 0; }

    virtual std::vector<int> getTriangles() const {
        return std::vector<int>();
    }

private:
    Vertex m_vet;
};

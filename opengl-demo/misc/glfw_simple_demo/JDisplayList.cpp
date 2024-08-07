#include "JDisplayList.h"
#include "JCommon.h"
#include "JError.h"
#include <algorithm>
#include <glad/glad.h>


JDisplayList::JDisplayList() : m_dl(0) {}

JDisplayList::~JDisplayList() {
    destroy();
}

void JDisplayList::render() {
    if (m_dl != 0) {
        glCallList(m_dl);
    }
}

JDisplayList& JDisplayList::create() {
    GLuint dl = glGenLists(1);
    if (dl == 0) {
        throw new JError("failed to generate display list");
    }

    m_dl = dl;
    return *this;
}

void JDisplayList::destroy() {
    if (m_dl != 0) {
        glDeleteLists(m_dl, 1);
        m_dl = 0;
    }
}

JDisplayList& JDisplayList::begin() {
    glNewList(m_dl, GL_COMPILE);
    return *this;
}

JDisplayList& JDisplayList::end() {
    glEndList();
    return *this;
}

JDisplayList& JDisplayList::lineLoop(const std::vector<Vertex> & verts) {
    glBegin(GL_LINE_LOOP);
    std::for_each(verts.begin(), verts.end(), [](const Vertex& v) { glVertex3f(v.x, v.y, v.z); });
    glEnd();
    return *this;
}

JDisplayList& JDisplayList::polygon(const std::vector<Vertex>& verts) {
    glBegin(GL_POLYGON);
    std::for_each(verts.begin(), verts.end(), [](const Vertex& v) { glVertex3f(v.x, v.y, v.z); });
    glEnd();
    return *this;
}

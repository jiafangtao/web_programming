#ifndef JDISPLAYLIST_H_
#define JDISPLAYLIST_H_

#include "JRenderObject.h"
#include "JCommon.h"
#include <vector>
#include <glad/glad.h>

class JDisplayList : public JRenderObject
{
public:
    JDisplayList();
    virtual ~JDisplayList();

    virtual JDisplayList& create();
    virtual void destroy();

    GLuint dl() const { return m_dl; }

    virtual void render();
    virtual JDisplayList& begin();
    virtual JDisplayList& end();
    virtual JDisplayList& lineLoop(const std::vector<Vertex>& verts);
    virtual JDisplayList& polygon(const std::vector<Vertex>& verts);

private:
    GLuint m_dl;
};

#endif //JDISPLAYLIST_H_

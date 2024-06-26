#ifndef JRENDEROBJECT_H_
#define JRENDEROBJECT_H_

class JRenderObject {
public:
    virtual ~JRenderObject() = default;
    
    /// <summary>
    /// Render the object in current GL context.
    /// </summary>
    virtual void render() = 0;
};

#endif //JRENDEROBJECT_H_

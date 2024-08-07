#ifndef JSCENE_H_
#define JSCENE_H_

//#include <vector>

class RenderObject;


class JScene
{
public:
    JScene();
    virtual ~JScene();

    virtual void addObject(RenderObject & obj);
    virtual void removeObject(RenderObject& obj);
    //virtual std::vector<RenderObject & > getObjects();

    virtual void findObject(int id, RenderObject * & out) const;
};

#endif//JSCENE_H_

//
//

#ifndef DERIVED_ACTIVE_OBJECT_H
#define dERIVED_ACTIVE_OBJECT_H

#include "ActiveObject.h"

using namespace std;


class DerivedActiveObject : public ActiveObject<Content_3>{
public:
    DerivedActiveObject(){}

protected:
    virtual void Service(Content_3& request) override{
        DoingStuff();
    }
private:
    void DoingStuff(){}
};


#endif

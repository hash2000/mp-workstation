#ifndef __SystemObjectsKey_H__
#define __SystemObjectsKey_H__


enum class SystemObjectType : int
{
    Undefined = 0,
};


struct SystemObjectsKey
{
    int Id;
    int ParentId;
    SystemObjectType Type;
};



#endif // !__SystemObjectsKey_H__
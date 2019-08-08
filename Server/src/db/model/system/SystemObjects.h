#ifndef __SystemObjects_H__
#define __SystemObjects_H__


enum class SystemObjectType : int
{
    Directory = 0,
    Dimension,
    DimensionAttribute,
};


struct SystemObject
{
    int Id;
    int ParentId;
    SystemObjectType Type;
};



#endif // !__SystemObjects_H__
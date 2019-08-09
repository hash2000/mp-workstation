#ifndef __SystemObjects_H__
#define __SystemObjects_H__

#include <string>

enum class SystemObjectType : int
{
    Directory = 0,
    Dimension,
    DimensionAttribute,
};


struct SystemObjectData
{
    int ParentId;
    SystemObjectType Type;
    int NameLength;
};

class SystemObject : public SystemObjectData
{
public:
    SystemObject() {
    }
    
    SystemObject(const SystemObjectData * value, std::size_t id) 
        : Id(id) {
        CopyFromKey(value);
    }

    void CopyFromKey(const SystemObjectData * value) {
        ParentId = value->ParentId;
        Type = value->Type;
        NameLength = value->NameLength;
        ReadTypeName(value);
        ReadKeyName(value);
    }

    void ReadTypeName(const SystemObjectData * value) {
        switch (value->Type) {
            case SystemObjectType::Directory:
                TypeName = "Directory";
                break;
            case SystemObjectType::Dimension:
                TypeName = "Dimension";
                break;        
            case SystemObjectType::DimensionAttribute:
                TypeName = "DimensionAttribute";
                break; 
        }

        TypeName = "Undefined";
    }

    void ReadKeyName(const SystemObjectData * value) {
        auto namePtr = reinterpret_cast<const char*>(value) + sizeof(SystemObjectData);
        Name.clear();
        Name.append(namePtr, value->NameLength);
    }

public:
    std::size_t Id;
    std::string TypeName;
    std::string Name;
};


#endif // !__SystemObjects_H__
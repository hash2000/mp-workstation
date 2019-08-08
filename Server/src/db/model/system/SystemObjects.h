#ifndef __SystemObjects_H__
#define __SystemObjects_H__

#include <string>

enum class SystemObjectType : int
{
    Directory = 0,
    Dimension,
    DimensionAttribute,
};


struct SystemObjectKey
{
    int Id;
    int ParentId;
    SystemObjectType Type;
    int NameLength;
};

class SystemObject : public SystemObjectKey
{
public:
    SystemObject() {
    }
    
    SystemObject(const SystemObjectKey * key) {
        CopyFromKey(key);
    }

    void CopyFromKey(const SystemObjectKey * key) {
        Id = key->Id;
        ParentId = key->ParentId;
        Type = key->Type;
        NameLength = key->NameLength;
        ReadTypeName(key);
        ReadKeyName(key);
    }

    void ReadTypeName(const SystemObjectKey * key) {
        switch (key->Type) {
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

    void ReadKeyName(const SystemObjectKey * key) {
        auto namePtr = reinterpret_cast<const char*>(key) + sizeof(SystemObjectKey);
        Name.clear();
        Name.append(namePtr, key->NameLength);
    }

public:
    std::string TypeName;
    std::string Name;
};


#endif // !__SystemObjects_H__
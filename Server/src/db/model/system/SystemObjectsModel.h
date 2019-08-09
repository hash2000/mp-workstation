#ifndef __SystemObjectsModel_H__
#define __SystemObjectsModel_H__

#include "../ModelWrapper.h"
#include "SystemObjects.h"

#include <atomic>
#include <list>
#include <map>

class SystemObjectsModel : public ModelWrapper
{
public:

    // Инициализация таблицы
    bool Initialize(const std::string &path,
        leveldb::Comparator * comparator = nullptr) override;

    // Добавить элемент
    std::shared_ptr<SystemObject> Add(std::size_t parentId, SystemObjectType type, 
        const std::string & name);

    std::shared_ptr<SystemObject> Update(std::size_t id, std::size_t parentId, SystemObjectType type, 
        const std::string & name);

    // Прочитать элемент
    SystemObjectData* GetItemData(std::size_t id);

    std::shared_ptr<SystemObject> GetItem(std::size_t id);

    // Вернуть набор элеметнов, у которых родительский узел
    //  имеет идентификатор (id)
    void GetNode(std::list<std::shared_ptr<SystemObject>> & result,
        std::size_t id);

private:

    // Добавить элемент в индекс IX_ParentId
    void IndexTo_IX_ParentId(
        std::size_t id, std::size_t parentId);

private:
    std::atomic<std::size_t> _identity;
    
    // Индексатор по ParentId
    std::map<std::size_t, std::list<std::size_t>> _IX_ParentId;

};


#endif // !__SystemObjectsModel_H__
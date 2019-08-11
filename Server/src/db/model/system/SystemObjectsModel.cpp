#include <stdafx.h>
#include "SystemObjectsModel.h"


bool SystemObjectsModel::Initialize(const std::string &path,
        leveldb::Comparator * comparator)
{
    if (!ModelWrapper::Initialize(path, comparator))
        return false;

    std::unique_ptr<leveldb::Iterator> it(
        _store->NewIterator(leveldb::ReadOptions()));
        
    for (it->SeekToFirst(); it->Valid(); it->Next())
    {
        auto keySlice = it->key();
        auto id = reinterpret_cast<const std::size_t *>(keySlice.data());
        // чтение идентификаторов, для определения максимального
        if (_identity.load(std::memory_order_relaxed) < *id)
            _identity = *id;

        auto valueSlice = it->value();
        auto dataBuffer = valueSlice.data();
        auto data = reinterpret_cast<const SystemObjectData*>(dataBuffer);

        AddIndexTo_IX_ParentId(*id, data->ParentId);
    }

    return true;
}

void SystemObjectsModel::AddIndexTo_IX_ParentId(
        std::size_t id, std::size_t parentId)
{
    auto index_ParentId = _IX_ParentId.insert(std::make_pair(parentId, 
        std::set<std::size_t>()));
    index_ParentId.first->second.insert(id);
}

void SystemObjectsModel::DeleteIndexFrom_IX_ParentId(
        std::size_t id, std::size_t parentId)
{
    auto index_ParentId = _IX_ParentId.find(parentId);
    if (index_ParentId != _IX_ParentId.end()) {
        index_ParentId->second.erase(index_ParentId->second.find(id));
    }

}

std::shared_ptr<SystemObject> SystemObjectsModel::Add(std::size_t parentId, SystemObjectType type, 
        const std::string & name)
{
    auto id = _identity.fetch_add(1);
    auto dataSize = sizeof(SystemObjectData) + name.length();
    std::string value;
    value.resize(dataSize);
    auto dataBuffer = &value.front();
    auto data = reinterpret_cast<SystemObjectData*>(dataBuffer);
    data->ParentId = parentId;
    data->Type = type;
    data->NameLength = (int)name.length();
    auto nameBuffer = dataBuffer + sizeof(SystemObjectData);
    std::copy(name.begin(), name.end(), nameBuffer);

    auto status = _store->Put(leveldb::WriteOptions(), 
        leveldb::Slice(reinterpret_cast<const char*>(&id), sizeof(id)),
        leveldb::Slice(dataBuffer, dataSize));
    if (!status.ok())
        return std::shared_ptr<SystemObject>();

    AddIndexTo_IX_ParentId(id, data->ParentId);

    auto result = new SystemObject(data, id);
    return std::shared_ptr<SystemObject>(result);
}

std::shared_ptr<SystemObject> SystemObjectsModel::Update(std::size_t id, std::size_t parentId, SystemObjectType type, 
    const std::string & name)
{
    leveldb::WriteBatch batch;
    leveldb::Slice key(reinterpret_cast<const char*>(&id), sizeof(id));

    std::string value;
    auto status = _store->Get(leveldb::ReadOptions(), key, &value);
    if (!status.ok())
        return std::shared_ptr<SystemObject>();


    // обновление информации об элементе
    auto dataSize = sizeof(SystemObjectData) + name.length();
    value.resize(dataSize);
    auto dataBuffer = &value.front();
    auto data = reinterpret_cast<SystemObjectData*>(dataBuffer);
    auto prevParentId = data->ParentId;
    data->ParentId = parentId;
    data->Type = type;
    data->NameLength = (int)name.length();
    auto nameBuffer = dataBuffer + sizeof(SystemObjectData);
    std::copy(name.begin(), name.end(), nameBuffer);    

    // удаление предыдущего значения 
    batch.Delete(key);

    // добавление элемента обратно
    batch.Put(key, leveldb::Slice(dataBuffer, dataSize));
    
    // применение изменений
    status = _store->Write(leveldb::WriteOptions(), &batch);
    if (!status.ok()) 
        return std::shared_ptr<SystemObject>();

    // Если изменился ParentId
    if (prevParentId != parentId) {    
        // удалить предыдущий индекс
        DeleteIndexFrom_IX_ParentId(id, prevParentId);
        // добавить новый индекс
        AddIndexTo_IX_ParentId(id, parentId);
    }

    auto result = new SystemObject(data, id);
    return std::shared_ptr<SystemObject>(result);
}

void SystemObjectsModel::Delete(std::size_t id)
{
    auto data = GetItemData(id);
    if (!data) 
        return;

    DeleteIndexFrom_IX_ParentId(id, data->ParentId);

    leveldb::Slice key(reinterpret_cast<const char*>(&id), 
        sizeof(id));
    _store->Delete(leveldb::WriteOptions(), 
        key);
}

SystemObjectData* SystemObjectsModel::GetItemData(std::size_t id)
{
    std::string value;
    auto status = _store->Get(leveldb::ReadOptions(), 
        leveldb::Slice(reinterpret_cast<const char*>(&id), sizeof(id)),
        &value);
    if (!status.ok())
        return nullptr;
    auto dataSize = value.length();
    auto dataBuffer = &value.front();
    return reinterpret_cast<SystemObjectData*>(dataBuffer);
}

std::shared_ptr<SystemObject> SystemObjectsModel::GetItem(std::size_t id)
{
    auto data = GetItemData(id);
    if (!data)
        return std::shared_ptr<SystemObject>();
    auto result = new SystemObject(data, id);
    return std::shared_ptr<SystemObject>(result);
}

void SystemObjectsModel::GetNode(std::list<std::shared_ptr<SystemObject>> & result,
        std::size_t id)
{
    auto index = _IX_ParentId.find(id);    
    if (index == _IX_ParentId.end())
        return;

    for (auto 
        begin = index->second.begin(), end = index->second.end();
        begin != end; begin ++) {
            auto id = *begin;
            result.push_back(GetItem(id));
    }
}
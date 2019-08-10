#ifndef __WorkContext_H__
#define __WorkContext_H__

#include "../../layout/LayoutBuilder.h"
#include "../../controller/IBaseController.h"

#include <Poco/Path.h>
#include <Poco/LocalDateTime.h>
#include <Poco/File.h>
#include <Poco/Dynamic/Var.h>

#include <functional>
#include <string>
#include <vector>
#include <atomic>


class WorkContext
{
public:

    // Запрошенный ресурс - html разметка
    // Состоит из общей области описанной в Web/Layout/имя_разметки.html 
    //  (указывается в шаблоне страницы partialView[layout]) и шаблона страницы,
    //  который добавляется в конец области (layout) тега <body>
    LayoutBuilder * _Layout;

    // Зарегистрированный контроллер для обработки текущего маршрута
    // Возвращает данные в формате JSON
    IBaseController * _Controller;

    // Тип контента.
    //  Регистрируется в файле настроек Web/MIME/types.properties
    std::string _ContentType;

    // Если заправшиваемый ресурс - файл
    //  тут будет содержимое файла
    std::string _FileBuffer;

    // Размер файла (используется совместно с _FileBuffer)
    Poco::File::FileSize _FileBufferSize;

    // Дата/Время обновления буфера/шаблона запрошенного ресурса
    Poco::LocalDateTime _ReadTime;

    // Количество использований текущего экземпляра маршрута
    std::atomic_uint32_t _UseCount;

    // Полный путь к заправшиваемому ресурсу, 
    //  если ресурс - файл.
    // Будет пустым если _Controller != null или _Layout != null
    Poco::Path _Path;

    // Параметры клиентского запроса 
    Poco::Dynamic::Var _RequestParameters;
};


#endif // !__WorkContext_H__
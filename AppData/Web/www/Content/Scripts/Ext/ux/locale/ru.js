//Добавлен formatCodes: q - формат для отправки даты на сервер. БЕЗ OffSet !!!!!
Ext.apply(Ext.Date.formatCodes, {
    q: function () {
        return 'Ext.Date.format(m, "Y-m-d H:i:s")';
    }
});



Ext.define('Ext.ux.locale.ru', {

}, function () {
    Ext.define("Ext.ux.locale.ru.picker.Date", {
        override: "Ext.picker.Date",
        format: "d.m.Y",
        startDay: 1
    });

    Ext.define("Ext.ux.locale.ru.form.field.Date", {
        override: "Ext.form.field.Date",
        format: "d.m.Y",
        startDay: 1
    });

    Ext.Date.defaultFormat = 'd.m.Y';

    Ext.Date.formatFunctions['datetime'] = function () {
        return Ext.Date.format(this, 'd.m.Y H:i');
    };

    Ext.Date.formatFunctions['time'] = function () {
        return Ext.Date.format(this, 'H:i');
    };

    Ext.Date.patterns = {
        ISO8601Long: "Y-m-d H:i:s",
        ISO8601Short: "Y-m-d",
        ShortDate: "n/j/Y",
        LongDate: "l, F d, Y",
        FullDateTime: "l, F d, Y g:i:s A",
        MonthDay: "F d",
        ShortTime: "g:i A",
        LongTime: "g:i:s A",
        SortableDateTime: "Y-m-d\\TH:i:s",
        UniversalSortableDateTime: "Y-m-d H:i:sO",
        YearMonth: "F, Y"
    };

    Ext.define("Ext.locale.ru.grid.RowEditor", {
        override: "Ext.grid.RowEditor",
        saveBtnText: "Сохранить",
        cancelBtnText: "Отмена",
        errorsText: "Ошибка",
        dirtyText: "Вы должны сохранить или отменить свои изменения"
    });

    Ext.define("Ext.locale.ru.grid.column.Boolean", {
        override: "Ext.grid.column.Boolean",
        trueText: 'Да',
        falseText: 'Нет'
    });

    Ext.define("Ext.locale.ru.toolbar.Paging", {
        override: "Ext.PagingToolbar",
        beforePageText: "Стр.",
        displayMsg: "С {0} по {1}, из {2}",
        emptyMsg: 'Нет данных'
    });

    //по-умолчанию для полей моделей с типом "date"
    Ext.define('Ext.ux.data.field.Date', {
        override: 'Ext.data.field.Date',
        dateFormat: 'c',
        dateWriteFormat: 'q'
    });
});
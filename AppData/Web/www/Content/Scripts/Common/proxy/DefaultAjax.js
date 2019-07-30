Ext.define('Common.proxy.DefaultAjax', {
    extend: 'Ext.data.proxy.Ajax',
    alias: 'proxy.defaultajax',
    requires: [
        'Common.reader.Default',
        'Common.writer.Default',
        'Ext.ux.ErrorsHandlers'
    ],

    batchActions: false,
    reader: 'defaultreader',
    writer: 'defaultwriter',
    defaultListenerScope: true,

    listeners: {
        exception: 'onException'
    },

    getUrl: function () {
        return Ext.Loader.buildUrl(this.callParent(arguments));
    },

    /**
    Проверка наличия изменений в хранилище
    */
    isDirty: function () {
        var dirty = this.getModifiedRecords().length;
        dirty = dirty || this.getNewRecords().length;
        dirty = dirty || this.getRemovedRecords().length;

        return !!dirty;
    },

    /**
    Обработка исключений прокси
    */
    onException: function (proxy, request, operation, eOpts) {
        Ext.ux.ErrorsHandlers.parseAndShowError(request);
    }
});
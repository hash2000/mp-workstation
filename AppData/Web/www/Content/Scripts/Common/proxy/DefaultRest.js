
/**
Базовый прокси для Rest
*/
Ext.define('Common.proxy.DefaultRest', {
    extend: 'Common.proxy.DefaultAjax',
    alias: 'proxy.defaultrest',

    actionMethods: {
        create: 'POST',
        read: 'GET',
        update: 'PUT',
        destroy: 'DELETE'
    }
});
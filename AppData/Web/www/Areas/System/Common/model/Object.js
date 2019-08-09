/**
    Описатель объекта
*/
Ext.define('SystemCommon.model.Object', {
    extend: 'Ext.data.TreeModel',
    fields: [
        'Name',
        'TypeId',
        'TypeName'
    ],

    proxy: {
        type: 'defaultrest',

        api: {
            read: 'System/Objects/Get',
            create: 'System/Objects/Add',
            update: 'System/Objects/Update'
        },

        reader: {
            type: 'json',
            rootProperty: 'children',
            messageProperty: 'message'
        }
    }
});
/**
    Описатель объекта
*/
Ext.define('SystemCommon.model.ObjectType', {
    extend: 'Ext.data.TreeModel',
    fields: [
        'Name'
    ],

    proxy: {
        type: 'defaultrest',

        api: {
            read: 'System/ObjectTypes/Get'
        },

        reader: {
            type: 'json',
            rootProperty: 'children',
            messageProperty: 'message'
        }
    }
});
/**
    Описатель объекта
*/
Ext.define('SystemCommon.model.ObjectType', {
    extend: 'Ext.data.Model',
    idProperty: 'Id',
    fields: [
        'Name'
    ],

    proxy: {
        type: 'defaultrest',
        api: {
            read: 'System/ObjectTypes/Get'
        }
    }
});
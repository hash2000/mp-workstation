Ext.define('SystemObjects.view.Model', {
    extend: 'Ext.app.ViewModel',
    alias: 'viewmodel.SystemObjectsModel',

    requires: [
        'SystemCommon.model.Object',
        'SystemCommon.model.ObjectType'
    ],

    data: {
        // Для копирования
        ItemCopy: null
    },

    formulas: {
        Item: {
            bind: '{ObjectsTree.selection}',
            get: function (value) {
                return value;
            }
        }
    },

    stores: {
        
        Items: {
            type: 'tree',
            model: 'SystemCommon.model.Object',
            autoLoad: false,
            autoSync: false,
            remoteFilter: true,
            sorters: [{
                property: 'Name',
                direction: 'ASC'
            }],
            root: {
                Id: null,
                Name: 'Все Объекты',
                expanded: true
            }
        }

    }


});

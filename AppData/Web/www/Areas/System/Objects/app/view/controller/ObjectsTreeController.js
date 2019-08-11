Ext.define('SystemObjects.view.controller.ObjectsTreeController', {
    extend: 'Common.controller.BaseController',
    alias: 'controller.ObjectsTreeController',


    requires: [
        'SystemCommon.window.ObjectWindow'
    ],

    /**
    *   Редактирование статьи
    */
    onItem_dblclick: function (btn) {
        var me = this,
            vm = me.getViewModel(),
            item = vm.get('Item'),
            store = vm.getStore('Items');

        if (Ext.isEmpty(item) || item.isRoot()) {
            return;
        }

        me.showItemWindow('ObjectWindow', item, store,
            'Изменить');
    },

    /** 
    *   Добавить статью
    */
    onAdd_click: function (btn) {
        var me = this,
            vm = me.getViewModel(),
            parent = vm.get('Item'),
            store = vm.getStore('Items');

        if (Ext.isEmpty(parent)) {
            return;
        }

        var newItem = new SystemCommon.model.Object({
            parentId: parent.get('id'),
            ViewOrder: 2147483647
        });

        parent.appendChild(newItem);

        me.showItemWindow('ObjectWindow', newItem, store,
            'Добавить');
    },

    /** 
    *   Удаление статью
    */
    onRemove_click: function (self) {
        var me = this,
            vm = me.getViewModel(),
            item = vm.get('Item'),
            store = vm.getStore('Items');

        me.RemoveItem(item, store,
            'System/Objects/Delete');
    },

    onReload_click: function (self) {
        var me = this,
            vm = me.getViewModel(),
            item = vm.get('Item'),
            store = vm.getStore('Items');

        store.load({
            node: item,
            callback: function (records, operation, success) {
                if (success) {
                    // TODO: при закрытом, если узел не открыть вручную, то на нем пропадет 'крестик',
                    //  даже если прилетят записи. 
                    // при открытом узле, он перезагружается нормально
                    if (records.length > 0)
                        item.expand();
                }
                else {
                    Common.Popup.red('Внимание', 'Ошибка при загрузке');
                }
            }
        });
    },

    /** 
    *   Запомнить объект
    */
    onCopy_click: function (self) {
        var me = this,
            vm = me.getViewModel(),
            item = vm.get('Item');
        vm.set('ItemCopy', item);
    },

    /** 
    *   Вставить скопированный объект
    */
    onPaste_click: function (self) {
        var me = this,
            vm = me.getViewModel(),
            parent = vm.get('Item'),
            store = vm.getStore('Items'),
            item = vm.get('ItemCopy');
        if (Ext.isEmpty(item))
            return;
        var newItem = item.copy(null);

        parent.appendChild(newItem);
        me.openItemWindow(newItem, store);
    }

});



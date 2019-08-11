Ext.define('Common.controller.BaseController', {
    extend: 'Ext.app.ViewController',

    /**
    * Отобразить меню
    *     если у элемента меню объявлен флаг isItemOnly = true, тогда этот элемент отображать 
    *         только при щелчке по элементу контейнера
    *     если у элемента меню объявлен флаг isContainerOnly = true, тогда этот элемент отображать 
    *         только при щелчке в контейнере
    */
    showMenu: function (view, event, isContainer) {
        event.stopEvent();
        var items = [];
        if (isContainer === true) {
            Ext.each(view.contextMenu, function (item) {
                if (item.hasOwnProperty('isItemOnly')) {
                    if (item.isItemOnly === true)
                        return;
                }
                items.push(item);
            });
        }
        else {
            Ext.each(view.contextMenu, function (item) {
                if (item.hasOwnProperty('isContainerOnly')) {
                    if (item.isContainerOnly === true)
                        return;
                }
                items.push(item);
            });
        }

        var menu = Ext.widget({
            xtype: 'menu',
            floating: true,
            items: items
        });
        menu.onAdded(view, 0, true);
        menu.showAt(event.getX() - view.getX(), event.getY() - view.getY());
    },

    /*
    Пример:

    viewConfig: {
        contextMenu: [{
            text: 'Добавить',
            glyph: 'xf055@FontAwesome',
            handler: 'onAdd_click'
        }, {
            text: 'Удалить',
            glyph: 'xf00d@FontAwesome',
            handler: 'onRemove_click',
            bind: {
                disabled: '{!FCatalogsType}'
            }
        }],
        //при двойном клике не раскрывает узел
        toggleOnDblClick: false,
        listeners: {
            scope: 'controller',
            itemcontextmenu: 'onItemContextmenu',
            containercontextmenu: 'onContainerContextmenu'
        }
    }    
    */

    onItemContextmenu: function (view, record, item, index, e, eOpts) {
        this.showMenu(view, e, false);
    },

    onContainerContextmenu: function (view, e) {
        this.showMenu(view, e, true);
    },

    /** 
    *   Изменение текста с поиском
    *       окно поиска всегда должно находиться внутри панели которую фильтруем (tbar, bbar, header)
    */
    onSearchField_change: function (self, value) {
        var store = self.up('panel').getStore(),
            extraParams = store.getProxy().extraParams;
        if (Ext.isEmpty(extraParams))
            return;

        if (value && value.length) {
            extraParams.query = value;
        } else {
            extraParams.query = '';
        }

        store.load();
    },


    /**
    *   Включить фильтрацию при поиске
    *       окно переключателя всегда должно находиться внутри панели которую фильтруем (tbar, bbar, header)
    */
    onUseFilter_click: function (self, state) {
        var store = store = self.up('panel').getStore(),
            extraParams = store.getProxy().extraParams;
        if (Ext.isEmpty(extraParams))
            return;

        extraParams.useFilter = state;

        store.load();
    },

    /** 
    *   Показать окно редактирования элемента
    */
    showItemWindow: function (widgetName, item, store, title) {
        var me = this;
        Ext.widget(widgetName, {
            controller: me.type,
            title: title,
            item: item,
            buttons: [{
                xtype: 'buttonsave',
                handler: function (self) {
                    var win = self.up('window');
                    me.SaveItem(win, item, store);
                }
            }, {
                xtype: 'buttoncancel',
                handler: function (self) {
                    self.up('window').close();
                }
            }],
            listeners: {
                close: function () {
                    store.rejectChanges();
                }
            }
        }).show();
    },

    /** 
    *   Показать окно просмотра элемента (только чтение)
    */
    showReadOnlyWindowForItem: function (widgetName, item, title) {
        Ext.widget(widgetName, {
            title: title,
            item: item,
            itemIsReadOnly: true,
            buttons: [{
                xtype: 'buttoncancel',
                handler: function (self) {
                    self.up('window').close();
                }
            }]
        }).show();
    },

    /** 
    *   Перетаскивание элементов
    */
    onItem_beforedrop: function (node, data, overModel, dropPosition, dropHandlers) {
        dropHandlers.wait = true;

        Ext.MessageBox.confirm('Переместить?', '<h1><a style="color:red"><b>ВЫ УВЕРЕНЫ?</b></a></h1>', function (btn) {
            if (btn === 'yes') {
                dropHandlers.processDrop();

                var viewOrder = overModel.getData().ViewOrder,
                    treeNode = data.records[0],
                    store = treeNode.getTreeStore();

                if (dropPosition === 'append') {
                    if (overModel.hasChildNodes()) {
                        viewOrder = overModel.lastChild.getData().ViewOrder + 1;
                    }
                    else {
                        viewOrder = 2147483647;
                    }
                }
                else if (dropPosition === 'after') {
                    viewOrder += 1;
                }
                else { //before
                    viewOrder -= 1;
                }

                var parentNode = dropPosition === 'append' ? overModel : overModel.parentNode;
                treeNode.set('ViewOrder', viewOrder);

                if (!parentNode.get('expandable')) {
                    parentNode.set('expandable', true);
                }
                else if (!parentNode.get('expanded')) { 
                    parentNode.expand();
                }

                parentNode.appendChild(treeNode);
                treeNode.save({
                    success: function (record, operation) {
                        Common.Popup.green('Информация', 'Изменён');
                    },
                    failure: function (record, operation) {
                        Common.Popup.red('Внимание', 'Ошибка при изменении');
                    }
                });


            } else {
                dropHandlers.cancelDrop();
            }
        });
    },

    /**
    * Сохранить запись
    * @param {object} win Окно из которого прилетело событие
    * @param {object} item Запись
    * @param {object} store Хранилище записи
    */
    SaveItem: function (win, item, store) {
        var form = win.down('form');
        var updateParentAndCloseWindow = function () {
            var parent = item.parentNode;
            // если дерево, тогда перегрузить дочерние узлы
            if (!Ext.isEmpty(parent)) {
                if (parent.isRoot()) {
                    store.load();
                }
                else {
                    store.load({
                        node: parent
                    });
                }

                if (!parent.get('expanded')) {
                    parent.set('expandable', true);
                    parent.expand();
                }
            }

            win.close();
        };

        if (form.isValid()) {
            if (item.phantom) {
                item.save({
                    success: function (record, operation) {
                        Common.Popup.green('Информация', 'Сохранено успешно');
                        updateParentAndCloseWindow();
                    },
                    failure: function (record, operation) {
                        Common.Popup.red('Внимание', 'Ошибка при сохранении');
                    }
                });
                return;
            }

            if (item.dirty) {
                item.save({
                    success: function (record, operation) {
                        Common.Popup.green('Информация', 'Изменено успешно');
                        updateParentAndCloseWindow();
                    },
                    failure: function (record, operation) {
                        Common.Popup.red('Внимание', 'Ошибка при изменении');
                    }
                });
                return;
            }

            // если ничего не поменяли, то просто закрываем окно
            win.close();
        }
    },

    /**
    * Удалить запись
    * @param {object} item Запись
    * @param {object} store Хранилище записи
    * @param {text} url Адрес метода удаления записи
    */
    RemoveItem: function (item, store, url) {

        if (item.isRoot()) {
            Common.Popup.red('Внимание', 'Этот элемент удалять нельзя');
            return;
        }

        Ext.MessageBox.show({
            title: 'Внимание',
            msg: 'Удалить выбранную запись?',
            icon: Ext.Msg.QUESTION,
            buttons: Ext.MessageBox.YESNO,
            fn: function (btn) {
                if (btn === 'yes') {
                    var recordData = item.getData({
                        // флаг нужно поставить для того, чтобы при чтении данных из записи учитывался 
                        //  флаг persist для филдов 
                        persist: true
                    });
                    var requestConfig = {
                        url: Ext.Loader.buildUrl(url),
                        method: 'DELETE',
                        jsonData: {
                            item: recordData
                        }
                    };
                    var parent = item.parentNode;

                    Ext.Ajax.request(requestConfig).then(function () {
                        store.load({
                            node: parent,
                            callback: function (records, operation, success) {
                                if (success === true) {
                                    if (parent.childNodes.length === 0 && !parent.isRoot()) {
                                        parent.set('expandable', false);
                                        parent.set('expanded', false);
                                    }
                                    else {
                                        parent.set('expandable', true);
                                        parent.set('expanded', true);
                                    }
                                }
                            }
                        });

                        Common.Popup.green('Информация', 'Удалено успешно');
                    })
                    .otherwise(function (result) {
                        Ext.ux.ErrorsHandlers.parseAndShowError(result);
                    });
                }
            }
        });
    }

});

Ext.define('SystemObjects.view.Viewport', {
    extend: 'Ext.container.Viewport',
    xtype: 'SystemObjectsViewport',
    
    layout: 'border',
    cls: 'unselectable borderview',

    requires: [
        'SystemCommon.panel.ObjectsTree',

        'SystemObjects.view.Model',
        'SystemObjects.view.controller.ObjectsTreeController'
    ],

    viewModel: {
        type: 'SystemObjectsModel',
        name: 'SystemObjectsModel'
    },

    items: [{
        tbar: [{
            xtype: 'SearchTextAreaField',
            listeners: {
                change: {
                    fn: 'onSearchField_change',
                    buffer: 1000
                }
            }
        }, {
            xtype: 'checkbox',
            handler: 'onUseFilter_click',
            boxLabel: 'Фильтровать'
        }],
        viewConfig: {
            contextMenu: [{
                text: 'Перезагрузить',
                glyph: 'xf021@FontAwesome',
                handler: 'onReload_click'
            }, '-', {
                text: 'Добавить',
                glyph: 'xf055@FontAwesome',
                handler: 'onAdd_click'
            }, {
                text: 'Удалить',
                glyph: 'xf00d@FontAwesome',
                handler: 'onRemove_click'
            }, '-', {
                text: 'Копировать',
                glyph: 'f0c5@FontAwesome',
                handler: 'onCopy_click'
            }, {
                text: 'Вставить',
                glyph: 'f0ea@FontAwesome',
                handler: 'onPaste_click',
                bind: {
                    disabled: '{!ItemCopy}'
                }
            }],
            //при двойном клике не раскрывает узел
            toggleOnDblClick: false,
            plugins: {
                ptype: 'treeviewdragdrop',
                ddGroup: 'onItem_ddGroup',
                displayField: 'Name'
            },
            listeners: {
                scope: 'controller',
                itemcontextmenu: 'onItemContextmenu',
                containercontextmenu: 'onContainerContextmenu',
                itemdblclick: 'onItem_dblclick',
                beforedrop: 'onItem_beforedrop'
            }
        },

        controller: 'ObjectsTreeController',

        xtype: 'ObjectsTree',
        reference: 'ObjectsTree',
        bind: {
            store: '{Items}'
        },
        title: 'Объекты',
        region: 'center',
        rootVisible: true
    }]
});

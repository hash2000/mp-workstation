/**
Автоматическая привязка PagingToolbar'а к хранилищу таблицы
*/
Ext.define('Ext.ux.toolbar.Paging', {
    override: 'Ext.toolbar.Paging',

    dock: 'bottom',
    displayInfo: true,

    listeners: {
        added: function (me) {
            var grid = me.up('grid'),
                store;

            if (grid) {
                store = grid.getStore();
                if (store) {
                    me.setStore(store);
                }
                grid.on('reconfigure', function (self, store) {
                    me.setStore(store);
                })
            }
        }
    },

    getPagingItems: function () {
        var me = this,
            inputListeners = {
                scope: me,
                blur: me.onPagingBlur
            };
        inputListeners[Ext.supports.SpecialKeyDownRepeat ? 'keydown' : 'keypress'] = me.onPagingKeyDown;

        return [{
            itemId: 'refresh',
            tooltip: me.refreshText,
            overflowText: me.refreshText,
            iconCls: Ext.baseCSSPrefix + 'tbar-loading',
            disabled: me.store.isLoading(),
            handler: me.doRefresh,
            scope: me
        }, '-', {
            itemId: 'first',
            tooltip: me.firstText,
            overflowText: me.firstText,
            iconCls: Ext.baseCSSPrefix + 'tbar-page-first',
            disabled: true,
            handler: me.moveFirst,
            padding: '4 0',
            // width: 16,
            scope: me
        }, {
            itemId: 'prev',
            tooltip: me.prevText,
            overflowText: me.prevText,
            iconCls: Ext.baseCSSPrefix + 'tbar-page-prev',
            disabled: true,
            handler: me.movePrevious,
            padding: '4 0',
            // width: 16,
            scope: me
        }, '-',
        me.beforePageText,
        {
            xtype: 'numberfield',
            readOnly: true,
            ui: 'gray',
            itemId: 'inputItem',
            name: 'inputItem',
            cls: Ext.baseCSSPrefix + 'tbar-page-number',
            allowDecimals: false,
            minValue: 1,
            hideTrigger: true,
            enableKeyEvents: true,
            keyNavEnabled: false,
            selectOnFocus: true,
            submitValue: false,
            // mark it as not a field so the form will not catch it when getting fields
            isFormField: false,
            width: me.inputItemWidth,
            margin: '-1 2 3 2',
            listeners: inputListeners
        }, {
            xtype: 'tbtext',
            itemId: 'afterTextItem',
            html: Ext.String.format(me.afterPageText, 1)
        }, '-', {
            itemId: 'next',
            tooltip: me.nextText,
            overflowText: me.nextText,
            iconCls: Ext.baseCSSPrefix + 'tbar-page-next',
            disabled: true,
            handler: me.moveNext,
            padding: '4 0',
            // width: 16,
            scope: me
        }, {
            itemId: 'last',
            tooltip: me.lastText,
            overflowText: me.lastText,
            iconCls: Ext.baseCSSPrefix + 'tbar-page-last',
            disabled: true,
            padding: '4 0',
            // width: 16,
            handler: me.moveLast,
            scope: me
        }];
    }
});

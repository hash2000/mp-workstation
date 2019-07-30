/**
Toolbar - с кнопкой "обновить" и количеством записей
*/
Ext.define('Ext.ux.toolbar.Refresher', {
    extend: 'Ext.toolbar.Paging',
    xtype: 'refreshertoolbar',

    displayMsg: 'Кол-во: {2}',

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
        }];
    }
});

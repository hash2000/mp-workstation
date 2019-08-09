Ext.define('SystemObjects.view.Viewport', {
    extend: 'Ext.container.Viewport',
    xtype: 'SystemObjectsViewport',
    
    layout: 'border',
    cls: 'unselectable borderview',

    requires: [
        'SystemCommon.panel.ObjectsTree',

        'SystemObjects.view.Model'
    ],

    viewModel: {
        type: 'SystemObjectsModel',
        name: 'SystemObjectsModel'
    },

    items: [{
        xtype: 'ObjectsTree',
        bind: {
            store: '{Objects}'
        },
        title: 'Объекты',
        region: 'center',
        rootVisible: true
    }]
});

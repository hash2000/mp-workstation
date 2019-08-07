Ext.define('SystemObjects.view.Viewport', {
    extend: 'Ext.container.Viewport',
    xtype: 'SystemObjectsViewport',
    
    layout: 'border',
    cls: 'unselectable borderview',

    requires: [
        'SystemObjects.view.Model'
    ],

    viewModel: {
        type: 'SystemObjectsModel',
        name: 'SystemObjectsModel'
    },

    items: [{
        xtype: 'panel',
        height: 300,
        region: 'north',
        expandable: true,
        split: true
    }, {
        xtype: 'panel',
        region: 'center',
    }]
});

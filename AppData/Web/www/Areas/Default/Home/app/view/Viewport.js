Ext.define('HomePage.view.Viewport', {
    extend: 'Ext.container.Viewport',
    xtype: 'HomePageViewport',
    
    layout: 'border',
    cls: 'unselectable borderview',

    viewModel: {
        type: 'HomePageModel',
        name: 'HomePageModel'
    },

    items: [{
        xtype: 'panel'
    }]
});

Ext.define('HomePage.view.Viewport', {
    extend: 'Ext.container.Viewport',
    xtype: 'HomePageViewport',
    
    layout: 'border',
    cls: 'unselectable borderview',

    requires: [
        'HomePage.view.Model'
    ],

    viewModel: {
        type: 'HomePageModel',
        name: 'HomePageModel'
    },

    items: [{
        xtype: 'panel',
        region: 'center',
        html: 'test',
        region: 'center',
    }]
});

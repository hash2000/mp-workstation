Ext.define('HomePage.view.Viewport', {
    extend: 'Ext.container.Viewport',
    xtype: 'HomePageViewport',
    
    contentItems: [{

        layout: 'border',

        viewModel: {
            type: 'HomePageModel',
            name: 'HomePageModel'
        },

        items: []
    }]
});

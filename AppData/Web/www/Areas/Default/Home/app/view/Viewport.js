Ext.define('HomePage.view.Viewport', {
    extend: 'Common.view.BorderViewport',
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

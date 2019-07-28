

Ext.application({
    name: 'HomePage',

    requires: [
       'HomePage.view.Viewport',

       'Ext.ux.TreePicker',
       'Common.proxy.DefaultRest',
       'Common.proxy.DefaultAjax'
    ],

    appFolder: '/Areas/Default/Home/app',
    autoCreateViewport: true
});
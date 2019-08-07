

Ext.application({
    name: 'SystemObjects',

    requires: [
       'SystemObjects.view.Viewport',

       'Ext.ux.TreePicker',
       'Common.proxy.DefaultRest',
       'Common.proxy.DefaultAjax'
    ],

    appFolder: '/Areas/System/Objects/app',
    autoCreateViewport: true
});
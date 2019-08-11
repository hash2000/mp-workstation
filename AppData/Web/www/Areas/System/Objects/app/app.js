

Ext.application({
    name: 'SystemObjects',

    requires: [
       'SystemObjects.view.Viewport',

       'Ext.ux.TreePicker',
       'Common.BaseControls',
       'Common.proxy.DefaultRest',
       'Common.proxy.DefaultAjax',
       'Common.controller.BaseController',
    ],

    appFolder: '/Areas/System/Objects/app',
    autoCreateViewport: true
});
/**
Хранилище по умолчанию
*/
Ext.define('Common.store.Default', {
    override: 'Ext.data.Store',
    alias: 'store.defaultstore',
    requires: ['Common.Popup'],

    constructor: function (config) {
        this.callParent(arguments);
        this.on('load', this.onLoad, this);
    },

    /**
    * При загрузке сторы
    */
    onLoad: function (el, records, successful, operation, eOpts) {

        //проверка версии
        if (operation._response && !Ext.isEmpty(operation._response.responseText) && operation._response.responseText.length !== 0) {

            var storeAssemblyVersion = Ext.decode(operation._response.responseText).assemblyVersion;
            //Common.Popup.red('', storeAssemblyVersion);

            if (!Ext.isEmpty(storeAssemblyVersion)) {
                var userInfoFields = Ext.query('.userinfo'),
                    userInfo = {};
                Ext.Array.each(userInfoFields, function (field) {
                    userInfo[field.name] = field.value;
                });
                //Common.Popup.red('', userInfo['AssemblyVersion']);

                if (userInfo['AssemblyVersion'] !== storeAssemblyVersion) {
                    Common.Popup.red('Внимание', 'Версия приложения устарела, требуется обновить страницу');
                }
            }
        }
    }
});

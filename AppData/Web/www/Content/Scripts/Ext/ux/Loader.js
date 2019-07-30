/**
Загрузчик, учитывающий виртуальный каталог на сервере
*/
Ext.define('Ext.ux.Loader', {
    override: 'Ext.Loader',

    /**
    @cfg {String}
    Имя виртуального каталога
    */
    virtualCatalog: '',

    getVirtualCatalog: function () {
        return this.virtualCatalog;
    },

    setVirtualCatalog: function (value) {
        this.virtualCatalog = value;
    },

    overrides: {
        /**
        Установить путь для загрузки класса, учитывая виртуальный каталог
        */
        setPath: function (ns, path) {
            path = this.buildUrl(path);
            return this._originalSetPath.apply(this, [ns, path]);
        },

        /**
        Получить путь для загрузки класса, учитывая виртуальный каталог
        */
        getPath: function (className) {
            var path = this._originalGetPath.call(this, className);
            return this.buildUrl(path);
        }
    },

    /**
    Добавить виртуальный каталог к URL (с проверкой)
    */
    buildUrl: function (path) {
        return path.indexOf(this.virtualCatalog) == 0 ? path :
            this.virtualCatalog + path;
    }
}, function () {
    // Заменить метод setPath
    Ext.Loader._originalSetPath = Ext.Loader.setPath;
    Ext.Loader.setPath = Ext.Loader.overrides.setPath;

    // Заменить метод getPath
    Ext.Loader._originalGetPath = Ext.Loader.getPath;
    Ext.Loader.getPath = Ext.Loader.overrides.getPath;

});

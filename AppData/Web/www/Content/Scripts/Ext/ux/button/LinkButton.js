/**
Кнопка-ссылка
*/
Ext.define('Ext.ux.button.LinkButton', {
    extend: 'Ext.button.Button',
    xtype: 'linkbutton',

    constructor: function (config) {
        config = config || {};
        config.ui = 'btn-default';
        //config.ui = 'link';
        this.callParent(arguments);
    },

    onClick: function (e) {
        // Учитываем щелчок только по тексту 
        // (сама невизуальная часть кнопки может быть больше)
        if (e.target.children.length === 0) {
            this.callParent(arguments);
        }
    }
});


/*
* Пример
* 
* xtype: 'linkbuttonhref',
* bind: {
*   text: '{item.FilePath}',
*   href: '{item.FilePath}'
* }
* 
*/

/**
Кнопка-гиперссылка
*/
Ext.define('Ext.ux.button.LinkButtonHref', {
    extend: 'Ext.button.Button',
    xtype: 'linkbuttonhref',

    constructor: function (config) {
        config = config || {};
        config.ui = 'btn-default';
        //config.ui = 'link';
        this.callParent(arguments);
    },

    onClick: function (e) {
        // Учитываем щелчок только по тексту 
        // (сама невизуальная часть кнопки может быть больше)
        if (e.target.children.length === 0) {
            this.callParent(arguments);

            window.open(this.getHref());
        }
    },

    config: {
        href: undefined
    },

    publishes: {
        href: 1 //true
    },

    userCls: 'ux-action-button'
});

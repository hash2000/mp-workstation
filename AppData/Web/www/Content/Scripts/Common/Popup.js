/**
Всплывающее окно
*/
Ext.define('Common.Popup', {
    singleton: true,

    /**
    @private
    */
    createBox: function (c, t, s) {
        return '<div class="' + c + '"><h3>' + t + '</h3><p>' + s + '</p></div>';
    },

    /**
    @private
    */
    message: function (c, title, format, id) {
        if (!this.msgCt) {
            this.msgCt = Ext.DomHelper.insertFirst(document.body, { id: 'msg-div' }, true);
        }
        var s = Ext.String.format.apply(String, Array.prototype.slice.call(arguments, 2));
        var m = Ext.DomHelper.append(this.msgCt, this.createBox(c, title, s), true);
        m.setOpacity(0);
        m.animate({
            opacity: 1,
            callback: function () {
                setTimeout(function () {
                    m.fadeOut({ remove: true });
                }, 3000);
            }
        });
    },

    /**
    Отобразить "красное" сообщение
    @param {String} title Заголовок сообщения
    @param {String} format Текст сообщения
    @param {String} params Аргументы форматирования текста сообщения
    */
    red: function (title, format) {
        var args = Array.prototype.concat.apply(['red'], arguments);
        this.message.apply(this, args)
    },

    /**
    Отобразить "зелёное" сообщение
    @param {String} title Заголовок сообщения
    @param {String} format Текст сообщения
    @param {String} params Аргументы форматирования текста сообщения
    */
    green: function (title, format) {
        var args = Array.prototype.concat.apply(['green'], arguments);
        this.message.apply(this, args)
    },

    /**
    Отобразить "голубое" сообщение
    @param {String} title Заголовок сообщения
    @param {String} format Текст сообщения
    @param {String} params Аргументы форматирования текста сообщения
    */
    blue: function (title, format) {
        var args = Array.prototype.concat.apply(['blue'], arguments);
        this.message.apply(this, args);
    }
});

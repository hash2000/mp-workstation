Ext.define('Ext.ux.ErrorsHandlers', {
    extend: 'Ext.Class',

    statics: {
        parseAndShowError: function (response) {

            //Заголовок окна
            var title = 'Ошибка при выполнении запроса';
            //Заголовок сообщения
            var header = '';
            //Тело сообщения
            var message = '';
            //Сообщение с ошибкой прилетевшее с сервера
            var responseMessage = Ext.decode(response.responseText, true);

            //Если есть сообщение с сервера
            if (responseMessage !== null && typeof responseMessage !== 'undefined') {

                //Заголовок сообщения
                if (typeof responseMessage.message !== 'undefined') {
                    header = responseMessage.message;
                }

                if (typeof responseMessage.messageText !== 'undefined') {
                    message = responseMessage.messageText;
                }
            }

            //HTTP 403 - нет прав на выполнение действия 
            if (response.status === 403) {
                if (header === '') {
                    header = 'Отсутствуют разрешения на выполняемое действие';
                }
            }
            else if (response.status === 401) {
                //Пользователь не авторизован - переправим на страницу авторизации
                //или сделаем редирект на главную страницу портала
                Ext.Msg.show({
                    title: 'Авторизация',
                    message: 'Вы не авторизованы для просмотра страницы, пожалуйста, авторизуйтесь!',
                    icon: Ext.Msg.ERROR,
                    buttons: Ext.Msg.OKCANCEL,
                    scope: this,
                    fn: function (btn) {
                        if (btn === 'ok') {
                            this.showLoginWindow();
                        } else if (btn === 'cancel') {
                            window.location.replace(Ext.Loader.buildUrl(''));
                        }
                    }
                });
                return;
            }

            //Если не смогли десериализовть ответ, 
            //покажем то, что прилетело с сервера
            if (responseMessage === null) {
                message = response.responseText;
            }

            if (response.message !== null || typeof response.message !== 'undefined') {
                message += '\n' + response.message;
            }

            //Ext.Msg.show({
            //    title: title,
            //    message: '<h3>' + header + '</h3>' + message,
            //    icon: Ext.Msg.ERROR,
            //    buttons: Ext.Msg.OK
            //});

            var window = Ext.create('Ext.window.Window', {
                title: title,
                width: 600,
                modal: true,
                items: [{
                    xtype: 'displayfield',
                    value: '<h3>' + header + '</h3>',
                    labelCls: 'x-message-box-error',
                    labelWidth: 50,
                    margin: '10 0 0 20'
                }, {
                    xtype: 'fieldset',
                    title: 'Детали',
                    collapsible: true,
                    collapsed: true,
                    items: [{
                        xtype: 'displayfield',
                        value: message
                    }]
                }],
                buttons: [{
                    text: 'Закрыть',
                    handler: function (btn) {
                        btn.up('window').close();
                    },
                    scale: 'medium'
                }]
            });
            window.show();
        },

        /**
         * Открыть окно аутентификации
         */
        showLoginWindow: function () {
            var win = Ext.widget({
                xtype: 'window',
                title: 'Вход',
                modal: true,
                layout: 'fit',
                width: 400,
                items: [{
                    xtype: 'loginpanel'
                }]
            });
            win.down('loginpanel').on('cancel', win.close, win);
            win.show();
        }
    }
});

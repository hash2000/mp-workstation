Ext.define('Ext.ux.field.Field', {
    override: 'Ext.form.field.Text',

    enableKeyEvents: true,

    config: {
        isDispatcherField: false,
        isCTRLPressed: false,
        //isSHIFTPressed: false,
        dispatcherTable: null,
        dispatcherField: null,
        qtip: null
    },

    //beforeRender: function () {
    //    var me = this,
    //        isDispatcherField = me.getIsDispatcherField(),
    //        bind = me.config.bind || me.config.name;

    //    if (isDispatcherField) {
    //        if (~bind.indexOf("_fire}")) {
    //            me.fieldCls = 'ownNeedsField-fire'; //перекрасить сжигание
    //        }
    //    }
    //},

    afterRender: function () {
        var me = this,
            isDispatcherField = me.getIsDispatcherField(),
            dispatcherTable = me.getDispatcherTable(),
            dispatcherField = me.getDispatcherField(),
            qtip = me.config.bind || me.config.name;

        me.callParent();

        if (isDispatcherField) {
            if ((dispatcherTable !== null) && (dispatcherField !== null)) {
                qtip = '{' + dispatcherTable + '.' + dispatcherField + '}';
            } else {
                qtip = me.parseBind(qtip);
            }

            if (qtip) {
                //Добавим tooltip
                Ext.create('Ext.tip.ToolTip', {
                    target: me.el,
                    //trackMouse: true,
                    html: qtip
                });
            }

            me.mon(me, 'keydown', 'onKeyDown', me);
            me.mon(me, 'keyup', 'onKeyUp', me);
            me.mon(me.el, 'click', 'onClick', me);
        }
    },

    onKeyDown: function (event) {
        var isDispatcherField = this.getIsDispatcherField();

        if (isDispatcherField) {
            if (event.getKey() === event.CTRL) {
                this.setIsCTRLPressed(true);
            }
            //if (event.getKey() === event.SHIFT) {
            //    this.setIsSHIFTPressed(true);
            //}
        }
    },

    onKeyUp: function (event) {
        var isDispatcherField = this.getIsDispatcherField();

        if (isDispatcherField) {
            if (event.getKey() === event.CTRL) {
                this.setIsCTRLPressed(false);
            }
            //if (event.getKey() === event.SHIFT) {
            //    this.setIsSHIFTPressed(false);
            //}
        }
    },

    onClick: function (event, field) {
        var textArea = document.createElement("textarea"),
            isDispatcherField = this.getIsDispatcherField(),
            dispatcherTable = this.getDispatcherTable(),
            dispatcherField = this.getDispatcherField(),
            isCTRLPressed = this.getIsCTRLPressed(),
            //isSHIFTPressed = this.getIsSHIFTPressed(),
            qtip = this.getQtip();

        if (isDispatcherField) {
            if (isCTRLPressed) {

                textArea.style.position = 'fixed';
                textArea.style.top = 0;
                textArea.style.left = 0;
                textArea.style.width = '2em';
                textArea.style.height = '2em';
                textArea.style.padding = 0;
                textArea.style.border = 'none';
                textArea.style.outline = 'none';
                textArea.style.boxShadow = 'none';
                textArea.style.background = 'transparent';
                textArea.value = dispatcherField;
                textArea.id = 'ta';

                document.body.appendChild(textArea);

                var range = document.createRange();
                range.selectNode(textArea);
                textArea.select();

                var sel = window.getSelection();
                sel.removeAllRanges();
                sel.addRange(range);

                try {
                    var successful = document.execCommand('copy');
                    if (successful) {
                        Common.Popup.blue('Информация', 'Скопировано:<br/>' + dispatcherField);
                    }
                } catch (err) {
                    alert('Ошибка при копировании');
                }
                document.body.removeChild(textArea);
                this.setIsCTRLPressed(false);
            }
        }

        //if (isSHIFTPressed) {
        //    var win = Ext.widget({
        //        xtype: 'dispatchertablefieldinfowindow',
        //        dispatcherTable: dispatcherTable,
        //        dispatcherField: dispatcherField
        //    });
        //    win.show();
        //}
    },

    /**
    * @private
    * Разбить строку на имя таблицы и имя поля
    */
    parseBind: function (qtip) {
        if (!Ext.isEmpty(qtip) && !Ext.isEmpty(qtip.value)) {
            qtip = qtip.value;
        }
        if (qtip && qtip !== null) {
            var dict = qtip.replace("{", "").replace("}", "").split(".");
            if (dict.length === 2) { //если field
                this.setDispatcherTable(dict[0]);
                this.setDispatcherField(dict[1]);
            }
            else if (dict.length === 1) {//если column
                this.setDispatcherField(dict[0]);
            }
        }
        return qtip;
    }
});

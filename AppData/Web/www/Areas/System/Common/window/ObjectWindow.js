
Ext.define('SystemCommon.window.ObjectWindow', {
    extend: 'Ext.window.Window',
    xtype: 'ObjectWindow',
    modal: true,
    bodyPadding: 10,
    width: 800,
    layout: 'fit',
    defaultListenerScope: true,

    requires: [
        'SystemCommon.model.ObjectType'
    ],

    config: {
        item: null,
        itemIsReadOnly: false
    },

    publishes: [
        'item',
        'itemIsReadOnly'
    ],

    viewModel: {
        stores: {
            ObjectTypes: {
                model: 'SystemCommon.model.ObjectType',
                autoLoad: true,
                autoSync: false,
                remoteFilter: false,
                sorters: [{
                    property: 'Name',
                    direction: 'ASC'
                }]
            }
        }
    },

    items: [{
        xtype: 'form',
        modelValidation: true,

        items: [{
            xtype: 'container',
            layout: {
                type: 'vbox',
                align: 'stretch'
            },
            defaults: {
                labelWidth: 130,
                margin: '0 0 10',
                width: '90%',
                xtype: 'textfield'
            },

            items: [{
                xtype: 'textfield',
                fieldLabel: 'Id',
                bind: '{item.id}',
                readOnly: true,
                ui: 'gray'
            }, {
                fieldLabel: 'Наименование',
                bind: {
                    value: '{item.Name}',
                    readOnly: '{itemIsReadOnly}'
                },
                allowBlank: false
            }, {
                xtype: 'textarea',
                fieldLabel: 'Описание',
                bind: {
                    value: '{item.Description}',
                    readOnly: '{itemIsReadOnly}'
                }
            }, {
                xtype: 'combobox',
                fieldLabel: 'Тип',
                displayField: 'Name',
                valueField: 'Id',
                editable: false,
                allowBlank: false,
                bind: {
                    value: '{item.TypeId}',
                    store: '{ObjectTypes}',
                    readOnly: '{itemIsReadOnly}'
                }
            }, {
                xtype: 'numberfield',
                fieldLabel: 'Сортировка',
                bind: {
                    value: '{item.ViewOrder}',
                    readOnly: '{itemIsReadOnly}'
                },
                minValue: 0,
                maxValue: 2147483647,
                allowBlank: false
            }, {
                xtype: 'datefield',
                fieldLabel: 'Дата последнего изменения',
                bind: '{item.ModifiedDate}',
                format: 'd.m.Y H:i:s',
                readOnly: true,
                ui: 'gray'
            }]
        }]

    }]
});
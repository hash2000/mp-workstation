/**
Пользовательские контролы
*/
Ext.define('Common.BaseControls', {
    extend: 'Ext.Class',
    requires: [
        'Common.button.ButtonAdd',
        'Common.button.ButtonCancel',
        'Common.button.ButtonRemove',
        'Common.button.ButtonSave',
        'Common.button.ButtonPrint',
        'Common.button.ButtonView',
        'Common.field.SearchTextAreaField',
    ]
});

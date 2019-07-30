Ext.define('Common.writer.Default', {
    extend: 'Ext.data.writer.Json',
    alias: 'writer.defaultwriter',
    type: 'json',
    rootProperty: 'item',
    allowSingle: true,
    writeAllFields: true,
    encode: false
});

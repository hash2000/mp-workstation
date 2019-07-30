Ext.define('Common.reader.Default', {
    extend: 'Ext.data.reader.Json',
    alias: 'reader.defaultreader',
    rootProperty: 'items',
    messageProperty: 'message'
});
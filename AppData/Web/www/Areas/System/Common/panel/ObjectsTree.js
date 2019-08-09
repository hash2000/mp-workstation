Ext.define('SystemCommon.panel.ObjectsTree', {
    extend: 'Ext.tree.Panel',
    xtype: 'ObjectsTree',

    columns: [{
        text: 'id',
        dataIndex: 'id',
        hidden: true
    }, {
        text: 'parentId',
        dataIndex: 'parentId',
        hidden: true
    }, {
        xtype: 'treecolumn',
        text: 'Наименование',
        dataIndex: 'Name',
        flex: 1
    }, {
        text: 'TypeId',
        dataIndex: 'TypeId',
        hidden: true
    }, {
        text: 'TypeName',
        dataIndex: 'TypeName'
    }]
});
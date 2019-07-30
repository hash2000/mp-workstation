/**
 * Конфигурация панели дерева по умолчанию
 */
Ext.define('Ext.ux.panel.TreePanel', {
    override: 'Ext.tree.Panel',
    split: true,
    useArrows: true,
    rootVisible: false,
    dockedItems: [{
        xtype: 'refreshertoolbar',
        displayInfo: false
    }]
});
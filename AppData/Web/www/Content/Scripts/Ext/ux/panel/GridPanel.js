/**
 * Конфигурация панели с таблицей по умолчанию
 */
Ext.define('Ext.ux.panel.GridPanel', {
	override: 'Ext.grid.Panel',
	split: true,
	columnLines: true,
	dockedItems: [{
		xtype: 'pagingtoolbar'
	}]
});

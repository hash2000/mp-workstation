/* global Ext */

/**
 * начиная с версии 6.2 из bind убрали обработку "!"
 */
Ext.define('Ext.vmx.app.bind.Binding', {
    override: 'Ext.app.bind.Binding',

    getValue: function () {
        var me = this,
            stub = me.stub,
            ret = stub && stub.getValue();
        if (me.not) {
            ret = !ret;
        }
        return ret;
    },

    privates: {
        getRawValue: function () {
            var me = this,
                stub = me.stub,
                ret = stub && stub.getRawValue();
            if (me.not) {
                ret = !ret;
            }
            return ret;
        }
    }
});
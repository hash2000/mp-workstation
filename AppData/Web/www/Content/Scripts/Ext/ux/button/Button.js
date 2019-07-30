Ext.define('Ext.ux.button.Button', {
    override: 'Ext.button.Button',

    config: {
        /**
        @cfg {Boolean}
        Режим "загрузка"
        */
        loading: undefined,

        /**
        @cfg
        Иконка в режиме "загрузки"
        */
        loadingIconCls: 'x-fa fa-spinner fa-pulse',
    },

    /**
     * При изменении режима "загрузка"
     */
    updateLoading: function (loading) {
        if (loading) {
            if (!this.originalIconCls) {
                this.originalIconCls = this.iconCls || '';
            }
            this.setIconCls(this.getLoadingIconCls());
        }
        else {
            if (this.originalIconCls !== undefined) {
                this.setIconCls(this.originalIconCls);
                delete this.originalIconCls;
            }
        }

        this.setDisabled(loading);
    },

    /**
     * Переопределение метода от Ext.Component
     */
    setLoading: function (loading) {
        if (loading != this.getLoading()) {
            this.updateLoading(loading);
        }
    }
});
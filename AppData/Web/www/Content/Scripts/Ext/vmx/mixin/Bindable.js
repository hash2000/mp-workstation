﻿/* global Ext */

/**
 * This override allows binding to the component's own properties. 
 * These properties should be declared in the 'publishes' config.
 */
Ext.define('Ext.vmx.mixin.Bindable', {
    initBindable: function () {
        var me = this;
        Ext.mixin.Bindable.prototype.initBindable.apply(me, arguments);
        me.applyInitialPublishedState();
    },

    /**
    Notifying parent ViewModel about state changes
    */
    publishState: function (property, value) {
        var me = this,
            vm = me.lookupViewModel(),
            parentVm = me.lookupViewModel(true),
            path = me.viewModelKey,
            state;

        if (path && property && parentVm) {
            path += '.' + property;
            parentVm.set(path, value);
        }

        Ext.mixin.Bindable.prototype.publishState.apply(me, arguments);

        if (property && vm && vm.getView() == me) {
            vm.set(property, value);
        }
    },

    /**
    Getting published state
    */
    getInitialPublishedState: function () {
        var me = this,
            state = me.publishedState || (me.publishedState = {}),
            publishes = me.getPublishes();

        for (name in publishes) {
            if (state[name] === undefined) {
                state[name] = me[name];
            }
        }

        return state;
    },

    /**
    Applying published state to own ViewModel
    */
    applyInitialPublishedState: function () {
        var me = this,
            vm = me.lookupViewModel(),
            state;

        if (vm && vm.getView() == me) {
            state = me.getInitialPublishedState();
            vm.set(state);
        }
    }
}, function () {
    Ext.Array.each([Ext.Component, Ext.Widget], function (Class) {
        Class.prototype.initBindable = Ext.vmx.mixin.Bindable.prototype.initBindable;
        Class.prototype.publishState = Ext.vmx.mixin.Bindable.prototype.publishState;
        Class.mixin([Ext.vmx.mixin.Bindable]);
    });
});
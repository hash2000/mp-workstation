/*
    хранилище данных, которое генерирует набор значений:
        от valueFrom, до valueTo, с шагом valueStep
        
    this.down('#SummaryHours').bindStore(Ext.create('Common.store.FlatStore', {
        valueFrom: 0,
        valueTo: 24,
        valueStep: 2
    }));

    если указать параметр names(Object),
        то будет сгенерирован список с указанными именами и индексами,
        
    names: {
        1: 'Январь',
        2: 'Февраль',
        3: 'Март',
        ...
    }

*/


Ext.define('Common.store.FlatStore', {
    extend:'Ext.data.Store',
    fields: ['Value', 'Name'],
    valueFrom: 0,
    valueTo: undefined,
    valueStep: 1,
    autoLoad: false,
    names: undefined,
    listeners: {
        load: {
            fn: function () {
                if (!Ext.isEmpty(this.names)) {
                    // если указан набор 
                    var keys = Object.keys(this.names);
                    var i, len;
                    for (i = 0, len = keys.length; i < len; i++) {
                        var key = keys[i];
                        var member = this.names[key];
                        var obj = {
                            Value: key,
                            Name: member
                        };
                        this.add(obj);
                    }
                } else {
                    // если указан диапазон 
                    for (var i = this.valueFrom ; i < this.valueTo ; i += this.valueStep) {
                        this.add({
                            Value: i
                        });
                    }
                }
            }
        }
    }
});
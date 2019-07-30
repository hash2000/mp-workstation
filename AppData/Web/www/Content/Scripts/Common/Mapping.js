/**
"Получатель" значения у объекта.

Использование:
<pre><code>
var obj = { 
    SomeValue: 'abc', 
    InnerObject: { 
        InnerValue: 'Hello, world!'
    } 
};

App.Mapping.map('InnerObject.InnerValue')(obj); 
// 'Hello, world!'

App.Mapping.map('InnerObject.InnerValue', 2)('foo', 'bar', obj); 
// 'Hello, world!'

App.Mapping.map('InnerObject.NoValue', null, 'Default')(obj); 
// 'Default'
</code></pre>

Может использоваться для параметра 'mapping' у Ext.data.Model. Например:
<pre><code>
fields: ['Id', 'Name', {
    name: 'InnerName',
    mapping: App.Mapping.map('InnerObject.InnerValue')
}]
</code></pre>

Тажке может использоваться для параметра 'renderer' у Ext.data.Column. 
Если объект имеет следующий формат: 
<pre><code>
{
    Name: 'John Smith',
    City: {
        Name: 'New York'
    }
}
</code></pre>

<pre><code>
columns: [{
    header: 'City name',
    
    // здесь argIndex = 2, т.к. в нем передается экземпляр Ext.data.Record.
    renderer: App.Mapping.map('data.City.Name', 2)    
}]
</code></pre>

*/
Ext.define('Common.Mapping', {
    singleton: true,

    /**
    Создать "получатель" значения объекта.
    @param {String} expression Выражение для получения
    @param {Int} [argIndex] Индекс аргумента, в который будет передан объект
    @param [defaultValue] Значение по умолчанию
    */
    map: function (expression, argIndex, defaultValue) {
        var expr = expression;
        var index = argIndex || 0;
        var def = defaultValue;

        return function () {
            var obj = arguments[index];
            var props = expr.split('.');
            var i, count = props.length;

            for (i = 0; i < count; i++) {
                var prop = props[i];
                if (obj != undefined)
                    obj = obj[prop];
                else
                    break;
            }

            return (i == count) && (obj != undefined) ? obj : def;
        }
    }
});

Person = {}

function Person.init(name, age)
    object = {}
    object.name = name
    object.age = age

    -- show profile
    function object.show(self)
        print(string.format("name = %s, age = %d",self.name , self.age))
    end

    -- incriment of age
    function object.inc(self, num_inc)
        if(num_inc == nil) then
            self.age = self.age + 1
        else
            self.age = self.age + num_inc
        end
    end

    return object
end

return Person;

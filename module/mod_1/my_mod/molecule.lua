Mol = {
}

function Mol.init(num_atom, max_iter)
    object = {}
    object.num_atom = num_atom
    object.max_iter = max_iter

    -- show profile
    function object.show(self)
        print(string.format("num_atom = %d , max_iter  : %d "
        , self.num_atom, self.max_iter))
    end

    -- change member 
    function object.ch_member(self,num_atom, max_iter)
        self.num_atom = num_atom
        self.max_iter = max_iter
     end 

    return object
end



return Mol


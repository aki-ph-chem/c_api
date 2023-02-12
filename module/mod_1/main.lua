p_1 = require("my_mod/person").init("foo",111)
m_1 = require("my_mod/molecule").init(26,1000)

function main()
    p_1:show()

    p_1:inc(10)
    p_1:show()

    p_1:inc()
    p_1:show()

    m_1:show()
    m_1:ch_member(10,100)
    m_1:show()
end

main()

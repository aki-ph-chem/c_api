-- 試しにパッケージを作ってみる

package = "my_tool"

version = "beta-1"

source = {
    url = "..."
}

description = {
    summary = "Tools for array manipulation.",

    detailed = [[
    This is an example for the LuaRocks tutorial.
    ]],

    homepage = "https://____",

    license = "MIT"
}

dependencies = {
    "lua >= 5.4"
}

build = {
   type = "builtin",

   modules = {
       my_tool = "my_tool.lua",
       sum = "sum.lua",
       prod = "prod.lua",
   }
}

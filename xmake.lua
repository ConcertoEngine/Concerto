add_rules("mode.debug", "mode.release")
add_rules("plugin.vsxmake.autoupdate")

add_repositories("Concerto-xrepo https://github.com/ConcertoEngine/xmake-repo.git main")

add_requires("gtest")
add_requires("ConcertoCore", {configs = { debug = is_mode("debug"), with_symbols = true}})

if is_plat("windows") then
    set_runtimes(is_mode("debug") and "MDd" or "MD")
end

local modules = {
    Ecs = {
        Option = "ecs",
        Dependencies = {},
        Packages = {
            "ConcertoCore"
        },
    },
    Graphics = {
        Option = "graphics",
        Dependencies = { "ConcertoEngineEcs" },
        Packages = {
            "ConcertoCore",
            "nazaraengine"
        },
    }
}

option("examples", { description = "Enable examples", default = false })
option("unit-test", { description = "Enable unit tests", default = false })

for name, module in table.orderpairs(modules) do
    if module.Option then
        option(module.Option, { description = "Enable " .. name .. " module", default = true })
    end
end

if has_config("graphics") then
    add_repositories("nazara-repo https://github.com/NazaraEngine/xmake-repo.git")
    add_requires("nazaraengine", {configs = { debug = is_mode("debug"), with_symbols = true, audio = false, bulletphysics = false, chipmunkphysics = false, graphics = true, joltphysics = false, platform = true, renderer = true, utility = true, widgets = false, plugin_assimp = false, network = false }})
end

for name, module in pairs(modules) do
    if has_config(module.Option) then
        target("ConcertoEngine" .. name, function()
            for _, dependency in pairs(module.Dependencies) do
                add_deps(dependency)
            end
            for _, package in pairs(module.Packages) do
                add_packages(package, {public = true})
            end
            for _, ext in ipairs({".h", ".hpp", ".inl"}) do
                add_headerfiles("Include/(Concerto/Engine/" .. name .. "/**" .. ext .. ")")
            end
            add_files("Src/" .. name .. "/*.cpp")
            if is_mode("debug") then
                set_symbols("debug")
            end
            set_warnings("allextra")
            set_kind("shared")
            set_languages("cxx20")
            add_includedirs("Include", {public = true})
            add_defines("CONCERTO_ENGINE_" .. name:upper() .. "_BUILD")
        end)
    end
end

if has_config("unit-test") then
    target("ConcertoEngineUnitTests")
        set_kind("binary")
        if is_mode("debug") then
            set_symbols("debug")
        end
        set_warnings("allextra")
        set_languages("cxx20")
        add_files("Tests/*.cpp")
        add_packages("gtest")
        add_deps("ConcertoEngineEcs")
end

includes("Xmake/Rules/*.lua")

if has_config("examples") then
    includes("Examples/xmake.lua")
end
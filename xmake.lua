add_rules("mode.debug", "mode.release")
add_rules("plugin.vsxmake.autoupdate")

add_repositories('Concerto-xrepo https://github.com/ConcertoEngine/xmake-repo.git main')
add_repositories("nazara-repo https://github.com/NazaraEngine/xmake-repo.git")

add_requires('gtest')
add_requires("nazaraengine", {configs = { debug = is_mode("debug"), with_symbols = true, audio = false, bulletphysics3d = false, chipmunkphysics2d = false, graphics = true, joltphysics3d = false, platform = true, renderer = true, utility = true, widgets = false, plugin_assimp = false, network = false }})
add_requires('ConcertoCore', {configs = { debug = is_mode("debug"), with_symbols = true}})

if is_plat("windows") then
    set_runtimes(is_mode("debug") and "MDd" or "MD")
end

target('ConcertoEngine')
    set_kind('shared')
    if is_mode('debug') then
        set_symbols('debug')
    end
    set_warnings('allextra')
    set_languages('cxx20')

    add_includedirs('Include', 'Include/Concerto/Engine', 'Include/Concerto', 'Include/Concerto/Engine/Ecs', 'Include/Concerto/Engine/Ecs/Components', 'Include/Concerto/Engine/Ecs/Systems', { public = true })

    add_headerfiles('Include/(Concerto/Engine/*.hpp)', 'Include/(Concerto/Engine/Ecs/*.hpp)', 'Include/(Concerto/Engine/Ecs/Components/*.hpp)', 'Include/(Concerto/Engine/Ecs/Systems/*.hpp)')
    add_headerfiles('Include/(Concerto/Engine/*.inl)', 'Include/(Concerto/Engine/Ecs/*.inl)', 'Include/(Concerto/Engine/Ecs/Components/*.inl)', 'Include/(Concerto/Engine/Ecs/Systems/*.inl)')

    add_files('Src/**.cpp')
    add_defines("CONCERTO_ENGINE_BUILD")
    add_packages('ConcertoCore', {public = true})
    add_packages('nazaraengine', {public = true})

target('ConcertoEngineUnitTests')
    set_kind('binary')
    set_symbols('debug')
    set_warnings('allextra')
    set_languages('cxx20')
    add_files('Tests/*.cpp')
    add_packages('gtest')
    add_deps('ConcertoEngine')

includes('Xmake/Rules/*.lua')
includes('Examples/xmake.lua')
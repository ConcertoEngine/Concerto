add_rules('mode.debug')
add_rules("plugin.vsxmake.autoupdate")

add_repositories('Concerto-xrepo https://github.com/ConcertoEngine/xmake-repo.git main')
add_repositories("nazara-repo https://github.com/NazaraEngine/xmake-repo.git")

add_requires('gtest', 'ConcertoCore')
add_requires("nazaraengine", { debug = is_mode("debug"), configs = { audio = false, bulletphysics3d = false, chipmunkphysics2d = false, graphics = true, joltphysics3d = false, platform = true, renderer = true, utility = true, widgets = false, plugin_assimp = false, network = false }})


if is_plat("windows") then
    set_runtimes(is_mode("debug") and "MDd" or "MD")
end

target('Concerto')
    set_kind('static')
    if is_mode('debug') then
        set_symbols('debug')
    end
    set_warnings('allextra')
    set_languages('cxx20')

    add_includedirs('Include', 'Include/Concerto', 'Include/Concerto/Ecs', 'Include/Concerto/Ecs/Components', 'Include/Concerto/Ecs/Systems', { public = true })

    add_headerfiles('Include/(Concerto/*.hpp)', 'Include/(Concerto/Ecs/*.hpp)', 'Include/(Concerto/Ecs/Components/*.hpp)', 'Include/(Concerto/Ecs/Systems/*.hpp)')
    add_headerfiles('Include/(Concerto/*.inl)', 'Include/(Concerto/Ecs/*.inl)', 'Include/(Concerto/Ecs/Components/*.inl)', 'Include/(Concerto/Ecs/Systems/*.inl)')

    add_files('Src/**.cpp')

    add_packages('ConcertoCore', {public = true})
    add_packages('nazaraengine', {public = true})

target('ConcertoUnitTests')
    set_kind('binary')
    set_symbols('debug')
    set_warnings('allextra')
    set_languages('cxx20')
    add_files('Tests/*.cpp')
    add_packages('gtest')
    add_deps('Concerto')

includes('Xmake/Rules/*.lua')
includes('Examples/xmake.lua')
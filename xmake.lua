add_rules('mode.debug')
add_repositories('Concerto-xrepo https://github.com/ConcertoEngine/xmake-repo.git main')

add_requires('gtest', 'ConcertoCore', 'ConcertoGraphics')
add_requireconfs("**.vulkan-headers", {override = true, version = "1.3.246"})


local function AddIncludesToTarget(includes)
    for _, include in ipairs(includes) do
        add_includedirs(include, { public = true })
    end
end

target('Concerto')
    set_kind('static')
    set_symbols('debug')
    set_warnings('allextra')
    set_languages('cxx20')
    
    AddIncludesToTarget({'Include/(Concerto/*.hpp)','Include/(Concerto/Ecs/*.hpp)', 'Include/(Concerto/Ecs/Components/*.hpp)', 'Include/(Concerto/Ecs/Systems/*.hpp)'})
    AddIncludesToTarget({'Include/(Concerto/*.inl)','Include/(Concerto/Ecs/*.inl)', 'Include/(Concerto/Ecs/Components/*.inl)', 'Include/(Concerto/Ecs/Systems/*.inl)'})

    add_headerfiles('Include/(Concerto/*.hpp)','Include/(Concerto/Ecs/*.hpp)', 'Include/(Concerto/Ecs/Components/*.hpp)', 'Include/(Concerto/Ecs/Systems/*.hpp)')
    add_headerfiles('Include/(Concerto/*.inl)','Include/(Concerto/Ecs/*.inl)', 'Include/(Concerto/Ecs/Components/*.inl)', 'Include/(Concerto/Ecs/Systems/*.inl)')
    
    add_files('Src/**.cpp')
    
    add_packages('ConcertoCore', {public = true})
    add_packages('ConcertoGraphics', {public = true})

target('ConcertoUnitTests')
    set_kind('binary')
    set_symbols('debug')
    set_warnings('everything')
    set_languages('cxx20')
    set_optimize('none')
    add_includedirs('Include', 'Include/Ecs', 'Include/Ecs/Systems')
    add_files('tests/*.cpp')
    add_packages('gtest', 'ConcertoCore')
    add_deps('Concerto')

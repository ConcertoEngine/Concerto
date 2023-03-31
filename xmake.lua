add_rules('mode.debug')
add_repositories('Concerto-xrepo https://github.com/ConcertoEngine/xmake-repo.git main')
add_requires('gtest', 'ConcertoCore', 'ConcertoGraphics')

target('Concerto')
--     set_runtimes(is_mode('debug') and 'MDd' or 'MD')
    set_kind('binary')
    set_symbols('debug')
    set_warnings('everything')
    set_optimize('none')
    set_languages('cxx20')
    add_includedirs('Include', 'Include/Ecs', 'Include/Ecs/Systems', 'Include/Ecs/Systems/NazaraRenderer', 'Include/Ecs/Components')
    add_files('Src/**.cpp')
    add_packages('ConcertoCore', 'ConcertoGraphics')
    after_build(function(target)
        import('net.http')
        import('utils.archive')

        if (not os.exists('assets/sponza')) then
            print('Downloading assets...')
            http.download('https://casual-effects.com/g3d/data10/common/model/crytek_sponza/sponza.zip', 'assets/sponza.zip')
            print('Downloading assets... Done !')

            print('Extracting assets...')
                archive.extract('assets/sponza.zip', 'assets/sponza')
                os.rm('assets/sponza.zip')
            print('Extracting assets... Done !')
        else
            print('Assets already downloaded !')
        end

        print("Copying resources...")
        local binaryPath = "$(buildir)/$(plat)/$(arch)/$(mode)"
        os.mkdir(binaryPath .. "/assets")
        os.cp("./config.json", binaryPath .. "/config.json")
        os.cp("assets/**", binaryPath .. "/assets")
        print("Copying resources... Done !")
    end)

target('ConcertoUnitTests')
    set_kind('binary')
    set_symbols('debug')
    set_warnings('everything')
    set_languages('cxx20')
    set_optimize('none')
    add_includedirs('Include', 'Include/Ecs', 'Include/Ecs/Systems')
    add_files('Src/Ecs/*.cpp', 'tests/*.cpp')
    add_packages('gtest', 'ConcertoCore')

rule('copy_to_build_dir')
    after_build(function (target)
        print('Copying assets to build directory...')
        local binaryPath = "$(buildir)/$(plat)/$(arch)/$(mode)"
        os.cp("./config.json", binaryPath .. "/config.json")
        print('Copying assets to build directory... Done !')
    end)
add_rules('copy_to_build_dir')

target('Basic')
    set_kind('binary')
    set_symbols('debug')
    set_warnings('allextra')
    add_deps('ConcertoEngine')
    add_files('main.cpp')
    set_languages('cxx20')
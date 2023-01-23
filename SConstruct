core_env = Environment(CCFLAGS='-ggdb', CPPPATH=['.'], LIBS=[], LIBPATH=[])
core_env['CPPPATH'] +=['./external', '/usr/include/SDL2']
core_env['LIBS'] += ['SDL2']
core_env['LIBPATH'] += ['/usr/lib']

corefiles = ['inputs.cpp', 'memory.cpp', 'screen.cpp', 'external/s7.c', 'api.cpp', 'lispc.cpp']

core_env.Program('lispc', corefiles);

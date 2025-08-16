import os
from glob import glob


ON = '1'
OFF = '0'

# --- PROJECT SETTINGS ----------------------------------------------------------------------------
VERSION_MAJOR = 1
VERSION_MINOR = 0
VERSION_PATCH = 0

OUTPUT_NAME = 'tml'
CXX_STANDARD = 'c++17'

# --- OPTIONS -------------------------------------------------------------------------------------
debug = ARGUMENTS.get('debug', OFF) == ON
optimize = ARGUMENTS.get('debug', OFF) == ON  # only release


# --- CREATE ENVIRONMENT --------------------------------------------------------------------------
env = Environment(CPPPATH=["#include"], CPPDEFINES=['TML_DLL_EXPORT'])
if debug:
    env.Append(CXXFLAGS=['/Zi', '/Od', '/EHsc', f'/std:{CXX_STANDARD}'], LINKFLAGS=['/DEBUG'])
else:
    flags = ['/EHsc', f'/std:{CXX_STANDARD}']
    if optimize: flags.append('/O2')

    env.Append(CXXFLAGS=flags)
    

# --- SCAN SRC ------------------------------------------------------------------------------------
VariantDir('build/obj/tml', 'src', duplicate=0)
src = Glob('build/obj/tml/*.cpp')

# --- SCAN TESTS ----------------------------------------------------------------------------------
VariantDir('build/obj/tests', 'tests', duplicate=0)
tests_src = Glob('build/obj/tests/*.cpp')

# --- BUILD ---------------------------------------------------------------------------------------
if debug:
    # lib
    lib = env.StaticLibrary(target=f'build/bin/{OUTPUT_NAME}-debug', source=src)
    dll = env.SharedLibrary(target=f'build/bin/{OUTPUT_NAME}-debug', source=src)

    # test
    env.Program(target=f'build/bin/testrunner', source=tests_src, LIBS=[lib], LIBPATH=["#src"])
else:
    raise NotImplementedError()
    app = env.Program(target=f'build/bin/{OUTPUT_NAME}-{VERSION_MAJOR}.{VERSION_MINOR}', source=obj)

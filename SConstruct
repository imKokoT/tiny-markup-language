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
env = Environment(CPPPATH=["#include"])
if debug:
    env.Append(CXXFLAGS=['/Zi', '/Od', '/EHsc', f'/std:{CXX_STANDARD}'], LINKFLAGS=['/DEBUG'])
else:
    flags = ['/EHsc', f'/std:{CXX_STANDARD}']
    if optimize: flags.append('/O2')

    env.Append(CXXFLAGS=flags)
    

# --- BUILD LIB -----------------------------------------------------------------------------------
VariantDir('build/obj/tml/', 'src', duplicate=0)
src = [File(f) for f in glob('src/*.cpp')]
obj = ['build/obj/tml/' + os.path.basename(str(s)) for s in src]


# --- BUILD ---------------------------------------------------------------------------------------
if debug:
    env.Library(target=f'build/bin/{OUTPUT_NAME}-debug', source=obj)
    env.SharedLibrary(target=f'build/bin/{OUTPUT_NAME}-debug', source=obj)
else:
    raise NotImplementedError()
    app = env.Program(target=f'build/bin/{OUTPUT_NAME}-{VERSION_MAJOR}.{VERSION_MINOR}', source=obj)

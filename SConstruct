import os
from glob import glob


ON = '1'
OFF = '0'

# --- PROJECT SETTINGS ----------------------------------------------------------------------------
VERSION_MAJOR = 1
VERSION_MINOR = 0
VERSION_PATCH = 0

OUTPUT_NAME = 'tml'
CXX_STANDARD = 'c++20'

# --- OPTIONS -------------------------------------------------------------------------------------
debug = ARGUMENTS.get('debug', OFF) == ON
optimize = ARGUMENTS.get('debug', OFF) == ON  # only release


# --- CREATE ENVIRONMENT --------------------------------------------------------------------------
env = Environment()
if debug:
    env.Append(CXXFLAGS=['/Zi', '/Od', '/EHsc', f'/std:{CXX_STANDARD}'], LINKFLAGS=['/DEBUG'])
else:
    flags = ['/EHsc', f'/std:{CXX_STANDARD}']
    if optimize: flags.append('/O2')

    env.Append(CXXFLAGS=flags)
    

# --- SCAN SOURCES --------------------------------------------------------------------------------
VariantDir('build/obj', 'src', duplicate=0)
src = [File(f) for f in glob('src/*.cpp')]
obj = ['build/obj/' + os.path.basename(str(s)) for s in src]


# --- BUILD ---------------------------------------------------------------------------------------
if debug:
    app = env.Program(target=f'build/bin/{OUTPUT_NAME}-debug', source=obj)
else:
    app = env.Program(target=f'build/bin/{OUTPUT_NAME}-{VERSION_MAJOR}.{VERSION_MINOR}', source=obj)

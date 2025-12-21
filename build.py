import platform
import subprocess
import glob

# =-=-=-=-= Global Settings =-=-=-=-=-=

COMPILER        = "clang++"
SOURCE_PATH     = "src"
APP_NAME        = "sandbox"

INCLUDES        = "-Iexternal -Isrc"
WARNINGS        = "-Wno-writable-strings -Wno-format-security -Wno-c++17-extensions -Wno-unused-value"

# =-=-=-=-= Platform Settings =-=-=-=-=-=

OS = platform.system()

if OS == "Windows":
    LIBRARIES = "-luser32 -lopengl32 -lgdi32"

elif OS == "Linux":
    LIBRARIES = "-lX11"


# =-=-=-=-= Logging Colors =-=-=-=-=-=

BLACK       = "\033[30m"
RED         = "\033[31m"
GREEN       = "\033[32m"
YELLOW      = "\033[33m"
BLUE        = "\033[34m"
MAGENTA     = "\033[35m"
CYAN        = "\033[36m"
WHITE       = "\033[37m"

BRIGHT_BLACK   = "\033[90m"
BRIGHT_RED     = "\033[91m"
BRIGHT_GREEN   = "\033[92m"
BRIGHT_YELLOW  = "\033[93m"
BRIGHT_BLUE    = "\033[94m"
BRIGHT_MAGENTA = "\033[95m"
BRIGHT_CYAN    = "\033[96m"
BRIGHT_WHITE   = "\033[97m"

RESET       = "\033[0m"

# =-=-=-=-= Build Script =-=-=-=-=-=

# find all .cpp files
SOURCE_CODE = glob.glob(f"{SOURCE_PATH}/**/*.cpp",recursive=True)

# transforms array list to string
SOURCE_CODE = " ".join(SOURCE_CODE)

# adds .exe if on windows
if OS == "Windows":
    APP_NAME += ".exe"

print(f"{BRIGHT_CYAN}Platform:{BRIGHT_BLUE} {OS}{RESET}")

print("")
print(f"{YELLOW}Building...{RESET}")
subprocess.run(f"{COMPILER} {SOURCE_CODE} -o {APP_NAME} {LIBRARIES} {INCLUDES} {WARNINGS}", shell=True)
print(f"{GREEN}Build Done!{RESET}")
    
# System-of-build

This is a simple build system for C/C++.\
Syntax example:
```
TARGET_1 = example1
SRC_1 = main1.cpp

TARGET_2 = example2
SRC_2 = main2.cpp

set_build_folder: build
set_c_standart: 17
set_cpp_standart: "23"
set_debug_mode: "On"

if $SYSTEM == WINDOWS and ($SYSTEM != LINUX)
	set_c_compiler: gcc
	set_cpp_compiler: g++
elif ($SYSTEM != APPLE)
	set_cpp_compiler: "g++"
else
	set_cpp_compiler: 'clang++'
endif

add_executable: $TARGET_1 $SRC_1
add_executable: $TARGET_2 $SRC_2
```

Usage:
`sob [path_to_sob_file]`

Example:
project/\
---- .sob\
---- main.cpp

.sob:
```
set_build_folder: build
set_cpp_compiler: clang++
add_executable: project main.cpp
```

main.cpp:
```
#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
```

build:\
`sob` or `sob .sob`

after build:\
project/\
---- build/\
---- ---- main.cpp.o\
---- ---- project\
---- .sob\
---- main.cpp

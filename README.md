## **Introduction**

SoB is a build system for the C and C++ languages, focused on ease of use and speed.

## Using

To use the system in your project, you need to create a .sob file and run the sob program. If the .sob file is not located in the work directory, then you need to specify the path to the file or the path to the folder with the file.

**Example:**

```
TARGET = program.exe
SRC = main.cpp

add_executable: $TARGET $SRC
```

```bash
$ sob path/to/.sob
```

## Syntax

The syntax of SoB is quite light.

**Strings:**

First, everything in SoB is a string, except for some exceptions. Secondly, if you write *hello world*, it will not be equal to "hello world", it will be two different words. Accordingly, the system recognizes this string as two words.

**Variables:**

Variables are created in the same way as in Make. Example:

```
TARGET = program.exe
```

But they don't work the way they do in Make! If everything after ‘=’ is assigned to a variable in Make, then only the first element is assigned in SoB. And if you need to assign several words to a variable, then you should use quotation marks. Example:

```
SRC = "main.cpp foo.cpp bar.cpp"
```

In order to get the value of a variable, put ‘$’ before its name.

```
add_executable: $TARGET $SRC
```

There are also system variables in the system:

```
SYSTEM = LINUX
C_COMPILER = gcc
CPP_COMPILER = g++
BUILD_FOLDER = .
DEBUG_MODE = Off
C_STANDART = 17
CPP_STANDART = 17
```

In **Windows**, the variables **SYSTEM**, **C_COMPILER**, **CPP_COMPILER** are equal to *WINDOWS*, *msvc*, *msvc*, respectively. In **MacOs**, the variables **SYSTEM**, **C_COMPILER**, **CPP_COMPILER** are equal to *APPLE*, *clang*, *clang++*, respectively.

**Functions:**

Functions in SoB are needed to access the variables of the system itself. Example:

```
set_c_compiler: gcc
```

The exception is the *add_executable* function, which saves the name and sources for the executable.

A list of all functions with a usage example:

```
add_executable: program.exe main.cpp foo.cpp
set_build_folder: build
set_debug_mode: On
set_c_compiler: gcc
set_c_standart: 11
set_cpp_compiler: g++
set_cpp_standart: 17
```

**Conditional construction:**

There is nothing unusual about conditional constructions, just here is an example:

```
if $SYSTEM == LINUX
	set_c_compiler: gcc
elif $SYSTEM == APPLE
	set_c_compiler: clang
else
	set_c_compiler: clang
endif
```

Attention! In no case do not write a conditional construction in one line, otherwise the system will either give an error or ignore the commands.
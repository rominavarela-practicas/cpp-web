##########################################################
program_NAME = pion
CXXFLAGS+= -std=c++11

##########################################################
### all .c, .cpp and .o
program_C_SRCS = $(wildcard ./src/*.c)
program_CXX_SRCS = $(wildcard ./src/*.cpp)
program_SRCS =  $(program_C_SRCS) $(program_CXX_SRCS)

##########################################################
### -I ./include
###  directory with .h, .hpp
###  include<>
program_INCLUDE_DIRS = ./include
###  -L ./lib
###  directory with .a .so .lib .dll
program_LIBRARY_DIRS =
###  linux:   lib***.a = -l***
###  windows: lib***.lib = -lib***.lib
program_LIBRARIES = boost_system pthread

#  include
CPPFLAGS += $(foreach includedir,$(program_INCLUDE_DIRS),-I$(includedir))
#  link
LDFLAGS += $(foreach librarydir,$(program_LIBRARY_DIRS),-L$(librarydir))
LDFLAGS += $(foreach library,$(program_LIBRARIES),-l$(library))

##########################################################
all:
	$(CXX) $(CXXFLAGS) $(program_SRCS) $(LDFLAGS) $(CPPFLAGS) -o $(program_NAME)


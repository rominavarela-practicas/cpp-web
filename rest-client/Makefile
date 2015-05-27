##########################################################
program_NAME = client
CXXFLAGS+= -std=c++11

##########################################################
### all .c, .cpp and .o
program_C_SRCS = $(wildcard ./src/*.c)
program_CXX_SRCS = $(wildcard ./src/*.cpp)
program_SRCS =  $(program_C_SRCS) $(program_CXX_SRCS)

program_C_OBJS = ${program_C_SRCS:.c=.o}
program_C_OBJS = ${program_C_SRCS:./src/=}
program_CXX_OBJS = ${program_CXX_SRCS:.cpp=.o}
program_CXX_OBJS = ${program_CXX_SRCS:./src/=}
program_OBJS = $(program_C_OBJS) $(program_CXX_OBJS)

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
program_LIBRARIES = curl

#  include
CPPFLAGS += $(foreach includedir,$(program_INCLUDE_DIRS),-I$(includedir))
#  link
LDFLAGS += $(foreach librarydir,$(program_LIBRARY_DIRS),-L$(librarydir))
LDFLAGS += $(foreach library,$(program_LIBRARIES),-l$(library))

##########################################################
all:
	$(CXX) $(CXXFLAGS) $(program_SRCS) $(LDFLAGS) $(CPPFLAGS) -o $(program_NAME)

clean:
	@- $(RM) $(program_OBJS)

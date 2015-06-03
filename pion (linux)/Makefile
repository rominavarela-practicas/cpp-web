##########################################################
program_NAME = client
CXXFLAGS+= -std=c++11

##########################################################
### all .c, .cpp and .o
program_SRC_DIRS += ./src/ ./lib/pion/src/
program_SRCS +=  $(foreach dir,$(program_SRC_DIRS),$(wildcard $(dir)*.c))
program_SRCS +=  $(foreach dir,$(program_SRC_DIRS),$(wildcard $(dir)*.cc))
program_SRCS +=  $(foreach dir,$(program_SRC_DIRS),$(wildcard $(dir)*.cpp))

##########################################################
### -I ./include
###  directory with .h, .hpp
###  include<>
program_INCLUDE_DIRS = ./lib/pion/include
#  include
CPPFLAGS += $(foreach includedir,$(program_INCLUDE_DIRS),-I$(includedir))

##########################################################
### LINK
### .a .so .lib .dll
# dirs
program_LIBRARY_DIRS =
LDFLAGS += $(foreach librarydir,$(program_LIBRARY_DIRS),-L$(librarydir))

# links
###  linux:   lib***.a = -l***
###  windows: lib***.lib = -lib***.lib
boost_LIBRARIES = system thread regex filesystem
program_LIBRARIES = pthread log4cpp ssl crypto dl z

LDFLAGS += $(foreach lib,$(boost_LIBRARIES),-lboost_$(lib))
LDFLAGS += $(foreach lib,$(program_LIBRARIES),-l$(lib))


##########################################################
all:
	$(CXX) $(CXXFLAGS) $(program_SRCS) $(LDFLAGS) $(CPPFLAGS) -o $(program_NAME)

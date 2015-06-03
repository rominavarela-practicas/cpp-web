##########################################################
program_NAME = client
CXXFLAGS+= -std=c++11 -Wno-deprecated -DBOOST_LOG_DYN_LINK

##########################################################
### all sources

#src
program_SRC_DIRS += ./src/

#avro
avro_SRC_DIRS = impl/ impl/json/ impl/parsing/
program_SRC_DIRS +=  $(foreach dir,$(avro_SRC_DIRS), ./include/avro/$(dir))

#csi
csi_SRC_DIRS = csi_http/ csi_http/client/ csi_http/csi_avro/
program_SRC_DIRS +=  $(foreach dir,$(csi_SRC_DIRS), ./include/$(dir))

#all
program_SRCS +=  $(foreach dir,$(program_SRC_DIRS),$(wildcard $(dir)*.cc))
program_SRCS +=  $(foreach dir,$(program_SRC_DIRS),$(wildcard $(dir)*.cpp))

##########################################################
### -I ./include
###  directory with .h, .hpp
###  include<>
program_INCLUDE_DIRS = ./include ./include/avro ./include/csi_http
#  include
CPPFLAGS += $(foreach dir,$(program_INCLUDE_DIRS),-I$(dir))

##########################################################
### LINK
### .a .so .lib .dll
# dirs
program_LIBRARY_DIRS =
LDFLAGS += $(foreach librarydir,$(program_LIBRARY_DIRS),-L$(librarydir))

# links
boost_LIBRARIES = system log program_options iostreams chrono
program_LIBRARIES = pthread curl ssl crypto

LDFLAGS += $(foreach lib,$(boost_LIBRARIES),-lboost_$(lib))
LDFLAGS += $(foreach lib,$(program_LIBRARIES),-l$(lib))

##########################################################
all:
	$(CXX) $(CXXFLAGS) $(program_SRCS) $(LDFLAGS) $(CPPFLAGS) -o $(program_NAME)

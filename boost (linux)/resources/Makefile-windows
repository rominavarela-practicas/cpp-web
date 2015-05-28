SRC = src/01_timer.cpp
TARGET = -o 01_timer
INCLUDES = -lwsock32 -lws2_32 -lboost_system-mgw48-mt-d-1_55
INCLUDE_BOOST = -L C:/local/boost_1_58_0/stage/lib -I C:/local/boost_1_58_0
CONFIG = -D _WIN32_WINNT=0x0501

all:

	g++ $(CONFIG) $(INCLUDE_BOOST) $(INCLUDES) $(TARGET) $(SRC)
SRC = main.cpp

TARGET_DIR 	= ./bin
TARGET 		= $(TARGET_DIR)/prog

CXX 		= 	g++
CXXFLAGS 	= 	-ggdb3 -std=c++11 -O2 -Wall -Wextra -fno-elide-constructors

.PHONY:
check:
	if [ ! -d "$(TARGET_DIR)" ]	; then	\
		mkdir  $(TARGET_DIR)	;		\
	fi

.PHONY:
build: check
	$(CXX) $(CXXFLAGS) $(SRC) $(INCLUDE) -o $(TARGET)

.PHONY:
run:
	./bin/prog


.DEFAULT_GOAL = build
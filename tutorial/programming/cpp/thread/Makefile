FileName=threading
bin= ../bin/

CFlag=-g -Wall -std=c++17
LdFlag= -pthread

src=$(shell ls src/*.cpp)
tmp=$(subst src,obj,$(src))
obj=$(subst .cpp,.o,$(tmp))


all: $(obj)
	g++ $(CFlag) $(obj) -o $(bin)$(FileName) $(LdFlag)
	$(bin)$(FileName)

obj/%.o: src/%.cpp
	g++ $(CFlag) -c $< -o $@ $(LdFlag)

clear:
	rm -rf obj/*.o

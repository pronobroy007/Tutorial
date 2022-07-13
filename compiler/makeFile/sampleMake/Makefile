CC=g++
CFlag=-std=c++11

#Here "$(BUILD)" is command line argument"
#We assign it like this "Make BUILD=release"
ifeq ($(BUILD), release)
	CFLAG+=-O2 -s -DNDEBUG
else
	CFlag+=-Wall -g 
endif


###############################################################
# src = src/*cpp
# tmp = obj/*.cpp
# obj = obj/*.o
###############################################################
src=$(shell ls src/*.cpp)
tmp=$(subst src,obj,$(src))
obj=$(subst .cpp,.o,$(tmp))


hello: $(obj)
	$(CC) $(CFlag) $(obj) -o bin/hello
	./bin/hello


obj/%.o: src/%.cpp
	$(CC) $(CFlag) -c $< -o $@

release:
	make "BUILD=release"

clean:
	rm -rf obj/*
	

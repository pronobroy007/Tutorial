cc=g++ 
cflage=-g -std=c++17 -Wall 
lib=-l sqlite3

project=./bin/exe

src=$(shell ls src/*.cpp)
tmp=$(subst src,obj,$(src))
obj=$(subst .cpp,.o,$(tmp))


server: $(obj)
	$(cc) $(cflage) $(obj) -o $(project) $(lib)
	$(project)

obj/%.o: src/%.cpp
	$(cc) $(cflage) -c $< -o $@ $(fflage) $(lib)

clean:
	rm -rf obj/*.o
	rm -rf ../lib/obj/*.o
	rm -rf $(project)


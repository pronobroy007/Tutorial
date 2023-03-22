cc=g++
cflage=-Wall -g
fflage=-l sqlite3 -pthread

src=$(shell ls src/*.cpp) \
	$(shell ls src/database/*.cpp) \
	$(shell ls ../lib/src/*.cpp)

tmp0=$(subst src,obj,$(src))
tmp=$(subst database/,,$(tmp0))
obj=$(subst .cpp,.o,$(tmp))


server: $(obj)
	$(cc) $(cflage) $(obj) -o bin/server $(fflage)
	bin/server


obj/%.o: src/%.cpp
	$(cc) $(cflage) -c $< -o $@ $(fflage)

obj/%.o: src/database/%.cpp
	$(cc) $(cflage) -c $< -o $@ $(fflage)

../lib/obj/%.o: ../lib/src/%.cpp
	$(cc) $(cflage) -c $< -o $@ $(fflage)


clean:
	rm -rf obj/*.o
	rm -rf ../lib/obj/*.o


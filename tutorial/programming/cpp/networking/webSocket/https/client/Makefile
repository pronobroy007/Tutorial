flag=g++ -g -Wall 
lib=-L/usr/local/ssl/lib -lssl -lcrypto  

src=$(shell ls src/*.cpp)\
	$(shell ls ../lib/src/*cpp)

tmp=$(subst src,obj,$(src))
obj=$(subst .cpp,.o,$(tmp))


client: $(obj)
	$(flag) $(obj) -o bin/client $(lib)
	bin/client


obj/%.o: src/%.cpp
	$(flag) -c $< -o $@ $(lib)


../lib/obj/%.o: ../lib/src/%.cpp
	$(flag) -c $< -o $@ $(lib)


clean:
	rm -rf obj/*.o
	rm -rf ../lib/obj/*.o

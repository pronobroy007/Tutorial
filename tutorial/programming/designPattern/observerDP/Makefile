cc=g++ 
cflage=-g -std=c++17 -Wall -pthread 

project=./bin/hello

# In Case we have multiple ".cpp" files in multiple places : 
#------------------------------------------------------------
# 	src=$(shell ls src/*.cpp) \
# 		$(shell ls src/database/*.cpp) \
# 		$(shell ls ../lib/src/*.cpp)
# 	
# 	tmp0=$(subst src,obj,$(src))
# 	tmp=$(subst database/,,$(tmp0))
# 	obj=$(subst .cpp,.o,$(tmp))


src=$(shell ls src/*.cpp)
tmp=$(subst src,obj,$(src))
obj=$(subst .cpp,.o,$(tmp))


server: $(obj)
	$(cc) $(cflage) $(obj) -o $(project) 
	$(project)

obj/%.o: src/%.cpp
	$(cc) $(cflage) -c $< -o $@ $(fflage)

clean:
	rm -rf obj/*.o
	rm -rf ../lib/obj/*.o
	rm -rf $(project)


CC=g++
CFLAG=-std=c++17 
LIB=-L/usr/local/ssl/lib -lssl -lcrypto -pthread


#Here "$(BUILD)" is command line argument"
#We assign it like this "Make BUILD=release"
ifeq ($(BUILD), release)
	CFLAG+=-O2 -s -DNDEBUG
else
	CFLAG+=-g -Wall 
endif

project=./bin/cryptography

src=$(shell ls src/*.cpp)
tmp=$(subst src,obj,$(src))
obj=$(subst .cpp,.o,$(tmp))


client: $(obj)
	$(CC) $(CFLAG) $(obj) -o $(project) $(LIB)
	$(project)

obj/%.o: src/%.cpp
	$(CC) $(CFLAG) -c $< -o $@ $(LIB)



release: 
	make "BUILD=release"

clean:
	rm -rf $(project)
	rm -rf Decrypt Encrypt pubKey priKey Sign
	rm -rf obj/*.o 

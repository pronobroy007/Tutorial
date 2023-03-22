#FileName=connectDB
FileName=prepareStmt
bin= ../bin/

all:
	g++ -g -Wall $(FileName).cpp -o $(bin)$(FileName) -l sqlite3
	$(bin)$(FileName)
clear:
	rm -rf $(bin)$(FileName)

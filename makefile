
#LFLAGS=-L lua_code/src -l lua -llua -lm -ldl
#BINPATH=bin
#OUTFILE=-o $BINPATH/luafilter

#1、wildcard : 扩展通配符
#2、notdir ： 去除路径
#3、patsubst ：替换通配符
INCLUDES=-I./lua_code/src -I./service/inc
SOURCE=$(wildcard ./service/src/*.cpp)
#SOURCE=$(wildcard ./service/src/luafilter.cpp)
OBJ=$(patsubst %.c, %.o, $(SOURCE))
LIB_PATH=-L./lua_code/src 
LIBS=-llua -lm -ldl

BINPATH=./bin


DEBUG=-D_MACRO    #宏定义  
CFLAGS=-Wall -c   #编译标志位 

CC=g++
TARGET=luafilter
$(TARGET): $(OBJ)     
    #@mkdir -p output/   #创建一个目录，用于存放已编译的目标  
	mkdir -p $(BINPATH)
	$(CC) $(OBJ) $(INCLUDES) $(LIB_PATH) $(LIBS) -o $(BINPATH)/$(TARGET)   
	#.$(VERSION)  

#%.o: %.c  
#	$(CC) $(INCLUDES) $(DEBUG) $(CFLAGS) $< -o $@  

.PHONY: clean  
clean:  
	rm -rf $(OBJ) output/

#g++ luafilter.cpp -L ../../lua_code/src -l lua -llua -lm -ldl -o luafilter -I ../inc -I ../../lua_code/src


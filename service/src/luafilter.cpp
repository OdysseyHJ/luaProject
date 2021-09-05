//##############################################
// filename:    luafilter.cpp
// author:      Brook Taylor
// date:        2021.9.4
// description: lua过滤器
//##############################################


//common file
#include <iostream>
#include <string>
#include <vector>


 
extern "C"  
{  
    #include "lua.h"  
    #include "lauxlib.h"  
    #include "lualib.h"  
} 


//private file
#include "lua_def.h"
#include "status_def.h"


int FilterResProc(lua_State *pLuaState)
{
    std::cout << "call callback successsful!" << std::endl;

    int nIndex = 0;
    int nTemp = -1;

    lua_settop(pLuaState, 0);
    lua_getglobal(pLuaState, LUA_VAR_FILTER_RES);
    int nLength = luaL_len(pLuaState, 1);
    
    for(int i = 0; i < nLength; i++)
    {
        lua_pushnumber(pLuaState, i+1);
        lua_gettable(pLuaState, -2);
        nTemp = lua_tonumber(pLuaState, -1);
        std::cout << nTemp << std::endl;
        lua_pop(pLuaState, 1);
    }

    return 0;
}

int main()
{


    //创建lua虚拟机
    lua_State *pLuaState = luaL_newstate();  
    luaL_openlibs(pLuaState);

    //注册lua回调函数
    lua_register(pLuaState, LUA_CALLBACK_FILTER_RES_PROC, FilterResProc);
    
    std::string strLuaPath = "../../lua/filter.lua";

    int nLuaRet = 0;
    nLuaRet = luaL_dofile(pLuaState, strLuaPath.c_str());
    if(nLuaRet)
    {
        std::string strError = (std::string)lua_tostring(pLuaState, -1);
        std::cout << "lua load error: "<< strError.c_str() << std::endl;
        return RET_ERROR;
    }

    std::string strGlobalName = LUA_FUNC_DATATYPE_FILTER;
    std::cout << strGlobalName << std::endl;
    nLuaRet = lua_getglobal(pLuaState, strGlobalName.c_str());
    std::cout << "nLuaRet: " << nLuaRet << std::endl;

    //创建lua table
    lua_newtable(pLuaState);
    for(int i=0; i<10; i++)
    {
        lua_pushnumber(pLuaState, i+1);
        lua_rawseti(pLuaState, -2, i+1);
    }

    //执行lua函数,
    nLuaRet = lua_pcall(pLuaState, 1, 0, 0);
    if(nLuaRet)
    {
        std::string strError = (std::string)lua_tostring(pLuaState, -1);
        std::cout << "lua pcall error: "<< strError.c_str() << std::endl;
        return RET_ERROR;
    }


    //获取过滤结果，通过全局变量来处理。。。这个方案略蠢，需要改进
    int nTemp = -1;
    lua_settop(pLuaState, 0);
    lua_getglobal(pLuaState, LUA_VAR_FILTER_RES);
    int nFilterRetLength = luaL_len(pLuaState, 1);
    std::vector<int> vecFilterRes(nFilterRetLength, -1);
    for(int i = 0; i < nFilterRetLength; i++)
    {
        lua_pushnumber(pLuaState, i+1);
        lua_gettable(pLuaState, -2);
        vecFilterRes[i] = lua_tonumber(pLuaState, -1);
        printf("result: index=%u, value=%u\n", i, vecFilterRes[i]);
        lua_pop(pLuaState, 1);
    }
    

    std::cout << "cpp-lua filter excute completely." << std::endl;
    return RET_OK;
}






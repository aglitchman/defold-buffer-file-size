#include <dmsdk/sdk.h>

#include <cstring>

static union TypeConversion {
    char string[4];

    float float32;

    unsigned char uint8[4];
    char int8[4];

    unsigned short uint16[2];
    short int16[2];
};
static TypeConversion t;

static int StrFloat32(lua_State* L)
{
    size_t buf1_len;

    const char* buf1 = luaL_checklstring(L, 1, &buf1_len);
    const int offset = luaL_checkint(L, 2);

    memcpy(t.string, buf1 + offset, 4);
    lua_pushnumber(L, t.float32);
    
    return 1;
}

static int StrInt8(lua_State* L)
{
    size_t buf1_len;

    const char* buf1 = luaL_checklstring(L, 1, &buf1_len);
    const int offset = luaL_checkint(L, 2);

    memcpy(t.string, buf1 + offset, 1);
    lua_pushinteger(L, t.int8[0]);

    return 1;
}

static int StrUint8(lua_State* L)
{
    size_t buf1_len;

    const char* buf1 = luaL_checklstring(L, 1, &buf1_len);
    const int offset = luaL_checkint(L, 2);

    memcpy(t.string, buf1 + offset, 1);
    lua_pushinteger(L, t.uint8[0]);

    return 1;
}

static int StrInt16(lua_State* L)
{
    size_t buf1_len;

    const char* buf1 = luaL_checklstring(L, 1, &buf1_len);
    const int offset = luaL_checkint(L, 2);

    memcpy(t.string, buf1 + offset, 2);
    lua_pushinteger(L, t.int16[0]);

    return 1;
}

static int StrUint16(lua_State* L)
{
    size_t buf1_len;

    const char* buf1 = luaL_checklstring(L, 1, &buf1_len);
    const int offset = luaL_checkint(L, 2);

    memcpy(t.string, buf1 + offset, 2);
    lua_pushinteger(L, t.uint16[0]);

    return 1;
}

// Functions exposed to Lua
static const luaL_reg Module_methods[] = {
    { "str_float32", StrFloat32 },
    { "str_int8", StrInt8 },
    { "str_uint8", StrUint8 },
    { "str_int16", StrInt16 },
    { "str_uint16", StrUint16 },
    /* Sentinel: */
    { NULL, NULL }
};

static void LuaInit(lua_State* L)
{
    int top = lua_gettop(L);

    // Register lua names
    luaL_register(L, "ext", Module_methods);

    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}

static dmExtension::Result InitializeExt(dmExtension::Params* params)
{
    LuaInit(params->m_L);

    return dmExtension::RESULT_OK;
}

static dmExtension::Result FinalizeExt(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

DM_DECLARE_EXTENSION(ext, "ext", 0, 0, InitializeExt, 0, 0, FinalizeExt)

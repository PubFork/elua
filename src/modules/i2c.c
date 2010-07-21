// Module for interfacing with the I2C interface

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "platform.h"
#include "auxmods.h"
#include "lrotable.h"
#include <string.h>
#include <ctype.h>

// Lua: speed = i2c.setup( id, speed )
static int i2c_setup( lua_State *L )
{
  unsigned id = luaL_checkinteger( L, 1 );
  u32 speed = ( u32 )luaL_checkinteger( L, 2 );

  MOD_CHECK_ID( i2c, id );
  lua_pushinteger( L, platform_i2c_setup( id, speed ) );
  return 1;
}

// Lua: i2c.start( id )
static int i2c_start( lua_State *L )
{
  unsigned id = luaL_checkinteger( L, 1 );

  MOD_CHECK_ID( i2c, id );
  platform_i2c_send_start( id );
  return 0;
}

// Lua: i2c.stop( id )
static int i2c_stop( lua_State *L )
{
  unsigned id = luaL_checkinteger( L, 1 );

  MOD_CHECK_ID( i2c, id );
  platform_i2c_send_stop( id );
  return 0;
}

// Lua: i2c.address( id, address, direction )
static int i2c_address( lua_State *L )
{
  unsigned id = luaL_checkinteger( L, 1 );
  u16 address = ( u16 )luaL_checkinteger( L, 2 );
  int direction = luaL_checkinteger( L, 3 );

  MOD_CHECK_ID( i2c, id );
  lua_pushboolean( L, platform_i2c_send_address( id, address, direction ) );
  return 1;
}

// Lua: wrote = i2c.write( id, string | table | 8-bit number )
static int i2c_write( lua_State *L )
{
  unsigned id = luaL_checkinteger( L, 1 );
  const char *pdata;
  size_t datalen, i;
  int numdata;
  u32 wrote;

  MOD_CHECK_ID( i2c, id );
  if( lua_isnumber( L, 2 ) )
  {
    numdata = ( int )luaL_checkinteger( L, 2 );
    if( numdata < 0 || numdata > 255 )
      return luaL_error( L, "numeric data can be between 0 and 255" );
    wrote = platform_i2c_send_byte( id, numdata );
  }
  else if( lua_istable( L, 2 ) )
  {
    datalen = lua_objlen( L, 2 );
    for( i = 0; i < datalen; i ++ )
    {
      lua_rawgeti( L, 2, i + 1 );
      numdata = luaL_checkinteger( L, -1 );
      lua_pop( L, 1 );
      if( numdata < 0 || numdata > 255 )
        return luaL_error( L, "numeric data can be between 0 and 255" );
      if( platform_i2c_send_byte( id, numdata ) == 0 )
        break;
    }
    wrote = i;
  }
  else
  {
    pdata = luaL_checklstring( L, 2, &datalen );
    for( i = 0; i < datalen; i ++ )
      if( platform_i2c_send_byte( id, pdata[ i ] ) == 0 )
        break;
    wrote = i;
  }
  lua_pushinteger( L, wrote );
  return 1;
}

// Lua: read = i2c.read( id, size )
static int i2c_read( lua_State *L )
{
  unsigned id = luaL_checkinteger( L, 1 );
  u32 size = ( u32 )luaL_checkinteger( L, 2 ), i;
  luaL_Buffer b;
  int data;

  MOD_CHECK_ID( i2c, id );
  luaL_buffinit( L, &b );
  for( i = 0; i < size; i ++ )
    if( ( data = platform_i2c_recv_byte( id, i < size - 1 ) ) == -1 )
      break;
    else
      luaL_addchar( &b, ( char )data );
  luaL_pushresult( &b );
  return 1;
}

// Module function map
#define MIN_OPT_LEVEL   2
#include "lrodefs.h"
const LUA_REG_TYPE i2c_map[] = 
{
  { LSTRKEY( "setup" ),  LFUNCVAL( i2c_setup ) },
  { LSTRKEY( "start" ), LFUNCVAL( i2c_start ) },
  { LSTRKEY( "stop" ), LFUNCVAL( i2c_stop ) },
  { LSTRKEY( "address" ), LFUNCVAL( i2c_address ) },
  { LSTRKEY( "write" ), LFUNCVAL( i2c_write ) },
  { LSTRKEY( "read" ), LFUNCVAL( i2c_read ) },
#if LUA_OPTIMIZE_MEMORY > 0
  { LSTRKEY( "SPEED_FAST" ), LNUMVAL( PLATFORM_I2C_SPEED_FAST ) },
  { LSTRKEY( "SPEED_SLOW" ), LNUMVAL( PLATFORM_I2C_SPEED_SLOW ) },
  { LSTRKEY( "TRANSMITTER" ), LNUMVAL( PLATFORM_I2C_DIRECTION_TRANSMITTER ) },
  { LSTRKEY( "RECEIVER" ), LNUMVAL( PLATFORM_I2C_DIRECTION_RECEIVER ) },
#endif
  { LNILKEY, LNILVAL }
};

LUALIB_API int luaopen_i2c( lua_State *L )
{
#if LUA_OPTIMIZE_MEMORY > 0
  return 0;
#else // #if LUA_OPTIMIZE_MEMORY > 0
  luaL_register( L, AUXLIB_I2C, i2c_map );
  
  // Add the stop bits and parity constants (for uart.setup)
  MOD_REG_NUMBER( L, "SPEED_FAST", PLATFORM_I2C_SPEED_FAST );
  MOD_REG_NUMBER( L, "SPEED_SLOW", PLATFORM_I2C_SPEED_SLOW ); 
  MOD_REG_NUMBER( L, "TRANSMITTER", PLATFORM_I2C_DIRECTION_TRANSMITTER );
  MOD_REG_NUMBER( L, "RECEIVER", PLATFORM_I2C_DIRECTION_RECEIVER );
  
  return 1;
#endif // #if LUA_OPTIMIZE_MEMORY > 0
}

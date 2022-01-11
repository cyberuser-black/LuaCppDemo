## Overview
A minimal demo of moving serialized data between two Lua scripts through C++.

In this demo, two lua scripts named ```a.lua``` and ```b.lua```, both expose the following API functions:
```lua
-- API: GetDataStr
function GetDataStr()
    
-- API: PushDataStr
function PushDataStr(datastr)
```
Where ```GetDataStr()``` returns a string of serialized data ('```DataStr```') which could for example be the result of parsing a file,
and ```PushDataStr(datastr)``` gets a string of serialized data which could be used for example in a calculation.

These functions can be used in C++ via the [LuaCppAPI](LuaCppAPI/LuaCppAPI.h) interface. 

The Lua table-to-string serialization logic is <b>invariant</b> (could be [JSON](https://www.json.org/json-en.html), [Protobuf](https://developers.google.com/protocol-buffers/docs/encoding), [base64](https://www.base64decode.org/), etc.) as long as it implements the following:
```lua
-- Serialize a Lua table to a string
function Serializer.TableToDataStr(table)

-- Deserialize a string into a Lua table
function Serializer.DataStrToTable(datastr)
```

For the purposes of this demo, serialization is implemented using JSON - See [Serializer.lua](LuaCppAPI/Serializer.lua). 
## Setup (Linux)
1) Install Lua on your system - [follow this tutorial](https://www.tecmint.com/install0lua0in-centos-ubuntu-linux)
    ```shell
   sudo apt install build-essential libreadline-dev
   mkdir lua_build
   cd lua_build
   curl -R -O http://www.lua.org/ftp/lua-5.3.4.tar.gz
   tar -zxf lua-5.3.4.tar.gz
   cd lua-5.3.4
   make linux test
   sudo make install
    ```
2) Install luarocks
   ```shell
   sudo apt install luarocks
   ```
3) Install Luajson
   ```shell
   sudo luarocks install lunajson
   ```
4) Clone this repository
   ```shell
   git clone https://github.com/cyberuser-black/AprilONeil.git
   ```
5) Build the project
   ```shell
   mkdir build
   cd build
   cmake .. && make
   ```

## Usage
1) Go into the build directory, and execute the binary
   ```shell
   cd build
   ./LuaCppDemo
   ```
   

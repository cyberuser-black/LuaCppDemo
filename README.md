## Overview
```Lua``` is an embedded language. That means that ```Lua``` is not a stand-alone package,
but a library that can be linked with other applications to incorporate ```Lua``` facilities
into these applications.

```Lua```'s [C API](https://www.lua.org/pil/24.html) is a set of functions that
allow C code to interact with ```Lua```, and you should have some familiarity with it in order
to understand what this project is really doing for you.

[LuaCppAPI](LuaCppAPI) is a simplified wrapper around that original [C API](https://www.lua.org/pil/24.html).
It exposes only the minimal ```GetDataStr()``` and ```PushDataStr(datastr)``` methods required to move serialized data between ```Lua``` and ```C++```.


###Project structure
* ```LuaCppAPI/``` - A directory containing the ```C++``` and ```Lua``` implementations of the interface.
  * ```LuaCppAPI.h``` - Interface declaration for ```C++```
  * ```LuaCppAPI.cpp``` - Interface implementation in ```C++```
  * ```LuaCppAPI.lua``` - Interface <b>reference</b> for ```Lua```
* ```Serialization/``` - <b>User implemented</b> serialization logics to transform lua objects into strings and vice versa.
  * ```ExampleSerializer.lua``` - A simple serializer that uses ```JSON```, provided as an example. 
* ```Demos/``` - A set of demos showing various usages of the interface. 

## Example
How do you get some serialized data from your ```Lua``` script into your ```C++``` code? <br>How do you push serialized data from your ```C++``` code to be handled by a ```Lua``` script? 

The following example shows the two flows of serialized data: ```Lua --> C++``` and ```C++ --> Lua```.

```Lua
-- "get.lua"

function GetDataStr()
   data = {author="Joey", message="How you doin'?"} 
   print("[get.lua] : " .. data["author"] .. " says...")
   datastr = serializer.TableToDataStr(data);
   return datastr
end
```
```Lua
-- "push.lua"

function PushDataStr(datastr)
   data = serializer.DataStrToTable(datastr)
   print("[push.lua] : " .. data["message"]); 
   return 1;
end
```
```cpp
// "main.cpp"

int main() {
    LuaCppAPI::DataStr datastr; // Buffer for holding serialized lua data in C++
    LuaCppAPI("get.lua").GetDataStr(&datastr); // Lua --> C++
    std::cout << "[main.cpp] : " << datastr << std::endl;
    LuaCppAPI("push.lua").PushDataStr(datastr); // C++ --> Lua
    return 0;
}
```
Output
```bash
$ ./main
[get.lua] : Joey says...
[main.cpp] : {"author":"Joey", "message":"How you doin'?"}
[push.lua] : How you doin'?
```

## Under The Hood
In the core [C API](https://www.lua.org/pil/24.html), the communication between ```C++``` 
and ```Lua``` occurs through the ```Lua Stack``` which is accessible to both runtimes.

```Lua``` scripts can push and pop data from the ```Lua Stack``` using ```return``` statements 
(to push) and function arguments ```foo(arg1, arg2)``` (to pop), for example.

```C++``` code can push and pop data from the ```Lua Stack``` using ```lua_pushlstring()``` 
and ```lua_tolstring()``` respectively, just to name a few options.


The  [LuaCppAPI](LuaCppAPI) implements this communication logic internally and exposes the following interfaces:
```C++
/*****************/
/** LuaCppAPI.h **/
/*****************/

// Call lua's GetDataStr() function and assign the returned value to out_datastr.
bool LuaCppAPI::GetDataStr(DataStr *out_datastr);

// Call lua's PushDataStr(datastr) function with the given datastr.
bool LuaCppAPI::PushDataStr(const DataStr &datastr);
```

```lua
-------------------
-- LuaCppAPI.lua --
-------------------

-- Returns serialized data from lua 
function GetDataStr() --> datastr
    
-- Handles serialized data in lua
function PushDataStr(datastr) --> boolean (1=success, 0=failure)
```

### Serialization
In order for ```Lua``` to exchange complex data (like [tables](https://www.lua.org/pil/2.5.html)) with ```C++```, this data needs to be serialized. 
The input for the serializer is any ```Lua``` object, and the output needs to be a string. 
This is why we often refer to a string representing some serialized data as a ```DataStr```, which is essentially just a typedef for ```std::string```.

How to serialize your data is totally **up to you**. There are many viable options like 
[JSON](https://www.json.org/json-en.html), 
[Protobuf](https://developers.google.com/protocol-buffers/docs/encoding), 
[base64](https://www.base64decode.org/), etc. 
<br>Take a look at [ExampleSerializer.lua](Serialization/ExampleSerializer.lua) to get an idea of what we're talking about.

The only requirements from your serializer are:
1) It handles strings containing embedded ```\0``` characters, and 
2) It exposes the following interface:
```lua
-----------------------------------
-- SomeUserDefinedSerializer.lua --
-----------------------------------

-- Serialize a lua table to a string
function Serializer.TableToDataStr(table) --> DataStr

-- Deserialize a string into a lua table
function Serializer.DataStrToTable(datastr) --> table
```
Notice that ```JSON``` has some troubles deserializing strings that contain ```\0```, 
which actually makes it a less viable serializing protocol. Sorry about that.

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
3) Install Luajson (for the JSON serializer)
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

## Demo
This project includes a set of small [demos](Demos) showing the various use cases of the [LuaCppAPI](LuaCppAPI) interface. 
<br>To run these demos, go into the build directory and execute the binary you just compiled:
   ```shell
   cd build
   ./LuaCppDemo
   ```
   
The output should look like this:
```
/home/cyber/CLionProjects/LuaCppDemo/cmake-build-debug/LuaCppDemo

[main.cpp] Running demo_get_then_push('../lua/a.lua', '../lua/b.lua')... 
[main.cpp] Calling GetDataStr('../lua/a.lua')...
[a.lua] GetDataStr() --> 'how you doin'?'
[main.cpp] DataStr = 'how you doin'?'
[main.cpp] Calling PushDataStr('../lua/b.lua', how you doin'?)...
[b.lua]: PushDataStr('how you doin'?')
[main.cpp] Done!

[main.cpp] Running demo_get_increment('../lua/increment.lua')
[main.cpp] Calling GetDataStr('../lua/increment.lua')...
[increment.lua] GetDataStr() --> 'counter = 1'
[main.cpp] DataStr = 'counter = 1'
[main.cpp] Calling GetDataStr('../lua/increment.lua')...
[increment.lua] GetDataStr() --> 'counter = 2'
[main.cpp] DataStr = 'counter = 2'
[main.cpp] Calling GetDataStr('../lua/increment.lua')...
[increment.lua] GetDataStr() --> 'counter = 3'
[main.cpp] DataStr = 'counter = 3'
[main.cpp] Calling GetDataStr('../lua/increment.lua')...
[increment.lua] GetDataStr() --> 'counter = 4'
[main.cpp] DataStr = 'counter = 4'
[main.cpp] Calling GetDataStr('../lua/increment.lua')...
[increment.lua] GetDataStr() --> 'counter = 5'
[main.cpp] DataStr = 'counter = 5'
[main.cpp] Done!

[main.cpp] Running demo_null_terminator('../lua/null_terminator.lua', '../lua/a.lua')... 
[main.cpp] Calling GetDataStr('../lua/null_terminator.lua')...
[null_terminator.lua] GetDataStr() --> 'null terminator -->   <-- great success!'
[main.cpp] DataStr from Lua = 'null terminator -->   <-- great success!'
[main.cpp] Calling PushDataStr('../lua/a.lua', 'null terminator -->   <-- great success!')...
[a.lua]: PushDataStr('null terminator -->   <-- great success!')
[main.cpp] DataStr by C++ = '{"message":"cyber -->   <-- victory!", "author":"main"}'
[main.cpp] Calling PushDataStr('../lua/a.lua', '{"message":"cyber -->   <-- victory!", "author":"main"}')...
[a.lua]: PushDataStr('{"message":"cyber -->   <-- victory!", "author":"main"}')
[main.cpp] Done!

Process finished with exit code 1
```

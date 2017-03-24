## Icarus

Icarus is a server written in C++ designed for version *PRODUCTION-201512012203-525044429*. 

This should compile out of the box if you open up *Icarus.vcxproj* with Visual Studio 2015 C++

## Compilation

This project isn't anywhere near being completed, don't even bother doing anything yet, but I'm not stopping you, so go ahead.

### Windows

---

*For Windows Server 2012 / Windows 10 possibly earlier Windows versions but this hasn't been tested*

**Download**

 - Download [Boost version 1.63](http://www.boost.org/users/history/version_1_63_0.html) for Windows and extract it somewhere you will remember.
 
 - Download [MySQL C++ Connector](https://dev.mysql.com/downloads/connector/cpp/) **Windows (x86, 64-bit), MSI Installer**
 
 - Download [MySQL C Connector](https://dev.mysql.com/downloads/connector/c/) **Windows (x86, 64-bit), MSI Installer**

**Compiling steps**

- Install [Visual Studio 2015](https://www.microsoft.com/en-us/download/details.aspx?id=48146)

- Make sure you're installing C++ components, this is needed for compiling Boost.

*Configuring and Compiling Boost*

Go to where you extracted boost, create a compile called compile.bat inside the folder where you see bootstrap.bat and add this:

```
call "%VS140COMNTOOLS%..\..\VC\vcvarsall.bat" x86
 
call bootstrap.bat
 
rem Most libraries can be static libs
b2 -j8 toolset=msvc-14.0 address-model=64 architecture=x86 link=static threading=multi runtime-link=shared --build-type=minimal stage --stagedir=stage/x64
b2 -j8 toolset=msvc-14.0 address-model=32 architecture=x86 link=static threading=multi runtime-link=shared --build-type=minimal stage --stagedir=stage/win32
 
pause
```

Execute this file and it should compile, it takes a long time so don't worry if it takes more than 10 minutes.

*Configuring MySQL Connectors*

- Install both MySQL/C and MySQL/C++ Connector in the links above

- Remember where you installed these, the paths are required

- After that's done, please open Icarus.vcxproj and at the top of Visual Studio where you see **Debug | x86** please change it to **Release | x64** otherwise the program will **not** work correctly.

- Configure the correct Boost and MySQL Connector paths for **Configuration Properties > C/C++ > General > Additional Include Directories** 

*Where you see:*

- **D:\lib\boost_1_63_0**;
- **D:\Program Files\MySQL\MySQL Connector C++ 1.1.8**\include
- **D:\Program Files\MySQL\MySQL Connector C 6.1**\include
- %(AdditionalIncludeDirectories)

You'll want to replace these parts in bold with your installed paths, leave the /include at the end.

Lets not forget **Configuration Properties > Linker > General > Additional Library Directories**

*Where you see:*

- **D:\Program Files\MySQL\MySQL Connector C++ 1.1.8**\lib\opt
- **D:\Program Files\MySQL\MySQL Connector C 6.1**\lib
- **D:\lib\boost_1_63_0**\stage\x64\lib;

Replace the bolded parts with your installed paths, leave the \lib and \lib\opt where they are!

### Linux

---

*Only tested on Ubuntu, have not tested any other Linux distributions at the moment.*

**Download**

Run this command

```git clone https://github.com/TheAmazingAussie/Icarus```

**Download Libraries**

- Boost library (should be using 1.63) 

```sudo apt-get install libboost-dev```

- MySQL C++ Connector

```sudo apt-get install  libmysqlcppconn-dev```

**Compile**

(Ugly command, I know).

Make sure you are in the same folder as the one you downloaded the git repo into.

```
g++-6 -m64 -fpermissive -Wall -Wextra -Wreorder -L /lib64 -I/usr/include/mysql/ -Isrc  src/main.cpp src/stdafx.cpp src/boot/Icarus.cpp src/communication/incoming/MessageHandler.cpp src/communication/streams/Request.cpp src/communication/streams/Response.cpp src/dao/CatalogueDao.cpp src/dao/ItemDao.cpp src/dao/MessengerDao.cpp src/dao/MySQLDao.cpp src/dao/NavigatorDao.cpp src/dao/RoomDao.cpp src/dao/UserDao.cpp src/database/DatabaseManager.cpp src/game/Game.cpp src/game/bot/Bot.cpp src/game/catalogue/CatalogueItem.cpp src/game/catalogue/CatalogueManager.cpp src/game/entities/EntityDetails.cpp src/game/item/Item.cpp src/game/item/ItemManager.cpp src/game/item/inventory/Inventory.cpp src/game/messenger/Messenger.cpp src/game/messenger/MessengerUser.cpp src/game/navigator/NavigatorManager.cpp src/game/navigator/NavigatorTab.cpp src/game/pathfinder/Pathfinder.cpp src/game/pathfinder/PathfinderNode.cpp src/game/pathfinder/Position.cpp src/game/player/Player.cpp src/game/player/PlayerManager.cpp src/game/room/Room.cpp src/game/room/RoomManager.cpp src/game/room/RoomUser.cpp src/game/room/model/DynamicModel.cpp src/game/room/model/RoomModel.cpp src/game/room/model/Rotation.cpp src/game/room/tasks/RoomRunnable.cpp src/misc/Configuration.cpp src/misc/Utilities.cpp src/network/NetworkConnection.cpp src/network/NetworkServer.cpp src/network/rcon/RconConnection.cpp src/network/rcon/RconServer.cpp src/thread/ExecutorService.cpp -lboost_system -lboost_thread -lboost_filesystem -lpthread -lmysqlcppconn -o icarus_server
```

Run server

```./icarus_server```



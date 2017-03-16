## Icarus

Icarus is a server written in C++ designed for version *PRODUCTION-201512012203-525044429*. 

This should compile out of the box if you open up *Icarus.vcxproj* with Visual Studio 2015 C++

## Compilation

This project isn't anywhere near being completed, don't even bother doing anything yet, but I'm not stopping you, so go ahead.

### Windows

---

*For Windows Server 2012 / Windows 10 possibly earlier Windows versions but this hasn't been tested*

**Download**

Click this [link](https://github.com/TheAmazingAussie/Icarus/archive/master.zip), and extract the zip into your favourite folder.

**Compiling steps**

- Install [Visual Studio Community](https://go.microsoft.com/fwlink/?LinkId=691978&clcid=0x409);

- Make sure you're installing C++ components

- Open up Icarus.vcxproj

Click the second "Icarus" down from the top and select "show all files" as that's how the project **should be** viewed like

### Linux

---

*Only tested on Ubuntu, have not tested any other Linux distributions at the moment.*

**Download**

Run this command

```git clone https://github.com/TheAmazingAussie/Icarus```

**Download Libraries**

- Boost library (should be using 16.2)

```sudo apt-get install libboost-dev```

- Mysql C++ Connector

```sudo apt-get install  libmysqlcppconn-dev```

**Compile**

(Ugly command, I know).

Make sure you are in the same folder as the one you downloaded the git repo into.

```
g++-6 -m64 -fpermissive -Wall -Wextra -Wreorder -L /lib64 -I/usr/include/mysql/ -Isrc  src/main.cpp src/stdafx.cpp src/boot/Icarus.cpp src/communication/incoming/MessageHandler.cpp src/communication/streams/Request.cpp src/communication/streams/Response.cpp src/dao/CatalogueDao.cpp src/dao/ItemDao.cpp src/dao/MessengerDao.cpp src/dao/MySQLDao.cpp src/dao/NavigatorDao.cpp src/dao/RoomDao.cpp src/dao/UserDao.cpp src/database/DatabaseManager.cpp src/game/Game.cpp src/game/bot/Bot.cpp src/game/catalogue/CatalogueItem.cpp src/game/catalogue/CatalogueManager.cpp src/game/entities/EntityDetails.cpp src/game/item/Item.cpp src/game/item/ItemManager.cpp src/game/item/inventory/Inventory.cpp src/game/messenger/Messenger.cpp src/game/messenger/MessengerUser.cpp src/game/navigator/NavigatorManager.cpp src/game/navigator/NavigatorTab.cpp src/game/navigator/populators/DefaultPopulator.cpp src/game/navigator/populators/MyRoomPopulator.cpp src/game/navigator/populators/OfficialRoomPopulator.cpp src/game/navigator/populators/PopularPopulator.cpp src/game/pathfinder/Pathfinder.cpp src/game/pathfinder/PathfinderNode.cpp src/game/pathfinder/Position.cpp src/game/player/Player.cpp src/game/player/PlayerManager.cpp src/game/room/Room.cpp src/game/room/RoomManager.cpp src/game/room/RoomUser.cpp src/game/room/model/DynamicModel.cpp src/game/room/model/RoomModel.cpp src/game/room/model/Rotation.cpp src/game/room/tasks/RoomRunnable.cpp src/misc/Configuration.cpp src/misc/Utilities.cpp src/network/NetworkConnection.cpp src/network/NetworkServer.cpp src/network/rcon/RconConnection.cpp src/network/rcon/RconServer.cpp src/thread/ExecutorService.cpp -lboost_system -lboost_thread -lboost_filesystem -lpthread -lmysqlcppconn -o icarus_server
```

Run server

```./icarus_server```



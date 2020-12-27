Uchat project. Not done already)<br>
Work only on osX<br>
You need to install gtk+3 for this app.<br>

````bash
brew install gtk+3

make - install client and server
make reinstall - reinstall all stuff
make clean - clean obj files
make uninstall - delete all obj and binary files
````

````c
server:
use
./uchat_server [port] - to start server
````

````c
client:
use
./uchat [ip] [port] - to connect
````

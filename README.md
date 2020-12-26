Uchat project. Not done already)<br>
Work only on osX<br>
You need to install gtk+3 for this app.<br>
:<br>
   brew install gtk+3

````bash
zsh install all - install client and server
zsh install server - install server without client
zsh install client - install client without server
zsh install clean - delete all obj and binary files
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

These programs allow the transference of files between a client and a server.
Each program can be compiled by using make in their respective directories. The
server will be run by typing './server *port number*', where it will await
a datagram from the client. The client can be run by typing './client *hostname*
*port number*'. The client will then prompt you for a command:


get *file*        -Download the specified file from the server
put *file*        -Upload the specified file to the server
delete *file*     -Delete the specified file
ls                -List all files on the server
exit              -Gracefully exit the client

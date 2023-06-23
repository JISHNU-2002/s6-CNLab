# s6-CNLab
1 TCP 
:TCP (Transmission Control Protocol) is a connecton-oriented protocol
:so for communication between server and client we need to establish a connection first;
  _in server:
    1 - create socket using socket() - it returns an integer value (socket file descriptor(sockfd))
    2 - add values to the structure
    3 - bind the values to socket (only server is binded in every program)
    4 - listen for clients
    5 - accept client connection
    * - send/recieve data through accept function return value
  _in client
    1 - create socket using socket() - it returns an integer value (socket file descriptor(sockfd))
    2 - add values to the structure
    3 - connect to server
    * - send/recieve data through sockfd
    
2 UDP 
:UDP (User Datagram Protocol ) is a connecton-less protocol
:so for communication between server and client there is no need to establish a connection first;
  _in server:
    1 - create socket using socket() - it returns an integer value (socket file descriptor(sockfd))
    2 - add values to the structure
    3 - bind the values to socket (only server is binded in every program)
    4 - first client sends the data then server send/recieve data through accept function return value otherwise it shows an error
    the server has to identify the client first

    * - here data is send/recieve through th socket file descriptor in both server and client
    
  _in client
    1 - create socket using socket() - it returns an integer value (socket file descriptor(sockfd))
    2 - add values to the structure
    3 - send/recieve data through sockfd (client is the first one to initiate the process)
    
3 Sliding Window Protocols 
4 Distance Vector (Bellman Ford) 
5 SMTP (TCP) 

6 FTP (TCP) 
: in FTP client is sending client_file.txt to server 
: so first create 'client_file.txt' in the directory and write something that you would like to send to server 
: server automatically creates a file 'server_file.txt' and read the data from client file and write the data in server_file.txt 
: otherwise the program shows error 

7 Leaky Bucket Algorithm

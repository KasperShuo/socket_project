The socket project
1. Use C language.
2. Use POSIX library.
3. Project is upload to Github ("https://github.com/KasperShuo/socket_project").
4. With README.md.
5. Develop and Demo the project in Debian 10 on a virtual machine.
6. With Video demo.

=========================================

Server:
    [myserverproject]

    "./myserverproject"

    After the socket created, the server will continuously listen the message from client and send the same message back to the client.
    When the server recived the message "stop" from the client, will be closed.


Client:
    [myclientproject]

    Please execute the program with input ip and port.

    "./myclientproject {IP address} {Port number}"

    After the socket created, you can input the message you want to sent to server.
    The server will send back the message if the communication is success.
    If the client cannot receive the message sent back from server, it will try again until the maximun number of retries reach the setting of maximun number of retries, and the retry time will follow the exponential backoff algorithm.

    ○ In the client program, the setting of maximun number of retries is 10.
    ○ Exit program with exit code 0 after the echo message is received
    ○ Exit program with exit code 1 if reach max-retry

Video Demo: (https://drive.google.com/file/d/1TPyEeMvPEBiqMXnPX911T_Q_wGg_ZVNq/view?usp=share_link)

the video was distinguished for three parts.

(1). basic function test. 
    Input message from client, the client will send message to server.
    Server received message and send back the message to client.
    The client received the message sent by server.
(2. Based on (1), 
    when the server received message, will sent back the message to the client after waiting 10 seconds to try the retry function in client.
(2. Based on (2), 
    when the server received message, will sent back the message to the client after waiting 60 seconds to try the max-retry times function in client.



Made by Li-Shuo, Huang (Kasper)
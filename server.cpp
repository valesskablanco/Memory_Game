#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

using namespace std;

int main (){

    //Create a socket
    int listening = socket(AF_INET, SOCK_STREAM, 0);

    if (listening ==-1)
    {
        cerr << "Can't create a socket";
        return -1;
    }

    // Bind the socker to a IP port
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    inet_pton(AF_INET,"0.0.0.0",&hint.sin_addr);

    if (bind(listening, (sockaddr*)&hint, sizeof(hint)) == -1)

    {
        cerr << "Can't bind to IP/Port";
        return -2;
    }

    // Mark the socket for listening
    if (listen(listening, 2) ==-1) //2 es la cantidad de conexiones
    {
        cerr << "Can't listen!";
        return -3;
    }

    // Accept a call
    sockaddr_in client;
    socklen_t clientSize;
    char host[NI_MAXHOST];
    char svc[NI_MAXSERV];

    int clientSocket = accept(listening, (sockaddr *)&client, &clientSize);

    if (clientSocket == -1)
    {
        cerr << "Problem with client connecting";
        return -4;
    }

    // Close the listening socket

    close(listening);

    memset(host, 0, NI_MAXHOST);
    memset(svc, 0, NI_MAXSERV);

    int result = getnameinfo((sockaddr *)&client, sizeof(client), host, NI_MAXHOST, svc, NI_MAXSERV, 0);

    if (result)
    {
        cout << host << "connected on" << svc << endl;
    }
    else
    {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        cout << host << "connected on" << ntohs(client.sin_port) << endl;
    }

    // While receiving - display message
    char buf[4096];
    while (true)
    {
        //Clear the buffer
        memset(buf, 0, 4096);
        // Wait for a message
        int bytesRecv = recv(clientSocket, buf, 4096, 0);
        
        if (bytesRecv==-1)
        {
            cerr << "There was a conection issue" << endl;
            break;
        }
        if (bytesRecv==0)
        {
            cerr << "The client disconnected" << endl;
            break;
        }

        // Display Message
        cout << "Recieved: " << string(buf, 0, bytesRecv) << endl;

        // Resend Message
        send(clientSocket, buf, bytesRecv + 1, 0);
    }

    // Close socket
    close(clientSocket);

    return 0;
}
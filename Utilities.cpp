#include "Utilities.hpp"

using namespace std;

// SHA1 utilities

// Calculates the node and key identifier truncated to sizeof(ulli)
ulli calculateIdentifier(std::string input) {
    ulli result = 0;
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1((const unsigned char *)input.c_str(), input.size(), hash);
    memcpy(&result, hash, m/8);
    return result;
}

// Network utilities

// sends buffer data of size sendLength using sendersSocket
void sendData(char *buffer, long long int sendLength, int sendersSocket) {
    char * ptrToBuffer = buffer;

    // Send the number of bytes to be sent
    if(send(sendersSocket, &sendLength, sizeof(long long int), 0) == -1) { perror("Error sending size"); exit(1); }

    // Send the data
    long long int bytesSent;
    while(sendLength > 0)
    {
        bytesSent = send(sendersSocket, ptrToBuffer, sendLength*sizeof(char), 0);
        if(bytesSent == -1) { perror("Error sending size"); exit(1); }
        ptrToBuffer += bytesSent;
        sendLength -= bytesSent; 
    }
}

// receives data of size bufferSize from receiversSocket // return the data
char* receiveData(long long int& bufferSize, int receiversSocket) {
    // Receive total bytes to be received
    if(recv(receiversSocket, &bufferSize, sizeof(long long int), 0) == -1) { perror("Error receiving file size"); exit(1); }
    char * bufferStorage = (char*)calloc(bufferSize, sizeof(char));
    
    long long int bytesRecvd, totalBytes = 0;
    char * buffer = bufferStorage;

    // Receive the data
    while(totalBytes < bufferSize)
    {
        bytesRecvd = recv(receiversSocket, bufferStorage, bufferSize-totalBytes, 0);
        if(bytesRecvd == -1){ perror("Error receiving data "); exit(1); }
        bufferStorage += bytesRecvd;
        totalBytes += bytesRecvd;
    }

    return buffer;
}

// Threads

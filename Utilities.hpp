#include <string>
#include <openssl/sha.h>
#include <cstring>
#include <sys/socket.h>

// Extract 64 bits from SHA1
#define m 8

#define ulli unsigned long long int

// SHA1 utilities

// Calculates the node and key identifier truncated to sizeof(ulli)
ulli calculateIdentifier(std::string input);

// Network utilities

// sends buffer data of size sendLength using sendersSocket
void sendData(char *buffer, long long int sendLength, int sendersSocket);

// receives data of size bufferSize from receiversSocket // return the data
char* receiveData(long long int& bufferSize, int receiversSocket);
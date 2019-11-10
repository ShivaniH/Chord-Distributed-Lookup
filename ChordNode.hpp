#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <sys/socket.h>

#define M 63

class ChordNode {

    private:

    std::string IPaddress;
    int portNumber;
    
    std::string nodeIdentifier;     // Obtained using SHA-1        // ISSUE: Make virtual servers or not?
    std::unordered_map<std::string, std::string> keysManaged;    // < keyID, actual key > 

    std::string chordRingID;

    // Each 'subvector' will contain 3 values: (nodeIdentifier, IP, port)
    std::vector<std::vector<std::string>> fingerTable;      // TODO: SET MAXIMUM ENTRIES TO M
    std::vector<std::vector<std::string>> successorList;
    std::vector<std::string> predecessor;

    public:

    /*
    TODO: create(), join(), findSuccessor(), notify(), closestPrecedingNode(), stabilize(), checkPredecessor(), fixFingers()
    
    RUN PERIODICALLY: stabilize(), checkPredecessor(), fixFingers()
    */

    ChordNode()
    {
        // create nodeIdentifier's value by calling calculateSHA1() here
    }

    // NOTE: May have to change return data types wherever required

    void create();

    void join(std::string nodeID);

    std::string findSuccessor(std::string ID);  // Of a key's ID

    std::string closestPrecedingNode(std::string ID);

    void checkPredecessor();

    void fixFingers();

    void stabilize();

    void notify(std::string nodeID);
};
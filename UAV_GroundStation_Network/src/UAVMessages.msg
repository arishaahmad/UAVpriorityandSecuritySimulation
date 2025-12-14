// UAV Message Definitions
// Defines the message types for UAV-Ground Station communication

// Enumeration for message priorities
enum MessagePriority
{
    LOW = 0;
    MEDIUM = 1;
    HIGH = 2;
    CRITICAL = 3;
}

// Enumeration for message types
enum MessageType
{
    DATA = 0;
    ACK = 1;
    NACK = 2;
    HEARTBEAT = 3;
    COMMAND = 4;
}

// Base message class for UAV communications
message UAVMessage
{
    int sourceId;           // UAV or Ground Station ID
    int destId;             // Destination ID
    int sequenceNumber;     // For tracking and acknowledgment
    MessageType msgType;    // Type of message
    MessagePriority priority; // Priority level
    simtime_t timestamp;    // When message was created
    string payload;         // Actual data content (encrypted)
    double xPos;            // Position information
    double yPos;
    double zPos;
    double ndviValue;       // Normalized Difference Vegetation Index (Simulated)
}

// Acknowledgment message
message AckMessage extends UAVMessage
{
    int ackedSeqNum;        // Sequence number being acknowledged
    bool success;           // Whether operation was successful
}

// Timeout self-message for retransmission
message TimeoutMsg extends cMessage
{
    int sequenceNumber;
    int retryCount;
}
#include "GroundStation.h"
#include <string> // Ensure string is included for XOR

Define_Module(GroundStation);

// FIX 1: Definition for simpleXOR (must match declaration in .h)
std::string GroundStation::simpleXOR(const std::string& data, const std::string& key)
{
    std::string output = data;
    for (size_t i = 0; i < data.length(); ++i) {
        output[i] = data[i] ^ key[i % key.length()];
    }
    return output;
}

void GroundStation::initialize()
{
    queueCapacity = par("queueCapacity");
    processingDelay = par("processingDelay");

    // FIX 2: Correctly read encryptionKey into the class member
    encryptionKey = par("encryptionKey").stdstringValue();

    isProcessing = false;

    processingTimer = new cMessage("processingTimer");

    // Register signals
    queueLengthSignal = registerSignal("queueLength");
    messagesProcessedSignal = registerSignal("messagesProcessed");
    messagesDroppedSignal = registerSignal("messagesDropped");
    processingDelaySignal = registerSignal("processingDelay");

    EV << "Ground Station initialized\n";
    EV << "Queue capacity: " << queueCapacity << "\n";
    EV << "Processing delay: " << processingDelay << "s\n";
    EV << "Encryption Key Set: " << encryptionKey << "\n"; // Log key set
}

void GroundStation::handleMessage(cMessage *msg)
{
    if (msg == processingTimer) {
        // Finished processing current message
        isProcessing = false;

        // Process next message if any
        if (!messageQueue.empty()) {
            processNextMessage();
        }
    }
    else {
        // Received message from UAV
        UAVMessage *uavMsg = check_and_cast<UAVMessage*>(msg);

        // Update statistics
        messagesPerUAV[uavMsg->getSourceId()]++;

        if (uavMsg->getMsgType() == HEARTBEAT) {
            // Heartbeats are processed immediately and deleted
            lastHeartbeat[uavMsg->getSourceId()] = simTime();
            delete uavMsg;
        } else {
            enqueueMessage(uavMsg);
        }

        // Start processing if not already busy
        if (!isProcessing && !messageQueue.empty()) {
            processNextMessage();
        }
    }
}

void GroundStation::enqueueMessage(UAVMessage *msg)
{
    if ((int)messageQueue.size() < queueCapacity) {
        messageQueue.push(msg);
        emit(queueLengthSignal, (long)messageQueue.size());
    } else {
        EV << "Ground Station queue full. Dropping message from UAV "
           << msg->getSourceId() << "\n";
        emit(messagesDroppedSignal, 1L);
        delete msg;
    }
}

// FIX 3: Definition for recordProcessingDelay (must match declaration in .h)
void GroundStation::recordProcessingDelay()
{
    emit(processingDelaySignal, processingDelay);
}

void GroundStation::processNextMessage()
{
    UAVMessage *msg = messageQueue.top();
    messageQueue.pop();

    emit(queueLengthSignal, (long)messageQueue.size());

    isProcessing = true;

    // Decrypt the payload
    std::string encryptedPayload = msg->getPayload();
    // FIX 4: Use the simpleXOR and encryptionKey member
    std::string decryptedPayload = simpleXOR(encryptedPayload, encryptionKey);

    // Log the decrypted content and NDVI data
    EV << "Ground Station processing message from UAV "
       << msg->getSourceId() << " (seq=" << msg->getSequenceNumber() << ").\n";
    EV << "Decrypted Payload: " << decryptedPayload << "\n";
    // Assuming NDVI data is available in the message
    EV << "Environmental Data (NDVI): " << msg->getNdviValue() << "\n";

    // Update statistics
    recordProcessingDelay();
    sendAck(msg, true);

    emit(messagesProcessedSignal, 1L);

    // Simulate processing time
    scheduleAt(simTime() + processingDelay, processingTimer);

    delete msg;
}

void GroundStation::sendAck(UAVMessage *msg, bool success)
{
    AckMessage *ack = new AckMessage("ACK");
    ack->setSourceId(0); // Ground station ID
    ack->setDestId(msg->getSourceId());
    ack->setAckedSeqNum(msg->getSequenceNumber());
    ack->setSuccess(success);
    ack->setMsgType(ACK);
    ack->setPriority(msg->getPriority());

    int gateIndex = getGateIndexForUAV(msg->getSourceId());

    if (gateIndex >= 0) {
        send(ack, "wireless$o", gateIndex);
        EV << "Sent ACK to UAV " << msg->getSourceId()
           << " (success=" << success << ")\n";
    } else {
        EV << "Error: Could not find gate for UAV " << msg->getSourceId() << "\n";
        delete ack;
    }
}

int GroundStation::getGateIndexForUAV(int uavId)
{
    // UAV IDs are 1, 2, 3 -> gate indices are 0, 1, 2
    return uavId - 1;
}

void GroundStation::finish()
{
    EV << "\n=== Ground Station Statistics ===\n";
    EV << "Messages per UAV:\n";
    for (auto& pair : messagesPerUAV) {
        EV << "  UAV " << pair.first << ": " << pair.second << "\n";
    }
}

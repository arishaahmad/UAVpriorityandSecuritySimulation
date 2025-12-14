#include "UAV.h"
#include <cmath>

Define_Module(UAV);

// Function to implement simple XOR encryption/decryption
std::string UAV::simpleXOR(const std::string& data, const std::string& key)
{
    std::string output = data;
    for (size_t i = 0; i < data.length(); ++i) {
        output[i] = data[i] ^ key[i % key.length()];
    }
    return output;
}


double UAV::getFloraValue()
{
    // Normalize coordinates (assuming 800x600 canvas)
    double xNorm = xPos / 800.0;
    double yNorm = yPos / 600.0;

    // Create a patterned base value (range 0 to 1)
    double baseValue = (sin(xNorm * 10) * cos(yNorm * 8) + 1.0) / 2.0;

    // Map the result to a plausible NDVI range (e.g., 0.2 to 0.8)
    double ndvi = 0.2 + baseValue * 0.6;

    // Add some random noise
    ndvi += uniform(-0.05, 0.05);

    // Clamp to valid NDVI range [0, 1]
    return fmax(0.0, fmin(1.0, ndvi));
}

void UAV::initialize()
{
    // Read parameters
    uavId = par("uavId");
    missionType = par("missionType").stdstringValue();
    xPos = par("xPos");
    yPos = par("yPos");
    zPos = par("zPos");
    ackTimeout = par("ackTimeout");
    maxRetries = par("maxRetries");

    // Movement parameters
    xVel = par("xVelocity");
    yVel = par("yVelocity");
    simtime_t moveInterval = par("moveInterval");

    // Security parameter
    encryptionKey = par("encryptionKey").stdstringValue();

    sequenceNumber = 0;

    // Register signals...
    messagesSentSignal = registerSignal("messagesSent");
    messagesReceivedSignal = registerSignal("messagesReceived");
    retransmissionsSignal = registerSignal("retransmissions");
    timeoutsSignal = registerSignal("timeouts");

    // Schedule periodic data generation...
    generateDataMsg = new cMessage("generateData");
    scheduleAt(simTime() + uniform(1, 3), generateDataMsg);

    // Schedule periodic heartbeat...
    heartbeatMsg = new cMessage("heartbeat");
    scheduleAt(simTime() + 5.0, heartbeatMsg);

    // Schedule periodic movement...
    moveMsg = new cMessage("moveTimer");
    scheduleAt(simTime() + moveInterval, moveMsg);

    EV << "UAV " << uavId << " initialized at position ("
       << xPos << ", " << yPos << ", " << zPos << ")\n";
    EV << "Mission type: " << missionType << "\n";
    EV << "Encryption Key Set: " << encryptionKey << "\n";
}

void UAV::handleMessage(cMessage *msg)
{
    // ... (self-messages, including movement) ...
    if (msg->isSelfMessage()) {
        simtime_t moveInterval = par("moveInterval");

        if (msg == generateDataMsg) {
            sendDataToGroundStation();
            scheduleAt(simTime() + uniform(2, 5), generateDataMsg);
        }
        else if (msg == heartbeatMsg) {
            sendHeartbeat();
            scheduleAt(simTime() + 10.0, heartbeatMsg);
        }
        else if (msg == moveMsg) {
            updatePosition();
            scheduleAt(simTime() + moveInterval, moveMsg);
        }
        else if (auto *timeout = dynamic_cast<TimeoutMsg*>(msg)) {
            handleTimeout(timeout);
        }
        else {
            delete msg;
        }
        return;
    }
    // ... (received message and ACK logic) ...
    if (auto *ack = dynamic_cast<AckMessage*>(msg)) {
        handleAck(ack);
        return;
    }

    // UAV data / other messages
    UAVMessage *uavMsg = check_and_cast<UAVMessage*>(msg);

    // Heartbeats are unencrypted for simple logging
    if (uavMsg->getMsgType() == HEARTBEAT) {
        EV << "UAV " << uavId << " received HEARTBEAT from UAV " << uavMsg->getSourceId() << "\n";
    } else {
        EV << "UAV " << uavId << " received encrypted message.\n";
    }

    emit(messagesReceivedSignal, 1L);

    // Send acknowledgment...
    AckMessage *ackMsg = new AckMessage("ACK");
    ackMsg->setSourceId(uavId);
    ackMsg->setDestId(uavMsg->getSourceId());
    ackMsg->setAckedSeqNum(uavMsg->getSequenceNumber());
    ackMsg->setSuccess(true);
    ackMsg->setMsgType(ACK);

    send(ackMsg, "wireless$o");

    delete uavMsg;
}

void UAV::sendDataToGroundStation()
{
    UAVMessage *msg = new UAVMessage("DATA");
    msg->setSourceId(uavId);
    msg->setDestId(0); // Ground station ID = 0
    msg->setSequenceNumber(sequenceNumber);
    msg->setMsgType(DATA);
    msg->setPriority(getPriorityForMission());
    msg->setTimestamp(simTime());

    // Calculate and set NDVI value
    double currentNDVI = getFloraValue();
    msg->setNdviValue(currentNDVI);

    // Prepare verbose payload string (before encryption)
    char payload[250];
    sprintf(payload,
            "UAV%d [%s]: Seq=%d, Pos=(%.1f,%.1f,%.1f), NDVI=%.3f, Time=%.2f",
            uavId, missionType.c_str(), sequenceNumber,
            xPos, yPos, zPos, currentNDVI, simTime().dbl());

    // Encrypt the payload (NEW)
    std::string originalPayload(payload);
    std::string encryptedPayload = simpleXOR(originalPayload, encryptionKey);
    msg->setPayload(encryptedPayload.c_str());

    msg->setXPos(xPos);
    msg->setYPos(yPos);
    msg->setZPos(zPos);

    pendingAcks[sequenceNumber] = msg->dup();
    retryCount[sequenceNumber] = 0;

    EV << "UAV " << uavId << " sending ENCRYPTED data (seq=" << sequenceNumber << ") with NDVI= " << currentNDVI << "\n";

    send(msg, "wireless$o");
    emit(messagesSentSignal, 1L);

    scheduleTimeout(sequenceNumber);
    sequenceNumber++;
}

void UAV::sendHeartbeat()
{
    // Heartbeats are sent unencrypted for simplicity in logging
    UAVMessage *msg = new UAVMessage("HEARTBEAT");
    msg->setSourceId(uavId);
    msg->setDestId(0);
    msg->setSequenceNumber(sequenceNumber++);
    msg->setMsgType(HEARTBEAT);
    msg->setPriority(LOW);
    msg->setTimestamp(simTime());
    msg->setPayload("Heartbeat");
    msg->setNdviValue(0.0); // No NDVI data for heartbeat
    msg->setXPos(xPos);
    msg->setYPos(yPos);
    msg->setZPos(zPos);

    send(msg, "wireless$o");
    EV << "UAV " << uavId << " sent heartbeat\n";
}

void UAV::scheduleTimeout(int seqNum)
{
    TimeoutMsg *timeout = new TimeoutMsg("timeout");
    timeout->setSequenceNumber(seqNum);
    timeout->setRetryCount(retryCount[seqNum]);
    scheduleAt(simTime() + ackTimeout, timeout);
}

void UAV::handleTimeout(TimeoutMsg *timeoutMsg)
{
    int seqNum = timeoutMsg->getSequenceNumber();

    if (pendingAcks.find(seqNum) == pendingAcks.end()) {
        delete timeoutMsg;
        return;
    }

    emit(timeoutsSignal, 1L);
    retryCount[seqNum]++;

    if (retryCount[seqNum] < maxRetries) {
        EV << "UAV " << uavId << " timeout for seq=" << seqNum << "\n";

        UAVMessage *original = pendingAcks[seqNum];
        UAVMessage *retransmit = original->dup();

        // The retransmit message will already contain the encrypted payload
        send(retransmit, "wireless$o");
        emit(retransmissionsSignal, 1L);

        scheduleTimeout(seqNum);
    }
    else {
        delete pendingAcks[seqNum];
        pendingAcks.erase(seqNum);
        retryCount.erase(seqNum);
        EV << "UAV " << uavId << " dropped message seq=" << seqNum << " after max retries.\n";
    }

    delete timeoutMsg;
}

void UAV::handleAck(AckMessage *ack)
{
    int ackedSeq = ack->getAckedSeqNum();

    double lossRate = 0.02;
    if (hasPar("ackLossRate")) {
        lossRate = par("ackLossRate");
    }

    if (uniform(0, 1) < lossRate) {
        EV << "UAV " << uavId << " simulating ACK loss for seq=" << ackedSeq << "\n";
        delete ack;
        return;
    }

    if (pendingAcks.find(ackedSeq) != pendingAcks.end()) {
        delete pendingAcks[ackedSeq];
        pendingAcks.erase(ackedSeq);
        retryCount.erase(ackedSeq);
        EV << "UAV " << uavId << " ACK received for seq=" << ackedSeq << "\n";
    }

    delete ack;
}

MessagePriority UAV::getPriorityForMission()
{
    if (missionType == "emergency") return CRITICAL;
    if (missionType == "delivery")  return HIGH;
    if (missionType == "surveillance") return MEDIUM;
    return LOW;
}

double UAV::calculateDistance(double x1, double y1, double z1,
                              double x2, double y2, double z2)
{
    return sqrt(pow(x2-x1, 2) + pow(y2-y1, 2) + pow(z2-z1, 2));
}

// Function to update UAV position (mobility logic)
void UAV::updatePosition()
{
    simtime_t moveInterval = par("moveInterval");
    double dt = moveInterval.dbl();

    xPos += xVel * dt;
    yPos += yVel * dt;

    // Boundary conditions
    if (xPos > 700 || xPos < 100) {
        xVel *= -1;
        xPos = (xPos > 700) ? 700 : 100;
    }
    if (yPos > 500 || yPos < 100) {
        yVel *= -1;
        yPos = (yPos > 500) ? 500 : 100;
    }

    // Update display
    cDisplayString& display = getDisplayString();
    char posStr[100];
    sprintf(posStr, "p=%f,%f", xPos, yPos);
    display.set(posStr);

    EV << "UAV " << uavId << " moved to (" << xPos << ", " << yPos << ")\n";
}


void UAV::finish()
{
    cancelAndDelete(generateDataMsg);
    cancelAndDelete(heartbeatMsg);
    cancelAndDelete(moveMsg);

    for (auto &p : pendingAcks) {
        delete p.second;
    }
}

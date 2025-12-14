//
// Generated file, do not edit! Created by opp_msgtool 6.0 from src/UAVMessages.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "UAVMessages_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

Register_Enum(MessagePriority, (MessagePriority::LOW, MessagePriority::MEDIUM, MessagePriority::HIGH, MessagePriority::CRITICAL));

Register_Enum(MessageType, (MessageType::DATA, MessageType::ACK, MessageType::NACK, MessageType::HEARTBEAT, MessageType::COMMAND));

Register_Class(UAVMessage)

UAVMessage::UAVMessage(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

UAVMessage::UAVMessage(const UAVMessage& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

UAVMessage::~UAVMessage()
{
}

UAVMessage& UAVMessage::operator=(const UAVMessage& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void UAVMessage::copy(const UAVMessage& other)
{
    this->sourceId = other.sourceId;
    this->destId = other.destId;
    this->sequenceNumber = other.sequenceNumber;
    this->msgType = other.msgType;
    this->priority = other.priority;
    this->timestamp = other.timestamp;
    this->payload = other.payload;
    this->xPos = other.xPos;
    this->yPos = other.yPos;
    this->zPos = other.zPos;
    this->ndviValue = other.ndviValue;
}

void UAVMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->sourceId);
    doParsimPacking(b,this->destId);
    doParsimPacking(b,this->sequenceNumber);
    doParsimPacking(b,this->msgType);
    doParsimPacking(b,this->priority);
    doParsimPacking(b,this->timestamp);
    doParsimPacking(b,this->payload);
    doParsimPacking(b,this->xPos);
    doParsimPacking(b,this->yPos);
    doParsimPacking(b,this->zPos);
    doParsimPacking(b,this->ndviValue);
}

void UAVMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->sourceId);
    doParsimUnpacking(b,this->destId);
    doParsimUnpacking(b,this->sequenceNumber);
    doParsimUnpacking(b,this->msgType);
    doParsimUnpacking(b,this->priority);
    doParsimUnpacking(b,this->timestamp);
    doParsimUnpacking(b,this->payload);
    doParsimUnpacking(b,this->xPos);
    doParsimUnpacking(b,this->yPos);
    doParsimUnpacking(b,this->zPos);
    doParsimUnpacking(b,this->ndviValue);
}

int UAVMessage::getSourceId() const
{
    return this->sourceId;
}

void UAVMessage::setSourceId(int sourceId)
{
    this->sourceId = sourceId;
}

int UAVMessage::getDestId() const
{
    return this->destId;
}

void UAVMessage::setDestId(int destId)
{
    this->destId = destId;
}

int UAVMessage::getSequenceNumber() const
{
    return this->sequenceNumber;
}

void UAVMessage::setSequenceNumber(int sequenceNumber)
{
    this->sequenceNumber = sequenceNumber;
}

MessageType UAVMessage::getMsgType() const
{
    return this->msgType;
}

void UAVMessage::setMsgType(MessageType msgType)
{
    this->msgType = msgType;
}

MessagePriority UAVMessage::getPriority() const
{
    return this->priority;
}

void UAVMessage::setPriority(MessagePriority priority)
{
    this->priority = priority;
}

omnetpp::simtime_t UAVMessage::getTimestamp() const
{
    return this->timestamp;
}

void UAVMessage::setTimestamp(omnetpp::simtime_t timestamp)
{
    this->timestamp = timestamp;
}

const char * UAVMessage::getPayload() const
{
    return this->payload.c_str();
}

void UAVMessage::setPayload(const char * payload)
{
    this->payload = payload;
}

double UAVMessage::getXPos() const
{
    return this->xPos;
}

void UAVMessage::setXPos(double xPos)
{
    this->xPos = xPos;
}

double UAVMessage::getYPos() const
{
    return this->yPos;
}

void UAVMessage::setYPos(double yPos)
{
    this->yPos = yPos;
}

double UAVMessage::getZPos() const
{
    return this->zPos;
}

void UAVMessage::setZPos(double zPos)
{
    this->zPos = zPos;
}

double UAVMessage::getNdviValue() const
{
    return this->ndviValue;
}

void UAVMessage::setNdviValue(double ndviValue)
{
    this->ndviValue = ndviValue;
}

class UAVMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_sourceId,
        FIELD_destId,
        FIELD_sequenceNumber,
        FIELD_msgType,
        FIELD_priority,
        FIELD_timestamp,
        FIELD_payload,
        FIELD_xPos,
        FIELD_yPos,
        FIELD_zPos,
        FIELD_ndviValue,
    };
  public:
    UAVMessageDescriptor();
    virtual ~UAVMessageDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(UAVMessageDescriptor)

UAVMessageDescriptor::UAVMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(UAVMessage)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

UAVMessageDescriptor::~UAVMessageDescriptor()
{
    delete[] propertyNames;
}

bool UAVMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<UAVMessage *>(obj)!=nullptr;
}

const char **UAVMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *UAVMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int UAVMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 11+base->getFieldCount() : 11;
}

unsigned int UAVMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_sourceId
        FD_ISEDITABLE,    // FIELD_destId
        FD_ISEDITABLE,    // FIELD_sequenceNumber
        0,    // FIELD_msgType
        0,    // FIELD_priority
        FD_ISEDITABLE,    // FIELD_timestamp
        FD_ISEDITABLE,    // FIELD_payload
        FD_ISEDITABLE,    // FIELD_xPos
        FD_ISEDITABLE,    // FIELD_yPos
        FD_ISEDITABLE,    // FIELD_zPos
        FD_ISEDITABLE,    // FIELD_ndviValue
    };
    return (field >= 0 && field < 11) ? fieldTypeFlags[field] : 0;
}

const char *UAVMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "sourceId",
        "destId",
        "sequenceNumber",
        "msgType",
        "priority",
        "timestamp",
        "payload",
        "xPos",
        "yPos",
        "zPos",
        "ndviValue",
    };
    return (field >= 0 && field < 11) ? fieldNames[field] : nullptr;
}

int UAVMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "sourceId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "destId") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "sequenceNumber") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "msgType") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "priority") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "timestamp") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "payload") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "xPos") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "yPos") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "zPos") == 0) return baseIndex + 9;
    if (strcmp(fieldName, "ndviValue") == 0) return baseIndex + 10;
    return base ? base->findField(fieldName) : -1;
}

const char *UAVMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_sourceId
        "int",    // FIELD_destId
        "int",    // FIELD_sequenceNumber
        "MessageType",    // FIELD_msgType
        "MessagePriority",    // FIELD_priority
        "omnetpp::simtime_t",    // FIELD_timestamp
        "string",    // FIELD_payload
        "double",    // FIELD_xPos
        "double",    // FIELD_yPos
        "double",    // FIELD_zPos
        "double",    // FIELD_ndviValue
    };
    return (field >= 0 && field < 11) ? fieldTypeStrings[field] : nullptr;
}

const char **UAVMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_msgType: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        case FIELD_priority: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *UAVMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_msgType:
            if (!strcmp(propertyName, "enum")) return "MessageType";
            return nullptr;
        case FIELD_priority:
            if (!strcmp(propertyName, "enum")) return "MessagePriority";
            return nullptr;
        default: return nullptr;
    }
}

int UAVMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    UAVMessage *pp = omnetpp::fromAnyPtr<UAVMessage>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void UAVMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    UAVMessage *pp = omnetpp::fromAnyPtr<UAVMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'UAVMessage'", field);
    }
}

const char *UAVMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    UAVMessage *pp = omnetpp::fromAnyPtr<UAVMessage>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string UAVMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    UAVMessage *pp = omnetpp::fromAnyPtr<UAVMessage>(object); (void)pp;
    switch (field) {
        case FIELD_sourceId: return long2string(pp->getSourceId());
        case FIELD_destId: return long2string(pp->getDestId());
        case FIELD_sequenceNumber: return long2string(pp->getSequenceNumber());
        case FIELD_msgType: return enum2string(pp->getMsgType(), "MessageType");
        case FIELD_priority: return enum2string(pp->getPriority(), "MessagePriority");
        case FIELD_timestamp: return simtime2string(pp->getTimestamp());
        case FIELD_payload: return oppstring2string(pp->getPayload());
        case FIELD_xPos: return double2string(pp->getXPos());
        case FIELD_yPos: return double2string(pp->getYPos());
        case FIELD_zPos: return double2string(pp->getZPos());
        case FIELD_ndviValue: return double2string(pp->getNdviValue());
        default: return "";
    }
}

void UAVMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UAVMessage *pp = omnetpp::fromAnyPtr<UAVMessage>(object); (void)pp;
    switch (field) {
        case FIELD_sourceId: pp->setSourceId(string2long(value)); break;
        case FIELD_destId: pp->setDestId(string2long(value)); break;
        case FIELD_sequenceNumber: pp->setSequenceNumber(string2long(value)); break;
        case FIELD_timestamp: pp->setTimestamp(string2simtime(value)); break;
        case FIELD_payload: pp->setPayload((value)); break;
        case FIELD_xPos: pp->setXPos(string2double(value)); break;
        case FIELD_yPos: pp->setYPos(string2double(value)); break;
        case FIELD_zPos: pp->setZPos(string2double(value)); break;
        case FIELD_ndviValue: pp->setNdviValue(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UAVMessage'", field);
    }
}

omnetpp::cValue UAVMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    UAVMessage *pp = omnetpp::fromAnyPtr<UAVMessage>(object); (void)pp;
    switch (field) {
        case FIELD_sourceId: return pp->getSourceId();
        case FIELD_destId: return pp->getDestId();
        case FIELD_sequenceNumber: return pp->getSequenceNumber();
        case FIELD_msgType: return static_cast<int>(pp->getMsgType());
        case FIELD_priority: return static_cast<int>(pp->getPriority());
        case FIELD_timestamp: return pp->getTimestamp().dbl();
        case FIELD_payload: return pp->getPayload();
        case FIELD_xPos: return pp->getXPos();
        case FIELD_yPos: return pp->getYPos();
        case FIELD_zPos: return pp->getZPos();
        case FIELD_ndviValue: return pp->getNdviValue();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'UAVMessage' as cValue -- field index out of range?", field);
    }
}

void UAVMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    UAVMessage *pp = omnetpp::fromAnyPtr<UAVMessage>(object); (void)pp;
    switch (field) {
        case FIELD_sourceId: pp->setSourceId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_destId: pp->setDestId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_sequenceNumber: pp->setSequenceNumber(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_timestamp: pp->setTimestamp(value.doubleValue()); break;
        case FIELD_payload: pp->setPayload(value.stringValue()); break;
        case FIELD_xPos: pp->setXPos(value.doubleValue()); break;
        case FIELD_yPos: pp->setYPos(value.doubleValue()); break;
        case FIELD_zPos: pp->setZPos(value.doubleValue()); break;
        case FIELD_ndviValue: pp->setNdviValue(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UAVMessage'", field);
    }
}

const char *UAVMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr UAVMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    UAVMessage *pp = omnetpp::fromAnyPtr<UAVMessage>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void UAVMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    UAVMessage *pp = omnetpp::fromAnyPtr<UAVMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'UAVMessage'", field);
    }
}

Register_Class(AckMessage)

AckMessage::AckMessage(const char *name, short kind) : ::UAVMessage(name, kind)
{
}

AckMessage::AckMessage(const AckMessage& other) : ::UAVMessage(other)
{
    copy(other);
}

AckMessage::~AckMessage()
{
}

AckMessage& AckMessage::operator=(const AckMessage& other)
{
    if (this == &other) return *this;
    ::UAVMessage::operator=(other);
    copy(other);
    return *this;
}

void AckMessage::copy(const AckMessage& other)
{
    this->ackedSeqNum = other.ackedSeqNum;
    this->success = other.success;
}

void AckMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::UAVMessage::parsimPack(b);
    doParsimPacking(b,this->ackedSeqNum);
    doParsimPacking(b,this->success);
}

void AckMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::UAVMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->ackedSeqNum);
    doParsimUnpacking(b,this->success);
}

int AckMessage::getAckedSeqNum() const
{
    return this->ackedSeqNum;
}

void AckMessage::setAckedSeqNum(int ackedSeqNum)
{
    this->ackedSeqNum = ackedSeqNum;
}

bool AckMessage::getSuccess() const
{
    return this->success;
}

void AckMessage::setSuccess(bool success)
{
    this->success = success;
}

class AckMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_ackedSeqNum,
        FIELD_success,
    };
  public:
    AckMessageDescriptor();
    virtual ~AckMessageDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(AckMessageDescriptor)

AckMessageDescriptor::AckMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(AckMessage)), "UAVMessage")
{
    propertyNames = nullptr;
}

AckMessageDescriptor::~AckMessageDescriptor()
{
    delete[] propertyNames;
}

bool AckMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<AckMessage *>(obj)!=nullptr;
}

const char **AckMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *AckMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int AckMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int AckMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_ackedSeqNum
        FD_ISEDITABLE,    // FIELD_success
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *AckMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "ackedSeqNum",
        "success",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int AckMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "ackedSeqNum") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "success") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *AckMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_ackedSeqNum
        "bool",    // FIELD_success
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **AckMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *AckMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int AckMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    AckMessage *pp = omnetpp::fromAnyPtr<AckMessage>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void AckMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    AckMessage *pp = omnetpp::fromAnyPtr<AckMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'AckMessage'", field);
    }
}

const char *AckMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    AckMessage *pp = omnetpp::fromAnyPtr<AckMessage>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string AckMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    AckMessage *pp = omnetpp::fromAnyPtr<AckMessage>(object); (void)pp;
    switch (field) {
        case FIELD_ackedSeqNum: return long2string(pp->getAckedSeqNum());
        case FIELD_success: return bool2string(pp->getSuccess());
        default: return "";
    }
}

void AckMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    AckMessage *pp = omnetpp::fromAnyPtr<AckMessage>(object); (void)pp;
    switch (field) {
        case FIELD_ackedSeqNum: pp->setAckedSeqNum(string2long(value)); break;
        case FIELD_success: pp->setSuccess(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'AckMessage'", field);
    }
}

omnetpp::cValue AckMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    AckMessage *pp = omnetpp::fromAnyPtr<AckMessage>(object); (void)pp;
    switch (field) {
        case FIELD_ackedSeqNum: return pp->getAckedSeqNum();
        case FIELD_success: return pp->getSuccess();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'AckMessage' as cValue -- field index out of range?", field);
    }
}

void AckMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    AckMessage *pp = omnetpp::fromAnyPtr<AckMessage>(object); (void)pp;
    switch (field) {
        case FIELD_ackedSeqNum: pp->setAckedSeqNum(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_success: pp->setSuccess(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'AckMessage'", field);
    }
}

const char *AckMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr AckMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    AckMessage *pp = omnetpp::fromAnyPtr<AckMessage>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void AckMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    AckMessage *pp = omnetpp::fromAnyPtr<AckMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'AckMessage'", field);
    }
}

Register_Class(TimeoutMsg)

TimeoutMsg::TimeoutMsg(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

TimeoutMsg::TimeoutMsg(const TimeoutMsg& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

TimeoutMsg::~TimeoutMsg()
{
}

TimeoutMsg& TimeoutMsg::operator=(const TimeoutMsg& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void TimeoutMsg::copy(const TimeoutMsg& other)
{
    this->sequenceNumber = other.sequenceNumber;
    this->retryCount = other.retryCount;
}

void TimeoutMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->sequenceNumber);
    doParsimPacking(b,this->retryCount);
}

void TimeoutMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->sequenceNumber);
    doParsimUnpacking(b,this->retryCount);
}

int TimeoutMsg::getSequenceNumber() const
{
    return this->sequenceNumber;
}

void TimeoutMsg::setSequenceNumber(int sequenceNumber)
{
    this->sequenceNumber = sequenceNumber;
}

int TimeoutMsg::getRetryCount() const
{
    return this->retryCount;
}

void TimeoutMsg::setRetryCount(int retryCount)
{
    this->retryCount = retryCount;
}

class TimeoutMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_sequenceNumber,
        FIELD_retryCount,
    };
  public:
    TimeoutMsgDescriptor();
    virtual ~TimeoutMsgDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(TimeoutMsgDescriptor)

TimeoutMsgDescriptor::TimeoutMsgDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(TimeoutMsg)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

TimeoutMsgDescriptor::~TimeoutMsgDescriptor()
{
    delete[] propertyNames;
}

bool TimeoutMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TimeoutMsg *>(obj)!=nullptr;
}

const char **TimeoutMsgDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TimeoutMsgDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TimeoutMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int TimeoutMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_sequenceNumber
        FD_ISEDITABLE,    // FIELD_retryCount
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *TimeoutMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "sequenceNumber",
        "retryCount",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int TimeoutMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "sequenceNumber") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "retryCount") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *TimeoutMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_sequenceNumber
        "int",    // FIELD_retryCount
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **TimeoutMsgDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *TimeoutMsgDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int TimeoutMsgDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TimeoutMsg *pp = omnetpp::fromAnyPtr<TimeoutMsg>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void TimeoutMsgDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TimeoutMsg *pp = omnetpp::fromAnyPtr<TimeoutMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TimeoutMsg'", field);
    }
}

const char *TimeoutMsgDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TimeoutMsg *pp = omnetpp::fromAnyPtr<TimeoutMsg>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TimeoutMsgDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TimeoutMsg *pp = omnetpp::fromAnyPtr<TimeoutMsg>(object); (void)pp;
    switch (field) {
        case FIELD_sequenceNumber: return long2string(pp->getSequenceNumber());
        case FIELD_retryCount: return long2string(pp->getRetryCount());
        default: return "";
    }
}

void TimeoutMsgDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TimeoutMsg *pp = omnetpp::fromAnyPtr<TimeoutMsg>(object); (void)pp;
    switch (field) {
        case FIELD_sequenceNumber: pp->setSequenceNumber(string2long(value)); break;
        case FIELD_retryCount: pp->setRetryCount(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TimeoutMsg'", field);
    }
}

omnetpp::cValue TimeoutMsgDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TimeoutMsg *pp = omnetpp::fromAnyPtr<TimeoutMsg>(object); (void)pp;
    switch (field) {
        case FIELD_sequenceNumber: return pp->getSequenceNumber();
        case FIELD_retryCount: return pp->getRetryCount();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TimeoutMsg' as cValue -- field index out of range?", field);
    }
}

void TimeoutMsgDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TimeoutMsg *pp = omnetpp::fromAnyPtr<TimeoutMsg>(object); (void)pp;
    switch (field) {
        case FIELD_sequenceNumber: pp->setSequenceNumber(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_retryCount: pp->setRetryCount(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TimeoutMsg'", field);
    }
}

const char *TimeoutMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr TimeoutMsgDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TimeoutMsg *pp = omnetpp::fromAnyPtr<TimeoutMsg>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TimeoutMsgDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TimeoutMsg *pp = omnetpp::fromAnyPtr<TimeoutMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TimeoutMsg'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp


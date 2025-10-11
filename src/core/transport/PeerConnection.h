#pragma once
#include "MessageTransport.h"
#include "ChallengeGenerator.h"
#include "Screen.h"
#include "AuthMessageEncoder.h"
#include "core/transport/model/Challenge.h"
#include "core/transport/model/Message.h"
#include "core/transport/model/AuthRequestMessage.h"

class PeerConnection {
public:
    PeerConnection(ChallengeGenerator* challengeGenerator, 
                  MessageTransport& transport, 
                  Screen& screen,
                  AuthMessageEncoder& encoder);
    
    void onDeviceConnected(const std::string& deviceAddress);
    
private:
    ChallengeGenerator* challengeGenerator;
    MessageTransport* transport;
    Screen* screen;
    AuthMessageEncoder* encoder;
};

#include "MockCommonIDGenerator.h"

MockCommonIDGenerator::MockCommonIDGenerator() 
    : currentIndex(0), generateCallCount(0) {
}

std::string MockCommonIDGenerator::generate() {
    generateCallCount++;
    
    if (currentIndex < scheduledIDs.size()) {
        return scheduledIDs[currentIndex++];
    }
    
    // Fallback si pas d'ID programmé
    return "mock-id-" + std::to_string(generateCallCount);
}

void MockCommonIDGenerator::scheduleID(const std::string& id) {
    scheduledIDs.push_back(id);
}

bool MockCommonIDGenerator::wasGenerateCalled() const {
    return generateCallCount > 0;
}

int MockCommonIDGenerator::getGenerateCallCount() const {
    return generateCallCount;
}


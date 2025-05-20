#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <string>
#include <unordered_map>

const int MMR_TOLERANCE = 100;

struct Player {  // Player
    std::string id;
    int mmr;
};

std::unordered_map<std::string, int> MMRDatabase = {  // MMRDatabase
    {"playhunjin", 1500},
    {"dalbicnaseoseu", 1600},
    {"bigwookiee", 1550},
    {"kana9451", 1400},
    {"enville", 1600}
};

std::vector<std::string> matchQueue;  // MatchQueue

std::vector<std::string> requestOrder = {
    {"playhunjin"},
    {"dalbicnaseoseu"},
    {"bigwookiee"},
    {"kana9451"},
    {"enville"}
};

int getMMR(const std::string& id) {
    return MMRDatabase[id];
}

std::string matchmakingSystem(const std::string& id) {  // MatchmakingSystem
    int bestDiff = std::numeric_limits<int>::max();
    int bestMatchIndex = -1;

    if (std::find(matchQueue.begin(), matchQueue.end(), id) != matchQueue.end()) {
        return "";
    }

    for (int i = 0; i < matchQueue.size(); ++i) {
        std::string currentPlayer = matchQueue[i];
        int diff = std::abs(getMMR(currentPlayer) - getMMR(id));
        if (diff <= MMR_TOLERANCE && diff < bestDiff) {
            bestDiff = diff;
            bestMatchIndex = i;
        }
    }

    if (bestMatchIndex != -1) {
        std::string matchedPlayer = matchQueue[bestMatchIndex];
        matchQueue.erase(matchQueue.begin() + bestMatchIndex);
        return matchedPlayer;
    }
    else {
        matchQueue.push_back(id);
        return "";
    }
}

void matchmakingRequest(const std::string& playerID) {
    int mmr = getMMR(playerID);
    std::cout << "플레이어 " << playerID
        << " (MMR: " << mmr
        << ")가 매치 요청을 보냅니다.\n";

    std::string opponentID = matchmakingSystem(playerID);

    if (!opponentID.empty()) {
        int opponentMMR = getMMR(opponentID);
        std::cout << " → 매칭 성공! 상대는 플레이어 " << opponentID
            << " (MMR: " << opponentMMR << ")\n";
    }
    else {
        std::cout << " → 매칭 실패: 유사한 MMR의 플레이어를 찾을 수 없습니다. 매칭 대기열에 등록되었습니다.\n";
    }
}

int main() {
    for (int i = 0; i < requestOrder.size(); ++i) {
        matchmakingRequest(requestOrder[i]);
        std::cout << std::endl;
    }
    return 0;
}
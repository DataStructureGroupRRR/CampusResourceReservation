#include "Resource.h"

using namespace std;

Resource::Resource(const string& room, const string& name, const string& type, bool available) {
    roomNum = room;
    resName = name;
    resType = type;
    isAvailable = available;
}

string Resource::GetRoomNumber() {
    return roomNum;
}

string Resource::GetResourceName() {
    return resName;
}

string Resource::GetResourceType() {
    return resType;
}

bool Resource::IsAvailable() {
    return isAvailable;
}

void Resource::SetAvailable(bool a) {
    isAvailable = a;
}
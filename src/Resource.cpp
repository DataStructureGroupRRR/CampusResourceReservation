#include "Resource.h"

using namespace std;

Resource::Resource(const string& id, const string& name, const string& type, bool available) {
    this->id = id;
    this->name = name;
    this->type = type;
    this->isAvailable = available;
}

string Resource::GetId() const {
    return id;
}

string Resource::GetName() const {
    return name;
}

string Resource::GetType() const {
    return type;
}

bool Resource::IsAvailable() const {
    return isAvailable;
}

void Resource::SetAvailable(bool a) {
    isAvailable = a;
}
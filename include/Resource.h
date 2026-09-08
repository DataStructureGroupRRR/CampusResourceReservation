#include <string>

class Resource {
    public:
        Resource(const std::string& room, const std::string& name, const std::string& type, bool available);

        std::string GetRoomNumber();
        std::string GetResourceName();
        std::string GetResourceType();
        bool IsAvailable();

        void SetAvailable(bool a);
    private:
        std::string roomNum;
        std::string resName;
        std::string resType;
        bool isAvailable;
};
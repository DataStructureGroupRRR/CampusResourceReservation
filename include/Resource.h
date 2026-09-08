#include <string>

class Resource {
    public:
        Resource(const std::string& id, const std::string& name, const std::string& type, bool available);

        std::string GetId() const;
        std::string GetName() const;
        std::string GetType() const;
        bool IsAvailable() const;

        void SetAvailable(bool a);
    private:
        std::string id;
        std::string name;
        std::string type;
        bool isAvailable;
};
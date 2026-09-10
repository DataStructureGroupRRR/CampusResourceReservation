#include <string>

class Reservation {
    public:
        Reservation(
            const std::string& id, 
            const std::string& studId, 
            const std::string& studName, 
            const std::string& resId, 
            const std::string& date
        );

        std::string GetId() const;
        std::string GetStudentId() const;
        std::string GetStudentName() const;
        std::string GetResourceId() const;
        std::string GetDate() const;
    private:
        std::string id;
        std::string studId;
        std::string studName;
        std::string resId;
        std::string date;
};
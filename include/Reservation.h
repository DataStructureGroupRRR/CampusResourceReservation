#include <string>

class Reservation {
    public:
        Reservation(
            int id, 
            int studId, 
            const std::string& studName, 
            const std::string& resId, 
            const std::string& date
        );

        int GetId() const;
        int GetStudentId() const;
        std::string GetStudentName() const;
        std::string GetResourceId() const;
        std::string GetDate() const;
    private:
        int id;
        int studId;
        std::string studName;
        std::string resId;
        std::string date;
};
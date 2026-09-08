cmake_minimum_required(VERSION 3.10)
project(CampusResourceReservation)

set(SOURCE_FILES
    "src/main.cpp"
    # "src/Resource.cpp"
    # "src/Reservation.cpp"
    # "src/ReservationManager.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
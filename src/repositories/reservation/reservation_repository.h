#pragma once

#include <vector>
#include <string>
#include "models/reservation/reservation.h"

using std::vector;
using std::string;

class ReservationRepository {
public:
    static Reservation createReservation(
        int customerId,
        int tableId,
        string startDateTime,
        string endDateTime,
        string notes,
        bool active);

    static vector<Reservation> findAll();
    static Reservation findById(int id);

    static Reservation updateReservation(
        int id,
        int customerId,
        int tableId,
        string startDateTime,
        string endDateTime,
        string notes,
        bool active);

    static void deleteReservation(int id);

private:
    static vector<Reservation> reservations;
    static int nextId;
};

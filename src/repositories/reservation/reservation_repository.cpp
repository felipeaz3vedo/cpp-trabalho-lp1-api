#include "repositories/reservation/reservation_repository.h"
#include "shared/exceptions/not_found_exception.h"

vector<Reservation> ReservationRepository::reservations = {};
int ReservationRepository::nextId = 1;

Reservation ReservationRepository::createReservation(
    int customerId,
    int tableId,
    string startDateTime,
    string endDateTime,
    string notes,
    bool active)
{
    Reservation reservation(
        nextId,
        customerId,
        tableId,
        startDateTime,
        endDateTime,
        notes,
        active);

    reservations.push_back(reservation);
    nextId++;
    return reservation;
}

vector<Reservation> ReservationRepository::findAll()
{
    return reservations;
}

Reservation ReservationRepository::findById(int id)
{
    for (Reservation r : reservations)
    {
        if (r.getId() == id)
        {
            return r;
        }
    }

    throw NotFoundException("Reservation not found.");
}

Reservation ReservationRepository::updateReservation(
    int id,
    int customerId,
    int tableId,
    string startDateTime,
    string endDateTime,
    string notes,
    bool active)
{
    for (Reservation& r : reservations)
    {
        if (r.getId() == id)
        {
            r.setCustomerId(customerId);
            r.setTableId(tableId);
            r.setStartDateTime(startDateTime);
            r.setEndDateTime(endDateTime);
            r.setNotes(notes);
            r.setActive(active);
            return r;
        }
    }

    throw NotFoundException("Reservation not found.");
}

void ReservationRepository::deleteReservation(int id)
{
    for (Reservation& r : reservations)
    {
        if (r.getId() == id)
        {
            r.setActive(false);
            return;
        }
    }

    throw NotFoundException("Reservation not found.");
}

#include "services/reservation/reservation_service.h"
#include "repositories/reservation/reservation_repository.h"
#include "repositories/user/customer_repository.h"
#include "repositories/table/table_repository.h"
#include "shared/exceptions/validation_exception.h"
#include "shared/exceptions/not_found_exception.h"
#include "shared/exceptions/business_exception.h"

using std::string;
using std::vector;

namespace {

    bool intervalsOverlap(
        const string& existingStartDateTime,
        const string& existingEndDateTime,
        const string& newStartDateTime,
        const string& newEndDateTime)
    {
        return (existingStartDateTime < newEndDateTime) &&
               (newStartDateTime < existingEndDateTime);
    }

    void ensureCustomerExists(int customerId)
    {
        CustomerRepository::findById(customerId);
    }

    void ensureTableExists(int tableId)
    {
        TableRepository::findById(tableId);
    }

    void ensureReservationIsActiveForUpdate(const Reservation& existing)
    {
        if (!existing.isActive())
        {
            throw BusinessException("Reservation is already cancelled and cannot be updated.");
        }
    }

    void ensureReservationIsActiveForDelete(const Reservation& existing)
    {
        if (!existing.isActive())
        {
            throw BusinessException("Reservation is already cancelled.");
        }
    }

    void ensureNoConflictingActiveReservationOnCreate(
        int tableId,
        const string& startDateTime,
        const string& endDateTime)
    {
        vector<Reservation> all = ReservationRepository::findAll();

        for (const Reservation& r : all)
        {
            if (!r.isActive())
            {
                continue;
            }

            if (r.getTableId() != tableId)
            {
                continue;
            }

            if (intervalsOverlap(
                    r.getStartDateTime(),
                    r.getEndDateTime(),
                    startDateTime,
                    endDateTime))
            {
                throw BusinessException(
                    "There is already an active reservation for this table in this time interval.");
            }
        }
    }

    void ensureNoConflictingActiveReservationOnUpdate(
        int reservationId,
        int tableId,
        const string& startDateTime,
        const string& endDateTime)
    {
        vector<Reservation> existentReservations = ReservationRepository::findAll();

        for (const Reservation& r : existentReservations)
        {
            if (r.getId() == reservationId)
            {
                continue;
            }

            if (!r.isActive())
            {
                continue;
            }

            if (r.getTableId() != tableId)
            {
                continue;
            }

            if (intervalsOverlap(
                    r.getStartDateTime(),
                    r.getEndDateTime(),
                    startDateTime,
                    endDateTime))
            {
                throw BusinessException(
                    "There is already an active reservation for this table in this time interval.");
            }
        }
    }
}

Reservation ReservationService::createReservation(
    int customerId,
    int tableId,
    string startDateTime,
    string endDateTime,
    string notes,
    bool active)
{
    ensureCustomerExists(customerId);
    ensureTableExists(tableId);

    if (active)
    {
        ensureNoConflictingActiveReservationOnCreate(
            tableId,
            startDateTime,
            endDateTime);
    }

    return ReservationRepository::createReservation(
        customerId,
        tableId,
        startDateTime,
        endDateTime,
        notes,
        active);
}

vector<Reservation> ReservationService::listReservations()
{
    return ReservationRepository::findAll();
}

Reservation ReservationService::getReservationById(int id)
{
    return ReservationRepository::findById(id);
}

Reservation ReservationService::updateReservation(
    int id,
    int customerId,
    int tableId,
    string startDateTime,
    string endDateTime,
    string notes,
    bool active)
{
    Reservation existing = ReservationRepository::findById(id);

    ensureReservationIsActiveForUpdate(existing);
    ensureCustomerExists(customerId);
    ensureTableExists(tableId);

    if (active)
    {
        ensureNoConflictingActiveReservationOnUpdate(
            id,
            tableId,
            startDateTime,
            endDateTime);
    }

    return ReservationRepository::updateReservation(
        id,
        customerId,
        tableId,
        startDateTime,
        endDateTime,
        notes,
        active);
}

void ReservationService::deleteReservation(int id)
{
    Reservation existing = ReservationRepository::findById(id);

    ensureReservationIsActiveForDelete(existing);

    ReservationRepository::deleteReservation(id);
}

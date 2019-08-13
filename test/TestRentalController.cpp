#include "interface/ICustomer.h"
#include "interface/IRentable.h"

class RentalController {
public:
    void IssueRental(ICustomer& customer,
                     std::unique_ptr<IRentable> rentable,
                     IRentable::clock_time endTime) {
        rentable->RentalStart(std::chrono::system_clock::now());
        rentable->RentalEnd(endTime);
        customer.AssignRental(std::move(rentable));
    }

    struct RentalReturnInfo {
        Money amountOwed;
        std::unique_ptr<IRentable> rental;
    };

    RentalReturnInfo ReturnRental(ICustomer& customer, size_t index) {
        auto rental = customer.RemoveRental(index);
        auto timeBorrowed = std::chrono::system_clock::now() - rental->RentalStart();
        return {};
    }
};

//TESTING STARTS HERE

#include "mocks/MockRentable.h"
#include "mocks/MockCustomer.h"

using trompeloeil::_;
using trompeloeil::eq;
using namespace std::chrono_literals;
using std::chrono::system_clock;

TEST_CASE("An IRentable is correctly dated and given to a ICustomer") {
    // Given a RentalController
    RentalController rc{};

    // When we create some mocks
    auto mockRentable = std::make_unique<MockRentable>();
    MockCustomer mockCustomer;

    // And expect the customer to be given a rental
    auto ptrVal = mockRentable.get();
    REQUIRE_CALL(mockCustomer, AssignRental(_))
        .WITH(_1.get() == ptrVal);
    // And expect dates to be set
    auto expiry = system_clock::now() + 100min;
    REQUIRE_CALL(*mockRentable, RentalStart(_))
        .WITH(_1 <= system_clock::now());
    REQUIRE_CALL(*mockRentable, RentalEnd(_))
        .WITH(_1 == expiry);

    // Then after calling, everything should be fine.
    rc.IssueRental(mockCustomer, std::move(mockRentable), expiry);
}

SCENARIO("A Rental return is correctly handled and billed") {
    GIVEN("An instance of our RentalController") {
        RentalController rc{};

        AND_GIVEN("A MockCustomer with a MockRental for 1 day costing £2.45") {
            MockCustomer mockCust;
            auto mockRental = std::make_unique<MockRentable>();

            REQUIRE_CALL(mockCust, RemoveRental(_))
                .WITH(_1  == 0)
                .LR_RETURN(std::move(mockRental));
            auto start = system_clock::now();
            auto end   = start + 25h;
            REQUIRE_CALL(*mockRental, RentalStart())
                .RETURN(start);
            /*REQUIRE_CALL(*mockRental, RentalEnd())
                .RETURN(end);*/
            REQUIRE_CALL(*mockRental, CostPerDay())
                .RETURN(Money{2, 45});
            WHEN("We execute the return of the first rental") {
                auto amountOwed = rc.ReturnRental(mockCust, 0);

                THEN("The amount owed should be £2.45") {
                    CHECK(amountOwed == Money{2, 45});
                }
            }
        }
    }
}
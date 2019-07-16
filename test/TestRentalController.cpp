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

TEST_CASE("A RentalController correctly takes back a rental") {

}
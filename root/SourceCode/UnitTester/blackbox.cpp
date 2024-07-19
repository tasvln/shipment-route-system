
//1. `createPackage` Function :
#include "shipment.h"

    void testCreatePackage() {
    // Test Case 1: Valid package
    struct Package package1 = createPackage(1, 500, 0.75, Point(10, 20));
    // Verify package1's attributes

    // Test Case 2: Invalid package due to weight exceeding the limit
    struct Package package2 = createPackage(2, 1200, 0.8, Point(5, 15));
    // Verify package2 is invalid

    // Test Case 3: Invalid package due to size below the limit
    struct Package package3 = createPackage(3, 800, 0.2, Point(25, 30));
    // Verify package3 is invalid
}


//2. `validatePackage` Function:


#include "shipment.h"

void testValidatePackage() {
    // Test Case 1: Valid package
    int isValid1 = validatePackage(700, 0.5, Point(15, 25));
    // Verify isValid1 == 1

    // Test Case 2: Invalid package due to weight exceeding the limit
    int isValid2 = validatePackage(1200, 0.8, Point(5, 10));
    // Verify isValid2 == 0

    // Test Case 3: Invalid package due to size below the limit
    int isValid3 = validatePackage(600, 0.2, Point(30, 40));
    // Verify isValid3 == 0
}



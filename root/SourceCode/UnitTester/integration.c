#include <stdio.h>
#include "Shipment.h"
#include "mapping.h"
#include "integration.h"

void runIntegrationTests() {
    // Create a map
    struct Map baseMap = populateMap();

    // Create an array of trucks
    struct Truck trucks[MAX_TRUCKS];

    // Initialize your trucks and packages here
    
    struct Package package1 = createPackage(1, 500, 0.5, (struct Point){4, 'C'});
    struct Package package2 = createPackage(2, 1200, 1.2, (struct Point){5, 'E'});
    struct Package package3 = createPackage(3, 300, 0.3, (struct Point){3, 'B'});
    struct Package package4 = createPackage(4, 600, 0.6, (struct Point){9, 'G'});
    struct Package package5 = createPackage(5, 400, 0.4, (struct Point){8, 'F'});
    struct Package package6 = createPackage(6, 700, 0.7, (struct Point){6, 'E'});
    struct Package package7a = createPackage(7, 200, 0.2, (struct Point){5, 'E'});
    struct Package package7b = createPackage(8, 300, 0.3, (struct Point){3, 'C'});
    struct Package package8 = createPackage(9, 800, 0.8, (struct Point){7, 'D'});
    struct Package package9 = createPackage(10, 1000, 1.0, (struct Point){4, 'C'});
    struct Package package10 = createPackage(11, 900, 0.9, (struct Point){9, 'A'});
    struct Package package11 = createPackage(12, 1100, 1.1, (struct Point){10, 'A'});
    struct Package package12 = createPackage(13, 1500, 1.5, (struct Point){2, 'B'});

    // Assign packages to trucks
    assignPackage(&baseMap, package1);
    assignPackage(&baseMap, package2);
    assignPackage(&baseMap, package3);
    assignPackage(&baseMap, package4);
    assignPackage(&baseMap, package5);
    assignPackage(&baseMap, package6);
    assignPackage(&baseMap, package7a);
    assignPackage(&baseMap, package7b);
    assignPackage(&baseMap, package8);
    assignPackage(&baseMap, package9);
    assignPackage(&baseMap, package10);
    assignPackage(&baseMap, package11);
    assignPackage(&baseMap, package12);

    
}

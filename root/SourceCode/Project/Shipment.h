#ifndef SHIPMENT_H
#define SHIPMENT_H

#include "mapping.h"

#define MAX_PACKAGE_SIZE 1.0 // 1m^3
#define MID_PACKAGE_SIZE .5  // 1/2m^3
#define MIN_PACKAGE_SIZE .25 // 1/4m^3

#define MAX_TRUCK_WEIGHT 1000 // 1000kg
#define MAX_TRUCK_SIZE 36.0   // 36m^3

#define MAX_TRUCKS 3
#define MAX_PACKAGES 99

/*
 * Author: Temitope Adebayo
 * A structure to represent the details package to be shipped.
 */
struct Package
{
  int packageId;
  int weight;
  double size;
  struct Point destination;
};

/*
 * Author: Temitope Adebayo
 * A structure to represent the truck that will be used to ship the package.
 */
struct Truck
{
  int truckId;
  int weight;
  double size;
  struct Route route;
  struct Package *packages;
};

/*
 * Function: createPackage
 * Creates a package with the given parameters.
 * @param packageId: The id of the package.
 * @param weight: The weight of the package.
 * @param size: The size of the package.
 * @param destination: The destination of the package.
 * returns: A package with the given parameters.
 */
struct Package createPackage(int packageId, int weight, double size, struct Point destination);

/*
 * Function: validatePackage
 * Validates the package with the given parameters.
 * @param package: The package to be validated.
 * @param weight: The weight of the package.
 * @param size: The size of the package.
 * @param destination: The destination of the package.
 * returns: 1 if the package is valid, 0 otherwise.
 */
int validatePackage(int weight, double size, struct Point destination);

/*
 * Function: assignPackage
 * Assigns the package to the truck with the given parameters.
 * @param package: The package to be assigned.
 * @param map: The map of the truck.
 */

void assignPackage(const struct Map *map, struct Package package, struct Truck trucks[MAX_TRUCKS]);

/*
 * Function: createTruck
 * Creates a truck with the given parameters.
 * @param truckId: The id of the truck.
 * @param weight: The weight of the truck.
 * @param size: The size of the truck.
 * @param route: The route of the truck.
 * @param packages: The packages of the truck.
 * @param returns: A truck with the given parameters.
 */
struct Truck createTruck(int truckId, int weight, double size, struct Route route, struct Package *packages);

/*
 * Function: validateTruck
 * Validates the truck if it can be used to ship the package.
 * @param truck: The truck to be validated.
 * @param package: The package to be shipped.
 * returns: 1 if the truck is valid, 0 otherwise.
 */

int validateTruck(struct Truck truck, struct Package package);

/*
 * Function: display
 * Displays the details of the truck and the package.
 * @param truck: The truck to be displayed.
 * @param package: The package to be displayed.
 */
void display(struct Route route, struct Package package);

/*
 * Function: hasDestination
 * Checks if the package has a destination.
 * @param route: The route of the truck.
 * @param package: The package to be shipped.
 * returns: 1 if the package has a destination, 0 otherwise.
 */
int hasDestination(struct Route *route, struct Package package);

#endif

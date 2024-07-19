#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "Shipment.h"

int main(void)
{
  struct Map baseMap = populateMap();

  struct Route blueRoute = getBlueRoute();
  struct Route greenRoute = getGreenRoute();
  struct Route yellowRoute = getYellowRoute();

  // create trucks
  struct Truck blueTruck = createTruck(1, 0, 0, blueRoute, NULL);
  struct Truck greenTruck = createTruck(2, 0, 0, greenRoute, NULL);
  struct Truck yellowTruck = createTruck(3, 0, 0, yellowRoute, NULL);

  struct Truck trucks[MAX_TRUCKS] = {blueTruck, greenTruck, yellowTruck};

  int input, flag = 0, isValid;
  size_t i;
  int weight;
  size_t pointLength;
  double size;
  char point[3];

  struct Point destination = {0};
  struct Package package = {0};

  printf("=================\n");
  printf("Seneca Deliveries\n");
  printf("=================\n");

  do
  {
    // get input from user
    printf("Enter shipment weight, box size and destination (0 0 x to stop): ");
    input = scanf("%d %lf %s", &weight, &size, point);

    pointLength = strlen(point);

    // check if input is valid
    if (weight == 0 && size == 0 && point[0] == 'x')
    {
      printf("Thank you for shipping with Seneca!\n");
      flag = 1;
    }
    else
    {
      destination.row = 0;
      destination.col = 0;

      if (input != 3)
      {
        printf("Invalid Package Input\n");
      }
      else
      {

        for (i = 0; i < pointLength; i++)
        {
          if (point[i] >= '0' && point[i] <= '9')
          {
            destination.row = destination.row * 10 + (point[i] - '0');
          }
          else if (point[i] >= 'A' && point[i] <= 'Z')
          {
            destination.col = destination.col * 26 + (point[i] - 'A');
          }
        }

        // check if package is valid
        isValid = validatePackage(weight, size, destination);

        if (isValid == 1)
        {
          package.packageId = package.packageId + 1;
          package.weight = weight;
          package.size = size;
          package.destination.col = destination.col;
          package.destination.row = --destination.row;
          assignPackage(&baseMap, package, trucks);
        }
      }
    }
  } while (flag == 0);

  return 0;
}

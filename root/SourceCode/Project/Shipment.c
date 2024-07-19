#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "mapping.h"
#include "Shipment.h"

int validatePackage(int weight, double size, struct Point destination)
{
  struct Map map = populateMap();
  int isValid = 1;

  // check if package is valid by weight, size, and destination
  if (weight < 0 || weight > MAX_TRUCK_WEIGHT)
  {
    printf("Invalid weight (must be 1-1000 Kg.)\n");
    isValid = 0;
  }
  else if (size != MAX_PACKAGE_SIZE && size != MID_PACKAGE_SIZE && size != MIN_PACKAGE_SIZE)
  {
    printf("Invalid size\n");
    isValid = 0;
  }
  else if ((destination.row < 0 || destination.row > MAP_ROWS) || (destination.col < 0 || destination.col > MAP_COLS))
  {
    printf("Invalid destination\n");
    isValid = 0;
  }
  else if (map.squares[(int)destination.row][(int)destination.col] == 0)
  {
    printf("Invalid destination\n");
    isValid = 0;
  }
  return isValid;
}

int validateTruck(struct Truck truck, struct Package package)
{
  int isValid = 0;

  // check if truck is valid by weight and size
  if ((truck.weight + package.weight >= MAX_TRUCK_WEIGHT) || (truck.size + package.size >= MAX_TRUCK_SIZE))
  {
    isValid = 1;
  }
  return isValid;
}

struct Truck createTruck(int truckId, int weight, double size, struct Route route, struct Package *packages)
{
  struct Truck truck = {0};

  truck.truckId = truckId;
  truck.weight = weight;
  truck.size = size;
  truck.route = route;
  truck.packages = packages;

  return truck;
}

void assignPackage(const struct Map *map, struct Package package, struct Truck trucks[MAX_TRUCKS])
{
  // shortest path
  struct Route shortPath = {0};

  struct Route blueShortestPath = {0};
  double blueDistance = 0;
  struct Route greenShortestPath = {0};
  double greenDistance = 0;
  struct Route yellowShortestPath = {0};
  double yellowDistance = 0;

  // for each truck, check if the package is valid
  for (int i = 0; i < 3; i++)
  {
    int isValid = validateTruck(trucks[i], package);

    if (isValid != 1)
    {
      for (int j = 0; j < trucks[i].route.numPoints; j++)
      {

        double currDistance = distance(&trucks[i].route.points[j], &package.destination);

        if (trucks[i].route.routeSymbol == BLUE)
        {
          if (blueDistance == 0 || currDistance < blueDistance)
          {
            blueDistance = currDistance;

            blueShortestPath = shortestPath(map, trucks[i].route.points[j], package.destination);

            if (hasDestination(&blueShortestPath, package) == 0 && blueDistance == 1)
            {
              blueShortestPath.numPoints = 1;
            }
          }
        }
        else if (trucks[i].route.routeSymbol == GREEN)
        {
          if (greenDistance == 0 || currDistance < greenDistance)
          {
            greenDistance = currDistance;

            greenShortestPath = shortestPath(map, trucks[i].route.points[j], package.destination);

            if (hasDestination(&greenShortestPath, package) == 0 && greenDistance == 1)
            {
              greenShortestPath.numPoints = 1;
            }
          }
        }
        else if (trucks[i].route.routeSymbol == YELLOW)
        {
          if (yellowDistance == 0 || currDistance < yellowDistance)
          {
            yellowDistance = currDistance;

            yellowShortestPath = shortestPath(map, trucks[i].route.points[j], package.destination);

            if (hasDestination(&yellowShortestPath, package) == 0 && yellowDistance == 1)
            {
              yellowShortestPath.numPoints = 1;
            }
          }
        }
      }
    }
  }

  // if the distance of one of the trucks is 0, then the package should be shipped by the other truck with the shortest distance
  if (blueDistance != 0 && greenDistance != 0 && yellowDistance != 0)
  {
    if (blueDistance < greenDistance && blueDistance < yellowDistance)
    {
      shortPath = blueShortestPath;
      shortPath.routeSymbol = BLUE;
    }
    else if (greenDistance < blueDistance && greenDistance < yellowDistance)
    {
      shortPath = greenShortestPath;
      shortPath.routeSymbol = GREEN;
    }
    else if (yellowDistance < blueDistance && yellowDistance < greenDistance)
    {
      shortPath = yellowShortestPath;
      shortPath.routeSymbol = YELLOW;
    }
  }
  else
  {
    if (blueDistance == 0 && greenDistance == 0 && yellowDistance == 0)
    {
      shortPath.numPoints = 0;
    }
    else if (blueDistance == 0 && greenDistance == 0)
    {
      shortPath = yellowShortestPath;
      shortPath.routeSymbol = YELLOW;
    }
    else if (blueDistance == 0 && yellowDistance == 0)
    {
      shortPath = greenShortestPath;
      shortPath.routeSymbol = GREEN;
    }
    else if (greenDistance == 0 && yellowDistance == 0)
    {
      shortPath = blueShortestPath;
      shortPath.routeSymbol = BLUE;
    }
    else if (blueDistance == 0)
    {
      if (greenDistance < yellowDistance)
      {
        shortPath = greenShortestPath;
        shortPath.routeSymbol = GREEN;
      }
      else
      {
        shortPath = yellowShortestPath;
        shortPath.routeSymbol = YELLOW;
      }
    }
    else if (greenDistance == 0)
    {
      if (blueDistance < yellowDistance)
      {
        shortPath = blueShortestPath;
        shortPath.routeSymbol = BLUE;
      }
      else
      {
        shortPath = yellowShortestPath;
        shortPath.routeSymbol = YELLOW;
      }
    }
    else if (yellowDistance == 0)
    {
      if (blueDistance < greenDistance)
      {
        shortPath = blueShortestPath;
        shortPath.routeSymbol = BLUE;
      }
      else
      {
        shortPath = greenShortestPath;
        shortPath.routeSymbol = GREEN;
      }
    }
  }

  display(shortPath, package);

  if (shortPath.routeSymbol == BLUE)
  {
    trucks[0].weight += package.weight;
    trucks[0].size += package.size;
  }
  else if (shortPath.routeSymbol == GREEN)
  {
    trucks[1].weight += package.weight;
    trucks[1].size += package.size;
  }
  else if (shortPath.routeSymbol == YELLOW)
  {
    trucks[2].weight += package.weight;
    trucks[2].size += package.size;
  }
}

int hasDestination(struct Route *route, struct Package package)
{
  int found = 0, i = 0;

  for (i = 0; i < route->numPoints; i++)
  {
    if (eqPt(route->points[i], package.destination) == 1)
    {
      found = 1;
    }
  }

  return found;
}

void display(struct Route route, struct Package package)
{
  if (route.routeSymbol == 2)
  {
    printf("Ship on BLUE LINE, ");
  }
  else if (route.routeSymbol == 4)
  {
    printf("Ship on GREEN LINE, ");
  }
  else if (route.routeSymbol == 8)
  {
    printf("Ship on YELLOW LINE, ");
  }

  if (route.numPoints != 0)
  {
    if (route.numPoints == 1)
    {
      printf("no diversion");
    }
    else
    {
      printf("divert: ");
      for (int i = 0; i < route.numPoints; i++)
      {
        if (i == route.numPoints - 1)
        {
          printf("%d%c", route.points[i].row + 1, 'A' + route.points[i].col);
        }
        else
        {
          printf("%d%c, ", route.points[i].row + 1, 'A' + route.points[i].col);
        }
      }
      if (package.destination.row != route.points[route.numPoints - 1].row || package.destination.col != route.points[route.numPoints - 1].col)
      {
        printf(", %d%c", package.destination.row + 1, 'A' + package.destination.col);
      }
    }
  }
  else
  {
    printf("Ships tommorow");
  }
  printf("\n");
}

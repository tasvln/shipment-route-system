

//1.  Positive Test Case : 

struct Package package = createPackage(1, 10, 0.5, (struct Point) { 10, 15 });
assert(package.packageId == 1);
assert(package.weight == 10);
assert(package.size == 0.5);
assert(package.destination.x == 10 && package.destination.y == 15);


//2. Negative Test Case(Invalid Size) 
struct Package package = createPackage(2, 5, -1.0, (struct Point) { 20, 30 });
assert(package.packageId == 2);
assert(package.weight == 5);
assert(package.size == 0.0); // Size should be set to 0 for invalid input


//3. Negative Test Case(Invalid Weight) :

struct Package package = createPackage(3, -5, 0.25, (struct Point) { 5, 5 });
assert(package.packageId == 3);
assert(package.weight == 0); // Weight should be set to 0 for invalid input
assert(package.size == 0.25);


//Test Cases for `validatePackage` function:

//1. Positive Test Case : 

int isValid = validatePackage(15, 0.75, (struct Point) { 10, 20 });
assert(isValid == 1);


//2. Negative Test Case(Invalid Weight) :

int isValid = validatePackage(-5, 0.5, (struct Point) { 5, 10 });
assert(isValid == 0);
```

//3. Negative Test Case(Invalid Size) :

int isValid = validatePackage(8, -0.5, (struct Point) { 15, 25 });
assert(isValid == 0);


// Test Cases for `assignPackage` function:

//1. Positive Test Case : 

struct Package package = createPackage(1, 20, 0.75, (struct Point) { 30, 40 });
struct Truck trucks[MAX_TRUCKS];
struct Map map;
// Initialize map and trucks
assignPackage(&map, package, trucks);
// Verify that package is assigned to a truck
assert(trucks[0].packages[0].packageId == package.packageId);


//2. Negative Test Case(Invalid Truck) :

struct Package package = createPackage(2, 15, 0.6, (struct Point) { 20, 30 });
struct Truck trucks[MAX_TRUCKS];
struct Map map;
// Initialize map and trucks
// Trying to assign a package to an invalid truck
assignPackage(&map, package, trucks);
// Verify that no package is assigned to trucks
assert(trucks[0].packages[0].packageId != package.packageId);


//3. Negative Test Case(Package Size Exceeds Truck Capacity) :

struct Package package = createPackage(3, 25, 2.0, (struct Point) { 10, 10 });
struct Truck trucks[MAX_TRUCKS];
struct Map map;
// Initialize map and trucks
assignPackage(&map, package, trucks);
// Verify that no package is assigned to trucks
assert(trucks[0].packages[0].packageId != package.packageId);



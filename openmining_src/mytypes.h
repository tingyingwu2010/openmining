#ifndef mytypes_h
#define mytypes_h

// standard includes
#include <map>
#include <cstdint>

// boost includes

// Qt includes

// my includes
typedef int32_t y_coordinate32_t;
typedef int32_t xcoordinate32_t;
typedef int32_t zcoordinate32_t;

typedef std::map<y_coordinate32_t, zcoordinate32_t> yzcoordinates32_t;
typedef std::map<xcoordinate32_t, yzcoordinates32_t> xyzcoordinates32_t; // long = x , lat = y, elev = z

#endif
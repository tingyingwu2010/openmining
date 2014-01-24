/*
  Copyright 2014 Daniel McInnes

  This file is part of OpenMining.

  OpenMining is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  OpenMining is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with OpenMining.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef elevation_h
#define elevation_h

// standard library includes
#include <string>
#include <iostream>

// boost #includes
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/map.hpp>

// Qt includes

// my includes
#include "mytypes.h" // typedefs
#include "cube.h" // 'Cube' member variable m_extremities
#include "simpleplot.h" // m_plot

class Locations;
class Longitudes;
class Latitudes;

/**
  The 'Latitudes' class exists purely to enable the following syntactic sugar:
  Longitudes[some_longitude][some_latitude] = some_elevation;
  It doesn't have any use apart from that.
*/
class Latitudes
{
public:
  friend class boost::serialization::access;
  Latitudes();
  elevation_t& operator[](const latitude_t& latitude);
  latitudes_t m_latitudes;
 
private:

  // When the class Archive corresponds to an output archive, the
  // & operator is defined similar to <<.  Likewise, when the class Archive
  // is a type of input archive the & operator is defined similar to >>.
  template<class Archive>
  void serialize(Archive& ar, const unsigned int version)
  {
    ar & m_latitudes;
    Q_UNUSED(version);
  }
};

typedef std::map<longitude_t, Latitudes> longitudes_t; // long = x , lat = y, elev = z

class Longitudes
{
public:
  friend class boost::serialization::access;
  Longitudes();
  Longitudes(QStringList& args);
  Longitudes& operator=(const Locations& locations);
  bool load();
  bool saveIfUpdated();
  void print(void);
  Cube m_extremities;
  double getElevation(double& longitude, double& latitude, const uint32_t coarseness);

private:
  Latitudes& operator[](const longitude_t& longitude);
  longitudes_t m_longitudes; // m_longitudes[long][lat] = elevation
  longitudes_t m_plottedLongitudes; // m_longitudes[long][lat] = elevation
  const char* m_key = "--longitudes-filename";
  std::string m_filename;  
  QStringList& m_args;
  bool changesNotSaved;
  // When the class Archive corresponds to an output archive, the
  // & operator is defined similar to <<.  Likewise, when the class Archive
  // is a type of input archive the & operator is defined similar to >>.
  template<class Archive>
  void serialize(Archive& ar, const unsigned int version)
  {
    ar & m_extremities;
    //ar & m_longitudes;
    ar & m_plottedLongitudes;
    Q_UNUSED(version);
  }
};

#endif

#ifndef Geometry_DTGeometry_DTTopology_H
#define Geometry_DTGeometry_DTTopology_H

/** \class DTTopology
 *
 * Conversion between the local frame of the DT DetUnits (i.e. a layer
 * of cells in a superlayer) and the "measurement frame".
 * This is a rectangular frame where x runs between (FirstCellNumber-0.5)
 * and (LastCellNumber+0.5). Note that cell numbers follow the hardware
 * convention, so that FirstCellNumber is either 1 or 2 depending of the layer.
 *
 * Note that DTs measure a time, not a position, so unlike for strip detectors,
 * there is no guarantee that a measurement in a cell will not end up in
 * the neighbouring cell. This must be taken into account for all cases where a * LocalPoint is used as an argument, e.g. to get back the channel number.
 * This will be an issue if wire misalignment is introduced.
 *
 * The Topology interface is extended with methods relevant for
 * the DT detectors, e.g. wirePosition(int), etc.
 *  
 *  $Date: 2006/02/08 15:25:55 $
 *  $Revision: 1.8 $
 *
 * \author R. Bellan - INFN Torino
 *
 */

#include "Geometry/CommonTopologies/interface/Topology.h"
#include "Geometry/Vector/interface/LocalPoint.h"

class DTTopology: public Topology {
 public:
  
  /// Constructor: number of first wire, total # of wires in the layer and their lenght
  DTTopology(int firstWire, int nChannels, float semilenght); 

  virtual ~DTTopology() {}
  
  /// Conversion between measurement coordinates
  /// and local cartesian coordinates.
  LocalPoint localPosition( const MeasurementPoint& ) const;

  /// Conversion between measurement coordinates
  /// and local cartesian coordinates.
  LocalError localError( const MeasurementPoint&, const MeasurementError& ) const;

  /// Conversion to the measurement frame.
  /// (Caveat: when converting the position of a rechit, there is no
  /// guarantee that the converted value can be interpreted as the cell
  /// where the hit belongs, see note on neighbouring cells in the class
  /// header.
  MeasurementPoint measurementPosition( const LocalPoint&) const;

  /// Conversion to the measurement frame.
  MeasurementError measurementError( const LocalPoint&, const LocalError& ) const;

  /// Return the wire number, starting from a LocalPoint.
  /// This method is deprecated: when converting the position of a rechit,
  /// there is no guarantee that the converted value can be
  /// interpreted as the cell where the hit belongs, see note on
  /// neighbouring cells in the class header.
  int channel( const LocalPoint& p) const;

  /// Returns the x position in the layer of a given wire number.
  float wirePosition(int wireNumber) const;
  
  /// Returns the cell width.
  const float cellWidth() const {return theWidth;}
  /// Returns the cell height.
  const float cellHeight() const {return theHeight;}
  /// Returns the cell lenght.
  const float cellLenght() const {return theLength;}
  /// Returns the number of wires in the layer
  const int channels() const {return theNChannels;} 

  /// Returns the width of the actual sensible volume of the cell.
  const float sensibleWidth() const;
  /// Returns the height of the actual sensible volume of the cell.
  const float sensibleHeight() const;

  /// Sides of the cell
  enum Side {zMin,zMax,xMin,xMax,yMin,yMax,none}; 

  /// Returns the side of the cell in which resides the point (x,y,z) (new cell geometry, 
  /// i.e. with I-beam profiles).
  Side onWhichBorder(float x, float y, float z) const;
  /// Returns the side of the cell in which resides the point (x,y,z) (old cell geometry).
  Side onWhichBorder_old(float x, float y, float z) const;
  
private: 
  int theFirstChannel;
  int theNChannels;
  
  static const float theWidth;
  static const float theHeight;
  float theLength;

  static const float IBeamWingThickness;
  static const float IBeamWingLength;
  static const float plateThickness;
  static const float IBeamThickness;

  Local2DPoint theOffSet;
};

#endif
/*
 * PolygonIterator.hpp
 *
 *  Created on: Sep 19, 2014
 *      Author: Péter Fankhauser
 *   Institute: ETH Zurich, Autonomous Systems Lab
 */

#pragma once

#include "grid_map_core/GridMap.hpp"
#include "grid_map_core/Polygon.hpp"
#include "grid_map_core/iterators/SubmapIterator.hpp"

// Eigen
#include <Eigen/Core>

// unique_ptr
#include <memory>

namespace grid_map {

/*!
 * Iterator class to iterate through a polygonal area of the map.
 */
class PolygonIterator
{
public:

  /*!
   * Constructor.
   * @param gridMap the grid map to iterate on.
   * @param polygon the polygonal area to iterate on.
   */
  PolygonIterator(const grid_map_core::GridMap& gridMap, const grid_map_core::Polygon& polygon);

  /*!
   * Assignment operator.
   * @param iterator the iterator to copy data from.
   * @return a reference to *this.
   */
  PolygonIterator& operator =(const PolygonIterator& other);

  /*!
   * Compare to another iterator.
   * @return whether the current iterator points to a different address than the other one.
   */
  bool operator !=(const PolygonIterator& other) const;

  /*!
   * Dereference the iterator with const.
   * @return the value to which the iterator is pointing.
   */
  const Eigen::Array2i& operator *() const;

  /*!
   * Increase the iterator to the next element.
   * @return a reference to the updated iterator.
   */
  PolygonIterator& operator ++();

  /*!
   * Indicates if iterator is passed end.
   * @return true if iterator is out of scope, false if end has not been reached.
   */
  bool isPassedEnd() const;

private:

  /*!
   * Check if current index is inside polygon.
   * @return true if inside, false otherwise.
   */
  bool isInside();

  /*!
   * Finds the submap that fully contains the polygon and returns the parameters.
   * @param[in] polygon the polygon to get the submap for.
   * @param[out] startIndex the start index of the submap.
   * @param[out] bufferSize the buffer size of the submap.
   */
  void findSubmapParameters(const grid_map_core::Polygon& polygon, Eigen::Array2i& startIndex, Eigen::Array2i& bufferSize) const;

  //! Polygon to iterate on.
  grid_map_core::Polygon polygon_;

  //! Grid submap iterator.
  std::shared_ptr<SubmapIterator> internalIterator_;

  //! Map information needed to get position from iterator.
  Eigen::Array2d mapLength_;
  Eigen::Vector2d mapPosition_;
  double resolution_;
  Eigen::Array2i bufferSize_;
  Eigen::Array2i bufferStartIndex_;
};

} /* namespace */

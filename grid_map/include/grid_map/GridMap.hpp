/*
 * GridMap.hpp
 *
 *  Created on: Jul 14, 2014
 *      Author: Péter Fankhauser
 *	 Institute: ETH Zurich, Autonomous Systems Lab
 */

#pragma once

#include "grid_map_core/TypeDefs.hpp"
#include <grid_map_core/GridMap.hpp>
#include <grid_map_msgs/GridMap.h>

// STL
#include <vector>
#include <unordered_map>

// Eigen
#include <Eigen/Core>

// ROS
#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <nav_msgs/OccupancyGrid.h>

namespace grid_map {

/*!
 * ROS interface for the Grid Map library.
 */
class GridMap : public grid_map_core::GridMap
{
 public:
  /*!
   * Default constructor.
   */
  GridMap();

  /*!
   * Constructor.
   * @param layers a vector of strings containing the definition/description of the data layers.
   */
  GridMap(const std::vector<std::string>& layers);

  /*!
   * Constructor. Sets the contents from a ROS message of type GridMap.
   * @param message the GridMap message.
   */
  GridMap(const grid_map_msgs::GridMap& message);

  /*!
   * Destructor.
   */
  virtual ~GridMap();

  /*!
   * Gets a submap from the map. The requested submap is specified with the requested
   * location and length.
   * @param[in] position the requested position of the submap (usually the center).
   * @param[in] length the requested length of the submap.
   * @param[out] isSuccess true if successful, false otherwise.
   * @return submap (is empty if success is false).
   */
  GridMap getSubmap(const Position& position, const Length& length, bool& isSuccess);

  /*!
   * Gets a submap from the map. The requested submap is specified with the requested
   * location and length.
   * @param[in] position the requested position of the submap (usually the center).
   * @param[in] length the requested length of the submap.
   * @param[out] indexInSubmap the index of the requested position in the submap.
   * @param[out] isSuccess true if successful, false otherwise.
   * @return submap (is empty if success is false).
   */
  GridMap getSubmap(const Position& position, const Length& length, Index& indexInSubmap, bool& isSuccess);

  /*!
   * Puts the all contents to a ROS message of type GridMap.
   * @param[out] message the GridMap message to be populated.
   */
  void toMessage(grid_map_msgs::GridMap& message) const;

  /*!
   * Puts the data of requested layers to a ROS message of type GridMap.
   * @param[in] layers the layers to be added to the message.
   * @param[out] message the GridMap message to be populated.
   */
  void toMessage(const std::vector<std::string>& layers, grid_map_msgs::GridMap& message) const;

  /*!
   * Puts the contents to a ROS PointCloud2 message. Set the type to be transformed
   * as the points of the point cloud, all other types will be added as additional fields.
   * @param pointCloud the message to be populated.
   * @param pointLayer the type that is transformed to points.
   */
  void toPointCloud(sensor_msgs::PointCloud2& pointCloud, const std::string& pointLayer) const;

  /*!
   * Puts the contents to a ROS PointCloud2 message. Set the type to be transformed
   * as the points of the point cloud and all other types to be added as additional fields.
   * @param pointCloud the message to be populated.
   * @param pointLayer the layer that is transformed to points.
   * @param layersToAdd the layers that should be added as fields to the point cloud. Must include the pointLayer.
   */
  void toPointCloud(sensor_msgs::PointCloud2& pointCloud, const std::string& pointLayer,
                    const std::vector<std::string>& layersToAdd) const;

  /*!
   * Puts the contents to a ROS OccupancyGrid message. Set the type to be transformed
   * as the cell data of the occupancy grid, all other types will be neglected.
   * @param occupancyGrid the message to be populated.
   * @param layer the layer that is transformed to the occupancy cell data.
   * @param dataMin the minimum value of the grid map data (used to normalize the cell data in [min, max]).
   * @param dataMax the maximum value of the grid map data (used to normalize the cell data in [min, max]).
   */
  void toOccupancyGrid(nav_msgs::OccupancyGrid& occupancyGrid, const std::string& layer,
                       float dataMin, float dataMax) const;

 private:
  /*!
   * Sets the contents from a ROS message of type GridMap.
   * @param message the GridMap message.
   * @return true if successful, false otherwise.
   */
  bool fromMessage(const grid_map_msgs::GridMap& message);
};

} /* namespace */

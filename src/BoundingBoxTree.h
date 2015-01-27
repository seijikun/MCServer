
// BoundingBoxTree.h

// Declares the cBoundingBoxTree class representing an R-Tree for fast intersection lookups.




#pragma once

#include "boost/geometry/index/rtree.hpp"

class cBoundingBox;



/** Tree optimization
Maximal amount of children within the last tree-layer
*/
#define RTREE_MAX_CHILDREN 8

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

typedef bg::model::point<double, 2, bg::cs::cartesian> Point;
typedef bg::model::box<Point> Box;
typedef std::pair<Box, cBoundingBox*> Value;




// tolua_begin

/** This is an R-Tree containing cBoundingBoxes for very fast intersection lookups.
This tree is optimized for reading-access. Adding to the tree is rather slow.
*/

class cBoundingBoxTree
{

public:
	cBoundingBoxTree();

	/// Insert a cBoundingBox into the tree
	void Insert(cBoundingBox* a_BBox);

	/// Remove a cBoundingBox from the tree
	void Remove(cBoundingBox* a_BBox);
	
	/// Returns the first found cBoundingBox which the block (x, y, z) is located in
	cBoundingBox* GetFirstContaining(double x, double y, double z);
	
	/// Returns the first found cBoundingBox which the block (x, z) is located in, ignoring the y coordinate
	cBoundingBox* GetFirstContaining(double x, double z);

protected:
	std::map<cBoundingBox*, Value> valueMap;
	bgi::rtree< Value, bgi::rstar<RTREE_MAX_CHILDREN>> rTree;

};

// tolua_end

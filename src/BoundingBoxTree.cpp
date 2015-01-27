
// BoundingBoxTree.cpp

// Implements the cBoundingBoxTree class representing an R-Tree for fast intersection lookups.


#include "Globals.h"
#include "BoundingBoxTree.h"
#include "Defines.h"

#include "BoundingBox.h"



cBoundingBoxTree::cBoundingBoxTree()
{
}




void cBoundingBoxTree::Insert(cBoundingBox* a_BBox)
{
	// create tree-item
	Value item = std::make_pair(Box(
		Point(a_BBox->GetMinX(), a_BBox->GetMinZ()),
		Point(a_BBox->GetMaxX(), a_BBox->GetMaxZ())
	), a_BBox);

	// insert tree-item into valueMap
	valueMap[a_BBox] = item;

	// insert item into the tree
	rTree.insert(item);

	// notify affected cBoundingBox of being added to a tree
	a_BBox->addTreeReference(this);
}





void cBoundingBoxTree::Remove(cBoundingBox* a_BBox)
{
	// get and remove tree-item from valueMap
	Value item = valueMap[a_BBox];
	valueMap.erase(a_BBox);

	// remove item from the tree
	rTree.remove(item);

	// notify affected cBoundingBox of being removed from a tree
	a_BBox->removeTreeReference(this);
}





cBoundingBox* cBoundingBoxTree::GetFirstContaining(double x, double y, double z)
{
	std::vector<Value> found_boxes;
	Point queryPoint(x, z);
	rTree.query(bgi::intersects(queryPoint), std::back_inserter(found_boxes));
	
	for (unsigned int i = 0; i < found_boxes.size(); i++)
	{
		cBoundingBox* tmp = found_boxes[i].second;
		if (tmp->IsInside(x, y, z))
		{
			return tmp;
		}
	}
	
	return nullptr;
}


cBoundingBox* cBoundingBoxTree::GetFirstContaining(double x, double z)
{
	std::vector<Value> found_boxes;
	Point queryPoint(x, z);
	rTree.query(bgi::intersects(queryPoint), std::back_inserter(found_boxes));
	
	if (found_boxes.size() > 0)
	{
		return found_boxes[0].second;
	}
	return nullptr;
}

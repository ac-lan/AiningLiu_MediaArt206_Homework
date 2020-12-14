#include "utils.h"


void drawBox(ofPoint position, ofPoint dimensions, ofColor color) {
	ofPushMatrix();
		ofTranslate(position.x + dimensions.x / 2, position.y + dimensions.y / 2, position.z + dimensions.z / 2);
		ofBoxPrimitive box = ofBoxPrimitive(dimensions.x, dimensions.y, dimensions.z);
		ofSetColor(color);
		box.draw();
	ofPopMatrix();
}

void drawBox(ofPoint dimensions, ofColor color) {
	ofPushMatrix();
		ofTranslate(dimensions.x / 2, dimensions.y / 2, dimensions.z / 2);
		ofBoxPrimitive box = ofBoxPrimitive(dimensions.x, dimensions.y, dimensions.z);
		ofSetColor(color);
		box.draw();
	ofPopMatrix();
}


BoundingBox getMeshBoundingBox(ofMesh mesh)
{	
	
	auto extremes_x = minmax_element(mesh.getVertices().begin(), mesh.getVertices().end(), [](const ofPoint& point1, const ofPoint& point2) {
		return point1.x < point2.x;
	});

	auto extremes_y = minmax_element(mesh.getVertices().begin(), mesh.getVertices().end(), [](const ofPoint& point1, const ofPoint& point2) {
		return point1.y < point2.y;
	});

	auto extremes_z = minmax_element(mesh.getVertices().begin(), mesh.getVertices().end(), [](const ofPoint& point1, const ofPoint& point2) {
		return point1.z < point2.z;
	});

	ofPoint max = ofPoint(extremes_x.second->x, extremes_y.second->y, extremes_z.second->z);
	ofPoint min = ofPoint(extremes_x.first->x, extremes_y.first->y, extremes_z.first->z);

	ofPoint size = max - min;
	
	BoundingBox bb = BoundingBox();
	bb.min = min;
	bb.max = max;
	bb.size = size;
	
	return bb;
}



// orignal code
// https://forum.openframeworks.cc/t/finding-bounding-width-height-depth-of-a-mesh/26190/3
//ofVec3f getMeshBoundingBoxDimension(const ofMesh &mesh) {
//
//	auto xExtremes = minmax_element(mesh.getVertices().begin(), mesh.getVertices().end(),
//		[](const ofPoint& lhs, const ofPoint& rhs) {
//		return lhs.x < rhs.x;
//	});
//	auto yExtremes = minmax_element(mesh.getVertices().begin(), mesh.getVertices().end(),
//		[](const ofPoint& lhs, const ofPoint& rhs) {
//		return lhs.y < rhs.y;
//	});
//	auto zExtremes = minmax_element(mesh.getVertices().begin(), mesh.getVertices().end(),
//		[](const ofPoint& lhs, const ofPoint& rhs) {
//		return lhs.z < rhs.z;
//	});
//	return ofVec3f(xExtremes.second->x - xExtremes.first->x,
//		yExtremes.second->y - yExtremes.first->y,
//		zExtremes.second->z - zExtremes.first->z);
//}
/*
//
// Created by Michal on 12.01.2024.
//

#include "VectorImage.h"

VectorImage::VectorImage(NSVGimage *image) {
    int shapeIndex = 0;
    for (NSVGshape *shape = image->shapes; shape != nullptr; shape = shape->next) {
        m_ShapeColor[shapeIndex] = shape->stroke.color;
        m_ShapeStrokeWidth[shapeIndex] = shape->strokeWidth;
        int pathCount = 0;
        for (NSVGpath *path = shape->paths; path != nullptr; path = path->next) {
            pathCount++;
        }
        m_PathPointCount[shapeIndex]    = new int[pathCount];
        m_Shape[shapeIndex] = new float *[pathCount];
        int pathIndex = 0;
        for (NSVGpath *path = shape->paths; path != nullptr; path = path->next) {
            m_PathPointCount[shapeIndex][pathIndex] = path->npts;
            m_Shape[shapeIndex][pathIndex] = new float[path->npts * 2];
            for (int i = 0; i < path->npts; i++) {
                m_Shape[shapeIndex][pathIndex][i * 2] = path->pts[i * 2];
                m_Shape[shapeIndex][pathIndex][i * 2 + 1] = path->pts[i * 2 + 1];
            }
            pathIndex++;
        }
        shapeIndex++;
    }



}
*/

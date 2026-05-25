
#ifndef CELLDECOMPOSITION_H
#define CELLDECOMPOSITION_H

#include <voro++.hh>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QVector3D>
#include<iostream>
#include "core.h"
#include "multiResolutionGraph.h"
#include <map>
#include <set>
#include "voronoi.h"




class CellDecomposition: protected QOpenGLFunctions_3_3_Core, QOpenGLContext {
 public:
    
   CellDecomposition();

   void clear();
   
   void renderCells();
   void renderParticles();
   void renderLinks();
   void renderPaths(std::set<std::pair<int,int>>& paths);

   void fullMeshDecomposition();
   void setShader(QOpenGLShaderProgram* shader) {cellShader = shader;} 
   Vector3 getMin() {return min;}
   Vector3 getMax() {return max;}
   
   void initializeSphereVAO(unsigned int numSubdivisions);
   void initializeCylinderVAO();

   void updateMesh(const std::vector<int>& newC, const std::vector<int>& oldC);
   
   std::vector<vorocell>* getCells() {return &graph.getCells(0);}
   std::map<std::pair<int,int>, vorolink>* getLinks() {return &graph.getLinks(0);}
   std::set<std::pair<int,int>>* getExteriorLinks() {return &graph.getExteriorLinks(0);}

   void voronoiDecomposition(std::vector<float>& v, std::vector<uint>& f, const HeightField *hf) {graph.multiLevelVoronoiDecomposition(v,f,hf);}
   void toyVoronoi(const HeightField *hf) {graph.toyVoronoi(hf);};

 private:
   std::vector<GLuint> cellVAOs;
   std::vector<GLuint> bufferVerts;
   std::vector<GLuint> bufferIndices;
   QOpenGLShaderProgram* cellShader = nullptr;

   MultiResolutionGraph graph;

   Vector3 min;
   Vector3 max;
   GLuint sphereVAO, cylinderVAO;
   GLuint sphereVertsVBO, cylinderVertsVBO;
   GLuint sphereIndicesVBO, cylinderIndicesVBO;
   unsigned int sphereIndicesSize;

   void cellToMesh(std::vector<float>& v, std::map<int,voroFace>& f, GLuint& meshVAO, GLuint& bufferVerts, GLuint& bufferIndices, int& triangles);
   void computeBounds();  

  
};

#endif
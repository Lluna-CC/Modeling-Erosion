
#ifndef CELLDECOMPOSITION_H
#define CELLDECOMPOSITION_H

#include <voro++.hh>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QVector3D>
#include<iostream>
#include "core.h"
#include <map>
#include <set>


enum cellState {
  SOLID,
  AIR,
  CORE
};

enum linkState {
  INTERIOR,
  EXTERIOR,
  BROKEN
};

struct voroFace {
  //int planeID;
  //std::vector<unsigned int> faceNeighbors;
  std::vector<unsigned int> vertices;
  double area;
  Vector3 normal;
};


struct vorocell {
  Vector3 centroid;
  std::vector<float> vertices;
  std::map<int,voroFace> faceData;
  std::vector<int> neighbors;
  int nTriangles;
  cellState state = SOLID;
  bool isExterior = false;
  
};

struct vorolink  {
  std::vector<std::pair<int,int>> neighbors;
  linkState state = INTERIOR;
  double life = 1.0;
};



class CellDecomposition: protected QOpenGLFunctions_3_3_Core, QOpenGLContext {
 public:
    
   CellDecomposition();

   void clear();
   void addCell(voro::voronoicell_neighbor& c, double x, double y, double z, int pid, bool outside);

   void renderCells();
   void renderParticles();
   
   void fullMeshDecomposition();
   void setShader(QOpenGLShaderProgram* shader) {cellShader = shader;} 
   float* getMin() {return min;}
   float* getMax() {return max;}
   
   void initializeSphereVAO(unsigned int numSubdivisions);
   void setNumCells(int n);

   void updateMesh(const std::vector<int>& newC, const std::vector<int>& oldC);
   

   std::vector<vorocell>* getCells() {return &cells;}
   std::map<std::pair<int,int>, vorolink>* getLinks() {return &links;}
   std::set<std::pair<int,int>>* getExteriorLinks() {return &exteriorLinks;}

 private:
   std::vector<std::vector<std::vector<unsigned int>>> cellFaces; //Each cell has a set of faces, which have a set of vertex indices inside the cell

   std::vector<GLuint> cellVAOs;
   std::vector<GLuint> bufferVerts;
   std::vector<GLuint> bufferIndices;
   QOpenGLShaderProgram* cellShader = nullptr;

   std::vector<vorocell> cells;
   std::map<std::pair<int,int>, vorolink> links;
   std::set<std::pair<int,int>> exteriorLinks;

   float min[3];
   float max[3];
   GLuint sphereVAO;
   GLuint sphereVertsVBO;
   GLuint sphereIndicesVBO;
   unsigned int sphereIndicesSize;

   void cellToMesh(std::vector<float>& v, std::map<int,voroFace>& f, GLuint& meshVAO, GLuint& bufferVerts, GLuint& bufferIndices, int& triangles);
   void computeBounds();  
   void addLinks(voro::voronoicell_neighbor& c, std::map<int,voroFace>& faces, int pid);
   void updateExternalLinks();
   void breakLink(std::pair<int,int> link);
   void removeComponent(int cell);


   int componentSize(int cell, int otherCell, bool& containsCore, bool& reachable);
   int componentSize_rec(int cell, int otherCell, bool& containsCore, bool& reachable, std::vector<bool>& visited);
  
};

#endif
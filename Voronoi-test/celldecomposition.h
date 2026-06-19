
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
#include "mechanicalModel.h"




class CellDecomposition: protected QOpenGLFunctions_3_3_Core, QOpenGLContext {
 public:
    
   CellDecomposition();

   void clear();
   
   void renderCells(int l);
   void renderParticles(int l);
   void renderLinks(int l, int mode, MechanicalModel& mechModel);
   void renderPaths(std::set<std::pair<int,int>>& paths, int l);

   void fullMeshDecomposition(int l);
   void setShader(QOpenGLShaderProgram* shader) {cellShader = shader;} 
   Vector3 getMin() {return min;}
   Vector3 getMax() {return max;}
   
   void initializeSphereVAO(unsigned int numSubdivisions);
   void initializeCylinderVAO();

   void updateMesh(const std::vector<int>& newC, const std::vector<int>& oldC);
   
   MultiResolutionGraph* getGraph() {return &graph;}

   void voronoiDecomposition(std::vector<float>& v, std::vector<uint>& f, const HeightField *hf, int multiRes_factor, 
                            Vector3 core_center, Vector3 core_range, int zSamples, bool furthest = true); 
   void toyVoronoi(const HeightField *hf) {graph.toyVoronoi(hf);};

 private:
   std::vector<std::vector<GLuint>> cellVAOs;
   std::vector<std::vector<GLuint>> bufferVerts;
   std::vector<std::vector<GLuint>> bufferIndices;
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
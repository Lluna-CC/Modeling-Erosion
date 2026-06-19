#include "celldecomposition.h"
#include<float.h>
#include<cmath>
#include<fstream>


CellDecomposition::CellDecomposition() {
    initializeOpenGLFunctions();
    
    cellVAOs.resize(graph.getLevels());
    bufferVerts.resize(graph.getLevels());
    bufferIndices.resize(graph.getLevels());
}


//Utility function 
float minMaxDistance(std::vector<float>& v) {
    float min[3], max[3], diff[3];
    min[0] = FLT_MAX;
    min[1] = FLT_MAX;
    min[2] = FLT_MAX;

    max[0] = - FLT_MAX;
    max[1] = - FLT_MAX;
    max[2] = - FLT_MAX;

    for (int i = 0; i < v.size(); i +=3) {
        for (int k = 0; k < 3; ++k) {
                if (v[i + k] < min[k]) min[k] = v[i + k];
                if (v[i + k] > max[k]) max[k] = v[i + k];
            }
    }
    for (int k = 0; k < 3; ++k) diff[k] = max[k] - min[k];
    return diff[0]*diff[0] + diff[1]*diff[1] + diff[2]*diff[2];
}


bool writeMesh(const std::string &filename, std::vector<float>& vertices, std::vector<unsigned int>& triangles) {
    std::ofstream ofs;
    ofs.open(filename);
    ofs << "ply\n";
    ofs << "format binary_little_endian 1.0\n";
    ofs << "element vertex " + std::to_string(vertices.size()/3) + "\n";
    ofs << "property float x\n";
    ofs << "property float y\n";
    ofs << "property float z\n";
    ofs << "element face " + std::to_string(triangles.size()) + "\n";
    ofs << "property list uchar uint vertex_indices\n";
    ofs << "end_header\n";
    char const * buff;
    unsigned char triangles_per_face = 3;
    for (int i = 0; i < vertices.size(); i += 3){
        
        buff = reinterpret_cast<char const *>(&vertices[i]);
        ofs.write(buff,sizeof(float));
        buff = reinterpret_cast<char const *>(&vertices[i + 1]);
        ofs.write(buff,sizeof(float));
        buff = reinterpret_cast<char const *>(&vertices[i + 2]);
        ofs.write(buff,sizeof(float));
      
    } 
    for (int i = 0; i < triangles.size(); i += 3) {
        buff = reinterpret_cast<char const *>(&triangles_per_face);
        ofs.write(buff,sizeof(unsigned char));


        for (int j = 0; j < 3; ++j) {    
            buff = reinterpret_cast<char const *>(&triangles[i + j]);
            ofs.write(buff,sizeof(unsigned int));    
    
        }

    }
        

    ofs.close();

    return false;
}


void CellDecomposition::renderCells(int l) {
    QMatrix4x4 model;
    std::vector<vorocell>& cells = graph.getCells(l);
    
    model.setToIdentity();
    glUniformMatrix4fv(glGetUniformLocation(cellShader -> programId(), "ModelMatrix"), 1, GL_FALSE, model.data()); 
    glUniform3f(glGetUniformLocation(cellShader -> programId(), "u_color"), 1.0f, 1.0f,1.0f);
    //int renderedCells = 0;
    for (int i = 0; i < cells.size(); ++i) {

        if (cells[i].state == AIR || !cells[i].isExterior) continue;
        glBindVertexArray(cellVAOs[l][i]);
        glDrawElements(GL_TRIANGLES, cells[i].nTriangles * 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
       //++renderedCells;

    }
    //std::cout << "Rendering " << renderedCells << " cells" << std::endl;

}

void CellDecomposition::renderLinks(int l, int mode, MechanicalModel& mechModel) {
    QMatrix4x4 model;
    std::vector<vorocell>& cells = graph.getCells(l);
    std::map<std::pair<int,int>, vorolink>& links = graph.getLinks(l);
    
    glUniform3f(glGetUniformLocation(cellShader -> programId(), "u_color"), 1.0f, 1.0f,1.0f);
    //int renderedCells = 0;
    for (int i = 0; i < cells.size(); ++i) {
        if (!cells[i].isExterior || cells[i].state == AIR) continue;
        model.setToIdentity();
        model.translate((float) cells[i].centroid[0], (float) cells[i].centroid[1], (float) cells[i].centroid[2]);
        model.scale(0.35,0.35,0.35);
        model.translate(-(float) cells[i].centroid[0], -(float) cells[i].centroid[1], -(float) cells[i].centroid[2]);

        glUniformMatrix4fv(glGetUniformLocation(cellShader -> programId(), "ModelMatrix"), 1, GL_FALSE, model.data()); 

        if (!cells[i].isExterior || cells[i].state == AIR) continue;
        glBindVertexArray(cellVAOs[l][i]);
        glDrawElements(GL_TRIANGLES, cells[i].nTriangles * 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
       //++renderedCells;

    }

    glBindVertexArray(cylinderVAO);
    

    for (int i = 0; i < cells.size(); ++i) {  
        if (!cells[i].isExterior || cells[i].state == AIR) continue;
        
        for (int j = 0; j < cells[i].neighbors.size(); ++j) {
            int neigh = cells[i].neighbors[j];
            if (neigh < i) continue;
            
            std::pair<int,int> key;
            if (i < neigh) key = std::make_pair(i, neigh);
            else key = std::make_pair(neigh, i);
            if (links.find(key) == links.end()) continue;

            vorolink& l = links[key];
            if (l.state == BROKEN || l.state == EXTERIOR) continue;
            
            float t;
            float D;
            switch (mode) {
                case 0:
                    t = l.life;
                    glUniform3f(glGetUniformLocation(cellShader -> programId(), "u_color"), 1.0f - t, t,0.0f);
                    
                    break;
                case 1:
                    D = 1 - l.life;
                    t = 1 - l.normalStress/mechModel.getTmax(D);
                    std::cout << "Link Normal Stress: " << l.normalStress << " AND: " << l.normalStress/mechModel.getTmax(D) << std::endl;
                    glUniform3f(glGetUniformLocation(cellShader -> programId(), "u_color"), 1.0f - t, t,0.0f);
                    break;
                case 2:
                    D = 1 - l.life;
                    t = 1 - l.shearStress/(mechModel.getShearC(D) - l.normalStress*mechModel.getTanPhi());
                    std::cout << "Link Shear Stress: " << l.shearStress << " AND: " << l.shearStress/(mechModel.getShearC(D) - l.normalStress*mechModel.getTanPhi()) << std::endl;
                    glUniform3f(glGetUniformLocation(cellShader -> programId(), "u_color"), 1.0f - t, t,0.0f);
                    break;
                default:
                    glUniform3f(glGetUniformLocation(cellShader -> programId(), "u_color"), 0.0f, 1.0f,0.0f);
                    break;
            }
            
            
            float dist = Norm(cells[neigh].centroid - cells[i].centroid);
            Vector3 dir = Normalized(cells[neigh].centroid - cells[i].centroid);
            float angle = acos(dot(Vector3(0,0,1),dir)) *360/(2*M_PI);
            Vector3 axis = cross(Vector3(0,0,1),dir);
            Vector3 centr = cells[i].centroid + dir*dist/2;

            QMatrix4x4 model;
            model.setToIdentity();
            model.translate((float) centr[0], (float) centr[1], (float) centr[2]);
            model.rotate(angle, axis[0], axis[1], axis[2]);
            model.scale(0.25,0.25,dist/2);

            //std::cout << particles[i] << " " << particles[i + 1] << " " << particles [i + 2] << std::endl;
            glUniformMatrix4fv(glGetUniformLocation(cellShader -> programId(), "ModelMatrix"), 1, GL_FALSE, model.data()); 

            glDrawElements(GL_TRIANGLES, 12*3, GL_UNSIGNED_INT, 0);
        }
        
    }
    glBindVertexArray(0);
}

void CellDecomposition::fullMeshDecomposition(int l) {
    computeBounds();
    graph.updateExternalLinks();
    graph.updateSolidCells(l);
    std::vector<vorocell>& cells = graph.getCells(l);

    float diff[3];
    for (int k = 0; k < 3; ++k) diff[k] = max[k] - min[k];
    float boxDist = diff[0]*diff[0] + diff[1]*diff[1] + diff[2]*diff[2];

    cellVAOs[l].resize(cells.size());
    bufferVerts[l].resize(cells.size());
    bufferIndices[l].resize(cells.size());
    
    for (int i = 0; i < cells.size(); ++i) {
        
        
        //std::cout << "Current Mesh Iteration: " << i << std::endl;
        if (cells[i].state == AIR || cells[i].state == DISCARDED) continue;
        float cellDist = minMaxDistance(cells[i].vertices);
        if (cellDist > 0.85*boxDist) continue;

        cellToMesh(cells[i].vertices, cells[i].faceData, cellVAOs[l][i], bufferVerts[l][i], bufferIndices[l][i], cells[i].nTriangles);
    }
    std::cout << "Models Created" << std::endl;
    
}

void CellDecomposition::computeBounds() {
    graph.computeBounds();
    min = graph.getMin();
    max = graph.getMax();
}


void CellDecomposition::cellToMesh(std::vector<float>& v, std::map<int,voroFace>& f, GLuint& meshVAO, GLuint& bufferVerts, GLuint& bufferIndices, int& triangles) {
    std::vector<unsigned int> indices;

    for (auto it = f.begin(); it != f.end(); ++it) {

        voroFace& face = it -> second;

        indices.push_back(face.vertices[0]);
        indices.push_back(face.vertices[2]);
        indices.push_back(face.vertices[1]);

        Vector3 v1 =  Vector3(v[3*face.vertices[0]], v[3*face.vertices[0] + 1], v[3*face.vertices[0] + 2]);
        Vector3 v2 =  Vector3(v[3*face.vertices[2]], v[3*face.vertices[2] + 1], v[3*face.vertices[2] + 2]);
        Vector3 v3 =  Vector3(v[3*face.vertices[1]], v[3*face.vertices[1] + 1], v[3*face.vertices[1] + 2]);
        
        Vector3 a = v2 - v1;
        Vector3 b = v3 - v1;
        face.normal = Normalized(cross(a,b));
        double area = Norm(cross(a,b))/2;
        if (area < 1e-5) face.normal = Vector3(0,0,0);


        for (int j = 3; j < face.vertices.size(); ++j) {
            indices.push_back(face.vertices[0]);
            indices.push_back(face.vertices[j]);
            indices.push_back(face.vertices[j - 1]);
            
            v2 =  Vector3(v[3*face.vertices[j]], v[3*face.vertices[j] + 1], v[3*face.vertices[j] + 2]);
            v3 =  Vector3(v[3*face.vertices[j - 1]], v[3*face.vertices[j - 1] + 1], v[3*face.vertices[j - 1] + 2]);
        
            a = v2 - v1;
            b = v3 - v1;
            area += Norm(cross(a,b))/2; 
        }        

        face.area = area;
    }
    triangles = indices.size()/3;

    /*std::cout << "triangles: " << std::endl;
    for (int i = 0; i < indices.size(); ++i) {
        std::cout << indices[i] << ": " << v[3*indices[i]] << " " << v[3*indices[i] + 1] << " " << v[3*indices[i] + 2] << std::endl;  
    } */

    glGenVertexArrays(1, &meshVAO);
    glBindVertexArray(meshVAO);
 
    glUseProgram(cellShader -> programId());
    GLuint attribVertexLoc = glGetAttribLocation(cellShader -> programId(), "a_position");

	glGenBuffers(1, &bufferVerts);
	glBindBuffer(GL_ARRAY_BUFFER, bufferVerts);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * v.size(), &v[0], GL_STATIC_DRAW);
    glVertexAttribPointer(attribVertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(attribVertexLoc);

    glGenBuffers(1, &bufferIndices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferIndices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
	glUseProgram(0);

    //writeMesh("./PLYTests/cell1.ply", v, indices);
}

void CellDecomposition::clear() {
    
    cellVAOs.clear();
    bufferVerts.clear();
    bufferIndices.clear();

    graph.clear(); 
}


void CellDecomposition::renderParticles(int l) {
    
    glBindVertexArray(sphereVAO);
    std::vector<vorocell>& cells = graph.getCells(l);
    
    for (int i = 0; i < cells.size(); ++i) {  
        QMatrix4x4 model;
        model.setToIdentity();
        model.translate((float) cells[i].centroid[0], (float) cells[i].centroid[1], (float) cells[i].centroid[2]);
        model.scale(1.5,1.5,1.5);

        glUniformMatrix4fv(glGetUniformLocation(cellShader -> programId(), "ModelMatrix"), 1, GL_FALSE, model.data()); 
        if(cells[i].state == AIR) glUniform3f(glGetUniformLocation(cellShader -> programId(), "u_color"), 1.0f, 1.0f,1.0f);
        else if (cells[i].state == SOLID) glUniform3f(glGetUniformLocation(cellShader -> programId(), "u_color"), 1.0f, 0.45f,0.09f);
        else if (cells[i].state == CORE) glUniform3f(glGetUniformLocation(cellShader -> programId(), "u_color"), 0.364f, 0.247f,0.827f);
        else if (cells[i].state == DISCARDED) continue;

        glDrawElements(GL_TRIANGLES, sphereIndicesSize, GL_UNSIGNED_INT, 0);
    }

    glBindVertexArray(0);
    
}

void CellDecomposition::renderPaths(std::set<std::pair<int,int>>& paths, int l) {
    
    QMatrix4x4 model;
    std::vector<vorocell>& cells = graph.getCells(l);
    std::map<std::pair<int,int>, vorolink>& links = graph.getLinks(l);
    
    glUniform3f(glGetUniformLocation(cellShader -> programId(), "u_color"), 1.0f, 1.0f,1.0f);
    //int renderedCells = 0;
    for (auto it = paths.begin(); it != paths.end(); ++it) {
        if (links[*it].state == INTERIOR) {
            links[*it].state = MARKED;
            
        } 
        cells[(*it).first].marked = true;
        cells[(*it).second].marked = true;

    }

    for (int i = 0; i < cells.size(); ++i) {
        if (!cells[i].isExterior || cells[i].state == AIR) continue;
        model.setToIdentity();
        model.translate((float) cells[i].centroid[0], (float) cells[i].centroid[1], (float) cells[i].centroid[2]);
        model.scale(1.0,1.0,1.0);
        model.translate(-(float) cells[i].centroid[0], -(float) cells[i].centroid[1], -(float) cells[i].centroid[2]);

        glUniformMatrix4fv(glGetUniformLocation(cellShader -> programId(), "ModelMatrix"), 1, GL_FALSE, model.data()); 

        
        if (cells[i].marked) glUniform3f(glGetUniformLocation(cellShader -> programId(), "u_color"), 0.1f, 0.7f,0.9f);
        else glUniform3f(glGetUniformLocation(cellShader -> programId(), "u_color"), 1.0f, 1.0,1.0f);
        glBindVertexArray(cellVAOs[l][i]);
        glDrawElements(GL_TRIANGLES, cells[i].nTriangles * 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
       //++renderedCells;

    }

    /*    
    glBindVertexArray(cylinderVAO);
    

    for (int i = 0; i < cells.size(); ++i) {  
        if (!cells[i].isExterior || cells[i].state == AIR) continue;
        
        for (int j = 0; j < cells[i].neighbors.size(); ++j) {
            int neigh = cells[i].neighbors[j];
            if (neigh < i) continue;
            
            std::pair<int,int> key;
            if (i < neigh) key = std::make_pair(i, neigh);
            else key = std::make_pair(neigh, i);
            if (links.find(key) == links.end()) continue;

            if (links[key].state == BROKEN || links[key].state == EXTERIOR) continue;
            if (links[key].state == MARKED) glUniform3f(glGetUniformLocation(cellShader -> programId(), "u_color"), 0.1f, 0.5f,1.0f);
            else {
                float t = links[key].life;
                glUniform3f(glGetUniformLocation(cellShader -> programId(), "u_color"), 1.0f - t, t,0.0f);
            }
            
            float dist = Norm(cells[neigh].centroid - cells[i].centroid);
            Vector3 dir = Normalized(cells[neigh].centroid - cells[i].centroid);
            float angle = acos(dot(Vector3(0,0,1),dir)) *360/(2*M_PI);
            Vector3 axis = cross(Vector3(0,0,1),dir);
            Vector3 centr = cells[i].centroid + dir*dist/2;

            QMatrix4x4 model;
            model.setToIdentity();
            model.translate((float) centr[0], (float) centr[1], (float) centr[2]);
            model.rotate(angle, axis[0], axis[1], axis[2]);
            model.scale(0.25,0.25,dist/2);

            //std::cout << particles[i] << " " << particles[i + 1] << " " << particles [i + 2] << std::endl;
            glUniformMatrix4fv(glGetUniformLocation(cellShader -> programId(), "ModelMatrix"), 1, GL_FALSE, model.data()); 

            glDrawElements(GL_TRIANGLES, 12*3, GL_UNSIGNED_INT, 0);
        }
        
    } */
    glBindVertexArray(0);

    for (auto it = paths.begin(); it != paths.end(); ++it) {
        if (links[*it].state == MARKED) {
            links[*it].state = INTERIOR;
        
        } 
        cells[(*it).first].marked = false;
        cells[(*it).second].marked = false;
    }
        
}

void CellDecomposition::initializeSphereVAO(unsigned int numSubdivisions) {
        // adapted from: https://schneide.blog/2016/07/15/generating-an-icosphere-in-c/
    const float X=.525731112119133606f;
    const float Z=.850650808352039932f;
    const float N=0.f;

    std::vector<float> verts = {
        -X, N, Z,
        X, N, Z,
        -X, N,-Z,
        X, N,-Z,
        N, Z, X,
        N, Z,-X,
        N,-Z, X,
        N,-Z,-X,
        Z, X, N,
        -Z, X, N,
        Z,-X, N,
        -Z,-X, N
    };
    std::vector<unsigned int> tris = {
        0,1,4,  0,4,9,  9,4,5,  4,8,5,  4,1,8,
        8,1,10, 8,10,3, 5,8,3,  5,3,2,  2,3,7,
        7,3,10, 7,10,6, 7,6,11, 11,6,0, 0,6,1,
        6,10,1, 9,11,0, 9,2,11, 9,5,2,  7,11,2
    };

    for (int s = 0; s < numSubdivisions; s++) {
        
        // keep track of which edges have been already subdivided, since we'll visit them twice
        std::map<std::pair<unsigned int, unsigned int>, unsigned int> edgeVert;

        // for each triangle
        unsigned int currLevelTris = tris.size();
        for (unsigned int t = 0; t < currLevelTris; t += 3) {

            // for each edge between two vertices, create a new vertex if needed
            for (unsigned int i = 0; i < 3; i++) {
                unsigned int v1 = tris[t + i];
                unsigned int v2 = tris[t + (i + 1)%3];
                std::pair<unsigned int, unsigned int> p(v1, v2);

                // create midpoint vertex if not already done
                if (edgeVert.find(p) == edgeVert.end()) {

                    float p1[3] = {verts[3*v1], verts[3*v1 + 1], verts[3*v1 + 1]};
                    float p2[3] = {verts[3*v2], verts[3*v2 + 1], verts[3*v2 + 1]};
    
            
                    float newVert[3] = {(0.5f*(p1[0] + p2[0])),(0.5f*(p1[1] + p2[1])), (0.5f*(p1[2] + p2[2])) };
                    float vertNorm = newVert[0]*newVert[0] + newVert[1]*newVert[1] + newVert[2]*newVert[2]; 
                    vertNorm = sqrt(vertNorm);
                    for(int k = 0; k < 3; ++k) newVert[i] /= vertNorm;

                    unsigned int idx = verts.size()/3;
                    for(int k = 0; k < 3; ++k) verts.push_back(newVert[k]);

                    // record vertex index in both senses
                    edgeVert[p] = idx;
                    edgeVert[std::make_pair(v2, v1)] = idx;
                }
            }

            // subdivide triangle into four new triangles (3 new ones, reuse values for central)
            unsigned int v1 = tris[t];
            unsigned int v2 = tris[t+1];
            unsigned int v3 = tris[t+2];
            unsigned int m12 = edgeVert[std::make_pair(v1, v2)];
            unsigned int m23 = edgeVert[std::make_pair(v2, v3)];
            unsigned int m31 = edgeVert[std::make_pair(v3, v1)];
            tris.push_back(v1); tris.push_back(m12); tris.push_back(m31);
            tris.push_back(v2); tris.push_back(m23); tris.push_back(m12);
            tris.push_back(v3); tris.push_back(m31); tris.push_back(m23);
            tris[t] = m12;      tris[t+1] = m23;     tris[t+2] = m31;
        }
    }

    sphereIndicesSize = tris.size();
    
    glGenVertexArrays(1, &sphereVAO);
    glBindVertexArray(sphereVAO);
 
    glUseProgram(cellShader -> programId());
    GLuint attribVertexLoc = glGetAttribLocation(cellShader -> programId(), "a_position");
    

	glGenBuffers(1, &sphereVertsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, sphereVertsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * verts.size(), &verts[0], GL_STATIC_DRAW);
    glVertexAttribPointer(attribVertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(attribVertexLoc);

    glGenBuffers(1, &sphereIndicesVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphereIndicesVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * tris.size(), &tris[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
	glUseProgram(0);

    //writeMesh("./PLYTests/icosa.ply", verts, tris);
    //std::cout << "saved icosa" << std::endl;
}

void CellDecomposition::initializeCylinderVAO() {
        
    //std::cout << "CYLINDER" << std::endl;
    const float X=1.0;
    //const float Z=.850650808352039932f;
    const float N=0.f;

    std::vector<float> verts = {
        -X, -X, -X,
        -X, -X, X,
        -X, X, X,
        -X, X,-X,
        X,-X,-X,
        X, -X, X,
        X, X, X,
        X, X,-X
    };
    std::vector<unsigned int> tris = {
        0,1,2, 0,2,3, 0,3,4, 4,3,7, 4,6,5, 4,7,6,
        5,6,1, 6,2,1, 7,3,6, 3,2,6, 4,5,1, 4,1,0 
    };


    //sphereIndicesSize = tris.size();
    
    glGenVertexArrays(1, &cylinderVAO);
    glBindVertexArray(cylinderVAO);
 
    glUseProgram(cellShader -> programId());
    GLuint attribVertexLoc = glGetAttribLocation(cellShader -> programId(), "a_position");
    

	glGenBuffers(1, &cylinderVertsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, cylinderVertsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * verts.size(), &verts[0], GL_STATIC_DRAW);
    glVertexAttribPointer(attribVertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(attribVertexLoc);

    glGenBuffers(1, &cylinderIndicesVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cylinderIndicesVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * tris.size(), &tris[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
	glUseProgram(0);

    //writeMesh("./PLYTests/icosa.ply", verts, tris);
    //std::cout << "saved icosa" << std::endl;
}


void CellDecomposition::updateMesh(const std::vector<int>& newC, const std::vector<int>& oldC) {
    std::vector<vorocell>& cells = graph.getCells(0);
    for (int i = 0; i < newC.size(); ++i) {
        int k = newC[i];
        cells[k].isExterior = true;
        cellToMesh(cells[k].vertices, cells[k].faceData, cellVAOs[0][k], bufferVerts[0][k], bufferIndices[0][k], cells[k].nTriangles);
    }

    glUseProgram(cellShader -> programId());
    for (int i = 0; i < oldC.size(); ++i) {
        int k = oldC[i];
        cells[k].isExterior = false;
        glDeleteBuffers(1, &bufferVerts[0][k]);
        glDeleteBuffers(1, &bufferIndices[0][k]);
        glDeleteVertexArrays(1, &cellVAOs[0][k]);
	    
    }
    glUseProgram(0);
}

void CellDecomposition::voronoiDecomposition(std::vector<float>& v, std::vector<uint>& f, const HeightField *hf, int multiRes_factor, 
                                            Vector3 core_center, Vector3 core_range, int zSamples, bool furthest) {

    if (furthest) graph.multiLevelVoronoiDecompositionFurthestPoint(v,f,hf, multiRes_factor, core_center, core_range, zSamples);
    else graph.multiLevelVoronoiDecompositionGridSampling(v,f,hf, 2, core_center, core_range, zSamples);
}
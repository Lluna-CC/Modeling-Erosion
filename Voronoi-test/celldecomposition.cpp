#include "celldecomposition.h"
#include<float.h>
#include<cmath>
#include<fstream>


CellDecomposition::CellDecomposition() {
    initializeOpenGLFunctions();
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

void CellDecomposition::addCell(voro::voronoicell_neighbor& c, double x, double y, double z, int pid, bool outside) {
    c.neighbors(cells[pid].neighbors);

    std::vector<int> auxiliarFaces;
    c.face_vertices(auxiliarFaces);
    int i = 0;
    int f = 0;

    
    while (i < auxiliarFaces.size()) {
        int nV = auxiliarFaces[i];
        voroFace face;
        face.vertices = std::vector<unsigned int>(nV);
        int faceID = cells[pid].neighbors[f];
        cells[pid].faceData[faceID] = face;
        
        
        for (int j = 1; j <= nV; ++j) {
            cells[pid].faceData[faceID].vertices[j - 1] = auxiliarFaces[i + j];
        }
        
        
        i = i + nV + 1;
        ++f;
    }

    
    
    
    std::vector<double> aux;
    c.vertices(x,y,z, aux);

    cells[pid].vertices.resize(aux.size());
    for (int i = 0; i < aux.size(); ++i) cells[pid].vertices[i] = (float) aux[i]; 
    cells[pid].centroid[0] = x;
    cells[pid].centroid[1] = y;
    cells[pid].centroid[2] = z;
    if (outside) {
        cells[pid].state = AIR;
    }

    
    addLinks(c,cells[pid].faceData, pid);
}


void CellDecomposition::renderCells() {
    QMatrix4x4 model;
    model.setToIdentity();
    glUniformMatrix4fv(glGetUniformLocation(cellShader -> programId(), "ModelMatrix"), 1, GL_FALSE, model.data()); 
    
    //int renderedCells = 0;
    for (int i = 0; i < cells.size(); ++i) {

        if (!cells[i].isExterior || cells[i].state == AIR) continue;
        glBindVertexArray(cellVAOs[i]);
        glDrawElements(GL_TRIANGLES, cells[i].nTriangles * 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
       //++renderedCells;

    }
    //std::cout << "Rendering " << renderedCells << " cells" << std::endl;

}

void CellDecomposition::fullMeshDecomposition() {
    computeBounds();
    updateExternalLinks();

    float diff[3];
    for (int k = 0; k < 3; ++k) diff[k] = max[k] - min[k];
    float boxDist = diff[0]*diff[0] + diff[1]*diff[1] + diff[2]*diff[2];

    cellVAOs.resize(cells.size());
    bufferVerts.resize(cells.size());
    bufferIndices.resize(cells.size());
    
    for (int i = 0; i < cells.size(); ++i) {
        
        
        //std::cout << "Current Mesh Iteration: " << i << std::endl;
        if (!cells[i].isExterior || cells[i].state == AIR) continue;
        float cellDist = minMaxDistance(cells[i].vertices);
        if (cellDist > 0.85*boxDist) continue;

        cellToMesh(cells[i].vertices, cells[i].faceData, cellVAOs[i], bufferVerts[i], bufferIndices[i], cells[i].nTriangles);
    }
    std::cout << "Models Created" << std::endl;
    
}

void CellDecomposition::computeBounds() {
    min[0] = FLT_MAX;
    min[1] = FLT_MAX;
    min[2] = FLT_MAX;

    max[0] = - FLT_MAX;
    max[1] = - FLT_MAX;
    max[2] = - FLT_MAX;
    for (int i = 0; i < cells.size(); ++i) {
        for (int j = 0; j < cells[i].vertices.size(); j += 3) {
            for (int k = 0; k < 3; ++k) {
                if (cells[i].vertices[j + k] < min[k]) min[k] = cells[i].vertices[j + k];
                if (cells[i].vertices[j + k] > max[k]) max[k] = cells[i].vertices[j + k];
            }
        }
    }

    std::cout << "cell max and min" << std::endl;
    std::cout << "min: " << min[0] << " " << min[1] << " " << min[2] << std::endl;
    std::cout << "max: " << max[0] << " " << max[1] << " " << max[2] << std::endl;
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
        if (area == 0) face.normal = Vector3(0,0,0);


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

    cells.clear(); 
}


void CellDecomposition::renderParticles() {
    
    glBindVertexArray(sphereVAO);

    for (int i = 0; i < cells.size(); ++i) {  
        QMatrix4x4 model;
        model.setToIdentity();
        model.translate((float) cells[i].centroid[0], (float) cells[i].centroid[1], (float) cells[i].centroid[2]);
        model.scale(2.0,2.0,2.0);

        //std::cout << particles[i] << " " << particles[i + 1] << " " << particles [i + 2] << std::endl;
        glUniformMatrix4fv(glGetUniformLocation(cellShader -> programId(), "ModelMatrix"), 1, GL_FALSE, model.data()); 

        glDrawElements(GL_TRIANGLES, sphereIndicesSize, GL_UNSIGNED_INT, 0);
    }
    glBindVertexArray(0);
    
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
        0,4,1,  0,9,4,  9,5,4,  4,5,8,  4,8,1,
        8,10,1, 8,3,10, 5,3,8,  5,2,3,  2,7,3,
        7,10,3, 7,6,10, 7,11,6, 11,0,6, 0,1,6,
        6,1,10, 9,0,11, 9,11,2, 9,2,5,  7,2,11
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

void CellDecomposition::setNumCells(int n) {
    cells.resize(n);

}

void CellDecomposition::addLinks(voro::voronoicell_neighbor& c, std::map<int,voroFace>& faces, int pid) {
    int edg = -1;
    for (auto it = faces.begin(); it != faces.end(); ++it) {
        voroFace& face = it -> second; 

        for (int k = 0; k < c.nu[face.vertices[0]]; ++k) {
                if (c.ed[face.vertices[0]][k] == face.vertices[1]) {
                    edg = k;
                    break;
                } 
        }
        int faceID = c.ne[face.vertices[0]][edg];
        std::pair<int,int> key;
        
        if (links.find(std::make_pair(pid, faceID)) != links.end()) key = std::make_pair(pid, faceID); 
        else key = std::make_pair(faceID,pid);

        
        if (faceID < 0 || cells[faceID].state == AIR) {
            links[key].state = EXTERIOR;
            cells[pid].isExterior = true;
        }

        for (int j = 0; j < face.vertices.size(); ++j) {
            
            for (int k = 0; k < c.nu[face.vertices[(j + 1)%face.vertices.size()]]; ++k) {
                if (c.ed[face.vertices[(j + 1)%face.vertices.size()]][k] == face.vertices[j]) {
                    edg = k;
                    break;
                } 
            }
            

            int neighID = c.ne[face.vertices[(j + 1)%face.vertices.size()]][edg];
            std::pair<int,int> neighKey;
            if (links.find(std::make_pair(pid, neighID)) != links.end()) neighKey = std::make_pair(pid, neighID);
            else  {
                neighKey = std::make_pair(neighID, pid);
                if (links.find(std::make_pair(neighID, pid)) == links.end()) links[neighKey].neighbors = std::vector<std::pair<int,int>>();
            } 

            links[key].neighbors.push_back(neighKey);
            //std::cout << "face: " << i << " ID: " << c.ne[face[(j + 1)%face.size()]][edg] << std::endl;   
        }
        
    }
    
}

void CellDecomposition::breakLink(std::pair<int,int> link) {
    
    //Delete Cell connection
    if (link.first >= 0 && link.second >= 0) {
        for (int i = 0; i < cells[link.first].neighbors.size(); ++i) {
            if (cells[link.first].neighbors[i] == link.second) {
                cells[link.first].neighbors[i] = cells[link.first].neighbors[cells[link.first].neighbors.size() - 1];
                cells[link.first].neighbors.pop_back(); 
            }
        }

        for (int i = 0; i < cells[link.second].neighbors.size(); ++i) {
            if (cells[link.second].neighbors[i] == link.first) {
                cells[link.second].neighbors[i] = cells[link.second].neighbors[cells[link.second].neighbors.size() - 1];
                cells[link.second].neighbors.pop_back(); 
            }
        }
    }

    //Delete edge, ask(?)
    /*
    std::vector<std::pair<int,int>> linkNeighbors;
    links.erase(link);
    for (int i = 0; i < linkNeighbors.size(); ++i) {
        std::pair<int,int> act = linkNeighbors[i];
        for (int j = 0; j < links[act].neighbors.size(); ++j) {
            if (links[act].neighbors[j] == link) {
                links[act].neighbors[j] = links[act].neighbors[links[act].neighbors.size() - 1];
                links[act].neighbors.pop_back();
            }
        }
    }*/

    //Check connected components
    if (link.first >= 0 && link.second >= 0) {
        bool containsCore_first, reachable;
        int firstComp_count = componentSize(link.first, link.second, containsCore_first, reachable);
        if (!reachable) {
            bool containsCore_second;
            int secondComp_count = componentSize(link.second, link.first, containsCore_second, reachable);
            
            if (!containsCore_first && containsCore_second) {
                //Remove first component
                removeComponent(link.first);
            }
            else if (containsCore_first && !containsCore_second) {
                //Remove Second Component
                removeComponent(link.second);
            }

            else if (!containsCore_first && !containsCore_second) {
                if (firstComp_count > secondComp_count) {
                    removeComponent(link.second);
                }
                else  {
                    removeComponent(link.first);
                }
            }
        }
    }

    //Update external links
    updateExternalLinks();
    

}

int CellDecomposition::componentSize(int cell, int otherCell, bool& containsCore, bool& reachable) {
    std::vector<bool> visited(cells.size(), false);
    containsCore = false;
    reachable = false;
    return componentSize_rec(cell, otherCell, containsCore, reachable, visited);
}

int CellDecomposition::componentSize_rec(int cell, int otherCell, bool& containsCore, bool& reachable, std::vector<bool>& visited) {
    int count = 1;
    visited[cell] = true;
    if (cells[cell].state == CORE) containsCore = true;
    if (cell == otherCell) reachable = true;

    for (int i = 0; i < cells[cell].neighbors.size(); ++i) {
        int next = cells[cell].neighbors[i];
        if (next < 0) continue;
        
        if (!visited[next]) count += componentSize_rec(next, otherCell, containsCore, reachable, visited); 
    }

    return count;
}

void CellDecomposition::removeComponent(int cell) {
    cells[cell].state = AIR;

    for (int i = 0; i < cells[cell].neighbors.size(); ++i) {
        int next = cells[cell].neighbors[i];
        if (next < 0) continue;
        if (cells[next].state != AIR) removeComponent(next); 
    }

    //FIX LINKS
}

void CellDecomposition::updateExternalLinks() {

    for (int i = 0; i < cells.size(); ++i) {
        for (int k = 0; k < cells[i].neighbors.size(); ++k) {
            if (cells[i].neighbors[k] > 0 && cells[cells[i].neighbors[k]].state == AIR) {
                cells[i].isExterior = true;     
                break;
            }
        }
    }

    for (auto it = links.begin(); it != links.end();) {
        std::pair<int,int>  key = it -> first;
        ++it;

        if ( (key.first < 0 || cells[key.first].state == AIR) && ( key.second < 0 ||cells[key.second].state == AIR) )  {
            links.erase(key);
            exteriorLinks.erase(key);

            
            std::vector<std::pair<int,int>> linkNeighbors;
            for (int i = 0; i < linkNeighbors.size(); ++i) {
                std::pair<int,int> act = linkNeighbors[i];
                for (int j = 0; j < links[act].neighbors.size(); ++j) {
                    if (links[act].neighbors[j] == key) {
                        links[act].neighbors[j] = links[act].neighbors[links[act].neighbors.size() - 1];
                        links[act].neighbors.pop_back();
                    }
                }
            }
        }

        else if ((key.first > 0 && cells[key.first].state == AIR) || (key.second > 0 && cells[key.second].state == AIR))  {
            links[key].state = EXTERIOR;
            exteriorLinks.insert(key);
        }

    }
    
}

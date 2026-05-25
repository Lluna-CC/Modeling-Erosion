#include "cellGraph.h"
#include<float.h>

void CellGraph::addCell(voro::voronoicell_neighbor& c, double x, double y, double z, int pid, bool outside) {
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

void CellGraph::setNumCells(int n) {
    cells.resize(n);
}

bool CellGraph::breakLink(std::pair<int,int> link) {return false;}
void CellGraph::removeComponent(int cell) {}
int CellGraph::componentSize(int cell, int otherCell, bool& containsCore, bool& reachable, bool& exterior) {return -1;}
void CellGraph::updateExternalLinks() {
    for (int i = 0; i < cells.size(); ++i) {
        if (cells[i].state == AIR) continue;
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
            
            
            for (int i = 0; i < links[key].neighbors.size(); ++i) {
                std::pair<int,int> act = links[key].neighbors[i];
                for (int j = 0; j < links[act].neighbors.size();) {
                    if (links[act].neighbors[j] == key) {
                        links[act].neighbors[j] = links[act].neighbors[links[act].neighbors.size() - 1];
                        links[act].neighbors.pop_back();
                    }
                    else ++j;
                }
            }
            links.erase(key);
            exteriorLinks.erase(key);
        }

        else if ((key.first > 0 && cells[key.first].state == AIR) || (key.second > 0 && cells[key.second].state == AIR))  {
            links[key].state = EXTERIOR;
            links[key].life = 0.0;
            exteriorLinks.insert(key);
            
        }

    }
    
} 

void CellGraph::addLinks(voro::voronoicell_neighbor& c, std::map<int,voroFace>& faces, int pid) {

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


void CellGraph::computeBounds() {
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

    /*std::cout << "cell max and min" << std::endl;
    std::cout << "min: " << min[0] << " " << min[1] << " " << min[2] << std::endl;
    std::cout << "max: " << max[0] << " " << max[1] << " " << max[2] << std::endl;*/
}

void CellGraph::clear() {
    cells.clear();
    links.clear();
    exteriorLinks.clear();
}
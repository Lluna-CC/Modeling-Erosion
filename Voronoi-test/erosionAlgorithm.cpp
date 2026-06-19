#include<erosionAlgorithm.h>
#include<random>
#include<queue>

ErosionAlgorithm::ErosionAlgorithm() {
    
}

ErosionAlgorithm::ErosionAlgorithm(MultiResolutionGraph* g, int workLevel, double L) {

    graph = g;
    level = workLevel;
    model.initializeModel(g -> getCells(level), g -> getLinks(level), g -> getSolidCells(level)); 
    model.setAvgLen(L); 
    computeAverageArea();               
}

double ErosionAlgorithm::resistanceField(double x, double y, double z) {
    return std::sin(x + y + z);
}

Vector3 ErosionAlgorithm::sampleDirection(double theta_base, double phi_base) {
    //std::random_device rd;
    //std::mt19937_64 generator{rd()};

    //std::normal_distribution theta_dist{M_PI/4, M_PI/8};
    //std::uniform_real_distribution<double> phi_dist(0.0,2*M_PI);

    //double theta = theta_dist(generator);
    //double phi = theta_dist(generator);
    
    return Normalized(-Vector3(std::sin(theta_base)*std::cos(phi_base),std::sin(theta_base)*std::sin(phi_base),std::cos(theta_base)));
}


void ErosionAlgorithm::getLinkDistibution(Vector3 dir) {
    std::set<std::pair<int,int>>& exteriorLinks = graph -> getExteriorLinks(level);
    weights.resize(exteriorLinks.size());
    keys.resize(exteriorLinks.size());
    std::vector<vorocell>& cells = graph -> getCells(level);


    int i = 0;
    for (auto it = exteriorLinks.begin(); it != exteriorLinks.end(); ++it) {
        keys[i] = *it;

        int first, second;
        if(it -> first < 0 || cells[it -> first].state == AIR) {first = it -> second; second = it -> first;} 
        else {first = it -> first; second = it -> second;}

        double area = cells[first].faceData[second].area;
        Vector3 normal = cells[first].faceData[second].normal;        

        weights[i] = area * dot(normal, dir);
        if (weights[i] < 0) weights[i] = 0;
        if (weights[i] != weights[i]) {
            weights[i] = 0;
            std::cout << "!!!" << std::endl;
        }
        ++i;
    }

}

void ErosionAlgorithm::setErosionDirection(double theta, double phi) {
    
    theta_dir = theta;
    phi_dir = phi;
    Vector3 inDir = sampleDirection(theta_dir, phi_dir);

    getLinkDistibution(inDir);
    externalLinkDistribution = std::discrete_distribution<int> (weights.begin(), weights.end());

}


bool ErosionAlgorithm::waterPath(std::set<std::pair<int,int>>& visited) {

    bool model_update = false;
    std::vector<vorocell>& cells = graph -> getCells(level);
    std::map<std::pair<int,int>, vorolink>& links = graph -> getLinks(level);

    std::random_device rd;
    std::mt19937 generator{rd()};
    std::uniform_real_distribution<double> rand(0.0,1.0);

    int firstLink_key = externalLinkDistribution(generator);

    double water = initialFlow;
    std::pair<int,int> actLink = keys[firstLink_key];
    //std::cout << "Starting from: " << firstLink_key << ": " << actLink.first << " " << actLink.second << std::endl;
    bool first = true;
    if (cells[actLink.first].state == AIR && cells[actLink.second].state == AIR) std::cout << "Okay, there is something weird going on" << std::endl;
  
    while (water > 0) {
        
        std::vector<double> propagationWeight(links[actLink].neighbors.size());
        Vector3 centr_a = cells[actLink.first].faceData[actLink.second].face_centroid;
        for(int i = 0; i < links[actLink].neighbors.size(); ++i) {
            int a,b; 
            std::pair<int,int> neigh = links[actLink].neighbors[i];
            if (links[neigh].state == EXTERIOR) {
                propagationWeight[i] = 0;
                continue;
            }

            Vector3 centr_b = cells[neigh.first].faceData[neigh.second].face_centroid;

            propagationWeight[i] = dot(g, Normalized(centr_b - centr_a));
            if (propagationWeight[i] < 0) propagationWeight[i] = 0;
            propagationWeight[i] *= (1 - links[links[actLink].neighbors[i]].life * resistanceField(centr_b[0], centr_b[1], centr_b[2]));
        }

        bool stop_path = true;
        for (int i = 0; i < propagationWeight.size(); ++i) {
            if (propagationWeight[i] > 0) {
                stop_path = false;
                break;
            }
        }
        if(stop_path) break;
        std::discrete_distribution<int> nextLinkDist(propagationWeight.begin(), propagationWeight.end());
        
        int next = nextLinkDist(generator);
        actLink = links[actLink].neighbors[next];
        visited.insert(actLink);
        //std::cout << "Next: " << actLink.first << " " << actLink.second << std::endl;

        //EROSION AND DAMAGE PART
        double link_area = actLink.first > 0 ? cells[actLink.first].faceData[actLink.second].area : cells[actLink.second].faceData[actLink.first].area;
        if (link_area < 1e-100) link_area = avg_area/100;
        double absorption = links[actLink].life > 0 ? link_area * k_solid + links[actLink].life * k_res : link_area*k_air;
        water = water - absorption;
        
        //std::cout << "Remaining water: " << water << std::endl;
        double full_absorption_probability = 1 - water/initialFlow;
        
        if (rand(generator) < full_absorption_probability) {
            water = 0;
        }

        double M_n = 1.0;
        double M_s = 0.0;
       
        if (useModel) {
            M_n = model.normalModifier(links[actLink]);
            M_s = model.shearModifier(links[actLink]);
        }

        links[actLink].life -= k_dmg*(absorption/link_area) * (M_n + M_s);
        
        if (links[actLink].life <= 0 && links[actLink].state != BROKEN && links[actLink].state != EXTERIOR) {
            //BREAK
            if(breakLink(actLink, true)) {
                model_update = true; 
                break;
            }
        }

        else if (useModel) {
            double D = 1 - links[actLink].life;
            if (links[actLink].normalStress > model.getTmax(D)) {
                if (breakLink(actLink), true) {
                    model_update = true;
                    break; 
                }
            }
            else if (links[actLink].normalStress < -model.getUCS(D)) {
                if (breakLink(actLink, true)) {
                    model_update = true;
                    break; 
                }
            }

            else if (links[actLink].shearStress > model.getShearC(D) - links[actLink].normalStress * model.getTanPhi()) {
                if (breakLink(actLink), true) {
                    model_update = true;
                    break; 
                }
            }
        }

        else if (links[actLink].life < k_break && links[actLink].state != BROKEN && links[actLink].state != EXTERIOR) {
            double break_prob = 1 - links[actLink].life/k_break;
            if (rand(generator) < break_prob) {
                links[actLink].life = 0;
                if (breakLink(actLink), true) {
                    model_update = true;
                    break; 
                }
                
            } 
        } 

        
        
    }

    //std::cout << "Water Path ended" << std::endl;
    return model_update;
}


bool ErosionAlgorithm::breakLink(std::pair<int,int> link, bool updateStresses) {
    //std::cout << "Breaking link: " << link.first << " " << link.second << std::endl;
    std::map<std::pair<int,int>, vorolink>& links = graph -> getLinks(level);
    std::vector<vorocell>& cells = graph -> getCells(level);
    //std::set<std::pair<int,int>>& exteriorLinks = graph -> getExteriorLinks(level);
    
    if (link.first < 0 || cells[link.first].state == AIR || link.second < 0 || cells[link.second].state == AIR) return false;
    links[link].state = BROKEN;
    model.removeLink(link, graph -> getCells(level), graph -> getSolidCells(level));


    //Check connected components
    bool update = false;
    if (link.first >= 0 && link.second >= 0) {
        bool containsCore_first, reachable, exterior_one;
        int firstComp_count = componentSize(link.first, link.second, containsCore_first, reachable, exterior_one);

        
        if (!reachable) {
            std::cout << "Seprated components !!" << std::endl;
            recentlyRemoved.clear();

            bool containsCore_second, exterior_two;
            int secondComp_count = componentSize(link.second, link.first, containsCore_second, reachable, exterior_two);
            
            //std::cout << "First size: " << firstComp_count << " Second size: " << secondComp_count << std::endl;
            if (!containsCore_first && containsCore_second) {
                //Remove first component
                update = exterior_one;
                //std::cout << "Removing first" << std::endl;
                removeComponent(link.first);
                graph -> updateSolidCells(level);
                model.initializeModel(graph -> getCells(level), graph -> getLinks(level), graph -> getSolidCells(level));
            }
            else if (containsCore_first && !containsCore_second) {
                //Remove Second Component
                update = exterior_two;
                //std::cout << "Removing second" << std::endl;
                removeComponent(link.second);
                graph -> updateSolidCells(level);
                model.initializeModel(graph -> getCells(level), graph -> getLinks(level), graph -> getSolidCells(level));
            }

            else if (!containsCore_first && !containsCore_second) {
                if (firstComp_count > secondComp_count) {
                    update = exterior_two;
                    std::cout << "Removing second" << std::endl;
                    removeComponent(link.second);
                }
                else  {
                    update = exterior_one;
                    std::cout << "Removing first" << std::endl;
                    removeComponent(link.first);
                }
                graph -> updateSolidCells(level);
                model.initializeModel(graph -> getCells(level), graph -> getLinks(level), graph -> getSolidCells(level));
            }

            
        }
    }

    
    if (useModel && updateStresses) computeStress();
    //Update external links
    if (update) {
        std::cout << "Updating Links" << std::endl;
        updateExternalLinks();
        
        Vector3 inDir = sampleDirection(theta_dir, phi_dir);

        getLinkDistibution(inDir);
        externalLinkDistribution = std::discrete_distribution<int> (weights.begin(), weights.end());
        
        return true;
    }
    

    else return false;
}

int ErosionAlgorithm::componentSize(int cell, int otherCell, bool& containsCore, bool& reachable, bool& exterior) {
    std::vector<vorocell>& cells = graph -> getCells(level);
    std::map<std::pair<int,int>, vorolink>& links = graph -> getLinks(level);
    std::vector<bool> visited(cells.size(), false);
    containsCore = false;
    reachable = false;
    exterior = false;
    std::queue<int> next_cells;
    visited[cell] = true;
    next_cells.push(cell);
    int count = 0;

    while (!next_cells.empty()) {
        int actCell = next_cells.front();
        next_cells.pop();

        count += 1;
        if (cells[actCell].state == CORE) containsCore = true;
        if (actCell == otherCell) {
            reachable = true;
            return -1;
        }

        for (int i = 0; i < cells[actCell].neighbors.size(); ++i) {
            int next = cells[actCell].neighbors[i];
            if (next < 0) continue;

            std::pair<int,int> key;
            if (actCell < next) key = std::make_pair(actCell, next);
            else key = std::make_pair(next, actCell);
            if (links.find(key) == links.end()) continue;

            if (links[key].state == EXTERIOR) {
                exterior = true;
                continue;
            }

            if (!visited[next] && links[key].state != BROKEN)  {
                visited[next] = true;
                next_cells.push(next);
            } 
            
        }
    }
    
    return count;
    
    //return componentSize_rec(cell, otherCell, containsCore, reachable, visited);
}

int ErosionAlgorithm::componentSize_rec(int cell, int otherCell, bool& containsCore, bool& reachable, std::vector<bool>& visited) { 
    return -1;
}

void ErosionAlgorithm::removeComponent(int cell) {
    std::vector<vorocell>& cells = graph -> getCells(level);
    std::map<std::pair<int,int>, vorolink>& links = graph -> getLinks(level);

    cells[cell].state = AIR;
    recentlyRemoved.insert(cell);
    if (level > 0) graph -> removeLowerLevel(level, cell);

    for (int i = 0; i < cells[cell].neighbors.size(); ++i) {
        int next = cells[cell].neighbors[i];
        if (next < 0) continue;

        std::pair<int,int> key;
        if (cell < next) key = std::make_pair(cell, next);
        else key = std::make_pair(next, cell);
        if (links.find(key) == links.end()) continue;

        if (cells[next].state != AIR && links[key].state != BROKEN) removeComponent(next); 
    }

    //FIX LINKS
}


void ErosionAlgorithm::updateExternalLinks() {
    std::vector<vorocell>& cells = graph -> getCells(level);
    std::map<std::pair<int,int>, vorolink>& links = graph -> getLinks(level);
    std::set<std::pair<int,int>>& exteriorLinks = graph -> getExteriorLinks(level);
    
    graph -> updateExternalCells(0);
    for (int i = 0; i < cells.size(); ++i) {
        if (cells[i].state == AIR || cells[i].state == DISCARDED) continue;
        for (int k = 0; k < cells[i].neighbors.size(); ++k) {
            if (cells[i].neighbors[k] < 0 || recentlyRemoved.find(cells[i].neighbors[k]) != recentlyRemoved.end()) {
                
                //graph -> updateLowerLevelCells(1, i);
                cells[i].isExterior = true;     
                break;
            }
        }
    }

    for (auto it = links.begin(); it != links.end();) {
        std::pair<int,int>  key = it -> first;
        ++it;

        if ( (key.first < 0 || cells[key.first].state == AIR) && ( key.second < 0 || cells[key.second].state == AIR) )  {
            
            
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

        else if ((key.first > 0 && recentlyRemoved.find(key.first) != recentlyRemoved.end()) || (key.second > 0 && recentlyRemoved.find(key.second) != recentlyRemoved.end()))  {
            links[key].state = EXTERIOR;
            exteriorLinks.insert(key);
        }
    }

}

void ErosionAlgorithm::computeAverageArea() {
    std::vector<vorocell>& cells = graph -> getCells(level);

    avg_area = 0;
    int total_faces = 0;
    for (int i = 0; i < cells.size(); ++i) {
        for (auto it = cells[i].faceData.begin(); it != cells[i].faceData.end(); ++it) {
            avg_area += it -> second.area;
            ++total_faces;
        }
    }
    avg_area = avg_area/total_faces;

    k_solid = k_solid/avg_area;
    k_air = k_air/avg_area;
    k_dmg *= avg_area;
}

void ErosionAlgorithm::computeStress() {
    if (graph == nullptr) return;
    
    std::vector<std::pair<int,int>> brokenLinks;
    model.computeEquilibra();
    model.updateLinkStresses(graph -> getLinks(level), graph -> getCells(level), graph -> getSolidCells(level), brokenLinks);
    for (int i = 0; i < brokenLinks.size(); ++i) {
        breakLink(brokenLinks[i], false);
    }
    if (brokenLinks.size() > 0) {
        
        computeStress();
    }
}


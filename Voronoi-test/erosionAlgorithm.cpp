#ifndef EROSIONALGORITHM_H
#define EROSIONALGORITHM_H
#include<erosionAlgorithm.h>
#include<random>
#include<queue>

ErosionAlgorithm::ErosionAlgorithm() {
    
}

ErosionAlgorithm::ErosionAlgorithm(std::vector<vorocell>* c, std::set<std::pair<int,int>>* el, std::map<std::pair<int,int>, vorolink>* l) {
    cells = c;
    exteriorLinks = el;
    links = l;

    
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
    weights.resize(exteriorLinks -> size());
    keys.resize(exteriorLinks -> size());

    //std::cout << "Number of keys!! " <<  exteriorLinks -> size() << std::endl;

    int i = 0;
    for (auto it = exteriorLinks -> begin(); it != exteriorLinks -> end(); ++it) {
        keys[i] = *it;

        int first, second;
        if(it -> first < 0 || (*cells)[it -> first].state == AIR) {first = it -> second; second = it -> first;} 
        else {first = it -> first; second = it -> second;}

        double area = (*cells)[first].faceData[second].area;
        Vector3 normal = (*cells)[first].faceData[second].normal;        

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
    

    Vector3 inDir = sampleDirection(0.0, 0.0);

    getLinkDistibution(inDir);
    externalLinkDistribution = std::discrete_distribution<int> (weights.begin(), weights.end());

}

void ErosionAlgorithm::waterPath() {

    std::cout << "STARTING WATER PATH" << std::endl;
    //std::cout << "MAX DIST: " << externalLinkDistribution.max() << " MIN: " << externalLinkDistribution.min() << std::endl;

    std::random_device rd;
    std::mt19937 generator{rd()};
    std::uniform_real_distribution<double> rand(0.0,1.0);

    int firstLink_key = externalLinkDistribution(generator);
    double water = initialFlow;
    std::pair<int,int> actLink = keys[firstLink_key];

    std::cout << "Starting from: " << firstLink_key << ": " << actLink.first << " " << actLink.second << std::endl;
    bool first = true;
    while (water > 0) {
        std::vector<double> propagationWeight((*links)[actLink].neighbors.size());
        for(int i = 0; i < (*links)[actLink].neighbors.size(); ++i) {
            int a,b; 
            std::pair<int,int> neigh = (*links)[actLink].neighbors[i];
            if (neigh.first == actLink.first || neigh.first == actLink.second) {
                a = neigh.first;
                b = neigh.second;
            }
            else {
                a = neigh.second;
                b = neigh.first;
            }

            Vector3 centr_a = (*cells)[a].centroid;
            Vector3 centr_b = (*cells)[b].centroid;

            propagationWeight[i] = dot(g, Normalized(centr_b - centr_a));
            if (propagationWeight[i] < 0) propagationWeight[i] = 0;
            propagationWeight[i] *= (1 - (*links)[(*links)[actLink].neighbors[i]].life * resistanceField(centr_b[0], centr_b[1], centr_b[2]));
        }

        std::discrete_distribution<int> nextLinkDist(propagationWeight.begin(), propagationWeight.end());
        
        int next = nextLinkDist(generator);
        actLink = (*links)[actLink].neighbors[next];
        std::cout << "Next: " << actLink.first << " " << actLink.second << std::endl;

        //EROSION AND DAMAGE PART
        double link_area = actLink.first > 0 ? (*cells)[actLink.first].faceData[actLink.second].area : (*cells)[actLink.second].faceData[actLink.first].area;
        double absorption = (*links)[actLink].life > 0 ? link_area * k_solid + (*links)[actLink].life * k_res : link_area*k_air;
        water = water - absorption;
        
        std::cout << "Remaining water: " << water << std::endl;
        double full_absorption_probability = 1 - water/initialFlow;
        
        if (rand(generator) < full_absorption_probability) {
            water = 0;
        }

        std::cout << "Link area: " << link_area << std::endl << std::endl;
        (*links)[actLink].life -= k_dmg*(absorption/link_area);
        if ((*links)[actLink].life <= 0 && (*links)[actLink].state != BROKEN) {
            //BREAK
            breakLink(actLink);
        }
        else if ((*links)[actLink].life < k_break && (*links)[actLink].state != BROKEN) {
            double break_prob = 1 - (*links)[actLink].life/k_break;
            if (rand(generator) < break_prob) {
                (*links)[actLink].life = 0;
                breakLink(actLink);
            } 
        }
        
    }

    std::cout << "Water Path ended" << std::endl;
}


void ErosionAlgorithm::breakLink(std::pair<int,int> link) {
    std::cout << "Breaking link: " << link.first << " " << link.second << std::endl;
    (*links)[link].state = BROKEN;
    //Delete Cell connection
    if (link.first >= 0 && link.second >= 0) {
        for (int i = 0; i < (*cells)[link.first].neighbors.size(); ++i) {
            if ((*cells)[link.first].neighbors[i] == link.second) {
                (*cells)[link.first].neighbors[i] = (*cells)[link.first].neighbors[(*cells)[link.first].neighbors.size() - 1];
                (*cells)[link.first].neighbors.pop_back(); 
            }
        }

        for (int i = 0; i < (*cells)[link.second].neighbors.size(); ++i) {
            if ((*cells)[link.second].neighbors[i] == link.first) {
                (*cells)[link.second].neighbors[i] = (*cells)[link.second].neighbors[(*cells)[link.second].neighbors.size() - 1];
                (*cells)[link.second].neighbors.pop_back(); 
            }
        }
    }

    
    else {
        //WE SHOULD NOT BE ABLE TO REMOVE EXTERIOR LINKS
    }

    std::cout << "Removed Link from cell graph" << std::endl;

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
        
        std::cout << "Analyzed components" << std::endl;
        if (!reachable) {
            std::cout << "Seprated components !!" << std::endl;
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

    std::cout << "Updating Links" << std::endl;
    //Update external links
    updateExternalLinks();
    

}

int ErosionAlgorithm::componentSize(int cell, int otherCell, bool& containsCore, bool& reachable) {
    std::vector<bool> visited((*cells).size(), false);
    containsCore = false;
    reachable = false;
    std::queue<int> next_cells;
    visited[cell] = true;
    next_cells.push(cell);
    int count = 0;

    while (!next_cells.empty()) {
        int actCell = next_cells.front();
        next_cells.pop();

        count += 1;
        if ((*cells)[actCell].state == CORE) containsCore = true;
        if (actCell == otherCell) reachable = true;

        for (int i = 0; i < (*cells)[actCell].neighbors.size(); ++i) {
            int next = (*cells)[actCell].neighbors[i];
            if (next < 0 || next >= (*cells).size()) continue;

            if (!visited[next] && (*cells)[next].state != AIR)  {
                visited[next] = true;
                next_cells.push(next);
            } 
            
        }
    }
    
    return count;
    
    //return componentSize_rec(cell, otherCell, containsCore, reachable, visited);
}

int ErosionAlgorithm::componentSize_rec(int cell, int otherCell, bool& containsCore, bool& reachable, std::vector<bool>& visited) { 
    int count = 1;
    visited[cell] = true;
    if ((*cells)[cell].state == CORE) containsCore = true;
    if (cell == otherCell) reachable = true;
    
    
    //std::cout << "Current: " << cell << std::endl;

    for (int i = 0; i < (*cells)[cell].neighbors.size(); ++i) {
        int next = (*cells)[cell].neighbors[i];
        if (next < 0 || next >= (*cells).size()) continue;

        if (!visited[next] && (*cells)[next].state != AIR) count += componentSize_rec(next, otherCell, containsCore, reachable, visited); 
        
    }

    //std::cout << "Count: " << count << std::endl;
    
    return count;
}

void ErosionAlgorithm::removeComponent(int cell) {
    (*cells)[cell].state = AIR;

    for (int i = 0; i < (*cells)[cell].neighbors.size(); ++i) {
        int next = (*cells)[cell].neighbors[i];
        if (next < 0) continue;
        if ((*cells)[next].state != AIR) removeComponent(next); 
    }

    //FIX LINKS
}


void ErosionAlgorithm::updateExternalLinks() {

    for (int i = 0; i < (*cells).size(); ++i) {
        for (int k = 0; k < (*cells)[i].neighbors.size(); ++k) {
            if ((*cells)[i].neighbors[k] < 0 || (*cells)[(*cells)[i].neighbors[k]].state == AIR) {
                (*cells)[i].isExterior = true;     
                break;
            }
        }
    }

    for (auto it = (*links).begin(); it != (*links).end();) {
        std::pair<int,int>  key = it -> first;
        ++it;

        if ( (key.first < 0 || (*cells)[key.first].state == AIR) && ( key.second < 0 || (*cells)[key.second].state == AIR) )  {
            links -> erase(key);
            exteriorLinks -> erase(key);

            
            std::vector<std::pair<int,int>> linkNeighbors;
            for (int i = 0; i < linkNeighbors.size(); ++i) {
                std::pair<int,int> act = linkNeighbors[i];
                for (int j = 0; j < (*links)[act].neighbors.size(); ++j) {
                    if ((*links)[act].neighbors[j] == key) {
                        (*links)[act].neighbors[j] = (*links)[act].neighbors[(*links)[act].neighbors.size() - 1];
                        (*links)[act].neighbors.pop_back();
                    }
                }
            }
        }

        else if ((key.first > 0 && (*cells)[key.first].state == AIR) || (key.second > 0 && (*cells)[key.second].state == AIR))  {
            (*links)[key].state = EXTERIOR;
            exteriorLinks -> insert(key);
        }
    }
}
#endif
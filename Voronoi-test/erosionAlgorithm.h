#include<celldecomposition.h>



class ErosionAlgorithm { 

  public:

    ErosionAlgorithm(MultiResolutionGraph* g, int workLevel = 0);
    ErosionAlgorithm();

    Vector3 sampleDirection(double theta_base, double phi_base);

    
    void setErosionDirection(double theta, double phi);
    bool waterPath(std::set<std::pair<int,int>>& visited);

    //Returns true if the model changed
    void getNewExteriorCells(std::vector<int>& newC, std::vector<int>& oldC) {
        newC = newExteriorCells;
        oldC = removedExteriorCells;
    }

  private:
    void getLinkDistibution(Vector3 dir);
  
    bool breakLink(std::pair<int,int > link);
    void removeComponent(int cell);
    int componentSize(int cell, int otherCell, bool& containsCore, bool& reachable, bool& exterior);
    int componentSize_rec(int cell, int otherCell, bool& containsCore, bool& reachable, std::vector<bool>& visited);
    void updateExternalLinks(); 
    double resistanceField(double x, double y, double z);
    void computeAverageArea();

    std::vector<double> weights; 
    std::vector<std::pair<int,int>> keys; 

  
    MultiResolutionGraph* graph;

    
    std::discrete_distribution<int> externalLinkDistribution;
  
    std::vector<int> newExteriorCells;
    std::vector<int> removedExteriorCells;

    double initialFlow = 10.0;
    Vector3 g = Vector3(0.0,0.0,-1.0);

    double k_air = 0.05;
    double k_solid = 0.1;
    double k_res = 0.25;
    double k_dmg = 0.5;
    double k_break = 0.4;
    double avg_area;
    double theta_dir;
    double phi_dir;

    int level;

  };

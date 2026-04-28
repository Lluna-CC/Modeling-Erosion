#include<celldecomposition.h>



class ErosionAlgorithm { 

  public:

    ErosionAlgorithm(std::vector<vorocell>* c, std::set<std::pair<int,int>>* el, std::map<std::pair<int,int>, vorolink>* l);
    ErosionAlgorithm();

    Vector3 sampleDirection();

    
    void algorithmInitialization(double initialFlow, Vector3 g = Vector3(0,0,-1));
    void waterPath();


  private:
    void getLinkDistibution(Vector3 dir);
  
    void breakLink(std::pair<int,int > link);
    void removeComponent(int cell);
    int componentSize(int cell, int otherCell, bool& containsCore, bool& reachable);
    int componentSize_rec(int cell, int otherCell, bool& containsCore, bool& reachable, std::vector<bool>& visited);
    void updateExternalLinks(); 
    
    std::vector<double> weights; 
    std::vector<std::pair<int,int>> keys; 

    std::vector<vorocell>* cells;
    std::set<std::pair<int,int>>* exteriorLinks;
    std::map<std::pair<int,int>, vorolink>* links;

    
    std::discrete_distribution<int> externalLinkDistribution;
  

    double initialFlow;
    Vector3 g;

    double k_air = 0.05;
    double k_solid = 0.1;
    double k_res = 0.25;
    double k_dmg = 0.5;
    double k_break = 0.4;
};

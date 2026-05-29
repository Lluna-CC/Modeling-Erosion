#include<celldecomposition.h>



class ErosionAlgorithm { 

  public:

    ErosionAlgorithm(std::vector<vorocell>* c, std::set<std::pair<int,int>>* el, std::map<std::pair<int,int>, vorolink>* l);
    ErosionAlgorithm();

    

    
    void setParams(double phi, double theta, Vector3 g = Vector3(0,0,-1));

    //Returns true if the model changed
    bool waterPath();


  private:
    void getLinkDistibution(Vector3 dir);
    Vector3 sampleDirection(double base_phi, double base_theta);
  
    void computeAverageArea();
    void breakLink(std::pair<int,int > link);
    void removeComponent(int cell);
    int componentSize(int cell, int otherCell, bool& containsCore, bool& reachable, bool& exterior);
    int componentSize_rec(int cell, int otherCell, bool& containsCore, bool& reachable, std::vector<bool>& visited);
    void updateExternalLinks(); 
    double resistanceField(double x, double y, double z);

    std::vector<double> weights; 
    std::vector<std::pair<int,int>> keys; 

    std::vector<vorocell>* cells;
    std::set<std::pair<int,int>>* exteriorLinks;
    std::map<std::pair<int,int>, vorolink>* links;

    
    std::discrete_distribution<int> externalLinkDistribution;
  

    double initialFlow = 50;
    Vector3 g;

    double k_air = 0.05;
    double k_solid = 0.1;
    double k_res = 0.25;
    double k_dmg = 0.5;
    double k_break = 0.4;
    double avg_area;
};

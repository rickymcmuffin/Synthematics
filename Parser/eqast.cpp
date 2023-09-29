#include "eqast.h"

EqAST::EqAST() {
  
}

EqAST::EqAST(std::string s, std::vector<std::string> yAs) {
  mainAST = Parser(s).parseExpression();

  for (int i = 0; i < yAs.size(); i++) {
    AST *yAST = Parser(yAs[i]).parseExpression();
    yAuxes.push_back(yAST);
  }
}
    
EqAST::EqAST(const EqAST& other){
    
};

EqAST::~EqAST() { 
    freeAST(mainAST); 
}

std::string EqAST::toString() { return unparseExpression(mainAST); }

double EqAST::getResult(double xVal, double fValue) {
  return resultExpression(mainAST, xVal, fValue, yAuxes);
}

    
EqAST& EqAST::operator=(const EqAST& other){
    std::cout << "called copy"<< std::endl;
    free(mainAST);
    for(int i = 0; i < yAuxes.size(); i++){
        free(yAuxes[i]);
    }
    mainAST = other.mainAST;
    yAuxes = other.yAuxes;
    return *this;
}

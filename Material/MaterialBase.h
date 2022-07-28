
#ifndef MATERIAL_BASE
#define MATERIAL_BASE



/**
 @defgroup mathstatement
 @brief Defines/implements the variational statement
 */

/**
 @brief Defines the variational statement interface
 @ingroup mathstatement
 
 A math statement involves computing the contribution to the stiffness matrix at an integration point\n
 Declaring the number of state variables \n
 Post processing the results
 */
class MaterialBase
{    
    int MathDim;
    
    int matid = 0;
    
public:
   
    static double gBigNumber;
    
    // Constructor of MaterialBase
    MaterialBase();
    
    // Copy constructor of MaterialBase
    MaterialBase(const MaterialBase &copy);
    
    // Operator of copy
    MaterialBase &operator=(const MaterialBase &copy);
    
    // Destructor of MaterialBase
    virtual ~MaterialBase();
    
    // Method for creating a copy of the element
    virtual MaterialBase *Clone() const = 0;
    
    // // Return the number of state variables
    // virtual int NState() const =0;
    
    // // Return the number of errors
    // virtual int NEvalErrors() const = 0;
    
    // // Method to implement integral over element's volume
    // virtual void Contribute(IntPointData &integrationpointdata, double weight, MatrixDouble &EK, MatrixDouble &EF) const = 0;
    
    // // Method to implement error over element's volume
    // virtual void ContributeError(IntPointData &integrationpointdata, VecDouble &u_exact, MatrixDouble &du_exact, VecDouble &errors) const = 0;
    
    // virtual void SetMatID(int indexmat){
    //     matid = indexmat;
    // }
    
    // virtual int GetMatID(){
    //     return matid;
    // }

    // virtual void SetDimension(int dim){
    //     MathDim = dim;
    // };
    
    // virtual int Dimension() const{
    //     return MathDim;
    // }; 
    
    
    // //Method to print MathStatement
    // virtual void Print(std::ostream &out);
    
    
};
#endif

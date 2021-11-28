#include "Line.h"

class Spline : public Line
{   
    public:

    Spline(const int& index, const std::string& name, std::vector<Point*> points, const bool& discretization = true);

    ~Spline();

    Spline* operator-();

    std::string getGmshCode() override;

};
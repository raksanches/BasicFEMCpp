#include "Line.h"

class Circle : public Line
{
    public:
    
    Circle(const int& index, const std::string& name, std::vector<Point*> points, const bool& discretization = true);

    ~Circle();

    Circle* operator-();

    std::string getGmshCode() override;

    Point* getMiddlePoint();
};
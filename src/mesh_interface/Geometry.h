#pragma once

#include "PlaneSurface.h"
#include "GeometricBoundaryCondition.h"
#include <unordered_map>

class Geometry
{
public:
	Geometry();

	Geometry(const int& index);

	~Geometry();

	int getIndex();

	int getNumberOfPoints();

	int getNumberOfLines();

	int getNumberOfLineLoops();

	int getNumberOfPlaneSurfaces();

	int getNumberOfBoundaryConditions(const std::string& type);

	Point* getPoint(const std::string& name);

	Line* getLine(const std::string& name);

	LineLoop* getLineLoop(const std::string& name);

	PlaneSurface* getPlaneSurface(const std::string& name);

	std::unordered_map<std::string, PlaneSurface*> getPlaneSurfaces();

	std::vector<GeometricBoundaryCondition*> getBoundaryConditions(const std::string& type);

	std::string getGmshCode();

	Point* addPoint(std::vector<double> coordinates, const double& lcar = 1.0, const bool& discretization = true);

	Line* addLine(std::vector<Point*> points, const bool& discretization = true);

	Circle* addCircle(std::vector<Point*> points, const bool& discretization = true);

	Spline* addSpline(std::vector<Point*> points, double(*function)(double), const int& ndiv, const bool& discretization = true);

	LineLoop* addLineLoop(std::vector<Line*> lines);

	PlaneSurface* addPlaneSurface(LineLoop* lineLoop, double thickness = 1.0);

	PlaneSurface* addPlaneSurface(std::vector<Line*> lines, double thickness = 1.0);

	void appendGmshCode(std::string text);

	void transfiniteLine(std::vector<Line*> lines, const int& divisions, const double& progression = 1);

	void transfiniteSurface(std::vector<PlaneSurface*> surfaces, std::string oientation = "Left", std::vector<Point*> points = std::vector<Point*>());

	void addBoundaryCondition(const std::string& type, Point* point, const std::vector<double>& componentX = std::vector<double>(), const std::vector<double>& componentY = std::vector<double>(), const std::string& referenceSystem = "GLOBAL", const std::string& method = "STRONG", const double& penaltyParameter = 1.0e6);
	
	void addBoundaryCondition(const std::string& type, Line* line, const std::vector<double>& componentX = std::vector<double>(), const std::vector<double>& componentY = std::vector<double>(), const std::string& referenceSystem = "GLOBAL", const std::string& method = "STRONG", const double& penaltyParameter = 1.0e6);

private:
	int index_;
	std::unordered_map<std::string, Point*> points_;
	std::unordered_map<std::string, Line*> lines_;
	std::unordered_map<std::string, LineLoop*> lineLoops_;
	std::unordered_map<std::string, PlaneSurface*> planeSurfaces_;
	std::unordered_map<std::string, std::vector<GeometricBoundaryCondition*>> boundaryConditions_;
	std::string gmshCode_;
};


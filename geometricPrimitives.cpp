#include "geometricPrimitives.hpp"
#include<stdlib.h>
#include<iostream>
#include<math.h>

using namespace std;
//extern ostream cerr;

Point::Point(){

}

Point::Point(int x, int y){
  this->xCoordinate = x;
  this->yCoordinate = y;
  this->r = sqrt(x*x + y*y);
  this->theta = tan(double(y)/x);
  if(theta < 0 && cos(double(x)/r) < 0){
    this->r = -this->r;
  }
}

int Point::getX(){
  return this->xCoordinate; 
}

int Point::getY(){
  return this->yCoordinate;
}

double Point::getR(){
  return this->r;
}

double Point::getTheta(){
  return this->theta;
}

double Point::distanceFrom(Point other){
  int a = (this->xCoordinate - other.xCoordinate);
  int a2 = a*a;
  int b = (this->yCoordinate - other.yCoordinate);
  int b2 = b*b;
  return sqrt(a2 + b2);
}

bool Point::isOnLine(Line line){
  return line.pointOnLine(*this);
}

void Point::print(){
  cout << "(" << this->getX() << ", " << this->getY() << ")" << endl;
}

bool Point::operator==(const Point &other){
  return (this->xCoordinate == other.xCoordinate &&
	  this->yCoordinate == other.yCoordinate);
}

Point Point::operator=(const Point &newValue){
  this->xCoordinate = newValue.xCoordinate;
  this->yCoordinate = newValue.yCoordinate;
  this->r = newValue.r;
  this->theta = newValue.theta;
  return *this;
}

bool Point::isOnEdge(Circle circle){
  return this->distanceFrom(circle.getCenter()) == circle.getRadius();
}

Circle::Circle(Point &center, int radius){
  this->center = center;
  this->radius = radius;
}

int Circle::getRadius(){
  return this->radius;
} 

int Circle::getDiameter(){
  return this->radius*2;
} 

double Circle::getCircumference(){
  return 2*M_PI*this->radius;
}

Point Circle::getCenter(){
  return Point(this->center.getX(), this->center.getY());
}

double Circle::getArea(){
  return M_PI*this->radius*this->radius;
}

bool Circle::contains(Point point){
  return (this->center.distanceFrom(point) < this->radius);
}

Magick::DrawableCircle Circle::toDrawable(){
  int x = this->getCenter().getX();
  int y = this->getCenter().getY();
  int r = this->getRadius();
  return Magick::DrawableCircle(x,y, x-r,y);
}

void Circle::print() {
  cout << "Circle at (" << this->center.getX() << ", " << this->center.getY()
       << ") with radius " << this->radius << endl;
}

bool Circle::operator==(const Circle &other){
  return (this->center == other.center && this->radius == other.radius);
} 

Line::Line(double slope, double intercept, int type = GP_LINE_CARTESIAN){
  if(type == GP_LINE_CARTESIAN){ 
    this->m = slope;
    this->b = intercept;
    this->theta = -atan(1/slope);
    this->r = intercept * sin(theta);
    this->sinTheta = sin(theta);
    this->cosTheta = cos(theta);
  }
  if(type == GP_LINE_POLAR){
    this->theta = -(intercept - int(intercept / (2 * M_PI)) * 2 * M_PI - M_PI);
    this->r = slope;
    if(tan(theta) != 0) this->m = -1/tan(theta);
    this->sinTheta = sin(theta);
    this->cosTheta = cos(theta);
    if(sinTheta != 0) this->b = this->r / sinTheta;
  }
}

double Line::getSlope(){
  return this->m;
} 

double Line::getYIntercept(){
  return this->b;
}

double Line::getTheta(){
  return this->theta;
}

double Line::getR(){
  return this->r;
}

bool Line::pointOnLine(Point point){
  return point.getY() == this->m * point.getX() + this->b;
}

bool Line::bisects(Circle circle){
  cerr << "calling unimplemented function Line::bisects\n";
  return 0;
}

bool Line::tangentTo(Circle circle){
  cerr << "calling unimplemented function Line::tangentTo\n";
  return 0;
}

bool Line::operator==(const Line &other){
  return (this->r == other.r && this->theta == other.theta);
}

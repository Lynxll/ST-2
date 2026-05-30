// Copyright 2022 UNN-CS
#include "circle.h"
#include "tasks.h"

double solveRopeTask() {
  const double earthRadiusKm = 6378.1;
  const double earthRadiusM = earthRadiusKm * 1000.0;
  const double addedLengthM = 1.0;

  Circle earth(earthRadiusM);
  Circle expanded;
  expanded.setFerence(earth.getFerence() + addedLengthM);

  return expanded.getRadius() - earth.getRadius();
}

double solvePoolTask() {
  const double poolRadiusM = 3.0;
  const double pathWidthM = 1.0;
  const double concreteCostPerSqM = 1000.0;
  const double fenceCostPerM = 2000.0;

  Circle pool(poolRadiusM);
  Circle outer(poolRadiusM + pathWidthM);

  const double pathArea = outer.getArea() - pool.getArea();
  const double fenceLength = outer.getFerence();

  return pathArea * concreteCostPerSqM + fenceLength * fenceCostPerM;
}

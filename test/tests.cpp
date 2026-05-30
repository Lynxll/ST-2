// Copyright 2025 UNN-CS Team

#include <gtest/gtest.h>
#include <cmath>
#include "circle.h"
#include "tasks.h"

namespace {
const double PI = 3.14159265358979323846;
const double EPS = 1e-6;
}  // namespace

TEST(CircleConstructorTest, ZeroRadius) {
  Circle circle(0.0);
  EXPECT_NEAR(circle.getRadius(), 0.0, EPS);
  EXPECT_NEAR(circle.getFerence(), 0.0, EPS);
  EXPECT_NEAR(circle.getArea(), 0.0, EPS);
}

TEST(CircleConstructorTest, SetsRadius) {
  Circle circle(5.0);
  EXPECT_NEAR(circle.getRadius(), 5.0, EPS);
}

TEST(CircleConstructorTest, CalculatesFerence) {
  Circle circle(1.0);
  EXPECT_NEAR(circle.getFerence(), 2.0 * PI, EPS);
}

TEST(CircleConstructorTest, CalculatesArea) {
  Circle circle(2.0);
  EXPECT_NEAR(circle.getArea(), 4.0 * PI, EPS);
}

TEST(CircleSetRadiusTest, UpdatesFerence) {
  Circle circle;
  circle.setRadius(3.0);
  EXPECT_NEAR(circle.getFerence(), 2.0 * PI * 3.0, EPS);
}

TEST(CircleSetRadiusTest, UpdatesArea) {
  Circle circle;
  circle.setRadius(4.0);
  EXPECT_NEAR(circle.getArea(), PI * 16.0, EPS);
}

TEST(CircleSetRadiusTest, RecalculatesAllFields) {
  Circle circle;
  circle.setRadius(10.0);
  EXPECT_NEAR(circle.getRadius(), 10.0, EPS);
  EXPECT_NEAR(circle.getFerence(), 20.0 * PI, EPS);
  EXPECT_NEAR(circle.getArea(), 100.0 * PI, EPS);
}

TEST(CircleSetFerenceTest, UpdatesRadius) {
  Circle circle;
  circle.setFerence(2.0 * PI);
  EXPECT_NEAR(circle.getRadius(), 1.0, EPS);
}

TEST(CircleSetFerenceTest, UpdatesArea) {
  Circle circle;
  circle.setFerence(4.0 * PI);
  EXPECT_NEAR(circle.getArea(), PI * 4.0, EPS);
}

TEST(CircleSetFerenceTest, RecalculatesAllFields) {
  Circle circle;
  circle.setFerence(6.0 * PI);
  EXPECT_NEAR(circle.getRadius(), 3.0, EPS);
  EXPECT_NEAR(circle.getFerence(), 6.0 * PI, EPS);
  EXPECT_NEAR(circle.getArea(), 9.0 * PI, EPS);
}

TEST(CircleSetAreaTest, UpdatesRadius) {
  Circle circle;
  circle.setArea(PI);
  EXPECT_NEAR(circle.getRadius(), 1.0, EPS);
}

TEST(CircleSetAreaTest, UpdatesFerence) {
  Circle circle;
  circle.setArea(PI * 9.0);
  EXPECT_NEAR(circle.getFerence(), 6.0 * PI, EPS);
}

TEST(CircleSetAreaTest, RecalculatesAllFields) {
  Circle circle;
  circle.setArea(PI * 25.0);
  EXPECT_NEAR(circle.getRadius(), 5.0, EPS);
  EXPECT_NEAR(circle.getFerence(), 10.0 * PI, EPS);
  EXPECT_NEAR(circle.getArea(), 25.0 * PI, EPS);
}

TEST(CircleConsistencyTest, SetRadiusThenSetFerence) {
  Circle circle;
  circle.setRadius(7.0);
  circle.setFerence(circle.getFerence());
  EXPECT_NEAR(circle.getRadius(), 7.0, EPS);
  EXPECT_NEAR(circle.getArea(), 49.0 * PI, EPS);
}

TEST(CircleConsistencyTest, SetFerenceThenSetArea) {
  Circle circle;
  circle.setFerence(8.0 * PI);
  circle.setArea(circle.getArea());
  EXPECT_NEAR(circle.getRadius(), 4.0, EPS);
  EXPECT_NEAR(circle.getFerence(), 8.0 * PI, EPS);
}

TEST(CircleConsistencyTest, SetAreaThenSetRadius) {
  Circle circle;
  circle.setArea(PI * 16.0);
  circle.setRadius(circle.getRadius());
  EXPECT_NEAR(circle.getRadius(), 4.0, EPS);
  EXPECT_NEAR(circle.getArea(), 16.0 * PI, EPS);
}

TEST(RopeTaskTest, GapEqualsOneOverTwoPi) {
  const double expectedGap = 1.0 / (2.0 * PI);
  EXPECT_NEAR(solveRopeTask(), expectedGap, EPS);
}

TEST(RopeTaskTest, GapDoesNotDependOnEarthRadius) {
  const double earthRadiusM = 6378.1 * 1000.0;
  Circle earth(earthRadiusM);
  Circle expanded;
  expanded.setFerence(earth.getFerence() + 1.0);
  EXPECT_NEAR(expanded.getRadius() - earth.getRadius(), solveRopeTask(), EPS);
}

TEST(RopeTaskTest, GapAfterAddingOneMeter) {
  Circle small(1.0);
  Circle large;
  large.setFerence(small.getFerence() + 1.0);
  EXPECT_NEAR(large.getRadius() - small.getRadius(), solveRopeTask(), EPS);
}

TEST(PoolTaskTest, TotalCostIsCorrect) {
  const double pathArea = 7.0 * PI;
  const double fenceLength = 8.0 * PI;
  const double expectedCost = pathArea * 1000.0 + fenceLength * 2000.0;
  EXPECT_NEAR(solvePoolTask(), expectedCost, EPS);
}

TEST(PoolTaskTest, PathAreaCalculation) {
  Circle pool(3.0);
  Circle outer(4.0);
  const double pathArea = outer.getArea() - pool.getArea();
  EXPECT_NEAR(pathArea, 7.0 * PI, EPS);
}

TEST(PoolTaskTest, FenceLengthCalculation) {
  Circle outer(4.0);
  EXPECT_NEAR(outer.getFerence(), 8.0 * PI, EPS);
}

TEST(PoolTaskTest, ConcreteAndFenceComponents) {
  Circle pool(3.0);
  Circle outer(4.0);
  const double concreteCost = (outer.getArea() - pool.getArea()) * 1000.0;
  const double fenceCost = outer.getFerence() * 2000.0;
  EXPECT_NEAR(concreteCost + fenceCost, solvePoolTask(), EPS);
}

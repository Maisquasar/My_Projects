#pragma once


#include <math.h>

#include <stdbool.h>

#define VEC2D_COLLINEAR_PRECISION 0.001f
#define VEC2D_HIGH_VALUE 1e20f

typedef struct Vec2D {
    float x;
    float y;
} Vec2D;

typedef struct RotationMatrix {
    float content[2][2];
} RotationMatrix;

// Return a new empty Vec2D
Vec2D create();

// Return a new Vec2D initialised with 'a' and 'b'
Vec2D createWith(float x, float y);

// Return a new Vec2D initialised with 'in'
Vec2D copy(Vec2D in);

// Return the length squared of 'in'
float lengthSquared(Vec2D in);

// Return the lenght of the given Vector
float getLength(Vec2D in);

// Return a new vector wich is the sum of 'a' and 'b'
Vec2D add(Vec2D a, Vec2D b);

// Return a new vector wich is the substraction of 'a' and 'b'
Vec2D sub(Vec2D a, Vec2D b);

// Return the result of the aritmetic multiplication of 'a' and 'b'
Vec2D mulV(Vec2D a, Vec2D b);

// Return the result of the aritmetic multiplication of 'a' and 'b'
Vec2D mul(Vec2D a, float b);

// Return the result of the aritmetic division of 'a' and 'b', will return 'a' * VEC2D_HIGH_VALUE if 'b' is equal 0;
Vec2D divF(Vec2D a, float b);

// Return tue if 'a' and 'b' are collinears (Precision defined by VEC2D_COLLINEAR_PRECISION)
bool areVectorsCollinear(Vec2D a, Vec2D b);

// Return the dot product of 'a' and 'b'
float dotProduct(Vec2D a, Vec2D b);

// Return the z component of the cross product of 'a' and 'b'
float crossProduct(Vec2D a, Vec2D b);

// Return a vector with the same direction that 'in', but with length 1
Vec2D unitVector(Vec2D in);

// Return a vector of length 'in' and with an opposite direction
Vec2D negate(Vec2D in);

Vec2D getNormal(Vec2D in);

// Return the given angular value in degres converted to radians
float toRadians(float in);

float cut(float in, float min, float max);

float mod(float in, float min, float max);

RotationMatrix getRotationMatrix(float angle);

Vec2D applyRotation(Vec2D in, RotationMatrix matrix);

int atoi(char* number);
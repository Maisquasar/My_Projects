#include "mathHelper.hpp"

Vec2D create() {
    Vec2D n;
    return n;
}

Vec2D createWith(float a, float b) {
    Vec2D n = create();
    n.x = a;
    n.y = b;
    return n;
}

Vec2D copy(Vec2D in) {
    Vec2D n = createWith(in.x, in.y);
    return n;
}

float lengthSquared(Vec2D in) {
    return (in.x * in.x + in.y * in.y);
}

float getLength(Vec2D in) {
    return sqrtf(lengthSquared(in));
}

Vec2D add(Vec2D a, Vec2D b) {
    Vec2D res = createWith(a.x + b.x, a.y + b.y);
    return res;
}

Vec2D sub(Vec2D a, Vec2D b) {
    Vec2D res = createWith(a.x - b.x, a.y - b.y);
    return res;
}

Vec2D mulV(Vec2D a, Vec2D b) {
    Vec2D res = createWith(a.x * b.x, a.y * b.y);
    return res;
}

Vec2D mul(Vec2D a, float b) {
    Vec2D res = createWith(a.x * b, a.y * b);
    return res;
}

Vec2D divF(Vec2D a, float b) {
    if (b == 0.0) return mul(a,VEC2D_HIGH_VALUE);
    Vec2D res = mul(a,1/b);
    return res;
}

bool areVectorsCollinear(Vec2D a, Vec2D b) {
    float res = a.x * b.y - a.y * b.x;
    return (res < VEC2D_COLLINEAR_PRECISION);
}

float dotProduct(Vec2D a, Vec2D b) {
    return (a.x * b.x + a.y * b.y);
}

float crossProduct(Vec2D a, Vec2D b) {
    return (a.x * b.y - a.y * b.x);
}

Vec2D unitVector(Vec2D in) {
    return divF(in, getLength(in));
}

Vec2D negate(Vec2D in) {
    return mul(in,-1);
}

Vec2D getNormal(Vec2D in) {
    return createWith(-in.y, in.x);
}

float toRadians(float in) {
    return in/180.0*M_PI;
}

float cut(float in, float min, float max) {
    if (in < min) in = min;
    if (in > max) in = max;
    return in;
}

float mod(float in, float min, float max) {
    while(in < min) in += max-min;
    while (in > max) in -= max-min;
    return in;
}

RotationMatrix getRotationMatrix(float angle) {
    RotationMatrix res = {0};
    float tmpCos = cosf(toRadians(angle));
    float tmpSin = sinf(toRadians(angle));
    res.content[0][0] = tmpCos;
    res.content[0][1] = -tmpSin;
    res.content[1][0] = tmpSin;
    res.content[1][1] = tmpCos;
    return res;
}

Vec2D applyRotation(Vec2D in, RotationMatrix matrix) {
    float res[2] = {0};
    float input[2] = {in.x, in.y};
    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < 2; i++) {
            res[j] += input[i]*matrix.content[j][i];
        }
    }
    return createWith(res[0], res[1]);
}

int atoi(char* number) {
    int res = 0;
    for (int i = 0; number[i] != 0; i++) {
        res *= 10;
        res += number[i]-'0';
    }
    return res;
}
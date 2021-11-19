#pragma once
#include <raylib.h>
#include "datas.hpp"
#include "mathHelper.hpp"


void initParticle(Particle *in, Vector2 pos, float rot, float speed, int timer, ParticleType type);
void handleParticles(Particle *in);
void createExplosion(GameDatas *in, Vector2 pos);

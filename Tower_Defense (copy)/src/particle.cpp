#include "particle.hpp"

void initParticle(Particle *in, Vector2 pos, float rot, float speed, int timer, ParticleType type)
{
    Vector2 dir = VtoV2(createWith(cosf(toRadians(rot)) * speed, sinf(toRadians(rot)) * speed));
    for (int i = 0; i < 1000; i++)
    {
        if (in[i].type == NONE)
        {
            in[i].type = type;
            in[i].vel = dir;
            in[i].pos = pos;
            in[i].timer = timer;
            in[i].opacity = 100;
            break;
        }
    }
}

void handleParticles(Particle *in)
{
    for (int i = 0; i < 1000; i++)
    {
        if (in->type == NONE)
            continue;
        Particle *tmp = &in[i];
        switch (in->type)
        {
        case EXPLOSION:
            tmp->timer += 1;
            tmp->radius = GetRandomValue(10,20);
            tmp->opacity -= 2;
            if (tmp->timer >= 0)
            {
                tmp->vel = VtoV2(add(V2toV(tmp->vel), divF(V2toV(tmp->vel), tmp->timer + 1)));
            }
            if (tmp->timer > 30)
            {
                tmp->type = NONE;
            }
            break;

        default:
            break;
        }
    }
}

void createExplosion(GameDatas *in, Vector2 pos)
{
    for (int i = 0; i < 7; i++)
    {
        initParticle(in->particle, VtoV2(add(V2toV(pos), V2toV(Vector2{(float)GetRandomValue(-10,10),(float)GetRandomValue(-10,10)}))) , GetRandomValue(0, 65536) / 65536.0f * 360.0f, 0.7 + GetRandomValue(0, 65536) / 65536.0f * 0.7, GetRandomValue(-10, 0), EXPLOSION);
    }
}

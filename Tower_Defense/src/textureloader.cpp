#include "textureloader.hpp"

void TexturesLoad(GameDatas* in)
{
    in->font[0] = LoadFont("/home/ISART/r.bourgogne/Documents/My_projects/Tower Defense/assets/Fonts/FredokaOne-Regular.ttf");

    //Map (0-49)
    in->texture[0] = LoadTexture("/home/ISART/r.bourgogne/Documents/My_projects/Tower Defense/assets/kenney_topdowntanksredux/PNG/Default size/tileGrass1.png");
    in->texture[1] = LoadTexture("/home/ISART/r.bourgogne/Documents/My_projects/Tower Defense/assets/kenney_topdowntanksredux/PNG/Default size/tileGrass2.png");
    in->texture[2] = LoadTexture("/home/ISART/r.bourgogne/Documents/My_projects/Tower Defense/assets/kenney_topdowntanksredux/PNG/Default size/tileGrass_roadEast.png");
    in->texture[3] = LoadTexture("/home/ISART/r.bourgogne/Documents/My_projects/Tower Defense/assets/kenney_topdowntanksredux/PNG/Default size/tileGrass_roadNorth.png");
    in->texture[4] = LoadTexture("/home/ISART/r.bourgogne/Documents/My_projects/Tower Defense/assets/kenney_topdowntanksredux/PNG/Default size/tileGrass_roadCornerUL.png");
    in->texture[5] = LoadTexture("/home/ISART/r.bourgogne/Documents/My_projects/Tower Defense/assets/kenney_topdowntanksredux/PNG/Default size/tileGrass_roadCornerUR.png");
    in->texture[6] = LoadTexture("/home/ISART/r.bourgogne/Documents/My_projects/Tower Defense/assets/kenney_topdowntanksredux/PNG/Default size/tileGrass_roadCornerLR.png");
    in->texture[7] = LoadTexture("/home/ISART/r.bourgogne/Documents/My_projects/Tower Defense/assets/kenney_topdowntanksredux/PNG/Default size/tileGrass_roadCornerLL.png");
    in->texture[8] = LoadTexture("/home/ISART/r.bourgogne/Documents/My_projects/Tower Defense/assets/kenney_topdowntanksredux/PNG/Default size/tileGrass_roadSplitE.png");
    in->texture[9] = LoadTexture("/home/ISART/r.bourgogne/Documents/My_projects/Tower Defense/assets/kenney_topdowntanksredux/PNG/Default size/tileGrass_roadSplitW.png");
    in->texture[10] = LoadTexture("/home/ISART/r.bourgogne/Documents/My_Projects/Tower_Defense/assets/kenney_topdowntanksredux/PNG/Default size/tileGrass_roadSplitS.png");
    in->texture[11] = LoadTexture("/home/ISART/r.bourgogne/Documents/My_Projects/Tower_Defense/assets/kenney_topdowntanksredux/PNG/Default size/tileGrass_roadSplitN.png");
    in->texture[12] = LoadTexture("/home/ISART/r.bourgogne/Documents/My_Projects/Tower_Defense/assets/kenney_topdowntanksredux/PNG/Default size/tileGrass_roadCrossing.png");

    //Enemies(50 - 99)
    in->texture[50] = LoadTexture("/home/ISART/r.bourgogne/Documents/My_projects/Tower Defense/assets/kenney_topdowntanksredux/PNG/Default size/tank_blue.png"); //Slow
    in->texture[51] = LoadTexture("/home/ISART/r.bourgogne/Documents/My_projects/Tower Defense/assets/kenney_topdowntanksredux/PNG/Default size/tank_green.png"); //Fast
    in->texture[52] = LoadTexture("/home/ISART/r.bourgogne/Documents/My_projects/Tower Defense/assets/kenney_topdowntanksredux/PNG/Default size/tank_darkLarge.png"); //Strong
    in->texture[53] = LoadTexture("/home/ISART/r.bourgogne/Documents/My_projects/Tower Defense/assets/kenney_topdowntanksredux/PNG/Default size/tank_huge.png"); //Boss
    
    //Tower(100 - 150)
    //Basic
    in->texture[100] = LoadTexture("/home/ISART/r.bourgogne/Documents/My_projects/Tower Defense/assets/tower-defense-top-down/PNG/Default size/towerDefense_tile180.png");
    in->texture[101] = LoadTexture("/home/ISART/r.bourgogne/Documents/My_projects/Tower Defense/assets/tower-defense-top-down/PNG/Default size/towerDefense_tile249.png");
    in->texture[102] = LoadTexture("/home/ISART/r.bourgogne/Documents/My_projects/Tower Defense/assets/tower-defense-top-down/PNG/Default size/towerDefense_tile250.png");
    in->texture[103] = LoadTexture("/home/ISART/r.bourgogne/Documents/My_Projects/Tower_Defense/assets/tower-defense-top-down/PNG/Default size/towerDefense_tile206.png");
    in->texture[104] = LoadTexture("/home/ISART/r.bourgogne/Documents/My_Projects/Tower_Defense/assets/tower-defense-top-down/PNG/Default size/towerDefense_tile205.png");

    //Shoots
    in->texture[110] = LoadTexture("/home/ISART/r.bourgogne/Documents/My_projects/Tower Defense/assets/tower-defense-top-down/PNG/Default size/towerDefense_tile298.png");
    in->texture[111] = LoadTexture("/home/ISART/r.bourgogne/Documents/My_projects/Tower Defense/assets/tower-defense-top-down/PNG/Default size/Tower1Fire.png");
    in->texture[112] = LoadTexture("/home/ISART/r.bourgogne/Documents/My_projects/Tower Defense/assets/tower-defense-top-down/PNG/Default size/Tower2Fire.png");
    in->texture[113] = LoadTexture("/home/ISART/r.bourgogne/Documents/My_Projects/Tower_Defense/assets/tower-defense-top-down/PNG/Default size/towerDefense_tile229.png");
    in->texture[114] = LoadTexture("/home/ISART/r.bourgogne/Documents/My_Projects/Tower_Defense/assets/tower-defense-top-down/PNG/Default size/towerDefense_tile228.png");

    in->texture[25] = LoadTexture("/home/ISART/r.bourgogne/Documents/My_projects/Tower Defense/assets/tower-defense-top-down/PNG/Default size/towerDefense_tile287.png");
}
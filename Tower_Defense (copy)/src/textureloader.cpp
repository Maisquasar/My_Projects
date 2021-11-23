#include "textureloader.hpp"

void TexturesLoad(GameDatas *in)
{
    in->setFont(0, LoadFont("/home/ISART/r.bourgogne/Documents/My_projects/Tower Defense/assets/Fonts/FredokaOne-Regular.ttf"));

    //Map (0-49)
    in->setTexture(0, LoadTexture("/home/ISART/r.bourgogne/Documents/My_projects/Tower Defense/assets/kenney_topdowntanksredux/PNG/Default size/tileGrass1.png"));
    in->setTexture(1, LoadTexture("/home/ISART/r.bourgogne/Documents/My_projects/Tower Defense/assets/kenney_topdowntanksredux/PNG/Default size/tileGrass2.png"));
    in->setTexture(2, LoadTexture("/home/ISART/r.bourgogne/Documents/My_projects/Tower Defense/assets/kenney_topdowntanksredux/PNG/Default size/tileGrass_roadEast.png"));
    in->setTexture(3, LoadTexture("/home/ISART/r.bourgogne/Documents/My_projects/Tower Defense/assets/kenney_topdowntanksredux/PNG/Default size/tileGrass_roadNorth.png"));
    in->setTexture(4, LoadTexture("/home/ISART/r.bourgogne/Documents/My_projects/Tower Defense/assets/kenney_topdowntanksredux/PNG/Default size/tileGrass_roadCornerUL.png"));
    in->setTexture(5, LoadTexture("/home/ISART/r.bourgogne/Documents/My_projects/Tower Defense/assets/kenney_topdowntanksredux/PNG/Default size/tileGrass_roadCornerUR.png"));
    in->setTexture(6, LoadTexture("/home/ISART/r.bourgogne/Documents/My_projects/Tower Defense/assets/kenney_topdowntanksredux/PNG/Default size/tileGrass_roadCornerLR.png"));
    in->setTexture(7, LoadTexture("/home/ISART/r.bourgogne/Documents/My_projects/Tower Defense/assets/kenney_topdowntanksredux/PNG/Default size/tileGrass_roadCornerLL.png"));
    in->setTexture(8, LoadTexture("/home/ISART/r.bourgogne/Documents/My_projects/Tower Defense/assets/kenney_topdowntanksredux/PNG/Default size/tileGrass_roadSplitE.png"));
    in->setTexture(9, LoadTexture("/home/ISART/r.bourgogne/Documents/My_projects/Tower Defense/assets/kenney_topdowntanksredux/PNG/Default size/tileGrass_roadSplitW.png"));
    in->setTexture(10, LoadTexture("/home/ISART/r.bourgogne/Documents/My_Projects/Tower_Defense/assets/kenney_topdowntanksredux/PNG/Default size/tileGrass_roadSplitS.png"));
    in->setTexture(11, LoadTexture("/home/ISART/r.bourgogne/Documents/My_Projects/Tower_Defense/assets/kenney_topdowntanksredux/PNG/Default size/tileGrass_roadSplitN.png"));
    in->setTexture(12, LoadTexture("/home/ISART/r.bourgogne/Documents/My_Projects/Tower_Defense/assets/kenney_topdowntanksredux/PNG/Default size/tileGrass_roadCrossing.png"));

    //Enemies(50 - 99)
    in->setTexture(50, LoadTexture("/home/ISART/r.bourgogne/Documents/My_projects/Tower Defense/assets/kenney_topdowntanksredux/PNG/Default size/tank_blue.png")); //Slow
    in->setTexture(51, LoadTexture("/home/ISART/r.bourgogne/Documents/My_projects/Tower Defense/assets/kenney_topdowntanksredux/PNG/Default size/tank_green.png")); //Fast
    in->setTexture(52, LoadTexture("/home/ISART/r.bourgogne/Documents/My_projects/Tower Defense/assets/kenney_topdowntanksredux/PNG/Default size/tank_darkLarge.png")); //Strong
    in->setTexture(53, LoadTexture("/home/ISART/r.bourgogne/Documents/My_projects/Tower Defense/assets/kenney_topdowntanksredux/PNG/Default size/tank_huge.png")); //Boss
    
    //Tower(100 - 150)
    //Basic
    in->setTexture(100, LoadTexture("/home/ISART/r.bourgogne/Documents/My_projects/Tower Defense/assets/tower-defense-top-down/PNG/Default size/towerDefense_tile180.png"));
    in->setTexture(101, LoadTexture("/home/ISART/r.bourgogne/Documents/My_projects/Tower Defense/assets/tower-defense-top-down/PNG/Default size/towerDefense_tile249.png"));
    in->setTexture(102, LoadTexture("/home/ISART/r.bourgogne/Documents/My_projects/Tower Defense/assets/tower-defense-top-down/PNG/Default size/towerDefense_tile250.png"));
    in->setTexture(103, LoadTexture("/home/ISART/r.bourgogne/Documents/My_Projects/Tower_Defense/assets/tower-defense-top-down/PNG/Default size/towerDefense_tile206.png"));
    in->setTexture(104, LoadTexture("/home/ISART/r.bourgogne/Documents/My_Projects/Tower_Defense/assets/tower-defense-top-down/PNG/Default size/towerDefense_tile205.png"));

    //Shoots
    in->setTexture(110, LoadTexture("/home/ISART/r.bourgogne/Documents/My_projects/Tower Defense/assets/tower-defense-top-down/PNG/Default size/towerDefense_tile298.png"));
    in->setTexture(111, LoadTexture("/home/ISART/r.bourgogne/Documents/My_projects/Tower Defense/assets/tower-defense-top-down/PNG/Default size/Tower1Fire.png"));
    in->setTexture(112, LoadTexture("/home/ISART/r.bourgogne/Documents/My_projects/Tower Defense/assets/tower-defense-top-down/PNG/Default size/Tower2Fire.png"));
    in->setTexture(113, LoadTexture("/home/ISART/r.bourgogne/Documents/My_Projects/Tower_Defense/assets/tower-defense-top-down/PNG/Default size/towerDefense_tile229.png"));
    in->setTexture(114, LoadTexture("/home/ISART/r.bourgogne/Documents/My_Projects/Tower_Defense/assets/tower-defense-top-down/PNG/Default size/towerDefense_tile228.png"));
    in->setTexture(25, LoadTexture("/home/ISART/r.bourgogne/Documents/My_projects/Tower Defense/assets/tower-defense-top-down/PNG/Default size/towerDefense_tile287.png"));
}
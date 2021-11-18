//Program for Fights
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "../rules/rules.hpp"
#include "../datas/species.hpp"
#include "../datas/gamedatas.hpp"
void *handleAttack(Pokemon *attacker, MoveSlot moveslot, Pokemon *defender)
{
    Species *spA = getSpeciesByIndex(attacker->speciesId);
    Species *spD = getSpeciesByIndex(attacker->speciesId);
    Move *move = getMoveById(moveslot.id);
    float Damage;
    float t = Accuracy(move, *attacker, *defender);
    int r = (rand() % 256);
    if (r > t)
    {
        if (move->category == C_PHYSICAL)
        {
            int critical = (int)CriticalHit(move, *attacker, 1);
            Damage = 2 * attacker->level;
            Damage = Damage / 5;
            Damage = (Damage + 2) * (move->power) * (attacker->attackStat / attacker->defenseStat);
            Damage = (Damage / 50) + 2;
            Damage = Damage * (((rand() % 16) + 85) * 0.01) * getSTAB(move->type, spD->primaryType, spD->secondaryType) * getTypeEffectiveness(move->type, spD->primaryType, spD->secondaryType) * critical;
            //Damage = ((((((2 * attacker->level) / 5) + 2) * move->power * attacker->attackStat / attacker->defenseStat) / 50) + 2) * (((rand() % 16) + 85) * 0.01) * getSTAB(move->type, spD->primaryType, spD->secondaryType) * getTypeEffectiveness(move->type, spD->primaryType, spD->secondaryType) * critical;
            //printf("Damage : %.2f \n", Damage);
        }
        else if (move->category == C_SPECIAL)
        {
            int critical = (int)CriticalHit(move, *attacker, 1);
            Damage = 2 * attacker->level;
            Damage = Damage / 5;
            Damage = (Damage + 2) * (move->power) * (attacker->attackStat / attacker->defenseStat);
            Damage = (Damage / 50) + 2;
            Damage = Damage * (((rand() % 16) + 85) * 0.01) * getSTAB(move->type, spD->primaryType, spD->secondaryType) * getTypeEffectiveness(move->type, spD->primaryType, spD->secondaryType) * critical;
            //Damage = ((((((2 * attacker->level) / 5) + 2) * move->power * attacker->specialStat / attacker->specialStat) / 50) + 2) * (((rand() % 16) + 85) * 0.01) * getSTAB(move->type, spD->primaryType, spD->secondaryType) * getTypeEffectiveness(move->type, spD->primaryType, spD->secondaryType) * critical;
            //printf("Damage : %.2f \n", Damage);
        }
        else if (move->category == C_STATUS)
        {
            Damage = 0;
        }
        defender->currentHP -= Damage;
        if (Damage > 0)
        {
            //damage
        }
        if (defender->currentHP < 0)
        {
            defender->currentHP = 0;
        }
    }
    else
    {
        //Failed
    }
}
/* 
void pokemonList(Player *player)
{
    if (player->pokemonInLife <= 1)
    {
        //affichage
        int pkchoice = 0;
        system("clear");
        printf("Pokemons:\n");
        for (int i = 0; i < player->pokemonCount; ++i)
        {
            printf("    %d. ", i + 1);
            printf("%s, lvl: %d, ",
                   player->pokemon[i].name,
                   player->pokemon[i].level);
            getColorByType(player->pokemon[i].type1);
            printType(player->pokemon[i].type1);
            printf(reset ", ");
            if (player->pokemon[i].type2 != T_NOT_SET)
            {
                getColorByType(player->pokemon[i].type2);
                printType(player->pokemon[i].type2);
            }
            printf(reset " [%.1f/%.1f]\n",
                   player->pokemon[i].currentHP,
                   getMaxHP(player->pokemon[i]));
        }
        printf(RED "    0. Leave\n" reset);
        pkchoice = NULL; //reinit choice
        //Choix
        while ((player->pokemon[player->PrecedentPKID].currentHP == 0) || pkchoice == NULL)
        {
            scanf("%d", &pkchoice);
            fgetc(stdin);
            if ((pkchoice - 1 == player->PrecedentPKID || pkchoice == 0) && player->pokemon[player->PrecedentPKID].currentHP != 0) //Si choix = precedent pokemon et precedent pokemon hp > 0
            {
                break;
            }
            else if (pkchoice > player->pokemonCount)
            {
                printf(RED "You can't choose a non-existent Pokemon !\n" reset);
                pkchoice = NULL;
            }
            else if (player->pokemon[player->PrecedentPKID].currentHP == 0) //Si precedent pokemon hp > 0
            {
                printf(RED "You can't choose a K.O Pokemon !\n" reset);
                player->PrecedentPKID = pkchoice - 1; //Init precedent pokemon
            }
            else if (pkchoice == 0 && player->pokemon[player->PrecedentPKID].currentHP == 0) //Si choix = 0 et precedent pokemon hp = 0
            {
                printf(RED "You can't leave without alive pokemon.\n" reset);
                player->PrecedentPKID = pkchoice - 1; //Init precedent pokemon
            }
        }
    }
}
void WildFight(GameDatas* in)
{
    int choice, temp, x = 0, back = 0, turn = 1, attempts = 0;
    for (int i = 0; i < in->player->pokemonCount; ++i) //Init First Pokemon
    {
        if (in->player->pokemon[i].currentHP != 0)
        {
            in->player->PrecedentPKID = i;
            break;
        }
    }
    Species *wildsp = getSpeciesByIndex(in->wild.speciesId);
    Species *sp = getSpeciesByIndex(in->player->pokemon[in->player->PrecedentPKID].speciesId);
    system("clear");
    printf("Wild ");
    getColorByType(wildsp->primaryType);
    printf("%s" reset " appeared !", in->wild.name);
    fgetc(stdin);
    system("clear");
    printf("Go ! ");
    getColorByType(in->player->pokemon[in->player->PrecedentPKID].type1);
    printf("%s" reset " !", in->player->pokemon[in->player->PrecedentPKID].name);
    fgetc(stdin);
    while (in->wild.currentHP != 0 || in->player->pokemonInLife != 0)
    {
        choice = 0;
        system("clear");
        printf("=======Turn #%d=======\n\n", turn);
        getColorByType(wildsp->primaryType);
        printf("%s" reset ", lvl : %d " RED "[%.1f/%.1f]" reset "\n",
               wild.name,
               wild.level,
               wild.currentHP,
               getMaxHP(wild));
        getColorByType(in->player->pokemon[in->player->PrecedentPKID].type1);
        printf("%s" reset ", lvl : %d " RED "[%.1f/%.1f] " reset HGRN "EXP. [%d/%d]" reset "\n\n",
               in->player->pokemon[in->player->PrecedentPKID].name,
               in->player->pokemon[in->player->PrecedentPKID].level,
               in->player->pokemon[in->player->PrecedentPKID].currentHP,
               getMaxHP(in->player->pokemon[in->player->PrecedentPKID]),
               in->player->pokemon[in->player->PrecedentPKID].ExpPoints,
               getxpRequiredForLevel(in->player->pokemon[in->player->PrecedentPKID]));
        printf("    " BRED "1.Moves    " BLU "2.Pokemons\n    " GRN "3.Item    " YEL " 4.Run\n" reset);
        scanf("%d", &choice);
        fgetc(stdin);

        //=========================================Attack=========================================
        if (choice == 1)
        {
            int movechoice = -1;
            system("clear");
            printf(BRED "Moves :\n" reset);
            //Print Moves
            for (int i = 0; i < in->player->pokemon[in->player->PrecedentPKID].moveCount; ++i)
            {
                printf("    %d. ", i + 1);
                printf("%s, Power : %d, Type : ",
                       in->player->pokemon[in->player->PrecedentPKID].moveSlots[i].name,
                       in->player->pokemon[in->player->PrecedentPKID].moveSlots[i].power);
                getColorByType(in->player->pokemon[in->player->PrecedentPKID].moveSlots[i].type);
                printType(in->player->pokemon[in->player->PrecedentPKID].moveSlots[i].type);
                printf(reset ", PP : [%d/%d]\n", in->player->pokemon[in->player->PrecedentPKID].moveSlots[i].pp, in->player->pokemon[in->player->PrecedentPKID].moveSlots[i].PPBase);
            }
            printf(RED "    0. Leave\n" reset);
            while (in->player->pokemon[in->player->PrecedentPKID].moveSlots[movechoice - 1].id == MT_UNDEFINE || movechoice == -1)
            {
                scanf("%d", &movechoice);
                fgetc(stdin);
                if (movechoice == 0)
                {
                    back = 1;
                    break;
                }
                else
                    back = 0;
            }
            //First hit
            if (wild.speedStat <= player->pokemon[player->PrecedentPKID].speedStat && back == 0) //=====Player Hit first=====
            {
                handleAttack(&player->pokemon[player->PrecedentPKID], player->pokemon[player->PrecedentPKID].moveSlots[movechoice - 1], &wild); //Damage
            }
            else if (wild.speedStat > player->pokemon[player->PrecedentPKID].speedStat && back == 0) //=====Wild Hit first=====
                handleAttack(&wild, wild.moveSlots[rand() % wild.moveCount], &player->pokemon[player->PrecedentPKID]);
            if (player->pokemon[player->PrecedentPKID].currentHP <= 0) //Player pokemon dead
            {
                back = 1;
                system("clear");
                getColorByType(player->pokemon[player->PrecedentPKID].type1);
                printf("%s" reset " fainted !\n", player->pokemon[player->PrecedentPKID].name);
                getc(stdin);
                player->pokemonInLife -= 1;
                if (player->pokemonInLife >= 1)
                    pokemonList(player);
                else
                {
                    ++turn;
                    break;
                }
            }
            if (wild.currentHP <= 0)
            {
                break;
            }
            //Second hit
            if (wild.speedStat <= player->pokemon[player->PrecedentPKID].speedStat && back == 0) //=====Wild Hit Second=====
            {
                handleAttack(&wild, wild.moveSlots[rand() % wild.moveCount], &player->pokemon[player->PrecedentPKID]);
                ++turn;
            }
            else if (wild.speedStat > player->pokemon[player->PrecedentPKID].speedStat && back == 0) //=====Player Hit Second=====
            {
                handleAttack(&player->pokemon[player->PrecedentPKID], player->pokemon[player->PrecedentPKID].moveSlots[movechoice - 1], &wild); //Damage
                ++turn;
            }
            if (player->pokemon[player->PrecedentPKID].currentHP <= 0 && back == 0) //Player pokemon dead
            {
                system("clear");
                getColorByType(player->pokemon[player->PrecedentPKID].type1);
                printf("%s" reset " fainted !\n", player->pokemon[player->PrecedentPKID].name);
                getc(stdin);
                player->pokemonInLife -= 1;
                if (player->pokemonInLife >= 1)
                    pokemonList(player);
                else
                    break;
            }
        }

        //=========================================PKMN===========================================
        if (choice == 2)
        {
            //affichage
            int pkchoice = 0;
            system("clear");
            printf(BLU "Pokemons:\n" reset);
            for (int i = 0; i < player->pokemonCount; ++i)
            {
                printf("    %d. ", i + 1);
                getColorByType(player->pokemon[i].type1);
                printf("%s" reset ", lvl: %d, ",
                       player->pokemon[i].name,
                       player->pokemon[i].level);
                getColorByType(player->pokemon[i].type1);
                printType(player->pokemon[i].type1);
                printf(reset ", ");
                if (player->pokemon[i].type2 != T_NOT_SET)
                {
                    getColorByType(player->pokemon[i].type2);
                    printType(player->pokemon[i].type2);
                }
                printf(reset " [%.1f/%.1f]\n",
                       player->pokemon[i].currentHP,
                       getMaxHP(player->pokemon[i]));
            }
            printf(RED "    0. Leave\n" reset);
            pkchoice = NULL; //reinit choice
            //Choix
            while ((player->pokemon[player->PrecedentPKID].currentHP == 0) || pkchoice == NULL)
            {
                scanf("%d", &pkchoice);
                fgetc(stdin);
                if ((pkchoice - 1 == player->PrecedentPKID || pkchoice == 0) && player->pokemon[player->PrecedentPKID].currentHP != 0) //Si choix = precedent pokemon et precedent pokemon hp > 0
                {
                    back = 1;
                    break;
                }
                else if (pkchoice > player->pokemonCount)
                {
                    printf(RED "You can't choose a non-existent Pokemon !\n" reset);
                    pkchoice = NULL;
                }
                else if (player->pokemon[player->PrecedentPKID].currentHP != 0) //Si precedent pokemon hp > 0
                {
                    printf(RED "You can't choose a K.O Pokemon !\n" reset);
                    player->PrecedentPKID = pkchoice - 1; //Init precedent pokemon
                }
                else if (pkchoice == 0 && player->pokemon[player->PrecedentPKID].currentHP == 0) //Si choix = 0 et precedent pokemon hp = 0
                {
                    printf(RED "You can't leave without alive pokemon.\n" reset);
                    player->PrecedentPKID = pkchoice - 1; //Init precedent pokemon
                }
                back = 0;
            }
            if (back == 0)
            {
                system("clear");
                printf("Go ! ");
                getColorByType(player->pokemon[player->PrecedentPKID].type1);
                printf("%s" reset " !", player->pokemon[player->PrecedentPKID].name);
                fgetc(stdin);
                handleAttack(&wild, wild.moveSlots[rand() % wild.moveCount], &player->pokemon[player->PrecedentPKID]);
                if (player->pokemon[player->PrecedentPKID].currentHP <= 0) //Player pokemon dead
                {
                    back = 1;
                    system("clear");
                    getColorByType(player->pokemon[player->PrecedentPKID].type1);
                    printf("%s" reset " fainted !\n", player->pokemon[player->PrecedentPKID].name);
                    getc(stdin);
                    player->pokemonInLife -= 1;
                    if (player->pokemonInLife >= 1)
                        pokemonList(player);
                    else
                        break;
                }
                ++turn;
            }
        }

        //=========================================Items==========================================
        if (choice == 3)
        {
            system("clear");
            int itemChoice;
            printf(GRN "Items :\n" reset);
            printf("    1. Poké Ball x%d\n", player->pokeballCount);
            printf(RED "    0. Leave\n" reset);
            scanf("%d", &itemChoice);
            fgetc(stdin);
            if (itemChoice == 1 && player->pokeballCount > 0) //Lancer pokeball
            {
                system("clear");
                printf("%s used Poké BALL !\n", player->name);
                fgetc(stdin);
                system("clear");
                int sucess = pokemonCatch(player->pokeball[0], wild);
                player->pokeballCount -= 1;
                if (sucess == 1)
                {
                    catchPokemon(player, wild);
                    break;
                    ++turn;
                }
                else
                {
                    printWait();
                    getColorByType(wild.type1);
                    printf("%s" reset " escape !", wild.name);
                    fgetc(stdin);
                    handleAttack(&wild, wild.moveSlots[rand() % wild.moveCount], &player->pokemon[player->PrecedentPKID]);
                    if (player->pokemon[player->PrecedentPKID].currentHP <= 0) //Player pokemon dead
                    {
                        back = 1;
                        system("clear");
                        getColorByType(player->pokemon[player->PrecedentPKID].type1);
                        printf("%s" reset " fainted !\n", player->pokemon[player->PrecedentPKID].name);
                        getc(stdin);
                        player->pokemonInLife -= 1;
                        if (player->pokemonInLife >= 1)
                            pokemonList(player);
                        else
                            break;
                    }
                    if (wild.currentHP <= 0)
                    {
                        break;
                    }
                    ++turn;
                }
            }
        }
        //=========================================Flee===========================================
        if (choice == 4)
        {
            system("clear");
            ++attempts;
            //TODO faire un system d'escape
            if (player->pokemon[player->PrecedentPKID].speedStat >= wild.speedStat)
            {
                getColorByType(player->pokemon[player->PrecedentPKID].type1);
                printf("%s" reset " escape !\n", player->pokemon[player->PrecedentPKID].name);
                fgetc(stdin);
                break;
            }
            else
            {
                float OddsEscape = ((player->pokemon[player->PrecedentPKID].speedStat * 32) / ((wild.speedStat / 4) % 256)) + 30 * attempts;
                int randoms = rand() % 256;
                if (OddsEscape > 255)
                {
                    getColorByType(player->pokemon[player->PrecedentPKID].type1);
                    printf("%s" reset " escape !\n", player->pokemon[player->PrecedentPKID].name);
                    fgetc(stdin);
                    break;
                }
                else if (randoms < OddsEscape)
                {
                    getColorByType(player->pokemon[player->PrecedentPKID].type1);
                    printf("%s" reset " escape !\n", player->pokemon[player->PrecedentPKID].name);
                    fgetc(stdin);
                    break;
                }
                else
                {
                    getColorByType(player->pokemon[player->PrecedentPKID].type1);
                    printf(RED "%s can't escape !\n" reset, player->pokemon[player->PrecedentPKID].name);
                    fgetc(stdin);
                    handleAttack(&wild, wild.moveSlots[rand() % wild.moveCount], &player->pokemon[player->PrecedentPKID]);
                    if (player->pokemon[player->PrecedentPKID].currentHP <= 0) //Player pokemon dead
                    {
                        back = 1;
                        system("clear");
                        getColorByType(player->pokemon[player->PrecedentPKID].type1);
                        printf("%s" reset " fainted !\n", player->pokemon[player->PrecedentPKID].name);
                        getc(stdin);
                        player->pokemonInLife -= 1;
                        if (player->pokemonInLife >= 1)
                            pokemonList(player);
                        else
                            break;
                    }
                    if (wild.currentHP <= 0)
                    {
                        break;
                    }
                    ++turn;
                }
                system("clear");
            }
            system("clear");
        }

        if (wild.currentHP == 0)
        {
            system("clear");
            getColorByType(wildsp->primaryType);
            printf("%s" reset " fainted !\n", wild.name);
            getc(stdin);
            system("clear");
            getColorByType(player->pokemon[player->PrecedentPKID].type1);
            printf("%s" reset " gained %d EXP. Points !\n", player->pokemon[player->PrecedentPKID].name, getExperienceYield(wild));
            player->pokemon[player->PrecedentPKID].ExpPoints = player->pokemon[player->PrecedentPKID].ExpPoints + getExperienceYield(wild);
            getc(stdin);
            checkLvlUp(player->pokemon[player->PrecedentPKID]);
            getColorByType(player->pokemon[player->PrecedentPKID].type1);
            //printf
            printf("%s" reset ", lvl : %d " RED "[%.1f/%.1f] " reset HGRN "EXP. [%d/%d]" reset ""
                   "\n\n",
                   player->pokemon[player->PrecedentPKID].name,
                   player->pokemon[player->PrecedentPKID].level,
                   player->pokemon[player->PrecedentPKID].currentHP,
                   getMaxHP(player->pokemon[player->PrecedentPKID]),
                   player->pokemon[player->PrecedentPKID].ExpPoints,
                   getxpRequiredForLevel(player->pokemon[player->PrecedentPKID]));
            //
            getc(stdin);
        }
    }
}
 */
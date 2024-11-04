//--- 2023-2024 Spring BLG 252E Object Oriented Programing Assignment 1 ---//
//--------------------------//
//---Name & Surname: Madina Alzhanova
//---Student Number: 150220939
//--------------------------//

#ifndef _H
#define _H



//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

//-------------Do Not Add Any New Class(es)-------------//

class pokemon{
    //-------------Do Not Change Given Variables-------------//
    //-------------You Can Add New Variables If Neccessary-------------//
    private:
        string name;
        int hpValue;
        int atkValue;
    public:
        pokemon();      //default constr decl
        pokemon(string& p_name, int p_atkValue);    //p_ means passed parameter, const decl
        pokemon(const pokemon&);                    //copy const decl

        const string& getName(){return name;}       
        int getAtk(){return atkValue;}
        int getHp(){return hpValue;}

};

class pokedex{
    //-------------Do Not Change Given Variables-------------//
    //-------------You Can Add New Variables If Neccessary-------------//
    private:
        pokemon pokedexArray[100];
        int value;
    public:
       pokedex();           //constr decl
       void updatePokedex(pokemon& newPokemon);     //method decl                   //const kerek pa?
       const void printPokedex();
       pokemon* getPokedexArray(){return pokedexArray;};
       
};

class player{
    private:
    //-------------Do Not Change Given Variables-------------//
    //-------------You Can Add New Variables If Neccessary-------------//
        string name;
        int pokemonNumber;
        int pokeballNumber;
        int badgeNumber;
        pokemon playerPokemon;
    public:
        pokedex playerPokedex;
        player();
        player(const std::string& name, const pokemon playerPokemon);
        int showPokemonNumber(){return pokemonNumber;}
        int showPokeballNumber(){return pokeballNumber;}
        int showBadgeNumber(){return badgeNumber;}
        pokemon getPokemon(){return playerPokemon;}
        void battleWon(){
            badgeNumber++;
            pokeballNumber+=3;
        }
        void catchPokemon(){
            pokemonNumber++;
            pokeballNumber--;
        }

};

class enemy{
    //-------------Do Not Change Given Variables-------------//
    //-------------You Can Add New Variables If Neccessary-------------//
    private:
        string name;
        pokemon enemyPokemon;
    public:
        enemy();
        enemy(string& p_name, pokemon);
        const pokemon getPokemon(){return enemyPokemon;}
        const string getName(){return name;}


        
};

#endif
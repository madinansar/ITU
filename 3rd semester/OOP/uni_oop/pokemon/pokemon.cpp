//--- 2023-2024 Spring BLG 252E Object Oriented Programing Assignment 1 ---//
//--------------------------//
//---Name & Surname:
//---Student Number:
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <string.h>

#include "pokemon.h"

using namespace std;

//-------------You Can Add Your Functions Down Below-------------//

pokemon:: pokemon(){                    //default constructor def
     name = "";
     hpValue =0;
     atkValue=0;
} 
pokemon:: pokemon(string& p_name, int p_atkValue){      //param constructor def
    name = p_name;
    hpValue = 100;
    atkValue = p_atkValue;
}
pokemon::pokemon(const pokemon& original){              //copy constrcutor def
    name = original.name;
    atkValue = original.atkValue;
    hpValue = original.hpValue;
}


pokedex::pokedex(){         //constructor initializes to 0
    value = 0;
}
void pokedex::updatePokedex(pokemon& newPokemon){

for(int i = 0; i<value; i++){                                                      
    if(pokedexArray[i].getName() == newPokemon.getName()){
        std::cout<<("such pokemon already exists")<< endl;
    } else{
        
        pokedexArray[value] = newPokemon;
        value++;
        std::cout<<("new pokemon added")<< endl;
    }
}
}
const void pokedex::printPokedex(){
    std::cout<<"Pokemons in pokedex:"<<endl;
    for(int i =0; i<value; i++){
        std:cout<<pokedexArray[i].getName()<<endl;

    }
}




player::player(){
    name = "";
    pokemonNumber = 0;
    pokeballNumber = 0;                                                             //is it really 0?
    badgeNumber = 0;
    playerPokemon = pokemon();
    playerPokedex = pokedex();
}

player::player(const std::string& p_name, const pokemon p_playerPokemon){
    name = p_name;
    playerPokemon = p_playerPokemon;
}


enemy::enemy(){
    name = "";
    enemyPokemon = pokemon();
}
enemy::enemy(string& p_name, pokemon p_enemyPokemon){
    name = p_name;
    enemyPokemon = p_enemyPokemon;
}

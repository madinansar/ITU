//--- 2023-2024 Spring BLG 252E Object Oriented Programing Assignment 1 ---//
//--------------------------//
//---Name & Surname: Madina Alzhanova
//---Student Number: 150220939
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream> 
#include <stdio.h>
#include <string.h>
#include <fstream>

#include "pokemon.h"

using namespace std;

//-------------Do Not Change These Global Variables-------------//
int NAME_COUNTER = 0;   //Use this to keep track of the enemy names
int POK_COUNTER = 0;    //Use this to keep track of the pokemon names
int PLAYER_POKEMON_ATTACK = 20; //You don't have to use this variable but its here if you need it
int ENEMY_POKEMON_ATTACK = 10;  //You don't have to use this variable but its here if you need it
//--------------------------------------------------------------//

//---If Necessary Add Your Global Variables Here---// 
// 
//
//
//-------------------------------------------------//

//-------------Do Not Change These Function Definitions-------------//
string* readEnemyNames(const char*);
string* readPokemonNames(const char*);
player characterCreate(string, int);
void mainMenu();
void fightEnemy(player*, string*, string*);
void catchPokemon(player*, string*);
//------------------------------------------------------------------//

//---If Necessary Add Your Function Definitions Here---// 
//
//
//
//-----------------------------------------------------//

//-------------Do Not Change This Function-------------//
int main(int argc, char* argv[]){
	system("clear");

    //---Creating Enemy and Pokemon Name Arrays---//
    string* enemyNames = readEnemyNames(argv[1]);         
    string* pokemonNames = readPokemonNames(argv[2]);
    

    string playerName;
    int pokemonChoice;

    cout << "Welcome to the Pokemon Game! \n" << endl;
    cout << "Please enter your name: "; 
    cin >> playerName;
    cout << "Please choose one of these pokemons as your pokemon: \n1- Bulbasaur \n2- Charmender \n3- Squirtle \nChoice: ";
    cin >> pokemonChoice;

    //---Character Creation--//
    player newPlayer = characterCreate(playerName, pokemonChoice);
    
    int menuChoice;

    while(true){
        mainMenu(); 
        cin>>menuChoice;

        switch (menuChoice){
        case 1:
            fightEnemy(&newPlayer, enemyNames, pokemonNames);
            break;
        case 2:
            catchPokemon(&newPlayer, pokemonNames);
            break;
        case 3:
            cout<<newPlayer.showPokemonNumber()<<endl;
            break;
        case 4:
            cout<<newPlayer.showPokeballNumber()<<endl;
            break;
        case 5:
            cout<<newPlayer.showBadgeNumber()<<endl;
            break;
        case 6:
            cout << endl;
            cout << "------- Pokedex -------" <<endl;
            newPlayer.playerPokedex.printPokedex();
            break;
        case 7:
            //---Deletes Dynamic Arrays From Memory and Exits---//
            delete[] enemyNames;
            delete[] pokemonNames;
            return EXIT_SUCCESS;
            break;
  
        default:
            cout << "Please enter a valid number!!!" << endl;
            break;
        }
    }
    return EXIT_FAILURE;
};
//-----------------------------------------------------//

//-------------Code This Function-------------//
string* readEnemyNames(const char* argv){
    string filename = argv;
    ifstream file;
    file.open(filename); 

    string line;
    getline(file, line);

    if(file.fail()){
        cout<<"Failed to open file"<<endl;
        return nullptr;
    }
    int length;
    stoi(line) >> length;
    string* enemyNames = new string[length];

    for(int i=0; i<length; i++){
        getline(file, line);
        line >> enemyNames[i];
    }

    file.close();
    return enemyNames;
};
//-----------------------------------------------------//

//-------------Code This Function-------------//
string* readPokemonNames(const char* argv){
    string filename = argv;
    ifstream file;
    file.open(filename); 

    string firstLine;
    getline(file, firstLine);

    if(file.fail()){
        cout<<"Failed to open file"<<endl;
        return nullptr;
    }
    int length;
    file >> length;
    string* pokemonNames = new string[length];

    for(int i=0; i<length; i++){
        file >> pokemonNames[i];
    }

    file.close();
    return pokemonNames;
};
//-----------------------------------------------------//

//-------------Code This Function-------------//
player characterCreate(string playerName, int pokemonChoice){ //\n1- Bulbasaur \n2- Charmender \n3- Squirtle \nChoice: ";
    string pokemonName;
     switch (pokemonChoice){
        case 1:
            pokemonName = "Bulbasaur";
            break;
        case 2:
            pokemonName = "Charmender";
            break;
        case 3:
            pokemonName = "Squirtle";
            break;
        default:
            cout << "Please enter a valid number!!!" << endl;
            break;
        }
        pokemon chosenPokemon(pokemonName, PLAYER_POKEMON_ATTACK);
        player newPlayer(playerName, chosenPokemon);

    return newPlayer;
};
//--------------------------------------------//

//-------------Do Not Change This Function-------------//
void mainMenu(){
    cout << endl;
    cout << "-------- Menu --------" << endl;
    cout << "1. Fight for a badge" << endl;
    cout << "2. Catch a Pokemon" << endl;
    cout << "3. Number of Pokemons" << endl;
    cout << "4. Number of Pokeballs " << endl;
    cout << "5. Number of Badges" << endl;
    cout << "6. Pokedex" << endl;
    cout << "7. Exit" << endl;
    cout << endl;
    cout << "Choice: ";
};
//-----------------------------------------------------//

//-------------Code This Function-------------//
void fightEnemy(player* newPlayer, string* enemyNames, string* pokemonNames){

   bool enemyIsInPokedex = false;

   pokemon enemysPokemon(pokemonNames[POK_COUNTER], ENEMY_POKEMON_ATTACK);

     cout << "You encounter with " << enemyNames[NAME_COUNTER] << " and their pokemon " << enemysPokemon.getName() << ". " 
         << enemysPokemon.getName() << " Health: " << enemysPokemon.getHp() << " Attack: " << enemysPokemon.getAtk() << ". " 
         << "1- Fight. "
         << "2- Runaway. "
         << "Choice: ";
         string choice;
        cin >> choice;
    while(choice=="1"){               //when 1: update pokedex if needed, fight, show result&choices
        if(choice=="2"){                //when 2: exit fight function
            break;
            return;
        }
        for(int i = 0; i<newPlayer->showPokemonNumber(); i++){
    if(newPlayer->playerPokedex.getPokedexArray()[i].getName() == enemysPokemon.getName()){ //compare every item in pokedx to enemy's pokemon
        enemyIsInPokedex = true;
        break;
    }
   }
   if(enemyIsInPokedex == false){
    newPlayer->playerPokedex.updatePokedex(enemysPokemon);  //if not in pokedex yet, update=add it
   }

   int playerHealth = newPlayer->getPokemon().getHp();
   int enemyHealth = enemysPokemon.getHp();

   while(playerHealth>0 && enemyHealth>0){
    playerHealth = playerHealth - enemysPokemon.getAtk();
    enemyHealth = enemyHealth - newPlayer->getPokemon().getAtk();
   }

   if(playerHealth <= 0){
    cout << "Your Pokemons Healt: " << playerHealth << ". " << "Misty Pokemons Healt: " << enemyHealth << ". " << "You Lose!(.*)";
   } else {
    cout << "Your Pokemons Healt: " << playerHealth << ". " << "Misty Pokemons Healt: " << enemyHealth << ". " << "You Won!(.*)";
    newPlayer->battleWon();
   }

    cout << "Your Pokemons Healt: " << playerHealth << ". " 
         << "Misty Pokemons Healt: " << enemyHealth << ". " 
         << "1- Fight. " 
         << "2- Runaway. " 
         << "Choice: ";
    }

   
POK_COUNTER++;
NAME_COUNTER++;    
return;
};
//--------------------------------------------//

//-------------Code This Function-------------//
void catchPokemon(player* newPlayer, string* pokemonNames){
       cout << "You encounter with " << pokemonNames[POK_COUNTER] << 
       " Health: " << newPlayer->getPokemon().getHp() << 
       " Attack: " << newPlayer->getPokemon().getAtk() << "(.*)1- Catch(.*)2- Runaway(.*)Choice: "<<endl;
         string choice;
        cin >> choice;
        if(choice=="2"){                //when 2: exit fight function
            POK_COUNTER++;
            NAME_COUNTER++;
            return;
        }
    if(choice=="1"){               //when 1: catch, update pokedex if needed, show result&choices
    newPlayer->catchPokemon();
    cout << "You catch " << pokemonNames[POK_COUNTER] << "(.*)";

   bool enemyIsInPokedex = false;
   pokemon enemysPokemon(pokemonNames[POK_COUNTER], ENEMY_POKEMON_ATTACK);
   
   
   for(int i = 0; i<newPlayer->showPokemonNumber(); i++){
    if(newPlayer->playerPokedex.getPokedexArray()[i].getName() == enemysPokemon.getName()){ //compare every item in pokedx to enemy's pokemon
        enemyIsInPokedex = true;
        break;
    }
   }
   if(enemyIsInPokedex == false){
    newPlayer->playerPokedex.updatePokedex(enemysPokemon);  //if not in pokedex yet, update=add it
   }
    }
    POK_COUNTER++;
    NAME_COUNTER++;
    return;
};
//--------------------------------------------//

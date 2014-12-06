//SQUAD- Greg, ryan, steven, jeremy
//  Trainer.cpp
//  CreatureTrainer
//
//  You may NOT #include any .h files we provide you (Battle, Creature, CreatureType,
//  EECSRandom, Party, PrintHelper)
//  other than the ones name "ClassX.h" and "Trainer.h"
//  You may #include other <> libraries if you wish to
//
//  Created by Jeremy Gibson on 11/4/14.
//  Copyright (c) 2014 Jeremy Richard Gibson. All rights reserved.
//

#include <iostream>
#include <sstream>
#include "Trainer.h"
#include "Class1.h"
#include "Class2.h"
#include "Class3.h"
#include "Class4.h"
#include "Class5.h"


using namespace std;

string Trainer::makeMove(stringstream& situation)
{
    string situationString = situation.str();// get situation
    cout << situationString;
    vector<string> lines = splitString(situationString, "\n");// split lines
    int healthline = -1;
    for (int i=0; i<lines.size(); i++)
    {
        string line = lines[i];
        char c = line[0];
        if (c == '|')
        {
            healthline = i;
        }
    }
    int enemyline = -1;
    string enemystring = "";
    for (int j = 0; j < lines.size(); ++j)
    {
        string line = lines[j];
        char c1 = line[0];
        if (c1 == 'E')
        {
            enemyline = j;
            enemystring = lines[enemyline];
        }
    }
    char enemname;
    int s = 1;
    int index2 = 1;
    enemname = enemystring[6];
    int damage = 0;
    for (int x = 0; x < enemystring.size(); ++x)
    {
        if (enemystring[x] == '1')
        {
            if (enemystring[x+1] == 48)
            {
                damage = 10;
            }
            if (enemystring[x+1] == 49)
            {
                damage = 11;
            }
            if (enemystring[x+1] == 50)
            {
                damage = 12;
            }
        }
        if (enemystring[x] >= 49 && enemystring[x] <= 59 && damage == 0)
        {
            damage = (int)enemystring[x];
            damage -= 48;
        }
    }
    if (damage == 12)
    {
        creature_to_be_captured = enemystring[6];
    }
    
    vector<string> creatureHealthBits = splitString(lines[healthline], "|");
    int inplaycreatures = 4;
    double healthpercentages[inplaycreatures];
    int healthy[inplaycreatures];
    int totalh[inplaycreatures];
    int j = 0;
    int m = 0;
    int z = 0;
    //string names[4];
    char creaturetypes[4];
    int currentpokemon = -1;
    int temp1 = -1;
    for (int i=1; i<creatureHealthBits.size()-1; i++)
    {
        //CreatureType mine;
        char mine;
        stringstream ss;
        ss << creatureHealthBits[i];
        string name;
        ss >> name;// Names of creatures
        if (name[0] == '*')
        {
            currentpokemon = i-1;
            mine = name[1];
        }
        else
        {
            mine = name[0];
        }
        int health;
        ss >> health; // Health of creatures
        char slash;
        ss >> slash; // slash = '/'
        int maxHealth;
        ss >> maxHealth; // maxHealth = 10
        healthy[j]= health;
        totalh[m]=maxHealth;
        healthpercentages[z] = health/maxHealth;
        creaturetypes[m] = mine;
        ++m;
        ++j;
        ++z;
    }
    // Check healths
    int total = 0;
    double avgtotal;
    string response = "";
    for (int i = 0; i < inplaycreatures; ++i)
    {
        total += totalh[i];
    }
    avgtotal = total/inplaycreatures;
    int t = 0;
    for (int i = 0; i < inplaycreatures; ++i)
    {
        t += healthy[i];
    }
    double avghealth = 0;
    avghealth = t/inplaycreatures;
    string creatureline;
    int defeatedline = -1;
    for (int j = 0; j < lines.size(); ++j)
    {
        string line = lines[j];
        char c1 = line[9];
        if (c1 == 'd')
        {
            defeatedline = j;
            creatureline = lines[defeatedline];
        }
    }
    if (creatureline[28] == creature_to_be_captured)
    {
        int type = (int)creature_to_be_captured - 65;
        int min = totalh[0];
        int index3 = -1;
        for (int y = 0; y < inplaycreatures; ++y)
        {
            if (totalh[y] <= min)
            {
                min = totalh[y]; // Find weakest player in party
                index3 = y;
            }
        }
    }
    if (healthy[currentpokemon] <= damage)
    {
        for (int i = 0; i < inplaycreatures; ++i)
        {
            if (healthpercentages[i] == 1
                && healthy[i] >= 15 && i != currentpokemon)
            {
                if (i == 0)
                {
                    response = "s1";
                }
                if (i == 1)
                {
                    response = "s2";
                }
                else if (i == 2)
                {
                    response = "s3";
                }
                else if (i == 3)
                {
                    response = "s4";
                }
                return response;
            }
        }
        for (int i = 0; i < inplaycreatures; ++i)
        {
            if (healthy[i] >= 15 && i != currentpokemon)
            {
                if (i == 0)
                {
                    response = "s1";
                }
                else if (i == 1)
                {
                    response = "s2";
                }
                else if (i == 2)
                {
                    response = "s3";
                }
                else if (i == 3)
                {
                    response = "s4";
                }
                return response;
            }
        }
        bool alllow = true;
        for (int i = 0; i < inplaycreatures; ++i)
        {
            if (healthy[i] >= 7)
            {
                alllow = false;
            }
        }
        if (alllow)
        {
            response = "r";
            return response;
        }
        else
        {
            int max = healthy[0];
            int index = -1;
            for (int i = 0; i < inplaycreatures; ++i)
            {
                if (healthy[i] >= max)
                {
                    max = healthy[i];
                    index = i;
                }
            }
            if (index == 0)
            {
                response = "s1";
            }
            else if (index == 1)
            {
                response = "s2";
            }
            else if (index == 2)
            {
                response = "s3";
            }
            else if (index == 3)
            {
                response = "s4";
            }
            return response;
            // find highest health and pick the one
        }
    }
    else
    {
        response = "a";
        return response;
    }
}


void Trainer::finalSituation(stringstream& situation) {
    cout << situation.str();
    
}



vector<string> Trainer::splitString(string inString, string splitOn) {
    vector<string> elements;
    string substring;
    
    size_t splitIndex = inString.find(splitOn),
    substrStart = 0;
    
    // keep searching until no spaces remain
    while (splitIndex != string::npos) {
        substring = inString.substr(substrStart, splitIndex - substrStart);
        elements.push_back(substring);
        substrStart = splitIndex + 1;
        // start at next character after finding substring
        splitIndex = inString.find(splitOn, substrStart);
    }
    // add last element to vector
    substring = inString.substr(substrStart, inString.length() - substrStart);
    elements.push_back(substring);
    
    return elements;
}

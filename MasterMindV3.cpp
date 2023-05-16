#include <iostream>
#include <string>
#include <array>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>

const int nb_couleurs = 2;

void saisie_code(std::string &code)
{
    code="";
    std::cout<<"Saisissez le code secret : ";
    while(code.length() != 4)
    {
        code += getch();
    }
    std::cout<<std::endl;
}

bool verif(std::string reponse, std::string code)
{
    if(reponse.length()!=code.length())
        return false;
    else if(reponse==code)
        return true;
    else return false;
}

int occurence_couleur(char couleur, std::string suite_couleurs)
{
    int compteur=0;
    for(int i=0 ; i<suite_couleurs.length(); ++i)
    {
        if(suite_couleurs[i]==couleur)
            compteur++;
    }
    return compteur;
}

void indice(std::string tentative, std::string code, int &bon_ordre, int &mauvais_ordre)
{
    bon_ordre = 0 , mauvais_ordre = 0;
    // Tableaux de booléens pour éviter de compter plusieurs fois la même couleur
    bool trouve_code[4] = {false};
    bool trouve_tentative[4] = {false};
    
    // Comptage des couleurs dans le bon ordre
    for (int i = 0; i < 4; ++i) {
        if (tentative[i] == code[i]) {
            bon_ordre++;
            trouve_code[i] = true;
            trouve_tentative[i] = true;
        }
    }
    
    // Comptage des couleurs correctes mais mal placées
    for (int i = 0; i < 4; ++i) {
        if (!trouve_tentative[i]) {
            for (int j = 0; j < 4; ++j) {
                if (!trouve_code[j] and tentative[i] == code[j]) {
                    mauvais_ordre++;
                    trouve_code[j] = true;
                    break;
                }
            }
        }
    }
    std::cout<<"Vous avez "<<bon_ordre<<" couleurs dans le bon emplacement "<<std::endl;
    std::cout<<"Vous avez "<<mauvais_ordre<<" couleurs correctes mais mal placees "<<std::endl;
}

void resolution(std::string& reponse, std::string& code) 
{
    int bon_ordre=0, mauvais_ordre=0;
    int occurence_rouge = 0;
    reponse = "RRRR";
    std::cout << "tentative " << reponse << std::endl;
    if(verif(reponse, code)) {
        std::cout << "La reponse est : " << reponse << std::endl;
        return;
    }
    else {
        indice(reponse, code, bon_ordre, mauvais_ordre);
        occurence_rouge = bon_ordre;
        std::cout<<"occurence rouge est : "<<occurence_rouge<<std::endl;
    }
    bool trouve_code[4] = {false};
    while(occurence_rouge > 0) 
    {
        for(int i = 0; i < 4; ++i) 
        {
            reponse = "BBBB";
            int mauvais_ordre1 = 0;
            if(!trouve_code[i]) 
            {
                reponse[i] = 'R';
                std::cout << "tentative : " << reponse << std::endl;
                indice(reponse, code, bon_ordre, mauvais_ordre1);
                if(mauvais_ordre1 == mauvais_ordre - 2 or mauvais_ordre1==0) 
                {
                    trouve_code[i] = true;
                    break;
                }
                mauvais_ordre = mauvais_ordre1;
            }
        }
        occurence_rouge--;
    }
    for(int i = 0; i < 4; ++i) {
        std::cout<<trouve_code[i]<<std::endl;
    }
    for(int i = 0; i < 4; ++i)
    {
        if(trouve_code[i]) {
            reponse[i] = 'R';
        }
        else if(!trouve_code[i]) {
            reponse[i] = 'B';
        }
    }
    std::cout << "La reponse est : " << reponse << std::endl;
}
    


int main()
{
    std::string code, reponse; int mauvais_ordre=0, bon_ordre=0;
    saisie_code(code);
    resolution(reponse,code);
    return 0;
}
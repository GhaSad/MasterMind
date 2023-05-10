#include <iostream>
#include <string>
#include <array>
#include <conio.h>
#include <cstdlib>
#include <ctime>

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

void genere_reponse(std::string &reponse, int nb_couleurs)
{
    char couleurs[4] = {'B', 'R', 'J', 'V'};
    reponse = "";
    std::srand(std::time(NULL));
    for(int i = 0; i < 4; ++i)
    {
        int index = std::rand() % nb_couleurs;
        reponse += couleurs[index];
    }
    std::cout<<reponse<<std::endl;
}

void melange(std::string &rep) 
{
    std::srand(std::time(NULL));
    int n = rep.length();
    for (int i = n - 1; i > 0; --i) 
    {
        int j = std::rand() % (i + 1);
        char temp = rep[i];
        rep[i] = rep[j];
        rep[j] = temp;
    }
}

bool verif(std::string reponse, std::string code)
{
    if(reponse.length()!=code.length())
        return false;
    else if(reponse==code)
        return true;
    else return false;
}

int compt_couleur(char couleur, std::string suite_couleurs)
{
    int compteur=0;
    for(int i=0 ; i<suite_couleurs.length(); ++i)
    {
        if(suite_couleurs[i]==couleur)
            compteur++;
    }
    return compteur;
}

void indice(std::string reponse, std::string code, int &mauvaise_couleur, int &mauvais_ordre)
{
    mauvaise_couleur=0;
    for(int i=0 ; i<4 ; ++i)
    {
        int occ_rep = compt_couleur(reponse[i],reponse), occ_code = compt_couleur(reponse[i],code);
        if (occ_rep != occ_code)
            if(occ_code < occ_rep)
                mauvaise_couleur = occ_rep - occ_code;
            else 
                mauvaise_couleur = occ_code - occ_rep;
    }
    mauvais_ordre=0;
    for(int i=0 ; i<4 ; i++)
    {
        if(reponse[i]!=code[i])
            mauvais_ordre++;
    }
    std::cout<<"Vous avez "<<mauvaise_couleur<<" mauvaises couleurs "<<std::endl;
    std::cout<<"Vous avez "<<mauvais_ordre<<" couleur dans le mauvais emplacement "<<std::endl;
}

void resolution(std::string &reponse, std::string code, int &mauvaise_couleur, int &mauvais_ordre, int nb_couleurs)
{
    genere_reponse(reponse,nb_couleurs);
    while(!verif(reponse,code))
    {
        indice(reponse,code,mauvaise_couleur,mauvais_ordre);
        if((mauvaise_couleur=0) and (mauvais_ordre>0))
        {
            melange(reponse);
            std::cout<<"tentative :" <<reponse<<std::endl;
            indice(reponse,code,mauvaise_couleur,mauvais_ordre);
        }
        else if((mauvaise_couleur>0) and (mauvais_ordre>0))
        {
            if(!verif(reponse,code))
            {
                char l='';
                l=reponse[1];
                reponse[1]=reponse[3];
                reponse[3]=reponse[2];
                reponse[2]=reponse[3];
            }
        }
    }
}

int main()
{
    std::string code, reponse; int nb_couleurs=2, mauvaise_couleur,mauvais_ordre;
    saisie_code(code);
    std::cout<<"Nb tentatives ? "; 
    resolution(reponse,code,mauvaise_couleur,mauvais_ordre,nb_couleurs);
    return 0;
}
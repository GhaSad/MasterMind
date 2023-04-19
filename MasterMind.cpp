#include <iostream>
#include <array>
#include <string>
#include <conio.h>

const int taille_max = 4;
using tab = std::array<std::string,taille_max>;

struct rangee
{
    tab t;
};

void init_jeu(rangee &r, int &nb_tentatives, int &nb_couleurs)
{
    std::cout<<"Combien de tentatives ?"; std::cin>>nb_tentatives;
    std::cout<<"Combien de couleur ? "; std::cin>>nb_couleurs;
}

void init_tab(rangee &r)
{
    for(int i=0 ; i < taille_max ; ++i)
    {
        r.t[i]="";
    }
}

void saisie_joueurs(std::string &j1, std::string &j2)
{
    std::cout<<"Quel est le nom du premier joueur ? "; std::cin>>j1;
    std::cout<<"Quel est le nom du deuxieme joueur ? "; std::cin>>j2;
}

void saisie_code(std::string &code, std::string j1, rangee r)
{
    std::cout<<j1<<" est en train de saisir le code secret : ";
    while(code.length() != taille_max)
    {
        code += getch();
    }
    std::cout<<std::endl;
}

bool verif(std::string code, std::string reponse)
{
    if(reponse.length()!=code.length())
        return false;
    else if(reponse != code)
        return false;
    else return true;
}

void jeu(std::string code, std::string j2, std::string j1, int nb_tentatives)
{
    int tour=0;
    std::string reponse;
    while(tour<=nb_tentatives)
    {
        tour++;
        std::cout<<j2<<" a vous de jouer : "; std::cin>>reponse;
        if(verif(code,reponse))
        {
            std::cout<<j2<<" a gagne en "<<tour<<" tours !";
            return;
        }
        else
        {
            std::string indice;
            std::cout<<"reponse incorrecte, "<<j1<<" va saisir l'indice :";
            std::cin>>indice;
        }
    }
    std::cout<<j2<<" a perdu ! "<<j1<<" est donc le gagnant de cette manche ";
}

int main()
{
    rangee r; int nb_tentatives, nb_couleurs;
    init_jeu(r,nb_tentatives,nb_couleurs);
    init_tab(r);
    std::string j1, j2;
    saisie_joueurs(j1,j2);
    std::string code; int tour=0;
    saisie_code(code,j1,r);
    jeu(code,j2,j1,nb_tentatives);
    return 0;
}
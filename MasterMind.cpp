#include <iostream>
#include <array>
#include <string>
#include <conio.h>

const int taille_max = 10;
using tab = std::array<std::string,taille_max>;

struct rangee
{
    tab t;
    int n; //taille du tableau et de la rangée
};

void init_jeu(rangee &r, int &nb_tentatives, int &nb_couleurs)
{
    std::cout<<"Combien de tentatives ?"; std::cin>>nb_tentatives;
    std::cout<<"Combien de couleur ? "; std::cin>>nb_couleurs;
    std::cout<<"Taille des rangées ? " ; std::cin>>r.n
}

void init_tab(rangee &r)
{
    for(int i=0 ; i < r.n ; ++i)
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
    std::cout<<j1<<" est en train de saisir le code couleur : ";
    while(code.length() != r.n)
    {
        code += getch();
    }
}

int main()
{
    rangee r;
    init_tab(r);
    std::string j1, j2;
    saisie_joueurs(j1,j2);
    std::string code;
    saisie_code(code,j1);
    return 0;
}
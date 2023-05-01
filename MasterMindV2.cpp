#include <iostream>
#include <string>
#include <array>
#include <cstdlib>
#include <ctime>


void init_jeu(std::string &j1, int &nb_manches, int &nb_couleurs)
{
    char rep;
    std::cout<<"Bienvenue dans le menu du jeu MasterMind. Voulez-vous une explication du deroulement du jeu ? (o/n)"; std::cin>>rep;std::cout<<std::endl;
    if(rep=='o')
    {
        std::cout<<"Le jeu se deroule entre deux joueurs : "<<std::endl;
        std::cout<<"Le premier decide du code couleur secret "<<std::endl;
        std::cout<<"Et le deuxieme possede un nombre de tentatives choisis pour deviner l'ordre des couleurs "<<std::endl;
        std::cout<<"Apres la saisie de la reponse, le premier joueur donne un indice qui indique le nombre de couleurs correctes ainsi que leurs ordres "<<std::endl;
        std::cout<<"Vous pouvez choisir le nombre de manches a jouer, ainsi que la difficulte "<<std::endl;
        std::cout<<"Facile -> 2 couleurs "<<std::endl;
        std::cout<<"Moyen -> 3 couleurs "<<std::endl;
        std::cout<<"Difficle -> 4 couleurs "<<std::endl;
        std::cout<<"Les couleurs disponibles sont : "<<std::endl;
        std::cout<<"Rouge(R) , Bleu(B), Jaune(J), Violet(V) "<<std::endl;
        std::cout<<"Si la manche se termine avant que le code ne soit devine, le premier joueur gagne, dans le cas contraire, le deuxieme joueur emporte la manche "<<std::endl<<std::endl;
    }
    std::cout<<"Nom du joueur ? " ; std::cin>>j1;
    std::cout<<"Nombre de manches ?" ; std::cin>>nb_manches;
    char difficulte; 
    std::cout<<"Quelle difficulte ? (facile(f),moyen(m),difficile(d)) "; std::cin>>difficulte;
    if(difficulte=='f')
        nb_couleurs=2;
    else if(difficulte=='m')
        nb_couleurs=3;
    else if(difficulte=='d')
        nb_couleurs=4;
    else std::cout<<"Difficulte parametree a moyen par defaut !"<<std::endl;
    using couleur = std::array<std::string,4>;
    couleur c = {"Rouge","Bleu","Jaune","Violet"};
    std::cout<<"Les couleurs disponibles sont donc : ";
    int compteur_couleur = 0;
    while(compteur_couleur < nb_couleurs)
    {
        std::cout<<c[compteur_couleur]<<" ";
        compteur_couleur++;
    }
    std::cout<<std::endl;
}

void genere_code(std::string &code, int nb_couleurs)
{
    std::srand(std::time(nullptr));
    char alpha[4] = {'R', 'B', 'J', 'V'};
    int length = 4;
    if (nb_couleurs == 2) {
        length = 2;
    } else if (nb_couleurs == 3) {
        length = 3;
    }
    code = "";
    for (int i = 0; i < 4; ++i) {
        code = code + alpha[std::rand() % length];
    }
    std::cout << code << " ";
}

int main()
{
    std::string j1, code; int nb_couleurs, nb_manches;
    init_jeu(j1,nb_manches,nb_couleurs);
    genere_code(code,nb_couleurs);
    return 0;
}
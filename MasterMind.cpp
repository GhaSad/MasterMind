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

void init_jeu(int &nb_tentatives, int &nb_couleurs, int &nb_manches)
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
    std::cout<<"Combien de tentatives ? "; std::cin>>nb_tentatives;
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
    std::cout<<"Nombre de manches ? "; std::cin>>nb_manches; std::cout<<std::endl;
    std::cout<<"Que le jeu commence ! " ; std::cout<<std::endl<<std::endl;
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

void saisie_code(std::string &code, std::string j1)
{
    code="";
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

void jeu(std::string &code, std::string j2, std::string j1, int nb_tentatives, std::string &gagnant)
{
    int tour=0;
    std::string reponse;
    saisie_code(code,j1);
    while(tour<=nb_tentatives)
    {
        tour++;
        std::cout<<j2<<" a vous de jouer : "; std::cin>>reponse;
        if(verif(code,reponse))
        {
            std::cout<<j2<<" a gagne en "<<tour<<" tours !"<<std::endl;
            gagnant = j2;
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
    gagnant=j1;
}

int main()
{
    rangee r; int nb_tentatives, nb_couleurs, nb_manches, score_j1=0 , score_j2=0;;
    init_jeu(nb_tentatives,nb_couleurs,nb_manches);
    init_tab(r);
    std::string j1, j2;
    saisie_joueurs(j1,j2);
    std::string code; int tour=0;
    int manche=0;
    while(manche <= nb_manches)
    {
        std::string gagnant ; 
        manche++;
        std::cout<<"Manche numero "<<manche<<std::endl;
        jeu(code,j2,j1,nb_tentatives,gagnant);
        if(gagnant == j1) score_j1++;
        else score_j2++;
        if(manche==nb_manches)              // Si jamais le nb_manches est impaire, on sort de la boucle while
            break;
        manche++;
        std::cout<<"Manche numero "<<manche<<std::endl;
        jeu(code,j1,j2,nb_tentatives,gagnant);
        if(gagnant == j1) score_j1++;
        else score_j2++;
    }
    if(score_j1 > score_j2)
        std::cout<<j1<<" remporte la partie !! Le score final est :"<<score_j1<<"-"<<score_j2<<std::endl;
    else if(score_j1 < score_j2)
        std::cout<<j2<<" remporte la partie !! Le score final est :"<<score_j2<<"-"<<score_j1<<std::endl;
    else
        std::cout<<"Les deux joueurs sont a egalite !!"<<std::endl;
    return 0;
}
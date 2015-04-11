#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>

//ligne que j'ai modifiée
//deusieme essai

using namespace std;


void cutTransition(string message,vector<vector<set<int>>> &transition)
{
    string mot="";
    string space=" ";
    vector<int> values;

    int i=0,j,conv,cpt=0;

    j = message.find(space);
    while( j != string::npos )  //Tant la ligne n'est pas vide
    {
        mot=message.substr(i,j-i);  //
        conv=stoi(mot);             //conversion du mot en entier(int)
        values.push_back(conv);

        i=j+1;                      //
        j = message.find(space,i);  //Change de mot grace au espace
    }

    mot=message.substr(i);  //
    conv=stoi(mot);         //conversion du mot en entier(int)
    values.push_back(conv); //


    int etatDepart = values[0];
    int lettre = values[1];
    int etatArrivee = values[2];
    transition[etatDepart][lettre].insert(etatArrivee); //on entre le tous dans: vector<vector<set<int>>>

}

int cutInitTerm(string message,bool init,vector<int> &initiaux,vector<int> &terminaux)
{
    string mot="";
    string space=" ";
    int i=0,j,conv,cpt=0;

    j = message.find(space);
    while( j != string::npos )
    {
        mot=message.substr(i,j-i);
        conv=stoi(mot); ///Conversion
        if(init==true)
            initiaux.push_back(conv);
        else
            terminaux.push_back(conv);

        i=j+1;
        j = message.find(space,i);
        cpt++;
    }

    mot=message.substr(i);
    conv=stoi(mot); ///Conversion
    if(init==true)
        initiaux.push_back(conv);
    else
        terminaux.push_back(conv);
    return cpt+1;
}

void enleverEpsilon(vector<vector<set<int>>> &transition,int n,vector<int> &initiaux)
{
    for (int i=0; i<n; i++)
    {
        for(auto it:transition[i][2])
        {
            for(auto init:initiaux) //On regarde si on passe l'état devient initial
            {
                if(i==init)
                    initiaux.push_back(it);
            }

            //On recherche les liaisons si l'état initial et un etat terminal d'une autre transition
            for (int x=0; x<n; x++)
                for(int y=0; y<3; y++)
                    for (auto tr:transition[x][y])
                        if (tr=it && tr==i)
                            transition[x][y].insert(it);

            transition[i][2].erase(it); //A la fin, on supprime epsilon
        }
    }
}



string affichage(int nbEtat,vector<int> initiaux,vector<int> terminaux,vector<vector<set<int>>> transition)
{
    string str;
    str += "nb etat: " + to_string(nbEtat) + "\n";
    //Afichage des états initiaux
    str += "Initiaux: ";
    for(auto i:initiaux)
        str += to_string(i) + " ";
    str += "\n";
    //Afichage des états terminaux
    str += "Terminaux: ";
    for(auto t:terminaux)
        str += to_string(t) + " ";
    str += "\n";
    //Affichage des transitions
    for (int i=0; i<nbEtat; i++)
        for (int j=0; j<3; j++)
            for (auto tr:transition[i][j])
                str += to_string(i) + " " + to_string(j) + " " + to_string(tr) + "\n";


    return str;
}

int main()
{
    vector<int>initiaux;
    vector<int>terminaux;

    vector<vector<set<int>>> transition;
    int nbEtat, nbEtatInit, nbEtatTerm;

    ifstream fichier("af.txt", ios::in);  // on ouvre en lecture

    if(fichier)  // si l'ouverture a fonctionné
    {
        string ligne;
        ///----- Nombre d'états -----///
        getline(fichier, ligne);
        nbEtat=stoi(ligne);
        transition.resize(nbEtat);
        for(int i=0; i<transition.size(); i++)
            transition[i].resize(3);

        ///----- Etats initiaux -----///
        getline(fichier, ligne);
        nbEtatInit=cutInitTerm(ligne,true,initiaux,terminaux);

        ///----- Etats terminaux -----///
        getline(fichier, ligne);
        nbEtatTerm=cutInitTerm(ligne,false,initiaux,terminaux);

        ///----- Transitions -----///
        while(getline(fichier, ligne))  // tant que l'on peut mettre la ligne dans "contenu"
        {
            cutTransition(ligne,transition);
        }
        fichier.close();
    }
    else
    {
        cerr << "Impossible d'ouvrir le fichier !" << endl;
    }

    string message;
    message += "----- Automate ND de base -----\n";
    message += affichage(nbEtat,initiaux,terminaux,transition);
    message += "\n";
    enleverEpsilon(transition,nbEtat,initiaux);
    message += "----- Automate ND Sans-E -----\n";
    message += affichage(nbEtat,initiaux,terminaux,transition);
    message += "\n";

    message += "----- Automate AFD -----\n";
    message += affichage(nbEtat,initiaux,terminaux,transition);
    cout << message << endl;

}


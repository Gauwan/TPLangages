#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>

//ligne que j'ai modifiée
//deusieme essai

using namespace std;

vector<int>initiaux;
vector<int>terminaux;

vector<vector<set<int>>> transition;
vector<set<int>> tmp;
vector<int> tmp2;

void cutTransition(string message,int ligne)
{
    string mot="";
    string space=" ";
    int i=0,j,conv,cpt=0;

    j = message.find(space);
    while( j != string::npos )
    {

        mot=message.substr(i,j-i);
        conv=stoi(mot); ///Conversion
        tmp2.push_back(conv);


        i=j+1;
        j = message.find(space,i);
        cpt++;
    }

    mot=message.substr(i);
    conv=stoi(mot); ///Conversion
    tmp2.push_back(conv);
    transition.push_back(tmp);
}

int cutInitTerm(string message,bool init)
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

void enleverEpsilon() //Suppression des transition epsilon
{
    /*int Initi;
    int Trans;
    int Termi;

    for(auto t:transition)
    {
        if(Trans==2) // 2:Epsilon
        {
            for(auto tm:tmp)//Tant qu'il y a des etat qui arrive sur la transition
            {
            ///    t.push_back();  //On ajoute une transition
            }
        ///    t.pop_back();   //On enleve la transition epsilon
        }
    }*/
}

void traitement() //On cherche les nouveaux états
{/*
    int test;
    for(auto i:initiaux)
        test=initiaux[0];
*/
}

int main()
{
    int nbEtat, nbEtatInit, nbEtatTerm;

    ifstream fichier("af.txt", ios::in);  // on ouvre en lecture

    if(fichier)  // si l'ouverture a fonctionné
    {
        string ligne;
        ///----- Nombre d'états -----///
        getline(fichier, ligne);
        cout << "nb etat: " <<ligne<<endl;
        nbEtat=stoi(ligne);

        ///----- Etats initiaux -----///
        getline(fichier, ligne);
        cout << "initiaux: " <<ligne<<endl;
        nbEtatInit=cutInitTerm(ligne,true);

        ///----- Etats terminaux -----///
        getline(fichier, ligne);
        cout << "terminaux: " <<ligne<<endl;
        nbEtatTerm=cutInitTerm(ligne,false);

        ///----- Transitions -----///
        while(getline(fichier, ligne))  // tant que l'on peut mettre la ligne dans "contenu"
        {
            cout << "t: "<< ligne << endl;  // on l'affiche
           //cout << transition.back(tmp[0]);

        }
        fichier.close();
    }
    else
        cerr << "Impossible d'ouvrir le fichier !" << endl;

    return 0;
}

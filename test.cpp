#include <iostream>
#include<vector>
using namespace std;

class Employe
{
protected:
    //attribut d'objet
        string Nom;
        string Matricule;
        double Salaire= 0.0;

public:
        // constructeur
        Employe();
        Employe(string, string, double);


        // Accesseur et mutateur
        virtual string get_nom()
            {return Nom;}
        virtual string get_matricule()
            {return Matricule;}
         double get_salaire()
            {return Salaire;}
        virtual double set_salaire(double s)=0;
  //          {this-> Salaire=s;}

        //surcharge
        bool operator<(Employe const&)const;
        friend ostream& operator<< (ostream& flux, const Employe& employe);

        //destructeur
        virtual ~Employe()
            {cout << "Un employe est detruit" << endl;}
};
// constructeur
Employe::Employe(string nom, string matricule, double salaire): Nom(nom), Matricule(matricule), Salaire(salaire){}

//surcharge
bool Employe::operator<(Employe const& employe)const
{
    if (Salaire< employe.Salaire )
        {return true; }
    else
        {return false;}
}
ostream& operator<< (ostream& flux, const Employe& employe)
{
    flux<<employe.Nom<<" de matricule= "<<employe.Matricule<<" a un salaire de: "<<employe.Salaire<<endl;
    return flux;
}



class Enseignant: virtual public Employe
{
protected:
    //attribut d'objet
        string Specialite;
        float Charge_horraire= 10;
public:
    // constructeEnseignantur
        Enseignant(string, string,double, string, float);

        double set_salaire(double s)
        {this-> Salaire= s*4*25;
        return Salaire;
        }

        virtual double get_salaire()
            { return Salaire;}
        virtual ~Enseignant()
            {cout << "Un Enseignant est detruit" << endl;}
};
// constructeur
Enseignant::Enseignant(string nom, string matricule, double salaire, string specialite, float charge): Employe(nom, matricule,0), Specialite(specialite), Charge_horraire(charge){}


class Agent_administratif: virtual public Employe
{
protected:
        //attribut d'objet
        int Nbre_annee_ancien=0;
public:
    // constructeur
    Agent_administratif();
        Agent_administratif(string, string, double,int);
        virtual void set_nbre_annee_ancien(int n)
            {this->Nbre_annee_ancien= n;}
        virtual ~Agent_administratif()
            {cout << "Un Agent_administratif est detruit" << endl;}
};
// constructeur
Agent_administratif::Agent_administratif(string nom, string matricule, double salaire, int nbre_annee_ancien): Employe(nom, matricule, salaire),Nbre_annee_ancien(nbre_annee_ancien){}


class Directeur: virtual public Agent_administratif
{
public:
    // constructeur
    Directeur(string, string, double, int);
    virtual double set_salaire(double s)
    {
        this->Salaire =1000+30*Nbre_annee_ancien;
        return Salaire;
    }
    virtual ~Directeur()
            {cout << "Un Directeur est detruit" << endl;}
};
// constructeur
Directeur::Directeur(string nom, string matricule, double salaire, int nbre_annee_ancien):Agent_administratif(nom, matricule, salaire, nbre_annee_ancien),Employe(nom,Matricule,salaire) {}


class Chef_de_departement : public Enseignant, public Agent_administratif
{public:
    Chef_de_departement(string nom, string num_mat, double salaire, int nbre, string special,int charge) : Agent_administratif(nom, num_mat, salaire,nbre ), Enseignant(nom, num_mat, salaire, special,charge) ,Employe(nom,num_mat,salaire){}
        double set_salaire(double s){return this->Salaire=s*25+200;}
       // {set_salaire(charge* 25 +200);}

    virtual string get_nom()
        { return Nom; }
    virtual string get_matricule()
        { return Matricule; }
    virtual ~Chef_de_departement(){cout << "chef de departement detruit" << endl;}
};



class Fonctionnaire: public Agent_administratif
{
public:
    Fonctionnaire(string, string, double, int);
     double set_salaire(double s)
        {
        this->Salaire =500+30*Nbre_annee_ancien;
        return Salaire;
        }
    virtual ~Fonctionnaire()
            {cout << "Un Fonctionnaire est detruit" << endl;}
};
Fonctionnaire::Fonctionnaire(string nom, string matricule, double salaire, int nbre_annee_ancien):Agent_administratif(nom, matricule, salaire, nbre_annee_ancien ), Employe(nom,Matricule,salaire){}



class Centre
{
private:
    string Nom;
    vector <Employe*> ensemble_employe;
public:
    Centre(string nom):Nom(nom){ensemble_employe.reserve(100);};
    void ajouter_employe(Employe &);
    double charge_salariale();
    vector <Employe*> get_ensemble_employe();
    virtual string get_nom()
        {return Nom;}
    friend ostream& operator<<(ostream& flux, const Centre& centre );
    virtual ~Centre()
            {cout << "Un Centre est detruit" << endl;}
};
void Centre::ajouter_employe(Employe &employe)
{
    ensemble_employe.push_back(&employe);
}

vector <Employe*> Centre::get_ensemble_employe()
{
    return ensemble_employe;
}
double Centre::charge_salariale()
{
    double charges=0;
    double sal;
    for (int i=0;i< ensemble_employe.size();i++)
    {
        charges+= ensemble_employe[i]->get_salaire();
    }
return charges;
}
ostream& operator<<(ostream& flux, const Centre& centre )
{


    flux <<"Dans le centre "<<centre.Nom<<" il y'a "<<centre.ensemble_employe.size()<<" employes "<< endl;

    for(int i=0;i<centre.ensemble_employe.size();i++)
        {
            cout<<(centre.ensemble_employe[i])<<endl;
        }
    return flux;

}
int main ()
{
    double salairechef;
    Centre centre("MAHBOUBA");



    Enseignant *en;
    en=new Enseignant("salih ben salah", "ense3E", 300, "info", 20);
    en->set_salaire(300);
    centre.ajouter_employe(*en);
   // cout << *en;




    Fonctionnaire *fonct;
    fonct=new Fonctionnaire ("saleh matr", " fonct343R", 200, 2);
    fonct->set_salaire(200);
    centre.ajouter_employe(*fonct);
   // cout << centre;

    Chef_de_departement *chef_departement ;
    chef_departement=new Chef_de_departement("riadh chakrounn", "chefdep2344 ", 0,5, "math", 30);
    chef_departement->set_salaire(200);
    centre.ajouter_employe(*chef_departement);

    Directeur *directeur;
    directeur=  new Directeur("fatma radhia", " dir3567",300, 4);
    directeur->set_salaire(4);
    centre.ajouter_employe(*directeur);

    cout<< centre<< endl;
    double charge_salariale;
    cout<< "la charge salariale de ce centre est egale a  " << centre.charge_salariale()<< endl;
    cout<< endl;

    delete& directeur;
    delete& fonct;
    return 0;
}

// ajouter _declspec(dllexport) devant tout public pour permettre à la dll d'exporter ces méthodes 
// pour qu'elles puissent être utilisées par d'autres applications ou programmes


#ifndef _IMAGE_CLASSE_
#define _IMAGE_CLASSE_

#include <string>
#include <vector>
#include <stack>
#include <QtCore>


#include "ImageNdg.h"
#include "ImageCouleur.h"


#define EUCLIDEAN(a,b) ((a-b) * (a-b)) 
#define MAX_ITER 100

// structure PIXEL utile pour empilements successifs
typedef struct {
    int abs;
    int ord;
} PIXEL;

typedef struct  {
	float  moyenne;
	int    surface;
} SIGNATURE_Ndg;

typedef struct  {
	float  moyenne[3];
	int    surface;
} SIGNATURE_Couleur;

typedef struct {
	float		centreGravite_i;
	float		centreGravite_j;
	int			surface;
	std::string codeFreeman; // au sens V8
	std::vector<float> histoFreeman;
	int			premierPt_i; // premier point rencontré sens de parcours avant
	int			premierPt_j;
	int			rectEnglob_Hi; // coins supérieur gauche et inférieur droit
	int			rectEnglob_Hj;
	int			rectEnglob_Bi;
	int			rectEnglob_Bj;
	float		perimetre; // au sens V8
} SIGNATURE_Forme;

// définition classe Image Classe --> images étiquetées pour analyse objets, nuées dynamiques pour analyse régions

class Q_DECL_EXPORT CImageClasse {

	///////////////////////////////////////
	private : 
	///////////////////////////////////////

		int              m_iHauteur;
		int              m_iLargeur;
		std::string      m_sNom;
		long			 m_lNbRegions;

		unsigned long*   m_pucPixel;

	///////////////////////////////////////
	public : 
	///////////////////////////////////////
		
		// constructeurs
        CImageClasse();
        CImageClasse(int hauteur, int largeur);
         CImageClasse(const CImageNdg& im, std::string choix = "V8"); // objets
        CImageClasse(const CImageClasse& in, std::string choix = "sans", std::string voisinage = "V8"); // re-étiquetage éventuel
        CImageClasse(const CImageNdg& im, int nbClusters = 2, std::string choix = "aleatoire"); // clustering
        CImageClasse(const CImageCouleur& im, int nbClusters = 2, std::string choix = "aleatoire", int plan=0); // plan dans HSV, non dans espace 3D

         ~CImageClasse();  // destructeur

		// sauvegarde au format bmp
		// attention : cast des informations car pertes potentielles
         void sauvegarde(); // sauvegarde data au format BMP avec cast des long en char

		// pouvoir accéder à un pixel par image(i)
        unsigned long& operator() (int i) const {
		return m_pucPixel[i];
		}

		// pouvoir accéder à un pixel par image(i,j)
        unsigned long& operator() (int i, int j) const {
            return m_pucPixel[i*m_iLargeur+j];
		}

		// opérateur copie image par imOut = imIn
        CImageClasse& operator=(const CImageClasse& im);

		// get et set 

        int lireHauteur() const {
            return m_iHauteur;
		}

        int lireLargeur() const {
		return m_iLargeur;
        }

        int lireNbRegions() const {
            return m_lNbRegions;
		}

        std::string lireNom() const {
            return m_sNom;
		}

        int lireNbPixels() const {
		return m_iHauteur*m_iLargeur;
		}

        void ecrireHauteur(int hauteur) {
		m_iHauteur = hauteur;
		}

        void ecrireLargeur(int largeur) {
		m_iLargeur = largeur;
		}

        void ecrireNom(std::string nom) {
		m_sNom = nom;
		}

        void ecrireNbRegions(int nb) {
		m_lNbRegions = nb;
		}

		// signatures pour Image_Ndg et Image_Couleur
        std::vector<SIGNATURE_Ndg> signatures(const CImageNdg& img, bool enregistrementCSV = false);
         std::vector<SIGNATURE_Couleur> signatures(const CImageCouleur& img, bool enregistrementCSV = false);
        QImage GetQImageClasse();
		// affichage
        CImageCouleur affichage(const std::vector<SIGNATURE_Couleur>& tab, const std::string& methode = "moyenne");
		
		// affichage avec contoure coloré
        CImageCouleur affichage(const std::vector<SIGNATURE_Ndg>& tab, int R = 255, int G = 0, int B = 0);

		// sélection région par région
        CImageClasse selection(const std::string& methode = "selection", int classe=0);

		// filtrage selon critères taille, bords, etc
        CImageClasse filtrage(const std::string& methode = "taille", int taille=50, bool miseAZero = true);

		// signatures forme pour Image_Ndg et Image_Couleur
        std::vector<SIGNATURE_Forme> signatures(bool enregistrementCSV = false);

		// Mutation
        CImageClasse mutation(const CImageNdg& img);

		// Distance
        CImageClasse distance(std::string eltStructurant, unsigned long valBord);

		// Mutation Inverse
        CImageNdg mutation(const std::string& methode = "troncature"); // troncature par défaut

		// Croissance de region
        CImageClasse croissanceRegion(const CImageNdg& in, int iGerme, int jGerme, double tolerance);

        int comptageobjetNDG(CImageNdg im);
        int comptageobjetNDG(CImageCouleur im, int plan = 0);
        std::vector<int> calculSurf(CImageNdg im);
        std::vector<int> calculPeri(CImageNdg im);
        std::string LectureCDB(CImageNdg img);
};

#endif //_IMAGE_CLASSE_

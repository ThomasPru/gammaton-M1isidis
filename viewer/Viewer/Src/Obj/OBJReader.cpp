// OBJReader.cpp: implementation of the COBJReader class.
//
//////////////////////////////////////////////////////////////////////

#include "OBJReader.hpp"
#include "OBJTriangle.hpp"
#include "OBJGroup.hpp"
#include "OBJLight.hpp"

#include "../Cpoint.hpp"


#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;



// Hypothèses : 
// (1) un groupe de facettes ne possède qu'un seul matériau
//     ce qui permet de stocker ce matériau non pas au/
//     niveau des triangles, mais au niveau de chaque
//     groupe.
// (2) chaque groupe ne possède qu'un seul nom (on ne gère pas
//     l'appartenance des facettes à plusieurs groupes). Ceci
//     permet également de stocker le matériau su niveau du groupe
// (3) chaque groupe a un nom différent. En cas d'absence de nom,
//     un nom defaultXXX est donné au groupe, avec XXX le numéro
//     du groupe sans nom trouvé

OBJReader::OBJReader(const string& dataDirectory,
		     const string& filename)
{
  char lettre;
  char buffer[1024];
  int coord_textures = 0, normales = 0;
  double coeff [3] = {.8, .8, .8};
  OBJMaterial *materiau_base = new OBJMaterial("default");
  OBJMaterial *currentmaterial=NULL;
  matlist.push_back(materiau_base);
  int normDec=0;// decalage dans la numérotation des normales

  string fullname = dataDirectory+"/"+filename;

  FILE * pfichier_obj = fopen(fullname.c_str(),"r");
  if(!pfichier_obj) return;

  // initialisation des groupes 
  int nbDefaultGroup=0;
  OBJGroup *gcurrent;// groupe en cours de construction


  OBJTriangle *P;
  while(!feof(pfichier_obj))
    {
      lettre = fgetc(pfichier_obj);
      switch(lettre)
	{
	default:
	  fgets(buffer,sizeof(buffer),pfichier_obj);
	  break;

	case 'g':{// apparition d'un nouveau groupe
	  // --- recherche du nom du groupe
	  char nom[256]={'\0'};
	  int nbNoms=0;
	  int i=0;
	  // lire la ligne du fichier
	  fgets(buffer,sizeof(buffer),pfichier_obj);
	  // analyse de la ligne
	  while(buffer[i]!='\0'){
	    if(isspace(buffer[i])){
	      i++;
	      continue;
	    }
	    if(sscanf(buffer+i,"%s",nom)!=EOF){
	      // on a un nom (le premier) pour le groupe
	      nbNoms=1;
	      break;
	    }
	  }// while
	  if(!nbNoms){
	    sprintf(nom,"default%03d",nbDefaultGroup);
	    nbDefaultGroup++;
	  }
	  // --- création du nouveau groupe
	  gcurrent = new OBJGroup(nom);
	  gliste.addGroup(gcurrent);
	  gcurrent->setMaterial(materiau_base); // par défaut

	  //cout<< "current = " << gliste.size() << endl;
	}
	  break;
	case '\n':
	  break;
	case 'm':{
	  fscanf(pfichier_obj," %s %s ",buffer,buffer);
	  this->importMaterial(dataDirectory.c_str(),(const char*)buffer);
	  break;
	}
	case 'l':{
	  char fullLightName[256];
	  fscanf(pfichier_obj," %s %s ",buffer,buffer);
	  sprintf(fullLightName,"%s/%s",dataDirectory.c_str(),buffer);
	  this->importLight((const char*)fullLightName);
	  pointlist.clear();
	  vecteurlist.clear();
	  break;
	}
	case 'v':
	  lettre = fgetc(pfichier_obj);
	  switch(lettre)
	    {
	    default:
	      break;
	    case ' ':// vertex
	      {
// 		char x[20], y[20], z[20];
		double x, y, z;
		fscanf(pfichier_obj," %lf %lf %lf ", &x, &y, &z);
		Cpoint p;
// 		p.assign(atof(x),atof(y),atof(z));
		p.assign(x, y, z);
// 		cout << x << "->" << (float)x << endl;
		pointlist.push_back(p);
		normales = coord_textures = 0;
	      }
	      break;				
	    case 'n':// normale
	      {
// 		char x[20], y[20], z[20];
		double x, y, z;
		fscanf(pfichier_obj," %lf %lf %lf ", &x, &y, &z);
		Cvector v;
		v.assign(x, y, z);
		vecteurlist.push_back(v);
		normales = 1;
	      }
	      break;
	    case 't':// texture
// 	      char x[20], y[20];
	      double u, v;
	      fscanf(pfichier_obj," %lf %lf ", &u, &v);
	      Cpoint t;
	      t.assign(u,v,0.0);
	      texturelist.push_back(t);
	      coord_textures = 2;

	      // 	      printf("texture : %f %f\n", atof(x),atof(y));
	      break;
	    }
	  break;
	case 'f':
	  {
	    int v[4], t[4], n[4], i;
	    char buffer[256], token[256];
	    bool texture=true, normale=true;
	    // lire la ligne
	    i=0;
	    do buffer[i]=fgetc(pfichier_obj); while(buffer[i++]!='\n');
	    buffer[i]='\0';

	    // analyser la ligne
	    int lg=0; // indice de parcours de la ligne
	    int nbsom = 4;// nombre de sommets de la facette

	    for(int i=0; i<4; i++){
	      token[0]='\0';
	      // passer les blancs
	      while(isspace(*(buffer+lg))) lg++;
	      sscanf(buffer+lg,"%s",token);
	      //  	    printf("token=|%s|\n", token);
	      lg+=strlen(token);
	      // tester l'existence du quatrième sommet
	      if((i==3)&&(token[0]=='\0')){
		nbsom=3;
		break;
	      }
	      // lire un indice de sommet
	      sscanf(token,"%d",&v[i]);
	      // lire une texture
	      if(sscanf(token,"%*d/%d",&t[i])<=0){// pas de texture
		texture = false;
		if(sscanf(token,"%*d//%d",&n[i])<=0){//pas de normale
		  normale = false;
		}
// 	    cout << token << " ";
// 	    if(texture) cout << "t";
// 	    if(normale) cout << "n";
// 	    cout << endl;
		continue;
	      }
	      // il y a une texture
	      if(sscanf(token,"%*d/%*d/%d",&n[i])<=0)
		normale = false;

	    }
	    bool erreurNormale = false;
	    if(!normale){// créer une normale constante pour la facette
	      Cvector v1, v2, N;
	      Cpoint a, b, c;
	      a = pointlist[v[0]-1];
	      b = pointlist[v[1]-1];
	      c = pointlist[v[2]-1];
	      v1.assign(b.x-a.x, b.y-a.y, b.z-a.z);
	      v2.assign(c.x-a.x, c.y-a.y, c.z-a.z);
	      N.assign(v1.y*v2.z-v1.z*v2.y,
		       v1.z*v2.x-v1.x*v2.z,
		       v1.x*v2.y-v1.y*v2.x);
	      float norme = sqrt(N.x*N.x+N.y*N.y+N.z*N.z);
	      if(norme==0.0){
		cout << "erreur : norme nulle" << endl;
		erreurNormale = true;
	      }
	      N.assign(N.x/norme, N.y/norme, N.z/norme);
	      vecteurlist.push_back(N);
	      n[0]=n[1]=n[2]=n[3]=vecteurlist.size();
// 	      cout << "!n : " << n[0] << " " << norme << endl;
// 	      cout << v1 << " " << v2 << endl;
// 	      cout << a << " - " << b << " - " << c << endl;
// 	      cout << v[0] << " " << v[1] << " " << v[2] << endl;
	      normDec++;// création d'une normale supplémentaire
	    }else{
	      // appliquer le décalage du à l'insertion éventuelle
	      // de normales constantes
	      for(int i=0; i<4; i++) n[i] += normDec;
	    }
	    if(erreurNormale) break;
	    // création de la première facette
	    P = new OBJTriangle();
	    P->setVertices(v[0]-1, v[1]-1, v[2]-1);
	    if(texture) P->setTextures(t[0]-1, t[1]-1, t[2]-1);
	    // corriger l'indice de normale pour tenir compte
	    // de la numérotation OBJ qui commence à 1
	    P->setNormals(n[0]-1, n[1]-1, n[2]-1);
	    // voir pour le matériel ...
	    gcurrent->addFacet(P);
	    

	    // création éventuelle de la seconde facette
	    if(nbsom==4){
	      P = new OBJTriangle();
	      P->setVertices(v[0]-1, v[2]-1, v[3]-1);
	      if(texture) P->setTextures(t[0]-1, t[2]-1, t[3]-1);
	      P->setNormals(n[0]-1, n[2]-1, n[3]-1);
	      // voir pour le matériau
	      gcurrent->addFacet(P);
	    }

	    break;

	  }
	case 'u':
	  fscanf(pfichier_obj," %s %s ",buffer, buffer);

	  for(matiter=matlist.begin(); 
	      matiter!=matlist.end() && !((**matiter)==string(buffer));
	      matiter++);
	  if(matiter!=matlist.end()){
	    cout << "buffer = " << buffer << " - mat = " << **matiter << endl;
	    currentmaterial=*matiter;
	  }
	  else{
	    cout<<"Erreur de chargement : material "<<buffer<<" unknown.\n";
	    currentmaterial = materiau_base;
	  }
	  // dans les obj, un même groupe peut posséder plusieurs matériaux
	  // On va donc couper les groupes et créer autant de groupes que
	  // de matériaux présents dans le groupe original. 
	  if(gcurrent->size()==0){
	    // le groupe vient d'être créé
	    gcurrent->setMaterial(currentmaterial);
	  }else{// le groupe existait déjà et possédait un matériau
	    // récupérer le nom du groupe actuel
	    string curname = gcurrent->getName();
	    curname += "Suite";
	    // créer un nouveau groupe
	    gcurrent = new OBJGroup(curname);
	    gliste.addGroup(gcurrent);
	    // lui ajouter le nouveau materiau
	    gcurrent->setMaterial(currentmaterial);
	  }
	  

	  break;
	}

    }

  fclose(pfichier_obj);

  //   cout << gliste << endl;
  cout << "fin chargement obj" << endl;
#ifdef OUT
  cout << gliste << endl;
#endif

}

void OBJReader::importMaterial(const char* dataDirectory,
			       const char* filename){
  char fullName[256];
  sprintf(fullName,"%s/%s",dataDirectory, filename);
  // Ouverture du fichier
  ifstream in(fullName, ios::in);
  if(!in.is_open()){
    cout << "error opening " << fullName << " file ..." << endl;
    return;
  }

  cout << "Loading materials from " << fullName << "..." << endl;
  string buffer;
  char cbuffer[256];
  float Kd[3], Ka[3], Ks[3], alpha, shini, illum;
  OBJMaterial *newMat=NULL;
  string name_nouvelle_matiere;
  string textureName;

  while(1){
    // tenter une lecture d'un début de ligne
    in >> buffer;
    // tester l'arrivée en fin de fichier
    if(in.eof()) break; 
    // tester une ligne de commentaire
    if(buffer[0]=='#'){
      in.getline(cbuffer,256); // passer la ligne de commentaire
      continue;
    }
    // définition d'un nouveau matériau
    if(buffer=="newmtl"){
      in >> name_nouvelle_matiere;
      newMat = new OBJMaterial(name_nouvelle_matiere);
      mlist.push_back(name_nouvelle_matiere);
      matlist.push_back(newMat);    
      continue;
    }
    // lecture du coeff ambiant
    if(buffer=="Ka"){
      in >> Ka[0] >> Ka[1] >> Ka[2];
      if(in.fail()){
	cout<<"error reading Ka for material "<<name_nouvelle_matiere<<endl;
      }else{
	if(newMat!=NULL) newMat->setKa(Ka);
      }
      continue;
    }
    // lecture du coeff diffus
    if(buffer=="Kd"){
      in >> Kd[0] >> Kd[1] >> Kd[2];
      if(in.fail()){
	cout<<"error reading Kd for material "<<name_nouvelle_matiere<<endl;
      }else{
	if(newMat!=NULL) newMat->setKd(Kd);
      }
      continue;
    }
    // lecture du coeff spéculaire
    if(buffer=="Ks"){
      in >> Ks[0] >> Ks[1] >> Ks[2];
      if(in.fail()){
	cout<<"error reading Ks for material "<<name_nouvelle_matiere<<endl;
      }else{
	if(newMat!=NULL) newMat->setKs(Ks);
      }
      continue;
    }
    // lecture de d (alpha)
    if(buffer=="d"){
      in >> alpha;
      if(in.fail()){
	cout<<"error reading d for material "<<name_nouvelle_matiere<<endl;
      }else{
	if(newMat!=NULL) newMat->setRefractionIndex(alpha);
      }
      continue;
    }
    // lecture de Ns (shini)
    if(buffer=="Ns"){
      in >> shini;
      if(in.fail()){
	cout<<"error reading Ns for material "<<name_nouvelle_matiere<<endl;
      }else{
	if(newMat!=NULL) newMat->setShininess((shini/1000)*128);// ???
      }
      continue;
    }
    // lecture de illum (?)
    if(buffer=="illum"){
      in >> illum;
      if(in.fail()){
	cout<<"error reading illum for material "<<name_nouvelle_matiere<<endl;
      }
      continue;
    }
    // lecture de map_Ka ou map_Kd ou map_Ks
    if((buffer=="map_Ka")||(buffer=="map_Kd")||(buffer=="map_Ks")){
      in >> textureName;
      if(in.fail()){
	cout << "error reading texture name for material ";
	cout << name_nouvelle_matiere << endl;
      }else{
	if(newMat!=NULL){
	  string name(dataDirectory);
	  name.append("/");
	  name.append(textureName);
	  cout << "texture : " << name << endl;

	  if(buffer=="map_Ka") newMat->setMapKa(name);
	  else
	    if(buffer=="map_Kd") newMat->setMapKd(name);
	    else newMat->setMapKs(name);
	}
      }
      continue;
    }

    cout << "Unknown attribute " << buffer << endl;
    in.getline(cbuffer, 256);
  }

  in.close();

  cout << "End loading materials." << endl;

#ifdef OUT
  for(matiter = matlist.begin(); matiter != matlist.end() ;  matiter++)
    cout << **matiter << endl;
#endif
}



void OBJReader::drawScene(){
  cout << "------------------------" << endl;
  
  OBJGroupList test =  gliste;
  
  for(int i = 0; i < test.size(); i++){ //liste des cubes
    gliste = test;
    int nb = test.getGroup(i)->size();
    vector<float> colors;
    colors.push_back(test.getGroup(i)->getMaterial().getAmbiantColor().r);
    colors.push_back(test.getGroup(i)->getMaterial().getAmbiantColor().g);
    colors.push_back(test.getGroup(i)->getMaterial().getAmbiantColor().b);
    for (int j = 0; j < nb; j++){ // nombre de facettes par objet
      glBegin(GL_TRIANGLES);
      glColor3f(colors[0], colors[1], colors[2]);
      glVertex3f(getPointListInd(gliste.getGroup(i)->getFacet(j)->getVertex(0).getCoordinate()).getX(),
		 getPointListInd(gliste.getGroup(i)->getFacet(j)->getVertex(0).getCoordinate()).getY(),
		 getPointListInd(gliste.getGroup(i)->getFacet(j)->getVertex(0).getCoordinate()).getZ());
      
      glVertex3f(getPointListInd(gliste.getGroup(i)->getFacet(j)->getVertex(1).getCoordinate()).getX(),
		 getPointListInd(gliste.getGroup(i)->getFacet(j)->getVertex(1).getCoordinate()).getY(),
		 getPointListInd(gliste.getGroup(i)->getFacet(j)->getVertex(1).getCoordinate()).getZ());
  
      glVertex3f(getPointListInd(gliste.getGroup(i)->getFacet(j)->getVertex(2).getCoordinate()).getX(),
		 getPointListInd(gliste.getGroup(i)->getFacet(j)->getVertex(2).getCoordinate()).getY(),
		 getPointListInd(gliste.getGroup(i)->getFacet(j)->getVertex(2).getCoordinate()).getZ());
      glEnd();
      
    }
    
  }
  test.clear();

}


void OBJReader::importLight(const char* filename)
{
  char buffer[256];
  char lightName[256];
  FILE *f;
  float x, y, z;
  OBJLight *source=NULL;
  OBJMaterial *matlight=NULL;
  int line=0; /**< numéro de laligne en cours de lecture. */


  if((f=fopen(filename,"r"))==NULL){
    cout<< "error opening light file " << filename << endl;
    return;
  }

  cout << "loading lights from " << filename << endl;

  srcVertices.clear();

  while(fscanf(f,"%s",buffer)!=EOF){

    line++;

    if(strcmp(buffer,"newlight")==0){// lire le nom de la source
      fscanf(f,"%s", lightName);
      source = new OBJLight(lightName);
    }

    if(strcmp(buffer,"category")==0){// créer la source
      // pas de sources ponctuelle sous Maxwell
      int type;
      fscanf(f,"%d",&type);
      source->setType(type);
    }

    if(strcmp(buffer,"samplingrate")==0){// définir le taux d'échantillonnage
      int sr;
      fscanf(f,"%d", &sr);
      if(sr>0) source->setSamplingRate(sr);
    }

    if(strcmp(buffer,"intensity")==0){// définir l'intensité de la source
      float v[3];
      fscanf(f,"%f %f %f",v, v+1, v+2);
      source->setColor(v[0], v[1], v[2]);
    }

    if(strcmp(buffer,"position")==0){// définir la position d'une source ponctuelle
      double x, y, z;
      fscanf(f,"%lf %lf %lf",&x, &y, &z);
      source->setPointLightPosition(x, y, z);
    }

    if(strcmp(buffer,"v")==0){// rajouter un sommet
      if(fscanf(f,"%f %f %f", &x, &y, &z)!=3)
	cout << "error reading vertex line " << line << endl;
      else{
	Cpoint p; p.assign(x,y,z);
	srcVertices.push_back(p);
      }
    }

    if(strcmp(buffer,"f")==0){// ajout d'une facette à la source
      int i1, i2, i3, i4;
      int nbsom = fscanf(f,"%d %d %d %d", &i1, &i2, &i3, &i4);
      source->addTriangle(i1-1, i2-1, i3-1);

      if(nbsom==4)
	source->addTriangle(i1-1, i3-1, i4-1);

    }

    if(strcmp(buffer,"g")==0 || strcmp(buffer,"endlight")==0){// fin de définition d'une source
      source->setPower(1000.0);// non prévu dans les .lig
      srclist.push_back(source);
      source = NULL;
    }

    if(*buffer=='#'){// commentaire : passer la ligne
      char k;
      do fscanf(f,"%c",&k); while(k!='\n');
    }

  }

  fclose(f);


  cout << "end loading light " << filename << endl;
  //#define OUT
#ifdef OUT
  for(list<OBJLight*>::iterator it=srclist.begin();
      it!=srclist.end(); it++)
    cout << **it << endl;
#endif

}



#define OUT

void OBJReader::toLxs(ostream& lxsFile){

  // démarrer la description des paramètres globaux
  lxsFile << "WorldBegin" << endl << endl;

  cout << "export des matériaux en cours ..." << endl;
  for(list<OBJMaterial*>::iterator it=matlist.begin();
      it!=matlist.end(); it++)
    (*it)->toLxm(lxsFile);
  cout << "--> fin d'export des matériaux." << endl;


  cout << "debut de conversion des sources lumineuses" << endl;

  for(list<OBJLight*>::iterator it=srclist.begin();
      it!=srclist.end(); it++){
    (*it)->toLxs(lxsFile, srcVertices);
  }

  cout << "--> fin de conversion des sources lumineuses." << endl;


  cout << "conversion des donnees geometriques en cours ..." << endl;

  for(int i=0; i<gliste.size(); i++){
    cout << "export groupe " << i << "/" << gliste.size() << endl;
    gliste.getGroup(i)->toLxs(lxsFile, pointlist, vecteurlist, texturelist);
    lxsFile << endl;
  }
  cout << "fin de conversion des donnees geometriques" << endl;



  // clore la description des paramètres globaux
  lxsFile << "WorldEnd" << endl;

}


void OBJReader::toJs(ostream& jsFile){

  cout << "sauvegarde en javascript" << endl;
  cout << "conversion des donnees geometriques en cours ..." << endl;

  jsFile << "var sommets = [" << endl;
  for(int i=0; i<pointlist.size(); i++){
    jsFile << "\t" << pointlist[i].x << "," << pointlist[i].y << "," << pointlist[i].z;
    if(i!=pointlist.size()-1) jsFile << ",";
    jsFile << endl;
  }
  jsFile << "              ];" << endl;

  jsFile << endl;

  jsFile << "var couleurs = [" << endl;
  for(int i=0; i<gliste.size(); i++){
    Crgb color = gliste.getGroup(i)->getMaterial().getDiffuseColor();
    int gsize = gliste.getGroup(i)->size();
    jsFile << "\t// groupe " << i << "/" << gliste.size() << endl;
    for(int c=0; c<gsize; c++){
      jsFile << "\t" <<color.r << "," << color.g << "," << color.b;
      if((i==gliste.size()-1)&&(c==gsize-1)) jsFile << endl;
      else jsFile << "," << endl;
    }
  }
  jsFile << "              ];" << endl;

   

  bool last = false;

  jsFile << "var indices = [" << endl;
  for(int i=0; i<gliste.size(); i++){
    if(i==gliste.size()-1) last = true;
    jsFile << "\t// groupe " << i << "/" << gliste.size() << endl;
    gliste.getGroup(i)->toJs(jsFile, pointlist, vecteurlist, texturelist, last);
    //jsFile << "\t// fin groupe " << i <<endl;
  }
  jsFile << "             ];" << endl;
  cout << "fin de conversion des donnees geometriques" << endl;
}


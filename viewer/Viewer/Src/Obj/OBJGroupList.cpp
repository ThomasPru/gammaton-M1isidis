#include "OBJGroupList.hpp"


OBJGroup* OBJGroupList::getGroup(char *name){
  for(unsigned int i=0; i<list.size(); i++)
    if(list[i]->nameIs(name)) return list[i];
  return NULL;
}

OBJGroup* OBJGroupList::getGroup(int i){
  if((i>=0)&&(i<list.size())) return list[i];
  return NULL;
}

void OBJGroupList::addFacet(OBJTriangle *f){
  for(unsigned int i=0; i<list.size(); i++)
    list[i]->addFacet(f);
}

ostream& operator<<(ostream& out, const OBJGroupList& l){
  for(unsigned int i=0; i<l.list.size(); i++)
    out << *(l.list[i]) << endl;
  return out;
}

#ifndef _DEFEAT_ON_DELETE_H_
#define _DEFEAT_ON_DELETE_H_
#include "component.h"

class DefeatOnDelete : public Component
{
public:
	DefeatOnDelete(GameObject* parent);
	~DefeatOnDelete();

	Type getType() { return T_DEFEATONDELETE; }
};

#endif

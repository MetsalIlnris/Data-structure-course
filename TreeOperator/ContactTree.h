#pragma once
#include"RBTree.h"

struct contact 
{
	char* name[10];
	char* city[10];
	char* phoneNumber[16];
	char* homeNumber[16];
	char* workNumber[16];
	char* email[20];
	char* note[40];
	char* time[10];
	char* group[10];

};

class ContactT : public RBTree<contact> 
{
	ContactT();
	~ContactT();
};
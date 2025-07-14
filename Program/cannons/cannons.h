#define CANNON_TYPES_QUANTITY		15

#define CANNON_TYPE_CANNON_LBS3	    0
#define CANNON_TYPE_CANNON_LBS6	    1
#define CANNON_TYPE_CANNON_LBS8		2
#define CANNON_TYPE_CANNON_LBS12    3
#define CANNON_TYPE_CANNON_LBS16    4
#define CANNON_TYPE_CANNON_LBS18	5
#define CANNON_TYPE_CANNON_LBS20    6
#define CANNON_TYPE_CANNON_LBS24    7
#define CANNON_TYPE_CANNON_LBS32    8
#define CANNON_TYPE_CANNON_LBS36	9
#define CANNON_TYPE_CANNON_LBS42    10
#define CANNON_TYPE_CANNON_LBS48    11

#define CANNON_TYPE_CULVERINE_LBS8	12
#define CANNON_TYPE_CULVERINE_LBS18 13
#define CANNON_TYPE_CULVERINE_LBS36 14

#define CANNON_TYPE_NONECANNON		1000

#define CANNON_NAME_CANNON              1
#define CANNON_NAME_CULVERINE           2
#define CANNON_NAME_SPECIAL_CANNON		3


object  Cannon[CANNON_TYPES_QUANTITY];

ref GetCannonByType(int iCannonType) 
{ 
	if (iCannonType == CANNON_TYPE_NONECANNON) return &NullCharacter; // fix для тартант boal
	return &Cannon[iCannonType]; 
}

int GetCannonCaliber(int nCannon)
{
	ref curCannon;
	makeref(curCannon, Cannon[nCannon]);
	
	if (CheckAttribute(curCannon, "RealCaliber"))
	{
		return sti(curCannon.RealCaliber);
	}
	return sti(curCannon.caliber);
}

int GetCannonCaliberNominal(int nCannon)
{
	ref curCannon;
	makeref(curCannon, Cannon[nCannon]);
	
	
	return sti(curCannon.caliber);
}

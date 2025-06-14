#define FELLOWTRAVEL_NO			0
#define FELLOWTRAVEL_CAPTIVE	1
#define FELLOWTRAVEL_PASSENGER	2
#define FELLOWTRAVEL_OFFICER	3
#define FELLOWTRAVEL_COMPANION	4

#define EVENT_CHANGE_OFFICERS	"EvntChangeOfficers"
#define EVENT_CHANGE_COMPANIONS	"EvntChangeCompanions"

#define MAX_ITEM_TAKE	5000

#define MSGICON_ACTIVE_TIME 10
#define MSGICON_LEVELUP	0
#define MSGICON_LOGBOOK	1
#define MSGICON_GETITEM	2

#event_handler("evnt_MsgIconTick","proc_MsgIconTick");

bool GetShipRemovable(ref _refCharacter)
{
	if( CheckAttribute(_refCharacter,"ShipRemovable") && sti(_refCharacter.ShipRemovable) == false ) 
	{
		return false;
	}
	return true;
}

bool GetShipRemovableEx(ref _refCharacter)
{
	if(GetShipRemovable(_refCharacter) == false && _refCharacter.id != pchar.id) 
	{
		return false;
	}
	return true;
}

void SetShipRemovable(ref _refCharacter, bool bRemovable)
{
	if(bRemovable)
	{
		DeleteAttribute(_refCharacter,"ShipRemovable");
	}
	else
	{
		_refCharacter.ShipRemovable = false;
	}
}

//ugeen --> проверка, является ли персонаж глав.героем
bool IsMainCharacter(ref chr)
{
	if(CheckAttribute(chr,"chr_ai.type") && chr.chr_ai.type == LAI_TYPE_PLAYER) return true;
	if(CheckAttribute(chr,"index") && sti(chr.index) == GetMainCharacterIndex()) return true;
	return false;
}
// <-- ugeen

//
bool CharacterIsDead(ref _refCharacter)
{
	return LAi_IsDead(_refCharacter);
}

bool IsCompanion(ref _refCharacter)
{
	int findIdx = sti(_refCharacter.index);
	ref mc = GetMainCharacter();
	for(int i=0; i<COMPANION_MAX; i++)
	{
		if(GetCompanionIndex(mc,i)==findIdx) return true;
	}
	return false;
}

bool IsOfficer(ref _refCharacter)
{
	int findIdx = sti(_refCharacter.index);
	ref mc = GetMainCharacter();
	for(int i=0; i<4; i++)
	{
		if(GetOfficersIndex(mc,i)==findIdx) return true;
	}
	return false;
}

void SetCharacterRemovable(ref _refCharacter, bool removable)
{
	if(removable) DeleteAttribute(_refCharacter,"NonRemovable");
	else _refCharacter.NonRemovable = true;
}

bool GetRemovable(ref _refCharacter)
{
	if( CheckAttribute(_refCharacter,"NonRemovable") ) return !sti(_refCharacter.NonRemovable);
	return true;
}

// Cargo utilites
//------------------------------------------
int GetCargoLoad(ref _refCharacter)
{
	if(!CheckAttribute(_refCharacter,"Ship.Cargo.Load")) return 0;
	int iLoad = sti(_refCharacter.Ship.Cargo.Load);
	return iLoad;
}

int GetCargoLoadEx(ref _refCharacter, int addGoods, int iGoods)
{
	int iGoodsQ = addGoods;
	if(iGoodsQ < 0)
	{
		iGoodsQ = -iGoodsQ;
	}
	iGoodsQ = GetGoodWeightByType(iGoods, iGoodsQ);//addGoods / sti(Goods[iGoods].units);

	int iLoad;
	
	if(addGoods < 0)
	{
		iLoad = GetCargoLoad(_refCharacter) - iGoodsQ;
	}
	else
	{
		iLoad = GetCargoLoad(_refCharacter) + iGoodsQ;
	}

	return iLoad;
}

int RecalculateCargoLoad(ref _refCharacter)
{
	int loadSpace = 0;
	// boal 27/07/06 учёт орудий на борту -->
	if (sti(_refCharacter.Ship.Cannons.Type) != CANNON_TYPE_NONECANNON)
	{
		ref Cannon = GetCannonByType(sti(_refCharacter.Ship.Cannons.Type));
		loadSpace = GetCannonsNum(_refCharacter) * sti(Cannon.Weight);
	}
	// учёт орудий на борту <--
	// ugeen --> учёт веса экипажа (1 тушка члена экипажа весит 1 ц.)
	loadSpace = loadSpace + GetCrewQuantity(_refCharacter);
	// <-- учёт веса экипажа
	for(int i=0; i<GOODS_QUANTITY; i++)
	{
		loadSpace = loadSpace + GetGoodWeightByType(i,GetCargoGoods(_refCharacter,i));
	}
	_refCharacter.Ship.Cargo.Load = loadSpace;
	return loadSpace;
}

///// --> Ugeen 13.11.10 Расчет ценового коэффициента для грузов
//   0  -  товар досталяся на халяву
//   1  -  товар достался честно

float GetCargoCostCoeff(ref _refCharacter, int _goods)
{
	string _goodsName = Goods[_goods].name;
	float CostCoeff = 1.0;	
	if(CheckAttribute(_refCharacter,"Goods." + (_goodsName) + ".costCoeff"))
	{
		CostCoeff = stf(_refCharacter.Goods.(_goodsName).costCoeff);
	}		
	return CostCoeff;
}

float RecalculateSquadronCargoCostCoeff(ref _refCharacter, string _goodsName, int _Qty, float _costCoeff)
{
	int oldQty;
	float oldPriceCoeff = 1.0;
	float newPriceCoeff = 1.0;

	if(CheckAttribute(_refCharacter,"Goods." + (_goodsName) + ".costCoeff"))
	{
		oldPriceCoeff = stf(_refCharacter.Goods.(_goodsName).costCoeff);
	}
	else
	{
		_refCharacter.Goods.(_goodsName).costCoeff = oldPriceCoeff;
	}	
	if(CheckAttribute(pchar,"partition.after." + (_goodsName)))
	{
		oldQty = sti(pchar.partition.after.(_goodsName));
	}
	else oldQty = 0;
		
	if(_Qty > 0)
	{
		newPriceCoeff = (oldQty * oldPriceCoeff + _costCoeff * _Qty)/ (oldQty + _Qty);
	}
	else
	{	
		if(oldQty > 0)	
		{
			newPriceCoeff = oldPriceCoeff;
		}	
		else
		{	
			newPriceCoeff = 1.0;
		}	
	}	
	
	_refCharacter.Goods.(_goodsName).costCoeff = newPriceCoeff;
	
	return newPriceCoeff;
}

int AddCharacterGoodsCostCoeff(ref _refCharacter,int _Goods,int _Quantity, float costCoeff)
{
	int i,cn,freeQuantity;
	string goodsName = Goods[_Goods].name;

	for (i=0; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(_refCharacter,i);
		if (cn!=-1 && GetRemovable(&Characters[cn]))//fix грузим токо своим
		{
			freeQuantity = GetGoodQuantityByWeight( _Goods, GetCargoFreeSpace(&Characters[cn]) );
			if(freeQuantity>=_Quantity)
			{
				RecalculateSquadronCargoCostCoeff(GetMainCharacter(), goodsName, _Quantity, costCoeff);
				Characters[cn].Ship.Cargo.Goods.(goodsName) = sti(Characters[cn].Ship.Cargo.Goods.(goodsName)) + _Quantity;
				RecalculateCargoLoad(&Characters[cn]);
				return true;
			}
			RecalculateSquadronCargoCostCoeff(GetMainCharacter(), goodsName, freeQuantity, costCoeff);
			Characters[cn].Ship.Cargo.Goods.(goodsName) = sti(Characters[cn].Ship.Cargo.Goods.(goodsName)) + freeQuantity;
			_Quantity = _Quantity - freeQuantity;
			RecalculateCargoLoad(&Characters[cn]);
		}
	}
	Trace("Overup cargo space on "+_Quantity + " id = " + _refCharacter.id);
	return false;
}

///// <-- Ugeen 13.11.10 

int RemoveCharacterGoods(ref _refCharacter,int _Goods,int _Quantity)
{
	int i,cn,curQuantity;
	string goodsName = Goods[_Goods].name;

	for(i=0; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(_refCharacter,i);
		if (cn!=-1 && GetRemovable(&Characters[cn]))//fix грузим токо своим
		{
            if (CheckAttribute(&Characters[cn], "Ship.Cargo.Goods."+goodsName)) // boal fix 230804
            {
                curQuantity = sti( Characters[cn].Ship.Cargo.Goods.(goodsName) );
    			if(curQuantity>=_Quantity)
    			{
    				Characters[cn].Ship.Cargo.Goods.(goodsName) = curQuantity - _Quantity;
    				RecalculateCargoLoad(&Characters[cn]);
    				return true;
    			}
    			Characters[cn].Ship.Cargo.Goods.(goodsName) = 0;
    			_Quantity = _Quantity - curQuantity;
    			RecalculateCargoLoad(&Characters[cn]);
			}
			else
			{
                if (MOD_BETTATESTMODE == "On") Log_TestInfo("Проверка (не критично): RemoveCharacterGoods нет груза для characterID = "+ Characters[cn].id);
			}
		}
	}
	Trace("Overup cargo space on "+_Quantity);
	return false;
}

// boal -->
int RemoveCharacterGoodsSelf(ref _refCharacter,int _Goods,int _Quantity)
{
	int    curQuantity;
	string goodsName = Goods[_Goods].name;

	curQuantity = sti( _refCharacter.Ship.Cargo.Goods.(goodsName) );
	if (curQuantity>=_Quantity)
	{
		_refCharacter.Ship.Cargo.Goods.(goodsName) = curQuantity - _Quantity;
		RecalculateCargoLoad(_refCharacter);
		return true;
	}
	_refCharacter.Ship.Cargo.Goods.(goodsName) = 0;
	RecalculateCargoLoad(_refCharacter);
	return false;
}

int GetCargoFreeSpace(ref _refCharacter)
{
	int freeSpace = GetCargoMaxSpace(_refCharacter) - GetCargoLoad(_refCharacter);
	if (freeSpace < 0) freeSpace = 0;  // fix
	return freeSpace;
}

int GetCargoSquadronFreeSpace(ref _refCharacter)
{
	int freeSpace = GetCargoMaxSpace(_refCharacter) - GetCargoLoad(_refCharacter);
	int i, cn;
	ref chref;
	for(i=1; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(_refCharacter,i);
  		if(cn != -1 && GetRemovable(&Characters[cn]))
		{
			chref = GetCharacter(cn);
			freeSpace += GetCargoMaxSpace(chref) - GetCargoLoad(chref);
		}		
	}
	if (freeSpace < 0) freeSpace = 0;  // fix
	return freeSpace;	
}

int GetCargoMaxSpace(ref _refCharacter)
{
	if( !CheckAttribute(_refCharacter,"Ship.Type") ) return 0;
	int _ShipType = sti(_refCharacter.Ship.Type);
	if( _ShipType==SHIP_NOTUSED )
		return 0;
	return sti(RealShips[_ShipType].Capacity);
}

int GetCharacterFreeSpace(ref _refCharacter,int _Goods)
{
	int g = GetGoodQuantityByWeight( _Goods, GetCargoFreeSpace(_refCharacter) );
	if (g < 0) g = 0; // fix
	return g;
}

int GetSquadronFreeSpace(ref _refCharacter,int _Goods)
{
	float weight = stf(Goods[_Goods].weight);
	int unitQ = sti(Goods[_Goods].Units);

	int retVal = unitQ * (GetCargoFreeSpace(_refCharacter)/weight);
	int i,cn;
	ref chref;
	for(i=1; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(_refCharacter,i);
  		if(cn!=-1 && GetRemovable(&Characters[cn]))//fix грузим токо своим
		{
			chref = GetCharacter(cn);
			//if(GetShipRemovableEx(chref))
			//{
				retVal = retVal + unitQ*(GetCargoFreeSpace(chref)/weight);
			//}
		}
	}	
	if (retVal < 0) retVal = 0; // fix
	return retVal;
}

int GetCargoGoods(ref _refCharacter,int _Goods)
{
	string goodsName = Goods[_Goods].name;
	if(!CheckAttribute(_refCharacter,"Ship.Cargo.Goods."+goodsName))
		return 0;
	return sti(_refCharacter.Ship.Cargo.Goods.(goodsName));
}

int GetSquadronGoods(ref _refCharacter,int _Goods)
{
	int i,cn;
	ref chref;
	int retVal = GetCargoGoods(_refCharacter,_Goods);
	for(i=1; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(_refCharacter,i);
		if(cn!=-1 && GetRemovable(&Characters[cn]))//fix грузим токо своим
		{
			chref = GetCharacter(cn);
			if( GetShipRemovableEx(chref) )
			{
				retVal = retVal + GetCargoGoods(chref,_Goods);
			}
		}
	}
	return retVal;
}


void SetCharacterGoods(ref _refCharacter,int _Goods,int _Quantity)
{
	string goodsName = Goods[_Goods].name;
	_refCharacter.Ship.Cargo.Goods.(goodsName) = _Quantity;
	int curLoad = RecalculateCargoLoad(_refCharacter);
	int maxLoad = GetCargoMaxSpace(_refCharacter);
	if(curLoad>maxLoad)
	{
		Trace("ERROR! Cargo space overup (character=" + _refCharacter.index + ",Quantity=" + _Quantity + ")");
	}
}


// доработал метод, теперь возвращает сколько взял
int AddCharacterGoodsSimple(aref aCharacter, int iGood, int iQuantity)
{
	string sGoodName = Goods[iGood].name;
	int    freeQuantity;

	freeQuantity = GetGoodQuantityByWeight(iGood, GetCargoFreeSpace(aCharacter));
	if (freeQuantity < 0) freeQuantity = 0; //fix
	if (freeQuantity > iQuantity)
	{
		freeQuantity = iQuantity;
	}
	aCharacter.Ship.Cargo.Goods.(sGoodName) = sti(aCharacter.Ship.Cargo.Goods.(sGoodName)) + freeQuantity;
	RecalculateCargoLoad(aCharacter);
	return freeQuantity;
}
// boal <--

int AddCharacterGoods(ref _refCharacter,int _Goods,int _Quantity)
{
	int i,cn,freeQuantity;
	string goodsName = Goods[_Goods].name;

	for (i=0; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(_refCharacter,i);
		if (cn!=-1 && GetRemovable(&Characters[cn]))//fix грузим токо своим
		{
			freeQuantity = GetGoodQuantityByWeight( _Goods, GetCargoFreeSpace(&Characters[cn]) );
			if(freeQuantity>=_Quantity)
			{
				Characters[cn].Ship.Cargo.Goods.(goodsName) = sti(Characters[cn].Ship.Cargo.Goods.(goodsName)) + _Quantity;
				RecalculateCargoLoad(&Characters[cn]);
				return true;
			}
			Characters[cn].Ship.Cargo.Goods.(goodsName) = sti(Characters[cn].Ship.Cargo.Goods.(goodsName)) + freeQuantity;
			_Quantity = _Quantity - freeQuantity;
			RecalculateCargoLoad(&Characters[cn]);
		}
	}
	Trace("Overup cargo space on "+_Quantity + " id = " + _refCharacter.id);
	return false;
}

// Cannons utilite
int GetCaracterShipCannonsType(ref _refCharacter)
{
	if(!CheckAttribute(_refCharacter,"Ship.Cannons.Type")) return CANNON_TYPE_NONECANNON;
	return sti(_refCharacter.Ship.Cannons.Type);
}

int GetCannonQuantity(ref refCharacter)
{
	int nShipType = GetCharacterShipType(refCharacter);
	if(nShipType==SHIP_NOTUSED) return 0;
	ref refBaseShip = GetRealShip(nShipType);
	
	int canQ = GetBortCannonsQtyMax(refCharacter, "cannonf") + 
	           GetBortCannonsQtyMax(refCharacter, "cannonb") + 
			   GetBortCannonsQtyMax(refCharacter, "cannonl") + 
			   GetBortCannonsQtyMax(refCharacter, "cannonr");
	return canQ;
}

int GetIntactCannonQuantity(ref refCharacter)
{
	int nShipType = GetCharacterShipType(refCharacter);
	if(nShipType==SHIP_NOTUSED) return 0;
	ref refBaseShip = GetRealShip(nShipType);
		
	int canQ = GetBortIntactCannonsNum(refCharacter, "cannonf", sti(refBaseShip.fcannon)) + 
	           GetBortIntactCannonsNum(refCharacter, "cannonb", sti(refBaseShip.bcannon)) + 
			   GetBortIntactCannonsNum(refCharacter, "cannonl", sti(refBaseShip.lcannon)) + 
			   GetBortIntactCannonsNum(refCharacter, "cannonr", sti(refBaseShip.rcannon));
	return canQ;
}

int GetMaximumCaliber(ref refCharacter)
{
	int nShipType = GetCharacterShipType(refCharacter);
	if(nShipType==SHIP_NOTUSED) return 0;
	ref rShip = GetRealShip(nShipType);
	return sti(rShip.MaxCaliber);
}

// Ship utilite
int GetCharacterShipType(ref _refCharacter)
{
	if(CheckAttribute(_refCharacter,"Ship.Type"))
	{
		int iShipType = sti(_refCharacter.Ship.Type);
		if(iShipType != SHIP_NOTUSED)
		{
            return iShipType;
		}
	}
	return SHIP_NOTUSED;
}
int GetCharacterShipHP(ref _refCharacter)
{
	int nShipType = GetCharacterShipType(_refCharacter);
	if(nShipType==SHIP_NOTUSED) return 0;
	return sti(RealShips[nShipType].HP);
}

int GetCharacterShipMaxHP(ref _refCharacter)
{
    int nShipType = GetCharacterShipType(_refCharacter);
    if(nShipType==SHIP_NOTUSED) return 0;
    int iBaseType = sti(RealShips[sti(_refCharacter.Ship.Type)].BaseType);
    ref refShip;
	makeref(refShip,ShipsTypes[iBaseType]);
    return sti(refShip.HP);
}

int GetCharacterShipBaseHP(ref _refCharacter)
{
	int nShipType = GetCharacterShipType(_refCharacter);
	if(nShipType==SHIP_NOTUSED) return 0;
	return sti(RealShips[nShipType].BaseHP);
}
int GetCurrentShipHP(ref _refCharacter)
{
	if( CheckAttribute(_refCharacter,"ship.hp") ) return sti(_refCharacter.ship.hp);
	return 0;
}
float GetCharacterShipSP(ref _refCharacter)
{
	int nShipType = GetCharacterShipType(_refCharacter);
	if(nShipType==SHIP_NOTUSED) return 0.0;
	return stf(RealShips[nShipType].SP);
}

string GetShipTypeName(ref _refCharacter)
{
	int nShipType = GetCharacterShipType(_refCharacter);
	if(nShipType==SHIP_NOTUSED) 
	{
		return SHIP_NOTUSED_TYPE_NAME;
	}

	return ShipsTypes[sti(RealShips[nShipType].basetype)].name;
}
int GetCharacterShipClass(ref _refCharacter)
{
	int nShipType = GetCharacterShipType(_refCharacter);
	if( nShipType==SHIP_NOTUSED ) return 7; // -1 неправильно, иначе сравнение врет, нет кораля - это лодка
	return sti(RealShips[nShipType].Class);
}
bool IsUniversalShipType(ref _refCharacter)
{
	int nShipType = GetCharacterShipType(_refCharacter);
	if( nShipType==SHIP_NOTUSED ) return false;
	return RealShips[nShipType].Spec == SHIP_SPEC_UNIVERSAL;
}
bool IsMerchantShipType(ref _refCharacter)
{
	int nShipType = GetCharacterShipType(_refCharacter);
	if( nShipType==SHIP_NOTUSED ) return false;
	return RealShips[nShipType].Spec == SHIP_SPEC_MERCHANT;
}
bool IsRaiderShipType(ref _refCharacter)
{
	int nShipType = GetCharacterShipType(_refCharacter);
	if( nShipType==SHIP_NOTUSED ) return false;
	return RealShips[nShipType].Spec == SHIP_SPEC_RAIDER;
}
bool IsWarShipType(ref _refCharacter)
{
	int nShipType = GetCharacterShipType(_refCharacter);
	if( nShipType==SHIP_NOTUSED ) return false;
	return RealShips[nShipType].Spec == SHIP_SPEC_WAR;
}
int GetMaxCrewQuantity(ref _refCharacter)
{
	if(!CheckAttribute(_refCharacter,"Ship.Type")) return 0;
	int shipType = sti(_refCharacter.Ship.Type);
	if(shipType<0) return 0;
    if(shipType>=REAL_SHIPS_QUANTITY) return 0;
	return sti(RealShips[shipType].MaxCrew);
}
//boal optimal crew
int GetOptCrewQuantity(ref _refCharacter)
{
	if(!CheckAttribute(_refCharacter,"Ship.Type")) return 0;
	int shipType = sti(_refCharacter.Ship.Type);
	if(shipType<0) return 0;
	if(shipType>=REAL_SHIPS_QUANTITY) return 0;
	return sti(RealShips[shipType].OptCrew);
}

int GetMinCrewQuantity(ref _refCharacter)
{
	if(!CheckAttribute(_refCharacter,"Ship.Type")) return 0;
	int shipType = sti(_refCharacter.Ship.Type);
	if(shipType<0) return 0;
	if(shipType>=REAL_SHIPS_QUANTITY) return 0;
	return sti(RealShips[shipType].MinCrew);
}
int GetFreeCrewQuantity(ref _refCharacter)
{
	return (GetMaxCrewQuantity(_refCharacter)-GetCrewQuantity(_refCharacter));
}
int GetFreePartyCrewQuantity(ref _refCharacter)
{
	int cn;
	int sumCrew = 0;
	for(int i=0; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(_refCharacter,i);
		if(cn!=-1)
		{
			sumCrew = sumCrew + GetFreeCrewQuantity(GetCharacter(cn));
		}
	}
	return sumCrew;
}
int GetCrewQuantity(ref _refCharacter)
{
	if(!CheckAttribute(_refCharacter,"Ship.Crew.Quantity")) return 0;
	if (sti(_refCharacter.Ship.Crew.Quantity) < 0) _refCharacter.Ship.Crew.Quantity = 0; // boal FIX 21.04.05
	
	return sti(_refCharacter.Ship.Crew.Quantity);
}
int SetCrewQuantity(ref _refCharacter,int num)
{
	int maxCrew = GetMaxCrewQuantity(_refCharacter);
	if(num>maxCrew)
	{
		Trace("Error!!! Overup maximum crew quantity (character=" + _refCharacter.index + ")");
		_refCharacter.Ship.Crew.Quantity = maxCrew;
		return false;
	}
	if (num < 0) num = 0; // boal fix
	_refCharacter.Ship.Crew.Quantity = num;
	return true;
}

// --> Eddy, пусть будет пока, а то неудобно в тестах.
void SetCrewQuantityFull(ref _refCharacter)
{
	SetCrewQuantity(_refCharacter, GetMaxCrewQuantity(_refCharacter)); // переделал в мах перегруз 01/08/06 boal
}
// <-- Eddy

// boal
int SetCrewQuantityOverMax(ref _refCharacter, int num)
{
    if (num < 0) num = 0; // boal fix
    _refCharacter.Ship.Crew.Quantity = num;
	return true;
}
int AddCharacterCrew(ref _refCharacter,int num)
{
	return SetCrewQuantity(_refCharacter,GetCrewQuantity(_refCharacter)+num);
}
int RemoveCharacterCrew(ref _refCharacter,int num)
{
	int curCrew = GetCrewQuantity(_refCharacter);
	if(curCrew<num)
	{
		//Trace("Error!!! Remove overup crew (character=" + _refCharacter.index + ")");
		SetCrewQuantity(_refCharacter,0);
		return false;
	}
	SetCrewQuantityOverMax(_refCharacter,curCrew-num);//fix
	return true;
}
// Repair section
float GetSailPercent(ref _refCharacter)
{
	if( !CheckAttribute(_refCharacter,"Ship.SP") ) return 100.0;
	float fSP = GetCharacterShipSP(_refCharacter);
	if(fSP<=0.0) return 100.0;
	float fpsp = 100.0*stf(_refCharacter.Ship.SP)/fSP;
	return fpsp;
}
float GetHullPercent(ref _refCharacter)
{
	if(!CheckAttribute(_refCharacter,"Ship.HP")) return 100.0;
	int iHP = GetCharacterShipHP(_refCharacter);
	if(iHP<=0) return 100.0;
	float fphp = 100.0*stf(_refCharacter.Ship.HP)/iHP;
	return fphp;
}

float GetHullPercentWithModifier(ref _refCharacter, int iModifier)
{
	if(!CheckAttribute(_refCharacter,"Ship.HP")) return 100.0;
	int iHP = GetCharacterShipHP(_refCharacter);
	if(iHP<=0) return 100.0;
	float fphp = 100.0*(stf(_refCharacter.Ship.HP) + iModifier)/iHP;
	return fphp;
}

float GetSailRPD(ref _refCharacter) // процент ремонта парусов в день
{
	float repairSkill = GetSummonSkillFromNameToOld(_refCharacter, SKILL_REPAIR);
	
	if(CheckOfficersPerk(_refCharacter, "SelfRepair")) repairSkill = repairSkill * 1.25;
	else
	{
		if (CheckOfficersPerk(_refCharacter, "Builder")) repairSkill = repairSkill * 1.00;
		else
		{
			// belamour legendary edition: CheckOfficersPerk не работает со способностями, которые имеют КД
			if(GetOfficersPerkUsing(_refCharacter, "LightRepair")) repairSkill = repairSkill * 0.75;
			else
			{
				if(CheckOfficersPerk(_refCharacter, "Carpenter")) repairSkill = repairSkill * 0.50;
				else 
				{
					if(IsCharacterEquippedArtefact(_refCharacter, "obereg_2")) repairSkill = repairSkill * 0.10;
					else repairSkill = 0.0;
				}
			}
		}
	}
	
    // belamour правка артефактов согласно описанию -->
	if(IsCharacterEquippedArtefact(_refCharacter, "talisman7")) repairSkill = repairSkill * 2.0; // вдвое увеличивает 
    if(IsCharacterEquippedArtefact(_refCharacter, "indian_5")) repairSkill = repairSkill * 0.9;  // тсантса
    if(IsCharacterEquippedArtefact(_refCharacter, "indian_6")) repairSkill = repairSkill * 0.9;  // Коралловая голова
    //<-- belamour

	float damagePercent = 100.0 - GetSailPercent(_refCharacter);
	if (damagePercent == 0.0) return 0.0;

	float ret = repairSkill*15.0 / damagePercent;
	if (ret > damagePercent) ret = damagePercent;
	return ret;  //boal
}
float GetHullRPD(ref _refCharacter) // процент ремонта корпуса в день
{
	float repairSkill = GetSummonSkillFromNameToOld(_refCharacter, SKILL_REPAIR);
	
	if(CheckOfficersPerk(_refCharacter, "SelfRepair")) repairSkill = repairSkill * 1.25;
	else
	{
		if (CheckOfficersPerk(_refCharacter, "Builder")) repairSkill = repairSkill * 1.00;
		else
		{
			// belamour legendary edition: CheckOfficersPerk не работает со способностями, которые имеют КД
			if(GetOfficersPerkUsing(_refCharacter, "LightRepair")) repairSkill = repairSkill * 0.75;
			else
			{
				if(CheckOfficersPerk(_refCharacter, "Carpenter")) repairSkill = repairSkill * 0.50;
				else 
				{
					if(IsCharacterEquippedArtefact(_refCharacter, "obereg_1")) repairSkill = repairSkill * 0.10;
					else repairSkill = 0.0;
				}					
			}
		}
	}
	
    // belamour правка артефактов согласно описанию -->
	if(IsCharacterEquippedArtefact(_refCharacter, "talisman7")) repairSkill = repairSkill * 2.0; // вдвое увеличивает
    if(IsCharacterEquippedArtefact(_refCharacter, "indian_5")) repairSkill = repairSkill * 0.9;  // Тсантса
    if(IsCharacterEquippedArtefact(_refCharacter, "indian_6")) repairSkill = repairSkill * 0.9;  // Коралловая голова
    //<-- belamour

	float damagePercent = 100.0 - GetHullPercent(_refCharacter);
	if(damagePercent == 0.0) return 0.0;

	float ret = repairSkill*15.0 / damagePercent;
	if (ret > damagePercent) ret = damagePercent;
	return ret;  //boal
}
float GetSailSPP(ref _refCharacter) // количество парусины на один процент починки
{
	float ret = 8-GetCharacterShipClass(_refCharacter);
	
	if (CheckOfficersPerk(_refCharacter, "Builder"))
	{
		ret = ret * 0.75; // потребность ниже
	}
	// belamour legendary edition сокращаем количество парусины для ремонта 
	ret = ret * isEquippedArtefactUse(_refCharacter, "obereg_2", 1.0, 0.85) * isEquippedArtefactUse(_refCharacter, "talisman7", 1.0, 0.7);
	ret = ret * (1.0-stf(GetSummonSkillFromNameToOld(_refCharacter, SKILL_REPAIR)/40.0)); // 100 починки экономит 25% ресурсов
	
	return ret;
}
float GetHullPPP(ref _refCharacter) // количество досок на один процент починки
{
	float ret = 8-GetCharacterShipClass(_refCharacter);
	
	float HPpercent = GetCharacterShipHP(_refCharacter) / 700.0;
	
	if (HPpercent > ret) ret = HPpercent;
	
	if (CheckOfficersPerk(_refCharacter, "Builder"))
	{
		ret = ret * 0.75; // потребность ниже
	}
	// belamour legendary edition сокращаем количество досок для ремонта 
	ret = ret * isEquippedArtefactUse(_refCharacter, "obereg_1", 1.0, 0.85) * isEquippedArtefactUse(_refCharacter, "talisman7", 1.0, 0.7);
	ret = ret * (1.0-stf(GetSummonSkillFromNameToOld(_refCharacter, SKILL_REPAIR)/40.0)); // 100 починки экономит 25% ресурсов
	
	return ret;
}
// расчёт починки корпуса
float GetHullRepairDay(ref _refCharacter, bool _qty) // процент ремонта корпуса в день с материалом
{
    float repPercent = 0.0;
    float matQ, tmpf;
    
    matQ = 0;	
	if (GetHullPercent(_refCharacter) < 100.0 )
	{
		repPercent = GetHullRPD(_refCharacter);
		matQ = repPercent*GetHullPPP(_refCharacter);
		tmpf = GetRepairGoods(true,_refCharacter);
		if (tmpf >= 0)
		{
			if (tmpf < matQ)
			{
                matQ = tmpf;
				repPercent = tmpf/GetHullPPP(_refCharacter);
			}
        }
	}
	if (_qty)
	{
	    return matQ;
	}
	return repPercent;
}

float GetSailRepairDay(ref _refCharacter, bool _qty)			// расчёт починки парусов
{
    float repPercent = 0.0;
    float matQ, tmpf;
    
    matQ = 0;
	if (GetSailPercent(_refCharacter) < GetAllSailsDamagePercent(_refCharacter) )
	{
		repPercent = GetSailRPD(_refCharacter);
		matQ = repPercent*GetSailSPP(_refCharacter);
		tmpf = GetRepairGoods(false,_refCharacter);
		if (tmpf >= 0)
		{
			if (tmpf < matQ)
			{
                matQ = tmpf;
				repPercent = tmpf/GetSailSPP(_refCharacter);  
			}
        }
	}
	if (_qty)
	{
	    return matQ;
	}
	return repPercent;
}

bool CheckSelfRepairConditions()
{
	ref chr;

	if (!CheckAttribute(pchar, "ship.type")) return false;    
	int iShip = sti(pchar.ship.type);
	if (iShip == SHIP_NOTUSED) return false;
	
	if(CheckAttribute(pchar, "GenQuest.CannotWait")) return false;
		
	for (int i = 0; i < GetCompanionQuantity(PChar); i++)
	{
		chr = GetCharacter(GetCompanionIndex(PChar, i));		
		if (GetHullPercent(chr) < 100 
		 || GetSailPercent(chr) < 100 
		 || GetShipFallMastsQuantity(chr) > 0) return true;
	}
	return false;				
}


// Fellowtravels utilites
// работа с пассажирами
int GetPassengersQuantity(ref _refCharacter)
{
	if(!CheckAttribute(_refCharacter,"Fellows.Passengers.Quantity")) return 0;
	return sti(_refCharacter.Fellows.Passengers.Quantity);
}

// пассажиры без пленных и квестовых boal
int GetOfficerPassengerQuantity(ref _refCharacter)
{
	int psgQuant = GetPassengersQuantity(_refCharacter);
	int curIdx=0;
	ref curChar;
	int cn;
	int how = 0;
	bool ok;
	
	for (int i=0; i<psgQuant; i++)
	{
		cn = GetPassenger(_refCharacter,i);
		if(cn==-1) break;

		curChar = GetCharacter(cn);
		ok = CheckAttribute(curChar, "prisoned") && curChar.prisoned == true;
		if (!ok && GetRemovable(curChar))
		{
   			how++;
		}
	}

	return how;
}

int GetNotCaptivePassengersQuantity(ref _refCharacter)
{
	int result, idx;
	result = 0;
	idx = 0;
	if(!CheckAttribute(_refCharacter,"Fellows.Passengers.Quantity")) return 0;
	for (int i=0; i <sti(_refCharacter.Fellows.Passengers.Quantity); i++)
	{
		if(sti(characters[idx].prisoned) != 1)
		{
			result = result+1;
		}
	}
	return result;
}

int GetFreePassengersQuantity(ref _refCharacter)
{
	int result, idx;
	result = 0;
	idx = 0;
	if(!CheckAttribute(_refCharacter,"Fellows.Passengers.Quantity")) return 0;
	for (int i=0; i <sti(_refCharacter.Fellows.Passengers.Quantity); i++)
	{
		idx = GetPassenger( _refCharacter,i);
		if(!CheckAttribute(&characters[idx], "isbusy"))
		{
			result = result+1;
		}
	}
	return result;
}


int GetNotQuestPassengersQuantity(ref _refCharacter)
{
	int result, idx;
	bool bOk;
	
	result = 0;
	idx = 0;
	if(!CheckAttribute(_refCharacter,"Fellows.Passengers.Quantity")) return 0;
	for (int i=0; i <sti(_refCharacter.Fellows.Passengers.Quantity); i++)
	{
		idx = GetPassenger( _refCharacter,i);
		
		bOk =  CheckAttribute(&characters[idx], "prisoned") && sti(characters[idx].prisoned) == true;
		if (!bOk && !CheckAttribute(&characters[idx], "isquest"))
		{
			result = result+1;
		}
	}
	return result;
}

int GetNotQuestFreePassengersQuantity(ref _refCharacter)
{
	int result, idx;
	result = 0;
	idx = 0;
	bool ok;
	if(!CheckAttribute(_refCharacter,"Fellows.Passengers.Quantity")) return 0;
	for (int i=0; i <sti(_refCharacter.Fellows.Passengers.Quantity); i++)
	{
		idx = GetPassenger( _refCharacter,i);
		if (idx >0)
		{
			ok = !CheckAttribute(&characters[idx], "prisoned") || sti(characters[idx].prisoned) != true;
			if (ok && !CheckAttribute(&characters[idx], "isquest") && !CheckAttribute(&characters[idx], "isbusy"))   //to_do  isquest?
			{
				result = result+1;
			}
		}
	}
	return result;
}

int GetPassenger(ref _refCharacter,int idx)
{
	if(idx<0) return -1;
	if(idx>=GetPassengersQuantity(_refCharacter)) return -1;

	string PsgAttrName = "id"+(idx+1);
	if(!CheckAttribute(_refCharacter,"Fellows.Passengers."+PsgAttrName)) return -1;
	return sti(_refCharacter.Fellows.Passengers.(PsgAttrName));
}

int GetPassengerEx(ref _refCharacter,int idx)
{
	if(idx < 0) 
	{
		return -1;
	}
	if(idx > GetPassengersQuantity(_refCharacter)) 
	{
		return -1;
	}
	if(idx == 0)
	{
		return nMainCharacterIndex;
	}
	string PsgAttrName = "id" + (idx);
	if(!CheckAttribute(_refCharacter,"Fellows.Passengers."+PsgAttrName)) 
	{
		return -1;
	}
	return sti(_refCharacter.Fellows.Passengers.(PsgAttrName));
}

int GetPassengerNumber(ref _refCharacter,int findCharacterIdx)
{
	int psgQuant = GetPassengersQuantity(_refCharacter);
	int cn;
	ref cr;
	for(int i=0; i<psgQuant; i++)
	{
		cn = GetPassenger(_refCharacter,i);
		if(cn==-1) break;
		cr = GetCharacter(cn);
		if(findCharacterIdx==sti(cr.index)) return i;
	}
	return -1;
}
int GetNotCaptivePassenger(ref _refCharacter,int idx)
{
	if(idx<0) return -1;
	int psgQuant = GetPassengersQuantity(_refCharacter);

	int curIdx=0;
	ref curChar;
	int cn;
	for(int i=0;i<psgQuant;i++)
	{
		cn = GetPassenger(_refCharacter,i);
		if(cn==-1) break;

		curChar = GetCharacter(cn);
		if(CheckAttribute(curChar,"prisoned"))
		{
			if(sti(curChar.prisoned)==true) continue;
		}
		if(curIdx==idx)	return sti(curChar.index);
		curIdx++;
	}
	return -1;
}

int GetFreePassenger(ref _refCharacter,int idx)
{
	if(idx<0) return -1;
	int psgQuant = GetPassengersQuantity(_refCharacter);

	int curIdx=0;
	ref curChar;
	int cn;
	for(int i=0;i<psgQuant;i++)
	{
		cn = GetPassenger(_refCharacter,i);
		if(cn==-1) break;

		curChar = GetCharacter(cn);
		if(CheckAttribute(curChar,"isbusy"))
		{
			continue;
		}
		if(curIdx==idx)	return sti(curChar.index);
		curIdx++;
	}
	return -1;
}

int GetNotQuestPassenger(ref _refCharacter,int idx)
{
	if(idx<0) return -1;
	int psgQuant = GetPassengersQuantity(_refCharacter);

	int curIdx=0;
	ref curChar;
	int cn;
	for(int i=0;i<psgQuant;i++)
	{
		cn = GetPassenger(_refCharacter,i);
		if(cn==-1) break;

		curChar = GetCharacter(cn);
		if(CheckAttribute(curChar,"isquest") || CheckAttribute(curChar,"isbusy"))
		{
			continue;
		}
		if(curIdx==idx)	return sti(curChar.index);
		curIdx++;
	}
	return -1;
}

int ChangePassenger(ref _refCharacter,int idx, int psngIdx)
{
	int retVal = GetPassenger(_refCharacter,idx);
	if(idx>=0)
	{
		string PsgAttrName = "id"+(idx+1);
		_refCharacter.Fellows.Passengers.(PsgAttrName) = psngIdx;
	}
	return retVal;
}
int AddPassenger(ref _refCharacter,ref _refPassenger, int prisonFlag)
{
	ref characterRef;
	int PsgQuantity = GetPassengersQuantity(_refCharacter);
	
	if(PsgQuantity<PASSENGERS_MAX)
	{
		aref tmpRef; makearef(tmpRef,_refCharacter.Fellows.Passengers);
		string PsgAttrName;
		for(int i=0;i<PsgQuantity;i++)
		{
			PsgAttrName = "id"+(i+1);	    
			characterRef = GetCharacter(sti(tmpRef.(PsgAttrName)));					
			if(tmpRef.(PsgAttrName) == _refPassenger.index && sti(characterRef.id) == 0) return PsgQuantity;
		}
		PsgQuantity++;
		tmpRef.Quantity = PsgQuantity;
		PsgAttrName = "id"+PsgQuantity;
		tmpRef.(PsgAttrName) = _refPassenger.index;
		if(prisonFlag == true) _refPassenger.prisoned = true;
	}
	else	trace("Overup maximum passengers quantity");
	return PsgQuantity;
}
int RemovePassenger(ref _refCharacter,ref _refPassenger)
{
 	if (sti(_refCharacter.index) == GetMainCharacterIndex())
	{
		CheckForReleaseOfficer(sti(_refPassenger.index));  // boal super fix
	}
	else
	{
	    RemoveOfficersIndex(_refCharacter,sti(_refPassenger.index));
	}
	int PsgQuantity = GetPassengersQuantity(_refCharacter);
	int psgNum = GetPassengerNumber(_refCharacter,sti(_refPassenger.index));
	if(psgNum==-1) return PsgQuantity;

	aref tmpRef;
	makearef(tmpRef,_refCharacter.Fellows.Passengers);
	string inPsgAttrName,outPsgAttrName;
	for(int i=(psgNum+1); i<PsgQuantity; i++)
	{
		inPsgAttrName = "id"+i;
		outPsgAttrName = "id"+(i+1);
		tmpRef.(inPsgAttrName) = tmpRef.(outPsgAttrName);
	}

	outPsgAttrName = "id"+PsgQuantity;
	DeleteAttribute(tmpRef,outPsgAttrName);
	PsgQuantity--;
	tmpRef.Quantity = PsgQuantity;
	return PsgQuantity;
}

int FindFellowtravellers(ref _refCharacter,ref _refFindCharacter)
{
	int i;
	string stmp;
	aref atmp;
	aref curref;

	if(sti(_refFindCharacter.index)==-1) return FELLOWTRAVEL_NO;
	if(CheckAttribute(_refFindCharacter,"prisoned"))
	{
		if(sti(_refFindCharacter.prisoned)==true) return FELLOWTRAVEL_CAPTIVE;
	}
	for(i=1;i<4;i++)
	{
		if( sti(_refFindCharacter.index) == GetOfficersIndex(_refCharacter,i) )	return FELLOWTRAVEL_OFFICER;
	}
	for(i=0;i<GetPassengersQuantity(_refCharacter);i++)
	{
		if(sti(_refFindCharacter.index)==GetPassenger(_refCharacter,i))	return FELLOWTRAVEL_PASSENGER;
	}
	for(i=1;i<COMPANION_MAX;i++)
	{
		if( GetCompanionIndex(_refCharacter,i)==sti(_refFindCharacter.index) )	
		{
			return FELLOWTRAVEL_COMPANION;
		}
	}
	return FELLOWTRAVEL_NO;
}

// ==> eddy
bool CheckPassengerInCharacter(ref _refBaseChar, string _seekId)
{
	int psgQuant = GetPassengersQuantity(_refBaseChar);
    if(psgQuant<0) return false;
	int cn;
	for(int i=0;i<psgQuant;i++)
	{
		cn = GetPassenger(_refBaseChar,i);
		if(cn==-1) continue;
		if (characters[cn].id == _seekId) return true;
	}
	return false;
}

// работа с компаньонами
int SetCompanionIndex(ref _refCharacter,int _CompanionNum, int _CompanionIdx)
{
  if(_CompanionNum == -1)
	{
		for(int i = 1; i < COMPANION_MAX; i++)	
		{
			if (GetCompanionIndex(_refCharacter, i) == -1)
			{
				_CompanionNum = i;
				break;
			}
		}
	}
	if(_CompanionNum < 1) return _CompanionIdx;
	if(_CompanionNum > COMPANION_MAX - 1) return _CompanionIdx;

	if(_CompanionIdx!=-1)
	{
		for(i=0;i<COMPANION_MAX;i++)
		{
			if(GetCompanionIndex(_refCharacter,i)==_CompanionIdx) return -1;
		}
	}

	string compName = "id"+_CompanionNum;
	int retVal = GetCompanionIndex(_refCharacter,_CompanionNum);
	_refCharacter.Fellows.Companions.(compName) = _CompanionIdx;

	if( _CompanionIdx>=0 && CheckAttribute(&Characters[_CompanionIdx],"nation") ) {
		Characters[_CompanionIdx].prev_nation = Characters[_CompanionIdx].nation;
		Characters[_CompanionIdx].nation = _refCharacter.nation;
		Characters[_CompanionIdx].location = "none";//fix
	}
	if( retVal>=0 && CheckAttribute(&Characters[retVal],"prev_nation") ) {
		Characters[retVal].nation = Characters[retVal].prev_nation;
		Characters[retVal].location = "none"; //fix
	}

	Event(EVENT_CHANGE_COMPANIONS,"");
	return _CompanionIdx;
}
int RemoveCharacterCompanion(ref _refCharacter, ref refCompanion)
{
	string compName;
	int i;

	aref refComps;
	makearef(refComps,_refCharacter.Fellows.Companions);
	for(i=1; i<COMPANION_MAX; i++)  // был баг к3
	{
		compName = "id"+i;
		if(CheckAttribute(refComps,compName) && refComps.(compName)==refCompanion.index)
		{
			refComps.(compName) = -1;
			refCompanion.location = "none";
			refCompanion.location.group = _refCharacter.location.group;
			refCompanion.location.locator = _refCharacter.location.locator;
			Event(EVENT_CHANGE_COMPANIONS,"");

			return i;
		}
	}
	return -1;
}
int GetCompanionIndex(ref _refCharacter, int _CompanionNum)
{
	if(_CompanionNum < 0) 
	{
		return -1;
	}
	if(_CompanionNum > (COMPANION_MAX - 1)) 
	{
		return -1;
	}
	if(_CompanionNum==0) 
	{
		if (!CheckAttribute(_refCharacter,"index"))
		{
			return -1;
		}
		return sti(_refCharacter.index);
	}

	string compName = "id"+_CompanionNum;
	if(!CheckAttribute(_refCharacter, "Fellows.Companions."+compName)) 
	{
		return -1;
	}
	if(sti(_refCharacter.Fellows.Companions.(compName)) < 1)
	{
		return -1;
	}
	if(sti(characters[sti(_refCharacter.Fellows.Companions.(compName))].ship.type) != SHIP_NOTUSED)
	{
		return sti(_refCharacter.Fellows.Companions.(compName));
	}
	return -1;
}
int GetCompanionNumber(ref _refCharacter,int _CompanionIdx)
{
	for(int i=0; i<COMPANION_MAX; i++)
	{
		if( GetCompanionIndex(_refCharacter,i) == _CompanionIdx ) return i;
	}
	return -1;
}
int GetCompanionQuantity(ref _refCharacter)
{
	int qn = 0;
	for(int i=0; i<COMPANION_MAX; i++)
	{
		if( GetCompanionIndex(_refCharacter,i)>=0 ) qn++;
	}
	return qn;
}

int GetRemovableCompanionsNumber(ref _refCharacter)
{
	int qn = 0;
	int cn = 1;
	for(int i=0; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(_refCharacter,i);
		if(cn > 0 && GetShipRemovable(&characters[cn]) == true)
		{
			qn++;
		}
	}
	return qn;
}

// ==> eddy
bool CheckCompanionInCharacter(ref _refBaseChar, string _seekId)
{
	int cn;
	for(int i=0;i<COMPANION_MAX;i++)
	{
		cn = GetCompanionIndex(_refBaseChar,i);
		if(cn==-1) continue;
		if (characters[cn].id == _seekId) return true;
	}
	return false;
}

// работа с офицерами
int GetOfficersQuantity(ref _refCharacter)
{
	int idx=0;
	for(int i=1; i<4; i++)
	{
		if( GetOfficersIndex(_refCharacter,i)!=-1 ) idx++;
	}
	return idx;
}
int GetOfficersIndex(ref _refCharacter,int _OfficerNum)
{
	if(_OfficerNum<0) return -1;
	if(_OfficerNum>3) return -1;
	if(_OfficerNum==0)
    {
        if(!CheckAttribute(_refCharacter,"index")) return -1; // boal fix
        return MakeInt(_refCharacter.index);
    }

	string compName = "id"+_OfficerNum;
	if(!CheckAttribute(_refCharacter,"Fellows.Passengers.Officers."+compName)) return -1;
	if(sti(_refCharacter.Fellows.Passengers.Officers.(compName)) < 1)
	{
		return - 1;
	}
	return sti(_refCharacter.Fellows.Passengers.Officers.(compName));
}

int SetOfficersIndex(ref _refCharacter,int _OfficerNum, int _OfficerIdx)
{
	int i;
    if(_OfficerNum == -1)
	{
		for(i=1; i<4; i++)	
		{
			if(GetOfficersIndex(_refCharacter, i) == -1)
			{
				_OfficerNum = i;
				break;
			}
		}
        // fix
        if (_OfficerNum == -1)
        {
            _OfficerNum = 3; // нет места?? да пофиг
        }
	}
	if(_OfficerNum<1) return _OfficerIdx;
	if(_OfficerNum>3) return _OfficerIdx;

	if(_OfficerIdx!=-1)
	{
		for(i=1;i<4;i++)
		{
			if(GetOfficersIndex(_refCharacter,i)==_OfficerIdx) return -1;
		}
		AddPassenger(_refCharacter,GetCharacter(_OfficerIdx),false);
	}

	string compName = "id"+_OfficerNum;
	int retVal = GetOfficersIndex(_refCharacter,_OfficerNum);
	_refCharacter.Fellows.Passengers.Officers.(compName) = _OfficerIdx;
	if(_OfficerIdx>=0)
	{
		LAi_SetOfficerType(GetCharacter(_OfficerIdx));
		Characters[_OfficerIdx].location = _refCharacter.location;
	}
	if(retVal>=0)
	{
		LAi_SetCitizenTypeNoGroup(GetCharacter(retVal));
		Characters[retVal].location = "none";
	}
	Event(EVENT_CHANGE_OFFICERS,"");

	return retVal;
}
bool RemoveOfficersIndex(ref _refCharacter, int _OfficerIdx)
{
	if(_OfficerIdx==-1) return false;
	for(int i=1; i<4; i++)
	{
		if(GetOfficersIndex(_refCharacter,i) == _OfficerIdx)
		{
			SetOfficersIndex(_refCharacter,i,-1);
			return true;
		}
	}
	return false;
}

int AddMoneyToCharacter(ref _refCharacter,int _Money)
{
	// boal -->
	if (_Money < 0 && sti(_refCharacter.Money) < abs(_Money))
	{
	    _Money = -sti(_refCharacter.Money);
	}
	// boal <--
	int newMoney = sti(_refCharacter.Money) + _Money;
	if(newMoney<0) newMoney=0;
	_refCharacter.Money = newMoney;

    //boal -->
	if (sti(_refCharacter.index) == GetMainCharacterIndex()) // флаг лога
	{
		if (_Money > 0)
		{
			//Log_Info("Добавлено " + _Money + " песо");
			notification(StringFromKey("characterUtilite_1", _Money), "Money");
			Statistic_AddValue(Pchar, "Money_get", _Money);
		}
		else
		{
		    if (_Money < 0)
			{
				//Log_Info("Потрачено " + abs(_Money) + " песо");
				notification(StringFromKey("characterUtilite_2", abs(_Money)), "Money");
				Statistic_AddValue(Pchar, "Money_spend", abs(_Money));
			}
		}
	}
	// boal <--
	return newMoney;
}

void SetBaseShipData(ref refCharacter)
{
    int  i;
    aref refShip;
    int  nShipType;
    ref  refBaseShip;

	if (CheckAttribute(refCharacter,"Ship"))
	{
		if(!CheckAttribute(refCharacter, "ship.upgrades"))
		{
			refCharacter.ship.upgrades.hull = 1;
			refCharacter.ship.upgrades.sails = 1;
			refCharacter.ship.upgrades.cannons = 1;
		}
		makearef(refShip,refCharacter.Ship);
		nShipType = GetCharacterShipType(refCharacter);
		if(nShipType==SHIP_NOTUSED) return;

		refBaseShip = GetRealShip(nShipType);

		if(!CheckAttribute(refBaseShip, "HP"))
		{
			trace ("ship have not HP.");
			return;
		}
		
		refShip.HP = refBaseShip.HP;
		refShip.SP = refBaseShip.SP;

        refShip.Soundtype = refBaseShip.Soundtype;

		refShip.Pos.x = 0;
		refShip.Pos.y = 0;
		refShip.Pos.z = 0;
		refShip.Ang = "";

		refShip.Cannons.Charge.Type = GOOD_BALLS;

		if (!CheckAttribute(refShip,"Cannons.Type")) 
		{
			refShip.Cannons.Type = GetCannonByTypeAndCaliber(RandPhraseSimple("cannon","culverine"), sti(refBaseShip.MaxCaliber));
		}

		if (!CheckAttribute(refShip,"Crew.Morale"))	
		{ 
			refShip.Crew.Morale = 20 + rand(79);	
		}
		if (!CheckAttribute(refShip,"Crew.Quantity")) 
		{ 
			refShip.Crew.Quantity = refBaseShip.OptCrew; // оптимальная команда 
		}
        
		SetGoodsInitNull(refCharacter); // boal пееренс в метод
		// новый опыт
        if(!CheckAttribute(refCharacter, "ship.crew.Exp"))
		{
			refCharacter.Ship.Crew.Exp.Sailors   = 1 + rand(80);
			refCharacter.Ship.Crew.Exp.Cannoners = 1 + rand(80);
			refCharacter.Ship.Crew.Exp.Soldiers  = 1 + rand(80);
		}
		int iGoodN = 0;
		int iGoodR = 0;

		// boal -->
		i = GetCharacterFreeSpace(refCharacter,GOOD_POWDER) / 40;
        if(i>0)
        {
			if(i>=500)
            {
				SetCharacterGoods(refCharacter,GOOD_POWDER, 500 - rand(50));
			} else
            {
				SetCharacterGoods(refCharacter,GOOD_POWDER,i);
			}
		}
		// boal <--
		// bombs		
		i = GetCharacterFreeSpace(refCharacter,GOOD_BOMBS) / 42;
		if(i>0) 
		{
			if(i > 600)
			{
				i = 600;
			}
			iGoodN = 20;
			iGoodR = rand(i - iGoodN);
			if(iGoodR < 0)
			{
				iGoodR = 0;
			}
			iGoodN = iGoodN + iGoodR;
			SetCharacterGoods(refCharacter,GOOD_BOMBS,iGoodN);
		}

		// grapes
		i = GetCharacterFreeSpace(refCharacter,GOOD_GRAPES) / 60;
		if(i>0) 
		{
			if(i > 200)
			{
				i = 200;
			}
			iGoodN = 20;
			iGoodR = rand(i - iGoodN);
			if(iGoodR < 0)
			{
				iGoodR = 0;
			}
			iGoodN = iGoodN + iGoodR;
			SetCharacterGoods(refCharacter,GOOD_GRAPES,iGoodN);
		}

		// knippels
		i = GetCharacterFreeSpace(refCharacter,GOOD_KNIPPELS) / 60;
		if(i>0) 
		{
			if(i > 200)
			{
				i = 200;
			}
			iGoodN = 20;
			iGoodR = rand(i - iGoodN);
			if(iGoodR < 0)
			{
				iGoodR = 0;
			}
			iGoodN = iGoodN + iGoodR;
			SetCharacterGoods(refCharacter,GOOD_KNIPPELS,iGoodN);
		}

		// cannonballs
		i = GetCharacterFreeSpace(refCharacter,GOOD_BALLS) / 42;
		if(i>0) 
		{
			if(i > 800)
			{
				i = 800;
			}
			iGoodN = 20;
			iGoodR = rand(i - iGoodN);
			if(iGoodR < 0)
			{
				iGoodR = 0;
			}
			iGoodN = iGoodN + iGoodR;
			SetCharacterGoods(refCharacter,GOOD_BALLS,iGoodN);
		}

		//food
		i = GetCharacterFreeSpace(refCharacter,GOOD_FOOD) / 20;
		if(i>0) 
		{
            if(i > 300)
			{
				i = 300;
			}
			iGoodN = 5;
			iGoodR = rand(i - iGoodN);
			if(iGoodR < 0)
			{
				iGoodR = 0;
			}
			iGoodN = iGoodN + iGoodR;
			SetCharacterGoods(refCharacter,GOOD_FOOD,iGoodN);
		}
		//GOOD_WEAPON
		i = GetCharacterFreeSpace(refCharacter,GOOD_WEAPON) / 60;
		if(i>0) 
		{
            if(i > 300)
			{
				i = 300;
			}
			iGoodN = 5;
			iGoodR = rand(i - iGoodN);
			if(iGoodR < 0)
			{
				iGoodR = 0;
			}
			iGoodN = iGoodN + iGoodR;
			SetCharacterGoods(refCharacter,GOOD_WEAPON,iGoodN);
		}
		//
		i = GetCharacterFreeSpace(refCharacter,GOOD_MEDICAMENT) / 100;
		if(i>0) 
		{
            if(i > 300)
			{
				i = 300;
			}
			iGoodN = 5;
			iGoodR = rand(i - iGoodN);
			if(iGoodR < 0)
			{
				iGoodR = 0;
			}
			iGoodN = iGoodN + iGoodR;
			SetCharacterGoods(refCharacter,GOOD_MEDICAMENT,iGoodN);
		}
	}
	refCharacter.ship.crew.disease = 0;
}

void SetGoodsInitNull(ref refCharacter)
{
	NullCharacterGoods(refCharacter);
}

// Warship. Нулим все товары у персонажа. Так уж получилось, что два одинаковых метода
void NullCharacterGoods(ref rChar)
{
	string sGood;
	if(!CheckAttribute(rChar, "Ship")) return;
	
	rChar.Ship.Cargo.Load = 0;
	
	for(i=0; i<GOODS_QUANTITY; i++)
	{
		sGood = Goods[i].Name;
		rChar.Ship.Cargo.Goods.(sGood) = 0;
	}
}

// метод рудимент от к1 видимо :)
void SetBaseFellows(object refCharacter)
{
	aref tmpRef;

	makearef(tmpRef,refCharacter.Fellows.Companions);
	tmpRef.id1 = -1;
	tmpRef.id2 = -1;
	tmpRef.id3 = -1;

	makearef(tmpRef,refCharacter.Fellows.Passengers);
	tmpRef.Quantity = 0;
	tmpRef.id1 = -1;
	tmpRef.id2 = -1;
	tmpRef.id3 = -1;
	tmpRef.id4 = -1;
	tmpRef.id5 = -1;
	tmpRef.id6 = -1;
	tmpRef.id7 = -1;
	tmpRef.id8 = -1;

	makearef(tmpRef,refCharacter.Fellows.Passengers.Officers);
	tmpRef.id1 = -1;
	tmpRef.id2 = -1;
	tmpRef.id3 = -1;
}

// Items Utilite
int GetChrItemQuantity(ref _refCharacter)
{
	aref ar; makearef(ar,_refCharacter.items);
	return GetAttributesNum(ar);
}
bool GiveItem2Character(ref _refCharacter,string itemName)
{
	return TakeNItems(_refCharacter,itemName,1);
}
void TakeItemFromCharacter(ref _refCharacter,string itemName)
{
	TakeNItems(_refCharacter,itemName,-1);
}

// Warship. Просто сокращения -->
void AddItems(ref _Chr, string _ItemID, int _Num)
{
	TakeNItems(_Chr, _ItemID, _Num);
}

void RemoveItems(ref _Chr, string _ItemID, int _Num)
{
	TakeNItems(_Chr, _ItemID, -1*_Num);
}
// <-- Просто сокращения

// Warship 11.05.09 Для новой системы предметов
void GenerateAndAddItems(ref _chr, string _itemID, int _qty)
{
	int i;
	String curItemID;

	for(i = 1; i <= _qty; i++)
	{
		curItemID = GetGeneratedItem(_itemID);
		AddItems(_chr, curItemID, 1);
	}
}

// mitrokosta переделка
bool CheckCharacterItem(ref _refCharacter, string itemName) {
	if(CheckAttribute(_refCharacter, "Items." + itemName) && sti(_refCharacter.Items.(itemName)) > 0) {
		return true;
	}
	
	ref tmpRef;
	if (IsGenerableItem(itemName)) {
		for(int i = ITEMS_QUANTITY; i < TOTAL_ITEMS; i++) {
			tmpRef = &Items[i];
			if(CheckAttribute(tmpRef, "DefItemID")) {
				if(tmpRef.DefItemID == itemName) {
					string sItm = tmpRef.ID;
					if (CheckAttribute(_refCharacter, "Items." + sItm) && (sti(_refCharacter.Items.(sItm)) > 0)) {
						return true;
					}
				}	
			}
		}
	}
	return false;
}

int GetCharacterItem(ref _refCharacter,string itemName)
{
	if(CheckAttribute(_refCharacter,"Items."+itemName))
	{
		return sti(_refCharacter.Items.(itemName));
	}
	return 0;
}

string GetCharacterGenerableItem(ref chr, string itemName) {
	if(CheckAttribute(chr, "Items." + itemName) && sti(chr.Items.(itemName)) > 0) {
		return itemName;
	}
	
	ref tmpRef;
	if (IsGenerableItem(itemName)) {
		for(int i = ITEMS_QUANTITY; i < TOTAL_ITEMS; i++) {
			tmpRef = &Items[i];
			if(CheckAttribute(tmpRef, "DefItemID")) {
				if(tmpRef.DefItemID == itemName) {
					string sItm = tmpRef.ID;
					if (CheckAttribute(chr, "Items." + sItm) && (sti(chr.Items.(sItm)) > 0)) {
						return sItm;
					}
				}	
			}
		}
	}
	return "";
}

int GetCharacterFreeGenerableItem(ref _refCharacter,string itemName) // patch-8
{
	ref tmpRef;
	int iItemQ = 0;
	if(IsGenerableItem(itemName))
	{
		for(int i = ITEMS_QUANTITY; i < TOTAL_ITEMS; i++)
		{
			tmpRef = &Items[i];
			if(CheckAttribute(tmpRef, "ID") && (tmpRef.DefItemID == itemName) )
			{				
				string sItm = tmpRef.ID;	
				if(CheckAttribute(_refCharacter,"Items."+sItm))
				{
					iItemQ = sti(_refCharacter.Items.(sItm));
					if(IsEquipCharacterByItem(_refCharacter, sItm)) 
					{
						iItemQ -= 1;
					}
					return iItemQ;
				}								
			}
		}	
		
		if(CheckAttribute(_refCharacter,"Items."+itemName))
		{
			iItemQ = sti(_refCharacter.Items.(itemName));
			if(IsEquipCharacterByItem(_refCharacter, itemName)) 		   
			{
				iItemQ -= 1;
			}
			return iItemQ;
		}	
		
	}
	else
	{
		if(CheckAttribute(_refCharacter,"Items."+itemName))
		{
			iItemQ = sti(_refCharacter.Items.(itemName));
			if(IsEquipCharacterByItem(_refCharacter, itemName)) 		   
			{
				iItemQ -= 1;
			}
			return iItemQ;
		}	
	}
	return iItemQ;
}

int GetCharacterFreeItem(ref _refCharacter,string itemName)
{
	if(CheckAttribute(_refCharacter,"Items."+itemName))
	{
		int iItemQ = sti(_refCharacter.Items.(itemName));
		if(IsEquipCharacterByItem(_refCharacter, itemName) || 
		   IsEquipCharacterByMap(_refCharacter, itemName) || 
		   IsEquipCharacterByArtefact(_refCharacter, itemName))
		{
			iItemQ -= 1;
		}
		return iItemQ;
	}
	return 0;
}

bool ReplaceItem(ref _refTakingCharacter,ref _refGivingCharacter,string itemName)
{
	bool retVal = CheckCharacterItem(_refGivingCharacter,itemName);
	if( TakeNItems(_refTakingCharacter,itemName,1) )
		TakeNItems(_refGivingCharacter,itemName,-1);
	return retVal;
}

bool TakeNItems(ref _refCharacter, string itemName, int n)
{
	int q;
	aref arItm;
	int   	idLngFile;
	
	if(Items_FindItem(itemName, &arItm) < 0)
	{
		trace("TakeNItems warning - can't find " + itemName + " item");
		return false;
	}
	
	
	if(CheckAttribute(arItm, "gold"))
	{
		if(CheckAttribute(_refCharacter,"Money"))
		{
			q = sti(_refCharacter.Money);
		}
		else
		{
			q = 0;
		}
		
		q += n * sti(arItm.gold);
		
		if(q < 0)
		{
			q = 0;
		}
		
		_refCharacter.Money = q;
		
		//AddItemToCRC(_refCharacter, itemName, n);
		
		return true;
	}	

	if(n > 0)
	{
        //if (findsubstr(itemName, "map_part" , 0) != -1 && GetCharacterItem(_refCharacter,itemName) > 0) return true;
        if (itemName == "treasure_note" && !TreasureNotesHandler(arItm)) return false;
	}
	
	if (itemName == "talisman11" && IsMainCharacter(_refCharacter) && !CheckAttribute(pchar, "TookChickenGod")) {
		Achievment_Set("ach_CL_96");
		pchar.TookChickenGod = true;
	}
	
	if(CheckAttribute(arItm, "price") && sti(arItm.price) == 0)
	{
		if(arItm.ID != "Gold") // Warship. Для нового интерфейса обмена - проверка на золото
		{
			if(CheckAttribute(_refCharacter, "index") && sti(_refCharacter.index) == GetMainCharacterIndex() && IsEntity(_refCharacter))
			{
				PlayStereoSound("interface\important_item.wav");
			}
			
			// Warship 08.05.09 - Не ясная мне логика. И и ИЛИ в одном выражении не поддерживаются скриптовым двигом
			// Перенес вверх
			/*if(n > 0 && IsOfficer(_refCharacter) || IsCompanion(_refCharacter))
			{
				AddMsgToCharacter(_refCharacter, MSGICON_GETITEM);
			}*/
		}
	}
	
	q = GetCharacterItem(_refCharacter, itemName);
	
	if(q + n <= 0)
	{
		DeleteAttribute(_refCharacter, "Items." + itemName);
		
		if(arItm.ID != "Gold") 
		{
			_refCharacter.SystemInfo.itemsCRC = sti(_refCharacter.SystemInfo.itemsCRC) + AddItemToCRC(_refCharacter, itemName, -q);
		}	
		
		if(CheckAttribute(arItm, "id") && arItm.id == "gold_dublon")
		{
			_refCharacter.dublon = 0;
		}
		
	}
	else
	{
		if(q <= 0 && GetChrItemQuantity(_refCharacter) >= MAX_ITEM_TAKE)
		{
			return false;
		}
		
		_refCharacter.Items.(itemName) = q + n;
		
		if(arItm.ID != "Gold") 
		{
			_refCharacter.SystemInfo.itemsCRC = sti(_refCharacter.SystemInfo.itemsCRC) + AddItemToCRC(_refCharacter, itemName, n);
		}	
		
		if(CheckAttribute(arItm, "id") && arItm.id == "gold_dublon")
		{
			_refCharacter.dublon = sti(_refCharacter.dublon) + n;
			if(n > 0 && sti(_refCharacter.index) == GetMainCharacterIndex()) 
			{
				//log_info("Получено "+n+" дублонов");
				notification(StringFromKey("characterUtilite_4", n), "Dubloon");
				PlayStereoSound("interface\took_item.wav");
			}
		}
		else
		{
			if(CheckAttribute(_refCharacter,"index") && sti(_refCharacter.index) == GetMainCharacterIndex())
			{
				if(n > 0)
				{
					idLngFile = LanguageOpenFile("ItemsDescribe.txt");
					if(pchar.chr_ai.type == "player" && !LAi_IsDead(pchar)) notification(StringFromKey("characterUtilite_3")+LanguageConvertString(idLngFile, arItm.name), "BoxPlus");
					//Log_Info(XI_ConvertString("You take item"));
					AddMsgToCharacter(_refCharacter, MSGICON_GETITEM);
					LanguageCloseFile(idLngFile);
				}
				
				if(n < 0)
				{
					idLngFile = LanguageOpenFile("ItemsDescribe.txt");
					//log_info("Отдано: "+LanguageConvertString(idLngFile, arItm.name))
					if(dialogrun) notification(StringFromKey("characterUtilite_5")+LanguageConvertString(idLngFile, arItm.name), "BoxMinus");
					//Log_Info(XI_ConvertString("You give item"));
					LanguageCloseFile(idLngFile);
				}
			}
		}
	}
	
	if(TW_IsActive() && IsMainCharacter(_refCharacter))
	{
		if(arItm.id == "chest_open" && CheckAttribute(&objTask, "land_craft") && objTask.land_craft == "1_Inventory" && CheckAttribute(&TEV, "Tutor.Alchemy"))
		{
			TW_ColorWeak(TW_GetTextARef("Inventory_alchemy"));
			DeleteAttribute(&TEV, "Tutor.Alchemy");
			if(!CheckAttribute(&TEV, "Tutor.Document"))
				TW_FinishLand_Craft_1_Inventory();
		}
		else if(arItm.id == "quest_potion" && objTask.land == "1_Loot" && CheckAttribute(&TEV, "Tutor.NeedPotion"))
		{
			if(TW_IncreaseCounter("land", "Loot_search", 1))
				TW_ColorWeak(TW_GetTextARef("Loot_search"));
			TW_AddBottomText("Loot_potion", StringFromKey("Tutorial_32"), "Default");
			DeleteAttribute(&TEV, "Tutor.NeedPotion");
			TW_RecalculateLayout();
		}
	}
	
	return true;
}

int GetCharacterCurrentIsland(ref _refCharacter)
{
	int curLocNum = FindLocation(_refCharacter.location);   // boal fix Characters[GetMainCharacterIndex()]    - ну-ну
	if(curLocNum<0) return -1;
	return GetIslandIdxByLocationIdx(curLocNum);
}

string GetCharacterCurrentIslandId(ref _refCharacter)
{
	int curLocNum = FindLocation(_refCharacter.location);
	if(curLocNum < 0) return "";
	int CurIdx = GetIslandIdxByLocationIdx(curLocNum);
    if(CurIdx == -1) return "";
	ref CurIsland = GetIslandByIndex(CurIdx);
	return CurIsland.id;
}

int GetIslandIdxByLocationIdx(int locIdx)
{
	aref rootar,ar;
	makearef(rootar,Locations[0].IslandsList);
	for(int i=0; i<GetAttributesNum(rootar); i++)
	{
		ar = GetAttributeN(rootar,i);
		if (locIdx >= sti(ar.begin) && locIdx < sti(ar.end) ) //fix boal 02.02.05
		{
			return FindIsland(GetAttributeName(ar));
		}
	}
	return -1;
}

int GetCurrentLocationNation() 
{
	int curLocNum = FindLocation(Characters[GetMainCharacterIndex()].location);
	if(curLocNum<0) return -1;
	return GetLocationNation(&Locations[curLocNum]);
}

void SetRandomNameToCharacter(ref rCharacter)
{
	int iNation = sti(rCharacter.nation);
	if (iNation == -1 || iNation == PIRATE) iNation = rand(NON_PIRATES);
	
	ref rNames, rLastNames;
    // fix -->
    rNames = &sEnManNames;
	if (rCharacter.sex != "man" && rCharacter.sex != "skeleton") rNames = &sEnWomenNames;
	rLastNames = &sEnFamilies;
	// fix <--
	switch(iNation)
	{
		case ENGLAND:
			rNames = &sEnManNames;
			if (rCharacter.sex != "man" && rCharacter.sex != "skeleton") rNames = &sEnWomenNames;
			rLastNames = &sEnFamilies;
		break;
		case FRANCE:
			rNames = &sFrManNames;
			if (rCharacter.sex != "man" && rCharacter.sex != "skeleton") rNames = &sFrWomenNames;
			rLastNames = &sFrFamilies;
		break;
		case SPAIN:
			rNames = &sSpManNames;
			if (rCharacter.sex != "man" && rCharacter.sex != "skeleton") rNames = &sSpWomenNames;
			rLastNames = &sSpFamilies;
		break;
		case HOLLAND:
			rNames = &sHoManNames;
			if (rCharacter.sex != "man" && rCharacter.sex != "skeleton") rNames = &sHoWomenNames;
			rLastNames = &sHoFamilies;
		break;
		case PIRATE:
			rNames = &sEnManNames;
			if (rCharacter.sex != "man" && rCharacter.sex != "skeleton") rNames = &sEnWomenNames;
			rLastNames = &sEnFamilies;
		break;
	}

	rCharacter.name = GetRandSubString(rNames[rand(GetArraySize(rNames) - 2)]);
	rCharacter.lastname = GetRandSubString(rLastNames[rand(GetArraySize(rLastNames) - 2)]);
}

string GenerateRandomName(int iNation, string sSex)
{
	if (iNation == -1 || iNation == PIRATE) iNation = rand(NON_PIRATES);
	
	ref rNames, rLastNames;

	switch(iNation)
	{
		case ENGLAND:
			rNames = &sEnManNames;
			if (sSex != "man") rNames = &sEnWomenNames;
			rLastNames = &sEnFamilies;
		break;
		case FRANCE:
			rNames = &sFrManNames;
			if (sSex != "man") rNames = &sFrWomenNames;
			rLastNames = &sFrFamilies;
		break;
		case SPAIN:
			rNames = &sSpManNames;
			if (sSex != "man") rNames = &sSpWomenNames;
			rLastNames = &sSpFamilies;
		break;
		case HOLLAND:
			rNames = &sHoManNames;
			if (sSex != "man") rNames = &sHoWomenNames;
			rLastNames = &sHoFamilies;
		break;
		case PIRATE:
			rNames = &sEnManNames;
			if (sSex != "man") rNames = &sEnWomenNames;
			rLastNames = &sEnFamilies;
		break;
	}

	string sname = GetRandSubString(rNames[rand(GetArraySize(rNames) - 2)]);
	string slastname = GetRandSubString(rLastNames[rand(GetArraySize(rLastNames) - 2)]);
	
	sname = sname + " " + slastName;
	return sName;
}

void SetRandomNameToCharacter_Generator(ref rCharacter)
{
	int iNation = sti(rCharacter.nation);
	if (iNation == -1 || iNation == PIRATE) iNation = rand(NON_PIRATES);
	
	ref rNames, rLastNames;
    // fix -->
    rNames = &sEnManGenNames;
	if (rCharacter.sex != "man" && rCharacter.sex != "skeleton") rNames = &sEnWomenGenNames;
	rLastNames = &sEnGenFamilies;
	// fix <--
	switch(iNation)
	{
		case ENGLAND:
			rNames = &sEnManGenNames;
			if (rCharacter.sex != "man" && rCharacter.sex != "skeleton") rNames = &sEnWomenGenNames;
			rLastNames = &sEnGenFamilies;
		break;
		case FRANCE:
			rNames = &sFrManGenNames;
			if (rCharacter.sex != "man" && rCharacter.sex != "skeleton") rNames = &sFrWomenGenNames;
			rLastNames = &sFrGenFamilies;
		break;
		case SPAIN:
			rNames = &sSpManGenNames;
			if (rCharacter.sex != "man" && rCharacter.sex != "skeleton") rNames = &sSpWomenGenNames;
			rLastNames = &sSpGenFamilies;
		break;
		case HOLLAND:
			rNames = &sHoManGenNames;
			if (rCharacter.sex != "man" && rCharacter.sex != "skeleton") rNames = &sHoWomenGenNames;
			rLastNames = &sHoGenFamilies;
		break;
		case PIRATE:
			rNames = &sEnManGenNames;
			if (rCharacter.sex != "man" && rCharacter.sex != "skeleton") rNames = &sEnWomenGenNames;
			rLastNames = &sEnGenFamilies;
		break;
	}

	rCharacter.name = GetRandSubString(rNames[rand(GetArraySize(rNames) - 2)]);
	rCharacter.lastname = GetRandSubString(rLastNames[rand(GetArraySize(rLastNames) - 2)]);
}

string GenerateRandomName_Generator(int iNation, string sSex)
{
	if (iNation == -1 || iNation == PIRATE) iNation = rand(NON_PIRATES);
	
	ref rNames, rLastNames;

	switch(iNation)
	{
		case ENGLAND:
			rNames = &sEnManGenNames;
			if (sSex != "man") rNames = &sEnWomenGenNames;
			rLastNames = &sEnGenFamilies;
		break;
		case FRANCE:
			rNames = &sFrManGenNames;
			if (sSex != "man") rNames = &sFrWomenGenNames;
			rLastNames = &sFrGenFamilies;
		break;
		case SPAIN:
			rNames = &sSpManGenNames;
			if (sSex != "man") rNames = &sSpWomenGenNames;
			rLastNames = &sSpGenFamilies;
		break;
		case HOLLAND:
			rNames = &sHoManGenNames;
			if (sSex != "man") rNames = &sHoWomenGenNames;
			rLastNames = &sHoGenFamilies;
		break;
		case PIRATE:
			rNames = &sEnManGenNames;
			if (sSex != "man") rNames = &sEnWomenGenNames;
			rLastNames = &sEnGenFamilies;
		break;
	}

	string sname = GetRandSubString(rNames[rand(GetArraySize(rNames) - 2)]);
	string slastname = GetRandSubString(rLastNames[rand(GetArraySize(rLastNames) - 2)]);
	
	sname = sname + " " + slastName;
	return sName;
}

//=============================================================================
//  EQUIP SECTION
//=============================================================================
string FindCharacterItemByGroup(ref chref, string groupID)
{
 	int i,n;
	ref refItm;
    float  maxBladeValue, curBladeValue;
    string resultItemId;
	
	//if (CheckAttribute(chref, "CanTakeMushket") && CheckAttribute(chref, "IsMushketer")) return ""; // мушкеты не выбираем
    // boal 17.06.05 офицерам даем кулаки -->
	if (groupID == BLADE_ITEM_TYPE && IsOfficer(chref) && IsEquipCharacterByItem(chref, "unarmed") && !CheckAttribute(chref, "isMusketer"))
	{
        RemoveCharacterEquip(chref, BLADE_ITEM_TYPE);
        TakeItemFromCharacter(chref, "unarmed");
	}
	// boal 17.06.05 офицерам даем кулаки <--
	maxBladeValue = 0;
	resultItemId  = "";
	for(i=TOTAL_ITEMS-1; i>=0; i--)
	{
		refItm = &Items[i];
		if( !CheckAttribute(refItm,"groupID") ) continue;
		if(refItm.groupID!=groupID) continue;
		if( !CheckAttribute(chref,"items."+refItm.id) ) continue;
		if(groupID==GUN_ITEM_TYPE || groupID == MUSKET_ITEM_TYPE)	// evganat - мушкеты
		{
			if( !CheckAttribute(refItm,"chargeQ") ) continue;
			n = sti(refItm.chargeQ);
			if(n<2) {return refItm.id;}
			if(n<5)
			{
				if( IsCharacterPerkOn(chref,"Gunman") ) {return refItm.id;}
				else continue;
			}
            //boal -->
            if( IsCharacterPerkOn(chref,"GunProfessional") )	{return refItm.id;}
            // boal <--
			continue;
		}
		// boal 08.10.04 броню офицерам -->
		// Jason: больше перк кирасы не нужен, водолаза и мундиры офицерам не даем
		if (groupID == CIRASS_ITEM_TYPE)
		{
          // if( IsCharacterPerkOn(chref, "Ciras") )	{return refItm.id;}
			if(refItm.Clothes == false)	return refItm.id;
           continue;
		}
		// boal 08.10.04 броню офицерам <--

		// перебор на лучшую саблю
		if (groupID == BLADE_ITEM_TYPE)
		{
			// формула лучшего выбора
			//( 20 + ( 0.6 * bAttack + 0.4 * bAttack * GetCharacterSkill(chref, refItm.FencingType) * ( 1 + ( 1 - bBlnce ) * ( bBlnce - 1 ) / 5 ) ) / Wght
			curBladeValue = (20.0 + (0.6 * stf(refItm.Attack) + 0.4 * stf(refItm.Attack) * (GetCharacterSkill(chref, refItm.FencingType) / SKILL_MAX) * (1.0 + (1.0 - stf(refItm.Balance)) * (stf(refItm.Balance) - 1.0)/5.0) ) ) / stf(refItm.Weight);
			
			if (curBladeValue > maxBladeValue)
			{
			    maxBladeValue = curBladeValue;
			    resultItemId  = refItm.id;
			}
		}
		else
		{
		    return refItm.id;
		}
	}
	
	if (resultItemId != "")
	{
        return resultItemId;
	}
	// boal 17.06.05 офицерам даем кулаки -->
	if (groupID == BLADE_ITEM_TYPE && IsOfficer(chref) && sti(chref.index) != GetMainCharacterIndex() && !CheckAttribute(chref, "isMusketer"))
	{
        GiveItem2Character(chref, "unarmed");
        EquipCharacterByItem(chref, "unarmed");
	}
	// boal 17.06.05 офицерам даем кулаки <--
	return "";  //ничего не делать далее
}

bool IsEquipCharacterByItem(ref chref, string itemID)
{
	aref arEquip;
	makearef(arEquip,chref.equip);
	int q = GetAttributesNum(arEquip);
	for(int i=0; i<q; i++)
	{	
		if(GetAttributeValue(GetAttributeN(arEquip,i))==itemID) return true;
	}
	return false;
}

// --> ugeen - проверяем, есть ли карта в атласе     18.06.09
bool IsEquipCharacterByMap(ref chref, string itemID)
{
	aref arEquip;
	string groupID = MAPS_ITEM_TYPE;
	
	makearef(arEquip,chref.equip.(groupID));
	int q = GetAttributesNum(arEquip);
	for(int i=0; i<q; i++)
	{	
		if(GetAttributeValue(GetAttributeN(arEquip,i))==itemID) return true;
	}
	
	return false;
}

// получить суммарный вес экипированных предметов в зависимости от группы -> нужно для атласа карт
float GetEquippedItemsWeight(ref chref, string groupID)
{	
	int 	j;
	string  itemID;
    ref     itm;
	float 	fEquipWeight = 0.0;
	
	for (j=0; j<TOTAL_ITEMS; j++)
    {
		makeref(itm, Items[j]);		
		if(CheckAttribute(itm, "ID") && CheckAttribute(itm,"groupID"))
		{
			itemID = itm.id;			
			if(groupID == MAPS_ITEM_TYPE)
			{
				if (CheckAttribute(itm, "mapType"))
				{
					if (CheckAttribute(chref, "items."+itemID) && IsEquipCharacterByMap(chref, itemID))
					{
						fEquipWeight += stf(itm.Weight);
					}
				}					
			}
			else
			{
				if (CheckAttribute(chref, "items."+itemID) && IsEquipCharacterByItem(chref, itemID))
				{
					fEquipWeight += stf(itm.Weight);
				}				
			}			
		}	
	}		
	return fEquipWeight;
}
// <-- ugeen

string GetCharacterEquipByGroup(ref chref, string groupID)
{
	if( CheckAttribute(chref,"equip."+groupID) ) return chref.equip.(groupID);
	return "";
}

string GetCharacterEquipPictureByGroup(ref chref, string groupID)
{
	string sItem = GetCharacterEquipByGroup(chref, groupID);
	for(int i = TOTAL_ITEMS-1; i >= 0; i--)
	{
		if(CheckAttribute(&items[i], "ID") && items[i].id == sItem)
		{
			if(Items[i].id == "spyglass5")
			{
				Items[i].picIndex = 4;
			}
			return groupID + items[i].picIndex;
		}
	}
	return "";
}

void RemoveCharacterEquip(ref chref, string groupID)
{
	if(groupID == GUN_ITEM_TYPE)
	{
		DeleteAttribute(chref, "bullets.gun");
		if(CheckAttribute(chref, "equip.tempgunid"))
			DeleteAttribute(chref, "equip.tempgunid");
	}
	if(groupID == MUSKET_ITEM_TYPE)
		DeleteAttribute(chref, "bullets.musket");
	DeleteAttribute(chref,"equip."+groupID);
	SetEquipedItemToCharacter(chref,groupID,"");
}

void RemoveOfficerEquip(ref chref, string groupID)
{
	string sItemID = chref.equip.(groupid);

	DeleteAttribute(chref,"equip."+groupID);
	SetEquipedItemToCharacter(chref,groupID,"");
	TakeItemFromCharacter(chref, sItemID);
	GiveItem2Character(pchar, sItemID);
}

void SetEquipedItemToCharacter(ref chref, string groupID, string itemID)
{
	object emptyItm;
	aref arItm;
	string modelName = "";
	makearef(arItm,emptyItm);
 	int itemNum; // boal 23.01.2004
	bool bEquip = (itemID != "");

	if(bEquip)
	{
		if( !CheckCharacterItem(chref,itemID) ) return;
		itemNum = Items_FindItem(itemID,&arItm);// boal 23.01.2004
	}
	
	switch(groupID)
	{
		case TOOL_ITEM_TYPE:
			
		break;
		case SPYGLASS_ITEM_TYPE:
			if(CheckAttribute(arItm,"id"))
			{
				setTelescopeInitParameters(arItm);
			}
		break;
	    // boal -->
	    case CIRASS_ITEM_TYPE:
	        if (CheckAttribute(chref, "HeroModel")) // все, у кого есть что одеть
	        {
	            if (CheckAttribute(arItm, "model"))
	            {
	                chref.model = GetSubStringByNum(chref.HeroModel, sti(arItm.model));
	                chref.cirassId = itemNum;
					if(startHeroType != 4 && chref.id == "blaze")
					{
						//log_testinfo("SDM");
						chref.model.animation = chref.model;
					}
					if(CheckAttribute(chref,"CanTakeMushket"))
					{
						chref.model.animation = chref.model;
					}
					string hat = GetCharacterEquipByGroup(chref, HAT_ITEM_TYPE);
					if(hat != "")
					{
						SetEquipedItemToCharacter(chref, HAT_ITEM_TYPE, hat);
					}
	            }
	            else
	            {
	                chref.model = GetSubStringByNum(chref.HeroModel, 0);
					chref.model.animation = chref.model;
	                DeleteAttribute(chref, "cirassId");
	            }
	        }
	        else
	        {
	            // тут анализ модели офицера или пирата
	            if(CheckAttribute(arItm, "model"))
	            {
	                chref.cirassId = itemNum;
	            }
	            else
	            {
	                DeleteAttribute(chref, "cirassId");
	            }
	        }
	        SetNewModelToChar(chref);//boal
			if (chref.model == "protocusto") {
				PostEvent("InterfaceBreak", 499); // mitrokosta fix
				DoQuestCheckDelay("TalkSelf_Quest", 0.5); // Jason
			}
		break;

		case PATENT_ITEM_TYPE:
	        if(CheckAttribute(arItm,"quest"))
	        {
	            DoQuestCheckDelay(arItm.quest, 1.0);
	            chref.EquipedPatentId = itemNum; // boal текущий патент
	        }
	        else
	        {
	            DeleteAttribute(chref, "EquipedPatentId");
	        }
	    break;
	    // boal <--
		case GUN_ITEM_TYPE:
			if(CheckAttribute(arItm,"model"))	{modelName = arItm.model;}
			SendMessage(chref, "ls", MSG_CHARACTER_SETGUN, modelName);
			SetGunParameters(chref, "gun", itemID, bEquip);
		break;
		
		case MUSKET_ITEM_TYPE:
			if(CheckAttribute(arItm,"model"))	{modelName = arItm.model;}
			//SendMessage(chref, "ls", MSG_CHARACTER_SETMUS, modelName);
			MusketEquipOldLogic(chref, modelName, bEquip);
			SetGunParameters(chref, "musket", itemID, bEquip);
		break;

		case BLADE_ITEM_TYPE:
			float liveTime = 0.1;
			int colors = argb(64, 64, 64, 64);
			int colore = argb(0, 32, 32, 32);
			if(CheckAttribute(arItm,"model"))	{modelName = arItm.model;}
			if(CheckAttribute(arItm, "blade.time"))	{liveTime = stf(arItm.blade.time);}
			if(CheckAttribute(arItm, "blade.colorstart"))	{colors = sti(arItm.blade.colorstart);}
			if(CheckAttribute(arItm, "blade.colorend"))	{colore = sti(arItm.blade.colorend);}			
			SendMessage(chref, "llsfll", MSG_CHARACTER_SETBLADE, 0, modelName, liveTime, colors, colore);
			// boal -->
			if(CheckAttribute(arItm,"FencingType"))
			{	LAi_BladeFencingType(chref, arItm.FencingType);
			} else
			{	LAi_BladeFencingType(chref, "FencingS");
			}
			if(CheckAttribute(arItm,"Weight")) //eddy.при загрузки локации если у ГГ нет оружия - ошибка
			{
				LAi_SetBladeEnergyType(chref, GetEnergyBladeDrain(stf(arItm.Weight), arItm.FencingType ) );  // энергоемкость от веса и типа
			}		
			// boal <--
		break;

		case HAT_ITEM_TYPE:
			if(CheckAttribute(arItm,"model"))	{modelName = arItm.model;}
			SendMessage(chref, "lsl", MSG_CHARACTER_EX_MSG, "UntieItem", 10);
			if(HasHatLocator(chref))
			{
				SendMessage(chref, "lslssl", MSG_CHARACTER_EX_MSG, "TieItem", 10, modelName, "hat", 1);
			}
		break;

		// --> ugeen 18.06.09   - увеличиваем счетчик карт в атласе	
		case MAPS_ITEM_TYPE:	
			if(CheckAttribute(chref, "MapsAtlasCount"))
			{
				if(CheckAttribute(arItm,"Atlas") && sti(arItm.Atlas) > 0) // ugeen fix
				{
					chref.MapsAtlasCount = sti(chref.MapsAtlasCount) + 1;
					if(sti(chref.MapsAtlasCount) == MAPS_IN_ATLAS && !CheckCharacterPerk(chref, "MapMaker"))  // даем скрытый перк если собрали все карты островов
					{
						SetCharacterPerk(chref, "MapMaker");
					}	
				}	
			}			
		break;	
	// <-- ugeen
	}
}

void SetGunParameters(ref chref, string sType, string itemID, bool bEquip)
{
	if(bEquip)
	{
		if(CheckAttribute(chref,"chr_ai." + sType + ".sGun") && itemID == chref.chr_ai.(sType).sGun)
		{
			if(CheckAttribute(chref,"chr_ai." + sType + ".bullet"))
			{
				LAi_SetCharacterUseBullet(chref, sType, chref.chr_ai.(sType).bullet);
			}
			else
			{
				LAi_SetCharacterDefaultBulletType(chref, sType);
				LAi_GunSetUnload(chref, sType);
			}
		}
		else
		{
			LAi_SetCharacterDefaultBulletType(chref, sType);
			LAi_GunSetUnload(chref, sType);
		}
		if(sType == "musket") chref.IsMushketer = true;
	}
	else
	{
		if(CheckAttribute(chref,"chr_ai." + sType + ".sGun"))		DeleteAttribute(chref,"chr_ai." + sType + ".sGun");
		if(CheckAttribute(chref,"chr_ai." + sType + ".bullet"))		DeleteAttribute(chref,"chr_ai." + sType + ".bullet");
		if(CheckAttribute(chref,"chr_ai." + sType + ".charge_max")) DeleteAttribute(chref,"chr_ai." + sType + ".charge_max");
		if(CheckAttribute(chref,"chr_ai." + sType + ".chargeprc")) 	DeleteAttribute(chref,"chr_ai." + sType + ".chargeprc");
		if(CheckAttribute(chref,"chr_ai." + sType + ".basedmg")) 	DeleteAttribute(chref,"chr_ai." + sType + ".basedmg");
		if(CheckAttribute(chref,"chr_ai." + sType + ".shards")) 	DeleteAttribute(chref,"chr_ai." + sType + ".shards");
		if(CheckAttribute(chref,"chr_ai." + sType + ".width")) 		DeleteAttribute(chref,"chr_ai." + sType + ".width");
		if(CheckAttribute(chref,"chr_ai." + sType + ".height")) 	DeleteAttribute(chref,"chr_ai." + sType + ".height");
		if(sType == "musket" && CheckAttribute(chref,"PriorityMode")) chref.PriorityMode = 1; //Сброс на сабельный
		if(sType == "musket" && CheckAttribute(chref,"IsMushketer")) DeleteAttribute(chref,"IsMushketer");
	}	
}

//Rosarak. Пока нет универсальной системы с пресетами режимов, надо так
void MusketEquipOldLogic(ref chref, string modelName, bool bEquip)
{
	if(IsMainCharacter(chref) || chref.id == "blaze")
	{
		SendMessage(chref, "ls", MSG_CHARACTER_SETMUS, modelName);
		return;
	}
	
	//if(IsOfficer(chref))
	if(CheckAttribute(chref,"CanTakeMushket"))
	{
		//if(!IsMainCharacter(chref))
		//{
			if(chref.model.animation != chref.model)
			{
				chref.model.animation = chref.model;
			}
			if(CheckAttribute(chref,"PriorityMode"))
			{
				SendMessage(chref, "lsl", MSG_CHARACTER_EX_MSG, "SetMusketer", sti(chref.PriorityMode) == 2);
			}
			else SendMessage(chref, "lsl", MSG_CHARACTER_EX_MSG, "SetMusketer", bEquip);
			SendMessage(chref, "ls", MSG_CHARACTER_SETMUS, modelName);
			return;
		//}
	}
	
	if(!bEquip)
	{
		if(CheckAttribute(chref, "equip.gun"))
		{
			aref arItm;
			Items_FindItem(chref.equip.gun, &arItm);
			modelName = arItm.model;
		}
		if(GetCharacterAnimation(chref) == "mushketer")
		{
			chref.model = FindStringBeforeChar(chref.model, "_mush");
			chref.model.animation = "man"; //Можно и через резерв
		}
	}
	else
	{
		if(GetCharacterAnimation(chref) != "mushketer")
		{
			chref.model = chref.model + "_mush";
			chref.model.animation = "mushketer";
		}
	}
	
	SendMessage(chref, "lss", MSG_CHARACTER_SETMODEL, chref.model, chref.model.animation);
	SendMessage(chref, "lsl", MSG_CHARACTER_EX_MSG, "SetMusketer", bEquip); //Флаг в движок на мушкетёрский ИИ
	SendMessage(chref, "ls",  MSG_CHARACTER_SETGUN, modelName);
}

// коэф траты энергии от веса сабли
float GetEnergyBladeDrain(float _weight, string _bladeType)
{
	float drain = 0.0;
	switch(_bladeType)
	{
		case "FencingL" :
			drain =  _weight / 4.5 + 0.4;
		break;
		case "FencingS" :
			drain = _weight / 3.75 + 0.4;
		break;
		case "FencingH" :
			drain = _weight / 3.0 + 0.4;
		break;
	}
	return drain;
}

void EquipCharacterByItem(ref chref, string itemID)
{
	aref arItm;

	if( !CheckCharacterItem(chref, itemID) ) return;
	int itemNum = Items_FindItem(itemID, &arItm); // mitrokosta понадобится позже
	if( itemNum < 0 ) return;
	if( !CheckAttribute(arItm, "groupID") ) return;

	string groupName = arItm.groupID;
	if(groupName != MAPS_ITEM_TYPE) // ugeen - для атласа карт  18.06.09
	{
		string oldItemID = GetCharacterEquipByGroup(chref, groupName);
		if(oldItemID == itemID) return;
	}	
	
	if (chref.model.animation == "mushketer")
	{
		if(groupName == BLADE_ITEM_TYPE && itemID != "unarmed") return;
		
		if(chref.index != GetMainCharacterIndex())
		{			
			if (groupName == GUN_ITEM_TYPE && !HasSubStr(arItm.id, "mushket")) return;			
		}
	}
	else
	{
		if (groupName == GUN_ITEM_TYPE) 
		{
			if (!CheckAttribute(arItm,"chargeQ") )
			{
				return;
			}
			int chrgQ = sti(arItm.chargeQ);
			if (chrgQ >= 2 && arItm.id != "pistol9" && arItm.id != "pistol6")
			{
				if (!IsCharacterPerkOn(chref,"GunProfessional")) return;
			}	
		}
		if (groupName == MUSKET_ITEM_TYPE) 
		{
			if(!IsCharacterPerkOn(chref,"Gunman"))	return;
			if (!CheckAttribute(arItm,"chargeQ") )
			{
				return;
			}
			chrgQ = sti(arItm.chargeQ);
			if (chrgQ >= 2 )
			{
				if (!IsCharacterPerkOn(chref,"GunProfessional")) return;
			}
		}
	}
	
	if(groupName != MAPS_ITEM_TYPE) // ugeen  18.06.09
	{
		chref.equip.(groupName) = itemID;
	}
	else
	{
		if (CheckAttribute(arItm,"mapType"))
		{
			chref.equip.(groupName).(itemID) = itemID;		
		}	
	}	
	if(IsEntity(&chref)) 
	{
		SetEquipedItemToCharacter(chref, groupName, itemID);
	} 
	else 
	{ // --> mitrokosta фикс надевания кирас в море
		if (groupName == CIRASS_ITEM_TYPE) 
		{
			if (CheckAttribute(chref, "HeroModel")) 
			{
				if (CheckAttribute(arItm, "model")) 
				{
					chref.model = GetSubStringByNum(chref.HeroModel, sti(arItm.model));
					chref.cirassId = itemNum;
					if(startHeroType != 4 && chref.id == "blaze")
					{
						//log_testinfo("SDM");
						chref.model.animation = chref.model;
					}
					if(CheckAttribute(chref,"CanTakeMushket"))
					{
						chref.model.animation = chref.model;
					}
				} 
				else 
				{
					chref.model = GetSubStringByNum(chref.HeroModel, 0);
					chref.model.animation = chref.model;
					DeleteAttribute(chref, "cirassId");
				}
			}
			else 
			{
				if(CheckAttribute(arItm, "model")) 
				{
					chref.cirassId = itemNum;
				} 
				else 
				{
					DeleteAttribute(chref, "cirassId");
				}
			}
		}
	} // <--
}
 // to_do
void EquipOfficerByItem(ref chref, string itemID)
{
	aref arItm;

	int iItemQuantity = 0;
	if( !CheckCharacterItem(chref, itemID))
	{
		iItemQuantity = GetCharacterItem(pchar);
		if(iItemQuantity == 1 && IsEquipCharacterByItem(pchar, itemID) == true)
		{
			return;
		}
		else
		{
			TakeItemFromCharacter(pchar, itemID);
			GiveItem2Character(chref, itemID);
		}
	}

	EquipCharacterByItem(chref, itemID);
}

void ExecuteCharacterEquip(ref chref)
{
	string stmp = GetCharacterEquipByGroup(chref,BLADE_ITEM_TYPE);
	if(stmp!="")	{SetEquipedItemToCharacter(chref, BLADE_ITEM_TYPE, stmp);}
	stmp = GetCharacterEquipByGroup(chref,GUN_ITEM_TYPE);
	if(stmp!="")	{SetEquipedItemToCharacter(chref, GUN_ITEM_TYPE, stmp);}
	stmp = GetCharacterEquipByGroup(chref,MUSKET_ITEM_TYPE); // evganat - мушкеты
	if(stmp!="")	{SetEquipedItemToCharacter(chref, MUSKET_ITEM_TYPE, stmp);}
	stmp = GetCharacterEquipByGroup(chref,HAT_ITEM_TYPE);
	if(stmp!="")	{SetEquipedItemToCharacter(chref, HAT_ITEM_TYPE, stmp);}
}

bool IsCanEquiping(ref chref, string equiping_group)
{
	if( CheckAttribute(chref,"equip.disabled_group."+equiping_group)
		&& sti(chref.equip.disabled_group.(equiping_group))==true ) return false;
	return true;
}

void EnableEquip(ref chref, string equiping_group, bool enable)
{
	if(enable)
	{	if(equiping_group=="")
		{	DeleteAttribute(chref,"equip.disabled_group");
		}
		else
		{	DeleteAttribute(chref,"equip.disabled_group."+equiping_group);
		}
	}
	else
	{	if(equiping_group=="")
		{
			string stmp;
			stmp = GUN_ITEM_TYPE;		chref.equip.disabled_group.(stmp) = true;
			stmp = MUSKET_ITEM_TYPE;	chref.equip.disabled_group.(stmp) = true;	// evganat - мушкеты
			stmp = BLADE_ITEM_TYPE;		chref.equip.disabled_group.(stmp) = true;
			stmp = SPYGLASS_ITEM_TYPE;	chref.equip.disabled_group.(stmp) = true;
			//
			stmp = SPECIAL_ITEM_TYPE;	chref.equip.disabled_group.(stmp) = true; // зелье команчей
		}
		else
		{
			chref.equip.disabled_group.(equiping_group) = true;
		}
	}
}


//=============================================================================
//  ARTEFACT ITEMS EQUIP SECTION
//=============================================================================
bool IsEquipCharacterByArtefact(ref chref, string itemID)
{
	aref 	arEquip;
	string 	sAttr;
	int 	i, q;
	ref 	rItem = ItemsFromID(itemID);
	
	if(!CheckAttribute(rItem, "groupID")) return false;
	if(!CheckAttribute(chref, "equip_item")) return false;
	if(rItem.groupID == ITEM_SLOT_TYPE || rItem.groupID == TALISMAN_ITEM_TYPE)
	{
		switch (rItem.groupID)
		{
			case ITEM_SLOT_TYPE 	:
				makearef(arEquip, chref.equip_item);
			break;
		
			case TALISMAN_ITEM_TYPE	:
				makearef(arEquip, chref.equip);
			break;
		}
		q = GetAttributesNum(arEquip);
		for(i = 0; i < q; i++)
		{	
			if(GetAttributeValue(GetAttributeN(arEquip,i)) == itemID) return true;
		}
		return false;
	}	
	return false;
}

string GetCharacterSlotRemainTime(ref chref, string slotID)
{
	if( CheckAttribute(chref, "equip_item." + slotID) ) 
	{
		if(sti(chref.equip_item.(slotID).time) > -1) 
		{
			return chref.equip_item.(slotID).time;
		}	
	}
	return "";
}

string GetCharacterEquipBySlot(ref chref, string slotID)
{
	if( CheckAttribute(chref, "equip_item." + slotID) ) return chref.equip_item.(slotID);
	return SLOT_NOT_USED;
}

string GetCharacterEquipSlot(ref chref, string itemID)
{
	aref arEquip;
	string sAttr;
	makearef(arEquip, chref.equip_item);
	int q = GetAttributesNum(arEquip);
	for(int i = 0; i < q; i++)
	{
		sAttr = GetAttributeName(GetAttributeN(arEquip, i));
		if(arEquip.(sAttr) == itemID) return sAttr;
	}
	return SLOT_NOT_USED;
}

string GetCharacterFreeSlot(ref chref)
{
	string sAttr;
	aref arEquip;
	makearef(arEquip, chref.equip_item);
	int q = GetAttributesNum(arEquip);
	for(int i = 0; i < q; i++)
	{
		sAttr = GetAttributeName(GetAttributeN(arEquip, i));
		if(arEquip.(sAttr) == SLOT_NOT_USED) return sAttr;
	}	
	return SLOT_NOT_USED;
}

bool IsCanArtefactBeEquipped(ref chref, string itemID)
{
	aref arEquip;
	string sAttr, sItem;
	makearef(arEquip, chref.equip_item);
	int q = GetAttributesNum(arEquip);
	for(int i = 0; i < q; i++)
	{
		sAttr = GetAttributeName(GetAttributeN(arEquip, i));		
		sItem = arEquip.(sAttr);
		if(sItem == SLOT_NOT_USED) continue;
		else
		{
			ref rItem1 = ItemsFromID(sItem);  	// экипированный артефакт
			ref rItem2 = ItemsFromID(itemID); 	// артефакт который хотим одеть
			if(!CheckAttribute(rItem1,"type") || !CheckAttribute(rItem2,"type")) return false;
			if(rItem1.type == rItem2.type) continue;
			if(rItem1.type == ITEM_OBEREG || rItem1.type == ITEM_TOTEM) continue;
			if(rItem2.type == ITEM_OBEREG || rItem2.type == ITEM_TOTEM) continue;
			else return false; 					// разного типа - одеть нельзя !!!!!
		}
	}
	return true;
}

string GetCharacterEquipPictureBySlot(ref chref, string slotID)
{
	string sItem = GetCharacterEquipBySlot(chref, slotID);
	for(int i = TOTAL_ITEMS - 1; i >= 0; i--)
	{
		if(CheckAttribute(&items[i], "ID") && items[i].id == sItem)
		{
			return items[i].picIndex;
		}
	}
	return "";
}

int GetCharacterEquipSlotUsedPicture(ref chref, string slotID)
{
	string sItem = GetCharacterEquipBySlot(chref, slotID);
	if(sItem != SLOT_NOT_USED)
	{
		ref rItem = ItemsFromID(sItem);
		string slotRemainTime = GetCharacterSlotRemainTime(chref, slotID);
		if(CheckAttribute(rItem, "time") && sti(rItem.time) > -1 && slotRemainTime != "")
		{
			return makeint(9 * (sti(rItem.time) - sti(slotRemainTime))/sti(rItem.time));
		}
	}
	return 0;
}

void RemoveCharacterArtefactEquip(ref chref, string slotID)
{
	string sItem = GetCharacterEquipBySlot(chref, slotID);
	if(sItem != "")
	{
		ref rItem = ItemsFromID(sItem);
		if(CheckAttribute(rItem, "time") && sti(rItem.time) > -1) // бессрочные артефакты оставляем
		{
			TakeNItems(chref, sItem, -1);			
		}
	}	
	chref.equip_item.(slotID) = "";
	chref.equip_item.(slotID).time = -1;
}

void EquipCharacterByArtefact(ref chref, string itemID)
{
	aref arItm;
	string slotID;

	if( !CheckCharacterItem(chref, itemID) ) return;
	if( Items_FindItem(itemID, &arItm) < 0 ) return;
	if( !CheckAttribute(arItm, "groupID") ) return;
	if(arItm.groupID == ITEM_SLOT_TYPE)
	{
		if(IsEquipCharacterByArtefact(chref, itemID)) return; // если уже экипирован этим артефактом
		slotID = GetCharacterFreeSlot(chref);
		if(slotID != SLOT_NOT_USED)
		{
			chref.equip_item.(slotID) 		= itemID;
			if(CheckAttribute(arItm,"time"))
			{
				int addTime = 0;
				if(ShipBonus2Artefact(chref, SHIP_GALEON_SM) && isMonkArtefact(itemID))
				{
					addTime += 15;
				}
				chref.equip_item.(slotID).time 	= sti(arItm.time)+addTime;
			}
			else chref.equip_item.(slotID).time = -1;	
		}
		else return;
	}
}

void EquipOfficerByArtefact(ref chref, string itemID)
{
	aref arItm;

	int iItemQuantity = 0;
	if( !CheckCharacterItem(chref, itemID))
	{
		iItemQuantity = GetCharacterItem(pchar);
		if(iItemQuantity == 1 && IsEquipCharacterByArtefact(pchar, itemID))
		{
			return;
		}
		else
		{
			TakeItemFromCharacter(pchar, itemID);
			GiveItem2Character(chref, itemID);
		}
	}
	EquipCharacterByArtefact(chref, itemID);
}

void UpdateCharacterEquipItem(ref chref)
{
	aref 	arEquip;
	string 	sAttr, sItem;
	int   	idLngFile;
	
	makearef(arEquip, chref.equip_item);
	int q = GetAttributesNum(arEquip);
	for(int i = 0; i < q; i++)
	{
		sAttr = GetAttributeName(GetAttributeN(arEquip, i));
		if(arEquip.(sAttr) != SLOT_NOT_USED) 
		{
			if(CheckAttribute(arEquip,(sAttr) + ".time") && sti(arEquip.(sAttr).time) > 0)
			{
				arEquip.(sAttr).time = sti(arEquip.(sAttr).time) - 1;
				if(sti(arEquip.(sAttr).time) == 0) 
				{
					idLngFile = LanguageOpenFile("ItemsDescribe.txt");
					sItem = GetCharacterEquipBySlot(chref, sAttr)
					ref arItem = ItemsFromID(sItem);
					pchar.systemInfo.messages.Artefact = GetFullName(chref) + StringFromKey("characterUtilite_6", LanguageConvertString(idLngFile, arItem.name))+ LanguageConvertString(idLngFile, "new_string");
					//Log_SetStringToLog(GetFullName(chref) + " заметил, что артефакт " + LanguageConvertString(idLngFile, arItem.name) + " утратил силу");
					RemoveCharacterArtefactEquip(chref, sAttr);
					LanguageCloseFile(idLngFile);
					if(!IsMainCharacter(chref) && GetCharacterFreeItem(chref, sItem) > 0)
					{
						EquipCharacterByArtefact(chref, sItem);
					}
				}	
			}	
		}
	}
}

void CheckCharactersUpdateItems()
{
	int iPassenger, cn;
	ref sld;

	UpdateCharacterEquipItem(pchar); // ГГ
	for (int io = 0; io < GetPassengersQuantity(pchar); io++) // пассажиры и офицеры
	{
		iPassenger = GetPassenger(pchar, io);
		if (iPassenger != -1)
		{
			sld = GetCharacter(iPassenger);
			UpdateCharacterEquipItem(sld);
		}
	}
	for (int i=1; i<COMPANION_MAX; i++) // компаньоны
	{
		cn = GetCompanionIndex(pchar, i);
		if(cn != -1)
		{
			sld = GetCharacter(cn);
			UpdateCharacterEquipItem(sld);
		}
	}
	if(CheckAttribute(pchar,"systemInfo.messages.Artefact"))
	{
		LaunchMessage(pchar.systemInfo.messages.Artefact);
		DeleteAttribute(pchar,"systemInfo.messages.Artefact");
	}
}

bool IsCharacterEquippedArtefact(ref rChar, string itemID)
{
	int 	iOfficer = -1;
	ref 	rItem, sld;
	string  sKind = "";
	
	if (IsMainCharacter(rChar)) // ГГ и его офицеры 
	{
		if(IsEquipCharacterByArtefact(pchar, itemID)) return true;
		rItem = ItemsFromID(itemID);
		if(CheckAttribute(rItem, "kind")) 
		{
			sKind = rItem.kind;
			if(sKind == "fighter")
			{
				for(int i = 1; i < 4; i++)
				{		
					iOfficer = GetOfficersIndex(pchar, i); 
					if(iOfficer != -1)
					{
						if(IsEquipCharacterByArtefact(&characters[iOfficer], itemID)) return true;						
					}
				}	
			}
			else
			{
				iOfficer = sti(pchar.Fellows.Passengers.(sKind));
				if(iOfficer != -1)
				{
					return IsEquipCharacterByArtefact(&characters[iOfficer], itemID);
				}
			}	
			return false;
		}	
		else
		{
			for (int io = 0; io < GetNotQuestPassengersQuantity(rChar); io++)
			{
				iOfficer = GetNotQuestPassenger(rChar, io);
				if(iOfficer != -1)
				{
					sld = GetCharacter(iOfficer);
					if(isOfficerInShip(sld, true))
					{
						if(IsEquipCharacterByArtefact(sld, itemID)) return true;
					}					
				}
			}
			return false;
		}	
	}
	// все прочие (компаньоны, враги и т.п.)
	return IsEquipCharacterByArtefact(rChar, itemID);
}

float isEquippedArtefactUse(ref rChar, string sItem, float fOff, float fOn)
{
	if(IsCharacterEquippedArtefact(rChar, sItem)) return fOn;	
	return fOff;
}

float isEquippedAmuletUse(ref rChar, string sItem, float fOff, float fOn)
{
	if(IsEquipCharacterByArtefact(rChar, sItem)) return fOn;	
	return fOff;
}

/// --> Ugeen 30.09.10  Новая комплексная репутация ГГ
int ChangeCharacterComplexReputationABS(ref chref, string repName, float incr)
{
	int curVal = COMPLEX_REPUTATION_NEUTRAL;
	if (CheckAttribute(chref,"reputation." + repName) ) curVal = stf(chref.reputation.(repName));

	if (curVal < COMPLEX_REPUTATION_NEUTRAL) incr = -incr;
	return ChangeCharacterComplexReputation(chref, repName, incr);
}

int ChangeCharacterComplexReputationToNeutral(ref chref, string repName, float incr)
{
	int curVal = COMPLEX_REPUTATION_NEUTRAL;
	if (CheckAttribute(chref,"reputation." + repName) ) curVal = stf(chref.reputation.(repName));
	
	if (curVal > COMPLEX_REPUTATION_NEUTRAL) incr = -incr;
	return ChangeCharacterComplexReputation(chref, repName, incr);
}

int ChangeCharacterComplexReputation(ref chref, string repName, float incr)
{
	string prevName, newName;
	string sReputation;
	
	if (CheckAttribute(chref, "GenQuest.ReputationNotChange")) return sti(chref.reputation.(repName)); 
	if(IsEquipCharacterByArtefact(pchar, "talisman15") && repName == "nobility") incr *= 2.0;
	float prevVal = COMPLEX_REPUTATION_NEUTRAL;
	if (CheckAttribute(chref,"reputation." + repName) )	prevVal = stf(chref.reputation.(repName));
	float newVal = prevVal + incr;
	if (newVal < COMPLEX_REPUTATION_MIN) newVal = COMPLEX_REPUTATION_MIN;
	if (newVal > COMPLEX_REPUTATION_MAX) newVal = COMPLEX_REPUTATION_MAX;
	chref.reputation.(repName) = newVal;
	if(!IsMainCharacter(chref)) return makeint(newVal);

	if(repName != "authority") // изменение авторитета не выводим
	{
		prevName 		= GetReputationComplexName(makeint(prevVal), repName);
		newName 		= GetReputationComplexName(makeint(newVal),  repName);
	
		switch (repName)
		{
			case "fame"		:
				sReputation = XI_ConvertString(newName) + " " + XI_ConvertString(GetReputationComplexName(sti(chref.reputation.nobility), "nobility"));
			break;

			case "nobility"	:
				sReputation = XI_ConvertString(GetReputationComplexName(sti(chref.reputation.fame), "fame")) + " " + XI_ConvertString(newName);
				if(IsEntity(&worldMap) || bSeaActive) 
				{
					if (prevName != newName)
					{
						if(incr > 0.0) notification(StringFromKey("characterUtilite_7"), "RepUp");
						if(incr < 0.0) notification(StringFromKey("characterUtilite_8"), "RepDown");
					}
				}
				else
				{
					if(incr > 0.0) notification(StringFromKey("characterUtilite_7"), "RepUp");
					if(incr < 0.0) notification(StringFromKey("characterUtilite_8"), "RepDown");
				}
			break;	
		}
				
		/* if (prevName != newName)
		{
			string outString = XI_ConvertString("Your reputation")+" ";
			outString += XI_ConvertString("changed");
			outString += " " + XI_ConvertString("to") + " " + sReputation;
			Log_SetStringToLog(outString);
		} */
	}	
	
	return makeint(newVal);
}
/// <-- Новая комплексная репутация ГГ

///  репутация ГГ 06/06/06 boal new concept -->
//изменить репутацию персонажа в зависимости от текущей репутации.
//минус для плохого это рост в плюс
int ChangeCharacterReputationABS(ref chref, float incr)
{
	int curVal = REPUTATION_NEUTRAL;
	if (CheckAttribute(chref,"reputation") ) curVal = stf(chref.reputation);

	if (curVal < REPUTATION_NEUTRAL) incr = -incr;
	return ChangeCharacterReputation(chref , incr);
}

// репутация стремится к нейтральной
int ChangeCharacterReputationToNeutral(ref chref, float incr)
{
	int curVal = REPUTATION_NEUTRAL;
	if (CheckAttribute(chref,"reputation") ) curVal = stf(chref.reputation);
	
	if (curVal > REPUTATION_NEUTRAL) incr = -incr;
	return ChangeCharacterReputation(chref , incr);
}

int ChangeCharacterReputation(ref chref, float incr)
{
	if (CheckAttribute(chref, "GenQuest.ReputationNotChange")) return sti(chref.reputation); //eddy. нужен флаг
	float prevVal = REPUTATION_NEUTRAL;
	if (CheckAttribute(chref,"reputation") )	prevVal = stf(chref.reputation);

	float newVal = prevVal + incr;
	if (newVal<REPUTATION_MIN) newVal = REPUTATION_MIN;
	if (newVal>REPUTATION_MAX) newVal = REPUTATION_MAX;
	chref.reputation = newVal;

	if( sti(chref.index) != GetMainCharacterIndex() ) return makeint(newVal);

	string prevName = GetReputationName(makeint(prevVal));
	string newName = GetReputationName(makeint(newVal));
	if (prevName!=newName)
	{
		string outString = XI_ConvertString("Your reputation")+" ";
		if (incr>0)	{outString+=XI_ConvertString("increase");}
		else	{outString+=XI_ConvertString("decrease");}
		outString += " "+XI_ConvertString("to")+" "+XI_ConvertString(newName);
		Log_SetStringToLog(outString);
	}

	return makeint(newVal);
}
//    ChangeCharacterNationReputation(chref, iType, incr);

void UpdateReputation()
{
	// благородство (бывшая репутация)
	if (sti(pchar.reputation.nobility) < (COMPLEX_REPUTATION_NEUTRAL - 10))  // плохиш
	{
		if(IsEquipCharacterByArtefact(pchar, "talisman15")) ChangeCharacterComplexReputation(pchar, "nobility", (MOD_SKILL_ENEMY_RATE / 25.0));
		else ChangeCharacterComplexReputation(pchar, "nobility", (MOD_SKILL_ENEMY_RATE / 50.0));
	}
	if (sti(pchar.reputation.nobility) > (COMPLEX_REPUTATION_NEUTRAL + 10))  // кибальчиш
	{
		if(IsEquipCharacterByArtefact(pchar, "talisman15")) ChangeCharacterComplexReputation(pchar, "nobility", (-MOD_SKILL_ENEMY_RATE / 12.5));
		else ChangeCharacterComplexReputation(pchar, "nobility", (-MOD_SKILL_ENEMY_RATE / 25.0));
	}
	
	//известность
	// belamour legendary edition Орден святого Людовика
	if(IsEquipTalisman9()) return;
	if(SandBoxMode) return;
	
	// известность не может расти сама по себе, только уменьшение
	if (sti(pchar.reputation.fame) > (COMPLEX_REPUTATION_NEUTRAL - 10))
	{
		ChangeCharacterComplexReputation(pchar, "fame", (-MOD_SKILL_ENEMY_RATE / 25.0));
	}
	//падает, но совсем медленно
	if (sti(pchar.reputation.fame) > (COMPLEX_REPUTATION_MIN + 19) && sti(pchar.reputation.fame) <= (COMPLEX_REPUTATION_NEUTRAL - 10))
	{
		ChangeCharacterComplexReputation(pchar, "fame", (-MOD_SKILL_ENEMY_RATE / 250.0));
	}
}

// метод вызывается ежедневно, уменьшает значение крайних репутаций - эффект забывания.
void UpdateFame()
{
	if (sti(pchar.reputation) < (REPUTATION_NEUTRAL - 10))  // плохиш
	{
		ChangeCharacterReputation(pchar, (MOD_SKILL_ENEMY_RATE / 40.0)); // медленнее
	}
	if (sti(pchar.reputation) > (REPUTATION_NEUTRAL + 10))  // кибальчиш
	{
		ChangeCharacterReputation(pchar, (-MOD_SKILL_ENEMY_RATE / 20.0));
	}
}
///  репутация ГГ 06/06/06 boal new concept <--

bool Character_IsAbordageEnable(ref rCharacter)
{
	if (CheckAttribute(rCharacter, "AlwaysFriend")) return false; // boal
	if (CheckAttribute(rCharacter, "Abordage.Enable")) { return sti(rCharacter.Abordage.Enable); }
	return true;
}

void Character_SetAbordageEnable(ref rCharacter, bool bEnable)
{
	rCharacter.Abordage.Enable = bEnable;
}

void Character_SetCompanionEnemyEnable(ref rCharacter, bool bEnable)
{
	rCharacter.CompanionEnemyEnable = bEnable;
}

void AddMsgToCharacter(ref chref, int nMsg)
{
	string msgName = "msg"+nMsg;
	bool bStartEvent = !CheckAttribute(chref,"MessageIcons."+msgName);
	chref.MessageIcons.(msgName).pic = nMsg;
	chref.MessageIcons.(msgName) = MSGICON_ACTIVE_TIME;
	if(bStartEvent) PostEvent("evnt_MsgIconTick",1000,"ll",nMsg,sti(chref.index));
}

void DelMsgFromCharacter(ref chref, int nMsg)
{
	DeleteAttribute(chref,"MessageIcons.msg"+nMsg);
}

void proc_MsgIconTick()
{
	int nMsg = GetEventData();
	int chrIdx = GetEventData();
	if(DialogRun!=0) {
		PostEvent("evnt_MsgIconTick",1000,"ll",nMsg,chrIdx);
		return;
	}
	ref chref = GetCharacter(chrIdx);
	string msgName = "msg"+nMsg;
	int nTime = 0;

	if( CheckAttribute(chref,"MessageIcons."+msgName) )
	{
		nTime = sti(chref.MessageIcons.(msgName));
		if(nTime>0)
		{
			chref.MessageIcons.(msgName) = nTime-1;
			PostEvent("evnt_MsgIconTick",1000,"ll",nMsg,chrIdx);
			return;
		}
		DelMsgFromCharacter(chref,nMsg);
	}
}
 // to_do
int GetCharacterReputation(aref chr, int iNation)
{
	int iVal = 0;
	switch (iNation)
	{
		case 0:
			iVal = sti(chr.reputation.england);
		break;
		
		case 1:
			iVal = sti(chr.reputation.france);
		break;
		
		case 2:
			iVal = sti(chr.reputation.spain);
		break;
		
		case 3:
			iVal = sti(chr.reputation.holland);
		break;
		
		case 4:
			iVal = sti(chr.reputation.pirate);
		break;
		
		case 5:
			iVal = sti(chr.reputation.smuggler);
		break;
		
		case 6:
			iVal = sti(chr.reputation.trader);
		break;
	}
	
	return iVal;
}

bool isPrisonedChar(aref chr)
{
	if(CheckAttribute(chr,"prisoned"))
	{
		if(sti(chr.prisoned) == 1)
		{
			return true;
		}
	}
	return false;
}

bool CheckForRank(aref chr, int iRank)
{
	if(CheckAttribute(chr, "rank"))
	{
		if(sti(chr.rank) >= iRank)
		{
			return true;
		}
	}
	return false;
}

/////////////////////////
string  Get_My_Cabin()
{
	return Pchar.SystemInfo.CabinType;
}

string  Get_My_Cabin_Pic()
{
    int  i;

    i = FindLocation(Pchar.SystemInfo.CabinType);
    if (i != -1)
    {
    	return   Locations[i].image;
    }
	return "";
}
bool isShipInside(string _id)
{
    bool   ret = false;

    if (_id == Get_My_Cabin() || _id == "My_Deck_Medium" || _id == "My_Campus" || _id == "My_Deck" || _id == "Deck_Near_Ship")
    {
        ret = true;
        if (CheckAttribute(pchar, "GenQuest.DestroyPirate") && CheckAttribute(pchar, "GenQuest.CaptainId") && pchar.GenQuest.CaptainId == "MQPirate")
	    {
	        if (!CheckQuestAttribute("Munity", "Deads")) ret = false;
	    }
    }

    return ret;
}
void  Set_My_Cabin() {
	int		n,i;
	string	sTemp, newCab;
	ref		rShip;

	int nShipType = GetCharacterShipType(pchar);
	if (nShipType == SHIP_NOTUSED) {
		newCab = "My_Cabin";
	}
	else 
	{
		rShip = GetRealShip(nShipType);
		newCab = "My_" + rShip.CabinType;  // превратим из каюты типа корабля
	}

	if (Pchar.SystemInfo.CabinType != newCab) {
		if (Pchar.SystemInfo.CabinType != "") {
			// переселить предметы
			ref		loc, locTo;
			aref	arFromBox;
			aref	curItem;
			aref	al;
			aref	boxTo;
			string	attr;

			loc		= &locations[FindLocation(Pchar.SystemInfo.CabinType)];
			locTo	= &locations[FindLocation(newCab)];
			
			string sat = "";
			string time;
			if (IsDay()) {
				time = "day";
			} else {
				time = "night";
			}
			
			if (CheckAttribute(locTo, "models." + time + ".locators")) {
				sat = "models." + time + ".locators";
			} else {
				if (CheckAttribute(locTo, "models.always.locators")) {
					sat = "models.always.locators";
				}
			}
			
			if (sat != "") {
				CreateEntity(locTo, "location");
				if(CheckAttribute(locTo, "filespath.models")) {		
					SendMessage(locTo, "ls", MSG_LOCATION_MODELSPATH, locTo.filespath.models);
				}
				LocLoadModel(locTo, sat, "");
				SendMessage(locTo, "l", MSG_LOCATION_UPDATELOCATORS);
			}
			
			// полная зачистка
			for (n = 1; n <= 4; n++) {
				sTemp = "box" + n;
				DeleteAttribute(locTo, sTemp + ".items");
				locTo.(sTemp).items = "";
				locTo.(sTemp) = Items_MakeTime(0, 0, 1, 2003);
				locTo.(sTemp).money = 0;
			}
			
			for (n = 1; n <= 4; n++) {
				sTemp = "box" + n;
				
				if (FindLocator(locTo.id, sTemp, &al, true)) {
					makearef(boxTo, locTo.(sTemp));
				} else {
					makearef(boxTo, locTo.box1);
				}
				
				if (CheckAttribute(loc, sTemp + ".money")) {
					boxTo.money = sti(boxTo.money) + sti(loc.(sTemp).money);
				}
				makearef(arFromBox, loc.(sTemp).items);
				for(i=0; i<GetAttributesNum(arFromBox); i++)
				{
					curItem = GetAttributeN(arFromBox, i);
					attr = GetAttributeName(curItem);
					if (attr != "") {
						if (!CheckAttribute(boxTo, "items." + attr)) {
							boxTo.items.(attr) = 0;
						}
						
						boxTo.items.(attr) = makeint(sti(boxTo.items.(attr)) + makeint(GetAttributeValue(curItem)));
					}
				}
				// del
				DeleteAttribute(loc, sTemp + ".items");
				loc.(sTemp).items = "";
				loc.(sTemp) = Items_MakeTime(0, 0, 1, 2003);
				loc.(sTemp).money = 0;
			}
			
			if (sat != "") {
				DeleteClass(locTo);
			}
		}
		Pchar.SystemInfo.CabinType = newCab;
		n = FindLocation("My_Deck");
		if (n != -1) {
			if (sti(rShip.Class) > 4) {
				Locations[n].reload.l1.go = Pchar.SystemInfo.CabinType;
				Locations[n].reload.l1.emerge = "reload1";
			} else {
				Locations[n].reload.l1.go = "My_Deck_Medium";
				Locations[n].reload.l1.emerge = "reload_hold";
			}
		}
		n = FindLocation(Pchar.SystemInfo.CabinType);
		if (n != -1) {
			if (sti(rShip.Class) > 4) {
				Locations[n].reload.l1.go = "My_Deck";
				Locations[n].reload.l1.emerge = "reload1";
			} else {
				Locations[n].reload.l1.go = "My_Deck_Medium";
				Locations[n].reload.l1.emerge = "reload_cabin";
			}
		}
		n = FindLocation("My_Deck_Medium");
		if (n != -1) {
			Locations[n].reload.l1.go = Pchar.SystemInfo.CabinType;
		}
	}
}

int CheckItemInBox(string _itemID, string _locationID, string _box) // Addon 2016-1 Jason подсчет указанных предметов в конкретном сундуке конкретной локации
{
	int Qty = 0; 
    string attr;
    ref loc = &locations[FindLocation(_locationID)];
	aref arBox, curItem;
	makearef(arBox, loc.(_box).items);
	
	for (int i=0; i<GetAttributesNum(arBox); i++)
    {
		curItem = GetAttributeN(arBox, i);
		attr = GetAttributeName(curItem);
		if (attr == _itemID) Qty += makeint(GetAttributeValue(curItem));
	}
	return Qty;
}

int CheckItemMyCabin(string _itemID)
{
	int     n,i;	
	int		Qty = 0; 
    string  sTemp;
    ref     loc;
	aref    arBox;
    aref    curItem;
	string  attr;

	int nShipType = GetCharacterShipType(pchar);
	if (nShipType == SHIP_NOTUSED)	return 0;
	
	if (Pchar.SystemInfo.CabinType != "")
	{
		loc = &locations[FindLocation(Pchar.SystemInfo.CabinType)]; 
		for (n = 1; n <= 4; n++)
	    {
			sTemp = "box" + n;			
			makearef(arBox, loc.(sTemp).items);
            for(i=0; i<GetAttributesNum(arBox); i++)
            {
                curItem = GetAttributeN(arBox, i);
                attr = GetAttributeName(curItem);
                if (attr == _itemID)
                {
                    Qty += makeint(GetAttributeValue(curItem));
                }
            }			
		}
	}
	loc = &locations[FindLocation("My_Deck")];
	for (n = 1; n <= 4; n++)
    {
		sTemp = "box" + n;
		makearef(arBox, loc.(sTemp).items);
        for(i=0; i<GetAttributesNum(arBox); i++)
        {
            curItem = GetAttributeN(arBox, i);
            attr = GetAttributeName(curItem);
            if (attr == _itemID)
            {
                Qty += makeint(GetAttributeValue(curItem));
            }
        }					
	}
	return Qty;
}

int GetItemMyCabin(string _itemID, int _qty)
{
	int     n,i;	
	int		Qty = 0; 
	int 	rQty = 0;	
    string  sTemp;
    ref     loc;
	aref    arBox;
    aref    curItem;
	string  attr;
	
	int nShipType = GetCharacterShipType(pchar);
	if (nShipType == SHIP_NOTUSED)	return;

	if (Pchar.SystemInfo.CabinType != "")
	{
		loc = &locations[FindLocation(Pchar.SystemInfo.CabinType)]; 
		for (n = 1; n <= 4; n++)
	    {	
			sTemp = "box" + n;			
			makearef(arBox, loc.(sTemp).items);
            for(i=0; i<GetAttributesNum(arBox); i++)
            {
                curItem = GetAttributeN(arBox, i);
                attr = GetAttributeName(curItem);
                if (attr == _itemID)
				{
					Qty = makeint(GetAttributeValue(curItem));
					if(Qty > 0)
					{
						if(Qty > _qty) 
						{
							loc.(sTemp).items.(attr) = makeint(sti(loc.(sTemp).items.(attr)) - _qty);
							rQty += Qty;
							return rQty;
						}
						else
						{
							DeleteAttribute(loc, sTemp + ".items." + attr);
							_qty -= Qty;
							rQty += Qty;
						}		
					}
				}
			}
		}
	}
	loc = &locations[FindLocation("My_Deck")];
	for (n = 1; n <= 4; n++)
    {
		sTemp = "box" + n;	
		makearef(arBox, loc.(sTemp).items);
        for(i=0; i<GetAttributesNum(arBox); i++)
        {
            curItem = GetAttributeN(arBox, i);
            attr = GetAttributeName(curItem);
            if (attr == _itemID)
            {		
				Qty = makeint(GetAttributeValue(curItem));
				if(Qty > 0)
				{
					if(Qty > _qty) 
					{
						loc.(sTemp).items.(attr) = makeint(sti(loc.(sTemp).items.(attr)) - _qty);
						rQty += Qty;
						return rQty;
					}
					else
					{
						DeleteAttribute(loc, sTemp + ".items." + attr);
						_qty -= Qty;
						rQty += Qty;
					}		
				}				
			}
		}	
	}
	return rQty;
} 
// belamour положить предмет в корабельный сундук
void PutItemMyBox(string _Box, string _itemID, int _qty)
{
	int nShipType = GetCharacterShipType(pchar);
	if (nShipType == SHIP_NOTUSED)	return;
	if (Pchar.SystemInfo.CabinType != "")
	{
		ref loc = &locations[FindLocation(Pchar.SystemInfo.CabinType)]; 
		if(CheckAttribute(loc,_Box+".items."+_itemID))
		{
			loc.(_Box).items.(_itemID) = makeint(sti(loc.(_Box).items.(_itemID)) + _qty);
		}
		else
		{
			loc.(_Box).items.(_itemID) = _qty;
		}
	}
} 

// belamour количество предмета в конкретном корабельном сундуке
int CheckItemMyBox(string _Box, string _itemID)
{
	int     i;	
	int		Qty = 0; 
    ref     loc;
	aref    arBox;
    aref    curItem;
	string  attr;

	int nShipType = GetCharacterShipType(pchar);
	if (nShipType == SHIP_NOTUSED)	return 0;
	if (Pchar.SystemInfo.CabinType != "")
	{
		loc = &locations[FindLocation(Pchar.SystemInfo.CabinType)]; 			
		makearef(arBox, loc.(_Box).items);
		for(i=0; i<GetAttributesNum(arBox); i++)
		{
			curItem = GetAttributeN(arBox, i);
			attr = GetAttributeName(curItem);
			if (attr == _itemID)
			{
				Qty += makeint(GetAttributeValue(curItem));
			}
		}			
	}
	return Qty;
}

// belamour взять предмет из конкретного корабельного сундука
int GetItemMyBox(string _Box, string _itemID, int _qty)
{
	int     i;	
	int		Qty = 0; 
	int 	rQty = 0;	
    ref     loc;
	aref    arBox;
    aref    curItem;
	string  attr;
	
	int nShipType = GetCharacterShipType(pchar);
	if (nShipType == SHIP_NOTUSED)	return;
	if (Pchar.SystemInfo.CabinType != "")
	{
		loc = &locations[FindLocation(Pchar.SystemInfo.CabinType)]; 			
		makearef(arBox, loc.(_Box).items);
		for(i=0; i<GetAttributesNum(arBox); i++)
		{
			curItem = GetAttributeN(arBox, i);
			attr = GetAttributeName(curItem);
			if (attr == _itemID)
			{
				Qty = makeint(GetAttributeValue(curItem));
				if(Qty > 0)
				{
					if(Qty > _qty) 
					{
						loc.(_Box).items.(attr) = makeint(sti(loc.(_Box).items.(attr)) - _qty);
						rQty += Qty;
						return rQty;
					}
					else
					{
						DeleteAttribute(loc, _Box + ".items." + attr);
						_qty -= Qty;
						rQty += Qty;
					}		
				}
			}
		}
		
	}
	return rQty;
}

// belamour общая проверка количества дублонов у ГГ и в каюте
int PCharDublonsTotal()
{
	int	Qty = 0; 
	Qty = GetCharacterItem(pchar,"gold_dublon") + CheckItemMyCabin("gold_dublon");
	return Qty;
}
// belamour взять дублоны сначала у ГГ, а потом в каюте 
void RemoveDublonsFromPCharTotal(int _Dublons)
{
	int	Qty = _Dublons; 
	if(Qty<1) return;
	if(GetCharacterItem(pchar,"gold_dublon") + CheckItemMyCabin("gold_dublon") < Qty) return;
	int Total = Qty;
	int cq = GetCharacterItem(pchar,"gold_dublon");
	int bq = CheckItemMyCabin("gold_dublon");
	if(cq > 0) // есть дублоны на руках
	{
		if(cq >= Qty) // можем оплатить полную сумму
		{
			//Log_Info("Потрачено "+FindRussianDublonString(Qty));
			TakeNItems(pchar,"gold_dublon", -Qty));
		}
		else // на руках часть дублонов
		{
			Total -= cq;
			TakeNItems(pchar,"gold_dublon", -cq));
			//Log_Info("Потрачено "+FindRussianDublonString(cq));
			GetItemMyCabin("gold_dublon", Total);
			//Log_Info("Взято из каюты "+FindRussianDublonString(Total));
		}
	}
	else
	{
		GetItemMyCabin("gold_dublon", Qty);
		//Log_Info("Взято из каюты "+FindRussianDublonString(Qty));
	}
	//"Потрачено "+_Dublons+" дублонов"
	notification(StringFromKey("characterUtilite_9", _Dublons), "Dubloon");
	PlayStereoSound("Ambient\SHOP\dubloons.wav");
}

int PCharItemsTotal(string _itemID)
{
	int	Qty = 0; 
	Qty = GetCharacterItem(pchar,_itemID) + CheckItemMyCabin(_itemID);
	return Qty;
}

void RemoveItemsFromPCharTotal(string _itemID, int _qty)
{
	int	Qty = _qty; 
	if(Qty<1) return;
	if(GetCharacterItem(pchar,_itemID) + CheckItemMyCabin(_itemID) < Qty) return;
	int Total = Qty;
	int cq = GetCharacterItem(pchar,_itemID);
	int bq = CheckItemMyCabin(_itemID);
	if(cq > 0)
	{
		if(cq >= Qty)
		{
			TakeNItems(pchar,_itemID, -Qty));
		}
		else
		{
			Total -= cq;
			TakeNItems(pchar,_itemID, -cq));
			GetItemMyCabin(_itemID, Total);
		}
	}
	else
	{
		GetItemMyCabin(_itemID, Qty);
	}
}

// есть ли патент
bool isMainCharacterPatented()
{
    if(CheckAttribute(pchar, "EquipedPatentId") && CheckCharacterItem(pchar, Items[sti(pchar.EquipedPatentId)].id))
    {
        return true;
    }
    return false;
}

int GetPatentNation()
{
    if(CheckAttribute(pchar, "EquipedPatentId") && CheckCharacterItem(pchar, Items[sti(pchar.EquipedPatentId)].id))
    {
        return sti(Items[sti(pchar.EquipedPatentId)].Nation);
    }
    return -1;
}

// звания
void AddTitleNextRate(int nation, float num)
{
    if (isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].Nation) == nation)
    {
        Items[sti(pchar.EquipedPatentId)].TitulCurNext = stf(Items[sti(pchar.EquipedPatentId)].TitulCurNext) + num;
        if (stf(Items[sti(pchar.EquipedPatentId)].TitulCurNext) < 0) Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
        if (stf(Items[sti(pchar.EquipedPatentId)].TitulCurNext) > MAX_TITLENEXTRATE) Items[sti(pchar.EquipedPatentId)].TitulCurNext = MAX_TITLENEXTRATE;
        Log_TestInfo("TitleCurNext = " + stf(Items[sti(pchar.EquipedPatentId)].TitulCurNext));
    }
}
// присвоить следующее?
bool isReadyToNextTitle(int nation)
{
    bool    ret = false;

    if (isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].Nation) == nation)
    {
        if (sti(Items[sti(pchar.EquipedPatentId)].TitulCur) < MAX_TITLE && (stf(Items[sti(pchar.EquipedPatentId)].TitulCurNext) / sti(Items[sti(pchar.EquipedPatentId)].TitulCur)) >= 3)
        {
            ret = true;
        }
    }

    return ret;
}

// belamour legendary edition полная экипировка офицера (патент+мундир)
bool IsOfficerFullEquip()
{
	for(int i=1; i<4; i++)
	{
		if(isMainCharacterPatented() && GetCharacterEquipSuitID(pchar) == "suit"+i) return true;
	}
	return false;
}

// belamour одет ли мундир
bool IsUniformEquip()
{
	for(int i=1; i<4; i++)
	{
		if(GetCharacterEquipSuitID(pchar) == "suit"+i) return true;
	}
	if(GetCharacterEquipSuitID(pchar) == "suit5") return true;
	
	return false;
}

// belamour проверка на действие ордена Людовика
bool IsEquipTalisman9()
{
	if(IsEquipCharacterByArtefact(pchar, "talisman9") || GetCharacterEquipSuitID(pchar) == "suit5") return true;
	return false;
}

// проверка на допустимость игры в карты и кости -->
float GetCardsGameCheckRate()
{
	float k;
	float   fWin, fLose;


	fWin  = makefloat(Statistic_AddValue(Pchar, "GameCards_Win", 0));
    fLose = makefloat(Statistic_AddValue(Pchar, "GameCards_Lose", 0));
    if (fLose < 1) fLose = 1.0;

    k = fWin / fLose;

	return k;
}
bool CheckCardsGameSmallRate()
{
	bool    ret = true;

    if (GetCardsGameCheckRate() >= 15)
    {
        ret = false;
    }
	return ret;
}

bool CheckCardsGameBigRate()
{
	bool    ret = true;

    if (GetCardsGameCheckRate() >= 7)
    {
        ret = false;
    }
	return ret;
}

float GetDiceGameCheckRate()
{
	float k;
	float   fWin, fLose;


	fWin  = makefloat(Statistic_AddValue(Pchar, "GameDice_Win", 0));
    fLose = makefloat(Statistic_AddValue(Pchar, "GameDice_Lose", 0));
    if (fLose < 1) fLose = 1.0;

    k = fWin / fLose;

	return k;
}
bool CheckDiceGameSmallRate()
{
	bool    ret = true;

    if (GetDiceGameCheckRate() >= 15)
    {
        ret = false;
    }
	return ret;
}

bool CheckDiceGameBigRate()
{
	bool    ret = true;

    if (GetDiceGameCheckRate() >= 7)
    {
        ret = false;
    }
	return ret;
}
// проверка на допустимость игры в карты и кости <--

// boal 08.01.05 -->
int GetPartyCrewQuantity(ref _refCharacter, bool _removable) // true - если только наши
{
	int cn;
	int sumCrew = 0;
	ref officer;

	for(int i=0; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(_refCharacter,i);
		if (cn!=-1)
		{
            officer = GetCharacter(cn);
            if (!GetRemovable(officer) && _removable) continue; // только наши + ГГ
			sumCrew = sumCrew + GetCrewQuantity(officer);
		}
	}
	return sumCrew;
}

int GetTroopersCrewQuantity(ref _refCharacter)
{
	int cn, j;
	int compCrew;
	int sumCrew = 0;
	ref officer;

 	if (CheckOfficersPerk(_refCharacter, "Troopers"))
    {
        Log_TestInfo("-= GetTroopersCrewQuantit =-");
        for (j=1; j<COMPANION_MAX; j++) // ГГ отдельно
        {
	        cn = GetCompanionIndex(_refCharacter, j);
	        if (cn>0)
	        {
		        officer = GetCharacter(cn);
		        if (!GetRemovable(officer)) continue;

		        compCrew = GetCrewQuantity(officer) - GetMinCrewQuantity(officer);
		        if (compCrew < 0)
		        {
		           compCrew = 0;
		        }
				compCrew = GetWeaponCrew(officer, compCrew);  // без оружия просто не идут (как половина команды учёт)

                if (compCrew > 0)
                {
	                RemoveCharacterGoodsSelf(officer, GOOD_WEAPON, makeint(compCrew/2 + 0.5));
	                SetCrewQuantity(officer, GetCrewQuantity(officer) - compCrew);
                	//Log_SetStringToLog("Десант корабля " + officer.Ship.Name + " составляет " + compCrew + " человек.");
                	Log_SetStringToLog(StringFromKey("characterUtilite_10", officer.Ship.Name, compCrew));
                	AddCharacterExpToSkill(officer, "Defence", makeint(compCrew / 2 + 0.5)); //качаем защиту
                	AddCharacterExpToSkill(officer, "Grappling", makeint(compCrew / 2 + 0.5));
                	sumCrew = sumCrew + compCrew;
                }
		    }
		}
    }
    // квестовый перк
    if (CheckAttribute(_refCharacter, "TempPerks.QuestTroopers"))
	{
        Log_TestInfo("-= QuestTroopers =-");
		for (j=1; j<COMPANION_MAX; j++) // ГГ отдельно
        {
	        cn = GetCompanionIndex(_refCharacter, j);
	        if (cn>0)
	        {
		        officer = GetCharacter(cn);
		        if (GetRemovable(officer)) continue;// токо квесты

		        compCrew = GetCrewQuantity(officer);
		        if (compCrew < 0)
		        {
		           compCrew = 0;
		        }
		        //Log_SetStringToLog("Десант корабля " + officer.Ship.Name + " составляет " + compCrew + " человек.");
		        Log_SetStringToLog(StringFromKey("characterUtilite_10", officer.Ship.Name, compCrew));
                if (compCrew > 0)
                {
                	sumCrew = sumCrew + compCrew;
                }
		    }
		}
		DeleteAttribute(_refCharacter, "TempPerks.QuestTroopers");
	}
	return sumCrew;
}
// распределить перегруз экипажа по кораблям ГГ
void AddTroopersCrewToOther(ref _refCharacter)
{
	int cn, j;
	int compCrew;
	int sumCrew = 0;
	ref officer;

    compCrew = 0;
    if (GetMaxCrewQuantity(_refCharacter) < GetCrewQuantity(_refCharacter))
    {
        compCrew = GetCrewQuantity(_refCharacter) - GetMaxCrewQuantity(_refCharacter);
        SetCrewQuantity(_refCharacter, GetMaxCrewQuantity(_refCharacter));
    }
	if (compCrew > 0)
	{
	    for (j=1; j<COMPANION_MAX; j++) // ГГ отдельно
	    {
	        cn = GetCompanionIndex(_refCharacter, j);
	        if (cn>0)
	        {
		        officer = GetCharacter(cn);
		        if (!GetRemovable(officer)) continue;

                if (GetMaxCrewQuantity(officer) >= (GetCrewQuantity(officer) + compCrew))
                {
                    SetCrewQuantity(officer, (GetCrewQuantity(officer) + compCrew));
                    break;  // все влезли
                }
                else
                {
                    compCrew = (GetCrewQuantity(officer) + compCrew) - GetMaxCrewQuantity(officer);
                    SetCrewQuantity(officer, GetMaxCrewQuantity(officer));
                }
		    }
		}
	}
}
// boal 21.01.2004
int GetWeaponCrew(ref _char, int _crew)
{
    int weaponOnBoard = GetCargoGoods(_char, GOOD_WEAPON);
	if (_crew > weaponOnBoard)
	{
	    _crew = weaponOnBoard + makeint(( _crew - weaponOnBoard)/2.0 + 0.5);
	}
	return _crew;
}
// boal 08.01.05 <--

// ========================= eddy пока сюда перенесу
int GenerateNationTrade(int nation)
{
	int i = -1;
	// boal -->
	int   j = 0;
	bool  ok;

	while (i == -1 && j < 10)
	{
		i = rand(MAX_NATIONS - 1);
		ok = (GetNationRelation2MainCharacter(i) == RELATION_ENEMY) && (i != PIRATE); //fix 12.05.05
		if (ok || GetNationRelation(nation, i) == RELATION_ENEMY) // boal было nation == i || i == PIRATE- но сами себе можем!!!
		{
			i = -1;
		}
		j++;
	}
    // boal <--
	return i;
}

int RecalculateSquadronCargoLoad(ref _refCharacter)
{
	int i,cn;
	int retVal = RecalculateCargoLoad(_refCharacter);

	for(i=1; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(_refCharacter,i);
		if(cn!=-1)
		{
			retVal = retVal + RecalculateCargoLoad(&Characters[cn]);
		}
	}
	return retVal;
}

// из Боф_реакшн
void LoansMoneyAvenger(ref _loan)
{
    Log_SetStringToLog(StringFromKey("characterUtilite_11"));

    LoansMoneyAvengerAmount(_loan, 25);
}

void LoansMoneyAvengerAmount(ref _loan, int _sum)
{
    string typeHunter = NationShortName(sti(_loan.nation)) + "hunter";
    ChangeCharacterComplexReputation(Pchar,"nobility", -20);
    OfficersReaction("bad");
    if ( _loan.nation == PIRATE)
    {
        typeHunter = "enghunter";  // за пиратов мстит англия
    }
    ChangeCharacterHunterScore(PChar, typeHunter, _sum);
}
//homo возращает нпс стоящего на локаторе
int GetCharacterbyLocation(string location, string group, string locator)
{
    ref sld;
    for(int i=0;i<MAX_CHARACTERS;i++)
	{
        sld = &characters[i];
        if (sld.location == location && sld.location.group == group && sld.location.locator == locator) return i;
	}
	return -1;
}

// Warship -->
// Сделать ГГ мушкетером или обычным фехтовальщиком
bool SetMainCharacterToMushketer(string sMushket, bool _ToMushketer) // если _ToMushketer == true, значит делаем мушкетером, иначе - делаем ГГ фехтовальщиком
{
	int iItem;
	string sLastGun = "";
	
	if(_ToMushketer && sMushket != "") // Делаем ГГ мушкетером
	{
		iItem = GetItemIndex(sMushket);
		if(iItem == -1) return false;
		EquipCharacterByItem(PChar, sMushket); // Экипируем мушкет
	}
	else // Делаем ГГ обычным фехтовальщиком
	{
		RemoveCharacterEquip(PChar, MUSKET_ITEM_TYPE); // Снимим мушкет
	}
	
	return true;
}

// Можно-ли экипировать мушкет в локации?
bool CanEquipMushketOnLocation(string LocationID)
{
	int iLocation = FindLocation(LocationID);
	if(iLocation == -1) return false;
	
	/* if(HasSubStr(LocationID, "Tavern")) // В таверне нельзя
	{
		return false;
	} */
	
	if(!IsPCharHaveMushketerModel())
	{
		return false;
	}
	
	return true;
}

// Есть ли для нашего ГГ мушкетерская модель?
bool IsPCharHaveMushketerModel()
{
	String sModel = PChar.Model;
	
	if(	HasSubStr(sModel, "Diego") 	|| 
		HasSubStr(sModel, "Willy") 	|| 
		HasSubStr(sModel, "Sharle") || 
		HasSubStr(sModel, "Longway") || 
		HasSubStr(sModel, "Port"))
	{
		return true;
	}
	
	return false;
}

// Создадим клона персонажа. Корабль не копируется
int CreateCharacterClone(ref Character, int iLifeDay)
{
	int iTemp = NPC_GeneratePhantomCharacter("citizen", sti(Character.Nation), MAN, iLifeDay);
	if(iTemp != -1)
	{
		ref rCloneChar = &Characters[iTemp];
		ChangeAttributesFromCharacter(rCloneChar, Character, true);
	}
	
	return iTemp;
}

// Получим ID надетой  кирасы или одежды
String GetCharacterEquipSuitID(ref rChar)
{
	String sItem = GetCharacterEquipByGroup(rChar, CIRASS_ITEM_TYPE);
	
	if(sItem == "") return INVALID_SUIT;
	return sItem;
}
// <-- Warship
// --> ugeen   16.02.09

void EquipCharacterByAtlas(ref chref)
{
	string groupID = MAPS_ITEM_TYPE;
	ref rLoc = ItemsFromID("MapsAtlas");
	chref.equip.(groupID) = rLoc.id;
}

// проверим наличие атласа и карты в нём
bool CheckMapForEquipped(ref refCh, string itemID)
{
	int   idLngFile;
	ref   arItem; 	 		 

	arItem = ItemsFromID(itemID);
	idLngFile = LanguageOpenFile("ItemsDescribe.txt");	
	
	if(sti(refCh.index) == GetMainCharacterIndex() && CheckCharacterItem(refCh, arItem.id))	
	{	
		if(!CheckCharacterItem(refCh, "MapsAtlas")) { // тривиальная проверка на наличие атласа - если его нет,  то получите и распишитесь
			GiveItem2Character(refCh, "MapsAtlas");
			EquipCharacterByAtlas(refCh);
		}	
		if(!IsEquipCharacterByMap(refCh, itemID)) { // проверяем, экипирован ли ГГ  этой картой
			EquipCharacterByItem(refCh, itemID); 			
			//Log_SetStringToLog(LanguageConvertString(idLngFile, arItem.name) +" добавлена в атлас");
			//notification(LanguageConvertString(idLngFile, arItem.name) +" в атласе!", "MapsAtlas");
			notification(StringFromKey("characterUtilite_12", LanguageConvertString(idLngFile, arItem.name)), "MapsAtlas");
			arItem = ItemsFromID("MapsAtlas");
			arItem.Weight = GetEquippedItemsWeight(refCh, MAPS_ITEM_TYPE);						
		}
		else return false;
	}
	
	LanguageCloseFile(idLngFile);		
	return true;
}

// проверка - есть ли новые карты для включения в атлас
void RefreshEquippedMaps(ref chref)
{
	int 	i;
	string  itemID, groupID;
    ref     itm;
	
	for (i=0; i<TOTAL_ITEMS; i++)
	{	
		makeref(itm,Items[i]);
		if(CheckAttribute(itm, "ID") && CheckAttribute(itm, "groupID"))
		{
			itemID = itm.id;
			groupID = itm.groupID;
			if(groupID == MAPS_ITEM_TYPE && itm.mapType == "")
			{
				CheckMapForEquipped(chref, itemID);
			}
		}		
	}
}

void StoreEquippedMaps(ref refCh)
{
    aref arItems;
	string  sName, groupID;
	ref rLoc;
	
	if( CheckAttribute( refCh, "Stored.Maps") ) DeleteAttribute( refCh, "Stored.Maps" );
	makearef(arItems, refCh.items);
    int	Qty = GetAttributesNum(arItems);
	
	for (int a = 0; a < Qty; a++)
    {
        sName = GetAttributeName(GetAttributeN(arItems, a));
		rLoc = ItemsFromID(sName);
		if(CheckAttribute(rLoc, "GroupID"))
		{
			groupID = rLoc.groupID;
			if(groupID == MAPS_ITEM_TYPE)
			{
				if(IsEquipCharacterByMap(refCh, rLoc.id))  
				// проверяем, экипирован ли ГГ  этой картой
				{
					refCh.Stored.Maps.(sName) = refCh.items.(sName);
				}
			}	
		}	
    }
}

void RestoreEquippedMaps(ref refCh)
{
    aref arItems;
	string sName;
	
	if( !CheckAttribute( refCh, "Stored.Maps") ) return;
	
	makearef(arItems, refCh.Stored.Maps);
    int Qty = GetAttributesNum(arItems);
    for (int a = 0; a < Qty; a++)
    {
        sName = GetAttributeName(GetAttributeN(arItems, a));
		TakeNItems(refCh, sName, 1);
    }
	DeleteAttribute(refCh, "Stored.Maps");
	RefreshEquippedMaps(refCh);
}
// <-- ugeen

void OfficersHold()
{
	int idx;
	for(int i=1; i<4; i++)
	{
		idx = GetOfficersIndex(PChar,i);
		if (idx != -1) {
			ref offchar = GetCharacter(idx)
			SetCharacterTask_Stay(offchar);
		}
	}
}

void OfficersFollow()
{
	int idx;
	for(int i=1; i<4; i++)
	{
		idx = GetOfficersIndex(PChar,i);
		if (idx != -1) {
			ref offchar = GetCharacter(idx)
			LAi_tmpl_SetFollow(offchar, GetMainCharacter(), -1.0);
		}
	}
}

void OfficersCharge()
{
	int idx;
	for(int i=1; i<4; i++)
	{
		idx = GetOfficersIndex(PChar,i);
		if (idx != -1) 
		{
			ref offchar = GetCharacter(idx)
			if(!LAi_CheckFightMode(offchar))
			{
				LAi_tmpl_SetFollow(offchar, GetMainCharacter(), -1.0);
			}
		}
	}
}

float ChangeIndianRelation(float _val) // Jason: репутация у индейцев
{
	pchar.questTemp.Indian.relation = stf(pchar.questTemp.Indian.relation) + _val;
	if (stf(pchar.questTemp.Indian.relation) > 100.0) pchar.questTemp.Indian.relation = 100.0;
	if (stf(pchar.questTemp.Indian.relation) < 0) pchar.questTemp.Indian.relation = 0;
	//log_testInfo("Отношение индейцев изменилось и равно "+stf(pchar.questTemp.Indian.relation)+" единицам");
	if (_val<0)
	{
		notification(StringFromKey("characterUtilite_13")+stf(pchar.questTemp.Indian.relation)+")", "Indians");
	}
	if (_val>0)
	{
		notification(StringFromKey("characterUtilite_14")+stf(pchar.questTemp.Indian.relation)+")", "Indians");
	}
	if(!GetAchievement("ach_CL_140") && stf(pchar.questTemp.Indian.relation) >= 70.0) Achievment_Set("ach_CL_140");
	
	return stf(pchar.questTemp.Indian.relation);
}

float GetCrewPercent(ref chr) {
	return 100.0 * GetCrewQuantity(chr) / GetMaxCrewQuantity(chr);
}

//Пользуется ли персонаж мушкетом в данный момент?
bool CharUseMusket(ref rChar)
{
	//Либо это чистый мушкетёр на старой анимации, либо универсал в мушкетном режиме
	if(GetCharacterAnimation(rChar) == "mushketer" || LAi_CheckFightMode(rChar) == 2) return true;
	return false;
}

// Приоритетный режим 0-сабля, 1-мушкет
bool MusketPriority(ref rChar)
{
	if(!IsMusketer(rChar)) return false;
	if(GetCharacterEquipByGroup(rChar, MUSKET_ITEM_TYPE) == "") return false;
	
	if(CheckAttribute(rChar,"PriorityMode") && sti(rChar.PriorityMode) == 2) return true;
	
	return false;
}

//Есть ли у персонажа мушкет?
bool IsMusketer(ref rChar)
{
	return CheckAttribute(rChar, "equip.musket");
}

//Получить анимацию персонажа
string GetCharacterAnimation(ref rChar)
{
	return rChar.model.animation;
}

//Установить модель и анимацию персонажу
void SetCharacterModelAndAnimation(ref rChar, string sModel, string sAnimation)
{
	rChar.model = sModel;
	rChar.model.animation = sAnimation;
	SetNewModelToChar(rChar);
}

//Установить модель персонажу
void SetCharacterModel(ref rChar, string sModel)
{
	rChar.model = sModel;
	SetNewModelToChar(rChar);
}

//Установить анимацию персонажу
void SetCharacterAnimation(ref rChar, string sAnimation)
{
	rChar.model.animation = sAnimation;
	SetNewModelToChar(rChar);
}

//Получить название текущей анимации персонажа
string GetCharCurAni(ref chr)
{
	string sAniCaseName;
	SendMessage(chr, "le", MSG_CHARACTER_GETCURANIMATION, &sAniCaseName);
	return sAniCaseName;
}
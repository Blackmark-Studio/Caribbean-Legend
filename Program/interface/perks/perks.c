
#event_handler("evntChrPerkDelay","procChrPerkDelay");

object ChrPerksList;

extern void extrnInitPerks();

void InitPerks()
{
	if( LoadSegment("interface\perks\perks_init.c") )
	{
		extrnInitPerks();
		UnloadSegment("interface\perks\perks_init.c");
	}
}

bool CheckCharacterPerk(ref chref, string perkName)
{
	if( CheckAttribute(chref,"perks.list."+perkName) ) return true;
	return false;
}

bool SetCharacterPerk(ref chref, string perkName)
{
	chref.perks.list.(perkName) = true;
	// разовые применения при назначении -->
	switch (perkName)
	{
		// belamour legendary edition дополнительные бонусы -->
		case "HPPlus":
			LAi_SetHP(chref, LAi_GetCharacterHP(chref) + sti(chref.rank), LAi_GetCharacterMaxHP(chref) + sti(chref.rank));
			if(CheckAttribute(chref, "chr_ai.hp_max_back"))
			{
				chref.chr_ai.hp_max_back = stf(chref.chr_ai.hp_max_back) + stf(chref.rank);
			}
			return true; // нужен рефрешь	
		break;
		
		case "Medic":
			LAi_SetHP(chref, LAi_GetCharacterHP(chref) + 40, LAi_GetCharacterMaxHP(chref) + 40);
			if(CheckAttribute(chref, "chr_ai.hp_max_back"))
			{
				chref.chr_ai.hp_max_back = stf(chref.chr_ai.hp_max_back) + 40.0;
			}
			return true; // нужен рефрешь	
		break;
		
		case "EnergyPlus":
			chref.PerkValue.EnergyPlus = sti(chref.rank);
			return true; // нужен рефрешь		
		break; 
		// <--
		case "Grus":
			return true; // нужен рефрешь
		break;
	}
	// разовые применения при назначении <--
	return false; // нужен рефрешь
}

void DelCharacterPerk(ref chref, string perkName)
{
	if(CheckAttribute(chref,"perks.list."+perkName))
	{
		DeleteAttribute(chref,"perks.list."+perkName);
	}
}

void ActivateCharacterPerk(ref chref, string perkName)
{
	if( !CheckAttribute(&ChrPerksList,"list."+perkName) )
	{
		trace("Invalid perk name - " + perkName);
		return;
	}

	int timeDelay = 0;
	int timeDuration = 0;

	if( CheckAttribute(&ChrPerksList,"list."+perkName+".TimeDuration") )
	{	timeDelay = sti(ChrPerksList.list.(perkName).TimeDuration);
		timeDuration = timeDelay;
	}
	if( CheckAttribute(&ChrPerksList,"list."+perkName+".TimeDelay") )
	{	timeDelay = sti(ChrPerksList.list.(perkName).TimeDelay);
		if(timeDuration<=0)	{timeDuration=timeDelay;}
	}
    // boal fix
    // иначе после применения давался ГГ
	
    int cn;
    if (!CheckCharacterPerk(chref, perkName))
    {

        cn = GetOfficersPerkUsingIdx(chref, perkName);
        if (cn != -1)
        chref = GetCharacter(cn);
    }
    // <--
	chref.perks.list.(perkName).delay = timeDelay;
	chref.perks.list.(perkName).active = timeDuration;

	//if(sti(chref.index) == nMainCharacterIndex)
	if (sti(chref.index) == nMainCharacterIndex || isOfficerInShip(chref, false)) // наследие перка от офа boal 30.06.06
	{
		AddPerkToActiveList(perkName);
	}

	if(timeDelay>0) PostEvent("evntChrPerkDelay",1000,"sl",perkName,sti(chref.index));
	Event("eSwitchPerks","l",sti(chref.index));
	// fix boal всегда для ГГ
	Event("eSwitchPerks","l", GetMainCharacterIndex());
}

bool GetCharacterPerkUsing(ref chref, string perkName)
{   // можно ли пользовать умение (задержки нет)
	if( !CheckAttribute(chref,"perks.list."+perkName) ) return false;
	if( CheckAttribute(chref,"perks.list."+perkName+".delay") ) return false;
	return true;
}

bool GetOfficersPerkUsing(ref chref, string perkName)
{ // boal препишем внутрянку под новых офов, че в к3 не было? не ведаю.
	string  sOfficerType;	
	ref   offc;	   
	bool  ok = false; // boal fix 25.03.05 проверка на запрет
	bool  okDelay = true;
	int   cn;
	if (GetCharacterPerkUsing(chref, perkName)) {return true;} // босс отдельно
	/* if (GetCharacterEquipByGroup(pchar, HAT_ITEM_TYPE) == "hat5" && IsCompanion(chref) && chref.id != pchar.id)
	{
		if(CheckAttribute(&ChrPerksList, "list."+perkName+".BaseType") && ChrPerksList.list.(perkName).BaseType == "ship")
		{
			if(GetCharacterPerkUsing(pchar, perkName)) return true;
		}
	} */
	if (!CheckAttribute(chref,"perks.list."+perkName))  // у гг нет перка вообще, тогда смотрим офов, иначе выход
	{
		for(int i=1; i<=6; i++)
		{
			sOfficerType = GetOfficerTypeByNum(i);
			if (CheckAttribute(&ChrPerksList, "list." + perkName + ".OfficerType") && ChrPerksList.list.(perkName).OfficerType == sOfficerType)
			{
				cn = sti(chref.Fellows.Passengers.(sOfficerType));
				if(cn<0) {continue;}
				offc = &Characters[cn];
				if (CheckAttribute(offc, "perks.list."+perkName) )          ok = true;
				if (CheckAttribute(offc, "perks.list."+perkName+".delay") ) okDelay = false;
				//if (GetCharacterPerkUsing(chref, perkName) return true;
			}
		}
	}
	return (ok) && (okDelay);
}

// boal
int GetOfficersPerkUsingIdx(ref chref, string perkName)
{
	string  sOfficerType;
	int     cn;
	if (GetCharacterPerkUsing(chref, perkName)) {return sti(chref.index);} // босс отдельно
	for(int i=1; i<=6; i++)
	{
		sOfficerType = GetOfficerTypeByNum(i);
		if (CheckAttribute(&ChrPerksList, "list." + perkName + ".OfficerType") && ChrPerksList.list.(perkName).OfficerType == sOfficerType)
		{
			cn = sti(chref.Fellows.Passengers.(sOfficerType));
			if(cn<0) {continue;}
			if (GetCharacterPerkUsing(&Characters[cn], perkName) ) {return cn;}
		}
	}
	return -1;
}

bool IsCharacterPerkOn(ref chref, string perkName)
{
	aref arRoot, arBase;
	makearef(arRoot,chref.perks.list);
	if( !CheckAttribute(arRoot,perkName) ) return false;
	makearef(arBase,ChrPerksList.list.(perkName));
	if( CheckAttribute(arBase,"TimeDuration") || CheckAttribute(arBase,"TimeDelay") ) {
		return CheckAttribute(arRoot,perkName+".active");
	}
	return true;
}

void CharacterPerkOff(ref chref, string perkName)
{
	if (perkName == "Turn180")
	{
		chref.Tmp.SpeedRecall = 0; // чтоб маневр применить
	}
	DeleteAttribute(chref,"perks.list."+perkName+".active");
	Event("eSwitchPerks","l",sti(chref.index));	 
	// fix boal всегда для ГГ
	Event("eSwitchPerks","l", GetMainCharacterIndex());
	if (sti(chref.index) == nMainCharacterIndex || isOfficerInShip(chref, false)) // наследие перка от офа boal 30.06.06
	{
		DelPerkFromActiveList(perkName);
	}
}

bool CheckOfficersPerk(ref chref, string perkName)
{ // активность перка в данный момент, для временных - режим активности, а не задержки
	bool ret = CheckOfficersPerkWOSelf(chref, perkName);

	if (ret) return true;
	// самого НПС
	if(IsCharacterPerkOn(chref,perkName) == true)
	{
		return true;
	}
	return false;
}

bool CheckOfficersPerkWOSelf(ref chref, string perkName)
{
	int     iOfficer = -1;
	string  sOfficerType;
	if(chref.id == pchar.id)
	{
		if (CheckAttribute(&ChrPerksList, "list." + perkName))
		{
			// boal новая схема наследования. switch не наш метод
			if (CheckAttribute(&ChrPerksList, "list." + perkName + ".OfficerType"))
			{
				sOfficerType = ChrPerksList.list.(perkName).OfficerType;
				iOfficer = sti(pchar.Fellows.Passengers.(sOfficerType));
			}
		}	
	}

	if(iOfficer != -1)
	{
		if(IsCharacterPerkOn(GetCharacter(iOfficer), perkName) == true )
		{
			return true;
		}
	}
	return false;
}
// нигде не юзан
bool CheckCompanionsPerk(ref chref, string perkName)
{
	int i,cn;
	for(i=0; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(chref,i);
		if(cn>=0)
		{	if( IsCharacterPerkOn(GetCharacter(cn),perkName) )	{return true;}
		}
	}
	return false; // fix by boal
}

void procChrPerkDelay()
{
	string perkName = GetEventData();
	int chrIdx = GetEventData();

	aref arPerk;
	makearef(arPerk,Characters[chrIdx].perks.list.(perkName));
	if( !CheckAttribute(arPerk,"delay") ) return;
	int delay = sti(arPerk.delay);
 	// фикс в каюте, палубе, абордаже
 	bool ok;
 	ok = (!bAbordageStarted) && (!bSeaReloadStarted);
 	if (ok || perkName == "Rush")
 	{
		delay--;
	}

	if( CheckAttribute(arPerk,"active") )
	{
		int iActive = sti(arPerk.active)-1;
		if( iActive>0 )	
		{
			arPerk.active = iActive;
			if(!IsPerkIntoList(perkName))
			{
				AddPerkToActiveList(perkName);
			}
		}
		else
		{
			CharacterPerkOff(GetCharacter(chrIdx),perkName);
		}
	}

	if( delay<=0 )
	{	DeleteAttribute(&Characters[chrIdx],"perks.list."+perkName+".delay");
		DeleteAttribute(&Characters[chrIdx],"perks.list."+perkName+".active");
		PostEvent("evntPerkAgainUsable",1);
		ControlsDesc();
	}
	else
	{
		ControlsDesc();
		Characters[chrIdx].perks.list.(perkName).delay = delay;
		PostEvent("evntChrPerkDelay",1000,"sl",perkName,chrIdx);
	}
}

void EnableUsingAbility(ref chref,string perkName)
{
    // boal fix
    // иначе после применения давался ГГ
	int cn;
    if (!CheckCharacterPerk(chref, perkName))
    {

        cn = GetOfficersPerkUsingIdx(chref, perkName);
        if (cn != -1)
        chref = GetCharacter(cn);
    }
    // <--
    
	Event("evntChrPerkDelay","sl",perkName, sti(chref.index));
}

void PerkLoad()
{
//	int iRDTSC = RDTSC_B();
	string locName = pchar.location;
	aref arPerksRoot,arPerk;
	int i,j,n,tmpi;

	for(i=0; i<MAX_CHARACTERS; i++)
	{
		if(Characters[i].location == locName)
		{
			makearef(arPerksRoot,Characters[i].perks.list);
			n = GetAttributesNum(arPerksRoot);
			for(j=0; j<n; j++)
			{
				arPerk = GetAttributeN(arPerksRoot,j);
				if( CheckAttribute(arPerk,"delay") )
				{
					tmpi = sti(arPerk.delay);
					if( tmpi>0 )
					{
						PostEvent("evntChrPerkDelay",1000,"sl",GetAttributeName(arPerk),i);
					}
				}
			}
		}
	}
	// belamour legendary edition при с/л таймер запускаем заново -->
	if(IsCharacterPerkOn(pchar, "IronWill")) 
	{
		ActivateCharacterPerk(pchar,"IronWill");
	}
	for(i=0; i<4; i++)
	{
		n = GetOfficersIndex(pchar,i);
		if(n == -1) continue;
		ref chr = GetCharacter(n);
		if(IsCharacterPerkOn(chr, "IronWill"))
		{
			ActivateCharacterPerk(chr,"IronWill");
		}
	}
	//<--
//	trace("TIME!!! PerkLoad() = " + RDTSC_E(iRDTSC));
}
// boal под новые слоты -->
void ClearActiveChrPerks(ref chref)
{
	int i,cn;
    ref offc; // boal
    string  sOfficerType;	
    
    if (bAbordageStarted || bSeaReloadStarted) return; 
	
	ClearActive(chref); // босс отдельно
	if (CheckAttribute(chref, "Fellows.Passengers")) // не у всех есть
	{
		for (i=1; i<=6; i++)
		{
			sOfficerType = GetOfficerTypeByNum(i);
			cn = sti(chref.Fellows.Passengers.(sOfficerType));
			if(cn<0) {continue;}
			offc = &Characters[cn];
			ClearActive(offc);
		}
	}
}

void ClearActive(ref offic)
{
	aref arPerksRoot, arPerk;
	int i,n;
	
	makearef(arPerksRoot, offic.perks.list);
		
	n = GetAttributesNum(arPerksRoot);
	for (i=0; i<n; i++)
	{
		arPerk = GetAttributeN(arPerksRoot,i);

		if (CheckAttribute(arPerk, "delay"))
        {
			DeleteAttribute(arPerk,"delay");
		}
		if (CheckAttribute(arPerk,"active"))
        {
			DeleteAttribute(arPerk,"active");
		}
	}
}
// был баг К3, этот перк не работал вовсе
void AcceptWindCatcherPerk(ref refCharacter)
{
    int  nShipType;
    ref  refBaseShip, refRealShip;

	nShipType = GetCharacterShipType(refCharacter);
	if (nShipType==SHIP_NOTUSED) return;

	refRealShip = GetRealShip(nShipType);
	refBaseShip = GetShipByType(sti(refRealShip.BaseType));
		
	if (CheckOfficersPerk(refCharacter, "WindCatcher"))
	{
		refRealShip.InertiaAccelerationX	= stf(refBaseShip.InertiaAccelerationX) + stf(refBaseShip.InertiaAccelerationX) / 10.0;
		refRealShip.InertiaAccelerationY	= stf(refBaseShip.InertiaAccelerationY) + stf(refBaseShip.InertiaAccelerationY) / 10.0;
		refRealShip.InertiaAccelerationZ	= stf(refBaseShip.InertiaAccelerationZ) + stf(refBaseShip.InertiaAccelerationZ) / 10.0;
		// потмоу что перк помогает только быстрее набирать скорость, нет торможения
	}
	else
	{   // вернём, если перк снят
	    refRealShip.InertiaAccelerationX	= stf(refBaseShip.InertiaAccelerationX);
		refRealShip.InertiaAccelerationY	= stf(refBaseShip.InertiaAccelerationY);
		refRealShip.InertiaAccelerationZ	= stf(refBaseShip.InertiaAccelerationZ);
	}
	if (iArcadeSails == 0) // момент инерции ниже для тактики
	{
	    refRealShip.InertiaAccelerationY = stf(refRealShip.InertiaAccelerationY) / 2.0;
	}
}

// Jason: зелье берсеркера
void PerkBerserkerReaction()
{
	RemoveItems(pchar, "berserker_potion", 1);
	AddCharacterHealth(pchar, -2);
	if(!ShowCharString()) Log_info(XI_ConvertString("TinctureUsed"));
	PlaySound("Ambient\Tavern\glotok_001.wav");
	PlaySound("Types\warrior03.wav");
}

// belamour legendary edition количество открытых перков у персонажа
int СharacterPerksEnb(ref chr, string perkType)
{
	int total = 0; 
	int perksQ, i;
	string perkName;
	aref arPerksRoot;
	
	makearef(arPerksRoot,ChrPerksList.list);
	perksQ = GetAttributesNum(arPerksRoot);
	for(i=0; i<perksQ; i++)
	{
        perkName = GetAttributeName(GetAttributeN(arPerksRoot,i));
        if(CheckAttribute(arPerksRoot, perkName + ".Hiden")) continue;
		if(!CheckAttribute(chr, "perks.list."+perkName)) continue;
        if(!CheckAttribute(arPerksRoot, perkName + ".BaseType")) arPerksRoot.(perkName).BaseType = "self";
		if(CheckAttribute(arPerksRoot, perkName + ".BaseType") && arPerksRoot.(perkName).BaseType == perkType) total++;
	} 
	return total;
}

// belamour legendary edition наличие перка у ГГ с учётом офицеров
bool CheckOfficersPerkEnable(string perkName)
{
	string  sOfficerType;	   
	int   cn;
	
	if( CheckAttribute(pchar,"perks.list."+perkName) ) return true;
	for(int i=1; i<=6; i++)
	{
		sOfficerType = GetOfficerTypeByNum(i);
		if (CheckAttribute(&ChrPerksList, "list." + perkName + ".OfficerType") && ChrPerksList.list.(perkName).OfficerType == sOfficerType)
		{
			cn = sti(pchar.Fellows.Passengers.(sOfficerType));
			if(cn<0) continue;
			if (CheckAttribute(&Characters[cn], "perks.list."+perkName)) return true;
		}
	}
	return false;
}

// belamour legendary edition время действия спосбности плюс кулдаун 
int AbilityTimeDuration(string stage, string perkName)
{
	if(CheckAttribute(pchar,"perks.list."+perkName+"."+stage)) return sti(pchar.perks.list.(perkName).(stage));
	for(int i=1; i<=6; i++)
	{
		string sOfficerType = GetOfficerTypeByNum(i);
		if (CheckAttribute(&ChrPerksList, "list."+perkName+".OfficerType") && ChrPerksList.list.(perkName).OfficerType == sOfficerType)
		{
			int cn = sti(pchar.Fellows.Passengers.(sOfficerType));
			if(cn<0) continue;
			if(CheckAttribute(&Characters[cn],"perks.list."+perkName+"."+stage)) return sti(Characters[cn].perks.list.(perkName).(stage));
		}
	}
	return -1;
}

// подсчёт перков для интерфейса belamour cle -->
int GetMaxPerks(ref chr, string perkType)
{
	int maximum = 0;
	
	int perksQ, i;
	string perkName;
	aref arPerksRoot;
	
	makearef(arPerksRoot,ChrPerksList.list);
	perksQ = GetAttributesNum(arPerksRoot);
	
	if(sti(chr.index) == GetMainCharacterIndex())
	{
		string HT;
		if(IsCharacterPerkOn(chr, "HT1")) HT = "HT1";
		if(IsCharacterPerkOn(chr, "HT2")) HT = "HT2";
		if(IsCharacterPerkOn(chr, "HT3")) HT = "HT3";
		if(IsCharacterPerkOn(chr, "HT4")) HT = "HT4";
		for(i=0; i<perksQ; i++)
		{
			perkName = GetAttributeName(GetAttributeN(arPerksRoot,i));
			if(CheckAttribute(arPerksRoot, perkName + ".Hiden")) continue;
			if(CheckAttribute(arPerksRoot, perkName + ".NPCOnly")) continue;
			if(CheckAttribute(arPerksRoot, perkName + ".HeroType") && arPerksRoot.(perkName).HeroType != HT) continue;
			if(!CheckAttribute(arPerksRoot, perkName + ".BaseType")) continue;
			if(arPerksRoot.(perkName).BaseType != perkType) continue;
			maximum++;
		}
		return maximum;
	}
	for(i=0; i<perksQ; i++)
	{
		perkName = GetAttributeName(GetAttributeN(arPerksRoot,i));
		if(CheckAttribute(arPerksRoot, perkName + ".Hiden")) continue;
		if(CheckAttribute(arPerksRoot, perkName + ".PlayerOnly")) continue;
		if(!CheckAttribute(arPerksRoot, perkName + ".BaseType")) continue;
		if(arPerksRoot.(perkName).BaseType != perkType) continue;
		maximum++;
	}
	return maximum;
}

bool bPerksMaxSelf(ref chr)
{
	if(СharacterPerksEnb(chr, "self") >= GetMaxPerks(chr, "self")) return true;
	
	return false;
}

bool bPerksMaxShip(ref chr)
{
	if(СharacterPerksEnb(chr, "ship") >= GetMaxPerks(chr, "ship")) return true;
	
	return false;
}

bool HaveAllPerks(ref chr, string type) // any, self, ship
{
	string perkName;
	aref arPerksRoot;
	makearef(arPerksRoot,ChrPerksList.list);
	int perksQ = GetAttributesNum(arPerksRoot);

    bool bHero = (sti(chr.index) == GetMainCharacterIndex());
    bool bAny  = (type == "any");

	for(int i = 0; i < perksQ; i++)
	{
		perkName = GetAttributeName(GetAttributeN(arPerksRoot,i));
        if(!CheckAttribute(arPerksRoot, perkName + ".BaseType")) continue;   // Предыстории
		if(!bAny && ChrPerksList.list.(perkName).BaseType != type) continue; // Не тот тип
        if(CheckAttribute(arPerksRoot, perkName + ".HeroType")) continue;    // Личные спецперки
        if(!bHero && CheckAttribute(arPerksRoot, perkName + ".PlayerOnly")) continue; // Не ГГ
        if(bHero && CheckAttribute(arPerksRoot, perkName + ".NPCOnly")) continue;     // Не НПЦ
        if(CheckAttribute(arPerksRoot, perkName + ".Hiden")) continue;       // Скрытые

		if(!CheckCharacterPerk(sld, perkName)) return false; // Перк доступен, но не прокачан
	}
    return true;
}
// <-- подсчёт перков для интерфейса
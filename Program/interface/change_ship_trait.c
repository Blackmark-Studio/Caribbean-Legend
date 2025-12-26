ref realShip;
int price;
string selectedTrait;
object possibleTraits;
int selectedTraitIndex = 0;
int maxTraits;
string currentTrait;
ref xi_refCharacter;

void InitInterface_R(string iniName, ref _chr)
{
	xi_refCharacter = _chr;
	StartAboveForm(true);
	bQuestCheckProcessFreeze = true; 	// лочим квест и карту
	realShip = GetRealShip(GetCharacterShipType(xi_refCharacter));
	price = 100;
	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcCommand",0);
	SetEventHandler("evntDoPostExit","DoPostExit",0);

	maxTraits = SetPossibleTraits(sti(realShip.Spec), &possibleTraits);

	string specName = GetShipSpecDesc(xi_refCharacter);
	specName = DLG_Convert(specName, "ShipsPerksDescribe.txt", &NullObject);
	SetFormatedText("SHIP_SPEC", "Тип корабля: " + specName);

	SetCurrentTrait();
	SelectTrait(0);
}

void SetCurrentTrait()
{
	int nShipType = GetCharacterShipType(xi_refCharacter);
	if (nShipType == SHIP_NOTUSED) currentTrait = "";
	else if (!CheckAttribute(&RealShips[nShipType],"Traits")) currentTrait = "";
	else currentTrait = RealShips[nShipType].Traits;
}

void SelectTrait(int direction)
{
	selectedTraitIndex += direction;
	selectedTraitIndex = iClamp(0, maxTraits-1, selectedTraitIndex);

	selectedTrait = GetAttributeName(GetAttributeN(&possibleTraits, selectedTraitIndex));
	string caption, desc, desc2;
	caption = DLG_Convert(selectedTrait, "ShipsPerksDescribe.txt", &NullObject);
	desc = DLG_Convert(selectedTrait + "_desc", "ShipsPerksDescribe.txt", &NullObject);
	desc2 = DLG_Convert(selectedTrait + "_desc2", "ShipsPerksDescribe.txt", &NullObject);

	SetFormatedText("TRAIT_CAPTION", caption);
	SetFormatedText("TRAIT_DESC", desc);
	SetFormatedText("TRAIT_DESC2", desc2);
	SetNewGroupPicture("TRAIT_ICON", "PERKS_SHIPS", selectedTrait);
	SetNewGroupPicture("TRAIT_ICON_BORDER", "PERKS_SHIPS", "border");
	SetNewGroupPicture("TRAIT_ICON_BACKGROUND", "PERKS_SHIPS", "background");
	SetCurrentNode("MAIN_FRAME");

	SetSelectable("B_OK", currentTrait != selectedTrait);
}

void ProcessBreakExit()
{
	IDoExit( RC_INTERFACE_SALARY_EXIT );
}

void ProcessCancelExit()
{
	IDoExit( RC_INTERFACE_SALARY_EXIT );
}

void IDoExit(int exitCode)
{
	EndAboveForm(true);
	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("evntDoPostExit","DoPostExit");
	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
	PostEvent("StopQuestCheckProcessFreeze", 100);//заморозка проверки квестов
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch (nodName)
	{
		case "TRAIT_CHANGE_LEFT":
			if (comName == "click") SelectTrait(-1);
		break;

		case "TRAIT_CHANGE_RIGHT":
			if (comName == "click") SelectTrait(1);
		break;

		case "B_OK":
			if (comName == "click" || comName == "activate") SetNewTrait();
		break;
	}

	if (comName == "leftstep") SelectTrait(-1);
	if (comName == "rightstep") SelectTrait(1);

}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void SetNewTrait()
{
	realShip.Traits = selectedTrait;
	RemoveDublonsFromPCharTotal(GetChangeShipTraitCost(xi_refCharacter));
	Achievment_Set("ach_CL_199");
	IDoExit(RC_INTERFACE_ANY_EXIT);
}

int SetPossibleTraits(int spec, ref result)
{
	switch (spec)
	{
		case SHIP_SPEC_MERCHANT:
			result.trait01;
			result.trait02;
			result.trait03;
			result.trait04;
			result.trait05;
		break;
		case SHIP_SPEC_WAR:
			result.trait11;
			result.trait12;
			result.trait13;
			result.trait14;
		break;
		case SHIP_SPEC_RAIDER:
			result.trait21;
			result.trait22;
			result.trait23;
			result.trait24;
		break;
		case SHIP_SPEC_UNIVERSAL:
			return 0;
		break;
	}

	return GetAttributesNum(result);
}
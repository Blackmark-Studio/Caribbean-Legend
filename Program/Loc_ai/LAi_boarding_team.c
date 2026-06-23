

void GenerateCrew(ref rCharacter, string sType, ref rDstArray)
{
	string sFunc = GetCrewFunction(rCharacter);

	int nDstArraySize = GetArraySize(rDstArray);

	object aSrcArray[1];
	call sFunc(&aSrcArray, sType);
	ShuffleArray(&aSrcArray);
	int nSrcArraySize = GetArraySize(&aSrcArray);

	for (int i = 0; i < nDstArraySize; i++)
	{
		rDstArray[i] = aSrcArray[i % nSrcArraySize];
	}
}


string GetCrewFunction(ref rCharacter)
{
	string sFunc = "GenerateCrewBase";
	int iNation = int(rCharacter.nation);

	if (CheckAttribute(rCharacter, "CrewCallback"))
	{
		return rCharacter.CrewCallback;
	}

	if (CheckAttribute(rCharacter, "GenQuest.CrewSkelMode"))
	{
		return "GenerateCrewSkeletons";
	}

	if (rCharacter.sex == "skeleton")
	{
		return "GenerateCrewSkeletons";
	}

	if (CheckAttribute(rCharacter, "GenQuest.CrewMementoMode"))
	{
		return "GenerateCrewMemento";
	}

	if(int(rCharacter.index) == GetMainCharacterIndex())
	{
		if (CheckAttribute(rCharacter, "GenQuest.CrewSkelMode"))
		{
			return "GenerateCrewSkeletons";
		}
		//--> Jason - национальная форма солдат на квестовиках по мультиквесту
		if (CheckAttribute(rCharacter, "questTemp.HWIC.HollEquip") && int(RealShips[int(pchar.ship.type)].basetype) == SHIP_MAYFANG)
		{
			return "GenerateCrewHol";
		}
		if (CheckAttribute(rCharacter, "questTemp.HWIC.EngEquip") && int(RealShips[int(pchar.ship.type)].basetype) == SHIP_VALCIRIA)
		{
			return "GenerateCrewEng";
		}
		if (CheckAttribute(rCharacter, "questTemp.Mtraxx.CharleePrince")) //команда пиратов Fullback7
		{
			return "GenerateCrewPir";
		}
		if (CheckAttribute(rCharacter, "questTemp.CharleePrince"))
		{
			return "GenerateCrewPir";
		}
		//<-- форма солдат на квестовиках
		if (isMainCharacterPatented() && int(Items[int(rCharacter.EquipedPatentId)].TitulCur) > 1) //форма только со звания капитан
		{
			iNation = int(Items[int(rCharacter.EquipedPatentId)].Nation);
			return "GenerateCrew" + NationShortName(iNation);
		}
		else
		{
			return "GenerateCrewBase";
		}
	}
	else
	{
		if (iNation < 0) iNation = PIRATE;
		if (CheckAttribute(rCharacter, "Ship.Mode") && rCharacter.Ship.Mode == "Pirate")
			iNation = PIRATE;
		if (CheckAttribute(rCharacter, "Ship.Mode") && rCharacter.Ship.Mode == "Trade")
		{
			return "GenerateCrewTraders";
		}
		else
		{//boal <--
			if (CheckAttribute(rCharacter, "Ship.Mode") && rCharacter.Ship.Mode == "mercenary")
			{ // Jason
				return "GenerateCrewMerceneries";
			}
			else
			{
				return "GenerateCrew" + NationShortName(iNation);
			}
		}
	}

	return sFunc;
}


void GenerateCrewEng(ref rModelArr, string type)
{
	int i;
	switch(type)
	{
		case "soldier":
			SetArraySize(rModelArr, 8);
			for (i = 0; i < 8; i++)
			{
				rModelArr[i].model = "sold_eng_" + (i+1);
				rModelArr[i].ani = "man";
			}
		break;

		case "mushketer":
			SetArraySize(rModelArr, 6);
			for (i = 0; i < 6; i++)
			{
				rModelArr[i].model = "mush_eng_" + (i+1);
				rModelArr[i].ani = "mushketer";
			}
		break;

		case "officer":
			SetArraySize(rModelArr, 2);
			for (i = 0; i < 2; i++)
			{
				rModelArr[i].model = "off_eng_" + (i+1);
				rModelArr[i].ani = "man";
			}
		break;

		case "captain":
			SetArraySize(rModelArr, 1);
			rModelArr[0].model = "off_eng_1";
			rModelArr[0].ani = "man";
		break;

		case "lowpoly":
			SetArraySize(rModelArr, 10);
			for (i = 0; i < 10; i++)
			{
				rModelArr[i].model = "LowCharacters/sold_eng_" + (i+1);
				rModelArr[i].ani = "";
			}
		break;
	}
}

void GenerateCrewFra(ref rModelArr, string type)
{
	int i;
	switch(type)
	{
		case "soldier":
			SetArraySize(rModelArr, 8);
			for (i = 0; i < 8; i++)
			{
				rModelArr[i].model = "sold_fra_" + (i+1);
				rModelArr[i].ani = "man";
			}
		break;

		case "mushketer":
			SetArraySize(rModelArr, 6);
			for (i = 0; i < 6; i++)
			{
				rModelArr[i].model = "mush_fra_" + (i+1);
				rModelArr[i].ani = "mushketer";
			}
		break;

		case "officer":
			SetArraySize(rModelArr, 2);
			for (i = 0; i < 2; i++)
			{
				rModelArr[i].model = "off_fra_" + (i+1);
				rModelArr[i].ani = "man";
			}
		break;

		case "captain":
			SetArraySize(rModelArr, 1);
			rModelArr[0].model = "off_fra_1";
			rModelArr[0].ani = "man";
		break;

		case "lowpoly":
			SetArraySize(rModelArr, 10);
			for (i = 0; i < 10; i++)
			{
				rModelArr[i].model = "LowCharacters/sold_fra_" + (i+1);
				rModelArr[i].ani = "";
			}
		break;
	}
}

void GenerateCrewSpa(ref rModelArr, string type)
{
	int i;
	switch(type)
	{
		case "soldier":
			SetArraySize(rModelArr, 8);
			for (i = 0; i < 8; i++)
			{
				rModelArr[i].model = "sold_spa_" + (i+1);
				rModelArr[i].ani = "man";
			}
		break;

		case "mushketer":
			SetArraySize(rModelArr, 6);
			for (i = 0; i < 6; i++)
			{
				rModelArr[i].model = "mush_spa_" + (i+1);
				rModelArr[i].ani = "mushketer";
			}
		break;

		case "officer":
			SetArraySize(rModelArr, 2);
			for (i = 0; i < 2; i++)
			{
				rModelArr[i].model = "off_spa_" + (i+1);
				rModelArr[i].ani = "man";
			}
		break;

		case "captain":
			SetArraySize(rModelArr, 1);
			rModelArr[0].model = "off_spa_1";
			rModelArr[0].ani = "man";
		break;

		case "lowpoly":
			SetArraySize(rModelArr, 10);
			for (i = 0; i < 10; i++)
			{
				rModelArr[i].model = "LowCharacters/sold_spa_" + (i+1);
				rModelArr[i].ani = "";
			}
		break;
	}
}

void GenerateCrewHol(ref rModelArr, string type)
{
	int i;
	switch(type)
	{
		case "soldier":
			SetArraySize(rModelArr, 8);
			for (i = 0; i < 8; i++)
			{
				rModelArr[i].model = "sold_hol_" + (i+1);
				rModelArr[i].ani = "man";
			}
		break;

		case "mushketer":
			SetArraySize(rModelArr, 6);
			for (i = 0; i < 6; i++)
			{
				rModelArr[i].model = "mush_hol_" + (i+1);
				rModelArr[i].ani = "mushketer";
			}
		break;

		case "officer":
			SetArraySize(rModelArr, 2);
			for (i = 0; i < 2; i++)
			{
				rModelArr[i].model = "off_hol_" + (i+1);
				rModelArr[i].ani = "man";
			}
		break;

		case "captain":
			SetArraySize(rModelArr, 1);
			rModelArr[0].model = "off_hol_1";
			rModelArr[0].ani = "man";
		break;

		case "lowpoly":
			SetArraySize(rModelArr, 10);
			for (i = 0; i < 10; i++)
			{
				rModelArr[i].model = "LowCharacters/sold_hol_" + (i+1);
				rModelArr[i].ani = "";
			}
		break;
	}
}

void GenerateCrewPir(ref rModelArr, string type)
{
	int i, j;
	switch(type)
	{
		case "soldier":
			SetArraySize(rModelArr, 10);
			for (i = 0; i < 10; i++)
			{
				rModelArr[i].model = "citiz_" + (i+41);
				rModelArr[i].ani = "man";
			}
		break;

		case "mushketer":
			SetArraySize(rModelArr, 3);
			for (i = 0; i < 3; i++)
			{
				rModelArr[i].model = "mush_ctz_" + (i+7);
				rModelArr[i].ani = "mushketer";
			}
		break;

		case "officer":
			SetArraySize(rModelArr, 10);

			i = 0;
			for (j = 6; j <=10; j++)
			{
				rModelArr[i].model = "mercen_" + j;
				rModelArr[i].ani = "man";
				i++;
			}

			for (j = 16; j <=20; j++)
			{
				rModelArr[i].model = "mercen_" + j;
				rModelArr[i].ani = "man";
				i++;
			}
		break;

		case "captain":
			SetArraySize(rModelArr, 1);
			rModelArr[0].model = "mercen_6";
			rModelArr[0].ani = "man";
		break;

		case "lowpoly":
			SetArraySize(rModelArr, 10);
			for (i = 0; i < 10; i++)
			{
				rModelArr[i].model = "LowCharacters/pirate_" + (i+1);
				rModelArr[i].ani = "";
			}
		break;
	}
}

void GenerateCrewTraders(ref rModelArr, string type)
{
	int i, j;
	switch(type)
	{
		case "soldier":
			SetArraySize(rModelArr, 6);
			for (i = 0; i < 6; i++)
			{
				rModelArr[i].model = "citiz_" + (i+21);
				rModelArr[i].ani = "man";
			}
		break;

		case "mushketer":
			SetArraySize(rModelArr, 3);
			for (i = 0; i < 3; i++)
			{
				rModelArr[i].model = "mush_ctz_" + (i+1);
				rModelArr[i].ani = "mushketer";
			}
		break;

		case "officer":
			SetArraySize(rModelArr, 6);

			i = 0;
			for (j = 22; j <=27; j++)
			{
				rModelArr[i].model = "mercen_" + j;
				rModelArr[i].ani = "man";
				i++;
			}
		break;

		case "captain":
			SetArraySize(rModelArr, 1);
			rModelArr[0].model = "mercen_26";
			rModelArr[0].ani = "man";
		break;

		case "lowpoly":
			SetArraySize(rModelArr, 10);
			for (i = 0; i < 10; i++)
			{
				rModelArr[i].model = "LowCharacters/trader_" + (i+1);
				rModelArr[i].ani = "";
			}
		break;
	}
}

void GenerateCrewSkeletons(ref rModelArr, string type)
{
	int i, j;
	switch(type)
	{
		case "soldier":
			SetArraySize(rModelArr, 4);
			for (i = 0; i < 4; i++)
			{
				rModelArr[i].model = "skel" + (i+1);
				rModelArr[i].ani = "skeleton";
			}
		break;

		case "mushketer":
			SetArraySize(rModelArr, 3);
			for (i = 0; i < 3; i++)
			{
				rModelArr[i].model = "mush_skel_" + (i+1);
				rModelArr[i].ani = "mush_skel";
			}
		break;

		case "officer":
			SetArraySize(rModelArr, 4);
			for (i = 0; i < 4; i++)
			{
				rModelArr[i].model = "skel" + (i+1);
				rModelArr[i].ani = "skeleton";
			}
		break;

		case "captain":
			SetArraySize(rModelArr, 1);
			rModelArr[0].model = "skeletcap";
			rModelArr[0].ani = "skeleton";
		break;

		case "lowpoly":
			SetArraySize(rModelArr, 10);
			for (i = 0; i < 10; i++)
			{
				rModelArr[i].model = "LowCharacters/skeleton_" + (i+1);
				rModelArr[i].ani = "";
			}
		break;
	}
}

void GenerateCrewBase(ref rModelArr, string type)
{
	int i, j;
	switch(type)
	{
		case "soldier":
			SetArraySize(rModelArr, 10);
			for (i = 0; i < 10; i++)
			{
				rModelArr[i].model = "citiz_" + (i+31);
				rModelArr[i].ani = "man";
			}
		break;

		case "mushketer":
			SetArraySize(rModelArr, 3);
			for (i = 0; i < 3; i++)
			{
				rModelArr[i].model = "mush_ctz_" + (i+4);
				rModelArr[i].ani = "mushketer";
			}
		break;

		case "officer":
			SetArraySize(rModelArr, 6);

			i = 0;
			for (j = 22; j <=27; j++)
			{
				rModelArr[i].model = "mercen_" + j;
				rModelArr[i].ani = "man";
				i++;
			}
		break;

		case "captain":
			SetArraySize(rModelArr, 1);
			rModelArr[0].model = "mercen_26";
			rModelArr[0].ani = "man";
		break;

		case "lowpoly":
			SetArraySize(rModelArr, 10);
			for (i = 0; i < 10; i++)
			{
				rModelArr[i].model = "LowCharacters/man_" + (i+1);
				rModelArr[i].ani = "";
			}
		break;
	}
}

void GenerateCrewMerceneries(ref rModelArr, string type)
{
	int i, j;
	switch(type)
	{
		case "soldier":
			SetArraySize(rModelArr, 10);
			for (i = 0; i < 10; i++)
			{
				rModelArr[i].model = "citiz_" + (i+51);
				rModelArr[i].ani = "man";
			}
		break;

		case "mushketer":
			SetArraySize(rModelArr, 3);
			for (i = 0; i < 3; i++)
			{
				rModelArr[i].model = "mush_ctz_" + (i+10);
				rModelArr[i].ani = "mushketer";
			}
		break;

		case "officer":
			SetArraySize(rModelArr, 10);

			i = 0;
			for (j = 6; j <=10; j++)
			{
				rModelArr[i].model = "mercen_" + j;
				rModelArr[i].ani = "man";
				i++;
			}

			for (j = 16; j <=20; j++)
			{
				rModelArr[i].model = "mercen_" + j;
				rModelArr[i].ani = "man";
				i++;
			}
		break;

		case "captain":
			SetArraySize(rModelArr, 1);
			rModelArr[0].model = "mercen_6";
			rModelArr[0].ani = "man";
		break;

		case "lowpoly":
			SetArraySize(rModelArr, 10);
			for (i = 0; i < 10; i++)
			{
				rModelArr[i].model = "LowCharacters/pirate_" + (i+1);
				rModelArr[i].ani = "";
			}
		break;
	}
}

void GenerateCrewMemento(ref rModelArr, string type)
{
	int i, j;
	switch(type)
	{
		case "soldier":
			SetArraySize(rModelArr, 30);

			i = 0;
			for (j = 1; j <=9; j++)
			{
				rModelArr[i].model = "citiz_4" + j;
				rModelArr[i].ani = "man";
				i++;
			}

			for (j = 1; j <=7; j++)
			{
				rModelArr[i].model = "rivados_" + j;
				rModelArr[i].ani = "man";
				i++;
			}

			for (j = 1; j <=8; j++)
			{
				rModelArr[i].model = "sold_spa_" + j;
				rModelArr[i].ani = "man";
				i++;
			}

			for (j = 1; j <=6; j++)
			{
				rModelArr[i].model = "miskito_" + j;
				rModelArr[i].ani = "man";
				i++;
			}
		break;

		case "mushketer":
			SetArraySize(rModelArr, 3);
			for (i = 0; i < 3; i++)
			{
				rModelArr[i].model = "mush_ctz_" + (i+7);
				rModelArr[i].ani = "mushketer";
			}
		break;

		case "officer":
			SetArraySize(rModelArr, 10);

			i = 0;
			for (j = 6; j <=10; j++)
			{
				rModelArr[i].model = "mercen_" + j;
				rModelArr[i].ani = "man";
				i++;
			}

			for (j = 16; j <=20; j++)
			{
				rModelArr[i].model = "mercen_" + j;
				rModelArr[i].ani = "man";
				i++;
			}
		break;

		case "captain":
			SetArraySize(rModelArr, 1);
			rModelArr[0].model = "mercen_6";
			rModelArr[0].ani = "man";
		break;

		case "lowpoly":
			SetArraySize(rModelArr, 10);
			for (i = 0; i < 10; i++)
			{
				rModelArr[i].model = "LowCharacters/pirate_" + (i+1);
				rModelArr[i].ani = "";
			}
		break;
	}
}

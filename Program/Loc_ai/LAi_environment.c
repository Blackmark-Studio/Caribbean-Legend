
// Jason. Выращивание травки: раз в 10 дней при заходе в локацию вырастает новый экземпляр
bool LAi_CreateFlowers(ref location)
{
	ref rItm;
	if (CheckAttribute(location, "fastreload") && location.id.label != "ExitTown") return false;
	if(!CheckAttribute(location, "locators.item") || location.id.label == "Cave entrance" || location.type == "seashore" || location.type == "cave") return false;
	if(location.type != "jungle") return false;
	
	if(CheckAttribute(location, "growflower") && GetNpcQuestPastDayParam(location, "Fl_date") > 9) {
		aref flowerLocs;
		makearef(flowerLocs, location.growflower);
		int flowerCount = GetAttributesNum(flowerLocs);
		for (int flowerIndex = 0; flowerIndex < flowerCount; flowerIndex++) {
			string flowerLocator = GetAttributeName(GetAttributeN(flowerLocs, flowerIndex));
			RemoveItemFromLocation(location.id, flowerLocator);
			QuestPointerDelLoc(location.id, "item", flowerLocator);
		}
		
		DeleteAttribute(location, "growflower");
	}
	
	if (!CheckAttribute(location, "growflower"))
	{
		int n = (location.id.label == "ExitTown") ? 2 : 1; // За городскими воротами выращиваем больше
		for(int i = 0; i < n; i++)
		{
			string item = "cannabis"+(rand(5)+1);
			string locator = "flower" + (rand(9)+1);
			SetItemInLocation(item, location.id, locator);
			Log_TestInfo("Новая травка " + item + " выросла в локаторе " + locator); // patch
			QuestPointerToLoc(location.id, "item", locator);
			location.growflower.(locator) = true;
		}
		SaveCurrentNpcQuestDateParam(location, "Fl_date");
	}
	return true;
}

// Садовник Jason. Рассадка квестовой травки
bool LAi_CreateQuestFlowers(ref location)
{
	ref rItm;
	int i;
	if (CheckAttribute(location, "questflower"))
	{
		i = int(location.questflower);
		rItm = ItemsFromID("cannabis7");
		rItm.shown = true;
		rItm.startLocation = location.id;
		rItm.startLocator = "qflower"+i;
		//Log_TestInfo("В этой локации произрастает Мангароса");// patch
		DeleteAttribute(location, "questflower");
		QuestPointerToLoc(location.id, "item", rItm.startLocator);
	}
	return true;
}

// Jason. Выброшенные на берег сундуки
bool LAi_CreateShoreChest(ref location)
{
	string sTemp = location.id;
	DeleteAttribute(location, "box1.NotChest");
	DeleteAttribute(location, "box2.NotChest");
	if(CheckAttribute(location, "Chestgennot")) return false;
	if (location.type == "seashore")
	{
		location.box1.NotChest = true;
		location.box2.NotChest = true;
		if (CheckAttribute(location, "Chestgennot")) return false;
		if (CheckAttribute(pchar, "questTemp.Sharlie.Lock")) return false; // 021012
		if (!CheckAttribute(location, "shorechest") && hrand(100, sTemp) < 5) // нет сундука
		{
			string sModel = "chest_"+(rand(2)+1);
			location.num = hrand(1, sTemp)+1;
			location.numbox = "box"+(int(location.num));
			location.shorechest = true;
			location.models.always.chest = sModel;
			location.models.always.chest.locator.group = "box";
			location.models.always.chest.locator.name = location.numbox;
			location.models.always.chest.tech = "DLightModel"; // 280313
			//log_testinfo("Сундук "+location.numbox+" "+sModel+" подготавливается!");// patch
			return true;
		}
		if(CheckAttribute(location, "shorechest")) // есть сундук
		{
			
			if (int(location.num) == 1) DeleteAttribute(location, "box1.NotChest");
			else DeleteAttribute(location, "box2.NotChest");
			if(CheckAttribute(location, "chest_date") && GetNpcQuestPastDayParam(location, "chest_date") > 2) 
			{
				DeleteAttribute(&locations[FindLocation(sTemp)], location.numbox);
				DeleteAttribute(location, "shorechest");
				DeleteAttribute(location, "shorefill");
				DeleteAttribute(location, "chest_date");
				DeleteAttribute(location, "models.always.chest");
				//log_testinfo("Сундук на берегу пуст!");// patch
			}
			else 
			{
				if(!CheckAttribute(location, "shorefill")) 
				{
					FillShorechestBox(sTemp, int(location.num), hrand(5, sTemp));
					SaveCurrentNpcQuestDateParam(location, "chest_date");
					location.shorefill = true;
					//log_testinfo("Сундук на берегу!");// patch
				}
				else
				{
					//log_testinfo("Сундук ещё здесь и полон!");// patch
					return true;
				}
			}
		}
	}
	return true;
}

// Jason. Установка телепортационных статуй и их активация
bool LAi_CreateDolly(ref location)
{
	ref rItm = ItemsFromID("dolly0");
	ref rItem = ItemsFromID("dolly5");
	if (CheckAttribute(location, "dolly"))
	{
		int i = int(location.dolly);
		float fStrTime, fFinTime;
		switch (i)
		{
			case 1:
				fStrTime = 0.00;
				fFinTime = 1.00;
			break;
			
			case 2:
				fStrTime = 8.00;
				fFinTime = 9.00;
			break;
			
			case 3:
				fStrTime = 16.00;
				fFinTime = 17.00;
			break;
		}
		if (float(environment.time) >= fStrTime && float(environment.time) < fFinTime && CheckAttribute(pchar, "questTemp.Dolly"))
		{
			rItm.shown = false;
			rItem.shown = true;
			rItem.startLocation = location.id;
			rItem.startLocator = "dolly"+i;
			location.canteleport = true;
			CreateLocationParticles("shadowstar", "camera", "dolly", 1.15, 0, 0, "");
		}
		else
		{
			rItem.shown = false;
			rItm.shown = true;
			rItm.startLocation = location.id;
			rItm.startLocator = "dolly"+i;
			DeleteAttribute(location, "canteleport");
		}
	}
	return true;
}

void LAi_CreateParticles(ref location)
{
	if (CheckAttribute(location, "fire"))
	{
		CreateFireParticles("goto", "fire");
	}
}

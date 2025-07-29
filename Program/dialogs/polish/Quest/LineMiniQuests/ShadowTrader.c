// Бесчестный конкурент
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "To jest błąd. Powiadomcie deweloperów";
			link.l1 = "Oczywiście!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "ShadowGuarder":
			dialog.text = "Czego potrzebujesz?";
			link.l1 = "Ty jesteś "+pchar.questTemp.Shadowtrader.Guardername+"? Wysłał mnie miejscowy kupiec. Niecierpliwie oczekuje na twoją obecność w tej chwili.";
			link.l1.go = "ShadowGuarder_1";
			DelLandQuestMark(npchar);
		break;
	
		case "ShadowGuarder_1":
			dialog.text = "A-ah, ale czekałem na niego tutaj! Powiedziano mi, że przyjdzie do karczmy! Przepraszam, już idę.";
			link.l1 = "Dobrze!";
			link.l1.go = "ShadowGuarder_2";
		break;
	
		case "ShadowGuarder_2":
			DialogExit();
			chrDisableReloadToLocation = true;
			sld = characterFromId("ShadowGuarder");	
			LAi_SetStayType(sld);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.questTemp.Shadowtrader.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", pchar.questTemp.Shadowtrader.City +"_store", "goto", "goto2", "OpenTheDoors", 6);
			pchar.questTemp.Shadowtrader = "begin";
			AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
		break;
	
		case "ShadowAgent":
			dialog.text = "Dobry wieczór, kapitanie. Chcesz zdobyć tanie towary, heh? Chodź za mną!";
			link.l1 = "Prowadź dalej.";
			link.l1.go = "ShadowAgent_1";
		break;
	
		case "ShadowAgent_1":
			DeleteAttribute(pchar, "questTemp.Shadowtrader.SeekTrader");
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "houseS4", "CommonFlamHouse", "barmen", "stay", "Shadow_inRoom", 40);
		break;
	
		case "ShadowTrader":
			dialog.text = "Dobry wieczór, panie. Miło spotkać nowego klienta, ha! Pozwól, że się przedstawię: jestem "+GetFullName(npchar)+". Mam najtańsze towary w tym mieście, zapewniam cię.";
			link.l1 = "Nareszcie się spotkaliśmy..."+npchar.name+". Cóż, obawiam się, że cię rozczaruję: szukałem cię nie dla handlu, lecz by zakończyć twój plugawy proceder. Stałeś się wielką zmorą dla ważnego człowieka. Ból stał się tak dotkliwy, że chce cię uciszyć... za wszelką cenę.";
			link.l1.go = "ShadowTrader_1";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				notification("Jesteś godny zaufania", "Trustworthy");
				link.l2 = "Stój, łotrze! Nie wiedziałeś, że musisz płacić podatki za prowadzenie działalności handlowej? Nikt nie łamie prawa na moich wodach! "+GetFullName(npchar)+", złamałeś prawo i twoje skradzione dobra są teraz skonfiskowane! Za drzwiami stoi uzbrojona straż, więc nawet nie próbuj udawać głupiego!";
				link.l2.go = "ShadowTrader_2";
			}
			AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
		break;
	
		case "ShadowTrader_1":
			dialog.text = "Naprawdę? Nie spodziewałem się... Kim, do diabła, jesteś?! To pułapka! Chyba wiem, kto za tym stoi! Za wszelką cenę... chłopcy, zabijcie go!";
			link.l1 = "Zatańczmy, łajdaki!";
			link.l1.go = "ShadowTrader_fight";
			NextDiag.currentnode = "ShadowTrader_6";
		break;
	
	case "ShadowTrader_2":
		dialog.text = "O Boże... oficerze, posłuchaj! Zróbmy układ. Jesteś mądrym i miłosiernym człowiekiem! Zapłacę ci 5000 sztuk srebra, a ty pozwolisz nam uciec przez drugie piętro. Weźmiesz także towar, potrzebujesz go, prawda? Po co ci ja? Wyjadę z miasta natychmiast i nikt nas więcej nie zobaczy. A ty dostaniesz swoje pieniądze. Co o tym sądzisz, oficerze?";
		link.l1 = "Naprawdę sądzisz, plugawcu, że splamię swój obowiązek dla tak marnej sumy?";
		link.l1.go = "ShadowTrader_3";
		break;
	
	case "ShadowTrader_3":
		dialog.text = "Dobrze, dobrze, oficerze, bierz wszystko, co mam - 10 000 pesos. To wszystko, co mam, przysięgam!";
		link.l1 = "Hm... Jeśli cię aresztuję, wszystkie twoje pieniądze zostaną skonfiskowane... Dobrze! Ten punkt przemytniczy jest zamknięty, a wszystkie towary są skonfiskowane... Daj mi monetę i znikaj. Nie pokazuj się tu więcej!";
		link.l1.go = "ShadowTrader_4";
		break;
		
	case "ShadowTrader_4":
			dialog.text = "Dzięki, dzięki, dzięki oficerze! Oto twoje pieniądze, i więcej mnie tu nie zobaczysz. Ruszamy!";
			link.l1 = " Wynoś się, albo będę zmuszony cię aresztować!";
			link.l1.go = "ShadowTrader_escape";
		break;
	
		case "ShadowTrader_fight":
			LAi_SetPlayerType(pchar);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("ShadowAgent_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				sld.nation = PIRATE;
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "ShadowTrader_afterfight");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
	
		case "ShadowTrader_escape"://напугали
			AddMoneyToCharacter(pchar, 10000);
			LAi_SetPlayerType(pchar);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("ShadowAgent_"+i);	
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload3", "none", "", "", "", 7.0);
			}
			sld = characterFromID("ShadowTrader"); 
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload3", "none", "", "", "", 7.0);
			DialogExit();
			DoQuestFunctionDelay("ShadowTrader_final", 9.0);
			pchar.questTemp.Shadowtrader.End.Escape = "true";
			AddQuestRecord("Shadowtrader", "8");
			AddCharacterExpToSkill(pchar, "Leadership", 200);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 250);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
		break;
	
		case "ShadowTrader_6":
			dialog.text = "Ach! Litości, nie zabijaj mnie! Oddam ci wszystko, co mam!";
			link.l1 = "Wszystkie twoje towary zostaną skonfiskowane przez władze. Naprawdę myślisz, że okażę ci łaskę po tym, co się tu właśnie wydarzyło?";
			link.l1.go = "ShadowTrader_7";
		break;
	
		case "ShadowTrader_7":
			dialog.text = "Ja... Ja dam ci wszystkie moje pieniądze i rzeczy! Tylko mnie puść! Dziś opuszczę wyspę i już mnie tu więcej nie zobaczysz!";
			link.l1 = "Bardzo dobrze. Daj mi wszystko, co masz przy sobie i wynoś się. I nigdy więcej nie próbuj robić tutaj interesów - następnym razem nie oszczędzę twojego żałosnego życia, ty łotrze.";
			link.l1.go = "ShadowTrader_free";
			link.l2 = "Nie ma mowy, łajdaku, nie przekupisz mnie. Jedynym sposobem na radzenie sobie z takimi jak ty jest zimna stal i gorący ołów!";
			link.l2.go = "ShadowTrader_killed";
		break;
		
		case "ShadowTrader_free"://отпустили
			AddMoneyToCharacter(pchar, 20550);
			TakeNItems(pchar, "jewelry1", rand(5));
			TakeNItems(pchar, "jewelry2", rand(20));
			TakeNItems(pchar, "jewelry5", rand(20));
			PlaySound("interface\important_item.wav");
			Log_Info("Otrzymano przedmioty");
			LAi_SetPlayerType(pchar);
			sld = characterFromID("ShadowTrader"); 
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload3", "none", "", "", "", 5.0);
			DialogExit();
			DoQuestFunctionDelay("ShadowTrader_final", 7.0);
			pchar.questTemp.Shadowtrader.End.Free = "true";
			AddQuestRecord("Shadowtrader", "9");
			ChangeCharacterComplexReputation(pchar,"nobility", 5); 
			AddComplexSelfExpToScill(70, 70, 70, 70);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		break;
	
		case "ShadowTrader_killed":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_SetActorType(pchar);
			//  belamour legendary edition если не надет пистоль или мушкет, то выдадим строевой -->
			if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE))
			{
				GiveItem2Character(pchar, "pistol1");
				EquipCharacterbyItem(pchar, "pistol1");
			}
			// <-- legendary edition
			LAi_ActorAnimation(pchar, "Shot", "ShadowTrader_killed_end", 1.3);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

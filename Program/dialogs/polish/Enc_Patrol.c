void ProcessDialogEvent()
{
	ref NPChar, sld;
	ref arItem;
	aref Link, Diag;
	int i, iShipType, iShipGoods;
	int jewelType;
	string sItemName = "";
	string sItem;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = sti(npchar.EncQty);
	string sTemp = "Patrol" + locations[FindLocation(npchar.location)].index + "_";
	string sGroup = "PatrolGroup_" + locations[FindLocation(npchar.location)].index;
	string sTemp1, sTemp2;

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;

		case "exit_fight":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, sGroup);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "LandEnc_PatrolAfrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_noFight":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.Dialog.CurrentNode = "GoodBye";
				sld.greeting = "soldier_common";
				LAi_SetWarriorType(sld);
				LAi_warrior_DialogEnable(sld, true);
				LAi_group_MoveCharacter(sld, sGroup);				
			}
			LAi_group_SetCheck(sGroup, "LandEnc_PatrolAfrer");
			DialogExit();			
		break;

		case "First Time":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
			}
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
    			if (pchar.nation == npchar.nation)
				{
					dialog.text = RandPhraseSimple("O, patrz, wygląda na to, że ten łajdak podniósł alarm w "+XI_ConvertString("Colony"+npchar.city+"To")+"! Brać "+GetSexPhrase("go","ją")+"!!","Heh, popatrz na to! Kilku "+NationNamePeople(sti(pchar.nation))+" udaje się być wrogami z "+NationNameAblative(sti(npchar.nation))+"! Chwytajcie łotra!!!");
				}
				else
				{
					dialog.text = RandPhraseSimple("Wrogi agent w pobliżu "+XI_ConvertString("Colony"+npchar.city+"Gen")+"! Łapać"+GetSexPhrase("go","ją")+"!!","Hej, popatrzcie, "+NationNamePeople(sti(pchar.nation))+" kręcą się blisko "+XI_ConvertString("Colony"+npchar.city+"To")+"! Natychmiast go złapać!!!");
				}
				link.l1 = RandPhraseSimple("Cóż, możesz spróbować. Jesteśmy tu sami...","Heh, nikt ci tu nie poda pomocnej dłoni.");
				link.l1.go = "exit_fight"; 				
			}
			else
			{				
				// belamour legendary edition
				sTemp1 = "";
				if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation)) sTemp1 = "Vice Admiral! ";
				if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE) sTemp1 = "Your Excellency Governor General! ";
				
				dialog.text = LinkRandPhrase("Pozwól mi się przedstawić! Jestem dowódcą patrolu z "+XI_ConvertString("Colony"+npchar.city+"Gen")+", szukamy zbiegłego skazańca.","Witaj, jestem szefem tego patrolu. Szukamy uciekiniera niewolnika z "+XI_ConvertString("Colony"+npchar.city+"Gen")+".","Pozdrowienia dla ciebie, "+GetAddress_Form(NPChar)+". Mój oddział patroluje teren w pobliżu "+XI_ConvertString("Colony"+npchar.city+"Gen")+".");
				Link.l1 = LinkRandPhrase("Rozumiem. Jak mogę ci pomóc?","Rozumiem. Czy mogę ci w czymś pomóc, "+GetAddress_FormToNPC(NPChar)+"?","Rozumiem. Czy mogę coś dla ciebie zrobić?");
				Link.l1.go = "Node_2";
			}
		break;
		
		case "Node_2":
			dialog.text = RandPhraseSimple("Czy widziałeś coś podejrzanego w okolicy?","Czy spotkałeś kogoś podejrzanego, "+GetAddress_Form(NPChar)+"?");
			Link.l1 = RandPhraseSimple("Nie, nic takiego.","Nie, oficerze, wszystko wydawało się spokojne.");
			Link.l1.go = "Node_3";		
		break;

		case "Node_3":
			Diag.TempNode = "GoodBye";
			dialog.text = RandPhraseSimple("Dobrze, nie będę cię już dłużej zatrzymywać. Do widzenia, "+GetAddress_Form(NPChar)+".","Rozumiem. Do widzenia, więc.");
			Link.l1 = "Powodzenia.";
			Link.l1.go = "exit_noFight";
		break;

		case "GoodBye":
			Diag.TempNode = "GoodBye";
			dialog.text = LinkRandPhrase("Nie rozpraszaj nas od naszego obowiązku.","Chciałbym, żebyś nas zostawił w spokoju!","O, to znowu ty... Idź swoją drogą i nie przeszkadzaj nam.");
			Link.l1 = "Dobrze.";
			Link.l1.go = "Exit";			
		break;
		
		// генератор "A reason to hurry"
		case "Reason_To_Fast_1":
				if(Pchar.Location == Pchar.location.from_sea)
				{
					dialog.text = "Hmm... Nie widziałem cię wcześniej. Kim jesteś?";
					link.l1 = "Jestem tym, na którego czekasz...";
					link.l1.go = "Reason_To_Fast_11";
					link.l2 = "Jestem kapitanem "+GetFullName(pchar)+". Chciałbym wiedzieć, dlaczego tak się spieszyłeś, że prawie zapomniałeś swoich spodni w burdelu...";
					link.l2.go = "Reason_To_Fast_21";
					link.l3 = "Jestem kapitanem "+GetFullName(pchar)+". Tylko spaceruję tutaj, wdychając słoną morską bryzę...";
					link.l3.go = "Reason_To_Fast_31";
				}
				else
				{
					Diag.TempNode = "GoodBye";
					dialog.text = "W końcu przyszedłeś. Myślałem, że nigdy cię więcej nie zobaczę. A kto to jest ten typ z tobą?";
					link.l1 = "Jaki typ?";
					link.l1.go = "Reason_To_Fast_Hunter";
				} 
		break;
		
		case "Reason_To_Fast_Hunter":
			DialogExit();	
			AddDialogExitQuest("ReasonToFast_MeetHunter");
		break;
		
		case "Reason_To_Fast_11":
			dialog.text = "Nie wyglądasz jak ktoś, komu bym zaufał "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+".";
			if(!CheckCharacterItem(pchar,"mapQuest"))
			{
				link.l1 = "Dobrze, powiem mu wszystko, co powiedziałeś.";
				link.l1.go = "Reason_To_Fast_12";
			}	
			link.l2 = "A kim jest ten "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+"?";
			link.l2.go = "Reason_To_Fast_13";
		break;
		
		case "Reason_To_Fast_21":
			dialog.text = "Ciekawość zabiła o wiele więcej ludzi niż koty...";
			link.l1 = "Cóż-cóż!";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfter";	
		break;
		
		case "Reason_To_Fast_31":
			Diag.TempNode = "Reason_To_Fast_GoodBye";
			dialog.text = "Przybywa fala. Lepiej opuść zatokę, tutaj woda podnosi się do poziomu palmy.";
			link.l1 = "Nie ma problemu, dobrze pływam.";
			link.l1.go = "Reason_To_Fast_GoodBye_0";
			pchar.questTemp.ReasonToFast = "MeetPatrolFail";
		break;
		
		case "Reason_To_Fast_12":
			jewelType = sti(pchar.questTemp.ReasonToFast.p4);
			pchar.questTemp.ReasonToFast.item = "jewelry" + jewelType;
			sItem = "jewelry" + jewelType;
			switch (jewelType)
			{
				case 1:
					sItemName = "amethysts";
				break;
				case 2:
					sItemName = "diamonds";
				break;
				case 3:
					sItemName = "rubies";
				break;
				case 4:
					sItemName = "emeralds";
				break;
			}
			pchar.questTemp.ReasonToFast.jewType = sItemName;
			dialog.text = "Dobrze, dobrze. Obiecano 30 "+sItemName+" z tobą?";
			link.l1 = GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" powiedział, że nie było wystarczająco dużo czasu, aby zebrać tyle klejnotów. Kazał mi zaoferować pieniądze zamiast tego.";
			link.l1.go = "Reason_To_Fast_14";
			if (GetCharacterItem(pchar, pchar.questTemp.ReasonToFast.item) >= 30)
			{
				link.l2 = "Proszę bardzo.";
				link.l2.go = "Reason_To_Fast_15";
			}			
		break;
		
		case "Reason_To_Fast_13":
			dialog.text = "Heh! Dowiesz się tego w piekle!";
			link.l1 = "Co za pewność siebie ...";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfter";	
		break;
		
		case "Reason_To_Fast_14":
			dialog.text = "Dobrze, więc jesteś mi winien "+sti(pchar.questTemp.ReasonToFast.p5)+" pesos, jak się umówiliśmy.";
			link.l1 = "Czy to nie jest trochę za dużo?";
			link.l1.go = "Reason_To_Fast_16";
			if(makeint(pchar.money) >= sti(pchar.questTemp.ReasonToFast.p5))
			{
				link.l2 = "Proszę bardzo.";
				link.l2.go = "Reason_To_Fast_17";
			}	
			link.l3 = "Ale nie mam przy sobie tyle pieniędzy!";
			link.l3.go = "Reason_To_Fast_18";	
			AddQuestRecord("ReasonToFast", "9");
			AddQuestUserData("ReasonToFast", "sText", pchar.questTemp.ReasonToFast.jewType);
		break;
		
		case "Reason_To_Fast_15":
			TakeNItems(pchar, pchar.questTemp.ReasonToFast.item, -30); 
			dialog.text = "Wszystko zgodnie z umową. Proszę. Ta mapa została zabrana powieszonemu piratowi, o którym "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" zapytał.";
			link.l1 = "Umowa jest zawarta!";
			link.l1.go = "Reason_To_Fast_15_1";
		break;
		
		case "Reason_To_Fast_15_1":
			Diag.TempNode = "Reason_To_Fast_GoodBye";
			DialogExit();
			AddQuestRecord("ReasonToFast", "10");
			AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM));
			pchar.questTemp.ReasonToFast = "PatrolSuccess_2";
			GiveItem2Character(pchar, "mapQuest"); 
			arItem = ItemsFromID("mapQuest");
			ReasonToFast_GenerateTreasureMap(arItem);	
			DeleteAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther");//можем говорить с губером 
			AddDialogExitQuest("pchar_back_to_player");	
			LAi_LocationFightDisable(&locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)], false);	
		break;
		
		case "Reason_To_Fast_16":
			dialog.text = "Załatwiliśmy sumę z "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_ABL)+" z góry. Nie podoba mi się to ani trochę. Zabijcie"+GetSexPhrase("go","ją")+", chłopaki!";
			link.l1 = "Dobrze, możesz spróbować!";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfter";	
		break;
		
		case "Reason_To_Fast_17":
			pchar.questTemp.ReasonToFast = "PatrolSuccess_1";
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.questTemp.ReasonToFast.p5)));
			pchar.GenQuest.CannotWait = 1; // лочим интерфейс отдыха
			if(CheckAttribute(pchar,"questTemp.ReasonToFast.chain")) DeleteAttribute(pchar,"questTemp.ReasonToFast.chain");
			if(CheckAttribute(pchar,"questTemp.ReasonToFast.ShipName")) DeleteAttribute(pchar,"questTemp.ReasonToFast.ShipName");
			if(CheckAttribute(pchar,"questTemp.ReasonToFast.ShipTypeName")) DeleteAttribute(pchar,"questTemp.ReasonToFast.TypeName");
			switch (sti(pchar.questTemp.ReasonToFast.target))
			{
				case 0: // корабль с товаром
					sTemp1 = generateRandomNameToShip(sti(pchar.questTemp.ReasonToFast.GuardNation));
					iShipType = ReasonToFast_GetVictimShipType();
					iShipGoods = ReasonToFast_GetVictimShipGoods();
					dialog.text = "Świetnie! Teraz przejdźmy do interesów. Przechwyciliśmy to "+GetStrSmallRegister(pchar.questTemp.ReasonToFast.ShipTypeName)+" '"+sTemp1+"' z ładunkiem "+GetGoodsNameAlt(iShipGoods)+", załoga jest już zatrzymana, a 'ładunek' wciąż jest na pokładzie. Załogę zatrudniono wśród nędzarzy w porcie, i nie dotrą do portu dopiero jutro. Możesz z nimi postępować jak chcesz.";
					link.l1 = "W porządku. Przekażę twoje słowa "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_DAT)+".";
					link.l1.go = "Reason_To_Fast_GoodBye_0";
					pchar.questTemp.ReasonToFast.chain = "A0";
					pchar.questTemp.ReasonToFast.ShipName = sTemp1;										
					DeleteAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther");//можем говорить с губером
					AddQuestRecord("ReasonToFast", "11");
					AddQuestUserData("ReasonToFast", "sShipType", pchar.questTemp.ReasonToFast.ShipTypeName);					
					AddQuestUserData("ReasonToFast", "sShipName", sTemp1);
					AddQuestUserData("ReasonToFast", "sGoodsName", GetGoodsNameAlt(iShipGoods));
					ReasonToFast_GenerateVictimShip(iShipType, iShipGoods);					
				break;

				case 1: // сокровища губернатора
					switch(rand(3))
					{
						case 0:
							sTemp1 = "The governor's daughter dowry is";
						break;
						case 1:
							sTemp1 = "Governor's gifts for the Viceroy are";
						break;
						case 2:
							sTemp1 = "The presents for governor's jubilee are";
						break;
						case 3:
							sTemp1 = "Governors 'pensionary' money is";
						break;
					}
					switch(rand(3))
					{
						case 0:
							sTemp2 = "Cheat";
						break;
						case 1:
							sTemp2 = "Mischief";
						break;
						case 2:
							sTemp2 = "Prank";
						break;
						case 3:
							sTemp2 = "Naughty";
						break;
					}
					pchar.questTemp.ReasonToFast.password = sTemp2;
					sTemp2 = generateRandomNameToShip(sti(pchar.questTemp.ReasonToFast.GuardNation));
					dialog.text = "Świetnie! "+sTemp1+" przechowywane w jego boudoir. Statek kurierski przybędzie każdego dnia, ale powinieneś sobie poradzić. Służący to 'nasz' człowiek. Hasło: '"+pchar.questTemp.ReasonToFast.password+"', odpowiedź: '"+sTemp2+"'.'";
					link.l1 = "Dobrze. Przekażę twoje słowo "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_DAT)+".";
					link.l1.go = "Reason_To_Fast_GoodBye_0";
					pchar.questTemp.ReasonToFast.chain = "A1";
					AddQuestRecord("ReasonToFast", "12");
					pchar.questTemp.ReasonToFast.ShipName = sTemp2;
					DeleteAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther");//можем говорить с губером
					
					pchar.quest.ReasonToFast_ClearLakey.win_condition.l1 = "Timer";
					pchar.quest.ReasonToFast_ClearLakey.win_condition.l1.date.day = GetAddingDataDay(0, 0, 2);
					pchar.quest.ReasonToFast_ClearLakey.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
					pchar.quest.ReasonToFast_ClearLakey.win_condition.l1.date.year = GetAddingDataYear(0, 0, 2);
					pchar.quest.ReasonToFast_ClearLakey.function = "ReasonToFast_ClearLakey";
				break;				
			}
		break;
		
		case "Reason_To_Fast_18":
			if(makeint(pchar.money) >= sti(pchar.questTemp.ReasonToFast.p5))
			{
				dialog.text = "Czy próbujesz mnie oszukać?! Ty psie!";
				link.l1 = "Zamknij się, kurwa!";
				link.l1.go = "Reason_To_Fast_ExitFight";
				pchar.questTemp.ReasonToFast = "PatrolAfter";	
			}
			else
			{
				dialog.text = "Wypiłeś! Moje! Pieniądze!... Argh.";
				link.l1 = "Gówno!";
				link.l1.go = "Reason_To_Fast_ExitFight";
				pchar.questTemp.ReasonToFast = "PatrolAfter";	
			}
		break;

		case "Reason_To_Fast_GoodBye_0":
			LAi_SetPlayerType(pchar);
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.Dialog.CurrentNode = "Reason_To_Fast_GoodBye";
				sld.greeting = "soldier_common";
				LAi_SetWarriorType(sld);
				LAi_warrior_DialogEnable(sld, true);
				LAi_group_MoveCharacter(sld, sGroup);				
			}
			pchar.quest.RemovePatrolFromShore.win_condition.l1          = "ExitFromLocation";
			pchar.quest.RemovePatrolFromShore.win_condition.l1.location = pchar.location; 
            pchar.quest.RemovePatrolFromShore.function    				= "ReasonToFast_DeletePatrolFromShore"; 
			DialogExit();			
		break;
		
		case "Reason_To_Fast_GoodBye":
			Diag.TempNode = "Reason_To_Fast_GoodBye";
			dialog.text = "Lepiej opuść zatokę, przypływ już nadchodzi...";
			link.l1 = "Tak, tak, odchodzę.";
			link.l1.go = "Exit";
		break;
		
		case "Reason_To_Fast_ExitFight":
			pchar.questTemp.ReasonToFast.relation = GetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation));
			SetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation), RELATION_ENEMY); 
			
			pchar.GenQuest.HunterScore2Pause = 1; //НЗГ не начисляются
			pchar.GenQuest.ReputationNotChange = 1; //репутацию не менять
			
			chrDisableReloadToLocation = true;
			LAi_SetPlayerType(pchar);
			LAi_LocationFightDisable(&locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)], false);	
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, sGroup);
			}
			if(pchar.questTemp.ReasonToFast == "PatrolAngry")
			{
				sld = CharacterFromID("ReasonToFast_Hunter");
				if(sld != -1) 
				{ 
					LAi_SetWarriorType(sld); 
					LAi_group_MoveCharacter(sld, sGroup);
				}
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			LAi_group_SetCheck(sGroup, "ReasonToFast_PatrolDied");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Reason_To_Fast_AfterHunter1":
			dialog.text = "Czy nie zgodziliśmy się, że posłaniec musi być sam?";
			link.l1 = "Brak koordynacji. Posłaniec zgubił drogę. Jestem zastępstwem.";
			link.l1.go = "Reason_To_Fast_11";
			link.l2 = "I przyszedłem sam, ale nie po to, czego się spodziewasz.";
			link.l2.go = "Reason_To_Fast_AfterHunter2";
		break;
		
		case "Reason_To_Fast_AfterHunter2":
			dialog.text = "No cóż, odnalazłeś mnie w końcu, jest mi przykro za to, co się wydarzy...";
			link.l1 = "Arrgh!";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfterHunter";	
		break;
		
		case "Reason_To_Fast_AfterHunter3":
			dialog.text = "Ty gnojku! Prawie uwierzyłem w to! Strażnicy! Łapcie "+GetSexPhrase("go","ją")+"...";
			link.l1 = "Spróbujcie, wy dranie!";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAngry";	
		break;
		// генератор "A reason to hurry"
	}
}

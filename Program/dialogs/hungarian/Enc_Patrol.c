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
	string sTemp = "Járôr" + locations[FindLocation(npchar.location)].index + "_";
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
					dialog.text = RandPhraseSimple("Ó, nézd csak, úgy tûnik, ez a gazember riadalmat keltett a " + XI_ConvertString("Colony" + npchar.city + "Dat") + "! Fogjátok h"+ GetSexPhrase("im","er") +"!!!", "Heh, ezt nézzétek! Több " + NationNamePeople(sti(pchar.nation))+ " sikerül ellenséggé válni a " + NationNameAblative(sti(npchar.nation)) + "! Fogjátok meg a gazembert!!!");
				}
				else
				{
					dialog.text = RandPhraseSimple("Ellenséges ügynök a " + XI_ConvertString("Colony" + npchar.city + "Gen") + "közelében ! Foglalja el h"+ GetSexPhrase("im","er") +"!!!", "Hé, nézd, " + NationNamePeople(sti(pchar.nation))+ " járkálnak szinte a " + XI_ConvertString("Colony" + npchar.city + "Dat") + "! Azonnal ragadjátok meg!!!");
				}
				link.l1 = RandPhraseSimple("Nos, megpróbálhatod. Egyedül vagyunk itt...", "Heh, itt senki sem nyújt segítô kezet.");
				link.l1.go = "exit_fight"; 				
			}
			else
			{				
				// belamour legendary edition
				sTemp1 = "";
				if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation)) sTemp1 = "Vice Admiral! ";
				if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE) sTemp1 = "Your Excellency Governor General! ";
				
				dialog.text = LinkRandPhrase("Engedjék meg, hogy bemutatkozzam! Járôr vagyok a " + XI_ConvertString("Colony" + npchar.city + "Gen") + ", egy szökött fegyencet keresünk.",
					"Jó napot, én vagyok a járôr vezetôje. Egy szökött rabszolgát keresünk a " + XI_ConvertString("Colony" + npchar.city + "Gen") + ".",
					"Üdvözlöm önöket, " + GetAddress_Form(NPChar) + ". Az osztagom a " + XI_ConvertString("Colony" + npchar.city + "Gen") + "közelében lévô területen járôrözik.");
				Link.l1 = LinkRandPhrase("Nagyon jó. Miben segíthetek?",
				"Nagyon jó. Segíthetek valamiben, " + GetAddress_FormToNPC(NPChar) + "?",
				"Nagyon jó. Van valami, amit tehetek önért?");
				Link.l1.go = "Node_2";
			}
		break;
		
		case "Node_2":
			dialog.text = RandPhraseSimple("Látott valami gyanúsat a kerületben?",
				"Találkozott valakivel, aki gyanúsnak tûnt, " + GetAddress_Form(NPChar) + "?");
			Link.l1 = RandPhraseSimple("Nem, semmi ilyesmi.", "Nem, biztos úr, minden nyugodtnak tûnt.");
			Link.l1.go = "Node_3";		
		break;

		case "Node_3":
			Diag.TempNode = "GoodBye";
			dialog.text = RandPhraseSimple("Rendben, nem fogom tovább feltartani. Viszlát, " + GetAddress_Form(NPChar) + ".",
				"Értem. Akkor viszlát.");
			Link.l1 = "Sok szerencsét.";
			Link.l1.go = "exit_noFight";
		break;

		case "GoodBye":
			Diag.TempNode = "GoodBye";
			dialog.text = LinkRandPhrase("Ne vonja el a figyelmünket a kötelességünkrôl.",
				"Szeretném, ha békén hagynának minket!",
				"Ó, már megint te vagy... Menj a saját utadon, és ne zavarj minket.");
			Link.l1 = "Rendben.";
			Link.l1.go = "Exit";			
		break;
		
		// генератор "A reason to hurry"
		case "Reason_To_Fast_1":
				if(Pchar.Location == Pchar.location.from_sea)
				{
					dialog.text = "Hmm... Még nem láttalak korábban. Ki vagy te?";
					link.l1 = "Én vagyok az, akire vársz...";
					link.l1.go = "Reason_To_Fast_11";
					link.l2 = "Kapitány vagyok " + GetFullName(pchar) + ". Szeretném tudni, hogy miért sietett annyira, hogy majdnem a bordélyházban felejtette a nadrágját...";
					link.l2.go = "Reason_To_Fast_21";
					link.l3 = "Kapitány vagyok " + GetFullName(pchar) + ". Csak sétálgatok itt, belélegezve a sós tengeri szellôt...";
					link.l3.go = "Reason_To_Fast_31";
				}
				else
				{
					Diag.TempNode = "GoodBye";
					dialog.text = "Végre eljöttél. Azt hittem, soha többé nem látlak. És ki az a típus veled?";
					link.l1 = "Milyen típus?";
					link.l1.go = "Reason_To_Fast_Hunter";
				} 
		break;
		
		case "Reason_To_Fast_Hunter":
			DialogExit();	
			AddDialogExitQuest("ReasonToFast_MeetHunter");
		break;
		
		case "Reason_To_Fast_11":
			dialog.text = "Nem úgy nézel ki, mint akiben megbíznék " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + ".";
			if(!CheckCharacterItem(pchar,"mapQuest"))
			{
				link.l1 = "Rendben, elmondok neki mindent, amit mondtál.";
				link.l1.go = "Reason_To_Fast_12";
			}	
			link.l2 = "És ki ez a " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + "?";
			link.l2.go = "Reason_To_Fast_13";
		break;
		
		case "Reason_To_Fast_21":
			dialog.text = "A kíváncsiság sokkal több embert ölt meg, mint a macskák...";
			link.l1 = "Nocsak, nocsak!";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfter";	
		break;
		
		case "Reason_To_Fast_31":
			Diag.TempNode = "Reason_To_Fast_GoodBye";
			dialog.text = "Jön a dagály. Jobb, ha elhagyod az öblöt, a víz itt a pálmafák szintjéig emelkedik.";
			link.l1 = "Nem gond, jó úszó vagyok.";
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
					sItemName = "ametisztek";
				break;
				case 2:
					sItemName = "gyémánt";
				break;
				case 3:
					sItemName = "rubin";
				break;
				case 4:
					sItemName = "smaragdok";
				break;
			}
			pchar.questTemp.ReasonToFast.jewType = sItemName;
			dialog.text = "Rendben, rendben. Az ígért 30 " + sItemName + " veled van?";
			link.l1 = GetName(NAMETYPE_MAIN , pchar.questTemp.ReasonToFast.p3, NAME_NOM) + " Azt mondta, hogy nincs elég idô ennyi drágakô összegyûjtésére. Megparancsolta, hogy inkább pénzt ajánljak fel.";
			link.l1.go = "Reason_To_Fast_14";
			if (GetCharacterItem(pchar, pchar.questTemp.ReasonToFast.item) >= 30)
			{
				link.l2 = "Tessék, tessék.";
				link.l2.go = "Reason_To_Fast_15";
			}			
		break;
		
		case "Reason_To_Fast_13":
			dialog.text = "Heh! A pokolban fogod megtudni!";
			link.l1 = "Micsoda önbizalom...";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfter";	
		break;
		
		case "Reason_To_Fast_14":
			dialog.text = "Rendben, akkor tartozol nekem " + sti(pchar.questTemp.ReasonToFast.p5) + " pezóval, ahogy megegyeztünk.";
			link.l1 = "Nem túl sok ez egy kicsit?";
			link.l1.go = "Reason_To_Fast_16";
			if(makeint(pchar.money) >= sti(pchar.questTemp.ReasonToFast.p5))
			{
				link.l2 = "Tessék, tessék.";
				link.l2.go = "Reason_To_Fast_17";
			}	
			link.l3 = "De nincs nálam ennyi pénz!";
			link.l3.go = "Reason_To_Fast_18";	
			AddQuestRecord("ReasonToFast", "9");
			AddQuestUserData("ReasonToFast", "sText", pchar.questTemp.ReasonToFast.jewType);
		break;
		
		case "Reason_To_Fast_15":
			TakeNItems(pchar, pchar.questTemp.ReasonToFast.item, -30); 
			dialog.text = "Minden a megállapodásnak megfelelôen történik. Tessék. Ezt a térképet a felakasztott kalózról vették, akirôl a "  + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + " érdeklôdött.";
			link.l1 = "Az üzlet megköttetett!";
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
			dialog.text = "Az összeget a " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_ABL) + " elôzetesen rendeztük. Egy kicsit sem tetszik. Kill h"+ GetSexPhrase("im","er") +", fiúk!";
			link.l1 = "Rendben, megpróbálhatjátok!";
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
					dialog.text = "Kiváló! Most pedig térjünk rá az üzletre. Elfogtuk azt a " + GetStrSmallRegister(pchar.questTemp.ReasonToFast.ShipTypeName) +" '" + sTemp1 + "' rakományt " + GetGoodsNameAlt(iShipGoods) + ", a legénységet már feltartóztattuk, és a 'rakomány' még mindig a fedélzeten van. A legénységet a kikötôben lévô lecsúszottak közül vették fel, és csak holnap fognak kikötni. Úgy bánik velük, ahogy akar.";
					link.l1 = "Jól van, rendben. Elmondom a szavaidat " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT) + ".";
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
							sTemp1 = "A kormányzó lányának hozománya...";
						break;
						case 1:
							sTemp1 = "A kormányzó ajándéka az alkirálynak.";
						break;
						case 2:
							sTemp1 = "A kormányzó jubileumi ajándékai a következôk.";
						break;
						case 3:
							sTemp1 = "A kormányzók 'nyugdíjpénze' pénzét";
						break;
					}
					switch(rand(3))
					{
						case 0:
							sTemp2 = "Csalás";
						break;
						case 1:
							sTemp2 = "Csínytevés";
						break;
						case 2:
							sTemp2 = "Tréfa";
						break;
						case 3:
							sTemp2 = "Csintalan";
						break;
					}
					pchar.questTemp.ReasonToFast.password = sTemp2;
					sTemp2 = generateRandomNameToShip(sti(pchar.questTemp.ReasonToFast.GuardNation));
					dialog.text = "Kiváló! " + sTemp1 + " tartotta a budoárjában. A futárhajó bármelyik nap megérkezhet, de még így is sikerülnie kell. A lakáj 'our' man. Password: '"+ pchar.questTemp.ReasonToFast.password +"', reply: '"+ sTemp2 +"'.";
					link.l1 = "Jól van, rendben. Átadom a szavát " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT) + ".";
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
				dialog.text = "Át akarsz verni?! Te kutya!";
				link.l1 = "Fogd be a pofád!";
				link.l1.go = "Reason_To_Fast_ExitFight";
				pchar.questTemp.ReasonToFast = "PatrolAfter";	
			}
			else
			{
				dialog.text = "Te megittad! A mindenit! A pénzem! Argh.";
				link.l1 = "Basszus!";
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
			dialog.text = "Jobb, ha elhagyod az öblöt, már jön a dagály...";
			link.l1 = "Igen, igen, elmegyek.";
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
			dialog.text = "Nem abban állapodtunk meg, hogy a hírnöknek egyedül kell lennie?";
			link.l1 = "A koordináció hiánya. A hírnök eltévedt. Én vagyok a helyettesítôje.";
			link.l1.go = "Reason_To_Fast_11";
			link.l2 = "És egyedül jöttem, de nem azért, amire ti számítotok.";
			link.l2.go = "Reason_To_Fast_AfterHunter2";
		break;
		
		case "Reason_To_Fast_AfterHunter2":
			dialog.text = "Szóval, mégiscsak megtaláltál, sajnálom, ami történni fog...";
			link.l1 = "Arrgh!";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfterHunter";	
		break;
		
		case "Reason_To_Fast_AfterHunter3":
			dialog.text = "Te pöcs! Majdnem elhittem ezt! Ôrség! Fogjátok el h"+ GetSexPhrase("im","er") +"...";
			link.l1 = "Próbáljátok meg, rohadékok!";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAngry";	
		break;
		// генератор "A reason to hurry"
	}
}

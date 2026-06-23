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
	int iTemp = int(npchar.EncQty);
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
			if (GetNationRelation2MainCharacter(int(NPChar.nation)) == RELATION_ENEMY && int(NPChar.nation) != PIRATE)
			{
    			if (pchar.nation == npchar.nation)
				{
					dialog.text = RandPhraseSimple("Oh schaut mal, es scheint, dieser Schurke hat Alarm geschlagen in "+XI_ConvertString("Colony"+npchar.city+"Dat")+"! Ergreife h"+GetSexPhrase("ich bin","er")+"!!","Heh, schau dir das an! Mehrere "+NationNamePeople(int(pchar.nation))+" schaffe es, Feinde zu sein mit "+NationNameAblative(int(npchar.nation))+"! Ergreift den Schurken!!!");
				}
				else
				{
					dialog.text = RandPhraseSimple("Feindlicher Agent in der Nähe "+XI_ConvertString("Colony"+npchar.city+"Gen")+"! Ergreift h"+GetSexPhrase("ich bin","er")+"!!","He, schau mal, "+NationNamePeople(int(pchar.nation))+" laufen fast herum in "+XI_ConvertString("Colony"+npchar.city+"Dat")+"! Sofort pack ihn!!!");
				}
				link.l1 = RandPhraseSimple("Nun, du kannst es versuchen. Wir sind hier alleine...","Heh, niemand wird dir hier eine helfende Hand reichen.");
				link.l1.go = "exit_fight"; 				
			}
			else
			{				
				// belamour legendary edition
				sTemp1 = "";
				if(isMainCharacterPatented() && int(Items[int(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == int(Items[int(pchar.EquipedPatentId)].Nation)) sTemp1 = "Vice Admiral! ";
				if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE) sTemp1 = "Your Excellency Governor General! ";
				
				dialog.text = LinkRandPhrase("Erlauben Sie mir, mich vorzustellen! Ich bin ein Patrouillenoffizier aus "+XI_ConvertString("Colony"+npchar.city+"Gen")+", wir suchen einen entflohenen Sträfling.","Hallo, ich bin der Anführer dieser Patrouille. Wir suchen nach einem entflohenen Sklaven aus "+XI_ConvertString("Colony"+npchar.city+"Geschlecht")+".","Grüße an dich, "+GetAddress_Form(NPChar)+". Meine Abteilung patrouilliert in der Nähe des Territoriums "+XI_ConvertString("Colony"+npchar.city+"Gen")+".");
				Link.l1 = LinkRandPhrase("Sehr gut. Wie kann ich Ihnen helfen?","Sehr gut. Kann ich Ihnen mit etwas helfen, "+GetAddress_FormToNPC(NPChar)+"?","Sehr gut. Gibt es etwas, was ich für Sie tun kann?");
				Link.l1.go = "Node_2";
			}
		break;
		
		case "Node_2":
			dialog.text = RandPhraseSimple("Haben Sie etwas Verdächtiges im Bezirk gesehen?","Haben Sie jemanden getroffen, der verdächtig aussieht, "+GetAddress_Form(NPChar)+"?");
			Link.l1 = RandPhraseSimple("Nein, nichts dergleichen.","Nein, Offizier, alles schien ruhig zu sein.");
			Link.l1.go = "Node_3";		
		break;

		case "Node_3":
			Diag.TempNode = "GoodBye";
			dialog.text = RandPhraseSimple("Gut, ich werde dich nicht länger aufhalten. Auf Wiedersehen, "+GetAddress_Form(NPChar)+".","Ich verstehe. Auf Wiedersehen, dann.");
			Link.l1 = "Viel Glück.";
			Link.l1.go = "exit_noFight";
		break;

		case "GoodBye":
			Diag.TempNode = "GoodBye";
			dialog.text = LinkRandPhrase("Stör uns nicht bei unserer Pflicht.","Ich möchte, dass du uns in Ruhe lässt!","Oh, das bist du schon wieder... Geh deinen eigenen Weg und stör uns nicht.");
			Link.l1 = "Gut.";
			Link.l1.go = "Exit";			
		break;
		
		// генератор "A reason to hurry"
		case "Reason_To_Fast_1":
				if(Pchar.Location == Pchar.location.from_sea)
				{
					dialog.text = "Hmm... Ich habe dich noch nie gesehen. Wer bist du?";
					link.l1 = "Ich bin derjenige, auf den du wartest...";
					link.l1.go = "Reason_To_Fast_11";
					link.l2 = "Ich bin Kapitän "+GetFullName(pchar)+". Ich würde gerne wissen, warum Sie in solcher Eile waren, dass Sie fast Ihre Hosen im Bordell vergessen hätten...";
					link.l2.go = "Reason_To_Fast_21";
					link.l3 = "Ich bin Kapitän "+GetFullName(pchar)+". Ich mache nur einen Spaziergang hier, atme die salzige Meeresbrise ein...";
					link.l3.go = "Reason_To_Fast_31";
				}
				else
				{
					Diag.TempNode = "GoodBye";
					dialog.text = "Endlich bist du gekommen. Ich dachte, ich würde dich nie wieder sehen. Und wer ist dieser Typ mit dir?";
					link.l1 = "Welche Art?";
					link.l1.go = "Reason_To_Fast_Hunter";
				} 
		break;
		
		case "Reason_To_Fast_Hunter":
			DialogExit();	
			AddDialogExitQuest("ReasonToFast_MeetHunter");
		break;
		
		case "Reason_To_Fast_11":
			dialog.text = "Du siehst nicht gerade wie jemand aus, dem ich vertrauen würde "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+".";
			if(!CheckCharacterItem(pchar,"mapQuest"))
			{
				link.l1 = "In Ordnung, ich werde ihm alles erzählen, was du gesagt hast.";
				link.l1.go = "Reason_To_Fast_12";
			}	
			link.l2 = "Und wer ist das "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+"?";
			link.l2.go = "Reason_To_Fast_13";
		break;
		
		case "Reason_To_Fast_21":
			dialog.text = "Die Neugier hat schon viel mehr Menschen getötet als Katzen...";
			link.l1 = "So-so!";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfter";	
		break;
		
		case "Reason_To_Fast_31":
			Diag.TempNode = "Reason_To_Fast_GoodBye";
			dialog.text = "Die Flut kommt. Du solltest die Bucht verlassen, das Wasser hier steigt bis zur Palme.";
			link.l1 = "Kein Problem, ich bin ein guter Schwimmer.";
			link.l1.go = "Reason_To_Fast_GoodBye_0";
			pchar.questTemp.ReasonToFast = "MeetPatrolFail";
		break;
		
		case "Reason_To_Fast_12":
			jewelType = int(pchar.questTemp.ReasonToFast.p4);
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
			dialog.text = "In Ordnung, in Ordnung. Sind versprochen 30 "+sItemName+" mit dir?";
			link.l1 = GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" sagte, dass nicht genug Zeit vorhanden war, um so viele Edelsteine zu sammeln. Er befahl mir, stattdessen Geld anzubieten.";
			link.l1.go = "Reason_To_Fast_14";
			if (GetCharacterItem(pchar, pchar.questTemp.ReasonToFast.item) >= 30)
			{
				link.l2 = "Hier, bitte.";
				link.l2.go = "Reason_To_Fast_15";
			}			
		break;
		
		case "Reason_To_Fast_13":
			dialog.text = "Heh! Du wirst es in der Hölle erfahren!";
			link.l1 = "Welch ein Selbstvertrauen ...";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfter";	
		break;
		
		case "Reason_To_Fast_14":
			dialog.text = "Gut, dann schuldest du mir "+int(pchar.questTemp.ReasonToFast.p5)+" Pesos, wie wir vereinbart hatten.";
			link.l1 = "Ist das nicht ein bisschen zu viel?";
			link.l1.go = "Reason_To_Fast_16";
			if(int(pchar.money) >= int(pchar.questTemp.ReasonToFast.p5))
			{
				link.l2 = "Hier, bitte.";
				link.l2.go = "Reason_To_Fast_17";
			}	
			link.l3 = "Aber ich habe nicht so viel Geld bei mir!";
			link.l3.go = "Reason_To_Fast_18";	
			AddQuestRecord("ReasonToFast", "9");
			AddQuestUserData("ReasonToFast", "sText", pchar.questTemp.ReasonToFast.jewType);
		break;
		
		case "Reason_To_Fast_15":
			TakeNItems(pchar, pchar.questTemp.ReasonToFast.item, -30); 
			dialog.text = "Alles ist gemäß der Vereinbarung. Hier hast du. Diese Karte wurde von dem gehängten Piraten genommen, von dem "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" hatte nachgefragt.";
			link.l1 = "Der Handel ist abgeschlossen!";
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
			dialog.text = "Wir haben die Summe beglichen mit "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_ABL)+" im Voraus. Es gefällt mir gar nicht. Töte h"+GetSexPhrase("ich bin","er")+", Jungs!";
			link.l1 = "In Ordnung, du darfst es versuchen!";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfter";	
		break;
		
		case "Reason_To_Fast_17":
			pchar.questTemp.ReasonToFast = "PatrolSuccess_1";
			AddMoneyToCharacter(pchar, -int(int(pchar.questTemp.ReasonToFast.p5)));
			pchar.GenQuest.CannotWait = 1; // лочим интерфейс отдыха
			if(CheckAttribute(pchar,"questTemp.ReasonToFast.chain")) DeleteAttribute(pchar,"questTemp.ReasonToFast.chain");
			if(CheckAttribute(pchar,"questTemp.ReasonToFast.ShipName")) DeleteAttribute(pchar,"questTemp.ReasonToFast.ShipName");
			if(CheckAttribute(pchar,"questTemp.ReasonToFast.ShipTypeName")) DeleteAttribute(pchar,"questTemp.ReasonToFast.TypeName");
			switch (int(pchar.questTemp.ReasonToFast.target))
			{
				case 0: // корабль с товаром
					sTemp1 = generateRandomNameToShip(int(pchar.questTemp.ReasonToFast.GuardNation));
					iShipType = ReasonToFast_GetVictimShipType();
					iShipGoods = ReasonToFast_GetVictimShipGoods();
					dialog.text = "Ausgezeichnet! Jetzt kommen wir zur Sache. Wir haben das abgefangen "+GetStrSmallRegister(pchar.questTemp.ReasonToFast.ShipTypeName)+" '"+sTemp1+"' mit einer Ladung von "+GetGoodsNameAlt(iShipGoods)+", die Mannschaft ist bereits festgenommen, und die 'Fracht' befindet sich noch an Bord. Die Mannschaft wurde unter den heruntergekommenen im Hafen angeworben, und sie werden erst morgen in den Hafen kommen. Sie können mit ihnen umgehen, wie Sie wollen.";
					link.l1 = "In Ordnung. Ich werde Ihre Worte übermitteln "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_DAT)+".";
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
					sTemp2 = generateRandomNameToShip(int(pchar.questTemp.ReasonToFast.GuardNation));
					dialog.text = "Ausgezeichnet! "+sTemp1+" in seinem Boudoir aufbewahrt. Das Kurierschiff wird jeden Tag eintreffen, aber du solltest es noch schaffen. Der Lakai ist 'unser' Mann. Passwort: '"+pchar.questTemp.ReasonToFast.password+"', Antwort: '"+sTemp2+"'. ";
					link.l1 = "In Ordnung. Ich werde deine Worte weiterleiten "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_DAT)+".";
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
			if(int(pchar.money) >= int(pchar.questTemp.ReasonToFast.p5))
			{
				dialog.text = "Versuchst du mich zu betrügen?! Du Hund!";
				link.l1 = "Halt die verdammte Klappe!";
				link.l1.go = "Reason_To_Fast_ExitFight";
				pchar.questTemp.ReasonToFast = "PatrolAfter";	
			}
			else
			{
				dialog.text = "Du hast! Mein! Geld!... Argh. weggetrunken.";
				link.l1 = "Scheiße!";
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
			dialog.text = "Du solltest die Bucht besser verlassen, die Flut kommt schon...";
			link.l1 = "Ja, ja, ich gehe.";
			link.l1.go = "Exit";
		break;
		
		case "Reason_To_Fast_ExitFight":
			pchar.questTemp.ReasonToFast.relation = GetNationRelation2MainCharacter(int(pchar.questTemp.ReasonToFast.GuardNation));
			SetNationRelation2MainCharacter(int(pchar.questTemp.ReasonToFast.GuardNation), RELATION_ENEMY);
			
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
			dialog.text = "Haben wir nicht vereinbart, dass der Bote allein sein muss?";
			link.l1 = "Mangel an Koordination. Der Bote hat seinen Weg verloren. Ich bin der Ersatz.";
			link.l1.go = "Reason_To_Fast_11";
			link.l2 = "Und ich bin alleine gekommen, aber nicht für das, was du erwartest.";
			link.l2.go = "Reason_To_Fast_AfterHunter2";
		break;
		
		case "Reason_To_Fast_AfterHunter2":
			dialog.text = "Also, du hast mich also doch aufgespürt, es tut mir leid für das, was passieren wird...";
			link.l1 = "Arrgh!";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfterHunter";	
		break;
		
		case "Reason_To_Fast_AfterHunter3":
			dialog.text = "Du Mistkerl! Ich habe fast daran geglaubt! Wachen! Packt ihn!"+GetSexPhrase("ich bin","er")+"...";
			link.l1 = "Versucht es, ihr Bastarde!";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAngry";	
		break;
		// генератор "A reason to hurry"
	}
}

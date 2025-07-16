// городские тюрьмы
void ProcessDialogEvent()
{
	int amount, iGunQty, iGunGoods, iGunPrice, iTemp;
	int iTest;
	ref NPChar, sld, location;
	ref arItem;
	ref rColony;
	aref Link, NextDiag;
	string sTemp;
	float locx, locy, locz;
	bool  ok;
	// belamour для ночного приключения -->
	int i;
	int SoldQty = 0;
	int SoldNum[10];
	// <--

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Prison\" + NPChar.City + "_Prison.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "NoMoreTalkExit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;
		//---------------- Начальник тюрьмы ------------------
		case "First_officer":
			dialog.text = RandPhraseSimple("Ich bin der Gefängniswärter. Was brauchst du hier?","Was brauchst du? Warum bist du ins Gefängnis gekommen?");
			NextDiag.TempNode = "First_officer";
			if(startHeroType == 4 && NPChar.location == "SantaCatalina_prison" && !CheckAttribute(pchar, "questTemp.HelenSCprison"))
			{
				dialog.text = "Frau MacArthur? Überrascht, Sie zu sehen. Wir haben meines Wissens noch niemanden aus Ihrer Crew oder von Kapitän Swenson festgenommen.";
				link.l1 = "Ich bin nur hier, Herr. Ist das nicht erlaubt? Ich habe nicht hinter Ihrem Rücken mit den Gefangenen geplaudert.";
				link.l1.go = "Helen_meeting";
				pchar.questTemp.HelenSCprison = true;
				break;
			}
			// --> Sinistra Длинные тени старых грехов
			if(CheckAttribute(pchar,"questTemp.DTSG_AntiguaTrevoga") && npchar.city == "SentJons")
			{
				dialog.text = "Ach, Charles de Maure... Du solltest verhaftet und mit deinem Offizier zusammengeführt werden, aber... der Vorfall bei der Bank wurde als bedauerliches Missverständnis eingestuft.";
				link.l1 = "Ich mag, wie Sie dieses Gespräch begonnen haben, Herr. "+GetFullName(NPChar)+". Ich kann alles erklären.";
				link.l1.go = "DTSG_AntiguaTrevoga_2";
				break;
			}
			// <-- Длинные тени старых грехов
			
			//--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "jailskiper")
			{
				link.l1 = "Offizier, ich habe gehört, dass ein Mann namens Folke Deluc in Ihrem Gefängnis ist. Gibt es etwas, was ich tun kann, um ihn freizulassen?";
                link.l1.go = "Sharlie";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "freeskiper")
			{
				link.l1 = "Offizier, ich bin es wieder wegen des Gefangenen Folke Deluc. Ich habe die Rechte an seiner Schuld gekauft und möchte, dass dieser Mann freigelassen und mir übergeben wird. Hier sind seine Schuldpapiere, schauen Sie mal.";
                link.l1.go = "Sharlie_3";
				break;
			}	
			//<-- Бремя гасконца
			
			//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
			// Офицер с патентом
			if(IsOfficerFullEquip())
			{
				dialog.text = "Grüße, Kapitän. Was führt Sie hierher?";
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "Grüße, Vizeadmiral! Wie kann ich Ihnen helfen?";
			}
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				dialog.text = "Eure Exzellenz, Generalgouverneur! Haben Sie irgendwelche Befehle?";
			}
			// <-- legendary edition
			link.l1 = "Oh, nichts Besonderes, du weißt, nur ein bisschen in der Stadt herumsehen, also bin ich hier zufällig hingewandert.";
			link.l1.go = "exit";
			link.l2 = "Ich wollte über einige Geschäfte sprechen.";
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakFort"))
			{
				if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l2.go = "F_ShipLetters_1";
				}
				else
				{
					link.l2.go = "quests";
				}		
			}
			else
			{
				if(CheckAttribute(pchar,"questTemp.ReasonToFast") && !CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
				{
					link.l2.go = "ReasonToFast_Prison1";
				}
				else
				{
					link.l2.go = "quests";
				}	
			}
			if (!sti(pchar.questTemp.jailCanMove))
			{
				link.l4 = "Ich möchte ins Gefängnis gehen.";
				link.l4.go = "ForGoodMove";		
			}
			if (CheckAttribute(pchar, "questTemp.jailCanMove.City") && npchar.city == pchar.questTemp.jailCanMove.City)
			{
				link.l5 = "Hallo, könnten Sie mir sagen, welches Verbrechen der Gefangene namens "+GetFullName(characterFromId(pchar.questTemp.jailCanMove.prisonerId))+"verbüßt eine Strafe für?";
				link.l5.go = "KnowAboutPrisoner";	
			}
			
			if(CheckAttribute(pchar,"GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
			{
				if(!CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
				{
					bool zMsm = (CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour")) && (!CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor"));
					if(pchar.GenQuest.CaptainComission == "MayorTalkBad" || zMsm) //говорил с губером и отказался или узнал слухи, но не говорил с губером
					{
						link.l6 = "Ich habe gehört, dass der ehemalige Kapitän einer Patrouille "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Akz"))+" "+pchar.GenQuest.CaptainComission.Name+" wird hier in Gewahrsam gehalten. Kann ich mit ihm sprechen?";
						link.l6.go = "CapComission_PrisonBad1";
					}
					if(pchar.GenQuest.CaptainComission == "MayorTalkGood")
					{
						link.l6 = "Ich "+GetFullName(pchar)+", im Auftrag und auf Anweisung des Gouverneurs "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Gen")+"muss mit dem ehemaligen Kapitän sprechen "+pchar.GenQuest.CaptainComission.Name+".";
						link.l6.go = "CapComission_PrisonGood1";
					}
				}	
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if(pchar.GenQuest.EncGirl.Father == "fort_keeper"  && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = "Es geht um Ihre Tochter...";
						link.l9.go = "EncGirl_1";
					}
				}
			}
			
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "begin" && NPChar.location == pchar.GenQuest.Marginpassenger.City + "_prison")
			{
				link.l12 = "Ich habe ein Anliegen an Sie, Offizier. Ich glaube, es könnte Sie interessieren, da es mit Ihren Pflichten zusammenhängt.";
				link.l12.go = "Marginpassenger";
			}
			
			// Warship, 16.05.11. Генер "Justice for sale".
			if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.PrisonWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_prison")
			{
				link.l13 = "Ich möchte mit dir über einen bestimmten Mann sprechen - "+PChar.GenQuest.JusticeOnSale.SmugglerName+". Er ist dein Gefangener, wenn ich mich nicht irre.";
				link.l13.go = "JusticeOnSale_1";
			}
			
			// --> belamour ночной приключенец
			if(CheckAttribute(pchar,"GenQuest.NightAdventureToJail"))
			{
				link.l14 = "Hallo Offizier. Soweit ich weiß, wurde vor einiger Zeit ein betrunkener Bürger festgenommen, nachdem er versucht hatte, auf den Straßen mit einem Wächter zu kämpfen."; 
				link.l14.go = "NightAdventure_CitizenHomie";
			}
			
			if(CheckAttribute(pchar,"GenQuest.NightAdventureToPrisoner"))
			{
				link.l14 = "Offizier, ich habe mit dem Wachposten gesprochen und er hat seine Behauptungen zurückgezogen. Hier ist ein Gutschein von ihm."; 
				link.l14.go = "NightAdventure_HomieToPrisoner";
			}
			// <-- приключенец
			NextDiag.TempNode = "First_officer";
		break;
		
		// --> Jason Похититель
		case "Marginpassenger":
			dialog.text = "Ja? Was ist es, das du mir sagen willst?";
			link.l1 = "In letzter Zeit wurde ich auf der Straße von "+pchar.GenQuest.Marginpassenger.Name+" der mir angeboten hat, eine schmutzige Tat zu arrangieren: die Entführung und dann das Lösegeld einer Person namens "+pchar.GenQuest.Marginpassenger.q1Name+". Es ist "+pchar.GenQuest.Marginpassenger.Text+"...";
			link.l1.go = "Marginpassenger_1";
		break;
		
		case "Marginpassenger_1":
			dialog.text = "Hmm... Das ist sehr interessant - bitte fahren Sie fort!";
			link.l1 = "Er kannte den Namen des Schiffes, auf dem "+pchar.GenQuest.Marginpassenger.q1Name+" hatte vor zu segeln. Es ist "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType),"Name")))+" genannt '"+pchar.GenQuest.Marginpassenger.ShipName+"'. Außerdem hat er mir die Zeit gesagt, wann dieses Schiff ablegen sollte.";
			link.l1.go = "Marginpassenger_2";
		break;
	
		case "Marginpassenger_2":
			dialog.text = "Und er hat vorgeschlagen, dass du den Passagier fängst und dann Lösegeld für ihn verlangst?";
			link.l1 = "Genau. Um Lösegeld zu sammeln, würde ich nach "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Targetcity)+", zu einer bestimmten Person namens "+pchar.GenQuest.Marginpassenger.q2Name+". Ich habe ihn für diese Information bezahlt, aber natürlich hatte ich nicht vor, diese Person zu entführen.";
			link.l1.go = "Marginpassenger_3";
		break;
		
		case "Marginpassenger_3":
			dialog.text = "Also hast du dich entschieden, mich zu besuchen und es mir zu sagen?";
			link.l1 = "Genau. Ich bin sicher, dass die Handlungen dieses Schurken die Bürger Ihrer Stadt bedrohen, und ich hoffe, dass Sie angemessene Maßnahmen ergreifen werden.";
			link.l1.go = "Marginpassenger_4";
		break;
		
		case "Marginpassenger_4":
			dialog.text = "Du hattest völlig recht, als du zu mir kamst, "+GetAddress_Form(NPChar)+"! Dieser Schurke, "+pchar.GenQuest.Marginpassenger.Name+", steht schon lange unter unserer Beobachtung. Ich werde ermitteln, und wenn alles, was Sie gesagt haben, bestätigt wird, werden wir diesen Bastard für ein halbes Jahr hinter Gitter werfen. Das wird ihm beibringen, solche Pläne gegen angesehene Bürger zu schmieden!\nNun, für Ihre Ehrlichkeit und Ihre Bereitschaft, einer guten Sache zu dienen, werde ich natürlich unserem Gouverneur von Ihrer Tat berichten, was natürlich seine Einstellung zu Ihnen beeinflussen wird... Sie wissen schon, auf positive Weise. Danke für Ihre Hilfe, Kapitän!";
			link.l1 = "Hmm... Gern geschehen, es war mir ein Vergnügen zu helfen. Auf Wiedersehen!";
			link.l1.go = "Marginpassenger_5";
		break;
		
		case "Marginpassenger_5":
			DialogExit();
			NextDiag.CurrentNode = "First_officer";
			AddQuestRecord("Marginpassenger", "20");
			AddQuestUserData("Marginpassenger", "sName", pchar.GenQuest.Marginpassenger.Name);
			CloseQuestHeader("Marginpassenger");
			pchar.quest.Marginpassenger_InWorld.over = "yes"; //снять таймер
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 5);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			ChangeContrabandRelation(pchar, -25);
			if (GetCharacterIndex("MarginCap") != -1)
			{
				sld = characterFromId("MarginCap");
				sld.lifeday = 0;
				Map_ReleaseQuestEncounter(sld.id);
				Group_DeleteGroup("Sea_MarginCap1");
			}
		break;
		//<-- Похититель

		case "EncGirl_1":
			dialog.text = "Ich bin ganz Ohr.";
			link.l1 = "Ich habe Ihren Flüchtling gebracht.";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "Oh, Kapitän, vielen Dank! Wie geht es ihr? Ist sie verletzt? Warum ist sie weggelaufen? Warum?\nVersteht sie nicht? Der Bräutigam ist ein reicher und wichtiger Mann! Jugend ist naiv und töricht... sogar grausam. Denken Sie daran!";
			link.l1 = "Nun, du bist ihr Vater und die endgültige Entscheidung liegt bei dir, aber ich würde mit der Hochzeit nicht überstürzen...";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "Was wissen Sie? Haben Sie eigene Kinder? Nein? Wenn Sie eines haben, kommen Sie zu mir und wir werden reden.\nIch habe eine Belohnung versprochen für jeden, der sie zu ihrer Familie zurückbringt.";
			link.l1 = "Danke. Du solltest ein Auge auf sie haben. Ich habe das Gefühl, dass sie nicht dabei stehenbleiben wird.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;
		
		// ------------------------- Повод для спешки -----------------------------
		case "ReasonToFast_Prison1":
			pchar.questTemp.ReasonToFast.SpeakOther = true;
			dialog.text = "Ich bin ganz Ohr, Kapitän.";
			link.l1 = "Ich möchte Ihnen von einer kriminellen Verschwörung zwischen einem Offizier Ihrer Garnison und Piraten erzählen (erklärt die Angelegenheit).";
			if(makeint(pchar.reputation.nobility) < 41)
			{
				link.l1.go = "ReasonToFast_Prison_BadRep";			
			}
			else
			{
				link.l1.go = "ReasonToFast_Prison_GoodRep";	
			}
		break;
		case "ReasonToFast_Prison_GoodRep":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 
				// вилка_А
				dialog.text = "Danke,"+GetSexPhrase("Herr","Fräulein")+"! Ich werde sofort den Befehl zur Verhaftung des Schurken geben.\nJedoch haben Sie Kosten verursacht und die städtischen Kassen, ach, sind leer...";
				link.l1 = "Herr! Ich habe es nicht für das Geld getan...";
				link.l1.go = "ReasonToFast_Prison_GoodRep_11";
				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = "Danke dir, "+GetSexPhrase("Herr","Fräulein")+"! Ich werde sofort den Befehl zur Festnahme des Schurken geben.\nDenk nur! Wir wollten ihn für den hervorragenden Dienst mit einer persönlichen Waffe belohnen. Wie schön, dass alles aufgeklärt ist, und ich habe nichts zu meiner Schande!";
				link.l1 = "Immer froh, Gerechtigkeit zu dienen.";
				link.l1.go = "ReasonToFast_Prison_GoodRep_21";			
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = "Mi"+GetSexPhrase("Ster","ss")+"! Wir hatten diesen Offizier und seine Schurken schon lange der schmutzigen Taten verdächtigt, aber ich glaube, du hast vorschnell gehandelt, als du sie ohne Zeugen behandelt hast.";
				link.l1 = "Herr! Aber ich musste mich verteidigen...";
				link.l1.go = "ReasonToFast_Prison_GoodRep_31";	
				pchar.questTemp.ReasonToFast.speakAfterPatrolDied = true;	
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";	
			}
		break;
		
		case "ReasonToFast_Prison_BadRep":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 
				// вилка_А
				dialog.text = "Kapitän, ist Ihnen bewusst, was Sie getan haben?! Wir haben über einen Monat versucht, diese Falle aufzustellen! Und jetzt, nur zu Ihrer Unterhaltung, haben Sie das Treffen unserer Patrouille mit dem Boten ruiniert "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_GEN)+" und jetzt kommst du hierher um zu prahlen?! Vielleicht kannst du mir jetzt erklären, wie ich all die Ausgaben und Kosten dieser Operation rechtfertigen soll?!";
				link.l1 = "Eure Gnaden! Ihr weigert Euch einfach, den Punkt zu sehen...";
				link.l1.go = "ReasonToFast_Prison_BadRep1";
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = "Lass mich diese Karte ansehen...\nMachst du Witze? Dieses zerfetzte Stück Pergament ist ein Beweis?";
				link.l1 = "Eure Gnaden! Sie weigern sich einfach, den Punkt zu sehen...";
				link.l1.go = "ReasonToFast_Prison_BadRep1";
				TakeItemFromCharacter(pchar, "mapQuest");	
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_B";	
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = "Das ist wirklich eine originelle Rechtfertigung für die Vernichtung der gesamten Patrouillengruppe. Nun, zumindest hast du uns durch dein Erscheinen die Notwendigkeit erspart, den Mörder zu suchen.";
				link.l1 = "Eure Gnaden! Ihr weigert euch einfach, den Punkt zu sehen...";
				link.l1.go = "ReasonToFast_Prison_BadRep1";			
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}		
		break;
		
		case "ReasonToFast_Prison_GoodRep_11":
			dialog.text = "Nonetheless, I think that your efforts should still be rewarded. Here, take this map; it was found in the belongings of a pirate who has recently gone to the gallows. God willing, perhaps you will actually find that treasure, although I find it quite unlikely...";
			link.l1 = "Danke, das ist sehr großzügig von dir!";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "15");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, "mapQuest"); 
			arItem = ItemsFromID("mapQuest");
			ReasonToFast_GenerateTreasureMap(arItem);
			pchar.questTemp.ReasonToFast.state = "chain_A"; // вилка_А, наводки не генерим
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		case "ReasonToFast_Prison_GoodRep_21":
			dialog.text = "Ihr Eifer ist lobenswert. Bitte, nehmen Sie dieses Schwert als Belohnung - es ist das Mindeste, was ich für Sie tun kann. Oh, und Sie können diese Karte für sich behalten. Ich bin sicher, dass es eine Menge solcher Fälschungen auf dem Archipel gibt.";
			link.l1 = "Danke, das ist sehr großzügig von dir!";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "14");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
			pchar.questTemp.ReasonToFast.state = "chain_B"; // была получена карта
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		case "ReasonToFast_Prison_GoodRep_31":
			dialog.text = "Könnte sein, könnte sein... Nun, sagen wir einfach, dass dieser Handel durch göttliche Gerechtigkeit und durch den Willen unseres Herrn entschieden wurde.";
			link.l1 = "Danke, das ist sehr großzügig von dir!";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			AddQuestRecord("ReasonToFast", "16");
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar,"ReasonToFast");			
		break;
		
		case "ReasonToFast_Prison_BadRep1":
			dialog.text = "Unterstehe dich, mir eine Predigt zu halten! Für mich ist es offensichtlich, dass du mit diesen Schurken zusammenarbeitest! Wachen, ergreift diesen 'Wohltäter'!";
			link.l1 = "Auf keinen Fall!";
			link.l1.go = "fight";
			
			pchar.quest.ReasonToFast_ExitFromTown.win_condition.l1			= "EnterToSea";           	
            pchar.quest.ReasonToFast_ExitFromTown.function    				= "ReasonToFast_ExitFromTownFight";
			pchar.questTemp.ReasonToFast.canSpeakSailor = true;			
			pchar.TownEscape = true;
			Flag_PIRATE();
		break;
		// ------------------------- Повод для спешки -----------------------------
		
		// -------------------------- Операция 'Галеон' ----------------------------
		case "CapComission_PrisonBad1":
			dialog.text = "Und was haben Sie mit ihm zu schaffen?";
			link.l1 = "Ich habe mehrere private Angelegenheiten zu besprechen.";
			link.l1.go = "CapComission_PrisonBad2";
		break;
		
		case "CapComission_PrisonBad2":
			dialog.text = "Kapitän, ich habe einen direkten Befehl, jeden festzuhalten und zur Residenz zu schicken, der nach etwas fragt "+pchar.GenQuest.CaptainComission.Name+"für weitere Befragungen.";
			link.l1 = "Schöne Einrichtung habt ihr hier! Die Gefangenen kommen selbst zu euch, um sich verhaften zu lassen!";
			link.l1.go = "CapComission_PrisonBad3";
		break;
		
		case "CapComission_PrisonBad3":
			dialog.text = "Und dennoch würde ich Sie bitten, Ihre Waffen zu übergeben!";
			link.l1 = "Verflucht seist du! Dann nimm es mir doch mit Gewalt weg!";
			link.l1.go = "fight";
			CaptainComission_GenerateCaptainInPrison(); // данила . на всякий случай ,чтобы сгенерился нормально.
			AddDialogExitQuest("CaptainComission_GenerateCapJail");
		break;
		
		case "CapComission_PrisonGood1":
			dialog.text = "Ja, natürlich. Ich habe Befehle vom Gouverneur, Ihnen in dieser Angelegenheit Hilfe zu leisten. Sie können jetzt den Gefangenen besuchen.";
			link.l1 = "Danke dir...";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			AddDialogExitQuest("CaptainComission_GenerateCapJail");
		break;
		
		case "CapComission_PrisonFree1":
		if(CheckAttribute(pchar,"GenQuest.CaptainComission"))// лесник . разделение диалога если кеп убит или нет
		{
			dialog.text = "Ähm, Kapitän, ich habe nicht die Befugnis, diesen Gefangenen aus der Haft zu entlassen. Sie müssen eine Genehmigung vom Gouverneur anfordern.";
			link.l1 = "Offizier, ich handle zum Wohl der Untersuchung. Der Gefangene hat zugestimmt, mit den Behörden zu kooperieren und das Versteck zu enthüllen. Die Zeit drängt - die Schmuggler können die wertvolle Fracht finden und dann wird sie für die Bevölkerung verloren sein.";
			link.l1.go = "CapComission_PrisonFree2";
		}
         else
		 {
         	dialog.text = "Sie hätten ihn nicht töten sollen, Kapitän... Es ist mir jedoch egal. Wir müssen Sie an seiner Stelle hinrichten. Wachen! Ergreift ihn!";
            link.l2 = "Du hast dir den falschen Kerl zum Ärgern ausgesucht!...";
             link.l2.go = "fight";
			 NextDiag.TempNode = "First_officer";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			AddDialogExitQuest("OpenTheDoors");
		 }			 
		break;
		
		case "CapComission_PrisonFree2":
			dialog.text = "Aber ich könnte ihm eine Eskorte zuweisen.";
			link.l1 = "Es besteht keine Notwendigkeit - ich habe genug Wachen. Außerdem würde ich nicht wollen, dass der Standort des Verstecks öffentlich gemacht wird.";
			link.l1.go = "CapComission_PrisonFree3";
		break;
		
		case "CapComission_PrisonFree3":
			dialog.text = "Hmm... oh, na gut. Aber du wirst mit deinem Kopf für ihn antworten.";
			link.l1 = "Natürlich.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First_officer";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			AddDialogExitQuest("OpenTheDoors");
		break;
		// -------------------------- Операция 'Галеон' ----------------------------
		
		case "F_ShipLetters_1":
			dialog.text = "Sprechen Sie jetzt, ich höre zu.";
			link.l1 = "Ich habe einige Schiffsdokumente bei mir. Der Besitzer muss sie verloren haben, und ich glaube, sie könnten für Sie von Interesse sein.";
			link.l1.go = "F_ShipLetters_2";
			pchar.questTemp.different.GiveShipLetters.speakFort = true;
		break;
		
		case "F_ShipLetters_2":			
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Quatsch! Stör mich nicht bei meiner Arbeit! Geh zu den Hafenbehörden, wenn es dir wichtig ist!";
				link.l1 = "Nun, danke, ich schätze...";
				link.l1.go = "exit";
			}
			else
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					dialog.text = "Ja, das ist der lokale Besitzer. Vielleicht ein Preis von "+sti(pchar.questTemp.different.GiveShipLetters.price2)+" Pesos werden als angemessene Belohnung für Ihre Wachsamkeit dienen, Kapitän.";
					link.l1 = "Vielleicht nicht.";
					link.l1.go = "F_ShipLetters_3";	
					link.l2 = "Ein großzügiges Angebot. Die Dokumente gehören dann Ihnen!";
					link.l2.go = "F_ShipLetters_4";
				}
				else
				{
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
					{
						dialog.text = "Oh, das ist wirklich interessant! Ich glaube, die Stadtkasse wird Ihnen gerne bezahlen "+sti(pchar.questTemp.different.GiveShipLetters.price4)+" Pesos für Ihren Beitrag im Kampf gegen den illegalen Handel.";
						link.l1 = "Vielleicht nicht.";
						link.l1.go = "F_ShipLetters_3";
						link.l2 = "Ein großzügiges Angebot. Die Dokumente gehören dann Ihnen!";
						link.l2.go = "F_ShipLetters_4";
					}
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
					{
						dialog.text = "Oh Herr! Welch ein Glück, dass du zu mir gekommen bist. Ich vermute, mein unglücklicher Kollege wird dir gerne bezahlen "+sti(pchar.questTemp.different.GiveShipLetters.price3)+" Pesos, um die Öffentlichkeit von dieser Angelegenheit fernzuhalten.";
						link.l1 = "Vielleicht nicht.";
						link.l1.go = "F_ShipLetters_3";
						link.l2 = "Ein großzügiges Angebot. Die Dokumente gehören dann Ihnen!";
						link.l2.go = "F_ShipLetters_4";
					}
				}
			}
		break;
		
		case "F_ShipLetters_3":
			dialog.text = "Das ist meine Stadt, Kapitän.";
			link.l1 = "Ich werde das in Erinnerung behalten.";
			link.l1.go = "exit";
		break;
		
		case "F_ShipLetters_4":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price4)); 
				}
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price3)); 
				}
			}
						
			if((sti(pchar.questTemp.different.GiveShipLetters.variant) == 0) || (sti(pchar.questTemp.different.GiveShipLetters.variant) == 2))
			{	
				ChangeCharacterComplexReputation(pchar,"nobility", -1); 
				OfficersReaction("bad"); 
			}	
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "8");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		
        case "ForGoodMove":
			//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				dialog.text = "Natürlich, du kannst alles sehen - hier habe ich eine vollständige Ordnung!";
				link.l1 = "Nun, lass uns das mal überprüfen, Leutnant.";
				link.l1.go = "exit";
				pchar.questTemp.jailCanMove = true;
				break;
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "Natürlich, Eure Exzellenz. Sie können passieren.";
				link.l1 = "Danke, Offizier.";
				link.l1.go = "exit";
				pchar.questTemp.jailCanMove = true;
				break;
			}
			// Офицер с патентом
			if(IsOfficerFullEquip() && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "Nun, ich sehe keinen Grund, Ihnen zu widersprechen - schließlich sind Sie der Kapitän des Schiffes im Dienst von "+NationNameGenitive(sti(npchar.nation))+". Komm rein."; 
				link.l1 = "Danke, Offizier.";
				link.l1.go = "exit";
				pchar.questTemp.jailCanMove = true;
				break;
			}
			// <-- legendary edition
			dialog.text = NPCStringReactionRepeat("Aber warum brauchen Sie es? Glauben Sie mir, es gibt nichts von Interesse, außer für Diebe und Banditen.","Wir haben diesen Wunsch von dir bereits besprochen.","Wieder? Wir hatten schon zweimal darüber gesprochen!","Hmm, wieder...","Block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Trotzdem würde ich mich gerne Ihrer Tour durch die Kasematten anschließen. Ich bin sehr interessiert!","Ja, genau. Aber ich wollte darüber reden.","Nun, vielleicht das dritte Mal...","Hoffe, dass deine Gefangenen mich nicht verlassen.",npchar,Dialog.CurrentNode);
			link.l1.go = "ForGoodMove_1";
		break;
		
        case "ForGoodMove_1":
			pchar.questTemp.jailCanMove.money = 20+hrand(3)*10;
			if (sti(colonies[FindColony(npchar.city)].jail))
			{
				dialog.text = "Nun, ich sehe keinen Grund abzulehnen. "+FindRussianDublonString(sti(pchar.questTemp.jailCanMove.money))+" - und bis du das Gefängnis verlässt, kannst du frei durch die Gänge gehen und sogar mit den Insassen sprechen.";
				if (PCharDublonsTotal() >= sti(sti(pchar.questTemp.jailCanMove.money)))
				{
					link.l1 = "Ich stimme zu, hier sind Ihre Münzen!";
					link.l1.go = "ForGoodMove_agree";
				}
				link.l2 = "Das wird nicht funktionieren. Es ist zu viel für zielloses Wandern durch die Korridore.";
				link.l2.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple("Nein, das ist strengstens durch die Vorschriften verboten. Was? Denkst du, wir haben hier einen Zirkus? Verzieh dich und lenk mich nicht von meinen Pflichten ab.","Ich kann nicht zulassen, dass fremde Leute in meinem Gefängnis herumlaufen. Bitte, hör auf, mich zu belästigen!");
				link.l1 = "In Ordnung, wie du meinst...";
				link.l1.go = "exit";
			}
		break;
		
        case "ForGoodMove_agree":
            dialog.text = "In Ordnung, du kannst jetzt mit deinem Ausflug beginnen...";
			link.l1 = "Danke, Offizier.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			RemoveDublonsFromPCharTotal(sti(pchar.questTemp.jailCanMove.money)));
		break;
		
        case "KnowAboutPrisoner":
			switch (pchar.questTemp.jailCanMove.ownerPrison)
			{
				case "0": sTemp = "For murder."; break;
				case "1": sTemp = "He is accused of piracy."; break;
				case "2": sTemp = "For banditry and robbery."; break;
				case "3": sTemp = "He was caught stealing."; break;
				case "4": sTemp = "For petty theft."; break;
				case "5": sTemp = "For cheating."; break;
				case "6": sTemp = "For vagrancy and begging."; break;
			}
			dialog.text = sTemp;
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				link.l1 = "Ich verstehe... Übergeben Sie ihn mir, Offizier, und dann werde ich das Schicksal dieses Gefangenen selbst entscheiden.";
				link.l1.go = "KnowAboutPrisoner_gengov";
			DeleteAttribute(pchar, "questTemp.jailCanMove.City");
		break;
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				link.l1 = "Ich verstehe... Übergeben Sie ihn mir, Offizier, und dann werde ich das Schicksal dieses Gefangenen selbst entscheiden.";
				link.l1.go = "KnowAboutPrisoner_admiral";
				DeleteAttribute(pchar, "questTemp.jailCanMove.City");
				break;
			}
			link.l1 = "Ich verstehe... Und gibt es eine Möglichkeit zur Auslöse, Kaution... oder ihn auf irgendeine andere Weise freizulassen?";
			link.l1.go = "KnowAboutPrisoner_" + pchar.questTemp.jailCanMove.ownerPrison;
			DeleteAttribute(pchar, "questTemp.jailCanMove.City");
		break;
		
        case "KnowAboutPrisoner_0":
			dialog.text = "Natürlich nicht. Dieser Galgenvogel wird direkt zur Hölle fahren. Der Gouverneur hat seine Sache unter besonderer Kontrolle!";
			link.l1 = "Heh, ich sehe...";
			link.l1.go = "notFree_exit";
		break;	
		
		case "KnowAboutPrisoner_1":
			dialog.text = "Machst du Witze? Er muss schon längst zum Galgen gegangen sein! Er wird sicherlich bald ein Seil heiraten. Vergiss es einfach.";
			link.l1 = "Habs verstanden. Und schon vergessen...";
			link.l1.go = "notFree_exit";
		break;
		
        case "KnowAboutPrisoner_2":
			dialog.text = "Ich glaube nicht. Er hat unseren Stadtbewohnern viel Ärger bereitet. Also frag nicht danach.";
			link.l1 = "Hmm, ich verstehe.";
			link.l1.go = "notFree_exit";
		break;
		
        case "KnowAboutPrisoner_3":
			dialog.text = "Wahrscheinlich nicht. Er ist ein Dieb, und ein Dieb muss im Gefängnis bleiben.";
			link.l1 = "Oh! Gut gesagt, Leutnant!";
			link.l1.go = "notFree_exit";
		break;
		
        case "KnowAboutPrisoner_4":
			dialog.text = "Ich weiß wirklich nicht. Er hat nur eine Kleinigkeit gestohlen. Ich kann ihn nicht freilassen, aber ihn im Gefängnis verrotten zu lassen ist sicherlich nicht richtig.";
			link.l1 = "Nun, dann gib ihn mir, Leutnant. Ich werde Kaution für ihn zahlen - natürlich einen angemessenen Betrag.";
			link.l1.go = "KnowAboutPrisoner_free";
		break;
		
        case "KnowAboutPrisoner_5":
			dialog.text = "Freilassen? Das scheint wahrscheinlich. Meiner Meinung nach gibt es keinen Sinn, diesen kleinen Gauner hier festzuhalten.";
			link.l1 = "Nun, dann gib ihn mir, Leutnant. Ich werde für ihn Kaution zahlen - natürlich einen angemessenen Betrag.";
			link.l1.go = "KnowAboutPrisoner_free";
		break;
		
		case "KnowAboutPrisoner_6":
			dialog.text = "Hmm... In deinen Worten liegt Vernunft. Dieser Taugenichts gehört nicht hierher - er verbreitet nur Schmutz und Krankheiten...";
			link.l1 = "Nun, dann gib ihn mir, Leutnant. Ich werde Kaution für ihn bezahlen - natürlich einen angemessenen Betrag.";
			link.l1.go = "KnowAboutPrisoner_free";
		break;
		
        case "KnowAboutPrisoner_free":
			pchar.questTemp.jailCanMove.ownerPrison.money = 50+hrand(10)*10;
			dialog.text = "In Ordnung, wir haben einen Deal. "+FindRussianDublonString(sti(pchar.questTemp.jailCanMove.ownerPrison.money))+" auf den Nagel, und Sie können ihn sofort mitnehmen.";
			if (PCharDublonsTotal() >= sti(pchar.questTemp.jailCanMove.ownerPrison.money))
			{
				link.l1 = LinkRandPhrase("Ausgezeichnet! Ich stimme zu!","Sie haben einen Handel, Offizier!","Ausgezeichnet. Ich bin bereit, diesen Beitrag zu zahlen.");
				link.l1.go = "KnowAboutPrisoner_agree";
			}
			link.l2 = "Nein, das ist zu teuer. Ich glaube, ich verzichte.";
			link.l2.go = "KnowAboutPrisoner_exit";
		break;
		
        case "KnowAboutPrisoner_agree":
			dialog.text = "Gut, Sie können zu seiner Zelle gehen und diesen Taugenichts mitnehmen.";
			link.l1 = "Danke.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			RemoveDublonsFromPCharTotal(sti(pchar.questTemp.jailCanMove.ownerPrison.money));
			Log_Info("You have given " + FindRussianDublonString(sti(pchar.questTemp.jailCanMove.ownerPrison.money)) + "");
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId)
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_canMove";
		break;
		
        case "KnowAboutPrisoner_exit":
			dialog.text = "Nun, es ist deine Entscheidung. Ich gebe dir keine weitere Chance...";
			link.l1 = "Keine Notwendigkeit dazu.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId);
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_expansive";
		break;
		
        case "notFree_exit":
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId);
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_notFree";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		// belamour legendary edition -->
		// генерал-губернатор
		case "KnowAboutPrisoner_gengov":
			dialog.text = "Natürlich, Eure Exzellenz, wenn Sie es wünschen, dann nehmen Sie diesen Unglücklichen. Seien Sie nur vorsichtig, er ist immer noch ein Verbrecher...";
			link.l1 = "Das ist großartig. Mach dir keine Sorgen Leutnant, ich weiß, was ich tue.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId)
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_canMove";
		break;
		// вице-адмирал
		case "KnowAboutPrisoner_admiral":
			dialog.text = "Nun... Ich weiß nicht mal... Eigentlich kann ich die Gefangenen nicht einfach gehen lassen. Aber du bist immer noch ein Vizeadmiral, also hast du wahrscheinlich das Recht, diesen Verbrecher zu nehmen.";
			link.l1 = "Das ist großartig. Mach dir keine Sorgen Leutnant, ich weiß, was ich tue.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId)
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_canMove";
		break;
		// <-- legendary edition
		//---------------- Протектор ------------------
        case "First_protector":
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				dialog.text = "Gouverneur General, Eure Exzellenz! Kommen Sie rein, aber seien Sie vorsichtig: Von diesen Verbrechern können Sie alles erwarten...";
				link.l1 = "Mach dir keine Sorgen, Soldat, ich kümmere mich darum, wenn etwas passiert.";
				link.l1.go = "exit";
				NextDiag.TempNode = "First_protector";
				break;
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "Grüße, Vizeadmiral! Ich bin hier im Dienst: Ich sorge dafür, dass niemand ohne Erlaubnis ein- oder ausgeht. Sie dürfen hier natürlich frei durchlaufen.";
				link.l1 = "Nun, das ist wunderbar.";
				link.l1.go = "exit";
				NextDiag.TempNode = "First_protector";
				break;
			}
			if (sti(pchar.questTemp.jailCanMove))
			{
				dialog.text = RandPhraseSimple("Du kannst passieren, der Wärter hat seine Erlaubnis gegeben.","Ich habe einen Befehl vom Gefängniswärter erhalten. Du darfst frei passieren.");
				link.l1 = "Sehr gut.";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison.money");
			}
			else
			{
				dialog.text = RandPhraseSimple("Sie dürfen nicht weitergehen, ohne spezielle Erlaubnis vom Gefängniswärter!","Ich antworte nur dem Gefängniswärter! Wenn Sie versuchen, ohne seine Erlaubnis weiterzugehen, sind Sie erledigt!");
				link.l1 = RandPhraseSimple("Ich sehe","In Ordnung")+", Soldat.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First_protector";
		break;
		//---------------- Солдаты ------------------
        case "First_soldier":
            dialog.text = RandPhraseSimple("Ich bin im Dienst, stör mich nicht.","Fortbewegen, ich darf nicht mit dir sprechen.");
			link.l1 = "Gut, Soldat.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First_soldier";
		break;
		//---------------- Заключенные ------------------
        case "First_prisoner": 
			if (GetNationRelation2MainCharacter(sti(npchar.nation)) == RELATION_ENEMY)
			{
				dialog.text = LinkRandPhrase("Ho-ho, ist das nicht eine großartige Zeit!","Schneidet sie, "+GetSexPhrase("Kumpel","lass")+", schneidet ab!!!","Oh, verdammt! Ich habe jede Hoffnung verloren, die Leiche meines Kerkermeisters zu sehen!");
				link.l1 = RandPhraseSimple("Heh!","Aarrgh!");
				link.l1.go = "NoMoreTalkExit";
				if (rand(10) > 6 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && !CheckAttribute(pchar, "GenQuest.PrisonQuestLock") && !CheckAttribute(pchar, "quest.GivePrisonFree") && !CheckAttribute(pchar, "quest.GivePrisonFree_Over") && !CheckAttribute(pchar, "quest.DeliverToBander")) // Addon 2016-1 Jason пиратская линейка
				{
					dialog.text = RandPhraseSimple("Halt an, "+GetSexPhrase("Kamerad","lass")+"!! Lasst mich los!","Hör zu, "+GetSexPhrase("Kamerad","Lass")+", öffne freundlicherweise die Zelle.");
					link.l1 = "Aus welchem Grund?";
					link.l1.go = "Prisoner_1"; // на квест освобождения заключённого
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("Ich werde des Raubes beschuldigt, aber ich bin unschuldig!","Arrgh, du gepflegter Abschaum... Möchtest du ein bisschen in meiner Zelle sitzen?! Kheh-heh-heh...","Ich bin nicht schuldig!");
				link.l1 = RandPhraseSimple("Halt die Klappe!","Mir ist scheißegal was mit dir passiert...");
				link.l1.go = "NoMoreTalkExit";
				if (rand(10) > 6 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && !CheckAttribute(pchar, "GenQuest.PrisonQuestLock") && !CheckAttribute(pchar, "quest.GivePrisonFree_Over") && !CheckAttribute(pchar, "quest.GivePrisonFree") && !CheckAttribute(pchar, "quest.DeliverToBander") && !sti(colonies[FindColony(npchar.city)].HeroOwn)) // Addon 2016-1 Jason пиратская линейка
				{
					dialog.text = RandPhraseSimple("Halt ein, "+GetSexPhrase("Kumpel","lass")+", komm nicht so schnell vorbei!","Mach keine Eile, "+GetSexPhrase("Kamerad","lass")+", lass uns reden.");
					link.l1 = "Aus welchem Grund?";
					if (rand(1))
					{
						link.l1.go = "Prisoner_1"; // на квест освобождения заключённого
					}
					else
					{
						link.l1.go = "Deliver_1"; // на квест передачу весточки
					}
				}
			}
		break;
		// -------------------- освобождение заключённого --------------------
        case "Prisoner_1":
            dialog.text = "Hör mir zu, Kamerad. Denk nicht, dass ich schlecht aussehe und so. Ich muss hier nur raus...";
			link.l1 = "Was?!";
			link.l1.go = "Prisoner_2";
			GetChestPlaceName();
			pchar.questTemp.jailCanMove.prisonerId = npchar.id; //запомним Id
			pchar.questTemp.jailCanMove.IsTrue = rand(4); //вид клада
			pchar.questTemp.jailCanMove.Item1 = GenQuestPrison_GenerateArtefact();
			pchar.questTemp.jailCanMove.Item2 = GenQuestPrison_GenerateBlade();
			pchar.questTemp.jailCanMove.Name = GetFullName(npchar); //имя перца
			npchar.nation = PIRATE;
		break;
        case "Prisoner_2":
            dialog.text = "Was du gehört hast! Hilf mir, und ich werde in der Lage sein zu zahlen...";
			link.l1 = "Das ist interessant. Wer bist du und was kannst du mir bieten?";
			link.l1.go = "Prisoner_3";
		break;
        case "Prisoner_3":
            dialog.text = "Mein Name ist "+GetFullName(npchar)+". Ich habe einige Sachen an einem sicheren Ort versteckt. Bring mich einfach hier raus und bring mich zu "+XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Akz")+". Dort, in einer Grotte, habe ich den Schatz. Wir werden ihn holen und teilen!";
			link.l1 = "Und was hast du in deinem Versteck? Und wie kann ich wissen, dass du die Wahrheit sagst?";
			link.l1.go = "Prisoner_4";
		break;
        case "Prisoner_4":
            dialog.text = "Ich schwöre, ich sage die Wahrheit! Was den Vorrat betrifft - da gibt es einen Schatz und Geld...";
			link.l1 = "Nein, Kumpel. Ich riskiere nicht meine Haut für eine fragwürdige Beute. Es tut mir leid...";
			link.l1.go = "Prisoner_5";
			if (GetNationRelation2MainCharacter(sti(npchar.nation)) != RELATION_ENEMY)
			{			
				// belamour legendary edition адмирал и губернатор может договориться без денег
				bool bAdmiral = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation);
				bool bGenGov = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == GetBaseHeroNation());
				if(!bAdmiral && !bGenGov)
				{
				link.l2 = "Nun, es könnte sich lohnen, ein Risiko einzugehen... Ich schlage folgendes vor: Ich kann die Wachen im Gefängnis ausschalten und dich zu meinem Schiff bringen. Wenn alles klappt, möchte ich, dass du die ganze Zeit an meiner Seite bleibst, bis wir zur Grotte kommen "+XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Stimme")+". Abmachung?"; // belamour gen
				link.l2.go = "Prisoner_agree"; //силовой способ вызволения
				}
				link.l3 = "In Ordnung, ich werde versuchen, Ihnen zu helfen. Ich werde mit dem Gefängniswärter sprechen. Vielleicht kann ich Sie auslösen.";
				link.l3.go = "ToPrisonHead_agree"; //мирный способ вызволения
			}
			else
			{
				link.l2 = "Gut, ich werde dir glauben und deine Zelle öffnen. Ich möchte, dass du die ganze Zeit an meiner Seite bleibst, bis wir zur Grotte kommen "+XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc")+". Abgemacht?";
				link.l2.go = "Prisoner_agree_3"; //силовой способ вызволения, когда тюремщики убиты
			}
		break;
        case "Prisoner_5":
            dialog.text = RandPhraseSimple("Verdammt seist du, du Schurke!","Verdammt, du hast mich ausgenommen, Abschaum...");
			link.l1 = RandPhraseSimple("Und auch dir alles Gute. Lebewohl...","Der Mond braucht nicht das Gebell der Hunde...");
			link.l1.go = "NoMoreTalkExit";
		break;
        case "Prisoner_agree":
            dialog.text = "Gut. Ich bin nicht in der Lage, wählerisch zu sein.";
			link.l1 = "In Ordnung. Ich werde jetzt dein Schloss knacken, um dich rauszuholen, und wir werden durchbrechen. Bist du bereit?";
			link.l1.go = "Prisoner_agree_1";
		break;
        case "Prisoner_agree_1":
            dialog.text = "Ja, "+GetSexPhrase("Kamerad","lass")+", ich bin bereit!";
			link.l1 = "Dann lass uns loslegen!";
			link.l1.go = "Prisoner_agree_2";
		break;
        case "Prisoner_agree_2":
			string slai_group = GetNationNameByType(sti(npchar.nation))  + "_citizens";
			LAi_group_AttackGroup(slai_group, LAI_GROUP_PLAYER);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
            AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			Pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			Pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			Pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";			
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			//LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

        case "Prisoner_agree_3":
            dialog.text = "Gut. Ich bin nicht in der Position, wählerisch zu sein.";
			link.l1 = "In Ordnung. Folge mir so schnell du kannst - wir müssen noch zu meinem Schiff gelangen. Zöger nicht!";
			link.l1.go = "Prisoner_agree_4";
		break;
        case "Prisoner_agree_4":
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
            AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			Pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			Pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			Pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			//LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;

        case "ToPrisonHead_agree":
            dialog.text = "Nun, du kannst es versuchen. Hoffentlich kommen wir durch! Aber verschwende keine Zeit - in ein paar Tagen werde ich hier raus sein...";
			link.l1 = "Warte hier, ich werde alles arrangieren.";
			link.l1.go = "NoMoreTalkExit";
			pchar.questTemp.jailCanMove.City = npchar.City; //город
			pchar.questTemp.jailCanMove.ownerPrison = rand(6); //характер преступления
			SetTimerCondition("GivePrisonFree_Over", 0, 0, 2, false);
			AddQuestRecord("GivePrisonFree", "5");
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("",""));
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
		break;

        case "ToPrisonHead_canMove":
            dialog.text = "Nun, was sagst du, "+GetSexPhrase("Kamerad","lass")+"?";
			link.l1 = "Alles ist arrangiert und ich kann dich von hier mitnehmen.";
			link.l1.go = "ToPrisonHead_canMove_1";
		break;
        case "ToPrisonHead_canMove_1":
            dialog.text = "Dann lass uns hier raus! Oh, Herr, wie glücklich ich bin!";
			link.l1 = "Fassen wir zusammen. Ich möchte, dass du die ganze Zeit an meiner Seite bleibst, bis wir zur Grotte kommen "+XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Dat")+", du bleibst nicht weiter als einen Schritt zurück. Nur zur Sicherheit. Bist du einverstanden?";
			link.l1.go = "ToPrisonHead_canMove_2";
		break;
        case "ToPrisonHead_canMove_2":
            dialog.text = "Natürlich, ich stimme zu! Vor allem, da ich nicht in der Lage bin, zu wählen.";
			link.l1 = "Dann bist du frei.";
			link.l1.go = "ToPrisonHead_canMove_exit";
		break;
        case "ToPrisonHead_canMove_exit":
			pchar.quest.GivePrisonFree_Over.over = "yes";
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
            AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			Pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			Pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			Pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";			
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			//LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;

        case "ToPrisonHead_notFree":
			switch (pchar.questTemp.jailCanMove.ownerPrison)
			{
				case "0": sTemp = "murder"; break;
				case "1": sTemp = "piracy"; break;
				case "2": sTemp = "brigandry"; break;
				case "3": sTemp = "thievery"; break;
			}
            dialog.text = "Nun, was sagst du, "+GetSexPhrase("Kamerad","lass")+"?";
			link.l1 = "Ich konnte deine Freilassung nicht arrangieren. Du wirst beschuldigt von "+sTemp+", also kannst du nicht ausgelöst werden.";
			link.l1.go = "ToPrisonHead_notFree_1";
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
		break;
		
        case "ToPrisonHead_notFree_1":
            dialog.text = "Aber ich wurde verleumdet! Oh Teufel! Und was soll ich jetzt tun? Ich werde hier lebendig verrotten!";
			link.l1 = "Es tut mir leid, Kumpel, aber ich kann nichts für dich tun.";
			link.l1.go = "ToPrisonHead_notFree_2";
			link.l2 = "Es bleibt nur eine Chance - dich mit Gewalt zu befreien. Ich werde jetzt dein Schloss aufbrechen, um dich herauszuholen, und wir werden durchbrechen. Bist du bereit?";
			link.l2.go = "Prisoner_agree_1";
			pchar.quest.GivePrisonFree_Over.over = "yes";
		break;
		
        case "ToPrisonHead_notFree_2":
            dialog.text = RandPhraseSimple("Verfluche dich!","Verflucht, du hast mich abgezockt, Miststück...");
			link.l1 = "Und auch dir das Beste. Lebewohl...";
			link.l1.go = "NoMoreTalkExit";
			AddQuestRecord("GivePrisonFree", "7");
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			DeleteAttribute(pchar, "questTemp.jailCanMove.islandId");	
			DeleteAttribute(pchar, "questTemp.jailCanMove.placeId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.prisonerId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.IsTrue");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Sum");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Name");
		break;

        case "ToPrisonHead_expansive":
			dialog.text = "Also, irgendwelche guten Nachrichten, "+GetSexPhrase("Kamerad","lass")+"";
			link.l1 = "Die Kaution für deine Freilassung ist zu hoch, ich habe nicht so viel Geld. Ich muss aufhören, dir zu helfen.";
			link.l1.go = "ToPrisonHead_notFree_2";
			pchar.quest.GivePrisonFree_Over.over = "yes";
		break;
		//==> в месте, где клад припрятан
        case "PrisonerInPlace":
			switch (sti(pchar.questTemp.jailCanMove.IsTrue))
			{
				case 0:
					dialog.text = "Hör zu, ich habe alles überprüft, aber keinen Schatz gefunden. Schade, dass es so gekommen ist. Jemand muss es vor uns ausgegraben haben.";
					link.l1 = "Und wie kann das sein?!";
					link.l1.go = "PrisonerInPlace_1";
				break;
				case 1:
					dialog.text = "Ich habe es gefunden! Der Schatz ist noch da, wo ich ihn hinterlassen habe.";
					link.l1 = "Ausgezeichnet. Nun, dann teilen wir uns?";
					link.l1.go = "Node_1";
				break;
				case 2:
					dialog.text = "Nun, hier ist es, mein Versteck. Nicht viel, aber das ist alles, was ich habe. Wie vereinbart, gehört die Hälfte davon dir.";
					link.l1 = "Ja, der Schatz ist in der Tat bescheiden. Nun, immer noch besser als nichts.";
					link.l1.go = "Node_2";
				break;
				case 3:
					dialog.text = "Kapitän, es tut mir leid, aber... Es gibt keinen Schatz.";
					link.l1 = "Was?! Du hast mich hintergangen, du Schurke! Ich habe dich auf diese Insel gebracht - und wofür? Das wirst du nicht ungestraft davonkommen!";
					link.l1.go = "Node_3";
				break;
				case 4:
                    ok = GetCharacterItem(pchar, "map_full") == 0 && GetCharacterItem(PChar, "map_part2") == 0;
                    if(GetCharacterItem(PChar, "map_part1") > 0 && !ok) // Первая половинка есть, но вторую дать нельзя
                    {
                        dialog.text = "Hör zu, ich habe alles überprüft, aber keinen Schatz gefunden. Schade, dass es so gekommen ist. Jemand muss es vor uns ausgegraben haben.";
                        link.l1 = "Und wie kann das sein?!";
                        link.l1.go = "PrisonerInPlace_1";
                    }
                    else
                    {
                        dialog.text = "Verdammt... Wie könnte das sein? Das kann nicht sein!";
                        link.l1 = "Was ist los, Kumpel? Wo ist der Schatz? Sag mir nicht, dass es keinen gibt!";
                        link.l1.go = "Node_4";
                    }
				break;
			}
		break;
			
		case "Node_1":
			dialog.text = "Natürlich, wie vereinbart. Die Hälfte des Schatzes gehört Ihnen.";
			link.l1 = "Heiliger Herr, jetzt gibt es sicherlich eine Menge kostbarer Dinge!";
			link.l1.go = "PrisonerInPlace_3";
			Log_Info("You have received your share of the treasure");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "icollection", 1+hrand(1));
			TakeNItems(pchar, "chest", 4+hrand(4));
			TakeNItems(pchar, "jewelry1", 70+rand(15));
			TakeNItems(pchar, "jewelry2", 50+rand(15));
			TakeNItems(pchar, "jewelry3", 60+rand(15));
			TakeNItems(pchar, "jewelry4", 40+rand(10));
			TakeNItems(pchar, "jewelry5", 10+rand(10));
			TakeNItems(pchar, "jewelry46", 60+rand(20));
			TakeNItems(pchar, "jewelry47", 40+rand(15));
			TakeNItems(pchar, "jewelry40", 60+rand(20));
			AddQuestRecord("GivePrisonFree", "3_1");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
		case "Node_2":
			dialog.text = "Kapitän, unter anderem gibt es auch diesen indischen Gegenstand. Sie können ihn zusätzlich zu Ihrem Anteil haben.";
			link.l1 = "Nun, zumindest etwas Wertvolles für deine Freilassung! Gib es mir.";
			link.l1.go = "PrisonerInPlace_3";
			Log_Info("You have received your share of the treasure");
			PlaySound("interface\important_item.wav");
			sTemp = pchar.questTemp.jailCanMove.Item1;
			TakeNItems(pchar, sTemp, 1);
			TakeNItems(pchar, "jewelry5", 40+rand(10));
			TakeNItems(pchar, "jewelry6", 20+rand(20));
			TakeNItems(pchar, "jewelry17", 80+rand(20));
			TakeNItems(pchar, "jewelry13", 10+rand(10));
			TakeNItems(pchar, "jewelry10", 20+rand(20));
			TakeNItems(pchar, "jewelry12", 50+rand(20));
			TakeNItems(pchar, "jewelry11", rand(2)+1);
			AddQuestRecord("GivePrisonFree", "3_2");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
		case "Node_3":
			dialog.text = "Warte, Kapitän, reg dich nicht auf, lass mich sprechen. Ich bin auch ein Seemann, genau wie du. Ich wurde aus Versehen ins Gefängnis geworfen, ich schwöre. Du warst meine einzige Chance zu entkommen, und ich musste dir wegen des Schatzes lügen.\nEs gibt keinen Schatz, aber ich habe dort eine gute Sache versteckt. Nimm es, und lass mich in Frieden gehen. Vielleicht wird es dir eines Tages in einer Schlacht helfen zu überleben.";
			link.l1 = "Gut, ich habe sowieso nicht viel von dir erwartet. Gott sei Dank, dass ich nicht nachtragend bin.";
			link.l1.go = "PrisonerInPlace_3";
			Log_Info("You have received equipment");
			PlaySound("interface\important_item.wav");
			sTemp = pchar.questTemp.jailCanMove.Item2;
			TakeNItems(pchar, sTemp, 1);
			AddQuestRecord("GivePrisonFree", "3_3");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
		case "Node_4":
			dialog.text = "Nein!!! Es ist nicht da! Verdammter Schrott... Kapitän, ich war mir absolut sicher, dass ich es hier finden würde! Aber anscheinend habe ich mich geirrt! Etwas auf diesem Stück Papier war wirklich unklar...";
			link.l1 = "Ach du meine Güte... Du steckst in ernsthaften Schwierigkeiten, Kumpel. Aber ich würde mir trotzdem gerne deine Erklärung anhören.";
			link.l1.go = "Node_4_1";
		break;
			
		case "Node_4_1":
			dialog.text = "Ich hatte einen Fetzen der Karte. Das war eine echte Karte, ich schwöre! Aber es ist sehr schwer zu sagen, welche Insel darauf abgebildet war... Ich dachte, es wäre hier... Aber wie du jetzt siehst, lag ich falsch.";
			link.l1 = "Welchen Fetzen Papier? Gib ihn mir sofort!";
			link.l1.go = "Node_4_2";
		break;
			
		case "Node_4_2":
			AddMapPart();
			dialog.text = "Natürlich, nimm es. Kapitän, befreie mich... bitte? Ich dachte wirklich, dass der Schatz dort war. Vielleicht findest du heraus, wo er ist, und nimmst ihn für dich. Ich flehe dich an.";
			link.l1 = "Ich sehe... Tatsächlich, es ist schwer, aus diesem Fetzen etwas herauszufinden. Die zweite Hälfte der Karte ist nötig. Also, verschwinde. Ich sehe jetzt, dass es nicht deine Schuld war.";
			link.l1.go = "PrisonerInPlace_4";
		break;
			
		case "PrisonerInPlace_1":
			dialog.text = "Sehr einfach, "+GetSexPhrase("Kamerad","lass")+". Alles im Leben passiert.\nNun, du bist hier - wenn du willst: bleib, such nach mehr. Nun, ich muss gehen!\nLebewohl, "+GetSexPhrase("mein Freund","lass")+", danke, dass du mein Leben gerettet hast. Ich werde dich immer in Erinnerung behalten!";
			link.l1 = "Schurke! Denkst du, ich lasse dich damit durchkommen?! Hey! Halt an, Feigling!";
			link.l1.go = "PrisonerInPlace_2";
			AddQuestRecord("GivePrisonFree", "4");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
        case "PrisonerInPlace_2":
			LAi_group_Delete("EnemyFight");
			DeleteAttribute(pchar, "questTemp.jailCanMove.islandId");	
			DeleteAttribute(pchar, "questTemp.jailCanMove.placeId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.prisonerId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.IsTrue");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Sum");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Name");
			chrDisableReloadToLocation = false;
			LAi_LocationDisableMonstersGen(pchar.location, false);
			npchar.lifeDay = 0;
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", -1);
			DialogExit();

            Pchar.quest.DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
            Pchar.quest.DeletePrisonGroup.win_condition.l1.location = pchar.location;
            Pchar.quest.DeletePrisonGroup.win_condition = "DeletePrisonGroup";
		break;
		
        case "PrisonerInPlace_3":
			dialog.text = "Hier, bitte. Danke!";
			link.l1 = "Auf Wiedersehen...";
			link.l1.go = "PrisonerInPlace_2";
		break;
		
        case "PrisonerInPlace_4":
			dialog.text = "Danke, Kapitän! Ich werde bis an mein Lebensende für Sie beten!";
			link.l1 = "Ach, halt die Klappe! Geh in Frieden...";
			link.l1.go = "PrisonerInPlace_2";
			AddQuestRecord("GivePrisonFree", "3_4");
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
        
		// -------------------- освобождение заключённого --------------------
		// ------------------------ передать маляву --------------------------
        case "Deliver_1":
			dialog.text = "Ich heiße "+GetFullName(npchar)+". Ich habe eine Bitte an Sie, he-he...";
			link.l1 = "Was ist los?";
			link.l1.go = "Deliver_2";
		break;
        case "Deliver_2":
			dialog.text = "Ich brauche eine Botschaft, die aus dem Gefängnis geschickt wird. Wirst du es tun?";
			link.l1 = "Und was ist für mich drin?";
			link.l1.go = "Deliver_3";
		break;
        case "Deliver_3":
			dialog.text = "Die Kumpels werden dich nicht enttäuschen, versprochen... Also? Bist du dabei?";
			link.l1 = "Nein, ich bin nicht interessiert.";
			link.l1.go = "Prisoner_5";
			link.l2 = "Nun, wenn es nicht zu viel Anstrengung von mir erfordert, kann ich es tun.";
			link.l2.go = "Deliver_agree";
		break;
        case "Deliver_agree":
			dialog.text = "Gut. Jetzt hör mir gut zu. Zwei Kumpel warten in einem Haus auf meine Botschaft, damit sie bei einem Überfall nicht erwischt werden. Aber ich habe keine Ahnung, welches Haus genau es ist. Du musst suchen.";
			link.l1 = "Was meinst du mit - suchen?";
			link.l1.go = "Deliver_4";
		break;
        case "Deliver_4":
			dialog.text = "Suchen wie im Suchen. Du wirst durch die Stadt rennen, in die Häuser schauen. Wenn du am richtigen Ort ankommst, lassen sie dich nicht ohne ein Gespräch gehen. Aber denk daran, dass ich höchstens noch zwei Tage dort bleiben würde. Also zögere nicht.";
			link.l1 = "Ich verstehe. Nun, reiche mir deine Botschaft, dann.";
			link.l1.go = "Deliver_5";
		break;
        case "Deliver_5":
			pchar.questTemp.jailCanMove.Deliver.locationId = GetBanderLocation(npchar); //Id коммона
			if (pchar.questTemp.jailCanMove.Deliver.locationId == "none")
			{
				dialog.text = "Hmm, weißt du, ich mag dich einfach nicht. Ich habe meine Meinung geändert. Komm schon, steh nicht da!";
				link.l1 = "Schau dich an! Nun, wie du willst...";
				link.l1.go = "NoMoreTalkExit";
				DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
			}
			else
			{
				dialog.text = "Hier. Danke, "+GetSexPhrase("Kamerad","Lass")+"!";
				link.l1 = "Überhaupt nicht.";
				link.l1.go = "NoMoreTalkExit";
				GiveItem2Character(Pchar, "Malyava");
				pchar.questTemp.jailCanMove.Deliver.Id = npchar.id; //Id зэка
				pchar.questTemp.jailCanMove.Deliver.name = GetFullName(npchar); //имя зэка
				pchar.questTemp.jailCanMove.Deliver.City = npchar.city; //город (Id колонии)
				pchar.questTemp.jailCanMove.Deliver.good = rand(3); //опрокинут или нет
				pchar.questTemp.jailCanMove.Deliver.price = rand(6)*500+500; //цена услуги
				pchar.quest.DeliverToBander.win_condition.l1 = "location";
				pchar.quest.DeliverToBander.win_condition.l1.location = pchar.questTemp.jailCanMove.Deliver.locationId;
				pchar.quest.DeliverToBander.win_condition = "DeliverToBander";
				pchar.quest.DeliverToBander.again = true; 
				SetTimerCondition("DeliverToBander_over", 0, 0, 2, false);
				ReOpenQuestHeader("GivePrisonFree");
				AddQuestRecord("GivePrisonFree", "8");
				AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("",""));
				AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
				AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Deliver.name);
			}
		break;
		
		// Warship, 16.05.11. Генер "Justice for sale".
		case "JusticeOnSale_1":
			dialog.text = "Ja, er wurde wegen Schmuggels festgenommen. Aber warum kümmern Sie sich um diesen Galgen-Vogel, "+GetAddress_Form(NPChar)+"?";
			link.l1 = "Seine Bande plant, seine Flucht zu arrangieren und ihre schmutzigen Taten fortzusetzen.";
			link.l1.go = "JusticeOnSale_2";
			link.l2 = "Ich habe gehört, dass er nicht schuldig war.";
			link.l2.go = "JusticeOnSale_3";
			
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.PrisonWait");
		break;
		
		case "JusticeOnSale_2":
			dialog.text = "Sie müssen den Gouverneur benachrichtigen, "+GetAddress_Form(NPChar)+", diese Schurken müssen alle gefangen werden!";
			link.l1 = "Ich werde genau das tun.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First_officer";
		break;
		
		case "JusticeOnSale_3":
			dialog.text = "Hör zu, "+GetFullName(PChar)+", dieser Kerl wurde beim Versuch, verbotene Waren zu verkaufen, mitten in der Stadt erwischt! Wie kannst du behaupten, dass er nicht schuldig ist?";
			link.l1 = "Ich habe gehört, dass der Vorwurf unbegründet war und ihr keine Beweise habt, ist das nicht korrekt? Ihr könnt nicht einfach einen Mann festnehmen, der Unrecht erlitten hat.";
			link.l1.go = "JusticeOnSale_4";
		break;
		
		case "JusticeOnSale_4":
			dialog.text = "Wir haben weder Zeugen noch die Waren, aber das ändert nichts, Kapitän "+GetFullName(PChar)+"! Diese Person ist definitiv schuldig - und vielleicht nicht nur am illegalen Handel. So oder so - warum sollten Sie sich um den Gefangenen kümmern?";
			link.l1 = "Vielleicht kann mein Wort die Bürgschaft für diesen unglücklichen Gefangenen sein?";
			link.l1.go = "JusticeOnSale_5_WithoutMoney";
			
			if(sti(PChar.money) >= 5000)
			{
				link.l2 = "Vielleicht können diese 5000 Pesos die Kaution für diesen unglücklichen Gefangenen sein?";
				link.l2.go = "JusticeOnSale_5";
			}
		break;
		
		case "JusticeOnSale_5_WithoutMoney":
			if(GetCharacterSkill(PChar, SKILL_LEADERSHIP) > hrand(100) || sti(PChar.money) < 5000)
			{
				dialog.text = "In Ordnung, "+GetAddress_Form(NPChar)+", nimm diesen Schurken und geh, bevor ich es mir anders überlege.";
				link.l1 = "Es ist großartig, den Triumph der Gerechtigkeit zu sehen, findest du nicht?";
				link.l1.go = "JusticeOnSale_6";
			}
			else
			{
				dialog.text = "Nein, "+GetAddress_Form(NPChar)+", das wird nicht gehen.";
				link.l1 = "Dann könnten vielleicht diese 5000 Pesos das gewichtigere Argument sein?";
				link.l1.go = "JusticeOnSale_5";
			}
		break;
		
		case "JusticeOnSale_5":
			dialog.text = "In Ordnung, "+GetAddress_Form(NPChar)+", nimm diesen Schurken und geh, bevor ich meine Meinung ändere.";
			link.l1 = "Es ist großartig, den Triumph der Gerechtigkeit zu sehen, findest du nicht?";
			link.l1.go = "JusticeOnSale_6";
			AddMoneyToCharacter(PChar, -5000);
			PChar.GenQuest.JusticeOnSale.PrisonMoney = true;
		break;
		
		case "JusticeOnSale_6":
			DialogExit();
			sld = GetCharacter(NPC_GenerateCharacter("JusticeOnSale_Smuggler", "mercen_"+(rand(9)+1), "man", "man", sti(PChar.rank)+5, PIRATE, -1, true, "marginal"));
			SetFantomParamFromRank(sld, sti(PChar.rank)+5, true);
			sld.name = PChar.GenQuest.JusticeOnSale.SmugglerName;
			sld.lastName = "";
			sld.dialog.filename = "GenQuests_Dialog.c";
			sld.dialog.currentnode = "First time";
			sld.greeting = "Enc_Raiders"; 
			AddPassenger(PChar, sld, false);
			SetCharacterRemovable(sld, false);
			PChar.GenQuest.JusticeOnSale.SmugglerModel = sld.model;
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait");
			sld = &Locations[FindLocation(PChar.GenQuest.JusticeOnSale.ShoreId)];
			sld.DisableEncounters = true;
			PChar.Quest.JusticeOnSale_ShoreEnterWithSmuggler.win_condition.l1  = "location";
			PChar.Quest.JusticeOnSale_ShoreEnterWithSmuggler.win_condition.l1.location = PChar.GenQuest.JusticeOnSale.ShoreId;
			PChar.Quest.JusticeOnSale_ShoreEnterWithSmuggler.function = "JusticeOnSale_ShoreEnterWithSmuggler";
			Log_Info("Smuggler's captain on a board");
			PlaySound("interface\notebook.wav");
			LAi_Fade("", "");
			WaitDate("",0,0,0,0,60); // 280313 // лесник. прокрутка времени было так WaitDate("",0,0,0,2,5);
		break;
		// --> belamour ночной приключенец
		case "NightAdventure_CitizenHomie":
			dialog.text = "Ja, es gab so einen gewalttätigen. Er war unhöflich zu einem Wachmann und dann geriet er in eine Schlägerei. Nichts weiter: er wird für einige Tage hinter Gittern sitzen - er wird nüchtern werden. Warum kümmern Sie sich um ihn? Sie scheinen ein Kapitän zu sein, und dieser Trunkenbold sieht nicht aus wie ein Seemann.";
			link.l1 = "Ja, das stimmt, ich bin ein Kapitän. Die Sache ist, dieser Trunkenbold ist ein alter Bekannter von mir. Erzähl bitte niemandem davon. Wenn ich das richtig verstehe, hat er nicht einmal eine Waffe gegriffen. Vielleicht lässt du ihn dieses Mal auf meine Bitte hin frei?";
			link.l1.go = "NightAdventure_CitizenHomie_1";
		break;
		
		case "NightAdventure_CitizenHomie_1":
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomie") // отпустил под честное слово
			{
				dialog.text = "Ja, ein guter Freund von mir. Mach dir keine Sorgen, ich werde es niemandem sagen. Tatsächlich konnte er nicht einmal richtig zuschlagen, es war nur ein Versuch - deshalb haben sie ihn ins Gefängnis gesteckt. Da du fragst, aus Respekt vor dir, werde ich ihn freilassen. Warn ihn nur, dass er sich das nächste Mal besser unter Kontrolle haben sollte. Oder noch besser, lass ihn weniger trinken.";
				link.l1 = "Danke, Offizier.";
				link.l1.go = "NightAdventure_CitizenHomieOK";
			}
			
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderNM" || pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderGM") // поговорить с солдатом
			{
				dialog.text = "Ja, guter Freund. Mach dir keine Sorgen, ich werde es niemandem erzählen. Nur hat er es geschafft, dem Wachposten ins Gesicht zu schlagen, bevor sie ihn gefesselt haben. Also kann ich ihn nicht rauslassen. Es sei denn natürlich, der Wachposten würde zustimmen, seine Ansprüche zurückzuziehen. Du kannst selbst mit ihm sprechen, er ist heute auf Patrouille rund um die Stadt.";
				link.l1 = "Nein, ich fürchte, wenn er den Wächter geschlagen hat, dann kann ich ihm nicht helfen. Er wird ein paar Tage sitzen müssen. Es tut mir leid, Sie zu belästigen, Offizier.";
				link.l1.go = "CitizenHomieEnd";
				link.l2 = "In Ordnung, ich gehe und versuche, mit dem Wachposten zu verhandeln.";
				link.l2.go = "NightAdventure_CitizenHomieSolder";
			}
			
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieOfficer") // выплата офицеру
			{
				dialog.text = "Ja, guter Freund. Mach dir keine Sorgen, ich werde niemandem etwas sagen. Die Sache ist die, ein Mitglied der Streitkräfte im Dienst anzugreifen, ist ein Verbrechen. Ich kann dir entgegenkommen und ihn freilassen, aber nur gegen Kaution.";
				link.l1 = "Und wie viel muss ich dafür bezahlen?";
				link.l1.go = "NightAdventure_CitizenHomieOfficer";
			}
		break;
		
		case "NightAdventure_CitizenHomieOK":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
			SetFunctionLocationCondition("NightAdventure_CitizenHomieOK", npchar.City+"_town", false);
		break;
		
		case "NightAdventure_CitizenHomieEnd":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
			pchar.quest.NightAdventure_SeaExit.over = "yes";
			pchar.quest.NightAdventure_JungleExit.over = "yes";
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		case "NightAdventure_CitizenHomieSolder":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
			for(i=0; i<MAX_CHARACTERS; i++)
			{
				if(Characters[i].location != npchar.City+"_town") continue;
				if(Characters[i].chr_ai.type != "patrol") continue;
				while(SoldQty < 10) // на всякий случай, чтобы не было выхода за границы массива
				{                   // генерируется 7 солдат + 3 мушкетера
					SoldNum[SoldQty] = Characters[i].index;
					SoldQty++;
				}
			}
			iTemp = rand(SoldQty);
			pchar.GenQuest.NightAdventureSolNum = SoldNum[iTemp];
		break;
		
		case "NightAdventure_HomieToPrisoner":
			DeleteAttribute(pchar,"GenQuest.NightAdventureToPrisoner");
			pchar.quest.NightAdventure_SeaExit.over = "yes";
			pchar.quest.NightAdventure_JungleExit.over = "yes";
			SetFunctionLocationCondition("NightAdventure_CitizenHomieOK", npchar.City+"_town", false);
			dialog.text = "*liest* Also... also... Nun, da der Wachposten keine Beschwerden hat, habe ich auch keine. Du kannst deinen Freund mitnehmen. Sag ihm einfach, dass er sich das nächste Mal beherrschen soll. Besser noch, lass ihn weniger trinken.";
			link.l1 = "Danke, Offizier.";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_CitizenHomieOfficer":
			dialog.text = "Nun, da er keine Waffe ergriffen hat, sind das nur 1500 Pesos.";
			link.l1 = "Ich fürchte, ich bin noch nicht bereit, so viel zu geben. Nun, wenn man bedenkt, dass er nur für ein paar Tage hier ist, wird es ihm wohl nicht schaden. Vielleicht trinkt er weniger.";
			link.l1.go = "NightAdventure_CitizenHomieEnd";
			if(sti(pchar.money) >= 1500)
			{
				link.l2 = "Gut, ich bin bereit, die Kaution zu zahlen.";
				link.l2.go = "NightAdventure_CitizenHomieOfficer_1";
			}
		break;
		
		case "NightAdventure_CitizenHomieOfficer_1":
			AddMoneyToCharacter(pchar, -1500);
			DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
			pchar.quest.NightAdventure_SeaExit.over = "yes";
			pchar.quest.NightAdventure_JungleExit.over = "yes";
			SetFunctionLocationCondition("NightAdventure_CitizenHomieOK", npchar.City+"_town", false);
			dialog.text = "Sie können Ihren Freund abholen. Sagen Sie ihm einfach, dass er sich das nächste Mal beherrschen soll. Oder noch besser, lassen Sie ihn weniger trinken.";
			link.l1 = "Danke, Offizier.";
			link.l1.go = "exit";
		break;
		// <-- ночной приключенец
		
		// --> Sinistra Путеводная звезда
		case "PZ_BasTer_ComendantDialog":
			if (CheckAttribute(pchar, "questTemp.PZ_BasTerOpozdal"))
			{
				dialog.text = "Danke, dass du zugestimmt hast zu kommen, anstatt ein Massaker zu beginnen. Wenigstens ist heutzutage jemand vernünftig.";
				link.l1 = "Also, weshalb schenkst du mir diese Aufmerksamkeit, Monsieur Offizier? Hat es etwas mit der Tatsache zu tun, dass ich nach einem Chinesen suche?";
				link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_1";
			}
			else
			{
				dialog.text = "Es ist gut, dass du freiwillig zu uns gekommen bist. Wir hatten in letzter Zeit genug von Rüpeln.";
				link.l1 = "Nun, wie Sie sehen können, bin ich nicht einer der gewalttätigen. Aber... warum bin ich hier, Offizier? Ich habe Ihre Männer schon gefragt, aber ich habe keine Antwort bekommen - ist es, weil ich nach einem bestimmten Chinesen in der Stadt suche?";
				link.l1.go = "PZ_BasTer_ComendantDialog_1";
			}
			DeleteQuestCondition("PZ_BasTerPeshera");
			npchar.Dialog.Filename = "Common_Prison.c";
			npchar.Dialog.CurrentNode = "First_officer";
		break;
		// <-- Путеводная звезда
		case "Helen_meeting":
			dialog.text = "Aber natürlich nicht! Bitte, komm rein. Du bist immer in unseren Verliesen willkommen. Äh, ich meine das natürlich im guten Sinne. Also, was brauchst du hier?";
			link.l1 = "Oh, nichts Besonderes, weißt du, ich schaue mich nur in der Stadt um, also bin ich zufällig hierher gewandert.";
			link.l1.go = "exit";
			link.l2 = "Ich wollte über einige Geschäfte sprechen.";
			link.l2.go = "quests";
			if (!sti(pchar.questTemp.jailCanMove))
			{
				link.l4 = "Ich möchte ins Gefängnis gehen.";
				link.l4.go = "ForGoodMove";		
			}
			NextDiag.TempNode = "First_officer";
		break;
	}
}

void GetChestPlaceName()
{
	string islandId;
	int iTemp = rand(3);
	switch (iTemp)
	{
		case 0: 
			pchar.questTemp.jailCanMove.islandId = "Bermudes";
			pchar.questTemp.jailCanMove.placeId = "Bermudes_Cavern";
		break;
		case 1: 
			pchar.questTemp.jailCanMove.islandId = "Caiman";
			pchar.questTemp.jailCanMove.placeId = "Caiman_Grot";
		break;
		case 2: 
			pchar.questTemp.jailCanMove.islandId = "Dominica";
			pchar.questTemp.jailCanMove.placeId = "Dominica_Grot";
		break;
		case 3: 
			pchar.questTemp.jailCanMove.islandId = "Terks";
			pchar.questTemp.jailCanMove.placeId = "Terks_Grot";
		break;
	}
}

string GetBanderLocation(ref npchar)
{
    aref	arCommon, arRld, arRld2;
    int	i, n, Qty, Qty2;
	string LocId; 
	string	storeArray [50];
	int howStore = 0;
    makearef(arRld, Locations[FindLocation(npchar.city + "_town")].reload);
	Qty = GetAttributesNum(arRld);
    if (CheckAttribute(pchar, "GenQuest.SeekSpy.Location")) //если взят квест мэра по поиску шпиона
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.GenQuest.SeekSpy.Location)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.GenQuest.SeekSpy.Location && arCommon.name != "reload1") // mitrokosta fix
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	else
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && arCommon.name != "reload1") // mitrokosta fix
    				{
						storeArray[howStore] = LocId;
						howStore++; 
					}
				}
			}	
		}
	}
	if (howStore == 0) return "none";
	LocId = storeArray[rand(howStore-1)];
	SetOpenDoorCommonLoc(npchar.city, LocId); //открываем дверь
	for(n=0; n<MAX_CHARACTERS; n++)
	{
		if (CheckAttribute(&characters[n], "locations") && characters[n].locations == LocId) 
		{			
			characters[n].lifeDay = 0;
		}
	}
	return LocId;
}

string GenQuestPrison_GenerateArtefact() // артефакты
{
	string itemID;
	switch(rand(7))
	{
		case 0:
			itemID = "indian_5";
		break;
		case 1:
			itemID = "indian_7"; 
		break;
		case 2:
			itemID = "indian_8"; 
		break;
		case 3:
			itemID = "indian_9"; 
		break;
		case 4:
			itemID = "indian_10"; 
		break;
		case 5:
			itemID = "indian_11"; 
		break;
		case 6:
			itemID = "indian_3"; 
		break;
		case 7:
			itemID = "indian_6"; 
		break;
	}
	return itemID;
}

string GenQuestPrison_GenerateBlade() // клинки и другое
{
	string itemID;
	switch(rand(8))
	{
		case 0:
			itemID = GetGeneratedItem("blade_16");
		break;
		case 1:
			itemID = GetGeneratedItem("blade_15"); 
		break;
		case 2:
			itemID = GetGeneratedItem("blade_13"); 
		break;
		case 3:
			itemID = "cirass2"; 
		break;
		case 4:
			itemID = GetGeneratedItem("blade_10"); 
		break;
		case 5:
			itemID = "spyglass3"; 
		break;
		case 6:
			itemID = "cirass6"; 
		break;
		case 7:
			itemID = "cirass7"; 
		break;
		case 8:
			itemID = "cirass1"; 
		break;	
		
	}
	return itemID;
}

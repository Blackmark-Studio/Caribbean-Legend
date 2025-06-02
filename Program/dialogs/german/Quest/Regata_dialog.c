void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		//вестовой
		case "Regata_Cureer":
			dialog.text = "Guten Tag. Sind Sie der Kapitän "+GetFullName(pchar)+"?";
			link.l1 = "Ja, das bin ich. Und worum geht es?";
			link.l1.go = "Regata_Cureer_1";
		break;
		
		case "Regata_Cureer_1":
			dialog.text = "Ich habe einen Brief für Sie vom Gouverneur von Jamaika, Sir Edward Doily.";
			link.l1 = "Wer hätte das gedacht! Ich hätte das nicht erwartet... Und was will der Gouverneur von mir?";
			link.l1.go = "Regata_Cureer_2";
		break;
		
		case "Regata_Cureer_2":
			dialog.text = "Lesen Sie den Brief, Herr. Kurz gesagt, man bietet Ihnen an, an der Regatta teilzunehmen, einem Rennen durch das gesamte Archipel. Gerüchte über Ihre seemännischen Fähigkeiten und bemerkenswerte Geschwindigkeit beim Segeln sind nicht unbemerkt geblieben.";
			link.l1 = "Unglaublich! Nun, ich... ich werde es in Betracht ziehen.";
			link.l1.go = "Regata_Cureer_3";
			GiveItem2Character(pchar, "letter_open");
			ChangeItemDescribe("letter_open", "itmdescr_letter_open_Regata");
			AddQuestRecordInfo("RegataLetter", "1");
		break;
		
		case "Regata_Cureer_3":
			if (Pchar.BaseNation == SPAIN || Pchar.BaseNation == HOLLAND)
			{
				dialog.text = "Auch soll ich Ihnen freien Zugang zum Hafen von Port Royal gewähren. Hier ist eine Lizenz für 30 Tage. Nun ist meine Mission erfüllt. Auf Wiedersehen, Kapitän.";
				link.l1 = "Danke. Die Lizenz ist sehr willkommen. Lebewohl!";
				link.l1.go = "Cureer_exit";
				GiveNationLicence(HOLLAND, 30);
			}
			else
			{
				dialog.text = "Gut. Nun ist meine Mission erfüllt. Auf Wiedersehen, Kapitän.";
				link.l1 = "Auf Wiedersehen!";
				link.l1.go = "Cureer_exit";
			}
		break;
		
		case "Cureer_exit":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			pchar.questTemp.Regata.ToPortRoyal = "true";
			SetQuestHeader("Regata");
			AddQuestRecord("Regata", "1");
		break;
		
		//распорядитель регаты
		case "Regata_Head":
			if (CheckAttribute(pchar, "questTemp.Regata.Begin"))
			{
				dialog.text = "Guten Tag. Sie nehmen an der Regatta teil, nehme ich an?";
				link.l1 = "Genau, Herr. Mein Name ist "+GetFullName(pchar)+". Ich habe die Einladung erhalten.";
				link.l1.go = "Regata_Head_1";
			}
			else
			{
				dialog.text = "Möchten Sie etwas, Herr?";
				link.l1 = "Nein, es ist nichts. Ich gehe schon.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Regata_Head";
			}
		break;
		
		case "Regata_Head_1":
			iTest = FindColony("PortRoyal"); 
			if (iTest != -1)
			{
				rColony = GetColonyByIndex(iTest);
			}
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
			{
				dialog.text = "Ich freue mich, Sie zu treffen, Kapitän "+GetFullName(pchar)+". Dann lass uns anfangen. Du weißt bereits über die Grundlagen aus dem Brief, richtig? Nur Schaluppen, und sie muss das einzige Schiff in deinem Geschwader sein, um an der Regatta teilzunehmen. Hast du diese Anforderungen erfüllt?";
				// belamour legendary edition допускаем курьерский люггер 
				ok = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
				if((GetCompanionQuantity(pchar) > 1) || !ok)
				{
					link.l1 = "Noch nicht. Ich werde es jetzt tun und bald zurück sein.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Regata_Head_repeat";
				}
				else
				{
					link.l1 = "Ja, das habe ich.";
					link.l1.go = "Regata_Head_2";
				}
			}
			else
			{
				dialog.text = "Sie sind gekommen, um an der Regatta teilzunehmen, aber wo ist Ihr Schiff, Kapitän?";
				link.l1 = "Entschuldigen Sie, Herr. Ich werde mein Schiff sofort zum Hafen bringen.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Regata_Head_repeat";
			}
		break;
		
		case "Regata_Head_repeat":
			if (CheckAttribute(pchar, "questTemp.Regata.Begin"))
			{
				iTest = FindColony("PortRoyal"); 
				if (iTest != -1)
				{
					rColony = GetColonyByIndex(iTest);
				}
				ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
				{
					ok = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
					dialog.text = "Ach, du bist es wieder. Hast du alles getan, um die Anforderungen für die Regatta zu erfüllen?";
					// belamour legendary edition допускаем курьерский люггер 
					if ((GetCompanionQuantity(pchar) > 1) || !ok)
					{
						link.l1 = "Noch nicht. Ich werde es jetzt tun und bald zurück sein.";
						link.l1.go = "exit";
						NextDiag.TempNode = "Regata_Head_repeat";
					}
					else
					{
						link.l1 = "Ja, das habe ich.";
						link.l1.go = "Regata_Head_2";
					}
				}
				else
				{
					dialog.text = "Kapitän, wir haben nichts zu besprechen, bis ich dein Schiff auf einer Reede sehe. Verstehst du mich oder soll ich mich wiederholen?";
					link.l1 = "Entschuldigen Sie, Herr. Ich werde mein Schiff sofort zum Hafen bringen.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Regata_Head_repeat";
				}
			}
			else
			{
				dialog.text = "Möchten Sie etwas, Herr?";
				link.l1 = "Nein... es ist nichts. Ich gehe schon.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Regata_Head";
			}
		break;
		
		case "Regata_Head_2":
			dialog.text = "Gut. Nun zur nächsten Frage. Wie heißt dein Schiff?";
			link.l1 = "'"+pchar.Ship.Name+"'. ";
			link.l1.go = "Regata_Head_3";
		break;
		
		case "Regata_Head_3":
			dialog.text = "Da die Regatta von den englischen Behörden veranstaltet wird und aufgrund der festgelegten Regeln muss der Name Ihres Schiffes für die Dauer der Veranstaltung geändert werden. Keine Sorge, das betrifft jeden Teilnehmer.";
			link.l1 = "Man sagt, es bringt Unglück, wenn man den Namen seines Schiffes ändert.";
			link.l1.go = "Regata_Head_4";
		break;
		
		case "Regata_Head_4":
			dialog.text = "Sie können den Namen nach der Regatta wieder ändern. Also wird Ihr Kutter den Namen 'Saint Catherine' tragen.";
			link.l1 = "Ich verstehe es, Herr, ich werde den Namen ändern.";
			link.l1.go = "Regata_Head_5";
			pchar.Ship.Name = "Saint Catherine";
		break;
		
		case "Regata_Head_5":
			dialog.text = "Nun sprechen wir über die Regatta selbst. Hören Sie gut zu. Ich werde Ihnen auch ein Regelblatt zur Verfügung stellen.\nDie Regatta beginnt und endet in Port Royal. Es gibt fünf Punkte, die Sie erreichen müssen\nDer erste ist von Port Royal nach Belize, West Main\nDer zweite ist von Belize nach Port-au-Prince, Hispaniola\nDer dritte ist von Port-au-Prince nach St. John's, Antigua\nDer vierte ist von St. John's nach Bridgetown, Barbados\nUnd der letzte ist von Bridgetown nach Port Royal\nIst das klar?";
			link.l1 = "Kristallklar, Herr.";
			link.l1.go = "Regata_Head_6";
		break;
		
		case "Regata_Head_6":
			dialog.text = "Prächtig. Sie müssen sich in jedem Hafenbüro der folgenden Städte melden: Belize, Port-au-Prince, St. Johns, Bridgetown. Sie werden disqualifiziert, wenn Sie eine dieser Städte verpassen oder die richtige Reihenfolge nicht einhalten\nDie Büros bleiben während der Regatta rund um die Uhr geöffnet. Klopfen Sie an die Tür und sie lassen Sie herein.";
			link.l1 = "Verstanden.";
			link.l1.go = "Regata_Head_7";
		break;
		
		case "Regata_Head_7":
			dialog.text = "Es ist verboten, das Schiff zu wechseln und weitere Schiffe zu Ihrer Staffel hinzuzufügen. Dies wird in jeder Stadt überprüft, denken Sie daran.";
			link.l1 = "Ich werde darüber nachdenken. Wer wird normalerweise als Gewinner angesehen und können wir über Preise sprechen?";
			link.l1.go = "Regata_Head_8";
		break;
		
		case "Regata_Head_8":
			dialog.text = "Es gibt nur einen Gewinner in der Regatta - den Kapitän, dessen Schiff als erstes Port-Royal erreicht. Der Preis ist sehr wertvoll. Der Gewinner erhält eine große Summe - 250.000 Pesos. Außerdem wird er mit einer Reihe wertvoller Geschenke belohnt.";
			link.l1 = "Also, Verlierer bekommen nichts?";
			link.l1.go = "Regata_Head_9";
		break;
		
		case "Regata_Head_9":
			dialog.text = "Genau. Zudem wetten viele reiche und arme Bürger der englischen Kolonien auf den Sieger der Regatta. Du kannst auch auf... dich selbst wetten. Normalerweise tut das jeder Kapitän. Wenn du gewinnst, wirst du noch mehr verdienen und vergiss nicht die Motivation. Normalerweise nehme ich die Wetten an\nWettest du auf deinen Sieg?";
			link.l1 = "Ha! Sicher, das bin ich. Wie viel kann ich wetten?";
			link.l1.go = "Regata_rate";
			link.l2 = "Ich werde darüber nachdenken. Vielleicht werde ich wetten.";
			link.l2.go = "Regata_Head_10";
		break;
		
		case "Regata_Head_10":
			if (CheckAttribute(pchar, "questTemp.Regata.Begin"))
			{
				dialog.text = "Überlege, ob du willst. Du hast etwas Zeit, bevor die Regatta beginnt.";
				link.l1 = "Gut. Wann fängt es an?";
				link.l1.go = "Regata_Head_11";
				DeleteAttribute(pchar, "questTemp.Regata.Rate");
				pchar.questTemp.Regata.Ratenext = "true";
			}
			else
			{
				dialog.text = "Denk, wenn du willst. Du hast etwas Zeit, bevor die Regatta beginnt.";
				link.l1 = "Gut.";
				link.l1.go = "exit";
			}
		break;
		
		case "Regata_Head_11":
			CreateRegataAdversaries();
			dialog.text = "In drei Tagen, um zwölf Uhr mittags. Komm zum Pier und sei nicht zu spät. Du wirst fünf Konkurrenten haben.\n"+pchar.questTemp.Regata.AdversaryName.a+", der "+pchar.questTemp.Regata.AdversaryShipName.a+"\n"+pchar.questTemp.Regata.AdversaryName.b+", der "+pchar.questTemp.Regata.AdversaryShipName.b+"\n"+pchar.questTemp.Regata.AdversaryName.c+", der "+pchar.questTemp.Regata.AdversaryShipName.c+"\n"+pchar.questTemp.Regata.AdversaryName.d+", der "+pchar.questTemp.Regata.AdversaryShipName.d+"\n"+pchar.questTemp.Regata.AdversaryName.e+", der "+pchar.questTemp.Regata.AdversaryShipName.e+"\nSie sind alle erfahrene Kapitäne. Nun, anscheinend ist das alles. Nehmen Sie zur Sicherheit das Regelblatt. Wir sehen uns am Start!";
			link.l1 = "Auf Wiedersehen, Herr.";
			if (Pchar.BaseNation == SPAIN || Pchar.BaseNation == HOLLAND) link.l1.go = "Regata_Head_13";
			else link.l1.go = "Regata_Head_12";
		break;
		
		case "Regata_Head_12":
			DialogExit();
			pchar.quest.RegataToPortRoyalTimeOver.over = "yes";//снять таймер
			SetFunctionTimerCondition("Regata_SetTime", 0, 0, 3, false);
			pchar.quest.Regata_Lost.win_condition.l1 = "Timer";
			pchar.quest.Regata_Lost.win_condition.l1.date.hour  = 13.0;
			pchar.quest.Regata_Lost.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 3);
			pchar.quest.Regata_Lost.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 3);
			pchar.quest.Regata_Lost.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 3);
			pchar.quest.Regata_Lost.function = "Regata_Lost";
			pchar.quest.Regata_Start.win_condition.l1 = "Timer";
			pchar.quest.Regata_Start.win_condition.l1.date.hour  = 12.0;
			pchar.quest.Regata_Start.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 3);
			pchar.quest.Regata_Start.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 3);
			pchar.quest.Regata_Start.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 3);
			pchar.quest.Regata_Start.win_condition.l2 = "locator";
			pchar.quest.Regata_Start.win_condition.l2.location = "Portroyal_town";
			pchar.quest.Regata_Start.win_condition.l2.locator_group = "reload";
			pchar.quest.Regata_Start.win_condition.l2.locator = "reload1_back";
			pchar.quest.Regata_Start.function = "Regata_Start";
			AddQuestRecordInfo("RegataRules", "1");
			NextDiag.CurrentNode = "Regata_Prepare";
			DeleteAttribute(pchar, "questTemp.Regata.Begin");
			pchar.questTemp.Regata.Prepare = "true";
			AddQuestRecord("Regata", "2");
		break;
		
		case "Regata_Head_13":
			dialog.text = "Warte! Ich gebe dir die 30-Tage-Lizenz für den Besuch englischer und französischer Häfen. Die Regatta wird nicht länger als einen Monat dauern. Bitte, nimm es.";
			link.l1 = "Danke!";
			link.l1.go = "Regata_Head_12";
			GiveNationLicence(HOLLAND, 30);
		break;
		
		case "Regata_rate":
			dialog.text = "Wie viel setzt du ein?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "Regata_rate_1";
			link.l2 = "Ich vermute, ich brauche noch etwas Zeit zum Nachdenken.";
			link.l2.go = "Regata_Head_10";
		break;
		
		case "Regata_rate_1":
			int iQty = sti(dialogEditStrings[4]);
			pchar.questTemp.Regata.Rate = sti(iQty);
			if (iQty < 10000)
			{
				dialog.text = "Herr, das ist nicht lustig, noch ist es lustig. Ich werde nicht für so eine kleine Summe arbeiten.";
				link.l1 = "Um Verzeihung zu bitten... Lassen Sie uns den Einsatz überdenken.";
				link.l1.go = "Regata_rate";
				break;
			}
			if (iQty > 100000)
			{
				dialog.text = "Herr, ich kann solche Einsätze aufgrund der Regeln der Regatta nicht akzeptieren. Reduzieren Sie es auf einen vernünftigen Wert.";
				link.l1 = "Schade. Lass uns die Summe nochmal überdenken.";
				link.l1.go = "Regata_rate";
				break;
			}
			dialog.text = ""+iQty+"? Das ist ein feiner Einsatz. Ich bin bereit, ihn zu akzeptieren. Ihr Geld, Herr?";
			if (makeint(Pchar.money) >= sti(pchar.questTemp.Regata.Rate))
			{
				link.l1 = "Bitte, nimm es.";
				link.l1.go = "Regata_rate_2";
			}
			link.l2 = "Ich habe jetzt nicht genug Münzen. Ich werde später zu dir kommen und wir werden eine Wette abschließen. Und ich werde mehr darüber nachdenken, vielleicht überdenke ich die Summe.";
			link.l2.go = "Regata_Head_10";
		break;
		
		case "Regata_rate_2":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Regata.Rate));
			pchar.questTemp.Regata.Advantage = sti(pchar.questTemp.Regata.Rate)*(1.5+frand(1.5)); // dlc
			dialog.text = "Hervorragend! Jetzt musst du nur noch der Erste sein und der Preis wird deiner sein. Sein endgültiger Wert könnte variieren, es hängt alles davon ab, wie viele Leute am Ende auf dich setzen werden.";
			if (!CheckAttribute(pchar, "questTemp.Regata.Ratenext"))
			{
				link.l1 = "Ich verstehe. Wann beginnt die Regatta?";
				link.l1.go = "Regata_Head_11";
			}
			else
			{
				link.l1 = "Ich verstehe. Ich werde auf den Start warten. Bis dann!";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Regata.Ratenext");
				NextDiag.TempNode = "Regata_Prepare";
			}
		break;
		
		case "Regata_Prepare":
			dialog.text = "Ach, du bist wieder hier, Kapitän "+GetFullName(pchar)+"? Was willst du?";
			if (!CheckAttribute(pchar, "questTemp.Regata.Rate"))
			{
				link.l1 = "Ich möchte auf meinen Sieg wetten.";
				link.l1.go = "Regata_rate";
			}
			link.l2 = "Nein, es ist nichts. Wollte dich nur begrüßen.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Regata_Prepare";
		break;
		
		//старт регаты
		case "Regata_CitMan":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Kapitän, sind Sie das erste Mal hier? Lassen Sie mich Ihnen sagen, dass Sie vorsichtig sein sollten. Ihre Konkurrenten könnten Ihnen einige sehr unangenehme Überraschungen bereiten...","Kapitän, ich habe auf dich gesetzt. Enttäusche mich nicht!","Kapitän, die Einheimischen in den Häfen der Regatta könnten Ihnen etwas zum Kauf anbieten. Es kann oft wirklich nützlich sein. Bedenken Sie das."),LinkRandPhrase("Gute Reise, Kapitän!","Kapitän, bitte seien Sie vorsichtig, die Kastilier jagen oft die Schaluppen der Teilnehmer in den spanischen Gewässern.","Ich habe gehört, dass einige zwielichtige Gestalten den Regattakapitänen oft ihre 'Dienste' anbieten. Es liegt an dir, ihre Angebote anzunehmen oder nicht."));
			link.l1 = "Ja, ja, natürlich... danke, ich schätze.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_CitMan";
		break;
		
		case "Regata_CitWom":
			dialog.text = LinkRandPhrase("Kapitän, ich und mein Mann haben zehntausend auf Ihren Sieg gewettet. Lassen Sie uns nicht im Stich! Ich werde für Sie beten!","Kapitän! Ich wünsche Ihnen Glück!","Ähm... Sie sind ein so mutiger und tapferer Kapitän...");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_CitWom";
		break;
		
		case "Regata_CitHorse":
			dialog.text = LinkRandPhrase("Hallo, Seemann! Wink der Schönheit zu! Ich werde auf deine Rückkehr warten!","He, salziger Seemann! Die Dame hat gesagt, dass sie mich als Preis für den Gewinner der Regatta kostenlos geben wird... Versuche zu gewinnen, du bist so gut aussehend!","Vergiss nicht uns zu besuchen, wenn du zurück bist, hübscher Mann, wir werden dich nach höchsten Standards verwöhnen!");
			link.l1 = "Nun, hah... Ich werde es in Betracht ziehen, danke!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_CitHorse";
		break;
		
		case "Regata_Prepare_1":
			if (sti(environment.time) < 12.0)
			{
				dialog.text = "Kapitän, die Regatta beginnt um 12 Uhr. Sie können sich jetzt ausruhen, wir bereiten das Fest vor. Kommen Sie mittags zurück, Ihre Wettbewerber werden das Gleiche tun.";
				link.l1 = "Sehr gut, Herr! Ich werde auf den Start warten...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Hier sind Sie, Kapitän.";
				link.l1 = "Meine Mannschaft und ich sind bereit, Herr! Ich warte auf den Start...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_Prepare_1";
		break;
		
		case "Regata_Start":
			dialog.text = "Also, meine Herren, hier sind wir. Ich verkünde den Start der Regatta. Sie kennen die Regeln. Derjenige, der hier zuerst zurückkehrt, wird als Sieger gefeiert. Meine Damen und Herren, wünschen wir unseren tapferen Kapitänen viel Glück!\nMeine Herren! Seid ihr bereit? Fertig! Los!";
			link.l1 = "...";
			link.l1.go = "Regata_Start_1";
		break;
		
		case "Regata_Start_1":
			DialogExit();
			PlaySound("people fight\mushketshot.wav");
			log_info("The regatta has started! Get aboard! Head to Belize!");
			for (i=1; i <=5; i++)
			{
				sld = characterFromId("Regata_Cap_F"+i);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			}
			Island_SetReloadEnableGlobal("Jamaica", false);//на остров нельзя
			SetFunctionTimerCondition("ReturnJamaicaNorm", 0, 0, 1, false);//таймер на возврат нормы
			LocatorReloadEnterDisable("Portroyal_town", "reload1_back", false);//откроем выход в море
			DeleteAttribute(pchar, "questTemp.Regata.Prepare");
			pchar.questTemp.Regata.Go = "true";
			pchar.questTemp.Regata.Town = "Beliz";
			pchar.quest.Regata_PU.win_condition.l1 = "locator";
			pchar.quest.Regata_PU.win_condition.l1.location = "Beliz_town";
			pchar.quest.Regata_PU.win_condition.l1.locator_group = "reload";
			pchar.quest.Regata_PU.win_condition.l1.locator = "reload10_back";
			pchar.quest.Regata_PU.win_condition.l2 = "Night";
			pchar.quest.Regata_PU.function = "RegataPU_Open";//вход в ПУ ночью
			//ситуации
			pchar.quest.Regata_ShYarder.win_condition.l1 = "location";
			pchar.quest.Regata_ShYarder.win_condition.l1.location = "Beliz_town";
			pchar.quest.Regata_ShYarder.function = "RegataShipyarder";
			sld = characterFromId("Beliz_shipyarder");
			LAi_RemoveLoginTime(sld);
			AddQuestRecord("Regata", "3");
		break;
		//старт регаты
		
		//верфист с парусами
		case "Regata_Shipyarder":
			dialog.text = "Grüße, Kapitän! Mir wurde mitgeteilt, dass Sie an der Karibik-Regatta teilnehmen.";
			link.l1 = "Es ist wahr. Neuigkeiten verbreiten sich über das Archipel schneller als der Wind.";
			link.l1.go = "Regata_Shipyarder_1";
		break;
		
		case "Regata_Shipyarder_1":
			dialog.text = "Sie tun es, Kapitän. Ich habe einen Vorschlag für Sie. Es betrifft Ihr Schiff und die Regatta.";
			link.l1 = "Heh! Interessant. Ich höre Ihnen zu, Herr.";
			link.l1.go = "Regata_Shipyarder_2";
		break;
		
		case "Regata_Shipyarder_2":
			dialog.text = "Ich habe ein Set perfekter Segel für einen Logger, sie sind aus der besten Baumwolle gefertigt. Diese Segel werden die Beschleunigung Ihres Schiffes erhöhen und Ihnen einen Zeitvorteil gegenüber Ihren Gegnern verschaffen\n Ich bin bereit, sie Ihnen zu verkaufen, das heißt, wenn Sie sie kaufen möchten.";
			link.l1 = "Wie viel verlangst du für diese Segel?";
			link.l1.go = "Regata_Shipyarder_3";
		break;
		
		case "Regata_Shipyarder_3":
			dialog.text = "Nur 15 000 Pesos. Sie müssen zugeben, dass dies ein sehr bescheidener Preis für eine... Situation wie diese ist.";
			if (makeint(Pchar.money) >= 15000)
			{
				link.l1 = "Ich stimme zu. Ich kaufe diese neuen Segel für meinen Logger. Hier, nehmen Sie Ihr Geld, Herr. Würden Sie so freundlich sein, sie zu meinem Schiff zu liefern, während ich einchecke.";
				link.l1.go = "Regata_Shipyarder_4";
			}
			link.l2 = "Ich habe nicht so viel Geld. Also kann ich Ihre Segel nicht kaufen.";
			link.l2.go = "Regata_Shipyarder_exit";
		break;
		
		case "Regata_Shipyarder_4":
			AddMoneyToCharacter(pchar, -15000);
			dialog.text = "Es wird erledigt, Herr. Meine Männer warten nur auf das Wort, und ich verspreche Ihnen, Sie werden es nicht bereuen. Außerdem sind diese Segel schön blau gefärbt. Ihre Schönheit wird es zu schätzen wissen.";
			link.l1 = "Also gut dann! Nun, ich muss gehen und du machst die Segel.";
			link.l1.go = "Shipyarder_exit";
			for (i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp))+12;//выиграл 12 часов у всех
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp)));
			}
			RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails = 3;
			SetSailsColor(Pchar, 5);
			AddQuestRecord("Regata", "28");
		break;
		
		case "Regata_Shipyarder_exit":
			dialog.text = "Wie schade. Nun, es ist deine Wahl. Lebewohl, Kapitän.";
			link.l1 = "Auf Wiedersehen!";
			link.l1.go = "Shipyarder_exit";
			pchar.questTemp.Regata.AdversarySecondTransition.Time.d = sti(pchar.questTemp.Regata.AdversarySecondTransition.Time.d)-16;//четвертый соперник выиграл 16 часов
			log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversarySecondTransition.Time.e));
			AddQuestRecord("Regata", "29");
		break;
		
		case "Shipyarder_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload5_back", "Beliz_Shipyard", "sit", "sit1", "ReturnRegataSYNorm", 5);
		break;
		//верфист с парусами
		
		//контрики с пушками
		case "Regata_Contra":
			dialog.text = "Hallo, Kapitän "+GetFullName(pchar)+". Wir müssen mit Ihnen sprechen... eigentlich ist es nur ein... Geschäftsvorschlag.";
			link.l1 = "Hm. Interessant und wie wissen Sie, wer ich bin?";
			link.l1.go = "Regata_Contra_1";
		break;
		
		case "Regata_Contra_1":
			dialog.text = "Was soll ich sagen, sie haben mir immer gesagt, dass ich begabt bin... Ha-ha, nun, die Regatta ist in vollem Gange und du nimmst daran teil, du bist ein berühmter Kapitän!";
			link.l1 = "Ich verstehe. Nun, sprich Deinen Verstand aus.";
			link.l1.go = "Regata_Contra_2";
		break;
		
		case "Regata_Contra_2":
			if (sti(pchar.questTemp.Regata.Index != 1))
			{
				sTemp = pchar.questTemp.Regata.ContraIndex;
				dialog.text = "Wir wissen, dass es noch einen Teilnehmer vor Ihnen gibt - "+pchar.questTemp.Regata.AdversaryName.(sTemp)+" der "+pchar.questTemp.Regata.AdversaryShipName.(sTemp)+". Er hat den Hafen vor nicht allzu langer Zeit verlassen und wird bald am Kap von Gonaives vorbeisegeln.";
			}
			else
			{
				dialog.text = "Wir wissen, dass sich noch ein Teilnehmer direkt hinter Ihnen befindet - "+pchar.questTemp.Regata.AdversaryName.b+" der "+pchar.questTemp.Regata.AdversaryShipName.b+". Er wird in ein paar Stunden hier sein.";
			}
			link.l1 = "Hmm... Sie sind sehr gut informiert.";
			link.l1.go = "Regata_Contra_3";
		break;
		
		case "Regata_Contra_3":
			if (sti(pchar.questTemp.Regata.Index != 1)) sTemp = "letting you pass ahead of him and take his position";
			else sTemp = "therefore you will be taking a lead for a long time";
			dialog.text = "Auf jeden Fall. Aber kommen wir zur Sache. Wir bieten Ihnen unsere Hilfe für Ihr Geld an. Wir haben vier Kanonen von unserem Schiff am Kap hinter der Bucht von Gonaives platziert. Jedes Regattaschiff muss es umfahren.\nDie Kanonen sind mit Kettenkugeln geladen. Wenn wir einen Deal machen, werde ich unseren Kanonenfreunden sagen, sie sollen die Segel deines Konkurrenten ruinieren, so dass er gezwungen sein wird, Zeit für die Reparatur zu verlieren, "+sTemp+".";
			link.l1 = "Wie viel verlangst du für diesen Dienst?";
			link.l1.go = "Regata_Contra_4";
			link.l2 = "Nein. Ich werde solche Methoden nicht benutzen, um zu gewinnen. Ihr habt euch in mir geirrt. Lebewohl, Herren.";
			link.l2.go = "Regata_Contra_exit";
		break;
		
		case "Regata_Contra_exit":
			dialog.text = "Nun Kapitän, es ist Ihre Wahl. Lebewohl.";
			link.l1 = "Danke für die Informationen über das Kap. Ich werde mich davon fernhalten.";
			link.l1.go = "Contra_exit";
			AddQuestRecord("Regata", "31");
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
		break;
		
		case "Regata_Contra_4":
			if (sti(pchar.questTemp.Regata.Index != 1)) iTemp = 50000;
			else iTemp = 30000;
			dialog.text = "Nicht viel. Nur "+iTemp+" Pesos. Und einer Ihrer Wettbewerber wird fast zwei Tage wegen... eines Unfalls verlieren, ha-ha!";
			if (makeint(Pchar.money) >= iTemp)
			{
				link.l1 = "Heh! Du sprichst Klartext, mein Freund! Ich zahle. Aber welche Garantien habe ich, dass du deinen Job machst? Und dass du nicht auf mein Schiff schießt, wenn ich das Kap passiere?";
				link.l1.go = "Regata_Contra_5";
			}
			link.l2 = "Ich habe nicht so viel Geld. Also kann ich Ihre Dienste nicht in Anspruch nehmen.";
			link.l2.go = "Regata_Contra_exit";
		break;
		
		case "Regata_Contra_5":
			dialog.text = "Kapitän bitte, wir sind Schmuggler, keine Piraten. Wir sind alle ehrliche Männer... auf unsere Weise. Sie müssen unsere Dienste schon mal in Anspruch genommen haben, nicht wahr? Sie haben mein Wort. Sie können sich darauf verlassen.";
			link.l1 = "Gut genug, nimm also dein Geld.";
			link.l1.go = "Regata_Contra_6";
		break;
		
		case "Regata_Contra_6":
			AddQuestRecord("Regata", "30");
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			dialog.text = "Sie werden mit diesem Handel zufrieden sein, Kapitän. Und ich werde meine Kanonenjungen sofort darüber informieren. Viel Glück!";
			link.l1 = "Gleichfalls...";
			link.l1.go = "Contra_exit";
			if (sti(pchar.questTemp.Regata.Index != 1))
			{
				AddMoneyToCharacter(pchar, -50000);
				sTemp = pchar.questTemp.Regata.ContraIndex;
				pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp))+48;//задержка на 48 часов
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp)));
			}
			else
			{
				AddMoneyToCharacter(pchar, -30000);
				pchar.questTemp.Regata.AdversaryThirdTransition.Time.b = sti(pchar.questTemp.Regata.AdversaryThirdTransition.Time.b)+36;//задержка на 36 часов
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryThirdTransition.Time.b));
			}
		break;
		
		case "Contra_exit":
			DialogExit();
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("RegataContra_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "quest", "quest2", "none", "", "", "", 10.0);
			}
		break;
		//контрики с пушками
		
		//падре
		case "Regata_Padre":
			pchar.questTemp.Regata.BranderName = GenerateRandomNameToShip(ENGLAND);
			dialog.text = "Guten Tag, mein Sohn. Ich möchte dich begrüßen und dich demütig fragen: Möchtest du als loyaler Diener Englands und unseres großen Herrn zur Pfarrkasse beitragen?";
			link.l1 = "Padre, die Menschen tun Gutes, weil ihre Seelen es verlangen, nicht aus Zwang. Ich fange an zu glauben, dass jeder auf dem Archipel beschlossen hat, die Kapitäne der Regatta auszurauben...";
			link.l1.go = "Regata_Padre_exit";
			link.l2 = "Sicher, heiliger Vater. Wie viel wäre genug?";
			link.l2.go = "Regata_Padre_1";
		break;
		
		case "Regata_Padre_1":
			dialog.text = "Genau so viel wie dein Wunsch und deine Möglichkeiten es zulassen, mein Sohn. Unsere Gemeinde wird sich über selbst die kleinste Summe freuen.";
			Link.l1.edit = 4;			
			link.l1 = "";
			link.l1.go = "Regata_Padre_2";
		break;
		
		case "Regata_Padre_2":
			iTemp = sti(dialogEditStrings[4]);
			if (iTemp <= 0 || sti(pchar.money) < iTemp)
			{
				dialog.text = "Das ist die falsche Einstellung, mein Sohn. Wir alle haben Sünden, vergiss deine Seele nicht. Du wirst vor unserem Schöpfer erscheinen müssen... und vielleicht bald.";
				link.l1 = "Ich brauche deine Predigten nicht, heiliger Vater. Lebewohl.";
				link.l1.go = "Padre_exit";
				ChangeCharacterComplexReputation(pchar, "nobility", -3);
				AddQuestRecord("Regata", "35");
				break;
			}
			if (iTemp > 0 && iTemp <= 1000)//ничего не скажет
			{
				dialog.text = "Unsere Pfarrei und ich danken Ihnen für dieses bescheidene Geschenk.";
				link.l1 = "Sie sind willkommen, heiliger Vater.";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -iTemp);
				AddQuestRecord("Regata", "35");
			}
			if (iTemp > 1000 && iTemp <= 5000)//1 категория - намекнет
			{
				dialog.text = "Unsere Gemeinde und ich danken Ihnen für dieses Geschenk. Und ich möchte Sie warnen, mein Sohn, dass einige sündige Männer Ihnen Schaden zufügen wollen. Seien Sie vorsichtig auf dem Meer!";
				link.l1 = "Padre, jeden Tag planen Leute, etwas gegen mich zu unternehmen... Aber danke für Ihre Sorge um mein Schicksal.";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -iTemp);
				AddQuestRecord("Regata", "34");
				AddQuestUserData("Regata", "sMoney", iTemp);
			}
			if (iTemp > 5000 && iTemp <= 10000)//2 категория - скажет
			{
				dialog.text = "Ich danke Ihnen im Namen unserer Gemeinde für dieses wertvolle Geschenk. Im Gegenzug möchte ich Sie warnen, dass sich einige wirklich böse Menschen gegen Sie verschworen haben. Ich habe gehört, dass diese abscheulichen Abtrünnigen vorhaben, Ihr Schiff in diesem Hafen zu versenken\nSie haben bereits ein Schiff voller Schießpulver für diese böse Tat vorbereitet. Seien Sie vorsichtig, mein Sohn, diese verlorenen Seelen sind ernsthaft in ihren abscheulichen Absichten... Gott segne Sie!";
				link.l1 = "Danke, heiliger Vater. Ich werde aufmerksam sein.";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -iTemp);
				AddQuestRecord("Regata", "33");
				AddQuestUserData("Regata", "sMoney", iTemp);
			}
			if (iTemp > 10000)//3 категория - расскажет полностью
			{
				dialog.text = "Du bist sehr großzügig, mein Sohn. Die Bescheidenheit eines demütigen Dieners Gottes erlaubt es mir nicht, die gesamte Summe anzunehmen, die du für das Wohl unserer Kirche geben möchtest. Ich werde nur 10 000 Pesos nehmen\nIm Gegenzug möchte ich dich warnen, dass böse Menschen gegen dich verschwören. Ich habe gehört, dass diese abscheulichen Apostaten vorhaben, dein Schiff direkt in diesem Hafen zu versenken\nSie haben eine Logger voller Schießpulver vorbereitet, die '"+pchar.questTemp.Regata.BranderName+"', sie segelt unter der englischen Flagge, um sich dir ohne Verdacht zu nähern. Sei vorsichtig, mein Sohn, diese verlorenen Seelen meinen es ernst mit ihren abscheulichen Absichten.\nZerstöre sie, ich gebe dir Absolution für diese Sünde. Gott segne dich! Ich werde für dich beten, mein Sohn.";
				link.l1 = "Danke, heiliger Vater. Wenn diese Bastarde es wagen, etwas Schlimmes zu tun, werde ich sie direkt in die Hölle schicken!";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -10000);
				ChangeCharacterComplexReputation(pchar, "nobility", 2);
				AddQuestRecord("Regata", "32");
				AddQuestUserData("Regata", "sText", pchar.questTemp.Regata.BranderName);
			}
		break;
		
		case "Regata_Padre_exit":
			dialog.text = "Sei nicht zornig, mein Sohn. Zorn ist eine Sünde. Es ist dein Recht, keine Wohltätigkeit zu tun. Gehe in Frieden, mein Sohn.";
			link.l1 = "Auf Wiedersehen, heiliger Vater.";
			link.l1.go = "Padre_exit";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddQuestRecord("Regata", "35");					  
		break;
		
		case "Padre_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload7_back", "SentJons_church", "barmen", "stay", "ReturnRegataPadreNorm", 5);
		break;
		
		case "Regata_Spyglass":
			dialog.text = "Guten Tag an Sie, Kapitän! Mein Name ist "+npchar.name+" und ich würde gerne...";
			link.l1 = "... um mir etwas anzubieten... Habe ich recht, junge Dame?";
			link.l1.go = "Regata_Spyglass_1";
		break;
		
		case "Regata_Spyglass_1":
			dialog.text = "Natürlich, Kapitän! Und warum sind Sie so überrascht? Sie sind ein gut aussehender Seemann und nehmen an der Regatta teil, sicherlich ist jeder bereit, Ihnen nützliche maritime Sachen zu verkaufen.";
			link.l1 = "Also gut, Schönheit, du hast einen Punkt. Was hast du für mich?";
			link.l1.go = "Regata_Spyglass_2";
		break;
		
		case "Regata_Spyglass_2":
			if(hrand(11) > 10)//отличная труба
			{
				pchar.questTemp.Regata.Spy = "spyglass4";
				sTemp = "an excellent spyglass";
				pchar.questTemp.Regata.SpyPrice = 20000;
				pchar.questTemp.Regata.SpyIndex = 12;//выигрыш - 12 часов
			}
			else
			{
				if(hrand(11) < 6)//обычная труба
				{
					pchar.questTemp.Regata.Spy = "spyglass2";
					sTemp = "an ordinary spyglass";
					pchar.questTemp.Regata.SpyPrice = 1800;
					pchar.questTemp.Regata.SpyIndex = 4;//выигрыш - 4 часа
				}
				else//хорошая труба - как пригодится
				{
					pchar.questTemp.Regata.Spy = "spyglass3";
					sTemp = "a good spyglass";
					pchar.questTemp.Regata.SpyPrice = 10000;
					pchar.questTemp.Regata.SpyIndex = 8;//выигрыш - 8 часов
				}
			}
			dialog.text = "Hier, schau mal. Ich habe es von meinem Vater geerbt. Er war auch ein Seemann, genau wie du, und er hatte viele Navigationsdinge. Ich brauche es nicht, aber du wirst es sicher nützlich finden. Ich frage nur "+FindRussianMoneyString(sti(pchar.questTemp.Regata.SpyPrice))+" dafür.";
			if (sti(pchar.money) >= sti(pchar.questTemp.Regata.SpyPrice))
			{
				link.l1 = "Nun, nun..."+sTemp+"! Interessant! Ich sage, ich kaufe es dir ab. Für deine hübschen Augen. Also, willst du "+FindRussianMoneyString(sti(pchar.questTemp.Regata.SpyPrice))+" dafür? Bitte, nimm dein Geld.";
				link.l1.go = "Regata_Spyglass_3";
			}
			link.l2 = "Hm..."+sTemp+"? Nein, Mädchen, es tut mir leid, aber ich brauche es nicht. Ich habe bereits ein sehr schönes Fernrohr. Also... leider!";
			link.l2.go = "Regata_Spyglass_exit";
		break;
		
		case "Regata_Spyglass_3":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Regata.SpyPrice));
			GiveItem2Character(pchar, pchar.questTemp.Regata.Spy);
			dialog.text = "Danke, Kapitän. Ich hoffe, es wird Ihnen gut dienen. Ich freue mich, dass Sie es nützlich gefunden haben. Viel Glück bei der Regatta!";
			link.l1 = "Danke, "+npchar.name+"! Auf Wiedersehen.";
			link.l1.go = "Spyglass_exit";
			for (i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp))+sti(pchar.questTemp.Regata.SpyIndex);//купил трубу - выиграл время
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp)));
			}
		break;
		
		case "Regata_Spyglass_exit":
			dialog.text = "Wie schade, Kapitän. Ich hatte gehofft, dass es für Sie nützlich sein wird. Nun, ich werde versuchen, es jemand anderem zu verkaufen. Auf Wiedersehen!";
			link.l1 = "Auf Wiedersehen, "+npchar.name+".";
			link.l1.go = "Spyglass_exit";
			pchar.questTemp.Regata.AdversaryFourthTransition.Time.c = sti(pchar.questTemp.Regata.AdversaryFourthTransition.Time.c)-sti(pchar.questTemp.Regata.SpyIndex);//третий соперник выиграл время
		break;
		
		case "Spyglass_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "Regata_SiegeOfficer":
			dialog.text = "Grüße, Kapitän. Sind Sie nicht ein Teilnehmer der Regatta? Liege ich richtig?";
			link.l1 = "Ja. Und was ist der Deal, Offizier?";
			link.l1.go = "Regata_SiegeOfficer_1";
		break;
		
		case "Regata_SiegeOfficer_1":
			dialog.text = "Sie müssen bereits informiert sein, dass unsere Kolonie von einer spanischen Belagerung bedroht ist. Deshalb möchte unser Gouverneur mit Ihnen sprechen. Wären Sie so freundlich, ihn zu besuchen? Momentan ist die Angelegenheit sehr dringend.";
			link.l1 = "Hm... Sehr gut, ich werde sofort zu Seiner Exzellenz gehen, obwohl ich nicht wirklich verstehe, wie ich in die militärischen Operationen eingebunden sein kann.";
			link.l1.go = "Regata_SiegeOfficer_2";
		break;
		
		case "Regata_SiegeOfficer_2":
			dialog.text = "Sie sind beteiligt, Kapitän. Lassen Sie uns keine Zeit verschwenden und zur Residenz gehen. Folgen Sie mir.";
			link.l1.go = "Regata_SiegeOfficer_3";
		break;
		
		case "Regata_SiegeOfficer_3":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "Bridgetown_townhall", "goto", "governor1", "RegataSiegeHover", -1);
		break;
		
		case "Regata_SiegeOfficer_4":
			dialog.text = "Herr! Ich bin bereit, Zivilisten zu Ihrem Schiff zu schicken. Gehen wir jetzt?";
			link.l1 = "Ja, sicher. Wir werden sofort segeln. Sag den Leuten, sie sollen in die Langboote steigen.";
			link.l1.go = "Regata_SiegeOfficer_5";
		break;
		
		case "Regata_SiegeOfficer_5":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "RegataSiegeOpen", -1);
			for (i=1; i <=9; i++)
			{
				sld = characterFromId("RegataBridgWom_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "quest", "quest1", "none", "", "", "", 30);
			}
		break;
		
		case "Regata_SiegeOfficer_6":
			dialog.text = "Wir haben es geschafft... Sieht so aus, als wäre diese Schaluppe ein Späher des Geschwaders und diese kastilischen Bastarde waren auf Erkundungstour. Kapitän, bitte helfen Sie mir, die Frauen in die Höhlen zu bringen, es besteht die Möglichkeit, dass es noch mehr spanische Abteilungen gibt.";
			link.l1 = "Gut. Lass uns gehen!";
			link.l1.go = "Regata_SiegeOfficer_7";
		break;
		
		case "Regata_SiegeOfficer_7":
			DialogExit();
			sld = characterFromId("SiegeOfficer");
			LAi_ActorFollowEverywhere(sld, "", -1);
			pchar.quest.Regata_Siege3.win_condition.l1 = "location";
			pchar.quest.Regata_Siege3.win_condition.l1.location = "Barbados_cave";
			pchar.quest.Regata_Siege3.function = "RegataBarbadosCave";
		break;
		
		case "Regata_SiegeOfficer_8":
			dialog.text = "Dankbarkeit für Ihre Hilfe, Kapitän! Wenn es nicht für Sie und Ihren Mut gewesen wäre... Sie sind ein wahrer Held, Sie haben diese Operation trotz aller Gefahren und Ihrer eigenen Interessen abgeschlossen. Ich habe darüber nachgedacht, wie ich Sie belohnen könnte... und es gibt eine Möglichkeit, Ihre Chancen bei der Regatta zu verbessern.";
			link.l1 = "Interessant. Was ist dieser Weg?";
			link.l1.go = "Regata_skiper";
		break;
		
		case "Regata_Hovernor":
			dialog.text = "Grüße, Kapitän "+GetFullName(pchar)+". Es ist gut, dass du gekommen bist. Unsere Stadt braucht deine Hilfe.";
			link.l1 = "Herr, wenn Sie von der spanischen Eskadron sprechen, die gerade Ihre Kolonie stürmt, dann habe ich keine Ahnung, wie ich Ihnen helfen kann. Ich befehlige einen Schoner, kein Linienschiff...";
			link.l1.go = "Regata_Hovernor_1";
		break;
		
		case "Regata_Hovernor_1":
			dialog.text = "Hör mir zu, Kapitän, und du wirst verstehen. Wir stecken in ernsten Schwierigkeiten. Die Stadt ist von der spanischen Belagerung betroffen. Eine entscheidende Schlacht mit der Festung steht kurz bevor. Außerdem sind bereits einige hundert Spanier gelandet und haben jeden Ausgang aus der Stadt blockiert, jetzt können sie uns vom Meer und vom Land aus angreifen\nDie Garnison der Festung bereitet sich darauf vor, die Stadt vor der Geschwader zu verteidigen und es gibt nicht genug Soldaten in der Siedlung selbst. Jeder Mann, der eine Waffe handhaben kann, ist mobilisiert, aber was ist mit den anderen?\nEs gibt hundert Seelen von Frauen in Bridgetown. Kannst du dir vorstellen, was ihnen passieren wird, wenn es uns nicht gelingt, unsere Kolonie zu schützen? Ich glaube, dass du verstehst.";
			link.l1 = "Herr, ich verstehe Sie, aber, nochmals, wie kann ich helfen? Was wollen Sie von mir? Soll ich gegen Linienschiffe kämpfen oder meine Mannschaft in der Stadtmiliz einziehen?";
			link.l1.go = "Regata_Hovernor_2";
		break;
		
		case "Regata_Hovernor_2":
			switch (sti(Pchar.BaseNation))
			{
				case ENGLAND: sTemp = "You are English , help us to save English citizens and what is important - women!" break;
				case FRANCE: sTemp = "You are French, so you basically are our ally, help us to save English citizens and what is more important - women!" break;
				case SPAIN: sTemp = "I know that you are Spanish and these are your people in the sea, so I know that I am already asking for a lot, but these women are innocent and have nothing to do with this battle. So please I beg of you, help them!" break;
				case HOLLAND: sTemp = "I know that you are Dutch and our nations are at war, but you are participating in the English regatta under the English flag. Don't you think that it is right to fight for innocent and peaceful people, for women? Please captain, help them!" break;
			}
			dialog.text = "Weder noch. Ich bitte Sie nur um eine Sache. Bringen Sie die Frauen und Kinder mit Ihrem Schiff von hier weg. Es sind nicht viele von ihnen, ungefähr hundert. Bringen Sie sie zusammen mit Leutnant Mahony zum Harrison-Kap, er wird dafür sorgen, dass sie in der Höhle sicher sind.\nIch bin mir sicher, dass die Spanier sie nicht suchen werden. Ich habe keine Schiffe übrig, alles was wir hatten, wurde von der spanischen Eskadron versenkt. Sie sind meine letzte Hoffnung. Sie können sie in einer Reise zum Kap bringen, auch wenn Ihr Schiff überladen sein wird. Linienschiffe werden Ihnen nicht folgen.\nIch kann niemand anderen bitten, es zu tun. "+sTemp+"";
			link.l1 = "Herr, es tut mir leid, aber mein Schiff ist bereits überladen und sie wird nicht in der Lage sein, so viele Menschen auch für zwei Reisen zu halten. Jede zufällige Kanonenkugel, die sogar in der Nähe gefällt, wird mein Schiff und Ihre Frauen auf den Grund des Meeres schicken. Verzeihen Sie mir, aber ich kann Ihnen nicht helfen.";
			link.l1.go = "Regata_Hovernor_exit";
			link.l2 = "Sehr gut, Herr. Ich werde Ihnen helfen. Die Ehre des Seemanns verpflichtet mich dazu.";
			link.l2.go = "Regata_Hovernor_3";
		break;
		
		case "Regata_Hovernor_3":
			dialog.text = "Ich bin froh, dass Sie zugestimmt haben. Sie sind ein wahrer Soldat. Leutnant Mahony wird Frauen und Kinder zu Ihrem Schiff bringen. Gott sei mit Ihnen, Kapitän!";
			link.l1 = "Danke, Herr. Lassen wir keine Zeit verschwenden!";
			link.l1.go = "Regata_Hovernor_4";
		break;
		
		case "Regata_Hovernor_wait":
			dialog.text = "Beeil dich, Kapitän. Die Zeit rennt.";
			link.l1 = "Ich bin schon am Segeln!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_Hovernor_wait";
		break;
		
		case "Regata_Hovernor_exit":
			dialog.text = "Das ist unglaublich. Du wirst es nicht einmal versuchen? Nun, du bist in deinem Recht. Ich kann dir nichts abverlangen. Wärst du nur ein gewöhnlicher Kapitän, würde ich dein Schiff für das Wohl hundert Frauen konfiszieren, aber du nimmst an der Regatta teil und stehst daher unter dem Schutz des Generalgouverneurs der englischen Kolonien. Ich hatte gehofft, dass dein Gewissen dich übernehmen würde, doch ich lag falsch. Geh und möge Gott deiner Seele gnädig sein!";
			link.l1 = "Auf Wiedersehen, Herr.";
			link.l1.go = "Hovernor_exit";
		break;
		
		case "Hovernor_exit":
			DialogExit();
			pchar.quest.Regata_TH.over = "yes"; // belamour снять прерывание
			pchar.questTemp.Regata.AdversaryFifthTransition.Time.e = sti(pchar.questTemp.Regata.AdversaryFifthTransition.Time.e)-36;//пятый противник выиграл 36 часов
			ChangeCharacterComplexReputation(pchar, "nobility", -8);
			ChangeCharacterNationReputation(pchar, ENGLAND, -5);
			//вертаем губера в норму
			npchar.Dialog.Filename = "Common_Mayor.c";
			npchar.dialog.currentnode = "First time";
			//удаляем лейтенанта
			sld = characterFromId("SiegeOfficer");
			sld.lifeday = 0;
			//открываем ворота и выход в море
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Bridgetown_town", "reload1_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "reload2_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate1_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate_back", false);
			LocatorReloadEnterDisable("Bridgetown_Exittown", "reload3", false);
			//остров в норму
			n = FindIsland("Barbados");	
			DeleteAttribute(Islands[n], "DontSetShipInPort");
			//осаду снимем через 5 дней
			SetFunctionTimerCondition("RegataSiegeDelete", 0, 0, 5, false);
			for (i=1; i <=9; i++)//девок счистим
			{
				sld = characterFromId("RegataBridgWom_"+i);
				sld.lifeday = 0; // patch-7
				LAi_CharacterDisableDialog(sld);
			}
			AddQuestRecord("Regata", "38");
			AddQuestUserData("Regata", "sName", GetFullName(npchar));
		break;
		
		case "Regata_Hovernor_4":
			DialogExit();
			pchar.quest.Regata_TH.over = "yes"; // belamour снять прерывание
			NextDiag.CurrentNode = "Regata_Hovernor_wait";
			sld = characterFromId("SiegeOfficer");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "Bridgetown_town", "goto", "goto4", "", 10);
			pchar.quest.Regata_evacuation.win_condition.l1 = "location";
			pchar.quest.Regata_evacuation.win_condition.l1.location = "Bridgetown_town";
			pchar.quest.Regata_evacuation.function = "RegataSiegeEvacuation";
			AddQuestRecord("Regata", "36");
			AddQuestUserData("Regata", "sName", GetFullName(npchar));
		break;
		
		case "Regata_BridgWom":
			dialog.text = "Die Spanier sind hinter uns her! Gott, hilf uns!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_BridgWom";
		break;
		
		case "Regata_BridgWom_1":
			dialog.text = "Leutnant Mahony ist tot... es muss ein Alptraum sein. Er war ein tapferer Offizier. Kapitän, würden Sie uns bitte zu einer Höhle bringen? Bringen Sie uns einfach dorthin und wir werden uns selbst versorgen.";
			link.l1 = "Sicher. Folge mir!";
			link.l1.go = "Regata_BridgWom_2";
		break;
		
		case "Regata_BridgWom_2":
			DialogExit();
			for (i=1; i <=9; i++)
			{
				sld = characterFromId("RegataBridgWom_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			pchar.quest.Regata_Siege3.win_condition.l1 = "location";
			pchar.quest.Regata_Siege3.win_condition.l1.location = "Barbados_cave";
			pchar.quest.Regata_Siege3.function = "RegataBarbadosCave";
		break;
		
		case "Regata_BridgWom_3":
			dialog.text = "Hier sind wir... danke, Kapitän! Sie haben uns alle gerettet! Ich habe darüber nachgedacht, wie ich Sie belohnen könnte... es gibt eine Möglichkeit, Ihre Chancen bei der Regatta zu verbessern.";
			link.l1 = "Mach weiter.";
			link.l1.go = "Regata_skiper";
		break;
		
		case "Regata_skiper":
			pchar.questTemp.Regata.Name = GetFullName(npchar);
			dialog.text = "Fahrt ihr nach Port Royal? Der kürzeste Weg führt über Curacao. Kehrt zurück nach Bridgetown. Sucht einen Mann namens Woodrow Dougherty, er ist ein alter Seemann und ein erfahrener Navigator. Er kennt das Gebiet zwischen Barbados und Jamaika perfekt, er wäre euch eine große Hilfe\nDas wird euch viel kritische Zeit sparen, die ihr so dringend zum Gewinnen braucht. Findet den Mann in der örtlichen Kirche und sagt ihm, dass "+GetFullName(npchar)+" - hat dich geschickt, er wird dich nicht abweisen. Bring ihn nach Port Royal, er wollte sowieso dorthin segeln.";
			link.l1 = "Sehr gut! Ein guter Navigator wird mir nützlich sein. Lebewohl.";
			link.l1.go = "Regata_skiper_1";
		break;
		
		case "Regata_skiper_1":
			dialog.text = "Auf Wiedersehen, Kapitän! Viel Glück!";
			link.l1 = "Vielleicht werden wir uns wiedersehen...";
			link.l1.go = "Regata_skiper_2";
		break;
		
		case "Regata_skiper_2":
			DialogExit();
			AddQuestRecord("Regata", "37");
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			ChangeCharacterNationReputation(pchar, ENGLAND, 10);
			LAi_SetStayType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0; // patch-8
			for (i=1; i <=9; i++)
			{
				sld = characterFromId("RegataBridgWom_"+i);
				LAi_SetStayType(sld);
				LAi_CharacterDisableDialog(sld);
				sld.lifeday = 0; // patch-8
			}
			//вертаем губера в норму
			sld = characterFromId("Bridgetown_Mayor");
			sld.Dialog.Filename = "Common_Mayor.c";
			sld.dialog.currentnode = "First time";
			//открываем ворота и выход в море
			LocatorReloadEnterDisable("Shore4", "boat", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate1_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate_back", false);
			LocatorReloadEnterDisable("Bridgetown_Exittown", "reload3", false);
			LocatorReloadEnterDisable("Barbados_cave", "reload1", false);
			bQuestDisableMapEnter = false;
			//осаду снимем через 5 дней
			SetFunctionTimerCondition("RegataSiegeDelete", 0, 0, 5, false);
			RegataSiegeSkiper();//поставим Вудро в церковь
		break;
		
		case "Regata_SiegeSkiper":
			dialog.text = "Guten Tag. Möchten Sie etwas?";
			link.l1 = "Dein Name ist Woodrow Dougherty, habe ich Recht?";
			link.l1.go = "Regata_SiegeSkiper_1";
		break;
		
		case "Regata_SiegeSkiper_1":
			dialog.text = "Du hast recht. Wie kann ich dienen?";
			link.l1 = "Ich weiß, dass du ein erfahrener Navigator bist und die Gewässer zwischen Barbados und Curacao gut kennst. Ich weiß auch, dass du nach Port Royal willst. Ich bin Teilnehmer der Regatta und es gibt nur noch einen letzten Halt - Port Royal. Ich möchte dich bitten, meiner Crew als Navigator für diese letzte Reise beizutreten.";
			link.l1.go = "Regata_SiegeSkiper_2";
		break;
		
		case "Regata_SiegeSkiper_2":
			dialog.text = "Interessant... Und warum denkst du, dass ich mich deiner Crew anschließen werde?";
			link.l1 = "Nun, weil ich von dir gehört habe "+pchar.questTemp.Regata.Name+" mit allen Garantien, dass Sie nicht nein sagen werden. Und wegen meiner Hilfe für Bridgetown in diesem kritischen Moment...";
			link.l1.go = "Regata_SiegeSkiper_3";
		break;
		
		case "Regata_SiegeSkiper_3"://а тут - как уж свезет
			if(hrand(2) != 2)
			{
				dialog.text = "Von "+pchar.questTemp.Regata.Name+"? Ich verstehe jetzt, sicher. Also gut, Kapitän, ich werde Ihnen helfen, den kürzesten Weg nach Port Royal zu segeln. Wollen Sie jetzt in See stechen?";
				link.l1 = "Ja.";
				link.l1.go = "Regata_SiegeSkiper_4";
			}
			else
			{
				dialog.text = ""+pchar.questTemp.Regata.Name+"? Ich verstehe. Aber, Kapitän, ich kann meine Stadt in so einer gefährlichen Zeit nicht verlassen. Sie müssen mich als einen Soldaten verstehen, der uns uneigennützig geholfen hat\nIch möchte nicht, dass die Leute hinter meinem Rücken flüstern, dass der alte Woodrow vor der entscheidenden Schlacht gegen die Spanier geflohen ist. Ich werde bleiben. Hege keine Groll, Kapitän.";
				link.l1 = "Und das ist dein letztes Wort? Aber ich habe deiner Kolonie geholfen...";
				link.l1.go = "Regata_SiegeSkiper_6";
			}
		break;
		
		case "Regata_SiegeSkiper_4":
			dialog.text = "Lassen wir keine Zeit verlieren. Lass mich nur meine Sachen packen und ich stehe zu deiner Verfügung.";
			link.l1 = "Meine Matrosen werden auf dich am Pier warten und dich zur 'Saint Catherine' bringen. Danke, Woodrow!";
			link.l1.go = "SiegeSkiper_hire";
		break;
		
		case "Regata_SiegeSkiper_6":
			dialog.text = "Kapitän, die Regatta ist ein Sport und die spanische Belagerung meiner Heimat ist ein Leben. Ich gehe mit dir nirgendwohin. Und ich wiederhole mich, du musst mich verstehen - Ehre und Pflicht bedeuten in dieser Welt noch etwas. Das ist mein letztes Wort und ich werde es nicht ändern\nAllerdings kann ich dir einen Rat geben, wie du auf dem sichersten Weg in kürzester Zeit dorthin gelangst, segel Nordwesten Richtung Dominica und von dort aus machst du dich auf den Weg nach Martinque oder Guadeloupe, je nach dir und dem Wind. Dann segel direkt Richtung Port-Royal, oder du könntest an Curacao vorbeisegeln, was ich nicht empfehlen würde, aber wenn du mit den Holländern gut zurechtkommst, dann auf jeden Fall.";
			link.l1 = "Nun, danke... aber ich bin enttäuscht. Auf Wiedersehen, Woodrow.";
			link.l1.go = "SiegeSkiper_exit";
		break;
		
		case "SiegeSkiper_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
		break;
		
		case "SiegeSkiper_hire":
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.loyality = 25;
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			//пересчитываем время пятого перехода
			for (i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				pchar.questTemp.Regata.AdversaryFifthTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversaryFifthTransition.Time.(sTemp))+18+(rand(18));//выигрыш до 1.5 суток
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp)));
			}
			SetFunctionTimerCondition("SiegeSkiperOver", 0, 0, 15, false);//чтобы не присвоил офицера
			DialogExit();
		break;
		
		case "Regata_Finish":
		iTest = FindColony("Portroyal"); 
		if (iTest != -1)
		{
			rColony = GetColonyByIndex(iTest);
			sFrom_sea = rColony.from_sea;
		}
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
		{
			//снимаем запреты
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			bool bRegLugger = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
			if (CheckAttribute(pchar, "questTemp.Regata.Breach") || !CheckAttribute(pchar, "questTemp.Regata.Bridgetown") || GetCompanionQuantity(pchar) > 1 || !bRegLugger || pchar.Ship.Name != "Saint Catherine")
			{
				dialog.text = "Sie haben die Regeln der Regatta auf der allerletzten Etappe gebrochen. Ihr Ergebnis wurde disqualifiziert. Ich habe Ihnen, Kapitän, nichts mehr zu sagen.";
				link.l1 = "Eh...was zur Hölle! Nun, es gibt nichts zu tun, du warst zu aufmerksam. Lebewohl!";
				link.l1.go = "exit";
				npchar.lifeday = 1;
				DeleteAttribute(pchar, "questTemp.Regata");
				AddQuestRecord("Regata", "45");
				CloseQuestHeader("Regata");
			}
			else
			{
				n=1;
				for (i=1; i <=5; i++)
				{
					if (i==1) sTemp = "a";
					if (i==2) sTemp = "b";
					if (i==3) sTemp = "c";
					if (i==4) sTemp = "d";
					if (i==5) sTemp = "e";
					if (pchar.questTemp.Regata.AdversaryFifthTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.FifthTransitionTime)) n++;
					pchar.questTemp.Regata.Result = n;//место в регате
				}
				if (n==1)
				{
					dialog.text = "Kapitän "+GetFullName(pchar)+", meine Gratulation! Es hat "+sti(pchar.questTemp.Regata.FifthTransitionTime)+" Stunden, um die Regatta zu beenden und du hast alle deine Gegner weit hinter dir gelassen. Das ist ein bemerkenswertes Ergebnis!";
					link.l1 = "Danke für Ihre freundlichen Worte, Herr!";
					link.l1.go = "First_result";
				}
				else
				{
					if (n==6)
					{
						dialog.text = "Kapitän, ach, aber Ihr Ergebnis ist das schlechteste, Sie haben ausgegeben "+sti(pchar.questTemp.Regata.FifthTransitionTime)+" Stunden. Sei nicht traurig, du hattest wirklich harte Gegner.";
						link.l1 = "Ich bin nicht traurig, Herr. Ich freue mich, dass ich an der Regatta teilgenommen und meine Fähigkeiten erprobt habe.";
						link.l1.go = "Other_result";
						AddQuestRecord("Regata", "44");
						CloseQuestHeader("Regata");
					}
					else
					{
          				dialog.text = "Kapitän, Sie sind in "+n+"ter Platz. Herzlichen Glückwunsch zum erfolgreichen Ergebnis, Sie haben eine würdige Zeit gezeigt - "+sti(pchar.questTemp.Regata.FifthTransitionTime)+" Stunden. Glückwunsch trotz deines Verlustes!";
						link.l1 = "Es ist in Ordnung, Herr. Ich bin froh, dass ich in diesem harten Wettbewerb ein gutes Ergebnis erzielt habe.";
						link.l1.go = "Other_result";
						if (n==2) AddQuestRecord("Regata", "40");
						if (n==3) AddQuestRecord("Regata", "41");
						if (n==4) AddQuestRecord("Regata", "42");
						if (n==5) AddQuestRecord("Regata", "43");
						CloseQuestHeader("Regata");
					}
				}
			}
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("SiegeSkiper");
			sld = &Characters[sti(Pchar.questTemp.FiringOfficerIDX)];
			CheckForReleaseOfficer(sti(Pchar.questTemp.FiringOfficerIDX));
			RemovePassenger(Pchar, sld);
			DeleteAttribute(sld, "Payment");
			DeleteAttribute(Pchar, "questTemp.FiringOfficerIDX");//удаляем из офицеров
			log_info("Woodrow Dougherty has landed");
			pchar.quest.SiegeSkiperOver.over = "yes"; //снять таймер
		}
		else
		{
			dialog.text = "Herr, darf ich Sie etwas fragen - wo ist Ihr Schiff? Ich sehe es nicht...";
			link.l1 = "Es tut mir leid, Herr. Ich bringe sie sofort zum Hafen.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_Finish";
		}
		break;
		
		case "First_result":
			if (CheckAttribute(pchar, "questTemp.Regata.Rate")) sTemp = "Come and see me in my office. I will give you your prize for your stake.";
			else sTemp = "And if you had made a stake on your victory as I offered you to, you would have gotten an extra prize too.";
			dialog.text = "Besuchen Sie morgen den Generalgouverneur und er wird Ihnen Ihre 250.000 Pesos und wertvolle Geschenke geben. "+sTemp+" Verlassen Sie nicht die Stadt, gemäß den Traditionen werden die Preise dem Stadtschatzhaus übergeben, falls der Gewinner sie nicht innerhalb einer Woche abholt.";
			link.l1 = "Ich habe verstanden, Herr. Ich werde ihn morgen besuchen!";
			link.l1.go = "First_result_1";
		break;
		
		case "First_result_1":
			DialogExit();
			//npchar.lifeday = 7;
			Achievment_Set("ach_09");
			npchar.dialog.currentnode = "Other_result_repeat";
			pchar.questTemp.Regata.Win = "true";
			pchar.quest.Regata_Final.win_condition.l1 = "Timer";
			pchar.quest.Regata_Final.win_condition.l1.date.hour  = 6.0;
			pchar.quest.Regata_Final.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Regata_Final.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Regata_Final.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Regata_Final.function = "RegataFinal";
			SetFunctionTimerCondition("RegataFinalOver", 0, 0, 8, false);//таймер не снимаем - через 8 дней подчистится все автоматически
			// слухи
			AddSimpleRumour("Ah, you are the legendary captain, the winner of the regatta! It's such a pleasure to see you in flesh!", ENGLAND, 60, 10);
			AddSimpleRumour("Ha, look at this, a master of wind and waves, the winner of the regatta! You have my respect...", ENGLAND, 60, 10);
			AddSimpleRumour("Oh, a great sailor, a king of the wind and the sea, the winner of regatta has visited our city! We are glad to see you, captain!", ENGLAND, 60, 10);
			AddSimpleRumour("Oh, yes I was lucky to chat with a living legend, the captain who is capable of crossing the archipelago in three days even facing a headwind! My respects, captain!", ENGLAND, 60, 10);
			AddSimpleRumour("Ah, so you are the legendary captain, the winner of the regatta! Pleasure to see you!", FRANCE, 60, 10);
			AddSimpleRumour("Ha, aren't you the master of wind and waves, the winner of the regatta! You have my respects...", FRANCE, 60, 10);
			AddSimpleRumour("Oh, a great sailor, a king of the wind and the sea, the winner of regatta has visited our city! We are glad to see you, captain!", FRANCE, 60, 10);
			AddSimpleRumour("Oh, yes I was lucky to chat with a living legend, the captain capable of crossing the archipelago in three days even facing a headwind! My respects, captain!", FRANCE, 60, 10);
			// экспа
			AddComplexSeaExpToScill(2000, 300, 300, 0, 500, 500, 0);
			AddCharacterExpToSkill(pchar, "Leadership", 2000);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 1000);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 15);
			ChangeOfficersLoyality("good_all", 3);
			AddQuestRecord("Regata", "39");
			CloseQuestHeader("Regata");
		break;
		
		case "Other_result":
			dialog.text = "Es ist gut, eine ehrenhafte Antwort zu hören. Viel Glück, Kapitän!";
			link.l1 = "Auf Wiedersehen, Herr.";
			link.l1.go = "Other_result_1";
		break;
		
		case "Other_result_1":
			DialogExit();
			npchar.dialog.currentnode = "Other_result_repeat";
			SetFunctionTimerCondition("RegataFinalOver", 0, 0, 1, false);
			// экспа
			AddComplexSeaExpToScill(500, 100, 100, 0, 100, 100, 0);
			AddCharacterExpToSkill(pchar, "Leadership", 200);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "Other_result_repeat":
			dialog.text = "Brauchen Sie etwas anderes, Kapitän?";
			link.l1 = "Nein... es ist nichts.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Other_result_repeat";
		break;
		
		case "Give_advantage":
			dialog.text = "Ach, da bist du ja, Herr "+GetFullName(pchar)+". Schön dich zu sehen. Bist du hier für deinen Preis? Er ist bereit für dich.";
			link.l1 = "Es ist gut zu hören, dass! Wie groß ist mein zusätzlicher Preis?";
			link.l1.go = "Give_advantage_1";
		break;
		
		case "Give_advantage_1":
			dialog.text = "Unter Berücksichtigung aller Einsätze ist Ihr endgültiger Preis "+FindRussianMoneyString(makeint(pchar.questTemp.Regata.Advantage))+". Bitte, nimm es. Herzlichen Glückwunsch!";
			link.l1 = "Danke!";
			link.l1.go = "Give_advantage_2";
		break;
		
		case "Give_advantage_2":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Regata.Advantage));
			dialog.text = "Sicher, Ihre Beliebtheit unter den Bürgern von Port Royal ist gewachsen. Ich denke, dass Sie das sehen können... aber ach, das Gedächtnis der Leute ist kurz. Also baden Sie im Ruhm, solange er noch so hell ist!";
			link.l1 = "Sie sprechen von den schönsten Dingen, Herr... Nun, lassen Sie uns sehen, wie es ist, im Ruhm zu baden. Auf Wiedersehen! Es war ein Vergnügen.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Other_result_repeat";
		break;
		
		case "Regata_CitMan_1":
			if (CheckAttribute(pchar, "questTemp.Regata"))
			{
				if (CheckAttribute(pchar, "questTemp.Regata.Result"))
				{
					if (sti(pchar.questTemp.Regata.Result) == 1)
					{
						dialog.text = "Herzlichen Glückwunsch zu Ihrem Sieg, Kapitän! Ein ausgezeichnetes Ergebnis!";
						link.l1 = "Danke!";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "Sei nicht traurig, Kapitän. Es ist nicht leicht, die Regatta zu gewinnen, schon die Teilnahme daran ist ein Privileg!";
						link.l1 = "Mach dir keine Sorgen um mich. Ich bin mit meinem Ergebnis zufrieden.";
						link.l1.go = "exit";
					}
				}
				else
				{
					dialog.text = "Freut mich, dich zu sehen, Kapitän! Du solltest dich bei Herrn Stevenson melden.";
					link.l1 = "Ich verstehe. Ich bin auf dem Weg zu ihm!";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Ach, Kapitän, warum sind Sie so gescheitert und das auf der allerletzten Stufe!";
				link.l1 = "Ja, so dumm von mir...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_CitMan_1";
		break;
		
		case "Regata_CitWom_1":
			if (CheckAttribute(pchar, "questTemp.Regata"))
			{
				if (CheckAttribute(pchar, "questTemp.Regata.Result"))
				{
					if (sti(pchar.questTemp.Regata.Result) == 1)
					{
						dialog.text = "Herzlichen Glückwunsch zu Ihrem Sieg, Kapitän! Ein hervorragendes Ergebnis!";
						link.l1 = "Danke!";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "Sei nicht traurig, Kapitän. Es ist nicht einfach, die Regatta zu gewinnen, schon die Teilnahme ist ein Privileg!";
						link.l1 = "Mach dir keine Sorgen um mich. Ich bin mit meinem Ergebnis zufrieden.";
						link.l1.go = "exit";
					}
				}
				else
				{
					dialog.text = "Freut mich, Sie zu sehen, Kapitän! Sie sollten sich bei Sir Stevenson anmelden.";
					link.l1 = "Ich verstehe. Ich bin auf dem Weg!";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Ach, Kapitän, warum hast du so versagt und das auf der allerletzten Etappe!";
				link.l1 = "Ja, so dumm von mir...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_CitWom_1";
		break;
		
		case "Regata_CitHorse_1":
			if (CheckAttribute(pchar, "questTemp.Regata"))
			{
				if (CheckAttribute(pchar, "questTemp.Regata.Result"))
				{
					if (sti(pchar.questTemp.Regata.Result) == 1)
					{
						dialog.text = "Glückwunsch zu Ihrem Sieg, Kapitän! Ein ausgezeichnetes Ergebnis!";
						link.l1 = "Danke dir!";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "Sei nicht traurig, Kapitän. Es ist nicht einfach, in der Regatta zu gewinnen, selbst die Teilnahme daran ist ein Privileg!";
						link.l1 = "Mach dir keine Sorgen um mich. Ich bin zufrieden mit meinem Ergebnis.";
						link.l1.go = "exit";
					}
				}
				else
				{
					dialog.text = "Schön dich zu sehen, Kapitän! Sie sollten sich anmelden, indem Sie mit Sir Stevenson sprechen.";
					link.l1 = "Ich verstehe. Ich bin unterwegs!";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Ach, Kapitän, warum haben Sie so versagt und das auf der allerletzten Stufe!";
				link.l1 = "Ja, so dumm von mir...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_CitHorse_1";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

void CreateRegataAdversaries()
{
	string sTemp;
	for (int i=0; i<=4; i++)
	{
	if (i==0) sTemp = "a";
	if (i==1) sTemp = "b";
	if (i==2) sTemp = "c";
	if (i==3) sTemp = "d";
	if (i==4) sTemp = "e";
	pchar.questTemp.Regata.AdversaryName.(sTemp) = GenerateRandomName_Generator(i, "man");
	pchar.questTemp.Regata.AdversaryShipName.(sTemp) = GenerateRandomNameToShip(ENGLAND);
	pchar.questTemp.Regata.AdversarySpeed.(sTemp) = 0.4+frand(0.9);
	log_testinfo(FindRussianDaysString(stf(pchar.questTemp.Regata.AdversarySpeed.(sTemp))));
	}
}

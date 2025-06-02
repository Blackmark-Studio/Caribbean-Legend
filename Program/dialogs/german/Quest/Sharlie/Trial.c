// диалоги НПС по квесту 'Карибские нравы'
void ProcessDialogEvent()
{
	ref NPChar, sld, rColony;
	aref Link, NextDiag;
	int iTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Was willst du?";
			link.l1 = "Nein, nichts.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// Жерар Лекруа
		case "lecrua":
			pchar.quest.Trial_LineOver.over = "yes"; //снять таймер
			dialog.text = "Guten Nachmittag. Sie müssen sein "+GetFullName(pchar)+"?";
			link.l1 = "Sie haben recht, Monsieur LeCroix. Kapitän "+GetFullName(pchar)+" zu Ihren Diensten. Fadey der Moskowiter hat Sie mir empfohlen...";
			link.l1.go = "lecrua_1";
			DelLandQuestMark(npchar);
		break;
		
		case "lecrua_1":
			iTemp = FindColony("Baster");
			rColony = GetColonyByIndex(iTemp);
			bOk = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			dialog.text = "Ja, ja. Mein lieber Freund Fadey hat mir ausführlich von dir und deiner Situation erzählt. Ich wusste, dass du es bist, sobald ich dich in der Tür sah. Sag mir Kapitän, was für ein Schiff hast du?";
			if(sti(pchar.ship.type) == SHIP_NOTUSED || !bOk)
			{
				link.l1 = "Ach...Ich habe im Moment kein Schiff, Monsieur...";
				link.l1.go = "lecrua_noship";
			}
			else
			{
				link.l1 = "Ich habe ein "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(RealShips[sti(pchar.ship.type)].basetype),"Name")))+", ihr Name ist "+pchar.ship.name+".";
				if (6-sti(RealShips[sti(pchar.ship.type)].Class) < 0) link.l1.go = "lecrua_badship";
				else link.l1.go = "lecrua_2";
			}
		break;
		
		case "lecrua_noship":
			dialog.text = "Ha! Nun, was für ein Kapitän sind Sie dann, wenn Sie kein Schiff haben? Es tut mir leid, monsieur, aber in diesem Fall habe ich keine Arbeit für Sie. Alles Gute, grüßen Sie Fadey von mir!";
			link.l1 = "Hm...";
			link.l1.go = "lecrua_exit";
			sTotalTemp = "I don't have a ship at the moment";
		break;
		
		case "lecrua_badship":
			dialog.text = "Nun, das geht einfach nicht. Das ist kein Schiff, Herr, das ist ein Boot! Leider, Monsieur, passen Sie nicht in die Rolle. Grüßen Sie Fadey von mir, guten Tag!";
			link.l1 = "Hm...";
			link.l1.go = "lecrua_exit";
			sTotalTemp = "My ship wasn't big enough for him";
		break;
		
		case "lecrua_exit":
			DialogExit();
			npchar.lifeday = 0;
			NextDiag.CurrentNode = "lecrua_repeat";
			AddQuestRecord("Trial", "3");
			AddQuestUserData("Trial", "sText", sTotalTemp);
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		
		case "lecrua_repeat":
			dialog.text = "Wir haben doch schon alles besprochen, Monsieur. Oder etwa nicht?";
			link.l1 = "Ja, Monsieur LeCroix... Ich bin auf dem Weg.";
			link.l1.go = "exit";
			NextDiag.TempNode = "lecrua_repeat";
		break;
		
		case "lecrua_2":
			dialog.text = "Ausgezeichnet. In diesem Fall passen Sie gut zu mir. Sind Sie bereit, sofort in See zu stechen?";
			link.l1 = "Ja, Monsieur, ich bin bereit. Was muss ich tun?";
			link.l1.go = "lecrua_3";
		break;
		
		case "lecrua_3":
			sld = characterFromId("BasTer_trader");
			dialog.text = "Sie müssen eine kleine Ladung Schießpulver und Bomben nach Port-au-Prince, auf Französisch Hispaniola, liefern. Der Kommandant wartet schon eine Weile darauf, also verlieren Sie keine Zeit, Sie haben noch etwa zehn Tage\nRespektiert "+GetFullName(sld)+" wird sich um die Lieferung und das Laden auf Ihr Schiff kümmern. Der Kommandant wird Ihnen fünftausend Achtstücke für den Job bezahlen.";
			link.l1 = "Und das ist die ganze Arbeit?";
			link.l1.go = "lecrua_4";
		break;
		
		case "lecrua_4":
			dialog.text = "Ach keineswegs, monsieur. Der Kommandant wird Ihnen die wirkliche Aufgabe erklären, wenn Sie die Munition bringen. Diese Fracht ist nur ein kleiner Aperitif der Arbeit, die Sie vor sich haben. Aber haben Sie keine Angst, wenn Sie die Arbeit gut machen, werden Sie einiges an Geld verdienen.";
			link.l1 = "Sie haben meine ungeteilte Aufmerksamkeit, Monsieur. Mein Schiff ist bereit, die Ladung an Bord zu nehmen.";
			link.l1.go = "lecrua_5";
		break;
		
		case "lecrua_5":
			dialog.text = "Lassen Sie uns dann keine Zeit verschwenden, Kapitän! Machen Sie sich auf den Weg zu Ihrem Schiff und bereiten Sie sich darauf vor, abzulegen.";
			link.l1 = "Ich gehe!";
			link.l1.go = "lecrua_6";
		break;
		
		case "lecrua_6":
			DialogExit();
			NextDiag.CurrentNode = "lecrua_repeat";
			AddQuestRecord("Trial", "4");
			pchar.questTemp.Trial = "fraht";
			AddMapQuestMarkCity("PortPax", false);
			// belamour legendary edition халява по чекбоксу
			if(!bImCasual) SetFunctionTimerCondition("Trial_FrahtFail", 0, 0, 17, false); // таймер
			else NewGameTip("Exploration mode: timer is disabled.");
			SetFunctionTimerCondition("Trial_LecruaHide", 0, 0, 1, false); // таймер
			// груз
			SetCharacterGoods(pchar, GOOD_BOMBS, GetCargoGoods(pchar, GOOD_BOMBS)+2500);
			SetCharacterGoods(pchar, GOOD_POWDER, GetCargoGoods(pchar, GOOD_POWDER)+2500);
			// Sinistra Пасхалка с Диего
			pchar.quest.VsD_DiegoNachalo.win_condition.l1 = "Ship_location";
			pchar.quest.VsD_DiegoNachalo.win_condition.l1.location = "PortPax_town";
			PChar.quest.VsD_DiegoNachalo.win_condition = "VsD_DiegoNachalo";
			
			// отключить все враждебные энкаунтеры на глобальной карте
			pchar.worldmapencountersoff = "1";
			SetFunctionTimerCondition("DelNavigatorNoShow", 0, 0, 180, false);
			pchar.systeminfo.tutorial.navigatorTrial = true;
		break;
		
		// Флориан Шоке
		case "florian_deck":
			if(!bImCasual) pchar.quest.Trial_CannonFail.over = "yes"; // belamour legendary edition снять таймер
			DelMapQuestMarkShore("shore47");
			DelLandQuestMark(npchar);
			sld = CharacterFromID("PortRoyal_shipyarder");
			if(CheckAttribute(sld, "TrialDelQuestMark"))
			{
				DeleteAttribute(sld, "TrialDelQuestMark");
				DelLandQuestMark(sld);
				DelMapQuestMarkCity("PortRoyal");
			}
			dialog.text = "Womit kann ich Ihnen helfen, Herr?";
			link.l1 = "Guten Nachmittag, Kapitän. Sie sind Florian Shoke, nehme ich an?";
			link.l1.go = "florian_deck_1";
		break;
		
		case "florian_deck_1":
			dialog.text = "Ich bin es. Und du bist das Paketschiff aus Port-au-Prince, wenn ich mich nicht irre?";
			link.l1 = "Aye, ich habe fünfzehn Kanonen für dich. Die Frist war knapp, ich habe es gerade noch geschafft...";
			link.l1.go = "florian_deck_2";
		break;
		
		case "florian_deck_2":
			if (GetSquadronGoods(pchar, GOOD_CANNON_24) < 15)
			{
				dialog.text = "Hm. Seltsamer Humor, den Sie haben, Herr! Aus irgendeinem Grund sehe ich keine fünfzehn Kanonen, die von Ihrem Schiff entladen werden...";
				link.l1 = "Nun, Sie sehen, wir hatten ein Leck und mussten einen Teil der Ladung über Bord werfen...";
				link.l1.go = "florian_deck_fail";
			}
			else
			{
				dialog.text = "Freut mich, dich zu sehen, Kapitän?..";
				link.l1 = ""+GetFullName(pchar)+". Kapitän "+GetFullName(pchar)+".";
				link.l1.go = "florian_deck_3";
			}
		break;
		
		case "florian_deck_3":
			dialog.text = "Freut mich, Sie kennenzulernen. Lassen Sie uns keine Zeit verschwenden und diese Kanonen an Bord holen. Das wird nicht einfach sein, also brauche ich Ihre Männer zur Hilfe.";
			link.l1 = "Wir schaffen das. Du da, bring das Flaschenzug am Rahholz in Ordnung!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Trial_TakeCannons");
		break;
		
		case "florian_deck_fail":
			dialog.text = "Du verfluchter Idiot! Wenn du nicht einmal diese einfache Aufgabe bewältigen kannst, wirst du sicher im nächsten Sturm untergehen. Mach dich auf den Weg zurück zu deinem Schiff, Kapitän, und mach etwas, was du besser kannst, wie Blumen an noble Damen zu liefern. Besser noch, segle zurück nach Europa und überlasse die Neue Welt den echten Männern. Guten Tag, Herr!";
			link.l1 = "Aber...";
			link.l1.go = "florian_deck_fail_1";
		break;
		
		case "florian_deck_fail_1":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			RemoveCharacterGoods(pchar, GOOD_CANNON_24, GetCargoGoods(pchar, GOOD_CANNON_24));
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			sld = characterFromId("Lecrua");
			sld.lifeday = 0;
			AddQuestRecord("Trial", "10");
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
			ChangeCharacterNationReputation(pchar, FRANCE, -3);
		break;
		
		case "florian_deck_4":
			dialog.text = "Puh, das war eine durstige Arbeit! Ich danke Ihnen für den Dienst, Kapitän! Nehmen Sie Ihre Belohnung, zweihundert Dublonen.";
			link.l1 = "Danke dir!";
			link.l1.go = "florian_deck_5";
		break;
		
		case "florian_deck_5":
			TakeNItems(pchar, "gold_dublon", 200);
			Log_Info("You've received 200 doubloons.");
			PlaySound("interface\important_item.wav");
			dialog.text = "Aber das ist noch nicht alles, Kapitän. Möchten Sie weitere zweihundertfünfzig goldene Doppel-Escudos verdienen?";
			link.l1 = "Das klingt vielversprechend, aber es hängt davon ab, was Sie mich dafür tun lassen wollen, Herr.";
			link.l1.go = "florian_deck_6";
		break;
		
		case "florian_deck_6":
			dialog.text = "Ich werde nicht lügen, es ist gefährlich. Wie du vielleicht schon weißt, liege ich auf der Lauer nach einer spanischen schweren Galeone mit wertvoller Ladung. Das Schiff wurde zur Reparatur in die Docks gebracht. Laut meinen Quellen sollte sie gestern in See stechen, aber das ist nicht geschehen.\nAußerdem kam mein Agent in Portobello nicht zum vereinbarten Treffpunkt, um die Updates zu liefern, auf die ich gewartet habe. Ich vermute, dass die Spanier ihn verhaftet haben. Ich zahle dir, wenn du dich nach Portobello schleichen und zwei Dinge herausfinden kannst: Warum ist die Galeone noch dort und was ist mit meinem Agenten passiert. Bist du dabei?";
			link.l1 = "Ich fürchte, mir fehlt die richtige Ausbildung für eine solche Operation. Ich bin ein Gentleman, kein Spion. Ich könnte selbst in Schwierigkeiten geraten und wäre nicht in der Lage, Ihnen zu helfen.";
			link.l1.go = "florian_deck_bye";
			link.l2 = "Klingt gefährlich, aber profitabel. Ich werde es riskieren. Wie heißt dein Mann und wie heißt die Galeone?";
			link.l2.go = "florian_deck_7";
		break;
		
		case "florian_deck_bye":
			dialog.text = "Nun, fühlen Sie sich nicht berechtigt? Ich verstehe Sie. Auf Wiedersehen dann, Kapitän, nochmals vielen Dank für Ihre Hilfe!";
			link.l1 = "Alles Gute, Monsieur Shoke.";
			link.l1.go = "florian_deck_bye_1";
		break;
		
		case "florian_deck_bye_1":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			sld = characterFromId("Lecrua");
			sld.lifeday = 0;
			AddQuestRecord("Trial", "11");
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		
		case "florian_deck_7":
			dialog.text = "Ja, hör gut zu. Mein Mann heißt Sylvan Laforet, aber in Portobello ist er als Jaime Silicio bekannt, ein Händler. Die Galeone heißt 'Alacantara'. Ich rate dir, nachts durch die Stadttore zu gehen, durch den Dschungel. Die Wächter von Portobello sind heutzutage sehr misstrauisch, ganz zu schweigen davon, dass Sylvans Verschwinden nichts Gutes für ihn lebend und gesund verheißt. Du hast zwei Tage Zeit, bis ich hier raus muss, bevor die spanischen Patrouillen uns finden. Viel Glück, Monsieur!";
			link.l1 = "Bis bald, Monsieur Shoke...";
			link.l1.go = "florian_deck_8";
		break;
		
		case "florian_deck_8":
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true; // доступно ожидание и sailto
			DialogExit();
			npchar.DeckDialogNode = "florian_deck_repeat";
			NextDiag.CurrentNode = "florian_deck_repeat";
			pchar.questTemp.Trial = "spy";
			AddQuestRecord("Trial", "12");
			// belamour legendary edition -->
			if(!bImCasual) 
			{
				pchar.quest.trial_spy_over.win_condition.l1 = "Timer";
				pchar.quest.trial_spy_over.win_condition.l1.date.hour  = sti(GetTime() + 2);
				pchar.quest.trial_spy_over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2);
				pchar.quest.trial_spy_over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
				pchar.quest.trial_spy_over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2);
				pchar.quest.trial_spy_over.function = "Trial_SpyTimeOver";
			}
			else NewGameTip("Exploration mode: timer is disabled.");
			// <-- legendary edition
			//Log_Info("You have received amulet 'Gypsy's fan'");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "obereg_4");
			pchar.quest.NewGameTip5.win_condition.l1 = "location";
			pchar.quest.NewGameTip5.win_condition.l1.location = "PortoBello_town";
			pchar.quest.NewGameTip5.function = "ShowNewGameTip";
			pchar.quest.NewGameTip5.text = "Guards are less suspicious when you walk at slow pace!";
			
			pchar.quest.Trial_CreatHabitue.win_condition.l1 = "location";
			pchar.quest.Trial_CreatHabitue.win_condition.l1.location = "PortoBello_tavern";
			pchar.quest.Trial_CreatHabitue.function = "Trial_CreatHabitue";
			
			pchar.quest.Tutorial_stealth.win_condition.l1 = "location";
			pchar.quest.Tutorial_stealth.win_condition.l1.location = "PortoBello_ExitTown";
			pchar.quest.Tutorial_stealth.function = "Tutorial_stealth";
			
			QuestPointerToLoc("shore47", "reload", "reload1_back");
			QuestPointerToLoc("PortoBello_Jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("PortoBello_Jungle_01", "reload", "reload3_back");
			QuestPointerToLoc("PortoBello_ExitTown", "reload", "reload4");
			QuestPointerToLoc("PortoBello_Town", "reload", "reload41_back");
			QuestPointerToLoc("PortoBello_Town", "reload", "reload4_back");
		break;
		
		case "florian_deck_repeat":
			dialog.text = "Wir haben doch alles besprochen, Kapitän, oder?";
			link.l1 = "Ja. Ich bin auf dem Weg.";
			link.l1.go = "exit";
			NextDiag.TempNode = "florian_deck_repeat";
		break;
		
		case "florian_failspy":
			pchar.quest.trial_spy_over.over = "yes"; //снять прерывание
			dialog.text = "Wie laufen die Dinge, Kapitän? Was konnten Sie herausfinden?";
			link.l1 = "Die Dinge laufen schlecht, Monsieur Shoke. Ich bin kein guter Spion, sie haben mich sehr schnell entdeckt. Ich musste die Stadt fliehen, nachdem ich einige Wächter bekämpft hatte. Das Einzige, was ich herausfinden konnte, ist, dass Ihr Mann Sylvan Laforet verhaftet wurde und im Gefängnis festgehalten wird.";
			link.l1.go = "florian_failspy_1";
		break;
		
		case "florian_failspy_1":
			dialog.text = "Verdammt noch mal! Das ist nicht gut... Hast du etwas über die Galeone herausgefunden?";
			link.l1 = "Nein, das habe ich nicht.";
			link.l1.go = "florian_failspy_2";
		break;
		
		case "florian_failspy_2":
			dialog.text = "Verdammt. Ich brauche wirklich einige Informationen darüber. Aber dieser Preis ist zu fett, um aufzugeben! Wie auch immer, ich werde versuchen, einen weiteren Späher dorthin zu schicken... Kapitän, ich bitte Sie, mich vorerst nicht zu verlassen. Ich könnte Ihre Hilfe benötigen. Werden Sie warten, bis ein weiterer Tag vergeht, während ich Informationen über die Alacantara ausspioniere?";
			link.l1 = "Natürlich werde ich warten! Ich möchte diesen Misserfolg wiedergutmachen.";
			link.l1.go = "florian_9";
			link.l2 = "Ich glaube nicht. Anscheinend bin ich zu schlecht in diesen Spielen. Ich gehe heimwärts.";
			link.l2.go = "florian_failspy_3";
		break;
		
		case "florian_failspy_3":
			dialog.text = "Nun, das ist Ihre Wahl. Alles Gute, Kapitän.";
			link.l1 = "Auf Wiedersehen, Monsieur Shoke.";
			link.l1.go = "florian_failspy_4";
		break;
		
		case "florian_failspy_4":
			DialogExit();
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			sld = characterFromId("Lecrua");
			sld.lifeday = 0;
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		
		case "florian_failspy_5":
			pchar.quest.trial_spy_over.over = "yes"; //снять прерывание
			dialog.text = "Wie laufen die Dinge, Kapitän? Was konnten Sie herausfinden?";
			link.l1 = "Es läuft schlecht, Herr Shoke. Ich bin kein guter Spion, sie haben mich sehr schnell entdeckt. Das Einzige, was ich herausfinden konnte, war, dass Ihr Mann, Sylvan Laforet, verhaftet wurde und irgendwo festgehalten wird.";
			link.l1.go = "florian_failspy_1";
		break;
		
		case "florian_9":
			dialog.text = "Dann machen Sie sich auf den Weg zu Ihrem Schiff, Kapitän. Morgen um die gleiche Zeit, oder ein wenig später, müssen Sie mich besuchen. Vielleicht habe ich bis dahin etwas herausgefunden. Betreten Sie nicht das Ufer, warten Sie auf mich auf Ihrem Schiff!";
			link.l1 = "In Ordnung. Werde ich machen.";
			link.l1.go = "florian_10";
		break;
		
		case "florian_10":
			dialog.text = "Und Kapitän, nehmen Sie diesen Beutel. Ihre Bemühungen waren schließlich nicht völlig umsonst. Zumindest wissen wir jetzt, was dem armen alten Sylvan passiert ist...";
			link.l1 = "...";
			link.l1.go = "florian_11";
		break;
		
		case "florian_11":
			DialogExit();
			Island_SetReloadEnableGlobal("Portobello", false);//закрыть остров	
			npchar.DeckDialogNode = "florian_deck_wait";
			NextDiag.CurrentNode = "florian_deck_wait";
			pchar.questTemp.Trial = "spy_wait";
			pchar.quest.Trial_spyfail_wait.win_condition.l1 = "Timer";
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.hour  = sti(GetTime()+rand(12));
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Trial_spyfail_wait.function = "Trial_Spyfail_NextStage";
			TakeNItems(pchar, "purse2", 1);
			Log_Info("You've received a purse of doubloons");
		break;
		
		case "florian_deck_wait":
			dialog.text = "Kapitän, ich habe im Moment keine Neuigkeiten. Wir warten immer noch...";
			link.l1 = "In Ordnung...";
			link.l1.go = "exit";
			NextDiag.TempNode = "florian_deck_wait";
		break;
		
		case "florian_12":
			pchar.quest.trial_spy_over.over = "yes"; //снять прерывание
			dialog.text = "Wie läuft es, Kapitän? Was konnten Sie herausfinden?";
			link.l1 = "Es ist getan. Ihr Mann, Sylvan Laforet, wurde verhaftet und sitzt im Gefängnis. Für ihn ist es vorbei.";
			link.l1.go = "florian_13";
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("PortoBello_Town", "reload", "gate_back");
			QuestPointerDelLoc("PortoBello_ExitTown", "reload", "reload1_back");
			QuestPointerDelLoc("PortoBello_Jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("PortoBello_Jungle_02", "reload", "reload3_back");
			QuestPointerDelLoc("shore47", "reload", "boat");
		break;
		
		case "florian_13":
			dialog.text = "Verdammt noch mal! Das ist furchtbar... Hast du etwas über die Galeone herausgefunden?";
			link.l1 = "Ja. Sie wird seit einer Weile auf die Abfahrt vorbereitet, aber der Gouverneur von Portobello beabsichtigt, sie am Dock festzuhalten. Im Moment wartet er auf eine Barkentine namens 'Puebla', die aus Cartagena mit einer Ladung Schießpulver für die 'Alcantara' ankommt. Laut einem Matrosen vom Galeon haben sie nicht genug davon und der Gouverneur fürchtet Piraten.";
			link.l1.go = "florian_14";
		break;
		
		case "florian_14":
			dialog.text = "Wie interessant!";
			link.l1 = "Aber wenn Puebla nicht innerhalb von drei Tagen ankommt, dann wird die Alacantara aufhören zu warten und in See stechen.";
			link.l1.go = "florian_15";
		break;
		
		case "florian_15":
			dialog.text = "Ausgezeichnete Arbeit, Kapitän "+GetFullName(pchar)+"! Ich bin sehr erfreut! Hier, nimm deine Belohnung. Du hast sie dir wirklich verdient!";
			link.l1 = "Danke! Haben Sie noch weitere Aufgaben für mich?";
			link.l1.go = "florian_16";
		break;
		
		case "florian_16":
			TakeNItems(pchar, "gold_dublon", 250);
			Log_Info("You've received 250 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Du liest meine Gedanken, "+GetFullName(pchar)+"! Ja, verdammt! Da Alacantara wenig Schießpulver hat, kann ich sie aufs offene Meer segeln lassen und sie dann zu einem langwierigen Seekampf zwingen, bei dem ihr Pulver vor unserem ausgeht, haha!\nDu solltest dafür sorgen, dass die Versorgungsbark Puebla niemals Portobello erreicht. Ich kann nicht nah an der Küste segeln, Patrouillen würden meine Fregatte leicht bemerken und mich vertreiben, bevor ich Alacantara abfangen kann\nDu kannst dich alleine um Puebla kümmern. Finde sie und werde sie los. Versenke sie oder nimm sie als Preis, es ist mir egal. Verhindere einfach, dass sie hierher kommt!\nWenn du Erfolg hast, geh nach Guadeloupe und sieh dir Gerard LeCroix an, ich glaube, du kennst ihn schon, oder? Er wird dir die Münze zahlen, die du verdienst.";
			link.l1 = "Abgemacht! Ich mache mich auf den Weg, um die Puebla abzuschneiden!";
			link.l1.go = "florian_19";
			link.l2 = "Warten Sie ein wenig, Monsieur Choquet. Die Tatsache ist, dass ich immer noch ... Sagen wir einfach, nicht besonders an Seeschlachten gewöhnt bin. Und Sie sind der Kapitän einer Fregatte, Sie haben offensichtlich mehr als eine Seeschlacht hinter sich. Wenn es Ihnen nicht schwer fällt, könnten Sie... Wie soll ich es sagen...";
			link.l2.go = "florian_guide_01";
		break;
		
		case "florian_17":
			dialog.text = "Froh, dass Sie hier sind, Kapitän. Ich habe gerade Informationen von meinem Spion erhalten und habe eine wichtige Mission für Sie.";
			link.l1 = "Ich bin ganz Ohr.";
			link.l1.go = "florian_18";
		break;
		
		case "florian_18":
			dialog.text = "Die Alacantara ist bereit in See zu stechen, aber der Kapitän des Galeons wartet auf die Barkentine 'Puebla', die aus Cartagena mit Munition beladen ankommen soll. Anscheinend hat die Alacantara nicht genug Schießpulver, also sind die Spanier noch nicht bereit in See zu stechen. Aber die Geduld des Kapitäns hat ihre Grenzen und wenn die Puebla in drei Tagen nicht kommt, dann wird das Galeon Portobello ohne sie verlassen.\nDie Alacantara hat wenig Schießpulver, ich kann sie aufs offene Meer hinausfahren lassen und sie dann zu einem langwierigen Seekampf zwingen, in dem ihr Pulver vor unserem ausgeht. Dein Ziel ist es, die Puebla abzufangen und sie zu zerstören. Versenke sie oder nimm sie als Preis, das ist mir egal. Verhindere nur, dass diese Versorgungsbark hierher kommt!\nWenn du Erfolg hast, dann geh nach Guadeloupe und sieh Gerard LeCroix, ich glaube, du kennst ihn bereits, oder? Er wird dir die Münze zahlen, die du verdienst.";
			link.l1 = "Abgemacht! Ich mache mich auf den Weg, um die Puebla abzuschneiden!";
			link.l1.go = "florian_19";
			link.l2 = "Warten Sie ein wenig, Monsieur Choquet. Die Tatsache ist, dass ich immer noch ... Sagen wir mal, nicht besonders an Seeschlachten gewöhnt bin. Und Sie sind der Kapitän einer Fregatte, Sie haben offensichtlich mehr als eine Seeschlacht hinter sich. Wenn es Ihnen nicht schwer fällt, könnten Sie... Wie soll ich es ausdrücken...";
			link.l2.go = "florian_guide_01";
		break;
		
		case "florian_19":
			DialogExit();
			Island_SetReloadEnableGlobal("Portobello", true); // открыть остров
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			Trial_CreatePueblaBarqueInWorld();
			pchar.questTemp.Trial = "puebla";
			AddQuestRecord("Trial", "19");
		break;
		// belamour legendary edition дополнительное обучение -->
		case "florian_guide_01":
			dialog.text = "Sie möchten, dass ich Ihnen eine Lektion in der Taktik des Seekampfs erteile? Mit Vergnügen, Kapitän! Vor allem, da es in meinem eigenen Interesse ist: Ich möchte sicher sein, dass Sie die 'Puebla' erfolgreich abfangen.";
			link.l1 = "Nein, das habe ich nicht gemeint. Schon gut, vergiss es: Ich bin sicher, dass ich keine Probleme haben werde, eine Barkentine zu kapern.";
			link.l1.go = "florian_19";
			link.l2 = "Ja, genau das habe ich gemeint. Ich bin sicher, dass neues Wissen mir nicht schaden wird.";
			link.l2.go = "florian_guide_02";
		break;
		
		case "florian_guide_02":
			dialog.text = "Also das Erste, was du dir merken musst, ist, dass die Hälfte der Schlacht gewonnen oder verloren ist, bevor sie überhaupt beginnt. Vieles hängt davon ab, wie bereit du und dein Schiff dafür sind.";
			link.l1 = "...";
			link.l1.go = "florian_guide_03";
		break;
		
		case "florian_guide_03":
			dialog.text = "Zuerst, stellen Sie sicher, dass Ihr Schiff repariert ist. Wenn Sie Löcher im Rumpf haben, dann wird es für den Feind nicht schwer sein, Sie auf den Grund zu schicken. Und wenn Sie Lumpen anstelle von Segeln hängen haben, dann schränkt dies Ihre Mobilität sehr erheblich ein. Der Feind kann leicht von Ihnen wegkommen, wenn das Kräfteverhältnis nicht zu seinen Gunsten ist oder schlimmer, Sie einholen und Ihnen eine unvorteilhafte Schlacht aufzwingen - oder sogar sofort an Bord gehen. Außerdem werden Sie mit zerrissenen Segeln Schwierigkeiten haben, die Wetterseite zu gewinnen, das heißt, Sie werden gegen den Wind Ihres Gegners kämpfen müssen, wo Sie sein wollen.";
			link.l1 = "Wetterseite, verstanden. Noch etwas?";
			link.l1.go = "florian_guide_04";
		break;
		
		case "florian_guide_04":
			dialog.text = "Stelle sicher, dass du genügend Männer hast. Selbst das mächtigste Schiff mit 42-Pfund-Kanonen wird nutzlos, wenn du einen Kanonier hast, der drei Kanonen nachladen muss und einfach niemand da ist, um die Segel zu kontrollieren. Im Allgemeinen würde ich ein solches Schiff einfach sofort entern und es in Besitz nehmen.";
			link.l1 = "Genug Männer, verstanden.";
			link.l1.go = "florian_guide_05";
		break;
		
		case "florian_guide_05":
			dialog.text = "Auch, achten Sie auf Ihre Kanonen: sie werden sich mit der Zeit abnutzen und explodieren. Mit der Zeit verschlechtert sich der Zustand der Fässer, und wenn Ihre Kanonen mitten in einer Schlacht zu explodieren beginnen, kann es sehr schlecht für Sie enden. Ich hatte überhaupt kein Glück: Die Charge von Kanonen, mit denen ich segelte, hatte mehrere Gussfehler. Hätten Sie nicht rechtzeitig einen Ersatz gebracht, hätte ich die Operation einfach aufgegeben, da die Militante der Alcantara an Feuerkraft weit unterlegen wäre. Werkzeuge müssen rechtzeitig gewechselt werden.";
			link.l1 = "Jetzt verstehe ich, warum es so wichtig war!";
			link.l1.go = "florian_guide_06";
		break;
		
		case "florian_guide_06":
			dialog.text = "Neben Kanonen sollte man auch immer ein Auge auf die Menge der Munition haben. Alcantara wird mir wegen diesem Fall. Wenn sie niedrige Bestände an Schießpulver hat, wird sie nicht in der Lage sein, eine lange Schlacht zu führen - sie muss sofort in den Nahkampf gehen. Und ich werde darauf spielen: meine Fregatte ist schneller, eine schwere Galeone wird nicht in der Lage sein, von ihr wegzukommen. Aber ich muss auch nicht nah kommen: Ich werde ein Artillerieduell auf lange Entfernung erzwingen und dann, wenn das Schießpulver auf der Alcantara ausgeht, werde ich schließen, sie mit Traubenhagel durchsieben und sie entern.";
			link.l1 = "Verzweifelte Situation...";
			link.l1.go = "florian_guide_07";
		break;
		
		case "florian_guide_07":
			dialog.text = "Genau. Behalte dein Schießpulver und deine Munition im Auge. Wenn dir die Vollkugeln ausgehen - und du wirst höchstwahrscheinlich kein feindliches Schiff versenken können. Wenn dir die Traubenschüsse ausgehen, kannst du bei Überzahl keine Enterung erhoffen. Wenn du keine Kettenkugeln oder Knöpfe hast, wirst du den Feind nicht einholen können oder vor ihm fliehen, wenn er schneller ist. Alle Munitionsarten sind wichtig.";
			link.l1 = "Aufschlussreich, danke.";
			link.l1.go = "florian_guide_08";
		break;
		
		case "florian_guide_08":
			dialog.text = "Und schließlich, abhängig von der Art und Größe Ihres Schiffes und des feindlichen Schiffes, verwenden Sie die angemessenen Taktiken. Auf See gibt es einen Kompromiss zwischen Feuerkraft und Geschwindigkeit. Auf einem großen und langsamen Schiff hat es keinen Sinn, eine Brigg oder eine Korvette zu verfolgen, um an Bord zu gehen - Sie werden sie immer noch nicht einholen, ohne sie zuerst mit Kettenkugeln zu erweichen. In solchen Fällen ist es klüger, sie aus der Ferne in Stücke zu blasen und durch das Wrack zu picken. Wenn Sie immer noch ein solches Schiff entern müssen, ist es vorzuziehen, ein schnelles und wendiges Schiff zu verwenden.";
			link.l1 = "...";
			link.l1.go = "florian_guide_09";
		break;
		
		case "florian_guide_09":
			dialog.text = "Gleichzeitig sollten Sie sich nicht mit einer Linie Schiff mit einer Brigantine anlegen. Eine Breitseite von einem solchen Monster zerschmettert kleinere Schiffe in Splitter. Nutzen Sie Ihren Geschwindigkeits- und Manövrierfähigkeitsvorteil, reißen Sie ihre Masten und Takelage nieder, dann nähern Sie sich und fegen ihre Decks mit Traubenkugeln, wenn Sie noch an Bord gehen müssen. Wenn Sie sie versenken müssen... es wird keine leichte Aufgabe sein, aber es ist möglich. Sie können an Bord gehen und dann ihr Pulvermagazin abfeuern, aber es ist nie beschämend zu fliehen. Ein guter Kapitän wird sein Schiff und seine Besatzung vor sicherem Tod retten, anstatt übermäßigen Heldenmut. Denken Sie daran, Diskretion und Klugheit sind oft der bessere Teil des Mutes.";
			link.l1 = "Vielen Dank, Monsieur Choquet!";
			link.l1.go = "florian_guide_10";
		break;
		
		case "florian_guide_10":
			AddCharacterSkillDontClearExp(pchar, SKILL_CANNONS, 1);
			AddCharacterSkillDontClearExp(pchar, SKILL_ACCURACY, 1);
			//Log_info(XI_ConvertString("Experience Bonus")+": +1 "+XI_ConvertString(SKILL_CANNONS));
			notification(XI_ConvertString("Experience Bonus")+": +1 ", SKILL_CANNONS);
			//Log_info(XI_ConvertString("Experience Bonus")+": +1 "+XI_ConvertString(SKILL_ACCURACY));
			notification(XI_ConvertString("Experience Bonus")+": +1 ",SKILL_ACCURACY);
			dialog.text = "Gerne helfe ich Kapitän. Ich hoffe, dieses Wissen wird Ihnen in Zukunft helfen.";
			link.l1 = "Ich bin sicher, es wird helfen. Wir machen uns auf, die 'Puebla' abzufangen!";
			link.l1.go = "florian_19";
		break;
		// <-- legendary edition дополнительное обучение

		// испанский офицер в таверне
		case "tavern_officer":
			dialog.text = "Das ist ein ungewöhnlicher Akzent, den Sie da haben, senor. Oder sollte ich 'monsieur' sagen? Möchten Sie Jaime Silicio sehen? Vielleicht könnt ihr euch eine Zelle teilen. Nehmt ihn, Jungs!";
			link.l1 = "Nun, wenn dir mein Akzent nicht gefällt, kann ich dir vielleicht das französische Fechten vorstellen!";
			link.l1.go = "tavern_officer_1";
		break;
		
		case "tavern_officer_1":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorTypeNoGroup(npchar);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
            LAi_group_SetCheck("EnemyFight", "Trial_AfterTavernFight");
			AddDialogExitQuest("MainHeroFightModeOn");
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

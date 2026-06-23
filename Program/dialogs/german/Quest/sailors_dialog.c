// реплики солдат на палубе при разговоре в море
// форт-стража и комендант форта
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
        case "exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
        case "First time":
			dialog.text = "Sprechen Sie mit unserem Kapitän. Ich habe Ihnen nichts zu erzählen.";
			Link.l1 = "Gut.";
			Link.l1.go = "exit";
			
			NextDiag.TempNode = "first time";
		break;
		//  на палубе -->
		case "On_Deck":
			dialog.text = "Sprechen Sie mit unserem Kapitän. Ich habe Ihnen nichts zu erzählen.";
			Link.l1 = "Gut.";
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Deck";
/*			
			// Первый церковный генератор
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapWaitOnTavern"))
			{
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithSailors"))
				{
					dialog.text = "Herr, suchen Sie jemanden?";
					Link.l1 = "Ja, Kumpel. Kann ich den Kapitän sehen?";
					Link.l1.go = "ChurchQuest1_Node1";
				}
				else
				{
					dialog.text = "Wenn Sie unseren Kapitän suchen. Er ist kürzlich gelandet.";
					Link.l1 = "Gut";
					Link.l1.go = "exit";
				}
				break;
			}
*/			
			//--> eddy. квест мэра, закрываем выход с палубы и ноду даем нужную
			if (CheckAttribute(pchar, "GenQuest.DestroyPirate") && pchar.GenQuest.CaptainId == "MQPirate")
			{
	    		dialog.text = RandPhraseSimple("Oh, du bist alleine hier. Ha! In diesem Fall geh zu unserem Kapitän. Erzähl ihm von deinen traurigen Taten...","Wow, es scheint, du bist verrückt, Freund. Geh zu unserem Kapitän und er wird mit dir reden.");
				Link.l1 = "Schade...";
				Link.l1.go = "exit";
			}
			//<-- eddy. квест мэра, закрываем выход с палубы
		break;
/*		
		case "ChurchQuest1_Node1":
			dialog.text = "Du solltest ihn besser im Hafen suchen.";
			Link.l1 = "Danke dir, mein Freund.";
			Link.l1.go = "exit";
			NextDiag.TempNode = "On_Deck";
			PChar.GenQuest.ChurchQuest_1.CapWaitOnTavern = true; 
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithSailors"); // Не спрашиваем моряков
		break;
*/		
        //  на палубе <--
				
		// ugeen --> разговор с боцманом по генератору "Повод для спешки"
		case "On_MyShip_Deck":
			dialog.text = "Nun, das war ein ernstes Durcheinander, Kapitän! Wir waren in der Taverne, tranken wie wir es normalerweise tun, als wir Schreie hörten. Wir rannten aus der Taverne und sahen, dass sie versuchten, dich festzunehmen. Zum Teufel mit ihnen! Also beschlossen wir, diesen unfreundlichen Hafen zu verlassen.";
			link.l1 = "Ja, sicherlich haben einige Leute eine etwas seltsame Vorstellung von Gerechtigkeit.";
			link.l1.go = "On_MyShip_Deck_1";
		break;
		
		case "On_MyShip_Deck_1":
		    if(pchar.questTemp.ReasonToFast == "speakSuccess_chain_A") 
			{
				// карты не было
				dialog.text = "Kapitän! Mach dir keine Sorgen! Es war klar, dass es keine Möglichkeit gab, in Frieden zu fliehen, also haben wir beschlossen, den örtlichen Bankier zu besuchen, um seine Truhen zu überprüfen. Hier ist dein Anteil - "+int(pchar.questTemp.ReasonToFast.p9)+" Pesos...";
			}
			if(pchar.questTemp.ReasonToFast == "speakSuccess_chain_B")
			{
				// карту отобрали
				GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
				dialog.text = "Kapitän! Machen Sie sich keine Sorgen! Es war klar, dass es keinen Weg gab, in Frieden zu fliehen, also haben wir beschlossen, den örtlichen Bankier zu besuchen und seine Truhen zu überprüfen. Es gab auch ein feines Schwert in der Pfandleihe. Hier ist Ihr Anteil - "+int(pchar.questTemp.ReasonToFast.p9)+" Pesos und ein Schwert...";
			}		
			link.l1 = "Gut gemacht Jungs! Gut gemacht! Ich bin stolz auf euch.";
			link.l1.go = "On_MyShip_Deck_End";
			AddMoneyToCharacter(pchar, int(pchar.questTemp.ReasonToFast.p9));
			pchar.Ship.Crew.Morale = MORALE_MAX;
			chrDisableReloadToLocation = false; // Откроем выход
			AddQuestRecord("ReasonToFast", "17");		
			AddQuestUserData("ReasonToFast", "sSex", GetSexPhrase("",""));		
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar,"TownEscape");
			DeleteAttribute(pchar,"questTemp.ReasonToFast");
			QuestOpenSeaExit();
		break;
		
		case "On_MyShip_Deck_End":
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		
		// разговор с боцманом по генератору 'Операция Галеон'
		case "CapComission_OnShipDeck":
			dialog.text = "Kapitän, Ihr Freund ist entkommen.";
			link.l1 = "Welcher Freund?";
			link.l1.go = "CapComission_OnShipDeck1";
		break;
		
		case "CapComission_OnShipDeck1":
			dialog.text = "Nun, der Freund, den du aus den Verliesen geholt hast.";
			link.l1 = "Wie zum Teufel hast du es geschafft, ihn zu verlieren?!";
			link.l1.go = "CapComission_OnShipDeck2";
		break;
		
		case "CapComission_OnShipDeck2":
			dialog.text = "Es war nicht unsere Schuld, Käpt'n. Er sprang durch das Latrin ins Meer... Wir versuchten, auf ihn zu schießen, aber es war zu dunkel dort...";
			link.l1 = "Verdammt! Ihr seid wirklich außer Kontrolle geraten! Ihr alle werdet an Land geschickt und zur Arbeit mit dem Zuckerrohr gezwungen! Einen so wertvollen Großkopf zu verlieren! Unglaublich!";
			link.l1.go = "CapComission_OnShipDeck3";
		break;
		
		case "CapComission_OnShipDeck3":
			chrDisableReloadToLocation = false; // Откроем выход
			AddQuestRecord("CaptainComission2", "25");	
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));			
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");	
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputationABS(pchar, "authority", 1);
			DeleteAttribute(pchar,"TownEscape");
			DeleteAttribute(pchar,"GenQuest.CaptainComission.canSpeakBoatswain");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			QuestOpenSeaExit();		
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		// <-- ugeen
		
		// разговор с боцманом по ситуациям в трюме
		case "Hold_GenQuest_OnShipDeck":
			dialog.text = "Kapitän, vergeben Sie uns, es war unser Fehler - der Gefangene ist entkommen.";
			link.l1 = "Welcher Gefangene? Wer ist entkommen?";
			link.l1.go = "Hold_GenQuest_OnShipDeck1";
		break;
				
		case "Hold_GenQuest_OnShipDeck1":
			dialog.text = "Nun, oh, seinen Namen vergessen, "+pchar.GenQuest.Hold_GenQuest.CapName+", richtig?";
			link.l1 = "Verdammt! Wo hast du hingeschaut?";
			link.l1.go = "Hold_GenQuest_OnShipDeck2";
		break;
		
		case "Hold_GenQuest_OnShipDeck2":
			dialog.text = "Er kam aus dem Laderaum und sprang von der Bordwand. Wir haben ihn nicht erschossen, um keinen Lärm zu machen, und während wir ein Beiboot vorbereiteten, wurde er von verdammten Fischern gerettet.";
			link.l1 = "Und warum bezahle ich euch! Peitscht den Wachhauptmann aus und entzieht ihm eine Woche lang den Rum. Achtung! Wir lichten den Anker...";
			link.l1.go = "Hold_GenQuest_OnShipDeck3";
		break;
		
		case "Hold_GenQuest_OnShipDeck3":
			chrDisableReloadToLocation = false; // Откроем выход
			sld = characterFromId(pchar.GenQuest.Hold_GenQuest.CapId);
			ReleasePrisoner(sld);			
			CloseQuestHeader("HoldQuest");	
			DeleteAttribute(pchar, "TownEscape");
			DeleteAttribute(pchar, "GenQuest.Hold_GenQuest.canSpeakSailor");
			DeleteAttribute(pchar, "GenQuest.Hold_GenQuest");
			QuestOpenSeaExit();					
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		
		case "Hold_GenQuest_OnShipDeck4":
			dialog.text = "Grüße, Kapitän. Es gab keine Zwischenfälle während deines...";
			link.l1 = "Gut, gut, ich habe es verstanden.... In unserem Laderaum befindet sich der Gefangene. Sein Name ist "+pchar.GenQuest.Hold_GenQuest.CapName+". Nehmt ein paar Männer und bringt ihn zum Hafen. Er ist jetzt frei.";
			link.l1.go = "Hold_GenQuest_OnShipDeck5";
		break;
		
		case "Hold_GenQuest_OnShipDeck5":
			dialog.text = "Ist er wirklich frei? Wir sollen ihn auf einem Langboot liefern?";
			link.l1 = "Nein, auf einer verdammten Schildkröte... Ich dachte, ich wäre klar genug. Und beeil dich! Wir müssen den Anker lichten, bevor die Ebbe einsetzt.";
			link.l1.go = "Hold_GenQuest_OnShipDeck3";
		break;
		
		// Warship 09.07.09 Базар с нашим матросом на палубе Мэри Селест -->
		case "On_MaryCeleste_Deck":
			Dialog.text = "Kapitän, auf dem Schiff sind überhaupt keine Menschen! Hier stimmt etwas ganz und gar nicht... Tommy sagte, er habe eine Katze im Cockpit gesehen und das war die einzige lebende Seele...";
			Link.l1 = "Idiot, Katzen haben keine Seelen. Sieht so aus, als ob er schon lange nicht mehr in der Kirche war oder überhaupt noch nie dort war. Warst du in der Kapitänskajüte? Ich brauche ein Logbuch.";
			Link.l1.go = "On_MaryCeleste_Deck_1";
		break;
		
		case "On_MaryCeleste_Deck_1":
			Dialog.text = "Nein, sie haben Seelen. Es gab kein Logbuch und kein einziges Navigationsinstrument. Nicht einmal ein einziges Beiboot...";
			Link.l1 = "Sie tun es nicht. Wurde es von einem Sturm müde?";
			Link.l1.go = "On_MaryCeleste_Deck_2";
		break;
		
		case "On_MaryCeleste_Deck_2":
			Dialog.text = "Das tun sie, Käpt'n. Katzen haben Seelen. Käpt'n, das Beiboot wurde abgeschnitten und wir haben ein Schwert auf dem Boden des Cockpits gefunden. Es ist rostig und blutig. Hier, schau mal...";
			Link.l1 = "Hör auf, mir diesen Mist zu geben, wirf ihn weg und hör verdammt noch mal auf, über Katzen zu reden! Lass uns das Schiff überprüfen und gehen... Oh, hier stimmt etwas ganz und gar nicht und das gefällt mir verdammt noch mal nicht...";
			Link.l1.go = "On_MaryCeleste_Last";
			NextDiag.TempNode = "On_MaryCeleste_Deck_SailorLast";
		break;
		
		case "On_MaryCeleste_Last":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetCitizenType(NPChar); // Чтоб по палубе ходил
			
			NPChar = GetRealShip(GetCharacterShipType(CharacterFromID("MaryCelesteCapitan")));
			NPChar.TurnRate = int(PChar.QuestTemp.MaryCeleste.TurnRate); // Вернем манёвренность, для интерфейса
			
			chrDisableReloadToLocation = false; // Откроем выход
			
			LaunchTransferMain(PChar, CharacterFromID("MaryCelesteCapitan"), "MaryCelesteTransfer");
		break;
		
		case "On_MaryCeleste_Deck_SailorLast":
			switch(rand(2))
			{
				case 0:
					Dialog.text = "Kapitän, ich habe ein schlechtes Gefühl bei diesem Ort... Vielleicht ist es an der Zeit für uns zu gehen?";
					Link.l1 = "Ja... Geh zum Beiboot.";
					Link.l1.go = "exit";
				break;
				
				case 1:
					Dialog.text = "Kapitän, ich werde nicht auf diesem seltsamen Schiff bleiben, wenn Sie bereit sind, es zum Hafen zu bringen. Ich würde lieber selbst ins Meer springen.";
					Link.l1 = "Ich bin nicht bereit, das zu tun... Ich bin auch ein bisschen verängstigt...";
					Link.l1.go = "exit";
				break;
				
				case 2:
					Dialog.text = "Vielleicht sollten wir es versenken, Kapitän?";
					Link.l1 = "Lassen wir die Seelen der toten Seeleute, die hier leben, uns in unseren Alpträumen besuchen?";
					Link.l1.go = "On_MaryCeleste_Deck_SailorLast_1";
				break;
			}
			
			NextDiag.TempNode = "On_MaryCeleste_Deck_SailorLast";
		break;
		
		case "On_MaryCeleste_Deck_SailorLast_1":
			Dialog.text = "Guter Gott, nein! Kapitän... warum sagst du das?";
			Link.l1 = "Verblasst nicht, ich habe nur gescherzt... Geht zum Schiffskahn. Und ich glaube, du hast vielleicht doch recht, vielleicht haben Katzen wirklich Seelen...";
			Link.l1.go = "exit";
		break;
		// <-- Базар с нашим матросом на палубе Мэри Селест
		
        //  на палубе <--
        case "On_Fort":
			dialog.text = RandPhraseSimple("Sprich mit dem Boss. Ich habe dir nichts zu sagen.","Ich bin an meinem Posten. Alle Fragen gehen an den Kommandanten der Festung.");
			Link.l1 = "Gut.";
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Fort";
		break;
		
		case "On_Fort_Head":
			dialog.text = RandPhraseSimple("Ich bin wirklich beschäftigt jetzt. Lass mich in Ruhe.","Stör mich nicht bei meiner Arbeit. Es gibt nichts zu besprechen.");
			Link.l1 = "Mitleid...";
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Fort_Head";
		break;
		
		case "Morgan_wait_you":
			Dialog.defAni = "dialog_stay1";
			Dialog.defCam = "1";
			Dialog.defSnd = "dialogs\0\017";
			Dialog.defLinkAni = "dialog_1";
			Dialog.defLinkCam = "1";
			Dialog.defLinkSnd = "dialogs\woman\024";
			Dialog.ani = "dialog_stay2";
			Dialog.cam = "1";
			Dialog.snd = "dialogs\0\009";

			dialog.text = RandPhraseSimple("Morgan wollte dir 'ein oder zwei Dinge' erzählen... Er ist irgendwo hier, auf dem Deck.","Heh, finde Morgan. Schlechte Nachrichten warten auf dich...");
			Link.l1 = "Gut.";
			Link.l1.go = "exit";

			NextDiag.TempNode = "Morgan_wait_you";
		break;
	}
}

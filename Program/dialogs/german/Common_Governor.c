// boal 25/04/04 общий диалог Governor
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Governor\" + NationShortName(int(NPChar.nation)) + "_Governor.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
    
    ref offref, sld;
    int i, cn;
    int qty;
    int iSumm;
    string attrLoc;

    /// выкуп колонии
    ref CaptGovenor, FortColony;
    int f, colony_money;

    int k = 1000;
    if (CheckAttribute(Nations[int(NPChar.nation)], "Fort"))
    {
        k = (300 - int(Nations[int(NPChar.nation)].Fort)*10);
    }
	bool ok;
	
	attrLoc = Dialog.CurrentNode;
	if (findsubstr(attrLoc, "CityGive_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.quest.CityIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "ColonyGive";
 	}
 	
	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "First time":
            NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Du wagst es, dein Gesicht im Büro des Generalgouverneurs zu zeigen?! Du bist wirklich verrückt...","Wie konnten diese Faulenzer einen Feind in meine Residenz eindringen lassen? Das geht über meinen Verstand hinaus...","Sicherlich, meine Wachen sind keinen Groschen wert, wenn irgendein Landstreicher in meiner Residenz herumläuft..."),LinkRandPhrase("Was brauchst du, "+GetSexPhrase("Lauerer","Stinktier")+"?! Meine Soldaten sind bereits auf deiner Spur, "+GetSexPhrase("schmutziger Pirat","Stinker")+"!",""+GetSexPhrase("Dreckig","Dreckig")+" Mörder, verlasse sofort meine Residenz! Wachen!","Ich habe keine Angst vor dir, "+GetSexPhrase("Schurke","Schurke")+"! Bald wirst du in unserem Fort gehängt, du wirst nicht weit kommen..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Soldaten sind keinen Dreck wert...","Du wirst mich nie kriegen."),RandPhraseSimple("Halt die Klappe, Kumpel, oder ich reiß dir diese verdammte Zunge raus!","Ich sag's dir, Kumpel: Sitze still, oder ich schneide deinen Kopf ab und werfe ihn durch diese Tür zu deinen Wachhunden..."));
				link.l1.go = "fight";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Ich habe gehört, dass Sie sehr hartnäckig um eine Audienz gebeten haben. Mein Name ist "+GetFullName(npchar)+". Ich bin der Generalgouverneur der Kolonien von "+NationNameGenitive(int(NPChar.nation))+", Stellvertreter der Krone von "+NationKingsName(npchar)+" in diesen Gewässern. Nun, seien Sie bitte so freundlich und sagen Sie mir, was der Zweck Ihres Besuches ist, "+GetAddress_Form(NPChar)+".";
				link.l1 = "Mein Name ist "+GetFullName(pchar)+".";
				link.l1.go = "node_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = RandPhraseSimple("Oh, das bist du wieder? Nun, was willst du vom Gouverneur?"+NationNameGenitive(int(NPChar.nation))+" dieses Mal?","Und schon wieder lenkst du mich von wichtigen Staatsangelegenheiten ab? Was willst du, "+GetAddress_Form(NPChar)+"?");
				link.l1 = "Ich möchte mit Ihnen über die Arbeit im Namen der Krone sprechen "+NationNameGenitive(int(NPChar.nation));
				link.l1.go = "work";
				link.l2 = "Ich muss mit dir über eine wichtige Angelegenheit sprechen.";
				link.l2.go = "quests"; // файл нации
				//Jason --> Регата
				if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
				{
					link.l3 = "Ich bin auf Einladung gekommen, um an der Regatta teilzunehmen. Hier ist meine Einladung.";
					link.l3.go = "Regata";
				}
				//<-- Регата
				link.l10 = "Es tut mir leid, aber ich habe einige Geschäfte zu erledigen.";
				link.l10.go = "exit";
			}
		break;
		
		case "node_1":
			dialog.text = "Also, was war der Grund für dich, hierher zu kommen und mich von wichtigen Staatsangelegenheiten abzulenken?";
			link.l1 = "Ich wollte mit Ihnen über die Arbeit im Namen der Krone sprechen "+NationNameGenitive(int(NPChar.nation));
			link.l1.go = "work";
			link.l2 = "Ich wollte mit dir über eine wichtige Angelegenheit sprechen.";
			link.l2.go = "quests";
			//Jason --> Регата
			if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
			{
				link.l3 = "Ich bin hier, um an der Regatta teilzunehmen. Hier ist meine Einladung.";
				link.l3.go = "Regata";
			}
			//<-- Регата
			link.l10 = "Es ist nur ein Höflichkeitsbesuch, nichts weiter, "+GetAddress_FormToNPC(NPChar);
			link.l10.go = "node_2";
		break;

		case "node_2":
			dialog.text = "In diesem Fall würde ich Sie bitten, mein Büro zu verlassen und mich nicht weiter von meiner Arbeit abzulenken.";
			link.l1 = "Ja, ja, natürlich. Entschuldigung für die Störung.";
			link.l1.go = "exit";
		break;
		
		case "work":
            dialog.text = "Wenn Sie Arbeit suchen, sprechen Sie mit den Gouverneuren der Kolonien. Sie brauchen oft kluge und mutige Kapitäne.";
			link.l1 = "Ich werde das im Kopf behalten. Danke.";
			link.l1.go = "exit";
		break;
		
		//--> Jason регата
		case "Regata":
			dialog.text = "Oh, großartig, froh dich zu sehen, Kapitän! Du bist gerade rechtzeitig angekommen - die Regatta soll in ein paar Tagen beginnen. Hast du die Regeln der Regatta in dem Brief gelesen, der dir sicherlich vom Boten übergeben wurde?";
			link.l1 = "Ja, Sir, das habe ich.";
			link.l1.go = "Regata_1";
			RemoveItems(PChar, "letter_open", 1);//уберем письмо
			TakeNationLicence(HOLLAND);//уберем лицензию
			DeleteAttribute(pchar, "questTemp.Regata.ToPortRoyal"); // patch-5
		break;
		
		case "Regata_1":
			dialog.text = "Und haben Sie 50000 Pesos vorbereitet - Ihre Eintrittsgebühr, die zum Preisgeld beitragen wird?";
			if (int(Pchar.money) >= 50000)
			{
				link.l1 = "Ja, natürlich. Bitte akzeptieren Sie meine Gebühr.";
				link.l1.go = "Regata_2";
			}
			link.l2 = "Ich bin momentan etwas knapp bei Kasse. Aber ich werde es definitiv so schnell wie möglich bringen.";
			link.l2.go = "Regata_nomoney";
		break;
		
		case "Regata_2":
			dialog.text = "Sehr gut. Wenn du gewinnst - dein Geld wird dir fünffach zurückgegeben. Nun, du solltest wissen, wie man die Regeln der Regatta nicht bricht.\nBespreche die Details mit Henry Stevenson, er muss im Wohnzimmer sein. Triff dich mit ihm, er wird alles erklären.";
			link.l1 = "In Ordnung. Ich werde tun, was du sagst.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -50000);
			pchar.quest.Regata_Guber.win_condition.l1 = "location";
			pchar.quest.Regata_Guber.win_condition.l1.location = "Portroyal_Roomtownhall";
			pchar.quest.Regata_Guber.function = "PrepareToRegataInPortroyal";
			pchar.questTemp.Regata.Begin = "true";
			NextDiag.TempNode = "First time";
		break;
		
		case "Regata_nomoney":
			dialog.text = "Gut, aber bitte zögern Sie nicht zu lange, Kapitän. Die Regatta wird bald beginnen.";
			link.l1 = "Ich verstehe. Ich werde versuchen, dir das Geld zu bringen, bevor die Regatta beginnt.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_1";
			pchar.questTemp.Regata.nomoney = "true";
		break;
		
		//регата-финал
		case "Regata_Final":
			dialog.text = "Und hier haben wir den Sieger der Regatta! Hallo, Kapitän "+GetFullName(pchar)+"! Lassen Sie mich Ihnen zu diesem wohlverdienten Erfolg gratulieren! Die Gewinner der Regatta sind immer beliebt in den englischen Kolonien, verdientermaßen beliebt.";
			link.l1 = "Danke, Herr!";
			link.l1.go = "Regata_complete";
		break;
		
		case "Regata_complete":
			dialog.text = "Nun, lasst uns zum angenehmsten Teil für Sie springen - zur Belohnungszeremonie. Der erste Geldpreis beträgt 250000 Pesos. Hier, bitte!";
			link.l1 = "Danke!";
			link.l1.go = "Regata_complete_1";
		break;
		
		case "Regata_complete_1":
			AddMoneyToCharacter(pchar, 250000);
			int iGift;
			string sItem1, sItem2, sItem3, sAdd;
			
			iGift = 3;
			switch (iGift)
			{
				case 0:
					sItem1 = "blade_10";//корд
					sItem2 = "cirass6";
					sItem3 = "bussol";
					sAdd = "cord, duelist's vest and boussole";
				break;
				
				case 1:
					sItem1 = "blade_15";//маринера
					sItem2 = "cirass2";//рейтарский панцирь
					sItem3 = "bussol";
					sAdd = "marinera, reiter's armour and boussole";
				break;
				
				case 2:
					sItem1 = "blade_17";//бретта
					sItem2 = "cirass7";//карацена
					sItem3 = "bussol";
					sAdd = "bretta, karacena and boussole";
				break;
				
				case 3://
					sItem1 = "blade_20";//мадонна
					sItem2 = "cirass2";//офицерская кираса
					sItem3 = "bussol";
					sAdd = "'Madonna', officer's cuirass and boussole";
				break;
			}
			GiveItem2Character(pchar, sItem1);
			GiveItem2Character(pchar, sItem2);
			GiveItem2Character(pchar, sItem3);
			dialog.text = "Außerdem hast du Anspruch auf eine Reihe wertvoller Preise: "+sAdd+". Jetzt gehört alles dir.";
			link.l1 = "Ich bin sehr erfreut, Herr! Wirklich, ich hätte es nicht erwartet.";
			link.l1.go = "Regata_complete_2";
		break;
		
		case "Regata_complete_2":
			dialog.text = "Im Namen aller englischen Kolonien freue ich mich, Ihnen für Ihre Teilnahme an der Regatta zu danken und gratuliere Ihnen erneut zu Ihrem Sieg! Wenn Sie eine Wette abgeschlossen haben, ist jetzt der perfekte Zeitpunkt, um Sir Henry Stevenson aufzusuchen und Ihre Gewinne abzuholen, falls Sie dies noch nicht getan haben. Viel Glück, Kapitän!";
			link.l1 = "Vielen Dank für Ihre freundlichen Worte, Herr! Erlauben Sie mir im Gegenzug, Ihnen für die Gelegenheit zu danken, an einem so großartigen Ereignis teilnehmen zu dürfen. Und nun, bitte erlauben Sie mir, Abschied zu nehmen und zu gehen.";
			link.l1.go = "Regata_complete_3";
		break;
		
		case "Regata_complete_3":
			DialogExit();
			NextDiag.CurrentNode = "First time";
		break;
		//<-- регата
	}
}

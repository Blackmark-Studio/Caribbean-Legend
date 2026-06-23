// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Welche Fragen haben Sie?","Wie kann ich Ihnen helfen, "+GetAddress_Form(NPChar)+"?"),"Du hast versucht, mir vor kurzem eine Frage zu stellen, "+GetAddress_Form(NPChar)+"...","Über den ganzen Tag hinweg ist dies das dritte Mal, dass du von irgendeiner Frage redest...","Noch mehr Fragen, nehme ich an?","Block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ich habe es mir anders überlegt...","Ich habe im Moment nichts zu besprechen."),"Umph, wo ist mein Gedächtnis hin...","Ja, es ist wirklich das dritte Mal...","Nein, welche Fragen?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";						
			//Jason, Бремя гасконца
			if (CheckAttribute(PChar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "hire" && !CheckAttribute(npchar, "quest.storehelper"))
			{
				link.l1 = "Hör zu, "+npchar.name+", ich bin zu Ihnen wegen einer ungewöhnlichen Angelegenheit gekommen. Ich muss einen Mann finden, der ein ruhiges, friedliches Leben in der Bucht als Händlerassistent in einem Laden in Saint-Pierre schätzen würde. Das Gehalt ist gut und er hätte ein Dach über dem Kopf. Könnten Sie mir jemanden vorschlagen, an den ich mich wenden könnte?";
				link.l1.go = "storehelper";
			}
			if (CheckAttribute(PChar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "seabattle" && !CheckAttribute(npchar, "quest.seabattle") && pchar.location.from_sea == "LeFransua_town")
			{
				link.l1 = "Ich bin hier wegen der Fässer Wein, die ihr gleich auf mein Schiff verladet, um sie nach Guadeloupe zu liefern...";
				link.l1.go = "seabattle";
			}
			//Бремя гасконца
			//Jason, Португалец
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "PortugalLeFransua" && !CheckAttribute(npchar, "quest.portugal") && Pchar.location.from_sea == "LeFransua_town")
			{
				link.l1 = "Weißt du, "+npchar.name+", ich suche einen Freund von mir. Er sollte hier ankommen und er fühlte sich unwohl. Vielleicht haben ihm seine Freunde geholfen...";
				link.l1.go = "Portugal";
			}
			//Португалец
		break;
		
		case "storehelper":
			dialog.text = "Hm .. Wir haben hier mehrere Leute, die vom Seemannsleben zum Leben eines Landratten wechseln möchten. Ich könnte Ihnen helfen, aber ich sage Ihnen jetzt gleich: Es wird nicht umsonst sein.";
			link.l1 = "Heh! Und wie viel wollen Sie?";
			link.l1.go = "storehelper_1";
		break;
		
		case "storehelper_1":
			dialog.text = "Eintausend Achtstücke. Und es gibt nichts, was du tun musst, in einer Stunde werden deine Kandidaten für den Job in meiner Taverne sein, mehrere Kandidaten. Du wirst mit ihnen sprechen und den auswählen können, der dir mehr zusagt als die anderen.";
			if (int(Pchar.money) >= 1000)
			{
				link.l1 = "Ahh... Also gut, hier, nimm tausend!";
				link.l1.go = "storehelper_2";
			}
			link.l2 = "Es tut mir leid, aber ich habe nicht so viel Geld!";
			link.l2.go = "storehelper_exit";
		break;
		
		case "storehelper_2":
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "Mach dir keine Sorgen, Kumpel. Du bekommst die Hälfte dieses Betrags vom Kandidaten zurück. Ich werde ihm sagen, dass das die Kosten für deine Dienste sind, he he... Sie geben nicht mehr als fünfhundert. Komm in einer Stunde in meine Taverne, bis dahin habe ich die Leute, die du brauchst, hier auf dich warten.";
			link.l1 = "Gut. Ich komme in einer Stunde wieder, "+npchar.name+".";
			link.l1.go = "storehelper_3";
			npchar.quest.storehelper = "true";
			DelLandQuestMark(npchar);
		break;
		
		case "storehelper_3":
			DialogExit();
			SetLaunchFrameFormParam("One hour passed...", "", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0); //крутим время
			RecalculateJumpTable();
			Storehelper_hire("");
		break;
		
		case "storehelper_exit":
			dialog.text = "Es tut mir leid, dass auch Sie nicht so viel Geld haben. Aber Sie wissen ja selbst, solche Angelegenheiten werden nicht nur für ein 'Danke' erledigt. Also...";
			link.l1 = "Ich verstehe. Aber ich habe wirklich kein Geld. Also gut, Tschüss...";
			link.l1.go = "exit";
			//pchar.quest.storehelper.over = "yes";
			//AddTimeToCurrent(2,0);
			//DeleteAttribute(pchar, "questTemp.Sharlie.Storehelper");
			//CloseQuestHeader("SharlieA");
		break;
		
		case "seabattle":
			DelLandQuestMark(npchar);
			dialog.text = "Wovon redest du, Kumpel? Welchen Wein meinst du?";
			link.l1 = "Ein Mann namens Walter Catcher hat mich zu Ihnen geschickt. Er sagte, Sie bräuchten ein Schiff, um eine Weinladung für zehntausend Pesos nach Guadeloupe zu transportieren. Und dass Sie genau mein Schiff für diesen Job benötigen...";
			link.l1.go = "seabattle_1";
			npchar.quest.seabattle = "true";
		break;
		
		case "seabattle_1":
			dialog.text = "Hör zu, Kamerad, ich handle nicht mit Wein, ich brauche deine Dienste nicht und ich kenne keinen Walter Catcher.";
			link.l1 = "So was! Also wurde dieser Catcher gar nicht von dir geschickt... Dann, was ist das ganze Theater hier?";
			link.l1.go = "seabattle_2";
		break;
		
		case "seabattle_2":
			dialog.text = "Heh! Nun, das ist entweder ein Art von Fehler oder ein schlechter Scherz oder...";
			link.l1 = "Oder was?";
			link.l1.go = "seabattle_3";
		break;
		
		case "seabattle_3":
			dialog.text = "Verstehst du es nicht selbst? Jemand musste dich nach Le Francois locken, warum weiß ich nicht. An deiner Stelle würde ich mich beeilen und hier rauskommen, und dabei so vorsichtig wie möglich sein. Das riecht nach schmutzigen Geschäften, Kumpel...";
			link.l1 = "Ich vermute, du hast recht. Dieser Catcher hatte mir eh nicht gefallen. Also gut, ich folge deinem Rat. Tschüss, Cesar!";
			link.l1.go = "seabattle_4";
		break;
		
		case "seabattle_4":
			DialogExit();
			AddQuestRecord("Sharlie", "16");
			pchar.quest.seabattle.win_condition.l1 = "location";
			pchar.quest.seabattle.win_condition.l1.location = "Martinique";
			pchar.quest.seabattle.function = "SharlieSeabattle_ship";
			
			pchar.quest.NewGameTip4.win_condition.l1 = "location";
			pchar.quest.NewGameTip4.win_condition.l1.location = "LeFransua_town";
			pchar.quest.NewGameTip4.function = "ShowNewGameTip";
			pchar.quest.NewGameTip4.text = "Your first sea battle is coming! Save you game!";					  
		break;
		
		case "Portugal":
			dialog.text = "Ja, Ihr Freund ist hier angekommen, Kapitän. Er kam gestern an und mietete ein Zimmer oben. Seine Kameraden sind auch hier, he-he... Sie sitzen dort drüben. Frag sie!";
			link.l1 = "...";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			DialogExit();
			AddDialogExitQuestFunction("Portugal_enterPirates");
			npchar.quest.portugal = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

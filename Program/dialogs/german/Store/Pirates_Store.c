// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	bool bOk;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Mach weiter, was willst du?","Wir haben gerade darüber gesprochen. Du musst es vergessen haben...","Das ist das dritte Mal heute, dass du von irgendeiner Frage sprichst...","Hör zu, dies ist ein Laden. Die Leute kaufen hier Sachen. Stör mich nicht!","Block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Du weißt, "+NPChar.name+", vielleicht nächstes Mal.","Richtig, ich habe aus irgendeinem Grund vergessen...","Ja, es ist wirklich das dritte Mal...","Hm, ich werde nicht...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				link.l1 = "Hör zu, "+npchar.name+", haben Sie in letzter Zeit Miguel Dichoso auf Isla Tesoro gesehen?";
				link.l1.go = "tieyasal";
			}
			// Addon 2016-1 Jason пиратскаЯ линейка
			if(CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "pasq_start")
			{
				link.l1 = ""+npchar.name+", ich bin im Auftrag von Marcus Tyrex hier. Er sagte, dass Sie einen Mann für einen Job brauchen.";
				link.l1.go = "mtraxx";
			}
			if(CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "pasq_win")
			{
				link.l1 = ""+npchar.name+", die 'Rosbohom' wurde gefunden und gefangen genommen. Sollen wir anfangen zu entladen und zu zählen?";
				link.l1.go = "mtraxx_5";
			}
		break;
				
		// город майя
		case "tieyasal":
			dialog.text = "Ja, habe ich. Er hat hier Vorräte für sein Schiff gekauft. Übrigens, es war sehr kürzlich. Ihr habt euch buchstäblich um ein paar Tage verpasst. Er könnte noch in dieser Siedlung sein. Ich spioniere nicht für Leute, weißt du. Frag noch etwas herum und wer weiß, vielleicht findest du deinen Don.";
			link.l1 = "In Ordnung. Danke für die Info!";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			DialogExit();
			npchar.quest.tieyasal = "true";
		break;
		
		// Addon 2016-1 Jason пиратскаЯ линейка
		case "mtraxx":
			pchar.quest.Mtraxx_PasqualeLate.over = "yes";
            dialog.text = "Genau! Es ist gut, dass du rechtzeitig angekommen bist. Jetzt lass mich dir den Kern der Sache erzählen...";
			link.l1 = "Ich bin ganz Ohr.";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
			string sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(int(pchar.questTemp.Mtraxx.Crdn.Ship), "Name")));
            dialog.text = "In diesem Moment ein "+sTemp+", das holländische Schiff namens 'Rosbohom', erreicht unsere Gewässer zusammen mit einem Wachschiff. Sie ist beladen mit Ebenholz und segelt von Willemstad aus, um ein weiteres Wachschiff zu treffen, um eine sichere Reise nach Europa zu gewährleisten. Ich weiß nicht, welche Route sie nimmt, über Sint Maarten oder über Espanyol, aber ich kenne die Koordinaten ihres Treffpunktes\nIhre Aufgabe ist es, die Holländer dort zu finden, den Händler zu entern und ihre Ladung zu mir zu bringen. Ich werde zahlen, sobald die Ladung geliefert ist.";
			link.l1 = "Verstanden. Zeit und Ort?";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
			int i = int(pchar.questTemp.Mtraxx.Crdn.minN2)-10;
			int n = int(pchar.questTemp.Mtraxx.Crdn.minW2)-10;
            dialog.text = ""+int(pchar.questTemp.Mtraxx.Crdn.degN)+" "+i+" Norden und "+int(pchar.questTemp.Mtraxx.Crdn.degW)+" "+n+"Westen. Es muss irgendwo südlich oder südwestlich von Isla Tesoro sein, ich bin nicht gut darin, ich bin kein Seemann, aber du bist es. Du hast ungefähr fünf Tage Zeit, um die Arbeit zu erledigen.";
			link.l1 = "Verstanden... Ich habe es. Keine Zeitverschwendung dann!";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "Gottes Segen, Kapitän. Ich warte auf Sie und die Fracht.";
			link.l1 = "...";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_convoy";
		   i = int(pchar.questTemp.Mtraxx.Crdn.minN2)-10;
           n = int(pchar.questTemp.Mtraxx.Crdn.minW2)-10;
		   AddQuestRecord("Roger_4", "3");
		   AddQuestUserData("Roger_4", "sShip", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(int(pchar.questTemp.Mtraxx.Crdn.Ship), "Name")+ "Gen")));
		   AddQuestUserData("Roger_4", "sdegN", int(pchar.questTemp.Mtraxx.Crdn.degN));
		   AddQuestUserData("Roger_4", "sminN", i);
		   AddQuestUserData("Roger_4", "sdegW", int(pchar.questTemp.Mtraxx.Crdn.degW));
		   AddQuestUserData("Roger_4", "sminW", n);
		   SetFunctionTimerCondition("Mtraxx_PasqualeTimeConvoy", 0, 0, 6, false);
		   SetFunctionTimerCondition("Mtraxx_PasqualeConvoyOver", 0, 0, 7, false);
		break;
		
		case "mtraxx_5":
			iTotalTemp = GetSquadronGoods(pchar, GOOD_EBONY);
			if (iTotalTemp < 1)
			{
				dialog.text = "Bist du verrückt, junger Mann? In deinen Frachträumen befindet sich kein einziges Ebenholzbrett! Dies ist eine unverschämte Täuschung! Geh weg von hier! Ich werde Marcus davon informieren! Raus!!!";
				link.l1 = "Hm...";
				link.l1.go = "mtraxx_6";
				break;
			}
			if (iTotalTemp < int(int(pchar.questTemp.Mtraxx.Crdn.Ebony)/4))
			{
				dialog.text = "Veräppelst du mich, Junge? Dein Laderaum hat nur ein paar Splitter aus Ebenholz! Das ist eine freche Täuschung! Raus hier! Ich werde Marcus davon informieren! Raus!!!";
				link.l1 = "Hm...";
				link.l1.go = "mtraxx_6";
				break;
			}
			if (iTotalTemp < int(pchar.questTemp.Mtraxx.Crdn.Ebony)-20)
			{
				dialog.text = "Der Rosbohom hatte zumindest "+FindRussianQtyString(int(pchar.questTemp.Mtraxx.Crdn.Ebony))+" aus Ebenholz. Warum hast du mir weniger gebracht?";
				link.l1 = "Nun... wie du weißt, musste ich während des Kampfes einen Teil davon loswerden. Plus die Ratten, verdammt noch mal...";
				link.l1.go = "mtraxx_7";
				break;
			}
            dialog.text = "Sehr gut. Wie viel hast du? "+FindRussianQtyString(iTotalTemp)+"? Prächtig! Ich werde Ihnen 150 Pesos für ein Stück zahlen.";
			link.l1 = "150 Dublonen? Ich vermute, dass dieses Ebenholz viel mehr kostet.";
			link.l1.go = "mtraxx_10";
		break;
		
		case "mtraxx_6":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_angry";
		   DoQuestReloadToLocation("Pirates_town", "reload", "reload6", "");
		   AddQuestRecord("Roger_4", "8");
		   CloseQuestHeader("Roger_4");
		   QuestSetCurrentNode("Terrax", "mtraxx_34");
		break;
		
		case "mtraxx_7":
            dialog.text = "Ratten? Na-na... Aber gut. 100 Pesos pro Stück und du bist frei zu gehen.";
			link.l1 = "100 Pesos nur? Das ist ein Überfall!";
			link.l1.go = "mtraxx_8";
		break;
		
		case "mtraxx_8":
			AddMoneyToCharacter(pchar, iTotalTemp*100);
			RemoveCharacterGoods(pchar, GOOD_EBONY, iTotalTemp);
            dialog.text = "Raub ist Ihr Handwerk, Kapitän, ich bin ein einfacher Händler. Nehmen Sie Ihr Geld und streiten wir uns nicht weiter, Sie haben bereits eine gute Summe gemacht, indem Sie einen Teil meiner Ladung anderswo verkauft haben.";
			link.l1 = "Verpiss dich dann!";
			link.l1.go = "mtraxx_9";
		break;
		
		case "mtraxx_9":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_fail";
		   AddQuestRecord("Roger_4", "8");
		   CloseQuestHeader("Roger_4");
		   QuestSetCurrentNode("Terrax", "mtraxx_34");
		break;
		
		case "mtraxx_10":
            dialog.text = "Und Sie haben Recht, Kapitän, aber zuerst, versuchen Sie, gestohlene Waren zu verkaufen und ich werde sehen, wie viel andere Händler Ihnen dafür bezahlen werden. Der Ihnen angebotene Preis ist sehr hoch. Zweitens, es war mein Hinweis, Sie hätten diesen Karawanen niemals alleine gefunden, dazu gab es andere Wertsachen und Waren darauf und ich beanspruche sie nicht. Drittens, ich werde Ihnen die besten Kredite in den Augen von Marcus Tyrex geben und das kostet viel, glauben Sie mir. Und schließlich, viertens, ein armer Händler muss irgendwie seinen Lebensunterhalt verdienen.";
			link.l1 = "Wer! Ich muss mich angesichts solcher Argumente zurückziehen "+npchar.name+". Lass uns zählen.";
			link.l1.go = "mtraxx_11";
		break;
		
		case "mtraxx_11":
			AddMoneyToCharacter(pchar, iTotalTemp*150);
			RemoveCharacterGoods(pchar, GOOD_EBONY, iTotalTemp);
            dialog.text = "Herrlich. Nehmen Sie Ihre Münzen. Es war mir ein Vergnügen. Vergewissern Sie sich, meinen Laden von Zeit zu Zeit zu überprüfen. Mögest du auf See Glück haben!";
			link.l1 = "Und du in deinem Handwerk...";
			link.l1.go = "mtraxx_12";
		break;
		
		case "mtraxx_12":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_complete";
		   AddQuestRecord("Roger_4", "9");
		   pchar.quest.mtr_pasq_fin.win_condition.l1 = "location";
		   pchar.quest.mtr_pasq_fin.win_condition.l1.location = "Pirates_town";
		   pchar.quest.mtr_pasq_fin.function = "Mtraxx_PasqualeJeffry";
		   bDisableFastReload = true;
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

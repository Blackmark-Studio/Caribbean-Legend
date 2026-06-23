// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	ref FortChref;
	FortChref = GetFortCommander(NPChar.City);
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Was wünscht Ihr? Fragt nur.","Ich höre Ihnen zu, was ist die Frage?"),"Das ist das zweite Mal, dass Sie versuchen zu fragen...","Es ist das dritte Mal, dass Sie versuchen zu fragen...","Wann wird das endlich aufhören?! Ich bin ein beschäftigter Mann, der sich um Kolonialangelegenheiten kümmert und Sie stören mich immer noch!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ich habe meine Meinung geändert...","Nicht jetzt. Falscher Ort und Zeit."),"Wahr... Aber später, nicht jetzt...","Ich werde fragen... Aber ein bisschen später...","Es tut mir leid, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";
			// Addon 2016-1 Jason пиратскаЯ линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_6")
			{
				link.l1 = "Eure Exzellenz, ich bin hier aufgrund des inhaftierten Offiziers, Lope Montoro...";
                link.l1.go = "Mtraxx";
			}
		break;
		
		case "Cupture_after":
            dialog.text = RandPhraseSimple("Du hast bereits alles genommen. Was willst du noch?","Gibt es noch etwas, das Sie nicht geschnappt haben?");
            link.l1 = RandPhraseSimple("Nur mal umsehen...","Nur zur Kontrolle, ich könnte vergessen haben, etwas mitzunehmen...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		case "Slavetrader_HavanaAttack":
			dialog.text = "Verdammte Diebe! Ihr wagt es, Havanna anzugreifen?! Was wollt ihr?!";
			link.l1 = "Denk ein wenig nach, du wirst verstehen.";
			link.l1.go = "Slavetrader_HavanaAttack_1";
			pchar.quest.Slavetrader_HavanaOver.over = "yes";
			AfterTownBattle();
        break;
		
		case "Slavetrader_HavanaAttack_1":
			dialog.text = "Gold, natürlich! Was könnte euch Schurken sonst interessieren als Gold?! Und wir haben es nicht... Nur ein paar Maß im Lager.";
			link.l1 = "Ha-ha ... Nein, wir sind nicht an Gold interessiert. Wir sind hier für Elfenbein ... das schwarze. Verstehst du mich?";
			link.l1.go = "Slavetrader_HavanaAttack_2";
        break;
		
		case "Slavetrader_HavanaAttack_2":
			if (CheckAttribute(FortChref, "Fort.Mode") && int(FortChref.Fort.Mode) != FORT_DEAD)//для особо хитрых - нефиг лезть с суши
			{
				dialog.text = "Ha! Ich habe vermutet, dass Sie hierher wegen Sklaven gekommen sind. Aber sie befinden sich in der Festung. Unsere Verstärkung kommt jetzt hierher und Ihre Bande wird in einer Sekunde vernichtet werden.";
				link.l1 = "Verdammt nochmal! Gut, sitz hier und beweg dich nicht... Lass uns hier wegkommen! Scheiße...";
				link.l1.go = "Slavetrader_HavanaAttack_lose";
			}
			else
			{
				dialog.text = "Aber wie... Wie wussten Sie das?";
				link.l1 = "Ha! Nur ein Idiot könnte 5000 Sklaven an einem Ort versammeln und hoffen, dass niemand es bemerken würde. Sie stinken von hier bis zum verdammt Tortuga... Ich hoffe, du verstehst, dass wir sie dir wegnehmen werden.";
				link.l1.go = "Slavetrader_HavanaAttack_3";
			}
        break;
		
		case "Slavetrader_HavanaAttack_3":
			dialog.text = "Gut, Sie haben sowieso gewonnen und wir müssen Ihrer Gewalt gehorchen. Aber hoffen Sie nicht, der Gerechtigkeit zu entkommen, nachdem Sie dieses Raubüberfall begangen und zwei spanische Kriegsschiffe versenkt haben.";
			link.l1 = "Plustere dich nicht so auf oder du bekommst einen Herzinfarkt. Setz dich hier hin und beweg dich nicht...";
			link.l1.go = "Slavetrader_HavanaAttack_4";
			ChangeCharacterHunterScore(pchar, NationShortName(int(npchar.Nation)) + "hunter", 50);
			ChangeCharacterComplexReputation(pchar,"nobility", -8);
        break;
		
		 case "Slavetrader_HavanaAttack_4":
			string sTemp;
            NextDiag.CurrentNode = "Cupture_after";
			DialogExit();
			SetReturn_Gover_Dialog_Exit(NPChar);
            Statistic_AddValue(Pchar, NationShortName(int(NPChar.nation)) + "_GrabbingTown", 1);
			pchar.quest.Slavetrader_DieHardHavana.over = "yes";//теперь можно на карту
            SetCharacterGoods(pchar, GOOD_SLAVES, 5000+rand(500));// c перегрузом пойдёт
            Log_SetStringToLog("Slaves have been put onto your ship");
			Log_SetStringToLog("You've got 30 days to deliver the slaves to your employer");
			chrDisableReloadToLocation = false;
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			AddQuestRecord("Slavetrader", "27");
			AddQuestUserData("Slavetrader", "sQty", sTemp);
			SetFunctionTimerCondition("Slavetrader_FiveTSlavesOver", 0, 0, 30, false);	//таймер
			pchar.questTemp.Slavetrader = "Win_HavanaFort";
        break;
		
		case "Slavetrader_HavanaAttack_lose":
            NextDiag.CurrentNode = "Cupture_after";
			DialogExit();
			SetReturn_Gover_Dialog_Exit(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -8);
            Statistic_AddValue(Pchar, NationShortName(int(NPChar.nation)) + "_GrabbingTown", 1);
			chrDisableReloadToLocation = false;
			pchar.quest.Slavetrader_DieHardHavana.over = "yes";//можно на карту
			pchar.quest.Slavetrader_HavanaAttack.over = "yes";//если из Сантьяго по суше пришёл - уберем корабли
			AddQuestRecord("Slavetrader", "27_1");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
        break;
		
		// Addon 2016-1 Jason пиратскаЯ линейка
		case "Mtraxx":
            dialog.text = "Wie merkwürdig... noch mehr Beschwerden?";
			link.l1 = "Nein-nein, ganz im Gegenteil, Eure Exzellenz. Lope ist ein alter Armee-Freund, wir haben gemeinsam in Europa gekämpft... Ich würde ihm gerne helfen und kam, um Ihre Unterstützung zu bitten.";
			link.l1.go = "Mtraxx_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtraxx_1":
            dialog.text = "Hm.. Nun, ich nehme an, da du zu mir gekommen bist, kennst du bereits diese... absurde Geschichte?";
			link.l1 = "Ich tue es, Eure Exzellenz.";
			link.l1.go = "Mtraxx_2";
		break;
		
		case "Mtraxx_2":
            dialog.text = "Ich schlage vor, Sie kontaktieren Don Rosario Gusman. Er, genau wie Sie, möchte Don Lope Montero helfen. Er versuchte, das Opfer zu kontaktieren, jedoch waren die Verhandlungen erfolglos. Treffen Sie sich mit ihm, er wird die Details erklären. Sie finden Don Rosario nachmittags von vier bis acht auf den Straßen. Er überprüft täglich alle Wachposten der Stadt.";
			link.l1 = "Dankbarkeit, Eure Exzellenz!";
			link.l1.go = "Mtraxx_3";
		break;
		
		case "Mtraxx_3":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_7";
			AddQuestRecord("Roger_1", "17");
			Mtraxx_CreateRosario();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

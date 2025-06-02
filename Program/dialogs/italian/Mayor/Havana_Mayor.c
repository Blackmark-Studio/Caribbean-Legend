// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	ref FortChref;
	FortChref = GetFortCommander(NPChar.City);
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Cosa vuoi? Chiedi pure.","Ti sto ascoltando, qual è la domanda?"),"Questa è la seconda volta che provi a chiedere...","È la terza volta che provi a chiedere...","Quando finirà tutto questo?! Sono un uomo impegnato, lavoro su questioni coloniali e tu continui a disturbarmi!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea...","Non ora. Luogo e momento sbagliati."),"È vero... Ma più tardi, non adesso...","Chiederò... Ma un po' più tardi...","Mi dispiace, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";
			// Addon 2016-1 Jason пиратскаЯ линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_6")
			{
				link.l1 = "Sua Eccellenza, sono qui a causa dell'ufficiale imprigionato, Lope Montoro...";
                link.l1.go = "Mtraxx";
			}
		break;
		
		case "Cupture_after":
            dialog.text = RandPhraseSimple("Hai già preso tutto. Cosa vuoi ancora?","C'è qualcosa che non hai preso?");
            link.l1 = RandPhraseSimple("Solo dando un'occhiata...","Solo un controllo, potrei aver dimenticato di prendere qualcosa...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		case "Slavetrader_HavanaAttack":
			dialog.text = "Maledetti ladri! Osate attaccare L'Avana?! Cosa volete?!";
			link.l1 = "Pensa un po', capirai.";
			link.l1.go = "Slavetrader_HavanaAttack_1";
			pchar.quest.Slavetrader_HavanaOver.over = "yes";
			AfterTownBattle();
        break;
		
		case "Slavetrader_HavanaAttack_1":
			dialog.text = "Oro, ovviamente! In cosa altro potreste bastardi essere interessati se non oro?! E non lo abbiamo... Solo alcune misure nel negozio.";
			link.l1 = "Ah-ah... No, non siamo interessati all'oro. Siamo venuti qui per l'avorio... quello nero. Mi capisci?";
			link.l1.go = "Slavetrader_HavanaAttack_2";
        break;
		
		case "Slavetrader_HavanaAttack_2":
			if (CheckAttribute(FortChref, "Fort.Mode") && sti(FortChref.Fort.Mode) != FORT_DEAD)//для особо хитрых - нефиг лезть с суши
			{
				dialog.text = "Ah! Sospettavo che fossi venuto qui per gli schiavi. Ma si trovano nel forte. I nostri rinforzi stanno arrivando adesso e la tua banda sarà distrutta in un attimo.";
				link.l1 = "Maledizione! Va bene, siediti qui e non muoverti... Fuggiamo da qui! Merda...";
				link.l1.go = "Slavetrader_HavanaAttack_lose";
			}
			else
			{
				dialog.text = "Ma come... Come hai fatto a saperlo?";
				link.l1 = "Ah! Solo un idiota potrebbe radunare 5000 schiavi in un solo luogo e sperare che nessuno lo sappia. Puzzano da qui a maledetta Tortuga... Spero che tu capisca che te li stiamo togliendo.";
				link.l1.go = "Slavetrader_HavanaAttack_3";
			}
        break;
		
		case "Slavetrader_HavanaAttack_3":
			dialog.text = "Bene, hai vinto comunque e dobbiamo obbedire alla tua violenza. Ma non sperare di sfuggire alla giustizia dopo quel furto e dopo aver affondato due navi da guerra spagnole.";
			link.l1 = "Non gonfiarti così o avrai un infarto. Siediti qui e non muoverti...";
			link.l1.go = "Slavetrader_HavanaAttack_4";
			ChangeCharacterHunterScore(pchar, NationShortName(sti(npchar.Nation)) + "hunter", 50);
			ChangeCharacterComplexReputation(pchar,"nobility", -8);
        break;
		
		 case "Slavetrader_HavanaAttack_4":
			string sTemp;
            NextDiag.CurrentNode = "Cupture_after";
			DialogExit();
			SetReturn_Gover_Dialog_Exit(NPChar);
            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
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
            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
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
            dialog.text = "Com'è curioso... ancora lamentele?";
			link.l1 = "No-no, al contrario, vostra Eccellenza. Lope è un vecchio amico dell'esercito, abbiamo combattuto insieme in Europa... Mi piacerebbe aiutarlo, e sono venuto a chiedere il vostro aiuto.";
			link.l1.go = "Mtraxx_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtraxx_1":
            dialog.text = "Mm.. Beh, presumo, visto che sei venuto da me, che tu già conosci... questa storia assurda?";
			link.l1 = "Certo, Vostra Eccellenza.";
			link.l1.go = "Mtraxx_2";
		break;
		
		case "Mtraxx_2":
            dialog.text = "Ti suggerisco di contattare don Rosario Gusman. Lui, proprio come te, vuole aiutare don Lope Montero. Ha tentato di contattare la vittima, tuttavia, le trattative non hanno portato frutti. Incontralo, ti spiegherà i dettagli. Puoi trovare don Rosario per le strade dalle quattro alle otto del pomeriggio. Fa un'ispezione completa dei posti di guardia della città ogni giorno.";
			link.l1 = "Grazie, vostra Eccellenza!";
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

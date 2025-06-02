// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Tutte le voci di "+GetCityName(npchar.city)+" al vostro servizio. Cosa vorreste scoprire?","Ne stavamo proprio parlando. Devi aver dimenticato...","Questa è la terza volta oggi che mi chiedi...","Ripeti sempre le stesse cose come un pappagallo...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sai, "+NPChar.name+", forse la prossima volta.","Giusto, per qualche motivo ho dimenticato...","Sì, è davvero la terza volta...","Sì...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
			{
				link.l1 = "Ascolta, è arrivato qui in questa città un alchimista, un medico? È italiano, ha circa trent'anni, si chiama Gino Gvineili?";
				link.l1.go = "guardoftruth";
			}
			// Калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && !CheckAttribute(npchar, "quest.Caleuche"))
			{
				link.l1 = "Ascolta, sto cercando un cacciatore di nome Fergus Hooper. Mi è stato detto che vive qui. Dove posso trovarlo?";
				link.l1.go = "caleuche";
			}
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("No, non l'ho fatto. Abbiamo erboristi e medici, ma nessuno con un nome del genere.","È la prima volta che sento un nome così strano. No, l'uomo di cui parli non è mai venuto a farci visita.","Non abbiamo affatto alcun tipo di alchimisti. Abbiamo dei medici, ma nessuno con un nome simile.");
			link.l1 = "Capisco. Che peccato. Continuerò a cercare!";
			link.l1.go = "exit";
			npchar.quest.jino = "true";
		break;
		
		// Калеуче
		case "caleuche":
			dialog.text = "Fergus? Visita spesso il mio posto. Ma è nella selva da ieri. Non preoccuparti, tornerà tra una settimana, a bere rum e a vantarsi delle sue avventure marittime. Anche se, lo ammetto, è un dannatamente buon cacciatore. Non conosco nessuno che riesce a catturare serpenti come lui.";
			link.l1 = "Serpenti? Hm. Quando dovrei tornare qui per trovarlo?";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Almeno tre giorni. Sappi che lui arriva sempre qui non prima delle sei di sera e non se ne va dopo le dieci.";
			link.l1 = "Come sembra? Non l'ho mai visto prima.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "Barbuto, di mezza età, indossa un cappotto marrone, un cappello e stivali lunghi.";
			link.l1 = "Grazie! Mi hai aiutato molto, amico. Ci vediamo in giro!";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			DialogExit();
			AddQuestRecord("Caleuche", "8");
			int iTerms = sti(pchar.questTemp.Caleuche.Belizterms);
			SetFunctionTimerCondition("Caleuche_FergusCome", 0, 0, iTerms, false);
			npchar.quest.Caleuche = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

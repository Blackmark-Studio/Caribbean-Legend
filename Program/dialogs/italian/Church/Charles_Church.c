// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Che tipo di domande, "+GetSexPhrase("mio figlio","mia figlia")+"?","Fai pure, ti sto ascoltando..."),"Ascolto, parla adesso, "+GetSexPhrase("mio figlio","mia figlia")+"...","Per la terza volta, "+GetSexPhrase("mio figlio","mia figlia")+", chiedi ciò di cui hai bisogno.","Un ecclesiastico ha molto lavoro e tu mi stai distrarrendo, "+GetSexPhrase("mio figlio","mia figlia")+"...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea...","Non in questo momento, padre..."),"Non ho nulla da dire, mi scuso.","Chiederò, ma più tardi. Perdonami, padre.","Perdonami, santo padre...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		case "Gravel1":
			dialog.text = "Cosa posso fare per te, mio figlio?";
			link.l1 = "Ti sto cercando, Georges.";
			link.l1.go = "Gravel2";
			DelLandQuestMark(npchar);
		break;
		
		case "Gravel2":
			dialog.text = "Io? Ma perché?";
			link.l1 = "Longway e Mynheer Van Merden hanno bisogno che tu indaghi di nuovo. Longway non può mostrare il suo volto qui dopo il suo... tour precedente.";
			link.l1.go = "Gravel3";
		break;
		
		case "Gravel3":
			AddQuestRecord("PZ", "23");
			dialog.text = "Ammorbidisci la voce, per l'amor di Dio! Ma capisco. Farò del mio meglio.";
			link.l1 = "Eccellente, Georges. Sei uno dei nostri alleati più preziosi. Ci vediamo dopo.";
			link.l1.go = "Exit";
			DelMapQuestMarkCity("Charles");
			
			pchar.questTemp.PZ_Etap5_Start = true;
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.PZ_ProvalFinal"))
			{
				PChar.quest.PZ_Etap5_Start.win_condition.l1 = "location";
				PChar.quest.PZ_Etap5_Start.win_condition.l1.location = "Pirates_town";
				PChar.quest.PZ_Etap5_Start.win_condition = "PZ_Etap5_Start";
				AddMapQuestMarkCity("Pirates", false);
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1 && !CheckAttribute(pchar, "questTemp.PZ_ProvalFinal"))
			{
				PChar.quest.PZ_Etap5_Start.win_condition.l1 = "location";
				PChar.quest.PZ_Etap5_Start.win_condition.l1.location = "Pirates_town";
				PChar.quest.PZ_Etap5_Start.win_condition = "PZ_Etap5_Start";
				AddMapQuestMarkCity("Pirates", false);
			}
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

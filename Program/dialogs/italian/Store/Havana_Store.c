// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Avanti, cosa desideri?","Ne stavamo appena parlando. Devi aver dimenticato...","Questa è la terza volta oggi che parli di qualche domanda...","Ascolta, questo è un negozio. Le persone comprano roba qui. Non disturbarmi!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sai, "+NPChar.name+", forse la prossima volta.","Giusto, per qualche motivo ho dimenticato...","Sì, è davvero la terza volta...","Mh, non lo farò...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "Ascolta, è mai venuto qui nel tuo negozio un uomo di nome Joachim Merriman? Un signore di mezza età, portoghese, con baffi, barba imperiale e occhi penetranti? Forse, ha comprato qualcosa?";
				link.l1.go = "caleuche";
			}
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "No, nessuno dei miei clienti somiglia a come hai descritto. Inoltre, non ho mai sentito questo nome prima. Mi dispiace, non posso aiutarti di più.";
			link.l1 = "Capisco. Peccato. Bene, continuerò la mia ricerca...";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

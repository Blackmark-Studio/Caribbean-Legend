// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quali domande avete?","Come posso aiutarti?"),"Hai cercato di farmi quella domanda poco tempo fa...","Sì, lascia che indovini... Ancora una volta girando in tondo?","Ascolta, io mi occupo delle finanze qui, non rispondo alle domande...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mi sono ricreduto...","Non ho nulla di cui parlare al momento."),"Umph, dove se n'è andata la mia memoria...","Hai indovinato, mi dispiace...","Capisco...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Карибские нравы
			if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "usurer" && !CheckAttribute(npchar, "quest.TrialTalk1"))
            {
                link.l1 = "";
                link.l1.go = "trial";
            }
		break;
		
		case "trial":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

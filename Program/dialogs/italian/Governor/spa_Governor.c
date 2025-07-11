// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
    int i, iTemp, iMoney, ShipType, Rank;
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = RandPhraseSimple("Che tipo di domande?","Di cosa hai bisogno?");
			link.l1 = RandPhraseSimple("Niente di importante, Signore.","Non ho nulla da dire, mi scuso.");
		    link.l1.go = "exit";
		break;
		
		case "work_1":  // работа на благо короны - линейка нации
			if (CheckAttribute(npchar, "notQuestLine"))
			{
                dialog.text = "Sfortunatamente non posso considerarti per un lavoro. Non sei qualcuno con cui voglio lavorare al momento. Addio.";
                link.l1 = "Non puoi essere serio.. ma va bene.";
                link.l1.go = "exit";
				break;
			}                   
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

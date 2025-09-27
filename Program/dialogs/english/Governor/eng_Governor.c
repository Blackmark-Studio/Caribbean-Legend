// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("What kind of questions?","What is it you need?");
			link.l1 = RandPhraseSimple("Nothing of importance, Sir.","I've nothing to say, apologies.");
		    link.l1.go = "exit";
		break;
		
		case "work_1":  // работа на благо короны - линейка нации
			if (CheckAttribute(npchar, "notQuestLine"))
			{
                dialog.text = "Unfortunately, I can't consider you for a job. You're not someone I wish to work with at the moment. Farewell.";
                link.l1 = "You can't be serious... but very well.";
                link.l1.go = "exit";
				break;
			}            
		break;		        
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

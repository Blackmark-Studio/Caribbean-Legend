// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = RandPhraseSimple("Milyen kérdések?", "Mire van szüksége?");
			link.l1 = RandPhraseSimple("Semmi fontosat, uram.", "Nincs mit mondanom, elnézést.");
		    link.l1.go = "exit";
		break;
		
		case "work_1":  // работа на благо короны - линейка нации
			if (CheckAttribute(npchar, "notQuestLine"))
			{
                dialog.text = "Sajnos, nem tudom figyelembe venni önt egy munkára. Jelenleg nem akarok önnel dolgozni. Viszontlátásra.";
                link.l1 = "Ezt nem gondolhatja komolyan... de nagyon jó.";
                link.l1.go = "exit";
				break;
			}            
		break;		 		            
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

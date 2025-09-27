// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Mit akarsz?", "Mit szeretnél tudni?"), "Mire van szüksége, " + GetAddress_Form(NPChar) + "?", "Már harmadszor próbálod megkérdezni...", "Elegem van belôled, tûnj el!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Sajnálom, meggondoltam magam.", "Semmiség, elnézést."), "Elfelejtettem, elnézést kérek...",
                      "Harmadszorra sikerül, mi? Elnézést...", "Bocsánat, bocsánat! Akkor majd én kikísérem magam...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "Figyelj, járt itt egy Joachim Merriman nevû férfi? Egy középkorú, portugál senor, bajusszal, császári szakállal és szúrós szemekkel? Talán egy öbölben vagy a világítótorony közelében szállt partra? Látott már hozzá hasonlót?";
				link.l1.go = "merriman";
			}
		break;
		
		// калеуче
		case "merriman":
			dialog.text = "Nem, pajtás, nem láttam még senkit, mint 'im. Észrevettem volna, aye.";
			link.l1 = "Értem, milyen kár. Köszönöm, hogy idôt szakított rám, akkor folytatom a keresést.";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}

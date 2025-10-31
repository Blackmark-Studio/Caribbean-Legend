// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Milyen kérdések?", "Mit akarsz, " + GetAddress_Form(NPChar) + "?"), "Kérdések ismét, " + GetAddress_Form(NPChar) + "...", "Kérdések, kérdések... Mi lenne, ha cserélnénk, " + GetAddress_Form(NPChar) + "huh?",
                          "Figyelj, meddig akarsz még beszélgetni?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Egyelôre nincsenek kérdések...", "Sajnálom, most nincs mit mondanom..."), "Még egyszer, sajnálom...",
                      "Talán tényleg itt az ideje kereskedni...", "Sajnálom, cseréljünk...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Figyelj, nem ismerôs a név 'Juan' ?";
				link.l1.go = "Consumption";
			}			
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "Nem, ez nem... Kérem, ne zavarjon, nagyon elfoglalt vagyok... Micsoda idióta kérdés...";
			link.l1 = "Értem, értem. Elnézést, hogy az idejét vesztegetem...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

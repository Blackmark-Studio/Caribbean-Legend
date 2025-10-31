// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Milyen kérdések, "+ GetSexPhrase("fiam","lányom") +"?", "Kérdezz csak, hallgatlak..."), "Figyelek, beszélj most, "+ GetSexPhrase("fiam","lányom") +"...", "Harmadszorra, "+ GetSexPhrase("fiam","lányom") +", kérd, amire szükséged van.",
                          "Egy lelkésznek rengeteg munkája van, és te eltereled a figyelmemet, "+ GetSexPhrase("fiam","lányom") +"...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam...", "Most nem, atyám..."), "Nincs mit mondanom, elnézést kérek.",
                      "Megkérdezem, de késôbb. Bocsásson meg, atyám.", "Bocsásson meg, szent atyám...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Mondd, szent atyám, ismerôsen hangzik a név 'Juan' ?";
				link.l1.go = "Consumption";
			}
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "Igen, fiam. Sok Juan nevû hívô van ebben a városban.";
			link.l1 = "Értem. Elnézést a zavarásért, atyám...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

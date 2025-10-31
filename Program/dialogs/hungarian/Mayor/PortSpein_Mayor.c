// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Mit akarsz? Kérdezzen csak.", "Figyelek, mi a kérdés?"), "Ez már a második alkalom, hogy megpróbálsz kérdezni...", "Ez a harmadik alkalom, hogy megpróbálod megkérdezni...",
                          "Mikor lesz ennek vége?! Elfoglalt ember vagyok, gyarmati ügyekkel foglalkozom, és te még mindig zaklatsz!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam, sajnálom.", "Most nem. Rossz helyen és rossz idôben."), "Igaz, most nincs mit mondanom, sajnálom.",
                      "Majd késôbb megkérdezem.", "Sajnálom, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "Kegyelmes uram, 1654 áprilisában Miguel Dichoso parancsnoksága alatt egy fregatt állt. Azóta eltûnt. Emlékszik valamire róla? Talán meglátogatta önt, beszélgettek...";
				link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Igen, emlékszem arra az emberre. De nem emlékszem semmilyen részletre róla. Idejött, aztán egyszerûen elment. Nem tudok segíteni.";
			link.l1 = "Értem, értem. Elnézést a zavarásért.";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

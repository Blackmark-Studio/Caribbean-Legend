// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Milyen kérdései vannak?", "Miben segíthetek?"), "Nemrég megpróbált feltenni nekem néhány kérdést, amikor a boltban volt...", "Ez ma már a harmadik kérdés. Üzletet kell kötnöm, nem pedig értelmetlen beszélgetésekbe bocsátkoznom...",
                          "Még több kérdés? Mi lenne, ha inkább üzletet kötnénk?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam...", "Jelenleg nincs mirôl beszélnem."), "Igen, így van. Megpróbáltam... Amíg a boltban voltam...",
                      "Igen, ez a harmadik kérdés...", "Hm, talán megegyezhetünk...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;				
	}
	UnloadSegment(NPChar.FileDialog2);
}

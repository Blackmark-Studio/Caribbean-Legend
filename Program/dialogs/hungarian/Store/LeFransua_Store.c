// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Milyen kérdései vannak?", "Miben segíthetek?"), "Nemrég megpróbált feltenni nekem néhány kérdést, amikor az üzletemben járt...", "Ez ma már a harmadik kérdés. Üzletet kell kötnöm, nem pedig értelmetlen beszélgetésekbe bocsátkoznom...",
                          "Még több kérdés? Mi lenne, ha inkább üzletet kötnénk?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam...", "Jelenleg nincs mirôl beszélnem."), "Igen, így van. Megpróbáltam... Míg a boltban...",
                      "Igen, ez a harmadik kérdés...", "Hm, talán megegyezhetünk...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

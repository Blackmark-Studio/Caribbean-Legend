// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("A "+ GetCityName(npchar.city) +" összes pletykája az Ön rendelkezésére áll. Mit szeretnél megtudni?",
                          "Éppen errôl beszéltünk. Biztos elfelejtette...", "Ma már harmadszor beszélsz valamilyen kérdésrôl...",
                          "Ismétled ugyanazt, mint egy papagáj...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Tudod, " + NPChar.name + ", talán legközelebb.", "Rendben, valamiért elfelejtettem...",
                      "Igen, ez tényleg a harmadik alkalom...", "Igen...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
 		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

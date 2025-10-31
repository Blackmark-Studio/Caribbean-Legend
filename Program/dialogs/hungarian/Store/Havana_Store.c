// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Gyerünk, mit akarsz?",
                          "Épp errôl beszéltünk. Biztos elfelejtetted...", "Ma már harmadszor beszélsz valami kérdésrôl...",
                          "Figyelj, ez egy bolt. Az emberek itt vásárolnak. Ne zavarjon!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Tudod, " + NPChar.name + ", talán legközelebb.", "Rendben, valamiért elfelejtettem...",
                      "Igen, ez tényleg a harmadik alkalom...", "Hm, nem fogom...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "Figyeljen, járt valaha egy Joachim Merriman nevû férfi az üzletében? Egy portugál, középkorú szenior, bajusszal, császári szakállal és szúrós szemekkel? Talán vásárolt valamit?";
				link.l1.go = "caleuche";
			}
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "Nem, egyik vásárlóm sem hasonlít az ön által leírtakra. És még soha nem hallottam ezt a nevet. Sajnálom, nem tudok többet segíteni.";
			link.l1 = "Értem, értem. Kár. Nos, folytatom a keresést...";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

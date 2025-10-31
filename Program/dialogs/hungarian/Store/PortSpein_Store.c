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
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Mondd, mond neked valamit a Juan név?";
				link.l1.go = "Consumption";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "1654 áprilisában egy fregatt kötött ki a kikötôjében Miguel Dichoso kapitány parancsnoksága alatt, miután mi eltûnt. Ismerôs a neve? Lehetséges, hogy vásárolt önöktôl árut, vagy mondott valamit...";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "Ó, hagyja már abba, kapitány! Éppen ma volt két Juan a boltomban, tegnap pedig egy másik. Mi, mindegyikre emlékeznem kéne?";
			link.l1 = "Semmi. Elnézést a zavarásért...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
		
		case "guardoftruth":
			dialog.text = "Ó, kapitány, annyi fregatt és gálya jött és ment ki innen az idô alatt, Miguelek és Carlosok...";
			link.l1 = "Értem. Szóval nem tud segíteni...";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

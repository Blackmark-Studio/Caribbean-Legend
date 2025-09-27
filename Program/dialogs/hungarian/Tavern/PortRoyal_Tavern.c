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
			if (pchar.questTemp.Slavetrader == "FindRatJamaica")
            {
                link.l1 = "Nem tudja, hol találom Francois Gontier-t?";
                link.l1.go = "Jamaica_ratP_1";
            }
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
			{
				link.l1 = "Figyeljen, nem érkezett ide a városba egy alkimista, egy orvos? Olasz, harminc év körüli, a neve Gino Gvineili. Hallottál róla valamit?";
				link.l1.go = "guardoftruth";
			}
		break;

		case "Jamaica_ratP_1":
			dialog.text = NPCStringReactionRepeat("A leghalványabb fogalmam sincs. Még csak nem is hallottam ezt a nevet.", "Már kérdeztél errôl, és én válaszoltam neked.", "Mondtam, hogy már kérdeztél errôl a Gontierrôl.", "Figyelj, menj el, és ne zaklass engem! Teljesen elment az eszed?", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Nos, akkor tovább keresgélek.", "Hm, azt hiszem...", "Igen, persze, ezt már kérdeztem...", "Bocsánat, " + npchar.name + "...", npchar, Dialog.CurrentNode);
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("Nem, még nem. Vannak gyógynövényszakértôink és orvosaink, de ilyen nevûek nincsenek.","Most hallottam elôször ilyen furcsa nevet. Nem, még soha nem látogatott meg minket az az ember, akirôl beszél.","Nálunk egyáltalán nincsenek alkimisták. Orvosaink vannak, de ilyen furcsa nevûek nincsenek.");
			link.l1 = "Értem. Az nagy kár. Folytatom a keresést!";
			link.l1.go = "exit";
			npchar.quest.jino = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

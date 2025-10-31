// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Milyen kérdések?", "Mit akarsz?");
			link.l1 = RandPhraseSimple("Meggondoltam magam.'", "Most már nincs mit mondanom.");
		    link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Mondja, nem cseng ismerôsen a 'Juan' név?";
				link.l1.go = "Consumption";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "Figyelj, pajtás, egy fregatt Miguel Dichoso parancsnoksága alatt 1654 áprilisában itt kötött ki. Aznap eltûnt. Emlékszel rá?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Azt hiszi, hogy a "+NationNameGenitive(sti(NPChar.nation))+"titkosszolgálatának dolgozom?";
			link.l1 = "Nos... nem. Akkor viszlát.";
			link.l1.go = "exit";
			link.l2 = "Van még kérdésed?";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "Úgy nézek ki, mint a nyomozóiroda? Nem tudom, nem tudok semmit.";

            link.l1 = "Maga olyan zavarosfejû! Távozz.";
			link.l1.go = "exit";
			link.l2 = "Van még kérdésed?";
			link.l2.go = "new question";
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "Viccelsz velem? Minden gyarmaton kétszer egy tucat Juan van!";
			link.l1 = "Értem. Elnézést a zavarásért...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
		
		// Страж Истины
		case "guardoftruth":
			dialog.text = LinkRandPhrase("Gyerünk, kapitány! Azt hiszi, hogy emlékszem ilyen dolgokra?","Bocsásson meg, Senor, ebben nem tudok segíteni.","Senor, tényleg azt hiszi, hogy emlékszem ilyen ostobaságokra? Már így is elég gondom van.");
			link.l1 = LinkRandPhrase("Értem. Elnézést a zavarásért...","Milyen kár, viszlát.","Rendben, viszlát...");
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

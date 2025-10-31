// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = RandPhraseSimple("Milyen kérdések?", "Mit akarsz?");
			link.l1 = RandPhraseSimple("Meggondoltam magam.'", "Most már nincs mit mondanom.");
			link.l1.go = "exit";
			//Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Citcount") && !CheckAttribute(npchar, "quest.Sharlie"))
			{
				link.l1 = "Elnézést, "+GetAddress_FormToNPC(NPChar)+" meg tudná mondani, hol találom Michel de Monper-t? Úgy hallottam, hogy ebben a városban van.";
				link.l1.go = "Sharlie";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "findskiper" && !CheckAttribute(npchar, "quest.Sharlie1"))
			{
				link.l1 = "Figyelj, "+GetAddress_FormToNPC(NPChar)+", szeretnék kérdezni valamit... Keresek egy navigátort a hajómra, tudsz valakit?";
				link.l1.go = "Sharlie_1";
			}
			//Бремя гасконца
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
		
		//--> Бремя гасконца
		case "Sharlie":
			if (sti(pchar.questTemp.Sharlie.Citcount) == 3)
			{
				dialog.text = "Hmm... Gyanítom, hogy nemrég érkeztél ide, mivel bátran teszel fel ilyen kérdéseket... Azt tanácsolom, hogy hagyd abba, ha nem akarsz bajt. Beszélj az apáttal, ô talán segíthet neked 'az észhez térni'. A templomban találod meg.";
				link.l1 = "Értem...";
				link.l1.go = "exit";
				AddDialogExitQuest("Sharlie_SetBenua");
				DelLandQuestMark(characterFromId("FortFrance_Mayor"));
			}
			else
			{
				dialog.text = LinkRandPhrase("Nem, még nem hallottam róla.","Nem tudok segíteni, dolgom van.","Ki? Nem ismerôs, nem. Máris megyek.");
				link.l1 = "Értem...  Akkor én is megyek. ";
				link.l1.go = "exit";
				npchar.quest.Sharlie = "true";
			}
		break;
		
		case "Sharlie_1":
			dialog.text = LinkRandPhrase("Nem, nem ismerek egyetlen navigátort sem.","Dolgom van, és nem, kérdezzen meg valaki mást...","Sajnos nem tudok segíteni, nem ismerek senkit.");
			link.l1 = "Értem. Akkor majd máshol érdeklôdöm.";
			link.l1.go = "exit";
			npchar.quest.Sharlie1 = "true";
			npchar.dialog.currentnode = "first time";
		break;
		//<-- Бремя Гасконца
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

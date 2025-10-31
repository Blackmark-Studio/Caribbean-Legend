// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Milyen kérdései vannak?", "Miben segíthetek, " + GetAddress_Form(NPChar) + "?"), "Nemrég próbáltál feltenni nekem néhány kérdést, " + GetAddress_Form(NPChar) + "...", "Az egész nap folyamán ez a harmadik alkalom, hogy valamilyen kérdésrôl beszélsz...",
                          "További kérdések, gondolom?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam...", "Jelenleg nincs mirôl beszélnem."), "Umph, hová tûnt a memóriám...",
                      "Igen, ez tényleg a harmadik alkalom...", "Nem, milyen kérdéseket?...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// Сага
			if(CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "valet")
			{
				link.l1 = "Egy Valet nevû embert keresek. Ismeri ôt?";
				link.l1.go = "valet_1";
				link.l2 = "Egy 'Marlin nevû polák kapitányt keresek'. Meg tudná mondani, hogy hol találom?";
				link.l2.go = "valet_2";
			}
		break;
		
		case "valet_1":
			dialog.text = NPCStringReactionRepeat("Nem, nem tudom, haver. Szóval nem tudok segíteni.", "Már mondtam, hogy nem tudom!", "Részeg vagy, vagy csak szórakozol?", "Hagyj békén!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Értem. Kár...", "Ez nagyon rossz. Azt hittem, hogy emlékezni fogsz...", "Józan vagyok! Csak kitartó vagyok...", "Hm...", npchar, Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;
		
		case "valet_2":
			dialog.text = NPCStringReactionRepeat("Á, Mr. David Fackman! Egy házat bérel nem messze a hajógyártól. Keresse ott.", "Az imént válaszoltam. Hogy hallgattál rám?", "Részeg vagy, vagy csak szórakozol?", "Hagyj békén!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Köszönöm!", "Igen. Sajnálom. Sajnálom.", "Józan vagyok! Csak kitartó vagyok...", "Hm...", npchar, Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

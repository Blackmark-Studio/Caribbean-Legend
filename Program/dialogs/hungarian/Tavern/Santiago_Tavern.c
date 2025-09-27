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
			// Jason Долго и счастливо
			if (CheckAttribute(pchar, "questTemp.LongHappy.Santiago"))
			{
				link.l1 = "Úgy hallottam, hogy a szentatyák egy francia kolóniáról érkeztek ide valami küldöttséggel, hogy megállapodjanak valamiben? Valószínûleg fogolycserérôl a martinique-i vérfürdô után?";
				link.l1.go = "LH_tavern";
			}
		break;
		
		// Jason Долго и счастливо
		case "LH_tavern":
			dialog.text = "Nem senor, ezt a történetet már régen elintézték, papok nélkül. Látja, ön teljesen pálma alatt él, hiszen nem hallotta, hogy X. Innocentus pápa Mazarin bíborossal végül megegyezett. Európa a maga háborúival egy dolog, de minden kereszténynek együtt kell harcolnia a pogány sötétség ellen a világ végén\nÉs igen, békanyalók jöttek hozzánk. De csak nem egyeztek meg semmiben - tisztelt vendégeink egy kormányzói kúriában ülnek, ôrség alatt, kávét isznak és melegednek. Már majdnem egy hónapja! Az emberek pletykáltak, hosszasan beszélgettek és megszokták - nézd, a francia apát úr esténként imaórát tart a templomban. Majdnem olyan, mint egy látványosság ahah!";
			link.l1 = "Érdekes! Meg kellene néznem azt a franciát, legalább viccesebb, mint egy bögre bámulása.";
			link.l1.go = "LH_tavern_1";
		break;
		
		case "LH_tavern_1":
			DialogExit();
			LongHappy_SantiagoBenua();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

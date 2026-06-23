// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Jakie pytania?","Czego chcesz?");
			link.l1 = RandPhraseSimple("Zmieniam zdanie.","Nie mam teraz nic do powiedzenia.");
		    link.l1.go = "exit";
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Czy sądzisz, że pracuję dla tajnej służby "+NationNameGenitive(int(NPChar.nation))+"?";
			link.l1 = "Cóż... nie. Żegnaj zatem.";
			link.l1.go = "exit";
			link.l2 = "Jakieś inne pytanie?";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "Wyglądam jak biuro śledcze? Nie wiem, nie mam pojęcia.";

            link.l1 = "Jesteś takim roztrzepanym głupcem! Znikaj.";
			link.l1.go = "exit";
			link.l2 = "Jakieś inne pytanie, zatem?";
			link.l2.go = "new question";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

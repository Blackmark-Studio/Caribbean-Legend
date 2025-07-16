// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Jakie to pytania?","Czego chcesz?");
			link.l1 = RandPhraseSimple("Zmieniłem zdanie.","Nie mam teraz nic do powiedzenia.");
		    link.l1.go = "exit";
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Czy myślisz, że pracuję dla tajnej służby "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "Cóż... nie. Żegnaj zatem.";
			link.l1.go = "exit";
			link.l2 = "Jakieś inne pytanie, zatem?";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "Czy wyglądam jak biuro śledcze? Nie wiem, nie wiem niczego.";

            link.l1 = "Jesteś takim bałamutem! Precz z tobą.";
			link.l1.go = "exit";
			link.l2 = "Masz jeszcze jakieś pytania?";
			link.l2.go = "new question";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

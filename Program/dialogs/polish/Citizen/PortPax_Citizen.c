// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Jakiego rodzaju pytania?","Czego chcesz?");
			link.l1 = RandPhraseSimple("Zmieniam zdanie.","Nie mam teraz nic do powiedzenia.");
		    link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "portprince" && !CheckAttribute(npchar, "quest.Guardoftruth"))
			{
				link.l1 = "Powiedz mi, "+GetAddress_FormToNPC(NPChar)+", czy galeon 'Santa Margarita' był tu niedawno? Może jako zdobyczna jednostka korsarza?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Czy myślisz, że pracuję dla tajnej służby "+NationNameGenitive(int(NPChar.nation))+"?";
			link.l1 = "Cóż... nie. Żegnaj zatem.";
			link.l1.go = "exit";
			link.l2 = "Masz jeszcze jakieś pytania?";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "Czy wyglądam na biuro śledcze? Nie wiem, nie mam pojęcia.";

            link.l1 = "Jesteś takim bałaganiarzem! Precz.";
			link.l1.go = "exit";
			link.l2 = "Masz jeszcze jakieś pytania?";
			link.l2.go = "new question";
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("Nie, nie pamiętam żadnego galeonu o tej nazwie. Rzadko widujemy tu takie duże statki.","Co? Galeon? Tutaj? Nie mam pojęcia.","Nie, panie, ten statek nie cumował tu ostatnio, przynajmniej nie przypominam sobie, żeby tak się stało.");
			link.l1 = LinkRandPhrase("Dobrze...","Bardzo dobrze...","Widzę, szkoda...");
			link.l1.go = "exit";
			npchar.quest.Guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

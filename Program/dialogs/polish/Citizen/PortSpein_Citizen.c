// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Jakie to pytania?","Czego chcesz?");
			link.l1 = RandPhraseSimple("Zmieniam zdanie.","Nie mam teraz nic do powiedzenia.");
		    link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Czy imię 'Juan' coś ci mówi?";
				link.l1.go = "Consumption";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "Słuchaj, kamracie, fregata pod dowództwem Miguela Dichoso zacumowała w porcie tutaj, w kwietniu 1654 roku. Zniknął tego dnia. Czy pamiętasz coś na ten temat?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Czy myślisz, że pracuję dla tajnych służb "+NationNameGenitive(int(NPChar.nation))+"?";
			link.l1 = "Cóż... nie. Zatem żegnaj.";
			link.l1.go = "exit";
			link.l2 = "Jakieś inne pytanie, zatem?";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "Czy wyglądam jak biuro śledcze? Nie wiem, nie wiem nic.";

            link.l1 = "Jesteś takim bałaganiarzem! Precz.";
			link.l1.go = "exit";
			link.l2 = "Czy masz jeszcze jakieś pytanie?";
			link.l2.go = "new question";
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "Żartujesz sobie? W każdej kolonii jest tuzin Juanów!";
			link.l1 = "Rozumiem. Przepraszam za kłopot...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
		
		// Страж Истины
		case "guardoftruth":
			dialog.text = LinkRandPhrase("Nie wygłupiaj się, kapitanie! Myślisz, że pamiętam takie rzeczy?","Wybacz mi, Senor, nie mogę ci w tym pomóc.","Senior, naprawdę myślisz, że pamiętam takie bzdury? Mam już wystarczająco dużo problemów.");
			link.l1 = LinkRandPhrase("Rozumiem. Przepraszam, że cię niepokoję...","Jaka szkoda, Żegnaj.","Dobrze, żegnaj...");
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

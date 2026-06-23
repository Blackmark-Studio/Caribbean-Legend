// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Jakie pytania?","Czego chcesz?");
			link.l1 = RandPhraseSimple("Zmieniam zdanie.","Nie mam teraz nic do powiedzenia.");
		    link.l1.go = "exit";
			//Jason, суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "baster" && !CheckAttribute(npchar, "quest.terrapin") && CheckAttribute(PChar, "questTemp.Terrapin.SJ_count"))
			{
				link.l1 = "Szukam pana Jonesa. Znasz go?";
				link.l1.go = "terrapin";
			}
		break;
		
		case "terrapin":
			if (int(pchar.questTemp.Terrapin.SJ_count) == 5 || rand(9) == 1) // 10% или числом
			{
				dialog.text = "Jest tu wielu Jonesów. Najbardziej znanym, o którym wiem, jest adiutant pod pułkownikiem Foxem, Benjamin Jones. Zwykle wita gości w kwaterze głównej pułku.";
				link.l1 = "Czy ma siostrę imieniem Molly?";
				link.l1.go = "terrapin_yes";
			}
			else
			{
				dialog.text = LinkRandPhrase("Którego Jonesa potrzebujesz? Znam co najmniej dwóch tuzinów z nich...","Mamy tu zbyt wielu Jonesów. Musisz być bardziej precyzyjny.","Jest tu wielu Jonesów, jak również Johnsonów czy Jacksonów. Musisz być bardziej konkretny, aye?");
				link.l1 = "Ma dorosłą siostrę o imieniu Molly. Słyszałem, że jest prawdziwą pięknością?";
				link.l1.go = "terrapin_no";
			}
			npchar.quest.terrapin = "true";
		break;
		
		case "terrapin_no":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Obawiam się, że nie mogę ci w tym pomóc.","Nie, nie znam go.","Phi! Jeśli Molly Jones, którą znam, to rzadkie piękno, to pułkownik Fox jest proboszczem."),LinkRandPhrase("Znam kilka Molly Jones. Jedna z nich ma brata, ale... to nie ta, której szukasz. Tylko człowiek, który żył z małpami, nazwałby ją 'rzadką pięknością'.","Przykro mi, ale wszyscy Jonesowie, których znam, nie mają sióstr.","Przepraszam, nie mogę ci pomóc. Zapytaj kogoś innego."));
			link.l1 = "Rozumiem. Przepraszam za kłopot.";
			link.l1.go = "exit";
			pchar.questTemp.Terrapin.SJ_count = int(pchar.questTemp.Terrapin.SJ_count)+1;
		break;
		
		case "terrapin_yes":
			dialog.text = "Tak, ale lepiej by było, gdyby była jego bratem. Ta chwatka prawdopodobnie nie znajdzie sobie męża z powodu swojej paskudnej gęby.";
			link.l1 = "Dziękuję.";
			link.l1.go = "terrapin_yes_1";
		break;
		
		case "terrapin_yes_1":
			DialogExit();
			AddQuestRecord("Terrapin", "2");
			pchar.questTemp.Terrapin.Benjamin = true;
			DeleteAttribute(pchar, "questTemp.Terrapin.SJ_count");
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Czy myślisz, że pracuję dla tajnej służby "+NationNameGenitive(int(NPChar.nation))+"?";
			link.l1 = "Cóż... nie. W takim razie żegnaj.";
			link.l1.go = "exit";
			link.l2 = "Masz jeszcze jakieś pytania?";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "Czy wyglądam jak biuro śledcze? Nie wiem, nic nie wiem.";

            link.l1 = "Ty niedołęgo! Precz stąd.";
			link.l1.go = "exit";
			link.l2 = "Może masz jeszcze jakieś pytanie?";
			link.l2.go = "new question";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

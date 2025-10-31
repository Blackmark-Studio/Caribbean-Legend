// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Jakiego rodzaju pytania?","Czego chcesz?");
			link.l1 = RandPhraseSimple("Zmieniam zdanie.","Nie mam teraz nic do powiedzenia.");
		    link.l1.go = "exit";
			
			// Rebbebion, "Путеводная звезда"
			if (CheckAttribute(pchar, "questTemp.PZ.TortugaCitizensAsk") && npchar.sex == "man")
			{
				link.l1 = "Czy przypadkiem nie znasz pewnego Joepa van der Vinka?";
				link.l1.go = "PZ_1";
			}
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
			dialog.text = "Czy wyglądam jak biuro śledcze? Nie wiem, nic nie wiem.";

            link.l1 = "Jesteś takim bałaganiarzem! Precz.";
			link.l1.go = "exit";
			link.l2 = "Masz jeszcze jakieś pytania?";
			link.l2.go = "new question";
		break;
		
		case "PZ_1":
			dialog.text = "Cóż, nie znam go osobiście, ale widuję go tu od czasu do czasu. Dlaczego pytasz?";
			link.l1 = "Zostałem przydzielony do dostarczenia mu przesyłki osobiście. Ale nikt nie chce o nim rozmawiać i nie wiem dlaczego. Czy ty wiesz? Czy to zły człowiek? Byłbym wdzięczny za uczciwą opinię.";
			link.l1.go = "PZ_2";
		break;
		
		case "PZ_2":
			dialog.text = "Znów, nie znamy się osobiście, więc wiem prawie nic. Ale ma bliskiego przyjaciela w mieście i często są widywani razem. Idź do niego - on zdecyduje, czy powiedzieć ci więcej, czy nie. Jego kumpel nazywa się Rober Martene.";
			link.l1 = "Rober Martene, mówisz... A kimże on jest? Gdzie mogę go znaleźć?";
			link.l1.go = "PZ_3";
		break;
		
		case "PZ_3":
			dialog.text = "Różne miejsca, ale teraz jest przy naszej latarni morskiej - naprawia swoją galeon po strasznej burzy. Nazywa się 'Voltigeur'.";
			link.l1 = "Dziękuję bardzo! Nie masz pojęcia, jak bardzo mi pomogłeś.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_CreateRobertMartin");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

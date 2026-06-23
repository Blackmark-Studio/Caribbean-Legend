// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = RandPhraseSimple("Jakie pytania?","Czego chcesz?");
			link.l1 = RandPhraseSimple("Zmieniam zdanie.","Nie mam teraz nic do powiedzenia.");
			link.l1.go = "exit";
			//Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Citcount") && !CheckAttribute(npchar, "quest.Sharlie"))
			{
				link.l1 = "Przepraszam, "+GetAddress_FormToNPC(NPChar)+"czy mógłbyś mi powiedzieć, gdzie mogę znaleźć Michela de Monpera? Słyszałem, że jest w tym mieście.";
				link.l1.go = "Sharlie";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "findskiper" && !CheckAttribute(npchar, "quest.Sharlie1"))
			{
				link.l1 = "Słuchaj, "+GetAddress_FormToNPC(NPChar)+", chcę cię o coś zapytać... Szukam nawigatora, który służyłby na moim statku, czy znasz kogoś takiego?";
				link.l1.go = "Sharlie_1";
			}
			//Бремя гасконца
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Czy sądzisz, że pracuję dla tajnej służby "+NationNameGenitive(int(NPChar.nation))+"?";
			link.l1 = "Cóż... nie. Żegnaj zatem.";
			link.l1.go = "exit";
			link.l2 = "Jakieś inne pytanie, zatem?";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "Czy wyglądam jak biuro śledcze? Nie wiem, nic nie wiem.";

            link.l1 = "Jesteś takim bałaganiarzem! Wynoś się.";
			link.l1.go = "exit";
			link.l2 = "Jakieś inne pytanie, zatem?";
			link.l2.go = "new question";
		break;
		
		//--> Бремя гасконца
		case "Sharlie":
			if (int(pchar.questTemp.Sharlie.Citcount) == 3)
			{
				dialog.text = "Hmm... Podejrzewam, że niedawno tu przybyłeś, skoro tak śmiało zadajesz takie pytania... Radzę ci przestać, jeśli nie chcesz kłopotów. Porozmawiaj z opatem, może ci pomóc 'oprzytomnieć'. Znajdziesz go w kościele.";
				link.l1 = "Widzę...";
				link.l1.go = "exit";
				AddDialogExitQuest("Sharlie_SetBenua");
				DelLandQuestMark(characterFromId("FortFrance_Mayor"));
			}
			else
			{
				dialog.text = LinkRandPhrase("Nie, nie słyszałem o nim.","Nie mogę ci pomóc, mam robotę do zrobienia.","Kto? Nie kojarzę, nie. Będę w drodze.");
				link.l1 = "Rozumiem...  W takim razie ruszam w drogę. ";
				link.l1.go = "exit";
				npchar.quest.Sharlie = "true";
			}
		break;
		
		case "Sharlie_1":
			dialog.text = LinkRandPhrase("Nie, nie znam żadnych nawigatorów.","Mam robotę do załatwienia i nie, zapytaj kogoś innego...","Niestety, nie mogę ci pomóc, nie znam nikogo.");
			link.l1 = "Rozumiem. W takim razie zapytam gdzie indziej.";
			link.l1.go = "exit";
			npchar.quest.Sharlie1 = "true";
			npchar.dialog.currentnode = "first time";
		break;
		//<-- Бремя Гасконца
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

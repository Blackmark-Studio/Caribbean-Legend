// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Czego chcesz? Pytaj śmiało.","Słucham cię, jakie jest pytanie?"),"To już drugi raz, gdy próbujesz zapytać...","To już trzeci raz, kiedy próbujesz zapytać...","Kiedy to się skończy?! Jestem zajętym człowiekiem, pracuję nad sprawami kolonii, a ty ciągle mnie niepokoisz!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie...","Nie teraz. Złe miejsce i czas"),"Prawda... Ale później, nie teraz...","Zapytałbym... Ale trochę później...","Przykro mi, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Jason Дороже золота
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "antigua")
			{
				link.l1 = "Wasza Ekscelencjo, chciałbym poinformować, że posiadam pewne informacje dotyczące zniknięcia Mercury'ego.";
                link.l1.go = "G_Girl";
			}
		break;
		
		// Jason Дороже золота
		case "G_Girl":
			dialog.text = "O co znowu chodzi z tymi informacjami?";
			link.l1 = "Brygantyna, Wasza Ekscelencjo. Transport poczty. Dokumenty o wielkim znaczeniu i tym podobne. Słyszałem o śledztwie i, oczywiście, jako lojalny przyjaciel Brytyjskiej Korony, chciałbym pomóc.";
			link.l1.go = "G_Girl_1";
		break;
		
		case "G_Girl_1":
			dialog.text = "Wspaniale! Baronet Cortney będzie zachwycony, mogąc Cię przyjąć! Natychmiast zorganizuję spotkanie.";
			link.l1 = "Dziękuję, Sir. Spieszę się i byłbym wdzięczny, gdyby to poszło szybko.";
			link.l1.go = "G_Girl_2";
		break;
		
		case "G_Girl_2":
			dialog.text = "Nie martw się, będziesz mieć cały czas na świecie. Straże! Pojmać go!";
			link.l1 = "Dziękuję... zaraz, co? To jakiś żart?!";
			link.l1.go = "G_Girl_3";
		break;
		
		case "G_Girl_3":
			DialogExit();
			GoldenGirl_AntiguaArest();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple(" Czego chcesz? Pytaj śmiało.","Słucham, jakie jest pytanie?"),"To już drugi raz, gdy próbujesz zapytać...","To już trzeci raz, kiedy próbujesz zapytać...","Kiedy to się skończy?! Jestem zajętym człowiekiem, pracuję nad sprawami kolonii, a ty wciąż mnie niepokojesz!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie, przepraszam.","Nie teraz. Nieodpowiednie miejsce i czas."),"Prawda, teraz nie mam nic do powiedzenia, przepraszam.","Zapytać, później.","Przykro mi, "+GetAddress_FormToNPC(NPChar)+"... ",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "Wasza Ekscelencjo, w kwietniu 1654 roku był fregata pod dowództwem Miguela Dichoso. Od tego czasu zniknął. Czy pamięta Wasza Ekscelencja coś o nim? Może odwiedził Waszą Ekscelencję, rozmawiał...";
				link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Tak, pamiętam tego człowieka. Ale nie pamiętam żadnych szczegółów na jego temat. Przyszedł tutaj, a potem po prostu odszedł. Nie mogę ci pomóc.";
			link.l1 = "Rozumiem. Przepraszam za kłopot.";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

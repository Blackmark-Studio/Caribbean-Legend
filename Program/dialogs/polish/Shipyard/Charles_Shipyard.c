// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie masz pytania?","Jak mogę ci pomóc?"),"Próbowałeś zadać mi pytanie jakiś czas temu...","Jeszcze nigdy nie spotkałem ludzi z taką ciekawością w mojej stoczni ani nigdzie indziej w tym mieście.","Co z tymi wszystkimi pytaniami? Moim zadaniem jest budować statki. Zajmijmy się tym.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie...","Nie mam teraz nic do omówienia."),"Umph, gdzież ta moja pamięć...","Hm, cóż...","Śmiało...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon 2016-1 Jason пиратскаЯ линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_2")
            {
                link.l1 = "Słuchaj, mistrzu, budujesz tu statki, prawda?.. I zmieniasz żagle również... czy kiedykolwiek myślałeś o... jakimś lepszym materiale na płótno żaglowe?";
                link.l1.go = "mtraxx";
			}
		break;
		
		// Addon 2016-1 Jason пиратскаЯ линейка
		case "mtraxx":
            dialog.text = "Pan mówi zagadkami, sir... Proszę mówić wprost, co pana tu sprowadza? Nic się nie martw, nie jestem jakimś biurokratą, a to nie jest urząd celny.";
			link.l1 = "Ach, cieszę się, że jesteśmy na tej samej stronie! Jedwabna tkanina żaglowa, panie. Jak rozumiem, nie ma lepszego materiału na żagle, jeśli zależy ci na prędkości.";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = "Nie tylko szybkość, ale także jej zdolność do żeglugi pod wiatr. Oferujesz do zakupu jedwab okrętowy? To naprawdę cenny ładunek. Ale jest przeszkoda: po prostu nie wiem, jak go wykorzystać w produkcji. Rozumiesz? Materiał taki jak ten wymaga bardzo specjalnego zestawu umiejętności i zdolności, których mi brakuje. Szczerze mówiąc, moja stocznia ma zupełnie inną specjalizację, gdybyś zaproponował mi jakieś liny z Carstwa Rosyjskiego, kupiłbym je wszystkie bez względu na cenę. Ciągle potrzebujemy lin, jednak jedwab okrętowy nie cieszy się tutaj popytem, przepraszam!";
			link.l1 = "Hm. Rozumiem. Dziękuję za poświęcony czas, mistrzu. Powodzenia!";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            DialogExit();
			AddQuestRecord("Roger_2", "4");
			pchar.questTemp.Mtraxx = "silk_3";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

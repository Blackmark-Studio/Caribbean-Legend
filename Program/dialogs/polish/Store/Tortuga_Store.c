// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie masz pytania?","Jak mogę ci pomóc?"),"Próbowałeś zadać mi jakieś pytanie niedawno...","Nikt nie zadawał takich pytań w sklepie na Tortudze od dłuższego czasu...","Pytania, pytania i jeszcze więcej pytań...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniam zdanie...","Nie mam teraz nic do omówienia."),"Umph, gdzież się podziała moja pamięć...","Dobrze, minęło już dużo czasu.","Yeeeeszcze pytania, tak...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "tortuga2")
			{
				link.l1 = "Słuchaj, muszę znaleźć Gaiusa Marchaisa. Powiedziano mi, że jest związany z korsarstwem i stał się przyzwoitym negocjatorem, zdobywając doskonały galeon od Hiszpanów. Czy zdarzyło mu się kupić od ciebie jakiś towar do handlu?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Gaius Marchais? Och tak, oczywiście, że go pamiętam! Ale niczego nie kupił. Oferował swój statek do frachtu. Akurat potrzebowałem statku z przestronną ładownią - dużą partię surowych skór.";
			link.l1 = "I jaki był punkt rozładunku?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Philipsburg, Saint Maarten.";
			link.l1 = "Dobrze. Dziękuję, bardzo mi pomogłeś!";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Zawsze do usług, kapitanie. Odwiedzaj mój sklep, kiedy tylko zechcesz!";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddQuestRecord("Guardoftruth", "10");
			pchar.questTemp.Guardoftruth = "maarten";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

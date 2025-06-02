// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie pytania?","Czego chcesz, "+GetAddress_Form(NPChar)+"?"),"Już próbowałeś zadać mi pytanie "+GetAddress_Form(NPChar)+"... ","Już trzeci raz dzisiaj mówisz o jakimś pytaniu...","Patrz, jeśli nie masz nic do powiedzenia o sprawach portowych, to nie zawracaj mi głowy swoimi pytaniami.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie.","Nie mam nic do powiedzenia."),"Nieważne.","Rzeczywiście, już trzeci raz...","Przykro mi, ale na razie nie interesują mnie sprawy portowe.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatHavana")
            {
                link.l1 = "Dzień dobry. Chciałbym dowiedzieć się o korwecie o nazwie '"+pchar.questTemp.Slavetrader.ShipName+"pod dowództwem Francois Gontiera.";
                link.l1.go = "Havana_ratP_1";
			}
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "Wybaczcie, czy człowiek o imieniu Joachim Merriman przybył do waszego portu? Średniego wieku señor, Portugalczyk, z wąsami, cesarską brodą i przenikliwymi oczami?";
				link.l1.go = "caleuche";
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_3" && !CheckAttribute(npchar, "quest.Mtraxx"))
			{
				link.l1 = "Interesuje mnie statek o nazwie 'Cantavro'. Szukam jego kapitana - Esberdo Cabanasa, w prywatnej sprawie. Czy mógłbyś mi pomóc?";
				link.l1.go = "mtraxx";
			}
		break;
		
		case "Havana_ratP_1":
			dialog.text = NPCStringReactionRepeat("Tak, był tutaj. Ale już poszedł. Zapytaj naszego karczmarza o niego, wynajął pokój na górze.","Już o to pytałeś i odpowiedziałem.","Powiadam ci, że już pytałeś o tego Gontiera..","Proszę cię, nie zawracaj mi głowy!","blokada",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Dzięki. Tak zrobię.","Hm, cóż ...","Tak, naprawdę zapytałem ...","Przepraszam, "+npchar.name+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "Nie mogę ci nic o nim powiedzieć. Nawet jeśli przybył, nigdy się nigdzie nie zarejestrował.";
			link.l1 = "Widzę. Taka szkoda... Dobrze, będę kontynuować swoje poszukiwania...";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx":
			dialog.text = "Zobaczmy... szkuner 'Cantavro' wypłynął dwa dni temu na patrol... jednak lokalizacja nie jest wymieniona. To wojenny statek, więc cel podróży znają tylko jego kapitan i komendant fortu. Sugerowałbym, byś porozmawiał bezpośrednio z komendantem, możesz go znaleźć w forcie, jeśli chcesz wiedzieć więcej. Niestety, to wszystko, co mogę dla ciebie zrobić.";
			link.l1 = "Widzę. Cóż, dziękuję za poświęcony czas...";
			link.l1.go = "exit";
			npchar.quest.Mtraxx = "true";
			AddQuestRecord("Roger_1", "5");
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId("Havana_tavernkeeper"), "questmarkmain");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

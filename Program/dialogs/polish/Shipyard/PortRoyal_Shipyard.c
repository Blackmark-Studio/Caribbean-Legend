// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie masz pytania?","Jak mogę ci pomóc?"),"Próbowałeś zadać mi pytanie jakiś czas temu...","Jeszcze nigdy nie spotkałem ludzi z taką ciekawością w mojej stoczni ani nigdzie indziej w tym mieście.","Co z tymi wszystkimi pytaniami? Moja praca to budowanie statków. Zajmijmy się tym.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie...","W tej chwili nie mam nic do omówienia."),"Ech, gdzież to moja pamięć się podziała...","Hm, cóż...","Śmiało...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon 2016-1 Jason пиратскаЯ линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx"))
            {
				if (pchar.questTemp.Mtraxx == "silk_2" || pchar.questTemp.Mtraxx == "silk_3")
				{
					link.l1 = "Słyszałem, że ta stocznia zajmuje się poprawą szybkości żeglugi statku. Wymaga to jedwabnego żaglowca, który jest bardzo rzadki. Chciałbyś... porozmawiać o tym?";
					link.l1.go = "mtraxx";
				}
			}
			if (CheckAttribute(npchar, "quest.upgradeship")) {
				link.l2 = "Jestem od panny MacArthur, w sprawie...";
				link.l2.go = "helen_upgradeship";
			}
			
			if (CheckAttribute(npchar, "quest.upgradeship.money") && HelenCanUpgrade()) {
				link.l2 = "Rozpocznij remont statku!";
				link.l2.go = "helen_upgradeship_money";
			}
		break;
		
		// Addon 2016-1 Jason пиратскаЯ линейка
		case "mtraxx":
            dialog.text = "Czy mógłbyś być bardziej precyzyjny, młodzieńcze? Co dokładnie cię tutaj sprowadza? Jeśli chcesz ulepszyć swój statek - przejdźmy od razu do interesów.";
			link.l1 = "Nie do końca. Rodzaj usług, które wykonujesz, wymaga towarów, które nie są swobodnie dostępne w sklepie. Chciałbym zaoferować ci ten sam rodzaj materiałów, których możesz potrzebować.";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = "Otóż to... Hmm... Czy wiesz, że tylko władze tej kolonii mogą zajmować się takimi strategicznymi towarami? Możesz dostarczyć własny jedwab, abym mógł pracować nad ulepszeniem twojego statku, jednak sprzedaż jest surowo zabroniona. Podobnie jak kupowanie go ode mnie - takie działania będą surowo karane grzywną.";
			link.l1 = "Cóż, to nie jest sklep, ani urząd celny...";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "Pozyskuję całe jedwabne płótno żaglowe bezpośrednio od moich klientów lub kupuję ograniczone ilości za specjalnym pozwoleniem gubernatora. Jeśli nie masz więcej pytań, proszę, pozwól mi wrócić do mojej pracy.";
			link.l1 = "Hmm... Bardzo dobrze. Miłego dnia, mistrzu.";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            DialogExit();
			AddQuestRecord("Roger_2", "5");
			pchar.questTemp.Mtraxx = "silk_4";
		break;
		
		case "helen_upgradeship":
			dialog.text = "Oh, I know! Lucky you, Captain. Is it about a complete overhaul of the ship? We'll take care of everything; our shipyard is on par with those in Plymouth!";
			link.l1 = "Zakładam, że to nie będzie darmowa usługa?";
			link.l1.go = "helen_upgradeship_1";
		break;
		
		case "helen_upgradeship_1":
			dialog.text = "Oczywiście, Kapitanie, takie usługi nie mogą być darmowe, nawet dla Cromwella! Jednak dotrzymuję słowa i wezmę tylko pieniądze - nie będziesz musiał przemycać kontrabandy.";
			link.l1 = "Zrozumiałe. Ile to kosztuje?";
			link.l1.go = "helen_upgradeship_2";
		break;
		
		case "helen_upgradeship_2":
			dialog.text = "To zależy od wielkości twojego okrętu flagowego, Kapitanie. Okręt pierwszej rangi będzie cię kosztować pięć tysięcy dublonów, a piątej rangi - tylko tysiąc.";
			link.l1 = "Dobrze, przyjdę do ciebie, gdy podejmę decyzję.";
			link.l1.go = "exit";
			
			npchar.quest.upgradeship.money = true;
		break;
		
		case "helen_upgradeship_money":
			dialog.text = "Doskonale, teraz mam wszystko, czego potrzebuję. Zaczynam pracę.";
			link.l1 = "Czekam.";
			link.l1.go = "helen_upgradeship_money_1";
			
			iTemp = GetCharacterShipType(pchar);
			sld = GetRealShip(iTemp);
			iTemp = (7 - sti(sld.class)) * 1000;
			RemoveDublonsFromPCharTotal(iTemp);
		break;
		
		case "helen_upgradeship_money_1":
			AddTimeToCurrent(6, 30);
			dialog.text = "... Chyba to wszystko... Gwarantujemy jakość.";
			link.l1 = "Dzięki! Sprawdzę to.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenUpgradeShip2");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

bool HelenCanUpgrade() {
	int shipIndex = GetCharacterShipType(pchar);
	if (shipIndex == SHIP_NOTUSED) {
		return false;
	}
	
	sld = GetRealShip(shipIndex);
	if (sti(sld.class) == 7) {
		return false;
	}
	
	int cost = (7 - sti(sld.class)) * 1000;
	return (PCharDublonsTotal() >= cost);
}

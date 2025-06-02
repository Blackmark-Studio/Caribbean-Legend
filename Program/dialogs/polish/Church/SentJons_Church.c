// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakiego rodzaju pytania, "+GetSexPhrase("mój synu","moja córko")+"?","Pytaj śmiało, słucham..."),"Słucham, mów teraz, "+GetSexPhrase("mój synu","moja córko")+"...","Po raz trzeci, "+GetSexPhrase("mój synu","moja córko")+", pytaj, czego potrzebujesz.","Duchowny ma od groma pracy, "+GetSexPhrase("mój synu","moja córko")+" a ty mnie ewidentnie rozpraszasz...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie...","Nie w tej chwili, ojcze..."),"Nie mam nic do powiedzenia, przepraszam.","Zapytam, ale później. Wybacz mi, ojcze.","Przepraszam, święty ojcze...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
				// --> Тёмные воды исцеления
			if (CheckAttribute(pchar, "questTemp.DWH_pastor"))
			{
				link.l1 = "Ojcze święty, chcę porozmawiać o córce Thomasa Morrisona.";
				link.l1.go = "dwh_pastor_1";
			}
			if (CheckAttribute(pchar, "questTemp.DWH_pastor_PrinesDengi"))
			{
				link.l1 = "Ojcze święty, Thomas prosił, żebym przekazał, że przyjmie pokutę, poświęci się dobrym uczynkom i zapewni parafii nowy dzwon - bez względu na to, ile by go to nie kosztowało.";
				link.l1.go = "dwh_pastor_VD_5";
			}
			// <-- Тёмные воды исцеления
			break;

		// --> Тёмные воды исцеления
		case "dwh_pastor_1":
			dialog.text = "Mów, moje dziecko, słucham cię.";
			link.l1 = "Wiem, że jest ojciec przeciwny temu, by cyganka pomagała dziewczynce. Ale jak można zmuszać ojca do odrzucenia choćby najmniejszej szansy na uratowanie swojej córki? Jej metody mogą wydawać się wątpliwe, ale posiada wiedzę, która może pomóc.";
			link.l1.go = "dwh_pastor_2";
			DelLandQuestMark(npchar);
		break;

		case "dwh_pastor_2":
			dialog.text = "Mój synu, tylko Pan może uzdrowić dziewczynkę. Wiara w Jego opatrzność prowadzi nas przez próby. Jeśli Thomas będzie pilnie się modlił, postępował zgodnie ze słowem Bożym i hojnie wspierał kościół, Pan wysłucha jego modlitw i okaże miłosierdzie.";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				link.l1 = "(Wywołujący zaufanie) Ale przecież nawet ojciec musi przyznać, że Pan działa przez ludzi. Co, jeśli cyganka jest jedynie narzędziem w rękach Bożych? Co, jeśli Jego plan jest tak głęboki, że nam, zwykłym śmiertelnikom, nie dane jest go zrozumieć? Drogi Pańskie są niezbadane, czyż nie?";
				link.l1.go = "dwh_pastor_VD_1";
				notification("Wywołujący zaufanie", "Trustworthy");
			}
			else
			{
				link.l1 = "Zmusza ojciec ojca, by patrzył, jak jego córka powoli gaśnie, zamiast pozwolić mu spróbować ją uratować. Czy to jest miłosierdzie?";
				link.l1.go = "dwh_pastor_bez_VD_1";
				notification("Nie otwarta umiejętność", "Trustworthy");
			}
		break;

		case "dwh_pastor_VD_1":
			dialog.text = "Twoje słowa, Kapitanie, są rzeczywiście mądre. Jednak nie mogę pozwolić, aby herezja przeniknęła do samego serca naszej kongregacji i zachwiała wiarą jednego z jej najbardziej oddanych synów.";
			link.l1 = "Nic nie mogłoby bardziej zachwiać jego wiarą niż śmierć własnej córki. Jeśli pozwoli mu ojciec użyć wszelkich środków, nawet tych, które można nazwać grzechem, jego wiara nie osłabnie - przeciwnie, stanie się silniejsza niż przedtem.";
			link.l1.go = "dwh_pastor_VD_2";
		break;

		case "dwh_pastor_VD_2":
			dialog.text = "Ale... Jaki to będzie przykład dla pozostałych członków kongregacji?";
			link.l1 = "Przykład tego, że kościół nie karze ślepo, lecz prowadzi i kieruje ku prawdziwej pokucie. Czy Pismo nie uczy nas, że szczery żal i dobre uczynki mogą odkupić grzech? Hojny datek na rzecz skarbca kościelnego mógłby być pierwszym krokiem ku odkupieniu.";
			link.l1.go = "dwh_pastor_VD_3";
		break;
		
		case "dwh_pastor_VD_3":
			dialog.text = "Być może masz rację, Kapitanie. Jestem gotów dać Thomasowi tę szansę. Ale wiedz, że jeśli zejdzie z prawdziwej ścieżki i straci stałość swojej wiary, odpowiedzialność spadnie również na ciebie! Co do datków - kościół nie potrzebuje bogactwa, mamy wszystko, co niezbędne. Chociaż nasz dzwon został uszkodzony podczas hiszpańskiego ataku...";
			link.l1 = "Przekażę Thomasowi ojca słowa. Dziękuję za rozmowę, ojcze święty. Niech Bóg ojca strzeże.";
			link.l1.go = "dwh_pastor_VD_4";
		break;

		case "dwh_pastor_VD_4":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DWH_pastor");
			AddLandQuestMark(characterFromId("DWH_Tomas"), "questmarkmain");

			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_11";
		break;

		case "dwh_pastor_bez_VD_1":
			dialog.text = "To nie bezduszność, kapitanie, to wiara. Nie pozostawiamy losu dziewczynki przypadkowi, lecz oddajemy go w ręce Pana Boga. Jeśli Thomas będzie się modlił, wierzył i cierpliwie czekał w pokorze, jestem pewien, że Pan usłyszy nasze modlitwy i obdarzy ją uzdrowieniem.";
			link.l1 = "Przecież wiadomo, że nawet szlachta tej wyspy, w tym gubernator, korzystała z usług cyganki. A nikt z nich nie został ekskomunikowany. Dlaczego więc w przypadku Thomasa jesteście tacy surowi?";
			link.l1.go = "dwh_pastor_bez_VD_2";
		break;

		case "dwh_pastor_bez_VD_2":
			dialog.text = "Oczywiście, wiem o tym, mój syn. Ale oni to dusze zagubione, które nie poznały prawdziwego światła Pana. Thomas natomiast jest podporą naszej wspólnoty, jednym z najlepszych. Pozwolić złemu osłabić jego wiarę to wystawić cały Kościół na niebezpieczeństwo – a na taki ciężki grzech nie mogę sobie pozwolić.";
			link.l1 = "Czyli odrzuca pan nawet najmniejszą szansę? Czy to naprawdę droga sprawiedliwa?";
			link.l1.go = "dwh_pastor_bez_VD_3";
		break;

		case "dwh_pastor_bez_VD_3":
			dialog.text = "To, co nazywacie ocaleniem, może być prostą drogą do zguby. Mówię to z własnego doświadczenia. Kiedyś, wbrew mojej woli, taka uzdrowicielka leczyła moją siostrzenicę. Mała dziewczynka zmarła w męczarniach, a tylko Pan wie, czy rytuały czarownicy nie skazały jej duszy na wieczne cierpienie. Nie próbujcie mnie przekonywać - to na nic.";
			link.l1 = "Dobrze. Jeśli to pańska ostateczna odpowiedź, nie będę się spierać. Niech Pan cię strzeże.";
			link.l1.go = "dwh_pastor_bez_VD_4";
		break;
		
		case "dwh_pastor_bez_VD_4":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DWH_pastor");
			
			AddQuestRecord("DWH", "4");
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetCitizenType(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_6";
			ChangeCharacterAddressGroup(sld, "SentJons_town", "goto", "goto23");
			LAi_SetImmortal(sld, true);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "dwh_pastor_VD_5":
			dialog.text = "Doskonale, synu mój. Nowy dzwon będzie symbolem jego oddania Panu i kościołowi. Niech czyni, co konieczne, ale niech pamięta, że oko Wszechmogącego czuwa nad każdym jego uczynkiem, i nie ma na tym świecie miejsca ukrytego przed Jego wzrokiem.";
			link.l1 = "Niech tak będzie, ojcze święty. Do widzenia.";
			link.l1.go = "dwh_pastor_VD_6";
			DelLandQuestMark(npchar);
		break;
		
		case "dwh_pastor_VD_6":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DWH_pastor_PrinesDengi");
			AddLandQuestMark(characterFromId("DWH_Tomas"), "questmarkmain");
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_15";
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_houseS3", "barmen", "bar1");
			DelLandQuestMark(sld);
		break;
		// <-- Тёмные воды исцеления
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

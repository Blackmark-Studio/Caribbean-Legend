// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie pytania, "+GetSexPhrase("mój synu","moja córko")+"?","Pytania powiadasz? Słucham..."),"Słucham, mów teraz, "+GetSexPhrase("mój synu","moja córko")+"...","Po raz trzeci, "+GetSexPhrase("mój synu","moja córko")+"Proś o to, czego potrzebujesz.","Duchowny ma od groma pracy, "+GetSexPhrase("mój synu","moja córko")+" a ty mnie ewidentnie rozpraszasz...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Już nieważne...","Nie w tej chwili, ojcze..."),"Nie mam nic do powiedzenia, przepraszam.","Zapytam, ale później. Wybacz mi, ojcze.","Niech mi ksiądz wybaczy...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "havana")
			{
				ref sld = characterFromId("Villemstad_Priest");
				link.l1 = "Szczęść Boże, prosze księdza. Przybywam od ojca "+sld.name+" z kościoła w Willemstad. Powiedziałeś mu o dziwnych zjawiskach w jaskini na Kubie.";
				link.l1.go = "caleuche";
				DelLandQuestMark(npchar);
			}
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "havana1")
			{
				link.l1 = "Odwiedziłem jaskinię w dżungli, ojcze.";
				link.l1.go = "caleuche_4";
				DelLandQuestMark(npchar);
			}
		break;
		
		case "caleuche":
			dialog.text = "Dzięki Bogu, że ktoś się tym zainteresował! Gdy tylko plotki o żywych trupach dotarły do mych uszu, natychmiast powiadomiłem Jego Wielebność Ojca Vincento, inkwizytora z Santiago. Obiecał to zbadać, ale jak dotąd nie podjęto żadnych działań! Obawiam się, że Jego Wielebność ma ważniejsze sprawy do załatwienia...";
			link.l1 = "Sam się tym zajmę. Poza tym, wszystkie te plotki to nic innego, jak brednie pijanych łowców - dlatego Inkwizycja nie traktuje ich poważnie. Wyruszę do dżungli, by zobaczyć to na własne oczy.";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Zapewniam cię, mój synu, że to prawda. Człowiek, który opowiedział mi o chodzących umarłych, jest godny mojego zaufania.";
			link.l1 = "Dobrze więc, zatem przygotuję się do bitwy. Jeśli nieczyste stworzenia rzeczywiście zadomowiły się w jaskini, wypędzę je z tego świata.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "Idź z błogosławieństwem Pana naszego - Jezusa Chrystusa, mój synu! Weź ten poświęcony amulet. Pomoże ci w twoim zadaniu. A teraz idź i zniszcz pomioty zła!";
			link.l1 = "Zło zostanie wyplenione, ojcze "+npchar.name+"! Gdy skończę, natychmiast do ciebie wrócę.";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			DialogExit();
			AddQuestRecord("Caleuche", "27");
			pchar.questTemp.Caleuche = "cave";
			Log_Info("Otrzymano kościelny amulet");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "amulet_7"); 
			if (GetCharacterIndex("cavehunter") != -1)
			{
				sld = characterFromId("cavehunter");
				sld.dialog.currentnode = "cavehunter_5";
				LAi_SetGuardianType(sld);
				sld.protector = true;
				LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
				AddLandQuestMark(sld, "questmarkmain");
			}
			LocatorReloadEnterDisable("Cuba_Jungle_07", "reload2_back", false);
			pchar.quest.Caleuche_cuba_caveentrance.win_condition.l1 = "location";
			pchar.quest.Caleuche_cuba_caveentrance.win_condition.l1.location = "Cuba_CaveEntrance";
			pchar.quest.Caleuche_cuba_caveentrance.function = "Caleuche_CubaCaveEntrance";
		break;
		
		case "caleuche_4":
			dialog.text = "Co widziałeś, mój synu? Czy nasze obawy były bezpodstawne?";
			link.l1 = "Obawiam się, że nie, ojcze "+npchar.name+". Jaskinia była pełna nieumarłych, ale z Boską pomocą wyszedłem zwycięsko. Nie będą już nikomu przeszkadzać.";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "Chwała Panu naszemu! Zło zostało przegnane i dobro zatriumfowało po raz kolejny! Zaprawde powiadam ci, iż Bóg wziął cie w godzine próby, w swą opieke. Proszę, pozwól mi wyrazić swą najgłębszą wdzięczność w imieniu całej parafii Hawany. Przyjmij te święte amulety jako wyraz wdzięczności. Z pewnością okażą się przydatne w twoich niebezpiecznych podróżach.";
			link.l1 = "Bóg zapłać, Ojcze "+npchar.name+".";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			Log_Info("Otrzymano kościelne amulety");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "amulet_3"); 
			GiveItem2Character(pchar, "amulet_9"); 
			GiveItem2Character(pchar, "obereg_7"); 
			GiveItem2Character(pchar, "obereg_11"); 
			dialog.text = "Dodatkowo upewnię się, że zarówno prosty lud, jak i szlachta dowiedzą się o twym bohaterskim czynie, a ja będę modlić się za ciebie dniem i nocą nieustannie.";
			link.l1 = "Dziękuję, ojcze. Mam jeszcze jedno pytanie jak to nie problem.";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "Pytaj śmiało, mój synu.";
			link.l1 = "Powiedz mi, ojcze "+npchar.name+", czy człowiek o imieniu Joachim Merriman przybył ostatnio do waszego miasta? Wiekowy facet, Portugalczyk z wąsem, cesarską brodą i przeszywającymi oczami?";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			sld = characterFromId("Villemstad_Priest");
			dialog.text = "Przepraszam, ale ani imię, ani opis niewiele mi mówią. Kim jest ten człowiek?";
			link.l1 = "Merriman jest czarownikiem. Inkwizycja ściga go od bardzo dawna. Ojciec "+sld.name+" i ja podejrzewamy, że pojawienie się żywych trupów na Kubie jest jego dziełem. Niedawno mieszkał w Willemstad, a potem nagle zniknął. Wkrótce po tym kobieta, która go przyjmowała, zamieniła się w chodzący szkielet.";
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = "Co za koszmar! Natychmiast poinformuję inkwizytorów, a nawet samego ojca Vincento! Musi wiedzieć, co tu się dzieje! Powiedz mi, mój synu, czy myślisz, że ludzie, którzy zaginęli w dżungli...?";
			link.l1 = "Rzeczywiście, jestem niemal pewien, że te żywe trupy w jaskini to byli wasi dawni obywatele. Chcę wytropić tego Portugalczyka na Kubie i sprowadzić go do porządku! Ten łotr zdobył starą pogańską relikwię - jadeitową czaszkę Yum Cimil. Obawiam się, że z artefaktem i indiańskimi czarami, Merriman narobi jeszcze więcej kłopotów, jeśli nikt go wkrótce nie powstrzyma.";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			dialog.text = "Wierzysz, że nieumarli znowu powstaną?";
			link.l1 = "Z całą pewnością. Nie jestem pewien, co nim kieruje, ale z pewnością jego aspiracje dalekie są od bycia cnotliwymi.";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			dialog.text = "Niech Wszechmogący zmiłuje się nad nami! Szukaj go, mój synu! Pozwalam ci podjąć wszelkie środki przeciwko niemu w imię naszego Świętego Kościoła! Natychmiast wyślę posłańca do Santiago z raportem dla Ojca Vincento.";
			link.l1 = "Zrób to. Żegnaj, ojcze "+npchar.name+".";
			link.l1.go = "caleuche_12";
		break;
		
		case "caleuche_12":
			DialogExit();
			AddQuestRecord("Caleuche", "29");
			pchar.questTemp.Caleuche = "graveyard";
			AddCharacterMaxHealth(pchar, 3);
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			ChangeCharacterNationReputation(pchar, SPAIN, 10);
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddLandQuestMark(characterFromId("Havana_CemeteryMan"), "questmarkmain");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

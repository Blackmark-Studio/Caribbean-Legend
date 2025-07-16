// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Mów, słucham";
			link.l1 = "Pomyliłem się. Żegnaj.";
			link.l1.go = "Exit";
			// Калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.Bandos") && pchar.questTemp.Caleuche.Bandos == "start")
			{
				link.l1 = "Słyszałem o gangu złodziei i rabusiów działających w okolicach Belize i w samym mieście.";
				link.l1.go = "caleuche";
			}
			if (CheckAttribute(pchar, "questTemp.Caleuche.Bandos") && pchar.questTemp.Caleuche.Bandos == "know" && CheckAttribute(pchar, "questTemp.Caleuche.belizbandos") && GetQuestPastDayParam("questTemp.Caleuche.belizbandos") < 3)
			{
				link.l1 = "Mogę ci dać informacje o tej bandzie.";
				link.l1.go = "caleuche_3";
			}
			if (CheckAttribute(pchar, "questTemp.Caleuche.BelizRegard"))
			{
				link.l1 = "Jakie wieści o bandzie? Czy pojmałeś ich w jaskini?";
				link.l1.go = "caleuche_7";
			}
			// Путеводная звезда ==>
			if (CheckAttribute(pchar, "questTemp.PZ_Beliz_Komendant"))
			{
				link.l1 = "Całe miasto zdaje się świętować pojmanie pirata. Czy możesz mi powiedzieć o tym więcej?";
				link.l1.go = "PZ_Beliz_Komendant_1";
				DeleteAttribute(pchar, "questTemp.PZ_Beliz_Komendant");
			}
			// <== Путеводная звезда
		break;
		
		// Путеводная звезда ==>
		case "PZ_Beliz_Komendant_1":
			dialog.text = "Chętnie! To nie jest zwykły pirat - to łajdak, Matthew Lutter.";
			link.l1 = "W końcu każdemu wyczerpuje się szczęście.";
			link.l1.go = "PZ_Beliz_Komendant_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Beliz_Komendant_2":
			dialog.text = "Nie jesteś Anglikiem i nie wyglądasz na kupca, więc rozumiem, dlaczego nie jesteś tak podekscytowany. Lutter terroryzował te wody przez lata, atakując zarówno nas, jak i Hiszpanów, ale częściej nas. Zawsze udawało mu się unikać naszych patroli przybrzeżnych, żeglując na swojej korwecie, Mewie, która kiedyś była najszybszym statkiem w Archipelagu. Jak udało mu się dowodzić takim okrętem wojennym, tylko Bóg wie.";
			link.l1 = "Więc to prawda, że przegrał z kupcem? Na korwecie? Brzmi niewiarygodnie.";
			link.l1.go = "PZ_Beliz_Komendant_3";
		break;
		
		case "PZ_Beliz_Komendant_3":
			dialog.text = "Choć brzmi to dziwnie, to prawda. Kupiec, i to Hiszpan! Nasza marynarka mogłaby się od niego czegoś nauczyć. Kapitan Sotta, zdając sobie sprawę, że nie ma ucieczki, przygotował się do bitwy...";
			link.l1 = "Dość niezwykły typ, ten Sotta.";
			link.l1.go = "PZ_Beliz_Komendant_4";
		break;
		
		case "PZ_Beliz_Komendant_4":
			dialog.text = "Być może. Przerobił swój statek, aby pomieścić jak najwięcej ładunku, co uniemożliwiło ucieczkę. Wiedząc, że piraci chcą jego ładunek, udawał dryfującego. A potem...";
			link.l1 = "...podniósł żagle w odpowiednim momencie?";
			link.l1.go = "PZ_Beliz_Komendant_5";
			if (!CharacterIsHere("Longway"))
			{
				sld = CharacterFromID("Longway");
				ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
			}
		break;
		
		case "PZ_Beliz_Komendant_5":
			dialog.text = "Ha! Nie, wystrzelił salwę kartaczy z bliskiej odległości, gdy Lutter się zbliżał, a potem sam wszedł na pokład pirata! Gdy dowiedział się, kim jest Lutter, przekazał go nam. Prawdziwy bohater, człowiek honoru!";
			link.l1 = "Nie tylko honor go napędzał - musiała być jakaś nagroda za złapanie Gaduły.";
			link.l1.go = "PZ_Beliz_Komendant_6";
		break;
		
		case "PZ_Beliz_Komendant_6":
			dialog.text = "Czasami zysk idzie w parze z dobrymi intencjami. Ale tak, został hojnie wynagrodzony. Jego Ekscelencja obdarzył go drogimi towarami jako wyraz wdzięczności naszego miasta, zanim odpłynął.";
			link.l1 = "Żałuję, że go nie spotkałem - chętnie uścisnąłbym mu dłoń. Powiedz mi...";
			link.l1.go = "PZ_Beliz_Komendant_7";
		break;
		
		case "PZ_Beliz_Komendant_7":
			StartInstantDialog("Longway", "PZ_Beliz_Komendant_8", "Quest\CompanionQuests\Longway.c");
		break;
		// <== Путеводная звезда
		
		// Калеуче
		case "caleuche":
			dialog.text = "Twoje źródło mówiło prawdę. Ci bandyci stali się dla nas prawdziwym bólem w tyłku. Chcesz nam coś o nich powiedzieć?";
			link.l1 = "Poza tym, że ukradli mi jedną ważną rzecz - właściwie nic. Miałem nadzieję, że będziesz w stanie powiedzieć mi coś o nich. Może, któryś z nich został złapany i jest teraz gotów zeznawać...";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Przykro mi, że cię rozczarowuję, kapitanie, ale nie mam o nich żadnych informacji. Wiem tylko, że ukrywają się gdzieś w dżungli i mają wspólników w mieście, to wszystko. Teraz, jeśli dowiesz się o nich czegoś nowego, proszę, powiedz mi natychmiast.";
			link.l1 = "Dobrze, oficerze. Zrobię to.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			DialogExit();
			AddQuestRecord("Caleuche", "10");
			pchar.questTemp.Caleuche.Bandos = "seek";
		break;
		
		case "caleuche_3":
			string sTime;
			if (GetQuestPastDayParam("questTemp.Caleuche.belizbandos") == 0) sTime = "in three days";
			if (GetQuestPastDayParam("questTemp.Caleuche.belizbandos") == 1) sTime = "on the day after tomorrow";
			if (GetQuestPastDayParam("questTemp.Caleuche.belizbandos") == 2) sTime = "tomorrow";
			dialog.text = "Serio, kapitanie? Mów, zamieniam się w słuch.";
			link.l1 = "Znalazłem jednego z ich informatorów w mieście. Powiedział mi, że ich banda szykuje się do ataku na statek, który ma przybyć do zatoki Chetumal. Łotry zbierają się "+sTime+" nocą przy jaskini niedaleko Belize. Aby tam dotrzeć, wystarczy skręcić w lewo na rozwidleniu w dżungli.";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "W jaskini? Świetna wiadomość. Rozkażę przygotować zasadzkę na tych łotrów. Jeśli masz rację i twój informator mówił prawdę, złapiemy tych drani, a wtedy zwrócę się do gubernatora o nagrodę dla ciebie.";
			link.l1 = "Dzięki! Przyjdę do ciebie, gdy to się skończy.";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "W porządku. Dobrze.";
			link.l1 = "Do zobaczenia wkrótce, oficerze.";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			DialogExit();
			AddQuestRecord("Caleuche", "15");
			pchar.questTemp.Caleuche.Bandos = "comendant";
			pchar.questTemp.Caleuche.BelizChance = hrand(3);
			SetFunctionTimerCondition("Caleuche_BelizRegard", 0, 0, 3, false); // таймер
		break;
		
		case "caleuche_7":
			if (sti(pchar.questTemp.Caleuche.BelizChance) < 3)
			{
				dialog.text = "Przygotowaliśmy gorące powitanie dla łajdaków, ha-ha-ha! Gdybyś tylko mógł zobaczyć ich twarze! Złapaliśmy wszystkich, w tym przywódcę! Niektórzy próbowali stawiać opór, ale zostali wyeliminowani przez naszych dzielnych żołnierzy.";
				link.l1 = "Doskonale wieści, oficerze! Teraz obywatele Belize wreszcie mogą spać spokojnie.";
				link.l1.go = "caleuche_12";
			}
			else
			{
				dialog.text = "Hmm... Moi żołnierze czekali na nich przy jaskini przez całą noc, ale nikt się nie pojawił. Sierżant był naprawdę wściekły. Dobrze, że jeszcze cię nie złapał.";
				link.l1 = "Cholera jasna! To po prostu niemożliwe! W której jaskini urządziłeś zasadzkę? Są dwie!";
				link.l1.go = "caleuche_8";
			}
		break;
		
		case "caleuche_8":
			dialog.text = "Gdzie mi powiedziałeś. Po prawej stronie na rozwidleniu...";
			link.l1 = "TO TEN PO LEWEJ! Na lewo od rozwidlenia, wy imbecyle!";
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = "Ale doskonale pamiętam, że powiedziałeś 'na prawo'.";
			link.l1 = "O mój Panie! Na lewo! Mówiłem, NA! LEWO! Pozwoliłeś im uciec, i to była twoja wina!";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			AddQuestRecord("Caleuche", "16");
			dialog.text = "To musiałeś coś mamrotać pod nosem. Wiesz, że słuch mam całkiem dobry.";
			link.l1 = "Dobrze, oficerze, nie będę się kłócił. Chciałem ci pomóc, ale nie można pomóc tym, którzy sami sobie nie potrafią pomóc. Żegnaj.";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Caleuche.BelizChance");
			DeleteAttribute(pchar, "questTemp.Caleuche.BelizRegard");
		break;
		
		case "caleuche_12":
			dialog.text = "Złożyłem raport gubernatorowi o twojej roli w eliminacji bandy. Bardzo wysoko ocenił twój wkład i upoważnił mnie do wręczenia ci nagrody: premię pieniężną i trofeum w postaci arkebuza.";
			link.l1 = "Dziękuję!";
			link.l1.go = "caleuche_13";
		break;
		
		case "caleuche_13":
			Log_Info("You have received a chest with doubloons");
			Log_Info("You have received an arquebus");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Caleuche", "17");
			GiveItem2Character(pchar, "chest"); 
			GiveItem2Character(pchar, "mushket3"); 
			dialog.text = "Dzięki za usługę, kapitanie! Gdyby tylko wszyscy nasi obywatele byli tak sumienni jak ty, pokonalibyśmy przestępczość raz na zawsze już dawno temu! Powodzenia!";
			link.l1 = "Do widzenia, oficerze! Powodzenia w służbie!";
			link.l1.go = "caleuche_11";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			OfficersReaction("good");
			ChangeCharacterNationReputation(pchar, ENGLAND, 8);
			AddCharacterExpToSkill(pchar, "Leadership", 300);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 200);//скрытность
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

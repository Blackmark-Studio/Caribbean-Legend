// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie pytania, "+GetSexPhrase("mój synu","moja córko")+"?","Pytaj śmiało, słucham..."),"Słucham, mów teraz, "+GetSexPhrase("mój synu","moja córko")+"... ","Po raz trzeci, "+GetSexPhrase("mój synu","moja córko")+", zapytaj o to, czego potrzebujesz.","Duchowny ma od groma pracy, "+GetSexPhrase("mój synu","moja córko")+" a ty mnie ewidentnie rozpraszasz...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniam zdanie...","Nie w tej chwili, ojcze..."),"Nie mam nic do powiedzenia, przepraszam.","Zapytam, ale później. Wybacz mi, ojcze.","Przepraszam, święty ojcze...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "priest")
			{
				link.l1 = "Przepraszam, ojcze, jeden z duchownych Twojej parafii poprosił mnie o zbadanie domu, w którym Joachim Merriman wynajmował pokój...";
				link.l1.go = "caleuche";
			}
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "Więc? Czy byłeś tam, mój synu?";
			link.l1 = "Rzeczywiście, byłem. Ale szczerze mówiąc, lepiej by było, gdybym tam nie zaglądał. Zostałem zaatakowany przez szkieleta z ogromną siekierą w górnym pokoju. Udało mi się wyjść z tego zwycięsko, chociaż z pewnością nie było to łatwe.";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Panie, zmiłuj się nad naszymi duszami! Moje najgorsze obawy się spełniły!";
			link.l1 = "To nie wszystko, ojcze. Kiedy w końcu je powaliłem, zapiszczało i brzmiało jak kobieta. Kiedy przeszukałem kości, znalazłem trochę biżuterii, więc można bezpiecznie założyć, że to była zaginiona gospodyni.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "(przeżegnał się)... Biedna, niech Pan spocznie jej duszę...";
			link.l1 = "Wygląda na to, że Merriman jest rzeczywiście czarnoksiężnikiem. Nie mam pojęcia, jak można zmienić żywego człowieka w takie plugastwo.";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "Joachim Merriman jest bardzo przerażającym czarnoksiężnikiem, mój synu. Znałem go w Europie, ale wówczas nie był zdolny do czegoś takiego. Tutaj, na Karaibach, udało mu się zdobyć coś, co dało mu nadprzyrodzone moce.";
			link.l1 = "Znałeś Merrimana, ojcze?";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "That I did. Back then I was just a humble priest in one of Lisbon's parishes. Joachim Merriman was a wealthy nobleman, and at some point he became interested in old manuscripts and scrolls brought by sailors from distant lands. He also began to study alchemy, but after some time he went into seclusion.\nPeople saw flashes of light in his house; sometimes they could also smell something strange. Then they saw him in the cemetery at nights. Once they saw him digging out a fresh corpse and bringing it to his home. And when patience ran out, local father superior contacted the Inquisition.\nWhen the guards breached the door of Merriman's house, Joachim was not there - he had escaped through a secret passage. They found a lab in the basement, and even the seasoned soldiers were shocked and sickened by what they saw. Whole rotting and dismembered bodies, human and animal skeletons, strange things... Fear and hatred for Merriman was so significant that his house was demolished in an instant.\nMerriman disappeared without a trace. The Inquisition began to search for him, sentencing him in his absence to burn at a stake as a dangerous warlock. But they never found him. And now, after all these years, I saw him again on the streets of Willemstad.";
			link.l1 = "Czemu nie powiedziałeś inkwizytorom?";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "Synu mój, czyż nie wiesz, że nasz kościół jest w konflikcie z Inkwizycją? Wolałbym trzymać się z dala od Ojca Vincento i jego łobuzów.";
			link.l1 = "Rozumiem. Ojcze, myślę, że wiem, skąd Merriman czerpał swoją moc. Zdobył starożytny artefakt, jadeitową czaszkę Yum Cimila, starożytnego boga śmierci czczonego przez Indian z plemienia Chavin.";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "Hm, Merriman był znany z odprawiania czarodziejskich rytuałów i eksperymentów na zwłokach, więc to może być prawda. Dziękuję Bogu, że ten straszny człowiek opuścił Willemstad i że zniszczyłeś diabelskie ziarna, które próbował tu zasadzić. Jesteśmy ci bardzo wdzięczni, mój synu. Proszę, przyjmij te poświęcone przedmioty jako swoją nagrodę.";
			link.l1 = "Dziękuję, ojcze";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			Log_Info("You have received church amulets");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "amulet_2"); 
			GiveItem2Character(pchar, "amulet_6"); 
			GiveItem2Character(pchar, "amulet_8"); 
			GiveItem2Character(pchar, "amulet_10"); 
			ref sld = characterFromId("Havana_Priest");
			dialog.text = "Ale to nie był koniec naszych kłopotów, mój synu. Niedawno otrzymałem list od "+sld.name+", ojcze przełożony kościoła w Hawanie. Przynosi straszne wieści. W jaskini, w dżungli Kuby, myśliwi widzieli przerażające potworności, żywe trupy. A wszystko to jest bardziej niepokojące, biorąc pod uwagę fakt, że ostatnio ludzie znikali po wejściu do dżungli.";
			link.l1 = "Hmm...  czy sugerujesz, że to również robota Merrimana?";
			if (CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 30) link.l1.go = "caleuche_8_1";
			else link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			sld = characterFromId("Havana_Priest");
			dialog.text = "Nie wiem, co o tym myśleć, mój synu. Ale jeśli ten czarnoksiężnik stał się tak potężny, wszyscy mieszkańcy archipelagu są w wielkim niebezpieczeństwie. Tylko Bóg wie, co ten sługa diabła może mieć na myśli\nMam nadzieję, że Ojciec "+sld.name+" było błędne, ale mimo wszystko - proszę, udaj się do Hawany i z nim porozmawiaj. Przygotowałem dla ciebie licencję handlową, która jest ważna przez miesiąc. Dzięki niej będziesz mógł bez przeszkód wejść do portu Hawany.";
			link.l1 = "Dobrze, ojcze. Udaję się do Hawany.";
			link.l1.go = "caleuche_9";
			npchar.quest.givelicence = true;
		break;
		
		case "caleuche_8_1":
			sld = characterFromId("Havana_Priest");
			dialog.text = "Nie wiem, co myśleć, mój synu. Ale jeśli ten czarny czarownik stał się tak potężny, wszyscy mieszkańcy archipelagu są w wielkim niebezpieczeństwie. Tylko Bóg wie, co ten sługa diabłów może mieć na myśli.\nMam nadzieję, że ojciec "+sld.name+"było złe, ale nieważne - proszę cię, abyś udał się do Hawany i porozmawiał z nim.";
			link.l1 = "Oczywiście, Ojcze. Wyruszam do Hawany natychmiast.";
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = "Jestem rad, że jesteś prawdziwym synem Kościoła. Będę modlił się o twoje zdrowie i pomyślność dniem i nocą. Idź z moim błogosławieństwem. Niech Pan wzmocni cię w twojej walce przeciwko tym bezbożnym siłom.";
			link.l1 = "Dziękuję i żegnaj, Ojcze.";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			DialogExit();
			AddQuestRecord("Caleuche", "26");
			AddCharacterMaxHealth(pchar, 1);
			if (CheckAttribute(npchar, "quest.givelicence")) GiveNationLicence(HOLLAND, 30);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			ChangeCharacterNationReputation(pchar, HOLLAND, 5);
			AddCharacterExpToSkill(pchar, "Leadership", 300);
			pchar.questTemp.Caleuche = "havana";
			Caleuche_PrepareCubaGrot();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

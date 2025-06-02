void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i, iRnd, iRnd1;
	string sTemp, sGems;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "exit_1":
			AddDialogExitQuest("LandEnc_RapersTalk");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;
		
		case "exit":
			LAi_SetCitizenTypeNoGroup(NPChar);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "Begin_1":
			LAi_RemoveCheckMinHP(npchar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = RandPhraseSimple(""+GetSexPhrase("Kapitanie","Damo")+"! Proszę, litości! Uratuj mnie, błagam Cię!","Pomocy! "+GetSexPhrase("Nieznajomy","Młoda damo")+", ratuj mnie, błagam Cię!");
			link.l1 = LinkRandPhrase("Co się stało?","O co chodzi?",RandPhraseSimple("W czym problem?","Co się dzieje?"));
			link.l1.go = "Begin_11";
		break;

		case "Begin_2":
			LAi_RemoveCheckMinHP(NPChar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = RandPhraseSimple(""+GetSexPhrase("Kapitanie! Kapitanie","Dziewczyno! Dziewczyno")+", zaczekaj!","Poczekaj, "+GetSexPhrase("Kapitanie","młoda damo")+"! Proszę.");
			link.l1 = LinkRandPhrase("Co się stało?","O co chodzi?",RandPhraseSimple("W czym problem?","Co się dzieje?"));
			link.l1.go = "Begin_21";
		break;

		case "Begin_3":
			LAi_RemoveCheckMinHP(NPChar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = "Oh, p"+GetSexPhrase("anie","anienko")+"! Proszę, pomóż biednej dziewczynie, błagam Cię! Ci ludzie chcą mi zrobić coś strasznego!";
			link.l1 = LinkRandPhrase("Co się stało?","O co chodzi?",RandPhraseSimple("W czym problem?","Co się dzieje?"));
			link.l1.go = "Begin_31";
		break;
		
		case "Begin_11":
			dialog.text = RandPhraseSimple("Te łotry zamierzają mnie zgwałcić! Dla wszystkiego, co dobre, nie pozwól im na to!","Na miłość boską, ochroń mnie przed tymi potworami! Zamierzają mnie zhańbić!");
			link.l1 = "Przestań panikować"+GetSexPhrase(", moja piękna","")+". Pozwól mi z nimi pomówić.";
			link.l1.go = "exit_1";
		break;

		case "Begin_21":
			dialog.text = RandPhraseSimple("Gwałciciele mnie gonią!"+GetSexPhrase("Czy stanąłbyś w obronie honoru damy?","")+"","Kapitanie, "+GetSexPhrase("bądź mężczyzną","ty też jesteś kobietą")+" i uratuj dziewczyne od hańby!");
			link.l1 = "Przestań panikować"+GetSexPhrase(", moja piękna","")+". Pozwól mi z nimi pomówić";
			link.l1.go = "exit_1";
		break;
		
		case "Begin_31":
			dialog.text = "Oni mnie ścigają! Bandyci! Powiedz im, żeby mnie zostawili w spokoju!";
			link.l1 = "Przestań panikować"+GetSexPhrase(", moja piękna","")+". Ja już sobie z nimi pomówię";
			link.l1.go = "exit_1";
		break;
		
		case "First time":
			LAi_RemoveCheckMinHP(npchar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = LinkRandPhrase("Pomocy! Pomocy! Oni mnie gonią! Ratuj mnie!","Aaah! Pomocy, "+GetSexPhrase("nieznajomy","młoda damo")+"! Uratuj mnie od tych łajdaków!","Okaz mi litość i ocal mnie przed tymi łotrzykami! Proszę!");
			Link.l1 = LinkRandPhrase("Co się dzieje?","O co tu chodzi?","Co się stało?");
			Link.l1.go = "Node_2";			
		break;        

		case "Node_2":
			dialog.text = LinkRandPhrase("Oni... oni zamierzają mnie zgwałcić! Za wszystko, co dobre, nie pozwól im! Proszę!","Te bestie... planują coś strasznego... Ocal mnie przed nimi, proszę!","W imię naszego Pana, ratuj mnie od tych pożądliwych bestii! Chcą mnie zhańbić!");
			Link.l1 = "Dobra, przejdź do boku. Ja sobie z nimi odpowiednio porozmawiam.";
			Link.l1.go = "exit_1";			
		break;

		case "ThanksForHelp":
			if(pchar.GenQuest.EncGirl == "Begin_11")
			{
				if(rand(1) == 0)
				{
					dialog.text = RandPhraseSimple("Dziękuję, "+GetSexPhrase("Kapitanie","młoda damo")+". Byłem tak przerażona!","Dziękuję ci za uratowanie mnie! Jestem ci taka wdzięczna!");
					link.l1 = "Już w porządku, "+GetSexPhrase("skarbie","moja droga")+", uspokój się, to wszystko jest już w przeszłości.";
					link.l1.go = "Node_11";
				}
				else
				{
					dialog.text = "Oh, dziękuję Ci, "+GetSexPhrase("szlachetny człowieku! Jestes prawdziwym dżentelmenem!","pani! Uratowałaś mnie!")+"";
					link.l1 = "Innego wyjścia nie było.";
					link.l1.go = "Node_12";
				}
			}
			if(pchar.GenQuest.EncGirl == "Begin_22")
			{
				if(rand(1) == 0)
				{
					dialog.text = "Oh, dziękuję, "+GetSexPhrase("szlachetny człowieku! Jesteś prawdziwym dżentelmenem!","pani! Uratowałaś mnie!")+"";
					link.l1 = "Innego wyjścia nie było.";
					link.l1.go = "Node_12";	
				}
				else
				{
					dialog.text = "Co ty... ty...? Oni nie żyją?! Teraz będą mnie szukać! Mój Boże, co ja takiego zrobiłam, żeby na to zasłużyć!";
					link.l1 = "To się nazywa wdzięczność!";
					link.l1.go = "Node_22";
				}
			}
			if(pchar.GenQuest.EncGirl == "Begin_33")
			{
				dialog.text = "Nie moge uwierzyć, "+GetSexPhrase("kapitanie","młoda damo")+"?! Wszyscy nie żyją? Właściwie to zostali wysłani przez mojego ojca... O mój Boże, teraz na pewno mnie zabije...";
				link.l1 = "Rychło w czas! I co to sobie myślałaś, krzycząc, że byłaś ścigana przez bandytów?!";
				link.l1.go = "Node_31";
			}
		break;
		
		case "Node_11":
			Diag.TempNode = "Node_1Next";
			addMoneyToCharacter(pchar, makeint((sti(pchar.rank))*25 + frand(2)*500));
			dialog.text = "Mam trochę pieniędzy, proszę, przyjmij je jako wyraz mojej wdzięczności. Teraz powiem wszystkim, "+GetSexPhrase("jakim jesteś dobrym i szlachetnym człowiekiem","jaką dobrą i szlachetną kobietą jesteś")+".";
			link.l1 = "Tak zrób. Dzięki... a teraz prosze wróć do domu.";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			Diag.CurrentNode = Diag.TempNode;
		break;
		
		case "Node_12":
			dialog.text = "Wciąż nie mogę się pozbierać. Czy "+GetSexPhrase("mógłbyś","mogłabyś")+" zabrać mnie do osady "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+"? Wiesz, teraz gwałciciele wydają mi się być za każdym krzakiem.";
			link.l1 = RandPhraseSimple("Nie zamartwiaj się, naprawdę... No dobrze, ruszajmy.","Co za tchórz z ciebie. Dobrze, zabiorę cię tam.");
			link.l1.go = "Node_121Next";
			link.l2 = "Przykro mi, kochanie, ale po prostu nie mam czasu.";
			link.l2.go = "Node_3End";
		break;
						
		case "Node_22":
			dialog.text = "Miałem nadzieję, że tylko ich przestraszysz! Teraz musisz zabrać mnie do karczmy w osadzie "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+", nie mam nikogo innego, tylko ty, kogo mogę prosić o pomoc.";
			link.l1 = "O, cholera! W porządku, idziemy. Tylko nie zostawaj w tyle.";
			link.l1.go = "Node_122Next";
			link.l2 = "Nie, to wszystko, "+GetSexPhrase("skarbię","moja droga")+"! Miałem dość niespodzianek na dzisiaj. Szukaj kogoś innego, kto ci pomoże.";
			link.l2.go = "Node_3End";
		break;
		
		case "Node_31":
			dialog.text = "I co ja miałam robić?! Mój ojciec chce, żebym wyszła za mąż za syna lichwiarza, tego mazgaja... tylko dlatego, że jego tatusiek ma w swoich skrzyniach od cholery pieniędzy! Ale ja kocham innego mężczyznę! Zabierz mnie do niego, proszę...";
			link.l1 = "Jakim jesteś ciężarem! No dobrze, chodźmy. Nie mogę cię tu zostawić, prawda?.. Jakie jest imię twojego wybrańca, gdzie mam cię zabrać?";
			link.l1.go = "Node_32";
			link.l2 = "Nie ma opcji, "+GetSexPhrase("skarbie","moja droga")+"! Mam dość niespodzianek na dzisiaj. Poszukaj kogoś innego, kto ci pomoże.";
			link.l2.go = "Node_3End";
		break;
		
		case "Node_32":
			pchar.GenQuest.EncGirl.sLoverId = GenerateRandomName(sti(npchar.nation), "man"); 
			dialog.text = "Jego imię to "+pchar.GenQuest.EncGirl.sLoverId+", jest nowicjuszem. Teraz przebywa w osadzie "+XI_ConvertString("Kolonia"+pchar.GenQuest.EncGirl.city)+", próbowałem tam znaleźć pracę, ale to są ciężkie czasy. Wszyscy mówią o kryzysie... I tak czy inaczej, nie ma dla mnie powrotu do domu.";
			link.l1 = "Kryzys? Ha... Dla prawdziwego pirata kryzys to, gdy na horyzoncie jest karawana handlowa, ale nie ma wiatru do napełnienia żagli...";
			link.l1.go = "Node_12Next";
		break;
		
		case "Node_12Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_12End";
			Diag.CurrentNode = Diag.TempNode;
			pchar.GenQuest.EncGirl = "FindLover";
			pchar.GenQuest.EncGirl.MeetSoldiers = 2;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_121Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_253";
			pchar.GenQuest.EncGirl = "FindCoins";
			pchar.GenQuest.EncGirl.MeetSoldiers = 1;
			Diag.CurrentNode = Diag.TempNode;
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_town";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_122Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.GenQuest.EncGirl.MeetSoldiers = 1;
			Diag.CurrentNode = Diag.TempNode;
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";		
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_12End":
			Diag.TempNode = "Node_12End";
			dialog.text = RandPhraseSimple("Wiesz, "+GetSexPhrase("kapitan","młoda dama")+"? Byłem tak przestraszony, że moje nogi są jeszcze trochę chwiejne.","O, wiesz, byłem tak przerażony. To wspaniale, że Bóg skierował cię na moją drogę.");
			link.l1 = RandPhraseSimple("Dzięki Bogu, że jeszcze żyjesz.","Nie bierz tego do serca. Dobrze, że tak się skończyło, wiesz.");
			link.l1.go = "exit";
		break;
		
		case "Node_1Next":
			dialog.text = RandPhraseSimple("Dziękuję, "+GetSexPhrase("kapitan","młoda dama")+", znowu. Naprawdę, jestem ci tak wdzięczny.","Dziękuję bardzo, "+GetSexPhrase("kapitan","młoda dama")+". Nie mam pojęcia, co bym zrobił bez twojej pomocy.");
			link.l1 = RandPhraseSimple("To powinna być dla ciebie lekcja. Dobrze, powodzenia...","Następnym razem powinieneś być bardziej ostrożny... Teraz, wracaj do domu, mam rzeczy do zrobienia.");
			link.l1.go = "Node_1End";
			link.l2 = "Jak mogłeś być tak nieostrożny? Dlaczego poszedłeś sam do dżungli?";
			link.l2.go = "Node_13";
		break;
		
		case "Node_1End":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_3End":
			Diag.TempNode = "Node_3Final";
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		
		case "Node_3Final":
			Diag.TempNode = "Node_3Final";
			dialog.text = RandPhraseSimple("Czy zmieniłeś zdanie?","Kapitanie, wspaniale, że zmieniłeś zdanie!");
			link.l1 = RandPhraseSimple("Nie-nie, kochanie, podziękuję.","Nie miej fałszywych nadziei...");
			link.l1.go = "exit";
		break;
		
		case "Node_13":
			if(pchar.GenQuest.EncGirl == "FindCoins") 
			{
				pchar.quest.LandEnc_RapersBadExit.win_condition.l1 = "ExitFromLocation";
				pchar.quest.LandEnc_RapersBadExit.win_condition.l1.location = pchar.location;
				pchar.quest.LandEnc_RapersBadExit.win_condition = "LandEnc_RapersBadExit";
			}
			pchar.GenQuest.EncGirl = "Begin_11";
			switch(sti(pchar.GenQuest.EncGirl.variant))
			{
				case 0:
					if(rand(1) == 0)
					{
						dialog.text = "Prawdopodobnie ze mnie się wyśmiejesz, ale... zbierałem eliksir miłości... Wiedźma powiedziała mi, że jest korzeń, który może pomóc w sprawach miłosnych.";
						link.l1 = "O mój Boże! Co "+GetSexPhrase("o czym te kobiety myślą","czy o tym myślałeś")+"?! Widocznie, uzbierałeś ich całkiem sporo, była cała masa zalotników goniących za tobą, miałem trudności z odpędzaniem ich wszystkich. Ha-ha-ha-ha... Do widzenia.";
						link.l1.go = "Node_1End";
					}
					else
					{
						dialog.text = "Właśnie wyszedłem na spacer, aby zebrać trochę ziół i nadechnąć się świeżym powietrzem. Wygląda na to, że to nie był najlepszy czas na spacer.";
						link.l1 = "Jakie niezdarność?! Dzięki Bogu, że pojawiłem się na czas. Cóż, powodzenia.";
						link.l1.go = "Node_1End";
					}
				break;
				case 1:
					dialog.text = "Moja pani rozsypała perły z jej naszyjnika gdzieś tutaj, kiedy była na spacerze. Kiedy wróciła do domu, krzyczała na mnie i kazała wyjść i je zbierać. Powiedziała: 'Nie pokazuj tu swojej twarzy, dopóki ich wszystkich nie zbierzesz!', A ja nawet nie znam dokładnego miejsca. Poza tym, jak mam je znaleźć w tej gęstej trawie? Perły są takie małe... Więc, po prostu tu błądzę bez pojęcia, co powinienem zrobić...";
					link.l1 = "A jaki to był naszyjnik? Może łatwiej byłoby po prostu kupić nowy, zamiast błądzić po dżungli? Ile pereł straciła twoja pani?";
					link.l1.go = "Node_131";
				break;
				case 2:
					dialog.text = "Mój zmarły ojciec zostawił mi mapę, a jego towarzysze chcieli ją ode mnie zabrać. Kiedy był żywy, wszyscy drżeli przed nim ze strachu, ale zaraz po tym, jak go pochowałam, zaczęły się czasy niespokojne. Najpierw próbowali kupić ode mnie tę mapę, ale odmówiłam, więc zaczęli mnie zastraszać.";
					link.l1 = "A dlaczego nie sprzedałeś tego po prostu? Co jest takiego wyjątkowego w tej mapie, że gangi piratów jej szukają?";
					link.l1.go = "Node_132";
				break;
			}	
		break;
		
		case "Node_131":
			pchar.GenQuest.EncGirl.SmallCoins = rand(25) + 20;
			pchar.GenQuest.EncGirl.BigCoins = rand(15) + 5;
			dialog.text = "To naszyjnik był wykonany z wyselekcjonowanych pereł, które nie mogą być kupione tanio. Były "+sti(pchar.GenQuest.EncGirl.BigCoins)+" duże perły i "+sti(pchar.GenQuest.EncGirl.SmallCoins)+" mniejsze. Gdyby te perły zostały znalezione, moglibyśmy zlecić wykonanie kolejnego naszyjnika, takiego jak ten.";
			link.l1 = "Na pewno nie będzie to łatwe zadanie... Cóż, jeśli twoja pani ci coś nakazała, to nie masz dużo do powiedzenia. Spróbuj znaleźć perły. Powodzenia.";
			link.l1.go = "Node_131End";
			link.l2 = "To bez sensu. Łatwiej byłoby znaleźć igłę w stogu siana niż perły w tej gęstej trawie. Nie mówiąc już o tym, że nawet nie znasz miejsca, gdzie perły zostały zgubione...";
			link.l2.go = "Node_133";
		break;
		
		case "Node_131End":
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.quest.LandEnc_RapersBadExit.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LandEnc_RapersBadExit.win_condition.l1.location = pchar.location;
			pchar.quest.LandEnc_RapersBadExit.win_condition = "LandEnc_RapersBadExit";
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132":
			pchar.GenQuest.EncGirl.mapOwner = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1); 
			dialog.text = "Mój ojciec zaznaczył na niej miejsce, gdzie ukrył swój skarb. Słyszałeś o sławnym piracie "+GetName(NAMETYPE_ORIG,pchar.GenQuest.EncGirl.mapOwner,NAME_VOC)+"?";
			link.l1 = "Nie, nigdy o nim nie słyszałem.";
			link.l1.go = "Node_132_1";
		break;
		
		case "Node_132_1":
			dialog.text = "No cóż, "+GetName(NAMETYPE_ORIG,pchar.GenQuest.EncGirl.mapOwner,NAME_NOM)+" był moim ojcem. Wszyscy się go bali, nikt nie odważyłby się pisnąć słówka. Teraz oczywiście stali się bezczelni. Kiedy odmówiłem sprzedaży mapy im, twierdzili, że oni też muszą mieć swój udział w skarbie. Chciałem schować mapę, ale i tak mnie namierzyli...";
			link.l1 = "A dlaczego byś to ukrywał, na pierwszym miejscu? Wynajmij statek i idź, zdobądź swój skarb. Twój ojciec nie ukryłby tego bez powodu.";
			link.l1.go = "Node_132_2";
		break;
		
		case "Node_132_2":
			dialog.text = "Łatwiej powiedzieć niż zrobić. Nie mam pieniędzy na wynajęcie statku, a... boję się... Jak mam to wszystko wykopać, przynieść na statek... A gdzie potem miałbym zabrać skarb? Każdy by mnie po drodze łatwo upolował...";
			link.l1 = "To dobra uwaga... Dobrze, schowaj swoją mapę. Tylko pamiętaj, żeby dobrze ją umieścić.";
			link.l1.go = "Node_132_2End";
			if(GetCharacterItem(pchar, "map_full") == 0)
			{
				link.l2 = "Hmm... To prawdopodobnie prawda. Tym bardziej powinieneś to sprzedać.";
				link.l2.go = "Node_132_3";
			}
			link.l3 = "Czy próbowałeś znaleźć towarzysza?";
			link.l3.go = "Node_132_8";	
		break;
		
		case "Node_132_2End":
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132_3":
			dialog.text = "Smutno mi tracić taką okazję... Tata opowiadał mi o skarbach, które ukrył tam. Nikt nie zapłaciłby mi tyle...";
			link.l1 = "Cóż, nie sprzedawaj tego za tanio. I tak czy inaczej, złoto nie jest warte twojego życia. Nie mówiąc już o tym, że to najłatwiejsza droga dla ciebie, po prostu zbierasz swoje pieniądze i pozbywasz się wszystkich kłopotów...";
			link.l1.go = "Node_132_4";
		break;
		
		case "Node_132_4":
			pchar.GenQuest.EncGirl.mapPrice = 20000 + 500 * sti(pchar.rank);
			dialog.text = "To brzmi kusząco... I ile możesz mi za to zaoferować?";
			link.l1 = "Nie sądzę, aby mogło to być warte więcej niż "+sti(pchar.GenQuest.EncGirl.mapPrice)+" pesos.";
			link.l1.go = "Node_132_5";
		break;
		
		case "Node_132_5":
			if((GetSummonSkillFromName(pchar, SKILL_COMMERCE) + GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) + GetSummonSkillFromName(pchar, SKILL_FORTUNE)) > (rand(220) + 100) && (makeint(pchar.money) >= sti(pchar.GenQuest.EncGirl.mapPrice)))
			{
				dialog.text = "Heh, bycie kobietą nie jest łatwe... Dobrze, zgadzam się. Wreszcie ten koszmar się skończy... Być może, to najlepiej, że ta mapa należy do ciebie,"+GetSexPhrase("szlachetny dżentelmen","")+", niż tym łajdakom.";
				link.l1 = "Dobrze. Oto twoje pieniądze... po prostu spróbuj nie wydać ich wszystkich naraz.";
				link.l1.go = "Node_132_6";
			}
			else
			{
				dialog.text = "Nie, "+GetSexPhrase("kapitan","młoda dama")+". Nie sprzedam tego. Wyjdę za mąż za dobrego mężczyznę, a potem razem zgarniemy skarb.";
				link.l1 = "Cóż, to zależy od ciebie. Twój kawałek papieru i tak nie jest więcej wart.";
				link.l1.go = "Node_132_2End";
			}	
		break;
		
		case "Node_132_6":
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.mapPrice))); 
			ref rMap = ItemsFromID("map_full"); // mitrokosta фикс пустой карты
			FillMapForTreasure(rMap);
			GiveItem2Character(pchar, "map_full");
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132_8":
			dialog.text = "I gdzie ich znajdę? Młodzi są niewiarygodni i nie zależy im na skarbach tak bardzo jak na, innych rzeczach. A starszych się boję, wszyscy przypominają mi kolegów mojego ojca. Tak przebiegli i zdradzieccy, nigdy nie wiesz, czego się po nich spodziewać.";
			link.l1 = "Ha-ha-ha... Dobrze, ale zabierzesz mnie ze sobą?";
			link.l1.go = "Node_132_9";
		break;
		
		case "Node_132_9":
			dialog.text = "Ty? A poszedłbyś? Ale wtedy musisz mnie przyprowadzić z powrotem tutaj, do osiedla "+XI_ConvertString("Colonia"+pchar.GenQuest.EncGirl.city)+", dobrze?";
			link.l1 = "Dobrze, daję ci moje słowo. Pokaż mi tylko drogę.";
			link.l1.go = "Node_132_10";
		break;
		
		case "Node_132_10":
			EncGirl_GenQuest_GetChestPlaceName();
			dialog.text = "Skarb jest ukryty w jaskini na "+XI_ConvertString(pchar.GenQuest.EncGirl.islandId+"Acc")+", musimy wylądować na "+XI_ConvertString(pchar.GenQuest.EncGirl.shoreId+"Gen")+", miejsce, w którym się pokażę... Ale nie zapomnij, dostaniesz tylko połowę!";
			link.l1 = "Dobrze, nie oszukam cię, obiecuję. Idź za mną i nie zostawaj w tyle.";
			link.l1.go = "Node_132_11";
		break;
		
		case "Node_132_11":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "4");
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sPirateName", GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_GEN));
			AddQuestUserData("JungleGirl", "sTreasureLoc", XI_ConvertString(pchar.GenQuest.EncGirl.islandId));
			AddQuestUserData("JungleGirl", "sShore", XI_ConvertString(pchar.GenQuest.EncGirl.shoreId + "Gen"));
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			pchar.quest.EncGirl_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.EncGirl_Death.win_condition.l1.character = npchar.id;
			pchar.quest.EncGirl_Death.function = "EncGirl_Death";
			pchar.quest.EncGirl_FindChest.win_condition.l1 = "location";
			pchar.quest.EncGirl_FindChest.win_condition.l1.location = pchar.GenQuest.EncGirl.placeId;
			pchar.quest.EncGirl_FindChest.function = "EncGirl_FindChest";
			SetFunctionExitFromLocationCondition("EncGirl_AddPassenger", pchar.location, false);
			SetFunctionLocationCondition("EncGirl_DialogAtShore", pchar.GenQuest.EncGirl.shoreId, false);
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "GetChest";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132_11_1":
			dialog.text = "Kapitanie, teraz musimy znaleźć jaskinię.";
			link.l1 = "Dobrze, spójrzmy teraz.";
			link.l1.go = "exit";
			Diag.TempNode = "Node_132_11_2";
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
		break;
		
		case "Node_132_11_2":
			Diag.TempNode = "Node_132_11_2";
			dialog.text = "Kapitanie, musimy znaleźć jaskinię.";
			link.l1 = "W porządku, spójrzmy teraz.";
			link.l1.go = "exit";
		break;
		
		case "Node_132_12":
			dialog.text = "Tutaj! Znalazłem to! Tak jak mój ojciec mówił! Ogromny stos skarbów! Połowa jest twoja, zgodnie z umową.";
			link.l1 = "Widzisz? To nie było trudne, więc nie było czego się bać.";
			link.l1.go = "Node_132_13";
		break;
		
		case "Node_132_13":
			dialog.text = "Ha-ha-ha! Teraz jestem bogaty! Weźmiesz teraz swoją część?";
			link.l1 = "Chyba tak.";
			link.l1.go = "Node_132_15";
		break;
		
		case "Node_132_15":
			dialog.text = "Więc weź to i proszę, pomóż mi przenieść cały ten dobytek na statek. Czy nadal pamiętasz, że obiecałeś zabrać mnie do domu?";
			link.l1 = "Nie zapomniałem! Jasne, zabiorę cię.";
			link.l1.go = "Node_132_16";
		break;
		
		case "Node_132_16":
			pchar.quest.EncGirl_DeathSimple.over = "yes";
			PChar.quest.EncGirl_DialogAtShore.over = "yes";// лесник . снял прерывание  , если не с той бухты зашёл.		
			LAi_LocationDisableMonstersGen(pchar.location, false);
			chrDisableReloadToLocation = false;
			Log_Info("You have received your share of the treasure");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "icollection", 1+hrand(1));
			TakeNItems(pchar, "chest", 2+hrand(6));
			TakeNItems(pchar, "jewelry1", 30+hrand(15));
			TakeNItems(pchar, "jewelry2", 30+hrand(15));
			TakeNItems(pchar, "jewelry3", 30+hrand(15));
			TakeNItems(pchar, "jewelry4", 30+hrand(15));
			TakeNItems(pchar, "jewelry5", 30+rand(10));
			TakeNItems(pchar, "jewelry6", 10+rand(10));
			TakeNItems(pchar, "jewelry42", 20+rand(10));
			TakeNItems(pchar, "jewelry44", 30+rand(10));
			TakeNItems(pchar, "jewelry46", 50+rand(20));
			AddQuestRecord("JungleGirl", "6");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sPirateName", GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_GEN));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));		
			pchar.GenQuest.EncGirl = "ChestGetted";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_town";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";
			pchar.quest.EncGirl_DeathAgain.win_condition.l1 = "NPC_Death";
			pchar.quest.EncGirl_DeathAgain.win_condition.l1.character = npchar.id;
			pchar.quest.EncGirl_DeathAgain.function = "EncGirl_DeathAgain";
			Diag.TempNode = "Node_132_17";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			pchar.quest.EncGirl_AddPassenger.win_condition.l1 = "location";// лесник на корабль девицу. 
			pchar.quest.EncGirl_AddPassenger.win_condition.l1.location = pchar.location.from_sea;
			pchar.quest.EncGirl_AddPassenger.function = "EncGirl_AddPassenger";
		break;
		
		case "Node_132_17":
			Diag.TempNode = "Node_132_17";
			dialog.text = "Bycie bogatym jest po prostu wspaniałe! Czuję się teraz tak inaczej."; 
			link.l1 = "Cieszę się dla ciebie.";
			link.l1.go = "exit";
		break;
		
		case "Node_132_18":
			dialog.text = "W porządku, kapitanie. Moja podróż teraz się kończy. Dziękuję za twoją pomoc.";
			link.l1 = "Proszę bardzo... Więc, co zamierzasz zrobić ze swoim nowo zdobytym bogactwem? Kupić plantację ze niewolnikami?";
			link.l1.go = "Node_132_19";
		break;
		
		case "Node_132_19":
			dialog.text = "Nie wiem, jeszcze nie zdecydowałem. Być może przeniosę się do Europy...";
			link.l1 = "Dobrze, cóż! Powodzenia dla ciebie.";
			link.l1.go = "Node_132_20";
		break;
		
		case "Node_132_20":
			dialog.text = "Zaczekaj... Ten drobiazg był wśród skarbów mojego ojca. Mi nie jest potrzebny, ale Tobie może się spodobać. Proszę, przyjmij go jako wyraz mojej osobistej wdzięczności za to, co dla mnie zrobiłeś. To z mojej części, ha-ha-ha!";
			link.l1 = "O, to naprawdę miły prezent. Dziękuję"+GetSexPhrase(", piękno","")+". Znajdź sobie porządnego pana młodego, co?...";
			link.l1.go = "Node_132_21";
		break;
		
		case "Node_132_21":
			chrDisableReloadToLocation = false;		
			RemovePassenger(pchar, npchar);			
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item); 
			AddQuestRecord("JungleGirl", "8");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
            LAi_SetActorType(npchar); // отправил восвояси чтоб не стояла. лесник.
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
            pchar.quest.EncGirl_EnterToSea.over = "yes";// лесник . снял прерывание  , если не с той бухты зашёл.	
            PChar.quest.EncGirl_DialogAtShore.over = "yes";// лесник . снял прерывание  , если не с той бухты зашёл.						
		break;
		
		case "Node_133":
			dialog.text = "Ale co mogę zrobić? Nie mogę zignorować poleceń mojej pani, obdaruje mnie ze skóry.";
			link.l1 = "Zaczekaj na mnie w kościele osady "+XI_ConvertString("Kolonia"+pchar.GenQuest.EncGirl.city)+", przyniosę ci perły, aby zrobić nowy naszyjnik.";
			link.l1.go = "Node_133_1";
			if(sti(pchar.money) >= 15000)
			{
				link.l2 = "Tutaj. Weź te 15000 peso. To powinno być więcej niż wystarczająco, aby wybrać perły do naszyjnika, lub kupić nowy.";
				link.l2.go = "Node_135";
			}							
		break;
		
		case "Node_133_1":
			pchar.GenQuest.EncGirl = "GetCoins";
			pchar.quest.EncGirl_Coins.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_Coins.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_Coins.function = "EncGirl_toChurch";
			pchar.quest.EncGirl_GetCoins.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.day = GetAddingDataDay(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.year = GetAddingDataYear(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.function = "EncGirl_GenQuest_GetCoins";	
            sTemp = LAi_FindNearestFreeLocator2Pchar("reload");// лесник - девица убегает если ГГ сказал ждать в цервки
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);			
			Diag.TempNode = "Node_134"; 
			Diag.CurrentNode = Diag.TempNode;
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "1"); 
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","")); 
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name); 
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			AddQuestUserData("JungleGirl", "sText1", sti(pchar.GenQuest.EncGirl.BigCoins)); 
			AddQuestUserData("JungleGirl", "sText2", sti(pchar.GenQuest.EncGirl.SmallCoins)); 		
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_134":
			dialog.text = RandPhraseSimple(""+GetSexPhrase("Kapitan","Młoda dama")+", Jestem tak szczęśliwy, że znowu cię widzę! Udało ci się zebrać perły na naszyjnik?","Witaj, kapitanie! Czy przyniosłeś mi perły? Wiesz, moja pani staje się tak nerwowa...");
			if (GetCharacterItem(pchar, "jewelry52") >= sti(pchar.GenQuest.EncGirl.BigCoins) && GetCharacterItem(pchar, "jewelry53") >= sti(pchar.GenQuest.EncGirl.SmallCoins))
			{
				link.l1 = "Tak. Oto twoje perły. Zanieś je swojej pani i powiedz jej, żeby była bardziej ostrożna następnym razem.";
				link.l1.go = "Node_134_1";
			}
			else
			{
				link.l1 = "Jeszcze nie. To nie jest takie łatwe, wiesz... Ale przyprowadzę ich, tylko poczekaj.";
				link.l1.go = "Node_134_2";
			}	
		break;
		
		case "Node_134_1":
			TakeNItems(pchar, "jewelry52", -sti(pchar.GenQuest.EncGirl.BigCoins)); 
			TakeNItems(pchar, "jewelry53", -sti(pchar.GenQuest.EncGirl.SmallCoins)); 
			pchar.quest.EncGirl_GetCoins.over = "yes";
			pchar.quest.EncGirl_DeathSimple.over = "yes";
			dialog.text = "Oh, "+GetSexPhrase("Kapitan","młoda dama")+", Jestem tak szczęśliwy, że cię spotkałem! Jako wyraz mojej wdzięczności za wszystko, co dla mnie zrobiłeś, chcę ci dać ten drobiazg i te klejnoty. Mam nadzieję, że okażą się dla ciebie przydatne.";
			link.l1 = "Wow! No, dziękuję również"+GetSexPhrase(", piękność","")+", nie spodziewałem się... Do widzenia, bądź szczęśliwy.";
			link.l1.go = "Node_134_End";
		break;
		
		case "Node_134_2":
			dialog.text = "Oh, "+GetSexPhrase("kapitan","młoda dama")+", liczę na ciebie.";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_SetStayType(NPChar);
		break;
		
		case "Node_134_End":
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item); 
			TakeNItems(pchar, "jewelry1", 15+hrand(8));
			AddQuestRecord("JungleGirl", "2");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name); 
			CloseQuestHeader("JungleGirl");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_135":
			addMoneyToCharacter(pchar, -15000);
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			dialog.text = "Oh, "+GetSexPhrase("kapitan","młoda dama")+", pomogłeś mi po raz drugi dzisiaj. Bardzo ci dziękuję. Nigdy nie zapomnę twojej dobroci.";
			link.l1 = "Nie ma za co. Pozdrów swoją panią...";
			link.l1.go = "Node_135End";
		break;
		
		case "Node_135End":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			NPChar.lifeDay = 0;
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();		
			AddDialogExitQuest("pchar_back_to_player");			
		break;	
		
		case "ThanksForSave":
			if (npchar.city == "Bridgetown" || npchar.city == "Charles" || npchar.city == "FortFrance" || npchar.city == "Marigo" || npchar.city == "Panama" || npchar.city == "PortRoyal" || npchar.city == "SantoDomingo" || npchar.city == "Tortuga") 
			{
				if(CheckAttribute(pchar, "GenQuest.EncGirl.Horse")) 
				{
					iRnd = 2;
					pchar.GenQuest.EncGirl.BrothelCity = true;
				}	
				else
				{	
					iRnd = 1;
				}	
			}
			else
			{
				iRnd = 1;
			}
			switch(rand(iRnd))
			{
				case 0:
					dialog.text = RandPhraseSimple("Nie powinieneś im dawać żadnych pieniędzy. Kłamali.","Nie wierz im. To kłamcy. I nie powinieneś im dawać żadnych pieniędzy.");
					link.l1 = "Czy powinienem ich zabić?";
					link.l1.go = "Node_200";
				break;
				case 1:
					dialog.text = "O, jaka szlachetna czynność! Od razu wiedziałem, że jesteś "+GetSexPhrase("prawdziwy dżentelmen","szlachetna dama")+"! Proszę, przyjmij moje najszczersze podziękowania. Mam nadzieję, że nie uwierzyłeś temu, co mówili ci łajdacy?";
					link.l1 = "To nie ma znaczenia. Dziewczyna i banda szmatławców w dżungli, to takie naturalne...";
					link.l1.go = "Node_210";
					link.l2 = "O czym ty mówisz, "+GetSexPhrase("piękno","drogi")+"? Jak mogłem?";
					link.l2.go = "Node_211";
				break;
				case 2:
					dialog.text = "Dziękuję, kapitanie. Przykro mi, że wplątałem cię w tę nieprzyjemną sprawę, ale po prostu nie miałem innego wyboru.";
					link.l1 = "Cóż, widzę, że też jesteś dość zablokowany. Jak do tego doszło?";
					link.l1.go = "Node_220";		
				break;
			}
		break;
		
		case "Node_200":
			if(rand(1) == 0)
			{
				dialog.text = "Być może... Oni nigdy mnie teraz nie zostawią w spokoju.";
				link.l1 = "Oh, daj spokój! Po prostu wróć do domu, teraz nie masz się czego bać.";
				link.l1.go = "Node_200End";
				link.l2 = "O rety! Dlaczego tak nie znosisz mężczyzn?";
				link.l2.go = "Node_201";
			}
			else
			{
				dialog.text = "Oczywiście, że nie! Ale i tak mnie nie zostawią. Czy przyprowadzisz mnie do osiedla "+XI_ConvertString("Colonia"+pchar.GenQuest.EncGirl.city)+", proszę?";
				link.l1 = "Po prostu wróć do domu, nie dotkną cię. Powinni iść teraz do karczmy, aby zmarnować swoje łatwe pieniądze.";
				link.l1.go = "Node_200End";
				link.l2 = RandPhraseSimple("Nie martw się tak bardzo, naprawdę... No dobrze, idziemy.","Jesteś taki tchórz, prawda? Dobrze, zawiozę cię tam..");
				link.l2.go = "Node_121Next";
			}
		break;
		
		case "Node_201":
			dialog.text = "O nie, co ty mówisz? Znam tych łotrów aż za dobrze. To byli dawni koledzy mojego ojca. Próbują znaleźć miejsce, gdzie ukrył swoje skarby.";
			link.l1 = "A co z twoim ojcem?";
			link.l1.go = "Node_202";
		break;
		
		case "Node_202":
			dialog.text = "Był kiedyś kapitanem pirackiego statku. Ostatnio zmarł... Wszyscy byli tak uprzejmi podczas pogrzebu, ale z czasem zapomnieli o nim, a niedługo potem o swojej honorowości i uczciwości. Dobrze, że ich zauważyłem. Jak tylko dowiedzą się, gdzie są skarby, jestem skończony.";
			link.l1 = "To smutna historia. Więc, planujesz nadal się przed nimi ukrywać?";
			link.l1.go = "Node_203";
		break;
		
		case "Node_203":
			dialog.text = "Nie mogę trzymać klejnotów w domu, nie mam kogoś kto by mnie chronił. Więc idę w nocy do jaskini, kiedy kończą mi się pieniądze...\nZabierz mnie, proszę, do jaskini, a ja oddam ci pieniądze, które dałeś im... Myślę, że piraci nie zaryzykowaliby podążania za nami, kiedy ty jesteś ze mną.";
			link.l1 = "Przykro mi, kochanie, ale mam inne plany. Zbierzesz swój skarb innym razem.";
			link.l1.go = "Node_200End";
			link.l2 = "Dobrze, chodźmy, jeśli mnie się nie boisz.";
			link.l2.go = "Node_204";
		break;
		
		case "Node_204":
			dialog.text = "Wiesz, z jakiegoś powodu, ja nie...";
			link.l1 = "Cóż, to dobra rzecz.";
			link.l1.go = "Node_205";
		break;
		
		case "Node_205":
			Diag.TempNode = "Node_206";
			EncGirl_GenerateChest(npchar);
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_206":
			Diag.TempNode = "Node_206";
			dialog.text = "Kapitanie, obiecałeś mnie zabrać do jaskini.";
			link.l1 = "Chodźmy...";
			link.l1.go = "exit";
		break;
		
		case "Node_207":
			dialog.text = "W porządku, kapitanie, wziąłem tyle, ile potrzebowałem. Teraz możemy wrócić.";
			link.l1 = "Nie widzę twoich kumpli w pobliżu.";
			link.l1.go = "Node_208";
		break;
		
		case "Node_208":
			dialog.text = "Dzięki Bogu. Nie potrzebuję więcej kłopotów... Tutaj, weź te sztabki... to powinno wystarczyć na pokrycie twoich wydatków. Idź sam, ja wybiorę inną drogę...";
			link.l1 = "Dobrze, powodzenia, jeśli się nie boisz.";
			link.l1.go = "Node_209";
		break;
		
		case "Node_209":
			LAi_LocationDisableMonstersGen(pchar.location, false);
			i = makeint(sti(pchar.GenQuest.EncGirl.price)/100.0);
			TakeNItems(pchar, "jewelry6", i);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			pchar.quest.EncGirl_RapersExit.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_RapersExit.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_RapersExit.function = "EncGirl_MeetRapers";
			DialogExit();
		break;
		
		case "Node_200End":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			AddDialogExitQuestFunction("EncGirl_GirlGoAway");
			DialogExit();
		break;
		
		case "Node_210":
			dialog.text = "Hmm, "+GetSexPhrase("kapitan","młoda dama")+", Nie podoba mi się twoja ironia.";
			link.l1 = "Możesz iść, "+GetSexPhrase("piękno","drogi")+". I lepiej pospiesz się do miasta, zanim znów cię ścigną.";
			link.l1.go = "Node_1End";
		break;
		
		case "Node_211":
			dialog.text = "Byłem tak zdenerwowany! Czy mógłbyś mnie proszę zabrać do karczmy w osadzie "+XI_ConvertString("Kolonia"+pchar.GenQuest.EncGirl.city)+"? W przeciwnym razie, obawiam się, że znowu będą za mną gonić.";
			link.l1 = "Być może masz rację. Chodźmy...";
			link.l1.go = "Node_122Next";
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
		break;
		
		case "Node_220":
			dialog.text = "Oh, kapitanie, to długa historia, nie jestem pewien, czy byłoby to dla ciebie interesujące. Chociaż... i tak nie poradzę sobie bez twojej pomocy. Czy mógłbyś mnie zawieźć do tawerny w osadzie "+XI_ConvertString("Kolonia"+pchar.GenQuest.EncGirl.city)+"Boję się, że po prostu nie zostawią mnie w spokoju.";
			link.l1 = "Przykro mi, kochanie, nie mam na to czasu. Mam rzeczy do zrobienia.";
			link.l1.go = "Node_221";
			link.l2 = "Dlaczego jesteś tak tajemniczy?";
			link.l2.go = "Node_222";
		break;
		
		case "Node_221":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddDialogExitQuestFunction("EncGirl_GirlGoAway");
			DialogExit();
		break;
		
		case "Node_222":
			dialog.text = "I jak mogę nie być skryty, jeśli wszyscy próbują zarobić na moim nieszczęściu?";
			link.l1 = "Dobrze, więc...";
			link.l1.go = "Node_223";
		break;
		
		case "Node_223":
			Diag.TempNode = "Node_224";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";		
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();		
		break;
		
		case "Node_224":
			dialog.text = "Kapitanie, obiecałeś zabrać mnie do tawerny w osadzie "+XI_ConvertString("Kolonia"+pchar.GenQuest.EncGirl.city)+".";
			link.l1 = RandPhraseSimple("Pamiętam.","Nie martw się, spotkam cię tam.");
			link.l1.go = "exit";
		break;
		
		case "Node_225":
			chrDisableReloadToLocation = false;
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				if (CheckAttribute(pchar, "GenQuest.EncGirl.BrothelCity") && sti(pchar.rank) > 15)
				{
					dialog.text = "Tam jest zbyt wiele osób. Chodźmy do prywatnego pokoju. Muszę ci coś powiedzieć.";
					link.l1 = LinkRandPhrase("Już za dużo dla ciebie zrobiłem, więc teraz żegnaj.","Nie powinieneś nadużywać mojej łaski. Do zobaczenia, kochanie.","Nie potrzebuję twoich opowieści od teraz, możesz to wszystko sam rozgryźć.");
					link.l1.go = "Node_226";
					link.l2 = "Hmm, dobrze. Wezmę klucze od barmana.";
					link.l2.go = "Node_227";
				}
				else
				{
					dialog.text = "Dziękuję bardzo za twoją pomoc, kapitanie. Nie zapomnę tego.";
					link.l1 = "Oh, nie przejmuj się. Po prostu postaraj się być ostrożniejszy w przyszłości.";
					link.l1.go = "Node_226_1";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.FMQP") && pchar.questTemp.FMQP == "begin") // Addon-2016 Jason, французские миниквесты (ФМК)
				{
					dialog.text = "Dziękuję Ci bardzo za pomoc, kapitanie. Nie zapomnę tego.";
					link.l1 = "Och, nie martw się. Po prostu postaraj się być bardziej ostrożny w przyszłości.";
					link.l1.go = "Node_226_1";
				}
				else
				{
					dialog.text = "Tam jest za dużo ludzi. Chodźmy do prywatnego pokoju. Muszę ci coś powiedzieć.";
					link.l1 = LinkRandPhrase("Zrobiłem dla ciebie już za dużo, więc teraz żegnaj.","Nie powinieneś nadużywać mojej łaski. Do zobaczenia, kochanie.","Nie potrzebuję już twoich opowieści, sam sobie możesz to wszystko rozgryźć.");
					link.l1.go = "Node_226";
					link.l2 = "Hmm, dobrze. Wezmę klucze od barmana.";
					link.l2.go = "Node_227";
				}
			}
		break;
		
		case "Node_226":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();		
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_226_1":
			ChangeCharacterComplexReputation(pchar,"nobility", 3);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();		
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_227":
			pchar.GenQuest.EncGirl = "EncGirl_ToTavern";
			pchar.quest.EncGirl_inRoom.win_condition.l1 = "location";
			pchar.quest.EncGirl_inRoom.win_condition.l1.location = npchar.city + "_tavern_upstairs";
			pchar.quest.EncGirl_inRoom.function = "EncGirl_SpeakInRoom";
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_228":
			if(CheckAttribute(pchar, "GenQuest.EncGirl.Horse") && CheckAttribute(pchar,"GenQuest.EncGirl.BrothelCity") && sti(pchar.rank) > 15) // душещипательная история о невинной девочке попавшей в бордель
			{
				DeleteAttribute(pchar, "GenQuest.EncGirl.BrothelCity");
				dialog.text = "Czy nadal chcesz wysłuchać moją historię?";
				link.l1 = "Hmm... Chyba, to czas dla mnie na wyjście. Do widzenia!";
				link.l1.go = "Node_232";
				link.l2 = "No, wypluj to, potem.";
				link.l2.go = "Node_233";	
			}
			else						
			{
				dialog.text = "Och, mój szlachetny wybawco, wreszcie mogę Ci podziękować w ten sposób, jak tylko kobieta może podziękować\nGdy zobaczyłam Cię w dżungli, wszystko we mnie się zmieniło. Zapomniałam o gwałcicielach i ostrych liściach palm, które chłostały moje policzki. Zapomniałam, dokąd biec, dlaczego uciekać... Widziałam tylko Ciebie. I tylko Ciebie pragnęłam... A po tym, co dla mnie zrobiłeś...";
				link.l1 = "O rety! Co za temperament! Twoi prześladowcy na pewno wiedzieli, kogo gonić...";
				link.l1.go = "Node_229"; // ГГ допрыгался - щас его попросту трахнут
				link.l2 = "Słuchaj, piękności, doskonale to rozumiem, ale proszę, zachowaj swoje humory dla siebie.";
				link.l2.go = "Node_230"; // Послал в пешее эротическое путешествие
			}
		break;
		
		case "Node_229":
			dialog.text = "Przyjdź do mnie teraz, mój bohaterze...";
			link.l1 = "Och, kochanie...";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "EncGirl_facking";
			DoQuestCheckDelay("PlaySex_1", 3.0);
		break;
		
		case "Node_230":
			dialog.text = "Och! Jak... Jak śmiesz?! Co za łajdak! Dziewczyna dziękowała ci z całego serca, a ty...";
			link.l1 = "Cóż, gdybyś nie flirtowała tak bardzo i nie rzuciła się na oślep na pierwszego napotkanego mężczyznę, z pewnością miałabyś mniej problemów. Już nie ratuję takich kokietek w dżungli...";
			link.l1.go = "Node_231";
		break;
		
		case "Node_231":
			dialog.text = "Nigdy wcześniej nie słyszałem takich słów od nikogo! I nie wybaczę ich! Jeszcze o mnie usłyszysz!";
			link.l1 = "Idź już, dobrze? I spróbuj się odświeżyć, chyba że chcesz znowu być ratowany...";
			link.l1.go = "Node_231_1";
		break;
		
		case "Node_231_1":
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "","", -1.0);
			npchar.lifeDay = 0;
			DoQuestFunctionDelay("EncGirl_SetBerglar", 5.0);
			DialogExit();		
		break;
		
		case "Node_232":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_233":
			pchar.GenQuest.EncGirl.Parents_City = GetQuestNationsCity(sti(pchar.GenQuest.EncGirl.nation));
			dialog.text = "Moja rodzina mieszka w osadzie "+XI_ConvertString("Kolonia"+pchar.GenQuest.EncGirl.Parents_City)+". Trafiłam tutaj przypadkowo, na statku, na którym mój narzeczony zabierał mnie do swoich rodziców, ale został on zdobyty przez piratów. Statek został im odebrany, a pasażerowie zostali wylądowani w zatoce niedaleko stąd. Mój narzeczony został zabity podczas abordażu statku, a ja byłem poważnie chora podczas przejścia przez dżunglę\nPani z lokalnego domu publicznego mnie leczyła, a kiedy stanęłam na nogi, zażądała, żebym pracowała na pieniądze wydane na leczenie. Byłam prostytutką, ale nie podobałam się Madame, więc Pani sprzedała mnie jakiemuś bandytom, żeby zarobić przynajmniej trochę pieniędzy. Resztę historii znasz.";
			link.l1 = "Więc po prostu zrezygnuj i wróć do domu! Dlaczego pozwalasz im traktować cię jak niewolnika?!";
			link.l1.go = "Node_234";
		break;
		
		case "Node_234":
			dialog.text = "Nie mogę! Wszystko co mam: porządne ubrania, pieniądze, dokumenty... Wszystko jest w burdelu w mojej torbie podróżnej. Schowałem to w pokoju randkowym. A tak ubrany, wszyscy marynarze w porcie będą za mną biegać. A kto mnie weźmie na pokład bez dokumentów czy pieniędzy? A teraz nawet nie mogę pokazać twarzy w mieście, bo zostanę wrzucony za kratki...";
			link.l1 = "Nie powinno być problemu. Chodźmy. Osobiście cię odwiozę do domu.";
			link.l1.go = "Node_235";
			link.l2 = "Zaczekaj tutaj. Przyniosę ci twój torbę podróżną.";
			link.l2.go = "Node_236";													
			if(sti(pchar.money) >= 5000) 
			{
				link.l3 = "Kto dba o twoje papiery? Ile pieniędzy potrzebujesz, żeby wrócić do domu?";
				link.l3.go = "Node_237";							
			}			
		break;
		
		case "Node_235":
			dialog.text = "Och, dziękuję ci, kapitanie... Ale... wiesz, nie mam nic, czym mógłbym ci zapłacić.";
			link.l1 = "O jakiej płatności mówisz? Chodźmy zanim nas znajdą...";
			link.l1.go = "Node_240";				
		break;
		
		case "Node_240":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "20");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City));
			AddQuestUserData("JungleGirl", "sBrothelCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city + "Gen"));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
		
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			OfficersReaction("bad");
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 3.0);
			pchar.quest.EncGirl_DeliveToParents.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveToParents.win_condition.l1.location = pchar.GenQuest.EncGirl.Parents_City + "_town";
			pchar.quest.EncGirl_DeliveToParents.function = "EncGirl_DeliveToParents";
			DialogExit(); 		
		break;
		
		case "Node_236":
			dialog.text = "Och, kapitanie, wiesz, nigdy bym nie odważył się zapytać...";
			link.l1 = "Nie bój się. Wkrótce wrócę.";
			link.l1.go = "Node_239";				
		break;		
		
		case "Node_239":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "21");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);

			pchar.quest.EncGirl_GenerateBag.win_condition.l1 = "location";
			if(GetSummonSkillFromName(pchar, SKILL_FORTUNE) > rand(100))
			{
				pchar.GenQuest.EncGirl = "Bag_BrothelRoomUp";
				pchar.quest.EncGirl_GenerateBag.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_Brothel_room";
			}
			else
			{
				pchar.GenQuest.EncGirl = "Bag_BrothelRoom";
				pchar.quest.EncGirl_GenerateBag.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_SecBrRoom";
			}
			pchar.quest.EncGirl_GenerateBag.function = "EncGirl_GenerateLeatherBag";

			pchar.quest.EncGirl_GetBagFail.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.function = "EncGirl_GenQuest_GetBag";
						
			pchar.quest.EncGirl_ExitRoom.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_ExitRoom.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_ExitRoom.function = "EncGirl_ExitTavernRoom";

			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;
		
		case "Node_240_1":
			pchar.quest.EncGirl_GetBagFail.over = "yes";
			dialog.text = "Oh, już zaczynałem się martwić, że coś ci się mogło przytrafić.";
			if(CheckCharacterItem(pchar, "leather_bag"))
			{
				link.l1 = "Co mogłoby się stać? Tutaj, weź swoje rzeczy.";
				link.l1.go = "Node_241";
			}	
			else
			{
				link.l1 = "Słuchaj, nie znalazłem tam nic. Jesteś pewien, że zostawiłeś swoją torbę podróżną w pokoju randkowym?";
				link.l1.go = "Node_242";			
			}	
		break;
		
		case "Node_241":
			TakeNItems(pchar, "leather_bag", -1);
			dialog.text = "Dziękuję, "+GetSexPhrase("szlachetny kapitan","szlachetna dziewczyna")+". Nigdy nie zapomnę, co dla mnie zrobiłeś. Nie mam wiele, ale proszę, przyjmij ten amulet. Być może to właśnie ten drobiazg uratował mi życie podczas pirackiego ataku.";
			link.l1 = "Dziękuję i udanej podróży! Do widzenia teraz...";
			link.l1.go = "Node_243";
		break;
		
		case "Node_242":
			dialog.text = "Czy naprawdę znaleźli mój worek?";
			if(sti(pchar.money) >= 5000)
			{
				link.l1 = "Ile pieniędzy potrzebujesz, aby wrócić do domu?";
				link.l1.go = "Node_237";
			}
			link.l2 = "Być może tak było. Tak czy inaczej, nasze drogi rozchodzą się tutaj. Żegnaj!";
			link.l2.go = "Node_244";
		break;
		
		case "Node_243":
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			TakeNItems(pchar, pchar.GenQuest.EncGirl.item, 1);
			AddQuestRecord("JungleGirl", "23");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_244":
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			AddQuestRecord("JungleGirl", "23");
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_245":
			dialog.text = "Dzięki, kapitanie. Wiesz, trudno mi uwierzyć, że w końcu jestem w domu. Proszę, chodź ze mną, przedstawię ci moich rodziców.";
			link.l1 = "Słuchaj, "+GetSexPhrase("piękność","drogiej")+", Naprawdę nie mam na to czasu. Może innym razem?";
			link.l1.go = "Node_246";
		break;
		
		case "Node_246":
			dialog.text = "Jaka szkoda... No cóż, na razie, niech Pan Bóg nad tobą czuwa. Nie mam nic, czym mógłbym ci się odwdzięczyć, ale proszę, przyjmij ten amulet.";
			link.l1 = "Dzięki! Biegnij teraz do domu, spraw, żeby twoi rodzice byli szczęśliwi!";
			link.l1.go = "Node_247";
		break;
		
		case "Node_247":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);		
			TakeNItems(pchar, pchar.GenQuest.EncGirl.item, 1);
			AddQuestRecord("JungleGirl", "24");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl","sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl","sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City));
			CloseQuestHeader("JungleGirl");
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();			
		break;
		
		case "Node_248":
		break;
		
		case "Node_237":
			dialog.text = "Cóż, nie wiem... Być może, będę musiał czekać na przypadkową okazję. Ale nie mogę prosić cię o pieniądze.";
			if(makeint(pchar.money)>=5000)
			{
				link.l1 = "Rozumiem. Dobrze, weź 5000 pesos. To powinno wystarczyć.";
				link.l1.go = "Node_237_1";
			}
			if(makeint(pchar.money)>=25000)
			{
				link.l2 = "Rozumiem. Dobrze, weź 25000 pesos i idź do domu.";
				link.l2.go = "Node_237_2";
			}
			if(makeint(pchar.money)>=35000)
			{
				link.l3 = "Rozumiem. Dobrze, weź 35000 pesos. Powinno to wystarczyć na zakup najlepszej kabiny na statku.";
				link.l3.go = "Node_237_3";
			}
		break;
		
		case "Node_237_1":
			AddMoneyToCharacter(pchar, -5000);
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			dialog.text = "Dziękuję, "+GetSexPhrase("szlachetny kapitan","szlachetna dziewczyna")+". Nigdy nie zapomnę tego, co dla mnie zrobiłeś.";
			link.l1 = "Żegnaj, więc. Do widzenia...";
			link.l1.go = "Node_238";
			pchar.GenQuest.EncGirl = "EncGirlFack_GetMoney";
		break;
		
		case "Node_237_2":
			AddMoneyToCharacter(pchar, -25000);
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			dialog.text = "Dziękuję, "+GetSexPhrase("szlachetny kapitanie","szlachetna dziewczyna")+". Nigdy nie zapomnę, co dla mnie zrobiłeś.";
			link.l1 = "Dobry rejs, więc. Do widzenia...";
			link.l1.go = "Node_238";
		break;
		
		case "Node_237_3":
			AddMoneyToCharacter(pchar, -35000);
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			dialog.text = "Dziękuję, "+GetSexPhrase("szlachetny kapitan","szlachetna dziewczyna")+". Nigdy nie zapomnę, co dla mnie zrobiłeś.";
			link.l1 = "Dobrego rejsu, w takim razie. Do widzenia...";
			link.l1.go = "Node_238";
		break;
		
		case "Node_238":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			if(pchar.GenQuest.EncGirl == "EncGirlFack_GetMoney") 
			{
				AddSimpleRumour(RandPhraseSimple("Have you heard? A whore was trying to sneak on board of a ship without documents, but she was caught and taken back to the brothel. They say she owed the madam quite a sum.",  
				"Have you heard? A whore without documents was caught at the port. They say she had cleaned out madam's coffers before attempting to flee from the brothel. I say, that source of filth and thievery must have been closed off long ago. Our kids are even seeing this and what can they learn from such an example?"), sti(pchar.GenQuest.EncGirl.nation), 3, 1);
			}
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_250":
			dialog.text = "Nie rujnuj mi życia, kapitanie! Mój ojciec chce, żebym poślubiła syna lichwiarza, tego plugawego mleczka... tylko dlatego, że jego tatuś ma w swoich skrzyniach gówno pieniędzy! Cóż, wolałbym zostać w dżungli, aby być pożartym przez dzikie bestie, niż wziąć dożywocie z nim!";
			link.l1 = "Jaki jest problem z twoim małżeństwem, "+GetSexPhrase("piękno","drogulenko")+"? Zatrzymaj tego, który chce cię poślubić, i bądź szczęśliwa. Po pewnym czasie z radością poślubiłabyś tego mleczka, ale może być za późno...";
			link.l1.go = "Node_251";
		break;
		
		case "Node_251":
			pchar.GenQuest.EncGirl.sLoverId = GenerateRandomName(sti(npchar.nation), "man"); 
			dialog.text = "Nie! Nie, kapitanie, ja kocham "+pchar.GenQuest.EncGirl.sLoverId+" i nie wyjdę za mąż za innego mężczyznę! A mój ojciec nie chce słuchać niczego! On mówi, że "+XI_ConvertString("Colonia"+pchar.GenQuest.EncGirl.city)+" jest tutaj tylko gościem, więc nigdy nie znajdzie tu pracy, a jego przeznaczeniem jest umrzeć w biedzie, a ja razem z nim! A poszedłbym za nim na koniec świata, tylko by być u jego boku! Zabierz mnie do niego, błagam cię!";
			link.l1 = "Dobrze, idziemy. Chyba sobie poradzę, co z tobą zrobić...";
			link.l1.go = "Node_252";
		break;
		
		case "Node_252":
			Diag.TempNode = "Node_253";
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "9");
			AddQuestUserData("JungleGirl","sText", pchar.GenQuest.EncGirl.FatherGen);
			AddQuestUserData("JungleGirl","sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			AddQuestUserData("JungleGirl", "sLover", pchar.GenQuest.EncGirl.sLoverId); 
			pchar.GenQuest.EncGirl.MeetSoldiers = 2;
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_253":
			Diag.TempNode = "Node_253";
			dialog.text = "Kapitanie, obiecałeś mnie przyprowadzić do osady "+XI_ConvertString("Kolonia"+pchar.GenQuest.EncGirl.city)+".";
			link.l1 = RandPhraseSimple("Pamiętam.","Nie martw się, zabiorę cię tam.");
			link.l1.go = "exit";			
		break;
		
		case "Node_260":
			chrDisableReloadToLocation = false;
			if(rand(1) == 0)
			{
				dialog.text = RandPhraseSimple("Dziękuję, "+GetSexPhrase("kapitan","młoda dama")+", znowu. Naprawdę, jestem ci tak wdzięczny.","Dziękuję bardzo, "+GetSexPhrase("kapitan","młoda dama")+". Nie mam pojęcia, co bym zrobił bez twojej pomocy.");
				link.l1 = RandPhraseSimple("To powinna być dla ciebie nauczka. Dobrze, powodzenia...","Następnym razem powinieneś być bardziej ostrożny... Teraz biegnij do domu, mam rzeczy do zrobienia.");
				link.l1.go = "Node_260End";
				link.l2 = "Jak mogłeś być tak nieostrożny? Dlaczego poszedłeś sam do dżungli?";
				link.l2.go = "Node_13";
			}
			else
			{
				dialog.text = "Oh, "+GetSexPhrase("kapitan","młoda dama")+", Naprawdę nie mam pojęcia, jak Ci podziękować.";
				link.l1 = "To nic. Zawsze chętnie pomogę...";
				link.l1.go = "Node_261";
			}
		break;
		
		case "Node_260End":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");			
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_261":
			dialog.text = "Czy możesz mnie zabrać do karczmy? Muszę poczekać na moją ciocię i odpocząć, ta 'przygoda' wyczerpała całą moją energię...";
			link.l1 = "Nie, "+GetSexPhrase("piękność","kochanie")+", to na pewno wystarczy dla mnie. Mam dużo do zrobienia.";
			link.l1.go = "Node_262";
			link.l2 = ""+GetSexPhrase("Och, kobiety! Czy jest coś, co mogą zrobić bez pomocy mężczyzny?","Dlaczego jesteś tak bezradny?")+"Chodźmy...";
			link.l2.go = "Node_263";
		break;
		
		case "Node_262":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "", "", -1.0);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_263":
			Diag.TempNode = "Node_224";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";					
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
				
		case "ThanksForHelp_1":
			Diag.TempNode = "ThanksAgain";
			if(makeint(Pchar.reputation.nobility) >= 80)
			{
				dialog.text = "Mam trochę pieniędzy... Proszę, przyjmij to jako wyraz mojej wdzięczności!";
				Link.l1 = "Dzięki. Postaraj się być ostrożniejszy następnym razem.";
				Link.l1.go = "exit";
			}
			else 
			{
				if(hrand(1) == 0)
				{
					dialog.text = "Powiedzę wszystkim, że mnie uratowałeś! Niech każdy to wie, "+GetSexPhrase("jakim odważnym i mężnym mężczyzną jesteś","jaką odważną i dzielną damą jesteś")+"!";
					Link.l1 = "Dziękuję. A teraz powinieneś wrócić do domu.";
					Link.l1.go = "exit";
				}
				else
				{
					addMoneyToCharacter(Pchar, makeint(PChar.rank)*100);
					dialog.text = "Mam trochę pieniędzy... Proszę, przyjmij to jako znak mojej wdzięczności!";
					Link.l1 = "Dzięki. Postaraj się być ostrożniejszy następnym razem.";
					Link.l1.go = "exit";
				}
			}
		break;

		case "ThanksAgain":
            Diag.TempNode = "ThanksAgain";
            dialog.text = "Powiem wszystkim, że mnie uratowałeś! Niech wszyscy wiedzą, "+GetSexPhrase("jakim odważnym i mężnym mężczyzną jesteś","jaką odważną i mężną damą jesteś")+"!";
			Link.l1 = "Dziękuję. A teraz powinieneś wrócić do domu.";
			Link.l1.go = "exit";
		break;
	}
}

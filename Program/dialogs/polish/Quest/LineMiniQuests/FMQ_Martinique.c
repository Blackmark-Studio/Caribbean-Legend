// Addon-2016 Jason, французские миниквесты (ФМК) Мартиника
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Oczywisty błąd. Powiedz o tym deweloperom.";
			link.l1 = "O, zrobię to.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// квестодатель
		case "carpenter":
			DelMapQuestMarkCity("Fortfrance");
			LAi_SetImmortal(npchar, false);
			npchar.lifeday = 0;
			DelLandQuestMark(npchar);
			dialog.text = TimeGreeting()+", kapitanie. Pozwól, że się przedstawię - "+GetFullName(npchar)+". Chociaż spotkaliśmy się już niedawno, wątpię, czy mnie zapamiętałeś.";
			link.l1 = "Witam, monsieur. A gdzież to mogłem cię wcześniej widzieć?";
			link.l1.go = "carpenter_1";
		break;
		
		case "carpenter_1":
			sTemp = "lugier 'Adeline'";
			if (pchar.questTemp.Sharlie.Ship == "sloop") sTemp = "slupa 'Black Dog'";
			dialog.text = "W naszej stoczni. Zakupiłeś "+sTemp+"  Pamiętasz teraz? Jestem tam cieślą.";
			link.l1 = "Tak, rzeczywiście kupiłem tam statek. Więc czego chcesz, monsieur "+GetFullName(npchar)+"?";
			link.l1.go = "carpenter_2";
		break;
		
		case "carpenter_2":
			sld = characterFromId("FortFrance_shipyarder");
			AddLandQuestMark(sld, "questmarkmain");
			dialog.text = "Nasz szkutnik - "+GetFullName(sld)+", chce z tobą porozmawiać. Wierzę, że ma jakiś interes do zaproponowania. Zobaczył twój statek w naszym porcie i wysłał mnie, bym cię odnalazł. Czy uprzejmie przyjmiesz zaproszenie?";
			link.l1 = "Dobrze. Odwiedzę twojego szefa, gdy tylko skończę moje sprawy w mieście.";
			link.l1.go = "carpenter_3";
		break;
		
		case "carpenter_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload5_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;
			pchar.questTemp.FMQM = "begin";
			AddQuestRecord("FMQ_Martinique", "1");
			SetFunctionTimerCondition("FMQM_Denial", 0, 0, 2, false);
		break;
		
		case "officer":
			PlaySound("Voice\English\soldier_arest_4.wav");
			dialog.text = "Ha, ha... Świeży przemytnicy w mojej sieci!";
			link.l1 = "Przepraszam co? To chyba jakaś pomyłka...";
			link.l1.go = "officer_1";
		break;
		
		case "officer_1":
			dialog.text = "Przestań pieprzyć! W tej stoczni jest kilka beczek żywicy. Kapitanie, dostarczyłeś je swojemu wspólnikowi w zbrodni. Oboje jesteście aresztowani, dodatkowo konfiskuję ładunek w imię prawa!";
			link.l1 = "Niemożliwe...";
			link.l1.go = "officer_2";
		break;
		
		case "officer_2":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FortFrance_shipyarder");
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "officer_3":
			dialog.text = "Nie udawaj głupiego, panie! Jakie beczki? Wiesz, że mówię o tych samych beczkach, które niedawno wyładowałeś ze statku tego żeglarza! Obaj zgnijecie w lochach! Ruszajcie się, łajdaki...";
			link.l1 = "";
			link.l1.go = "officer_4";
		break;
		
		case "officer_4":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FortFrance_shipyarder");
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "officer_5":
			PlaySound("Voice\English\soldier\soldier arest-02.wav");
			dialog.text = "Ta żywica, mój drogi mistrzu szkutniku, to dobro o strategicznej wartości, które jest pod bezpośrednią kontrolą naszego gubernatora! Skoro twierdzisz, że jest całkowicie twoja - masz ją na swoje życzenie. Jesteś aresztowany, spędzisz tę noc w naszych wygodnych lochach, a jutro dasz nam szczegółowy raport o tym, jak ją zdobyłeś i w jakim celu. Nie martw się, w końcu wszystkiego się dowiemy. Ty, kapitanie, możesz odejść. To twój szczęśliwy dzień.";
			link.l1 = "";
			link.l1.go = "officer_6";
		break;
		
		case "officer_6":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToCharacter(pchar, characterFromID("FMQM_officer"));
			sld = characterFromId("FortFrance_shipyarder");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "FortFrance_town", "officers", "reload5_3", "FMQM_ArestContinue", 8);
		break;
		
		case "officer_7":
			PlaySound("Voice\English\soldier_arest_2.wav");
			dialog.text = "Wiedziałem, że coś jest nie tak z tym statkiem... Wygląda na to, że cię nie doceniłem, kapitanie.";
			link.l1 = "Dokładnie, poruczniku. Nie jestem aż tak głupi. Twoja owocna współpraca ze szkutnikiem jest teraz zagrożona.";
			link.l1.go = "officer_8";
			DelLandQuestMark(npchar);
		break;
		
		case "officer_8":
			dialog.text = "Rozumiem. Gratulacje, musisz być utalentowany, skoro udało ci się mnie wytropić i zaskoczyć. Teraz powiedz mi, czego chcesz.";
			link.l1 = "Czy to nie jest jasne? Potrzebuję z powrotem mojej żywicy. Tej żywicy, którą ty i twój kumpel mi ukradliście.";
			link.l1.go = "officer_9";
		break;
		
		case "officer_9":
			dialog.text = "Dobrze. Możesz to mieć, ale tylko połowę twojej partii. To wszystko, co mam tutaj schowane. Mam nadzieję, że ci to wystarczy, gdyż to wszystko, co mogę zaoferować.";
			link.l1 = "Jeszcze próbujesz mnie oszukać? Wynagrodź mi drugą połowę złotem lub towarami ukrytymi za tobą.";
			link.l1.go = "officer_10";
		break;
		
		case "officer_10":
			dialog.text = "Nie ma mowy. Zwróć się do naszego wspólnego przyjaciela po drugą połowę.";
			link.l1 = "Chyba sobie kurwa żartujesz? Naprawdę w to wierzysz, że "+GetFullName(characterFromId("FortFrance_shipyarder"))+" odda mi moje beczki? To absurd.";
			link.l1.go = "officer_11";
		break;
		
		case "officer_11":
			dialog.text = "Kapitanie, weź całą żywicę, którą mam, zachowaj swoje życie i wynoś się stąd. Mogę dodać do tej umowy moją obietnicę, że nie sprawię ci kłopotów w St. Pierre. To moja ostateczna oferta.";
			link.l1 = "Od kiedy to moje życie jest częścią umowy? Ha!";
			link.l1.go = "officer_12";
		break;
		
		case "officer_12":
			dialog.text = "Wygląda na to, że wciąż czujesz się niezwyciężony po walce, kapitanie. Pozwól, że ci to wyjaśnię: to byli nowicjusze, niewyszkoleni i bez motywacji, nie masz szans przeciwko mojej drużynie. Mógłbym cię tu teraz zabić bez żadnych negocjacji, ale cenię sobie życie moich ludzi. Ktoś z nich mógłby zostać ranny lub nawet zabity podczas zabijania ciebie. Więc albo zaakceptujesz moją hojność, albo zostaniesz tutaj na zawsze. Czas na wybór.";
			link.l1 = "Do diabła z tobą, poruczniku, ale jestem zmuszony przyjąć twoje warunki. Jestem tu znacznie słabszy.";
			link.l1.go = "officer_13";
			link.l2 = "Zbyt pewny siebie, poruczniku? Sądzę, że powinienem nauczyć ciebie i twoich najemników lekcji. Ty pieprzony żywiczny psie!";
			link.l2.go = "officer_15";
		break;
		
		case "officer_13":
			dialog.text = "Jesteś rozsądnym człowiekiem, kapitanie. Weź swoje beczki i znikaj. Powinienem cię ostrzec, że oskarżanie mnie przed gubernatorem nic nie da. Dziś zmienię miejsce mojego składu. Oszczędź swój czas.";
			link.l1 = "Nie miałem zamiaru. Rozumiem bezcelowość zwracania się do władz.";
			link.l1.go = "officer_14";
		break;
		
		case "officer_14":
			dialog.text = "Pośpiesz się, nie mam wiele czasu do stracenia.";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQM_PeaceExit");
		break;
		
		case "officer_15":
			DialogExit();
			AddDialogExitQuestFunction("FMQM_BattleExit");
		break;
		
		case "greguar":
			PlaySound("Voice\English\LE\Greguar\Greguar_02.wav");
			dialog.text = "O! Co za spotkanie! Witam, monsieur! Czyżby wspaniała noc?";
			link.l1 = "Dobry wieczór... ach, to ty! Pamiętam cię, spotkaliśmy się w sam pierwszy dzień mojego przybycia na Karaiby. Monseniour Gregoire Valinnie.";
			link.l1.go = "greguar_1";
		break;
		
		case "greguar_1":
			dialog.text = "Cieszę się, że wciąż pamiętasz. Widzę, że teraz jesteś kapitanem, panie "+GetFullName(pchar)+". Gratulacje.";
			link.l1 = "Dzięki...";
			link.l1.go = "greguar_2";
		break;
		
		case "greguar_2":
			dialog.text = "Wyglądasz na zmartwionego, kapitanie. Co tu się stało? Coś nie tak?";
			link.l1 = "Coś jest bardzo nie tak...";
			link.l1.go = "greguar_3";
		break;
		
		case "greguar_3":
			dialog.text = "Panie, zamiast stać na środku ulicy, chodźmy do karczmy. Przydałby ci się kufel albo dwa. Tam możemy porozmawiać. Chodź!";
			link.l1 = "Dobrze więc...";
			link.l1.go = "greguar_4";
		break;
		
		case "greguar_4":
			DialogExit();
			NextDiag.CurrentNode = "greguar_5"; 
			FreeSitLocator("Fortfrance_tavern", "sit_front4");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Fortfrance_tavern", "sit", "sit_front4", "FMQM_InTavern", -1);
		break;
		
		case "greguar_5":
			LAi_SetSitType(Pchar);
			dialog.text = "Nalej, kapitanie...";
			link.l1 = "No to spróbujmy...";
			link.l1.go = "greguar_6";
		break;
		
		case "greguar_6":
			LAi_Fade("", "");
			WaitDate("",0,0,0,1,20);
			RecalculateJumpTable();
			dialog.text = "Uch... Teraz proszę, powiedz mi, co się stało? Wyglądasz jak ten facet, którego powiesili w zeszłym tygodniu. Miał dokładnie tę samą minę, stojąc na szubienicy.";
			link.l1 = "Widzisz, monsieur Gregoire... Powiedzmy, że mam problemy z pracą.";
			link.l1.go = "greguar_7";
		break;
		
		case "greguar_7":
			dialog.text = "Kapitanie, możesz mi powierzyć wszystko. Nie zamierzam cię wydać gubernatorowi ani komendantowi, możesz mi na tym zaufać. Czy mi nie ufasz?";
			link.l1 = "Ufam ci, monseniour.";
			link.l1.go = "greguar_8";
		break;
		
		case "greguar_8":
			dialog.text = "W takim razie wyznaj swe grzechy i ulżyj duszy. Może będę w stanie ci pomóc.";
			link.l1 = "Lokalny budowniczy statków wynajął mnie, bym splądrował hiszpańską karawanę, która wyruszyła z Trynidadu. Miał pilną potrzebę żywicy, to był mój cel i obiecał zapłacić piętnaście dublonów za beczkę. Śledziłem karawanę, splądrowałem ją i przywiozłem towary tutaj. Oddali mój statek do naprawy i rozładowali beczki do stoczni. Mieliśmy już kończyć nasz interes, gdy pojawił się ten oficer... Zastanawiam się, jak mógł się o tym dowiedzieć?";
			link.l1.go = "greguar_9";
		break;
		
		case "greguar_9":
			dialog.text = "";
			link.l1 = "To było to, mieli nas. Chyba powinienem oddać uznanie szkutnikowi - wziął całą winę na siebie, powiedział im, że żywica to jego własność i nie mam z tym nic wspólnego. W końcu został aresztowany, a moje monety przepadły. Bałagan z hiszpańską karawaną był stratą czasu i pieniędzy, choć miałem szczęście, że nie skończyłem w więzieniu. Nalej jeszcze raz, monsieur Gregoire.";
			link.l1.go = "greguar_10";
		break;
		
		case "greguar_10":
			dialog.text = "Więc, budowniczy statków został aresztowany?";
			link.l1 = "Cóż, tak. Został zabrany do więzienia przez tego samego oficera, o którym mówiłem. Powinieneś ich był zobaczyć.";
			link.l1.go = "greguar_11";
		break;
		
		case "greguar_11":
			dialog.text = "Tak, widziałem ich oboje, chociaż nie miałem pojęcia, że porucznik Felicien Gronier mógłby aresztować swego starego przyjaciela.";
			link.l1 = "Co... co ty właśnie powiedziałeś?";
			link.l1.go = "greguar_12";
		break;
		
		case "greguar_12":
			dialog.text = "Dobrze słyszałeś. Porucznik Felicien Gronier i stoczniowiec "+GetFullName(characterFromId("FortFrance_shipyarder"))+" są starymi przyjaciółmi. Kiedyś razem służyli w armii w Europie. Gronier pozostał w wojsku a "+GetFullName(characterFromId("FortFrance_shipyarder"))+" zdołał rozpocząć własny interes.";
			link.l1 = "Czyli się znają... Teraz rozumiem...";
			link.l1.go = "greguar_13";
		break;
		
		case "greguar_13":
			dialog.text = "Mój drogi panie "+pchar.name+", wygląda na to, że został pan oszukany. Nadal jest pan tu nowicjuszem i oni to wykorzystali. Założę się o sto dublonów, że monsieur "+GetFullName(characterFromId("FortFrance_shipyarder"))+" będzie znowu krążył po swojej stoczni za trzy dni lub mniej.";
			link.l1 = "Wydaje się, że masz rację, monsieur. Oszukali mnie. Nie ma szans, by ten oficer wiedział o żywicy. Nie wspomne już o idealnym wyczuciu czasu.";
			link.l1.go = "greguar_14";
		break;
		
		case "greguar_14":
			dialog.text = "To są Karaiby, monseniour "+pchar.name+". Przyzwyczaj się do tego. Zapomnij o wyglądzie, najgorsza hołota tutaj zawsze wygląda jak szlachetny dostojnik.";
			link.l1 = "Słyszałem już tę kwestię gdzieś wcześniej... Co powinienem z nimi zrobić? Powinienem zwrócić się do gubernatora?";
			link.l1.go = "greguar_15";
		break;
		
		case "greguar_15":
			dialog.text = "Obawiam się, że w tym przypadku "+GetFullName(characterFromId("FortFrance_shipyarder"))+" opowie im inną historię, a ty skończysz w więzieniu.";
			link.l1 = "Zrozumiałe. No cóż! Skoro prawo nie jest po mojej stronie, zrobię to po swojemu, do diabła! Nie zamierzam się tak po prostu poddać.";
			link.l1.go = "greguar_16";
		break;
		
		case "greguar_16":
			dialog.text = "Proszę, uspokój się "+pchar.name+". Gniew i rum za ciebie przemawiają w tym momencie. Prześpij się, a potem przemyśl to jeszcze raz. Może najlepiej będzie, jeśli to odpuścisz. Porucznik Felicien Gronier i "+GetFullName(characterFromId("FortFrance_shipyarder"))+" są tu potężnymi ludźmi, są daleko poza twoją ligą. Nie rób nic głupiego.";
			link.l1 = "Zobaczymy. Dziękuję za oświecenie mnie. Dobrze, że cię spotkałem.";
			link.l1.go = "greguar_17";
		break;
		
		case "greguar_17":
			dialog.text = "Bądź ostrożny. Pamiętaj, co ci powiedziałem.";
			link.l1 = "Będę. A teraz napijmy się jeszcze raz!";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQM_OutTavern");
		break;
		
		case "greguar_18":
			PlaySound("Voice\English\LE\Greguar\Greguar_03.wav");
			dialog.text = "Kapitan "+GetFullName(pchar)+"!";
			link.l1 = "O, monsieur Gregoire! Znowu ty!";
			link.l1.go = "greguar_19";
		break;
		
		case "greguar_19":
			dialog.text = "Tak. Po naszej rozmowie w karczmie zrobiłem rozeznanie w sprawie porucznika Feliciena Groniera. Okazało się, że niedawno poprosił o dziesięciodniowy urlop. Jego prośba została zatwierdzona. Widziałem go dzisiaj, wsiadł do łodzi i popłynął do tartany, która wkrótce odpłynęła na Gwadelupę. Nazywa się 'Topaz'.\nPowiedziałem ci wszystko, teraz to twoja decyzja. Jestem pewien, że dostrzegasz schemat nagłej prośby Groniera o urlop i odpłynięcia z wyspy na świeżo zbudowanej tartanie.";
			link.l1 = "Cholera, teraz to dla mnie jasne jak słońce, to na pewno! Ta tartana ma moją żywicę w ładowni! Monseniour Gregoire, dziękuję, naprawdę się spisałeś! Czy jest coś, co mógłbym dla ciebie zrobić w zamian?";
			link.l1.go = "greguar_20";
		break;
		
		case "greguar_20":
			dialog.text = "Och, no weź, przyjacielu. Jesteśmy szlachcicami, powinniśmy sobie pomagać. Tak to się żyje. Wierzę, że zrobiłbyś to samo, gdybym był na twoim miejscu. Nie trać ani minuty, żegluj na północ i znajdź oficera. Nie angażuj się w walkę, po prostu go śledź i dowiedz się, co planuje. Pospiesz się, kapitanie!";
			link.l1 = "Dziękuję raz jeszcze!";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQM_HurryToSea");
		break;
		
		case "pirate":
			dialog.text = "Na co się gapisz? Czego tu szukasz?";
			link.l1 = "Hej, kolego, szukam swoich fantów. Widzisz te beczki tam? To moja żywica, za którą nie zapłacili mi ani grosza.";
			link.l1.go = "pirate_1";
			DelLandQuestMark(characterFromId("FMQM_Enemy_crew_2"));
		break;
		
		case "pirate_1":
			dialog.text = "Jesteś idiotą czy coś? Zmykaj, póki jeszcze możesz!";
			link.l1 = "Zadałem sobie zbyt wiele trudu, aby zdobyć tę żywicę, by pozwolić kilku plugawym szumowinom mnie powstrzymać.";
			link.l1.go = "pirate_2";
		break;
		
		case "pirate_2":
			dialog.text = "Tu pochowamy twój elegancki strój!";
			link.l1 = "O, jakże miło z twojej strony zasugerować pochówek, ale obawiam się, że po prostu zostawimy cię tutaj na plaży, a mewy zjedzą twoje wnętrzności!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQM_ShoreFight");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

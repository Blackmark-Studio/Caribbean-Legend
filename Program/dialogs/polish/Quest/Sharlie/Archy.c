// Арчибальд Колхаун
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Czy czegoś potrzebujesz?";
			link.l1 = "Nie, nic.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "portroyal":
			dialog.text = "Ha, Monsieur de Maure! Witaj w Port Royal! Czy nadal mnie pamiętasz?";
			link.l1 = "Hmm... Ty jesteś Calhoun, prawda? Henry Calhoun?";
			link.l1.go = "portroyal_1";
		break;
		
		case "portroyal_1":
			dialog.text = "Prawie... Archibald Calhoun.";
			link.l1 = "Och, wybacz mi, Monsieur. Tak, pamiętam cię. Spotkaliśmy się na Przylądku Catoche, w zatoce. Twój kapitan był z tobą, William Patterson. Rozpoznałem jego eskadrę.";
			link.l1.go = "portroyal_2";
		break;
		
		case "portroyal_2":
			dialog.text = "To prawda! Proszę wybaczyć mojemu kapitanowi. Zawsze jest niegrzeczny wobec osób, których nie zna. Wykonałeś świetną robotę, szturmując fort Diego de Montoya, nad którym przypadkiem ostrzyliśmy sobie pazury...";
			link.l1 = "To dla sprawiedliwości, muszę dodać, że bez wstępnych przygotowań pokazanych przez waszego kapitana, wątpię, bym w ogóle mógł dotrzeć do zysków, będąc pod ostrzałem hiszpańskich dział. Czy wasz dowódca znalazł to, czego szukał?";
			link.l1.go = "portroyal_3";
		break;
		
		case "portroyal_3":
			dialog.text = "Tak. Zagrzebał się głęboko w kazamatach pod fortem i znalazł jakiś archiwum. Był niewypowiedzianie zadowolony. A tak przy okazji, jeśli nie masz nic przeciwko, co cię skłoniło do ataku na ten fort w dżungli?";
			link.l1 = "Po tym, jak pokonałem Don Diego w Saint-Pierre, zaczął on knuć intrygi i w końcu zorganizował na mnie otwarty atak na Kubię. Potem przerwał walkę i uciekł w góry w stronę lądu. Cóż, postanowiłem raz na zawsze pozbyć się tego tchórzliwego psa, by nigdy więcej nie zhańbił Francuzów.";
			link.l1.go = "portroyal_4";
		break;
		
		case "portroyal_4":
			dialog.text = "Właśnie, słyszałem niemało legendarnych opowieści o bohaterskich czynach kapitana Charlesa de Maure. Teraz widziałem to na własne oczy...";
			link.l1 = "Tak, słyszałem kilka rzeczy o męstwie Williama Pattersona. Masz szczęście, że masz takiego kapitana.";
			link.l1.go = "portroyal_5";
		break;
		
		case "portroyal_5":
			dialog.text = "Szczęśliwy ja, to prawda. Choć stał się teraz tak ważnym człowiekiem, człowiekiem wysokiego społeczeństwa, audiencji, balów, parad i prywatnych przyjęć... Nie można go wyciągnąć z pałacu gubernatora, kiedy tylko przybywamy do Port Royal. Właściwie to jest tam znowu właśnie teraz. \nKapitanie Charles de Maure, możesz wyświadczyć przysługę szkockiemu pijakowi? Dołącz do mojego towarzystwa i porozmawiajmy! Mam dość ciągle widywania tych samych twarzy, a ty wydajesz się być dobrą osobą do rozmowy. Przyjdź do mnie, zrelaksujmy się i napijmy się beczki doskonałej whisky. Ja stawiam!";
			link.l1 = "Hm... Kuszące, ale...";
			link.l1.go = "portroyal_6";
		break;
		
		case "portroyal_6":
			dialog.text = "Och przestań, Kapitanie, ty też musisz czasem odpocząć. Mam przy okazji trochę wykwintnych przekąsek, prosto ze sklepu miejscowego kupca. Wynajmuję pokój tuż nad sklepem. Kiedy tylko zechcesz coś zjeść lub się napić, po prostu zejdź na dół i wszystko będzie gotowe, haha! Wygodne, prawda? Chodźmy, ruszajmy!";
			link.l1 = "Przekonałeś mnie do tego!";
			link.l1.go = "portroyal_7";
		break;
		
		case "portroyal_7":
			dialog.text = "Świetnie. Chodź za mną!";
			link.l1 = "...";
			link.l1.go = "portroyal_8";
		break;
		
		case "portroyal_8":
			DialogExit();
			NextDiag.CurrentNode = "portroyal_9";
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload6_back", "PortRoyal_store", "goto", "goto2", "GuardOT_ArchyIntoStore", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "portroyal_9":
			LAi_SetSitType(Pchar);
			dialog.text = "Widzisz, jak tu miło? Przyjemnie i chłodno... Oto beczki z whisky! Do dna, Kapitanie!";
			link.l1 = "Cóż, wypijmy za nasze szczęśliwe spotkanie i miłą znajomość!";
			link.l1.go = "portroyal_10";
		break;
		
		case "portroyal_10":
			dialog.text = "Zachwycony!... Ach! Niedawno przybyłeś na Karaiby, prawda, Monsieur de Maure?";
			link.l1 = "Stosunkowo niedawno... a może wcale nie tak niedawno. Nie wiem, jak to ująć. Czuję, jakbym spędził tutaj połowę życia.";
			link.l1.go = "portroyal_11";
		break;
		
		case "portroyal_11":
			dialog.text = "Och, znam to uczucie... Choć sam jestem tu już od dłuższego czasu. A kiedy wylądowałem na tej przeklętej wyspie, z której uratował mnie William... Ohoo, z pewnością czułem się, jakbym tam pożegnał połowę swojego życia.";
			link.l1 = "Interesujące! Co to była za wyspa?";
			link.l1.go = "portroyal_12";
		break;
		
		case "portroyal_12":
			dialog.text = "Willy jest moim starym przyjacielem, znaliśmy się jeszcze, gdy oddychałem świeżym powietrzem Szkocji... Dobre czasy. Byłem na tyle głupi, żeby wdać się w kłótnię z przeklętymi papistami i samym inkwizytorem, więc zorganizował na mnie zamach. Byłem wtedy kupcem, miałem swoją własną fluitę.\nEh, tego przeklętego dnia mój statek został zaatakowany przez Hiszpanów, przebranych za piratów. Walczyliśmy dzielnie, ale udało im się nas osaczyć jak szczurów! Nawet wtedy stary Calhoun nie stracił głowy i skoczył za burtę z beczką wody i kilkoma deskami.\nWykorzystałem ciemność i odpłynąłem z mojego statku, niezauważony przez żołnierzy. Szanse na przeżycie nie były zbyt dobre, ale pozostanie na statku oznaczało brak szans w ogóle. Dwa dni później wyrzuciło mnie na brzeg jakiejś bezludnej wyspy.\nMieszkałem na Karaibach już jakiś czas, a jednak nigdy wcześniej o niej nie słyszałem! Jest mała i całkowicie niezamieszkana... i spędziłem tam dwa lata, które wydawały się wiecznością. Nadal nie wiem, jak udało mi się zachować zdrowy rozum.";
			link.l1 = "Mieszkałeś dwa lata na bezludnej wyspie?";
			link.l1.go = "portroyal_13";
		break;
		
		case "portroyal_13":
			dialog.text = "Tak zrobiłem, przeklęte miejsce! Dobrze, że była tam świeża woda. Żywiłem się krabami, pąklami, rybami i ptakami. Dlatego nazwałem to miejsce Wyspą Krabów. Nie miałem żadnej broni, więc opanowałem harpun, włócznię i strzałę jak dziki człowiek! Ohoo! Pij, pij, Kapitanie! Nie mam nic przeciwko temu, bym także zwilżył swój gwizdek...";
			link.l1 = "Tak... Nie zazdroszczę ci.";
			link.l1.go = "portroyal_14";
		break;
		
		case "portroyal_14":
			dialog.text = "Oto i jest! Dokładnie to powiedziałem, gdy po raz pierwszy stanąłem na plaży tego wielkiego kawałka piasku: 'Stary Archy, twoja sytuacja nie jest godna pozazdroszczenia, ale też nie jest beznadziejna!' I wiesz, co mnie utrzymało przy życiu, Kapitanie?";
			link.l1 = "Statek przepływający obok wyspy?";
			link.l1.go = "portroyal_15";
		break;
		
		case "portroyal_15":
			dialog.text = "Nie! Praca mnie ocaliła! Praca, wiara i chęć życia! Zwiedziłem całą wyspę, każdy jej zakątek, i zostałem nagrodzony skrzynią pełną narzędzi ciesielskich, przyborów do pisania i innych drobiazgów. Wiesz, co sobie wtedy powiedziałem? Lej więcej, Kapitanie, tylko lej!\nPowiedziałem: Archie, musisz pracować, aby utrzymać umysł w ryzach, a Bóg dał ci wszystko, by to zacząć robić. Teraz widzisz! Zacząłem budować dom blisko zatoki i wiesz co? To mnie uratowało od złych myśli i dało powód do życia!";
			link.l1 = "„Jesteś żywym natchnieniem, panie Calhoun. Nie każdy człowiek zdołałby cokolwiek zrobić, jeśli w ogóle coś, w takiej sytuacji...”";
			link.l1.go = "portroyal_16";
		break;
		
		case "portroyal_16":
			dialog.text = "Tak, stary Calhoun urodził się w Szkocji z jakiegoś powodu! Racja! Jesteśmy synami gór - silni, odważni i twardzi, o wiele lepsi niż te piórka z bagien. Nalej więcej... Tak, o czym to mówiłem? Tak! Ciężko pracowałem i zbudowałem sobie przyzwoity dom. Zacząłem też dziennik na codzienne zapiski o moich nieszczęściach. Wziąłem go ze sobą, gdy Willy mnie uratował.\nTeraz trzymam go tutaj na stole i czytam ponownie w ciepłym, miękkim łóżku za każdym razem, gdy jesteśmy w Port Royal.\nZapisałem w nim wszystko, co mi się przytrafiło przed i po tym, jak tam dotarłem. To jeden z powodów, dla których nadal mam zdrowe zmysły.";
			link.l1 = "Okazuje się, że pan Patterson zabrał cię z wyspy? Ale jak mógł ją znaleźć? Mówiłeś...";
			link.l1.go = "portroyal_17";
		break;
		
		case "portroyal_17":
			dialog.text = "Tak, tak, wyspa nie jest zaznaczona na żadnej mapie. Ale Willy, to stary Willy! On potrafi wszystko! I znalazł tę przeklętą wyspę i mnie uratował, i za to będę mu wdzięczny do końca mojego życia. Tak...";
			link.l1 = "Czy lubisz służyć panu Pattersonowi? Czy chciałbyś ponownie działać na własny rachunek?";
			link.l1.go = "portroyal_18";
		break;
		
		case "portroyal_18":
			dialog.text = "Dość tej niezależności. Willy jest młody i odnosi sukcesy, a ja jestem jego długoletnim przyjacielem. Czego więcej mi trzeba? Nie, będę z Willym do końca swoich dni, albo przynajmniej dopóki mnie nie wyrzuci następnym razem, gdy się upiję, haha! A skoro o upijaniu mowa, nalej jeszcze!";
			link.l1 = "Akh... (pijąc) Powiedz mi, panie Calhoun. Słyszałem, że byłeś, uh, poszukiwaczem skarbów. Czy to prawda, czy tylko bzdury?";
			link.l1.go = "portroyal_19";
		break;
		
		case "portroyal_19":
			dialog.text = "Kto ci to powiedział? Cóż, nie ma sensu próbować tego ukrywać. Kiedyś byłem jednym z nich. Nie skończyło się to jednak dobrze, dokładnie to poszukiwanie skarbów doprowadziło mnie do cholernych jezuitów i wyspy. Święci ojcowie zamęczyli człowieka na śmierć z mojego powodu, a ja sam... och, zostawmy przeszłość w przeszłości.\nZapłaciłem już wystarczająco za swoje grzechy i mam nadzieję, że nigdy ich nie powtórzę w przyszłości. Nie, Willy na to nie pozwoli, jestem tego pewien!";
			link.l1 = "Słuchaj, Archibaldzie. Czy kiedykolwiek słyszałeś o człowieku imieniem Miguel Dichoso?";
			link.l1.go = "portroyal_20";
		break;
		
		case "portroyal_20":
			dialog.text = "Nie słyszałem wcześniej tego imienia. Kim on jest?";
			link.l1 = "Ach, nikim ważnym... tylko człowiek, który lubi poszukiwać przygód i skarbów. Ale skoro o nim nie słyszałeś, nie będziemy o nim mówić.";
			link.l1.go = "portroyal_21";
		break;
		
		case "portroyal_21":
			dialog.text = "Tak, nie rozmawiajmy o tym! Porozmawiajmy o starej Europie zamiast tego! Pamiętam, dwadzieścia lat temu w Szkocji...";
			link.l1 = "...";
			link.l1.go = "portroyal_22";
		break;
		
		case "portroyal_22":
			DialogExit();
			AddDialogExitQuest("GuardOT_MCOutFromArchyRoom");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

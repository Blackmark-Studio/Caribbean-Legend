void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "To zdecydowanie błąd. Czy możesz proszę poinformować Jasona, kiedy i jak to się stało.";
			link.l1 = "Zrobię to.";
			link.l1.go = "exit";
		break;
		
		// шаман карибов Туттуатхапак
		case "Tuttuat":
			dialog.text = "Dlaczego przyszedłeś do mojej chaty, biały człowieku? Tuttuathapak nie myśli, że jesteś jego drogim gościem.";
			if (GetCharacterFreeItem(pchar, "mushket1") || GetCharacterFreeItem(pchar, "mushket2") || GetCharacterFreeItem(pchar, "mushket7"))
			{
				link.l1 = "Witaj, wielki szamanie Tuttuathapak. Przyszedłem do ciebie, by prosić o twoją pomoc i radę. Proszę, przyjmij ten muszkiet jako dowód mojej dobrej woli.";
				link.l1.go = "Tuttuat_1";
			}
			else
			{
				link.l1 = "Witaj, wielki szamanie Tuttuathapak. Przyszedłem do ciebie, by szukać twej pomocy i rady.";
				link.l1.go = "Tuttuat_exit";
			}
		break;
		
		case "Tuttuat_exit":
			dialog.text = "Tuttuathapak nie pomoże białemu człowiekowi. Biali ludzie to źli ludzie. Oni zabijają i podbijają Indian, czynią Indian niewolnikami. Tuttuathapak nie daje białemu człowiekowi żadnej rady. Ty teraz odejdź.";
			link.l1 = "Hmm...";
			link.l1.go = "Tuttuat_exit_1";
		break;
		
		case "Tuttuat_exit_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat";
		break;
		
		case "Tuttuat_1":
			if (GetCharacterFreeItem(pchar, "mushket1")) 
			{
				sTemp = "mushket1";
			}
			else 
			{
				if(GetCharacterFreeItem(pchar, "mushket2"))
				{
					sTemp = "mushket2";
				}
				else
				{
					sTemp = "mushket7";
				}
			}
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			Log_Info("You have given: "+XI_ConvertString(sTemp)+"");
			dialog.text = "Wiesz, co dać Tuttuathapakowi, białasie. Tuttuathapak przyjmuje twój dar. On przemówi. Jakiej rady ode mnie szukasz?";
			link.l1 = "Słyszałem, że przybyłeś z odległego miejsca na południu. Mam indiański amulet, a jeden znawca powiedział mi, że możesz wiedzieć, jak go użyć.";
			link.l1.go = "Tuttuat_2";
			DelLandQuestMark(npchar);
			DelMapQuestMarkIsland("Dominica");
		break;
		
		case "Tuttuat_2":
			dialog.text = "Pokaż amulet.";
			link.l1 = "Oto, wielki szamanie.";
			link.l1.go = "Tuttuat_3";
		break;
		
		case "Tuttuat_3":
			PlaySound("interface\important_item.wav");
			dialog.text = "(patrząc na amulet)... Twój przyjaciel mówi prawdę, biały człowieku. Ten amulet należy do mojego ludu, wielkich Indian, Chavin ich imię było. Przeklęty bluźnierczy blady pies zbezcześcił świątynię i zabrał go tutaj. Tuttuathapak ukarał tego psa.";
			link.l1 = "Odebrałeś mu rozum, jak mniemam?";
			link.l1.go = "Tuttuat_4";
		break;
		
		case "Tuttuat_4":
			dialog.text = "Białoskóry człowiek zaskoczył Tuttuathapaka swoją wiedzą. Tak, pożeram umysł tego szkorbutnego psa. On i jego plugawi ludzie dostaną to, na co zasłużyli.";
			link.l1 = "Widzę... Powiedz mi, szamanie, do czego służy ten amulet? Może chronić w bitwie lub odpędzać złą magię?";
			link.l1.go = "Tuttuat_5";
		break;
		
		case "Tuttuat_5":
			dialog.text = "Ten amulet nie jest ci potrzebny, biały kapitanie. Nie możesz użyć jego mocy. Tylko wielcy szamani naszego plemienia wiedzą, jak go obudzić.";
			link.l1 = "Hmm... Więc okazuje się, że wyruszyłem w tak długą podróż na próżno. Ale może ty potrafisz obudzić moc tego amuletu, wielki szamanie? Z pewnością moglibyśmy dojść do porozumienia...";
			link.l1.go = "Tuttuat_6";
		break;
		
		case "Tuttuat_6":
			dialog.text = "  Nawet   jeśli   obudzę   amulet,   nie   utrzymasz   jego   mocy   długo.   Ale   oferuję   ci   układ,   białas.  ";
			link.l1 = "Jaki rodzaj umowy?";
			link.l1.go = "Tuttuat_7";
		break;
		
		case "Tuttuat_7":
			dialog.text = "Trzy amulety takie jak ten zostały zabrane z naszej świątyni. Mają różne moce, ale jeśli zostaną połączone, będą bardzo, bardzo potężne. Znajdź wszystkie trzy amulety i przynieś je do mnie, a ja cię nagrodzę. Dam ci moc, którą będziesz mógł zatrzymać na zawsze.";
			link.l1 = "Nie całkiem rozumiem... O jakiej mocy mówisz?";
			link.l1.go = "Tuttuat_8";
		break;
		
		case "Tuttuat_8":
			dialog.text = "Wszystko poznasz w odpowiednim czasie. Znajdź i przynieś mi wszystkie trzy amulety. Są na Karaibach. Poszukaj i znajdź. Rozpoznasz je łatwo - wyglądają podobnie. Idź, biały człowieku. Tuttuathapak czeka i prosi duchy, by ci pomogły.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_9";
		break;
		
		case "Tuttuat_9":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_10";
			pchar.questTemp.Caleuche = "ghostship"; 
			AddQuestRecord("Caleuche", "3");
			pchar.quest.Caleuche_ghostship.win_condition.l1 = "location";
			pchar.quest.Caleuche_ghostship.win_condition.l1.location = "Dominica";
			pchar.quest.Caleuche_ghostship.function = "Caleuche_PrepareGhostship";
		break;
		
		case "Tuttuat_10":
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && Caleuche_CheckAmulet())
			{
				dialog.text = "Idź, biały człowieku. Znajdź jeszcze dwa amulety.";
				link.l1 = "Już ich znalazłem, wielki szamanie. Spójrz, proszę.";
				link.l1.go = "Tuttuat_33";
			}
			else
			{
				dialog.text = "Idź, biały człowieku. Znajdź pozostałe dwa amulety.";
				link.l1 = "...";
				link.l1.go = "Tuttuat_10_1";
			}
		break;
		
		case "Tuttuat_10_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_10";
		break;
		
		case "Tuttuat_11":
			dialog.text = "Znowu tu jesteś, biały człowieku? Wyglądasz, jakbyś spotkał dzikiego jaguara w dżungli.";
			link.l1 = "Gorzej, wielki szamanie. Gdy wszedłem do morza, znikąd pojawiła się ogromna burza i zostałem zaatakowany przez statek obsadzony przez nieumarłych! Ich kapitan był całkowicie niezwyciężony. Najpierw zabrał mi amulet i prawie mnie zabił - ledwo przeżyłem. A potem prawie zatopili mój statek, tylko garstka mojej załogi przeżyła.";
			link.l1.go = "Tuttuat_12";
			DelLandQuestMark(npchar);
		break;
		
		case "Tuttuat_12":
			dialog.text = "Złe wieści, biały człowieku. Caleuche znów rusza do ataku.";
			link.l1 = "El Caleuche? Ten nieumarły kapitan nazwał swój statek Latającym Sercem. Więc wiedziałeś o statku-duchu i nie ostrzegłeś mnie o nim? Gdybym wiedział, że ten żeglarski koszmar poluje na amulet, nigdy bym...";
			link.l1.go = "Tuttuat_13";
		break;
		
		case "Tuttuat_13":
			dialog.text = "Tuttuathapak widzi, że biały kapitan jest zdenerwowany. Biały kapitan musi się uspokoić.";
			link.l1 = "Uspokoić się?! Oszalałeś, jak mam przeżyć przeciwko temu czemuś!";
			link.l1.go = "Tuttuat_14";
		break;
		
		case "Tuttuat_14":
			dialog.text = "Tak. Uspokój się i nie krzycz. Powiedz mi - nadal chcesz otrzymać ode mnie wielką moc, która pozostanie z tobą na zawsze?";
			link.l1 = "Cóż, oczywiście, że tak. Ale nie mam już amuletu.";
			link.l1.go = "Tuttuat_15";
		break;
		
		case "Tuttuat_15":
			dialog.text = "Ja nauczę cię, jak wziąć amulet od kapitana Caleuche. To nie będzie łatwe. Ale jeśli ci się uda, weźmiesz jego statek jako swoją nagrodę, znajdziesz cenny skarb, zdobędziesz chwałę wśród swoich ludzi i otrzymasz nagrodę ode mnie.";
			link.l1 = "Do diabła! Z chęcią zniszczyłbym tego skurczonego potwora! Ale jak mogę go pokonać, skoro nie można go zranić ani mieczem, ani kulą?!";
			link.l1.go = "Tuttuat_16";
		break;
		
		case "Tuttuat_16":
			dialog.text = "Jesteś gotów mnie słuchać, biały kapitanie?";
			link.l1 = "Tak, jestem, wielki szamanie.";
			link.l1.go = "Tuttuat_17";
		break;
		
		case "Tuttuat_17":
			dialog.text = "Kiedy mój ojciec był młodym wojownikiem, biali ludzie przybyli na moją ziemię na statku Latające Serce. Udali się w góry. Legenda mówi, że tam ukryta jest świątynia naszych przodków. Świątynia wojowników jaguara. Biali ludzie znaleźli świątynię i złoto i zbezcześcili starożytną, świętą rzecz. Zabrali wielki skarb Chavinów - jadeitową czaszkę Yum Cimil, boga śmierci i patrona ludzi jaguara.\nBiali ludzie wrócili na swój statek. Postanowili wrócić po więcej złota, ale kiedy ich człowiek postawił stopę na suchej ziemi, umarł w okropnym bólu. Yum Cimil przeklął kapitana i jego załogę. Stali się nieśmiertelni, ale nie mogą już stąpać po lądzie. Żeglowali wiele, wiele zim, pół wieku według waszego kalendarza. Tak narodził się Caleuche.\nIch ciała więdną, ich ciało gnije, ale wciąż żyją. Jeśli odetniesz ramię lub nogę, to odrasta. Jeśli ich przetniesz na pół, znów staną się całością. Jeśli ich statek zatonie, naprawiają go pod wodą, a on znów wypływa.";
			link.l1 = "Po prostu wspaniale...";
			link.l1.go = "Tuttuat_18";
		break;
		
		case "Tuttuat_18":
			dialog.text = " Caleuche terroryzuje żeglarzy. Atakuje bez powodu i zwiastuje pewną zagładę. Nie jest częstym gościem na Karaibach. Lubi żeglować wzdłuż wybrzeży mojej ojczyzny. Sądzę, że chce zdjąć klątwę. Ale nigdy jej nie zdejmie.";
			link.l1 = " Dlaczego?  Co trzeba zrobić, aby zdjąć klątwę?";
			link.l1.go = "Tuttuat_19";
		break;
		
		case "Tuttuat_19":
			dialog.text = "Jadeitowa czaszka. Musi wrócić do sanktuarium Yum Cimila, świątyni jaguarowych wojowników. Jest kilka świątyń. Starsi z mojego plemienia mówią, że jest jedna na małej wyspie na Karaibach. Dlatego Caleuche tam popłynął. Gdy czaszka znajdzie się w świątyni, zaklęcie Yum Cimila zostanie złamane, a oni staną się śmiertelni i już nie będą leczyć ran.";
			link.l1 = "Ha! Bardziej prawdopodobne, że nie zamierzają zwrócić czaszki! Dlaczego mieliby to zrobić, skoro są nieśmiertelni i niezwyciężeni? A poza tym, po prostu nie mogą jej zwrócić, jeśli nie wolno im postawić stopy na lądzie, prawda?";
			link.l1.go = "Tuttuat_20";
		break;
		
		case "Tuttuat_20":
			dialog.text = "Nie mają czaszki. Kapitan wyrzucił ją w ziemi moich przodków, kiedy wrócił z sanktuarium ludzi jaguara. Jadeit to nie złoto, biały człowiek go nie potrzebuje, nie mógł wziąć pięknego zielonego kamienia w oczach czaszki. I wyrzucił go. Jeden żeglarz podniósł go i nie został dotknięty przez klątwę. Kiedy żeglarz zobaczył, czym stała się załoga Caleuche, uciekł. Przyszedł do naszej wioski. Mój ojciec zobaczył tego żeglarza i czaszkę Yum Cimil. A potem biały człowiek poszedł na północ wzdłuż wybrzeża i zabrał czaszkę ze sobą.";
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				if (CheckAttribute(pchar, "questTemp.Caleuche.SolomonSkul"))
				{
					link.l1 = "Jadeitowa czaszka z zielonymi kamieniami w oczodołach? Miałem ją w rękach, możesz sobie wyobrazić? Dałem ją samemu Solomonowi. Ale wyjechał do Europy ze swoją córką, i wydaje się, że zabrał czaszkę ze sobą.";
				}
				else
				{
					link.l1 = "Czaszka z jadeitu z zielonymi klejnotami w oczodołach? Święty kurwa... Ja... Ja trzymałem ją własnymi rękoma! I sprzedałem ją jakiemuś Portugalczykowi... Merriman, czy coś w tym stylu... Tak, tak właśnie powiedział - czaszka Yum Cimil! Naprawdę jej pragnął! Zapłacił za nią pół miliona pesos!";
				}
				link.l1.go = "Tuttuat_21_1";
			}
			else
			{
				link.l1 = "Jadeitowa czaszka z zielonymi klejnotami w oczodołach? Więc to właśnie będę musiał znaleźć? Ale ten żeglarz mógł zginąć w dżungli pięćdziesiąt lat temu, a czaszka mogła zaginąć na zawsze!";
				link.l1.go = "Tuttuat_21_2";
			}
		break;
		
		case "Tuttuat_21_1":
			dialog.text = "Ja wiem, że czaszka jest na Karaibach. Caleuche nie jest tutaj przypadkowo. Przez ostatnie sześć księżyców często widywano go na wyspie. Dawniej nie było go tam przez wiele zim. Kapitan Caleuche potrafi wyczuć artefakt ludzi jaguara. Tak właśnie cię znalazł i twój statek.";
			link.l1 = "Więc, czy dobrze rozumiem, że muszę znowu znaleźć tę czaszkę? A potem co mam z nią zrobić?";
			link.l1.go = "Tuttuat_22";
		break;
		
		case "Tuttuat_21_2":
			dialog.text = "Czaszka musi być tutaj, na Karaibach. Caleuche jest tutaj nie przez przypadek. Przez ostatnie sześć księżyców często widziano go na wyspie. Przedtem nie było go tam przez wiele zim. Kapitan Caleuche wyczuwa artefakt ludzi jaguara. To dlatego znalazł ciebie i twój statek.";
			link.l1 = "Więc czy dobrze rozumiem, że muszę ponownie znaleźć tę czaszkę? I co wtedy mam z nią zrobić?";
			link.l1.go = "Tuttuat_22";
		break;
		
		case "Tuttuat_22":
			dialog.text = "Najpierw musisz znaleźć dwa amulety, o których rozmawialiśmy. Bez nich nic nie możesz zrobić. Amulety dają ci moc, by stanąć przeciwko ludziom-jagurom i każdemu wrogowi, na którego natrafisz.";
			link.l1 = "Stanąć przeciwko ludziom-jaguary? O czym ty mówisz?";
			link.l1.go = "Tuttuat_23";
		break;
		
		case "Tuttuat_23":
			dialog.text = "Świątynia, do której musisz przynieść jadeitową czaszkę, znajduje się na bezludnej wyspie na Karaibach. Strzeżona jest przez ludzi-jaguary. Wszyscy oni są martwi, ale teraz żyją. Bez amuletu nie przejdziesz obok nich. Ludzie-jaguary za życia byli zaciekłymi wojownikami, a po śmierci stają się niemal niezwyciężeni. Siłę daje im sam Yum Cimil.";
			link.l1 = "Nieumarli? Znowu? Szczęście do mnie...";
			link.l1.go = "Tuttuat_24";
		break;
		
		case "Tuttuat_24":
			dialog.text = "Dlaczego taki zdziwiony, biały kapitanie? Yum Cimil to bóg śmierci, jadeitowa czaszka daje władzę nad martwymi i żywymi. Karaiby. Strzegą jej ludzie-jaguary. Bez amuletu nie przejdziesz obok nich. Z amuletem możesz wejść do świątyni i przeżyć, zostawiasz tam czaszkę, potem znajdujesz Caleuche, pokonujesz jej kapitana i zabierasz amulet, który ci zabrał.";
			link.l1 = " A dlaczego kapitan Caleuche potrzebuje tych amuletów?";
			link.l1.go = "Tuttuat_25";
		break;
		
		case "Tuttuat_25":
			dialog.text = "Mnie się zdaje, że chce iść do świątyni ludzi jaguara i myśli, że amulet mu pomoże. Ale mogę się mylić. Jednak Caleuche zawsze jest zwabiana przez artefakty z mojej ziemi. Płynęła blisko wyspy, gdzie jest świątynia ludzi jaguara, i płynęła przy brzegach mojej ojczyzny.";
			link.l1 = "A gdzie jest ta wyspa?";
			link.l1.go = "Tuttuat_26";
		break;
		
		case "Tuttuat_26":
			dialog.text = "Najpierw znajdź czaszkę Yum Cimil i amulety. Potem porozmawiamy o wyspie.";
			link.l1 = "Dobrze. Czy możesz mi podpowiedzieć, gdzie szukać jadeitowej czaszki?";
			link.l1.go = "Tuttuat_27";
		break;
		
		case "Tuttuat_27":
			dialog.text = "Nie wiem. Ale jest tutaj, na Karaibach. I amulety też. Pytaj. Szukaj. Znajdź.";
			link.l1 = "Heh... Dobrze, spróbuję.";
			link.l1.go = "Tuttuat_28";
		break;
		
		case "Tuttuat_28":
			dialog.text = "I bądź ostrożny, biały kapitanie. Caleuche czuje przedmioty Chavinów. Gdy masz amulet, ona cię poszuka. Jeśli cię znajdzie, uciekaj szybko. Jeśli cię dopadnie, jesteś martwy.";
			link.l1 = "Ten przeklęty statek jest szaleńczo szybki! Jest mniej więcej dwa razy szybszy niż jakikolwiek statek, jaki kiedykolwiek widziałem. Ale zauważyłem, że ma trudności podczas żeglowania pod wiatr.";
			link.l1.go = "Tuttuat_29";
		break;
		
		case "Tuttuat_29":
			dialog.text = "Kaleuche jest przeklęta - dlatego jest taka szybka. Trudno uciec. Musisz mieć statek, który potrafi prześcignąć Kaleuche. Inaczej skończysz martwy. Kiedy znajdziesz amulet, przynieś go do mnie. Nie trzymaj amuletu na statku.";
			link.l1 = "Już to mam. Dzięki za twoją opowieść, wielki szamanie. Czas, żebym teraz poszedł.";
			link.l1.go = "Tuttuat_31";
		break;
		
		case "Tuttuat_31":
			dialog.text = "Proszę duchy, by ci pomogły i uchroniły cię przed Caleuche.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_32";
		break;
		
		case "Tuttuat_32":
			DialogExit();
			LocatorReloadEnterDisable("Shore27", "boat", false);
			npchar.dialog.currentnode = "Tuttuat_10";
			pchar.questTemp.Caleuche = "mayak"; 
			AddQuestRecord("Caleuche", "6");
		break;
		
		case "Tuttuat_33":
			if (CheckCharacterItem(pchar, "kaleuche_amulet2")) RemoveItems(pchar, "kaleuche_amulet2", 1);
			else RemoveItems(pchar, "kaleuche_amulet3", 1);
			Log_Info("You have given the amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "(spogląda) Tak, to ten. Drugi amulet Chavins. Dobra robota. Musisz jeszcze znaleźć kolejny amulet.";
			link.l1 = "Pamiętam to, szamanie. Wkrótce to dostaniesz.";
			link.l1.go = "Tuttuat_34";
			DelLandQuestMark(npchar);
			DelMapQuestMarkIsland("Dominica");
		break;
		
		case "Tuttuat_34":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_35";
			AddQuestRecord("Caleuche", "22");
			if (!Caleuche_CheckAmulet())
			{
				if (GetCharacterIndex("Map_Caleuche") != -1)
				{
					sld = characterFromId("Map_Caleuche");
					sld.lifeday = 0;
					Map_ReleaseQuestEncounter("Map_Caleuche");
				}
			}
		break;
		
		case "Tuttuat_35":
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && Caleuche_CheckAmulet())
			{
				dialog.text = "Idź, biały człowieku. Znajdź jeszcze jeden amulet.";
				link.l1 = "Już to mam, wielki szamanie. Spójrz tutaj.";
				link.l1.go = "Tuttuat_36";
			}
			else
			{
				dialog.text = "Idź, biały człowieku. Znajdź jeszcze jeden amulet.";
				link.l1 = "...";
				link.l1.go = "Tuttuat_35_1";
			}
		break;
		
		case "Tuttuat_35_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_35";
		break;
		
		case "Tuttuat_36":
			if (CheckCharacterItem(pchar, "kaleuche_amulet2")) RemoveItems(pchar, "kaleuche_amulet2", 1);
			else RemoveItems(pchar, "kaleuche_amulet3", 1);
			Log_Info("You have given the amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "(patrząc) Tak, to ten. Trzeci amulet Chavins. Jesteś dobry. Znalazłeś wszystkie amulety, by przejść obok martwych wojowników jaguarów, sług Yum Cimil.";
			link.l1 = "Teraz, jak rozumiem, będę potrzebować jadeitowej czaszki?";
			link.l1.go = "Tuttuat_37";
			DelLandQuestMark(npchar);
			DelMapQuestMarkIsland("Dominica");
		break;
		
		case "Tuttuat_37":
			dialog.text = "Mówisz prawdę. Jadeitowa czaszka Yum Cimil. Musisz zanieść ją do świątyni Chavinów. Wtedy Caleuche straci swoją moc na zawsze.";
			link.l1 = "Tuttuathapak, proszę, powiedz mi, gdzie szukać? Jakieś myśli?";
			link.l1.go = "Tuttuat_38";
		break;
		
		case "Tuttuat_38":
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				dialog.text = "Nie. Pomyśl, gdzie ostatnio widziałeś jadeitową czaszkę. Komu ją dałeś. Zacznij szukać tam.";
				link.l1 = "Dobrze, wielki szamanie. Zrobię wszystko, co w mojej mocy.";
				link.l1.go = "Tuttuat_39";
			}
			else
			{
				dialog.text = "Biały czarnoksiężnik interesuje się czaszką Yum Cimil. On jej szuka. Przybył nawet do naszej wioski. Słyszałem, że czarnoksiężnik mieszka w domu na holenderskiej wyspie. Szukaj czarnoksiężnika na holenderskiej wyspie, a może się czegoś dowiesz.";
				link.l1 = "W porządku, wielki szamanie. Zrobię wszystko, co w mojej mocy.";
				link.l1.go = "Tuttuat_39";
			}
		break;
		
		case "Tuttuat_39":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_40";
			AddQuestRecord("Caleuche", "23");
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				if (CheckAttribute(pchar, "questTemp.Caleuche.SolomonSkul")) sTemp = "I'll start with Curacao, where I handed it over to Solomon. Maybe I'll find some clue - to find out what happened to the skull.";
				else sTemp = "I'll start with visiting Curacao - there I've sold the jade skull to Joachim Merriman.";
			}
			else sTemp = "Tuttuathapak told me, that a 'white warlock' showed interest in the jade skull, and adviced seeking for him on Dutch islands. Who might that be?";
			AddQuestUserData("Caleuche", "sText", sTemp);
			if (GetCharacterIndex("Map_Caleuche") != -1)
			{
				sld = characterFromId("Map_Caleuche");
				sld.lifeday = 0;
				Map_ReleaseQuestEncounter("Map_Caleuche");
			}
			pchar.questTemp.Caleuche = "skul";
			pchar.quest.Caleuche_villemstad.win_condition.l1 = "location";
			pchar.quest.Caleuche_villemstad.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Caleuche_villemstad.function = "Caleuche_CreateMonk";
			AddMapQuestMarkCity("Villemstad", false);
		break;
		
		case "Tuttuat_40":
			dialog.text = "Idź, białas. Znajdź jadeitową czaszkę Yum Cimil.";
			if (pchar.questTemp.Caleuche == "island")
			{
				link.l1 = "Mam to tutaj, wielki szamanie, spójrz.";
				link.l1.go = "Tuttuat_45";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "Tuttuat_40_1";
			}
		break;
		
		case "Tuttuat_40_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_40";
		break;
		
		case "Tuttuat_41":
			dialog.text = "Idź, biały człowieku. Znajdź jadeitową czaszkę Yum Cimil.";
			link.l1 = "Obawiam się, że nie będę w stanie tego zrobić. Znalazłem czarnoksiężnika, ale w ostatniej chwili wymknął się ze czaszką. Nie mam absolutnie żadnego pojęcia, gdzie teraz może być.";
			link.l1.go = "Tuttuat_42";
		break;
		
		case "Tuttuat_42":
			dialog.text = "To bardzo źle, biały człowieku. Teraz nie przejdziesz przez świątynię i nie pokonasz Caleuche. Nie dam ci żadnego daru. Teraz odejdź.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_43";
		break;
		
		case "Tuttuat_43":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_44";
		break;
		
		case "Tuttuat_44":
			dialog.text = "Teraz wychodzisz, białasie.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_44_1";
		break;
		
		case "Tuttuat_44_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_40";
		break;
		
		case "Tuttuat_45":
			dialog.text = "(patrząc) Tak, to ten. Bardzo piękny. I bardzo przerażający.";
			link.l1 = "Jasne... Ale co ciekawsze - przepłynąłem całe Morze Karaibskie z Kuby do Dominiki, a Caleuche nigdy nie próbował mnie zaatakować, gdy miałem tę czaszkę, nawet go nie widziałem. A kiedy niosłem amulety do ciebie, nieustannie mnie ścigał, jak tylko wypłynąłem, odnajdywał mnie w ciągu kilku godzin.";
			link.l1.go = "Tuttuat_46a";
		break;
		
		case "Tuttuat_46a":
			dialog.text = "Mniemam, że Caleuche boi się czaszki lub nie może jej wyczuć. Nie mam innego wyjaśnienia. Może Yum Cimil sprawił, że jadeitowa czaszka jest bardzo niebezpieczna dla Caleuche - oprócz klątwy. Może dlatego kapitan tak bardzo chciał zdobyć trzy amulety mojego ludu. Aby zdobyć mądrość, jak kontrolować zaklęcie Yum Cimil.";
			link.l1 = "Więc, dopóki mam jadeitową czaszkę na pokładzie mojego statku, nie muszę się obawiać ataków Caleuche?";
			link.l1.go = "Tuttuat_46b";
		break;
		
		case "Tuttuat_46b":
			dialog.text = "Dokładnie, blady. Widzisz to na własne oczy.";
			link.l1 = "Bardzo dobrze! Zatem mogę objąć dowództwo nad dużym statkiem, wynająć przyzwoitą załogę i przygotować miłe powitanie dla tego chodzącego trupa, gdy czar zostanie z niego zdjęty, bez obaw, że przechwyci mnie wcześniej...";
			link.l1.go = "Tuttuat_46c";
		break;
		
		case "Tuttuat_46c":
			dialog.text = "";
			link.l1 = "...a tak przy okazji, gdzie mam zanieść ten jadeitowy czaszkę?";
			link.l1.go = "Tuttuat_46";
		break;
		
		case "Tuttuat_46":
			dialog.text = "Musisz zabrać to do świątyni Chavinów i zakończyć swą podróż. Chcę opowiedzieć ci historię. Jesteś gotów słuchać, biały człowieku?";
			link.l1 = "Moje uszy zawsze są otwarte na twoją mądrość, Tuttuathapak.";
			link.l1.go = "Tuttuat_47";
		break;
		
		case "Tuttuat_47":
			dialog.text = "As legendy moich przodków mówią, dawno temu, kiedy blade twarze jeszcze nie przybyły na naszą ziemię, wielki wódz Chavinów zbudował bardzo, bardzo dużą łódź i wysłał ją z grupą wojowników do krainy wielu wysp. Syn wielkiego wodza prowadził ich, a także był z nimi jeden z wysokich szamanów. W krainie wielu wysp znaleźli pustkowie i założyli osadę oraz zbudowali wielką świątynię dla Yum Cimila, którą tylko nasi wielcy przodkowie mogli zbudować\nPosłańcy wrócili z dobrymi wieściami, ale nikt już nie widział ani syna wodza, ani szamana, ani wojowników. Legenda głosi, że tam zostali, by żyć, ale najmądrzejszy z szamanów rozmawiał z duchami i powiedział, że tam już nikt nie żyje, a Yum Cimil rządzi tą ziemią\nKraina wielu wysp to Karaiby, biały człowieku. Świątynia Yum Cimila jest na wyspie, na której nie żyją ani biali ludzie, ani Indianie. Tylko słudzy Yum Cimila, Chavinavi, wciąż strzegą korytarzy świątyni.";
			link.l1 = "A gdzie jest ta wyspa?";
			link.l1.go = "Tuttuat_48";
		break;
		
		case "Tuttuat_48":
			dialog.text = "Rozumiem, że to małe i na północ od wioski, gdzieś w tej wielkiej wodzie, którą nazywacie oceanem, to nie jest daleko.";
			link.l1 = "Hmm... Może na północ od Dominiki, przy granicy oceanicznej? Psiakrew - to bardzo duży obszar na morzu! Jak mam tam znaleźć małą wyspę, skoro nikt o niej nie słyszał?";
			link.l1.go = "Tuttuat_49";
		break;
		
		case "Tuttuat_49":
			dialog.text = "Nie mogę powiedzieć lepiej. Ale znam jeszcze inną historię. Możesz usłyszeć ją od swoich braci. Około dwudziestu zim temu biały człowiek znalazł tę wyspę. Z kobietą i starym mężczyzną wszedł do świątyni Yum Cimil i zabrał potężny artefakt - kulę wschodzącego słońca. Na brzegach wyspy bladolicy kapitan został zaatakowany przez Caleuche\nBladolicy był sprytny. Oślepił kapitana i załogę Caleuche wschodzącym słońcem. Klątwa Caleuche osłabła, a kapitan zatopił ją, ale kula wschodzącego słońca rozpuściła się. Jeśli znajdziesz tego bladolicego człowieka, powie ci, gdzie jest wyspa.";
			if (CheckAttribute(pchar, "questTemp.NatanStory")) link.l1 = "Ha! Myślę, że znam tego 'bladoskórego człowieka'... Opowieści brzmią zbyt podobnie. Więc, Caleuche został zatopiony?";
			else link.l1 = "Hmm... Czyżby Caleuche został zatopiony?";
			link.l1.go = "Tuttuat_50";
		break;
		
		case "Tuttuat_50":
			dialog.text = "Tak, ale klątwa chroni ich przed śmiercią. Naprawili to i kontynuowali swoją wieczną podróż.";
			link.l1 = "Dobrze, rozumiem. Ale co mam zrobić w świątyni? Gdzie mam umieścić czaszkę? Jak pokonać wojowników jaguara, którzy jej pilnują? Jeśli to są Chavinavi, jak ci przyzwani przez czarownika Merrimana, byłoby głupotą iść tam samemu - każdy z nich jest tak silny jak dziesięciu żołnierzy.";
			link.l1.go = "Tuttuat_51";
		break;
		
		case "Tuttuat_51":
			dialog.text = "Oni nie są. Chavinavi przywołani przez białego czarownika z czaszką są słabi. O wiele słabsi niż ci przywołani przez samego Yum Cimil. Nigdy ich nie skrzywdzisz, a oni zabiją cię jednym dotknięciem swojej broni.";
			link.l1 = "Trzymaj się - a jak ten 'blady człowiek' zdołał wejść do świątyni i ukraść artefakt?";
			link.l1.go = "Tuttuat_52";
		break;
		
		case "Tuttuat_52":
			dialog.text = "Przedtem, zanim pierwszy blady twarz wszedł do świątyni, była strzeżona przez duchy zmarłych przodków. Blady twarz był silnym wojownikiem i pokonał ich. Kiedy ukradł kulę wschodzącego słońca, Yum Cimil był wściekły. Zesłał ogień i siarkę na bladą twarz i prawie zniszczył świątynię, ale on uciekł z artefaktem. Teraz Yum Cimil wezwał niezwyciężonych wojowników jaguara, by strzegli świątyni.";
			link.l1 = "Wspaniale! A jak się tam potem zakradnę?";
			link.l1.go = "Tuttuat_53";
		break;
		
		case "Tuttuat_53":
			dialog.text = "Pomogę ci, biały człowieku. Dam ci dwa amulety Chavinów, które mi przyniesiesz. Porozmawiam z duchami przodków i naładuję amulet. Kiedy będziesz miał jeden przy sobie, będziesz mógł walczyć z wojownikami jaguarów jak zwykli żołnierze, będziesz jak jeden z nich, choć bardzo silny. Amulet ochroni cię i da ci moc broni, by zaszkodzić Chavinavi w świątyni.";
			link.l1 = "Jesteś pewien, że amulety pomogą?";
			link.l1.go = "Tuttuat_54";
		break;
		
		case "Tuttuat_54":
			dialog.text = "Ja wiedzieć. Ja rozmawiać z przodkami. Ja wielki szaman. Ty ufać mi. Ty weź dwa amulety. Jeden chroni. Drugi wzmacnia broń. Jeden amulet musisz użyć. Który - ty wybierasz. Jeśli ty nie nosić amulet, ty zginąć przez wojowników jaguara\nI ty pamiętać, że o północy Yum Cimil ożywia wszystkich wojowników, których zabiłeś. Musisz znaleźć czas, by nie walczyć z nimi dwa razy, lub tak, duchy mówią mi, że możesz.";
			link.l1 = "Widzę.";
			link.l1.go = "Tuttuat_55";
		break;
		
		case "Tuttuat_55":
			dialog.text = "Ty bierzesz amulety. Oto one. Pamiętasz, ich moc ma ograniczenia. Ona zniknie w jednej pełni. Pamiętasz, jak mówiłem, że nie możesz utrzymać ich mocy? Tylko wielki szaman naszego plemienia może ją utrzymać.";
			link.l1 = "Pamiętam. Więc, mam tylko jeden księżyc? Jeden miesiąc?";
			link.l1.go = "Tuttuat_56";
		break;
		
		case "Tuttuat_56":
			dialog.text = "Tak. Kiedy dotrzesz do świątyni Yum Cimil, musisz znaleźć sanktuarium i wielką statuę Kondora w nim. To jest najważniejsza część świątyni. Tutaj umieść jadeitową czaszkę Yum Cimil, a klątwa zostanie zdjęta z Caleuche. Kiedy on znów cię zaatakuje, pokonaj go jak zwykłego człowieka. Potem przynieś mi amulet, który ci zabrał.";
			link.l1 = "Kondor? Co to jest?";
			link.l1.go = "Tuttuat_57";
		break;
		
		case "Tuttuat_57":
			dialog.text = "Kondor to wielki ptak, który żyje w górach mojego domu. Na pamiątkę domu, przodkowie zbudowali posąg Kondora w pobliżu świątyni.";
			link.l1 = "Dobrze, poszukam tego...";
			link.l1.go = "Tuttuat_58";
		break;
		
		case "Tuttuat_58":
			dialog.text = "Bądź ostrożny. Wiele niebezpieczeństw czai się w świątyni obok wojowników jaguara.";
			link.l1 = "Jakie niebezpieczeństwa?";
			link.l1.go = "Tuttuat_59";
		break;
		
		case "Tuttuat_59":
			dialog.text = "Nie wiem na pewno. Widzisz sam. To może być pułapka, lub... zamieszanie. Dostać się do sanktuarium to trudne zadanie. Wejście jest zapieczętowane, a ty musisz znaleźć sposób, aby je otworzyć. Moi przodkowie byli nie tylko wielkimi wojownikami i szamanami, ale też wielkimi budowniczymi, więc aby je otworzyć, musisz myśleć.";
			link.l1 = "Heh! Brzmi przerażająco, ale niech wszyscy przyjdą! Nie będę tracić czasu. Wypływam od razu!";
			link.l1.go = "Tuttuat_60";
		break;
		
		case "Tuttuat_60":
			dialog.text = "Idź, biały wojowniku. Ja przywołam duchy, które pomogą ci przeciw wojownikom jaguara i Caleuche. Pamiętaj, jeśli użyjesz amuletów, mogę pomóc, jeśli nie, zginiesz";
			link.l1 = "Dziękuję, wielki szamanie... Zrobię to.";
			link.l1.go = "Tuttuat_61";
		break;
		
		case "Tuttuat_61":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_62";
			npchar.greeting = "Tuttuat_3";
			Log_Info("You have received two amulets");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "kaleuche_amulet2");
			GiveItem2Character(pchar, "kaleuche_amulet3");
			// преобразуем амулеты
			ChangeItemDescribe("kaleuche_amulet2", "itmdescr_kaleuche_amulet2_sword");
			ChangeItemDescribe("kaleuche_amulet3", "itmdescr_kaleuche_amulet3_shield");
			sld = ItemsFromID("kaleuche_amulet2");
			sld.picIndex = 13;
			sld.picTexture = "ITEMS_36";
			sld.groupID = TALISMAN_ITEM_TYPE;
			sld.unique = true;	
			sld.ItemType = "ARTEFACT";
			sld = ItemsFromID("kaleuche_amulet3");
			sld.picIndex = 14;
			sld.picTexture = "ITEMS_36";
			sld.groupID = TALISMAN_ITEM_TYPE;
			sld.unique = true;	
			sld.ItemType = "ARTEFACT";
			SetFunctionTimerCondition("Caleuche_TuttuatAmuletOver", 0, 0, 30, false); // таймер
			// делаем доступным Хаэль Роа
			n = FindIsland("KhaelRoa");
			Islands[n].visible = true;
			Island_SetReloadEnableGlobal(Islands[n].id, true);
			Islands[n].reload.l1.radius = 150.0;
			Islands[n].reload.l2.label = "Shore64_1";
			Islands[n].reload.l2.name = "reload_2";
			Islands[n].reload.l2.go = "";
			Islands[n].reload.l2.emerge = "";
			Islands[n].reload.l2.radius = 0.0;
			Islands[n].reload.l2.pic = 0;
			Islands[n].reload.l2.tex = "t1";
			pchar.questTemp.Caleuche = "khaelroa";
			pchar.quest.Caleuche_khaelroa_arrive.win_condition.l1 = "location";
			pchar.quest.Caleuche_khaelroa_arrive.win_condition.l1.location = "KhaelRoa_port";
			pchar.quest.Caleuche_khaelroa_arrive.function = "Caleuche_KhaelRoaArrive";
			AddQuestRecord("Caleuche", "34");
			if (CheckAttribute(pchar, "questTemp.NatanStory")) 
			{
				pchar.questTemp.Caleuche.NatanInfo = "true";
				AddQuestUserData("Caleuche", "sText", "But I have a clue: it seems that white captain, who had visited the temple of the Chavins, is none other than my good friend Nathaniel Hawk. I remember him saying that he had a map of that island in Maroon Town. Guess I will pay Nathan a visit.");
			}
			else AddQuestUserData("Caleuche", "sText", "That's a huge area in the sea, but I have no choice. I'll have to scour it entirely. Shaman said North of Dominica, and not too far so I could steadily move North, it might very well be a bit to the East or West. He also mentioned some Captain that destroyed the undead ship maybe I will be lucky and I might find him one day, alas, he said that I have only one month to hold this power or whatever it is, oh well it is what it is, let the search begin!");
		break;
		
		case "Tuttuat_62":
			if (pchar.questTemp.Caleuche == "regard" && CheckCharacterItem(pchar, "kaleuche_amulet1") && CheckCharacterItem(pchar, "kaleuche_amulet2") && CheckCharacterItem(pchar, "kaleuche_amulet3")) 
			{
				dialog.text = "Ja rozmawiam z duchami. Byłeś na wyspie w świątyni Yum Cimil. Znalazłeś Caleuche i amulet?";
				link.l1 = "Masz rację, wielki szamanie. Znalazłem wyspę, wszedłem do świątyni i zostawiłem jadeitową czaszkę w środku.";
				link.l1.go = "Tuttuat_63";
			}
			else
			{
				dialog.text = "Idź, biały wojowniku.";
				if (CheckAttribute(pchar, "questTemp.Caleuche.AmuletOver"))
				{
					link.l1 = "Tuttuathapak, widzisz... Nie zaniosłem czaszki do świątyni na czas, i twoje amulety straciły swoją moc.";
					link.l1.go = "Tuttuat_82";
				}
				else
				{
					link.l1 = "... ";
					link.l1.go = "Tuttuat_62_1";
				}
			}
		break;
		
		case "Tuttuat_62_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_62";
		break;
		
		case "Tuttuat_63":
			npchar.greeting = "Tuttuat_2";
			pchar.quest.Caleuche_TuttuatAmuletOver.over = "yes"; //снять таймер
			if(IsEquipCharacterByArtefact(pchar, "kaleuche_amulet2")) RemoveCharacterEquip(pchar, TALISMAN_ITEM_TYPE);
			if(IsEquipCharacterByArtefact(pchar, "kaleuche_amulet3")) RemoveCharacterEquip(pchar, TALISMAN_ITEM_TYPE);
			dialog.text = "Zdjąłeś klątwę z Caleuche. Czy ona cię potem znalazła?";
			link.l1 = "Tak. Spotkaliśmy się na wyspie. Zmierzyłem się z nią i wyszedłem zwycięsko. Teraz mam wszystkie trzy amulety. Proszę, weź je.";
			link.l1.go = "Tuttuat_64";
		break;
		
		case "Tuttuat_64":
			RemoveItems(pchar, "kaleuche_amulet1", 1);
			RemoveItems(pchar, "kaleuche_amulet2", 1);
			RemoveItems(pchar, "kaleuche_amulet3", 1);
			Log_Info("You have given three Chavin amulets");
			PlaySound("interface\important_item.wav");
			dialog.text = "Jesteś szybkim i silnym wojownikiem, blady. Tuttuathapak nie lubi białych ludzi, ale ja szanuję odważnego i zręcznego wojownika. Spisałeś się bardzo dobrze. Oczyściłeś morza z Caleuche. Przyniosłeś mi trzy amulety. Ja cię nagrodzę.";
			link.l1 = "Obiecałeś coś o 'mocy, którą będę mógł trzymać na zawsze'?";
			link.l1.go = "Tuttuat_65";
		break;
		
		case "Tuttuat_65":
			dialog.text = "Rzekłeś prawdę. Dam ci tę moc. Nikt na Karaibach nie zna sekretu rośliny, który ja znam. Słuchaj mnie, blady! W moim domu jest roślina lecznicza. Nazywamy ją Manga Rosa. Słyszałeś o tej roślinie?";
			if (CheckAttribute(pchar, "questTemp.Mangarosa.Tell"))
			{
				link.l1 = "Tak. Trzymałem to w rękach. Cyganie wykazują duże zainteresowanie tym. A jedna z nich, uzdrowicielka Amelia, potrafi nawet...";
				link.l1.go = "Tuttuat_66";
			}
			else
			{
				link.l1 = "Nie mam pojęcia...";
				link.l1.go = "Tuttuat_66_1";
			}
		break;
		
		case "Tuttuat_66":
			dialog.text = "Ja słyszałem o zielarce Amelii. Ona nie wie mało, ale nie dużo. Ona nie zna sekretu Manga Rosa. Tylko wielki szaman z mojej ojczyzny, skąd Manga Rosa została tu przywieziona, potrafi używać jej pełnej mocy.";
			link.l1 = "Jaka to moc?";
			link.l1.go = "Tuttuat_67";
		break;
		
		case "Tuttuat_66_1":
			dialog.text = "To ziele rośnie w mojej ojczyźnie, ale występuje również na Karaibach. Jest to jasnozielona wysoka roślina, z liśćmi jak palma z rozpostartymi palcami, i przyjemnym zapachem. Rozpoznasz ją natychmiast i nie pomylisz z niczym innym. Ja znam sekrety tej rośliny. Potrafię wydobyć z niej moc.";
			link.l1 = "Rozumiem, ale jakiego rodzaju to moc?";
			link.l1.go = "Tuttuat_67";
		break;
		
		case "Tuttuat_67":
			dialog.text = "Ja mogę zrobić mikstury z Manga Rosa. Bardzo silne mikstury. Nikt oprócz mnie na Karaibach nie potrafi ich zrobić. Moje mikstury czynią człowieka na zawsze silniejszym, szybszym, mądrzejszym, bystrym, przystojniejszym i szczęśliwszym. Uwarzam dla ciebie trzy takie mikstury.";
			link.l1 = "Bardzo interesujące!";
			link.l1.go = "Tuttuat_68";
		break;
		
		case "Tuttuat_68":
			dialog.text = "Ty wielki wojowniku, więc najpierw potrzebujesz mikstury, która uczyni cię twardszym, i jednej, która uczyni cię szybszym. A trzecią miksturę wybierzesz, gdy zrobię te dwie pierwsze. Ale musisz przynieść mi Manga Rosa, by je zrobić - nie mam żadnej.";
			link.l1 = "Gdzie powinienem szukać Mangi Rosy?";
			link.l1.go = "Tuttuat_69";
		break;
		
		case "Tuttuat_69":
			dialog.text = "Manga Rosa to rzadkie ziele na Karaibach. Rośnie tam, gdzie ludzie rzadko chodzą. Głupi ludzie zbierają je, suszą i palą. Bardzo głupi ludzie. NIE PAL TEGO! To marnowanie mocy... Szukaj dżungli i zatoczek, tajnych miejsc, gdzie głupi ludzie nie stąpają. Patrz uważnie. Na każdą miksturę potrzebuję pięciu łodyg Manga Rosa.";
			link.l1 = "Dobrze, wielki szamanie. Wrócę do ciebie, gdy będę miał wystarczająco Manga Rosa.";
			link.l1.go = "Tuttuat_70";
		break;
		
		case "Tuttuat_70":
			dialog.text = "Idź, biały wojowniku. Przynieś mi Manga Rosa. Nie pożałujesz tego. Moje mikstury są najlepsze. Powiem duchom, by pomogły ci w poszukiwaniach.";
			link.l1 = "Dziękuję! Do zobaczenia, szamanie!";
			link.l1.go = "Tuttuat_71";
		break;
		
		case "Tuttuat_71":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_72";
			pchar.questTemp.Caleuche = "mangarosa";
			pchar.questTemp.Caleuche.Mangarosa = 0;
			AddQuestRecord("Caleuche", "41");
		break;
		
		case "Tuttuat_72":
			dialog.text = "Przynosisz pięć łodyg Manga Rosa na miksturę?";
			if (GetCharacterItem(pchar, "cannabis7") >= 5)
			{
				link.l1 = "Tak. Oto pięć roślin, których potrzebujesz.";
				link.l1.go = "Tuttuat_73";
			}
			link.l2 = "Jeszcze nie, wielki szamanie. Moje poszukiwania trwają...";
			link.l2.go = "Tuttuat_72_1";
		break;
		
		case "Tuttuat_72_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_72";
		break;
		
		case "Tuttuat_73":
			RemoveItems(pchar, "cannabis7", 5);
			switch (sti(pchar.questTemp.Caleuche.Mangarosa))
			{
				case 0:
					dialog.text = "Bardzo dobrze. Przyjdź jutro, gdy słońce zajdzie. Uwarzę ci mikstury, które zwiększą twoją reakcję i zręczność.";
					link.l1 = "Dobrze, szamanie. Przyjdę jutro wieczorem.";
					link.l1.go = "Tuttuat_74";
					pchar.questTemp.Caleuche.Mangarosa = 1;
				break;
				
				case 1:
					dialog.text = "Bardzo dobrze. Przyjdź jutro, gdy słońce zajdzie. Przyrządzę ci mikstury, które zwiększą twoją wytrzymałość.";
					link.l1 = "Dobrze, szamanie. Przyjdę jutro wieczorem.";
					link.l1.go = "Tuttuat_74";
					pchar.questTemp.Caleuche.Mangarosa = 2;
				break;
				
				case 2:
					dialog.text = "Bardzo dobrze. Jaki jest twój eliksir do wyboru? Eliksir siły, bystrego wzroku, inteligencji, piękna czy szczęścia?";
					link.l1 = "Mikstura siły.";
					link.l1.go = "Tuttuat_77_1";
					link.l2 = "Mikstura bystrego wzroku.";
					link.l2.go = "Tuttuat_77_2";
					link.l3 = "Eliksir inteligencji.";
					link.l3.go = "Tuttuat_77_3";
					link.l4 = "Eliksir piękna.";
					link.l4.go = "Tuttuat_77_4";
					link.l5 = "Eliksir szczęścia.";
					link.l5.go = "Tuttuat_77_5";
				break;
			}
		break;
		
		case "Tuttuat_74":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_75";
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1 = "Timer";
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.hour  = 19.0;
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Caleuche_mangarosa_potion.function = "Caleuche_MangarosaPotion";
		break;
		
		case "Tuttuat_75":
			if (CheckAttribute(pchar, "questTemp.Caleuche.Potion"))
			{
				sTemp = "";
				if (sti(pchar.questTemp.Caleuche.Mangarosa) == 1) sTemp = "  It make your movements faster, and you better fight with fine light weapons.";
				if (sti(pchar.questTemp.Caleuche.Mangarosa) == 2) sTemp = "  It make you more hardy in long journeys, and you better fight with sharp sabers.";
				dialog.text = "Mikstura gotowa, blady wojowniku. Weź ją."+sTemp+"";
				link.l1 = "Dziękuję, wielki szamanie.";
				link.l1.go = "Tuttuat_76";
			}
			else
			{
				dialog.text = "Jeszcze nie gotowe, biały człowieku. Przyjdź później. Nie przeszkadzaj mi.";
				link.l1 = " Dobrze...";
				link.l1.go = "Tuttuat_75_1";
			}
		break;
		
		case "Tuttuat_75_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_75";
		break;
		
		case "Tuttuat_76":
			if (sti(pchar.questTemp.Caleuche.Mangarosa) > 2)
			{
				dialog.text = "Uwarzę dla ciebie wszystkie mikstury, które obiecałem. Staniesz się silniejszy. Ty zadowolony?";
				link.l1 = "Tak, wielki szamanie. To była rzeczywiście godna nagroda.";
				link.l1.go = "Tuttuat_78";
			}
			else
			{
				dialog.text = "Znajdziesz pięć kolejnych łodyg Manga Rosa, przyniesiesz mi je. Zrobię ci kolejny eliksir.";
				link.l1 = "Przyniosę ci więcej z nich. Do zobaczenia!";
				link.l1.go = "Tuttuat_77";
			}
		break;
		
		case "Tuttuat_77":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_72";
			DeleteAttribute(pchar, "questTemp.Caleuche.Potion");
			if (sti(pchar.questTemp.Caleuche.Mangarosa) == 1)
			{
				ChangeItemDescribe("kaleuche_amulet1", "itmdescr_kaleuche_amulet1_potion");
				sld = ItemsFromID("kaleuche_amulet1");
				sld.name = "itmname_kaleuche_amulet1_potion";
				sld.groupID = SPECIAL_ITEM_TYPE;
				sld.picIndex = 15;
				sld.picTexture = "ITEMS_35";
				sld.price = 0;
				sld.Weight = 1.0;
				sld.ItemType = "SUPPORT";
				GiveItem2Character(pchar, "kaleuche_amulet1");
			}
			if (sti(pchar.questTemp.Caleuche.Mangarosa) == 2)
			{
				ChangeItemDescribe("kaleuche_amulet2", "itmdescr_kaleuche_amulet2_potion");
				sld = ItemsFromID("kaleuche_amulet2");
				sld.name = "itmname_kaleuche_amulet2_potion";
				sld.groupID = SPECIAL_ITEM_TYPE;
				sld.picIndex = 15;
				sld.picTexture = "ITEMS_35";
				sld.price = 0;
				sld.Weight = 1.0;
				sld.ItemType = "SUPPORT";
				GiveItem2Character(pchar, "kaleuche_amulet2");
			}
		break;
		
		case "Tuttuat_77_1":
			dialog.text = "Przyjdź jutro, jak zwykle. Uwarzę ci miksturę, która cię wzmocni, a ty lepiej walcz dużym toporem.";
			link.l1 = "Dobrze.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 31;
		break;
		
		case "Tuttuat_77_2":
			dialog.text = "Przyjdź jutro, jak zwykle. Uwarzę ci miksturę, która sprawi, że twoje oczy będą bystre, abyś widział każdy cel, a ty lepiej trafiaj ognistą bronią, która ryczy.";
			link.l1 = "Dobrze.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 32;
		break;
		
		case "Tuttuat_77_3":
			dialog.text = "Przyjdź jutro, jak zwykle. Uwarzę ci miksturę, żebyś był mądrzejszy, i lepiej ukryj się przed wrogami.";
			link.l1 = "Dobrze.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 33;
		break;
		
		case "Tuttuat_77_4":
			dialog.text = "Przyjdź jutro, jak zwykle. Uwarzę ci miksturę, żebyś był przystojniejszy, a ty lepiej przekonuj ludzi.";
			link.l1 = "Dobrze.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 34;
		break;
		
		case "Tuttuat_77_5":
			dialog.text = "Przyjdź jutro, jak zwykle. Uwarzę ci miksturę, która przyniesie ci szczęście, a będziesz mieć dobrą fortunę.";
			link.l1 = "Dobrze.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 35;
		break;
		
		case "Tuttuat_78":
			dialog.text = "Me cieszy, że podoba ci się moja sztuka, sztuka wielkiego szamana.";
			link.l1 = "Powiedz, Tuttuathapak, do czego potrzebowałeś tych trzech amuletów? Po prostu ciekawość...";
			link.l1.go = "Tuttuat_79";
		break;
		
		case "Tuttuat_79":
			dialog.text = "Już czujesz moc tych dwóch amuletów. Duchy pomogą mi nadać im moc, a wszystkie trzy amulety razem dają wielką mądrość szamańską i oświecenie moich przodków, wielkich Chavinów.";
			link.l1 = "Widzę. Dobrze, dziękuję raz jeszcze za twoje doskonałe mikstury. Naprawdę jesteś wspaniałym szamanem. Nadszedł czas, abym poszedł. Żegnaj, Tuttuathapak, mam nadzieję, że jeszcze się zobaczymy.";
			link.l1.go = "Tuttuat_80";
		break;
		
		case "Tuttuat_80":
			dialog.text = "Żegnaj, biały wojowniku. Już mnie nie szukasz. Udaję się w odosobnienie, by pojąć mądrość moich przodków. Niech duchy wspierają cię w twoich podróżach!";
			link.l1 = "Cóż więc... hah... niech duchy oświetlają twą drogę, wielki szamanie. Żegnaj...";
			link.l1.go = "Tuttuat_81";
		break;
		
		case "Tuttuat_81":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			GiveItem2Character(pchar, "kaleuche_amulet3");
			ChangeItemDescribe("kaleuche_amulet3", "itmdescr_kaleuche_amulet3_potion");
			sld = ItemsFromID("kaleuche_amulet3");
			sld.name = "itmname_kaleuche_amulet3_potion";
			sld.groupID = SPECIAL_ITEM_TYPE;
			sld.picIndex = 15;
			sld.picTexture = "ITEMS_35";
			sld.price = 0;
			sld.Weight = 1.0;
			sld.reaction = sti(pchar.questTemp.Caleuche.Mangarosa);
			sld.ItemType = "SUPPORT";
			i = sti(sld.reaction);
			ChangeItemDescribe("kaleuche_amulet3", "itmdescr_kaleuche_amulet"+i+"_potion");
			AddQuestRecord("Caleuche", "42");
			pchar.questTemp.Caleuche = "end";
			CloseQuestHeader("Caleuche");
			DeleteAttribute(pchar, "questTemp.Caleuche.Mangarosa");
			DeleteAttribute(pchar, "questTemp.Caleuche.Potion");
		break;
		
		case "Tuttuat_82":
			Log_Info("You have given amulets");
			RemoveItems(pchar, "kaleuche_amulet2", 1);
			RemoveItems(pchar, "kaleuche_amulet3", 1);
			dialog.text = "Zasmucasz mnie, białolicy. Odprawiłem rytuał z duchami, by nadać moc tym amuletom, a ty to marnujesz. Smutno mi. Idź już. Tuttuathapak nie ma ci nic więcej do powiedzenia.";
			link.l1 = "Przepraszam, nie miałem szczęścia... No cóż. Żegnaj, szamanie.";
			link.l1.go = "Tuttuat_83";
		break;
		
		case "Tuttuat_83":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Caleuche", "43");
			pchar.questTemp.Caleuche = "end";
			CloseQuestHeader("Caleuche");
			sld = ItemsFromID("SkullAztec");
			sld.price = 10000;
		break;

		// капитан Калеуче
		case "CaleucheCap":
			PlaySound("Voice\English\LE\Baltazar_de_Kortes\Baltazar_01.wav");
			dialog.text = "Wszystko na próżno, żeglarzu. Nie pokonasz mnie. A wszyscy moi ludzie leżący na pokładzie złożą swoje kości i powstaną przed świtem. Nie można nas zabić, bo śmierć porzuciła nas na zawsze.";
			link.l1 = "Cholera jasna! Jesteś martwy czy żywy? Bardziej prawdopodobne, że wciąż żyjesz - martwi zazwyczaj leżą cicho i nie wymachują mieczami. Ale kimże jesteś i dlaczego zaatakowałeś mój statek?";
			link.l1.go = "CaleucheCap_1";
		break;
		
		case "CaleucheCap_1":
			dialog.text = "Jestem Balthazar de Cordes z Latającego Serca. Żałosne tchórze, którzy nic o mnie nie wiedzą, nazywają mnie Van der Decken, kapitanem Latającego Holendra. Ale to nie ma znaczenia. Ważne jest to, że masz przy sobie amulet, który teraz zabiorę. Potrzebuję go! Czuję to! Wielki amulet Chavinów, jeden z trzech, w końcu będzie mój! Uklęknij przede mną, śmiertelniku! A może uczynię twoją śmierć bezbolesną!";
			link.l1 = "Pierdol się, trupie!";
			link.l1.go = "CaleucheCap_2";
		break;
		
		case "CaleucheCap_2":
			DialogExit();
			npchar.MultiFighter = 4.0;
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_SetCheckMinHP(pchar, 10, true, "Caleuche_GhostshipGetOut");
		break;
		
		case "CaleucheCap_3":
			PlaySound("Voice\English\LE\Baltazar_de_Kortes\Baltazar_02.wav");
			dialog.text = "Nie mogę w to uwierzyć! Minęło tak wiele czasu odkąd ostatnio widziałem swoją własną krew i czułem jakikolwiek ból...JAK?!";
			link.l1 = "Tym razem przegrałeś, Balthazarze de Cordes. Znam twoją historię. Jadeitowa czaszka została zwrócona do świątyni Chavinów, a klątwa Yum Cimil już dłużej nie wisi nad tobą ani twoimi ludźmi. Nie będziesz już przywracał swoich marynarzy do życia.";
			link.l1.go = "CaleucheCap_4";
		break;
		
		case "CaleucheCap_4":
			dialog.text = "Och, więc musisz się uważać za odkupiciela, może? Nie! Balthazar de Cordes sprzeda drogo cokolwiek z życia, co mu pozostało!";
			link.l1 = "Ostatnia podróż Latającego Serca kończy się tutaj, na Khael Roa. I nie podniesiesz swego statku z dna morza, jak to uczyniłeś dwadzieścia pięć lat temu.";
			link.l1.go = "CaleucheCap_5";
		break;
		
		case "CaleucheCap_5":
			PlaySound("Voice\English\LE\Baltazar_de_Kortes\Baltazar_03.wav");
			dialog.text = "Jastrząb! Minęło dwadzieścia pięć lat, a ja wciąż pamiętam to, jakby to było zaledwie wczoraj. Blask tej kuli, która nas oślepiła i rozbiła mój statek na pół. To była pierwsza i ostatnia porażka Latającego Serca i Balthazara de Cordes... Więc przepłyńmy ostatni raz, kapitanie! Śmierć w bitwie jest lekka i mile widziana!";
			link.l1 = "...";
			link.l1.go = "CaleucheCap_6";
		break;
		
		case "CaleucheCap_6":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Caleuche_ChangeShip");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// --> // наш матрос на берегу
		case "on_coast":
			dialog.text = "W końcu się obudziłeś, kapitanie... Jak się czujesz?";
			link.l1 = "Cholera jasna, co się stało? Głowa mi pęka z bólu...";
			link.l1.go = "on_coast_1";
		break;
		
		case "on_coast_1":
			dialog.text = "Kiedy weszliśmy do kajuty kapitana, leżałeś na podłodze, nadal bez ruchu. Chłopcy podnieśli cię i przeciągnęli na nasz statek - i to w samą porę, ponieważ martwi leżący na pokładzie zaczęli się znów podnosić\nNajświętsza Dziewico i wszyscy Święci! Szybko przecięliśmy liny i próbowaliśmy odpłynąć, ale salwa z ich statku szybko zamieniła naszą starą wannę w drzazgi i straciliśmy nad nią kontrolę. Potem podnieśli żagle i zniknęli w mgnieniu oka\nNasz statek osiadł na mieliźnie, a wszyscy, którzy zdołali przeżyć, dotarli na brzeg łodzią. Wielu dobrych ludzi zginęło dzisiaj... gdybyśmy tylko zostali na pokładzie... Ale byliśmy pewni, że burza ostatecznie zatopi statek.";
			link.l1 = "Nie wasza wina, panowie. To była słuszna decyzja. Dziękuję, zapamiętam to.";
			link.l1.go = "on_coast_2";
		break;
		
		case "on_coast_2":
			dialog.text = "Zaciągnęliśmy cię na łódź, a potem przywieźliśmy na brzeg. Byłeś prawie martwy...";
			link.l1 = "Jestem ci winien życie. Jak długo leżałem tu nieprzytomny?";
			link.l1.go = "on_coast_3";
		break;
		
		case "on_coast_3":
			dialog.text = "Przez cały dzień. Umyliśmy i opatrzyliśmy twoje rany, daliśmy ci lekarstwa i wlaliśmy w ciebie trochę rumu. Powinieneś szybko wydobrzeć.";
			link.l1 = "Na pewno nie umrę tym razem. Chociaż nie czuję się naprawdę dobrze...";
			link.l1.go = "on_coast_4";
		break;
		
		case "on_coast_4":
			dialog.text = "To pewne... Czy to był Latający Holender, kapitanie? Dlaczego nas zaatakowali? I dlaczego nie strzelili do nas przed abordażem, ale prawie zatopili nasz statek jedną salwą później?";
			link.l1 = "Ich kapitan potrzebował amuletu, o którym rozmawiałem z Tuttuathapakiem, indiańskim szamanem. Dlatego nie zatopili nas od razu, ale gdy ich przywódca wziął amulet, szybko nas się pozbyli... Co za koszmar! Statek obsługiwany przez umarłych! Nie do uwierzenia...";
			link.l1.go = "on_coast_5";
		break;
		
		case "on_coast_5":
			dialog.text = "Tak, teraz przyszła nasza kolej, by natknąć się na Latającego Holendra. Gdy będę miał okazję, pójdę do kościoła, zapalę świecę za moje cudowne ocalenie i pomodlę się do naszego Pana...";
			link.l1 = "Ja też... Chyba. Ale najpierw wrócę do tej wioski. Muszę opowiedzieć Tuttuathapakowi o wszystkim. Ta przeklęta łajba zaatakowała nas z powodu amuletu! Jestem pewien, że ten czerwono-skóry diabeł miał jakieś pomysły, po co do cholery te żywe trupy mogły go potrzebować.";
			link.l1.go = "on_coast_6";
		break;
		
		case "on_coast_6":
			dialog.text = "Dobrze. Ale uważaj kapitanie, twoje rany ledwo się zagoiły, przynajmniej weź kogoś ze sobą na wszelki wypadek.";
			link.l1 = "Będę ostrożny, obiecuję. Dzięki, że mnie nie porzuciłeś!";
			link.l1.go = "on_coast_7";
		break;
		
		case "on_coast_7":
			dialog.text = "Co ty gadasz, kapitanie! Poszlibyśmy za tobą na koniec świata i walczyli z tysiącami nieumarłych! To cholerny wstyd, że tak wiele straciliśmy, ale ta historia będzie żyła w legendach.";
			link.l1 = "...";
			link.l1.go = "on_coast_8";
		break;
		
		case "on_coast_8":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("Caleuche", "5");
		break;
		
		// Фергус Хупер
		case "fergus":
			dialog.text = "Ej! Jeszcze nie zebrałem wystarczającej ilości wężowych skór, żeby je ci sprzedać, więc spadaj!";
			link.l1 = "Hmm... Czy jesteś Fergus Hooper?";
			link.l1.go = "fergus_1";
		break;
		
		case "fergus_1":
			dialog.text = "Nie, moje imię to Tuttuathapak, i przeklnę cię, jeśli natychmiast się nie zgubisz. Więc lepiej się pospiesz, bo inaczej...";
			link.l1 = "...stracę rozum, spalę własny statek, a moi żeglarze mnie zabiją i zabiorą wszystkie moje rzeczy. Prawda?";
			link.l1.go = "fergus_2";
		break;
		
		case "fergus_2":
			sld = characterFromId(pchar.questTemp.Caleuche.Amuletmaster);
			dialog.text = "Arrgh... Co do diabła, kim jesteś!? Jak się...";
			link.l1 = "Mamy wspólnego przyjaciela, Fergusa. Jest latarnikiem, a jego imię to "+GetFullName(sld)+"On mi o tobie opowiedział i wysłał mnie, by cię odszukać. Tak przy okazji, osobiście znam szamana Tuttuathapaka, więc twój żart się nie udał, przepraszam. Słuchaj, nie szukam kłopotów. Chcę coś od ciebie kupić, i to nie są wężowe skóry.";
			link.l1.go = "fergus_3";
		break;
		
		case "fergus_3":
			dialog.text = "O, więc znasz mojego starego przyjaciela! Jak się miewa? Czy jeszcze nie umarł z nudów w swojej latarni morskiej? Proszę, siadaj, marynarzu, napij się ze mną!";
			link.l1 = "Przykro mi, Fergus, naprawdę nie mam dużo czasu. Słuchaj, potrzebuję tego indyjskiego amuletu, jednego z tych, które twój zmarły kapitan zabrał z Głównego z Tuttuathapak. Zapłacę dobrą cenę za niego, a ty pozbędziesz się niebezpiecznego drobiazgu.";
			link.l1.go = "fergus_4";
		break;
		
		case "fergus_4":
			dialog.text = "A cóż w nim takiego niebezpiecznego? Jak dotąd nie widziałem z tego żadnej szkody. To tylko bezużyteczny kamień";
			link.l1 = "To dlatego, że już nie żeglujesz po morzach. Miałem podobny amulet do niedawna. Statek widmo poluje na te rzeczy.";
			link.l1.go = "fergus_5";
		break;
		
		case "fergus_5":
			dialog.text = "Żartujesz sobie, kumplu? Może znajomość z Tuttuathapakiem odcisnęła na tobie piętno? Uważaj, kapitanie, ten czerwonoskóry diabeł pożre twój umysł...";
			link.l1 = "Wierzysz mi lub nie, ale mówię prawdę. Sam bym w to nie uwierzył, gdybym nie widział tego na własne oczy, mogę przysiąc na Księgę lub możesz zapytać tych, którzy byli ze mną. Ledwo przeżyłem to spotkanie z Caleuche.";
			link.l1.go = "fergus_6";
		break;
		
		case "fergus_6":
			dialog.text = "Caleuche?";
			link.l1 = "„Cóż, większość nazywa to Latającym Holendrem, ale jego prawdziwa nazwa to Latające Serce. Nieważne. Po prostu sprzedaj mi ten amulet. I tak nie masz z niego pożytku, wiem.”";
			link.l1.go = "fergus_7";
		break;
		
		case "fergus_7":
			dialog.text = "Zgadza się. To tylko bezużyteczny drobiazg, choć całkiem piękny. Słuchaj, sprzedałbym go tobie bez dalszych ceregieli, ale widzisz - już go nie mam. Został skradziony z mojej chaty wraz z innymi rzeczami, kiedy byłem na polowaniu w dżungli. To wydarzyło się całkiem niedawno, około miesiąca temu. Przykro mi, ale nie mogę ci w niczym pomóc.";
			link.l1 = "A kto to ukradł?";
			link.l1.go = "fergus_8";
		break;
		
		case "fergus_8":
			dialog.text = "Naprawdę myślisz, że siedziałbym tutaj, gdybym wiedział, kto oczyścił mój dom? Jest banda złodziei i zbójców działających poza Belize, a w mieście mają informatorów. Przynajmniej tak myśli komendant. Jestem pewien, że to byli oni.";
			link.l1 = "Komendant wie o bandytach, a wciąż nic nie robi?";
			link.l1.go = "fergus_9";
		break;
		
		case "fergus_9":
			dialog.text = "Nie wiem, czy coś robi, czy nie. Jedyna rzecz, którą wiem na pewno, to że moje rzeczy zniknęły, a Twój cenny amulet z nimi. Spróbuj odnaleźć tych bandytów - może znajdziesz go w ich kieszeniach. Mało prawdopodobne, żeby zdążyli go sprzedać - kupcy nie mają potrzeby na takie rzeczy.";
			link.l1 = "Dobrze, pójdę zobaczyć się z komendantem. Powodzenia, Fergus!";
			link.l1.go = "fergus_10";
		break;
		
		case "fergus_10":
			DialogExit();
			AddQuestRecord("Caleuche", "9");
			pchar.questTemp.Caleuche.Bandos = "start"; 
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		// бандит в городе
		case "Beliz_townbandos":
			dialog.text = "Hej!  Czego potrzebujesz?  Nie spodziewam się żadnych gości.  Zjeżdżaj!";
			link.l1 = "Czemu tak niegrzecznie, przyjacielu? Chciałem tylko zapytać...";
			link.l1.go = "Beliz_townbandos_1";
		break;
		
		case "Beliz_townbandos_1":
			dialog.text = "Nie słyszałeś? Wynoś się do cholery, albo wyrzucę cię za drzwi!";
			link.l1 = "Hmm... Cóż, może jednak jesteś osobą, której szukam. Wydajesz się zbyt nerwowy, kumplu...";
			link.l1.go = "Beliz_townbandos_2";
		break;
		
		case "Beliz_townbandos_2":
			dialog.text = "Uważasz się za zbyt sprytnego, co? Jeszcze raz: albo natychmiast się wynosisz, albo wzywam strażników, i wrzucą cię za kraty!";
			link.l1 = "Wsadzić mnie za kraty? Jakież to interesujące. Wiesz, teraz jestem prawie pewien, że znalazłem, kogo szukałem. Dobrze, zgadzam się. Zawołajmy strażników, a potem pójdziemy razem do biura komendanta, jak jedna szczęśliwa rodzina. Właśnie tam byłem, więc pamiętam drogę... Strażnicy! STRAŻNICY!";
			link.l1.go = "Beliz_townbandos_3";
		break;
		
		case "Beliz_townbandos_3":
			dialog.text = "Do diabła z tobą! Przeszyję cię na wylot!";
			link.l1 = "O ho-ho! Cóż, możesz spróbować!";
			link.l1.go = "Beliz_townbandos_4";
		break;
		
		case "Beliz_townbandos_4":
			DialogExit();
			DeleteAttribute(npchar, "CityType");
			DeleteAttribute(npchar, "city"); // чтобы не было НЗГ
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Caleuche_BelizTownbandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
			pchar.quest.Caleuche_letter.win_condition.l1 = "item";
			pchar.quest.Caleuche_letter.win_condition.l1.item = "kaleuche_letter";
			pchar.quest.Caleuche_letter.function = "Caleuche_FindLetter";
		break;
		
		// главарь лесных бандосов
		case "Beliz_forestbandos":
			dialog.text = "Hej, podróżniku! Witaj, witaj... Kolacja, nocleg - wszystko za twoje pieniądze. No, szykuj się na wywrócenie kieszeni na lewą stronę!";
			link.l1 = "Nie tak prędko, mój dobry człowieku. Mam z tobą interesy.";
			link.l1.go = "Beliz_forestbandos_1";
		break;
		
		case "Beliz_forestbandos_1":
			dialog.text = "Interesy? Ha-ha! Twój jedyny interes to oddać mi całe swoje srebro i złoto!";
			link.l1 = "Zamknij się już. Przyniosłem ci list z Belize, na który czekałeś. Posłaniec nie mógł dogadać się ze strażnikami i powierzył mi tę sprawę.";
			link.l1.go = "Beliz_forestbandos_2";
		break;
		
		case "Beliz_forestbandos_2":
			dialog.text = "Pokaż mi!";
			link.l1 = "Oto...";
			link.l1.go = "Beliz_forestbandos_3";
		break;
		
		case "Beliz_forestbandos_3":
			Log_Info("You have given a note");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "kaleuche_letter", 1);
			dialog.text = "(czytając) Hm... To z pewnością dziwne... Jak się w to wplątałeś?";
			link.l1 = "Już ci powiedziałem, złapali twojego człowieka, więc zabrałem jego robotę. Obiecał pieniądze i ciepłe przyjęcie od ciebie...";
			link.l1.go = "Beliz_forestbandos_4";
		break;
		
		case "Beliz_forestbandos_4":
			dialog.text = "A warm welcome? Alright, pal. We'll warm you up, feed you, give you money and all that stuff - but you, you too, will have to prove us that you're not a guards' hound. We've got a score to settle now\nA merchant has recently arrived to a nearby cove; apparently, he wants to sneak into the city with his wares past the customs office. But we will still exact the duty from him. We are lawful folk after all! You'll come with us. Do you know which end of the sword goes where?";
			link.l1 = "I czy dostanę część tej roboty?";
			link.l1.go = "Beliz_forestbandos_5";
		break;
		
		case "Beliz_forestbandos_5":
			dialog.text = "Pewnie, że tak! Jeśli będziesz odważny w walce i jeśli przeżyjesz. Ale nie oczekuj, że to będzie spacerek, kupiec nie jest sam, ma eskortę, i to bardzo dużą eskortę. Cóż, czas ruszać - nasza zdobycz jest blisko. Chłopcy! Przygotujcie broń, wyruszamy!";
			link.l1 = "...";
			link.l1.go = "Beliz_forestbandos_6";
		break;
		
		case "Beliz_forestbandos_6":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			LocatorReloadEnterDisable(pchar.location, "reload2_back", true);
			LocatorReloadEnterDisable(pchar.location, "reload3_back", true);
			for (i=1; i<=6; i++)
			{
				sld = characterFromId("Beliz_forestbandos_"+i);	
				LAi_SetActorType(sld);
				LAi_group_MoveCharacter(sld, "TMP_FRIEND");
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "Beliz_ExitTown", "goto", "goto"+(rand(1)+1), "", 10.0);
			}
			DoQuestCheckDelay("OpenTheDoors", 12.0);
			pchar.quest.Caleuche_bandosrobb.win_condition.l1 = "location";
			pchar.quest.Caleuche_bandosrobb.win_condition.l1.location = "Beliz_ExitTown";
			pchar.quest.Caleuche_bandosrobb.function = "Caleuche_JungleBandosRobbery";
		break;
		
		case "Beliz_forestbandos_7":
			dialog.text = "Widzę, że nie jesteś tchórzem. Dobra robota! Zasłużyłeś na swoją działkę. Jak byś chciał? Gotówka? Towar? Mieli dużo alkoholu, na pewno jest wiele wart.";
			link.l1 = "Pieniądze.";
			link.l1.go = "Beliz_forestbandos_8_1";
			link.l2 = "Towary.";
			link.l2.go = "Beliz_forestbandos_8_2";
		break;
		
		case "Beliz_forestbandos_8_1":
			Log_Info("You have received 100 doubloons");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "gold_dublon", 100);
			dialog.text = "Oto proszę! A ta sakiewka jest za dostarczenie listu.";
			link.l1 = "Dzięki! Właśnie tak to lubię!";
			link.l1.go = "Beliz_forestbandos_9";
		break;
		
		case "Beliz_forestbandos_8_2":
			Log_Info("You have received 30 bottles of rum");
			Log_Info("You have received 12 bottles of wine");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "potionrum", 30);
			TakeNItems(pchar, "potionwine", 12);
			dialog.text = "Oto i masz! Tylko się nie upij na śmierć, ha-ha-ha! A ten mieszek jest za dostarczenie listu.";
			link.l1 = "Dzięki! Tak właśnie to lubię!";
			link.l1.go = "Beliz_forestbandos_9";
		break;
		
		case "Beliz_forestbandos_9":
			Log_Info("You have received a purse");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "purse2", 1);
			dialog.text = "Wyglądasz mi na porządnego człowieka. Co powiesz na kolejny interes? Chodzi o ten list, który dostarczyłeś mi.";
			link.l1 = "Pewnie.";
			link.l1.go = "Beliz_forestbandos_10";
		break;
		
		case "Beliz_forestbandos_10":
			dialog.text = "Więc przyjdź do jaskini. Są ich dwie. Idź do dżungli do punktu, w którym ostatnio się spotkaliśmy, potem wybierz lewą ścieżkę. Zbieramy się za trzy dni przy wejściu do jaskini, od północy do pierwszej. Rozumiesz? Jeśli będziesz grzecznym chłopcem, przyjmiemy cię do naszej szajki. Ale pamiętaj - jeśli coś wygadasz w mieście, jesteś skończony. Mam długie ramię.";
			link.l1 = "Przestań mnie straszyć. Rozumiem. Będę cichy jak ryba. Czekaj na mnie za trzy dni, będę tam. Uwielbiam łatwe pieniądze!";
			link.l1.go = "Beliz_forestbandos_11";
		break;
		
		case "Beliz_forestbandos_11":
			dialog.text = "Dobrze, kumplu. Teraz zmykaj, zanim przyjdą strażnicy. My też się wynosimy.";
			link.l1 = "Do zobaczenia, kumplu...";
			link.l1.go = "Beliz_forestbandos_12";
		break;
		
		case "Beliz_forestbandos_12":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LocatorReloadEnterDisable("Beliz_Jungle_01", "reload2_back", false);
			LocatorReloadEnterDisable("Beliz_Jungle_01", "reload3_back", false);
			LocatorReloadEnterDisable("Beliz_CaveEntrance_2", "reload1_back", true); // закрываем пещеру
			SetFunctionTimerCondition("Caleuche_CaveOpen", 0, 0, 1, false); // таймер
			SetFunctionTimerCondition("Caleuche_BelizbandosClear", 0, 0, 4, false); // таймер
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			for (i=1; i<=6; i++)
			{
				if (GetCharacterIndex("Beliz_forestbandos_"+i) != -1)
				{
					sld = characterFromId("Beliz_forestbandos_"+i);	
					LAi_SetActorType(sld);
					LAi_group_MoveCharacter(sld, "TMP_FRIEND");
					LAi_ActorRunToLocation(sld, "reload", "reload1_back", "", "", "", "OpenTheDoors", 20.0);
				}
			}
			AddQuestRecord("Caleuche", "13");
			// костер
			ref location = &Locations[FindLocation("Beliz_Jungle_01")];
			DeleteAttribute(location, "fire");
			sld = ItemsFromID("fire");
			sld.shown = false;
			// пакуем схрон в пещере
			pchar.GenQuestBox.Beliz_Cave_2 = true;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.kaleuche_amulet2 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.suit4 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.purse1 = 7; // Addon-2016 Jason
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.purse2 = 3; // Addon-2016 Jason
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.potion2 = 10;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.potionrum = 55;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.indian_3 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.obereg_4 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.berserker_potion = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.jewelry2 = 15;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.jewelry3 = 33;
			// меняем флаг
			pchar.questTemp.Caleuche.Bandos = "know";
			SaveCurrentQuestDateParam("questTemp.Caleuche.belizbandos");
		break;
		
		// спалили бандосы в пещере
		case "Beliz_cavebandos":
			dialog.text = "Co! Rozumiem, że postanowiłeś przywłaszczyć sobie część naszego mienia? Nie ujdzie ci to na sucho, ty plugawy robaku!";
			link.l1 = "Jak śmiałeś nazwać mnie robakiem, ty łajdaku?!";
			link.l1.go = "Beliz_cavebandos_1";
		break;
		
		case "Beliz_cavebandos_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_Delete("EnemyFight");
			DialogExit();
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Beliz_cavebandos_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			if (MOD_SKILL_ENEMY_RATE > 4)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Beliz_cavebandos_3", "citiz_23", "man", "man", 30, PIRATE, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, 30, 70, 70, "blade_10", "pistol1", "bullet", 150);
				ChangeCharacterAddressGroup(sld, pchar.location, "monsters", "monster16");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Caleuche_CaveBandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// капитан гарпии
		case "reginald":
			dialog.text = "Witaj, kolego! Co cię tu sprowadza?";
			link.l1 = TimeGreeting()+", mynheer Jackson. Cieszę się, że w końcu cię znalazłem.";
			link.l1.go = "reginald_1";
		break;
		
		case "reginald_1":
			dialog.text = "'Mynheer Jackson', ha-ha! Cóż, szczerze mówiąc, niedługo też tak będę się nazywał. Pracuję dla tej cholernie firmy bez przerwy... ale płacą dobrze, bardzo dobrze!.. Więc, co cię tu sprowadza, kamracie?";
			link.l1 = "Nasze wspólne znajomy, opiekun latarni morskiej, powiedział mi, że masz starożytny indiański amulet. Myślę, że nigdy go nie wykorzystałeś, a ja go naprawdę bardzo potrzebuję. Chcę go od ciebie kupić.";
			link.l1.go = "reginald_2";
		break;
		
		case "reginald_2":
			dialog.text = "O, masz na myśli ten ozdobny drobiazg, o który pytałem tego emerytowanego bosmana? Tak, przyjacielu, masz rację, tak naprawdę nigdy się nie przydał, tylko ładnie wygląda.";
			link.l1 = "Ile za to chcesz?";
			link.l1.go = "reginald_3";
		break;
		
		case "reginald_3":
			dialog.text = "Widzisz, jest mały problem... Pozwól, że wyjaśnię. Nie mam tego teraz ze sobą. Ponieważ nigdy nie znalazłem dla tego zastosowania, zostawiłem to w mojej skrzyni na brzegu, wśród innych moich rzeczy.";
			link.l1 = "Och, to wyjaśnia, że wciąż jesteś... cóż, nieważne. Po prostu idźmy do tej twojej skrzyni, a ja kupię od ciebie amulet. Proste jak drut. Gdzie go masz?";
			link.l1.go = "reginald_4";
		break;
		
		case "reginald_4":
			dialog.text = "To nie jest dokładnie takie proste. Mój kuferek znajduje się na Barbadosie, w wieży latarni morskiej, i jest bezpiecznie zamknięty, aby nikt nie mógł z niego skorzystać pod moją nieobecność. I naprawdę mi przykro, ale nie mogę z tobą popłynąć na Barbados, zgodnie z moim kontraktem z Holendrami muszę żeglować między Philipsburgiem a Port Royal i trzymać się ściśle harmonogramu. A Barbados jest daleko od tej trasy.";
			link.l1 = "I co możemy zrobić? Naprawdę, naprawdę potrzebuję tego amuletu!";
			link.l1.go = "reginald_5";
		break;
		
		case "reginald_5":
			dialog.text = "Hmm... Cóż, jest jedna opcja. Dam ci klucz do mojej skrzyni, a ty popłyniesz na Barbados na własną rękę. Ale będziesz musiał mi zrekompensować wszystkie rzeczy, które się w niej znajdują, i możesz je zatrzymać. Przepraszam za brak zaufania - ale musisz zrozumieć. Nigdy cię wcześniej nie widziałem.";
			link.l1 = "Ile to kosztuje?";
			link.l1.go = "reginald_6";
		break;
		
		case "reginald_6":
			dialog.text = "Pięćset złotych monet. Ani mniej.";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Masz to! Oto twoje złoto.";
				link.l1.go = "reginald_10";
			}
			link.l2 = "Hmm... Nie mam przy sobie tylu dublonów.";
			link.l2.go = "reginald_7";
		break;
		
		case "reginald_7":
			dialog.text = "W takim razie przyjdź do mnie ponownie, gdy już zgromadzisz pieniądze. Skoro raz mnie znalazłeś, znajdziesz mnie znowu. Zamierzam teraz żeglować między St. Martin a Jamajką przez dość długi czas.";
			link.l1 = "Dobrze, umowa stoi.";
			link.l1.go = "reginald_8";
		break;
		
		case "reginald_8":
			DialogExit();
			NextDiag.CurrentNode = "reginald_9";
			npchar.DeckDialogNode = "reginald_9";
		break;
		
		case "reginald_9":
			dialog.text = "Znowu ty, przyjacielu? Masz 500 monet?";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Tak. Oto twoje złoto.";
				link.l1.go = "reginald_10";
			}
			link.l2 = "Jeszcze nie, ale pracuję nad tym.";
			link.l2.go = "reginald_8";
		break;
		
		case "reginald_10":
			Log_Info("You have given 500 doubloons");
			PlaySound("interface\important_item.wav");
			RemoveDublonsFromPCharTotal(500);
			DeleteAttribute(pchar, "GenQuest.SeaHunter2Pause"); // вертаем морских ОЗГов
			dialog.text = "Świetnie! A oto twój klucz. Mam tylko jedną prośbę: po zabraniu wszystkiego, co tam jest, zostaw proszę klucz w zamku. Nie chciałbym zlecać wykonania nowego zamka i klucza do niego.";
			link.l1 = "Dobrze.";
			link.l1.go = "reginald_11";
		break;
		
		case "reginald_11":
			dialog.text = "W takim razie szczęścia, przyjacielu! Bon voyage!";
			link.l1 = " I tobie również... Bon voyage, panie Jackson!";
			link.l1.go = "reginald_12";
		break;
		
		case "reginald_12":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true;
			DeleteAttribute(pchar, "questTemp.Caleuche.Garpiya");
			DeleteAttribute(pchar, "questTemp.Garpiya");
			GiveItem2Character(pchar, "kaleuche_key"); 
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key");
			AddQuestRecord("Caleuche", "20");
			// сундук со схроном
			i = Findlocation("Mayak2");
			Locations[i].models.always.locators = "lighthouse_Blocators";
			locations[i].private1.key = "kaleuche_key";
			locations[i].private1.key.delItem = true;
			locations[i].private1.items.kaleuche_amulet3 = 1;
			locations[i].private1.items.pistol9 = 1;
			locations[i].private1.items.indian_6 = 1;
			locations[i].private1.items.map_barbados = 1;
			locations[i].private1.items.map_part2 = 1;
			locations[i].private1.items.jewelry22 = 5;
			locations[i].private1.items.jewelry17 = 6;
			locations[i].private1.items.jewelry12 = 3;
			locations[i].private1.items.jewelry16 = 2;
			locations[i].private1.items.jewelry20 = 7;
			locations[i].private1.items.jewelry53 = 11;
			locations[i].private1.items.mineral25 = 1;
			locations[i].private1.items.mineral21 = 1;
			locations[i].private1.items.mineral22 = 5;
			locations[i].private1.items.mineral26 = 1;
			locations[i].private1.items.mineral10 = 1;
			locations[i].private1.items.mineral3 = 10;
			pchar.quest.caleuche_amulet3.win_condition.l1 = "item";
			pchar.quest.caleuche_amulet3.win_condition.l1.item = "kaleuche_amulet3";
			pchar.quest.caleuche_amulet3.function = "Caleuche_ThirdAmuletFind";
		break;
		
		// монах в Виллемстаде
		case "monk_caleuche":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("villemstad");
			npchar.lifeday = 1;
			dialog.text = "Cześć, kapitanie "+GetFullName(pchar)+" . Cieszę się, że mogę powitać cię w Willemstad.";
			link.l1 = "Cześć, ojcze. Nie pamiętam cię. Czy się znamy?";
			link.l1.go = "monk_caleuche_1";
		break;
		
		case "monk_caleuche_1":
			dialog.text = "Rozpytałem się o ciebie, gdy tylko twój statek zacumował. I myślę, że mogę cię poprosić o pomoc.";
			link.l1 = "Bardzo interesujące. A dlaczego ja?";
			link.l1.go = "monk_caleuche_2";
		break;
		
		case "monk_caleuche_2":
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				dialog.text = "Ponieważ zrobiłeś wiele dla Republiki Wolnych Prowincji. Masz dobrą reputację w Kompanii i jesteś przyjacielem gubernatora. Już odwoływałem się do kilku instancji i zostałem skarcony, ale mam nadzieję, że szlachetna osoba taka jak ty nie odrzuci pokornej prośby sługi naszego Pana.";
			}
			else
			{
				dialog.text = "Ponieważ nie jesteś na służbie naszego gubernatora. Nie pracujesz dla Kompanii i nie masz żadnych spraw z naszym wojskiem - w przeciwnym razie najprawdopodobniej zbyłbyś mnie jak irytującą muchę, ponieważ już odwoływałem się do kilku instancji i zostałem odrzucony.";
			}
			link.l1 = "Zgoda, zatem. Jaki jest charakter twojej prośby?";
			link.l1.go = "monk_caleuche_3";
		break;
		
		case "monk_caleuche_3":
			sld = characterFromId("Villemstad_Priest");
			dialog.text = "Za bankiem stoi dom. Mieszkała tam pewna dama, która wynajmowała pokój jednemu bardzo podejrzanemu typowi, ani miejscowemu, ani Holendrowi. I tak nasz ojciec przełożony, Ojciec "+sld.name+", rozpoznał go\nTo był Joachim Merriman, Portugalczyk, oskarżony przez Inkwizycję o czary i konszachty z nieczystymi siłami. Ukrywał się przed Inkwizycją w Nowym Świecie. Wiesz, Hiszpanie często oskarżają tych, którzy nie są w łasce, o herezję i czary, aby ich spalić na stosie, ale... W tym przypadku mieli rację. Merriman to czarownik\nWięc mieszkał w Willemstad przez jakiś czas, a potem zniknął tak nagle, jak się pojawił. A po jakimś czasie kobieta, ta która wynajęła mu pokój, nigdy nie była widziana wychodząc z tego domu. Nigdy! I od tamtej pory nikt jej nigdy nigdzie nie widział\nA nocami mieszkańcy czasami widzą czerwono-niebieskie światła migoczące w oknach na drugim piętrze i słyszą dziwne dźwięki, prawie jakby jakieś nieświęte krzyki. Ojciec "+sld.name+" odwołał się do komendanta. Wysłał patrol czterech żołnierzy, przeszukali dom, ale nic nie znaleźli: ani gospodyni, ani nikogo innego, ani nic podejrzanego w ogóle\nAle te dziwne rzeczy nadal się dzieją. Gospodyni nigdy się nie pojawiła, a to piekielne światło wciąż można tam zobaczyć nocami. Poza tym, dwóch żebraków niedawno zaginęło. Słyszałem ich, jak rozmawiali na dziedzińcu - wiedzieli, że w domu nie ma właścicieli, więc postanowili się tam zatrzymać. Nikt ich nie widział odtąd.";
			link.l1 = "Rozumiem, że chcesz, abym wszedł do tego domu i sprawdził, co się naprawdę stało?";
			link.l1.go = "monk_caleuche_4";
		break;
		
		case "monk_caleuche_4":
			dialog.text = "Dokładnie, szlachetny panie. Proszę, pomóż Świętemu Kościołowi. Komendant mówi, że to sobie wyobrażamy, bo jego patrol nigdy nic nie znalazł. Rząd myśli to samo. Zwykli ludzie po prostu się tym nie przejmują, bo nie widzą w tym bezpośredniego zagrożenia dla siebie.";
			link.l1 = "Hmm... I będę musiał tam pójść w nocy?";
			link.l1.go = "monk_caleuche_5";
		break;
		
		case "monk_caleuche_5":
			sld = characterFromId("Villemstad_Priest");
			dialog.text = "Tak, panie. Jest tam cicho w ciągu dnia, dlatego żołnierze nic nie znaleźli. Myślę, że komendant boi się o swoich ludzi, ja też bym się bał. Ale proszę, błagam cię. Ojcze "+sld.name+"podziękuje ci i nagrodzi cię za twoją służbę. Gdy już odwiedzisz tę norę w nocy, proszę powiedz mu, co tam znajdziesz. Zapewniam cię, nasze obawy są dobrze uzasadnione.";
			link.l1 = "Dobrze. Pomyślę o tym.";
			link.l1.go = "monk_caleuche_6";
		break;
		
		case "monk_caleuche_6":
			dialog.text = "Dziękuję, kapitanie. Mam nadzieję, że nie odrzucisz mojej pokornej prośby. Proszę, uczyń to w imię naszego Pana, naszej wiary i wszystkiego, co święte. Idź z moim błogosławieństwem.";
			link.l1 = "...";
			link.l1.go = "monk_caleuche_7";
		break;
		
		case "monk_caleuche_7":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload7_back", "none", "", "", "", -1);
			AddQuestRecord("Caleuche", "24");
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				if (CheckAttribute(pchar, "questTemp.Caleuche.SolomonSkul")) sTemp = "visit the house of Joaquim Merriman, where, according to him, strange things happen at night. Remembering that special gleam in Merriman's eyes when he looked at the jade skull, I feel a little creepy. It seems that the old Jew could not resist the sum of half a million pesos. Whatever the case, I don`t feel like going to Merriman former abode at night.";
				else sTemp = "visit the house of my old acquaintance Joachim Merriman, where, allegedly, strange things are happening at nights. I still remember that glitter in Merriman's eyes, when he was looking at the skull, and honestly I feel frightened. I am not really fond of the idea to visit his former abode in the night, who knows what kind of devils lurk there.";
			}
			else sTemp = "visit the house at the back of the bank, where some Joachim Merriman had been renting a room. Apparently it is that warlock, of which Tuttuathapak was talking about. According to the monk, strange things are happening in this house in the night. I really feel uncomfortable about visiting the warlock's former home, who knows what kind of devils lurk there.";
			AddQuestUserData("Caleuche", "sText", sTemp);
			i = Findlocation("Villemstad_town");
			DeleteAttribute(&locations[i], "reload.l14.close_for_night");
			pchar.quest.Caleuche_villemstadhouse.win_condition.l1 = "location";
			pchar.quest.Caleuche_villemstadhouse.win_condition.l1.location = "Villemstad_houseSp1_room";
			pchar.quest.Caleuche_villemstadhouse.win_condition.l2 = "Hour";
			pchar.quest.Caleuche_villemstadhouse.win_condition.l2.start.hour = 1.00;
			pchar.quest.Caleuche_villemstadhouse.win_condition.l2.finish.hour = 3.00;
			pchar.quest.Caleuche_villemstadhouse.function = "Caleuche_CreateJoakimSkel";
		break;
		
		// охотник у пещеры
		case "cavehunter":
			dialog.text = "Trzymaj się, kamracie. Lepiej tam nie idź, jeśli cenisz swoje życie.";
			link.l1 = "I o co chodzi?";
			link.l1.go = "cavehunter_1";
		break;
		
		case "cavehunter_1":
			dialog.text = "Uwierz mi, nie chcesz wiedzieć. Ale Śmierć sama czai się za rogiem, i mogę przysiąc na Księgę, że nie wrócisz żywy, są rzeczy poza twoją wyobraźnią.";
			link.l1 = "Cóż, skoro tak mówisz, nie będę kusił losu. Dzięki za ostrzeżenie.";
			link.l1.go = "cavehunter_2";
		break;
		
		case "cavehunter_2":
			dialog.text = "Nie ma za co. Trzymaj się z dala od tej ścieżki.";
			link.l1 = "...";
			link.l1.go = "cavehunter_3";
		break;
		
		case "cavehunter_3":
			DialogExit();
			npchar.dialog.currentnode = "cavehunter_4";
		break;
		
		case "cavehunter_4":
			dialog.text = "Trzymaj się z dala od tej ścieżki, kumplu.";
			link.l1 = "Tak, pamiętam...";
			link.l1.go = "cavehunter_4_1";
		break;
		
		case "cavehunter_4_1":
			DialogExit();
			npchar.dialog.currentnode = "cavehunter_4";
		break;
		
		case "cavehunter_5":
			sld = characterFromId("Havana_Priest");
			dialog.text = "Jesteś pewien, że chcesz tam pójść?";
			link.l1 = "Absolutnie. "+sld.name+", ojciec przeor kościoła w Hawanie, wysłał mnie tutaj. Muszę ustalić, co się tutaj dzieje, i podjąć odpowiednie środki.";
			link.l1.go = "cavehunter_6";
		break;
		
		case "cavehunter_6":
			dialog.text = "Co się tu dzieje? Obawiam się, że będziesz trząsł się ze strachu, gdy zobaczysz, co tu się dzieje na własne oczy.";
			link.l1 = "Masz na myśli chodzących zmarłych?";
			link.l1.go = "cavehunter_7";
		break;
		
		case "cavehunter_7":
			dialog.text = "Tak. I lepiej uwierz w moje słowa.";
			link.l1 = "I wierzę ci. Już spotkałem to przeklęte monstrum w Willemstad i zniszczyłem je. A teraz wejdę tam i zniszczę wszelkie plugastwo, które czai się w tej jaskini.";
			link.l1.go = "cavehunter_8";
		break;
		
		case "cavehunter_8":
			int icpy = GetOfficersQuantity(pchar);
			switch (icpy)
			{
				case 0:
					dialog.text = "Czy zamierzasz iść tam sam? Jesteś martwy, kompanie. Nie masz pojęcia, ile z tych rzeczy tam jest. Cóż, idź, jeśli musisz, a ja pójdę do kościoła zapalić świecę za spokój twojej duszy.";
					link.l1 = "Nie śpiesz się z moim pogrzebem. Widziałem gorsze rzeczy.";
					link.l1.go = "cavehunter_exit";
				break;
				
				case 1:
					dialog.text = "Tylko was dwoje? Obawiam się, że daleko nie zajdziecie. Nie macie pojęcia, ile tego tam jest. To samobójstwo.";
					link.l1 = "Po prostu nas nie znasz dobrze, przyjacielu. Odejdź, a my oczyścimy tę bezbożną norę.";
					link.l1.go = "cavehunter_exit";
				break;
				
				case 2:
					dialog.text = "Tylko was trzech? Musicie być doświadczonymi wojownikami, skoro się na to odważacie. Ale wciąż obawiam się, że nie dacie rady. Nie macie pojęcia, ile tych rzeczy jest tam wewnątrz tej groty.";
					link.l1 = "Po prostu nas nie znasz dobrze, przyjacielu. Odsuń się, a oczyścimy tę nieświętą norę.";
					link.l1.go = "cavehunter_exit";
				break;
				
				case 3:
					dialog.text = "Nie jesteście tchórzami, widzę. Ale naprawdę nie macie pojęcia, ile tych cholerstw tam jest. W takiej sprawie każdy człowiek się liczy. Do diabła, pójdę z wami i wystrzelam to plugastwo z mojego muszkietu!";
					link.l1 = "Jesteś odważną duszą, przyjacielu. Nie odrzucę twojej pomocy. Chodźmy!";
					link.l1.go = "cavehunter_9";
				break;
			}
		break;
		
		case "cavehunter_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
		break;
		
		case "cavehunter_9":
			DialogExit();
			npchar.quest.caleuche = true;
			npchar.dialog.currentnode = "cavehunter_10";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			// закрываем локаторы выхода
			LocatorReloadEnterDisable("Cuba_Jungle_07", "reload1_back", true);
			LocatorReloadEnterDisable("Cuba_Jungle_07", "reload3_back", true);
		break;
		
		case "cavehunter_10":
			dialog.text = "Naprzód! Śmierć plugawym nieumarłym!";
			link.l1 = "...";
			link.l1.go = "cavehunter_10_1";
		break;
		
		case "cavehunter_10_1":
			DialogExit();
			npchar.dialog.currentnode = "cavehunter_10";
		break;
		
		case "cavehunter_11":
			dialog.text = "Toż to była prawdziwa rzeź! Kto by pomyślał, że tylu umarłych kryło się w tym miejscu! No cóż, przynajmniej teraz możemy odpocząć... Proszę, powiedz o tym swojemu przełożonemu ojcu, temu który cię tu przysłał. Mam nadzieję, że Inkwizycja się tym zajmie po twoim raporcie. W końcu, rozprawianie się z nieumarłymi leży w ich gestii, ja jestem tylko prostym myśliwym.";
			link.l1 = "Na pewno mu powiem. Dzięki za pomoc, kumplu. Jesteś rzadkim rodzajem, niewielu ośmieliłoby się walczyć ze samą śmiercią! Powodzenia!";
			link.l1.go = "cavehunter_exit";
		break;
		
		// солдат в крипте при провале
		case "cryptguard":
			dialog.text = "Stój, gdzie jesteś! To miejsce jest niedostępne!";
			link.l1 = "Ehh... A co tam jest?";
			link.l1.go = "cryptguard_1";
		break;
		
		case "cryptguard_1":
			dialog.text = "Niebezpieczny czarownik został tam znaleziony. Tylko święci ojcowie i towarzyszący im żołnierze mogą wejść.";
			link.l1 = "Widzę. Czy czarownik został aresztowany?";
			link.l1.go = "cryptguard_2";
		break;
		
		case "cryptguard_2":
			dialog.text = "Nie mam uprawnień, by odpowiadać na takie pytania, señor. Czas, abyś opuścił to miejsce.";
			link.l1 = "Dobrze, rozumiem. Powodzenia!";
			link.l1.go = "cryptguard_3";
		break;
		
		case "cryptguard_3":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Caleuche", "31");
			CloseQuestHeader("Caleuche");
			pchar.questTemp.Caleuche = "end";
		break;
		
		// чавинави-вождь
		case "Chavinavi":
			PlaySound("Voice\English\LE\Chavinavi\Chavinavi_01.wav");
			dialog.text = "Stój spokojnie, człowieku! Jesteś w samym sercu świątyni i zaszedłeś za daleko, by się teraz wycofać.";
			link.l1 = "Kim jesteś?!";
			link.l1.go = "Chavinavi_1";
		break;
		
		case "Chavinavi_1":
			dialog.text = "Jestem wodzem Chavinavi, strażnikiem i opiekunem tego świętego miejsca. Nie jesteś pierwszym, który wszedł do tej świątyni, ale tylko dwóch mężczyzn i jedna kobieta weszli i wyszli z niej żywi przed tobą. To jedyny powód, dla którego zniżam się teraz do rozmowy z tobą. Dlaczego tu przyszedłeś, blada twarzo?";
			link.l1 = "Przyniosłem tutaj starożytny relikt, jadeitową czaszkę. Pięćdziesiąt lat temu została zabrana z indyjskiej świątyni głęboko na lądzie. Zamierzałem odnaleźć kapliczkę i zwrócić relikt twojemu bogu.";
			link.l1.go = "Chavinavi_2";
		break;
		
		case "Chavinavi_2":
			dialog.text = "To dziwne słyszeć takie słowa od kogoś z twojego rodzaju. Nie wierzę ci. Wy, bladoskórzy, zawsze przychodzicie, by coś zabrać, ale nigdy nic nie oddajecie.";
			link.l1 = "Nie kłamię. Zwracając czaszkę, zdejmę klątwę nałożoną na kapitana statku widmo, który terroryzuje karaibskie morze, co uczyni go znów śmiertelnym, a ja na zawsze uwolnię świat od niego.";
			link.l1.go = "Chavinavi_3";
		break;
		
		case "Chavinavi_3":
			dialog.text = "Skąd wiesz, że nasz Bóg zdejmie tę klątwę, blady twarzu? Czy nasz Bóg z tobą rozmawia?";
			link.l1 = "Nie. Przybyłem tu za radą wielkiego szamana imieniem Tuttuathapak. Jak powiedział, czaszka jest kluczem do klątwy, a to jedyna świątynia na Karaibach. I wiesz co - myślę, że on rzeczywiście potrafi rozmawiać z duchami przeszłości. Może nawet z tobą, wodzu wojowników jaguara.";
			link.l1.go = "Chavinavi_4";
		break;
		
		case "Chavinavi_4":
			dialog.text = "Twoje słowa mnie zaskakują, blady, ale wciąż nie mogę ci całkowicie zaufać. Jednakże, jeśli przyszedłeś do tej świątyni, aby zwrócić nasz relikt, z pewnością nasz szaman musiał opowiedzieć ci o tym miejscu, jego stworzeniu, historii i mieszkańcach\nJeśli tak, z łatwością odpowiesz na wszystkie moje pytania. Wtedy przyznam, że byłeś wobec mnie szczery, pozwolę ci przejść i, co więcej, nagrodzę cię.";
			link.l1 = "Wtedy zapytaj!";
			link.l1.go = "question1";
		break;
		
		case "question1":
			dialog.text = "I am the chieftain of the Chavinavi, and the jaguar warriors. Thousand years ago I was human; now I am carrying out my sacred duty in these chambers. Which god commands me?";
			link.l1 = "Mictlantecuhtli.";
			link.l1.go = "question1_l";
			link.l2 = "Kukulcan.";
			link.l2.go = "question1_l";
			link.l3 = "Yum Cimil.";
			link.l3.go = "question1_r";
			link.l4 = "Inti.";
			link.l4.go = "question1_l";
			link.l5 = "Kauil.";
			link.l5.go = "question1_l";
		break;
		
		case "question1_r":
			dialog.text = "Zanim przybyli wasi bladzi ludzie, cała ta ziemia, od wielkiego śniegu na północy po wielkie równiny na południu, należała do nas, braci jednej rodziny...";
			link.l1 = "";
			link.l1.go = "question2";
		break;
		
		case "question1_l":
			dialog.text = "Zanim przybyli wasi bladzi ludzie, cała ta ziemia, od wielkiego śniegu na północy po wielkie równiny na południu, należała do nas, braci jednej rodziny...";
			link.l1 = "";
			link.l1.go = "question2";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question2":
			dialog.text = "Jaki indiański plemię zbudowało tę świątynię?";
			link.l1 = "Inkowie.";
			link.l1.go = "question2_l";
			link.l2 = "Chavins.";
			link.l2.go = "question2_r";
			link.l3 = "Maja.";
			link.l3.go = "question2_l";
			link.l4 = "Aztek.";
			link.l4.go = "question2_l";
			link.l5 = "Arawak.";
			link.l5.go = "question2_l";
		break;
		
		case "question2_r":
			dialog.text = "Nasz lud postępował, ucząc się mądrości, i podporządkowywał nowe lasy, równiny i wyspy. Ludzie, którzy zbudowali tę świątynię, przybyli z lasów zza Wielkiej Wody...";
			link.l1 = "";
			link.l1.go = "question3";
		break;
		
		case "question2_l":
			dialog.text = "Nasi ludzie postępowali naprzód, zdobywając mądrość, i ujarzmiali nowe lasy, równiny i wyspy. Ludzie, którzy zbudowali tę świątynię, przybyli z lasów zza Wielkiej Wody...";
			link.l1 = "";
			link.l1.go = "question3";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question3":
			dialog.text = "Kto prowadził grupę tych chwalebnych ludzi?";
			link.l1 = "Wielki wodzu.";
			link.l1.go = "question3_l";
			link.l2 = "Wielki kapłan.";
			link.l2.go = "question3_l";
			link.l3 = "Syn wielkiego wodza.";
			link.l3.go = "question3_r";
			link.l4 = "Syn wielkiego kapłana.";
			link.l4.go = "question3_l";
			link.l5 = "Załoga nie miała dowódcy.";
			link.l5.go = "question3_l";
		break;
		
		case "question3_r":
			dialog.text = "Indianie, dzielni wojownicy i podróżnicy, zawsze kochali i czcili swoją ojczyznę, nawet po osiedleniu się w nowym miejscu. Na znak miłości do swojego domu zbudowali posąg w świątyni w formie ptaka, symbolu ich domu. Jest za mną...";
			link.l1 = "";
			link.l1.go = "question4";
		break;
		
		case "question3_l":
			dialog.text = "Indianie, dzielni wojownicy i podróżnicy, zawsze kochali i czcili swoją ojczyznę, nawet po osiedleniu się w nowym miejscu. Jako wyraz miłości do swojej ziemi ojczystej zbudowali posąg w świątyni w formie ptaka, symbolu ich domu. Jest za mną...";
			link.l1 = "";
			link.l1.go = "question4";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question4":
			dialog.text = "Jak się nazywa ten ptak?";
			link.l1 = "Albatros.";
			link.l1.go = "question4_l";
			link.l2 = "Orzeł.";
			link.l2.go = "question4_l";
			link.l3 = "Sęp.";
			link.l3.go = "question4_l";
			link.l4 = "Rok.";
			link.l4.go = "question4_l";
			link.l5 = "Kondor.";
			link.l5.go = "question4_r";
		break;
		
		case "question4_r":
			dialog.text = "Minęły lata dobrobytu i zbladły, jak płomień lampy, a życie opuściło wyspę. Tylko świątynia pozostała tu jako przypomnienie wielkiej potęgi starożytnych Indian. Ostatni szaman pozostawił na piedestale świętą słoneczną kulę, która dawała moc odważnym i karała niegodziwych. Została zabrana przez człowieka, który był tu przed tobą.";
			link.l1 = "";
			link.l1.go = "question5";
		break;
		
		case "question4_l":
			dialog.text = "Minęły lata dobrobytu i zniknęły, jak płomień lampy, a życie opuściło wyspę. Tylko świątynia pozostała tutaj jako przypomnienie wielkiej mocy starożytnych Indian. Ostatni szaman pozostawił na piedestale świętą słoneczną kulę, która dawała moc odważnym i karała niegodziwych. Zabrano ją przez człowieka, który był tu przed tobą.";
			link.l1 = "";
			link.l1.go = "question5";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question5":
			dialog.text = "Jak się nazywała ta święta kula?";
			link.l1 = "Kula lśniącego słońca.";
			link.l1.go = "question5_l";
			link.l2 = "Kula promieni słonecznych.";
			link.l2.go = "question5_l";
			link.l3 = "Kula południowego słońca.";
			link.l3.go = "question5_l";
			link.l4 = "Kula wschodzącego słońca.";
			link.l4.go = "question5_r";
			link.l5 = "Kula zachodzącego słońca.";
			link.l5.go = "question5_l";
		break;
		
		case "question5_r":
			if (CheckAttribute(pchar, "questTemp.Caleuche.QuestionFail"))
			{
				PlaySound("Voice\English\LE\Chavinavi\Chavinavi_02.wav");
				dialog.text = "Złe odpowiedzi wskazują, że mnie okłamałeś, biały człowieku! Przyszedłeś z niecnymi zamiarami! Udało ci się przemknąć obok strażników świątyni i sanktuarium, rozgryzłeś, jak działa mechanizm drzwi - ale wciąż nie uciekniesz przed śmiertelnym pojedynkiem ze mną. Przygotuj się na śmierć, blada twarzo!";
				link.l1 = "Cóż, skoro nalegasz - zobaczymy, jak wielkim wojownikiem jesteś...";
				link.l1.go = "chavinavi_fight";
			}
			else
			{
				dialog.text = "Twoja wiedza o moim narodzie i mojej świątyni przynosi ci zaszczyt, bladolicy. Teraz ci wierzę. Idź i spełnij to, po co tu przyszedłeś. Umieść święty relikwiarz na piedestale przed kondorem, gdzie kiedyś znajdowała się kula wschodzącego słońca\nNastępnie wróć do mnie. Twoje oddanie Yum Cimilowi i decyzja o dobrowolnym zwróceniu tego, co zostało skradzione przez twoich braci, muszą zostać nagrodzone.";
				link.l1 = "Dziękuję za zaufanie, wielki wodzu.";
				link.l1.go = "chavinavi_exit";
			}
		break;
		
		case "question5_l":
			PlaySound("Voice\English\LE\Chavinavi\Chavinavi_02.wav");
			dialog.text = "Złe odpowiedzi wskazują, że mnie okłamałeś, białasie! Przyszedłeś z niecnymi zamiarami! Udało ci się przemknąć obok strażników świątyni i sanktuarium, rozgryzłeś mechanizm drzwi – ale i tak nie uciekniesz przede mną w śmiertelnej walce. Przygotuj się na śmierć, blada twarzo!";
			link.l1 = "Cóż, skoro nalegasz - zobaczmy, jak wielkim wojownikiem jesteś...";
			link.l1.go = "chavinavi_fight";
		break;
		
		case "chavinavi_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_Delete("EnemyFight");
			DialogExit();
			n = 1;
			if (MOD_SKILL_ENEMY_RATE > 2) n = 3;
			if (MOD_SKILL_ENEMY_RATE > 4) n = 5;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("TopChavinavi_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Caleuche_TopChavinaviDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "chavinavi_exit":
			DialogExit();
			sld = ItemsFromID("SkullAztec");
			sld.shown = "0";
			sld.useLocation = "KhaelRoa_Treasure_Alcove";
			sld.useLocator = "button01";
			LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
		break;
		
		case "Chavinavi_5":
			PlaySound("Voice\English\LE\Chavinavi\Chavinavi_03.wav");
			dialog.text = "Zrobiłeś to, co obiecałeś, blada twarzo. Cieszę się, że nie byłeś kłamcą jak większość twoich braci. Ja również dotrzymam słowa. Oto weź ten dar ode mnie - symbol potęgi wojowników jaguara. Sam Yum Cimil obdarzył to futro odrobiną swojej mocy.";
			link.l1 = "O rany! Jest takie piękne!";
			link.l1.go = "Chavinavi_6";
		break;
		
		case "Chavinavi_6":
			GiveItem2Character(pchar, "KhaelRoa_item");
			Log_Info("You have received jaguar's pelt");
			PlaySound("interface\important_item.wav");
			dialog.text = "To nie jest zwykła skóra. Gdy ją założysz, zyskasz siłę jaguarowego wojownika. Moc twojej broni, która zionie ogniem i strzela ołowiem, zwiększy się dziesięciokrotnie, a ty będziesz mógł zasypać pole bitwy trupami swoich wrogów\nLecz żaden śmiertelnik nie może utrzymać mocy, którą w tę skórę włożył Yum Cimil. Gdy ją uwolnisz, będzie ci towarzyszyć tylko do następnej północy, a potem zniknie. Dbaj o nią, bladolicy, i nie marnuj jej mocy na drobne potyczki.";
			link.l1 = "Dziękuję! Użyję tego tylko wtedy, gdy będę całkowicie przytłoczony przez wrogów.";
			link.l1.go = "Chavinavi_7";
		break;
		
		case "Chavinavi_7":
			dialog.text = "Teraz idź. I ostrzeż swoich braci przed zakłócaniem spokoju tych świętych komnat. Wojownicy jaguara nie okazują litości bladoskórym i nie dadzą im pardonu.";
			link.l1 = "Żegnaj, wodzu.";
			link.l1.go = "Chavinavi_8";
		break;
		
		case "Chavinavi_8":
			DialogExit();
			LAi_SetPlayerType(pchar);
			n = 1;
			if (MOD_SKILL_ENEMY_RATE > 2) n = 3;
			if (MOD_SKILL_ENEMY_RATE > 4) n = 5;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("TopChavinavi_"+i);	
				LAi_SetWarriorType(sld);
				LAi_CharacterDisableDialog(sld);
			}
			AddQuestRecord("Caleuche", "38");
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeIndianRelation(10.0);
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

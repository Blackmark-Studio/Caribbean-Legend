// диалог прочих и малозначимых НПС
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i, n, iTemp;
	string attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Czy czegoś potrzebujesz?";
			link.l1 = "Nie, nie teraz.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// --> матрос на корабле, прибытие в Сен-Пьер
		case "Startsailor":
			dialog.text = "Psiakrew, nareszcie ziemia! Obudź się, monsieur... cokolwiek masz na imię... dotarliśmy!";
			link.l1 = "A-ach! Już poranek? Co to za przeklęte gorąco i wilgoć?";
			link.l1.go = "Startsailor_1";
			link.l2 = "Rzekę! Charles de Maure! Szlachcic, wiecie. Jak można w ogóle pić w tym upale? Wolałbym trochę wody, na miłość boską.";
			link.l2.go = "Startsailor_1a";
		break;
		
		case "Startsailor_1":
			dialog.text = "Przyzwyczaj się do tego, monsieur. To jedyna pogoda, jaką tu mamy... zawsze mogło być gorzej.";
			link.l1 = "Jak mogło być gorzej!? Mam na sobie tylko lnianą koszulę, a pot leje mi się po plecach!";
			link.l1.go = "Startsailor_2";			
		break;
		
		case "Startsailor_2":
			dialog.text = "Zobaczysz, haha! Może być sezon huraganów! Pośpiesz się, monsieur. Szalupa nie będzie na ciebie czekać. Nie chcesz chyba płynąć wpław do Martyniki, prawda?";
			link.l1 = "Daj mi chwilę, dobrze? Gdzie jest mój miecz? Ach, oto jest...";
			link.l1.go = "Startsailor_3";			
		break;
		
		case "Startsailor_3":
			dialog.text = "Nie jesteś już w Europie... Bądź ostrożny, monsieur. To niespokojne czasy. Plotki mówią, że Kompania Wysp Amerykańskich sprzedała wyspę Martynika jakimś religijnym fanatykom, krzyżowcom czy jakiemuś innemu szaleństwu. Jeszcze nie zauważyłem niczego niezwykłego, przynajmniej patrząc na brzeg z pokładu. Ale skoro byliśmy nieobecni przez jakiś czas, wiele mogło się zmienić pod moją nieobecność.";
			link.l1 = "Krzyżowcy? Niedorzeczność!";
			link.l1.go = "Startsailor_4";			
		break;
		
		case "Startsailor_4":
			dialog.text = "„Niezależnie od tego, czy to bzdury, czy nie, plotki krążą wszędzie. Już mamy wystarczająco kłopotów. Kanibale w dżungli, tropikalna gorączka, piraci, bandyci w zaułkach, nie wspominając już o Hiszpanach i Anglikach...”";
			link.l1 = "Och, znowu to samo... W tej chwili jedynym problemem, jaki widzę, jest przytłaczające ciepło i komary... Dobrze, jestem gotów. Idziemy?";
			link.l1.go = "Startsailor_5";			
		break;
		
		case "Startsailor_5":
			dialog.text = "Idź na pokład i wejdź na szalupę, Monsieur. Witamy na Karaibach!";
			link.l1 = "";
			link.l1.go = "Startsailor_6";			
		break;
		
		case "Startsailor_1a":
			dialog.text = "Nie ma tu innej pogody, 'Wasza Lordowska Mość'. Jeśli już, to tylko się pogarsza.";
			link.l1 = "Pogoda jest nie do zniesienia, tak samo jak moje towarzystwo w ostatnich miesiącach. Mam nadzieję, że na Archipelagu znajdą się jacyś przyzwoici ludzie.";
			link.l1.go = "Startsailor_2a";
			AddCharacterExpToSkill(pchar, "Leadership", 10);
		break;
		
		case "Startsailor_2a":
			dialog.text = "Cóż, myślę, że wszyscy będziemy zadowoleni, gdy w końcu nas opuścisz, monsieur. Łódź czeka. Nie wyskakuj z portek z radości. I nie zapomnij swoich rzeczy - statek płynie dalej, a możesz je równie dobrze zapomnieć, jeśli tego nie zrobisz.";
			link.l1 = "Jakbym miał je zostawić dla twojej przyjemności. Pesos, szabla - wygląda na to, że mnie nie obrabowano.";
			link.l1.go = "Startsailor_3a";			
		break;
		
		case "Startsailor_3a":
			dialog.text = "Oczywiście jesteśmy uczciwymi ludźmi, ale masz rację - zawsze miej oko na swoje rzeczy, bo ktoś może opróżnić twoje kieszenie. Tak jak w starej Europie. Albo wszędzie, naprawdę. Ale to miejsce nie jest jak dom. Jacyś fanatycy założyli tutaj bazę. Mówią, że potajemnie kupili całą wyspę. Więc bądź czujny i nie zwracaj na siebie uwagi.";
			link.l1 = "Co za bzdury!";
			link.l1.go = "Startsailor_4a";			
		break;
		
		case "Startsailor_4a":
			dialog.text = "Takie chodzą plotki. Bądź wdzięczny, że raczyłem się podzielić i wyrazić troskę o twój pobyt tutaj. W przeciwnym razie, ta delikatna gascjońska róża mogłaby zwiędnąć pod naszym palącym słońcem. Bez względu na to, czy to bzdury, czy nie, miej się na baczności - mamy tu wystarczająco kłopotów bez fanatyków. Bandyci w zaułkach i dżungli, piraci na morzu i czerwono-skórzy kanibale...";
			link.l1 = "Teraz, teraz! Dam sobie radę. Może być teraz dla mnie trochę gorąco, ale w domu jestem zahartowany słońcem, w przeciwieństwie do tych Normanów, powiedzmy. A jeśli coś można rozwiązać mieczem, możesz na mnie liczyć. Ale komary - to jest czysta męka! Cóż, wszystkie moje rzeczy są policzone. Łódź jest gotowa, mówisz?";
			link.l1.go = "Startsailor_5a";			
		break;
		
		case "Startsailor_5a":
			dialog.text = "Oczekując niecierpliwie. Mam nadzieję, że dasz sobie radę, monsieur? Głowa do góry, i miejmy nadzieję, że nie zgubisz się stąd. Och, i witaj na Archipelagu, heh-heh.";
			link.l1 = "Tak, dzięki. Jedyną pociechą jest to, że nie będę tu długo.";
			link.l1.go = "Startsailor_6";			
		break;
		
		case "Startsailor_6":
			DialogExit();
			AddDialogExitQuestFunction("SharlieTutorial_StartGameInMartinique");
		break;
		// <-- матрос на корабле, прибытие в Сен-Пьер
		
		// горожанин знает Мишеля
		case "Benuatalker":
			DelLandQuestMark(npchar);
			link.l1 = "Przepraszam, "+GetAddress_FormToNPC(NPChar)+", mógłbyś mi powiedzieć, gdzie mogę znaleźć Michela de Monpera? Musi być gdzieś w twoim mieście.";
            link.l1.go = "Benuatalker_1";
		break;
		
		case "Benuatalker_1":
			dialog.text = "Hmm... Widzę, że przybyłeś tu niedawno, skoro bez obaw zadajesz takie pytania... Radzę przestać, bo inaczej wpakujesz się w kłopoty. A co do twojego pytania... Porozmawiaj z opatem. Znajdziesz go w kościele.";
			link.l1 = "Dziękuję!";
            link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddDialogExitQuest("Sharlie_SetBenua");
			QuestPointerToLoc("FortFrance_town", "reload", "reload7_back");
		break;
		
		// --> арест в резиденции
		case "Sharlie_arest":
			dialog.text = "Stój! Oddaj broń natychmiast, monsieur, i chodź z nami!";
			link.l1 = "Co to, do diabła, jest?";
			link.l1.go = "Sharlie_arest_1";
			if (CheckCharacterItem(PChar, "knife_03")) pchar.Sharlie.KnifeMonpe = true;
		break;
		
		case "Sharlie_arest_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoFunctionReloadToLocation("FortFrance_prison", "goto", "goto9", "Puancie_InJail");
			WaitDate("", 0, 0, 2, 0, 10); //крутим время
			RecalculateJumpTable();
			RemoveAllCharacterItems(PChar, true);
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "Puancie_Jail"; 
			LAi_SetActorTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "FortFrance_prison", "goto", "goto13");
		break;
		// арест в резиденции
		
		// --> офицер базы
		case "Maltie_officer":
			ref location = &Locations[FindLocation(pchar.location)];
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "begin")
			{
				dialog.text = "Miło cię widzieć, Monsieur de Maure. Jaka to okazja?";
				link.l1 = TimeGreeting()+" , oficerze. Chciałbym porozmawiać z moim bratem, Michelem de Monper. Oczywiście nieoficjalnie. Próbuję dowiedzieć się o jego służbie tutaj na Karaibach.";
				link.l1.go = "spanish";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "think")
			{
				dialog.text = "Jak poszło przesłuchanie? Czy znalazłeś coś wartościowego?";
				link.l1 = "O, tak. Tak bardzo, że zabieram tego Hiszpana ze sobą na mój statek. Jest ważnym świadkiem i musi zostać dostarczony do St. Christopher na dalsze przesłuchanie.";
				link.l1.go = "spanish_10";
				break;
			}
			if (!CheckAttribute(location, "first_meeting"))
			{
				dialog.text = "Jakie interesy sprowadzają cię tutaj, monsieur?";
				link.l1 = "Przybyłem zobaczyć mojego brata, Michela de Monper.";
				link.l1.go = "Maltie_officer_1";
				location.first_meeting = true;
			}
			else
			{
				dialog.text = "Panie, muszę delikatnie przypomnieć, że znajdujesz się na terenie wojskowego kantonu. Zachowuj się odpowiednio.";
				link.l1 = "Tak, sir. Oczywiście.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Maltie_officer";
			}
			
			if (SandBoxMode)
			{
				dialog.text = "Panie, muszę delikatnie przypomnieć, że znajdujesz się w wojskowym obozie. Zachowuj się odpowiednio.";
				link.l1 = "Tak, sir. Oczywiście.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Maltie_officer";
			}
		break;
		
		case "Maltie_officer_1":
			DelLandQuestMark(npchar);
			dialog.text = "Michel de Monper jest obecnie pod strażą w jednej z naszych kazamat, trzymany na osobisty rozkaz Kawalera Philippe de Poincy. Zejdź na dół na niższy poziom. Znajdziesz tam kazamaty, które używamy do przechowywania i jako cele. Myślę, że dasz sobie radę.";
			link.l1 = "Dziękuję!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Maltie_officer";
			QuestPointerToLoc("FortFrance_Dungeon", "quest", "quest1");
		break;
		// офицер базы
		
		// --> солдаты базы
		case "Maltie_soldier":
			dialog.text = "Witaj, monsieur. Czy mogę w czymś pomóc?";
			link.l1 = "Dziękuję, żołnierzu, ale nie, wszystko w porządku. Kontynuuj.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Maltie_soldier";
		break;
		// --> солдаты базы
		
		// --> мальтиец-проводник
		case "Sharlie_maltie":
			dialog.text = "Dziękuję za czekanie, monsieur. Szukasz więc Michela de Monper? Jesteś jego bratem?";
			link.l1 = "Tak, to prawda. Jestem jego bratem, Charlesem. Muszę go natychmiast zobaczyć. Czy Michel ma kłopoty?";
			link.l1.go = "Sharlie_maltie_1";			
		break;
		
		case "Sharlie_maltie_1":
			dialog.text = "Niestety tak jest, monsieur. Michel jest zamknięty w jednym z kazamatów poniżej. Chevalier de Poincy, gubernator generalny francuskich kolonii w Nowym Świecie, osobiście podpisał rozkaz jego aresztowania. Wszyscy byliśmy w szoku. Twój brat to wzór męskiej cnoty, dyscypliny i odwagi, duma naszego Zakonu! Najgorsze jest to, że my, jego przyjaciele, musimy go zamknąć za kratami i pilnować jak pospolitego przestępcę! Robimy wszystko, co w naszej mocy, by uczynić jego pobyt wygodnym, ale... więzienie to wciąż więzienie.";
			link.l1 = "O co jest oskarżony? Czy popełnił zbrodnię?";
			link.l1.go = "Sharlie_maltie_1_1";			
		break;
		
		case "Sharlie_maltie_1_1":
			dialog.text = "Biuro Generalnego Gubernatora oskarżyło Michela o defraudację! Jakże to niedorzeczne! Wszyscy tutaj jesteśmy przekonani, że to motywowane politycznie. Powiem ci coś w zaufaniu. Michel brał udział w pewnych tajnych działaniach w imieniu Zakonu. Być może dowiedział się więcej, niż powinien. Albo, co gorsza, rozgniewał jakichś potężnych ludzi. Ale kradzież pieniędzy? Nikt w to nie wierzy. To pretekst, nie prawdziwy powód, tchórzliwy i niegodny pretekst! Ale dość słów. Twój brat nie może się doczekać spotkania z tobą, jestem pewien, że sam ci wszystko opowie.";
			link.l1 = "Dobrze. Gdzie znajduje się wasze więzienie?";
			link.l1.go = "Sharlie_maltie_1_2";
		break;
		
		case "Sharlie_maltie_1_2":
			dialog.text = "W naszej podziemnej zbrojowni, tutaj w mieście. Chodź za mną. Pokażę ci drogę.";
			link.l1 = "...";
			link.l1.go = "Sharlie_maltie_2";
		break;
		
		case "Sharlie_maltie_2":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "FortFrance_town", "officers", "reload7_1", "Maltie_GoTown", -1);
		break;
		
		case "Sharlie_maltie_3":
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId("Maltie_officer"), "questmarkmain");
			dialog.text = "Jesteśmy na miejscu. To nasza baza operacyjna - Karaibski Oddział Wojskowego Zakonu Szpitalników Świętego Jana Jerozolimskiego, z Rodos i z Malty. Kazamaty znajdują się poniżej nas. Idź korytarzem obok jadalni i kaplicy. Schody tam zaprowadzą cię na niższy poziom. Szukaj korytarza z celami. Znajdziesz swojego brata w jednej z nich, blisko tyłu.\nIdź, Charles, i niech Bóg będzie z tobą. Proszę, pomóż Michelowi! On jest niewinny, wszyscy tutaj są gotowi przysiąc na to.";
			link.l1 = "Cały powód, dla którego przybyłem do tej dziury, to zobaczyć mojego brata. Mam nadzieję, że przynajmniej uda mi się wyciągnąć go z tej kabały.";
			link.l1.go = "Sharlie_maltie_4";
		break;
		
		case "Sharlie_maltie_4":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.lifeday = 0;
			LAi_ActorGoToLocator(npchar, "goto", "goto1", "none", -1);
		break;
		
		//belamour cle -->
		case "Sharlie_maltieA":
			dialog.text = "Więc szukałeś Michela de Monpera? I jesteś jego bratem?";
			link.l1 = "Tak, to prawda. Jestem jego bratem, Charlesem. Muszę go zobaczyć natychmiast. Wpadł w kłopoty, prawda?";
			link.l1.go = "Sharlie_maltie_1a";			
		break;
		
		case "Sharlie_maltie_1a":
			dialog.text = "Niestety, ma, Monsieur. Michel jest aresztowany i zamknięty w naszej więzieniu. Sam Kawaler de Poincy, generalny gubernator francuskich kolonii, wydał i podpisał rozkazy. Wszyscy byliśmy w szoku.\nTwój brat jest przykładem męskości, stanowczości i odwagi, dumą naszego Zakonu! Najgorsze jest to, że my, jego przyjaciele, musimy zamknąć jego celę i strzec go jak przestępcę! Robimy wszystko, by złagodzić jego stan, ale... więzienie to więzienie.";
			link.l1 = "Więc o co jest oskarżany? Czy popełnił zbrodnię?";
			link.l1.go = "Sharlie_maltie_1_1a";			
		break;
		
		case "Sharlie_maltie_1_1a":
			dialog.text = "Absurd! Czysty absurd! Oskarżyli Michela o defraudację i kradzież państwowych pieniędzy. Nonsens! Wszyscy jesteśmy pewni, że to tylko polityczna gra. Michel brał udział w tajnych operacjach Zakonu, być może dowiedział się więcej, niż powinien.\nAlbo coś innego. Ale kradzież pieniędzy! Nikt w to nie wierzy. To tylko pretekst, a nie powód, taki gruby i głupi pretekst! Ale dość słów. Twój brat nie może się doczekać spotkania z tobą, jestem pewien, że sam ci wszystko opowie.";
			link.l1 = "Dobrze. Gdzie znajduje się więzienie?";
			link.l1.go = "Sharlie_maltie_1_2a";
		break;
		
		case "Sharlie_maltie_1_2a":
			dialog.text = "Znajduje się w naszej podziemnej bazie, tutaj w mieście. Chodź za mną. Pokażę ci drogę.";
			link.l1 = "...";
			link.l1.go = "Sharlie_maltie_2a";
		break;
		
		case "Sharlie_maltie_2a":
			DialogExit();
			//LAi_ActorGoToLocation(npchar, "reload", "reloadPr1", "FortFrance_Dungeon", "reload", "reload1", "", -1);
			Pchar.quest.Sharlie_Maltie.win_condition.l1 = "location";
			Pchar.quest.Sharlie_Maltie.win_condition.l1.location = "FortFrance_town";
			Pchar.quest.Sharlie_Maltie.win_condition = "Maltie_GoBasement";
			QuestPointerDelLoc("FortFrance_prison", "reload", "reload1");
		break;
		//<-- cle
		// мальтиец-проводник
		
		// --> найм матросов
		case "Sharlie_sailor":
			DelLandQuestMark(npchar);
			dialog.text = "A potem wychylił się za burtę... i wylał tyle, że samo Morze Karaibskie zzieleniało! Ha, ha, ha!";
			link.l1 = "Alonso?";
			link.l1.go = "Sharlie_sailor_1";
		break;
		
		case "Sharlie_sailor_1":
			dialog.text = "O! Charles, właśnie opowiadam chłopakom o naszych przygodach!";
			link.l1 = "Zauważyłem. Słuchaj, Alonso. Zostałem kapitanem...";
			link.l1.go = "Sharlie_sailor_2";
		break;
		
		case "Sharlie_sailor_2":
			dialog.text = "Już? Myślałem, że zajmie to co najmniej miesiąc, ha, ha!";
			link.l1 = "Mówię poważnie!";
			link.l1.go = "Sharlie_sailor_3";
		break;
		
		case "Sharlie_sailor_3":
			dialog.text = "Gdyby chodziło tylko o mnie, dołączyłbym od razu. Ale mam ze sobą czterdziestu ludzi z Ulysse. Powierzyli mi swoją przyszłość, muszę być pewien, że ich nie zawiedziesz\n"+
			"Jaki macie statek?";
			link.l1 = "Statek jak każdy inny, "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(RealShips[sti(pchar.ship.type)].basetype), "Name")))+". To aż tak istotne?";
			link.l1.go = "Sharlie_sailor_4";
		break;
		
		case "Sharlie_sailor_4":
			dialog.text = "Wie pan, po Ulysse nie chcielibyśmy służyć na byle barkasie czy tartanie. Twój statek już widzieliśmy i chłopakom się podoba\n"+
			"Teraz kwestia pieniędzy. Bierzemy 4800 peso zaliczki. Potem – jak wszędzie, podział łupów. Nie prosimy o więcej, proszę się nie martwić. Dasz radę?";
			if (sti(Pchar.money) >= 4800)
			{
				link.l1 = "Zgoda! Oto wasze monety.";
				link.l1.go = "Sharlie_sailor_5";
			}
			link.l2 = "Na nieszczęście, nie mam przy sobie teraz takiej sumy pieniędzy.";
			link.l2.go = "Sharlie_sailor_nomoney";
		break;
		
		case "Sharlie_sailor_5":
			if (GetSquadronGoods(pchar, GOOD_FOOD) < 20 || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < 30)
			{
				dialog.text = "Czy masz prowiant w ładowni, kapitanie? A lekarstwa? Nie? Cóż, to niedobrze. Idź po niezbędne zapasy na naszą podróż, a potem wróć i porozmawiamy. Idź do sklepu i zdobądź, czego potrzebujesz.";
				link.l1 = "Hm. Masz rację. Dobrze, zrobię to.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Sharlie_sailor_again";
			}
			else
			{
				AddMoneyToCharacter(pchar, -4800);
				dialog.text = "No proszę! Gratulacje... kapitanie! Zaraz zbieram chłopaków i idziemy na wasz statek.";
				link.l1 = "Cieszę się, że kontynuujemy przygodę, Alonso. Szykuj statek do wyjścia w morze!";
				link.l1.go = "Sharlie_sailor_6";
			}
		break;
		
		case "Sharlie_sailor_6":
			DialogExit();
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, "Fortfrance_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
			SetCrewQuantityOverMax(PChar, 40);
			pchar.Ship.Crew.Morale = 50;
			pchar.Ship.Crew.Exp.Sailors = 50;
			pchar.Ship.Crew.Exp.Cannoners = 50;
			pchar.Ship.Crew.Exp.Soldiers = 50;
			AddQuestRecord("Sharlie", "7");
			pchar.questTemp.Sharlie = "skiper";
			DeleteAttribute(pchar, "GenQuest.CannotWait");//снимаем запрет, если не был снят раньше
			AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
		break;
		
		case "Sharlie_sailor_nomoney":
			dialog.text = "Cóż, jak tylko znajdziesz wystarczająco pieniędzy, wracaj. Znajdziesz nas tutaj w tawernie. I tak nie ma innych statków w pobliżu. Będziemy po prostu dalej pić i trwonić nasze pieniądze na dziwki, harhar!";
			link.l1 = "Postaram się wrócić tak szybko, jak to możliwe.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Sharlie_sailor_again";
		break;
		
		case "Sharlie_sailor_again":
			dialog.text = "Wracasz, kapitanie? Gotów nająć mnie i moich kamratów? Nasze sakiewki zaczynają być lekkie, trzeba znów poczuć morską bryzę na twarzach!";
			if (sti(Pchar.money) < 4800)
			{
				link.l1 = "Jeszcze nie, wciąż wszystko przygotowuję.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Sharlie_sailor_again";
			}
			else
			{
				link.l1 = "Tak. Weź swoją zaliczkę. Teraz jesteś na mojej służbie.";
				link.l1.go = "Sharlie_sailor_5";
			}
		break;
		// найм матросов
		
		// наводчик на штурмана
		case "skipertalker":
			DelLandQuestMark(npchar);
			dialog.text = LinkRandPhrase("Ahoy kapitanie! Czego potrzebujesz?","Witaj, monsieur. Co mogę dla ciebie zrobić?","Dzień dobry. Czego chcesz?");
			link.l1 = RandPhraseSimple("Mam do ciebie pytanie.","Potrzebuję informacji o tej kolonii.");
			link.l1.go = "skipertalker_1";
			link.l2 = "Po prostu mówię cześć. Au revoir!";
			link.l2.go = "exit";
			NextDiag.TempNode = "skipertalker";
		break;
		
		case "skipertalker_1":
			dialog.text = RandPhraseSimple("Cóż to jest?","Czego potrzebujesz?");
			link.l1 = "Słuchaj, "+GetAddress_FormToNPC(NPChar)+" , jest taka sprawa... Szukam nawigatora. Może znasz kogoś, kto nadaje się do tej pracy tutaj w mieście?";
			link.l1.go = "skipertalker_2";
		break;
		
		case "skipertalker_2":
			dialog.text = "Nawigator? Hm. Cóż, znam jednego... Jest tylko jeden problem - siedzi w więzieniu, więzieniu dla dłużników. Biedny drab został zamknięty w kazamatach od prawie miesiąca, dopóki on lub ktoś inny nie spłaci jego długu.";
			link.l1 = "Dłużnik? Hm... Jak się nazywa?";
			link.l1.go = "skipertalker_3";
		break;
		
		case "skipertalker_3":
			dialog.text = "Jego imię to Folke Deluc. Zapytaj komendanta więzienia, jeśli chcesz go zobaczyć. Ale nie sądzę, że pozwolą mu stamtąd wyjść, chyba że spłacisz jego dług, bo on na pewno tego nie zrobi, hahaha!";
			link.l1 = "Może i zrobię to. Dzięki za informacje, przyjacielu.";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			pchar.questTemp.Sharlie = "jailskiper";
			AddQuestRecord("Sharlie", "8");
			LocatorReloadEnterDisable("Fortfrance_town", "reload_jail", false);
			SetFunctionLocationCondition("FortfranceJailOff_AddQuestMark", "fortfrance_prison", false);
		break;
		
		// --> штурман
		case "Folke":
			dialog.text = "Jakiejże to zaszczytu ja dostąpiłem, monsieur?";
			link.l1 = "Cześć, Folke. To proste, mam statek, ale nie mam nawigatora. A potrzebuję go. Więc wykupiłem twój dług...";
			link.l1.go = "Folke_1";
		break;
		
		case "Folke_1":
			dialog.text = "Chcesz powiedzieć, że wyciągnąłeś mnie stąd, żeby wziąć mnie do swojej załogi?";
			link.l1 = "Dokładnie. Myślę, że szybko nadrobisz pieniądze, które na ciebie wydałem. No cóż... zobaczymy, jak to pójdzie.";
			link.l1.go = "Folke_2";
		break;
		
		case "Folke_2":
			dialog.text = "Moja wdzięczność, Monsieur. Już mi niedobrze od tej zgniłej, wilgotnej celi. Z wielką przyjemnością wróciłbym na pokład raz jeszcze. Ach, morze...";
			link.l1 = "Cieszę się, że doszliśmy do porozumienia, Folke. Jeszcze jedno, czy masz jakieś inne umiejętności oprócz sterowania statkiem?";
			link.l1.go = "Folke_3";
		break;
		
		case "Folke_3":
			dialog.text = "Trochę wszystkiego, kapitanie. Służyłem kiedyś na kaprze dla Holenderskiej Kompanii Zachodnioindyjskiej. Tam nauczyłem się obsługiwać działa, więc mogę służyć jako oficer artylerii, jeśli mnie potrzebujesz. Handel i abordaż to moje najsłabsze strony.";
			link.l1 = "Dziękuję za podzielenie się, teraz podążaj za mną na statek. Chcę, abyś obserwował załogę swoim doświadczonym okiem, gdy przygotowują wszystko do wypłynięcia. Potem chcę jak najszybciej udać się na Gwadelupę.";
			link.l1.go = "Folke_4";
		break;
		
		case "Folke_4":
			dialog.text = "Tak jest, kapitanie! Poczekam na ciebie w twojej kajucie. *Użyj menu akcji podczas żeglugi, aby uzyskać dostęp do kajuty i innych obszarów statku*";
			link.l1 = "Dziękuję, Folke. Do zobaczenia na pokładzie.";
			link.l1.go = "Folke_5";
			Log_Info("You have received amulet 'Merchant's Rosary'");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "obereg_8");
			if(CheckAttribute(pchar,"systeminfo.tutorial.Amulet"))
			{
				DoQuestFunctionDelay("Tutorial_Amulet", 0.1);
			}
		break;
		
		case "Folke_5":
			DialogExit();
			EndQuestMovie();
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			AddQuestRecord("Sharlie", "10");
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.Sharlie_skiper.win_condition.l1 = "location";
			pchar.quest.Sharlie_skiper.win_condition.l1.location = "My_Cabin_Small";
			pchar.quest.Sharlie_skiper.function = "Sharlie_SkiperTalk";
			//прерывание на засаду пиратов - принудительный квест
			pchar.quest.Sharlie_seabattle.win_condition.l1 = "location";
			pchar.quest.Sharlie_seabattle.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Sharlie_seabattle.function = "SharlieSeabattle_agent";
			
			pchar.quest.NewGameTip2.win_condition.l1 = "location";
			pchar.quest.NewGameTip2.win_condition.l1.location = "Martinique";
			pchar.quest.NewGameTip2.function = "ShowNewGameTip";
			pchar.quest.NewGameTip2.text = "Your first officer is waiting for you. Use the action menu (ENTER) to go to the cabin.";
		break;
		
		case "Folke_6":
			pchar.GenQuest.StoreGoods.StoreIdx = Fortfrance_STORE;
			pchar.GenQuest.StoreGoods.Starting = true; // заполняем магазин 250912
			dialog.text = "Piękna lugger, kapitanie! Całkiem przyzwoity mały statek z doskonałym takielunkiem i solidnym drewnem. Z takim statkiem nie tylko bezpiecznie dotrzemy na Gwadelupę, ale nawet przemierzymy całe Karaiby, jeśli zechcemy.";
			link.l1 = "Wyśmienicie. Przynajmniej nie wyrzuciłem pieniędzy na dziurawą łajbę... Masz jakieś rady, zanim wyruszymy, Folke?";
			link.l1.go = "Folke_8";
		break;
		
		case "Folke_7":
			dialog.text = "Do diabła, ten slup cieknie jak sito, kapitanie. Będzie blisko, żebyśmy przeprawili się na Gwadelupę. Jeśli chcesz dotrzeć do Basse-Terre w jednym kawałku, trzeba go natychmiast oddać do naprawy w stoczni.";
			link.l1 = "Nie miałem wyboru, to był jedyny statek na sprzedaż! I kazali mi za nią słono zapłacić. Jak wiesz, nie mamy teraz czasu, by ją naprawić... Masz jakieś rady, zanim wyruszymy w morze?";
			link.l1.go = "Folke_8";
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_BALLS) >= 80) && (GetSquadronGoods(pchar, GOOD_GRAPES) >= 80) && (GetSquadronGoods(pchar, GOOD_KNIPPELS) >= 80) && (GetSquadronGoods(pchar, GOOD_BOMBS) >= 80) && (GetSquadronGoods(pchar, GOOD_POWDER) >= 180);
		case "Folke_8":
			if (bOk)
			{
				dialog.text = "Mamy wystarczająco dużo prochu i kul, kapitanie. Na razie wystarczy; pamiętaj tylko, by uzupełniać zapasy na czas.";
				link.l1 = "Cóż, to się rozumie samo przez się. Jakieś inne uwagi?";
				link.l1.go = "Folke_10";
				if (CheckCharacterItem(PChar, "BoxOfBalls"))
				{
					link.l2 = "O! Dzięki za przypomnienie. Mam akurat całą skrzynię kul przy sobie!";
					link.l2.go = "Folke_8_1";
				}
			}
			else
			{
				dialog.text = "Nie mamy wystarczająco amunicji w magazynie, kapitanie. Musimy mieć co najmniej sto kul armatnich, kartaczy i bomb, a także sto worków z grapeshotem i dwieście beczek prochu strzelniczego. Kup niezbędny materiał, kapitanie. To nie będzie kosztować dużo, ale uratuje nasze życie, jeśli zostaniemy zaatakowani przez piratów lub Hiszpanów.";
				link.l1 = "Godna inwestycja. Wyruszam do kupca.";
				link.l1.go = "Folke_9";
			}
		break;
		
		case "Folke_8_1":
			dialog.text = "...I jak długo pan to ze sobą nosi?";
			link.l1 = "Prawie dwa tygodnie.";
			link.l1.go = "Folke_8_2";
			TakeItemFromCharacter(pchar, "BoxOfBalls");
			//AddCharacterGoodsSimple(sld, GOOD_BALLS, 10);
		break;
		
		case "Folke_8_2":
			dialog.text = "Ale po co, kapitanie?!";
			link.l1 = "Lubię zbierać różne rzeczy. Nigdy nie wiadomo, co się przyda.";
			link.l1.go = "Folke_8_3";
		break;
		
		case "Folke_8_3":
			dialog.text = "Cóż, pech. Te kule nigdy nie wejdą do naszych działek. Nigdy nie widziałem takich dużych kul. Jedna taka posłałaby Adeline na dno.";
			link.l1 = "...";
			link.l1.go = "Folke_10";
		break;
		
		case "Folke_9":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_1";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "12");
		break;
		
		case "Folke_goods_1":
			dialog.text = "Czy skończyłeś kupować amunicję, kapitanie?";
			if (bOk)
			{
				link.l1 = "Tak, mam. Jakieś inne uwagi?";
				link.l1.go = "Folke_10";
			}
			else
			{
				link.l1 = "Nie teraz, wciąż nad tym pracuję.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_1";
			}
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_WEAPON) >= 50);
		case "Folke_10":
			if (bOk)
			{
				dialog.text = "Dobra robota, kupiłeś wystarczająco dużo broni dla swojej załogi. Jeśli nie będziemy mieli wystarczająco dużo broni, stracimy znacznie więcej ludzi podczas abordażu. Niech Bóg nas przed tym chroni. Nie zapomnij często sprawdzać ilości w ładowni\nRozsądnie jest mieć nieco więcej broni, niż potrzebujemy. Te przeklęte szczury lubią obgryzać drewniane rękojeści i kolby.";
				link.l1 = "Zrozumiano. Widzę, że jest jeszcze coś, co chcesz dodać?";
				link.l1.go = "Folke_11";
			}
			else
			{
				dialog.text = "Nie mamy wystarczającej ilości broni na pokładzie dla załogi. Jeśli nie będziemy mieli wystarczającej ilości broni, stracimy znacznie więcej ludzi podczas abordażu. Niech Bóg nas przed tym uchroni. O ile rozumiem, masz czterdziestu ludzi w załodze\nKup wystarczająco dużo broni dla każdego, a nawet kup kilka dodatkowych, pięćdziesiąt zestawów powinno wystarczyć. Rozsądnie jest mieć kilka więcej sztuk broni, niż będziemy potrzebować. Przeklęte szczury lubią gryźć drewniane uchwyty i kolby.";
				link.l1 = "Tak właśnie zrobię. Wkrótce wrócę.";
				link.l1.go = "Folke_10_1";
			}
		break;
		
		case "Folke_10_1":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_2";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "13");
		break;
		
		case "Folke_goods_2":
			dialog.text = "Czy skończyłeś kupować broń, kapitanie?";
			if (bOk)
			{
				link.l1 = "Broń jest w ładowni. Widzę, że chcesz coś jeszcze dodać?";
				link.l1.go = "Folke_11";
			}
			else
			{
				link.l1 = "Nie teraz, wciąż nad tym pracuję.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_2";
			}
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_FOOD) >= 100) && (GetSquadronGoods(pchar, GOOD_RUM) >= 10);
		case "Folke_11":
			if (bOk)
			{
				dialog.text = "Nie, myślę, że to wszystko. Mamy wystarczająco jedzenia, zadbałeś też o rum dla załogi. To mądre, ponieważ nie ma lepszego lekarstwa na wszelkie dolegliwości niż przyjemny, chłodny kieliszek rumu po twojej zmianie. Marynarze kochają i szanują kapitanów, którzy dają im ich codzienną rację rumu. Nigdy nie chcesz usłyszeć, jak twoi ludzie pytają: 'Dlaczego rum się skończył?'";
				link.l1 = "Czy możemy już wyruszyć w morze?";
				link.l1.go = "Folke_12";
			}
			else
			{
				dialog.text = "Tak. Jedzenie i rum. To katastrofa, gdy na pokładzie brakuje wystarczającej ilości jedzenia. Zawsze miej więcej prowiantu, niż myślisz, że potrzebujesz. Nigdy nie wiadomo, jak długo potrwa podróż - martwa cisza lub silna wichura mogą zniszczyć każdy plan. Ludzie się zbuntują lub umrą z głodu, gdy skończą się zapasy\nZapas rumu nie jest tak krytyczny, ale gorąco polecam zawsze mieć trochę na pokładzie, nie ma lepszego lekarstwa na wszelkie dolegliwości niż ładny chłodny kieliszek rumu po swojej wachcie. Marynarze kochają i szanują kapitanów, którzy dają im codzienną rację rumu\nWięc idź i kup zapasy, których potrzebujemy - przynajmniej sto skrzyń jedzenia i dziesięć beczek rumu. Nigdy nie chcesz słyszeć, jak twoi ludzie pytają: 'Dlaczego rum się skończył?'";
				link.l1 = "Chyba masz rację. Pójdę jeszcze raz do kupca.";
				link.l1.go = "Folke_11_1";
			}
		break;
		
		case "Folke_11_1":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_3";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "14");
		break;
		
		case "Folke_goods_3":
			dialog.text = "Czy skończyłeś kupować nasze jedzenie i rum, kapitanie?";
			if (bOk)
			{
				link.l1 = "Tak. Czy możemy teraz wyruszyć w morze?";
				link.l1.go = "Folke_12";
			}
			else
			{
				link.l1 = "Nie, wciąż nad tym pracuję.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_3";
			}
		break;
		
		case "Folke_12":
			dialog.text = "Owszem, kapitanie. Możemy podnieść kotwicę i ruszyć na północ w kierunku Gwadelupy, tak jak chciałeś.";
			// belamour legendary edition -->
			link.l1 = "Świetna robota, Folke. Nie dałbym sobie rady bez ciebie.";
			link.l1.go = "Folke_13";
			link.l2 = "Dobrze, zabierajmy się do roboty, zobaczmy, czy jesteś wart tych pieniędzy.";
			link.l2.go = "Folke_13a";
		break;
		
		case "Folke_13a":
			Npchar.loyality = makeint(Npchar.loyality) - 5;
			ChangeCharacterComplexReputation(pchar,"authority", 5);
			dialog.text = "W takim razie ustaw mnie jako nawigatora, a ja pójdę na swoje miejsce na pokładzie.";
			link.l1 = "... ";
			link.l1.go = "Folke_14";
		break;
		
		case "Folke_13":
			Npchar.loyality = makeint(Npchar.loyality) + 5;
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			// <-- legendary edition
			dialog.text = "Zatem wyznacz mnie na nawigatora, a pójdę na swoje miejsce na pokładzie.";
			link.l1 = "...";
			link.l1.go = "Folke_14";
		break;
		
		case "Folke_14":
			DialogExit();
			LAi_SetStayType(npchar);
			LAi_SetImmortal(npchar, false);
			AddQuestRecord("Sharlie", "15");
			pchar.questTemp.Sharlie = "seabattle";//в Ле Франсуа
			DeleteAttribute(pchar, "NoNavyPenalty"); // штрафуем за нехватку навигации
			
			npchar.quest.OfficerPrice = 20;
			npchar.loyality = 30;
			
			// --> копипаста LandEnc_OfficerHired
			AddPassenger(pchar, npchar, false);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			// <--
			
			pchar.questTemp.HelenDrinking.TakeFolke = true;
			
			DoQuestFunctionDelay("Tutorial_Navigator2", 1.0);
			//DoQuestFunctionDelay("Ngt_FolkeEng", 3.0);
			//NewGameTip("Welcome aboard your new officer! Press F4 to assign him as your Navigator.");
			pchar.questTemp.Sharlie.FolkeWait = true;
			LocatorReloadEnterDisable("My_Cabin_Small", "reload1", true);
			NextDiag.CurrentNode = "Folke_wait";
		break;
		
		case "Folke_wait":
			dialog.text = "Gotów do odcumowania, kapitanie!";
			link.l1 = "...";
			
			if (!CheckAttribute(npchar, "navigator")) {
				dialog.text = "Kapitanie, ustaw mnie jako nawigatora, inaczej szybko wpadniemy na mieliznę.";
				link.l1 = "Jasne, zrobię to teraz.";
			}
			
			link.l1.go = "exit";
			NextDiag.TempNode = "Folke_wait";
		break;
	
		// штурман

	// --> пират-обманщик
		case "Seabattle_pirate":
			dialog.text = "Moje przeprosiny. "+GetFullName(pchar)+"?";
			link.l1 = "Zgadza się. Czym zawdzięczam tę okazję, panie?";
			link.l1.go = "Seabattle_pirate_1";
		break;
		
		case "Seabattle_pirate_1":
			dialog.text = "Pozwól, że się przedstawię - "+GetFullName(npchar)+" . Przysłał mnie tu Cesar Craig. Musisz go znać. Jest właścicielem tawerny w Le Francois. Jak on twierdzi, zamierzasz wypłynąć na Gwadelupę. Chciałby zaoferować ci łatwe pieniądze.";
			link.l1 = "Hm... Interesujące! A jak to się stało, że Cesar Craig jest tak dobrze poinformowany?";
			link.l1.go = "Seabattle_pirate_2";
		break;
		
		case "Seabattle_pirate_2":
			dialog.text = "To proste, kapitanie. Twój statek jest jedynym statkiem w St. Pierre w tej chwili, każdy z dwoma uszami i okiem wie wszystko o tym, kim jesteś i dokąd zmierzasz. Tutaj, w koloniach, plotki latają szybciej niż mewy. Czy jesteś zainteresowany wysłuchaniem naszej oferty?";
			link.l1 = "Oczywiście. Nigdy nie sprzeciwiam się zarobieniu trochę pieniędzy.";
			link.l1.go = "Seabattle_pirate_3";
		break;
		
		case "Seabattle_pirate_3":
			dialog.text = "Teraz rozmawiamy, kamracie! Widzę, że masz wyczulony nos do interesów. Oto umowa. Cesar pilnie potrzebuje dostarczenia partii wina na Gwadelupę. Dwieście beczek, twój statek łatwo to pomieści. Zapłata wynosi dziesięć tysięcy peso za łatwą robotę - Cesar się spieszy, a twój statek jest jedynym w porcie w tej chwili. Musisz się zgodzić, takie opłacalne propozycje są rzadkie.";
			link.l1 = "Cholera, dziesięć tysięcy pesos? Cóż, mamy umowę!";
			link.l1.go = "Seabattle_pirate_4";
		break;
		
		case "Seabattle_pirate_4":
			dialog.text = "Udaj się do Le Francois i porozmawiaj z Cesarem. On zajmie się wszystkim. Ty tylko musisz zakotwiczyć w zatoce tuż przed Le Francois. Nie zawiedź mnie, kamracie, Cesar obiecał mi tysiąc pesos, jeśli cię przekonam...";
			link.l1 = "Nie martw się, uznaj mnie za przekonanego. Jak tylko będę gotowy do wyjazdu, popłynę prosto do Le Francois.";
			link.l1.go = "Seabattle_pirate_5";
		break;
		
		case "Seabattle_pirate_5":
			dialog.text = "Hurra! Ruszam po moje tysiąc. Dzięki, kumplu!";
			link.l1 = "Proszę bardzo...";
			link.l1.go = "Seabattle_pirate_6";
		break;
		
		case "Seabattle_pirate_6":
			DialogExit();
			AddLandQuestMark(characterFromId("LeFransua_tavernkeeper"), "questmarkmain");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "", "", "", "", -1);
			AddQuestRecord("Sharlie", "11");
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.location = "None";
		break;
	// пират-обманщик

	// офицер Гриффондора
		case "griffondor_officer":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "exit";
		break;

	// командир абордажной роты по защите Сен-Пьера
		case "rosetti":
			PlaySound("Voice\English\EvilPirates01.wav");
			dialog.text = "Kapitanie, grupa abordażowa jest sformowana i gotowa! Czekamy na twoje rozkazy!";
			link.l1 = "";
			link.l1.go = "rosetti_1";
		break;
		
		case "rosetti_1":
			DialogExit();
			bDisableCharacterMenu = true;//лоченые интерфейсы
			ChangeShowIntarface();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("DefendSP_soldier_0"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Blaze");
			sld.dialog.filename = "MainHero_dialog.c";
			sld.dialog.currentnode = "SP_defend";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rosetti_2":
			PlaySound("interface\abordage_wining.wav");
			dialog.text = "O tak, kapitanie! Gotowi chłopcy, za kapitanem! Hut, raz-dwa-trzy!";
			link.l1 = " ";
			link.l1.go = "rosetti_3";
		break;
		
		case "rosetti_3":
			DialogExit();
			PlaySound("interface\abordage_wining.wav");
			bDisableCharacterMenu = false;//лоченые интерфейсы
			ChangeShowIntarface();
			for (i=0; i<=12; i++)
			{
				sld = CharacterFromID("DefendSP_soldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			// прерывание на джунгли перед выходом из города
			pchar.quest.DefendSP_jungle1.win_condition.l1 = "location";
			pchar.quest.DefendSP_jungle1.win_condition.l1.location = "Martinique_jungle_01";
			pchar.quest.DefendSP_jungle1.function = "DefendSP_SpainPatrol";
		break;
		
		case "spain_patrol":
			dialog.text = "Mierda, francuskie posiłki! Formować szeregi! Lorenzo, idź do obozu i podnieś alarm! Zdychajcie, skurwysyny!";
			link.l1 = "... ";
			link.l1.go = "spain_patrol_1";
		break;
		
		case "spain_patrol_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("DefendSP_spapatrol_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
				LAi_group_SetCheck("EnemyFight", "DefendSP_SpaPatrolDie");
				AddDialogExitQuest("MainHeroFightModeOn");
			}
			sld = CharacterFromID("DefendSP_spapatrol_5");
			LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "DefendSP_GateAlarm", -1);
		break;

	// страж истины
		case "spanish":
			dialog.text = "Czy rozumiesz, że nie jestem upoważniony do rozpowszechniania takich informacji?";
			link.l1 = "Czy rozumiesz, że tylko dzięki mojej szybkiej interwencji St. Pierre nie zostało splądrowane przez Hiszpanów? Mój brat zniknął, opuszczając Zakon! Musiał to zrobić z jakiegoś powodu. Ja, jako przedstawiciel Sir Philippe de Poincy, mam upoważnienie do prowadzenia śledztwa!";
			link.l1.go = "spanish_1";
		break;
		
		case "spanish_1":
			dialog.text = "Dobrze, dobrze, Monsieur de Maure. Odpowiem na twoje pytania. Najpierw się uspokój. Teraz pytaj śmiało.";
			link.l1 = "Co się stało przed tym, jak Michel został zamknięty pod strażą?";
			link.l1.go = "spanish_2";
		break;
		
		case "spanish_2":
			dialog.text = "Michel de Monper negocjował z jakimiś baronami pirackimi, aby zorganizować zmianę reżimu na Tortudze.";
			link.l1 = "To już wiem. Co jeszcze?";
			link.l1.go = "spanish_3";
		break;
		
		case "spanish_3":
			dialog.text = "Planował także inną operację przeciwko Hiszpanom. Mówiąc precyzyjnie - przechwycenie hiszpańskiego statku z cennym ładunkiem na pokładzie. Michel miał zwabić cel pod działa lekkiej fregaty 'Gryffondor'. Nie widzieliśmy go ani śladu przez dłuższy czas, gdy planował to przedsięwzięcie.\nAle plan się nie powiódł. Hiszpański transport nie dotarł, a Michel został znaleziony przez miejscowych rybaków wyrzucony na brzeg Zatoki Le Marin, półżywy. Wygląda na to, że operacja zakończyła się niepowodzeniem.\nWojna to wojna, i rzeczy mogą pójść źle. Cudem było, że Michel w ogóle przeżył, ale Chevalier de Poincy wpadł w furię. Oskarżył Michela o sprzeniewierzenie pieniędzy Zakonu i kazał go uwięzić. Oczywiście, nie uwierzyliśmy w te oskarżenia. Michel to uczciwy człowiek, prawdziwy rycerz Zakonu. Tylko Bóg wie, co tak rozzłościło generała-gubernatora. Może Chevalier de Poincy powie ci to sam?";
			link.l1 = "Możliwe. To wszystko, co wiesz?";
			link.l1.go = "spanish_4";
		break;
		
		case "spanish_4":
			dialog.text = "Niestety, nie ma nic więcej do powiedzenia. Szczegóły operacji twojego brata były znane tylko jemu i Chevalierowi de Poincy. Jesteśmy rycerzami Zakonu Świętego Jana z Malty. Wykonujemy nasze rozkazy.";
			link.l1 = "Jeśli Kawaler tak bardzo ufa Michelowi, musiał wcześniej pomyślnie realizować swoje sekretne plany. Czy wiesz o jakichkolwiek udanych akcjach, które Michel przeprowadził?";
			link.l1.go = "spanish_5";
		break;
		
		case "spanish_5":
			dialog.text = "Zdecydowanie. Ta ostatnia porażka Michela de Monper była również jego pierwszą porażką, dlatego byliśmy zszokowani reakcją Kawalera. Niedawno 'Gryffindor' pojmał hiszpańską galeonę skarbów pełną srebra dzięki starannemu planowaniu Michela. To samo w sobie powinno zrekompensować dziesiątki przyszłych niepowodzeń. A jednak, twój brat został aresztowany.";
			link.l1 = "Rozumiem. Czy masz jakieś pojęcie, dlaczego Michel uciekł ze St. Pierre?";
			link.l1.go = "spanish_6";
		break;
		
		case "spanish_6":
			dialog.text = "Podejrzewam, że konflikt osobisty między Michelem a de Poincy był powodem jego aresztowania. Oczywiście, twój brat obawia się, że Kawaler będzie go prześladował nawet po jego uwolnieniu, więc podjął środki ostrożności. I wiesz co, Monsieur de Maure - nikt tutaj nie obwinia go za tę decyzję!\nCzłowiek ten pracował dzielnie dla dobra Zakonu, a jednak wrzucili go do cuchnącej celi za jego pierwszą porażkę, podczas gdy był ciężko ranny! Porażka, która nawet nie była taka zła, nikt nie zginął i żadne statki nie zatonęły!\nA tak przy okazji, ta rozmowa jest ściśle poufna i nie powtórzę tego, co właśnie powiedziałem, nawet pod przysięgą, czy to jasne, Monsieur de Maure?";
			link.l1 = "Tak, sir. Już zapomniałem, że mieliśmy tę rozmowę. Powiedz mi, czy atak Hiszpanów na St. Pierre mógł być sprowokowany przez Najświętszy Zakon napadający na hiszpańskie statki? Może chodzi o ten sam hiszpański galeon ze srebrem, o którym wspominałeś? Kastylijczycy byli niezwykle gorliwi w poszukiwaniu waszej bazy...";
			link.l1.go = "spanish_7";
		break;
		
		case "spanish_7":
			dialog.text = "Nie sądzę. Bardzo niewiele osób wie o obecności Zakonu na Karaibach, a wszystkie nasze wypady przeciwko Hiszpanom były starannie zaplanowane. Zapytaj hiszpańskiego oficera, którego wzięliśmy do niewoli, chłodzi teraz swój ognisty kastylijski temperament w naszych kazamatach. Już go przesłuchaliśmy. Atak na St. Pierre był zwykłym rajdem zorganizowanym przez hiszpańskiego wielkiego barona imieniem Ramon de Mendoza y Riba dla jego własnego zysku i zastraszenia francuskich kolonii. Chciał także zdobyć przychylność Escorialu.";
			link.l1 = "Porozmawiam z tym Hiszpanem. Gdzie mogę go znaleźć?";
			link.l1.go = "spanish_8";
		break;
		
		case "spanish_8":
			dialog.text = "Na dole, w tej samej celi, gdzie trzymano twojego brata.";
			link.l1 = "Znam drogę. Wrócę po przesłuchaniu Hiszpana. Mogę mieć kilka dodatkowych pytań.";
			link.l1.go = "spanish_9";
		break;
		
		case "spanish_9":
			DialogExit();
			NextDiag.CurrentNode = "Maltie_officer";
			AddQuestRecord("Guardoftruth", "2");
			pchar.questTemp.Guardoftruth = "prisoner";
			sld = characterFromId("spa_baseprisoner");
			LAi_CharacterEnableDialog(sld);
			chrDisableReloadToLocation = true;//закрыть локацию
		break;
		
		case "spanish_10":
			dialog.text = "Cóż, cóż za niespodzianka! Rozumiesz, że nie mogę uwolnić tego więźnia, prawda? Ten łotr pomógł w ataku na St. Pierre!";
			link.l1 = "Oficerze, to ważny świadek. Atak na St. Pierre nie był prostym najazdem w poszukiwaniu łupów. Don Ramon Mendosa szukał czegoś innego. Musimy poznać ostateczny motyw. Więc czy zwolnisz mi tego Hiszpana, czy będę musiał żądać pozwolenia od de Poincy?";
			link.l1.go = "spanish_11";
		break;
		
		case "spanish_11":
			dialog.text = "Na Boga Wszechmogącego... Dobrze, zabierzcie go. I tak miałem powiesić tego drania na placu w St. Pierre jak pospolitego pirata, którym jest... Teraz to wasz problem. Dopilnujcie, by nie uszedł sprawiedliwości!";
			link.l1 = "Bez wątpienia. Odpowiem za tego Hiszpana przed de Poincy. Zakuć tego jeńca w kajdany i dostarczyć do mojej łodzi przy miejskim nabrzeżu.";
			link.l1.go = "spanish_12";
		break;
		
		case "spanish_12":
			dialog.text = "Bardzo dobrze, kapitanie.";
			link.l1 = "Jeszcze jedna rzecz, oficerze. Czy nazwisko Miguel Dichoso coś Ci mówi?";
			link.l1.go = "spanish_13";
		break;
		
		case "spanish_13":
			dialog.text = "Nie. Nigdy wcześniej tego nie słyszałem. Dlaczego pytasz?";
			link.l1 = "Czy jesteś pewien? Czyli nie spotkałeś nikogo o tym imieniu, ani tutaj w swoim kantonie, ani w pałacu gubernatora, ani nigdzie w St. Pierre?";
			link.l1.go = "spanish_14";
		break;
		
		case "spanish_14":
			dialog.text = "Nie, nie mam. W moich stronach nie mamy zbyt dobrej opinii o Hiszpanach.";
			link.l1 = "Dobrze. W każdym razie, tego można było się spodziewać. Byłoby zbyt łatwo... Dziękuję, oficerze! Byłeś bardzo pomocny.";
			link.l1.go = "spanish_15";
		break;
		
		case "spanish_15":
			dialog.text = "Jesteś mile widziany... Jak myślisz, monsieur de Maure, gdzie teraz jest twój brat?";
			link.l1 = "Sam chciałbym znać odpowiedź na to pytanie. I dowiem się... prędzej czy później. Au revoir!";
			link.l1.go = "spanish_16";
		break;
		
		case "spanish_16":
			DialogExit();
			NextDiag.CurrentNode = "Maltie_officer";
			AddQuestRecord("Guardoftruth", "3");
			pchar.questTemp.Guardoftruth = "toship";
			sld = characterFromId("spa_baseprisoner");
			sld.dialog.currentnode = "spa_prisoner_28";
			LAi_CharacterEnableDialog(sld);
		break;
		
	// монах-посланник от Винсенто
		case "monk_vinsento":
			dialog.text = TimeGreeting()+"! Czy jesteś kapitanem "+GetFullName(pchar)+"?";
			link.l1 = "Tak, to ja. Co mogę dla ciebie zrobić?";
			link.l1.go = "monk_vinsento_1";
		break;
		
		case "monk_vinsento_1":
			dialog.text = "Witaj, kapitanie. Zostałem do ciebie wysłany przez ojca Vincento. Mam coś dla ciebie...";
			link.l1 = "Ojciec Vincento? Nie pracuję już dla Jego Łaski. Nie po tym, jak wysłał Alonso de Maldonado, przysięgłego człowieka Diego de Montoya, żeby mnie zabił. Możesz przekazać ten komunikat Czcigodnemu Ojcu: nie udało mu się.";
			link.l1.go = "monk_vinsento_2";
		break;
		
		case "monk_vinsento_2":
			dialog.text = "Poczekaj, kapitanie. Ojciec Vincento spodziewał się takiej reakcji z twojej strony i mnie przed tym ostrzegł. Zapewniam cię, że Jego Łaska nie życzy ci źle. Proszę, przeczytaj ten list. To bardzo, bardzo ważne.";
			link.l1 = "Ojciec Vincento nie życzy mi nic złego? Hm. Może również nie powiedział ci nic o mnie i Don de Maldonado? Rozumiem, dlaczego miałbym ci wierzyć.";
			link.l1.go = "monk_vinsento_3";
		break;
		
		case "monk_vinsento_3":
			dialog.text = "Weź ten list, kapitanie. Przeczytaj go i podejmij własną decyzję. Wiedz tylko, że los całego chrześcijaństwa jest w twoich rękach. Nie traktuj tego lekko. Niech Bóg cię błogosławi i prowadzi na ścieżkę prawości!";
			link.l1 = "Dobrze, daj mi list.";
			link.l1.go = "monk_vinsento_4";
		break;
		
		case "monk_vinsento_4":
			GiveItem2Character(pchar, "specialletter"); 
			ChangeItemDescribe("specialletter", "itmdescr_specialletter_vinsento");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Vincento_last";
			dialog.text = "Oto i jest. Modlę się, że podejmiesz właściwą decyzję. Pax vobiscum.";
			link.l1 = "...";
			link.l1.go = "monk_vinsento_5";
		break;
		
		case "monk_vinsento_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 30.0);
			ReOpenQuestHeader("Sharlie"); // patch-8
			AddQuestRecord("Sharlie", "40");
			CloseQuestHeader("Ksochitam");
		break;
		
	// падре Адриан
		case "adrian":
			dialog.text = "Witaj, mój synu. Niech Pan będzie z tobą.";
			link.l1 = "I również z tobą, Ojcze Adrianie. Jego Ekscelencja powiedział, że możesz dostarczyć mi amulety i lekarstwa.";
			link.l1.go = "adrian_1";
		break;
		
		case "adrian_1":
			dialog.text = "Tak, oczywiście. Otrzymałem specjalną przesyłkę z Santiago właśnie dla ciebie. Oto amulety pobłogosławione i mikstury lecznicze. A na dodatek, rzadka, unikalna nalewka Ometochtli, która uczyni cię niezwyciężonym w walce. To wszystko dla ciebie, mój synu. Weź i przekonaj się, że Pan jest dobry.";
			link.l1 = "Dziękuję!";
			link.l1.go = "adrian_2";
		break;
		
		case "adrian_2":
			for(i=2; i<=10; i++)
			{
				if (i == 4 || i == 5 || i == 8 || i == 9) continue;
				TakeNItems(pchar, "amulet_"+i, 2);
			}
			TakeNItems(pchar, "potion2", 20);
			TakeNItems(pchar, "potion4", 10);
			TakeNItems(pchar, "potion7", 3);
			TakeNItems(pchar, "berserker_potion", 3);
			dialog.text = "Jeśli potrzebujesz więcej ziół leczniczych, mogę dostarczyć ci fiolkę każdego dnia. Przygotuję tyle, ile będziesz potrzebować.";
			link.l1 = "Jestem wdzięczny, Ojcze Adrianie. Zapamiętam to.";
			link.l1.go = "exit";
			link.l2 = "Świetnie. Teraz właśnie tego potrzebuję.";
			link.l2.go = "potion";
			NextDiag.TempNode = "adrian_3";
		break;
		
		case "adrian_3":
			dialog.text = "Niech cię Bóg błogosławi i strzeże, mój synu. Czego sobie życzysz?";
			link.l1 = "Chciałbym zakupić kilka mikstur leczniczych.";
			link.l1.go = "potion";
			link.l2 = "W tej chwili nic, przygotowuję się do podróży. Wpadłem tylko, aby się przywitać i zobaczyć, jak się masz.";
			link.l2.go = "exit";
			NextDiag.TempNode = "adrian_3";
		break;
		
		case "potion":
			dialog.text = "Oczywiście, mój synu. Jakiego lekarstwa potrzebujesz?";
			if (!CheckAttribute(npchar, "potion1_date") || GetNpcQuestPastDayParam(npchar, "potion1_date") >= 1)
			{
				link.l1 = "Po prostu prosty środek zaradczy.";
				link.l1.go = "potion1";
			}
			if (!CheckAttribute(npchar, "potion2_date") || GetNpcQuestPastDayParam(npchar, "potion2_date") >= 1)
			{
				link.l2 = "Eliksir dający zdrowie.";
				link.l2.go = "potion2";
			}
			if (!CheckAttribute(npchar, "potion3_date") || GetNpcQuestPastDayParam(npchar, "potion3_date") >= 1)
			{
				link.l3 = "Antidotum.";
				link.l3.go = "potion3";
			}
			if (!CheckAttribute(npchar, "potion4_date") || GetNpcQuestPastDayParam(npchar, "potion4_date") >= 1)
			{
				link.l4 = "Mieszanka ziołowa.";
				link.l4.go = "potion4";
			}
			link.l5 = "Przepraszam, że cię niepokoję, ojcze. Zmieniłem zdanie.";
			link.l5.go = "exit";
		break;
		
		case "potion1":
			npchar.quest.price = 90;
			npchar.quest.type = 1;
			dialog.text = "Esencja lecznicza? To będzie 90 pesos, synu. Oczywiście, za materiały.";
			if (sti(Pchar.money) >= 90)
			{
				link.l1 = "Dziękuję, ojcze.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Niestety, nie mam pieniędzy... Wrócę później.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion2":
			npchar.quest.price = 500;
			npchar.quest.type = 2;
			dialog.text = "Eliksir zdrowia? 500 pesos, mój synu.";
			if (sti(Pchar.money) >= 500)
			{
				link.l1 = "Dziękuję, ojcze.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Niestety, nie mam pieniędzy... Wrócę później.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion3":
			npchar.quest.price = 200;
			npchar.quest.type = 3;
			dialog.text = "Antidotum? 200 pesos, mój synu.";
			if (sti(Pchar.money) >= 200)
			{
				link.l1 = "Dziękuję, ojcze.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Niestety, nie mam pieniędzy... Wrócę później.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion4":
			npchar.quest.price = 900;
			npchar.quest.type = 4;
			dialog.text = "Mieszanka ziołowa? 900 pesos, mój synu.";
			if (sti(Pchar.money) >= 900)
			{
				link.l1 = "Dziękuję, ojcze.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Niestety, nie mam pieniędzy... Wrócę później.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion_pay":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.price));
			iTemp = sti(npchar.quest.type);
			GiveItem2Character(pchar, "potion"+iTemp);
			PlaySound("interface\important_item.wav");
			dialog.text = "Dlatego przywrócę ci zdrowie i uzdrowię cię z twoich ran, mówi Pan.";
			link.l1 = "Dziękuję, ojcze Adrianie.";
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "potion"+iTemp+"_date");
			NextDiag.TempNode = "adrian_3";
		break;
		
	// посланец Дичозо
		case "Dichoso_agent":
			dialog.text = "Kapitanie "+GetFullName(pchar)+"?";
			link.l1 = "Tak, to ja. Czego chcesz?";
			link.l1.go = "Dichoso_agent_1";
		break;
		
		case "Dichoso_agent_1":
			dialog.text = "Mam dla ciebie wiadomość od kapitana Miguela Dichoso. Mówi, że go znasz.";
			link.l1 = "Tak, słyszałem o nim. Nigdy nie miałem honoru spotkać go osobiście.";
			link.l1.go = "Dichoso_agent_2";
		break;
		
		case "Dichoso_agent_2":
			dialog.text = "Kapitan Dichoso chciałby to zmienić. Chce spotkać się z tobą twarzą w twarz. Ma dla ciebie propozycję dotyczącą wyprawy w głąb hiszpańskiego Main do zaginionego indiańskiego miasta Tayasal. Powiedział mi, że twoje doświadczenie połączone z jego wiedzą przyniesie zadowalające rezultaty.";
			link.l1 = "To były jego dokładne słowa?";
			link.l1.go = "Dichoso_agent_3";
		break;
		
		case "Dichoso_agent_3":
			dialog.text = "Zgadza się. Kapitan Dichoso będzie czekał na ciebie na St. Christopher. Będzie cię oczekiwał w dużej krypcie cmentarza Capsterville, aby uniknąć ciekawskich oczu i uszu.";
			link.l1 = "Hm...";
			link.l1.go = "Dichoso_agent_4";
		break;
		
		case "Dichoso_agent_4":
			dialog.text = "Dichoso ostrzegł mnie, że możesz się wahać. Powiedział mi, bym dał ci gwarancje, że nie zostaniesz skrzywdzony podczas negocjacji, niezależnie od twojej decyzji. Dodał również, że to, co znalazłeś na pewnej wyspie, było tylko małą przystawką w porównaniu z tym, co znajdziesz w Tayasal.";
			link.l1 = "Czyżby... to bardzo intrygujące. Ale dlaczego kapitan Dichoso nie odwiedził mnie osobiście? Dlaczego wysłał pośrednika?";
			link.l1.go = "Dichoso_agent_5";
		break;
		
		case "Dichoso_agent_5":
			dialog.text = "Don Dichoso najpierw szukał cię na Isla Tesoro, potem tutaj, a teraz zmierza do St. Christopher z nadzieją, że cię tam znajdzie. Jesteś oficerem samego Philippe'a de Poincy, prawda? Miałem na ciebie czekać tutaj na wypadek, gdybyś przybył do Blueweld.";
			link.l1 = "Wszystko jasne. No dobrze. Nie będę marnował czasu, powinienem udać się do Capsterville.";
			link.l1.go = "Dichoso_agent_6";
		break;
		
		case "Dichoso_agent_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "Tieyasal_PrepareDichosoTrap", -1);
		break;
		
	// агент Дичозо
		case "Dichoso_crypt_agent":
			dialog.text = "No, nareszcie się spotykamy, kapitanie "+GetFullName(pchar)+"... ";
			if (CheckAttribute(pchar, "questTemp.Tieyasal.MigelKnow")) 
			{
				link.l1 = "Gdzie jest Miguel Dichoso? I nie próbuj się z tego wykręcić. Wiem, kim on naprawdę jest, i myślę, że ty też to wiesz.";
				link.l1.go = "Dichoso_crypt_agent_2";
			}
			else
			{
				link.l1 = "Przypuszczam, że to Miguel Dichoso we własnej osobie przede mną?";
				link.l1.go = "Dichoso_crypt_agent_1";
			}
		break;
		
		case "Dichoso_crypt_agent_1":
			dialog.text = "Zgadujesz poprawnie, kapitanie. Już od długiego czasu depczemy sobie po piętach, prawda?";
			if (CheckAttribute(pchar, "questTemp.Ksochitam.SQCapBookRead")) // прочел журнал Санта-Квитерии
			{
				link.l1 = "Widzę, że kłamiesz, patrząc na ciebie, kamracie. Nie jesteś Dichoso. Przeczytałem wpisy w dzienniku kapitana 'Santa Quiteria' i wypytałem o jego wygląd. Nie wyglądasz jak on. Nie masz nawet blizny na twarzy od kawaleryjskiej szabli. No dalej, nawet błazen mógłby przynajmniej spróbować ją narysować!";
				link.l1.go = "Dichoso_crypt_agent_2";
			}
			else
			{
				link.l1 = "Dokładnie. Jak rozumiem, jesteśmy tutaj, aby porozmawiać o zaginionym mieście Tayasal?";
				link.l1.go = "Dichoso_crypt_agent_7";
			}
		break;
		
		case "Dichoso_crypt_agent_2":
			dialog.text = "Ha!  Nie ma sensu kontynuować tej farsy. Miguel ostrzegł mnie, że jesteś przebiegłym łajdakiem...";
			link.l1 = "Gdzie jest Miguel Dichoso?";
			link.l1.go = "Dichoso_crypt_agent_3";
		break;
		
		case "Dichoso_crypt_agent_3":
			dialog.text = "Nie ma go tutaj. Jestem upoważniony, aby spotkać się z tobą i porozmawiać w jego imieniu.";
			link.l1 = "Nie będę rozmawiał z pionkiem. Jestem tu dla króla. Gdzie on jest?!";
			link.l1.go = "Dichoso_crypt_agent_4";
		break;
		
		case "Dichoso_crypt_agent_4":
			dialog.text = "Nie jesteś przyjemnym rozmówcą, kapitanie. Straciłeś panowanie nad sobą.";
			link.l1 = "Dosyć gierek, rozumiem. To znowu zasadzka. Chłopcy, musicie wymyślić jakieś nowe sztuczki.";
			link.l1.go = "Dichoso_crypt_agent_5";
		break;
		
		case "Dichoso_crypt_agent_5":
			dialog.text = "Haha, masz rację, kamracie! Moi ludzie czekają na ciebie tuż za drzwiami prowadzącymi do katakumb. Co więcej, mam muszkieterów ukrytych za każdym z nagrobków, gotowych do strzału. Nie ma ucieczki. Tak więc, jak powtarzalny może być ten trik, wpadłeś prosto w niego! Twoje pragnienie zobaczenia Tayasal przeważyło nad zdrowym rozsądkiem!";
			link.l1 = "Wybrałeś świetne miejsce na walkę, łajdaku. Nie będę musiał daleko iść, by pochować ciebie i twoich zbójeckich przyjaciół.";
			link.l1.go = "Dichoso_crypt_agent_6";
		break;
		
		case "Dichoso_crypt_agent_6":
			dialog.text = "Haha! Podoba mi się twój dowcip! Zupełnie jak Miguel! Mów, co chcesz, obaj jesteście zrobieni z tej samej gliny... Zrobię dokładnie tak, jak on rozkazał - wyślę cię do piekła najszybciej i bezboleśnie, jak to możliwe. Do broni, chłopcy!";
			link.l1 = "Lepsi ludzie od ciebie próbowali. Pozdrów ode mnie diabła, łajdaku!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_StartCryptBattle");
		break;
		
		case "Dichoso_crypt_agent_7":
			dialog.text = "Naprawdę chcesz dostać się do miasta? Rozumiem, kapitanie, ale nie sądzę, że to dobry pomysł.";
			link.l1 = "Więc o czym mamy tu rozmawiać?";
			link.l1.go = "Dichoso_crypt_agent_8";
		break;
		
		case "Dichoso_crypt_agent_8":
			dialog.text = "Nie szukam długiej, romantycznej rozmowy z tobą. Jesteś tutaj i to mi wystarczy.";
			link.l1 = "Dość gierek, rozumiem. Znowu zasadzka. Chłopcy, musicie wymyślić jakieś nowe sztuczki.";
			link.l1.go = "Dichoso_crypt_agent_5";
		break;
		
	// командир абордажников
		case "newcastle_officer":
			dialog.text = "Oczekuję na twoje rozkazy, kapitanie!";
			link.l1 = "Przechodzimy przez dżunglę do cmentarza w Capsterville. Gdy tam dotrzemy, nie wchodźcie na sam cmentarz. Zajmijcie pozycje do strzału tuż przed bramą i uważnie słuchajcie, gdy wejdę do środka. Jeśli usłyszycie walkę, natychmiast ruszajcie do środka.";
			link.l1.go = "newcastle_officer_1";
		break;
		
		case "newcastle_officer_0":
			dialog.text = "Oczekuję na twoje rozkazy, kapitanie!";
			link.l1 = "Zmierzamy przez dżunglę do cmentarza w Capsterville. Gdy tam dotrzemy, nie wchodźcie na sam cmentarz. Zajmijcie pozycje strzeleckie wzdłuż ścieżki, otoczcie cmentarz i nasłuchujcie, kiedy wejdę do środka. Cała ta sprawa śmierdzi zasadzką. Jak tylko zobaczycie wroga, atakujcie natychmiast.";
			link.l1.go = "newcastle_officer_1";
		break;
		
		case "newcastle_officer_1":
			dialog.text = "Tak jest, kapitanie!";
			link.l1 = "Dobrze. Naprzód!";
			link.l1.go = "newcastle_officer_2";
		break;
		
		case "newcastle_officer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			locations[FindLocation("Charles_exittown")].DisableEncounters = true; //энкаутеры закрыть
			locations[FindLocation("Charles_CaveEntrance")].DisableEncounters = true; //энкаутеры закрыть
			for(i=2; i<=4; i++)
			{
				locations[FindLocation("Charles_Jungle_0"+i)].DisableEncounters = true; //энкаутеры закрыть
			}
			LocatorReloadEnterDisable("Shore42", "boat", true);
			for(i=1; i<=iTotalTemp; i++)
			{
				sld = characterFromID("Tieyasal_Oursoldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			// на локацию перед кладбищем
			pchar.quest.Tieyasal_newcastle.win_condition.l1 = "location";
			pchar.quest.Tieyasal_newcastle.win_condition.l1.location = "Charles_exittown";
			pchar.quest.Tieyasal_newcastle.function = "Tieyasal_NewcastleGoJungle";
			// на крипту
			pchar.quest.Tieyasal_graveyard.win_condition.l1 = "location";
			pchar.quest.Tieyasal_graveyard.win_condition.l1.location = "Charles_CryptBig2";
			pchar.quest.Tieyasal_graveyard.function = "Tieyasal_InGraveyardCrypt";
		break;

case "Europe":
			PlaySound("Voice\English\military01.wav");
			dialog.text = "Kapitanie Hobart! Według informacji naszego szpiega, buntownicy ukrywają się w tej posiadłości. Masz do dyspozycji pięciu dragonów. Przeszukaj budynek i aresztuj każdego, kto się tam kręci! Nie obchódź się z tą hołotą jak z dziećmi. Działasz w imieniu Króla!";
			link.l1 = "Tak, sir!";
			link.l1.go = "Europe_1";
		break;
		
		case "Europe_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Europe_SharlieFinal_1", 5);
		break;
		
		//Индеец по квесту "Знакомство с индейцами"
		case "ZsI_ListKakao":
			dialog.text = "Tsk! Synu Morza!";
			link.l1 = "Eh... co? Mówisz do mnie?";
			link.l1.go = "ZsI_ListKakao_1";
			sld = characterFromId("Tichingitu");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		break;
		
		case "ZsI_ListKakao_1":
			dialog.text = "Racja. Jestem Liść Kakaowca. Mam z tobą sprawę, Synu Morza.";
			link.l1 = "Nie wiem, jak wygląda kakao, ani dlaczego masz takie imię. Ale dobrze, powiedz mi, czego potrzebujesz, szybko.";
			link.l1.go = "ZsI_ListKakao_2";
		break;
		
		case "ZsI_ListKakao_2":
			dialog.text = "Tsk! Idź do miasta. Kup dwa pistolety oraz dziesięć prochu i kul. Przynieś je do mnie. Czeka nagroda. Syn Morza będzie zadowolony.";
			link.l1 = "Dwa pistolety i dwadzieścia strzałów? To wszystko? Dlaczego więc sam ich nie kupisz?";
			link.l1.go = "ZsI_ListKakao_3";
		break;
		
		case "ZsI_ListKakao_3":
			dialog.text = "Czy nie rozumiesz, bladziuchu? Kto by mi sprzedał broń ogniową?!";
			if (CheckAttribute(pchar, "questTemp.ZsI_Cannibals"))		//Sinistra Только если проходил квест "Каннибалы"
			{
				link.l1 = "Wiesz, spotkałem takich jak ty wcześniej na Martynice... Kanibale. Porwali dziewczynę i dwóch mężczyzn. Jednego z mężczyzn upiekli i zjedli. Gdyby którykolwiek z nich miał pistolet, nie prowadzilibyśmy tej rozmowy.";
				link.l1.go = "ZsI_ListKakao_3_1";
			}
			else
			{
				link.l1 = "A po co ci broń palna, Liściu Kokainy? Chcesz kogoś zabić?";
				link.l1.go = "ZsI_ListKakao_3_2";
			}
		break;
		
		case "ZsI_ListKakao_3_1":
			dialog.text = "Goo-oo! Liść Kakao nie jest zbójem, moja walka jest tylko dla wojowników twojego plemienia. Bladoskórzy przybywają na nasze ziemie, czynią nas niewolnikami. Liść Kakao sam walczy. Weź niewolnika. Nie dobrze, nie źle. Tak to jest. Indianin, biały, nie ma różnicy. Broń ogniowa robi różnicę.";
			link.l1 = "„A po co ci broń palna, Liściu Kakaowca? Chcesz kogoś zabić?”";
			link.l1.go = "ZsI_ListKakao_3_2";
		break;
		
		case "ZsI_ListKakao_3_2":
			dialog.text = "Aby walczyć. Ale na równych warunkach. Bladzi twarze mają broń palną, Indianie nie. To niesprawiedliwe. A posiadanie broni palnej przez Indianina - to ochrona przed niesprawiedliwym traktowaniem, poniżeniem lub zniewagą przez bladych twarzy.";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_4";
		break;
		
		case "ZsI_ListKakao_4":
			StartInstantDialog("Tichingitu", "ZsI_ListKakao_5", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_ListKakao_5":
			dialog.text = "Dobrze, kapitanie. Bladzi twarze patrzą na nas z góry.";
			link.l1 = "Zauważyłem. W Europie głoszą kazania o nauczaniu Indian prawdziwej wiary i o tym, jak wszyscy razem pokojowo pracujemy na plantacjach...";
			link.l1.go = "ZsI_ListKakao_7";
		break;
		
		case "ZsI_ListKakao_7":
			dialog.text = "Tichingitu może nie rozumieć kapitana, ale rozumie Liść Kakaowy. Szuka zemsty.";
			link.l1 = "Wygląda na to... Czy ty też nie chcesz zemsty, na naszych ostatnich porywaczach?";
			link.l1.go = "ZsI_ListKakao_8";
		break;
		
		case "ZsI_ListKakao_8":
			dialog.text = "Być może. Ale Tichingitu nie ucieknie się do tego. Tichingitu jest teraz z tobą. I Tichingitu używa własnej głowy. Będzie zbyt wiele rozlewu krwi. Białej krwi. Krwi indiańskiej. Zbyt wiele cierpienia. To nie jest w porządku.";
			link.l1 = "Tak, już jest źle, a pomoc Liściowi Kokainy w zdobyciu broni tylko pogorszy sytuację... Ale ma swoje racje. A ja wciąż muszę zapłacić załodze wkrótce.";
			link.l1.go = "ZsI_ListKakao_9";
		break;
		
		case "ZsI_ListKakao_9":
			dialog.text = "Użyj swojej głowy, Kapitanie.";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_10";
		break;
		
		case "ZsI_ListKakao_10":
			StartInstantDialog("ListKakao", "ZsI_ListKakao_11", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_ListKakao_11":
			dialog.text = "Syn morza dużo gada. Wygląda jak squaw z wąsami.";
			link.l1 = "Kto? Wyjaśnij mi to, Liściu Kokii. Też jestem bladolicym, a ty prosisz mnie o broń, by walczyć z bladolicymi. Czy to nie jest sprzeczne? Dlaczego zwracasz się do mnie?";
			link.l1.go = "ZsI_ListKakao_12";
		break;
		
		case "ZsI_ListKakao_12":
			dialog.text = "Podsłuchałem twoją rozmowę z tym dziwnie ubranym Indianinem. Nie jesteś jak inni białoskórzy. Rozumiesz Tichingitu. I rozumiesz liść kakao, jestem pewien.";
			link.l1 = "Ach... Co zaproponujesz za broń, Liściu Kakaowy?";
			link.l1.go = "ZsI_ListKakao_13";
		break;
		
		case "ZsI_ListKakao_13":
			dialog.text = "Łzy bogów. Nazywasz je perłami. Wiele pereł.";
			link.l1 = "Podjąłem decyzję, Liściu Koki. Zaczekaj tutaj, idę do handlarza bronią. Kupię, co potrzebuję i wrócę.";
			link.l1.go = "ZsI_ListKakao_Soglasen_5";
			if (sti(pchar.items.pistol1) >= 2 && sti(pchar.items.GunPowder) >= 20 && sti(pchar.items.bullet) >= 20)
			{
				link.l2 = "Podjąłem decyzję, Liściu Kokainowy. Przypadkiem już mam to, czego potrzebujesz. Proszę bardzo.";
				link.l2.go = "ZsI_ListKakao_Soglasen_2";
			}
			link.l3 = "Podjąłem decyzję, Liściu Kokowy. Nie chcę zapraszać niepotrzebnych kłopotów. Nie dostaniesz ode mnie broni palnej. Ruszaj dalej.";
			link.l3.go = "ZsI_ListKakao_Otkaz";
			npchar.LifeDay = 1;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		
		case "ZsI_ListKakao_Otkaz":
			dialog.text = "Tfu!";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_Otkaz_2";
		break;
		
		case "ZsI_ListKakao_Otkaz_2":
			DialogExit();
			
			ChangeIndianRelation(-3.0);
			ChangeCharacterComplexReputation(pchar, "authority", -1);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "ZsI_Mir", -1);
			LAi_SetImmortal(npchar, false);
			LAi_SetHP(npchar, 1.0, 1.0);
			npchar.lifeday = 0;
			PChar.quest.ZsI_Draka.win_condition.l1 = "NPC_Death";
			PChar.quest.ZsI_Draka.win_condition.l1.character = "ListKakao";
			PChar.quest.ZsI_Draka.win_condition = "ZsI_Draka";
			PChar.quest.ZsI_Mir.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ZsI_Mir.win_condition.l1.location = PChar.location;
			PChar.quest.ZsI_Mir.win_condition = "ZsI_Mir";
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			sld = characterFromId("Tichingitu");
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
			sld.Dialog.CurrentNode = "Tichingitu_officer";
			LaunchTutorial("Fighter", 1);
		break;
		
		case "ZsI_ListKakao_Soglasen_2":
			dialog.text = "O rety! Czy Syn Morza ma muszkiet? Zapłać wysoką cenę za muszkiet!";
			link.l1 = "Nie, ale czy działo z mojego statku wystarczy? Wynoś się teraz, Liściu Kokowy, zanim nas zauważą i aresztują.";
			link.l1.go = "ZsI_ListKakao_Soglasen_3";
			AddCharacterExpToSkill(pchar, "Commerce", 50);
			ChangeIndianRelation(3.0);
			AddItems(pchar, "jewelry53", 180);
			Log_Info("You have received 180 small pearls");
			PlaySound("Interface\important_item.wav");
			DeleteAttribute(pchar, "questTemp.ZsI_PokupaemPistolety");
			if (sti(pchar.items.pistol1) >= 2 && sti(pchar.items.GunPowder) >= 20 && sti(pchar.items.bullet) >= 20)
			{
				RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
				RemoveItems(PChar, "pistol1", 2);
				RemoveItems(PChar, "GunPowder", 20);
				RemoveItems(PChar, "bullet", 20);
			}
		break;
		
		case "ZsI_ListKakao_Soglasen_3":
			dialog.text = "Świetny interes! Synu Morza, jeśli idziesz do selvy, weź broń palną. Spotkaj Indianina, zrób interes.";
			link.l1 = "Zapamiętam to. Żegnaj, Liściu Koki.";
			link.l1.go = "ZsI_ListKakao_Soglasen_4";
		break;
		
		case "ZsI_ListKakao_Soglasen_4":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			npchar.lifeday = 0;
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			Return_TichingituOfficer();
			LaunchTutorial("Fighter", 1);
		break;
		
		case "ZsI_ListKakao_Soglasen_5":
			dialog.text = "Lekkość kakao poczeka.";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_Soglasen_6";
		break;
		
		case "ZsI_ListKakao_Soglasen_6":
			DoQuestReloadToLocation("BasTer_town", "reload", "gate_back", "ZsI_TPvGorod");
		break;

		case "ZsI_officer":
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				dialog.text = "Phi, wygląda na to, że mamy tu zgromadzenie tubylców!\nChcesz wrócić do więzienia, psie?\nCo tu robisz, monsieur?";
			}
			else
			{
				dialog.text = "Stać! Co tu robisz, Monsieur?";
			}
			link.l1 = "";
			link.l1.go = "ZsI_officer_2";
			sld = CharacterFromID("ListKakao");
			LAi_CharacterEnableDialog(sld);
			EndBattleLandInterface();
		break;
		
		case "ZsI_officer_2":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("ListKakao"));
			dialog.text = "Hej, łachudro, czekałeś na tego szanowanego obywatela?";
			link.l1 = "";
			link.l1.go = "ZsI_officer_3";
		break;
		
		case "ZsI_officer_3":
			DialogExit();
			StartInstantDialog("ListKakao", "ZsI_officer_4", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_officer_4":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("ZsI_Patrul_off"));
			dialog.text = "Wszystkie blade twarze wyglądają dla mnie tak samo. Ale tego jeszcze nie widziałem. Ty, wojowniku, rób ze mną, co musisz. To się robi męczące. Liść Kakao jest gotów stawić czoła duchom lasu.";
			link.l1 = "";
			link.l1.go = "ZsI_officer_5";
		break;
		
		case "ZsI_officer_5":
			DialogExit();
			StartInstantDialog("ZsI_Patrul_off", "ZsI_officer_6", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_officer_6":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("ListKakao"));
			dialog.text = "Piekło na ciebie czeka, nie duchy lasu.";
			link.l1 = "";
			link.l1.go = "ZsI_officer_7";
		break;
		
		case "ZsI_officer_7":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			dialog.text = "Kapitanie, jesteś zwolniony. Trzymaj się z dala ode mnie. Ochrona miasta to poważna sprawa.";
			link.l1 = "Rozumiem... Ale co z tym Indianinem?";
			link.l1.go = "ZsI_officer_8";
		break;
		
		case "ZsI_officer_8":
			dialog.text = "Co cię interesuje w Indianach, Monsieur? Chociaż... cóż, tak, jesteś świeżo z Europy\nJak tam Paryż? Czy nadal miażdżą szczury miejskie, czy już zapraszają je na komunię? Widzisz, my mamy tubylców zamiast szczurów. Handlują z bukanierami, atakują drwali, jedzą ludzi, do diabła\nTrzy dni temu jakiś bystrzak już sprzedał muszkiet takim jak ten. I zgadnij co? Te łajdaki zabiły wszystkich żołnierzy w patrolu, na czele, swoją drogą, z moim przyjacielem i towarzyszem. Znaleźliśmy zdrajcę-kolonistę i powiesiliśmy go na słońcu, żeby dać przykład. Dawać broń palną Indianom! To zdrada! Zdrada przeciwko Francji! Śledziliśmy tę kolorową małpę od jakiegoś czasu, bo stał się już znajomą twarzą na różnych wydarzeniach\nCóż, teraz spotka go szybki i zasłużony koniec. Możesz ruszać dalej, Kapitanie. Nie angażuj się w sprawy, które cię nie dotyczą. Nie jesteś częścią tej wojny... Jeszcze... A może jesteś?!";
			if (IsCharacterPerkOn(Pchar, "Trustworthy"))
			{
				notification("Trustworthy", "Trustworthy");
				link.l1 = "„(Godny zaufania) Widzicie, oficerze... Jestem kapitan Charles de Maure, gość Fadeja Moskiewskiego. Mamy pewne zainteresowanie tym Indianinem... więc nie przeszkadzajmy sobie nawzajem w obowiązkach. Zgoda, poruczniku?”";
				link.l1.go = "ZsI_officer_Mir";
			}
			link.l2 = "Stosunek do nowo przybyłych, stosunek do tubylców... Koloniści, tubylcy... Jeszcze tego wszystkiego dobrze nie rozumiem, ale w tej chwili, poruczniku, porównanie nie przemawia na twoją korzyść... Do boju!";
			link.l2.go = "ZsI_officer_Draka";
			link.l3 = "Masz rację, poruczniku, nie jestem. Żegnaj.";
			link.l3.go = "ZsI_officerKIll";
			StartBattleLandInterface();
		break;
		
		case "ZsI_officer_Mir":
			dialog.text = "Ahem! Zrozumiano, Kapitanie. Proszę przekazać moje pozdrowienia panu Fadey. Oddział, wznowić patrol!";
			link.l1 = "";
			link.l1.go = "ZsI_officer_Mir_2";
		break;
		
		case "ZsI_officer_Mir_2":
			DialogExit();
			
			DeleteAttribute(pchar, "questTemp.CameraDialogMode");
			sld = CharacterFromID("ZsI_Patrul_off");
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			LAi_SetImmortal(sld, true);
			LAi_ActorGoToLocation(sld, "reload", "reload4", "none", "", "", "", -1);
			
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("ZsI_Patrul_"+i);
				LAi_SetActorType(sld);
				sld.lifeday = 0;
				LAi_SetImmortal(sld, true);
				LAi_ActorGoToLocation(sld, "reload", "reload4", "none", "", "", "", -1);
			}
			sld = CharacterFromID("ListKakao");
			sld.dialog.filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "ZsI_MirFinal";
			LAi_SetActorType(sld);
			LAi_SetActorType(pchar);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 2.0);
			LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 2.0);
			
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Fortune", 30);
		break;
		
		case "ZsI_MirFinal":
			dialog.text = "O rety!";
			link.l1 = "Tak, cóż, nawet ja jestem zaskoczony, że to zadziałało. Oto twoje towary, Liść Kakaowca.";
			link.l1.go = "ZsI_MirFinal_2";
		break;
		
		case "ZsI_MirFinal_2":
			dialog.text = "Syn Morza dobrze gada. Uratowanie Indianina to wielka sprawa! Wielka nagroda!";
			link.l1 = "Wow, to całkiem niezły łup... I kamień z dziurą, i jakiś amulet.";
			link.l1.go = "ZsI_MirFinal_3";
			AddItems(pchar, "jewelry53", 180);
			AddItems(pchar, "cannabis1", 3);
			GiveItem2Character(pchar, "indian_10");
			GiveItem2Character(pchar, "talisman11");
			Log_Info("You have received 180 small pearls");
			Log_info("You have received Amulet 'Cascavella'}");
			Log_info("You have received Ward 'Adder stone'");
			Log_info("You have received 3 Datura herbs");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "ZsI_MirFinal_3":
			dialog.text = "Czy Syn Morza ma muszkiet? Zapłać wysoką cenę za muszkiet!";
			link.l1 = "Nie, ale czy działo z mojego statku wystarczy? Zmykaj teraz, Liściu Kakaowy, zanim nas zauważą i aresztują.";
			link.l1.go = "ZsI_MirFinal_4";
		break;
		
		case "ZsI_MirFinal_4":
			dialog.text = "To interes! Synu Morza, jeśli wchodzisz do selva, zabierz broń palną. Spotkasz Indianina, będzie targ.";
			link.l1 = "Zapamiętam to. Żegnaj, Liściu Koki.";
			link.l1.go = "ZsI_MirFinal_5";
		break;
		
		case "ZsI_MirFinal_5":
			DialogExit();
			
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			npchar.lifeday = 0;
			LAi_LocationFightDisable(&Locations[FindLocation("BasTer_ExitTown")], false);
			LAi_SetPlayerType(pchar);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "ZsI_officer_Draka":
			DialogExit();
			
			DeleteAttribute(pchar, "questTemp.CameraDialogMode");
			LAi_LocationFightDisable(&Locations[FindLocation("BasTer_ExitTown")], false);
			LAi_SetFightMode(pchar, true);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			ChangeCharacterComplexReputation(pchar, "authority", -2);	
			ChangeIndianRelation(5.0);
			ChangeCharacterNationReputation(pchar, FRANCE, -10);
			sld = CharacterFromID("ListKakao");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_SetImmortal(sld, false);
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("ZsI_Patrul_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			sld = CharacterFromID("ZsI_Patrul_off");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "ZsI_officer_Draka_3");
		break;
		
		case "ZsI_Final":
			ChangeIndianRelation(5.0);
			dialog.text = "Oj-oj! Zła decyzja, Synu Morza. Dlaczego byś to zrobił?";
			link.l1 = "Ugh... Pięć minut temu wydawało się w porządku... Teraz nie jestem już taki pewien.... W końcu zabiłem swojego. Co mam teraz zrobić? Co jeśli się dowiedzą? Cholera! Cholera!";
			link.l1.go = "ZsI_Final_2";
		break;
		
		case "ZsI_Final_2":
			dialog.text = "Teraz będzie napad. Żołnierze zabiją wszystkich. Dwie patrole nie wybaczą. Liść Kakao biegnij. A ty, Synu Morza... dlaczego. Liść Kakao i tak zginie. Duchy tego chcą.";
			link.l1 = "Och... Czy nasza umowa nadal jest aktualna?";
			link.l1.go = "ZsI_Final_3";
		break;
		
		case "ZsI_Final_3":
			dialog.text = "Zła decyzja, Synu Morza. Ale dziękuję. Wielka nagroda.";
			link.l1 = "Nie tak duże, biorąc pod uwagę wszystko...";
			link.l1.go = "ZsI_Final_4";
			AddItems(pchar, "jewelry53", 180);
			AddItems(pchar, "cannabis1", 3);
			GiveItem2Character(pchar, "indian_10");
			GiveItem2Character(pchar, "talisman11");
			Log_Info("You have received 180 small pearls");
			Log_info("You have received Amulet 'Cascavella'}");
			Log_info("You have received Ward 'Adder stone'");
			Log_info("You have received 3 Datura herbs");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "ZsI_Final_4":
			dialog.text = "Synu Morza, jeśli przetrwasz, a potem udasz się do selwy, zabierz broń palną. Spotkasz Indianina, będzie to targować się.";
			link.l1 = "Będę to miał na uwadze na przyszłość. Żegnaj, Liściu Koki.";
			link.l1.go = "ZsI_Final_5";
		break;
		
		case "ZsI_Final_5":
			DialogExit();
			
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			LAi_SetImmortal(npchar, true);
			npchar.lifeday = 0;
		break;
		
		case "ZsI_officerKIll":
			DialogExit();
			
			DeleteAttribute(pchar, "questTemp.CameraDialogMode");
			sld = CharacterFromID("ZsI_Patrul_off");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("ListKakao"));
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("ZsI_officerKIll_1", 0.1);
			DoQuestCheckDelay("ZsI_officerKIll_2", 1.3);
			AddItems(pchar, "pistol1", 2);
			AddItems(pchar, "GunPowder", 20);
			AddItems(pchar, "bullet", 20);
		break;
		
		//Торговец Барбье по квесту "Деньги на деревьях"
		case "MOT_Barbie":
			dialog.text = "Witaj, Kapitanie Charles de Maure. Nazywam się Charles Barbier. Czy mogę zająć chwilę twojego czasu?";
			link.l1 = "Kapitan de Maure... Rzeczywiście, to ja! Proszę mówić dalej, Monsieur Barbier.";
			link.l1.go = "MOT_Barbie_2";
		break;
		
		case "MOT_Barbie_2":
			dialog.text = "Zawsze przyjemność spotkać kolegę po fachu, zwłaszcza takiego, z którym dzielę imię! Mam dla ciebie propozycję, kapitanie. Widzisz, potrzebuję eskorty do St. Pierre, i...";
			link.l1 = "Znam St. Pierre! Ale to tylko dwudniowa podróż! I muszę przyznać, że wciąż jestem dość zielony w roli eskorty. Dopiero tydzień temu objąłem dowództwo nad tym statkiem.";
			link.l1.go = "MOT_Barbie_3";
		break;
		
		case "MOT_Barbie_3":
			dialog.text = "Doceniam twoją uczciwość, Kapitanie. Charles, wybacz mi moją nieformalność, ale jesteś dokładnie tą osobą, której potrzebuję.";
			link.l1 = "Hmm... Przypominam sobie podobną propozycję niedawno. Doprowadziła do zasadzki piratów w pobliżu Le Francois.";
			link.l1.go = "MOT_Barbie_4";
		break;
		
		case "MOT_Barbie_4":
			dialog.text = "Słyszałem o tym incydencie, dlatego cię szukałem\nPo pierwsze, przewożę dość cenny ładunek, a zawsze czają się drapieżnicy. Jednakże, twoje ostatnie zwycięstwo nad tymi piratami w pobliżu Le Francois sprawi, że łotry tam się zastanowią\nPo drugie, twoje powiązanie z Fadeyem Moskiewskim to silna rekomendacja.";
			link.l1 = "Przekonujący argument, Monsieur. A jaką rekompensatę proponujesz za tę przysługę?";
			link.l1.go = "MOT_Barbie_5";
		break;
		
		case "MOT_Barbie_5":
			dialog.text = "To nie przysługa, Kapitanie, lecz wzajemnie korzystne przedsięwzięcie! Zapłacę ci czterdzieści złotych monet za eskortowanie mnie do St. Pierre w odpowiednim czasie.";
			if (IsCharacterPerkOn(Pchar, "Trustworthy"))
			{
				notification("Trustworthy", "Trustworthy");
				link.l1 = " (Godny zaufania) Ponieważ zmierzam w przeciwnym kierunku, Monsieur, wymagam płatności z góry.";
				link.l1.go = "MOT_Barbie_Torg";
			}
			link.l2 = "Nie najgorsza propozycja - i tak zmierzam w tamtym kierunku. Umowa stoi!";
			link.l2.go = "MOT_Barbie_Soglasen";
			link.l3 = "   Wartościowy ładunek, powiadacie? Niestety, monsieur, na chwilę obecną nasyciłem się przygodami.  ";
			link.l3.go = "MOT_Barbie_Otkaz";
		break;
		
		case "MOT_Barbie_Torg":
			dialog.text = "Trudno odmówić takiemu poważnemu młodzieńcowi, kapitanie. Oto twoje czterdzieści dublonów. Czy wypływamy bez zwłoki? Czas to pieniądz.";
			link.l1 = "Nie będziemy tu długo zwlekać, Monsieur. Wkrótce wyruszamy w morze.";
			link.l1.go = "MOT_Barbie_Escadra";
			
			AddItems(pchar, "gold_dublon", 40);
			Log_info("You've received 40 doubloons");
			PlaySound("Interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			AddCharacterExpToSkill(pchar, "Commerce", 20);
		break;
		
		case "MOT_Barbie_Soglasen":
			dialog.text = "Znakomicie! Natychmiast przygotuję się do wypłynięcia!";
			link.l3 = "";
			link.l3.go = "MOT_Barbie_Escadra";
		break;
		
		case "MOT_Barbie_Otkaz":
			dialog.text = "Rozumiem, kapitanie. Nie będę się narzucać. Żegnaj, i dobrego dnia.";
			link.l3 = "";
			link.l3.go = "MOT_Barbie_Otkaz_2";
		break;
		
		case "MOT_Barbie_Otkaz_2":
			DialogExit();
			
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload6_back", "none", "", "", "", -1);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "MOT_Barbie_Escadra":
			DialogExit();
			
			SetQuestHeader("MoneyOnTrees");
			AddQuestRecord("MoneyOnTrees", "1");
			
			FantomMakeCoolSailor(npchar, SHIP_BARKENTINE, "Charles", CANNON_TYPE_CANNON_LBS3, 40, 33, 20);
			npchar.Ship.Mode = "trade";
			SetCharacterRemovable(npchar, false);
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.CompanionEnemyEnable = true;
			SetCrewQuantity(npchar, 35);
			SetCharacterGoods(npchar, GOOD_ROPES, 30);
			LAi_SetImmortal(npchar, false);
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			SetTimerCondition("MOT_ZadanieProvaleno", 0, 0, 14, false);
			PChar.quest.MOT_Zahvatili.win_condition.l1 = "NPC_Death";
			PChar.quest.MOT_Zahvatili.win_condition.l1.character = "SharlieBarbie";
			PChar.quest.MOT_Zahvatili.win_condition = "MOT_Zahvatili";
			PChar.quest.MOT_Dostavili.win_condition.l1 = "location";
			PChar.quest.MOT_Dostavili.win_condition.l1.location = "FortFrance_town";
			PChar.quest.MOT_Dostavili.win_condition = "MOT_Dostavili";
		break;
		
		case "MOT_Barbie_101":
			if (IsCharacterPerkOn(Pchar, "Trustworthy"))
			{
				dialog.text = "Dziękuję za wzorową eskortę, Kapitanie. Cieszy mnie, że nie napotkaliśmy żadnych incydentów.";
				link.l1 = "Z przyjemnością robić z Panem interesy, Monsieur. A teraz, jeśli Pan pozwoli, mam wiele spraw do załatwienia.";
			}
			else
			{	
				dialog.text = "Dziękuję za wzorowy eskortaż, Kapitanie. Cieszę się, że nie napotkaliśmy żadnych incydentów. Oto twoja zapłata - czterdzieści dublonów w pełni.";
				link.l1 = "Z przyjemnością robię z tobą interesy, monsieur. A teraz, jeśli pozwolisz, mam wiele do załatwienia.";
				AddItems(pchar, "gold_dublon", 40);
				Log_info("You've received 40 doubloons");
				PlaySound("Interface\important_item.wav");
			}
			link.l1.go = "MOT_Barbie_102";
		break;
		
		case "MOT_Barbie_102":
			dialog.text = "Charles...";
			link.l1 = "Tak, Charles? Wyglądasz na zaniepokojonego. Czy coś jest nie tak?";
			link.l1.go = "MOT_Barbie_103";
			RemoveCharacterCompanion(pchar, npchar);
			npchar.lifeday = 0;
		break;
		
		case "MOT_Barbie_103":
			dialog.text = "Cóż, skoro jesteś godnym zaufania człowiekiem i znasz Fadeja... Spójrz, handel to ryzykowna sprawa, prawda?";
			link.l1 = "Jeśli tak mówisz.";
			link.l1.go = "MOT_Barbie_104";
		break;
		
		case "MOT_Barbie_104":
			dialog.text = "Udało mi się nabyć partię lin po okazyjnej cenie na Gwadelupie od... wiesz kogo. Zamierzałem szybko sprzedać je w St. Pierre i użyć uzyskanych środków na zakup kawy do odsprzedaży w Willemstad. Wydawało się to rozsądnym planem.";
			link.l1 = "Nie kwestionuję twojej uczciwości, monsieur, ale to wszystko brzmi raczej podejrzanie. Mówisz o swoim ładunku, jakby to było złoto. Tymczasem mój statek jest załadowany tymi linami i są one tanie jak barszcz.";
			link.l1.go = "MOT_Barbie_106";
		break;
		
		case "MOT_Barbie_106":
			dialog.text = "Charles, te liny są najwyższej jakości, wykonane z doskonałego konopi i tkane w fabrykach cara moskiewskiego. Służą do celów strategicznych i są wykorzystywane w takielunku okrętów wojennych. Anglicy monopolizują szlaki handlowe z Moskwą, zabraniając swobodnego handlu takimi linami. Inne narody intensywnie rywalizują, aby zabezpieczyć całość dostępnej podaży dla swoich stoczni w Europie również.";
			link.l1 = "Więc to jest przemyt?";
			link.l1.go = "MOT_Barbie_107";
		break;
		
		case "MOT_Barbie_107":
			dialog.text = "Yes. Unfortunately, I had a falling out with Santiago smugglers last year. I had nearly forgotten about it, but these individuals maintain close connections and long memories. Here's a piece of advice: avoid incensing them and reneging on deals; it's a situation you won't rectify later.";
			link.l1 = "Dziękuję, ale przemyt mnie nie interesuje.";
			link.l1.go = "MOT_Barbie_108";
		break;
		
		case "MOT_Barbie_108":
			dialog.text = "Szkoda! Uczciwy handel może przynieść ci pokaźny zysk, ale nigdy nie zgromadzisz znacznego bogactwa. Niemniej jednak, nie rozpocząłem tej dość niebezpiecznej rozmowy z tobą bez powodu. Proponuję, abyś zakupił ode mnie ładunek lin. Lokalni przemytnicy często bywają w tawernie i będą chętni kupić ten towar. Pomyśl o tym! Dziś zbierzesz znaczny zysk, nie wypływając na otwarte morze.";
			link.l1 = "Ile żądasz za ładunek?";
			link.l1.go = "MOT_Barbie_109";
		break;
		
		case "MOT_Barbie_109":
			dialog.text = " Dziesięć tysięcy pesos. To skromna suma, a odsprzedaż lin przemytnikom przyniesie znaczne zyski.";
			if (sti(pchar.Money) >= 10000)
			{
				link.l1 = "   Nigdy bym sobie nie wybaczył, gdybym przegapił taką okazję. Weź srebro i upewnij się, że towary zostaną szybko dostarczone na mój statek.";
				link.l1.go = "MOT_Barbie_ContraSoglasen";
			}
			if (sti(pchar.Money) >= 7000)
			{
				link.l2 = "To ryzykowne przedsięwzięcie, mój przyjacielu. Spotkajmy się w połowie drogi, dobrze? Przyjmę twoje liny za siedem tysięcy.";
				link.l2.go = "MOT_Barbie_ContraTorg";
			}
			link.l3 = "To znaczna suma, Monsieur. Współczuję twojej sytuacji, ale nie mogę zaakceptować takiego ryzyka.";
			link.l3.go = "MOT_Barbie_ContraOtkaz";
		break;
		
		case "MOT_Barbie_ContraSoglasen":
			dialog.text = "Moja wdzięczność, Charles! Uchroniłeś mnie przed finansowym upadkiem! Towary zostaną wysłane szybko i z najwyższą ostrożnością\nPozwól, że jako kolega kupiec udzielę Ci jednej rady: gdy już zatrudnisz porządnego skarbnika, zaopatrz się w kawę w Saint-Pierre i sprzedaj ją z zyskiem w Willemstad. Lokalni kapitaliści hojnie płacą za kolonialne towary, eksportując je do Europy z dużymi zyskami. Powodzenia w Twoich przedsięwzięciach, przyjacielu!";
			link.l1 = "Żegnaj, monsieur.";
			link.l1.go = "MOT_Barbie_ContraSoglasen_2";
			AddCharacterGoodsSimple(pchar, GOOD_ROPES, 30);
			AddMoneyToCharacter(pchar, -10000);
			Log_info("You've received 30 ropes");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "MOT_Barbie_ContraSoglasen_2":
			DialogExit();
			
			AddQuestRecord("MoneyOnTrees", "5");
			CloseQuestHeader("MoneyOnTrees");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			
			sld = CharacterFromID("SharlieBarbie");
			sld.lifeday = 0;
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "MOT_Barbie_ContraTorg":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) > 30)
			{
				notification("Skill Check Passed", SKILL_COMMERCE);
				dialog.text = "Moja wdzięczność, Charles! Uchroniłeś mnie od finansowej ruiny! Towary zostaną wysłane szybko i z najwyższą ostrożnością\nPozwól, że udzielę ci jednej rady jako kolega handlarz: gdy już zatrudnisz porządnego kwatermistrza, zakup kawę w Saint-Pierre i sprzedaj ją z zyskiem w Willemstad. Lokalne kapitały hojnie płacą za kolonialne dobra, eksportując je do Europy dla znacznych zysków. Powodzenia w przedsięwzięciach, przyjacielu!";
				link.l1 = "Żegnaj, Monsieur.";
				link.l1.go = "MOT_Barbie_ContraSoglasen_2";
				AddCharacterGoodsSimple(pchar, GOOD_ROPES, 30);
				AddMoneyToCharacter(pchar, -7000);
				Log_info("You've received 30 ropes");
				PlaySound("Interface\important_item.wav");
			}
			else
			{
				notification("Skill Check Failed (31)", SKILL_COMMERCE); 
				dialog.text = "Nie mogę, Kapitanie. Mój towar jest poważny i wymaga poważnego traktowania. Większość wolnych kapitanów nie odważy się handlować towarami strategicznymi. Niestety, negocjacje są tutaj nieuzasadnione.";
				if (sti(pchar.Money) >= 10000)
				{
					link.l1 = "Nie wybaczyłbym sobie, gdybym przegapił taką okazję. Weź srebro i upewnij się, że towary zostaną szybko dostarczone na mój statek.";
					link.l1.go = "MOT_Barbie_ContraSoglasen";
				}
				link.l2 = "To znaczna suma, Monsieur. Współczuję twemu położeniu, lecz nie mogę przyjąć takiego ryzyka.";
				link.l2.go = "MOT_Barbie_ContraOtkaz";
			}
		break;
		
		case "MOT_Barbie_ContraOtkaz":
			dialog.text = "Szkoda! Żegnaj, Kapitanie.";
			link.l1 = "";
			link.l1.go = "MOT_Barbie_ContraOtkaz_2";
		break;
		
		case "MOT_Barbie_ContraOtkaz_2":
			DialogExit();
			
			AddQuestRecord("MoneyOnTrees", "4");
			CloseQuestHeader("MoneyOnTrees");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			
			sld = CharacterFromID("SharlieBarbie");
			sld.lifeday = 0;
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		//Миниквест "Делюк"
		//Матрос Алонсо
		case "Del_Alonso":
			dialog.text = "Kłopoty, kapitanie.";
			link.l1 = "No?";
			link.l1.go = "Del_Alonso_2";
		break;
		
		case "Del_Alonso_2":
			dialog.text = "Nasz nawigator został aresztowany i zabrany do miejscowych lochów. Powiadają, że to kwestia długu.";
			link.l1 = "Co, znowu?!";
			link.l1.go = "Del_Alonso_3";
		break;
		
		case "Del_Alonso_3":
			dialog.text = "To łobuz, kapitanie.";
			link.l1 = "Co za okropne wyczucie czasu! Bez nawigatora jesteśmy tu uziemieni. Będę musiał go znowu wyciągać! Porozmawiam z komendantem...";
			link.l1.go = "Del_Alonso_4";
		break;
		
		case "Del_Alonso_4":
			dialog.text = "Pozwolisz przemówić, Kapitanie?";
			link.l1 = "Śmiało.";
			link.l1.go = "Del_Alonso_5";
		break;
		
		case "Del_Alonso_5":
			dialog.text = "Po co przechodzić przez te wszystkie trudności? Człowiek taki jak on tylko przysporzy kłopotów na statku.";
			link.l1 = "Czy mam wybór? Trudno o innych nawigatorów, więc moje opcje są dość ograniczone.";
			link.l1.go = "Del_Alonso_6";
		break;
		
		case "Del_Alonso_6":
			dialog.text = "Prawda, znakomitego nawigatora trudno znaleźć, ale jeszcze nie potrzebujesz mistrza, wystarczy kompetentny. Twoja sytuacja zmieniła się w ciągu ostatniego tygodnia, wiesz o tym, prawda? Nie musisz już przeszukiwać dna beczki, by znaleźć ludzi do swojej załogi. Teraz ludzie mówią, jak pokonałeś tego pirata i jakie masz kontakty. Załoga też jest za tobą, Kapitanie, lubimy cię.";
			link.l1 = "To uspokajające, Alonso. A co sądzi załoga o Delucu?";
			link.l1.go = "Del_Alonso_7";
		break;
		
		case "Del_Alonso_7":
			dialog.text = "Szybko się pan uczy, kapitanie. Załoga uważa, że choć to dobry oficer i traktuje nas dobrze, nie warto się nim przejmować. Niedawno duży kupiec zwolnił oficerów – może zajrzy pan do tawerny? Tam na pewno znajdzie pan kogo trzeba. A o Delucu proszę zapomnieć – takie jest zdanie ludzi.";
			link.l1 = "Dzięki za radę, Alonso. Wiedziałem, że mogę na ciebie liczyć. Wracaj na statek i obejmij wachtę, a ja zajmę się sprawą.";
			link.l1.go = "Del_Alonso_8";
		break;
		
		case "Del_Alonso_8":
			dialog.text = "Tak jest!";
			link.l1 = "...";
			link.l1.go = "Del_Alonso_9";
		break;
		
		case "Del_Alonso_9":
			DialogExit();
			SetQuestHeader("FolkeDeluc");
			AddQuestRecord("FolkeDeluc", "1");
			
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			SetFunctionLocationCondition("FortfranceJailOff_AddQuestMark", "fortfrance_prison", false);
			QuestCloseSeaExit();
			sld = CharacterFromID("Folke");
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Del_Folke_1";
			RemovePassenger(pchar, sld);
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "FortFrance_prison", "goto", "goto9");
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			pchar.questTemp.Del_Deluck = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("Del_shturman", "mercen_4", "man", "man", 5, FRANCE, 3, false, "quest"));
			GiveItem2Character(sld, "blade_03");
			EquipCharacterByItem(sld, "blade_03");
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Del_shturman";
			LAi_SetSitType(sld);
			sld.greeting = "officer_hire";
			SetSelfSkill(sld, 21, 23, 18, 33, 25);
			SetShipSkill(sld, 25, 10, 8, 6, 35, 11, 13, 25, 14);
			SetSPECIAL(sld, 7, 10, 6, 8, 7, 8, 4);
			sld.rank = 5;
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "BasicDefense");
			//sld.quest.officertype = "navigator";
			FreeSitLocator("FortFrance_tavern", "sit4");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern", "sit", "sit4");
			AddLandQuestMark(characterFromId("Del_shturman"), "questmarkmain");
		break;
		
		//Делюк
		case "Del_Folke_1":
			DelLandQuestMark(npchar);
			dialog.text = "Kap...";
			link.l1 = "Mam milion pytań, ale zadam tylko jedno: jak udało ci się narobić nowych długów, będąc przez cały ten czas ze mną i ucząc mnie żeglarstwa!";
			link.l1.go = "Del_Folke_2";
		break;
		
		case "Del_Folke_2":
			dialog.text = "Wstyd mi to przyznać, Kapitanie, ale pożyczałem od różnych wierzycieli na długo zanim dołączyłem do twojej załogi. Mój plan był taki, żeby się ukryć i pracować na twoim statku, dopóki nie zarobię wystarczająco, aby spłacić wszystkie moje długi. Ale popełniłem błąd, zostawiając statek tutaj, aby zaangażować się z pewną kobietą tutaj, w St. Pierre, a żołnierze pojmali mnie tuż pod jej nosem. Nie narobiłem sobie żadnych nowych długów na Martynice, odkąd zapłaciłeś za mój ostatni, przysięgam!";
			link.l1 = "Jesteś idiotą, Deluc, i zrobiłeś ze mnie pośmiewisko w St. Pierre!";
			link.l1.go = "Del_Folke_3a";
			link.l2 = "Imponujące, Folke. Dzięki za anegdotę.";
			link.l2.go = "Del_Folke_3b";
		break;
		
		case "Del_Folke_3a":
			AddComplexSelfExpToScill(10, 10, 10, 10);
			dialog.text = "Co zrobisz, Kapitanie? Czy możesz mnie znów wyciągnąć z tarapatów? Znalezienie nowego nawigatora nie będzie łatwe, wiesz...";
			link.l1 = "Zostań na miejscu na razie. Podejmę decyzję. Może odwiedzę bankiera ponownie.";
			link.l1.go = "Del_Folke_4";
		break;
		
		case "Del_Folke_3b":
			AddCharacterExpToSkill(pchar, "Sailing", 10);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 10);//торговля
			dialog.text = "Co zrobisz, kapitanie? Czy możesz mnie znów wyciągnąć z tarapatów? Znalezienie nowego nawigatora nie będzie łatwe, wiesz...";
			link.l1 = "Zostań tutaj na razie. Podejmę decyzję. Może odwiedzę bankiera ponownie.";
			link.l1.go = "Del_Folke_4";
		break;
		
		case "Del_Folke_4":
			dialog.text = "To nie tak, że mam dokąd pójść...";
			link.l1 = "... ";
			link.l1.go = "Del_Folke_5";
		break;
		
		case "Del_Folke_5":
			DialogExit();
			
			pchar.questTemp.Del_Rostovshik = true;
			LAi_CharacterDisableDialog(npchar);
			AddLandQuestMark(characterFromId("FortFrance_usurer"), "questmarkmain");
		break;
		
		case "Del_Folke_10":
			dialog.text = "Kapitanie, dziękuję. Spłaciłeś moje długi, ale teraz jestem ci winien jeszcze większy dług - moje życie. I jestem za to naprawdę wdzięczny! Zapewniam cię, nie znajdziesz bardziej lojalnego człowieka nigdzie na tym świecie!";
			link.l1 = "Przypuszczam, że niektóre długi można spłacić tylko zaciągając inne. Wracajmy do pracy, Folke. Na morzu jest wiele do zrobienia.";
			link.l1.go = "Del_Folke_11a";
			link.l2 = "Nie zapomnij o tym, Deluc. Następnym razem po prostu cię zastrzelę.";
			link.l2.go = "Del_Folke_11b";
			
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			QuestOpenSeaExit()
			sld = CharacterFromID("Del_shturman");
			sld.lifeday = 0;
			
			sld = CharacterFromID("Del_Ohranik");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload3", "none", "", "", "", -1);
		break;
		
		case "Del_Folke_11a":
			AddCharacterExpToSkill(pchar, "Sailing", 10);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 10);//торговля
			dialog.text = "Tak jest, Kapitanie!";
			link.l1 = "...";
			link.l1.go = "Del_Folke_12";
		break;
		
		case "Del_Folke_11b":
			AddComplexSelfExpToScill(10, 10, 10, 10);
			dialog.text = "Tak jest, kapitanie!";
			link.l1 = "...";
			link.l1.go = "Del_Folke_12";
		break;
		
		case "Del_Folke_12":
			DialogExit();
			EndQuestMovie();
			AddQuestRecord("FolkeDeluc", "3");
			CloseQuestHeader("FolkeDeluc");
			
			ChangeCharacterComplexReputation(pchar, "authority", -2);
			AddCrewMorale(Pchar, -30);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "", "", "", "", -1);
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			npchar.quest.meeting = true;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			SetCharacterPerk(npchar, "ShipEscape");
			npchar.location = "None";
			npchar.Dialog.CurrentNode = "hired";
			npchar.Payment = true;
			SetCharacterPerk(npchar, "ByWorker");
			DeleteAttribute(npchar, "CompanionDisable");
		break;
		
		//Штурман из таверны. Стандартный диалог, но с некоторыми изменениями (обучение найма для новичков)
		case "Del_shturman":
			dialog.text = "Czy potrzebujesz oficera, kapitanie?";
    		Link.l1 = "Oficer? A w czym jesteś dobry?";
    		Link.l1.go = "Del_Node_2";
			Link.l2 = "Nie, mam pełny zestaw.";
			Link.l2.go = "Exit";
			NextDiag.TempNode = "Del_OnceAgain";
		break;		
		case "Del_Node_2":
			dialog.text = "Jestem najlepszym nawigatorem na tych wodach. Wciąż znam się trochę na medycynie. I jestem gotów wyświadczyć ci przysługę i służyć pod twoim dowództwem.";
			Link.l1 = "Ile chcesz?";
			Link.l1.go = "Del_price";
			Link.l2 = " A jakiego rodzaju specjalistą jesteś?";
			Link.l2.go = "Del_ShowParam_exit";
			Link.l3 = "Ach, już mam nawigatora.";
			Link.l3.go = "Exit";
		break;		
		case "Del_price":
			dialog.text = "Myślę, że możemy się zgodzić na 4000 pesos.";
			Link.l1 = "Czy to nie za wiele?";
			Link.l1.go = "Del_trade";
			Link.l2 = "Zgadzam się. Uważaj się za część załogi.";
			Link.l2.go = "Del_hire";
			Link.l3 = "Nie jesteś wart tych pieniędzy.";
			Link.l3.go = "exit";
		break;	
		case "Del_ShowParam_exit":
			NextDiag.TempNode = "Del_OnceAgain";
			NPChar.quest.meeting = true;
			DialogExit();
			
			PChar.SystemInfo.OnlyShowCharacter = true;
            LaunchCharacter(NPChar);
		break;		
		case "Del_OnceAgain":
			NextDiag.TempNode = "Del_OnceAgain";
			dialog.text = "Czy zmieniłeś zdanie, kapitanie? Zdecydowałeś, że nowy nawigator by nie zaszkodził?";
			// boal -->
			if (FindFreeRandomOfficer() > 0)
			{
                Link.l1 = "Coś w tym stylu. Ile chcesz?";
                Link.l1.go = "Del_price";
			}
			Link.l2 = "A na co cię stać?";
			Link.l2.go = "Del_ShowParam_exit";
			// boal <--
			Link.l3 = "Mam pełny zestaw. Do zobaczenia.";
			Link.l3.go = "exit";
		break;		
		case "Del_trade":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) > 25)
			{
				dialog.text = "Dobrze... Chyba mogę się zgodzić nawet na 2500 pesos. Co ty na to?";
				Link.l1 = "To już lepiej. Jesteś w środku.";
				Link.l1.go = "Del_hire";
				pchar.questTemp.Del_SniziliTsenu = true;
			}
			else
			{
				dialog.text = "Przykro mi, kapitanie, ale jestem wart dokładnie tyle, ile zażądałem. Jeśli to dla ciebie za dużo, to idź poszukaj kogoś innego.";
				Link.l1 = "Dobrze, zgadzam się. Zabiorę cię.";
				Link.l1.go = "Del_hire";				
				Link.l2 = "To właśnie zamierzam uczynić. Żegnaj.";
				Link.l2.go = "exit";
			}
		break;		
		case "Del_hire":
			if (CheckAttribute(pchar, "questTemp.Del_SniziliTsenu"))
			{
				if (sti(pchar.Money) >= 2500)
				{
					AddMoneyToCharacter(pchar, -2500);
					NextDiag.TempNode = "OnboardSoon";
					dialog.text = "Dziękuję, kapitanie. Nie pożałujesz swego wyboru.";
					Link.l1 = "Mam nadzieję.";
					Link.l1.go = "Del_Exit_hire";
					DeleteAttribute(pchar, "questTemp.Del_SniziliTsenu");
				}
				else
				{
					dialog.text = "Widzę, że masz niedostatek gotówki, kapitanie! Przykro mi, ale nie pracuję na kredyt.";
					Link.l1 = "O, diable!";
					Link.l1.go = "Exit";								
				}
			}
			else
			{
				if (sti(pchar.Money) >= 4000)
				{
					AddMoneyToCharacter(pchar, -4000);
					NextDiag.TempNode = "Del_OnboardSoon";
					dialog.text = "Dziękuję, kapitanie. Nie pożałujesz swojego wyboru.";
					Link.l1 = "Mam nadzieję, że tak.";
					Link.l1.go = "Del_Exit_hire";
				}
				else
				{
					dialog.text = "Widzę, że brak ci gotówki, kapitanie! Przykro mi, ale nie pracuję na kredyt.";
					Link.l1 = "O, diable!";
					Link.l1.go = "Exit";								
				}
			}
		break;
		case "Del_OnboardSoon":			
			NextDiag.TempNode = "Del_OnboardSoon";
			dialog.text = "Zaraz skończę swój napitek, kapitanie, i potem ruszam na statek. Nie martw się, będę tam na czas.";
			Link.l1 = "Dobrze. Jeśli się spóźnisz, każę ci szorować pokład!";
			Link.l1.go = "Exit";											
		break;
		case "Del_exit_hire":
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			npchar.Dialog.CurrentNode = "hired";
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NPChar.quest.meeting = true;
			npchar.loyality = 18;
			
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			AddCrewMorale(Pchar, 30);
			QuestOpenSeaExit();
			DelLandQuestMark(npchar);
			pchar.quest.FortfranceJailOff_AddQuestMark.over = "yes";
			if (GetCharacterIndex("FortFranceJailOff") != -1)
			{
				DelLandQuestMark(characterFromId("FortFranceJailOff"));
			}
			sld = CharacterFromID("Folke");
			LAi_CharacterDisableDialog(sld);
			DeleteAttribute(pchar, "questTemp.Del_Deluck");
			DeleteAttribute(pchar, "questTemp.Del_DeluckSvoboda");
			DeleteAttribute(pchar, "questTemp.Del_Rostovshik");
			DeleteAttribute(pchar, "questTemp.Del_Rostovshik_repeat");
			pchar.questTemp.Del_DeluckSiditTurma = true;
			AddQuestRecord("FolkeDeluc", "4");
			CloseQuestHeader("FolkeDeluc");
			DialogExit();
		break;
		
		//Квест "Травля крысы"
		//Капитан корабля Хейтер
		case "TK_Kapitan":
			dialog.text = "Dobrze, dobrze! Poddaję się, do diabła!";
			link.l1 = "Jesteś teraz moim więźniem, ale wkrótce znajdziesz się w St. Pierre, stając przed szubienicą.";
			link.l1.go = "TK_Kapitan_1";
			PChar.quest.TK_Potopil.over = "yes";
		break;
		
		case "TK_Kapitan_1":
			dialog.text = "To więc to... Skąd wiedziałeś, gdzie mnie znaleźć?";
			link.l1 = "Gubernator osobiście poinformował mnie o sytuacji.";
			link.l1.go = "TK_Kapitan_2";
		break;
		
		case "TK_Kapitan_2":
			dialog.text = "Co za dupek! Musiał się dowiedzieć o moich planach i postanowił otwarcie wkurwić mnie tuż przed swoją norą, żeby dać przykład innym załogom!";
			link.l1 = "Jeszcze jedna obelga pod adresem Jego Ekscelencji, a twoja podróż do St. Pierre będzie szybka i niezapomniana.";
			link.l1.go = "TK_Kapitan_3";
		break;
		
		case "TK_Kapitan_3":
			dialog.text = "Eh? Nie mówię o waszej ekscelencji, kamracie. Mówię o Jacquesie Dobrym\nDo diabła, plotki były prawdziwe! Barbazon zdał sobie sprawę, że staję się zagrożeniem, więc wydał mnie gubernatorowi, by trzymać mnie z dala od swojego nosa. Dlatego miałeś moje dokładne położenie - i złapałeś mnie z opuszczonymi portkami, ha ha!";
			link.l1 = "Jesteś złudny. Gubernator Martyniki nie zniżyłby się do współpracy z przywódcą piratów!";
			link.l1.go = "TK_Kapitan_4";
		break;
		
		case "TK_Kapitan_4":
			dialog.text = "Tak, jasne. Może nie bezpośrednio, ale myślę, że zawarł układ z Barbazonem. To dla niego wygodne: niebezpieczny pirat zostaje powieszony, raporty wyglądają ładnie, a 'wydatki na operację wojskową' są uzasadnione. Służyłem, wiesz? Więc wiem, jak to tam działa. A ty? Służysz w garnizonie?";
			link.l1 = "Służę mojemu krajowi, a ta rozmowa jest zakończona. Witaj w brygu.";
			link.l1.go = "TK_Kapitan_5";
		break;
		
		case "TK_Kapitan_5":
			dialog.text = "Trzymaj się, kamracie. Nie jestem Kastylijczykiem i nie wypływałem dziś na morze, by plądrować francuskich kupców. Mam zasady, do diabła! Zawrzyjmy układ, co ty na to?";
			link.l1 = "Marnujesz tylko oddech, piracie. Do ciupy z tobą.";
			link.l1.go = "TK_Kapitan_7_1";
			link.l2 = "Próbujesz uniknąć stryczka?";
			link.l2.go = "TK_Kapitan_6";
		break;
		
		case "TK_Kapitan_6":
			dialog.text = "Miałem tu solidny trop, a jeśli mnie puścisz, podzielę się z tobą. Moje życie warte jest tylko kilka tysięcy w srebrze, ale mogę ci zarobić o wiele więcej - i to bez podatków.";
			if (CheckAttribute(pchar, "questTemp.MOT_SharlyBad"))
			{
				link.l1 = "To kusząca oferta... Chociaż piractwo nie jest dokładnie moją mocną stroną.";
				link.l1.go = "TK_Kapitan_7";
			}
			else
			{
				link.l1 = "Nie jestem piratem!";
				link.l1.go = "TK_Kapitan_7";
			}
		break;
		
		case "TK_Kapitan_7":
			dialog.text = "To zależy od ciebie, kumplu. Czy chcesz być człowiekiem fortuny czy bezgroszowym kapitanem z zasadami. Jeśli chcesz prawdziwych pieniędzy i wolności, będziesz musiał spróbować wszystkiego po trochu. Chwytaj każdą okazję.";
			link.l1 = "Z pewnością masz dar do słów...";
			link.l1.go = "TK_Kapitan_8";
			link.l2 = "Ahem...  Sądzę, że zabiorę cię do St. Pierre.  Zdaje się, że to właściwa rzecz do zrobienia.";
			link.l2.go = "TK_Kapitan_7_1";
		break;
		
		case "TK_Kapitan_7_1":
			dialog.text = "Pieprz się wtedy!";
			link.l1 = "...";
			link.l1.go = "TK_Kapitan_Plen";
		break;
		
		case "TK_Kapitan_8":
			dialog.text = "Więc, mamy umowę?";
			link.l1 = "Tak. Powiedz mi, kto jest twoim przywódcą, a możesz odejść wolno.";
			link.l1.go = "TK_Kapitan_9";
		break;
		
		case "TK_Kapitan_9":
			dialog.text = "Jest taki cwany Anglik na statku Henry, bark. Skończy swoją małą podróż handlową, przywożąc towary z francuskich plantacji do Willemstad za niezły zysk. Wkrótce opuszcza Martynikę w kierunku Curaçao. To prosta robota - bez eskorty, a bark jest załadowany kosztownościami kosztem swojej obrony. Zbyt długo się ociąga, więc rozchodzą się plotki. Moja rada, kumplu? Nie krępuj się w tawernie. Kilka drinków dla miejscowych, a zdradzą ci niejedną tajemnicę.";
			link.l1 = "Dlaczego bez eskorty?";
			link.l1.go = "TK_Kapitan_10";
		break;
		
		case "TK_Kapitan_10":
			dialog.text = "Jak inaczej Anglik mógłby prowadzić swoje interesy po cichu na Curaçao? To otwarta wojna między Anglią a Niderlandami, a uzyskanie licencji handlowej to kłopot i jest kosztowne.";
			link.l1 = "Ale przecież nie ma wojny między Francją a Anglią. Jakie będą konsekwencje, jeśli zaatakuję neutralny statek?";
			link.l1.go = "TK_Kapitan_11";
		break;
		
		case "TK_Kapitan_11":
			dialog.text = "Żadne, jeśli będziesz dyskretny. Załoga na pewno będzie się chwalić twoimi wyczynami w najbliższym porcie, ale dopóki nie atakujesz regularnie angielskich ani holenderskich statków, powinieneś być w porządku. Podejdź do Henry'ego pod francuską banderą. Załaduj działa kartaczem, zmniejsz dystans, wystrzel z Czarnego, oddaj kilka salw i abordażuj tę sucz. To proste, kamracie.";
			link.l1 = "Zobaczymy, jak to będzie. Dotrzymam słowa i cię uwolnię. Nie dawaj mi powodu, by tego żałować.";
			link.l1.go = "TK_Kapitan_12";
		break;
		
		case "TK_Kapitan_12":
			dialog.text = "Nie zrobię tego. Powodzenia w łowach, kamracie.";
			link.l1 = "...";
			link.l1.go = "TK_Kapitan_Otpustil";
		break;
		
		case "TK_Kapitan_Plen":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			sld.DontRansackCaptain = true;
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = GetCharacter(NPC_GenerateCharacter("TK_Heiter2", "mercen_8", "man", "man", sti(PChar.rank), PIRATE, -1, false, "pirate"));
			sld.name = "Daniel";
			sld.lastname = "Montbars";
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			ChangeCharacterAddressGroup(sld, "My_Deck", "goto", "goto7");
			LAi_SetGroundSitType(sld);
			LAi_CharacterDisableDialog(sld);
			DoQuestCheckDelay("TK_KapitanSidit_1", 0.8);
		break;
		
		case "TK_Kapitan_Otpustil":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			sld.ShipEnemyDisable  = true;
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_SetCitizenType(sld);
			sld.lifeday = 0;
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			pchar.questTemp.TK_Otpustil = true;
			AddQuestRecord("TravlyaKrys", "4");
			
			SetTimerCondition("TK_GenrihSpawn", 0, 0, 1, false);	
		break;
		
		//Диего и Гийом за столиком по квесту "Встреча с Диего"
		case "VsD_DiegoAndErnat":
			dialog.text = "... Zajmę się twoimi problemami hazardowymi. Hej! Trzymaj się, człowieku! Albo się ogarnij, albo sam cię potrząsnę, żebyś oprzytomniał.";
			link.l1 = "";
			link.l1.go = "VsD_DiegoAndErnat_2";
			sld = CharacterFromID("GiumDyubua");
			LAi_CharacterEnableDialog(sld);
		break;
		
		case "VsD_DiegoAndErnat_2":
			DialogExit();
			StartInstantDialogNoType("GiumDyubua", "VsD_DiegoAndErnat_3", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "VsD_DiegoAndErnat_3":
			dialog.text = "Panie, przepraszam, ale jesteś trochę kłopotliwy.";
			link.l1 = "Tak, oczywiście. Życzę miłego dnia, panowie.";
			link.l1.go = "VsD_DiegoAndErnat_4";
		break;
		
		case "VsD_DiegoAndErnat_4":
			DialogExit();
			sld = CharacterFromID("Diego");
			LAi_CharacterDisableDialog(sld);
			sld = CharacterFromID("GiumDyubua");
			LAi_CharacterDisableDialog(sld);
		break;
		
		//Гийом Дюбуа по квесту "Встреча с Диего"
		case "VsD_GiumDyubua":
			dialog.text = "Kapitanie de Maure! Czekaj!";
			link.l1 = "Tak, poruczniku?";
			link.l1.go = "VsD_GiumDyubua_2";
			DelLandQuestMark(npchar);
		break;
		
		case "VsD_GiumDyubua_2":
			dialog.text = "Ledwo mogłem za tobą nadążyć. Był... drobny problem, Kapitanie. Co za bałagan!";
			link.l1 = "Weź oddech i uspokój się, proszę.";
			link.l1.go = "VsD_GiumDyubua_3";
		break;
		
		case "VsD_GiumDyubua_3":
			dialog.text = "Dobrze, dobrze. Słuchaj, czy po załadowaniu dział, jest jeszcze miejsce w ładowni?";
			link.l1 = "Jestem wciąż nowy w tym, więc nie jestem całkiem pewien, ale zakładam, że powinno być.";
			link.l1.go = "VsD_GiumDyubua_4";
		break;
		
		case "VsD_GiumDyubua_4":
			dialog.text = "Doskonale! Dowództwo chce wesprzeć operację w Porto Bello na wszelkie możliwe sposoby, więc zamówili dodatkowe dwieście beczek prochu do dostarczenia na Wojowniczy. Może się wydawać, że to niewiele, ale kilka dodatkowych salw może przechylić szalę bitwy!";
			link.l1 = "Bardzo dobrze, poruczniku. Jestem gotów zrobić swoją część. Ładuj proch - wcale mi to nie przeszkadza.";
			link.l1.go = "VsD_GiumDyubua_5";
		break;
		
		case "VsD_GiumDyubua_5":
			dialog.text = "Dziękuję, Kapitanie. Zaraz poinformuję naszą załogę ładującą. Na szczęście, jeszcze nie skończyli z '"+PChar.Ship.Name+"jeszcze. Powodzenia na twojej misji!";
			link.l1 = "Dzięki, chociaż jak dotąd było dość chaotycznie. Żegnaj, poruczniku.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("VsD_GoToCity");
		break;
		
		//Фульк или Алонсо по квесту "Встреча с Диего"
		case "VsD_FolkeAlonso":
			dialog.text = "Jezu, Kapitanie! Dzięki niebiosom, że nic ci się nie stało!";
			link.l1 = "Co się, do cholery, stało?! Co się stało z moim statkiem?!";
			link.l1.go = "VsD_FolkeAlonso_2";
		break;
		
		case "VsD_FolkeAlonso_2":
			dialog.text = "Nie wiem, kapitanie! Po prostu żegnałem się z miejscową kobietą, którą niedawno poznałem... O cholera! Eugenie!";
			link.l1 = "Nie żyje, "+npchar.name+" Przepraszam, ale musimy się skupić i sprawdzić, czy ktoś z naszej załogi nie ucierpiał.";
			link.l1.go = "VsD_FolkeAlonso_3";
		break;
		
		case "VsD_FolkeAlonso_3":
			dialog.text = "Ledwie się znaliśmy... Aaah! Cholera! Meldunek, Kapitanie: większość załogi była na lądzie, gdy doszło do eksplozji - na szczęście. Chłopcy korzystali z przepustki na ląd przed naszą następną wielką wyprawą. Ale straż na okręcie... Obawiam się, że nie ma ocalałych. Rozejrzyj się tylko! Odłamki zraniły lub zabiły ludzi nawet tutaj, na tym nabrzeżu! To cud, że dwóm z nas nic się nie stało.";
			link.l1 = "Co z okrętem? Czy wszystko z nią w porządku?!";
			link.l1.go = "VsD_FolkeAlonso_4";
		break;
		
		case "VsD_FolkeAlonso_4":
			dialog.text = "Czy ona?! Moje przeprosiny, Kapitanie. Trudno powiedzieć na pewno, ale wygląda na to, że eksplozja miała miejsce na górnym pokładzie, a nie poniżej. Nie widzę żadnych aktywnych pożarów i wygląda na to, że uniknęliśmy większych uszkodzeń.";
			link.l1 = "... ";
			link.l1.go = "VsD_FolkeAlonso_5";
			sld = GetCharacter(CreateCharacterClone(CharacterFromID("PortPaxAmmoOff"), 0));
			sld.id = "PortPaxAmmoOff_clone";
			LAi_LoginInCaptureTown(sld, true);
			ChangeCharacterAddressGroup(sld, "PortPax_town", "quest", "quest1");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		break;
		
		case "VsD_FolkeAlonso_5":
			DialogExit();
			LAi_SetStayType(pchar);
			sld = CharacterFromID("PortPaxAmmoOff_clone");
			sld.dialog.filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "VsD_Komendant";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 3, 0);
		break;
		
		case "VsD_Komendant":
			dialog.text = "Co do diabła, kapitanie?!";
			link.l1 = "Zadaję to samo pytanie, pułkowniku!";
			link.l1.go = "VsD_Komendant_1";
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				LAi_SetActorType(sld);
				LAi_ActorGoToLocator(sld, "reload", "reload1", "", -1);
			}
		break;
		
		case "VsD_Komendant_1":
			dialog.text = "Uważaj na siebie, de Maure! Przyjąłeś tę robotę od Marynarki, zabrałeś ciężkie działa - własność Korony, o strategicznym znaczeniu! Rozumiesz, jakie znaczenie mają te działa dla całej operacji?! Twoje zaniedbanie naraziło prawie czterystu ludzi i francuski okręt wojenny na niebezpieczeństwo! Grozi ci tu proces za zdradę!";
			link.l1 = "Spokój, pułkowniku! Cudownie, wygląda na to, że mój statek przetrwał, a twój cenny ładunek jest w większości nienaruszony... w większości.";
			link.l1.go = "VsD_Komendant_2";
		break;
		
		case "VsD_Komendant_2":
			dialog.text = "Co masz na myśli, mówiąc głównie?!";
			link.l1 = "Nie mogę zagwarantować, że dwieście miar prochu, załadowanych w ostatniej chwili przez jednego z twoich poruczników, nie zostało uszkodzonych. Miały być załadowane na końcu i to prawdopodobnie one wybuchły.";
			link.l1.go = "VsD_Komendant_3";
		break;
		
		case "VsD_Komendant_3":
			dialog.text = "Co to za bzdury, Charles? Jaki porucznik? Jaki proch strzelniczy? Nie wydawałem takiego rozkazu!";
			link.l1 = "Ten porucznik musiał być z waszego garnizonu. Nie pytałem o jego imię, ale wydawało się, że jest świadomy operacji.";
			link.l1.go = "VsD_Komendant_4";
		break;
		
		case "VsD_Komendant_4":
			dialog.text = "Ach, cholera! Wygląda na to, że Kastylijczycy też skłonni są do brudnych zagrywek... Zajmę się tą niefortunną sytuacją, Kapitanie. Ty jednak wciąż masz zadanie do wykonania: czy jesteś pewien, że twój statek jest gotowy do żeglugi?";
			link.l1 = "Jest na wodzie, ale zdecydowanie potrzebuje poważnych napraw.";
			link.l1.go = "VsD_Komendant_5";
			SetMusic("classic_fra_music_day");
		break;
		
		case "VsD_Komendant_5":
			dialog.text = "Nie ma na to czasu, Kapitanie. Wypływaj natychmiast i wykonaj misję. Stawka jest zbyt wysoka, by zwlekać.";
			link.l1 = "Czyż nie możemy mieć choćby jednego dnia, na miłość boską? Miejscowa stocznia mogłaby dokonać niezbędnych napraw! A co z moją załogą?! Z pewnością są ranni!";
			link.l1.go = "VsD_Komendant_6";
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				LAi_SetOfficerType(sld);
				sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
				sld.Dialog.CurrentNode = "Tichingitu_officer";
			}
			if (GetCharacterIndex("Folke") != -1 && CheckPassengerInCharacter(pchar, "Folke"))
			{
				sld = CharacterFromID("Folke");
				ChangeCharacterAddressGroup(sld, "none", "", "");
				sld.Dialog.Filename = "Enc_Officer_dialog.c";
				sld.Dialog.CurrentNode = "hired";
			}
			else
			{
				sld = CharacterFromID("Alonso");
				ChangeCharacterAddressGroup(sld, "none", "", "");
			}
		break;
		
		case "VsD_Komendant_6":
			dialog.text = "Jeśli nie zauważyliście, stocznia stoi w płomieniach. Wciąż ustalamy, czy to było celowe działanie, czy skutek eksplozji. Mogę jedynie obiecać, że wasi ranni otrzymają opiekę medyczną, a Korona pokryje koszty pochówku zmarłych.";
			link.l1 = "Jesteś poważny? To najlepsze, co możesz zaoferować?";
			link.l1.go = "VsD_Komendant_7";
			sld = CharacterFromID("VsD_Tsyganka");
			ChangeCharacterAddressGroup(sld, "PortPax_town", "reload", "reload5_back");
			LAi_CharacterEnableDialog(sld);
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		break;
		
		case "VsD_Komendant_7":
			dialog.text = "Kapitanie, Francja pilnie potrzebuje Twojej pomocy. Dostarczę Ci deski, a jeśli rozegrasz to sprytnie, Twój statek będzie prawie w pełni naprawiony, zanim dotrzesz na Jamajkę.";
			link.l1 = "Przepraszam, ale jakie deski? I dlaczego Jamajka?";
			link.l1.go = "VsD_Komendant_8";
			pchar.ship.HP = sti(pchar.ship.HP) / 2;
			pchar.Ship.Crew.Quantity = sti(pchar.ship.Crew.Quantity) - sti(pchar.ship.Crew.Quantity) / 7;
			AddCharacterGoodsSimple(pchar, GOOD_PLANKS, 100);
		break;
		
		case "VsD_Komendant_8":
			dialog.text = "Twoja załoga może przeprowadzić awaryjne naprawy na morzu przy użyciu desek - podstawowego materiału naprawczego. A Jamajka jest dość blisko jednej z tras, które możesz obrać do Porto Bello. Jeśli nie zmarnujesz czasu, możesz tam dokończyć naprawy i zrekrutować pełną załogę.";
			link.l1 = "Bardzo dobrze, zatem. Wypływam natychmiast, pułkowniku.";
			link.l1.go = "VsD_Komendant_9";
			
			sld = CharacterFromID("PortRoyal_shipyarder");
			sld.TrialDelQuestMark = true;
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("PortRoyal", false);
		break;
		
		case "VsD_Komendant_9":
			DialogExit();
			LAi_SetStayType(pchar);
			
			sld = CharacterFromID("VsD_Tsyganka");
			sld.dialog.filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "VsD_Tsyganka";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 3, 0);
			
			sld = CharacterFromID("PortPaxAmmoOff_clone");
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "gate_back", "none", "", "", "", -1);
		break;
		
		case "VsD_Tsyganka":
			dialog.text = "Po co ten pośpiech, kochana?";
			link.l1 = "Kochanie, nie mam teraz na to czasu. Nie widzisz, co się dzieje?";
			link.l1.go = "VsD_Tsyganka_1";
		break;
		
		case "VsD_Tsyganka_1":
			dialog.text = "Och, obecne kłopoty są straszne, ale widzę po twojej dłoni, że na horyzoncie pojawiają się kolejne.";
			link.l1 = "Każdy może to zobaczyć, nawet nie patrząc na moją rękę, która, dodam, jest w rękawiczce. Dobrze, pogramy: jaka jest cena za uniknięcie katastrofy w dzisiejszych czasach?";
			link.l1.go = "VsD_Tsyganka_2";
		break;
		
		case "VsD_Tsyganka_2":
			dialog.text = "Nie mam takiej mocy, przystojniaku. A nawet gdybym miał, nie byłoby mnie na to stać. Ale mogę ci pomóc... z twoim statkiem. Dziewczyna jest w opłakanym stanie, drogi mój.";
			link.l1 = "Nie wiedziałem, że wasza cygańska brać ma ambicje w stolarstwie.";
			link.l1.go = "VsD_Tsyganka_3";
			
			for (i=3; i<=8; i++)
			{				
				sld = CharacterFromID("VsD_MirnyeMan_"+i);
				LAi_SetCitizenType(sld);
			}
			for (i=3; i<=6; i++)
			{				
				sld = CharacterFromID("VsD_MirnyeWoman_"+i);
				LAi_SetCitizenType(sld);
			}
			for (i=1; i<=6; i++)
			{				
				sld = CharacterFromID("VsD_Sold_"+i);
				LAi_SetCitizenType(sld);
			}
			//Возвращаем всё обратно
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			bDisableCharacterMenu = false;
			SetLocationCapturedState("PortPax_town", false);
			Locations[FindLocation("PortPax_town")].locators_radius.quest.quest1 = 1.0;
			Locations[FindLocation("PortPax_town")].locators_radius.patrol.patrol14 = 0.5;
			LocatorReloadEnterDisable("PortPax_ExitTown", "reload2_back", false);
			LocatorReloadEnterDisable("PortPax_ExitTown", "reload1_back", false);
			LAi_LocationFightDisable(&Locations[FindLocation("PortPax_town")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("PortPax_Fort")], false);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("VsD_Guard_"+i);
				sld.lifeday = 0;
			}
			//Диего исчезает
			sld = CharacterFromID("Diego");
			LAi_CharacterEnableDialog(sld);
			sld.location = "None";
			//Верфь закрывается
			LocatorReloadEnterDisable("PortPax_Town", "reload5_back", true);
			SetTimerCondition("VsD_VerfOtkryt", 0, 0, 7, false);
			//Труп предателя в джунглях
			PChar.quest.VsD_TrupPredatelya.win_condition.l1 = "location";
			PChar.quest.VsD_TrupPredatelya.win_condition.l1.location = "PortPax_ExitTown";
			PChar.quest.VsD_TrupPredatelya.win_condition = "VsD_TrupPredatelya";
			SetTimerCondition("VsD_TrupPredatelya_3", 0, 0, 60, false);
		break;
		
		case "VsD_Tsyganka_3":
			dialog.text = "Ty, kochanieńki, ledwo jesteś cieślą. Myślisz, że same deski naprawią statek? Tylko będą cię obciążać, chyba że masz mistrza cieśli...";
			link.l1 = "Albo?";
			link.l1.go = "VsD_Tsyganka_4";
		break;
		
		case "VsD_Tsyganka_4":
			dialog.text = "Jest potężny amulet, czczony przez miejscowych. Drewno ugina się pod jego wolą, a nawet ci, którzy nie znają się na stolarstwie, stają się biegli, gdy go noszą. To twój za jedyne tysiąc peso, drogi.";
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = "Bardzo dobrze, mamy umowę. Potrzebuję wszelkiej pomocy, jaką mogę uzyskać.";
				link.l1.go = "VsD_Tsyganka_Da";
			}
			link.l2 = "Nie mam czasu na twoje czary. Idź w pokoju, wiedźmo, i nie wtrącaj się.";
			link.l2.go = "VsD_Tsyganka_Net";
			npchar.lifeday = 0;
		break;
		
		case "VsD_Tsyganka_Net":
			DialogExit();
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Trial", "7_1");
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "VsD_Tsyganka_Da":
			DialogExit();
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Trial", "7_1");
			AddCharacterExpToSkill(pchar, "Repair", 20);
			AddMoneyToCharacter(pchar, -1000);
			GiveItem2Character(PChar, "obereg_1");
			Log_info("You have received Amulet 'Teredo'");
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Słuchaj no, jestem praworządnym obywatelem tego miasta. Muszę cię poprosić, byś nie chodził z odsłoniętą bronią jak jakiś rabuś.","Proszę pana, prawo jest jasne, że mężczyźni nie mogą chodzić z dobytymi broniami w obrębie murów miasta.");
			link.l1 = LinkRandPhrase("Dobrze.","Dobrze.","Jak sobie życzysz...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			if (npchar.id == "GigoloMan") NextDiag.TempNode = "GigoloMan";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

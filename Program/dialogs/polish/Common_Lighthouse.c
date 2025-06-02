#include "DIALOGS\%language%\Rumours\Common_rumours.c" //Jason
// Jason общий диалог смотрителей маяков
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Lighthouse\" + NPChar.City + "_Lighthouse.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
    int iTest, iTemp;
	string sTemp;
	bool ok;
    iTest = FindColony(NPChar.City); // город
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("Alarm został podniesiony w mieście. Wygląda na to, że nadszedł czas, abym też wziął do ręki broń...","Czy przypadkiem strażnicy miejski nie gonią za tobą?","Nie znajdziesz tu schronienia, ale możesz znaleźć kilka cali zimnej stali pod swoim żebrem!"),LinkRandPhrase("Czego chcesz, "+GetSexPhrase("łotrze","łobuzie")+"?! Strażnicy są na twoim tropie, daleko nie uciekniesz, "+GetSexPhrase("brudny piracie","cwaniaro")+"!",""+GetSexPhrase("Brudny","Brudny")+" morderca! Strażnicy!!!","Nie boję się ciebie, "+GetSexPhrase("ty draniu","paskudo")+"! Wkrótce będziesz wisieć w naszym forcie, nie uciekniesz daleko..."));
				link.l1 = PCharRepPhrase(RandPhraseSimple("Widzę, że jesteś zmęczony życiem...","Wygląda na to, że nie ma tu pokojowych ludzi w "+XI_ConvertString("Colony"+npchar.city+"Gen")+", wszyscy chcą być bohaterem!"),RandPhraseSimple("Idź do diabła!","Heh, to będą ostatnie sekundy twojego życia..."));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			//belamour legendary edtion карибские нравы
			if(npchar.quest.meeting != "0" && CheckAttribute(npchar, "quest.trial_usurer"))
			{
				dialog.text = "Co cię tym razem przywodzi do mnie?";
				link.l1 = "Wierzę, że znasz pewnego dżentelmena o imieniu Gerard LeCroix? Powinien zostawić dla mnie nagrodę...";
				link.l1.go = "Trial";
				DelLandQuestMark(npchar);
				break;
			}
			// <-- legendary edition
			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple("Dzień dobry, marynarzu! Nazywam się "+GetFullName(npchar)+", a ja jestem stróżem tej latarni morskiej. Jaki wiatr cię tutaj przyniósł?","Cześć! Minęło trochę czasu od kiedy ostatni raz widziałem nowe twarze przy moim latarni morskiej... Pozwól, że się przedstawię - "+GetFullName(npchar)+", a ta latarnia morska to mój dom i moja praca. Co mogę dla ciebie zrobić?");
				link.l1 = "Witaj, "+npchar.name+"! Nazywam się "+GetFullName(pchar)+", jestem kapitanem statku. Spacerowałem po tej wspaniałej zatoce i postanowiłem zajrzeć, kto tu mieszka.";
				link.l1.go = "Lightman_meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "O, mój stary przyjacielu, kapitanie "+GetFullName(pchar)+"! Wchodź, wchodź! Co cię tym razem tutaj sprowadza?";
				link.l1 = "Witaj, stary solony! Czy nie wylasz tu w samotności w swoim latarni morskiej?";
				link.l1.go = "Lightman_talk";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "Lightman_meeting":
			dialog.text = "Teraz wiesz. Kiedyś byłem marynarzem, tak jak ty, ale dawno temu ostatni raz postawiłem nogę na pokładzie statku. Teraz ta latarnia morska jest pod moją opieką, a ja także sprzedaję trochę rzeczy...";
			link.l1 = "A co dokładnie sprzedajesz?";
			link.l1.go = "trade_info";
			NextDiag.TempNode = "First time";
		break;
		
		case "Lightman_talk":
			dialog.text = "Co cię tym razem tu przyniosło?";
			link.l1 = RandPhraseSimple("Czy możesz mi powiedzieć, czy coś interesującego ostatnio wydarzyło się w twojej kolonii?","Nie byłem na lądzie od dłuższego czasu... Co tu się dzieje?");
			link.l1.go = "rumours_lighthouse";
			link.l2 = "Zobaczmy, co masz na sprzedaż.";
			link.l2.go = "Trade_lighthouse";
			if (CheckAttribute(npchar, "artefact"))
			{
				if (CheckAttribute(npchar, "quest.art"))
				{
					link.l3 = "Więc, "+npchar.name+", czy mój amulet już dotarł?";
					link.l3.go = "Trade_artefact_3";
				}
				else
				{
					link.l3 = ""+npchar.name+", chcę u ciebie zamówić amulet.";
					link.l3.go = "Trade_artefact_1";
				}
				// калеуче
				if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "amulet" && !CheckAttribute(npchar, "quest.Caleuche"))
				{
					link.l5 = "Słuchaj, "+npchar.name+", Wiem, że zajmujesz się dostarczaniem amuletów na zamówienie. Więc na pewno dużo o nich wiesz. Spójrz, proszę, na tę małą rzecz - co możesz mi o niej powiedzieć?";
					link.l5.go = "Caleuche";
				}
				if (npchar.id == pchar.questTemp.Caleuche.Amuletmaster && CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "mayak")
				{
					link.l5 = "Przyjacielu, znów jestem tutaj, aby zapytać cię o te dziwne amulety";
					link.l5.go = "Caleuche_9";
				}
			}
			link.l4 = "Jest coś, o co chciałem cię zapytać...";
			link.l4.go = "quests";
			link.l9 = "Właśnie rzuciłem okiem...";
			link.l9.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "trade_info":
			dialog.text = "Czasami idę na brzeg i zbieram muszle, nieopodal jest jedno ładne miejsce, więc zawsze możesz ode mnie kupić perły. Każda burza przynosi bursztyn, też go sprzedaję, choć będzie cię to dużo kosztować.\nCzasami fale przynoszą wszelkiego rodzaju interesujące drobiazgi z zatopionych statków, a moi starzy kumple przynoszą mi specjalne przedmioty. Interesują mnie zaklęte amulety, mędrcy płacą za nie dobrą monetą.\nRównież oferuję broń przy specjalnych okazjach, nie pytaj mnie skąd ją mam. Miejscowy handlowiec kupuje ode mnie całe badziewie, dobre rzeczy sprzedaję sam po ich naprawie i czyszczeniu.\nInteresuje mnie rum. Nie mówię o moczach, które serwują w lokalnej karczmie za dwa peso za kubek. Mówię o prawdziwym butelkowanym rumie jamajskim. Leczy i ożywia ludzi. Zapłacę dziesięć razy więcej za każdą butelkę, którą przyniesiesz. Pomyśl o tym.";
			link.l1 = "Słuchaj, "+npchar.name+", powiedziałeś, że masz starych marynarskich przyjaciół, którzy przynoszą ci zaczarowane amulety. Czy mogę zamówić u ciebie pewien amulet? Zapłacę za to sowicie.";
			link.l1.go = "Trade_artefact";
		break;
		
		case "Trade_lighthouse":
			//иногда продает корабельные товары // Addon-2016 Jason
			npchar.quest.goods = GOOD_COFFEE + hrand(sti(GOOD_PAPRIKA - GOOD_COFFEE));
			npchar.quest.goodsqty = 50+hrand(100);
			if (sti(npchar.quest.goods) == GOOD_EBONY || sti(npchar.quest.goods) == GOOD_MAHOGANY) npchar.quest.goodsqty = 25+hrand(50);
			npchar.quest.goodsprice = makeint(sti(Goods[sti(npchar.quest.goods)].Cost)/4);//цена единицы товара
			npchar.quest.goodscost = sti(npchar.quest.goodsprice)*sti(npchar.quest.goodsqty);//стоимость товара
			ok = (!CheckAttribute(npchar, "goods_date")) || (GetNpcQuestPastDayParam(npchar, "goods_date") >= 10)
			if (hrand(4) == 1 && makeint(GetCharacterFreeSpace(pchar, sti(npchar.quest.goods))) > sti(npchar.quest.goodsqty) && sti(pchar.money) >= sti(npchar.quest.goodscost) && ok)
			{
				dialog.text = "Kapitanie, niedawno na brzeg wyrzuciło ilość towarów - "+GetGoodsNameAlt(sti(npchar.quest.goods))+". Niektóre części zostały zniszczone przez słoną wodę, ale "+FindRussianQtyString(sti(npchar.quest.goodsqty))+" Udało mi się zachować w świetnym stanie. Chcesz kupić trochę? Przydam je tanio, tylko za "+FindRussianMoneyString(sti(npchar.quest.goodsprice))+" za jednostkę.";
				link.l1 = "Nie. Pokaż mi swoje najnowsze zdobycze.";
				link.l1.go = "Trade_lighthouse_double";
				link.l2 = "Hm... Szczerą ofertę, zgadzam się. Myślę, że mógłbym to odsprzedać z zyskiem. Zobaczmy... To wyniesie "+FindRussianMoneyString(sti(npchar.quest.goodscost))+". Czy to prawda?";
				link.l2.go = "Trade_goods";
				SaveCurrentNpcQuestDateParam(npchar, "goods_date");
			}
			else
			{
				DialogExit();
				if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
				{
					GiveItemToTrader(npchar);
					SaveCurrentNpcQuestDateParam(npchar, "trade_date");
				}
				LaunchItemsTrade(npchar, 0);
			}
		break;
		
		case "Trade_lighthouse_double":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
		case "Trade_goods":
			AddCharacterGoods(pchar, sti(npchar.quest.goods), sti(npchar.quest.goodsqty));
			AddMoneyToCharacter(pchar, -sti(npchar.quest.goodscost));
			AddMoneyToCharacter(npchar, sti(npchar.quest.goodscost));
			dialog.text = "Masz rację, kapitanie. Wspaniały interes! Obydwoje na tym zyskaliśmy...";
			link.l1 = "Dobrze, więc. Wyślę marynarzy, aby zabrali ładunek do mojego statku. Teraz pokaż mi, co zgromadziłeś na sprzedaż.";
			link.l1.go = "Trade_lighthouse_double";
		break;
//------------------------------------------------заказ артефактов------------------------------------------------
		case "Trade_artefact":
			if (CheckAttribute(npchar, "artefact")) // Addon-2016 Jason за дублоны
			{
				dialog.text = "Cóż, nie wszystkie, ale niektóre drobiazgi są przynoszone częściej niż inne, więc myślę, że mogę ci pomóc. Ale ostrzegam cię: wszystkie amulety zamówione w ten sposób będą kosztować cię 100 dublonów. Powinieneś to zrozumieć...";
				link.l1 = "Cena nie jest problemem. Jakie amulety możesz dostarczyć?";
				link.l1.go = "Trade_artefact_1";
				link.l2 = "Pff! Za takie pieniądze można by kupić statek. To zbyt drogie. Chyba poradzę sobie sam...";
				link.l2.go = "exit_artefact";
			}
			else
			{
				dialog.text = "Nie, kapitanie. Takie rzeczy można znaleźć tylko przez przypadek, więc nie można ich zamawiać z góry. A także musiałbyś na nie czekać trochę krócej niż na zawsze...";
				link.l1 = "No cóż, jeśli tak jest, nic nie można zrobić.";
				link.l1.go = "exit_artefact";
			}
		break;
		
		case "exit_artefact":
			if (CheckAttribute(npchar, "artefact")) dialog.text = "Jak sobie życzysz. Przyjdź do mnie, jeśli zmienisz zdanie.";
			else dialog.text = "Czy chciałbyś zobaczyć, co mam dzisiaj na sprzedaż, kapitanie? Jeśli nie znajdziesz niczego godnego, wróć wkrótce - mogę mieć coś innego na sprzedaż.";
			// belamour legendary edition карибские нравы -->
			if(CheckAttribute(npchar, "quest.trial_usurer"))
			{
				link.l1 = "Wszystko to, oczywiście, jest dobre, ale oto co chciałem zapytać - przypuszczam, że znasz pewnego pana o imieniu Gerard Lecroix? Powinien zostawić dla mnie nagrodę...";
				link.l1.go = "Trial";
				DelLandQuestMark(npchar);
				break;
			}
			// <-- legendary edition
			link.l1 = "Pokaż mi swoje przedmioty.";
			link.l1.go = "Trade_lighthouse";
			link.l2 = "Po prostu powiedz mi, co ciekawego wydarzyło się ostatnio w twojej kolonii?";
			link.l2.go = "rumours_lighthouse";
			link.l3 = "Handel to handel, ale chciałem zapytać o coś.";
			link.l3.go = "quests";
			link.l4 = "Miłego dnia, "+npchar.name+"! Miło było cię poznać! Wpadnę kiedyś w innym czasie...";
			link.l4.go = "exit";
		break;
		
		case "Trade_artefact_1":
			dialog.text = "Wybierz swoje.";
			iTemp = 1;
			string sArt;
			if (CheckAttribute(npchar, "artefact.indian")) sArt = "indian_";
			if (CheckAttribute(npchar, "artefact.amulet")) sArt = "amulet_";
			if (CheckAttribute(npchar, "artefact.obereg")) sArt = "obereg_";
			for (i=11; i>=1; i--)
			{
				sTemp = "l"+iTemp;
				link.(sTemp) = XI_ConvertString(sArt+i);
				link.(sTemp).go = sArt+i;
				iTemp++;
			}
			link.l12 = "Niestety, nic z tej listy mnie na razie nie interesuje.";
			link.l12.go = "exit";
		break;
		
		//группа indian
		case "indian_1":
			dialog.text = "Lalka voodoo? Lubisz broń palną? Dobrze...";
			link.l1 = "Kiedy powinienem wrócić po odebranie mojego zamówienia?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_1";
		break;
		
		case "indian_2":
			dialog.text = "Tester prochu strzelniczego? Celna strzelba to klucz do sukcesu w każdej potyczce. Miło...";
			link.l1 = "Kiedy powinienem wrócić, aby odebrać moje zamówienie?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_2";
		break;
		
		case "indian_3":
			dialog.text = "Rytualny nóż? Lubisz siekać swoich wrogów mocnymi cięciami ciężkiego szpady? To dla ciebie, w takim razie. Dobrze... ";
			link.l1 = "Kiedy powinienem wrócić, aby odebrać moje zamówienie?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_3";
		break;
		
		case "indian_4":
			dialog.text = "Halabarda? Uderzenie z góry ogromnym toporem zgniecie każdego wroga! Dobrze...";
			link.l1 = "Kiedy powinienem wrócić po moje zamówienie?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_4";
		break;
		
		case "indian_5":
			dialog.text = "Tsantsa? Nawet najbardziej zuchwały pirat może się tego przestraszyć. Dobrze...";
			link.l1 = "Kiedy powinienem wrócić po moje zamówienie?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_5";
		break;
		
		case "indian_6":
			dialog.text = "Rafa koralowa? Kartacz z twoich dział poleci prosto w cel! Dobrze...";
			link.l1 = "Kiedy powinienem wrócić po moje zamówienie?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_6";
		break;
		
		case "indian_7":
			dialog.text = "Garbacz? Wytrwałość to najlepszy przyjaciel wojownika. Dobrze...";
			link.l1 = "Kiedy powinienem wrócić po odebranie mojego zamówienia?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_7";
		break;
		
		case "indian_8":
			dialog.text = "Xiuhtecuhtli? Niech kadłub wrogiego statku zamieni się w proch! Dobrze...";
			link.l1 = "Kiedy powinienem wrócić, aby odebrać moje zamówienie?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_8";
		break;
		
		case "indian_9":
			dialog.text = "Baldo? Postaw na Baldo - a wszystkie kule armatnie polecą prosto do celu! Dobrze...";
			link.l1 = "Kiedy powinienem wrócić, aby odebrać moje zamówienie?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_9";
		break;
		
		case "indian_10":
			dialog.text = "Cascavella? Jad węża to najniebezpieczniejsza rzecz. Dobrze...";
			link.l1 = "Kiedy powinienem wrócić po odbiór mojego zamówienia?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_10";
		break;
		
		case "indian_11":
			dialog.text = "Maska Ngombo? Obniż czujność swoich wrogów, ha-ha! Dobrze...";
			link.l1 = "Kiedy powinienem wrócić, aby odebrać moje zamówienie?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_11";
		break;
		
		//группа amulet
		case "amulet_1":
			dialog.text = "Tarcza Ngombo? Jeśli nie udało ci się uniknąć kuli, ten amulet może uratować ci życie. Dobrze...";
			link.l1 = "Kiedy powinienem wrócić, aby odebrać moje zamówienie?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_1";
		break;
		
		case "amulet_2":
			dialog.text = "Euchologion? Dobra modlitwa może nawet odwrócić kulę. Dobrze...";
			link.l1 = "Kiedy powinienem wrócić, aby odebrać moje zamówienie?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_2";
		break;
		
		case "amulet_3":
			dialog.text = "Krzyż? Ten znacznie pomoże chrześcijaninowi w walce wręcz. Dobrze...";
			link.l1 = "Kiedy powinienem wrócić, aby odebrać moje zamówienie?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_3";
		break;
		
		case "amulet_4":
			dialog.text = "El Trozo? Ten uczyni śmiertelną ranę tylko zadrapaniem. Dobrze...";
			link.l1 = "Kiedy powinienem wrócić, aby odebrać moje zamówienie?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_4";
		break;
		
		case "amulet_5":
			dialog.text = "Sogbo? A niechaj działa zawsze będą gotowe do bitwy! Dobrze...";
			link.l1 = "Kiedy powinienem wrócić po moje zamówienie?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_5";
		break;
		
		case "amulet_6":
			dialog.text = "Madonna? Oblicze Najświętszej Dziewicy posiada potężne właściwości lecznicze. Dobrze...";
			link.l1 = "Kiedy powinienem wrócić po odbiór mojego zamówienia?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_6";
		break;
		
		case "amulet_7":
			dialog.text = "Święta woda? Nawet słabeusz pokropiony świętą wodą stanie się epickim bohaterem! Dobrze...";
			link.l1 = "Kiedy powinienem wrócić po odbiór mojego zamówienia?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_7";
		break;
		
		case "amulet_8":
			dialog.text = "Kotwica? A może twój statek utrzyma się na powierzchni nawet pod gradem kulek armatnich, ha-ha! Dobrze...";
			link.l1 = "Kiedy powinienem wrócić, aby odebrać moje zamówienie?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_8";
		break;
		
		case "amulet_9":
			dialog.text = "Encolpion? Twoje żagle nie będą się bać żadnego wiatru, póki posiadasz ten amulet. Dobrze...";
			link.l1 = "Kiedy powinienem wrócić, aby odebrać moje zamówienie?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_9";
		break;
		
		case "amulet_10":
			dialog.text = "Cudotwórca? Niech Pan Bóg ma na oku twoją załogę zarówno na lądzie, jak i na morzu! Dobrze...";
			link.l1 = "Kiedy powinienem wrócić po moje zamówienie?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_10";
		break;
		
		case "amulet_11":
			dialog.text = "Cimaruta? Muszkietowe kule przelatują ci nad głową, nie wyrządzając szkody! Dobrze...";
			link.l1 = "Kiedy powinienem wrócić, aby odebrać moje zamówienie?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_11";
		break;
		
		//группа obereg
		case "obereg_1":
			dialog.text = "Teredo? Każdy stocznia marzy o tym. Dobrze...";
			link.l1 = "Kiedy powinienem wrócić po odebranie mojego zamówienia?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_1";
		break;
		
		case "obereg_2":
			dialog.text = "Xochipilli? To zaoszczędzi trochę czasu na cerowaniu żagli. Dobrze...";
			link.l1 = "Kiedy powinienem wrócić po mój zamówienie?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_2";
		break;
		
		case "obereg_3":
			dialog.text = "Małpa? Powiedziałbym, że to bardziej muł pakowy! Dobrze...";
			link.l1 = "Kiedy powinienem wrócić, aby odebrać moje zamówienie?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_3";
		break;
		
		case "obereg_4":
			dialog.text = "Wachlarz Cyganki? Założyć klapki na oczy patrolującego! Dobrze...";
			link.l1 = "Kiedy powinienem wrócić po moje zamówienie?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_4";
		break;
		
		case "obereg_5":
			dialog.text = "Jadeitowy żółw? To jest twój as w talii kart! Dobrze...";
			link.l1 = "Kiedy powinienem wrócić, aby odebrać moje zamówienie?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_5";
		break;
		
		case "obereg_6":
			dialog.text = "Pięść małpy? Jak mówią - zmusz ich do szacunku! Dobrze...";
			link.l1 = "Kiedy powinienem wrócić po moje zamówienie?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_6";
		break;
		
		case "obereg_7":
			dialog.text = "Rybak? To jest marzenie każdego nawigatora. Dobrze...";
			link.l1 = "Kiedy powinienem wrócić po odbiór mojego zamówienia?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_7";
		break;
		
		case "obereg_8":
			dialog.text = "Koraliki kupca? Pieniądze lubią być liczone, prawda? Dobrze...";
			link.l1 = "Kiedy powinienem wrócić, aby odebrać moje zamówienie?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_8";
		break;
		
		case "obereg_9":
			dialog.text = "Ehecatl? Każda stara, powolna łajba będzie pływać szybciej niż wiatr! Dobrze...";
			link.l1 = "Kiedy powinienem wrócić po odbiór mojego zamówienia?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_9";
		break;
		
		case "obereg_10":
			dialog.text = "Kolczyk marynarza? Daj to swojemu sternikowi! Dobrze...";
			link.l1 = "Kiedy powinienem wrócić po odbiór mojego zamówienia?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_10";
		break;
		
		case "obereg_11":
			dialog.text = "Pielgrzym? Wiatr w twarz staje się wiatrem w plecy. Dobrze...";
			link.l1 = "Kiedy powinienem wrócić, aby odebrać moje zamówienie?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_11";
		break;
		
		case "Trade_artefact_2":
			dialog.text = "Za dwa miesiące, nie wcześniej. Myślę, że do tego czasu przyniosą mi to. Więc będę na ciebie czekać z pieniędzmi za dwa miesiące.";
			link.l1 = "Świetnie! Będę tam! Dziękuję, "+npchar.name+"!";
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "art_date");
			npchar.quest.artday = rand(20)+50;
			sTemp = "Amulet_"+npchar.location;
			AddQuestRecord(sTemp, "1");
			ReOpenQuestHeader(sTemp);
			AddQuestUserData(sTemp, "sAml", XI_ConvertString(npchar.quest.art)); // dlc
		break;
		
		case "Trade_artefact_3":
			if (CheckAttribute(npchar, "art_date") && GetNpcQuestPastDayParam(npchar, "art_date") >= sti(npchar.quest.artday))
			{
			dialog.text = "Tak, mam to. Przygotowałeś 100 dublonów, kapitanie?"; // Addon-2016 Jason
				// belamour legendary edition -->
				if(PCharDublonsTotal() >= 100) 
				{
					link.l1 = "Pewnie! Oto jest, jak się zgodziliśmy.";
					link.l1.go = "Trade_artefact_4";
				}
				else
				{
					link.l1 = "Och, zapomniałem pieniędzy na statku! Przyniosę je wkrótce.";
					link.l1.go = "exit";
				}
				// <-- legendary edition
			}
			else
			{
			dialog.text = "Jeszcze nie. Przyjdź do mnie później. I nie martw się - twój amulet na pewno przyjdzie.";
			link.l1 = "Dobrze.";
			link.l1.go = "exit";
			}
		break;
		
		case "Trade_artefact_4":
			RemoveItems(pchar, "gold_dublon", 100); // Addon-2016 Jason
			Log_Info("You have given 100 doubloons");
			dialog.text = "Wszystko wydaje się w porządku. Oto twój amulet. Powodzenia z nim!";
			link.l1 = "Dziękuję, "+npchar.name+"!";
			link.l1.go = "Trade_artefact_5";
		break;
		
		case "Trade_artefact_5":
			DialogExit();
			Log_Info("You have received "+XI_ConvertString(npchar.quest.art)+"");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, npchar.quest.art, 1);
			DeleteAttribute(npchar, "quest.art");
			sTemp = "Amulet_"+npchar.location;
			AddQuestRecord(sTemp, "2");
			CloseQuestHeader(sTemp);
		break;
		
		// --> калеуче
		case "caleuche":
			PlaySound("interface\important_item.wav");
			dialog.text = "Pokaż, co tam masz.";
			link.l1 = "Tu, wygląda na starożytny indyjski amulet. Ale nie mam pojęcia, jak go używać lub jakie ma ukryte moce.";
			link.l1.go = "caleuche_1";
			npchar.quest.caleuche = "true";
		break;
		
		case "caleuche_1":
			if (npchar.id == pchar.questTemp.Caleuche.Amuletmaster)
			{
				dialog.text = "Cóż, cóż. Jesteś trzecią osobą, która pokazała mi coś takiego, kumplu. Ten amulet został przyniesiony stąd z dzikiej selvy Południowej Main. Nieopodal Panamy są Indianie, którzy noszą takie ozdoby jak ta. Czerwonoskórzy mówią, że to jest dziedzictwo ich 'wielkich przodków'.\nNie mam pojęcia, kim byli ich przodkowie ani jakie dziedzictwo zostawili, ale mogę ci doradzić, gdzie zapytać. Zainteresowany?";
				link.l1 = "Z pewnością!";
				link.l1.go = "caleuche_2";
				DelLandQuestMark(npchar);
				if (npchar.id == "BasTer_Lightman") DelMapQuestMarkShore("Mayak4");
				if (npchar.id == "Santiago_Lightman") DelMapQuestMarkShore("Mayak9");
			}
			else
			{
				dialog.text = "Hmm... I've held a lot of amulets in my hands, but this one, I see for the first time in the Caribbean. Sorry, mate, I cannot help you; I don't know this kind of stuff. But it is not a simple thing; that's a fact. Ask somebody else. I know for sure that there are other lighthouse keepers like me who know about amulets not any less.";
				link.l1 = "Przepraszam... W takim razie będę kontynuować pytania.";
				link.l1.go = "exit";
			}
		break;
		
		case "caleuche_2":
			dialog.text = "There is a Carib village on Dominica, and the local chief is named Moknitekuvri. They have a shaman named Tuttuathapak, a highly respected Indian. He's not one of the Caribs; he's from that place about which I've told you already. He can tell you more about this amulet than me. But be careful - Tuttuathapak hates white people. He really hates them. After all, they once enslaved him and took him away from his home...";
			link.l1 = "Zakładam, że w ten sposób dotarł na Karaiby?";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "Tak. To jest dość interesująca historia. Statek, który przewoził indyjskich niewolników, został uwięziony przez martwą ciszę w pobliżu Marie Galante i połowa załogi zginęła na skutek nagłej gorączki. Jednak żaden z Indian nie zachorował!\nNastępnie kapitan oszalał i podpalił swój statek. W rezultacie uwięzieni Indianie zaczęli bunt i wymordowali załogę. Zgadniesz, kto był ich liderem?";
			link.l1 = "Ja robię...";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "To wszystko. Założę się, że to była czary szamana, które uczyniły morze spokojnym jak zmarły, i zaraziły załogę śmiertelną chorobą. Ten Indianin jest bardzo mądry i bardzo niebezpieczny. Jeśli pójdziesz do niego - zachowuj się grzecznie i pilnuj języka - w przeciwnym razie spotka Cię wiele kłopotów. Ponadto, nawet nie porozmawia z tobą bez ofiary dla niego.";
			link.l1 = "I jaką ofiarę mógłby on wymagać?";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "Nie przekupisz go jakimś badziewiem. Z tego co wiem, wysyła swoich żołnierzy z Karaibów do osad białych, aby kupować broń palną. Przynieś mu muszkiet jako prezent, a wtedy, myślę, będzie zadowolony i poświęci ci trochę swojej uwagi.";
			link.l1 = "Dziękuję! Zrobię jak mówisz... Powiedz, kumple, skąd wiesz o tym wszystkim?";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "Mój przyjaciel był marynarzem na tym straszliwie zdanym na zgubę statku. Na szczęście, udało mu się przetrwać w tym piekle... Widziałem na nim taki amulet jak twój, wygląda na to, że zmarły kapitan też zabrał rzeczy Indian. Jestem pewien, że twój amulet pochodzi z jego kolekcji - kiedy kapitan oszalał i podpalił swój statek, jego marynarze zabili go, a potem splądrowali skrzynie w kajucie.";
			link.l1 = "Rozumiem. Więc muszę tylko pójść z prezentem do Dominiki. Dziękuję za pomoc i za ciekawą historię!";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "Powodzenia, mój przyjacielu, i bądź ostrożny z tym czerwonoskórym diabłem...";
			link.l1 = "...";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			DialogExit();
			AddQuestRecord("Caleuche", "2");
			pchar.questTemp.Caleuche = "dominica"; 
			Caleuche_CreateShamane();
		break;
		
		case "caleuche_9":
			dialog.text = "Tak? Rozmawiałeś z Tuttuathapak, czy się mylę?";
			link.l1 = "Dokładnie. A teraz chcę znaleźć jeszcze dwa amulety. Powiedziałeś, że byłem trzeci, który pokazał ci ten artefakt. A kim byli dwaj inni?";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			dialog.text = "Jeden to mój przyjaciel, marynarz z tamtego statku, który przyprowadził Tuttuathapak na Karaiby. Od tamtego incydentu nie postawił stopy na żadnym pokładzie statku. Nie widziałem go od jakiegoś czasu, ale wiem, gdzie mieszka. Szukaj go na West Main, w Belize - jest teraz myśliwym i wędruje po dżunglach. Nazywa się Fergus Hooper.";
			link.l1 = "Dobrze. A drugi?";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			dialog.text = "Wiem o drugim tylko troszkę. Czy jego imię to Jack, czy Jackson, i czy jest korsarzem, czy małym przedsiębiorcą, czy po prostu poszukiwaczem przygód. Jest właścicielem kszebeka o dziwnej nazwie... hmm... jej nazwa to... Do diabła, zapomniałem! Ale nazwa ta jest jakoś demoniczna. Zapytałem go, co to znaczy, a on powiedział, że to ptak-kobieta, urodzona przez morskich bogów. Bah! Bezbożnik...";
			link.l1 = "Nerd... Więc nie pamiętasz jej imienia?";
			link.l1.go = "caleuche_12";
		break;
		
		case "caleuche_12":
			dialog.text = "Nie, niech mnie trafi piorun, nie pamiętam. O, a kiedy się przedstawiał, wspomniał, że jest z Barbadosu.";
			link.l1 = "To coś! Dobrze, spróbuję znaleźć tego miłośnika pierzastych kobiet, zanim ktoś inny go znajdzie... Dzięki, kumplu, bardzo mi pomogłeś!";
			link.l1.go = "caleuche_13";
		break;
		
		case "caleuche_13":
			dialog.text = "Proszę bardzo, kapitanie, wpadaj czasem.";
			link.l1 = "Pewnie!";
			link.l1.go = "caleuche_14";
		break;
		
		case "caleuche_14":
			DialogExit();
			AddQuestRecord("Caleuche", "7");
			pchar.questTemp.Caleuche = "hunting"; 
			pchar.questTemp.Caleuche.Belizterms = rand(4)+3;
			pchar.quest.caleuche_prepare_beliz.win_condition.l1 = "location";
			pchar.quest.caleuche_prepare_beliz.win_condition.l1.location = "Beliz";
			pchar.quest.caleuche_prepare_beliz.function = "Caleuche_PrepareBeliz";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_SetOwnerType(NPChar); // belamour иначе обижается навсегда		   
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Man_FackYou"://реакция на попытку залезть в сундук
			dialog.text = LinkRandPhrase("Jesteś "+GetSexPhrase(" złodziej, droga moja! Strażnicy, chwytajcie go"," złodziejka! Strażnicy, chwytajcie ją")+"!!!","O rety! Nieco odwróciłem wzrok, a ty już głową w skrzyni! Złapać złodzieja!","Stróże! Rabunek! Zatrzymajcie złodzieja!");
			link.l1 = "Argh, gówno!";
			link.l1.go = "fight";
		break;
		
		// belamour legendary edition карибские нравы
		case "Trial":
			dialog.text = "Ach, więc ty jesteś tym kapitanem! Tak, czekałem na ciebie. Gerard też czekał, ale musiał nagle wybrać się na jakąś ekspedycję, więc poprosił mnie, aby przekazać ci płatność. Powiedział, że musisz przyjść. Tutaj jest czterysta dublonów, jeśli pozwolisz.");
			link.l1 = "Dziękuję! Miło jest mieć do czynienia z uczciwymi ludźmi.";
			link.l1.go = "Trial_1";
		break;
		
		case "Trial_1":
			DialogExit();
			TakeNItems(pchar, "gold_dublon", 400);
			Log_Info("You have received 400 doubloons");
			PlaySound("interface\important_item.wav");
            NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar, "questTemp.Trial");
			DeleteAttribute(npchar, "quest.trial_usurer");
			pchar.questTemp.IslamonaSpaOfficer = true;
			CloseQuestHeader("Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		// <-- legendary edition
	}
}

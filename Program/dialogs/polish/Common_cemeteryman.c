// Jason общий диалог смотрителей кладбищ
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Cemetery\" + NPChar.City + "_cemetery.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
    int iTemp;
	string sTemp;
	bool ok;
    
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("Miasto jest zaalarmowane. Wygląda na to, że nadszedł czas, abym też wziął do ręki broń...","Czy nie jesteś ścigany przez całą straż miejską?. Do mnie, żołnierze!!!","Nie znajdziesz tu schronienia. Ale znajdziesz kilka cali zimnej stali pod żebrem!"),LinkRandPhrase("Czego chcesz, łotrzyku?! Miejska straż już cię śledzi, nie uciekniesz zbyt daleko, "+GetSexPhrase("brudny piracie!","cwaniaro")+"!","Stop! "+GetSexPhrase("Brudny morderca! Straż!!!","Nie boję się ciebie! Wkrótce zostaniesz powieszony w naszym forcie, nie ma gdzie się ukryć...")));
				link.l1 = PCharRepPhrase(RandPhraseSimple("Wygląda na to, że jesteś zmęczony życiem...","A dlaczego nie chcecie żyć spokojnie, obywatele..."+XI_ConvertString("Colony"+npchar.city+"Gen")+"!"),RandPhraseSimple("Idź do diabła!","Zostało ci kilka sekund w tym świecie..."));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			if(!CheckAttribute(pchar, "questTemp.Lantern"))
			{
				dialog.text = "A-a-ah! Ach, to ty... Kim jesteś? Po co przyszedłeś na cmentarz?";
				link.l1 = "Mam na imię "+GetFullName(pchar)+". A kim jesteś i co tu robisz? I dlaczego tak się boisz?";
				link.l1.go = "Lantern_01";
				npchar.quest.meeting = "1";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Lantern") && pchar.questTemp.Lantern == "ToCrypt")
			{
				dialog.text = "No więc, jak było? Sprawdziłeś? Teraz mi wierzysz?";
				link.l1 = "Nie, jeszcze nie schodziłem do krypty. Poczekaj trochę dłużej, sprawdzę wszystko.";
				link.l1.go = "exit";
				break;
			}
			
			if(CheckAttribute(pchar, "questTemp.Lantern") && pchar.questTemp.Lantern == "ToKeeper")
			{
				dialog.text = "No cóż? Rzuciłeś okiem? Widziałeś to?";
				link.l1 = "Tak, na pewno! Miałeś rację!";
				link.l1.go = "Lantern_10";
				link.l2 = "To nie było do końca to, co myślałeś.";
				link.l2.go = "Lantern_14";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple("Witaj, marynarzu! Moje imię to "+GetFullName(npchar)+", a ja jestem jedyną żyjącą duszą tutaj. Tak naprawdę, my wszyscy i tak umrzemy, ha-ha-ha! Dlaczego przyszedłeś?","Witaj! Dawno nie widziałem żywego człowieka... Pozwól, że się przedstawię - "+GetFullName(npchar)+", a ten cmentarz to moje ostatnie schronienie. Wygląda na to, że zostanę tu pochowany. Jak mogę ci pomóc?");
				link.l1 = "Witaj, "+npchar.name+"! Nazywam się "+GetFullName(pchar)+", a jestem kapitanem. Przechodziłem przez dżunglę i dotarłem tutaj. Pomyślałem, że zajrzę do tego wygodnego domu, żeby zobaczyć, kto nie boi się tu mieszkać...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ach, mój stary przyjacielu, kapitanie "+GetFullName(pchar)+"! Chodź, chodź!";
				link.l1 = "Witaj, przyjacielu! Bardzo się cieszę, że cię widzę. Czy nie widzisz tańczących szkieletów w nocy i zmarłych z miedzianymi monetami na oczach we śnie?";
				link.l1.go = "talk";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "A dlaczego miałbym się bać, kapitanie? Trzeba się bać żywych ludzi, martwi nie gryzą. Eh! Kiedyś miałem zupełnie inne życie, a teraz jestem stróżem tego cmentarza. Pilnuję grobów. I czasem handluję jakimiś drobiazgami...";
			link.l1 = "A jakie przedmioty handlujesz, powiedz mi, proszę?";
			link.l1.go = "trade_info";
		break;
		
		case "talk":
			dialog.text = "Co cię do mnie tym razem przyprowadziło?";
			link.l1 = "Pokaż mi, co masz dzisiaj na sprzedaż.";
			link.l1.go = "trade";
			link.l2 = "Chcę zadać ci pytanie...";
			link.l2.go = "quests";
			link.l3 = "Nic poważnego. Po prostu przyszedłem cię przywitać.";
			link.l3.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "trade_info":
			dialog.text = "Mam dużo wolnego czasu, dlatego lubię chodzić po dżungli i zbierać użyteczne rośliny oraz fantazyjne kamienie. Potem sprzedaję je w mieście. Nie kosztują dużo, ale - to lepsze niż nic. I dostaję różne rzeczy od moich przyjaciół...";
			link.l1 = "Przyjaciele? Masz na myśli, że odsprzedajesz to, co inni ci przynoszą?";
			link.l1.go = "trade_info_1";
		break;
		
		case "trade_info_1":
			dialog.text = "O-ho-ho... Nie, dają mi wszystko za darmo. Kto może być przyjacielem stróża cmentarnego, jeśli nie zmarli?";
			link.l1 = "Co... Grabiż martwe ciała?";
			link.l1.go = "trade_info_2";
		break;
		
		case "trade_info_2":
			dialog.text = "I don't rob; I just take things off those who don't need them anymore. Many different people are buried here-some unknown and not from our lands. The commandant brings a dead body from the town and says: 'This is for you, "+npchar.name+", send him on his final journey.' Homeless, hanged pirates, bandits killed by guardians-all are buried here. And old "+npchar.name+" buries their bodies on a Christian custom.";
			link.l1 = "Rozumiem. Cóż, pieniądze to pieniądze, pokaż mi, co masz.";
			link.l1.go = "trade";
			link.l2 = "Zrozumiałem. Muszę iść. Miło mi było cię spotkać.";
			link.l2.go = "exit";
		break;
		
		case "trade":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
			NextDiag.TempNode = "First time";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
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
			dialog.text = LinkRandPhrase("A ty, "+GetFullName(pchar)+", jesteś złodziejem! Strażnicy!!!","Co do diabła! Odwróciłem się na chwilę i już próbujesz ukraść to, co do mnie należy! Chwytać złodzieja!!!","Stróż! Rabunek!!! Chwytać złodzieja!!!");
			link.l1 = "O nie!!!";
			link.l1.go = "fight";
		break;
		//belamour квест на получение фонаря -->
		case "Lantern_01":
			dialog.text = "Uff, więc jesteś tylko podróżnikiem... Moje imię to "+GetFullName(npchar)+", jestem opiekunem tego opuszczonego przez Boga miejsca.";
			link.l1 = "Dlaczego tak czujesz na temat cmentarza? Przeciwnie, to stąd nasz Pan zabiera sprawiedliwych po pogrzebie.";
			link.l1.go = "Lantern_02";
		break;
		
		case "Lantern_02":
			dialog.text = "Ale grzesznicy, najwyraźniej, zostają tutaj po pogrzebie! Przez ostatnie kilka nocy, z krypty dochodzi jakiś hałas. A jęki są tak przerażające, że aż mnie ciarki przechodzą... Wydaje się, że zgubiona dusza nie może znaleźć spokoju! Teraz tylko śpię w ciągu dnia - w nocy nie mogę opuścić mojego stanowiska ani zdrzemnąć się...";
			link.l1 = "Dźwięki? Jęki? Ale tam nie ma nikogo oprócz zmarłych.";
			link.l1.go = "Lantern_03";
		break;
		
		case "Lantern_03":
			dialog.text = "To o czym mówię, rozumiesz? Lepiej stąd uciekaj, zanim duch cię wyczuje... Inaczej nie będziesz mógł spać, tak jak ja.";
			link.l1 = "Hm, tak, myślę, że lepiej opuścić to miejsce.";
			link.l1.go = "Lantern_04";
			link.l2 = "Może mogę ci pomóc? Pozwól mi posłuchać tych dziwnych dźwięków dzisiaj wieczorem.";
			link.l2.go = "Lantern_05";
		break;
		
		case "Lantern_04":
			pchar.questTemp.Lantern = "NoLantern";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Lantern_05":
			dialog.text = "Czy zwariowałeś?! Widzę, że masz broń, ale jak zamierzasz nią walczyć z nieumarłymi? A co jeśli tam kopniesz w kalendarz? Duch będzie swobodnie grasować, a nawet może cię wskrzesić jako swojego sługę!";
			link.l1 = "Cóż, to tylko przesąd...";
			link.l1.go = "Lantern_06";
		break;
		
		case "Lantern_06":
			dialog.text = "Jakie przesądy? To nie jest pobożna ziemia Europy, do diabła... Tubylcy, ci o czerwonych twarzach, potrafią wyczarować wszystko - a teraz musimy tu żyć!";
			link.l1 = "Mimo wszystko, pozwól mi spróbować. Poczekam do zmierzchu, a potem zejdę do krypty.";
			link.l1.go = "Lantern_07";
		break;
		
		case "Lantern_07":
			dialog.text = "Dobrze, rób jak chcesz. Ale jeśli nie wrócisz przed wschodem słońca, zamknę wszystko, zablokuję i ucieknę stąd na własną rękę! Czy to będzie szorowanie pokładu jako marynarz, czy ciągnięcie skrzyń jako dokarz - i tak nie wrócę tutaj!";
			link.l1 = "Spokojnie... Wszystko będzie dobrze.";
			link.l1.go = "Lantern_08";
		break;
		
		case "Lantern_08":
			dialog.text = "Poczekaj... Weź tę latarnię. Mam zapasową. Będziesz jej potrzebować tam. Jest tam zupełnie ciemno!";
			link.l1 = "Dzięki, latarnia rzeczywiście przyda się w takim miejscu.";
			link.l1.go = "Lantern_09";
		break;
		
		case "Lantern_09":
			GiveItem2Character(pchar, "lantern_belt");
			Log_Info("'Lantern' received");
			PlaySound("interface\important_item.wav");
			if(npchar.city == "Charles") SetFunctionLocationCondition("NoiseCemetery_toCrypt", "Charles_CryptBig2", true);
			if(npchar.city == "Havana") SetFunctionLocationCondition("NoiseCemetery_toCrypt", "Havana_CryptBig2", true);
			if(npchar.city == "Villemstad" || npchar.city == "PortRoyal") SetFunctionLocationCondition("NoiseCemetery_toCrypt", "Common_CryptBig2", true);
			pchar.quest.NoiseCemetery_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NoiseCemetery_SeaExit.function = "NoiseCemetery_SeaExit";
			pchar.questTemp.Lantern = "ToCrypt";
			pchar.questTemp.Lantern.nation = npchar.nation;
			AddQuestRecord("NoiseCemetery", "1");
			AddQuestUserData("NoiseCemetery", "sCity", XI_ConvertString(loadedlocation.islandId)); 
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Lantern_10":
			dialog.text = "Prawda? Co tam było? Powiedz mi!";
			link.l1 = "Był niespokojny duch kobiety! Na szczęście, miałem miejscowego księdza, który poświęcił mój miecz, aby smagać niegodziwych, więc wszystko się udało. Ten duch już cię nie przeszkadza.";
			link.l1.go = "Lantern_11";
		break;
		
		case "Lantern_11":
			dialog.text = "O Panie, zbaw nasze grzeszne dusze! Przestrzegałem cię! A ty mi nie uwierzyłeś!";
			link.l1 = "Tak, i szczerze żałuję tego. Ale teraz wszystko jest w porządku - pokropiłem to miejsce święconą wodą, i żaden duch nie ośmieli się powstać z grobu. Możesz spać spokojnie.";
			link.l1.go = "Lantern_12";
		break;
		
		case "Lantern_12":
			dialog.text = "Dziękuję bardzo! Nie masz pojęcia, co to dla mnie znaczy! Proszę, weź to. To niewiele, ale nie mogę pozwolić Ci odejść bez nagrody.";
			link.l1 = "Dziękuję, nie mogę odmówić. Powodzenia!";
			link.l1.go = "Lantern_13";
		break;
		
		case "Lantern_13":
			pchar.quest.NoiseCemetery_SeaExit.over = "yes";
			AddMoneyToCharacter(PChar, 1000);
			pchar.questTemp.Lantern = "Done";
			AddQuestRecord("NoiseCemetery", "3");
			CloseQuestHeader("NoiseCemetery");
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Lantern_14":
			dialog.text = "Nie? Więc co do diabła... to znaczy, co w imię Boga, tam się stało?";
			link.l1 = "Wcale nie było ducha. Młoda para wybrała ten krypt jako miejsce na swoje randki. Ich rodzice są przeciwko temu związku, więc szukali miejsca, gdzie mogliby być sami.";
			link.l1.go = "Lantern_15";
		break;
		
		case "Lantern_15":
			dialog.text = "Sama?.. Dlaczego ci młodzieniaszki! Tylko niech spróbują tu jeszcze raz przyjść! Albo przegonię ich obu biczem, albo zamknę w krypcie, żeby tam zostali!!!";
			link.l1 = "Oni już tu więcej nie wrócą. Powiedziałem im, że ich małe eskapady naprawdę przestraszyły lokalną straż. Oni mają na celu robienie tego. A tak przy okazji, zamek w drzwiach i tak jest zepsuty.";
			link.l1.go = "Lantern_16";
		break;
		
		case "Lantern_16":
			dialog.text = "Nie ma problemu, wymienię to. Ale jeśli kiedykolwiek ich złapię...";
			link.l1 = "Nie bądź taki zły. Wszyscy byliśmy w tym wieku. Nie przyszli tu, bo to najlepsze miejsce na randki.";
			link.l1.go = "Lantern_17";
		break;
		
		case "Lantern_17":
			dialog.text = "W porządku... No cóż, Pan z nimi. Dziękuję, że nie zostawiłeś starca w tarapatach. Proszę, weź to. To nie wiele, ale nie mogę pozwolić Ci odejść bez nagrody.";
			link.l1 = "Dziękuję, nie mogę odmówić. Powodzenia!";
			link.l1.go = "Lantern_18";
		break;
		
		case "Lantern_18":
			DialogExit();
			pchar.quest.NoiseCemetery_SeaExit.over = "yes";
			AddMoneyToCharacter(PChar, 1000);
			pchar.questTemp.Lantern = "Done";
			AddQuestRecord("NoiseCemetery", "4");
			CloseQuestHeader("NoiseCemetery");
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		// <-- квест на получение фонаря 
	}
}

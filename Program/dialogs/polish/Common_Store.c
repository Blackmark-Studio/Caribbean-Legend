// boal 08/04/04 общий диалог торговцев
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06

void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	

	string iDay, iMonth, sTemp, sMoney, attrL;
	
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;
	
	int iMoney, iQuantityGoods, iTradeGoods, iTmp;
	
	bool  ok;

	int iTest, cn, i;
	iTest = FindColony(NPChar.City); // город магазина
	ref rColony, chref;
	
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	int iSeaGoods = LanguageOpenFile("ShipEatGood.txt"); // нужно заменить на GetGoodsNameAlt(idx)

	if(!CheckAttribute(npchar, "quest.trade_date"))
	{
		npchar.quest.trade_date = "";
	}
    
	// вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Store\" + NPChar.City + "_Store.c";
	if(LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	
	// вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06
	
	string attrLoc   = Dialog.CurrentNode;
	
	if(HasSubStr(attrLoc, "TransferGoodsTo_"))
	{
		NPChar.CharToTransferGoodsID = FindStringAfterChar(attrLoc, "_");
		Dialog.CurrentNode = "TransferGoods_Start";
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Alarm został podniesiony w mieście, i wszyscy cię szukają. Na twoim miejscu nie zostawałbym tu.","Wszyscy strażnicy miasta przeszukują miasto, szukając ciebie. Nie jestem głupcem i nie będę z tobą rozmawiać!","Biegnij, "+GetSexPhrase("kumplu","dziewczyno")+", zanim żołdacy zrobią z ciebie sito..."),LinkRandPhrase("Czego chcesz, "+GetSexPhrase("łotrze","łotrzyk")+"?! Strażnicy miejscy już mają twój trop, daleko nie zajdziesz, "+GetSexPhrase("plugawy piracie","mordercze plugastwo")+"!","Plugawy morderco, natychmiast opuść mój dom! Straże!","Nie boję się ciebie, "+GetSexPhrase("szumowino","śmierdziel")+"! Wkrótce zostaniesz powieszony w naszym forcie, daleko nie zajdziesz..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, alarm nigdy nie stanowi dla mnie problemu...","Nie dostaną mnie nigdy."),RandPhraseSimple("Zamknij swoją pieprzoną gębę, "+GetWorkTypeOfMan(npchar,"")+", albo wyrwę twój plugawy język!!","Heh, "+GetWorkTypeOfMan(npchar,"")+", a wszyscy tam - są tu, aby łapać piratów! Powiem ci tak, kumplu: siedź cicho, a nie zginiesz..."));
				link.l1.go = "fight";
				break;
			}
			if (sti(pchar.GenQuest.Piratekill) > 20 && sti(npchar.nation) == PIRATE)
			{
				dialog.text = RandPhraseSimple("Hej, draniu! Myślisz, że możesz brać, co chcesz? Na pewno nie! Chłopcy! Do broni! Zgładźcie szaleńca!","Jeśli czegoś chcesz, kup to, bestio! Teraz pokażę ci, co i jak! Chłopaki, do broni! Alarm!");
				link.l1 = RandPhraseSimple("Co? Co takiego?","Uh, dlaczego to robisz?");
				link.l1.go = "fight";
				bDisableFastReload = true;//закрыть переход
				pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
				pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
				pchar.quest.pirate_in_town.function = "TownPirate_battle";
				break;
			}
			//--> Jason Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				//Jason --> мини-квест Дефицитный товар
				if (CheckAttribute(pchar, "questTemp.Wine.Trader") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
				{
					link.l13 = "Chciałbym od ciebie kupić partię europejskiego wina - pięćdziesiąt-sześćdziesiąt butelek. Powiedziano mi, że masz go wystarczająco na stanie."; 
					link.l13.go = "Wine_Trader";
				}
				if (CheckAttribute(pchar, "questTemp.Wine.Repeat2") && NPChar.location == pchar.questTemp.Wine.City + "_store" && CheckCharacterItem(pchar, "letter_1") && !CheckAttribute(pchar, "questTemp.Wine.fail"))
				{
					link.l13 = "Witaj ponownie. Proszę, spójrz na ten list - może rozważysz ponownie swoją decyzję dotyczącą sprzedaży mi wina?"; 
					link.l13.go = "Wine_Repeat2";
				}
				if (CheckAttribute(pchar, "questTemp.Wine.wait") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
				{
					link.l13 = "To znowu ja. Czy możemy wznowić naszą przerwaną transakcję winem? Udało mi się zebrać wystarczająco pieniędzy."; 
					link.l13.go = "Wine_Price";
				}
				// <-- мини-квест Дефицитный товар
				dialog.text = "Czy chciał pan coś kupić, monsieur?";
				Link.l1 = "Oczywiście, że tak - do czegoż innego służą sklepy? Pokaż mi swoje towary.";
				Link.l1.go = "trade_1";
				Link.l2 = "Przychodzę w celu załatwienia konkretnego interesu...";
				Link.l2.go = "quests";
				Link.l3 = "Przykro mi, ale muszę iść.";
				Link.l3.go = "exit";
				// туториал Мартиника
				if(NPChar.City == "FortFrance")
				{
					if (!CheckAttribute(npchar, "quest.storehelper") && pchar.questTemp.Sharlie == "ship")
					{
						Link.l2 = "Słuchaj, monsieur, szukam pracy. Nie takiej na pełen etat ani taszczenia worków z towarem, ale bardziej jak załatwianie spraw, że tak powiem. Czy przypadkiem potrzebujesz pomocy?";
						Link.l2.go = "Sharlie_storehelper";
					}
					if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "return")
					{
						Link.l2 = "Zakończyłem twoje zlecenie. Znalazłem Gralama Lavoie.";
						Link.l2.go = "Sharlie_storehelper_2";
					}
					if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "choise")
					{
						Link.l2 = "Poznaj swojego nowego asystenta, monsieur.";
						Link.l2.go = "Sharlie_storehelper_11";
					}
					if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "final")
					{
						Link.l2 = "To znowu ja, monsieur. Przyszedłem po swoją nagrodę.";
						Link.l2.go = "Sharlie_storehelper_13";
					}
					if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
					{
						link.l4 = "Spójrz na te kolczyki, monsieur. Znalazłem je przy ciele bandyty, który zginął w dżungli. To z pewnością dzieło wyśmienitego jubilera, który, jestem pewien, nie pochodzi z tych okolic. Czy możesz coś powiedzieć o tych kolczykach?";
						link.l4.go = "Sharlie_junglejew";
					}
				}
				break;
			}			
			//<-- Бремя гасконца
			
			// Warship, 29.05.11. Дело чести - трусливый фехтовальщик.
			if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk"))
			{
				dialog.text = "Kapitanie, dziękuję za uratowanie mnie.";
				Link.l1 = "O, proszę bardzo.";
				Link.l1.go = "exit";
				DeleteAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk");
				break;
			}
			// Карибские нравы
			if(CheckAttribute(npchar, "quest.trial_usurer"))
			{
				dialog.text = "Co tam, kapitanie? Czy coś zgubiłeś? Dlaczego tak biegasz po moim sklepie?";
				Link.l1 = "Cóż, wyobraź sobie - naprawdę mam! Gdzie jest ten przeklęty Gerard LeCroix? Wykonałem wszystkie zadania zlecone mi przez Floriana Shoke, i, niech rekin mnie pożre, miałem z tym cholernie trudny czas! A teraz, gdy przychodzę po swoją nagrodę, okazuje się, że ten ptak odleciał!";
				Link.l1.go = "trial";
				// belamour legendary edition -->
				Link.l2 = "Jak mam ci to powiedzieć... Zaginął. Czy widziałeś mojego klienta? Nazywa się Gerard LeCroix.";
				Link.l2.go = "trialA";
				//<-- legendary edition
				DelLandQuestMark(npchar);
				break;
			}
			// belamour legendary edition Бесчестный конкурент -->
			if(!CheckAttribute(pchar, "questTemp.Shadowtrader") && sti(npchar.nation) != PIRATE && npchar.location == "baster_store")
			{
				dialog.text = "Kapitanie, chcę prosić cię o jedną przysługę. Czy mi pomożesz?";
				link.l1 = "Jak mogę ci pomóc?"; 
				link.l1.go = "Shadowtrader_begin";
				break;
			}
			// <-- legendary edition			
            dialog.Text = GetNatPhrase(npchar,LinkRandPhrase("Miło mi cię poznać, panie! Czy jesteś nowy na tych ziemiach?","Witamy, kapitanie! Mój sklep jest do twojej dyspozycji, sir.","Panie, proszę wejść! Z radością oferuję najlepsze towary, jakie można kupić na tym archipelagu."),LinkRandPhrase("O, monsieur kapitanie! Najlepsze towary we wszystkich francuskich koloniach - właśnie tutaj i teraz, wyłącznie dla ciebie!","Co za miłe spotkanie, monsieur! Najlepszy sklep oferujący najlepsze francuskie towary - do usług!","Czy spotkaliśmy się wcześniej, monsieur kapitanie? Wiesz, mój sklep jest równie dobry jak najlepsze sklepy w ojczyźnie!"),LinkRandPhrase("O! Senor kapitanie! Tak się cieszę, że widzę cię w moim sklepie!","Jestem szczęśliwy, mogąc powitać tak znakomitego caballero w najlepszym sklepie we wszystkich hiszpańskich koloniach!","O, szlachetny hidalgo! Los sam przywiódł cię do mego skromnego sklepu! Tutaj znajdziesz cokolwiek zechcesz!"),LinkRandPhrase("Dzień dobry, panie kapitanie. Czy to wasza pierwsza wizyta tutaj?","Witaj, panie. Czy to twoja pierwsza wizyta tutaj? Zapewniam cię, że jakość naszych holenderskich towarów przyjemnie cię zaskoczy!","Proszę wejść, panie kapitanie! Najlepsze towary po najniższych cenach - to nasz, holenderski, sposób na handel!"));
			Link.l1 = LinkRandPhrase("Miło mi cię poznać. Nazywam się "+GetFullName(pchar)+" i jestem raczej nowy na tych ziemiach. Cóż, pokaż mi bogactwa archipelagu!","Miło cię poznać. Ja jestem "+GetFullName(pchar)+". kapitan statku '"+pchar.ship.name+"'. Więc, jakie są gorące okazje?",""+GetFullName(pchar)+", kapitan statku '"+pchar.ship.name+"Miło cię poznać. Więc, co możesz mi zaoferować?");
			link.l1.go = "node_1";
			
			if(startHeroType == 4 && NPChar.location == "SantaCatalina_store")
			{
				dialog.text = "Kapitanka Helen! Zawsze przyjemność.";
				link.l1 = "Jak i ja tobie, dziękuję.";
				link.l1.go = "Helen_node_1";
			}
			NextDiag.TempNode = "Second time";
		break;

		case "second time":
			if (LAi_group_GetPlayerAlarm() > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("W mieście podniesiono alarm i wszyscy cię szukają. Na twoim miejscu bym tam nie zostawał.","Wszyscy strażnicy miejscy przeszukują miasto, szukając ciebie. Nie jestem głupcem i nie będę z tobą rozmawiał!","Biegnij, "+GetSexPhrase("kamracie","dziewko")+", zanim żołnierze zamienią cię w sito..."),LinkRandPhrase("Czego potrzebujesz, "+GetSexPhrase("łotr","łobuz")+"?! Strażnicy miejscy już wyczuli twój trop, daleko nie zajdziesz, "+GetSexPhrase("plugawy pirat","mordercze plugastwo")+"!","Plugawy morderco, natychmiast opuść mój dom! Strażnicy!","Nie boję się ciebie, "+GetSexPhrase("łajdak","śmierdziel")+"Niebawem zawisniesz na naszej fortecy, daleko nie zajdziesz..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, alarm nigdy nie jest dla mnie problemem...","Nie dostaną mnie nigdy."),RandPhraseSimple("Zamknij gębę, "+GetWorkTypeOfMan(npchar," ")+", albo wyrwę ci plugawy język!","Heh, "+GetWorkTypeOfMan(npchar," ")+", a wszyscy tam - są tutaj, by łapać piratów! Powiem ci tak, kumplu: siedź cicho, a nie zginiesz..."));
				link.l1.go = "fight";
				break;
			}
            
			//--> Jason, Сомнительное предложение
			if (CheckAttribute(pchar, "GenQuest.Contraoffer.Trader.busy"))
			{
				dialog.text = "Proszę, wybacz mi, ale nie mam teraz dla ciebie czasu.";
				link.l1 = "Tak, oczywiście. Wpadnę innym razem, wtedy.";
				link.l1.go = "exit";
				break;
			}
			//<-- Сомнительное предложение
            
			// Warship, 29.05.11. Дело чести - трусливый фехтовальщик.
			if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk"))
			{
				dialog.text = "Kapitánie, dziękuję za uratowanie mnie.";
				Link.l1 = "O, nie ma za co.";
				Link.l1.go = "exit";
				DeleteAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk");
				break;
			}
			// Карибские нравы
			if(CheckAttribute(npchar, "quest.trial_usurer"))
			{
				dialog.text = "Co tam, kapitanie? Zgubiłeś coś? Dlaczego tak biegasz po moim sklepie?";
				Link.l1 = "Cóż, wyobraź sobie, że naprawdę mam! Gdzie jest ten przeklęty Gerard LeCroix? Wykonałem wszystkie zadania, które zlecił mi Florian Shoke, i, niech mnie rekin w całości połknie, miałem z tym cholernie trudny czas! A teraz, gdy przychodzę po swoją nagrodę, okazuje się, że ptak odleciał!";
				Link.l1.go = "trial";
				// belamour legendary edition -->
				Link.l2 = "Jak mam ci to powiedzieć... Zaginął. Czy widziałeś mojego klienta? Nazywa się Gerard LeCroix.";
				Link.l2.go = "trialA";
				//<-- legendary edition
				DelLandQuestMark(npchar);
				break;
			}
 			// belamour legendary edition Бесчестный конкурент -->
			if(!CheckAttribute(pchar, "questTemp.Shadowtrader") && sti(npchar.nation) != PIRATE && npchar.location == "baster_store")
			{
				dialog.text = "Kapitanie, chciałbym prosić cię o jedną przysługę. Czy mi pomożesz?";
				link.l1 = "Jak mogę ci pomóc?"; 
				link.l1.go = "Shadowtrader_begin";
				break;
			}
			// <-- legendary edition           
			dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("O, kogo my tu mamy! No cóż, jak to mówią, pieniądze nie śmierdzą, więc wejdź, kapitanie, i handlujmy...","Nie mogę powiedzieć, że cieszę się na twój widok, "+GetFullName(pchar)+"... Ale wciąż mogę z tobą handlować.","He-he... Cóż, nie zaprosiłbym cię do mojego domu, kapitanie - ale mój sklep wciąż jest do twojej dyspozycji."),LinkRandPhrase("O, kogo my tu mamy! Czyżby to nie był "+GetFullName(pchar)+"Chcesz handlować czy może wziąć coś za darmo? Hej, tylko żartuję...","Nie mogę powiedzieć, że cieszę się, widząc cię tutaj, "+GetAddress_Form(NPChar)+" Ale jeśli masz pieniądze do wydania - wejdź, wejdź...","Chcesz handlować, kapitanie "+GetFullName(pchar)+"Jeśli tak, czy mógłbyś się pospieszyć? Inni klienci cię unikają, a to źle wpływa na mój interes,"),LinkRandPhrase("Chcesz handlować, panie? Chwileczkę, tylko się rozliczę – wiesz, wokół kręcą się podejrzane typy... Oczywiście nie mam na myśli ciebie, kapitanie!","Gdybym zobaczył cię na otwartym morzu, "+GetAddress_Form(NPChar)+", prawdopodobnie kazałbym dodać żagle... Ale tutaj, w moim sklepie, mogę zaoferować ci handel.","Kapitanie, od razu cię ostrzegam: jeśli tkanina jest poplamiona krwią, a kawa cuchnie prochem, nie przyjmę jej. W przeciwnym razie rozejrzyj się i wybierz coś.")),LinkRandPhrase(LinkRandPhrase("I ja cieszę się, że znów cię witam, "+GetAddress_Form(NPChar)+"Handel kupnem czy sprzedażą - zawsze chętnie pomogę.","Błagam cię, "+GetAddress_Form(NPChar)+", wejdźże! Zawsze z radością witam tu mojego ulubionego klienta. Cóż to będzie tym razem - kupno czy sprzedaż?","O, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Jestem tak szczęśliwy, że znów cię widzę! Co tym razem - kupno czy sprzedaż?"),LinkRandPhrase("Czy podoba ci się nasz towar, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"? Zawsze jestem do twoich usług - spójrz i dokonaj wyboru.","Witaj, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+" . Cieszę się, że znów cię widzę! Chcesz rzucić okiem na asortyment naszych towarów?","Radość cię widzieć, kapitanie! Wiedziałem, że spodobają ci się nasze towary najwyższej jakości. Chcesz rzucić okiem na nowości?"),LinkRandPhrase("Oh, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"Proszę, wejdź! Wszystkie towary tylko dla ciebie - i z dużymi rabatami z tej okazji!","Kapitanie "+GetFullName(pchar)+", znów uszczęśliwiłeś mnie swoją wizytą! Proszę, wybierz, co tylko chcesz!","Czego byś sobie życzył tym razem, kapitanie? Cieszę się, że nadal pamiętasz, jak mnie odnaleźć. Mamy wszystkie towary, które mogą ci być potrzebne - najlepszej jakości!")));
			Link.l1 = pcharrepphrase(RandPhraseSimple(RandPhraseSimple("Tak mnie witasz, kamracie? Cóż, zapamiętam to, jeśli spotkamy się na morzu... Przestań drżeć, tylko żartowałem. Pokaż, co masz.","Zgoda, kumplu. Mogę potrzebować twych towarów, ale nie potrzebuję twojego języka. Potrafisz go trzymać na wodzy, czy potrzebujesz z tym pomocy? Zamknij się i pokaż mi swoje towary."),RandPhraseSimple("Przejdźmy do interesów, handlarzu. Nie mam czasu na dyskusję o moralności, więc handlujmy jak przyzwoici ludzie.","Trzymaj konie, kumplu. Żarty są w porządku, ale pamiętaj, że mogę się zezłościć... Więc przestań mnie drażnić i po prostu pokaż mi swoje towary.")),RandPhraseSimple(RandPhraseSimple("Zawsze miło cię odwiedzić, kumplu. Co masz w magazynie, co mogłoby przykuć moją uwagę?","Zawsze miło cię widzieć, kumplu. Co nowego dla morskich wędrowców, którzy nie byli na lądzie od miesięcy?"),RandPhraseSimple("I znowu jestem w "+XI_ConvertString("Colony"+npchar.City+"Rachunek")+"! Cieszę się, że nie zapomniałem. Ale czy coś dla mnie zostało w twoich magazynach? Wszystko już posortowane?","Jak mogłeś nie przyjść? Zawsze zadowalasz mnie bardziej niż to. No cóż, co tam masz?")));
			link.l1.go = "node_1";
			NextDiag.TempNode = "Second time";
		break;

		case "node_1":
			dialog.text = NPCStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase(RandPhraseSimple("Wszyscy na pokład!","Przeprowadź inspekcję! ")+LinkRandPhrase("Co robi "+GetSexPhrase("gentleman","szlachcic, o, przepraszam - dama")+"  szczęścia potrzebujesz w mym sklepie, he-he?","Co za niespodzianka dla biednego, starego sklepikarza! He-he!","Jakiż to pomyślny wiatr przywiał cię do mego sklepu?"),LinkRandPhrase("Otwórzcie porty!","Haki na bok!","Płyń prosto przed siebie!")+RandPhraseSimple(" Tutaj znajdziesz"," Mój sklep ma")+LinkRandPhrase(" najlepsze ceny na całej wyspie.","znakomity asortyment towarów."," towary najlepszej dostępnej jakości.")+RandPhraseSimple(" Jestem do twoich usług"," Cokolwiek chcesz")+", kapitanie!"),pcharrepphrase(RandPhraseSimple("Jakieś towary na "+GetSexPhrase("panowie","panowie i panie")+"  szczęścia! He-he! Dopóki nie zostaną powieszeni do wyschnięcia na słońcu!","Wiatr kołysze powieszonych w porcie i niesie brzęk łańcuchów. Ale pieniądz nie ma zapachu, prawda?"),"Czy chciałbyś "+LinkRandPhrase("kup najlepsze towary z "+NationNameGenitive(sti(NPChar.nation)),"kupuj lub sprzedawaj swój ładunek","masz dochodowy ładunek?")+RandPhraseSimple("? Jestem do Twojej dyspozycji!"," ? Mój sklep jest do twoich usług!")+RandPhraseSimple(" Miło cię widzieć","Jak sobie życzysz")+", kapitanie!")),NPCharRepPhrase(npchar,pcharrepphrase("Jeśli chcesz mojej rady, kapitanie - nie żałuj pieniędzy na kartacze. Wiesz, zmarłych dużo łatwiej przeszukać!","Od razu zauważyłem, że jesteś "+GetSexPhrase("sprytny druh","przebiegła dziewka")+". "+RandPhraseSimple("Ale teraz widzę, że jesteś prawdziwym "+GetSexPhrase("bohater","śmiałek")+".","Jesteś młody, ale "+RandPhraseSimple("zachowaj swoje zmysły przy sobie.","z pewnością nie można cię łatwo oszukać."))),pcharrepphrase("Jestem skłonny kupić od ciebie cały ładunek z przejętych nagród. Chcesz srebro czy złoto? To towar zawsze kosztowny.","Żegluga handlowa to dochodowy interes, kapitanie "+GetFullName(pchar)+"czyż nie?")),NPCharRepPhrase(npchar,RandPhraseSimple("Zawinęliśmy ich wszystkich w mocny grot Z dwudziestoma zwojami liny na węźle I wrzuciliśmy ich za burtę, poza zasięg wzroku!",RandPhraseSimple("Piętnastu ludzi na skrzyni umarlaka!","Pij i diabeł zrobił resztę!")+" Yo ho ho i butelka rumu! ")+RandPhraseSimple("Co słychać, kapitanie?","Szukasz czegoś do kupienia, kapitanie?"),pcharrepphrase("Widzę, że jesteś niezłym targowiskiem, kapitanie "+GetFullName(pchar)+"Ponieważ jesteś stałym klientem, oferuję ci bardzo dobre ceny!","Dobrze, kapitanie "+GetFullName(pchar)+", z szacunku dla ciebie mogę zaoferować tylko trochę więcej! Czego byś sobie życzył?")),NPCharRepPhrase(npchar,"Przysięgam, rozmowa z tobą doprowadza mnie do mdłości. "+LinkRandPhrase("Kup kilka orzeszków. Świnie uwielbiają to świństwo. ","Spodziewasz się, że ktoś wypoleruje ci buty rumem tutaj? ",pcharrepphrase("Znam twoje typy. Napijesz się rumu - i prosto na szubienicę.","Zastanawiam się, jak twoja matka pozwoliła ci zostać żeglarzem! Żeglarzem! Byłbyś o wiele lepszym krawcem...")),pcharrepphrase(RandPhraseSimple("Myślałem, że ","Miałem nadzieję, że ")+RandPhraseSimple("opuściłeś naszą wyspę na dobre.","Już nigdy cię nie zobaczę.")+RandPhraseSimple("Trupy wiszą ci na szyi jak kamienie młyńskie..."," Ilu żeglarzy zostawiłeś, by gnili wśród koralowców?!"),"Kapitanie "+GetFullName(pchar)+", twoja pasja do handlu przerosła wszystkie moje oczekiwania!"+RandPhraseSimple("Chcesz dokonać ostatnich zakupów przed wypłynięciem w morze?"," Szukasz czegoś specjalnego?"))),"cykl",10,npchar,Dialog.CurrentNode);
			// belamour legendary edition на пару с Акулой -->
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && npchar.location == "caracas_store")
			{
				if(pchar.questTemp.SharkGoldFleet == "start" || pchar.questTemp.SharkGoldFleet == "afterGvik")
				{
					dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("O, patrzcie, kto to przyszedł! Cóż, jak mawiają, pieniądze nie śmierdzą, więc wejdź, kapitanie, i handlujmy...","Nie mogę powiedzieć, że cieszę się na twój widok, "+GetFullName(pchar)+"... Ale wciąż mogę z tobą handlować.","He-he... Cóż, nie zaprosiłbym cię do mojego domu, kapitanie - ale mój sklep jest wciąż do twojej dyspozycji."),LinkRandPhrase("O, spójrz, kto tam jest! Czyż to nie "+GetFullName(pchar)+"Chcesz handlować czy po prostu wziąć coś za darmo? Hej, tylko żartuję...","Nie mogę powiedzieć, że cieszę się z twojej obecności tutaj, "+GetAddress_Form(NPChar)+" Ale jeśli masz pieniądze do wydania - wejdź, wejdź...","Chcesz handlować, kapitanie "+GetFullName(pchar)+"Czy mógłbyś się zatem pospieszyć? Inni klienci cię unikają, a to źle wpływa na mój interes,"),LinkRandPhrase("Czy chcecie pohandlować, panie? Chwileczkę, muszę zliczyć kasę - wiecie, kręcą się tu podejrzane typy... Oczywiście, nie mam na myśli was, kapitanie!"," Gdybym zobaczył cię na otwartym morzu, "+GetAddress_Form(NPChar)+", prawdopodobnie kazałbym dodać żagle... Ale tutaj, w moim sklepie, mogę zaoferować ci handel.","Kapitanie, od razu ostrzegam: jeśli tkanina jest poplamiona krwią, a kawa śmierdzi prochem, nie wezmę tego. W przeciwnym razie spójrz i wybierz coś dla siebie.")),LinkRandPhrase(LinkRandPhrase("I ja cieszę się, że znów cię witam, "+GetAddress_Form(NPChar)+"! Kupno czy sprzedaż - zawsze chętnie pomogę.","Błagam cię, "+GetAddress_Form(NPChar)+", wejdźże! Zawsze miło mi widzieć mojego ulubionego klienta tutaj. Cóż to będzie tym razem - kupno czy sprzedaż?","Och, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Jakże miło cię znów widzieć! Czym się zajmiemy tym razem - kupnem czy sprzedażą?"),LinkRandPhrase("Czy podobają ci się nasze towary, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"? Zawsze jestem do twojej dyspozycji - spójrz i wybierz coś dla siebie.","Witaj, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+". Cieszę się, że znów cię widzę! Chcesz rzucić okiem na nasz asortyment towarów?","Miło cię widzieć, kapitanie! Wiedziałem, że spodobają ci się nasze towary najwyższej jakości. Chcesz rzucić okiem na nowości?"),LinkRandPhrase("Oh, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Proszę wejść! Wszystkie towary tylko dla ciebie - i z wielkimi zniżkami z tej okazji!","Kapitanie "+GetFullName(pchar)+" , raz jeszcze uszczęśliwiłeś mnie swoją wizytą! Proszę, wybierz, co tylko zechcesz!","Czego sobie życzysz tym razem, kapitanie? Cieszę się, że wciąż pamiętasz, jak mnie znaleźć. Mamy wszystkie towary, jakich możesz potrzebować - najlepszej jakości!")));
					link.l14 = "Słuchaj, zamierzam teraz wyruszyć do Porto Bello i chciałbym kupić od ciebie ładunek kawy i kakao. Powiedzmy, trzysta jednostek każdego."; 
					link.l14.go = "SharkGoldFleet";
				}
			}
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && npchar.location == "caracas_store" && pchar.questTemp.SharkGoldFleet == "buyincar")
			{
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("O, kogo my tu mamy! Cóż, jak to mówią, pieniądze nie śmierdzą, więc wejdź, kapitanie, i handlujmy...","Nie mogę powiedzieć, że cieszę się na twój widok, "+GetFullName(pchar)+"... Ale wciąż mogę z tobą handlować.","He-he... Cóż, nie zaprosiłbym cię do mojego domu, kapitanie - ale mój sklep jest wciąż do twojej dyspozycji."),LinkRandPhrase("O, spójrz, kto tam jest! Czyż to nie jest "+GetFullName(pchar)+"Chcesz handlować czy po prostu zabrać coś za darmo? Hej, tylko żartuję...","Nie mogę powiedzieć, że cieszę się z twojego widoku tutaj, "+GetAddress_Form(NPChar)+" Ale jeśli masz pieniądze do wydania - wejdź, wejdź...","Chcesz handlować, kapitanie "+GetFullName(pchar)+"? Jeśli tak, to czy możesz się pospieszyć? Inni klienci cię unikają, a to źle wpływa na mój interes,"),LinkRandPhrase("Chcesz handlować, mynheer? Chwileczkę, muszę się rozliczyć - wiesz, wokół kręcą się podejrzane typy... Oczywiście nie mam na myśli ciebie, kapitanie!","Jeśli zobaczyłbym cię na otwartym morzu, "+GetAddress_Form(NPChar)+", prawdopodobnie kazałbym dodać żagle... Ale tutaj, w moim sklepie, mogę zaoferować ci handel.","Kapitanie, od razu Cię ostrzegam: jeśli tkanina jest poplamiona krwią, a kawa cuchnie prochem, to jej nie wezmę. W przeciwnym razie, spójrz i dokonaj wyboru.")),LinkRandPhrase(LinkRandPhrase("I cieszę się, że mogę cię znów powitać, "+GetAddress_Form(NPChar)+"Kupić czy sprzedać - zawsze chętnie pomogę.","Błagam cię, "+GetAddress_Form(NPChar)+", wejdź! Zawsze cieszę się, gdy widzę mojego ulubionego klienta. Co to będzie tym razem - kupno czy sprzedaż?","Oh, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Tak się cieszę, że znów cię widzę! Co to będzie tym razem - kupno czy sprzedaż?"),LinkRandPhrase("Czy podobają ci się nasze towary, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"? Zawsze jestem do twojej dyspozycji - rozejrzyj się i wybierz coś.","Cześć, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+" . Cieszę się, że znów cię widzę! Chcesz rzucić okiem na asortyment naszych towarów?","Miło cię widzieć, kapitanie! Wiedziałem, że spodobają ci się nasze towary wysokiej jakości. Chcesz rzucić okiem na nowości?"),LinkRandPhrase("Och, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Proszę, wejdź! Wszystkie towary tylko dla ciebie - i z wielkimi zniżkami na tę okazję!","Kapitanie "+GetFullName(pchar)+" , znowu sprawiłeś mi radość swoją wizytą! Proszę, wybierz, co tylko zechcesz!","Czego pragniesz tym razem, kapitanie? Cieszę się, że wciąż pamiętasz, jak mnie znaleźć. Mamy wszystkie towary, których możesz potrzebować - najlepszej jakości!")));
				link.l14 = "Przybyłem po kawę i kakao. "; 
				link.l14.go = "SharkGoldFleet_again";
			}
										
			// <-- на пару с Акулой
			link.l1 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Pokaż mi, co masz, stary piracie!","Chciałem tylko rzucić okiem na twoje towary, dobry człowieku."),pcharrepphrase("Przysięgam na szubienicę, "+GetFullName(npchar)+", nie pozwolę ci mnie zbyć! Pokaż mi swoje towary natychmiast!","Spójrzmy na twoje towary, "+GetAddress_FormToNPC(NPChar)+".")),NPCharRepPhrase(npchar,pcharrepphrase("To na pewno! Martwi nie gryzą! A co masz w swojej ładowni?","Lepiej zajmij się swoim interesem, mój dobry człowieku. Jakie towary możesz mi zaoferować?"),pcharrepphrase("Nadejdzie dzień, kiedy staniesz się moją zdobyczą, he-he. Żartuję. Pokaż mi swoje towary.","Porozmawiajmy o naszych sprawach handlowych, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"Sure, please provide the text you need translated.")),NPCharRepPhrase(npchar,pcharrepphrase("Co chcę? Chcę coś kupić!","Pijaństwo zaprowadzi cię do grobu, "+GetFullName(npchar)+"Chcę rzucić okiem na twój towar."),pcharrepphrase("Znam twoje zniżki! Dwa funty kakao w cenie trzech! Teraz pokaż mi swoje towary.","To zawsze dobrze. Targujmy się zatem.")),"Pokaż mi swoje towary. Im mniej gadania, tym szybciej załatwiona sprawa. Śpieszę się.",npchar,Dialog.CurrentNode);
			link.l1.go = "market";
			link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Och, naprawdę chciałbym kogoś dźgnąć, Dobrze, przejdźmy do interesów.","Przejdźmy do innych interesów, mój dobry człowieku."),pcharrepphrase("Caramba! Jestem tu w innej sprawie!","Chcę z tobą porozmawiać o pewnym interesie, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+".")),NPCharRepPhrase(npchar,pcharrepphrase("Mam z tobą interesy, stary piracie!","Przejdźmy do interesów, kumplu!"),pcharrepphrase("Przysięgam na diabła, nie oszukasz mnie, łotrze! Mam z tobą inne interesy!","Absolutnie się zgadzam, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+", chciałem omówić z tobą inne sprawy.")),NPCharRepPhrase(npchar,pcharrepphrase("Już załadowany? Mam z tobą interesy.","Przyszedłem tu nie dla handlu, mój dobry człowieku. Mam inne sprawy."),pcharrepphrase("Oby piorun cię trafił za takie ceny! Mam z tobą interesy.","Zniżki są zawsze miłe, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+", ale mam z tobą inne interesy.")),NPCharRepPhrase(npchar,pcharrepphrase("Trzymaj język za zębami, stary pijaku, mam z tobą interesy","Źle się czujesz z powodu rumu, jak mniemam. Nie żebym był tobą zachwycony. Przejdźmy do interesów."),pcharrepphrase("Już mnie oskubałeś, łotrze! Mam z tobą interesy.","Twoja ironia jest nie na miejscu. Mam inne sprawy do omówienia z tobą.")),npchar,Dialog.CurrentNode);
			link.l2.go = "business";
			/*link.l3 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Najpierw interesy, potem zabawa. Chcę cię o coś zapytać.","Nie teraz. Potrzebuję informacji."),pcharrepphrase("Do diabła z twoimi cenami! Najpierw powiesz mi wszystko, co potrzebuję wiedzieć.","Z przyjemnością. Chciałem o coś zapytać.")),NPCharRepPhrase(npchar,pcharrepphrase("Dzięki za radę, stary morderco. Chciałem cię o coś zapytać.","Miałem konkretne pytanie."),pcharrepphrase("Złoto może poczekać. Chciałem cię o coś zapytać.","Tak, zgadzam się. Chciałem cię o coś zapytać.")),NPCharRepPhrase(npchar,pcharrepphrase("Jestem przekonany, że wiesz, o co chciałem zapytać.","Mam nadzieję, że odpowiesz na moje pytanie."),pcharrepphrase("Potrafisz myśleć o czymś innym niż twoje metki z cenami? Bo właśnie o to chciałem cię zapytać.","To mnie nie interesuje. Potrzebuję informacji.")),NPCharRepPhrase(npchar,pcharrepphrase("Nie podniecaj się za bardzo, kumplu! Chciałem ci tylko zadać pytanie.","Nie podniecaj się za bardzo, bo dostaniesz udaru. Odpowiedz tylko na jedno pytanie, a ja odejdę"),pcharrepphrase("Nie spodziewam się, że powiesz coś mądrego, skoro masz mózg karalucha. Ale z pewnością musisz coś wiedzieć.","Nie będę cię długo zatrzymywał. Tylko jedno pytanie.")),npchar,Dialog.CurrentNode);*/
			//link.l3 = "Jestem w innej sprawie.";
			//link.l3.go = "quests";
			// --> Jason, генер почтового курьера 2 уровня
			if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
			{
				if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					link.l12 = "Przyniosłem ci cennik z miasta "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Generał")+".";
					link.l12.go = "Postcureer_LevelUp_ForAll";
				}
			}
			//<--генер почтового курьера 2 уровня	
						
			//Jason --> мини-квест Дефицитный товар
			if (CheckAttribute(pchar, "questTemp.Wine.Trader") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
				link.l13 = "Chciałbym nabyć partię europejskiego wina od ciebie - pięćdziesiąt-sześćdziesiąt butelek. Powiedziano mi, że masz go wystarczająco na składzie.."; 
				link.l13.go = "Wine_Trader";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.Repeat2") && NPChar.location == pchar.questTemp.Wine.City + "_store" && CheckCharacterItem(pchar, "letter_1") && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
				link.l13 = "Witaj ponownie. Proszę, spójrz na ten list - być może zmienisz swoje stanowisko w sprawie sprzedaży wina dla mnie?"; 
				link.l13.go = "Wine_Repeat2";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.wait") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
				link.l13 = "To znowu ja. Czy możemy wznowić naszą przerwaną transakcję wina? Udało mi się zebrać wystarczająco pieniędzy."; 
				link.l13.go = "Wine_Price";
			}
			// <-- мини-квест Дефицитный товар
			
			// туториал Мартиника
			if(CheckAttribute(pchar, "questTemp.Sharlie.Lock") && NPChar.City == "FortFrance")
			{
				if (!CheckAttribute(npchar, "quest.storehelper") && pchar.questTemp.Sharlie == "ship")
				{
					Link.l2 = "Słuchaj, monsieur, szukam pracy. Nie takiej na pełen etat ani pracy przy przenoszeniu worków z towarem, ale bardziej jak załatwianie spraw, że tak powiem. Czy przypadkiem nie potrzebujesz pomocy?";
					Link.l2.go = "Sharlie_storehelper";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "return")
				{
					Link.l2 = "Zakończyłem twoje zlecenie. Znalazłem Gralama Lavoie.";
					Link.l2.go = "Sharlie_storehelper_2";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "choise")
				{
					Link.l2 = "Poznaj swojego nowego asystenta, monsieur.";
					Link.l2.go = "Sharlie_storehelper_11";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "final")
				{
					Link.l2 = "To znowu ja, monsieur. Przyszedłem po swoją nagrodę.";
					Link.l2.go = "Sharlie_storehelper_13";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
				{
					link.l4 = "Rzuć okiem na te kolczyki, monsieur. Znalazłem je na ciele bandyty, który zginął w dżungli. To wyraźnie dzieło wyśmienitego jubilera, który, jestem pewien, nie pochodzi stąd. Czy możesz coś powiedzieć o tych kolczykach?";
					link.l4.go = "Sharlie_junglejew";
				}
			}
						
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "store_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l9 = "Witaj, przyszedłem na zaproszenie twojego syna."; 
					link.l9.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if(pchar.GenQuest.EncGirl.Father == "store_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = "Chodzi o twoją córkę...";
						link.l9.go = "EncGirl_1";
					}
				}				
			}			
			link.l5 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Do zobaczenia, stary pijaku.","Miłego dnia, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"."),pcharrepphrase("Caramba! Nigdzie się nie ruszaj, wrócę ponownie.","Miło było Cię tu gościć, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"Do widzenia!")),NPCharRepPhrase(npchar,pcharrepphrase("Odpływamy!","Żegnaj, mój dobry człowieku."),pcharrepphrase("Hej! Co tam chowasz? Rum? Nie?! Dobrze, pójdę zwilżyć gardło.","Przykro mi, ale mam pilne sprawy w mieście.")),NPCharRepPhrase(npchar,pcharrepphrase("Heh! Cóż, do zobaczenia!","Muszę iść. Żegnaj, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!"),pcharrepphrase("I nawet nie próbuj się ze mną kłócić! Nie mam na to czasu!","Być może muszę iść i sprawdzić, co słychać na moim statku. Żegnaj, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!")),NPCharRepPhrase(npchar,pcharrepphrase("Co tam, stary druhu? To ja - "+GetFullName(pchar)+"Wyśpij się i wytrzeźwiej, wrócę później.","Obawiam się, że twoja wątroba wykończy cię, zanim będę miał okazję znowu do ciebie przyjść."),pcharrepphrase("Liczyj dalej swoje gwinee i dublony, stary lisie! Wrócę.","Byłem zadowolony, że cię widzę, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!")),npchar,Dialog.CurrentNode);
			link.l5.go = "exit";
		break;
		
		case "Helen_node_1":
			dialog.text = "Co mogę dla ciebie zrobić? Uzupełnić zapasy na Rainbow, sprzedać trochę łupów? Wątpię, żebyś był zainteresowany obecnymi dochodowymi frachtami, ha-ha.";
			link.l1 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Pokaż mi, co masz, stary piracie!","Chciałem tylko rzucić okiem na twoje towary, mój dobry człowieku."),pcharrepphrase("Przysięgam na szubienicę, "+GetFullName(npchar)+", Nie dam się zbyć! Pokaż mi swoje towary natychmiast!","Rzućmy okiem na twoje towary, "+GetAddress_FormToNPC(NPChar)+".")),NPCharRepPhrase(npchar,pcharrepphrase("To pewne! Umarli nie ugryzą! No, cóż masz w swojej ładowni?","Radziłbym ci zająć się swoimi sprawami, mój dobry człowieku. Jakie towary możesz mi zaoferować?"),pcharrepphrase("Przyjdzie dzień, kiedy staniesz się moim łupem, he-he. Żartuję tylko. Pokaż mi swoje towary.","Porozmawiajmy o naszych sprawach handlowych, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"")),NPCharRepPhrase(npchar,pcharrepphrase("Czego chcę? Chcę coś kupić!","Pijaństwo zaprowadzi cię do grobu, "+GetFullName(npchar)+"Chcę rzucić okiem na twój asortyment."),pcharrepphrase("Znam twoje zniżki! Dwa funty kakao w cenie trzech! Teraz pokaż mi swoje towary.","To zawsze dobrze. Potargujmy się, zatem.")),"Pokaż mi swoje towary. Im mniej się mówi, tym szybciej załatwione. Spieszę się.",npchar,Dialog.CurrentNode);
			link.l1.go = "market";
			link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Och, naprawdę chciałbym kogoś dźgnąć, Dobrze, przejdźmy do interesów.","Przejdźmy do innych interesów, mój dobry człowieku."),pcharrepphrase("Caramba! Jestem tu w innym interesie!","Chcę porozmawiać z tobą o pewnym interesie, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+".")),NPCharRepPhrase(npchar,pcharrepphrase("Mam z tobą interesy, stary piracie!","Przejdźmy do interesów, kumplu!"),pcharrepphrase("Przysięgam na diabła, nie oszukasz mnie, łotrze! Mam z tobą inne interesy!","Zdecydowanie się zgadzam, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+", chciałem z tobą omówić inne sprawy.")),NPCharRepPhrase(npchar,pcharrepphrase("Już załadowany? Mam sprawę do ciebie.","Przyszedłem tu nie dla handlu, mój dobry człowieku. Mam inne sprawy."),pcharrepphrase("Niech cię piorun trzaśnie za takie ceny! Mam z tobą interesy.","Zniżki są zawsze miłe, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+", ale mam z tobą inne interesy.")),NPCharRepPhrase(npchar,pcharrepphrase("Trzymaj język za zębami, stary pijaku, mam z tobą interesy","Chyba masz kaca po rumie. Nie żebym za tobą przepadał. Przejdźmy do interesów."),pcharrepphrase("Już mnie oskubałeś, łotrze! Mam z tobą interesy.","Twoja ironia jest nie na miejscu. Mam z tobą inne interesy.")),npchar,Dialog.CurrentNode);
			link.l2.go = "business";
			link.l3 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Najpierw interesy, potem hulanki. Chcę cię o coś zapytać.","Nie teraz. Potrzebuję informacji."),pcharrepphrase("Do diabła z twoimi cenami! Najpierw powiesz mi wszystko, czego potrzebuję.","Z przyjemnością. Chciałem o coś zapytać.")),NPCharRepPhrase(npchar,pcharrepphrase("Dzięki za radę, stary morderco. Chciałem cię o coś zapytać.","Miałem konkretne pytanie."),pcharrepphrase("Złoto może poczekać. Chciałem cię o coś zapytać.","Tak, zgadzam się. Chciałem cię o coś zapytać.")),NPCharRepPhrase(npchar,pcharrepphrase("Jestem przekonany, że wiesz, o co miałem zamiar zapytać.","Mam nadzieję, że odpowiesz na moje pytanie."),pcharrepphrase("Czy potrafisz myśleć o czymś innym niż twoje metki z cenami? Bo właśnie o to chciałem cię zapytać.","To mnie nie interesuje. Potrzebuję informacji.")),NPCharRepPhrase(npchar,pcharrepphrase("Nie ekscytuj się za bardzo, kumplu! Chciałem ci tylko zadać pytanie.","Nie ekscytuj się za bardzo, bo dostaniesz apopleksji. Odpowiedz tylko na jedno pytanie, a wtedy odejdę"),pcharrepphrase("Nie spodziewam się, że powiesz coś mądrego, skoro masz mózg karalucha. Ale na pewno musisz coś wiedzieć.","Nie będę cię długo zatrzymywać. Tylko jedno pytanie.")),npchar,Dialog.CurrentNode);
			link.l3.go = "quests";
			link.l5 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Do zobaczenia, stary pijaku.","Miłego dnia, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"."),pcharrepphrase("Caramba! Nie ruszaj się nigdzie, wrócę ponownie.","Miło było cię tu gościć, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"Żegnaj!")),NPCharRepPhrase(npchar,pcharrepphrase("Zrywaj kotwicę!","Żegnaj, mój dobry człowieku."),pcharrepphrase("Hej! Co tam chowasz? Rum? Nie?! Dobrze, pójdę zwilżyć gardło.","Przykro mi, ale mam pilne sprawy w mieście.")),NPCharRepPhrase(npchar,pcharrepphrase("Heh! Cóż, do zobaczenia!","Muszę iść. Żegnaj, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!"),pcharrepphrase("I nawet nie próbuj się ze mną kłócić! Nie mam na to czasu!","Być może muszę iść i sprawdzić, co się dzieje na moim statku. Żegnaj, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!")),NPCharRepPhrase(npchar,pcharrepphrase("Co tam, stary druhu? To ja - "+GetFullName(pchar)+"Wyśpij się i wytrzeźwiej, wrócę później.","Obawiam się, że twoja wątroba wykończy cię, zanim będę miał okazję znów do ciebie przyjść."),pcharrepphrase("Liczyj dalej swoje gwinee i dublony, stary lisie! Wrócę jeszcze.","Byłem szczęśliwy, widząc cię, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!")),npchar,Dialog.CurrentNode);
			link.l5.go = "exit";
		break;

		case "market":
//navy -->
			//занят ПГГ
			if (CheckFreeServiceForNPC(NPChar, "Store") != -1)	 // to_do имя сунуть
			{
				dialog.text = "Przykro mi, ale teraz jestem zbyt zajęty. Tyle klientów! Wróć jutro.";
				link.l1 = "O, doprawdy? Cóż, wrócę później, zatem.";
				link.l1.go = "exit";
				break;
			}
//navy <--
			dialog.text = RandPhraseSimple("Mam kulę armatnią, żagle, lekarstwa, cenne drewno i inne towary! Czym jesteś zainteresowany?","Chcesz kupić cukier i przyprawy? A może rum i proch strzelniczy?");
			link.l1 = pcharrepphrase(LinkRandPhrase("Mam mnóstwo łupów w ładowni! Pieniądze nie mają zapachu, prawda?","Muszę pozbyć się łupu z mojego ładowni i napełnić ją twoim złotem. Ha-ha!","Och, wiem, że sprzedałbyś własną matkę za worek pełen doubloonów! Ale ja tylko potrzebuję uzupełnić swoje zapasy."),LinkRandPhrase("Chcę sprzedać mój ładunek i uzupełnić zapasy.","Chcę zakupić towary na sprzedaż.","Pokaż mi kule armatnie, bomby i takie tam."));
			link.l1.go = "trade_1";

			if(CheckFunctionalTreasurer() && CheckAttribute(PChar, "TransferGoods.Enable")) // Автозакупка товаров
			{
				link.l5 = "Mój kwatermistrz dokona wszystkich niezbędnych zakupów...";
				link.l5.go = "TransferGoods";
			}
			
			link.l3 = pcharrepphrase(RandPhraseSimple("Odchodzę bez handlu. Do zobaczenia!","Idę zwilżyć gardło. Zostań tam!"),RandPhraseSimple("Nie, nie mam teraz czasu na handel. Żegnaj.","Przepraszam, mam pilne sprawy do załatwienia. Do widzenia!"));
			link.l3.go = "exit";
		break;
		
		case "EncGirl_1":
			dialog.text = "Zamieniam się w słuch.";
			link.l1 = "Przyprowadziłem twojego zbiega.";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "O, kapitanie, bardzo dziękuję! Jak się ma? Czy jest ranna? Minął dzień, odkąd uciekła, niegrzeczna dziewczyna. Czy wygląda na to, że zamierzam jej wyrządzić jakąś krzywdę? Znalazłem jej męża. Zaaranżowałem małżeństwo. Bogaty, młody narzeczony. Może nie wygląda najlepiej, ale kogo obchodzi wygląd twarzy. Nie! Zawsze próbuje wszystko załatwić po swojemu. Tak samo, jak zawsze robiła jej matka, płomienie!\nChoć, nie urodziłaby się, gdyby jej matka nie uciekła z jakimś obiecującym idiotą dawno temu... cóż, nieważne... Młodość jest naiwna, głupia i okrutna.";
			link.l1 = "Oczywiście, jesteś ojcem i to do ciebie należy decyzja, ale nie spieszyłbym się z weselem...";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "Cóż ty wiesz? Masz własne dzieci? Nie? Porozmawiaj ze mną, gdy będziesz miał...\nTak... Obiecałem nagrodę człowiekowi, który ją sprowadzi, oto weź to.";
			link.l1 = "Dzięki. I miej na nią oko. Mam przeczucie, że na tym nie poprzestanie.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "O, więc jesteś "+GetSexPhrase("ten kapitan, który przyniósł","ta dziewka, która przyniosła")+" mój marnotrawny syn z młodą żoną?";
				link.l1 = "Tak, pomogłem im uciec.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "O, tam "+GetSexPhrase("on jest, nasz dobroczyńca","ona jest naszą dobrodziejką")+"Spodziewam się nagrody, czyż nie tak?";
				link.l1 = "Cóż, dam sobie radę bez nagrody, ale wystarczą mi twoje podziękowania.";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "Jestem Ci bardzo wdzięczny, że nie porzuciłeś mojego dziecka w trudnej sytuacji i pomogłeś mu znaleźć wyjście z delikatnego położenia. Pozwól mi podziękować Ci i proszę, przyjmij tę skromną sumę oraz prezent ode mnie osobiście.";
			link.l1 = "Dzięki. Pomoc tej młodej parze była dla mnie przyjemnością.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "Dzięki? Jakie dzięki?! Ten gamoń kręci się bez pracy od pół roku - a spójrz na niego, ma wystarczająco dużo czasu na miłostki! Kiedy ja byłem w jego wieku, już prowadziłem własny interes! Pff! Gubernator ma córkę na wydaniu - a ten prostak przyprowadził do mojego domu jakąś ladacznicę bez rodziny i śmiał prosić o moje błogosławieństwo!";
			link.l1 = "Hmm... Najwyraźniej nie wierzysz w szczere uczucia?";
			link.l1.go = "EncGirl_6_1";		
		break;
		
		case "EncGirl_5_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.EncGirl.sum));
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item);
			AddQuestRecord("JungleGirl", "18");
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "EncGirl_6_1":
			dialog.text = "Jakie uczucia? O jakich uczuciach mówisz? Uczucia... jak można być tak lekkomyślnym w twoim wieku?! Wstydź się, że pobłażasz młodym w ich kaprysach i działasz jak stręczyciel! Nie tylko zabrałeś dziewczynę z jej domu, ale także zrujnowałeś życie mojego nowicjusza. Nie będzie ci za to podziękowań. Żegnaj.";
			link.l1 = "Dobrze, i to samo dla ciebie...";
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		
		// Warship. Автозакупка товаров -->
		case "TransferGoods":
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				dialog.text = LinkRandPhrase("...Już zrobione. Teraz pozostało tylko zdecydować, który statek załadować.","Twój skarbnik już się tym zajął. Zdecydujmy teraz, który statek ma być załadowany.","Tak, "+PChar.name+", wiem. Już mnie odwiedził. A teraz, który statek będziemy ładować?");
					
				for(i=0; i<COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(PChar, i);
					if(cn > 0)
					{
						chref = GetCharacter(cn);
						if(!GetRemovable(chref)) continue;
						
						attrL = "l"+i;
						Link.(attrL)    = "It will be " + XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
						Link.(attrL).go = "TransferGoodsTo_" + chref.id;
					}
				}
				
				Link.l99 = "Przyszło mi to na myśl, niczego nie potrzebuję.";
				Link.l99.go = "exit";
			}
			else // Корабля нету
			{
				dialog.text = NPCharRepPhrase(npchar,pcharrepphrase("Żartujesz sobie? Gdzie jest twój statek? Nie widzę go przy nabrzeżu!","Przysięgam na diabła, nie oszukasz mnie! Twojego statku nie ma przy nabrzeżu!"),pcharrepphrase("Nie widzę twojego statku w porcie, kapitanie "+GetFullName(pchar)+"  Mam nadzieję, że to nie 'Latający Holender'?","Kapitanie, o wiele łatwiej jest załadować ładunek z nabrzeża. I wolę to robić w ten sposób. Przyprowadź swój statek szybko i wracaj."));
				link.l1 = NPCharRepPhrase(npchar,pcharrepphrase(""+RandSwear()+"Co za kłopot! Dobrze, stary chytrusie, do zobaczenia wkrótce!","Nie chciałem cię oszukać, "+GetFullName(npchar)+", statek jest po drugiej stronie wyspy."),pcharrepphrase("Nie. Mój statek nazywa się 'Czarna Perła'. Dlaczego zbladłeś? Haha! Tylko żartuję!","Dzięki za radę, koniecznie ją wykorzystam."));
				link.l1.go = "exit";
			}
			break;
			
		case "TransferGoods_2": // Тут уже не проверяем, есть корабль или нету (выбрали корабль, в который груз не помещается)
			dialog.text = LinkRandPhrase("Więc, kapitanie, który statek załadujemy?","Więc, który statek załadujemy?",PChar.name+"Na który statek mamy załadować towary?");
				
			for(i=0; i<COMPANION_MAX; i++)
			{
				cn = GetCompanionIndex(PChar, i);
				if(cn > 0)
				{
					chref = GetCharacter(cn);
					if(!GetRemovable(chref)) continue; // Если квестовый - пропускаем
					
					attrL = "l"+i;
					Link.(attrL)    = "It will be " + XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
					Link.(attrL).go = "TransferGoodsTo_" + chref.id;
				}
			}
			
			Link.l99 = "Zmieniłem zdanie, niczego nie potrzebuję.";
			Link.l99.go = "exit";
			break;
			
		case "TransferGoods_Start":
			chref = CharacterFromID(NPChar.CharToTransferGoodsID);
			
			iQuantityGoods = TransferGoods_CalculateWeight(chref);
			
			if(GetCargoFreeSpace(chref) >= iQuantityGoods)
			{
				if(TransferGoods_StartTransfer(chref, NPChar.City) != 0)
				{
					dialog.text = LinkRandPhrase("Wszystko gotowe! Załadunek wybranego statku się rozpoczął.","Dobrze, rozpoczęło się ładowanie towarów na wybrany statek.","Kapitanie, załadunek towarów na wybrany statek się rozpoczął.");
					link.l1 = "Dziękuję. Przyjemność robić z tobą interesy.";
					link.l1.go = "exit";
          SetPriceListByStoreMan(rColony); // mitrokosta обновляем список цен
					WaitDate("", 0, 0, 0, 1, 0); // Крутим время
				}
				else
				{
					dialog.text = LinkRandPhrase("Kapitanie, wszystkie towary zamówione przez Twojego skarbnika są już na pokładzie wskazanego przez Ciebie statku!","Kapitanie, wszystkie towary są już na pokładzie wskazanego przez Ciebie statku!","Kapitanie, ten statek nie wymaga obsługi, ponieważ wszystkie towary są już na pokładzie.");
					link.l1 = "Tak, racja.";
					link.l1.go = "exit";
					link.l2 = "Chyba będę musiał wybrać inny statek, w takim razie.";
					link.l2.go = "TransferGoods_2";
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("Obawiam się, że statek tego typu po prostu nie pomieści tyle.","Kapitanie, twój statek nie pomieści tyle ładunku!","Kapitanie, ładownia twojego statku nie pomieści tyle ładunku!");
				link.l1 = "Tak, masz rację. Będę musiał wybrać inny statek.";
				link.l1.go = "TransferGoods_2";
				link.l2 = "Zastanawiałem się... Nie potrzebuję nic kupować.";
				link.l2.go = "exit";
			}
			break;
		// <-- Автозакупка товаров

		case "trade_1":
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
			    DialogExit();
			    Pchar.PriceList.StoreManIdx = rColony.index; // boal 27.02.05
			    LaunchStore(sti(rColony.StoreNum));
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar,pcharrepphrase("Żartujesz sobie ze mnie? Gdzie jest twój statek? Nie widzę go przy nabrzeżu!","Przysięgam na diabła, nie oszukasz mnie! Twojego statku nie ma przy nabrzeżu!"),pcharrepphrase("Nie widzę twojego statku w porcie, kapitanie "+GetFullName(pchar)+" Mam nadzieję, że to nie jest 'Latający Holender'?","Kapitanie, znacznie łatwiej załadować towar z nabrzeża. Przyprowadź swój statek szybko i wróć."));
				link.l1 = NPCharRepPhrase(npchar,pcharrepphrase(" "+RandSwear()+"Co za kłopot! Dobrze, stary chytrusie, do zobaczenia wkrótce!","Nie chciałem cię oszukać, "+GetFullName(npchar)+", statek jest po drugiej stronie wyspy."),pcharrepphrase("Nie. Mój statek nazywa się 'Czarna Perła'. Dlaczego zbladłeś? Haha! Tylko żartuję!","Dzięki za radę, skorzystają z niej."));
			    link.l1.go = "exit";//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			}
		break;

		case "storage_0":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar, "Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 
			{
				dialog.text = "Co do czynszu, nadal jesteś mi winien "+FindRussianMoneyString(sti(NPChar.MoneyForStorage))+".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
				{
					link.l1 = "Dobrze, teraz zapłacę za wynajem.";
					link.l1.go = "storage_3";
				}
				else
				{
					link.l1 = "Wracam później.";
					link.l1.go = "exit";
				}
			}		
			else
			{
				dialog.text = "Chodź.";
				link.l1 = "Dziękuję.";
				link.l1.go = "storage_2";
			}
			link.l2 = "Nie, zmieniłem zdanie.";
			link.l2.go = "exit"; 						
		break;
		
		case "storage_01":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "Tak, mam magazyn w porcie - może pomieścić 50000 cetnarów ładunku. Dla "+FindRussianMoneyString(sti(NPChar.MoneyForStorage))+" miesięcznie mogę zapewnić przechowanie twoich towarów. "+"To obejmuje straż, ochronę przed zalaniem i walkę ze szczurami. Co powiesz? Również... potrzebuję miesięcznej zapłaty z góry.";	
			link.l1 = "Strój. Mogę na niego zerknąć? Masz tam wiele szczurów?";
			link.l1.go = "storage_1";
			link.l2 = "Nie, tylko pytam. Mogę z tego skorzystać, gdy zajdzie potrzeba...";
			link.l2.go = "exit";
		break;
		
		case "storage_1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "Jak już mówiłem, żądam zapłaty z góry za miesiąc. I żadnych szczurów!";
			if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = "Jesteś... całkiem kupiecki, muszę przyznać. Oto twoje pieniądze - wynajmę tę szopę.";
				link.l1.go = "storage_11";
			}
			else
			{
				link.l1 = "Jesteś... całkiem kupiecki, muszę przyznać. Dobrze, wrócę wkrótce z pieniędzmi.";
				link.l1.go = "exit";
			}
		break;
		
		case "storage_11":
			AddMoneyToCharacter(pchar, -makeint(NPChar.MoneyForStorage)); 
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			NPChar.Storage.Activate = true;
			Achievment_Set("ach_67"); // ugeen 2016
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;
				
		case "storage_2":			
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;
		
		case "storage_3":			
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage)); 
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar);
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;		

		case "storage_04":
			dialog.text = "Już wychodzisz? Co za szkoda - to naprawdę doskonałe miejsce na świetnych warunkach. Zapewniam cię, że nigdzie indziej na Karaibach nie znajdziesz takiej oferty.";
			link.l1 = "Powiedziałem - zwolnij. Czy sugerujesz, że mam płacić za przechowywanie powietrza? Poszukaj innego najemcy.";
			link.l1.go = "storage_4";
			link.l2 = "Nigdzie na Karaibach, mówisz? Dobrze, odłożę to na jakiś czas, zatem.";
			link.l2.go = "exit";
		break;
		
		case "storage_4":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar,"Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 			
			{
				dialog.text = "A za czynsz, wciąż jesteś mi winien "+FindRussianMoneyString(sti(NPChar.MoneyForStorage))+".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))			
				{
					link.l1 = "Dobrze.";
					link.l1.go = "storage_5";
				}
			}
			else
			{
				dialog.text = "Zbierz swoje towary, a ja zamknę magazyn.";
				link.l1 = "Dobrze.";
				link.l1.go = "storage_6";
			}
		break;
		
		case "storage_5":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage)); 
			NPChar.Storage.NoActivate = true;
			DeleteAttribute(NPChar,"Storage.Activate");
			DialogExit();
		break;
		
		case "storage_6":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			DeleteAttribute(NPChar,"Storage.Activate");
			NPChar.Storage.NoActivate = true;
			DialogExit();
		break;		

		case "business":
			iTest = 0;			
	
	
			//Jason --> генератор Сомнительное предложение
			/*if (hrand(3) == 1 && !CheckAttribute(pchar, "GenQuest.Contraoffer.Trader") && !CheckAttribute(pchar, "GenQuest.Contraoffer.Slaves.Yes") && sti(npchar.nation) != PIRATE && 7-sti(RealShips[sti(pchar.ship.type)].Class) > 0) 
			{
				if (!CheckAttribute(npchar, "Contraoffer") || GetNpcQuestPastDayParam(npchar, "Contraoffer") >= 30) 
				{
					dialog.text = "O! W samą porę, kapitanie. Chciałbym prosić cię o przysługę.";
					link.l1 = "Posłuchajmy."; 
					link.l1.go = "Contraoffer";
					break;
				}
			}
		
			if (CheckAttribute(pchar, "GenQuest.Contraoffer.Trader") && NPChar.location == pchar.GenQuest.Contraoffer.Trader.City + "_store") 
			{
				dialog.text = "Słucham uważnie, kapitanie.";
				link.l5 = "Przyniosłem twoje zamówienie."; 
				link.l5.go = "Contraoffer_check";
			}
			
			if (!CheckAttribute(pchar, "GenQuest.Contraoffer.Slaves") && sti(npchar.quest.Contraoffer.chance) == 2 && GetNpcQuestPastDayParam(npchar, "Contraoffer") >= 30) //единичный вариант за всю игру, ака 'пасхалка'
			{
				dialog.text = "O! Jesteś akurat na czas, kapitanie. Potrzebuję specjalnej przysługi.";
				link.l5 = "Posłuchajmy."; 
				link.l5.go = "Contraoffer_slaves";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Contraoffer.Slaves.Yes") && NPChar.location == pchar.GenQuest.Contraoffer.Slaves.City + "_store") 
			{
				dialog.text = "Zamieniam się w słuch, kapitanie.";
				link.l5 = "Przywiozłem ci niewolników."; 
				link.l5.go = "Contraoffer_slaves_check";
			}*/
			// <-- генератор Сомнительное предложение
	
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_store" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "Słuchaj, handlujesz wszelkiego rodzaju towarami... Czy wczoraj lub dzisiaj ktoś zaoferował ci zakup "+pchar.GenQuest.Device.Shipyarder.Type+"?";
				link.l16.go = "Device_Trader";
			}
			// <-- генератор Неудачливый вор
			
			//Jason --> генератор Место под солнцем
			// belamour legendary edition втречается чаще
			if (!CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && !CheckAttribute(npchar, "quest.Sunplace") && sti(npchar.nation) != PIRATE && sti(pchar.rank) < 20 && hrand(2) == 2 && !CheckAttribute(pchar, "questTemp.Shadowtrader_Block")) 
			{
				dialog.text = "Kapitanie, chciałbym prosić cię o przysługę i jestem gotów sowicie ci zapłacić, jeśli się zgodzisz.";
				link.l1 = "Interesujące. No cóż, w czym problem?"; 
				link.l1.go = "Sunplace_begin";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "complete" && npchar.location == pchar.GenQuest.Sunplace.Trader.City + "_store") 
			{
				dialog.text = "Kapitanie, cieszę się, że cię widzę. Już wiem, że spełniłeś moją prośbę dotyczącą "+pchar.GenQuest.Sunplace.Trader.Enemyname+".";
				link.l1 = "Heh! To na pewno. "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType),"Imię")))+" "+pchar.GenQuest.Sunplace.Trader.ShipName+" i ładunek - "+GetGoodsNameAlt(sti(pchar.GenQuest.Sunplace.Trader.Goods))+", nie należą już do twojego rywala."; 
				link.l1.go = "Sunplace_complete";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "complete_murder" && npchar.location == pchar.GenQuest.Sunplace.Trader.City + "_store") 
			{
				dialog.text = "Mości kapitanie... Czemu go zabiłeś? Prosiłem jedynie, byś zatopił jego statek! Święta Dziewico, teraz mam krew niewinnego człowieka na rękach...";
				link.l1 = "Heh! Co ci dolega, "+npchar.name+"? Kogo to obchodzi - już nigdy więcej ci nie będzie przeszkadzał, i to się liczy!"; 
				link.l1.go = "Sunplace_complete_murder";
				break;
			}
			// <-- генератор Место под солнцем
			
//navy -->
			//занят ПГГ
			iTmp = CheckAvailableTaskForNPC(NPChar, PGG_TASK_WORKONSTORE);
			if (iTmp != -1)
			{
				dialog.text = "Miałem robotę, ale "+GetFullName(&Characters[iTmp])+"już się tego podjął dla mnie.";
				link.l1 = "O, naprawdę? Cóż, wrócę później, zatem.";
				link.l1.go = "exit";
				break;
			}
//navy <--
			dialog.text = NPCharRepPhrase(npchar,"Jaki interes?! Opowiedz mi wszystko!","Słucham. O jakiej umowie mówisz?");
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
            if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
    			if (CheckQuestAttribute("generate_trade_quest_progress", "begin") || CheckQuestAttribute("generate_trade_quest_progress",  "failed"))
    			{
    				if (pchar.CargoQuest.TraderID == npchar.id )
    				{
    					link.l1 = RandPhraseSimple("Mam partię towarów do Twojego sklepu w ładowni mojego statku.","Moja łajba została wynajęta, by dostarczyć towary do twojego sklepu. Towary są teraz rozładowywane.");
    					link.l1.go = "generate_quest_2";
    				}
    				else
    				{
                        if (!CheckQuestAttribute("generate_trade_quest_progress",  "failed") && pchar.CargoQuest.GiveTraderID == npchar.id && GetNationRelation2MainCharacter(sti(characters[GetCharacterIndex(pchar.CargoQuest.TraderID)].nation)) == RELATION_ENEMY)
                        {
                            link.l1 = "Niestety, jestem zmuszony porzucić ich zobowiązania. Sytuacja polityczna nie pozwala mi dostarczyć towarów.";
            				link.l1.go = "generate_quest_cannot_done";
                        }
                        else
                        {
                            if (rand(1) == 1)
                            {
                                link.l1 = RandPhraseSimple("Mogę zaoferować ci czarter mojego statku do przewozu ładunków.","Mam wspaniały statek i mogę dostarczyć każdy ładunek, gdziekolwiek będziesz potrzebował.");
            				    link.l1.go = "generate_quest_not_closed";
        				    }
    				    }
    				}
    			}
    			else
    			{
    				link.l1 = "Czy chciałbyś wynająć statek, "+GetAddress_FormToNPC(NPChar)+" ? Mam niezawodny okręt i doświadczoną załogę.";
    				link.l1.go = "generate_quest";
    			}
				link.l22 = "Jestem tu w innej sprawie.";
				link.l22.go = "quests";
    			// --> на кредитный генератор
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
    			{
	                link.l3 = pcharrepphrase(RandPhraseSimple("Och, naprawdę wyczerpało mnie morze... Cóż, kamracie, pieniądze to dla mnie teraz prawdziwy problem.","Dobrze, stary lisie, porozmawiajmy o naszych sprawach finansowych."),RandPhraseSimple("Chciałbym omówić z tobą kwestie finansowe.","Porozmawiajmy o sprawach finansowych, musimy o nich pomówić."));,
	
	                link.l3.go = "LoanForAll";
                }
				//квест мэра - на связь с нашим шпионом
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") 
				{
					link.l4 = RandPhraseSimple("Jestem tu na prośbę pewnego człowieka. Nazywa się gubernator "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" wysłał mnie do ciebie. Mam coś odebrać...");
					link.l4.go = "IntelligenceForAll";
				}	
				
				//homo 25/06/06 слухи
                link.l6 = pcharrepphrase(RandPhraseSimple("Czy możesz mi powiedzieć najnowsze plotki? I tak cały dzień się tu kręcisz.","Nie rób zamieszania, stary oszuście - lepiej powiedz mi, co nowego na suchym lądzie?"),RandPhraseSimple("Wydaje mi się, że spędziłem wieczność na morzu. Co nowego w waszym regionie?","Zapewne znasz wszystkie najnowsze wieści? Co ważnego się wydarzyło?"));,

    		    link.l6.go = "rumours_trader";

				// ugeen --> склад товаров для ГГ
				if(CheckAttribute(NPChar,"Storage") && Pchar.location.from_sea == "Pirates_town")
				{
					if(CheckAttribute(NPChar,"Storage.Activate"))
					{
						link.l7 = "Zabierz mnie do magazynu. Chcę zobaczyć, w jakim jest stanie.";
						link.l7.go = "storage_0";
						link.l8 = "Zdecydowałem się zwolnić magazyn. Nie potrzebuję go teraz.";
						link.l8.go = "storage_04";
					}
					else
					{
						if(!CheckAttribute(NPChar,"Storage.NoActivate"))
						{
							link.l7 = "Przepraszam, mój dobry człowieku - czy przypadkiem nie wynajmujesz magazynów?";
							link.l7.go = "storage_01";
						}	
					}
				}				
				// <-- ugeen
				// Jason --> квест губера на поиск дезертира
				if(CheckAttribute(pchar, "GenQuest.FindFugitive") && sti(NPChar.nation) == PIRATE)
				{
					link.l8 = "Rozumiesz, próbuję znaleźć mojego towarzysza, "+pchar.GenQuest.FindFugitive.Name+" to jego imię. W Port-Royal ludzie w karczmie mówili mi, że kierował się do waszej osady. Czy przypadkiem go spotkałeś?";
					link.l8.go = "FindFugitiveSt";
				}
				//<-- поиск дезертира
				
				// <-- homo
				link.l99 = "Ale teraz nie ma czasu na rozmowy.";
    			link.l99.go = "no_quests";
			}
			else
			{
                link.l1 = NPCharRepPhrase(npchar,pcharrepphrase(""+RandSwear()+"Zostawiłem statek po drugiej stronie wyspy. Wrócę później!","Proszę o wybaczenie, "+GetFullName(npchar)+"  Przyjdę później. Mój statek jeszcze nie dotarł do przystani."),pcharrepphrase("Diabeł! Te bałwany nie przygotowały statku do załadunku! Wrócę później!","Przepraszam, muszę wydać rozkazy, aby zacumować mój statek przy nabrzeżu!"));
                link.l1.go = "exit";
				link.l22 = "Jestem tu w innej sprawie.";
				link.l22.go = "quests";
    			// --> на кредитный генератор
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
    			{
	                link.l3 = pcharrepphrase(RandPhraseSimple("Och, naprawdę zostałem wyczerpany na morzu... Cóż, kumplu, pieniądze to prawdziwy problem dla mnie w tej chwili.","Dobrze, stary lisie, porozmawiajmy o naszych finansowych sprawach."),RandPhraseSimple("Chciałbym omówić z tobą kwestie finansowe.","Porozmawiajmy o sprawach finansowych, musimy porozmawiać."));,
	
	                link.l3.go = "LoanForAll";
                }
				//квест мэра - на связь с нашим шпионом
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") 
				{
					link.l7 = RandPhraseSimple("Jestem tutaj na prośbę pewnego człowieka. Nazywa się gubernator "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" wysłał mnie do ciebie. Mam odebrać coś...");
					link.l7.go = "IntelligenceForAll";
				}
				// Jason --> квест губера на поиск дезертира
				if(CheckAttribute(pchar, "GenQuest.FindFugitive") && sti(NPChar.nation) == PIRATE)
				{
					link.l8 = "Widzisz, próbuję znaleźć mojego towarzysza, "+pchar.GenQuest.FindFugitive.Name+" to jego imię. W Port-Royal ludzie w tawernie powiedzieli mi, że zmierzał do waszej osady. Czy przypadkiem go spotkałeś?";
					link.l8.go = "FindFugitiveSt";
				}
				//<-- поиск дезертира
			}
		break;
		
		case "generate_quest":
			if (npchar.quest.trade_date != lastspeak_date || bBettaTestMode)
			{
				npchar.quest.trade_date = lastspeak_date;
				//проверка враждебности нам страны торговца
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
					dialog.text = "Nie, nie potrzebuję twoich usług! Przynajmniej dopóki jesteś wrogami z "+NationNameAblative(sti(NPChar.nation))+".";
					link.l1 = "W takim razie, żegnaj.";
					link.l1.go = "exit";
				}
				else
				{
                    // проверка на проф пригодность -->
                    if (isBadReputation(pchar, 42))
                    {
                        dialog.text = RandSwear()+"Jesteś "+GetFullName(pchar)+", nieprawdaż? Mówią, że "+RandPhraseSimple("dużo strasznych rzeczy o tobie","wiele brzydkich rzeczy o tobie")+", a ja nie chcę mieć z tobą do czynienia.";
						link.l1 = RandPhraseSimple("Oczywiście - popełnij błąd raz, a wszyscy chętnie na ciebie spluną.",RandSwear()+"Cóż, na morzu są lepsze rzeczy do roboty, "+GetFullName(npchar)+".");
						link.l1.go = "exit";
                        break;
                    }
                    // проверка на проф пригодность <--
                    int iTradeNation = GenerateNationTrade(sti(NPChar.nation));

					if (iTradeNation < 0)
					{
						dialog.text = NPCharRepPhrase(npchar,"Heh, "+GetAddress_Form(NPChar)+", nie mam dzisiaj czasu na ładunki. Wróć jutro.","Wróć jutro. Być może złożę Ci korzystną ofertę.");
						link.l1 = "Dobrze, wrócę jutro.";
						link.l1.go = "exit";
					}
					else
					{
                        int storeMan = findStoreMan(NPChar, iTradeNation);
                        if (storeMan > 0)
                        {
                            //проверяем импорт/экспорт
							iTradeGoods = GOOD_COFFEE + hrand(sti(GOOD_PAPRIKA - GOOD_COFFEE)); //Jason
    						//проверяем свободное место (при этом должно вмещаться по меньшей мере 100 единиц выбранного груза
    						RecalculateSquadronCargoLoad(pchar); // fix неверное место
    						iQuantityGoods = GetSquadronFreeSpace(pchar, iTradeGoods);
							if (sti(Goods[iTradeGoods].Weight)/sti(Goods[iTradeGoods].Units)*sti(iQuantityGoods) > 1500) iQuantityGoods = makeint(1500/(sti(Goods[iTradeGoods].Weight)/sti(Goods[iTradeGoods].Units))); //Jason: больше 1500 массы не дадим - большие фрахты только через ПУ
    						if (iQuantityGoods < 100)// это в шт. товара
    						{
    							dialog.text = NPCharRepPhrase(npchar,"Twoja nędzna stara łajba nie pomieści całej partii, więc dzisiaj nie będzie transakcji.","Niestety, kapitanie "+GetFullName(pchar)+"Potrzebuję bardziej pojemnego statku do mojego transportu.");
    							link.l1 = NPCharRepPhrase(npchar,"Moja łajba jest przyzwoita, ale rozumiem twój punkt widzenia. Do widzenia.","Widzę twój punkt widzenia, interes to interes. Żegnaj.");
    							link.l1.go = "exit";
    						}
    						else
    						{
    							iQuantityGoods = iQuantityGoods - rand(makeint(iQuantityGoods/3)) - 10;
    							iMoney = makeint((iQuantityGoods * sti(Goods[iTradeGoods].Weight) / sti(Goods[iTradeGoods].Units)) * (4+rand(3) + GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE)) + 0.5);

    							pchar.CargoQuest.iTradeGoods = iTradeGoods;
    							pchar.CargoQuest.iQuantityGoods = iQuantityGoods;
    							pchar.CargoQuest.iMoney = iMoney;
    							pchar.CargoQuest.iTradeNation = iTradeNation;
    							pchar.CargoQuest.iDaysExpired = 25 + rand(5);
    							
    							pchar.CargoQuest.iTradeColony = Characters[storeMan].city;
    							pchar.CargoQuest.iTradeIsland = GetIslandByCityName(Characters[storeMan].city);
    							pchar.CargoQuest.TraderID     = Characters[storeMan].id;
    							pchar.CargoQuest.GiveTraderID = NPChar.id;
                                SaveCurrentQuestDateParam("CargoQuest");
    							string sNation = XI_ConvertString("Colony"+Characters[storeMan].city);
                                sTemp = "";
                                if (pchar.CargoQuest.iTradeIsland != Characters[storeMan].city)
								{
                                    sTemp = ", which is on " + XI_ConvertString(pchar.CargoQuest.iTradeIsland+"Dat");
                                }
                                dialog.text = "O! Właśnie miałem prosić cię o przysługę. Widzisz, muszę dostarczyć ładunek "+GetGoodsNameAlt(iTradeGoods)+" w liczbie "+FindRussianQtyString(iQuantityGoods)+" do miasta "+sNation+sTemp+", a im szybciej, tym lepiej. Jeśli uda ci się to zrobić za "+FindRussianDaysString(makeint(pchar.CargoQuest.iDaysExpired))+", wtedy po przybyciu otrzymasz "+FindRussianMoneyString(iMoney)+"  jako twoja nagroda. Co powiesz?";
    							link.l1 = "Myślę, że się zgadzam.";
    							link.l1.go = "exit_trade";
    							link.l2 = "To chyba nie dla mnie.";
    							link.l2.go = "exit";
    						}
                        }
                        else
                        {
                            dialog.text = "Polityczne realia archipelagu nie pozwalają mi handlować. "+XI_ConvertString(NationShortName(sti(NPChar.nation))+"myśliwy")+" jest wrogo nastawiony do wszystkich i zostawił tylko mnie w sklepie.";
    						link.l1 = "Och! Przepraszam. Powodzenia.";
    						link.l1.go = "exit";
                        }
					}
				}
			}
			else
			{
				dialog.text = NPCharRepPhrase(npchar,"Zjeżdżaj, nie mam czasu na próżne gadanie!","Już mówiłem ci, że nie mam dla ciebie niczego.");
				link.l1 = NPCharRepPhrase(npchar,"Musisz być grzeczny, bo inaczej nauczę cię manier!","O, przepraszam!");
				link.l1.go = "exit";
			}
		break;

		case "exit_trade":
			AddDialogExitQuest("trade_quest_open");
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
		break;

		case "generate_quest_2":
			if (pchar.quest.generate_trade_quest_progress == "failed")
			{
				dialog.text = RandSwear()+"Czy nie sądzisz, że przypomniałeś sobie o tej umowie trochę za późno? Musiałem zamówić towar ponownie. Żegnaj.";
				link.l1 = "Przebacz mi, ale byłem w pośpiechu. Może jeśli pokryję twoje straty, moja reputacja zostanie przywrócona?";
				link.l1.go = "generate_quest_failed";
				link.l9 = "Wszystkiego najlepszego.";
				link.l9.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", -1);
			}
			else
			{
                iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
                iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
                
                dialog.text = "Rzeczywiście! Czekałem na to już od pewnego czasu. Musisz dostarczyć mi ładunek "+GetGoodsNameAlt(iTradeGoods)+" w ilości "+FindRussianQtyString(iQuantityGoods)+" i otrzymać za to "+FindRussianMoneyString(sti(pchar.CargoQuest.iMoney))+".";
				link.l1 = "Dokładnie.";
				link.l1.go = "generate_quest_ready";
			}
		break;
		
		case "generate_quest_ready":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            // блок кидалова нас на бабки -->
            if (rand(8) == 1 && sti(Goods[iTradeGoods].Cost) <= 44 && GetQuestPastDayParam("CargoQuest") > 5)
            {
                dialog.text = RandSwear()+"Muszę cię przeprosić, "+GetAddress_Form(NPChar)+"  Widzisz, problem polega na tym, że byłem "+RandPhraseSimple("w kłopotliwej sytuacji i nie będę w stanie ci zapłacić"," już kupiłem ten ładunek od innego sprzedawcy za lepszą cenę")+"Jako zapłatę za twój czarter proponuję, abyś zatrzymał cały ładunek, który dostarczałeś.";
				link.l1 = RandSwear()+RandPhraseSimple("I chroniłem ten cholerny ładunek przed wszelkim niebezpieczeństwem! Zabiłem przez niego dwieście szczurów!","Wprowadziłeś mnie w patową sytuację, więc będę musiał się zgodzić.");
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", 2);
				AddCharacterExpToSkill(pchar, "Sailing", 60);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				AddCharacterExpToSkill(pchar, "COMMERCE", 15);

				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
                
                AddQuestRecord("DELIVERY_TRADE_QUEST", "4");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen")); // belamour gen
                CloseQuestHeader("DELIVERY_TRADE_QUEST");
                break;
            }
            // блок кидалова нас на бабки <--
			if (GetSquadronGoods(pchar, iTradeGoods) < iQuantityGoods)
			{
                iTmp = iQuantityGoods - GetSquadronGoods(pchar, iTradeGoods);
                dialog.text = "To nie cała partia! Według naszej umowy potrzebuję "+FindRussianQtyString(iTmp)+" jednostek więcej.";
				link.l9 = RandPhraseSimple("Tak, rzeczywiście. Będę musiał zrekompensować niedobór. Do zobaczenia później.",RandSwear()+"Te przeklęte szczury zepsuły ładunek. Zrekompensuję brak i wrócę ponownie.");
				link.l9.go = "exit";
                AddQuestRecord("DELIVERY_TRADE_QUEST", "8");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sHaveNotQty", iTmp);
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			}
			else
			{
                dialog.text = "Doskonale! Oto twoja nagroda, kapitanie "+GetFullName(pchar)+".";
				link.l1 = "Z przyjemnością z tobą współpracowałem.";
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", 3);
				AddCharacterExpToSkill(pchar, "Sailing", 100);
				AddCharacterExpToSkill(pchar, "Leadership", 30);
				AddCharacterExpToSkill(pchar, "COMMERCE", 100);

				AddMoneyToCharacter(pchar, makeint(pchar.CargoQuest.iMoney));
				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
				RemoveCharacterGoods(pchar, makeint(pchar.CargoQuest.iTradeGoods), makeint(pchar.CargoQuest.iQuantityGoods));
				
                OfficersReaction("good");
                
                AddQuestRecord("DELIVERY_TRADE_QUEST", "2");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
                CloseQuestHeader("DELIVERY_TRADE_QUEST");
			}
		break;
		
		case "generate_quest_failed":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            iMoney =  3*makeint(iQuantityGoods * sti(Goods[iTradeGoods].Cost) / sti(Goods[iTradeGoods].Units));
			dialog.text = "Dobrze... Suma "+FindRussianMoneyString(iMoney)+" pokryje tylko szkody spowodowane naruszeniem warunków naszej umowy.";
			link.l1 = "O rety! Nie, to nie przejdzie! Nigdy więcej nie będę dostarczał żadnego ładunku! Tego szmelcu na morzu jest wystarczająco dużo!";
			link.l1.go = "exit";
            if (sti(pchar.Money) >= iMoney)
            {
    			link.l2 = "Oto wymagana kwota";
    			link.l2.go = "generate_quest_failed_2";
			}
            else
            {
                AddQuestRecord("DELIVERY_TRADE_QUEST", "7");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sMoney", FindRussianMoneyString(iMoney));
    		    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
            }
		break;
		
		case "generate_quest_failed_2":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            iMoney =  3*makeint(iQuantityGoods * sti(Goods[iTradeGoods].Cost) / sti(Goods[iTradeGoods].Units));
			dialog.text = "Doskonale. Teraz mogę powiedzieć moim kolegom, że nadal można się z tobą rozsądnie dogadać.";
			link.l1 = "Dziękuję! Nie zawiodę cię ponownie.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			AddCharacterExpToSkill(pchar, "Sailing", -100);
			AddCharacterExpToSkill(pchar, "Leadership", -50);
			AddCharacterExpToSkill(pchar, "COMMERCE", -100);

			AddMoneyToCharacter(pchar, -iMoney);
			pchar.quest.generate_trade_quest_progress = "";
			pchar.quest.generate_trade_quest.over = "yes";

            AddQuestRecord("DELIVERY_TRADE_QUEST", "5");
            AddQuestUserData("DELIVERY_TRADE_QUEST", "sMoney", FindRussianMoneyString(iMoney));
            AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
		    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
            CloseQuestHeader("DELIVERY_TRADE_QUEST");
		break;
		
		case "generate_quest_not_closed":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);

            dialog.text = "Hmm. Słyszałem, że nie wywiązałeś się z obowiązków określonych w poprzednim kontrakcie - a teraz prosisz o kolejny? Musiałeś dostarczyć ładunek "+LanguageConvertString(iSeaGoods,"seg_"+Goods[iTradeGoods].Name)+" do "+XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony)+".";
			link.l1 = "Tak, rzeczywiście! Masz rację!";
			link.l1.go = "exit";
		break;
		
		case "generate_quest_cannot_done":
            dialog.text = RandSwear()+GetAddress_Form(NPChar)+", zawiodłeś mnie!!! Może zrobisz coś, aby rozwiązać ten problem?";
			link.l1 = "Dobrze. Zrobię co w mojej mocy, by dostarczyć ładunek.";
			link.l1.go = "exit";
			link.l2 = "Nie, nie mogę. Przykro mi.";
			link.l2.go = "generate_quest_cannot_done_2";
			
		break;
		
		case "generate_quest_cannot_done_2":
		    iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            if (GetSquadronGoods(pchar, iTradeGoods) < iQuantityGoods)
			{
				dialog.text = "Zaczekaj! Na pokładzie twojego statku nie ma wystarczającej ilości towarów! Nie masz "+FindRussianQtyString(iQuantityGoods - GetSquadronGoods(pchar,iTradeGoods))+"jednostek ładunku.";
				link.l9 = RandPhraseSimple("Tak, rzeczywiście. Będę musiał zrekompensować ten niedobór.",RandSwear()+"Szczury zepsuły ładunek. Kupię brakującą ilość i wrócę ponownie.");
				link.l9.go = "exit";
			}
			else
			{
                dialog.text = "Rozumiem, rozumiem... Przyjmę przesyłkę z powrotem.";
    			link.l1 = "Dziękuję! Nie zawiodę Cię ponownie!";
    			link.l1.go = "exit";
    			ChangeCharacterComplexReputation(pchar,"nobility", -3);

				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
				RemoveCharacterGoods(pchar, makeint(pchar.CargoQuest.iTradeGoods), makeint(pchar.CargoQuest.iQuantityGoods));
                
                AddQuestRecord("DELIVERY_TRADE_QUEST", "6");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodQty", FindRussianQtyString(sti(pchar.CargoQuest.iQuantityGoods)));
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
    		    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen")); // belamour gen
                CloseQuestHeader("DELIVERY_TRADE_QUEST");
            }
		break;
	
//Jason --> мини-квест Дефицитный товар
		case "Wine_Trader":
			dialog.text = "O czym ty mówisz? Wyraźnie cię wprowadzono w błąd - nigdy nie handlowałem europejskim winem w takich ilościach. Jedna-dwie butelki, nie więcej. Ale lokalne wino to inna historia - mam tego pod dostatkiem i jest sprzedawane w gąsiorach, nie butelkach!";
			link.l1 = "Do diabła! Ale powiedziano mi...";
			link.l1.go = "Wine_Trader_1";
		break;
		
		case "Wine_Trader_1":
			dialog.text = "Nie mam pojęcia, co ci powiedziano, ale powiem to jeszcze raz: nie mam w zapasach europejskiego wina. To wszystko, co mam do powiedzenia w tej sprawie.";
			link.l1 = "Dobrze... To ja się tym zajmę, zatem!";
			link.l1.go = "exit";
			AddQuestRecord("Wine", "5");
			AddQuestUserData("Wine", "sName", pchar.questTemp.Wine.Name);
			DeleteAttribute(pchar, "questTemp.Wine.Trader");
			pchar.questTemp.Wine.Repeat1 = "true";
		break;
		
		case "Wine_Repeat2":
			RemoveItems(PChar, "letter_1", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "To już inna historia. Wiesz, różne typy przychodzą tutaj, zadając niepotrzebne pytania. Więc, potargujmy się, co?";
			link.l1 = "Pewnie!";
			link.l1.go = "Wine_Price";
			pchar.questTemp.Wine.wait = "true";
			DeleteAttribute(pchar, "questTemp.Wine.Repeat2");
			SetFunctionTimerCondition("Wine_wait", 0, 0, 7, false);
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId(pchar.questTemp.Wine.ItemTraderID), "questmarkmain");
		break;
		
		case "Wine_Price":
			dialog.text = "Ile butelek potrzebujesz? Cena jednej butelki to 500 pesos, a minimalna partia to 20 butelek.";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "Wine_Qty";
			link.l2 = "Nie mam teraz wystarczająco pieniędzy. Wrócę później.";
			link.l2.go = "Wine_Qty_exit";
		break;
		
		case "Wine_Qty":
			int iQty = sti(dialogEditStrings[4]);
			pchar.questTemp.Wine.Qty = sti(iQty);
			if (iQty < 20)
			{
				dialog.text = "Nie jestem domokrążcą, kapitanie. O ile pamiętam, mówiliście o większej partii?";
				link.l1 = "Przykro mi... Rozważmy zatem ponownie tę kwotę.";
				link.l1.go = "Wine_Price";
				break;
			}
			if (iQty > 70)
			{
				dialog.text = "Niestety, nie mam tyle.";
				link.l1 = "Szkoda... Zastanówmy się zatem nad kwotą ponownie.";
				link.l1.go = "Wine_Price";
				break;
			}
			pchar.questTemp.Wine.Summ = sti(iQty)*500;
			dialog.text = ""+sti(iQty)+" Butelki? Dobrze. To będzie cię kosztować "+FindRussianMoneyString(sti(pchar.questTemp.Wine.Summ))".";
			if (makeint(Pchar.money) >= sti(pchar.questTemp.Wine.Summ))
			{
				link.l1 = "Oto i proszę.";
				link.l1.go = "Wine_Qty_1";
			}
			link.l2 = "Nie mam teraz wystarczająco pieniędzy. Wrócę później.";
			link.l2.go = "Wine_Qty_exit";
		break;
		
		case "Wine_Qty_exit":
			dialog.text = "To w porządku, ale postaraj się nie przeciągać. Te rzeczy są tu dość popularne.";
			link.l1 = "Zaraz wrócę!";
			link.l1.go = "exit";
		break;
		
		case "Wine_Qty_1":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Wine.Summ));
			dialog.text = "Zobaczmy... Wszystko wydaje się w porządku. Możesz odebrać swój zakup.";
			link.l1 = "Dziękuję! Powodzenia!";
			link.l1.go = "Wine_Qty_2";
		break;
		
		case "Wine_Qty_2":
			pchar.quest.Wine_wait.over = "yes";//снять прерывание
			DeleteAttribute(pchar, "questTemp.Wine.wait");
			TakeNItems(pchar, "potionwine", sti(pchar.questTemp.Wine.Qty));
			PlaySound("interface\important_item.wav");
			Log_Info ("You have received wine");
			AddQuestRecord("Wine", "8");
			DelLandQuestMark(npchar);
			DialogExit();
		break;
		// <-- мини-квест Дефицитный товар
		
// Jason --> -------------------------генератор Сомнительное предложение----------------------------------------
		int iCGood, amount;
		case "Contraoffer":
			pchar.GenQuest.Contraoffer.Trader.Goods = SelectContrabandGoods(pchar);
			while (sti(pchar.GenQuest.Contraoffer.Trader.Goods) == -1)
			{
				pchar.GenQuest.Contraoffer.Trader.Goods = SelectContrabandGoods(pchar);
			}
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			pchar.GenQuest.Contraoffer.Trader.Qty = makeint(15*(sti(pchar.rank)+30)/(sti(Goods[iCGood].Weight)/sti(Goods[iCGood].Units))*(8-sti(RealShips[sti(pchar.ship.type)].Class)));//количество
			pchar.GenQuest.Contraoffer.Trader.Price = sti(Goods[iCGood].Cost)/sti(Goods[iCGood].Units)*3;//цена единицы товара
			pchar.GenQuest.Contraoffer.Trader.Summ = sti(pchar.GenQuest.Contraoffer.Trader.Price)*sti(pchar.GenQuest.Contraoffer.Trader.Qty);//сумма
			pchar.GenQuest.Contraoffer.Trader.Days = 30+hrand(20);//срок
			pchar.GenQuest.Contraoffer.Trader.Chance = rand(5);//17% вероятности, что патруль накроет
			dialog.text = "Planowałem ubić dobry interes, lecz wciąż potrzebuję pewnego towaru do tego - "+GetGoodsNameAlt(iCGood)+"Problem w tym, że ten towar to kontrabanda w naszej kolonii, więc nie mogę liczyć na zakup od kapitanów handlowych\nWszystko, czego potrzebuję, to "+FindRussianQtyString(sti(pchar.GenQuest.Contraoffer.Trader.Qty))+" jednostek tego. Może mógłbyś mi to dostarczyć? Dobrze ci zapłacę, "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Price))+" za jednostkę, co wyniesie "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ))+", A potrzebuję tego nie później niż za "+FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Trader.Days))+"Więc, pomożesz mi?";
			link.l1 = "Hmm... Brzmi interesująco. Zgadzam się!";
			link.l1.go = "Contraoffer_1";
			link.l2 = "Przemycanie towarów? Przykro mi, nie jestem zainteresowany.";
			link.l2.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "Contraoffer");
		break;
		
		case "Contraoffer_1":
			dialog.text = "Doskonale. Cieszę się, że się zgodziłeś. W takim razie będę oczekiwał Twojego powrotu z towarem.";
			link.l1 = "Za chwilę wrócę!";
			link.l1.go = "exit";
			rColony = GetColonyByIndex(FindColony(npchar.city));
			SetNull2StoreGood(rColony, sti(pchar.GenQuest.Contraoffer.Trader.Goods));//нулим товар
			pchar.GenQuest.Contraoffer = "begin";
			pchar.GenQuest.Contraoffer.Trader = "true";
			pchar.GenQuest.Contraoffer.Trader.City = npchar.city;
			pchar.GenQuest.Contraoffer.Trader.Nation = npchar.nation;
			iCGood = pchar.GenQuest.Contraoffer.Trader.Goods;
			ReOpenQuestHeader("Contraoffer");
			AddQuestRecord("Contraoffer", "1");
			AddQuestUserData("Contraoffer", "sGoods", GetGoodsNameAlt(iCGood));
			AddQuestUserData("Contraoffer", "sGoodQty", FindRussianQtyString(sti(pchar.GenQuest.Contraoffer.Trader.Qty)));
			AddQuestUserData("Contraoffer", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ)));
			AddQuestUserData("Contraoffer", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Contraoffer.Trader.City+"Gen"));
			AddQuestUserData("Contraoffer", "sDays", FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Trader.Days)));
			SetFunctionTimerCondition("Contraoffer_Over", 0, 0, sti(pchar.GenQuest.Contraoffer.Trader.Days), false);
		break;
		
		case "Contraoffer_check":
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			amount = sti(pchar.GenQuest.Contraoffer.Trader.Qty) - GetSquadronGoods(pchar, sti(pchar.GenQuest.Contraoffer.Trader.Goods));
			if (amount > 0)
			{
				dialog.text = "Żartujesz? Nie masz pełnej ilości towarów, których potrzebuję!";
				link.l1 = "Przepraszam, moja wina...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Zobaczmy zatem. Miałeś dostarczyć ładunek "+GetGoodsNameAlt(iCGood)+"w ilości"+FindRussianQtyString(pchar.GenQuest.Contraoffer.Trader.Qty)+". Zgadza się?";
				link.l1 = "Dokładnie, "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "Contraoffer_pay";
			}
		break;
		
		case "Contraoffer_pay":
			dialog.text = "Dziękuję za wykonaną pracę. Proszę, weź swoją zapłatę - "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ))+".";
		link.l1 = "Dziękuję! Z przyjemnością robię z tobą interesy.";
		link.l1.go = "Contraoffer_complete";
		break;
		
		case "Contraoffer_complete":
			pchar.quest.Contraoffer_Over.over = "yes";
			RemoveCharacterGoods(pchar, sti(pchar.GenQuest.Contraoffer.Trader.Goods), sti(pchar.GenQuest.Contraoffer.Trader.Qty));
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Contraoffer.Trader.Summ));
			SaveCurrentNpcQuestDateParam(npchar, "Contraoffer");
			npchar.quest.Contraoffer.chance = rand(2);//личный шанс торговца для 'пасхалки'
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 100);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			if (pchar.GenQuest.Contraoffer.Trader.Chance == 3)
			{
				dialog.text = "Och... Kapitanie, wygląda na to, że mamy tu problem...";
				link.l1 = "Cóż to znowu?";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("Contraoffer_Patrol");
				pchar.GenQuest.Contraoffer.Trader.busy = "true";
				pchar.quest.Contraoffer_busy.win_condition.l1 = "ExitFromLocation";
				pchar.quest.Contraoffer_busy.win_condition.l1.location = pchar.location;
				pchar.quest.Contraoffer_busy.function = "Trader_free";
			}
			else
			{
				DialogExit();
				AddQuestRecord("Contraoffer", "3");
				CloseQuestHeader("Contraoffer");
				DeleteAttribute(pchar, "GenQuest.Contraoffer.Trader");
			}
		break;
		
		case "Contraoffer_slaves"://единичный вариант за всю игру, ака 'пасхалка'
			pchar.GenQuest.Contraoffer.Slaves.Name = GetFullName(npchar);
			pchar.GenQuest.Contraoffer.Slaves.Price = 300;//цена на рабов, пока фиксированная, можно подставить формулу
			pchar.GenQuest.Contraoffer.Slaves.Qty = 300+rand(50);//количество
			pchar.GenQuest.Contraoffer.Slaves.Days = 14+rand(6);//срок
			pchar.GenQuest.Contraoffer.Slaves.Money = sti(pchar.GenQuest.Contraoffer.Slaves.Qty)*sti(pchar.GenQuest.Contraoffer.Slaves.Price);
			dialog.text = "Pilnie potrzebuję partii niewolników - "+sti(pchar.GenQuest.Contraoffer.Slaves.Qty)+"  głowy. Jestem gotów zapłacić "+sti(pchar.GenQuest.Contraoffer.Slaves.Price)+" monet za duszę, co da w sumie "+sti(pchar.GenQuest.Contraoffer.Slaves.Money)+" pesos in total; term - "+FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Slaves.Days))+".";
			link.l1 = "Myślę, że się zgodzę. To kłopotliwy, ale bardzo dochodowy interes.";
			link.l1.go = "Contraoffer_slaves_1";
			link.l2 = "Nie jestem zainteresowany.";
			link.l2.go = "exit";
			pchar.GenQuest.Contraoffer.Slaves = "begin";
		break;
		
		case "Contraoffer_slaves_1":
			dialog.text = "Dokładnie - to rzeczywiście bardzo opłacalne. Cóż, zatem będę czekać na twój powrót z moimi niewolnikami.";
			link.l1 = "Nie każę ci długo czekać. Do zobaczenia!";
			link.l1.go = "exit";
			pchar.GenQuest.Contraoffer.Slaves.Yes = "begin";
			pchar.GenQuest.Contraoffer.Slaves.City = npchar.city;
			ReOpenQuestHeader("Contraoffer");
			AddQuestRecord("Contraoffer", "4");
			AddQuestUserData("Contraoffer", "sDays", FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Slaves.Days)));
			AddQuestUserData("Contraoffer", "sGoodQty", FindRussianQtyString(sti(pchar.GenQuest.Contraoffer.Slaves.Qty)));
			AddQuestUserData("Contraoffer", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Slaves.Money)));
			AddQuestUserData("Contraoffer", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Contraoffer.Slaves.City+"Gen"));
			SetFunctionTimerCondition("Contraoffer_Over", 0, 0, sti(pchar.GenQuest.Contraoffer.Slaves.Days), false);
		break;
		
		case "Contraoffer_slaves_check":
			amount = sti(pchar.GenQuest.Contraoffer.Slaves.Qty) - GetSquadronGoods(pchar, GOOD_SLAVES);
			if (amount > 0)
			{
				dialog.text = "Żartujesz? Nie masz wszystkich niewolników, których potrzebuję!";
				link.l1 = "Przepraszam, moja wina...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Zobaczmy więc. Miałeś dostarczyć mi partię niewolników w ilości "+FindRussianQtyString(pchar.GenQuest.Contraoffer.Slaves.Qty)+". Zgadza się?";
				link.l1 = "Dokładnie, "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "Contraoffer_slaves_pay";
			}
		break;
		
		case "Contraoffer_slaves_pay":
			dialog.text = "Dzięki za twoją pracę. Proszę, weź swoją zapłatę - "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Slaves.Money))+"Również, proszę przyjąć to. Jestem pewien, że uznasz to za przydatne.";
			link.l1 = "Dziękuję! Przyjemność robić z tobą interesy.";
			link.l1.go = "Contraoffer_slaves_complete";
		break;
		
		case "Contraoffer_slaves_complete":
			DialogExit();
			pchar.quest.Contraoffer_Over.over = "yes";
			RemoveCharacterGoods(pchar, GOOD_SLAVES, sti(pchar.GenQuest.Contraoffer.Slaves.Qty));
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Contraoffer.Slaves.Money));
			AddQuestRecord("Contraoffer", "5");
			CloseQuestHeader("Contraoffer");
			SaveCurrentNpcQuestDateParam(npchar, "Contraoffer");
			AddCharacterExpToSkill(pchar, "Sailing", 150);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 200);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 150);//везение
			TakeNItems(pchar, "cirass3", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			DeleteAttribute(pchar, "GenQuest.Contraoffer.Slaves.Yes");
		break;
		// <-- генератор Сомнительное предложение
		
		//Jason --> генератор Неудачливый вор
		case "Device_Trader":
			dialog.text = "Hmm, "+pchar.GenQuest.Device.Shipyarder.Type+"? Nigdy wcześniej o tym nie słyszałem... Czym to właściwie jest? Nigdy o czymś takim nie słyszałem przez cały ten czas.";
			link.l1 = "Cóż, to narzędzie szkutnicze, "+pchar.GenQuest.Device.Shipyarder.Describe+"Czy ktoś oferował ci coś takiego?";
			link.l1.go = "Device_Trader_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Trader_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) == 0)
			{
				dialog.text = "Hmm... Tak, był tu jeden dziwny gość. Ale nie powiedział mi, co to było, po prostu próbował mi to sprzedać. Ale po co mi to, skoro nie mam pojęcia, do czego to służy? Jak mógłbym to odsprzedać? Więc po prostu odmówiłem.";
				link.l1 = "I jak on wyglądał i dokąd poszedł? Bardzo potrzebuję tego instrumentu.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "Nie, nic takiego. Przykro mi, nie mogę ci pomóc. Popytaj w okolicy.";
				link.l1 = "Rozumiem. Cóż - czas popytać!";
				link.l1.go = "exit";
			}
		break;
		// <-- генератор Неудачливый вор

		//Jason --> генератор Место под солнцем
		case "Sunplace_begin":
			dialog.text = "Konkurencja... Bez niej nie ma interesów. Chciwi dranie, którzy starają się wedrzeć w twój przytulny interes i używają wszelkiego rodzaju nikczemnych metod, by przyciągnąć klientów do siebie.\nAle to tylko słowa. A tak naprawdę chciałbym cię poprosić, abyś pomógł mi pozbyć się jednego z moich konkurentów. Nie, nie trzeba go zabijać. Po prostu przechwyć lub zatop jego statek z ładunkiem.";
			link.l1 = "Hmm... cóż, jeśli dobrze płacisz, mogę to załatwić.";
			link.l1.go = "Sunplace_1";
			link.l2 = "Nie, nie wtrącam się w wasze handlowe spory. Idź zatopić swego rywala bez mojej pomocy.";
			link.l2.go = "Sunplace_exit";
		break;
		
		case "Sunplace_exit"://если отказал - этот непись больше никогда не даст
			npchar.quest.Sunplace = "true";
			DialogExit();
		break;
		
		case "Sunplace_1":
			GetSunplaceShore();//бухта и остров
			pchar.GenQuest.Sunplace.Trader.Enemyname = GenerateRandomName_Generator(sti(npchar.nation), "man");//имя конкурента
			pchar.GenQuest.Sunplace.Trader.Nation = npchar.nation;//нация общая для торговца и конкурента
			pchar.GenQuest.Sunplace.Trader.City = npchar.City;//город квестодателя
			pchar.GenQuest.Sunplace.Trader.CityT = findSunplaceCity(NPChar);//город конкурента
			pchar.GenQuest.Sunplace.Trader.Shiptype = Sunplace_Shiptype();//тип корабля
			pchar.GenQuest.Sunplace.Trader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));//имя корабля
			pchar.GenQuest.Sunplace.Trader.DaysQty = 5 + hrand(5);//дни
			pchar.GenQuest.Sunplace.Trader.Money = sti(pchar.GenQuest.Sunplace.Trader.Shiptype)*3000;//оплата
			pchar.GenQuest.Sunplace.Trader.Goods = GOOD_COFFEE + hrand(sti(GOOD_PAPRIKA - GOOD_COFFEE));//товар
			dialog.text = "Bardzo dobrze. A więc, imię twojego człowieka to "+pchar.GenQuest.Sunplace.Trader.Enemyname+" Niedawno wysłał "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType),"Imię")+"Rachunek"))+"'"+pchar.GenQuest.Sunplace.Trader.ShipName+" z ładunkiem "+GetGoodsNameAlt(sti(pchar.GenQuest.Sunplace.Trader.Goods))+"Zapłacił całkiem przyzwoitą sumę za ten ładunek, więc jego utrata będzie sporym ciosem dla jego sakiewki.";
			link.l1 = "A mógłbyś mi powiedzieć, gdzie dokładnie szukać tego 'przyjaciela'?";
			link.l1.go = "Sunplace_2";
		break;
		
		case "Sunplace_2":
			dialog.text = "Mój 'przyjaciel' jest obecnie w swoim domu w "+XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.CityT+"Voc")+". Nie potrzebujesz jego - potrzebujesz jego statku, który, jak się dowiedziałem po około "+FindRussianDaysString(sti(pchar.GenQuest.Sunplace.Trader.DaysQty))+" będzie przepływać w pobliżu "+XI_ConvertString(pchar.GenQuest.Sunplace.Trader.Shore+"Gen")+". Możesz go zatopić, możesz zdobyć przez abordaż - to nie ma znaczenia. Najważniejsze, aby statek i ładunek nie były już własnością "+pchar.GenQuest.Sunplace.Trader.Enemyname+". I nie obchodzi mnie, kto to zgarnie - ty czy morze. Za tę robotę zapłacę ci "+FindRussianMoneyString(sti(pchar.GenQuest.Sunplace.Trader.Money))".";
			link.l1 = "Zrozumiałem. Cóż, czas ruszać!";
			link.l1.go = "Sunplace_3";
		break;
		
		case "Sunplace_3":
			DialogExit();
			pchar.GenQuest.Sunplace.Trader = "true";
			if (sti(pchar.GenQuest.Sunplace.Chance) == 1 && sti(pchar.rank) > 9) pchar.GenQuest.Sunplace.Bonus = "true";
			ReOpenQuestHeader("Sunplace");
			AddQuestRecord("Sunplace", "1");
			AddQuestUserData("Sunplace", "sGoods", GetGoodsNameAlt(sti(pchar.GenQuest.Sunplace.Trader.Goods)));
			AddQuestUserData("Sunplace", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)));
			AddQuestUserData("Sunplace", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Sunplace.Trader.Money)));
			AddQuestUserData("Sunplace", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.City+"Gen"));
			AddQuestUserData("Sunplace", "sType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType), "Name") + "Acc")));
			AddQuestUserData("Sunplace", "sSName", pchar.GenQuest.Sunplace.Trader.ShipName);
			AddQuestUserData("Sunplace", "sName", GetFullName(npchar));
			AddQuestUserData("Sunplace", "sShore", XI_ConvertString(pchar.GenQuest.Sunplace.Trader.Shore+"Gen"));
			SetFunctionTimerCondition("Sunplace_Over", 0, 0, sti(pchar.GenQuest.Sunplace.Trader.DaysQty), false);
			pchar.quest.Sunplace_Trader.win_condition.l1 = "location";
			pchar.quest.Sunplace_Trader.win_condition.l1.location = pchar.GenQuest.Sunplace.Trader.Island;
			pchar.quest.Sunplace_Trader.win_condition.l2 = "Timer";
			pchar.quest.Sunplace_Trader.win_condition.l2.date.hour  = sti(GetTime());
			pchar.quest.Sunplace_Trader.win_condition.l2.date.day   = GetAddingDataDay(0, 0, makeint(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)-2));
			pchar.quest.Sunplace_Trader.win_condition.l2.date.month = GetAddingDataMonth(0, 0, makeint(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)-2));
			pchar.quest.Sunplace_Trader.win_condition.l2.date.year  = GetAddingDataYear(0, 0, makeint(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)-2));
			pchar.quest.Sunplace_Trader.function = "Sunplace_CreateTraderShip";
		break;
		
		case "Sunplace_complete":
			dialog.text = "Doskonale! Wiedziałem, że mogę na ciebie liczyć. Myślę, że nie będę pytał o miejsce pobytu tego statku i ładunku. To w końcu nie moja sprawa. A mój przyjaciel będzie potrzebował sporo czasu, by dojść do siebie po takim ciosie, he-he. Proszę, weź swoje pieniądze - i dziękuję za świetną robotę.";
			link.l1 = "Proszę bardzo... Do zobaczenia, "+npchar.name+"!";
			link.l1.go = "Sunplace_complete_1";
		break;
		
		case "Sunplace_complete_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Sunplace.Trader.Money));
			AddQuestRecord("Sunplace", "12");
			CloseQuestHeader("Sunplace");
			pchar.GenQuest.Sunplace.Chance = rand(2);
			AddComplexSeaExpToScill(50, 50, 50, 50, 50, 0, 0);
			AddComplexSelfExpToScill(20, 20, 20, 20);
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			DeleteAttribute(pchar, "GenQuest.Sunplace.Trader");
			DialogExit();
		break;
		
		case "Sunplace_complete_murder":
			dialog.text = "Biedny "+pchar.GenQuest.Sunplace.Trader.Enemyname+", cóż za okrutny los! I choć pośrednio, to ja jestem przyczyną jego śmierci! Nie rozumiesz, kapitanie! Czy prosiłem cię, byś go zabił? Planowałem, że po stracie pieniędzy wydanych na ładunek znów będzie musiał... cóż, nieważne... Ty...";
			link.l1 = "Ej, słuchaj - przestań jęczeć, dobra? Poprosiłeś mnie, żebym uwolnił cię od rywala - zrobiłem to. Jeszcze lepiej - tracąc ładunek, mógłby jeszcze się wzbogacić i nadal szkodzić twojemu interesowi. Teraz niewiele może zrobić, będąc martwym.";
			link.l1.go = "Sunplace_complete_murder_1";
		break;
		
		case "Sunplace_complete_murder_1":
			dialog.text = "Dość tego! Wystarczy! Nie chcę więcej słyszeć tych bluźnierczych przemów! Weź swoje przeklęte pieniądze i natychmiast opuść mój sklep!";
			link.l1 = "Hej, "+npchar.name+", uspokój się, dobrze? Albo sam cię ostudzę - moja szabla zawsze jest przy mnie! Dobra, nie bój się, tylko żartowałem. Słuchaj, przepraszam, że tak wyszło - ale to ty mnie na początku wprowadziłeś w błąd. Żegnaj.";
			link.l1.go = "Sunplace_complete_murder_2";
		break;
		
		case "Sunplace_complete_murder_2":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Sunplace.Trader.Money));
			AddQuestRecord("Sunplace", "13");
			AddQuestUserData("Sunplace", "sName", GetFullName(npchar));
			CloseQuestHeader("Sunplace");
			npchar.quest.Sunplace = "true";//этот непись повторно квест больше не даст
			AddComplexSeaExpToScill(50, 50, 50, 50, 50, 0, 0);
			AddComplexSelfExpToScill(30, 30, 30, 30);
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			DeleteAttribute(pchar, "GenQuest.Sunplace.Trader");
			DialogExit();
		break;
		
		//Jason --> поиск дезертира
		case "FindFugitiveSt":
			if (NPChar.city == pchar.GenQuest.FindFugitive.City && sti(pchar.GenQuest.FindFugitive.Chance) == 1)
			{
				dialog.text = NPCStringReactionRepeat(" "+pchar.GenQuest.FindFugitive.Name+"? Tak, znam go. Kupił u mnie zapasy dla swojej długiej łodzi. W ciągu dnia zazwyczaj łowi ryby gdzieś w zacisznych zatokach, ale każdego wieczoru można go znaleźć w tawernie.","Już pytałeś mnie o tego człowieka, i powiedziałem ci wszystko, co wiedziałem!","Czy sobie ze mnie żartujesz, czy naprawdę jesteś idiotą?! Zadajesz już po raz trzeci te same pytania!","Jak to możliwe, że taki głupiec został kapitanem...","blokada",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Dziękuję, ogromnie mi pomogłeś!","Tak, tak, dobrze.","Teraz, teraz, nie ekscytuj się tak. Po prostu zapomniałem.","No cóż, zrobił to, jak widzisz...",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("FindFugitiveSt_1", "exit", "", "", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = NPCStringReactionRepeat("Nie wiem, co ludzie mówili w tawernie Port Royal, ale nigdy nie spotkałem tego człowieka w moim sklepie. Właściwie, nigdy go nigdzie nie widziałem. Popytaj w wiosce - może ktoś ci coś powie...","Już mnie o tego człowieka pytałeś, a ja ci powiedziałem: nie wiem!","Czy żartujesz sobie ze mnie, czy naprawdę jesteś idiotą?! Zadajesz te same pytania już trzeci raz!","Jak to możliwe, że taki idiota został kapitanem...","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Rozumiem. Cóż, dzięki w każdym razie.","Tak, tak, dobrze.","Teraz, teraz, nie ekscytuj się tak. Po prostu zapomniałem.","Cóż, zrobił to, jak widzisz...",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
			}
		break;
		
		case "FindFugitiveSt_1":
			DialogExit();
			AddQuestRecord("MayorsQuestsList", "12-2");
			sld = characterFromId("Fugitive");
			LAi_SetSitType(sld);
			sld.dialog.currentnode = "Fugitive_tavern";
			LAi_SetLoginTime(sld, 20.0, 23.99);
			FreeSitLocator(pchar.GenQuest.FindFugitive.City + "_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.FindFugitive.City+"_tavern", "sit", "sit_front1");
		break;
		//<-- поиск дезертира
		
		// --> Карибские нравы - временное завершение
		// belamour legendary edition -->
		case "trial":
			dialog.text = "Mości Panie, co z tobą, młodzieńcze! Proszę, bądź bardziej powściągliwy i dobieraj słowa ostrożnie, gdy mówisz o szanowanych osobach! Gerard LeCroix opuścił Gwadelupę z ekspedycją na kontynent, ale zostawił tu dla ciebie nagrodę. Czy jesteś teraz zadowolony?";
			link.l1 = "Hm... Proszę wybaczyć, monsieur. Trochę się uniosłem...";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "Bardzo dobrze. Pan Lecroix zostawił twoją nagrodę u lokalnego latarnika - są starymi przyjaciółmi. Musisz tylko go odwiedzić i odebrać należną zapłatę. Monsieur Lecroix jest uczciwym człowiekiem, więc myślę, że będziesz zadowolony ze swojej nagrody.";
			link.l1 = "Zrozumiałem, dziękuję! Teraz idę do latarnika. Teraz pozwól mi zrobić sobie przerwę.";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			//TakeNItems(pchar, "gold_dublon", 400);
			link.l1 = "...";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			DialogExit();
			AddQuestRecord("Trial", "22");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "FencingL", 20);
			AddCharacterExpToSkill(pchar, "FencingS", 20);
			AddCharacterExpToSkill(pchar, "FencingH", 20);
			AddCharacterExpToSkill(pchar, "Pistol", 20);
            NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar, "questTemp.Trial");
			DeleteAttribute(npchar, "quest.trial_usurer");
			sld = characterFromId("BasTer_Lightman");
			sld.quest.trial_usurer = true;
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "trialA":
			dialog.text = "Tak, był tu, czekał na ciebie. Jednakże, zadanie, które ci powierzył, okazało się prawdopodobnie trudniejsze niż początkowo zakładano, więc nie czekał i wyruszył na wyprawę na kontynent. Zostawił twoją nagrodę z zaufaną osobą.";
			link.l1 = "Tak, naprawdę miałem nieprzewidziane okoliczności, ale pomyślnie ukończyłem zadanie. Cieszę się, że moja zapłata na mnie czeka. Od kogo mogę ją odebrać?";
			link.l1.go = "trialA_1";
		break;
		
		case "trialA_1":
			dialog.text = "Panie Lecroix zostawił twoją nagrodę u miejscowego latarnika - są starymi przyjaciółmi. Musisz tylko odwiedzić go i odebrać należną zapłatę. Monsieur Lecroix to uczciwy człowiek, więc myślę, że będziesz zadowolony ze swojej nagrody.";
			link.l1 = "Zrozumiałem, dziękuję! W takim razie idę do latarnika. Teraz pozwól mi zrobić przerwę.";
			link.l1.go = "trialA_2";
		break;
		
		case "trialA_2":
			dialog.text = "Powodzenia, monsieur.";
			link.l1 = "...";
			link.l1.go = "trialA_3";
		break;
		
		case "trialA_3":
			DialogExit();
			AddQuestRecord("Trial", "22");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Commerce", 80);
            NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar, "questTemp.Trial");
			DeleteAttribute(npchar, "quest.trial_usurer");
			sld = characterFromId("BasTer_Lightman");
			sld.quest.trial_usurer = true;
			AddLandQuestMark(sld, "questmarkmain");
		break;
		// <-- legendary edition
		/*case "trial":
			dialog.text = "Boże, czemu jesteś taki głośny, młodzieńcze! Uspokój się i uważaj na język, mówiąc o szanowanych ludziach! Gerard LeCroix opuścił Gwadelupę z ekspedycją na kontynent, ale dla ciebie zostawił wiadomość\nCzy uspokoiłeś się, panie? Gotów mnie wysłuchać?";
			link.l1 = "Hm... Proszę, wybacz mi, monsieur. Trochę się uniosłem. Słucham.";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "Bardzo dobrze. Następnym razem spróbuj najpierw zapytać, a potem krzyczeć głośno. Dobrze... Znasz człowieka o imieniu Simon Maurois?";
			link.l1 = "Ha! Każdy słyszał o Simonie Mauroisie! Oczywiście, że go znam.";
			link.l1.go = "trial_2";
			link.l2 = "Nie słyszałem o nim. Kim on jest?";
			link.l2.go = "trial_3";
		break;
		
		case "trial_2":
			dialog.text = "Doskonałe. Idź do niego zatem. To on sfinansował wyprawę monsieur Shoke'a, więc możesz odebrać swoją nagrodę od niego. Czy naprawdę było konieczne tak się unosić?";
			link.l1 = "Jeszcze raz proszę o wybaczenie... Dziękuję za pomoc, monsieur. Zaraz udam się do monsieur Maurois!";
			link.l1.go = "trial_exit";
		break;
		
		case "trial_3":
			dialog.text = "Jest właścicielem domu bankowego Maurois i kierownikiem oddziału w Capsterville. Będziesz musiał udać się do Saint-Christopher i odwiedzić bank w Capsterville. To monsieur Maurois sfinansował ekspedycję monsieur Shoke, więc możesz odebrać swoją nagrodę od niego. Czy naprawdę trzeba było się tak przejmować?";
			link.l1 = "Jeszcze raz, proszę o wybaczenie... Dziękuję za pomoc, monsieur. Od razu udam się do monsieur Maurois!";
			link.l1.go = "trial_exit";
		break;
		
		case "trial_exit":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(npchar, "quest.trial_usurer");
			pchar.questTemp.Trial = "usurer";
			AddQuestRecord("Trial", "22");
		break;*/
		
		// belamour legendary edition на пару с Акулой -->
		case "SharkGoldFleet":
			dialog.text = "Ach, przedsiębiorczy kupiec! Od razu widać biznesowe podejście. Szanuję to. Oczywiście, mam towar, którego potrzebujesz.";
			link.l1 = "Jestem pewien, że mogę to sprzedać z zyskiem. O ile mi wiadomo, w Porto Bello jest na to duże zapotrzebowanie. Ile mnie to będzie kosztować?";
			link.l1.go = "SharkGoldFleet_01";
		break;
		
		case "SharkGoldFleet_01":
			pchar.questTemp.SharkGoldFleet = "buyincar";
			dialog.text = "Tak sobie... Więc, trzysta jednostek kawy... I tyle samo kakao... To cię wyniesie..."+sti(GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)],GOOD_COFFEE,PRICE_TYPE_BUY,pchar,300)+GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)],GOOD_CHOCOLATE,PRICE_TYPE_BUY,pchar,300))+" pesos!";
			if(pchar.money < sti(GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_COFFEE, PRICE_TYPE_BUY, pchar, 300) + GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_CHOCOLATE, PRICE_TYPE_BUY, pchar, 300)))
			{
				link.l1 = "Hmm... Przepraszam, zdaje się, że nie mam wystarczająco gotówki. Poczekaj, proszę: biegnę teraz na statek po pieniądze - i zaraz wracam!";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "Proszę bardzo.";
				link.l1.go = "SharkGoldFleet_02";
			}
		break;
		
		case "SharkGoldFleet_02":
			if(GetCargoFreeSpace(pchar) < 1200)
			{
				dialog.text = "Poczekaj chwilę, señor. Wygląda na to, że na twoim statku nie ma wystarczająco miejsca na taką imprezę. Opróżnij ładownię i wróć.";
				link.l1 = "Och, zapomniałem rozładować! Zaczekaj chwilę - zaraz wracam!";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Świetnie! Natychmiast wydam rozkaz załadunku towarów na twój statek. Przyjemność robić z tobą interesy!";
				link.l1 = "Wzajemnie, señor! A teraz pozwól, że się oddalę: sprawy nie czekają.";
				link.l1.go = "SharkGoldFleet_03";
			}
		break;
		
		case "SharkGoldFleet_03":
			DialogExit();
			AddMoneyToCharacter(pchar, -sti(GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_COFFEE, PRICE_TYPE_BUY, pchar, 300) + GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_CHOCOLATE, PRICE_TYPE_BUY, pchar, 300)))
			SetCharacterGoods(pchar, GOOD_COFFEE, GetCargoGoods(pchar, GOOD_COFFEE)+300);
			SetCharacterGoods(pchar, GOOD_CHOCOLATE, GetCargoGoods(pchar, GOOD_CHOCOLATE)+300);
			AddQuestRecord("SharkGoldFleet", "4");
			pchar.questTemp.SharkGoldFleet = "toCarPortOffice";
		break;
		
		case "SharkGoldFleet_again":
			dialog.text = "Towary czekają na ciebie. Czy przyniosłeś pieniądze?";
			if(pchar.money < sti(GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_COFFEE, PRICE_TYPE_BUY, pchar, 300) + GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_CHOCOLATE, PRICE_TYPE_BUY, pchar, 300)))
			{
				link.l1 = "Jeszcze nie. Chciałem tylko upewnić się, że twoja oferta jest aktualna. A pieniądze wkrótce nadejdą.";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "Proszę bardzo.";
				link.l1.go = "SharkGoldFleet_02";
			}
		break;
		//<-- на пару с Акулой
		case "no_quests":
			dialog.text = "Obecnie nie potrzebuję twoich usług.";
			link.l1 = "Szkoda. Zmieńmy temat.";
			link.l1.go = "node_1";
		break;
		
        case "fight":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "Exit":			
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();			
		break;
	}
	LanguageCloseFile(iSeaGoods);
}

int findStoreMan(ref NPChar, int iTradeNation)
{
    ref ch;
	int n;
    int storeArray[30];
    int howStore = 0;

	for(n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(ch,Characters[n]);
        if (CheckAttribute(ch, "Dialog.Filename") && ch.Dialog.Filename == "Common_Store.c") // магазин
		{
            if (sti(ch.nation) !=  iTradeNation) continue;
            if (NPChar.id == ch.id) continue;
            if (NPChar.id == "Panama_trader" || ch.id == "Panama_trader") continue; //нельзя доплыть
			if (NPChar.id == "SanAndres_trader" || ch.id == "SanAndres_trader") continue; // fix 2016-03-07
            if (ch.location == "none") continue; // фикс для новых, невидимых до поры островов
            if (GetIslandByCityName(ch.city) == GetIslandByCityName(NPChar.city)) continue; // хрен вам, а не читы!
            storeArray[howStore] = n;
            howStore++;
		}
    }
    if (howStore == 0)
    {
        return -1;
    }
    else
    {
        return storeArray[rand(howStore-1)];
    }
}

int Sunplace_Shiptype() // new
{
	int i;
	
	if (sti(pchar.rank) >= 1 && sti(pchar.rank) < 6) i = SHIP_SCHOONER;
	if (sti(pchar.rank) >= 6 && sti(pchar.rank) < 11) i = SHIP_FLEUT;
	if (sti(pchar.rank) >= 11 && sti(pchar.rank) < 18) i = SHIP_PINNACE;
	if (sti(pchar.rank) >= 18) i = SHIP_GALEON_L;
	
	return i;
}

string findSunplaceCity(ref NPChar) // new
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(pchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hrand(howStore-1)];
	return colonies[nation].id;
}

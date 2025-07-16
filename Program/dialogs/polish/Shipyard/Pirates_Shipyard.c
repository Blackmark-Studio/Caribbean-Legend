// диалог по городам
// Это мастер тюнинга
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    string 	sTemp;
	int 	amount, iSan, iOil, iSil, iRop;
	int iTemp, iSum; // 280912
	ref 	shTo;
	string 	s1;
	
	int     Matherial1;
	int     Matherial2;
	int     Matherial3;
	int     Matherial4;
	int		HPPrice; 
	
	if ( sti(pchar.Ship.Type) != SHIP_NOTUSED)
	{
		int   	shipCurHP   = sti(RealShips[sti(pchar.Ship.Type)].HP);
		int   	shipBaseHP	= sti(RealShips[sti(pchar.Ship.Type)].BaseHP);
		int   	shipClass   = sti(RealShips[sti(pchar.Ship.Type)].Class);
	}	
 
	switch (Dialog.CurrentNode)
	{		
		// -----------------------------------Диалог первый - первая встреча
		case "First time":  // перехват основного диалога, только один раз
			if(NPChar.quest.meeting == "0")
			{
				Dialog.Text = "Uf... Co za okropny klimat... Nazywam się "+GetFullName(npchar)+", a niech mnie Bóg potępi, jeśli nie jestem najlepszym szkutnikiem na tych zapomnianych przez Boga wyspach. Ale ta wilgotność mnie po prostu powala...";
				Link.l1 = pcharrepphrase("Tysiąc rekinów, brakowało mi tylko mamrotania starego człowieka. Nazywam się "+GetFullName(pchar)+", Wierzę, że o mnie słyszałeś.","To nie wilgotność, to starość, panie. Nazywam się "+GetFullName(pchar)+"Wierzę, że słyszałeś o mnie.");
				Link.l1.go = "node_1";
				npchar.quest.meeting = "1";
			}
			else // нужно, если по квестам будет сброс на  "First time"
			{
				dialog.text = "O, znowu ty, zawsze gadasz o swoich problemach... (kaszle).";
				link.l1 = pcharrepphrase("Masz rację, to znowu ja. Ale porozmawiajmy o interesach, póki jeszcze nie oddałeś duszy Bogu.","Twoja pamięć ci dobrze służy, a teraz, jeśli pozwolisz, przejdźmy do bardziej szczegółowych pytań.");
				link.l1.go = "node_3";
				link.l2 = pcharrepphrase("Zmęczyłem się twoim mamrotaniem. Żegnaj."," Czas, żebym poszedł. Przepraszam za kłopotanie cię ");
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "Master_Ship";
			Dialog.CurrentNode = "Master_Ship";
		break;
		
		case "Master_Ship":
		//Jason ----------------------------------- Хронометр Алекса ------------------------------------------
			if (CheckAttribute(npchar, "quest.sextant") && CheckAttribute(pchar, "questTemp.AlexClock") && pchar.location == "Pirates_shipyard" && !CheckAttribute(npchar, "quest.clock"))
			{
				dialog.text = "Aha, kapitanie "+GetFullName(pchar)+"! Jak miło, że wpadłeś!";
				Link.l1 = "Wygląda na to, że czegoś ode mnie potrzebujesz, prawda? Zwykle nie jesteś aż tak uprzejmy.";
				Link.l1.go = "clock_begin";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.AlexClock") && pchar.questTemp.AlexClock == "clock" && pchar.location == "Pirates_shipyard")
			{
				dialog.text = "Widzę, że wracasz do mnie z pustymi rękami, kapitanie! Co się stało z... gośćmi?";
				Link.l1 = "Poszli. Zapytałem ich, i poszli.";
				Link.l1.go = "clock_complete";
				break;
			}
		//<-- хронометр Алекса
			dialog.text = "O, znowu ty, zawsze opowiadasz o swoich problemach... (kaszląc)";
			link.l1 = pcharrepphrase("Masz rację, to znowu ja. Ale porozmawiajmy o interesach, póki jeszcze duszy Bogu nie oddałeś.","Twoja pamięć cię nie zawodzi, a teraz, jeśli pozwolisz, przejdźmy do bardziej szczegółowych pytań.");
			link.l1.go = "node_3";
			link.l2 = pcharrepphrase("Mam dość twojego mamrotania. Żegnaj.","Już czas, bym szedł. Przepraszam, że przeszkadzałem.");
			link.l2.go = "exit";
			NextDiag.TempNode = "Master_Ship";
		break;

		case "node_1":
			dialog.text = "Młodzi ludzie w dzisiejszych czasach... Nigdy nie macie żadnego szacunku. Gorące głowy, twarde ręce, czego potrzebujesz?";
			link.l1 = pcharrepphrase("Zgadza się. Ale prędzej czy później wszystko się kończy i wygląda na to, że twój czas jest bliski...","Coś mi mówi, że w młodości również nie miałeś zbyt wiele szacunku dla starszych. Mam rację?");
			link.l1.go = "node_2";
		break;

		case "node_2":
			dialog.text = "Nie sprzeczaj się ze starszymi, szczeniaku.";
			link.l1 = pcharrepphrase("Spokojnie, teraz. Uspokój się. Nie nadwyrężaj się, bo możesz dostać zawału. Nie chcę być oskarżony o śmierć najlepszego stoczniowca na Karaibach. Przejdźmy do rzeczy.","Przebaczam ci twoją nieuprzejmość, tylko z szacunku dla twojego wieku. A teraz, jeśli skończyłeś, przejdźmy do interesów.");
			link.l1.go = "node_3";
			link.l2 = pcharrepphrase("Dobrze, dość już kazań! Żegnaj!","Widzę, że nie dojdziemy do porozumienia. Żegnaj.");
			link.l2.go = "exit";
		break;

		case "node_3":
			dialog.text = "(kaszląc)... Ludzie nie dadzą starszemu spokoju. Czego potrzebujesz ode mnie tym razem, "+GetAddress_Form(NPChar)+"? ";
			link.l1 = pcharrepphrase("Potrzebuję skorzystać z usług stoczni.","Chcę skorzystać z usług stoczni.");
			link.l1.go = "shipyard_dlg";
            Link.l2 = "Mam pytanie.";
			Link.l2.go = "quests"; //(пересылка в файл города)
			// -->
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l3 = "Chciałbym porozmawiać o finansach.";
				link.l3.go = "LoanForAll";//(перессылка в файл города)
			}
			link.l9 = pcharrepphrase("Cholera, mam kilka pilnych spraw do załatwienia, do widzenia.","Muszę już iść. Przepraszam.");
			link.l9.go = "exit";
			NextDiag.TempNode = "Master_Ship";
		break;
		
		case "shipyard_dlg":			
			if((shipBaseHP - shipCurHP > 0) && (shipClass < 7))
			{
				dialog.Text = " Mogę zaoferować ci kapitalny remont szkieletu twojego kadłuba. Ludzie tutaj nie mają pojęcia, jak budować porządne statki, wszystkie rozpadają się od jednego strzału... ";						
				Link.l1 = "Świetnie! Akurat mam statek, który wymaga naprawy. Może rzucisz okiem, co da się zrobić?";
				Link.l1.go = "ship_repair_start";		
			}
			else
			{
				dialog.Text = "Ależ, czego chcesz? Nie niepokój starego człowieka...";
			}	
			link.l2 = "Chcę tylko skorzystać z usług stoczni.";
			link.l2.go = "shipyard";
			link.l3 = "Potrzebuję broni dla statku.";
			link.l3.go = "Cannons";
			if(RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM)
			{
					link.l4 = "Chcę zmienić wygląd moich żagli.";
					link.l4.go = "SailsGerald";
			}
			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && !CheckAttribute(npchar, "quest.FDM_hull"))
			{
					link.l50 = "Mój statek jest dość... wyjątkowy. Chciałbym dokonać kilku zmian.";
					link.l50.go = "FDM";
			}
			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_full") && npchar.quest.FDM_full == "cabin" && GetCharacterItem(pchar, "Chest") > 0)
			{
					link.l50 = "Mam więcej skrzyń na przebudowę kabiny.";
					link.l50.go = "FDM_cabin_pay";
			}
			// Xenon -->
			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_hull") && npchar.quest.FDM_hull == "hull_waitmoney")
			{
					link.l50 = "Przyszedłem w sprawie odbudowy statku.";
					link.l50.go = "FDM_hull_givemoney";
			}

			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_hull") && npchar.quest.FDM_hull == "hull_waitmaterials")
			{
					link.l50 = "Jestem tutaj w sprawie odbudowy statku.";
					link.l50.go = "FDM_hull_checkmaterials";
			}
			// <-- Xenon
			link.l9 = pcharrepphrase("Cholera, mam parę pilnych spraw do załatwienia, do widzenia.","Już czas, bym odszedł. Przepraszam.");
			Link.l9.go = "ship_tunning_not_now";
		break;
		
		case "ship_repair_again":
			if((shipBaseHP - shipCurHP > 0) && (shipClass < 7))
			{
				dialog.Text = RandPhraseSimple("Ach... znowu ty. Chcesz znowu naprawić swój statek?",RandPhraseSimple("Witam, sławnego kapitana. Co, potrzebujesz kolejnego remontu kapitalnego?","Do diabła... Ani chwili spokoju. Nie dajecie staremu człowiekowi się skupić... Kolejna naprawa?"));
				Link.l1 = "Tak. Masz rację. Przyjrzymy się, co możemy zrobić?";
				Link.l1.go = "ship_repair_start";						   
			}
			else
			{
				dialog.Text = "Co się tym razem stało? Nie chcesz dać mi spokoju...";
			}				
			link.l2 = "Chcę tylko skorzystać z usług stoczni.";
			link.l2.go = "shipyard";
			link.l3 = "Potrzebuję broni dla statku.";
			link.l3.go = "Cannons";
			if(RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM)
			{
					link.l31 = "Chcę zmienić wygląd moich żagli.";
					link.l31.go = "SailsGerald";
			}
			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && !CheckAttribute(npchar, "quest.FDM_hull"))
			{
					link.l50 = "Mój statek jest dość... wyjątkowy. Chciałbym wprowadzić kilka zmian.";
					link.l50.go = "FDM";
			}
			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_full") && npchar.quest.FDM_full == "cabin" && GetCharacterItem(pchar, "Chest") > 0)
			{
					link.l50 = "Mam więcej skrzyń na przebudowę kajuty.";
					link.l50.go = "FDM_cabin_pay";
			}
            Link.l4 = "Mam pytanie.";
			Link.l4.go = "quests"; //(пересылка в файл города)
			// -->
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l5 = "Chciałbym porozmawiać o finansach.";
				link.l5.go = "LoanForAll";//(пересылка в файл города)
			}
			Link.l9 = "Nie. Jestem zadowolony z tego, co mam.";
			Link.l9.go = "ship_tunning_not_now_2";
		break;
		
		case "ship_tunning_not_now_2":
			dialog.Text = "O, widzę, że wciąż myślisz! Zajdziesz daleko! Wróć, kiedy zdecydujesz, czego chcesz, i nie zawracaj mi głowy błahostkami.";
			Link.l1 = RandPhraseSimple("Dziękuję! Wszystkiego najlepszego.","Żegnaj, mistrzu. I mniej sarkazmu.");
			Link.l1.go = "ship_tunning_not_now";
		break;
		
		case "ship_repair_start":
            if ( sti(Pchar.Ship.Type) == SHIP_NOTUSED || Pchar.location.from_sea != "Pirates_town")
            {
                dialog.Text = "Gdzie jest statek? Co to za czary-mary?!";
			    Link.l1 = "Tak, masz rację... Ja jestem... Przepraszam.";
			    Link.l1.go = "ship_tunning_not_now";
            }
            else
            {
			    if (GetHour() == 13)
			    {
					dialog.Text = "Może jestem pracoholikiem, ale też mam przerwę na lunch. Wróć później!";
			        Link.l1 = "Dobrze...";
			        Link.l1.go = "ship_tunning_not_now";
			    }
			    else
			    {
                    if( makefloat(shipCurHP)/makefloat(shipBaseHP) < 0.10)
                    {
						dialog.Text = "Do diabła... Twój statek jest kompletnie rozbity. Nie podejmę się naprawy kapitalnej, nawet mnie nie pytaj... Gdybyś przyszedł trochę wcześniej...";
    			        Link.l1 = "Dobrze... Szkoda...";
    			        Link.l1.go = "ship_tunning_not_now";
    			        break;
                    }
					if( makefloat(shipCurHP)/makefloat(shipBaseHP) > 0.95)
                    {
						dialog.Text = "Co to za czary mary... Twój statek wygląda jak nowy... Kadłub praktycznie lśni. Nie ma tu nic do naprawy.";
						Link.l1 = "Dobrze... Cóż, przyjdę później...";
    			        Link.l1.go = "ship_tunning_not_now";
    			        break;
					}
                    s1 = "Fine, alright... What do we have here... Aha, " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) + ".";
    			    if (sti(RealShips[sti(Pchar.Ship.Type)].Stolen) == true && !CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning"))
    			    {
    			        s1 = s1 + " Bah! This ship's been in too many hands. Yeah and there are a lot of scuffs. Do you have a corsair patent? Just joking... anyway, back to the matter.";
    			    }
                    dialog.Text = s1;
					Link.l1 = "Spójrzmy, co możemy tutaj zrobić.";
    			    Link.l1.go = "ship_repair_HP";		    			    
    			    Link.l2 = "Stój! Zmieniłem zdanie.";
    			    Link.l2.go = "ship_tunning_not_now_2";
			    }
			}
		break;
		
		case "ship_repair_HP":
			HPPrice 	= GetMaterialQtyRepair( pchar, 0 ); 
			Matherial1	= GetMaterialQtyRepair( pchar, 1 );
			Matherial2	= GetMaterialQtyRepair( pchar, 2 );
			Matherial3	= GetMaterialQtyRepair( pchar, 3 );
			Matherial4	= GetMaterialQtyRepair( pchar, 4 );
			
			s1 = "Let's have a look here at what we can do. At the moment, the ship's frame is " + shipCurHP + ". . The highest possible value is " + shipBaseHP;			
			s1 = s1 + ". In order to make a full repair, I need: ironwood - "+ Matherial1 + ", resin - " + Matherial2 + ", ship silk - " + Matherial3 + " ropes - " + Matherial4 + ".";
			s1 = s1 + " For this work I will charge: "+ HPPrice + " doubloons for the labor... My grandchildren have been calling me back to Europe for a long time. I don't want to come back empty-handed you know... So, that'll be all. And oh yes - the money up front.";
            dialog.Text = s1;
			Link.l1 = "Brzmi dobrze. Akceptuję warunki. Wszystko zostanie dostarczone zgodnie z umową.";
			if(CheckItemMyCabin("gold_dublon") >= HPPrice)
			{
				Link.l1.go = "ship_repair_HP_start_0";
			}
			else
			{
				Link.l1.go = "ship_repair_HP_start";
			}			
			Link.l2 = "Nie. Nie jestem z tego zadowolony.";
			Link.l2.go = "ship_tunning_not_now";
		break;
		
		case "ship_repair_HP_start_0":
			dialog.Text = "Tak... Płatność... Możesz zapłacić teraz lub wysłać posłańca na statek po potrzebną sumę... Co chciałbyś zrobić?";
			link.l1 = "Zapłacę od razu.";
			link.l1.go = "ship_repair_HP_start";
			link.l2 = "Wyślę chłopaka na posyłki. Wierzę, że miałem trochę złota leżącego w moich skrzyniach...";
			link.l2.go = "ship_repair_HP_start_1";
		break;
		
		case "ship_repair_HP_start":
			HPPrice 	= GetMaterialQtyRepair( pchar, 0 ); 
			Matherial1	= GetMaterialQtyRepair( pchar, 1 );
			Matherial2	= GetMaterialQtyRepair( pchar, 2 );
			Matherial3	= GetMaterialQtyRepair( pchar, 3 );
			Matherial4	= GetMaterialQtyRepair( pchar, 4 );
		    amount = HPPrice;
		    if(GetCharacterItem(pchar,"gold_dublon") >= amount)
			{
				TakeNItems(pchar,"gold_dublon", -amount);				
			    NPChar.Repair.Money  		= amount;
			    NPChar.Repair.Matherial1 	= Matherial1; 
			    NPChar.Repair.Matherial2    = Matherial2;
				NPChar.Repair.Matherial3 	= Matherial3; 
			    NPChar.Repair.Matherial4    = Matherial4; 				 				
			    NPChar.Repair.ShipType      = Pchar.Ship.Type;
			    NPChar.Repair.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NPChar.Repair.Delta         = shipBaseHP - shipCurHP;
			    			
				NextDiag.TempNode = "ship_repair_HP_again";
                dialog.text = "Znakomicie. Będę czekać na materiały.";
			    link.l1 = "Zamierzam ich zebrać...";
			    link.l1.go = "Exit";
			    
			    ReOpenQuestHeader("ShipRepair");
			    AddQuestRecord("ShipRepair", "t1");
				AddQuestUserData("ShipRepair", "sText",  "For capital repairing measures of  " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) +
    " the shipmaster requires: ironwood - " + NPChar.Repair.Matherial1 + ", resin - "+ NPChar.Repair.Matherial2 + ", ship silk - " + NPChar.Repair.Matherial3 + " ropes - " + NPChar.Repair.Matherial4 + 
				". As a deposit we handed in " + NPChar.Repair.Money + " doubloons... He says he's about to take off to Europe. I think that old devil's lying.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now";
                dialog.text = RandPhraseSimple("Nie widzę zaliczki...","Co to za czary-mary...");
				link.l1 = "Wracam później.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_repair_HP_start_1":
			HPPrice 	= GetMaterialQtyRepair( pchar, 0 ); 
			Matherial1	= GetMaterialQtyRepair( pchar, 1 );
			Matherial2	= GetMaterialQtyRepair( pchar, 2 );
			Matherial3	= GetMaterialQtyRepair( pchar, 3 );
			Matherial4	= GetMaterialQtyRepair( pchar, 4 );
			AddTimeToCurrent(0, 30);
		    amount = HPPrice;
			GetItemMyCabin("gold_dublon", amount);
		    
			NPChar.Repair.Money  		= amount;
			NPChar.Repair.Matherial1 	= Matherial1; 
			NPChar.Repair.Matherial2    = Matherial2; 
			NPChar.Repair.Matherial3 	= Matherial3; 
			NPChar.Repair.Matherial4    = Matherial4; 				 							
			NPChar.Repair.ShipType      = Pchar.Ship.Type;
			NPChar.Repair.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
			NPChar.Repair.Delta         = shipBaseHP - shipCurHP;
			    			
			NextDiag.TempNode = "ship_repair_HP_again";
			dialog.text = "Znakomicie. Będę czekał na materiały.";
			link.l1 = "Ruszam w drogę...";
			link.l1.go = "Exit";
			
			ReOpenQuestHeader("ShipRepair");
			AddQuestRecord("ShipRepair", "t1");
			AddQuestUserData("ShipRepair", "sText",  "For capital repairing measures of  " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) +
    " the shipmaster requires: ironwood - " + NPChar.Repair.Matherial1 + ", resin - "+ NPChar.Repair.Matherial2 + ", ship silk - " + NPChar.Repair.Matherial3 + " ropes - " + NPChar.Repair.Matherial4 + 
				". As a deposit we handed in " + NPChar.Repair.Money + " doubloons... He says he's about to take off to Europe. I think that old devil's lying.");
			
		break;
		
		case "ship_repair_HP_again":
		    if (sti(NPChar.Repair.ShipType) == sti(Pchar.Ship.Type) && NPChar.Repair.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName)
		    {
                NextDiag.TempNode = "ship_repair_HP_again";
				dialog.Text = "Zegar tyka. Masz to, o co prosiłem?";
			    Link.l1 = "Tak. Udało mi się coś zdobyć.";
			    Link.l1.go = "ship_repair_HP_again_2";
			    Link.l2 = "Nie. Wciąż szukam.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Repair");
                NextDiag.TempNode = "ship_repair_again";
			    dialog.Text = "Wydaje mi się, panie, że zmienił pan statek od czasu naszej ostatniej umowy. Będziemy musieli wszystko przeliczyć od nowa...";
			    Link.l1 = "Tak, to prawda. Jaka szkoda, że złoże zniknęło...";
			    Link.l1.go = "Exit";		    
			    AddQuestRecord("ShipRepait", "Lose");
			    CloseQuestHeader("ShipRepair");
			}
		break;
		
		case "ship_repair_HP_again_2":
			checkMatherial_repair(Pchar, NPChar, GOOD_SANDAL, 	1);
			checkMatherial_repair(Pchar, NPChar, GOOD_OIL, 		2);
			checkMatherial_repair(Pchar, NPChar, GOOD_SHIPSILK, 3);
			checkMatherial_repair(Pchar, NPChar, GOOD_ROPES, 	4);
		    if(sti(NPChar.Repair.Matherial1) < 1 && 
			   sti(NPChar.Repair.Matherial2) < 1 &&
			   sti(NPChar.Repair.Matherial3) < 1 &&
			   sti(NPChar.Repair.Matherial4) < 1)
			{
                NextDiag.TempNode = "ship_repair_again";
                dialog.text = "Wszystko, czego potrzebowałem. Dobrze! Czas zabrać się do pracy...";
			    link.l1 = "Dobrze, poczekam.";
			    link.l1.go = "ship_repair_HP_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_repair_HP_again";
				dialog.Text = "Teraz, co jeszcze musisz mi przynieść, to: "+sti(NPChar.Repair.Matherial1)+" z żelaznego drewna, "+sti(NPChar.Repair.Matherial2)+"żywica, "+NPChar.Repair.Matherial3+" z jedwabiu statku, "+NPChar.Repair.Matherial4+"lina.";
				link.l1 = "W porządku.";
				link.l1.go = "Exit";

                AddQuestRecord("ShipRepair", "t1");
				AddQuestUserData("ShipRepair", "sText", "Materials left: ironwood - "+ NPChar.Repair.Matherial1 + ", resin - "+ NPChar.Repair.Matherial2 + ", ship silk - " + NPChar.Repair.Matherial3 + " ropes - " + NPChar.Repair.Matherial4 + ".");
			}
		break;
		
		case "ship_repair_HP_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
			shTo.HP = sti(shTo.HP) + sti(NPChar.Repair.Delta);
		    DeleteAttribute(NPChar, "Repair");
			
			pchar.ship.hp = GetCharacterShipBaseHP(pchar);
			DeleteAttribute(pchar, "ship.hulls");
			DeleteAttribute(pchar, "ship.blots");		
			
            NextDiag.TempNode = "node_3";
			dialog.Text = "... Cóż, to wszystko... Gwarantuję, że teraz będzie naprawdę trudno zniszczyć ten statek!";
			Link.l1 = "Dziękuję! Wolałbym nie eksperymentować, ale zaufam tobie.";
			Link.l1.go = "Exit";
			AddQuestRecord("ShipRepair", "End");
			CloseQuestHeader("ShipRepair");
		break;		
		
		///////////////////////////////  квестовые ветки
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie masz pytania?","Jak mogę ci pomóc?"),"Próbowałeś zadać mi pytanie chwilę temu...","Nie spotkałem nigdy ludzi z taką ciekawością w mojej stoczni ani nigdzie indziej w tym mieście.","Co z tymi wszystkimi pytaniami? Moim zadaniem jest budować statki. Zajmijmy się tym.","blokada",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie...","Nie mam w tej chwili nic do powiedzenia."),"Ech, gdzież to moja pamięć się podziała...","Hm, cóż...","Dobrze, pozwólmy...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (!CheckAttribute(npchar, "Step_Door"))
			{
				link.l2 = "Słuchaj, chciałbym przejść, ale te drzwi są zamknięte...";
				link.l2.go = "Step_Door_1";
			}

			if ((pchar.questTemp.different == "GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakAlexus"))
			{
				link.l1 = "Chciałbym zaproponować umowę.";
				link.l1.go = "Al_ShipLetters_1";// генератор  "Найденные документы"
				pchar.questTemp.different.GiveShipLetters.speakAlexus = true;
			}
			if(CheckAttribute(pchar, "questTemp.AlexClock") && pchar.questTemp.AlexClock == "go") // 280912
			{
				link.l1 = "Przybyłem w sprawie materiałów na fregatę.";
				link.l1.go = "clock";
			}
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				link.l1 = "Słuchaj, "+npchar.name+", widziałeś ostatnio Miguela Dichoso na Isla Tesoro?";
				link.l1.go = "tieyasal";
			}
		break;
//*************************** Генератор - "Найденные судовые документы" **************
		
		case "Al_ShipLetters_1":
			dialog.text = "Przedstaw swe warunki.";
			s1 = "I lucked into finding an absolutely legal ship's documents packet that hasn't been called for search yet.";
			s1 = s1 + "The ship is afloat and it hasn't been excluded from the registry, don't worry. Just a blind fool-owner had the misfortune of losing these papers...";
			link.l1 = s1;
			link.l1.go = "Al_ShipLetters_2";			
		break;
		case "Al_ShipLetters_2":
			s1 = "Let me take a look! It really looks to be freshly filled out. Well, luck is in your favor, sir! ";
			s1 = s1 + "I actually needed a packet just like this. I, in turn, will offer you " + sti(pchar.questTemp.different.GiveShipLetters.price5) + " pesos. What do you say?";
			dialog.text = s1;
			link.l1 = "Prawdziwa królewska hojność! Oczywiście, że się zgadzam!";
			link.l1.go = "Al_ShipLetters_3";
			link.l2 = "Nie, nie sądzę.";
			link.l2.go = "exit";
		break;
		case "Al_ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price5)); 
			ChangeCharacterComplexReputation(pchar,"nobility", -1); 
			OfficersReaction("bad"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "9");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 
		break;
		

//*************************** Открывание двери ***************************
 		case "Step_Door_1":
			dialog.text = "Zgadza się. Jeśli chcesz przejść przez te drzwi, musisz zapłacić mi 20000 pesos. Jeśli nie zapłacisz, nie otworzę. To nie jest jadłodajnia. I nie radzę ci tam iść. Lepiej dla ciebie, jeśli tego nie zrobisz...";
			if(sti(pchar.money) >= 20000)
			{
    			link.l1 = "Oto twoje pieniądze. Otwieraj.";
    			link.l1.go = "Step_Door_2";
            }
            else
            {
    			link.l1 = "Nie mam tyle pieniędzy.";
    			link.l1.go = "Step_Door_3";
            }
            link.l2 = "Nie ma mowy! Nigdy bym nie zapłacił za jakieś drzwi.";
    		link.l2.go = "exit";
		break;
		
 		case "Step_Door_2":
			npchar.Step_Door = true; // fix
			dialog.text = "Wejdź. Drzwi są otwarte. Nie przejmuj się, by mi dziękować!";
			link.l1 = "Nie, czemu nie. Dziękuję, "+npchar.name+"...";
			link.l1.go = "exit";
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
            AddMoneyToCharacter(pchar, -20000);
			pchar.quest.CloseBermudesDungeonDoor.win_condition.l1 = "MapEnter";
            pchar.quest.CloseBermudesDungeonDoor.win_condition = "CloseBermudesDungeonDoor";
		break;
		
 		case "Step_Door_3":
			dialog.text = "Cóż, kiedy będziesz to miał, wróć. W przeciwnym razie, nie próbuj mnie przekonywać. To bezużyteczne...";
			link.l1 = "Argh, jestem kompletnie oniemiały!";
			link.l1.go = "exit";
		break;
		
	// ------------------------------------------- хронометр Ђлекса ----------------------------------------------// Addon-2016 Jason замена дублонов на песо везде
		case "clock_begin":
			dialog.text = "Nie bądź tak surowy dla starego człowieka... Naprawdę potrzebuję twojej pomocy, kapitanie.";
			link.l1 = "Powiedz mi, mistrzu. Co ci się przydarzyło?";
			link.l1.go = "clock_begin_1";
		break;
		
		case "clock_begin_1":
			sTotalTemp = "Steven Dodson";
			if (pchar.questTemp.Alex.Clock == "terrax") sTotalTemp = "Marcus Tyrex";
			dialog.text = "Nasz nowy przywódca Braci Wybrzeża, "+sTotalTemp+", zamówił nowy statek, fregatę. Postawił również dość trudne zadania: chroniony kadłub, szybka prędkość i dobra manewrowość oraz działa o największym możliwym kalibrze\nRozumiem, że statek admirała, przepraszam, przywódcy bractwa, musi być czymś wyjątkowym, ale to oznacza, że potrzebuję specjalnych materiałów, aby go zbudować. Musiałeś o nich słyszeć. Żelazne drewno, żywica, jedwab okrętowy i liny...";
			link.l1 = "Więc powiedz o tym przywódcy Bractwa. A może jesteś podejrzliwy, że "+sTotalTemp+"zetnę ci za to łeb?";
			link.l1.go = "clock_begin_2";
		break;
		
		case "clock_begin_2":
			dialog.text = "Powiedziałem mu... Rzecz w tym, że nasz nowy przywódca nie ma ani czasu, ani możliwości, by znaleźć i dostarczyć te materiały. Musisz wiedzieć, jaką to rzadkość. I nie ma mowy, żebym mógł zbudować fregatę o takich charakterystykach bez nich.";
			link.l1 = "I pewnie proponujesz, żebym to ja znalazł materiały na statek?";
			link.l1.go = "clock_begin_3";
		break;
		
		case "clock_begin_3":
			dialog.text = "Cóż, tak. Jesteś dobrym przyjacielem naszego przywódcy. "+sTotalTemp+"sam mówi, że wiele ci zawdzięcza i że wymaga wszelkiego rodzaju szacunku dla ciebie... Więc pomyślałem: skoro jesteś jego przyjacielem, to może nie będziesz miał nic przeciwko, by mu pomóc? A jednocześnie: zdajesz sobie sprawę, w jak niezręcznej sytuacji się znajduję? Wszystkie materiały zostaną opłacone, "+sTotalTemp+"nie szczędzi złota.";
			link.l1 = "Przykro mi bardzo, mistrzu, ale jestem nie mniej zajęty niż "+sTotalTemp+"Obawiam się, że zebranie materiałów może zająć całą wieczność. Lepiej zapytaj kogoś innego.";
			link.l1.go = "clock_exit";
			link.l2 = "Cóż, jeśli "+sTotalTemp+" zamówiłem u ciebie statek - wtedy oczywiście spróbuję pomóc. Naprawdę jesteśmy przyjaciółmi, a przyjaciele muszą sobie pomagać. Ile materiałów potrzebujesz?";
			link.l2.go = "clock_begin_4";
		break;
		
		case "clock_exit":
			dialog.text = "To naprawdę szkoda. Naprawdę wielka szkoda. Liczyłem na ciebie. No cóż, jak mówią, nie znaczy nie...";
			link.l1 = "...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.AlexClock");
		break;
		
		case "clock_begin_4":
			dialog.text = "Brakuje mi 100 jednostek żelaznego drewna, 150 pojemników żywicy, 110 bel jedwabiu żaglowego i 90 zwojów konopnych lin. Co myślisz? Czy mógłbyś mi to wszystko znaleźć w ciągu czterech miesięcy? Nie sądzę, abym miał więcej czasu.";
			link.l1 = "Mogę przynajmniej spróbować. A co z zapłatą?";
			link.l1.go = "clock_begin_5";
		break;
		
		case "clock_begin_5":
			dialog.text = "Oto moje stawki: drewno żelazne po 4000 pesos za sztukę, żywice po 1400 pesos za kontener, jedwab po 2500 pesos za rolkę, a liny po 1500 pesos za zwój. A jeśli przyniesiesz mi to wszystko, otrzymasz ode mnie bardzo miły prezent.";
			link.l1 = "Cóż to takiego, zastanawiam się?";
			link.l1.go = "clock_begin_6";
		break;
		
		case "clock_begin_6":
			dialog.text = "Najpierw przynieś mi materiały. Ale zapewniam cię: przydadzą ci się i rzecz jest unikalna. Nie ma drugiej takiej na Karaibach, ani na całym świecie jak dotąd. Mam nadzieję, że ta mała iskra ciekawości wzbudziła w tobie zainteresowanie, by zebrać dla mnie materiały.";
			link.l1 = "Cóż, jesteś zręczny jak skrzat, mistrzu! Dobrze, mamy umowę.";
			link.l1.go = "clock_begin_7";
		break;
		
		case "clock_begin_7":
			dialog.text = "Jestem bardzo szczęśliwy. Będę czekał na twój powrót.";
			link.l1 = "Mam nadzieję, że to nie zajmie zbyt długo...";
			link.l1.go = "clock_begin_8";
		break;
		
		case "clock_begin_8":
			DialogExit();
			pchar.questTemp.AlexClock = "go";
			npchar.quest.clock = "true";
			SetFunctionTimerCondition("AlexClock_Over", 0, 0, 122, false); // таймер
			AddQuestRecord("alex_clock", "1");
			// запоминаем переменные
			pchar.questTemp.AlexClock.Sandal = 100;
			pchar.questTemp.AlexClock.Oil = 150;
			pchar.questTemp.AlexClock.Shipsilk = 110;
			pchar.questTemp.AlexClock.Ropes = 90;
		break;
		
		case "clock":
			dialog.text = "Doskonale! Co mi dzisiaj przyniosłeś?";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) > 0 && !CheckAttribute(npchar, "quest.sandal"))
			{
				iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
				link.l1 = "Żelazne drewno, w ilości "+FindRussianQtyString(iSan)+".";
				link.l1.go = "sandal";
			}
			if (GetSquadronGoods(pchar, GOOD_OIL) > 0 && !CheckAttribute(npchar, "quest.oil"))
			{
				iOil = GetSquadronGoods(pchar, GOOD_OIL);
				link.l2 = "Żywice, w ilości "+FindRussianQtyString(iOil)+".";
				link.l2.go = "oil";
			}
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0 && !CheckAttribute(npchar, "quest.shipsilk"))
			{
				iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
				link.l3 = "Jedwab okrętowy, w ilości "+FindRussianQtyString(iSil)+".";
				link.l3.go = "shipsilk";
			}
			if (GetSquadronGoods(pchar, GOOD_ROPES) > 0 && !CheckAttribute(npchar, "quest.ropes"))
			{
				iRop = GetSquadronGoods(pchar, GOOD_ROPES);
				link.l4 = "Konopne liny, w ilości "+FindRussianQtyString(iRop)+".";
				link.l4.go = "ropes";
			}
			link.l5 = "Nic na tę chwilę. Chciałem tylko upewnić się, że nasza umowa wciąż obowiązuje.";
			link.l5.go = "exit";
		break;
		
		case "clock_1":
			if (CheckAttribute(npchar, "quest.sandal") && CheckAttribute(npchar, "quest.oil") && CheckAttribute(npchar, "quest.shipsilk") && CheckAttribute(npchar, "quest.ropes")) // все привез
			{
				dialog.text = "Świetnie! Mam wszystkie materiały w potrzebnej ilości. Wielkie dzięki za pomoc, kapitanie. Bardzo mi pomogłeś.";
				link.l1 = "Tak, w każdej chwili, panie. Jestem również bardzo zadowolony: pomogłem przyjacielowi i zarobiłem trochę dobrych pieniędzy. A teraz wróćmy do naszej rozmowy o twoim tajemniczym przedmiocie, który mi obiecałeś.";
				link.l1.go = "clock_2";
			}
			else
			{
				dialog.text = "Masz dla mnie jeszcze jakieś niespodzianki, kapitanie?";
				link.l1 = "Niestety, to wszystko na teraz. Po prostu czekaj dalej.";
				link.l1.go = "exit";
				link.l2 = "Tak, mam jeszcze jedną rzecz...";
				link.l2.go = "clock";
			}
		break;
		
		case "sandal": // бакаут
			amount = sti(pchar.questTemp.AlexClock.Sandal);
			iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
			iTemp = amount-iSan;
			if (iTemp > 0) // ещё не все привез
			{
				iSum = 4000*iSan;
				dialog.text = "Dobrze, w porządku. Będę też potrzebował "+FindRussianQtyString(amount)+"z żelaznego drewna. Przyniosłeś mi "+FindRussianQtyString(iSan)+". . Więc, co ci pozostało mi przynieść, to "+FindRussianQtyString(iTemp)+"Zgoda, po stawce 4000 pesos za sztukę, Twoja nagroda wynosi "+FindRussianMoneyString(iSum)+" Proszę, weź to.";
				link.l1 = "Dziękuję! Resztę otrzymasz wkrótce.";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, iSan);
				pchar.questTemp.AlexClock.Sandal = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "ironwood");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 4000*amount;
				dialog.text = "Dobrze, w porządku. Będę także potrzebował "+FindRussianQtyString(amount)+"  z żelaznego drewna. Przyniosłeś mi "+FindRussianQtyString(iSan)+" . Więc, załatwiliśmy teraz żelazne drewno! Dobrze, w tempie 4000 pesos za sztukę, twoja nagroda wynosi "+FindRussianMoneyString(iSum)+"Proszę, weź to.";
				link.l1 = "Dziękuję!";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, amount);
				npchar.quest.sandal = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "ironwood");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "oil": // смолы
			amount = sti(pchar.questTemp.AlexClock.Oil);
			iOil = GetSquadronGoods(pchar, GOOD_OIL);
			iTemp = amount-iOil;
			if (iTemp > 0) // ещё не все привез
			{
				iSum = 1400*iOil;
				dialog.text = "Dobrze, w porządku. Będę też potrzebował "+FindRussianQtyString(amount)+" żywic. Przyniosłeś mi "+FindRussianQtyString(iOil)+". Więc, co ci zostało do przyniesienia mi to "+FindRussianQtyString(iTemp)+" Dobrze, przy stawce 1400 pesos za kontener, twoja nagroda wynosi "+FindRussianMoneyString(iSum)+" Proszę, weź to.";
				link.l1 = "Dziękuję! Wkrótce otrzymasz resztę.";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, iOil);
				pchar.questTemp.AlexClock.Oil = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "resins");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 1400*amount;
				dialog.text = "Dobrze, w porządku. Będę również potrzebował "+FindRussianQtyString(amount)+"żywice. Przyniosłeś mi "+FindRussianQtyString(iOil)+"Więc, uporaliśmy się już z żywicami! Dobrze, przy stawce 1400 peso za kontener, twoja nagroda wynosi "+FindRussianMoneyString(iSum)+"Proszę, weź to.";
				link.l1 = "Dziękuję!";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, amount);
				npchar.quest.oil = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "resins");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "shipsilk": // шёлк
			amount = sti(pchar.questTemp.AlexClock.Shipsilk);
			iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
			iTemp = amount-iSil;
			if (iTemp > 0) // ещё не все привез
			{
				iSum = 2600*iSil;
				dialog.text = "Dobrze, w porządku. Będę też potrzebował "+FindRussianQtyString(amount)+" jedwab. Przyniosłeś mi "+FindRussianQtyString(iSil)+"Więc, co ci pozostało do przyniesienia mi to "+FindRussianQtyString(iTemp)+" . W porządku, w tempie 2600 pesos za sztukę, twoja nagroda wynosi "+FindRussianMoneyString(iSum)+" Proszę, weź to.";
				link.l1 = "Dziękuję! Wkrótce dostaniesz resztę.";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, iSil);
				pchar.questTemp.AlexClock.Shipsilk = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "silk");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 2600*amount;
				dialog.text = "Dobrze, w porządku. Będę również potrzebował "+FindRussianQtyString(amount)+" jedwab. Przywiozłeś mi "+FindRussianQtyString(iSil)+"Więc, zajęliśmy się teraz jedwabiem! Zatem, przy stawce 2600 pesos za sztukę, twoja nagroda wynosi "+FindRussianMoneyString(iSum)+" Proszę, weź to.";
				link.l1 = "Dziękuję!";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, amount);
				npchar.quest.shipsilk = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "silk");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "ropes": // канаты
			amount = sti(pchar.questTemp.AlexClock.Ropes);
			iRop = GetSquadronGoods(pchar, GOOD_ROPES);
			iTemp = amount-iRop;
			if (iTemp > 0) // ещё не все привез
			{
				iSum = 1500*iRop;
				dialog.text = "Dobrze, w porządku. Będę także potrzebował "+FindRussianQtyString(amount)+" liny. Przyniosłeś mi "+FindRussianQtyString(iRop)+"Więc, co ci zostało do przyniesienia mi to "+FindRussianQtyString(iTemp)+". Tak więc, przy stawce 1500 pesos za sztukę, twoja nagroda wynosi "+FindRussianMoneyString(iSum)+" Proszę, weź to.";
				link.l1 = "Dziękuję! Resztę dostaniesz wkrótce.";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, iRop);
				pchar.questTemp.AlexClock.Ropes = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "ropes");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 1500*amount;
				dialog.text = "Dobrze, w porządku. Będę również potrzebował "+FindRussianQtyString(amount)+" liny. Przyniosłeś mi "+FindRussianQtyString(iRop)+". Tak więc, już zajęliśmy się linami. Dobrze, przy stawce 1500 pesos za sztukę, Twoja nagroda wynosi "+FindRussianMoneyString(iSum)+" Proszę, weź to.";
				link.l1 = "Dziękuję!";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, amount);
				npchar.quest.ropes = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "ropes");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "clock_2":
			dialog.text = "Tak, tak... o mojej sprawie, oczywiście. M-m-mmm... Hmmm... gdzie ja... ahhh...";
			link.l1 = "Co się dzieje, mistrzu? Wyglądasz na bardzo zmartwionego. Czy coś jest nie tak? Jakieś problemy?";
			link.l1.go = "clock_3";
		break;
		
		case "clock_3":
			dialog.text = "Owszem. Problemy. Ostatnio. Przeklęci poszukiwacze skarbów...";
			link.l1 = "Spokojnie, spokojnie. W twoim wieku nie jest dobrze tak się martwić. Nie daj Boże, możesz być o krok od zguby. Kto wtedy zbudowałby fregatę dla głowy Bractwa? Uspokój się i wyjaśnij mi, kim są ci poszukiwacze skarbów?";
			link.l1.go = "clock_4";
		break;
		
		case "clock_4":
			dialog.text = "Tam przy moim stole są drzwi. Prowadzą bezpośrednio do starego skarbca. W tym skarbcu w jednej ze skrzyń skarbów trzymam moją metalową szkatułkę z przedmiotami, które miałem przy sobie, gdy dwadzieścia lat temu wciągnął mnie ten cholerny wir i wylądowałem tutaj...";
			link.l1 = "Jaki lejek? O czym ty mówisz?";
			link.l1.go = "clock_5";
		break;
		
		case "clock_5":
			dialog.text = "Ach, przepraszam za moje fantazje. Bycie starym nie jest łatwe, młody człowieku. Wybacz mi. Ale to nieistotne. Istotne jest to, że skrzynia z prezentem dla ciebie jest w kufrze, który leży w lochu obecnie zajmowanym przez jakichś łotrów. Nie są oni naszymi ludźmi, ani z Isla Tesoro\nŁowcy skarbów, ktoś musiał im powiedzieć, że to miejsce jest pełne skarbów. Nie odważą się pokazać tutaj, jednak ja boję się ich odwiedzić, rozumiesz? Ich twarze są...";
			link.l1 = "Widzę. Otwórz drzwi. Rozprawię się z twoimi nieproszonymi gośćmi.";
			link.l1.go = "clock_6";
		break;
		
		case "clock_6":
			dialog.text = "Tak po prostu? Pokonasz ich? Sam? Nie boisz się? Mamy całą osadę, która będzie walczyć za ciebie, jeśli tylko poprosisz...";
			link.l1 = "Mniej gadania, więcej działania, mistrzu. Otwórz te drzwi, a resztą zajmę się ja. W której skrzyni trzymasz swoje rzeczy?";
			link.l1.go = "clock_7";
		break;
		
		case "clock_7":
			dialog.text = "Na końcu korytarza jest cała kolekcja pustych drewnianych beczek. Za nimi, na podłodze, w ustronnym miejscu, jest mała skrzynia. Przybiłem na niej zamek, więc wątpię, by intruzi zdołali wsadzić swoje brudne łapy do środka, nawet gdyby ją znaleźli. Oto klucz.";
			link.l1 = "Cieszę się, że myślisz naprzód. Poczekaj tutaj i nigdzie się nie ruszaj.";
			link.l1.go = "clock_8";
		break;
		
		case "clock_8":
			DialogExit();
			GiveItem2Character(pchar, "key3"); 
			bDisableFastReload = true;//закрыть переход
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload1_back", true);
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
			LAi_LocationDisableOfficersGen("Bermudes_Dungeon", true);//офицеров не пускать
			pchar.quest.Alex_Chest.win_condition.l1 = "location";
			pchar.quest.Alex_Chest.win_condition.l1.location = "Bermudes_Dungeon";
			pchar.quest.Alex_Chest.function = "AlexClock_Chest";
			pchar.quest.AlexClock_Over.over = "yes"; //снять прерывание
			pchar.questTemp.AlexClock = "chest";
			AddQuestRecord("alex_clock", "3");
		break;
		
		case "clock_complete":
			dialog.text = "Oni po prostu cię wysłuchali i odeszli?";
			link.l1 = "Zgadza się. Okazali się być uprzejmymi, miłymi gośćmi. Wyjaśniłem im, że ich obecność przeraża starego, sławnego szkutnika i z szacunku do waszego wieku opuścili teren. Możesz tam zejść bez obaw.";
			link.l1.go = "clock_complete_1";
		break;
		
		case "clock_complete_1":
			dialog.text = "Ah-ha, kpisz sobie ze starego człowieka! Dobrze. Daj mi moją skrzynkę, a ja ją otworzę i dam ci urządzenie, które uczciwie zdobyłeś.";
			link.l1 = "Proszę, weź to...";
			link.l1.go = "clock_complete_2";
		break;
		
		case "clock_complete_2":
			RemoveItems(pchar, "alexs_chest", 1);
			dialog.text = "Wdzięczność! Otwórzmy to. Proszę, weź to. Automatyczny mechaniczny timer, nikt tutaj nie robi takich urządzeń i nikt nie będzie przez następne trzysta lat... ech, przepraszam, proszę wybaczyć staremu człowiekowi. Wszystko, co chcę powiedzieć, to że ta rzecz jest unikalna\nSam wykonuje całą pracę, nie będziesz potrzebować głupich klepsydr i tak dalej. Żadnych błędów! Po prostu trzymaj to z dala od bezpośrednich uderzeń i wody, w przeciwnym razie stracisz to. Nawet małpa potrafi obsługiwać ten timer.";
			link.l1 = "Daj mi to zobaczyć! Nigdy w życiu nie widziałem czegoś tak cudownego! Dzięki, mistrzu.";
			link.l1.go = "clock_complete_3";
		break;
		
		case "clock_complete_3":
			GiveItem2Character(pchar, "clock3");
			Log_Info("You've received an automatic mechanical timer");
			SetAlchemyRecipeKnown("sextant2");
			PlaySound("interface\important_item.wav");
			dialog.text = "Nie ma za co. Teraz zawsze będziesz wiedział, która jest godzina. Nie pytaj mnie, skąd to mam. Nie powiem ci.";
			link.l1 = "Wszyscy mają swoje sekrety, prawda mistrzu? Dobrze... zatrzymaj swoje tajemnice, a ja nie będę się wtrącać w twoje sprawy. Dzięki za prezent!";
			link.l1.go = "clock_complete_4";
		break;
		
		case "clock_complete_4":
			dialog.text = "I dziękuję za pomoc, kapitanie. Odwiedzaj mnie czasem. Nie zapominaj o starym cieśli.";
			link.l1 = "Jakbym mógł cię zapomnieć... W każdym razie, na pewno to zrobię, Alexusie Mistrzu. Do widzenia!";
			link.l1.go = "clock_complete_5";
		break;
		
		case "clock_complete_5":
			DialogExit();
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", true);
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload1_back", false);
			LocatorReloadEnterDisable("Bermudes_Dungeon", "reload2_back", false);
			LAi_LocationDisableOfficersGen("Bermudes_Dungeon", false);
			AddQuestRecord("alex_clock", "5");
			CloseQuestHeader("alex_clock");
			DeleteAttribute(pchar, "questTemp.AlexClock");
			// belamour legendary edition на пару с Акулой
			pchar.questTemp.SharkGoldFleet.KGBB = true;
			if(CheckAttribute(pchar,"questTemp.SharkFrigate")) SetTimerCondition("SharkGoldFleet", 0, 0, 30, false);
		break;
	// <-- хронометр Алекса
		
		// город майя
		case "tieyasal":
			dialog.text = "Aha, Miguel! Mój stary znajomy. Pamiętam go. Pytał mnie o każdy drobny szczegół raz za razem. Ale jak miałem mu wytłumaczyć, jak skonstruowane jest radio wewnątrz, skoro nie widział nawet prostego telegrafu?";
			link.l1 = "Co?.. O czym ty mówisz, mistrzu?";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Och, przepraszam, młody człowieku. Nie zwracaj zbytnio uwagi na moje gadanie... Nasz ciekawski Michel zaspokoił swoją ciekawość i zniknął. Zaledwie trzy dni temu mieliśmy rozmowę.";
			link.l1 = "Gdzie jest teraz Miguel, jeśli można zapytać?";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "Kto wie. Może załatwia swoje interesy w Sharptown, a może już odpłynął z Isla Tesoro.";
			link.l1 = "Rozumiem. Dzięki, mistrzu!";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			DialogExit();
			npchar.quest.tieyasal = "true";
		break;
		
		// Калеуче
		case "FDM":
			if(CheckAttribute(npchar, "quest.FDM_secondtime"))
				dialog.text = "Znowu z tym twoim 'statkiem widmo'... Wiedz, że zajmuję się nim tylko z nadzieją, że przekształci się w coś przyzwoitego. W przeciwnym razie nie tknąłbym go nawet kijem. Myślę, że każdy na morzu podziela podobną opinię. Co chcesz z nim zrobić tym razem?";
			else	
				dialog.text = "Ach, ten 'statek widmo'! Matki używają twojego galeonu, by straszyć niegrzeczne dzieciaki. A ty zdecydowałeś się zatrzymać tę przeklętą jednostkę zamiast ją zatopić! Marynarze drżą, gdy widzą twój statek na horyzoncie... Więc, co chcesz z nim zrobić?";
			if (!CheckAttribute(npchar, "quest.FDM_cabin"))
			{
				link.l1 = "Lubię pomysł małych tchórzy, którzy boją się jak cholera. Ale wnętrze mnie smuci. Widziałeś kajutę? Czuję się w niej jak w trumnie. Wszystkie te pleśnie i kurz. Chcę to naprawić. Czy możesz to zrobić, mistrzu?";
				link.l1.go = "FDM_cabin";
			}
			if (!CheckAttribute(npchar, "quest.FDM_sails"))
			{
				link.l2 = "Dość mam tych podartych czarnych szmat. Przyznaję, że łapią wiatr tak samo dobrze jak zwykłe żagle, ale widok... Obrzydliwy. Chcę zwykłe śnieżnobiałe żagle. Jesteś gotów, mistrzu?";
				link.l2.go = "FDM_sails";
			}
			
			if (!CheckAttribute(npchar, "quest.FDM_hull"))
			{
				link.l3 = "Cóż, myślę, że nadszedł czas, aby przerobić go na coś przyzwoitego. Statek jest dobry, załoga się do niego przyzwyczaiła, ale to po prostu niegodne szacownego kapitana, aby żeglować na statku, który może przerazić dorosłych, nie wspominając o dzieciach. Chcę go całkowicie przebudować, aby inni kapitanowie zazdrościli mi, gdy zobaczą mój statek, zamiast się żegnać. A do kogo innego mam się z tym zwrócić, jak nie do najlepszego szkutnika na archipelagu?";
				link.l3.go = "FDM_hull";
			}
		break;
		
		case "FDM_cabin":
			dialog.text = "Dlaczego nie? Moje ręce wciąż są sprawne. Twój galeon jest ogromny, więc mogę nawet zrobić królewską kabinę, jaką budują na okrętach i statkach wojennych. Albo możemy zostawić standardową kabinę. Wybór należy do ciebie?";
			link.l1 = "Zbuduj kajutę liniowca! Wszyscy umrą z zazdrości...";
			link.l1.go = "FDM_cabin_m";
			link.l2 = "Nie ma sensu przesadzać z luksusami. Trzymaj standard.";
			link.l2.go = "FDM_cabin_s";
		break;
		
		case "FDM_cabin_m":
			dialog.text = "Dobrze. Dziesięć skrzyń z dublonami i będzie gotowe za pięć dni.";
			link.l1 = "Umowa stoi!";
			link.l1.go = "FDM_cabin_m1";
			link.l2 = "Dziesięć skrzyń? Tysiąc pięćset dublonów? Hm, potrzebuję czasu, by rozważyć takie wydatki...";
			link.l2.go = "exit";
		break;
		
		case "FDM_cabin_s":
			dialog.text = "Dobrze. Siedem skrzyń z dublonami i będzie to zrobione w pięć dni.";
			link.l1 = "Umowa stoi!";
			link.l1.go = "FDM_cabin_s1";
			link.l2 = "Siedem skrzyń? Ponad tysiąc doblonów? Hm, potrzebuję czasu, aby rozważyć takie wydatki...";
			link.l2.go = "exit";
		break;
		
		case "FDM_cabin_m1":
			iTemp = GetCharacterItem(pchar, "Chest");
			npchar.quest.FDM_cabin = 10;
			npchar.quest.FDM_cabin.type = "Cabin_Huge";
			dialog.text = "Dobrze, będę czekał na zapłatę.";
			if (iTemp > 0)
			{
				link.l1 = "   Mam ze sobą kufry. Zobaczmy. Tutaj,   "+FindRussianQtyString(iTemp)+".";
				link.l1.go = "FDM_cabin_pay";
			}
			else
			{
				link.l1 = "Muszę iść i włożyć monety do skrzyń.";
				link.l1.go = "FDM_cabin_wait";
			}
		break;
		
		case "FDM_cabin_s1":
			iTemp = GetCharacterItem(pchar, "Chest");
			npchar.quest.FDM_cabin = 7;
			npchar.quest.FDM_cabin.type = "Cabin";
			dialog.text = "Dobrze, będę czekał na zapłatę.";
			if (iTemp > 0)
			{
				link.l1 = "Mam ze sobą skrzynie. Zobaczmy. Oto, "+FindRussianQtyString(iTemp)+".";
				link.l1.go = "FDM_cabin_pay";
			}
			else
			{
				link.l1 = "Muszę iść i wkładać monety do skrzyń.";
				link.l1.go = "FDM_cabin_wait";
			}
		break;
		
		case "FDM_cabin_wait":
			DialogExit();
			npchar.quest.FDM_full = "cabin";
		break;
		
		case "FDM_cabin_pay":
			iTemp = GetCharacterItem(pchar, "Chest");
			amount = sti(npchar.quest.FDM_cabin)-iTemp;
			Log_Info("You have given chests to Master Alexus");
			PlaySound("interface\important_item.wav");
			if (amount <= 0) // всё принес
			{
				RemoveItems(pchar, "chest", sti(npchar.quest.FDM_cabin));
				dialog.text = "Więc musiałeś mi przynieść "+FindRussianQtyString(sti(npchar.quest.FDM_cabin))+"skrzynie, które przyniosłeś"+FindRussianQtyString(iTemp)+" . Mam zapłatę. Teraz moja kolej. Idź i pospaceruj. Nie martw się, zrobię wszystko, co w mojej mocy.";
				link.l1 = "Dobrze...";
				link.l1.go = "FDM_cabin_do";
			}
			else
			{
				RemoveItems(pchar, "chest", iTemp);
				dialog.text = "Więc, musiałeś mi przynieść "+FindRussianQtyString(sti(npchar.quest.FDM_cabin))+" skrzynie, które przyniosłeś "+FindRussianQtyString(iTemp)+". "+FindRussianQtyString(amount)+"  skrzynie zostały.";
				link.l1 = "Bardzo dobrze, panie.";
				link.l1.go = "FDM_cabin_wait";
				npchar.quest.FDM_cabin = amount;
			}
		break;
		
		case "FDM_cabin_do":
			DialogExit();
			SetLaunchFrameFormParam("Five days later..."+ NewStr() +"Master Alexus has done his job", "", 0, 5);
			WaitDate("", 0, 0, 5, 0, 10); //крутим время
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			shTo = &RealShips[sti(Pchar.Ship.Type)];
			shTo.CabinType = npchar.quest.FDM_cabin.type;
			if (CheckAttribute(npchar, "quest.FDM_sails")) npchar.quest.FDM_full = "done";
			else DeleteAttribute(npchar, "quest.FDM_full");
		break;
		
		case "FDM_sails":
			dialog.text = "Oczywiście, mogę to zrobić! No cóż... To oznacza, że musimy wyrzucić wszystkie brudne stare szmaty i zamontować nowe, czyste żagle z bawełny. Dużo pracy nas czeka. Sto tysięcy pesos za pracę i materiały. Umowa?";
			if (sti(Pchar.money) >= 100000)
			{
				link.l1 = "Oczywiście, zgadzam się na to. Umowa stoi!";
				link.l1.go = "FDM_sails_do";
			}
			link.l2 = "Hm. Sądzę, że muszę się nad tym zastanowić...";
			link.l2.go = "exit";
		break;
		
		case "FDM_sails_do":
			AddMoneyToCharacter(pchar, -100000);
			dialog.text = "Dobrze. Mam monety, czas wykonać swoją robotę. Przejdź się, aż będzie gotowe i nie martw się.";
			link.l1 = "Dobre...";
			link.l1.go = "FDM_sails_done";
		break;
		
		case "FDM_sails_done":
			DialogExit();
			SetLaunchFrameFormParam("Two days later..."+ NewStr() +"Master Alexus has done his job", "", 0, 5);
			WaitDate("", 0, 0, 2, 0, 10); //крутим время
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			SetShipSailsFromFile(pchar, "ships/parus_silk.tga");
			SetSailsColor(pchar, 0);//белый хлопковый парус
			npchar.quest.FDM_sails = "true";
			if (CheckAttribute(npchar, "quest.FDM_cabin")) npchar.quest.FDM_full = "done";
		break;
		//--> Xenon
		case "FDM_hull":
			dialog.text = "Cóż, cieszę się, że w końcu to słyszę. I prawdą jest, że wydajesz się być porządnym człowiekiem, ale pływasz na czymś, co nie wiadomo skąd się wzięło. Ale pozwól, że cię uprzedzę, ta robota nie jest na kilka godzin, a kosztować cię będzie niemało.";
			link.l1 = "Czy możesz być trochę bardziej szczegółowy?";
			link.l1.go = "FDM_hull_01";
		break;

		case "FDM_hull_01":
			dialog.text = "Ok, policzmy... Na całkowitą przebudowę kadłuba statku potrzebuję 150 jednostek żelaznego drewna, 130 zwojów lin, 170 bali jedwabiu okrętowego i 200 beczek żywicy. Za to wszystko wezmę 250 tysięcy pesos. I nie patrz tak na mnie - większość tych pieniędzy i tak pójdzie na pracę! W końcu nie odbudowujemy tartany.";
			link.l1 = "Chyba nie. Nie zamierzam przewozić tak ogromnej ilości materiałów, a do tego płacić ćwierć miliona za tę robotę. Chyba będę dalej pływać na tym, jak jest.";
			link.l1.go = "FDM_hull_thinking";
			link.l2 = "Eh, czegoż nie zrobimy dla naszego statku...Dobrze, umowa stoi.";
			link.l2.go = "FDM_hull_02";
		break;

		case "FDM_hull_02":
			dialog.text = "Dobrze, mniej gadania, więcej działania. Będę czekał na pieniądze od ciebie, abym mógł zacząć kupować wszystko, czego potrzebuję. Gdy będę miał pieniądze, możesz zacząć przynosić mi materiały. A ja zabiorę się do pracy nad twoim statkiem.";
			if(sti(pchar.money) >= 250000)
			{
    			link.l1 = "Cóż, pieniądze nie stanowią problemu. Mam je przy sobie. Proszę, mistrzu.";
    			link.l1.go = "FDM_hull_waitmaterials";
            }
            else
            {
    			link.l1 = "Na razie nie mam takich pieniędzy. Poczekaj chwilę, przyniosę je dla ciebie.";
    			link.l1.go = "FDM_hull_waitmoney";
            }
		break;

		case "FDM_hull_waitmaterials":
			addMoneyToCharacter(pchar, -250000);
			npchar.quest.FDMsandal = 0;
			npchar.quest.FDMoil = 0;
			npchar.quest.FDMshipsilk = 0;
			npchar.quest.FDMropes = 0;
			AddQuestRecord("renovate_fdm", "1");

			npchar.quest.FDM_hull = "hull_waitmaterials";
			dialog.text = "„Nie boisz się chodzić po pirackiej osadzie z taką porządną sumką, hehe? Dobra, żartuję, to wszyscy uczciwi ludzie, na swój sposób. Teraz czekam na materiały. Przypominam, musisz dostarczyć łącznie 150 kawałków drewna żelaznego, 130 zwojów lin, 170 bel żaglówki i 200 beczek żywicy.”";
			link.l1 = "Trzymaj się, przyniosę ci twoje materiały.";
			link.l1.go = "exit";
		break;

		case "FDM_hull_checkmaterials":
			dialog.text = "Bardzo dobrze! Co mi dzisiaj przyniosłeś?";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) > 0 && sti(npchar.quest.FDMsandal) < 150)
			{
				iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
				link.l1 = "Żelazne drewno w ilości "+FindRussianQtyString(iSan)+".";
				link.l1.go = "FDM_sandal";
			}
			if (GetSquadronGoods(pchar, GOOD_OIL) > 0 && sti(npchar.quest.FDMoil) < 200)
			{
				iOil = GetSquadronGoods(pchar, GOOD_OIL);
				link.l2 = "Żywica w ilości "+FindRussianQtyString(iOil)+".";
				link.l2.go = "FDM_oil";
			}
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0 && sti(npchar.quest.FDMshipsilk) < 170)
			{
				iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
				link.l3 = "Jedwab na statku w ilości "+FindRussianQtyString(iSil)+".";
				link.l3.go = "FDM_shipsilk";
			}
			if (GetSquadronGoods(pchar, GOOD_ROPES) > 0 && sti(npchar.quest.FDMropes) < 130)
			{
				iRop = GetSquadronGoods(pchar, GOOD_ROPES);
				link.l4 = "Liny w ilości "+FindRussianQtyString(iRop)+".";
				link.l4.go = "FDM_ropes";
			} 
			link.l5 = "Jeszcze nic. Chciałem tylko upewnić się, że umowa nadal jest aktualna.";
			link.l5.go = "exit";
		break;

		case "FDM_hull_checkmaterials_1":
			if (sti(npchar.quest.FDMsandal) > 149 && sti(npchar.quest.FDMoil) > 199 && sti(npchar.quest.FDMshipsilk) > 169 && sti(npchar.quest.FDMropes) > 129)
			{
				dialog.text = "Wspaniale! Wszystkie materiały są uwzględnione. Teraz pozwól, że zabiorę tego potwora z twoich rąk. W końcu nabierze odpowiedniego wyglądu.";
				link.l1 = "Dość narzekania, majstrze. Z niecierpliwością oczekuję wyniku.";
				link.l1.go = "FDM_hull_building";
			}
			else
			{
				dialog.text = "Masz coś jeszcze, co rozjaśni mi dzień, kapitanie?";
				link.l1 = "Niestety, to wszystko na teraz.";
				link.l1.go = "exit";
				link.l2 = "Tak, mam coś jeszcze dla ciebie...";
				link.l2.go = "FDM_hull_checkmaterials";
			}
		break;

		case "FDM_sandal": // бакаут
			amount = 150 - sti(npchar.quest.FDMsandal);
			iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
			iTemp = amount-iSan;
			if (iTemp > 0) 
			{
				dialog.text = "Zobaczmy... Potrzebuję "+FindRussianQtyString(amount)+" z żelaznego drewna. Przywiozłeś "+FindRussianQtyString(iSan)+". z żelaznego drzewa. Dlatego musisz mi jeszcze przynieść "+FindRussianQtyString(iTemp)+".";
				link.l1 = "Dzięki! Wkrótce przyniosę resztę.";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, iSan);
				npchar.quest.FDMsandal = sti(npchar.quest.FDMsandal) + iSan;
				AddQuestRecord("renovate_fdm", "2");
				AddQuestUserData("renovate_fdm", "sGood", "ironwood");
				AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				dialog.text = "Zobaczmy... Wciąż potrzebuję "+FindRussianQtyString(amount)+" z żelaznego drewna. Przyniosłeś mi "+FindRussianQtyString(iSan)+"Zatem skończyliśmy z żelaznym drzewem!";
				link.l1 = "Dzięki!";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, amount);
				npchar.quest.FDMsandal = sti(npchar.quest.FDMsandal) + amount;
				AddQuestRecord("renovate_fdm", "3");
				AddQuestUserData("renovate_fdm", "sGood", "ironwood"); 
			}
		break;

		case "FDM_oil": // смолы
			amount = 200 - sti(npchar.quest.FDMoil);
			iOil = GetSquadronGoods(pchar, GOOD_OIL);
			iTemp = amount-iOil;
			if (iTemp > 0) 
			{
				dialog.text = "Zobaczmy... Potrzebuję "+FindRussianQtyString(amount)+" żywicy. Przywiozłeś "+FindRussianQtyString(iOil)+" Dlatego nadal musisz mi przynieść "+FindRussianQtyString(iTemp)+".";
				link.l1 = "Dzięki! Resztę przyniosę wkrótce.";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, iOil);
				npchar.quest.FDMoil = sti(npchar.quest.FDMoil) + iOil;
				AddQuestRecord("renovate_fdm", "2");
				AddQuestUserData("renovate_fdm", "sGood", "resin");
				AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				dialog.text = "Zobaczmy... Wciąż potrzebuję "+FindRussianQtyString(amount)+" żywicy. Przyniosłeś mi "+FindRussianQtyString(iOil)+"Zatem skończyliśmy z żywicą!";
				link.l1 = "Dzięki!";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, amount);
				npchar.quest.FDMoil = makeint(npchar.quest.FDMoil) + amount;
				AddQuestRecord("renovate_fdm", "3");
				AddQuestUserData("renovate_fdm", "sGood", "resin");
			}
		break;

		case "FDM_shipsilk": // шёлк
			amount = 170 - sti(npchar.quest.FDMshipsilk);
			iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
			iTemp = amount-iSil;
			if (iTemp > 0) 
			{
				dialog.text = "Zobaczmy... Potrzebuję "+FindRussianQtyString(amount)+" z jedwabiu statku. Przywiozłeś "+FindRussianQtyString(iSil)+"Zatem, nadal musisz mi przynieść "+FindRussianQtyString(iTemp)+".";
				link.l1 = "Dzięki! Wkrótce przyniosę resztę";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, iSil);
				npchar.quest.FDMshipsilk = sti(npchar.quest.FDMshipsilk) + iSil;
				AddQuestRecord("renovate_fdm", "2");
				AddQuestUserData("renovate_fdm", "sGood", "ship silk");
				AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				dialog.text = "Zobaczmy... Wciąż potrzebuję "+FindRussianQtyString(amount)+" jedwabiu na statek. Dlatego wciąż musisz mi przynieść "+FindRussianQtyString(iSil)+"  Zatem, skończyliśmy z jedwabiem okrętowym";
				link.l1 = "Dzięki!";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, amount);
				npchar.quest.FDMshipsilk = sti(npchar.quest.FDMshipsilk) + amount;
				AddQuestRecord("renovate_fdm", "3");
				AddQuestUserData("renovate_fdm", "sGood", "ship silk"); 
			}
		break;

		case "FDM_ropes": // канаты
			amount = 170 - sti(npchar.quest.FDMropes);
			iRop = GetSquadronGoods(pchar, GOOD_ROPES);
			iTemp = amount-iRop;
			if (iTemp > 0) 
			{
				dialog.text = "Zobaczmy... Potrzebuję "+FindRussianQtyString(amount)+" lin do żagli. Przyniosłeś "+FindRussianQtyString(iRop)+"Zatem, nadal musisz mi przynieść "+FindRussianQtyString(iTemp)+".";
				link.l1 = "Dzięki! Wkrótce przyniosę resztę.";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, iRop);
				npchar.quest.FDMropes = sti(npchar.quest.FDMropes) + iRop;
				AddQuestRecord("renovate_fdm", "2");
				AddQuestUserData("renovate_fdm", "sGood", "ropes");
				AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				dialog.text = "Zobaczmy... Potrzebuję "+FindRussianQtyString(amount)+" lin z konopi. Przyniosłeś "+FindRussianQtyString(iRop)+"Zatem, skończyliśmy z linami!";
				link.l1 = "Dzięki!";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, amount);
				npchar.quest.FDMropes = sti(npchar.quest.FDMropes) + amount;
				AddQuestRecord("renovate_fdm", "3");
				AddQuestUserData("renovate_fdm", "sGood", "ropes");
			}
		break;

		case "FDM_hull_thinking":
			DialogExit();
			npchar.quest.FDM_secondtime = true;
		break;

		case "FDM_hull_waitmoney":
			DialogExit();
			npchar.quest.FDM_hull = "hull_waitmoney";
		break;

		case "FDM_hull_givemoney":
			dialog.text = "Cóż, przyniosłeś pieniądze";
			if(sti(pchar.money) >= 250000)
			{
    			link.l2 = "Tak, zrobiłem. 250 000 pesos, jak ustalono.";
    			link.l2.go = "FDM_hull_waitmaterials";
            }
            else
            {
    			link.l1 = "Jeszcze nie, poczekaj, mistrzu.";
    			link.l1.go = "exit";
            }
		break;

		case "FDM_hull_building":
			DialogExit();
			SetLaunchFrameFormParam("Five days passed..."+ NewStr() +"Master Alexus completed the job", "", 0, 5);
			WaitDate("", 0, 0, 5, 0, 10); //Pass time
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			RealShips[sti(Pchar.Ship.Type)].BaseType = SHIP_RENOVATED_FDM;
			RealShips[sti(Pchar.Ship.Type)].Name = "NewFlyingdutchman1";
			RealShips[sti(Pchar.Ship.Type)].BaseName = "NewFlyingdutchman";
			/* RealShips[sti(Pchar.Ship.Type)].CannonsQuantity = 58;
			RealShips[sti(Pchar.Ship.Type)].CannonsQuantityMax = 58;
			RealShips[sti(Pchar.Ship.Type)].CannonsQuantityMin = 58;
			RealShips[sti(Pchar.Ship.Type)].rcannon = 24;
			RealShips[sti(Pchar.Ship.Type)].lcannon = 24;
			RealShips[sti(Pchar.Ship.Type)].fcannon = 6;
			RealShips[sti(Pchar.Ship.Type)].bcannon = 4; */
			if(Get_My_Cabin() == "My_Cabin") RealShips[sti(Pchar.Ship.Type)].CabinType = "Cabin";	
			else RealShips[sti(Pchar.Ship.Type)].CabinType = "Cabin_Huge";
			SetShipSailsFromFile(pchar, "ships/parus_silk.tga");
			SetSailsColor(pchar, 0);//White cotton sail
			RealShips[sti(Pchar.Ship.Type)].HP = GetCharacterShipBaseHP(pchar);
			pchar.ship.hp = GetCharacterShipBaseHP(pchar);
			DeleteAttribute(pchar, "ship.hulls");
			DeleteAttribute(pchar, "ship.blots");	
			CloseQuestHeader("renovate_fdm");
		break;
		//<-- Xenon
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

void checkMatherial_repair(ref Pchar, ref NPChar, int good, int goodType)
{
	int amount;
	string Matherial = "Matherial" + goodType;
	amount = GetSquadronGoods(Pchar, good) - sti(NPChar.Repair.(Matherial));
	
	if (amount < 0)
    {
		amount = amount + sti(NPChar.Repair.(Matherial));
    }
    else
    {
		amount = sti(NPChar.Repair.(Matherial));
    }
    RemoveCharacterGoods(Pchar, good, amount);
    NPChar.Repair.(Matherial) = sti(NPChar.Repair.(Matherial)) - amount;
}

int GetMaterialQtyRepair( ref _chr, int MaterialNum )
{
	if ( sti(_chr.Ship.Type) == SHIP_NOTUSED) return 0;
	
	int   	shipCurHP   = sti(RealShips[sti(_chr.Ship.Type)].HP);
	int   	shipBaseHP	= sti(RealShips[sti(_chr.Ship.Type)].BaseHP);	
	int   	shipClass   = sti(RealShips[sti(_chr.Ship.Type)].Class);
	int     shipWeight  = CWT2Tonnes(sti(RealShips[sti(_chr.Ship.Type)].Weight));
	int     HPPrice     = shipWeight * (1.2 - makefloat(shipCurHP)/makefloat(shipBaseHP));
	int     modifier    = (2 * MOD_SKILL_ENEMY_RATE) + sti(RealShips[sti(_chr.Ship.Type)].MinCrew)/2 + 1;	

	float   fQuest 	= 1.0;
	if(CheckAttribute(&RealShips[sti(_chr.Ship.Type)], "QuestShip")) 
	{
		fQuest  = 1.3;
		HPPrice = HPPrice * 2;
	}					
	
	int     Matherial1 = makeint(fQuest * (10 + MOD_SKILL_ENEMY_RATE) * (7 - shipClass) / 2) + rand(modifier);
	int     Matherial2 = makeint(fQuest * (10 + MOD_SKILL_ENEMY_RATE) * (7 - shipClass) / 2) + rand(modifier);
	int     Matherial3 = makeint(fQuest * (10 + MOD_SKILL_ENEMY_RATE) * (7 - shipClass) / 2) + rand(modifier);
	int     Matherial4 = makeint(fQuest * (10 + MOD_SKILL_ENEMY_RATE) * (7 - shipClass) / 2) + rand(modifier);
		
	if(MaterialNum == 0) return HPPrice;	
	if(MaterialNum == 1) return Matherial1;
	if(MaterialNum == 2) return Matherial2;
	if(MaterialNum == 3) return Matherial3;
	if(MaterialNum == 4) return Matherial4;
	
	return 0;
}

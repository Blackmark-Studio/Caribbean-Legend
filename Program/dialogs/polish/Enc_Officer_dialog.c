// BOAL новый диалог офицера и компаньона 21/06/06
void ProcessDialogEvent()
{
	ref NPChar, d;
	aref Link, Diag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);
	
	ref    	sld, rItm, rItem;
	string 	attr, attrLoc, sGun, sBullet, attrL, sAttr;
	int    	iTemp, iTax, iFortValue, i;
	aref 	rType;
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
        case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = RandPhraseSimple("Heh, kapitanie, połowa garnizonu cię teraz goni. Na pewno to nie jest najlepszy czas, aby zatrudniać się w twojej załodze!","I walczyć, żeby przedrzeć się do statku? Nie, kapitanie, w innym czasie...");
				link.l1 = RandPhraseSimple("Jak sobie życzysz...","Właściwie, nie zamierzałem cię zatrudniać."); 
				link.l1.go = "exit";
				break;
			}
			Diag.TempNode = "OnceAgain";
			dialog.text = "Czy potrzebujesz oficera, kapitanie?";
			if (FindFreeRandomOfficer() > 0)
			{
    			Link.l1 = "Oficer? A czym się dobrze zajmujesz?";
    			Link.l1.go = "Node_2";
			}
			Link.l2 = "Nie, mam pełny zestaw.";
			Link.l2.go = "Exit";			
		break;
		
		case "CitizenNotBlade":
			dialog.text = "Kapitanie, co robisz? Odłóż swoją broń, zanim narobisz dużo kłopotów!";
			link.l1 = LinkRandPhrase("Dobrze.","Dobrze.","Nie martw się, odkładam to...");
			link.l1.go = "exit";
		break;
		
		case "hired":
			Diag.TempNode = "Hired";
			// только наняли -->
			if (IsCompanion(NPChar))
			{
				Dialog.text = "Dzisiaj w końcu wypływamy!";
				link.l2 = "Tak... Jestem zadowolony.";
				link.l2.go = "Exit";
				break;
			}
			if (Npchar.location.group == "sit" && !isShipInside(pchar.location))
			{
				dialog.text = "Dopiję tylko swój trunek, kapitanie, a potem pójdę na statek. Nie martw się - będę tam na czas.";
				Link.l1 = "Dobrze. Jeśli spóźnisz się, kazał będę ci szorować pokład!";
				Link.l1.go = "Exit";
				break;
			}
			// только наняли <--
   			dialog.text = "Co chcesz, kapitanie?";
			// диалог компаньона на корабле.
			if (CheckAttribute(NPChar, "IsCompanionClone"))
			{
				Link.l2 = "Muszę wydać ci kilka poleceń.";
				Link.l2.go = "Companion_Tasks";
				break;
			}
			
			// на Тайясаль
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l66 = ""+npchar.name+", Idę do starego indyjskiego miasta Tayasal. To będzie niebezpieczna i niezwykła podróż - przez teleportacyjny idol. Dołączysz do mnie?";
				if(npchar.id == "Folke")
				{
					Link.l66 = ""+npchar.name+", Mam do Ciebie poważną prośbę - prawdziwy interes, samobójczy, ale cholernie zyskowny. Potrzebuję lojalnego człowieka na wyprawę do starożytne indyjskiego miasta. Jesteś ze mną?";
				}
				if(npchar.id == "Duran")
				{
					Link.l66 = "Claude, kiedyś narzekałeś, że najemnicy są niedopłaceni.";
				}
				Link.l66.go = "tieyasal";
			}
			
			if (isOfficer(Npchar)) // проверка для кампуса, где слотовые офы
			{
				Link.l2 = "Teraz słuchaj mojego rozkazu!";
				Link.l2.go = "stay_follow";
			}

           		// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l8 = "Daj mi szczegółowy raport o stanie statku, "+GetStrSmallRegister(XI_ConvertString("skarbnik"))+".";
			    Link.l8.go = "QMASTER_1";
			        
			    // Warship. Автозакупка товара
			    if(!CheckAttribute(PChar, "TransferGoods.Enable"))
			    {
				    Link.l11 = "Chcę, abyś kupił towary, podczas gdy przebywamy w kolonii.";
				    Link.l11.go = "TransferGoodsEnable";
			    }
			    else
			    {
				    Link.l11 = "Wiesz, już nie musimy kupować towarów w koloniach.";
				    Link.l11.go = "TransferGoodsDisable";
			    }
			}
			
			if (pchar.location != "My_Campus") // patch-5
			{
			Link.l4 = "Oficerze, twoje usługi już nie są potrzebne.";
			Link.l4.go = "AsYouWish";
			}
			
			
			// по тек локации определим можно ли тут приказать  -->
			if(IsEntity(&loadedLocation))
			{
				if(CheckAttribute(loadedLocation, "fastreload"))
				{
					iTemp = FindColony(loadedLocation.fastreload);
					if(iTemp != -1)
					{
						sld = GetColonyByIndex(iTemp);
						if(sti(sld.HeroOwn) == true && !CheckAttribute(sld, "OfficerIdx"))
						{
							NPChar.ColonyIdx = iTemp;
							Link.l7 = "Mianuję cię zastępcą tego miasta!";
							Link.l7.go = "Gover_Hire";
						}
					}
				}
			}
			
			Link.l9 = "Nic. Wystarczy!";
			Link.l9.go = "Exit";
		break;
		
		// Тайясаль
		case "tieyasal":
			if(npchar.id == "Folke")
			{
				dialog.text = "Cholera, Kapitanie! Myślałem, że pozbyłeś się mnie przy pierwszej okazji, ale jak zawsze mnie zaskoczyłeś. Oczywiście, jestem z tobą, i dzięki za to, że dałeś temu idiocie prawdziwe życie morskiego wilka!";
				Link.l1 = "Dobrze idzie, "+npchar.name+"!";
				Link.l1.go = "folke_tieyasal";
				break;
			}
			if(npchar.id == "Duran")
			{
				dialog.text = "He? Czy naprawdę to powiedziałem?";
				Link.l1 = "Zrobiłeś to. Uważnie cię wtedy słuchałem i jestem gotów naprawić niesprawiedliwość.";
				Link.l1.go = "Duran_tieyasal";
				break;
			}
			dialog.text = LinkRandPhrase("Przykro mi, kapitanie, ale na to nie poszedłem. Nie myśl, że jestem tchórzem, ale nie chcę iść i stawić czoła pewnej śmierci. Jeszcze nie mam dość życia - jeszcze nie. Możesz mnie zwolnić, jeśli chcesz.","Kapitanie, przepraszam, ale - nie. Morza, abordaże, wrogie miasta - to jest w porządku, ale nie chcę się mieszać w to indiańskie czary. Jeśli jesteś niezadowolony z mojej odpowiedzi, możesz anulować naszą umowę.","Chcesz niemożliwego, kapitanie, i zdajesz sobie z tego sprawę. Nikt nie wróci stąd żywy, włącznie z tobą, więc podziękuję. Jeśli uważasz moją odmowę za naruszenie warunków kontraktu, możesz go anulować.");
			link.l1 = LinkRandPhrase("Nie winię cię, oficerze. Doskonale to rozumiem.","Szkoda, ale rozumiem cię. Dlatego mówiłem ci o tym wcześniej.","Liczyłem na ciebie... Ale rozumiem twoją pozycję, oficerze.");
			link.l1.go = "tieyasal_1";
		break;
		
		case "Duran_tieyasal":
			dialog.text = "Heh! Czy podniesiesz mi wtedy płacę?";
			Link.l1 = "Nie ma mowy! Idę do starożytnego miasta Indian. Praca jest samobójcza, ale tam będzie złoto...";
			Link.l1.go = "Duran_tieyasal_2";
		break;
		
		case "Duran_tieyasal_2":
			dialog.text = "Nie jestem zainteresowany złotem. Byłbym zaszczycony, mogąc Ci pomóc, Kapitanie, jak kiedyś ty pomogłeś mi. Kiedy wyruszamy?";
			Link.l1 = "Dobrze powiedziane, Claude! Bądź w pełnej gotowości - już długo nie będzie.";
			Link.l1.go = "Duran_tieyasal_3";
		break;
		
		case "Duran_tieyasal_3":
			DialogExit();
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "folke_tieyasal":
			Achievment_Set("ach_CL_108");
			DialogExit();
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "tieyasal_1":
			DialogExit();
			npchar.quest.Tieyasal = "true";
		break;
		
		case "TransferGoodsEnable":
			if(sti(PChar.Ship.Type) == SHIP_NOTUSED)
	        {
				dialog.text = "Kapitanie, jakie towary? Najpierw musimy znaleźć sobie statek!";
				Link.l1 = "Tak, masz rację.";
				Link.l1.go = "Exit";
				Diag.TempNode = "Hired";
				break;
	        }
	        	
			PChar.TransferGoods.Enable = true;
		//	PChar.TransferGoods.TreasurerID = NPChar.id;
			Dialog.text = "Będzie zrobione, "+GetSexPhrase("panie","panna")+" kapitanie!";
			Link.l1 = "Na spoczynek.";
			Link.l1.go = "TransferGoodsEnable_2";
        break;
        	
		case "TransferGoodsEnable_2":
			Diag.CurrentNode = "Hired";
			DialogExit();
			LaunchTransferGoodsScreen(); // Интерфейс автозакупки товаров
		break;
		
		case "TransferGoodsDisable":
			DeleteAttribute(PChar, "TransferGoods.Enable");
			Dialog.text = "Zostanie to zrobione, "+GetSexPhrase("panie","panno")+" kapitanie!";
			Link.l1 = "Na łatwość.";
			Link.l1.go = "exit";
			Diag.TempNode = "Hired";
		break;
        
		case "ShowParam_exit":
			Diag.CurrentNode = "OnceAgain";
			NPChar.quest.meeting = true;
			DialogExit();
			
			PChar.SystemInfo.OnlyShowCharacter = true;
            LaunchCharacter(NPChar);
		break;
		
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();			
		break;

		case "exit_hire":
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
			if(CheckAttribute(pchar,"systeminfo.tutorial.Fighter") && Npchar.quest.officertype == "fighter")
			{
				DeleteAttribute(pchar,"systeminfo.tutorial.Fighter");
				LaunchTutorial("Fighter", 1);
			}
		break;

		case "exit_fire":
			//navy -->
			if (CheckAttribute(NPChar, "PGGAi"))
			{
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();			
				break;
			}
			//navy <--
			Diag.TempNode = "Fired";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");

			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;

			DialogExit();			
		break;
		
		// boal 29.05.04 офицер хочет свалить -->
        case "WantToGo":
			if (npchar.id == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_SobytieKlodDuran"))
			{
				SetTimerCondition("SKD_DuranTavern", 0, 0, 30, false);
				pchar.questTemp.SKD_SobytieKlodDuran = true;
			}
			chrDisableReloadToLocation = false;
			Diag.TempNode = "Hired";
			dialog.text = LinkRandPhrase(LinkRandPhrase("Kapitanie, wiesz, ja... No, chciałbym cię prosić o zwolnienie mnie. Czas mi się osiedlić, ożenić i mieć trochę dzieci. Nadal nie mam własnego domu, kiedy zestarzeję się, nie będzie nikogo, kto przyniósłby mi szklankę wody.","Kapitanie, proszę, pozwól mi zrezygnować. Przez te wszystkie lata bujałem się po całym świecie, a tak naprawdę nic nie widziałem. Chcę tylko zacząć nowe życie, rzucić kotwicę i zobaczyć świat z innej perspektywy.","Kapitanie, służba w marynarce to na pewno coś wspaniałego, jest dobry zysk i przygoda, ale nadszedł czas, aby pomyśleć o sobie. Wiesz, rzucić kotwicę w cichym porcie, kupić dom, mieć dzieci. Proszę, pozwól mi odejść."),LinkRandPhrase("Kapitanie, wiesz, naprawdę mi przykro, ale mam dość tych wszystkich obowiązków, wart i dyscypliny. Wiesz, chciałbym po prostu żyć wolnym życiem przynajmniej na jakiś czas, ale zdaję sobie sprawę, że nie będziesz na mnie czekać, więc... Czy mógłbyś mnie zwolnić?","Kapitanie, wiesz... Jest taka mała łódź, na którą mnie stać, więc... Myślę, że to chyba czas, aby zacząć moje własne przedsięwzięcie. Proszę, czy mógłbyś mnie puścić?","Kapitanie, właśnie zaproponowano mi stanowisko w porcie. Właściwie, od dawna marzyłem o zacumowaniu i osiedleniu się do życia małżeńskiego. Proszę, pozwól mi odejść. Naprawdę nie mogę przegapić takiej okazji."),LinkRandPhrase("Kapitanie, jestem naprawdę chory na morze. Lekarze mówią mi, że to idiosynkrazja. Proszę, na miłość boską, pozwól mi odejść, bo w końcu skoczę za burtę.","Kapitanie, myślę, że nadszedł dla mnie czas, aby osiąść i znaleźć sobie spokojniejsze miejsce. Wiesz, boję się. Boję się zbłąkanych kul, boję się umrzeć podczas abordażu. Modlę się do Pana, aby utrzymał mnie przy życiu, a kiedy zamykam oczy, widzę wszystkie niewinne dusze, które zabiłem. Błagają mnie, abym ich oszczędził... Proszę, okaz mi trochę współczucia i pozwól mi odejść.","Kapitanie, moje stare rany bolą, a ostatnie stłuczenie przypomina o sobie każdego dnia. Wkrótce mnie zwolnisz, a kto mnie potem zatrudni? Proszę, pozwól mi odejść, opatrzyłem się i znajdę spokojniejsze miejsce."));
			Link.l1 = RandPhraseSimple(LinkRandPhrase("Wszyscy w końcu odchodzą. Dobrze, możesz iść.","Mogę zrozumieć twoje powody. Prędzej czy później wszystko dobiega końca. No cóż, idź więc... i nie żywić urazy, jeśli kiedykolwiek cię uraziłem.","Znowu to samo? Specjalnie wybrałeś najmniej dogodny moment, żeby mnie zostawić, prawda? Cokolwiek. Żegnaj."),LinkRandPhrase("Trudno uwierzyć w to, co mi mówisz... Dobrze, pakuj swoje rzeczy i idź.","Ty? Nie spodziewałem się... Po tylu latach walki ramię w ramię... Cóż, nie zatrzymuję cię. Niech Bóg ci sprzyja.","Brzmisz poważnie. Cóż, życzę ci szczęścia, wiedz, że będę za tobą tęsknił."));				
			Link.l1.go = "WantToGo_free";
			if (sti(Pchar.money) >= sti(NPChar.rank)*250)
			{
				Link.l2 = LinkRandPhrase("Rozumiem... Więc tak to jest, co? A ja liczyłem na ciebie... No cóż, jeśli już podjąłeś decyzję, to rozstaniemy się. Weź "+sti(NPChar.rank)*250+" pesos za twoją lojalną służbę. I nie miej do mnie urazy, jeśli kiedykolwiek cię uraziłem.","Cóż, nie żywię urazy i nie pamiętam zła. Jeśli tak zdecydowałeś, to idź. I weź "+sti(NPChar.rank)*250+" pesos, aby zacząć od nowa, na pewno się przyda.","Rozumiem... No cóż, prędzej czy później musiało się to zdarzyć. Dam ci "+sti(NPChar.rank)*250+" pesos, aby uregulować twoje życie. I dbaj o swoje zdrowie, służba morska pełna jest trudności..."); 
				Link.l2.go = "Im_kind_A2_1";
			}
			Link.l3 = LinkRandPhrase("Tak mówisz... Czy nie zdajesz sobie sprawy, że idąc teraz po prostu wbijasz mi nóż w plecy? Nie mogę cię teraz puścić, nawet o tym nie myśl.","To są nowiny! Wiesz, ludzie powinni mnie o takich rzeczach uprzedzać z wyprzedzeniem! Więc na jakiś czas zapomnij o swoim prywatnym życiu. Kiedy nadejdzie czas, podpowiem ci, kiedy odejść na emeryturę.","Bez rezygnacji. Mam wszystkich na koncie. Nie mogę pozwolić wszystkim odejść tylko z powodu ich osobistego życzenia. Służ, dopóki nie rozważę, czy zasługujesz na urlop.");	
			Link.l3.go = "WantToGo_Stay";
		break;
		
		case "Im_kind_A2_1":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*250)));
			ChangeOfficersLoyality("good_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			dialog.text = "Dziękuję, kapitanie! Naprawdę nieoczekiwana hojność... Wiesz, wciąż mam trochę twoich rzeczy, może chciałbyś je odzyskać?";
			Link.l1 = "Być może... Znalezienie dobrego ostrza nie jest takie łatwe w dzisiejszych czasach.";
			Link.l1.go = "Get_out_А2_chang";
			Link.l2 = "Och, nie zawracaj sobie głowy. Zatrzymaj je jako pamiątkę po swojej służbie.";
			Link.l2.go = "WantToGo_free";
		break;
		
		case "WantToGo_Stay":
			dialog.text = RandPhraseSimple("Ale jak to, kapitanie? Nawet niewolnicy są ostatecznie wysyłani na brzeg. A ja nie jestem niewolnikiem, więc mogę sam decydować o swoim losie!","Kapitanie, służyłem ci wiernie przez cały ten czas. Czy nie zasłużyłem na prawo do samodzielnego decydowania o swoim losie?");
			Link.l1 = LinkRandPhrase("Widzę, że nie mogę cię zatrzymać. Dobrze, co powiesz na jakieś wsparcie finansowe? To nigdy nie zaszkodzi, możesz użyć tych pieniędzy, aby zbudować sobie przytulny dom w cichym porcie lub zadbać o swoje zdrowie.","Dobrze, powiedzmy to tak. Jaką sumę musiałbyś rozważyć, aby zmienić swoją decyzję?","Masz rację. Ale co powiesz na jednorazową dotację pieniężną, czy to by zmieniło twoje zdanie?");
			Link.l1.go = "WantToGo_Stay_2";
			Link.l2 = PCharRepPhrase(RandPhraseSimple("Och, nie, mój przyjacielu, tutaj się mylisz... Gdy marnowałeś swój czas w karczmach, goniąc za spódnicami po kielichach, mogłeś decydować o sobie, ale kiedy postawiłeś stopę na pokładzie mojego statku, powierzyłeś swoje losy w moje ręce.","Hmm. No, to poważne stwierdzenie. Wygląda na to, że zapomniałeś, jak cię znalazłem, w śmierdzącej karczmie bez miedziaka w kieszeni. Nie można ci nawet pokazać jednej złotej monety, bo od razu zamienisz ją na rum. 'Decyduj o moim losie...' Pfff! Co za żart!"),LinkRandPhrase("Dopóki jesteś w mojej służbie, to ja podejmuję decyzje. A teraz, czy mógłbyś wrócić do swoich obowiązków, zanim zdenerwujesz mnie za bardzo!","Hmm. To poważne oświadczenie. Ale jeszcze nie zarobiłeś całej sumy, którą ci wypłacono z góry. Więc twoje demarche można uznać za próbę wymuszenia, prawda?","Ach, rozumiem... Co znowu mówi regulamin statku? Tutaj, paragraf drugi: 'Każdy, kto spróbuje odejść bez pozwolenia, zostanie wylądowany na opuszczonej plaży z jednym workiem prochu, bukłakiem wody, pistoletem i jednym pociskiem.' A więc, jak ci się to podoba?"));	
			Link.l2.go = "WantToGo_Stay_force";
		break;
		
	case "WantToGo_Stay_2":
		dialog.text = LinkRandPhrase("Cóż, to już inna historia. "+sti(NPChar.rank)*500+" pesos na gwoździu, a zostanę z tobą.","No cóż, być może dla "+sti(NPChar.rank)*500+" pesos mogę zostać, przypuszczam.","No dobrze, jeśli tak na to patrzysz, za "+sti(NPChar.rank)*500+" pesos mogę kontynuować swoją służbę.");
		if (sti(Pchar.money) >= sti(NPChar.rank)*500)
		{
			Link.l1 = RandPhraseSimple("Dobrze, zgoda.","Dobrze. Chociaż mogłeś poprosić o mniej.","Widzę, że masz niezły apetyt! Ale, dałem ci przecież obietnicę, prawda? I dotrzymam mojego słowa.");	
			Link.l1.go = "WantToGo_Stay_ForMoney";
		}
		Link.l2 = LinkRandPhrase("To po prostu za dużo. Za taką cenę mógłbym wynająć dwóch oficerów. Może, prościej będzie po prostu cię wypuścić.","Cóż, na pewno masz o sobie wygórowane mniemanie. Dobrze, puszczę cię. Ale zobaczysz sam, kiedy staniesz się swobodny, że twoje życie nie będzie tak bezchmurne, jak się spodziewałeś.","Nie zamierzam płacić takich pieniędzy. Możesz iść, ale nawet nie pytaj o powrót, nie wybaczam zdrady.");				
		Link.l2.go = "WantToGo_free";
	break;
	
	case "WantToGo_Stay_force":
		Npchar.loyality = makeint(Npchar.loyality) - 2;
		dialog.text = "Dobrze, jeśli tak na to patrzysz, zostanę. Ale wiedz, że robiąc to, działam wbrew swojej woli.";
		Link.l1 = LinkRandPhrase("Bardzo dobrze. Wróć do swoich obowiązków, a my kontynuujemy tę rozmowę później.","Wróć do statku. A następnym razem zastanów się dwa razy zanim poprosisz o emeryturę.","Rzeczywiście. Obowiązek to obowiązek, nie powinieneś jeszcze oddawać się swoim fantazjom.");
		Link.l1.go = "exit";
	break;
	
	case "WantToGo_Stay_ForMoney":
		Diag.TempNode = "Hired";
		NPChar.greeting = "Gr_Officer";
		if(NPChar.id == "Duran") NPChar.greeting = "Duran_officer";
		ChangeCharacterComplexReputation(pchar,"authority", 0.2);
		AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
		Npchar.loyality = makeint(Npchar.loyality) + 1;    
		Diag.CurrentNode = Diag.TempNode;
		NPChar.quest.meeting = true;
		DialogExit();
		NPChar.location = "none";
		LAi_SetOfficerType(NPChar);
	break;
	
	case "WantToGo_free":
		//navy -->
		if (CheckAttribute(NPChar, "PGGAi"))
		{	
			pchar.questTemp.FiringOfficerIDX = NPChar.index;
			AddDialogExitQuestFunction("PGG_FireOfficer");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();	
			break;
		}
		//navy <--
		Diag.TempNode = "WantToGo_free_Yet";
		Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
		AddDialogExitQuestFunction("LandEnc_OfficerFired");
		Diag.CurrentNode = Diag.TempNode;
		NPChar.quest.meeting = true;
		DialogExit();
	break;
	
	case "WantToGo_free_Yet":
		Diag.TempNode = "WantToGo_free_Yet";
		dialog.text = LinkRandPhrase("Nie mogę w to uwierzyć! Dziękuję Ci Kapitanie, to takie odciążenie dla mojego umysłu.","Dziękuję Ci, kapitanie, że nie próbujesz mnie zatrzymać. Wiesz, naprawdę chcę spróbować innych rzeczy w życiu.","Heh, teraz będę musiał przyzwyczaić się do mojej nowo odkrytej wolności. Dopiero teraz zdałem sobie sprawę, jak bardzo miałem już dość tej całej służby floty.");	
		Link.l1 = RandPhraseSimple("Cóż, powodzenia dla ciebie.","Jesteś teraz wolny. Twoja służba dobiegła końca.");
		Link.l1.go = "exit";
	break;
	// boal 29.05.04 офицер хочет свалить <--
		
	// пассажир возмущен игроком и сваливает -->
	case "WantToRemove":
		if (npchar.id == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_SobytieKlodDuran"))
		{
			SetTimerCondition("SKD_DuranTavern", 0, 0, 30, false);
			pchar.questTemp.SKD_SobytieKlodDuran = true;
		}
        chrDisableReloadToLocation = false;
		if (Npchar.alignment == "good")
		{
			dialog.text = RandPhraseSimple(LinkRandPhrase("Kapitanie, nie chcę działać wbrew mojemu sumieniu i brać udziału w bandytyzmie.","Kapitanie, nie chcę już uczestniczyć w twoich buntach. Jestem oficerem, nie rzeźnikiem.","Kapitanie, twoje bandyckie metody prowadzenia interesów sprawiają, że niemożliwym staje się dla mnie pozostanie w twojej załodze."),LinkRandPhrase("Kapitanie, muszę przyznać, że moje zatrudnienie przy tobie było rozczarowującym błędem. Nie jestem skłonny poświęcić swojej reputacji dla żadnych pieniędzy.","Kapitanie, zgromadziłeś na swoim statku najbardziej nikczemnych łotrów Nowego Świata. Przyzwoitemu człowiekowi jest obrzydliwie nawet na nich patrzeć. Nie chcę już więcej służyć z taką załogą.","Kapitanie, zatrudniłeś całą załogę łotrów, nie ma ani jednego porządnego człowieka, z którym można by porozmawiać. Gardzę taką służbą."))+" Do widzenia.";
			Link.l1 = "Co?! To jest okręt wojenny, a nie szkoła dla panienek! Możesz pójść wtedy do diabła!";
			Link.l1.go = "exit_fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "Wiedziałem, że wkrótce odejdziesz... ta służba nie jest dla ciebie. Ale nie oskarżaj mnie o nic. Oto "+sti(NPChar.rank)*500+" pesos, przydadzą ci się, kiedy szukasz pracy do swojego gustu.";
				Link.l2.go = "Im_kind_A2";
			}
			Link.l3 = LinkRandPhrase("Ach, to teraz śpiewasz taką pieśń. A co z twoją częścią z każdego rabunku, czy palą ci ręce? Czy planujesz przejść na emeryturę do klasztoru, aby modlić się o przebaczenie swoich grzechów? Wspomnij o nas też! Ha-ha-ha-ha-ha!","Hmm. No, to poważne oświadczenie. A gdzie patrzyło twoje niewinne sumienie, kiedy razem okradaliśmy kupców? Jak zamierzasz je oczyścić? A może zamierzasz nas wydać, abyśmy mogli wisieć na szubienicy w porządnym towarzystwie?","Oj, brawo! Widocznie zapomniałeś, jak cię znalazłem, w cuchnącej tawernie bez grosza przy duszy. Tak dla twojej informacji, jako oficer nie jesteś wart ani miedziaka. Jesteś nic nie wart!");
			Link.l3.go = "WantToGo_stop";
		}
		else
		{
            dialog.text = RandPhraseSimple(LinkRandPhrase("Kapitanie, naprawdę nie lubię twoich szlacheckich gier i nie zamierzam porzucać swoich nawyków dla twojego spokoju. Do widzenia.","Kapitanie, nie mogę już dłużej służyć pod Twoim dowództwem. Straciłem już tyle czasu. Bycie prostym korsarzem przyniosłoby mi już fortunę. Odchodzę.","Kapitanie, twoi ludzie mnie obrzydzają. Nie ma ani jednego porządnego człowieka, tylko sami wytworniacy, z którymi nie da się nawet napić. Odchodzę."),LinkRandPhrase("Kapitanie, jestem doświadczonym oficerem, a twój statek wygląda bardziej jak barka ładunkowa. Nie przepadam za taką służbą. Do widzenia.","Kapitanie, cała twoja załoga to same wytworne panienki, nie ma ani jednego mężczyzny, z którym można by było napić się czy porozmawiać. Mam silną niechęć do takiej obsługi. Do widzenia.","Kapitanie, myślałem, że służę prawdziwemu korsarzowi, ale wszystko, co robimy, to tylko charytatywka! Nie chcę dalej marnować swojego czasu. Odchodzę."));
			Link.l1 = RandPhraseSimple("Rozumiem. Biorąc pod uwagę twoje nastawienie, to miało się zdarzyć prędzej czy później. Dobrze, nie będę cię zatrzymywał.","Twoje oświadczenie nie było niespodzianką. Szczerze mówiąc, od dawna jestem niezadowolony z twojego nastawienia.")+"Powodzenia.";
			Link.l1.go = "exit_fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "Wiedziałem, że niedługo odejdziesz... ta służba nie jest dla ciebie. Ale nie oskarżaj mnie o nic. Oto "+sti(NPChar.rank)*500+" pesos, przydadzą się, kiedy będziesz szukać nowej pracy.";
				Link.l2.go = "Im_kind_A2";
			}
			Link.l3 = RandPhraseSimple("Hmm. To poważne oświadczenie. Ale jeszcze nie odpracowałeś całej sumy, którą zapłacono ci z góry. Więc twoja demarche może być uważana za próbę wyłudzenia, prawda?","Ach, rozumiem... Co mówi regulamin statku? Tutaj, paragraf drugi: 'Ktokolwiek próbuje opuścić statek bez pozwolenia, zostanie wylądowany na opustoszałym brzegu z jednym workiem prochu, bukłakiem wody, pistoletem i jednym pociskiem.' Czy podoba ci się taka perspektywa?");
			Link.l3.go = "WantToGo_stop";
		}
		break;
		
		case "WantToGo_stop":
			if (Npchar.alignment == "good")
			{
				dialog.text = LinkRandPhrase("Nie próbuj nawet mnie obrażać! Pracuję za pieniądze, ale nadal mam prawo wybierać pracę, która mi się podoba!","Jestem wolnym człowiekiem! I mam prawo do podjęcia nowej pracy, kiedy tylko zechcę!","Nie jestem niewolnikiem pracującym za jedzenie, więc moje sumienie jest czyste! Ale już nie będę brał udziału w rabunkach!");
				Link.l1 = "Cóż, tak naprawdę, jesteś w błędzie... Kiedy piłeś w tawernie, mogłeś wybierać jakąkolwiek pracę, która ci się podobała... Ale jak tylko stanąłeś na pokładzie mojego statku, twoją jedyną drogą powrotu stała się kula armatnia, która roztrzaskuje ci szyję... A z wyrwanym językiem, tak abyś nic nie wygadał w następnym świecie...";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "WantToGo_stop_stay";
				}
				else
				{
					Link.l1.go = "WantToGo_stop_fight";	
				}
				Link.l2 = "Dobrze. Możesz iść... Ale niech Bóg ci zabroni spotkać mnie na otwartym morzu. Przysięgam, pożałujesz momentu, kiedy zdecydowałeś się nie zostać przy moim boku.";
				Link.l2.go = "exit_fire_5";
			}
			else
			{
				dialog.text = LinkRandPhrase("Nie próbuj nawet mnie zastraszyć! Pracuję za pieniądze, ale nadal mam prawo wybierać pracę, która mi się podoba!","Jestem wolnym człowiekiem! I mam prawo do podjęcia nowej pracy kiedy tylko zechcę!","Nie jestem twoim niewolnikiem! I nie zamierzam dalej prowadzić nędznego życia na twoim starym wiadrze!");
				Link.l1 = "Cóż, tak naprawdę, mylisz się... Kiedy piłeś w karczmie, mogłeś wybrać, jakąkolwiek pracę chciałeś... Ale jak tylko stanąłeś na pokładzie mojego statku, jedyną drogą powrotną stała się kula armatnia, która rozwala ci kark... I z wyrwanym językiem, żebyś nic nie wygadał w następnym świecie...";
				// belamour legendary edition можно запугать офицера -->
				//if (makeint(Pchar.Rank) > makeint(NPchar.Rank) || CheckCharacterPerk(pchar, "IronWill"))
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "WantToGo_stop_stay";
				}
				else
				{
					Link.l1.go = "WantToGo_stop_fight";	
				}
				Link.l2 = "Dobrze. Możesz iść ... Ale niech Bóg zabrania ci spotkać mnie na otwartym morzu. Przysięgam, pożałujesz momentu, w którym zdecydowałeś się nie zostać u mojego boku.";
				Link.l2.go = "exit_fire_5";
			}
		break;
		
		case "WantToGo_stop_stay":
			dialog.text = RandPhraseSimple("Jeśli to tak przedstawiasz, zostanę, po prostu nie mam innego wyboru. Ale pamiętaj, że robię to nie z własnej woli...","Dobrze, jeśli tak to przedstawiasz, zostanę. Ale wiedz, że robiąc to, działam wbrew własnej woli.");
			Link.l1 = RandPhraseSimple("To w porządku... Służ, dopóki nie zdecyduję, kiedy cię puścić.","To dobrze. Kontynuuj obsługę... Zdecyduję, kiedy cię puścić.");
			Link.l1.go = "WantToGo_Munity"; //этот линк ведет к бегству
		break;
		
		case "WantToGo_stop_fight":
			dialog.text = NPCharRepPhrase(NPChar,"Nigdy nie zmusisz mnie do przemyślenia! Nie masz prawa trzymać mnie jako niewolnika! Zamierzam odejść, trzymaj się z daleka, albo skończysz.","Myślisz, że mógłbyś przerazić weterana oficera?! Niejednokrotnie byłem o włos od śmierci. A jeśli na to spojrzeć, to o wiele lepiej umrzeć w uczciwej bitwie, niż podczas krwawego plądrowania!");
			Link.l1 = NPCharRepPhrase(NPChar,"Cóż... każdy wybiera swój własny los. Mam nadzieję, że pomodliłeś się, zanim przyszedłeś do mnie.","Gdybym wiedział, co się stanie, kiedy podniosłem cię z karczmy, pozwoliłbym ci zamienić się na szubienicę. I teraz nie jest za późno na to ...");
			Link.l1.go = "WantToGo_stop_fight_1";
			Link.l2 = NPCharRepPhrase(NPChar,"Cóż, możesz odejść, jeśli tak bardzo potrzebujesz swojej wolności. Ale nie zamierzam ci dawać żadnych rekomendacji.","Dobrze. Możesz iść... Ale broń ci Bóg spotkać mnie na otwartym morzu. Przysięgam, pożałujesz momentu, w którym zdecydowałeś, że nie zostaniesz u mojego boku.");
			Link.l2.go = "exit_fire_5";	
		break;
		
		case "WantToGo_stop_fight_1":
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			dialog.text = NPCharRepPhrase(NPChar,"Przestań mnie już zastraszać! Który z twoich pechowców ośmieli się przeciwstawić mi? Gdybym był kapitanem, już by teraz tarzali się w pieniądzach! A po tym jak angażowałeś się we wszystkie te charytatywne akcje, boisz się, że twoja załoga stanie po mojej stronie?!","Zanieś swoje obyczaje, nie przestraszysz mnie! Do widzenia.");
			Link.l1 = NPCharRepPhrase(NPChar,"Nie, kumplu, nie dożyjesz wystarczająco długo, aby dotrzeć na szubienicę. Takie luksusy nie są dla ciebie...","Nie tak szybko kumplu, jeszcze nie jesteśmy kwita, jesteś mi coś winien.");
			Link.l1.go = "Get_out_fight";
		break;	
		///////////////////////////////////////////////////////////////////////////////////
		case "WantToGo_Munity":	//zagolski. отыгрыш бегство офицера
			Diag.TempNode = "Hired";
			// belamour legendary edition в ближайшее время не подойдет от страха
			/* if(CheckCharacterPerk(pchar, "IronWill"))
			{
				Npchar.loyality = makeint(Npchar.loyality) + 3 + hrand(sti(GetSummonSkillFromNameToOld(pchar,SKILL_FORTUNE)+GetSummonSkillFromNameToOld(pchar,SKILL_LEADERSHIP)));
				log_info(GetFullName(Npchar)+" increased his loyalty");
				log_testinfo("Loyalty has become: " + Npchar.loyality + " of " + MAX_LOYALITY);
			}
			else
			{ */
				if (!CheckAttribute(pchar, "questTemp.MutinyOfficerIDX"))
				{
					pchar.questTemp.MutinyOfficerIDX = npchar.index;
					npchar.quest.Mutiny = true; // mitrokosta доп защита от багов
					SetFunctionTimerCondition("mOfficer_fc", 0, 0, 1, false);
				}
			//}
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.location = "none";
			LAi_SetOfficerType(NPChar);
			DialogExit();
		break;
		////////////////////////////////////////////////////////////////////
		// пассажир возмущен игроком и сваливает <--
		
		case "Node_2":
			dialog.text = NPCharRepPhrase(Npchar,RandSwear()+"Jestem najlepszy "+XI_ConvertString(Npchar.quest.officertype)+" w tych wodach. "+Npchar.quest.officertype_2+"I jestem gotów zrobić ci przysługę i służyć pod twoim dowództwem.","No, mówią, że nie jestem zły "+XI_ConvertString(Npchar.quest.officertype)+". "+Npchar.quest.officertype_2+"Możesz mnie zabrać na swój statek, kapitanie, i samemu się przekonać.");
			Link.l1 = "I ile chcesz?";
			Link.l1.go = "price";
			Link.l2 = "A jakim specjalistą jesteś?";
			Link.l2.go = "ShowParam_exit";
			Link.l3 = "Niestety, już mam "+XI_ConvertString(Npchar.quest.officertype)+".";
			Link.l3.go = "Exit";
		break;

		case "OnceAgain":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = RandPhraseSimple("Heh, kapitanie, połowa garnizonu jest teraz za tobą. Z pewnością to nie jest najlepszy czas, aby zatrudnić się w twojej załodze!","I walka nasza droga do statku? Nie, kapitanie, innym razem...");
				link.l1 = RandPhraseSimple("Jak sobie życzysz...","Właściwie, nie miałem zamiaru cię zatrudniać."); 
				link.l1.go = "exit";
				break;
			}
			Diag.TempNode = "OnceAgain";
			dialog.text = "Czy zmieniłeś zdanie, kapitanie? Zdecydowałeś, że nowa "+XI_ConvertString(Npchar.quest.officertype)+" nie zaszkodziłoby?";
			// boal -->
			if (FindFreeRandomOfficer() > 0)
			{
                Link.l1 = "Coś w tym rodzaju. Ile chcesz?";
                Link.l1.go = "price";
			}
			Link.l2 = "I co jesteś w stanie zrobić?";
			Link.l2.go = "ShowParam_exit";
			// boal <--
			Link.l3 = "Mam pełny zestaw. Do zobaczenia.";
			Link.l3.go = "exit";
		break;

		case "price":
			dialog.text = "Myślę, że możemy się zgodzić na "+Npchar.quest.OfficerPrice+" pesos.";
			if(Npchar.rank >= 15)
			{
				dialog.text = "Myślę, że możemy się zgodzić na "+(makeint(Npchar.quest.OfficerPrice)/ 100+30)+" dublony.";
			}	
			Link.l1 = "Czy to nie jest trochę za dużo?";
			Link.l1.go = "trade";
			Link.l2 = "Zgadzam się. Uważaj się za część załogi.";
			Link.l2.go = "hire";
			Link.l3 = "Nie jesteś wart tych pieniędzy.";
			Link.l3.go = "exit";
		break;

		case "trade":
			if (GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE) >= Rand(12) && (sti(Npchar.quest.OfficerPrice) - GetCharacterSkillToOld(Pchar, "commerce")*100) >= sti(Npchar.quest.OfficerLowPrice))// bug fix
			{
				Npchar.quest.OfficerPrice = makeint(makeint(Npchar.quest.OfficerPrice) - GetCharacterSkillToOld(Pchar, "commerce")*100); // пусть будет коммерция перса голой
				dialog.text = "Dobrze... Myślę, że mogę się nawet zgodzić na "+Npchar.quest.OfficerPrice+" pesos. Co ty na to?";
				if(Npchar.rank >= 15)
				{
					dialog.text = "Zgaduję, że mogę nawet się zgodzić na "+(makeint(Npchar.quest.OfficerPrice)/ 100+30)+" doubloony. Co ty na to?";
				}
				Link.l1 = "Teraz jest lepiej. Jesteś w środku.";
				Link.l1.go = "hire";				
				Link.l2 = "Wciąż myślę, że to trochę za dużo. Do widzenia.";
				Link.l2.go = "exit";
			}
			else
			{
				dialog.text = "Przykro mi, kapitanie, ale jestem wart dokładnie tyle, ile poprosiłem. Jeśli to dla ciebie za dużo, to znajdź kogoś innego.";
				Link.l1 = "Dobrze, zgadzam się. Zabiorę cię.";
				Link.l1.go = "hire";				
				Link.l2 = "To właśnie zamierzam zrobić. Do widzenia.";
				Link.l2.go = "exit";
			}
		break;

		case "hire":
			dialog.text = "Widzę, że brakuje ci gotówki, kapitanie! Przykro mi, ale nie pracuję na kredyt.";
			Link.l1 = "O, diabli!";
			Link.l1.go = "Exit";
			if(Npchar.rank < 15 && makeint(Pchar.money) >= makeint(Npchar.quest.OfficerPrice))
			{
				AddMoneyToCharacter(Pchar, -(makeint(Npchar.quest.OfficerPrice)));
				Diag.TempNode = "OnboardSoon";
				dialog.text = "Dziękuję, kapitanie. Nie pożałujesz swojego wyboru.";
				Link.l1 = "Mam nadzieję.";
				Link.l1.go = "Exit_hire";								
			}
			if(Npchar.rank >= 15 && PCharDublonsTotal() >= makeint((makeint(Npchar.quest.OfficerPrice) / 100 + 30)))
			{
				RemoveDublonsFromPCharTotal(makeint((makeint(Npchar.quest.OfficerPrice) / 100 + 30)));
				Diag.TempNode = "OnboardSoon";
				dialog.text = "Dziękuję Ci, kapitanie. Nie pożałujesz swojego wyboru.";
				Link.l1 = "Mam nadzieję.";
				Link.l1.go = "Exit_hire";								
			}
		break;

		case "OnboardSoon":			
			Diag.TempNode = "OnboardSoon";
			dialog.text = "Skończę tylko swój drink, kapitanie, a potem pójdę do statku. Nie martw się, będę tam na czas.";
			Link.l1 = "Dobrze. Jeśli spóźnisz się, każę ci szorować pokład!";
			Link.l1.go = "Exit";											
		break;
        
		case "QMASTER_1":
			if(sti(PChar.Ship.Type) == SHIP_NOTUSED)
			{
				dialog.text = "Kapitanie, ale nie masz statku!";
				Link.l1 = "Dziękuję za przypomnienie mi...";
				Link.l1.go = "Exit";
				Diag.TempNode = "Hired";
				break;
			}
			// Rebbebion, добавил фикс отображения знака процента
			dialog.text = "Maksymalna aktywność szczurów w podróży "+FloatToString(50.0 /(2.0+GetSummonSkillFromNameToOld(PChar,SKILL_REPAIR)+GetSummonSkillFromNameToOld(PChar,SKILL_SNEAK)),1)+"%% całkowitej ilości ładunku. Za "+GetCrewQuantity(PChar)+" żeglarzy nam będzie potrzeba "+makeint((GetCrewQuantity(PChar)+6)/ 10)+" jedzenie na dzień. To bez uwzględniania transportowanych niewolników.";
			Link.l1 = "Dzięki.";
			Link.l1.go = "Exit";
			Diag.TempNode = "Hired";
		break;
        
        // boal 05.09.03 offecer need to go to abordage -->
        case "stay_follow":
            dialog.text = "Jakie są twoje rozkazy?";
            Link.l1 = "Stój tutaj!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Podążaj za mną i nie zostawaj w tyle!";
            Link.l2.go = "Boal_Follow";
            // boal 05.09.03 offecer need to go to abordage <--
			if (npchar.id == "OffMushketer")
			{
				Link.l3 = "Chcę, abyś utrzymywał pewną odległość od celu.";
				Link.l3.go = "TargetDistance";
			}
			
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l4 = "Musimy zmienić rodzaj amunicji do twojej broni palnej.";
					Link.l4.go = "SetGunBullets";
				}	
			}
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l5 = "Musimy zmienić typ amunicji do twojego muszkietu.";
					Link.l5.go = "SetMusketBullets";
				}
					Link.l6 = "Musimy zmienić twoją broń priorytetową do walki.";
					Link.l6.go = "SetPriorityMode";
			}
		break;

		case "SetGunBullets":
			Dialog.Text = "Wybierz rodzaj amunicji:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			Diag.CurrentNode = Diag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;
		
		case "SetMusketBullets":
			Dialog.Text = "Wybierz rodzaj amunicji:";
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetMusketBullets1_" + i;
			}
		break;	

		case "SetMusketBullets2":
			i = sti(NPChar.SetMusketBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, MUSKET_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, MUSKET_ITEM_TYPE);
			Diag.CurrentNode = Diag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetMusketBullets");
			DialogExit();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "Na początku walki użyjesz:";
			Link.l1 = "Szabla";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Muszkiet";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
            SetPriorityMode(NPChar, 1);
			DialogExit();
		break;
		
		case "MusketPriorityMode":
			SetPriorityMode(NPChar, 2);
			DialogExit();
		break;
		
		case "TargetDistance":
			dialog.text = "Jaką dokładnie odległość, kapitanie? Wskazać w krokach, ale nie więcej niż 20.";
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";			
		break;
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "Kapitanie, czy wszystko w porządku?";
				link.l1 = "Przepraszam, moja wina...";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Będę stał w miejscu bez ruchu. Czy to jest to, czego ode mnie chcesz, kapitanie?";
				link.l1 = "Tak. To jest dokładnie to, czego od ciebie potrzebujemy.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "Myslę, że mówiłem ci, że nie mogę stanąć dalej niż 20 kroków od celu.";
				link.l1 = "Dobrze, zachowaj odległość 20 metrów.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "Zrozumiane i wzięte pod uwagę.";
			link.l1 = "Dobrze.";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;

		case "AsYouWish":
			// проверка на море -->
			if (bSeaActive)
			{
				attr = Sea_FindNearColony();
				if (attr == "none")
				{
					dialog.text = "Kapitanie, chociaż naprawdę nie rozumiem twojego rozumowania, czy moglibyśmy porozmawiać o tym na brzegu? Czy zdecydowałeś się po prostu wyrzucić mnie za burtę?";
					Link.l1 = "Hmm... Nie, to nie o to chodziło. Zostań tutaj, dopóki nie dotrzemy do portu.";
					Link.l1.go = "Exit";	
					break;	
				}
			}
			// проверка на море <--
			if (makeint(PChar.reputation.nobility) >= 41 && makeint(NPChar.reputation) < 41) //герой против злодея
			{
				dialog.text = RandPhraseSimple(LinkRandPhrase("Teraz to jest nowe!","Dlaczego, na miłość Boską?","Z jakiego powodu?!"),RandPhraseSimple("Kapitanie, czy jesteś szalony? Opowiadanie takich wiadomości bez powodu!","O rety! A co ja zrobiłem, żeby ci się narazić?"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("Zdecydowałem się wprowadzić porządek w załodze. I nie podobają mi się twoje relacje z kolegami","Twoje korzyści nie były tak dobre, jak omawiano podczas zatrudnienia. Więc,","Zbirów i łotrów w moim zespole nie będzie! Więc,"),LinkRandPhrase("Dowiedziałem się, że kradniesz rum, potajemnie przyzwyczajając moją załogę do mocnego picia i tym samym obniżając jej morale. Dlatego,","Mam dość twoich bandyckich manier i nie zamierzam tego tolerować. Więc,","Ciągle spędzasz swój czas w centralnej kajucie na grę w karty czy kości, odciągając od obowiązków innych oficerów. To nie może trwać w nieskończoność. Więc,"))+" spakuj swoje rzeczy i opuść statek.";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "Get_out_A1_peace";
				}
				else
				{
					Link.l1.go = "Get_out_A1_strife";
				}
				break;	
			}
			if (makeint(PChar.reputation.nobility) >= 41 && makeint(NPChar.reputation) >= 41) // герой против героя
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple("Czy mogę znać powód takiej decyzji?","Oczywiście, taka decyzja jest dobrze uzasadniona?"),RandPhraseSimple("Wyjaśnij się, kapitanie","To całkiem niespodziewane. Ale wciąż chciałbym znać powód."));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("Jestem całkowicie niezadowolony z Twojego podejścia do obowiązków.","Niestety, nie sprawdziłeś się jako dobry oficer i prawdopodobnie nigdy nie będziesz...","Jesteś dobrym oficerem i twoja służba była sprawiedliwa, ale teraz nasze drogi się rozeszły. Nie pytaj mnie dlaczego."),LinkRandPhrase("Ostrzegałem cię, że ta pasja do rumu cię zniszczy. Jak mogę zaufać człowiekowi w walce, który nawet nie jest w stanie włóż swojego miecza do pochwy?","Jesteś okropnym żeglarzem i oficerem... Myślę, że więcej będziesz na lądzie niż na morzu.","Nie jestem zadowolony z twoich kwalifikacji, ale w końcu znalazłem godnego zastępcę."));
				Link.l1.go = "Get_out_A2";
				break;	
			}
			if (makeint(PChar.reputation.nobility) < 41 && makeint(NPChar.reputation) >= 41) // злодей против героя 
			{		
				dialog.text = RandPhraseSimple(RandPhraseSimple("Hmm... Czy mogę znać powód?","To poważne stwierdzenie. Czy mogę wiedzieć, z czym konkretnie jesteś niezadowolony?"),RandPhraseSimple("Wyjaśnij się, kapitanie.","Oczywiście, takie oświadczenie jest dobrze uzasadnione?"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("Jestem całkowicie niezadowolony z twoich kwalifikacji, dlatego","Niestety, nie okazałeś się porządnym oficerem. Więc,","Mam dość twoich szlachetnych manier. Nie zamierzam ich tolerować w nieskończoność, więc"),LinkRandPhrase("Doszło do mojej wiadomości, że podburzasz załogę do nieposłuszeństwa. Nie będzie żadnych zakłóceń na moim statku! I nie dziękuj mi, że cię wcześniej nie wyrzuciłem. Więc","Twoje szlachetne zasady cię honorują, ale są sprzeczne z rabunkowym życiem wolnego korsarza. Więc","Nie podoba mi się twój stosunek do obowiązków. Więc"))+" spakuj swoje rzeczy i opuść statek.";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "Get_out_A3_peace";
				}
				else
				{
					Link.l1.go = "Get_out_A3_strife";
				}	
				break;
	
			}
			if (makeint(PChar.reputation.nobility) < 41 && makeint(NPChar.reputation) < 41) // злодей против злодея
			{	
				dialog.text = RandPhraseSimple(LinkRandPhrase("Kapitanie, naprawdę tego nie spodziewałem! Może byś wyjaśnił, co się dzieje?","Kapitanie, co cię gryzie?!","Co masz na myśli, kapitanie?!"),RandPhraseSimple("Co do diabła, kapitanie?! Wszystko wydawało się w porządku wczoraj, a teraz jesteśmy tutaj, co się stało?","Wow! Może byś się wytłumaczył?"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("Jesteś totalnym leniwcem i bezużytecznym idiotą, nawet chłopiec na statku robiłby to lepiej. Zbyt długo cierpiałem z powodu ciebie. Więc","Od jakiegoś czasu myślałem, żeby cię zwolnić, a teraz w końcu znalazłem godnego zastępstwa. Więc","Dowiedziałem się, że kradniesz rum, potajemnie przyzwyczajając moją załogę do mocnego picia i tym samym obniżając jej morale. Dlatego"),LinkRandPhrase("Gdy cię zatrudniałem, chwaliłeś się, że jesteś najlepszym oficerem we całej flocie, ale okazało się, że jesteś tylko leniuchem, więc","Ostrzegałem cię, że twój nawyk picia źle się skończy. Dlaczego miałbym trzymać bezużytecznego pijaka na moim statku? Więc","Zamiast obsługiwać, ciągle gdzieś błąkasz się albo grasz w karty czy w kości. Mam nadzieję, że nie myślałeś, że to może trwać wiecznie? Więc"))+" spakuj swoje rzeczy i opuść statek.";
				Link.l1.go = "Get_out_A4";
				break;
			}
		break;
	
		case "Get_out_A1_peace":
			dialog.text = RandPhraseSimple(LinkRandPhrase("No więc jak teraz mówisz! Dobrze, jak sobie życzysz. Ale bądź pewien: nie wrócę do ciebie, nawet jeśli umieram z głodu!","Szczerze mówiąc, też nie przepadam za twoimi szlacheckimi gierkami. Więc do widzenia...","Och, idź do diabła! Zostań ze swoimi lizusami. 'Bohater', rzeczywiście!"),LinkRandPhrase("Właściwie, nigdy mi nie podobało się służyć ci... Masz tam barkę towarową, a nie przyzwoity okręt. Raczej szkoła wykończeniowa...","Wiesz, mam dość twojej załogi, wszystko niby elegancki, tylko małe dzieci, ani jednego prawdziwego mężczyzny...","Dobrze, kapitanie, jak mówisz. Ale Bóg wie, że dobrze wykonywałem swoją pracę..."));
			Link.l1 = "Poczekaj. W tej chwili nie mogę opuścić statku bez oficera. Ale wrócimy do tej rozmowy później.";
			Link.l1.go = "exit_bad";
			Link.l2 = "W takim razie idź w pokoju.";
			Link.l2.go = "Exit_Fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "Nie denerwuj się. Przygotowałem dla ciebie odprawę - "+sti(NPChar.rank)*500+" pesos. Mam nadzieję, że to rozwieje wszelkie wątpliwości.";
				Link.l3.go = "Get_out_А1_ForMoney";
			}
		break;

		case "Get_out_A1_strife":
			dialog.text = LinkRandPhrase("Przepraszam! Co masz na myśli mówiąc 'opuść statek'?! Nie wystawiłem swojej głowy pod grad kul, abyś mógł mnie wyrzucić kiedy tylko chcesz!","Ha! 'Opuść statek'! Naprawdę myślisz, że pozwolę ci wyrzucić mnie jak kociaka?!","Spokojnie, kapitanie, poważni ludzie nie załatwiają spraw w ten sposób. Nie pozwolę się traktować jak zielony.");
			Link.l1 = "Dobrze, możesz zostać na razie - ale tylko do momentu, gdy znajdę godnego zastępstwa.";
			Link.l1.go = "exit_bad";
			Link.l2 = "Powtarzam, twoja służba się skończyła. Możesz spakować swoje rzeczy.";
			Link.l2.go = "Get_out_A1_strife_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "Nie denerwuj się. Przygotowałem "+sti(NPChar.rank)*500+" pesos dla ciebie. Mam nadzieję, że to rozwieje wszelkie wątpliwości.";
				Link.l3.go = "Get_out_А1_ForMoney";
			}
		break;

		case "Get_out_A1_strife_1":
			dialog.text = RandPhraseSimple("Właściwie, nie palę się z chęcią zostania tutaj. Ale równie dobrze nie odejdę bez rekompensaty!","Teraz, na pewno nie zostanę na tym twoim starym wiadrze, ale najpierw mi zrekompensujesz!")+" "+sti(NPChar.rank)*1000+" pesos, a my o sobie zapomnimy.";
			Link.l1 = "Trochę się zdenerwowałem... Proszę, przyjmij moje przeprosiny i wróć do swoich obowiązków.";
			Link.l1.go = "exit_bad1";
			Link.l2 = "O jakich pieniądzach mówisz, skoro zawsze dostawałeś swoją uczciwą część? To wygląda na wymuszenie dla mnie!";
			Link.l2.go = "Get_out_А1_strife_battle";
			if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
			{
				Link.l3 = "Dobrze. Zwróć sprzęt, a potem dostaniesz to, o co prosiłeś.";
				Link.l3.go = "Get_out_А1_chang";
			}
		break;

		case "Get_out_А1_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			dialog.text = "Teraz to już inna historia. Żegnaj!";
			Link.l1 = "Mam nadzieję, że nasze ścieżki nigdy się więcej nie skrzyżują.";
			Link.l1.go = "Exit_Fire_1";
		break;

		case "Get_out_А1_strife_battle":
			dialog.text = LinkRandPhrase("Uważaj to za rekompensatę za szkody moralne. Nie będę tolerować takiego traktowania, a ten, kto odważy się tak ze mną postępować, będzie żałował!","To nie jest wymuszenie, ale raczej rekompensata za tę głupią stratę mojego czasu! I dostanę to, niezależnie od kosztów!","Zmarnowałem zbyt wiele czasu służąc pod takim miękiszonem jak ty. Mogłem zrobić fortunę plądrując statki kupieckie. Więc chcę tylko zrekompensować moje stracone zyski.");
			if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
			{
				Link.l1 = "Dobrze. Oto twoje pieniądze... A teraz znikaj!";
				Link.l1.go = "Get_out_А1_ForMoney_angry";
			}
			Link.l2 = "Wygląda na to, że zapominasz kim jesteś! Nie pozwolę takim półgłówkom jak ty krzyczeć na mnie!";
			Link.l2.go = "Get_out_А1_strife_death";
		break;

		case "Get_out_А1_strife_death":
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			OfficersReaction("good");
			dialog.text = "Proszę bardzo, kapitanie! Pokaż się!";
			Link.l1 = "Bóg wie, nie chciałem tego!";
			Link.l1.go = "Get_out_fight";
		break;
	
		case "Get_out_А1_ForMoney_angry":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			OfficersReaction("bad");
			dialog.text = "To już inna historia. Żegnaj!";
			Link.l1 = "Mam nadzieję, że nasze ścieżki nigdy się nie skrzyżują.";
			Link.l1.go = "Exit_Fire_1";
		break;

		case "Get_out_A2":
			dialog.text = RandPhraseSimple(LinkRandPhrase("No cóż, to jest postanowione. Do widzenia, kapitanie, i nie żywić urazy...","Szkoda, kapitanie. Ale Bóg wie, że próbowałem. Do widzenia.","Cóż, kapitanie, na pewno ciężko cię zadowolić! Dobrze, powodzenia."),LinkRandPhrase("Szkoda, kapitanie. Wiesz, lubiłem dla ciebie pracować.","Tak, rzeczy się zdarzają... Ale nie żywię urazy. Do widzenia.","Jesteś niesprawiedliwy wobec mnie, kapitanie. Mimo to, szanuję twoją decyzję. Do widzenia."));
			Link.l1 = "Poczekaj, zmieniłem zdanie. Wróćmy do tej rozmowy później.";
			Link.l1.go = "exit_good";
			Link.l2 = "Nie bądź zdenerwowany. Powodzenia dla ciebie...";
			Link.l2.go = "exit_fire_2";
			Link.l3 = "Poczekaj... Wyposażyłem cię dobrze. Oddaj to, nie zamierzam wyposażać hordy...";
			Link.l3.go = "Return_items_A2";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l4 = "Zaczekaj... Nie chcę, żebyś odszedł z pustymi rękami. Weź to "+sti(NPChar.rank)*500+" pesos. Przyda się, gdy będziesz szukać nowej pracy.";
			}
			Link.l4.go = "Im_kind_A2";
		break;

		case "Return_items_A2":
			ChangeOfficersLoyality("bad_all", 1);
			dialog.text = "O, pewnie, weź to wszystko z powrotem...";
			Link.l1 = "Wiem, że mnie dobrze rozumiesz...";
			Link.l1.go = "Get_out_А2_chang";
		break;

		case "Im_kind_A2":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeOfficersLoyality("good_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			dialog.text = "Dziękuję Ci, kapitanie! Naprawdę niespodziewana hojność... Wiesz, nadal mam trochę twoich rzeczy, może chciałbyś je odzyskać?";
			Link.l1 = "Być może... znalezienie dobrego ostrza nie jest takie łatwe w dzisiejszych czasach...";
			Link.l1.go = "Get_out_А2_chang";
			Link.l2 = "Oh, nie martw się. Zachowaj je jako pamiątkę po swojej służbie.";
			Link.l2.go = "exit_fire_2";
		break;

		case "Get_out_A3_peace":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Dobrze, jak sobie życzysz. Ale bądź pewien: nie wrócę do ciebie, nawet jeśli umieram z głodu!!","Kapitanie, twoje bandyckie metody prowadzenia biznesu również mnie mdli. Prędzej czy później, to musiało się stać. I nie ma potrzeby wymyślać żadnych powodów.","Pozostań ze swoimi bandytami, wtedy. Porządny człowiek nawet by nie pokazał swojej twarzy w mesie twojego statku. Co za burdel tutaj masz, Boże mi wybacz!"),LinkRandPhrase("Szczerze mówiąc, moja służba pod twoim dowództwem też mi się nie podobała. Zatrudniłeś całą załogę łotrów, ani jednego porządnego człowieka, z którym można by pogadać.","Tak, jeśli będziesz utrzymywać takie nastawienie do swojej załogi, wkrótce będziesz całkiem sam i nie będzie potrzeby wymyślać żadnych powodów.","Nasza wrogość jest wzajemna, i to mnie pociesza. Do widzenia."));
			Link.l1 = "Zaczekaj. Teraz to nie jest najlepszy czas na twoją emeryturę. Ale wszystkie roszczenia są aktualne.";
			Link.l1.go = "exit_bad";
			Link.l2 = "Idź, idź. Poradzę sobie bez twoich wykładów.";
			Link.l2.go = "exit_fire_3";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "Poczekaj. Dam ci "+sti(NPChar.rank)*500+" pesos. Nie chcę, żebyś umarł w rynsztoku, abym czuł się przez to winny.";
				Link.l3.go = "Get_out_А3_ForMoney";
			}
		break;

		case "Get_out_А3_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			ChangeOfficersLoyality("good_all", 1);
			dialog.text = LinkRandPhrase("Cóż, dziękuję. Do widzenia...","Dziękuję za zrozumienie. Powodzenia.","Teraz skończyliśmy. Powodzenia...");
			Link.l1 = "Wiem, że mnie dobrze rozumiesz.";
			Link.l1.go = "exit_fire_3";
		break;
	
		case "Get_out_A3_strife":
			dialog.text = LinkRandPhrase("Ale kapitanie, w takim razie zostaję na mieliźnie. Czy naprawdę chcesz mnie wysłać prosto z pokładu na plac kościelny?","Jesteś niesprawiedliwy wobec mnie kapitanie. Ale nie będę żywił urazy, jeśli otrzymam godziwe wynagrodzenie.","I to jest twoja wdzięczność za wszystkie moje rany bojowe? Cóż, chyba nie mogę obyć się bez pieniężnego wynagrodzenia.");
			Link.l1 = "Dobrze, zmieniłem zdanie. Możesz zostać, ale wrócimy do tej rozmowy.";
			Link.l1.go = "exit_bad";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "O, nie martw się o to. Oto - "+sti(NPChar.rank)*500+" pesos. To wynagrodzi twój czas na moim statku.";
				Link.l2.go = "Get_out_А3_ForMoney";
				Link.l3 = "Dam ci pieniądze. Mimo to, dzięki mnie jesteś ładnie wyposażony, więc chyba odpowiednie byłoby zwrócić mi te rzeczy.";
				Link.l3.go = "Return_items_A3";
			}
			Link.l4 = "Ach, naprawdę? A co z twoją częścią, którą regularnie otrzymywałeś?! Wiedziałem, że wszystko skończy się narzekaniem i żądaniem premii.";
			Link.l4.go = "Get_out_A3_strife_1";
		break;

		case "Return_items_A3":
			dialog.text = "Wiedziałem, że to powiesz, ale odzyskasz swój sprzęt tylko po tym, jak otrzymam "+sti(NPChar.rank)*1000+" pesos. W przeciwnym razie możesz go mieć tylko nad moim martwym ciałem!";
			Link.l1 = "W porządku, weź swoje pieniądze, no.";
			Link.l1.go = "Get_out_А3_chang";
			Link.l2 = "Czy jesteś szalony, czy co?! Wymagasz takiej sumy za to, co dano ci za darmo?! Teraz widzę, że twoja chciwość wyraźnie przeważyła nad udawanym dobrodziejstwem.";
			Link.l2.go = "Get_out_A3_strife_1";
		break;

		case "Get_out_A3_strife_1":
			dialog.text = "Nie ośmielaj się mnie obrażać! Mogę nie być najlepszy w marynarce, ale nadal jestem oficerem bojowym. I będę szanowany, nawet przez takiego chamstwa jak ty!";
			Link.l1 = "Jeśli jeszcze tego nie zrozumiałeś, powtórzę to jeszcze raz: przestań błagać, nic od mnie nie dostaniesz.";
			Link.l1.go = "Get_out_А3_strife_death";
		break;

		case "Get_out_А3_strife_death":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			OfficersReaction("bad");
			dialog.text = "Cóż, i tak dostanę satysfakcję!";
			Link.l1 = "O, więc to wyzwanie, prawda? Jak sobie życzysz...";
			Link.l1.go = "Get_out_fight";
		break;

		case "Get_out_A4":
			dialog.text = RandPhraseSimple(LinkRandPhrase("To moje szczęście! Włożyłem serce i duszę w służbę, tylko po to, aby zostać wykopanym bez nawet świadczenia za służbę!","Co za nieszczęście?! Zatrudniają mnie, a potem prawie natychmiast wykopują. Nie mam pojęcia, do którego świętego zapalić świecę w tych czasach...","O kurcze! Zwolniony po raz trzeci w tym roku, wszystko w poniedziałki. Być może, nie powinienem pojawiać się w obecności kapitana, kiedy mam kaca."),LinkRandPhrase("Cóż, jak sobie życzysz. Módl się, żebyśmy nigdy więcej się nie spotkali.","Jak sobie życzysz. Pamiętaj jednak, że nigdy nie znajdziesz lepszego oficera.","Dobrze, kapitanie, jak mówisz. Ale Bóg wie, że dobrze wykonywałem swoją pracę..."));
			Link.l1 = "Zaczekaj. Teraz to nie jest najlepszy czas na twoją emeryturę. Ale wszystkie roszczenia są aktualne.";
			Link.l1.go = "exit_good";
			Link.l2 = RandPhraseSimple("Znikaj teraz. I dziękuj Bogu, że jestem dziś w dobrym humorze.","Zgub się teraz. Jesteś tak dobrym oficerem, jak gówno jest dobre do robienia kul.");
			Link.l2.go = "exit_fire_4";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "Poczekaj. Dam ci "+sti(NPChar.rank)*500+" pesos. Nie chcę, abyś umarł w rynsztoku, a ja czułbym się przez to winny.";
				Link.l3.go = "Get_out_А4_ForMoney";
			}
			Link.l4 = "Zaczekaj... Ubrałem cię ładnie, oddaj mi moje rzeczy.";
			Link.l4.go = "Return_items_A4";
		break;

		case "Get_out_А4_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			ChangeOfficersLoyality("good_all", 1);
			dialog.text = LinkRandPhrase("O, dzięki, kapitanie! To naprawdę miłe z twojej strony...","Dziękuję za zrozumienie. Powodzenia.","Teraz skończymy. Powodzenia...");
			Link.l1 = "Powodzenia. Mam nadzieję, że nie zmarnujesz tego wszystkiego w pierwszej karczmie.";
			Link.l1.go = "exit_fire_4";
		break;

		case "Return_items_A4":
			if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
			{
				dialog.text = LinkRandPhrase("A teraz zabierasz mi sprzęt! Och, do diabła z tym! Pójdę na ryby, przysięgam...","Widzę, że zdecydowałeś się mnie całkowicie oczyszczyć. Cóż, teraz jest tylko jedna droga dla mnie, na parvis...","Och, bardzo dziękuję! Teraz postanowiłeś mnie okraść. Och, jakie okrutne losy... Weź to więc, weź! Co ja mogę zrobić tak czy inaczej...");
				Link.l1 = "Znikaj teraz. Jesteś tak dobrym oficerem, jak gówno jest dobre do robienia kul.";
				Link.l1.go = "Get_out_А4_chang_1";
			}
			else	
			{
				dialog.text = RandPhraseSimple("Jak sobie życzysz, kapitanie, ale najpierw bądź tak uprzejmy i podaj mi "+sti(NPChar.rank)*1000+" pesos. Niech to będzie rekompensatą za moralne szkody.","W porządku. Ale nadal chcę otrzymać "+sti(NPChar.rank)*1000+" pesos jako rekompensata za moją ciężką i wierną służbę.");
				if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
				{
					Link.l1 = "Co za łotr! Dobrze, oto twoje pieniądze.";
					Link.l1.go = "Get_out_А4_chang";
				}
				Link.l2 = "Czy ty zwariowałeś?! Jak śmiesz prosić o takie pieniądze za to, co ci sam dałem!";
				Link.l2.go = "Get_out_A4_strife";
				Link.l3 = "Ha-ha! Żartowałem! Jak mogę wyrzucić starego przyjaciela, jak dziurawy kapelusz!";
				Link.l3.go = "exit_bad1";
			}
		break;

		case "Get_out_A4_strife":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			ChangeOfficersLoyality("bad_all", 1);
			dialog.text = "No cóż, w takim razie nic nie dostaniesz! Nie zrobię kroku, dopóki nie usłyszę brzęku moich pieniędzy!";
			Link.l1 = RandPhraseSimple("Wkrótce usłyszysz dzwonienie mojego miecza!","Wtedy wyniosą cię stąd nogami do przodu!");
			Link.l1.go = "Get_out_fight";
		break;

		case "Get_out_fight":
			CheckForReleaseOfficer(GetCharacterIndex(Npchar.id));
			RemovePassenger(Pchar, Npchar);
			LAi_CharacterDisableDialog(NPChar);
			LAi_SetWarriorType(Npchar);
			LAi_group_MoveCharacter(Npchar, "TmpEnemy");
			LAi_group_SetHearRadius("TmpEnemy", 100.0);
			LAi_group_FightGroupsEx("TmpEnemy", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
			if (PChar.location == Get_My_Cabin() || findsubstr(PChar.location, "_tavern" , 0) != -1 || findsubstr(PChar.location, "_store" , 0) != -1)
            {
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				LAi_group_SetCheck("TmpEnemy", "CannotFightCurLocation");
				LAi_group_SetCheck("TmpEnemy", "MainHeroFightModeOff");
            }
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

	    case "Get_out_А1_chang": // интерфейс обмена
			Diag.TempNode = "Fired_1";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;	
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А2_chang": // интерфейс обмена
			Diag.TempNode = "Fired_2";
			LAi_CharacterDisableDialog(NPChar);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А3_chang": // интерфейс обмена
			Diag.TempNode = "Fired_3";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А4_chang_1": // интерфейс обмена
			Diag.TempNode = "Fired_4";
			LAi_CharacterDisableDialog(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;	
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А4_chang": // интерфейс обмена
			Diag.TempNode = "Fired_4";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;	
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

	    case "exit_bad":
			Npchar.loyality = makeint(Npchar.loyality) - 3;
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_bad1":
			Npchar.loyality = makeint(Npchar.loyality) - 2;
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			Diag.CurrentNode = Diag.TempNode;			
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_good":
			Npchar.loyality = makeint(Npchar.loyality) - 1;
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_fire_1":	//navy -->			
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--		
			Diag.TempNode = "Fired_1";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_2":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");	
				DialogExit();
				break;
			}	//navy <--	
			Diag.TempNode = "Fired_2";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_3":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--	
			Diag.TempNode = "Fired_3";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_4":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");	
				DialogExit();
				break;
			}	//navy <--		
			Diag.TempNode = "Fired_4";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_5":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--	
			Diag.TempNode = "Fired_1";
			OfficersReaction("good");
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "Fired_1":
			Diag.TempNode = "Fired_1";      
			dialog.text = "Co teraz?! Już o wszystkim rozmawialiśmy! Nigdy więcej nie postawię stopy na twoim statku.";
			Link.l1 = RandPhraseSimple("Znikaj teraz. W końcu to nie duża strata.","Dobrze, idź, w takim razie. Nie będę cię zatrzymywać.");	
			Link.l1.go = "Exit";
		break;

		case "Fired_2":
			Diag.TempNode = "Fired_2"; 
			dialog.text = "Czy coś jeszcze, kapitanie? Myślałem, że już wszystko omówiliśmy...";
			Link.l1 = "Nie, nic. Chciałem tylko pożegnać się...";	 
			Link.l1.go = "Exit";
		break;

		case "Fired_3":
			Diag.TempNode = "Fired_3"; 
			dialog.text = "Kapitanie, omówiliśmy wszystko i wyraziliśmy nasze roszczenia. Nie zamierzasz chyba powiedzieć, że zmieniłeś zdanie, prawda?";
			Link.l1 = "Dobrze, idź już. W końcu to nie jest wielka strata.";	 
			Link.l1.go = "Exit";
		break;

		case "Fired_4":
			Diag.TempNode = "Fired_4"; 
			dialog.text = "Kapitanie, jakie mogą być jeszcze pytania? Chcę ci powiedzieć, jestem bardzo obrażony i nie mam ochoty wracać...";
			Link.l1 = "Dobrze, idź więc. Nie to, że tak bardzo cię potrzebowałem.";	 
			Link.l1.go = "Exit";
		break;
		
		// boal 05.09.03 offecer need to go to abordage -->
	    case "Boal_Stay":
            //SetCharacterTask_Stay(Characters[Npchar.index]); // it's a mistic but here doesn't work :(
            //Log_SetStringToLog(Npchar.id +" "+Npchar.index);
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
		    Diag.TempNode = "Hired";
		    dialog.text = "Tak jest Kapitanie!";
		    Link.l1 = "Na łatwość.";
		    Link.l1.go = "Exit";
		    Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
	    break;
		
	    case "Boal_Follow":
		    SetCharacterTask_FollowCharacter(Npchar, PChar); // it works here!!!
		    Diag.TempNode = "Hired";
		    dialog.text = "Tak jest Kapitanie!";
		    Link.l1 = "Spokojnie.";
		    Link.l1.go = "Exit";
	    break;
        // boal 05.09.03 offecer need to go to abordage <--

		//////////////////////////////    офицер-наместник -->
		case "Gover_Hire":
            dialog.Text = "Kapitanie! To byłoby zaszczytem!";
            Link.l1 = "Utrzymuj porządek i spraw, aby miasto prosperowało, a ja będę wpływać od czasu do czasu, aby pobierać cła.";
			Link.l1.go = "Exit_Gover_Hire";
            Link.l2 = "Zmieniłem zdanie.";
            Link.l2.go = "Exit";
            Diag.TempNode = "Hired";
        break;

        case "Exit_Gover_Hire":
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
            attr = sld.id + "_townhall";

            // снимем пассажира -->
			CheckForReleaseOfficer(sti(NPChar.index));
			RemovePassenger(pchar, NPChar);
			// снимем пассажира <--
		    sld.OfficerIdx = sti(NPChar.index);
			ChangeCharacterAddressGroup(NPChar, attr, "sit", "sit1");
			LAi_SetHuberTypeNoGroup(NPChar);
            SaveCurrentNpcQuestDateParam(NPChar, "StartTaxDate");
            SaveCurrentNpcQuestDateParam(NPChar, "GoverTalkDate");
            LAi_LoginInCaptureTown(NPChar, true);
			//  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
            AddQuestRecordInfo("Gen_CityCapture", "t3_1");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + sld.id));
			AddQuestUserData("Gen_CityCapture", "sName", GetFullName(NPChar));
			//  СЖ <--
			Diag.CurrentNode = "Gover_Main";
            DialogExit();
        break;

        case "Gover_Main":
            iTemp = GetNpcQuestPastDayParam(NPChar, "GoverTalkDate");
            if (iTemp > 0)
            {
				dialog.Text = "Jakie są twoje rozkazy? Ostatni raz, gdy mnie odwiedziłeś "+FindRussianDaysString(iTemp)+" temu.";
			}
			else
			{
			    dialog.Text = "Jakie są twoje rozkazy?";
			}

            Link.l1 = "Ile podatku zarobiłeś "+NPCharSexPhrase(NPChar,"zebrane","zebrane")+" w tym momencie?";
        	Link.l1.go = "Gover_Tax";
            Link.l8 = "Jesteś potrzebny na statku, zwalniam cię z obowiązku miasta.";
            Link.l8.go = "Gover_Fire";
			Link.l9 = "Wszystkiego najlepszego.";
            Link.l9.go = "Exit";
            Diag.TempNode = "Gover_Main";
            SaveCurrentNpcQuestDateParam(NPChar, "GoverTalkDate");
        break;

        case "Gover_Tax":
            iTemp = GetNpcQuestPastDayParam(NPChar, "StartTaxDate");
            iTax  = makeint((GetCharacterSkillSimple(NPChar, SKILL_COMMERCE) + GetCharacterSkillSimple(NPChar, SKILL_LEADERSHIP)) / 2);
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
			if (CheckAttribute(sld, "FortValue"))
			{
			    iFortValue = sti(sld.FortValue);
			}
			else
			{
			    iFortValue = 20;
			}
			NPChar.Gover_Tax_Sum = iFortValue*iTax*iTemp;
			dialog.Text = "Moje umiejętności pozwalają na zbieranie "+FindRussianMoneyString(iFortValue*iTax)+" Za dzień. Powyżej "+FindRussianDaysString(iTemp)+" Ja "+NPCharSexPhrase(NPChar,"zebrane","zebrany")+" "+FindRussianMoneyString(sti(NPChar.Gover_Tax_Sum))+".";
			if (sti(NPChar.Gover_Tax_Sum) > 0)
			{
			    Link.l1 = "Chcę zabrać wszystkie zebrane pieniądze z podatków.";
            	Link.l1.go = "Gover_Tax_Get";
			}
			Link.l2 = "Dzięki za usługę!";
            Link.l2.go = "Exit";
        break;

        case "Gover_Tax_Get":
            SaveCurrentNpcQuestDateParam(NPChar, "StartTaxDate");
            AddMoneyToCharacter(Pchar, sti(NPChar.Gover_Tax_Sum));

			Diag.CurrentNode = "Gover_Main";
            DialogExit();
        break;

        case "Gover_Fire":
            dialog.Text = "Świetnie! Wiesz, nie jestem lądowym szczurem.";
            Link.l8 = "To dobrze.";
            Link.l8.go = "exit_hire";
            Diag.TempNode = "Hired";
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
            DeleteAttribute(sld, "OfficerIdx");
            //  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
            AddQuestRecordInfo("Gen_CityCapture", "t3_2");
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + sld.id));
			AddQuestUserData("Gen_CityCapture", "sName", GetFullName(NPChar));
			//  СЖ <--
        break;
        //////////////////////////////    офицер-наместник <--

		//Указания для компаньона 19.02.08 -->
		case "Companion_Tasks":
			dialog.Text = "Słucham cię.";
			Link.l1 = "To jest o abordażu.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "To dotyczy twojego statku.";
			Link.l2.go = "Companion_TaskChange";
			if(bBettaTestMode) // Только при бета-тесте
			{
			    Link.l3 = "Chcę, żebyś na jakiś czas opuścił mój szwadron i szukał fortuny na własną rękę.";
			    Link.l3.go = "CompanionTravel";
			}
			Link.l8 = "Nic do tej pory.";
			Link.l8.go = "exit";
		break;
		
		case "Companion_TaskBoarding":
			dialog.Text = "Więc jakie jest twoje życzenie.";
			Link.l1 = "Nie wchodź na pokład wrogich statków. Dbaj o siebie i załogę.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "Chcę, żebyś abordażował wrogie statki.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;
		
		case "Companion_TaskChange":
			dialog.Text = "Więc jakie jest twoje życzenie.";
			Link.l1 = "Chciałbym, abyś po wejściu na pokład nie zamieniał swojego statku na inny. Jest zbyt cenny.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "Kiedy abordujesz wrogie statki, możesz je dla siebie zabrać, jeśli okażą się porządne.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;
		
		case "Companion_TaskBoardingNo":
			dialog.Text = "Tak jest, Kapitanie.";
			Link.l1 = "Spokojnie.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;
		
		case "Companion_TaskBoardingYes":
			dialog.Text = "Zostanie zrobione, Kapitanie.";
			Link.l1 = "Spokojnie.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;
		
		case "Companion_TaskChangeNo":
			dialog.Text = "Tak jest Kapitanie.";
			Link.l1 = "Spokojnie.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;
		
		case "Companion_TaskChangeYes":
			dialog.Text = "Zostanie to zrobione, Kapitanie.";
			Link.l1 = "Na spokojnie.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
		//<--
	
		// Самостоятельное плавание компаньона -->
		case "CompanionTravel":
			if(GetAttrValue(PChar, "CompanionTravel") == 3) // Если уже троих отпустил
			{
				dialog.Text = "Kapitanie, nie opuszczę twojego dywizjonu, ponieważ już odwołałeś trzy statki.";
					Link.l1 = "Tak, być może, masz rację.";
					Link.l1.go = "exit";
				break;
			}
		
			dialog.Text = "Nie ma problemu, kapitanie. W jakim mieście mamy się spotkać?";
			for(iTemp=0; iTemp<MAX_COLONIES; iTemp++)
			{
				sld = &colonies[iTemp];
				attr = sld.ID;
				if(sld.nation == "none" || sld.nation == PIRATE || attr == "Panama" || attr == "FortOrange") continue;
				attrLoc = "l" + iTemp;
				Link.(attrLoc) = "In the " + XI_ConvertString("Colony" + attr + "Dat");
				Link.(attrLoc).go = "CompanionTravelToColony_" + attr;
			}
				Link.l99 = "Zmieniłem zdanie.";
				Link.l99.go = "exit";
		break;
			
		case "CompanionTravel_EnemyColony":
			dialog.Text = "Kapitanie, ale nie mogę na ciebie czekać w kolonii, która jest dla nas wroga!";
				Link.l1 = "Wiesz, zapomnij o wszystkich tych podróżach...";
				Link.l1.go = "exit";
		break;
			
		case "CompanionTravel_NoCrew":
			dialog.Text = "Kapitanie, prawie nie mamy marynarzy w załodze! O jakiej podróży mówisz?!";
				Link.l1 = "To prawda, naprawdę brakuje nam marynarzy...";
				Link.l1.go = "exit";
		break;
			
		case "CompanionTravel_NoFood":
			dialog.Text = "Kapitanie, nie mam wystarczających zapasów na pokładzie na taką podróż.";
				Link.l1 = "Tak, masz rację. Podróż może poczekać...";
				Link.l1.go = "exit";
		break;
			
		case "CompanionTravel_NoHP":
			dialog.Text = "Kapitanie, ale mój statek jest w złym stanie. Byłoby niemądrze żeglować samemu w takich okolicznościach!";
				Link.l1 = "Tak, masz rację. Twój statek wymaga naprawy.";
				Link.l1.go = "exit";
		break;
		
		case "CompanionTravel_PrepareStart":
			dialog.Text = "Rozumiem. Do zobaczenia "+XI_ConvertString("Kolonia"+characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID+"Gen")+" do zrobienia "+sti(characters[sti(NPChar.realcompanionidx)].CompanionTravel.Days)+" dni, co mam robić po przybyciu?";
				Link.l1 = "Zostań w porcie kolonii na miesiąc.";
				Link.l1.go = "CompanionTravel_PrepareStart_2";
				Link.l2 = "Wiesz, przeszło mi to przez myśl. Zostań ze mną...";
				Link.l2.go = "exit";
		break;
		
		case "CompanionTravel_PrepareStart_2":
			dialog.Text = "Rozumiem, kapitanie. Odpłynę natychmiast.";
				Link.l1 = "Tak, proszę to zrobić.";
				Link.l1.go = "CompanionTravel_Start";
		break;
			
		case "CompanionTravel_Start":
			Diag.CurrentNode = "CompanionTravel_LastNode";
			NPChar.quest.meeting = true;
			CompanionTravel_SetTraveller(NPChar);
			DialogExit();
		break;
			
		case "CompanionTravel_LastNode":
			Dialog.text = RandPhraseSimple("Dziś znów wypłynę w morze...","Nie zapomnij o naszym spotkaniu w "+XI_ConvertString("Colonia"+characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID+"To")+".");
				link.l2 = "...";
				link.l2.go = "Exit";
				Diag.TempNode = "CompanionTravel_LastNode";
		break;
			
		case "CompanionTravel_ToSquadron":
			if(GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				dialog.text = "Także by mi się to podobało. Od teraz moja łódź jest znowu pod twoim dowództwem, kapitanie.";
					Link.l1 = "Dobrze.";
					Link.l1.go = "exit";
					Diag.TempNode = "hired";
					CompanionTravel_DeleteSpecialShipAttributes(NPChar);
					Group_DeleteAtEnd(NPChar.CompanionTravel.GroupID); // Потрем группу
					SetCompanionIndex(PChar, -1, sti(NPChar.index));
					PChar.CompanionTravel = sti(PChar.CompanionTravel) - 1; // Этого компаньона взяли обратно в эскадру
					DeleteAttribute(NPChar, "CompanionTravel");
			}
			else
			{
				dialog.text = "Kapitanie, już masz pięć statków w swoim oddziale - co zamierzasz zrobić z szóstym? Cóż, myślę, że wolałbym poczekać na ciebie tutaj na moim statku. Twoi nowi towarzysze nie wydają mi się wiarygodni. Ich statki zaraz zatoną, a ty wrócisz po mnie.";
					Link.l1 = "Hej, jesteś chyba mądry? Powinieneś być admirałem, a nie tylko kapitanem!";
					Link.l1.go = "exit";
					Diag.TempNode = "CompanionTravel_ToSquadron_2";
					NPChar.DeckDialogNode = "CompanionTravel_ToSquadron_2"; // ставим снова эту ноду
			}
		break;
			
		case "CompanionTravel_ToSquadron_2":
			dialog.text = "Oh, kapitanie, wróciłeś, tak jak mówiłem. Czy więc jest teraz wolne miejsce w twoim eskadronie?";
			if(GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				Link.l1 = "Tak, "+NPChar.name+", jest jeden. Witamy w eskadrze.";
				Link.l1.go = "exit";
				Diag.TempNode = "hired";
				CompanionTravel_DeleteSpecialShipAttributes(NPChar);
				Group_DeleteAtEnd(NPChar.CompanionTravel.GroupID);
				SetCompanionIndex(PChar, -1, sti(NPChar.index));
				PChar.CompanionTravel = sti(PChar.CompanionTravel) - 1; // Этого компаньона взяли обратно в эскадру
				DeleteAttribute(NPChar, "CompanionTravel");
			}
			else
			{
				Link.l1 = "Nie jeszcze, niestety.";
				Link.l1.go = "exit";
				Diag.TempNode = "CompanionTravel_ToSquadron_2";
				NPChar.DeckDialogNode = "CompanionTravel_ToSquadron_2";
			}
		break;
		// <-- Самостоятельное плавание компаньона
		
		case "tonzag_after_boarding":
			dialog.text = "Kapitanie, wszystko jest do diabła! Wróg ma nas w ścisłym uścisku, obawiam się, że nie puści dopóki nie skończymy na dnie! Nasza załoga jest teraz w prawdziwych tarapatach, a większość działowych jest wyłączona z walki!";
			link.l1 = "Pomogę im. Przejmij dowództwo i wydostań nas stąd!";
			link.l1.go = "tonzag_after_boarding_1";
			DelLandQuestMark(npchar);
		break;
		
		case "tonzag_after_boarding_1":
			dialog.text = "Tak jest, panie!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_GoToGunDeck");
		break;
		
		case "tonzag_after_victory":
			dialog.text = "Sukces, Kapitanie! Desant został zniszczony, wróg postanowił się wycofać i skierował się na południe. Stan statku jest akceptowalny. Żywa załoga: "+GetCrewQuantity(pchar)+" ludzie. Raport zakończony!";
			link.l1 = "Dziękuję! Rum dla wszystkich i wzmacniajcie straże, dopóki nie dotrzemy do portu!";
			link.l1.go = "tonzag_after_victory_1";
		break;
		
		case "tonzag_after_victory_1":
			dialog.text = "Hurra! Tak jest!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_AlonsoBoardingDialog");
		break;
	}
}

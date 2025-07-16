// Чарли Книппель - старый артиллерист
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i, iTemp, amount;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
		//ветка на взятие 2 варианта прохождения - за Англию
		if(CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Eng") && !CheckAttribute(npchar, "quest.HWICTake") && !CheckAttribute(pchar, "questTemp.HWIC.Holl") && !CheckAttribute(pchar, "questTemp.HWIC.Self"))
		{
			dialog.text = "Ahoy, kamracie, łańcuchowy strzał w moją rzyć! Co cię tu sprowadza?";
			link.l1 = "Łańcuchowe kule twoje... co? A, nieważne, chciałem tylko się przywitać.";
			link.l1.go = "exit";
			link.l2 = "Witaj, panie Knippel. Ha, rozumiem, dlaczego nazywają cię Knippel. Tak czy inaczej, słyszałem plotki, że kiedyś służyłeś w angielskiej flocie. Mam wspaniały statek i wykwalifikowaną załogę. Chciałbym zaoferować siebie i mój statek na służbę angielskiej Koronie... eee... Wspólnocie. Czy możesz mi dać jakieś rady lub polecić kogoś, a może pomóc mi w tej sprawie?";
			link.l2.go = "Knippel_check";
			break;
		}
		//за Голландию
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
		{
			if (pchar.questTemp.HWIC.Holl == "toKnippel")
			{
				dialog.text = "Ahoymatey, łańcuchowa kula moja dupa! Co cię tu sprowadza?";
				link.l1 = "Witaj, Panie Knippel. Ha, widzę, dlaczego nazywają cię Knippel. Krążą plotki, że kiedyś służyłeś w angielskiej marynarce wojennej, dlatego chcę cię prosić o pomoc...";
				link.l1.go = "Dominica";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "Łańcuchowy strzał w moje cztery litery! Czego chcesz, kumplu?";
			link.l1 = "Nie, to nic. Wychodzę.";
			link.l1.go = "exit";
			break;
		}
		//за Англию
		if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
		{
			if (pchar.questTemp.HWIC.Eng == "TakeHollConvoy")
			{
				dialog.text = "Ahoy kapitanie, słyszałem plotki o przechwyceniu srebrnego konwoju...";
				link.l1 = "Jesteś dobrze poinformowany, panie Knippel.";
				link.l1.go = "HollConvoy_Check";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("SentJons");
				break;
			}
			if (pchar.questTemp.HWIC.Eng == "Wait")
			{
				dialog.text = "Pytania, kapitanie?";
				link.l1 = "Nie, to nic. Odchodzę.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Eng == "Start_main")
			{
				dialog.text = "Miło cię widzieć, kapitanie! Mój dowódca Richard Fleetwood miał tu przybyć, by cię osobiście poznać, ale wczoraj wieczorem zdarzył się wypadek... Ktoś próbował go zabić na środku ulicy, do kroćset!";
				link.l1 = "Niemożliwe! Co robili strażnicy?";
				link.l1.go = "Fleetwood_house";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "Pytania, kapitanie?";
			link.l1 = "Nie, to nic. Wychodzę.";
			link.l1.go = "exit";
		break;
		}
			dialog.text = "Ahoy, kamracie, łańcuchowy strzał, psiakrew! Co cię tu przygnało?";
			link.l1 = "Cześć, tylko wpadłem na chwilę.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

//-------------------------------------------за Голландию--------------------------------------------------	
		case "Dominica":
			dialog.text = "Ahoy, toż to prawda? A jak stary marynarz, co dawno kotwicę zarzucił, może ci pomóc, kamracie?";
			link.l1 = "Widzisz... Jestem tylko zwykłym kapitanem i odbywam regularne rejsy między Martyniką a Curaçao. Tak więc dwa razy zostałem zaatakowany przez statek-widmo niedaleko Martyniki... Ale wiesz co, to nie jest Fata Morgana ani Latający Holender. Udało mi się poszarpać jej żagle zwykłymi kulami armatnimi!";
			link.l1.go = "Dominica_1";			
		break;
		
		case "Dominica_1":
			dialog.text = "Czyżby tak? To z pewnością nie w stylu statku widmo, by tracić żagle od kul, niech mnie kule biją...";
			link.l1 = "Przetrwaliśmy tylko dlatego, że mój statek mógł go wyprzedzić, żeglując blisko wiatru. Ostatnim razem musiałem wyrzucić cały towar za burtę, by odciążyć kadłub na tyle, by uciec... wyobrażasz sobie tę stratę? To łamie serce!";
			link.l1.go = "Dominica_2";			
		break;
		
		case "Dominica_2":
			dialog.text = "Niech mnie kule biją, kapitanie...";
			link.l1 = "Mathias Beck, gubernator Curacao, po prostu zlekceważył moje skargi. Powiedział, że opowieści o statku widmo to bzdury, a moi strażnicy byli pijani grogiem. Gubernator Martyniki obiecał wysłać tam patrol, ale jego oczy mówiły mi, że nie będzie się tym przejmował. Nie mogę wrócić na Martynikę, dopóki ten przeklęty pirat 'widmo' krąży w pobliżu. Mój statek jest mały, podobnie jak moja załoga, jest prawdopodobne, że nie przeżyjemy trzeciego spotkania z nim...";
			link.l1.go = "Dominica_3";			
		break;
		
		case "Dominica_3":
			dialog.text = "Toż to wielkie nieszczęście, kamracie. Ale jak mogę ci pomóc?";
			link.l1 = "Słyszałem od marynarzy tutaj, że był tu w St. John's kapitan o imieniu Richard Fleetwood, który polował na ten sam nawiedzony statek. Nie znam go osobiście, dlatego opowiadam tę historię tobie, może mógłbyś przekazać mu historię moich nieszczęść? Jestem pewien, że ten plugawy pirat ukrywa się gdzieś w pobliżu dzikich brzegów Dominiki i napada między Barbados a Martynikę.";
			link.l1.go = "Dominica_4";			
		break;
		
		case "Dominica_4":
			dialog.text = "Między Barbados a Martyniką? Ya har! Tłusta i bogata trasa handlowa. To brzmi dokładnie jak coś, co zrobiłby ten szczur lądowy.";
			link.l1 = "Nie jestem bogaty ani tłusty, i nie mam pieniędzy, by przekupić kapitana marynarki dla eskorty wojskowej. Ale jeśli Sir Fleetwood już poluje na tego szczura pokładowego, mógłbyś mu powiedzieć, gdzie może znaleźć tego 'Latającego Holendra'?";
			link.l1.go = "Dominica_5";			
		break;
		
		case "Dominica_5":
			dialog.text = "Zrobiłeś dobrze, przybywając tutaj, kumplu. Opowiem twoją historię odpowiednim ludziom, niech mnie piorun trzaśnie! Wkrótce będziesz mógł znów handlować z Martyniką.";
			link.l1 = "Mam nadzieję, że Bóg usłyszy twoje słowa! Dziękuję za wysłuchanie mnie, Charlie. Mam nadzieję na najlepsze. Żegnaj i unikaj kartaczy!";
			link.l1.go = "Dominica_6";			
		break;
		
		case "Dominica_6":
			DialogExit();	
			pchar.questTemp.HWIC.Holl = "toDominica";
			AddQuestRecord("Holl_Gambit", "1-17");
			pchar.quest.toDominica.win_condition.l1 = "location";
			pchar.quest.toDominica.win_condition.l1.location = "Dominica";
			pchar.quest.toDominica.function = "PrepareToFleetwoodAttack";
			DelMapQuestMarkShore("Shore1");
			DelMapQuestMarkShore("Shore2");
			AddMapQuestMarkIsland("Dominica", true);
		break;

//----------------------------------------------за Англию--------------------------------------------------	
		case "Knippel_check"://начинаем проверять нашего ГГ по всем статьям
			if(makeint(PChar.reputation.nobility) < 48)//низкая репа
			{
				// belamour legendary edition покажем критерии
				notification("Reputation Too Low! (Adventurer)", "None");
				PlaySound("Voice\English\hambit\Charlie Knippel-04.wav");
				dialog.text = "Wesoła Stara Anglia nie potrzebuje usług od łotrów, szrapnel w moją dupę! Z szacunkiem, możesz się wypchać.";
				link.l1 = "Hej hej kumplu, uważaj na język, bo ci go zaszyję!";
				link.l1.go = "exit";
				break;
			}
			else
			{
				notification("Reputation Check Passed", "None");
			}
			if(GetSummonSkillFromName(pchar, SKILL_SAILING) < 30)//низкая навигация
			{
				dialog.text = "Kapitánie, będę szczery. Nie potrafiłbyś wypłynąć z mokrego worka. Wróć, gdy zdobędziesz więcej umiejętności nawigacyjnych, kumasz?";
				// belamour legendary edition покажем критерии  -->
				notification("Skill Check Failed (30)", SKILL_SAILING);
				//<--
				dialog.text = "Cao'n, nasza flota potrzebuje doświadczonych kapitanów, nie landry! Wróć, gdy opanujesz sztukę nawigacji.";							 
				link.l1 = "Rozumiem... W takim razie zobaczymy się później.";
				link.l1.go = "exit";
				break;
			}
			else
			{
				notification("Skill Check Passed", SKILL_SAILING);
			}
			dialog.text = "Ahoy, jesteś tu w samą porę, kapitanie, łańcuchowa kula w moją rufę! Richard nie wiedział, na kogo może liczyć w tej ryzykownej sprawie, nawet rozważał jej odrzucenie... Więc dzisiaj ptaszki możliwości śpiewają słodko w twoje uszy. Jeśli spełnisz nasze standardy, polecę cię pewnemu bardzo ważnemu człowiekowi. Masz wystarczająco śrutu w portkach, żeby sobie z tym poradzić?";
			link.l1 = "Jestem nabity kartaczami, panie Knippel.";
			link.l1.go = "Knippel_task";
		break;
		
		case "Knippel_task"://первое задание
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Bridgetown_tavernkeeper"));
			DelLandQuestMark(characterFromId("Lucas"));
			DelMapQuestMarkCity("Bridgetown");
			DelMapQuestMarkCity("Villemstad");
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Ar har! Widzę, że twój drąg jest gotowy, kapitanie! Wkrótce poleci iskra! Teraz słuchaj uważnie. Srebrna flota Holenderskiej Kompanii Zachodnioindyjskiej opuściła Willemstad na Curacao dzień lub dwa temu. Płynie do Philipsburg. Tym razem w flocie jest tylko kilka statków. Jeden Galeon z srebrem w ładowni oraz dwa eskortowce. Przechwyć srebrną flotę, zdobądź Galeon z ładunkiem srebra i doprowadź go do Antigui. Możesz jednak zatopić eskorty, są jednorazowe. Traf ich w wątroby, yar!";
			link.l1 = "Ich dni są policzone.";
			link.l1.go = "Knippel_task_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Knippel_task_1":
			dialog.text = "Mała rada, kapitanie. Szlak handlowy z Curacao do Sint Maarten leży niedaleko brzegów St. Christopher. Radziłbym przygotować tam zasadzkę. Przygotuj siebie i swój statek dobrze do tej potyczki. Zadzieranie z Kompanią Zachodnioindyjską to nie spacer po parku z piękną dziewczyną.";
			link.l1 = "Zdaję sobie sprawę, w co się pakuję, ale doceniam twoją szczerość, panie Knippel. Wrócę z holenderskim srebrem.";
			link.l1.go = "Knippel_task_2";			
		break;
		
		case "Knippel_task_2":
			DialogExit();
			npchar.quest.HWICTake = "true";
			pchar.questTemp.HWIC.CanTake.Eng = "true";//признак, что английка уже бралась
			HWICSilverConvoyInWorld();
			AddQuestRecord("Holl_Gambit", "2-1");
			ReOpenQuestHeader("Holl_Gambit"); // данила ,чтобы вышел из архива. 																				   
			pchar.questTemp.HWIC.Eng = "begin";
			SetFunctionTimerCondition("HollConvoy_Over", 0, 0, 15, false);
		break;
		
		case "HollConvoy_Check"://начинаем проверять
			int iHal = 0;
			for(i = 0; i < COMPANION_MAX; i++)
			{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
					sld = GetCharacter(iTemp);
					pchar.questTemp.HWIC.Eng.CompanionIndex = sld.Index;
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_GALEON_L) iHal++;
				}
			}//признак наличия ТГ в компаньонах
			if (iHal > 0)
			{
				amount = sti(pchar.questTemp.HWIC.Eng.SlvQty) - GetSquadronGoods(pchar, GOOD_SILVER);
				if (amount <= 0)
				{
					dialog.text = "Nie potrzeba mi opowiadać, co się wydarzyło, kapitanie. Zostałem poinformowany o wszystkim, gdy celnik sprawdzał twój statek... Odwaliłeś kawał dobrej roboty, kapitanie. Wprost wyśmienicie! Nie brzmiało to na łatwe, łańcuchowy strzał w mój zadek!";
					link.l1 = "Miło być docenionym.";
					link.l1.go = "HollConvoy_complete";
				}
				else
				{
					dialog.text = "Nie musisz mi mówić, co się stało, koleś. Zostałem poinformowany o wszystkim, gdy agent celny sprawdzał twój statek... Nie udało ci się przywieźć całego srebra, łańcuchowe strzały, co za bzdura! Wiem dokładnie, ile srebra było na tym statku Kompanii Wschodnioindyjskiej, co do peso. Celem tej misji było nie tylko przetestowanie twoich umiejętności bojowych, ale także twojej uczciwości. Zawiodłeś w tym drugim. Wynoś się z mojego domu, obiboku!";
					link.l1 = "Do diabła z tobą, głupcze!";
					link.l1.go = "HollConvoy_fail";
				}
			}
			else
			{
				dialog.text = "Ahoj, kamracie. Nie widzę holenderskiego East Indiamana w twojej eskadrze. Kazałem ci przyprowadzić ją tutaj jako łup. Sprzedałeś ją i próbowałeś zatrzymać pieniądze dla siebie, co?";
				link.l1 = "Zaczekaj, miałem przyprowadzić statek? Myślałem, że chciałeś tylko srebro.";
				link.l1.go = "HollConvoy_noShip";
			}
		break;
		
		case "HollConvoy_noShip":
			dialog.text = "Nie ma mowy, by ktoś robił z Charlie'ego Knippela głupca, kamracie! Doskonale pamiętam, co ci powiedziałem, a czego nie. Złamałeś warunki naszej umowy i żaden uczciwy Anglik z tobą nie będzie współpracował, nie ma tu miejsca dla łajdaków. Wynoś się z mojego domu, szczurze pokładowy!";
			link.l1 = "A więc do diabła z tobą, głupcze!";
			link.l1.go = "HollConvoy_fail";
		break;
		
		case "HollConvoy_fail":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-3");
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.Eng");//зачищаем для возможности отката к голландскому варианту
			pchar.questTemp.HWIC.Fail2 = "true";
		break;
		
		case "HollConvoy_complete":
			dialog.text = "Odwiedź mnie jutro, a przedstawię cię mojemu mecenasowi. On zaproponuje ci więcej pracy godnej twoich umiejętności. A do tego zadba o twoją... zachętę finansową. Żagle na wiatr!";
			link.l1 = "Bardzo dobrze, panie Knippel. Będę tutaj jutro.";
			link.l1.go = "exit";
			npchar.greeting = "knippel_2";
			AddDialogExitQuestFunction("HollConvoy_Remove");
			AddQuestRecord("Holl_Gambit", "2-4");
			SetTimerFunction("EnglandGambit_2_ZadanieStart", 0, 0, 1);
			pchar.questTemp.HWIC.Eng = "Wait";
			AddSimpleRumourCity("They say that you captured a Dutch ship filled with silver. Well done! You are a valiant sailor, captain! Godspeed!", "SentJons", 10, 3, "");
		break;
		
		case "Fleetwood_house":
			dialog.text = "Zadaję sobie to samo pytanie... Jakiś drań rzucił pieprz w oczy kapitana Fleetwooda i dźgnął go w pierś, zanim Richard zdołał chwycić za ostrze. Morderca liczył, że jednym pchnięciem zakończy kapitana, bo nie miał czasu na kolejne, ale nie udało mu się. Kapitan Fleetwood zawsze nosi kirys pod płaszczem\nTen plugawy szumowina, łańcuchowy strzał wątrobę jego załatwił, zdołał uciec i zniknąć. Wygląda na to, że ma przyjaciół w mieście. Jedyny szczegół, który kapitan pamięta, to że zabójca ma tylko jedno oko. To nam jednak niewiele pomoże, bo ostatnio na dokach krąży sporo takich Cyklopów\nRichard stracił dużo krwi, a pieprz strasznie podrażnił mu oczy, przez co teraz jest prawie ślepy...";
			link.l1 = "Pieprz mielony? To kosztowny sposób, by kogoś oślepić. Fleetwood musiał naprawdę kogoś wkurzyć. Przykro mi z powodu twojego kapitana. Czy poszukiwania napastnika przyniosły jakieś rezultaty?";
			link.l1.go = "Fleetwood_house_1";
		break;
		
		case "Fleetwood_house_1":
			dialog.text = "Marines Cap'na Fleetwooda przeszukali całe miasto i okoliczne zatoki, ale nic nie znaleźli, niech ich kule zeżrą! Jeśli nie znaleźliśmy go zaraz po ataku, to teraz nie ma co marzyć o odnalezieniu tego drania. Cap'n Fleetwood ma wielu wrogów... Ale, kapitanie, mój dowódca chce cię zobaczyć mimo tego wypadku. Odpoczywa teraz w swoim domu, więc chodźmy do niego. Podążaj za mną!";
			link.l1 = "Prowadź, panie Knippel.";
			link.l1.go = "Fleetwood_house_2";
		break;
		
		case "Fleetwood_house_2":
			chrDisableReloadToLocation = true;//закрыть локацию
			bDisableFastReload = true;//закроем быстрый переход
			LocatorReloadEnterDisable("SentJons_town", "reload1_back", true);
			LocatorReloadEnterDisable("SentJons_town", "reload2_back", true);
			LocatorReloadEnterDisable("SentJons_town", "gate_back", true);//чтобы не сбежал
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SentJons_town", "reload", "houseH1", "OpenTheDoors", -1);
			pchar.quest.Knippel_Outside.win_condition.l1 = "location";
			pchar.quest.Knippel_Outside.win_condition.l1.location = "SentJons_town";
			pchar.quest.Knippel_Outside.function = "Knippel_GoTown";
			LocatorReloadEnterDisable("SentJons_town", "houseSP3", true);
			sld = characterFromId("Fleetwood");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_houseSP3_room", "goto", "goto1");
			AddLandQuestMark(sld, "questmarkmain");
			pchar.GenQuestBox.SentJons_houseSP3_room = true;
			pchar.GenQuestBox.SentJons_houseSP3_room.box1.money = 110000;
		break;
		
		case "InFleetwoodHouse":
			dialog.text = "Kapitan Fleetwood jest na górze w swoim pokoju. Idź do niego, czeka na ciebie. Ja zostanę tutaj.";
			link.l1 = "Zrozumiano, panie Knippel. Już wyruszam.";
			link.l1.go = "exit";	
		break;
		
		case "Knippel_ToOfficer":
			dialog.text = "Słuchaj kap... Kapitan Fleetwood jest teraz bezpieczny i w dobrych rękach. Chcę ci pomóc zemścić się na draniu, który go zaatakował. Oferuję ci moje usługi jako artylerzysta. Nie jestem zbyt dobry w szermierce, jestem na to za stary, ale potrafię strącić marsel z kupieckiego statku z tysiąca kroków.";
			link.l1 = "Teraz bym to chciał zobaczyć. Witaj na pokładzie, Panie Knippel!";
			link.l1.go = "Knippel_ToOfficer_1";	
		break;
		
		case "Knippel_ToOfficer_1":
			LocatorReloadEnterDisable("SentJons_town", "reload1_back", false);
			LocatorReloadEnterDisable("SentJons_town", "reload2_back", false);
			LocatorReloadEnterDisable("SentJons_town", "gate_back", false);//откроем локаторы
			//Книппеля - в офицеры
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.HalfImmortal = true;//полубессмертен
			npchar.loyality = 20;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			SetFunctionTimerCondition("GotoBridgetownOver", 0, 0, 30, false);//на все дела - 1 месяц
			AddSimpleRumourCity("They say that Sir Richard Fleetwood himself is indebted in you. You are a very important man in our town, sir", "SentJons", 10, 3, "");
		break;
		
		case "hired":
			dialog.text = "Ahoy kapitanie! Potrzebujesz czegoś?";
			link.l1 = "Nie, nic.";
			link.l1.go = "exit";
			NextDiag.TempNode = "hired";
		break;
		
		case "MC_GoAway":
			PlaySound("Voice\English\hambit\Charlie Knippel-07.wav");
			if (pchar.questTemp.HWIC.Eng == "MirageFail")
			{
				dialog.text = "Jesteś kompletnym głupcem, kamracie, łańcuch kul moją dupę! Nie udało ci się wykonać elementarnego zadania - przechwycić 'Mirage' bez utraty 'Valkyrie'\nNasza załoga nie będzie już służyć pod twoim dowództwem. Jesteśmy pewni, że Sir Fleetwood zatwierdzi naszą decyzję, on lubi idiotów tak mało, jak my.";
				link.l1 = "Pieprz się ty i twój pan!";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.HWIC.Eng == "GotoBridgetown" || pchar.questTemp.HWIC.Eng == "SeekVanBerg")
			{
				dialog.text = "Jesteś kompletnym idiotą, kumplu, wystrzelić na moje siedzenie! Zmarnowaliśmy za dużo czasu na rozwiązywanie twoich osobistych problemów\nNasza załoga nie będzie ci już dłużej służyć. Jesteśmy pewni, że Sir Fleetwood zatwierdzi naszą decyzję, on lubi idiotów tak samo mało jak my.";
				link.l1 = "Pierdol się ty i twój pan!";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.HWIC.Eng == "VanBergFailInWorld")
			{
				dialog.text = "Jesteś kompletnym idiotą, kumplu, łańcuchowy strzał w moją dupę! Kazano ci grać samotnego kupca na 'Valkyrie', a co zrobiłeś? Przestraszyłeś pirata swoją flotyllą!\nJesteśmy pewni, że Sir Fleetwood zatwierdzi naszą decyzję, on nie lubi idiotów tak samo jak my.";
				link.l1 = "Pierdolisz ty i twój pan!";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.HWIC.Eng == "MirageTake")
			{
				dialog.text = "Ty kompletny idioto, kamracie, łańcuchowa kula w moją dupę! Czy zdecydowałeś się marnować nasz czas na cokolwiek innego niż schwytanie 'Mirage' i żeglowanie do Antigui?\nNasza załoga nie będzie ci dłużej służyć. Jesteśmy pewni, że Sir Fleetwood zatwierdzi naszą decyzję, on nie lubi idiotów tak samo jak my.";
			link.l1 = "Pierdolisz się ty i twój pan!";
			link.l1.go = "exit";
			}
			PChar.quest.Munity = "Deads";
			LAi_LocationFightDisable(&Locations[FindLocation("Ship_deck")], false);
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_VALCIRIA)//если сам на Валькирии
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
				pchar.Ship.name = "Boat";
				SetBaseShipData(pchar);
				SetCrewQuantityOverMax(PChar, 0);
			}
			else
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_VALCIRIA)
						{
							pchar.questTemp.HWIC.Eng.CompanionIndex = sld.Index;
							sld = GetCharacter(sti(pchar.questTemp.HWIC.Eng.CompanionIndex));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			LAi_CharacterDisableDialog(npchar);
			LAi_SetImmortal(npchar, true);
			ChangeCharacterAddressGroup(npchar, "SentJons_houseH1", "goto", "goto1");//Книппеля домой
			pchar.questTemp.HWIC.Eng = "end";
			pchar.questTemp.HWIC.Detector = "eng_fail";
			CloseQuestHeader("Holl_Gambit");
		break;
		
		case "OnCuracao":
			pchar.quest.HWICEng_toBarbadosOver.over = "yes";//снять прерывание
			dialog.text = "Witaj, kapitanie. Miło cię widzieć!";
			link.l1 = "Witaj, panie Knippel. Masz pieniądze? Daj je mi i ruszajmy do Willemstad po Abigail. Dołączysz do mnie?";
			link.l1.go = "OnCuracao_1";	
		break;
		
		case "OnCuracao_1":
			dialog.text = "Kapitanie, słuchaj... Teraz nie ma potrzeby nigdzie się ruszać.";
			link.l1 = "O czym ty mówisz? To bzdury!";
			link.l1.go = "OnCuracao_2";	
		break;
		
		case "OnCuracao_2":
			dialog.text = "Mam list od kapitana Fleetwooda dla ciebie. I pieniądze. Ale te pieniądze nie są dla ojca Abigail, lecz dla ciebie. Dwieście tysięcy peso. Przeczytaj list i postaraj się go nie oceniać zbyt surowo...";
			link.l1 = "Co się do cholery dzieje w tych czasach?! Kolejna nieprzyjemna niespodzianka? Daj mi list!";
			link.l1.go = "OnCuracao_3";	
		break;
		
		case "OnCuracao_3":
			DialogExit();
			NextDiag.CurrentNode = "OnCuracao_4";
			AddMoneyToCharacter(pchar, 200000);
			LAi_SetCitizenType(npchar);
			npchar.lifeday = 1;//еще денек пусть погуляет по пляжу
			pchar.quest.Holland_ShoreAttack.win_condition.l1 = "location";
			pchar.quest.Holland_ShoreAttack.win_condition.l1.location = "Curacao";
			pchar.quest.Holland_ShoreAttack.function = "CreateHollandShorePatrol";//патруль в прибрежных водах
			LocatorReloadEnterDisable("SentJons_town", "basement1_back", false);//открыть подземелье
			pchar.questTemp.HWIC.Eng = "MerdokMeeteng";
			AddQuestRecordInfo("LetterFromFleetwood", "1");
			AddQuestRecord("Holl_Gambit", "2-23");
			AddLandQuestMark(npchar, "questmarkmain");
		break;
		
		case "OnCuracao_4":
			dialog.text = "Czytałeś to, kapitanie? Będę szczery. Wstyd mi za kapitana Fleetwooda i za to, co zrobił, łańcuchową kulą... ach, do diabła z tym. Rodenburg był wściekły, gdy dowiedział się o romansie Abigail z Richardem. Patrole piesze przeszukują Curaçao, a wojskowe statki Kompanii patrolują lokalne wody. Musimy się stąd wynieść, do diabła.\n Kapitanie, potrzebujesz artylerzysty? Nie potrzebuję luksusu - tylko normalnych racji morskich regularnie. Nie jestem dobry w szermierce, za stary na to, ale mogę strącić topgallanty z kupieckiego statku z tysiąca kroków.";
			link.l1 = "No cholera, chciałbym zobaczyć, jak to zrobisz, panie Knippel. Witaj na pokładzie!";
			link.l1.go = "Knippel_hire";
			link.l2 = "Żałuję, że w ogóle pomogłem wam, angielskim łajdakom. Teraz nie wiem, jak wyjść z tego bałaganu. Idźcie swoją drogą, mam dość niespodzianek.";
			link.l2.go = "Knippel_exit";
			DelLandQuestMark(npchar);
		break;
		
		case "Knippel_hire":
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			npchar.quest.OfficerPrice = sti(pchar.rank)*200;
			npchar.OfficerWantToGo.DontGo = true;
			DeleteAttribute(npchar, "CompanionDisable");//теперь можем и в компаньоны
			DeleteAttribute(npchar, "HalfImmortal");
			npchar.loyality = MAX_LOYALITY;
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			SetCharacterPerk(npchar, "ShipEscape");
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			LAi_SetImmortal(npchar, false);
			LAi_SetHP(npchar, 120, 120);
			LAi_SetOfficerType(npchar);
			npchar.greeting = "knippel_hire";
			NextDiag.CurrentNode = "Knippel_officer";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			
			//Sinistra - через 2 месяца стартует личный квест Чарли Книппеля "Длинные тени старых грехов"
			SetTimerCondition("DTSG_Start", 0, 0, 60, false);
		break;
		
		case "Knippel_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "", -1);
		break;
		
//------------------------------------------------против всех-----------------------------------------------
		case "Knippel_abordage":
			dialog.text = "Stój, ty szczurze ładowni! Czemu zaatakowałeś ten spokojny holenderski statek? Nie mam żadnych cennych towarów ani złota, kulą łańcuchową w moją rzyć!";
			link.l1 = "Holenderski statek? Haha! Nie rozśmieszaj mnie, 'Holendrze'. Zaatakowałem twój brygantynę, aby cię pojmać, drogi Charlie. Witamy w moim ładowni. Porozmawiamy o tym, dokąd płynąłeś i dlaczego...";
			link.l1.go = "Knippel_abordage_1";	
		break;
		
		case "Knippel_abordage_1":
			AddQuestRecord("Holl_Gambit", "3-20");
            pchar.quest.Knippel_DieHard.over = "yes";
		    DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
            DialogExit();
			LAi_SetPlayerType(pchar);
			pchar.questTemp.HWIC.Self = "KnippelPrisoner";
			npchar.lifeday = 0;
			SetFunctionTimerCondition("RemoveKnippelOver", 0, 0, 1, false);//таймер до конца суток, ибо нефиг
		break;
		
		case "Knippel_prisoner":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\hambit\Charlie Knippel-07.wav");
			dialog.text = "Jesteś diabłem, piracie... Spłoniesz w piekle za wszystkie swoje grzechy! Krzycz...";
			link.l1 = "Odpocznij, kaznodziejo. Głosisz jak purytanin. Lepiej najpierw zajmij się stanem swojej duszy.";
			link.l1.go = "Knippel_prisoner_1";
		break;
		
		case "Knippel_prisoner_1":
			dialog.text = "Co planujesz, łotrze? Czego chcesz od mojego dowódcy i od biednej holenderskiej dziewczyny?";
			link.l1 = "To nie twoja sprawa, Charlie. Nie potrzebuję cię już. Wstawaj.";
			link.l1.go = "Knippel_prisoner_2";	
		break;
		
		case "Knippel_prisoner_2":
			dialog.text = "Chcesz mnie zabić? Godne takiego łajdaka jak ty. *pluje* Pieprz się!";
			link.l1 = "Wstań, Charlie. Odmów swoje ostatnie modlitwy.";
			link.l1.go = "Knippel_prisoner_3";	
		break;
		
		case "Knippel_prisoner_3":
			DialogExit();
			LAi_SetActorType(pchar);
			sld = characterFromId("KnippelClone");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Ground_StandUp", "Kill_Knippel", 3.5);
			pchar.quest.RemoveKnippelOver.over = "yes";//снять таймер
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Knippel_officer":
			dialog.text = "Ahoj kapitanie, łańcuchowy pocisk w moją dupę!";
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Panie Knippel, udaję się do starożytnego, zaginionego indiańskiego miasta Tayasal. Będę szczery, to będzie naprawdę niebezpieczna wyprawa i również niezwykła - musimy tam dotrzeć przez ten...magiczny idol. Czy dołączysz do mnie?";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Panie Knippel, daj mi pełny raport o statku.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Chcę, abyś zakupywał pewne towary za każdym razem, gdy jesteśmy w porcie.";
				Link.l12.go = "QMASTER_2";
			}
			
			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "Przybyłem na twoje wezwanie, kapitanie.";
				Link.l2 = "Muszę wydać ci kilka rozkazów.";
				Link.l2.go = "Companion_Tasks";
				NextDiag.TempNode = "Knippel_officer";// не забыть менять в зависисомости от оффа
				break;
			}
			Link.l1 = "Słuchaj moich rozkazów!";
            Link.l1.go = "stay_follow";
			link.l2 = "To nic. Zwolniony!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Knippel_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Niech mnie... Działa są w porządku, wymieniamy te, które wybuchają, i trzymamy proch suchym i bezpiecznym. Jakiego raportu się spodziewałeś, kapitanie? Jestem starym artylerzystą, nie kwatermistrzem. Łańcuchowe strzały, psiakrew, jestem najlepszym artylerzystą na Karaibach, pamiętaj!";
			Link.l1 = "Nie ma tu co się kłócić, panie Knippel, znasz się na swoim fachu. Znajdę sobie kwatermistrza, nie martw się.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Chcesz, by stary Charlie zamienił swoją baterię dział na rufowy pokład? Kapitanie, ja zatapiam statki, a nie walczę o każdy peso. I jestem pewien, że oskubią mnie w pierwszej lepszej kolonii, gdzie to spróbujemy.";
			link.l1 = "Oczywiście, panie Knippel. Powinienem zacząć szukać odpowiedniego kwatermistrza.";
			link.l1.go = "exit";
		break;
		
		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "Słucham cię.";
			Link.l1 = "Chodzi o abordaż.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "Chodzi o twój statek.";
			Link.l2.go = "Companion_TaskChange";
			if (bBettaTestMode) // Только при бета-тесте
			{
				Link.l3 = "Chcę, żebyś opuścił moją eskadrę na jakiś czas i poszukał szczęścia na własną rękę.";
				Link.l3.go = "CompanionTravel";
			}
			Link.l8 = "Nic jak dotąd.";
			Link.l8.go = "exit";
			break;

		case "Companion_TaskBoarding":
			dialog.Text = "A więc jakie jest twoje życzenie.";
			Link.l1 = "Nie aborduj wrogich statków. Dbaj o siebie i załogę.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "Chcę, żebyś abordował wrogie statki.";
			Link.l2.go = "Companion_TaskBoardingYes";
			break;

		case "Companion_TaskChange":
			dialog.Text = "Więc jakie jest twoje życzenie.";
			Link.l1 = "Chciałbym, abyś nie zamieniał swojego statku na inny po abordażu. Twój statek jest zbyt cenny.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "Kiedy abordujesz wrogie statki, możesz je zabrać dla siebie, jeśli są warte zachodu.";
			Link.l2.go = "Companion_TaskChangeYes";
			break;

		case "Companion_TaskBoardingNo":
			dialog.Text = "Tak jest!";
			Link.l1 = "Spocznij.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
			break;

		case "Companion_TaskBoardingYes":
			dialog.Text = "Zostanie to zrobione.";
			Link.l1 = "Spocznij.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
			break;

		case "Companion_TaskChangeNo":
			dialog.Text = "Tak jest!";
			Link.l1 = "Zostanie to zrobione.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
			break;

		case "Companion_TaskChangeYes":
			dialog.Text = "To będzie zrobione.";
			Link.l1 = "Spocznij.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
			break;
			//	<========////////////////////////////////////////

		case "stay_follow":
            dialog.Text = "Rozkazy?";
            Link.l1 = "Stój tutaj!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Podążaj za mną i nadążaj!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Zmień rodzaj amunicji do swojej broni palnej.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Wybór rodzaju amunicji:";
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
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Zmiana usposobienia!";
            Link.l1 = "Zwolniony.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Nastąpiła zmiana nastawienia!";
            Link.l1 = "Zwolniony.";
            Link.l1.go = "Exit";
        break;
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "Naprawdę się do ciebie przywiązałem podczas mojej służby, "+pchar.name+", a ja nie zostawię mojego kapitana na lodzie. Poszedłbym za tobą przez piekło, gdyby potrzeba była. Jestem z tobą!";
			link.l1 = "Dziękuję, panie Knippel! Cieszę się, że miałem rację co do ciebie.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Kiedy zaczynamy, niech mnie kule łańcuchowe trafią?";
			link.l1 = "Trochę później. Musimy się na to przygotować.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "22");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Jesteś "+GetSexPhrase("złodziej, panie! Straże, bierzcie go","złodziejka, dziewczyno! Straże, weźcie ją")+"!!!","Spójrz tylko na to! W chwili, gdy się odwróciłem, postanowiłeś sprawdzić moją skrzynię! Łapać złodzieja!!!","Straże! Rabunek! Łapcie złodzieja!!!");
			link.l1 = "Cholera!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}

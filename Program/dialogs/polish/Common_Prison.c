// городские тюрьмы
void ProcessDialogEvent()
{
	int amount, iGunQty, iGunGoods, iGunPrice, iTemp;
	int iTest;
	ref NPChar, sld, location;
	ref arItem;
	ref rColony;
	aref Link, NextDiag;
	string sTemp;
	float locx, locy, locz;
	bool  ok;
	// belamour для ночного приключения -->
	int i;
	int SoldQty = 0;
	int SoldNum[10];
	// <--

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Prison\" + NPChar.City + "_Prison.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "NoMoreTalkExit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;
		//---------------- Начальник тюрьмы ------------------
		case "First_officer":
			dialog.text = RandPhraseSimple("Jestem strażnikiem więziennym. Czego tu szukasz?","Czego potrzebujesz? Dlaczego przyszedłeś do więzienia?");
			NextDiag.TempNode = "First_officer";
			if(startHeroType == 4 && NPChar.location == "SantaCatalina_prison" && !CheckAttribute(pchar, "questTemp.HelenSCprison"))
			{
				dialog.text = "Panna MacArthur? Zdziwiony cię widzieć. Nie aresztowaliśmy nikogo z twojej załogi ani kapitana Swensona, o ile mi wiadomo.";
				link.l1 = "Jestem tutaj, panie. Czy to nie jest dozwolone? Nie rozmawiałam z więźniami za twoimi plecami.";
				link.l1.go = "Helen_meeting";
				pchar.questTemp.HelenSCprison = true;
				break;
			}
			// --> Sinistra Длинные тени старых грехов
			if(CheckAttribute(pchar,"questTemp.DTSG_AntiguaTrevoga") && npchar.city == "SentJons")
			{
				dialog.text = "Ach, Charles de Maure... Powinieneś zostać aresztowany i dołączyć do swojego oficera, ale... incydent w banku uznano za godne pożałowania nieporozumienie.";
				link.l1 = "Podoba mi się sposób, w jaki rozpocząłeś tę rozmowę, Panie "+GetFullName(NPChar)+". Mogę wszystko wyjaśnić.";
				link.l1.go = "DTSG_AntiguaTrevoga_2";
				break;
			}
			// <-- Длинные тени старых грехов
			
			//--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "jailskiper")
			{
				link.l1 = "Oficerze, słyszałem, że w waszym więzieniu jest człowiek o imieniu Folke Deluc. Czy mogę coś zrobić, aby go uwolnić?";
                link.l1.go = "Sharlie";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "freeskiper")
			{
				link.l1 = "Oficerze, to znowu ja odnośnie więźnia Folke Deluc. Kupiłem prawa do jego długu i chcę, aby ten człowiek został uwolniony i przekazany mi. Oto dokumenty jego długu, spójrz.";
                link.l1.go = "Sharlie_3";
				break;
			}	
			//<-- Бремя гасконца
			
			//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
			// Офицер с патентом
			if(IsOfficerFullEquip())
			{
				dialog.text = "Pozdrowienia, kapitanie. Co cię tu przynosi?";
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "Pozdrowienia, Wiceadmirał! Jak mogę Ci pomóc?";
			}
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				dialog.text = "Wasza Wysokość, Generale Gubernatorze! Czy macie jakieś rozkazy?";
			}
			// <-- legendary edition
			link.l1 = "Oh, nic specjalnego, wiesz, tylko się rozglądam po mieście, więc zawędrowałem tu przypadkowo.";
			link.l1.go = "exit";
			link.l2 = "Chciałem porozmawiać o pewnych interesach.";
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakFort"))
			{
				if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l2.go = "F_ShipLetters_1";
				}
				else
				{
					link.l2.go = "quests";
				}		
			}
			else
			{
				if(CheckAttribute(pchar,"questTemp.ReasonToFast") && !CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
				{
					link.l2.go = "ReasonToFast_Prison1";
				}
				else
				{
					link.l2.go = "quests";
				}	
			}
			if (!sti(pchar.questTemp.jailCanMove))
			{
				link.l4 = "Chcę wejść do więzienia.";
				link.l4.go = "ForGoodMove";		
			}
			if (CheckAttribute(pchar, "questTemp.jailCanMove.City") && npchar.city == pchar.questTemp.jailCanMove.City)
			{
				link.l5 = "Hej, czy mógłbyś mi powiedzieć, za jaki przestępstwo skazano więźnia o imieniu "+GetFullName(characterFromId(pchar.questTemp.jailCanMove.prisonerId))+"odbywa karę za?";
				link.l5.go = "KnowAboutPrisoner";	
			}
			
			if(CheckAttribute(pchar,"GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
			{
				if(!CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
				{
					bool zMsm = (CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour")) && (!CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor"));
					if(pchar.GenQuest.CaptainComission == "MayorTalkBad" || zMsm) //говорил с губером и отказался или узнал слухи, но не говорил с губером
					{
						link.l6 = "Słyszałem, że były kapitan patrolu "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Imię")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" jest tutaj przetrzymywany w areszcie. Czy mogę z nim porozmawiać?";
						link.l6.go = "CapComission_PrisonBad1";
					}
					if(pchar.GenQuest.CaptainComission == "MayorTalkGood")
					{
						link.l6 = "Ja "+GetFullName(pchar)+", działając w imieniu i na polecenie gubernatora "+XI_ConvertString("Kolonia"+pchar.GenQuest.CaptainComission.City+"Gen")+"muszę rozmawiać z byłym kapitanem "+pchar.GenQuest.CaptainComission.Name+".";
						link.l6.go = "CapComission_PrisonGood1";
					}
				}	
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if(pchar.GenQuest.EncGirl.Father == "fort_keeper"  && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = "To jest o twojej córce...";
						link.l9.go = "EncGirl_1";
					}
				}
			}
			
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "begin" && NPChar.location == pchar.GenQuest.Marginpassenger.City + "_prison")
			{
				link.l12 = "Mam do ciebie sprawę, oficerze. Wierzę, że byłoby to dla ciebie interesujące, ponieważ jest związane z twoimi obowiązkami.";
				link.l12.go = "Marginpassenger";
			}
			
			// Warship, 16.05.11. Генер "Justice for sale".
			if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.PrisonWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_prison")
			{
				link.l13 = "Chcę porozmawiać z tobą o pewnym człowieku - "+PChar.GenQuest.JusticeOnSale.SmugglerName+". On jest twoim więźniem, jeśli się nie mylę.";
				link.l13.go = "JusticeOnSale_1";
			}
			
			// --> belamour ночной приключенец
			if(CheckAttribute(pchar,"GenQuest.NightAdventureToJail"))
			{
				link.l14 = "Witaj oficerze. O ile mi wiadomo, jakiś czas temu pijany obywatel został zatrzymany po próbie bójki z strażnikiem na ulicach."; 
				link.l14.go = "NightAdventure_CitizenHomie";
			}
			
			if(CheckAttribute(pchar,"GenQuest.NightAdventureToPrisoner"))
			{
				link.l14 = "Oficerze, rozmawiałem z wartownikiem, i wycofał swoje roszczenia. Oto od niego pokwitowanie."; 
				link.l14.go = "NightAdventure_HomieToPrisoner";
			}
			// <-- приключенец
			NextDiag.TempNode = "First_officer";
		break;
		
		// --> Jason Похититель
		case "Marginpassenger":
			dialog.text = "Tak? Co jesteś gotowy mi powiedzieć?";
			link.l1 = "Ostatnio, zostałem zatrzymany na ulicy przez "+pchar.GenQuest.Marginpassenger.Name+" kto zaproponował mi zorganizowanie brudnego czynu: porwanie, a potem wykupienie osoby o imieniu "+pchar.GenQuest.Marginpassenger.q1Name+". To jest "+pchar.GenQuest.Marginpassenger.Text+"...";
			link.l1.go = "Marginpassenger_1";
		break;
		
		case "Marginpassenger_1":
			dialog.text = "Hmm... To bardzo intrygujące - proszę, kontynuuj!";
			link.l1 = "On znał nazwę statku, na którym "+pchar.GenQuest.Marginpassenger.q1Name+" planował wypłynąć. To jest "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType),"Imię")))+" nazywany '"+pchar.GenQuest.Marginpassenger.ShipName+"'. Również powiedział mi o czasie, kiedy ten statek miał wypłynąć.";
			link.l1.go = "Marginpassenger_2";
		break;
	
		case "Marginpassenger_2":
			dialog.text = "I zasugerował ci, żebyś porwał pasażera, a potem żądał za niego okupu?";
			link.l1 = "Dokładnie. Aby zebrać okup, poszedłbym do "+XI_ConvertString("Kolonia"+pchar.GenQuest.Marginpassenger.Targetcity)+", do pewnej osoby o imieniu "+pchar.GenQuest.Marginpassenger.q2Name+". Zapłaciłem mu za te informacje, ale oczywiście, nie zamierzałem porywać tej osoby.";
			link.l1.go = "Marginpassenger_3";
		break;
		
		case "Marginpassenger_3":
			dialog.text = "Więc zdecydowałeś się przyjść do mnie i dać mi znać?";
			link.l1 = "Dokładnie. Jestem pewien, że działania tego łotrzyka zagrażają obywatelom twojego miasta, i mam nadzieję, że podjąłeś odpowiednie środki.";
			link.l1.go = "Marginpassenger_4";
		break;
		
		case "Marginpassenger_4":
			dialog.text = "Miałeś całkowitą rację, kiedy przyszedłeś do mnie, "+GetAddress_Form(NPChar)+"! Ten łajdak, "+pchar.GenQuest.Marginpassenger.Name+", od dawna jest pod naszym nadzorem. Przeprowadzę śledztwo, a jeśli wszystko, co powiedziałeś, zostanie potwierdzone, wrzucimy tego łotra za kratki na pół roku. To go nauczy, aby nie knuł takich schematów przeciwko szanowanym obywatelom!\nNo cóż, za twoją szczerość i gotowość do służenia dobrej sprawie, na pewno zgłoszę o twoim czynie naszemu gubernatorowi, co oczywiście wpłynie na jego stosunek do ciebie... wiesz, w pozytywny sposób. Dzięki za pomoc, kapitanie!";
			link.l1 = "Hmm... Proszę, to była przyjemność pomóc. Do widzenia!";
			link.l1.go = "Marginpassenger_5";
		break;
		
		case "Marginpassenger_5":
			DialogExit();
			NextDiag.CurrentNode = "First_officer";
			AddQuestRecord("Marginpassenger", "20");
			AddQuestUserData("Marginpassenger", "sName", pchar.GenQuest.Marginpassenger.Name);
			CloseQuestHeader("Marginpassenger");
			pchar.quest.Marginpassenger_InWorld.over = "yes"; //снять таймер
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 5);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			ChangeContrabandRelation(pchar, -25);
			if (GetCharacterIndex("MarginCap") != -1)
			{
				sld = characterFromId("MarginCap");
				sld.lifeday = 0;
				Map_ReleaseQuestEncounter(sld.id);
				Group_DeleteGroup("Sea_MarginCap1");
			}
		break;
		//<-- Похититель

		case "EncGirl_1":
			dialog.text = "Słucham uważnie.";
			link.l1 = "Przywiózłem twojego zbiega.";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "Och, kapitanie, bardzo dziękuję! Jak ona się ma? Czy jest ranna? Dlaczego uciekła? Dlaczego?\nCzy ona nie rozumie? Pan młody jest bogatym i ważnym człowiekiem! Młodość jest naiwna i głupia... nawet okrutna. Pamiętaj o tym!";
			link.l1 = "Cóż, jesteś jej ojcem i ostateczna decyzja należy do ciebie, ale nie spieszyłbym się z tym ślubem...";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "Co ty wiesz? Czy masz swoje własne dzieci? Nie? Kiedy będziesz miał jedno, przyjdź do mnie, a porozmawiamy. \nObiecałem nagrodę każdemu, kto by ją zwrócił rodzinie.";
			link.l1 = "Dzięki. Powinieneś na nią uważać. Mam przeczucie, że na tym się nie zatrzyma.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;
		
		// ------------------------- Повод для спешки -----------------------------
		case "ReasonToFast_Prison1":
			pchar.questTemp.ReasonToFast.SpeakOther = true;
			dialog.text = "Słucham uważnie, kapitanie.";
			link.l1 = "Chcę Ci opowiedzieć o przestępczym zmowie między oficerem twojej załogi a piratami (wyjaśnia sprawę).";
			if(makeint(pchar.reputation.nobility) < 41)
			{
				link.l1.go = "ReasonToFast_Prison_BadRep";			
			}
			else
			{
				link.l1.go = "ReasonToFast_Prison_GoodRep";	
			}
		break;
		case "ReasonToFast_Prison_GoodRep":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 
				// вилка_А
				dialog.text = "Dziękuję,"+GetSexPhrase("panie","panna")+"! Natychmiast wydam rozkaz aresztowania łotra.\nJednakże poniosłeś koszty, a miejskie skarbce, niestety, są puste...";
				link.l1 = "Pan! Nie zrobiłem tego dla pieniędzy...";
				link.l1.go = "ReasonToFast_Prison_GoodRep_11";
				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = "Dziękuję Ci, "+GetSexPhrase("panie","panna")+"! Natychmiast wydam rozkaz aresztowania łotrzyka.\nPomyśl tylko! Chcieliśmy nagrodzić go osobistą bronią za doskonałe usługi. Jak dobrze, że wszystko się wyjaśniło, nie mam się czego wstydzić!";
				link.l1 = "Zawsze chętnie służę sprawiedliwości.";
				link.l1.go = "ReasonToFast_Prison_GoodRep_21";			
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = "Ja"+GetSexPhrase("rufa","ss")+"! Od jakiegoś czasu podejrzewaliśmy tego oficera i jego szemrane towarzystwo o brudne sprawy, ale myślę, że działałeś pochopnie, kiedy rozprawiłeś się z nimi bez świadków.";
				link.l1 = "Pan! Ale musiałem się bronić...";
				link.l1.go = "ReasonToFast_Prison_GoodRep_31";	
				pchar.questTemp.ReasonToFast.speakAfterPatrolDied = true;	
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";	
			}
		break;
		
		case "ReasonToFast_Prison_BadRep":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 
				// вилка_А
				dialog.text = "Kapitanie, zdajesz sobie sprawę z tego, co zrobiłeś?! Próbujemy zorganizować tę pułapkę przez ponad miesiąc! A teraz, tylko dla twojej rozrywki, zniszczyłeś spotkanie naszej patroli z posłańcem "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_GEN)+" a teraz przychodzisz tutaj, aby się chwalić?! Może teraz powiesz mi, jak mam wytłumaczyć wszystkie wydatki i koszty tej operacji?!";
				link.l1 = "Wasza łaska! Po prostu odmawiasz zrozumienia...";
				link.l1.go = "ReasonToFast_Prison_BadRep1";
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = "Pozwól mi spojrzeć na tę mapę...\nŻartujesz sobie ze mnie? Ten podarty kawałek pergaminu to dowód?";
				link.l1 = "Wasza Łaska! Po prostu odmawiasz zrozumienia...";
				link.l1.go = "ReasonToFast_Prison_BadRep1";
				TakeItemFromCharacter(pchar, "mapQuest");	
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_B";	
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = "To oryginalne usprawiedliwienie zniszczenia całej grupy patrolującej. Cóż, przynajmniej przychodząc tutaj, oszczędziłeś nam potrzeby szukania mordercy.";
				link.l1 = "Wasza łaska! Po prostu odmawiacie zrozumienia...";
				link.l1.go = "ReasonToFast_Prison_BadRep1";			
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}		
		break;
		
		case "ReasonToFast_Prison_GoodRep_11":
			dialog.text = "Nonetheless, I think that your efforts should still be rewarded. Here, take this map; it was found in the belongings of a pirate who has recently gone to the gallows. God willing, perhaps you will actually find that treasure, although I find it quite unlikely...";
			link.l1 = "Dziękuję, to bardzo hojne z twojej strony!";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "15");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, "mapQuest"); 
			arItem = ItemsFromID("mapQuest");
			ReasonToFast_GenerateTreasureMap(arItem);
			pchar.questTemp.ReasonToFast.state = "chain_A"; // вилка_А, наводки не генерим
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		case "ReasonToFast_Prison_GoodRep_21":
			dialog.text = "Twój zapał jest godny pochwały. Proszę, przyjmij ten miecz jako nagrodę - to najmniej, co mogę dla ciebie zrobić. Och, i możesz zatrzymać tę mapę dla siebie. Jestem pewien, że na Archipelagu jest wiele takich fałszywek.";
			link.l1 = "Dziękuję, to bardzo hojne z twojej strony!";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "14");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
			pchar.questTemp.ReasonToFast.state = "chain_B"; // была получена карта
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		case "ReasonToFast_Prison_GoodRep_31":
			dialog.text = "Może być, może być... Powiedzmy tylko, że ten interes został zadecydowany przez boską sprawiedliwość i wolę naszego Pana.";
			link.l1 = "Dziękuję, to bardzo hojne z twojej strony!";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			AddQuestRecord("ReasonToFast", "16");
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar,"ReasonToFast");			
		break;
		
		case "ReasonToFast_Prison_BadRep1":
			dialog.text = "Nie waż się mnie pouczać! Dla mnie jest oczywiste, że współpracujesz z tymi łotrzykami! Strażnicy, chwycić tego 'dobrodzieja'!";
			link.l1 = "Nie ma mowy!";
			link.l1.go = "fight";
			
			pchar.quest.ReasonToFast_ExitFromTown.win_condition.l1			= "EnterToSea";           	
            pchar.quest.ReasonToFast_ExitFromTown.function    				= "ReasonToFast_ExitFromTownFight";
			pchar.questTemp.ReasonToFast.canSpeakSailor = true;			
			pchar.TownEscape = true;
			Flag_PIRATE();
		break;
		// ------------------------- Повод для спешки -----------------------------
		
		// -------------------------- Операция 'Галеон' ----------------------------
		case "CapComission_PrisonBad1":
			dialog.text = "A jakie masz z nim interesy?";
			link.l1 = "Mam kilka prywatnych spraw do omówienia.";
			link.l1.go = "CapComission_PrisonBad2";
		break;
		
		case "CapComission_PrisonBad2":
			dialog.text = "Kapitanie, mam bezpośredni rozkaz aresztować i wysłać do rezydencji każdego, kto pyta o "+pchar.GenQuest.CaptainComission.Name+"do dalszych przesłuchań.";
			link.l1 = "Fajne miejsce tu masz! Aresztowani sami idą do ciebie, żeby się poddać!";
			link.l1.go = "CapComission_PrisonBad3";
		break;
		
		case "CapComission_PrisonBad3":
			dialog.text = "I mimo to prosiłbym, abyście złożyli swoje bronie!";
			link.l1 = "Spadaj! Odbierz to ode mnie siłą, jeśli możesz!";
			link.l1.go = "fight";
			CaptainComission_GenerateCaptainInPrison(); // данила . на всякий случай ,чтобы сгенерился нормально.
			AddDialogExitQuest("CaptainComission_GenerateCapJail");
		break;
		
		case "CapComission_PrisonGood1":
			dialog.text = "Tak, oczywiście. Mam rozkazy od gubernatora, aby udzielić ci pomocy w tej sprawie. Możesz teraz odwiedzić więźnia.";
			link.l1 = "Dziękuję...";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			AddDialogExitQuest("CaptainComission_GenerateCapJail");
		break;
		
		case "CapComission_PrisonFree1":
		if(CheckAttribute(pchar,"GenQuest.CaptainComission"))// лесник . разделение диалога если кеп убит или нет
		{
			dialog.text = "Ehm, kapitanie, nie mam uprawnień, aby zwolnić tego więźnia. Musisz poprosić o pozwolenie gubernatora.";
			link.l1 = "Oficerze, działam dla dobra śledztwa. Więzień zgodził się współpracować z władzami i ujawnić skrytkę. Czas ma kluczowe znaczenie - przemytnicy mogą znaleźć cenny ładunek, a potem będzie on stracony dla ludności.";
			link.l1.go = "CapComission_PrisonFree2";
		}
         else
		 {
         	dialog.text = "Nie powinieneś go zabić, kapitanie... To dla mnie nie ma znaczenia. Musimy cię zamiast niego stracić. Strażnicy! Złapcie go!";
            link.l2 = "Wybrałeś niewłaściwego gościa, z którym chcesz się pieprzyć!...";
             link.l2.go = "fight";
			 NextDiag.TempNode = "First_officer";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			AddDialogExitQuest("OpenTheDoors");
		 }			 
		break;
		
		case "CapComission_PrisonFree2":
			dialog.text = "Ale mogę mu przydzielić eskortę.";
			link.l1 = "Nie ma potrzeby - mam wystarczająco dużo straży. Poza tym, nie chciałbym, aby lokalizacja kryjówki stała się publiczna.";
			link.l1.go = "CapComission_PrisonFree3";
		break;
		
		case "CapComission_PrisonFree3":
			dialog.text = "Hmm... no cóż. Ale za niego odpowiesz swoją głową.";
			link.l1 = "Oczywiście.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First_officer";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			AddDialogExitQuest("OpenTheDoors");
		break;
		// -------------------------- Операция 'Галеон' ----------------------------
		
		case "F_ShipLetters_1":
			dialog.text = "Mów teraz, słucham.";
			link.l1 = "Mam ze sobą dokumentację statku. Jej właściciel musiał ją zgubić, a myślę, że mogłaby cię zainteresować.";
			link.l1.go = "F_ShipLetters_2";
			pchar.questTemp.different.GiveShipLetters.speakFort = true;
		break;
		
		case "F_ShipLetters_2":			
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Bzdury! Nie rozpraszaj mnie od mojej pracy! Idź do władz portowych, jeśli ci na tym zależy!";
				link.l1 = "No cóż, dzięki, chyba...";
				link.l1.go = "exit";
			}
			else
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					dialog.text = "Tak, to lokalny właściciel. Być może, nagroda wyniesie "+sti(pchar.questTemp.different.GiveShipLetters.price2)+" pesos posłużą jako adekwatna nagroda za twoją czujność, kapitanie.";
					link.l1 = "Być może nie.";
					link.l1.go = "F_ShipLetters_3";	
					link.l2 = "Hojne propozycja. Dokumenty są więc twoje!";
					link.l2.go = "F_ShipLetters_4";
				}
				else
				{
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
					{
						dialog.text = "O, teraz to jest naprawdę interesujące! Wierzę, że miejska skarbnica chętnie ci zapłaci "+sti(pchar.questTemp.different.GiveShipLetters.price4)+" pesos za twój wkład w walkę z nielegalnym handlem.";
						link.l1 = "Być może nie.";
						link.l1.go = "F_ShipLetters_3";
						link.l2 = "Hojne propozycję. Dokumenty są twoje, więc!";
						link.l2.go = "F_ShipLetters_4";
					}
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
					{
						dialog.text = "O Panie! Co za szczęście, że przyszedłeś do mnie. Przypuszczam, że mój nieszczęsny kolega chętnie ci zapłaci "+sti(pchar.questTemp.different.GiveShipLetters.price3)+" pesos, aby uniknąć rozgłosu wokół tej sprawy.";
						link.l1 = "Być może nie.";
						link.l1.go = "F_ShipLetters_3";
						link.l2 = "Oferta hojna. Dokumenty są więc twoje!";
						link.l2.go = "F_ShipLetters_4";
					}
				}
			}
		break;
		
		case "F_ShipLetters_3":
			dialog.text = "To moje miasto, kapitanie.";
			link.l1 = "Pamiętam o tym.";
			link.l1.go = "exit";
		break;
		
		case "F_ShipLetters_4":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price4)); 
				}
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price3)); 
				}
			}
						
			if((sti(pchar.questTemp.different.GiveShipLetters.variant) == 0) || (sti(pchar.questTemp.different.GiveShipLetters.variant) == 2))
			{	
				ChangeCharacterComplexReputation(pchar,"nobility", -1); 
				OfficersReaction("bad"); 
			}	
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "8");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		
        case "ForGoodMove":
			//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				dialog.text = "Oczywiście, możesz zobaczyć wszystko - tu mam całkowity porządek!";
				link.l1 = "Cóż, sprawdźmy to, poruczniku.";
				link.l1.go = "exit";
				pchar.questTemp.jailCanMove = true;
				break;
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "Oczywiście, Wasza Ekscelencjo. Możecie przejść.";
				link.l1 = "Dziękuję Ci, oficerze.";
				link.l1.go = "exit";
				pchar.questTemp.jailCanMove = true;
				break;
			}
			// Офицер с патентом
			if(IsOfficerFullEquip() && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "Cóż, nie widzę powodu, aby ci odmówić - przecież jesteś kapitanem statku w służbie "+NationNameGenitive(sti(npchar.nation))+". Wejdź do środka."; 
				link.l1 = "Dziękuję oficerze.";
				link.l1.go = "exit";
				pchar.questTemp.jailCanMove = true;
				break;
			}
			// <-- legendary edition
			dialog.text = NPCStringReactionRepeat("Ale po co ci to? Uwierz mi, nie ma tam niczego ciekawego, oprócz złodziei i bandytów.","Już rozmawialiśmy o tym twoim życzeniu.","Znowu? Już dwukrotnie o tym rozmawialiśmy!","Hmm, znowu...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Mimo to, chciałbym dołączyć do twojej wycieczki po kazamatach. Jestem bardzo zainteresowany!","Tak, dokładnie. Ale chciałem o tym porozmawiać.","Cóż, może za trzecim razem...","Mam nadzieję, że twoi więźniowie mnie nie opuszczą.",npchar,Dialog.CurrentNode);
			link.l1.go = "ForGoodMove_1";
		break;
		
        case "ForGoodMove_1":
			pchar.questTemp.jailCanMove.money = 20+hrand(3)*10;
			if (sti(colonies[FindColony(npchar.city)].jail))
			{
				dialog.text = "Cóż, nie widzę powodu, aby odmówić. "+FindRussianDublonString(sti(pchar.questTemp.jailCanMove.money))+" - aż do momentu, kiedy opuścisz więzienie, możesz swobodnie chodzić po korytarzach i nawet rozmawiać z więźniami.";
				if (PCharDublonsTotal() >= sti(sti(pchar.questTemp.jailCanMove.money)))
				{
					link.l1 = "Zgadzam się, oto twoje monety!";
					link.l1.go = "ForGoodMove_agree";
				}
				link.l2 = "To nie zadziała. To zbyt wiele dla bezcelowego błądzenia po korytarzach.";
				link.l2.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple("Nie, to jest surowo zabronione przez regulamin. Co? Myślisz, że mamy tu cyrk? Spadaj i nie odwracaj mnie od moich obowiązków.","Nie mogę pozwolić obcym osobom chodzić po moim więzieniu. Proszę, przestań mi przeszkadzać!");
				link.l1 = "Dobrze, jak mówisz...";
				link.l1.go = "exit";
			}
		break;
		
        case "ForGoodMove_agree":
            dialog.text = "Dobrze, możesz teraz rozpocząć swoją wycieczkę...";
			link.l1 = "Dziękuję, oficerze.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			RemoveDublonsFromPCharTotal(sti(pchar.questTemp.jailCanMove.money)));
		break;
		
        case "KnowAboutPrisoner":
			switch (pchar.questTemp.jailCanMove.ownerPrison)
			{
				case "0": sTemp = "For murder."; break;
				case "1": sTemp = "He is accused of piracy."; break;
				case "2": sTemp = "For banditry and robbery."; break;
				case "3": sTemp = "He was caught stealing."; break;
				case "4": sTemp = "For petty theft."; break;
				case "5": sTemp = "For cheating."; break;
				case "6": sTemp = "For vagrancy and begging."; break;
			}
			dialog.text = sTemp;
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				link.l1 = "Rozumiem... Oddaj mi go, oficerze, a potem sam zdecyduję o losie tego więźnia.";
				link.l1.go = "KnowAboutPrisoner_gengov";
			DeleteAttribute(pchar, "questTemp.jailCanMove.City");
		break;
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				link.l1 = "Rozumiem... Wydać mi go, oficerze, a potem sam zdecyduję o losie tego więźnia.";
				link.l1.go = "KnowAboutPrisoner_admiral";
				DeleteAttribute(pchar, "questTemp.jailCanMove.City");
				break;
			}
			link.l1 = "Rozumiem... A czy istnieje możliwość wykupu, kaucji... czy w jakiś inny sposób uwolnienia go?";
			link.l1.go = "KnowAboutPrisoner_" + pchar.questTemp.jailCanMove.ownerPrison;
			DeleteAttribute(pchar, "questTemp.jailCanMove.City");
		break;
		
        case "KnowAboutPrisoner_0":
			dialog.text = "Oczywiście, że nie. Ten łotr iście piekielny od razu pójdzie prosto do piekła. Gubernator ma jego sprawę pod specjalnym nadzorem!";
			link.l1 = "Heh, widzę...";
			link.l1.go = "notFree_exit";
		break;	
		
		case "KnowAboutPrisoner_1":
			dialog.text = "Czy żartujesz? On musiał pójść na szubienicę dawno temu! Na pewno wkrótce poślubi linę. Tylko o tym zapomnij.";
			link.l1 = "Zrozumiałem. I już zapomniałem...";
			link.l1.go = "notFree_exit";
		break;
		
        case "KnowAboutPrisoner_2":
			dialog.text = "Nie sądzę. Spowodował wiele kłopotów naszym mieszkańcom. Więc nie pytaj o to.";
			link.l1 = "Hmm, rozumiem.";
			link.l1.go = "notFree_exit";
		break;
		
        case "KnowAboutPrisoner_3":
			dialog.text = "Pewnie że nie. On jest złodziejem, a złodziej musi siedzieć w więzieniu.";
			link.l1 = "Oh! Dobrze powiedziane, poruczniku!";
			link.l1.go = "notFree_exit";
		break;
		
        case "KnowAboutPrisoner_4":
			dialog.text = "Naprawdę nie wiem. Ukradł tylko drobnostkę. Nie mogę go uwolnić, ale pozostawienie go na zgniliznę w więzieniu z pewnością nie jest słuszne.";
			link.l1 = "Cóż, to daj mi go, poruczniku. Zapłacę za niego kaucję - oczywiście, rozsądną sumę.";
			link.l1.go = "KnowAboutPrisoner_free";
		break;
		
        case "KnowAboutPrisoner_5":
			dialog.text = "Zwolnienie? To wydaje się prawdopodobne. Moim zdaniem, nie ma sensu zatrzymywać tego drobnego przestępcy tutaj.";
			link.l1 = "Cóż, to daj mi go, poruczniku. Zapłacę za niego kaucję - oczywiście, rozsądną sumę.";
			link.l1.go = "KnowAboutPrisoner_free";
		break;
		
		case "KnowAboutPrisoner_6":
			dialog.text = "Hmm... Jest sens w twoich słowach. Ten włóczęga tu nie pasuje - tylko szerzy brud i choroby...";
			link.l1 = "Cóż, to daj mi go, poruczniku. Zapłacę za niego kaucję - oczywiście, rozsądną sumę.";
			link.l1.go = "KnowAboutPrisoner_free";
		break;
		
        case "KnowAboutPrisoner_free":
			pchar.questTemp.jailCanMove.ownerPrison.money = 50+hrand(10)*10;
			dialog.text = "Dobrze, mamy umowę. "+FindRussianDublonString(sti(pchar.questTemp.jailCanMove.ownerPrison.money))+" na miejscu, i możesz go od razu zabrać.";
			if (PCharDublonsTotal() >= sti(pchar.questTemp.jailCanMove.ownerPrison.money))
			{
				link.l1 = LinkRandPhrase("Świetnie! Zgadzam się!","Masz umowę, oficerze!","Doskonale. Jestem gotowy zapłacić ten składkę.");
				link.l1.go = "KnowAboutPrisoner_agree";
			}
			link.l2 = "Nie, to jest zbyt drogie. Myślę, że podziękuję.";
			link.l2.go = "KnowAboutPrisoner_exit";
		break;
		
        case "KnowAboutPrisoner_agree":
			dialog.text = "Dobrze, możesz iść do jego celi i zabrać tego łobuza ze sobą.";
			link.l1 = "Dzięki.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			RemoveDublonsFromPCharTotal(sti(pchar.questTemp.jailCanMove.ownerPrison.money));
			Log_Info("You have given " + FindRussianDublonString(sti(pchar.questTemp.jailCanMove.ownerPrison.money)) + "");
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId)
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_canMove";
		break;
		
        case "KnowAboutPrisoner_exit":
			dialog.text = "No cóż, to twój wybór. Nie dam ci kolejnej szansy...";
			link.l1 = "Nie ma potrzeby.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId);
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_expansive";
		break;
		
        case "notFree_exit":
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId);
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_notFree";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		// belamour legendary edition -->
		// генерал-губернатор
		case "KnowAboutPrisoner_gengov":
			dialog.text = "Oczywiście, Wasza Ekscelencjo, jeśli tak pragniesz, weź tego nieszczęśnika. Jednak bądź ostrożny, nadal jest przestępcą...";
			link.l1 = "To świetnie. Nie martw się poruczniku, wiem co robię.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId)
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_canMove";
		break;
		// вице-адмирал
		case "KnowAboutPrisoner_admiral":
			dialog.text = "Cóż... Nawet nie wiem... Właściwie, nie mogę po prostu puścić więźniów. Ale jesteś nadal wiceadmirałem, więc prawdopodobnie masz prawo zabrać tego przestępcę.";
			link.l1 = "To jest wspaniałe. Nie martw się poruczniku, wiem co robię.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId)
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_canMove";
		break;
		// <-- legendary edition
		//---------------- Протектор ------------------
        case "First_protector":
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				dialog.text = "Gubernatorze Generale, Wasza Ekscelencjo! Wejdź, ale bądź ostrożny: możesz się spodziewać wszystkiego od tych przestępców...";
				link.l1 = "Nie martw się, żołnierzu, poradzę sobie, jeśli coś się stanie.";
				link.l1.go = "exit";
				NextDiag.TempNode = "First_protector";
				break;
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "Witaj, Wiceadmirał! Pełnię tu służbę: dbam o to, aby nikt nie wchodził ani nie wychodził bez pozwolenia. Ale ty, oczywiście, masz prawo swobodnie tu przechodzić.";
				link.l1 = "Cóż, to wspaniałe.";
				link.l1.go = "exit";
				NextDiag.TempNode = "First_protector";
				break;
			}
			if (sti(pchar.questTemp.jailCanMove))
			{
				dialog.text = RandPhraseSimple("Możesz przejść, strażnik dał swoją zgodę.","Otrzymałem rozkaz od strażnika więzienia. Możesz przechodzić swobodnie.");
				link.l1 = "Bardzo dobrze.";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison.money");
			}
			else
			{
				dialog.text = RandPhraseSimple("Nie możesz iść dalej bez konkretnego pozwolenia od strażnika więzienia!","Odpowiadam tylko strażnikowi więziennemu! Jeśli spróbujesz iść dalej bez jego pozwolenia, jesteś skończony!");
				link.l1 = RandPhraseSimple("Widzę","W porządku")+", żołnierzu.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First_protector";
		break;
		//---------------- Солдаты ------------------
        case "First_soldier":
            dialog.text = RandPhraseSimple("Jestem na służbie, nie przeszkadzaj mi.","Idź dalej, nie wolno mi z tobą rozmawiać.");
			link.l1 = "Dobrze, żołnierzu.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First_soldier";
		break;
		//---------------- Заключенные ------------------
        case "First_prisoner": 
			if (GetNationRelation2MainCharacter(sti(npchar.nation)) == RELATION_ENEMY)
			{
				dialog.text = LinkRandPhrase("Ho-ho, czy to nie jest wspaniały czas!","Potnij ich, "+GetSexPhrase("kumpel","dziewczyno")+", kroić!!!","O, cholera! Straciłem wszelką nadzieję na zobaczenie trupa mojego strażnika!");
				link.l1 = RandPhraseSimple("Heh!","Arrgh!");
				link.l1.go = "NoMoreTalkExit";
				if (rand(10) > 6 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && !CheckAttribute(pchar, "GenQuest.PrisonQuestLock") && !CheckAttribute(pchar, "quest.GivePrisonFree") && !CheckAttribute(pchar, "quest.GivePrisonFree_Over") && !CheckAttribute(pchar, "quest.DeliverToBander")) // Addon 2016-1 Jason пиратская линейка
				{
					dialog.text = RandPhraseSimple("Poczekaj, "+GetSexPhrase("kumplu","dziewczyna")+"!! Uwolnij mnie!","Słuchaj, "+GetSexPhrase("kumple","dziewczyno")+", uprzejmie otwórz celę.");
					link.l1 = "Z jakiego powodu?";
					link.l1.go = "Prisoner_1"; // на квест освобождения заключённого
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("Jestem oskarżony o rabunek, ale jestem niewinny!","Arrgh, ty wytworny szumowino... Chciałbyś trochę posiedzieć w mojej celi?! Kheh-heh-heh...","Nie jestem winny!");
				link.l1 = RandPhraseSimple("Zamknij się!","Nie obchodzi mnie ciebie...");
				link.l1.go = "NoMoreTalkExit";
				if (rand(10) > 6 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && !CheckAttribute(pchar, "GenQuest.PrisonQuestLock") && !CheckAttribute(pchar, "quest.GivePrisonFree_Over") && !CheckAttribute(pchar, "quest.GivePrisonFree") && !CheckAttribute(pchar, "quest.DeliverToBander") && !sti(colonies[FindColony(npchar.city)].HeroOwn)) // Addon 2016-1 Jason пиратская линейка
				{
					dialog.text = RandPhraseSimple("Zaczekaj, "+GetSexPhrase("kumpel","dziewczyno")+", nie podchodź tak szybko!","Nie spiesz się, "+GetSexPhrase("kumpel","dziewczyno")+", porozmawiajmy.");
					link.l1 = "Z jakiego powodu?";
					if (rand(1))
					{
						link.l1.go = "Prisoner_1"; // на квест освобождения заключённого
					}
					else
					{
						link.l1.go = "Deliver_1"; // на квест передачу весточки
					}
				}
			}
		break;
		// -------------------- освобождение заключённого --------------------
        case "Prisoner_1":
            dialog.text = "Słuchaj mnie, kumplu. Nie myśl, że nie wyglądam dobrze i tak dalej. Po prostu muszę stąd wyjść...";
			link.l1 = "Co?!";
			link.l1.go = "Prisoner_2";
			GetChestPlaceName();
			pchar.questTemp.jailCanMove.prisonerId = npchar.id; //запомним Id
			pchar.questTemp.jailCanMove.IsTrue = rand(4); //вид клада
			pchar.questTemp.jailCanMove.Item1 = GenQuestPrison_GenerateArtefact();
			pchar.questTemp.jailCanMove.Item2 = GenQuestPrison_GenerateBlade();
			pchar.questTemp.jailCanMove.Name = GetFullName(npchar); //имя перца
			npchar.nation = PIRATE;
		break;
        case "Prisoner_2":
            dialog.text = "Co usłyszałeś! Pomóż mi, a będę mógł zwrócić...";
			link.l1 = "Teraz to jest interesujące. Kim jesteś i co możesz mi zaoferować?";
			link.l1.go = "Prisoner_3";
		break;
        case "Prisoner_3":
            dialog.text = "Mam na imię "+GetFullName(npchar)+". Mam kilka rzeczy schowanych w bezpiecznym miejscu. Po prostu wyciągnij mnie stąd i zabierz do "+XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Acc")+". Tam, w grocie, mam skarb. Pójdziemy go zabrać i podzielimy!";
			link.l1 = "A co masz w swoim kryjówku? I jak mogę wiedzieć, że mówisz prawdę?";
			link.l1.go = "Prisoner_4";
		break;
        case "Prisoner_4":
            dialog.text = "Przysięgam, że mówię prawdę! Co do skrytki - jest tam skarb i pieniądze...";
			link.l1 = "Nie, kolego. Nie ryzykuję mojej skóry dla wątpliwego skrytki. Przykro mi...";
			link.l1.go = "Prisoner_5";
			if (GetNationRelation2MainCharacter(sti(npchar.nation)) != RELATION_ENEMY)
			{			
				// belamour legendary edition адмирал и губернатор может договориться без денег
				bool bAdmiral = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation);
				bool bGenGov = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == GetBaseHeroNation());
				if(!bAdmiral && !bGenGov)
				{
				link.l2 = "Cóż, może warto podjąć ryzyko... Proponuję następujące: Mogę wyeliminować strażników w więzieniu i zabrać cię na mój statek. Jeśli wszystko pójdzie dobrze, chcę, abyś był cały czas przy mnie, dopóki nie dotrzemy do grotu na  "+XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc")+". Umowa?"; // belamour gen
				link.l2.go = "Prisoner_agree"; //силовой способ вызволения
				}
				link.l3 = "Dobrze, spróbuję ci pomóc. Porozmawiam z naczelnikiem więzienia. Być może uda mi się wykupić cię na wolność.";
				link.l3.go = "ToPrisonHead_agree"; //мирный способ вызволения
			}
			else
			{
				link.l2 = "Dobrze, uwierzę ci i otworzę twoją celę. Chcę, abyś był cały czas przy mnie, aż dotrzemy do groty na "+XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc")+". Umowa?";
				link.l2.go = "Prisoner_agree_3"; //силовой способ вызволения, когда тюремщики убиты
			}
		break;
        case "Prisoner_5":
            dialog.text = RandPhraseSimple("Przeklęty bądź, łotrzyku!","Przeklęty draniu, oszukałeś mnie...");
			link.l1 = RandPhraseSimple("I wszystkiego najlepszego dla ciebie także. Do widzenia...","Księżyc nie potrzebuje szczekania psów...");
			link.l1.go = "NoMoreTalkExit";
		break;
        case "Prisoner_agree":
            dialog.text = "Dobrze. Nie jestem w pozycji, aby być wybredny.";
			link.l1 = "Dobrze. Teraz otworzę twój zamek, żeby cię wypuścić, a potem przedzieramy się. Jesteś gotowy?";
			link.l1.go = "Prisoner_agree_1";
		break;
        case "Prisoner_agree_1":
            dialog.text = "Tak, "+GetSexPhrase("kumpel","dziewczyna")+", Jestem gotowy!";
			link.l1 = "No więc do dzieła!";
			link.l1.go = "Prisoner_agree_2";
		break;
        case "Prisoner_agree_2":
			string slai_group = GetNationNameByType(sti(npchar.nation))  + "_citizens";
			LAi_group_AttackGroup(slai_group, LAI_GROUP_PLAYER);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
            AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			Pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			Pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			Pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";			
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			//LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

        case "Prisoner_agree_3":
            dialog.text = "Dobrze. Nie jestem w pozycji, żeby być wybrednym.";
			link.l1 = "Dobrze. Śledź mnie tak szybko, jak możesz - musimy jeszcze dotrzeć do mojego statku. Nie zwlekaj!";
			link.l1.go = "Prisoner_agree_4";
		break;
        case "Prisoner_agree_4":
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
            AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			Pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			Pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			Pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			//LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;

        case "ToPrisonHead_agree":
            dialog.text = "No cóż, możesz spróbować. Mam nadzieję, że nam się uda! Ale nie marnuj czasu - za kilka dni stąd wyjadę...";
			link.l1 = "Poczekaj tutaj, załatwię wszystko.";
			link.l1.go = "NoMoreTalkExit";
			pchar.questTemp.jailCanMove.City = npchar.City; //город
			pchar.questTemp.jailCanMove.ownerPrison = rand(6); //характер преступления
			SetTimerCondition("GivePrisonFree_Over", 0, 0, 2, false);
			AddQuestRecord("GivePrisonFree", "5");
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("",""));
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
		break;

        case "ToPrisonHead_canMove":
            dialog.text = "No cóż, co na to powiesz, "+GetSexPhrase("kumpel","dziewczyna")+"?";
			link.l1 = "Wszystko zostało załatwione, i mogę cię stąd zabrać.";
			link.l1.go = "ToPrisonHead_canMove_1";
		break;
        case "ToPrisonHead_canMove_1":
            dialog.text = "Wtedy wyjdźmy stąd! Och, Panie, jak ja jestem szczęśliwy!";
			link.l1 = "Podsumujmy. Chcę, żebyś cały czas był przy mnie, dopóki nie dotrzemy do groty na "+XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"To")+", nie zostaniesz dalej niż o krok. Tak na wszelki wypadek. Czy zgadzasz się?";
			link.l1.go = "ToPrisonHead_canMove_2";
		break;
        case "ToPrisonHead_canMove_2":
            dialog.text = "Oczywiście, zgadzam się! Tym bardziej, że nie jestem w stanie wybierać.";
			link.l1 = "Wtedy jesteś wolny.";
			link.l1.go = "ToPrisonHead_canMove_exit";
		break;
        case "ToPrisonHead_canMove_exit":
			pchar.quest.GivePrisonFree_Over.over = "yes";
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
            AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			Pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			Pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			Pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";			
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			//LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;

        case "ToPrisonHead_notFree":
			switch (pchar.questTemp.jailCanMove.ownerPrison)
			{
				case "0": sTemp = "murder"; break;
				case "1": sTemp = "piracy"; break;
				case "2": sTemp = "brigandry"; break;
				case "3": sTemp = "thievery"; break;
			}
            dialog.text = "No cóż, co odpowiesz, "+GetSexPhrase("kumpel","dziewczyno")+"?";
			link.l1 = "Nie mogłem załatwić twojego zwolnienia. Jestes oskarżony o "+sTemp+", więc nie możesz być wykupiony.";
			link.l1.go = "ToPrisonHead_notFree_1";
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
		break;
		
        case "ToPrisonHead_notFree_1":
            dialog.text = "Ale ja zostałem oczerniony! O, diabli! I co teraz zrobię? Zgniję tu na żywo!";
			link.l1 = "Przykro mi, kolego, ale nic nie mogę dla ciebie zrobić.";
			link.l1.go = "ToPrisonHead_notFree_2";
			link.l2 = "Pozostaje tylko jedna szansa - uwolnić cię siłą. Teraz złamię twój zamek, żeby cię wyciągnąć, a potem przebijemy się. Jesteś gotowy?";
			link.l2.go = "Prisoner_agree_1";
			pchar.quest.GivePrisonFree_Over.over = "yes";
		break;
		
        case "ToPrisonHead_notFree_2":
            dialog.text = RandPhraseSimple("Przeklęty ty!","Przeklęta suko, okradłaś mnie...");
			link.l1 = "I wszystkiego najlepszego dla ciebie też. Do widzenia...";
			link.l1.go = "NoMoreTalkExit";
			AddQuestRecord("GivePrisonFree", "7");
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			DeleteAttribute(pchar, "questTemp.jailCanMove.islandId");	
			DeleteAttribute(pchar, "questTemp.jailCanMove.placeId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.prisonerId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.IsTrue");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Sum");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Name");
		break;

        case "ToPrisonHead_expansive":
			dialog.text = "Czy są jakieś dobre wiadomości, "+GetSexPhrase("kumpel","dziewczyno")+"?";
			link.l1 = "Kaucja za twoje zwolnienie jest zbyt wysoka, nie mam takich pieniędzy. Muszę przestać ci pomagać.";
			link.l1.go = "ToPrisonHead_notFree_2";
			pchar.quest.GivePrisonFree_Over.over = "yes";
		break;
		//==> в месте, где клад припрятан
        case "PrisonerInPlace":
			switch (sti(pchar.questTemp.jailCanMove.IsTrue))
			{
				case 0:
					dialog.text = "Słuchaj, sprawdziłem wszystko, ale nie znalazłem skarbu. Szkoda, że tak się to skończyło. Ktoś musiał go wykopać przed nami.";
					link.l1 = "A jak to może być?!";
					link.l1.go = "PrisonerInPlace_1";
				break;
				case 1:
					dialog.text = "Znalazłem to! Skarb jest nadal tam, gdzie go zostawiłem.";
					link.l1 = "Doskonale. No to, rozejść się?";
					link.l1.go = "Node_1";
				break;
				case 2:
					dialog.text = "Cóż, oto on, mój skład. Niewiele, ale to wszystko, co mam. Zgodnie z umową, połowa jest twoja.";
					link.l1 = "Tak, skarb jest skromny, rzeczywiście. Cóż, nadal lepiej niż nic.";
					link.l1.go = "Node_2";
				break;
				case 3:
					dialog.text = "Kapitanie, przykro mi, ale... Nie ma żadnego skarbu.";
					link.l1 = "Co?! Oszukałeś mnie, łotrzyku! Zabrałem cię na tę wyspę - i po co? Nie ujdzie ci to na sucho!";
					link.l1.go = "Node_3";
				break;
				case 4:
                    ok = GetCharacterItem(pchar, "map_full") == 0 && GetCharacterItem(PChar, "map_part2") == 0;
                    if(GetCharacterItem(PChar, "map_part1") > 0 && !ok) // Первая половинка есть, но вторую дать нельзя
                    {
                        dialog.text = "Słuchaj, sprawdziłem wszystko, ale nie znalazłem skarbu. Szkoda, że tak się to skończyło. Ktoś musiał go wykopać przed nami.";
                        link.l1 = "A jak to może być?!";
                        link.l1.go = "PrisonerInPlace_1";
                    }
                    else
                    {
                        dialog.text = "Cholera... Jak to możliwe? To nie może być prawda!";
                        link.l1 = "Co u ciebie, kumplu? Gdzie jest skarb? Nie mów mi, że go nie ma!";
                        link.l1.go = "Node_4";
                    }
				break;
			}
		break;
			
		case "Node_1":
			dialog.text = "Oczywiście, zgodnie z umową. Połowa skarbu jest twoja.";
			link.l1 = "Święty Panie, na pewno jest tu dużo cennych rzeczy!";
			link.l1.go = "PrisonerInPlace_3";
			Log_Info("You have received your share of the treasure");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "icollection", 1+hrand(1));
			TakeNItems(pchar, "chest", 4+hrand(4));
			TakeNItems(pchar, "jewelry1", 70+rand(15));
			TakeNItems(pchar, "jewelry2", 50+rand(15));
			TakeNItems(pchar, "jewelry3", 60+rand(15));
			TakeNItems(pchar, "jewelry4", 40+rand(10));
			TakeNItems(pchar, "jewelry5", 10+rand(10));
			TakeNItems(pchar, "jewelry46", 60+rand(20));
			TakeNItems(pchar, "jewelry47", 40+rand(15));
			TakeNItems(pchar, "jewelry40", 60+rand(20));
			AddQuestRecord("GivePrisonFree", "3_1");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
		case "Node_2":
			dialog.text = "Kapitanie, jest tam także ten indiański przedmiot wśród innych rzeczy. Możesz go mieć dodatkowo do swojego udziału.";
			link.l1 = "Cóż, przynajmniej coś wartościowego za twoje uwolnienie! Daj mi to.";
			link.l1.go = "PrisonerInPlace_3";
			Log_Info("You have received your share of the treasure");
			PlaySound("interface\important_item.wav");
			sTemp = pchar.questTemp.jailCanMove.Item1;
			TakeNItems(pchar, sTemp, 1);
			TakeNItems(pchar, "jewelry5", 40+rand(10));
			TakeNItems(pchar, "jewelry6", 20+rand(20));
			TakeNItems(pchar, "jewelry17", 80+rand(20));
			TakeNItems(pchar, "jewelry13", 10+rand(10));
			TakeNItems(pchar, "jewelry10", 20+rand(20));
			TakeNItems(pchar, "jewelry12", 50+rand(20));
			TakeNItems(pchar, "jewelry11", rand(2)+1);
			AddQuestRecord("GivePrisonFree", "3_2");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
		case "Node_3":
			dialog.text = "Poczekaj, Kapitanie, nie denerwuj się, pozwól mi powiedzieć. Jestem też żeglarzem, tak jak ty. Zostałem wtrącony do więzienia przez pomyłkę, przysięgam. Ty byłeś moją jedyną szansą na ucieczkę, musiałem cię okłamać na temat skarbu.\nNie ma żadnego skarbu, ale ukryłem tam jedną dobrą rzecz. Weź ją i pozwól mi odejść w spokoju. Być może pewnego dnia pomoże ci przetrwać bitwę.";
			link.l1 = "Dobrze, i tak nie spodziewałem się po tobie wiele. Dzięki Bogu, że nie żywię urazy.";
			link.l1.go = "PrisonerInPlace_3";
			Log_Info("You have received equipment");
			PlaySound("interface\important_item.wav");
			sTemp = pchar.questTemp.jailCanMove.Item2;
			TakeNItems(pchar, sTemp, 1);
			AddQuestRecord("GivePrisonFree", "3_3");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
		case "Node_4":
			dialog.text = "Nie!!! To nie tam! Przeklęty szmat... Kapitanie, byłem absolutnie pewien, że znajdę to tutaj! Ale, najwyraźniej, pomyliłem się! Coś na tym kawałku papieru było naprawdę niejasne...";
			link.l1 = "O nie... Jesteś w poważnych tarapatach, kumplu. Ale chciałbym jeszcze posłuchać twojego wyjaśnienia.";
			link.l1.go = "Node_4_1";
		break;
			
		case "Node_4_1":
			dialog.text = "Miałem kawałek mapy. To była prawdziwa mapa, przysięgam! Ale jest bardzo trudno powiedzieć, która wyspa była na niej pokazana... Myślałem, że to tutaj... Ale jak widzisz teraz, myliłem się.";
			link.l1 = "Jaki skrawek papieru? Daj mi go natychmiast!";
			link.l1.go = "Node_4_2";
		break;
			
		case "Node_4_2":
			AddMapPart();
			dialog.text = "Oczywiście, weź to. Kapitanie, uwolnij mnie... proszę? Naprawdę myślałem, że skarb tam jest. Być może, dowiesz się, gdzie jest, i weźmiesz go dla siebie. Błagam cię.";
			link.l1 = "Rozumiem... Rzeczywiście, trudno cokolwiek zrozumieć z tego szmatka. Potrzebna jest druga połowa mapy. Dobrze, znikaj. Widzę teraz, że to nie była twoja wina.";
			link.l1.go = "PrisonerInPlace_4";
		break;
			
		case "PrisonerInPlace_1":
			dialog.text = "Bardzo proste, "+GetSexPhrase("kumpel","dziewczyna")+". Wszystko w życiu się zdarza.\nNo, jesteś tutaj - jeśli chcesz: zostań, szukaj więcej. No, muszę iść!\nDo widzenia, "+GetSexPhrase("mój przyjacielu","dziewczyno")+", dziękuję za uratowanie mi życia. Zawsze cię zapamiętam!";
			link.l1 = "Łotrzyku! Myślisz, że pozwolę ci ujść z tym?! Hej! Zaczekaj, tchórze!";
			link.l1.go = "PrisonerInPlace_2";
			AddQuestRecord("GivePrisonFree", "4");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
        case "PrisonerInPlace_2":
			LAi_group_Delete("EnemyFight");
			DeleteAttribute(pchar, "questTemp.jailCanMove.islandId");	
			DeleteAttribute(pchar, "questTemp.jailCanMove.placeId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.prisonerId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.IsTrue");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Sum");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Name");
			chrDisableReloadToLocation = false;
			LAi_LocationDisableMonstersGen(pchar.location, false);
			npchar.lifeDay = 0;
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", -1);
			DialogExit();

            Pchar.quest.DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
            Pchar.quest.DeletePrisonGroup.win_condition.l1.location = pchar.location;
            Pchar.quest.DeletePrisonGroup.win_condition = "DeletePrisonGroup";
		break;
		
        case "PrisonerInPlace_3":
			dialog.text = "Proszę bardzo. Dziękuję!";
			link.l1 = "Pożegnanie...";
			link.l1.go = "PrisonerInPlace_2";
		break;
		
        case "PrisonerInPlace_4":
			dialog.text = "Dziękuję ci, kapitanie! Będę się za ciebie modlił do końca moich dni!";
			link.l1 = "Och, zamknij się! Idź w pokoju...";
			link.l1.go = "PrisonerInPlace_2";
			AddQuestRecord("GivePrisonFree", "3_4");
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
        
		// -------------------- освобождение заключённого --------------------
		// ------------------------ передать маляву --------------------------
        case "Deliver_1":
			dialog.text = "Nazywam się "+GetFullName(npchar)+". Mam do ciebie prośbę, he-he...";
			link.l1 = "Co u ciebie słychać?";
			link.l1.go = "Deliver_2";
		break;
        case "Deliver_2":
			dialog.text = "Potrzebuję, aby list został wysłany z więzienia. Czy to zrobisz?";
			link.l1 = "A co dla mnie z tego będzie?";
			link.l1.go = "Deliver_3";
		break;
        case "Deliver_3":
			dialog.text = "Kumple cię nie zawiodą, obiecuję... Więc? Jesteś przy nas?";
			link.l1 = "Nie, nie jestem zainteresowany.";
			link.l1.go = "Prisoner_5";
			link.l2 = "Cóż, jeśli to nie wymaga zbyt dużego wysiłku z mojej strony, mogę to zrobić.";
			link.l2.go = "Deliver_agree";
		break;
        case "Deliver_agree":
			dialog.text = "Dobrze. Teraz słuchaj mnie uważnie. Dwóch kumpli czeka na moją wiadomość w domu, aby nie zostali schwytani podczas nalotu. Ale nie mam pojęcia, który to dokładnie dom. Będziesz musiał szukać.";
			link.l1 = "Co masz na myśli - szukać?";
			link.l1.go = "Deliver_4";
		break;
        case "Deliver_4":
			dialog.text = "Szukaj, jak w szukaniu. Będziesz biegać po mieście, zaglądać do domów. Kiedy trafiłeś we właściwe miejsce, nie wypuszczą cię bez rozmowy. Ale pamiętaj, że zostałbym tam co najwyżej dwa dni. Więc nie zwlekaj.";
			link.l1 = "Rozumiem. No to podaj swoją wiadomość.";
			link.l1.go = "Deliver_5";
		break;
        case "Deliver_5":
			pchar.questTemp.jailCanMove.Deliver.locationId = GetBanderLocation(npchar); //Id коммона
			if (pchar.questTemp.jailCanMove.Deliver.locationId == "none")
			{
				dialog.text = "Hmm, wiesz, po prostu mi się nie podobasz. Zmieniłem zdanie. Chodź, nie stój tam!";
				link.l1 = "Patrz na ciebie! Cóż, jak sobie życzysz...";
				link.l1.go = "NoMoreTalkExit";
				DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
			}
			else
			{
				dialog.text = "Tu. Dziękuję, "+GetSexPhrase("kumpel","dziewczyno")+"!";
				link.l1 = "Wcale nie.";
				link.l1.go = "NoMoreTalkExit";
				GiveItem2Character(Pchar, "Malyava");
				pchar.questTemp.jailCanMove.Deliver.Id = npchar.id; //Id зэка
				pchar.questTemp.jailCanMove.Deliver.name = GetFullName(npchar); //имя зэка
				pchar.questTemp.jailCanMove.Deliver.City = npchar.city; //город (Id колонии)
				pchar.questTemp.jailCanMove.Deliver.good = rand(3); //опрокинут или нет
				pchar.questTemp.jailCanMove.Deliver.price = rand(6)*500+500; //цена услуги
				pchar.quest.DeliverToBander.win_condition.l1 = "location";
				pchar.quest.DeliverToBander.win_condition.l1.location = pchar.questTemp.jailCanMove.Deliver.locationId;
				pchar.quest.DeliverToBander.win_condition = "DeliverToBander";
				pchar.quest.DeliverToBander.again = true; 
				SetTimerCondition("DeliverToBander_over", 0, 0, 2, false);
				ReOpenQuestHeader("GivePrisonFree");
				AddQuestRecord("GivePrisonFree", "8");
				AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("",""));
				AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
				AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Deliver.name);
			}
		break;
		
		// Warship, 16.05.11. Генер "Justice for sale".
		case "JusticeOnSale_1":
			dialog.text = "Tak, został aresztowany pod zarzutem przemytu. Ale dlaczego tobie zależy na tym szubrawcu, "+GetAddress_Form(NPChar)+"?";
			link.l1 = "Jego gang planuje zorganizować jego ucieczkę i kontynuować ich brudne sprawy.";
			link.l1.go = "JusticeOnSale_2";
			link.l2 = "Słyszałem, że nie był winny.";
			link.l2.go = "JusticeOnSale_3";
			
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.PrisonWait");
		break;
		
		case "JusticeOnSale_2":
			dialog.text = "Musisz powiadomić gubernatora, "+GetAddress_Form(NPChar)+", te łajdaki muszą być złapani!";
			link.l1 = "Zrobię właśnie to.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First_officer";
		break;
		
		case "JusticeOnSale_3":
			dialog.text = "Słuchaj, "+GetFullName(PChar)+", ten facet został aresztowany podczas próby sprzedaży zakazanych towarów, prosto w mieście! Jak możesz twierdzić, że nie jest winny?";
			link.l1 = "Słyszałem, że oskarżenie jest bezpodstawne i nie masz dowodów, czyż nie? Nie możesz po prostu zatrzymać człowieka, który został skrzywdzony.";
			link.l1.go = "JusticeOnSale_4";
		break;
		
		case "JusticeOnSale_4":
			dialog.text = "Nie mamy ani świadków, ani towarów, ale to niczego nie zmienia, kapitanie "+GetFullName(PChar)+"! Ta osoba jest zdecydowanie winna - a może nie tylko nielegalnego handlu. Tak czy inaczej - dlaczego miałbyś się przejmować więźniem?";
			link.l1 = "Być może, moje słowo może być poręką dla tego nieszczęsnego więźnia?";
			link.l1.go = "JusticeOnSale_5_WithoutMoney";
			
			if(sti(PChar.money) >= 5000)
			{
				link.l2 = "Być może, te 5000 pesos mogą być kaucją dla tego nieszczęsnego więźnia?";
				link.l2.go = "JusticeOnSale_5";
			}
		break;
		
		case "JusticeOnSale_5_WithoutMoney":
			if(GetCharacterSkill(PChar, SKILL_LEADERSHIP) > hrand(100) || sti(PChar.money) < 5000)
			{
				dialog.text = "W porządku, "+GetAddress_Form(NPChar)+", weź tego łajdaka i odejdź, zanim zmienię zdanie.";
				link.l1 = "Cudownie jest widzieć triumf sprawiedliwości, nie sądzisz?";
				link.l1.go = "JusticeOnSale_6";
			}
			else
			{
				dialog.text = "Nie, "+GetAddress_Form(NPChar)+", to nie przejdzie.";
				link.l1 = "W takim razie, może te 5000 pesos będą bardziej przekonującym argumentem?";
				link.l1.go = "JusticeOnSale_5";
			}
		break;
		
		case "JusticeOnSale_5":
			dialog.text = "Dobrze, "+GetAddress_Form(NPChar)+", weź tego łajdaka i wyjdź, zanim zmienię zdanie.";
			link.l1 = "To wspaniale widzieć triumf sprawiedliwości, nie sądzisz?";
			link.l1.go = "JusticeOnSale_6";
			AddMoneyToCharacter(PChar, -5000);
			PChar.GenQuest.JusticeOnSale.PrisonMoney = true;
		break;
		
		case "JusticeOnSale_6":
			DialogExit();
			sld = GetCharacter(NPC_GenerateCharacter("JusticeOnSale_Smuggler", "mercen_"+(rand(9)+1), "man", "man", sti(PChar.rank)+5, PIRATE, -1, true, "marginal"));
			SetFantomParamFromRank(sld, sti(PChar.rank)+5, true);
			sld.name = PChar.GenQuest.JusticeOnSale.SmugglerName;
			sld.lastName = "";
			sld.dialog.filename = "GenQuests_Dialog.c";
			sld.dialog.currentnode = "First time";
			sld.greeting = "Enc_Raiders"; 
			AddPassenger(PChar, sld, false);
			SetCharacterRemovable(sld, false);
			PChar.GenQuest.JusticeOnSale.SmugglerModel = sld.model;
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait");
			sld = &Locations[FindLocation(PChar.GenQuest.JusticeOnSale.ShoreId)];
			sld.DisableEncounters = true;
			PChar.Quest.JusticeOnSale_ShoreEnterWithSmuggler.win_condition.l1  = "location";
			PChar.Quest.JusticeOnSale_ShoreEnterWithSmuggler.win_condition.l1.location = PChar.GenQuest.JusticeOnSale.ShoreId;
			PChar.Quest.JusticeOnSale_ShoreEnterWithSmuggler.function = "JusticeOnSale_ShoreEnterWithSmuggler";
			Log_Info("Smuggler's captain on a board");
			PlaySound("interface\notebook.wav");
			LAi_Fade("", "");
			WaitDate("",0,0,0,0,60); // 280313 // лесник. прокрутка времени было так WaitDate("",0,0,0,2,5);
		break;
		// --> belamour ночной приключенец
		case "NightAdventure_CitizenHomie":
			dialog.text = "Tak, był taki gwałtowny. Był niegrzeczny wobec strażnika, a potem wszedł w bójkę. Nic więcej: posiedzi za kratkami kilka dni - wytrzeźwieje. Dlaczego on cię obchodzi? Wyglądasz na kapitana, a ten pijak nie wygląda na marynarza.";
			link.l1 = "Tak, to prawda, jestem kapitanem. Sprawa wygląda tak, że ten pijak to stary znajomy. Proszę, tylko nikomu o tym nie mów. Jeśli dobrze rozumiem, nawet nie chwycił za broń. Może tym razem na moją prośbę go wypuścisz?";
			link.l1.go = "NightAdventure_CitizenHomie_1";
		break;
		
		case "NightAdventure_CitizenHomie_1":
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomie") // отпустил под честное слово
			{
				dialog.text = "Tak, dobry przyjaciel mój. Nie martw się, nikomu nie powiem. Właściwie, nawet nie potrafił dobrze uderzyć, to był tylko próba - dlatego wsadzili go do więzienia. Skoro pytasz, z szacunku dla ciebie, go wypuszczę. Tylko ostrzeż go, żeby za następnym razem się kontrolował. Albo lepiej jeszcze, niech pije mniej.";
				link.l1 = "Dziękuję ci, oficerze.";
				link.l1.go = "NightAdventure_CitizenHomieOK";
			}
			
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderNM" || pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderGM") // поговорить с солдатом
			{
				dialog.text = "Tak, dobry przyjacielu. Nie martw się, nikomu nie powiem. Tylko on zdołał uderzyć strażnika w twarz, zanim go związali. Więc nie mogę go wypuścić. Chyba że, oczywiście, strażnik zgodzi się wycofać swoje roszczenia. Możesz z nim sam porozmawiać, dzisiaj patroluje po mieście.";
				link.l1 = "Nie, obawiam się, że jeśli uderzył strażnika, to nie mogę mu pomóc. Będzie musiał posiedzieć kilka dni. Przykro mi, że przeszkadzam ci, oficerze.";
				link.l1.go = "CitizenHomieEnd";
				link.l2 = "Dobrze, pójdę i spróbuję negocjować z wartownikiem.";
				link.l2.go = "NightAdventure_CitizenHomieSolder";
			}
			
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieOfficer") // выплата офицеру
			{
				dialog.text = "Tak, dobry przyjacielu. Nie martw się, nikomu nie powiem. Sprawa wygląda tak, że atak na członka sił zbrojnych podczas służby to przestępstwo. Mogę iść na kompromis i wypuścić go, ale tylko za kaucją.";
				link.l1 = "Ile muszę za to zapłacić?";
				link.l1.go = "NightAdventure_CitizenHomieOfficer";
			}
		break;
		
		case "NightAdventure_CitizenHomieOK":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
			SetFunctionLocationCondition("NightAdventure_CitizenHomieOK", npchar.City+"_town", false);
		break;
		
		case "NightAdventure_CitizenHomieEnd":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
			pchar.quest.NightAdventure_SeaExit.over = "yes";
			pchar.quest.NightAdventure_JungleExit.over = "yes";
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		case "NightAdventure_CitizenHomieSolder":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
			for(i=0; i<MAX_CHARACTERS; i++)
			{
				if(Characters[i].location != npchar.City+"_town") continue;
				if(Characters[i].chr_ai.type != "patrol") continue;
				while(SoldQty < 10) // на всякий случай, чтобы не было выхода за границы массива
				{                   // генерируется 7 солдат + 3 мушкетера
					SoldNum[SoldQty] = Characters[i].index;
					SoldQty++;
				}
			}
			iTemp = rand(SoldQty);
			pchar.GenQuest.NightAdventureSolNum = SoldNum[iTemp];
		break;
		
		case "NightAdventure_HomieToPrisoner":
			DeleteAttribute(pchar,"GenQuest.NightAdventureToPrisoner");
			pchar.quest.NightAdventure_SeaExit.over = "yes";
			pchar.quest.NightAdventure_JungleExit.over = "yes";
			SetFunctionLocationCondition("NightAdventure_CitizenHomieOK", npchar.City+"_town", false);
			dialog.text = "*czyta* Tak... tak... No, skoro wartownik nie ma zastrzeżeń, to ja też nie mam. Możesz zabrać swojego przyjaciela. Tylko go ostrzeż, żeby za następnym razem się kontrolował. Lepiej jeszcze, niech pije mniej.";
			link.l1 = "Dziękuję oficerze.";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_CitizenHomieOfficer":
			dialog.text = "Cóż, biorąc pod uwagę, że nie chwycił za broń, to tylko 1500 peso.";
			link.l1 = "Obawiam się, że nie jestem gotów dać aż tyle. Cóż, biorąc pod uwagę, że jest tu tylko przez kilka dni, chyba mu to nie zaszkodzi. Może będzie pił mniej.";
			link.l1.go = "NightAdventure_CitizenHomieEnd";
			if(sti(pchar.money) >= 1500)
			{
				link.l2 = "Dobrze, jestem gotowy wpłacić kaucję.";
				link.l2.go = "NightAdventure_CitizenHomieOfficer_1";
			}
		break;
		
		case "NightAdventure_CitizenHomieOfficer_1":
			AddMoneyToCharacter(pchar, -1500);
			DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
			pchar.quest.NightAdventure_SeaExit.over = "yes";
			pchar.quest.NightAdventure_JungleExit.over = "yes";
			SetFunctionLocationCondition("NightAdventure_CitizenHomieOK", npchar.City+"_town", false);
			dialog.text = "Możesz odebrać swojego przyjaciela. Tylko go ostrzeż, żeby następnym razem się kontrolował. Albo lepiej jeszcze, niech pije mniej.";
			link.l1 = "Dziękuję Ci, oficerze.";
			link.l1.go = "exit";
		break;
		// <-- ночной приключенец
		
		// --> Sinistra Путеводная звезда
		case "PZ_BasTer_ComendantDialog":
			if (CheckAttribute(pchar, "questTemp.PZ_BasTerOpozdal"))
			{
				dialog.text = "Dzięki za zgodę na przybycie zamiast rozpoczynania masakry. Przynajmniej ktoś jest rozsądny w dzisiejszych czasach.";
				link.l1 = "Więc, czemu zawdzięczam tę uwagę, Panie Oficerze? Czy to ma coś wspólnego z faktem, że szukam Chińczyka?";
				link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_1";
			}
			else
			{
				dialog.text = "Dobrze, że przyszedłeś do nas z własnej woli. Ostatnio mamy dość chuliganów.";
				link.l1 = "Cóż, jak możesz zobaczyć, nie jestem jednym z tych agresywnych. Jednak... dlaczego jestem tutaj, oficerze? Już pytałem twoich ludzi, ale nie dostałem odpowiedzi - czy to dlatego, że szukam pewnego Chińczyka w mieście?";
				link.l1.go = "PZ_BasTer_ComendantDialog_1";
			}
			DeleteQuestCondition("PZ_BasTerPeshera");
			npchar.Dialog.Filename = "Common_Prison.c";
			npchar.Dialog.CurrentNode = "First_officer";
		break;
		// <-- Путеводная звезда
		case "Helen_meeting":
			dialog.text = "Oczywiście, że nie! Proszę, wejdź. Zawsze jesteś mile widziany w naszych lochach. Ehm, oczywiście mam na myśli to w dobry sposób. No to, czego tutaj potrzebujesz?";
			link.l1 = "Och, nic specjalnego, wiesz, po prostu oglądam miasto, więc przypadkowo tu zawędrowałem.";
			link.l1.go = "exit";
			link.l2 = "Chciałem porozmawiać o pewnym interesie.";
			link.l2.go = "quests";
			if (!sti(pchar.questTemp.jailCanMove))
			{
				link.l4 = "Chcę wejść do więzienia.";
				link.l4.go = "ForGoodMove";		
			}
			NextDiag.TempNode = "First_officer";
		break;
	}
}

void GetChestPlaceName()
{
	string islandId;
	int iTemp = rand(3);
	switch (iTemp)
	{
		case 0: 
			pchar.questTemp.jailCanMove.islandId = "Bermudes";
			pchar.questTemp.jailCanMove.placeId = "Bermudes_Cavern";
		break;
		case 1: 
			pchar.questTemp.jailCanMove.islandId = "Caiman";
			pchar.questTemp.jailCanMove.placeId = "Caiman_Grot";
		break;
		case 2: 
			pchar.questTemp.jailCanMove.islandId = "Dominica";
			pchar.questTemp.jailCanMove.placeId = "Dominica_Grot";
		break;
		case 3: 
			pchar.questTemp.jailCanMove.islandId = "Terks";
			pchar.questTemp.jailCanMove.placeId = "Terks_Grot";
		break;
	}
}

string GetBanderLocation(ref npchar)
{
    aref	arCommon, arRld, arRld2;
    int	i, n, Qty, Qty2;
	string LocId; 
	string	storeArray [50];
	int howStore = 0;
    makearef(arRld, Locations[FindLocation(npchar.city + "_town")].reload);
	Qty = GetAttributesNum(arRld);
    if (CheckAttribute(pchar, "GenQuest.SeekSpy.Location")) //если взят квест мэра по поиску шпиона
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.GenQuest.SeekSpy.Location)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.GenQuest.SeekSpy.Location && arCommon.name != "reload1") // mitrokosta fix
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	else
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && arCommon.name != "reload1") // mitrokosta fix
    				{
						storeArray[howStore] = LocId;
						howStore++; 
					}
				}
			}	
		}
	}
	if (howStore == 0) return "none";
	LocId = storeArray[rand(howStore-1)];
	SetOpenDoorCommonLoc(npchar.city, LocId); //открываем дверь
	for(n=0; n<MAX_CHARACTERS; n++)
	{
		if (CheckAttribute(&characters[n], "locations") && characters[n].locations == LocId) 
		{			
			characters[n].lifeDay = 0;
		}
	}
	return LocId;
}

string GenQuestPrison_GenerateArtefact() // артефакты
{
	string itemID;
	switch(rand(7))
	{
		case 0:
			itemID = "indian_5";
		break;
		case 1:
			itemID = "indian_7"; 
		break;
		case 2:
			itemID = "indian_8"; 
		break;
		case 3:
			itemID = "indian_9"; 
		break;
		case 4:
			itemID = "indian_10"; 
		break;
		case 5:
			itemID = "indian_11"; 
		break;
		case 6:
			itemID = "indian_3"; 
		break;
		case 7:
			itemID = "indian_6"; 
		break;
	}
	return itemID;
}

string GenQuestPrison_GenerateBlade() // клинки и другое
{
	string itemID;
	switch(rand(8))
	{
		case 0:
			itemID = GetGeneratedItem("blade_16");
		break;
		case 1:
			itemID = GetGeneratedItem("blade_15"); 
		break;
		case 2:
			itemID = GetGeneratedItem("blade_13"); 
		break;
		case 3:
			itemID = "cirass2"; 
		break;
		case 4:
			itemID = GetGeneratedItem("blade_10"); 
		break;
		case 5:
			itemID = "spyglass3"; 
		break;
		case 6:
			itemID = "cirass6"; 
		break;
		case 7:
			itemID = "cirass7"; 
		break;
		case 8:
			itemID = "cirass1"; 
		break;	
		
	}
	return itemID;
}

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ref rItem, rChar, sld, MerPrm;
	aref arTemp1, arTemp2;
	bool bTemp;
	int iBanditsCount, i, iMoney, iNation, iTmp, iGoods, iRank, iScl;
	String sTitle, sGroup, sTemp, sText; // belamour 
	float locx, locy, locz;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "To jest błąd. Skontaktuj się z deweloperami i powiedz im, jak i gdzie go znalazłeś";
					link.l1 = RandSwear()+"Dam im znać!";
					link.l1.go = "exit";
					
			if(HasSubStr(NPChar.id, "ContraMeetManQuest_Soldier_")) // Солдеры по квесту "встреча в бухте"
			{
				dialog.text = "Nie jestem upoważniony do handlu z tobą. Porozmawiaj z naszym oficerem.";
					link.l1 = LinkRandPhrase("Oczywiście...","Rozumiem.","Z pewnością!");
					link.l1.go = "exit";
				break;
			}
			
			if(HasSubStr(NPChar.id, "ContraMeetManQuest_Officer_")) // Офицер по квесту "встреча в бухте"
			{
				dialog.text = "Przedstaw się! Chcę wiedzieć, z kim rozmawiam!";
					link.l1 = "Me imię to "+GetFullName(PChar)+"  Co tu się dzieje?";
					link.l1.go = "ContraMeetManQuest_Sold_1";
				break;
			}
					
			if(NPChar.id == "ContraMeetManQuest_QuestMan" && PChar.location == PChar.GenQuest.ContraMeetMan.ShoreID) // Квестовый чел по генеру "meeting in the cove" 
			{
				dialog.text = "Kapitanie, twoje imię to "+GetFullName(PChar)+", czyż nie?";
					link.l1 = "Tak, masz rację.";
					link.l1.go = "ContraMeetManQuest_1";
					link.l2 = "Nie. Pomyliliście mnie z kimś innym.";
					link.l2.go = "exit";
					break;
			}
			
			if(NPChar.id == "ContraMeetManQuest_QuestMan" && CheckAttribute(PChar, "GenQuest.ContraMeetMan.ContraIsDead")) // В комнате таверны после убицства контриков
			{
				LAi_LocationFightDisable(LoadedLocation, false);
				dialog.text = PChar.name+", bardzo Ci dziękuję! Gdyby nie Ty, mój los byłby godny pożałowania... Jak mogę Ci podziękować?";
					link.l1 = "Nie potrzebuję niczego...";
					link.l1.go = "ContraMeetManQuest_7";
					link.l2 = "Nie odmówiłbym drobnej nagrody.";
					link.l2.go = "ContraMeetManQuest_8";
					break;
			}
			
			if(NPChar.id == "ContraMeetManQuest_Contrick_0") // Контрик в комнате по квесту "встреча в бухте"
			{
				iMoney = (rand(3)+2)*500;
				PChar.GenQuest.ContraMeetMan.Money = iMoney;
				if(!CheckAttribute(PChar, "GenQuest.ContraMeetMan.ManIsTraitor")) // Просто платят деньги
				{
					dialog.text = "...Hmm, to rzeczywiście on... Dziękuję, "+GetSexPhrase("kamrat","dziewka")+", bez twojej pomocy mielibyśmy trudności, nie ma mowy, żebyśmy wydostali się z miasta. Proszę, weź "+FindRussianMoneyString(iMoney)+" i możesz się zgubić. A my sobie 'pogadamy' z naszym przyjacielem...";
						link.l1 = "...";
						link.l1.go = "ContraMeetManQuest_3";
				}
				else
				{
					dialog.text = "...Hmm, to rzeczywiście on... Dziękuję, "+GetSexPhrase("kamrat","dziewko")+"bez twojej pomocy mielibyśmy trudności, nie ma dla nas drogi wyjścia z miasta. Proszę, weź "+FindRussianMoneyString(iMoney)+" i możesz się zgubić. Teraz wypatroszymy tego parszywego zdrajcę!";
						link.l1 = "Oczywiście. Do zobaczenia ponownie, panowie...";
						link.l1.go = "ContraMeetManQuest_4";
						link.l2 = "Co?! Nie, nie pozwolę ci zamordować człowieka, bez względu na to, kim jest... I nie potrzebuję twoich przeklętych pieniędzy!";
						link.l2.go = "ContraMeetManQuest_5";
				}
					break;
			}
			
			if(NPChar.id == "ContraDeliverQuest_Soldier_0") // Солдер в комнате
			{
				dialog.text = "Więc... Co my tu mamy? Piraci?! Będziecie musieli iść z nami do biura komendanta na przesłuchanie...";
					link.l1 = "Nie jesteśmy piratami! W ogóle nie znam tego człowieka! On tylko wynajął i wprowadził się do tego pokoju, a ja nie miałem czasu spakować swoich rzeczy i odejść!";
					link.l1.go = "ContraDeliverQuest_Sold1";
					break;
			}
				
			if(CheckAttribute(PChar, "GenQuest.ContraDeliver.WaitOnRoom") && NPChar.id == "ContraDeliverQuest_Contra_1")
			{
				dialog.text = "Więc co mówiłeś? Masz dla mnie wiadomość?! Czekam!";
					link.l1 = "Oto masz...";
					link.l1.go = "ContraDeliverQuest_1";
					DeleteAttribute(PChar, "GenQuest.ContraDeliver.WaitOnRoom");
					DeleteAttribute(PChar, "GenQuest.ContraDeliver.GoToTavern");
					break;
			}
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore") && NPChar.id == "Church_GenQuest2_Bandit_0")
			{
				dialog.text = "Hej, ty! Tak, ty. Widzę, że jesteś przyzwoitym i zamożnym człowiekiem.";
					link.l1 = "Nie mogę powiedzieć tego samego o tobie.";
					link.l1.go = "Church_GenQuest_2_ShoreBandit_1";
					break;
			}
					
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.WayOfShortVariant") && NPChar.id == "Church_GenQuest2_Bandit_0")
			{
				dialog.text = "Trzymaj się! Hej, "+GetSexPhrase("kamracie","dziewka")+"pokaż nam, jak ciężka jest twoja sakiewka!";
					link.l1 = "Więc, czy już zmarnowałeś wszystkie kościelne pieniądze?";
					link.l1.go = "Church_GenQuest_2_1";
					break;
			}
			
			if(NPChar.id == "ReasonToFast_Hunter")
			{
				if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > sti(pchar.questTemp.ReasonToFast.p2))
				{
					dialog.text = "Ej, na łodzi! Hic... Oczyśćcie tor - muszę pogadać z chłopakami...";
					link.l1 = "Czy nie jesteś trochę skołowany, kumplu? Idź to odespać.";
					link.l1.go = "ReasonToFast_Hunter1";
				}
				else
				{
					dialog.text = "Hej, kapitanie! Rzuć kotwicę!";
					link.l1 = "A dlaczego do diabła miałbym....";
					link.l1.go = "ReasonToFast_Hunter2";
				}
				link.l2 = "Czyż nie jesteś trochę zbyt niegrzeczny!?";
				link.l2.go = "ReasonToFast_Hunter3";	
			}
			
			if(NPChar.id == "PirateOnUninhabited_0")
			{
				dialog.text = RandPhraseSimple("Witajcie! Wreszcie Pan wysłuchał naszych modlitw i zesłał dzielnego kapitana na ten opuszczony brzeg!","Dzięki Opatrzności! Teraz miejscowe sępy nie będą pożywiać się naszymi zgniłymi kośćmi!");
				link.l1 = "Witaj, dobry człowieku, jestem kapitanem "+GetFullName(PChar)+" Widzę, że jesteś tu w niezłych tarapatach.";
				link.l1.go = "PiratesOnUninhabited_3";
				link.l2 = "Dobry człowieku, mam własne sprawy do załatwienia i nie mam czasu na twoje kłopoty.";
				link.l2.go = "PiratesOnUninhabited_1";
			}
			
			if(NPChar.id == "ShipWreck_0")
			{
				dialog.text = RandPhraseSimple("O, kapitanie! To czyste szczęście, że Bóg zesłał ci pomyślny wiatr i poprowadził cię do tego opuszczonego miejsca!","Kapitanie! Dzięki Opatrzności, żeś zdecydował się zarzucić kotwicę na tej pustynnej przystani!");
				link.l1 = "Witaj, dobry człowieku, jestem kapitanem "+GetFullName(pchar)+" Widzę, że masz tu poważne kłopoty.";	
				link.l1.go = "ShipWreck_2";
				link.l2 = "Dobry człowieku, mam swoje własne sprawy do załatwienia i nie mam czasu na twoje kłopoty.";
				link.l2.go = "ShipWreck_1";
			}
			
			if(NPChar.id == "Convict_0")
			{
				dialog.text = LinkRandPhrase("Trzymaj się, "+GetAddress_Form(pchar)+"Zechcesz poświęcić nam chwilę swego cennego czasu?","Czy szlachetny by się zgubił"+GetSexPhrase("ter","s")+" wysłuchaj pokornego żądania tych niegodnych ludzi?","Szlachetna pomyłka"+GetSexPhrase("ter","s")+", proszę, poświęć chwilę ze swego cennego czasu, by porozmawiać z nieszczęśnikiem.");
				link.l1 = LinkRandPhrase("Nie mam na to czasu.","Spadaj, mam dużo do zrobienia bez ciebie.","Zostaw mnie w spokoju, nie mam dla ciebie czasu.");
				link.l1.go = "Convict_0End";
				link.l2 = LinkRandPhrase("Czego chcesz?","Czego potrzebujesz?","Jaki kłopot?");
				link.l2.go = "Convict_Begin";
			}
			
			// Warship, 15.05.11. Генер "Justice for sale".
			if(HasSubStr(NPChar.id, "JusticeOnSale_Jungle_"))
			{
				dialog.text = "Cześć, kapitanie! Czy interesują cię indiańskie błyskotki i towary, których nie można kupić w zwykłych sklepach? A może gotówka?";
					link.l1 = "Lumpy jak ty zazwyczaj żądają - nie oferują niczego. Dlaczego jesteś tak dziwnie uprzejmy?";
					link.l1.go = "JusticeOnSale_1";
					link.l2 = "Moja pistolet zwykle rozmawia z takimi łajdakami jak ty!";
					link.l2.go = "JusticeOnSale_2";
			}
		break;
		
		// Генератор "Situation in the hold - Ransom"
		case "Hold_GenQuest1":
			pchar.quest.Hold_GenQuest_FindCharTimeIsOver.over = "yes";
			dialog.text = "Słucham cię, kapitanie. Czy jesteś tu w interesach?";
			link.l1 = "Poszukuję pana "+pchar.GenQuest.Hold_GenQuest.Name+"?";
			link.l1.go = "Hold_GenQuest2";
		break;
		
		case "Hold_GenQuest2":
			dialog.text = RandPhraseSimple("Jestem panem "+pchar.GenQuest.Hold_GenQuest.Name+"Komu zawdzięczam ten zaszczyt?","Znalazłeś go. Co mogę dla ciebie zrobić?");
			link.l1 = "Jestem kapitanem "+GetFullName(pchar)+", chciałem z tobą porozmawiać o "+pchar.GenQuest.Hold_GenQuest.CapName+".";
			link.l1.go = "Hold_GenQuest3";
		break;
		
		case "Hold_GenQuest3":
			sld = characterFromId(pchar.GenQuest.Hold_GenQuest.CapId);
			pchar.GenQuest.Hold_GenQuest.RansomSum = makeint(3 * sti(sld.rank) * (800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L) * 100) + GetCharacterSkillToOld(sld, "Leadership")*500 + GetCharacterSkillToOld(pchar, "commerce")*500); 
						
			switch(hrand(3))
			{
				case 0:
					dialog.text = "A kto to jest?";
					link.l1 = "Trzymaj się... Jesteś "+pchar.GenQuest.Hold_GenQuest.Name+", a ty nie wiesz o "+pchar.GenQuest.Hold_GenQuest.CapName+"?";
					link.l1.go = "Hold_GenQuest40";
				break;
				case 1:
					dialog.text = "O rany! Minęło sporo czasu, odkąd ostatni raz słyszałem o tym starym lisie. Co się z nim stało tym razem?";
					link.l1 = "Tym razem jest w poważnych tarapatach... Jest przetrzymywany jako jeniec i potrzebuje twojej pomocy.";
					link.l1.go = "Hold_GenQuest50";
				break;
				case 2:
					dialog.text = "Dobrze, zamieniam się w słuch.";
					link.l1 = "Jego statek został zaatakowany przez piratów, a teraz jest przetrzymywany jako zakładnik. Radził, abym skontaktował się z tobą w sprawie okupu.";
					link.l1.go = "Hold_GenQuest60";
				break;
				case 3:
					dialog.text = "Tak, cieszę się, że słyszę o starym przyjacielu. Jak się ma?";
					link.l1 = "Jego sytuacja jest tak tragiczna, że trudno to sobie nawet wyobrazić.";
					link.l1.go = "Hold_GenQuest70";
				break;				
			}	
		break;
		
		case "Hold_GenQuest40":
			// dialog.text = "Istotnie, jestem "+pchar.GenQuest.Hold_GenQuest.Name+" ! Ale dlaczego miałbym coś o tym wiedzieć "+pchar.GenQuest.Hold_GenQuest.CapName+"?! ";
			dialog.text = "Zgadza się, jestem "+pchar.GenQuest.Hold_GenQuest.Name+"! Ale imię "+pchar.GenQuest.Hold_GenQuest.CapName+" to mi nic nie mówi."; // belamour gen
			link.l1 = "Przykro mi. Może się pomyliłem...";
			link.l1.go = "Hold_GenQuest41";
		break;
		
		case "Hold_GenQuest41":
			AddQuestRecord("HoldQuest", "10");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		
		case "Hold_GenQuest50":
			dialog.text = "Wow! A jak niby mam mu pomóc? Uwolnić go zabijając wszystkich jego wrogów, czy co? Ha-ha-ha!";
			link.l1 = "Nie, nie, to nie jest konieczne. Wystarczy, że oddasz "+pchar.GenQuest.Hold_GenQuest.RansomSum+"pesos jako okup.";
			link.l1.go = "Hold_GenQuest51";
		break;		
		
		case "Hold_GenQuest51":
			dialog.text = "Co za bezczelność! I dlaczego miałbym płacić za niego okup?! Nie jest ani moim krewnym, ani przyjacielem!";
			link.l1 = "Hmm... Powiedział mi, że jesteś jego jedyną nadzieją. I wspomniał też o jakimś twoim długu...";
			link.l1.go = "Hold_GenQuest52";
		break;		
		
		case "Hold_GenQuest52":
			dialog.text = LinkRandPhrase("Co za bezczelny typ! To on jest mi winien pieniądze, dla twojej informacji! Ale to nie jest powód, żebym go wykupywał w nadziei, że spłaci oba długi.","Co za łotr! Oszukał mnie, gdy dzieliliśmy nasz interes, a teraz ma czelność prosić mnie, bym zapłacił za niego okup!","To dopiero niespodzianka! Dlaczego miałbym płacić za niego okup?! Nie jesteśmy aż tak blisko.");
			link.l1 = "Więc mogę mu powiedzieć, że odmówiłeś zapłaty okupu i nie uznałeś swojego długu?";	
			link.l1.go = "Hold_GenQuest53";
		break;
		
		case "Hold_GenQuest53":
			dialog.text = "O mój Boże! O jakim długu mówisz? Już ci wszystko wyjaśniłem! A jeśli nie masz innych pytań poza tą głupią historią, to pozwól mi się oddalić.";
			link.l1 = "Rozumiem. Cóż, nie mam już więcej pytań do ciebie, ale kilka do tego twojego kumpla.";
			link.l1.go = "Hold_GenQuest54";
		break;
		
		case "Hold_GenQuest54":
			AddQuestRecord("HoldQuest", "10");
			//AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar)); // НПС вешать собрались? )))
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName); // belamour gen				
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		
		case "Hold_GenQuest60":
			dialog.text = "Hmm... A ty, jak mniemam, jesteś tym, który go trzyma... Cóż, chyba mu pomogę.";
			link.l1 = "Bardzo dobrze. Okup wyniesie "+pchar.GenQuest.Hold_GenQuest.RansomSum+"pesos.";
			link.l1.go = "Hold_GenQuest61";
		break;
		
		case "Hold_GenQuest61":
			dialog.text = "Źle mnie zrozumiałeś: jestem członkiem rady miejskiej. Pilnujemy przestrzegania karty."+"Straże!!! Straże! Aresztujcie go pod zarzutem handlu niewolnikami i plądrowania statków "+NationNameGenitive(sti(pchar.GenQuest.Hold_GenQuest.Nation))+"!";
			link.l1 = "No cóż, 'kamracie', pozwól mi tylko do ciebie dotrzeć...";
			link.l1.go = "Hold_GenQuest62";
		break;
		
		case "Hold_GenQuest62":
			LAi_SetImmortal(NPChar, false);
			AddQuestRecord("HoldQuest", "10");
			//AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName); // belamour gen	
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_SetWarriorTypeNoGroup(NPChar);
   	        LAi_warrior_DialogEnable(NPChar, false);
            LAi_group_MoveCharacter(NPChar, "TmpEnemy");			
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetCheckFunction("TmpEnemy", "Hold_GenQuest_AfterBattle");
			chrDisableReloadToLocation = true; 
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);  
			AddDialogExitQuest("MainHeroFightModeOn"); 
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
			DialogExit();
		break;
		
		case "Hold_GenQuest70":
			dialog.text = "Co ty mówisz?! I jak mogę mu pomóc?";
			link.l1 = "Jest przetrzymywany w niewoli i poprosił mnie, abym z tobą porozmawiał o jego wykupie.";
			link.l1.go = "Hold_GenQuest71";
		break;		
		
		case "Hold_GenQuest71":
			dialog.text = "Oczywiście, oczywiście. Zrobię wszystko, co w mojej mocy. Gdzie ich trzymają? A jaka jest wysokość okupu?";
			link.l1 = "Piraci żądają "+pchar.GenQuest.Hold_GenQuest.RansomSum+" pesos. Muszę dostarczyć pieniądze do portu, a wtedy twój przyjaciel zostanie uwolniony.";
			link.l1.go = "Hold_GenQuest72";
		break;
		
		case "Hold_GenQuest72":
			dialog.text = "Oto pieniądze. Na szczęście miałem przy sobie wystarczająco dużo.";
			link.l1 = "Tak, to rzeczywiście szczęście. Idź do portu, a wkrótce znów zobaczysz swego druha.";
			link.l1.go = "Hold_GenQuest73";
		break;
		
		case "Hold_GenQuest73":
			addMoneyToCharacter(pchar, sti(pchar.GenQuest.Hold_GenQuest.RansomSum));
			AddQuestRecord("HoldQuest", "11");
			AddQuestUserData("HoldQuest", "sNameChar", GetFullName(NPChar)); // belamour gen 
			AddQuestUserData("HoldQuest", "sName", NPChar.Hold_GenQuest.Name); // belamour gen
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.RansomSum);
			pchar.GenQuest.Hold_GenQuest = "prisoner_ransom";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;				
		// Генератор "Situation in the hold - Ransom"
		
		// Генератор "Situation in the hold - Partner in crime"
		case "Hold_GenQuest80":
			dialog.text = "Witaj, kapitanie, przepraszam, że nie miałem zaszczytu się przedstawić. Mówili, że mnie szukałeś.";
			link.l1 = "Rzeczywiście, jeśli jesteś panem "+pchar.GenQuest.Hold_GenQuest.Name+". Jestem kapitanem "+GetFullName(pchar)+"Chciałem z tobą porozmawiać.";
			link.l1.go = "Hold_GenQuest81";
		break;
		
		case "Hold_GenQuest81":
			dialog.text = "A jaki to interes, kapitanie "+GetFullName(pchar)+"?";
			link.l1 = "Słyszałem, że posiadasz coś, z czym nie miałbyś nic przeciwko się rozstać.";
			link.l1.go = "Hold_GenQuest82";
		break;
		
		case "Hold_GenQuest82":
			dialog.text = "Co dokładnie insynuujesz?";
			link.l1 = "Nie bądź taki uparty, mój dobry człowieku, doskonale wiem o twojej mrocznej przeszłości i o prowizorycznej mapie, na której jest lokalizacja skarbu"+GetName(NAMETYPE_VIP,pchar.GenQuest.Hold_GenQuest.PirateName,NAME_ACC)+"jest wskazane.";
			link.l1.go = "Hold_GenQuest83";
		break;
		
		case "Hold_GenQuest83":
			dialog.text = "Cholera jasna! Zawsze wiedziałem, że ten łajdak"+pchar.GenQuest.Hold_GenQuest.CapName+"wygadałby to prędzej czy później! Co ja sobie myślałem, oferując mu ten układ?";
			link.l1 = "Przestań już jęczeć. Nie mam złych zamiarów... Po prostu sprzedaj mi tę mapę i prowadź życie, do którego jesteś przyzwyczajony.";
			link.l1.go = "Hold_GenQuest84";
		break;
		
		case "Hold_GenQuest84":
			dialog.text = "Jeśli tylko mógłbym być tego taki pewny... A ile zamierzasz mi za to zaoferować? Z pewnością wiesz, że w skrzyni było dużo złota. Niosło ją czterech ludzi, niech Pan spoczywa ich dusze...";
			link.l1 = "Ale "+GetName(NAMETYPE_VIP,pchar.GenQuest.Hold_GenQuest.PirateName,NAME_NOM)+" mógł już zdobyć jego skarb...";
			link.l1.go = "Hold_GenQuest85";
		break;
		
		case "Hold_GenQuest85":
			dialog.text = "Prawda także... Dobrze, jestem gotów sprzedać ci to za "+pchar.GenQuest.Hold_GenQuest.Sum+"pesos. Nie odważę się i tak niepokoić zmarłych.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.Hold_GenQuest.Sum) && !CheckCharacterItem(pchar,"mapQuest") && !CheckCharacterItem(pchar,"map_full"))
			{
				link.l1 = "Dobrze. Umowa stoi.";
				link.l1.go = "Hold_GenQuest86";
			}	
			link.l2 = "Nie, mój dobry człowieku, ten skrawek papieru nie jest wart tych pieniędzy. Żegnaj...";
			link.l2.go = "Hold_GenQuest87";
			pchar.quest.Hold_GenQuest_GetMapTimeIsOver.over = "yes";
		break;
		
		case "Hold_GenQuest86":		
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Hold_GenQuest.Sum));
			GiveItem2Character(pchar, "mapQuest"); 
			rItem = ItemsFromID("mapQuest");
			Hold_GenQuest_GenerateTreasureMap(rItem);
			AddQuestRecord("HoldQuest", "15");
			AddQuestUserData("HoldQuest", "sPirateName", GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_ACC));
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("",""));
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.Sum);						
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);			
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;	
		
		case "Hold_GenQuest87":
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);
			AddQuestRecord("HoldQuest", "16");
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("",""));
			AddQuestUserData("HoldQuest", "sPirateName", GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_GEN)); // belamour gen
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.Sum);			
			CloseQuestHeader("HoldQuest");
			DeleteAttribute(pchar,"GenQuest.Hold_GenQuest");				
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;
		// Генератор "Situation in the hold - Partner in crime"
		
		// Генератор "Shipwrecked"
		case "ShipWreck_1":
			dialog.text = "Jak to możliwe, kapitanie?! Bóg nigdy nie przebaczy ci takiego grzechu.";
			link.l1 = "To do Niego należy decyzja.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddDialogExitQuestFunction("ShipWreck_DialogDisable");
		break;
		
		case "ShipWreck_2":
			pchar.GenQuest.ShipWreck.StartShipType = PiratesOnUninhabited_GenerateShipType(); 		
			pchar.GenQuest.ShipWreck.ShipTypeName = GenerateRandomNameToShip(sti(pchar.GenQuest.ShipWreck.Nation));			
			
			if(rand(1) == 0)
			{
				dialog.text = RandPhraseSimple(" Witaj, jestem "+pchar.GenQuest.ShipWreck.Name+", kapitanie z "+GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name+"Acc"))+" '"+pchar.GenQuest.ShipWreck.ShipTypeName+", mój statek rozbił się na rafach niedaleko wybrzeża."+"Z całej załogi przeżyło tylko kilku marynarzy. Przypływ wyrzucił nas na ten opustoszały brzeg. Głodowaliśmy i pragnęliśmy "+(5+hRand(7))+"tygodnie do teraz","Cześć, jestem "+pchar.GenQuest.ShipWreck.Name+", kapitanie z "+GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name+"Gen"))+" '"+pchar.GenQuest.ShipWreck.ShipTypeName+". Nasz statek rozbił się niedaleko stąd."+"Udało nam się dotrzeć do tego brzegu na wrakach statków, ale to miejsce wydaje się niezamieszkałe. Byliśmy zmuszeni przetrwać na skorupiakach i owocach palm przez "+(5+hRand(7))+" tygodni do tej pory.");
				link.l1 = RandPhraseSimple("Ilu z was zostało?","Ilu z was udało się przeżyć?");
				link.l1.go = "ShipWreck_3";
			}
			else
			{						
				pchar.GenQuest.ShipWreck.Mutiny = "true"; // belamour gen кавычки
				pchar.GenQuest.ShipWreck.BadName = GenerateRandomName_Generator(sti(pchar.GenQuest.ShipWreck.Nation), "man");
				pchar.GenQuest.ShipWreck.City = GetQuestNationsCity(sti(pchar.GenQuest.ShipWreck.Nation));
				dialog.text = "O, kapitanie, nasze straty są naprawdę straszne... Witaj, jestem "+pchar.GenQuest.ShipWreck.Name+", kapitan i właściciel "+GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name+"Gen"))+" '"+pchar.GenQuest.ShipWreck.ShipTypeName+"Albo, powinienem rzec, były kapitanie i właścicielu."+"Ten drań "+pchar.GenQuest.ShipWreck.BadName+" którego wynająłem w "+XI_ConvertString("Colony"+pchar.GenQuest.ShipWreck.City+"Voc")+" sprowokował moją załogę do buntu. W końcu wylądowaliśmy w tym zagubionym miejscu. To się stało "+(5+hRand(7))+" tygodnie temu.";
				link.l1 = "I co wtedy? Cała twoja załoga dołączyła do buntowników?";
				link.l1.go = "ShipWreck_4";			
			}
		break;
		
		case "ShipWreck_3":
			dialog.text = RandPhraseSimple("Z całej załogi tylko "+ShipWreck_GetStringQty(sti(pchar.GenQuest.ShipWreck.Qty))+" survived. Other's have perished; several of them died already here of wounds and fever",
				"Only " + ShipWreck_GetStringQty(sti(pchar.GenQuest.ShipWreck.Qty)) + " were lucky enough. Others have met their end... either in the deep or in the dunes of this coast.");
			link.l1 = LinkRandPhrase("Tak, to godny pożałowania los. Ale taki jest los marynarza - każdy mógłby skończyć na twoim miejscu.","Widzę... Bóg trzyma każde życie, tylko że jest zbyt zajęty, by pamiętać o wszystkich.","Rzeczywiście. Człowiek proponuje, ale Bóg rozporządza.");
			link.l1.go = "ShipWreck_5";	
		break;
		
		case "ShipWreck_4":
			dialog.text = "Oczywiście, że nie! Wielu odmówiło przyłączenia się do buntowników, ale ci łajdacy zdobyli arsenał, i dobrze, że nie stawialiśmy oporu, bo inaczej by nas po prostu zabili. Wielu już tutaj padło ofiarą gorączki i trucizn od jadowitych owadów, tylko "+ShipWreck_GetStringQty(sti(pchar.GenQuest.ShipWreck.Qty))+"przetrwałem. Dzięki Bogu, nasze próby wreszcie się skończyły.";
			link.l1 = RandPhraseSimple("Tak, to z pewnością było uderzenie pecha.","O cóż, wiele dziwnych rzeczy może się zdarzyć w tych przez Boga zapomnianych miejscach.");
			link.l1.go = "ShipWreck_5";			
			link.l2 = "Zaczekaj, przyjacielu. A skąd mam wiedzieć, że nie wysadzono cię jako podżegaczy buntu?";
			link.l2.go = "ShipWreck_6";			
		break;
		
		case "ShipWreck_5":
			dialog.text = RandPhraseSimple("Kapitanie, mam nadzieję, że masz kilka wolnych schowków na swoim statku. Wszyscy mamy rodziny, które prawdopodobnie opłakują naszą stratę, podczas gdy my rozmawiamy. Bylibyśmy Ci bardzo wdzięczni.","Kapitanie, jesteśmy całkowicie zdesperowani, jesteś naszą jedyną nadzieją. Proszę, nie odmawiaj nam swojej pomocy, zabierz nas z tej przeklętej ziemi.");
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.ShipWreck.Qty) && GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l1 = "Ohh... a dokąd chcesz, żebym cię zabrał?";
				link.l1.go = "ShipWreck_7";			
			}
			link.l2 = RandPhraseSimple(RandPhraseSimple("Naprawdę przepraszam, ale nie ma ani jednej wolnej koi, nie wspominając o kajutach. Marynarze śpią na pokładzie, nie mogą nawet porządnie odpocząć po wachcie...","Naprawdę nie chciałbym cię rozczarować, ale statek jest przeładowany, a ludzie muszą spać w złej pogodzie. Gdyby wybuchła choroba, stracę połowę załogi."),RandPhraseSimple("Naprawdę przepraszam, ale na moim statku absolutnie nie ma wolnej przestrzeni dla załogi. Nie mogę wziąć na pokład więcej pasażerów.","Muszę cię rozczarować, ale mój statek jest przeciążony. Obawiam się epidemii."));
			link.l2.go = "ShipWreck_8";	
			if(stf(pchar.reputation.nobility) <= REPUTATION_NEUTRAL)
			{
				link.l3 = "Jesteś doświadczonym żeglarzem i powinieneś wiedzieć, że obecność kogoś, kto przeżył katastrofę morską, to bardzo zły znak. Moi marynarze po prostu wyrzucą was wszystkich za burtę.";
				link.l3.go = "ShipWreck_9";
			}
		break;
		
		case "ShipWreck_6":
			dialog.text = "Co ty mówisz, "+GetAddress_Form(npchar)+" "+pchar.lastname+"?! Zlituj się! Jestem negocjantem, znanym w Karaibach! Cóż... Myślę, że kiedyś nim byłem. Teraz nie, bez statku czy pieniędzy...";
			link.l1 = "Jak to... Założę się, że to wy byliście prawdziwymi podżegaczami buntu, a teraz macie to, na co zasłużyliście.";
			link.l1.go = "ShipWreck_18";
			if(GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l2 = "Ale co za łajdak to "+pchar.GenQuest.ShipWreck.BadName+" ! Naprawdę pozwolisz mu na to i poddasz się swojemu losowi?";
				link.l2.go = "ShipWreck_19";
			}	
		break;		
		
		case "ShipWreck_7":
			if(rand(1) == 0)
			{
				if(rand(100) < 90)
				{
					pchar.GenQuest.ShipWreck.variant = "1";
					dialog.text = "Do dowolnej osady "+NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation))+".";
					link.l1 = "Cóż, mam wystarczająco wolnych schowków i hamaków. Wpakuj się na łódź.";
					link.l1.go = "ShipWreck_10";
					link.l2 = "Hmm... Przed nami bitwy, i nie wiem, gdzie będziesz bardziej bezpieczny, na pokładzie mojego statku czy w tej przytulnej zatoce.";
					link.l2.go = "ShipWreck_11";
				}
				else
				{				
					dialog.text = "Do Dunkierki! Moja mama tam mieszka...";
					link.l1 = "Jesteś szalony czy co?! Wydaje mi się, że dostałeś za dużo ciosów w głowę...";
					link.l1.go = "ShipWreck_12";					
					pchar.GenQuest.ShipWreck.Crazy = true; // получите психа на борт :-)
					
				}				
			}
			else
			{
				pchar.GenQuest.ShipWreck.variant = "2";
				dialog.text = "Dokąd tylko chcesz, to dla nas bez znaczenia. I tak nie mamy czym ci zapłacić...";
				link.l1 = "Cóż, mam wystarczająco dużo wolnych szafek i hamaków. Załaduj się do łodzi.";
				link.l1.go = "ShipWreck_10_1";
				link.l2 = "Hmm... Przed nami bitwy, a ja nie wiem, gdzie będziesz bardziej bezpieczny, na pokładzie mojego statku czy w tej przytulnej zatoczce.";
				link.l2.go = "ShipWreck_11";		
			}						
		break;		

		case "ShipWreck_8":
			pchar.GenQuest.ShipWreck.FoodQty = sti(pchar.GenQuest.ShipWreck.Qty) * 10 + rand(10);
			pchar.GenQuest.ShipWreck.MedicamentQty = sti(pchar.GenQuest.ShipWreck.Qty) * 5 + rand(10);
			pchar.GenQuest.ShipWreck.AmunitionQty = sti(pchar.GenQuest.ShipWreck.Qty) * 3 + rand(5);
			pchar.GenQuest.ShipWreck.RumQty = sti(pchar.GenQuest.ShipWreck.Qty) * 7 + rand(10);
			if(GetFreeCrewQuantity(pchar) < sti(pchar.GenQuest.ShipWreck.Qty))
			{
				if(GetSquadronGoods(pchar, GOOD_FOOD) < sti(pchar.GenQuest.ShipWreck.FoodQty) || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < sti(pchar.GenQuest.ShipWreck.MedicamentQty))
				{
					dialog.text = "Ale odmawiając, z pewnością skazujesz nas na śmierć! Cóż, spróbujemy przebić się do statku, nawet jeśli będzie to kosztować nas życie!";
					link.l1 = "Co? Spójrzcie na siebie, ledwo stoicie na nogach...";
					link.l1.go = "ShipWreck_8_1";
					link.l2 = "Możesz spróbować...";
					link.l2.go = "ShipWreck_16";
				}
				else
				{
					dialog.text = "Ale nie możesz nas tu zostawić! Bez twojej pomocy wszyscy wkrótce zginiemy!";
					if(GetSquadronGoods(pchar, GOOD_WEAPON) < sti(pchar.GenQuest.ShipWreck.AmunitionQty) || GetSquadronGoods(pchar, GOOD_RUM) < sti(pchar.GenQuest.ShipWreck.RumQty))
					{			
						link.l1 = "Jedyne, co mogę dla ciebie zrobić, to zostawić ci wystarczająco dużo prowiantu i medykamentów oraz dać ci łódź. Przynajmniej nie umrzesz z głodu i pragnienia. Co do żeglugi, nie muszę cię tego uczyć.";
						link.l1.go = "ShipWreck_8_2";
					}
					else
					{
						if(rand(1) == 0)
						{
							link.l1 = "Jedyne, co mogę dla ciebie zrobić, to zostawić ci wystarczająco prowiantu i lekarstw oraz dać ci łódź. Przynajmniej nie umrzesz z głodu i pragnienia. Co do żeglarstwa, nie muszę cię tego uczyć.";
							link.l1.go = "ShipWreck_8_2";
						}
						else
						{
							link.l1 = "Mogę zostawić ci wystarczająco lekarstw, amunicji, rumu i zapasów na miesiąc. Albo wrócę sam, albo przyślę kogoś po ciebie.";
							link.l1.go = "ShipWreck_8_4";
						}
					}
				}
			}
			else
			{
				if(stf(pchar.reputation.nobility) <= REPUTATION_NEUTRAL) // плохиш
				{
					if(GetSquadronGoods(pchar, GOOD_FOOD) < sti(pchar.GenQuest.ShipWreck.FoodQty) || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < sti(pchar.GenQuest.ShipWreck.MedicamentQty))				
					{
						dialog.text = "   Ale odmawiając, z pewnością skazujesz nas na śmierć! Cóż, spróbujemy przebić się do statku, nawet jeśli to nas kosztuje życie!   ";
						link.l1 = "Co? Spójrzcie na siebie, ledwo stoicie na nogach...";
						link.l1.go = "ShipWreck_8_1";
						link.l2 = "Możesz spróbować...";
						link.l2.go = "ShipWreck_16";					
					}
					else
					{
						link.l1 = "The only thing I can do for you is leave you enough provisions and medicines and give you a boat. At least you are not going to die of starvation and thirst; as for seafaring, I need not teach you that.";
						link.l1.go = "ShipWreck_8_2";					
					}
				}
				else // кибальчиш
				{
					if(GetSquadronGoods(pchar, GOOD_FOOD) < sti(pchar.GenQuest.ShipWreck.FoodQty) || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < sti(pchar.GenQuest.ShipWreck.MedicamentQty))				
					{
						if(rand(1) == 0)
						{
							dialog.text = "   Ale odmawiając, z pewnością skazujesz nas na śmierć!   Cóż, spróbujemy przebić się do statku, nawet jeśli to nas kosztuje życie!";
							link.l1 = "Co? Spójrzcie na siebie, ledwie stoicie na nogach...";
							link.l1.go = "ShipWreck_8_1";
							link.l2 = "Możesz spróbować...";
							link.l2.go = "ShipWreck_16";						
						}
						else
						{
							dialog.text = "Jak mogłeś to nam zrobić?!.. Nie tylko zlekceważyłeś Kodeks Morski, ale także splamiłeś swój honor!";
							link.l1 = "Z pewnością nie ty masz prawo mówić o moim honorze, karzełku!";
							link.l1.go = "ShipWreck_16";
						}	
					}
					else
					{
						link.l1 = "Jedyne, co mogę dla ciebie zrobić, to zostawić ci wystarczające zapasy i lekarstwa oraz dać ci łódź. Przynajmniej nie umrzesz z głodu i pragnienia. Co do żeglugi, nie muszę cię tego uczyć.";
						link.l1.go = "ShipWreck_8_2";											
					}						
				}
			}			
		break;				
	
		case "ShipWreck_8_1":
			dialog.text = "Masz rację, nie mamy szans. Dobrze, niech Bóg będzie twoim sędzią, a każdy niech otrzyma to, na co zasługuje.";
			link.l1 = "Cóż, mogę się tym zająć...";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			AddDialogExitQuestFunction("ShipWreck_DialogDisable");
		break;
	
		case "ShipWreck_8_2":
			dialog.text = "Cóż... Nie zostawiasz nam wyboru... Będziemy się modlić, aby burze i pragnienie nie zabrały naszego życia, zanim dotrzemy do zamieszkałych miejsc...";
			link.l1 = "Żegnaj. Niech Pan ma cię w opiece...";
			link.l1.go = "ShipWreck_8_3";
		break;
		
		case "ShipWreck_8_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddCharacterExpToSkill(pchar, "Leadership", 25);
			RemoveCharacterGoods(pchar, GOOD_FOOD, sti(pchar.GenQuest.ShipWreck.FoodQty));
			RemoveCharacterGoods(pchar, GOOD_MEDICAMENT, sti(pchar.GenQuest.ShipWreck.MedicamentQty));			
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.FoodQty + " units of provision.");
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.MedicamentQty + "units of medicine.");
			DialogExit();
			NextDiag.TempNode = "ShipWreck_8_7";
			NextDiag.CurrentNode = NextDiag.TempNode;			
		break;
	
		case "ShipWreck_8_4":	
			dialog.text = "Najwyraźniej nie mamy wyboru... Ale błagam cię, kapitanie, wróć jak najszybciej lub wyślij do nas statek ekspedycyjny.";
			link.l1 = "Wymyślę coś. Po prostu czekaj.";
			link.l1.go = "ShipWreck_8_5";
		break;
	
		case "ShipWreck_8_5":		
			pchar.quest.ShipWreck_LocationExit.over = "yes";
			AddCharacterExpToSkill(pchar, "Leadership", 50); 
			RemoveCharacterGoods(pchar, GOOD_FOOD, sti(pchar.GenQuest.ShipWreck.FoodQty));
			RemoveCharacterGoods(pchar, GOOD_MEDICAMENT, sti(pchar.GenQuest.ShipWreck.MedicamentQty));			
			RemoveCharacterGoods(pchar, GOOD_WEAPON, sti(pchar.GenQuest.ShipWreck.AmunitionQty));
			RemoveCharacterGoods(pchar, GOOD_RUM, sti(pchar.GenQuest.ShipWreck.RumQty));			
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.FoodQty + " units of provision.");
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.MedicamentQty + "units of medicine.");		
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.AmunitionQty + " units of arms.");
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.RumQty + " units of rum");	
			ReOpenQuestHeader("ShipWrecked");
			if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
			{
				AddQuestRecord("ShipWrecked", "11");
				AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);			
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			else
			{
				AddQuestRecord("ShipWrecked", "10");
				AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			DialogExit();
			NextDiag.TempNode = "ShipWreck_8_6";
			NextDiag.CurrentNode = NextDiag.TempNode;	
			pchar.GenQuest.ShipWreck = "SailorsOnShore";
			SetFunctionTimerCondition("ShipWreck_SaveSailors", 0, 0, 30, false);
			pchar.GenQuest.ShipWreck.Shore = pchar.location;
			SaveCurrentQuestDateParam("GenQuest.ShipWreck");
			SetFunctionLocationCondition("ShipWreck_MeetInShore", pchar.GenQuest.ShipWreck.Shore, true);
		break;
	
		case "ShipWreck_8_6":			
			dialog.text = RandPhraseSimple("Kapitanie, proszę pamiętaj, że jesteś naszą jedyną nadzieją...","Po co się tak ociągasz? Każda minuta spędzona tutaj jest dla nas nie do zniesienia...");
			link.l1 = "Zrobię wszystko, co w mojej mocy. Żegnaj...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_8_6";		
		break;

		case "ShipWreck_8_7":			
			dialog.text = RandPhraseSimple("Żegnaj, kapitanie... Musimy się przygotować do podróży.","Żegnaj... I zapal świece, by ocalić nasze dusze...");
			link.l1 = "Żegnaj. Niech Pan nad tobą czuwa...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_8_7";		
		break;
		
		case "ShipWreck_9":
			pchar.GenQuest.ShipWreck = "SailorsOnShoreFight"; // belamour gen
			dialog.text = "Jak mogłeś nam to zrobić?! Nie tylko zlekceważyłeś Kodeks Morski, ale także splamiłeś swój honor!";
			link.l1 = "Na pewno nie ty masz prawo mówić o mojej honorze, krewetko!";
			link.l1.go = "ShipWreck_16";
		break;					
		
		case "ShipWreck_10":
			dialog.text = "Dziękuję, kapitanie! Załadunek nie powinien zająć zbyt wiele czasu. Boże, jakże modliliśmy się, by ten moment nadszedł!";
			link.l1 = "To świetnie. Mam nadzieję, że twoje próby wkrótce się skończą.";
			link.l1.go = "ShipWreck_13";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Nation_City";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.nation = sti(pchar.GenQuest.ShipWreck.Nation);
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";
			ReOpenQuestHeader("ShipWrecked");
			if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
			{
				AddQuestRecord("ShipWrecked", "2");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				// --> belamour окончание по количеству персон
				if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailors");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailor");
				}
				// <-- belamour
				AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			else
			{
				AddQuestRecord("ShipWrecked", "1");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				// --> belamour окончание по количеству персон
				if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailors");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailor");
				}
				// <-- belamour
				AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
				// --> belamour: нужно разделить, иначе получается с потерпевшего крушение бригантины 
				if(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_SCHOONER_W")
				{
					AddQuestUserData("ShipWrecked", "sText", "wrecked");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "sText", "wrecked");
				}
				// <-- belamour
			}
			
		break;							

		case "ShipWreck_10_1":
			dialog.text = "Dziękujemy, kapitanie! Załadunek nie powinien zająć zbyt wiele czasu. Boże, jakże modliliśmy się, by ten moment nadszedł!";
			link.l1 = "To wspaniale. Mam nadzieję, że twoje próby wkrótce się skończą.";
			link.l1.go = "ShipWreck_13";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";
			ReOpenQuestHeader("ShipWrecked");
			if(CheckAttribute(pchar,"GenQuest.ShipWreck.Mutiny"))
			{
				AddQuestRecord("ShipWrecked", "4");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
				// --> belamour окончание по количеству персон
				if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailors");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailor");
				}
				// <-- belamour
			}
			else
			{
				AddQuestRecord("ShipWrecked", "3");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				// --> belamour окончание по количеству персон
				if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailors");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailor");
				}
				// <-- belamour
				AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);
				// --> belamour: нужно разделить, иначе получается с потерпевшего крушение бригантины 
				if(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_SCHOONER_W")
				{
					AddQuestUserData("ShipWrecked", "sText", "wrecked");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "sText", "wrecked");
				}
				// <-- belamour
			}			
		break;							
				
		case "ShipWreck_11":
			dialog.text = "Chodźże! Naprawdę, kapitanie?! Czyżbyśmy bali się śmierci?! Oszukaliśmy ją raz, możemy zrobić to ponownie. Po prostu nie chcemy stracić życia w taki sposób. Gnić tutaj, sami\nZ radością dołączylibyśmy do twojej załogi i walczyli pod twoją banderą dzielnie. Tylko nie zostawiaj nas tu...";
			link.l1 = "Widzę, że jesteście gotowi zrobić wszystko, byle tylko stąd się wydostać. Ale spójrzcie na siebie, jakimi wy możecie być żeglarzami?";
			link.l1.go = "ShipWreck_14";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.ShipWreck.Qty))
			{
				link.l2 = "To dobry pomysł. Przypuszczam, że mogę cię zatrudnić.";
				link.l2.go = "ShipWreck_15";
			}	
		break;									
		
		case "ShipWreck_12":
			dialog.text = "Nie-nie, nie żartuję! Proszę, zabierz mnie z tej karaibskiej rzeźni... z tego piekła! Wiesz, jestem bogatym człowiekiem... bardzo bogatym człowiekiem. Nawet sam papież nie widział tyle złota przez całe swoje życie. Zasypię cię złotem...";
			link.l1 = "O mój... Dobrze, wsiadaj do łodzi...";
			link.l1.go = "ShipWreck_13";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";			
			ChangeOfficersLoyality("bad_all", 1);
			ReOpenQuestHeader("ShipWrecked");
			AddQuestRecord("ShipWrecked", "5");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
			AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty);
			AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Gen"))); // belamour gen
			AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);	
			// --> belamour: нужно разделить, иначе получается с потерпевшего крушение бригантины
			if(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_SCHOONER_W")
			{
				AddQuestUserData("ShipWrecked", "sText", "wrecked");
			}
			else
			{
				AddQuestUserData("ShipWrecked", "sText", "wrecked");
			}
			// <-- belamour
		break;							

		case "ShipWreck_13": // берем пассажирами
			pchar.GenQuest.ShipWreck = "SailorsSaved";
			//Achievment_SetStat(29, sti(pchar.GenQuest.ShipWreck.Qty));
			if(CheckAttribute(pchar,"GenQuest.ShipWreck.variant"))
			{
				if(pchar.GenQuest.ShipWreck.variant == "1") ChangeCharacterComplexReputation(pchar,"nobility", 1);			
				if(pchar.GenQuest.ShipWreck.variant == "2") ChangeCharacterComplexReputation(pchar,"nobility", 2);			
			}	
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				if(i == 0) 
				{
					AddPassenger(pchar, rChar, false);
					SetCharacterRemovable(rChar, false);	
				}
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.Dialog.currentnode = "ShipWreck_13_again";
			}
			DialogExit();
		break;
		
		case "ShipWreck_13_again":
			dialog.text = LinkRandPhrase("Czemu się ociągasz, kapitanie? Rozkaż podnieść kotwicę.","Przykro nam, kapitanie, ale musimy się przygotować do wypłynięcia.","Jesteśmy tak szczęśliwi, że zdecydowałeś się tu przybyć!");
			link.l1 = "Pospiesz się. Statek nie będzie na nikogo czekał.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_13_again";		
		break;
		
		case "ShipWreck_14":
			dialog.text = "Kapitanie, nie mamy nic do stracenia. Śmierć już depcze nam po piętach... Wolimy zginąć w uczciwej walce, niż zostać pożarci przez śmierdzące kojoty...";
			link.l1 = "O, to wyzwanie, co?! Dobrze, rozstrzygnijmy nasze spory"+GetSexPhrase(", jak ludzie","")+"!";
			link.l1.go = "ShipWreck_16";
			AddDialogExitQuest("MainHeroFightModeOn"); 
		break;		
		
		case "ShipWreck_15":
			dialog.text = "Przysięgam, kapitanie, nie pożałujesz tego. Będziemy najlepszymi żeglarzami w całym archipelagu.";
			link.l1 = "Świetnie! Wsiadaj do łodzi...";
			link.l1.go = "ShipWreck_17";			
		break;				
		
		case "ShipWreck_16":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				LAi_SetImmortal(rChar, false);
				if(CheckPassengerInCharacter(pchar, "ShipWreck_" + i)) 
				{
					RemovePassenger(pchar, rChar);
				}
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, "ShipWreckGroup");
			}

			LAi_Group_SetRelation("ShipWreckGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("ShipWreckGroup", LAI_GROUP_PLAYER, true);
			if(pchar.GenQuest.ShipWreck == "fight" || pchar.GenQuest.ShipWreck == "SailorsOnShoreFight") // belamour gen
			{
				LAi_group_SetCheck("ShipWreckGroup", "OpenTheDoors"); 
				LAi_group_SetCheckFunction("ShipWreckGroup", "ShipWreck_AfterBattle");
			}	
			DialogExit();		
		break;
		
		case "ShipWreck_17": // принимаем в команду
			if(pchar.GenQuest.ShipWreck.variant == "1") ChangeCharacterComplexReputation(pchar,"nobility", 1);			
			if(pchar.GenQuest.ShipWreck.variant == "2") ChangeCharacterComplexReputation(pchar,"nobility", 2);			
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.LifeDay = 0;			
				rChar.Dialog.currentnode = "ShipWreck_17_again";
			}
			AddCharacterCrew(pchar, sti(pchar.GenQuest.ShipWreck.Qty));
			// --> belamour gen по количеству персон
			if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5) sText = "";	
			else sText = "";
			Log_Info("Your team has increased by " + pchar.GenQuest.ShipWreck.Qty + " man" + sText + ".");
			// <-- belamour gen 
			Achievment_SetStat(29, sti(pchar.GenQuest.ShipWreck.Qty));
			pchar.quest.ShipWreck_LocExit.over = "yes"; // Снимаем прерывание на выход из локации			
			DeleteAttribute(pchar, "GenQuest.ShipWreck");			
			AddCharacterExpToSkill(pchar, "Leadership", 50); 			
			DialogExit();
		break;

		case "ShipWreck_17_again":
			dialog.text = LinkRandPhrase("Przysięgam, kapitanie, nie pożałujesz tego.","Dokonałeś właściwego wyboru, kapitanie.","Kapitanie, bądź pewien, że miałeś tyle samo szczęścia, co my!");
			link.l1 = RandPhraseSimple("Mam nadzieję.","Pośpiesz się. Statek nie będzie czekał na nikogo.");
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_17_again";
		break;
		
		case "ShipWreck_18":
			dialog.text = "Kapitanie, dlaczego obrażasz uczciwych ludzi takim brakiem zaufania? Spójrz tylko na ich twarze, naprawdę myślisz, że mogliby być buntownikami?";
			link.l1 = "Dobrze, ale co ja mam teraz z tobą zrobić?";
			link.l1.go = "ShipWreck_20";
		break;
		
		case "ShipWreck_19":
			dialog.text = "A co mogę zrobić? Przynajmniej teraz żyję... i dziękuję Bogu, że udało mi się uciec! Ale jeśli pomożesz mi odzyskać mój statek i zemścić się za moje upokorzenie, jestem gotów dać ci wszystko, co ten łajdak ukradnie i schowa w ładowni.";
			link.l1 = "Dobrze, mamy umowę.";
			link.l1.go = "ShipWreck_13";
			ShipWreck_SetCapToMap();
			SetFunctionTimerCondition("prosralisrok", 0, 0, 180, false); // таймер лесник тамймер на поиск корабля 																																   
			ReOpenQuestHeader("ShipWrecked");
			AddQuestRecord("ShipWrecked", "16");
			AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			// --> belamour окончание по количеству персон
			if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
			{
				AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " his sailors");
			}
			else
			{
				AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " his sailor");
			}
			// <-- belamour
			AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
			AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);	
		break;
		
		case "ShipWreck_20":
			dialog.text = "Nie jesteśmy w stanie wydawać żadnych rozkazów. To zależy od ciebie, po prostu zabierz nas do jakiejkolwiek osady lub przyjmij nas do swojej załogi.";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.ShipWreck.Qty))
			{
				link.l1 = "Dobrze, przyjmę cię do mojej załogi. Ale żadnych głupstw! Na moim statku panuje surowa dyscyplina!";
				link.l1.go = "ShipWreck_17";
			}
			link.l2 = "Nie zabieram cię nigdzie. Już mam wystarczająco dużo zbirów w mojej załodze.";	
			link.l2.go = "ShipWreck_22";
			link.l3 = "Dobrze, wsiadaj do łodzi, zabiorę cię gdzieś.";
			link.l3.go = "ShipWreck_10_1";
		break;		
		
		case "ShipWreck_22":
			dialog.text = "No cóż... Nie pozostawiasz nam wyboru... Będziemy modlić się, aby Opatrzność okazała nam łaskę i pozwoliła wydostać się z tego niebezpiecznego miejsca. Jeśli Bóg pozwoli, możemy jeszcze dotrzeć do zamieszkanej ziemi...";
			link.l1 = "Żegnaj. Niech Pan czuwa nad tobą...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ShipWreck_DialogDisable");
		break;		
		
		case "ShipWreck_30":
			if(pchar.GenQuest.ShipWreck == "SailorsSaved")
			{
				dialog.text = "Dziękuję bardzo, kapitanie "+GetFullName(pchar)+"Zrobiłeś dla nas tak wiele, że żadna wdzięczność nie wystarczy, by Ci się odwdzięczyć. I choć wszystkie nasze dobra nie są warte miedziaka, pozwól mi wręczyć Ci ten amulet. Będzie bardzo przydatny dla kapitana, który często bierze udział w bitwach morskich.";
				link.l1 = "Dziękuję za twój dar! Ta błyskotka jest naprawdę bardzo przydatna! Żegnaj, kapitanie "+pchar.GenQuest.ShipWreck.Name+" i powodzenia na twych podróżach.";
				link.l1.go = "ShipWreck_47";
			}
			else
			{
				dialog.text = "Kapitanie, dziękujemy bardzo. Zrobiłeś dla nas wiele, a każda nagroda byłaby niczym w porównaniu z naszą wdzięcznością. Proszę, przyjmij ten skromny dar jako wyraz naszej wdzięczności.";
				link.l1 = "Naprawdę, nie powinieneś się kłopotać... Bardziej potrzebujesz pieniędzy niż ja. Mimo to, to bardzo miłe z twojej strony. Dziękuję i żegnaj.";
				link.l1.go = "ShipWreck_31";
			}	
		break;
		
		case "ShipWreck_31":
			//addMoneyToCharacter(pchar, sti(pchar.rank) * 200 + rand(2000));
			AddCharacterExpToSkill(pchar, "Commerce", 50);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			TakeNItems(pchar, "jewelry2", 15+hrand(10));
			AddQuestRecord("ShipWrecked", "6");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony"+ Locations[FindLocation(PChar.location)].townsack + "Acc"));
			CloseQuestHeader("ShipWrecked");
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_32":	
			dialog.text = "Kapitanie, wiedz, że od teraz są ludzie, którzy poszliby na koniec świata dla ciebie. Szkoda, że nie mam nic, czym mógłbym Ci podziękować. Niemniej... Proszę, przyjmij ten drobiazg, znalazłem go w tej nieszczęsnej zatoce. Mam nadzieję, że przyniesie Ci szczęście.";
			link.l1 = "Każdy na moim miejscu zrobiłby to samo. Żegnaj.";
			link.l1.go = "ShipWreck_33";
		break;
		
		case "ShipWreck_33":
			GiveItem2Character(pchar, pchar.GenQuest.ShipWreck.Prize);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddQuestRecord("ShipWrecked", "6");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony" + Locations[FindLocation(PChar.location)].townsack + "Acc")); // belamour gen: просто pchar.location ничего не даст
			CloseQuestHeader("ShipWrecked");		
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_34":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Kapitanie, czy to już Dunkierka?","Naprawdę jesteśmy w Dunkierce, kapitanie?"),RandPhraseSimple("Kapitanie, czy to Europa?","Czyżbyśmy tak szybko dopłynęli do Europy?"));
			bTemp = !GetCharacterItem(pchar, "map_full") && !GetCharacterItem(pchar, "map_part2");
			bTemp = !GetCharacterItem(pchar, "map_part1") || bTemp;
			if(rand(100) > 75 && !isDay() && bTemp)
			{
				link.l1 = "A-ha...";
				link.l1.go = "ShipWreck_40";
			}
			else
			{
				link.l1 = LinkRandPhrase("Jeszcze nie...","Jaki Dunkierka? Jaka Europa? Rozejrzyj się!","O mój Boże!");
				link.l1.go = "ShipWreck_35";
			}
		break;
		
		case "ShipWreck_35":
			dialog.text = LinkRandPhrase("Ale, kapitanie, złożyłeś obietnicę!","Jak mogłeś złamać swoje słowo, kapitanie?","Kiedy dostaniemy się do Europy?");
			if(rand(100) < 70)
			{
				link.l1 = "Dobrze. Panie, zbierz swoich ludzi i dobytek, i idź, dokąd zechcesz.";
				link.l1.go = "ShipWreck_36";
			}
			link.l2 = RandPhraseSimple(LinkRandPhrase("Jesteś pewien, że naprawdę musimy dostać się do Dunkierki?","Wiesz, mój statek nie jest przeznaczony do żeglowania przez ocean.","Kapitanie, a co nie tak z Karaibami?"),LinkRandPhrase("Ale miałem inne plany...","Dlaczego w pierwszej kolejności chcesz jechać do Europy...","Pomyśl tylko o tych uwodzicielskich mulatkach! Nigdy nie spotkasz ich w Europie..."));
			link.l2.go = "ShipWreck_37";	
		break;
		
		case "ShipWreck_36":
			pchar.quest.ShipWreck_DeliveToCity.over = "yes";
			pchar.GenQuest.ShipWreck = "fight";
			dialog.text = "Jak to możliwe?.. Jak śmiesz?! Co to za zdrada?! Nauczę cię, jak dotrzymywać słowa!";
			link.l1 = "Cóż, sam się o to prosiłeś...";
			link.l1.go = "ShipWreck_16";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			AddDialogExitQuest("MainHeroFightModeOn"); 
		break;
		
		case "ShipWreck_37":
			dialog.text = LinkRandPhrase(RandPhraseSimple("Nie! Muszę dostać się do Dunkierki!","Zamiast uczyć mnie geografii, powinieneś raczej wypełnić swoje zobowiązanie!"),RandPhraseSimple("Nie chcę o tym słyszeć! Obiecałeś mi, że zabierzesz mnie do Europy!","Nie, kapitanie, to nie przejdzie. Płyniemy do Europy."),"Nie zamierzam prowadzić nędznego życia do końca moich dni w tej dziurze!");
			link.l1 = "Och, nie wiem, czy to się dobrze skończy...";
			link.l1.go = "ShipWreck_38";
		break;		
		
		case "ShipWreck_38":
			chrDisableReloadToLocation = false;			
			SetFunctionExitFromLocationCondition("ShipWreck_ExitFromTown", pchar.location, false);				
			if(!CheckAttribute(pchar,"GenQuest.ShipWreck.CrazyRec")) // mitrokosta исправлена блокировка поручения капитана
			{
				pchar.GenQuest.ShipWreck.CrazyRec = true;
				AddQuestRecord("ShipWrecked", "7");
			}
			DialogExit();
		break;
		
		case "ShipWreck_40":
			pchar.quest.ShipWreck_DeliveToCity.over = "yes";
			dialog.text = "Widzisz! To jest przyzwoity człowiek! Europa! Krwawa stara Europa! Tak-tak-tak!\nOch, tak! Spełniłeś swoją część umowy, więc i ja spełnię swoją. Oto, weź tę połowę mapy. Drugą połowę miał mój partner. Spoczywaj w pokoju, czy spoczywaj w wodzie? Nieważne. To on mnie namówił, by wziąć udział w tej przygodzie.";
			link.l1 = "Zaraz, to nie jesteś marynarzem? Twój towarzysz był kapitanem?";
			link.l1.go = "ShipWreck_41";
		break;
		
		case "ShipWreck_41":
			dialog.text = "O mój Boże!.. Oczywiście, że nie! Cóż, tak, nie jestem marynarzem. I został zmieciony za burtę przez ogromną falę, kiedy postanowił odpłynąć dalej od brzegu. Potem przejąłem dowodzenie i rozkazałem wpłynąć do zatoki... I dobrze nam szło, przeciskając się przez rafy, aż wszystko przesądził fatalny przypadek. Statek uderzył o kawałek skały i poszedł na dno...";
			link.l1 = "To dopiero prawdziwy pokaz niekompetencji...";
			link.l1.go = "ShipWreck_42";
		break;
		
		case "ShipWreck_42":
			dialog.text = "Słuchaj, czy to naprawdę Dunkierka? Pomyśl tylko, minęło zaledwie sześć miesięcy, a całe miejsce się zmieniło\nTutaj, weź mapę, a konkretnie jej część. Skarb jest wewnątrz jaskini! Nie mam pojęcia, jaka to wyspa, ale jesteś doświadczonym żeglarzem, pewnego dnia znajdziesz dokładną lokalizację... Gwarantuję, że są tam niezliczone bogactwa pirata o imieniu aaarrrrrhg...";
			link.l1 = "Dziękuję, mój dobry człowieku. Nawet jeśli nie będzie żadnego skarbu, nie będę zbyt zasmucony. Żegnaj, i mam nadzieję, że nigdy więcej się nie zobaczymy...";
			link.l1.go = "ShipWreck_43";
		break;
		
		case "ShipWreck_43":
			sld = CharacterFromID("ShipWreck_0");
			RemovePassenger(pchar, sld);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			AddMapPart();
			AddQuestRecord("ShipWrecked", "9");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("ShipWrecked");	
			AddSimpleRumourCity(LinkRandPhrase(RandPhraseSimple("They say some loony recently showed up on the island. He is telling everyone that he had lost his documents, and no he's attempting to apply for a captain on a ship to Dunkirk.",
				"They say some maniac recently showed up on the island. He stole a spade at the local shop and now is digging a pit past the town gates..."),
				RandPhraseSimple("Just imagine, recently some visiting European in worn and dirty clothes attempted to get an audience with the governor! He claimed that he needed to see the governor of Dunkirk ass soon as possible.",
				"There was a scandal at the town hall recently. Some vagrant was caught, he claimed that he personally knew the governor of Dunkirk."),
				"Some psycho was looking for you recently. He claimed that you owed him money..."), pchar.location, 5, 3,"");
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_44":
			dialog.text = RandPhraseSimple("Kapitanie, to wspaniale, że nas nie zapomniałeś! Wszyscy modliliśmy się za ciebie!","Kapitanie, czy nasze zbawienie jest blisko? Jakże modliliśmy się, żeby nadeszło! Niektórzy już zaczęli tracić nadzieję...");
			link.l1 = "Witaj, "+pchar.GenQuest.ShipWreck.Name+"! Jak mógłbym opuścić moich towarzyszy w takim stanie? Dokąd?";
			link.l1.go = "ShipWreck_45";
			link.l2 = "Witaj, "+pchar.GenQuest.ShipWreck.Name+"Obawiam się, że mam dla ciebie złe wieści. Nastąpiła zmiana planów i nie będę mógł cię zabrać na pokład.";
			link.l2.go = "ShipWreck_9";
		break;
		
		case "ShipWreck_45":
			dialog.text = "Nie obchodzi nas, dokąd płyniemy, byleby było daleko od tego przeklętego miejsca... Pozwolisz nam zacząć się załadowywać?";
			link.l1 = "Tak, śmiało z tym. Wkrótce twoje próby się skończą.";
			link.l1.go = "ShipWreck_46";
		break;

		case "ShipWreck_46":
			ChangeCharacterComplexReputation(pchar,"nobility", 4);			
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				if(i == 0) 
				{
					AddPassenger(pchar, rChar, false);
					SetCharacterRemovable(rChar, false);	
				}
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.dialog.currentnode = "ShipWreck_13_again";
			}			
			pchar.quest.ShipWreck_SaveSailors.over = "yes"; // belamour gen снять таймер на 30 дней	 
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";			
			pchar.GenQuest.ShipWreck = "SailorsSaved";
			if(CheckAttribute(pchar,"GenQuest.ShipWreck.Mutiny")) DeleteAttribute(pchar,"GenQuest.ShipWreck.Mutiny"));
			SetFunctionExitFromLocationCondition("ShipWreck_LocationExit", pchar.location, false);				
			DialogExit();			
		break;

		case "ShipWreck_47":
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			GiveItem2Character(pchar, "indian_10");
			AddQuestRecord("ShipWrecked", "15");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			CloseQuestHeader("ShipWrecked");				
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_48":
			dialog.text = "Dziękujemy, kapitanie. Zaczęliśmy już tracić nadzieję, ale dosłownie przywróciłeś nas do życia.";
			link.l1 = "To było nic... Żegnaj.";
			link.l1.go = "ShipWreck_49";
		break;
		
		case "ShipWreck_49":
			AddQuestRecord("ShipWrecked", "17");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("ShipWrecked");								
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_50":
			dialog.text = "Czego do cholery chcesz ode mnie?";
			link.l1 = "Przybyłem"+GetSexPhrase("","")+" przesłać ci pozdrowienia od osoby imieniem"+pchar.GenQuest.ShipWreck.Name+" Czy go znasz?"; // belamour gen
			link.l1.go = "ShipWreck_51";
		break;
		
		case "ShipWreck_51":
			dialog.text = "Szkoda, że wcześniej nie udusiłem tego łajdaka. No cóż, chyba nadszedł czas, by zapłacić za moją dobroć...";
			link.l1 = "Rzeczywiście... I właśnie czas się skończył...";
			link.l1.go = "ShipWreck_52";
		break;
		
		case "ShipWreck_52":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheckFunction(LAI_GROUP_BRDENEMY, "ShipWreck_afterCabinFight");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");				
		break;

		case "ShipWreck_53":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			pchar.quest.ShipWreck_ShipSink.over = "yes";
			dialog.text = "Wspaniała robota, kapitanie! Wszystko zgodnie z naszymi ustaleniami, prawda? My dostajemy statek, a ty ładunek?";
			link.l1 = "Pewnie. Weź statek i dobrze go wykorzystaj.";
			link.l1.go = "exit";

			NextDiag.TempNode = "ShipWreck_53_again";		
			AddDialogExitQuestFunction("ShipWreck_SetShipNew");
		break;
		
		case "ShipWreck_53_again":
			dialog.text = "Witam cię, kapitanie "+GetFullName(pchar)+".";
			link.l1 = "Jak ci się podoba twój statek?";
			link.l1.go = "ShipWreck_53_again1";
		break;
		
		case "ShipWreck_53_again1":
			dialog.text = "Heh, skrzypi i trzaska, tak jak ja sam. Myślę, że oboje nie mamy już dużo czasu na żeglowanie po morzach...";
			link.l1 = "Powodzenia zatem...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_53_again";		
		break;
		// Генератор "Shipwrecked"
		
		// Генератор "State convicts"
		case "Convict_0End":
			DialogExit();
			pchar.GenQuest.Convict = "close";
			chrDisableReloadToLocation = false;
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddDialogExitQuestFunction("Convict_DialogDisable");
		break;
		
		case "Convict_Begin":					
			switch(sti(pchar.GenQuest.Convict.var))
			{
				case 0:
					dialog.text = "Kapitanie, proszę, pomóż nam zdobyć statek lub długą łódź, tartanę, cokolwiek, to naprawdę nie ma znaczenia. Znajdujemy się w takich okolicznościach, że musimy uciekać z tego niegościnnego miejsca, ale nie możemy pojawić się w osadzie.";
					link.l1 = "A cóż to za okoliczności?";
					link.l1.go = "Convict_11";
				break;
				case 1:
					dialog.text = "Kapitanie, czy mógłbyś pożyczyć nam parę setek pesos? Nie prosilibyśmy, ale naprawdę jesteśmy w pilnej potrzebie.";
					link.l1 = "W potrzebie, mówisz? Założę się, że właśnie skończył ci się rum, a to z pewnością wielka potrzeba.";
					link.l1.go = "Convict_12";			
				break;
				case 2:
					pchar.GenQuest.Convict.ToCity = FindColonyWithMayakExceptIsland(GetCharacterCurrentIslandId(pchar));	
					pchar.GenQuest.Convict.Mayak = GetMayakByCityName(pchar.GenQuest.Convict.ToCity);
					dialog.text = "Kapitanie, czy mógłbyś być tak uprzejmy i zabrać naszą pokorną kompanię do latarni morskiej "+XI_ConvertString("Colony"+pchar.GenQuest.Convict.ToCity+"Gen")+".";
					link.l1 = "Patrząc na ciebie, nie powiedziałbym, że jesteś zbyt pokorny.";
					link.l1.go = "Convict_13";								
				break;
			}						
			link.l2 = LinkRandPhrase("Nie daję jałmużny w piątki.","Nie mam czasu na te bzdury.","Nie pomagam obcym ludziom.");
			link.l2.go = "Convict_14";
			Convict_GetMineType();
			pchar.GenQuest.Convict.ShoreLocation = SelectQuestShoreLocation();
		break;
		
		case "Convict_11":
			dialog.text = "Jesteśmy zbiegami... z "+GetStrSmallRegister(XI_ConvertString("TypKopalni"+pchar.GenQuest.Convict.MineType+"Dat"))+". Wkrótce były pan zauważy... a wtedy na pewno zginiemy.";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				link.l1 = "Więc wiesz, jak zarządzać żaglami?";
				link.l1.go = "Convict_11_1";
			}	
			link.l2 = "A czymże zamierzasz zapłacić?";
			link.l2.go = "Convict_11_2";
		break;
		
		case "Convict_12":
			dialog.text = "To nie jest dobry czas, by myśleć o rumie. Minął tydzień od naszej ucieczki, teraz ukrywamy się w dżungli i głodujemy.";
			if(sti(pchar.money) >= 3000)
			{
				link.l1 = "Cóż, przypuśćmy, że mogę dać ci pieniądze... i co wtedy? Zamierzasz się ukrywać, dopóki ostatecznie nie zostaniesz odkryty przez patrol?";
				link.l1.go = "Convict_12_1";		
				link.l2 = "Zatem, ile potrzebujesz?";
				link.l2.go = "Convict_12_2";
			}	
			link.l3 = "Krótko gadam z takimi jak ty, głowy na pniu kata, i tyle!";
			link.l3.go = "Convict_12_3";
		break;		
		
		case "Convict_12_1":
			if(hrand(1) == 0 && GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				dialog.text = "A co innego możemy zrobić? Chętnie zatrudnilibyśmy się jako marynarze, ale biorąc pod uwagę, że jesteśmy zbiegami, kto nas zatrudni?";
				link.l1 = "Zatrudnię cię, jeśli wiesz, jak zarządzać żaglami i nie okażesz oznak tchórzostwa.";
				link.l1.go = "Convict_12_1_1";
			}
			else
			{
				dialog.text = "Już doszliśmy do porozumienia z miejscowymi żeglarzami. Aby się stąd wydostać, brakuje nam tylko trzech tysięcy.";
				link.l1 = "Cóż, oto twoje trzy tysiące, jeśli to naprawdę ci pomoże.";
				link.l1.go = "Convict_12_1_2";
			}
			link.l2 = "Cóż, nie wiem... To są twoje własne problemy, i nie zamierzam pomagać ci w ich rozwiązaniu.";
			link.l2.go = "Convict_12_1_End"; // выход из локи с закрытием квеста
		break;
		
		case "Convict_12_1_1":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = "Prosimy, kapitanie, zatrudnij nas, z pewnością nie pożałujesz! Piratowaliśmy z "+GetName(NAMETYPE_NICK,pchar.GenQuest.Convict.PirateName,NAME_ABL)+" na Adriatyku, aż w końcu został powieszony, a my, "+pchar.GenQuest.Convict.ConvictQty+"ludzie, zostali wygnani do tego miejsca.";
			link.l1 = "Dobrze. Jest tu niedaleko miejsce, znane jako "+XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation)+" Około północy odbiorę cię tam. Mam nadzieję, że się nie zgubisz.";
			link.l1.go = "Convict_11_6";
			pchar.GenQuest.Convict = "ToShore";		
		break;

		case "Convict_12_1_2":
			addMoneyToCharacter(pchar, -3000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 60);
			iTmp = hrand(3);
			if(iTmp <= 1)
			{
				dialog.text = "Oczywiście, to nam bardzo pomoże! Wypływamy dziś, jeśli wiatr będzie sprzyjał i rybacy nas nie zawiodą. Dziękuję, kapitanie, i niech Bóg ci pomoże...";
				link.l1 = "Powodzenia także tobie.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			if(iTmp == 2)
			{
				dialog.text = "Toż to prawdziwy łut szczęścia! Nawet nie marzyliśmy, że tak szybko uda się zdobyć pieniądze. Kapitanie, pozwól mi wręczyć ci jeden drobiazg, który zabraliśmy naszemu dawnego szefowi. Może i tobie przyniesie szczęście.";
				link.l1 = "Dziękuję, to z pewnością przyzwoita rzecz. Powodzenia.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			}
			if(iTmp == 3)
			{
				pchar.GenQuest.Find_Merchant.lastspeak_date = LastSpeakDate();
				GenerateMerchant();
				makeref(MerPrm, MerchantParam);
				dialog.text = "Teraz to jest hojny człowiek, który nie boi się wydawać monety, bo wie, jak ją zarobić!\nZeszłej nocy widzieliśmy miejscowych przemytników ładujących "+MerPrm.QuestGoodsIdx+". Było ciemno, ale udało nam się dostrzec nazwę statku na burcie jednej z łodzi, '"+MerPrm.ShipName+"... a ten statek płynie pod banderą "+MerPrm.nation+"Być może, uznasz te informacje za przydatne, he-he.";			
				link.l1 = "Hmm... Cóż, być może tak zrobię. Żegnajcie, tropiciele.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "7");
				AddQuestUserData("Convict", "sShipName", MerPrm.ShipName);
				AddQuestUserData("Convict", "sGoodName", MerPrm.QuestGoodsIdx);
				CloseQuestHeader("Convict");
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				AddDialogExitQuestFunction("Convict_DialogDisable");			
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Sneak", 30);
			}
		break;
		
		case "Convict_12_2":
			dialog.text = "O mój Boże, nie jesteśmy w pozycji, by stawiać żądania. Cokolwiek możesz dać, będziemy wdzięczni za wszystko.";
			link.l1 = "300 pesos.";
			link.l1.go = "Convict_12_2_1";
			link.l2 = "1000 pesos.";
			link.l2.go = "Convict_12_2_2";
			link.l3 = "3000 pesos.";
			link.l3.go = "Convict_12_2_3";
		break;
		
		case "Convict_12_2_1":
			addMoneyToCharacter(pchar, -300);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 20);
			dialog.text = "Dziękuję, kapitanie, i niech Bóg ma cię w opiece...";
			link.l1 = "Powodzenia i tobie.";
			link.l1.go = "exit";
			pchar.GenQuest.Convict = "close";
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_12_2_2":
			addMoneyToCharacter(pchar, -1000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 40);
			if(hrand(1) == 0)
			{
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				dialog.text = "To dopiero szczęście! Nawet nie śniliśmy o tym, że zdobędziemy pieniądze tak szybko. Kapitanie, pozwól mi podarować ci jedną błyskotkę, którą zabraliśmy naszemu byłemu szefowi. Może i tobie przyniesie szczęście.";
				link.l1 = "Dziękuję, to na pewno przyzwoita rzecz. Powodzenia.";
				AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 20);
			}
			else
			{
				dialog.text = "Dziękuję, kapitanie, niech Bóg ma cię w opiece...";
				link.l1 = "Powodzenia i tobie.";
			}
			link.l1.go = "exit";
			pchar.GenQuest.Convict = "close";
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_12_2_3":
			addMoneyToCharacter(pchar, -3000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 60);
			if(hrand(1) == 0)
			{
				dialog.text = "Toż to szczęście! Nawet nie marzyliśmy o tym, żeby zdobyć pieniądze tak szybko. Kapitanie, pozwól mi wręczyć ci błyskotkę, którą zabraliśmy naszemu dawnemu szefowi. Może i tobie przyniesie szczęście.";
				link.l1 = "Dziękuję, to na pewno przyzwoita rzecz. Powodzenia.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			}
			else
			{
				pchar.GenQuest.Find_Merchant.lastspeak_date = LastSpeakDate();
				GenerateMerchant();
				makeref(MerPrm, MerchantParam);
				dialog.text = "Teraz oto hojny człowiek, który nie boi się wydać monety, bo wie, jak ją zarobić!\nWczoraj wieczorem widzieliśmy, jak miejscowi przemytnicy ładują "+MerPrm.QuestGoodsIdx+". Było ciemno, ale udało nam się rozpoznać nazwę statku na burcie jednej z łodzi '"+MerPrm.ShipName+"... a ten statek płynie pod banderą "+MerPrm.nation+"Może uznasz te informacje za przydatne, he-he.";
				link.l1 = "Hmm... Cóż, być może tak zrobię. Żegnajcie, tropiciele.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "7");
				AddQuestUserData("Convict", "sShipName", MerPrm.ShipName);
				AddQuestUserData("Convict", "sGoodName", MerPrm.QuestGoodsIdx);				
				CloseQuestHeader("Convict");
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Sneak", 30);
			}			
		break;
		
		case "Convict_12_1_End":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			OfficersReaction("bad");	
			pchar.GenQuest.Convict = "close";
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_12_3":
			if(hrand(1) == 0)
			{
				dialog.text = "Nie sprowadzaj na nas zguby, kapitanie! Mamy przyzwoity bibelot, proszę, przyjmij go jako okup i pozwól nam odejść...";
				link.l1 = "Oddaj to, a potem zmykaj, póki jeszcze możesz.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			else
			{
				dialog.text = "Teraz nie mamy innego wyboru, człowiek dwa razy nie umrze. Do ostatniej bitwy, chłopcy!";
				link.l1 = "To już inna historia!";
				link.l1.go = "Convict_Fight";
			}			
		break;
		
		case "Convict_13":
			dialog.text = "Cóż, z pewnością nie jesteśmy świętymi, ale nie szukamy zwady bez powodu... Jesteśmy zbiegami i musimy stąd uciec jak najszybciej.";
			link.l1 = "Masz coś, czym zapłacisz za przejście?";
			link.l1.go = "Convict_13_1";		
			link.l2 = "O, rozumiem... Nie, nie splamię swojej reputacji z twojego powodu. Żegnaj.";
			link.l2.go = "Convict_11_5";
		break;
		
		case "Convict_11_1":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = "Jasne! Jesteśmy przyzwyczajeni do abordażów i takich rzeczy. Przez prawie dwa lata my i nieboszczyk "+GetName(NAMETYPE_NICK,pchar.GenQuest.Convict.PirateName,NAME_ABL)+" terroryzował miejscowych kupców, ale niestety! Został powieszony, i "+pchar.GenQuest.Convict.ConvictQty+" ludzi z nas zostało skazanych na ciężkie roboty.";
			link.l1 = "A może dołączysz do mojej załogi? Jestem hojny"+GetSexPhrase("","")+", ale nie obiecuję ci spokojnego życia.";
			link.l1.go = "Convict_11_3";			
		break;
		
		case "Convict_11_2":
			dialog.text = "Tak, złapaliśmy coś z "+GetStrSmallRegister(XI_ConvertString("TypKopaliny"+pchar.GenQuest.Convict.MineType+"Gen"))+", więc możemy zapłacić podwójnie. WIĘC ufam, że cena jest uzgodniona. I nie waż się sprowadzać straży. Nie wybaczamy zdrady..."; // belamour gen
			link.l1 = " Dobrze, zaczekaj na mnie na plaży "+XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation+"Rodzaj")+" . Bliżej północy będzie dla ciebie łódź... I nie chcę widzieć żadnych sztuczek!"; // belamour gen
			link.l1.go = "Convict_11_4";
			link.l2 = "Nie, moi przyjaciele. A co jeśli oddam wam statek, a wy mnie zdradzicie? Nie, nie pomogę wam w tej sprawie.";
			link.l2.go = "Convict_11_5";
		break;
		
		case "Convict_11_3":
			dialog.text = "Z wielką przyjemnością, "+GetSexPhrase("pan","tęsknić")+" kapitanie. Jesteśmy z tym dobrze zaznajomieni, i na pewno nie zostaniemy przyjęci do Marynarki z takimi referencjami, he-he.";
			link.l1 = "Dobrze. Jest tu niedaleko miejsce, znane jako "+XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation)+"Po północy cię tam odbiorę. Mam nadzieję, że się nie zgubisz.";
			link.l1.go = "Convict_11_6";
		break;
		
		case "Convict_11_4":
			dialog.text = "Ale, "+GetSexPhrase("pan","panna")+" kapitanie, podejmujemy jeszcze większe ryzyko? A co jeśli postanowisz nas wydać komendantowi?";
			link.l1 = "To prawda... Dobrze, jeśli mnie tam nie będzie o świcie, umowa jest anulowana.";
			link.l1.go = "Convict_11_7";			
		break;
		
		case "Convict_11_5":
			if(makeint(pchar.reputation.nobility) < 11 || makeint(pchar.reputation.nobility) > 79) //макс. репутатция 90
			{
				dialog.text = "O, kapitanie, liczyliśmy na ciebie...";
				link.l1 = "Nie ma problemu. Jeśli masz pieniądze, znajdziesz transport. Żegnaj.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				ChangeCharacterComplexReputation(pchar,"nobility", -2);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			else
			{
				dialog.text = "Jesteś bystrym, kapitanie, jak widzę. Jestem pewien, że od razu pobiegniesz do komendanta, prawda? I myślisz, że ujdzie ci to na sucho?";
				link.l1 = "A zamierzasz mnie powstrzymać, jak widzę?! To dostaniesz, na co zasługujesz!";
				link.l1.go = "Convict_Fight";
				pchar.GenQuest.Convict = "fight";
			}	
		break;
		
		case "Convict_11_6":
			pchar.GenQuest.Convict = "ToShore";
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "1");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sConvictNum", Convict_GetStringNum(sti(pchar.GenQuest.Convict.ConvictQty))); // belamour gen колво прописью
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Gen"));	// belamour gen	
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);	
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;			
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_11_7":
			pchar.GenQuest.Convict = "GetShip";
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "2");		
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));		
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Acc"));					
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;			
			DialogExit();		
			AddDialogExitQuestFunction("Convict_DialogDisable");		
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_13_1":
			pchar.GenQuest.Convict.Sum = (sti(pchar.rank)+10)*100+1000;
			dialog.text = "Coś jest. Przeszukaliśmy skrzynie naszego szefa, ale potem zrobiło się zamieszanie, i musieliśmy przebić się walką. Tylko "+PChar.GenQuest.Convict.ConvictQty+" ludzie zdołali przeżyć.";
			link.l1 = "Z uwagi na okoliczności, nie dam ci przejazdu taniej niż "+FindRussianMoneyString(sti(pchar.GenQuest.Convict.Sum))+"pesos za osobę.";
			link.l1.go = "Convict_13_2";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty) && GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l2 = "Widzę, że nie jesteście tchórzami. Dołączycie do mojej załogi?";
				link.l2.go = "Convict_13_3";
			}
		break;
		
		case "Convict_13_2":
			dialog.text = "Czy mamy wybór? Dobrze, "+FindRussianMoneyString(sti(pchar.GenQuest.Convict.Sum))+"... ";
			link.l1 = "W takim razie idź do "+XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation+"To")+"Poślę po ciebie łódź po północy."; // belamour gen 
			link.l1.go = "Convict_13_4";
			pchar.GenQuest.Convict = "ToMayak";
			pchar.GenQuest.Convict.Sum = sti(pchar.GenQuest.Convict.Sum) * sti(pchar.GenQuest.Convict.ConvictQty);
		break;
		
		case "Convict_13_3":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = "I czemu nie? Znamy się na tym, piraciliśmy z "+GetName(NAMETYPE_NICK,pchar.GenQuest.Convict.PirateName,NAME_ABL)+" w "+RandPhraseSimple("Gibraltar","Kanał Angielski")+"zanim utknęliśmy tutaj.";
			link.l1 = "Dobrze. W pobliżu jest miejsce, znane jako "+XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation)+"  Około północy cię tam odbiorę. Mam nadzieję, że się nie zgubisz.";
			link.l1.go = "Convict_11_6";
			pchar.GenQuest.Convict = "ToShore";
		break;
		
		case "Convict_13_4":
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "8");					
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));		
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sConvictNum", Convict_GetStringNum(sti(pchar.GenQuest.Convict.ConvictQty))); // belamour gen колво прописью
			AddQuestUserData("Convict", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Convict.ToCity + "Gen"));
			AddQuestUserData("Convict", "sSum", pchar.GenQuest.Convict.Sum);
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Dat"));	// belamour gen	 	
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;			
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
				
		case "Convict_14":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Eh, kapitanie, też byłeś kiedyś biedny, miałeś puste kieszenie. A teraz gardzisz prostymi ludźmi, takimi jak my."),RandPhraseSimple("Heh, ludzie naprawdę stają się zbyt samolubni w dzisiejszych czasach. Żyjecie tak, jakbyście mieli przed sobą jeszcze dwa stulecia.","O, widzę, że dopiero co przybyłeś z Europy, jeszcze nie poczułeś smrodu naszego tropikalnego śmietniska."));
			link.l1 = LinkRandPhrase("Próbujesz mnie zawstydzić? Skrócę ci język o parę cali!","Straszysz mnie? Trzymaj się teraz swojego kapelusza!","Czyś ty filozof, czy co? Wbiję ci trochę rozumu do głowy!");
			link.l1.go = "Convict_Fight";	
			pchar.GenQuest.Convict = "fight";
		break;
		
		case "Convict_Fight":
			LAi_SetPlayerType(pchar);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);	 
			LAi_LockFightMode(pchar, false); 
			LAi_SetFightMode(pchar, true);
			chrDisableReloadToLocation = true;
			iTemp = sti(PChar.GenQuest.Convict.ConvictQty);
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID("Convict_" + i);
				DeleteAttribute(rChar, "City");
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, "ConvictGroup");
				LAi_SetImmortal(rChar, false);
			}
			LAi_group_SetRelation("ConvictGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("ConvictGroup", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("ConvictGroup", "OpenTheDoors"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "Convict_15":
			dialog.text = LinkRandPhrase("Więc, kapitanie? Zdobyłeś dla nas statek?","Witaj, kapitanie. A więc, co z naszą umową?","Cześć, kapitanie. Zaczęliśmy się już martwić. Wszystko poszło dobrze, jak mniemam?");
			if(Convict_CheckShipType(SHIP_TARTANE) || Convict_CheckShipType(SHIP_WAR_TARTANE))
			{
				link.l1 = "Tak, oto twoja łajba. I nie zapomnij o zapłacie. Zapłaciłem "+pchar.GenQuest.Convict.ShipPrice+"monet za to, więc jesteś mi winien"+sti(pchar.GenQuest.Convict.ShipPrice)* 2+" , tak jak się umówiliśmy.";
				link.l1.go = "Convict_15_1";
			}	
			link.l2 = "Nie, zmieniłem zdanie. Znajdź sobie innego pomocnika. Żegnaj...";
			link.l2.go = "Convict_15_2";
		break;
		
		case "Convict_15_1":
			switch(sti(pchar.GenQuest.Convict.variant))
			{
				case 1:
					dialog.text = "Oczywiście! Odebrali nam wolność, ale nie sumienie! Proszę, przyjmij swoje pieniądze wraz z naszą nieograniczoną wdzięcznością. Naprawdę nam pomogłeś. Czy masz coś przeciwko, jeśli zapłacimy ci w srebrnych sztabach?";
					link.l1 = "Pewnie, że nie. Powodzenia w podróży. I módl się, żebym nie spotkał cię na otwartym morzu, bo szybko się z tobą rozprawię.";
					link.l1.go = "Convict_15_1_1End";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Commerce", 30);
					TakeNItems(pchar, "jewelry6", makeint(sti(pchar.GenQuest.Convict.ShipPrice)/50));
				break;
				case 2:
					dialog.text = "Kapitanie, wiesz, doszliśmy do wniosku, że pieniądze tak naprawdę nie są aż tak ważne w życiu. I, szczerze mówiąc, teraz potrzebujemy ich znacznie bardziej niż ty. Ale mamy jedną rzecz, którą ukradliśmy naszemu dawnemu szefowi. Może zainteresuje cię bardziej niż złoto. Chcesz rzucić okiem?...";
					link.l1 = "Tak, masz rację. To naprawdę cudowna rzecz. Dobrze, masz umowę, dzięki i żegnaj.";
					link.l1.go = "Convict_15_1_2End";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Fortune", 30);
					GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				break;
				case 3:
					pchar.GenQuest.Convict = "FightInShore";
					SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);				
					dialog.text = "Po co ci w ogóle tyle pieniędzy, kapitanie? I tak jesteś bogaty, a my jesteśmy zgubieni, jeśli nie zdobędziemy tego statku. Więc... po prostu go od ciebie weźmiemy. Bez urazy.";
					link.l1 = "To był twój ostatni błąd. Bez statku mógłbyś jeszcze odpłynąć, ale teraz albo będziesz dryfować, albo pójdziesz na dno.";
					link.l1.go = "Convict_Fight";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Sneak", 30);
				break;
			}
		break;
	
		case "Convict_15_1_1End":
			AddQuestRecord("Convict", "4");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Gen")); // belamour gen
			CloseQuestHeader("Convict");
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuestFunction("Convict_SetConvictToShip");
			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;
	
		case "Convict_15_1_2End":
			AddQuestRecord("Convict", "5");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Gen")); // belamour gen
			CloseQuestHeader("Convict");
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuestFunction("Convict_SetConvictToShip");
			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;	
	
		case "Convict_15_2":
			AddQuestRecord("Convict", "3");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Convict");
			for(i = 0; i < sti(pchar.GenQuest.Convict.ConvictQty); i++)
			{
				sld = CharacterFromID("Convict_" + i);
				sld.LifeDay = 0;
			}	
			ChangeCharacterComplexReputation(pchar,"nobility", -2);	
			LAi_group_Delete("ConvictGroup");
			DeleteAttribute(pchar, "GenQuest.Convict");
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_16":
			dialog.text = RandPhraseSimple("Więc, kapitanie? Możemy zaczynać się ładować?","W końcu! Już zaczęliśmy się martwić, myśleliśmy, że zmieniłeś zdanie.");
			link.l1 = "Przepraszam, zmieniłem plany. Teraz musisz poszukać innego kapitana.";
			link.l1.go = "Convict_16_1";
			if(pchar.GenQuest.Convict == "ToMayak")
			{
				link.l2 = "Załaduj się na łódź, nie mam dużo czasu.";
				link.l2.go = "Convict_16_2";			
			}			
			if(pchar.GenQuest.Convict == "ToShore" && GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				link.l2 = "Załadujcie się na łódź, nie mam dużo czasu.";
				link.l2.go = "Convict_16_2";			
			}			
		break;
		
		case "Convict_16_1":
			if(rand(1) == 0)
			{
				dialog.text = "Cholera! Z pewnością już wysłałeś patrol za nami?! Nie ujdzie ci to na sucho!";
				link.l1 = "O czym ty mówisz?! Chcesz zginąć czy co?!";
				link.l1.go = "Convict_Fight";
				pchar.GenQuest.Convict = "ShoreFight";
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			}
			else
			{
				dialog.text = "Kapitan "+GetSexPhrase(", jesteś człowiekiem honoru czy jak?","?")+" A może jesteś tylko pieprzonym gadułą...";
				link.l1 = "Lepiej uważaj na język...";
				link.l1.go = "Convict_16_3";
			}
		break;
		
		case "Convict_16_2":
			if(pchar.GenQuest.Convict == "ToShore")
			{
				AddCharacterExpToSkill(pchar, "Leadership", 30);
				AddCharacterCrew(pchar, sti(pchar.GenQuest.Convict.ConvictQty));
				OfficersReaction("bad");
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "10");
				CloseQuestHeader("Convict");				
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			}
			if(pchar.GenQuest.Convict == "ToMayak")
			{
				AddQuestRecord("Convict", "10");
				sld = characterFromId("Convict_0");
				AddPassenger(pchar, sld, false);
				SetCharacterRemovable(sld, false); 
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				SetFunctionLocationCondition("Convict_OnMayak", pchar.GenQuest.Convict.Mayak, true);
				locations[FindLocation(pchar.GenQuest.Convict.Mayak)].DisableEncounters = true;			
			}
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_16_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			OfficersReaction("bad");
			pchar.GenQuest.Convict = "close";
			AddQuestRecord("Convict", "3");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Convict");				
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			AddDialogExitQuestFunction("Convict_DialogDisable");			
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;
						
		case "Convict_17":
			dialog.text = LinkRandPhrase("O, dziękuję, "+GetSexPhrase("dobry człowiek","zacna dziewoja")+".","Dziękuję, kapitanie, naprawdę uratowałeś mnie od stryczka.","Doceniam tak wspaniałą podróż.");
			link.l1 = LinkRandPhrase("To wszystko dobrze i pięknie, ale czekam na pieniądze.","Czas zapłacić, wiesz.","Gotówka na paznokieć, jak się umówiliśmy.");
			link.l1.go = "Convict_17_1";
		break;
		
		case "Convict_17_1":
			switch(sti(pchar.GenQuest.Convict.variant))
			{
				case 1:
					dialog.text = "Oczywiście, co za pytania! Oto twoje pieniądze w sztabach złota i przyjmij nasze najszczersze podziękowania.";
					link.l1 = "Powodzenia również tobie. Żegnaj.";
					link.l1.go = "Convict_17_1_1End";
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Commerce", 80);
					TakeNItems(pchar, "jewelry5", makeint(sti(pchar.GenQuest.Convict.Sum)/200));
					break;
				case 2:
					dialog.text = "Kapitanie, wiecie, pomyśleliśmy, że pieniądze naprawdę nie są tak ważne w życiu. I, szczerze mówiąc, potrzebujemy ich teraz dużo bardziej niż wy. Ale mamy jedną rzecz, którą ukradliśmy naszemu byłemu szefowi. Może zainteresuje was to dużo bardziej niż złoto. Chcecie rzucić okiem?...";
					link.l1 = "Tak, masz rację. To naprawdę cudowna rzecz. Dobrze, w porządku, mamy umowę, dzięki i żegnaj.";
					link.l1.go = "Convict_17_1_2End";
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Fortune", 80);
					GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
					break;
				case 3:
					dialog.text = "Po co ci tyle pieniędzy? I tak jesteś bogaty. Pomogłeś nam, my pomożemy ci przy innej okazji.";
					link.l1 = "Nie będzie takiej okazji. Odmówcie modlitwy, łotry, nie zamierzam tolerować długów.";
					link.l1.go = "Convict_Fight";
					pchar.GenQuest.Convict = "MayakFight";
					SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);				
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Sneak", 80);			
					break;
			}
		break;
		
		
		case "Convict_17_1_1End":
			AddQuestRecord("Convict", "11");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sMayak", XI_ConvertString(pchar.GenQuest.Convict.Mayak + "Dat"));	//belamour gen			
			AddQuestUserData("Convict", "sSum", makeint(pchar.GenQuest.Convict.Sum));
			CloseQuestHeader("Convict");
			pchar.GenQuest.Convict = "close";
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_17_1_2End":
			AddQuestRecord("Convict", "12");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sMayak", XI_ConvertString(pchar.GenQuest.Convict.Mayak + "Dat"));	// belamour gen	
			CloseQuestHeader("Convict");
			pchar.GenQuest.Convict = "close";
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;		
		// <-- Генератор "State convicts"
		
		// Генератор "A reason to hurry" -->
		// Встреча с ОЗГ на берегу
		case "ReasonToFast_Hunter1":
			dialog.text = "Zostałem tu wysłany przez "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" sam...";
			link.l1 = GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+"czeka na ciebie z odpowiedzią już od kilku godzin. Wysłał mnie zaraz po tobie.";
			link.l1.go = "ReasonToFast_Hunter4";
		break;
		
		case "ReasonToFast_Hunter2":
			dialog.text = "Podążałem za tobą w twoim śladzie przez długi czas, ale jesteś po prostu za szybki.";
			link.l1 = "I co z tego?";
			link.l1.go = "ReasonToFast_Hunter6";		
		break;
		
		case "ReasonToFast_Hunter3":
			dialog.text = "Może powiesz mi, ile gubernator płaci swoim pachołkom?";
			link.l1 = "Do diabła!";
			link.l1.go = "ReasonToFast_Fight";		
		break;
		
		case "ReasonToFast_Hunter4":
			dialog.text = "Nie piłem! Szukałem bosmana...";
			link.l1 = "Idź teraz... Powiem "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_DAT)+", że zgubiłeś się w dżungli.";
			link.l1.go = "ReasonToFast_Hunter5";		
			AddQuestRecord("ReasonToFast", "5");
			AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
		break;
		
		case "ReasonToFast_Hunter5":
			LAi_SetPlayerType(pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("ReasonToFast_HunterGoOut");
		break;
		
		case "ReasonToFast_Hunter6":
			pchar.questTemp.ReasonToFast = "MeetHunterFail";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("ReasonToFast_PatrolAngry");
		break;
		
		case "ReasonToFast_Fight":
			LAi_SetPlayerType(pchar);
			pchar.questTemp.ReasonToFast = "PatrolAngry";
			pchar.questTemp.ReasonToFast.relation = GetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation));
			SetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation), RELATION_ENEMY); 
			pchar.GenQuest.HunterScore2Pause = 1; //НЗГ не начисляются
			pchar.GenQuest.ReputationNotChange = 1; //репутацию не менять
			sTemp = "Patrol" + pchar.questTemp.ReasonToFast.LocIdx + "_";
			sGroup = "PatrolGroup_" + pchar.questTemp.ReasonToFast.LocIdx;
			LAi_LocationFightDisable(&locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)], false);	
			iTemp = sti(pchar.questTemp.ReasonToFast.PatrolNum);
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("ReasonToFast_Hunter");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, sGroup);
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			LAi_group_SetCheck(sGroup, "ReasonToFast_PatrolDied");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		// бой с кэпом пиратского корабля
		case "ReasonToFast_FightCap": 
			dialog.text = "I ty jesteś sprytny. Módl się do Boga, aby twoje sztuczki nie stały się znane "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+".";
			link.l1 = "Nie dowie się, jeśli mu nie powiesz... I nie powiesz, prawda?";
			link.l1.go = "ReasonToFast_FightCap_1";
		break;
		
		case "ReasonToFast_FightCap_1":
			dialog.text = "Dlaczego? Oczywiście, że tak, i to z wielką przyjemnością!";
			link.l1 = "On i tak cię powiesi za tę głupotę. Więc nie traćmy czasu, a ja pomogę ci umknąć stryczkowi.";
			link.l1.go = "ReasonToFast_FightCap_2";
		break;
		
		case "ReasonToFast_FightCap_2":
			dialog.text = "Hmm... A jak zamierzasz to zrobić?";
			link.l1 = "Zabiję cię osobiście...";
			link.l1.go = "ReasonToFast_FightCap_Last";
		break;
		
		case "ReasonToFast_FightCap_Last":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;		
		
		// встреча с лакеем в резиденции
		case "ReasonToFast_Lakey":
			dialog.text = "Masz tu interes, "+GetSexPhrase("monsieur","mademoiselle")+"?";
			link.l1 = "Nie, nie, jestem tu na zaproszenie uroczej żony gubernatora, rozglądam się po tej naprawdę luksusowej rezydencji.";
			link.l1.go = "ReasonToFast_Lakey1";
			link.l2 = "Mam wiadomość od ludzi, których znasz.";
			link.l2.go = "ReasonToFast_Lakey2";
			link.l3 = "Tak. Chcę cię postawić przed sądem!";
			link.l3.go = "ReasonToFast_Lakey3";
			pchar.questTemp.ReasonToFast = "MeetLakey";
			pchar.questTemp.ReasonToFast.SpeakOther = true;			
		break;
		
		case "ReasonToFast_Lakey1":
			NextDiag.TempNode = "ReasonToFast_Lakey11";
			dialog.text = "O tak, miałem naprawdę szczęście służyć w tak pięknym domu.";
			link.l1 = "Nie ma co się dziwić...";
			link.l1.go = "ReasonToFast_Lakey11";
		break;

		case "ReasonToFast_Lakey11":
			NextDiag.TempNode = "ReasonToFast_Lakey11";
			dialog.text = "Nie zapomnij zajrzeć do naszego ogrodu!";
			link.l1 = "Dziękuję, dobry człowieku!";
			link.l1.go = "exit";			
			bDisableFastReload = false;
		break;
		
		case "ReasonToFast_Lakey2":
			dialog.text = "Ehh... "+pchar.questTemp.ReasonToFast.password+"?";
			link.l1.edit = 1;			
			link.l1 = ""; 
			link.l1.go = "ReasonToFast_Lakey21";
		break;

		case "ReasonToFast_Lakey3":
			dialog.text = "Nie ujdzie ci to na sucho, zdrajco!";
			link.l1 = "Stój w miejscu, łotrze!";
			link.l1.go = "ReasonToFast_Lakey_exit";
			pchar.questTemp.ReasonToFast = "LakeyExitFail";
			bDisableFastReload = false;			
		break;

		case "ReasonToFast_Lakey21":
			if(GetStrSmallRegister(pchar.questTemp.ReasonToFast.ShipName) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "Szybko teraz! Zabrać wszystko, co cenne, i uciekać!";
				link.l1 = " Myślę, że powinieneś też uciekać.";
				link.l1.go = "ReasonToFast_Lakey_exit";
				TakeNItems(pchar,"icollection", sti(pchar.questTemp.ReasonToFast.p8));
				TakeNItems(pchar,"Chest", sti(pchar.questTemp.ReasonToFast.p7));
				pchar.questTemp.ReasonToFast = "LakeyExitSuccess";					
				bDisableFastReload = true;		
				//chrDisableReloadToLocation = true;			
			}
			else
			{
				dialog.text = "Przepraszam, muszę się oddalić.";
				link.l1 = "Stój spokojnie, łotrze!";
				link.l1.go = "ReasonToFast_Lakey_exit";
				pchar.questTemp.ReasonToFast = "LakeyExitFail";
				bDisableFastReload = false;
			}			 
		break;

		case "ReasonToFast_Lakey_exit":
			DialogExit();	
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			pchar.quest.ReasonToFast_ClearLakey.over = "yes"; //снимаем таймер
			ReasonToFast_SetHunterCoastal();
			AddDialogExitQuest("ReasonToFast_LakeyGoOut");
		break;		
		
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Jesteś "+GetSexPhrase("Złodziej, widzę! Strażnicy, złapcie go","Złodziejka, widzę! Strażnicy, schwytajcie ją!")+"!","Nie mogę w to uwierzyć! Odwróciłem się na sekundę, a ty nurkujesz do mojej skrzyni! Zatrzymać złodzieja!","Straż! Rabunek! Zatrzymać złodzieja!");
			link.l1 = "Aaaah, diabeł!";
			link.l1.go = "ReasonToFast_Lakey_exit";
			pchar.questTemp.ReasonToFast = "LakeyExitFail";
			bDisableFastReload = false;
		break; 
		// Генератор "A reason to hurry" <--
		
		// ситуации с капитаном захваченного корабля
		// взрыв на корабле
		case "ShipSituation11": // пираты или ДУ
			dialog.text = RandPhraseSimple("Cześć, "+GetSexPhrase("kamracie","dziewko")+"! Przygotowałem dla ciebie niespodziankę, zapaliłem lont do komory prochowej. Wysadzi to wszystko w diabły!","Co tam stoisz? W izbie prochowej pożar! Wybuchnie, a fajerwerki będą widoczne w Europie!");
			link.l1 = RandPhraseSimple("Ty łotrze, nie oszukasz mnie! Walcz, tchórzu!","Widzę, że szczury opuszczają statek, a ty jesteś wśród pierwszych?");
			link.l1.go = "ShipSituation12";
		break;
		
		case "ShipSituation12":
			dialog.text = RandPhraseSimple("Ty też powinieneś uciekać, jeśli cenisz swoje życie... Cóż, nie mam czasu, łódź na mnie czeka. Miłego łowienia ryb!","Nie mam czasu na zabawę w bohatera, chłopcy na łodzi czekają na mnie. Miłego połowu, zwycięzco!");
			link.l1 = RandPhraseSimple("Do diabła! Odcinaj odbijacze! Ruszaj!","O Boże, jak mogliśmy wpaść w takie tarapaty! Otwórzcie cieśniny! Odpływajcie!");
			link.l1.go = "ShipSituation_End";
		break;
		
		case "ShipSituation21": // военный корабль (не флагман)
			dialog.text = "Więc co z tego?! Myślisz, że wygrałeś bójkę?! Nie ma mowy. Podpaliłem prochownię, nie uciekniesz z tego statku żywy.";
			link.l1 = RandPhraseSimple("Ty łotrze, nie oszukasz mnie! Walcz, tchórzu!","Widzę, że szczury opuszczają statek, a ty jesteś wśród pierwszych?");
			link.l1.go = "ShipSituation22";
		break;
		
		case "ShipSituation22":
			dialog.text = RandPhraseSimple("Jestem związany przysięgą, ale to nie znaczy, że muszę umrzeć na próżno. Przepraszam, że nie oferuję ci miejsca w łodzi, marynarze tego nie zrozumieją.","Okręty są związane ze sobą podczas abordażu, więc twój los jest przypieczętowany. Wybacz, ale moja łódź czeka...");
			link.l1 = RandPhraseSimple("Do diabła! Odetnijcie odbijacze! Ruszajcie!","O Boże, jak mogliśmy się wpakować w taką kabałę! Otwórzcie wloty morskie! Odciągnijcie!");
			link.l1.go = "ShipSituation_End";
		break;
		
		case "ShipSituation31": // ОЗГ
			dialog.text = RandPhraseSimple("Jesteś zwycięzcą! Witaj w piekle! Podpaliłem prochownię.","Oto jesteś, mój dobry człowieku! Zrobiłeś to, podpaliłem prochownię.");
			link.l1 = RandPhraseSimple("Ty łotrze, nie oszukasz mnie! Walcz, tchórzu!","Widzę, że szczury opuszczają statek, a ty jesteś jednym z pierwszych?");
			link.l1.go = "ShipSituation32";
		break;
		
		case "ShipSituation32":
			dialog.text = RandPhraseSimple("Śledziłem cię przez długi czas. Szkoda, że musiałem poświęcić swój statek, ale twoja głowa jest warta dwóch nowych. Miłego łowienia ryb!","Zobacz, jak zamierzasz odejść? Z fajerwerkami, jak indyjski książę"+GetSexPhrase("ce","szambo")+". Ale nie dam się wydymać, twoja głowa jest warta o wiele więcej niż mój statek. Żegnaj teraz, moja łajba nie będzie czekać zbyt długo...");
			link.l1 = RandPhraseSimple("Cholera! Odetnijcie odbijacze! Ruszajcie!","O Boże, jak mogliśmy wpaść w takie kłopoty! Otwórzcie wloty morskie! Odpływajcie!");
			link.l1.go = "ShipSituation_End";			
		break;
		
		case "ShipSituation_End":
			AddCharacterExpToSkill(pchar, "Sneak", 200);
			DialogExit();
			LAi_SetActorType(NPChar); 
			LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);
			NPChar.LifeDay = 0;
			LAi_LockFightMode(pchar, false);	
			Log_Info(XI_ConvertString("Ship can explode"));
			pchar.GenQuest.ShipSituation.Explosion = ShipSituation_4;	
			pchar.GenQuest.ShipSituation.Explosion.CapId = NPChar.CaptanId;
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;
		
		// эпидемия
		case "ShipEpidemy1":
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = RandPhraseSimple("Trzymaj się, kapitanie! Na parę słów.","Trzymaj się, kapitanie! Myślę, że to może być dla ciebie interesujące.");
			link.l1 = LinkRandPhrase("Po co gadać podczas walki?!","A o czym to niby miałbym rozmawiać z nieboszczykiem?","Co jest grane? Chcesz zrobić testament na moje nazwisko?");
			link.l1.go = "ShipEpidemy2";
		break;
		
		case "ShipEpidemy2":
			dialog.text = "Na pokładzie wybuchła zaraza. Straciłem jedną czwartą załogi podczas podróży. Wszyscy jesteście skazani na zagładę...";
			link.l1 = RandPhraseSimple("Ty zgniły łajdaku! Czemu nie pokazałeś sygnału, że na twoim statku jest katastrofa?!","Czy zapomniałeś o kodeksie morskim? Powinieneś był wywiesić sygnał na maszcie, że na twoim statku jest klęska!");
			link.l1.go = "ShipEpidemy3";
		break;
		
		case "ShipEpidemy3":
			dialog.text = "Już i tak mieliśmy zginąć. Dlatego się nie poddaliśmy, chcieliśmy zabrać ciebie i twoje diabelskie pomioty ze sobą na tamten świat! Teraz jestem w pełni usatysfakcjonowany. Możesz dokończyć swoje plugastwo.";
			link.l1 = RandPhraseSimple("Odpowiesz mi za to!..","Lubię myśl, że to ty umrzesz pierwszy. A ja będę na to patrzył.");
			link.l1.go = "ShipEpidemy31";
			link.l2 = RandPhraseSimple("Nie splamię mego ostrza twoją plugawą krwią, możesz żyć, chociaż... po co? Zabieram moją załogę z tej zgniłej starej łajby.","Za to powinieneś trafić na szubienicę, ale teraz nie ma takiej potrzeby. Zabieram swoich ludzi... Możesz żyć, choć twój czas powinien być krótki...");
			link.l2.go = "ShipEpidemy32";
			pchar.GenQuest.ShipSituation.Epidemy.CapId = NPChar.CaptanId;
			pchar.GenQuest.ShipSituation.Epidemy = ShipSituation_4;
		break;
		
		case "ShipEpidemy31":
			pchar.GenQuest.QuestAboardCabinDialogIdx = NPChar.index;
			pchar.GenQuest.ShipSituation.Epidemy.CapState = "Died"; // вражеский кэп на волосок от смерти от переизбытка стали и свинца в организме
			LAi_LockFightMode(pchar, false);
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "ShipEpidemy32":
			DialogExit();
			LAi_SetActorType(NPChar); 
			LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);
			LAi_LockFightMode(pchar, false);	
			pchar.GenQuest.ShipSituation.Epidemy.CapState = "Live"; // вражеский кэп остался в живых
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;
		// ситуации с капитаном захваченного корабля
		
		// Генератор "A damsel in the jungle"
		case "EncGirl_Lover":
			dialog.text = "Witaj, kapitanie, powiedziano mi, że mnie szukałeś.";
			link.l1 = "Jestem - jeśli ty jesteś "+pchar.GenQuest.EncGirl.sLoverId+".";
			link.l1.go = "EncGirl_Lover1";
		break;
		
		case "EncGirl_Lover1":
			dialog.text = "To prawda. Coś ważnego?";
			link.l1 = "Nie wiem, czy to dla ciebie ważne, ale przyniosłem "+pchar.GenQuest.EncGirl.name+". Uciekła z domu i teraz czeka na ciebie niedaleko tawerny.";
			link.l1.go = "EncGirl_Lover2";
		break;
		
		case "EncGirl_Lover2":
			dialog.text = "O mój... Wiedziałem, że to wszystko tak się skończy... A dlaczego ona uciekła? Czy ci powiedziała?";
			link.l1 = "Jej ojciec chce wydać ją za syna lichwiarza.";
			link.l1.go = "EncGirl_Lover3";
		break;
		
		case "EncGirl_Lover3":
			pchar.GenQuest.EncGirl.LoverCity = GetQuestNationsCity(sti(pchar.GenQuest.EncGirl.nation));
			pchar.GenQuest.EncGirl.LoverIsland = GetIslandByCityName(pchar.GenQuest.EncGirl.LoverCity);
			dialog.text = "O nie, nie możemy na to pozwolić! Kapitanie, wiesz, jestem w takiej głupiej sytuacji... Chciałem cię prosić, żebyś zabrał nas do "+XI_ConvertString(pchar.GenQuest.EncGirl.LoverIsland+"Acc")+" do miasta zwanego "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.LoverCity)+", ale teraz nie mam żadnych pieniędzy i wciąż nie znalazłem pracy. Mam zamożną rodzinę i obiecującą karierę w "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.LoverCity)+"Zapewniam cię, moi rodzice będą zachwyceni, widząc mnie z młodą narzeczoną i hojnie cię wynagrodzą. Więc, zgadzasz się?";
			link.l1 = "...Słuchaj teraz, mam zupełnie inne plany. Mogę ci doradzić, żebyś znalazł pracę jako marynarz i wynajął kabinę dla swojej narzeczonej za swoją pensję. Ludzie w taki sposób dostają się do Europy, a ta twoja osada jest w zasięgu nocnego lotu ptaka.";
			link.l1.go = "EncGirl_Lover4";
			link.l2 = "Och, młodzieńcze... Czy zdajesz sobie sprawę, o co mnie prosisz? Zabranie dziewczyny od jej rodziców bez ich błogosławieństwa? ... I jaki człowiek by odmówił takiej rzeczy, oczywiście, że wchodzę w to!";
			link.l2.go = "EncGirl_Lover5";
		break;
		
		case "EncGirl_Lover4":
			npchar.lifeDay = 0;
			AddDialogExitQuestFunction("EncGirl_LoverExit");	
			DialogExit();
		break;
		
		case "EncGirl_Lover5":
			AddDialogExitQuestFunction("EncGirl_ToLoverParents");	
			DialogExit();
		break;
		
		case "EncGirl_Lover6":
			AddSimpleRumourCityTip(RandPhraseSimple("Have you heard, " + pchar.GenQuest.EncGirl.name + " ran off with her lover. She decided not to bind her life to an invalid. That's surely the mistake of her parents, they should not have become tempted with the money of her fiance and try to give such a beauty in marriage to a fright.",  
				"Have you heard?" + pchar.GenQuest.EncGirl.name + " tricked both her dad and her would-be fiance. They say one noble captain helped her and her lover to get to another island, where her lover's parents lived... Imagine that, there still are people, who had not yet forgotten the taste of passion!"), pchar.GenQuest.EncGirl.LoverCity, 3, 2, "citizen,habitue", "");
			dialog.text = "Dziękujemy, kapitanie. Będziemy pamiętać twoją pomoc do końca naszych dni.";
			link.l1 = "To nic takiego. Mam nadzieję, że wszystko ułoży się dla ciebie pomyślnie.";
			link.l1.go = "EncGirl_Lover7";
		break;
		
		case "EncGirl_Lover7":
			switch (rand(4))
			{
				case 0:
					sTemp = "the shop";
					pchar.GenQuest.EncGirl.LoverFather = "store_keeper";
				break;
				case 1:
					sTemp = "the shipyard";					
					pchar.GenQuest.EncGirl.LoverFather = "shipyard_keeper";
				break;
				case 2:
					sTemp = "the port office";					
					pchar.GenQuest.EncGirl.LoverFather = "portman_keeper";
				break;
				case 3:
					sTemp = "the tavern";					
					pchar.GenQuest.EncGirl.LoverFather = "tavern_keeper";
				break;
				case 4:
					sTemp = "the bank";					
					pchar.GenQuest.EncGirl.LoverFather = "usurer_keeper";
				break;
			}	
			pchar.GenQuest.EncGirl.FatherLoc = sTemp;
			dialog.text = "Obiecałem przedstawić cię moim rodzicom. Jeśli masz wolną chwilę, proszę przyjdź do "+sTemp+", mój ojciec tam pracuje, i powiem mu, co dla nas zrobiłeś. Jestem pewien, że będzie zachwycony, mogąc cię zobaczyć.";
			link.l1 = "W porządku, wpadnę, gdy tylko znajdę chwilę. Bądźcie szczęśliwi i dbajcie o siebie nawzajem, oboje...";
			link.l1.go = "EncGirl_Lover8";
		break;
		
		case "EncGirl_Lover8":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			npchar.lifeday = 0;
			AddQuestRecord("JungleGirl", "16");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sText", pchar.GenQuest.EncGirl.FatherLoc);
			if((GetSummonSkillFromName(pchar, SKILL_FORTUNE) + GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)) < 175)
			{
				pchar.GenQuest.EncGirl.LoverFatherAngry = 0; // папочка жениха счастлив за сына :)
			}
			else
			{
				pchar.GenQuest.EncGirl.LoverFatherAngry = 1; // папочка жениха разъярен за то что сын притащил в дом шалаву :)
			}
			chrDisableReloadToLocation = false; 
			pchar.GenQuest.EncGirl = "toLoverFather";
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.day = GetAddingDataDay(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.year = GetAddingDataYear(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.function = "EncGirl_GenQuest_GetLoverFather";
			DialogExit();	
		break;
		// Генератор "A damsel in the jungle"
		
		// Генератор "Captain's request"
		case "CaptainComission_1":
			dialog.text = RandPhraseSimple("Stój! Stój, kapitanie! Proszę.","Kapitanie, proszę, zaczekaj, błagam cię...");
			link.l1 = LinkRandPhrase("Co? Zabrakło ci tchu?","Podnieś swój miecz, tchórzu!","Co tam? Zapomniałeś spisać testament?");
			link.l1.go = "CaptainComission_2";
		break;
		
		case "CaptainComission_2":
			dialog.text = "Poczekaj... Jestem ranny i zbyt słaby, by dalej walczyć... Nie proszę o litość, ale mam niedokończone sprawy. Proszę, obiecaj mi, że spełnisz ostatnią wolę umierającego człowieka.";
			link.l1 = RandPhraseSimple("Nie bądź mięczakiem, kapitanie, zaakceptuj śmierć jak przystało na mężczyznę!","Kapitanie, co za sentymentalność? Wokół szaleje bitwa, więc dokończmy to, co zaczęliśmy.");
			link.l1.go = "CaptainComission_21";
			link.l2 = "Mów teraz i bądź szybki.";
			link.l2.go = "CaptainComission_22";
		break;
		
		case "CaptainComission_21":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "CaptainComission_22":		
			if(rand(1) == 0) // "Ransom"
			{
				CaptainComission_Init(NPChar);
				dialog.text = "Powiedz "+pchar.GenQuest.CaptainComission.Name+" z osady "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City)+", że nie zdołałem spełnić jego prośby... zanim miałem czas... Niech mi wybaczy...";
				link.l1 = RandPhraseSimple("I to wszystko?! Dobrze, mogę to zrobić. Hej, przyjacielu...","Dobrze, powiem mu, jeśli będę miał czas. Hej, przyjacielu...");
				link.l1.go = "CaptainComission_22_1";
				link.l2 = "Nie sądzę. Nie mam czasu na takie bzdury. Dokończmy, co zaczęliśmy.";
				link.l2.go = "CaptainComission_22_2";
			}
			else // "Operation 'Galleon'"
			{			
				CaptainComission_GaleonInit(NPChar);
				dialog.text = "Proszę, powiedz kapitanowi patrolu "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Imię")+"Gen"))+"  '"+pchar.GenQuest.CaptainComission.ShipTypeName+"' "+pchar.GenQuest.CaptainComission.Name+", że nie powinien pokazywać się w "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Voc")+"... "+"Władze są świadome prawdziwych okoliczności jego śmierci "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Imię")+"Gen"))+" ' "+pchar.GenQuest.CaptainComission.VictimShipName+"... czas jest krótki, wkrótce zostanie aresztowany... płynie do "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Acc")+" z "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City1+"Gen")+", podróż zajmie prawie piętnaście dni... ahh ... trzeba się pośpieszyć..."; // belamour gen
				link.l1 = RandPhraseSimple("Nic nie obiecuję, ale spróbuję przy okazji. Hej, przyjacielu...","Dobrze, powiem mu, jeśli będę miał czas. Hej, przyjacielu...");
				link.l1.go = "CaptainComission_300";
			}					
		break;
		
		case "CaptainComission_22_1":
			ReOpenQuestHeader("CaptainComission1");
			AddQuestRecord("CaptainComission1", "1");
			AddQuestUserData("CaptainComission1", "sShipName", pchar.GenQuest.CaptainComission.ShipName);
			AddQuestUserData("CaptainComission1", "sCapName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));	
			SetFunctionTimerCondition("CaptainComission_Speak", 0, 0, 30, false);
			SetFunctionTimerCondition("CaptainComission_SellSlave", 0, 0, 15 + rand(5), false);
			LAi_KillCharacter(NPChar);
			LAi_SetPlayerType(pchar); 
			pchar.GenQuest.CaptainComission = "Begin_1";
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			DialogExit();	
		break;
		
		case "CaptainComission_22_2":
			dialog.text = "Co za okrucieństwo! Mam nadzieję, że odpowiesz za to.";
			link.l1 = "I za znacznie więcej...";
			link.l1.go = "CaptainComission_22_3";
		break;
		
		case "CaptainComission_22_3":
			ReOpenQuestHeader("CaptainComission1");
			AddQuestRecord("CaptainComission1", "1");
			AddQuestUserData("CaptainComission1", "sShipName", pchar.GenQuest.CaptainComission.ShipName);
			AddQuestUserData("CaptainComission1", "sCapName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));
			SetFunctionTimerCondition("CaptainComission_Speak", 0, 0, 30, false);
			SetFunctionTimerCondition("CaptainComission_SellSlave", 0, 0, 15 + rand(5), false);
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			pchar.GenQuest.CaptainComission = "Begin_2";
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "CaptainComission_3":
			dialog.text = LinkRandPhrase("Słucham cię, "+GetAddress_Form(pchar)+".","Czego chciałeś?","Jak mogę ci pomóc?");
			if (pchar.GenQuest.CaptainComission == "Begin_1" || pchar.GenQuest.CaptainComission == "Begin_2") // лесник - доп.проверка если есть квест. для перехода .
			{	
			link.l1 = "Czy jesteś "+pchar.GenQuest.CaptainComission.Name+"? Mam z tobą interesy. Kapitan "+pchar.GenQuest.CaptainComission.CapName+" poprosił mnie, abym przekazał ci ważną informację.";
			link.l1.go = "CaptainComission_4";
			break;
			}
			link.l2 = "Nie, nic...";
			link.l2.go = "exit";
			NextDiag.TempNode = "CaptainComission_3"; // лесник - переход чтобы не вызывал баг при повтороном обращении
		break;
		
		case "CaptainComission_4":
			dialog.text = "Naprawdę? Dobrze. Więc, czego chce kapitan "+pchar.GenQuest.CaptainComission.CapName+"chciał, żebym wiedział?";
			link.l1 = "Poprosił mnie, abym ci powiedział, że nie będzie w stanie spełnić twojej prośby.";
			link.l1.go = "CaptainComission_5";
		break;
		
		case "CaptainComission_5":
			dialog.text = "O czym ty mówisz?! Znam go od lat, to bardzo uczciwy człowiek. Na pewno nie mógł ci tego powiedzieć!";
			link.l1 = "Powiedzmy, że to było z powodów niezależnych od niego. Inaczej mówiąc - to było jego ostatnie życzenie.";
			link.l1.go = "CaptainComission_6";
		break;
		
		case "CaptainComission_6":
			CaptainComission_GetPirateIsland();
			CaptainComission_GetFamilyType();
			if(pchar.GenQuest.CaptainComission == "Begin_1")
			{
				dialog.text = "Ach, to zupełnie nie na miejscu! Tyle czasu zmarnowane\n"+"Kapitanie, w takim razie muszę cię prosić o pomoc. Piraci z "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.PiratesCity+"Generał")+"pojmały mojego krewnego"+pchar.GenQuest.CaptainComission.SlaveName+" i żądają za niego okupu. Czy mógłbyś podjąć się tej misji? Nagroda powinna być całkiem hojna.";
				link.l1 = "Niestety, mam inne plany.";
				link.l1.go = "CaptainComission_6_1";
				link.l2 = "Spróbuję ci pomóc, jeśli wyjaśnisz to bardziej szczegółowo.";
				link.l2.go = "CaptainComission_6_2";
			}
			
			if(pchar.GenQuest.CaptainComission == "Begin_2")
			{
				dialog.text = "Ach, to jest zupełnie nie na miejscu! Tyle czasu zmarnowane\nA co z kuframi?";
				link.l1 = "Umm... jakie skrzynie?";
				link.l1.go = "CaptainComission_6_3";
				pchar.GenQuest.CaptainComission.CanFindChest = true;
			}	
		break;
		
		case "CaptainComission_6_1":
			dialog.text = "To szkoda, kapitanie... Szkoda, że nie chcesz mi pomóc.";
			link.l1 = "To nie kwestia mojej woli, mój przyjacielu. Musisz zrozumieć. Żegnaj.";
			link.l1.go = "CaptainComission_6_1End";
		break;
		
		case "CaptainComission_6_2":
			dialog.text = "Wczoraj otrzymałem list od "+ChangeNameCase(NAMETYPE_MAIN,pchar.GenQuest.CaptainComission.PirateName,NAME_ACC)+", w którym zawiadamiał mnie, że okup będzie wyższy, a także groził sprzedażą go w niewolę. Zmarły kapitan powinien był zawiadomić "+ChangeNameCase(NAMETYPE_MAIN,pchar.GenQuest.CaptainComission.PirateName,NAME_ACC)+", że zgadzam się z wcześniejszymi warunkami i dokonam zaliczki. Ale teraz widzę, dlaczego piraci podnieśli stawki.";
			link.l1 = "A co proponujesz?";
			link.l1.go = "CaptainComission_6_21";
		break;
		
		case "CaptainComission_6_3":
			dialog.text = "Oh, "+GetSexPhrase("kamracie","dziewko")+", Czuję tu zdradę. Ostrzegam cię, że to jest bardzo niebezpieczne i może mieć straszne konsekwencje. Kapitanie "+pchar.GenQuest.CaptainComission.CapName+"miał trzy skrzynie pełne złota, które powinien był przekazać"+ChangeNameCase(NAMETYPE_MAIN,pchar.GenQuest.CaptainComission.PirateName,NAME_DAT)+" na "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.PiratesCity+"Zgoda")+" jako okup za jednego człowieka -  "+pchar.GenQuest.CaptainComission.SlaveName+"Jeśli zaś chciał, byś do nas przyszedł, nie mógł zapomnieć wspomnieć o kufrach.";
			link.l1 = "Kiedy wypowiadał ostatnie słowa, nie wyglądało na to, że skończył zdanie. Miałem nadzieję, że powiesz mi więcej.";
			link.l1.go = "CaptainComission_6_31";
		break;
		
		case "CaptainComission_6_1End":
			AddQuestRecord("CaptainComission1", "3");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCharType", GetStrSmallRegister(XI_ConvertString("Family" + pchar.GenQuest.CaptainComission.FamilyType + "Gen")));
			CloseQuestHeader("CaptainComission1");
			sld = CharacterFromID("CapComission_1"); // удаление если послал нахуй. лесник.
			sld.LifeDay = 0;
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			DialogExit();	
		break;
		
		case "CaptainComission_6_21":
			dialog.text = "Nie mam innego wyboru... Już zebrałem wymaganą sumę, 150 000 pesos. Proszę cię, byś ją dostarczył do "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.PiratesCity+"Acc")+" i przyprowadź tu mojego krewnego. Zapłacę ci 40 000, gdy tylko to zostanie zrobione.";
			link.l1 = "Dobrze, jestem gotów.";
			link.l1.go = "CaptainComission_6_22";
			link.l2 = "Niestety, mam inne plany.";
			link.l2.go = "CaptainComission_6_1";			
		break;
		
		case "CaptainComission_6_22":
			dialog.text = "W takim razie weź pieniądze, a niech nasz Pan cię pobłogosławi. Ale proszę, pośpiesz się. Obawiam się, że "+ChangeNameCase(NAMETYPE_MAIN,pchar.GenQuest.CaptainComission.PirateName,NAME_NOM)+" nie będzie czekać i sprzeda biedną duszę w niewolę.";
			link.l1 = "Czekaj tu na mnie. Nie sądzę, by to zajęło zbyt wiele czasu.";
			link.l1.go = "CaptainComission_6_22End";
		break;
		
		case "CaptainComission_6_22End":
			AddQuestRecord("CaptainComission1", "4");
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sPirateName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sPirateCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc"));
			AddQuestUserData("CaptainComission1", "sFamilyType", GetStrSmallRegister(XI_ConvertString("Family" + pchar.GenQuest.CaptainComission.FamilyType + "Gen")));
			AddQuestUserData("CaptainComission1", "sSlaveName",pchar.GenQuest.CaptainComission.SlaveName);
			addMoneyToCharacter(pchar, 150000);
			pchar.GenQuest.CaptainComission = "Begin_11";
			pchar.GenQuest.CaptainComission.AfterTavernSpeak = "goodSpeak";
			pchar.GenQuest.CaptainComission.GetSlave = "NoSlave";
			pchar.GenQuest.CaptainComission.toMayor = true;
			SetFunctionTimerCondition("CaptainComission_30DaysIsLeft", 0, 0, 30, false);
			NextDiag.TempNode = "CaptainComission_7";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			DialogExit();
		break;
		
		case "CaptainComission_6_31":
			dialog.text = "To nie ma znaczenia\nLudzie, którzy zebrali okup, nie będą się przejmować. Potrzebują tylko wyniku, żywego i w jednym kawałku - "+pchar.GenQuest.CaptainComission.SlaveName+"Więc nie trać czasu.";
			link.l1 = "A co jeśli odmówię?";
			link.l1.go = "CaptainComission_6_32";
		break;
						
		case "CaptainComission_6_32":
			dialog.text = "Tak naprawdę, nie potrzebuję twojej zgody. Po prostu informuję cię, że jeśli nie dostarczysz "+pchar.GenQuest.CaptainComission.SlaveName+" żywy i zdrów do tawerny, poślę za tobą łowców nagród...";
			link.l1 = "Hmm... To poważna sprawa. A jeśli to zrobię?";
			link.l1.go = "CaptainComission_6_33";
		break;
		
		case "CaptainComission_6_33":
			dialog.text = "W takim razie omówimy to dalej.";
			link.l1 = "Dobrze... Zobaczmy, jak to się potoczy.";
			link.l1.go = "CaptainComission_6_33End";
		break;
		
		case "CaptainComission_6_33End":
			AddQuestRecord("CaptainComission1", "5");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCapName",pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sPirateName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sPirateCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc"));
			AddQuestUserData("CaptainComission1", "sSlaveName",pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			pchar.GenQuest.CaptainComission = "Begin_22";
			pchar.GenQuest.CaptainComission.AfterTavernSpeak = "badSpeak";
			pchar.GenQuest.CaptainComission.GetSlave = "NoSlave";
			pchar.GenQuest.CaptainComission.toMayor = true;
			SetFunctionTimerCondition("CaptainComission_30DaysIsLeft", 0, 0, 30, false);
			NextDiag.TempNode = "CaptainComission_7";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			DialogExit();
		break;
		
		case "CaptainComission_7":
			if(pchar.GenQuest.CaptainComission.GetSlave == "NoSlave")
			{
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = LinkRandPhrase("Witaj, kapitanie "+GetFullName(pchar)+" . Jakieś wieści?","Więc, kapitanie, czy już dostarczyłeś okup?","Witaj, mam nadzieję, że przybyłeś z dobrymi wieściami?");
					if(makeint(pchar.money)>=150000)
					{
						link.l1 = "Niestety, moje plany się zmieniły, więc muszę zerwać naszą umowę.";
						link.l1.go = "CaptainComission_7_1";
					}
					link.l2 = "Jeszcze nie. Wciąż jestem zajęty tym.";
					link.l2.go = "CaptainComission_7_2";
				}
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "badSpeak")
				{
					dialog.text = LinkRandPhrase("O, miło cię powitać, kapitanie "+GetFullName(pchar)+" . Jakieś dobre wieści?","Więc, kapitanie, czy uratowałeś naszego cierpiącego przyjaciela?","Miło cię widzieć żywego i zdrowego, kapitanie. Jaki jest status naszej wspólnej sprawy?");
					link.l1 = "Nie ma jeszcze żadnych wieści, ale pracuję nad tym.";
					link.l1.go = "CaptainComission_7_3";
					link.l2 = "Słuchaj, przyjacielu, a dlaczego próbujesz mnie obarczyć odpowiedzialnością za tę umowę?";
					link.l2.go = "CaptainComission_7_4";
				}
			}
			if(pchar.GenQuest.CaptainComission.GetSlave == "GetSlave")
			{
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = LinkRandPhrase("Witaj, kapitanie "+GetFullName(pchar)+"  Jakieś wieści?","Więc, kapitanie, czy już dostarczyłeś okup?","Cześć, mam nadzieję, że przyniosłeś dobre wieści?");
					link.l1 = "Tak. Twoja prośba została spełniona, "+pchar.GenQuest.CaptainComission.SlaveName+" jest na pokładzie mojego statku i szykuje się do zejścia na brzeg.";
					link.l1.go = "CaptainComission_30";
				}
				else
				{
					dialog.text = LinkRandPhrase("O, miło cię powitać, kapitanie "+GetFullName(pchar)+"  Jakieś dobre wieści?","Więc, kapitanie, czy uratowałeś naszego cierpiącego przyjaciela?","Cieszę się, że widzę cię żywego i w pełni sił, kapitanie. Jaki jest status naszej wspólnej sprawy?");	
					link.l1 = "Przyprowadziłem człowieka, o którym rozmawialiśmy. Jest na pokładzie mojego statku.";
					link.l1.go = "CaptainComission_32";
				}
			}
			if(pchar.GenQuest.CaptainComission.GetSlave == "SlaveDied")
			{
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = LinkRandPhrase("Cześć, kapitanie "+GetFullName(pchar)+"  Jakieś wieści?","Więc, kapitanie, czy już dostarczyłeś okup?","Cześć, mam nadzieję, że przyszedłeś z dobrymi wieściami?");
					link.l1 = "Pozdrowienia, "+pchar.GenQuest.CaptainComission.Name+"Muszę cię zmartwić.";
					link.l1.go = "CaptainComission_50";
				}
				else
				{
					dialog.text = LinkRandPhrase("O, miło cię powitać, kapitanie "+GetFullName(pchar)+"   Czy jakieś dobre wieści?","Więc, kapitanie, czy uratowałeś naszego cierpiącego przyjaciela?","Cieszę się, że widzę cię żywego i w dobrym zdrowiu, kapitanie. Jaki jest status naszej wspólnej sprawy?");
					link.l1 = "Mężczyzna, za którego się wstawiałeś, nie żyje.";
					link.l1.go = "CaptainComission_60";
				}
			}
		break;
		
		case "CaptainComission_30":
			dialog.text = "Dziękuję ci, kapitanie, wyświadczyłeś naszej rodzinie wielką przysługę. Oto twoja nagroda... Są tu trzy skrzynie - to równo 40 000 pesos. Proszę, wybacz mi, muszę go teraz zobaczyć.";
			link.l1 = "Oczywiście, miłego spotkania i powodzenia wam obojgu.";
			link.l1.go = "CaptainComission_30_1";
			if(CheckAttribute(pchar, "GenQuest.CaptainComission.SlaveAddMoney"))
			{
				link.l2 = "Doskonale rozumiem twoją niecierpliwość, ale zaszły nieprzewidziane okoliczności, które zmusiły mnie do poniesienia dodatkowych kosztów.";
				link.l2.go = "CaptainComission_31";
			}	
		break;
		
		case "CaptainComission_30_1":
			//addMoneyToCharacter(pchar, 25000);
			TakeNItems(pchar, "chest", 3);
			Log_Info("You have received credit chests");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("CaptainComission1", "14");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;
		
		case "CaptainComission_31":
			//addMoneyToCharacter(pchar, 25000);
			TakeNItems(pchar, "chest", 2);
			Log_Info("You have received credit chests");
			PlaySound("interface\important_item.wav");
			dialog.text = "Nie rozumiem... Już uzgodniliśmy kwotę twojej zapłaty, czyż nie?";
			link.l1 = "Mieliśmy, ale zamiast 150000 pesos musiałem zapłacić 200000, nie wspominając już o podróży na Barbados.";
			link.l1.go = "CaptainComission_31_1";
		break;
		
		case "CaptainComission_31_1":
			dialog.text = "Kapitanie, to tylko wynik twojej własnej opieszałości. Piraci nie stawiali mi żadnych dodatkowych żądań. Co za dziwny jegomość, próbujący zyskać coś kosztem trudów innych?";
			link.l1 = "Dobrze, widzę, że to daremne próbować cokolwiek ci wyjaśniać...";
			link.l1.go = "CaptainComission_31_1End";
		break;
		
		case "CaptainComission_31_1End":
			AddQuestRecord("CaptainComission1", "15");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");			
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;

		case "CaptainComission_32":
			dialog.text = "Doskonale! A miałeś wątpliwości, że będziemy dobrze współpracować.";
			link.l1 = "Ale musiałem sporo wydać na tę sprawę.";
			link.l1.go = "CaptainComission_32_1";
		break;
		
		case "CaptainComission_32_1":
			GetSlaveSpeciality();
			dialog.text = "Ja wiem, ja wiem... Ale to i twoja wina. Jak mogłeś zatopić trzy skrzynie złota, które musieliśmy dosłownie wytrząsnąć ze skarbca, żeby "+NationNameNominative(sti(pchar.GenQuest.CaptainComission.Nation))+" mógłby mieć takiego specjalistę "+pchar.GenQuest.CaptainComission.SlaveSpeciality+"?";
			link.l1 = "Wiedz, że nie oddam go tobie bez odpowiedniej rekompensaty.";
			link.l1.go = "CaptainComission_32_2";
		break;
		
		case "CaptainComission_32_2":
			dialog.text = "„Cóż, jesteś mądrym człowiekiem, z pewnością rozumiesz, że na targowanie się jest już za późno. Mogliśmy zatrzymać twój statek z ładunkiem.\nAle rekompensata została wcześniej zapewniona. Dlatego rząd "+NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation))+" gratuluje ci udanej operacji i wręcza ci ten cenny podarunek oraz skromną nagrodę.";
			link.l1 = "Hmm... Cóż, wciąż lepsze niż nic. Weź swojego cennego specjalistę.";
			link.l1.go = "CaptainComission_32_2End";
		break;
		
		case "CaptainComission_32_2End":
			AddQuestRecord("CaptainComission1", "16");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sSpeciality", pchar.GenQuest.CaptainComission.SlaveSpeciality);
			AddQuestUserData("CaptainComission1", "sNation", NationNameNominative(sti(pchar.GenQuest.CaptainComission.Nation)));
			CloseQuestHeader("CaptainComission1");			
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 15);			
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Item); 
			TakeNItems(pchar, "jewelry5", 100);
			PlaySound("interface\important_item.wav");
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;
		
		case "CaptainComission_7_1":
			dialog.text = "Ach, co za szkoda! Już straciłem za dużo czasu. Naprawdę mnie zawiodłeś, kapitanie!";
			link.l1 = "Rozumiem, ale okoliczności były nie do pokonania. Oto twoje pieniądze.";
			link.l1.go = "CaptainComission_7_1End";
		break;
		
		case "CaptainComission_7_1End":
			AddQuestRecord("CaptainComission1", "8");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission1");
			rChar = characterFromId("CapComission_1");
			rChar.lifeDay = 0; 
			pchar.quest.CaptainComission1_30DaysIsLeft.over = "yes";
			addMoneyToCharacter(pchar, -150000);
			ChangeCharacterComplexReputation(pchar,"nobility", -4);
			LAi_CharacterDisableDialog(NPChar);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;
		
		case "CaptainComission_7_2":
			dialog.text = "Czy mógłbyś się pospieszyć? Obawiam się, że piraci znów zmienią warunki umowy.";
			link.l1 = "Nie martw się, damy radę.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;
		
		case "CaptainComission_7_3":
			dialog.text = "Mam nadzieję, że zdajesz sobie sprawę, że czas nie jest po twojej stronie?";
			link.l1 = "Jeszcze raz! Zajmę się tym. Miej cierpliwość.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;
		
		case "CaptainComission_7_4":
			dialog.text = "Boże nas zbaw! Bez nacisku, po prostu pomoc od skromnego Purytanina\nTo twoja własna wina. Zabiłeś kapitana "+pchar.GenQuest.CaptainComission.CapName+", straciliśmy nasze złoto i nie udało się wykupić bardzo cennego człowieka. To teraz prawdziwy ból w dupie i twoja odpowiedzialność. Nawet nie myśl, że jesteś wybaczony... Zapłacisz za wszystko.";
			link.l1 = "Pierd*l się!";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;
		
		// диалоги с управляющим на плантации
		case "CaptainComission_10":
			dialog.text = "Cześć, chciałeś czegoś?";
			link.l1 = "Można zobaczyć właściciela tej plantacji?";
			link.l1.go = "CaptainComission_10_1";
		break;
		
		case "CaptainComission_10_1":
			dialog.text = "Nie ma go tutaj, szuka jednego zbiegłego niewolnika, Ostrze, czy Krew, nie pamiętam... A ja jestem tutejszym zarządcą "+npchar.name+" i mam uprawnienia do załatwiania wszystkich spraw, gdy szef jest na urlopie.";
			link.l1 = "Jesteś? To dobrze... A handel niewolnikami to też twoje sprawki?";
			link.l1.go = "CaptainComission_10_2";
		break;
		
		case "CaptainComission_10_2":
			dialog.text = "Oczywiście. Ile chcesz kupić?";
			link.l1 = "Tylko jeden.";
			link.l1.go = "CaptainComission_10_3";
		break;
		
		case "CaptainComission_10_3":
			dialog.text = "Ehh... Czy jesteś pewien, że potrzebujesz tylko jednego niewolnika?";
			link.l1 = "Oczywiście, że tak. Jego imię to "+pchar.GenQuest.CaptainComission.SlaveName+".";
			link.l1.go = "CaptainComission_10_4";
		break;
		
		case "CaptainComission_10_4":
			if(rand(1) == 0)
			{
				dialog.text = "Z pewnością zdajesz sobie sprawę, że cena jednego niewolnika będzie wyższa w porównaniu do ceny jednego niewolnika w większej partii?";
				link.l1 = "Oczywiście, że tak. Czy możesz podać cenę?";
				link.l1.go = "CaptainComission_11";
			}
			else
			{
				if(rand(100) < makeint(sti(pchar.rank) + 0.75 * GetSummonSkillFromName(pchar, SKILL_FORTUNE)))
				{
					dialog.text = "Hmm... Mam nadzieję, że wiesz, za kim się wstawiasz?";
					link.l1 = "Co masz na myśli?";
					link.l1.go = "CaptainComission_12";
				}
				else
				{
					dialog.text = "Ach, ten obibok. Nie dałbym za niego nawet grosza. Od kiedy go tu przywieziono, nigdy nie wykonał żadnej prawdziwej pracy. Nie mam pojęcia, dlaczego pułkownik marnuje pieniądze na tych państwowych skazańców. Teraz czarni to inna historia. Są świetnymi robotnikami, to w ich krwi, zarówno silni, jak i posłuszni. I uwierz mi, mogą wykonać absolutnie każdą pracę. Zbieranie trzciny cukrowej czy służba jako zarządca - zrobią to najlepiej jak potrafią, wystarczy im tylko trochę 'przekonywania'...";
					link.l1 = "Mój przyjacielu, nie obchodzi mnie twój czarny lud. Interesuje mnie tylko ten włóczęga, o którym mówiłeś, i tak nie pożyje długo, potrzebuję go jako mięso armatnie i zapłacę za niego więcej.";
					link.l1.go = "CaptainComission_13";
				}
			}
		break;
		
		case "CaptainComission_11":
			dialog.text = "Jasne, jasne. Pozwól, że spojrzę na cennik\nOooo!!! 150000 pesos.";
			link.l1 = "Wow...";
			link.l1.go = "CaptainComission_11_1";
		break;
		
		case "CaptainComission_11_1":
			dialog.text = "Cena powinna być na liście cen. Tutaj. Wiesz, nie do końca to pojmuję. Inni niewolnicy sprzedawani są w rozsądnych cenach, ale ten jest sprzedawany za fortunę...";
			if(sti(pchar.money) >= 150000)
			{
				link.l1 = "Chyba rozumiem, o co tu chodzi... Dobra, oto pieniądze, a ja zabieram go ze sobą.";
				link.l1.go = "CaptainComission_14";
			}	
			link.l2 = "Hmm... Ale nie wykupuję zakładnika, chcę kupić zwykłego niewolnika. Czy nie uważasz, że za taką sumę można by kupić porządny, w pełni wyposażony statek?";
			link.l2.go = "CaptainComission_15";
		break;
		
		case "CaptainComission_12":
			dialog.text = "To nie jest zwykły niewolnik. Pułkownik Bishop nawet rozkazał go strzec.";
			link.l1 = "Więc nie mogę go nawet kupić?";
			link.l1.go = "CaptainComission_12_1";
		break;
		
		case "CaptainComission_12_1":
			dialog.text = "Z pewnością możesz. Pułkownik ustalił jego cenę - 200000 pesos, zgodnie z cennikiem.";
			if(sti(pchar.money) >= 200000)
			{
				link.l1 = "O rany! Cóż, ten pułkownik musi wiedzieć, jakiego rodzaju osoba z tego niewolnika...";
				link.l1.go = "CaptainComission_16";
			}	
			link.l2 = "Hmm... Ale ja nie wykupuję zakładnika, chcę kupić zwykłego niewolnika. Nie sądzisz, że za taką kwotę można by kupić porządny, w pełni wyposażony statek?";
			link.l2.go = "CaptainComission_15";	
		break;
		
		case "CaptainComission_13":
			dialog.text = "Ach, tak. Przepraszam. Pozwól mi zobaczyć cennik, który zostawił Biskup.\nAha, oto jest. Cóż. O!.. 150 000 pesos!..";
			if(sti(pchar.money) >= 15000)
			{
				link.l1 = "Najwyraźniej to jakiś błąd. Z pewnością zdajesz sobie sprawę, że żaden niewolnik nie może kosztować aż tyle. Przypuszczam, że jest jedno dodatkowe zero, a suma powinna wynosić 15000 pesos. I to wciąż za dużo, biorąc pod uwagę, że to obibok i idiota.";
				link.l1.go = "CaptainComission_17";
			}	
			link.l2 = "Hmm... Ale ja nie wykupuję zakładnika, chcę kupić zwykłego niewolnika. Czy nie sądzisz, że za taką sumę można by kupić porządny, w pełni wyposażony statek?";
			link.l2.go = "CaptainComission_15";
		break;
		
		case "CaptainComission_14":
			addMoneyToCharacter(pchar, -150000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 150000;
			dialog.text = "Świetnie! To wspaniale! Zaraz go tu przyprowadzą... Ehh... Może herbata?";
			link.l1 = "Nie, dziękuję... Pozdrów pułkownika Bishopa...";
			link.l1.go = "CaptainComission_14_1";
		break;
		
		case "CaptainComission_14_1":
			dialog.text = "A od kogo, jeśli mogę wiedzieć?";
			link.l1 = "Mmm... Nieważne, nie zawracaj sobie głowy. Żegnaj.";
			link.l1.go = "CaptainComission_14_1End";
		break;
		
		case "CaptainComission_14_1End":
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_15":
			dialog.text = "Przykro mi, ale nic nie mogę zrobić. Oto cennik.";
			link.l1 = "Och, przestań już z tym 'cennik, cennik...' Nie możecie zdecydować najprostszej rzeczy bez Biskupa. Powiedz mu... Nieważne, nie mów mu niczego.";
			link.l1.go = "CaptainComission_15_1";
		break;
		
		case "CaptainComission_15_1":
			dialog.text = "Więc nie zamierzasz kupić tego niewolnika.";
			link.l1 = "Nie. Żegnaj.";
			link.l1.go = "CaptainComission_15_1End";
		break;
		
		case "CaptainComission_15_1End":
			OfficersReaction("bad");
			AddQuestRecord("CaptainComission1", "30");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			NextDiag.TempNode = "CaptainComission_19";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_16":
			dialog.text = "Nic o tym nie wiem. Mam tylko konkretne instrukcje dotyczące sprzedaży tego konkretnego niewolnika.";
			link.l1 = "Bzdura... Dobra, nieważne. Oto pieniądze. Przyprowadź niewolnika.";
			link.l1.go = "CaptainComission_16_1"; 
		break;
		
		case "CaptainComission_16_1":
			addMoneyToCharacter(pchar, -200000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 200000;
			dialog.text = "Oczywiście. Zostanie dostarczony tutaj natychmiast.";
			link.l1 = "Żegnaj.";
			link.l1.go = "CaptainComission_16_1End";
		break;
		
		case "CaptainComission_16_1End":
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_17":
			dialog.text = "Hmm... Tak, może masz rację. To musi być pomyłka.";
			link.l1 = "Cóż, jeśli zgodziliśmy się na cenę, czy mogę go teraz zabrać ze sobą?";
			link.l1.go = "CaptainComission_17_1";
		break;
		
		case "CaptainComission_17_1":
			dialog.text = "Tak, oczywiście. Zostanie tu przyprowadzony za chwilę.";
			link.l1 = "Bardzo dobrze. Oto twoje pieniądze... Żegnaj.";
			link.l1.go = "CaptainComission_17_1End";
		break;
		
		case "CaptainComission_17_1End":
			addMoneyToCharacter(pchar, -15000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 15000;
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_18":
			dialog.text = "Chcesz trochę herbaty, kapitanie?";
			link.l1 = "Nie, dzięki.";
			link.l1.go = "exit";
		break;
		
		case "CaptainComission_19":
			dialog.text = "Zdecydowałeś się go kupić.";
			link.l1 = "Nie. Żegnaj.";
			link.l1.go = "exit";
		break;
		
		// диалоги с рабом
		case "CaptainComission_20":
			if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
			{
				dialog.text = "Witaj, kapitanie. Jak mogę pomóc? Nie mogę uwierzyć, że ten koszmar wreszcie się skończył.";
				link.l1 = "Nie mnie powinieneś dziękować, lecz raczej swojemu krewnemu "+pchar.GenQuest.CaptainComission.Name+" z "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Gen")+"Zebrał okup.";
				link.l1.go = "CaptainComission_201";
			}
			else
			{
				dialog.text = "Witaj, kapitanie. Powiedziano mi, że zapłaciłeś za mnie okup. Muszę ci za to podziękować, chociaż zdaję sobie sprawę, że byłeś tylko kurierem.";
				link.l1 = "Nie wyglądasz na zadowolonego z odzyskania wolności. Martwi cię coś?";
				link.l1.go = "CaptainComission_202";
			}
		break;
		
		case "CaptainComission_201":
			dialog.text = "Proszę, jeśli to nie przeszkadza zbytnio w twoich planach, zabierz mnie do niego. Chciałbym mu osobiście podziękować.";
			link.l1 = "Oczywiście, że tak. Chodź, zaprowadzę cię na statek.";
			link.l1.go = "CaptainComission_201_1";
		break;
		
		case "CaptainComission_201_1":
			AddQuestRecord("CaptainComission1", "11");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1.0);
			DialogExit();
		break;
		
		case "CaptainComission_202":
			dialog.text = "By upewnić się co do mojej wolności, muszę znać imiona tych, którzy za nią zapłacili.";
			link.l1 = "Cóż, to ja zapłaciłem, choć nie z własnej woli.";
			link.l1.go = "CaptainComission_202_1";
		break;
		
		case "CaptainComission_202_1":
			dialog.text = "Zatem moje podejrzenia się potwierdziły. Zostałeś zmuszony do tego przez "+NationNamePeople(sti(pchar.GenQuest.CaptainComission.Nation))+"?";
			link.l1 = "Tak, to "+pchar.GenQuest.CaptainComission.Name+" z "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Gen")+".";
			link.l1.go = "CaptainComission_202_2";
		break;
		
		case "CaptainComission_202_2":
			iNation = FindEnemyNation2NationWithoutPirates(sti(pchar.GenQuest.CaptainComission.Nation));	// mitrokosta 
			if(iNation == -1) iNation = rand(NON_PIRATES);
			pchar.GenQuest.CaptainComission.SlaveCity = FindAlliedColonyForNation(iNation, true);
			pchar.GenQuest.CaptainComission.EnemyNation = iNation;
			LAi_SetImmortal(npchar, true);// лесник . откатил .  и защиту  чтоб умники не убили.
			dialog.text = "Widzę. Nie mam pojęcia, co ci obiecali, ale oto układ: zabierz mnie do tawerny "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.SlaveCity+"Gen")+", Tam będę naprawdę bezpieczny. W zamian podzielę się z tobą pewnymi informacjami, które posiadam.";
			link.l1 = "To dobrze, tym bardziej, że jak dotąd niczego nie obiecywali. Chodź ze mną, zaprowadzę cię na mój statek.";
			link.l1.go = "CaptainComission_202_3";
			link.l2 = "Nie będę ryzykować sprowadzania kłopotów na siebie z powodu jakiejś wątpliwej informacji.";
			link.l2.go = "CaptainComission_203";
		break;
		
		
		
		case "CaptainComission_202_3":
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			rChar = characterFromId("CapComission_1");
			ChangeCharacterAddress(rChar, "none", "");			
			rChar.lifeDay = 0; 
			AddQuestRecord("CaptainComission1", "12");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.SlaveCity + "Acc"));
			pchar.quest.CapComission_DeliveSlave.win_condition.l1 = "location";
			pchar.quest.CapComission_DeliveSlave.win_condition.l1.location = pchar.GenQuest.CaptainComission.SlaveCity + "_tavern";
			pchar.quest.CapComission_DeliveSlave.function = "CaptainComission_DeliveSlave";
			LAi_SetActorType(NPChar);
			LAi_ActorFollow(NPChar, PChar, "OpenTheDoors", -1.0); //лесник  идем за ГГ
			DialogExit();
		break;
		
		case "CaptainComission_203":
			dialog.text = "Niestety, nie mogę ci tego teraz ujawnić. To może oznaczać kłopoty dla nas obu.";
			link.l1 = "Wszystko tym bardziej... Podążaj za mną i żadnych głupstw, proszę. Uważaj się za ponownie aresztowanego.";
			link.l1.go = "CaptainComission_203_1";
		break;
		
		case "CaptainComission_203_1":
			AddQuestRecord("CaptainComission1", "13");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1.0); //лесник - провожаем на корабль типа..
			DialogExit();
		break;
		
		case "CaptainComission_50":
			dialog.text = "Co?! Piraci znów zmienili umowę? Ale nie mogę już wyciągać więcej pieniędzy z interesu! W ten sposób wkrótce zbankrutuję!";
			link.l1 = "Nie... Twój krewny zginął na plantacjach Barbadosu podczas nieudanej próby ucieczki.";
			link.l1.go = "CaptainComission_51";
		break;
		
		case "CaptainComission_51":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			dialog.text = "Och... Jestem całkowicie załamany... Jak to się stało?";
			link.l1 = "Piratów nie zadowolił okup i sprzedali go w niewolę. Udałem się po niego na Barbados, ale nie udało mi się go uratować...";
			link.l1.go = "CaptainComission_52";
		break;
		
		case "CaptainComission_52":
			dialog.text = "Jezu! Co się dzieje?\nW porządku, kapitanie, dziękuję za udział. I proszę, zwróć pieniądze, które ci dałem.";
			link.l1 = "Mój wydatek przekroczył wszelkie oczekiwania, więc zatrzymam twoje pieniądze... Żegnaj.";
			link.l1.go = "CaptainComission_53";
			if(sti(pchar.money) >= 150000)
			{
				link.l2 = "Pewnie, weź to... Przepraszam, że nie udało mi się ci pomóc... Żegnaj.";
				link.l2.go = "CaptainComission_54";
			}
		break;
		
		case "CaptainComission_53":
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			OfficersReaction("bad");			
			AddQuestRecord("CaptainComission1", "22");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0; 			
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_54":
			OfficersReaction("good");
			addMoneyToCharacter(pchar, -150000);
			AddQuestRecord("CaptainComission1", "23");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0; 			
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_60":
			dialog.text = "To zbyt źle. Nie masz pojęcia, jak bardzo źle to naprawdę jest...";
			link.l1 = "Nie mogę nic na to poradzić. Nawet cieszę się, że wszystko potoczyło się w ten sposób. Żegnaj.";
			link.l1.go = "CaptainComission_61";
		break;
		
		case "CaptainComission_61":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -15);
			AddQuestRecord("CaptainComission1", "32");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0; 			
			DeleteAttribute(pchar,"GenQuest.CaptainComission");			
			DialogExit();
		break;
		
		// диалог с рабом в колодках
		case "CaptainComission_70":
			dialog.text = "Napój... kapitanie, przynieś trochę wody...";
			link.l1 = "Ej, kumplu, czyżbyś nie był "+pchar.GenQuest.CaptainComission.SlaveName+"?";
			link.l1.go = "CaptainComission_71";
		break;
		
		case "CaptainComission_71":
			dialog.text = "Tak... To ja...";
			link.l1 = "Słuchaj! Jeśli nie chcesz zginąć tutaj jak płastuga na mieliźnie, zbierz się i słuchaj mnie. Wiesz, gdzie znajduje się latarnia morska na Barbadosie?";
			link.l1.go = "CaptainComission_72";
		break;
		
		case "CaptainComission_72":
			dialog.text = "Ja robię...";
			link.l1 = "Gdy tylko nadarzy się okazja, biegnij tam. Spróbuję zaaranżować taką okazję dla ciebie.";
			link.l1.go = "CaptainComission_73";			
		break;
		
		case "CaptainComission_73":	
			LAi_SetPlayerType(pchar); 
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_LockFightMode(pchar, false);			
			sTemp = GetNationNameByType(GetCityNation("Bridgetown"))  + "_citizens";
			for(i = 0; i < 3; i++)
			{
				if (GetCharacterIndex("SlaveGuard_" + i) == -1) continue;
				sld = CharacterFromID("SlaveGuard_" + i);			
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "SlaveGuards");
			}
						
			LAi_group_SetRelation("SlaveGuards", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetRelation("SlaveGuards", sTemp, LAI_GROUP_NEITRAL);			
			LAi_group_SetAlarmReaction("SlaveGuards", sTemp, LAI_GROUP_NEITRAL, LAI_GROUP_FRIEND);
			LAi_group_FightGroups("SlaveGuards", LAI_GROUP_PLAYER, true);
			LAi_group_SetAlarm("SlaveGuards", LAI_GROUP_PLAYER, 0);
			LAi_group_SetCheck("SlaveGuards", "OpenTheDoors");
			LAi_group_SetCheckFunction("SlaveGuards", "CaptainComission_GuardsAfter");
			
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn"); 
		break;
		
		// диалог охранников раба
		case "CaptainComission_80":
			dialog.text = RandPhraseSimple("Śmiało pytaj, kapitanie, ale szybko, jestem na służbie.","Mów, ale mów szybko i nie zawracaj mi głowy błahostkami.");
			link.l1 = RandPhraseSimple("Czy możesz mi powiedzieć, jak mogę znaleźć pewnego niewolnika? Ma na imię "+pchar.GenQuest.CaptainComission.SlaveName+".","Na tej plantacji powinien być niewolnik o imieniu "+pchar.GenQuest.CaptainComission.SlaveName+" Możesz mi powiedzieć, jak mógłbym z nim porozmawiać?");
			link.l1.go = "CaptainComission_81";			
		break;
		
		case "CaptainComission_81":
			dialog.text = "Dziś jest ukarany i pod strażą.";
			link.l1 = "Dzięki.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_80";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "CaptainComission_85":
			dialog.text = "Dziękuję... kapitanie, uratowałeś mi życie...";
			link.l1 = "Biegnij do latarni Barbados i czekaj tam na mnie.";
			link.l1.go = "CaptainComission_86";
		break;
		
		case "CaptainComission_86":
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1.0);
			sTemp = GetNationNameByType(GetCityNation("Bridgetown"))  + "_citizens";
			LAi_group_AttackGroup(sTemp, LAI_GROUP_PLAYER);
			DialogExit();
		break;
		
		case "CaptainComission_90":
			if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
			{
				dialog.text = "Kapitanie, jak mogę ci podziękować? Wciąż nie mogę uwierzyć, że ta męka wreszcie się skończyła.";
				link.l1 = "Już dziękował mi twój krewny "+pchar.GenQuest.CaptainComission.Name+" z "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Gen")+" Działam zgodnie z jego instrukcjami.";
				link.l1.go = "CaptainComission_91";
			}
			if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "badSpeak")
			{
				dialog.text = "Dziękuję, kapitanie. Nie wiem, w czyim imieniu działasz, ale nawet zła wolność jest lepsza niż dobra niewola.";
				link.l1 = "Co masz na myśli?";
				link.l1.go = "CaptainComission_92";
			}
		break;
		
		case "CaptainComission_91":
			dialog.text = "Jeśli to nie zburzy zbytnio twoich planów, proszę, zabierz mnie do niego. Jestem już po prostu zmęczony tym wszystkim.";
			link.l1 = "Oczywiście, że... jeśli uda nam się stąd wyjść żywymi.";
			link.l1.go = "CaptainComission_91End";
		break;
		
		case "CaptainComission_91End":
			pchar.GenQuest.CaptainComission = "toOurTavern";
			rChar = CharacterFromID("CapComission_Slave");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;
		
		case "CaptainComission_92":
			dialog.text = "A czy mogę poznać imiona ludzi, którzy zapłacili za moją wolność?";
			link.l1 = "Cóż, właściwie to mi nie zapłacono. Nie pozostawili mi wyboru.";
			link.l1.go = "CaptainComission_93";
		break;
		
		case "CaptainComission_93":
			dialog.text = "Więc, moje podejrzenia się potwierdziły. Zostałeś zmuszony do tego przez "+NationNamePeople(sti(pchar.GenQuest.CaptainComission.Nation))+"?";
			link.l1 = "Tak, to "+pchar.GenQuest.CaptainComission.Name+" z "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Generał")+".";
			link.l1.go = "CaptainComission_94";
		break;		
		
		case "CaptainComission_94":
			iNation = FindEnemyNation2NationWithoutPirates(sti(pchar.GenQuest.CaptainComission.Nation));	// mitrokosta
			if(iNation == -1) iNation = rand(NON_PIRATES);
			pchar.GenQuest.CaptainComission.SlaveCity = FindAlliedColonyForNation(iNation, true);
			pchar.GenQuest.CaptainComission.EnemyNation = iNation;
			LAi_SetImmortal(npchar, true);// лесник . откатил .  и защиту  чтоб умники не убили.
			dialog.text = "Nie mam pojęcia, co ci obiecali, ale oto umowa: zabierz mnie do tawerny "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.SlaveCity+"Gen")+"Tam będę naprawdę bezpieczny. W zamian podzielę się z tobą pewnymi informacjami, które posiadam.";
			link.l1 = "To dobrze, tym bardziej, że do tej pory niczego nie obiecali. Chodź ze mną, odprowadzę cię na mój statek.";
			link.l1.go = "CaptainComission_95";
			link.l2 = "Nie zaryzykuję sprowadzenia na siebie kłopotów z powodu jakichś wątpliwych informacji.";
			link.l2.go = "CaptainComission_96";
		break;	
		
		case "CaptainComission_95":
		AddQuestRecord("CaptainComission1", "12"); // поставил запись в СЖ лесник
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.SlaveCity + "Acc"));
			pchar.GenQuest.CaptainComission = "toEnemyTavern";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;
		
		case "CaptainComission_96":
			dialog.text = "Niestety, nie mogę ci tego ujawnić na razie. To może oznaczać kłopoty dla nas obojga.";
			link.l1 = "Właśnie dlatego... Chodź za mną i żadnych głupstw, proszę. Uważaj się za ponownie aresztowanego.";
			link.l1.go = "CaptainComission_97";
		break;
		
		case "CaptainComission_97":	
            AddQuestRecord("CaptainComission1", "13");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);		
			pchar.GenQuest.CaptainComission = "toTavern";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;
		
		case "CaptainComission_100":		
			dialog.text = "Dziękuję, kapitanie. Teraz wreszcie jestem bezpieczny. Nie oferuję ci pieniędzy, bo jestem pewien, że wiedza i jej umiejętne zastosowanie są warte znacznie więcej niż nietrwały metal.";
			link.l1 = "Czekam na informacje";
			link.l1.go = "CaptainComission_101";
		break;
		
		case "CaptainComission_101":
			GetSlaveSpeciality();
			dialog.text = "Rzecz w tym, że jestem naukowcem, specjalistą od "+pchar.GenQuest.CaptainComission.SlaveSpeciality+" i "+NationNamePeople(sti(pchar.GenQuest.CaptainComission.EnemyNation))+" oferował mi współpracę już od dłuższego czasu,"+"ale jestem inżynierem wojskowym i dotrzymuję przysięgi wierności. Próbowali mnie porwać, choć prawdziwe kłopoty zaczęły się, gdy piraci dowiedzieli się o mojej prawdziwej tożsamości i znaczeniu\n"+"Na końcu udało im się mnie schwytać, lecz złoto było jedyną rzeczą, której pragnęli, nigdy nie potrzebowali mojej wiedzy. Moi przyjaciele i wrogowie nie zdążyli mnie wykupić na czas i zostałem sprzedany na plantacje. Resztę znasz.";
			link.l1 = "Tak, biada mądrości, jak to mówią, rzeczywiście.";	
			link.l1.go = "CaptainComission_102";
		break;
		
		case "CaptainComission_102":
			switch(sti(pchar.GenQuest.CaptainComission.Speciality))
			{
				case 0:
					sTemp = "protecting your ship and its crew during combat.";
				break;	
				case 1:
					sTemp = "quickly reloading your cannons and firing aimed shot under conditions of dusting. ";
				break;					
				case 2:
					sTemp = "quickly managing the sails and maneuvering in combat.";
				break;					
			}
			dialog.text = "Cóż, można tak powiedzieć. Więc, jeśli zwrócisz uwagę na to, co mogę ci powiedzieć, staniesz się znacznie bardziej biegły w umiejętności "+sTemp;
			link.l1 = "Dziękuję, ta informacja jest rzeczywiście bardzo przydatna.";
			link.l1.go = "CaptainComission_103";
		break;
		
		case "CaptainComission_103":
			dialog.text = "Cóż, żegnaj i dzięki za wszystko.";
			link.l1 = "Dzięki tobie również. Żegnaj, i spróbuj nie dać się złapać następnym razem.";
			link.l1.go = "CaptainComission_104";
		break;
		
		case "CaptainComission_104":
			AddQuestRecord("CaptainComission1", "21");
			CloseQuestHeader("CaptainComission1");
			// а теперь раздача слонов !!!!!!!
			switch(sti(pchar.GenQuest.CaptainComission.Speciality))
			{
				case 0:
					if(hrand(1) == 0) 
					{
						AddCharacterSkill(pchar, SKILL_DEFENCE, 10);
					}
					else
					{
						AddCharacterSkill(pchar, SKILL_REPAIR, 10);
					}					
				break;
				case 1:
					if(hrand(1) == 0) 
					{
						AddCharacterSkill(pchar, SKILL_CANNONS, 10);
					}
					else
					{
						AddCharacterSkill(pchar, SKILL_ACCURACY, 10);
					}	
				break;
				case 2:
					AddCharacterSkill(pchar, SKILL_SAILING, 10);
				break;
			}
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "","OpenTheDoors", -1.0);
			NPChar.lifeDay = 0;
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;
		// Генератор "Captain's request"
		
		// Генератор "Operation 'Galleon'"
		case "CaptainComission_300":
			ReOpenQuestHeader("CaptainComission2");
			AddQuestRecord("CaptainComission2", "1");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); //ПРАВКА
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sCapName",  pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sCity1", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Voc")); // belamour gen
			AddQuestUserData("CaptainComission2", "sShipTypeNom", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name"))));
			AddQuestUserData("CaptainComission2", "sCity2", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City1 + "Gen"));
			AddQuestUserData("CaptainComission2", "sCity11", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));			
			SetFunctionLocationCondition("CaptainComission_GenerateQuestContinuation", GetArealByCityName(pchar.GenQuest.CaptainComission.City), false);
			SetFunctionTimerCondition("CaptainComission_TimeIsOver", 0, 0, 15, false);
			SaveCurrentQuestDateParam("GenQuest.CaptainComission");
			LAi_KillCharacter(NPChar);
			LAi_SetPlayerType(pchar); 
			pchar.GenQuest.CaptainComission = "Begin_1";
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			DialogExit();			
		break;
		
		// диалог с кэпом на палубе 
		case "CaptainComission_301":
		    if (!CheckAttribute(pchar,"GenQuest.pizdezh_uze_bil")) // проверка если разговор уже состоялся . чтобы не повторяться. лесник
			{
			pchar.quest.CaptainComission_TimeIsOver.over = "yes";
			dialog.text = RandPhraseSimple("Ahoy, jestem kapitanem "+GetFullName(NPChar)+", co cię sprowadziło na pokład mojego statku '"+pchar.GenQuest.CaptainComission.ShipTypeName+"?","Ahoy, zawsze cieszę się z gości na moim statku. Kapitan "+GetFullName(NPChar)+" do usług.");
			link.l1 = "Witaj, jestem kapitanem "+GetFullName(pchar)+", działając w imieniu jakiegoś kapitana "+pchar.GenQuest.CaptainComission.CapName+"Powiedział mi, żebym ci przekazał, że zostaniesz aresztowany w "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Voc")+"    Władze wiedzą o "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Imię")+"Generał"))+"."; // ПРАВКА + belamour gen
			link.l1.go = "CaptainComission_302";
			break;
			}
			dialog.text = "Co do diabła tu robisz? Wszystko już ustaliliśmy! Wracaj na swój statek!";
			link.l2 = "Ehh..Tak, racja!";
			link.l2.go = "exit";
			NextDiag.TempNode = "CaptainComission_301"; // чтобы не было перехода на баг  - и т.д.  лесник 
			
		break;
		
		case "CaptainComission_302":
			dialog.text = "Ach, co za szkoda! Niech pomyślę\nA gdzie jest kapitan "+pchar.GenQuest.CaptainComission.CapName+"?";
			link.l1 = "Zginął.";
			link.l1.go = "CaptainComission_303";
		break;
		
		case "CaptainComission_303":
			dialog.text = "Cholera! Sprawy się tylko pogarszają... Słuchaj, "+GetFullName(pchar)+", nie jestem gotowy stawić czoła takiemu obrotowi wydarzeń. Kapitanie "+pchar.GenQuest.CaptainComission.CapName+" i zgodziłem się spotkać o "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Voc")+"Plan był taki, by załadować trochę towaru na jego statek. Teraz kapitan nie żyje, nie mogę się pokazać w osadzie\nWygląda na to, że nie pozostaje mi nic innego, jak prosić cię o przysługę.";
			link.l1 = "Moja zgoda będzie zależała od rodzaju pomocy, której potrzebujesz.";
			link.l1.go = "CaptainComission_304";
		break;
		
		case "CaptainComission_304":
			pchar.GenQuest.CaptainComission.ShoreLocation = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			dialog.text = "Pomóż mi z ludźmi i szalupami. Muszę zabrać ładunek z "+XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation+"Gen")+" Możesz zatrzymać część ładunku zmarłego kapitana.";
			link.l1 = "Hmm... Najwidoczniej wziąłeś na siebie więcej, niż możesz udźwignąć. Potrzebuję więcej informacji.";
			link.l1.go = "CaptainComission_305";
			link.l2 = "Na nieszczęście, nie mogę sobie pozwolić na marnowanie czasu na to.";
			link.l2.go = "CaptainComission_306";
		break;
		
		case "CaptainComission_305":
			sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen"));
			dialog.text = "Dobrze, dam ci szczegóły\n"+"Podczas jednego z regularnych patroli spotkałem statek pod banderą "+NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation))+"Zignorowali moje rozkazy, by się poddać."+"Kiedy po krótkim pościgu dogoniliśmy "+sTemp+"' "+pchar.GenQuest.CaptainComission.VictimShipName+" i tak podnieśli czarną flagę. Fort był dość daleko, więc musieliśmy walczyć sami. Zniszczyli nasz bukszpryt, dlatego nie mogliśmy uniknąć abordażu.\n"+"Było blisko, ale udało nam się zabić ich wszystkich dzięki Świętej Marii i oddziałowi muszkieterów. Wyobraź sobie naszą radość, gdy dowiedzieliśmy się, że "+sTemp+"było wypełnione."+"Zdecydowaliśmy, że to jest godziwa nagroda za nasze rany i śmierć naszych towarzyszy\nByło już ciemno, wzięliśmy "+sTemp+" do najbliższej zatoki i ukryj ładunek na brzegu. Potem wysadziliśmy "+sTemp+" i zgłosiłem o zatopionym statku pirackim. Oczywiście, nie wspomniałem o ładunku.";
			link.l1 = "Najwyraźniej ktoś jednak puścił farbę...";	
			link.l1.go = "CaptainComission_307";
		break;
		
		case "CaptainComission_306":
			dialog.text = "Szkoda, kapitanie... Szkoda, że nie chcesz mi pomóc.";
			link.l1 = "To nie kwestia mojej woli, moja droga. Musisz to zrozumieć. Żegnaj.";
			link.l1.go = "CaptainComission_306End";			
		break;
		
		case "CaptainComission_306End":
			AddQuestRecord("CaptainComission2", "3");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.CapName);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "", 1.5);			
			pchar.GenQuest.CaptainComission = "close";
			SetFunctionExitFromLocationCondition("CaptainComission_ExitFromLoc", pchar.location, false);
			DialogExit();
		break;
		
		case "CaptainComission_307":
			dialog.text = "Nie sądzę, że to byli moi ludzie. Najprawdopodobniej właściciel ładunku pragnie złagodzić ból straty\nTak więc? Mogę liczyć na twoją pomoc?";
			link.l1 = "Tak, brzmi dobrze.";
			link.l1.go = "CaptainComission_308";
			link.l2 = "Nie, mój przyjacielu. Po pierwsze: nie wiem, ile ładunku trafi do mojego ładowni. A po drugie: nie ma gwarancji, że władze już go nie znalazły i nie zabrały, zostawiając przy tym zasadzkę przy skrytce.";
			link.l2.go = "CaptainComission_309";
		break;
		
		case "CaptainComission_308":
			dialog.text = "Spotkajmy się w "+XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation+"Generał")+" potem, zaraz po północy. Moja obecna pozycja wymaga dyskrecji. Musimy unikać patroli."; // belamour gen
			link.l1 = "Dobrze, poczekaj tam na mnie.";
			link.l1.go = "CaptainComission_313";
//			bQuestDisableMapEnter = true;
		break;
		
		case "CaptainComission_309":
			dialog.text = "Szkoda, ale nie zostawiasz mi wyboru. Jeden statek to za mało, by zabrać cały ładunek. Zaryzykowałem dla tego swoją karierę i własne życie. Z pewnością twoja załoga chętnie mi pomoże w zamian za przyzwoity udział.";
			link.l1 = "I co proponujesz?";
			link.l1.go = "CaptainComission_310";
		break;
		
		case "CaptainComission_310":
			dialog.text = "Wezmę twój statek i zostawię cię na "+XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation+"Generał")+"."; // belamour gen
			link.l1 = "Twoje szanse na sukces wydają mi się nikłe. Wrócę na swój statek, nawet jeśli będę musiał wyciąć całą twoją załogę.";
			link.l1.go = "CaptainComission_311";
			link.l2 = "Zdaje się, że nie mam wyboru. No cóż, poddam się przemocy...";
			link.l2.go = "CaptainComission_312";
		break;
		
		case "CaptainComission_311":
			pchar.GenQuest.CaptainComission.FightAfterDeck = true; //после резни на палубе - драка в море		
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "CaptainComission_FightInDeck", 3.5);
			DialogExit();
		break;
		
		case "CaptainComission_312":
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_toShore");
		break;
		
		case "CaptainComission_313": 		
			NextDiag.TempNode = "CaptainComission_314";
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddQuestRecord("CaptainComission2", "7");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Gen"));
			AddQuestUserData("CaptainComission2", "sShoreNameDat", XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Dat"));
			SetFunctionTimerCondition("CaptainComission_SailToShore", 0, 0, 1, false);
		    pchar.GenQuest.pizdezh_uze_bil = "true"; // лесник временная запоминалка для диалога 
			DialogExit();			
		break;
		
		case "CaptainComission_314":
			NextDiag.TempNode = "CaptainComission_314";
			dialog.text = "Kapitanie, musimy się spieszyć. Obawiam się, że patrol może nas zauważyć.";
			link.l1 = "Dobrze, pośpieszmy się.";
			link.l1.go = "exit";
		break;
		
		case "CaptainComission_315":
			dialog.text = "Kapitanie, rozkazuję spuścić wszystkie szalupy. Będziemy musieli pływać kilka razy, a obawiam się, że do zatoczki może przybyć patrol. ";
			link.l1 = "Nie martw się, wszystko powinno być w porządku. Łodzie już zbliżają się do brzegu.";
			link.l1.go = "CaptainComission_316";
		break;
		
		case "CaptainComission_316":
			dialog.text = "O, cholera. Teraz mamy towarzystwo...";
			link.l1 = "Rzeczywiście, wspomnij o jakimś głupcu, a zaraz się pojawi...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.pizdezh_uze_bil"); // удаление проверки на повтор диалога лесник
			AddDialogExitQuestFunction("CaptainComission_GenerateShorePatrol");
		break;
		
		// диалог с патрулем на берегу
		case "CaptainComission_317":
			dialog.text = "Kapitanie, szukamy zbrodniarza wojennego "+pchar.GenQuest.CaptainComission.Name+", który ukrył cenny ładunek przed władzami. Twoje dokumenty, proszę.";
			link.l1 = "Jakie dokumenty, oficerze? Zeszliśmy na ląd, aby uzupełnić zapasy świeżej wody.";
			link.l1.go = "CaptainComission_318";
		break;
		
		case "CaptainComission_318":
			dialog.snd = "Voice\COGU\COGU004"; 
			dialog.text = "A oto i on, "+pchar.GenQuest.CaptainComission.Name+" sam . Oddajcie broń i idźcie za mną, obaj!";
			link.l1 = "To był naprawdę zły moment, oficerze...";
			link.l1.go = "CaptainComission_319";
		break;
		
		case "CaptainComission_319":
			DialogExit();
			for (i = 1; i <= sti(pchar.GenQuest.CaptainComission.SoldierQty); i++)
			{
    			sTemp = "SoldierIDX" + i;
				sld = GetCharacter(sti(pchar.GenQuest.CaptainComission.(sTemp)));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "CoastalGuards");
            }
			
			LAi_group_SetHearRadius("CoastalGuards", 100.0);			
		    sld = characterFromId("CapComission_1");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);		
			LAi_group_SetRelation("CoastalGuards", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("CoastalGuards", LAI_GROUP_PLAYER, true);
            LAi_SetFightMode(Pchar, true);
				
		break;
		
		case "CaptainComission_320":
		    pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие если жив.
			pchar.GenQuest.CaptainComission.GoodsQty = makeint((sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Capacity")) - sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Capacity")) + rand(250)) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));	
			pchar.GenQuest.CaptainComission.GoodsQtyNorm = sti(pchar.GenQuest.CaptainComission.GoodsQty);
			dialog.text = "Musimy się spieszyć, zanim przybędą posiłki. Załadunek zaraz się skończy, a twój udział to "+pchar.GenQuest.CaptainComission.GoodsQty+" jednostki "+GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name+"Generał"))+".";
			link.l1 = "Doskonałe. Czas się teraz wynosić. Miło było robić z tobą interesy.";
			link.l1.go = "CaptainComission_321";
		break;
		
		case "CaptainComission_321":		
			iTmp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation),pchar.GenQuest.CaptainComission.City, true);			
			sTemp = Colonies[iTmp].id;
			pchar.GenQuest.CaptainComission.ConvoyIsland = GetArealByCityName(sTemp);
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(pchar.GenQuest.CaptainComission.ConvoyIsland);
			pchar.GenQuest.CaptainComission.ConvoyCity = sTemp;
			dialog.text = "I jeszcze jedna prośba. Władze na pewno będą nas ścigać, czy mógłbyś eskortować mój statek do "+XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore+"Gen")+", który jest na "+XI_ConvertString(GetIslandByCityName(sTemp)+"Voc")+"?"; // belamour gen
			link.l1 = "Nie, mój przyjacielu, od teraz każdy za siebie. Żegnaj...";
			link.l1.go = "CaptainComission_322";
			if (GetCompanionQuantity(pchar) < COMPANION_MAX)
			{
				link.l2 = "Oczywiście, mogę to zrobić za dobrą nagrodę.";
				link.l2.go = "CaptainComission_323";
			}				
		break;
		
		case "CaptainComission_322":
			Group_DeleteGroup("Sea_CapComission_1"); 
			sld = characterFromId("CapComission_1");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			sld.lifeDay = 0; 	
			CaptainComission_GenerateCoastalPatrol();
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
			if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// перегруз
			AddQuestRecord("CaptainComission2", "10");
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			CloseQuestHeader("CaptainComission2");	
			DeleteAttribute(pchar, "GenQuest.CaptainComission");		
			DialogExit();
		break;
		
		case "CaptainComission_323":
			sld = characterFromId("CapComission_1");
			Fantom_SetCharacterGoods(sld, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoFreeSpace(sld), 1);
			pchar.GenQuest.CaptainComission.ConvoyMoney = makeint((sti(pchar.rank)*100 + sti(NPChar.rank)*170 + hRand(30)*20) * 2.5);
			pchar.GenQuest.CaptainComission.iDay  = 15 + hRand(10);
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
			if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// перегруз
			dialog.text = "Oczywiście. Za eskortę jestem gotów zapłacić  "+pchar.GenQuest.CaptainComission.ConvoyMoney+" pesos. Ale jest jeszcze jeden warunek, nie powinno to zająć więcej niż "+pchar.GenQuest.CaptainComission.iDay+" dni. To ważne.";	
			link.l1 = "Umowa stoi. Wyruszamy natychmiast.";
			link.l1.go = "CaptainComission_324";
			NextDiag.TempNode = "CaptainComission_325";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "CaptainComission_324":
			pchar.GenQuest.CannotWait = 1; // лочим интерфейс отдыха 
			sld = characterFromId("CapComission_1");
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(sld);
			LAi_ActorSetStayMode(sld);
			CharacterIntoCompanionAndGoOut(pchar, sld, "reload", sTemp, 5, false);
			SetShipRemovable(sld, false);
			SetCharacterRemovable(sld, false);
			Group_ChangeCharacter(PLAYER_GROUP, "CapComission_1");
			AddQuestRecord("CaptainComission2", "11");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));		
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen"));
			AddQuestUserData("CaptainComission2", "sShoreType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.CaptainComission.ConvoyCity) + "Voc")); // belamour gen
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.ConvoyMoney);
			CaptainComission_GenerateCoastalPatrol();
			pchar.quest.CaptainComission_MapEnter.win_condition.l1 = "MapEnter";
			pchar.quest.CaptainComission_MapEnter.function = "CaptainComission_MapEnter"; 
			pchar.quest.CaptainComission_CapShip_Sink.win_condition.l1 = "Character_sink";
			pchar.quest.CaptainComission_CapShip_Sink.win_condition.l1.character = "CapComission_1";
			pchar.quest.CaptainComission_CapShip_Sink.function = "CaptainComission_CapShip_Sink";
			DialogExit();
		break;
		
		case "CaptainComission_325":
			NextDiag.TempNode = "CaptainComission_314";
			dialog.text = LinkRandPhrase("Kapitanie, tracimy czas. Mogą nas znaleźć w każdej chwili.","Kapitanie, ścigamy się z czasem. Nie zapomnij, że mnie szukają.","Kapitanie, nie możemy zwlekać. Mój statek jest zbyt duży, by uniknąć uwagi patrolu.");
			link.l1 = LinkRandPhrase("Tak, masz rację. Musimy się pospieszyć.","Zatem ładujcie się do łodzi bez dalszej zwłoki.","To tyle... Zbierz swoich ludzi. Wypływamy.");
			link.l1.go = "exit";
		break;
		
		case "CaptainComission_326_0":
			dialog.text = "Kapitanie, muszę porozmawiać z moimi ludźmi.";
			link.l1 = "Śmiało.";
			link.l1.go = "exit";
			InterfaceStates.Buttons.Save.enable = false; 
			AddDialogExitQuestFunction("CaptainComission_DialogInShore");
		break;
		
		case "CaptainComission_326":
			sld = characterFromId("Blaze");
			dialog.text = "Witam cię, kapitanie "+pchar.CaptainComission.Name+" Więc, czy przywiozłeś cały ładunek? A gdzie jest kapitan "+pchar.CaptainComission.CapName+"?";
			link.l1 = pchar.CaptainComission.CapName+" zmarł. Musiałem zapytać "+NPCharSexPhrase(sld,"ten dżentelmen","ta dama")+"  po pomoc. Przedstawię cię, to jest kapitan "+pchar.CaptainComission.FullName+".";
			link.l1.go = "CaptainComission_327";
		break;
		
		case "CaptainComission_327":
			sld = characterFromId("Blaze");
			dialog.text = "A "+NPCharSexPhrase(sld,"kim on jest? Czy on","kim ona jest? Czy ona")+"świadomy naszych spraw?";
			link.l1 = "Owszem, ale jest jeden problem -"+NPCharSexPhrase(sld,"jest pewien","jest pewna")+", że połowa ładunku należy do "+NPCharSexPhrase(sld,"jego","jej")+". Musimy przekonać "+NPCharSexPhrase(sld,"jego","jej")+", że to nie do końca tak.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CaptainComission_GangDialog");
		break;
		
		case "CaptainComission_328":
			dialog.text = "Mój przyjaciel "+GetFullName(pchar)+", już usłyszałeś, co potrzebujesz wiedzieć. Musimy dostać się do twojego ładowni.";
			link.l1 = "A myślisz, że moi chłopcy po prostu będą stali i patrzyli, jak jakieś obszarpańce opróżniają naszą ładownię?";
			link.l1.go = "CaptainComission_329";
		break;
		
		case "CaptainComission_329":
			pchar.GenQuest.CaptainComission.GoodsSum = 2 * sti(pchar.GenQuest.CaptainComission.GoodsQtyNorm) * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost);
			dialog.text = "Masz rację. Gotówka w kwocie, powiedzmy, "+pchar.GenQuest.CaptainComission.GoodsSum+" pesos, uwolni nas od konieczności starcia z twoją załogą. Pamiętaj, że to pokrywa połowę naszego ładunku, więc wszystko jest uczciwe. Jeśli się na to zgadzasz, nikt nie zostanie skrzywdzony.";
			link.l1 = "A co, jeśli odmówię?";
			link.l1.go = "CaptainComission_330";
		break;
		
		case "CaptainComission_330":
			dialog.text = "W takim razie przemoc jest nieunikniona. Będziesz pierwszą ofiarą i znajdziesz spokój w tej przytulnej zatoczce, a twoja załoga nie będzie w stanie przyjść ci na pomoc... Jak ci się to podoba?";
			link.l1 = "Nie zostawiasz mi wyboru. No cóż, po prostu was wszystkich zabiję.";
			link.l1.go = "CaptainComission_331";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsSum))
			{
				link.l2 = "Chyba nie mam wyboru. Dobrze, oto twoje pieniądze.";
				link.l2.go = "CaptainComission_332";
			}	
		break;
		
		case "CaptainComission_331":
			dialog.text = "Cóż, to odpowiednia decyzja dla "+GetSexPhrase("szlachetny dżentelmen","dzielna dama")+".";
			link.l1 = "Przestań filozofować! Przejdźmy do interesów!";
			link.l1.go = "CaptainComission_334";
			CaptainComission_ChangeCaptain();
		break;
		
		case "CaptainComission_332":
			dialog.text = "Mądra decyzja. Powodzenia.";
			link.l1 = "Obyś się tym zadławił...";
			link.l1.go = "CaptainComission_333";
		break;
		
		case "CaptainComission_333":
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);// лесник - разрешить снова драться после сдачи денег. но после драки кулаками не машут ..как говориться))
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsSum));
			AddQuestRecord("CaptainComission2", "17");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", UpperFirst(XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen")));
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsSum);
			CloseQuestHeader("CaptainComission2");	
			ChangeOfficersLoyality("bad_all", 1);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GangExit");
		break;

		case "CaptainComission_334":
			LAi_SetPlayerType(pchar);
			sTemp = "Gang_";
			sGroup = "GangGroup_0";			
			LAi_LocationFightDisable(&locations[FindLocation(pchar.GenQuest.CaptainComission.ConvoyShore)], false);	
			iTemp = sti(pchar.GenQuest.CaptainComission.GangNum);
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("CapComission_1");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, sGroup);
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
				LAi_SetImmortal(rChar, false);
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			LAi_group_SetCheckFunction(sGroup, "CaptainComission_GangDied");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;

		case "CaptainComission_340":
			dialog.text = "Kapitanie "+GetFullName(pchar)+", jesteśmy spóźnieni. Mam nadzieję, że rozumiesz, iż teraz nie kwalifikujesz się do nagrody.";
			link.l1 = "Jasne, że tak. Już zarobiłem niezłą monetę, dzięki tobie. Żegnaj...";
			link.l1.go = "CaptainComission_341";
		break;
		
		case "CaptainComission_341":
			Group_DeleteGroup("Sea_CapComission_1");			
			LAi_SetImmortal(NPChar, true);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			NPChar.lifeDay = 0; 						
			AddQuestRecord("CaptainComission2", "15");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")))); 
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");	
			DeleteAttribute(pchar, "GenQuest.CaptainComission");					
			DialogExit();
		break;
		
		case "CaptainComission_Canoneer":
			dialog.text = "Czy kupiłbyś trochę rumu dla starego żołnierza, który bardzo ucierpiał w bitwach o chwałę Korony?";
			link.l1 = "Karczmarzu! Nalej nam rumu!";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_Canoneer1";
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("CaptainComission_TalkCanoneer");
		break;
		
		case "CaptainComission_Canoneer1":
			dialog.text = "Dzięki ci, "+GetAddress_Form(pchar)+", bardzo miło z twojej strony, że traktujesz kalekę, który całkowicie stracił pamięć...";
			link.l1 = "Całkowicie, mówisz?";
			link.l1.go = "CaptainComission_Canoneer2";
		break;
		
		case "CaptainComission_Canoneer2":
			dialog.text = "Absolutnie, mis"+GetSexPhrase("ter","s")+" kapitanie... zupełnie. Nic nie pamiętam poza kniplem, który poleciał prosto w moją głowę. Zobacz, jaką dziurę zrobił, chyba cała moja pamięć musiała przez nią wyciec.";
			link.l1 = "Koleś, zachowaj swoje żałosne opowieści dla gospodyń domowych. Widziałem ludzi, którzy dostali prosto z kartacza, ich pamięć została całkowicie zmyta... razem z głowami... A ty tu mówisz o jakimś wymyślonym łańcuchowym strzale. Porozmawiajmy lepiej o kapitanie "+pchar.GenQuest.CaptainComission.Name+". ";
			link.l1.go = "CaptainComission_Canoneer3";
		break;
		
		case "CaptainComission_Canoneer3":
			dialog.text = "Och, cóż, wiesz. Muszę jakoś zarabiać na życie. Jeśli chodzi o kapitana "+pchar.GenQuest.CaptainComission.Name+", nie ma dla mnie zysku w gadaniu... Gdybym brał sto monet za każde pytanie o niego, miałbym teraz więcej złota niż gubernator zbiera od swoich poddanych w ciągu roku... ";
			link.l1 = "I próbowałeś sprzedać towar, schowany przez tamtego kapitana?";
			link.l1.go = "CaptainComission_Canoneer4";
		break;
		
		case "CaptainComission_Canoneer4":
			dialog.text = "Co? Kolejny tropiciel? Mówię ci jeszcze raz, nie pamiętam żadnego kapitana "+pchar.GenQuest.CaptainComission.Name+" ! Jestem kontuzjowany, a mam zaświadczenie od doktora, które to potwierdza! Czego jeszcze potrzebujesz?!";
			link.l1 = "Woah, nie podniecaj się tak. Wiesz... Było już za późno. Kapitanie "+pchar.GenQuest.CaptainComission.CapName+" poprosił mnie, bym powiedział, że "+pchar.GenQuest.CaptainComission.Name+" nie powinien pokazywać się w tej osadzie, władze wiedzą o okolicznościach zniszczenia "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Imię")+"Przyznanie"))+" ' "+pchar.GenQuest.CaptainComission.VictimShipName+", a on zostanie aresztowany.";
			link.l1.go = "CaptainComission_Canoneer5";
		break;
		
		case "CaptainComission_Canoneer5":
			dialog.text = "Uf. Powinieneś był to powiedzieć od razu, a nie kręcić się w kółko. To ja zapytałem kapitana "+pchar.GenQuest.CaptainComission.CapName+"  przechwycić nasz statek podczas powrotu. "+"Zostało przeniesione na doki zaraz po tej krwawej walce. Co ten cholerny pirat tam robił ze swoimi towarami?! Tyle chłopaków zginęło przez niego.";
			link.l1 = "Jak udało ci się przetrwać?";
			link.l1.go = "CaptainComission_Canoneer6";	
		break;
		
		case "CaptainComission_Canoneer6":
			dialog.text = "Przez pomyłkę. Szczerze mówiąc, przez moją własną cholerną pomyłkę. Nie byłem wystarczająco szybki, więc nasz szalupa nie zdążyła opuścić strefy zagrożenia. Tylko ja ucierpiałem. Zostałem trafiony przez jakiś wrak i wrzucony do wody. Nawet nie pamiętam, jak dotarłem na brzeg.";
			link.l1 = "Jak udało Ci się wykręcić od śledztwa?";
			link.l1.go = "CaptainComission_Canoneer7";
		break;
		
		case "CaptainComission_Canoneer7":
			dialog.text = "Powiedziałem im, że zostałem poturbowany podczas abordażu i nic nie wiem o żadnym ładunku. Udawałem też, że jestem słabego umysłu, wiesz, dopiero co stanąłem na nogi, tuż przed przybyciem "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Imię")+"Acc"))+"Nie mogłem się poruszać prawidłowo, moja koordynacja była do kitu.";
			link.l1 = "Ej, ale kto w ogóle wygadał się o tajemnicy ładunku?";
			link.l1.go = "CaptainComission_Canoneer8";
		break;
		
		case "CaptainComission_Canoneer8":
			dialog.text = "Piratci wysłali list do gubernatora, rzekomo w imieniu zranionego kupca. Postanowili zemścić się na kapitanie za jego upór. To była jego wina, jego głupia upartość, która wprowadziła nas w to bagno.";
			link.l1 = "Ale jak ty w ogóle spotkałeś tego pirata?";
			link.l1.go = "CaptainComission_Canoneer9";
		break;
		
		case "CaptainComission_Canoneer9":
			dialog.text = "Nie wiem. To był zwykły patrol i płynął zwykły statek pod banderą "+NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation))+". Nie mam pojęcia, dlaczego kapitan postanowił to sprawdzić, ale nie zwrócili uwagi na strzał ostrzegawczy, a gdy ich dogoniliśmy, podnieśli 'Jolly Roger'. "+"Nie mieliśmy wsparcia z fortu, więc walka nie była łatwa. Potem abordaż. Nadal nie wiem, jak udało nam się ich pokonać.\n"+"Cóż, i widzieliśmy ten cały cenny ładunek. Diabeł sam musiał nam go zesłać. Musieliśmy ukryć ładunek na brzegu i wysadzić zdobyty statek w powietrze. Była zbyt uszkodzona.";
			link.l1 = "Czy nie boisz się, że wszystkie twoje wysiłki i poświęcenia pójdą na marne, jeśli ludzie gubernatora odkryją skrytkę?";	
			link.l1.go = "CaptainComission_Canoneer10";
		break;
		
		case "CaptainComission_Canoneer10":
			iTmp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation),pchar.GenQuest.CaptainComission.City, true);			
			pchar.GenQuest.CaptainComission.CanoneerCity = Colonies[iTmp].id;			
			pchar.GenQuest.CaptainComission.Sum = 20000 + 2000 * sti(pchar.rank);
			dialog.text = "Nie znajdą tego. Wysadziłem wejście do jaskini w powietrze, w końcu byłem najlepszym ekspertem od materiałów wybuchowych w całej eskadrze. Tylko przemytnicy mogą znaleźć mój skarb, znają każdy cal tego miejsca.\n"+"Patrz, sam nie mam pojęcia, co zrobić z łupem. Nie mogę go ani sprzedać, ani samodzielnie przenieść. Poza tym, nikt nie zrobi interesu z rozbitą czaszką. Nie chcę zarabiać na śmierciach moich towarzyszy z załogi, ale mogę ci powiedzieć, gdzie jest skrytka na "+pchar.GenQuest.CaptainComission.Sum+"  pesos, jeśli zabierzesz mnie do "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.CanoneerCity)+".";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.Sum))	
			{
				link.l1 = "Zgadzam się. Oto twoje pieniądze. Teraz mów.";	
				link.l1.go = "CaptainComission_Canoneer11";
			}
			else
			{
				link.l1 = "Cholera! Dobrze, czekaj tutaj, przyniosę pieniądze.";
				link.l1.go = "CaptainComission_Canoneer12";				
			}	
			link.l2 = "To za dużo, kumplu. Poza tym, nie mam odpowiedniego statku. No cóż, powodzenia i żegnaj...";
			link.l2.go = "CaptainComission_Canoneer13";
		break;
		
		case "CaptainComission_Canoneer11":
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.Sum));
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			pchar.GenQuest.CaptainComission.GoodsQty = makeint(sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Capacity")) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));
			dialog.text = "No dobrze. Spotkaj się dziś wieczorem po północy w okolicach "+XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore+"Generał")+". I upewnij się, że masz miejsce w ładowni na "+pchar.GenQuest.CaptainComission.GoodsQty+" szt. "+GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name+"Gen"))+". Szkoda byłoby coś z tego wyrzucić..."; // belamour gen
			link.l1 = "Zajmę się tym. Do zobaczenia w zatoce...";
			link.l1.go = "CaptainComission_Canoneer14";
		break;
		
		case "CaptainComission_Canoneer12":
			AddQuestRecord("CaptainComission2", "41");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); //Gen лесник
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.Sum);
			AddQuestUserData("CaptainComission2", "sName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			SetFunctionTimerCondition("CaptainComission_CanoneerWaitMoney", 0, 0, 1, false);
			NextDiag.TempNode = "CaptainComission_Canoneer15";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;
		
		case "CaptainComission_Canoneer13":
			AddQuestRecord("CaptainComission2", "40");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // belamour gen
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			AddQuestUserData("CaptainComission2", "sName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen"))); // belamour gen
			AddQuestUserData("CaptainComission2", "sShipNameQuest", pchar.GenQuest.CaptainComission.VictimShipName);
			CloseQuestHeader("CaptainComission2");
			LAi_CharacterDisableDialog(NPChar);
			pchar.GenQuest.CaptainComission = "close";
			SetFunctionExitFromLocationCondition("CaptainComission_ExitFromLoc", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;
		
		case "CaptainComission_Canoneer14":
			AddQuestRecord("CaptainComission2", "43");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); 
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			AddQuestUserData("CaptainComission2", "sName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen")));
			AddQuestUserData("CaptainComission2", "sShipNameQuest", pchar.GenQuest.CaptainComission.VictimShipName);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Dat"));	// belamour gen
			LAi_CharacterDisableDialog(NPChar);
			SetFunctionTimerConditionParam("CaptainComission_TimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			SetFunctionTimerCondition("CaptainComission_MeetCanoneerInShoreTimer", 0, 0, 1, false);
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;
		
		case "CaptainComission_Canoneer15":
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.Sum))	
			{
				dialog.text = "A oto i ty, w końcu. Już zaczynałem się martwić. Myślałem, że po prostu oddasz mnie władzom.";
				link.l1 = "Jeszcze nie oszalałem. Oto twoje pieniądze. Teraz twoje słowo.";
				pchar.quest.CaptainComission_CanoneerWaitMoney.over = "yes";// лесник . снят таймер ожилания бабла
				link.l1.go = "CaptainComission_Canoneer11";
			}	
			else
			{
				dialog.text = "Gdzie są pieniądze?";	
				link.l1 = "Cholera! Dobra, czekaj tutaj, przyniosę to.";
				link.l1.go = "exit";
				NextDiag.TempNode = "CaptainComission_Canoneer15";
				NextDiag.CurrentNode = NextDiag.TempNode;
			}
		break;
		
		case "CaptainComission_350":
			dialog.text = "Kapitanie, najwyraźniej się spóźniliśmy. Przemytnicy znaleźli skrytkę.";
			link.l1 = "Nie zamierzam oddać swojego łupu, nawet sam diabeł mi go nie odbierze.";
			link.l1.go = "CaptainComission_351";
			link.l2 = "Rzucam to, radź sobie z konkurencją sam.";	
			link.l2.go = "CaptainComission_352";
		break;
		
		case "CaptainComission_351":
			DialogExit();
			AddDialogExitQuest("CaptainComission_GangDialog_1");
		break;
		
		case "CaptainComission_352":
			DialogExit();
			//SetFunctionExitFromLocationCondition("CaptainComission_NoGangDialog", pchar.location, false);
			 AddDialogExitQuestFunction("CaptainComission_NoGangDialog");   // лесник - исправлено . предыдцщий код не работал
		break;
		
		case "CaptainComission_360":
			dialog.text = "Kapitanie, mamy tu poważną sprawę. Radzę zabrać swoją eskadrę, zanim przybędą nasze statki.";
			link.l1 = "Panowie, wygląda na to, że próbujecie zabrać coś, co do was nie należy.";
			link.l1.go = "CaptainComission_361";
		break;
		
		case "CaptainComission_361":
			dialog.text = "O, naprawdę?! Czy masz pojęcie, z kim rozmawiasz?";
			link.l1 = "Rozmawiam z tobą, przyjacielu. Ten ładunek ma prawowitego właściciela, a ja go reprezentuję.";
			link.l1.go = "CaptainComission_362";
		break;
		
		case "CaptainComission_362":
			dialog.text = "Nie pozwolimy ci mieszać się w nasze sprawy, nawet gdybyś był Mesjaszem naszego Boga! Oczyść tor, jeśli cenisz swoje życie?";
			link.l1 = "Nie wyraziłem się jasno? Ten ładunek jest mój i nie odejdę bez niego!";
			link.l1.go = "CaptainComission_363";
		break;
		
		case "CaptainComission_363":
			dialog.text = "Do diabła z tym! Jeśli tak bardzo tego chcesz, to będziesz tu na to czekać, na wieki!";
			link.l1 = "Los zadecyduje, kto zostanie tu na zawsze.";
			link.l1.go = "CaptainComission_364";
		break;
				
		case "CaptainComission_364":
			LAi_SetPlayerType(pchar);
			sTemp = "Gang_";
			sGroup = "GangGroup_0";			
			LAi_LocationFightDisable(&locations[FindLocation(pchar.GenQuest.CaptainComission.ConvoyShore)], false);	
			iTemp = sti(pchar.GenQuest.CaptainComission.GangNum);
			chrDisableReloadToLocation = true;
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				rChar = CharacterFromID("CapComission_1");
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);						
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				rChar = CharacterFromID("CapComission_Canoneer");
				//LAi_SetWarriorType(rChar);
				LAi_SetImmortal(rChar, false);
				LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);			
			}	
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
				LAi_SetImmortal(rChar, false);
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				LAi_group_SetCheckFunction(sGroup, "CaptainComission_CheckCaptainAfterBattle");
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				LAi_group_SetCheckFunction(sGroup, "CaptainComission_CheckGangAfterBattle");
			}	
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");						
		break;
		
		case "CaptainComission_365":
			dialog.text = "Kapitanie, rozkaż swoim ludziom się pośpieszyć, patrol może przybyć w każdej chwili. Poza tym, przemytnicy najwyraźniej też czekali na swoje transporty.";
			link.l1 = "Tak, musimy się pośpieszyć... Załadujcie ładunek do ładowni i ruszajmy stąd.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_365";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "CaptainComission_366":
			dialog.text = "Dziękuję, kapitanie "+GetFullName(pchar)+"Jeśli to nie byłeś ty, przemytnicy zdobyli by nasz ładunek, a ci ludzie, którzy polegli go broniąc, zginęliby na próżno...";
			link.l1 = "Dziękuję za zaufanie mi.";
			link.l1.go = "CaptainComission_367";
		break;
		
		case "CaptainComission_367":
			dialog.text = "Mam tu jeden drobiazg, zawdzięczam mu życie. Proszę, przyjmij go, może być twoim talizmanem szczęścia. I jeszcze raz dziękuję, przyjacielu. Niech wiatr zawsze będzie po twojej stronie.";
			link.l1 = "Dzięki za prezent, nie spodziewałem się tego. I lepiej dbaj o swoje zdrowie, póki masz monety w kieszeniach.";
			link.l1.go = "CaptainComission_368";
		break;
		
		case "CaptainComission_368":
			LAi_SetActorType(NPChar);
			LAi_SetImmortal(NPChar, true);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);			
			NPChar.LifeDay = 0;
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "48");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // лесник окончание
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sCharName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_ABL));
			AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.CanoneerCity + "Gen"));
			CloseQuestHeader("CaptainComission2");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_370":
			if(pchar.GenQuest.CaptainComission == "MayorTalkBad")
			{
				pchar.quest.CaptainComission_TimeIsOver.over = "yes";
			}	
			dialog.text = "Widać, dziś jest mój dzień wizyt. Potrzebujesz mnie?";
			link.l1 = "Jeśli jesteś kapitanem "+pchar.GenQuest.CaptainComission.Name+" , wtedy tak.";
			link.l1.go = "CaptainComission_371";
		break;
		
		case "CaptainComission_371":
			dialog.text = "...były kapitan"+pchar.GenQuest.CaptainComission.Name+"... -> ";
			link.l1 = "Jestem "+GetFullName(pchar)+", a mam do ciebie kilka pytań.";
			link.l1.go = "CaptainComission_372";
		break;
		
		case "CaptainComission_372":
			dialog.text = "A dlaczego sądzisz, że miałbym na nie odpowiedzieć?";
			link.l1 = "Kapitanie "+pchar.GenQuest.CaptainComission.CapName+" poprosił mnie, bym cię ostrzegł, że okoliczności zniszczenia "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Imię")+"Acc"))+" '"+pchar.GenQuest.CaptainComission.VictimShipName+" stało się znane władzom, "+"ale nie złapałem twojego statku podczas podróży z "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City1+"Generał")+".";
			link.l1.go = "CaptainComission_373";	
		break;
		
		case "CaptainComission_373":
			dialog.text = "A gdzie jest kapitan "+pchar.GenQuest.CaptainComission.CapName+"?";
			link.l1 = "Zginął.";
			link.l1.go = "CaptainComission_374";
		break;
		
		case "CaptainComission_374":
			dialog.text = "Widzę... Więc tak to jest, co? Wiele rzeczy nabiera teraz sensu. Ktoś wygadał się, że złupiliśmy "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Imię")+"Rodzaj"))+". "+"Prędzej czy później znajdą ładunek i powieszą mnie. Kapitanie "+pchar.GenQuest.CaptainComission.CapName+" nie żyje, to znaczy, że nikt nie może mi pomóc\nZ wyjątkiem ciebie\n "+GetFullName(pchar)+", wyciągnij mnie stąd, a wynagrodzę ci to.";
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor"))
				{
					link.l1 = "Gubernator otrzymał wiadomość od właściciela ładunku. A liczby w niej są całkiem imponujące, wiesz.";
					link.l1.go = "CaptainComission_375";
				}
				else
				{
					link.l1 = "Ale z pewnością nie myślisz, że będę ci pomagał z zawiązanymi oczami?";
					link.l1.go = "CaptainComission_375";
				}
			}			
			else
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor"))
				{
					link.l1 = "Gubernator otrzymał wiadomość od właściciela ładunku. A liczby w niej są dość imponujące, wiesz.";
					link.l1.go = "CaptainComission_375";				
				}
				else
				{
					link.l1 = "Są plotki na kolonii, że masz do czynienia z przemytnikami...";
					link.l1.go = "CaptainComission_375";				
				}
			}
		break;
		
		case "CaptainComission_375":
			sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen"));
			dialog.text = "Wygląda na to, że będę musiał opowiedzieć ci całą historię.\n"+"Podczas jednego z regularnych patroli spotkałem statek pod banderą "+NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation))+"Zignorowali moje rozkazy, by się poddać. "+"Osiągnęliśmy "+sTemp+"'"+pchar.GenQuest.CaptainComission.VictimShipName+"po krótkim pościgu i podnieśli czarną flagę. Fort był dość daleko, więc musieliśmy walczyć na własną rękę. Zniszczyli nasz bukszpryt, dlatego nie mogliśmy uniknąć abordażu.\n"+"Było blisko, ale udało nam się ich wszystkich zabić dzięki Świętej Maryi i oddziałowi muszkieterów. Wyobraź sobie nasze szczęście, gdy się dowiedzieliśmy, że "+sTemp+" był wypełniony kosztownościami. "+"Zdecydowaliśmy, że to przyzwoita nagroda za nasze rany i śmierć naszych ludzi\nJuż było ciemno, udało nam się wziąć "+sTemp+" do najbliższej zatoki i ukryj ładunek na brzegu. Potem spaliliśmy "+sTemp+" i zgłosiłem zatopiony statek piracki. Oczywiście, nie wspomniałem o ładunku.";		
			link.l1 = " Myślę, że nie ma sensu mnie oszukiwać. Więc proponuję układ: pokaż mi skrytkę, a ja cię zabiorę, dokąd tylko zechcesz na archipelagu.";
			link.l1.go = "CaptainComission_376";
		break;
		
		case "CaptainComission_376":
			dialog.text = "Ha-ha-ha... Nie, kapitanie, nie opuszczę osady bez mojej części, nawet jeśli będę musiał zawisnąć na szubienicy.";
			link.l1 = "Dobrze. Dostaniesz swoją połowę.";
			link.l1.go = "CaptainComission_377";
			link.l2 = "Hmm... Wiesz, nie zamierzam ryzykować głową dla twojego dobrobytu. Żegnaj...";
			link.l2.go = "CaptainComission_378";
		break;
		
		case "CaptainComission_377":
			dialog.text = "Teraz mówisz z sensem. Jestem gotów\nNajpierw powinieneś ukryć mnie na pokładzie swojego statku. Pokażę ci zatokę, gdzie ukryty jest łup.";
			link.l1 = "W takim razie działajmy szybko i skoordynowanie. Otworzę twoją celę, a ty idź za mną. Nie zostawaj w tyle i żadnych pytań, dopóki nie opuścimy fortu.";
			link.l1.go = "CaptainComission_379";
		break;
		
		case "CaptainComission_378":
			pchar.quest.CaptainComission_GetSecretTimeIsOut.over = "yes";
			sld = CharacterFromID("CapComission_1");
			sld.LifeDay = 0;
			ChangeCharacterComplexReputation(pchar,"nobility", -5);			
			AddQuestRecord("CaptainComission2", "8");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");
			LAi_CharacterDisableDialog(npchar);// лесник - запрет диалога
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_379":
			AddQuestRecord("CaptainComission2", "21");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition.l1.character = "CapComission_1";
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition = "CaptainComission_PrisonFree_Death";
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_group_Register("CapComission_Prison");
			LAi_group_SetRelation("CapComission_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "CapComission_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "CapComission_Prison");
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_CharacterDisableDialog(npchar);
			pchar.GenQuest.CaptainComission.PrisonFree = true;
			if(pchar.GenQuest.CaptainComission == "MayorTalkGood") 
			{
				chrDisableReloadToLocation = true;	
				sld = CharacterFromId(pchar.GenQuest.CaptainComission.City + "JailOff");	
				sld.dialog.currentnode = "CapComission_PrisonFree1";
			}	
			pchar.quest.CapComission_ExitFromPrison.win_condition.l1 = "ExitFromLocation";
            pchar.quest.CapComission_ExitFromPrison.win_condition.l1.location = pchar.location;
            pchar.quest.CapComission_ExitFromPrison.win_condition = "CaptainComission_ExitFromPrison"; 
			DialogExit();
		break;		
		
		case "CaptainComission_380":
			pchar.quest.CaptainComission_GetSecretTimeIsOut.over = "yes";
			pchar.quest.CaptainComission_PrisonFree_Death.over = "yes";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.canSpeakCaptain");
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PrisonFree");
			pchar.GenQuest.CaptainComission = "CanGetGoods";
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			dialog.text = "Dzięki za ratunek. Przejdźmy do "+XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore+"Dat")+", wskażę lokalizację skrytki. Powinniśmy się pospieszyć, zanim dzikusy znajdą to miejsce.";	// belamour gen	
			link.l1 = "Czy jesteś pewien, że będziemy w stanie zabrać cały ładunek?";
			link.l1.go = "CaptainComission_381";
		break;
		
		case "CaptainComission_381":
			pchar.GenQuest.CaptainComission.GoodsQty = makeint(sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Capacity")) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));
			dialog.text = "Masz rację, upewnij się, że masz wystarczająco dużo miejsca na "+pchar.GenQuest.CaptainComission.GoodsQty+" kawałki "+GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name+"Gen"))+"Byłoby szkoda stracić taki cenny łup, oblany taką ilością krwi. Nie dadzą nam drugiej szansy.";
			link.l1 = "Zajmę się tym.";
			link.l1.go = "CaptainComission_382";
		break;
		
		case "CaptainComission_382":
			AddQuestRecord("CaptainComission2", "24");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen")); // belamour gen
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			SetFunctionLocationCondition("CaptainComission_MeetInShore", pchar.GenQuest.CaptainComission.ConvoyShore, false); 
			SetFunctionTimerConditionParam("CaptainComission_CapEscapeTimer", 0, 0, 1, MakeInt(24 - GetHour()), false);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			chrDisableReloadToLocation = false; // Откроем выход
			DeleteAttribute(pchar,"TownEscape");
			QuestOpenSeaExit();
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		
		case "CaptainComission_383":
			dialog.text = "Kapitanie, nie potrzebujemy świadków. Proszę, spróbuj przekonać tych ludzi, by opuścili zatokę.";
			link.l1 = "Dobrze, zróbmy to.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CaptainComission_GangDialogGetGoods");
		break;
		
		case "CaptainComission_384":
			dialog.text = "Kapitanie, przykro mi, ale to nie jest najlepsze miejsce na twoje ćwiczenia. Ten dok jest już zajęty.";
			link.l1 = "Panowie, nie przyszedłem tu na zwiedzanie. Mam tu interesy.";
			link.l1.go = "CaptainComission_385";
		break;
		
		case "CaptainComission_385":
			dialog.text = "Cóż, my też tu nie łapiemy meduz, zawracajcie swoje statki i wynoście się stąd do licha.";
			link.l1 = "Nie chcę tracić czasu na przekonywanie cię do odejścia. Albo zrobisz to dobrowolnie i przeżyjesz, albo zostaniesz tu na zawsze.";
			link.l1.go = "CaptainComission_386";
		break;
		
		case "CaptainComission_386":
			dialog.text = "Widzę, że masz problem ze zrozumieniem moich słów. Dobrze, jeśli to twój pogrzeb...";
			link.l1 = "To lepiej!";
			link.l1.go = "CaptainComission_364";
		break;
		
		case "CaptainComission_387":
			LAi_LocationDisableOfficersGen(pchar.GenQuest.CaptainComission.ConvoyShore, false);
			pchar.GenQuest.CaptainComission.MaxGoodsQty = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods));
			if(sti(pchar.GenQuest.CaptainComission.MaxGoodsQty) > sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.MaxGoodsQty = pchar.GenQuest.CaptainComission.GoodsQty;
			dialog.text = "Jesteśmy tutaj. Skrytka jest w niszy w tamtej skale. Wejście jest zablokowane kamieniami. W skrytce jest "+pchar.GenQuest.CaptainComission.GoodsQty+" jednostki "+GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name+"Generał"))+" Pamiętaj, że połowa należy do mnie?";
			link.l1 = "Jasne, że tak. Mamy trochę czasu, gdy moi ludzie ładują towary. Porozmawiajmy, dokąd ty i twój ładunek musicie być przewiezieni.";
			link.l1.go = "CaptainComission_388";
			if (!CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))
			{	
			link.l2 = "Bardzo dobrze. A teraz powiedz mi, czy mam powód, by się dzielić?";
			link.l2.go = "CaptainComission_389";
			}
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))
			{
				link.l3 = "Kapitana "+pchar.GenQuest.CaptainComission.Name+", muszę ci powiedzieć coś nieprzyjemnego. Pracuję dla gubernatora. I zamierzam dostarczyć mu cały ładunek, który ukryłeś. Powinieneś wrócić do więzienia i tam czekać na swój los.";
				link.l3.go = "CaptainComission_389";
				link.l2 = "Bardzo dobrze. Ale jest taka rzecz... Na początku chciałem cię wydać władzom, ale po co miałbym to robić teraz? I po co miałbym się z tobą dzielić?";
			    link.l2.go = "CaptainComission_3899"; // // лесник . отдельный диалог в случае обмана всех.
			}	
		break;
		
		case "CaptainComission_388":
		    pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие ,иначе в СЖ не то пишут.
			iTmp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation),pchar.GenQuest.CaptainComission.City, true);			
			sTemp = Colonies[iTmp].id;
			pchar.GenQuest.CaptainComission.ConvoyIsland = GetArealByCityName(sTemp);
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(pchar.GenQuest.CaptainComission.ConvoyIsland);
			pchar.GenQuest.CaptainComission.ConvoyCity = sTemp;			
			pchar.GenQuest.CaptainComission.iDay  = 20 + hRand(10);
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
			if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// перегруз
			dialog.text = "Muszę dostać się do "+XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore+"Rodzaj")+", przy "+XI_ConvertString(GetIslandByCityName(sTemp)+"Voc")+" dla "+pchar.GenQuest.CaptainComission.iDay+" dni. Moi ludzie musieli przygotować tam ładunek do sprzedaży."; // belamour gen
			link.l1 = "Dobrze. W takim razie czas wyruszać.";
			link.l1.go = "CaptainComission_391";
		break;
		case "CaptainComission_3899": // лесник . отдельный диалог в случае обмана всех.
		    DeleteAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood");
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -10);
		    pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие ,иначе в СЖ не то пишут.
			dialog.text = "Racja. Zawsze trzeba ufać umysłowi, a nie sercu. Żyj i ucz się\nChoć się tego nie spodziewałem, zawsze jestem gotów do walki. Odpowiesz za swoją zdradę.";
			link.l1 = "Cóż, jeśli masz szczęście...";
			link.l1.go = "CaptainComission_390";
			SetFunctionTimerConditionParam("CaptainComission_NaebalGubera", 0, 0, 1, MakeInt(24 - GetHour()), false);
		break;
		
		case "CaptainComission_389":
			pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие ,иначе в СЖ не то пишут.
			dialog.text = "Racja. Zawsze trzeba ufać rozumowi, a nie sercu. Żyj i ucz się\nChociaż się tego nie spodziewałem, zawsze jestem gotów do walki. Odpowiesz za swoją zdradę.";
			link.l1 = "Jestem do twoich usług...";
			link.l1.go = "CaptainComission_390";
		break;
		
		
		case "CaptainComission_390":
			LAi_SetPlayerType(pchar);
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("CapComission_1");
			LAi_SetWarriorType(rChar);
			LAi_SetImmortal(rChar, false);// лесник.  
			LAi_group_MoveCharacter(rChar, "EnemyFight");		
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors"); 			
			if(pchar.GenQuest.CaptainComission == "CapDuel")
			{
				LAi_group_SetCheckFunction("EnemyFight", "CaptainComission_CaptainDiedDuel");
			}
			else
			{
				LAi_group_SetCheckFunction("EnemyFight", "CaptainComission_CheckCaptainDied");
			}	
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");						
		break;
		
		case "CaptainComission_391":
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			GetCharacterPos(NPChar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);			
			pchar.GenQuest.CaptainComission.CapGoodsQty = sti(pchar.GenQuest.CaptainComission.GoodsQty)/2;
			if(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) > sti(pchar.GenQuest.CaptainComission.MaxGoodsQty)) pchar.GenQuest.CaptainComission.CapGoodsQty = pchar.GenQuest.CaptainComission.MaxGoodsQty;
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))AddQuestRecord("CaptainComission2", "53");// лесник. выбор записи в СЖ
			else AddQuestRecord("CaptainComission2", "26");// смотря по какому пути пошел 
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.MaxGoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sSum1", pchar.GenQuest.CaptainComission.CapGoodsQty);
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sDays", pchar.GenQuest.CaptainComission.iDay);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Dat")); // belamour gen
			AddQuestUserData("CaptainComission2", "sShoreType", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyIsland + "Gen")); // belamour gen
			OfficersReaction("bad");
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))
			{
				ChangeCharacterComplexReputation(pchar,"nobility", -5);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -10);
			}
			CaptainComission_GenerateCoastalPatrol();
			pchar.GenQuest.CaptainComission = "GetGoodsEscape";
			SetFunctionLocationCondition("CaptainComission_CapMeetInShore", pchar.GenQuest.CaptainComission.ConvoyShore, false);
			SaveCurrentQuestDateParam("GenQuest.CaptainComission.DeleiveCapShore");	
			DialogExit();
		break;
		
		case "CaptainComission_392":
			dialog.text = "Najwyraźniej się spóźniliśmy... Klienci nie czekali, a ja nie mam możliwości zorganizowania przechowywania i sprzedaży ładunku samodzielnie...";
			link.l1 = "Czy masz jakieś szczególne propozycje w tej kwestii?";
			link.l1.go = "CaptainComission_393";
		break;
		
		case "CaptainComission_393":
			pchar.GenQuest.CaptainComission.GoodsPrice = makeint(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) * 0.75 * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost));
			dialog.text = "Kapitan "+GetFullName(pchar)+", wiem, że to trochę niezręczne, ale... czy mógłbyś dać mi równowartość mojej części w gotówce? Przypuszczam, "+pchar.GenQuest.CaptainComission.GoodsPrice+" pesos mogłoby być dobrym kompromisem.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsPrice))
			{
				link.l1 = "Tak, to uczciwa cena. Nie mam nic przeciwko. Oto twoje pieniądze, żegnaj.";
				link.l1.go = "CaptainComission_394";
			}
			link.l2 = "O nie, mój przyjacielu, to nie przejdzie. Nie mogę się tobą opiekować wiecznie. Jeśli nie chcesz odebrać swojego ładunku, po prostu go zatrzymam. Bądź pewien, że znajdę sposób, by go przechować i w końcu sprzedać.";
			link.l2.go = "CaptainComission_3951";
		break;
		
		case "CaptainComission_394":
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsPrice));
			dialog.text = "Zaczekaj, kapitanie. Chcę ci podziękować za moje ocalenie. Wiesz, prawie straciłem nadzieję... Tutaj, jestem pewien, że to cacko okaże się bardzo przydatne w wielu trudnych sytuacjach... Żegnaj teraz.";
			link.l1 = "Dzięki. Nie spodziewałem się. Przyjemność robić z tobą interesy.";
			link.l1.go = "CaptainComission_395";
		break;
		
		case "CaptainComission_3951": // лесник . верное назначение диалога
			pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes";
			dialog.text = "Nie spodziewałem się tego po tobie... Najwidoczniej nie mam innego wyboru, jak tylko wyzwać cię na pojedynek.";
			link.l1 = "Do usług...";
			link.l1.go = "CaptainComission_390";
			pchar.GenQuest.CaptainComission = "CapDuel";
		break;
		
		case "CaptainComission_395":
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "32");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen")); // belamour gen
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");	
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			NPChar.lifeDay = 0; 						
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;

		case "CaptainComission_396_0":
			dialog.text = "Kapitanie, muszę porozmawiać z moimi ludźmi.";
			link.l1 = "Śmiało.";
			link.l1.go = "exit";
			InterfaceStates.Buttons.Save.enable = false; 
			AddDialogExitQuestFunction("CaptainComission_DialogInShore");
		break;
		
		case "CaptainComission_396":
			sld = characterFromId("Blaze");
			dialog.text = "Witam cię, kapitanie "+GetFullName(pchar)+" Więc, czy przywiozłeś cały ładunek? A gdzie jest kapitan "+pchar.CaptainComission.CapName+"?";
			link.l1 = pchar.CaptainComission.CapName+" umarł, a ja zostałem aresztowany na podstawie donosu. A jeśli kapitan "+pchar.CaptainComission.FullName+"nie pomógłbyś mi, nie zobaczyłbyś ani mnie, ani ładunku.";
			link.l1.go = "CaptainComission_397";
		break;
		
		case "CaptainComission_397":
			sld = characterFromId("Blaze");
			dialog.text = "I "+NPCharSexPhrase(sld,"kim on jest? Czy on","Kimże ona jest? Czyżby to ona")+"świadomy naszych spraw?";
			link.l1 = "Oczywiście. "+NPCharSexPhrase(sld,"Wydobył","Wyciągnęła")+" me from the jail and undertook to deliver half of the cargo here; the other half I promised "+ NPCharSexPhrase(sld, "him","her") +" as a compensation.";
			link.l1.go = "CaptainComission_398";
		break;
		
		case "CaptainComission_398":
			sld = characterFromId("Blaze");
			dialog.text = "Eh, kapitanie, nie ma mowy. To są twoje problemy! Proponowałem, żebyśmy zabrali statek, ale ty za bardzo dbałeś o swoją cholerną karierę. A oto i jesteś, twój ukochany gubernator trzyma cię w więzieniu."+" Twój udział był znacznie mniejszy niż połowa! Nie nadstawialiśmy głów pod kartaczami, żebyś mógł ukraść całą połowę dla siebie!";
			link.l1 = "Słuchaj, bosmanie, nie pamiętasz, że statek był całkowicie rozbity? Że prawie poszedł na dno? Nie rozumiesz, że gdybym nie dał temu człowiekowi połowy, nigdy byś nie zobaczył nawet małego kawałka ładunku?";	
			link.l1.go = "CaptainComission_399";
		break;
		
		case "CaptainComission_399":
			dialog.text = "Nie nabierzesz mnie! Skąd mogliśmy wiedzieć, że nie jesteś w zmowie? A co jeśli w ogóle nie było żadnego aresztu? Co jeśli po prostu byłeś zbyt chciwy i postanowiłeś ukraść nasze rzeczy? A może myślisz, że zapomnieliśmy, jak się posługiwać szablą?!";
			link.l1 = "Widzę, że oszalałeś. Nic nie słyszysz oprócz brzęku monet w uszach.";
			link.l1.go = "CaptainComission_400";
		break;
		
		case "CaptainComission_400":
			sld = characterFromId("Blaze");
			dialog.text = "Chłopaki! Zobaczcie, jak teraz nasz kapitan gada! Rzeczywiście, chciwość całkowicie go opanowała! Sprzedał naszą część do "+NPCharSexPhrase(sld,"łajdak","awanturnica")+"!!";
			link.l1 = "Zamknij swój plugawy pysk teraz, albo uciszę cię na dobre!";
			link.l1.go = "exit";
			AddDialogExitQuest("CaptainComission_ShoreGangDialog");
		break;
		
		case "CaptainComission_401":
			dialog.text = "Przykro mi, kapitanie, że musiałeś być świadkiem tej absurdalnej sceny, a nawet wziąć w niej udział. Trudno uwierzyć, że zaledwie miesiąc temu byliśmy zjednoczoną załogą, a każdy z nas chętnie poświęciłby swoje życie, by uratować przyjaciela.";
			link.l1 = "Muszę przyznać, nie mogę sobie tego wyobrazić, bez urazy.";
			link.l1.go = "CaptainComission_402";
		break;
		
		case "CaptainComission_402":
			dialog.text = "Niestety, nie mam możliwości samodzielnie zorganizować przechowywania i sprzedaży ładunku...";
			link.l1 = "Czy masz jakieś konkretne propozycje w tej kwestii?";
			link.l1.go = "CaptainComission_403";
		break;
		
		case "CaptainComission_403":
			pchar.GenQuest.CaptainComission.GoodsPrice = makeint(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) * 0.75 * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost));
			dialog.text = "Kapitana "+GetFullName(pchar)+", wiem, że to trochę niezręczne, ale... mógłbyś mi dać równowartość pieniężną mojej części? Przypuszczam, że "+pchar.GenQuest.CaptainComission.GoodsPrice+" pesos mogą być dobrym kompromisem.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsPrice))
			{
				pchar.quest.CaptainComission_Capitan_Cdox.over = "yes"; // на всякий случай .лесник
				pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник
				link.l1 = "Dobrze, nie mam nic przeciwko. Oto twoje pieniądze, żegnaj.";
				link.l1.go = "CaptainComission_404";
			}	
			link.l2 = "Nie, to nie zadziała. Możesz zabrać swój ładunek lub zostawić go w ładowni, ale nie dam ci ani jednego grosza.";
			link.l2.go = "CaptainComission_405";
		break;
		
		case "CaptainComission_404":
			bTemp = false;
			if(hrand(1) == 0)
			{
			    NPChar.reputation = 60 + rand(20); 
				NPChar.alignment = "good"; 
			}	
			else
			{
			    NPChar.reputation = 10 + rand(20); 
				NPChar.alignment = "bad"; 			
			}
			if (NPChar.alignment == "good" && sti(pchar.reputation.nobility) > 50) bTemp = true; 
			if (NPChar.alignment == "bad" && sti(pchar.reputation.nobility) <= 50) bTemp = true;
			
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsPrice));
			
			if(!bTemp || FindFreeRandomOfficer() < 0)
			{
				dialog.text = "Zaczekaj, kapitanie. Chcę ci podziękować za moje ocalenie. Wiesz, prawie straciłem nadzieję... Proszę, jestem pewien, że ten drobiazg okaże się bardzo przydatny w wielu trudnych sytuacjach... Żegnaj teraz.";
				link.l1 = "Dzięki. Nie spodziewałem się tego. Miło robić z tobą interesy.";
				link.l1.go = "CaptainComission_406";
			}
			else
			{
				dialog.text = "Zaczekaj... Właśnie pomyślałem... Wiesz, moja kariera jest teraz skończona, nie mam załogi i jestem wygnany w mojej ojczyźnie. Z pewnością potrzebujesz zaufanych ludzi z pewną ręką, którzy potrafią trzymać język za zębami. Proszę, przyjmij mnie do swojej załogi, obiecuję, że nie pożałujesz.";
				if(!CaptainComission_CheckAllPassengersHired())
				{
					link.l1 = "Być szczerym, czekałem na twoją zgodę od jakiegoś czasu. Pewnie. Zobaczymy się na pokładzie.";
					link.l1.go = "CaptainComission_407";
				}	
				link.l2 = "Hmm... wiesz, wydaje mi się, że jesteś zbyt bystry, by służyć pod kimkolwiek. Żegnaj...";
				link.l2.go = "CaptainComission_408";
			}
		break;
		
		case "CaptainComission_405":
			dialog.text = "Cóż, najwyraźniej dziś zdecydowanie nie jest mój szczęśliwy dzień... Dobrze, kapitanie, dobywajmy nasze ostrza i załatwmy to wszystko od razu...";
			link.l1 = "Jestem do twoich usług...";
			link.l1.go = "CaptainComission_390";
			pchar.GenQuest.CaptainComission = "CapDuel";
			pchar.GenQuest.CaptainComission.Duel = true;
		break;
		
		case "CaptainComission_406":
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "34");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);			
			NPChar.lifeDay = 0; 						
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
	
		
		case "CaptainComission_407":	
			AddQuestRecord("CaptainComission2", "36");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");		
			npchar.CaptainComission = true;
			SetCharacterRemovable(Npchar, true);
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			NPChar.Dialog.Filename = "Enc_Officer_dialog.c";
			NPChar.Dialog.CurrentNode = "hired";
            NPChar.greeting = "Gr_Officer"; 			
			NPChar.quest.OfficerPrice = sti(pchar.rank)*500;	
			NPChar.loyality = MAX_LOYALITY;
			DeleteAttribute(NPChar, "LifeDay");
			NPChar.id = "GenChar_" + NPChar.index;// лесник . смена ИД при взятии в оффы. 
			pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(NPChar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired"); 
			NPChar.quest.meeting = true; 
			DialogExit();
		break;		
		
		case "CaptainComission_408":
			AddQuestRecord("CaptainComission2", "35");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);						
			NPChar.lifeDay = 0; 						
			DeleteAttribute(pchar, "GenQuest.CaptainComission");		
			DialogExit();
		break;		
		// Генератор "Operation 'Galleon'"
		
		// Квест "meeting in the cove" -->
		// Офицер
		case "ContraMeetManQuest_Sold_1":
			dialog.text = "Nie twój interes. Teraz powiedz mi, czego tu szukasz? Nie szukasz przypadkiem człowieka, którego właśnie zatrzymano?!";
				link.l1 = "Człowiek?! Nie...";
				link.l1.go = "ContraMeetManQuest_Sold_2";
			break;
			
		case "ContraMeetManQuest_Sold_2":
			dialog.text = "Dobrze dla ciebie. Inaczej też trafiłbyś do więzienia razem z nim. Więc nie kręć się tutaj, żeglarzu. Zgiń mi z oczu!";
				link.l1 = "Tak, lepiej pójdę...";
				link.l1.go = "ContraMeetManQuest_Sold_3";
			break;
			
		case "ContraMeetManQuest_Sold_3":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteQuestCondition("ContraMeetManQuest_TimeIsLeft"); // Время больше не роляет
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "8");
			PChar.GenQuest.ContraMeetMan.ToTavernPatrolInShore = true;
			LAi_CharacterDisableDialog(NPChar);
			DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.ContraMeetMan.ShoreID)], "DisableEncounters"); // Включаем случайки
			ContraMeetManQuest_DeletePatrolFromShore(); // По выходу потрем всех из локации
			break;
			
		// Сам чел
		case "ContraMeetManQuest_1":
			dialog.text = "Świetnie! Powinniśmy teraz udać się do tawerny do tego przemytnika. Nie chciałbym tutaj się ociągać!";
				link.l1 = "Nie ma z tym problemu. Chodźmy...";
				link.l1.go = "ContraMeetManQuest_2";
			break;
			
		case "ContraMeetManQuest_2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetActorType(NPChar);
			LAi_ActorFollowEverywhere(NPChar, "", -1);
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "3");
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
			PChar.GenQuest.ContraMeetMan.ToTavernWithMan = true;
			DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.ContraMeetMan.ShoreID)], "DisableEncounters"); // Включаем случайки
			break;
		
		// Контрики в комнате таверны	
		case "ContraMeetManQuest_3":
			ContraMeetManQuest_ContersGoQut();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "4");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			CloseQuestHeader(sQuestTitle);
			ChangeContrabandRelation(PChar, 5);
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
			
		case "ContraMeetManQuest_4":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "5");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContraBeatMan();
			ChangeContrabandRelation(PChar, 5);
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
			
		case "ContraMeetManQuest_5":
			dialog.text = "He-he... Zdaje się, "+GetSexPhrase("towarzyszu","dziewucha")+",   bardzo   szybko   pójdziesz   do   piekła z nim... Hej, kumplu - wypatroszmy ich obu!";
				link.l1 = "Ty parszywa świnio! Broń się!";
				link.l1.go = "ContraMeetManQuest_6";
			break;
			
		case "ContraMeetManQuest_6":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ContraMeetManQuest_PlayerBeatContra();
			break;
			
		case "ContraMeetManQuest_7":
			dialog.text = "Dziękuję jeszcze raz, "+PChar.name+"Żegnaj...";
				link.l1 = "... ";
				link.l1.go = "ContraMeetManQuest_9";
			break;
			
		case "ContraMeetManQuest_8":
			iMoney = (rand(3)+2)*500;
			PChar.GenQuest.ContraMeetMan.Money = iMoney;
			dialog.text = "Nagroda?! Oczywiście. Proszę - weź "+FindRussianMoneyString(iMoney)+" i żegnaj...";
				link.l1 = "Żegnaj...";
				link.l1.go = "ContraMeetManQuest_10";
			break;
			
		case "ContraMeetManQuest_9":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "6");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(iMoney));
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContersGoQut();
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
			
		case "ContraMeetManQuest_10":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "7");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContersGoQut();
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
		// <-- Квест "meeting in the cove"
			
		// Квест на доставку письма контрику -->
		case "ContraDeliverQuest_Sold1":
			dialog.text = "Heh! Spodziewasz się, że uwierzymy w te bzdury?! Chłopaki, złapcie tych dwóch szubieniczników!";
			//if(80 > rand(100) || sti(PChar.skill.Fortune) > rand(100)) // Попытка отмазаться
			//{
				link.l1 = "Oficerze, popełniasz poważny błąd, próbując zatrzymać dwoje niewinnych ludzi. Wierz mi, nie znam tego człowieka i nic mnie on nie obchodzi."+" Jestem pewien, że twój komendant będzie bardzo niezadowolony z ciebie, jeśli zatrzymasz dwóch praworządnych obywateli...";
				link.l1.go = "ContraDeliverQuest_Sold2_Liberty";
			//}
			/*else // Тюрьма
			{
				link.l1 = "";
				link.l1.go = "ContraDeliverQuest_Sold2_Prison";
			}*/
			break;
			
		case "ContraDeliverQuest_Sold2_Liberty":
			dialog.text = "Hmm... Tak, być może masz rację. Komendant z pewnością będzie niezadowolony z tego. Wiesz co - zapomnijmy o tym małym incydencie.";
				link.l1 = "Dziękuję, oficerze, zaoszczędziłeś nam czas. Chciałbym cię prosić, abyś następnym razem był bardziej ostrożny, z pewnością nie chciałbyś być zdegradowany, prawda?";
				link.l1.go = "ContraDeliverQuest_Sold2_Liberty1";
			break;
			
		case "ContraDeliverQuest_Sold2_Liberty1":
			dialog.text = "Nie, w żadnym wypadku. W takim razie, proszę się rozejść. Do zobaczenia...";
				link.l1 = "To lepiej!";
				link.l1.go = "ContraDeliverQuest_Sold2_Liberty2";
			break;
			
		case "ContraDeliverQuest_Sold2_Liberty2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ContraDeliverQuest_SoldiersGoOut();
			break;
		
		case "ContraDeliverQuest_1":
			iMoney = (rand(3)+2)*500;
			if(rand(1) == 0) // Денег не даёт
			{
				dialog.text = "Doskonale! A teraz możesz się zgubić!";
					link.l1 = "Co?! A co z pieniędzmi? Mieliśmy umowę...";
					link.l1.go = "ContraDeliverQuest_NoMon";
			}
			else // Деньги или патруль
			{
				if(rand(2) == 1) // Патруль
				{
					dialog.text = "Dzięki za dostawę. Teraz możesz się zmy... czekaj, ktoś nadchodzi...";
						link.l1 = "Co?!";
						link.l1.go = "ContraDeliverQuest_Patrol";
				}
				else // Просто отдает деньги
				{
					dialog.text = "Świetnie. Dzięki za dostawę. Proszę, weź "+FindRussianMoneyString(iMoney)" I pamiętaj, że przemytnicy zawsze będą pamiętać dobrych ludzi...";
					link.l1 = "Mam nadzieję, że tak będzie. Żegnaj.";
					link.l1.go = "ContraDeliverQuest_GoWithMoney";
					PChar.GenQuest.ContraDeliver.Money = iMoney;
				}
			}
			
			ChangeContrabandRelation(PChar, 5); // Письмо доставили - повышаем отношение у контриков
			ChangeCharacterComplexReputation(pchar,"nobility", -5); // Помогли контрикам - репу понижаем
			RemoveItems(PChar, "letter_1", 1);
			BackItemDescribe("letter_1");
			DeleteAttribute(&Items[FindItem("letter_1")], "City");
			rChar = &Characters[GetCharacterIndex(Locations[FindLocation(PChar.location)].townsack + "_Smuggler")];
			SaveCurrentNpcQuestDateParam(rChar, "work_date");
			break;
			
		case "ContraDeliverQuest_Patrol":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_LocationFightDisable(LoadedLocation, true); // Чтоб не поубивали кого-нить
			ContraDeliverQuest_GeneratePatrolToRoom();
			break;
			
		case "ContraDeliverQuest_NoMon":
			dialog.text = "Słuchaj... między nami nie było żadnej umowy. Domagaj się pieniędzy od tego, kto zawarł z tobą tę umowę.";
				link.l1 = "Cóż, to z pewnością nie mój szczęśliwy dzień, co mogę powiedzieć?! Dobra, do zobaczenia...";
				link.l1.go = "ContraDeliverQuest_GoWithoutMoney";
				link.l2 = RandSwear()+"Odpowiesz za to! Przygotuj się na śmierć!";
				link.l2.go = "ContraDeliverQuest_PrepareToFight";
			break;
			
		case "ContraDeliverQuest_GoWithoutMoney": // Уходим без денег
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload         = false;
			PChar.GenQuest.ContraDeliver.Complete.WithoutMoney = true;
			sQuestTitle = PChar.GenQuest.ContraDeliver.QuestTown + "ContraDeliverQuest";
			AddQuestRecordEx(sQuestTitle, "ContraDeliverQuest", "4");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ContraDeliver.QuestTown));
			LAi_ActorGoToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", 3.0);
			break;
			
		case "ContraDeliverQuest_PrepareToFight":
			dialog.text = "Odważyłeś się mnie wyzwać, "+GetSexPhrase("szczeniak","szumowiny")+"? Cóż, z pewnością nie masz pojęcia, co dla ciebie dobre. Rozpruję cię!";
				link.l1 = "...";
				link.l1.go = "ContraDeliverQuest_Fight";
			break;
			
		case "ContraDeliverQuest_Fight": // Бой
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetImmortal(NPChar, false);
			LAi_ActorAttack(NPChar, PChar, "");
			LAi_SetFightMode(PChar, true);
			SetFunctionNPCDeathCondition("ContraDeliverQuest_ContraIsDead", NPChar.ID, false);
			break;
			
		case "ContraDeliverQuest_GoWithMoney": // Уходим с деньгами
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraDeliver.Money));
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload         = false;
			sQuestTitle = PChar.GenQuest.ContraDeliver.QuestTown + "ContraDeliverQuest";
			AddQuestRecordEx(sQuestTitle, "ContraDeliverQuest", "3");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraDeliver.Money)));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ContraDeliver"); // Квест пройден - атрибуды потрем
			LAi_ActorGoToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", 3.0);
			break;
		// <-- Квест на доставку письма контрику
			
		// Церковеый генератор. Квест № 1. Диалог кэпа, которого ищем -->
		case "ChurchGenQuest_1_DeckDialog_1":
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithCap"))
			{
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapWaitOnTavern")) // Если ждёт в таверне
				{
					dialog.text = RandPhraseSimple("Pół tysiąca ludzi! I skrzynia martwego człowieka! Hic!","Pij! Hic! A diabeł zrobił resztę - Hic! - reszty!");
						link.l1 = "Ohh... Cóż. Witaj, panie "+GetFullname(NPChar)+".";
						link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_2";
						PChar.Quest.Church_GenQuest1_Timer.over = "yes";
				}
				else // на палубе своего шипа
				{
					if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.Complete"))
					{
						dialog.text = "Dobrze, zobaczmy teraz... Trzy kawałki płótna żaglowego, deski na poszycie statku, wymiana betingów i lin na brasach...";
							link.l1 = "Cześć, panie "+GetFullName(NPChar)+". Jestem kapitanem "+PChar.name+".";
							link.l1.go = "ChurchGenQuest1_DialogShip_1";
					}
					else
					{
						dialog.text = LinkRandPhrase("Opuść mój statek natychmiast, mam wiele do zrobienia bez ciebie!","Otrzymałeś swoje księgi, czego jeszcze chcesz?!","Zrobiłem wszystko, co chciałeś, czego jeszcze ode mnie chcesz?!");
							link.l1 = "Nie ekscytuj się tak, bo dostaniesz zawału!";
							link.l1.go = "exit";
					}					
				}
			}
			else
			{
				dialog.text = RandPhraseSimple("Rum, rum! Daj mi rum... Hic!","Minęło trochę czasu... hik... odkąd ostatnio tak się upiłem...");
					link.l1 = "Tak, twój ładownia jest pełna... może czas udać się do zatoki?";
					link.l1.go = "exit";
			}			
			NextDiag.TempNode = "ChurchGenQuest_1_DeckDialog_1";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_2":
			dialog.text = RandPhraseSimple("Proszę usiąść, kapitanie-hic! Co cię truje?","Siadaj, kapitanie! Czego chciałbyś się napić? Hik...");
					link.l1 = "Dzięki, ale wolałbym miłą rozmowę z porządnym człowiekiem.";
					link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_3";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_3":
			dialog.text = "Próbujesz mnie obrazić - czkawka!..? W tej tawernie nie ma ani jednego przyzwoitego człowieka! Czkawka! Tylko bandyci i rzezimieszki! Wszyscy to wyzyskiwacze, a ten tam... pierwszy z nich! Ich herszt, murena w gardle!";
				link.l1 = "Miałem na myśli ciebie. To z tobą chcę porozmawiać. A kto jest przywódcą bandytów i dlaczego on...";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_4";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_4":
			dialog.text = "Miś"+GetSexPhrase(" ter","s")+"! Moja droga! Jakże ci było na imię, przypomnij mi? Szanuję cię! Nikt jeszcze nie nazwał starego wilka morskiego porządnym człowiekiem! Zrobiłbym dla ciebie wszystko! Oddałbym ci wszystkie moje pieniądze, do ostatniego peso!.. Och, zapomniałem. Nie mam pieniędzy. Nie zostało mi nawet żadnych groszy. Ten drań, ten reketier, właśnie zabrał mi ostatni grosik, niech diabły załadują swoje działa jego flakami w piekle!";
				link.l1 = "Panie kapitanie? Wszystko w porządku? Zdajesz sobie sprawę, że majaczysz? Jakie zwoje?";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_5";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_5":
			dialog.text = "Nie, nie! Ten stary kapitan może być pijany, ale wciąż ma swoje rozumy przy sobie. Księgi i zwoje zostały mi przekazane przez Ojca "+PChar.GenQuest.ChurchQuest_1.ToName+", zabierałem ich do "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown)+". A rano poszedłem do lokalnego kościoła i wspomniałem o tych książkach miejscowemu proboszczowi. Oczywiście, chciał je zobaczyć, wiadomo, jak to z nimi bywa, mają fioła na punkcie żywotów świętych i tych wszystkich rzeczy. Więc wysłałem chłopca z kabiny, aby przyniósł skrzynię z nimi. I podczas gdy czekałem, postanowiłem trochę pograć... i jakoś przegrałem wszystkie moje pieniądze. Wszystko! Nie miałem za co zapłacić za trunki! Więc właściciel tawerny wziął książki w zastaw, a potem dałem mu także zwoje...";
				link.l1 = "Sprzedałeś więc książki, święte księgi powierzone ci przez kapłana  "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.ToColony+"Gen")+"?";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_6";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_6":
			dialog.text = "Wiem, wiem... Będę płonął w piekle na wieki wieków. Teraz nie mogę pokazać się ani Ojcu, który powierzył mi tę misję, ani temu, kto dostarczał papiery, ani miejscowemu... Kto teraz pomodli się za moją duszę? A co jeśli mnie wykluczą? O, biada mi... Potrzebuję drinka... ";
				link.l1 = "Ej, spokojnie, nie jest tak źle. Twoje działania były kiepskie i bezbożne, a jednak jestem gotów ci pomóc. Spłacę twój dług i kupię te manuskrypty. Poza tym, skoro znam obu wymienionych księży, popłynę bezpośrednio do "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown)+"aby dostarczyć tam dokumenty. Zgoda?";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_7";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_7":
			dialog.text = "Zbawco! Aniele Boży... Oczywiście, zgadzam się! Oddałbym ci wszystko... wszystko! Gdybym tylko mógł napić się jeszcze raz...";
				link.l1 = "Chyba już masz dość... Ach, nieważne. Kupię ci jeszcze trochę rumu od karczmarza.";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_8";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_8":
			DialogExit();
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithCap");
			PChar.GenQuest.ChurchQuest_1.NeedToDialogWithBarmen = true;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "7_2");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			NextDiag.CurrentNode = "ChurchGenQuest_1_DeckDialog_1";
			break;
			
		case "ChurchGenQuest1_DialogShip_1":
			dialog.text = "...i prześcieradła! Musimy także wymienić prześcieradła!.. Och, cześć. Proszę się nie obrażać, panie"+GetSexPhrase("piwnica","s")+" cokolwiek-jak-się-nazywasz, ale teraz, jak widzisz, jestem dość zajęty, więc jeśli masz ze mną interes, proszę, załatw to szybko.";
				link.l1 = "Z tego, co wiem, ojcze "+PChar.GenQuest.ChurchQuest_1.ToName+"dał ci jakieś święte papiery w "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.ToColony+"Voc")+" Obiecałeś je dostarczyć do "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown)+" bo i tak płynąłeś w tamtym kierunku."; // belamour gen
				link.l1.go = "ChurchGenQuest1_DialogShip_2";
			break;
			
		case "ChurchGenQuest1_DialogShip_2":
			dialog.text = "Zmierzałem w tamtym kierunku, dopóki ta przeklęta burza prawie nie zniszczyła mojej starej łajby, i utknąłem tutaj na bogowie wiedzą jak długo! Ci oszuści na dokach ciągle próbują wcisnąć mi zgniłe deski wyrzucone na brzeg przez przypływ na kadłub statku, a na żagle jakieś stare worki, na których ich babcie spały, gdy były jeszcze młode.";
				link.l1 = "Panie, następnym razem z przyjemnością wysłucham twoich wspaniałych opowieści, ale teraz chciałbym dowiedzieć się więcej o losie książek i rękopisów, które otrzymałeś w "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.ToColony+"Dat")+".";
				link.l1.go = "ChurchGenQuest1_DialogShip_3";
			break;
			
		case "ChurchGenQuest1_DialogShip_3":
			dialog.text = "Nikt, słyszysz mnie? Nikt nie śmie obwiniać mnie za opóźnienie w dostarczeniu tych przeklętych papierów!";
				link.l1 = "O nie, z pewnością nie to miałem na myśli. Chciałem tylko ulżyć twemu ciężarowi. Rzecz w tym, że "+PChar.GenQuest.ChurchQuest_1.ToName+" jest bardzo zaniepokojony książkami i dokumentami, które mają być dostarczone do "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown)+"Rzeczywiście, zaraz tam popłynę.";
				link.l1.go = "ChurchGenQuest1_DialogShip_4";
			break;
			
		case "ChurchGenQuest1_DialogShip_4":
		if(rand(3) != 1)
		{
			dialog.text = "Wydaje mi się, że, mis"+GetSexPhrase("ter","s")+", że masz duchowego doradcę w każdym porcie. Chociaż to nie moja sprawa. Jeśli zależy ci na tych bzdurach, to weź swoje książki i wynocha! Niech cię diabli!";
				link.l1 = "Dziękuję, panie kapitanie. Powodzenia przy naprawach.";
				link.l1.go = "ChurchGenQuest1_DialogShip_5_1";
		}
		else // Свитки не отдает
		{
			dialog.text = "Nie martw się tym, panienko"+GetSexPhrase("ter","s")+", i podróżuj do "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown)+"  łagodnie, bo to ja podjąłem się dostarczenia tych dokumentów, i to ja zrobię to za wszelką cenę, by nikt nie krzyczał na każdym rogu, że kapitan "+NPChar.name+"nie dotrzymał słowa!";
				link.l1 = "Ale panie kapitanie, chodzi tak naprawdę o...";
				link.l1.go = "ChurchGenQuest1_DialogShip_5_2";
		}
			break;
			
		case "ChurchGenQuest1_DialogShip_5_1":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // Трем судно кэпа
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2":
			dialog.text = "Właściwie, chodzi o to, że nie mam z tobą żadnych interesów. Święty Ojciec dał mi zadanie, dostarczyć książki do "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown)+" i oddaj je miejscowemu księdzu. A ciebie tam nie widzę. Wcale! Powodzenia.";
//				link.l1 = "Dobrze, w takim razie. Jesteś bardzo odpowiedzialnym człowiekiem, chociaż to twój jedyny atut. Powodzenia, mój nieuprzejmy przyjacielu.";
//				link.l1.go = "ChurchGenQuest1_DialogShip_5_2_1"; // Сваливаем, поверили ему
				link.l2 = "Mam dość twojego bezczelnego zachowania. Twoja głupia gęba może zmusić nawet anioła do przemocy. Muszę spełnić wolę mojego świętego ojca i użyję broni, jeśli będę musiał!";
				link.l2.go = "ChurchGenQuest1_DialogShip_5_2_2"; // 
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2_1":
			DialogExit();
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "11");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete.NoManuscripts = true; // Квест выполнен без манускриптов
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // Трем судно кэпа
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2_2":
			dialog.text = "Cicho, cicho, kapitanie "+PChar.name+"! Co się z tobą dzieje? Ach, widzę, że jeśli nie przyniesiesz tych dokumentów, wszyscy ci Święci Ojcowie będą na ciebie bardzo źli, nie wspominając o naszym Ojcu w Niebie. Dobrze, weź swoje teologiczne skarby i idź z Bożym błogosławieństwem.";
				link.l1 = "Cieszę się, że nie tylko zrozumiałeś moje stanowisko, ale także zapamiętałeś moje imię. Sugeruję, byś je sobie przypomniał za każdym razem, gdy zamierzasz zrobić coś głupiego.";
				link.l1.go = "ChurchGenQuest1_DialogShip_5_2_3"; // Сваливаем, поверили ему
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2_3":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown)); // belamour gen
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // Трем судно кэпа
			break;
			
		// <-- Церковеый генератор. Квест № 1. Диалог кэпа, которого ищем
			
		case "Left_Time_Case":
			dialog.text = RandPhraseSimple("Zgub się...","Nie przeszkadzaj mi!");
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Left_Time_Case";
			break;
			
		case "Church_GenQuest_2_1":
			if(sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) == 1)
			{
				dialog.text = RandSwear()+"Nie powinieneś był tego mówić! Teraz będę musiał wysłać cię do Pana, abyś modlił się o przebaczenie moich grzechów!";
			}
			
			if(sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) == 2)
			{
				dialog.text = RandSwear()+"Nie powinieneś był tego mówić! Teraz będę musiał cię wysłać do Pana, abyś modlił się o przebaczenie naszych grzechów!";
			}
			
			if(sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) > 2)
			{
				dialog.text = RandSwear()+"Nie powinieneś był tego mówić! Teraz będę musiał cię wysłać do Pana, abyś modlił się o przebaczenie wszystkich naszych grzechów!";
			}
			
				link.l1 = "Nie bardzo, kumplu. Każdy odpowie za siebie przed Bogiem!";
				link.l1.go = "exit";
				NPChar.money = sti(PChar.GenQuest.ChurchQuest_2.MoneyCount);
				LAi_LocationFightDisable(LoadedLocation, false);
				AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			break;
			
		case "Church_GenQuest_2_ShoreBandit_1":
			dialog.text = "Hej, czemu te przekleństwa? A jeśli mam z tobą interes.";
				link.l1 = "To dopiero wieści! Wiesz, mam krótkie rozmowy z takimi jak ty!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_2";
				LAi_LocationFightDisable(LoadedLocation, false);
			break;
			
		case "Church_GenQuest_2_ShoreBandit_2":
			dialog.text = "Cóż, nie zamierzam też z tobą długo gadać. Ale może zainteresowałbyś się kupnem kilku błyskotek po dobrej cenie?";
				link.l1 = "Czy wyglądam jak cholerny paser?!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_3";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_3":
			if(rand(1) == 0)
			{
				dialog.text = "Spokojnie, spokojnie, nie ma wśród nas złodziei! Ta waza została nam przekazana za uczciwą pracę! Tylko spójrz... czyste złoto, ozdobione perłami. Ale rzecz w tym, że jej nie potrzebujemy. Więc po prostu chcemy ją sprzedać i podzielić się pieniędzmi.";
					link.l1 = "Pozwól, że przyjrzę się bliżej... O mój Boże! To jest kielich komunijny!!! Więc to wy jesteście tymi bluźniercami, którzy splądrowali kościół w "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_2.QuestTown+"Gen")+"? ! A oto i ty!";
					link.l1.go = "Church_GenQuest_2_ShoreBandit_4";
					break;
			}
		
			dialog.text = "Cicho, panie"+GetSexPhrase("ter","s")+" hipokryto! Wiesz, trochę nam brakuje pieniędzy, więc postanowiliśmy coś sprzedać. Spójrz na ten wazon... czyste złoto, zdobione perłami. Specjalna cena dla ciebie, powiedzmy, tysiąc monet.";
				link.l1 = "Pozwól mi się przyjrzeć... O mój Boże! To jest kielich komunijny!!! Więc to wy jesteście tymi bluźniercami, którzy splądrowali kościół "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_2.QuestTown+"Generał")+"?! O, tu jesteś!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_1";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_4":
			dialog.text = "Trzymaj konie, mis"+GetSexPhrase("ter","s")+"!.. Cholera, mówiłem temu durniowi, żeby nie robił zamieszania, aż nadejdzie właściwy czas...";
				link.l1 = "Co ty bredzisz? Dobra, wybieraj: albo dobrowolnie oddasz mi swoje skradzione łupy, albo wołam straż.";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_5";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_5":
			dialog.text = "Słuchaj, "+GetSexPhrase("dobry człowiek","młoda dama")+", nie potrzebujemy żadnych kłótni, więc rozwiążmy tę sprawę pokojowo. Musicie nam wierzyć, nie splądrowaliśmy tego kościoła, ani nie mamy żadnych pieniędzy. Tak, otrzymaliśmy kilka pesos i ten złoty drobiazg za udawanie rabunku. A ten złoty kielich był jedyną rzeczą, która nam została po opłaceniu przemytników...";
				link.l1 = "Więc próbujesz powiedzieć, że...";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_6";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_6":
			dialog.text = "Ten przeklęty ksiądz nas wynajął, to właśnie mówię! Ale po co musiał cię wysłać do nas?.. No cóż, teraz jesteśmy kwita. Weź ten wazon i pokaż go temu hipokrycie, zobaczysz, jak będzie się miotał jak kalmar na mieliźnie!";
				link.l1 = "Oddaj mi puchar i zmiataj, zanim zmienię zdanie.";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_7";
				link.l2 = "Pięknie gadasz, ale nie tak łatwo mnie oszukać. Jeśli chcesz mnie przekonać, najpierw przekonaj mój miecz.";
				link.l2.go = "Church_GenQuest_2_ShoreBandit_8";
				// Тут давать чашу, если будет
				ChurchGenQuest2_GiveCup();
				PChar.GenQuest.ChurchQuest_2.Complete.PriestIsThief = true;
			break;
			
		case "Church_GenQuest_2_ShoreBandit_7":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_Type_Actor_Reset(rChar);
				LAi_CharacterDisableDialog(rChar);
				rChar.LifeDay = 0;
				LAi_ActorRunToLocation(rChar, "reload", "reload1_back", "none", "", "", "", -1);
			}
			
			// Разрешим генерацию энкаунтеров, откроем выходы
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "10_1");
			AddQuestUserData(sQuestTitle, "sName", PChar.GenQuest.ChurchQuest_2.QuestTown.PriestName);
			break;
			
		case "Church_GenQuest_2_ShoreBandit_8":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "10_2");
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_1":
			if(PChar.GenQuest.ChurchQuest_2.BanditsCount == 1)
			{
				dialog.text = RandSwear()+"Nie mówiłem tym łachudrom: trzymajcie swe chciwe łapy i nie zabierajcie niczego oprócz pieniędzy od księdza!";
			}
			else
			{
				dialog.text = RandSwear()+"Nie mówiłem tym nienasyconym draniom: trzymajcie swoje łapska z dala i nie bierzcie nic oprócz pieniędzy od księdza!";
			}
			
					link.l1 = "Co ty bredzisz? Dobra, wybieraj: albo dobrowolnie oddasz mi swoje skradzione łupy, albo wzywam straże.";
					link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2":
			dialog.text = "Podejmuję inną decyzję, zamknij swój gadaninę i oddaj mi swoją sakiewkę, a oszczędzę ci życie.";
				link.l1 = "Pomogę ci teraz umówić się na audiencję z naszym Panem!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_1";
				link.l2 = "Dobrze, dam ci trochę pieniędzy, ale tylko z własnej woli, abyś ty i twoi przyjaciele mogli prowadzić uczciwe życie i nie musieli poniżać się kradzieżą.";
				link.l2.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_2";
				link.l3 = "Ehh... Dobrze, odłóżmy nasze nieporozumienia na bok i wróćmy do początku naszej rozmowy. Więc ile chciałeś za tę rzecz?";
				link.l3.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_1":
			// Не забыть чашу!
			ChurchGenQuest2_GiveCup();
			PChar.GenQuest.ChurchQuest_2.Complete.With_All = true;
			NPChar.money = ((rand(3) + 6) * 1000);
			PChar.GenQuest.ChurchQuest_2.MoneyCount = NPChar.money;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_1");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_2":
			AddMoneyToCharacter(PChar, -sti(PChar.money)/2); // Забираем половину денег
			PChar.GenQuest.ChurchQuest_2.Complete.Without_All = true; // Полностью проигрышный вариант. Остаемся ни с чем
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_SetCitizenType(rChar);
				rChar.LifeDay = 0;
				rChar.Dialog.Currentnode = "First time";
			}
			
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "11_2");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3":
			iMoney = makeint(makeint(Pchar.money)/20)*10;
			dialog.text = "Nie potrzebuję też żadnych problemów, "+GetAddress_Form(pchar)+", ale teraz cena wzrosła. Za ten cenny kielich będę wymagał wszystkiego, co masz przy sobie.";
			if(iMoney >= makeint(Pchar.rank)*300)
			{
				link.l1 = "Chciwy łajdaku! Mam tylko "+FindRussianMoneyString(iMoney)+" ze mną. Weź to i zmykaj!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_1";
			}
			else
			{
				link.l1 = "Niewłaściwy wybór, chciwy szczurze. Nie zrobisz sobie dobrze moim kosztem!"+GetSexPhrase(" Jestem wolny jak wiatr - dziś tu, jutro tam, dziś biedny - jutro będę bogaty..."," ")+"";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_2";
			}
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_GiveCup();	// Даем чашу
			AddMoneyToCharacter(PChar, -(makeint(makeint(Pchar.money)/20)*10));
			PChar.GenQuest.ChurchQuest_2.Complete.Only_With_Cup = true;
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_SetCitizenType(rChar);
				rChar.LifeDay = 0;
				rChar.Dialog.Currentnode = "Left_Time_Case"; // Диалог не забыть поменять.
			}
			
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_3");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore");
			break;

		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_2":
			dialog.text = "Czy nie próbujesz powiedzieć, że akurat dzisiaj "+GetSexPhrase("jesteś biedny","nie masz pieniędzy")+"?!";
				link.l1 = "Dokładnie, mój chciwy przyjacielu, ku twemu wielkiemu rozczarowaniu. A teraz muszę się pożegnać, mam wiele do zrobienia.";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_3";	
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_3":
			dialog.text = "Stój! Sprawdzimy to, a jeśli kłamałeś, włożę twój kłamliwy język do kolonii mrówek!";
				link.l1 = "Po tym, co powiedziałeś, jesteś skończony!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_4";
			break;
			
		// Можно этот кэйс - Church_GenQuest_2_ShoreBandit_Real_Band_2_1
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_4":
				// ГГ как-бы может обыскать трупики и забрать все барахло...
				PChar.GenQuest.ChurchQuest_2.Complete.With_All = true;
				NPChar.money = ((rand(3) + 6) * 1000);
				PChar.GenQuest.ChurchQuest_2.MoneyCount = NPChar.money;
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
				sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
				AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_4");
				AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("As a real gentleman, I am honest","I am honest"));
			break;
			
		///////////////////////////////////////////////////////////////////////////////////////////////////
		// ГЕНЕР "PIRATES ON AN UNINHABITED ISLAND"
		///////////////////////////////////////////////////////////////////////////////////////////////////
		
		case "PiratesOnUninhabited_1":
			dialog.text = "Och, nie ma o czym decydować. Możemy wszystko sami zadecydować. Ale zabierzemy twój statek i wyniesiemy się stąd.";
			link.l1 = "Jest jeden warunek, najpierw musisz odebrać mi mój miecz...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_2":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				LAi_SetImmortal(CharacterFromID("PirateOnUninhabited_" + i), false);
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_3":
			PChar.GenQuest.PiratesOnUninhabited.MainPirateName = GetRandName(NAMETYPE_NICK, NAME_GEN);
			PChar.GenQuest.PiratesOnUninhabited.BadPirateName = GetRandName(NAMETYPE_ORIG, NAME_NOM);
			
				i = PiratesOnUninhabited_GenerateShipType();
				PChar.GenQuest.PiratesOnUninhabited.StartShipType = i;
			
			if(hrand(1) == 0)
			{
				PChar.GenQuest.PiratesOnUninhabited.Shipwrecked = true;
				
				dialog.text = "Witaj, kapitanie! Najwyraźniej sama Opatrzność cię przysłała, byś nas ocalił "+PChar.GenQuest.PiratesOnUninhabited.MainPirateName+" i jego chłopcy. Jesteśmy tutaj w pilnej potrzebie."+"Nasz "+GetStrSmallRegister(XI_ConvertString(ShipsTypes[i].Name))+" rozbił się w burzy na lokalnych rafach, a fale wyrzuciły na brzeg ocalałych członków załogi."+"Dla "+(5+hRand(7))+" tygodni przyglądaliśmy się horyzontowi, mając nadzieję ujrzeć żagiel statku, który przybędzie nas uratować.";
				link.l1 = RandPhraseSimple(RandPhraseSimple("Tak, to nie do pozazdroszczenia los. Ale taki jest los życia marynarzy, każdy mógłby skończyć na twoim miejscu.","Widzę... Bóg trzyma każde życie, tylko że jest zbyt zajęty, by pamiętać o wszystkich."),RandPhraseSimple("Rzeczywiście. Człowiek planuje, ale to Bóg dysponuje.","Tak, to z pewnością był pech."));
				link.l1.go = "PiratesOnUninhabited_4";
			}
			else
			{
				dialog.text = "To było bardzo poważne! Ten łajdak "+PChar.GenQuest.PiratesOnUninhabited.BadPirateName+" nie mógł wymyślić innej kary niż odejście "+ChangeNameCase(NAMETYPE_NICK,PChar.GenQuest.PiratesOnUninhabited.MainPirateName,NAME_ACC)+" na bezludnej wyspie, jak parszywy kundel! "+"Miał nadzieję, że słońce i pragnienie wysuszą nas jak suszonego makrela na stoisku rybaka! Ale się mylił, bo Opatrzność sama była po naszej stronie, gdyż zesłała cię tutaj, by nas uratować...";
				link.l1 = RandPhraseSimple("Nie tak szybko, przyjacielu. O ile mogę powiedzieć, jesteście ludźmi wolnego zawodu, i trafiliście tu nie przez przypadek.","Już mówisz o zbawieniu? Jak rozumiem, jesteś tutaj z powodu jakichś wyjątkowych osiągnięć.");
				link.l1.go = "PiratesOnUninhabited_41";
			}
		break;
		
		case "PiratesOnUninhabited_4":
			PChar.GenQuest.PiratesOnUninhabited.PiratesCount = 5 + hrand(5);
			
			dialog.text = RandPhraseSimple("Kapitanie, bądź tak dobry i pomóż  "+PiratesOnUninhabited_GetStringNum(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))+" nędzarze. Jesteś naszą jedyną nadzieją, poza naszym najłaskawszym Panem.","Kapitanie, czy masz wolne schowki na swoim statku dla "+PiratesOnUninhabited_GetStringNum(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))+"biedni ludzie?");
			
			if(GetFreeCrewQuantity(PChar) >= sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) && GetPassengersQuantity(PChar) < PASSENGERS_MAX)
			{
				link.l1 = "Ohh... a dokąd chciałbyś, żebym cię zabrał?";
				link.l1.go = "PiratesOnUninhabited_5";
			}
			
			link.l2 = RandPhraseSimple(RandPhraseSimple("Naprawdę mi przykro, ale nie ma ani jednej wolnej koi, nie mówiąc już o kajutach. Marynarze śpią na pokładzie, nie mogą nawet porządnie odpocząć po wachcie...","Bardzo bym nie chciał cię rozczarować, ale statek jest przeładowany, a ludzie muszą spać w złej pogodzie. Jeśli wybuchnie epidemia, stracę połowę załogi."),RandPhraseSimple("Naprawdę mi przykro, ale na moim statku nie ma absolutnie żadnego wolnego miejsca dla załogi. Nie mogę zabrać na pokład więcej pasażerów.","Muszę cię rozczarować, ale mój statek jest przeładowany załogą. Obawiam się epidemii..."));
			link.l2.go = "PiratesOnUninhabited_21";
			
			if(stf(PChar.reputation.nobility) <= REPUTATION_NEUTRAL)
			{
				link.l3 = "Jesteś doświadczonym żeglarzem i powinieneś wiedzieć, że obecność kogoś, kto przeżył katastrofę morską, to bardzo zły znak. Moi marynarze po prostu wyrzucą was wszystkich za burtę.";
				link.l3.go = "PiratesOnUninhabited_7";
			}
		break;
		
		case "PiratesOnUninhabited_5":
			dialog.text = "Hmm... Wiesz, z kilku powodów chcielibyśmy trzymać się jak najdalej od władz... Proszę, dostarcz nas do jakiejkolwiek zatoki na zamieszkanej wyspie lub na Głównej, a wtedy będziemy mogli zadbać o siebie.";
			link.l1 = "Zatem mam wystarczająco wolnych szafek i hamaki. Załaduj się do łodzi.";
			link.l1.go = "PiratesOnUninhabited_10";
			link.l2 = "Hmm... nieszczęście... Przed nami bitwy, i nie wiem, gdzie będziesz bardziej bezpieczny, na pokładzie mojego statku czy w tej przytulnej zatoce.";
			link.l2.go = "PiratesOnUninhabited_6";
		break;
		
		case "PiratesOnUninhabited_6":
			dialog.text = "O, kapitanie! To są czasy, kiedy człowiek nie czuje się bezpiecznie nawet w łóżku z własną żoną, ha-ha, a co dopiero na morzu... Spójrz na tych oprychów, każdy z nich gotów jest walczyć gołymi rękami przeciwko armatom. Wcale nie pragną bezpieczeństwa i wygody, widać to na ich twarzach!";
			link.l1 = "Na ich twarzach widzę jedynie chęć wbicia noża w plecy swojemu głupiemu dobroczyńcy.";
			link.l1.go = "PiratesOnUninhabited_7";
			link.l2 = "Hmm... To, właściwie, jest dobry pomysł. Powiedz mi przyjacielu, czy twoi zbóje są gotowi służyć w mojej załodze?";
			link.l2.go = "PiratesOnUninhabited_8";
		break;
		
		case "PiratesOnUninhabited_7":
			dialog.text = "Jaka szkoda, kapitanie... Widzę, że nie możemy tego rozwiązać po przyjacielsku. Chyba będę musiał przypomnieć ci kodeks morski. I miej na uwadze, że gdy dojdzie do abordażu, nie mamy sobie równych...";
			link.l1 = "Cóż, teraz mogę w końcu zobaczyć cię takim, jaki jesteś naprawdę...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
			ChangeCharacterComplexReputation(pchar,"nobility", -3.0);
		break;
		
		// Берем их в команду
		case "PiratesOnUninhabited_8":
			dialog.text = "Ależ oczywiście! Oni z radością staną się częścią twojej abordażowej załogi! Nikt ich nie pokona w walce, może tylko sam Davy Jones! Ha-ha-ha!";
			link.l1 = "Dobrze, więc. Załadujcie się do łodzi...";
			link.l1.go = "PiratesOnUninhabited_9";
		break;
		
		case "PiratesOnUninhabited_9":
			bTemp = CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.Shipwrecked");
			
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.LifeDay = 0;
				
				if(bTemp)
				{
					rChar.Dialog.currentnode = "PiratesOnUninhabited_11_Again";
				}
				else
				{
					rChar.Dialog.currentnode = "PiratesOnUninhabited_43_again";
				}
			}
			
			AddCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount));
			
			Log_Info("Your crew was increased by " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " men.");
			OfficersReaction("bad");
			
			//PChar.Quest.PiratesOnUninhabited_LocExit.over = "yes"; // Снимаем прерывание на выход из локации
			
			//DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_10":
			dialog.text = "Dziękuję, kapitanie! Załadunek nie powinien zająć zbyt dużo czasu. Boże, jakże się modliliśmy, by ten moment nadszedł!";
			link.l1 = "Bardzo dobrze, zatem.";
			link.l1.go = "PiratesOnUninhabited_11";
		break;
		
		// Берем их в пассажирами - держать курс на населенный остров
		case "PiratesOnUninhabited_11":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.Dialog.currentnode = "PiratesOnUninhabited_11_Again";
			}
			
			Log_Info("Your crew was increased by " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " men.");
			
			ChangeCharacterComplexReputation(pchar,"nobility", 3.0);
			
			AddCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
			OfficersReaction("good");
			PChar.Quest.PiratesOnUninhabited_LocExit.over = "yes"; // Снимаем прерывание на выход из локации
			
			AddPassenger(PChar, NPChar, false); // Главного в пассажиры
			SetCharacterRemovable(NPChar, false);
			
			sTemp = XI_ConvertString(PChar.location + "Gen"); // belamour gen
			
			sTitle = "PiratesOnUninhabited" + PChar.location;
			ReOpenQuestHeader(sTitle);
			
			if(!CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.TreasureMap"))
			{
				if(CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.Shipwrecked"))
				{
					AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "1");
					AddQuestUserData(sTitle, "shipTypeName", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name + "Gen"))); // belamour gen
					// --> belamour gen: нужно разделить, иначе получается с потерпевшего крушение бригантины 
					if(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_SCHOONER_W")
					{
						AddQuestUserData(sTitle, "sText", "wrecked pirate");
					}
					else
					{
						AddQuestUserData(sTitle, "sText", "wrecked pirate");
					}
					// <-- belamour gen
				}
				else
				{
					AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "11");
					AddQuestUserData(sTitle, "pirateName", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_ABL));
				}
			}
			else
			{
				AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "5");
				AddQuestUserData(sTitle, "shipTypeName", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name + "Gen"))); // belamour gen
				// --> belamour gen: нужно разделить, иначе получается с потерпевшего крушение бригантины 
				if(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_SCHOONER_W")
				{
					AddQuestUserData(sTitle, "sText", "wrecked pirate");
				}
				else
				{
					AddQuestUserData(sTitle, "sText", "wrecked pirate");
				}
				// <-- belamour gen
			}
			
			AddQuestUserDataForTitle(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "count", PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " sailors"); // belamour gen
			
			PChar.GenQuest.PiratesOnUninhabited.StartShore = PChar.location;
			
			PChar.Quest.PiratesOnUninhabited_LocExitGood.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PiratesOnUninhabited_LocExitGood.win_condition.l1.location = PChar.location;
			PChar.Quest.PiratesOnUninhabited_LocExitGood.function = "PiratesOnUninhabited_LocationExit_Good";
			
			PChar.Quest.PiratesOnUninhabited_OnShore.win_condition.l1 = "Location_Type";
			PChar.Quest.PiratesOnUninhabited_OnShore.win_condition.l1.location_type = "seashore";
			PChar.Quest.PiratesOnUninhabited_OnShore.again = true;
			PChar.Quest.PiratesOnUninhabited_OnShore.function = "PiratesOnUninhabited_OnShore";
			
			PChar.Quest.PiratesOnUninhabited_OnMayak.win_condition.l1 = "Location_Type";
			PChar.Quest.PiratesOnUninhabited_OnMayak.win_condition.l1.location_type = "mayak";
			PChar.Quest.PiratesOnUninhabited_OnMayak.again = true;
			PChar.Quest.PiratesOnUninhabited_OnMayak.function = "PiratesOnUninhabited_OnShore";
			
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_11_Again":
			dialog.text = LinkRandPhrase("Na co się ociągasz, kapitanie? Rozkaż podnieść kotwicę.","Przykro nam, kapitanie, ale musimy się przygotować do wypłynięcia w morze.","Mamy takie szczęście, że zdecydowałeś się tu przybyć!");
			link.l1 = "Pośpiesz się. Statek nie będzie czekał na nikogo.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_11_Again";
		break;
		
		// Базар с главарем уже в другой бухте на обитаемом острове
		case "PiratesOnUninhabited_12":
			if(hrand(1) == 0)
			{
				// Успешное завершение квеста - даст награду
				dialog.text = "Dziękuję, kapitanie. Rzeczywiście, dobrze zrobiliśmy, wierząc w nasze szczęście... Proszę, przyjmij ten klejnot, znalazłem go w tej nieszczęsnej zatoce. Mam nadzieję, że przyniesie ci szczęście.";
				link.l1 = "Nie spodziewałem się takiego prezentu.";
				link.l1.go = "PiratesOnUninhabited_13";
			}
			else
			{
				// Требуют денег
				dialog.text = "Kapitanie, proszę, nie myśl, że jesteśmy zbyt bezczelni, ale naprawdę brakuje nam pieniędzy. Wiesz, straciliśmy wszystko, co mieliśmy. Czy mógłbyś nam pożyczyć kilka garści pesos? Na pewno ci oddamy... gdy tylko nadarzy się okazja...";
				link.l1 = "Wow! Rzeczywiście, bezczelność nie zna granic. Cóż, jedyną rzeczą, jaką mógłbym teraz dla ciebie zrobić po wszystkim, co już zrobiłem, byłoby nie zgłoszenie cię władzom.";
				link.l1.go = "PiratesOnUninhabited_15";
				link.l2 = "Nie mów... A ile chcesz?";
				link.l2.go = "PiratesOnUninhabited_17";
			}
			
			RemovePassenger(PChar, NPChar);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
		break;
		
		case "PiratesOnUninhabited_13":
			AddItems(PChar, "jewelry4", 1);
			
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
				
				rChar.Dialog.currentnode = "PiratesOnUninhabited_14";
			}
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "2");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.location + "Gen"))); // belamour gen
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_14":
			dialog.text = LinkRandPhrase("Dziękuję, kapitanie.","Kapitanie, jesteśmy ci tak wdzięczni.","Będziemy się za ciebie modlić, kapitanie "+PChar.name+"!");
			link.l1 = "Powodzenia. Żegnaj...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_14";
		break;
		
		case "PiratesOnUninhabited_15":
			dialog.text = "Heh, kapitanie... Wiesz, dogadywaliśmy się całkiem nieźle... Naprawdę szkoda by było cię zabić...";
			link.l1 = "Możesz spróbować!";
			link.l1.go = "PiratesOnUninhabited_16";
			AddDialogExitQuest("MainHeroFightModeOn");
			ChangeCharacterComplexReputation(pchar,"nobility", 2.0);
		break;
		
		case "PiratesOnUninhabited_16":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "3");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.location + "Gen"))); // belamour gen
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_17":
			iMoney = sti(PChar.rank) * 500;
			PChar.GenQuest.PiratesOnUninhabited.Money = iMoney * sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount);
			
			dialog.text = "No cóż, powiedz, "+iMoney+" peso dla każdego z nas byłoby w sam raz... Oczywiście, jeśli nie uważasz, że to odszkodowanie za cały nasz ból i cierpienie jest zbyt małe, he-he...";
			link.l1 = RandPhraseSimple("Wręcz przeciwnie, jestem pewien, że to stanowczo za dużo... Pętla na szyi dla każdego z was byłaby najlepsza.","Powieszę cię jak małpy na palmach za takie pieniądze osobiście!");
			link.l1.go = "PiratesOnUninhabited_18";
			
			if(sti(PChar.money) >= iMoney * sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))
			{
				link.l2 = "Dobrze, weź to. Mam nadzieję, że niczego więcej ci nie jestem winien?";
				link.l2.go = "PiratesOnUninhabited_19";
			}
		break;
		
		case "PiratesOnUninhabited_18":
			dialog.text = "Co za hojność! Szczerze mówiąc, myślałem, że już miałeś okazję zobaczyć, że zawsze dostajemy to, czego pragniemy. I tym razem również nie zamierzamy się wycofać...";
			link.l1 = "Spróbuj, jeśli śmiesz!";
			link.l1.go = "PiratesOnUninhabited_16";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_19":
			dialog.text = "O nie, kapitanie, co mówisz?! Z pewnością zapalimy świecę w twoim imieniu, jeśli kiedykolwiek wejdziemy do kościoła... hah!";
			link.l1 = "Mam nadzieję, że tak...";
			link.l1.go = "PiratesOnUninhabited_20";
			
			iMoney = sti(PChar.GenQuest.PiratesOnUninhabited.Money);
			
			AddMoneyToCharacter(PChar, -iMoney);
			AddMoneyToCharacter(NPChar, iMoney);
		break;
		
		case "PiratesOnUninhabited_20":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_CharacterDisableDialog(rChar);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			ChangeCharacterComplexReputation(pchar,"nobility", 2.0);
			OfficersReaction("good");
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "4");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.location + "Acc")));
			CloseQuestHeader(sTitle);
			
			NPChar.SaveItemsForDead = true; // сохранять на трупе вещи
			NPChar.DontClearDead = true;  // не убирать труп через 200с
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_21":
			if(GetFreeCrewQuantity(PChar) >= sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))
			{
				// Игрок врет - свободное место есть
				dialog.text = "O nie, kapitanie, co ty mówisz?! Na pewno zapalimy świecę w twoje imię, jeśli kiedykolwiek wejdziemy do kościoła... hah!";
				link.l1 = "Mam nadzieję, że tak...";
				link.l1.go = "PiratesOnUninhabited_23";
			}
			else
			{
				dialog.text = "Heh, kapitanie, wiesz, to nie jest wielki problem. Ja i moi chłopcy chętnie zwolnią tuzin hamaków na twoim statku od tych, którzy je obecnie zajmują...";
				link.l1 = "Hmm... to brzmi jak groźba...";
				link.l1.go = "PiratesOnUninhabited_22";
			}
		break;
		
		case "PiratesOnUninhabited_22":
			dialog.text = "Cóż, właściwie to jest groźba. Potrzebuję twojego statku i wyjdę z tego miejsca, z twoją zgodą lub bez niej!";
			link.l1 = "Cóż, teraz mogę wreszcie zobaczyć cię takim, jakim naprawdę jesteś...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_23":
			dialog.text = "Rozumiem cię, kapitanie. Doskonale cię rozumiem... Kto chciałby niańczyć biednych piratów, którzy sami prosili się o stryczek?.. Ale... co jeśli zaproponuję ci wymianę? Dostarczysz nas do jakiejkolwiek zatoczki na zamieszkanej wyspie lub na lądzie, a ja dam ci za to mapę skarbu. Umowa stoi?";
			link.l1 = "Hmm... A jak możesz zagwarantować, że ta mapa to nie falsyfikat?";
			link.l1.go = "PiratesOnUninhabited_25";
			link.l2 = "Ha, jestem pewien, że twoja mapa jest warta tyle, co papier, na którym została narysowana...";
			link.l2.go = "PiratesOnUninhabited_24";
		break;
		
		case "PiratesOnUninhabited_24":
			dialog.text = "Cóż... Zostawiasz nas bez wyboru... Jednakże, zamierzamy wydostać się z tego miejsca, z twoją zgodą lub bez niej!";
			link.l1 = "Teraz wreszcie mogę zobaczyć, kim naprawdę jesteś...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_25":
			dialog.text = "A jak możesz zagwarantować, że nie wydasz nas władzom w najbliższym porcie? Oboje gramy, nie widząc kart przeciwnika...";
			link.l1 = "Dobrze, umowa stoi.";
			link.l1.go = "PiratesOnUninhabited_11";
			PChar.GenQuest.PiratesOnUninhabited.TreasureMap = true;
		break;
		
		// Базар с главарем уже в другой бухте на обитаемом острове. Вариант, когда нам обещали карту сокровищ
		case "PiratesOnUninhabited_26":
			// PChar.GenQuest.PiratesOnUninhabited.MainPirateName - имя в родительном падеже
			
			dialog.text = "Dziękuję, kapitanie "+PChar.name+" . Wypełniłeś"+GetSexPhrase("","I'm sorry, but there seems to be no text provided for translation. Could you please provide the text you would like translated?")+" twoja obietnica, czas nadszedł "+ChangeNameCase(NAMETYPE_NICK,PChar.GenQuest.PiratesOnUninhabited.MainPirateName,NAME_DAT)+" by spełnić moje. Nie mam przy sobie mapy, ale powiem ci, gdzie jest skarb. Idź do zatoki...";
			link.l1 = "O, więc teraz tak to przedstawiasz! Widzę, że zamierzałeś mnie oszukać od samego początku...";
			link.l1.go = "PiratesOnUninhabited_27";
			link.l2 = "Od razu wiedziałem, że nie można ci ufać...";
			link.l2.go = "PiratesOnUninhabited_30";
			link.l3 = "Tego się spodziewać, gdy ufasz piratowi. Jakim rodzajem ludzi jesteście? Nic nie jest dla was święte!";
			link.l3.go = "PiratesOnUninhabited_33";
			
			RemovePassenger(PChar, NPChar);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
		break;
		
		case "PiratesOnUninhabited_27":
			dialog.text = "Nie rób zamieszania... Nie jestem święty, ale dotrzymuję słowa!";
			link.l1 = "I oczekujesz, że znowu ci uwierzę? Żeby jutro cały archipelag miał ze mnie ubaw?";
			link.l1.go = "PiratesOnUninhabited_28";
		break;
		
		case "PiratesOnUninhabited_28":
			dialog.text = "Hmm... Najwidoczniej nie będzie pokojowego rozwiązania. Ale, Bóg wie, nie chciałem tego...";
			link.l1 = "Dobywaj szabli, albo zetrę cię na miazgę jak szczura, którym jesteś!";
			link.l1.go = "PiratesOnUninhabited_29";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_29":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "6");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_30":
			sTitle = PiratesOnUninhabited_GenerateTreasureShore(&sTemp);
			PChar.GenQuest.PiratesOnUninhabited.TreasureShore = sTitle;
			PChar.GenQuest.PiratesOnUninhabited.TreasureBox = sTemp;
			
			dialog.text = "I co innego mogłem zrobić? Zostać w tej śmierdzącej kałuży z moimi chłopakami i zgnić na śmierć? Lepiej mnie wysłuchaj..."+XI_ConvertString(sTitle+"Gen")+" kapitan "+ChangeNameCase(NAMETYPE_ORIG,PChar.GenQuest.PiratesOnUninhabited.BadPirateName,NAME_GEN)+" jest skrytka, gdzie trzyma swoje łupy. Ale bądź ostrożny"+GetSexPhrase(""," ")+", często tam bywa. Znalezienie skrytki nie będzie trudne, jeśli zachowasz przytomność umysłu..."; // belamour gen
			link.l1 = "I znowu oczekujesz, że ci uwierzę? Żeby jutro całe archipelag się ze mnie śmiało?";
			link.l1.go = "PiratesOnUninhabited_28";
			link.l2 = "Dobrze. Ale jeśli jeszcze raz mnie wystawisz, to cię znajdę.";
			link.l2.go = "PiratesOnUninhabited_31";
		break;
		
		case "PiratesOnUninhabited_31":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
				rChar.Dialog.currentnode = "PiratesOnUninhabited_32";
			}
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "7");
			AddQuestUserData(sTitle, "capName", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_NOM));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.TreasureShore + "Gen"))); // belamour gen
			
			// Таймер для клада. По прошествии 10 дней в кладе будут всякие бакланы и т.д.
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1 = "Timer";
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1.date.day = GetAddingDataDay(0, 0, 10);
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1.date.year = GetAddingDataYear(0, 0, 10);
			PChar.Quest.PiratesOnUninhabited_TreasureLose.function = "PiratesOnUninhabited_TreasureLose"; // belamour gen
			
			PChar.Quest.PiratesOnUninhabited_InTreasureLoc.win_condition.l1 = "Location";
			PChar.Quest.PiratesOnUninhabited_InTreasureLoc.win_condition.l1.Location = PChar.GenQuest.PiratesOnUninhabited.TreasureShore;
			PChar.Quest.PiratesOnUninhabited_InTreasureLoc.function = "PiratesOnUninhabited_InTreasureLoc";
			
			DialogExit();
			
			// Курс в бухту, которую назвал пират. У нас сроку 10 дней, котом клад пропадёт
		break;
		
		case "PiratesOnUninhabited_32":
			sTemp = ChangeNameCase(NAMETYPE_NICK, PChar.GenQuest.PiratesOnUninhabited.MainPirateName, NAME_ACC);
			
			dialog.text = LinkRandPhrase("Słuchaj "+sTemp+"On mówi z sensem.","Nie gniewaj się na "+sTemp+", po prostu nie miał innego wyboru.","Dziękuję, kapitanie.");
			link.l1 = "Powodzenia...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_32";
		break;
		
		case "PiratesOnUninhabited_33":
			sTitle = PiratesOnUninhabited_GenerateTreasureShore(&sTemp);
			PChar.GenQuest.PiratesOnUninhabited.TreasureShore = sTitle;
			PChar.GenQuest.PiratesOnUninhabited.TreasureBox = sTemp;
			
			dialog.text = "A co innego mogłem zrobić? Zostać w tej śmierdzącej kałuży z moimi chłopakami i gnić na śmierć? Lepiej mnie wysłuchaj..."+XI_ConvertString(sTitle+"Gen")+" kapitan "+ChangeNameCase(NAMETYPE_ORIG,PChar.GenQuest.PiratesOnUninhabited.BadPirateName,NAME_GEN)+"  jest skrytka, gdzie trzyma swoje łupy. Ale bądź ostrożny, często tam zagląda. Znalezienie skrytki nie będzie trudne, jeśli zachowasz przytomność umysłu..."; // belamour gen
			link.l1 = "I spodziewasz się, że znów ci uwierzę? By jutro cały archipelag ze mnie drwił?";
			link.l1.go = "PiratesOnUninhabited_28";
		break;
		
		// Пираты в бухте с сокровищем
		case "PiratesOnUninhabited_34":
			dialog.text = "Kimżeś ty,"+GetSexPhrase(" kamracie","dziewczę")+"? A co cię sprowadziło do tego opuszczonego miejsca?";
			link.l1 = "Zatrzymałem się, by uzupełnić zapasy świeżej wody.";
			link.l1.go = "PiratesOnUninhabited_35";
			link.l2 = "Jestem tutaj w imieniu "+ChangeNameCase(NAMETYPE_NICK,PChar.GenQuest.PiratesOnUninhabited.MainPirateName,NAME_GEN)+".";
			link.l2.go = "PiratesOnUninhabited_38";
			NextDiag.TempNode = "PiratesOnUninhabited_34";
		break;
		
		case "PiratesOnUninhabited_35":
			dialog.text = "Wybrałeś marne miejsce na to... Dobrze, nie spiesz się.";
			link.l1 = "A-ha...";
			link.l1.go = "exit";
			link.l2 = "A kimże jesteś, by mówić mi, co mam robić?";
			link.l2.go = "PiratesOnUninhabited_36";
		break;
		
		case "PiratesOnUninhabited_36":
			dialog.text = "Ja wszystkim mówię, co robić. A ci, którzy uważają się za zbyt mądrych, będą wisieć na palmie.";
			link.l1 = "Obetnę ci język, psie.";
			link.l1.go = "PiratesOnUninhabited_37";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_37":
			DialogExit();
			LAi_Group_SetRelation("PiratesOnUninhabited_ShoreGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		break;
		
		case "PiratesOnUninhabited_38":
			dialog.text = "A dlaczego nie przyszedł osobiście?";
			link.l1 = "Nie chciał, został w "+LowerFirst(XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore+"Generał"))+" i czekając na mnie."; // belamour gen
			link.l1.go = "PiratesOnUninhabited_39";
		break;
		
		case "PiratesOnUninhabited_39":
			dialog.text = "Ten stary łajdak! Znów próbuje nas oszukać, prawda? Na to nie pozwolimy. Powiedz mu, że może zebrać pieniądze tylko razem z nami!";
			link.l1 = "Powiedział mi, żeby nie wracać bez pieniędzy i nie zabierać nikogo na pokład...";
			link.l1.go = "PiratesOnUninhabited_40";
		break;
		
		case "PiratesOnUninhabited_40":
			dialog.text = "Cóż, jeśli mu tak ufasz, możesz tu zostać. Ale zabieramy twój statek, twoje pieniądze i ruszamy do "+LowerFirst(XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore+"Generał"))+". Umieramy z ciekawości, by spojrzeć w twarz "+PChar.GenQuest.PiratesOnUninhabited.MainPirateName+"."; // belamour gen
			link.l1 = "Jeśli tak za nim tęsknisz, możesz tam popłynąć... albo umrzeć tutaj.";
			link.l1.go = "PiratesOnUninhabited_37";
			AddDialogExitQuest("MainHeroFightModeOn");
			PChar.GenQuest.PiratesOnUninhabited.UseMainPiratename = true;
		break;
		
		// Ветка из PiratesOnUninhabited_3
		case "PiratesOnUninhabited_41":
			iBanditsCount = 5 + hrand(5);
			iMoney = GetFreeCrewQuantity(PChar);
			
			PChar.GenQuest.PiratesOnUninhabited.PiratesCount = iBanditsCount;
			
			dialog.text = "Jesteś przebiegłą osobą. Ale pozwól mi zapewnić cię, że nasz konflikt z kapitanem "+ChangeNameCase(NAMETYPE_ORIG,PChar.GenQuest.PiratesOnUninhabited.BadPirateName,NAME_ABL)+"jest czysto ideologicznej natury. Ostrzegłem go, że jego brudne operacje zostaną kiedyś ukarane, a teraz ja i mój "+iBanditsCount+" kumple cierpią z powodu naszej miłości do Boga i sprawiedliwości.";
			link.l1 = "Jak to... Założę się, że to wy byliście prawdziwymi podżegaczami buntu i dostaliście, na co zasłużyliście.";
			link.l1.go = "PiratesOnUninhabited_42";
			
			if(iMoney >= iBanditsCount - 1 && GetPassengersQuantity(PChar) < PASSENGERS_MAX)
			{
				link.l2 = "Oczywiście... Miło by jednak było usłyszeć opinię kapitana "+ChangeNameCase(NAMETYPE_ORIG,PChar.GenQuest.PiratesOnUninhabited.BadPirateName,NAME_GEN)+" sam co do waszych nieporozumień.";
				link.l2.go = "PiratesOnUninhabited_44";
			}
		break;
		
		case "PiratesOnUninhabited_42":
			dialog.text = "Kapitanie, dlaczego obrażasz uczciwych ludzi swoim brakiem zaufania? Spójrz tylko na ich twarze... czy naprawdę myślisz, że to buntownicy? Są tak pokorni, jak tylko ludzie mogą być... Ale w walce o słuszną sprawę pod dobrą komendą są niezrównani! Mogę osobiście ręczyć za każdego z nich.";
			link.l1 = "Dobrze, ale co mam teraz z tobą zrobić?";
			link.l1.go = "PiratesOnUninhabited_43";
		break;
		
		case "PiratesOnUninhabited_43":
			iBanditsCount = sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount);
			iMoney = GetFreeCrewQuantity(PChar);
			
			dialog.text = "Cokolwiek sobie zażyczysz. To zależy od ciebie, zabierz nas do osady lub przyjmij do swojej załogi, wydajesz się być dobrym kapitanem.";
			
			if(iMoney >= iBanditsCount)
			{
				link.l1 = "Dobrze, przyjmę cię do mojej załogi. Ale żadnych wygłupów! Na moim statku panuje surowa dyscyplina!";
				link.l1.go = "PiratesOnUninhabited_9"; // Берем в команду
			}
			
			link.l2 = "Nie zabieram cię nigdzie. Już mam wystarczająco dużo zbirów w mojej załodze.";
			link.l2.go = "PiratesOnUninhabited_24"; // Рубилово и конец квеста
			
			if(iMoney >= iBanditsCount - 1 && GetPassengersQuantity(PChar) < PASSENGERS_MAX)
			{
				link.l3 = "Dobrze, wsiadaj do łodzi, zabiorę cię gdzieś.";
				link.l3.go = "PiratesOnUninhabited_11"; // В пассажиры и на остров
			}
		break;
		
		case "PiratesOnUninhabited_43_again":
			dialog.text = LinkRandPhrase("Przysięgam, kapitanie, nie pożałujesz tego.","Dokonałeś właściwego wyboru, kapitanie.","Kapitanie, zapewniam cię, że miałeś tyle szczęścia, co my sami!");
			link.l1 = RandPhraseSimple("Mam nadzieję.","Pospiesz się. Statek nie będzie czekał na nikogo.");
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_43_again";
		break;
		
		case "PiratesOnUninhabited_44":
			sTitle = GenerateRandomNameToShip(PIRATE);
			PChar.GenQuest.PiratesOnUninhabited.StartShipName = sTitle;
			
			dialog.text = "To można łatwo załatwić. On żegluje na "+GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].Name+"Voc"))+" '"+sTitle+" i handluje niewolnikami... Zróbmy tak: Jeśli go znajdziemy, ty dostaniesz ładunek, a my statek. Aha, i możesz go zapytać, czy wie o "+ChangeNameCase(NAMETYPE_NICK,PChar.GenQuest.PiratesOnUninhabited.MainPirateName,NAME_ACC)+" Mam nadzieję, że nie zrobi w spodnie, gdy usłyszy to imię, bo to mój statek..."; // belamour gen
			link.l1 = "Dobrze, masz umowę.";
			link.l1.go = "PiratesOnUninhabited_45";
		break;
		
		case "PiratesOnUninhabited_45":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.Dialog.currentnode = "PiratesOnUninhabited_11_Again";
				rChar.location = "none"; // Убираем из локации при выходе   исправлено с NPChar на rChar - лесник
				rChar.location.locator = ""; // лесник  - так же исправлено .  тогда бага не будет.
			}
			
			Log_Info("Your crew was increased by " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " men.");
			
			ChangeCharacterComplexReputation(pchar,"nobility", 3.0);
			
			AddCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1)
			AddPassenger(PChar, NPChar, false); // Главного в пассажиры
			SetCharacterRemovable(NPChar, false);
			//NPChar.FaceId = 101; // лесник потом подобрать аву бандиту.   
			
			PChar.Quest.PiratesOnUninhabited_LocExit.over = "yes"; // Снимаем прерывание на выход из локации
			
			sTemp = XI_ConvertString(PChar.location + "Gen"); // belamour gen
			
			sTitle = "PiratesOnUninhabited" + PChar.location;
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "13");
			AddQuestUserDataForTitle(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "shoreName", sTemp);
			// --> belamour окончание по количеству персон
			if(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) >= 5)
			{
				AddQuestUserData(sTitle, "count", PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " sailors");
			}
			else
			{
				AddQuestUserData(sTitle, "count", PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " sailor");
			}
			// <-- belamour
			AddQuestUserData(sTitle, "badCapName", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_ABL));
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name + "Voc")) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'"); // belamour gen
			
			PChar.GenQuest.PiratesOnUninhabited.StartShore = PChar.location;
			
			PiratesOnUninhabited_SetCapToMap(); // Ставим корабль на карту
			
			DialogExit();
		break;
		
		// Диалог с кэпом в каюте
		case "PiratesOnUninhabited_46":
			dialog.text = "Czego do diabła ode mnie chcesz?";
			link.l1 = "Przyszedłem się przywitać w imieniu "+ChangeNameCase(NAMETYPE_NICK,PChar.GenQuest.PiratesOnUninhabited.MainPirateName,NAME_GEN)+"Domyślam się, że go znasz?";
			link.l1.go = "PiratesOnUninhabited_47";
			
			PChar.Quest.PiratesOnUninhabited_ShipSink.over = "yes";
			PChar.GenQuest.PiratesOnUninhabited.ClearShip = true;
			Map_ReleaseQuestEncounter("PiratesOnUninhabited_BadPirate"); // Убираем с глобалки
		break;
		
		case "PiratesOnUninhabited_47":
			dialog.text = "Szkoda, że ​​nie udusiłem tego łotra wcześniej. Cóż, chyba nadszedł czas zapłacić za moją dobroć...";
			link.l1 = "Rzeczywiście... I czas właśnie się skończył...";
			link.l1.go = "PiratesOnUninhabited_48";
		break;
		
		case "PiratesOnUninhabited_48":
			LAi_CharacterDisableDialog(NPChar);
			LAi_Group_Attack(NPChar, Pchar);
			
			LAi_SetCurHPMax(NPChar);
			QuestAboardCabinDialogFree(); // важный метод
			
			LAi_Group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_Group_SetCheckFunction(LAI_GROUP_BRDENEMY, "PiratesOnUninhabited_CapDeath");
			
			AddDialogExitQuest("MainHeroFightModeOn");
			
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_49":
			dialog.text = "Świetna robota, kapitanie! Wszystko zgodnie z umową, prawda? My dostajemy statek, a ty ładunek?";
			link.l1 = "Pewnie. Weź statek i dobrze go wykorzystaj.";
			link.l1.go = "PiratesOnUninhabited_50";
		break;
		
		case "PiratesOnUninhabited_50":
			NPChar.LifeDay = 0;
			NPChar.location = "none"; // Убираем из каюты
			NPChar.location.locator = "";
			
			RemovePassenger(PChar, NPChar);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "14");
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			ChangeAttributesFromCharacter(CharacterFromID("PiratesOnUninhabited_BadPirate"), NPChar, true);
			DialogExit();
			
		break;
		
		// На палубе, когда корабль с нашим пиратом отпустили
		case "PiratesOnUninhabited_50_Deck1":
			dialog.text = "Witam cię, kapitanie "+PChar.name+".";
			link.l1 = "Jak ci się podoba twój statek?";
			link.l1.go = "PiratesOnUninhabited_50_Deck2";
		break;
		
		case "PiratesOnUninhabited_50_Deck2":
			dialog.text = "Heh... skrzypi i trzeszczy, tak jak ja. Myślę, że oboje nie mamy już wiele czasu, by pływać po morzach...";
			link.l1 = "Powodzenia, zatem...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_50_Deck1";
		break;
		
		// В бухте, вариант, когда корабль, который нужно было захватить, утопили
		case "PiratesOnUninhabited_51":
			dialog.text = "Dlaczego zatopiłeś mój statek?! Czy w ogóle pamiętasz naszą umowę?";
			link.l1 = "Co, nie chciałem, żeby to on zatopił mnie zamiast tego. Nie widzisz, że ledwo uszedłem z życiem?";
			link.l1.go = "PiratesOnUninhabited_52";
		break;
		
		case "PiratesOnUninhabited_52":
			if(hrand(1) == 1)
			{
				dialog.text = "Kto tak walczy? Straciłeś taki statek! Do diabła! Co tu w ogóle robi taki dzieciak jak ty?";
				link.l1 = "Wytnę ci język, psie.";
				link.l1.go = "PiratesOnUninhabited_53";
			}
			else
			{
				iMoney = sti(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].Price);
				iMoney = MakeInt((iMoney / 1.2 + hrand(iMoney - (iMoney / 1.2))) * 1.2);
				dialog.text = "Kto tak walczy? Straciłeś taki statek! Czy masz pojęcie, ile mnie to kosztowało?"+FindRussianMoneyString(iMoney)+"! Teraz jesteś mi winien...";
				link.l1 = "Czy to nie będzie dla ciebie za dużo? Nie zapominaj, że już raz ci przysługę oddałem.";
				link.l1.go = "PiratesOnUninhabited_54";
				
				if(sti(PChar.money) >= iMoney)
				{
					link.l2 = "Niech cię diabli z tym przeklętym statkiem! Weź swoje pieniądze i nie pojawiaj się więcej na me oczy!";
					link.l2.go = "PiratesOnUninhabited_55";
				}
			}
		break;
		
		case "PiratesOnUninhabited_53":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "15");
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			AddDialogExitQuest("MainHeroFightModeOn");
			
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_54":
			dialog.text = "A cóż mi teraz z tej przysługi?! Jeśli kapitan "+ChangeNameCase(NAMETYPE_ORIG,PChar.GenQuest.PiratesOnUninhabited.BadPirateName,NAME_NOM)+" leży teraz na dnie morza z moim statkiem! Teraz ani nie dostanę swojej części, ani swojego statku z powrotem! Co za los, umrzeć w rynsztoku, jak włóczęga!!!";
			link.l1 = "Ale dlaczego? Mogę zorganizować dla ciebie wspaniały pogrzeb. Tutaj, jeśli ci to odpowiada...";
			link.l1.go = "PiratesOnUninhabited_53";
		break;
		
		case "PiratesOnUninhabited_55":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_SetImmortal(rChar, false);
				LAi_CharacterDisableDialog(rChar);
				rChar.LifeDay = 0;
			}
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "16");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
		break;
		
		// КОНЕЦ
		
		// Warship, 15.05.11. Генер "Justice for sale".
		case "JusticeOnSale_1":
			dialog.text = "Myślałem, że moglibyśmy... dojść do porozumienia, może? Jeśli wyświadczysz nam przysługę, odpłacimy się, he-he.";
			link.l1 = "Przysługa? A o co chodzi i co oferujesz w zamian?";
			link.l1.go = "JusticeOnSale_3";
		break;
		
		case "JusticeOnSale_2":
			LAi_Group_SetRelation("JusticeOnSaleGroup_" + LoadedLocation.index, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("JusticeOnSaleGroup_" + LoadedLocation.index, LAI_GROUP_PLAYER, true);
			
			DialogExit();
			LAi_SetFightMode(PChar, true);
		break;
		
		case "JusticeOnSale_3":
			dialog.text = "Nasz kapitan "+PChar.GenQuest.JusticeOnSale.SmugglerName+" został złapany przez miejscowy patrol  "+XI_ConvertString("Colony"+PChar.GenQuest.JusticeOnSale.CityId+"Gen")+"Trzymają go w więzieniu, ale nie mają wystarczających dowodów, by go powiesić. Nie możemy go sami wyciągnąć\n"+"Jesteś szanowanym człowiekiem. Ludzie cię znają. Może mógłbyś negocjować, wykupić go albo po prostu go wykupić? Zaufaj nam, opuścimy wyspę, jak tylko odzyskamy naszego człowieka, więc twoja reputacja nie ucierpi!"; // belamour gen
			link.l1 = "Powiedzmy, że mogę ci pomóc. Ale co z moją zapłatą?";
			link.l1.go = "JusticeOnSale_4";
			link.l2 = "Idź do diabła, piekielny pomiocie! Nie chcę mieć z tobą nic wspólnego!";
			link.l2.go = "JusticeOnSale_5";
		break;
		
		case "JusticeOnSale_4":
			dialog.text = "Chcesz kilka indiańskich błyskotek i talizmanów? Są raczej rzadkie... A może wolisz gotówkę na stół? Kilka tysięcy pesos, powiadam?";
			link.l1 = "Idź do diabła, piekielne nasienie! Nie będę miał z tobą nic wspólnego!";
			link.l1.go = "JusticeOnSale_5";
			link.l2 = "Interesują mnie indiańskie błyskotki. Chyba się zgodzę.";
			link.l2.go = "JusticeOnSale_6";
			link.l3 = "Pieniądze to najlepszy przyjaciel żeglarza. Pieniądze nie śmierdzą, jak wszyscy wiemy. Zgadzam się.";
			link.l3.go = "JusticeOnSale_7";
		break;
		
		case "JusticeOnSale_5":
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_Jungle_" + i);
				LAi_CharacterDisableDialog(rChar);
			}
			DialogExit();
		break;
		
		case "JusticeOnSale_6":
			PChar.GenQuest.JusticeOnSale.ShipName = GenerateRandomNameToShip(PIRATE);
			PChar.GenQuest.JusticeOnSale.ShipType = PiratesOnUninhabited_GenerateShipType();
			PChar.GenQuest.JusticeOnSale.RewardType = 0; // Подрякушки.
			dialog.text = "Dziękujemy, kapitanie. Zrekompensujemy ci sumę kaucji oprócz twojej nagrody. Myślę, że powinieneś porozmawiać z komendantem o naszym kapitanie. Być może uda ci się go przekonać. Jak tylko go wyciągniesz, przyjdź do "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Dat")+", tam nasz statek zarzucił kotwicę - "+LowerFirst(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.JusticeOnSale.ShipType)].name))+" '"+PChar.GenQuest.JusticeOnSale.ShipName+". Będziemy czekać na ciebie na brzegu."; // belamour gen
			link.l1 = "... -> ";
			link.l1.go = "JusticeOnSale_8";
		break;
		
		case "JusticeOnSale_7":
			PChar.GenQuest.JusticeOnSale.ShipName = GenerateRandomNameToShip(PIRATE);
			PChar.GenQuest.JusticeOnSale.ShipType = PiratesOnUninhabited_GenerateShipType();
			PChar.GenQuest.JusticeOnSale.RewardType = 1; // Монеты.
			
			dialog.text = "Dziękuję, kapitanie. Wynagrodzimy ci sumę kaucji oprócz twojej nagrody. Myślę, że powinieneś porozmawiać z komendantem o naszym kapitanie. Być może uda ci się go przekonać. Kiedy go wyciągniesz, przyjdź do "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Tam")+", tam nasz statek zarzucił kotwicę - "+LowerFirst(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.JusticeOnSale.ShipType)].name))+" '"+PChar.GenQuest.JusticeOnSale.ShipName+"  Będziemy czekać na ciebie na brzegu."; // belamour gen
			link.l1 = "... ";
			link.l1.go = "JusticeOnSale_8";
		break;
		
		case "JusticeOnSale_8":
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_Jungle_" + i);
				LAi_CharacterDisableDialog(rChar);
			}
			ReOpenQuestHeader("JusticeOnSale");
			AddQuestRecord("JusticeOnSale", "1");
			AddQuestUserData("JusticeOnSale", "cityName", XI_ConvertString("Colony" + PChar.GenQuest.JusticeOnSale.CityId + "Gen")); // belamour gen
			PChar.GenQuest.JusticeOnSale.MayorWait = true;
			PChar.GenQuest.JusticeOnSale.PrisonWait = true;
			
			DialogExit();
		break;
		
		case "JusticeOnSale_9":
			if(hrand(1) == 0)
			{
				if(sti(PChar.GenQuest.JusticeOnSale.RewardType) == 0)
				{
					// Награда побрякушками.
					dialog.text = "Jesteśmy na miejscu, kapitanie! Świetnie ci poszło z tymi brzuchatymi biurokratami! Oto twoja nagroda. Chłopcy, przynieście świecidełka!";
				}
				else
				{
					// Награда золотом.
					dialog.text = "Jesteśmy tutaj, kapitanie! Świetnie udało ci się oszukać tych brzuchatych biurokratów! Oto twoja nagroda. Chłopcy, przynieście skrzynię!";
				}
				
				link.l1 = "Daj mi moją część i wynocha!";
				link.l1.go = "JusticeOnSale_10";
			}
			else
			{
				// Массакра.
				dialog.text = "Jesteśmy na miejscu, kapitanie! Widzę, że wszystko ładnie załatwiłeś. Ale widzisz... nie potrzebujemy żadnych świadków, więc... Podziękujmy kapitanowi, chłopcy!";
				link.l1 = RandSwear()+"Powinienem był cię zastrzelić, gdy tylko cię spotkałem!";
				link.l1.go = "JusticeOnSale_11";
			}
			chrDisableReloadToLocation = false;
		break;
		
		case "JusticeOnSale_10":
			DialogExit();
			if(sti(PChar.GenQuest.JusticeOnSale.RewardType) == 0)
			{
				if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.PrisonMoney"))
				{
					AddItems(PChar, "indian_"+(1+hrand(10)), 1);
				}
				else
				{
					AddItems(PChar, "obereg_"+(1+hrand(10)), 1);
				}
			}
			else
			{
				if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.PrisonMoney"))
				{
					AddMoneyToCharacter(PChar, sti(PChar.rank) * 700 + hrand(2000));
				}
				else
				{
					AddMoneyToCharacter(PChar, sti(PChar.rank) * 500 + hrand(1000));
				}
			}
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_ShorePirate_" + i);
				LAi_Type_Actor_Reset(rChar);
				LAi_ActorGoToLocation(rChar, "reload", LAi_FindNearestFreeLocator2Pchar("reload"), "none", "", "", "", 3.0);
			}
			AddQuestRecord("JusticeOnSale", "3");
			CloseQuestHeader("JusticeOnSale");
		break;
		
		case "JusticeOnSale_11":
			AddQuestRecord("JusticeOnSale", "4");
			CloseQuestHeader("JusticeOnSale");
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_ShorePirate_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_Group_MoveCharacter(rChar, "JusticeOnSale_ShoreGroup");
			}
			
			LAi_Group_SetRelation("JusticeOnSale_ShoreGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
		break;
		
		// belamour постоялец-->
		case "Unwantedpostor_room":
			dialog.text = ""+GetSexPhrase("Kimże jesteś? I dlaczego wdzierasz się do mego pokoju?","Wow. Kim jesteś? To oczywiście mój pokój, ale nie mam nic przeciwko takiemu towarzystwu. Czy to dostawa miłości?")+"";
			link.l1 = ""+GetSexPhrase("Już nie twoja. Karczmarz wynajął mi pokój, a skoro za niego nie płacisz, zaraz stąd wylecisz. Możemy to załatwić po dobroci albo siłą. Wybór należy do ciebie.","Śnisz na jawie. W naszym wypadku to czyszczenie. Więc oczyść to miejsce z siebie. To teraz mój pokój, bo w przeciwieństwie do ciebie, zawsze płacę karczmarzom.")+"Rozumiem. Proszę podaj teksty do tłumaczenia.";
			link.l1.go = "Unwantedpostor_room_1";
		break;
		
		case "Unwantedpostor_room_1":
			If(sti(pchar.reputation.fame) > 60)
			{
				dialog.text = " "+GetSexPhrase("Zdaje się, że o tobie słyszałem. Dobra, wygrałeś, odchodzę, jeszcze chcę żyć...","Hmm, wiele o tobie słyszałem. Przypuszczam, że nie tylko twój język jest ostry. Dobrze, nie gniewaj się, pokój jest twój.")+"";
				link.l1 = ""+GetSexPhrase("Podjąłeś dobrą decyzję.","Dobry chłopcze.")+"";
				link.l1.go = "Unwantedpostor_peace";
				break;
			}
			dialog.text = "I'm sorry, I need the content in order to provide a translation. Can you please provide the text that needs to be translated?"+GetSexPhrase("Tak to jest, co? Cóż, wybieram trudną drogę.","Ty suko! Chciałem z tobą postąpić po ludzku...")+" ";
			link.l1 = ""+GetSexPhrase("Jak sobie życzysz...","I ty nazywasz to 'grzecznie'? Żal mi ciebie. Chociaż, może nie.")+"";
			link.l1.go = "Unwantedpostor_fight";
		break;
		
		case "Unwantedpostor_peace":
			DialogExit();
			sld = CharacterFromID("Berglar_Unwantedpostor");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld.lifeday = 0;
			DeleteAttribute(PChar, "GenQuest.Unwantedpostor");
			SetFunctionTimerCondition("Unwantedpostor_NextQuest", 0, 0, 180, false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //разрешить драться
			chrDisableReloadToLocation = false; // открыть локацию
			sTemp = 40*MOD_SKILL_ENEMY_RATE/2;
			AddCharacterExpToSkill(pchar, "Fortune", sti(sTemp));
			AddCharacterExpToSkill(pchar, "Sneak", sti(sTemp));
			AddCharacterExpToSkill(pchar, "Leadership", sti(sTemp));
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;
		
		case "Unwantedpostor_fight":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_SetFightMode(pchar, true);
			sld = characterFromId("Berglar_Unwantedpostor"); 
			LAi_SetWarriorType(sld);
			LAi_Group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_SetCheckMinHP(sld, 10, true, "Unwantedpostor_Win");
			LAi_SetCheckMinHP(pchar, 10, true, "Unwantedpostor_Lose");	
		break;
		
		case "Unwantedpostor_Win":
			dialog.text = ""+GetSexPhrase("Dobrze, dobrze, przestań! Nie zabijaj mnie. Odchodzę.","Stój! Co mamy teraz zrobić, zabić się nawzajem o ten pokój?! Udław się nim, cały twój. Śmierdziel...")+"";
			link.l1 = ""+GetSexPhrase("Rozsądna decyzja. Następnym razem pomyśl głową: nie każdy jest tak łaskawy jak ja, mogą cię niechcący zabić.","Ludzie.")+"";
			link.l1.go = "Unwantedpostor_Win_1";
		break;
		
		case "Unwantedpostor_Win_1":
			DialogExit();
			sld = CharacterFromID("Berglar_Unwantedpostor");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld.lifeday = 0;
			if(CheckAttribute(pchar,"GenQuest.Unwantedpostor")) DeleteAttribute(PChar, "GenQuest.Unwantedpostor"); // полуночная драка
			SetFunctionTimerCondition("Unwantedpostor_NextQuest", 0, 0, 170+rand(20), false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //разрешить драться
			chrDisableReloadToLocation = false; // открыть локацию
			sTemp = 40*MOD_SKILL_ENEMY_RATE/2;
			AddCharacterExpToSkill(pchar, "FencingL", sti(sTemp));
			AddCharacterExpToSkill(pchar, "FencingS", sti(sTemp));
			AddCharacterExpToSkill(pchar, "FencingH", sti(sTemp));
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;
		
		case "Unwantedpostor_Lose":
			dialog.text = ""+GetSexPhrase("No cóż, wyrzuciłeś mnie? Wynoś się stąd, zanim cię posiekam.","Więc jedyne, co potrafisz, to paplać. Ciesz się, że wciąż jestem w dobrym humorze, bo inaczej zrobiłbym ci coś jeszcze gorszego. Wynocha stąd!")+"";
			link.l1 = "Got it! Please provide the text you need translated."+GetSexPhrase("Cholera...","Cholera, niedoceniłem cię... Dobra, dobra, już odchodzę.")+" ";
			link.l1.go = "Unwantedpostor_Lose_1";
		break;
		
		case "Unwantedpostor_Lose_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //разрешить драться
			chrDisableReloadToLocation = false; // открыть локацию
			sld = CharacterFromID("Berglar_Unwantedpostor");
			sld.lifeday = 0;
			if(CheckAttribute(pchar,"GenQuest.Unwantedpostor")) pchar.GenQuest.Unwantedpostor = "Lose"; // если драка за полночь перевалит
			DoQuestReloadToLocation(Locations[FindLocation(pchar.location)].fastreload+"_tavern", "reload", "reload2_back", "");	
		break;
		// <-- belamour постоялец
		
		// belamour пьяный матрос -->
		case "GuiltySailor":
			dialog.text = "Ach?.. Wynocha, żółtodziobie, nie piję... hic!.. z byle kim.";
			link.l1 = "Uderzę cię teraz tak mocno, że przez tydzień nie będziesz pić.";
			link.l1.go = "GuiltySailor_1";
		break;
		
		case "GuiltySailor_1":
			dialog.text = "Co?! Czy wiesz, z kim rozmawiasz? Jestem marynarzem ze statku '"+pchar.ship.name+"'! Muszę tylko powiedzieć kapitanowi, a nawet nie zdążysz opuścić miasta! Wynoś się stąd, póki jeszcze jesteś cały."; 
			link.l1 = "...";
			link.l1.go = "GuiltySailor_2";
		break;
		
		case "GuiltySailor_2":
			dialog.text = "...";
			link.l1 = "... ";
			link.l1.go = "GuiltySailor_3";
		break;
		
		case "GuiltySailor_3":
			dialog.text = "Kapitanie?..";
			link.l1 = "Będziesz szorować pokład przez miesiąc.";
			link.l1.go = "GuiltySailor_4";
		break;
		
		case "GuiltySailor_4":
			NPChar.Dialog.currentnode = "GuiltySailor_Again";
			SetFunctionTimerCondition("GuiltySailor_NextQ", 0, 0, 45+rand(45), false);
			DialogExit();
		break;
		
		case "GuiltySailor_Again":
			dialog.text = "Przepraszam, kapitanie!";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "GuiltySailor_Again";
		break;
		// <-- пьяный матрос
		
		// belamour хороший специалист -->
		case "ExpertSailor":
			int ExpertSailorVar = 1 + hrand(2);
			dialog.text = "Pozdrowienia, kapitanie! Wiem, że jesteś kapitanem, tak.";
			link.l1 = "Witaj. Skąd wiesz, że jestem kapitanem?";
			link.l1.go = "ExpertSailor_"+ExpertSailorVar;
		break;
		
		case "ExpertSailor_1": // матрос
			dialog.text = "Ha, jestem doświadczonym wilkiem morskim, żegluję po morzach od ponad dekady. Zajmowałem się głównie żeglugą: żeglowałem w spokoju, w burzy, na lugrze, a nawet na okręcie wojennym. Prawda, w zeszłym miesiącu zostałem ranny po ciężkiej bitwie, była silna burza i nikt nie odważył się wejść na żagiel, więc ja to zrobiłem, ale zapłaciłem za to cenę, na szczęście tylko skręciłem kostkę i nie mogłem chodzić przez kilka tygodni. Więc odprawili mnie na brzeg. Teraz jest lepiej i siedzę tu, czekając na okazję.";
			link.l1 = "Interesujące. Nie miałbym nic przeciwko specjaliście w tej dziedzinie. Chciałbyś dołączyć do mojej załogi?";
			link.l1.go = "ExpertSailor_1_1";
		break;
		
		case "ExpertSailor_1_1":
			dialog.text = " Czemu nie? Już tęsknię za pokładem statku i szumem żagli wypełnionych świeżym wiatrem. Mogę również szkolić twoją załogę, jeśli zajdzie taka potrzeba. Ale od razu poproszę cię o tysiąc pesos, inaczej moje kieszenie są już puste. Zresztą jak reszta załogi. Jestem uczciwym człowiekiem.";
			link.l1 = "Nie, prawdopodobnie odmówię. Jeśli wszyscy marynarze dostaną tysiąc pesos za najem, zbankrutuję. Nie obwiniaj mnie.";
			link.l1.go = "ExpertSailor_nomoney";
			if(GetFreeCrewQuantity(pchar) > 0 && sti(pchar.money) >= 1000)
			{
				link.l2 = "Umowa stoi. Nie mam nic przeciwko tysiącu pesos za dobrego specjalistę. Poczekaj... tutaj. I czekam na ciebie na statku.";
				link.l2.go = "ExpertSailor_payS";
			}
		break;
		
		case "ExpertSailor_nomoney":
			DialogExit();
			NPChar.Dialog.currentnode = "ExpertSailor_Again";
		break;
		
		case "ExpertSailor_payS":
			DialogExit();
			AddMoneyToCharacter(pchar, -1000);
			AddCharacterCrew(pchar, 1);
			ChangeCrewExp(pchar, "Sailors", 10);
			AddCrewMorale(pchar, 1);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
		break;
		
		case "ExpertSailor_2": // канонир
			dialog.text = "Ha, jestem doświadczonym wilkiem morskim, żegluję po morzu od ponad dekady. Głównie stałem przy armatach: strzelałem z falconetów, z karonad, kulwerin, sakerów... służyłem na lugrze, a nawet na okręcie liniowym. Prawda, w zeszłym miesiącu zostałem ranny po ciężkiej bitwie, rykoszet z kartacza mnie trafił, nic poważnego, tylko zadrapanie na nodze, więc spisali mnie na ląd. Teraz czuję się lepiej i siedzę tu, czekając na okazję.";
			link.l1 = "Interesujące. Nie miałbym nic przeciwko specjaliście w tej sprawie. Chciałbyś dołączyć do mojej załogi?";
			link.l1.go = "ExpertSailor_2_1";
		break;
		
		case "ExpertSailor_2_1":
			dialog.text = "Dlaczego nie? Już tęsknię za pokładem artyleryjskim, zapachem palącego się prochu i hukiem salw armatnich. Mogę również poprowadzić twój zespół, jeśli zajdzie taka potrzeba. Ale od razu poproszę cię o tysiąc pesos, bo inaczej moje kieszenie już są puste. Wtedy, jak reszta załogi, jestem uczciwym człowiekiem.";
			link.l1 = "Nie, prawdopodobnie odmówię. Jeśli wszystkim marynarzom płacą tysiąc pesos za zatrudnienie, to zbankrutuję. Nie obwiniaj mnie.";
			link.l1.go = "ExpertSailor_nomoney";
			if(GetFreeCrewQuantity(pchar) > 0 && sti(pchar.money) >= 1000)
			{
				link.l2 = "Umowa stoi. Nie mam nic przeciwko tysiąc pesos za dobrego specjalistę. Poczekaj... tutaj. I czekam na ciebie na statku.";
				link.l2.go = "ExpertSailor_payС";
			}
		break;
		
		case "ExpertSailor_payС":
			DialogExit();
			AddMoneyToCharacter(pchar, -1000);
			AddCharacterCrew(pchar, 1);
			ChangeCrewExp(pchar, "Cannoners", 10);
			AddCrewMorale(pchar, 1);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
		break;
		
		case "ExpertSailor_3": // солдат
			dialog.text = "Ha, jestem doświadczonym wilkiem morskim, pływam po morzu już od ponad dekady. Głównie walczyłem w abordażach: walczyłem z piratami i regularnymi armiami, wiem jak władać wszelkiego rodzaju bronią, byłem na lugrze, a nawet na okręcie liniowym. Prawda, w zeszłym miesiącu zostałem ranny po ciężkiej bitwie, to była tylko mała rysa od szabli na plecach, tchórz nie mógł się ze mną zmierzyć, ale zabiłem go w rewanżu, och, powinniście byli zobaczyć ich twarze, kiedy zobaczyli tę rysę, ha-ha. Więc, spisali mnie na brzeg. Teraz czuję się lepiej i siedzę tutaj, czekając na okazję.";
			link.l1 = "Interesujące. Nie miałbym nic przeciwko specjaliście w tej dziedzinie. Czy chciałbyś dołączyć do mojej ekipy?";
			link.l1.go = "ExpertSailor_3_1";
		break;
		
		case "ExpertSailor_3_1":
			dialog.text = "Dlaczego nie? Już tęsknię za dźwiękiem szabel, trzaskiem statków zbliżających się do burt i adrenaliną bitwy. Mogę również trenować twoją załogę, jeśli zajdzie taka potrzeba. Ale od razu poproszę cię o tysiąc pesos, w przeciwnym razie moje kieszenie są już puste. Potem, jak reszta załogi, jestem uczciwym człowiekiem.";
			link.l1 = "Nie, prawdopodobnie odmówię. Jeśli wszyscy marynarze dostaną tysiąc pesos za zatrudnienie, zbankrutuję. Nie obwiniaj.";
			link.l1.go = "ExpertSailor_nomoney";
			if(GetFreeCrewQuantity(pchar) > 0 && sti(pchar.money) >= 1000)
			{
				link.l2 = "Układ. Nie mam nic przeciwko tysiącu pesos za dobrego specjalistę. Poczekaj... tutaj. I czekam na ciebie na statku.";
				link.l2.go = "ExpertSailor_payA";
			}
		break;
		
		case "ExpertSailor_payA":
			DialogExit();
			AddMoneyToCharacter(pchar, -1000);
			AddCharacterCrew(pchar, 1);
			ChangeCrewExp(pchar, "Soldiers", 10);
			AddCrewMorale(pchar, 1);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
		break;
		
		case "ExpertSailor_Again":
			dialog.text = "Powodzenia na morzu, kapitanie!";
			link.l1 = "Ty też.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ExpertSailor_Again";
		break;
		// <-- хороший специалист
		
		//belamour ночной приключенец -->
		// матрос -->
		case "NightAdventure_Sailor":
			LAi_RemoveLoginTime(npchar);
			dialog.text = " K-kim jesteś?";
			link.l1 = "Jestem kapitanem "+GetFullName(pchar)+".";
			if (pchar.id == "Knippel")
			{
				link.l1 = "Przepraszam, kumplu, ale się spieszę.";
				link.l1.go = "exit";
				LAi_CharacterDisableDialog(npchar);
				break;
			}
			switch(pchar.GenQuest.NightAdventureVar)
			{
				case "NightAdventure_SailorTavern":          link.l1.go = "NightAdventure_Sailor_1_1"; break; // до таверны
				case "NightAdventure_SailorShuler0":         link.l1.go = "NightAdventure_Sailor_2_1"; break; // шулер
				case "NightAdventure_SailorShulerGiveMoney": link.l1.go = "NightAdventure_Sailor_2_1"; break;
				case "NightAdventure_SailorShulerGiveOk":    link.l1.go = "NightAdventure_Sailor_2_1"; break; 
				case "NightAdventure_SailorShulerFight":     link.l1.go = "NightAdventure_Sailor_2_1"; break; 
				case "NightAdventure_SailorBoat":      		 link.l1.go = "NightAdventure_Sailor_3_1"; break; // до пирса
				case "NightAdventure_SailorShip":            link.l1.go = "NightAdventure_Sailor_3_1"; break;
				case "NightAdventure_Bull":                  link.l1.go = "NightAdventure_Bull";       break; // наезд
			}
		break;
		// до таверны 
		case "NightAdventure_Sailor_1_1":
			dialog.text = "K-kapitanie?.. hic! K-kapitanie... odprowadź mnie do k-karczmy... hic!.. co? Proszę. Wydaje się, że ... zgubiłem się w tej w tej k-kolonii, tak ... hic! ..";
			link.l1 = "Złaź ze mnie, nie mam czasu!";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Dobrze, chodźmy. Wyglądasz na kogoś, kto sam by tam nie dotarł.";
			link.l2.go = "NightAdventure_Sailor_1_2";
		break;
		
		case "NightAdventure_Sailor_1_2":
			dialog.text = "Po prostu... hic!.. powoluuu, p-proszę. Nie jestem... hic!.. w stanie... ustać...";
			link.l1 = "Dobrze, ruszajmy, powoli.";
			link.l1.go = "NightAdventure_Sailor_tavern";
		break;
		
		case "NightAdventure_Sailor_tavern":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			NPChar.Dialog.currentnode = "NightAdventure_SailorAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventureNode = "NA_SailorTavern"; // для выбора диалога
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocationCondition("NightAdventure_Intavern", npchar.City+"_tavern", true);
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		// шулер
		case "NightAdventure_Sailor_2_1":
			dialog.text = "Kapitanie?.. hic!.. K-kapitanie... pomóż mi!";
			link.l1 = "Złaź ze mnie, nie mam czasu!";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Co z tobą nie tak?";
			link.l2.go = "NightAdventure_Sailor_2_2";
		break;
		
		case "NightAdventure_Sailor_2_2":
			dialog.text = "Tam... w tawernie... hic!.. Szuler!";
			link.l1 = "Cóż, co w tym złego? W każdej tawernie każdej kolonii są szulerzy, jak błoto.";
			link.l1.go = "NightAdventure_Sailor_2_3";
		break;
		
		case "NightAdventure_Sailor_2_3":
			dialog.text = "K-kapitanie, ty... nie rozumiesz... hic!... On zostawił m-mnie... bez ani jednego peso! Hic!.. A potem... wygnał mnie... hic!..";
			link.l1 = "Więc, czego teraz ode mnie chcesz?";
			link.l1.go = "NightAdventure_Sailor_2_4";
		break;
		
		case "NightAdventure_Sailor_2_4":
			dialog.text = "Chodź z-ze mną... hik!... Załatw go! N-niech... hik!... odda mi moje pieniądze! hik!..";
			link.l1 = "Nie musisz być karciarzem, aby pokonać pijaka przy stole. Następnym razem pij mniej.";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Cóż, po co mi to, co? .. Dobrze, chodźmy, zobaczmy na tego twojego szulerka.";
			link.l2.go = "NightAdventure_Sailor_2_5";
		break;
		
		case "NightAdventure_Sailor_2_5":
			dialog.text = "Po prostu... czk!.. poowoli, p-proszę. Nie jestem... czk!.. w stanie... u-stać...";
			link.l1 = "Dobrze, idźmy powoli.";
			link.l1.go = "NightAdventure_Sailor_gambler";
		break;
		
		case "NightAdventure_Sailor_gambler":
			DialogExit();
			NPChar.Dialog.currentnode = "NightAdventure_SailorAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventureNode = "NA_SailorGambler"; // для выбора диалога
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocationCondition("NightAdventure_Intavern", npchar.City+"_tavern", true);
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		// диалог в таверне с матросом
		case "NA_SailorTavern":
			dialog.text = "K-kapitanie... hic!.. wielkie dzięki... pomogłeś mi! Ja... proszę bardzo... hic!.. To dla ciebie.";
			link.l1 = "Chodź, nieważne... Nie pij już tak. Albo przynajmniej nie szukaj przygód.";
			link.l1.go = "NA_SailorTavern_1";
		break;
		
		case "NA_SailorTavern_1":
			DialogExit();
			pchar.quest.NightAdventure_Intavern.over = "yes";
			chrDisableReloadToLocation = false;
			if(GetDataDay() < 7) AddMoneyToCharacter(pchar, 10);
			if(GetDataDay() >= 7  && GetDataDay() < 13) {GiveItem2Character(pchar, "slave_01");  Log_Info("You've received Harpoon");}
			if(GetDataDay() >= 13 && GetDataDay() < 19) {GiveItem2Character(pchar, "potion5");   Log_Info("You've received Ginger root");}
			if(GetDataDay() >= 19 && GetDataDay() < 25) {GiveItem2Character(pchar, "cartridge"); Log_Info("You've received Paper cartridge");}
			if(GetDataDay() >= 25) 
			{
				if(GetDataDay() == 25) {GiveItem2Character(pchar, "amulet_8");  Log_Info("You've received amulet 'Anchor'");}
				if(GetDataDay() == 26) {GiveItem2Character(pchar, "amulet_9");  Log_Info("You've received amulet 'Encolpion'");}
				if(GetDataDay() == 27) {GiveItem2Character(pchar, "obereg_7");  Log_Info("You've received amulet 'Fisher'");}
				if(GetDataDay() >  27) {GiveItem2Character(pchar, "obereg_11"); Log_Info("You've received amulet 'Pilgrim'");}
			}
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// разговор про  шулера
		case "NA_SailorGambler":
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorShuler0")
			{
				dialog.text = "K-kapitanie!.. T-ten... Hik!.. Szuler!..";
				link.l1 = "Ja? Szuler karciany?";
				link.l1.go = "NA_SailorGamblerBelka";
			}
			else	
			{
				dialog.text = "Tam jest, kapitanie! Hic!.. S-siedzi przy stole...";
				link.l1 = "Chodź...";
				link.l1.go = "NA_SailorGamblerCards"; 
			}
					
		break;
		// шулер сбежал
		case "NA_SailorGamblerBelka": 
			dialog.text = "Nie... hic!... Sharper!... Zniknął!...";
			link.l1 = "Cóż, odszedł, więc na ciebie nie czekał.";
			link.l1.go = "NA_SailorGamblerBelka_1";
		break;
		
		case "NA_SailorGamblerBelka_1":
			dialog.text = "A co... d-dalej? Hic!..";
			link.l1 = "Cóż, teraz już nic nie możesz zrobić. Na pewno nie będę go szukał w nocy po całej kolonii. Nie pij już w ten sposób. Albo przynajmniej nie graj hazardu będąc pijanym.";
			link.l1.go = "NA_SailorGamblerBelka_2";
		break;
		
		case "NA_SailorGamblerBelka_2":
			DialogExit();
			pchar.quest.NightAdventure_Intavern.over = "yes";
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		// шулер остался таверне
		case "NA_SailorGamblerCards":
			DialogExit();
			pchar.quest.NightAdventure_Intavern.over = "yes";
			iNation = npchar.nation
			iRank = MOD_SKILL_ENEMY_RATE+sti(pchar.rank);
			iScl = 15 + 2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("NightAdventure_CardProf", "citiz_"+(rand(9)+11), "man", "man", iRank, iNation, 1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_04", "pistol1", "bullet", iScl*2);
			sld.dialog.filename    = "GenQuests_Dialog.c";
			sld.dialog.currentnode = "NightAdventure_CardProf";
			sld.greeting = "player";
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			AddMoneyToCharacter(sld, sti(pchar.GenQuest.NightAdventure_money));
			GiveItem2Character(sld, "totem_13");
			FreeSitLocator(pchar.location, "sit_front4");
			ChangeCharacterAddressGroup(sld, pchar.location, "sit", "sit_front4");
			LAi_SetSitType(sld);
			chrDisableReloadToLocation = false;
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// разговор с самим шулером
		case "NightAdventure_CardProf":
			dialog.text = "Proponuję grę w kości. Jesteś zainteresowany?";
			link.l1 = "Nic z tego. Jestem kapitanem statku i nie gram z szulerami. Ale mogę łatwo zmiażdżyć ci boki, jeśli nie oddasz pieniędzy temu dobremu człowiekowi tam.";
			link.l1.go = "NightAdventure_CardProf_1";
		break;
		
		case "NightAdventure_CardProf_1":
			dialog.text = "Z szulerami?! Czy ja jestem szulerem? Komu oddać pieniądze, temu pijusowi?! Obrażasz mnie, kapitanie...";
			link.l1 = "Mogę obrazić jeszcze bardziej. Oddaj pieniądze.";
			link.l1.go = "NightAdventure_CardProf_2";
		break;
		
		case "NightAdventure_CardProf_2":
			dialog.text = "Tak, nie jestem oszustem karcianym! Jestem uczciwym graczem. Szczęście wygrywa, a twój przyjaciel po prostu miał pecha, to wszystko.";
			link.l1 = "   Szczęście, co? Daj mi swoje kości, a zobaczę, jak szczęśliwie wypadną.";
			link.l1.go = "NightAdventure_CardProf_3";
		break;
		
		case "NightAdventure_CardProf_3":
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorShulerGiveMoney") // отдал деньги
			{
				AddMoneyToCharacter(pchar, makeint(pchar.GenQuest.NightAdventure_money));
				dialog.text = "Dobrze, dobrze, spokojnie, kapitanie. No cóż, pobiłem pijaka i trochę oszukałem, a tak robi co drugi gracz. Oto jego pieniądze.";
				link.l1 = "To lepiej. I mam nadzieję, że rozumiesz, że jeśli mój przyjaciel teraz powie, że to nie cała suma, to wrócę do ciebie?";
				link.l1.go = "NightAdventure_CardProf_GiveMoney";
			}
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorShulerGiveOk") // играл честно
			{
				dialog.text = "Tak proszę, oto moje kości. Oba zestawy. Sprawdź. Nie mam nic do ukrycia.";
				link.l1 = "Więc... Para... Nic... Para... Full... Nic... Nic... Dwie Pary... Set... Nic... Para...";
				link.l1.go = "NightAdventure_CardProf_Ok";
			}
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorShulerFight") // драка
			{
				dialog.text = "Tak proszę, oto moje kości. Obie pary. Sprawdź. Nie mam nic do ukrycia.";
				link.l1 = "Więc... Kareta... Kareta... Full... Full... Kareta... Poker... Full... Poker... Kareta... Full... Hmm, a jak mi to wytłumaczysz?";
				link.l1.go = "NightAdventure_CardProf_Fight";
			}
		break;
		// разошлись миром
		case "NightAdventure_CardProf_GiveMoney":
			dialog.text = "Rozumiem wszystko, oto cała suma. Powodzenia tobie i twemu przyjacielowi.";
			link.l1 = "I ty.";
			link.l1.go = "NightAdventure_CardProf_GiveMoney_1";
		break;
		
		case "NightAdventure_CardProf_GiveMoney_1":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_CharacterDisableDialog(npchar);
			sld = characterFromId(pchar.GenQuest.NightAdventureId);
			sld.dialog.currentnode = "NightAdventure_CardProf_GiveMoney_2";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		// матрос забирает свои деньги
		case "NightAdventure_CardProf_GiveMoney_2":
			AddMoneyToCharacter(pchar, - makeint(pchar.GenQuest.NightAdventure_money));
			dialog.text = "Ale... on n-nie chciał tego przyznać! Hic!..";
			link.l1 = "Tak, próbował tego uniknąć. Oto, zatrzymaj swoje pieniądze.";
			link.l1.go = "NightAdventure_CardProf_GiveMoney_3";
		break;
		
		case "NightAdventure_CardProf_GiveMoney_3":
			AddMoneyToCharacter(pchar, makeint(pchar.GenQuest.NightAdventure_money)/2);
			dialog.text = "K-kapitanie... hic!.. dzięki wielkie... pomogłeś mi! Ja...'wymiotuje na bok'... proszę... hic!.. To dla ciebie.";
			link.l1 = "Chodź, ugh... nieważne... Nie pij już w ten sposób. Albo przynajmniej nie hazarduj się, kiedy jesteś pijany.";
			link.l1.go = "NightAdventure_CardProf_GiveMoney_4";
		break;
		
		case "NightAdventure_CardProf_GiveMoney_4":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// играл честно
		case "NightAdventure_CardProf_Ok":
			dialog.text = "No i co? Przekonany?";
			link.l1 = "Hmm, to naprawdę wydają się być zwykłe kości ...";
			link.l1.go = "NightAdventure_CardProf_Ok_1";
		break;
		
		case "NightAdventure_CardProf_Ok_1":
			dialog.text = "Powiedziałem ci. A twój przyjaciel jest po prostu pijany. On też nie chciał przyznać się do porażki, więc przyprowadził cię tutaj.";
			link.l1 = "Zgoda, przepraszam za incydent. Powodzenia.";
			link.l1.go = "NightAdventure_CardProf_Ok_2";
		break;
		
		case "NightAdventure_CardProf_Ok_2":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_CharacterDisableDialog(npchar);
			sld = characterFromId(pchar.GenQuest.NightAdventureId);
			sld.dialog.currentnode = "NightAdventure_CardProf_Ok_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		// подходит матрос
		case "NightAdventure_CardProf_Ok_3":
			dialog.text = "Więc... hic!.. co to jest?.. On... hic!.. nie jest oszustem?..";
			link.l1 = "Cóż, wydaje się, że grał uczciwie.";
			link.l1.go = "NightAdventure_CardProf_Ok_4";
		break;
		
		case "NightAdventure_CardProf_Ok_4":
			dialog.text = "I co dalej?... N-następne? Hik!..";
			link.l1 = "Cóż, teraz nic nie możesz zrobić. Uczciwie cię pokonał. Nie pij już więcej w ten sposób. Albo przynajmniej nie graj w hazard, gdy jesteś pijany.";
			link.l1.go = "NightAdventure_CardProf_Ok_5";
		break;
		
		case "NightAdventure_CardProf_Ok_5":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			DeleteAttribute(pchar,"GenQuest.NightAdventure_money");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// драка 
		case "NightAdventure_CardProf_Fight":
			dialog.text = "Szczęście. Po prostu miałeś farta, i tyle. Szczęście to kapryśna dama.";
			link.l1 = "Hmm, naprawdę. No cóż, zagrajmy z tobą, ale pamiętaj, że gram tymi kośćmi!";
			link.l1.go = "NightAdventure_CardProf_Fight_1";
		break;
		
		case "NightAdventure_CardProf_Fight_1":
			dialog.text = "Te?.. To jest... Nie, nie chcę z tobą grać! Obraziłeś mnie. A zresztą, jestem spłukany...";
			link.l1 = "Może chcesz, żebym opowiedział wszystkim w tej tawernie o twoich kościach? Albo może im je pokazał? A potem opowiesz im o szczęściu. Co o tym myślisz?";
			link.l1.go = "NightAdventure_CardProf_Fight_2";
		break;
		
		case "NightAdventure_CardProf_Fight_2":
			dialog.text = "Co?! Kim ty jesteś?! Próbujesz mnie szantażować?! Zaraz cię podziurawię, jeśli się stąd nie wyniesiesz!";
			link.l1 = "Wolałbym zostać tutaj i pokazać wszystkim twoje kości.";
			link.l1.go = "NightAdventure_CardProf_Fight_3";
		break;
		
		case "NightAdventure_CardProf_Fight_3":
			dialog.text = "Cóż, chodź tutaj, padlino!";
			link.l1 = "Nie zgub spodni.";
			link.l1.go = "NightAdventure_CardProf_Fight_4";
		break;
		
		case "NightAdventure_CardProf_Fight_4":
			LAi_LocationDisableOfficersGen(pchar.location, true); // офицеров не  пускать
			SetFunctionLocationCondition("NightAdventure_Duel", Locations[FindLocation(pchar.location)].fastreload+"_town", false);
			pchar.quest.NightAdventure_KillPhant.over = "yes";
			PChar.questTemp.duel.enemy = NPChar.id;
			AddDialogExitQuestFunction("Duel_Prepare_Fight");
			DialogExit();
		break;
		// матрос на выходе
		case "NightAdventure_CardProf_Fight_5":
			dialog.text = "K-kapitanie?.. Ty... hik!.. wdałeś się w bójkę?.. A ten... hik!.. oszust?";
			link.l1 = "Sam dostał w mordę. Nie będzie grał z nikim innym.";
			link.l1.go = "NightAdventure_CardProf_Fight_6";
		break;
		
		case "NightAdventure_CardProf_Fight_6":
			dialog.text = "Ale... on n-nie chciał tego przyznać! Hic!..";
			link.l1 = "Tak, próbował tego uniknąć. Po prostu nie miał twoich pieniędzy. Pewnie je wydał.";
			link.l1.go = "NightAdventure_CardProf_Fight_7NM";
			link.l2 = "Tak, próbował tego uniknąć. Oto twoje pieniądze.";
			link.l2.go = "NightAdventure_CardProf_Fight_7";
		break;
		
		case "NightAdventure_CardProf_Fight_7NM": // скажем, что нет денег
			ChangeCharacterComplexReputation(pchar,"nobility", -5); 
			ChangeOfficersLoyality("bad", 2); 
			dialog.text = "A co... d-dalej? Hyk!..";
			link.l1 = "Cóż, teraz nic nie możesz zrobić. Uczciwie cię pokonał. Nie pij już więcej w ten sposób. Albo przynajmniej nie graj w karty, gdy jesteś pijany.";
			link.l1.go = "NightAdventure_CardProf_Fight_End";
		break;
		
		case "NightAdventure_CardProf_Fight_7": // деньги есть
			AddMoneyToCharacter(pchar, - makeint(pchar.GenQuest.NightAdventure_money));
			ChangeCharacterComplexReputation(pchar,"nobility", 3); 
			ChangeOfficersLoyality("good", 1); 
			dialog.text = "K-kapitanie... hik!.. dziękuję ci bardzo... pomogłeś mi! Ja... 'wymiotuje na bok'... proszę bardzo... hik!.. To dla ciebie.";
			link.l1 = "Chodź, uch... nieważne... Nie pij już więcej w taki sposób. Albo przynajmniej nie graj w hazard, kiedy jesteś pijany.";
			link.l1.go = "NightAdventure_CardProf_Fight_End";
			AddMoneyToCharacter(pchar, makeint(pchar.GenQuest.NightAdventure_money)/2);
		break;
		
		case "NightAdventure_CardProf_Fight_End": 
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			DeleteAttribute(pchar,"GenQuest.NightAdventure_money");
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			DialogExit();
			
		break;
		// проводить до пирса
		case "NightAdventure_Sailor_3_1":
			dialog.text = "Kapitane?.. hik!.. K-kapitane... odprowadź mnie do p-p-pomostu... hik!.. co? Proszę. Ja... hik!.. m-muszę iść na ... statek... Bosman... będzie klnąć... hik!.. jeśli się s-spóźnię...";
			link.l1 = "Złaź ze mnie, nie mam czasu!";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Dobrze, chodźmy. Wygląda na to, że sam nie dasz rady tam dotrzeć.";
			link.l2.go = "NightAdventure_Sailor_3_2";
		break;
		
		case "NightAdventure_Sailor_3_2":
			dialog.text = "Tylko... czk!.. powoli, p-proszę. Ja... czk!.. nie... mogę... ustać...";
			link.l1 = "Dobrze, idźmy powoli.";
			link.l1.go = "NightAdventure_Sailor_3_3";
		break;
		
		case "NightAdventure_Sailor_3_3":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			NPChar.Dialog.currentnode = "NightAdventure_SailorAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorBoat")
			{
				pchar.GenQuest.NightAdventureNode = "NA_SailorBoat"; 
			}
			else
			{
				pchar.GenQuest.NightAdventureNode = "NA_SailorShip"; 
			}
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocatorCondition("NightAdventure_ToBoat",  npchar.City+"_town", "quest", "quest1", false)
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		// вариант просто проводить
		case "NA_SailorBoat":
			dialog.text = "K-kapitanie... hik!.. dzięki wielkie... pomogłeś mi! Ja...'wymiotuje na bok'... proszę... hik!.. To dla ciebie.";
			link.l1 = "Chodź, ugh... nieważne... Nie pij już tak. Albo przynajmniej nie szukaj przygód.";
			link.l1.go = "NA_SailorBoat_1";
		break;
		
		case "NA_SailorBoat_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			if(GetDataDay() < 7) AddMoneyToCharacter(pchar, 10);
			if(GetDataDay() >= 7  && GetDataDay() < 13)  {GiveItem2Character(pchar, "slave_01");  Log_Info("You've received Harpoon");}
			if(GetDataDay() >= 13 && GetDataDay() < 19)  {GiveItem2Character(pchar, "potion5");   Log_Info("You've received Ginger root");}
			if(GetDataDay() >= 19 && GetDataDay() < 25)  {GiveItem2Character(pchar, "cartridge"); Log_Info("You've received Paper cartridge");}
			if(GetDataDay() >= 25) 
			{
				if(GetDataDay() == 25) {GiveItem2Character(pchar, "amulet_8");  Log_Info("You've received amulet 'Anchor'");}
				if(GetDataDay() == 26) {GiveItem2Character(pchar, "amulet_9");  Log_Info("You've received amulet 'Encolpion'");}
				if(GetDataDay() == 27) {GiveItem2Character(pchar, "obereg_7");  Log_Info("You've received amulet 'Fisher'");}
				if(GetDataDay() >  27) {GiveItem2Character(pchar, "obereg_11"); Log_Info("You've received amulet 'Pilgrim'");}
			}
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "NightAdventure_OpenLoc", -1); 
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// просится на корабль
		case "NA_SailorShip":
			dialog.text = "K-kapitanie!.. Statek!";
			link.l1 = "Jaka 'łajba'?";
			link.l1.go = "NA_SailorShip_1";
		break;
		
		case "NA_SailorShip_1":
			dialog.text = "Statek!.. Gdzie on jest?.. hic!..";
			link.l1 = "Oczywiście, że odpłynął. Musisz mniej pić w tawernach. Cały statek nie będzie czekał na jednego pijanego marynarza.";
			link.l1.go = "NA_SailorShip_2";
		break;
		
		case "NA_SailorShip_2":
			dialog.text = "Ale ja... hic!... nie jestem pijany... prawie... może...";
			link.l1 = "Ach, tak, rzeczywiście. Powodzenia.";
			link.l1.go = "NA_SailorShip_3";
		break;
		
		case "NA_SailorShip_3":
			dialog.text = "Poczekaj, k-kapitanie! Z-zabierz mnie... hic!.. na swój o-okret! Nie będę... hic!.. p-pić więcej...";
			if(GetFreeCrewQuantity(pchar) > 0)
			{
				link.l1 = "Dobrze, co możesz na to poradzić. Ale natychmiast na statek. A nie daj Bóg, zobaczę cię gdzieś pijanego, będziesz szorować pokład aż do następnego postoju w porcie.";
				link.l1.go = "NA_SailorShip_4";
			}
			link.l2 = "Żebym to ja płacił, a ty się upijasz i potem szukam cię po wszystkich tawernach i zaułkach kolonii? Nie, nie potrzebuję takiego szczęścia.";
			link.l2.go = "NA_SailorShip_6";
			
		break; 
		
		case "NA_SailorShip_4": 
			AddCharacterCrew(pchar, 1);
			dialog.text = "Tak, k-kapitanie!.. hik!..";
			link.l1 = "... ";
			link.l1.go = "NA_SailorShip_5";
		break;
		
		case "NA_SailorShip_5": 
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "NightAdventure_OpenLoc", 5.0); // побежит вдохновленный 
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		case "NA_SailorShip_6": 
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload4_back");
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "NightAdventure_OpenLoc", -1);
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// пьяные наезды
		case "NightAdventure_Bull":
			switch (rand(5))
			{
				case 0:
				dialog.text = "Kapitanie?.. hik!.. Ty jesteś... szczur lądowy... hik!.. nie kapitan!..";
				link.l1 = "Setki takich jak ty ciąłem w abordażowych walkach, więc wynoś się, pijaku.";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 1:
				dialog.text = "Kapitanie... hic!.. K-kapitanie tego koryta w rajdzie?.. hic!..";
				link.l1 = "Jeśli ujrzysz tę koryto na horyzoncie, będąc na morzu, lepiej od razu zanurkuj do wody: z rekinami masz większe szanse na przeżycie niż przeciw mojemu statkowi. A teraz zmykaj!";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 2:
				dialog.text = "Kapitanie?.. czk!.. Jesteś mlecznym pijakiem, nie kapitanem!.. Twoja m-matka była jeszcze dziewczynką... czk!.. kiedy ja żeglowałem po morzu...";
				link.l1 = "Lecz twoja matka zapewne ucieszyłaby się, wiedząc, że taki chłopczyk jak ja został kapitanem, a ty pozostałeś pijanym marynarzem, nadającym się tylko do szorowania pokładu.";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 3:
				dialog.text = "Kapitanie?.. Uważaj... hik!.. kapitanie... wybiję ci zęby... hik!.. nie zdążysz mrugnąć!..";
				link.l1 = "Odrzut zabije. Wynoś się! Wybij mi zęby, jeśli śmiesz...";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 4:
				dialog.text = "Kapitanie?.. Wygląda na... hic!.. j-jakiegoś obdartusa...";
				link.l1 = "Wygląda na to, że jeszcze nie spojrzałeś w lustro...";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 5:
				dialog.text = "K-kapitanie?.. Nie zgodziłbym się... hik!.. nawet służyć... na twoim statku... hik!..";
				link.l1 = "I nikt cię nie zapraszał na mój statek, żebyś się zgodził. Zejdź mi z drogi.";
				link.l1.go = "NightAdventure_End";
				break;
			}
		break;
		
		case "NightAdventure_End":
			DialogExit();
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			NPChar.Dialog.currentnode = "NightAdventure_Again";
		break;
		
		case "NightAdventure_Again":
			NextDiag.TempNode = "NightAdventure_Again";
			dialog.text = "Hik!..";
			link.l1 = "Idź spać.";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_SailorAgain":
			dialog.text = "Hic!.. Tak... jeszcze daleko?..";
			link.l1 = "Jesteśmy blisko, bądź cierpliwy.";
			link.l1.go = "exit";
			NextDiag.TempNode = "NightAdventure_SailorAgain";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
		break;
		// <-- матрос
		// горожанин -->
		case "NightAdventure_Citizen":
			LAi_RemoveLoginTime(npchar);
			dialog.text = "K-kim... hic!.. jesteś?..";
			link.l1 = "Jestem kapitanem "+GetFullName(pchar)+".";
			if (pchar.id == "Knippel")
			{
				link.l1 = "Przepraszam, kumplu, śpieszę się.";
				link.l1.go = "exit";
				LAi_CharacterDisableDialog(npchar);
				break;
			}
			switch(pchar.GenQuest.NightAdventureVar)
			{
				case "NightAdventure_CitizenHomie":          link.l1.go = "NightAdventure_Citizen_1_1"; break; // выручить приятеля
				case "NightAdventure_CitizenHomieSolderNM":  link.l1.go = "NightAdventure_Citizen_1_1"; break; 
				case "NightAdventure_CitizenHomieSolderGM":  link.l1.go = "NightAdventure_Citizen_1_1"; break;
				case "NightAdventure_CitizenHomieOfficer":   link.l1.go = "NightAdventure_Citizen_1_1"; break; 
				case "NightAdventure_SailorShuler0":         link.l1.go = "NightAdventure_Sailor_2_1";  break; // шулер
				case "NightAdventure_SailorShulerGiveMoney": link.l1.go = "NightAdventure_Sailor_2_1";  break;
				case "NightAdventure_SailorShulerGiveOk":    link.l1.go = "NightAdventure_Sailor_2_1";  break; 
				case "NightAdventure_SailorShulerFight":     link.l1.go = "NightAdventure_Sailor_2_1";  break; 
				case "NightAdventure_Bull":                  link.l1.go = "NightAdventure_Bull";        break;// наезд
			}
		break;
		
		// дружок
		case "NightAdventure_Citizen_1_1":
			dialog.text = "Kapitanie?.. hik!.. K-kapitanie... pomóż mi! Ja... mam na myśli... hik!.. mój przyjaciel... naprawdę potrzebuje twojej p-pomocy! Proszę.";
			link.l1 = "Nie zamierzam rozwiązywać problemów każdego pijaka, którego spotkam w środku nocy..";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Dobrze, powiedz mi, co się stało z twoim przyjacielem tam.";
			link.l2.go = "NightAdventure_Citizen_1_2";
		break;
		
		case "NightAdventure_Citizen_1_2":
			dialog.text = "Mój przyjaciel... on, ogólnie... upił się. Po prostu ogólnie... czkawka! ... upił się...";
			link.l1 = "Oczywiście, wytrzeźwiłem marynarzy, którzy pili na służbie, ale dość radykalnymi metodami. Nie sądzę, żeby twój przyjaciel tego potrzebował.";
			link.l1.go = "NightAdventure_Citizen_1_3";
		break;
		
		case "NightAdventure_Citizen_1_3":
			dialog.text = "Nie! On... on jest z g-gwardią! On arrr...gumentował z nim. I wdał się w bójkę. I on... hic!.. został zabrany do więzienia... on jest po prostu p-pijany!";
			link.l1 = "A czego teraz ode mnie chcesz? Sam jest sobie winien: trzeba mniej pić. Albo przynajmniej nie szukać przygód na własną rękę...";
			link.l1.go = "NightAdventure_Citizen_1_4";
		break;
		
		case "NightAdventure_Citizen_1_4":
			dialog.text = "Porozmawiaj z klawiszem, kap... hik! .. kapitanie! On go puści... puści go! Hmm... oto jest... hik!.. jakie masz szczęście... Mój przyjaciel właśnie... się sprzeczał... cóż... i chciał mnie walnąć w twarz... ale... hik!.. nie miał broni...";
			link.l1 = "Teraz nie mam nic innego do roboty, oprócz wyciągania pijaków z więzienia w nocy, którzy pobili się ze strażnikami. Nie, niech posiedzi kilka dni. Może następnym razem się nad tym zastanowisz.";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Aj, do diabła z tobą. Dobrze, porozmawiam z naczelnikiem.";
			link.l2.go = "NightAdventure_Citizen_1_5";
			if(GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && !CheckNationLicence(HOLLAND))
			{
				link.l2 = "Nie jestem pewien, czy strażnikowi spodoba się mój akcent. Po prostu zgłosi to później gubernatorowi. Więc idźcie bez mnie.";
				link.l2.go = "NightAdventure_Citizen_RE";
			}
			if(ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -15)
			{
				link.l2 = "Obawiam się, przyjacielu, że droga do lokalnych kazamat jest dla mnie zablokowana. Strażnik trzyma mój portret niczym ikonę, a ja nie zamierzam osiedlać się w tych ich gościnnych apartamentach. Więc przykro mi, ale nie mogę ci pomóc.";
				link.l2.go = "NightAdventure_Citizen_NR";
			}
		break;
		
		case "NightAdventure_Citizen_1_5":
			DialogExit();
			pchar.GenQuest.NightAdventureToJail = true;
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			chrDisableReloadToLocation = true; //закрыть локацию пока бежит
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0); 
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		case "NightAdventure_CitizenHomiePresent":
			dialog.text = "D-dziękuję... kapitanie. I za mojego p-przyjaciela również. T-tutaj... to dla ciebie.";
			link.l1 = "Następnym razem, miej oko na swojego przyjaciela, kiedy się upije i postanowi walczyć ze strażnikami. Nie każdej nocy kapitanowie spacerują po ulicach, gotowi negocjować z dozorcem za jakichś pijaków. Powodzenia.";
			link.l1.go = "NightAdventure_CitizenHomiePresent_1";
		break;
		
		case "NightAdventure_CitizenHomiePresent_1":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 5.0);
			sld = characterFromId("NightAdventure_Homie");
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			if(GetDataDay() < 7) 						{GiveItem2Character(pchar, "indian_2");  Log_Info("You've received amulet 'Gunpowder tester'");}
			if(GetDataDay() >= 7  && GetDataDay() < 13) {GiveItem2Character(pchar, "obereg_5");  Log_Info("You've received amulet 'Jade turtle'");}
			if(GetDataDay() >= 13 && GetDataDay() < 19) {GiveItem2Character(pchar, "obereg_6");  Log_Info("You've received amulet 'Monkey's fist'");}
			if(GetDataDay() >= 19 && GetDataDay() < 25) {GiveItem2Character(pchar, "obereg_8");  Log_Info("You've received amulet 'Merchant's beads'");}
			if(GetDataDay() == 25) 		    			{GiveItem2Character(pchar, "indian_9");  Log_Info("You've received amulet 'Baldo'");}
			if(GetDataDay() == 26) 	    				{GiveItem2Character(pchar, "obereg_11"); Log_Info("You've received amulet 'Pilgrim'");}
			if(GetDataDay() >= 27 && GetDataDay() < 31) {GiveItem2Character(pchar, "obereg_4");  Log_Info("You've received amulet 'Gypsy's fan'");}
			if(GetDataDay() == 31) 	    				{GiveItem2Character(pchar, "amulet_11"); Log_Info("You've received amulet 'Cimaruta'");}
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		case "NightAdventure_Citizen_RE":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) + GetSummonSkillFromName(pchar, SKILL_FORTUNE)  < (rand(100)+rand(100)))
			{
				dialog.text = "Oh!.. Więc wiem jak... hik!.. uwolnić mojego... p-przyjaciela... hik!.. Straże! Szpieg w mieście!.. hik!..";
				link.l1 = "Wybrałeś bardzo złą opcję, aby uwolnić swojego przyjaciela.";
				link.l1.go = "NightAdventure_Fight";
			}
			else
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
				AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 100);
				dialog.text = "Ach, c-cudzoziemcze... czk! .. Ty... będziesz miał problemy... czk! .. Dobrze... Mam tutaj... czk! .. wszystko pod kontrolą.";
				link.l1 = "Oczywiście. Jeśli coś się wydarzy, przyjdę do ciebie od razu.";
				link.l1.go = "NightAdventure_End";
			}
		break;
		
		case "NightAdventure_Citizen_NR":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) + GetSummonSkillFromName(pchar, SKILL_FORTUNE) < (rand(100)+rand(100)))
			{
				dialog.text = "Ah ... więc ty ... hic! .. Jesteś przestępcą! Strażnicy!";
				link.l1 = "Ach, więc tak teraz gadasz!";
				link.l1.go = "NightAdventure_Fight";
			}
			else
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
				AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 100);
				dialog.text = "O, jakże... hic! .. przepraszam. A co jeśli... pozwolisz mi... negocjować za ciebie z... hic!.. strażnikiem, a ty... hic!.. za m-moim przyjacielem?..";
				link.l1 = "Nie, nie musisz negocjować za mnie, dzięki. Powodzenia.";
				link.l1.go = "NightAdventure_End";
			}
		break;
		
		case "NightAdventure_Fight":
			DialogExit();
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			LAi_group_Attack(NPChar, Pchar);
		break;
		// контрабандист 
		case "NightAdventure_Pirate": 
			LAi_RemoveLoginTime(npchar);
			dialog.text = "K-kim... hic!.. jesteś?...";
			link.l1 = "Jestem kapitanem "+GetFullName(pchar)+".";
			if (pchar.id == "Knippel")
			{
				link.l1 = "Przepraszam, kumplu, śpieszę się.";
				link.l1.go = "exit";
				LAi_CharacterDisableDialog(npchar);
				break;
			}
			switch(pchar.GenQuest.NightAdventureVar)
			{
				case "NightAdventure_Bull":          		 link.l1.go = "NightAdventure_Bull";       break; // пьяные наезды
				case "NightAdventure_PiratePeace":           link.l1.go = "NightAdventure_PirateCave"; break; // до пещеры
				case "NightAdventure_PirateBad":             link.l1.go = "NightAdventure_PirateCave"; break;
			}
		break;
		
		case "NightAdventure_PirateCave":
			dialog.text = "K-kapitanie?.. hik!.. K-kapitanie... posłuchaj, eskortuj mnie do jaskini blisko miasta... hik!.. co? P-proszę.";
			link.l1 = "Do jaskini? Nie rozumiem. Dlaczego idziesz do jaskini? I dlaczego ja ci jestem potrzebny?";
			link.l1.go = "NightAdventure_PirateCave_1";
		break;
		
		case "NightAdventure_PirateCave_1":
			dialog.text = "Widzisz... k-kapitanie... hik!.. Skończyły mi się p-pieniądze na trunki... A w... hik!.. w jaskini mam... skrytkę, więc... hik!.. Ale ja... boję się iść sam przez dż... dż... dżunglę... hik!.. w nocy... Więc...";
			link.l1 = "Odejdź ode mnie, nie mam czasu!";
			link.l1.go = "NightAdventure_End";
			link.l2 = "Dobrze, chodźmy. Wygląda na to, że sam nie potrafisz tam dotrzeć";
			link.l2.go = "NightAdventure_PirateCave_2";
		break;
		
		case "NightAdventure_PirateCave_2":
			dialog.text = "Po-prostu... hic!.. powoooli, p-proszę. Nie jestem... hic!.. w stanie... ustać...";
			link.l1 = "Dobrze, idźmy powoli.";
			link.l1.go = "NightAdventure_PirateCave_3";
		break;
		
		case "NightAdventure_PirateCave_3":
			DialogExit();
			NPChar.Dialog.currentnode = "NightAdventure_SailorAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventureNode = true; // что взяли квест
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			string NAIsland = GetIslandByCityName(npchar.city);
			string NACave = "absent. Tell belamour that you are";
			// найти пещеру на острове
			i = Findlocation(NAIsland+"_Grot");
			if(i != -1) NACave = NAIsland+"_Grot";
			i = Findlocation(NAIsland+"_Cave");
			if(i != -1) NACave = NAIsland+"_Cave";
			// для мейна и капстервиля
			i = Findlocation(npchar.city+"_Cave");
			if(i != -1) NACave = npchar.city+"_Cave";
			i = Findlocation(npchar.city+"_Grot");
			if(i != -1) NACave = npchar.city+"_Grot";
			
			log_testinfo("Cave "+NACave+" on the island " +NAIsland);
			SetFunctionLocationCondition("NightAdventure_InCave", NACave, false);
			SetFunctionLocationCondition("NightAdventure_InFort", npchar.city+"_ammo", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		case "NightAdventure_PirateCave_4": // диалог в пищере
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_PiratePeace")
			{
				AddMoneyToCharacter(pchar, 1000);
				TakeNItems(pchar, "potionrum", 1);   
				TakeNItems(pchar, "potionwine", 1);
				PlaySound("interface\important_item.wav");
				Log_Info("You've received an alcohol")
				dialog.text = "K-kapitanie... hic!.. wielkie dzięki... pomogłeś mi! Ja... oto... hic!.. To dla ciebie.";
				link.l1 = "Chodź, ugh... nieważne... Nie pij już tak więcej.";
				link.l1.go = "NightAdventure_PirateCave_4_1";
				break;
			} 
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_PirateBad")
			{
				dialog.text = "Świetnie, kapitanie! Cieszę się, że się zgodziłeś.";
				link.l1 = "Cóż, gdzie jest twój skarb? Poczekaj chwilę, wydaje się, że nie jesteś pijany.";
				link.l1.go = "NightAdventure_PirateCave_5";
				break;
			} 
		break;
		
		case "NightAdventure_PirateCave_4_1": // мирный исход
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 5.0); 
			SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
		break;
		
		case "NightAdventure_PirateCave_5": // драка
			dialog.text = "Tak, nie piłem dużo, nie martw się o mnie. A co do skrytki... Chłopaki!";
			link.l1 = "... ";
			link.l1.go = "NightAdventure_PirateCave_6";
		break;
		
		case "NightAdventure_PirateCave_6": 
			DialogExit();
			AddDialogExitQuestFunction("NightAdventure_PiratesInCave");
		break;
		
		case "NightAdventure_PirateCave_7": 
			dialog.text = "Chłopaki, przyniosłem tu skarb. Trzeba go otworzyć. O ile, oczywiście, ten skarb sam się nie otworzy, w dobry sposób. Kapitanie, co myślisz?";
			link.l1 = LinkRandPhrase(" Myślę, że lepiej by było, gdybyś upił się do utraty pamięci. Przynajmniej byś przeżył. A teraz jest tylko jedna droga... "," Myślę, że wcale nie jesteś zbyt mądry, skoro zdecydowałeś się obrabować kapitana okrętu wojennego ... "," Myślę, że chyba jesteś zmęczony życiem, skoro postanowiłeś spróbować tego...");
			link.l1.go = "NightAdventure_PirateCave_8F";
			link.l2 = "Dobrze, chyba najlepiej rozstać się w dobry sposób. A ile potrzebujesz?";
			link.l2.go = "NightAdventure_PirateCave_8A";
		break;
		
		case "NightAdventure_PirateCave_8F": 
			dialog.text = "Więc, w dobry sposób nie otworzymy skrytki?";
			link.l1 = "Obawiam się, że to był ostatni zapas w twoim życiu.";
			link.l1.go = "NightAdventure_PirateCave_9F";
		break;
		
		case "NightAdventure_PirateCave_9F": 
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешить драться
			sld = CharacterFromID(pchar.GenQuest.NightAdventureId);
			sld.SaveItemsForDead   = true; // сохранять на трупе вещи
			sld.DontClearDead = true;  // не убирать труп через 200с
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			for(i=0 ; i < 3; i++)
			{
				sld = CharacterFromID("NAPirat_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			LAi_SetFightMode(pchar, true);
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		case "NightAdventure_PirateCave_8A": // испугался
			iMoney = sti(pchar.money)/3;
			dialog.text = "O, nie jesteśmy chciwi. Tylko "+FindRussianMoneyString(iMoney)+"."; 
			link.l1 = "Obawiam się, że to był twój ostatni skarb w życiu.";
			link.l1.go = "NightAdventure_PirateCave_9F";
			link.l2 = "Dobrze, niech będzie po twojemu. Nigdy więcej nie pomogę pijakowi...";
			link.l2.go = "NightAdventure_PirateCave_9A";
		break;
		
		case "NightAdventure_PirateCave_9A": 
			DialogExit();
			NPChar.Dialog.currentnode = "NightAdventure_PirateCaveAgain";
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false); 
			iMoney = sti(pchar.money)/3;
			AddMoneyToCharacter(pchar, -iMoney);
			AddMoneyToCharacter(npchar, iMoney);
			npchar.SaveItemsForDead   = true; // сохранять на трупе вещи
			npchar.DontClearDead = true;  // не убирать труп через 200с
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешить драться
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for(i=0 ; i < 3; i++)
			{
				sld = CharacterFromID("NAPirat_" + i);
				sld.dialog.currentnode = "NightAdventure_PirateCaveAgain";
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_Group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
		break;
		
		case "NightAdventure_PirateCaveAgain": 
			dialog.text = "Kapitanie, zaskakujesz mnie swoją hojnością. Czy chcesz podzielić się z nami jeszcze czymś?";
			link.l1 = "Już dałem ci wszystko. Odchodzę...";
			link.l1.go = "exit";
			NextDiag.TempNode = "NightAdventure_PirateCaveAgain";
		break;
		
		// дворянин -->
		case "NightAdventure_Noble":
			LAi_RemoveLoginTime(npchar);
			dialog.text = "K-kim... hic!.. jesteś?...";
			link.l1 = "Jestem kapitanem "+GetFullName(pchar)+".";
			if (pchar.id == "Knippel")
			{
				link.l1 = "Przepraszam, kumplu, śpieszę się.";
				link.l1.go = "exit";
				LAi_CharacterDisableDialog(npchar);
				break;
			}
			switch(pchar.GenQuest.NightAdventureVar)
			{
				case "NightAdventure_NobleGame":             link.l1.go = "NightAdventure_NobleGame";  break; // карты
				case "NightAdventure_NobleGameDuel":         link.l1.go = "NightAdventure_NobleGame";  break; 
				case "NightAdventure_NobleWhore": 			 link.l1.go = "NightAdventure_NobleWhore"; break; // жрица
			}
		break;
		// карты
		case "NightAdventure_NobleGame": 
			dialog.text = "Kapitanie?.. hic!.. och, "+GetAddress_Form(NPChar)+" ... Przepraszam... hik!.. za mój... s-stan. Chcesz dołączyć do mnie? hik!.. P-proszę."; 
			link.l1 = "Przepraszam, "+GetAddress_Form(NPChar)+", ale jestem zajęty."; 
			link.l1.go = "NightAdventure_NobleEnd";
			link.l2 = "Dołączyć? Przepraszam, ale dzisiaj nie piję..."; 
			link.l2.go = "NightAdventure_NobleGame_1";
		break;
		
		case "NightAdventure_NobleGame_1":
			dialog.text = "Och, nie musisz... hic!.. pić! Rzecz w tym... No... Wypiłem z przyjacielem... Więc... już jestem wstawiony... widzisz?";
			link.l1 = "Zatem, potrzebujesz pomocy, by wytrzeźwieć?";
			link.l1.go = "NightAdventure_NobleGame_2";
		break;
		
		case "NightAdventure_NobleGame_2": 
			dialog.text = "Nie bardzo! Jestem w porządku. Teraz chcę z-zagrać... w karty, ogólnie chcę zagrać... czkawka!.. A-le nie za nędzne... p-pesos... z tymi obdartusami w... czkawka!.. t-tawernie... Ale z prawdziwym szlachcicem! czkawka!.. Na prawdziwe stawki!.."; 
			link.l1 = "Przepraszam, "+GetAddress_Form(NPChar)+", co mogę powiedzieć... Nie jestem fanem hazardu. Trzeba płacić pensje marynarzom, utrzymywać statek, wiesz..."; 
			link.l1.go = "NightAdventure_NobleEnd";
			link.l2 = "Hmm, dobrze, zagrajmy. Czy pójdziemy do tawerny?"; 
			link.l2.go = "NightAdventure_NobleGame_3";
		break;
		
		case "NightAdventure_NobleGame_3": 
			dialog.text = "Doobrze! Tylko... czkawka!.. pooowoli, p-proszę. Ja... czkawka!.. nie... mogę... stać..."; 
			link.l1 = "Dobrze, idźmy powoli."; 
			link.l1.go = "NightAdventure_NobleGame_4";
		break;
		
		case "NightAdventure_NobleGame_4":
			DialogExit();
			NPChar.Dialog.currentnode = "NightAdventure_NobleTownAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventureNode =  "NightAdventure_NobleGame_5"; // для выбора диалога
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocationCondition("NightAdventure_Intavern", npchar.City+"_tavern", true);
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		case "NightAdventure_NobleGame_5": 
			pchar.quest.NightAdventure_Intavern.over = "yes";
			FreeSitLocator(pchar.location, "sit_front4");
			FreeSitLocator(pchar.location, "sit_base4");
			dialog.text = "D-dla tego stołu... hic!.. chodźmy!"; 
			link.l1 = "Dobrze, chodźmy."; 
			link.l1.go = "NightAdventure_NobleGame_6";
		break;
		
		case "NightAdventure_NobleGame_6": 
			DialogExit();
			//if(CheckAttribute(pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
			LAi_Fade("NightAdventure_NobleGameDialogPrep", "NightAdventure_NobleGameDialog");
		break;
		
		case "NightAdventure_NobleGame_7": 
			dialog.text = "Nie masz... pojęcia, k-kapitanie, jak... hic!.. jak się cieszę, że spotykam prawdziwego szlachcica! hic!.. W tym pustkowiu... zazwyczaj tylko... hic!.. m-menda..."; 
			link.l1 = "Tak, jest to na pęczki w lokalnych koloniach. No cóż, zagramy?"; 
			link.l1.go = "NightAdventure_NobleGame_8";
		break;
		
		case "NightAdventure_NobleGame_8": 
			dialog.text = "Tak, zagrajmy! hik!.. Jakie zakłady?.."; 
			if(sti(pchar.money) > 10000)
			{
				link.l1 = "Gramy za 1000 pesos."; 
				link.l1.go = "NightAdventure_NobleGame_9_1";
			}
			if(sti(pchar.money) > 20000)
			{
				link.l2 = "Gramy za 2000 pesos."; 
				link.l2.go = "NightAdventure_NobleGame_9_2";
			}
			link.l3 = "Hmm, przykro mi, wydaje się, że moja kieszeń jest chwilowo pusta..."; 
			link.l3.go = "NightAdventure_NobleGame_Голодранец";
		break;
		
		case "NightAdventure_NobleGame_Голодранец": 
			dialog.text = "W-co?.. Nie masz... hic!.. pieniędzy, żeby grać... ze mną?.."; 
			link.l1 = "Cóż, zdarza się. Zagramy następnym razem, nie martw się."; 
			link.l1.go = "NightAdventure_NobleGame_Голодранец_1";
		break;
		
		case "NightAdventure_NobleGame_Голодранец_1": 
			DialogExit();
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			chrDisableReloadToLocation = false; // открыть локацию
			LAI_SetPlayerType(pchar);           
			DoQuestReloadToLocation(pchar.location, "tables", "stay4", "");
			ChangeCharacterAddressGroup(npchar, "none", "", "");
		break;
		
		case "NightAdventure_NobleGame_9_1": 
			DialogExit();
			npchar.money = 15000;
			pchar.questTemp.NA.Cards = true; 
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
			pchar.GenQuest.Cards.iRate     = 1000; 
			LaunchCardsGame();
		break;
		
		case "NightAdventure_NobleGame_9_2": 
			DialogExit();
			npchar.money = 30000;
			pchar.questTemp.NA.Cards = true; 
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
			pchar.GenQuest.Cards.iRate     = 2000; 
			LaunchCardsGame();
		break;
		
		case "NightAdventure_NobleGame_Win": 
			DeleteAttribute(pchar, "questTemp.NA.Cards.Win");
			dialog.text = "Hic!.. Świetnie się bawiłem, k-kapitanie! hic!.."; 
			link.l1 = "Zgadzam się z tobą. Przynajmniej odpocznij od interesów."; 
			link.l1.go = "NightAdventure_NobleGame_HappyEnd";
		break;
		
		case "NightAdventure_NobleGame_Lose": 
			DeleteAttribute(pchar, "questTemp.NA.Cards.Fail");
			dialog.text = "Hic!.. Świetnie się bawiłem, k-kapitanie! hic!.."; 
			link.l1 = "Zgadzam się z tobą. Przynajmniej zrób sobie przerwę od interesów."; 
			link.l1.go = "NightAdventure_NobleGame_Lose_1";
		break;
		
		case "NightAdventure_NobleGame_Lose_1": 
			dialog.text = "Czasami po prostu musisz... hick!.. s-spędzić czas z miłym... hick!.. towarzystwem. Dziękuję bardzo... hick!.. za twoje towarzystwo!"; 
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_NobleGameDuel")
			{		
				link.l1 = "Tak, właśnie przegrałem w drobny mak. I jak to się stało, że wygrałeś nawet wtedy, gdy miałem wszelkie szanse na zwycięstwo?"; 
				link.l1.go = "NightAdventure_NobleGame_Duel";
				break;
			}	
			link.l1 = "Wzajemnie, dziękuję za grę i rozmowę."; 
			link.l1.go = "NightAdventure_NobleGame_HappyEnd_1";
		break;
		
		case "NightAdventure_NobleGame_HappyEnd": 
			dialog.text = "Czasem po prostu trzeba... hik!.. s-spędzić czas w miłym... hik!.. towarzystwie. Bardzo ci dziękuję... hik!.. za twoje towarzystwo!"; 
			link.l1 = "Wzajemnie, dziękuję za grę i za rozmowę."; 
			link.l1.go = "NightAdventure_NobleGame_HappyEnd_1";
		break;
		
		case "NightAdventure_NobleGame_HappyEnd_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.NA.Cards");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			chrDisableReloadToLocation = false; // открыть локацию
			LAI_SetPlayerType(pchar);           
			DoQuestReloadToLocation(pchar.location, "tables", "stay4", "");
			ChangeCharacterAddressGroup(npchar, "none", "", "");
		break;
		
		case "NightAdventure_NobleGame_Duel": 
			dialog.text = "Po prostu szczęście, k-kapitanie... hic!.."; 
			link.l1 = "To nie wygląda na zwykłe szczęście...."; 
			link.l1.go = "NightAdventure_NobleGame_Duel_1";
		break;
		
		case "NightAdventure_NobleGame_Duel_1": 
			dialog.text = "Na co insynuujesz? Chcesz powiedzieć, że grałem nieuczciwie? Sam widziałeś wszystko, braliśmy karty z tej samej talii!"; 
			link.l1 = "Tak, widziałem. I widziałem też, że minutę temu twój język ledwo się ruszał, a teraz mówisz, jakbyś nie był pijany."; 
			link.l1.go = "NightAdventure_NobleGame_Duel_2";
		break;
		
		case "NightAdventure_NobleGame_Duel_2": 
			dialog.text = "Ach, cholera! A dobrze mnie złapałeś! Dobra, przyznaję, nie będę się ukrywał. Nie byłem pijany. Ale czy wiesz, jak dobrze ludzie wpadają na tych rzekomo bogatych i pijanych, którzy chcą grać w karty? Każdy, kto ma coś do postawienia, prawie jako pierwszy biegnie do tawerny, aby szybko zdobyć niewątpliwie dużą wygraną od niewątpliwie bogatego, ale pijanego szlachcica. Pozwól, że powiem, że jesteś pierwszym, który dotarł do mojego sedna."; 
			link.l1 = "A więc, co teraz? Oddasz mi moje pieniądze po dobroci?"; 
			link.l1.go = "NightAdventure_NobleGame_Duel_3";
		break;
		
		case "NightAdventure_NobleGame_Duel_3": 
			dialog.text = "Ha ha ha, nie rozśmieszaj mnie, kapitanie. Oczywiście, że niczego ci nie zwrócę! I nie myśl, że możesz mnie do tego zmusić. Mogę łatwo udawać szanowanego szlachcica, na którego krzywo patrzy jakiś włóczęga kapitan. Moja rada dla ciebie: zaakceptuj swoją porażkę i po prostu odejdź."; 
			link.l1 = "Cóż, szczerze życzę ci, abyś nie wpadł na mnie w mniej sprzyjających okolicznościach, bo wtedy już się tak nie pośmiejesz. Do widzenia."; 
			link.l1.go = "NightAdventure_NobleGame_HappyEnd_1";
			link.l2 = "I moja rada dla ciebie, postaraj się znaleźć czas na zdobycie miecza."; 
			link.l2.go = "NightAdventure_NobleGame_Duel_4";
		break;
		
		case "NightAdventure_NobleGame_Duel_4": 
			dialog.text = "Nie odważyłbyś się... To karczma, pełna ludzi..."; 
			link.l1 = "Więc jestem tylko bezpańskim kapitanem, co mnie obchodzą zasady przyzwoitości. A w porcie, w tawernie nocą, co się może stać... Władam mieczem na wszelkie sposoby lepiej niż ty."; 
			link.l1.go = "NightAdventure_NobleGame_Duel_5";
		break;
		
		case "NightAdventure_NobleGame_Duel_5": 
			dialog.text = "Ach, więc tak to jest?! Cóż, teraz sprawdzimy, kto lepiej tym włada!"; 
			link.l1 = "Do usług..."; 
			link.l1.go = "NightAdventure_NobleGame_Duel_6";
		break;
		
		case "NightAdventure_NobleGame_Duel_6": 
			DeleteAttribute(pchar, "questTemp.NA.Cards");
			SetFunctionLocationCondition("NightAdventure_KillPhant", NPChar.City+"_town", false);
			npchar.money = 0;
			AddMoneyToCharacter(npchar, makeint(pchar.GenQuest.NightAdventure_money));
			GiveItem2Character(npchar, "totem_13");
			npchar.SaveItemsForDead   = true; // сохранять на трупе вещи
			npchar.DontClearDead = true;  // не убирать труп через 200с
			chrDisableReloadToLocation = false; // открыть локацию
			PChar.questTemp.duel.enemy = NPChar.id;
			AddDialogExitQuestFunction("Duel_Prepare_Fight");
			DialogExit();
		break;
		// жрица
		case "NightAdventure_NobleWhore": 
			dialog.text = "Kapitanie?.. hik!.. och, "+GetAddress_Form(NPChar)+" ... p-przepraszam... czk! .. za moją... k-kondycję. Czy możesz mi p-pomóc? czk!.. P-proszę."; 
			link.l1 = "Przepraszam, "+GetAddress_Form(NPChar)+", ale jestem zajęty."; 
			link.l1.go = "NightAdventure_NobleEnd";
			link.l2 = "Och... słucham."; 
			link.l2.go = "NightAdventure_NobleWhore_1";
		break;
		
		case "NightAdventure_NobleWhore_1": 
			dialog.text = "To taka rzecz... W ogóle... Jestem... już podpity... Widać... hic!.. tak?"; 
			link.l1 = "Szczerze mówiąc, tak. Potrzebujesz pomocy, by wytrzeźwieć?"; 
			link.l1.go = "NightAdventure_NobleWhore_2";
		break;
		
		case "NightAdventure_NobleWhore_2": 
			dialog.text = "Nie bardzo! Jestem... dobry. Chcę damę. Ale jestem tak pijany... hic!.. M-madame mnie wyrzuci, więc. Czy mógłbyś... hic!... p-ponegocjować za mnie? Dam pieniądze."; 
			link.l1 = "Przykro mi, "+GetAddress_Form(NPChar)+", ale jak ci to powiedzieć... Nie chodzę do burdeli. Honor, reputacja... wiesz ..."; 
			link.l1.go = "NightAdventure_NobleEnd";
			link.l2 = "Och, dobrze, pomogę ci."; 
			link.l2.go = "NightAdventure_NobleWhore_3";
		break;
		
		case "NightAdventure_NobleWhore_3": 
			dialog.text = "Po prostu... hik!.. powoooli, p-proszę. Nie jestem... hik!.. w stanie... stać..."; 
			link.l1 = "Dobrze, idźmy powoli."; 
			link.l1.go = "NightAdventure_NobleWhore_4";
		break;
		
		case "NightAdventure_NobleWhore_4":
			DialogExit();
			if(npchar.city != "Charles" || npchar.city != "Tortuga") // вход только с парадного
			{
				LocatorReloadEnterDisable(npchar.city+"_town", "reload91", true);
			}
			NPChar.Dialog.currentnode = "NightAdventure_NobleTownAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventure_money = 3000+(rand(4)*500);
			pchar.GenQuest.NightAdventureNode =  "NightAdventure_NobleWhore_5"; // для выбора диалога
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocationCondition("NightAdventure_InBrothel", npchar.City+"_Brothel", false);
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		case "NightAdventure_NobleWhore_5": 
			pchar.GenQuest.NightAdventureVar = "NightAdventure_NobleWhoreMoney";
			AddMoneyToCharacter(pchar, 5000);
			dialog.text = "Oto pieniądze... hik!... Będę czekał na ciebie t-tutaj."; 
			link.l1 = "Dobrze, wkrótce wrócę."; 
			link.l1.go = "NightAdventure_NobleWhore_6";
		break;
		
		case "NightAdventure_NobleWhore_6": 
			LAi_SetCitizenType(npchar);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable(npchar.city + "_Brothel", "reload1_back", true); 
			LocatorReloadEnterDisable(npchar.city + "_SecBrRoom", "reload2", true); 
			NPChar.Dialog.currentnode = "NightAdventure_NobleBrothelAgain";
			dialog.text = "J-jedynie... przynieś mi... hic!.. najlepsze!.. Tak..."; 
			link.l1 = "Dobrze, w porządku, zrozumiałem."; 
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_NobleWhore_7": // заказ исполнен
			dialog.text = "Hip!.. Jak długo jeszcze?"; 
			link.l1 = "Najlepsza dziewczyna tej kolonii czeka na ciebie na górze."; 
			link.l1.go = "NightAdventure_NobleWhore_8";
		break;
		
		case "NightAdventure_NobleWhore_8": 
			dialog.text = "Tak!.. Ten wieczór... jest wspaniały... D-dziękuję, "+GetAddress_Form(NPChar)+". Reszta pieniędzy... hic!... weź to. A ja tonę... w mojej... pięęęknej... la-lali...";
			link.l1 = "Dobrze się baw."; 
			link.l1.go = "NightAdventure_NobleWhore_9";
		break;
		
		case "NightAdventure_NobleWhore_9": 
			DialogExit();
			chrDisableReloadToLocation = true; // закрыть пока бежит
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "", "", "", "NightAdventure_OpenBrothel", -1);
		break;
		
		case "NightAdventure_NobleBrothelAgain":
			NextDiag.TempNode = "NightAdventure_NobleBrothelAgain";
			dialog.text = "Hic!.. Jak długo jeszcze?";
			link.l1 = "Wkrótce będę negocjować, bądź cierpliwy.";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_NobleEnd":
			DialogExit();
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			NPChar.Dialog.currentnode = "NightAdventure_NobleEndAgain";
		break;
		
		case "NightAdventure_NobleEndAgain":
			NextDiag.TempNode = "NightAdventure_NobleEndAgain";
			dialog.text = "Hic!..";
			link.l1 = "Musisz spać.";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_NobleTownAgain":
			dialog.text = "Hic!.. Tak... czy to jeszcze daleko?..";
			link.l1 = "Jesteśmy prawie na miejscu, bądź cierpliwy.";
			link.l1.go = "exit";
			NextDiag.TempNode = "NightAdventure_SailorAgain";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
		break;
		// <-- ночной приключенец
		
		// belamour квест на получение фонаря Xenon -->
		case "CemeteryMan":
			dialog.text = "Co? Kim jesteś? Co tu robisz?";
			link.l1 = "Mógłbym zapytać cię o to samo.";
			link.l1.go = "CemeteryMan_1";
		break;
		
		case "CemeteryMan_1":
			dialog.text = "My? Och, my... um... Zbieramy tu kwiaty...";
			link.l1 = "Kwiaty na groby? Cóż, jak się ma zielnik?";
			link.l1.go = "CemeteryMan_2";
		break;
		
		case "CemeteryMan_2":
			dialog.text = "Jej... Czy to ma związek z ziołami?";
			link.l1 = "Więc... Myślę, że rozumiem, co się tu dzieje.";
			link.l1.go = "CemeteryMan_3";
		break;
		
		case "CemeteryMan_3":
			dialog.text = "Nie jesteśmy maruderami! Nie mów o nas w ten sposób! Jesteśmy tylko...";
			link.l1 = "Co takiego?";
			link.l1.go = "CemeteryMan_4";
		break;
		
		case "CemeteryMan_4":
			dialog.text = "Cóż, my... Mój ojciec zabrania nam się spotykać! I jej ojciec także! Więc my... szukaliśmy miejsca bez świadków. Być samemu. Zamek w drzwiach i tak jest zepsuty, więc łatwo tu wejść...";
			link.l1 = "Widzę teraz, czym były te przerażające jęki niespokojnej duszy...";
			link.l1.go = "CemeteryMan_5";
		break;
		
		case "CemeteryMan_5":
			DialogExit();
			sld = characterFromId("CemeteryCouple_2");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		
		case "CemeteryMan_6":
			dialog.text = "Cóż, skoro wszystko rozgryzłeś, może zostawisz nas w spokoju?";
			link.l1 = "Nie boisz się umawiać na randki w krypcie? Niezbyt to najlepsze miejsce...";
			link.l1.go = "CemeteryMan_7";
		break;
		
		case "CemeteryMan_7":
			dialog.text = "Nie jesteśmy przesądni! A nawet gdyby to było straszne - jaki mamy wybór? W mieście rodzice od razu by się o tym dowiedzieli. Ale tutaj nikt nas nie wyda. Więc na razie to najlepsza opcja.";
			link.l1 = "Naprawdę przepraszam, ale czy mógłbyś poszukać innego miejsca? Nie zrozum mnie źle, rozumiem wszystko - młodość i te sprawy - ale twoje schadzki przestraszyły stróża cmentarza na śmierć z powodu wszystkich hałasów i jęków dochodzących z krypty każdej nocy.";
			link.l1.go = "CemeteryMan_8";
		break;
		
		case "CemeteryMan_8":
			dialog.text = "Cóż... Przerażenie strażnika nie było częścią naszego planu. Ale gdzież indziej możemy się spotkać? Czy sugerujesz, że mamy nasze randki pod otwartym niebem?";
			link.l1 = "Miłość nie zna granic. Znajdź inne miejsce, gdzie na pewno nikomu nie będziesz przeszkadzać. Wtedy nikt nie będzie ci przeszkadzał. Prawdopodobnie. I lepiej uporządkuj sprawy z rodzicami - nie planujesz się ukrywać wiecznie, prawda?";
			link.l1.go = "CemeteryMan_9";
		break;
		
		case "CemeteryMan_9":
			dialog.text = "Fine, we'll think of something... We won't be scaring the guard anymore; you have my word.";
			link.l1 = "Wspaniale. Powodzenia!";
			link.l1.go = "CemeteryMan_10";
		break;
		
		case "CemeteryMan_10":
			sld = characterFromId("CemeteryCouple_1");
			sld.lifeDay = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld = characterFromId("CemeteryCouple_2");
			sld.lifeDay = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
			pchar.questTemp.Lantern = "ToKeeper";
			DeleteAttribute(pchar,"questTemp.Lantern.nation");
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddQuestRecord("NoiseCemetery", "2");
			DialogExit();
		break;
		
		case "CemeteryGirl":
			dialog.text = "Co?!";
			link.l1 = "O, nic...";
			link.l1.go = "CemeteryGirl_1";
		break;
		
		case "CemeteryGirl_1":
			DialogExit();
			sld = characterFromId("CemeteryCouple_1");
			sld.dialog.currentnode = "CemeteryMan_6";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		// <-- квест на получение фонаря 

		//замечание по обнажённому оружию от персонажей типа citizen // лесник вставил в ген.квесты чтобы не было пустого диалога .
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Słuchaj, jestem obywatelem tego miasta i prosiłbym cię, byś schował swoją klingę.","Słuchaj, jestem obywatelem miasta i proszę cię, żebyś schował swój miecz.");
			link.l1 = LinkRandPhrase("Dobrze.","Jak sobie życzysz...","Jak powiadasz...");
			link.l1.go = "exit";
		break;																																																				  
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			break;
	}
}

void ChurchGenQuest2_GiveCup()
{
	AddItems(PChar, "Bible", 1);
	ref rItem = ItemsFromID("Bible");
	rItem.Name = "itmname_ChurchGenQuest2Cup"; // rItem.Name = "itmname_bible";
	rItem.City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen");
	rItem.Weight = 15.0; // rItem.Weight = 2;
	rItem.picIndex = 13; // itm.picIndex = 6;
	rItem.picTexture = "ITEMS_31"; // itm.picTexture = "ITEMS_9";
	ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest2Cup");
}

// Для генера "Пираты на необитаемом острове"
String PiratesOnUninhabited_GetStringNum(int _num)
{
	String retValue = "";
	
	switch(_num)
	{
		case 5: retValue = "five"; break;
		case 6: retValue = "six"; break;
		case 7: retValue = "seven"; break;
		case 8: retValue = "eight"; break;
		case 9: retValue = "nine"; break;
		case 10: retValue = "ten"; break;
	}
	
	return retValue;
}

int PiratesOnUninhabited_GenerateShipType()
{
	int rank = sti(PChar.rank);
	int retShipType;
	
	if(rank < 5)
	{
		switch(hrand(1))
		{
			case 0: retShipType = SHIP_LUGGER; break;
			case 1: retShipType = SHIP_SLOOP; break;
		}
	}
	
	if(rank >= 5 && rank < 20)
	{
		switch(hrand(3))
		{
			case 0: retShipType = SHIP_SLOOP; break;
			case 1: retShipType = SHIP_BRIGANTINE; break;
			case 2: retShipType = SHIP_SCHOONER_W; break;
			case 3: retShipType = SHIP_BRIG; break;
		}
	}
	
	if(rank >= 20)
	{
		switch(hrand(2))
		{
			case 0: retShipType = SHIP_CORVETTE; break;
			case 1: retShipType = SHIP_GALEON_H; break;
			case 2: retShipType = SHIP_FRIGATE; break;
		}
	}
	
	return retShipType;
}

String PiratesOnUninhabited_GenerateTreasureShore(ref _boxId)
{
	String retShoreId;
	
	switch(hrand(4))
	{
		case 0:
			retShoreId = "Shore9";
			_boxId = "box1";
		break;
		
		case 1:
			retShoreId = "Shore55";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
	
		case 2:
			retShoreId = "Shore_ship1";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
		
		case 3:
			retShoreId = "Shore_ship2";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
		
		case 4:
			retShoreId = "Shore_ship3";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
	}
	
	return retShoreId;
}

void PiratesOnUninhabited_SetCapToMap()
{
	int temp;
	String group = "PiratesOnUninhabited_SeaGroup";
	ref character = GetCharacter(NPC_GenerateCharacter("PiratesOnUninhabited_BadPirate", "", "man", "man", sti(pchar.rank) + 5, PIRATE, -1, true, "soldier"));		
	character.Ship.Type = GenerateShipExt(sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType), true, character);
	character.Ship.Name = PChar.GenQuest.PiratesOnUninhabited.StartShipName;
    SetBaseShipData(character);
    SetCrewQuantityFull(character);
    Fantom_SetCannons(character, "pirate");
    Fantom_SetBalls(character, "pirate");
	Fantom_SetUpgrade(character, "pirate");
	
	character.Ship.Mode = "pirate";	
	SetCaptanModelByEncType(character, "pirate");

	DeleteAttribute(character, "SinkTenPercent");
	DeleteAttribute(character, "SaveItemsForDead");
	DeleteAttribute(character, "DontClearDead");
	DeleteAttribute(character, "AboardToFinalDeck");
	DeleteAttribute(character, "SinkTenPercent");
	
	character.AlwaysSandbankManeuver = true;
	character.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	character.DontRansackCaptain = true; //не сдаваться
	
	SetAllPerksToChar(character, false);
	
	Group_FindOrCreateGroup(group);
	Group_SetTaskAttackInMap(group, PLAYER_GROUP);
	Group_LockTask(group);
	Group_AddCharacter(group, character.id);
	Group_SetGroupCommander(group, character.id);
	SetRandGeraldSail(character, PIRATE);
	
	character.fromCity = SelectAnyColony(""); // Колония, из бухты которой выйдет
	character.fromShore = GetIslandRandomShoreId(GetArealByCityName(character.fromCity));
	character.toCity = SelectAnyColony(character.fromCity); // Колония, в бухту которой придёт
	character.toShore = GetIslandRandomShoreId(GetArealByCityName(character.toCity));
	
	character.mapEnc.type = "trade";
	character.mapEnc.worldMapShip = "quest_ship";
	character.mapEnc.Name = LowerFirst(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'";
	
	Map_CreateTrader(character.fromShore, character.toShore, "PiratesOnUninhabited_BadPirate", GetMaxDaysFromIsland2Island(GetArealByCityName(character.toCity), GetArealByCityName(character.fromCity)) + 3);
	
	temp = GetCharacterFreeSpace(character, GOOD_SLAVES); // Сколько влезет рабов
	AddCharacterGoodsSimple(character, GOOD_SLAVES, makeint(temp / 2 + hrand(temp / 2)) - 1);
	
	PChar.Quest.PiratesOnUninhabited_ShipSink.win_condition.l1 = "Character_sink";
	PChar.Quest.PiratesOnUninhabited_ShipSink.win_condition.l1.character = "PiratesOnUninhabited_BadPirate";
	PChar.Quest.PiratesOnUninhabited_ShipSink.function = "PiratesOnUninhabited_ShipSink";
	
	Log_TestInfo("Pirates on an uninhabited island: cap left " + character.fromCity + " and went to: " + character.toShore);
}
// belamour gen количество каторжан прописью -->
String Convict_GetStringNum(int iCQTY)
{
	String ConvictStr = "";
	
	switch(iCQTY)
	{
		case 2: ConvictStr = "two"; break;
		case 3: ConvictStr = "three"; break;
		case 4: ConvictStr = "four"; break;
		case 5: ConvictStr = "five"; break;
		case 6: ConvictStr = "six"; break;
		case 7: ConvictStr = "seven"; break;
	}
	
	return ConvictStr;
}
// <-- gen

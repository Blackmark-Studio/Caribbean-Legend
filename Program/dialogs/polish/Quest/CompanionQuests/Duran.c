void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Czego wam trzeba?";
			link.l1 = "Niczego.";
			link.l1.go = "exit";
		break;
		
		case "SKD_DomAnri":
			dialog.text = "Witam w moim domu, panowie. Czym mogę Wam pomóc?";
			link.l1 = "Levasseur przesyła swoje pozdrowienia, monsieur.";
			link.l1.go = "SKD_DomAnri_2";
			StartQuestMovie(true, false, true);
		break;
		
		case "SKD_DomAnri_2":
			dialog.text = "Więc tak to wygląda... Alicjo! Zostaw nas, proszę. Ci panowie mają ze mną interesy.";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_2_1";
			CharacterTurnToLoc(npchar, "goto", "goto1");
		break;
		case "SKD_DomAnri_2_1":
			StartInstantDialog("SKD_Alisia", "SKD_DomAnri_3", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_3":
			dialog.text = "Ale...";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_3_1";
			CharacterTurnToLoc(npchar, "barmen", "stay");
		break;
		case "SKD_DomAnri_3_1":
			StartInstantDialog("SKD_Anri", "SKD_DomAnri_4", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_4":
			dialog.text = "Kocham cię, kochanie. No dalej!";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_5";
			CharacterTurnToLoc(npchar, "goto", "goto1");
		break;
		
		case "SKD_DomAnri_5":
			DialogExit();
			locCameraFromToPos(3.47, 2.41, 0.10, false, -1.05, 0.20, -0.07);
			
			sld = CharacterFromID("SKD_Anri");
			CharacterTurnByLoc(sld, "barmen", "stay");
			
			sld = CharacterFromID("SKD_Alisia");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "", "", "", "", -1);
			sld.location = "None";
			sld.lifeday = 0;
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("SKD_DomAnri_2", 4.0);
		break;
		
		case "SKD_DomAnri_6":
			dialog.text = "Cudowne dzieła, o Panie! Warto było stracić wszystko, aby znaleźć miłość swojego życia na końcu świata! Panowie, jestem cały wasz. Nie sądzę, żebyśmy mogli zawrzeć jakiś układ?";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_6_1";
		break;
		case "SKD_DomAnri_6_1":
			StartInstantDialog("Duran", "SKD_DomAnri_7", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_7":
			dialog.text = "Nie, i nie próbuj prosić o łaskę.";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_7_1";
			CharacterTurnToLoc(npchar, "barmen", "stay");
			locCameraFromToPos(-0.52, 1.47, 0.76, false, -2.52, 0.20, 0.99);
		break;
		case "SKD_DomAnri_7_1":
			StartInstantDialog("SKD_Anri", "SKD_DomAnri_8", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_8":
			dialog.text = "Nie przystoi Rycerzowi Zakonu prosić o łaskę.";
			link.l1 = "Choć byłym rycerzem.";
			link.l1.go = "SKD_DomAnri_9";
		break;
		
		case "SKD_DomAnri_9":
			dialog.text = "Biurokraci nie mieliby tyle atramentu na świecie, by odebrać mi ten tytuł.";
			link.l1 = "Skoro tak, to udowodnij. Ale najpierw zaspokój moją ciekawość: Czy jesteś zdrajcą Korony? Inaczej nie rozumiem, czemu Levasseur tak bardzo pragnął twojej śmierci.";
			link.l1.go = "SKD_DomAnri_10";
		break;
		
		case "SKD_DomAnri_10":
			dialog.text = "Jestem wierny mojej przysiędze, monsieur, więc nie miej mi tego za złe. Powiem tylko, że zdrajca Korony wysłał mnie, bym zlikwidował innego zdrajcę. I będzie to robić raz za razem, dopóki Brat bardziej zdolny ode mnie nie odniesie sukcesu. Dość gadania. Panowie, do walki!";
			link.l1 = "...";
			link.l1.go = "SKD_DomAnri_11";
		break;
		
		case "SKD_DomAnri_11":
			DialogExit();
			EndQuestMovie();
			
			sld = CharacterFromID("Duran");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "SKD_DomAnri_6");
		break;
		
		case "SKD_DomAnri_12":
			dialog.text = "Ah-ah! Och, dziękuję, Kapitanie. Twardy z niego diabeł był. Nie ma mowy, żebym go pokonał sam.";
			link.l1 = "Jakoś nie czuję się zbyt szczęśliwy z tego zwycięstwa. Czy to już koniec?";
			link.l1.go = "SKD_DomAnri_13";
		break;
		
		case "SKD_DomAnri_13":
			dialog.text = "Nie całkiem, najpierw musimy posprzątać i wyeliminować dziewczynę, która tak szybko uciekła na drugie piętro.";
			link.l1 = "Co?! Uspokój się! Czyś ty rozum postradał, Claude? Nie jestem rzeźnikiem!";
			link.l1.go = "SKD_DomAnri_14";
		break;
		
		case "SKD_DomAnri_14":
			dialog.text = "Nie musisz nic robić, Kapitanie. Poza tym, to wszystko twoja wina: nie powinieneś był wspominać jej o Levasseura.";
			link.l1 = "To bzdura i dobrze o tym wiesz. A jeśli odważysz się dać mi kolejną niewyraźną naganę, nie wywiniesz się z tego.";
			link.l1.go = "SKD_DomAnri_15";
		break;
		
		case "SKD_DomAnri_15":
			dialog.text = "Heh! Mój błąd, Kapitanie. Faktycznie, rozkazy Levasseura wyraźnie mówiły, by wyeliminować nie tylko rycerza, ale i wszystkich jego towarzyszy. Wszystkich, rozumiesz? Z tymi ludźmi nie ma żartów i ich żądania trzeba traktować poważnie. Nie powstrzymuj mnie przed wykonaniem mojej pracy, Kapitanie. Jeszcze jedno brudne zadanie i potem jestem z tobą do końca, przysięgam!";
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) > 70)
			{
				notification("Reputation Check Passed", "None");
				notification("Trustworthy", "Trustworthy");
				link.l1 = " (Godny zaufania) (Honor) Powiedziałeś kiedyś, że jestem przeznaczony do wielkich rzeczy, i cieszyło Cię, że mogłeś w tym pomóc.";
				link.l1.go = "SKD_DomAnri_VD";
			}
			else
			{
				notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(71))+")", "None");
				notification("Perk Check Failed", "Trustworthy");
			}
			link.l2 = "Do diabła z tobą! Wykonaj swoją brudną robotę. Przyjmuję twoją przysięgę, i lepiej, żebyś traktował ją śmiertelnie poważnie. Czy się rozumiemy?";
			link.l2.go = "SKD_DomAnri_DuranDruzhba";
			link.l3 = "Nie za tę cenę, Claude. Nie pozwolę ci zabić tej dziewczyny.";
			link.l3.go = "SKD_DomAnri_DuranDraka";
		break;
		
		case "SKD_DomAnri_DuranDraka":
			dialog.text = "Heh! Chyba było nam pisane się pozabijać, co, Kapitanie?";
			link.l1 = "Tak sądzę. Wróćmy do tego, gdzie skończyliśmy w Tortudze, dobrze?";
			link.l1.go = "SKD_DomAnri_DuranDraka_2";
		break;
		
		case "SKD_DomAnri_DuranDraka_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			
			RemovePassenger(pchar, npchar);
			npchar.SaveItemsForDead = true;
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "SKD_DomAnri_DuranDraka");
		break;
		
		case "SKD_DomAnri_DuranDruzhba":
			dialog.text = "Tak jest, Kapitanie!";
			link.l1 = "...";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_2";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_2":
			DialogExit();
			
			LocatorReloadEnterDisable("PortRoyal_houseSp1", "reload2", true);
			sld = CharacterFromID("Duran");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen("PortRoyal_town", true);
			
			PChar.quest.SKD_DomAnri_DuranDruzhba.win_condition.l1 = "location";
			PChar.quest.SKD_DomAnri_DuranDruzhba.win_condition.l1.location = "PortRoyal_town";
			PChar.quest.SKD_DomAnri_DuranDruzhba.win_condition = "SKD_DomAnri_DuranDruzhba";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_3":
			dialog.text = "Zrobione, kapitanie. Zaskoczyła mnie...";
			link.l1 = "Nie chcę o tym słyszeć. Dotrzymałem słowa. Teraz twoja kolej.";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_4";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_4":
			dialog.text = "Złoto to jedno, ale narażanie własnej skóry dla zwykłego najemnika jest warte o wiele więcej. Jestem z tobą do końca, Kapitanie.";
			link.l1 = "W takim razie, skończyliśmy tutaj.";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_5";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_5":
			dialog.text = "Tak jest.";
			link.l1 = "... ";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_6";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_6":
			DialogExit();
			
			EndQuestMovie();
			locCameraTarget(PChar);
			locCameraFollow();
			LAi_LocationDisableOfficersGen("PortRoyal_town", false);
			chrDisableReloadToLocation = false;
			AddQuestRecord("TheFormerKnight", "3");
			CloseQuestHeader("TheFormerKnight");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			
			sld = CharacterFromID("Duran");	//Клод Дюран становится постоянным офицером
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.Dialog.CurrentNode = "hired";
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0;
			sld.Health.maxHP    = 60.0;
			SetCharacterPerk(sld, "ShipEscape");
			
			pchar.questTemp.SKD_DuranDruzhba = true;
			pchar.questTemp.SKD_DevushkaUbita = true;
			sld.reputation = sti(sld.reputation) - 15;
			OfficersFollow();
		break;
		
		case "SKD_DomAnri_VD":
			dialog.text = "Zrobiłem to. O co ci chodzi, kapitanie?";
			link.l1 = "Udowodnij mi, że te słowa to nie były puste frazesy. Chcesz zdobyć miejsce w mojej drużynie? Udział w przyszłych łupach? Słuchaj moich rozkazów. Nie dotykaj dziewczyny. Dlaczego? Bo jeśli tego nie zrobisz, na zawsze pozostaniesz rzeźnikiem, a dla takich nie ma miejsca w mojej załodze.";
			link.l1.go = "SKD_DomAnri_VD_2";
		break;
		
		case "SKD_DomAnri_VD_2":
			dialog.text = "To już drugi raz, kiedy ty i ja mamy walczyć na śmierć, Kapitanie.\nI znów wygrywasz dzięki twojemu darowi do ciętych słów! Ha ha! Powiedziałeś to! Cóż, do diabła z dziewczyną. W końcu jestem bestią. Pozwolisz dołączyć do załogi?";
			link.l1 = "Witaj, Claude. Tym razem na serio.";
			link.l1.go = "SKD_DomAnri_VD_3";
		break;
		
		case "SKD_DomAnri_VD_3":
			dialog.text = "Tak jest, Kapitanie!";
			link.l1 = "...";
			link.l1.go = "SKD_DomAnri_VD_4";
		break;
		
		case "SKD_DomAnri_VD_4":
			DialogExit();
			AddQuestRecord("TheFormerKnight", "2");
			CloseQuestHeader("TheFormerKnight");
			chrDisableReloadToLocation = false;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			
			sld = CharacterFromID("Duran");	//Клод Дюран становится постоянным офицером
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.Dialog.CurrentNode = "hired";
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0;
			sld.Health.maxHP    = 60.0;
			SetCharacterPerk(sld, "ShipEscape");
			
			pchar.questTemp.SKD_DuranDruzhba = true;
			sld.reputation = 60;
			OfficersFollow();
		break;
		
		case "SKD_KlodDuran":
			dialog.text = "Coś się wydarzyło, Kapitanie.";
			Link.l1 = "Pozwól, że zgadnę: zamierzasz znów grozić rezygnacją i żądać podwyżki?";
			Link.l1.go = "SKD_KlodDuran_1";
		break;
		
		case "SKD_KlodDuran_1":
			dialog.text = "Heh! Nie tym razem... Nie martw się, Kapitanie, dopóki płacisz, jestem cały twój... w granicach rozsądku, oczywiście. To jedyny sposób, w jaki nasi bracia najemnicy przetrwają. I nawet najlepsi z nas są opłacani groszami.";
			link.l1 = "Może po prostu przejdźmy od razu do interesów?";
			link.l1.go = "SKD_KlodDuran_2";
		break;
		
		case "SKD_KlodDuran_2":
			dialog.text = "Pamiętasz tę sukę z Tortugi?";
			link.l1 = "Marceline? Żona gubernatora? Takiej kobiety nie da się zapomnieć.";
			link.l1.go = "SKD_KlodDuran_3";
		break;
		
		case "SKD_KlodDuran_3":
			dialog.text = "Nie trafiłem do domu Levasseura przypadkiem. Miałem do czynienia z tym łajdakiem i heretykiem.";
			link.l1 = "To dość dziwne, że mówisz tak pogardliwie o możnych, Claude.";
			link.l1.go = "SKD_KlodDuran_4";
		break;
		
		case "SKD_KlodDuran_4":
			dialog.text = "Co? Heh! Levasseur to diabeł! Jest o wiele gorszy niż nawet piraci, którzy się nim żywią!";
			link.l1 = "Sam powiedziałeś, że robiłeś z nim interesy. Czy to nie jest trochę hipokryzja z twojej strony?";
			link.l1.go = "SKD_KlodDuran_5";
		break;
		
		case "SKD_KlodDuran_5":
			dialog.text = "Nie jestem aniołem, Kapitanie, i zarabiam na życie, zabijając tych, kogo mi każą. Dlatego tak mnie cenisz, prawda? Ale nawet tacy jak ja dostają gęsiej skórki, słysząc plotki o tym, co robią kobietom na Tortudze w legowiskach Levasseura!";
			link.l1 = "Plotki mnie nie interesują. Ten człowiek to szlachcic i sługa Króla, i zasługuje na szacunek.";
			link.l1.go = "SKD_KlodDuran_6";
		break;
		
		case "SKD_KlodDuran_6":
			dialog.text = "Więc obrabowałeś sługę tego króla i przespałeś się z jego żoną? Heh! Rób, co chcesz, Kapitanie. Przejdźmy do rzeczy. Jego Ekscelencja zlecił mi znalezienie i zabicie człowieka. Dość rutynowe zadanie, nawet jeśli rzadko pochodzi od tak wysoko postawionej osoby, i to osobiście.";
			link.l1 = "A czego chcesz? Żebym cię uwolnił, abyś mógł dotrzymać słowa i zabić tego człowieka?";
			link.l1.go = "SKD_KlodDuran_7";
		break;
		
		case "SKD_KlodDuran_7":
			dialog.text = "Chcę, żebyś mi pomógł, kapitanie. Kiedy sytuacja na Tortudze się pogorszyła, zgodziłem się dołączyć do twojej służby, ale nie spocznę, dopóki nie wykonam zadania. Levasseur by mnie zabił, gdyby się dowiedział. Poza tym, to nieprofesjonalne zostawić robotę niedokończoną.";
			link.l1 = "Czy to profesjonalne mieć romans z żoną klienta? Bardzo dziwnie słyszeć takie żądanie od ciebie, zwłaszcza jeśli pamiętamy początek naszej rozmowy, gdzie dość trafnie opisałeś istotę naszych relacji. Krew za złoto, co?";
			link.l1.go = "SKD_KlodDuran_8";
		break;
		
		case "SKD_KlodDuran_8":
			dialog.text = "Jeśli mi pomożesz, nie tylko zdobędziesz mój miecz, ale i moją lojalność. Od razu widzę, że jesteś przeznaczony do wielkich rzeczy, Kapitanie. Z przyjemnością pomogę w tym.";
			link.l1 = "Przyznaję, wolałbym mieć u boku człowieka o twoich zdolnościach. Gdzie możemy znaleźć twój cel?";
			link.l1.go = "SKD_KlodDuran_10";
			link.l2 = "Twoja szabla na razie wystarczy. Nie jestem zabójcą. Spocznij, oficerze!";
			link.l2.go = "SKD_KlodDuran_9";
		break;
		
		case "SKD_KlodDuran_9":
			dialog.text = "Aye, aye, Kapitanie. Warto było zapytać.";
			link.l1 = "...";
			link.l1.go = "SKD_KlodDuran_9_1";
		break;
		
		case "SKD_KlodDuran_9_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.loyality = makeint(npchar.loyality) + 10;
			Return_DurandOfficer();
		break;
		
		case "SKD_KlodDuran_10":
			dialog.text = "Heh! To jest problem, kapitanie. Wszystko, co wiem, to że jest byłym rycerzem Zakonu Maltańskiego, ukrywającym się gdzieś na terytorium angielskim. Człowiek szlachetnego urodzenia, więc nie będzie mieszkał w lepiance.";
			link.l1 = "Rycerz Zakonu?";
			link.l1.go = "SKD_KlodDuran_11";
		break;
		
		case "SKD_KlodDuran_11":
			dialog.text = "Były rycerz. Tak, i już tysiąc razy żałowałem, że wziąłem tę robotę. Rycerze walczą jak diabły, więc gwarantuję ci poważny sprawdzian twoich umiejętności szermierczych.";
			link.l1 = "Nie podoba mi się to, ale spróbujmy. Więc: nie biedak, szlachcic i ukrywający się z Anglikami? Levasseur nie powiedział, dlaczego należy się z nim rozprawić?";
			link.l1.go = "SKD_KlodDuran_12";
		break;
		
		case "SKD_KlodDuran_12":
			dialog.text = "Oczywiście, że nie! Ale to jest ewidentnie polityczne, inaczej wysłałby żołnierzy.";
			link.l1 = "Spróbuję, ale nic nie mogę obiecać.";
			link.l1.go = "SKD_KlodDuran_13";
		break;
		
		case "SKD_KlodDuran_13":
			dialog.text = "Dzięki, Kapitanie.";
			link.l1 = "...";
			link.l1.go = "SKD_KlodDuran_14";
		break;
		
		case "SKD_KlodDuran_14":
			DialogExit();
			SetQuestHeader("TheFormerKnight");
			AddQuestRecord("TheFormerKnight", "1");
			chrDisableReloadToLocation = false;
			npchar.loyality = makeint(npchar.loyality) + 15;
			Return_DurandOfficer();
			PChar.quest.SKD_DomAnri.win_condition.l1 = "location";
			PChar.quest.SKD_DomAnri.win_condition.l1.location = "PortRoyal_houseSp1";
			PChar.quest.SKD_DomAnri.win_condition = "SKD_DomAnri";
			pchar.GenQuestBox.PortRoyal_houseSp1.box1.items.chest = 1;
		break;
		
	}
} 

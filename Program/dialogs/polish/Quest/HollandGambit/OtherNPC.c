// диалоги прочих НПС
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Robak. Powiedz deweloperom.";
			link.l1 = "Zrobię to!";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			if (npchar.id == "HWICFernando") NextDiag.CurrentNode = "Fernando";
			DialogExit();
		break;
	
//---------------------------------------за Голландию--------------------------------------------------
		//сопроводить торговца
		case "Baltazar":
			pchar.quest.Create_BaltazarOver.over = "yes";//снять прерывание
			dialog.text = "Co za szczęście! Kapitanie, akurat potrzebuję pilnie eskorty do Philipsburga...";
			link.l1 = "Czy jesteś Balthazar Ridderbock?";
			link.l1.go = "Baltazar_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Baltazar_1":
			dialog.text = "Co do diabła, jestem już bardziej znany niż wicekról! Kim jesteś? Czego chcesz?";
			link.l1 = "Jestem Kapitanem "+GetFullName(pchar)+"Zostałem wysłany do ciebie przez Lukasa Rodenburga. Mam upoważnienie, aby wziąć ciebie i twój statek pod moją ochronę.";
			link.l1.go = "Baltazar_2";			
		break;
		
		case "Baltazar_2":
			dialog.text = "Och, pan Rodenburg musiał usłyszeć moje błagania o pomoc! Widzisz, jest pewien korsarz...";
			link.l1 = "Pomińmy szczegóły twojej opowieści, już je znam.";
			link.l1.go = "Baltazar_3";			
		break;
		
		case "Baltazar_3":
			dialog.text = "Oczywiście! Już straciłem zbyt wiele czasu... Muszę dotrzeć do Philipsburga nie później niż za dwa tygodnie.";
			link.l1 = "Zatem idź na swój statek i przygotuj się do żeglugi. Wypływamy natychmiast!";
			link.l1.go = "Baltazar_4";			
		break;
		
		case "Baltazar_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 4);
			SetCharacterRemovable(npchar, false);
			npchar.CompanionEnemyEnable = false; //всегда друзья
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
			AddQuestRecord("Holl_Gambit", "1-3");
			AddMapQuestMarkCity("Marigo", true);
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Baltazar_ConvoyOver", 0, 0, 28, false);
			}
			else SetFunctionTimerCondition("Baltazar_ConvoyOver", 0, 0, 14, false); //таймер
			pchar.quest.BaltazarConvoy_fail.win_condition.l1 = "NPC_Death";//прерывание на потопление сопровождаемого
			pchar.quest.BaltazarConvoy_fail.win_condition.l1.character = "Baltazar";
			pchar.quest.BaltazarConvoy_fail.function = "Baltazar_fail";
			pchar.quest.BaltazarConvoy_complete.win_condition.l1 = "location";//прерывание на выполнение
			pchar.quest.BaltazarConvoy_complete.win_condition.l1.location = "Marigo_town";
			pchar.quest.BaltazarConvoy_complete.function = "Baltazar_complete";
			if (rand(1) == 0)
			{
				BaltazarPirateGlobalCreate();
			}
			else
			{
				pchar.questTemp.HWIC.Holl.BaltazarAttack = "true";
				pchar.quest.BaltazarConvoy_Attack.win_condition.l1 = "location";//прерывание на выполнение
				pchar.quest.BaltazarConvoy_Attack.win_condition.l1.location = "SentMartin";
				pchar.quest.BaltazarConvoy_Attack.function = "BaltazarPirateSeaCreate";
			}
		break;
		
		case "Baltazar_5":
			dialog.text = "Dziękuję za pomoc, Kapitanie! Twoja ochrona przyszła w najlepszym momencie, przyjmij moje podziękowania i te 5 000 pesos.";
			link.l1 = "Hmm... To nie jest zbyt hojna nagroda za ocalenie życia...";
			link.l1.go = "Baltazar_6";			
		break;
		
		case "Baltazar_6":
			dialog.text = "Poza tym, wyślę list do pana Rodenburga, kiedy będę miał okazję - z najwyższą możliwą oceną za twoje działania. Teraz muszę iść.";
			link.l1 = "No cóż, żegnaj zatem, Baltazarze.";
			link.l1.go = "Baltazar_7";			
		break;
		
		case "Baltazar_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", 3.0);
			AddQuestRecord("Holl_Gambit", "1-6");
			AddMoneyToCharacter(pchar, 5000);
			ChangeCharacterComplexReputation(pchar,"nobility", 2); 
			ChangeCharacterNationReputation(pchar, HOLLAND, 1);
			ChangeOfficersLoyality("good_all", 1);
			pchar.questTemp.HWIC.Holl = "BaltazarCom";
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			AddMapQuestMarkCity("Villemstad", true);
		break;
		
		//командировка в Сантьяго
		case "Santiago_Trip":
			dialog.text = "Sznor! Czekaj... wygląda na to, że coś upuściłeś...";
			link.l1 = "Co? Ah?!";
			link.l1.go = "Santiago_Trip_1";
		break;
		
		case "Santiago_Trip_1":
			DialogExit();
			PlaySound("People Fight\Death_NPC_08.wav");
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("You were knocked unconscious from behind", "", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 15, 10); //крутим время
			RecalculateJumpTable();
			DoQuestFunctionDelay("SantiagoTripInHouse", 4.0);
		break;
		
		case "Santiago_Trip_2":
			dialog.text = "Przepraszam, mój przyjacielu - musiałem ci lekko przyłożyć, żebyś nie sprawił żadnych kłopotów. Zdaję sobie sprawę, że pewnie boli cię głowa, ale co tam, przeżyjesz. Jeśli będzie na to czas...";
			link.l1 = "Kim jesteś, do diabła, i co tu się dzieje?";
			link.l1.go = "Santiago_Trip_3";
		break;
		
		case "Santiago_Trip_3":
			dialog.text = "Spokojnie, spokojnie, przyjacielu - inaczej będę musiał cię znów uspokoić. Nie chcemy, aby te marionetki wpadły tutaj, brzęcząc swoimi zardzewiałymi mieczami, prawda? Musimy porozmawiać na spokojnie.";
			link.l1 = "Oddaj mi mój miecz, skurwysynie, a pogadamy sobie miło, przysięgam!";
			link.l1.go = "Santiago_Trip_4";
		break;
		
		case "Santiago_Trip_4":
			dialog.text = "Jesteś szybkim małym człowieczkiem, prawda? Na razie nie ma potrzeby używać stali. Powiedz mi, co chcę wiedzieć, a może wyjdziesz stąd w jednym kawałku. Czy jestem jasny? Porozmawiajmy więc trochę.\nMilczysz? Dobrze, mamy więc umowę. Co przyniosłeś od Rodenburga do bankiera?";
			link.l1 = "List.";
			link.l1.go = "Santiago_Trip_5";
		break;
		
		case "Santiago_Trip_5":
			dialog.text = "Sprytnie. Wiem, że to nie był bukiet stokrotek. Co było w tym liście, chłopcze?";
			link.l1 = "Skąd mam wiedzieć? Nie mam zwyczaju czytać korespondencji powierzonej mi. Może to była wiadomość miłosna. Wiesz, co mówią o ludziach u władzy...";
			link.l1.go = "Santiago_Trip_6";
		break;
		
		case "Santiago_Trip_6":
			dialog.text = "...Uczciwy kapitan to dość rzadki widok w tych nędznych czasach. Cóż, to zła wiadomość dla ciebie. Co powiedział ten cholerny bankier, kiedy otrzymał paczkę? Jakie ma interesy z Holendrami?";
			link.l1 = "Handlują przemycanym perfumem z Francji... albo bawarskim gównem krowim, tak myślę.";
			link.l1.go = "Santiago_Trip_7";
			link.l2 = "Chodziło o rekompensatę za coś. To wszystko, co wiem.";
			link.l2.go = "Santiago_Trip_8";
		break;
		
		case "Santiago_Trip_7":
			dialog.text = "Jesteś odważnym gościem... I masz też poczucie humoru. Byłoby szkoda cię zabić. Gaston by cię polubił. Chociaż... zostań tu na razie. Powinienem coś sprawdzić, a Miguel będzie się tobą opiekował, gdy mnie nie będzie.";
			link.l1 = "Przysięgam, 'mój przyjacielu' - pożałujesz tego! ";
			link.l1.go = "Santiago_Trip_9";
		break;
		
		case "Santiago_Trip_8":
			dialog.text = "Wszystko minęło... Gdy sytuacja wygląda ponuro, nasz dzielny kapitan wykazuje rozsądek. Mogłeś to zrobić dużo wcześniej i zaoszczędziłbyś nam czasu oraz kłopotów. Cóż, muszę iść coś sprawdzić, ale potem wrócę i porozmawiamy, o ile będzie jeszcze taka potrzeba. Zostań tutaj na razie. Miguel będzie się tobą opiekował, gdy mnie nie będzie.";
			link.l1 = "Przysięgam, 'mój przyjacielu' - pożałujesz tego! ";
			link.l1.go = "Santiago_Trip_11";
		break;
		
		case "Santiago_Trip_9":
			dialog.text = "Ale oczywiście. Zachowaj spokój, 'bohaterze' - być może, wszystko jeszcze będzie dobrze.";
			link.l1 = "... ";
			link.l1.go = "Santiago_Trip_11";
		break;
		
		case "Santiago_Trip_10":
			dialog.text = "Zostań tu i miej nadzieję, że twoja elastyczność się opłaci.";
			link.l1 = "... ";
			link.l1.go = "Santiago_Trip_11";
		break;
		
		case "Santiago_Trip_11":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-44");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "Santiago_HouseSp2", "goto", "goto4", "", -1);
			pchar.quest.Santiago_Trip1.win_condition.l1 = "item";
			pchar.quest.Santiago_Trip1.win_condition.l1.item = "slave_01";
			pchar.quest.Santiago_Trip1.function = "SantiagoTrip_wait";
		break;
		
		case "Santiago_Trip_12":
			dialog.text = "Co do diabła?!";
			link.l1 = "Przygotuj się na śmierć, łotrze!";
			link.l1.go = "Santiago_Trip_13";
		break;
		
		case "Santiago_Trip_13":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "SantiagoTripExitFromRoom");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Santiago_Trip_14":
			dialog.text = "Co za bałagan! Zastanawiałem się, o co chodzi z tym hałasem. Moje gratulacje - jesteś bystrym facetem!";
			link.l1 = "Mądrzejszy, niż myślisz... Zobaczmy teraz, co potrafisz przeciw uzbrojonemu przeciwnikowi!";
			link.l1.go = "Santiago_Trip_15";
		break;
		
		case "Santiago_Trip_15":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "SantiagoTripExitHouse");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		//офицер-посланник по 5 заданию
		case "HollQuest_Officer":
			dialog.text = "Mynheer Lucas Rodenburg chce cię zobaczyć natychmiast. Przyjdź do niego od razu.";
			link.l1 = "W drodze.";
			link.l1.go = "HollQuest_Officer_exit";			
		break;
		
		case "HollQuest_Officer_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			pchar.questTemp.HWIC.Holl = "MerdokStart";
			AddQuestRecord("Holl_Gambit", "1-36");
		break;
		
//---------------------------------------------против всех----------------------------------------------
		//убрать испанского идальго
		case "Fernando":
			dialog.text = "Czego ode mnie chcesz?";
			link.l1 = "Twoja głowa!";
			link.l1.go = "Fernando_fight";
			link.l2 = "Nieważne, zapomnij.";
			link.l2.go = "exit";	
			NextDiag.TempNode = "Fernando_repeat";
		break;
		
		case "Fernando_repeat":
			dialog.text = "„To znowu ty? Czego ode mnie chcesz?! Wytłumacz się!”";
			link.l1 = "Twoja głowa!";
			link.l1.go = "Fernando_fight";
			link.l2 = "Nic, nieważne.";
			link.l2.go = "exit";	
			NextDiag.TempNode = "Fernando_repeat";		
		break;
		
		case "Fernando_fight":
			chrDisableReloadToLocation = true;//выходы закроем
			LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "SPAIN_CITIZENS");
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
			pchar.quest.HWIC_Fernando.win_condition.l1 = "NPC_Death";
			pchar.quest.HWIC_Fernando.win_condition.l1.character = "HWICFernando";
			pchar.quest.HWIC_Fernando.function = "Fernando_died";
		break;
		
		//в доме Флитвуда
		case "Fleetwood_soldier"://для любителей сунуть нос куда не надо
			if (CheckAttribute(npchar, "quest.talked"))
			{
			dialog.text = "To znowu ty? Dlaczego się tu kręcisz? Wcale mi się to nie podoba. Dobra, aresztuję cię i wyślę do biura komendanta na przesłuchanie. Chłopcy, złapcie tego gościa!";
			link.l1 = "Ale ja tylko chciałem...";
			link.l1.go = "Fleetwood_soldier_4";	
			}
			else
			{
			dialog.text = "Kim jesteś i czego chcesz? Wytłumacz się!";
			link.l1 = "Przepraszam, panie, wydaje się, że trafiłem do niewłaściwego domu. Proszę o wybaczenie.";
			link.l1.go = "Fleetwood_soldier_1";	
			link.l2 = "Chciałbym zobaczyć Richarda Fleetwooda.";
			link.l2.go = "Fleetwood_soldier_2";		
			}
		break;
		
		case "Fleetwood_soldier_1":
			dialog.text = "Zgadza się. Rozmawiasz z niewłaściwym człowiekiem. Bądź tak uprzejmy i odejdź natychmiast!";
			link.l1 = "Tak. Oczywiście.";
			link.l1.go = "Fleetwood_soldier_3";			
		break;
		
		case "Fleetwood_soldier_2":
			dialog.text = "Naprawdę? Kto ci powiedział, że on tu mieszka? To wydaje się podejrzane... Dobrze, aresztuję cię i wyślę do biura komendanta na przesłuchanie. Chłopcy, schwytajcie tego gościa!";
			link.l1 = "Ale ja tylko chciałem zobaczyć Richarda...";
			link.l1.go = "Fleetwood_soldier_4";	
		break;
		
		case "Fleetwood_soldier_3":
			DialogExit();
			npchar.quest.talked = "true";
			DoQuestReloadToLocation("SentJons_town", "reload", "houseSP3", "");
			pchar.quest.Fleetwood_Soldier.win_condition.l1 = "location";
			pchar.quest.Fleetwood_Soldier.win_condition.l1.location = "SentJons_houseSP3";
			pchar.quest.Fleetwood_Soldier.function = "Fleetwood_Soldier";//для настырных
		break;
		
		case "Fleetwood_soldier_4":
			DialogExit();
			GoToPrison("SentJons", 1000, 10);			
		break;
		
		case "Theft_soldier":
			dialog.text = "Ah! Złodzieje? Szpiedzy? Trzymaj się teraz kapelusza!";
			link.l1 = "Hup!";
			link.l1.go = "Attack_Theft_soldier";			
		break;
		
		case "Attack_Theft_soldier":
			LAi_group_Delete("EnemyFight");
			LAi_SetHP(npchar, 500, 500);
			LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Attack_soldier":
			dialog.text = "Ach! Co ten gość tu robi? Chłopcy, mamy tu szpiega! Do broni!";
			link.l1 = "Hup!";
			link.l1.go = "Attack_soldier_fight";			
		break;
		
		case "Attack_soldier_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//снять запрет драки
			LAi_group_Delete("EnemyFight");
			for (i=1; i<=4; i++)
			{
			sld = characterFromId("Attack_sold_"+i);	
			LAi_SetWarriorType(sld);
            LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "PrepareToStreetFight");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		//Книппель-пленник в трюме
		case "Sailor_deck":
			chrDisableReloadToLocation = true;
			dialog.text = "Kapitánie, przesłuchaliśmy tego łotra, jak nam kazałeś. Musieliśmy go trochę przypiec... Miał przy sobie ten list. Próbował go zjeść, ale mu nie pozwoliliśmy. Tak jak się spodziewaliśmy, miał zabrać jakąś dziewczynę w Willemstad i przyprowadzić ją do swojego szefa.";
			link.l1 = "List? Daj no, zerknę na niego. Potem sam z nim pogadam.";
			link.l1.go = "Sailor_deck_1";			
		break;
		
		case "Sailor_deck_1":
			DialogExit();
			AddLandQuestMark(characterFromId("KnippelClone"), "questmarkmain");
			GiveItem2Character(pchar, "NPC_Letter");
			AddQuestRecordInfo("LetterToAbi", "1");
		break;
		
		case "Sailor_deck_2":
			dialog.text = "Jakie są twoje rozkazy, Kapitanie?";
			link.l1 = "Wyrzuć trupa za burtę. I przygotuj się do zejścia na ląd!";
			link.l1.go = "Sailor_deck_3";			
			// belamour legendary edition -->
			link.l2 = "Pochowaj go na morzu z pełnymi honorami wojskowymi. Ten starzec walczył dzielnie do samego końca. Nawet załadował i wycelował to działo, gdy zostało zniszczone z jego lawety. Prawdziwa szkoda. W innym świecie moglibyśmy być towarzyszami...";
			link.l2.go = "Sailor_deck_3a";
		break;
		
		case "Sailor_deck_3a":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			dialog.text = "Tak, Kapitanie!";
			link.l1 = "... ";
			link.l1.go = "Sailor_deck_4";			
		break;
		
		case "Sailor_deck_3":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Sneak", 120);
			AddCharacterExpToSkill(pchar, "FencingL", 30);
			AddCharacterExpToSkill(pchar, "FencingS", 30);
			AddCharacterExpToSkill(pchar, "FencingH", 30);
			AddCharacterExpToSkill(pchar, "Pistol", 30);
			// <-- legendary edition
			dialog.text = "Tak jest, kapitanie!";
			link.l1 = "...";
			link.l1.go = "Sailor_deck_4";			
		break;
		
		case "Sailor_deck_4":
			DialogExit();
			chrDisableReloadToLocation = false;
			AddQuestRecord("Holl_Gambit", "3-21");
			LAi_SetActorType(pchar);
			sld = characterFromId("KnippelClone");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld.lifeday = 0;
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("Sailor_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "ReturnMCPlayer", 3);
			}
			pchar.questTemp.HWIC.Self = "toVillemstad";
			sld = characterFromId("Solomon");
			sld.greeting = "solomon_2";
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("Villemstad", false);
			LocatorReloadEnterDisable("Villemstad_town", "houseSP2", false);//откроем дом Аби
			LocatorReloadEnterDisable("Villemstad_houseSP2", "reload2", true);//закроем комнату Аби
		break;
		
		//Лонгвэй-пленник в трюме
		case "Sailor_deck_5":
			chrDisableReloadToLocation = true;
			dialog.text = "Przygotowaliśmy Chińczyka do przesłuchania, tak jak rozkazałeś, Kapitanie. Nie miał przy sobie nic, żadnych dokumentów. Przygotowano piecyk, i właśnie rozgrzewamy kajdanki i szczypce do czerwoności.";
			link.l1 = "Dobra robota, Alonso. Ale zanim zaczniesz, chciałbym spróbować przemówić mu do rozsądku. Może zdecyduje się współpracować dobrowolnie?";
			link.l1.go = "Sailor_deck_6";			
		break;
		
		case "Sailor_deck_6":
			dialog.text = "Jak powiadasz, Kapitanie.";
			link.l1 = "... ";
			link.l1.go = "exit";	
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
		break;
		
		case "Sailor_deck_7":
			dialog.text = "Tak, Kapitanie?";
			link.l1 = "Zakujcie go w kajdany i miejcie go na oku przez cały czas, aż dotrzemy do Gwadelupy. Wy trzej musicie tu zawsze być. Odpowiadacie za niego własnym życiem.";
			link.l1.go = "Sailor_deck_8";			
		break;
		
		case "Sailor_deck_8":
			dialog.text = "Tak jest, kapitanie!";
			link.l1 = "";
			link.l1.go = "Sailor_deck_9";			
		break;
		
		case "Sailor_deck_9":
			chrDisableReloadToLocation = false;
			AddQuestRecord("Holl_Gambit", "3-48");
			sld = characterFromId("LongwayClone");
			LAi_SetActorType(sld);
			LAi_SetGroundSitType(sld);
			DialogExit();
			pchar.quest.Longway_Shore.win_condition.l1 = "location";
			pchar.quest.Longway_Shore.win_condition.l1.location = "Shore31";
			pchar.quest.Longway_Shore.function = "LongwayInShore";
			AddMapQuestMarkShore("Shore31", true);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
		break;
		
		//пьяница - передача письма Флитвуду
		case "Drunkard":
			DelLandQuestMark(npchar);
			dialog.text = "H-ic! Dobry wieczór, panie! Czego byś sobie życzył? Może postawisz staremu pijakowi drinka? A ja bym...";
			link.l1 = "Słuchaj tutaj, stary pijaku... Czy jesteś Jack Harrison?";
			link.l1.go = "Drunkard_1";			
		break;
		
		case "Drunkard_1":
			dialog.text = "O! Tak, to ja. Któż inny mógłby to być? Dlaczego? Cóżżż mamy zrobiććć zżż pijanym żegla-a-rzeee...";
			link.l1 = "O mój Panie, daj mi cierpliwość! Jaki z ciebie żeglarz? Na twarzy masz wypisane, że jesteś szczurem lądowym... Chcesz zarobić trochę grosza?";
			link.l1.go = "Drunkard_2";			
		break;
		
		case "Drunkard_2":
			dialog.text = "Zawsze chcę zarabiać pieniądze. Co mam robić? Ale nie zabiję nikogo. I niczego nie ukradnę. I nie jesteś w moim typie.";
			link.l1 = "Nie musisz nikogo zabijać, a wątpię, czy faktycznie jesteś do tego zdolny. Jesteś zbyt niezgrabny. Teraz. Oto list. Weź go i dostarcz do domu po lewej stronie rezydencji gubernatora. Jest przeznaczony dla Richarda Fleetwooda.";
			link.l1.go = "Drunkard_3";			
		break;
		
		case "Drunkard_3":
			dialog.text = "Dla Richarda Fleetwooda? Nie... Zostanę aresztowany na miejscu.";
			link.l1 = "Zamknij się i słuchaj. Nikt cię nie aresztuje. Powiesz, że przyszedłeś od Charliego Knippela w sprawie Abigail. Zostaniesz wpuszczony. Powtórz, co powiedziałem.";
			link.l1.go = "Drunkard_4";			
		break;
		
		case "Drunkard_4":
			dialog.text = "Kim jest Abigail? Znam Knippela...";
			link.l1 = "Nie twój interes. Im mniej wiesz, tym dłużej pożyjesz. Cóż, czekam. Powtórz.";
			link.l1.go = "Drunkard_5";			
		break;
		
		case "Drunkard_5":
			dialog.text = "Przychodzę od Charlie'ego Knippela w sprawie twojej..... Abigail. Otóż to.";
			link.l1 = "Dobra robota. Otrzymasz 5000 pesos za tę robotę.";
			link.l1.go = "Drunkard_6";			
		break;
		
		case "Drunkard_6":
			if (makeint(Pchar.money) >= 5000)
			{
				dialog.text = "5000 pesos? Ooo... Tylko za dostarczenie listu?";
				link.l1 = "Nie. Otrzymasz kolejny list. Przyjdziesz z nim do tawerny i usiądziesz tutaj. Ja go od ciebie odbiorę. Nie rób nic głupiego i nie bój się - będę cię obserwował i będę blisko. Weź tę sumę jako zaliczkę, żebyś czuł się pewniej.";
				link.l1.go = "Drunkard_7";	
			}
			else
			{
				dialog.text = "Pięć tysięcy? Czy masz w ogóle tyle pieniędzy?";
				link.l1 = "Ha! Oczywiście, że mam. Zaraz to przyniosę.";
				link.l1.go = "Drunkard_no_money";	
				NextDiag.CurrentNode = "Drunkard_no_money";
			}
		break;
		
		case "Drunkard_no_money":
			dialog.text = "Przyniosłeś pięć tysięcy?";
			if (makeint(Pchar.money) >= 5000)
			{
				link.l1 = "Tak. Proszę bardzo. Nie martw się.";
				link.l1.go = "Drunkard_7";
			}
			else
			{
				link.l1 = "Nie. Czekaj. Wrócę wkrótce.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Drunkard_no_money";
			}
		break;
		
		case "Drunkard_7":
			AddMoneyToCharacter(pchar, -5000);
			RemoveItems(PChar, "MC_Letter", 1);
			dialog.text = "Hmm... Czy powinienem teraz iść, sir?";
			link.l1 = "Nie, w czwartek rano... Oczywiście, teraz, ty głupcze! Teraz kończ swój rum i idź!";
			link.l1.go = "Drunkard_8";			
		break;
		
		case "Drunkard_8":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-26");
			LAi_SetStayType(npchar);
			LAi_RemoveLoginTime(npchar);//удалить время загрузки
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, "sentjons_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "sentjons_town", "reload", "reload4_back", "DrunkardGoTown", -1);
			chrDisableReloadToLocation = true;//закрыть локацию
			LocatorReloadEnterDisable("SentJons_town", "reload1_back", true);
			LocatorReloadEnterDisable("SentJons_town", "reload2_back", true);
			LocatorReloadEnterDisable("SentJons_town", "gate_back", true);//чтобы не сбежал
		break;
		
		case "Drunkard_9":
			DelLandQuestMark(npchar);
			dialog.text = "Ach, oto Pan jest, sir... Lepiej by było, gdybym tego nie zrobił. Richard wpadł w furię, gdy skończył czytać. Myślałem, że mnie zabije.";
			link.l1 = "Lecz oto jesteś! Nie martw się - nie odważyłby się tego zrobić - byłeś dla niego bardzo cenny w tamtej chwili, ha-ha! Nawet nie możesz sobie wyobrazić, jak bardzo...";
			link.l1.go = "Drunkard_10";			
		break;
		
		case "Drunkard_10":
			dialog.text = "Muszę się napić... Oto jego odpowiedź dla ciebie.";
			link.l1 = "Daj to mnie! I zamknij gębę!";
			link.l1.go = "Drunkard_11";			
		break;
		
		case "Drunkard_11":
			GiveItem2Character(pchar, "MC_Letter");
			ChangeItemDescribe("MC_Letter", "itmdescr_MC_Letter1");
			AddQuestRecordInfo("FleetwoodAnswer", "1");
			dialog.text = "Przez kilka następnych dni trudno mi będzie rozmawiać... Żegnaj... Obyśmy się nigdy więcej nie spotkali.";
			link.l1 = "Spokojnie, stary pijaku, ha-ha-ha! Co zrobimy z pijanym marynarzem... Pij i odpocznij - wszystko już skończone!";
			link.l1.go = "Drunkard_12";			
		break;
		
		case "Drunkard_12":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Holl_Gambit", "3-27");
			pchar.questTemp.HWIC.Self = "FleetwoodAgree";
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		//кэп курьерского судна
		case "Cureer_abordage":
			dialog.text = "Na Boga, czemu zaatakowaliście mój statek? Nie mam ani kosztowności, ani pieniędzy - tylko papiery, które i tak nie są wam do niczego potrzebne!";
			link.l1 = "Zamknij się. Przegrałeś, więc teraz będziesz mnie słuchać. Nie potrzebuję ani twojego statku, ani twoich papierów. Potrzebuję, abyś przekazał tę wiadomość swojemu szefowi, tej parszywej szczurze Lucasowi Rodenburgowi. Powiedz mu, że kapitan Fleetwood przesyła pozdrowienia.";
			link.l1.go = "Cureer_abordage_1";			
		break;
		
		case "Cureer_abordage_1":
			dialog.text = "Kapitan Fleetwood? Ale...";
			link.l1 = "Czy przekażesz ten list swojemu szefowi - czy może mam cię przebić na wylot? Mogę też poszukać innego kandydata do dostarczenia. Dla twojej wiadomości, z powodu nudy napadam na statki tej waszej plugawnej Kompanii co weekend.";
			link.l1.go = "Cureer_abordage_2";			
		break;
		
		case "Cureer_abordage_2":
			dialog.text = "Dobrze, panie Fleetwood. Dostarczę to.";
			link.l1 = "To świetnie. Teraz możemy się pożegnać, Mynheer. Możesz się dziś uważać za bardzo szczęśliwego. I nie zapomnij odwiedzić kościoła po przybyciu!";
			link.l1.go = "Cureer_abordage_3";			
		break;
		
		case "Cureer_abordage_3":
			DialogExit();
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			sld.ShipEnemyDisable  = true;
			pchar.quest.HWICCureer_AfterBattle.over = "yes";
			pchar.quest.HWICCureerOnMapOver.over = "yes";
			AddQuestRecord("Holl_Gambit", "3-39");
			Log_TestInfo("THE LETTER HAS BEEN DELIVERED!");
			RemoveItems(PChar, "MC_Letter", 1);
			pchar.questTemp.HWIC.Self = "LetterToLucasSent";
			pchar.quest.Curacao_exploring.win_condition.l1 = "location";
			pchar.quest.Curacao_exploring.win_condition.l1.location = "Curacao";
			pchar.quest.Curacao_exploring.function = "CuracaoExploring";
			DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
			AddComplexSeaExpToScill(50, 50, 50, 100, 50, 50, 0);
			AddComplexSelfExpToScill(30, 30, 30, 30);
			AddMapQuestMarkIsland("Curacao", true);
		break;
		
		//Матиас Бек в тюрьме
		case "MatiasBek"://на случай если геймер захочет пообщаться
			dialog.text = "Zostałem aresztowany nielegalnie! Nie mam żadnych powiązań z Anglikami! To wszystko intrygi Rodenburga. Nieważne. Peter Stuyvesant wkrótce przybędzie - on to wszystko rozwiąże!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "MatiasBek";
		break;
		
		//стражник у входа в резиденцию
		case "QuestGuard":
			dialog.text = "Panie Lucas Rodenburg nie chce nikogo widzieć w tej chwili. Bądź tak miły i opuść rezydencję natychmiast.";
			link.l1 = "Hm. Rozumiem. Spróbuję zajrzeć za tydzień...";
			link.l1.go = "exit";
			NextDiag.TempNode = "QuestGuard";		
		break;
		
		//Питер Стайвесант
		case "Stivesant":
			dialog.text = "Idziemy do rezydencji, Kapitanie. Już wysłałem moich ludzi do fortu, aby zdobyć informacje o Matthiasie Becku. Jeśli rzeczywiście jest teraz w więzieniu, musiał już zostać zwolniony i odprowadzony do miasta. Podążaj za mną!";
			link.l1 = "Tak, Mynheer Stuyvesant.";
			link.l1.go = "Stivesant_1";			
		break;
		
		case "Stivesant_1":
			DialogExit();
			AddLandQuestMark(npchar, "questmarkmain");
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "Villemstad_townhall", "goto", "goto2", "OpenVillemstadResidence", -1);
		break;
		
		case "ArestLucas_1":
			dialog.text = "Lucas! Co tu się dzieje? Gdzie jest Matthias Beck? Czy to prawda, że wysłałeś go do więzienia?";
			link.l1 = "";
			link.l1.go = "ArestLucas_2";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_2":
			StartInstantDialog("Lucas", "ArestLucas_3", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_3":
			dialog.text = "Witaj, panie Stuyvesant. Mam dowód na jego powiązania z brytyjskim wywiadem i bezpośrednio z kapitanem Fleetwoodem. Dał cynk przeklętym Brytyjczykom, aby zaatakowali nasz brygantynę kurierową, by przejąć poufną korespondencję Kompanii.";
			link.l1 = "";
			link.l1.go = "ArestLucas_4";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));
			LAi_ActorAnimation(npchar, "dialog_stay13", "1", 4.5);
		break;
		
		case "ArestLucas_4":
			StartInstantDialog("Stivesant", "ArestLucas_5", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_5":
			dialog.text = "Gdzie zdobyłeś te informacje?";
			link.l1 = "";
			link.l1.go = "ArestLucas_6";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_6":
			StartInstantDialog("Lucas", "ArestLucas_7", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_7":
			dialog.text = "It was claimed by the captain of the courier brigantine. Richard Fleetwood boarded his ship and took away his papers; then the ship was set free. Nobody except me, you and Matthias Beck had any information about either the route or the schedule.";
			link.l1 = "";
			link.l1.go = "ArestLucas_8";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));
		break;
		
		case "ArestLucas_8":
			StartInstantDialog("Stivesant", "ArestLucas_9", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_9":
			dialog.text = "And that's why you have decided that Beck tipped off Fleetwood to attack the brigantine? What rubbish! Fleetwood is an ordinary pirate; he only attacks merchant ships. Why would he need the papers, which, by the way, only contained bookkeeping information?";
			link.l1 = "";
			link.l1.go = "ArestLucas_10";		
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_10":
			StartInstantDialog("Lucas", "ArestLucas_11", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_11":
			dialog.text = "Mynheer, kurier przewoził także inne ważne dokumenty Kompanii - nie tylko zwykłe raporty. A teraz wszystkie są w rękach Brytyjczyków. Dlatego postanowiłem aresztować Becka.";
			link.l1 = " ";
			link.l1.go = "ArestLucas_12";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));			
		break;
		
		case "ArestLucas_12":
			StartInstantDialog("Stivesant", "ArestLucas_13", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_13":
			dialog.text = "Cholera jasna! To jest prawdziwe uzurpacja władzy! Czy w ogóle zdajesz sobie sprawę, co robisz, Lucasie? Gdzie jest kapitan kurierowej brygantyny?";
			link.l1 = "";
			link.l1.go = "ArestLucas_14";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
			LAi_ActorAnimation(npchar, "dialog_stay13", "1", 4.5);
		break;
		
		case "ArestLucas_14":
			StartInstantDialog("Lucas", "ArestLucas_15", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_15":
			dialog.text = "Pojechał do Philipsburga, Mynheer.";
			link.l1 = "";
			link.l1.go = "ArestLucas_16";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));	
		break;
		
		case "ArestLucas_16":
			StartInstantDialog("Stivesant", "ArestLucas_17", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_17":
			dialog.text = "Dobrze, więc. Rozkazałem uwolnić Becka. Zostanie tu przyprowadzony, a potem we trójkę porozmawiamy.";
			link.l1 = "";
			link.l1.go = "ArestLucas_18";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_18":
			StartInstantDialog("Lucas", "ArestLucas_19", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_19":
			dialog.text = "Dobrze, nie mam nic przeciwko. Nas trzech - w porządku. Porozmawiajmy.";
			link.l1 = " ";
			link.l1.go = "ArestLucas_20";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));	
		break;
		
		case "ArestLucas_20":
			DialogExit();
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "governor1", "DoubleTalkWithLucas", -1.0);
			locCameraFromToPos(4.70, 2.92, -4.19, false, 3.60, -0.70, 5.00);
			DoQuestCheckDelay("PiterTalkWithLucas_2", 4.5);
		break;
		
		case "ArestLucas_40":
			dialog.text = "Zapłacisz za swoje bezprawie, Rodenburg! Twoje oskarżenia są absurdalne. Nawet nie pozwoliłeś mi zobaczyć kapitana brygantyny! Nie przedstawiłeś żadnych dowodów, wszystkie oskarżenia pochodzą od Ciebie osobiście.\nPrzysięgam Panu, jestem niewinny! Nie mam i nie miałem żadnego kontaktu z Brytyjczykami!";
			link.l1 = "";
			link.l1.go = "ArestLucas_41";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_41":
			StartInstantDialog("Lucas", "ArestLucas_42", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_42":
			dialog.text = "O, naprawdę?  Więc jak Fleetwood dowiedział się o naszym brygantynie i że na pokładzie były nie tylko zwykłe dokumenty?";
			link.l1 = "";
			link.l1.go = "ArestLucas_43";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Villemstad_Mayor"));
		break;
		
		case "ArestLucas_43":
			dialog.text = "... ";
			link.l1 = "Rodenburg kłamie. Richard Fleetwood nie mógł zaatakować brygantyny kurierskiej.";
			link.l1.go = "ArestLucas_44";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			sld = characterFromId("Stivesant");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			sld = characterFromId("Villemstad_Mayor");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
		break;
		
		case "ArestLucas_44":
			dialog.text = "A kimże ty jesteś, panie? Na jakiej podstawie wygłaszasz takie oświadczenia?";
			link.l1 = "Nazywam się "+GetFullName(pchar)+"Osobiście wyeliminowałem kapitana Fleetwooda, zwabiając go w pułapkę. Jego ciało zjadają mewy na brzegach Turks. Urzędnicy nie zdołali nas, holenderskich kupców, ochronić przed jego agresją, więc sam go wykończyłem. A stało się to zanim brygantyna kurierska została splądrowana...";
			link.l1.go = "ArestLucas_46";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "ArestLucas_46":
			dialog.text = " ";
			link.l1 = "Fleetwood po prostu nie mógł tego zrobić, był już martwy. Dowiedziałem się od miejscowych w tawernie, że Mathias Beck został aresztowany, więc postanowiłem zbadać tę sprawę, bo zawsze wierzyłem, że pan Beck to człowiek o nieskazitelnej reputacji...";
			link.l1.go = "ArestLucas_47";			
		break;
		
		case "ArestLucas_47":
			dialog.text = "";
			link.l1 = "Ludzie w porcie mówili mi, że załadowałeś swój szybek wszelkiego rodzaju kryminalistami i najemnikami, a strażnicy Kompanii zostali na lądzie. Śledziłem twój statek i go pojmałem, zabijając każdego zbója, którego wynająłeś. Przesłuchałem kapitana Longwaya, w zamian za jego wolność wszystko mi opowiedział, Mynheer Rodenburg...";
			link.l1.go = "ArestLucas_48";			
		break;
		
		case "ArestLucas_48":
			dialog.text = "";
			link.l1 = "Planowałeś przejąć władzę nad Curacao i zleciłeś Longwayowi zatopienie galeonu pana Stuyvesanta. Znając twoje metody, jestem pewien, że biedny kapitan brygantyny nie żyje. Musiałeś zorganizować atak na statek kurierski, aby stworzyć precedens, czyż nie? A ten czyn został przeprowadzony przez twojego zabójcę, zwanego Jacobem van Bergiem? Longway opowiedział mi wiele o tym człowieku.";
			link.l1.go = "ArestLucas_49";			
		break;
		
		case "ArestLucas_49":
			dialog.text = "To... to jest jawne kłamstwo! O czym ty mówisz, Mynheer? Kim do diabła jesteś?";
			link.l1 = "Jestem niezależnym kapitanem, który chciał oczyścić morze i ląd z tego łajdaka Fleetwooda i który wplątał się w wasze polityczne intrygi! Ostrzegłem pana Stuyvesanta o niebezpieczeństwie, w jakim się znalazł. I jestem tu, by położyć kres waszym grabieżom na Curaçao - razem z legalnymi władzami!";
			link.l1.go = "ArestLucas_50";			
		break;
		
		case "ArestLucas_50":
			dialog.text = "Co za bezczelność! Odpowiesz za swoje słowa, Mynheer 'niezależny kapitanie'! Ty...";
			link.l1 = "";
			link.l1.go = "ArestLucas_51";
		break;
		
		case "ArestLucas_51":
			StartInstantDialog("Stivesant", "ArestLucas_52", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_52":
			dialog.text = "Dość, Lucas. Zapłacisz za swoje zbrodnie! Słyszałem i widziałem wystarczająco. Lucas Rodenburg, aresztuję cię za próbę zamachu na życie dyrektora Kompanii, próbę zdobycia władzy siłą i podejrzenie o zamordowanie kapitana statku kurierskiego.\nPoza tym, jestem pewien, że podczas oficjalnego śledztwa odkryjemy więcej ciekawych fragmentów twojej biografii. Zostaniesz zatrzymany i dostarczony do Amsterdamu, gdzie zostaniesz osądzony. Zabierzcie go!";
			link.l1 = "";
			link.l1.go = "ArestLucas_53";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
			sld = characterFromId("Lucas");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromID("Stivesant"));					
		break;
		
		case "ArestLucas_53":
			StartInstantDialog("Lucas", "ArestLucas_54", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_54":
			dialog.text = "Ale...";
			link.l1 = "";
			link.l1.go = "ArestLucas_55";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));			
		break;
		
		case "ArestLucas_55":
			DialogExit();
			LAi_ActorTurnToCharacter(pchar, characterFromID("Lucas"));
			sld = characterFromId("Lucas");
			LAi_SetImmortal(sld, true);//защита от хитреца
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "goto", "goto6");
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "LucasGoToPrison", -1);
			for (i=3; i<=5; i++)
			{
			sld = characterFromId("StivesantGuard_"+i);
			LAi_ActorFollow(sld, characterFromID("Lucas"), "", -1);
			}
			LAi_SetActorType(PChar);
			locCameraFromToPos(4.70, 2.92, -4.19, false, -4.60, -1.70, 5.50);
			DoQuestFunctionDelay("SecondDayInVillemstad", 6.0);
		break;
		
		case "Stivesant_10":
			dialog.text = "Kapitanie "+GetFullName(pchar)+" ! W imieniu administracji kolonii Willemstad uprzejmie proszę o przyjęcie naszych szczerych podziękowań za Twoje działania, które pomogły nam aresztować tego niebezpiecznego przestępcę. Chciałbym również podziękować Ci osobiście, ponieważ prawdopodobnie jestem Ci winien życie.";
			link.l1 = "Działałem dla dobra wszystkich holenderskich kolonii, Mynheer.";
			link.l1.go = "Stivesant_11";			
		break;
		
		case "Stivesant_11":
			dialog.text = "Twoja skromność wzbudza szacunek, przyjacielu. Teraz chciałbym załatwić kilka formalności: ponieważ zdobyłeś Meifeng wyłącznie w dobrych celach i w trudnych okolicznościach, nie może być żadnych roszczeń. Jednakże ten statek należy do Kompanii i uprzejmie proszę o jego zwrot.";
			link.l1 = "Oczywiście, Mynheer.";
			link.l1.go = "Stivesant_12";			
		break;
		
		case "Stivesant_12":
		//удаляем Мейфенг
		DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//удаляем атрибут квестового корабля
		if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MAYFANG)
		{
			pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
			pchar.Ship.name = "A boat";
			SetBaseShipData(pchar);
			SetCrewQuantityOverMax(PChar, 0);//сажаем на тартану
		}
		else
		{
			for(i = 1; i < COMPANION_MAX; i++)
			{
			int iTemp = GetCompanionIndex(PChar, i);
			if(iTemp > 0)
				{
				sld = GetCharacter(iTemp);
				if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
					{
						pchar.questTemp.HWIC.Self.CompanionIndex = sld.Index;
						sld = GetCharacter(sti(pchar.questTemp.HWIC.Self.CompanionIndex));
						RemoveCharacterCompanion(PChar, sld);
						AddPassenger(PChar, sld, false);
					}
				}
			}
		}
			dialog.text = "Proszę przyjdź jutro do mojej rezydencji - zostaniesz nagrodzony w imieniu Republiki Wolnych Prowincji za swoje czyny w jej najlepszym interesie. Uprzejmie proszę, abyś nie opuszczał miasta.";
			link.l1 = "Dobrze, panie. Przyjdę jutro.";
			link.l1.go = "Stivesant_13";			
		break;
		
		case "Stivesant_13":
			DialogExit();
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			sld.dialog.currentnode = "Bek_2";
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "Bek_2":
			dialog.text = "Chciałbym również osobiście podziękować ci, Kapitanie, za twój duch przedsiębiorczości i pomoc w odpowiednim czasie. Nie zapomnij przyjść tu jutro, przygotuję dla ciebie cenny prezent.";
			link.l1 = "Dziękuję, Panie Beck. Będę tam!";
			link.l1.go = "Bek_3";			
		break;
		
		case "Bek_3":
			DialogExit();
			pchar.quest.Award_FromPiter.win_condition.l1 = "Timer";
			pchar.quest.Award_FromPiter.win_condition.l1.date.hour  = 9.0;
			pchar.quest.Award_FromPiter.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Award_FromPiter.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Award_FromPiter.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Award_FromPiter.function = "OpenResidenceDoor";
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Villemstad_town", "reload5_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload10_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload3_back", true);//закрыть вход в резиденцию
			LocatorReloadEnterDisable("Villemstad_town", "reloadR2", true);//закрыть боковой вход в резиденцию
			AddQuestRecord("Holl_Gambit", "3-53");
			DoQuestReloadToLocation("Villemstad_prison", "goto", "goto23", "TalkWithLucasPrisoner");
			for (i=4; i<=5; i++)
			{
				sld = characterFromId("StivesantGuard_"+i);
				sld.lifeday = 0;//подчистим солдат
			}
		break;
		
		case "Stivesant_14":
			dialog.text = " "+GetFullName(pchar)+", w imieniu Republiki Wolnych Prowincji zostajesz niniejszym nagrodzony osobistą bronią i kwotą 100 000 pesos za inicjatywę podjętą w likwidacji wroga wszystkich Holendrów, przestępcy państwowego Richarda Fleetwooda. Gratulacje!";
			link.l1 = "Dziękuję, Mynheer Styuvesant!";
			link.l1.go = "Stivesant_15";			
		break;
		
		case "Stivesant_15":
			dialog.text = "Także, za bezprecedensową odwagę, za ujawnienie zdradzieckiego spisku wewnątrz Kompanii i za ryzykowną operację pojmania byłego wiceprezesa Kompanii, zostajesz nagrodzony 150 000 pesos. Będziesz również mógł podpisywać kontrakty z Holenderską Kompanią Zachodnioindyjską\nJestem pewien, że nasz nowy wicedyrektor znajdzie dobrze płatną pracę dla tak dzielnego kapitana jak ty.";
			link.l1 = "Dziękuję! Będę o tym pamiętał.";
			link.l1.go = "Stivesant_16";			
		break;
		
		case "Stivesant_16":
			AddMoneyToCharacter(pchar, 250000);
			GiveItem2Character(pchar, GetGeneratedItem("blade_16")); // belamour legendary edition используем GetGeneratedItem иначе пачка одинаковых клинков из первой части массива
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			dialog.text = "Miej na uwadze, że zawsze możesz liczyć na moją pomoc w jakichkolwiek interesach, dopóki działasz po stronie i w interesie Holandii. Teraz posłuchajmy, co ma do powiedzenia gubernator Willemstad, Matthias Beck.";
			link.l1 = "";
			link.l1.go = "Stivesant_17";			
		break;
		
		case "Stivesant_17":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			LAi_SetActorType(sld);
			sld.dialog.currentnode = "Bek_4";
			LAi_ActorDialog(sld, pchar, "", -1, 0);		
		break;
		
		case "Bek_4":
			dialog.text = "Wyrażam szczerą wdzięczność, Kapitanie, za odwagę i wnikliwość w odkryciu spisku przeciwko państwu. Chciałbym wręczyć Ci ten cenny instrument nawigacyjny, który jest nieoceniony dla każdego człowieka wojennego.";
			link.l1 = "Dziękuję, Mynheer Beck";
			link.l1.go = "Bek_5";			
		break;
		
		case "Bek_5":
			GiveItem2Character(pchar, "bussol");
			dialog.text = "Chciałbym, abyś wiedział: jesteś teraz moim przyjacielem i to dla mnie wiele znaczy. Zawsze będziesz mile widzianym gościem w mojej rezydencji. Przybywaj w każdej chwili i z jakiegokolwiek powodu - z radością udzielę ci wszelkiej pomocy, której możesz potrzebować.";
			link.l1 = "Cieszę się, że to słyszę, Mynheer!";
			link.l1.go = "Bek_6";			
		break;
		
		case "Bek_6"://наведем порядок в городе
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-54");
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			LAi_SetHuberStayType(sld);
			sld.Dialog.Filename = "Common_Mayor.c";//patch-8
			sld.dialog.currentnode = "First time";
			sld.quest.meeting = "1";
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("StivesantGuard_"+i);
				sld.lifeday = 0;//подчистим солдат
			}
			sld = characterFromId("Stivesant");
			LAi_ActorGoToLocator(sld, "goto", "goto6", "StivesantSitDown", -1);
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", false);
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			DelMapQuestMarkCity("Villemstad");
		break;
		
		case "Bek_7":
			dialog.text = "Holandia jest z ciebie dumna, Mynheer. Kapitanowie tacy jak ty są kręgosłupem holenderskiej floty na Karaibach. Oto jest, proszę przyjąć swoją nagrodę.";
			link.l1 = "Dziękuję, Mynheer. Jestem zaszczycony służąc Holandii!";
			link.l1.go = "Bek_8";
		break;
		
		case "Bek_8":
			TakeNItems(pchar, "gold_dublon", 1000);
			ChangeCharacterComplexReputation(pchar,"authority", 5);
			ChangeCharacterNationReputation(pchar, HOLLAND, 20);
			DialogExit();
			sld = characterFromId("Lucas");
			LAi_SetActorType(sld);
			sld.dialog.currentnode = "LucasAward_2";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Stivesant_18":
			dialog.text = "Miło cię widzieć. Jak się masz?";
			link.l1 = "U mnie wszystko w porządku. Wpadłem tylko, żeby cię zobaczyć.";
			link.l1.go = "exit";	
			NextDiag.TempNode = "Stivesant_18";
		break;
		
		// Jason НСО
		case "Stivesant_19":
			if (ChangeCharacterHunterScore(pchar, "holhunter", 0) > 10)
			{
				dialog.text = "Spójrz, kto to jest! To "+GetFullName(pchar)+". Niedawno wysłaliśmy naszych łowców głów, którzy mieli cię tu sprowadzić. A ta usługa kosztowała niemało.";
				link.l1 = "Uhm... Powinienem iść...";
				link.l1.go = "arest";
				break;
			}
			// belamour legendary edition фикс проверки мундира с мушкетом
			if (pchar.questTemp.Patria == "epizode_4" && IsUniformEquip())
			{
				dialog.text = "Jesteś kapitanem francuskiej marynarki? Dobrze, nie mam dużo czasu, ale wysłucham, co masz do powiedzenia. Co cię tu sprowadza?";
				link.l1 = "Mynheer Stuyvesant, przybyłem z Saint Christopher z wiadomością od generała-gubernatora francuskich kolonii, Kawalera de Poincy.";
				link.l1.go = "Stivesant_20";
			}
			else
			{
				dialog.text = "Przepraszam, Kapitanie, ale jestem teraz niezwykle zajęty i nie mogę poświęcić ci wystarczająco dużo czasu. Porozmawiaj z panem Mathiasem Beckiem, niech usłyszy, co masz do powiedzenia.";
				link.l1 = "Hmm...";
				link.l1.go = "Stivesant_19_1";
			}
		break;
		
		case "Stivesant_19_1":
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_19";
		break;
		
		case "Stivesant_20":
			sld = characterFromId("Patria_FlautCap");
			dialog.text = "Od Chevaliera de Poincy? Zdecydowanie nie spodziewałem się, że to zajmie tak mało... ekhm... jak się miewa Chevalier?";
			link.l1 = "Wszystko w porządku, Mynheer. Monsieur de Poincy polecił mi dostarczyć ten list do ciebie. Moim drugim zadaniem było eskortowanie '"+sld.ship.name+" z ładunkiem dla twojej kompanii do portu w Willemstad. Statek jest przy nabrzeżu, a ładunek nie został uszkodzony.";
			link.l1.go = "Stivesant_21";
		break;
		
		case "Stivesant_21":
			dialog.text = "Flota z ładunkiem dla naszej kompanii? Intrygujące... A list, kapitanie?";
			link.l1 = "Proszę. Weź to.";
			link.l1.go = "Stivesant_22";
		break;
		
		case "Stivesant_22":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "Hmmm... (czytając). Inspekcja z metropolii... Ahem... Huh, cóż... to interesujące, he-he... A tak przy okazji, Kapitanie, słyszałem, że Francja jest w stanie wojny z Hiszpanią na Karaibach? Oblężenie i złupienie fortu San Jose, zniszczenie hiszpańskiej eskadry wojennej u wschodnich wybrzeży Kuby...";
			link.l1 = "U zachodniego wybrzeża Hispanioli, przy Port-au-Prince, Mynheer. A jedynym celem oblężenia San Jose było uzyskanie odszkodowania finansowego od Hiszpanów za ich atak na Saint-Pierre. Od dłuższego czasu mamy złe stosunki z Hiszpanią... Kiedy powinienem wrócić po odpowiedź?";
			link.l1.go = "Stivesant_23";
		break;
		
		case "Stivesant_23":
			dialog.text = "Nie będę cię zatrzymywał, kapitanie, jesteś człowiekiem wojskowym, pewnie masz wiele spraw na głowie i jestem pewien, że kawaler niecierpliwie czeka na twój powrót. Bądź tak uprzejmy i poczekaj tutaj, w salonie, przez dwie godziny, aż skomponuję odpowiedź na ten list. Usiądź i odpocznij tutaj, zostaniesz poczęstowany winem lub rumem, jeśli sobie życzysz...";
			link.l1 = "Moja wdzięczność, Mynheer, wolałbym kieliszek wyśmienitego wina...";
			link.l1.go = "Stivesant_24";
		break;
		
		case "Stivesant_24":
			chrDisableReloadToLocation = true;//закрыть локацию
			pchar.quest.Patria_CureerTimeOver.over = "yes"; //снять таймер
			pchar.quest.Patria_CureerFail.over = "yes"; //снять прерывание
			sld = characterFromId("Patria_FlautCap");
			RemoveCharacterCompanion(pchar, sld);
			sld.lifeday = 0;
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_25";
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "Villemstad_townhall", "goto", "goto6");
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "Patria_StivesantWait", -1);
			pchar.questTemp.Patria = "epizode_4_return";
		break;
		
		case "Stivesant_25":
			GiveItem2Character(pchar, "Reserve_item_01");
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_2");
			dialog.text = "Odpowiedź dla monsieur de Poincy jest gotowa. Proszę, weź ją... Powodzenia, Kapitanie.";
			link.l1 = "Dziękuję, panie. Żegnaj!";
			link.l1.go = "Stivesant_26";
		break;
		
		case "Stivesant_26":
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_19";
			chrDisableReloadToLocation = false;
			AddQuestRecord("Patria", "23");
			SetFunctionTimerCondition("Patria_CureerBackOver", 0, 0, 31, false);
		break;
		
		case "Stivesant_27":
			if (ChangeCharacterHunterScore(pchar, "holhunter", 0) > 10)
			{
				dialog.text = "Popatrz, kto to! To "+GetFullName(pchar)+". Ostatnio wysłaliśmy naszych łowców głów, którzy mieli cię tu sprowadzić. A ta usługa kosztowała niemało.";
				link.l1 = "Uhm... Powinienem iść...";
				link.l1.go = "arest";
				break;
			}
			if (pchar.questTemp.Patria == "epizode_6" && IsUniformEquip())
			{
				dialog.text = "Przyszedłeś znów z wiadomością od gubernatora generalnego Philippe'a de Poincy, czyż nie?";
				link.l1 = "Tak, Mynheer Stuyvesant. Na brzegach Sint Maarten doszło do nieprzyjemnego nieporozumienia - statek przewożący inspektora z Paryża, barona Noela Forgeta, został ostrzelany przez fort Philipsburg, i...";
				link.l1.go = "Stivesant_28";
			}
			else
			{
				dialog.text = "Przepraszam, kapitanie, ale jestem teraz niezwykle zajęty i nie mogę poświęcić ci wystarczającej uwagi. Porozmawiaj z panem Mathiasem Beckiem, niech on usłyszy, co masz do powiedzenia.";
				link.l1 = "Hmm...";
				link.l1.go = "Stivesant_27_1";
			}
		break;
		
		case "Stivesant_27_1":
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_27";
		break;
		
		case "Stivesant_28":
			if (pchar.questTemp.HWIC.Detector == "holl_win" || pchar.questTemp.HWIC.Detector == "self_win")
			{
				dialog.text = "I dlatego jesteś tutaj, kapitanie. Nie będę wchodził w dyplomatyczne dyskusje: powiedz Kawalerowi, że już nie zarządza Sint Maarten. Dość z niego. A co do inspekcji z macierzystego państwa - niech coś wymyśli, dla de Poincy nigdy nie było trudno przewrócić wszystko do góry nogami.";
				link.l1 = "Czy mam mu dokładnie to powiedzieć?";
				link.l1.go = "Stivesant_29";
			}
			else
			{
				dialog.text = "I dlatego właśnie jesteście tutaj, Kapitanie. Nie będę wdawał się w dyplomatyczne dyskusje: wasz władca był ostatnio zbyt chciwy na Sint Maarten, więc nadeszła pora, by pohamować jego nienasycony apetyt. I wierzę, że on doskonale to rozumie. Do was, Kapitanie Charles de Maure, również mamy pytania dotyczące ostatnich wydarzeń związanych z brytyjskim bandytą o imieniu Richard Fleetwood, więc będziecie musieli tutaj zostać na jakiś czas.\nSierżancie! Zabierzcie broń kapitana i zaprowadźcie go do biura komendanta!";
				link.l1 = "Opóźnianie francuskiego oficera na służbie jest niedopuszczalne!";
				link.l1.go = "Stivesant_31";
			}
		break;
		
		case "Stivesant_29":
			dialog.text = "Nie mógłbym tego lepiej ująć, kapitanie. Twój dowódca wszystko zrozumie, ale nie musisz się w to wgłębiać, to nic nie zmieni. Życzę ci wszystkiego najlepszego. Sierżancie, odprowadź pana Charlesa de Maure do wyjścia!";
			link.l1 = "...";
			link.l1.go = "Stivesant_30";
		break;
		
		case "Stivesant_30":
			DialogExit();
			DoQuestReloadToLocation("Villemstad_town", "reload", "reload3", "Patria_DiplomatGetOut");
		break;
		
		case "Stivesant_31":
			dialog.text = "Niestety, mam inne zdanie. Sierżancie! W razie oporu, użyj siły!";
			link.l1 = "Jeszcze nie wiesz, z kim masz do czynienia, Mynheer...";
			link.l1.go = "Stivesant_32";
		break;
		
		case "Stivesant_32":
			DialogExit();
			Patria_DiplomatFight();
		break;
		
		case "Stivesant_33":
			dialog.text = "To trochę dziwne widzieć cię, kapitanie Charles de Maure, w tej roli... Mam nadzieję, że możesz zagwarantować immunitet tym, którzy przychodzą do ciebie na negocjacje..";
			link.l1 = "Możesz być tego pewien, Mynheer Stuyvesant.";
			link.l1.go = "Stivesant_34";
		break;
		
		case "Stivesant_34":
			dialog.text = "Więc, czy możesz dać mi możliwość przeczytania umowy, którą przygotowałeś? Jak rozumiem, zawiera ona treść listu?";
			link.l1 = "Dokładnie, Mynheer, tylko w oficjalnej formie. Ze strony Francji - przywrócenie stosunków do neutralnych, rezygnacja z jakichkolwiek roszczeń do wyspy Sint Maarten. Ze strony Anglii - koniec wojny handlowej. Szczegóły są opisane tutaj... I oczywiście, finansowe odszkodowanie za straty, które ponieśliśmy z powodu działań wojennych, które zainicjowaliście.";
			link.l1.go = "Stivesant_35";
		break;
		
		case "Stivesant_35":
			dialog.text = "Proszę bądź tak uprzejmy i daj mi ten dokument.";
			link.l1 = "Oczywiście.";
			link.l1.go = "Stivesant_36";
		break;
		
		case "Stivesant_36":
			dialog.text = "...(czytając)...";
			link.l1 = "... ";
			link.l1.go = "Stivesant_37";
		break;
		
		case "Stivesant_37":
			LAi_Fade("", "");
			dialog.text = "Skoro nie zostawiłeś mi wyboru, podpiszę tę umowę. Ale dla mnie ochrona Willemstad i jego mieszkańców jest najważniejsza.";
			link.l1 = "Wówczas zatwierdzimy wszystkie trzy kopie podpisami. Jestem upoważniony przez gubernatora generalnego Philippe'a de Poincy, aby podpisać dokument po stronie Francji, pułkownik Doily podpisze go po stronie Anglii.";
			link.l1.go = "Stivesant_38";
		break;
		
		case "Stivesant_38":
			dialog.text = "...(podpisywanie)...";
			link.l1 = "Doskonale! Teraz powinniśmy to podpisać...";
			link.l1.go = "Stivesant_39";
		break;
		
		case "Stivesant_39":
			LAi_Fade("", "");
			dialog.text = "Zatem, wierzę, że teraz odwołasz oblężenie?";
			link.l1 = "Bez wątpienia. Mam nadzieję, że wszystkie warunki umowy będą przestrzegane przez stronę holenderską bez naruszeń.";
			link.l1.go = "Stivesant_40";
		break;
		
		case "Stivesant_40":
			dialog.text = "Jeśli nie będzie naruszeń ze strony Anglii lub Francji, to będziemy przestrzegać warunków umowy, nie martw się.";
			link.l1 = "Zawsze lepiej handlować niż walczyć, Mynheer Stuyvesant. A teraz możesz bezpiecznie wrócić do Willemstad. Oblężenie zostanie zniesione, a nasza eskadra wkrótce opuści wody Curaçao.";
			link.l1.go = "Stivesant_41";
		break;
		
		case "Stivesant_41":
			DialogExit(); // Стайвесант уходит, подходит д'Ойли
			Patria_CuracaoStivesantGo();
		break;
		
		case "Stivesant_42":
			dialog.text = "Więc, czy jesteś baronem Noelem Forgetem? Huh, a ty musisz być samym monsieur Charlesem de Maure! Witaj, wiceadmirał! Jest powód, dla którego jesteś znany jako najbardziej przebiegły intrygant archipelagu - nigdy nie wiadomo, po której stronie jesteś w danym momencie...";
			link.l1 = "Wiceadmirał jest po stronie króla i waszej, jego szczerze oddanego przedstawiciela, w tej chwili.";
			link.l1.go = "Stivesant_43";
		break;
		
		case "Stivesant_43":
			dialog.text = "Król jest daleko stąd, podobnie jak Francja, baronie, ale Saint Christopher i Chevalier de Poincy są blisko. On jest prawdziwym właścicielem francuskich kolonii. De facto... Jednakże, czy jesteś tutaj, aby zdobyć coś, co skompromituje de Poincy w oczach ministra finansów?";
			link.l1 = "Dokładnie, Mynheer.";
			link.l1.go = "Stivesant_44";
		break;
		
		case "Stivesant_44":
			dialog.text = "Posiadam takie dokumenty. To cały rejestr z moimi i de Poincy'ego rozliczeniami dotyczącymi kopalni i innych spraw. Znajdziesz w nim również całą masę dokumentów związanych z tym interesem, z osobistym podpisem Philippe'a de Poincy. Gwarantuję, że zawartość tych papierów w rękach zainteresowanej osoby zatopi Kawalera głębiej niż dno Morza Karaibskiego.";
			link.l1 = "Czego chcesz za tę księgę?";
			link.l1.go = "Stivesant_45";
		break;
		
		case "Stivesant_45":
			dialog.text = "Sprzedaję to za bezcen. Zaledwie milion peso w srebrze.";
			link.l1 = "Milion peso?!!";
			link.l1.go = "Stivesant_46";
		break;
		
		case "Stivesant_46":
			dialog.text = "Zgadza się, Baronie. Ta suma przynajmniej częściowo pokryje straty spowodowane niedawną wojną. Dam ci radę: zwróć się do Monsieur Charlesa de Maure. Podczas swojej służby dla de Poincy i ahem... innych ludzi, prawdopodobnie zgromadził ogromną fortunę, a zdobycie miliona nie będzie dla niego problemem. Jestem tego prawie pewien.\nDam ci termin - jeden miesiąc. Po tym czasie, jeśli nie przyniesiesz wskazanej sumy, wyślę list do Kawalera, w którym opiszę szczegóły twojej wizyty u mnie. Możesz się domyślić, co stanie się potem.";
			link.l1 = "Szantażujesz mnie! Musisz zrozumieć, że nie mogę mieć miliona w koloniach!";
			link.l1.go = "Stivesant_47";
		break;
		
		case "Stivesant_47":
			dialog.text = "Oczywiście, rozumiem. Dlatego natychmiast wskazałem wam osobę, która ma ten milion. Jeśli monsieur de Maure odmówi, najlepiej, baronie, odpłyńcie do Europy, zanim Kawaler otrzyma mój list, w przeciwnym razie ryzykujecie, że zostaniecie tu na zawsze. Co do monsieur de Maure... oczywiście, straci swój admirałowy tytuł, ale wyjdzie z tego... a może nawet pozbędzie się de Poincy'ego swoimi metodami, co mi całkowicie odpowiada.\nNo cóż, panowie, słyszeliście mnie. Będę czekał na was z milionem za miesiąc w mojej rezydencji. Gwarantowane wolne wejście i wyjście.";
			link.l1 = "... ";
			link.l1.go = "Stivesant_48";
		break;
		
		case "Stivesant_48":
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			locCameraTarget(pchar);
			locCameraFollow();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = true;
			bDisableCharacterMenu = false;
			sld = CharacterFromID("Noel");
			sld.dialog.currentnode = "noel_84";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
			sld = CharacterFromID("Stivesant");
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "Patria_CondotierStivesantInHall", 12.0);
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("Stivesant_sold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
			}
		break;
		
		case "Stivesant_49":
			if (sti(pchar.money) >= 1000000)
			{
				dialog.text = "Nie miałem nawet wątpliwości, wiceadmirale Charles de Maure, że przyniesiesz mi te pieniądze. Być może nawet za mało od ciebie zażądałem, ale cóż... Baron to tylko pionek w twojej następnej grze, prawda? Stopień i pieniądze ci nie wystarczą, teraz chcesz zająć miejsce de Poincy, mam rację? Musisz przyznać, milion to mała suma za stanowisko Generalnego Gubernatora kolonii francuskich! Odzyskasz te pieniądze w ciągu kilku miesięcy, biorąc pod uwagę twój żelazny uchwyt.";
				link.l1 = "Weź milion, Mynheer. Chciałbym otrzymać obiecaną księgę.";
				link.l1.go = "Stivesant_50";
			}
			else
			{
				dialog.text = "Lepiej skup się na zbieraniu miliona, monsieur, zamiast tracić czas na bezsensowne wizyty.";
				link.l1 = "...";
				link.l1.go = "Stivesant_49_1";
			}
		break;
		
		case "Stivesant_49_1":
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_49";
		break;
		
		case "Stivesant_50":
			pchar.quest.Patria_CondotierStivesantTimeOver.over = "yes"; // снять таймер
			AddMoneyToCharacter(pchar, -1000000);
			GiveItem2Character(pchar, "Reserve_item_01");
			ref itm = ItemsFromID("Reserve_item_01");
			itm.picIndex = 15;
			itm.picTexture = "ITEMS_26";
			itm.price = 0;
			itm.Weight = 2.0;
			itm.name = "itmname_Reserve_item_01_1";
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_4");
			dialog.text = "Oczywiście, Wiceadmirał. I nie marszcz się: kiedy zostaniesz Generalnym Gubernatorem, zobaczysz, że Holenderska Kompania Zachodnioindyjska jest bardziej dochodowym partnerem biznesowym niż chciwi i wojowniczy Brytyjczycy. Czy nie wiesz, że jeśli dasz Brytyjczykowi palec, to weźmie całą rękę? Jeśli nie, nauczysz się tego na własnej skórze. Więc jeszcze się z tobą nie żegnam. Zachowaj swoje dokumenty. Mam nadzieję, że twój baron jest na tyle kompetentny, by pokonać Kawalera.";
			link.l1 = "Moje podziękowania. Żegnaj, Panie Stuvesant.";
			link.l1.go = "Stivesant_51";
		break;
		
		case "Stivesant_51":
			DialogExit();
			AddQuestRecord("Patria", "84");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", -1);
			pchar.quest.Patria_CondotierCabin.win_condition.l1 = "location";
			pchar.quest.Patria_CondotierCabin.win_condition.l1.location = "Curacao";
			pchar.quest.Patria_CondotierCabin.function = "Patria_CondotierCabin";
		break;
		
		case "vanberg_sold":
			dialog.text = "Ha-ha-ha! Spójrz na to! Jakub miał rację, jak zawsze - ten lis przybył na wyspę z dobrego powodu. Wydaje się, że w skrzyni jest całkiem sporo złota. Bardzo nieostrożnie z twojej strony, że przyszedłeś tu sam, przyjacielu. Ale z drugiej strony, to tylko ułatwia nam robotę!";
			link.l1 = "Te łotry mnie wytropiły! Nie spodziewałem się tego... Ale nie będę łatwą zdobyczą!";
			link.l1.go = "vanberg_sold_1";			
		break;
		
		case "vanberg_sold_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("vanberg_sold_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "PrepareMassakraInShore");
			AddDialogExitQuest("MainHeroFightModeOn");			
		break;
		
		case "Abihouselady":
			dialog.text = "Szukasz kogoś?";
			link.l1 = "Tak, to ja. Gdzie są Solomon i Abigail Shneur?";
			link.l1.go = "Abihouselady_1";			
		break;
		
		case "Abihouselady_1":
			dialog.text = "Już tu nie mieszkają. Po prostu nie było ich stać na to miejsce. Abigail, biedna dziewczyna, pracuje jako jedna ze służących gubernatora. Pracuje ciężko każdego dnia, by utrzymać siebie i ojca. Salomon pije codziennie w tawernie, nie może znieść tego, co się z nimi stało. Teraz mieszkają w małej chatce niedaleko morza...";
			link.l1 = "Och... Dobrze, dziękuję za informację. Muszę iść.";
			link.l1.go = "Abihouselady_2";
		break;
		
		case "Abihouselady_2":
			DialogExit();
			NextDiag.CurrentNode = "Abihouselady_3";
		break;
		
		case "Abihouselady_3":
			dialog.text = "Czego jeszcze chciałbyś się dowiedzieć, Mynheer?";
			link.l1 = "Nieważne, nie przejmuj się.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Abihouselady_3";
		break;
		
		//удаление Мейфенг при провале квеста
		case "TempOffGuard":
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//удаляем атрибут квестового корабля
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MAYFANG)
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
				pchar.Ship.name = "A boat";
				SetBaseShipData(pchar);
				SetCrewQuantityOverMax(PChar, 0);//сажаем на тартану
			}
			else
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
						iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							pchar.questTemp.HWIC.Self.CompanionIndex = sld.Index;
							sld = GetCharacter(sti(pchar.questTemp.HWIC.Self.CompanionIndex));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			dialog.text = "Kapitánie, przywłaszczyłeś sobie statek Holenderskiej Kompanii Zachodnioindyjskiej. Jestem upoważniony do jego konfiskaty i użycia siły w przypadku oporu. To rozkaz Petera Stuyvesanta.";
			link.l1 = "Cóż, jeśli to rozkaz samego Petera Stuyvesanta... Nie będę toczył wojny z Holandią z powodu statku. Weź go.";
			link.l1.go = "TempOffGuard_1";			
		break;
		
		case "TempOffGuard_1":
			dialog.text = "Dobrze, że kierujesz się rozsądkiem.";
			link.l1 = "... ";
			link.l1.go = "TempOffGuard_2";
		break;
		
		case "TempOffGuard_2":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;//открыть локацию
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");
		break;
		
		// Jason НСО
		case "arest":
			dialog.text = "Oczywiście, że nadszedł czas na wyjście, nawet będziesz miał towarzystwo. Strażnicy! Zabrać go!";
		    link.l1 = "Zmuszaj mnie!";
		    link.l1.go = "fight";
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_LockFightMode(Pchar, true); // ножками путь убегает
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); // не работает на бессмертного мера :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Hej, słuchaj no! Jako obywatel tego miasta, uprzejmie proszę cię, abyś nie chodził z wyciągniętym ostrzem.","Wiesz, jako obywatel tego miasta, uprzejmie proszę cię, byś nie chodził z obnażonym ostrzem.");
			link.l1 = LinkRandPhrase("Dobrze.","Zgoda.","Jak mówisz...");
			link.l1.go = "exit";
		break;
	}
}

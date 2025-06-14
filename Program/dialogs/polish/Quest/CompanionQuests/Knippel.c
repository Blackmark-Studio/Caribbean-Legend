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
			link.l1 = "Nic.";
			link.l1.go = "exit";
		break;
		
		// Квест "Длинные тени старых грехов"
		case "DTSG_Knippel_1":
			dialog.text = "O, co za upał dzisiaj. Możesz równie dobrze przywiązać kulę łańcuchową do nogi i skoczyć do morza, żeby pozbyć się tej duchoty!";
			link.l1 = "Ha-ha, Charlie!.. To dość ekstremalne środki, jeśli mnie pytasz. Ale nie miałbym nic przeciwko zwilżeniu gardła - naprawdę dziś zbyt gorąco. Jesteś z nami?";
			link.l1.go = "DTSG_Knippel_2";
		break;
		
		case "DTSG_Knippel_2":
			dialog.text = "Napijmy się lub dwa z tobą, Kapitanie? Zawsze!";
			link.l1 = "To lubię słyszeć. Ruszajmy!";
			link.l1.go = "DTSG_Knippel_3";
		break;
		
		case "DTSG_Knippel_3":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "", "", "", "DTSG_BasTerTavern", -1);
			FreeSitLocator("BasTer_tavern", "sit_base2");
			FreeSitLocator("BasTer_tavern", "sit_front2");
		break;
		
		case "DTSG_Ohotnik_1":
			dialog.text = "Hej, żeglarzu, wyglądasz, jakbyś wszystko już widział! Napijmy się i wymieńmy opowieściami? Ja stawiam!";
			link.l1 = "";
			link.l1.go = "DTSG_Ohotnik_1_Animation";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Knippel"));
			
		break;
		
		case "DTSG_Ohotnik_1_Animation":
			StartInstantDialogNoType("Knippel", "DTSG_Ohotnik_2", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_2":
			dialog.text = "Uh, nie, dzięki, kumplu. Przybyłem tu z moim Kapitanem. Znajdź kogoś innego.";
			link.l1 = "";
			link.l1.go = "DTSG_Ohotnik_2_Animation";
			LAi_tmpl_SetDialog(npchar, pchar, -1.0);
			locCameraFromToPos(5.57, 2.39, -4.63, true, 8.53, 2.07, 1.84);
		break;
		
		case "DTSG_Ohotnik_2_Animation":
			StartInstantDialog("DTSG_Ohotnik", "DTSG_Ohotnik_3", "Quest\CompanionQuests\Knippel.c");
			locCameraSleep(true);
		break;
		
		case "DTSG_Ohotnik_3":
			dialog.text = "Ha, taki obdartus jak ty ma takie wysokie mniemanie, tylko pije z kapitanami?";
			link.l1 = "";
			link.l1.go = "DTSG_Ohotnik_3_Animation";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Knippel"));
		break;
		
		case "DTSG_Ohotnik_3_Animation":
			StartInstantDialogNoType("Knippel", "DTSG_Ohotnik_4", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_4":
			dialog.text = "Wysokie mniemanie?! Służyłem przez dekady w Królewskiej Marynarce! I walczyłem nie dla lordów, ale dla zwykłych ludzi takich jak ty i ja, by zapewnić prawo i porządek wszędzie!..";
			link.l1 = "";
			link.l1.go = "DTSG_Ohotnik_4_Animation";
			LAi_tmpl_SetDialog(npchar, pchar, -1.0);
		break;
		
		case "DTSG_Ohotnik_4_Animation":
			StartInstantDialog("DTSG_Ohotnik", "DTSG_Ohotnik_5", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_5":
			dialog.text = "Dużo gadasz, ale pijesz tylko z kapitanami i szlachcicami! Wygląda na to, że Marynarka nauczyła cię tylko jak polerować działa, ha!";
			link.l1 = "";
			link.l1.go = "DTSG_Ohotnik_5_Animation";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Knippel"));
		break;
		
		case "DTSG_Ohotnik_5_Animation":
			StartInstantDialogNoType("Knippel", "DTSG_Ohotnik_6", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_6":
			dialog.text = "Wcisnę ci łańcuchową kulę w gardło, szczeniaku!";
			link.l1 = "Charlie, nie wariuj tak, to nie jest tego warte.";
			link.l1.go = "DTSG_Ohotnik_7";
			LAi_tmpl_SetDialog(npchar, pchar, -1.0);
		break;
		
		case "DTSG_Ohotnik_7":
			dialog.text = "Pozwól mi się tym zająć, Kapitanie. Honor marynarki jest zagrożony, muszę go bronić sam i nie chować się za nikim...";
			link.l1 = "";
			link.l1.go = "DTSG_Ohotnik_8";
		break;
		
		case "DTSG_Ohotnik_8":
			DialogExit();
			EndQuestMovie();
			locCameraSleep(false);
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			sld = CharacterFromID("Blaze");
			LAi_SetImmortal(sld, true);
			LAi_CharacterDisableDialog(sld);
			LAi_SetSitType(sld);
			sld = CharacterFromID("Baster_Smuggler");
			LAi_SetImmortal(sld, true);
			SetMainCharacterIndex(GetCharacterIndex("Knippel"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			sld = CharacterFromID("DTSG_Ohotnik");
			ChangeCharacterAddressGroup(sld, "BasTer_tavern", "tables", "stay7");
			DoQuestReloadToLocation("BasTer_tavern", "tables", "stay6", "DTSG_BasTerTavern_7");
		break;
		
		case "DTSG_Knippel_l0":
			dialog.text = "Dziękuję za czekanie, Kapitanie. Mam nadzieję, że nie zajęło mi to zbyt długo.";
			link.l1 = "Nie martw się o to. Nic ci nie jest? Ten łotr był całkiem dobry.";
			link.l1.go = "DTSG_Knippel_l1";
		break;
		
		case "DTSG_Knippel_l1":
			dialog.text = "Nie martw się, Kapitanie. Najważniejsze, że dostał to, na co zasłużył. Z jego ciała zabrałem jakiś klucz...";
			link.l1 = "";
			link.l1.go = "DTSG_Knippel_l2";
		break;
		
		case "DTSG_Knippel_l2":
			dialog.text = "Zabrałem jakiś klucz z jego ciała... Zastanawiam się, do czego może służyć?";
			link.l1 = "Podstawy, Charlie... Dla drzwi lub skrzyni, ha-ha. Powinniśmy porozmawiać z karczmarzem o tym łajdaku, to może się przydać.";
			link.l1.go = "DTSG_Knippel_l3";
			AddItems(pchar, "Key1", 1);
			Log_info("Charlie gave you the key.");
			PlaySound("interface\important_item.wav");
		break;
		
		case "DTSG_Knippel_l3":
			DialogExit();
			
			bDisableCharacterMenu = false;
			InterfaceStates.Buttons.Save.enable = true;
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			sld.location = "None";
			pchar.questTemp.DTSG_BasTerTavern = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
		break;
		
		case "DTSG_Knippel_20":
			dialog.text = "Niewiarygodne...";
			link.l1 = "Czy myślisz to samo, co ja, Charlie?";
			link.l1.go = "DTSG_Knippel_21";
		break;
		
		case "DTSG_Knippel_21":
			dialog.text = "Nie wiem, jak ty, panie, ale jestem zaskoczony, ile tu jest pieniędzy - wyglądał jak zwykły człowiek, nie kupiec czy szlachcic.";
			link.l1 = "To naprawdę niewiele, ale masz rację. Co mnie zaskakuje, to ten dziwny spalony list.";
			link.l1.go = "DTSG_Knippel_22";
		break;
		
		case "DTSG_Knippel_22":
			dialog.text = "Tak, to nie było zbyt mądre z jego strony - to jak strzelać łańcuchem do solidnego kadłuba. Powinien był całkowicie zniszczyć ten list.";
			link.l1 = "To prawda. Ale to nam nie pomaga - nie wiemy, kim on był ani z kim prowadził korespondencję. Chodźmy, Charlie, nic tu po nas.";
			link.l1.go = "DTSG_Knippel_23";
		break;
		
		case "DTSG_Knippel_23":			//КОНЕЦ ЭТАПА 1
			DialogExit();
			Return_KnippelOfficer();

			AddQuestRecord("DTSG", "2");
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			pchar.questTemp.DTSG_Nastoroje1 = true;
		break;
		
		case "DTSG_Ohotnik_10":
			dialog.text = "Tak wiele o twojej chełpionej Królewskiej Marynarce, pfft!";
			link.l1 = "Charlie był dobrym, porządnym człowiekiem. I był kanonierem, a nie marines.";
			link.l1.go = "DTSG_Ohotnik_11";
		break;
		
		case "DTSG_Ohotnik_11":
			dialog.text = "Kanoniery?! A więc, dokładnie tak jak mówiłem, ha-ha-ha! I nie patrz tak groźnie - powinieneś był wiedzieć, kogo bierzesz do swojej załogi.";
			link.l1 = "Powinieneś był wiedzieć, z kim zadzierasz.";
			link.l1.go = "DTSG_Ohotnik_Agressia_1";
			link.l2 = "Żyjesz tylko dlatego, że zwyciężyłeś uczciwie, więc trzymaj swój zgniły język za zębami i wynoś się stąd.";
			link.l2.go = "DTSG_Ohotnik_Otpustil_1";
		break;
		
		case "DTSG_Ohotnik_Otpustil_1":
			dialog.text = "Cóż, myślałem, że będę musiał walczyć z tobą następnym razem. Miło słyszeć, że honor coś dla ciebie znaczy.";
			link.l1 = "To nie były tylko puste słowa dla Charliego. Ale co do ciebie, mam wątpliwości. W każdym razie, to teraz już nie ma znaczenia.";
			link.l1.go = "DTSG_Ohotnik_Otpustil_2";
		break;
		
		case "DTSG_Ohotnik_Otpustil_2":			//ПРОВАЛ ЭТАПА 1
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			npchar.lifeday = 0;
			LAi_LocationDisableOfficersGen("BasTer_tavern", false);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			bDisableCharacterMenu = false;
			InterfaceStates.Buttons.Save.enable = true;
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar, "authority", -3);
			ChangeCharacterComplexReputation(pchar, "fame", -3);	
		break;
		
		case "DTSG_Ohotnik_Agressia_1":
			dialog.text = "Z kim to niby zadarłem, z rozpieszczonym słabeuszem?! Widziałeś w ogóle swoje własne cienkie wąsy?..";
			link.l1 = "Na pewno wiesz, jak naciskać na guziki... Tym bardziej satysfakcjonujące będzie wyładować na tobie swoją złość.";
			link.l1.go = "DTSG_Ohotnik_Agressia_2";
		break;
		
		case "DTSG_Ohotnik_Agressia_2":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			sld = CharacterFromID("DTSG_Ohotnik");
			DeleteAttribute(sld, "CantLoot");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_Ohotnik_Agressia_3");
			LAi_SetFightMode(pchar, true);
		break;
		
		case "DTSG_PiterAdams_1":
			dialog.text = "Poczekaj, Kapitanie. Widzę, że jesteś godnym i szlachetnym człowiekiem, czy możesz mi w czymś pomóc? To kwestia honoru.";
			link.l1 = "Może i mogę, ale o co chodzi? I dlaczego przyszedłeś do mnie? Wokół jest wielu szlachetnych ludzi. Z kim mam przyjemność rozmawiać, tak na marginesie?";
			link.l1.go = "DTSG_PiterAdams_2";
			InterfaceStates.Buttons.Save.enable = true;
		break;
		
		case "DTSG_PiterAdams_2":
			dialog.text = "Peter. Peter Adams. Widzę, że nie jesteś typowym rozpieszczonym potomkiem starej rodziny, lecz rzetelnym człowiekiem z pewną ręką.";
			link.l1 = "Ach, powinieneś mnie zobaczyć, gdy pierwszy raz przybyłem na Karaiby, panie. Ale mów, z czym potrzebujesz pomocy?";
			link.l1.go = "DTSG_PiterAdams_3";
		break;
		
		case "DTSG_PiterAdams_3":
			dialog.text = "Czy mógłbyś... pojedynkować się w moim imieniu, panie? Lokalny awanturnik, Ralph Faggle, obraził moją żonę. I nękał ją, publicznie. Prosto przed moimi oczami. Czy możesz to sobie wyobrazić?";
			link.l1 = "Nie ma zbyt wiele honoru w wyzwaniu na pojedynek, a potem chowaniu się za kimś innym. Zwłaszcza gdy stawką jest nie tylko twój osobisty honor, ale także honor kobiety, twojej żony. Czyż nie tak, Adams? Dlaczego nie możesz walczyć o swoją kobietę sam?";
			link.l1.go = "DTSG_PiterAdams_4";
		break;
		
		case "DTSG_PiterAdams_4":
			dialog.text = "I masz rację, absolutną rację. Ale ostatnio cierpiałem na ciężką gorączkę i ledwo stoję na nogach\nPrzyznaję, nie jest mi łatwo prosić cię o coś takiego. Gdyby mnie obraził, zniósłbym to. Ale nie, gdy na szali jest honor mojej żony! Nie jestem tchórzem, sir. Kiedyś służyłem w Królewskiej Marynarce i żeglowałem na tym samym statku co sam Robert Blake!";
			link.l1 = "Ja...";
			link.l1.go = "DTSG_PiterAdams_5";
		break;
		
		case "DTSG_PiterAdams_5":
			StartInstantDialog("Knippel", "DTSG_PiterAdams_6", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_PiterAdams_6":
			dialog.text = "Pomożemy ci.";
			link.l1 = "Charlie?..";
			link.l1.go = "DTSG_PiterAdams_7";
			CharacterTurnByChr(npchar, characterFromId("DTSG_PiterAdams"))
		break;
		
		case "DTSG_PiterAdams_7":
			dialog.text = "Jest to godny człowiek, Kapitanie. I niech mnie diabli wezmą na wieczność od kul armatnich, jeśli to nieprawda! Wielcy ludzie służyli z Admirałem Blake'iem. Walczyli razem, aby nikt nie uciskał zwykłych ludzi\nI dzięki niemu, Jamajka została uwolniona spod tyranii Hiszpanów!";
			link.l1 = "Nawet jeśli tak jest, nie pozwolę moim ludziom przerywać mi ani podejmować decyzji za mnie. Czy to jasne?";
			link.l1.go = "DTSG_PiterAdams_8";
			link.l2 = "Rozumiem, naprawdę. Jednakże, nawet nie miałem okazji odpowiedzieć. Postaraj się nie być tak pochopny i nie przerywaj mi w przyszłości, dobrze?";
			link.l2.go = "DTSG_PiterAdams_8";
			CharacterTurnByChr(npchar, pchar)
		break;
		
		case "DTSG_PiterAdams_8":
			dialog.text = "Powiem ci to, Kapitanie - jeśli nie pomożesz temu człowiekowi, stary Charlie porzuci wszystko i sam się za niego pojedynkować będzie, niech mnie zaraza weźmie!";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje1"))
			{
				link.l1 = "Spokojnie teraz, nie powiedziałem, że odmawiam pomocy. Prawda, panie Adams?";
				link.l1.go = "DTSG_PiterAdams_Nastoroje_1";
			}
			else
			{
				link.l1 = "Szczerze mówiąc, Charlie, sprawiasz, że wyglądam jak tchórz. A nigdy nim nie byłem. Powinieneś to wiedzieć.";
				link.l1.go = "DTSG_PiterAdams_NN_1";
			}
		break;
		
		case "DTSG_PiterAdams_NN_1":
			dialog.text = "Uh, przepraszam, Kapitanie, poniosło mnie.";
			link.l1 = "Jest w porządku. Ale trzymaj się w ryzach, dobrze?";
			link.l1.go = "DTSG_PiterAdams_NN_1_1";
		break;
		
		case "DTSG_PiterAdams_NN_1_1":
			StartInstantDialog("DTSG_PiterAdams", "DTSG_PiterAdams_NN_2", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_PiterAdams_NN_2":
			dialog.text = "";
			link.l1 = "Będę się pojedynkował za ciebie, panie Adams.";
			link.l1.go = "DTSG_PiterAdams_NN_3";
		break;
		
		case "DTSG_PiterAdams_NN_3":
			dialog.text = "Dziękuję, panie! Niech cię Bóg błogosławi!";
			link.l1 = "I niechaj Pan Bóg błogosławi też Lorda Protektora, prawda, panie Adams? Nie martw się, Charles de Maure nigdy nie zostawia uczciwego człowieka w tarapatach.";
			link.l1.go = "DTSG_PiterAdams_NN_4";
		break;
		
		case "DTSG_PiterAdams_NN_4":
			dialog.text = "Doceniamy to, panie de Maure, sir! Czy chciałby pan wpaść i zjeść kolację z Jane i mną?";
			link.l1 = "Cóż, ja...";
			link.l1.go = "DTSG_PiterAdams_NN_5";
		break;
		
		case "DTSG_PiterAdams_NN_5":
			dialog.text = "Nalegam!";
			link.l1 = "Cóż, tylko jeśli nalegasz. Dziękuję, Piotrze. Prowadź.";
			link.l1.go = "DTSG_PiterAdams_IdemKDomu";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_1":
			StartInstantDialog("DTSG_PiterAdams", "DTSG_PiterAdams_Nastoroje_2", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_PiterAdams_Nastoroje_2":
			dialog.text = "Oczywiście, że to prawda, panie! Chciałbyś przyjść z Jane i odpocząć po podróży?";
			link.l1 = "Dziękuję, ale czy wypada korzystać z twej gościnności?";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_3";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_3":
			dialog.text = "O, wręcz przeciwnie, Kapitanie, bylibyśmy urażeni, gdybyś nie przyszedł.";
			link.l1 = "Jakże mógłbym wtedy odmówić? Po tobie, Peter!";
			link.l1.go = "DTSG_PiterAdams_IdemKDomu";
		break;
		
		case "DTSG_PiterAdams_IdemKDomu":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "houseF1", "DTSG_PiterAdams_VDom", -1);
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "", -1);
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_1":
			dialog.text = "To my! Proszę, wejdź.";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje1"))
			{
				link.l1 = "Dziękuję. Czy mogę porozmawiać z Jane? Zapytaj ją, jak to się stało - potrzebuję wszystkich szczegółów.";
				link.l1.go = "DTSG_PiterAdamsRyadomSDomom_2";
			}
			link.l2 = "Bardzo przepraszam, ale po namyśle muszę odmówić. Mam pojedynek, do którego muszę się przygotować. A tak przy okazji, gdzie i kiedy jest zaplanowany?";
			link.l2.go = "DTSG_PiterAdamsRyadomSDomom_4";
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_2":
			dialog.text = "Oczywiście, sir. Chętnie porozmawiamy z tobą i odpowiemy na wszystkie twoje pytania. Proszę, za mną.";
			link.l1 = "Dziękuję, Piotrze.";
			link.l1.go = "DTSG_PiterAdamsRyadomSDomom_3";
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_3":
			DoQuestReloadToLocation("PortPax_houseF1", "reload", "reload1", "DTSG_PiterAdams_VDom_2");
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_4":
			dialog.text = "Jaka szkoda! Ale masz rację, oczywiście powinieneś się porządnie przygotować. Dwie godziny. Zaraz za bramami miasta.";
			link.l1 = "Zrozumiano, dziękuję. Z przyjemnością przyjdę, gdy to się skończy. Do zobaczenia wtedy!";
			link.l1.go = "DTSG_PiterAdamsRyadomSDomom_5";
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_5":
			DialogExit();
			bDisableFastReload = false;
			chrDisableReloadToLocation = false; 
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "", "", "", "", -1);
			npchar.location = "None";
			
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			sld.Dialog.CurrentNode = "Knippel_officer";
			sld.location = "None";
			
			PChar.quest.DTSG_PoP_DuelTime.win_condition.l1 = "Timer";
			PChar.quest.DTSG_PoP_DuelTime.win_condition.l1.date.hour = sti(GetTime() + 2);
			PChar.quest.DTSG_PoP_DuelTime.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
			PChar.quest.DTSG_PoP_DuelTime.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			PChar.quest.DTSG_PoP_DuelTime.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
			PChar.quest.DTSG_PoP_DuelTime.win_condition = "DTSG_PoP_DuelTime";
			
			PChar.quest.DTSG_PoP_Duel.win_condition.l1 = "location";
			PChar.quest.DTSG_PoP_Duel.win_condition.l1.location = "PortPax_ExitTown";
			PChar.quest.DTSG_PoP_Duel.win_condition = "DTSG_PoP_Duel";
			
			AddQuestRecord("DTSG", "3");
		break;
		
		case "DTSG_JeinAdams_1":
			dialog.text = "Witaj! Droga, nie powiedziałaś mi, że przyprowadzasz gości - przygotowałbym się odpowiednio.";
			link.l1 = "Dziękuję, pani, nie zajmie nam to dużo czasu. Charles de Maure, do usług. Zgodziłem się wysłuchać twojej historii z mężem. Opowiedz mi, jak to się stało.";
			link.l1.go = "DTSG_JeinAdams_2";
		break;
		
		case "DTSG_JeinAdams_2":
			dialog.text = "Oh, to było okropne! Ralph był kompletnie pijany. Zaczął mnie nękać przed sąsiadami, nawet przed Peterem, mówiąc nieprzyzwoite rzeczy...";
			link.l1 = "Co dokładnie ci powiedział?";
			link.l1.go = "DTSG_JeinAdams_3";
		break;
		
		case "DTSG_JeinAdams_3":
			dialog.text = "Zbyt się wstydzę, by o tym mówić. Potem wytrzeźwiał, i...";
			link.l1 = "Przeprosiłeś i poprosiłeś o odwołanie pojedynku, być może?";
			link.l1.go = "DTSG_JeinAdams_4";
		break;
		
		case "DTSG_JeinAdams_4":
			dialog.text = "Ani razu.";
			link.l1 = "Przykro mi z twojego powodu. Chciałbym wiedzieć jeszcze jedną rzecz, jeśli pozwolisz, pani.";
			link.l1.go = "DTSG_JeinAdams_5";
		break;
		
		case "DTSG_JeinAdams_5":
			dialog.text = "A co to takiego, sir?";
			link.l1 = "Jakie okoliczności życiowe i próby zmusiły ciebie i twojego męża do życia tutaj? W każdym angielskim mieście, biorąc pod uwagę zasługi twojego męża, już dawno postawiłabyś Ralpha na swoim miejscu.";
			link.l1.go = "DTSG_JeinAdams_6";
		break;
		
		case "DTSG_JeinAdams_6":
			StartInstantDialog("Knippel", "DTSG_JeinAdams_7", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_JeinAdams_7":
			dialog.text = "Proszę o wybaczenie, panie, ale jak śmiesz?! Gdybyś nie był moim kapitanem, złapałbym kulę łańcuchową i porządnie cię poturbował!\nNie tylko nie ufasz tak godnemu człowiekowi jak pan Adams, ale także drwisz z damy w potrzebie...";
			link.l1 = "Słyszałeś, żebym szydził z damy? Nie? Więc nie oczerniaj mnie. Nasi ludzie mogli im pomóc, dlatego zapytałem.";
			link.l1.go = "DTSG_JeinAdams_8a";
			link.l1 = "Spokojnie, Charlie! Jak mogłeś... Chciałem tylko dowiedzieć się więcej o trudnościach Jane i Petera oraz współczuć im. W angielskich koloniach z pewnością już by im pomogli.";
			link.l1.go = "DTSG_JeinAdams_8b";
		break;
		
		case "DTSG_JeinAdams_8a":
			dialog.text = "Życie może potoczyć się na wiele sposobów... Wrak statku. Albo czyjeś oszczerstwo, które czasami może zmusić nawet takich uczciwych ludzi do ukrywania się w niesławie\nJeśli jesteś tak nieufny i podejrzliwy - możesz porozmawiać z sąsiadami. Jestem pewien, że potwierdzą każde słowo. Ale stary Charlie nie zniżyłby się do omawiania ludzkich nieszczęść za ich plecami!";
			link.l1 = "Nie słyszałeś mnie? Powiedziałem, że pomogę tym ludziom.";
			link.l1.go = "DTSG_JeinAdams_9";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
		break;
		
		case "DTSG_JeinAdams_8b":
			dialog.text = "Życie może się potoczyć na wiele sposobów... Rozbicie statku. Albo czyjeś oszczerstwo, które czasem może zmusić nawet takich uczciwych ludzi do ukrycia się w hańbie.\nJeśli jesteś tak nieufny i podejrzliwy - możesz porozmawiać z sąsiadami. Jestem pewny, że potwierdzą każde słowo. Ale stary Charlie nie zniżyłby się do omawiania ludzkiego nieszczęścia za ich plecami!";
			link.l1 = "Nie słyszałeś mnie? Powiedziałem, że pomogę tym ludziom.";
			link.l1.go = "DTSG_JeinAdams_9";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterComplexReputation(pchar, "authority", -2);
		break;
		
		case "DTSG_JeinAdams_9":
			StartInstantDialog("DTSG_PiterAdams", "DTSG_JeinAdams_10", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_JeinAdams_10":
			dialog.text = "Dziękujemy z głębi naszych serc. Będziemy pamiętać o Tobie w naszych modlitwach.";
			link.l1 = "To dobrze. A tak przy okazji, o naszej sprawie. Gdzie i kiedy umówiłeś się na pojedynek, panie Adams?";
			link.l1.go = "DTSG_JeinAdams_11";
		break;
		
		case "DTSG_JeinAdams_11":
			dialog.text = "Poza bramami miasta, panie. Za dwie godziny.";
			link.l1 = "Dam sobie radę. Spodziewaj się dobrych wieści. I nie myśl o zapalaniu świecy za moją duszę przed czasem!";
			link.l1.go = "DTSG_JeinAdams_13";
		break;
		
		case "DTSG_JeinAdams_13":
			DoQuestReloadToLocation("PortPax_town", "reload", "houseF1", "DTSG_PiterAdams_IsDoma");
		break;
		
		case "DTSG_Knippel_30":
			dialog.text = "Czy coś Cię trapi, kapitanie? Wyglądasz na bardzo zamyślonego.";
			link.l1 = "Wiesz, tak. Coś w historii Adamsa się nie zgadza, i...";
			link.l1.go = "DTSG_Knippel_31";
		break;
		
		case "DTSG_Knippel_31":
			dialog.text = "Ile to jeszcze potrwa, panie?! Czy zawsze tak reagujesz, gdy ktoś potrzebuje pomocy?";
			link.l1 = "Na miłość boską, mów ciszej. Wykrzykujesz to na całą ulicę. Powiedziałem, że pójdę na pojedynek. Czy to ci nie wystarczy? A teraz słuchaj mnie uważnie.";
			link.l1.go = "DTSG_Knippel_32";
		break;
		
		case "DTSG_Knippel_32":
			dialog.text = "Hmm, dobrze, Kapitanie. Przepraszam za mój wybuch - troszczę się o los tych, którzy służyli w Królewskiej Marynarce. Wielu z nas to byli porządni ludzie, zasługujący na lepszy los niż większość otrzymała.";
			link.l1 = "Rozumiem cię, Charlie. Teraz pamiętaj, co trzeba zrobić. Chcę, żebyś wysłał część załogi do bram miasta. Gdy nadejdzie czas pojedynku, niech zbiorą się cicho i będą gotowi na mój sygnał.";
			link.l1.go = "DTSG_Knippel_33";
		break;
		
		case "DTSG_Knippel_33":
			dialog.text = "Czy zamierzasz zamienić uczciwy pojedynek w morderstwo?";
			link.l1 = "Podejrzewam, że to nie będzie do końca uczciwe. Zasygnalizuję tylko w razie potrzeby. Jeśli wszystko będzie naprawdę w porządku, z radością przyznam się do błędu. Czy teraz rozumiesz? Czy pamiętasz, co się stało miesiąc temu?";
			link.l1.go = "DTSG_Knippel_34";
		break;
		
		case "DTSG_Knippel_34":
			dialog.text = "Zrozumiano, panie. Szczerze mówiąc, nie jestem z tego zbyt zadowolony, ale zrobię, co trzeba. Nie martw się.";
			link.l1 = "To chciałem usłyszeć.";
			link.l1.go = "DTSG_Knippel_35";
		break;
		
		case "DTSG_Knippel_35":
			DialogExit();
			
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "", "", "", "", -1);
			npchar.location = "None";
			AddDialogExitQuestFunction("DTSG_Knippel_36");
		break;
		
		case "DTSG_RalfFaggl":
			LAi_LocationDisableOfficersGen("PortPax_ExitTown", false);
			PChar.quest.DTSG_PoP_DuelTime.over = "yes";
			PChar.quest.DTSG_PoP_Duel.over = "yes";
			dialog.text = "Więc, de Maure. Jesteś wcześnie. I wciąż jesteśmy w mieście. Choć to nie ma znaczenia. Szkoda, że ​​nie przyprowadziłeś ze sobą tego starego głupca. Ale nie martw się, w końcu do niego dotrzemy.";
			link.l1 = "Do waszych usług w każdej chwili. Najemnicy, co? Kogo ja skrzywdziłem?";
			link.l1.go = "DTSG_RalfFaggl_2";
		break;
		
		case "DTSG_RalfFaggl_2":
			dialog.text = "Otóż to, nikt inny. Szukamy tego starego piernika, Charliego, a łatwiej go znaleźć przez ciebie, bo dowiedzieliśmy się, że jest teraz na twoim okręcie. To nie dżungla, więc musimy działać szybko, by nie zwrócić uwagi tłumu. Ale tutaj przynajmniej, nie uciekniesz.";
			link.l1 = "Przypuszczam, że cała ta sprawa z pojedynkiem była pułapką?";
			link.l1.go = "DTSG_RalfFaggl_3";
		break;
		
		case "DTSG_RalfFaggl_3":
			dialog.text = "Trochę późno, żeby to zauważyć, przyjacielu. I tak byśmy walczyli - jestem Ralph Faggle, do usług.";
			link.l1 = "Właściwie, coś takiego podejrzewałem, więc postanowiłem porozmawiać z sąsiadami. A tak przy okazji, czy Adams też jest w to zamieszany? A co z Jane? Czy ona mogłaby być...";
			link.l1.go = "DTSG_RalfFaggl_4";
		break;
		
		case "DTSG_RalfFaggl_4":
			dialog.text = "Ciekawość to pierwszy stopień do piekła, nie słyszałeś? Kazano ci stawić się na pojedynek, a nie węszyć wszędzie dookoła. Mogłeś mieć szansę przetrwać tę kabałę\nOczywiście. Sprowokuj starego służbistę i zmusisz jego dowódcę do pojedynku - doskonały plan, który wymyśliliśmy razem z Peterem, jak sądzę. A Jane też dobrze się spisała.";
			link.l1 = "Powiedz mi, kto chciał pozbyć się Charliego?";
			link.l1.go = "DTSG_RalfFaggl_5";
		break;
		
		case "DTSG_RalfFaggl_5":
			dialog.text = "Ha, jakbym ci to powiedział? Broń się.";
			link.l1 = "Szkoda. W takim razie zapytam Piotra później.";
			link.l1.go = "DTSG_RalfFaggl_6";
		break;
		
		case "DTSG_RalfFaggl_6":
			DialogExit();
			
			sld = CharacterFromID("DTSG_FrederikStouks");
			LAi_SetCheckMinHP(sld, 1, true, "DTSG_FrederikStouks_ranen");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("DTSG_RalfFaggl");
			LAi_SetCheckMinHP(sld, 1, false, "DTSG_RalfFaggl_ubit");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_SetFightMode(pchar, true);
		break;
		
		case "DTSG_PiterAdams_11":
			dialog.text = "Och, widzę, że wziąłeś moją opowieść do serca i już ukarałeś Ralpha, kapitanie.";
			link.l1 = "Oczywiście, skoro jak zauważyłeś, jestem godnym i szlachetnym człowiekiem. A teraz będę musiał cię ukarać za tę zdradziecką pułapkę.";
			link.l1.go = "DTSG_PiterAdams_12";
			npchar.SaveItemsForDead = true;
			npchar.DontClearDead = true;
			GiveItem2Character(npchar, "letter_1");
			ChangeItemName("letter_1", "itmname_specialletter");
			ChangeItemDescribe("letter_1", "itmdescr_DTSG_letter2");
		break;
		
		case "DTSG_PiterAdams_12":
			dialog.text = "Miło mi, że próbujesz, Kapitanie - z pewnością jesteś już wyczerpany i zraniony.";
			link.l1 = "To zróbmy sobie przerwę. W międzyczasie powiedz mi, dla kogo pracujesz?";
			link.l1.go = "DTSG_PiterAdams_13";
		break;
		
		case "DTSG_PiterAdams_13":
			dialog.text = "Przepraszam, ale mój mecenas by tego nie pochwalił, nawet gdybym później skutecznie się tobą zajął. Co, nawiasem mówiąc, zaraz się stanie.";
			link.l1 = "Cholera jasna!..";
			link.l1.go = "DTSG_PiterAdams_14";
		break;
		
		case "DTSG_PiterAdams_14":
			DialogExit();
			
			if (MOD_SKILL_ENEMY_RATE > 4)
			{
				sld = CharacterFromID("DTSG_FrederikStouks");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_SetHP(sld, GetCharacterBaseHPValue(sld)/2, GetCharacterBaseHPValue(sld));
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			else
			{
				sld = CharacterFromID("DTSG_FrederikStouks");
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
				LAi_KillCharacter(sld);
			}
			
			sld = CharacterFromID("Knippel");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = CharacterFromID("DTSG_PiterAdams");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_Sosedi_Pobeda");
			LAi_SetFightMode(pchar, true);
		break;
		
		case "DTSG_Knippel_40":
			dialog.text = "Nie mogę uwierzyć, że ci... ci łajdacy nie tylko nas oszukali, ale też skłamali o Królewskiej Marynarce! Jak oni śmią! Gdyby nie byli martwi, zmusiłbym ich do połknięcia kilku kul łańcuchowych za taką zdradę!..";
			link.l1 = "Ludzie kłamią na różne tematy, Charlie. Myślałem, że dobrze o tym wiesz. Ale to, co z pewnością wiesz, to kto ich wysłał. To nie jest pierwsza pułapka zastawiona na ciebie ostatnio. Mieli list ze szczegółowym opisem ciebie. Kogo tak bardzo rozwścieczyłeś?";
			link.l1.go = "DTSG_Knippel_41";
		break;
		
		case "DTSG_Knippel_41":
			dialog.text = "Cóż, ja... Może znajdziemy coś jeszcze w domu Adamsa, sir?";
			link.l1 = "Unikasz pytania? Ale masz rację, i tak planowałem to dokładnie przeszukać. Chodźmy.";
			link.l1.go = "DTSG_Knippel_42";
		break;
		
		case "DTSG_Knippel_42":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			PChar.quest.DTSG_PoP_ProverimSunduk.win_condition.l1 = "ExitFromLocation";
			PChar.quest.DTSG_PoP_ProverimSunduk.win_condition.l1.location = PChar.location;
			PChar.quest.DTSG_PoP_ProverimSunduk.win_condition = "DTSG_PoP_ProverimSunduk";
		break;
		
		case "DTSG_Knippel_50":
			dialog.text = "Święte kule armatnie, tyle złota!";
			link.l1 = "Szkoda, że nie ma tu nic więcej. 'Jane' też nigdzie nie widać. Myślisz, że wciąż żyje?";
			link.l1.go = "DTSG_Knippel_51";
		break;
		
		case "DTSG_Knippel_51":
			dialog.text = "Nie wiem, sir, takie łotry są zdolne do wszystkiego...";
			link.l1 = "To prawda, ale wydaje mi się, że wiesz więcej, niż mówisz. To nie pierwszy raz, kiedy cię ścigają. I za każdym razem znajdujemy na nich kupę pieniędzy.";
			link.l1.go = "DTSG_Knippel_52";
		break;
		
		case "DTSG_Knippel_52":
			dialog.text = "Nie jestem pewien, kapitanie, ale może to był lichwiarz ze St. John's.";
			link.l1 = "Jakżeś go przechytrzył?";
			link.l1.go = "DTSG_Knippel_53";
		break;
		
		case "DTSG_Knippel_53":
			dialog.text = "Cóż... jakiś czas temu pożyczyłem od niego pieniądze, by spłacić wszystkie moje inne długi. Richard obiecał to spłacić, ale...";
			link.l1 = "Czy myślisz, że tego nie zrobił?";
			link.l1.go = "DTSG_Knippel_54";
		break;
		
		case "DTSG_Knippel_54":
			dialog.text = "Nie uwierzyłbym w to wcześniej, ale po tym, co ci zrobił i szybko opuścił Karaiby z Abi... Może zapomniał o długu. Albo nie zapomniał, ale i tak odszedł... Richard zachował się jak prawdziwy skurwiel, sir. Nie zdziwiłbym się, ale wciąż byłbym rozczarowany, gdyby okazało się to ponownie prawdą.";
			link.l1 = "Nie bądź tak kategoryczny przedwcześnie, Charlie. Zatem, St. John's to jest.";
			link.l1.go = "DTSG_Knippel_55";
		break;
		
		case "DTSG_Knippel_55":			//КОНЕЦ ЭТАПА 2
			DialogExit();
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.location = "None";
			
			n = Findlocation("PortPax_town");
			locations[n].reload.l31.name = "houseF1";
			locations[n].reload.l31.go = "CommonRoom_MH9";
			locations[n].reload.l31.emerge = "reload1";
			locations[n].reload.l31.autoreload = "0";
			locations[n].reload.l31.label = "House";
			
			BackItemName("letter_1");
			BackItemDescribe("letter_1");
			TakeItemFromCharacter(pchar, "letter_1");
			AddQuestRecord("DTSG", "5");
			QuestOpenSeaExit()
			
			AddMapQuestMarkCity("SentJons", true);
			PChar.quest.DTSG_Etap3_Start.win_condition.l1 = "location";
			PChar.quest.DTSG_Etap3_Start.win_condition.l1.location = "Antigua";
			PChar.quest.DTSG_Etap3_Start.win_condition = "DTSG_Etap3_Start";
		break;
		
		case "DTSG_PiterAdams_20":
			if (CheckAttribute(pchar, "questTemp.DTSG_ZovemMatrosov"))
			{
				dialog.text = "Ach, oto jesteś, sir - wygląda na to, że wszyscy postanowili przyjść wcześniej. Sądząc po twoim wyglądzie, wydajesz się dość radosny, czy jesteś tak pewny swoich umiejętności?";
				link.l1 = "Oczywiście, to z daleka nie mój pierwszy pojedynek.";
				link.l1.go = "DTSG_PiterAdams_Nastoroje_21";
				ChangeCharacterComplexReputation(pchar, "authority", 1);
			}
			else
			{
				dialog.text = "Bałem się, że nie przyjdziesz, panie. Inni już tu są.";
				link.l1 = "Prawdziwy szlachcic może się spóźnić tylko na swoją śmierć.";
				link.l1.go = "DTSG_PiterAdams_NN_21";
				ChangeCharacterComplexReputation(pchar, "nobility", 1);
			}
		break;
		
		case "DTSG_PiterAdams_NN_21":
			dialog.text = "Cudowne słowa, panie! Poznaj naszego przeciwnika, Ralpha Faggle. A to nasz sekundant, Frederick Stokes.";
			link.l1 = "";
			link.l1.go = "DTSG_PiterAdams_NN_22";
		break;
		
		case "DTSG_PiterAdams_NN_22":
			dialog.text = "Spotkaj się...";
			link.l1 = "";
			link.l1.go = "DTSG_PiterAdams_NN_23";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_NN_23":
			dialog.text = "Nasz przeciwnik, Ralph Faggle.";
			link.l1 = "";
			link.l1.go = "DTSG_PiterAdams_NN_24";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_NN_24":
			dialog.text = "I to jest nasz drugi, Frederick Stokes.";
			link.l1 = "";
			link.l1.go = "DTSG_PiterAdams_NN_25";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_FrederikStouks"));
		break;
		
		case "DTSG_PiterAdams_NN_25":
			dialog.text = "...";
			link.l1 = "Więc to jest Ralph? Nie wygląda jak typowy pijany sąsiad.";
			link.l1.go = "DTSG_PiterAdams_NN_26";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetCameraDialogMode(CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_NN_26":
			dialog.text = "  Nigdy nie wiesz, kim może być twój sąsiad, czy pomyślałeś o tym, panie de Maure? Heh-heh-heh.";
			link.l1 = "Więc to pułapka... Widzę, że przestałeś nawet drżeć. Zmęczony udawaniem gorączkowego?";
			link.l1.go = "DTSG_PiterAdams_NN_27";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetCameraDialogMode(npchar);
		break;
		
		case "DTSG_PiterAdams_NN_27":
			dialog.text = "Jedyną rzeczą, którą mogę teraz odrzucić, jest śmiech z twojej naiwności.";
			link.l1 = "Cóż, cóż. Żałuję tylko, że Charlie się w to wplątał - łatwiej i ciszej byłoby rozprawić się z tobą sam na sam...";
			link.l1.go = "DTSG_PiterAdams_BitvaDuel";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_21":
			dialog.text = "No, to cudowne!";
			link.l1 = "";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_22";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_22":
			dialog.text = "Pozwól mi przedstawić...";
			link.l1 = "";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_23";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_Nastoroje_23":
			dialog.text = "Pan Stokes, nasz drugi.";
			link.l1 = "";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_24";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_FrederikStouks"));
		break;
		
		case "DTSG_PiterAdams_Nastoroje_24":
			dialog.text = "I to jest Ralph Faggle.";
			link.l1 = "Więc to jest Ralph? Muszę przyznać, że wyobrażałem go sobie inaczej. Ale mniejsza z tym, miałem do czynienia z gorszymi.";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_25";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_Nastoroje_25":
			dialog.text = "Hmm, zastanawiam się, czy jesteś naiwny, niczego nie rozumiesz? A może aż tak pewny siebie?";
			link.l1 = "A czegoż to nie rozumiem, panie Adams? Dalej, zaskocz mnie.";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_26";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetCameraDialogMode(npchar);
		break;
		
		case "DTSG_PiterAdams_Nastoroje_26":
			dialog.text = "Zazwyczaj ludzie są zaskoczeni lub przestraszeni w takich sytuacjach, ale ty wydajesz się być innego typu. Tym przyjemniej będzie zetrzeć ten zadowolony uśmieszek z twojej twarzy, panie de Maure.";
			link.l1 = "Ależ groźby! Czyż nie jesteśmy po tej samej stronie, Piotrze?";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_27";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_27":
			dialog.text = "Nie mów mi, że masz nadzieję pokonać nas wszystkich z tym starcem. Jesteś w mniejszości, drogi panie.";
			link.l1 = "Jak mówiłem, to TY nie rozumiesz. Charlie trochę pomruczał, ale i tak kazałem mu przyprowadzić tu chłopaków na wszelki wypadek. Jak się okazuje, nie na próżno. CHŁOPAKI, TUTAJ!!!";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_28";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_28":
			DialogExit();
			
			StartQuestMovie(true, false, true);
			locCameraFromToPos(0.34, 0.51, 34.93, true, -5.63, -1.20, 57.46);
			DoQuestCheckDelay("DTSG_PoP_Duel_Podkreplenie", 3.0);
			
			int DTSG_PoP_MK;
			if (MOD_SKILL_ENEMY_RATE == 2) DTSG_PoP_MK = 5;
			if (MOD_SKILL_ENEMY_RATE == 4) DTSG_PoP_MK = 5;
			if (MOD_SKILL_ENEMY_RATE == 6) DTSG_PoP_MK = 4;
			if (MOD_SKILL_ENEMY_RATE == 8) DTSG_PoP_MK = 4;
			if (MOD_SKILL_ENEMY_RATE == 10) DTSG_PoP_MK = 3;
			
			for (i=1; i<=DTSG_PoP_MK; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("DTSG_PoP_Matrosy_"+i, "citiz_3"+i, "man", "man", sti(pchar.rank)-5, sti(pchar.nation), -1, false, "quest"));
				GiveItem2Character(sld, "blade_11");
				sld.equip.blade = "blade_11";
				ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
				sld.lifeday = 0;
				LAi_SetHP(sld, 120.0, 120.0);
			}
		break;
		
		case "DTSG_PiterAdams_Nastoroje_29":
			dialog.text = "Co?..";
			link.l1 = "Zaskoczony i przestraszony, panie Adams? Dobrze wiedzieć.";
			link.l1.go = "DTSG_PiterAdams_BitvaDuel";
			SetCameraDialogMode(npchar);
		break;
		
		case "DTSG_PiterAdams_BitvaDuel":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("PortPax_ExitTown")], false);
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=5; i++)
			{
				if (GetCharacterIndex("DTSG_PoP_Matrosy_"+i) != -1)
				{
					sld = CharacterFromID("DTSG_PoP_Matrosy_"+i);
					LAi_SetWarriorType(sld);
					LAi_CharacterDisableDialog(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				}
			}
			
			sld = CharacterFromID("Knippel");
			LAi_SetWarriorType(sld);
			LAi_SetCheckMinHP(sld, 10, true, "KnippelRanen");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = CharacterFromID("DTSG_PiterAdams");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("DTSG_FrederikStouks");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("DTSG_RalfFaggl2");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_PiterAdams_Duel_Pobeda");
		break;
		
		case "DTSG_Knippel_60":
			dialog.text = "Tak właśnie powinno się postępować z takimi kłamliwymi łajdakami. Nadal nie mogę uwierzyć, że mieli czelność kłamać o Królewskiej Marynarce! Zadusiłbym ich łańcuchowym strzałem!..";
			link.l1 = "Teraz już powinieneś wiedzieć, że niektórzy ludzie nie mają skrupułów, Charlie. Powiedziałem, że się tym zajmę, mogłeś zostać na statku. Czy chciałeś się upewnić, że pomogę tym 'godnym ludziom'? I kto znowu miał rację, że to nie było takie proste, jak myślałeś?";
			link.l1.go = "DTSG_Knippel_61";
		break;
		
		case "DTSG_Knippel_61":
			dialog.text = "Ty, panie...";
			link.l1 = "Dokładnie. Ale powiedz mi, dlaczego ktoś chciałby cię ścigać? To nie pierwszy raz.";
			link.l1.go = "DTSG_Knippel_62";
		break;
		
		case "DTSG_Knippel_62":
			dialog.text = "Nie wiem, Kapitanie. Stary Charlie to tylko prosty kanonier.";
			link.l1 = "Hmm, no cóż, no cóż. Dobrze, skoro nasi biedni pojedynkowicze nie mieli przy sobie nic użytecznego... Nie, chodźmy zobaczyć, czy znajdziemy coś w domu Adamsa.";
			link.l1.go = "DTSG_Knippel_63";
		break;
		
		case "DTSG_Knippel_63":
			DialogExit();
			
			LAi_RemoveCheckMinHP(npchar);
			LAi_SetImmortal(npchar, false);
			AddDialogExitQuestFunction("DTSG_Knippel_64");
		break;
		
		case "DTSG_Knippel_70":
			dialog.text = "A więc ta kobieta też zniknęła... Może przygotowywali się do ucieczki z miasta zaraz po tym 'pojedynku'? I to w pośpiechu - tyle tu złota!";
			link.l1 = "Masz rację, bo złoto to nie jedyna rzecz, którą zostawili. Jeszcze jeden list. Tak się spieszyli, że zapomnieli go spalić. Spójrz, spodoba ci się jego treść.";
			link.l1.go = "DTSG_Knippel_71";
		break;
		
		case "DTSG_Knippel_71":
			TakeItemFromCharacter(pchar, "letter_1");
			dialog.text = "(czyta) Cóż, spierałbym się o 'stary'.";
			link.l1 = "Nie o to teraz chodzi. To już drugi raz, kiedy wysłali za tobą najemników, dając im pieniądze i informacje. I to ciebie właśnie chcą. Powiedz mi, ty prosty kanonierze, kogo mogłeś aż tak rozwścieczyć?";
			link.l1.go = "DTSG_Knippel_72";
		break;
		
		case "DTSG_Knippel_72":
			dialog.text = "Mam jedno przypuszczenie, panie, tylko jedno, i naprawdę nie chcę, żeby było prawdziwe.";
			link.l1 = "Więc to najprawdopodobniej prawda. Mów śmiało.";
			link.l1.go = "DTSG_Knippel_73";
		break;
		
		case "DTSG_Knippel_73":
			dialog.text = "Kiedyś miałem długi wobec różnych ludzi w St. John's, i...";
			link.l1 = "... a teraz myślisz, że cię ścigają? Ilu z nich stać na najemników i takie sumy?";
			link.l1.go = "DTSG_Knippel_74";
		break;
		
		case "DTSG_Knippel_74":
			dialog.text = " Myślisz poprawnie, panie. W końcu spłaciłem prawie wszystkie swoje długi, pożyczając od lichwiarza. Oczywiście, on może sobie na to pozwolić. Ale...";
			link.l1 = "Ale co? Spłacimy twój dług i to wszystko. Co cię martwi?";
			link.l1.go = "DTSG_Knippel_75";
		break;
		
		case "DTSG_Knippel_75":
			dialog.text = "Widzisz, kapitanie, Richard obiecał, że to za mnie spłaci.";
			link.l1 = "Myślisz, że tego nie zrobił?";
			link.l1.go = "DTSG_Knippel_76";
		break;
		
		case "DTSG_Knippel_76":
			dialog.text = "Nie wiem już, co myśleć, panie. Przez cały czas, kiedy się znaliśmy, znałem go jako wzorowego dżentelmena. Ale po tym, jak cię opuścił i uciekł z Abigail... Nie byłbym zaskoczony. Dlatego powiedziałem, że nie chciałbym, żeby to była prawda.";
			link.l1 = "Domysły najpierw trzeba sprawdzić, potem możesz się irytować, Charlie. Chodź, odwiedzisz jeszcze raz St. John's.";
			link.l1.go = "DTSG_Knippel_77";
		break;
		
		case "DTSG_Knippel_77":			//КОНЕЦ ЭТАПА 2
			DialogExit();
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			
			n = Findlocation("PortPax_town");
			locations[n].reload.l31.name = "houseF1";
			locations[n].reload.l31.go = "CommonRoom_MH9";
			locations[n].reload.l31.emerge = "reload1";
			locations[n].reload.l31.autoreload = "0";
			locations[n].reload.l31.label = "House";
			
			BackItemName("letter_1");
			BackItemDescribe("letter_1");
			AddQuestRecord("DTSG", "6");
			QuestOpenSeaExit()
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			LAi_LocationDisableOfficersGen("PortPax_ExitTown", false);
			
			AddMapQuestMarkCity("SentJons", true);
			PChar.quest.DTSG_Etap3_Start.win_condition.l1 = "location";
			PChar.quest.DTSG_Etap3_Start.win_condition.l1.location = "Antigua";
			PChar.quest.DTSG_Etap3_Start.win_condition = "DTSG_Etap3_Start";
		break;
		
		case "DTSG_Knippel_PoPDuelTime":
			dialog.text = "Kapitanie!!!";
			link.l1 = "Co się stało, Charlie, co się wydarzyło?";
			link.l1.go = "DTSG_Knippel_PoPDuelTime_2";
		break;
		
		case "DTSG_Knippel_PoPDuelTime_2":
			dialog.text = "Stało się?! Nie mów mi, że zapomniałeś o pojedynku, panie! Adams może już być posiekany na kawałki, podczas gdy ty się tutaj opalasz!";
			link.l1 = "Racja!.. Natychmiast opuszczam miasto.";
			link.l1.go = "DTSG_Knippel_PoPDuelTime_3";
		break;
		
		case "DTSG_Knippel_PoPDuelTime_3":
			DialogExit();
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			DoQuestReloadToLocation("PortPax_ExitTown", "reload", "reload3", "");
		break;
		
		case "DTSG_AntiguaArest":
			dialog.text = "Kapitanie Charles de Maure? Czy to Charlie Knippel z tobą?";
			link.l1 = "Nie, to...";
			link.l1.go = "DTSG_AntiguaArest_2";
		break;
		
		case "DTSG_AntiguaArest_2":
			dialog.text = "Nie zaprzeczaj temu, panie - każdy w tej kolonii zna Charlie'ego.";
			link.l1 = "To po co pytać? Jak mogę pomóc?";
			link.l1.go = "DTSG_AntiguaArest_3";
		break;
		
		case "DTSG_AntiguaArest_3":
			dialog.text = "Nie możesz. Proszę, nie opieraj się - Charlie jest tutaj poszukiwany. Musimy go zatrzymać.";
			link.l1 = "Czy mogę wiedzieć, jakie zarzuty są postawione mojemu człowiekowi? Czy chodzi o jego dług? Mogę go spłacić za niego. Chodźmy natychmiast do bankiera, w twojej obecności.";
			link.l1.go = "DTSG_AntiguaArest_4";
		break;
		
		case "DTSG_AntiguaArest_4":
			dialog.text = "Dług? Pierwszy raz o tym słyszę. Nie znam szczegółów, ale proszę, nie komplikuj spraw - ja tylko wykonuję rozkazy.";
			link.l1 = "O, to po prostu świetnie...";
			link.l1.go = "DTSG_AntiguaArest_5";
		break;
		
		case "DTSG_AntiguaArest_5":
			StartInstantDialog("Knippel", "DTSG_AntiguaArest_6", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_AntiguaArest_6":
			dialog.text = "Kapitanie...";
			link.l1 = "Charlie, jeśli teraz uciekniemy, nagroda za nasze głowy będzie jeszcze wyższa. A nie możemy się przebić? Spróbuję cię wyciągnąć, tylko nie rób nic głupiego!";
			link.l1.go = "DTSG_AntiguaArest_7";
		break;
		
		case "DTSG_AntiguaArest_7":
			DialogExit();
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			AddQuestRecord("DTSG", "8");
			pchar.questTemp.DTSG_KnippelDolg = true;
			
			sld = CharacterFromID("Knippel");
			RemovePassenger(pchar, sld);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload_jail", "", "", "", "", -1);
			sld.location = "None";
			
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("DTSG_AntiguaSold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload_jail", "", "", "", "", -1);
				sld.location = "None";
			}
		break;
		
		case "DTSG_AntiguaStrazhBank":
			dialog.text = "Przestań hałasować i grozić temu człowiekowi natychmiast, sir. Oddaj broń i podążaj za mną w tej chwili!";
			link.l1 = "Nie groziłem nikomu, zaszła pomyłka. To sprawa biznesowa, a nie próba morderstwa.";
			link.l1.go = "DTSG_AntiguaStrazhBank_2";
		break;
		
		case "DTSG_AntiguaStrazhBank_2":
			dialog.text = "Nie wygląda na to dla mnie. Będziesz musiał odpowiedzieć przed prawem.";
			link.l1 = "Co, jeśli przeproszę i odejdę?";
			link.l1.go = "DTSG_AntiguaStrazhBank_3";
		break;
		
		case "DTSG_AntiguaStrazhBank_3":
			dialog.text = "Więc możesz się zakraść z powrotem i dokończyć to, co przerwałem? Myślisz, że jestem głupi?";
			link.l1 = "Musisz być, jeśli nie chcesz załatwić tego pokojowo. Bóg wie, że nie chciałem, by do tego doszło...";
			link.l1.go = "DTSG_AntiguaStrazhBank_4";
		break;
		
		case "DTSG_AntiguaStrazhBank_4":
			DialogExit();
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_bank")], false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_AntiguaStrazhBank_Ubili");
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki":
			dialog.text = "Zabiłeś go!..";
			link.l1 = "Uznaj to za zrobione własnoręcznie, panie. Mogłeś po prostu odpowiedzieć na moje pytania zamiast histeryzować. Przysięgam, jeszcze jeden krzyk, a rozwalę ci łeb.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_V1";
			link.l2 = "Tak, zabiłem go. Zmusił mnie do tego. Ale nie jesteś tak bezmyślny jak on i nie pójdziesz jego śladem, prawda?";
			link.l2.go = "DTSG_AntiguaUsurer_PosleDraki_V2";
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_V1":
			dialog.text = "Czego chcesz?!";
			link.l1 = "Jakiś czas temu, Charlie Knippel pożyczył od ciebie pieniądze. Jego przyjaciel obiecał spłacić jego dług, ale najwyraźniej tego nie zrobił. Żądam, abyś natychmiast przestał wysyłać najemników za nami. Jestem gotów spłacić dług Charliego od razu, jeśli tylko mnie na to stać.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_3";
			AddComplexLandExpToScill(100, 0, 0);
			AddComplexSeaExpToScill(0, 0, 0, 0, 0, 0, 100);
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_V2":
			dialog.text = "Czego chcesz?!";
			link.l1 = "Jakiś czas temu Charlie Knippel pożyczył od ciebie pieniądze. Jego przyjaciel obiecał spłacić jego dług, ale najwyraźniej tego nie zrobił. Żądam, abyś natychmiast przestał wysyłać najemników za nami. Jestem gotów spłacić dług Charliego natychmiast, jeśli mnie na to stać.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_3";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_3":
			dialog.text = "Charlie?! I would never do that to him; he's a good, honest man. Besides, his debt has long been paid off. Mr. Fleetwood, the captain of the Valkyrie, settled it to the last peso.";
			link.l1 = "Naprawdę? Wiem, kim on jest. Powinieneś był powiedzieć to od razu. Przepraszam za kłopot, do widzenia.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_4";
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_4":
			dialog.text = "Ot tak po prostu?! Groziłeś mi! I zabiłeś człowieka!..";
			link.l1 = "Czy zapomniałeś, co powiedziałem? Jeszcze jeden krzyk, a dołączysz do niego. Żegnaj.";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_5";
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_5":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_town")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_bank")], true);
			//LAi_LocationDisableOfficersGen("SentJons_town", false);
			LAi_LocationDisableOfficersGen("SentJons_bank", false);
			npchar.dialog.filename = "Usurer_dialog.c";
			npchar.dialog.currentnode = "First time";
			LAi_SetOwnerType(npchar);
			
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "fame", 2);
			
			chrDisableReloadToLocation = false;
			AddQuestRecord("DTSG", "9");
			PChar.quest.DTSG_AntiguaTrevoga.win_condition.l1 = "location";
			PChar.quest.DTSG_AntiguaTrevoga.win_condition.l1.location = "SentJons_town";
			PChar.quest.DTSG_AntiguaTrevoga.win_condition = "DTSG_AntiguaTrevoga";
		break;
		
		case "DTSG_Killer":
			dialog.text = "Jeszcze tu jesteś i nie wiszysz? No cóż, pozdrowienia z Sussex, Charlie.";
			link.l1 = "Pozdrawiam cię, kimkolwiek jesteś.";
			link.l1.go = "DTSG_Killer_2";
			CharacterTurnToLoc(npchar, "goto", "goto9");
		break;
		
		case "DTSG_Killer_2":
			dialog.text = "Ach, Charles de Maure. Dobrze, że odwiedziłeś biednego Charliego. Liczyliśmy na to.";
			link.l1 = "Kim jesteśmy?";
			link.l1.go = "DTSG_Killer_3";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "DTSG_Killer_3":
			dialog.text = "Nie ma znaczenia. Kosztowałeś nas znacząco czasu i pieniędzy, panie de Maure. Myślę, że nie będą mieli nic przeciwko, jeśli zajmę się zarówno Charliem, jak i tobą, tutaj.";
			link.l1 = "Cóż, skoro i tak obaj jesteśmy martwi, czy mógłbyś nam z dobroci serca powiedzieć, kogo tak bardzo rozzłościliśmy? Obiecujemy, że nie zrobimy tego ponownie. A kim jest Sussex?";
			link.l1.go = "DTSG_Killer_4";
		break;
		
		case "DTSG_Killer_4":
			dialog.text = "Nie da się. Obowiązek wzywa i, w przeciwieństwie do ciebie, jestem człowiekiem czynu, nie słów.";
			link.l1 = "Na litość boską, czy ktoś mi w końcu wyjaśni, co się dzieje?!";
			link.l1.go = "DTSG_Killer_5";
		break;
		
		case "DTSG_Killer_5":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetImmortal(npchar, false);
			
			for (i=1; i<=12; i++)
			{
				if (GetCharacterIndex("SentJonsPrisoner_"+i) != -1)
				{
					sld = CharacterFromID("SentJonsPrisoner_"+i);
					sld.lifeday = 0;
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
			}
			
			for (i = 0; i < MAX_CHARACTERS; i++)
			{
				sld = GetCharacter(i);
				if (sld.city == "sentjons" && sld.location == "SentJons_prison")
				{
					sld.lifeday = 0;
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
			}
			
			sld = CharacterFromID("SentJonsJailOff");
			sld.lifeday = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
			
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_SentJonsJailOff", "off_eng_1", "man", "man", 30, PIRATE, 0, true, "soldier"));
			ChangeCharacterAddressGroup(sld, "SentJons_prison", "goto", "goto18");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld.rank = 30;
			SetSelfSkill(sld, 80, 80, 80, 80, 80);
			LAi_SetHP(sld, 200+MOD_SKILL_ENEMY_RATE*20, 200+MOD_SKILL_ENEMY_RATE*20);
			
			for (i=1; i<=3; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("DTSG_AntiguaSoldTurma_"+i, "sold_eng_"+(rand(15)+1), "man", "man", sti(pchar.rank), PIRATE, 0, true, "soldier"));
				ChangeCharacterAddressGroup(sld, "SentJons_prison", "goto", "goto22");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			
			for (i=4; i<=7; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("DTSG_AntiguaSoldTurma_"+i, "sold_eng_"+(rand(15)+1), "man", "man", sti(pchar.rank), PIRATE, 0, true, "soldier"));
				ChangeCharacterAddressGroup(sld, "SentJons_prison", "reload", "reload1");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			
			/*sld = CharacterFromID("SentJons_Mayor");
			LAi_group_Attack(sld, Pchar);*/
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_TurmaDayPobeda");
		break;
		
		case "DTSG_KnippelDaySpasen":
			dialog.text = "Cóż, do diabła, Kapitanie, cóż za masakrę tu urządziłeś!";
			link.l1 = "Czy masz coś przeciwko? Wolisz szubienicę? A może wolisz gnić tu w nieskończoność?";
			link.l1.go = "DTSG_KnippelDaySpasen_2";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_KnippelDaySpasen_2":
			dialog.text = "Nie, panie. Dziękuję za uratowanie mnie. Szczerze mówiąc, jestem zaskoczony, że przyszedłeś, biorąc pod uwagę, jak łatwo pozwoliłeś im mnie zabrać. I zaskoczony, jak łatwo poradziłeś sobie ze strażnikiem - był to Morski Lis. Żołnierz piechoty morskiej.";
			link.l1 = "Powiedziałem ci, że cię wyciągnę, nie powinieneś był wątpić. Teraz wyłaź z tej celi, zanim cała garnizon tu przybędzie.";
			link.l1.go = "DTSG_KnippelDaySpasen_3";
		break;
		
		case "DTSG_KnippelDaySpasen_3":
			dialog.text = "Tak jest, kapitanie.";
			link.l1 = "";
			link.l1.go = "DTSG_KnippelDaySpasen_4";
		break;
		
		case "DTSG_KnippelDaySpasen_4":
			DialogExit();
			
			Pchar.GenQuest.Hunter2Pause = true;
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("DTSG_TurmaDayPobeda_2", 1.0);
		break;
		
		case "DTSG_KnippelDaySpasen_5":
			dialog.text = "Cholera, sir, trudno mi w to uwierzyć...";
			link.l1 = "A tak swoją drogą, powiedz mi, o co cię oskarżono? I kim jest Sussex?";
			link.l1.go = "DTSG_KnippelDaySpasen_6";
		break;
		
		case "DTSG_KnippelDaySpasen_6":
			dialog.text = "Nie wiem, panie. Nie mam pojęcia, kogo mieli na myśli...";
			link.l1 = "Dobrze, dowiemy się później. Teraz musimy się stąd wydostać.";
			link.l1.go = "DTSG_KnippelDaySpasen_7";
		break;
		
		case "DTSG_KnippelDaySpasen_7":
			DialogExit();
			
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			AddPassenger(pchar, npchar, false);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			AddQuestRecord("DTSG", "12");
			
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition = "DTSG_KnippelRazgovorVKaute";
		break;
		
		case "DTSG_AntiguaNightPirs":
			dialog.text = "Jakie są twoje następne kroki, panie? Wyciskanie sensu z tego krwiopijcy w biały dzień to ryzykowna sprawa.";
			link.l1 = "Dałeś mi właśnie pomysł. Po co wybijać mu rozum za dnia, skoro możemy to zrobić teraz, pod osłoną nocy?";
			link.l1.go = "DTSG_AntiguaNightPirs_2";
		break;
		
		case "DTSG_AntiguaNightPirs_2":
			dialog.text = "Niech mnie diabli, to genialny pomysł, Kapitanie!";
			link.l1 = "Dokładnie. Powiedz mi, Charlie, mieszkałeś tu przez jakiś czas. Wiesz, gdzie mieszka lichwiarz?";
			link.l1.go = "DTSG_AntiguaNightPirs_3";
		break;
		
		case "DTSG_AntiguaNightPirs_3":
			dialog.text = "Kiedyś wiedziałem, panie, ale ostatnim razem, gdy tu byłem, sprzedawał swój dom. Nie mam pojęcia, gdzie jest nowy.";
			link.l1 = "Cóż, to problem...";
			link.l1.go = "DTSG_AntiguaNightPirs_4";
		break;
		
		case "DTSG_AntiguaNightPirs_4":
			dialog.text = "Jestem pewien, że coś wymyślisz, Kapitanie, w końcu pokonałeś wielkiego strasznego Lucasa Rodenburga!";
			link.l2 = "Dobrze, zajmę się tym. Chociaż, gdybyś wiedział, gdzie znajduje się dom lichwiarza, byłoby lepiej!";
			link.l2.go = "DTSG_AntiguaIskat_1";
			link.l1 = "To prawda. Ale poranek jest mądrzejszy od wieczora, Charlie. Odpocznijmy po podróży i ruszmy za dnia - nie przybyliśmy tutaj, by zabić tego człowieka w końcu.";
			link.l1.go = "DTSG_AntiguaSpat_1";
		break;
		
		case "DTSG_AntiguaSpat_1":
			dialog.text = "Jesteś tego pewien, panie? Stracimy element zaskoczenia.";
			link.l1 = "Jestem pewien i zmęczony. Poza tym, chcę tylko porozmawiać. Przestrasz go trochę, jeśli będzie trzeba.";
			link.l1.go = "DTSG_AntiguaSpat_2";
		break;
		
		case "DTSG_AntiguaSpat_2":
			TavernWaitDate("wait_day");
			DoQuestReloadToLocation("SentJons_tavern_upstairs", "goto", "goto2", "DTSG_AntiguaSpat_3");
		break;
		
		case "DTSG_AntiguaIskat_1":
			dialog.text = " Czego nie wiem - nie wiem, przepraszam, panie. ";
			link.l1 = "A, nieważne, poszukajmy go.";
			link.l1.go = "DTSG_AntiguaIskat_2";
		break;
		
		case "DTSG_AntiguaIskat_2":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			
			AddQuestRecord("DTSG", "13");
			pchar.questTemp.DTSG_NightIskat = true;
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			pchar.GenQuest.CannotWait = true;
			pchar.questTemp.TimeLock = true;
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood":
			dialog.text = "Czy myślisz to samo co ja, sir?";
			link.l1 = "Obawiam się, że tak, Charlie. Nie ma innego słynnego kapitana o tym imieniu na Karaibach. A Richard rzeczywiście pojechał do Londynu. Więc mało prawdopodobne, że to przypadek.";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_2";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_2":
			dialog.text = "Okropne... Choć powiedziałem o nim wiele gorzkich słów, nigdy nie życzyłem mu czegoś takiego! A biedna Abi!.. Oczekiwała dziecka. Mam nadzieję, że żyje...";
			link.l1 = "Rzeczywiście, nikomu bym tego nie życzył. Miejmy nadzieję, że z Abi wszystko w porządku. Masz jakiś pomysł, kto mógłby to zrobić Dickowi? Czy kiedykolwiek wspominał o potężnych wrogach?";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_3";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_3":
			dialog.text = "Żartujesz sobie, Kapitanie. Nie wiem, jak tam w Europie, ale tutaj każdy Holender chciał śmierci Richarda.";
			link.l1 = "To prawda. Może ktoś tutaj wydał dużo pieniędzy i wysłał zabójców za nim do Starego Świata. Czy to możliwe, że to nie ten drobny lichwiarz stoi za atakami na ciebie, ale jakiś tajemniczy wróg Richarda?";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_4";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_4":
			dialog.text = "Nie wiem, sir. Wszystko jest teraz możliwe. Ale to skomplikowałoby sprawy dla nas wszystkich...";
			link.l1 = "Tak, masz rację, mnie też nie podoba się ta możliwość.";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_5";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_5":
			DialogExit();
			npchar.location = "None";
			
			AddQuestRecord("DTSG", "14");
			pchar.questTemp.DTSG_Nastoroje2 = true;
			chrDisableReloadToLocation = false;
			
			PChar.quest.DTSG_NightDom.win_condition.l1 = "locator";
			PChar.quest.DTSG_NightDom.win_condition.l1.location = "SentJons_town";
			PChar.quest.DTSG_NightDom.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_NightDom.win_condition.l1.locator = "houseSp3";
			PChar.quest.DTSG_NightDom.win_condition = "DTSG_NightDom";
		break;
		
		case "DTSG_NightRostovshik":
			dialog.text = "Co, kto... CO?! Co się dzieje?.. Kim jesteś?!..";
			link.l1 = "Oj, daj spokój. Gdybym chciał cię zabić, zrobiłbym to, gdy śpisz. Więc nie komplikujmy ani nie skracajmy sobie życia. Skinij głową, jeśli rozumiesz.";
			link.l1.go = "DTSG_NightRostovshik_2";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_NightRostovshik_2":
			dialog.text = "Mhm...";
			link.l1 = "Bardzo dobrze. Uspokój się - nie jestem tu, by cię okraść, porwać ani skrzywdzić.";
			link.l1.go = "DTSG_NightRostovshik_3";
		break;
		
		case "DTSG_NightRostovshik_3":
			dialog.text = "Więc... czemu tu jesteś? Czemu nie mogłeś przyjść rano?";
			link.l1 = "Ponieważ jakiś bogaty, wpływowy człowiek poluje na mojego przyjaciela. Mamy powody sądzić, że to Ty, więc prawdopodobnie nie jest bezpiecznie dla niego chodzić po tych ulicach w biały dzień.";
			link.l1.go = "DTSG_NightRostovshik_4";
		break;
		
		case "DTSG_NightRostovshik_4":
			dialog.text = "Ale ja naprawdę nie rozumiem, o czym mówisz, panie...";
			link.l1 = "Charlie Knippel. Wszyscy w mieście go znają. Pomyśl dobrze. Jest ci winien pieniądze.";
			link.l1.go = "DTSG_NightRostovshik_5";
		break;
		
		case "DTSG_NightRostovshik_5":
			dialog.text = "Nasz stary Charlie?? To prawda, ale jego dług został spłacony dawno temu, choć nie osobiście przez niego.";
			link.l1 = "A kto był tym dobroczyńcą?";
			link.l1.go = "DTSG_NightRostovshik_6";
		break;
		
		case "DTSG_NightRostovshik_6":
			dialog.text = "Jego kapitan, lord Richard Fleetwood. Jeśli mi nie wierzysz, mogę pokazać ci moje zapiski.";
			link.l1 = "Fleetwood, powiadasz? W takim razie ci wierzę. Czyli nie wysłałeś najemników za Charliem?";
			link.l1.go = "DTSG_NightRostovshik_7";
		break;
		
		case "DTSG_NightRostovshik_7":
			dialog.text = "Oczywiście, że nie, dlaczego miałbym?? I powiedz mi, jaki miałoby to sens?";
			link.l1 = "Rzeczywiście. Cóż, przepraszam za późną wizytę. Dobranoc.";
			link.l1.go = "DTSG_NightRostovshik_8";
		break;
		
		case "DTSG_NightRostovshik_8":
			DialogExit();
			
			PChar.quest.DTSG_NightDom_3.win_condition.l1 = "locator";
			PChar.quest.DTSG_NightDom_3.win_condition.l1.location = "SentJons_houseSP3";
			PChar.quest.DTSG_NightDom_3.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_NightDom_3.win_condition.l1.locator = "reload1";
			PChar.quest.DTSG_NightDom_3.win_condition = "DTSG_NightDom_3";
			
			LAi_CharacterDisableDialog(npchar);
			Pchar.GenQuest.Hunter2Pause = true;
			AddQuestRecord("DTSG", "15");
		break;
		
		case "DTSG_NightKiller":
			dialog.text = "Co, Charlie, miałeś nadzieję ukryć się u swojego dawnego patrona tej nocy? Nie ma go tam. Ale wkrótce się z nim spotkasz. Pozdrowienia od Sussex.";
			link.l1 = "Już to wiedzieliśmy. A kim jest Sussex? A kim jesteś ty?";
			link.l1.go = "DTSG_NightKiller_2";
		break;
		
		case "DTSG_NightKiller_2":
			dialog.text = "To nie twoja sprawa, panie de Maure. Szkoda, że wplątałeś się w ten bałagan bardziej, niż byśmy chcieli. Jesteś utrapieniem.";
			link.l1 = "Utrapienie dla kogo? Proszę, nie mów mi, że spałem z żoną bardzo wpływowego i bardzo wściekłego Anglika.";
			link.l1.go = "DTSG_NightKiller_3";
		break;
		
		case "DTSG_NightKiller_3":
			dialog.text = "Bardzo śmieszne. Znalazłeś czas na żarty. Widocznie to, co o tobie słyszałem, jest prawdą\nCzego chcemy? Głowa Charliego wystarczy. Ale biorąc pod uwagę, ile kłopotów nam sprawiłeś, tym razem chodzi też o ciebie - ciągle wsadzasz nos tam, gdzie nie trzeba.";
			link.l1 = "Przypuszczam, że jesteśmy aresztowani?";
			link.l1.go = "DTSG_NightKiller_4";
		break;
		
		case "DTSG_NightKiller_4":
			dialog.text = "Areszt? Nie, drogi panie, czas na półśrodki już minął. To jest egzekucja, kapitanie de Maure.";
			link.l1 = "Zgoda. Pozostaje tylko pytanie, czyja.";
			link.l1.go = "DTSG_NightKiller_5";
		break;
		
		case "DTSG_NightKiller_5":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_town")], false);
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("Knippel");
			LAi_SetOfficerType(sld);
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("DTSG_Killers_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_NightKiller_Pobeda");
		break;
		
		case "DTSG_Knippel_80":
			dialog.text = "Nie sądziłem, że Morskie Lisy będą zamieszane...";
			link.l1 = "Cóż, zawsze jest ten pierwszy raz. Powiedz mi, Charlie, kim jest Sussex?";
			link.l1.go = "DTSG_Knippel_81";
		break;
		
		case "DTSG_Knippel_81":
			dialog.text = "Ja...";
			link.l1 = "Czy nie widzisz, jak daleko to zaszło? Wygląda na to, że jesteśmy w tej samej łajbie, Charlie. Więc mam prawo znać szczegóły.";
			link.l1.go = "DTSG_Knippel_82";
		break;
		
		case "DTSG_Knippel_82":
			dialog.text = "Oczywiście, Kapitanie. Ale nie tutaj, prawda? Zejdźmy z wyspy i porozmawiajmy na statku.";
			link.l1 = "Masz rację. Dobra, pospieszmy się.";
			link.l1.go = "DTSG_Knippel_83";
		break;
		
		case "DTSG_Knippel_83":
			DialogExit();
			AddQuestRecord("DTSG", "16");
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			DeleteAttribute(pchar,"questTemp.TimeLock");
			chrDisableReloadToLocation = false;
			//LAi_LocationDisableOfficersGen("SentJons_town", false);
			LAi_LocationDisableOfficersGen("SentJons_bank", false);
			
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition = "DTSG_KnippelRazgovorVKaute";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom":
			dialog.text = "Wołałeś, Kapitanie?";
			link.l1 = "Tak, Charlie. Musimy porozmawiać. Myślę, że już się domyśliłeś, o co chodzi.";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_2";
			DelLandQuestMark(npchar);
			//LAi_LocationDisableOfficersGen("SentJons_town", true);
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_2":
			dialog.text = "Tak, panie...";
			link.l1 = "Dobrze. Powiedz mi, dlaczego twoi rodacy, w tym siły elitarne, polują na ciebie, skoro nie jesteś przestępcą ani nikim takim.";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_3";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_3":
			dialog.text = "Naprawdę nie wiem, panie...";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				link.l1 = "To nie żart, Charlie. Ktokolwiek cię ściga, może wydawać rozkazy morskim lisom. Pewnie jest też za morderstwem Richarda. Więc jeśli masz jakieś myśli, podziel się nimi. Jakie to pozdrowienia z Sussex, kto to jest?";
			}
			else
			{
				link.l1 = "Przestań odwracać wzrok, Charlie. Widzę, że coś wiesz. Jako twój kapitan, rozkazuję ci powiedzieć mi wszystko. Kim jest Sussex?";
			}
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_4";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_4":
			dialog.text = "Dobrze, kapitanie. Sussex to nie osoba. To... statek.";
			link.l1 = "Pozdrowienia z okrętu? To bzdura.";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_5";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_5":
			dialog.text = "Pozwól, że wyjaśnię. Czy mogę usiąść, panie? Opowieść jest długa i niezbyt przyjemna.";
			link.l1 = "Oczywiście, Charlie. Śmiało.";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_6";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_6":
			DialogExit();
			SetCurrentTime(2, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			SetMainCharacterIndex(GetCharacterIndex("Knippel"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			DoQuestReloadToLocation("SentJons_houseH1", "goto", "goto2", "DTSG_KnippelDoma");
		break;
		
		case "DTSG_Kurier":
			dialog.text = "Ej, Charlie, jestem od kapitana Fleetwooda. Chce cię zobaczyć.";
			link.l1 = "Dzięki, kamracie. Coś się stało? Zwykle wszystko przesyła przez ciebie od razu.";
			link.l1.go = "DTSG_Kurier_2";
		break;
		
		case "DTSG_Kurier_2":
			dialog.text = "Nie wiem. Mówi, że chce to omówić z tobą bezpośrednio. To twoja sprawa, załatwcie to między sobą.";
			link.l1 = "O, mam złe przeczucia co do tego...";
			link.l1.go = "DTSG_Kurier_3";
		break;
		
		case "DTSG_Kurier_3":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "", "", "", "", -1);
			npchar.lifeday = 0;
			npchar.location = "None";
			
			PChar.quest.DTSG_KD1.win_condition.l1 = "locator";
			PChar.quest.DTSG_KD1.win_condition.l1.location = "SentJons_houseH1";
			PChar.quest.DTSG_KD1.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_KD1.win_condition.l1.locator = "reload1";
			PChar.quest.DTSG_KD1.win_condition = "DTSG_KD1";
			
			PChar.quest.DTSG_KD2.win_condition.l1 = "locator";
			PChar.quest.DTSG_KD2.win_condition.l1.location = "SentJons_town";
			PChar.quest.DTSG_KD2.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_KD2.win_condition.l1.locator = "houseSp3";
			PChar.quest.DTSG_KD2.win_condition = "DTSG_KD2";
			
			pchar.questTemp.Knippel.Soldiers_1 = true;
		break;
		
		case "DTSG_Cortny":
			dialog.text = "...";
			link.l1 = "Dobranoc, panie!";
			link.l1.go = "DTSG_Cortny_2";
		break;
		
		case "DTSG_Cortny_2":
			dialog.text = "Dobranoc. Pozwól mi przejść.";
			link.l1 = "Oczywiście, śmiało, przepraszam, sir.";
			link.l1.go = "DTSG_Cortny_3";
		break;
		
		case "DTSG_Cortny_3":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "", "", "", "", -1);
			npchar.lifeday = 0;
			npchar.location = "None";
			
			PChar.quest.DTSG_KD4.win_condition.l1 = "locator";
			PChar.quest.DTSG_KD4.win_condition.l1.location = "SentJons_houseSP3";
			PChar.quest.DTSG_KD4.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_KD4.win_condition.l1.locator = "reload2";
			PChar.quest.DTSG_KD4.win_condition = "DTSG_KD4";
			
			sld = CharacterFromID("Fleetwood");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_houseSP3_room", "goto", "goto1");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Fleetwood";
			sld.greeting = "";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "DTSG_Fleetwood":
			dialog.text = "Ach, to ty, Charlie. Wejdź, wejdź. Zamknij za sobą drzwi.";
			link.l1 = "Dobranoc, Kapitanie. Co się dzieje? A kim był tamten człowiek? Nadęty paw...";
			link.l1.go = "DTSG_Fleetwood_2";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_Fleetwood_2":
			dialog.text = "Na to, nie mogę odpowiedzieć. Ani nie mogę pozwolić, by ktoś podsłuchał naszą rozmowę. Nie mów nikomu o tym, rozumiesz?";
			link.l1 = "Tak, panie. Czy coś się stało? Wyglądasz niepokojąco, co do ciebie niepodobne.";
			link.l1.go = "DTSG_Fleetwood_3";
		break;
		
		case "DTSG_Fleetwood_3":
			dialog.text = "Wydaje ci się. Ty też nie wyglądasz najlepiej - w końcu jest noc. Ale obawiam się, że twój sen na dziś się skończył, przyjacielu - mamy pilną i tajną misję.";
			link.l1 = "A co to będzie obejmować, Kapitanie?";
			link.l1.go = "DTSG_Fleetwood_4";
		break;
		
		case "DTSG_Fleetwood_4":
			dialog.text = "Eliminacja zdrajcy. Z naszych własnych. Wkrótce u wybrzeży Dominiki pojawi się dyplomatyczny statek ze Starego Świata - fregata 'Sussex'. Oficjalnie mają negocjować dobry układ z Holendrami. Ale w rzeczywistości...";
			link.l1 = "... czy mają zamiar przekazać informacje naszym wrogom, sir?";
			link.l1.go = "DTSG_Fleetwood_5";
		break;
		
		case "DTSG_Fleetwood_5":
			dialog.text = "Jeszcze gorzej. Całkowicie przejść na ich stronę. I chociaż będą wyczerpani po przekroczeniu Atlantyku, w końcu to dobra fregata, która na pewno spróbuje uciec, jeśli zaatakujemy ciężkim statkiem.\nMusimy więc działać szybko i zdecydowanie. Możemy polegać tylko na 'Valkyrii' - tylko ona jest zdolna do takiej misji.";
			link.l1 = "Czy stara 'Walkiria' poradzi sobie z fregatą?..";
			link.l1.go = "DTSG_Fleetwood_6";
		break;
		
		case "DTSG_Fleetwood_6":
			dialog.text = "Ha-ha, Charlie, czy wątpisz w swojego kapitana? Poza tym, jak mówiłem, będą wyczerpani. Jeśli zaatakujemy nagle, wszystkie przewagi będą po naszej stronie.";
			link.l1 = "Ja bym nigdy! Ale mam nadzieję, że wiesz, co robisz, sir...";
			link.l1.go = "DTSG_Fleetwood_7";
		break;
		
		case "DTSG_Fleetwood_7":
			dialog.text = "Jestem tego pewien. I jeszcze jedno. Ten dezerter zajmuje wysokie stanowisko w samym Parlamencie, rozumiesz? Może mieć oczy i uszy wszędzie - nie tylko w kraju, ale już tutaj, na Karaibach. Więc nie wspominaj o Sussex ani żadnych szczegółach naszej misji w mieście.";
			link.l1 = "Nie musiałeś mi tego mówić, panie. Zawsze możesz liczyć na starego Charliego.";
			link.l1.go = "DTSG_Fleetwood_8";
		break;
		
		case "DTSG_Fleetwood_8":
			dialog.text = "Znam to. Tylko tym razem stawka jest wyższa niż kiedykolwiek. Zbierz swoje rzeczy i przygotuj się - wypływamy o świcie.";
			link.l1 = "Tak jest, panie. Dobranoc, panie.";
			link.l1.go = "DTSG_Fleetwood_9";
		break;
		
		case "DTSG_Fleetwood_9":
			DoQuestReloadToLocation("SentJons_town", "reload", "houseSp3", "");
			
			PChar.quest.DTSG_KD5.win_condition.l1 = "locator";
			PChar.quest.DTSG_KD5.win_condition.l1.location = "SentJons_town";
			PChar.quest.DTSG_KD5.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_KD5.win_condition.l1.locator = "houseH1";
			PChar.quest.DTSG_KD5.win_condition = "DTSG_KD5";
		break;
		
		case "DTSG_Knippel_SamSoboi":
			dialog.text = "Jeszcze nigdy nie widziałem Richarda w takim stanie... Był tak zmartwiony czy nawet... przestraszony?";
			link.l1 = "Ale dlaczego? Nawet się tym ze mną nie podzielił. No, nieważne. Jest świetnym kapitanem, więc na pewno poradzimy sobie z tą fregatą i jej zmęczoną załogą.";
			link.l1.go = "DTSG_Knippel_SamSoboi_2";
			DeleteAttribute(pchar, "questTemp.lockedMusic");
		break;
		
		case "DTSG_Knippel_SamSoboi_2":
			DialogExit();
			SetLaunchFrameFormParam("August 17th, 1654"+ NewStr() +", SE of Dominica", "DTSG_ProshloeDominika", 0, 4.0);
			LaunchFrameForm();
			DeleteAttribute(pchar, "questTemp.Knippel.Soldiers_1");
			DeleteAttribute(pchar, "questTemp.Knippel.Soldiers_2");
			DeleteAttribute(pchar, "questTemp.Knippel.Soldiers_3");
		break;
		
		case "DTSG_Fleetwood_10":
			dialog.text = "Sussex' jest na horyzoncie, Charlie, przygotuj się.";
			link.l1 = "Zawsze gotowy, Kapitanie.";
			link.l1.go = "DTSG_Fleetwood_11";
		break;
		
		case "DTSG_Fleetwood_11":
			dialog.text = "Bardzo dobrze. Liczę na ciebie i twoje kartacze. Spróbuj rozerwać im żagle jak najszybciej, a jeszcze lepiej, obalić maszt. Wdawanie się w ryzykowną walkę, by ich zatopić, nie ma sensu, więc spróbuję ich abordażować.\nPoza tym musimy się upewnić, że zdrajca nie żyje - jeśli ich zatopimy, i tak będziemy musieli podejść bliżej i upewnić się, że nikt nie przeżył.";
			link.l1 = "I zabić tylu rodaków dla jednego zdrajcy...";
			link.l1.go = "DTSG_Fleetwood_12";
		break;
		
		case "DTSG_Fleetwood_12":
			dialog.text = "Niestety. Mnie też to boli, Charlie. Ale rozkazy to rozkazy. Przynajmniej nie robimy tego dla zabawy. Więc załatwmy to szybko.";
			link.l1 = "Tak, panie...";
			link.l1.go = "DTSG_Fleetwood_13";
		break;
		
		case "DTSG_Fleetwood_13":
			DialogExit();
			EndQuestMovie();
			AddItems(pchar, "potion4", 10);
			AddItems(pchar, "bullet", 10);
			AddItems(pchar, "GunPowder", 10);
			AddItems(pchar, "grapeshot", 10);
			AddItems(pchar, "cartridge", 10);
			PlaySound("interface\abordage.wav");
			PlaySound("interface\abordage.wav");
			PlaySound("interface\MusketFire1.wav");
			PlaySound("interface\MusketFire1.wav");
			
			SetLaunchFrameFormParam("2 hours later..."+ NewStr() +"Boarding the 'Sussex'", "DTSG_ProshloeDominika_11", 0, 4.0);
			LaunchFrameForm();
			
			n = Findlocation("Location_reserve_06");
			DeleteAttribute(&locations[n], "IslandId");
			DeleteAttribute(&locations[n], "type");
			DeleteAttribute(&locations[n], "models");
			DeleteAttribute(&locations[n], "environment");
			DeleteAttribute(&locations[n], "Box1");
			DeleteAttribute(&locations[n], "Box2");
			DeleteAttribute(&locations[n], "Box3");
			Locations[n].id.label = "Orlop deck";
			Locations[n].filespath.models = "locations\decks\oldeck";
			Locations[n].image = "loading\Boarding_B" + rand(3) + ".tga";
			//Sound
			locations[n].type = "deck_fight";
			//Models
			//Always
			Locations[n].models.always.ODeck = "oldeck";
			Locations[n].models.always.locators = "oldeck_locators";

			//Day
			Locations[n].models.day.charactersPatch = "oldeck_patch";
			Locations[n].models.day.fonar = "oldeck_fday";
			//Night
			Locations[n].models.night.charactersPatch = "oldeck_patch";
			Locations[n].models.night.fonar = "oldeck_fnight";
			//Environment
			Locations[n].environment.sea = "true";
			Locations[n].environment.weather = "true";
		break;
		
		case "DTSG_Graf_Sheffild_1":
			StartQuestMovie(true, false, true);
			dialog.text = "Dostatecznie! Jestem gotów złożyć mój miecz i omówić twoje żądania. Ale najpierw, przedstaw się! Kim jesteś i jak śmiesz nas atakować?! To jest zdrada!";
			link.l1 = "";
			link.l1.go = "DTSG_Graf_Sheffild_2";
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_2":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_3":
			dialog.text = "Kapitan Richard Fleetwood. A ty musisz być hrabią Sheffield? I masz absolutną rację, to jest zdrada.";
			link.l1 = "";
			link.l1.go = "DTSG_Graf_Sheffild_5";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;
		case "DTSG_Graf_Sheffild_5":
			DialogExit();
			sld = CharacterFromID("DTSG_Graf_Sheffild");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_6";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_6":
			dialog.text = " Wiesz, kim jestem? Do diabła! Wiedziałem, że coś takiego się stanie, szczury są wszędzie, więc prosiłem, nawet błagałem o okręt wojenny...";
			link.l1 = "";
			link.l1.go = "DTSG_Graf_Sheffild_7";
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_7":
			DialogExit();
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_8";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_8":
			dialog.text = "To by cię nie uratowało, tylko przedłużyło nieuniknione, bo znalazłbym inną drogę. I tak, przez zdradę, mam na myśli twoją, hrabio Sheffield.";
			link.l1 = "";
			link.l1.go = "DTSG_Graf_Sheffild_9";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;
		case "DTSG_Graf_Sheffild_9":
			DialogExit();
			sld = CharacterFromID("DTSG_Graf_Sheffild");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_10";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_10":
			dialog.text = "Zatem nic pan o mnie nie wie, panie! Wszyscy wiedzą, że nie ma bardziej lojalnego człowieka wobec Anglii niż ja! Pożałujesz tego błędu, zapamiętaj moje słowa.";
			link.l1 = "";
			link.l1.go = "DTSG_Graf_Sheffild_12";
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_12":
			DialogExit();
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_13";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_13":
			dialog.text = "Nie mam czego żałować, bo to nie ja zdradzam na rzecz Holendrów.";
			link.l1 = "";
			link.l1.go = "DTSG_Graf_Sheffild_15";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;
		case "DTSG_Graf_Sheffild_15":
			DialogExit();
			sld = CharacterFromID("DTSG_Graf_Sheffild");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_16":
			dialog.text = "Co?! Jakie bzdury wygadujesz?! Zostałeś wprowadzony w błąd i podążyłeś za fałszywym tropem jak szalony pies\nAhem, to prawda, zmierzam na negocjacje z Holenderską Kompanią Zachodnioindyjską. Ale w interesie naszej Anglii, Kapitanie. To okropna pomyłka, ale wciąż możemy ją naprawić.";
			link.l1 = "";
			link.l1.go = "DTSG_Graf_Sheffild_17";
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_17":
			DialogExit();
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_18";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_18":
			dialog.text = "Obawiam się, że to nie zależy ode mnie. I na pewno nie od was. Wybraliście złą stronę, panowie. Żegnajcie.";
			link.l1 = "";
			link.l1.go = "DTSG_Graf_Sheffild_19";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;

		case "DTSG_Graf_Sheffild_19":
			DialogExit();
			LAi_SetActorType(pchar);
			sld = CharacterFromID("Fleetwood");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "1", 1.8);
			DoQuestCheckDelay("DTSG_Graf_Sheffild_20", 0.9);
		break;
		
		case "DTSG_Graf_Sheffild_22":
			dialog.text = "Zrobione. Myślałem, że ten gruby człowiek nigdy nie przestanie piszczeć. Ach, ci hrabiowie, prawda, Charlie?";
			link.l1 = "Ciekawi mnie tylko, panie, co jeśli pułkownik się mylił? Albo, nie daj Boże, okłamał nas, żeby pozbyć się hrabiego?";
			link.l1.go = "DTSG_Graf_Sheffild_23";
		break;
		
		case "DTSG_Graf_Sheffild_23":
			dialog.text = "Słuchaj mnie, przyjacielu. I słuchaj uważnie. Nasza służba jest bardzo niebezpieczna i trudna, w każdym aspekcie. Może zdarzyć się wszystko - smutna pomyłka, śmieszny zbieg okoliczności, czy zdradziecka zdrada\nSłużba krajowi to nie tylko ładowanie dział kulami armatnimi, Charlie. Dla władzy to podejmowanie trudnych decyzji. A dla żołnierzy takich jak my - wykonywanie tych decyzji.";
			link.l1 = "Ale co, jeśli pewnego dnia przelejemy niewinną krew, kapitanie? To będzie na naszych rękach, na naszym sumieniu.";
			link.l1.go = "DTSG_Graf_Sheffild_24";
		break;
		
		case "DTSG_Graf_Sheffild_24":
			dialog.text = "Zatem krew będzie na ich rękach tak samo jak na naszych, jeśli nie bardziej. Niech to cię pocieszy. Najważniejsze, że nasze intencje były czyste - wyeliminować wroga ojczyzny\nTeraz pomóż mi, Charlie, musimy jeszcze sprawić, by to wyglądało jak atak Holendrów.";
			link.l1 = "Tak, sir...";
			link.l1.go = "DTSG_Graf_Sheffild_25";
		break;
		
		case "DTSG_Graf_Sheffild_25":
			DialogExit();
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_Kortni", "off_eng_5", "man", "man", 40, ENGLAND, -1, false, "quest"));
			sld.name = "Thomas";
			sld.lastname = "Lynch";
			sld.rank = 40;
			GiveItem2Character(sld, "blade_16");
			EquipCharacterByItem(sld, "blade_16");
			GiveItem2Character(sld, "pistol6");
			EquipCharacterByItem(sld, "pistol6");
			SetSelfSkill(sld, 100, 100, 100, 100, 100);
			LAi_SetHP(sld, 400.0, 400.0);
			FantomMakeCoolSailor(sld, SHIP_HIMERA, "Сhimera", CANNON_TYPE_CANNON_LBS20, 70, 70, 70);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Tireless");
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			SetCharacterPerk(sld, "Sliding");
			SetCharacterPerk(sld, "HardHitter");
			SetCharacterPerk(sld, "SwordplayProfessional");
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "ShipTurnRateUp");
			SetCharacterPerk(sld, "StormProfessional");
			SetCharacterPerk(sld, "WindCatcher");
			SetCharacterPerk(sld, "SailsMan");
			SetCharacterPerk(sld, "Doctor1");
			SetCharacterPerk(sld, "MusketsShoot");
			SetCharacterPerk(sld, "LongRangeGrappling");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "SailsDamageUp");
			SetCharacterPerk(sld, "CrewDamageUp");
			SetCharacterPerk(sld, "CriticalShoot");
			SetCharacterPerk(sld, "BasicCommerce");
			SetCharacterPerk(sld, "AdvancedCommerce");
			sld.Ship.Mode = "war";
			sld.alwaysEnemy = true;
			sld.Coastal_Captain = true;
			sld.AlwaysSandbankManeuver = true;
			sld.DontRansackCaptain = true;
			
			Group_FindOrCreateGroup("DTSG_KortniAttack");
			Group_SetType("DTSG_KortniAttack", "pirate");
			Group_AddCharacter("DTSG_KortniAttack", "DTSG_Kortni");

			Group_SetGroupCommander("DTSG_KortniAttack", "DTSG_Kortni");
			Group_SetTaskAttack("DTSG_KortniAttack", PLAYER_GROUP);
			Group_SetAddress("DTSG_KortniAttack", "Antigua", "Quest_Ships", "Quest_Ship_10");
			Group_LockTask("DTSG_KortniAttack");
			
			SetLaunchFrameFormParam("Present time", "DTSG_SegodnyaVremya", 0, 4.0);
			LaunchFrameForm();
		break;
		
		case "DTSG_Knippel_101":
			dialog.text = "Zostawiliśmy fałszywe dowody, aby wyglądało na to, że zrobili to Holendrzy. Richard i ja nigdy więcej nie rozmawialiśmy o tym dniu.";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				link.l1 = "Cóż, teraz wiele nabiera sensu. Myślę, że za śmiercią Richarda stoi krewny lub zwolennik hrabiego. Ale dlaczego celują w ciebie? Jesteś tylko kanonierem i nie podejmowałeś żadnych decyzji tamtego smutnego dnia.";
				link.l1.go = "DTSG_Knippel_ZS_102";
				AddComplexLandExpToScill(50, 50, 50);
				Log_info("Experience bonus received");
			}
			else
			{
				link.l1 = "„Rzeczywiście. To paskudna sprawa i śmierdzi. Może ktoś się dowiedział i postanowił pomścić hrabiego. Ale czy jeden kanonier wart jest takich wydatków? Pieniądze, najemnicy, zatrudnianie Morskich Lisów... Nie ma mowy, Charlie.”";
				link.l1.go = "DTSG_Knippel_NS_102";
			}
		break;
		
		case "DTSG_Knippel_ZS_102":
			dialog.text = "Może ta osoba ściga wszystkich z dawnej załogi Richarda. Co o tym sądzisz, sir?";
			link.l1 = "Myślę, że powinniśmy oddalić się od Antigui, im szybciej, tym lepiej.";
			link.l1.go = "DTSG_Knippel_103";
		break;
		
		case "DTSG_Knippel_NS_102":
			dialog.text = "Zadałem sobie to pytanie również, kapitanie, ale nie znalazłem odpowiedzi.";
			link.l1 = "Cholera. Ktoś nadchodzi. Prosiłem, by mi nie przeszkadzano!";
			link.l1.go = "DTSG_Knippel_103";
		break;
		
		case "DTSG_Knippel_103":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
			{
				sld = characterFromId("Helena");
				ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
				sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
				sld.dialog.currentnode = "DTSG_Helena_1";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", 0, 0);
				break;
			}
			if (GetCharacterIndex("Tichingitu") != -1 && CheckPassengerInCharacter(pchar, "Tichingitu"))
			{
				sld = characterFromId("Tichingitu");
				ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
				sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
				sld.dialog.currentnode = "DTSG_Tichingitu_1";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", 0, 0);
				break;
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("Alonso", "Alonso", "man", "man", sti(pchar.rank), pchar.nation, 0, true, "soldier"));
				sld.name 	= "Alonso";
				sld.lastname = "";
				ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
				sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
				sld.dialog.currentnode = "DTSG_Alonso_1";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", 0, 0);
				sld.location = "None";
			}
		break;
		
		case "DTSG_Helena_1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "Charles!..";
				link.l1 = "Co się stało, Helen??";
				link.l1.go = "DTSG_Helena_2";
			}
			else
			{
				dialog.text = "Charles, pamiętam, że prosiłeś mnie, by nikogo nie wpuszczać i nie przeszkadzać wam z Charliem, ale...";
				link.l1 = "... zdecydowałeś się przyjść osobiście. Dobrze, dobrze, Helen.";
				link.l1.go = "DTSG_Helena_2";
			}
		break;
		
		case "DTSG_Helena_2":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "Angielski okręt wojenny! Został dostrzeżony jakiś czas temu. Na początku nie zwróciłem uwagi, ale zaraz do nas dotrze! Nigdy nie widziałem tak szybkiego statku.";
				link.l1 = "Dzięki za informacje. Mam nadzieję, że mamy czas się przygotować, zanim się zbliży. Helen, Charlie, na stanowiska bojowe!";
				link.l1.go = "DTSG_GotovimsyKBitve";
			}
			else
			{
				dialog.text = "... możecie kontynuować swoje tajne spotkanie później. Angielski okręt wojenny zbliża się w naszym kierunku. Myślałem, że to ważne.";
				link.l1 = "Cóż, pójdę się rozejrzeć. Dzięki, Helen.";
				link.l1.go = "DTSG_GotovimsyKBitve";
			}
		break;
		
		case "DTSG_Tichingitu_1":
			dialog.text = "Kapitanie, szybki statek płynie w naszą stronę. Bardzo szybko. Duchy szepczą mi, że ich zamiary są złowieszcze.";
			link.l1 = "Dziękuję tobie i duchom za ostrzeżenie. Przygotuj się do bitwy na wszelki wypadek. I przekaż tę wiadomość innym ode mnie.";
			link.l1.go = "DTSG_GotovimsyKBitve";
		break;
		
		case "DTSG_Alonso_1":
			dialog.text = "Przepraszam za przerwanie, Kapitanie, ale to pilne.";
			link.l1 = "Och, mam nadzieję, że to naprawdę ważne, Alonso. Zgłaszaj się.";
			link.l1.go = "DTSG_Alonso_2";
		break;
		
		case "DTSG_Alonso_2":
			dialog.text = "Angielski statek się zbliża. To... 'Mirage', Kapitanie.";
			link.l1 = "Co? Jesteś absolutnie pewien? Znowu piłeś, co?";
			link.l1.go = "DTSG_Alonso_3";
		break;
		
		case "DTSG_Alonso_3":
			dialog.text = "Jestem pewien, Kapitanie - nie ma drugiego takiego statku na Karaibach, wiesz o tym.";
			link.l1 = "Rzeczywiście. Sam się temu przyjrzę - zobaczymy, czy ten 'Mirage' jest prawdziwy.";
			link.l1.go = "DTSG_GotovimsyKBitve";
		break;
		
		case "DTSG_GotovimsyKBitve":
			DialogExit();
			AddQuestRecord("DTSG", "17");
			
			if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
			{
				sld = characterFromId("Helena");
				LAi_SetOfficerType(sld);
				sld.Dialog.Filename = "Quest\Saga\Helena.c";
				sld.Dialog.CurrentNode = "Helena_officer";
			}
			if (GetCharacterIndex("Tichingitu") != -1 && CheckPassengerInCharacter(pchar, "Tichingitu"))
			{
				sld = characterFromId("Tichingitu");
				LAi_SetOfficerType(sld);
				sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
				sld.Dialog.CurrentNode = "Tichingitu_officer";
			}
			if (GetCharacterIndex("Knippel") != -1 && CheckPassengerInCharacter(pchar, "Knippel"))
			{
				sld = characterFromId("Knippel");
				LAi_SetOfficerType(sld);
				sld.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
				sld.Dialog.CurrentNode = "Knippel_officer";
			}
			
			PChar.quest.DTSG_KortniPotopil.win_condition.l1 = "Character_sink";
			PChar.quest.DTSG_KortniPotopil.win_condition.l1.character = "DTSG_Kortni";
			PChar.quest.DTSG_KortniPotopil.win_condition = "DTSG_KortniPotopil";
			
			chrDisableReloadToLocation = false;
			bDisableCharacterMenu = false;
			InterfaceStates.Buttons.Save.enable = true;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			DeleteAttribute(pchar, "GenQuest.CannotWait");
		break;
		
		case "DTSG_Kortni":
			dialog.text = "Och... Ale to jeszcze nie koniec! Brian, oto jesteś! Gdzie do cholery byłeś?";
			link.l1 = "To tylko opóźni nieuniknione.";
			link.l1.go = "DTSG_Kortni_Pikar";
		break;
		
		case "DTSG_Kortni_Pikar":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			LAi_SetWarriorType(npchar);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetCheckMinHP(npchar, 10, true, "DTSG_KortniRanen");
			LAi_SetImmortal(npchar, false);
			
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_Mrt_Rocur", "citiz_8", "man", "man", sti(pchar.rank), ENGLAND, -1, false, "soldier"));
			sld.name = "Brian";
			sld.lastname = "Tasse";
			GiveItem2Character(sld, "blade_20");
			EquipCharacterByItem(sld, "blade_20");
			GiveItem2Character(sld, "pistol5");
			EquipCharacterByItem(sld, "pistol5");
			AddItems(sld, "purse2", 1);
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
			LAi_SetHP(sld, 300.0, 300.0);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetCheckMinHP(sld, 10, true, "DTSG_PikarRanen");
			sld.location = "None";
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "DTSG_Kortni_1":
			dialog.text = "Charles de Maure. Pomyśleć, jak daleko zaszedłeś. Szkoda. Miałem nadzieję zaskoczyć cię na tym statku.";
			link.l1 = "Znasz mnie? A więc to ty stoisz za naszymi ostatnimi kłopotami - wyglądasz jak ptak wysoko latający, zmuszony opuścić przytulne gniazdo i wyjść osobiście, zamiast wysyłać kolejnego sępa.";
			link.l1.go = "DTSG_Kortni_2";
			
			Island_SetReloadEnableGlobal("Antigua", true);
			bQuestDisableMapEnter = false;
			LAi_LocationDisableOfficersGen("SentJons_town", false);
			DeleteQuestCondition("DTSG_KortniPotopil");
		break;
		
		case "DTSG_Kortni_2":
			dialog.text = "Zgadza się, w obu przypadkach. Przypuszczam, że szlachcic potrafi rozpoznać innego z daleka. Pułkownik Thomas Lynch. Wygląda na to, że nadszedł czas, by porozmawiać jak dżentelmeni, zamiast próbować się zniszczyć. Być może uda nam się osiągnąć wzajemnie korzystne porozumienie.";
			link.l1 = "Nie mogę niczego obiecać, ale daję ci moje słowo jako szlachcic, że przynajmniej porozmawiamy jak cywilizowani ludzie, pułkowniku.";
			link.l1.go = "DTSG_Kortni_3";
		break;
		
		case "DTSG_Kortni_3":
			dialog.text = "Bardzo dobrze. Nie mógłbym mieć takiej rozmowy z Fleetwoodem. Mimo to, znaleźliśmy na niego haka i już nas nie będzie niepokoił. Szkoda, że z tobą się nie udało, ale mniejsza z tym.";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				link.l1 = "Całe Karaiby mówią o śmierci Richarda. Więc, to byłeś ty! A tak przy okazji, tą kartą przetargową, o której wspomniałeś, była Abigail? Co się z nią stało, tak na marginesie?";
				AddComplexLandExpToScill(50, 50, 50);
				Log_info("Experience bonus received");
			}
			else
			{
				link.l1 = "Nie groźba, powiadasz?.. Więc, zabiłeś go? Jesteś zwolennikiem hrabiego?";
			}
			link.l1.go = "DTSG_Kortni_4";
		break;
		
		case "DTSG_Kortni_4":
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				dialog.text = "Abigail? Ach, młoda Żydówka, jego narzeczona. Raz jeszcze, udowodniłeś, że jesteś całkiem przenikliwą osobą. Ona żyje i ma się dobrze - obiecaliśmy to i dotrzymaliśmy słowa w zamian za współpracę Fleetwooda.";
				link.l1 = "Muszę przyznać, że to całkiem współpraca. Ale dlaczego to zrobiłeś? Jesteś zwolennikiem hrabiego?";
			}
			else
			{
				dialog.text = "Wspierasz? Och, wręcz przeciwnie. Ale widzisz, niektóre karty nie mogą już być zagrane, gdyż stają się ciężarem dla gracza. Niestety, Richard stał się jedną z nich.";
				link.l1 = "Widzę. Usuwasz wszystkich świadków. Co się stało z Abigail? Też ją zabiłeś?";
			}
			link.l1.go = "DTSG_Kortni_5";
		break;
		
		case "DTSG_Kortni_5":
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				dialog.text = "Nie, wcale nie. Wręcz przeciwnie. Ale Richard wiedział za dużo, a powracając do Starego Świata, stał się niebezpieczny. Powinien był tu zostać, a nie odebralibyśmy mu życia.";
				link.l1 = "Eliminujesz każdego, kto kiedykolwiek dla ciebie pracował, pułkowniku?";
			}
			else
			{
				dialog.text = "Kto? Ach, jego narzeczona, jak mniemam. Ona była dźwignią. Jego życie za jej. Ma się dobrze, przysięgam na mój honor.";
				link.l1 = "Wątpię, że wiesz, czym jest honor, biorąc pod uwagę to, co zrobiłeś, pułkowniku.";
			}
			link.l1.go = "DTSG_Kortni_6";
		break;
		
		case "DTSG_Kortni_6":
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				dialog.text = "Nie odpowiem na tę prowokację, sir.";
				link.l1 = "Więc odpowiedz na to - jak zdobyłeś ten statek? Czy to... 'Mirage'?";
			}
			else
			{
				dialog.text = "Przymknę oko na tę zniewagę, bo pochodzi od kogoś, kto nigdy nie musiał dzierżyć władzy ani wpływać na porządek rzeczy.";
				link.l1 = "Skoro już o tym mowa, skąd masz 'Mirage'? Czy to ona?";
			}
			link.l1.go = "DTSG_Kortni_7";
		break;
		
		case "DTSG_Kortni_7":
			dialog.text = "Nie do końca. Wspaniały okręt, co? Szkoda, że nie spełnił swego przeznaczenia przeciwko tobie. Znasz historię tego okrętu, kapitanie de Maure?";
			link.l1 = "Masz na myśli statek-widmo i polowanie na angielskich kupców?";
			link.l1.go = "DTSG_Kortni_8";
		break;
		
		case "DTSG_Kortni_8":
			dialog.text = "To? Och, nie. Nie mówię o rzeczach powszechnie znanych. Mam na myśli rzeczy ukryte przed wzrokiem. Ten kecz został zaprojektowany przez Johana van Merdena i Lucasa Rodenburga\nTa słodka para stworzyła łańcuch machinacji, a statek ostatecznie został zwodowany z stoczni w Hawanie. Mieliśmy szczęście zdobyć oryginalne plany. I w końcu odtworzyliśmy Mirage w całej jej chwale, a nawet ją ulepszyliśmy, poprawiając niektóre wady w jej projekcie.";
			link.l1 = "Szkoda, jak sam zauważyłeś, niewiele ci to pomogło, pułkowniku.";
			link.l1.go = "DTSG_Kortni_9";
		break;
		
		case "DTSG_Kortni_9":
			dialog.text = "Masz ochotę na śmiech? Nie powinieneś. Przyznaję, że przewyższyłeś mnie zarówno jako kapitan, jak i wojownik. Ale wciąż mam tutaj przewagę.";
			link.l1 = "Czy to umierający blef? Czy po prostu zwykła pewność siebie ludzi takich jak ty? Co kryje się za tymi słowami?";
			link.l1.go = "DTSG_Kortni_10";
		break;
		
		case "DTSG_Kortni_10":
			dialog.text = "Doskonałe pytanie. Wydaje mi się, że jesteś kimś więcej niż tylko rozrywkowym rozpustnikiem i pojedynkowiczem, jak sugerowały moje badania. Podjąłem środki na wszystkie możliwe wyniki tego spotkania. Nawet ten, gdzie ginę od twojego ostrza, kuli lub zbłąkanego odłamka armatniego. Jeśli dziś zginę, ty i Charlie pożałujecie, że nie dołączyliście do Fleetwooda.";
			link.l1 = "Więcej łowców nagród? Proszę. To było nieprzyjemne i żmudne, ale nie śmiertelne. Wtedy ich odpędziliśmy - odpędzimy ich znowu.";
			link.l1.go = "DTSG_Kortni_11";
		break;
		
		case "DTSG_Kortni_11":
			dialog.text = "Nie mam wątpliwości. Teraz znów widzę beztroskiego szermierza. Nie tylko łowcy nagród. Cała siła Morskich Lisów i angielskiego wywiadu morskiego runie na twoją głowę jak burzowa fala na łódź rybacką.";
			link.l1 = "Czego ode mnie chcesz? Nie oczekujesz, że się poddam?";
			link.l1.go = "DTSG_Kortni_12";
		break;
		
		case "DTSG_Kortni_12":
			dialog.text = "Oczywiście, że nie. Studiowaliśmy cię dobrze przez cały ten czas. Chcę ci zaproponować wzajemnie korzystny układ. Taki, którego nie byłoby mądrze odrzucić. I jako dwóch szlachetnych mężów, mam nadzieję, że możemy dojść do porozumienia.";
			link.l1 = "W takim razie powtarzam pytanie, pułkowniku, czego chcesz? Zakładam, że chodzi o Charliego?.. I myślisz, że możesz mi coś zaoferować w zamian? Nie zdradzę za kilka złotych monet.";
			link.l1.go = "DTSG_Kortni_13";
		break;
		
		case "DTSG_Kortni_13":
			dialog.text = "Zgadza się. Nie chodzi tylko o kilka złotych monet, jak to ująłeś, ale o całą górę - 10 000 dublonów. Depozyt będzie czekał na ciebie u bankiera w Port Royal, jeśli dojdziemy do porozumienia\nAle najważniejsze, co oferuję, to twoje życie, kapitanie de Maure. Słyszałeś mnie. Zaprzestaniemy wszelkich pościgów, jeśli wszyscy teraz złożymy broń, a ty wydasz nam Charliego\nSłyszałeś o wyrażeniu 'człowiek przeciwko społeczeństwu'? W twoim przypadku, jeśli odmówisz, będzie to 'człowiek przeciwko państwu'. Decyduj, Charles. Tutaj i teraz.";
			link.l1 = "Możesz łatwo wykorzystać swój tytuł i wpływy, by zastraszyć jakiegoś głupca. Ale ja nie jestem głupcem. I wyczuwam desperację na milę. Wynoś się. I ciesz się, że cię nie zabiłem - zasługujesz na to.";
			link.l1.go = "DTSG_Kortni_PkCh_1";
			link.l2 = "Nie potrzebujesz naprawdę Charliego, pułkowniku. Potrzebujesz jego milczenia.";
			link.l2.go = "DTSG_Kortni_LT_1";
			link.l3 = "Zgadzam się na to dla bezpieczeństwa siebie i moich ludzi, nie z chciwości na twoje pieniądze, żebyś wiedział.";
			link.l3.go = "DTSG_Kortni_Sdat";
		break;
		
		case "DTSG_Kortni_PkCh_1":
			dialog.text = "Podjąłeś jedną z najgorszych decyzji w swoim życiu, kapitanie de Maure. Nie zazdroszczę ci. Szczerze. Będziesz miał pretensje tylko do siebie - nikt nie złoży ci podobnych ofert ponownie. Zwłaszcza nie ja. Żegnaj.";
			link.l1 = "Poczekaj, pułkowniku.";
			link.l1.go = "DTSG_Kortni_PkCh_2";
		break;
		
		case "DTSG_Kortni_PkCh_2":
			dialog.text = "Cóż, zmieniłeś zdanie? Moje słowa w końcu zadziałały?";
			link.l1 = "Właśnie, wręcz przeciwnie.";
			link.l1.go = "DTSG_Kortni_PkCh_3";
		break;
		
		case "DTSG_Kortni_PkCh_3":
			dialog.text = "Co masz na myśli? Wyjaśnij się.";
			link.l1 = "Twoje słowa tylko wzmocniły moją determinację przeciwko tobie. Nie patrz tak - nie zabiję cię. A jak powiedziałem, nawet cię puszczę. Ale myślę, że poradzisz sobie bez łodzi.";
			link.l1.go = "DTSG_Kortni_PkCh_4";
		break;
		
		case "DTSG_Kortni_PkCh_4":
			dialog.text = "Nie potrzebuję tego, bo mam statek.";
			link.l1 = "Masz rację. Ale tylko w kwestii tego, że tego nie potrzebujemy. Możesz być wpływowym człowiekiem. Ale brak ci poczucia umiaru. I taktu. Zrobię to, do czego jesteś przyzwyczajony - będę panem sytuacji.";
			link.l1.go = "DTSG_Kortni_PkCh_5";
		break;
		
		case "DTSG_Kortni_PkCh_5":
			dialog.text = "Nie jesteś, Kapitanie de Maure. Nie oszukuj się.";
			link.l1 = "W pełni? Może nie. Ale ty też nie - twoje życie jest teraz w moich rękach, pułkowniku. Nieważne, co stanie się ze mną później - teraz mogę robić, co tylko chcę. A ja... biorę ten statek. Jesteś wolny. Brzeg nie jest daleko.";
			link.l1.go = "DTSG_Kortni_PkCh_6";
		break;
		
		case "DTSG_Kortni_PkCh_6":
			dialog.text = "Nie odważyłbyś się. Ale sądząc po twoim wyglądzie... Ciesz się swoim małym zwycięstwem. Udało ci się...";
			link.l1 = "Tak, tak, jedna z najgorszych decyzji w moim życiu. Już to słyszałem. Zejdź z tego statku. Mojego statku. Skoczysz sam, czy mamy cię wyrzucić za burtę?";
			link.l1.go = "DTSG_Kortni_PkCh_7";
		break;
		
		case "DTSG_Kortni_PkCh_7":
			DialogExit();
			
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto4", "", "", "", "DTSG_Kortni_Vyprygnul", 7);
			npchar.lifeday = 0;
			npchar.location = "None";
		break;
		
		case "DTSG_Kortni_PkCh_8":
			dialog.text = "Nie sądziłem, że go tak zobaczę - upokorzonego, wyskakującego przez okno i płynącego do brzegu na czworakach.";
			link.l1 = "Rzuciłeś okiem? Zadowolony? Wspaniale. Teraz twoja kolej.";
			link.l1.go = "DTSG_Kortni_PkCh_9";
		break;
		
		case "DTSG_Kortni_PkCh_9":
			dialog.text = "What are you saying, sir? We're not enemies; I was just following orders!.. Can I at least ask for a boat? You'll never see me again!";
			link.l1 = "Nie oszczędziłbyś mnie, gdybyś był na moim miejscu i właśnie przegrał ze mną bitwę. Więc ciesz się, że cię nie zabiłem. Przez okno. Teraz. Może dogonisz swojego patrona.";
			link.l1.go = "DTSG_Kortni_PkCh_10";
		break;
		
		case "DTSG_Kortni_PkCh_10":
			dialog.text = "Wolałbym umrzeć, niż stawić czoła takiemu upokorzeniu, monsieur!";
			link.l1 = "Jak sobie życzysz.";
			link.l1.go = "DTSG_Kortni_PkCh_11";
		break;
		
		case "DTSG_Kortni_PkCh_11":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			LAi_RemoveCheckMinHP(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_Kortni_Vyprygnul_3");
		break;
		
		case "DTSG_Kortni_PkCh_12":
			dialog.text = "To był pułkownik, prawda, kapitanie?";
			link.l1 = "Racja. Spójrz przez okno, Charlie, nie pożałujesz.";
			link.l1.go = "DTSG_Kortni_PkCh_13";
		break;
		
		case "DTSG_Kortni_PkCh_13":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto4", "DTSG_Kortni_Vyprygnul_5", 6);
		break;
		
		case "DTSG_Kortni_PkCh_14":
			dialog.text = "Pułkownik?.. Nigdy bym nie pomyślał, że zobaczę coś takiego, sir. Że ktoś odważyłby się wyrzucić człowieka z takim tytułem za burtę jak zwykłego marynarza! Richard nigdy by tego nie zrobił - szanowanie rangi było dla niego kluczowe.";
			link.l1 = " Wbito to w niego przez lata musztry. Jest człowiekiem wojskowym, z odpowiadającym temu sposobem myślenia. Ja nie, i myślę szerzej, bez takich... ograniczeń.";
			link.l1.go = "DTSG_Kortni_PkCh_15";
		break;
		
		case "DTSG_Kortni_PkCh_15":
			dialog.text = "I nie będziemy mieli kłopotów za to, co mu zrobimy?";
			link.l1 = "Heh, obwiniasz Richarda, ale myślisz jak on. Ośmieliliśmy się sprzeciwić, więc będziemy przez jakiś czas ścigani. Ale prędzej czy później nawet angielska marynarka wojenna da sobie z nami spokój. A dla Lyncha stanie się to sprawą osobistą. Ale zadbaliśmy o to, żeby następnym razem nie miał za sobą państwowych zasobów.";
			link.l1.go = "DTSG_Kortni_PkCh_16";
		break;
		
		case "DTSG_Kortni_PkCh_16":
			dialog.text = "Wiesz, Kapitanie, od tego dnia szanuję cię jeszcze bardziej. Nigdy nie będę żałować, że nie odpłynąłem z Dickiem na Valkyrie i zdecydowałem się dołączyć do ciebie.";
			link.l1 = "Dziękuję, mój przyjacielu! Bądź gotów - burza nadciąga na nas. Ale wiesz co? Coś mi mówi, że znów wyjdziemy zwycięsko. Chodźmy, czas wracać na pokład.";
			link.l1.go = "DTSG_Kortni_PkCh_17";
		break;
		
		case "DTSG_Kortni_PkCh_17":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			
			DoQuestCheckDelay("DTSG_Kortni_Vyprygnul_7", 3.0);
			Achievment_Set("ach_CL_114");
		break;
		
		case "DTSG_Kortni_LT_1":
			dialog.text = "To nie do końca prawda, chociaż osobiście nie obchodzi mnie Charlie, jeśli od teraz trzyma język za zębami. Ale moi koledzy chcieliby zobaczyć jego ciało. I wiedzą, jak wygląda\nTo jest prawdziwe życie, Charles, nie dziecinna bajka czy rycerski poemat czytany nam przez nianie w dzieciństwie, i nie widzę rozwiązania, które zadowala wszystkich.";
			link.l1 = "Ale ja tak myślę. Zawsze możesz znaleźć podobne ciało. I kupić podobne ubrania. Nasmarować kilka trybików. A ja porozmawiam z Charliem. I daję ci moje słowo jako gwarancję.";
			link.l1.go = "DTSG_Kortni_LT_2";
		break;
		
		case "DTSG_Kortni_LT_2":
			if (sti(pchar.reputation.nobility) > 70)
			{
				notification("Reputation Check Passed", "None");
				dialog.text = "To... duże ryzyko. I tu nie chodzi tylko o to, czy mogę ufać twemu słowu. Ale czy moi koledzy mi uwierzą, gdy zobaczą ciało przypominające Charliego. I nie podejmę tego ryzyka... tak po prostu.";
				link.l1 = "Ile?";
				link.l1.go = "DTSG_Kortni_LT_4";
			}
			else
			{
				notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(71))+")", "None");
				dialog.text = "Słowo człowieka z twoją reputacją? Żartujesz sobie. Szlachetne pochodzenie to za mało, by zaufać.";
				link.l1 = "Słysząc to od innego człowieka o podobnym pochodzeniu i czynach, wybacz mi, pułkowniku.";
				link.l1.go = "DTSG_Kortni_LT_3";
			}
		break;
		
		case "DTSG_Kortni_LT_3":
			dialog.text = "Oczywiście, masz rację. Ale w tym przypadku chodzi o moje zaufanie, a nie kogoś innego. A ty jako gwarant mi nie odpowiadasz\nMówię ci ostatni raz. Oddaj mi Charlie. Jeśli, oczywiście, nie chcesz podzielić losu Fleetwooda.";
			link.l1 = "Możesz łatwo wykorzystać swój tytuł i wpływy, by zastraszyć jakiegoś głupca. Ale ja nie jestem głupcem. I wyczuwam desperację z daleka. Wynoś się. I ciesz się, że cię nie zabiłem - zasługujesz na to w pełni.";
			link.l1.go = "DTSG_Kortni_PkCh_1";
		break;
		
		case "DTSG_Kortni_LT_4":
			dialog.text = "W końcu, prosto do rzeczy. Milion pesos. Ostateczna oferta.";
			if (sti(pchar.Money) >= 1000000)
			{
				link.l1 = "Zapłacę ci pieniądze. Nie myśl, że jestem biedny lub nie cenię życia moich ludzi. Żadne z tych nie jest prawdą. Weź to.";
				link.l1.go = "DTSG_Kortni_LT_7";
			}
			else
			{
				link.l1 = " Masz niezły apetyt, choć niczego innego się nie spodziewałem. Ale teraz nie mam aż tyle, i...";
				link.l1.go = "DTSG_Kortni_LT_5";
			}
		break;
		
		case "DTSG_Kortni_LT_5":
			dialog.text = "Bez srebra - nie ma umowy. Myślałeś, że okażę litość? Czy wyglądam na świętego, panie?";
			link.l1 = "Ale może mógłbyś trochę poczekać? Gdzie i kiedy byłoby ci wygodnie spotkać się ponownie? Mógłbym pożyczyć dublony od lichwiarza.";
			link.l1.go = "DTSG_Kortni_LT_6";
		break;
		
		case "DTSG_Kortni_LT_6":
			dialog.text = "W takim razie myślisz, że jestem jeszcze bardziej naiwna, niż sądziłam.\nNie jestem wiejską dziewczyną gotową czekać wiecznie na kogoś, kto raz miał z nią swoją drogę.\nBez pieniędzy? I tak o nie nie prosiłam. Chcę tylko Charlie'ego. Nie jesteś mi do niczego potrzebny mimo całego kłopotu, który sprawiłeś.";
			link.l1 = "Możesz łatwo użyć swego tytułu i wpływów, by zastraszyć głupca czy dwóch. Ale ja nie jestem głupcem. I wyczuwam desperację na milę. Wynoś się. I ciesz się, że cię nie zabiłem - zasługujesz na to z nawiązką.";
			link.l1.go = "DTSG_Kortni_PkCh_1";
		break;
		
		case "DTSG_Kortni_LT_7":
			dialog.text = "Czy naprawdę jesteś tak przywiązany do biednego Charliego? W każdym razie, twoja szlachetność zasługuje na szacunek. Upewnij się, że twój artylerzysta jest cichy jak grób. W przeciwnym razie obaj tam skończycie.";
			link.l1 = "Obiecuję. A ty dotrzymujesz słowa i zaprzestajesz wszelkiego pościgu.";
			link.l1.go = "DTSG_Kortni_LT_8";
			AddMoneyToCharacter(pchar, -1000000);
		break;
		
		case "DTSG_Kortni_LT_8":
			dialog.text = "Też obiecuję. I jeszcze jedno. Pomimo twojego uczciwego zwycięstwa, zabiorę ze sobą mój statek. To specjalnie wykonany egzemplarz, wiesz. I bardzo drogi.";
			link.l1 = "A co z prawem zwycięzcy? Ale nie będę kusił losu. Tym razem.";
			link.l1.go = "DTSG_Kortni_LT_9";
		break;
		
		case "DTSG_Kortni_LT_9":
			DialogExit();
			
			LAi_Fade("DTSG_Kortni_Otkup_1", "");
		break;
		
		case "DTSG_Kortni_LT_10":
			dialog.text = "Przykro mi to mówić, Brian, ale obawiam się, że nasza współpraca kończy się tutaj.";
			link.l1 = "";
			link.l1.go = "DTSG_Kortni_LT_11";
			CharacterTurnToLoc(npchar, "rld", "aloc0");
		break;
		case "DTSG_Kortni_LT_11":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("DTSG_Mrt_Rocur");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_12";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_12":
			dialog.text = "Jestem... wolny, pułkowniku? Zdejmiesz nagrodę z mojej głowy, i mogę zacząć od nowa, jakbym był praworządnym człowiekiem?";
			link.l1 = "";
			link.l1.go = "DTSG_Kortni_LT_13";
			CharacterTurnToLoc(npchar, "rld", "loc0");
		break;
		case "DTSG_Kortni_LT_13":
			DialogExit();
			sld = CharacterFromID("DTSG_KortniClone");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_14";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_14":
			dialog.text = "Rzekłbym, że widziałeś zbyt wiele - zupełnie jak nieboszczyk Fleetwood. Właśnie teraz przyjąłem łapówkę wprost przed tobą.";
			link.l1 = "";
			link.l1.go = "DTSG_Kortni_LT_15";
			CharacterTurnToLoc(npchar, "rld", "aloc0");
		break;
		case "DTSG_Kortni_LT_15":
			DialogExit();
			sld = CharacterFromID("DTSG_Mrt_Rocur");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_16":
			dialog.text = "J... Ja nikomu nic nie powiem, przysięgam na Boga!";
			link.l1 = "";
			link.l1.go = "DTSG_Kortni_LT_17";
			CharacterTurnToLoc(npchar, "rld", "loc0");
		break;
		case "DTSG_Kortni_LT_17":
			DialogExit();
			sld = CharacterFromID("DTSG_KortniClone");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_18";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_18":
			dialog.text = "Oczywiście, że nie.";
			link.l1 = "";
			link.l1.go = "DTSG_Kortni_LT_19";
			CharacterTurnToLoc(npchar, "rld", "aloc0");
		break;
		case "DTSG_Kortni_LT_19":
			DialogExit();
			sld = CharacterFromID("DTSG_Mrt_Rocur");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_20";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_20":
			dialog.text = "Nie!..";
			link.l1 = "";
			link.l1.go = "DTSG_Kortni_LT_21";
			CharacterTurnToLoc(npchar, "rld", "loc0");
		break;
		case "DTSG_Kortni_LT_21":
			DialogExit();
			
			sld = CharacterFromID("DTSG_KortniClone");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "1", 1.8);
			DoQuestCheckDelay("DTSG_Kortni_Otkup_3", 0.9);
			
			LAi_SetActorType(NPChar);
			LAi_ActorAttack(NPChar, sld, "");
		break;
		
		case "DTSG_Kortni_LT_22":
			dialog.text = "Nie patrz na mnie tak, Charles. Jeśli będę się ciągle martwić, czy Brian się wygada, to w ogóle nie będę mógł spać.";
			link.l1 = "Nie wiem nawet, czy powinienem być zaskoczony tym, co zobaczyłem, czy nie.";
			link.l1.go = "DTSG_Kortni_LT_23";
		break;
		
		case "DTSG_Kortni_LT_23":
			dialog.text = "Nie powinieneś. Jestem zobowiązany. Wszystko, czego od was wymagam, to żebyście trzymali buzie na kłódkę o tym, co się stało. Spróbuję znaleźć podobne ciało, odpowiednio naprawić twarz, dobrze wykorzystać pieniądze i przekonać moich kolegów.";
			link.l1 = "Dziękuję, pułkowniku.";
			link.l1.go = "DTSG_Kortni_LT_24";
		break;
		
		case "DTSG_Kortni_LT_24":
			dialog.text = "Nie ma jeszcze za co dziękować. Zawsze istnieje ryzyko, że mi nie uwierzą, a wtedy polowanie zacznie się na nowo. Na razie, żegnaj, kapitanie de Maure. Odpływam na moim statku. Żadnych sprzeciwów tutaj - już wyświadczyłem tobie i Charliemu wielką przysługę.";
			link.l1 = "Cóż, żegnaj zatem.";
			link.l1.go = "DTSG_Kortni_LT_25";
			
			pchar.GenQuest.CannotTakeShip = true;
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition.l1 = "MapEnter";
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition = "DTSG_Kortni_KechNeNash";
		break;
		
		case "DTSG_Kortni_LT_25":
			DialogExit();
			
			//sld = CharacterFromID("Knippel");
			sld = GetCharacter(CreateCharacterClone(CharacterFromID("Knippel"), 0));
			sld.id = "KnippelClone";
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_26";
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
			LAi_SetActorType(pchar);
			LAi_SetActorType(sld);
			SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
			LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 2.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 2.0);
		break;
		
		case "DTSG_Kortni_LT_26":
			dialog.text = "Czy wiesz, z kim rozmawiałeś, Kapitanie? Pułkownikiem! Czy to on zorganizował całe to zamieszanie?";
			link.l1 = "Wiem, przedstawił się. I masz rację - był.";
			link.l1.go = "DTSG_Kortni_LT_27";
		break;
		
		case "DTSG_Kortni_LT_27":
			dialog.text = "To dziwne, sir, ponieważ kiedyś znałem go jako przełożonego Richarda. Jak to możliwe? I dlaczego odchodzi, jakby nic się nie stało? Czego on w ogóle chciał?";
			link.l1 = "Tak naprawdę, nie ma w tym nic dziwnego. Ci, którzy wykonują podejrzane rozkazy, często ryzykują życiem nie tyle przez wrogów, ile przez swoich przełożonych. A on chciał twojej głowy, Charlie.";
			link.l1.go = "DTSG_Kortni_LT_28";
		break;
		
		case "DTSG_Kortni_LT_28":
			dialog.text = "Nie rozumiem, Kapitanie. Dlaczego więc odchodzi? Czy przyjął porażkę?";
			link.l1 = "To do niego wcale niepodobne. Musiałem dać mu złoto ważące mniej więcej tyle, co twoja głowa. Może trochę więcej. Dokładnie milion pesos.";
			link.l1.go = "DTSG_Kortni_LT_29";
		break;
		
		case "DTSG_Kortni_LT_29":
			dialog.text = "I ty... zapłaciłeś mu tę ogromną sumę? Za mnie?..";
			link.l1 = "Cóż, nie tylko dla ciebie. Dla siebie również. I dla wszystkich chłopaków, też. Ale tak, Charlie, przede wszystkim dla ciebie. Gdybyśmy go zabili, czekałyby nas karne ekspedycje na wieczność.";
			link.l1.go = "DTSG_Kortni_LT_30";
		break;
		
		case "DTSG_Kortni_LT_30":
			dialog.text = "Nie... mogę w to uwierzyć, panie. Po prostu... dziękuję. Nie sądziłem, że Fleetwood zrobiłby to na twoim miejscu.";
			link.l1 = "Jesteś zbyt uprzedzony wobec niego po jego ucieczce. Richard po prostu chciał cichego i spokojnego życia z Abigail. Przykro mi, że mu się nie udało. Poza tym dotrzymał słowa i spłacił twój dług. Heh, ja, Fleetwood - masz szczęście do kapitanów, co, Charlie?";
			link.l1.go = "DTSG_Kortni_LT_31";
		break;
		
		case "DTSG_Kortni_LT_31":
			dialog.text = "Bez żartów, Kapitanie. Więc, czy wszystko już skończone?";
			link.l1 = "Tak, mój bardzo kosztowny przyjacielu. Przynajmniej na razie. Walka się skończyła - możesz powiedzieć chłopakom, żeby schowali broń. I niech się przygotują do stawiania żagli.";
			link.l1.go = "DTSG_Kortni_LT_32";
		break;
		
		case "DTSG_Kortni_LT_32":
			DialogExit();
			
			InterfaceStates.Buttons.Save.enable = true;
			LAi_SetPlayerType(pchar);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			
			AddQuestRecord("DTSG", "19");
			CloseQuestHeader("DTSG");
			LAi_ReloadBoarding();
			Achievment_Set("ach_CL_114");
			sld = CharacterFromID("Knippel");
			SetCharacterPerk(sld, "Bombardier");
			notification("Bombardier Unlocked", "Knippel");
		break;
		
		case "DTSG_Kortni_Sdat":
			dialog.text = "Nie obchodzi mnie, dlaczego się zgadzasz – czy z chciwości, strachu, czy z obowiązku wobec swoich ludzi. Najważniejsze, że się zgadzasz. Wyślę mojego człowieka do Port Royal z instrukcjami dla bankiera.";
			link.l1 = "Dobrze. Nie mogę uwierzyć, że to w końcu koniec.";
			link.l1.go = "DTSG_Kortni_Dengi_1";
			link.l2 = "Wiesz co, do diabła z pieniędzmi. Zawsze można znaleźć więcej. Chcę czegoś innego od ciebie w zamian za Charlie'ego, pułkowniku.";
			link.l2.go = "DTSG_Kortni_Kech_1";
		break;
		
		case "DTSG_Kortni_Kech_1":
			dialog.text = "O? Muszę przyznać, zaskoczyłeś mnie, kapitanie de Maure. A co, według ciebie, byłoby równoważne z łysą głową starego kanoniera, jeśli góra złota ci nie odpowiada?";
			link.l1 = "Sam to powiedziałeś - wspaniały okręt, z poprawionymi błędami projektowymi. Nie mogę się doczekać, by samemu ją wypróbować. Wciąż masz plany. Ale tylko jeden Charlie. Poza tym, leży w twoim interesie, bym był zadowolony.";
			link.l1.go = "DTSG_Kortni_Kech_2";
		break;
		
		case "DTSG_Kortni_Kech_2":
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) > 70)
			{
				dialog.text = "Jesteś twardym negocjatorem. Czy masz pojęcie, ile kosztowało nas zbudowanie choćby jednego z nich?";
				link.l1 = "(Godny zaufania) (Honor) Doskonale o tym wiem, dlatego pytam. Twoja ręka jest w mojej paszczy aż po łokieć. Możesz próbować zastrzelić tego wilka. Ale stracisz rękę. I nie tylko ją.";
			}
			else
			{
				dialog.text = "Obawiam się, że zbudowanie jednej z nich kosztuje znacznie więcej niż złoto, które dla ciebie przygotowaliśmy. Ale mnie rozbawiłeś, Charles. W dobry sposób.";
				link.l1 = "Było warto spróbować.";
				if (!IsCharacterPerkOn(pchar, "Trustworthy")) notification("Perk Check Failed", "Trustworthy");
				if (sti(pchar.reputation.nobility) < 71) notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(71))+")", "None");
			}
			link.l1.go = "DTSG_Kortni_Kech_3";
		break;
		
		case "DTSG_Kortni_Kech_3":
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) > 70)
			{
				dialog.text = "Widzę, że wiesz, czego chcesz, i dążysz do swoich celów w życiu\nDobrze, dobrze. Kecz jest twój. Ale zapomnij o pieniądzach - lichwiarz powie, że nic nie wie.";
				link.l1 = "To mi pasuje.";
				link.l1.go = "DTSG_Kortni_Kech_4";
				pchar.questTemp.DTSG_Kech = true;
			}
			else
			{
				dialog.text = "Zdecydowanie. Moje życie to historia chwytania okazji i zabezpieczania się przed ryzykiem\nWięc przyprowadź tutaj Charlie'ego, a rozstaniemy się w pokoju. Po tym, możesz nawet wziąć zaliczkę. Ale ja odpływam na tym statku.";
				link.l1 = "Więc załatwmy to.";
				link.l1.go = "DTSG_Kortni_VizyvaemKnippel";
				pchar.questTemp.DTSG_depozit = true;
			}
		break;
		
		case "DTSG_Kortni_Kech_4":
			dialog.text = "Nie mogę powiedzieć, że jestem całkowicie zadowolony. Ale chcę to szybko zakończyć. Teraz daj mi to, czego chcę.";
			link.l1 = "Nie 'co', ale 'kto'. Ale jak sobie życzysz.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel";
		break;
		
		case "DTSG_Kortni_Dengi_1":
			dialog.text = "Ja także nie mogę. Zaczynam wierzyć, że nie chodzi tylko o to, kim człowiek jest, ale kto go otacza - prosta robota złapania starego kanoniera zmieniła się w ból głowy przez jego kapitana, czyli ciebie, Charles\nZawołaj tu Charliego. Ten bałagan skończy się na dobre - podniesiemy kotwice, a nasze statki się rozejdą.";
			link.l1 = "Rozstać się, mówisz?";
			link.l1.go = "DTSG_Kortni_Dengi_2";
		break;
		
		case "DTSG_Kortni_Dengi_2":
			dialog.text = "Wyglądasz na zaskoczonego? Myślałeś, że kecz to twoja prawowita zdobycz? Nie jesteśmy piratami, kapitanie de Maure. Cywilizowani ludzie żyją według innych, znacznie bardziej skomplikowanych zasad. Statek zostaje ze mną.";
			link.l1 = "No to wtedy...";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel";
			pchar.questTemp.DTSG_depozit = true;
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel":
			DialogExit();
			
			//sld = CharacterFromID("Knippel");
			sld = GetCharacter(CreateCharacterClone(CharacterFromID("Knippel"), 0));
			sld.id = "KnippelClone";
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_VizyvaemKnippel_2";
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_2":
			dialog.text = "Czy wszystko w porządku, sir? Czy to... pułkownik?";
			link.l1 = "Tak, Charlie, to pułkownik. Przyszedłeś w samą porę - właśnie miałem iść po ciebie osobiście.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_3";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_3":
			dialog.text = "Zabrać mnie, kapitanie?.. Teraz? Czemu rozmawiałeś z tym... człowiekiem tak długo? Myślałem, że masz kłopoty, więc przyszedłem tu osobiście.";
			link.l1 = "Zgadza się. Nadal mamy kłopoty mimo zwycięstwa. I nadal byśmy mieli, gdyby pułkownik i ja nie znaleźli rozwiązania.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_4";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_4":
			dialog.text = "Czy udało się panu przekonać go, by dał nam spokój, sir?";
			link.l1 = "Niestety, tylko ja. Nie my. Ty... pójdziesz z nim, Charlie.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_5";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_5":
			dialog.text = "Co?.. Ale dlaczego?.. Wygraliśmy!";
			link.l1 = "Nie rozumiesz? Nie możemy wciąż wygrywać bez końca - nie przestaną, dopóki nie zdobędą twojej głowy.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_6";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_6":
			dialog.text = "Nie mogę uwierzyć, że to robisz staremu Charliemu, Kapitanie. Jesteś taki sam jak Dick. Oboje kiedyś mówiliście mi, że jesteście moimi przyjaciółmi. I obaj porzuciliście mnie i wszystkich bliskich.";
			link.l1 = "To brzemię kapitana, jego odpowiedzialność. Widzę, że nie możesz tego pojąć, bo wszystko, co musiałeś robić, to ładować armaty kulami armatnimi.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_7";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_7":
			dialog.text = "Nie rozumiesz?.. Może po prostu nie jestem zdrajcą jak ty? Wiesz, dokąd powinieneś iść?";
			link.l1 = "Do diabła? Może masz rację. Wszyscy na to zasługujemy.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_8";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_8":
			dialog.text = "Do diabła z tobą, panie.";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_9";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_9":
			DialogExit();
			
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_VizyvaemKnippel_10";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			
			sld = CharacterFromID("KnippelClone");
			LAi_SetActorType(sld);
			sld = CharacterFromID("Knippel");
			RemovePassenger(pchar, sld);
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_10":
			dialog.text = "Przezabawne. Prawie się roześmiałem. Słyszałeś to, Brian?\nCzasami słuchanie prostych wieśniaków jest jak powiew wiatru i wcale nie irytuje. Podjąłeś właściwą decyzję, Charles. Rozumiem, jak trudno ci było. Ale pociesz się wiedząc, że teraz ani ty, ani nikt inny z twoich ludzi nie będzie cierpiał.";
			link.l1 = "Mam nadzieję, że dotrzymasz tej obietnicy, pułkowniku.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_11";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_11":
			dialog.text = "Jestem człowiekiem słowa. Los Abigail jest tego dowodem. Spójrz na Briana. Francuski pirat, ale podjął właściwą decyzję, gdy nadszedł czas, by dołączyć do właściwej strony. I nikt go nie tknie, dopóki wiernie nam służy. Jak on, idziesz w dobrym kierunku, Kapitanie de Maure.";
			if (CheckAttribute(pchar, "questTemp.DTSG_Kech"))
			{
				link.l1 = "Mówiąc o wyruszeniu. Chcę stąd wyjechać jak najszybciej. Na tym niewątpliwie szybkim statku, który mi obiecałeś, pułkowniku.";
			}
			else
			{
				link.l1 = "Nie jestem piratem. I nie planuję jeszcze dołączyć do angielskiej floty. Ale zamierzam odebrać obiecaną nagrodę.";
			}
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_12";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_12":
			if (CheckAttribute(pchar, "questTemp.DTSG_Kech"))
			{
				dialog.text = "I won't hide it - it feels like tearing her from my heart. I'll have to spend on a new one, but perhaps it's worth it - too long have I been troubled by the thought that Charlie might spill the beans\nIf you don't talk or commit serious crimes against England, consider that we're no longer enemies. Enjoy the new ship; she's indeed beautiful. Goodbye, Charles. Brian - prepare a boat for us. Charlie - follow me as you have no say in the matter.";
				link.l1 = "Żegnajcie. Wszyscy.";
				link.l1.go = "DTSG_Kortni_VizyvaemKnippel_13";
			}
			else
			{
				dialog.text = "Szkoda, zawsze potrzebujemy zdolnych ludzi, niezależnie od ich narodowości. Ale oczywiście zasługujesz na nagrodę. Możesz bezpiecznie udać się do Port Royal - dotrę tam przed jakimkolwiek innym statkiem na tym keczu.";
				link.l1 = "Mam taką nadzieję. I mam nadzieję, że w Port Royal nie będzie czekać na mnie uzbrojona eskorta.";
				link.l1.go = "DTSG_Kortni_VizyvaemKnippel_14";
			}
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_13":
			DialogExit();
			
			AddQuestRecord("DTSG", "20");
			CloseQuestHeader("DTSG");
			ChangeOfficersLoyality("bad_all", 5);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "fame", -10);
			AddCrewMorale(Pchar, -10);
			LAi_ReloadBoarding();
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_14":
			dialog.text = "Znów wątpisz w moje słowo? Wstydź się. Zyskałeś wdzięczność całej angielskiej floty. Jeśli kiedykolwiek będziesz czegoś potrzebował, lub zdecydujesz się do nas dołączyć, skontaktuj się ze mną, kapitanie de Maure.";
			link.l1 = "Kiedyś próbowałem zdobyć wsparcie i kontakty z angielskim wywiadem. Nie wyszło. Żegnaj więc, pułkowniku.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_15";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_15":
			DialogExit();
			
			if (CheckAttribute(pchar, "questTemp.DTSG_depozit"))
			{
				ChangeCharacterNationReputation(pchar, ENGLAND, 30);
			}
			pchar.GenQuest.CannotTakeShip = true;
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition.l1 = "MapEnter";
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition = "DTSG_Kortni_KechNeNash";
			AddQuestRecord("DTSG", "21");
			CloseQuestHeader("DTSG");
			ChangeOfficersLoyality("bad_all", 5);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "fame", -10);
			AddCrewMorale(Pchar, -10);
			LAi_ReloadBoarding();
			Achievment_Set("ach_CL_114");
		break;
		
	}
} 

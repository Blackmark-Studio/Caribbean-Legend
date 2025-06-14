void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i, n;
	string sTemp, sStr, sStr2, sGun, sBullet, attrL;
	
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
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Czego ci potrzeba?";
			link.l1 = "Niczego.";
			link.l1.go = "exit";
		break;
		
		case "BM_Contra_1":
			dialog.text = "Kim jesteś i co ty tu, do cholery robisz?! Nie kręć się tutaj!";
			if (sti(pchar.reputation.nobility) >= 40)
			{
				link.l1 = "Spokojnie, kumplu. Tylko przechodzę obok. Nie zamierzam wtrącać się w wasze... cokolwiek to jest.";
			}
			else
			{
				link.l1 = "Hm? A co? To twoja latarnia? Następnym razem, umieść znak z twoim imieniem na jednej z palm albo zbuduj cholerną palisade.";
			}
			link.l1.go = "BM_Contra_2";
			DelLandQuestMark(npchar);
		break;
		
		case "BM_Contra_2":
			if (sti(pchar.reputation.nobility) >= 40)
			{
				dialog.text = " Wynoś się stąd! Jeśli zepsujesz umowę, odstraszając klienta, to ja...";
			}
			else
			{
				dialog.text = "Słuchaj, dzieciaku, nie zmuszaj mnie i moich chłopaków, byśmy sprawdzili, czy twój miecz jest tak ostry jak twój język. Po prostu zniknij i...";
			}
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_BarbadosPatrolPribegaet");
		break;
		
		case "BM_Contra_3":
			dialog.text = "No cóż, Frankie, który to?";
			link.l1 = "...";
			link.l1.go = "BM_Contra_3_1";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay12", "1", 1.9);
		break;
		case "BM_Contra_3_1":
			StartInstantDialog("BM_PatrolZhitel", "BM_Contra_4", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_4":
			dialog.text = "Nie... Do diabła. Nie rozpoznaję żadnej z tych gęb.";
			link.l1 = "...";
			link.l1.go = "BM_Contra_4_1";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay15", "1", 1.9);
		break;
		case "BM_Contra_4_1":
			StartInstantDialog("BM_PatrolOff", "BM_Contra_5", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_5":
			dialog.text = "Co?! Jesteś pewny?";
			link.l1 = "... ";
			link.l1.go = "BM_Contra_5_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolZhitel"));
		break;
		case "BM_Contra_5_1":
			StartInstantDialog("BM_PatrolZhitel", "BM_Contra_6", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_6":
			dialog.text = "Czy myślisz, że jestem ślepy?! Mówię ci, co...";
			link.l1 = "...";
			link.l1.go = "exit";
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
			CharacterTurnByChr(CharacterFromID("BM_PatrolOff"), CharacterFromID("BM_PatrolZhitel"));
			AddDialogExitQuest("BM_BarbadosMayakVystrel");
		break;
		
		case "BM_Contra_7":
			dialog.text = "Co, do diabła?!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_7_1";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay9", "1", 1.9);
			CharacterTurnByChr(npchar, CharacterFromID("BM_Contra_1"));
		break;
		
		case "BM_Contra_7_1":
			StartInstantDialog("BM_Contra_1", "BM_Contra_8", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_8":
			dialog.text = "Kto strzelał?!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_8_1";
			locCameraFromToPos(-84.11, 6.33, -62.68, true, -78.07, 3.20, -66.67);
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay13", "1", 1.9);
		break;
		
		case "BM_Contra_8_1":
			StartInstantDialog("BM_PatrolOff", "BM_Contra_9", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_9":
			dialog.text = "Macie nas za głupców, łajdaki? Rzućcie broń na ziemię, wszyscy! I ty też!";
			link.l1 = "Co?!";
			link.l1.go = "BM_Contra_9_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_Contra_1"));
		break;
		
		case "BM_Contra_9_1":
			StartInstantDialog("BM_Contra_1", "BM_Contra_10", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_10":
			dialog.text = "Tylko trzymaj nerwy na wodzy, oficerze. To nie my, nie widzisz? Nasze pistolety są tam, gdzie były. I nie dotykaj swoich!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_10_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
		break;
		case "BM_Contra_10_1":
			StartInstantDialog("BM_PatrolOff", "BM_Contra_11", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_11":
			dialog.text = "Rozkazujesz mi, łajdaku?! Aresztować ich wszystkich, natychmiast!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_11_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_Contra_1"));
		break;
		
		case "BM_Contra_11_1":
			StartInstantDialog("BM_Contra_1", "BM_Contra_12", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_12":
			dialog.text = "Pierdolenie! Nie ma takiej opcji. Chłopaki, do broni!";
			link.l1 = "Widze, że kłopoty lubią za mną chodzić...";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_BarbadosMayakBoinya");
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
		break;
		
		case "BM_Irons_1":
			dialog.text = "Hej, hej, uważaj! Ktoś może zginąć, jeśli będziesz tak dziko machać tym żelazem.";
			link.l1 = "Hah! Niby kto?";
			link.l1.go = "BM_Irons_2";
			LAi_SetCurHPMax(npchar);
			SetOfficerToMushketer(npchar, "mushket1", true);
		break;
		
		case "BM_Irons_2":
			dialog.text = "Ja, oczywiście.";
			link.l1 = "Phi! Odezwał się. Kim ty do diabła wogóle jesteś?";
			link.l1.go = "BM_Irons_4";
			link.l2 = "Zdajesz sobie sprawe, że właśnie to próbuję zrobić. Czyż nie?";
			link.l2.go = "BM_Irons_3";
		break;
		
		case "BM_Irons_3":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			npchar.MusketerDistance = 10;
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "BM_Irons_4":
			if (startHeroType == 4)
			{
				dialog.text = "Jestem Tommy! Tommy Irons. Tak mi się przynajmniej wydaje. Kim ty jesteś? Jesteś odważną kobietą, powiem ci, chodząc tak ubrana, hehehe.";
				link.l1 = "Odważną, jak najbardziej. I nie boję się zamknąć ci gęby, jeśli będę musiała. To gorące miejsce, więc ubieram się lekko - nie po to, by zadowolić ciebie lub innych. Nazywam się Helen MacArthur. Moi przyjaciele mogą nazywać mnie Rumba, ale ty z pewnością nie jesteś jednym z nich. A co to było za 'chyba'?";
				link.l1.go = "BM_Irons_5";
			}
			else
			{
				dialog.text = "Jestem Tommy! Tommy Irons. Chyba. A ty?";
				link.l1 = ""+GetFullName(pchar)+". A co dokładnie oznacza to 'Chyba'?";
				link.l1.go = "BM_Irons_5";
			}
			LAi_SetCurHPMax(pchar);
		break;
		
		case "BM_Irons_5":
			dialog.text = "To znaczy dokładnie to, co znaczy. Straciłem pamięć - zostałem nieźle pobity w bitwie. Wiesz, czasami tracisz wszystko. Mam jednak szczęście. Zapomniałem tylko swoje imię. Szczęśliwie dla mnie, mam ten wisiorek na szyi, który mówi 'Thomas'. Ale wolę Tommy. I Irons. Walczyłem w Ironsides dla Cromwella, pamiętaj to. Ale 'Ironsides' jest zbyt nieporęczne. Irons jest znacznie lepsze.";
			link.l1 = "Widzę, co z tobą nie tak, Tommy. Więc, powiedz mi - co to było? Celowałeś w kogoś konkretnego? Trafiłeś w cel? Czy może po prostu strzelałeś dla zabawy? Nie byłbym zaskoczony.";
			link.l1.go = "BM_Irons_6";
		break;
		
		case "BM_Irons_6":
			dialog.text = "Trafiłem go, i to w sam środeczek! Mówie o tym eleganciku rzecz jasna. Śledził mój trop i przyprowadził ze sobą żołnierzy. Cały oddział, tylko dlatego, że spałem z jego żoną.";
			link.l1 = "Rzeczywiście, trafiłeś, heh. Mam rozumieć, że przyłapał was dwoje na gorącym uczynku?";
			link.l1.go = "BM_Irons_7";
		break;
		
		case "BM_Irons_7":
			dialog.text = "Ha! Nie uwierzyłbyś - nie. Dziewka później się przyznała. Wyrzuty sumienia, a może nie podobało jej się to tak bardzo jak mnie, hehe. Kto wie, co się dzieje w głowach kobiet? Nie obchodzi mnie to naprawdę, ha-ha-ha!";
			link.l1 = ""+GetSexPhrase("Hmm, dziwna kobieta.","Mężczyźni... W jednej chwili próbujecie zrozumieć, co mamy w głowach, a następnie mówicie, że was to nie obchodzi. Ale masz rację co do jednego - to, co zrobiła, było dziwne. Powinna była po prostu odejść i zapomnieć jak o złym śnie. Dokładnie to bym zrobiła, gdyby do tego doszło.")+"";
			link.l1.go = "BM_Irons_8";
		break;
		
		case "BM_Irons_8":
			dialog.text = "Dokładnie! Ludzie mówią, że to ze mną jest coś nie tak. Żal mi żołnierzy, którzy zginęli. Wiem, jak to jest, sam byłem kiedyś zwykłym żołnierzem. Czyż nie mówiłem ci?";
			link.l1 = "Tak, mówiłeś. Z Ironsides. Cromwell.";
			link.l1.go = "BM_Irons_9";
		break;
		
		case "BM_Irons_9":
			dialog.text = "Ach tak? Nie pamiętam, czy to zrobiłem, czy nie. Wiesz, jak trafiłem do Nowego Świata? Czy mam ci opowiedzieć?";
			link.l1 = "Nie, i nie interesowałoby mnie to, Tommy.";
			link.l1.go = "BM_Irons_10";
		break;
		
		case "BM_Irons_10":
			dialog.text = "Oj będzie. Powiem ci.";
			link.l1 = "Przecież ci...aaa do diabła z tym... wal-yyy to znaczy, śmiało.";
			link.l1.go = "BM_Irons_11";
		break;
		
		case "BM_Irons_11":
			dialog.text = "Nie przerywaj mi, zatem! Gdzie to ja byłem? Aha, więc byłem ranny, rozumiesz? Dostałem swoją oficjalną dymisję, bo byłem po zwycięskiej stronie. Ale powinieneś zobaczyć miny tych szczurów biurowych! Myśleli, że udaję, że straciłem pamięć. Ciągle pytali o moją rodzinę.";
			link.l1 = "I? Co im powiedziałeś?";
			link.l1.go = "BM_Irons_12";
		break;
		
		case "BM_Irons_12":
			dialog.text = "Cóż im powiedziałem? Powiedziałem, że nie pamiętam. I nie kłamałem - nigdy nie znałem swoich rodziców. Wychowała mnie ulica, robotnicy i służba w slumsach. Dołączyłem do Rewolucji dla nich. Choć niewdzięczność ludzi jest zdumiewająca - gdybym stracił ramię lub nogę, byliby zmuszeni dać takiemu bohaterowi jak ja natychmiastową emeryturę. A tak przy okazji, prawie straciłem głowę, dosłownie!";
			link.l1 = "Cóż, jak dotarłeś do Nowego Świata, bohaterze wojenny?";
			link.l1.go = "BM_Irons_13";
		break;
		
		case "BM_Irons_13":
			dialog.text = "Czy w to wątpisz? Walka za wspólne dobro - co w tym nieheroicznego? Mam nadzieję, że pewnego dnia tchórze tacy jak ty poznają, czym jest prawdziwa wolność!";
			link.l1 = "Chociaż wolność to dobra rzecz, jakoś sprawiłeś, że brzmi to jak groźba. Dobrze, Tommy, mów dalej.";
			link.l1.go = "BM_Irons_14";
		break;
		
		case "BM_Irons_14":
			dialog.text = "Aye. Dostałem swoją rezygnację po wygranej Rewolucji, a potem zdałem sobie sprawę, że nie umiem robić nic poza strzelaniem i łamaniem ludziom kości. A do armii nie da się wrócić - wyśmialiby mnie, zwłaszcza po tym, jak tak zaciekle walczyłem o rezygnację. Heh, wydaje mi się, że nawet gdybym naprawdę stracił ramię lub nogę, biurokratyczne szczury nadal myślałyby, że gdzieś je ukrywam, by później przyszyć z powrotem, gdy tylko dostanę papiery wyjściowe, ha-ha-ha!";
			link.l1 = "To zabawne. Ale wciąż nie powiedziałeś mi, jak tu trafiłeś.";
			link.l1.go = "BM_Irons_15";
		break;
		
		case "BM_Irons_15":
			dialog.text = "Och, jaki nudziarz z ciebie. Czy nie nauczyli cię cierpliwości, "+GetSexPhrase("młodzieńcu","dziewczyno")+"? Nie miałem nic do roboty w domu oprócz strzelania do kaczek i jeleni, więc karnąłem się do Nowego Świata. Pływałem z piratami przez jakiś czas dla zabawy, a kiedy zmęczyłem się bezprawiem, zostałem najemnikiem.";
			link.l1 = "Nie bardzo oryginalna historia.";
			link.l1.go = "BM_Irons_16";
		break;
		
		case "BM_Irons_16":
			dialog.text = "Może masz lepszy pomysł? Nie potrzebujesz przypadkiem ochroniarza? Bo wyglądasz... słabo. Martwię się, że daleko nie zajdziesz, hehe. Pamiętaj, to świta tworzy królów. A zła kompania może ich zgubić.";
			link.l1 = "I co by "+GetSexPhrase("król miał","królowa miała")+" z takim orszakiem jak ty? Tytuł "+GetSexPhrase("króla","lrólowej")+" z gnojowiska?";
			link.l1.go = "BM_Irons_17";
		break;
		
		case "BM_Irons_17":
			dialog.text = "Nie, nie! Składam ci prawdziwą ofertę, a ty...";
			link.l1 = "Jeszcze nie otrzymałem żadnej oferty. Ile żądasz za swoje usługi, Tommy?";
			link.l1.go = "BM_Irons_18";
		break;
		
		case "BM_Irons_18":
			dialog.text = "Dwieście pięćdziesiąt dubloonów z góry! By upewnić się, że mówisz poważnie, a nie tylko bujasz. I miesięczna opłata potem. Myślę, że możemy się dogadać.";
			link.l1 = "I ty nie...";
			link.l1.go = "BM_Irons_19";
		break;
		
		case "BM_Irons_19":
			dialog.text = "... myślisz, że masz odwagę? Heh, nawet nie będę z tobą dyskutować - widziałeś, jak zastrzeliłem tego rogacza z latarni morskiej? Pierwszy strzał! I żadnego targowania, jeśli to właśnie myślisz. Musisz pokazać, że stać cię na takiego profesjonalistę jak ja.";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "Tak, mogę! Dwieście pięćdziesiąt złotych monet. Proszę bardzo.";
				link.l1.go = "BM_Irons_Hire1";
			}
			link.l2 = "Miałeś szczęście z tym strzałem. A teraz próbujesz podnieść swoją wartość przechwałkami. Mogę się obejść bez takiego fachowca jak ty. To zbyt wielki zaszczyt i zbyt dużo pieniędzy.";
			link.l2.go = "BM_Irons_NoHire1";
			link.l3 = "Nie stać mnie teraz na to, bo nie noszę tyle w kieszeniach. Zostań tutaj i nigdzie nie idź - przyniosę złoto z okrętu i wrócę.";
			link.l3.go = "BM_Irons_Wait1";
		break;
		
		case "BM_Irons_Hire1":
			RemoveDublonsFromPCharTotal(250);
			
			dialog.text = "Nie jesteś taki zły, jak myślałem! Ale lepiej upewnij się, że się nie znudzę. Szkoda by było marnować mój talent, prawda? Tommy i "+pchar.name+"  Zaszalejmy na Karaibach! ";
			link.l1 = "Ucz się szanować hierarchię dowodzenia, Tommy. Po drugie, jestem dla ciebie kapitanem. Rozumiesz?";
			link.l1.go = "BM_Irons_Hire2";
		break;
		
		case "BM_Irons_Hire2":
			dialog.text = "Heh, ależ oczywiście, Kapitanie Nuda.";
			link.l1 = "Och, już zaczynam tego żałować...";
			link.l1.go = "Irons_hire";
		break;
		
		case "Irons_Hire":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetPlayerType(pchar);
			DeleteAttribute(npchar, "LifeDay");
			LAi_SetImmortal(npchar, false);
			npchar.quest.OfficerPrice = 15000;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.CompanionDisable = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			SetCharacterPerk(npchar, "ShipEscape");
			npchar.CanTakeMushket = true;
			pchar.questTemp.IronsItemsBlock = true;
			LAi_SetOfficerType(npchar);
			NextDiag.CurrentNode = "Irons_officer";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			LAi_SetHP(npchar, 170.0, 170.0);
			
			// Костыли, нужно украсить интерфейс офицера ==>
			//RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			//TakeItemFromCharacter(npchar, "unarmed");
			//GiveItem2Character(npchar, "blade_42");
			//EquipCharacterByItem(npchar, "blade_42");
			//EquipCharacterByItem(npchar, "mushket1");
			//EquipCharacterByItem(npchar, "indian_2");
			// <== Костыли, нужно украсить интерфейс офицера
			
			if (CheckAttribute(pchar, "questTemp.BM_hireInGrot"))
			{
				AddQuestRecord("BlackMark", "4");
			}
			else
			{
				AddQuestRecord("BlackMark", "1");
			}
			
			// Продолжение через неделю в джунглях
			SetTimerCondition("BM_FirstJungle_Time", 0, 0, 7, false);
		break;
		
		case "BM_Irons_NoHire1":
			dialog.text = "Cóż, jesteś głupcem, "+GetSexPhrase("młody człowieku","młoda damo")+"! I zupełnie brak ci rozsądku. Radzę ci to naprawić, bo inaczej długo nie pociągniesz. Zwłaszcza na Archipelagu.";
			link.l1 = "Poradzę sobie bez ciebie, Tommy. Żegnaj.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_IronsGoodbye");
		break;
		
		case "BM_Irons_Wait1":
			dialog.text = "Ty tak na poważnie? Banda żołnierzy właśnie tu zginęła, geniuszu! Pewnie wkrótce wyślą kolejny oddział. Nie, mógłbym zamknąć drzwi latarni i zorganizować obronę, ale czy chcę? Nie.";
			link.l1 = "Więc co sugerujesz?";
			link.l1.go = "BM_Irons_Wait2";
		break;
		
		case "BM_Irons_Wait2":
			dialog.text = "Spotkaj się ze mną w jaskini w dżungli. Dam ci kilka dni na zarobienie wystarczającej sumy, by zapłacić za moje usługi - wiesz, jak władać mieczem, może ci się uda.";
			link.l1 = "Jesteś poważny? Będziesz tam jak zaszczuty szczur.";
			link.l1.go = "BM_Irons_Wait3";
		break;
		
		case "BM_Irons_Wait3":
			dialog.text = "Tylko jeśli będą mnie szukać konkretnie, z dużym oddziałem. Więc myślę, że będzie w porządku. A teraz muszę iść - będą tu wkrótce. Do zobaczenia później.";
			link.l1 = "Tak, muszę też iść, na wszelki wypadek.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_IronsToCave");
		break;
		
		case "BM_Irons_WaitInCave1":
			dialog.text = "Aye, tu jesteś! Zaczynałem myśleć, że nie masz w sobie tego, by zarabiać pieniądze. Czasami myślę, że tacy ludzie jak ty rodzą się z tym. A jeśli nie, umierają w biedzie, nie przepracowawszy ani dnia jak uczciwi ludzie.";
			link.l1 = "Prosze prosze, Tommy. Jeśli nie chcesz dołączyć do mojej załogi, to nie. Widzę, że lubisz zagnieżdżać się w tej norze.";
			link.l1.go = "BM_Irons_WaitInCave2";
			DelLandQuestMark(npchar);
		break;
		
		case "BM_Irons_WaitInCave2":
			dialog.text = "Najwidoczniej nie chowałeś się w jamach podczas pory deszczowej w Irlandii, "+GetSexPhrase("młokosie","dziewczyno")+"! Ale pójście z tobą jest lepsze niż ukrywanie się tutaj. Teraz, o tym złocie...";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "Oto twoje złoto.";
				link.l1.go = "BM_Irons_HireInCave1";
			}
			link.l2 = "Jeszcze tego nie mam. Pomyślałem, że sprawdzę, czy nie uciekłeś gdzie indziej.";
			link.l2.go = "BM_Irons_NoHireInCave1";
		break;
		
		case "BM_Irons_HireInCave1":
			RemoveDublonsFromPCharTotal(250);
			pchar.quest.BM_IronsTimeOver.over = "yes";
			pchar.questTemp.BM_hireInGrot = true;
			
			dialog.text = "Teraz to rozumiem! Co robimy dalej... Kapitanie?";
			link.l1 = "Przede wszystkim wyjdźmy z tego wilgotnego miejsca, bo zaraz zacznę kichać.";
			link.l1.go = "BM_Irons_HireInCave2";
		break;
		
		case "BM_Irons_HireInCave2":
			dialog.text = "Och, powinieneś spróbować wojny. Czuję się niemal jak w domu w takich miejscach.";
			link.l1 = "Widzę, że dostałeś swoją dymisję i zapomniałeś o szacunku i podporządkowaniu, co, Tommy? Nie martw się, nie zawaham się nauczyć cię ponownie, jeśli będę musiał. Teraz chodźmy.";
			link.l1.go = "Irons_hire";
		break;
		
		case "BM_Irons_NoHireInCave1":
			NextDiag.TempNode = "BM_Irons_WaitInCave3";
			
			dialog.text = "Heh, Tommy Irons nigdy nie ucieka! On dotrzymuje słowa. A ty dotrzymasz swojego?";
			link.l1 = "Pracuję nad tym.";
			link.l1.go = "Exit";
		break;
		
		case "BM_Irons_WaitInCave3":
			dialog.text = "Przyniosłeś złoto?";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "Oto twoje złoto.";
				link.l1.go = "BM_Irons_HireInCave1";
			}
			link.l2 = "Jeszcze tego nie mam. Pomyślałem, że sprawdzę, czy nie uciekłeś gdzieś indziej.";
			link.l2.go = "BM_Irons_NoHireInCave1";
		break;
		
		case "BM_IronsJungleUhodit":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			
			sld = characterFromID("Irons");
			RemovePassenger(pchar, sld);
			LAi_SetWarriorType(sld);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			sld.lifeday = 0;
			LAi_CharacterDisableDialog(sld);
			GiveItem2Character(sld, "blade_42");
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			//LAi_ActorRunToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			AddQuestRecord("BlackMark", "5");
			AddQuestUserData("BlackMark", "sSex1", GetSexPhrase("","а"));
			CloseQuestHeader("BlackMark");
		break;
		
		case "BM_IronsFirstJungle_1":
			dialog.text = "Słuchaj, kapitanie...";
			link.l1 = "Co tam, Tommy?";
			link.l1.go = "BM_IronsFirstJungle_2";
		break;
		
		case "BM_IronsFirstJungle_2":
			dialog.text = "Czy nie masz przy sobie dodatkowej rundy amunicji? Nie tylko kulę, ale pełnoprawny, papierem owinięty ładunek.";
			link.l1 = "Czy to kolejny z twoich dowcipów? Regularnie daję ci kule i naboje, cokolwiek potrzebujesz. I dlaczego dokładnie jeden nabój, a nie garść?";
			link.l1.go = "BM_IronsFirstJungle_3";
		break;
		
		case "BM_IronsFirstJungle_3":
			dialog.text = "Czemu tak źle przyjmujesz moją prośbę? Nie proszę o krwawe perły, tylko o nabój. Czekałem nawet, aż wyjdziemy do dżungli, żeby cię nie rozpraszać w interesach w mieście. Więc, masz nabój?";
			if (CheckCharacterItem(PChar, "cartridge"))
			{
				link.l1 = "Tak, mam kolejkę. Proszę bardzo. Tylko nie rób ze mnie głupca z tym nabojem. Rozumiesz, Tommy?";
				link.l1.go = "BM_IronsFirstJungle_7";
			}
			link.l2 = "Na ten moment nie, nie mam. To nie tak, że noszę jedną kulę w kieszeni, zastanawiając się, co jeśli Tommy o nią poprosi...?";
			link.l2.go = "BM_IronsFirstJungle_4";
		break;
		
		case "BM_IronsFirstJungle_4":
			dialog.text = "Cóż, to trafna uwaga, i szybko pojmujesz, hehe. Ale obawiam się, że tutaj nasze drogi się rozchodzą, zatem.";
			link.l1 = "Jesteś poważny? Obrażasz się o kulę? Daj spokój, chodźmy na statek i weźmy jedną stamtąd. Jeśli tak pilnie jej potrzebujesz, zdobędę dla ciebie jedną, dziesięć, ile tylko potrzebujesz.";
			link.l1.go = "BM_IronsFirstJungle_5";
		break;
		
		case "BM_IronsFirstJungle_5":
			dialog.text = "Nie. W końcu nie ma w tobie nic wyjątkowego. Dobry kapitan zawsze potrafi zaopatrzyć swoją załogę we wszystko, czego potrzebują. Więc pójdę.";
			link.l1 = "A gdybyśmy byli na morzu, zabrakło rumu, a ty chciałbyś więcej? Czy rozwiązałbyś szalupę i odpłynął? Czy skoczyłbyś do wody?";
			link.l1.go = "BM_IronsFirstJungle_6";
		break;
		
		case "BM_IronsFirstJungle_6":
			dialog.text = "Ha-ha-ha! Pośmiałem się, ale w tej smutnej chwili nawet dobry dowcip nie pomoże. Żegnaj, Kapitanie Nuda.";
			link.l1 = "A cholera z tobą, Tommy. Żegnaj.";
			link.l1.go = "BM_IronsJungleUhodit";
		break;
		
		case "BM_IronsFirstJungle_7":
			dialog.text = "Nie mogę nic obiecać, heh-heh. Dobry dowcip rozjaśnia atmosferę. Ale dzięki, oczywiście.";
			link.l1 = "Dobrze, chodźmy, ty żartownisiu.";
			link.l1.go = "BM_IronsFirstJungle_8";
			TakeItemFromCharacter(pchar, "cartridge");
		break;
		
		case "BM_IronsFirstJungle_8":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			Return_IronsOfficer();
			SetTimerCondition("BM_SecondJungle_Time", 0, 0, 7, false);
		break;
		
		case "BM_IronsSecondJungle_1":
			dialog.text = "Ej, Kapitanie!";
			link.l1 = "Tak, Tommy?";
			link.l1.go = "BM_IronsSecondJungle_2";
		break;
		
		case "BM_IronsSecondJungle_2":
			dialog.text = "Masz jeszcze jeden papierowy nabój?";
			link.l1 = "Co się stało z ostatnim? I co to był za żart o wkładzie? Czekałem dwa tygodnie na jakiś głupi żart od ciebie, ale nic.";
			link.l1.go = "BM_IronsSecondJungle_3";
		break;
		
		case "BM_IronsSecondJungle_3":
			dialog.text = "O, to będzie zabójczy dowcip, zaufaj mi. Pokochasz go, hehe. Jeszcze tylko nie złożyłem wszystkiego w całość. A co z nabojem?";
			if (CheckCharacterItem(PChar, "cartridge"))
			{
				link.l1 = "Prosze bardzo. Mam nadzieję, że naprawdę spodoba mi się twój nadchodzący żart. A gdzie schowałeś ostatnią rundę? Dałem ci ich mnóstwo. Czy trzymasz amunicję do walki w jednym miejscu, a dowcipy w innym?";
				link.l1.go = "BM_IronsSecondJungle_7";
			}
			link.l2 = "Nie noszę amunicji dla Twoich głupich żartów, Tommy! Mogłeś poprosić o całą partię zamiast tylko jednego naboju dwa tygodnie temu!";
			link.l2.go = "BM_IronsSecondJungle_4";
		break;
		
		case "BM_IronsSecondJungle_4":
			dialog.text = "I tak zrobiłem! Myślałem, że kto się mianuje moim kapitanem, zawsze dba o potrzeby swojej załogi.";
			link.l1 = "Nie udaję nikogo, Tommy. Dawno temu postanowiłem być sobą. Kto czuje się ze mną dobrze, w porządku. Jeśli nie, również w porządku.";
			link.l1.go = "BM_IronsSecondJungle_5";
		break;
		
		case "BM_IronsSecondJungle_5":
			dialog.text = "Heh, ty i ja jesteśmy pod tym względem podobni. Ale mam pewne wymagania dla mojego kapitana. A ty już ich nie spełniasz, młodzieńcze. To tutaj się rozstajemy.";
			link.l1 = "Naprawde? Obrażasz się na mnie tylko dlatego bo nie dałem ci jakiegoś jebanego papierowego naboju?";
			link.l1.go = "BM_IronsSecondJungle_6";
		break;
		
		case "BM_IronsSecondJungle_6":
			dialog.text = "To wykluczone. Zazwyczaj radzę ludziom robić, co im się podoba, i brać z życia to, czego chcą. Radziłbym ci w przyszłości więcej myśleć o swoich ludziach. Do widzenia.";
			link.l1 = "I radzę ci zadbać o swoją głowę - zrobili jej więcej szkody, niż zdajesz sobie sprawę. Żegnaj, Tommy.";
			link.l1.go = "BM_IronsJungleUhodit";
		break;
		
		case "BM_IronsSecondJungle_7":
			dialog.text = "Dowiesz się. Wszystko w swoim czasie, hehe.";
			link.l1 = "Och, mam złe przeczucia co do tego, Tommy...";
			link.l1.go = "BM_IronsSecondJungle_8";
			TakeItemFromCharacter(pchar, "cartridge");
		break;
		
		case "BM_IronsSecondJungle_8":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			Return_IronsOfficer();
			SetTimerCondition("BM_ThirdJungle_Time", 0, 0, 7, false);
		break;
		
		case "BM_IronsThirdJungle_1":
			dialog.text = "Mam pytanie do ciebie, Kapitanie.";
			link.l1 = "Aye, Tommy, co się dzieje?";
			link.l1.go = "BM_IronsThirdJungle_2";
		break;
		
		case "BM_IronsThirdJungle_2":
			dialog.text = "Nie zgadłeś? Zgadywanie to przydatna umiejętność, hehe. Ty, ja, dżungla... Około dwóch tygodni temu mieliśmy tę rozmowę. Potrzebuję kolejnego papierowego naboju.";
			if (CheckCharacterItem(PChar, "cartridge"))
			{
				link.l1 = "To się staje zabawną tradycją, prawda? Minęły dwa tygodnie - Tommy prosi o nabój. Proszę bardzo. Ile jeszcze potrzebujesz do tego swojego dowcipu?";
				link.l1.go = "BM_IronsThirdJungle_5";
			}
			link.l2 = "Jak długo jeszcze, Tommy?! Jak długo to będzie trwało? Czy wy, Ironsides, dostajecie tylko jeden nabój przed każdą bitwą?! Nie muszę mieć zawsze przy sobie amunicji na wasze dziwactwa, wiesz o tym!";
			link.l2.go = "BM_IronsThirdJungle_3";
		break;
		
		case "BM_IronsThirdJungle_3":
			dialog.text = "Tak naprawdę, jako mój kapitan, to twoim obowiązkiem jest zapewnić mi wszystko, czego potrzebuję do bitew i nie tylko.";
			link.l1 = "Jesteś zdezorientowany, Tommy. Twoim obowiązkiem jest słuchać rozkazów kapitana. Zawsze dostarczam wam wszystko - leki, amunicję, rum. To, że nie bierzesz tego, czego potrzebujesz na czas, a potem zachowujesz się jak żebrak, to tylko twoja wina!";
			link.l1.go = "BM_IronsThirdJungle_4";
		break;
		
		case "BM_IronsThirdJungle_4":
			dialog.text = "Jesteś taki bystry - dlaczego do tej pory niczego tu nie osiągnąłeś? Powiem ci, dlaczego. Bo nie myślisz naprzód i nigdy nie jesteś na nic gotowy. Nie wiesz, co robisz, nudziarzu. Nie uznam takiej osoby za mojego dowódcę, więc żegnaj.";
			link.l1 = "I wcale nie używasz głowy! Dobrej podróży, ty przeklęty głupcze!";
			link.l1.go = "BM_IronsJungleUhodit";
		break;
		
		case "BM_IronsThirdJungle_5":
			dialog.text = "Ten się nada, hehe.";
			link.l1 = "W końcu się ogarnąłeś, co? Ale po co?";
			link.l1.go = "BM_IronsThirdJungle_6";
			TakeItemFromCharacter(pchar, "cartridge");
		break;
		
		case "BM_IronsThirdJungle_6":
			dialog.text = "Po prostu robiłem sobie z ciebie żarty, sprawdzając, czy znów staniesz się swoim zrzędliwym sobą. Hehe. Ale dzięki za nabój.";
			link.l1 = "Twoje żarty są dziwne, Tommy.";
			link.l1.go = "BM_IronsThirdJungle_7";
		break;
		
		case "BM_IronsThirdJungle_7":
			dialog.text = "To też był żart. Nie kolekcjonowałem ich, tylko wybierałem. Potrzebowałem naboju, który byłby niemal idealny. Ten się nada. Tak, z tym nabojem kula poleci daleko i celnie. Tak jak wtedy, gdy rozwaliłem głowę starego Reasleya, ha-ha-ha!";
			link.l1 = "Stary Reasley, powiedziałeś... Frankie Rogacz, prawda? Ten, którego zastrzeliłeś przy latarni? Więc znacie się od dawna, co?";
			link.l1.go = "BM_IronsThirdJungle_8";
		break;
		
		case "BM_IronsThirdJungle_8":
			dialog.text = "Co? O cholera, powiedziałem to przez przypadek. Ale nie obchodzi mnie to - nigdy nie byłem dobry w kłamaniu ani w trzymaniu tajemnic.";
			link.l1 = "Zakładam, że druga kula była przeznaczona dla kogoś konkretnego, prawda, Tommy?";
			link.l1.go = "BM_IronsThirdJungle_9";
		break;
		
		case "BM_IronsThirdJungle_9":
			dialog.text = "Właśnie, geniuszu. Cóż, znam siebie i swoje cele, i nie wstydzę się tego. Dlatego nie obchodzi mnie, co myślisz – opowiem ci całą historię, dlaczego by nie, do cholery.";
			link.l1 = "Cóż, powiedz mi zatem. Nie zaszkodzi wiedzieć, co knujesz.";
			link.l1.go = "BM_IronsThirdJungle_10";
		break;
		
		case "BM_IronsThirdJungle_10":
			dialog.text = "No cóż, nie przerywaj mi, jak to zwykle robisz. Było ze mną w towarzystwie dwóch łajdaków - Francis Reasley i Gabriel Callow. Prawdziwe szczury! Nawet gorsze niż te biurowe szczury, które nie chciały mi dać mojej rezygnacji, co, wiesz, nie było łatwe do uzyskania.";
			link.l1 = "A co oni zrobili? Zwłaszcza ten drugi, Callow. Spałeś też z jego żoną? I również wysłał za tobą żołnierzy?";
			link.l1.go = "BM_IronsThirdJungle_11";
		break;
		
		case "BM_IronsThirdJungle_11":
			dialog.text = "Zamknij gębę, dobrze? Chociaż... nie miałbym nic przeciwko, hehe. Ale nie. Królewscy zaatakowali nas tego dnia. Kawaleria też. Było ich o wiele więcej. Gabe i Frankie uciekli jak przestraszone króliki. Ale ja zostałem z chłopakami. Byłem jedyny, który przeżył. Wiele zapomniałem z dzieciństwa i młodości, ale nie tego.";
			link.l1 = "A chcesz zemsty, bo uciekli? Nie każdy walczy dla jakiejś idei. Każdy chce przetrwać. Albo prawie każdy. Nawet jeśli ktoś walczy dla Rewolucji, mógł dołączyć przypadkiem i tego żałować.";
			link.l1.go = "BM_IronsThirdJungle_12";
		break;
		
		case "BM_IronsThirdJungle_12":
			dialog.text = "Ha, gdybym polował na każdego tchórza, musiałbym zastrzelić cały świat. Tchórze, do diabła z nimi. Ale oni mnie zdradzili. Powiedzieli wszystkim, że zdradziłem Rewolucję i wyrżnąłem całą naszą kompanię na rozkaz zwolenników Króla. Okłamałem cię w czymś, Kapitanie.";
			link.l1 = "Co to jest? Poza faktem, że skłamałeś o tym, że Frankie cię ściga tylko z powodu tego, co zrobiłeś z jego żoną?";
			link.l1.go = "BM_IronsThirdJungle_13";
		break;
		
		case "BM_IronsThirdJungle_13":
			dialog.text = "Nie, nie! Nie okłamałem cię, po prostu nie powiedziałem ci wszystkiego. Jest różnica. To, co skłamałem, dotyczyło rezygnacji. Nie było żadnej rezygnacji. Był trybunał. I szczęśliwy stary Tommy - zdecydowali się go nie powiesić, ale wysłać do kamieniołomów w południowych koloniach. Dokładnie na Barbados.";
			link.l1 = "Tak, to było szczęście. Ile lat tam pracowałeś?";
			link.l1.go = "BM_IronsThirdJungle_14";
		break;
		
		case "BM_IronsThirdJungle_14":
			dialog.text = "Żaden. Skoro ziemski trybunał skazał mnie z powodu tych szczurów, to niebiański na górze postanowił mnie ocalić. Gdy tylko przekroczyliśmy Archipelag, poczuliśmy jego atmosferę - nasz statek został abordażowany przez piratów.";
			link.l1 = "Więc zamiast kamieniołomów i plantacji Barbados, zostałeś sprzedany przez piratów do niewoli? Ale powiedziałeś, że nigdy nie pracowałeś w kamieniołomach.";
			link.l1.go = "BM_IronsThirdJungle_15";
		break;
		
		case "BM_IronsThirdJungle_15":
			dialog.text = "To właśnie powiedziałem - ktoś na górze postanowił mnie uratować. Co to była za akcja ratunkowa, hehe! Masz rację - piraci zwyciężyli nad tymi, którzy lubią znęcać się nad związanymi i zakutymi w kajdany ludźmi. Ale to była gorąca walka, tak gorąca jak słońce tutaj. A nasi wybawcy ponieśli pewne straty. Więc zaproponowali każdemu, kto chciał, dołączenie do nich.";
			link.l1 = "I do dołączyłeś do nich? Powiedziałeś, że pływałeś z piratami.";
			link.l1.go = "BM_IronsThirdJungle_16";
		break;
		
		case "BM_IronsThirdJungle_16":
			dialog.text = "Do diabła, tak! Najlepsze lata mojego życia. Jack Mills był kapitanem przez duże K - mam nadzieję, że pewnego dnia będziesz taki jak on. Pływałem na jego 'Crane' przez około dwa lata, aż...";
			link.l1 = "... aż miałeś dość bezprawia, jak mówiłeś? Dlaczego mówisz, że to były najlepsze lata twojego życia?";
			link.l1.go = "BM_IronsThirdJungle_17";
		break;
		
		case "BM_IronsThirdJungle_17":
			dialog.text = "Eh... aż usłyszałem, że ci dwaj zdrajcy również skończyli w Archipelagu. Aye, wiem, mówiłem ci, że mam dość piractwa na otwartym morzu i tego wszystkiego. I już ci mówiłem, że nie obchodzi mnie, co myślisz. To nadal prawda, ale nie znałem cię dobrze, kiedy się pierwszy raz spotkaliśmy. Nie wiedziałem, jak zareagujesz. Dlatego mówiłem różne rzeczy.";
			link.l1 = "Jesteś kłamcą, Tommy! Ale dobrze, dlaczego opuściłeś 'Żurawia'?";
			link.l1.go = "BM_IronsThirdJungle_18";
		break;
		
		case "BM_IronsThirdJungle_18":
			dialog.text = "Ponieważ Jack był prawdziwym przywódcą, więc powiedział, że nie zrobi objazdu dla jednego człowieka, nie będzie na niego czekał, nie będzie szukał zemsty i nie będzie zadzierał z wybitnymi oficerami Brytyjskiej Marynarki zamiast atakować tłuste statki kupieckie.";
			link.l1 = "Wyróżniający się oficerowie? Frank był cywilem, tak sądzę.";
			link.l1.go = "BM_IronsThirdJungle_19";
		break;
		
		case "BM_IronsThirdJungle_19":
			dialog.text = "Eh, nie zawsze taki był. Zawsze był, wiesz, trochę mętny. A kiedy próbował kogoś wrobić, wyrzucono go w niesławie. Próbował pływać na kupcu, ale uczciwa praca nie była jego działką. Ostatecznie osiedlił się tutaj.";
			link.l1 = "Wciąż nie nazwałbym go wybitnym oficerem.";
			link.l1.go = "BM_IronsThirdJungle_20";
		break;
		
		case "BM_IronsThirdJungle_20":
			dialog.text = "Nie zapomnij o Gabe'u. Został porucznikiem w domu. I dostał tutaj w Port Royal nominację na kapitana statku, 'Principio'.";
			link.l1 = "Nie brzmi to zbyt po angielsku.";
			link.l1.go = "BM_IronsThirdJungle_21";
		break;
		
		case "BM_IronsThirdJungle_21":
			dialog.text = "Dobrze powiedziane! Statek zmieniał właścicieli jak portowa dziewka, więc widział wszelkiego rodzaju rzeczy. Ale wciąż jest zdatny do żeglugi. A Gabe to utalentowany kapitan, niech go diabli.";
			link.l1 = "A Jack bał się z nim mieć do czynienia? Czy jest tak dobry, jak mówisz?";
			link.l1.go = "BM_IronsThirdJungle_22";
		break;
		
		case "BM_IronsThirdJungle_22":
			dialog.text = "Dobrze, dobrze! Bardziej jakby nie chciał tracić czasu na mnie. Mówiąc o Jacku, podobało mi się kilka tradycji, które po raz pierwszy zobaczyłem u niego - chodzenie po desce i rozdawanie czarnych znaków. To dało mi wtedy zabawny pomysł.";
			link.l1 = "Czarne... znaki? Chodzi ci o czarną plamę, prawda? I co to było, Tommy? Nie sądzę, żeby wiedział, co robić, gdybyś mu wręczył czarną plamę. Czy to się stało? Chciałeś mu to przekazać, a on zaatakował cię, gdy tylko cię zobaczył, więc uciekłeś do latarni morskiej, a on zabrał ze sobą oddział żołnierzy, mówiąc im, że jesteś piratem?";
			link.l1.go = "BM_IronsThirdJungle_23";
		break;
		
		case "BM_IronsThirdJungle_23":
			dialog.text = " Wolę nazywać to czarną plamą. Brzmi to lepiej. Prosta czarna plama nie sprawiłaby, że coś zrozumiał. Ale czarna plama z naszej jedwabnej chusteczki, która była charakterystycznym znakiem naszej kompanii - to by zrozumiał. Dyskretnie wsunąłem ją do jego kieszeni. Potem upewniłem się, że widział, jak kieruję się do latarni morskiej. Resztę znasz. ";
			link.l1 = "A przemytnicy?";
			link.l1.go = "BM_IronsThirdJungle_24";
		break;
		
		case "BM_IronsThirdJungle_24":
			dialog.text = "Złe miejsce, zły czas. Nawet trochę było mi ich żal. Ale tylko trochę, hehe.";
			link.l1 = "A dla Frankiego?";
			link.l1.go = "BM_IronsThirdJungle_25";
		break;
		
		case "BM_IronsThirdJungle_25":
			dialog.text = "Kogo to teraz obchodzi? Mamy większe ryby do smażenia. Zostaje Gabe. To będzie trudne. Musimy...";
			link.l1 = "My?";
			link.l1.go = "BM_IronsThirdJungle_26";
		break;
		
		case "BM_IronsThirdJungle_26":
			dialog.text = "Cóż, co innego to usłyszeć ciekawą opowieść, a co innego stworzyć ją samemu! Oto plan. Będziemy musieli zostawić Gabe'owi kolejny specjalny czarny znak - już go przygotowałem. Następnie podążymy jego śladami do Portland Cove, gdzie rozprawimy się z nim bez śladu.";
			link.l1 = "A gdzie mamy to zasadzić?";
			link.l1.go = "BM_IronsThirdJungle_27";
		break;
		
		case "BM_IronsThirdJungle_27":
			dialog.text = "Ha ha ha, oto co miałem na myśli, gdy powiedziałem, że chciałbym, żebyś był bardziej jak Jack, Kapitanie. No dalej, nie bądź nudziarzem, widzę, jak twoje oczy płoną!";
			link.l1 = "Raczej byłem rzeczywiście nieco zainteresowany twoją opowieścią.";
			link.l1.go = "BM_IronsThirdJungle_28";
		break;
		
		case "BM_IronsThirdJungle_28":
			dialog.text = "Oczywiście, w jego domu! Co to za pytanie? Osiedlił się w Port Royal. Ty i ja zacumujemy w zatoce, abyśmy mogli opuścić wyspę, jeśli coś pójdzie nie tak.";
			link.l1 = "Czy wiesz, gdzie jest jego dom?";
			link.l1.go = "BM_IronsThirdJungle_29";
		break;
		
		case "BM_IronsThirdJungle_29":
			dialog.text = "Nie. Ale nie jest trudno się dowiedzieć. Zapytamy pijaków - sprzedaliby własną matkę, gdybyś kupił im drinka lub dwa. No, co myślisz o moim planie?";
			if (GetSummonSkillFromName(pchar, SKILL_ACCURACY) > 24 && GetSummonSkillFromName(pchar, SKILL_GRAPPLING) > 24 && GetSummonSkillFromName(pchar, SKILL_SAILING) > 24)
			{
				link.l1 = "Jeśli jest kapitanem statku płynącego na Jamajkę, cały czas patroluje wody wyspy. Atakowanie pod fałszywą banderą jest lepsze niż próbowanie czegokolwiek w mieście.";
				link.l1.go = "BM_IronsThirdJungle_Sea1";	// Морской вариант
				notification("Skill Check Passed", SKILL_SAILING);
				notification("Skill Check Passed", SKILL_ACCURACY);
				notification("Skill Check Passed", SKILL_GRAPPLING);
			}
			else
			{
				if (GetSummonSkillFromName(pchar, SKILL_SAILING) < 25) notification("Skill Check Failed (25)", SKILL_SAILING);
				if (GetSummonSkillFromName(pchar, SKILL_ACCURACY) < 25) notification("Skill Check Failed (25)", SKILL_ACCURACY);
				if (GetSummonSkillFromName(pchar, SKILL_GRAPPLING) < 25) notification("Skill Check Failed (25)", SKILL_GRAPPLING);
			}
			link.l2 = "Nie jest to bez wad, i zostawiasz wiele przypadkowi. Ale ogólnie, jest do zrobienia. Jestem z tobą, Tommy. Pozbyłeś się jednego, nie możesz pozwolić, by drugi odszedł, prawda?";
			link.l2.go = "BM_IronsThirdJungle_Land1";	// Сухопутный вариант
			link.l3 = "Nie będę się angażował w twoją zemstę i ryzykował mojej relacji z Anglią dla tej przygody, gdzie tak wiele zależy od przypadku, Tommy.";
			link.l3.go = "BM_IronsThirdJungle_Otkaz1";	// Отказ
		break;
		
		case "BM_IronsThirdJungle_Sea1":
			dialog.text = "Jesteś ryzykownym człowiekiem, kapitanie! Zaczynam cię lubić. Ale Gabe na starym 'Principio' nie jest łatwym łupem - jest o wiele bardziej niebezpieczny niż inni kapitanowie na takim statku.";
			link.l1 = "Co myślisz, że jestem tchórzem, Tommy? Sami go przejmujemy, a ty możesz z nim porozmawiać od serca. Daj mu czarną plamę tuż przed tym, jak zostanie obalony.";
			link.l1.go = "BM_IronsThirdJungle_Sea2";
		break;
		
		case "BM_IronsThirdJungle_Sea2":
			dialog.text = "Heh, może nie jesteś tchórzem, ale on jest, chociaż cwany. Nie zaatakuje żołnierza ani nawet pirata większego od jego statku. Jeśli zobaczy coś takiego na horyzoncie, schowa się pod skrzydło fortu.";
			link.l1 = "Hmm, a co z   okrętami kupieckimi?";
			link.l1.go = "BM_IronsThirdJungle_Sea3";
		break;
		
		case "BM_IronsThirdJungle_Sea3":
			dialog.text = "Tak, to może zadziałać! Ale znowu, nic większego niż bark! Gabe to nie tylko tchórz - nigdy nie był na tyle chciwy, by pozwolić, żeby to przeważyło jego ostrożność.";
			link.l1 = "Miejmy nadzieję, że to zadziała, Tommy. A więc, barka piątej klasy pod hiszpańską lub holenderską banderą. Przygotuj się na spotkanie ze swoim starym wojennym towarzyszem!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_SeaVariant");
		break;
		
		case "BM_IronsThirdJungle_Land1":
			dialog.text = "Wiedziałem, że mogę na ciebie liczyć! Może pewnego dnia będziesz nawet lepszym kapitanem niż Jack. A co do mojego szczęścia... Dotychczas mnie nie zawiodło, więc znowu na nie postawię. Wyruszamy, zatem?";
			link.l1 = "Tak, nie przeciągajmy tego zbyt długo. Im szybciej to się skończy, tym lepiej.";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_LandVariant");
		break;
		
		case "BM_IronsThirdJungle_Otkaz1":
			dialog.text = "Heh, miałem nadzieję, że będzie inaczej, ale spodziewałem się tego - nie masz odwagi na takie rzeczy, "+GetSexPhrase("młokos","moja dziewczyno")+"  Każdy prawdziwy kapitan miał przynajmniej kilka takich sytuacji, gdzie dyskretnie rozprawiał się ze szczurami. Czasem nawet z własnymi szczurami.";
			link.l1 = "Przypuszczam, że mam dać się sprowokować i powiedzieć, że zmieniłem zdanie i udowodnię, że jestem prawdziwym kapitanem, co, Tommy? Ale rozumiem twoje pragnienie zemsty. Nie zmuszę cię do opuszczenia załogi jak zrobił to Jack. Ile czasu ci potrzeba na to? Do tego czasu dotrę na Jamajkę.";
			link.l1.go = "BM_IronsThirdJungle_Otkaz2";
		break;
		
		case "BM_IronsThirdJungle_Otkaz2":
			dialog.text = "Ha ha ha, dorastasz. Prawie cię szanuję za to, że się na to nie nabrałeś. Ale nie musisz czekać i odbierać mnie później - sam to skończę. W końcu, wszystko czego zawsze chciałem, to ktoś chętny zrobić coś dla mnie jako mój kapitan. Więc żegnaj. Dbaj o Anglię, ha-ha.";
			link.l1 = "Jesteś naprawdę dziwny. Ale jak sobie życzysz. Do widzenia! I powodzenia z twoją zemstą, Tommy.";
			link.l1.go = "BM_IronsThirdJungle_Otkaz3";
		break;
		
		case "BM_IronsThirdJungle_Otkaz3":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			
			sld = characterFromID("Irons");
			RemovePassenger(pchar, sld);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			sld.location = "None";
			AddQuestRecord("BlackMark", "6");
			AddQuestUserData("BlackMark", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("BlackMark", "sSex1", GetSexPhrase("к","чка"));
			CloseQuestHeader("BlackMark");
		break;
		
		case "BM_IronsJamaicaShore1":
			dialog.text = "Świetnie, możemy się stąd szybko wycofać, jeśli zajdzie taka potrzeba. Weź to - daj Gabe'owi notatkę i czarną plamę, gdy dowiesz się, gdzie mieszka i kiedy jest w domu.";
			link.l1 = "Och, więc teraz to ty dyktujesz warunki, Tommy. Ale pamiętaj, że wciąż jestem twoim kapitanem. Co zamierzasz robić, gdy będę w mieście?";
			link.l1.go = "BM_IronsJamaicaShore2";
		break;
		
		case "BM_IronsJamaicaShore2":
			dialog.text = "Heh, jak mógłbym o tym zapomnieć, Kapitanie Nudny? Jeśli Gabe mnie zobaczy na ulicach, albo podniesie alarm, albo zmyje się z wyspy, ten przeklęty tchórz. Nie martw się, przygotuję tu zasadzkę, hehehe.";
			link.l1 = "Zasadzka, mówisz. Dobrze, Tommy. Dajmy twojemu staremu towarzyszowi wojennemu godne spotkanie, ha ha ha ha!";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_IronsJamaicaGo");
		break;
		
		case "BM_Pyanitsa_0":
			dialog.text = "Hik! To świetny rum! Hik... Na zdrowie!";
				link.l1 = "Słuchaj, kumplu, co słychać w mieście o kapitanie Gabrielu Callowie?";
			link.l1.go = "BM_Pyanitsa_1";
			DelLandQuestMark(npchar);	//Удаляем квестмарку
		break;
		
		case "BM_Pyanitsa_1":
			dialog.text = "Stary Gabe?! Same dobre rzeczy! Dlaczego, hic, co to jest?";
			link.l1 = "„Och, doprawdy? Miło to słyszeć. Cóż, jest problem z piratem. Komendant zajmuje się głównie sprawami lądowymi, a ja nie chcę niepokoić Jego Lordowskiej Mości.”";
			link.l1.go = "BM_Pyanitsa_2";
		break;
		
		case "BM_Pyanitsa_2":
			dialog.text = "Wtedy idź prosto do Gabe'a, mówię ci! Nie ma bardziej uczciwego ani odważniejszego kapitana w mieście niż Gabe. Nawet pułkownik Doyley darzy go wielkim szacunkiem. Pływa na statku, który kiedyś należał do samego Nicolasa Sharpa, czy możesz w to uwierzyć?";
			link.l1 = " Nie jestem jeszcze na tyle pijany, żeby w to uwierzyć, kumplu.";
			link.l1.go = "BM_Pyanitsa_3";
		break;
		
		case "BM_Pyanitsa_3":
			dialog.text = "A-Aye, ależ tak! To Principio! Coś ci mówi, co?";
			link.l1 = "Hiszpański statek zdobyczny, tak? Dlaczego?";
			link.l1.go = "BM_Pyanitsa_4";
		break;
		
		case "BM_Pyanitsa_4":
			dialog.text = "Kiedy ostatni raz widziałeś różowego na własne oczy, co? Wiem, co mówię, eek!";
			link.l1 = "Cóż, nie wiem, czy projekt statku jest aż tak niezwykły.";
			link.l1.go = "BM_Pyanitsa_5";
		break;
		
		case "BM_Pyanitsa_5":
			dialog.text = "Ależ tak jest! Nikt teraz nie dowodziłby takim gratem, przy tych wszystkich nowych projektach! Przestali je budować w stoczniach prawie t-trzydzieści lat temu! Nic sam ją prowadził, mówię ci.";
			link.l1 = "Dobrze, kupię to. Więc, to jest statek. Jak to się stało, że ten wrak jeszcze się nie rozpadł?";
			link.l1.go = "BM_Pyanitsa_6";
		break;
		
		case "BM_Pyanitsa_6":
			if (sti(pchar.basenation) == ENGLAND) sStr = "our";
			else sStr = "your";
			dialog.text = "Cóż, nie jest już tak szybka, jak była w swoich najlepszych latach - jak ja po kolejnym drinku, ha-ha-ha! Ale dobry kapitan wciąż może coś wycisnąć z tej starej damy. Gabe też stara się nie wystawiać jej na linię ognia.";
			link.l1 = "Więc dlaczego statek nie został przemianowany? Może Okręt Jego Królewskiej Mości Thrashing, pod "+sStr+" stary reżim?";
			link.l1.go = "BM_Pyanitsa_7";
		break;
		
		case "BM_Pyanitsa_7":
			dialog.text = "Trad... Trad-trad-tradycja, eek! Sam Nic nigdy jej nie przemianował po ucieczce z hiszpańskiej plantacji na Kubie. Nigdy nie chciał zapomnieć o tym doświadczeniu - a Hiszpanie też nie! Powiem ci, ta bitwa niedaleko wybrzeża Tendales...";
			if (startHeroType == 4)
			{
				link.l1 = "Tendales, prawda? Huh, ostatni raz słyszałem to imię, gdy byłem dzieckiem. Nie sądziłem, że ktokolwiek jeszcze zna i pamięta o tych teraz opuszczonych skałach.";
				link.l1.go = "BM_Pyanitsa_8";
			}
			else
			{
				link.l1 = "Tendales? Gdzie to jest?";
				link.l1.go = "BM_Pyanitsa_8";
			}
		break;
		
		case "BM_Pyanitsa_8":
			dialog.text = "Albo to była, eek, Highrock? N-nie, zdecydowanie nie tam... W każdym razie, to nie ma znaczenia! Nic walczył i wygrał w tej różowej, niewiarygodne zwycięstwo przeciwko brygantynie Cuttlefish, wysłanej za nim przez Desmonda Raya Beltropa, Barona Piratów. Krew zepsuli sobie nawzajem przez długi czas, aż Nic pokonał samego Desmonda.";
			if (startHeroType == 4)
			{
				link.l1 = "Och, to imponujące! Chociaż, nie spodziewałbyś się niczego innego od Nicholasa. Eh, Sharps i Beltrops są zawsze razem, potem osobno - widocznie, historia naprawdę czasami się powtarza.";
				link.l1.go = "BM_Pyanitsa_9";
			}
			else
			{
				link.l1 = "Imponujące. Więc, jak Sharp rozstał się ze statkiem? Sprzedał ją w stoczni?";
				link.l1.go = "BM_Pyanitsa_9";
			}
		break;
		
		case "BM_Pyanitsa_9":
			dialog.text = "Nie. Po tamtym abordażu zaczęła przeciekać, więc Nic ją porzucił. Potem, z dużym przypływem, pinka została przyciągnięta na brzeg, tuż obok miasta.";
			link.l1 = "Jakby kogokolwiek interesował ten wrak.";
			link.l1.go = "BM_Pyanitsa_10";
		break;
		
		case "BM_Pyanitsa_10":
			dialog.text = "O, ale marynarka się zainteresowała! Praktyczni chłopcy. Zobaczyli statek pod angielską banderą, ale z hiszpańską nazwą i się zainteresowali. Nic zmarł kilka lat później, ale jego statek nadal pływał, zmieniając właścicieli, zawsze w krwawy sposób.";
			link.l1 = "To tylko kolejna opowieść o statku widmo, podczas gdy kapitanat Gabe'a jest bardzo realny. Więc myślę, że pójdę go zobaczyć. Czy wiesz, gdzie mieszka?";
			link.l1.go = "BM_Pyanitsa_11";
		break;
		
		case "BM_Pyanitsa_11":
			dialog.text = "Ha-ha! Oczywiście, hik, wiem! Wszyscy wiedzą! Stary Gabe mieszka przy starym wiatraku. Po prostu obejdź tawernę i spójrz w górę... hik!";
			link.l1 = "Kiedy on jest w domu? Wygląda na to, że jest zajętym człowiekiem.";
			link.l1.go = "BM_Pyanitsa_12";
		break;
		
		case "BM_Pyanitsa_12":
			dialog.text = "Zgadza się, kumplu! Ma mnóstwo do roboty. W domu jest tylko wieczorami, od dziesiątej. I wstaje punktualnie o szóstej, każdego dnia, sam. Żelazna dyscyplina!";
			link.l1 = "Dziękuję bardzo! Na razie mam dość tych pirackich opowieści.";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_SearchGabeHouse");
		break;
		
		case "BM_Callow1":
			if (startHeroType == 4) 
			{
				dialog.text = "Ty jesteś... Rumba? Słyszałem o tobie... ale nigdy wcześniej nie zwróciłaś się przeciwko swoim!";
				link.l1 = "Ja nie. Moja waśń nie dotyczy mojego kraju. Dotyczy ciebie, Gabe.";
				link.l1.go = "BM_Callow_Helena1";
			}
			else
			{
				dialog.text = "Nie jesteś kupcem...";
				link.l1 = "Niespodzianka, Gabe! Powiedziano mi, że jesteś ostrożny i nawet tchórzliwy. Chciwość zaćmiła twój osąd, prawda? Żaden kupiec nie szukałby abordażu tak jak ja.";
				link.l1.go = "BM_Callow2";
			}
		break;
		
		case "BM_Callow_Helena1":
			dialog.text = "Ze mną? Jaki jest problem? Moglibyśmy porozmawiać jak należy u mnie, albo nawet u ciebie. Jak kapitanowie, i... Co TY tutaj robisz?!";
			link.l1 = "";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_CabinDialog");
		break;
		
		case "BM_Callow2":
			dialog.text = "Rzeczywiście. Więc kim jesteś? Nie, do diabła z tobą, zresztą. Kim jest ten...";
			link.l1 = "";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_CabinDialog");
		break;
		
		case "BM_IronsClone1":
			dialog.text = "Tommy, czy to ty...?";
			link.l1 = "O tak, Gabe. I przyszedłem cię ukarać za to, co mi wtedy zrobiłeś.";
			link.l1.go = "BM_IronsClone2";
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			CharacterTurnByChr(sld, CharacterFromID("IronsClone"));
			sld = CharacterFromID("IronsClone");
			CharacterTurnByChr(sld, &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)]);
		break;
		
		case "BM_IronsClone2":
			dialog.text = "Ukarzesz mnie?! Uważaj na słowa, Thomasie! Jeśli któremuś z nas należy się kara, to tobie! Powiedziałeś, że przyprowadzisz posiłki! A my czekaliśmy, umierając pod kulami i mieczami królewskiej kawalerii!";
			link.l1 = "Zasuwałem cholernie ciężko, by przynieść pomoc! Ale prześcignęła mnie inna pieprzona siła! Krwawi zwolennicy Charlesa byli wszędzie! Przyparli mnie do muru, prawie zginąłem! Dobrze, że myśleli, że nie żyję. Ale wiesz, co zobaczyłem, Gabe?!";
			link.l1.go = "BM_IronsClone3";
		break;
		
		case "BM_IronsClone3":
			dialog.text = "Co się dzieje, Tom? Jesteś gotów wymyślać jakąkolwiek historię, by ten człowiek ci uwierzył?!";
			link.l1 = "Heh, ten człowiek i tak mnie nie zdradzi. Nie jest szczurem jak niektórzy.";
			link.l1.go = "BM_IronsClone4";
		break;
		
		case "BM_IronsClone4":
			dialog.text = "Nie ma wyboru! Zaatakować statek angielskiej marynarki!";
			link.l1 = "Oh, miał wybór od samego początku. I wybrał, by mi pomóc. Ty i Frankie też mieliście wybór. Wybraliście ucieczkę, żeby nie zginąć. A potem wróciliście i znaleźliście mnie na wpół martwego. I opowiedzieliście swoje nikczemne kłamstwa na trybunale. Wiedzieliście, że nikt mnie nie posłucha, bo dostałem w głowę i straciłem pamięć!";
			link.l1.go = "BM_IronsClone5";
		break;
		
		case "BM_IronsClone5":
			dialog.text = "Nikt by cię i tak nie posłuchał. Zawsze byłeś... poharatany, Thomas.";
			link.l1 = "O, więc nie ukrywasz, co zrobiłeś tamtego dnia. Mam coś dla ciebie, Gabe. Czarną plamę. Ale jaki jest sens dawać ci ją teraz, skoro statek został przejęty i zaraz rozprujemy ci flaki, hee hee hee hee hee hee...";
			link.l1.go = "BM_IronsClone6"; // здесь переход на кейс с боёвкой
		break;
		
		case "BM_IronsClone6":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			locCameraTarget(PChar);
			locCameraFollow();
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			
			sld = CharacterFromID("IronsClone");
			LAi_SetCheckMinHP(sld, 1, true, "");
			LAi_SetCurHPMax(sld);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "reload", "reload1", "BM_IronsCloneMushket", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			LAi_SetImmortal(sld, false);
			LAi_SetCurHPMax(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "BM_CabinDialog4");
		break;
		
		case "BM_IronsClone8":
			dialog.text = "Cóż, Gabe został obalony, hehehe. Od dawna chciałem to powiedzieć. Szkoda, że nie możesz już tego usłyszeć, kolego. O, poczekaj! Może możesz - z Piekła.";
			link.l1 = "Chodź, Tommy. Nawet jeśli tego nie słyszał, to widział i wiedział, że to dokładnie twój plan i zemsta. I nie mógł nic na to poradzić.";
			link.l1.go = "BM_IronsClone9";
		break;
		
		case "BM_IronsClone9":
			if (startHeroType == 4) 
			{
				dialog.text = "Heh, masz rację! Cholera, masz absolutną rację! Dzięki, że mi pomogłaś w tej sprawie. Wiesz, myślałem, że jesteś po prostu jakąś rozpieszczoną dziewczyną w błyszczącym stroju, która dostała statek dla zabawy. Ale jesteś cholernie dobrą kapitan! Założę się, że mogłabyś rzucić Jackowi wyzwanie.";
			}
			else
			{
				dialog.text = "Heh, masz rację! Cholera, masz absolutną rację! Dzięki, że mi pomogłeś w tej sprawie. Wiesz, myślę, że jesteś tak dobrym kapitanem jak Jack. A może nawet lepszym!";
			}
			link.l1 = "Och, teraz mi schlebiasz. Dziękuję. Chyba.";
			link.l1.go = "BM_IronsClone10";
		break;
		
		case "BM_IronsClone10":
			dialog.text = "Nie ma za co. Żadnego pochlebstwa. Jak być może zauważyłeś, rzadko kogokolwiek tak chwalę. Więc zamknij się i ciesz się, że mam o tobie takie wysokie mniemanie.";
			link.l1 = "Nie powiedziałbym, że podoba mi się sposób, w jaki to przedstawiasz, choć cieszę się, że ogólnie uważasz mnie za dobrego kapitana. Ale... łańcuch dowodzenia, Tommy, łańcuch dowodzenia.";
			link.l1.go = "BM_IronsClone11";
		break;
		
		case "BM_IronsClone11":
			if (startHeroType == 4) 
			{
				dialog.text = "Ach, daj spokój! Czuję, że wszystko, przez co przeszliśmy, zbliżyło nas do siebie, Ellie. Moglibyśmy być czymś więcej niż tylko kapitanem i oficerem. Przyznaj - nawet jeśli tylko przed sobą czujesz to samo.";
				link.l1 = "Tylko w twoich najśmielszych snach, Tommy. I to Helen, nie Ellie. Ale przypuszczam, że teraz możesz mnie nazywać Rumba.";
				link.l1.go = "BM_IronsClone12";
			}
			else
			{
				dialog.text = "Och, daj spokój, nudziarzu! Wydaje mi się, że nie jesteśmy już tylko kapitanem i jego oficerem, ale najprawdziwszymi przyjaciółmi. Czyż nie sądzisz?!";
				link.l1 = "Heh. Może. Lepiej być twoim przyjacielem niż wrogiem. A skoro etykieta wyraźnie nie jest twoją mocną stroną, chyba będę musiał się do tego przyzwyczaić.";
				link.l1.go = "BM_IronsClone12";
			}
		break;
		
		case "BM_IronsClone12":
			dialog.text = "Mam dla ciebie... prezent, Kapitanie.";
			link.l1 = "Hejże, spójrz na to! Czarny znak? Chcesz, żebym też został usunięty, co, Tommy? Chcesz sam zostać kapitanem? Ha-ha-ha-ha! Myślałem, że mówiłeś, że jesteśmy kumplami.";
			link.l1.go = "BM_IronsClone13";
			GiveItem2Character(PChar, "talisman15");		//Предмет Чёрная Метка
		break;
		
		case "BM_IronsClone13":
			dialog.text = "To czarna PLAMA, ty głąbie. Wiesz, zaczynam myśleć, że jak tylko wyhaftowałem czaszkę i skrzyżowane kości na tej chuście, zaczęła przynosić mi szczęście. Nie potrafię tego wyjaśnić. Weź to. A także... jeśli chcesz, zawsze możesz pożyczyć mój wierny miecz i zbroję... to, co z nich zostało, ha-ha! Przyda ci się! Daleko zajdziesz. I chcę być tego świadkiem. Nie chcę, żebyś zginął od zabłąkanej kuli.";
			link.l1 = "Dzięki, kumplu! Dam z siebie wszystko. A ty - patrz i podziwiaj, ha-ha-ha!";
			link.l1.go = "BM_IronsClone14";
		break;
		
		case "BM_IronsClone14":
			dialog.text = "Podziwiać, pewnie, ha-ha-ha. Aye. Więc, co postanowiłeś zrobić z tym statkiem? Z jednej strony, nie jest już zbyt użyteczny. Z drugiej strony, nie ma już takich jak on. Nie sądzę, by kiedykolwiek znów się pojawił.";
			if (startHeroType == 4) 
			{
				link.l1 = "Jeszcze nie zdecydowałem... Wiesz, Tommy, czuję pewne połączenie z tym statkiem. Nie potrafię tego wyjaśnić. Więc najpierw wyrzućmy to śmierdzące truchło stąd. Jeśli w ładowni nie ma przecieków, prawdopodobnie wezmę tę dziewczynę dla siebie.";
			}
			else
			{
				link.l1 = "Nie wiem, Tommy. Jeszcze nie zdecydowałem. W międzyczasie pozbądźmy się ciała Gabe'a. Na wypadek, gdybyśmy jednak zatrzymali statek.";
			}
			link.l1.go = "BM_IronsClone15";
		break;
		
		case "BM_IronsClone15":
			DialogExit();
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;
		
		case "BM_IronsPinkPotopil1":
			dialog.text = "Cóż, wykonałeś całkiem dobrą robotę na tym starożytnym statku, Kapitanie! I choć chciałem wykończyć Gabe'a własnymi rękami, nie będę gniewać Stwórcy, umniejszając to zwycięstwo.";
			link.l1 = "To by było niepotrzebne, Tommy. Mam nadzieję, że twoja dusza jest teraz w spokoju.";
			link.l1.go = "BM_IronsPinkPotopil2";
		break;
		
		case "BM_IronsPinkPotopil2":
			if (startHeroType == 4) 
			{
				dialog.text = "Czuję, że wszystko, co przeszliśmy, zbliżyło nas, Ellie. Moglibyśmy być czymś więcej niż tylko kapitanem i oficerem. Przyznaj to - nawet jeśli tylko przed sobą, też to czujesz.";
				link.l1 = "Tylko w twoich najdzikszych snach, Tommy. I jestem Helen, nie Ellie. Ale chyba możesz teraz nazywać mnie Rumba, jeśli przestaniesz z tym pochlebstwem.";
			}
			else
			{
				dialog.text = "Jeszcze nigdy w życiu nie byłem tak szczęśliwy! Dzięki, że mi w tym pomogłeś. Wiesz, myślę, że jesteś równie dobrym kapitanem jak Jack. A może nawet lepszym!";
				link.l1 = "Och, schlebiasz mi. Dziękuję również za porównanie, jak mniemam.";
			}
			link.l1.go = "BM_IronsPinkPotopil3";
		break;
		
		case "BM_IronsPinkPotopil3":
			if (startHeroType == 4) 
			{
				dialog.text = "Wcale nie. Żadnych pochlebstw. Jak zapewne już zauważyłaś, rzadko kogoś tak chwalę. Więc zamknij się i ciesz się, że cię tak wysoko cenię.";
				link.l1 = "Nie powiedziałbym, że podoba mi się, jak to ująłeś, ale cieszę się, że ogólnie uważasz mnie za dobrego kapitana. Ale... łańcuch dowodzenia, Tommy, łańcuch dowodzenia.";
			}
			else
			{
				dialog.text = "Absolutnie nie. Żadnych pochlebstw. Jak pewnie już zauważyłeś, rzadko kogoś tak chwalę. Więc zamknij się i ciesz się, że mam o tobie takie dobre zdanie.";
				link.l1 = "Nie powiedziałbym, że podoba mi się, jak to ująłeś, ale cieszę się, że ogólnie uważasz mnie za dobrego kapitana. Ale... łańcuch dowodzenia, Tommy, łańcuch dowodzenia.";
			}
			link.l1.go = "BM_IronsPinkPotopil4";
		break;
		
		case "BM_IronsPinkPotopil4":
			if (startHeroType == 4) 
			{
				dialog.text = "Och, daj spokój, nudziarzu! Wydaje mi się, że ty i ja jesteśmy już nie tylko kapitanem i jego oficerem, ale prawdziwymi przyjaciółmi. Nie sądzisz?!";
				link.l1 = "Heh. Może. Lepiej być twoim przyjacielem niż wrogiem. A skoro etykieta najwyraźniej nie jest twoją mocną stroną, chyba będę musiała się do tego przyzwyczaić.";
			}
			else
			{
				dialog.text = "Och, daj spokój, nudziarzu! Wydaje mi się, że ty i ja jesteśmy już nie tylko kapitanem i jego oficerem, ale prawdziwymi przyjaciółmi. Nie sądzisz?!";
				link.l1 = "Heh. Może. Lepiej być twoim przyjacielem niż wrogiem. A skoro etykieta najwyraźniej nie jest twoją mocną stroną, chyba będę musiał się do tego przyzwyczaić.";
			}
			link.l1.go = "BM_IronsPinkPotopil5";
		break;
		
		case "BM_IronsPinkPotopil5":
			if (startHeroType == 4) 
			{
				dialog.text = "Mam dla ciebie... prezent, Kapitanie.";
			}
			else
			{
				dialog.text = "Mam dla ciebie... prezent, Kapitanie.";
			}
			link.l1 = "Widzisz to? Czarna plama? Chcesz, żebym i ja został odsunięty, co, Tommy? Chcesz sam być kapitanem? Ha-ha-ha-ha! Myślałem, że mówiłeś, że jesteśmy kumplami.";
			link.l1.go = "BM_IronsPinkPotopil6";
		break;
		
		case "BM_IronsPinkPotopil6":
			dialog.text = "To czarny ZNAK, ty głupku. Wiesz, zaczynam myśleć, że jak tylko wyhaftowałem czaszkę i kości na tej chuście, zaczęło mi to przynosić szczęście. Nie potrafię tego wyjaśnić. Weź to. A także... jeśli chcesz, zawsze możesz pożyczyć mój niezawodny miecz i zbroję... co z niej zostało, ha-ha! Przyda ci się! Zajdziesz daleko. I chcę być tego świadkiem. Nie chcę, żebyś zginął od zbłąkanej kuli.";
			link.l1 = "Dzięki, kumplu! Dam z siebie wszystko. A ty - patrz i podziwiaj, ha-ha-ha!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_PinkPotopil_4");
			GiveItem2Character(PChar, "talisman15");		//Предмет Чёрная Метка
		break;
		
		case "BM_GabeHouseGood1":
			notification("Reputation Check Passed", "None");
			if (startHeroType == 4)
			{
				dialog.text = "Kto wierzy w coś takiego... Przepraszam, panienko. "+TimeGreeting()+". Jak mogę ci pomóc? Wyglądasz na bardzo zaniepokojoną.";
			}
			else
			{
				dialog.text = "Co? Kto przychodzi o tak późnej godzinie? Wyglądasz na dość zaniepokojonego, panie. Czym mogę służyć?";
			}
			link.l1 = "Przepraszam, że zakłócam twój odpoczynek, kapitanie Callow. Mam na imię "+GetFullName(pchar)+", a przybywam w imieniu jednego z twoich starych towarzyszy broni.";
			link.l1.go = "BM_GabeHouseGood2";
		break;
		
		case "BM_GabeHouseGood2":
			dialog.text = "Który towarzysz? Miałem wielu, zarówno w Starym Świecie, jak i w Nowym.";
			link.l1 = "Na początku zamierzałem tylko zostawić coś w jednej z twoich skrzyń. Albo może na stole, żebyś zauważył to szybciej. Chodzi o człowieka z twojej przeszłości. Oto, spójrz i przeczytaj sam.";
			link.l1.go = "BM_GabeHouseGood3";
		break;
		
		case "BM_GabeHouseGood3":
			dialog.text = "Czarna plama? Nie przypominam sobie, aby wśród moich towarzyszy byli piraci. A może niektórzy z chłopaków wpadli w to życie? Czarny jedwab? Naprawdę... Och, Thomas. Jestem zaskoczony, że człowiek taki jak Ty ma do czynienia z tym łajdakiem.";
			link.l1 = "Przepraszam, ale nie tobie nazywać go łajdakiem. Uciekłeś z pola bitwy i zniesławiłeś Toma. Może później żałowałeś i stałeś się wzorowym oficerem tutaj, w Archipelagu, ale to nie zmienia przeszłości.";
			link.l1.go = "BM_GabeHouseGood4";
		break;
		
		case "BM_GabeHouseGood4":
			dialog.text = "Powiedział ci to? Nic dziwnego - zawsze wiedział, jak znaleźć odpowiedniego człowieka, by snuć swoje opowieści. Thomas miał srebrny język. Nie znasz go ani prawdziwej historii, ani w co się pakujesz. Mogę ci powiedzieć - skoro i tak teraz nie zasnę.";
			link.l1 = "Nie zaszkodzi posłuchać. Dalej, kapitanie Callow.";
			link.l1.go = "BM_GabeHouseGood5";
		break;
		
		case "BM_GabeHouseGood5":
			dialog.text = "Więc, Thomas twierdzi, że uciekłem, a potem go oczerniłem? Cóż, powinieneś wiedzieć, że było na odwrót! Kiedy kawaleria króla nadciągała, Tom powiedział, że idzie po posiłki. Więc nie wycofaliśmy się - czekaliśmy. Cała nasza kompania została wybita! Gdybyśmy nie czekali na obiecane przez niego posiłki, moglibyśmy się wycofać i przeżyć! Na końcu, to tylko ja, Frankie i cholerny Thomas przeżyliśmy.";
			link.l1 = "Więc mówisz, że...";
			link.l1.go = "BM_GabeHouseGood6";
		break;
		
		case "BM_GabeHouseGood6":
			dialog.text = "Mówię, że krew naszych chłopców jest na rękach Toma tak samo jak na rękach Royalistów. Ma szczęście, że został skazany na ciężkie roboty, a nie na powieszenie! A teraz ma czelność żywić urazę i wyzwać mnie na pojedynek! Nie jest tego wart!";
			link.l1 = "Więc nie pójdziesz? Zdajesz sobie sprawę, co to oznacza. Prawa honoru są pisane dla wszystkich.";
			link.l1.go = "BM_GabeHouseGood7";
		break;
		
		case "BM_GabeHouseGood7":
			dialog.text = "Oczywiście, że tak. I dlatego pójdę. Musimy dokończyć to, czego nasz republikański sąd nie mógł z powodu dawnych zasług wojskowych Toma. A ty... wydajesz się być przyzwoitym człowiekiem. Radziłbym ci wybierać znajomych mądrzej. Nie mieszaj się z Tomem i jego pokrojem.";
			link.l1 = "Ale Thomas jest teraz moim podwładnym, oficerem na moim statku. "+GetSexPhrase("Będę go miał na oku i nie pozwolę mu się dalej hańbić, jeśli przetrwa spotkanie z tobą.","")+"";
			link.l1.go = "BM_GabeHouseGood_Tommi1";
			link.l2 = "A co byś zrobił na moim miejscu, kapitanie Callow?";
			link.l2.go = "BM_GabeHouseGood_Gabe1";
		break;
		
		case "BM_GabeHouseGood_Tommi1":
			dialog.text = "Eh, jeśli Tom zdołał cię przekonać swoją opowieścią, to nie będzie miał problemu zrobić tego ponownie.";
			link.l1 = ""+GetSexPhrase("Ale zgodnie z prawami honoru, nie mogę go zdradzić. Jestem","Jestem")+" odpowiedzialny za moich ludzi... Nie będę taki jak on. I będę bardziej ostrożny i krytyczny wobec niego od teraz, jeśli przeżyje.";
			link.l1.go = "BM_GabeHouseGood_Tommi2";
		break;
		
		case "BM_GabeHouseGood_Tommi2":
			dialog.text = "To trudna decyzja. Ale nie będę próbował zmieniać twojego zdania. Cóż, żegnaj, "+GetSexPhrase("pan","przegapić")+" - Wciąż muszę się przygotować na spotkanie z Tomem.";
			link.l1 = "Żegnaj, kapitanie Callow.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GoToJamaicaJungle_TommiPlan");
		break;
		
		case "BM_GabeHouseGood_Gabe1":
			dialog.text = "Niech sprawiedliwość zatriumfuje! Pomóż mi pokonać Thomasa, "+pchar.lastname+". To rzadki łajdak i tchórz, ale świetny strzelec - nie będzie łatwo. Ale razem...";
			link.l1 = "Hmm, pomóc ci pokonać Thomasa? Czy w takim pojedynku jest dużo honoru? Możecie to załatwić sami, a ja się nie wtrącę.";
			link.l1.go = "BM_GabeHouseGood_Gabe2";
		break;
		
		case "BM_GabeHouseGood_Gabe2":
			dialog.text = "Znając go, wątpię, że dostanę uczciwy pojedynek. Pozostając neutralnym, tylko popierasz niesprawiedliwość. Czy mam rację?";
			link.l1 = "Wydaje się, że znasz Toma lepiej niż ja i jaki jest naprawdę. Masz rację - już szykuje zasadzkę w Portland Bay i liczy na moją pomoc - tak samo jak ty teraz.";
			link.l1.go = "BM_GabeHouseGood_Gabe3";
		break;
		
		case "BM_GabeHouseGood_Gabe3":
			dialog.text = "W takim razie to nie pojedynek, lecz bójka. Ale nie sugeruję, byśmy sami zabili Thomasa. Aresztujemy go! Przyprowadzę żołnierzy i dokończymy to, czego nie mogliśmy w Starym Świecie. Jeśli znów spróbują go uniewinnić, napiszę do pułkownika albo nawet przywiozę go tutaj na proces. Jeśli Thomas nie złoży broni, to jego własna wina.";
			link.l1 = "To brzmi o wiele lepiej.";
			link.l1.go = "BM_GabeHouseGood_Gabe4";
		break;
		
		case "BM_GabeHouseGood_Gabe4":
			dialog.text = "Cieszę się, że to słyszę, "+pchar.lastname+"! Rozumiem, że podjęcie takiej decyzji może nie być dla ciebie łatwe, ale zapewniam cię, podjąłeś właściwą decyzję. A żeby to zapewnić, pomogę ci w czymś jeszcze.";
			link.l1 = "Co to jest, Kapitanie Callow?";
			link.l1.go = "BM_GabeHouseGood_Gabe5";
		break;
		
		case "BM_GabeHouseGood_Gabe5":
			dialog.text = "Tu, weź to. Nie jako prezent, lecz jako pożyczkę - Thomas, jak mówiłem, to bardzo dobry wojownik i lepiej stawić mu czoła z porządną bronią, a nie zardzewiałym kawałkiem żelaza. Sam pułkownik Doyley dał mi to cudo, ale do prawdziwej walki zawsze wybrałbym miecz szeroki.";
			link.l1 = "Rzeczywiście, to wspaniała rapiera. Dziękuję.";
			link.l1.go = "BM_GabeHouseGood_Gabe6";
			GiveItem2Character(PChar, "blade_40");
		break;
		
		case "BM_GabeHouseGood_Gabe6":
			dialog.text = "Nie dziękuj mi - pożyczam ci to, nie daję w prezencie, pamiętaj? Teraz udaj się do zatoczki i odegraj swoją rolę z naszym drogim Tomem, podczas gdy ja zbieram posiłki. Do zobaczenia tam.";
			link.l1 = "Do zobaczenia tam, Kapitanie Callow.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GoToJamaicaJungle_GabePlan");
		break;
		
		case "BM_GabeHouseNeutral1":
			notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(71))+")", "None");
			if (startHeroType == 4)
			{
				dialog.text = "Kim jesteś, panienko? Musisz mieć zły adres. Ja, uh, nie zamawiałem żadnych usług nocnych.";
				link.l1 = "Helen MacArthur. I trzymaj swoje żądze na wodzy, panie Callow. Jestem przyzwoitą dziewczyną. Nasz klimat sprawia, że czuję się gorąco, nawet w nocy. Czy nie wstydziłeś się powiedzieć tego nieznajomej dziewczynie? Powiedziano mi o tobie jako o wzorowym oficerze.";
				link.l1.go = "BM_GabeHouseNeutral2";
			}
			else
			{
				dialog.text = "Kim jesteś i czego chcesz? Nie podoba mi się twój uśmieszek, panie.";
				link.l1 = ""+GetFullName(pchar)+" A pan nie jest zbyt gościnny, panie Callow.";
				link.l1.go = "BM_GabeHouseNeutral2";
			}
		break;
		
		case "BM_GabeHouseNeutral2":
			dialog.text = "Czy witasz nieznajomych o tej porze inaczej?";
			link.l1 = "Powiedziano mi, że nie ma cię w domu o innych porach.";
			link.l1.go = "BM_GabeHouseNeutral3";
		break;
		
		case "BM_GabeHouseNeutral3":
			dialog.text = "Oczywiście, że nie - mam służbę, obowiązek i uczciwą pracę, słowa, które wydają się tobie nieznane, sądząc po twoim wyglądzie.";
			link.l1 = "Co za pewność siebie! Ale cóż, nie przekonałbyś pułkownika Doyley'a i innych o swojej uczciwości inaczej. Nie potrzebuję niczego od ciebie, Gabe, ale stary znajomy ma. Proszę bardzo.";
			link.l1.go = "BM_GabeHouseNeutral4";
		break;
		
		case "BM_GabeHouseNeutral4":
			dialog.text = "Przekonany? Gabe? Mówię ci! Czarna plama? Więc jesteś piratem? Zaczekaj chwilę... czarny jedwab... czy to może być... Och, rozumiem. Thomas, ty krwawy draniu, wciąż zły na mnie i Franka za to, że cię zgłosiliśmy, ha ha ha ha!";
			link.l1 = "Mówię! Tom jest oficerem na moim statku i zasługuje na szacunek. Jest jednym z najlepszych strzelców Archipelagu.";
			link.l1.go = "BM_GabeHouseNeutral5";
		break;
		
		case "BM_GabeHouseNeutral5":
			dialog.text = "Nie powiedziałem, że źle strzela. Ale widzę, że nie znasz dobrze Thomasa. To on nas wszystkich zdradził. Widzę jednak, że nie ma sensu z tobą dyskutować - jesteście dla siebie stworzeni.";
			link.l1 = "Nie obchodzi mnie to. Zostaw swoje opowieści dla Doyley'a i wszystkich tych naiwnych prostaczków. Jeśli jesteś tak odważny i honorowy, jak mówią, przyjmiesz wyzwanie i przyjdziesz teraz. Więc, przyjmujesz je?";
			link.l1.go = "BM_GabeHouseNeutral6";
		break;
		
		case "BM_GabeHouseNeutral6":
			dialog.text = "Tak, tak. Teraz wynoś się z mojego domu, zanim zawołam strażników.";
			link.l1 = "Będzie to dla mnie przyjemność, Gabe.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GoToJamaicaJungle_TommiPlan");
		break;
		
		case "BM_IronsJamaicaJungle1":
			if (CheckAttribute(pchar, "questTemp.BM_GabePlan"))
			{
				dialog.text = "Czemu jesteś taki nerwowy? Boisz się, czy jak?";
				link.l1 = "Każdy by się zdenerwował, gdyby zobaczył, jak ktoś z muszkietem biegnie w jego stronę - na początku cię nie poznałem. Co tu robisz, Tommy?";
				link.l1.go = "BM_IronsJamaicaJungle_GabePlan_2";
			}
			else
			{
				dialog.text = "Jak poszło? Hej, hej, czemu tak na mnie patrzysz? Przestraszyłeś mnie, hehehe.";
				link.l1 = "Kto kogo straszy! Kto tak ucieka?! Ustaliliśmy, że spotkamy gości w zatoce!";
				link.l1.go = "BM_IronsJamaicaJungle2";
			}
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_2":
			dialog.text = "Heh, cóż, może. Zmęczyło mnie czekanie - na naszych drogich gości i na ciebie. I zdecydowałem, że to miejsce lepiej nadaje się na dobrą zasadzkę. W końcu jestem łowcą, a nie pojedynkowiczem.";
			link.l1 = "Widzę.";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_3";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_3":
			dialog.text = "Tak. Więc, zostawiłeś mój prezent w domu Gabe'a? Trochę ci to zajęło. Byłbym o wiele szybszy, gdybym mógł dostać się do miasta. Co ci się w oczy rzuciło, kapitanie? Co się stało?";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				link.l1 = "(Zaufany) Jestem zdenerwowany. Gabe to tchórz, ale nie jest głupi. Co jeśli zamiast niego przyjdzie cały pluton żołnierzy? Albo podejdą do zatoki i najpierw zatopią nasz statek?";
				link.l1.go = "BM_IronsJamaicaJungle_GabePlan_VD1";
				notification("Trustworthy", "Trustworthy");
			}
			else
			{
				link.l2 = "Gabe mnie zobaczył. Musiałem uciekać.";
				link.l2.go = "BM_IronsJamaicaJungle_GabePlan_4";
				notification("Perk Check Failed", "Trustworthy");
			}
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_VD1":
			dialog.text = "Heh, rozumiem - sam nie jestem całkowicie pewien, czy to zadziała. To pierwszy raz, kiedy coś takiego się wydarzyło dla ciebie, co? W porządku, zdarza się. Mam wszystko przemyślane. Jeśli żołnierze przyjdą bez Gabe'a, po prostu uciekamy. Jeśli przyjdą z Gabe'em, wsadzę mu kulę między oczy, i znów, po prostu uciekamy. A jeśli statek wpłynie do zatoki, uciekamy do Maroon Town - tam nie odważą się iść, a potem zdecydujemy, co robić dalej.";
			link.l1 = "Widzę, że naprawdę o wszystkim pomyślałeś, Tommy.";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_VD2";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_VD2":
			dialog.text = "Oczywiście, że mam. Teraz poczekajmy na naszego gościa...";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_GazgovorTommiAndGabe");
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_4":
			dialog.text = "Ha ha, jesteś równie dobrym złodziejem, jak ja królewcem. Ale czemu nie patrzysz mi w oczy... Kapitanie? Rozmawiałeś z Gabem, prawda?";
			link.l1 = "Nie, o czym ty mówisz? Dlaczego miałbym z nim w ogóle rozmawiać?";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_5";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_5":
			dialog.text = "Bo wszyscy jesteście wielkimi gadułami. Tylko gadacie. Więc, co wam powiedział nasz drogi Gabe?";
			link.l1 = "Czy to ma znaczenie, Tommy?";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_6";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_6":
			dialog.text = "Szczerze mówiąc, nie. Tylko jeśli mnie nie dźgniesz w plecy. Ale wygląda na to, że już to zrobiłeś. Namówił cię, żebyś stanął po jego stronie, prawda?";
			link.l1 = "Nie. Nie do końca. Odłóż broń, Tommy. Obiecuję ci, nic nieodwracalnego nie musi się wydarzyć. Może będziesz pracował w kamieniołomach. Poproszę Gabe'a, by okazał łaskę. Nawet poproszę pułkownika Doyley'a, jeśli będę musiał.";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_7";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_7":
			dialog.text = "Co za dobry Samarytanin z ciebie. Okazujesz miłosierdzie, żebym mógł wypluć płuca po latach w kamieniołomie? Nie wrócę na statki więzienne. Nigdy więcej. A ty... Powinienem był wiedzieć, że jesteś tylko kolejną szczurzą. Coś w twoim wyglądzie. Najpierw się z tobą rozprawię, żeby później Gabe był łatwiejszy.";
			link.l1 = "Nie zostawiasz nam wyboru!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaSTommi");
		break;
		
		case "BM_GabePlan_TommiMertv":
			dialog.text = "Cóż, widzę, że już to zrobiłeś, "+GetSexPhrase("pan","panna")+"I zbierałem drużynę, myśląc, że przewaga liczebna sprawi, że Tom dwa razy się zastanowi i złoży broń.";
			link.l1 = "I nie śpieszyłeś się, kapitanie Callow.";
			link.l1.go = "BM_GabePlan_TommiMertv2";
		break;
		
		case "BM_GabePlan_TommiMertv2":
			dialog.text = "Powiedziałem ci, zbierałem ludzi. Najlepszych z naszego garnizonu. Tom to w końcu weteran. Ale komu ja to mówię? Dobra robota, "+GetSexPhrase("Panie.","Panna")+" "+pchar.lastname+". "+GetSexPhrase("Jestem z ciebie dumny, młody człowieku","Muszę przyznać, że posiadasz równe części piękna, inteligencji i umiejętności, młoda damo")+"  Jak ci mówiłem, gdy się pierwszy raz spotkaliśmy, podjąłeś właściwą decyzję. Teraz sprawiedliwość została wymierzona.";
			link.l1 = "Tak dobrze ci to wyszło. Czujesz dumę?";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict";
			link.l2 = "Cóż, nie jestem weteranem, ale potrafię walczyć, jak mogłeś właśnie zauważyć. Ale dziękuję, panie. Sprawiedliwość nie jest dla mnie pustym słowem.";
			link.l2.go = "BM_GabePlan_TommiMertv_Mir";
		break;
		
		case "BM_GabePlan_TommiMertv_Mir":
			dialog.text = "I to jest godne pochwały, "+GetSexPhrase("młody człowieku","młoda panna")+"Jednakże, pozostała jeszcze jedna rzecz do zrobienia, by zakończyć ten wspaniały dzień.";
			link.l1 = "Hmm, a co to? Tom już został pokonany, w końcu.";
			link.l1.go = "BM_GabePlan_TommiMertv_Mir2";
		break;
		
		case "BM_GabePlan_TommiMertv_Mir2":
			dialog.text = "Masz coś, co należy do mnie. Oddaj mi proszę mój piękny włoski rapier. To nie tylko wykałaczka, ale pamiątka - dar od samego pułkownika Doyley’a.";
			if (!CheckCharacterItem(PChar, "blade_40"))
			{
				link.l1 = "Eh... Rzecz w tym, Kapitanie Callow... rapier zniknął. Zgubiłem go. Przykro mi.";
				link.l1.go = "BM_GabePlan_TommiMertv_Poteryal";			//Потеряли Рапиру
				break;
			}
			if (CheckCharacterItem(PChar, "blade_40"))
			{
				link.l2 = "Ach, oczywiście. Proszę. Nie zamierzałem tego ukraść. Nie będę kłamał - chciałbym to zatrzymać. Ale oto jesteś, Kapitanie Callow.";
				link.l2.go = "BM_GabePlan_TommiMertv_Soglasen";			//Согласен
			}
			if (CheckCharacterItem(PChar, "blade_42"))
			{
				link.l3 = "Mam lepszą ofertę dla ciebie, Kapitanie.";
				link.l3.go = "BM_GabePlan_TommiMertv_Obmen";			//Обмен
			}
			link.l4 = "Ale przecież nazwałeś to wykałaczką. Poza tym, mówiłeś, że nawet nie lubisz rapierów. Ja natomiast zasługuję na nagrodę.";
			link.l4.go = "BM_GabePlan_TommiMertv_Otkaz";				//Отказ
		break;
		
		case "BM_GabePlan_TommiMertv_Soglasen":
			dialog.text = "Każdy chciałby zatrzymać tę piękność! Dziękuję, że mi ją zwróciłeś. Wiele osób na twoim miejscu byłoby uparte.";
			link.l1 = "To twoje. Przypuszczam, że skończyliśmy tutaj?";
			link.l1.go = "BM_GabePlan_TommiMertv_Platok";
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			TakeItemFromCharacter(pchar, "blade_40");
			AddCharacterExpToSkill(pchar, "Leadership", 300);
			ChangeCharacterNationReputation(pchar, ENGLAND, 5);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
		break;
		
		case "BM_GabePlan_TommiMertv_Obmen":
			dialog.text = "Nie jestem zainteresowany. Po prostu oddaj rapier, a rozstaniemy się w dobrej atmosferze, "+GetSexPhrase("Pan.","panna")+" "+pchar.lastname+".";
			link.l1 = "Rozumiem, że ta szpada jest dla ciebie cenna, ponieważ lubisz broń z historią, mam rację? Mam jedną taką samą, a ta jest tą, którą chciałbyś nosić zamiast trzymać w szufladzie.";
			link.l1.go = "BM_GabePlan_TommiMertv_Obmen2";
		break;
		
		case "BM_GabePlan_TommiMertv_Obmen2":
			dialog.text = "Czyżby? Cóż, nie mogę obiecać, że dojdziemy do porozumienia, ale słucham. Rzeczywiście interesują mnie broń z historią. Ale ta rapiera była prezentem od pułkownika. Dlatego jest dla mnie tak cenna.";
			link.l1 = "Wspomniałeś, że lubisz szerokie miecze. Proszę. Należał do naszego drogiego Tommy'ego. Wyobraź sobie, przez co ta broń przeszła przez te lata. I przez co jeszcze przejdzie z tobą.";
			link.l1.go = "BM_GabePlan_TommiMertv_Obmen3";
		break;
		
		case "BM_GabePlan_TommiMertv_Obmen3":
			dialog.text = "Jesteś bardzo przekonujący, młody człowieku! Dzierżąc miecz Thomasa... jakie to ironiczne. No cóż, weź rapier. Nie rozstaję się z nim lekko, pamiętaj.";
			link.l1 = "Cieszę się, że mogliśmy dojść do porozumienia. Myślę, że to pożegnanie, Kapitanie Callow?";
			link.l1.go = "BM_GabePlan_TommiMertv_Platok";
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			TakeItemFromCharacter(pchar, "blade_42");
			AddCharacterExpToSkill(pchar, "Leadership", 250);
			AddCharacterExpToSkill(pchar, "Commerce", 500);
		break;
		
		case "BM_GabePlan_TommiMertv_Poteryal":
			dialog.text = "CO?! Jak mogłeś... Jak mogłeś zgubić cały cholerny rapier?! Jesteś idiotą!";
			link.l1 = "Spokojnie! To tylko rapier. I tak byś go nigdy nie użył. Tom nie żyje - czy to nie jest jedyna rzecz, która się teraz liczy?";
			link.l1.go = "BM_GabePlan_TommiMertv_Poteryal2";
		break;
		
		case "BM_GabePlan_TommiMertv_Poteryal2":
			dialog.text = "Tylko rapier?! To był mój skarb! Prezent od samego pułkownika Doyley'a! Nie obchodzi mnie, że go nie używałem!";
			link.l1 = "W takim razie nie powinieneś był mi tego dawać, prawda?";
			link.l1.go = "BM_GabePlan_TommiMertv_Poteryal3";
		break;
		
		case "BM_GabePlan_TommiMertv_Poteryal3":
			dialog.text = "Powinieneś teraz zamknąć gębę, "+GetSexPhrase("Pan","panna")+" "+pchar.lastname+" Mogliśmy rozejść się w pokoju. Ale teraz... teraz chciałbym dać ci nauczkę, "+GetSexPhrase("młodzieniec","Młoda panna")+".";
			link.l1 = "Cmentarze są pełne nauczycieli takich jak ty.";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaCallowSoloConflict");
			pchar.questTemp.BM_GabeCallow_Rapira = true;
		break;
		
		case "BM_GabePlan_TommiMertv_Otkaz":
			dialog.text = "Oczywiście, że tak. Ale nie możesz po prostu zabrać osobistej broni oficera tylko dlatego, że mu pomogłeś, prawda?";
			link.l1 = "Zgodziłbym się, ale i tak tego nie używasz. Po prostu będzie wisiało na gwoździu w twoim pokoju. A u mnie znajdzie godne zastosowanie. Pułkownik Doyley nie będzie sprawdzał, czy go nie zgubiłeś, prawda?";
			link.l1.go = "BM_GabePlan_TommiMertv_Otkaz2";
		break;
		
		case "BM_GabePlan_TommiMertv_Otkaz2":
			dialog.text = "To nie podlega dyskusji, młody człowieku. Mówiłem ci od początku, to nie jest prezent. Oddaj mi rapier. Natychmiast.";
			link.l1 = ""+GetSexPhrase("Nie jestem jednym z twoich żołnierzyków","Nie jestem jedną z twoich portowych dziwek")+", by przyjmować od ciebie rozkazy. Jestem kapitanem statku, tak jak ty. Rapier zostaje ze mną, czy ci się to podoba, czy nie.";
			link.l1.go = "BM_GabePlan_TommiMertv_Otkaz3";
		break;
		
		case "BM_GabePlan_TommiMertv_Otkaz3":
			dialog.text = "Wygląda na to, że Thomas wywarł na ciebie spory wpływ. To umieraj za to, jeśli tak bardzo tego pragniesz.";
			link.l1 = "Dokładnie tak myślałem!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaCallowSoloConflict");
			pchar.questTemp.BM_GabeCallow_Rapira = true;
		break;
		
		case "BM_GabePlan_TommiMertv_Platok":
			dialog.text = "Proszę, weź to. Wcale tego nie potrzebuję. To będzie twoja pamiątka z tego dnia. Spróbuj być teraz trochę mniej łatwowierny. I nie pozwól żadnym łajdakom, takim jak Thomas, wciągać cię w ich brudne interesy.";
			link.l1 = "Cóż, dajesz mi czarną plamę, Kapitanie Callow?";
			link.l1.go = "BM_GabePlan_TommiMertv_Platok2";
			GiveItem2Character(PChar, "talisman15");		//Предмет Чёрная Метка
		break;
		
		case "BM_GabePlan_TommiMertv_Platok2":
			dialog.text = "„Cóż, żaden z nas nie jest piratem, prawda, ”"+pchar.name+"? Niech to będzie przypomnienie. Zajmij się sobą, Archipelag potrzebuje takich ludzi jak ty. "+GetSexPhrase("Może zasugerowałbym dołączenie do marynarki i napisanie rekomendacji dla pułkownika Doyley'a...","")+"";
			link.l1 = "Żałuję, że nie mogę przyjąć twojej oferty, Kapitanie.";
			if (startHeroType == 3)
			{
				link.l1 = "Hm. Zastanowię się nad tym. Naprawdę dobrze.";
			}
			if (startHeroType == 4)
			{
				link.l1 = "Żegnaj, panie.";
				link.l1.go = "exit";
				AddDialogExitQuest("BM_GabePlan_CallowDruzhba");
				break;
			}
			link.l1.go = "BM_GabePlan_TommiMertv_Platok3";
		break;
		
		case "BM_GabePlan_TommiMertv_Platok3":
			dialog.text = "Jak sobie życzysz. No cóż, żegnaj, "+GetSexPhrase("Panie.","przegapić")+" "+pchar.lastname+". Zasługujesz na to, by nosić to, co pozostało z Ironsides. Żegnaj.";
			link.l1 = "Żegnaj, panie.";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_CallowDruzhba");
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict":
			dialog.text = "Nie podoba mi się twój ton, "+GetSexPhrase("pan","panna")+" . O co ci chodzi?";
			link.l1 = "Celowo zwlekałeś, zbierając swoich 'najlepszych ludzi'. Po co? By schwytać jednego człowieka? Powinieneś był zgarnąć kilku żołnierzy patrolujących miasto i natychmiast przyjść mi z pomocą!";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict2";
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict2":
			dialog.text = "Przyprowadzasz mięso armatnie?! Tom nie był tylko strażnikiem miejskim jak oni. Miał zupełnie inne szkolenie i doświadczenie - jest przeklętym Pancernikiem, tak jak ja! Jak możesz tego nie zauważać?";
			link.l1 = "O, wręcz przeciwnie, zdaję sobie z tego sprawę. Dlatego my tutaj jesteśmy - aby skrzyżować szable z Tomem, pozwalając chłopakom schwytać go żywcem. Poza tym, ty też jesteś Ironclad. Nawet ta sama kompania. Czyżbyś tak bardzo bał się walczyć z nim osobiście?";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict3";
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict3":
			dialog.text = "Jak śmiesz oskarżać mnie o tchórzostwo, młody "+GetSexPhrase("mężczyzna","chybić")+"Zapytaj kogokolwiek, a opowiedzą ci szczegółowo, jakie wyczyny dokonałem dla tego miasta.";
			link.l1 = "Jeszcze nie skończyłem. Zaczynam się zastanawiać, czy te ‘wyczyny' były dokonane własnymi rękami. Chciałeś, żebyśmy z Tomem się pozabijali, abyś mógł zgarnąć całą chwałę. Już to wcześniej robiłeś, prawda?";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict4";
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict4":
			dialog.text = "Mam dość twoich oskarżeń, "+GetSexPhrase("Monsieur.","Panna")+" "+pchar.lastname+"Chcesz konfliktu? To go dostaniesz. Natychmiast.";
			link.l1 = "Prawda boli, prawda, Gabe?";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaCallowSoloConflict");
			pchar.questTemp.BM_GabeCallow_Conflict = true;
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_1":
			dialog.text = "";
			link.l1 = "Gabe! Minęło tyle czasu, tyle ponurych zim! A patrz na ciebie - wciąż masz ten sam zadowolony wyraz twarzy, do diabła z tobą!";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_2";
			CharacterTurnByChr(npchar, characterFromID("Irons"));
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_2":
			dialog.text = "Thomasie! Powinienem być zadowolony, gdyż dziś wreszcie własnymi rękoma zakończę to, czego nasz system sprawiedliwości nie zdołał zrobić przez lata. A że jestem w dobrym nastroju, pozwalam ci złożyć broń i podążyć za nami. Możesz nawet zostać odesłany do ciężkich robót. W takim razie osobiście cię tam zabiorę.";
			link.l1 = "Heh, spróbuj mnie powstrzymać! Myślisz, że kilku facetów obok ciebie mnie zatrzyma!!!";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_3";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_3":
			dialog.text = "Kto mówi, że to tylko oni są ze mną? Mówię o osobie stojącej teraz obok ciebie.";
			link.l1 = "Co?";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_4";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_4":
			dialog.text = "Thomas, Thomas, Thomas... jesteś, jak zawsze, sam na tym świecie. Prawie mi cię żal!";
			link.l1 = "Krwiste szczury! Dranie!";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_5";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_5":
			StartInstantDialog("Irons", "BM_GabePlan_GazgovorTommiAndGabe_6", "Quest\BlackMark.c");
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_6":
			dialog.text = "Co to znaczy?! Co miał na myśli?!";
			link.l1 = "Tommy, słuchaj...";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_7";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_7":
			dialog.text = "To właśnie robię! Powiedz mi, że on kłamie!";
			link.l1 = "Niestety, ma rację. Odłóżcie broń. I nikt nie musi dziś umierać. Osobiście wstawię się za wami, abyście nie zostali powieszeni. Może nawet pewnego dnia wrócicie do uczciwego życia.";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_8";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_8":
			dialog.text = "To nie tobie decydować! I na pewno nie tobie! Kto potrzebuje wrogów z takim dowódcą! Kolejna cholera szczur.";
			link.l1 = "Pewnie, Tommy. Dla takich jak ty nie ma czystych ucieczek.";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_9";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_9":
			dialog.text = " Miejsce w twojej załodze, na twoim statku byłoby początkiem, gdybyś tylko był gotów stanąć w obronie swoich ludzi! Ale to już nie ma znaczenia. Do diabła z tobą, z wami wszystkimi! Wypatroszę wasze tchórzliwe flaki, ty mały szczurze. A ciebie, Gabe, spróbuję zabrać ze sobą...";
			link.l1 = "Czekaj, Tommy, nie!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_GazgovorTommiAndGabe_Fight");
		break;
		
		case "BM_GabePlan_GabeWin_1":
			dialog.text = "Gratulacje, "+GetSexPhrase("młodzieniec","młoda panna")+"! Jestem pod wrażeniem, że udało ci się sprawić, by Thomas poczuł, że wszystko szło zgodnie z jego planem - miał nosa do zdrady.";
			link.l1 = "Ach, dziękuję, oczywiście, Kapitanie Callow.";
			link.l1.go = "BM_GabePlan_GabeWin_2";
		break;
		
		case "BM_GabePlan_GabeWin_2":
			dialog.text = "Czy coś cię trapi, "+GetSexPhrase("Pan.","pani")+" "+pchar.lastname+"?";
			link.l1 = "Tom...  nie był po prostu wściekły, że stanąłem po twojej stronie. W jego głosie była prawdziwa rozpacz i niezrozumienie, jakby...";
			link.l1.go = "BM_GabePlan_GabeWin_3";
		break;
		
		case "BM_GabePlan_GabeWin_3":
			dialog.text = "...jakby to on był tu poszkodowany. Można było tego oczekiwać. Pamiętaj, Charles, potwór może odczuwać ból. Ale to nie przestaje być potworem. Wielu przestępców jest często szczerze przekonanych o swojej słuszności i niewinności.";
			link.l1 = "Spróbuję to zapamiętać. Myślę, że skończyliśmy tutaj, czyż nie, Kapitanie?";
			link.l1.go = "BM_GabePlan_GabeWin_4";
		break;
		
		case "BM_GabePlan_GabeWin_4":
			dialog.text = "Ogólnie rzecz biorąc, tak, ale jest jeszcze jedna rzecz do zrobienia, by zakończyć ten wspaniały dzień.";
			link.l1 = "O? Co to jest?";
			link.l1.go = "BM_GabePlan_TommiMertv_Mir2";
		break;
		
		case "BM_IronsJamaicaJungle2":
			dialog.text = "Zajęło ci to wystarczająco długo. Więc pomyślałem, że zrobię mały rekonesans. W każdym razie, myślę, że lepiej będzie zrobić na nich zasadzkę tutaj, zamiast udawać wytwornych szermierzy na plaży. Mam nadzieję, że udało ci się znaleźć dom Gabe'a i zostawić wszystko na widoku?";
			link.l1 = "Oczywiście, że to zrobiłem, za kogo mnie masz, za idiotę? W rzeczywistości jestem twoim kapitanem, Tommy. Co by to z ciebie zrobiło, gdybyś służył idiocie?";
			link.l1.go = "BM_IronsJamaicaJungle3";
		break;
		
		case "BM_IronsJamaicaJungle3":
			dialog.text = "Ha-ha-ha-ha, nie uwierzyłbyś, jak często musiałem radzić sobie z takim gównem na służbie! Ale w naszym przypadku, na szczęście, tak nie jest. Dobra, więc. Oczekujemy towarzystwa. Gotowy?";
			link.l1 = "Cóż, chyba że cała flota lub garnizon Port Royal tu się pojawi, jestem gotowy.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_CreateGabeInJungle");
		break;
		
		case "BM_GabeJungle1":
			dialog.text = "Thomas? To naprawdę ty po wszystkim...";
			link.l1 = "Oczywiście, że to naprawdę ja, czy spodziewałeś się kogoś innego, Gabe? Heh, wyglądasz blado, jakbyś zobaczył ducha. Jesteś też grubszy niż byłeś w Starej Anglii.";
			link.l1.go = "BM_GabeJungle2";
			CharacterTurnByChr(npchar, characterFromID("Irons"));
		break;
		
		case "BM_GabeJungle2":
			dialog.text = "Teraz w końcu jestem przekonany, że to naprawdę ty. Opryskliwy jak zawsze. Ale nic nie szkodzi, wkrótce zamknę na dobre twoją plugawą gębę, draniu.";
			link.l1 = "Ha-ha-ha, teraz to rozmawiamy! Wiesz, Gabe, naprawdę mnie zawiodłeś. Znowu! Wyraźnie potrzebowałeś zabrać ze sobą więcej ludzi, by poradzić sobie nawet tylko ze mną. A przecież jest nas dwóch! Czy to wszystko, na co mogli ci pozwolić, tchórzu?";
			link.l1.go = "BM_GabeJungle3";
		break;
		
		case "BM_GabeJungle3":
			dialog.text = "Dosyć! Nie widzę sensu, byśmy dłużej rozmawiali.";
			link.l1 = "Zgadzam się z tobą co do tego! "+pchar.name+"! Do boju, Kapitanie!";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GabeJungleFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "BM_IronsJamaicaJungle4":
			dialog.text = "Heh, masz to! Spoczywaj w pokoju, ty draniu.";
			link.l1 = "Cóż, jesteś zadowolony, Tommy? Wiesz, wielu ludziom tylko się pogarsza po tym, jak się zemszczą.";
			link.l1.go = "BM_IronsJamaicaJungle5";
		break;
		
		case "BM_IronsJamaicaJungle5":
			dialog.text = "Ha, przeczytałeś to gdzieś? Nigdy nie rozumiałem takich mięczaków. Phi! Czy jestem zadowolony? Jestem tak szczęśliwy, że zaraz się zsikam! Ci dranie byli źródłem moich największych nieszczęść!";
			link.l1 = "Cieszę się dla ciebie. Czy nie ma nikogo innego, na kim musisz się zemścić? Czy mam się spodziewać kolejnych żartów o papierowych nabojach od ciebie?";
			link.l1.go = "BM_IronsJamaicaJungle6";
		break;
		
		case "BM_IronsJamaicaJungle6":
			dialog.text = "Spokojnie, Gabe był ostatni. A co do żartów - nie martw się, nie będzie ich więcej, przynajmniej jeśli chodzi o ciebie.";
			link.l1 = "Czy zatem wracamy na statek?";
			link.l1.go = "BM_IronsJamaicaJungle7";
		break;
		
		case "BM_IronsJamaicaJungle7":
			dialog.text = "Wracalibyśmy na nią tak czy inaczej, niezależnie od tego, czy mam jeszcze kogoś, na kim chcę się zemścić, czy nie. Zaraz, jednak...";
			link.l1 = "O, więc to jeszcze nie koniec...";
			link.l1.go = "BM_IronsJamaicaJungle8";
		break;
		
		case "BM_IronsJamaicaJungle8":
			dialog.text = "Tak, tak. Jest coś, co chcę ci powiedzieć. To coś, co mówię bardzo niewielu osobom. I nie powiem tego ponownie. Jeśli się ze mnie śmiejesz, bardzo się na ciebie wkurzę.";
			link.l1 = "Obiecuję, że się nie zaśmieję. Tak czy owak, uważam, że twoje dowcipy są bardziej napięte niż zabawne.";
			link.l1.go = "BM_IronsJamaicaJungle9";
		break;
		
		case "BM_IronsJamaicaJungle9":
			dialog.text = "Dobrze. Więc. Jestem bardzo wdzięczny, że zdecydowałeś się mi pomóc zamiast robić to, co zrobił Jack. Jesteś prawdziwym przyjacielem, Kapitanie. Dziękuję. A także... jeśli chcesz, możesz pożyczyć mój zaufany miecz i moją zbroję... To, co z niej zostało, ha-ha!";
			link.l1 = "Cóż, dziękuję za te słowa. Nie codziennie słyszy się coś takiego od swoich oficerów. No dalej, kumplu.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_FinalInJungleWithTommy");
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Irons_officer":
			dialog.text = "Ajaj, Kapitanie?";
			if (startHeroType == 4 && CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				dialog.text = "Więc, Rumba, na czyich kościach zatańczymy tej nocy?";
			}
			if (startHeroType == 4 && !CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				dialog.text = "Tak, Ellie?";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Zamieniam się w słuch, kapitanie.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = ""+pchar.name+"?";
			}
			//////
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal") && !CheckAttribute(pchar, "questTemp.BM_TommiTieyasalOtkaz"))
			{
				Link.l4 = "Tommy, chciałbym cię zapytać o coś bardzo poważnego. Jest jeden... kamienny idol Czerwonoskórych. I będę potrzebował pomocy. Mogę poprosić o to tylko najbliższych przyjaciół, takich jak ty. Nowicjusze lub ci, którym jeszcze za bardzo nie ufam, nie nadają się.";
				Link.l4.go = "tieyasal_1";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Tommy, przestań liczyć mewy. Czy zliczyłeś już cały ładunek? Daj mi pełen raport z prognozą.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Tommy, od dzisiaj potrzebuję, abyś kupował pewne towary w portach.";
				Link.l12.go = "QMASTER_2";
				
				if (startHeroType == 4)
				{
					Link.l11 = "Tommy, czy mógłbyś zgłosić wszystko na statku?";
					Link.l12 = "Tommy, robię się dość zmęczony. Czy mógłbyś zaopatrzyć się w pewne towary w każdym porcie?";
				}
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					Link.l11 = "Przygotuj mi raport o stanie statku i wszystkiego na nim, Tommy.";
					Link.l12 = "Czy mógłbyś uzupełnić zapasy pewnych towarów podczas naszych postojów w porcie?";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					Link.l11 = "Policz wszystko, co mam na statku, i zrelacjonuj jego ogólny stan.";
					Link.l12 = "Potrzebuję, abyś kupił te towary podczas naszych postojów w każdym porcie.";
				}
			}
			//////
			Link.l1 = "Słuchaj uważnie mojego rozkazu!";
			if (startHeroType == 4 && CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				Link.l1 = "Ktoś na pewno. Ale na razie, słuchaj moich rozkazów.";
			}
			if (startHeroType == 4 && !CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				Link.l1 = "Słuchaj mojego rozkazu... Tommy. ";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l1 = "To dobrze, bo mam dla ciebie nowe zlecenie, Tommy.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l1 = "Słuchaj mojego rozkazu, Tom.";
			}
			Link.l1.go = "stay_follow";
			//////
			link.l2 = "Nic, Tommy. Spocznij.";
			if (startHeroType == 4 && CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				link.l2 = "Zobaczymy, jak to pójdzie, Tommy.";
			}
			if (startHeroType == 4 && !CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				link.l2 = "Nie, Tom, nic.";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l2 = "Nie, nic.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l2 = "Wszystko w porządku.";
			}
			link.l2.go = "exit";
			NextDiag.TempNode = "Irons_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Jeszcze nawet nie zacząłem inwentaryzacji. Powinieneś być wdzięczny, że w ogóle liczę nasze zyski i straty, nie mówiąc już o targowaniu się z tymi chciwymi kupcami. Inwentaryzacja to nie moja sprawa, nigdy tego nie robiłem w armii i nie zamierzam zaczynać teraz.";
			Link.l1 = "To nie wojsko, Tommy. Ale dobrze, rozumiem, nie będę cię zmuszać.";
			if (startHeroType == 4)
			{
				dialog.Text = "Nie jestem skrybą, Ellie. Kiedyś znałem faceta, Daniela Crimsona, który zawsze twierdził, że jest skrybą, ale ledwie widział pole bitwy. Jednak w walce był bestią. To nie ja, jednak, i nie będę o tym kłamał. Inwentarz to nie moja działka. Już prowadzę nasze księgi dla ciebie. Nie naciskaj.";
				Link.l1 = "Dobrze, Tommy, nie zrobię tego.";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Słuchaj, nie jestem skrybą. Nikt nigdy nie wymagał tego od zwykłych żołnierzy jak ja, nawet w armii. Nie zmieniajmy tej zasady.";
				Link.l1 = "Nie, nie róbmy tego.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Jedyną rzeczą, którą mogę policzyć, jest ile naszych wrogów zastrzeliłem, ha-ha-ha. A nawet wtedy stracę rachubę. Jestem prostym żołnierzem, wiesz. Kto do diabła wie coś o statku - przez większość życia byłem szczurem lądowym.";
				Link.l1 = "Wygląda na to, że będę musiał zrobić to sam.";
			}
			Link.l1.go = "exit";
		break;

		case "QMASTER_2":
			dialog.text = "Za kogo mnie masz, za jakiegoś podrzędnego kwatermistrza? Mieliśmy tylko pogardę dla tych miękiszów tchórzy w ojczyźnie. Może nie jestem szlachcicem, ale wciąż mam swoją dumę.";
			link.l1 = "Dobrze, dobrze, jeśli nie chcesz, to nie chcesz.";
			link.l1.go = "exit";
			if (startHeroType == 4)
			{
				dialog.Text = "Słuchaj, byłem prostym, uczciwym żołnierzem, nie kwatermistrzem, moja dziewczyno. Nie wiem o tym zbyt wiele i nie chcę zaczynać się uczyć. To jakby prosić cię o złożenie i rozłożenie muszkietu na czas.";
				Link.l1 = "Cóż, mógłbym z pamięci wymienić każdą część stałego i ruchomego takielunku na tym statku. Ale jak sobie życzysz, Tom. Sprawa zamknięta.";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Nie, nie mogłem. Może zapomniałeś albo wcale tego nie wiesz, więc wyjaśnię. Dla ciebie to byłoby rutynowe zadanie, ale w naszej armii nie traktujemy zaopatrzenia i służb tylnych zbyt dobrze. Proszę, nie licz mnie wśród nich.";
				Link.l1 = "Ha-ha, dobrze, dobrze.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Patrz, rzecz jasna, mam do ciebie szacunek, ale nie zamierzam się przestawiać i robić coś, czego nie potrafię i nie mogę znieść. Ledwo nauczyłem się wtedy liczyć, a ty chcesz, żebym był prawdziwym dostawcą. A tak przy okazji, nie podobały nam się - oszczędzają na amunicji, wodzie, jedzeniu i jego świeżości.";
				Link.l1 = "Hm, dobrze, zapomnijmy o tym.";
			}
		break;
		
		case "stay_follow":
            dialog.Text = ""+GetSexPhrase("O, rozkaz, co? Lubisz musztrę i te wszystkie wojskowe sprawy, prawda? Wolałbym, żebyś po prostu powiedział mi, co trzeba zrobić.","Jesteś jak sierżant czy coś. To do ciebie nie pasuje - jesteś zbyt piękna na to. Nie przeżyłabyś dnia w armii. Ale słucham.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Najwyraźniej naprawdę jesteś wielkim fanem mundurów, musztry i tego wszystkiego. Ale dobrze, mów dalej.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Który?";
			}
			
            Link.l1 = ""+GetSexPhrase("Nie idź nigdzie i nic nie rób - tylko obserwuj, rozumiesz? Znam cię.","Zostań dokładnie tam, gdzie jesteś, rozumiesz mnie?")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l1 = "Stój tu, nigdzie nie idź i niczego nie dotykaj.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l1 = "Zostań tu i nie wpuszczaj nikogo.";
			}
			Link.l1.go = "Boal_Stay";
            Link.l2 = ""+GetSexPhrase("Chodź za mną i nie daj się rozproszyć niczemu - włącznie z błąkającymi się żonami czy nagle pojawiającymi się dawnymi towarzyszami broni.","Trzymaj się blisko, dobrze? Chciałbym mieć osłonięte plecy.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l2 = "Podążaj za mną. Widzę, że jesteś pogrążony w myślach.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l2 = "Chodź za mną, inaczej zatrzymałeś się z jakiegoś powodu.";
			}
			Link.l2.go = "Boal_Follow";
			
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Potrzebuję, żebyś tym razem strzelił w coś innego.";
					Link.l3.go = "SetGunBullets";
					if (pchar.sex == "man" && pchar.rank >= 15)
					{
						Link.l3 = "Potrzebuję, abyś użył innej amunicji w nadchodzącej walce.";
					}
					if (pchar.sex == "man" && pchar.rank >= 25)
					{
						Link.l3 = "Będziesz używał innej amunicji w następnej bitwie.";
					}
				}	
			}
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l4 = "Zmień rodzaj amunicji do swojejo muszkietu.";
					Link.l4.go = "SetMusketBullets";
				}
				Link.l5 = "Zmień swoją priorytetową broń do walki.";
				Link.l5.go = "SetPriorityMode";
				Link.l6 = "Chciałbym, abyś utrzymał pewien dystans między sobą a swoimi wrogami.";
				Link.l6.go = "TargetDistance";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					Link.l6 = "Chciałbym, abyś trzymał pewien dystans od wroga, Tommy.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					Link.l6 = "Zachowaj pewną odległość między sobą a wrogiem, Tommy.";
				}
			}
		break;
		
		case "SetGunBullets":
			Dialog.Text = ""+GetSexPhrase("Jakiego rodzaju pociski? Mam nadzieję, że starannie wykonałeś każdy z nich, bo kto wie, gdzie wylądują, hehe.","Zastrzelę dla ciebie cokolwiek. Cokolwiek to jest, ale nigdy ślepakami, hehe. ")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Przeczuwam, że coś ciekawego się szykuje! Dobrze, jaki rodzaj?";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Znów walka... Dobrze, jaki rodzaj?";
			}
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
				Link.(attrL).go = "SetGunBullets1_" + i;
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
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetMusketBullets");
			DialogExit();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "Na początku walki będziesz używać:";
			Link.l1 = "Ostrza";
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
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = ""+GetSexPhrase("Nawet jeśli tam oberwiesz, hehe? Zrozumiałem, po prostu będę obserwować.","Próbujesz mnie zamienić w strażnika? A co jeśli zostaniesz pobity czy coś?")+"";
            Link.l1 = ""+GetSexPhrase("Hej, uważaj! Coś wymyślimy, jeśli do tego dojdzie.","Cóż, nie zamierzasz tylko patrzeć, prawda? Jeśli uważasz, że twój kapitan jest tak wspaniały, jak mówisz, zrobisz coś z tym.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Nawet w łeb? Dobrze, dobrze, nie patrz na mnie tak, rozumiem.";
				Link.l1 = "Mam nadzieję.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Nie bój się, nikt nie przejdzie.";
				Link.l1 = "Jeśli nikogo nie brakuje, oczywiście. Ale dobrze.";
			}
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = ""+GetSexPhrase("Bardzo śmieszne. Ale rozumiem, o co ci chodzi.","Oj, nie martw się, twoje plecy są zawsze pod moim czujnym okiem, hehe.")+"";
            Link.l1 = ""+GetSexPhrase("Dobrze.","Boże, jesteś nieznośny, Tom.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Cóż, próbuję sobie przypomnieć coś bardzo ważnego. A potem uświadamiam sobie, że nawet nie wiem, co to jest, ponieważ wtedy straciłem pamięć, więc nic z tego nie wyjdzie. Dobra, chodźmy.";
				Link.l1 = "Sprytny, muszę przyznać.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Wszak stoję tu, boś sam mi rozkazał wcześniej. Już idę, już idę.";
				Link.l1 = "Hm-m, dobrze, dobrze.";
			}
            Link.l1.go = "Exit";
        break;
		
		//--> задать дистанцию стрельбы
		case "TargetDistance":
			dialog.text = ""+GetSexPhrase("Jaka odległość? Pamiętaj, że poza dwudziestoma jardami nie będę w stanie celować dokładnie. Chyba że, oczywiście, nie potrzebujesz, żebym w cokolwiek trafił, hehe.","Jakbym chciała zbliżyć się do śmierdzących mężczyzn po przebywaniu w twoim towarzystwie. Więc, jaka to odległość? Ale pamiętaj, nie mogę naprawdę celować dalej niż na dwadzieścia jardów. Nikt nie może.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Dobrze, jaka odległość? Ale przypomnę ci, że nie będę w stanie celnie i powoli strzelać na odległość większą niż dwadzieścia metrów w ferworze bitwy.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Dobrze. Co? Pamiętaj, że dalej niż... cóż, nie jesteśmy już mali, ty i ja o tym wiemy.";
			}
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";
		break;
		
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = ""+GetSexPhrase("Nie powinieneś próbować humoru.","Jeszcze wiele musisz się ode mnie nauczyć o humorze, dziewczyno. Ale robisz postępy!")+"";
				link.l1 = ""+GetSexPhrase("That's odd; I've always been told the opposite.","Very funny, Tommy.")+"";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					dialog.text = "Nie najgorszy z twoich dowcipów. Może pewnego dnia przestaniesz być zrzędą, heh-heh.";
					Link.l1 = "Och cóż.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					dialog.text = "Ha-ha-ha, dobry żart.";
					Link.l1 = "Właściwie to ja po prostu... dobrze.";
				}
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Cóż, wtedy po prostu będę stać nieruchomo i trzymać swoją pozycję. Jeśli walczysz zbyt daleko, to twój tyłek jest na linii, hehe.";
				link.l1 = "Don't be sarcastic; holding your ground is exactly what I want you to do from now.";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					dialog.text = "Heh, mogłeś mi po prostu powiedzieć, żebym trzymał linię, a nie mówić o odległościach i liczbach.";
					Link.l1 = "Cóż, najważniejsze, że mnie zrozumiałeś.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					dialog.text = "Zrozumiałem, będę trzymał linię tutaj. Potem przyprowadź ich bliżej mnie, abym mógł strzelać.";
					Link.l1 = "Pewnie.";
				}
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "Słuchaj, wiem, że chciałbyś, aby każdy mój strzał był jak ten w latarni, ale to się nie zdarzy. Tam była dobra pozycja. Spokojnie i stabilnie. Nie da się tego powtórzyć w ogniu bitwy.";
				link.l1 = "Hmm. W takim razie trzymaj się na odległość dwudziestu jardów.";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					dialog.text = "Wiem, że ci się to podoba, wszyscy chłopcy by to chcieli, ale jak wtedy, przy latarni morskiej, to już nie zadziała. Będę potrzebować dobrego punktu, i żeby nikt mnie nie dorwał, inaczej moje nerwy puszczą.";
					Link.l1 = "Hm-m, dobrze.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					dialog.text = "Z pewnością doszlifowałem swoje umiejętności od tamtej pory, ale niemożliwe pozostanie niemożliwym - w ogniu bitwy nigdy nie mógłbym powtórzyć tego strzału z latarni. Nawet z rusznicą na koło.";
					Link.l1 = "I niemożliwe jest możliwe, Tommy. Ale dobrze, nie znaczy nie.";
				}
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = RandPhraseSimple("Bardzo dobrze. Utrzymam dokładnie tę odległość, ale jeśli będziemy walczyć wewnątrz tawerny lub jaskini, wyjdę na zewnątrz, aby ją zachować, hehe.","Spróbuję. Ale pokłady i ciasne przestrzenie mogą narzucać własne warunki.");
			link.l1 = ""+GetSexPhrase("To nie jest śmieszne, Tommy. Zachowuj się stosownie do sytuacji, ale bez dowcipów czy twoich głupich psikusów.","Wiem o tym, Thomas, nie jestem głupi.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "Spróbuję zapamiętać.";
				Link.l1 = "Okay, liczę na ciebie.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "Tak, kapitanie.";
				Link.l1 = "Spocznij, Tommy.";
			}
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;
		//<-- задать дистанцию стрельбы
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal_1":
			dialog.text = "Pomóc z czym, ukraść to? Ale po co? Jestem pochlebiony, oczywiście, ale mogłeś to powiedzieć już dawno temu. Śmiało, wyrzuć to z siebie.";
			link.l1 = "Pilnuj języka, co? Cóż, do diabła - nie obchodzi mnie, jak się wyrażasz, dopóki jesteś po mojej stronie. Więc, ten idol. Dzięki niemu możesz... magicznie przenieść się w inne miejsce. Nie patrz na mnie tak - wiem, jak to brzmi. Ale już przez to przeszedłem i widziałem wszystko na własne oczy. To... bezpieczne, jeśli wypijesz jeden eliksir.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "Widzę, że już kilka drinków za tobą. Chociaż nie, wydajesz się trzeźwy. A to o mnie mówią, że zawsze plotę bzdury...";
			link.l1 = "Idziesz ze mną czy nie? Idol ma nas zabrać do starożytnego miasta Majów, a kto wie, co tam na nas czeka? Jesteś jednym z tych, na których wierzę, że mogę polegać w trudnej chwili. A teraz właśnie nadeszła taka chwila.";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			dialog.text = "Mam złe przeczucia co do tego wszystkiego. Gdybyś nie był moim kapitanem, powiedziałbym, że należysz do domu wariatów. Następnym razem powiesz mi, że Bóg istnieje.";
			link.l1 = "Robi to, Tommy. I, ku mojemu zaskoczeniu odkryłem na tym Archipelagu, nie tylko nasz. Sam mogłeś zobaczyć wszystkie diabelstwa, które się tu dzieją. I pewnie zauważyłeś wpływ błogosławionych lub przeklętych drobiazgów.";
			link.l1.go = "tieyasal_4";
		break;
		
		case "tieyasal_4":
			dialog.text = "Diabły także istnieją w domu. I zawsze miały normalne wytłumaczenie. Przykro mi, kapitanie, ale nie będę tańczyć wokół kamiennych bożków z tobą. Strzelać do wrogów - proszę bardzo. Mogłem stracić pamięć, ale nie straciłem rozumu. Przynajmniej tak myślę.";
			link.l1 = "Cóż, nie mogę cię zmusić. Więc... jak sobie życzysz, Tommy.";
			link.l1.go = "tieyasal_5";
			link.l2 = "Wątpię, że będziesz miał jaja, żeby do nich strzelić, śmiałku, skoro boisz się podejść do idola.";
			link.l2.go = "tieyasal_6";
		break;
		
		case "tieyasal_5":
			dialog.text = "Och no cóż, nie dąsaj się. Dobrze, jeśli wrócisz po tańcach wokół tego bożka, to następnym razem o tym pomyślę.";
			link.l1 = "Może nie być następnego razu. Wracaj na statek, Tom.";
			link.l1.go = "exit";
			pchar.questTemp.BM_TommiTieyasalOtkaz = true;
		break;
		
		case "tieyasal_6":
			dialog.text = "Nie boję się, nie zrozum mnie źle. Ale jestem przyzwyczajony do słuchania mojego przeczucia, nigdy mnie nie zawiodło przez te lata. A teraz mówi mi, że nic dobrego z tego nie wyniknie. I tak czy inaczej... No cóż, obrażasz się.";
			link.l1 = "Śmiało, powiedz mi.";
			link.l1.go = "tieyasal_7";
		break;
		
		case "tieyasal_7":
			dialog.text = "Skoro tak, to w porządku! Zgodziłem się walczyć ramię w ramię z tobą. Ale co jeśli, wyobraźmy sobie, ta rzecz naprawdę działa? Co jeśli jest przeklęta? Nie zamierzam umierać za nikogo, przepraszam.";
			link.l1 = "Teraz się wykazałeś, Tommy. Teraz potrzebowałem najbardziej lojalnych ludzi. I teraz widzę, że nie jesteś jednym z nich. Idę tam. A ty... rób, co chcesz.";
			link.l1.go = "tieyasal_8";
		break;
		
		case "tieyasal_8":
			dialog.text = "Spójrz na niego. Jest przecież obrażony.";
			link.l1 = "Zamknij gębę. Jeśli uważasz nas za tak odrażających, nie musisz wracać na statek.";
			link.l1.go = "tieyasal_9";
		break;
		
		case "tieyasal_9":
			dialog.text = "Wow!  Naprawdę? Cóż, może to i lepiej. Nie chcę być z nudziarzami, którzy nawet nie rozumieją dowcipów. W takim razie... żegnaj, Wasza Ekscelencjo.";
			link.l1 = "Żegnaj, Tommy. I idź do diabła.";
			link.l1.go = "tieyasal_10";
		break;
		
		case "tieyasal_10":
			DialogExit();
			RemovePassenger(pchar, npchar);
			DeleteAttribute(npchar, "OfficerImmortal");
			npchar.lifeday = 0;
			LAi_SetWarriorType(npchar);
			LAi_CharacterDisableDialog(npchar);
		break;
	}
} 
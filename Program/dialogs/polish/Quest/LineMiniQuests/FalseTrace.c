void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Błąd. Daj nam znać.";
			link.l1 = "Pewnie!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "FalseTrace":
			DelMapQuestMarkCity(pchar.questTemp.FalseTrace.StartCity);
			dialog.text = "Dobry popołudniu, kapitanie... ehm... kha-hahrm! Cholera jasna te kopalnie... Pozwól, że się przedstawię. Adam Rayner. Jestem prostym człowiekiem i nie lubię długich wstępów, więc od razu przechodzę do rzeczy. Chcesz dobrze zarobić? Oferuję ci mały interes, któremu sami nie podołamy.";
			link.l1 = "Heh! Dobre pieniądze? Interesujące. Słucham cię, Adamie.";
			link.l1.go = "FalseTrace_1";
			link.l2 = "Wiesz, przykro mi, ale nie wyglądasz na godnego zaufania. Więc nie będę miał z tobą żadnych interesów.";
			link.l2.go = "FalseTrace_exit";
		break;
		
		case "FalseTrace_exit":
			dialog.text = "Godny zaufania? Ha-ha! Nie powinno się oceniać człowieka po twarzy. No, nieważne. Właśnie przegapiłeś dobrą okazję, by łatwo i szybko zarobić dobre pieniądze. Znajdę kogoś bardziej współpracującego...";
			link.l1 = "Nasza rozmowa jest skończona, panie. Do widzenia!";
			link.l1.go = "FalseTrace_exit_1";
		break;
		
		case "FalseTrace_exit_1":
			DialogExit();
			DelLandQuestMark(npchar);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			DeleteAttribute(pchar, "questTemp.FalseTrace");
		break;
		
		case "FalseTrace_1":
			//выбираем целевой пункт
			switch (hrand(2))
			{
				case 0: 
					pchar.questTemp.FalseTrace.DayQty = 18;
					pchar.questTemp.FalseTrace.TargetCity = "Beliz";
					pchar.questTemp.FalseTrace.TargetShore = "Shore8";
				break;
				case 1: 
					pchar.questTemp.FalseTrace.DayQty = 22;
					pchar.questTemp.FalseTrace.TargetCity = "Marigo";
					pchar.questTemp.FalseTrace.TargetShore = "Shore41";
				break;
				case 2: 
					pchar.questTemp.FalseTrace.DayQty = 20;
					pchar.questTemp.FalseTrace.TargetCity = "Santodomingo";
					pchar.questTemp.FalseTrace.TargetShore = "Mayak8";
				break;
			}
			pchar.questTemp.FalseTrace.ShipName = GenerateRandomNameToShip(sti(npchar.nation));
			pchar.questTemp.FalseTrace.Mation = sti(npchar.nation);
			dialog.text = "Kha! Przyjemność robić interesy z kimś tak bystrym jak ty, Kapitanie. Zadanie jest proste: jest fluita wypełniony niemałą ilością srebra i wkrótce odpłynie z jednego z lokalnych portów. Jedna jednostka, bez eskorty. Głupie, prawda? K-kha\n Łatwizna. Powiem ci gdzie i kiedy, ty zdobywasz łup, a ja dostaję swoją część.";
			link.l1 = "I oczywiście, chcesz otrzymać to teraz w gotówce?";
			link.l1.go = "FalseTrace_2";
		break;
		
		case "FalseTrace_2":
			dialog.text = "Czy wyglądam jak żałosny złodziejaszek, kapitanie? W żadnym wypadku. Dołączę do ciebie w tym rajdzie i zrobimy to razem. Nie zostanę w ładowni podczas walki, wręcz przeciwnie - proszę cię, byś umieścił mnie w oddziale abordażowym jako swojego oficera, tymczasowo, oczywiście.\nZnam swoją robotę, wiem, jak dźgnąć i strzelać do ludzi. Więc zaryzykuję swoją dupę tak jak ty... khe... kha! Zapłacisz mi moją część po tym, jak zdobędziemy fluita.";
			link.l1 = "Jaką część łupu sobie rościsz?";
			link.l1.go = "FalseTrace_3";
		break;
		
		case "FalseTrace_3":
			dialog.text = "Nie jestem chciwym człowiekiem, kapitanie. Mój udział to tyle, ile można załadować do ładowni mojej starej długiej łodzi, czyli około 200 paczek srebra. Według moich informacji na fluita będzie nie mniej niż 2000 paczek srebra, więc dostanę dziesiątą część. To uczciwe, nie sądzisz?";
			link.l1 = "Jedna dziesiąta łupu tylko za informacje? Kupuję takie informacje od pijaków za szklankę rumu w lokalnej tawernie. Nie, nie idziemy tą samą drogą, przyjacielu!";
			link.l1.go = "FalseTrace_4";
			link.l2 = "Hm. Chyba się zgadzam. Przyjmuję twoją ofertę, Adamie. Witaj na pokładzie. Teraz o twojej informacji: skąd, dokąd, czas, nazwa statku?";
			link.l2.go = "FalseTrace_5";
		break;
		
		case "FalseTrace_4":
			dialog.text = "Co za sknera z ciebie, Kapitanie! W takim razie nie dostaniesz niczego! Do zobaczenia!";
			link.l1 = "Powodzenia! Znajdź innego głupca do swoich szemranych interesów!";
			link.l1.go = "FalseTrace_exit_1";
		break;
		
		case "FalseTrace_5":
			dialog.text = "Nazwa fluitau to "+pchar.questTemp.FalseTrace.ShipName+", odpływa z Cartagena i żegluje "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+"Nie mamy jednak zbyt wiele czasu. Dwa tygodnie, trzy najwyżej. Jeśli nie znajdziemy jej w ciągu trzech tygodni, wszystko przepadnie.";
			link.l1 = "Nie traćmy zatem czasu! Przygoda wzywa!";
			link.l1.go = "FalseTrace_6";
		break;
		
		case "FalseTrace_6":
			DialogExit();
			NextDiag.CurrentNode = "FalseTrace_officer";
			DelLandQuestMark(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto1");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			AddPassenger(pchar, npchar, false);
			AddQuestRecord("FalseTrace", "1");
			AddQuestUserData("FalseTrace", "sCity1", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.StartCity+"Gen"));
			AddQuestUserData("FalseTrace", "sCity2", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity));
			AddQuestUserData("FalseTrace", "sShip", pchar.questTemp.FalseTrace.ShipName);
			//установим таймер на генерацию энкаунтера
			pchar.quest.False_Trace_2.win_condition.l1 = "Timer";
			pchar.quest.False_Trace_2.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.False_Trace_2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2);
			pchar.quest.False_Trace_2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.False_Trace_2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2);
			pchar.quest.False_Trace_2.function = "CreateFalseTraceGaleonOnMap";
			SetFunctionTimerCondition("FalseTraceGaleonOver", 0, 0, sti(pchar.questTemp.FalseTrace.DayQty)+2, false);//таймер
		break;
		
		case "FalseTrace_officer":
			dialog.text = "Chciałeś czegoś, kapitanie?";
			link.l1 = "Nic, nieważne.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FalseTrace_officer";
		break;
		
		case "FalseTrace_7":
			chrDisableReloadToLocation = true;
			dialog.text = "Czy chciałeś mnie widzieć, kapitanie?";
			link.l1 = "Myślę, że to przewidziałeś... Gdzie jest srebro, do diabła? Gdzie ono jest? Mówię do ciebie! Kapitan fluitau powiedział mi, że to był statek zaopatrzeniowy! Okłamałeś mnie!";
			link.l1.go = "FalseTrace_8";
		break;
		
		case "FalseTrace_8":
			dialog.text = "Spokojnie, Kapitanie. Spróbuję wszystko wyjaśnić.";
			link.l1 = "Oczywiście, że tak! Już się uspokoiłem! Nie wisisz teraz na rei tylko dlatego, że wciąż nie mogę pojąć twoich motywów. Ścigałeś ten fluita ze mną, wiedząc wcześniej, że nie było tam srebra. Więc proszę, wyjaśnij się.";
			link.l1.go = "FalseTrace_9";
		break;
		
		case "FalseTrace_9":
			dialog.text = "Tak, naprawdę cię oszukałem, Kapitanie. Ale to był jedyny sposób, by przekonać cię do zrobienia tego, czego potrzebuję, do zdobycia... khe kha! Do zdobycia tego przeklętego fluitau\nAle obiecuję, że spłacę mój dług wobec ciebie. Teraz pozwól mi wyjaśnić, dlaczego to zrobiłem. Czy znalazłeś kobietę na fluitaie? Widziałem, jak załoganci zabierają ją na twój statek...";
			link.l1 = "Hm... A więc, potrzebowałeś dziewczyny? I dlatego zmusiłeś mnie do rozpoczęcia bitwy morskiej i zabicia wielu ludzi!?";
			link.l1.go = "FalseTrace_10";
		break;
		
		case "FalseTrace_10":
			dialog.text = "To moja żona. Katerine Rayner. Uciekła ode mnie trzy miesiące temu z tym żałosnym kapitanem. Zrobiłem wszystko, aby ich znaleźć i udało mi się. Oboje zmierzali do "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+". Nie mogłem sobie wyobrazić lepszego sposobu na odzyskanie Katerine i na załatwienie tego złodzieja żon\nGdybym powiedział ci prawdę, odszedłbyś. Więc musiałem opowiedzieć ci soczystą historię o fluitaie pełnym srebra.";
			link.l1 = "Hmpf... Twoja żona cię opuściła, prawda? Bardzo interesujące!";
			link.l1.go = "FalseTrace_11";
		break;
		
		case "FalseTrace_11":
			dialog.text = "To moja prawowita żona, kocham ją i nikt inny nie ma prawa być z nią! Ten łajdak opowiedział jej piękne kłamstwa o romansie i całym tym bzdurze, kiedy ja byłem... z dala. Nie znasz się na kobietach? Uwierzyła w te bzdury, głupiutka dziewczyna, i uciekła z nim.";
			link.l1 = "Dobrze, słuchaj, naprawdę nie obchodzi mnie twoje życie rodzinne, więc załatw to z żoną. Ale mówiłeś coś o zrekompensowaniu moich kosztów, prawda? Czy dobrze cię zrozumiałem?";
			link.l1.go = "FalseTrace_12";
		break;
		
		case "FalseTrace_12":
			if (pchar.basenation == SPAIN || pchar.basenation == HOLLAND)
			{
				pchar.questTemp.FalseTrace.QuestCity = "Portobello";
				pchar.questTemp.FalseTrace.QuestShore = "Shore48";
			}
			else
			{
				pchar.questTemp.FalseTrace.QuestCity = "SantaCatalina";
				pchar.questTemp.FalseTrace.QuestShore = "Shore54";
			}
			dialog.text = "Tak, dobrze mnie słyszałeś, kapitanie. Przysługa za przysługę. Nie mam teraz pieniędzy, ale jeśli przyprowadzisz Katerinę i mnie do "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+", Powiem ci całkowicie wiarygodną informację, gdzie możesz zdobyć trochę złota bez żadnego wysiłku.";
			link.l1 = "Bardzo interesujące. A dlaczego nie możesz mi teraz powiedzieć tej całkowicie wiarygodnej informacji?";
			link.l1.go = "FalseTrace_13";
		break;
		
		case "FalseTrace_13":
			dialog.text = "Ponieważ, nie mam jeszcze tych informacji. Pozwól, że wyjaśnię szczegóły. Pewien dżentelmen fortuny o imieniu Zezowaty Solly - słyszałeś o nim kiedyś? - zamierza splądrować jakieś złote kopalnie niedaleko Blueweld\nZ powodu pewnych wydarzeń, będzie musiał zostawić całe swoje złoto w jakimś ukrytym miejscu i zostawić kilku strażników, by je chronili. Sam pójdzie pieszo do Belize lub do Blueweld, aby zdobyć statek\nMam agenta wśród załogi Solly'ego, będzie czekał na mnie w "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+" Jak już zarzucimy kotwicę tam, powie mi, gdzie Solly ukrywa swoje skarby\nTy pójdziesz tam, wyeliminujesz strażników i zabierzesz całe złoto dla siebie. Zamierzałem to zrobić sam, ale biorąc pod uwagę obecną sytuację, zostawiam wszystko tobie. Bez opłat.";
			link.l1 = "Twoja opowieść brzmi dość podobnie do twej poprzedniej bajki o fluitaie załadowanym srebrem. Już raz mnie oszukałeś. Jak możesz zagwarantować, że tym razem nie kłamiesz?";
			link.l1.go = "FalseTrace_14";
		break;
		
		case "FalseTrace_14":
			dialog.text = "Daję ci moje słowo. Nie mam innych gwarancji. Ale to prawda, przysięgam khe... kha... cholera, kopalnie!";
			link.l1 = "Dobrze. Teraz idź, a ja pomyślę o tym, co powiedziałeś.";
			link.l1.go = "FalseTrace_15";
		break;
		
		case "FalseTrace_15":
			dialog.text = "Nie zastanawiaj się zbyt długo. Zezowaty Solly wróci po swoje skarby, jak powinieneś to pojąć. Według moich obliczeń masz tylko dwa tygodnie, aby dotrzeć do "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+".";
			link.l1 = "Będę o tym pamiętać. A teraz idź do kwater załogi i dołącz do marynarzy. Myślę, że lepiej, żebyś był oddzielony od swojej żony aż do naszego przybycia. Możesz już iść.";
			link.l1.go = "FalseTrace_16";
		break;
		
		case "FalseTrace_16":
			DialogExit();
			LAi_SetActorType(npchar);
			pchar.questTemp.FalseTrace = "TalkCabinWoman";
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "TalkSelf_Quest", 3.0);
			SetFunctionTimerCondition("FalseTraceSollyOver", 0, 0, 15, false);//таймер
			AddQuestRecord("FalseTrace", "5");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
		break;
		
		case "FalseTrace_17":
			dialog.text = "Wołałeś mnie, kapitanie?";
			link.l1 = "Tak. Adamie Rayner, aresztuję cię i zamknę. Oszukałeś mnie, i nie mam innego wyboru, jak tylko odizolować cię i przekazać władzom.";
			link.l1.go = "FalseTrace_18";
		break;
		
		case "FalseTrace_18":
			dialog.text = "Naprawdę? Spodziewałem się, że tak zrobisz, Kapitanie. Zwłaszcza po tym, jak przyszedłeś do ładowni i porozmawiałeś z tym plugawym porywaczem cudzych żon. Zdecydowałeś, że jesteś po jego stronie, czyż nie, Kapitanie?";
			link.l1 = "To nie twój interes. Wykorzystałeś mnie, oszukałeś mnie, a teraz próbujesz mnie znowu zwieść absurdalnymi opowieściami o skarbach! Bosmanie, zabierz go!";
			link.l1.go = "FalseTrace_19";
		break;
		
		case "FalseTrace_19":
			dialog.text = "Kha, nie tak szybko, kapitanie... Bosman i reszta twoich ludzi nie będą mogli tu szybko wejść. Nie zauważyłeś, że zamknąłem drzwi? Teraz jesteśmy tu sami - tylko ty i ja. Pokaż mi więc, kapitanie, z czego jesteś zrobiony!";
			link.l1 = "Naprawdę? Naprawdę myślisz, że masz szansę?! Pożałujesz tego, draniu!";
			link.l1.go = "FalseTrace_20";
		break;
		
		case "FalseTrace_20":
			DialogExit();
			NextDiag.currentnode = "FalseTrace_21";
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetHP(npchar, 100+MOD_SKILL_ENEMY_RATE*35, 100+MOD_SKILL_ENEMY_RATE*35); // belamour с 40 хп боец из него никудышный
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "FalseTrace_capture");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_21":
			dialog.text = "";
			link.l1 = "To lepiej... Odłóż broń, łajdaku! Bosmanie! Zakuć tego drania w kajdany i wrzuć go do ładowni!";
			link.l1.go = "FalseTrace_22";
		break;
		
		case "FalseTrace_22":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			bQuestDisableMapEnter = false;
			RemovePassenger(Pchar, npchar);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			Pchar.questTemp.FalseTrace.PrisonerAdamIDX = sti(pchar.GenQuest.LastQuestPrisonerIdx);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			LAi_SetPlayerType(pchar);
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(npchar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(npchar, CIRASS_ITEM_TYPE);
			sld = &Characters[sti(Pchar.questTemp.FalseTrace.PrisonerIDX)];
			ReleasePrisoner(sld); //освободили пленника
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			DeleteAttribute(sld, "LifeDay") //постоянный персонаж
			GiveItem2Character(sld, "blade_10");
			EquipCharacterbyItem(sld, "blade_10");
			GiveItem2Character(sld, "pistol1");
			EquipCharacterbyItem(sld, "pistol1");//патроны не даю - все одно для антуражу
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			AddComplexSelfExpToScill(40, 40, 40, 40);
			AddQuestRecord("FalseTrace", "11");
			AddQuestUserData("FalseTrace", "sShore", XI_ConvertString(pchar.questTemp.FalseTrace.TargetShore+"Gen"));
			pchar.questTemp.FalseTrace = "AdamPrisoner";
		break;
		
		case "FalseTrace_23":
			pchar.quest.FalseTraceSollyOver.over = "yes"; //снять таймер
			dialog.text = "Dziękuję, kapitanie, za pomoc w odnalezieniu mojej żony! Adam Rayner jest twoim dłużnikiem, nie zapomni o tym, ha-ha, przysięgam na... kha! Przeklęte kopalnie! Teraz o Zezowatym Sollym. Mój człowiek już mi wszystko opowiedział. Solly zostawił wszystkie swoje skarby w grocie zatoki San Juan del Norte. Sam przebywa teraz w Blueweld\nPowinieneś się pospieszyć, masz tylko pięć dni, według mojego kumpla. Zabierz swoich ludzi, bandyci Solly’ego są twardzi, dadzą ci popalić\nCzas się pożegnać. Jeszcze raz dziękuję, Kapitanie, powodzenia!";
			link.l1 = "Powodzenia, Adamie. Nie obrażaj swej żony!";
			link.l1.go = "FalseTrace_Remove_exit";
			SetFunctionTimerCondition("FalseTraceBonanzaOver", 0, 0, 5, false);//таймер
			pchar.quest.False_Trace_4.win_condition.l1 = "location";
			pchar.quest.False_Trace_4.win_condition.l1.location = "Shore55";
			pchar.quest.False_Trace_4.function = "FalseTrace_SollyBonanza";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddQuestRecord("FalseTrace", "14");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
		break;
		
		case "FalseTrace_24":
			pchar.quest.FalseTraceSollyOver.over = "yes"; //снять таймер
			dialog.text = "Ha! Dlaczego, kapitanie, zeszliśmy na ląd w tej zatoce? Mówiłem ci, że mój człowiek czekał na mnie w porcie "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+"! Czy zamierzasz iść tam pieszo przez dżungle?";
			link.l1 = "Zły domysł, Adamie. Naprawdę myślałeś, że znowu uwierzę w twoje bzdury? Myślisz, że jestem totalnym głupcem? Tym razem zawarłem umowę z twoją żoną.";
			link.l1.go = "FalseTrace_25";
		break;
		
		case "FalseTrace_25":
			dialog.text = "Co?! Cha! Jaka umowa z moją żoną? O czym ty mówisz, ty zgniła rybo?!";
			link.l1 = "Z powodu twoich fałszywych informacji pojmałem pusty fluita i zabiłem jego kapitana. Żałuję, że to zrobiłem, choć na żal jest już za późno. Twoja żona była zakochana w tym żeglarzu, jak zrozumiałem. Dlatego poprosiła mnie, bym cię zabił. Dlatego teraz jesteśmy w tej zatoce.";
			link.l1.go = "FalseTrace_26";
		break;
		
		case "FalseTrace_26":
			dialog.text = "Nie mogę w to uwierzyć! Katerina... co za suka! Cóż, jeszcze dostaniesz to, na co zasługujesz... Więc jak obiecała ci zapłacić, głupcze? Nie ma grosza, sprzedała nawet całą swoją biżuterię, żeby uciec z tym kapitanem!";
			link.l1 = "To nie twój interes, łajdaku. Ale czas zakończyć naszą rozmowę. Wyślę cię do piekła, gdzie już dawno powinieneś być!";
			link.l1.go = "FalseTrace_27";
		break;
		
		case "FalseTrace_27":
			dialog.text = "Zobaczmy, co potrafisz, zgniły śledziu!";
			link.l1 = "... ";
			link.l1.go = "FalseTrace_28";
		break;
		
		case "FalseTrace_28":
			DialogExit();
			npchar.SaveItemsForDead = true;
			npchar.DontClearDead = true;
			LAi_SetWarriorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FalseTrace_AdamDead");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_abordage":
			dialog.text = "Ach! Dlaczego, do cholery, zaatakowałeś mój statek, łajdaku? Nie mogę tego pojąć...";
			link.l1 = "Nie udawaj baranka, kapitanie. Wiem, jaki ładunek przewozisz. Potrzebuję go.";
			link.l1.go = "FalseTrace_abordage_1";
		break;
		
		case "FalseTrace_abordage_1":
			dialog.text = "Ładunek? Ha-ha! Jakiego ładunku się tu spodziewałeś? Moje ładownie są puste!";
			link.l1 = "Co powiedziałeś, łajdaku! Powtórz to!";
			link.l1.go = "FalseTrace_abordage_2";
		break;
		
		case "FalseTrace_abordage_2":
			dialog.text = "Powtarzam - nie mam żadnego ładunku na pokładzie. Ten fluita to statek zaopatrzeniowy zmierzający do "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+" dostarczyć ładunek kul armatnich i zaopatrzenia dla wojsk.";
			link.l1 = "Zamydlasz mi oczy. Twoje ładownie muszą być pełne srebra. A ja to sprawdzę, gdy skończymy tę rozmowę...";
			link.l1.go = "FalseTrace_abordage_3";
		break;
		
		case "FalseTrace_abordage_3":
			dialog.text = "Nie wiem, kto ci powiedział o srebrze. Ale to absolutne bzdury... Przegrałem z tobą, więc się poddaję. Oto mój miecz. Teraz możesz iść i sprawdzić ładownie. Są puste.";
			link.l1 = "Poddać się? Nie! Nie potrzebuję żadnych świadków. Chwytaj za szablę i walcz, albo wypatroszę cię jak owcę.";
			link.l1.go = "FalseTrace_abordage_4";
			link.l2 = "Dobrze dla ciebie, że okazałeś rozsądek. Myślę, że będę w stanie dostać za ciebie okup... Hej, chłopaki - wrzuccie kapitana do ładowni!";
			link.l2.go = "FalseTrace_abordage_5";
		break;
		
		case "FalseTrace_abordage_4":
			DialogExit();
			pchar.questTemp.FalseTrace.KillCaptain = "true";//атрибут квеста
			Lai_SetPlayerType(pchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "FalseTrace_AfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.FalseTrace.CapName = GetFullName(npchar);
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
		break;
		
		case "FalseTrace_abordage_5":
			DialogExit();
			pchar.questTemp.FalseTrace.CapPrisoner = "true";//атрибут квеста
			Lai_SetPlayerType(pchar);
			DeleteAttribute(npchar, "DontRansackCaptain");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "FalseTrace_AfterFight", 3.0);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			pchar.questTemp.FalseTrace.CapName = GetFullName(npchar);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "FalseTrace_wife":
			dialog.text = "Zabiłeś go, łotrze! Draniu! Biedny "+pchar.questTemp.FalseTrace.CapName+"!";
			link.l1 = "Co to takiego? Skąd się tu wzięłaś, kochana?";
			link.l1.go = "FalseTrace_wife_1";
		break;
		
		case "FalseTrace_wife_1":
			dialog.text = "Spłoniesz w piekle za wszystko, co zrobiłeś. Do diabła z tobą!";
			link.l1 = "Spokojnie, młoda damo! Nie próbuj szczęścia, przeklinając mnie - bo wyślę cię zaraz za twoim kapitanem!";
			link.l1.go = "FalseTrace_wife_2";
		break;
		
		case "FalseTrace_wife_2":
			dialog.text = "Ty ... ty nie ośmielisz się podnieść ręki na kobietę!";
			link.l1 = "Nie będę nawet musiał. Mogę cię zastrzelić. Albo po prostu wyrzucę cię za burtę, a resztę zrobią rekiny... Na co jeszcze czekasz? Idź na mój statek. Nie bój się - nie pozwolę nikomu cię skrzywdzić i sam nie tknę cię, jeśli będziesz cicho...";
			link.l1.go = "FalseTrace_wife_3";
		break;
		
		case "FalseTrace_wife_3":
			DialogExit();
			pchar.quest.False_Trace_AfterBattle.over = "yes";
			pchar.quest.FalseTraceGaleonOver.over = "yes";
			if (CheckAttribute(pchar, "questTemp.FalseTrace.CapPrisoner")) AddQuestRecord("FalseTrace", "");
			else AddQuestRecord("FalseTrace", "");
			sld = characterFromId("Mugger");
			DeleteAttribute(sld, "HalfImmortal");
			RemovePassenger(Pchar, sld);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			DoQuestCheckDelay("LAi_EnableReload", 4.0);
			bQuestDisableMapEnter = true;
			pchar.questTemp.FalseTrace = "TalkCabin";
			AddQuestRecord("FalseTrace", "4");
		break;
		
		case "FalseTrace_wife_4":
			dialog.text = "Co... co zamierzasz z nim zrobić?";
			link.l1 = "Co to jest? Skąd się tu wzięłaś, kochana?";
			link.l1.go = "FalseTrace_wife_5";
		break;
		
		case "FalseTrace_wife_5":
			dialog.text = "Biedny "+pchar.questTemp.FalseTrace.CapName+"Powiedz mi - zamierzasz go zabić? Nie...";
			link.l1 = "Słuchaj teraz, pani - gdybym chciał go zabić, już bym to zrobił. Będzie przebywał w ładowni, a potem go wypuszczę lub prawdopodobnie zażądam okupu... to drugie jest bardziej prawdopodobne. A teraz bądź dobrą dziewczyną i wejdź na pokład mojego statku. Nie bój się - nie pozwolę nikomu cię skrzywdzić i sam cię nie dotknę, jeśli będziesz cicho...";
			link.l1.go = "FalseTrace_wife_3";
		break;
		
		case "FalseTrace_wife_6":
			if (CheckAttribute(pchar, "questTemp.FalseTrace.KillCaptain"))
			{
				dialog.text = "Czego ode mnie chcesz? Wyrzuć mnie do rekinów, jak mówiłeś, że zrobisz? Zrujnowałeś moje życie i ja...";
				link.l1 = "Chodź, kochanie. Nikt cię nigdzie nie wyrzuci. Chcę tylko wyjaśnić sytuację, ponieważ zaatakowałem ten fluita z twojego powodu, a nie z jakiegokolwiek innego.";
				link.l1.go = "FalseTrace_wife_7";
			}
			else
			{
				dialog.text = "Czego ode mnie chcesz? Gdzie jest "+pchar.questTemp.FalseTrace.CapName+"Czy okup? Potrzebujesz okupu?";
				link.l1 = "Dobrze, pani, przestańmy z tym potokiem bezsensownych pytań. Nie po to cię tu wezwałem. Jeden fakt został wyjaśniony i będzie cię interesować, żeby go usłyszeć.";
				link.l1.go = "FalseTrace_wife_20";
			}
		break;
		
		case "FalseTrace_wife_7":
			dialog.text = "Przeze mnie? Czy chcesz powiedzieć, że to moja wina, iż zaatakowaliście nasz statek i zabiliście moją ukochaną? Biedna "+pchar.questTemp.FalseTrace.CapName+", co on ci zrobił? Odpowiesz przed Panem za wszystko, co uczyniłeś...";
			link.l1 = "Ten sam stary gulasz! Czy powinniśmy wrócić do rozmowy o rekinach?";
			link.l1.go = "FalseTrace_wife_8";
		break;
		
		case "FalseTrace_wife_8"://ноды пересечения - старт
			dialog.text = "";
			link.l1 = "Już cicho? Wspaniale. Teraz mnie słuchaj! Zaatakowałem statek, ponieważ miałem informacje, że przewoził porządny ładunek srebra. I te informacje otrzymałem od Adama Raynera.";
			link.l1.go = "FalseTrace_wife_9";
		break;
		
		case "FalseTrace_wife_9":
			dialog.text = "Ach! Co?! Adam? Gdzie on jest? Czy jest tutaj?";
			link.l1 = "Widzę, że znasz to imię... Katerine. I jak widzisz, wiem już o tobie wszystko. Rozumiem, że Adam Rayner to twój mąż, prawda?";
			link.l1.go = "FalseTrace_wife_10";
		break;
		
		case "FalseTrace_wife_10":
			dialog.text = "Tak. Jestem żoną tego potwora. Byłam pod wrażeniem, że ten koszmar wreszcie się skończył... Czy zatrudnił cię, by mnie złapać?";
			link.l1 = "Zazwyczaj tak się okazywało. Adam okłamał mnie o srebrze, bym schwytał fluita."+pchar.questTemp.FalseTrace.ShipName+"'. Zdecydowanie, był zdeterminowany, by cię sprowadzić z powrotem. Kwadrans temu wyjaśnił mi wszystkie swoje działania.";
			link.l1.go = "FalseTrace_wife_11";
		break;
		
		case "FalseTrace_wife_11":
			dialog.text = "I... czego on chce? Co ci powiedział?";
			link.l1 = "On chce, żeby jego prawowita żona wróciła do niego. Dostarczy mi informacji o złocie zezowatego Solly'ego jako rekompensatę za oszustwo. A ja zamierzam zabrać was oboje do "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+".";
			link.l1.go = "FalseTrace_wife_12";
		break;
		
		case "FalseTrace_wife_12":
			dialog.text = "Nie... (płacząc) Nie chcę wracać do tego łotra! Włożyłam ogromny wysiłek, aby od niego uciec i zatrzeć swoje ślady, ale on i tak mnie znalazł... Łotr! Bandyta! Kurwa złodziejaszku!";
			link.l1 = "Spokojnie, Katerine... Uważaj na język. On jest przecież twoim mężem. I powiedział, że cię kocha.";
			link.l1.go = "FalseTrace_wife_13";
		break;
		
		case "FalseTrace_wife_13":
			dialog.text = "(płacząc) Mój mąż? Czy wiesz, kim jest mój mąż? On jest byłym więźniem, skazańcem, a teraz najokrutniejszym bandytą "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.StartCity+"Generał")+"! On jest podłym i plugawym bydlakiem, a ja jestem dla niego tylko dziurą między nogami do pieprzenia!";
			link.l1 = "Czyż nie widziałaś tego wszystkiego, zanim go poślubiłaś?";
			link.l1.go = "FalseTrace_wife_14";
		break;
		
		case "FalseTrace_wife_14":
			dialog.text = "Na początku był inny... A jego przeszłość wydawała mi się tak romantyczna... Ale ostatecznie wszystko się zmieniło. I nawet nie chcę go widzieć, nie mówiąc już o życiu z nim, czy nie rozumiesz tego? Nie chcę! Zwłaszcza po tym ataku na fluita, który zorganizował!";
			link.l1 = "Hm... Co mam z tobą zrobić, słodka damo?";
			link.l1.go = "FalseTrace_wife_15";
		break;
		
		case "FalseTrace_wife_15"://ноды пересечения - конец
			if (CheckAttribute(pchar, "questTemp.FalseTrace.KillCaptain"))
			{
				dialog.text = "Co robić? Wiem, co robić. Jesteś narzędziem grzechu, dzięki uczynkom mego męża. Zabiłeś niewinnego człowieka, jedynego, który mnie dobrze traktował. Odpokutuj za swoje grzechy, kapitanie. Zabij Adama. Na moich oczach. Chcę widzieć, jak to ścierwo umiera, chcę splunąć na jego trupa. Gdy będzie martwy, powiem ci, gdzie ukrywa swoje skarby. Pijany idiota kiedyś mi powiedział o swojej kryjówce, ha-ha, nawet tego nie pamięta!";
				link.l1 = "Ha! Jesteś okrutną kobietą, Katerino, jak widzę!";
				link.l1.go = "FalseTrace_wife_16";
			}
			else
			{
				dialog.text = ""+pchar.questTemp.FalseTrace.CapName+"... Kapitan fluitau. Uwięziłeś go. Porozmawiaj z nim, błagam cię! Zaproponuje ci coś za nasze życie i wolność! Wymyśli jakiś pomysł! Ja... Ja nie chcę wracać do Adama, od teraz "+pchar.questTemp.FalseTrace.CapName+" to mój mąż! Błagam cię - nie oddawaj mnie Adamowi, temu potworowi!";
				link.l1 = "Hm. Interesujące. A co mój więzień może mi zaoferować? Mogę dostać za niego okup od władz, a także zdobędę złoto Zezowatego Solly'ego...";
				link.l1.go = "FalseTrace_wife_21";
			}
		break;
		
		case "FalseTrace_wife_16":
			dialog.text = "Popatrz, kto mówi o okrucieństwie. Żegluj do "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+", zrób, co Adam ci powiedział, tylko wyląduj nie w porcie, ale w najbliższej zatoce. Trzech z nas tam pójdzie, a ty zabijesz drania\nKiedy to zrobisz, powiem ci o skrytce. Przysięgam, nie kłamię. Wierzę, że masz więcej zaufania do moich słów niż do Adama, oszukał cię raz, prawda? Co powiesz, kapitanie?";
			link.l1 = "Tak... Nie bez powodu mówią, że mąż i żona to naprawdę ta sama para. Patrzę na ciebie, Katerino, i widzę, że jesteś idealnym dopasowaniem dla Adama... Jeśli tak bardzo chcesz jego śmierci, możesz go równie dobrze zadźgać, gdy śpi pijany... Bosmanie! Zabierz ją!";
			link.l1.go = "FalseTrace_wife_17";
			link.l2 = "Nienawidzę łajdaków, którzy próbują mnie oszukać i wykorzystać do swoich celów. Dobrze, Katherine, zgadzam się na twoją propozycję, ponieważ jest dla mnie jasne, że Adamowi nie można ufać. Ale jeśli ty mnie oszukasz, także cię znajdę, nawet w Europie, przysięgam, i wpakuję ci kulę w łeb. A teraz zmykaj. Bosmanie! Zabierz ją!";
			link.l2.go = "FalseTrace_wife_19";
		break;
		
		case "FalseTrace_wife_17":
			dialog.text = "Będziesz tego żałować... Przysięgam, ja...";
			link.l1 = "Bosmanie! Pilnuj jej i miej na nią oko przez cały czas, aż dotrzemy do "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Rodzaj")+"!";
			link.l1.go = "FalseTrace_wife_18";
		break;
		
		case "FalseTrace_wife_18":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("FalseTrace", "6");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
			AddDialogExitQuestFunction("SetCheckForSolly");
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		break;
		
		case "FalseTrace_wife_19":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("FalseTrace", "7");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
			AddDialogExitQuestFunction("SetCheckForKillAdam");
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		break;
		
		case "FalseTrace_wife_20":
			dialog.text = "Jaki fakt? Co zamierzasz z nami zrobić? Dlaczego przejęliście nasz statek?";
			link.l1 = "Czy pozwolisz mi się odezwać, czy mam rozkazać mojemu bosmanowi zatkać ci usta kneblem?!";
			link.l1.go = "FalseTrace_wife_8";
		break;
		
		case "FalseTrace_wife_21":
			dialog.text = "Złoto Solly'ego? Naprawdę ufasz temu łajdakowi? On cię znowu oszuka, to jego metoda! Porozmawiaj z twoim więźniem!\n"+pchar.questTemp.FalseTrace.CapName+" to prawdziwy dżentelmen, nie złamie swojego słowa i nie okłamie cię!";
			link.l1 = "Nie przekonałaś mnie, pani. Nie mam o czym rozmawiać z twoim kapitanem. Dostanę za niego okup i dostanę złoto Solly'ego od Adama. Jeśli Adam znów mnie oszuka, znajdę go nawet na końcu świata, a on przeklnie dzień, w którym się urodził... Bosmanie! Zabierz ją!";
			link.l1.go = "FalseTrace_wife_23";
			link.l2 = "Powiem ci szczerze, nie ufam Adamowi... Nie znoszę być manipulowany. Dobrze, porozmawiam z twoim kapitanem i zobaczę, co mi może powiedzieć. Możesz już iść... Bosmanie! Zabierz ją!";
			link.l2.go = "FalseTrace_wife_24";
		break;
		
		case "FalseTrace_wife_23":
			dialog.text = "Jesteś okrutnym i bezdusznym człowiekiem! Przysięgam, że ja...";
			link.l1 = "Bosmanie! Pilnuj jej i miej na nią oko przez cały czas, aż dotrzemy do "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+"!";
			link.l1.go = "FalseTrace_wife_18";
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], true);
		break;
		
		case "FalseTrace_wife_24":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("FalseTrace", "8");
			chrDisableReloadToLocation = false;
			pchar.questTemp.FalseTrace.Prisoner = "true";
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], true);
		break;
		
		case "FalseTrace_wife_25":
			dialog.text = "To już koniec... Biedny "+pchar.questTemp.FalseTrace.CapName+" jest pomszczony, i teraz mogę swobodnie oddychać i nazywać się wdową...";
			link.l1 = "Spełniłem swoją część umowy, Katerine. Teraz twoja kolej.";
			link.l1.go = "FalseTrace_wife_26";
		break;
		
		case "FalseTrace_wife_26":
			dialog.text = "Oczywiście, kapitanie. Mój mąż - dzięki Bogu, teraz były mąż - był bandytą, jak już wiesz. Obawiając się możliwych rewizji, nie trzymał łupów w domu. Zorganizował skrytkę - ale raz się o niej wygadał. Mimo to ukrył ją w bardzo sprytny sposób - nie ma dostępu do tego miejsca od strony brzegu.";
			link.l1 = "Bardzo interesujące... A gdzie to jest?";
			link.l1.go = "FalseTrace_wife_27";
		break;
		
		case "FalseTrace_wife_27":
			dialog.text = "Na małej wyspie w pobliżu Hispanioli. W latarni morskiej.";
			link.l1 = "Latarnia morska Port-au-Prince! Znajduje się na wyspie!";
			link.l1.go = "FalseTrace_wife_28";
		break;
		
		case "FalseTrace_wife_28":
			dialog.text = "Prawdopodobnie tak. Tam będziesz mógł znaleźć łup. Zobaczysz. To wszystko. Do widzenia, Kapitanie.";
			link.l1 = "Poczekaj... Wybacz mi, Katarzyno, jeśli możesz. Mam nadzieję, że śmierć tego, kto odpowiada za wszystkie twoje nieszczęścia, przyniesie ci ulgę. Naprawdę mi przykro...";
			link.l1.go = "FalseTrace_wife_29";
		break;
		
		case "FalseTrace_wife_29":
			dialog.text = "Nie potrzebuję twoich ubolewań, kapitanie. Zrobiłeś, co prosiłem - i powiedziałem ci wszystko, co chciałeś wiedzieć. Żegnaj teraz, i zostaw mnie samego z moim smutkiem...";
			link.l1 = "Żegnaj, Katerine.";
			link.l1.go = "FalseTrace_wife_30";
		break;
		
		case "FalseTrace_wife_30":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 15);
			LAi_LocationDisableOfficersGen(pchar.questTemp.FalseTrace.QuestShore, false);//офицеров пускать
			//LAi_LocationDisableOfficersGen("Mayak7", true);//офицеров не пускать
			locations[FindLocation("Mayak7")].DisableEncounters = true;//энкаунтеры закрыть
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			pchar.quest.False_Trace_7.win_condition.l1 = "location";
			pchar.quest.False_Trace_7.win_condition.l1.location = "Mayak7";
			pchar.quest.False_Trace_7.function = "FalseTrace_AdamTreasure";
			AddQuestRecord("FalseTrace", "23");
		break;
		
		case "FalseTrace_wife_31":
			dialog.text = "Plugawy łotr! Udało mu się zabić całą czwórkę! Niewiarygodne!";
			link.l1 = "Nie spodziewałaś się takiego obrotu, Katerine? Trudno mnie zabić. Muszę przyznać, że grasz w podwójną grę całkiem nieźle!";
			link.l1.go = "FalseTrace_wife_32";
		break;
		
		case "FalseTrace_wife_32":
			dialog.text = "Zabiłeś mojego człowieka. Naprawdę myślisz, że pozwolę ci dalej oddychać?! Myślałeś, że śmierć Adama mnie zadowoliła? Nie! Nie opuścisz tego miejsca. Niedaleko tej wyspy jest statek, który zatopi twój stary kocioł razem z tobą!\nTeraz rób ze mną, co chcesz.";
			link.l1 = "Nie mówiłem ci, kochanie, że stracisz głowę, jeśli mnie oszukasz? Sprytny diabeł! Będziesz o wiele mniej niebezpieczny martwy. Ta piękna głowa zaraz dostanie kulę...";
			link.l1.go = "FalseTrace_wife_33";
			link.l2 = "Współczuję ci, Katerine. Twoje pragnienie zemsty nie przyniosło ci niczego dobrego w końcu. Zostawię cię twojemu losowi - zostaniesz na tej wyspie. Myślę, że miejscowi rybacy wkrótce cię znajdą i zabiorą na Hispaniolę. I niech Pan osądzi nas za wszystkie nasze czyny...";
			link.l2.go = "FalseTrace_wife_35";
		break;
		
		case "FalseTrace_wife_33":
			dialog.text = "To ty powinieneś się modlić, potworze! Morderco! Pomocy! Cholera, ty...";
			link.l1 = "Słyszałem dość.";
			link.l1.go = "FalseTrace_wife_34";
		break;
		
		case "FalseTrace_wife_34":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetImmortal(npchar, false);
			//  belamour legendary edition если не надет пистоль или мушкет, то выдадим строевой -->
			if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE) || !CheckAttribute(pchar,"equip."+MUSKET_ITEM_TYPE))
			{
				GiveItem2Character(pchar, "pistol1");
				EquipCharacterbyItem(pchar, "pistol1");
			}
			// <-- legendary edition
			LAi_ActorAnimation(pchar, "shot", "FalseTrace_CaterinaKilled", 1.0);
		break;
		
		case "FalseTrace_wife_35":
			dialog.text = "Niech cię utopią! Niech twoja łajba roztrzaska się o skały! Niech cię...";
			link.l1 = "Żegnaj, Katerine.";
			link.l1.go = "FalseTrace_wife_36";
		break;
		
		case "FalseTrace_wife_36":
			DialogExit();
			sld = characterFromID("FalseTraceWife"); 
			sld.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "goto", "goto33", "none", "", "", "", -1);
			LAi_SetPlayerType(pchar);
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen("Mayak7", false);//офицеров пускать
			locations[FindLocation("Mayak7")].DisableEncounters = false;//энкаунтеры открыть
			AddQuestRecord("FalseTrace", "25");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			OfficersReaction("good");
		break;
		
		case "FalseTrace_Bandits":
			dialog.text = "A-ah, oto morderca Adama! Katerina miała rację, ten drań przyszedł obrabować skrytkę!";
			link.l1 = "Co? Katerine? Kim jesteś?";
			link.l1.go = "FalseTrace_Bandits_1";
		break;
		
		case "FalseTrace_Bandits_1":
			dialog.text = "Kim my jesteśmy? Jesteśmy przyjaciółmi Adama Raynera, którego zamordowałeś. Był on głową naszego bractwa. Teraz ja jestem głową, nazywam się "+GetFullName(npchar)+", a ja cię ukarzę za zabicie mojego szefa i za przemoc, którą popełniłeś wobec jego żony.";
			link.l1 = "Przemoc? O czym do diabła mówisz?";
			link.l1.go = "FalseTrace_Bandits_2";
		break;
		
		case "FalseTrace_Bandits_2":
			dialog.text = "Zdradziłeś Adama, ty plugawy zdrajco, zmusiłeś jego żonę, by wyjawiła ci, gdzie Adam trzyma swoje złoto, a potem zostawiłeś biedną kobietę na pastwę losu na pustynnym brzegu\nAle ona przeżyła, poprosiła nas o pomoc, by naprawić krzywdę. Czekaliśmy na ciebie kilka dni. I oto jesteś, łajdaku!";
			link.l1 = "Ha-ha! Zdecydowanie w stylu Katerine... Teraz posłuchaj, zabiłem Adama, to prawda, ale zrobiłem to, ponieważ jego żona faktycznie poprosiła mnie, abym go zabił. To była zemsta za śmierć jej kochanka. Powiedziała mi, gdzie znaleźć skrytkę, żeby mi się odwdzięczyć...";
			link.l1.go = "FalseTrace_Bandits_3";
		break;
		
		case "FalseTrace_Bandits_3":
			dialog.text = "Nie oczerniaj biednej wdowy, łajdaku! Dlaczego w takim razie przyszłaby do nas? Zaproponowała nam, byśmy wzięli całe złoto dla siebie w zamian za twoje życie. Nie chce monet, chce twojej śmierci! Święta śmierć za śmierć męża!\nAle przysięgam, że nie umrze w biedzie, to jest tak prawdziwe, jak moje imię to "+GetFullName(npchar)+", a teraz nadszedł czas, byś zginął, tchórzu!";
			link.l1 = "Święty szlag, cóż za wspaniała przemowa. O, jest i ona, chętna osobiście obejrzeć tę komedię... Panowie?";
			link.l1.go = "FalseTrace_Bandits_4";
		break;
		
		case "FalseTrace_Bandits_4":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			DialogExit();
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Adam_bandit_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FalseTrace_BanditsAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_Remove1":
			dialog.text = "Jesteś takim bałaganiarzem, kapitanie! Stracić fluita wypełniony srebrem... Popełniłem błąd, licząc na ciebie. Żegnaj!";
			link.l1 = "Żegnaj, Adam.";
			link.l1.go = "FalseTrace_Remove2";
		break;
		
		case "FalseTrace_Remove2":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 15);
		break;
		
		case "FalseTrace_Remove_exit":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "FalseTraceWife_Remove", 15);
		break;
		
		case "FalseTrace_Remove2":
			dialog.text = "Ostrzegałem cię, kapitanie, mieliśmy tylko dwa tygodnie! Teraz Przymrużony Solly musiał już zabrać cały łup. To nie moja wina, że jesteś takim bałaganiarzem. Żegnaj!";
			link.l1 = "Tak, moja wina. Żegnaj, mam nadzieję, że się już nie spotkamy, przynosisz mi tylko pecha.";
			link.l1.go = "FalseTrace_Remove_exit";
		break;
		
		case "FalseTrace_Solly":
			dialog.text = "Heh! Nareszcie! Jesteśmy zmęczeni czekaniem, a te przeklęte komary... Czekaj... A gdzie jest Solly? Nie rozumiem...";
			link.l1 = "Solly tu nie przyjdzie. Działam w jego imieniu... Więc albo dasz mi złoto, albo jesteś już martwy.";
			link.l1.go = "FalseTrace_Solly_1";
		break;
		
		case "FalseTrace_Solly_1":
			dialog.text = "Argh! Zobaczymy! Do mnie, chłopcy! Do broni!";
			link.l1 = "Taki głupi sposób na śmierć, chodźcie więc, sępy!";
			link.l1.go = "FalseTrace_Solly_2";
			AddDialogExitQuestFunction("FalseTrace_SollyBonanzaAdd");
		break;
		
		case "FalseTrace_Solly_2":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			DialogExit();
			for (i=1; i<=6; i++)
			{
				sld = characterFromId("FTEnemy_crew_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FalseTrace_SollyAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_GoldShip":
			dialog.text = "Spełniłeś swoją część umowy, kapitanie. Dziękuję za zaufanie. Nie martw się o Adama, dostarczę go we właściwe miejsce. Dostanie, na co zasłużył.";
			link.l1 = "Nie obchodzi mnie Adam. A co z twoją obietnicą dotyczącą jakiegoś statku?";
			link.l1.go = "FalseTrace_GoldShip_1";
		break;
		
		case "FalseTrace_GoldShip_1":
			if (sti(pchar.basenation == HOLLAND) || sti(pchar.basenation == SPAIN))
			{
				pchar.questTemp.FalseTrace.ShipNation = ENGLAND;
				pchar.questTemp.FalseTrace.ShipCity = "PortRoyal";
			}
			else
			{
				pchar.questTemp.FalseTrace.ShipNation = SPAIN;
				pchar.questTemp.FalseTrace.ShipCity = "Maracaibo";
			}
			dialog.text = "Tak, tak, oczywiście. Zobaczmy, licząc od dzisiaj... Tak... Za 12-14 dni od "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.ShipCity+"Gen")+" ciężki galeon załadowany złotą rudą wypłynie do Europy. Będzie chroniony przez jedną fregatę lub korwetę\nWięc przygotuj się, to bogaty łup, ale ma zęby. Jednak jestem pewien, że ci się uda, dość łatwo pokonałeś mój opór... Musisz dotrzeć "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.ShipCity+"Gen")+" za dwa tygodnie i przygotuj zasadzkę\nPamiętaj, że twoim celem jest ciężki galeon z jednym statkiem konwojowym. To by było na tyle, jak sądzę. Reszta jest w twoich rękach.";
			link.l1 = "Rozumiem... Cóż, "+pchar.questTemp.FalseTrace.CapName+"Żegnaj. Może powinienem życzyć ci szczęścia i szczęśliwego życia z Katerine? Mam nadzieję, że wam obojgu będzie dobrze. Szkoda, że spotkaliśmy się w takich smutnych okolicznościach.";
			link.l1.go = "FalseTrace_GoldShip_2";
		break;
		
		case "FalseTrace_GoldShip_2":
			dialog.text = "Dziękuję, kapitanie. Jak już wcześniej mówiłem, masz pewną szlachetność. Mam nadzieję, że wyciągniesz właściwy wniosek, że uczciwe czyny przynoszą więcej korzyści niż niehonorowe. Poświęć się służbie swojemu narodowi, a zostaniesz wielkim marynarzem.";
			link.l1 = "Przemyślę twoje słowa. No cóż, żegnaj teraz!";
			link.l1.go = "FalseTrace_GoldShip_3";
		break;
		
		case "FalseTrace_GoldShip_3":
			DialogExit();
			locations[FindLocation(pchar.questTemp.FalseTrace.TargetShore)].DisableEncounters = false; //энкаутеры открыть
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "FalseTraceDouble_Remove", -1);
			pchar.quest.False_Trace_6.win_condition.l1 = "Timer";
			pchar.quest.False_Trace_6.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.False_Trace_6.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 14);
			pchar.quest.False_Trace_6.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 14);
			pchar.quest.False_Trace_6.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 14);
			pchar.quest.False_Trace_6.function = "CreateFalseTraceGoldShipOnMap";
			AddQuestRecord("FalseTrace", "19");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.ShipCity+"Gen"));
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

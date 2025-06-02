// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie masz pytania?","Jak mogę ci pomóc, "+GetAddress_Form(NPChar)+"?"),"Próbowałeś zadać mi jakieś pytanie niedawno temu, "+GetAddress_Form(NPChar)+"...","Przez cały ten dzień, to już trzeci raz, kiedy mówisz o jakimś pytaniu...","Więcej pytań, jak sądzę?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniam zdanie...","Nie mam teraz nic do powiedzenia."),"Umph, gdzie podziała się moja pamięć...","Tak, to naprawdę już trzeci raz...","Nie, jakie pytania?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			/* //--> Jason, Бремя гасконца
			if (!CheckAttribute(npchar, "quest.Rum") && CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.questTemp.Sharlie == "ship" && makeint(environment.time) > 5.0 && makeint(environment.time) < 19.0)
			{
				link.l1 = "Panie, szukam pracy. Czy macie jakieś zlecenia?";
                link.l1.go = "Sharlie_rum";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") && pchar.questTemp.Sharlie.Rum == "regard")
			{
				link.l1 = "Wykonałem twoje zlecenie. Łódź z rumem została dostarczona do Zatoki Le Francois i przekazana twoim ludziom.";
                link.l1.go = "Sharlie_rum_5";
			}	
			//<-- Бремя гасконца */
			
			//Jason, Португалец
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "ToMartinique" && !CheckAttribute(npchar, "quest.Portugal"))
			{
				link.l1 = "Potrzebuję wynająć jeden z twoich pokoi na dwa lub trzy dni. Mam na pokładzie człowieka, który jest ranny. Musi odpocząć i dojść do siebie.";
				link.l1.go = "Portugal";
			}
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "MartiniqueGovernorEnd")
			{
				link.l1 = "Powiedz mi. Mój przyjaciel, dla którego wynająłem pokój, czy wyjechał? Obiecał na mnie czekać, ale pokój jest pusty.";
				link.l1.go = "Portugal_2";
			}
			//Португалец
			// Jason Долго и счастливо
			if (!CheckAttribute(npchar, "quest.LongHappy") && CheckAttribute(PChar, "questTemp.LongHappy.MarryRum") && LongHappy_CheckTavernGoods())
			{
				link.l1 = "Zamierzam zorganizować przyjęcie dla moich ludzi. Przypuszczam, że już o tym wiesz?";
				link.l1.go = "LH_tavern_SP";
			}
			if (CheckAttribute(npchar, "quest.LongHappy.Nomoney") && LongHappy_CheckTavernGoods() && sti(Pchar.money) >= 100000+sti(pchar.questTemp.LongHappy.MarryMoney))
			{
				link.l1 = "Przyniosłem wszystko, co potrzebne do naszej uczty.";
				link.l1.go = "LH_tavern_SP_3";
			}
		break;
		
		//--> Jason, Бремя гасконца
		case "Sharlie_rum":
			DelLandQuestMark(npchar);
			dialog.text = "Zadanie? Hm... Wyglądasz na kogoś, kto ma trochę rozumu, chłopcze. Może mam coś dla ciebie\nTa robota może wydawać się łatwa, ale wymaga odpowiedzialności i rozumu. Nie mogę zaufać tym idiotom, by zajmowali się interesami, na pewno to zrujnują...";
			link.l1 = "Słuchaj, czy możesz mi po prostu powiedzieć, co do diabła chcesz mi zlecić? Przysięgam, nie zawiodę cię, a przynajmniej zrobię, co w mojej mocy.";
			link.l1.go = "Sharlie_rum_1";
		break;
		
		case "Sharlie_rum_1":
			switch(rand(4))
			{
				case 0:
					pchar.questTemp.Sharlie.Rum.Pass = "Old Thomas has grown tired of waiting for the beer";
				break;
				case 1:
					pchar.questTemp.Sharlie.Rum.Pass = "The boards and the oakum will be here in the morning";
				break;
				case 2:
					pchar.questTemp.Sharlie.Rum.Pass = "Don't wait for the south wind";
				break;
				case 3:
					pchar.questTemp.Sharlie.Rum.Pass = "The bay is ready for disembarkation";
				break;
				case 4:
					pchar.questTemp.Sharlie.Rum.Pass = "The camels are going north";
				break;
			}
			dialog.text = " Dobrze. Potrzebuję kogoś, kto dostarczy kilka skrzyń wybornego jamajskiego rumu do mojej tawerny. Chodzi o to, że cła importowe zmniejszają moje marże, a moi najlepsi klienci są spragnieni, więc musimy działać sprytnie, aby uniknąć celników. Szkuner 'Duch' przybędzie dziś wieczorem u wybrzeży Martyniki\nZarzuci kotwicę niedaleko zatoki Lamanten. Musisz odnaleźć ten statek i wejść na pokład. Zapewnię ci łódź i pięciu marynarzy, którzy będą wykonywać twoje rozkazy\nGdy już będziesz na pokładzie, podejdzie do ciebie człowiek. Musisz mu powiedzieć hasło: '"+pchar.questTemp.Sharlie.Rum.Pass+"'\nOdpowiedź będzie 'Czemu by nie napić się rumu, marynarzu?'. Masz tylko jedną próbę, więc zapisz to sobie i nie popełnij błędu, bo inaczej umowa przepadnie. Dlatego nie mogę powierzyć tego tym bezmózgim bałwanom, którzy z tobą popłyną. Powtórz hasło.";
			link.l1 = "' "+pchar.questTemp.Sharlie.Rum.Pass+"'.";
			link.l1.go = "Sharlie_rum_2";
		break;
		
		case "Sharlie_rum_2":
			dialog.text = "Świetnie. Powtarzaj to sobie jeszcze kilka razy, albo lepiej zapisz to gdzieś. Gdy wspomnisz hasło kapitanowi lugra, skrzynie z butelkami rumu zostaną załadowane na szalupę, którą następnie popłyniesz do zatoki osady pirackiej Le Francois - tam cię przywitają.\nTo całe zadanie. Możesz przejść z Zatoki Le Francois do Saint Pierre pieszo - szalupa zostanie w zatoce. Zapłacę pięć tysięcy sztuk srebra, gdy to będzie zrobione.";
			link.l1 = "Przemyt brzmi zarówno ekscytująco, jak i dochodowo. Zrobię, co mi powiedziałeś. Gdzie jest szalupa?";
			link.l1.go = "Sharlie_rum_3";
			link.l2 = "Więc proponujesz, żebym zajął się przemytem? Hm... Wiesz, nie mogę ryzykować swojego imienia. Musisz mi wybaczyć, udawajmy, że nic nie słyszałem.";
			link.l2.go = "Sharlie_rum_exit";
		break;
		
		case "Sharlie_rum_exit":
			dialog.text = "Jak sobie życzysz, monsieur. Nie mam żadnych innych zadań.";
			link.l1 = "Rozumiem. W takim razie wszystkiego najlepszego, "+npchar.name+".";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Sharlie.Rum");
			SetCurrentTime(23, 0);
			Sharlie_removeLocks("");
		break;
		
		case "Sharlie_rum_3":
			dialog.text = "Szalupa będzie przy nabrzeżu o siódmej wieczorem. Załoga na szalupie jest doświadczona, więc powinieneś szybko dotrzeć do lugra. Całe zadanie nie powinno zająć więcej niż cztery godziny - jestem pewien, że wrócisz do Saint Pierre do jedenastej wieczorem. Weź tę lunetę, to kawał śmiecia, ale lepsze to niż nic. Plaża Lamanten znajduje się na północnej części wyspy, więc opuszczając port, trzymaj kurs na północ. Powodzenia!";
			link.l1 = "Dobrze, zrozumiałem. Do zobaczenia wkrótce, "+npchar.name+"!";
			link.l1.go = "Sharlie_rum_4";
		break;
		
		case "Sharlie_rum_4":
			DialogExit();
			AddQuestRecord("SharlieB", "1");
			AddQuestUserData("SharlieB", "sPassword", pchar.questTemp.Sharlie.Rum.Pass);
			GiveItem2Character(pchar, "spyglass1"); 
			Log_Info("You've received a spyglass");
			PlaySound("interface\important_item.wav");
			if(CheckAttribute(pchar, "questTemp.Sharlie.FastStart"))
			{
				GiveItem2Character(pchar, "map_martiniqua");
				Log_Info("You have received a map of Martinique");
				RefreshEquippedMaps(GetMainCharacter());
			}
			/* pchar.quest.Sharlie_rum.win_condition.l1 = "location";
			pchar.quest.Sharlie_rum.win_condition.l1.location = "Fortfrance_town"; */
			//pchar.quest.Sharlie_rum.win_condition.l1.locator_group = "rld";
			//pchar.quest.Sharlie_rum.win_condition.l1.locator = "loc0";
			pchar.quest.Sharlie_rum.win_condition.l1 = "HardHour";
			pchar.quest.Sharlie_rum.win_condition.l1.hour = 19.00;
			pchar.quest.Sharlie_rum.function = "Rum_CreateBarkas";
			SetFunctionTimerCondition("Rum_CreateBarkasOver", 0, 0, 1, false);
			pchar.questTemp.Sharlie.Rum = "true";
			npchar.quest.Rum = "true";
			NewGameTip("Open your inventory (F1) and equip the spyglass.");
			pchar.quest.NgtBarkas.win_condition.l1 = "location";
			pchar.quest.NgtBarkas.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.NgtBarkas.win_condition.l2 = "HardHour";
			pchar.quest.NgtBarkas.win_condition.l2.hour = 19.00;
			pchar.quest.NgtBarkas.function = "NgtBarkas";
			AddTimeToCurrent(1,30);
			QuestPointerDelLoc("fortfrance_town", "reload", "reload4_back");
			QuestPointerToLoc("fortfrance_town", "reload", "reload1_back");
		break;
		
		case "Sharlie_rum_5":
			dialog.text = "Świetnie! Wiedziałem, że mogę na Ciebie liczyć. Czy było trudno?";
			link.l1 = "Cóż, to zależy od tego, jak zdefiniujesz trudne...";
			link.l1.go = "Sharlie_rum_6";
		break;
		
		case "Sharlie_rum_6":
			dialog.text = "Cóż, oto twoja nagroda: pięć tysięcy pesos. Możesz zatrzymać lunetę. A także, kolejny mały podarunek, proszę, weź te trzy butelki rumu. Kiedy spróbujesz, zrozumiesz, dlaczego jest na niego takie zapotrzebowanie.";
			link.l1 = "Dziękuję! Miło było z tobą współpracować! Do zobaczenia później!";
			link.l1.go = "Sharlie_rum_7";
		break;
		
		case "Sharlie_rum_7":
			DialogExit();
			AddMoneyToCharacter(pchar, 5000);
			TakeNItems(pchar, "potionrum", 3);
			AddQuestRecord("SharlieB", "5");
			CloseQuestHeader("SharlieB");
			DeleteAttribute(pchar, "questTemp.Sharlie.Rum");
			// Rebbebion, новые марки до места назначения
			QuestPointerDelLoc("lefransua_town", "reload", "gate_back");
			QuestPointerDelLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerDelLoc("fortfrance_town", "reload", "reload4_back");
			DelLandQuestMark(npchar);
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Gigolo"))
			{
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1 = "Hour";
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.start.hour = 6.00;
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.finish.hour = 22.00;
				pchar.quest.Sharlie_CreatShipyardMarker.function = "Sharlie_CreatShipyardMarker";
			}
		break;
		//<-- Бремя гасконца
		
		//Португалец
		case "Portugal":
			dialog.text = "Nie ma sprawy, mam pokój. Za 50 pesos jest twój na trzy dni.";
			if (sti(pchar.money) >= 50)
			{
				link.l1 = "Oto masz.";
				link.l1.go = "Portugal_1";
			}
			else
			{
				link.l1 = "Pójdę po pieniądze do skarbnika i wrócę.";
				link.l1.go = "exit";
			}
		break;
		
		case "Portugal_1":
			ref sld;
			DialogExit();
			AddMoneyToCharacter(pchar, -50);
			npchar.quest.Portugal = "true";
			LocatorReloadEnterDisable("Fortfrance_tavern", "reload2_back", false);
			pchar.quest.Portugal_Ill3.over = "yes";
			LocatorReloadEnterDisable("Fortfrance_town", "reload1_back", true);
			LocatorReloadEnterDisable("Fortfrance_town", "reload2_back", true);
			LocatorReloadEnterDisable("Fortfrance_town", "gate_back", true);//закрыть выходы из города
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern_upstairs", "goto", "goto3");
			sld = characterFromId("PortugalDoctor");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern_upstairs", "goto", "goto1");
			pchar.quest.Portugal_tavernroom.win_condition.l1 = "location";
			pchar.quest.Portugal_tavernroom.win_condition.l1.location = "FortFrance_tavern_upstairs";
			pchar.quest.Portugal_tavernroom.function = "PortugalInTavernRoom";
		break;
		
		case "Portugal_2":
			dialog.text = "Nie powiedziałbym, że sam wstał i opuścił pokój, monsieur. Wczoraj przyszli tu jacyś ludzie. Jeden z nich był wysoki, chudy, jednooki mężczyzna - na pierwszy rzut oka bandyta, a drugi sepleniący, wyglądał jak Kastylijczyk. Byłem po prostu zaskoczony, ale ten sepleniący spojrzał na mnie... jak na wszy przed zmiażdżeniem. I tak pytali o twojego przyjaciela... a ja im powiedziałem. Cóż innego miałem zrobić?";
			link.l1 = "Wiem, "+npchar.name+", nie jesteś bohaterem, to prawda. Co jeszcze widziałeś? Dokąd poszli?";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			dialog.text = "To wszystko... czekaj, nie! Poczekaj, jednooki powiedział coś o wozie. Chyba wzięli wóz i przeciągnęli twojego przyjaciela na drugą stronę wyspy. To wszystko monsieur, przysięgam... Zawołałbym straż, ale ten sepleniący powiedział mi przed odejściem, że mam piękną żonę... Widzisz? Jeśli się dowiedzą, że ci to wszystko powiedziałem, to oni...";
			if (pchar.money >= 1000)
			{
				link.l1 = "Nie bój się, nic nie usłyszą ode mnie oprócz kul. Naprawdę mi pomogłeś, dziękuję. Proszę, weź 1000 pesos jako nagrodę.";
				link.l1.go = "Portugal_4";
			}
			link.l2 = "To nie dużo, ale dziękuję mimo wszystko. Następnym razem zawołaj straż i nie bądź taka gąska.";
			link.l2.go = "Portugal_5";
		break;
		
		case "Portugal_4":
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "Dziękuję, monsieur. Mogę dać słowo, że twój przyjaciel prawie wyzdrowiał. Przynajmniej chodził samodzielnie. A ten jeden człowiek, ten cichy Holender, wszedł z zewnątrz w tym momencie, zobaczył całe to zamieszanie i wyskoczył na zewnątrz, po prostu zniknął potem.";
			link.l1 = "Rzekłbym, że już odpłynął na pierwszym statku, jaki mógł złapać. Dzięki za informację, czas, abym ruszył w drogę.";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_5":
			dialog.text = "Nie każdy człowiek może być bohaterem z mieczem w pochwie, kapitanie.";
			link.l1 = "No cóż... to wybór tego człowieka.";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_6":
			DialogExit();
			sld = characterFromId("Avendel");
			sld.dialog.currentnode = "Avendel_seapatrol_9";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		//Португалец
		
		// Jason Долго и счастливо
		case "LH_tavern_SP":
			npchar.quest.LongHappy = "true";
			dialog.text = "Tak, twoja asystentka tu była, ale powiedziałem jej i powtórzę tobie - przyzwyczaiłem się do tłumów pijanych marynarzy, ale wiem, jak wyglądają twoje zabawy. To, co zostanie, będzie wyglądać jak Antwerpia po wizycie hiszpańskich tercji. Będę szczęśliwy, jeśli ściany nadal będą stały. Więc, jeśli chcesz, aby tłumy się biły, będę potrzebował bezzwrotnej zaliczki ponad to, co już przyniosłeś. Na wypadek konsekwencji, że tak powiem.";
			link.l1 = "Ty chytry lisie! Sam piłem z morskimi wilkami przez wiele lat, bywałem w różnych... przybytkach, i wiem, że za te pieniądze, które przyniosłem, moglibyśmy zbudować twoją tawernę od nowa! Wykorzystujesz okazję, co? Dobrze, mam wesele, i nie mam ochoty przejmować się takimi drobnostkami - ile chcesz?";
			link.l1.go = "LH_tavern_SP_1";
		break;
		
		case "LH_tavern_SP_1":
			dialog.text = "Jeszcze 100 000 sztuk srebra powinno wystarczyć i nie martw się - zrobię wszystko w najlepszy możliwy sposób. Twoi chłopcy będą pamiętać tę zabawę przez długi czas, pamiętaj moje słowo!";
			if (sti(Pchar.money) >= 100000+sti(pchar.questTemp.LongHappy.MarryMoney))
			{
				link.l1 = "Musisz się naprawdę postarać - to wyjątkowa okazja, zrozumiesz. I tak, po świętowaniu, nie przychodź do mnie z zażaleniami, nawet jeśli twoja tawerna spłonie.";
				link.l1.go = "LH_tavern_SP_4";
			}
			else
			{
				link.l1 = "Już czuję się, jakbym organizował królewskie wesele! Czekaj, zaraz wrócę.";
				link.l1.go = "LH_tavern_SP_2";
			}
		break;
		
		case "LH_tavern_SP_2":
			DialogExit();
			npchar.quest.LongHappy.Nomoney = "true";
		break;
		
		case "LH_tavern_SP_3":
			dialog.text = "Twoi chłopcy będą wspominać tę zabawę przez długi czas, pamiętaj moje słowo!";
			link.l1 = "Musisz się naprawdę postarać - to wyjątkowa okazja, rozumiesz. Nie przychodź do mnie z płaczem, jeśli moi chłopcy przypadkiem spalą twoją tawernę.";
			link.l1.go = "LH_tavern_SP_4";
		break;
		
		case "LH_tavern_SP_4":
			DialogExit();
			RemoveCharacterGoods(pchar, GOOD_RUM, sti(pchar.questTemp.LongHappy.MarryRum));
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.LongHappy.MarryMoney));
			AddMoneyToCharacter(pchar, -100000);
			DeleteAttribute(npchar, "quest.LongHappy.Nomoney");
			pchar.questTemp.LongHappy.DrinkReady = "true";
			pchar.questTemp.LongHappy.MarrySP = "true";
			DeleteAttribute(pchar, "questTemp.LongHappy.MarryMoney");
			DeleteAttribute(pchar, "questTemp.LongHappy.MarryRum");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

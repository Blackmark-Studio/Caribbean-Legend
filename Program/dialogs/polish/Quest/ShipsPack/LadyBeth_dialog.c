void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
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
			dialog.text = "Czego panu potrzeba?";
			link.l1 = "Niczego.";
			link.l1.go = "exit";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "AlonsoNaPalube":
			if (CheckAttribute(pchar, "questTemp.LadyBeth_AlonsoNaPalube"))
			{
				pchar.questTemp.LadyBeth_AlonsoNaPalube2 = true;
				dialog.text = "Pańska decyzja, kapitanie? Może nie warto?";
				link.l1 = "Udało ci się zebrać więcej ochotników do sprawy?";
				link.l1.go = "AlonsoNaPalube_StrongGroup";
			}
			else
			{
				pchar.questTemp.LadyBeth_AlonsoNaPalube = true;
				dialog.text = "Kapitanie, słowo na osobności.";
				link.l1 = "Mów, Alonso.";
				link.l1.go = "AlonsoNaPalube_2";
			}
			locCameraFromToPos(-10.33, 9.69, -22.16, true, -5.22, 7.19, -21.06);
		break;
		
		case "AlonsoNaPalube_2":
			dialog.text = "Załoga chce wiedzieć, jakie macie plany wobec Kajmanu. Ludzie się niepokoją.";
			link.l1 = "Jeszcze nie zdecydował"+GetSexPhrase("em","am")+". A dlaczego ludzie się niepokoją, Alonso?";
			link.l1.go = "AlonsoNaPalube_3";
		break;
		
		case "AlonsoNaPalube_3":
			dialog.text = "Ta wyspa to włości kapitana Blackwooda. Marynarze mówią, że jak opętany przekopuje ją wzdłuż i wszerz. Że w czasie wykopalisk stracił dziesiątki ludzi... A ci, którzy od niego odeszli, opowiadają dziwne rzeczy.";
			link.l1 = "Jakie rzeczy?";
			link.l1.go = "AlonsoNaPalube_4";
		break;
		
		case "AlonsoNaPalube_4":
			dialog.text = "Że Blackwood to już nie ten sam człowiek, co dawniej. Że jest opętany poszukiwaniem jakiegoś skarbu konkwistadorów. Że gotów jest poświęcić wszystko i wszystkich, by go zdobyć. Kapitanie, dobrze wiemy, jak bardzo lubisz wplątywać się w te piękne historie, schodzić samemu na ląd i wpadać w pułapki... Ale z tej nie wyjdziesz.";
			link.l1 = "Dziękuję za meldunek i ostrzeżenie. Jeśli mimo to zdecyduję się na desant, wezmę ze sobą awangardę i oddział naszych najlepszych ludzi.";
			link.l1.go = "AlonsoNaPalube_5";
		break;
		
		case "AlonsoNaPalube_5":
			dialog.text = "Z tym mogą być trudności, kapitanie. Abordaż to jedno, ale na lądzie pchać się pod kule piechoty morskiej i szable wszelkiego motłochu, którego, jak mówią, Blackwood zaciągnął z każdego kąta Małych Antyli - to już zupełnie co innego. No i o Kajmanie krążą mrożące krew w żyłach plotki... Niewielu ochotników zgłosi się na taką wyprawe.";
			link.l1 = "Trzeba będzie poradzić sobie z tymi, których mamy. Twoja obecność jest wymagana, Alonso.";
			link.l1.go = "AlonsoNaPalube_LiteGroup";
			link.l2 = "Moim zdaniem już udowodnił"+GetSexPhrase("em","am")+" wam wszystko, co było do udowodnienia. Wszyscy dobrzy wojownicy i strzelcy idą ze mną. To rozkaz.";
			link.l2.go = "AlonsoNaPalube_StrongGroup";
			link.l3 = "Hm... Muszę to przemyśleć. Być może wrócimy do tej rozmowy później.";
			link.l3.go = "AlonsoNaPalube_Exit";
		break;

		
		case "AlonsoNaPalube_Exit":
			SetFunctionLocationCondition("LadyBeth_CaimanSea", "Caiman", false);
			EndQuestMovie();
			bQuestDisableMapEnter = false;
			chrDisableReloadToLocation = false;
			if(UnloadLocation(loadedLocation) == true)
			{
				pchar.Ship.Pos.x = 0;
				pchar.Ship.Pos.z = 0;
				pchar.Ship.Ang.y = 0;
				Land_MapLoad();
				pchar.location = "";
			}
		break;
		
		case "AlonsoNaPalube_LiteGroup":
			dialog.text = "Wedle rozkazu, kapitanie.";
			link.l1 = "A co z okrętem Blackwooda? Nie sprawi nam kłopotów?";
			link.l1.go = "AlonsoNaPalube_Vpered";
			pchar.questTemp.LadyBeth_LiteGroup = true;
		break;
		
		case "AlonsoNaPalube_StrongGroup":
			if (GetSummonSkillFromName(pchar, SKILL_Leadership) >= 50 || sti(pchar.rank) >= 17)
			{
				dialog.text = "Tak jest, kapitanie!";
				link.l1 = "A co z okrętem Blackwooda? Nie sprawi nam kłopotów?";
				link.l1.go = "AlonsoNaPalube_Vpered";
				pchar.questTemp.LadyBeth_StrongGroup = true;
				if (GetSummonSkillFromName(pchar, SKILL_Leadership) >= 50) notification("Sprawdzenie umiejętności zaliczone", SKILL_Leadership);
				if (sti(pchar.rank) >= 17) notification("Sprawdzenie poziomu zakończone sukcesem", "None");
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LadyBeth_AlonsoNaPalube2"))
				{
					dialog.text = "Obawiam się, że nie, kapitanie.";
				}
				else
				{
					dialog.text = "Nie ma Pan nic do udowodnienia - ani mnie, ani swoim oficerom. Pójdziemy tam, dokąd Pan rozkaże, ale zwykły marynarz myśli inaczej. Obawiam się, że mogą pojawić się problemy, kapitanie.";
				}
				link.l1 = "Trzeba będzie poradzić sobie z tymi, których mamy. Twoja obecność jest wymagana, Alonso.";
				link.l1.go = "AlonsoNaPalube_LiteGroup";
				link.l2 = "Hm... Muszę to przemyśleć. Być może wrócimy do tego pytania później.";
				link.l2.go = "AlonsoNaPalube_Exit";
				if (GetSummonSkillFromName(pchar, SKILL_Leadership) < 50) notification("Umiejętność niewystarczająco rozwinięta (50)", SKILL_Leadership);
				if (sti(pchar.rank) < 17) notification("Wymagany poziom 17", "None");
			}
		break;
		
		case "AlonsoNaPalube_Vpered":
			dialog.text = "Wątpliwa sprawa. Mówią, że ten Snow to prawdziwa piękność z groźnym temperamentem. Nie martwiłbym się o nią. Cała załoga zapewne haruje jak przeklęta na lądzie, podczas gdy statek jest bezpiecznie ukryty w załamaniach linii brzegowej. Gdy, i jeśli, wygramy, będziemy mogli ją wziąć jako trofeum.";
			link.l1 = "Zbierz ludzi. Dziś jest dobry dzień - fortuna będzie po naszej stronie.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_AlonsoNaPalube_Vpered");
		break;
		
		// Диалог в таверне с Блеквудом
		case "LadyBeth_DialogInCity": // главное меню
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Fourth"))
			{
				dialog.text = "Miło pana widzieć, kapitanie. Wydaje mi się, że już wszystko omówiliśmy.";
				link.l1 = "Rzeczywiście. Do widzenia.";
				link.l1.go = "exit";
				NextDiag.TempNode = "LadyBeth_DialogInCity_again";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Third"))
			{
				dialog.text = "...";
				link.l1 = ""+TimeGreeting()+", Albercie.";
				link.l1.go = "LadyBeth_DialogInCity_Third_2";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Second"))
			{
				dialog.text = "...";
				link.l1 = ""+TimeGreeting()+", kapitanie Blackwoodzie.";
				link.l1.go = "LadyBeth_DialogInCity_Second_1";
				break;
			}
			if (startHeroType == 4)
			{
				dialog.text = "...";
				link.l1 = "Dzień dobry. Czy Pan jest kapitanem Blackwoodem?";
				link.l1.go = "LadyBeth_DialogInCity_First_Helena_1";
			}
			else
			{
				dialog.text = "...";
				link.l1 = ""+TimeGreeting()+". Czy Pan jest kapitanem Albertem Blackwoodem?";
				link.l1.go = "LadyBeth_DialogInCity_First_1";
			}
		break;
		
		case "LadyBeth_DialogInCity_again": // повтор
			dialog.text = "Miło pana widzieć, kapitanie. Wydaje mi się, że już wszystko omówiliśmy.";
			link.l1 = "Rzeczywiście. Żegnaj.";
			link.l1.go = "exit";
			NextDiag.TempNode = "LadyBeth_DialogInCity_again";
		break;
		
		case "LadyBeth_DialogInCity_First_1": // первый диалог
			dialog.text = "Tak, to ja. A pan?";
			link.l1 = "Kapitan "+GetFullName(pchar)+". Dowodzę statkiem '" + PChar.Ship.Name + "'.";
			link.l1.go = "LadyBeth_DialogInCity_First_2";
		break;
		
		case "LadyBeth_DialogInCity_First_2":
			dialog.text = "Kapitanie... Był pan kiedyś na Kajmanach?";
			link.l1 = "Tylko przepływałem obok.";
			link.l1.go = "LadyBeth_DialogInCity_First_3";
		break;
		
		case "LadyBeth_DialogInCity_First_3":
			dialog.text = "Słyszał pan coś o znajdujących się tam skarbach?";
			link.l1 = "Nie, nic konkretnego.";
			link.l1.go = "LadyBeth_DialogInCity_First_4";
		break;
		
		case "LadyBeth_DialogInCity_First_4":
			dialog.text = "Śladach Hiszpanów? Starej broń? Monet z czasów konkwistadorów?";
			link.l1 = "Niczego takiego nie znalazłem.";
			link.l1.go = "LadyBeth_DialogInCity_First_5";
		break;
		
		case "LadyBeth_DialogInCity_First_5":
			dialog.text = "Lokalnych legend? Opowieści o Cortesie? Coś o grobach?";
			link.l1 = "Przepraszam, kapitanie, ale nie posiadam takich informacji. A to wszystko zaczyna przypominać przesłuchanie.";
			link.l1.go = "LadyBeth_DialogInCity_First_6";
		break;
		
		case "LadyBeth_DialogInCity_First_6":
			dialog.text = "Proszę wybaczyć... Zboczenie zawodowe byłego oficera. Po prostu... to dla mnie niezwykle ważne.";
			link.l1 = "Dlaczego tak bardzo interesuje pana właśnie Kajman?";
			link.l1.go = "LadyBeth_DialogInCity_First_7";
		break;
		
		case "LadyBeth_DialogInCity_First_7":
			dialog.text = "Nieważne. Jeszcze raz proszę o wybaczenie.";
			link.l1 = "Rozumiem. Powodzenia w poszukiwaniach.";
			link.l1.go = "LadyBeth_DialogInCity_First_8";
		break;
		
		case "LadyBeth_DialogInCity_First_8":
			if (GetHour() >= 23 || GetHour() < 6) sStr = "Dobranoc";
			else sStr = "Dobrego dnia";
			dialog.text = "Proszę wpaść, jeśli trafi się coś wartego uwagi. Miło będzie porozmawiać z innym kapitanem... z kimś, kto rozumie morze. Miłego dnia. " + sStr + ".";
			link.l1 = ""+Goodbye()+".";
			link.l1.go = "LadyBeth_DialogInCity_First_9";
		break;
		
		case "LadyBeth_DialogInCity_First_9":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Second = true;
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_1": // первый диалог с Элен
			dialog.text = "We własnej osobie. A pani to... Kapitan Helen McArthur? Protegowana Jana Swensona, prawda? Słyszałem o pani.";
			link.l1 = "Jest pan dobrze poinformowany, kapitanie Blackwood. Nie jestem jednak zdziwiona tym faktem, gdyż każdy angielski oficer zna mnie dość dobrze";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_2";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_2":
			dialog.text = "Były oficer. I wszyscy czerwoni mundurowi znają pani... unikalne przywileje od Korony. Jak to się mówi, pieniądze nie śmierdzą. A historia o tym, jak pani ojciec, Sean McArthur, zabierał panią na morze od dzieciństwa i uczynił kapitanem, stała się legendą we flocie.";
			link.l1 = "I jakie to uczucie spotkać tę legendę?";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_3";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_3":
			dialog.text = "Osobiście jestem pod wrażeniem. Choć przyznam, że wielu moich byłych kolegów to mocno irytuje. Ale by zostać kapitanem, potrzeba czegoś więcej niż tylko szlachetnego pochodzenia czy królewskiego patentu, prawda?";
			link.l1 = "Zgadza się. Potrzeba wiedzy, doświadczenia i ciągłej gotowości do udowadniania swojej kompetencji. Zwłaszcza w moim przypadku.";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_4";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_4":
			dialog.text = "Dokładnie! Na morzu, jak i w życiu, nie liczą się tytuły, lecz rezultaty. Miło mi panią poznać, kapitanie McArthur. Mam nadzieję, że jeszcze się spotkamy. Może wpadnie pani na kieliszek wina, gdy wrócę z wyprawy?";
			link.l1 = "Może. Powodzenia w poszukiwaniach, kapitanie.";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_5_harizma";
			link.l2 = "Nie interesuje mnie to. Ale powodzenia w poszukiwaniach, kapitanie.";
			link.l2.go = "LadyBeth_DialogInCity_First_Helena_5_oruzhie";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_5_harizma":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Second = true;
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_5_oruzhie":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Second = true;
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_DialogInCity_Second_1": // drugi dialog
			dialog.text = "Ach, kapitanie "+pchar.lastname+"! Miło panią widzieć. Usiądzie pani?";
			link.l1 = "Z przyjemnością.";
			link.l1.go = "LadyBeth_DialogInCity_Second_2";
		break;
		
		case "LadyBeth_DialogInCity_Second_2":
			dialog.text = "Kapitanie... proszę powiedzieć, czym dla pana są prawdziwe skarby?";
			link.l1 = "Prawdziwym skarbem jest miłość. Właściwa osoba obok. Nie ma nic gorszego niż być samotnym.";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_love";
			link.l2 = "Pieniądze, oczywiście. Czym innym może być skarb?";
			link.l2.go = "LadyBeth_DialogInCity_Second_3_sokrovisha";
			link.l3 = "Cenne i unikalne wyposażenie. Dobra szpada lub pistolet są warte więcej niż złoto.";
			link.l3.go = "LadyBeth_DialogInCity_Second_3_oruzhie";
			link.l4 = "Wiedza. Najcenniejszym skarbem jest to, co masz w głowie.";
			link.l4.go = "LadyBeth_DialogInCity_Second_3_znania";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love":
			if (startHeroType == 4)
			{
				dialog.text = "Miłość? Hm... Nie spodziewałem się takiej odpowiedzi od córki pirata. Byłem... zaręczony z Elizabeth. Córką plantatora z Barbadosu. Ale jej ojciec... uznał, że nie mam wystarczająco pieniędzy. Co mogłem dać jego córce poza swoją miłością? Miała pani szczęście, kapitanie MacArthur. Pani ojciec cenił pani umiejętności bardziej niż posag.";
				link.l1 = "Może to nie kwestia szczęścia, lecz tego, że prawdziwej miłości nie mierzy się złotem. Mój ojciec to rozumiał. A pańska narzeczona? Czy podziela poglądy swojego ojca?";
				link.l1.go = "LadyBeth_DialogInCity_Second_3_love_Helena_1";
			}
			else
			{
				dialog.text = "Miłość? Tak... Może masz rację. Byłem... byłem zaręczony. Na Barbadosie. Kochaliśmy się, ale... jej ojciec uznał mnie za nieodpowiednią partię. Ha! Zbyt biedną. Dlatego tu jestem - szukam skarbów, by im wszystkim udowodnić. Może na próżno?";
				link.l1 = "Może po prostu powinieneś z nią porozmawiać? Do diabła z tym plantatorem.";
				link.l1.go = "LadyBeth_DialogInCity_Second_3_love_2";
			}
			AddComplexLandExpToScill(100, 100, 0);
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love_2":
			dialog.text = "Porozmawiać... Tak, może. Ale co mam jej powiedzieć? 'Przepraszam, nie mogłem zapewnić ci godnego życia'? Nie. Muszę wrócić jako zwycięzca. Albo nie wracać wcale.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love_Helena_1":
			dialog.text = "Elizabeth? Nie... ona mnie kocha. Ale ja... nie mogłem pozwolić jej żyć w biedzie. Zasługuje na coś lepszego. Muszę udowodnić, że jestem jej godny.";
			link.l1 = "Czasami to duma przeszkadza szczęściu bardziej niż bieda, kapitanie.";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_love_Helena_2";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love_Helena_2":
			dialog.text = "Nie mogę wrócić z pustymi rękami. Po prostu nie mogę. Proszę wybaczyć, mam dużo pracy. Miło było z panią porozmawiać, kapitanie MacArthur.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_5";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_sokrovisha":
			dialog.text = "Jaka banalna odpowiedź. Ale trudno się z nią spierać. Gdy dorasta się w slumsach Bristolu, gdy trzeba walczyć o resztki... zaczyna się rozumieć prawdziwą wartość pieniędzy. To nie luksus. To wolność. Możliwość, by nie wrócić do tego brudu, z którego z takim trudem się wydostałeś.";
			link.l1 = "Zgadzam się. Pieniądze rozwiązują większość problemów. A jeśli nie - to znaczy, że było ich za mało.";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_sokrovisha_2";
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;
		
		case "LadyBeth_DialogInCity_Second_3_sokrovisha_2":
			dialog.text = "Dokładnie! Rozumie pan. Pieniądze nie dają szczęścia, ale ich brak z pewnością daje nieszczęście. Wiem coś o tym...";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_oruzhie":
			dialog.text = "Interesujące. Praktyczne. Mam arkebuzę... prawdziwą, z czasów konkwistadorów. Prezent od pewnego księdza. Czasami myślę, że jest więcej warta niż całe złoto, które znalazłem. Ale... to nie rozwiąże moich problemów.";
			link.l1 = "Dobra broń może rozwiązać wiele problemów. I nigdy cię nie zdradzi.";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_oruzhie_2";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_DialogInCity_Second_3_oruzhie_2":
			dialog.text = "Jest w tym trochę prawdy. Ale niektórych bitew nie da się wygrać siłą oręża.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_znania":
			dialog.text = "Wiedza... Tak, rozumiem. Przestudiowałem wszystko, co mogłem, o konkwistadorach, o skarbach. Sporządziłem cały regulamin poszukiwań skarbów. Wymyśliłem system regularnych ćwiczeń i nagród rzeczowych dla okrętowej kompanii strzeleckiej\nKażdy kapitan chciałby mieć taki regulamin. Ale cała ta wiedza... jest bezużyteczna, jeśli nie prowadzi do rezultatu. Do prawdziwego rezultatu.";
			link.l1 = "Ale to właśnie wiedza pozwala osiągnąć rezultat. Bez niej każde poszukiwanie to tylko błądzenie w ciemności.";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "LadyBeth_DialogInCity_Second_4":
			if (GetHour() >= 23 || GetHour() < 6) sStr = "Cóż, już późno, a ja mam dużo pracy";
			else sStr = "Cóż, mam dużo pracy";
			dialog.text = "" + sStr + ". Dziękuję za rozmowę, kapitanie. To było naprawdę interesujące.";
			link.l1 = "Panu również dziękuję. "+Goodbye()+".";
			link.l1.go = "LadyBeth_DialogInCity_Second_5";
		break;
		
		case "LadyBeth_DialogInCity_Second_5":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Third = true;
		break;
		
		case "LadyBeth_DialogInCity_Third_2": // третий диалог
			dialog.text = "Ach, "+pchar.name+"! Miło pana widzieć. Mam świetne wieści - w końcu znalazłem rozwiązanie swoich problemów. Wkrótce ruszam na wyprawę i tym razem wrócę z prawdziwym skarbem! Przyjacielska rada - trzymaj się z dala od Kajmana. To teraz mój teren.";
			link.l1 = "Kajman nie należy do ciebie, Albercie. Nie masz do niego królewskich praw. To piractwo.";
			link.l1.go = "LadyBeth_DialogInCity_Third_3_harizma";
			link.l2 = "Grozi mi pan, Blackwood?";
			link.l2.go = "LadyBeth_DialogInCity_Third_3_oruzhie";
		break;
		
		case "LadyBeth_DialogInCity_Third_3_harizma":
			dialog.text = "Królewskie prawa? Gdybyś mieszkał w slumsach Bristolu, "+pchar.name+", zrozumiałbyś, ile warte są te papiery. Gdy jesteś głodny, prawo nie znaczy nic. Ale... masz rację. Formalnie nie mam praw do wyspy. Ale znalazłem tam coś, czego szukałem latami. I nie pozwolę nikomu mi tego odebrać.";
			link.l1 = "Mam nadzieję, że wie pan, iż kroczy niebezpieczną ścieżką.";
			link.l1.go = "LadyBeth_DialogInCity_Third_3_harizma_2";
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "LadyBeth_DialogInCity_Third_3_harizma_2":
			dialog.text = "Zawsze wiedziałem, że moja droga nie będzie łatwa. Żegnaj, "+pchar.name+". Może jeszcze się spotkamy.";
			link.l1 = ""+Goodbye()+".";
			link.l1.go = "LadyBeth_DialogInCity_Third_4";
		break;
		
		case "LadyBeth_DialogInCity_Third_3_oruzhie":
			dialog.text = "Grożę? Wcale nie. To tylko przyjacielska rada od jednego kapitana do drugiego. Na Kajmanach jest niebezpiecznie... zwłaszcza dla tych, którzy wtrącają się w moje sprawy.";
			link.l1 = "Zapamiętam tę 'radę'. Powodzenia na Kajmanie.";
			link.l1.go = "LadyBeth_DialogInCity_Third_3_oruzhie_2";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_DialogInCity_Third_3_oruzhie_2":
			dialog.text = "I panu powodzenia, kapitanie. Mam nadzieję, że nie będzie panu potrzebne. Żegnaj.";
			link.l1 = ""+Goodbye()+".";
			link.l1.go = "LadyBeth_DialogInCity_Third_4";
		break;
		
		case "LadyBeth_DialogInCity_Third_4":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Fourth = true;
		break;
		
		// Ловушка, абордаж в каюте
		case "LadyBeth_abordage":
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Second"))
			{
				dialog.text = "Wy?!! Myślicie, że się poddam? Myślicie, że wrócę do nędzy? Wolę zginąć, niż znów głodować w slumsach! Żadnej litości, żadnej nagrody, żadnego zwycięstwa! Pod koją jest beczka z prochem... Wszyscy pójdziemy na dno!";
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("LadyBeth_Lovushka");
			}
			else
			{
				dialog.text = "Kim jesteście, by mnie atakować?! Myślicie, że się poddam? Nie! Wolę zginąć, niż znów głodować w slumsach! Żadnej litości, żadnej nagrody, żadnego zwycięstwa! Pod koją jest beczka z prochem... Wszyscy pójdziemy na dno!";
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("LadyBeth_Lovushka");
			}
		break;
		
		// Блеквуд разговаривает с ГГ перед битвой на Каймане
		case "LadyBeth_BlackWood_Boss":
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Second"))
			{
				dialog.text = "Kapitanie! Przecież ostrzegałem. Teraz zapłacisz za swoją ciekawość.";
			}
			else
			{
				dialog.text = "Kim jesteś i jak śmiesz wkraczać na mój teren?! Ta wyspa należy do mnie!";
			}
			link.l1 = "Zobaczymy, Blackwood. Dziś na świecie będzie o jednego opętanego mniej.";
			link.l1.go = "LadyBeth_BlackWood_Boss_oruzhie_1";
			link.l2 = "Rozwiążmy to pokojowo, Blackwood. Mogę odejść.";
			link.l2.go = "LadyBeth_BlackWood_Boss_torgovlya_1";
			link.l3 = "Blackwood, przecież jest pan rozsądnym człowiekiem! Jest pan oficerem! Nad pańskim obozem powiewa królewska flaga, do diabła! Czy naprawdę nie możemy się dogadać?";
			link.l3.go = "LadyBeth_BlackWood_Boss_harizma_1";
		break;
		
		case "LadyBeth_BlackWood_Boss_oruzhie_1":
			dialog.text = "Opętany? Ha! Jestem po prostu człowiekiem, który wie, czego chce!";
			link.l1 = "...";
			link.l1.go = "LadyBeth_BlackWood_Boss_2";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_BlackWood_Boss_torgovlya_1":
			dialog.text = "Odejść? Po tym, co pan widział? Nie, nie, nie! Nikt nie może się dowiedzieć, co tutaj znalazłem. Nikt!";
			link.l1 = "Daję słowo, że nikomu nie powiem. Przysięgam na honor kapitana.";
			link.l1.go = "LadyBeth_BlackWood_Boss_torgovlya_2";
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;
		
		case "LadyBeth_BlackWood_Boss_torgovlya_2":
			dialog.text = "W tym świecie nie ma honoru, kapitanie. Jest tylko brud, nędza i pogarda. Przykro mi, ale musi pan tu umrzeć.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_BlackWood_Boss_2";
		break;
		
		case "LadyBeth_BlackWood_Boss_harizma_1":
			dialog.text = "Myślałem. Dużo myślałem. I zrozumiałem - to moja jedyna szansa. Albo znajdę złoto Cortésa, albo... nic. Rozumie pan? Nic! Nie wrócę do dawnego życia! Nie wrócę do brudu i nędzy! Lepiej umrzeć tutaj!";
			link.l1 = "...";
			link.l1.go = "LadyBeth_BlackWood_Boss_2";
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "LadyBeth_BlackWood_Boss_2":
			dialog.text = "Do walki! Bullock, Fraser - ładujcie kartacze, jeśli się zbliżą! Hopkins, do ataku!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_CaimanKino_11");
		break;
		
		// Диалоги с офицерами
		case "LadyBeth_Helena_1": // Элен
			dialog.text = "Wszystko w porządku?";
			link.l1 = "Tak, wszystko dobrze. A ty?";
			link.l1.go = "LadyBeth_Helena_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Helena_2":
			dialog.text = "Żyję. Ale te lądowe potyczki to nie dla mnie. Daj mi pokład pod stopami, a rozniosę każdy statek, ale tutaj... dziwne miejsce. Zmusić setkę wilków morskich do zejścia na ląd, machania kilofami, budowania umocnień... Ja bym tak nie potrafiła.";
			link.l1 = "Blackwood potrafił inspirować swoją załogę.";
			link.l1.go = "LadyBeth_Helena_3";
		break;
		
		case "LadyBeth_Helena_3":
			dialog.text = "Słyszałam o nim jeszcze w Blueveldzie. Wielu angielskich marynarzy mówiło o nim z szacunkiem. Najlepszy oficer we flocie, błyskotliwa kariera... i nagle wszystko porzucił, by szukać skarbów.";
			link.l1 = "Co o nim sądzisz?";
			link.l1.go = "LadyBeth_Helena_4";
		break;
		
		case "LadyBeth_Helena_4":
			dialog.text = "Myślę, że przykład Blackwooda dobrze pokazuje ciężar odpowiedzialności, jaką my... to znaczy ty, ponosisz wobec swoich ludzi. Proszę cię, nie zostań takim kapitanem, jakim on się stał.";
			link.l1 = "Postaram się, Eleno.";
			link.l1.go = "LadyBeth_Helena_5";
		break;
		
		case "LadyBeth_Helena_5":
			dialog.text = "Dziękuję, mój kapitanie. Wiem, że ci się uda.";
			link.l1 = "My.";
			link.l1.go = "LadyBeth_Helena_6";
		break;
		
		case "LadyBeth_Helena_6":
			dialog.text = "My.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Helena_7";
		break;
		
		case "LadyBeth_Helena_7":
			DialogExit();
			Return_HelenaOfficer();
		break;
		
		case "LadyBeth_Mary_1": // Мэри
			dialog.text = "Charles... jak tu strasznie.";
			link.l1 = "Wszystko w porządku, Mary? Zachowałaś się jak prawdziwy żołnierz.";
			link.l1.go = "LadyBeth_Mary_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Mary_2":
			dialog.text = "Nie, nie w porządku, tak, co nie. Spójrz na tych ludzi! Pracowali do wyczerpania, żyli w głodzie, umierali na choroby... I po co? Dla złota, które być może nawet nie istnieje.";
			link.l1 = "Blackwood wierzył, że ono tu jest.";
			link.l1.go = "LadyBeth_Mary_3";
		break;
		
		case "LadyBeth_Mary_3":
			dialog.text = "Ten czerwony mundur... dokładnie taki jak mój. Oficer angielski... Wiesz, nagle pomyślałam o rodzicach, tak, co nie. O korzeniach... o tym, czego nigdy nie znałam. Może ja też jestem jedną z takich osób?";
			link.l1 = "Jakich?";
			link.l1.go = "LadyBeth_Mary_4";
		break;
		
		case "LadyBeth_Mary_4":
			dialog.text = "Z tych, którzy szukają czegoś, czego być może w ogóle nie ma. A potem gubią się w tych poszukiwaniach. Ja... chciałabym porozmawiać o tym później, tak, co nie. Kiedy opuścimy to straszne miejsce.";
			link.l1 = "Oczywiście, Mary.";
			link.l1.go = "LadyBeth_Mary_5";
		break;
		
		case "LadyBeth_Mary_5":
			dialog.text = "Najpierw go pochowajmy, dobrze? Nawet jeśli na to nie zasłużył. Dla człowieka, którym kiedyś był.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Mary_6";
		break;
		
		case "LadyBeth_Mary_6":
			DialogExit();
			Return_MaryOfficer();
		break;
		
		case "LadyBeth_Tichingitu_1": // Тичингиту
			dialog.text = "Kapitanie, Tichingitu widzi, że to złe miejsce. Bardzo złe miejsce.";
			link.l1 = "Co masz na myśli?";
			link.l1.go = "LadyBeth_Tichingitu_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Tichingitu_2":
			dialog.text = "Ta wyspa jest teraz przeklęta. Ziemia wchłonęła zbyt wiele krwi i łez. Każdy, kto tu kopie, wdycha to przekleństwo.";
			link.l1 = "Myślisz, że Blackwood był opętany?";
			link.l1.go = "LadyBeth_Tichingitu_3";
		break;
		
		case "LadyBeth_Tichingitu_3":
			dialog.text = "Nie tylko opętany. On był... jak to powiedzieć... pustym naczyniem. Coś do niego weszło i wypchnęło jego duszę. Widziałem coś takiego wcześniej. Gdy szaman mojego plemienia składał ofiarę z człowieka duchom. Ten szaman miał to samo spojrzenie.";
			link.l1 = "Ale co mogło wywołać takie opętanie?";
			link.l1.go = "LadyBeth_Tichingitu_4";
		break;
		
		case "LadyBeth_Tichingitu_4":
			dialog.text = "Człowiek z pustką w środku łatwo przyjmuje cudze myśli. Ktoś znalazł jego słabość i to wykorzystał. Tichingitu prawie żałuje tego człowieka.";
			link.l1 = "Prawie?";
			link.l1.go = "LadyBeth_Tichingitu_5";
		break;
		
		case "LadyBeth_Tichingitu_5":
			dialog.text = "Tak, prawie. Każdy wojownik sam odpowiada za swój wybór. Nawet jeśli demony szepczą mu do ucha.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Tichingitu_6";
		break;
		
		case "LadyBeth_Tichingitu_6":
			DialogExit();
			Return_TichingituOfficer();
		break;
		
		case "LadyBeth_Irons_1": // Томми
			dialog.text = "Cholera, kapitanie! Spójrz tylko na to! Jak za starych, dobrych czasów!";
			link.l1 = "Ty dobrze wiesz, co to wojna na lądzie.";
			link.l1.go = "LadyBeth_Irons_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Irons_2":
			dialog.text = "Przypomniało mi się starcie pod Naseby. Nasze skrzydło kawalerii natknęło się na oddział kawalerzystów Ruperta. Walczyli z taką samą zaciekłością dla swojego króla.";
			link.l1 = "Co sądzisz o Blackwoodzie?";
			link.l1.go = "LadyBeth_Irons_3";
		break;
		
		case "LadyBeth_Irons_3":
			dialog.text = "Ten cały Blackwood był albo geniuszem, albo kompletnym wariatem. Myślę, że jedno i drugie. Wiesz, co mnie dziwi? Jego ludzie. Wielu z nich to byli wojskowi. Nie wyrzutki, ale profesjonaliści. I wszyscy poszli za nim w to szaleństwo. Nawet piechota morska Foxa. Ha! On to się dzisiaj ucieszy z rzezi! Nigdy im nie wybaczył dezercji.";
			link.l1 = "Może chodziło o pieniądze?";
			link.l1.go = "LadyBeth_Irons_4";
		break;
		
		case "LadyBeth_Irons_4":
			dialog.text = "Nie, tu było coś więcej. Ten facet miał nad nimi władzę. Prawdziwą władzę. I słyszałem, że był zaręczony z jakąś bogatą panną z Barbadosu. Dziwne, że jej nie poślubił, mając już te wszystkie skarby. Typowy żołnierz  nie wiedział, kiedy skończyć wojnę.";
			link.l1 = "Dzięki, Tommy. Z ciebie prawdziwy myśliciel.";
			link.l1.go = "LadyBeth_Irons_5";
		break;
		
		case "LadyBeth_Irons_5":
			dialog.text = "Co?";
			link.l1 = "Nic.";
			link.l1.go = "LadyBeth_Irons_6";
		break;
		
		case "LadyBeth_Irons_6":
			DialogExit();
			Return_IronsOfficer();
		break;
		
		case "LadyBeth_Knippel_1": // Книппель
			dialog.text = "Jakże gorzko na to patrzeć, kapitanie. Do czego my doszliśmy?!";
			link.l1 = "My?";
			link.l1.go = "LadyBeth_Knippel_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Knippel_2":
			dialog.text = "Brytyjska flota! Proszę spojrzeć - małe punkciki czerwonych mundurów leżące wśród tych martwych wyrzutków!";
			link.l1 = "Niektórzy z tych ‘wyrzutków’ to nasi ludzie, Charlie. Rozumiem, co czujesz, ale...";
			link.l1.go = "LadyBeth_Knippel_3";
		break;
		
		case "LadyBeth_Knippel_3":
			dialog.text = "Do diabła z tym, sir.";
			link.l1 = "Rozumiem twoje uczucia, ale lepiej skieruj swój gniew i rozczarowanie na Blackwooda. To on zdezerterował z twojej ukochanej angielskiej floty i przyprowadził ich tutaj.";
			link.l1.go = "LadyBeth_Knippel_4";
			link.l2 = "Racja. Chodźmy, dzień się jeszcze nie skończył.";
			link.l2.go = "LadyBeth_Knippel_6";
		break;
		
		case "LadyBeth_Knippel_4":
			dialog.text = "Oni tylko podążali za swoim dowódcą!";
			link.l1 = "Tak jak za Fleetwoodem?";
			link.l1.go = "LadyBeth_Knippel_5";
			link.l2 = "Racja. Chodźmy, dzień się jeszcze nie skończył.";
			link.l2.go = "LadyBeth_Knippel_6";
		break;
		
		case "LadyBeth_Knippel_5":
			dialog.text = "Tak jak za panem!";
			link.l1 = "Mam nadzieję, że okażę się lepszym kapitanem niż Blackwood i Fleetwood. Chodźmy, dzień się jeszcze nie skończył.";
			link.l1.go = "LadyBeth_Knippel_6";
		break;
		
		case "LadyBeth_Knippel_6":
			dialog.text = "Tak jest, kapitanie. A jak się skończy - będę pił, aż skończy się następny.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Knippel_7";
		break;
		
		case "LadyBeth_Knippel_7":
			DialogExit();
			Return_KnippelOfficer();
		break;
		
		case "LadyBeth_Alonso_1": // Алонсо
			dialog.text = "Madre de Dios, kapitanie! Wszystko w porządku?";
			link.l1 = "To się jeszcze okaże. Ilu ludzi straciliśmy?";
			link.l1.go = "LadyBeth_Alonso_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Alonso_2":
			dialog.text = "Zabici? W tej awanturze straciliśmy "+sti(pchar.SailorDiedInBattleInfo)+" ludzi. Nie chcę być natrętny, kapitanie, ale... przecież ostrzegałem!";
			link.l1 = "Przemilczę ten komentarz, bo dziś się wykazałeś, Alonso. Skąd u ciebie tyle talentów?";
			link.l1.go = "LadyBeth_Alonso_3";
		break;
		
		case "LadyBeth_Alonso_3":
			dialog.text = "Pewnego dnia opowiem ci tę historię, kapitanie - o ile dożyjemy.";
			link.l1 = "Masz jeszcze jakieś rady dla mnie?";
			link.l1.go = "LadyBeth_Alonso_4";
		break;
		
		case "LadyBeth_Alonso_4":
			dialog.text = "Gdyby tu naprawdę był skarb, już dawno by go znaleźli. Ale mimo to powinniśmy przeszukać wyspę i znaleźć ocalałych, a potem zdecydować, co z nimi zrobić. No i nie zapominajmy o statku Blackwooda - słyszałem same dobre rzeczy o tej pięknej szniawie. Szkoda byłoby przegapić taki łup, kapitanie. Oczywiście tylko przekazuję stanowisko załogi w tej sprawie.";
			link.l1 = "Ależ oczywiście. Chodźmy. Łupy czekają!";
			link.l1.go = "LadyBeth_Alonso_5";
		break;
		
		case "LadyBeth_Alonso_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		break;
		
		// Диалог с матросом в гроте Каймана
		case "LadyBeth_MatrosyInGrot":
			dialog.text = "Nie strzelajcie! Poddajemy się!";
			link.l1 = "Kim jesteście?";
			link.l1.go = "LadyBeth_MatrosyInGrot_2";
		break;
		
		case "LadyBeth_MatrosyInGrot_2":
			dialog.text = "My... my jesteśmy z 'Lady Beth'. Załoga kapitana Blackwooda. Czy on... czy on żyje?";
			link.l1 = "Nie. Wasz kapitan nie żyje.";
			link.l1.go = "LadyBeth_MatrosyInGrot_3";
		break;
		
		case "LadyBeth_MatrosyInGrot_3":
			dialog.text = "Więc to koniec... Dzięki Bogu.";
			link.l1 = "Nie wyglądacie na tych, którzy opłakują swojego kapitana.";
			link.l1.go = "LadyBeth_MatrosyInGrot_4";
		break;
		
		case "LadyBeth_MatrosyInGrot_4":
			dialog.text = "Pan nie rozumie. Blackwood był wielkim człowiekiem. Najlepszym kapitanem, jakiego znałem. Ale w ostatnich miesiącach... zmienił się. Stał się opętany, okrutny. Kazał nam pracować dniami i nocami, szukać czegoś, co może wcale nie istnieje.";
			link.l1 = "Biorę was do swojej załogi. Potrzebujemy doświadczonych marynarzy.";
			link.l1.go = "LadyBeth_MatrosyInGrot_PlusKomanda";
			link.l2 = "Biada pokonanym, chłopaki. Teraz jesteście w mojej mocy. Macie szczęście. Jeśli dotrwacie, traficie na jakąś plantację na Barbadosie.";
			link.l2.go = "LadyBeth_MatrosyInGrot_PlusRaby";
		break;
		
		case "LadyBeth_MatrosyInGrot_PlusKomanda":
			dialog.text = "Naprawdę? Nie boi się pan, że... że coś z nami nie tak po tym wszystkim?";
			link.l1 = "Każdy zasługuje na drugą szansę.";
			link.l1.go = "LadyBeth_MatrosyInGrot_PlusKomanda_1";
		break;
		
		case "LadyBeth_MatrosyInGrot_PlusKomanda_1":
			dialog.text = "Dziękuję, kapitanie. Przysięgam, nie pożałuje pan. Jesteśmy dobrymi marynarzami. I... może teraz koszmary się skończą.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Grot_MatrosySdautsya_2");
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			pchar.Ship.Crew.Quantity = sti(pchar.ship.Crew.Quantity) + 30;
		break;
		
		case "LadyBeth_MatrosyInGrot_PlusRaby":
			dialog.text = "Dziękujemy, dziękujemy! Przynajmniej będziemy żyć. Zabierzcie nas stąd, proszę. Ta wyspa... wygląda jak przeklęta.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Grot_MatrosySdautsya_2");
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			SetCharacterGoods(pchar, GOOD_SLAVES, GetCargoGoods(pchar, GOOD_SLAVES)+30);
		break;
		
		case "LadyBeth_MatrosyInGrot_exit":
			DialogExit();
			for (i=1; i<=8; i++)
			{
				sld = CharacterFromID("LadyBeth_MatrosyPryachutsya_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", 5);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
		break;
		
		// Диалог с матросом на Леди Бет
		case "LadyBeth_EnemyMatros_1":
			dialog.text = "Co do diabła?! Jak śmieliście zaatakować 'Lady' i zabić Jeremy’ego? Nie wyjdziecie stąd żywi, dranie, kapitan wróci i...";
			link.l1 = "Wasz kapitan nie żyje. Jeremy strzelił pierwszy, a waszą 'Lady' biorę jako prawowity, krwią opłacony łup.";
			link.l1.go = "LadyBeth_EnemyMatros_2";
		break;
		
		case "LadyBeth_EnemyMatros_2":
			dialog.text = "Kapitan... nie żyje? Kłamiesz, psie! Nie jesteś wart nawet guzika z jego munduru!";
			link.l1 = "Jeśli ten mundur coś znaczył, to dla tego dawnego Blackwooda. Decydujcie - walczycie za trupa czy ratujecie swoje życie.";
			link.l1.go = "LadyBeth_EnemyMatros_3";
		break;
		
		case "LadyBeth_EnemyMatros_3":
			if (CharacterIsHere("Helena"))
			{
				StartInstantDialog("Helena", "LadyBeth_EnemyMatros_Helena_1", "Quest\ShipsPack\LadyBeth_dialog.c");
				break;
			}
			if (CharacterIsHere("Knippel"))
			{
				StartInstantDialog("Knippel", "LadyBeth_EnemyMatros_Knippel_1", "Quest\ShipsPack\LadyBeth_dialog.c");
				break;
			}
			if (CharacterIsHere("Irons"))
			{
				StartInstantDialog("Irons", "LadyBeth_EnemyMatros_Irons_1", "Quest\ShipsPack\LadyBeth_dialog.c");
				break;
			}
			dialog.text = "Nie oddamy wam statku bez walki!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Bitva");
		break;
		
		case "LadyBeth_EnemyMatros_Helena_1":
			dialog.text = "Posłuchajcie, chłopaki. Wierność waszemu kapitanowi zasługuje na szacunek. Ale on nie żyje, a wy macie wybór. Możecie zacząć od nowa. Dajemy wam taką szansę.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_EnemyMatros_5";
			CharacterTurnByChr(npchar, CharacterFromID("LadyBeth_CrewOfShip_7"));
		break;

		case "LadyBeth_EnemyMatros_Knippel_1":
			dialog.text = "Kapitanie, ci ludzie nie są naszymi wrogami. Wykonywali rozkazy. Wielu z nich służyło we flocie królewskiej – są zdyscyplinowani, znają się na rzeczy. Byłoby głupotą nie wykorzystać ich umiejętności. Panowie, byłem kiedyś na waszym miejscu. Zaufałem właściwej stronie – zróbcie to samo.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_EnemyMatros_5";
		break;

		case "LadyBeth_EnemyMatros_Irons_1":
			dialog.text = "No, chłopcy! Sprawa prosta: możecie zostać w ładowni jako jeńcy, możecie dołączyć do naszej załogi z racją i żołdem... albo... (przesuwa palcem po gardle) Sam wiecie. Ja na waszym miejscu wiedziałbym, co wybrać.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_EnemyMatros_10";
			CharacterTurnByChr(npchar, CharacterFromID("LadyBeth_CrewOfShip_7"));
		break;

		case "LadyBeth_EnemyMatros_5":
			StartInstantDialog("LadyBeth_CrewOfShip_7", "LadyBeth_EnemyMatros_6", "Quest\ShipsPack\LadyBeth_dialog.c");
		break;

		case "LadyBeth_EnemyMatros_6":
			dialog.text = "...";
			link.l1 = "Zostaniecie częścią mojej załogi.";
			link.l1.go = "LadyBeth_EnemyMatros_7";
			link.l2 = "Biada pokonanym, chłopaki. Teraz jesteście w mojej mocy. Macie szczęście. Jeśli dotrwacie - traficie na jakąś plantację na Barbadosie.";
			link.l2.go = "LadyBeth_EnemyMatros_9";
		break;
		
		case "LadyBeth_EnemyMatros_7":
			dialog.text = "Bierze nas pan do swojej załogi? Po tym wszystkim?";
			link.l1 = "Dobrzy marynarze są zawsze w cenie. A kapitan Blackwood miał oko do ludzi.";
			link.l1.go = "LadyBeth_EnemyMatros_8";
		break;

		case "LadyBeth_EnemyMatros_8":
			dialog.text = "Dziękujemy, kapitanie. Nie zawiedziemy pana.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Vnutri_1");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			pchar.Ship.Crew.Quantity = sti(pchar.ship.Crew.Quantity) + 12;
		break;
		
		case "LadyBeth_EnemyMatros_9":
			dialog.text = "Cóż... przynajmniej tylko tak mogła się skończyć ta awantura. Wybacz nam, kapitanie Blackwood. Nie uchroniliśmy cię.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Vnutri_1");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			SetCharacterGoods(pchar, GOOD_SLAVES, GetCargoGoods(pchar, GOOD_SLAVES)+12);
		break;

		case "LadyBeth_EnemyMatros_10":
			StartInstantDialog("LadyBeth_CrewOfShip_7", "LadyBeth_EnemyMatros_11", "Quest\ShipsPack\LadyBeth_dialog.c");
		break;

		case "LadyBeth_EnemyMatros_11":
			dialog.text = "Nie oddamy wam statku bez walki!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Bitva");
		break;
		
		// Диалог с Элизабет Бишоп
		case "LadyBeth_Elizabeth_1":
			dialog.text = "...";
			link.l1 = "Przepraszam. Czy jesteś Elizabeth?";
			if (pchar.sex == "man") link.l1.go = "LadyBeth_Elizabeth_2";
			if (pchar.sex == "woman") link.l1.go = "LadyBeth_Elizabeth_Woman_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Elizabeth_2":
			dialog.text = "Tak, to ja. A pan to kto?";
			link.l1 = "Kapitan "+GetFullName(pchar)+". Znałem... Alberta Blackwooda.";
			link.l1.go = "LadyBeth_Elizabeth_3";
		break;

		case "LadyBeth_Elizabeth_3":
			dialog.text = "Mojego Alberta? Boże... Czy z nim wszystko w porządku?";
			link.l1 = "Niestety nie. Zginął w walce. Walczył do samego końca.";
			link.l1.go = "LadyBeth_Elizabeth_4";
		break;

		case "LadyBeth_Elizabeth_4":
			dialog.text = "Ja... domyślałam się. Tyle lat bez żadnych wiadomości... Wie pan, naprawdę na niego czekałam. Długo czekałam. Ojciec mówił, że Albert musi tylko poczekać na awans. Gubernator już wszystko ustalił, to była kwestia kilku miesięcy. Ale Albert... on zrozumiał to inaczej. Powiedział, że wróci bogaty, godny mojej ręki. I odszedł. Po prostu... odszedł.";
			link.l1 = "Myślał o pani do samego końca.";
			link.l1.go = "LadyBeth_Elizabeth_5";
		break;

		case "LadyBeth_Elizabeth_5":
			dialog.text = "Jakże to było głupie. Nie potrzebowałam jego skarbów. Kochałam jego, nie jego pieniądze. Byłam gotowa uciec z nim... ale on był taki dumny. Czekałam na list, wiadomość... A potem przyszedł tylko ten dziwny statut. Taki zimny, wyrachowany dokument... zupełnie niepodobny do Alberta, którego znałam. Wtedy zrozumiałam, że go straciłam.";
			link.l1 = "Znalazłem to wśród jego rzeczy.";
			link.l1.go = "LadyBeth_Elizabeth_6";
		break;
		
		case "LadyBeth_Elizabeth_6":
			dialog.text = "Mapa do mojego domu? Czyli byłam jego największym skarbem? Co za ironia. Szukał bogactwa po całych Karaibach, a jedyne, co naprawdę miało dla niego znaczenie, było tu... Proszę zaczekać. Mam coś dla pana. To statut Alberta. Przysłał mi go rok temu. Mówił, że pomoże mu odnaleźć skarb i wrócić do mnie. Teraz panu się bardziej przyda.";
			link.l1 = "Dziękuję, Elizabeth. Przykro mi, że tak się to potoczyło.";
			link.l1.go = "LadyBeth_Elizabeth_7";
			GiveItem2Character(PChar, "talisman18");
		break;
		
		case "LadyBeth_Elizabeth_7":
			dialog.text = "A ja wyszłam za mąż, kapitanie. Za pana Bishopa. Ojciec nalegał. Nie zna pan tego człowieka... i lepiej, żeby pan nie znał. Codziennie myślę, jak potoczyłoby się moje życie, gdyby Albert po prostu... wrócił.";
			link.l1 = "Teraz i ja będę o tym myślał.";
			link.l1.go = "LadyBeth_Elizabeth_8";
		break;
		
		case "LadyBeth_Elizabeth_8":
			dialog.text = "Żegnajcie, kapitanie. I... proszę na siebie uważać. Nie gonić za duchami.";
			link.l1 = ""+Goodbye()+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Barbados_Elizabeth_2");
		break;
		
		case "LadyBeth_Elizabeth_Woman_2":
			dialog.text = "Tak, to ja.";
			link.l1 = "Kapitan Helen MacArthur. Znałam... Alberta Blackwooda.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_3";
		break;

		case "LadyBeth_Elizabeth_Woman_3":
			dialog.text = "Mojego Alberta? Boże... On... A pani to kto?";
			link.l1 = "Kapitan Helen MacArthur, jak już mówiłam. Dowodzę własnym statkiem.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_4";
		break;

		case "LadyBeth_Elizabeth_Woman_4":
			dialog.text = "Kapitan? Kobieta-kapitan? Pani... była z Albertem? W jakim sensie... go pani znała?";
			link.l1 = "Tylko jako kapitana. Przykro mi, ale Albert zginął. Byłam świadkiem jego ostatniej bitwy.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_5";
		break;

		case "LadyBeth_Elizabeth_Woman_5":
			dialog.text = "Rozumiem. Proszę wybaczyć moje podejrzenia. Po prostu... kapitan Blackwood zawsze przyciągał uwagę kobiet. Nawet tutaj, na Barbadosie. Zwłaszcza tutaj.";
			link.l1 = "Kochała go pani.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_6";
		break;

		case "LadyBeth_Elizabeth_Woman_6":
			dialog.text = "Całym sercem. Ojciec mówił, że Albert musi tylko doczekać awansu. To była kwestia kilku miesięcy. Ale Albert odebrał jego słowa jako odrzucenie z powodu biedy. Powiedział, że wróci z kosztownościami. I odszedł.";
			link.l1 = "Mężczyźni i ich duma!";
			link.l1.go = "LadyBeth_Elizabeth_Woman_7";
		break;
		
		case "LadyBeth_Elizabeth_Woman_7":
			dialog.text = "Ma pani szczęście, kapitanie MacArthur. Jest pani wolna. Płynie tam, gdzie chce. Żadnych plantatorów, żadnych ojców decydujących o pani losie. Żadnych mężów, którzy uważają panią za swoją własność.";
			link.l1 = "Wolność sporo kosztuje. I trzeba jej bronić każdego dnia.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_8";
		break;
		
		case "LadyBeth_Elizabeth_Woman_8":
			dialog.text = "Być może mam coś, co pomoże pani w tej sprawie. Proszę, oto ono. To jego statut poszukiwacza skarbów. Albert przysłał mi go mniej więcej rok temu. Powiedział, że to najlepsze, co kiedykolwiek stworzył. Że dzięki temu się wzbogaci i wróci do mnie. Ale z każdą stroną coraz mniej przypominał Alberta, którego znałam.";
			link.l1 = "Dziękuję. Zachowam go.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_9";
			GiveItem2Character(PChar, "talisman18");
		break;
		
		case "LadyBeth_Elizabeth_Woman_9":
			dialog.text = "Proszę panią, kapitanie... niech pani ceni swoją wolność. Wyszłam za pułkownika Bishopa. Człowieka, którego boi się nawet mój ojciec. Gdybym była wolna jak pani... Wszystko potoczyłoby się inaczej.";
			link.l1 = "Wiem.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_10";
		break;
		
		case "LadyBeth_Elizabeth_Woman_10":
			dialog.text = "Żegnajcie, kapitanie. I niech wiatr wam sprzyja.";
			link.l1 = ""+Goodbye()+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Barbados_Elizabeth_2");
		break;
	}
} 
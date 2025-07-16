// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Mów, słucham.";
			link.l1 = "Byłem w błędzie. Żegnaj.";
			link.l1.go = "Exit";
			// --> Тичингиту
			if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "true")
            {
                link.l1 = "Jest tu Indianin pod aresztem. Został schwytany przez Fadeya Moskala. Czy mogę z nim porozmawiać?";
                link.l1.go = "Tichingitu";
            }
			if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "commandante")
            {
                link.l1 = "Powiedz mi, czy naprawdę zamierzasz powiesić tego Indianina? Czy to nie za surowa kara za tak małe przestępstwo?";
                link.l1.go = "Tichingitu_3";
            }
			if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "pay")
            {
                link.l1 = "To znowu ja, komendancie. Fadiej Moskwicin napisał tę petycję o uwolnienie Indianina. Oto ona.";
                link.l1.go = "Tichingitu_6";
            }
			// <-- Тичингиту
			//Jason --> Бесчестный конкурент
			if (CheckAttribute(pchar, "questTemp.Shadowtrader.Fort") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_prison")
			{
				link.l1 = "Przyszedłem do ciebie na prośbę lokalnego właściciela sklepu, nazywa się "+pchar.questTemp.Shadowtrader.Tradername+" Poprosił mnie, abym przekazał ci ten list.";
				link.l1.go = "Shadowtrader_prison";
			}
			
			if (CheckAttribute(pchar, "questTemp.Shadowtrader.SeekTrader") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_prison")
			{
				link.l1 = "To znowu ja. Mam istotne dowody, że "+pchar.questTemp.Shadowtrader.Tradername+" jest prawdą.";
				link.l1.go = "Shadowtrader_prison2";
			}
			//Jason <-- Бесчестный конкурент
			//Sinistra --> Путеводная звезда
			if (CheckAttribute(pchar, "questTemp.PZ_BasTerTurma"))
            {
                link.l1 = "Szukam człowieka o nazwisku Longway. Słyszałem, że również go szukacie, Monsieur Oficerze. Czy mieliście szczęście go znaleźć, albo może jakieś tropy?";
                link.l1.go = "PZ_IshemLongway_1";
            }
			//Sinistra <-- Путеводная звезда
		break;
		
		// --> Тичингиту
		case "Tichingitu":
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("BasTer_town", "reload", "reload_jail");
			dialog.text = "A-ah, Fadey opowiedział ci swoją historię? Nie mam powodu, by zabraniać ci go odwiedzić, monsieur. Nie jesteś pierwszym, kto przyszedł zobaczyć tego czerwonoskórego. Cóż, za dziesięć dni każdy obywatel będzie mógł go obejrzeć, kiedy powiesimy go na słońcu...";
			link.l1 = "Czy mogę wejść głębiej do więzienia?";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "Jak już ci mówiłem 'Nie mam powodów, by ci tego zabraniać'. Ruszaj dalej.";
			link.l1 = "Dzięki!";
			link.l1.go = "Tichingitu_2";
		break;
		
		case "Tichingitu_2":
			DialogExit();
			pchar.questTemp.Sharlie.Tichingitu = "wait";
			pchar.questTemp.jailCanMove = true;
		break;
		
		case "Tichingitu_3":
			DelLandQuestMark(npchar);
			dialog.text = "Jesteś tu nowy, prawda, monsieur? Prosto z Europy? Nie rozumiesz sytuacji w koloniach. Ta egzekucja będzie lekcją dla tych czerwonoskórych drani, którzy ośmieliliby się naruszyć własność francuskich kolonistów. Poza tym, sam Fadey nalega na to, a on jest tu bardzo szanowanym człowiekiem i bliskim przyjacielem naszego gubernatora.";
			link.l1 = "Czy istnieje jakiś sposób na złagodzenie kary? Wciąż uważam, że jest zbyt surowa...";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			dialog.text = "Och, nie filozofuj! Idź do Fadeya i poproś o tego Indianina, jeśli naprawdę tak bardzo zależy ci na jego losie. Jeśli Fadey napisze petycję o uwolnienie, spełnimy ją.";
			link.l1 = "Zrozumiano, oficerze. Idę do Fadeya.";
			link.l1.go = "Tichingitu_5";
		break;
		
		case "Tichingitu_5":
			DialogExit();
			pchar.questTemp.Sharlie.Tichingitu = "fadey";
			AddLandQuestMark(characterFromId("fadey"), "questmarkmain");
			QuestPointerToLoc("BasTer_town", "reload", "houseSp1");
		break;
		
		case "Tichingitu_6":
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("BasTer_town", "reload", "reload_jail");
			RemoveItems(pchar, "letter_1", 1);
			dialog.text = "(czytając) Hm... Ten Fadey jest dziwny... Żądał pokazowej egzekucji, a teraz prosi o uwolnienie tego Indianina... Cóż, przypuszczam, że wszyscy przyjaciele gubernatora są tacy jak on. Dobrze, możesz iść i zabrać tego czerwonoskórego.";
			link.l1 = "Moje dzięki, oficerze!";
			link.l1.go = "Tichingitu_7";
		break;
		
		case "Tichingitu_7":
			DialogExit();
			AddQuestRecord("Tichingitu", "3");
			pchar.questTemp.Sharlie.Tichingitu = "wait";
			pchar.questTemp.jailCanMove = true;
			sld = characterFromId("Tichingitu");
			sld.dialog.currentnode = "Tichingitu_6";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		// <-- Тичингиту
		
		//Jason --> мини-квест Бесчестный конкурент
		case "Shadowtrader_prison":
			dialog.text = "Znowu ten "+pchar.questTemp.Shadowtrader.Tradername+" z jego skargami! Dobrze, zobaczmy, co to tym razem... (czyta)";
			link.l1 = "... ";
			link.l1.go = "Shadowtrader_prison_1";
			RemoveItems(PChar, "letter_1", 1);
			DeleteAttribute(pchar, "questTemp.Shadowtrader.Fort");
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_prison_1":
			dialog.text = "Po raz kolejny, absurdalne domysły i ani jednego mocnego dowodu! Dobrze. Powiedz mu, że to po prostu za mało, bym mógł alarmować strażników i kazać im przeszukać miasto.";
			link.l1 = "Chcesz, żebym mu to powiedział?";
			link.l1.go = "Shadowtrader_prison_2";
		break;
		
		case "Shadowtrader_prison_2":
			dialog.text = "Dokładnie - i, najlepiej, słowo w słowo. On zrozumie, co mam na myśli. Nie będę marnować papieru na pisanie odpowiedzi temu irytującemu.";
			link.l1 = "Rozumiem. Żegnaj zatem.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.Trouble = "true";
			NextDiag.TempNode = "First_officer";
			AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
		break;
		
		case "Shadowtrader_prison2":
			dialog.text = "A jakie to 'istotne' dowody, które twierdzisz, że zebrałeś?";
			link.l1 = "Zawarłem umowę z przemytnikami dotyczącą zakupu towarów przez ich nieoficjalny sklep. Ich agent przyjdzie dziś w nocy do biura władz portowych, aby zabrać mnie do ich tak zwanego 'sklepu'.";
			link.l1.go = "Shadowtrader_prison2_1";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.SeekTrader");
			pchar.quest.ShadowtraderTimeSmugglers_Over.over = "yes";
			pchar.quest.Shadowtrader_SMG.over = "yes";//снять оба прерывания
			sld = characterFromID("ShadowAgent_1");
			sld.lifeday = 0;
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_prison2_1":
			dialog.text = "Hhm... No cóż, doskonała robota, kapitanie! W takim razie działamy dalej. Wyślemy naszego człowieka na ich spotkanie, zlokalizujemy ich kryjówkę i aresztujemy wszystkich. Dziękuję za twoją inicjatywę!";
			link.l1 = "Zawsze chętnie pomogę. Jestem pewien, że twoja operacja zakończy się sukcesem.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.End.Fort = "true";
			AddQuestRecord("Shadowtrader", "7");
			AddQuestUserData("Shadowtrader", "sSex", GetSexPhrase("","а"));
			SetTimerFunction("ShadowTrader_questmark", 0, 0, 1);
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			NextDiag.TempNode = "First_officer";
		break;
		// <-- мини-квест Бесчестный конкурент
		
		// Sinistra - Квест "Путеводная звезда" ==>
		case "PZ_IshemLongway_1":
			DelLandQuestMark(npchar);
			dialog.text = "Kto? Daleka... Droga? Nie przypominam sobie żadnych Anglików w naszym mieście ostatnio.";
			link.l1 = "Nie, Longway jest... Chińczykiem.";
			link.l1.go = "PZ_IshemLongway_2";
			DeleteAttribute(pchar, "questTemp.PZ_BasTerTurma");
			DeleteQuestCondition("PZ_BasTerPeshera");
		break;
		
		case "PZ_IshemLongway_2":
			dialog.text = "Cóż, cóż. A dlaczego szukasz tego swojego Longwaya, monsieur?";
			link.l1 = "To mój przyjaciel. Już słyszałem, co się stało - to smutne nieporozumienie, zapewniam cię.";
			link.l1.go = "PZ_IshemLongway_Zashita_1";
			if (pchar.location.from_sea != "BasTer_Town")
			{
				link.l2 = "Szukam go, ponieważ jest znanym przestępcą na Archipelagu.";
				link.l2.go = "PZ_IshemLongway_OhotnikOtryad_1";
			}
		break;
		
		case "PZ_IshemLongway_Zashita_1":
			dialog.text = "Ach, nieporozumienie. Nie chcieliśmy go od razu naprostować, w żadnym razie. Chcieliśmy tylko z nim porozmawiać... na początek. Jednak ten wasz agresywny żółty człowiek nie tylko wyciął kilku strażników miejskich, ale także wybił jednostki wysłane, by go ścigać w dżungli.";
			link.l1 = "Czy planujesz wysłać kolejną jednostkę? Mogę iść z twoimi ludźmi, porozmawiać z nim, uspokoić go i zapobiec kolejnej katastrofie. Czy wystarczy, jeśli zabójstwa ustaną i Longway na dobre opuści miasto?";
			link.l1.go = "PZ_IshemLongway_Zashita_2";
		break;
		
		case "PZ_IshemLongway_Zashita_2":
			dialog.text = "Zwykle mógłbym się z tobą zgodzić. Ale widzisz, jeden z zabitych był oficerem - obiecującym młodym porucznikiem, ulubieńcem Jego Wysokości. Miasto pogrążone jest w żałobie. Nie można tego zignorować ani naprawić. Rozumiesz?";
			link.l1 = "Rozumiem doskonale. Przepraszam za czyny mojego przyjaciela. Nie będę cię już więcej niepokoić.";
			link.l1.go = "PZ_IshemLongway_Uiti_1";
			link.l2 = "Wiesz, tylko Bóg wie, co się dzieje w dżungli. Każdy mógł zabić tych ludzi.";
			link.l2.go = "PZ_IshemLongway_Blef_1";
		break;
		
		case "PZ_IshemLongway_Blef_1":
			dialog.text = "A kto według ciebie mógł pokonać całą drużynę patrolową dowodzoną przez oficera?";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				notification("Trustworthy", "Trustworthy");
				link.l1 = "Godni zaufania) Bandyci, kto inny? Wstyd przyznać, ale ledwo co uciekłem niedawno przed ogromną bandą.";
				link.l1.go = "PZ_IshemLongway_Blef_2";
			}
			else
			{
				notification("Perk check failed", "Trustworthy");
				link.l1 = "Ale skąd miałbym wiedzieć? To mógł być ktokolwiek – bandyci, piraci, szpiedzy...";
				link.l1.go = "PZ_IshemLongway_Blef_netVD_1";
			}
		break;
		
		case "PZ_IshemLongway_Blef_2":
			dialog.text = "Heh, to nie dziwi - biorąc pod uwagę twe gabaryty, Kapitanie. Tak, mamy takich łotrów na wyspie w te dni...";
			link.l1 = "Dokładnie! Mogli więc zmasakrować patrol i biednego młodszego porucznika.";
			link.l1.go = "PZ_IshemLongway_Blef_3";
		break;
		
		case "PZ_IshemLongway_Blef_3":
			dialog.text = "Niestety, to całkiem możliwe.";
			link.l1 = "Dokładnie. Więc jeszcze raz proszę cię, byś pozwolił mi dołączyć do następnej ekipy poszukiwawczej - Longway mnie posłucha, a w ten sposób możemy uniknąć kolejnych zgonów.";
			link.l1.go = "PZ_IshemLongway_Blef_4";
		break;
		
		case "PZ_IshemLongway_Blef_4":
			dialog.text = "Zgoda. Ale jest jeszcze jedno 'ale', sir.";
			link.l1 = "A cóż to takiego?";
			link.l1.go = "PZ_IshemLongway_Blef_5";
		break;
		
		case "PZ_IshemLongway_Blef_5":
			dialog.text = "Nie tak jak w dżungli, wina twojego przyjaciela w mieście jest jasna i w pełni udowodniona. Nie pozostanie bezkarna. Tak więc, te zgony muszą zostać zrekompensowane, jeśli chcesz, aby opuścił miasto żywy.";
			link.l1 = "Zgoda. Ile to będzie kosztować, Monsieur Oficerze?";
			link.l1.go = "PZ_IshemLongway_Blef_6";
		break;
		
		case "PZ_IshemLongway_Blef_6":
			dialog.text = "Trzysta dublonów. Te pieniądze trafią do miasta, a nie do handlarzy na rynku.";
			if (PCharDublonsTotal() >= 300)
			{
				link.l1 = "Oczywiście. Trzysta dublonów - proszę bardzo.";
				link.l1.go = "PZ_IshemLongway_Blef_7";
			}
			link.l2 = "Nie przywiozłem tym razem moich dublonów do miasta. Ale jeśli pozwolisz mi je odzyskać...";
			link.l2.go = "PZ_IshemLongway_NetDublonov_1";
		break;
		
		case "PZ_IshemLongway_Blef_7":
			dialog.text = "Doskonale. Udowodniłeś swoją odpowiedzialność. Kończymy właśnie odprawę dla następnego oddziału. Zezwalam ci do niego dołączyć.";
			link.l1 = "Dziękuję. Do widzenia, Monsieur Oficerze.";
			link.l1.go = "PZ_IshemLongway_BeryomOtryad";
			RemoveDublonsFromPCharTotal(300);
			pchar.questTemp.PZ_DrugOtryad = true;
		break;
		
		case "PZ_IshemLongway_NetDublonov_1":
			dialog.text = "Nie urodziłem się wczoraj. Wiem, że zamierzasz uciec - nie dla dublonów, ale dla swojego drogiego Chińczyka.";
			link.l1 = "Dam ci moje słowo, że nie opuszczę miasta z Longwayem.";
			link.l1.go = "PZ_IshemLongway_NetDublonov_2";
		break;
		
		case "PZ_IshemLongway_NetDublonov_2":
			dialog.text = "Słowa, słowa... Mam dość twojego gadania, kapitanie. Nigdzie się nie ruszasz, dopóki sami nie złapiemy tego cholernie żółtoskórego człowieka.";
			link.l1 = "Posłucham twego rozkazu, jeśli obiecasz nie zabić Longwaya na miejscu, Panie Oficerze.";
			link.l1.go = "PZ_IshemLongway_Arest_1";
			link.l2 = "Czy osobiście złamałem dziś prawa miasta?";
			link.l2.go = "PZ_IshemLongway_Pobeg_1";
		break;
		
		case "PZ_IshemLongway_Blef_netVD_1":
			dialog.text = "W takim razie nie wiesz. Trzymam się swojej obecnej intuicji - Chińczyk musi być schwytany, bez względu na wszystko.";
			link.l1 = "Twoje obecne przeczucie? Ale nie masz dowodów, że Longway zabił wszystkich w dżungli.";
			link.l1.go = "PZ_IshemLongway_Blef_netVD_2";
		break;
		
		case "PZ_IshemLongway_Blef_netVD_2":
			dialog.text = "A czy masz dowód jego niewinności? Nie? To przestań robić świętego z tego twojego żółtoskórego człowieka. Rozumiesz mnie?";
			link.l1 = "Doskonale rozumiem. Przepraszam za działania mego przyjaciela. Nie będę ci więcej przeszkadzał.";
			link.l1.go = "PZ_IshemLongway_Uiti_1";
		break;
		
		case "PZ_IshemLongway_Uiti_1":
			dialog.text = "Obawiam się, że nie mogę cię jeszcze wypuścić, kapitanie.";
			link.l1 = "Co masz na myśli?";
			link.l1.go = "PZ_IshemLongway_Uiti_2";
		break;
		
		case "PZ_IshemLongway_Uiti_2":
			dialog.text = "Chodzi mi o to, że skoro ten Longway to twój przyjaciel, nie ma gwarancji, że nie pobiegniesz za nim i nie spróbujesz uciec razem z nim. Więc będę musiał zatrzymać cię, dopóki sami nie złapiemy tego żółtoskórego rzeźnika.";
			link.l1 = "Zastosuję się do twojego rozkazu, jeśli obiecasz nie zabić Longwaya na miejscu, panie oficerze.";
			link.l1.go = "PZ_IshemLongway_Arest_1";
			link.l2 = "Ale czy osobiście złamałem dzisiaj prawa miasta?";
			link.l2.go = "PZ_IshemLongway_Pobeg_1";
		break;
		
		case "PZ_IshemLongway_Arest_1":
			dialog.text = "Nie mogę niczego obiecać. Kto wie, co twój przyjaciel ma na myśli, albo czy nie rozpocznie kolejnej masakry, gdy nas zobaczy. W międzyczasie, proszę, ciesz się swoimi luksusowymi kwaterami, Kapitanie.";
			link.l1 = "Zabawne...";
			link.l1.go = "PZ_IshemLongway_Arest_2";
		break;
		
		case "PZ_IshemLongway_Arest_2":
			DialogExit();
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(PChar, MUSKET_ITEM_TYPE);
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			bDisableCharacterMenu = true;
			InterfaceStates.Buttons.Save.enable = false;
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			DoQuestReloadToLocation("BasTer_prison", "goto", "goto9", "PZ_SharliePlennik_BadFinal");
		break;
		
		case "PZ_IshemLongway_Pobeg_1":
			dialog.text = "Zrozum, nie mam nic przeciwko tobie osobiście. I masz rację - nie popełniłeś żadnej zbrodni. Ale musimy upewnić się, że twój żółtoskóry przyjaciel nie ucieknie przed sprawiedliwością.";
			link.l1 = "Zrozum więc, że nie pozwolę się zatrzymać w tak nieuczciwy sposób.";
			link.l1.go = "PZ_IshemLongway_Pobeg_2";
		break;
		
		case "PZ_IshemLongway_Pobeg_2":
			if (pchar.location.from_sea == "BasTer_Town")
			{
				dialog.text = "W takim razie będziemy musieli cię uciszyć, panie.";
			}
			else
			{
				dialog.text = "Mam tego dość! Sierżancie, poprowadź oddział do tej przeklętej jaskini i znajdźcie Chińczyków! Z tym tutaj rozprawię się osobiście...";
			}
			link.l1 = "Do diabła z tobą.";
			link.l1.go = "PZ_IshemLongway_Pobeg_3";
		break;
		
		case "PZ_IshemLongway_Pobeg_3":
			DialogExit();
			
			LAi_SetHuberType(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_MoveCharacter(NPChar, "FRANCE_CITIZENS");
			LAi_group_Attack(characterFromId("BasTer_Mayor"), Pchar);
			ChangeCharacterNationReputation(pchar, FRANCE, -50);
			if (pchar.location.from_sea == "BasTer_Town")
			{
				PChar.quest.PZ_KorablPort_BadFinal.win_condition.l1 = "MapEnter";
				PChar.quest.PZ_KorablPort_BadFinal.win_condition = "PZ_KorablPort_BadFinal";
				AddQuestRecord("PZ", "10");
				LocatorReloadEnterDisable("BasTer_town", "gate_back", true);
				Island_SetReloadEnableGlobal("Guadeloupe", false);
			}
			else
			{
				PChar.quest.PZ_KorablBuhta_BadFinal.win_condition.l1 = "EnterToSea";
				PChar.quest.PZ_KorablBuhta_BadFinal.win_condition = "PZ_KorablBuhta_BadFinal";
				AddQuestRecord("PZ", "5");
				
				// Микро-диалог с Лонгвэем у пещеры, если мы побежали к пещере ему помочь после ссоры с комендантом
				PChar.quest.PZ_IshemLongway_SorraKomendant.win_condition.l1 = "location";
				PChar.quest.PZ_IshemLongway_SorraKomendant.win_condition.l1.location = "Guadeloupe_CaveEntrance";
				PChar.quest.PZ_IshemLongway_SorraKomendant.win_condition = "PZ_IshemLongway_SorraKomendant";
				
				LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", true);
				LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", true);
				//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", true);
			}
		break;
		
		case "PZ_IshemLongway_OhotnikOtryad_1":
			dialog.text = "Łowca nagród, co? Zazwyczaj nie lubię mieć do czynienia z waszą bandą, ale w tym przypadku, korzystne jest dla mnie, że nasze interesy się pokrywają. Najwyraźniej ten żółtoskóry to słynny zabójca. Zabił wielu moich ludzi, zarówno w mieście, jak i w dżungli.";
			link.l1 = "Ścigałem go przez Archipelag już od jakiegoś czasu.";
			link.l1.go = "PZ_IshemLongway_OhotnikOtryad_2";
		break;
		
		case "PZ_IshemLongway_OhotnikOtryad_2":
			dialog.text = "Przeklęty łajdak! Oto co zrobimy: zbiorę kolejny oddział, a ty pójdziesz z nimi. Tym razem nie ma dokąd uciec, a z twoją pomocą będziemy mieli większe szanse na sukces. Nie oczekuj ode mnie nagrody - jesteś łowcą nagród, więc zapłatę otrzymasz od tego, kto cię zatrudnił. Powinieneś być wdzięczny, że w ogóle pozwalam ci współpracować ze mną.";
			link.l1 = "To prawda. Do zobaczenia później, oficerze. Jeśli któryś z twoich ludzi przeżyje kolejne spotkanie z naszym chińskim przyjacielem, dam ci znać, jak poszło.";
			link.l1.go = "PZ_IshemLongway_BeryomOtryad";
			pchar.questTemp.PZ_OhotnikOtryad = true;
		break;
		
		case "PZ_IshemLongway_BeryomOtryad":
			DialogExit();
			
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", true);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", true);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", true);
			DoQuestReloadToLocation("Guadeloupe_jungle_02", "goto", "goto1", "PZ_IshemLongway_Otryad");
		break;
		
		case "PZ_BasTer_ComendantDialog_1":
			dialog.text = "Masz rację. Wy dwaj jesteście znajomymi, jak mniemam? Kim dla siebie jesteście?";
			link.l1 = " Jest nawigatorem na moim statku, i...";
			link.l1.go = "PZ_BasTer_ComendantDialog_2";
			if (pchar.location.from_sea != "BasTer_Town")
			{
				link.l2 = "  Szukam go, ponieważ jest znanym przestępcą na Archipelagu.";
				link.l2.go = "PZ_IshemLongway_OhotnikOtryad_1";
			}
		break;
		
		case "PZ_BasTer_ComendantDialog_2":
			dialog.text = "On lepiej radzi sobie z bronią niż z mapami. Czy masz pojęcie, co zrobił twój chiński pupil?";
			link.l1 = "Prawdę mówiąc, nie, bo właśnie przybiłem do portu i zacząłem szukać. Jestem pewien, że to wszystko było nieporozumieniem.";
			link.l1.go = "PZ_IshemLongway_Zashita_1";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_1":
			dialog.text = "Dokładnie. Kimże ty jesteś dla niego, skoro tak bardzo go chcesz? To nie ma znaczenia - ważny jest cel twojej wizyty w mieście.";
			link.l1 = "Nic nielegalnego, panie. Ale co miałeś na myśli mówiąc „to już nie ma znaczenia”? Czy on...";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_2";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_2":
			dialog.text = "Tak. Został pochowany za jednym z wzgórz, w pewnej odległości od cmentarza. Święci ojcowie nie pozwolili na właściwy chrześcijański pochówek dla poganina.";
			link.l1 = "Jak do tego doszło, jeśli to nie tajemnica?";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_3";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_3":
			dialog.text = "Bardzo prosto - przybył do miasta, węszył bez końca. Próbowaliśmy z nim porozmawiać, dowiedzieć się, co tutaj robi, ale zabił kilku ludzi i uciekł do dżungli. Wysłałem za nim kilka grup poszukiwawczych, jedną po drugiej, ale wszystkich wykończył! Musieliśmy go uwięzić w jaskini, a strzelcy dokończyli resztę.";
			link.l1 = "A nie wiesz, czego szukał? Widzisz, nigdy wcześniej nie zrobił czegoś takiego - był nawigatorem na moim statku. Ale potem mnie okradł i uciekł.";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_4";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_4":
			dialog.text = "Po prostu wyleciało mi z głowy, aye. Więc, ty też ucierpiałeś z powodu jego działań? To będzie dla ciebie nauczka, Kapitanie. Będziesz wiedział, żeby nie brać na pokład kogoś, komu nie można ufać. Nigdy nie ufaj żółtoskóremu człowiekowi - zapamiętaj moje słowa!";
			link.l1 = "Aye, będę o tym pamiętać. Czy znalazłeś coś przy nim?";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_5";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_5":
			dialog.text = "Och, chcesz odzyskać skradzione towary? Miał trochę srebra w kieszeniach, więc jeśli coś ci ukradł, to już wszystko wydał. Były też jakieś inne papiery... z dziennika twojego statku? I tak nic z tego nie rozumieliśmy - jakiś kod, może? Wszystko było pokryte krwią, więc nie mogliśmy odczytać nieuszkodzonych części.";
			link.l1 = "Er, tak. Dziękuję. Zawsze martwiłem się, co się stanie, jeśli moje dzienniki i pamiętniki wpadną w ręce kogoś innego...";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_6";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_6":
			dialog.text = " I wymyślać skomplikowany szyfr z tego powodu? Nie szkoda ci było czasu i wysiłku? Proszę bardzo. A co do srebra - nie gniewaj się, ale oddaliśmy je miastu. Ten Chińczyk posłał wielu moich ludzi do piachu tamtego dnia.";
			link.l1 = "W takim razie nie śmiem nalegać. Do widzenia.";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_7";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_7":
			DialogExit();
			
			LAi_SetHuberType(npchar);
			AddQuestRecord("PZ", "9");
			CloseQuestHeader("PZ");
			bDisableLandEncounters = false;
		break;
		// <== Квест "Путеводная звезда" - Sinistra
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

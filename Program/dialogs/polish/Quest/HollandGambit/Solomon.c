// Соломон Шнеур - старый еврей
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
//--------------------------------------за Голландию------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
				if (pchar.questTemp.HWIC.Holl == "AbbyFather")
				{
					dialog.text = "Czego chcesz od tego starego Żyda, młodzieńcze?";
					link.l1 = "Salomonie, potrzebuję, abyś się skupił i przypomniał sobie o zagubionej wyspie, na której rozbił się twój statek. Ukryłeś tam skarb. Rozmawiałem z twoją córką. Mój szef Lucas Rodenburg dał mi carte blanche, by działać na rzecz dobra twojej rodziny. Jak widzę, najważniejszą rzeczą dla ciebie w tej chwili jest odzyskanie kapitału twojej rodziny, a bez mojej pomocy nie wywąchasz ani grosza z tego złota.";
					link.l1.go = "SolomonBonanza";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "AbbyFindScull" && makeint(Pchar.money) >= 200000)
				{
					dialog.text = "O, mój młodzieńcze, to ty? Czy nie możesz mi powiedzieć czegoś dobrego? Czy wy, chrześcijanie, znowu przyszliście dręczyć tego biednego starego Żyda pytaniami?";
					if (CheckCharacterItem(pchar, "SkullAztec"))
					{
						link.l1 = "Znalazłem wyspę, choć było to dość trudne. Znalazłem również twój kufer z pieniędzmi i tę czaszkę. Domyślam się, że to czaszka twojego dziadka-patriarchy, o czymkolwiek tam mówiłeś.";
						link.l1.go = "SolomonBonanza_2";
					}
					link.l2 = "Znalazłem wyspę, choć nie było to łatwe. Znalazłem też twoją skrzynię z pieniędzmi. Ale w tej skrzyni nie było żadnych czaszek.";
					link.l2.go = "SolomonBonanza_3";
					link.l3 = "Nie, nie mam pytań w tej chwili.";
					link.l3.go = "exit";
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "GiveLucasMoney" && GetQuestPastDayParam("questTemp.HWIC.Holl.LucasMoney") > 7)
				{
					dialog.text = "O, mój młody człowieku, to ty? Czy możesz mi powiedzieć coś dobrego? Czy znów zamierzasz dręczyć tego biednego starego Żyda pytaniami?";
					link.l1 = "Znalazłem wyspę, choć było to dość trudne. Znalazłem również twój kufer z pieniędzmi. Proszę, oto on.";
					link.l1.go = "SolomonBonanza_5";
					break;
				}
				dialog.text = "Witaj, młody człowieku. Czego chcesz od tego biednego starego Żyda?";
				link.l1 = "Dobry wieczór. Nie, nic takiego, przyszedłem tylko się przywitać.";
				link.l1.go = "exit";
				break;
			}
//----------------------------------------за Англию-----------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				if (pchar.questTemp.HWIC.Eng == "toAbigile")
				{
					dialog.text = "Dzień dobry, młody człowieku. Widzę, że przyszedłeś w jakimś celu... Czego chcesz? Czy coś z tego będę miał, czy coś mi umknęło?";
					link.l1 = "Dzień dobry, Salomonie. Chciałbym porozmawiać z Abigail.";
					link.l1.go = "Solomon_treasure";
					DelLandQuestMark(npchar);
					break;
				}
				dialog.text = "Witaj, młody człowieku. Czego chcesz od tego biednego starego Żyda?";
				link.l1 = "Dzień dobry, Solomonie. Nic takiego, przyszedłem tylko się przywitać.";
				link.l1.go = "exit";
				break;
			}
//-----------------------------------------против всех-------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "toVillemstad")
				{
					dialog.text = "Dzień dobry, młodzieńcze. Widzę, że przyszedłeś w jakimś celu... Czego chcesz? Czy coś z tego będę miał, czy może coś przeoczyłem?";
					link.l1 = "Muszę porozmawiać z Abigail. Mam dla niej list.";
					link.l1.go = "Abigile_kidnap";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileNextDayOver")
				{
					dialog.text = "Witaj, młodzieńcze. Czego chcesz? Kolejny list do mojej córki?";
					link.l1 = "Nie. Gdzie jest Abigail?";
					link.l1.go = "Abigile_GoOver";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistory")
				{
					dialog.text = "Oj... Czy mówisz o moich pieniądzach, młody człowieku?";
					link.l1 = "Tak, panie. O pieniądzach, które ukryłeś na jakiejś wyspie. Czy to prawda, że ty i Abigail nie pamiętacie jej lokalizacji?";
					link.l1.go = "Solomon_history";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistoryAfter")
				{
					dialog.text = "Dobrze. Pamiętam fleut i jego kapitana. Widziałem go nawet raz wcześniej w Amsterdamie. Fleut nazywał się 'Leiden', a kapitan nosił imię Toff Keller.";
					link.l1 = "To dobry początek! Mam teraz trop.";
					link.l1.go = "Solomon_history_3";
					pchar.questTemp.HWIC.Self = "SolomonHistoryEnd";
					break;
				}
				dialog.text = "Oy vey, czego chcesz od tego biednego starego Żyda tym razem?";
				link.l1 = "Dzień dobry. Nie, nic takiego, przyszedłem tylko się przywitać.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Oy vey, czego chcesz od tego biednego starego Żyda tym razem?";
			link.l1 = "Dzień dobry. Nie, nic takiego, przyszedłem tylko się przywitać.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

//-----------------------------------------------За Голландию-----------------------------------
		case "SolomonBonanza":
			PlaySound("Voice\English\hambit\Solomon Shneur-03.wav");
			dialog.text = "A czego chcesz ode mnie? Czy wyglądam na człowieka, który coś wie? Skądże mogłem wiedzieć, że w takim dniu, zapomnianym przez Boga, dokładnie tam znajdowała się działka z towarami i złotem do zabrania? Wyobraź sobie, jak wielu gojów chodzących po ulicach chce przechytrzyć takiego Żyda jak ja i zabrać mi pieniądze!\nJest wyspa. Ani jednego człowieka tam, oprócz Abiego i mnie. Ani jednego. Nikogo w ogóle. Pośrodku była grota. Tam schowałem swoją skrzynię, aby uchronić ją przed tym piratem gojem Amalekiem! Skrzynia pełna złota, żadnych drobiazgów w niej. Dźwigałem ją aż z Starego Kraju! Wszystko, co zarobiłem potem, jak się mówi, w pocie czoła, jest tam. Plus, czaszka mojego dziadka... Uwierz mi, to nas uratowało, tak, tak\nOh-ho-ho, to starożytny talizman naładowany magiczną mocą Talmudu! Boże chroń nas przed Amalekiem! Oy vey, trudno zacząć od nowa w tej epoce gojów! Chciałbym, żebyś wiedział, młody człowieku! Och, chciałbym, żebyś wiedział!";
			link.l1 = "Co ty, do diabła, bredzisz, szaleńcze? Kogo to obchodzi. Poradzę sobie z tym sam. Żegnaj!";
			link.l1.go = "SolomonBonanza_1";
		break;
		
		case "SolomonBonanza_1":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "AbbySeekIsland";
			pchar.quest.Joakim_meeteng.win_condition.l1 = "location";
			pchar.quest.Joakim_meeteng.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Joakim_meeteng.function = "Create_Joakim";
		break;
		
		case "SolomonBonanza_2"://отдаем всё
			dialog.text = "Oj, jest Bóg i jesteś prawdziwym mężczyzną! Przywróciłeś nie tylko moje złoto, ale także odkupiłeś nazwisko Shneur! Jakiego wstydu zapobiegłeś! Mynheer Rodenburg może być słusznie dumny, że ma takich kapitanów jak ty pod swoją komendą. Dam czaszkę mynheerowi Rodenburgowi, obiecał zapłacić za nią znaczną sumę. Chciałbym ci osobiście podziękować, jesteś znakomitym szabes gojem - proszę, przyjmij ten amulet jako mały dowód wdzięczności tego Żyda.";
			link.l1 = "Uh, dziękuję, chyba.";
			link.l1.go = "SolomonBonanza_4";
			RemoveItems(PChar, "SkullAztec", 1);
			AddMoneyToCharacter(pchar, -200000);
			GiveItem2Character(pchar, "amulet_7"); 
			AddDialogExitQuestFunction("DeleteJoakimFromRoom");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			SetFunctionTimerCondition("Caleuche_StartTotal", 0, 0, 180, false); // таймер на Калеуче
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Joakim"));
			pchar.questTemp.Caleuche.SolomonSkul = true;
		break;
		
		case "SolomonBonanza_3":
			dialog.text = "Oj, jest Bóg i jesteś prawdziwym człowiekiem honoru! Odzyskałeś nie tylko moje złoto, ale także przywróciłeś dobre imię Shneura! Co za hańba została zażegnana! Co do czaszki - cóż, mniejsza z tym, w końcu był to szalony dureń! Mynheer Rodenburg może być dumny, że ma takich kapitanów jak ty pod swoją komendą. Chciałbym ci osobiście podziękować, jesteś wspaniałym szabasowym gojem - proszę, przyjmij ten amulet na pamiątkę.";
			link.l1 = "Uh, dziękuję, chyba.";
			link.l1.go = "SolomonBonanza_4";
			AddMoneyToCharacter(pchar, -200000);
			GiveItem2Character(pchar, "obereg_10");
			pchar.questTemp.HWIC.Holl.ScullnotReturn = "true";//признак для Лукаса
			ChangeCharacterComplexReputation(pchar, "nobility", -8);
			DelLandQuestMark(npchar);
		break;
		
		case "SolomonBonanza_4":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "AbbyLeavesMarried";//теперь можно говорить с Аби
			AddQuestRecord("Holl_Gambit", "1-32");
			AddLandQuestMark(characterFromId("Abigile"), "questmarkmain");
		break;
		
		case "SolomonBonanza_5":
			dialog.text = "Co? Co ty mówisz, młody człowieku? Czy to prawda? Daj mi spojrzeć... ";
			link.l1 = "Oto twoje pieniądze. Należą do ciebie i Abigail. Lecz niestety, nie znalazłem czaszki twego dziadka.";
			link.l1.go = "SolomonBonanza_6";
		break;
		
		case "SolomonBonanza_6":
			AddMoneyToCharacter(pchar, -200000);
			GiveItem2Character(pchar, "amulet_7"); 
			dialog.text = "O pieniądze, pieniądze, cudowne pieniądze... Hmm, to jednak nie wygląda jak moje pieniądze... Nie pachnie jak mój ukochany szmal. Ale z drugiej strony - pieniądze to pieniądze, młodzieńcze, prawda? Nie będę narzekać. 'Darowanemu koniowi w zęby się nie zagląda,' jak to mówimy! Dziękuję bardzo za zwrot moich oszczędności. Chciałbym ci również podziękować, proszę, przyjmij ten amulet. Teraz idź i powiedz Abi dobre wieści. Muszę to przeliczyć.";
			link.l1 = "Wszystkiego najlepszego, Salomonie.";
			link.l1.go = "SolomonBonanza_4";
			pchar.questTemp.HWIC.Holl.LucasMoney = "true";//признак для Лукаса
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

//-------------------------------------------за Англию------------------------------------------------
		
		case "Solomon_treasure":
			dialog.text = "Oj, weź się w garść! Mynheer Rodenburg jest o krok od bycia moim goj zięciem. Wszyscy żołnierze z garnizonu będą tu za sekundę, jeśli zawołam o pomoc!";
			link.l1 = "Kim do cholery jesteś?";
			link.l1.go = "Solomon_treasure_1";
		break;
		
		case "Solomon_treasure_1":
			dialog.text = "Słuchaj mnie, kapitanie. Jestem jej ojcem, Solomonem. Zrób to, co należy, przywieź mi moje zgubione monety i jadeitową czaszkę jej pradziada. Ten stary Żyd może nie jest tak przebiegły jak ty, ale nawet on wie, że czegoś chcesz od jego córki\nMoże zostałes przysłany przez kogoś, przez jakiegoś kapitana, który mnie zna, powiem Abi wszystko, nie martw się. Nie ma jej teraz w domu, modli się za dusze grzeszników, takich jak ty.";
			link.l1 = "To ledwo miało sens... Kurwa, jesteś prawdziwym dziwakiem. Żegnaj, stary skąpcze.";
			link.l1.go = "Solomon_treasure_2";
		break;
		
		case "Solomon_treasure_2":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-17");
			pchar.questTemp.HWIC.Eng = "AbigileInChurch";
			sld = characterFromId("Abigile");
			sld.greeting = "abigile_3";
			ChangeCharacterAddressGroup(sld, "Villemstad_church", "goto", "goto1");//Аби в церковь
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
//----------------------------------------------против всех---------------------------------------------	
		
		case "Abigile_kidnap":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Villemstad");
			dialog.text = "List? Nie gadaj! Posłuchaj, chłopie, Mynheer Rodenburg jest o krok od zostania moim zięciem. Możesz się stąd wynosić, bo go lubię!";
			link.l1 = "Słuchaj, nie obchodzi mnie, kim jest twój zięć. Jestem zobowiązany przekazać ten list Abigail. Wiesz, gdzie mogę ją znaleźć? I kim, do diabła, jesteś?";
			link.l1.go = "Abigile_kidnap_1";
		break;
		
		case "Abigile_kidnap_1":
			dialog.text = "Kimże jestem? Jestem jej ojcem, Solomonem... I nie lubię cię, goju.";
			link.l1 = "Martwiłbym się bardziej, gdybyś powiedział, że mnie lubisz. A teraz, czy będziesz mnie dalej pouczać, czy sprowadzisz Abigail? Powtarzam, jestem posłańcem! Mam list do twojej córki!";
			link.l1.go = "Abigile_kidnap_2";
		break;
		
		case "Abigile_kidnap_2":
			dialog.text = "Daj mi ten list. Przekażę go mojej córce.";
			link.l1 = "Ogolę ci włosy i podstawię ci nos, zanim przekażę ci ten list. Mam rozkaz dostarczyć tę wiadomość osobiście do niej. Nie powiedziano mi ani słowa o jej ojcu i nie obchodzi mnie to. Gdzie mogę znaleźć Abigail?";
			link.l1.go = "Abigile_kidnap_3";
		break;
		
		case "Abigile_kidnap_3":
			dialog.text = "Jak tylko krzyknę, młody goju, każdy żołnierz w mieście zjawi się tu natychmiast. Nie bądź taki uparty, widzisz przecież, że mam wszystkie karty w ręku.";
			link.l1 = "Jezus, Maryja i Józef! Naprawdę? A co potem? Oczekujesz, że wsadzą mnie w kajdany za dostarczenie listu? Nie bądź śmieszny!";
			link.l1.go = "Abigile_kidnap_4";
		break;
		
		case "Abigile_kidnap_4":
			DialogExit();
			sld = characterFromId("Abigile");
			ChangeCharacterAddressGroup(sld, "Villemstad_houseSP2", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Abigile_GoOver":
			dialog.text = "Czyś ty oszalał? Podnieciłeś moją biedną córkę na śmierć swoim listem... Postanowiła ruszyć za tym angielskim draniem! Wypłynęła na pierwszym dostępnym statku! Ojej, moja biedna córka! Co ma teraz zrobić ten stary Żyd? Moje życie jest zrujnowane! To hańba! Zostaw mnie z moim nieszczęściem albo zostań i tryumfuj, nie obchodzi mnie to! Oooo, moja biedna Abigail! Sprowadziłeś szare włosy swego ojca do Szeolu w rozpaczy!";
			link.l1 = "No, jak o tym pomyśleć! Wygląda na to, że nie mogła dłużej czekać. Żegnaj, Solomon!";
			link.l1.go = "Abigile_GoOver_1";
		break;
		
		case "Abigile_GoOver_1":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-69");
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Self = "end";
			pchar.questTemp.HWIC.Detector = "self_fail";
		break;
		
		case "Solomon_history":
			PlaySound("Voice\English\hambit\Solomon Shneur-03.wav");
			dialog.text = "Jak to wygląda? To tylko wyspa bez ludzi, tylko ja i Abigail. Tam ukryłem swoją skrzynię, by zapobiec temu pirackiemu łobuzowi Amalekowi przed jej zabraniem. Wszystko, co uczciwie zarobiłem, wkładając w to pot i trud, jest w tej skrzyni...";
			link.l1 = "Powiedz mi, Salomonie, czy może przypominasz sobie nazwę fleuty, o której mówiła twoja córka? A jak się nazywał jej kapitan?";
			link.l1.go = "Solomon_history_1";
		break;
		
		case "Solomon_history_1":
			dialog.text = "Hmm... Cóż, nie wiem. Łeb tego biednego starego Żyda jest zmieszany jak patelnia gefilte fish! A dlaczego pytasz, młody człowieku?";
			link.l1 = "Chcę tylko pomóc twojej córce, Solomonie. Nie mogę niczego obiecać, ale chciałbym spróbować. Mój były szef źle ją traktował, i po tym czuję się zobowiązany pomóc jej jakoś się osiedlić.";
			link.l1.go = "Solomon_history_2";
		break;
		
		case "Solomon_history_2":
			dialog.text = "Oj waj, jeśli tak się sprawy mają...";
			link.l1 = " ";
			link.l1.go = "Solomon_history_3";
			pchar.questTemp.HWIC.Self = "SolomonHistoryNext";
		break;
		
		case "Solomon_history_3":
			DialogExit();
			sld = characterFromId("Abigile");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Solomon_thanks":
			dialog.text = "Młody człowieku! Czekaj!";
			link.l1 = "Tak?";
			link.l1.go = "Solomon_thanks_1";
		break;
		
		case "Solomon_thanks_1":
			dialog.text = "Młody człowieku! Chciałbym podziękować ci za wszystko, co zrobiłeś dla mnie i mojej córki. Uratowałeś nas. Przepraszam za trudne powitanie, kiedy spotkaliśmy się po raz pierwszy, i za moje wątpliwości co do twojej szczerej chęci pomocy. Proszę, wybacz temu staremu Żydowi. Jesteś naprawdę błogosławionym człowiekiem wśród gojów. Powiedz mi teraz, czy nie znalazłeś niczego innego oprócz moich pieniędzy w grocie?";
			link.l1 = "Nie, Salomonie. Nie było nic poza pieniędzmi. Musiałem walczyć z oprychami van Berga - to on zatopił twój statek miesiące temu. Może już coś ukradli... Co jeszcze miało tam być?";
			link.l1.go = "Solomon_thanks_2";
		break;
		
		case "Solomon_thanks_2":
			dialog.text = "Och, nic ważnego... Jedna stara rodzinna relikwia... Cóż, nieważne! Zapomnij o tym, on i tak był palantem! I... Jeszcze jedna rzecz, młodzieńcze... ";
			link.l1 = "Kontynuuj.";
			link.l1.go = "Solomon_thanks_3";
		break;
		
		case "Solomon_thanks_3":
			dialog.text = "Ty... cóż, dowiedziałem się czegoś o tobie. Nasz gubernator bardzo cię ceni, a ty jesteś znakomitym kapitanem. Powiem ci sekret... moja córka bardzo cię lubi. Sama mi to powiedziała. Może... pomyślisz o tym? Abigail to bardzo dobra dziewczyna, zapewniam cię, lepsza niż jakiekolwiek shiksa ladacznice, które mogłeś spotkać w swoich podróżach.";
			link.l1 = "Oj waj... To nie takie proste, Salomonie. Twoja córka to prawdziwy klejnot. Dobrze się nią opiekuj.";
			link.l1.go = "Solomon_thanks_4";
		break;
		
		case "Solomon_thanks_4":
			dialog.text = "Przemyśl to, młodzieńcze. Zastanów się jeszcze raz i wróć! Chętnie cię znów zobaczymy!";
			link.l1 = "Jasne...żegnaj, Salomonie.";
			link.l1.go = "Solomon_thanks_5";
		break;
		
		case "Solomon_thanks_5":
			DialogExit();
			LocatorReloadEnterDisable("Villemstad_houseSp2", "reload1", false);
			AddQuestRecord("Holl_Gambit", "3-65");
			NextDiag.CurrentNode = "First time";
		break;
		
		case "Solomon_poor":
			dialog.text = "Oyyy... Czasem niemożliwością jest rozpocząć nowe życie, młody człowieku. Żyć w biedzie - cóż może być gorszego dla starego głupca jak ja?";
			link.l1 = "Przykro mi, Salomonie. Trzymaj się mocno i szukaj Chrystusa.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Solomon_poor";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Jesteś "+GetSexPhrase("Złodziej, panie! Strażnicy, łapcie go","złodziejka, dziewczyno! Straże, bierzcie ją")+"!!!","Popatrz tylko na to! Ledwo się zagłębiłem w rozmyślania, a ty postanowiłeś sprawdzić moją skrzynię! Łap złodzieja!!!","Straż! Rabunek! Łapcie złodzieja!!!");
			link.l1 = "Do diabła!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}

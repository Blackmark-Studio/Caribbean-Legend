// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie pytania?","Czego chcesz, "+GetAddress_Form(NPChar)+"?"),"Już próbowałeś zadać mi pytanie "+GetAddress_Form(NPChar)+"...","Rozmawiasz o tym pytaniu już trzeci raz dzisiaj...","Spójrz, jeśli nie masz mi nic do powiedzenia o sprawach portowych, to nie zawracaj mi głowy swoimi pytaniami.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniam zdanie.","Nie mam o czym rozmawiać."),"Nieważne.","Rzeczywiście, to już trzeci raz...","Przykro mi, ale nie interesują mnie teraz sprawy portu.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			// belamour legengary edition на пару с Акулой -->
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet"))
			{
				if(pchar.questTemp.SharkGoldFleet == "toCarPortOffice" || pchar.questTemp.SharkGoldFleet == "start" || pchar.questTemp.SharkGoldFleet == "afterGvik" || pchar.questTemp.SharkGoldFleet == "buyincar")
				{
					link.l1 = "Faktem jest, że zamierzam wyruszyć do Porto Bello w najbliższych dniach z ładunkiem towarów zakupionych od ciebie w kolonii. Pomyślałem: może masz jakieś towary lub interesy, które mogę załatwić po drodze... Oczywiście za opłatą.";
					link.l1.go = "SharkGoldFleet";
				}
				if(pchar.questTemp.SharkGoldFleet == "LightVar")
				{
					if(!bImCasual) pchar.quest.SharkGoldFleetToCPO10.over = "yes";
					link.l1 = "Witaj ponownie. Dostarczyłem twój list do Porto Bello. Tam poproszono mnie, abym ci przekazał odpowiedź.";
					link.l1.go = "SharkGoldFleet_09";
				}
				if(pchar.questTemp.SharkGoldFleet == "DifficultVar")
				{
					if(!bImCasual) pchar.quest.SharkGoldFleetToCPO10.over = "yes";
					link.l1 = "Cześć. Przyszedłem do ciebie z Porto Bello. Twój kolega z lokalnego urzędu portowego poprosił mnie, abym przekazał ci ten list.";
					link.l1.go = "SharkGoldFleet_13";
				}
			}
			//<-- на пару с Акулой
		break;
		
		// belamour на пару с Акулой -->
		case "SharkGoldFleet":
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet.Fail21"))
			{
				pchar.questTemp.SharkGoldFleet = "toCurierDie";
				AddQuestRecord("SharkGoldFleet", "5");
				SGF_CreateCurierInWorld("");
				dialog.text = "Dziękuję za troskę, ale nie mam takich spraw. Rzeczywiście, było jedno zlecenie, ale dosłownie spóźniłeś się o parę dni: wysłałem w tym celu szybkiego kuriera lugra.";
				link.l1 = "Rozumiem... Cóż, dzięki za to.";
				link.l1.go = "exit";
			}
			else
			{
				if(!bImCasual) pchar.quest.SharkGoldFleet21.over = "yes"; 
				if(!bImCasual) pchar.quest.SharkGoldFleet30.over = "yes"; 
				if(GetCompanionQuantity(pchar) > 1)
				{
					pchar.questTemp.SharkGoldFleet = "toCurierWait";
					AddQuestRecord("SharkGoldFleet", "10");
					SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
					dialog.text = "Widzę, że nie masz nawet jednego statku. Musisz być bogatym kupcem. Hmm... Ale znam wszystkich miejscowych kupców z eskadrami na pamięć, ale ciebie nie znam. Więc nie miej mi tego za złe, ale nie mogę powierzyć ci niczego poważnego.";
					link.l1 = "Zrozumiałem... Cóż, dzięki za to.";
					link.l1.go = "exit";
				}
				else
				{
					if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
					{
						pchar.questTemp.SharkGoldFleet = "toCurierWait";
						AddQuestRecord("SharkGoldFleet", "11");
						SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
						dialog.text = "Hmm... Mam zadanie. Tylko teraz twój statek nie pasuje. Potrzebuję statku, który jest szybki i potężny jednocześnie, a twój nie spełnia w pełni tych wymagań. Przynajmniej w tym samym czasie. Więc proszę, wybacz mi.";
						link.l1 = "Zrozumiałem... Cóż, dzięki za to.";
						link.l1.go = "exit";
					}
					else
					{
						if(!CheckAttribute(pchar,"questTemp.SharkGoldFleet.LicenceOk"))
						{
							pchar.questTemp.SharkGoldFleet = "toCurierWait";
							AddQuestRecord("SharkGoldFleet", "12");
							SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
							dialog.text = "  Mam coś do załatwienia... A ty masz dobrą łajbę. Nie wygląda ona jednak na kupiecką. I, o ile widzę, nie masz długoterminowej licencji od Holenderskiej Kompanii Zachodnioindyjskiej. Nie obrażaj się, ale nie wyglądasz na kupca. Nie mogę podjąć takiego ryzyka.";
							link.l1 = "Rozumiem... Cóż, dzięki za to.";
							link.l1.go = "exit";
						}
						else
						{
							if(pchar.questTemp.SharkGoldFleet != "toCarPortOffice" || GetSquadronGoods(pchar, GOOD_COFFEE) < 300 || GetSquadronGoods(pchar, GOOD_CHOCOLATE) < 300)
							{
								pchar.questTemp.SharkGoldFleet = "toCurierWait";
								AddQuestRecord("SharkGoldFleet", "13");
								SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
								dialog.text = "Mam coś do załatwienia... A ty masz dobrą łajbę. Tylko teraz nie rozumiem, czym zamierzasz handlować... Powiedziałeś, że wybierasz się do Porto Bello, by sprzedać towary, ale, o ile mi wiadomo, nie kupiłeś ich od nas w kolonii. Nie obraź się, ale nie wyglądasz na kupca. Nie mogę podjąć tego ryzyka.";
								link.l1 = "Zrozumiałem... Cóż, dzięki za to.";
								link.l1.go = "exit";
							}
							else
							{
								dialog.text = "  Mam coś do zrobienia. Oczywiście, nie znam cię... Ale, prawdę mówiąc, pamiętam tylko kupców z eskadrami przy ich nazwiskach. Reszty - nie. Tak, i masz długoterminową licencję, od razu widać doświadczonego kupca. Twój statek, jednakże, jest interesujący. Czemu handlować na fregacie?";
								link.l1 = "Hah, to nie jest zwykła fregata. Może osiągnąć bardzo dużą prędkość nawet z pełnym ładunkiem. Zawsze łatwiej jest uciec przed piratami, niż z nimi walczyć, prawda? Chociaż mój statek ma mniejszą pojemność niż zwykłe statki handlowe, ryzyko jest znacznie mniejsze.";
								link.l1.go = "SharkGoldFleet_01";
							}
						}
						
					}
					
				}
			}
		break;
		
		case "SharkGoldFleet_01":
			dialog.text = "Hmm, ale masz rację! Hiszpanie wiedzą, jak budować statki, prawda? Tak, tak, od razu zobaczyłem, że ten przystojniak opuścił stocznie naszych stoczni. I tak, właściwie dzisiaj mi powiedziano, że kupiłeś partię kawy i kakao od naszego kupca na odsprzedaż w Porto Bello. Dobry interes, mówię ci. Ludzie nieznający się na handlu nie wiedzą, że te towary są tu tanie, dzięki plantacjom, a w Porto Bello cieszą się dużym popytem, ponieważ stamtąd trafiają do metropolii.";
			link.l1 = "Cóż, o to właśnie chodzi, señor. Za kilka pesos nie pływałbym moją łajbą tak daleko.";
			link.l1.go = "SharkGoldFleet_02";
		break;
		
		case "SharkGoldFleet_02":
			dialog.text = "Cóż, prawdę mówiąc, mam dla ciebie interes. I bardzo dobrze, że masz tak szybki statek, który w razie potrzeby potrafi się bronić.";
			link.l1 = "Poczekaj, señor... Twoja sprawa sugeruje, że muszę walczyć...?";
			link.l1.go = "SharkGoldFleet_03";
		break;
		
		case "SharkGoldFleet_03":
			dialog.text = "Nie, nie! W rzeczywistości moje zadanie jest tak proste, jak to tylko możliwe. Potrzebuję, abyś dostarczył jeden list do Urzędu Portowego w Porto Bello. List jest zapieczętowany i nie można go otworzyć. Nikt nie musi o nim mówić, korespondencja... osobista. Przekaż osobiście. Termin to dziesięć dni. Potem będzie to już nieważne.";
			link.l1 = "Tak proste? A ile za to dostanę?";
			link.l1.go = "SharkGoldFleet_04";
		break;
		
		case "SharkGoldFleet_04":
			dialog.text = "Pięć tysięcy pesos. Potraktuj to jako oszczędność wysyłania kuriera lugra do Porto Bello.";
			link.l1 = "A jakie były twoje pytania o mnie i mój statek?";
			link.l1.go = "SharkGoldFleet_05";
		break;
		
		case "SharkGoldFleet_05":
			dialog.text = "Nie szkodzi. Po prostu ta korespondencja jest na tyle ważna, że muszę mieć pewność, że dotrze do adresata. I tak nic szczególnego. Biurokracja... Dla zwykłego człowieka te dokumenty nie są interesujące.";
			link.l1 = "Cóż, zgadzam się. Załatwmy twoje dokumenty tutaj. Jak tylko dotrę do Porto Bello, przekażę je twojemu koledze. Poradzę sobie w dziesięć dni, nie martw się.";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_06":
			dialog.text = "Chwileczkę. Przepraszam, zupełnie zapomniałem twojego imienia. Czy możesz mi je podać, proszę? Muszę je zapisać w dokumentach.";
			link.l1 = "Nazywam się Andreas Garcia.";
			link.l1.go = "SharkGoldFleet_07";
		break;
		
		case "SharkGoldFleet_07":
			dialog.text = "Dziękuję. Więc... Wspaniale. Pamiętaj, że to ty musisz dostarczyć ten dokument bezpośrednio w ręce adresata. Proszę bardzo. Nagrodę otrzymasz od szefa Urzędu Portowego w Porto Bello. Szczęśliwej podróży!";
			link.l1 = "Dziękuję! Teraz, przepraszam.";
			link.l1.go = "SharkGoldFleet_08";
		break;
		
		case "SharkGoldFleet_08":
			DialogExit();
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleetToPB10", 0, 0, 10, false);
			else NewGameTip("Exploration mode: timer is disabled.");
			AddCharacterSkillDontClearExp(pchar, SKILL_LEADERSHIP, 1);
			AddCharacterSkillDontClearExp(pchar, SKILL_SNEAK, 1);
			TakeNItems(pchar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_SharkGoldFleet_1");
			AddQuestRecord("SharkGoldFleet", "14");
			pchar.questTemp.SharkGoldFleet = "toPBPortOffice";
		break;
		
		case "SharkGoldFleet_09":
			RemoveItems(PChar, "letter_2", 1);
			ChangeItemDescribe("letter_2", "itmdescr_letter_2");
			dialog.text = "Świetnie! Bardzo mi pomogłeś. Czy napotkałeś jakieś trudności?";
			link.l1 = "Nie, nie było żadnych trudności. Prawda, że twój kolega przeklinał na ciebie: powiedział, że wszyscy tu jesteście skąpcami, bo nie wysyłacie statku kurierskiego, tylko przechodzących kupców, a nawet obciążacie opłatą odbiorcę. Groził, że napisze skargę do Hawany...";
			link.l1.go = "SharkGoldFleet_10";
		break;
		
		case "SharkGoldFleet_10":
			dialog.text = "Co?! Czyżbym to ja był zrzędą?! Co on sobie tam myślał? Najpierw, zatrzymaj swoje pięć... nie, sześć tysięcy pesos! Płaczę uczciwie!";
			link.l1 = "Dziękuję. Miło widzieć, że twój kolega mylił się w swojej opinii o tobie.";
			link.l1.go = "SharkGoldFleet_11";
		break;
		
		case "SharkGoldFleet_11":
			AddMoneyToCharacter(pchar, 6000);
			dialog.text = "A po drugie, ten łajdak zdaje się zapomniał, jak dwa miesiące temu obciążył mnie wszystkimi kosztami utrzymania statku handlowego, który płynął z Caracas do Porto Bello, a stamtąd do Hawany! A umówiliśmy się, że zapłaci za drugą część podróży! I nigdy nie zwrócił długu, ale obiecał, że wszystko spłaci w zeszłym miesiącu! A ja wciąż biedny... Tak, sam napiszę na niego skargę do Hawany!";
			link.l1 = "Cóż, masz oczywiście pasje madryckiego podwórza ...";
			link.l1.go = "SharkGoldFleet_12";
		break;
		
		case "SharkGoldFleet_12":
			AddQuestRecord("SharkGoldFleet", "20");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date)
			pchar.questTemp.SharkGoldFleet = "LightVarToShark";
			SetFunctionLocationCondition("SharkGoldFleetToShark", "Curacao", false);
			dialog.text = "Nie, jak tak pomyśleć... Co za bezczelność! Dobrze, zajmę się nim jeszcze raz... A teraz proszę o wybaczenie: mam pilne sprawy do załatwienia. To była przyjemność robić z tobą interesy!";
			link.l1 = "I powodzenia!";
			link.l1.go = "exit";
		break;
		
		case "SharkGoldFleet_13":
			RemoveItems(PChar, "letter_2", 1);
			ChangeItemDescribe("letter_2", "itmdescr_letter_2");
			dialog.text = "Świetnie! Bardzo mi pomogłeś. Chociaż wysłałem do nich kuriera lugra, a oni odesłali mi odpowiedź przez przepływający statek. Tak... A potem jeszcze narzekają, że mamy tutaj skąpców.";
			link.l1 = "Cóż, może oszczędzili pieniądze na kuriera ...";
			link.l1.go = "SharkGoldFleet_14";
		break;
		
		case "SharkGoldFleet_14":
			AddMoneyToCharacter(pchar, 5000);
			AddQuestRecord("SharkGoldFleet", "20");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date)
			pchar.questTemp.SharkGoldFleet = "DifficultVarToShark";
			SetFunctionLocationCondition("SharkGoldFleetToShark", "Curacao", false);
			dialog.text = "Nie 'może', ale na pewno, mówię ci! Dobrze, to nie ma znaczenia. Proszę, weź swoją pracę. A teraz mam dużo roboty, wybacz.";
			link.l1 = "No cóż, może oszczędzili pieniądze na kuriera ...";
			link.l1.go = "exit";
		break;
		// <-- на пару с Акулой
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

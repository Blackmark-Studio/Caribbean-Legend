// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Mów, słucham";
			link.l1 = "Pomyliłem się. Żegnaj.";
			link.l1.go = "Exit";
			//искушение барбазона
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.Prison"))
            { 
                link.l1 = "Macie tutaj Simona Morelle'a w areszcie. Jest przemytnikiem, którego szkuner został niedawno zatopiony przez patrol. Czy mogę go zobaczyć?";
                link.l1.go = "BarbTemptation";
				DeleteAttribute(pchar, "questTemp.Saga.BarbTemptation.Prison");
            }
			// Addon-2016 Jason ФМК-Сент-Кристофер
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "way_div")
			{
				link.l1 = "Oficerze, zostałem wysłany tutaj przez pana gubernatora Philipsburga. Poprosił mnie, abym zaatakował wyspę i jej wody w poszukiwaniu angielskich szpiegów. Jego Ekscelencja również powiedział mi, że możesz dostarczyć mi przydatnych informacji.";
				link.l1.go = "FMQN";
			}
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "way_div_2")
			{
				link.l1 = "Oficerze, znalazłem zaginiony patrol. Znalazłem także brytyjskich szpiegów. Są tutaj na wyspie.";
				link.l1.go = "FMQN_3";
			}
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "hol_peace_rew")
			{
				link.l1 = "To znowu ja, oficerze. Czy zatrzymaliście szpiegów?";
				link.l1.go = "FMQN_8";
			}
		break;
		
		//искушение барбазона
		case "BarbTemptation":
			dialog.text = "A po co ci on, panie?";
			link.l1 = "Chcę mu powiedzieć, że jest przeklętym łajdakiem i łotrem. Mam nadzieję, że to mu pomoże stojąc na szubienicy.";
			link.l1.go = "BarbTemptation_1";
		break;
		
		case "BarbTemptation_1":
			dialog.text = "Ha-ha! Masz poczucie humoru, panie... Cóż, dwa tysiące pesos i możesz iść dalej.";
			if(int(Pchar.money) >= 2000)
			{
				link.l1 = "Weź to, oficerze. Dzięki!";
				link.l1.go = "BarbTemptation_2";
			}
			link.l2 = "Hm... Wiesz co, zmieniłem zdanie. Lepiej przepuszczę moje pieniądze w tawernie.";
			link.l2.go = "BarbTemptation_4";
		break;
		
		case "BarbTemptation_2":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "Proszę bardzo... Ruszaj dalej!";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
		break;
		
		case "BarbTemptation_4":
			dialog.text = "Jak sobie życzysz, następnym razem nie dostaniesz takiej propozycji.";
			link.l1 = "Nie potrzebuję tego w każdym razie. Do zobaczenia, oficerze!";
			link.l1.go = "exit";
		break;
		
		// Addon-2016 Jason ФМК-Сент-Кристофер
		case "FMQN":
			DelLandQuestMark(npchar);
			dialog.text = "Przydatne? Ha! Z drugiej strony, zaczekaj. Mam coś przydatnego do powiedzenia. Jeden z naszych patroli zaginął w dżungli. Powinni byli już wrócić do swoich koszar, ale wydaje się, że wolą towarzystwo papug. Albo naprawdę coś się stało. Jeśli ich znajdziesz podczas swoich poszukiwań, proszę, powiedz im, żeby wymyślili sensowne usprawiedliwienie swojego opóźnienia, bo inaczej nie spodoba im się konsekwencje... Dowódcą patrolu jest niejaki Jannes Hoffman.";
			link.l1 = "Czy to wszystko, oficerze?";
			link.l1.go = "FMQN_1";
		break;
		
		case "FMQN_1":
			dialog.text = "Tak, cholera. Przykro mi, ale nie mam nic więcej do powiedzenia. Powodzenia, kapitanie.";
			link.l1 = "Dziękuję...";
			link.l1.go = "FMQN_2";
		break;
		
		case "FMQN_2":
			DialogExit();
			pchar.questTemp.FMQN = "way_div_1";
			AddQuestRecord("FMQ_Nevis", "10");
			FMQN_SetSoldiersInCave();
		break;
		
		case "FMQN_3":
			DelLandQuestMark(npchar);
			dialog.text = "Co?! Mam nadzieję, że sobie nie żartujesz? Złóż mi raport!";
			link.l1 = "Spotkałem patrol w pobliżu jaskini w dżungli. Zatrzymali mnie i spytali, dokąd zmierzam i dlaczego, po czym pozwolili mi odejść. Niech mnie diabli, jeśli to nie byli Brytyjczycy przebrani w holenderskie mundury! Widziałem też coś ciekawego w dżungli, co wyglądało dokładnie jak gromada nagich mężczyzn ukrytych w krzakach. Przypuszczam, że brytyjska grupa rajdowa rozbroiła twój patrol i przejęła ich mundury.";
			link.l1.go = "FMQN_4";
		break;
		
		case "FMQN_4":
			dialog.text = "... ";
			link.l1 = "Jak rozumiesz, nie zaryzykowałem walki z oddziałem wyszkolonych czerwonych kurt i zamiast tego pośpieszyłem do ciebie z raportem.";
			link.l1.go = "FMQN_5";
		break;
		
		case "FMQN_5":
			dialog.text = "No, no... Jaskinia, mówisz? Ile ich naliczyłeś??";
			link.l1 = "Pięciu ludzi. I tak, myślę, że weszli do tej jaskini.";
			link.l1.go = "FMQN_6";
		break;
		
		case "FMQN_6":
			dialog.text = "Wysyłam natychmiast oddział do jaskini! Kapitanie, jeśli ludzie, których spotkałeś, naprawdę są brytyjskimi szpiegami, otrzymasz zasłużoną nagrodę. Możesz dołączyć do oddziału, jeśli chcesz pomóc władzom w zatrzymaniu tych drani i otrzymać dodatkową nagrodę, to w końcu rozkazy gubernatora. Więc, idziesz z nami?";
			link.l1 = "Nie oficerze, ściganie szpiegów to twoja robota. Upewnij się, że wyślesz dobrze uzbrojoną drużynę, te kanalie są zbyt niebezpieczne...";
			link.l1.go = "FMQN_7";
			link.l2 = "Myślę, że mogę to zrobić. Twoi ludzie szybciej znajdą szpiegów z moją pomocą.";
			link.l2.go = "FMQN_10";
		break;
		
		case "FMQN_7":
			dialog.text = "Twój wybór, kapitanie, wezmę twoją radę pod uwagę. Przyjdź do mnie jutro, aby usłyszeć o wynikach naszej operacji.";
			link.l1 = "Do zobaczenia jutro.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_HollandPeace");
		break;
		
		case "FMQN_8":
			DelLandQuestMark(npchar);
			dialog.text = "Twoje informacje były trafne, kapitanie. Znaleźliśmy tych drani w jaskini. Nie mieli zamiaru się poddać i wdali się w bójkę. W rezultacie - wyeliminowaliśmy ich wszystkich. Znaleźliśmy także zaginiony patrol. Są cali i zdrowi, chociaż nieco poturbowani... Dziękujemy, kapitanie, w imieniu wszystkich dobrych obywateli Philipsburga. Twoja czujność zostanie nagrodzona zgodnie z obietnicą. Proszę, weź to.";
			link.l1 = "Dziękuję!";
			link.l1.go = "FMQN_9";
		break;
		
		case "FMQN_9":
			AddMoneyToCharacter(pchar, 10000);
			dialog.text = "Zawsze jesteś mile widzianym gościem na Sint-Maarten. Teraz, proszę wybacz, mam inne sprawy do załatwienia.";
			link.l1 = "Ja też. Żegnaj.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_HollandPeaceComplete");
		break;
		
		case "FMQN_10":
			dialog.text = "Zgoda. Twoja pomoc jest bardzo doceniana. Udaj się do bram miasta, oddział karny zbierze się tam za godzinę.";
			link.l1 = "Mała rada, powinieneś wysłać najlepszych żołnierzy, jakich masz, na tę misję. Ci szpiedzy są niebezpieczni.";
			link.l1.go = "FMQN_11";
		break;
		
		case "FMQN_11":
			dialog.text = "Nie martw się. Wysyłam naszych najbardziej doświadczonych żołnierzy pod dowództwem oficera Hansa Shulte'a - mistrza szermierki z Philipsburga.";
			link.l1 = "Świetnie! Nie traćmy więc czasu.";
			link.l1.go = "exit";
			WaitDate("",0,0,0,1,5);
			AddDialogExitQuestFunction("FMQN_HollandBattle");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

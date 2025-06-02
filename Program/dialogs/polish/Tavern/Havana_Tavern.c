// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Wszystkie plotki o "+GetCityName(npchar.city)+" do usług. Czego chciałbyś się dowiedzieć?","Rozmawialiśmy właśnie o tym. Musiałeś zapomnieć...","To już trzeci raz dzisiaj, kiedy mówisz o jakimś pytaniu...","Powtarzasz się jak papuga...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Wiesz, "+NPChar.name+"może następnym razem.","Racja, zapomniałem z jakiegoś powodu...","Tak, to naprawdę jest trzeci raz...","Tak...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Slavetrader") && pchar.questTemp.Slavetrader == "FindRatHavana")
            {
                link.l1 = "Czy przypadkiem nie zatrzymał się w twoim mieście Francois Gontier? Ma korwetę '"+pchar.questTemp.Slavetrader.ShipName+" , na wszelki wypadek... ";
                link.l1.go = "Havana_ratT_1";
            }
			if (CheckAttribute(npchar, "quest.batabano"))
            {
                link.l1 = "Powiedz mi, kumplu, gdzie mógłbym znaleźć Don Diego de Montoya? Czy jestem spóźniony? Czy już odpłynął do Main?";
                link.l1.go = "guardoftruth";
            }
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "Słuchaj, czy zatrzymał się tu człowiek o imieniu Joachim Merriman? Średniego wieku doktor, Portugalczyk, z wąsami, cesarską brodą i przenikliwymi oczami? Może chciał wynająć pokój?";
				link.l1.go = "caleuche";
			}
		break;

		case "Havana_ratT_1":
			dialog.text = "Aha, ten ponury jegomość? Tak, zatrzymał się u mnie. Powiem ci coś: miał spotkanie z Oregon-and-Haskon. Złożył wniosek o otrzymanie patentu. Ale nie wyszło mu to i stamtąd wyszedł.";
			Link.l1 = "A gdzież on odpłynął, wiesz może? Gonię go od Porto Bello i nie mogę go znaleźć.";
			Link.l1.go = "Havana_ratT_2";
		break;
		
		case "Havana_ratT_2":
			dialog.text = "Czego od niego potrzebujesz? On boi się obcych, zawsze się przed nimi chowa, jak tylko zobaczy uzbrojonego nieznajomego, chwyta za miecz. Chodzi tylko w otoczeniu czterech strażników. Czy przypadkiem jesteś tym, przed kim się strzeże?";
			Link.l1 = "Panie, ludzie mówią to w kółko! Co, wyglądam na zabójcę? To mój stary druh, spieszę się, by przekazać mu pewne wieści, będzie niezmiernie zadowolony, wiedząc, że nie musi się już ukrywać, nikt go nie szuka.";
			Link.l1.go = "Havana_ratT_3";
		break;
		
		case "Havana_ratT_3":
			dialog.text = "Nie musi się ukrywać? Ha-ha-ha! Zaledwie dzień przed jego odjazdem z Hawany cała banda łotrów próbowała go zabić w dżungli... Oczywiście, miał swoich ludzi i w mgnieniu oka zamienili ich w mielone. A ty tutaj mówisz...";
			Link.l1 = "Oj, daj spokój. To pewnie tylko jakieś miejscowe bandziory, które próbowały dobrać się do jego sakiewki. Sam wiesz, ilu łajdaków kręci się po dżungli. Więc dokąd poszedł?";
			Link.l1.go = "Havana_ratT_4";
		break;
		
		case "Havana_ratT_4":
			dialog.text = "Cóż, po tym jak został wysłany daleko i na długo z rezydencji, ciągle powtarzał, że odda się żabojadom, swoim rodakom. Udał się na Tortugę, do jakiegoś d'Ogerona... Mruczał też coś o swojej kochance, ale nie do końca go zrozumiałem.";
			Link.l1 = "Więc, Tortuga? Świetnie! Mam nadzieję, że go tam złapię. Dziękuję, "+npchar.name+", byłeś ogromną pomocą. Żegnaj.";
			Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_7");
			pchar.questTemp.Slavetrader = "FindRatTortuga";
			pchar.quest.Slavetrader_findTortugaRat.win_condition.l1 = "location";
            pchar.quest.Slavetrader_findTortugaRat.win_condition.l1.location = "Tortuga_HouseHut";
            pchar.quest.Slavetrader_findTortugaRat.win_condition = "Slavetrader_findTortugaRat";
		break;

		case "guardoftruth":
			dialog.text = "Hm... A dlaczego to Francuz miałby się interesować Don Diego, co?";
			link.l1 = "Fakt, że jestem Francuzem, jest nieistotny. Ważny jest ten dokument podpisany przez Inkwizytora. Spójrz... widzisz teraz? Mam pilną wiadomość dla Diego.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "A-ha, zatem pracujesz dla Jego Czcigodności, Ojca Vincento? To zmienia postać rzeczy. Don Diego de Montoya wyjechał dwa dni temu ze swoją eskadrą, ale wkrótce wrócił na swoim kurierze lugrze. Jeden z jego statków osiadł na mieliznach na południu Kuby, więc właśnie dzisiaj kupował materiały do naprawy\nSprawdź zatokę na południu, znajdziesz tam statek i samego człowieka. Wątpię, by już zdążyli załatać dziury.";
			link.l1 = "Dzięki, kumplu! Byłeś wielką pomocą!";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Ani trochę, o każdej porze. Zawsze chętnie pomogę jezuickiemu bratu.";
			link.l1 = "Aj, pax vobiscum i te inne.";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			DialogExit();
			DeleteAttribute(npchar, "quest.batabano");
			AddQuestRecord("Guardoftruth", "47");
			pchar.quest.GuardOT_Batabano.win_condition.l1 = "location";
			pchar.quest.GuardOT_Batabano.win_condition.l1.location = "Shore13";
			pchar.quest.GuardOT_Batabano.function = "GuardOT_SanAntonioPrepare";
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "Diabeł go wie, kumplu. Może i przybył, ale nic mi o tym nie wiadomo. Przepraszam.";
			link.l1 = "Widzę. Szkoda. Będę kontynuować moje poszukiwania...";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

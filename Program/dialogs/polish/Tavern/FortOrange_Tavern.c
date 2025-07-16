// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie masz pytania?","Jak mogę ci pomóc, "+GetAddress_Form(NPChar)+"?"),"Próbowałeś zadać mi jakieś pytanie niedawno, "+GetAddress_Form(NPChar)+"... ","Przez cały ten dzień, to już trzeci raz, kiedy rozmawiasz o jakimś pytaniu...","Więcej pytań, jak mniemam?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniam zdanie...","Nie mam teraz o czym rozmawiać."),"Umph, gdzie podziała się moja pamięć...","Tak, to naprawdę już trzeci raz...","Nie, jakie pytania?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatJamaica")
            {
                link.l1 = "Czy w twoim mieście zatrzymał się człowiek o imieniu Francois Gontier? Naprawdę go potrzebuję.";
                link.l1.go = "Jamaica_ratF_1";
            }
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_4")
            {
                link.l1 = "Słuchaj, kumplu, z Port Royal wypływa statek, który kupuje jedwab dla swojej stoczni... bardzo specjalny jedwab, na pewno o nim słyszałeś. Mówią, że sprzedawca takiego jedwabiu przebywa gdzieś w tej osadzie. Masz jakieś wskazówki, jak go znaleźć? Mam dla niego propozycję biznesową.";
                link.l1.go = "mtraxx";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_5" && (PCharDublonsTotal() >= 50))
            {
                link.l1 = "Mam przy sobie pięćdziesiąt dublonów. Weź je i zacznij mówić.";
                link.l1.go = "mtraxx_4_1";
			}
		break;

		case "Jamaica_ratF_1":
			dialog.text = "Był tutaj. Wynajmował pokój przez kilka dni. Nie był to najprzyjemniejszy typ, powiem ci. Poza tym, był obsesyjnie paranoiczny, że ktoś go szuka. Zawsze był przestraszony i rozglądał się wokół. Czy to ty jesteś tym człowiekiem, którego tak się bał?";
			link.l1 = "Nie, to nie ja. Wiesz, kaperzy mają wielu wrogów. Więc, gdzie mogę go znaleźć? On i ja postanowiliśmy się dogadać, ale wygląda na to, że ziemia go pochłonęła.";
			link.l1.go = "Jamaica_ratF_2";
		break;
		
		case "Jamaica_ratF_2":
			dialog.text = "Odpłynął na morze na własnym statku. Nie wiem dokąd. Nie wtajemniczył mnie w to.";
			link.l1 = "Ach, co za szkoda! Gdzie teraz mam go szukać?";
			link.l1.go = "Jamaica_ratF_3";
		break;
		
		case "Jamaica_ratF_3":
			dialog.text = "Nie wiem, kumplu. Powiedziałbym ci, gdybym wiedział.";
			link.l1 = "Dobrze, rozumiem. Pójdę zapytać innych ludzi...";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_4");
			pchar.questTemp.Slavetrader = "FindRatJamaica_H";
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx":
            dialog.text = "Hm, jeśli podejrzewasz naszego kupca, tego co prowadzi sklep, mogę powiedzieć, że to nie on, nie handluje jedwabiem na żagle. Przemytnicy też tutaj nie przychodzą, nie ma potrzeby, skoro nie ma izby celnej. Zresztą nikt inny, oprócz naszego kupca, i tak tu nie handluje. Rozejrzyj się, nie jesteśmy takimi ludźmi, ha-ha!";
			link.l1 = "Ale ktoś dostarcza jedwab do Port Royal - to niezaprzeczalne. Czy masz jakikolwiek pomysł, kto mógłby być dostawcą?";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = "Przemytnicy z Port Royal, może? Albo zbuntowani piraci? Na pewno rozładowują swój łup w jakiejś ukrytej zatoce... Ha! Mam pomysł, kumplu. Jest tu jeden miejscowy, zna wszystko, co się dzieje na tych wodach. Jeśli on nie będzie miał żadnych przypuszczeń, to nie ma kupców jedwabiu.";
			link.l1 = "Wspaniale! Jak się nazywa ten facet?";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "Hm... Próbuję przypomnieć sobie jego imię, ale z jakiegoś powodu po prostu nie mogę...";
			link.l1 = "Może kilka monet odświeży twoją pamięć?";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "Przypuszczam, że to może pomóc... Pięćdziesiąt złotych dublonów na pewno rozświetli tę starą głowę.";
			if (PCharDublonsTotal() >= 50) // Rebbebion, учёт количества дублонов из рундука
			{
				link.l1 = "Rozumiem. Oto monety.";
				link.l1.go = "mtraxx_4_1";
			}
			else
			{
				link.l1 = "Rozumiem. Wrócę...";
				link.l1.go = "mtraxx_4_2";
			}
		break;
		
		case "mtraxx_4_1":
			RemoveDublonsFromPCharTotal(50);
			PlaySound("interface\important_item.wav");
            dialog.text = "Husky Billy to człowiek, którego potrzebujesz. Mieszka na Jamajce od zawsze, zna każdy pies na ulicach. Był kiedyś piratem i utrapieniem dla Brytyjczyków, dopóki nie został ranny jakieś trzy lata temu. Teraz głównie łowi ryby, poluje na rekiny i zbiera bursztyn w zatokach Jamajki. Opuszcza swoją starą łódź tylko po to, by kupić więcej rumu i sucharów\nPowinieneś go szukać na wodach wokół Jamajki. Mówią, że żegluje po północnej stronie, aż do najbardziej wysuniętego na wschód punktu. Ale gonienie łodzi jest szaleństwem, lepiej zaczaić się wokół południowo-zachodniego rogu, mówią, że widziano go w pobliżu Przylądka Negril około raz w tygodniu. Jego łódź nazywa się 'The Fly Fish'.";
			link.l1 = "Dzięki, kamracie. Zarobiłeś swoje złoto.";
			link.l1.go = "mtraxx_5";
		break;
		
		case "mtraxx_5":
            dialog.text = "Powodzenia, kamracie! Mam nadzieję, że znajdziesz to, czego szukasz!";
			link.l1 = "...";
			link.l1.go = "mtraxx_6";
		break;
		
		case "mtraxx_4_2":
            DialogExit();
			AddQuestRecord("Roger_2", "6");
			pchar.questTemp.Mtraxx = "silk_5";
		break;
		
		case "mtraxx_6":
            DialogExit();
			AddQuestRecord("Roger_2", "7");
			pchar.questTemp.Mtraxx = "silk_6";
			/*pchar.quest.mtr_negril.win_condition.l1 = "Timer";
			pchar.quest.mtr_negril.win_condition.l1.date.hour  = 12+rand(12);
			pchar.quest.mtr_negril.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2+rand(3));
			pchar.quest.mtr_negril.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2+rand(3));
			pchar.quest.mtr_negril.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2+rand(3));*/
			PChar.quest.mtr_negril.win_condition.l1 = "ExitFromLocation";
			PChar.quest.mtr_negril.win_condition.l1.location = PChar.location;
			pchar.quest.mtr_negril.function = "Mtraxx_CreateBilly";
			SetFunctionTimerCondition("Mtraxx_BillySeaTimeOver", 0, 0, 7, false);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie masz pytania?","Jak mogę ci pomóc, "+GetAddress_Form(NPChar)+"?"),"Próbowałeś zadać mi jakieś pytanie niedawno, "+GetAddress_Form(NPChar)+"... ","Przez cały ten dzień to już trzeci raz, kiedy mówisz o jakimś pytaniu...","Więcej pytań, jak mniemam?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniam zdanie...","Nie mam teraz nic do powiedzenia."),"Umph, gdzie podziała się moja pamięć...","Tak, to naprawdę jest trzeci raz...","Nie, jakie pytania?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(PChar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "islatesorotavern")
			{
				link.l1 = "Słuchaj, "+npchar.name+", słyszałeś coś o człowieku imieniem Miguel Dichoso? Mówią, że jego statek widziano na wodach Isla Tesoro...";
				link.l1.go = "guardoftruth";
			}
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				link.l1 = "Słuchaj, "+npchar.name+", czy ostatnio widziałeś Miguela Dichoso na Isla Tesoro?";
				link.l1.go = "tieyasal";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Tak, mam. Ten hiszpański don sprzedał Sharkowi Dodsonowi niezwykły statek, fregatę, gdy jeszcze tutaj mieszkał. Ach, ten statek... Była niesamowita...";
			link.l1 = "Pozwól, że zgadnę: miała nowoczesną smukłą sylwetkę i była zdolna osiągnąć szesnaście węzłów? A jej imię to 'Santa Quitaria'?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Co do kadłuba i prędkości, masz absolutną rację, ale nosiła inne imię: 'San Martin'. Rekin zapłacił temu łotrowi całą kupę złota za ten statek.";
			link.l1 = "Jesteś pewien, że to był 'San Martin', a nie 'Santa Quiteria'? Kiedy go kupił? I dlaczego nazwałeś Dichoso łotrem?";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Niech mnie kule biją, jestem absolutnie pewien, że to był 'San Martin', bo osobiście widziałem, jak pracownicy Alexusa odrywali tę papistyczną bzdurę z rufy. Rekin Dodson nazwał ją 'Fortuna', o wiele bardziej odpowiednie imię dla takiej piękności. (pluje) Kupił ją zimą '54, niedługo przed tym, jak Blaze został zamordowany\nDlaczego nazwałem Don Miguela łajdakiem? Bo ukradł cholerny statek hiszpańskiej marynarce z Providence! Dodson zorganizował przedstawienie z ogniem i dymem dla fortu św. Juana i jego garnizonu, jak mi zawsze opowiadał, gdy był pijany. Rekin poświęcił dwa uszkodzone lugry, aby walka z fregatą wyglądała na prawdziwą\nKiedy nadeszła noc, po cichu odpłynął 'San Martin' na Isla Tesoro. Rekin zdobył statek, a Dichoso dostał pieniądze. Sprytny drań później powiedział swoim przełożonym, że fregata zatonęła podczas walki z flotą piracką, a komendant fortu św. Juana to potwierdził.";
			link.l1 = "O, jakże ci hiszpańscy grandowie napychają sobie kieszenie! Co za spryciarz! Powiedz mi, czy jesteś pewien, że to się stało zimą 1654 roku? Czy mogło to być podczas wiosny? I czy tamta fregata nie wykazywała oznak zużycia po burzy?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Jestem pewien, że to była zima... Och, kto wie. Może to była wiosna. Nie pamiętam dokładnie. Pewnie byłem pijany. Fregata wcale nie była zużyta, była zupełnie nowiutka.";
			link.l1 = "A gdzie teraz jest ten piękny fregat?";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "To mroczna opowieść... Kiedy Blaze został zamordowany, wszyscy podejrzewali Rekina, ponieważ na zwłokach znaleziono jego naszyjnik, ząb rekina. Dodatkowo, niektórzy widzieli Rekina w rezydencji Blaze'a tamtej nocy\nRekin uciekł z Isla Tesoro, zanim dostał czarną plamę. Odwiedził Czarnego Pastora i zamienił swoją fregatę na bryg. Nie wiadomo, gdzie teraz jest ten człowiek. Zachary później sprzedał fregatę Williamowi Patersonowi.";
			link.l1 = "Kim jest ten Paterson?";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Co, nigdy nie słyszałeś o Willie Patersonie? To Szkot, który dopiero co przybył na Karaiby. Uważa się za kapitana królewskiej floty, ulubieńca samego pułkownika Foxa! A tak przy okazji, właśnie zaczął kręcić jakieś interesy z Jackmanem. Okręt flagowy Patersona to sama 'Fortuna'.";
			link.l1 = "Rozumiem. Czy wiesz, gdzie teraz jest Dichoso?";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "Nie mam pojęcia. Po tym całym zamieszaniu z 'Fortuną' nie widziałem go na Isla Tesoro i nic o nim nie słyszałem.";
			link.l1 = "W porządku, "+npchar.name+", dzięki za wyczerpujące informacje! Jesteś doskonałym karczmarzem! Chciałbym, aby było więcej takich ludzi jak ty... Do widzenia!";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Powodzenia, "+pchar.name+"!";
			link.l1 = "...";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			DialogExit();
			AddQuestRecord("Guardoftruth", "60_1");
			pchar.questTemp.Guardoftruth.Archy = "guadeloupe";
			// маленькая развлекуха
			pchar.quest.GuardOT_cabinattack.win_condition.l1 = "EnterToSea";
			pchar.quest.GuardOT_cabinattack.function = "GuardOT_PrepareCreateBandosInCabin";
		break;
		
		case "tieyasal":
			dialog.text = "Wydaje się, że obaj się ścigacie, kumplu. Tak, Dichoso był tutaj, dokładnie tam, gdzie teraz stoisz. I dokładnie w ten sam sposób wypytywał o ciebie, jak ostatnim razem, gdy byłeś w Sharptown.";
			link.l1 = "Cholera jasna! To dopiero wieści... A gdzie teraz jest Miguel?";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Nie mam pojęcia. Wypłynął na morze, gdzie... wspomniał coś o Blueweld. Pewnie tam pojechał tylko po to, by cię znaleźć.";
			link.l1 = "Czy to przypadkiem ty wysłałeś go do Blueweld?";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "Nie. Wszystko, co mu powiedziałem, to że dawno cię nie widziałem.";
			link.l1 = "Rozumiem. Dobrze, zatem. Dzięki, kumplu!";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			DialogExit();
			AddQuestRecord("Tieyasal", "3");
			npchar.quest.tieyasal = "true";
			pchar.quest.Tieyasal_ITAttack.win_condition.l1 = "location";
			pchar.quest.Tieyasal_ITAttack.win_condition.l1.location = "Bermudes";
			pchar.quest.Tieyasal_ITAttack.function = "Tieyasal_CreateITShips";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

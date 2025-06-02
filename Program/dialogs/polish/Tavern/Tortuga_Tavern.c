// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Wszystkie plotki o "+GetCityName(npchar.city)+" do usług. Czego chciałbyś się dowiedzieć?","Rozmawialiśmy właśnie o tym. Musiałeś zapomnieć...","To już trzeci raz dzisiaj, kiedy mówisz o jakimś pytaniu...","Powtarzasz wszystko jak papuga...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Wiesz, "+NPChar.name+"Może następnym razem.","Racja, zapomniałem z jakiegoś powodu...","Tak, to naprawdę trzeci raz...","Tak...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatTortuga") // работорговец
            {
                link.l1 = "Słuchaj, gdzie mogę znaleźć Francois Gontier? Miał już dotrzeć do Tortugi.";
                link.l1.go = "Tortuga_ratT_1";
            }
			// суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tortuga" && !CheckAttribute(pchar, "questTemp.Tonzag.TerrapinBlock"))
			{
				link.l1 = "Szukałem Henriego Thibauta. Gdzie mogę go znaleźć?";
				link.l1.go = "terrapin";
			}
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tortuga1" && !CheckAttribute(pchar, "questTemp.Tonzag.TerrapinBlock"))
			{
				link.l1 = "Szukam Henriego Thibauta. Gdzie mogę go znaleźć?";
				link.l1.go = "terrapin_2";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "tortuga")
			{
				link.l1 = "Powiedz mi, czy galeon o nazwie 'Santa Margarita' zatrzymał się ostatnio w twojej kolonii? Może jako nagroda dla kaperów?";
                link.l1.go = "guardoftruth";
			}
			// Addon 2016-1 Jason Пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Jeweller"))
			{
				link.l1 = "Słuchaj, kolego, szukam Gasparda Parmentiera. Gdzie mogę go znaleźć?";
                link.l1.go = "mtraxx_jew";
			}
			// Rebbebion, "Путеводная звезда"
			if (CheckAttribute(pchar, "questTemp.PZ.TortugaCitizensAsk") && !CheckAttribute(npchar, "quest.PZ.Ask.Block"))
			{
				link.l1 = "Możesz mi trochę pomóc, kamracie? Szukam człowieka o imieniu Joep van der Vink. Znasz go?";
				link.l1.go = "PZ1";
			}
        break;
        
		case "Tortuga_ratT_1":
			dialog.text = "Francois Gontier? Kto to jest? Nie znam człowieka o tym imieniu.";
			link.l1 = "Jest kapitanem korwety '"+pchar.questTemp.Slavetrader.ShipName+"'.";
			link.l1.go = "Tortuga_ratT_2";
        break;
		
		case "Tortuga_ratT_2":
			dialog.text = "Nie mam najmniejszego pojęcia, kamracie. I żadna korweta o tej nazwie nie zacumowała w naszym porcie, tego mogę być pewien.";
			link.l1 = "Dobrze więc, widziałeś ostatnio jakichś obcych w mieście?";
			link.l1.go = "Tortuga_ratT_3";
        break;
		
		case "Tortuga_ratT_3":
			dialog.text = "Dobre pytanie! To jest miasto portowe, a nie wioska. Codziennie przybywają tu obcy. Choć słyszałem o pięciu dziwnych chłopakach, zawsze trzymają się razem i mają gotowe szable. Nawet patrol pytał o nich, ale bez skutku. Ale jestem pewien, że nie przybyli tu na korwecie, żadnej takiej jednostki nie widziano w okolicy, rozumiesz?";
			link.l1 = "Hm... Dobrze więc, rozumiem. Dziękuję, "+npchar.name+".";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_8");
			pchar.questTemp.Slavetrader = "wait1";//затычка
        break;
		
		// суп из черепахи
		case "terrapin":
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Monsieur Thibaut to sławny człowiek na Tortudze. Jego rezydencja znajduje się niedaleko urzędu portowego. Wychodząc z tawerny, idź prosto w kierunku portu. Zbliż się do łuku prowadzącego do portu, skręć w lewo na skrzyżowaniu i idź aż do końca ulicy, gdzie natkniesz się na dwupiętrowy kamienny budynek z czerwonym dachem. To jest rezydencja Monsieur Thibaut.";
			link.l1 = "Dziękuję! Pójdę go odwiedzić...";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			DialogExit();
			pchar.questTemp.Terrapin = "house";
			sld = characterFromId("Tibo");
			ChangeCharacterAddressGroup(sld, "Tortuga_houseS2", "barmen", "stay");
			LAi_SetOwnerType(sld);
		break;
		
		case "terrapin_2":
			dialog.text = "Monsieur Thibaut jest dziś bardzo poszukiwany, posłaniec od gubernatora właśnie tu przybiegł. On też się interesował. Czy to takie trudne go znaleźć? Wynajmuje u mnie pokój na drugim piętrze od dłuższego czasu, chociaż ma całą posiadłość, w której mógłby mieszkać. Nie wiem, po co mu to, ale przychodzi znacznie częściej, niż wychodzi. A bywa tam tylko wieczorami.";
			link.l1 = "Może jest tu teraz.";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			if (stf(environment.time) < 20.0 && stf(environment.time) > 8.0)
			{
				dialog.text = "Nie. Powiedział, że nie wróci do ósmej wieczorem dzisiaj. Możesz spróbować poszukać go w domu w jego rezydencji, ale nie sądzę, że go tam znajdziesz. Widziałem go żeglującego na patrolowej lugrze na morzu.";
				link.l1 = "Dziękuję! Wpadnę do niego później.";
				link.l1.go = "terrapin_4";
			}
			else
			{
				dialog.text = "Tak. Jeśli chcesz, możesz wejść na górę.";
				link.l1 = "Dziękuję! Odwiedzę go...";
				link.l1.go = "terrapin_4";
			}
		break;
		
		case "terrapin_4":
			DialogExit();
			pchar.questTemp.Terrapin = "tavern";
			sld = characterFromId("Tibo");
			sld.dialog.currentnode = "tibo_9";
			LAi_SetLoginTime(sld, 20.0, 8.0);
			ChangeCharacterAddressGroup(sld, "Tortuga_tavern_upstairs", "goto", "goto1");
			LocatorReloadEnterDisable("Tortuga_tavern", "reload2_back", false); // откроем комнату
			LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_tavern_upstairs")], true);//запретить драться
			LAi_SetStayType(sld);
			// Addon 2016-1 Jason Пиратская линейка
			if (GetCharacterIndex("Mary") != -1)
			{
				sld = characterFromId("Mary");
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && !IsOfficer(sld))
				{
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
			}
			if (GetCharacterIndex("Helena") != -1)
			{
				sld = characterFromId("Helena");
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && !IsOfficer(sld))
				{
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Nie mam pojęcia, jak nazywał się ten statek, czy to była 'Santa Margarita' czy 'Castylijska Dziwka', ale przywieźli tutaj zdobyty hiszpański galeon. Zdobyty przez slup, nie mniej! To dopiero prawdziwe, cholernie dobre żeglowanie! Gaius Marchais, jego kapitan, chwali się w tawernie od dwóch dni - jego pierwszy rejs i taka zdobycz!\nAye, bardzo heroiczny czyn, abordaż galeonu wypełnionego kościelnymi szczurami bez żołnierzy do ich ochrony. Wydaje się, że ci papistyczni dranie zapomnieli, co się mówi o tych, którzy pomagają sobie sami...";
			link.l1 = "Tak, Bóg pomaga tym, którzy sami sobie pomagają, to na pewno powiedzenie hugenotów. Jak mogę zobaczyć tego szczęśliwego kapitana? Jest tutaj, na Tortudze?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Ach, kto do diabła wie. Nie widziałem go w mojej tawernie od dłuższego czasu. Jak tylko wytrzeźwiał, kupił sobie nowy, lśniący statek za pieniądze z nagrody i biegał po jego pokładzie jak szaleniec. Nie mam pojęcia, gdzie teraz jest Marchais. Może jest na Tortudze, a może na morzu.";
			link.l1 = "Dobrze. Cóż, dzięki za opowieść, kumplu!";
			link.l1.go = "guardoftruth_2";			
		break;
		
		case "guardoftruth_2":
			dialog.text = "Zawsze do usług, Monsieur. Zawsze chętnie pomogę naszemu ukochanemu Kapitanowi "+pchar.name+" , zbawco St. Pierre! Wpadnij później!";
			link.l1 = "...";
			link.l1.go = "exit";	
			AddQuestRecord("Guardoftruth", "8");
			pchar.questTemp.Guardoftruth = "tortuga1";
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		case "mtraxx_jew":
            dialog.text = "Wydaje się, że Gaspard staje się coraz bardziej popularny wśród waszego rodzaju. Jego dom jest przy murze. Skręć w lewo od tawerny i idź w stronę portu, ale tam nie idź, znów skręć w lewo, idź prosto, a potem skręć w prawo. Dwupiętrowy dom.";
			link.l1 = "Dzięki!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekJewellerHouse");
		break;
		
		case "PZ1":
			dialog.text = "Nigdy o nim nie słyszałem.";
			link.l1 = "Być może posługuje się innym imieniem. Może słyszałeś o nim jako o kapitanie brygu 'Banten'?";
			link.l1.go = "PZ2";
		break;
		
		case "PZ2":
			dialog.text = "Też nigdy nie słyszałem o tamtej brygantynie.";
			link.l1 = "Słyszałem, że był tu niedawno. Może trochę srebra odświeży twoją pamięć?";
			link.l1.go = "PZ3";
		break;
		
		case "PZ3":
			npchar.quest.PZ.Ask.Block = true;
			
			dialog.text = "Cóż, zapytaj, gdzie to słyszałeś. Nie mam nic przeciwko przyjęciu twojego srebra.";
			link.l1 = "Nie ma tym razem srebra, więc żegnaj.";
			link.l1.go = "Exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

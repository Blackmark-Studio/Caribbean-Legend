// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Śmiało, czego chcesz?"," Właśnie o tym rozmawialiśmy. Musiałeś zapomnieć...","To już trzeci raz dzisiaj, kiedy mówisz o jakimś pytaniu...","Słuchaj, to jest sklep. Ludzie tu kupują rzeczy. Nie przeszkadzaj mi!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Wiesz, "+NPChar.name+"może następnym razem.","Racja, zapomniałem z jakiegoś powodu...","Tak, to naprawdę już trzeci raz...","Hm, nie będę...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			//Jason --> ----------------------------------мини-квест Бесчестный конкурент------------------------------------
			if (CheckAttribute(pchar, "questTemp.Shadowtrader"))
			{
				if(pchar.questTemp.Shadowtrader == "begin" && GetNpcQuestPastDayParam(npchar, "Shadowtrader_date") < 5 && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "Dziękuję, kapitanie, za spełnienie mojej prośby. Teraz, kiedy "+pchar.questTemp.Shadowtrader.Guardername+" jest tutaj, mogę przynajmniej poczuć się trochę bardziej zrelaksowany.";
					link.l1 = "Hmm... Nie chciałbym być natrętny, ale wydaje mi się, że masz kłopoty. Czy możesz mi powiedzieć, o co chodzi - być może mógłbym ci pomóc?"; 
					link.l1.go = "Shadowtrader_fort";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.Trouble") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "Więc? Czy przekazałeś mój list?";
					link.l1 = "Przekazałem. Komendant odpowiedział ustnie, że dowody w Twoim liście są niewystarczające, aby straż miejska podjęła jakiekolwiek działania."; 
					link.l1.go = "Shadowtrader_trouble";
					pchar.quest.ShadowtraderTimeFort_Over.over = "yes";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Fort") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store" && CheckAttribute(pchar, "questTemp.Shadowtrader.EndFort"))
				{
					dialog.text = "Słyszałem już wieści - dziś w nocy strażnicy odkryli nielegalny posterunek przemytników i aresztowali ich wszystkich. Był pod dowództwem jednego łajdaka, ale już wszystko w porządku, przez jakiś czas nie będzie mógł nikomu szkodzić\nKomendant opowiedział mi o twojej roli w tym wszystkim, masz moje podziękowanie! Dotrzymałeś słowa! Proszę, weź pieniądze - 15 000 pesos. Uratowałeś mnie. Nic teraz nie zagraża mojemu interesowi!";
					link.l1 = "Nie ma za co. To było łatwe."; 
					link.l1.go = "Shadowtrader_complete";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Escape") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "Jakieś dobre wieści, "+pchar.name+"?";
					link.l1 = "Odnalazłemę twego rywala. Nie będzie ci już solą w oku - udało mi się go przekonać... by opuścił tę wyspę. Jego 'sklep' znajdował się w domu niedaleko bram miasta. To twoja decyzja, co zrobić z porzuconym ładunkiem. Możesz go oddać władzom lub spróbować zabrać go dla siebie."; 
					link.l1.go = "Shadowtrader_Escape_complete";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Free") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "Słyszałem już nowiny - tej nocy straż odkryła kryjówkę przemytników pod jednym z domów. Dwóch łajdaków znaleziono martwych. Świetna robota, "+pchar.name+", podziwiam cię! Proszę, weź nagrodę - 15 000 peso. Właśnie mnie uratowałeś! Teraz będę handlować na poważnie!\nZaspokój moją ciekawość - ich przywódca... również wśród tych dwóch martwych?";
					link.l1 = "Nie. Ale już nigdy nie pokaże się w twoim mieście. Wierzę, że powinien być kilkadziesiąt mil stąd, gdy rozmawiamy."; 
					link.l1.go = "Shadowtrader_complete";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Kill") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "Słyszałem już wieści - tej nocy strażnicy zlokalizowali tajny sklep przemytników w jednym z domów. Znaleziono trzech martwych łotrów. Doskonała robota, "+pchar.name+", Podziwiam cię! Oto nagroda - 15 000 peso. Właśnie mnie uratowałeś! Teraz będę handlować na poważnie!\nZaspokój moją ciekawość - ich przywódca... również wśród dwóch zmarłych?";
					link.l1 = "Tak. Pozbyłeś się swojego rywala na zawsze. Już nigdy cię nie zaniepokoi."; 
					link.l1.go = "Shadowtrader_complete";
					break;
				}
			}
			//<-- мини-квест Бесчестный конкурент
		break;
		
		// --> мини-квест Бесчестный конкурент
		case "Shadowtrader_begin":
			pchar.questTemp.Shadowtrader = "true";
			pchar.questTemp.Shadowtrader_Block = true;
			pchar.questTemp.Shadowtrader.Guardername = GenerateRandomName_Generator(sti(npchar.nation), "man");
			dialog.text = "Czy mógłbyś pójść do tawerny i znaleźć człowieka o imieniu "+pchar.questTemp.Shadowtrader.Guardername+" i powiedz mu, żeby przyszedł tutaj jak najszybciej? Nie mogę opuścić sklepu, a ten gamoń siedzi w tawernie, opijając się rumem, i z pewnością nawet nie pomyśli, żeby tu przyjść, mimo że jest na służbie.";
			link.l1 = "Zawsze chętnie pomogę, kumplu - tym bardziej, że i tak zamierzałem odwiedzić tawernę.";
			link.l1.go = "Shadowtrader_begin_1";
			link.l2 = "Czy sobie ze mnie kpisz? Czy wyglądam na twojego chłopca na posyłki? Tawerna jest zaledwie kilka kroków stąd - możesz tam pójść sam.";
			link.l2.go = "exit";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("BasTer");
		break;
		
		case "Shadowtrader_begin_1":
			dialog.text = "Dziękuję! Proszę, powiedz mu, żeby przyszedł tutaj natychmiast. O mój Boże, dlaczego musi być takim utrapieniem...";
			link.l1 = "Nie martw się. Skieruję go do ciebie.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.City = npchar.City;
			pchar.questTemp.Shadowtrader.nation = sti(npchar.nation);
			//создаем охранника
			sld = GetCharacter(NPC_GenerateCharacter("ShadowGuarder" , "officer_7", "man", "man", 10, sti(npchar.nation), 5, true, "quest"));
			FantomMakeCoolFighter(sld, 20, 50, 50, "topor_2", "pistol3", "bullet", 50);
			sld.name = pchar.questTemp.Shadowtrader.Guardername;
			sld.lastname = "";
			sld.dialog.FileName = "Quest\LineMiniQuests\ShadowTrader.c";
			sld.dialog.currentnode = "ShadowGuarder";
			sld.greeting = "pirat_common";
			LAi_SetSitType(sld);
			LAi_SetImmortal(sld, true);
			FreeSitLocator(pchar.questTemp.Shadowtrader.City + "_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, pchar.questTemp.Shadowtrader.City + "_tavern", "sit", "sit_front1");
			SaveCurrentNpcQuestDateParam(npchar, "Shadowtrader_date");
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Shadowtrader_fort":
			dialog.text = "O, kapitanie, bardzo bym chciał twojej pomocy. Czy mógłbyś dostarczyć ten list do komendanta jak najszybciej? Zapłaciłbym ci 300 monet za tę błahą przysługę - jak już mówiłem, nie mogę opuścić mojego sklepu.";
			link.l1 = "Nie ma problemu. Daj mi ten list.";
			link.l1.go = "Shadowtrader_fort_1";
			link.l2 = "Nie, mój dobry człowieku, nie mam czasu na takie bzdury.";
			link.l2.go = "Shadowtrader_fort_end";
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_fort_1":
			dialog.text = "Oto i on. Proszę przekaż mu to dzisiaj i dostarcz mi jego odpowiedź.";
			link.l1 = "Nie martw się, zrobię to.";
			link.l1.go = "exit";
			GiveItem2Character(pchar, "letter_1");
			ChangeItemDescribe("letter_1", "itmdescr_letter_1"); // 240912
			pchar.questTemp.Shadowtrader.Tradername = GetFullName(npchar);
			SetFunctionTimerCondition("ShadowtraderTimeFort_Over", 0, 0, 1, false);
			pchar.questTemp.Shadowtrader = "current"
			pchar.questTemp.Shadowtrader.Fort = "true";
			AddQuestRecord("Shadowtrader", "1");
			AddQuestUserData("Shadowtrader", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Shadowtrader.City+"Gen"));
			AddLandQuestMarkToPhantom("baster_prison", "basterJailOff");
		break;
		
		case "Shadowtrader_fort_end":
			dialog.text = "Cóż, widocznie będę musiał zapytać kogoś innego. Przepraszam, że Cię niepokoiłem, kapitanie.";
			link.l1 = "Nie ma sprawy. Do widzenia!";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader = "true";
			DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
		break;
		
		case "Shadowtrader_trouble":
			dialog.text = "To on tak powiedział? Jakich dowodów potrzebuje ode mnie, na miłość boską?! Mojego trupa? Cóż, wkrótce będzie jeden, jeśli tak dalej pójdzie!..";
			link.l1 = "Hej, hej, "+npchar.name+", uspokój się, bo dostaniesz udaru. Proszę, napij się wody... Teraz powiedz mi, co się stało - może będę w stanie ci pomóc?";
			link.l1.go = "Shadowtrader_trouble_1";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.Trouble");
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_trouble_1":
			dialog.text = "O, kapitanie! Proszę, weź swoje 300 pesos - prawie zapomniałem... Oczywiście, powiem ci, ale nie jestem pewien, jak mógłbyś mi pomóc. Mój interes jest prawie zrujnowany - wszystko przez tych przeklętych przemytników i tego nieznanego łotra, który nimi dowodzi.";
			link.l1 = "Przemytnicy?";
			link.l1.go = "Shadowtrader_trouble_2";
			AddMoneyToCharacter(pchar, 300);
		break;
		
		case "Shadowtrader_trouble_2":
			dialog.text = "To koniec! Te łajdaki najwyraźniej postanowiły wyrzucić mnie z miasta! Do tej pory wszystko było jak zwykle - odsprzedawali zakazane towary, a kiedy patrole ich łapały, ukrywali się lub przekupywali ich. Ale ostatnio otworzyli gdzieś w zaułku sklep i zaczęli sprzedawać najpopularniejsze towary po niesamowicie niskich cenach!\nNie mogę sobie pozwolić na takie luksusy - w rzeczywistości muszę płacić podatki - stopniowo zubożałem i marynarze prawie nie chcą moich towarów - wszystkie towary kupują od tych łotrów.";
			link.l1 = "Ale powinieneś był odwołać się do władz! W końcu to ich praca - powstrzymywanie takiego bezprawia.";
			link.l1.go = "Shadowtrader_trouble_3";
		break;
		
		case "Shadowtrader_trouble_3":
			dialog.text = "Widziałeś sam wynik ostatniej apelacji. Gubernator jest zbyt zajęty, a komendant nie uwierzył, że przemytnicy zorganizowali tajne sklepy, albo udaje, że nie wierzy - i, jak sądzę, o to właśnie chodzi\nOczywiście, po co mieliby to robić? A ja mówię: Jestem pewien, że jakiś łotr, który chce mnie zniszczyć i wygnać z miasta, wymyślił to wszystko, a potem cicho uporządkuje mój interes, by oczyścić swoje brudne rączki.";
			link.l1 = "Hm... twoja opinia nie jest bezpodstawna. To w naturze kupców - robić z kogoś marionetkę... Och, przepraszam, nie miałem na myśli ciebie, oczywiście. ";
			link.l1.go = "Shadowtrader_trouble_4";
		break;
		
		case "Shadowtrader_trouble_4":
			dialog.text = "Och, nic... A niedawno przyszedł do mnie jakiś łobuz i bezczelnie powiedział, że jeśli będę nadal hałasować, spalą mój sklep\nWięc wynająłem ochroniarza."+pchar.questTemp.Shadowtrader.Guardername+" nie jest tani, ale to profesjonalista i pod jego ochroną mogę czuć się trochę spokojniej.";
			link.l1 = "Widzę... Nieprzyjemna historia, rzeczywiście. Najwyraźniej miałeś rację - nic nie mogę dla ciebie zrobić. Ale mimo to, jestem pewien, że sprawy się ułożą - takie podejrzane przybytki zazwyczaj nie trwają długo. No cóż, powodzenia!";
			link.l1.go = "Shadowtrader_end";
			link.l2 = "Rozumiem. Cóż, może wciąż będę mógł ci pomóc...";
			link.l2.go = "Shadowtrader_trouble_5";
		break;
		
		case "Shadowtrader_trouble_5":
			dialog.text = "Ty mi oferujesz swoją pomoc mimo wszystko? Ale co zamierzasz zrobić?";
			link.l1 = "Spróbuję znaleźć tego twojego 'kolegę' i... przekonać go, by przestał cię niepokoić. Wiesz, mam pewne umiejętności w przekonywaniu ludzi.";
			link.l1.go = "Shadowtrader_trouble_6";
		break;
		
		case "Shadowtrader_trouble_6":
			dialog.text = "Jesteś poważny? Niech Pan pobłogosławi twoją sprawiedliwą sprawę! Jeśli uwolnisz mnie od tej zarazy, będę twoim dłużnikiem.";
			link.l1 = "Dobrze, uznajmy to za umowę. Zaczynam szukać, więc.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.seeksmugglers = "true";
			AddLandQuestMark(characterFromId("BasTer_Smuggler"), "questmarkmain");
			AddQuestRecord("Shadowtrader", "2");
			AddQuestUserData("Shadowtrader", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Shadowtrader.City+"Gen"));
			AddQuestUserData("Shadowtrader", "sSex1", GetSexPhrase("ся","ась"));
		break;
		
		case "Shadowtrader_end":
			pchar.questTemp.Shadowtrader = "true";
			CloseQuestHeader("Shadowtrader");
			DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
			DialogExit();
		break;
		
		case "Shadowtrader_Escape_complete":
			dialog.text = "Czy to prawda? Mogę teraz prowadzić interesy bez żadnych obaw? Och, dziękuję bardzo! Oto twoja nagroda - 15000 pesos. Jeśli chodzi o towary w ich domu, myślę, że najlepiej oddać je komendantowi. Jeszcze raz dziękuję!";
			link.l1 = "Proszę bardzo. To nie było zbyt trudne. Mówiłem, że jestem dobry w przekonywaniu.";
			link.l1.go = "Shadowtrader_complete";
		break;
		
		case "Shadowtrader_complete":
			dialog.text = "Odwiedzaj mnie ponownie, kapitanie - zawsze będę się cieszył na twój widok.";
			link.l1 = "Oczywiście! A teraz pozwól, że się oddalę - mam sprawy do załatwienia! Żegnaj i powodzenia w handlu, "+npchar.name+"!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.End");
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.Shadowtrader = "complete";
			AddQuestRecord("Shadowtrader", "11");
			AddQuestUserData("Shadowtrader", "sSex", GetSexPhrase("","а"));
			CloseQuestHeader("Shadowtrader");
			DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
			DeleteAttribute(pchar, "questTemp.Shadowtrader.EndFort");
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("BasTer");
		break;
		//<-- мини-квест Бесчестный конкурент
	}
	UnloadSegment(NPChar.FileDialog2);
}

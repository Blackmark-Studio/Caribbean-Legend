#include "DIALOGS\%language%\Rumours\Common_rumours.c" //Jason
void ProcessDialogEvent()
{
 	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\ItemTrader\" + NPChar.City + "_ItemTrader.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
// ============================================================================
// ============================= блок angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
			
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
// ============================================================================	   
	switch(Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
  		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;

  		case "First time":
			dialog.text = NPCharSexPhrase(npchar,"Czy chciałbyś kupić sprzęt dla siebie czy dla swoich oficerów, kapitanie? Jeśli tak, to przyszedłeś do właściwej osoby!","Oh, kapitanie, wiedziałem, że podejdziesz do mnie! Mogę zaoferować ci sprzęt dla ciebie i twoich oficerów, wśród wielu innych użytecznych rzeczy.");
			link.l1 = "Pokaż mi, co masz.";
			link.l1.go = "Trade_exit";
			
   			/*link.l2 = "Przybyłem w innej sprawie.";
			link.l2.go = "quests";*/
			// --> Мангароса
			if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "find" && npchar.Merchant.type == "potion" && !CheckAttribute(npchar, "quest.mangarosa"))
			{
				link.l4 = "Hej, znalazłem jedną interesującą roślinę w okolicy. Czy mógłbyś mi powiedzieć, czy można jej użyć do warzenia mikstur czy wywarów? Wydaje mi się po prostu interesująca. Czy mógłbyś rzucić okiem?";
				link.l4.go = "mangarosa";
			}
			// <-- Мангароса
			

			//Jason --> мини-квест Дефицитный товар
			if (CheckAttribute(pchar, "questTemp.Wine.bottle") && NPChar.location == pchar.questTemp.Wine.City + "_town" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
   				link.l4 = "Powiedz, możesz mi sprzedać butelkę dobrego europejskiego wina?";
				link.l4.go = "Wine_ItemTrader";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.bottles") && NPChar.location == pchar.questTemp.Wine.City + "_town" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
   				link.l4 = "Słuchaj, wiem, że sprzedajesz europejskie wino. Potrzebuję sześćdziesiąt butelek.";
				link.l4.go = "Wine_Bottles";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.Repeat1") && NPChar.location == pchar.questTemp.Wine.City + "_town" && npchar.id == pchar.questTemp.Wine.ItemTraderID && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
   				link.l4 = "To znowu ja. Co to wszystko znaczy, co?";
				link.l4.go = "Wine_Repeat1";
			}
			// <-- мини-квест Дефицитный товар
			
			//Sinistra --> мини-квест "Знакомство с индейцами"
			if (CheckAttribute(pchar, "questTemp.ZsI_PokupaemPistolety") && npchar.Merchant.type == "armourer")
			{
   				link.l4 = "Potrzebuję dwóch pistoletów, razem z kulami i prochem na dwadzieścia strzałów.";
				link.l4.go = "ZsI_PokupaemPistolety";
			}
			// <-- мини-квест "Знакомство с индейцами"
			
			// --> Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l4 = "Słuchaj, czy imię 'Juan' coś ci mówi?";
				link.l4.go = "Consumption";
			}
			// <-- Цена чахотки
			
			//--> Украденное воспоминание
			if(CheckAttribute(pchar, "questTemp.UV_Lavochniki") && !CheckAttribute(npchar, "quest.UV_Vopros") && npchar.city == "PortPax")
			{
				link.l4 = "Powiedz mi, nie masz przypadkiem czegoś naprawdę wartościowego? Nie jakichś tandetnych błyskotek, ale czegoś naprawdę eleganckiego – na przykład pięknych kolczyków albo szykownego wisiorka. Potrzebuję prezentu dla damy szlachetnego pochodzenia.";
				link.l4.go = "UV_Lavochniki_1";
			}
            if(CheckAttribute(pchar, "questTemp.UV_Lavochniki_2") && !CheckAttribute(npchar, "quest.UV_Vopros") && npchar.city == "PortPax")
            {
				link.l4 = "Czy nie masz może czegoś naprawdę cennego? Potrzebuję ozdoby godnej nawet najbardziej wybrednej arystokratki – coś rzadkiego, eleganckiego, nie dla zwykłych ludzi. Może delikatny medalion albo wyszukana bransoletka?";
				link.l4.go = "UV_Lavochniki_2";
			}
			if(CheckAttribute(pchar, "questTemp.UV_Lavochniki_3") && !CheckAttribute(npchar, "quest.UV_Vopros") && npchar.city == "PortPax")
            {
				link.l4 = "Powiedz, znasz się może na biżuterii? Potrzebuję czegoś wyjątkowego na prezent dla pewnej szlachetnej damy. Uprzedzam – tandetne błyskotki mnie nie interesują. Potrzebuję czegoś wyrafinowanego: bogato zdobionej broszy albo okazałego pierścienia.";
				link.l4.go = "UV_Lavochniki_3";
			}
			//<-- Украденное воспоминание
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l5 = "Słuchaj, handlujesz przeróżnymi towarami... Wczoraj czy dzisiaj - czy ktoś proponował ci sprzedaż "+pchar.GenQuest.Device.Shipyarder.Type+"?";
				link.l5.go = "Device_ItemTrader";
			}
			//<-- генератор Неудачливый вор

			link.l9 = "Dziękuję, nie jestem zainteresowany.";
			link.l9.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Trade_exit":
            if (CheckNPCQuestDate(npchar, "Item_date"))
			{
				SetNPCQuestDate(npchar, "Item_date");
				GiveItemToTrader(npchar);
			}
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchItemsTrade(npchar, 0);
		break;
		
		//Jason --> мини-квест Дефицитный товар
		case "Wine_ItemTrader":
			dialog.text = "Pewnie. Siedemset pesos za butelkę.";
			if (makeint(Pchar.money) >= 700)
			{
				link.l1 = "Świetnie. Weź pieniądze i daj mi je.";
				link.l1.go = "Wine_ItemTrader_1";
			}
			link.l2 = "Doskonale! Wrócę, gdy zdecyduję się coś kupić.";
			link.l2.go = "exit";
		break;
		
		case "Wine_ItemTrader_1":
			dialog.text = "Proszę, weź swoją butelkę.";
			link.l1 = "Dziękuję Ci!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -700);
			TakeNItems(pchar, "potionwine", 1);
			PlaySound("interface\important_item.wav");
			DeleteAttribute(pchar, "questTemp.Wine.bottle");
			AddQuestRecord("Wine", "1_1");
			WineTraderQMDel();
		break;
		
		case "Wine_Bottles":
			dialog.text = "Ha! Jestem tylko sprzedawcą detalicznym, nie hurtownikiem. Sprzedawałbym tak dużo butelek przez ponad pół roku - to wino jest rzadkie i drogie, i nie każdy na to stać, wiesz. Nie mam aż tak wielu.";
			link.l1 = "Dobrze, nie masz ich - nie ma problemu. Ale skądś je zdobywasz dla siebie, prawda? Może mógłbyś mi powiedzieć nazwę swojego dostawcy, a ja bym od niego kupił bezpośrednio. Czy może wino dostarczane jest do ciebie z Europy?";
			link.l1.go = "Wine_Bottles_1";
		break;
		
		case "Wine_Bottles_1":
			dialog.text = "Nie, nie jest. Dostaję go tutaj. Ale nie podam ci nazwy mojego dostawcy tak po prostu. Ale za tysiąc peso... być może, zrobiłbym...";
			if (makeint(Pchar.money) >= 1000)
            {
				link.l1 = "Dobrze. Oto twoje tysiąc - a teraz powiedz mi, kim jest twój dostawca.";
				link.l1.go = "Wine_Bottles_2";
			}
			link.l2 = "Teraz wy, szachrajscy kupcy, staliście się zbyt bezczelni! Czy nie byłoby dla was za dobrze? Dam sobie radę bez waszego dostawcy, dziękuję.";
			link.l2.go = "Wine_Bottles_fail";
		break;
		
		case "Wine_Bottles_free":
			dialog.text = "Chyba... w porządku. Oto twój list, mam nadzieję, że odwdzięczysz się w przyszłości.";
			link.l1 = "...";
			link.l1.go = "Wine_Bottles_free_1";
		break;
		
		case "Wine_Bottles_free_1":
			pchar.questTemp.Wine.TraderID = pchar.questTemp.Wine.City +"_trader";
			sld = characterFromId(pchar.questTemp.Wine.TraderID);
			pchar.questTemp.Wine.Name = GetFullName(sld);
			pchar.questTemp.Wine.ItemTraderID = npchar.id;
			dialog.text = "Nazwa mojego dostawcy wina to "+pchar.questTemp.Wine.Name+", on jest właścicielem lokalnego sklepu.";
			link.l1 = "Rozumiem! Dzięki!";
			link.l1.go = "exit";
			//pchar.questTemp.Wine.Trader = "true";
			DeleteAttribute(pchar, "questTemp.Wine.bottles");
			pchar.questTemp.Wine.Repeat2 = "true";
			TakeNItems(pchar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_1");
			PlaySound("interface\important_item.wav");
		break;
		
		case "Wine_Bottles_2":
    		AddMoneyToCharacter(pchar, -1000);
			pchar.questTemp.Wine.TraderID = pchar.questTemp.Wine.City +"_trader";
			sld = characterFromId(pchar.questTemp.Wine.TraderID);
			AddLandQuestMark(sld, "questmarkmain");
			pchar.questTemp.Wine.Name = GetFullName(sld);
			pchar.questTemp.Wine.ItemTraderID = npchar.id;
			dialog.text = "Nazwa mojego dostawcy wina to "+pchar.questTemp.Wine.Name+", on jest właścicielem lokalnego sklepu.";
			link.l1 = "Rozumiem! Dzięki!";
			link.l1.go = "exit";
			pchar.questTemp.Wine.Trader = "true";
			DeleteAttribute(pchar, "questTemp.Wine.bottles");
			AddQuestRecord("Wine", "3");
			AddQuestUserData("Wine", "sName", pchar.questTemp.Wine.Name);
			WineTraderQMDel();
		break;
		
		case "Wine_Bottles_fail":
			dialog.text = "Jak sobie życzysz, kapitanie. Wszystkiego najlepszego dla ciebie.";
			link.l1 = "Do widzenia.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Wine.bottles");
			AddQuestRecord("Wine", "4");
			WineTraderQMDel();
		break;
		
		case "Wine_Repeat1":
			DeleteAttribute(pchar, "questTemp.Wine.Repeat1");
			dialog.text = "Co masz na myśli mówiąc to? Wyjaśnij się.";
			link.l1 = "Oszukałeś mnie, łotrzyku! Właśnie byłem w sklepie, "+pchar.questTemp.Wine.Name+" nigdy nie handluje winem, sam mi to powiedział! Oddaj mi moje pieniądze!";
			link.l1.go = "Wine_Repeat1_fail";
			link.l2 = "Było nieporozumienie... Przyszedłem do sklepikarza, a "+pchar.questTemp.Wine.Name+" twierdził, że nigdy nie handlował winem. Jak możesz to wyjaśnić?";
			link.l2.go = "Wine_Repeat1_1";
		break;
		
		case "Wine_Repeat1_1":
			dialog.text = "Heh! Z pewnością handluje winem. Po prostu nie sprzedaje wina każdemu - podobnie jak z kilkoma innymi towarami. I jest kilka powodów dla tego... Jeśli chcesz od niego kupić wino, mogę mu napisać notatkę. Zna mnie i mój charakter pisma, więc po przeczytaniu sprzeda ci to wino. Oczywiście, ta przysługa też nie jest darmowa.";
			link.l1 = "To skandal! Właśnie zabrałeś ode mnie tysiąc!";
			link.l1.go = "Wine_Repeat1_2";
		break;
		
		case "Wine_Repeat1_2":
			dialog.text = "Wziąłem od ciebie tysiąc za informacje. A za list musisz zapłacić osobno dwa tysiące pesos, i w żaden sposób mniej niż to.";
			if (makeint(Pchar.money) >= 2000)
			{
				link.l1 = "Oh... Wy handlarze jesteście tak cholernie chciwi. Nic dziwnego, że nikt was nie lubi. No cóż, oto twoje pieniądze, więc pisz ten list.";
				link.l1.go = "Wine_Bottles_3";
			}
			if(CheckCharacterPerk(pchar, "Trustworthy"))
			{
				notification("Trustworthy", "Trustworthy");
				link.l2 = "(Zaufany) Dojdźmy do kompromisu. Dostarczysz mi teraz rekomendację, bezpłatnie, a ja odwdzięczę się rekomendacją dla ciebie później, również bez kosztów. Ta transakcja z winem to dopiero początek.";
				link.l2.go = "Wine_Bottles_free";
			}
			link.l3 = "To już zupełnie przekracza granice! Wolę porzucić całą sprawę, nie wzbogacę takiego przebiegłego skąpca. A tym skąpcem mam na myśli ciebie. Do widzenia.";
			link.l3.go = "Wine_Repeat1_goaway";
		break;
		case "Wine_Bottles_free":
			dialog.text = "Chyba... dobrze w takim razie. Oto twój list, mam nadzieję, że odwdzięczysz się w przyszłości.";
			link.l1 = "...";
			link.l1.go = "Wine_Bottles_free_1";
		break;
		
		case "Wine_Bottles_free_1":
			pchar.questTemp.Wine.Repeat2 = "true";
			TakeNItems(pchar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_1");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Wine", "6_1");
			DelLandQuestMark(npchar);
			sld = characterFromId(pchar.questTemp.Wine.TraderID);
			AddLandQuestMark(sld, "questmarkmain");
			DialogExit();
		break;
		
		case "Wine_Bottles_3":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "Jesteś dziwnym ptakiem, kapitanie! Oczywiście, zdaję sobie sprawę, że twój skarbnik zajmuje się wszystkimi finansami, ale czasami powinieneś też korzystać ze swojego własnego rozumu. Będziesz miał okazję kupić porządną partię win hurtowo bez mojej marży i zarobić sporo. Więc nie przeszkadzajmy sobie w zarabianiu pieniędzy, bo to ty teraz wyglądasz na chciwego.\nDobrze... (piszę) Tutaj, weź ten list - "+pchar.questTemp.Wine.Name+"  sprzeda ci wino bez żadnych pytań.";
			link.l1 = "Mam taką nadzieję... Jeśli coś pójdzie znowu nie tak, wrócę. Do zobaczenia!";
			link.l1.go = "Wine_Bottles_4";
		break;
		
		case "Wine_Bottles_4":
			pchar.questTemp.Wine.Repeat2 = "true";
			TakeNItems(pchar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_1");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Wine", "6");
			DelLandQuestMark(npchar);
			sld = characterFromId(pchar.questTemp.Wine.TraderID);
			AddLandQuestMark(sld, "questmarkmain");
			DialogExit();
		break;
		
		case "Wine_Repeat1_goaway":
			dialog.text = "Jak sobie życzysz, kapitanie. Do widzenia.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddQuestRecord("Wine", "4");
			DelLandQuestMark(npchar);
		break;
		
		case "Wine_Repeat1_fail":
			dialog.text = "Oh, więc przyszedłeś tu, aby mi grozić i być niegrzeczny? Wołam strażników! Hej, strażnicy! Tu jest!";
			link.l1 = "Och, zamknij się! Wygrałeś, odchodzę! Przeklęty ty "+NPCharSexPhrase(npchar,"","")+", kormoranie, niech cię zrujnuje!";
			link.l1.go = "exit";
			AddQuestRecord("Wine", "7");
			DelLandQuestMark(npchar);
		break;
		// <-- мини-квест Дефицитный товар
		
		//Sinistra --> мини-квест "Знакомство с индейцами"
		case "ZsI_PokupaemPistolety":
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				dialog.text = "Ach, rozumiem. Robisz interesy z tubylcami? Słyszałem, że ten już cię kosztował ładną sumkę, ha ha!";
			}
			else
			{
				dialog.text = "Spodziewasz się kłopotów, Kapitanie? Czy planujesz przygodę w dżungli? Ha-ha!";
			}
			link.l1 = "Czy możemy zrobić interes?";
			link.l1.go = "ZsI_PokupaemPistolety_1";
			DelLandQuestMark(npchar);
		break;
		
		case "ZsI_PokupaemPistolety_1":
			dialog.text = "Oczywiście! Klienci są zawsze mile widziani. Za trzy tysiące pesos otrzymasz niezawodne pistolety, kule i proch, jak to było zamówione.";
			if (sti(pchar.Money) > 2999)
			{
				link.l1 = "Drogo, ale w porządku. Wezmę to.";
				link.l1.go = "ZsI_PokupaemPistolety_2";
			}
			if (sti(pchar.Money) > 2299)
			{
				link.l2 = "Cena wydaje się niesprawiedliwa. Co powiesz na zniżkę dla przyjaciela Fadeya Moskiewskiego?";
				link.l2.go = "ZsI_Torg";
			}
			link.l3 = "Trzy tysiące? To rabunek! Do widzenia, Panie!";
			link.l3.go = "ZsI_NetDeneg";
		break;
		
		case "ZsI_NetDeneg":
			DialogExit();
			
			LocatorReloadEnterDisable("BasTer_town", "gate_back", false);
			PChar.quest.ZsI_Timer.over = "yes";
			sld = CharacterFromID("ListKakao");
			sld.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.ZsI_PokupaemPistolety");
		break;
		
		case "ZsI_PokupaemPistolety_2":
			dialog.text = "Powodzenia tam na zewnątrz, Kapitanie!";
			link.l1 = "Do widzenia, Monsieur.";
			link.l1.go = "ZsI_PokupaemPistolety_3";
			AddMoneyToCharacter(pchar, -3000);
			Log_info("You have acquired the required pistols for Cocoa Leaf");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "ZsI_PokupaemPistolety_3":
			DialogExit();
			
			LocatorReloadEnterDisable("BasTer_town", "gate_back", false);
			DeleteAttribute(pchar, "questTemp.ZsI_PokupaemPistolety");
			PChar.quest.ZsI_Patrul.win_condition.l1 = "location";
			PChar.quest.ZsI_Patrul.win_condition.l1.location = "BasTer_ExitTown";
			PChar.quest.ZsI_Patrul.win_condition = "ZsI_Patrul";
		break;
		
		case "ZsI_Torg":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) > 18)
			{
				notification("Skill Check Passed", SKILL_COMMERCE);
				dialog.text = "Rzeczywiście, Kapitanie. Przyjaciele Fadeya zawsze są tutaj mile widziani. Dwa tysiące trzysta za całość?";
				link.l1 = "To brzmi lepiej. Wezmę to.";
				link.l1.go = "ZsI_Torg_2";
				AddCharacterExpToSkill(pchar, "Commerce", 30);
			}
			else
			{
				notification("Skill Check Failed (19)", SKILL_COMMERCE); 
				dialog.text = "Przyjaciele Pana Fadey'a zawsze są mile widziani, ale ceny nie mają przyjaciół. To będzie trzy tysiące peso, Kapitanie.";
				if (sti(pchar.Money) > 2999)
				{
					link.l1 = "Drogo, ale w porządku. Wezmę to.";
					link.l1.go = "ZsI_PokupaemPistolety_2";
				}
				link.l2 = "Trzy tysiące? To rabunek! Do widzenia, Panie!";
				link.l2.go = "ZsI_NetDeneg";
				//Log_info("Trading skill is not sufficient");
				AddCharacterExpToSkill(pchar, "Commerce", -30);
			}
		break;
		
		case "ZsI_Torg_2":
			dialog.text = "Miłego dnia na morzu, Kapitanie!";
			link.l1 = "Żegnaj, Monsieur.";
			link.l1.go = "ZsI_PokupaemPistolety_3";
			AddMoneyToCharacter(pchar, -2300);
			Log_info("You have acquired the required pistols for Cocoa Leaf");
			PlaySound("Interface\important_item.wav");
		break;
		// <-- мини-квест "Знакомство с индейцами"
		
		// --> Цена чахотки
		case "Consumption":
			dialog.text = "Nie, nie... Teraz proszę mnie nie przeszkadzać, jestem bardzo zajęty... Co za idiotyczne pytanie...";
			link.l1 = "Rozumiem. Przepraszam za marnowanie twojego czasu...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
		// <-- Цена чахотки
		//Jason --> генератор Неудачливый вор
		case "Device_ItemTrader":
			dialog.text = "Hmm, "+pchar.GenQuest.Device.Shipyarder.Type+"? Nigdy o tym nie słyszałem... Co to właściwie jest? Nigdy o czymś takim nie słyszałem w całym moim życiu"+NPCharSexPhrase(npchar,"","")+".";
			link.l1 = "No cóż, to narzędzie stoczniowe, "+pchar.GenQuest.Device.Shipyarder.Describe+". Czy ktoś ci coś takiego proponował?";
			link.l1.go = "Device_ItemTrader_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_ItemTrader_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 0 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 4 && npchar.location.group == "merchant" && npchar.location.locator == "merchant"+sti(pchar.GenQuest.Device.Shipyarder.Chance1))
			{
				dialog.text = "Hmm... Tak, był jeden dziwny facet. Ale nie powiedział mi, co to jest, tylko próbował mi to sprzedać. Ale po co mi to, jeśli nie miałem pojęcia, do czego to służy? Jak bym to odsprzedał? Więc, po prostu odmówiłem"+NPCharSexPhrase(npchar,"","")+", i odszedł";
				link.l1 = "A jak on wyglądał i dokąd poszedł? Bardzo potrzebuję tego instrumentu.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "Nie, nic takiego. Przykro mi, nie mogę ci pomóc. Pytaj wokół.";
				link.l1 = "Rozumiem. Cóż, czas rozejrzeć się!";
				link.l1.go = "exit";
			}
		break;
		// <-- генератор Неудачливый вор
		
		// Мангароса
		case "mangarosa":
			// тут работает везение
			if (sti(pchar.questTemp.Mangarosa.m_count) == 5 || GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 10+hrand(30)+hrand(40, "1"))
			{
				dialog.text = "Pokaż mi to... Tak, to interesująca roślina. I bardzo, bardzo rzadka. Nazywa się Manga Rosa. Nie wiem, do czego jest używana, ale jest z nią związany ciekawy fakt...";
				link.l1 = "Co masz na myśli?";
				link.l1.go = "mangarosa_1";
			}
			else
			{
				dialog.text = LinkRandPhrase("Pokaż mi to... Tak, to interesująca roślina. Ale, niestety, nie mogę powiedzieć ci więcej na ten temat. Jeśli rzeczywiście jest używana do jakiegoś celu, jest mi to nieznane.","Zobaczmy... Hmm... Wygląda na leczniczą roślinę, ale nic o niej nie wiem. Przykro mi, nie mogę ci pomóc.","Gdzie to jest? Hmm... Nie, nigdy tego wcześniej nie widziałem. Na pewno wygląda bardzo interesująco, ale nie mam pojęcia, do czego to służy...");
				link.l1 = "Rozumiem. Cóż, zapytam się jeszcze trochę. Przepraszam.";
				link.l1.go = "mangarosa_exit";
			}
		break;
		
		case "mangarosa_exit":
			DialogExit();
			pchar.questTemp.Mangarosa.m_count = sti(pchar.questTemp.Mangarosa.m_count)+1;
			npchar.quest.mangarosa = "true";
		break;
		
		case "mangarosa_1":
			dialog.text = "Nomadyczni cyganie i dzicy wykazują wielkie zainteresowanie tymi roślinami. Kiedyś widziałem, jak cygan płacił garść złota za tylko jeden taki pień. Ale nie mam pojęcia, po co im to potrzebne.";
			link.l1 = "Rozumiem... Cóż, to już coś przynajmniej! Teraz wiem, gdzie dalej pytać. Bardzo ci dziękuję!";
			link.l1.go = "mangarosa_2";
		break;
		
		case "mangarosa_2":
			DialogExit();
			npchar.quest.mangarosa = "true";
			DeleteAttribute(pchar, "questTemp.Mangarosa.m_count");
			pchar.questTemp.Mangarosa = "gipsy";
			AddQuestRecord("Mangarosa", "2");
		break;
		
		//--> Украденное воспоминание
		case "UV_Lavochniki_1":
    		dialog.text = "Niestety, "+GetAddress_Form(NPChar)+", nie mam już od dawna nic naprawdę cennego. Popyt na takie rzeczy, wiecie, dziś jest niewielki. Zwykli ludzie kupują tylko tanie błyskotki, a szlachta prawie nie zagląda do mojego sklepu.";
    		link.l1 = "W porządku...";
    		link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.UV_Lavochniki");
			pchar.questTemp.UV_Lavochniki_2 = true;
			npchar.quest.UV_Vopros;
 		break;
		
		case "UV_Lavochniki_2":
    		dialog.text = "Przykro mi, kapitanie, ale takimi towarami nie handluję od dawna. Zamożni klienci rzadko tu zaglądają, a zwykli ludzie kupują tylko to, co tanie.";
    		link.l1 = "W porządku...";
    		link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.UV_Lavochniki_2");
			pchar.questTemp.UV_Lavochniki_3 = true;
			npchar.quest.UV_Vopros;
 		break;
		
		case "UV_Lavochniki_3":
    		dialog.text = "Kapitanie, obawiam się, że przybyliście za późno... Zaledwie kilka godzin temu sprzedałem wspaniały naszyjnik pewnemu zamożnemu kapitanowi. Czasem trafiają mi się rzeczy, które mogą oczarować nawet najbardziej upartą damę\nWpadnijcie jutro – być może Giselle... to znaczy... moi dostawcy... znajdą dla was klejnot, który na zawsze skradnie serce każdej kobiety.";
    		link.l1 = "Nie mam czasu, potrzebuję ozdoby natychmiast. Powiedz mi, jak nazywał się ten kapitan, któremu sprzedałeś naszyjnik?";
    		link.l1.go = "UV_Lavochniki_3_1";
 		break;
		
		case "UV_Lavochniki_3_1":
    		dialog.text = "Tristan Renier, kapitan 'Golden Seagull'. Jego statek nadal stoi w porcie. Ale szczerze mówiąc, wątpię, by chciał się rozstać z tym naszyjnikiem. Jeśli odmówi, wpadnijcie jutro. Przysięgam, kapitanie, nie pożałujecie.";
    		link.l1 = "...";
    		link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.UV_Lavochniki_3");
			AddDialogExitQuestFunction("UV_GoldSeagull");
 		break;
		//<-- Украденное воспоминание
		
// ======================== блок нод angry ===============>>>>>>>>>>>>>>>

////////////////////////////////////////////////////////////////////////////////////////////////
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok")
		break;

// <<<<<<<<<<<<============= блок нод angry =============================
	}
}

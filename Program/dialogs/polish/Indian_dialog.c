// диалог индейцев в поселениях
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Nie mamy o czym rozmawiać!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		// ==> индейцы в поселении
		case "IndianMan":
			NextDiag.TempNode = "IndianMan";
			dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Blada twarz","Blada twarz")+" chce rozmawiać?","Ty znowu, "+GetSexPhrase("Blada twarz","Blada twarz")+".",""+GetSexPhrase("Blada twarz lubi mówić.","Blada twarz lubi rozmawiać.")+"","Duchy przyprowadziły moją bladą twarz do mnie.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Tak.","Tak, to znowu ja.","Bardzo poetycko.","Ja również cieszę się, że cię widzę.",npchar,Dialog.CurrentNode);
			link.l1.go = "IndPearlMan_1";
		break;
		
		case "IndPearlMan_1":
			dialog.text = "Powiedz, dlaczego przyszedłeś, blada twarzy?";
			link.l1 = "O, nic konkretnego, po prostu chciałem posłuchać, co masz do powiedzenia...";
			link.l1.go = "exit";
		break;
		
		case "IndianWoman":
			NextDiag.TempNode = "IndianWoman";
			dialog.text = NPCStringReactionRepeat("Biały człowiek chce rozmawiać?","Ty znowu, blada twarz?","Blada twarz lubi rozmawiać.","Duchy przyprowadziły mojego bladotwarzego brata do mnie.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Tak.","Tak, to znowu ja.","Bardzo poetycko.","Cieszę się, że też cię widzę.",npchar,Dialog.CurrentNode);
			link.l1.go = "IndianWoman_1";
		break;
		
		case "IndianWoman_1":
			dialog.text = LinkRandPhrase(""+npchar.name+" słucham cię, synu morza.","Czego chcesz od "+npchar.name+", blada twarz?","Moje uszy są otwarte na twoje słowa, obcy.");
			if (CheckIndianGift() && !CheckAttribute(npchar, "quest.gift"))
			{
				link.l1 = LinkRandPhrase("Mam coś dla ciebie. Chcesz zobaczyć?","Chcesz zobaczyć coś naprawdę ciekawego? Na pewno ci się spodoba...","Mam coś, co cię ucieszy, dziecko dżungli. Chcesz zobaczyć?");
				link.l1.go = "gift";
			}
			link.l9 = "Oh, nic szczególnego, po prostu chciałem posłuchać, co masz do powiedzenia...";
			link.l9.go = "exit";
		break;
		
		case "gift":
			iTemp = 2;
			dialog.text = RandPhraseSimple(""+npchar.name+" chce zobaczyć. Pokaż to.",""+npchar.name+" jest zainteresowany. Pokaż mi.");
			if (CheckCharacterItem(pchar, "mineral6"))
			{
				link.l1 = "Daj lustro.";
				link.l1.go = "gift_1";
			}
			for (i=50; i>=47; i--)
			{
				if (CheckCharacterItem(pchar, "jewelry"+i))
				{
					sTemp = "l"+iTemp;
					link.(sTemp) = "Give"+XI_ConvertString("jewelry"+i)+".";
					link.(sTemp).go = "gift_"+i;
					iTemp++;				
				}
			}
		break;
		
		case "gift_1":
			RemoveItems(pchar, "mineral6", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "O! Teraz "+npchar.name+" może patrzeć na siebie nie tylko w rzece! Dziękuję Ci, uprzejmy obcy!";
			link.l1 = "Pewnie, teraz możesz podziwiać swoją twarz, ile tylko chcesz...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_47":
			RemoveItems(pchar, "jewelry47", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Och! Tak piękny! Ta bransoletka jest dla "+npchar.name+". Dziękuję, życzliwy obcy!";
			link.l1 = "Załóż to na swoją ciemną rękę, piękności, będziesz wyglądać fantastycznie...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_48":
			RemoveItems(pchar, "jewelry48", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Oh! Jaki piękny pierścień? To dla "+npchar.name+", tak? Dziękuję, uprzejmy obcy!";
			link.l1 = "Załóż to na swój palec, a wszyscy twoi przyjaciele będą zazdrościć...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_49":
			RemoveItems(pchar, "jewelry49", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "O! Te cudowne zielone koraliki są dla "+npchar.name+"? Tak piękne! Dziękuję ci, uprzejmy obcy!";
			link.l1 = "Ozdób swoją szyję nimi, córko selvy. Wszyscy będą Cię podziwiać...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_50":
			RemoveItems(pchar, "jewelry50", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "O, jaki piękny zielony pierścień! To prezent dla "+npchar.name+". Dziękuję Ci, życzliwy nieznajomy!";
			link.l1 = "Będzie wyglądało wspaniale na twojej ręce, piękna...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_exit":
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Women")) // Addon 2016-1 Jason Пиратская линейка
			{
				dialog.text = "Chciałeś zapytać "+npchar.name+" cokolwiek, synie morza?";
				link.l1 = "Masz rację, piękna. Ja i moi nieustraszeni wojownicy idziemy do selvy, do hiszpańskiej osady wśród gór i szukamy przewodnika. Będę hojny dla samego mężczyzny, a także dla jego żony. Mam wiele bogactw: piękne pistolety, magiczne szkła, lustra, naszyjniki, bransoletki i pierścienie. Być może twój mąż może być przewodnikiem, którego szukamy?";
				link.l1.go = "hayamee";
			}
			else
			{
				DialogExit();
			}
			ChangeIndianRelation(1.00);
			npchar.quest.gift = true;
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		// Кумвана, вождь деревни араваков
		case "cumvana":
			dialog.text = "Pozdrowienia, synu morza. Jestem Kumwana, wodzem klanu Żółwia z ludu Locono. Co przyprowadziło cię do mojej wioski?";
			if (GetCharacterFreeItem(pchar, "pistol5") > 0 || CheckCharacterItem(pchar, "compass1") || GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l1 = "Przyniosłem ci prezent, wodzu. Spójrz, na pewno ci się spodoba.";
				link.l1.go = "cumvana_2";
			}
			else 
			{
				link.l1 = "Wodzu, przyszedłem prosić o twoją pomoc. Chcę dotrzeć do hiszpańskiej osady o nazwie Merida, która znajduje się wśród gór w twojej dżungli, problem w tym, że nie wiem, jak tam dotrzeć.";
				link.l1.go = "cumvana_no";
			}
			DelLandQuestMark(npchar);
		break;
		
		case "cumvana_no":
			dialog.text = "To bardzo dobrze dla ciebie, synu morza, nie znając drogi tam. Prowadzi przez las, ziemię nieustraszonego plemienia Capong. Prawdziwe jaguary, oni są, oh-ey! Ja nigdy nie idę do tego hiszpańskiego miejsca. Moi ludzie - pokojowi ludzie, nie idziemy do ziemi Capong. Kumwana nie może ci dać rady. Droga zbyt niebezpieczna.";
			link.l1 = "Ale Hiszpanie znaleźli bezpieczną droge! A poza tym nie boję się tych Capongów...";
			link.l1.go = "cumvana_no_1";
		break;
		
		case "cumvana_no_1":
			dialog.text = "Ale powinieneś. To okrutni ludzie. Zabili wielu moich ludzi w lesie. Kumwana powiedział wszystko.";
			link.l1 = "Cóż, szlag by to...";
			link.l1.go = "cumvana_no_2";
		break;
		
		case "cumvana_no_2":
			DialogExit();
			AddQuestRecord("Roger_5", "5");
			npchar.dialog.currentnode = "cumvana_1";
		break;
		
		case "cumvana_1":
			dialog.text = "Oh-ey! Ty znowu, synu morza. Co chcesz powiedzieć do Kumwana?";
			if (GetCharacterFreeItem(pchar, "pistol5") > 0 || CheckCharacterItem(pchar, "compass1") || GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l1 = "Przyniosłem ci prezent, wodzu. Spójrz, na pewno ci się spodoba.";
				link.l1.go = "cumvana_2";
			}
			else 
			{
				link.l1 = "Nadzieja na znalezienie Meridy wciąż we mnie jest...";
				link.l1.go = "cumvana_1_1";
			}
		break;
		
		case "cumvana_1_1":
			DialogExit();
			npchar.dialog.currentnode = "cumvana_1";
		break;
		
		case "cumvana_2":
			dialog.text = "Locono zawsze cieszą się na widok dobrych przyjaciół.";
			if (GetCharacterFreeItem(pchar, "pistol5") > 0)
			{
				link.l1 = "Podaruj pistolet."; // 5
				link.l1.go = "cumvana_2_1";
			}
			if (CheckCharacterItem(pchar, "compass1")) // 3
			{
				link.l2 = "Podaruj kompas.";
				link.l2.go = "cumvana_2_2";
			}
			if (GetCharacterFreeItem(pchar, "spyglass1") > 0)
			{
				link.l3 = "Podaruj tanią lunetę.";
				link.l3.go = "cumvana_2_3";
			}
			if (GetCharacterFreeItem(pchar, "spyglass2") > 0)
			{
				link.l4 = "Podaruj zwykłą lunetę."; // 2
				link.l4.go = "cumvana_2_4";
			}
			if (GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l5 = "Podaruj dobrą lunete."; // 4
				link.l5.go = "cumvana_2_5";
			}
		break;
		
		case "cumvana_2_1":
			Log_Info("Dałeś pistolet");
			//Log_Info("Otrzymałeś amulety");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "pistol5", 1);
			GiveItem2Character(pchar, "obereg_9");
			GiveItem2Character(pchar, "indian_7");
			GiveItem2Character(pchar, "obereg_3");
			dialog.text = "Oh-ey! Co za piękna blada broń! Kumwana przyjmuje twój dar! Ty też, synu morza, przyjmij dar od Kumwany i ludu Locono.";
			link.l1 = "Dziękuję ci, wodzu!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_2":
			Log_Info("Dałeś kompas");
			//Log_Info("Otrzymałeś amulety");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "compass1", 1);
			GiveItem2Character(pchar, "indian_10");
			GiveItem2Character(pchar, "indian_6");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = "Oh-ey! Magiczny amulet bladolicych! Kumwana przyjmuje twój dar! Ty też, synu morza, przyjmij dar od Kumwany i ludu Locono.";
			link.l1 = "Dziękuję, szefie!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_3":
			Log_Info("Dałeś tanią lunetę");
			//Log_Info("Otrzymałeś amulety");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass1", 1);
			GiveItem2Character(pchar, "obereg_2");
			GiveItem2Character(pchar, "indian_5");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = "Oh-ey! Magiczna tuba bladych twarzy! Kumwana przyjmuje twój dar! Ty również, synie morza, przyjmij dar od Kumwany i ludu Locono.";
			link.l1 = "Dziękuję, szefie!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_4":
			Log_Info("Dałeś zwykłą lunetę");
			//Log_Info("Otrzymałeś amulety");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass2", 1);
			GiveItem2Character(pchar, "obereg_6");
			GiveItem2Character(pchar, "indian_6");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = "Oh-ey! Magiczna tuba bladolicych! Kumwana przyjmuje twój dar! Ty też, synu morza, przyjmij dar od Kumwany i ludu Locono.";
			link.l1 = "Dziękuję, szefie!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_5":
			Log_Info("Dałeś dobrą lunetę");
			//Log_Info("Otrzymałeś amulety");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass3", 1);
			GiveItem2Character(pchar, "obereg_9");
			GiveItem2Character(pchar, "indian_7");
			GiveItem2Character(pchar, "obereg_5");
			dialog.text = "Oh-ey! Magiczna rurka bladych twarzy! Kumwana przyjmuje twój dar! Ty też, synu morza, przyjmij dar od Kumwany i ludu Locono.";
			link.l1 = "Dziękuję Ci, szefie!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_3":
			dialog.text = "Co przynosi cię do naszej wioski, synie morza?";
			link.l1 = "Wódzu, przyszedłem prosić o twoją pomoc. Chcę dotrzeć do hiszpańskiego osiedla o nazwie Merida, które znajduje się wśród gór w twojej dżungli, problem polega na tym, że nie wiem, jak tam trafić. Być może mógłbyś dostarczyć mi odważnego wojownika, który pokazałby nam drogę?";
			link.l1.go = "cumvana_4";
		break;
		
		case "cumvana_4":
			dialog.text = "Oh-ey! Niebezpieczna droga, niebezpieczna. Droga tam prowadzi przez las, ziemię nieustraszonych plemienia Capong. Prawdziwe jaguary, one są, oh-ey! Ja nigdy nie idę do tego hiszpańskiego miejsca. Moi ludzie - pokojowi ludzie, nie idziemy do ziemi Capong.";
			link.l1 = "Naprawdę muszę dostać się do Meridy. Kumwana, zapytaj swoich ludzi, może ktoś zgodzi się dołączyć do mojej jednostki? Moi wojownicy są doświadczeni, dobrze uzbrojeni i niczego się nie boją, nawet Diabła. Ochronimy przewodnika i hojnie go wynagrodzimy, gdy to się skończy.";
			link.l1.go = "cumvana_5";
		break;
		
		case "cumvana_5":
			dialog.text = "Bardzo dobrze, synu morza. Zgromadzę krąg wojowników i opowiem im o twoich pragnieniach. Zobacz mnie jutro po świcie.";
			link.l1 = "Dziękuję, wodzu!";
			link.l1.go = "cumvana_6";
		break;
		
		case "cumvana_6":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_SetStayType(pchar);
			npchar.dialog.currentnode = "cumvana_7";
			//AddQuestRecord("Roger_5", "6");
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			SetLaunchFrameFormParam("The next day...", "Mtraxx_MeridaVozhdDialog", 0, 4.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 1, 0, 0);
			RecalculateJumpTable();
		break;
		
		case "cumvana_7":
			dialog.text = "Oh-ey! Ty znowu, synu morza. Co chcesz powiedzieć Kumwanie?";
			link.l1 = "Nic jeszcze, wodzu.";
			link.l1.go = "cumvana_7x";
			if(CheckAttribute(pchar,"questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "merida_hayamee")
			{
				link.l2 = "Słuchaj, Kumwana. Ja i moi ludzie naprawdę musimy przekroczyć rzekę i dotrzeć do tego przeklętego małego miasteczka. Pozwól mi wyjaśnić, jak ważne jest to dla nas.";
				link.l2.go = "cumvana_hard";
			}
		break;
		
		case "cumvana_hard":
			dialog.text = "Moi łowcy już cię poinformowali, że...";
			link.l1 = "Nie ma potrzeby powtarzać się dwa razy, Kumwana. Ale spójrz na zewnątrz - i nie przeceniaj swoich możliwości. Moi odważni chłopcy, którzy przyszli tu po hiszpańskie kamienie, są rozproszeni po twojej wiosce. I ich cierpliwość się kończy. A co się stanie, gdy w końcu się skończy, lepiej, żebyś nie wiedział - uwierz mi.";
			link.l1.go = "cumvana_medium_1";
			link.l2 = "Zamknij swoją paszczę i słuchaj, czerwonoskóra małpo. Moi ludzie mogą być o wiele straszniejsi niż te przeklęte Kapongi. Nie daj się zmylić tym, że jesteśmy teraz tacy mili. Daję ci prosty wybór: albo znajdziesz przewodnika w ciągu dwudziestu czterech godzin, albo związujemy was wszystkich i wyślemy przez dżunglę przed naszym oddziałem. Jeśli poprowadzisz nas w niewłaściwym kierunku, sam zginiesz w bagnach albo pójdziesz związany walczyć z Kapongami. Zrozumiałeś?";
			link.l2.go = "cumvana_hard_1";
			link.l3 = "Kumwana, potrzebuję tego przewodnika. Przebyliśmy długą drogę i naprawdę nie chcę mówić moim ludziom, że to było na próżno.";
			link.l3.go = "cumvana_good_1";
			pchar.questTemp.Mtraxx_MeridaZapugivanieIndeets = true;
		break;
		
		case "cumvana_good_1":
			dialog.text = "Kumwana już powiedział, żaden z Lokono nie chce iść z bladą twarzą.";
			link.l1 = "I nie możesz nic z tym zrobić? Poproś kogoś osobiście. Nakazuj, przecież. Jesteś wodzem czy nie?";
			link.l1.go = "cumvana_good_2";
		break;
		
		case "cumvana_good_2":
			dialog.text = "Wódz nie zmusza Indianina. Wódz rządzi i pragnie pokoju dla swojego ludu. Indianie wiedzą - Kapong zobaczy, że Lokono przyprowadzają bladotwarzy. Ich głowy mają zostać schwytane przez Kanaima. Przyjadą, aby zemścić się na Lokono. Kapong - aby zabić. Schwytaj Lokono, zrób z nich niewolników.";
			link.l1 = "I kto zdobył wasze głowy? Jaki duch czy demon sprawia, że Indianie są tak tchórzliwymi robakami? Cóż, być może naprawdę będę musiał porzucić kampanię przeciwko Merida. Ale pamiętaj o czymś, wodzu. Gdykolwiek mnie pytają, co wiem o Lokono, zawsze odpowiadam - że to plemię bezwartościowych tchórzów. Prowadzone przez równie tchórzliwego i krótkowzrocznego wodza, którego twarz jest zniekształcona grimasą grozy na samą pamięć o Kapongs. Nie zdobędziesz sławy wśród Indian, ani szacunku wśród nas, bladych twarzy.";
			link.l1.go = "cumvana_good_3";
		break;
		
		case "cumvana_good_3":
			dialog.text = "Białotwarz nie zna zwyczajów Indian...";
			link.l1 = "Wiem wystarczająco dużo, aby wiedzieć, kogo Indianie nazywają tchórzem, a kogo dzielnym wojownikiem. Żegnaj, Kumwana. I pamiętaj moje słowa. Jesteś tchórzliwym i krótkowzrocznym władcą.";
			link.l1.go = "cumvana_good_4";
		break;
		
		case "cumvana_good_4":
			DialogExit();
			ChangeIndianRelation(5.00);
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Women")) DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			pchar.questTemp.Mtraxx = "fail";
			
			pchar.quest.Mtraxx_MeridaHayameeGoodDialog.win_condition.l1 = "location";
			pchar.quest.Mtraxx_MeridaHayameeGoodDialog.win_condition.l1.location = "Locono_village";
			pchar.quest.Mtraxx_MeridaHayameeGoodDialog.function = "Mtraxx_MeridaHayameeGoodDialog";
		break;
		
		case "cumvana_medium_1":
			dialog.text = "Dlaczego mi grozisz tak? Myślimy, że jesteś dobry...";
			link.l1 = "Będe dobry, o ile będziesz współpracować, rozumiesz? Masz jeden dzień. I wierz mi, moi ludzie zrobią wszystko, co im rozkażę. Jesteśmy silniejsi. A jeśli w to wątpisz... Widziałem twoją żonę. I twoje córki. Myślę, że teraz zrozumiałeś przekaz.";
			link.l1.go = "cumvana_hard_2";
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;
		
		case "cumvana_hard_1":
			dialog.text = "Dlaczego mi grozisz? Myślimy, że jesteś dobry...";
			link.l1 = "Będe dobry, o ile współpracujesz, rozumiesz? Masz jeden dzień. I uwierz mi, moi ludzie zrobią wszystko, co rozkażę. Jesteśmy silniejsi. A jeśli w to wątpisz... Widziałem twoją żonę. I twoje córki. Myślę, że teraz rozumiesz przekaz.";
			link.l1.go = "cumvana_hard_2";
		break;
		
		case "cumvana_hard_2":
			dialog.text = "Kumwana rozumie, bladej twarzy. W wiosce jest myśliwy o imieniu Tagofa. Być może on może cię poprowadzić do osady...";
			link.l1 = "Wrócę za dwadzieścia cztery godziny. Charlie Prince nie ma nic więcej do dodania, dzikusie.";
			link.l1.go = "cumvana_hard_3";
		break;
		
		case "cumvana_hard_3":
			DialogExit();
			ref Hayam = characterFromId("Hayamee");
			ChangeCharacterAddressGroup(Hayam, "none", "", "");
			Hayam.lifeday = 0;
			pchar.questTemp.Mtraxx = "merida_hayamee_hard";
			npchar.dialog.currentnode = "cumvana_7";
			SetFunctionTimerCondition("Mtraxx_MeridaHayameeHardTagofaWait", 0, 0, 1, false);
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Women")) DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			ChangeCharacterComplexReputation(pchar, "nobility", -80);
			ChangeOfficersLoyality("bad", 5);
			ChangeIndianRelation(-50.0);
			//log_Info("The attitude of the Indians has decreased");
			AddQuestRecord("Roger_5", "8a");
			pchar.GenQuest.CannotWait = true; //запретить отдыхать
			
			pchar.quest.Mtraxx_MeridaHayameeHardLepriconDialog.win_condition.l1 = "location";
			pchar.quest.Mtraxx_MeridaHayameeHardLepriconDialog.win_condition.l1.location = "Locono_village";
			pchar.quest.Mtraxx_MeridaHayameeHardLepriconDialog.function = "Mtraxx_MeridaHayameeHardLepriconDialog";
		break;
		
		case "cumvana_7x":
			DialogExit();
			npchar.dialog.currentnode = "cumvana_7";
		break;
		
		case "cumvana_8":
			dialog.text = "Synie morza, to ty. Kumwana rozmawiał z wojownikami Locono.";
			link.l1 = "No cóż? Masz ochotnika?";
			link.l1.go = "cumvana_9";
		break;
		
		case "cumvana_9":
			dialog.text = "Mamy kilku myśliwych, którzy byli tam. Ale boją się Capongów, jaguary są na ścieżce wojennej. Oni nie idą, mówią, że Capong zabije twój oddział. Nie boją się bladych twarzy.";
			link.l1 = "Moi wojownicy są o wiele lepsi niż wszyscy inni! Część mojej jednostki spędziła całe życie w dżungli! Nie jesteśmy jacyś amatorzy!";
			link.l1.go = "cumvana_10";
		break;
		
		case "cumvana_10":
			dialog.text = "Przykro mi, synu morza. Moi łowcy się boją, Capongs są niebezpieczne, bardzo bardzo.";
			link.l1 = "Dobrze, a może w takim razie, mogliby wyjaśnić, jak tam dotrzeć? W szczegółach.";
			link.l1.go = "cumvana_11";
		break;
		
		case "cumvana_11":
			dialog.text = "Aby tam dotrzeć, powinieneś popłynąć rzeką, a następnie wysiąść w specjalnym miejscu. Jeśli to złe miejsce, wpadniesz do bagna i umrzesz. Nasza selva pełna jest niebezpieczeństw. Nie znajdziesz tego miejsca sam, synu morza.";
			link.l1 = RandSwear()+", A co powinienem wtedy zrobić? Jak przekonać twoich myśliwych?";
			link.l1.go = "cumvana_12";
		break;
		
		case "cumvana_12":
			dialog.text = "Kumwana mówi dość, synie morza.";
			link.l1 = "Dobrze...";
			link.l1.go = "cumvana_13";
		break;
		
		case "cumvana_13":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetPlayerType(pchar);
			npchar.dialog.currentnode = "cumvana_7";
			AddQuestRecord("Roger_5", "7");
			pchar.questTemp.Mtraxx = "merida_advice";
			LAi_SetHuberType(npchar);
			AddLandQuestMark(characterFromId("Lepricon"), "questmarkmain");
		break;
		
		// Хайами
		case "hayamee":
			if (npchar.id == "Hayamee")
			{
				dialog.text = "Mój mąż Tagofa to najlepszy myśliwy w plemieniu. Oh-ey! "+npchar.name+" jest dumna ze swojego męża. "+npchar.name+" często idzie z Tagofą do Selvy. Idź daleko. Tagofa wie, gdzie jest hiszpańska osada.";
				if (IsCharacterPerkOn(pchar, "Trustworthy") && stf(pchar.questTemp.Indian.relation) >= 40.0)
				{
					link.l1 = "Czy Tagofa zna drogę do hiszpańskiego miasta, które blade twarze nazywają Merida?";
					link.l1.go = "hayamee_1";
				}
				else
				{
					link.l1 = "Cóż, cóż... Czy Tagofa wie, jak dostać się do hiszpańskiego miasta?";
					link.l1.go = "hayamee_bad_1";
				}
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple("Mój mąż nie idzie do dżungli, synu morza. On łowi ryby. Dobry rybak, oj-oj! ","Mój mąż dobry łowca, oh-ey, ale nie idzie do głębokiej dżungli."),RandPhraseSimple("Jaguar zranił mojego męża na polowaniu. Teraz siedzi we wsi, robi strzałki, oh-ey!","Sześć księżyców temu trzej Capongowie zaatakowali mojego męża. Teraz on nie chodzi na polowanie daleko od wioski. Nigdy! oh-ey!"));
				link.l1 = LinkRandPhrase("Szkoda...","Szkoda...","Jaka szkoda..."));
				link.l1.go = "exit";
			}
		break;
		
		case "hayamee_bad_1":
			dialog.text = "Tagofa dorastał w tej dżungli. Zna każde drzewo i każdy kamień wokół!";
			link.l1 = "Dam ci i Tagofie wiele prezentów, jeśli zabierze nas tam. Biżuteria, broń, cokolwiek. Cokolwiek chcesz. Oczywiście, w granicach rozsądku, he-he. Jak mogę porozmawiać z twoim mężem?";
			link.l1.go = "hayamee_bad_2";
		break;
		
		case "hayamee_bad_2":
			dialog.text = "Tagofa nie pójdzie z bladą twarzą. Tagofa zostanie we wsi. Pójdzie na polowanie. Nie będzie walczyć z Kapongiem.";
			link.l1 = "On nie będzie musiał walczyć z Kapong. Jak tylko ich zobaczy, może się schować. Tylko moi ludzie będą walczyć.";
			link.l1.go = "hayamee_bad_3";
		break;
		
		case "hayamee_bad_3":
			dialog.text = "Nie, yalanaui. Białotwarz nigdy nie dotrzymuje słowa. Białotwarz mówi - a słowo natychmiast ucieka w próżnię. Kapong zabije Tagofę, a potem przyjdzie do naszej wioski, zabije Lokono.";
			link.l1 = "Czy myślisz, że te Kapongi to wszystko, o co musisz się martwić? Bardzo się mylisz...";
			link.l1.go = "hayamee_bad_4";
			if (stf(pchar.questTemp.Indian.relation) < 40.0) notification("The Indians don't respect you "+stf(pchar.questTemp.Indian.relation)+"/40", "None");
			if (!IsCharacterPerkOn(pchar, "Trustworthy")) notification("Brak zdolności", "Godny Zaufania");
		break;
		
		case "hayamee_bad_4":
			dialog.text = "Yahahu, aby wejść do bladolicy! Hayami już nie mówi do yalanaui.";
			link.l1 = "Cóż-cóż...";
			link.l1.go = "hayamee_bad_5";
		break;
		
		case "hayamee_bad_5":
			DialogExit();
			pchar.questTemp.Mtraxx = "merida_hayamee";
			DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			LAi_CharacterDisableDialog(npchar);
		break;
		case "hayamee_1":
			dialog.text = "Tagofa poszedł na polowanie dzień temu. Obiecał wrócić jutro, gdy słońce śpi. Przyjdź jutro, synu morza, będę z Tagofą w tej chacie, idź w prawo jak wejdziesz do wioski. Zapytam go, czy pójdzie z tobą, czy nie.";
			link.l1 = "Powiedz Tagofie, że podaruję mu najpiękniejszy pistolet. A tobie podaruję mnóstwo klejnotów.";
link.l1.go = "hayamee_1_1";
		break;
		
		case "hayamee_1_1":
			dialog.text = "Lokono nie ufają Yalanaui. Yalanaui oszukują Indianina, czynią z Indianina niewolnika. Ale Lokono słyszał twoje imię, bladej twarzy. Moje zaufanie jest twoje. Przyjdź jutro po zachodzie słońca, synu morza. Będę z Tagofą w tamtej chacie. Zapytam go, czy pójdzie z tobą, czy nie.";
			link.l1 = "Powiedz Tagofie, że dam mu mój najpiękniejszy pistolet. A dla ciebie mam wiele klejnotów.";
			link.l1.go = "hayamee_2";
			notification("The Indians respect you "+stf(pchar.questTemp.Indian.relation)+"/40", "None");
			notification("Trustworthy", "Trustworthy");
		break;
		
		case "hayamee_2":
			dialog.text = "Oh-ey!";
			link.l1 = "...";
			link.l1.go = "hayamee_3";
		break;
		
		case "hayamee_3":
			DialogExit();
			AddQuestRecord("Roger_5", "9");
			DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			LAi_CharacterDisableDialog(npchar);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.hour  = 22.0;
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.function = "Mtraxx_MeridaHayameeTimer";
		break;
		
		case "hayamee_4":
			pchar.quest.Mtraxx_MeridaPotionLate.over = "yes";
			dialog.text = ""+npchar.name+" cieszy się, widząc syna morza. Tagofa wrócił. Ale wypił za dużo kasheeri i śpi. Nie budź go, Tagofa odpoczywa. Ja porozmawiam.";
			link.l1 = "Bardzo dobrze, "+npchar.name+". Czy twój mąż poprowadzi nas do Meridy?";
			link.l1.go = "hayamee_5";
		break;
		
		case "hayamee_5":
			dialog.text = "Tagofa zgodził się prowadzić twoich wojowników przez selwę do hiszpańskiej wioski. Ale są pewne warunki...";
			link.l1 = "Które są?";
			link.l1.go = "hayamee_6";
		break;
		
		case "hayamee_6":
			dialog.text = "Chronisz Tagofę przed wojownikami Capong. Tagofa nie walczy z żadnymi Hiszpanami, żadnymi Capong. Jeśli stawi czoła niebezpieczeństwu, ucieknie i nikt go nie znajdzie, jest najlepszym myśliwym Locono.";
			link.l1 = "Rozumiem. Martwisz się o swojego człowieka, to zrozumiałe. Obiecuję ci, że sami poradzimy sobie ze wszystkimi tymi Capongami.";
			link.l1.go = "hayamee_7";
		break;
		
		case "hayamee_7":
			dialog.text = "Oh-ey! Tagofa chce prezenty od syna morza: jeden mały, aby strzelać wiele kamieni i jeden duży, aby strzelać jeden kamień, te ładne. Chce też kulki do każdej pistolet: tyle co palce obu rąk trzy razy.";
			link.l1 = "O rety! Twój człowiek zna się na działach, co? Bardzo dobrze. Co jeszcze?";
			link.l1.go = "hayamee_8";
		break;
		
		case "hayamee_8":
			dialog.text = "A Tagofa chce piękne magiczne oko bladych twarzy.";
			link.l1 = "Luneta? Dobrze. Czy coś jeszcze?";
			link.l1.go = "hayamee_9";
		break;
		
		case "hayamee_9":
			dialog.text = "Nic więcej dla Tagofa."+npchar.name+" chce ładnych rzeczy. Złoty pierścionek z dużym czerwonym kamieniem i koraliki z wielu, wielu zielonych kamieni. "+npchar.name+" widziałem to na białej Mary w Maracaibo.";
			link.l1 = "Złoty pierścień z rubinami i jadeitowymi koralikami?";
			link.l1.go = "hayamee_10";
		break;
		
		case "hayamee_10":
			dialog.text = "Nie jadeit. To błyszczy i biali ludzie to cenią.";
			link.l1 = "Szmaragd? Szmaragdowe koraliki?";
			link.l1.go = "hayamee_11";
		break;
		
		case "hayamee_11":
			dialog.text = "Oh-ey!";
			link.l1 = "Heh, "+npchar.name+" wie coś o klejnotach! Bardzo dobrze, dostaniesz to.";
			link.l1.go = "hayamee_12";
		break;
		
		case "hayamee_12":
			dialog.text = "Przynieś wszystko do "+npchar.name+" razem, synu morza. Wtedy Tagofa poprowadzi ciebie i twoich wojowników. Nie marnuj czasu, za półksiężyca Tagofa i ja pójdziemy do sąsiedniej wioski. Na wielkie święto. Teraz idź, "+npchar.name+" chce iść spać.";
			link.l1 = "Nie będę cię zbyt długo trzymać. Do zobaczenia.";
			link.l1.go = "hayamee_13";
		break;
		
		case "hayamee_13":
			DialogExit();
			AddQuestRecord("Roger_5", "10");
			LAi_CharacterDisableDialog(npchar);
			SetFunctionTimerCondition("Mtraxx_MeridaHayameeLate", 0, 0, 15, false); // таймер
			// Тагофу в сидячее положение
			pchar.quest.mtraxx_merida_wait2.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.hour  = 9.0;
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.function = "Mtraxx_MeridaTagofaHide";
		break;
		
		case "hayamee_14":
			bOk = GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0;
			dialog.text = "Przyniosłeś co "+npchar.name+" a Tagofa zapytał?";
			if (bOk && GetCharacterFreeItem(pchar, "pistol3") > 0 && GetCharacterFreeItem(pchar, "pistol5") > 0 && GetCharacterItem(pchar, "bullet") >= 30 && GetCharacterItem(pchar, "grapeshot") >= 30 && GetCharacterItem(pchar, "gunpowder") >= 60 && CheckCharacterItem(pchar, "jewelry41") && CheckCharacterItem(pchar, "jewelry42"))
			{
				link.l1 = "Tak. Wszystko jest zgodne z twoją listą.";
				link.l1.go = "hayamee_15";
			}
			else
			{
				link.l1 = "Nie, nadal nad tym pracuję.";
				link.l1.go = "hayamee_14x";
			}
		break;
		
		case "hayamee_14x":
			DialogExit();
			npchar.dialog.currentnode = "hayamee_14";
		break;
		
		case "hayamee_15":
			pchar.quest.Mtraxx_MeridaHayameeLate.over = "yes";
			Mtraxx_MeridaRemoveGifts();
			dialog.text = ""+npchar.name+" jest szczęśliwy, synie morza. Teraz nazywam mężem. Idzie z tobą. Ale pamiętaj, co obiecałeś "+npchar.name+"!";
			link.l1 = "Tak-tak, pamiętam wszystko. Będę go chronił, nie martw się.";
			link.l1.go = "hayamee_16";
		break;
		
		case "hayamee_16":
			DialogExit();
			pchar.questTemp.Mtraxx = "merida_hayamee_peace";
			chrDisableReloadToLocation = true;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 7.0);
			DoQuestFunctionDelay("Mtraxx_MeridaTagofaEnter", 20.0);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
			
		case "CitizenNotBlade":
			dialog.text = "Odłóż swoją broń, bladolicie, inaczej zmusimy cię do tego!";
			link.l1 = LinkRandPhrase("Dobrze.","Dobrze.","Nie martw się, odkładam to...");
			link.l1.go = "exit";
		break;  

	}
}

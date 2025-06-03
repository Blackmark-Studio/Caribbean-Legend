//Jason общий диалог цыганок
// ugeen <-- добавил продажу мышьяка из под полы
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	int poison_price;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Ach, witaj, kochanie. Czego sobie życzysz?";
			link.l1 = "Nic, jak sądzę.";
			link.l1.go = "exit";
			link.l2 = RandPhraseSimple("Mam do ciebie pytanie.","Potrzebuję informacji.");
			link.l2.go = "quests";//(перессылка в файл города)
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = LinkRandPhrase("Kochańcu, czy byłbyś tak uprzejmy, aby podzielić się złotem? Powiem ci, jaka cię czeka przyszłość.","Ej, marynarzu, nie śpiesz się tak! Chcesz poznać przyszłość?","Daj mi trochę tytoniu i kilka srebrnych monet, odważny młodzieńcze. A ja spojrzę w twoją przyszłość. (mrugnięcie) Chcesz usłyszeć sekretne cygańskie czary?");
				link.l1 = "Przykro mi, ale muszę iść.";
				link.l1.go = "exit";
				// --> мангароса
				if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "gipsy" && !CheckAttribute(npchar, "quest.mangarosa"))
				{
					link.l5 = "Słuchaj, cygańska damo, wiem, że twoi ludzie to eksperci od mikstur i trucizn. Powiedziano mi, że mogłabyś być zainteresowana tą rośliną. Spójrz. Co o tym sądzisz?";
					link.l5.go = "mangarosa";
				}
				if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "gipsy_trade" && !CheckAttribute(npchar, "quest.mangarosa"))
				{
					link.l5 = "Ej, ciemnookie, mam coś dla ciebie... To jest mangarosa. Chcesz kupić trochę??";
					link.l5.go = "mangarosa_trade1";
				}
				// <-- мангароса
				link.l2 = "Możesz przepowiedzieć mi przyszłość?";
				link.l2.go = "guess";
				link.l3 = RandPhraseSimple("Mam do ciebie pytanie.","Potrzebuję informacji.");
				link.l3.go = "quests";//(перессылка в файл города)
				npchar.quest.meeting = "1";
			}
			// --> Тёмные воды исцеления
			if (CheckAttribute(pchar, "questTemp.DWH_Start") && !CheckAttribute(pchar, "questTemp.DWH_gipsy") && npchar.city == "SentJons")
			{
				link.l6 = "Szukam Cyganki, która leczy ludzi. Czy to ty?";
				link.l6.go = "dwh_gypsy_1";
			}
			// <-- Тёмные воды исцеления
			if (!CheckAttribute(npchar, "quest.poison_price") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && rand(2) == 0)
			{
				link.l4 = "Hej, czarnookie, masz jakieś trucizny na szczury? Są przeklętym utrapieniem na moim statku.";
				link.l4.go = "get_poison_1";
			}
			NextDiag.TempNode = "First time";
		break;

//-------------------------------------------------гадание-------------------------------------------------
		case "guess":
			dialog.text = "Oczywiście, przystojniaku. Daj mi trochę monet i pokaż prawą rękę. Opowiem ci o twojej przyszłości i pomogę uniknąć katastrofy. Nigdy nie oszukuję! Gwarancja zwrotu pieniędzy!";
			link.l1 = "Czuję, że to ten moment, kiedy twój rodak opróżnia mi kieszenie...Zmieniam zdanie. Nie jestem w nastroju.";
			link.l1.go = "exit";
			link.l2 = "Ile pieniędzy chcesz?";
			link.l2.go = "guess_1";
		break;
		
		case "guess_1":
			dialog.text = "Ach drogi, tyle ile twój mieszek pozwala i serce pragnie. Im więcej sztuk ośmiu, tym dalej w przyszłość mogę spojrzeć!";
			link.l1 = "100 pesos";
			link.l1.go = "guess_rate_1";
			link.l2 = "500 pesos";
			link.l2.go = "guess_rate_2";
			link.l3 = "1000 pesos";
			link.l3.go = "guess_rate_3";
			link.l4 = "5000 pesos";
			link.l4.go = "guess_rate_4";
		break;
		
		sTemp = GuessText();
		case "guess_rate_1"://никаких плюшек
			if (sti(pchar.money) >= 100)
			{
				AddMoneyToCharacter(pchar, -100);
				dialog.text = "Ach, dziękuję za twoją hojność, mój przystojny młody sokołu! Teraz posłuchaj:  "+sTemp+" ";
				link.l1 = LinkRandPhrase("Heh! To bardzo interesujące. Wezmę to pod uwagę...","Naprawdę? Rozważę to...","O, naprawdę? Mówisz poważnie? Zapamiętam to...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Najbrzydsze i nieuniknione nieszczęście czeka na ciebie. Przeklnij szydercę! Niech ciemne chmury zgromadzą się nad tobą i niech kara cię dosięgnie!";
				link.l1 = "Ha-ha! Naprawdę myślałeś, że dam ci pieniądze, ty cygańska wiedźmo? Zejdź mi z drogi! Mam nadzieję, że inkwizycja cię dopadnie!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_2"://немного в везение или скрытность
			if (sti(pchar.money) >= 500)
			{
				AddMoneyToCharacter(pchar, -500);
				dialog.text = "Ach, dziękuję, mój przystojny młody sokole! Teraz słuchaj:"+sTemp+"";
				link.l1 = LinkRandPhrase("Heh! To bardzo interesujące. Wezmę to pod uwagę...","Naprawdę? Rozważę to...","O, naprawdę? Naprawdę? Cóż, zapamiętam to...","Hej, już czuję się lepiej!");
				link.l1.go = "exit";
				if (hrand(1) == 0) AddCharacterExpToSkill(pchar, "Fortune", 30+rand(10));//везение
				else AddCharacterExpToSkill(pchar, "Sneak", 30+rand(10));//скрытность
			}
			else
			{
				dialog.text = "Najbrzydsze i nieuniknione nieszczęście czeka na ciebie. Przeklinaj szydercę! Niech ciemne chmury zgromadzą się nad tobą i niech kara cię dosięgnie!";
				link.l1 = "Ha-ha! Naprawdę myślałeś, że dam ci pieniądze, ty cygańska wiedźmo? Zejdź mi z drogi! Mam nadzieję, że Inkwizycja cię dopadnie!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_3"://здоровье + везение или скрытность, харизма
			if (sti(pchar.money) >= 1000)
			{
				AddMoneyToCharacter(pchar, -1000);
				dialog.text = "Ach, dzięki za twoje srebro, mój przystojny młody sokołu! Teraz słuchaj:"+sTemp+" ";
				link.l1 = LinkRandPhrase("Heh! To bardzo interesujące. Rozważę to...","Naprawdę? Rozważę to...","O, naprawdę? Mówisz poważnie? Cóż, zapamiętam to...");
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 1);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				if (hrand(1) == 0) AddCharacterExpToSkill(pchar, "Fortune", 50+rand(20));//везение
				else AddCharacterExpToSkill(pchar, "Sneak", 50+rand(20));//скрытность
			}
			else
			{
				dialog.text = "Najbrzydsze i nieuniknione nieszczęście czeka na ciebie. Przekleństwo na szydercę! Niech ciemne chmury zbiorą się nad tobą i niech kara cię odnajdzie!";
				link.l1 = "Ha-ha! Czy naprawdę myślałaś, że dam ci pieniądze, ty cygańska wiedźmo? Zejdź mi z drogi! Mam nadzieję, że Inkwizycja cię złapie!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_4"://умения в оружие, везение+скрытность, здоровье, харизма
			if (sti(pchar.money) >= 5000)
			{
				AddMoneyToCharacter(pchar, -5000);
				dialog.text = "Oh la la! Dziękuję za twoją hojność, mój przystojny młody sokołku! Teraz słuchaj:"+sTemp+" ";
				link.l1 = LinkRandPhrase("Heh! To bardzo interesujące. Rozważę to...","Naprawdę? Rozważę to...","O, naprawdę? Mówisz poważnie? Cóż, zapamiętam to...");
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 2);
				AddCharacterExpToSkill(pchar, "Leadership", 40);
				AddCharacterExpToSkill(pchar, "Fortune", 50+rand(100));//везение
				AddCharacterExpToSkill(pchar, "Sneak", 50+rand(50));//скрытность
				AddComplexSelfExpToScill(20, 20, 20, 20);
			}
			else
			{
				dialog.text = "Najbrzydsze i nieuniknione nieszczęście czeka na ciebie. Przeklęty szyderca! Niech ciemne chmury zbierają się nad tobą i niech kara cię znajdzie!";
				link.l1 = "Ha-ha! Czy naprawdę myślałaś, że dam ci pieniądze, ty cygańska wiedźmo? Zejdź mi z drogi! Mam nadzieję, że Inkwizycja cię dorwie!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_exit":
			DialogExit();
			AddCharacterHealth(pchar, -10);
			LAi_CharacterDisableDialog(npchar);
		break;
//<-- гадание

// --> продажа мышьяка
		case "get_poison_1" :
			npchar.quest.poison_price = (hrand(3) + 1) * 10;
			if(hrand(10) == 3 || IsCharacterPerkOn(pchar, "Trustworthy"))
			{				
				dialog.text = LinkRandPhrase("Och, nie jestem pewna, przystojniaku! Niedawno był tu facet, który prosił o pomoc w zabijaniu szczurów, a potem ktoś zatruł żołnierzy w forcie. Zrobiło się dość gorąco dla moich ludzi na wyspie, gdy strażnicy przesłuchiwali nas przez dwa tygodnie, aż znaleźli mordercę. Był to szpieg wroga.","A jak mogę być pewny twojego celu? Może po prostu chcesz otruć szlachcica, z którym jesteś zbyt tchórzliwy, by walczyć w honorowym pojedynku??","Słyszałem, że ktoś otruł jakiegoś handlarza w tawernie i ukradł wszystkie jego rzeczy. Człowiek ten cierpiał przez długi czas, zanim wyzionął ducha. Piana wychodziła mu z ust i zrobił się fioletowy jak bakłażan... Czy to ty za tym stoisz, moja miła?");
				link.l1 = "Wy, cygańskie dziewki, z pewnością lubicie dzielić się swoimi opiniami! Nie martw się, dziewczyno, nie zamierzam truć ludzi. To kobiecy sposób zabijania, nie w moim stylu. Na mężczyzn mam swój miecz, ale nie radzę sobie z tymi przeklętymi szczurami.";
				link.l1.go = "get_poison_2";
				if (IsCharacterPerkOn(pchar, "Trustworthy")) notification("Trustworthy", "Trustworthy");
			}
			else
			{
				dialog.text = "Próbujesz mnie wrobić! Nie, panie, nie mam żadnej trucizny. Mam rośliny i mikstury, ale żadnych trucizn.";
				link.l1 = "Cokolwiek, zatem. Nie rzucaj na mnie złego oka.";
				link.l1.go = "exit";
				notification("Perk Check Failed", "Trustworthy");
			}	
		break;
		
		case "get_poison_2" :
			dialog.text = "O, przystojny, taki dzielny mężczyzna! (szeptem) Zapłać mi "+sti(npchar.quest.poison_price)+"  дублонów.";
			if (PCharDublonsTotal() >= sti(npchar.quest.poison_price))
			{				
				link.l1 = "Drogo... To lepiej niech działa.";
				link.l1.go = "get_poison_4";
			}
			else
			{
				link.l1 = "Nie ma mowy! Kupiłem to samo w domu za pięć pistolów! Za takie pieniądze sam bym złapał wszystkie szczury!";
				link.l1.go = "get_poison_3";
			}
		break;
		
		case "get_poison_3" :
			dialog.text = "Złap ich sam, a mnie nie zawracaj głowy. Następnym razem zawołam straż.";
			link.l1 = "Nie potrzeba straży, wiedźmo, wychodzę.";
			link.l1.go = "exit";
		break;
		
		case "get_poison_4" :
			PlaySound("interface\important_item.wav");
			RemoveDublonsFromPCharTotal(sti(npchar.quest.poison_price));
			TakeNItems(pchar, "rat_poison", 1);
			DialogExit();
		break;
// <-- продажа мышьяка

	// --> Мангароса
		case "mangarosa":
			dialog.text = LinkRandPhrase("Pokaż mi tę roślinę, kochana... Hm... Przypuszczam, że mogę ją od ciebie kupić. Trzysta sztuk ośmiu, zgoda?","Pokaż mi to, przystojniaku... Heh... Cóż, mogę zapłacić dwieście pięćdziesiąt za to.","Zobaczmy... O! Ciekawy przykład! Dwieście pesos! Umowa?")"";
			link.l1 = LinkRandPhrase("O Panie... ciemnooka, nie jestem jakimś prowincjonalnym głupcem. Znam tę roślinę. To mangarosa...","O, naprawdę?! To doskonały okaz mangarosa. Nie próbuj mnie oszukać, cyganie.","Aha, i myślisz, że dam ci tę mangarosę za tak nędzną sumę.");
			link.l1.go = "mangarosa_1";
		break;
		
		case "mangarosa_1":
			dialog.text = "Dobrze, dobrze, przystojniaku. Widzę, że coś wiesz o tej roślinie. Pięćdziesiąt doubloonów. Daj mi to.";
			link.l1 = "Zaczekaj teraz! Chcę wiedzieć, jak można to wykorzystać i do czego. Czy możesz mi o tym opowiedzieć? Wszyscy twoi ludzie są gotowi zapłacić dużo złota za ten mały krzew!";
			link.l1.go = "mangarosa_2";
		break;
		
		case "mangarosa_2":
			// тут работает харизма
			if (sti(pchar.questTemp.Mangarosa.g_count) == 5 || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 10+hrand(25)+hrand(30, "1"))
			{
				dialog.text = "Hm... Przypuszczam, że nie jest zbyt źle, jeśli opowiem ci o tym trochę. Nie będziesz w stanie nic zrobić z tą rośliną bez specjalnych umiejętności.";
				link.l1 = "Słucham.";
				link.l1.go = "mangarosa_3";
			}
			else
			{
				dialog.text = LinkRandPhrase("Moi ludzie mogą zapłacić dużo złota, ale nigdy nie zdradzą swoich tajemnic.","Złoto to złoto, a sekrety to sekrety, młody człowieku... ","Aj, jesteśmy gotowi zapłacić, ale nie mówić.")+"Więc sprzedasz mi swoją mangarosę? Pięćdziesiąt dublonów to nasza cena, nikt ci nie zapłaci więcej.";
				link.l1 = "Och, dobrze... Tak czy inaczej, mi to pasuje. Pięćdziesiąt dublonów. Weź to";
				link.l1.go = "mangarosa_trade";
				link.l2 = "Zrozum mnie, nie chcę tego sprzedawać. Chcę wiedzieć, dlaczego tego potrzebujesz. Podziel się ze mną swoją wiedzą, a dam ci to za darmo.";
				link.l2.go = "mangarosa_exit";
			}
		break;
		
		case "mangarosa_trade":
			RemoveItems(pchar, "cannabis7", 1);
			TakeNItems(pchar, "gold_dublon", 50);
			PlaySound("interface\important_item.wav");
			dialog.text = "Weź swoje monety, młody sokołku. I jeszcze jedno, przynieś nam więcej tych roślin. Ale możemy je kupować tylko po jednej sztuce, bo nie nosimy przy sobie dużych sum. Strażnicy nie ufają naszym i lubią nas dręczyć...";
			link.l1 = "Dobrze. Jeśli znajdę więcej, przyniosę to.";
			link.l1.go = "mangarosa_trade_exit";
		break;
		
		case "mangarosa_trade_exit":
			DialogExit();
			npchar.quest.mangarosa = "true";
			DeleteAttribute(pchar, "questTemp.Mangarosa.g_count");
			pchar.questTemp.Mangarosa = "gipsy_trade";
			AddQuestRecord("Mangarosa", "3");
		break;
		
		case "mangarosa_exit":
			dialog.text = LinkRandPhrase("Nie ma mowy! Jeśli nie chcesz tego sprzedać - to nie sprzedawaj. Nic ci nie powiem.","Nie zdradzę naszych sekretów obcemu gadowi! (pluje) Nie chcesz tego sprzedać? Do diabła z tobą.","Przyjacielu, to nie dla twoich uszu. Nie chcesz sprzedać tego za pięćdziesiąt дублонów? Idź i sprzedaj to handlowej dziewczynie za dwieście pesos.");
			link.l1 = LinkRandPhrase("Szkoda cię wtedy! Ktoś inny z twoich ludzi i tak mi o tym opowie. A ona dostanie tę roślinę w prezencie. Do zobaczenia!","Po co taki uparty? Jeśli mi nie powiesz, to zrobi to ktoś inny. A ona dostanie tę mangarosę w prezencie. Żegnaj.","Twój oddech śmierdzi czosnkiem. W końcu dostanę to, czego chcę. Ktoś inny z twojego plemienia będzie bardziej rozmowny i dostanie roślinę za darmo. Do zobaczenia.");
			link.l1.go = "exit";
			npchar.quest.mangarosa = "true";
			pchar.questTemp.Mangarosa.g_count = sti(pchar.questTemp.Mangarosa.g_count)+1;
		break;
		
		case "mangarosa_trade1":
			dialog.text = "A czemu pytasz, sokołu?! Pewnie! Daj mi to.";
			link.l1 = "Daj mi pięćdziesiąt дублонов.";
			link.l1.go = "mangarosa_trade1_1";
			link.l2 = "Oups! Wydaje się, że zgubiłem to albo zapomniałem na moim statku. Co za szkoda. Żegnaj...";
			link.l2.go = "exit";
			npchar.quest.mangarosa = "true";
		break;
		
		case "mangarosa_trade1_1":
			RemoveItems(pchar, "cannabis7", 1);
			TakeNItems(pchar, "gold_dublon", 50);
			PlaySound("interface\important_item.wav");
			dialog.text = "Nie martw się, nie oszukam cię. Weź swoje monety.";
			link.l1 = "Weź swoją mangarosę. Przyniosę więcej, jeśli znajdę.";
			link.l1.go = "exit";
		break;
		
		case "mangarosa_3":
			dialog.text = "Rozdrabniamy pąki w specjalny sposób, potem suszymy je, usuwamy nasiona i łodygi, potem mieszamy z tytoniem, nabijamy fajki i palimy tę mieszankę. I otrzymujemy... niezapomniany efekt. Jak odurzenie alkoholem, ale bez bólu głowy po nim. Jedna roślina wystarcza na dwie tuziny nabitych fajek.";
			link.l1 = "Teraz rozumiem! Możesz mnie nauczyć tej tajnej techniki? Mogę ci dobrze zapłacić...";
			link.l1.go = "mangarosa_4";
		break;
		
		case "mangarosa_4":
			dialog.text = "Młody sokołku, zaufaj mi, nie potrzebujesz tego. Nie mieszaj się, ta roślina cię zrujnuje. Otępia umysł i powoduje, że tyjesz. Nawet mnie nie pytaj. Ale... widzę przed sobą odważnego człowieka, z mieczem, człowieka morza... może nawet kapitana?";
			link.l1 = "Masz rację.";
			link.l1.go = "mangarosa_5";
		break;
		
		case "mangarosa_5":
			dialog.text = "Słuchaj no tutaj. Mangarosa może być wykorzystana do znacznie szlachetniejszych rzeczy i możesz ją uznać za użyteczną. Jedna z naszych uzdrowicielek zna wszystkie jej tajemnice. To ją musisz znaleźć\nDaj mi roślinę, a powiem ci jej imię i gdzie ją znaleźć. Przekonanie jej, by podzieliła się swoimi sekretami, to już twój problem.";
			link.l1 = "Dobrze. Weź roślinę i powiedz mi, jak znaleźć twojego cygańskiego maga.";
			link.l1.go = "mangarosa_6";
		break;
		
		case "mangarosa_6":
			RemoveItems(pchar, "cannabis7", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Jej imię to Amelia. Mieszka sama w małym domku pośród wydm niedaleko od morza, gdzieś na południowo-zachodnim wybrzeżu Hiszpańskiej Głównej, jak mówią mądrzy ludzie.";
			link.l1 = "O mój Boże, czy możesz być bardziej konkretny?";
			link.l1.go = "mangarosa_7";
		break;
		
		case "mangarosa_7":
			dialog.text = "Jesteś marynarzem, odważny sokoł, a ja nie. Szukaj jej tam, gdzie powiedziałem. Jej dom jest naprawdę blisko wybrzeża. Jest w pobliżu zatoki na południowym zachodzie Głównej Hiszpańskiej - marynarze muszą to wiedzieć.";
			link.l1 = "Dobrze, spróbuję to znaleźć...";
			link.l1.go = "mangarosa_8";
		break;
		
		case "mangarosa_8":
			dialog.text = "Weź jej Mangarosę, bo inaczej nawet nie będzie z tobą rozmawiać. I nie zapomnij przynieść dubloonów, nie myśl nawet, że nauczy cię za darmo!";
			link.l1 = "Taka chciwość. Rozważę to. Dzięki za twoją opowieść!";
			link.l1.go = "mangarosa_9";
		break;
		
		case "mangarosa_9":
			DialogExit();
			npchar.quest.mangarosa = "true";
			DeleteAttribute(pchar, "questTemp.Mangarosa.g_count");
			pchar.questTemp.Mangarosa = "amelia";
			pchar.questTemp.Mangarosa.Tell = "true"; // калеуче
			AddQuestRecord("Mangarosa", "4");
			// создаем и ставим Амелию
			sld = GetCharacter(NPC_GenerateCharacter("Amelia", "gipsy_3", "woman", "towngirl", 10, PIRATE, -1, true, "citizen"));
			SetFantomParamFromRank(sld, 10, true);
			sld.name = "Amelia";
			sld.lastname = "";
			sld.dialog.FileName = "Quest\Mangarosa.c";
			sld.dialog.currentnode = "amelia";
			//sld.greeting = "";
			LAi_SetOwnerType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Amelia_house", "barmen", "stay");
		break;
		
		// --> Тёмные воды исцеления
		case "dwh_ne_ta":
			sld = CharacterFromID("DWH_gypsy");
			dialog.text = "Nie, " + GetSexPhrase("kochanie", "piękna") + ", to nie ja ci jestem potrzebna, tylko " + sld.name + ". Ona jest teraz w mieście. Widziałam ją niedawno.";
			link.l1 = "Dziękuję.";
			link.l1.go = "exit";
		break;
		// <-- Тёмные воды исцеления
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Słuchaj mnie, dzielny sokołku, może i jestem cyganem, ale nawet my odrzucamy otwartą przemoc. Proszę, schowaj swój miecz.","Słuchaj mnie, dzielny sokołku, jako obywatel tego miasta proszę cię, byś schował swój miecz.");
			link.l1 = LinkRandPhrase("Dobrze.","Jak sobie życzysz.","Jak mówisz...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string GuessText()
{
	string sText;
	switch (hrand(19))
	{
		case 0: sText = "you will have luck, brave young falcon, tomorrow you'll be lucky with cards!" break;
		case 1: sText = "the fortune will be kind with you in your mercantile business, captain!" break;
		case 2: sText = "there is a misfortune awaiting you in the open sea, it's waiting just for you, wait for three days!" break;
		case 3: sText = "I see that you need to seek help from your closest ones, you won't make it alone in your next fight!" break;
		case 4: sText = "go and light a candle in a church, you have been cursed by your enemy. You won't make it without God's help!" break;
		case 5: sText = "you are going to lose a lot soon, my falcon, but don't despair and hope for yourself, seek help from you friends..." break;
		case 6: sText = "a heavy loss is waiting for you in the sea, but I see, that you, captain, will be able to ride it out even if you don't get what you want." break;
		case 7: sText = "you have entered the aim of misfortune, captain! Visit a brothel and have some rest." break;
		case 8: sText = "you will get what you want, captain, but don't expect anything good from it. All what you've wanted so passionately, captain, will bring only bad things so you'd better change your plans away." break;
		case 9: sText = "I see that there is a sign on that face of yours, the sign of ultimate luck. You will get more than you're expecting to get, young man!" break;
		case 10: sText = "you need to evaluate your wish once again and decide. Do you really need it? Your fate is giving you a chance to rethink." break;
		case 11: sText = "it's rare luck, not everyday we've getting a chance to rethink. Take a rest for a few days, bright-eyed, think about things. Don't hurry to your death!" break;
		case 12: sText = "though all of your efforts won't give you the expected result, don't despair, young falcon, great luck is waiting for you in the most unexpected day, don't lose it!" break;
		case 13: sText = "your problem won't be solved in a positive way but you are a stubborn one and you'll get what you want but, perhaps, not from the place you've expected." break;
		case 14: sText = "you'd better forget about the business you are up to. You will never be lucky in this and if you'll be continuing in it than, perhaps, your closest people will be hurt or killed." break;
		case 15: sText = "there is an event which is waiting for you, captain, and it will completely change your life. Your recent concerns will lose all of their meaning to you after that." break;
		case 16: sText = "there is danger on your way to your dream, captain, and you must be really lucky if you will be able to get what you want without heavy losses. It's better to turn away and forget your unachievable dream. Or perhaps, this fate could be tricked if you lose in cards or dice right now..." break;
		case 17: sText = "I see a strong power in you like a rock and a light as bright as the north star which leads people. Good news is waiting for you!" break;
		case 18: sText = "a bad sign is rising on your way, fear the evil eye and keep loyal men close to you." break;
		case 19: sText = "a lucky event is rising on your way right behind your own back. Look for the good which is coming right to your hands and don't chase the unachievable." break;
	}
	return sText;
}

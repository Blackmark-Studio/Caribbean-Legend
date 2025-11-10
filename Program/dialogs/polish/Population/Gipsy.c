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
			dialog.text = "Ach, witaj, kochaniutki. Czego ci trzeba?";
			link.l1 = "Nic, jak sądzę.";
			link.l1.go = "exit";
			link.l2 = RandPhraseSimple("Chciałbym o coś zapytać.", "Potrzebuję pewnych informacji.");
			link.l2.go = "quests";//(перессылка в файл города)
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = LinkRandPhrase(
					"Kochanie, jeśli dasz mi parę złotych monet, zdradzę ci, co mówi o tobie przyszłość.",
					"Ej, marynarzu, nie śpiesz się tak! Może chcesz dowiedzieć się, co cię czeka?",
					"Hej! Daj mi garść pesos i trochę tytoniu, młody wilku morski, a opowiem ci, co los ci przygotował. (mruga) Chcesz poznać sekrety cygańskiej magii?"
				);
				link.l1 = "Może innym razem. Na razie muszę iść.";
				link.l1.go = "exit";
				// --> мангароса
				if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "gipsy" && !CheckAttribute(npchar, "quest.mangarosa"))
				{
					link.l5 = "Słuchaj, cygańska damo, wiem, że twoi ludzie znają się na miksturach i truciznach. Powiedziano mi, że ta roślina może cię zainteresować. Spójrz. Co o niej sądzisz?";

					link.l5.go = "mangarosa";
				}
				if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "gipsy_trade" && !CheckAttribute(npchar, "quest.mangarosa"))
				{
					link.l5 = "Hej, ciemnooka! Mam coś dla ciebie... oto mangarosa! Chcesz kupić trochę?";
					link.l5.go = "mangarosa_trade1";
				}
				// <-- мангароса
				link.l2 = "Chętnie. Czy możesz przepowiedzieć mi przyszłość?";
				link.l2.go = "guess";
				link.l3 = RandPhraseSimple("Chciałbym zadać ci pytanie.", "Szukam pewnych informacji.");
				link.l3.go = "quests";//(перессылка в файл города)
				npchar.quest.meeting = "1";
			}
			// --> Тёмные воды исцеления
			if (CheckAttribute(pchar, "questTemp.DWH_Start") && !CheckAttribute(pchar, "questTemp.DWH_gipsy") && npchar.city == "SentJons")
			{
				link.l6 = "Szukam Cyganki, która potrafi leczyć ludzi. Czy to przypadkiem nie ty?";
				link.l6.go = "dwh_ne_ta";
			}
			// <-- Тёмные воды исцеления
			if (!CheckAttribute(npchar, "quest.poison_price") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && rand(2) == 0)
			{
				link.l4 = "Hej, Cyganko, masz może trutkę na szczury? Na moim statku są już istną plagą!";
				link.l4.go = "get_poison_1";
			}
			NextDiag.TempNode = "First time";
		break;

//-------------------------------------------------гадание-------------------------------------------------
		case "guess":
			dialog.text = "Ależ oczywiście, przystojniaku. Daj mi trochę monet i pokaż prawą dłoń. Opowiem ci, co mówi przyszłość... i być może pomogę uniknąć katastrofy.  jeśli się pomylę – oddam złoto, przysięgam!";
			link.l1 = "Wiesz co? Coś mi mówi, że to własnie ten moment, gdy jakiś twój rodak próbuje wyłudzić ze mnie pieniądze... Nie. Zmieniam zdanie.";
			link.l1.go = "exit";
			link.l2 = "Ile pieniędzy chcesz?";
			link.l2.go = "guess_1";
		break;
		
		case "guess_1":
			dialog.text = "Ach drogi, tyle ile pozwala twój mieszek - i tyle, ile pragnie twoje serce. Im więcej pesos, tym dalej w przyszłość mogę spojrzeć!";
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
				dialog.text = "Ach, dziękuję za twoją hojność, mój mały sokole! Teraz posłuchaj: "+sTemp+" ";
				link.l1 = LinkRandPhrase("Heh! To bardzo interesujące. Wezmę to pod uwagę...","Naprawdę? Rozważę to...","O, naprawdę? Mówisz poważnie? Zapamiętam to...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Najbrzydsze i nieuniknione nieszczęście czeka na ciebie. Przeklnij szydercę! Niech ciemne chmury zgromadzą się nad tobą i niech kara cię dosięgnie!";
				link.l1 = "Ha! Myślałaś, że dam ci pieniądze, ty cygańska wiedźmo? Zejdź mi z drogi! Mam nadzieję, że inkwizycja cię dopadnie!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_2"://немного в везение или скрытность
			if (sti(pchar.money) >= 500)
			{
				AddMoneyToCharacter(pchar, -500);
				dialog.text = "Ach, dziękuję, mój słodki sokole! Teraz słuchaj: "+sTemp+" ";
				link.l1 = LinkRandPhrase(
					"Ciekawe... coś w tym chyba jest.",
					"Dziękuję. Z pewnością to przemyślę.",
					"Hm... coś mi to mówi. Zapamiętam.",
					"Brzmi prawdopodobnie. Dzięki."
				);
				link.l1.go = "exit";
				if (hrand(1) == 0) AddCharacterExpToSkill(pchar, "Fortune", 30+rand(10));//везение
				else AddCharacterExpToSkill(pchar, "Sneak", 30+rand(10));//скрытность
			}
			else
			{
				dialog.text = "Najbrzydsze i nieuniknione nieszczęście czeka na ciebie. Przeklinaj szydercę! Niech ciemne chmury zgromadzą się nad tobą i niech kara cię dosięgnie!";
				link.l1 = "Ha! Myślałaś, że dam ci pieniądze, ty cygańska wiedźmo? Zejdź mi z drogi! Mam nadzieję, że inkwizycja cię dopadnie!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_3"://здоровье + везение или скрытность, харизма
			if (sti(pchar.money) >= 1000)
			{
				AddMoneyToCharacter(pchar, -1000);
				dialog.text = "Ach, dzięki za twoje srebro, mój przystojny młody sokołu! Teraz słuchaj: "+sTemp+" ";
				link.l1 = LinkRandPhrase(
					"Ciekawe... coś w tym chyba jest.",
					"Dziękuję. Z pewnością to przemyślę.",
					"Hm... coś mi to mówi. Zapamiętam.",
					"Brzmi prawdopodobnie. Dzięki."
				);				
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 1);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				if (hrand(1) == 0) AddCharacterExpToSkill(pchar, "Fortune", 50+rand(20));//везение
				else AddCharacterExpToSkill(pchar, "Sneak", 50+rand(20));//скрытность
			}
			else
			{
				dialog.text = "Najbrzydsze i nieuniknione nieszczęście czeka na ciebie. Przekleństwo na szydercę! Niech ciemne chmury zbiorą się nad tobą i niech kara cię odnajdzie!";
				link.l1 = "Ha! Myślałaś, że dam ci pieniądze, ty cygańska wiedźmo? Zejdź mi z drogi! Mam nadzieję, że inkwizycja cię dopadnie!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_4"://умения в оружие, везение+скрытность, здоровье, харизма
			if (sti(pchar.money) >= 5000)
			{
				AddMoneyToCharacter(pchar, -5000);
				dialog.text = "Oh la la! Dziękuję za twoją hojność, mój przystojny młody sokołku! Teraz słuchaj: "+sTemp+" ";
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
				link.l1 = "Ha! Myślałaś, że dam ci pieniądze, ty cygańska wiedźmo? Zejdź mi z drogi! Mam nadzieję, że inkwizycja cię dopadnie!";
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
				dialog.text = LinkRandPhrase(
					"Och, nie jestem pewna, kochaniutki. Niedawno przyszedł tu facet, który szukał pomocy w zabijaniu szczurów... a tydzień później ktoś zatruł garnizon w forcie. Moi ludzie mieli potem niezłą przeprawę z żołnierzami... Przesłuchiwali nas przez dwa tygodnie, zanim znaleźli winnego. Okazało się, że to był szpieg.",
					"A skąd pewność, że to nie trucizna dla jakiegoś szlachcica? Może jesteś zbyt tchórzliwy, by stanąć z nim w pojedynku jak mężczyzna?",
					"Słyszałam, że ktoś otruł kupca w tawernie. Umarł w męczarniach — piana na ustach, siny jak bakłażan. Podobno zabrano mu cały towar. To nie była twoja sprawka... prawda?"
				);				
				link.l1 = "Ej, nie przesadzaj, cygańska dziewko! Nie zamierzam truć ludzi — to kobiecy sposób zabijania, nie w moim stylu. Na mężczyzn mam swój miecz, ale z tymi przeklętymi szczurami za cholerę nie mogę sobie poradzić!";
				link.l1.go = "get_poison_2";
				if (IsCharacterPerkOn(pchar, "Trustworthy")) Notification_Perk(true, "Trustworthy");
			}
			else
			{
				dialog.text = "Próbujesz mnie wrobić! Nie, panie, nie mam żadnej trucizny! Mam tylko rośliny i mikstury, ale żadnych trucizn!";
				link.l1 = "Dobrze, już dobrze! Obejdę się bez tego. Ale nie patrz na mnie tak, jakbyś już szykowała przekleństwo!";
				link.l1.go = "exit";
				Notification_Perk(false, "Trustworthy");
			}	
		break;
		
		case "get_poison_2" :
			dialog.text = "Och, jesteś taki odważny i męski... (szeptem) To będzie kosztowało " + sti(npchar.quest.poison_price) + " dublonów.";
			if (PCharDublonsTotal() >= sti(npchar.quest.poison_price))
			{				
				link.l1 = "Drogo... ale niech będzie. Oby to działało lepiej niż stare pułapki z beczek i sera.";
				link.l1.go = "get_poison_4";
			}
			else
			{
				link.l1 = "Pff! Za tyle to mógłbym kupić kota, który sam by je wyłapał. Nie dam ci aż tyle za jakąś butelkę podejrzanego płynu...";
				link.l1.go = "get_poison_3";
			}
		break;
		
		case "get_poison_3" :
			dialog.text = "W takim razie łap te szczury sam, bohaterze. A jeśli jeszcze raz przyjdziesz z takimi prośbami, zawołam straż.";
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
			dialog.text = LinkRandPhrase("Pokaż mi tę roślinę, kochanie... Hm... Przypuszczam, że mogę ją od ciebie kupić. Trzysta sztuk pesos, zgoda?","Pokaż mi to, przystojniaku... Heh... Cóż, mogę za to zapłacić dwieście pięćdziesiąt i ani peso więcej. ","Zobaczmy... O! Ciekawe znalezisko! Dwieście pesos! Umowa?")"";
			link.l1 = LinkRandPhrase("Oj, ciemnooka... myślisz, że jestem jakimś kretynem z prowincji?! Znam tę roślinę. To mangarosa...","Ha! To doskonały okaz mangarosa. Nie próbuj mnie oszukać, Cyganko!","Aha, i myślisz, że dam ci tę mangarosę za tak nędzną sumę...?");
			link.l1.go = "mangarosa_1";
		break;
		
		case "mangarosa_1":
			dialog.text = "Dobrze, dobrze, przystojniaku. Widzę, że coś tam o niej wiesz. Pięćdziesiąt dublonów – i roślina jest moja.";
			link.l1 = "Poczekaj... zanim ją oddam, chcę wiedzieć, do czego ją wykorzystujecie. Ludzie z twojego plemienia gotowi są płacić za nią fortunę! Dlaczego...?";
			link.l1.go = "mangarosa_2";
		break;
		
		case "mangarosa_2":
			// тут работает харизма
			if (sti(pchar.questTemp.Mangarosa.g_count) == 5 || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 10+hrand(25)+hrand(30, "1"))
			{
				dialog.text = "Hm... może nie zaszkodzi zdradzić ci uchylić rąbka tajemnicy. Ale bez odpowiedniej wiedzy i składników nic z nią nie zrobisz.";
				link.l1 = "A więc zamieniam się w słuch.";
				link.l1.go = "mangarosa_3";
			}
			else
			{
				dialog.text = LinkRandPhrase(
					"Złoto to jedno, ale sekrety to zupełnie inna cena, przyjacielu.",
					"Możemsz kupować, ale nie zdradzamy, co z tym robimy. To nasza tajemnica.",
					"Nie, młody wilku morski. Tego nie opowiadamy obcym. Albo pieniądze albo nie."
				) + " Pięćdziesiąt dublonów – to nasza oferta. Nikt ci nie zapłaci więcej";
				link.l1 = "Och, dobrze... Tak czy inaczej, mi to pasuje. Pięćdziesiąt dublonów. Weź to";
				link.l1.go = "mangarosa_trade";
				link.l2 = "Zrozum, nie chcę tego sprzedawać. Chcę tylko wiedzieć, do czego to służy. Podziel się ze mną swoją wiedzą, a dam ci to za darmo.";
				link.l2.go = "mangarosa_exit";
			}
		break;
		
		case "mangarosa_trade":
			RemoveItems(pchar, "cannabis7", 1);
			TakeNItems(pchar, "gold_dublon", 50);
			PlaySound("interface\important_item.wav");
			dialog.text = "Weź swoje monety, młody sokole. I jeszcze jedno, przynieś nam więcej tych roślin. Ale możemy je kupować tylko po jednej sztuce, bo nie nosimy przy sobie dużych sum. Wiesz, strażnicy nie ufają naszym i wręcz uwielbiają nas dręczyć...";
			link.l1 = "Dobrze. Jeśli znajdę więcej, to przyniosę.";
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
			dialog.text = LinkRandPhrase("Nie ma mowy! Jeśli nie chcesz tego sprzedać - to nie sprzedawaj. Niczego ci nie powiem!","Phi! Nie zdradzę naszych sekretów jakiemuś obcemu gadowi! (pluje) Nie chcesz tego sprzedać, co? Więc do diabła z tobą!","Przyjacielu, to nie dla twoich uszu. Naparwdę nie chcesz sprzedać tego za pięćdziesiąt dublonów? Dobrze. Idź więc i sprzedaj to jakiejś przekupce za dwieście pesos!");
			link.l1 = LinkRandPhrase(
				"Szkoda, że tak uparcie trzymasz język za zębami. Ale spokojnie - ktoś inny z twoich i tak mi to zdradzi. A roślinę dostanie w prezencie. Ha!",
				"Jesteś uparta jak osioł. Znajdę kogoś bardziej rozmownego. A ty obejdziesz się smakiem!",
				"Nie szkodzi. Twój oddech i tak śmierdzi czosnkiem! Dam tę roślinę komuś innemu z twojego plemienia - może będzie miał więcej rozumu."
			);
			link.l1.go = "exit";
			npchar.quest.mangarosa = "true";
			pchar.questTemp.Mangarosa.g_count = sti(pchar.questTemp.Mangarosa.g_count)+1;
		break;
		
		case "mangarosa_trade1":
			dialog.text = "Jeszcze pytasz, sokole?! Pewnie! Daj mi to.";
			link.l1 = "W takim razie poproszę pięćdziesiąt dublonów.";
			link.l1.go = "mangarosa_trade1_1";
			link.l2 = "Ups... Wygląda na to, że zapomniałem jej zabrać ze statku. Co za pech! No nic, do zobaczenia.";
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
			dialog.text = "Rozdrabniamy pąki w specjalny sposób, potem suszymy je, usuwamy nasiona i łodygi, potem mieszamy z tytoniem, nabijamy fajki i palimy tę mieszankę. I otrzymujemy... niezapomniany efekt. Coś jak odurzenie alkoholem, ale bez bólu głowy po nim. Jedna roślina wystarcza na dwie tuziny nabitych fajek.";
			link.l1 = "Już rozumiem! Dziękuję. Możesz mnie nauczyć tej tajnej techniki? Mogę ci to sowicie wynagrodzić...";
			link.l1.go = "mangarosa_4";
		break;
		
		case "mangarosa_4":
			dialog.text = "Młody sole, zaufaj mi, nie potrzebujesz tego. Nie mieszaj się, ta roślina cię zrujnuje. Otępia umysł i powoduje, że tyjesz. Nawet nie pytaj. Ale... widzę przed sobą odważnego człowieka, z mieczem, człowieka morza... może nawet kapitana?";
			link.l1 = "Masz rację.";
			link.l1.go = "mangarosa_5";
		break;
		
		case "mangarosa_5":
			dialog.text = "Słuchaj! Mangarosa może być wykorzystana do znacznie szlachetniejszych rzeczy i możesz ją uznać za użyteczną. Jedna z naszych uzdrowicielek zna wszystkie jej tajemnice. To ją musisz znaleźć\nDaj mi roślinę, a powiem ci jej imię i gdzie ją znaleźć. Natomiast przekonanie jej, by podzieliła się swoimi sekretami, to już twój problem.";
			link.l1 = "Dobrze. W takim razie weź roślinę i powiedz mi, jak znaleźć tą twoją cygańską czarownice...";
			link.l1.go = "mangarosa_6";
		break;
		
		case "mangarosa_6":
			RemoveItems(pchar, "cannabis7", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Jej imię to Amelia. Mieszka sama w małym domku pośród wydm niedaleko od morza, gdzieś na południowo-zachodnim wybrzeżu Hiszpańskiego Kontynentu, jak mówią mądrzy ludzie.";
			link.l1 = "O mój Boże... To nic mi nie mówi! Czy możesz być bardziej konkretna?";
			link.l1.go = "mangarosa_7";
		break;
		
		case "mangarosa_7":
			dialog.text = "Jesteś marynarzem, odważny sokole, a ja nie. Szukaj jej tam, gdzie powiedziałem. Jej dom jest naprawdę blisko wybrzeża. Jest w pobliżu zatoki na południowym zachodzie Hiszpańskiego Kontynentu - marynarze muszą to wiedzieć.";
			link.l1 = "Dobrze, spróbuję to znaleźć...";
			link.l1.go = "mangarosa_8";
		break;
		
		case "mangarosa_8":
			dialog.text = "Weź jej Mangarosę, bo inaczej nawet nie będzie chciała z tobą rozmawiać. I nie zapomnij przynieść dublonów. Nie myśl nawet, że nauczy cię za darmo!";
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
			dialog.text = NPCharSexPhrase(NPChar,"Słuchaj mnie, dzielny sokole. Może i jestem Cyganką, ale uwierz mi, nawet my odrzucamy otwartą przemoc! Proszę, schowaj swój miecz.","Słuchaj mnie, dzielny sokole, jako obywatel tego miasta proszę cię, byś schował swój miecz.");
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
		case 0: sText = "Jutro fortuna da ci znak – jeśli zagrasz w karty, możesz zgarnąć więcej, niż się spodziewasz."; break;
		case 1: sText = "Dobrze ci pójdzie w sprawach handlowych, kapitanie. Porty będą łaskawe, a sakiewka cięższa niż zwykle."; break;
		case 2: sText = "Coś złego czai się na wodach. Daj sobie trzy dni – potem wypłyń... jeśli odważysz się zaryzykować."; break;
		case 3: sText = "W nadchodzącej walce nie poradzisz sobie sam. Zaufaj tym, którzy stoją u twego boku."; break;
		case 4: sText = "Ktoś rzucił na ciebie zły urok. Zanim wyruszysz dalej – zajrzyj do kościoła i zapal świecę."; break;
		case 5: sText = "Przygotuj się na dotkliwą stratę, mój drogi... ale nie trać ducha! Masz wielu przyjaciół – i jeszcze wszystko przed tobą."; break;
		case 6: sText = "Morze odbierze ci coś ważnego... ale zachowasz to, co najważniejsze. Przetrwasz – nawet jeśli nie wygrasz."; break;
		case 7: sText = "Zła passa cię nie opuszcza, kapitanie! Odpocznij, wypij rum i znajdź ramiona, które ukoją twój los."; break;
		case 8: sText = "Dostaniesz to, czego tak bardzo pragniesz, kapitanie… ale nie spodziewaj się po tym niczego dobrego. To, za czym tak goniłeś, przyniesie ci tylko kłopoty. Może lepiej zawróć, póki czas."; break;
		case 9: sText = "Widzę na twojej twarzy znak wielkiego szczęścia... Los szykuje ci o wiele więcej dobra, niż się spodziewasz, młody człowieku."; break;
		case 10: sText = "Zastanów się raz jeszcze nad swoim aktualnym pragnieniem. Czy... oby na pewno tego chcesz? Los daje ci rzadką szansę, by zmienić kierunek."; break;
		case 11: sText = "Taka okazja nie zdarza się codziennie. Zrób przerwę, rozpal fajkę, pomyśl, zanim ruszysz dalej. Pośpiech prowadzi prosto do grobu."; break;
		case 12: sText = "Twoje wysiłki nie przyniosą oczekiwanego skutku… ale nie trać nadziei, sokole. Wielkie szczęście czeka cię wtedy, gdy najmniej się tego spodziewasz."; break;
		case 13: sText = "Twój problem nie znajdzie łatwego rozwiązania… ale jesteś uparty. I choć nie pójdzie po twojej myśli, osiągniesz swój cel – choć może nie tam, gdzie go szukałeś."; break;
		case 14: sText = "Rzuć to, czym się teraz zajmujesz. To przedsięwzięcie nie skończy się dobrze. Jeśli będziesz brnął dalej, to nie tylko ty możesz ucierpieć – ale i ci, których kochasz."; break;
		case 15: sText = "Zbliża się pewne wydarzenie, kapitanie, które odmieni całe twoje życie. Twoje obecne zmartwienia staną się wtedy bez znaczenia."; break;
		case 16: sText = "Na drodze do twojego marzenia czai się niebezpieczeństwo. Teoretycznie może ci się udać... ale tylko jeśli będziesz miał dużo szczęścia. Lepiej zawróć, zanim stracisz wszystko. Albo... Spróbuj oszukać przeznaczenie i przegrywaj dziś w kości."; break;
		case 17: sText = "Jest w tobie siła jak w skale i światło jak gwiazda polarna, która prowadzi innych. Dobre wieści już do ciebie zmierzają."; break;
		case 18: sText = "Na twojej drodze wschodzi zły znak. Strzeż się złego oka i trzymaj przy sobie lojalnych ludzi."; break;
		case 19: sText = "Szczęśliwy los już idzie za tobą krok w krok. Przestań gonić za jakimiś złudzeniami – to, co dobre, samo trafi ci w ręce."; break;
	}
	return sText;
}

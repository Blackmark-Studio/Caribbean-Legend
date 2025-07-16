// диалоги обитателей плантаций
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp, i, n;
	string sTemp;
	bool bOk;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "Czy potrzebujesz czegoś?";
			link.l1 = "Nie, nie robię.";
			link.l1.go = "exit";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// рабы
		case "plantation_slave":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Jestem tak zmęczony, padam na ryj...","Nie mogę tak dalej żyć!"),RandPhraseSimple("Ta praca mnie zabija.","Stróże chcą nas wszystkich zabić!"));				
			link.l1 = RandPhraseSimple("Jaka szkoda.","Przykro mi.");
			link.l1.go = "exit";				
		break;
		
		// рабы-пираты по пиратской линейке
		case "pirate_slave":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Słuchaj, odejdź!","Wywalaj stąd!"),RandPhraseSimple("Co chcesz?!","Zgredzie, wynoś się stąd!"));				
			link.l1 = RandPhraseSimple("Hm...","No tak...");
			link.l1.go = "exit";				
		break;
		
		// охрана - солдаты
		case "plantation_soldier":
            dialog.text = RandPhraseSimple(RandPhraseSimple("Idź zawracaj głowę szefowi plantacji","Nie rozpraszaj niewolników, kumplu."),RandPhraseSimple("Moim zadaniem jest zmotywować tych leniwych bękartów.","Cholera, znowu za gorąco, jak zawsze..."));
			link.l1 = RandPhraseSimple("Widzę...","Rzeczywiście...");
			link.l1.go = "exit";
		break;
		
		// охрана - протектор
		case "plantation_protector":
            if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				if (sti(pchar.nation) == PIRATE)
				{
					PlaySound("Voice\English\soldier_arest_1.wav");
    				dialog.text = RandPhraseSimple("Pirat?! Chwytajcie go!","On jest piratem! Atakujcie!");
					link.l1 = RandPhraseSimple("Pirat. I co z tego?","Heh, śmiało, spróbuj.");
					link.l1.go = "fight"; 
					break;
				}
				PlaySound("Voice\English\soldier_arest_2.wav");
				dialog.text = RandPhraseSimple("Haha, płyniesz pod flagą "+NationNameGenitive(sti(pchar.nation))+"! Myślę, że nasz komendant będzie zadowolony, aby porozmawiać z tobą!","Cóż-cóż, pachnie "+NationNameAblative(sti(pchar.nation))+" tutaj! Szpieg?! Czas, abyś porozmawiał z naszym komendantem.");
				link.l1 = RandPhraseSimple("Najpierw wyślę cię do piekła!","Czas, abyś porozmawiał z moim ostrzem!");
				link.l1.go = "fight"; 
			}
			else
			{
				if (GetNationRelation(sti(NPChar.nation), GetBaseHeroNation()) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
					if (sti(pchar.nation) == PIRATE)
					{
						PlaySound("Voice\English\soldier_arest_1.wav");
						dialog.text = RandPhraseSimple("Pirat?! Złapcie go!","On jest piratem! Atakuj!");
						link.l1 = RandPhraseSimple("Pirat!? Gdzie?","Heh, śmiało, spróbuj.");
						link.l1.go = "fight"; 
						break;
					}
					PlaySound("Voice\English\soldier_arest_4.wav");
					dialog.text = RandPhraseSimple("Kim jesteś i czego tu szukasz?","Stop! Jaki jest twój cel tutaj?");
					if (CheckNationLicence(HOLLAND))
					{
						link.l1 = "Chcę zobaczyć kierownika tego przybytku, aby omówić interesy. Mam licencję handlową.";
						link.l1.go = "Licence";
					}
					else
					{
						link.l1 = "Chcę zobaczyć szefa tego miejsca, aby omówić interesy.";
						if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < (10+rand(50)+rand(50))) link.l1.go = "PegYou";
						else link.l1.go = "NotPegYou";
					}
					if (IsCharacterPerkOn(pchar, "Trustworthy"))
					{
						link.l2 = "(Zaufany) Szanowni panowie, jestem tutaj dla uczciwej i wzajemnie korzystnej wymiany. Proszę, pozwólcie mi zobaczyć właściciela plantacji.";
						link.l2.go = "mtraxx_soldier_1";
						notification("Trustworthy", "Trustworthy");
					}
				}
				else
				{
					PlaySound("Voice\English\soldier_arest_4.wav");
					dialog.text = RandPhraseSimple("Kim jesteś i czego tu szukasz?","Stop! Jaki jest twój cel tutaj?");
					link.l1 = "Chcę zobaczyć szefa tego miejsca, aby omówić interesy.";
					link.l1.go = "NotPegYou";
				}
			}
		break;
		
		case "Licence":
			iTemp = GetDaysContinueNationLicence(HOLLAND);
			if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -12)
			{
				PlaySound("Voice\English\soldier_arest_2.wav");
				dialog.text = "Licencja? Poczekaj sekundę... Haha, zabawne! Wiem kim jesteś. Jesteś poszukiwany, ziomku! A nagroda za twoją głowę jest bardzooo duża! Złapcie go!";
				link.l1 = RandPhraseSimple("No cóż, w takim razie musisz spotkać się z moim ostrzem!","Spieprzaj.");
				link.l1.go = "fight";	
				break;
			}
			if (iTemp == -1)
			{
				PlaySound("Voice\English\soldier_arest_1.wav");
				dialog.text = "Zobaczmy... ha! Twoja licencja jest przeterminowana. Idź za mną, zaprowadzę cię do komendanta...";
				link.l1 = RandPhraseSimple("Gówno! Chyba nadszedł czas, abyś poznał moją szablę, kumplu.","Nie sądzę...");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			dialog.text = "Dobrze. Możesz wejść. Zachowuj się i nie przeszkadzaj niewolnikom.";
			link.l1 = "Nie martw się, przyjacielu.";
			link.l1.go = "plantation_exit";
		break;
		
		case "PegYou":
			PlaySound("Voice\English\soldier_arest_2.wav");
            dialog.text = "Biznes? Ha-ha! To jest śmieszne! Pachniesz "+NationNameAblative(sti(GetBaseHeroNation()))+" z tysiąca mil! To czas, abyś spotkał naszego komendanta.";
			link.l1 = "Nie, myślę, że nadszedł czas, abyś poznał moją szablę.";
			link.l1.go = "fight";
		break;
		
		case "NotPegYou":
            dialog.text = "Dobrze. Możesz wejść. Zachowaj się i nie przeszkadzaj niewolnikom.";
			link.l1 = "Nie martw się, przyjacielu.";
			link.l1.go = "plantation_exit";
		break;
		
		case "plantation_exit":
           DialogExit();
		   NextDiag.CurrentNode = "plantation_repeat";
		break;
		
		case "plantation_repeat":
            dialog.text = "Dalej, ruszaj się!";
			link.l1 = "...";
			link.l1.go = "plantation_exit";
		break;
		
		// управляющий в Маракайбо // Addon 2016-1 Jason
		case "Plantator":
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "plant_2") // belamour legendary edition 
			{
				dialog.text = "Jaki masz tu interes, panie?";
				link.l1 = TimeGreeting()+", panie. Mam dla ciebie propozycję biznesową. Mam niewolników na sprzedaż. "+FindRussianQtyString(sti(GetSquadronGoods(pchar,GOOD_SLAVES)))+". Zainteresowany?";
				link.l1.go = "mtraxx";
				break;
			}
            dialog.text = "Jaki masz tu interes, senorze?";
			link.l1 = "Po prostu spaceruję, chciałem powiedzieć cześć.";
			link.l1.go = "plantator_x";
		break;
		
		case "plantator_x":
           DialogExit();
		   npchar.dialog.currentnode = "plantator";
		break;
		
		case "plantator_1":
			bOk = GetSquadronGoods(pchar, GOOD_COFFEE) >= 500 || GetSquadronGoods(pchar, GOOD_CINNAMON) >= 500 || GetSquadronGoods(pchar, GOOD_COPRA) >= 500;
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup") && bOk) //пробуем выкупить Красавчика
			{
				dialog.text = "Znowu ty, senorze. Jak się masz?";
				link.l1 = "Mam do Ciebie propozycję biznesową. Produkujesz cukier i kakao. Chciałbym kupić twoje towary, ale nie za pieniądze, mogę zaoferować moje własne towary w zamian. Być może moglibyśmy zrobić targ?";
				link.l1.go = "mtraxx_5";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "plant_6" && bOk)
			{
				dialog.text = "Znowu ty, senorze. Jak się masz?";
				link.l1 = "Mam do Ciebie propozycję biznesową. Produkujesz cukier i kakao. Chciałbym kupić twoje towary, ale nie za pieniądze, mogę zaoferować moje własne towary w zamian. Być może moglibyśmy zrobić interes?";
				link.l1.go = "mtraxx_5";
				break;
			}
            dialog.text = "Ty znowu, senorze. Jak się masz?";
			link.l1 = "Dziękuję, u mnie dobrze.";
			link.l1.go = "plantator_1x";
		break;
		
		case "plantator_1x":
           DialogExit();
		   npchar.dialog.currentnode = "plantator_1";
		break;
		
		case "mtraxx":
			// belamour legendary edition возможность обмануть плантатора -->
			if(GetSquadronGoods(pchar, GOOD_SLAVES) >= 50 || CheckCharacterPerk(pchar, "Trustworthy") || ChangeCharacterHunterScore(Pchar, "spahunter", 0) <= -50)
			{
            dialog.text = "Muszę cię rozczarować, señor, ale w tej chwili nie potrzebujemy niewolników. Kapitan Eduardo de Losada już nas zaopatrzył w piratów, których pojmał podczas swojego ostatniego nalotu.";
			link.l1 = "Piraci tutaj? Jak możesz tutaj w ogóle spać?";
			link.l1.go = "mtraxx_1";
			}
			else
			{
				dialog.text = "Ach, zobaczmy więc... Kupię twoich niewolników. Po prostu wydaje mi się, że nie jesteś tym, za kogo się podajesz. Chodź ze mną do biura komendanta, drogi, a jeśli się mylę, w pełni pokryję twoje moralne koszty. A teraz przepraszam. Strażnik!";
				link.l1 = RandPhraseSimple("Śnij dalej, nie poddam się żywy!");
				link.l1.go = "mtraxx_fail";
			}
		break;
		
		case "mtraxx_fail":
            DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddQuestRecord("Roger_3", "27");
			sld = characterFromId("Mtr_plantation_boss");
			sld.lifeday = 0;
			Mtraxx_PlantPellyClear();
			Mtraxx_TerraxReset(3);
		break;
		// <-- legendary edition
		case "mtraxx_1":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(characterFromId("Fadey"));
            dialog.text = "Mamy dobrą straż, więc szanse na bunt są niskie. Ale masz rację w pewnym punkcie: ci łotry są okropnymi robotnikami. Nie kupiłbym ich, gdyby gubernator nie prosił mnie o okazanie szacunku dla don de Losada. Co więcej, on też nie zażądał za nich dużo.";
			link.l1 = "Rozumiem. Muszę więc popłynąć do Los-Teques... Panie, czy mogę pozwiedzać twoje plantacje? Może chciałbym kupić trochę twojej produkcji...";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "Czy jesteś kupcem?";
			link.l1 = "W pewnym stopniu, tak. Nie jestem profesjonalnym handlowcem, ale nigdy nie odwrócę się od obiecującej transakcji.";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "Ciekawe. Bardzo dobrze, masz moje pozwolenie. Wróć, jeśli będziesz miał jakieś pomysły.";
			link.l1 = "Dziękuję, panie. Myślę, że skorzystam.";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
           DialogExit();
		   NextDiag.CurrentNode = "plantator_1";
		   pchar.questTemp.Mtraxx = "plant_3";
		   AddQuestRecord("Roger_3", "5");
		   Mtraxx_PlantSetMaxRocur();
		break;
		
		case "mtraxx_5":
            dialog.text = "Dlaczego nie? Jakie towary oferujesz?";
			if (GetSquadronGoods(pchar, GOOD_COFFEE) >= 500)
			{
				link.l1 = "500 skrzynek kawy.";
				link.l1.go = "mtraxx_coffee";
			}
			if (GetSquadronGoods(pchar, GOOD_CINNAMON) >= 500)
			{
				link.l2 = "500 skrzynek wanilii.";
				link.l2.go = "mtraxx_cinnamon";
			}
			if (GetSquadronGoods(pchar, GOOD_COPRA) >= 500)
			{
				link.l3 = "500 skrzynek kopry.";
				link.l3.go = "mtraxx_copra";
			}
		break;
		
		case "mtraxx_coffee":
			i = hrand(3)+1;
			n = 5 - i;
			pchar.questTemp.Mtraxx.PlantGood.Cargo = 11;
			pchar.questTemp.Mtraxx.PlantGood.Sugar = i * 100;
			pchar.questTemp.Mtraxx.PlantGood.Cocoa = n * 100;
            dialog.text = "Pięćset skrzynek kawy? No-no... Zobaczmy... (liczy) Jestem gotów wymienić twoją kawę za "+sti(pchar.questTemp.Mtraxx.PlantGood.Sugar)+" worki cukru i "+sti(pchar.questTemp.Mtraxx.PlantGood.Cocoa)+"  skrzynki kakao. Umowa?";
			link.l1 = "Hmm... Liczyłem na lepsze warunki. Cóż, kto by się przejmował. Umowa stoi!";
			link.l1.go = "mtraxx_6";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup"))
			{
				link.l1 = "(Zaufany) Szanowny panie, pozwól mi zaprotestować! Przyniosłem ci towary najwyższej jakości. Znam wartość każdej jednostki, zarówno tego, co oferuję, jak i tego, co oferujesz w zamian. Zasługuję na nieco większy ładunek z twojej strony, a ten interes nadal będzie dla ciebie rentowny - doskonale o tym wiesz.";
				link.l1.go = "mtraxx_PlantVykup_2";
				notification("Trustworthy", "Trustworthy");
			}
		break;
		
		case "mtraxx_cinnamon":
			i = hrand(3)+1;
			n = 5 - i;
			pchar.questTemp.Mtraxx.PlantGood.Cargo = 19;
			pchar.questTemp.Mtraxx.PlantGood.Sugar = i * 106;
			pchar.questTemp.Mtraxx.PlantGood.Cocoa = n * 106;
            dialog.text = "Pięćset skrzynek wanilii? Cóż-cóż... Zobaczymy... (liczy) Jestem gotów wymienić twoją wanilię na "+sti(pchar.questTemp.Mtraxx.PlantGood.Sugar)+" worki cukru i "+sti(pchar.questTemp.Mtraxx.PlantGood.Cocoa)+"  skrzynki kakao. Umowa?";
			link.l1 = "Hmm... Liczyłem na lepsze warunki. Ale co tam. Umowa stoi!";
			link.l1.go = "mtraxx_6";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup"))
			{
				link.l1 = "(Zaufany) Szanowny panie, pozwól mi zaprotestować! Przywiozłem ci towary najwyższej jakości. Znam wartość każdej jednostki, zarówno tego, co oferuję, jak i tego, co oferujesz w zamian. Zasługuję na nieco większy ładunek z twojej strony, a ta transakcja nadal będzie dla ciebie opłacalna - doskonale o tym wiesz.";
				link.l1.go = "mtraxx_PlantVykup_2";
				notification("Trustworthy", "Trustworthy");
			}
		break;
		
		case "mtraxx_copra":
			i = hrand(3)+1;
			n = 5 - i;
			pchar.questTemp.Mtraxx.PlantGood.Cargo = 20;
			pchar.questTemp.Mtraxx.PlantGood.Sugar = i * 100;
			pchar.questTemp.Mtraxx.PlantGood.Cocoa = n * 100;
            dialog.text = "Pięćset skrzynek z koprą? Cóż, cóż... Zobaczmy... (liczy) Jestem gotowy wymienić twoją koprę na "+sti(pchar.questTemp.Mtraxx.PlantGood.Sugar)+" worki cukru i "+sti(pchar.questTemp.Mtraxx.PlantGood.Cocoa)+"  skrzynie kakao. Zgoda?";
			link.l1 = "Hmm... Liczyłem na lepsze warunki... Cóż, kto by się tym przejmował. Umowa stoi!";
			link.l1.go = "mtraxx_6";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup"))
			{
				link.l1 = "(Zaufany) Szanowny panie, pozwól mi zaprotestować! Przywiozłem ci towary najwyższej jakości. Znam wartość każdej jednostki, zarówno tego, co oferuję, jak i tego, co oferujesz w zamian. Zasługuję na nieco większy ładunek z twojej strony, a ta transakcja nadal będzie dla ciebie zyskowna - doskonale o tym wiesz.";
				link.l1.go = "mtraxx_PlantVykup_2";
				notification("Trustworthy", "Trustworthy");
			}
		break;
		
		case "mtraxx_6":
            dialog.text = "Wspaniale! To korzystna umowa dla nas obu! Kiedy przeprowadzimy wymianę?";
			link.l1 = "Najpierw powinienem przygotować towary. Myślę, że ty też. Zacznijmy wymianę jutro o czwartej po południu. Moi ludzie dostarczą skrzynki przed zachodem słońca.";
			link.l1.go = "mtraxx_7";
		break;
		
		
		case "mtraxx_7":
            dialog.text = "Umowa. W takim razie do zobaczenia jutro, senor!";
			link.l1 = "Do widzenia...";
			link.l1.go = "mtraxx_8";
		break;
		
		case "mtraxx_8":
            DialogExit();
			NextDiag.CurrentNode = "plantator_1";
			AddQuestRecord("Roger_3", "10");
			pchar.questTemp.Mtraxx = "plant_7";
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			pchar.quest.mtraxx_plant_goods.win_condition.l1 = "ExitFromLocation";
			pchar.quest.mtraxx_plant_goods.win_condition.l1.location = pchar.location;
			pchar.quest.mtraxx_plant_goods.function = "Mtraxx_PlantFindRocurDay";
		break;
		
		case "mtraxx_9":
            dialog.text = "To jest to, senorze. Jeśli kiedykolwiek będziesz potrzebował cukru lub kakao, proszę, przyjdź i zobacz mnie. Kiedykolwiek!";
			link.l1 = "Jeśli ten targ okaże się dochodowy - spotkamy się ponownie. Powinienem teraz iść, senorze.";
			link.l1.go = "mtraxx_10";
		break;
		
		case "mtraxx_10":
            dialog.text = "Żegnaj, señor!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantAfterTrading");
		break;
		
		case "mtraxx_soldier_1":
            dialog.text = "Nie wyglądasz na handlowca, obcokrajowcu. Pokaż swoją licencję.";
			link.l1 = "Daj mi spokój! Czy jakiś kawałek papieru decyduje, czy osoba może handlować, czy nie? Są zbyt drogie! Dopiero niedawno zacząłem handlować, ale już stało się to moją pasją! Przepuść mnie, a na pewno dobrze o was powiem właścicielowi.";
			link.l1.go = "mtraxx_10";
		break;
		
		case "mtraxx_soldier_2":
            dialog.text = "Masz srebrny język, ty sknera. Dobrze, idź. Ale nie zapomnij powiedzieć szefowi, że to my cię mu polecaliśmy.";
			link.l1 = "Oczywiście. Dziękuję.";
			link.l1.go = "plantation_exit";
		break;
		
		case "mtraxx_PlantVykup_2":
            dialog.text = "Jesteś dobrze zorientowany w obecnych cenach, Kapitanie! Masz wyraźny talent do negocjacji, nawet jeśli wyglądasz na początkującego. Dobrze, jeśli twoje towary są naprawdę pierwszorzędne, powinienem chyba dodać dla ciebie trochę ekstra.";
			link.l1 = "Oczywiście, pierwszorzędny, przysięgam! Jeszcze jedno, panie. Chciałbym coś od pana kupić.";
			link.l1.go = "mtraxx_PlantVykup_3";
		break;
		
		case "mtraxx_PlantVykup_3":
            dialog.text = "Oh? A co to może być?";
			link.l1 = "Ktoś, nie coś. Chciałbym kupić jednego z twoich niewolników jako osobistego służącego. Czy to możliwe?";
			link.l1.go = "mtraxx_PlantVykup_4";
		break;
		
		case "mtraxx_PlantVykup_4":
            dialog.text = "Nie ma problemu. Znajdziemy dla ciebie odpowiednią osobę.";
			link.l1 = "Interesuje mnie konkretny niewolnik. Ten o uroczym obliczu - kogoś, kogo nie byłbyś zawstydzony zabrać na oficjalne wydarzenia lub kto podawałby wino twoim gościom. Przedstawił się jako Jean Picard. Już się dogadaliśmy.";
			link.l1.go = "mtraxx_PlantVykup_5";
		break;
		
		case "mtraxx_PlantVykup_5":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 70)
			{
				dialog.text = "Tak, jest zapotrzebowanie na Jean Picard - nie tylko do podawania wina. Już skontaktował się ze mną wpływowy Anglik. Mężczyzna o imieniu, jak to było... Pattornson? Przekazał mi list.";
				link.l1 = "Ale ani Pattornson, ani jego klient jeszcze nie przyszli. Jestem gotów kupić od ciebie Jean tutaj i teraz. Nazwij swoją cenę - panie czekają!";
				link.l1.go = "mtraxx_PlantVykup_10";
				notification("Skill Check Passed", SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "Ach, rozumiem. Ale obawiam się, że muszę odmówić - Jean Picard nie jest na sprzedaż. Przykro mi, senorze.";
				link.l1 = "Oh? Dlaczego? Jestem gotów zapłacić hojnie. Po prostu podaj swoją cenę.";
				link.l1.go = "mtraxx_PlantVykup_6";
				notification("Skill Check Failed (70)", SKILL_COMMERCE);
			}
		break;
		
		case "mtraxx_PlantVykup_6":
            dialog.text = "Bezcenny. On już ma kupca. Obiecałem go komuś innemu. Nie ma więcej do powiedzenia. Wróćmy do naszej początkowej umowy i zakończmy handel.";
			link.l1 = "Hmm, jak sobie życzysz, senor.";
			link.l1.go = "mtraxx_PlantVykup_7";
		break;
		
		case "mtraxx_PlantVykup_7":
            dialog.text = "Wspaniale! To korzystna umowa dla nas obu! Kiedy przeprowadzimy wymianę?";
			link.l1 = "Najpierw powinienem przygotować towary. Ty też tak myślę. Zacznijmy wymianę jutro o czwartej po południu. Moi ludzie dostarczą skrzynki przed zachodem słońca.";
			link.l1.go = "mtraxx_PlantVykup_8";
		break;
		
		
		case "mtraxx_PlantVykup_8":
            dialog.text = "Zgoda. Cóż, do zobaczenia jutro, senor!";
			link.l1 = "Do widzenia...";
			link.l1.go = "mtraxx_PlantVykup_9";
		break;
		
		case "mtraxx_PlantVykup_9":
            DialogExit();
			NextDiag.CurrentNode = "plantator_1";
			pchar.questTemp.mtraxx_PlantVykup2 = true;
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantVykup");
			DoFunctionReloadToLocation("Shore37", "goto", "goto6", "Mtraxx_PlantPlantVykup_1");
		break;
		
		case "mtraxx_PlantVykup_10":
            dialog.text = "Jak sobie życzysz, senorze. Ale zrozum, cena jest wysoka: pięćset dublonów.";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "To nie problem - proszę. Dobry osobisty sługa jest więcej wart niż zwykły niewolnik, jak dobrze wiesz.";
				link.l1.go = "mtraxx_PlantVykup_11";
			}
			else
			{
				link.l2 = "Dość wysoka cena, którą ustawiłeś, panie. Ale jestem bardzo zainteresowany tym niewolnikiem. Zaczekaj tutaj. Jeśli Pattornson się pojawi, powiedz mu, że Picard już został sprzedany - ha-ha-ha!";
				link.l2.go = "mtraxx_PlantVykup_13";
			}
		break;
		
		case "mtraxx_PlantVykup_11":
            dialog.text = "Masz rację. Zajmę się przygotowaniami. Picard będzie na ciebie czekał na zewnątrz.";
			link.l1 = "...";
			link.l1.go = "mtraxx_PlantVykup_12";
			RemoveDublonsFromPCharTotal(500);
		break;
		
		case "mtraxx_PlantVykup_12":
            DialogExit();
			NextDiag.CurrentNode = "plantator_1";
			pchar.questTemp.mtraxx_PlantVykup3 = true;
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantVykup");
			DoFunctionReloadToLocation("Maracaibo_ExitTown", "rld", "loc17", "Mtraxx_PlantPlantVykup_2");
		break;
		
		case "mtraxx_PlantVykup_13":
            dialog.text = "Jeśli przyjdzie z pełną kwotą, wątpię, aby go odrzucił. Więc pospiesz się, Kapitanie.";
			link.l1 = "Wrócę wkrótce.";
			link.l1.go = "mtraxx_PlantVykup_14";
		break;
		
		case "mtraxx_PlantVykup_14":
            DialogExit();
			NextDiag.CurrentNode = "mtraxx_PlantVykup_15";
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantVykup");
		break;
		
		case "mtraxx_PlantVykup_15":
            dialog.text = "Czy przyniosłeś złoto dla Jean Picard, Kapitanie? Czas nagli.";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Doskonale o tym wiem. Więc oto, weź swoje złoto, i daj mi mojego nowego służącego do domu.";
				link.l1.go = "mtraxx_PlantVykup_16";
			}
			else
			{
				link.l2 = "Wciąż na to zbieram - to ty ustawiłeś taką wysoką cenę, señor.";
				link.l2.go = "mtraxx_PlantVykup_14";
			}
		break;
		
		case "mtraxx_PlantVykup_16":
            dialog.text = "Nigdy nie widziałem, żeby ktoś wydał tyle na zdobycie służącego. Ale patrząc na to, jak jesteś dobrze ubrany, musisz być przyzwyczajony do takich wielkich zakupów. Poinformuję moich ludzi, a Picard będzie na ciebie czekał przy wyjściu.";
			link.l1 = "...";
			link.l1.go = "mtraxx_PlantVykup_12";
			RemoveDublonsFromPCharTotal(500);
		break;
	}
} 

void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	bool bOk1, bOk2;
	
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
			dialog.text = "Czego wam trzeba?";
			link.l1 = "Nic.";
			link.l1.go = "exit";
		break;
		
		case "OZ_Kuznets_1":
			//PlaySound("VOICE\Russian\Master_05.wav");
			dialog.text = "Czego chcieliście, "+GetAddress_Form(NPChar)+"? Wybaczcie, ale nowych zamówień nie przyjmuję. Mam po prostu... dużo pracy...";
			link.l1 = "Tak? Mówią, że niedawno przegraliście w karty coś bardzo cennego, czy to prawda?";
			link.l1.go = "OZ_Kuznets_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Kuznets_2":
			dialog.text = "Jeśli przyszliście, żeby się natrząsać, ustawcie się w kolejce - chętnych i bez was nie brakuje. Tylko że nikt nie zaproponował mi pomocy. Mój los wisi na włosku i całkowicie zależy od Javiera Castillo, a ludziom tylko w głowie pośmiać się z mojego nieszczęścia.";
			link.l1 = "Nie należę do tych, którzy śmieją się z cudzych nieszczęść. Opowiedzcie, jak to było. Może będę mógł"+GetSexPhrase("","a")+" wam pomóc.";
			link.l1.go = "OZ_Kuznets_3";
			link.l2 = "Pomoc? A niby dlaczego ktoś miałby wam jej udzielać? Ja na pewno nie zamierzam"+GetSexPhrase("","a")+". Sami jesteście kowalem swojego szczęścia... i nieszczęścia też. Więc przestańcie udawać ofiarę - po prostu przyjmijcie konsekwencje swoich czynów, są aż nadto oczywiste.";
			link.l2.go = "OZ_Kuznets_NoAgree";
		break;
		
		case "OZ_Kuznets_NoAgree":
			DialogExit();
			AddDialogExitQuestFunction("OZ_Kuznets_NoAgree");
		break;
		
		case "OZ_Kuznets_3":
			dialog.text = "Ten wieczór nie miał być pechowy. Wpadłem tylko do tawerny, żeby wypić kufel rumu po tym, jak sam admirał Eugenio de la Torre złożył u mnie duże zamówienie. Ale, porządnie podchmielony, usiadłem do stołu, żeby zagrać w karty. Wtedy właśnie wziął się za mnie Javier\nNa początku szczęście było po mojej stronie - nawet wygrałem niezłą sumę, ale gdy tylko uwierzyłem we własne szczęście, sytuacja gwałtownie się odwróciła. Javier wciąż dolewał rum do mojego kufla, a ja przegrywałem raz za razem: najpierw poszła gotówka, potem pieniądze odłożone na materiały, a potem wszystkie oszczędności\nKiedy uświadomiłem sobie, ile już straciłem, na odwrót było za późno. Ogarnęła mnie jedna myśl - odegrać się za wszelką cenę. Postawiłem więc na szali moją księgę. Ten łotr Javier wycenił ją na zaledwie pięć tysięcy peso\nOczywiście warta jest znacznie więcej, ale byłem tak zaślepiony hazardem, że się zgodziłem. A potem... myślę, że już wiecie. Przegrałem. Nigdy mi się coś takiego nie zdarzyło. Wydaje mi się, że ten drań czymś mnie odurzył.";
			link.l1 = "I w czymże, jeśli wolno spytać, mogę wam pomóc? To wy sami zasiedliście do stołu, sami postawiliście na szali swój majątek i sami wszystko przegraliście. Teraz po prostu nie chcecie pogodzić się z konsekwencjami? I co tak cennego ma ta księga, nad którą tak ubolewacie?";
			link.l1.go = "OZ_Kuznets_4";
		break;
		
		case "OZ_Kuznets_4":
			dialog.text = "Ta księga to najcenniejsza rzecz, jaką miałem. Skrywa sekrety przekazywane od mistrza do ucznia przez całe wieki. To serce mojej kuźni, dusza mojego rzemiosła. Z przegraną już się pogodziłem, "+GetAddress_Form(NPChar)+", ale jak mam pogodzić się z utratą księgi? Zaproponowałem Javierowi wykup – pięć tysięcy peso\nByłem gotów wpakować się w długi, byle ją odzyskać. A wiecie, co powiedział? Że chce za nią sto tysięcy! Sto, "+GetAddress_Form(NPChar)+"! Takich pieniędzy nie mam. A na obniżkę ceny ani na płatność w ratach nie chce się zgodzić. Błagałem go... ale tylko się ze mnie śmiał. Widzę, że jesteście "+GetSexPhrase("człowiekiem rezolutnym, marynarzem... a może nawet kapitanem. I broń u was nie dla ozdoby wisi","niezwykłą kobietą, która zapewne potrafi znaleźć podejście do każdego mężczyzny")+"\nProszę, porozmawiajcie z Javierem. Może was posłucha i zgodzi się na odroczenie spłaty długu. Bez tej księgi... moje życie nie ma sensu. W zamian zawsze będę mógł sprzedać wam materiały dobrej jakości w dobrej cenie, gdy tylko stanę na nogi, a może uda się nawet wykonać dla was coś wyjątkowego, kapitanie.";
			link.l1 = "Cóż, porozmawiać to żadna sztuka. Zobaczymy, co z tego wyjdzie. Ale najpierw pozwólcie, że się przedstawię: nazywam się "+GetFullName(pchar)+", jestem kapitanem własnego statku.";
			link.l1.go = "OZ_Kuznets_5";
		break;
		
		case "OZ_Kuznets_5":
			dialog.text = ""+GetSexPhrase("A ja Sebastian Cordoba...","Kobieta – kapitan własnego statku? Słyszałem o takich, ale spotkać osobiście i porozmawiać – jeszcze mi się nie zdarzyło.")+" Miło mi, kapitanie "+pchar.lastname+". I dziękuję. W naszych czasach łatwiej znaleźć tych, którzy szydzą z cudzego nieszczęścia, niż tych, którzy są gotowi pomóc. Wiecie, jeśli moja księga wróci, przysięgam: już nigdy nie zagram w hazard.";
			link.l1 = "Na razie nie ma za co dziękować. Najpierw załatwię swoje sprawy, a potem, jeśli starczy czasu, porozmawiam z Javierem.";
			link.l1.go = "OZ_Kuznets_6";
		break;
		
		case "OZ_Kuznets_6":
			dialog.text = "Obawiam się, że możecie się spóźnić. Javier okazał się znacznie sprytniejszy, niż myślałem\nJuż znalazł kupca na księgę – to Étienne Renoir, francuski mistrz od broni. Jeśli admirał się dowie, że z mojej winy taka wartość trafiła w ręce Francuzów... stracę głowę. Więzienie byłoby jeszcze łagodną karą.";
			link.l1 = "Hm... Dobrze. Zajmę się waszym problemem natychmiast.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_repeat";
			AddDialogExitQuestFunction("OZ_Kuznets_Agree");
		break;
		
		case "OZ_Kuznets_repeat":
			dialog.text = "Kapitanie "+ pchar.lastname +"! Rozmawialiście z Javierem? Jakie wieści?";
			link.l1 = "Jeszcze nie, ale właśnie zmierzam do tawerny.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_repeat";
			if (CheckCharacterItem(PChar, "OZ_book"))
			{
				link.l1 = "Porozmawia"+GetSexPhrase("łem","łam")+". I to z powodzeniem. Javier pospiesznie udał się na tamten świat, ale wcześniej zdążył oddać waszą księgę. Proszę, trzymajcie.";
				link.l1.go = "OZ_Kuznets_11";
				DelLandQuestMark(npchar);
			}
		break;
		
		case "OZ_Kuznets_11":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", nawet nie wyobrażacie sobie, co to dla mnie znaczy! Dzięki wam zdołam wykonać wszystkie zamówienia, nawet pracę dla samego admirała! Pieniędzy, niestety, nie mam, ale przygotowałem dla was nagrodę\nProszę, weźcie ten kirys – wykonałem go dla pewnego dona, ale jestem pewien, że może trochę poczekać. Mam też pewne materiały; przydadzą wam się, jeśli zechcecie coś zrobić własnymi rękami.";
			link.l1 = "Dziękuję, "+npchar.name+", to bardzo hojny gest!";
			link.l1.go = "OZ_Kuznets_12";
			TakeItemFromCharacter(pchar, "OZ_book");
		break;
		
		case "OZ_Kuznets_12":
			dialog.text = "I jeszcze – zaglądajcie do mnie, gdy będziecie potrzebować materiałów. Dostawy mam raz w miesiącu, więc zawsze znajdzie się dla was coś pożytecznego - i to w dobrej cenie. Dotrzymuję obietnic.";
			link.l1 = "Na pewno zajrzę! No to, "+npchar.name+", bądźcie zdrowi. A ja pójdę, obowiązki wzywają.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Kuznets_Nagrada");
			GiveItem2Character(PChar, "cirass3");
			AddItems(PChar, "jewelry13", 10);
			AddItems(PChar, "jewelry12", 5);
			AddItems(PChar, "jewelry10", 5);
			AddItems(PChar, "jewelry11", 2);
			AddQuestRecordInfo("Useful_Acquaintances", "7");
		break;
		
		case "OZ_Kuznets_Fail":
			dialog.text = "Kapitanie "+ pchar.lastname +"! Rozmawialiście z Javierem? Jakie wieści?";
			link.l1 = "Widzicie... księga była w moich rękach. Ale... okoliczności ułożyły się tak, że została sprzedana.";
			link.l1.go = "OZ_Kuznets_Fail_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Kuznets_Fail_2":
			dialog.text = "Co?! Wy... sprzedaliście ją?! Moją księgę?!";
			link.l1 = "Księgę, którą przegraliście w karty. Sprzedano ją temu Francuzowi, któremu obiecał ją Javier.";
			link.l1.go = "OZ_Kuznets_Fail_3";
		break;
		
		case "OZ_Kuznets_Fail_3":
			dialog.text = "Ale... to już mój koniec. Księga jest u Francuzów, zlecenie admirała nie zostanie wykonane... moje życie jest zrujnowane... Ja... jestem zgubiony!";
			link.l1 = "Sami wpędziliście się w ten róg. Myślę, że posłuży wam to za dobrą lekcję. Żegnajcie.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Kuznets_Fail");
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
		break;
		
		case "OZ_Shuler_1":
			PlaySound("Voice\english\tavern\Igroki v Tavernah-01.wav"); 
			dialog.text = "Hej, "+GetSexPhrase("marynarzu","ślicznotko")+", nie chcesz spróbować szczęścia w kartach? Siadaj, stawki u nas łagodne... przynajmniej dla nowicjuszy.";
			link.l1 = "Wydaje mi się, że to właśnie ciebie szukam. Właśnie tak wabiłeś Sebastiana, zanim obedrzeć go do nitki? Jestem tu, żeby zwrócić mu jego księgę.";
			link.l1.go = "OZ_Shuler_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Shuler_2":
			dialog.text = "No dobrze. Daj sto tysięcy - i możesz ją zabrać. Z tej księgi nie mam żadnego pożytku, szczypiec od młotka i tak nie odróżnię.";
			link.l1 = "Dam ci pięć tysięcy - sam ustaliłeś tę cenę, kiedy ograłeś kowala.";
			link.l1.go = "OZ_Shuler_3";
		break;
		
		case "OZ_Shuler_3":
			dialog.text = "Ha! Masz mnie za głupca? Doskonale znam prawdziwą wartość tej księgi. Sto tysięcy i ani monety mniej. Albo trafi do Francuzów - u nich z pieniędzmi nie ma problemu.";
			link.l1 = "Myślisz, że władze przymkną oko na to, że zamierzasz sprzedać Francuzom hiszpańskie rysunki? Admirał będzie wściekły, kiedy się o tym dowie.";
			link.l1.go = "OZ_Shuler_4";
		break;
		
		case "OZ_Shuler_4":
			dialog.text = "Och, daj spokój. Władze mają gdzieś jakąś tam książeczkę, mają dość innych kłopotów. A admirał? Owszem, nienawidzi Francuzów całym sercem, ale czekać na niego nie zamierzam - z taką kupą pieniędzy będę mile widziany w każdej kolonii Nowego Świata.";
			link.l1 = "To ustalmy tak: dostaniesz swoje pieniądze, ale nie od razu. Kowal będzie spłacać dług częściami, a księga dziś wraca do niego pod zastaw mojego kapitańskiego honoru. Dla ciebie nic się nie zmienia - i tak się rozliczy, a ty nie stracisz ani peso.";
			link.l1.go = "OZ_Shuler_5";
		break;
		
		case "OZ_Shuler_5":
			dialog.text = "Chyba mnie nie słyszysz. Powiedziałem jasno - pieniądze są mi potrzebne teraz. Nie za tydzień, nie za miesiąc, ani kiedy tam kowal je uzbiera, tylko teraz. Zamierzam wynieść się z tej nieszczęsnej wyspy jak najszybciej. Więc albo cała suma ląduje u mnie w rękach teraz, albo księga idzie do Francuzów, a swój kapitański honor będziesz zastawiać u admirałowskiego kata.";
			if (sti(pchar.Money) >= 100000 && GetSummonSkillFromName(pchar, SKILL_SNEAK) >= 30)
			{
				link.l1 = "Zróbmy tak: zagramy. Moje sto tysięcy przeciwko księdze. Jeśli wygrasz, opuścisz wyspę jako bogacz. Jeśli przegrasz - biorę księgę. Czy grasz tylko z tymi, którzy pierwszy raz widzą karty?";
				link.l1.go = "OZ_Shuler_6";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "OZ_Shuler_6_No_Money";
				AddDialogExitQuestFunction("OZ_GameCards_Fail");
			}
		break;
		
		case "OZ_Shuler_6_No_Money":
			DialogExit();
			notification("Niewystarczająco pieniędzy (100 000)", "Money");
			LAi_CharacterDisableDialog(npchar);
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) >= 30)
			{
			notification("Test zaliczony (30)", SKILL_SNEAK);
			}
			else
			{
			notification("Niewystarczająco rozwinięta umiejętność (30)", SKILL_SNEAK);
			}
		break;
		
		case "OZ_Shuler_6":
			dialog.text = "Ha! Nie muszę zostawać bogaczem - już nim jestem! Po co mam ryzykować coś, co przyniesie mi kupę pieniędzy?";
			link.l1 = "O proszę, sam Javier Castillo boi się zagrać? A myślał"+GetSexPhrase("em","am")+", że jesteś wyjadaczem, a nie tylko szulerem żerującym na pijanych prostakach.";
			link.l1.go = "OZ_Shuler_7";
			notification("Test zaliczony (100 000)", "Money");
			notification("Test zaliczony (30)", SKILL_SNEAK);
		break;
		
		case "OZ_Shuler_7":
			dialog.text = "Nie boję się, po prostu nie widzę sensu siadać do stołu, kiedy już mam wszystko, czego trzeba.";
			link.l1 = "Daj spokój, widzę jak cię aż nosi na samą myśl o grze z kimś, kto nie trzyma kart pierwszy raz w życiu. Zgadnę: tak ci spieszno stąd uciec, bo ci wstyd? Wszyscy już zrozumieli, że kogoś silniejszego niż pijany prostak nie pokonasz?";
			link.l1.go = "OZ_Shuler_8";
		break;
		
		case "OZ_Shuler_8":
			dialog.text = "Jak ty śmiesz? Ogrywałem takich ludzi, którzy z tobą do jednego stołu by nie zasiedli! Zdarzały się pule takie, że można by kupić po statku i po takim bezczelnym kapitanie dla każdego! Gramy. Po pięć tysięcy za kartę, każdy ma po sto tysięcy, komu skończą się pieniądze - ten przegrywa. Zobaczymy, kto kogo.";
			link.l1 = "Mniej gadania, więcej grania. Rozdawaj.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_GameCards");
		break;
		
		case "OZ_Shuler_Win_1":
			dialog.text = "Diabli! To niemożliwe...";
			link.l1 = "Co, już nie tak wesoło, kiedy wygrywa ktoś inny?";
			link.l1.go = "OZ_Shuler_Win_2";
		break;
		
		case "OZ_Shuler_Win_2":
			dialog.text = "Ty oszuście! Myślisz, że nic nie widziałem? Prędzej potnę cię na kawałki, niż dam się oskubać!";
			link.l1 = "Oszust? Ha-ha! Wygląda na to, że po prostu nie umiesz przegrywać, przyjacielu. Ale skoro tak ci śpieszno na tamten świat - chętnie pomogę. Do broni!";
			link.l1.go = "exit";
			pchar.questTemp.OZ_Draka = true;
			AddDialogExitQuestFunction("OZ_GameCards_Duel");
		break;
		
		case "OZ_Shuler_Lose_1":
			dialog.text = "Ha! No i jak, "+GetSexPhrase("kolego","ślicznotko")+", jak to jest czuć się ogołocon"+GetSexPhrase("ym","ą")+"? Mówią, że bezczelność to drugie szczęście, ale nie w twoim przypadku.";
			link.l1 = "Nie ciesz się. Po prostu miałeś szczęście.";
			link.l1.go = "OZ_Shuler_Lose_2";
		break;
		
		case "OZ_Shuler_Lose_2":
			dialog.text = "Przegrani zawsze tak mówią. Dobrze, zagra"+GetSexPhrase("łeś","łaś")+" - przegra"+GetSexPhrase("łeś","łaś")+", nie obrażaj się. Jeśli znajdziesz jeszcze sto tysięcy, możesz spróbować szczęścia znowu... Ale wątpię, by wynik się zmienił...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_GameCards_Lose");
			AddLandQuestMark(characterFromId("PortSpein_Tavern"), "questmarkmain");
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Felip_1":
			dialog.text = "Witajcie, "+GetAddress_Form(NPChar)+". Czym zawdzięczam waszą wizytę?";
			link.l1 = "Pozdrawiam. Jestem kapitan "+GetFullName(pchar)+", chciał"+GetSexPhrase("em","am")+" porozmawiać z wami o Javierze Castillo.";
			link.l1.go = "OZ_Felip_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Felip_2":
			dialog.text = "Hm... Jeśli ten spryciarz zadłużył się także u was, obawiam się, że będziecie musieli ustawić się w długiej kolejce. Javier nigdy nie spieszył się ze spłatą pożyczek. Ale jeśli kiedykolwiek dorwie pieniądze, w pierwszej kolejności spłaci mnie - już zadbałem, by nie miał innego wyboru.";
			link.l1 = "Na szczęście nie jestem jego wierzycielem. Ile jest wam winien? I jakie dokładnie kroki podjęliście?";
			link.l1.go = "OZ_Felip_3";
		break;
		
		case "OZ_Felip_3":
			dialog.text = "Całkowita kwota jego długu to sto pięćdziesiąt tysięcy peso. Spłacił zaledwie dziesięć tysięcy, chyba uznając, że na tym można poprzestać. Szybko jednak dałem mu do zrozumienia, że się myli. Moi ludzie wycisnęli z niego kolejne dwadzieścia tysięcy. Resztę ma oddać w ciągu tygodnia i termin właśnie się kończy. Na szczęście słyszałem, że wkrótce dostanie niezłą sumę ze sprzedaży jakiejś księgi.";
			link.l1 = "Naprawdę sądzicie, że zamierza oddać wam pieniądze? Nie sądzę, by warto było na to liczyć. Javier nawet nie ukrywa, że gdy tylko dostanie pieniądze, natychmiast stąd ucieknie.";
			link.l1.go = "OZ_Felip_4";
		break;
		
		case "OZ_Felip_4":
			dialog.text = "Wiem o tym, kapitanie. Zapewniam was, już zadbałem o to, by nie zdołał uciec, nie rozliczywszy się ze mną.";
			link.l1 = "Widzę, że kontrolujecie sytuację. Jednak, jak pokazuje praktyka, przezorność nigdy nie zaszkodzi. Wiecie, jestem specjalist"+GetSexPhrase("ą","ką")+" od windykacji. Jeśli pozwolicie mi działać w waszym imieniu, zdołam odzyskać wasze pieniądze.";
			link.l1.go = "OZ_Felip_5";
		break;
		
		case "OZ_Felip_5":
			dialog.text = "Niestety, kapitanie, odzyskiwanie tego długu kosztuje mnie już zbyt wiele i nie mogę pozwolić sobie na opłacanie jeszcze waszych usług...";
			link.l1 = ""+UpperFirst(GetAddress_Form(NPChar))+", o to nie musicie się martwić. W tej sprawie mam własny interes, dlatego pomogę wam nieodpłatnie.";
			link.l1.go = "OZ_Felip_6";
		break;
		
		case "OZ_Felip_6":
			dialog.text = "Czy mogę wiedzieć, na czym dokładnie polega wasz interes?";
			link.l1 = "Powiedzmy tak: niektórych jego sztuczek przy kartach nie mogę zostawić bez kary.";
			link.l1.go = "OZ_Felip_7";
		break;
		
		case "OZ_Felip_7":
			dialog.text = "Skoro mnie to nic nie będzie kosztować, nie widzę powodu, by odmawiać. Tylko jedno, kapitanie, proszę was, nie posuwajcie się za daleko. Jeśli ten łajdak pójdzie do piachu, zanim odda dług, nie będę miał z tego żadnego pożytku.";
			link.l1 = "Nie martwcie się, Felipe, będę działa"+GetSexPhrase("ł","ła")+" ostrożnie.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Felip_again";
			AddDialogExitQuestFunction("OZ_Felip_2");
			pchar.questTemp.OZ_Dolg = true;
		break;
		
		case "OZ_Felip_again":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+"! Czy to możliwe, że uwinęliście się tak szybko?";
			link.l1 = "Niestety, jeszcze nie. Ale nad tym pracuję.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Felip_again";
		break;
		
		case "OZ_Shuler_11":
			if (CheckAttribute(npchar, "quest.OZ_Shuler_Lose"))
			{
				dialog.text = "A, "+GetSexPhrase("kapitanie pyszałku","ślicznotko")+"! Znowu ty? Co, chcesz przegrać jeszcze parę tysięcy?";
			}
			else
			{
				dialog.text = "Znowu ty? Przecież jasno powiedziałem: pieniądze na stół - albo spadaj.";
			}
			link.l1 = "Zmień ton, Javier. I wyciągnij trzos - nie jestem tu bez powodu. Długu wobec Felipe Alarcona chyba nie zapomniałeś? Teraz reprezentuję jego interesy. Więc wybieraj: albo oddajesz dług natychmiast, albo poszukam pieniędzy w twoich kieszeniach po tym, jak pójdziesz do piachu.";
			link.l1.go = "OZ_Shuler_12";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Shuler_12":
			dialog.text = "Cholera by cię wzięła! Mam tu transakcję, nie widzisz? Wróć za parę godzin - wtedy pogadamy.";
			link.l1 = "Chyba mnie nie słyszałeś. Przecież dałe"+GetSexPhrase("m","am")+" jasno do zrozumienia - pieniądze są mi potrzebne teraz. Nie za tydzień, nie za miesiąc ani kiedy tam je uskrobiesz, tylko teraz. Sto dwadzieścia tysięcy peso i ani monety mniej. Księgę przyjmę jako pięć tysięcy.";
			link.l1.go = "OZ_Shuler_13";
		break;
		
		case "OZ_Shuler_13":
			dialog.text = ""+GetSexPhrase("Brudny łajdaku","A ty, zołzo")+"! Jeśli myślisz, że łatwo się mnie pozbędziesz - to największy błąd w twoim nędznym życiu.";
			link.l1 = "Zobaczymy.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Shuler_Bitva");
		break;
		
		case "OZ_Frantsuz_1":
			//PlaySound("VOICE\Russian\tra_quest_1.wav");
			if (CheckAttribute(pchar, "questTemp.OZ_Draka"))
			{
				dialog.text = "Co za widowisko... Przyznaję, "+GetAddress_Form(NPChar)+", sprawiliście mi przyjemność. Doskonale władajecie klingą. Pozwólcie, że się przedstawię - "+GetFullName(npchar)+". A ten nieszczęśnik, jak rozumiem, to Javier Castillo?";
				link.l1 = "Dokładnie tak, to on. A ja - kapitan "+GetFullName(pchar)+".";
				link.l1.go = "OZ_Frantsuz_1_1";
			}
			else
			{
				dialog.text = "Co za widowisko... Przyznaję, "+GetAddress_Form(NPChar)+", sprawiliście mi przyjemność. Doskonale władajecie klingą. Zabawne, jak czasem układają się okoliczności - księga, dla której przebyłem długą drogę, zmieniła właściciela w najbardziej nieoczekiwany sposób. Ale mam nadzieję, że nie wyjadę stąd z pustymi rękami.";
				link.l1 = "Hm... Na ile wy wyceniacie tę księgę?";
				link.l1.go = "OZ_Frantsuz_2";
			}
		break;
		
		case "OZ_Frantsuz_1_1":
			dialog.text = "Widzicie, kapitanie, przebyłem niemałą odległość dla jednej księgi... I wygląda na to, że teraz jest w waszych rękach. Szczerze liczę, że dojdziemy do porozumienia - nie chciałbym opuszczać tego miejsca z pustymi rękami.";
			link.l1 = "Hm... Na ile wy wyceniacie tę księgę?";
			link.l1.go = "OZ_Frantsuz_2";
		break;
		
		case "OZ_Frantsuz_2":
			dialog.text = "Och, "+GetAddress_Form(NPChar)+", znam cenę naprawdę rzadkich rzeczy. Osiemdziesiąt tysięcy peso. Suma więcej niż hojna i, wierzcie mi, raczej nie dostaniecie podobnej propozycji drugi raz.";
			link.l1 = "Cóż, księga rzeczywiście cenna i przyznam, zapyta"+GetSexPhrase("łem","łam")+" wyłącznie z ciekawości. Nie zamierzam handlować czyimś losem. Niestety, monsieur, transakcji nie będzie - ta księga musi wrócić do właściciela.";
			link.l1.go = "OZ_Frantsuz_3";
			link.l2 = "Śmieszna suma. W tej księdze zebrano sekrety najlepszych mistrzów kowalskich. Sto pięćdziesiąt tysięcy peso - albo się zgadzacie, albo wraca do właściciela. Targów nie będzie.";
			link.l2.go = "OZ_Frantsuz_4";
		break;
		
		case "OZ_Frantsuz_3":
			dialog.text = "Proszę, nie odmawiajcie tak pochopnie. Przebyłem dla niej długą drogę. Jestem gotów zaoferować wam sto tysięcy, wyłącznie w dowód szacunku dla kunsztu, z jakim poradziliście sobie z tym człowiekiem.";
			link.l1 = "Powiedzia"+GetSexPhrase("łem","łam")+" już wszystko. Proszę wybaczyć, muszę iść.";
			link.l1.go = "OZ_Frantsuz_4_1";
		break;
		
		case "OZ_Frantsuz_4_1":
			DialogExit();
			AddDialogExitQuestFunction("OZ_Frantsuz_1");
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, SPAIN, 10);
		break;
		
		case "OZ_Frantsuz_4":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", doceniam waszą pewność, ale sto pięćdziesiąt tysięcy - to już nie cena, to absurd. Nie zamieniajmy transakcji w farsę. Sto tysięcy peso - to rozsądna suma, zgódźcie się, nikt za tę księgę nie da więcej.";
			link.l1 = "Wygląda na to, że nie doszliśmy do porozumienia. Cóż, nie widzę sensu ciągnąć tej rozmowy. Wszystkiego dobrego, monsieur.";
			link.l1.go = "OZ_Frantsuz_5";
		break;
		
		case "OZ_Frantsuz_5":
			dialog.text = "Zaczekajcie! Dobrze, wygraliście. Sto pięćdziesiąt tysięcy. Umawiamy się?";
			link.l1 = "Rad"+GetSexPhrase("","a")+" jestem, że dokonaliście właściwego wyboru. Księga wasza. Sądzę, że z nią staniecie się najlepszym mistrzem na Karaibach.";
			link.l1.go = "OZ_Frantsuz_6";
			TakeItemFromCharacter(pchar, "OZ_book");
			AddMoneyToCharacter(pchar, 150000);
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
			ChangeCharacterNationReputation(pchar, SPAIN, -10);
			ChangeCharacterReputation(pchar, -5);
		break;
		
		case "OZ_Frantsuz_6":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", nawet bez tej księgi nie miałem równych. Ale przyznam, miło zdobyć tak rzadkie trofeum. A teraz proszę wybaczyć - nie mogę się doczekać, by sprawdzić, czy naprawdę jest warta tych zachwytów, które o niej słyszałem.";
			link.l1 = "Cóż, w takim razie nie będę was dłużej zatrzymywać. Wszystkiego dobrego.";
			link.l1.go = "OZ_Frantsuz_7";
		break;
		
		case "OZ_Frantsuz_7":
			DialogExit();
			AddDialogExitQuestFunction("OZ_Frantsuz_2");
		break;
		
		case "OZ_Bandit_1":
			if (pchar.sex == "man")
			{
				dialog.text = "Oho, a cóż to za szumowina? Myślałeś, że opróżnisz naszą skrzynię i dasz nogę? Pomyłka, koleś. Zaraz cię wpakujemy do tej skrzyni i zabijemy wieko na głucho!";
			}
			else
			{
				dialog.text = "No, no... Kogo my tu mamy? Nie zgubiłaś się, maleńka? Myślałaś opróżnić skrzynię i cichcem się ulotnić? Pomyłka, kochaneczko. Teraz cię porządnie przetrzepiemy - i zobaczymy, co masz w kieszeniach... i nie tylko.";
			}
			link.l1 = "Za dużo gadania jak na mizerne robaki waszego pokroju. Wyciągajcie żelastwo, zobaczymy, ile naprawdę jesteście warci.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Grot_4");
		break;
		
		case "OZ_Felip_11":
			dialog.text = "Kapitanie! Już mi doniesiono, że Javier poszedł na tamten świat z waszej łaski. A przecież prosiłem, by nie zabijać go przed czasem! Mam nadzieję, że przyszliście oddać mi moje pieniądze?";
			if (sti(pchar.Money) >= 100000)
			{
				link.l1 = "Dokładnie tak. Udało mi się znaleźć jego skrytkę, w której było sto tysięcy peso. To wszystkie pieniądze, jakie miał.";
				link.l1.go = "OZ_Felip_12";
			}
			link.l2 = "Tak, musiał"+GetSexPhrase("em","am")+" go zabić. Ale to on sam ruszył pierwszy, więc musiał"+GetSexPhrase("em","am")+" się bronić. W jego kieszeniach było pusto - ani grosza. Niestety, długu nie udało się odzyskać.";
			link.l2.go = "OZ_Felip_14";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.OZ_Dolg");
		break;
		
		case "OZ_Felip_12":
			dialog.text = "Sto tysięcy... Oczywiście to nie cała suma, ale znając Javiera, wątpię, by ktoś zdołał wycisnąć z niego więcej. Cóż, dziękuję, kapitanie. Wygląda na to, że zatrudniłem nie tych ludzi. Naprawdę jesteście mistrzem w swoim fachu.";
			link.l1 = "To nie było trudne. Na tym jestem zmuszon"+GetSexPhrase("y","a")+" się z wami pożegnać. Obowiązki wzywają.";
			link.l1.go = "OZ_Felip_13";
			AddMoneyToCharacter(pchar, -100000);
		break;
		
		case "OZ_Felip_13":
			dialog.text = "Do widzenia, kapitanie.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Felip_good");
		break;
		
		case "OZ_Felip_14":
			dialog.text = "Ty łajdak"+GetSexPhrase("","a")+"! Kłamiesz mi prosto w oczy?! Nie ujdzie ci to płazem!";
			link.l1 = "Argh...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Felip_bad");
		break;
		
		case "OZ_Kuznets_Tovar":
			//PlaySound("VOICE\Russian\Master_02.wav");
			//PlaySound("VOICE\Spanish\Master_02.wav");
			dialog.text = "Witajcie, "+pchar.name+"! Czy chcecie kupić materiały lub wyroby?";
			link.l1 = ""+TimeGreeting()+". Zobaczmy, co macie.";
			link.l1.go = "OZ_Kuznets_Tovar_2";
			link.l2 = "I wam dzień dobry, "+npchar.name+"! Dziękuję za propozycję, ale chciał"+GetSexPhrase("em","am")+" się tylko przywitać.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_Tovar_repeat";
			SetFunctionTimerCondition("OZ_Kuznets_Reset", 0, 0, 1, false);
			if (!CheckAttribute(npchar, "quest.OZ_Kuznets_tovar")) 
			{
				SetFunctionTimerCondition("OZ_Kuznets_Reset_2", 0, 0, 30, false);
				npchar.quest.OZ_Kuznets_tovar = true;
			}
		break;
		
		case "OZ_Kuznets_Tovar_repeat":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", zdecydowaliście się jednak coś kupić?";
			link.l1 = "Dokładnie tak. Pokażcie, co macie dzisiaj.";
			link.l1.go = "OZ_Kuznets_Tovar_2";
			link.l2 = "Niestety, już wychodzę.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_Tovar_repeat";
		break;
		
		case "OZ_Kuznets_Tovar_2":
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
			NextDiag.CurrentNode = "OZ_Kuznets_Tovar_repeat";
		break;
		
	}
}
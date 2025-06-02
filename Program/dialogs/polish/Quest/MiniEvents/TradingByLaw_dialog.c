void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	
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
			dialog.text = "Czego chcesz?";
			link.l1 = "Nic.";
			link.l1.go = "exit";
		break;

		case "Kristian":
			dialog.text = "Witam w moim domu! Nazywam się Christian. Christian Deluche. W czym mogę pomóc?";
			link.l1 = "Jestem kapitanem "+GetFullName(pchar)+". Potrzebuję kupić partię alkoholu. Wie pan, o co chodzi?";
			link.l1.go = "Kristian_2";
			DelLandQuestMark(npchar);
		break;

		case "Kristian_2":
			dialog.text = "Co??? Kto ci to powiedział? To jakaś pomyłka, zapewniam cię, nie handluję żadnym alkoholem!";
			link.l1 = "Aha. Widzę, że trafiłem"+GetSexPhrase("em","am")+" pod właściwy adres.";
			link.l1.go = "Kristian_3";
		break;

		case "Kristian_3":
			dialog.text = "O-o-o, nie, nie, co ty! Żadnego handlu alkoholem, co ty, ja... ja tylko, e-e... No tak, mam trochę towaru, ale to wszystko zgodnie z prawem! Kupuję tylko dla prywatnych osób, e-e... na uroczystości, na małe przyjęcia!";
			link.l1 = "Dlaczego się tak denerwujesz? Ja przysz"+GetSexPhrase("edłem","łam")+" nie po to, żeby cię aresztować, tylko żeby pomóc twojemu biznesowi się rozwijać. I, mam nadzieję, napełnić też trochę moje kieszenie.";
			link.l1.go = "Kristian_4";
		break;

		case "Kristian_4":
			dialog.text = "Ja... ja wcale się nie denerwuję! Dlaczego miałbym się denerwować? Jestem uczciwym obywatelem, mój dom stoi tuż obok rezydencji gubernatora. Zapewniam cię, nie łamię prawa!";
			link.l1 = "Czyli nie handlujesz alkoholem? Szkoda, wielka szkoda. Widzisz, mam bardzo korzystną propozycję. Jestem pewn"+GetSexPhrase("y","a")+", że tylu dublonów w życiu żeś nie widział. Ale skoro nie jesteś tą osobą, której szukam, to chyba sobie pójdę. Dobrze?";
			link.l1.go = "Kristian_5";
		break;

		case "Kristian_5":
			dialog.text = "E-e... zaczekaj... "+GetAddress_Form(NPChar)+"... przepraszam, po prostu się zestresowałem, zapomniałem, jak się nazywasz.";
			link.l1 = "Kapitan "+GetFullName(pchar)+".";
			link.l1.go = "Kristian_6";
		break;

		case "Kristian_6":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" "+pchar.lastname+", chodzi o to, e-e... no... wiem, gdzie znaleźć osobę, której szukasz. Mogę mu... przekazać twoją propozycję.";
			link.l1 = "Przekazać? Naprawdę sądzisz, że w takich sprawach należy coś przekazywać przez obcych ludzi?";
			link.l1.go = "Kristian_7";
		break;
		
		case "Kristian_7":
			dialog.text = "Masz rację. Ale... ech... niech będzie... tak, to ja jestem tym, kogo szukasz.";
			link.l1 = "No, tak lepiej, Christian. Widzisz, w karczmie są teraz poważne problemy z dostawami alkoholu i mam nadzieję, że razem uda nam się z tego coś wyciągnąć.";
			link.l1.go = "Kristian_8";
		break;

		case "Kristian_8":
			dialog.text = "Kapitanie, wiem o trudnościach karczmarza, bo ludzie zaczęli przychodzić do mnie, i już zaczynam się bać handlu, to przyciąga zbyt dużo uwagi. Pomyślałem więc, że ty... no, rozumiesz...";
			link.l1 = "Dlaczego więc nie zaproponowałeś mu swoich usług?";
			link.l1.go = "Kristian_9";
		break;

		case "Kristian_9":
			dialog.text = "On... on nigdy nie będzie chciał współpracować ze mną. Ten człowiek nie znosi takich drobnych handlarzy jak ja.";
			link.l1 = "Tak, słyszałem"+GetSexPhrase("","am")+" o tym. Z tobą może i nie będzie chciał. Ale ze mną – będzie.";
			link.l1.go = "Kristian_10";
		break;

		case "Kristian_10":
			dialog.text = "Chcesz zostać pośrednikiem? Cóż, nie mam nic przeciwko... ostatnio dostarczyliśmy partię – prawdziwy rekord! Powinna mi wystarczyć na pół roku. Ale, niech Bóg będzie świadkiem, tylko cud uratował nas przed wykryciem.\nDo tej pory nie wiem, jak udało nam się umknąć. Powtórzenie tego byłoby samobójstwem.";
			link.l1 = "W takim razie powinieneś wyjść z cienia. Przynajmniej częściowo.";
			link.l1.go = "Kristian_11";
		break;

		case "Kristian_11":
			dialog.text = "W-wyjdę z cienia? Ale... do tego trzeba kontaktów! I pieniędzy! Po co w ogóle? Czy ty, kapitan statku, zamierzasz osiąść w mieście i zająć się dostawami dla lokalnej karczmy?";
			link.l1 = "Kontaktami, sądzę, mogę ci pomóc. Co do pieniędzy... nie sądzę, żeby trzeba było ich zbyt wiele. A ostatnie wcale nie będzie potrzebne. Będziesz działać w moim imieniu. Ja pomogę tobie, ty pomożesz mnie. Regularnie. Ty masz stabilny zbyt, ja – solidnego dostawcę. Co powiesz na taki układ?";
			link.l1.go = "Kristian_12";
		break;

		case "Kristian_12":
			dialog.text = "Myślałem, że to jakaś pułapka. Ale, szczerze mówiąc, twoja propozycja brzmi... bardzo kusząco. Stabilność, niezawodność... Kto by pomyślał, że dostanę taką szansę. "+GetSexPhrase("Monsieur","Mademoiselle")+", zgadzam się! Ile chcesz kupować?";
			link.l1 = "Najpierw zalegalizujemy twój interes, a potem przejdziemy do szczegółów. Ile rumu i wina masz teraz?";
			link.l1.go = "Kristian_13";
		break;

		case "Kristian_13":
			dialog.text = "W tej chwili? E-e... Chodźmy do piwnicy, tam powiem ci dokładnie.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TPZ_GoToPogreb");	// спускаемся в погреб
		break;
		
		// погреб
		case "Kristian_15":
			dialog.text = "No, no... Co my tu mamy? Aha\nObecnie mam na stanie dokładnie sto butelek rumu i sto butelek wina.";
			link.l1 = "Cóż, myślę, że na początek to wystarczy. Jeśli uda się rozwiązać problem z dostawami, będziesz w stanie dostarczać takie partie co miesiąc, bez opóźnień?";
			link.l1.go = "Kristian_16";
		break;

		case "Kristian_16":
			dialog.text = "Oczywiście, kapitanie! Nawet trzy, nie – cztery razy więcej mogę! Nie będzie żadnych opóźnień, zawsze będę trzymać odpowiednią ilość w magazynie, aby w razie czego pokryć każdy niedobór.";
			link.l1 = "Ile chcesz za tę partię?";
			link.l1.go = "Kristian_17";
		break;

		case "Kristian_17":
			dialog.text = "Zadowoli mnie: dziesięć dubloonów za każde dziesięć butelek wina i trzy dubloony za dziesięć butelek rumu. Czyli razem sto trzydzieści dublonów za całą partię.";
			link.l1 = "Dobrze. Porozmawiam z karczmarzem i wkrótce wrócę.";
			link.l1.go = "Kristian_18";
		break;
		
		case "Kristian_18":
			DialogExit();
			
			NextDiag.CurrentNode = "Kristian_18_1";
			pchar.questTemp.TPZ_Tavern_2 = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
			AddQuestRecord("TPZ", "4");
		break;
		
		case "Kristian_18_1":
			dialog.text = "Kapitanie, są jakieś wieści? Co powiedział karczmarz?";
			link.l1 = "Właśnie się do niego udaję.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Kristian_18_1";
		break;

		case "Kristian_21":
			dialog.text = "Jak wszystko poszło, kapitanie? Udało się dogadać z karczmarzem?";
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino240"))
			{
				link.l1 = "Napracowałem się, Christian. Kupi tę i wszystkie następne partie po dwieście czterdzieści dublonów. Za pierwszą zapłacę ci sto trzydzieści, jak chciałeś. Resztę zostawię sobie jako wynagrodzenie. A cały przyszły zysk – twój.";
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino200"))
			{
				link.l1 = "Dobrze się spisałem, Christian. Kupi tę i wszystkie następne partie po dwieście dublonów. Za pierwszą zapłacę ci sto trzydzieści, jak chciałeś. Reszta zostanie ze mną – za trud. Cały przyszły zysk – twój.";
			}
			link.l1.go = "Kristian_22";
			DelLandQuestMark(npchar);
		break;

		case "Kristian_22":
			dialog.text = "Toż to wspaniała wiadomość, kapitanie! Nawet nie śniłem o takiej umowie, dziękuję! Ale... czy się nie pospieszyłeś? Gubernator... ja... to znaczy...";
			link.l1 = "Z gubernatorem wszystko załatwione. Teraz każdego miesiąca będziesz płacić podatek – sto dublonów – i składać raporty z handlu.";
			link.l1.go = "Kristian_23";
		break;

		case "Kristian_23":
			dialog.text = "Niewiarygodne! Jak ci się to udało, kapitanie? Gubernator to przecież surowy człowiek i zaciekły przeciwnik nielegalnego handlu...";
			link.l1 = "Właśnie o to chodzi, Christian – przeciwnik nielegalnego, ale nie uczciwego. Wysłuchał mnie chętnie i przedstawił warunki handlu alkoholem na wyspie. Będziesz działać w moim imieniu, a za twoje wybryki będę odpowiadać razem z tobą. Więc nie zawiedź mnie, bo znajdę cię nawet po drugiej stronie życia.";
			link.l1.go = "Kristian_24";
		break;

		case "Kristian_24":
			dialog.text = "Przysięgam, kapitanie, nie pożałujesz!";
			link.l1 = "Teraz musimy dopiąć transakcję z karczmarzem, a potem omówimy szczegóły naszej współpracy.";
			link.l1.go = "Kristian_25";
		break;
		
		case "Kristian_25":
			dialog.text = "Oczywiście, kapitanie. Jesteś gotów odebrać towar już teraz? To będzie kosztować sto trzydzieści dublonów.";
			if (PCharDublonsTotal() >= 130)
			{
				link.l1 = "Tak, oto twoje dubloony.";
				link.l1.go = "Kristian_26";
			}
			else
			{
				link.l1 = "W tej chwili nie mam wystarczającej kwoty. Zaczekaj tu, znajdę pieniądze i wrócę.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Kristian_25_1";
			}
		break;

		case "Kristian_25_1":
			dialog.text = "Kapitanie! Wróciłeś po towar? To będzie kosztować sto trzydzieści dublonów.";
			if (PCharDublonsTotal() >= 130)
			{
				link.l1 = "Dokładnie tak! Oto twoje dubloony.";
				link.l1.go = "Kristian_26";
			}
			else
			{
				link.l1 = "Niestety, jeszcze nie mam odpowiedniej sumy. Wpadnę później.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Kristian_25_1";
			}
		break;

		case "Kristian_26":
			dialog.text = "Dziękuję! Zabieraj! Sto butelek wina i sto butelek rumu, jak ustaliliśmy.";
			link.l1 = "Towar odbiorą moi marynarze. A ja tymczasem porozmawiam z karczmarzem.";
			link.l1.go = "Kristian_27";
			RemoveDublonsFromPCharTotal(130);
		break;
		
		case "Kristian_27":
			DialogExit();
			
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.TPZ_Tavern_4 = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
		break;
		
		case "Kristian_31":
			dialog.text = ""+pchar.name+"! Już jesteś! No i jak, wszystko poszło zgodnie z planem?";
			link.l1 = "Wszystko w porządku, Krystianie. Karczmarz będzie odbierał takie same partie dwa razy w miesiącu. Zapewnij mu regularne dostawy — a zapomnisz, czym jest bieda.";
			link.l1.go = "Kristian_32";
			DelLandQuestMark(npchar);
		break;

		case "Kristian_32":
			dialog.text = "Kapitanie... ty... jakbyś sam los zesłał się do mnie! To jakiś cud, wciąż nie wierzę! Czym zasłużyłem na taką dobroć? Nie wiem, jak ci dziękować!";
			link.l1 = "Ale ja wiem, Krystianie. Co miesiąc musisz mieć odłożoną część towaru tylko dla mnie i dla nikogo innego. Kupię ją po cenie, którą podałeś — dziesięć dublonów za dziesięć butelek wina i trzy dublony za dziesięć butelek rumu.";
			link.l1.go = "Kristian_33";
		break;

		case "Kristian_33":
			dialog.text = "Będę zaszczycony, "+pchar.name+", rezerwować dla ciebie towar! Możesz być pewien, że cię nie zawiodę! Ile chciałbyś odbierać? Pięćdziesiąt? Sto butelek? Podaj tylko liczbę!";
			link.l1 = "Na razie nie potrzebuję aż tyle. Dwadzieścia butelek wystarczy. Jeśli będę potrzebować więcej — dam ci znać.";
			link.l1.go = "Kristian_34";
		break;

		case "Kristian_34":
			dialog.text = "Oczywiście, oczywiście! Zatem, dwadzieścia butelek wina i dwadzieścia rumu za 26 dubloonów. Każdego piętnastego dnia miesiąca towar będzie czekał na ciebie. Będę się cieszył z każdej twojej wizyty, nawet jeśli tylko zajrzysz się przywitać!";
			link.l1 = "Doskonale! I jeszcze jedno, Krystianie. Ręczę za ciebie swoim imieniem. Nie zawiedź mnie.";
			link.l1.go = "Kristian_35";
		break;

		case "Kristian_35":
			dialog.text = "Ja... co ty, kapitanie... ja... nie, nie, nie zawiodę! Wszystko będzie na najwyższym poziomie, przysięgam!";
			link.l1 = "W takim razie — do zobaczenia!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TPZ_SpawnShip");
		break;
		
		case "Pirate_1":
			dialog.text = ""+GetSexPhrase("Bękarcie","Szmato")+"! Czyż nie uczono cię, że wtykanie nosa w nieswoje sprawy to zawsze kłopoty?";
			link.l1 = "To ty pierwszy mnie zaatakowałeś, a teraz jeszcze mówisz, że wtrącam się w cudze sprawy? Chyba ci odbiło?";
			link.l1.go = "Pirate_2";
		break;

		case "Pirate_2":
			dialog.text = "Grom mnie w bukszpryt! Ty, "+GetSexPhrase("sukinsynu","szmato")+", nawet nie rozumiesz, w co się wpakował"+GetSexPhrase("eś","aś")+"? Myślisz, że dostawy do karczmy po prostu tak sobie ustały?";
			link.l1 = "Chcesz powiedzieć, że to ty spaliłeś tę faktorję?";
			link.l1.go = "Pirate_3";
		break;

		case "Pirate_3":
			dialog.text = "Ha ha, wreszcie załapałeś, niech mnie kule trafią! Tak, to moja robota! Ten dostawca miał zbyt mocną pozycję. Ale jak widzisz, zawsze potrafię pozbyć się rywali. I ty też nie uciekniesz, niech mnie knypel trafi w grot!";
			link.l1 = "Zabawne. Zobaczmy, na co cię stać, niech rekiny pożrą twoje truchło! Ha ha!";
			link.l1.go = "Pirate_4";
		break;

		
		case "Pirate_4":
			DialogExit();
			
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_GivePrisoner");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Kristian_41":
			dialog.text = "Witam, "+pchar.name+"! W czym mogę pomóc?";
			if(CheckAttribute(pchar, "questTemp.TPZ_TradeVinoAndRom")) // торговля вином и ромом
			{
				if (GetDataDay() == 15)
				{
					link.l1 = "Witam, Christian. Towar już gotowy?";
					link.l1.go = "Kristian_42";
				}
			}
			link.l2 = "Witam, Christian. Chciał"+GetSexPhrase("em","am")+" tylko zobaczyć, jak się pan miewa. Już wychodzę.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Kristian_41";
		break;

		case "Kristian_42":
			if (CheckAttribute(pchar, "questTemp.TPZ_UpgradeVino"))
			{
				dialog.text = "Oczywiście, kapitanie! Czyżbyś mógł wątpić w moją niezawodność?";
				if (PCharDublonsTotal() >= 130)
				{
					link.l1 = "Oczywiście, że nie, Christian. Oto twoje dublony, zabieram alkohol.";
					link.l1.go = "Kristian_43";
				}
				else
				{
					link.l2 = "W żadnym wypadku. Ale zapomniał"+GetSexPhrase("em","am")+" zabrać dublony. Może wpadnę później.";
					link.l2.go = "exit";
					NextDiag.TempNode = "Kristian_41";
				}
			}
			else
			{
				dialog.text = "Oczywiście, kapitanie! Czyżbyś wątpił w moją niezawodność?";
				if (PCharDublonsTotal() >= 26)
				{
					link.l1 = "Oczywiście, że nie, Christian. Oto twoje dublony, zabieram alkohol.";
					link.l1.go = "Kristian_43";
				}
				else
				{
					link.l2 = "W żadnym wypadku. Ale zapomniał"+GetSexPhrase("em","am")+" zabrać dublony. Może wpadnę później.";
					link.l2.go = "exit";
					NextDiag.TempNode = "Kristian_41";
				}
			}
			if(sti(pchar.questTemp.TPZ_KritstianVinoAndRom) >= 1 && !CheckAttribute(pchar, "questTemp.TPZ_KritstianVinoBlock")) // увеличить объём поставок вина и рома
			{
				link.l4 = "Christian, chciał"+GetSexPhrase("bym","abym")+" zwiększyć zakupy. Powiedzmy, po sto butelek rumu i wina co miesiąc.";
				link.l4.go = "UpgradeVino";
			}
			if(sti(pchar.questTemp.TPZ_KritstianVinoAndRom) >= 1 && CheckAttribute(pchar, "questTemp.TPZ_KritstianVinoPotom") && sti(pchar.Money) >= 50000) // увеличить объём поставок вина и рома, если в первый раз не принесли
			{
				link.l4 = "Christian, chciał"+GetSexPhrase("bym","abym")+" omówić zwiększenie dostaw.";
				link.l4.go = "UpgradeVino_Agreed";
			}
		break;
		
		case "Kristian_43":
			dialog.text = "Doskonałe. Piętnastego dnia każdego miesiąca nowa partia będzie na ciebie czekać, jak zawsze. Zapraszam.";
			link.l1 = "Na pewno przyjdę. Do zobaczenia.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Kristian_41";
			
			if (CheckAttribute(pchar, "questTemp.TPZ_UpgradeVino"))
			{
				RemoveDublonsFromPCharTotal(130);
				AddItems(pchar, "potionrum", 100);
				AddItems(pchar, "potionwine", 100);
			}
			else
			{
				RemoveDublonsFromPCharTotal(26);
				AddItems(pchar, "potionrum", 20);
				AddItems(pchar, "potionwine", 20);
			}
			
			DeleteAttribute(pchar, "questTemp.TPZ_TradeVinoAndRom");
			SetFunctionTimerCondition("TPZ_KristianReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			pchar.questTemp.TPZ_KritstianVinoAndRom = sti(pchar.questTemp.TPZ_KritstianVinoAndRom) + 1; // счётчик покупок
		break;

		case "UpgradeVino":
			dialog.text = "Kapitanie, zwiększenie dostaw to rzecz niewątpliwie korzystna, lecz i kosztowna! Więcej towaru oznacza więcej rąk do pracy, trzeba rozszerzyć magazyny, wynająć większy statek... Bez inwestycji nie zdołam zapewnić potrzebnej ilości towaru na czas.";
			link.l1 = "O jakiej kwocie mówimy? Ile potrzeba, by wszystko działało jak należy?";
			link.l1.go = "UpgradeVino_2";
		break;

		case "UpgradeVino_2":
			dialog.text = "Pięćdziesiąt tysięcy peso. Pozostałe wydatki wezmę na siebie.";
			link.l1 = "Pięćdziesiąt tysięcy? Hm... to niemała suma. Naprawdę nie da się tego zrobić taniej?";
			link.l1.go = "UpgradeVino_3";
		break;
		
		case "UpgradeVino_3":
			dialog.text = "Niestety, kapitanie, ale tu nie da się oszczędzić. Jeśli nie zrobimy wszystkiego jak należy, wszystko może się... powiedzmy, nie potoczyć zgodnie z planem. A kłopoty nie są nikomu potrzebne – ani mi, ani tobie.";
			if (sti(pchar.Money) >= 50000)
			{
				link.l1 = "Oto twoje pieniądze. Nie zawiedź mnie, Kristianie.";
				link.l1.go = "UpgradeVino_5";
			}
			link.l2 = "Wiesz co, Kristianie, może to jednak nie taki świetny pomysł. Wrócimy do tego, kiedy okoliczności będą bardziej sprzyjające.";
			link.l2.go = "UpgradeVino_4";
		break;

		case "UpgradeVino_4":
			dialog.text = "Jak sobie życzysz, kapitanie. Jeśli zmienisz zdanie, daj mi znać.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Kristian_41";
			pchar.questTemp.TPZ_KritstianVinoBlock = true;
			pchar.questTemp.TPZ_KritstianVinoPotom = true;
		break;

		case "UpgradeVino_Agreed":
			dialog.text = "Kapitanie, to wspaniała wiadomość! Czy jesteś gotów wpłacić pięćdziesiąt tysięcy srebra od razu?";
			if (sti(pchar.Money) >= 50000)
			{
				link.l1 = "Oto twoje pieniądze. Nie zawiedź mnie, Kristianie.";
				link.l1.go = "UpgradeVino_5";
			}
			link.l2 = "W tej chwili nie mam odpowiedniej kwoty. Wrócę, gdy ją zgromadzę.";
			link.l2.go = "UpgradeVino_4";
		break;

		case "UpgradeVino_5":
			dialog.text = "Obiecuję, "+pchar.name+", nie pożałujesz tej decyzji! Natychmiast zabieram się za przygotowania. Już od następnej dostawy będziesz mógł odbierać po sto butelek rumu i tyleż samo doskonałego wina, za sto trzydzieści dublonów za całość.";
			link.l1 = "Znakomicie. I nie zapominaj o ostrożności. Twoja praca to również moja reputacja.";
			link.l1.go = "UpgradeVino_6";
			AddMoneyToCharacter(pchar, -50000);
		break;
		
		case "UpgradeVino_6":
			DialogExit();
			
			NextDiag.CurrentNode = "Kristian_41";
			pchar.questTemp.TPZ_UpgradeVino = true;
			pchar.questTemp.TPZ_KritstianVinoBlock = true;
			DeleteAttribute(pchar, "questTemp.TPZ_KritstianVinoPotom");
			AddQuestRecordInfo("Useful_Acquaintances", "4_1");
		break;
		
		
	}
}
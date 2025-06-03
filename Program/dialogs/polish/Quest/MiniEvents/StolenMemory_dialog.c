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
			link.l1 = "Niczego.";
			link.l1.go = "exit";
		break;

		case "Juli":
			dialog.text = "...";
			if (pchar.sex == "woman")
			{
				link.l1 = "Mademoiselle, mówią, że Port-au-Prince traci swój urok, gdy się nie uśmiechasz. Dziś jest, jak sądzę, właśnie taki dzień. Wybacz szczerość, ale coś cię trapi?";
			}
			else
			{
				link.l1 = "Mademoiselle, słyszałem wiele o twojej urodzie i wdzięku, i muszę przyznać – pogłoski były zdecydowanie zbyt skromne. Mówią też, że Port-au-Prince traci cały swój urok, gdy się nie uśmiechasz. Dziś, niestety, wydaje się być takim właśnie dniem. Powiedz mi, kim jest ten drań, który ośmielił się zepsuć ci humor – przysięgam, wyzwę go na pojedynek, by przywrócić uśmiech na twojej pięknej twarzy.";
			}
			link.l1.go = "Juli_2";
			DelLandQuestMark(npchar);
		break;

		case "Juli_2":
			if (pchar.sex == "woman")
			{
				dialog.text = "Ach, mademoiselle, jesteś zbyt uważna... Przyznaję, twoja troska mnie poruszyła. Ale niestety, powód mojego niepokoju nie jest czymś, co można rozwiać lekką rozmową. To nie czyjaś wina, lecz okoliczności, którym nawet najbardziej zdeterminowana osoba nie jest w stanie zaradzić.";
				link.l1 = "Okoliczności? Zapewniam cię, mademoiselle, że dla "+GetFullName(pchar)+" nie istnieją przeszkody nie do pokonania. Opowiedz mi, co się stało – być może będę w stanie pomóc.";
			}
			else
			{
				dialog.text = "Och, monsieur, wygląda na to, że jesteś mistrzem pięknych słów. Przyznaję, niemal udało ci się wywołać uśmiech na mojej twarzy. Ale niestety, pojedynek nie rozwiąże mojego problemu. Ten, kto zepsuł mi dzień, to raczej nie łotr, a okoliczności, które są poza zasięgiem nawet tak dzielnego dżentelmena jak ty.";
				link.l1 = "Okoliczności? Zapewniam cię, mademoiselle, kapitan "+GetFullName(pchar)+" radzi sobie z każdą sytuacją! A jeśli zawiodę, przysięgam, zjem kapelusz pierwszego przechodnia, którego zobaczę!";
			}
			link.l1.go = "Juli_3";
		break;

		case "Juli_3":
			if (pchar.sex == "woman")
			{
				dialog.text = "Jeśli naprawdę nalegasz, opowiem ci, co się stało. Ale najpierw muszę mieć twoje słowo, że ta rozmowa pozostanie tylko między nami.";
				link.l1 = "Daję ci słowo honoru, mademoiselle. Wszystko, co mi powiesz, pozostanie między nami – nawet jeśli miałabym zabrać ten sekret na samo dno morza.";
			}
			else
			{
				dialog.text = "Monsieur "+pchar.lastname+", bez wątpienia potrafisz rozweselić nawet głęboko zasmuconą damę. Ale błagam, oszczędź kapelusze biednych przechodniów. Jeśli naprawdę nalegasz, powiem ci, co się stało. Tylko daj słowo, że moje słowa pozostaną tajemnicą znaną tylko nam dwojgu.";
				link.l1 = "Daję ci słowo, mademoiselle, że wszystko, co mi powiesz, zachowam w tajemnicy – nawet pod groźbą śmierci.";
			}
			link.l1.go = "Juli_4";
		break;
		
		case "Juli_4":
			dialog.text = "Dobrze. Niedawno z mojego pokoju zniknął naszyjnik... to nie jest zwykła ozdoba. Został mi podarowany przez osobę, która zajmuje szczególne miejsce w moim sercu. Teraz czuję, jakbym straciła coś znacznie cenniejszego niż tylko przedmiot\nDługo się zastanawiałam, kto mógł to zrobić, i doszłam tylko do jednego wniosku. Obawiam się, że to ktoś z mojej służby. To jedyne osoby, które mają dostęp do mojego pokoju i mogą być zainteresowane takim łupem. Ale nie mogę tego zgłosić otwarcie...";
			link.l1 = "To rzeczywiście delikatna sprawa, skoro chcesz uniknąć rozgłosu. Ale jeśli mam ci pomóc, muszę wiedzieć, dlaczego tak bardzo chcesz to zachować w tajemnicy. Muszę wiedzieć, kogo i czego się wystrzegać, aby przez przypadek nie zdradzić twoich intencji.";
			link.l1.go = "Juli_5";
			if (pchar.sex == "woman")
			{
				link.l2 = "Nie możesz? W takim razie, mademoiselle, pozostaje mi tylko życzyć powodzenia. Intrygi i sekrety to nie moja specjalność. Twój problem wydaje się możliwy do rozwiązania przy pomocy straży miejskiej. Ale wygląda na to, że sama wolisz wszystko skomplikować.";
				link.l2.go = "Juli_end";
			}
			else
			{
				link.l2 = "Nie możesz? Wybacz, mademoiselle, ale w takim razie naprawdę jestem bezsilny. Tajemnice i gry pozorów nie są dla mnie, madame. Twój problem wydaje się boleśnie prosty – straż mogłaby to szybko rozwiązać. Ale wygląda na to, że wolisz uczynić z tego dworski dramat.";
				link.l2.go = "Juli_end";
			}
		break;

		case "Juli_end":
			dialog.text = "Tak oto radzisz sobie z trudnościami, "+GetFullName(pchar)+"? Gdy ktoś ci zaufał, odwracasz się plecami? Mam nadzieję, że znajdziesz zadania godniejsze twójego wybitnego talentu – może liczenie beczek rumu albo gorące spory z portowymi handlarzami. Ale przynajmniej zachowaj naszą rozmowę w tajemnicy, jeśli pozostało ci choć odrobinę honoru. Żegnaj.";
			link.l1 = "...";
			link.l1.go = "Juli_end_2";
		break;

		case "Juli_end_2":
			DialogExit();
			CloseQuestHeader("UV");
			ChangeCharacterComplexReputation(pchar, "nobility", -5);

			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;

		case "Juli_5":
			dialog.text = "Masz rację, "+GetAddress_Form(NPChar)+", powinieneś znać prawdę. Ten naszyjnik był prezentem od osoby, której mój wuj – gubernator francuskiej części tej wyspy – nie znosi. Zakazał mi nawet wspominać jego imienia. Jeśli dowie się, kto podarował mi ten naszyjnik, konsekwencje mogą być katastrofalne – nie tylko dla mnie, ale i...";
			link.l1 = "Nie mów więcej, madame. Wiem już wystarczająco. Obiecuję ci, że zrobię wszystko, by odzyskać ten naszyjnik, nie narażając twojego sekretu nawet na najmniejsze niebezpieczeństwo.";
			link.l1.go = "Juli_6";
		break;

		case "Juli_6":
			dialog.text = "Dziękuję ci, "+GetSexPhrase("monsieur "+pchar.lastname+"",""+pchar.name+"")+". Twoja determinacja i takt bardzo mnie poruszyły. Wierzę, że mój sekret jest bezpieczny w twych rękach. Niech szczęście ci sprzyja w tym trudnym zadaniu.";
			if (pchar.sex == "woman")
			{
				link.l1 = "Szczęście sprzyja tym, którzy działają, mademoiselle. Znajdę twój naszyjnik, możesz być tego pewna.";
			}
			else
			{
				link.l1 = "Szczęście sprzyja silnym, mademoiselle. Jak tylko znajdę naszyjnik, od razu trafi w twoje delikatne ręce.";
			}
			link.l1.go = "Juli_7";
		break;
		
		case "Juli_7":
			DialogExit();
			
			NextDiag.CurrentNode = "Juli_7_again";
			AddQuestRecord("UV", "2");
			AddQuestUserData("UV", "sSex", GetSexPhrase("","а"));
			
			pchar.questTemp.UV_Lavochniki = true;
		break;
		
		case "Juli_7_again":
			if (CheckCharacterItem(PChar, "SM_necklace_Julie"))
			{
				dialog.text = "Ach, kapitanie, to ty... "+GetSexPhrase("Znalazłeś","Znalazłaś")+" go? Proszę, powiedz mi, że naszyjnik jest już u ciebie.";
				link.l1 = "Twoje zmartwienia dobiegły końca, Julie. Naszyjnik mam przy sobie i z przyjemnością oddam go tam, gdzie jego miejsce – w twe delikatne ręce.";
				link.l1.go = "Juli_22";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "Ach, kapitanie, to wy... "+GetSexPhrase("Znalazłeś","Znalazłaś")+" go? Proszę, powiedz mi, że naszyjnik jest już u ciebie.";
				link.l1 = "Niestety, Julie, jeszcze nie. Ale proszę się nie martwić – zrobię wszystko, co w mojej mocy, aby go odzyskać.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Juli_7_again";
				DelLandQuestMark(npchar);
			}
		break;

		case "Starpom_1":
			dialog.text = "Dzień dobry, monsieur. Co sprowadza cie na mój statek?";
			link.l1 = "Szukam Tristana Reniera – mam dla niego lukratywną propozycję.";
			link.l1.go = "Starpom_2_sneak";
			link.l2 = "Muszę porozmawiać z Tristanem Renierem w sprawie osobistej.";
			link.l2.go = "Starpom_2_fortune";
			DelLandQuestMark(npchar);
		break;

		case "Starpom_2_sneak":
			dialog.text = "Kapitan nie jest teraz na pokładzie. Sądzę, że możesz go znaleźć gdzieś w mieście.";
			link.l1 = "Czy wiesz może dokładniej, dokąd się udał?";
			link.l1.go = "Starpom_3";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;

		case "Starpom_2_fortune":
			dialog.text = "Kapitan nie jest teraz na pokładzie. Sądzę, że możesz go znaleźć gdzieś w mieście.";
			link.l1 = "Czy wiesz może dokładniej, dokąd się udał?";
			link.l1.go = "Starpom_3";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "Starpom_3":
			dialog.text = "Przykro mi, "+GetAddress_Form(NPChar)+", ale kapitan nie dzieli się ze mną swoimi planami. Wiem tylko, że zszedł na ląd.";
			link.l1 = "Cóż, i tak dziękuję.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("UV_GoldSeagull_RasprashivaemZhiteley");
		break;
		
		case "Captain_1":
			if (pchar.sex == "man")
			{
				dialog.text = "Kim, do diabła, jesteś? I jakim prawem wtargnąłeś do mojego pokoju bez zaproszenia?";
				link.l1 = "Nazywam się "+GetFullName(pchar)+". I mam do ciebie interes.";
			}
			else
			{
				dialog.text = "Kim jesteś, moja pani? Nie przypominam sobie, żebym zapraszał gości. Choć muszę przyznać, że niespodziewane wizyty bywają intrygujące. Czym zawdzięczam tę przyjemność?";
				link.l1 = "Nazywam się kapitan "+GetFullName(pchar)+". Przyszłam w interesach.";
			}
			link.l1.go = "Captain_2";
			DelLandQuestMark(npchar);
		break;

		case "Captain_2":
			if (pchar.sex == "man")
			{
				dialog.text = "Interes? Jaki interes, do diabła?";
				link.l1 = "Bardzo prosty. Masz naszyjnik, którego szukam.";
			}
			else
			{
				dialog.text = "W interesach, mówisz? Ciekawe... I cóż to za interes mógłby sprowadzić tak urodziwą damę prosto do mojego pokoju?";
				link.l1 = "Spokojnie, monsieur słodziaku – chodzi o naszyjnik. Wiem, że go masz.";
			}
			link.l1.go = "Captain_3";
		break;

		case "Captain_3":
			if (pchar.sex == "man")
			{
				dialog.text = "Ha! Naszyjnik? Tak, mam naszyjnik – i co z tego? Myślisz, że oddam go ot tak, bez powodu?";
			}
			else
			{
				dialog.text = "Naszyjnik, mówisz? Hm... Tak, mam jeden. I co? W jaki sposób chcesz go zdobyć?";
			}
			if (sti(pchar.Money) >= 5000)
			{
				link.l1 = "Jestem gotow"+GetSexPhrase("y","a")+" zapłacić ci pięć tysięcy peso. To wystarczająca suma, by kupić równie godny klejnot. Ten naszyjnik powinien wrócić do osoby, która ceni go całym sercem.";
				link.l1.go = "Captain_4_commerce";
			}
			link.l2 = "Wierz mi, nie masz wielu opcji: oddaj go po dobroci, a odejdę – albo wezmę to, czego potrzebuję, z twojego martwego ciała. Wybór należy do ciebie.";
			link.l2.go = "Captain_4_leadership";
		break;

		case "Captain_4_commerce":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 45)
			{
				dialog.text = "Pięć tysięcy? Cóż, dobrze, kapitanie. Bierz go, skoro to dla ciebie takie ważne.";
				link.l1 = "Dziękuję. Podjąłęś słuszną decyzję.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("UV_Ozherelie");
				notification("Sukces!", SKILL_COMMERCE);
				GiveItem2Character(pchar, "SM_necklace_Julie");
				ChangeCharacterComplexReputation(pchar, "nobility", 2);
				AddMoneyToCharacter(pchar, -5000);
			}
			else
			{
				dialog.text = "Nie kupiłem tego naszyjnika po to, by targować się z kimś takim jak ty! To prezent dla mojej żony i nie masz tu czego szukać. Wynocha stąd, póki sam cię stąd nie wyrzuce!";
				link.l1 = "Skoro nie chcesz rozstać się z nim po dobroci, to odbiorę go siłą.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("UV_Ozherelie_Duel");
				notification("Niewystarczająca umiejętność (45)", SKILL_COMMERCE);
			}
		break;

		case "Captain_4_leadership":
			if (GetSummonSkillFromName(pchar, SKILL_Leadership) >= 45)
			{
				dialog.text = "Ach... bezczelny szczeniaku... Myślisz, że przestraszą mnie twoje głupie groźby? Ha! Nie wiesz, z kim zadarłeś!";
				link.l1 = "Nie obchodzi mnie, kim jesteś. Po prostu oddaj naszyjnik i sobie pójdę. Chyba że naprawdę chcesz zginąć za błyskotkę, która nie ma dla ciebie większej wartości.";
				link.l1.go = "Captain_4_leadership_2";
				notification("Sukces!", SKILL_Leadership);
				AddCharacterExpToSkill(pchar, "Fortune", 100);
			}
			else
			{
				dialog.text = "Nie kupiłem tego naszyjnika po to, by targować się z kimś takim jak ty! To prezent dla mojej żony i nie masz tu czego szukać. Wynocha stąd, póki sam cię stąd nie wyrzuce!";
				link.l1 = "Skoro nie chcesz oddać naszyjnika po dobroci, zabiorę go siłą.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("UV_Ozherelie_Duel");
				notification("Umiejętność zbyt niska (45)", SKILL_Leadership);
			}
		break;

		case "Captain_4_leadership_2":
			dialog.text = "Niech cię diabli i ten przeklęty naszyjnik! Bierz go i znikaj, póki się nie rozmyśliłem.";
			link.l1 = "Rozsądna decyzja! Żegnaj.";
			AddDialogExitQuestFunction("UV_Ozherelie");
			GiveItem2Character(pchar, "SM_necklace_Julie");
		break;

		case "Juli_22":
			dialog.text = ""+pchar.name+", przyniosłeś mi znów radość! Zwróciłeś nie tylko naszyjnik, ale też cząstkę mojej duszy. Twoja szlachetność budzi podziw, i obiecuję, że każdy, kogo spotkam, usłyszy o twojej odwadze!";
			link.l1 = "Ależ proszę, mademoiselle, zwrócił"+GetSexPhrase("em","am")+" go nie dla chwały. Twój uśmiech to jedyna nagroda, na której mi naprawdę zależy.";
			link.l1.go = "Juli_23";
			TakeItemFromCharacter(pchar, "SM_necklace_Julie");
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;

		case "Juli_23":
			dialog.text = "Jesteś tak skromny, "+pchar.name+". Ale proszę, przyjmij tę skrzyneczkę z dublonami. Tylko wiedząc, że przyjąłeś mój dar, poczuję, że odpłaciłam ci się jak należy.";
			link.l1 = "Proszę, nie nalegaj, mademoiselle. Twoje wdzięczne słowa są dla mnie cenniejsze niż jakakolwiek skrzynia złota.";
			link.l1.go = "Juli_24_nobility";
			link.l2 = "Jeśli to cię uspokoi, mademoiselle, przyjmę twój dar. Ale wiedz, że nie dla nagrody to zrobił"+GetSexPhrase("em","am")+". Twoje uznanie znaczy dla mnie więcej niż te dublony.";
			link.l2.go = "Juli_24_chest";
		break;

		case "Juli_24_nobility":
			dialog.text = "Całkiem zapomniałam zapytać – czy wiesz, kto ukradł ten naszyjnik?";
			link.l1 = "Wiem tylko tyle, mademoiselle: naszyjnik trafił do kupca dzięki niejakiej Giselle. I wygląda na to, że to nie pierwszy jej występek.";
			link.l1.go = "Juli_25";
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
		break;

		case "Juli_24_chest":
			dialog.text = "Całkiem zapomniałam zapytać – czy wiesz, kto ukradł ten naszyjnik?";
			link.l1 = "Wiem tylko tyle, mademoiselle: naszyjnik trafił do kupca dzięki niejakiej Giselle. I wygląda na to, że to nie pierwszy jej występek.";
			link.l1.go = "Juli_25";
			GiveItem2Character(PChar, "chest");
		break;
		
		case "Juli_25":
			dialog.text = "Giselle? Moja własna pokojówka! Miałam podejrzenia... ale nie chciałam w to wierzyć. Najgorsze jest to, że nie mogę jej otwarcie ukarać. Mogłaby zdradzić mój sekret, a na to nie mogę sobie pozwolić.";
			link.l1 = "I co zamierza pani zrobić? Pozwolić jej dalej kraść bezkarnie?";
			link.l1.go = "Juli_26";
		break;

		case "Juli_26":
			dialog.text = "O nie, oczywiście, że nie. Najpierw upewnię się, że nie będzie się więcej kręcić w pobliżu mnie. A potem wymyślę sposób, by ją ukarać tak, by wyglądało to na karę zesłaną przez los, a nie przeze mnie.";
			link.l1 = "Pomysłowość kobiet to niebezpieczna broń, zwłaszcza w rękach tak bystrej i przenikliwej damy jak pani. Jestem pewn"+GetSexPhrase("y","a")+", że służąca nawet nie domyśla się, że partia już została rozegrana — i to na jej niekorzyść.";
			link.l1.go = "Juli_27";
		break;

		case "Juli_27":
			dialog.text = "Ach, kapitanie, oczywiście wolałabym uniknąć podstępów, ale... czasem przebiegłość to jedyna droga.";
			link.l1 = "Bez wątpienia, Julie. Niechętnie panią opuszczam, lecz obowiązki wzywają. Kto, jeśli nie ja, zadba o moich marynarzy?";
			link.l1.go = "Juli_28";
		break;

		case "Juli_28":
			dialog.text = "Do zobaczenia, "+pchar.name+". Proszę, odwiedzaj nasz port częściej. Naszemu miastu tak bardzo brakuje "+GetSexPhrase("tak szlachetnych i dzielnych mężczyzn jak pan.","dziewcząt o tak szlachetnym sercu i zdecydowanym duchu jak pani.")+"";
			link.l1 = "Pani mi schlebia, mademoiselle. Obiecuję, że nie przegapię żadnej okazji, by znów odwiedzić to piękne miasto. Do zobaczenia wkrótce.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("UV_Juli_GoodEnd");
		break;
		
		case "Juli_31":	
			if (CheckAttribute(pchar, "questTemp.UV_ojerelie_Julie"))
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = ""+pchar.name+"! Co za niespodziewane spotkanie! Nadal podbijasz morza?";
						link.l1 = "Miło cię widzieć, mademoiselle. Podbijam, jak mogę, choć morze jak zwykle kapryśne. A ty? Mam nadzieję, że cieszysz się spokojem?";
						link.l1.go = "Juli_32";
					break;

					case 1:
						dialog.text = "Ach, kapitanie "+pchar.lastname+", jakże się cieszę, że cię widzę! Mam nadzieję, że twoje sprawy mają się dobrze?";
						link.l1 = "Miło cię widzieć, mademoiselle. Sprawy, jak zwykle, wymagają czasu i wysiłku, ale takie spotkania jak to rozjaśniają każdy dzień. A jak mija twój czas?";
						link.l1.go = "Juli_33";
					break;
				}
			}
			else
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = "Kapitanie "+pchar.lastname+",  znowu tutaj? Czyżby w naszym skromnym miasteczku zostały jeszcze osoby, których nie zdążył"+GetSexPhrase("eś","aś")+"  zdradzić dla garści złota?";
						link.l1 = "Mademoiselle, rozumiem twoje uczucia, ale postąpił"+GetSexPhrase("em","am")+" tak, jak uważał"+GetSexPhrase("em","am")+" za słuszne. Czasami właściwe decyzje ranią, i żałuję, że cię to zabolało.";
						link.l1.go = "exit";
						NextDiag.TempNode = "Juli_34_zlaya";
					break;

					case 1:
						dialog.text = "Kapitanie "+pchar.lastname+", znowu ty? Czyżby twa chciwość była tak wielka, że nie może pan zostawić naszego miasta w spokoju i szuka nowej ofiary?";
						link.l1 = "Mademoiselle, przykro mi, że moje działania tak na ciebie wpłynęły, ale postąpił"+GetSexPhrase("em","am")+" tak, jak uważałem za słuszne.";
						link.l1.go = "exit";
						NextDiag.TempNode = "Juli_34_zlaya";
					break;
				}
			}
			SetTimerFunction("UV_Julie_HelloAgain", 0, 0, 1);
		break;

		case "Juli_32":	
			dialog.text = "Ostatnio naprawdę panuje tu cisza i spokój, nic nie zakłóca tej idylli. Odwiedzaj nasz port częściej, kapitanie. Jestem pewna, że tutaj, w naszym sklepie i poza nim, znajdziesz wszystko, czego dusza zapragnie.";
			link.l1 = "Dziękuję, mademoiselle. Postaram się zaglądać częściej. Jestem pewn"+GetSexPhrase("y","a")+", że wasze miasto jeszcze nie raz mnie miło zaskoczy.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Juli_repeat_residence_1";
		break;

		case "Juli_33":	
			dialog.text = "Dzięki tobie, kapitanie, wszystko stało się znacznie spokojniejsze. Mam nadzieję, że jeszcze nie raz zaszczycisz nas swoją obecnością.";
			link.l1 = "Oczywiście, mademoiselle. Wasze miasto zawsze pozostawia po sobie miłe wrażenia. Do zobaczenia.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Juli_repeat_residence_1";
		break;
		
			case "Juli_repeat_residence_1":
			switch (rand(1))
			{
				case 0:
					dialog.text = "Kapitanie "+pchar.lastname+", spotykamy się ponownie. Niesamowite, prawda?";
					link.l1 = "Zdaje się, że los dziś sprzyja naszym spotkaniom, mademoiselle.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_repeat_residence_1";
				break;

				case 1:
					dialog.text = "Kapitanie "+pchar.lastname+", wygląda na to, że nasze drogi znowu się skrzyżowały.";
					link.l1 = "Na to wygląda, mademoiselle. Cieszę się, że znowu cię widzę.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_repeat_residence_1";
				break;
			}
		break;

		case "Juli_34_zlaya":
			switch (rand(1))
			{
				case 0:
					dialog.text = "Wygląda na to, że spotykamy się zbyt często, kapitanie. A może po prostu nie potrafisz trzymać się z dala od tych, których zdradzono?";
					link.l1 = "Mademoiselle, nasze spotkania są przypadkowe, ale rozumiem twoje oburzenie. Mam tylko nadzieję, że z czasem zrozumiesz moje motywy.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_34_zlaya";
				break;

				case 1:
					dialog.text = "Czego jeszcze chcesz? Wątpię, byś miał tyle pecha, by to spotkanie było przypadkowe. A może chcesz przypomnieć mi o swoim nikczemnym czynie?";
					link.l1 = "Mademoiselle, nie mam zamiaru ci się narzucać ani przypominać o przeszłości. To spotkanie jest naprawdę przypadkowe.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_34_zlaya";
				break;
			}
		break;
		
		
		
		
		
		
		
		
	}
}
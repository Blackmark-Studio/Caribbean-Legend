
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		////// Леа Карно //////
		
		case "Exit":
			DialogExit();
		break;
		
		case "First Time":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+"! Przepraszam... czy jesteś "+GetSexPhrase("marynarzem","")+"?";
			link.l1 = "Kapitan "+GetFullName(pchar)+", do usług.";
			link.l1.go = "Lea First Talk";
			DelLandQuestMark(npchar);
		break;

		case "Lea First Talk":
			dialog.text = "Jestem Lea. Lea Carnot... "+GetSexPhrase("Monsieur","Mademoiselle")+" kapitanie, czy jesteś tu od dawna? Nie "+GetSexPhrase("widziałeś","widziałaś")+" przypadkiem na morzu kutra rybackiego 'Kormoran'? Widzisz... mój mąż, Pierre... wypłynął dwa dni temu i nie wrócił.";
			link.l1 = "'Kormoran'? Nie, nie widział"+GetSexPhrase("em","am")+" takiego kutra. Tę nazwę bym zapamiętał"+GetSexPhrase("","a")+". Przykro mi to słyszeć, madame. Mam nadzieję, że z pana mężem wszystko w porządku i po prostu się gdzieś zatrzymał.";
			link.l1.go = "Lea First Talk Rep Plus";
			link.l2 = "'Kormoran'? Ha, ha! To nazwa statku czy przezwisko właściciela? W sumie bez różnicy. Nie widział"+GetSexPhrase("em","am")+" ani jednego, ani drugiego.";
			link.l2.go = "Lea First Talk Rep Minus";
		break;

		case "Lea First Talk Rep Plus":
			dialog.text = "Nie wiem, co o tym myśleć... Nigdy się tak nie spóźniał. Zawsze wracał przed południem. A teraz... Coś się stało. Czuję to.";
			link.l1 = "Zgłoś się do władz. Wyślą statek patrolowy, by przeszukał wody przybrzeżne.";
			link.l1.go = "Lea First Talk1";
			ChangeCharacterComplexReputation(pchar,"nobility", 3);
		break;

		case "Lea First Talk Rep Minus":
			dialog.text = "Nie wiem, co o tym myśleć... Nigdy się tak nie spóźniał. Zawsze wracał przed południem. A teraz... Coś się stało. Czuję to.";
			link.l1 = "Zgłoś się do władz. Wyślą statek patrolowy, by przeszukał wody przybrzeżne.";
			link.l1.go = "Lea First Talk1";
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
		break;

		case "Lea First Talk1":
			dialog.text = "Ależ "+GetSexPhrase("monsieur","mademoiselle")+" kapitanie, oczywiście, już byłam u komendanta. Ale co z tego? Rozłożył tylko ręce... Powiedział, że nie ma teraz wolnych jednostek, które mógłby wysłać na poszukiwania mojego męża.\nA ja co mogę? Tylko stać tu, patrzeć w horyzont, czekać... i mieć nadzieję.";
			link.l1 = "Nie trać nadziei, madame Lea. Myślę, że znajdę dzień, by pomóc wam w poszukiwaniach.";
			link.l1.go = "Agree To Help";
			link.l2 = "Dlaczego tak panikujesz? Może poranny wiatr zdmuchnął go prosto w ramiona jakiejś czarującej damy. Posnuje się trochę, nawdycha świeżego powietrza i wróci.";
			link.l2.go = "bad joke";
			link.l3 = "Rada? Przestań mrużyć oczy w stronę horyzontu i idź do karczmy w Le François. Może tam znajdziesz swego małżonka. Przebacz mi szczerość, ale może po prostu robi sobie przerwę od domowych obowiązków, a ty robisz z tego tragedię. Powodzenia.";
			link.l3.go = "Rejection";
		break;

		case "Agree To Help":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" kapitanie, ja... nawet nie wiem, jak ci dziękować... Nie masz pojęcia, co to dla mnie znaczy! Wszyscy tylko rozkładają ręce... Ale ty... ty chcesz pomóc. Dziękuję!";
			link.l1 = "Na podziękowania przyjdzie czas. Lepiej powiedz, gdzie zazwyczaj łowił twój mąż. Miał swoje miejsce czy zmieniał je często?";
			link.l1.go = "Go To Help";
		break;
		
		case "bad joke":
			dialog.text = "Czarująca dama?! Czy naprawdę uważa "+GetSexPhrase("Monsieur","Mademoiselle")+", że to odpowiednia sytuacja na żarty? Czuję, że jest w niebezpieczeństwie... A "+GetSexPhrase("Monsieur","Mademoiselle")+" śmieje się z mojego bólu! (płacze) Wszystko na świecie jest teraz przeciwko mnie. Nikt nie chce pomóc... Nikt nie rozumie, jak trudne to jest dla mnie.";
			link.l1 = "Madame Lea, na miłość boską, proszę wybaczyć moją nietaktowność. Z pewnością nie chciałem"+GetSexPhrase("","a")+" urazić! Obiecuję, że rozpocznę poszukiwania pani męża. Proszę tylko powiedzieć, od czego mam zacząć.";
			link.l1.go = "bad joke1";
		break;

		case "bad joke1":
			dialog.text = GetSexPhrase("Monsieur","Mademoiselle")+"..? Naprawdę chce mi "+GetSexPhrase("Monsieur","Mademoiselle")+" pomóc?";
			link.l1 = "Oczywiście. To najmniej, co mogę zrobić, aby wynagrodzić mój niewybaczalny, niestosowny żart.";
			link.l1.go = "bad joke2";
		break;

		case "bad joke2":
			dialog.text = "Dziękuję, "+GetSexPhrase("Monsieur","Mademoiselle")+" kapitanie. Dziękuję... Naprawdę, zaskoczył"+GetSexPhrase("","aś")+" mnie "+GetSexPhrase("Monsieur","Mademoiselle")+", nawet nie wiem, co powiedzieć...";
			link.l1 = "Za wcześnie, by mi dziękować. Lepiej proszę mi powiedzieć, gdzie pani mąż zwykle łowił ryby. Czy miał stałe miejsce, czy często wybierał nowe?";
			link.l1.go = "Go To Help";
		break;

		case "Go To Help":
			dialog.text = "No cóż... Pierre... Rzadko mówił, gdzie dokładnie łowił ryby. Nazywał to 'swoją tajemnicą'. Ale jeśli to pomoże go znaleźć... Może... Nie wiem... "+GetSexPhrase("Monsieur","Mademoiselle")+" naprawdę chce pomóc? Naprawdę?";
			link.l1 = "Zastanawia się pani, czy powiedzieć mi o sekretnym miejscu swojego męża? Zapewniam, że ten rodzinny sekret pozostanie tylko między nami, daję słowo kapitana. Muszę wiedzieć, gdzie rozpocząć poszukiwania, by nie tracić cennego czasu.";
			link.l1.go = "Go To Help1";
		break;

		case "Go To Help1":
			dialog.text = "Ma "+GetSexPhrase("Monsieur","Mademoiselle")+" rację, kapitanie... Przepraszam. To miejsce było tak ważne dla Pierre’a. Zawsze mówił, że to jego jedyna tajemnica, jego mały sekret\nAle wiem, gdzie ono jest. Jeśli to pomoże go odnaleźć... Łowił ryby przy zatoce Le Marin. To południowe wybrzeże, niedaleko od miasta. Proszę, znajdźcie go, błagam!";
			link.l1 = "Spokojnie, Lea, wszystko będzie dobrze. Zrobię wszystko, co w mojej mocy. Czy miał wrogów? Może ktoś mu groził?";
			link.l1.go = "Go To Help2";
		break;

		case "Go To Help2":
			dialog.text = "Wrogowie? Pierre? Był najżyczliwszym człowiekiem na świecie! Nikomu nie zrobiłby krzywdy... Był tylko prostym rybakiem. Komu mógł przeszkadzać? Nie rozumiem, co mogło się wydarzyć... To wszystko jest takie dziwne... i przerażające...";
			link.l1 = "Proszę się nie martwić, Madame Lea. Natychmiast wyruszę na poszukiwania. Jestem pewien"+GetSexPhrase("","a")+", że z pani mężem wszystko w porządku. Z pewnością wrócę go w pani troskliwe ramiona. Proszę trzymać się dzielnie.";
			link.l1.go = "Return Lea Exit";
		break;

		case "Return back to Lea":
			dialog.text = GetSexPhrase("Monsieur","Mademoiselle")+" kapitanie, proszę powiedzieć, czy są jakieś wieści? Czy dowiedział"+GetSexPhrase("","a")+" się "+GetSexPhrase("Monsieur","Mademoiselle")+" czegoś? Cokolwiek?";
			link.l1 = "Niestety, jeszcze nie, Madame, ale wciąż szukam!";
			link.l1.go = "Exit";
		break;
		
		case "Return Lea Exit":
			DialogExit();
			npchar.dialog.currentnode = "Return back to Lea";
			AddQuestRecord("VPVL", "2"); 
			DoQuestCheckDelay("VPVL_Start", 0.1);
		break;
		
		case "Rejection":
			DialogExit();
			npchar.dialog.currentnode = "Rejection1";
			SetTimerCondition("VPVL_ClearLea", 0, 0, 2, false);  // Удаляем Леа через 2 дня
			CloseQuestHeader("VPVL");
		break;
		
		case "Rejection1":
			dialog.text = "Czego jeszcze chce "+GetSexPhrase("Monsieur","Mademoiselle")+"? Nie wystarczyło naśmiewania się z biednej kobiety?";
			link.l1 = "...";
			link.l1.go = "Exit";
		break;

		case "Lea second talk":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" kapitanie! Pierre! Jakże się cieszę, że was widzę! Udało się tobie go odnaleźć!";
			link.l1 = "Lea, pozwólcie, że przedstawię - Pierre Carno we własnej osobie. Nie mogę powiedzieć, że cały i zdrowy, ale jestem pewn"+GetSexPhrase("y","a")+", że pani troska szybko go uleczy!";
			link.l1.go = "Lea second talk1";
			locCameraFromToPos(-7.58, 3.1, 82.5, false, -10, -15, 0);
		break;

		case "Lea second talk1":
			dialog.text = "Pierre! Przenajświętsza Dziewico Maryjo! Tak się o ciebie martwiłam! Gdzie byłeś? Twarz masz jakbyś wrócił z zaświatów... Jesteś cały blady... Ojej! Co to?! Co to za... okropne rany?! Cięcia... i oparzenia...";
			link.l1 = "Wszystko dobrze, moja ukochana. To tylko zadrapania. Cieszę się, że znów cię widzę! Gdyby nie kapitan... zawdzięczam mu życie.";
			link.l1.go = "Lea second talk2";
			CharacterTurnByChr(npchar, CharacterFromID("VPVL_Pier_carno"));
			sld = CharacterFromID("VPVL_Pier_carno");
			CharacterTurnByChr(sld, CharacterFromID("VPVL_Lea_girl"));
			locCameraFromToPos(-7.62, 3.1, 83.26, false, 30, -15, 0);
		break;

		case "Lea second talk2":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" kapitanie... ja... nawet nie wiem, jak ci dziękować... odnalazł się! Mój Pierre! Dziękuję ci... dziękuję za wszystko! Niech Bóg cie chroni, "+GetSexPhrase("Monsieur","Mademoiselle")+" kapitanie!";
			link.l1 = "Dajmy już spokój podziękowaniom. Teraz najważniejsze, by Pierre dobrze zjadł i odpoczął.";
			link.l1.go = "Exit";
			CharacterTurnByChr(npchar, CharacterFromID("Blaze"));
			locCameraFromToPos(-7.58, 3.1, 82.5, false, -10, -15, 0);
			AddDialogExitQuest("VPVL_PierTalkOnThePirs");
		break;
		
		case "Kontr Le Maren":
			dialog.text = "No nareszcie się pojawił"+GetSexPhrase("eś","aś")+", "+GetSexPhrase("psie","ladacznico")+"! Gdzie cię do diabła nosiło? Siedzimy tu już trzy dni na tej plaży, gotując się w upale! Gdzie nasz ładunek?!";
			link.l1 = "Wygląda na to, że bez mnie nie zacznie się zabawa, co, panowie? No cóż, trochę się spóźnił"+GetSexPhrase("em","am")+", ale lepiej późno niż wcale!";
			link.l1.go = "Exit_Sneak";
			link.l2 = "To do mnie? Hm, może najpierw nauczcie się manier, zanim zaczniecie zadawać pytania?";
			link.l2.go = "Exit_Lucky";
			//locCameraFromToPos(-3.35, 2.23, 6.93, false, 20, -1, 10);
			locCameraFromToPos(-5.73, 2.45, 5.75, true, -0.53, 0.40, 7.17);
			DeleteAttribute(pchar, "questTemp.VPVL_Contr_V_Lemaren");
		break;
		
		case "Exit_Sneak":
			DialogExit();
			sld = CharacterFromID("VPVL_contr_1");
			sld.dialog.filename = "Quest\MiniEvents\VPVL_dialog.c";
			sld.dialog.currentnode = "Kontr Le Maren0";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddCharacterExpToSkill(pchar, "Sneak", 50);
			notification("Zdobyto doświadczenie", SKILL_SNEAK);
		break;
		
		case "Exit_Lucky":
			DialogExit();
			sld = CharacterFromID("VPVL_contr_1");
			sld.dialog.filename = "Quest\MiniEvents\VPVL_dialog.c";
			sld.dialog.currentnode = "Kontr Le Maren0";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			notification("Zdobyto doświadczenie", SKILL_FORTUNE);
		break;

		case "Kontr Le Maren0":
			sld = CharacterFromID("VPVL_contr_2");
			dialog.text = ""+sld.name+", ty tępa buło! Otwórz oczy, głupcze – to w ogóle nie nasz człowiek!";
			link.l1 = "Arrgh... Jeszcze jedna psina gubernatora! Pewne jak przypływ! Skoro ta głupia kobieta sama się tu przywlekła, wrzućmy ją do jaskini z jej przyjacielem. Będziemy się dobrze bawić! A przy okazji wyciągniemy z niej wszystko, co wie o planach swojego pana.";
			if (pchar.sex == "man")
			{
				link.l1 = "Arrgh... Jeszcze jeden z psów gubernatora! Pewne jak przypływ! Skoro ten łotr sam się tu przyniósł, zawleczmy go do jaskini do jego kumpla. Pokażemy mu, jak wyciągamy sekrety – zaraz wyśpiewa wszystkie nikczemne zamiary swego pana!";
			}
			link.l1.go = "Kontr Le Maren1";
			locCameraFromToPos(-3.40, 2.38, 5.79, true, -0.49, 0.5, 7.59);
			CharacterTurnByChr(sld, CharacterFromID("VPVL_contr_1"));
			
			sld = CharacterFromID("VPVL_contr_1");
			CharacterTurnByChr(sld, CharacterFromID("VPVL_contr_2"));
		break;

		case "Kontr Le Maren1":
			dialog.text = "Co się tak rozmarzyłeś, bydlaku? Ślinę sobie otrzyj! Lepiej sprzedajmy ją... wiesz komu. Za taką panienkę dostaniemy worek monet, a potem hulanka przez miesiąc!";
			if (pchar.sex == "man")
			{
				dialog.text = "Na co nam jeszcze jedna małpa w jaskini? Przypuśćmy większy nacisk na jego wspólnika – i tak wszystko wyśpiewa. A tego zabijmy na miejscu, żeby nam oczu nie raził!";
			}
			link.l1 = "Niech cię tysiąc rekinów pożre, Simon! Jesteś najbardziej przebiegłym przemytnikiem w całym archipelagu!";
			link.l1.go = "Kontr Le Maren2";
		break;
		
		case "Kontr Le Maren2":
			dialog.text = "...";
			if (GetSummonSkillFromName(pchar, SKILL_PISTOL) >= 20)
			{
				if(GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE) == "") {	
				notification("Nie masz pistoletu!", "NONE");
				link.l2 = "Jeśli ten tu to najbystrzejszy z was, aż strach pomyśleć, jaką głupotę mają w głowach pozostali!";
				link.l2.go = "Kontr Le Maren3";
				CharacterTurnByChr(npchar, CharacterFromID("Blaze"));
				//locCameraFromToPos(-3.35, 2.23, 6.93, false, 20, -1, 10);
				CharacterTurnByChr(npchar, CharacterFromID("Blaze"));
				sld = CharacterFromID("VPVL_contr_1");
				CharacterTurnByChr(sld, CharacterFromID("Blaze"));
				}
				else
				{
				link.l1 = " (Do siebie)(Pistolety) Gdy te szczury morskie trajkoczą swoje bzdury, mam okazję zadać nagły cios.";
				link.l1.go = "murder";
				notification("Sukces!", SKILL_PISTOL);
				locCameraFromToPos(-5.73, 2.45, 5.75, true, -0.53, 0.40, 7.17);
				}
			}
			if (GetSummonSkillFromName(pchar, SKILL_PISTOL) < 20)
			{
			notification("Umiejętność zbyt niska (20)", SKILL_PISTOL);
			CharacterTurnByChr(npchar, CharacterFromID("Blaze"));
			sld = CharacterFromID("VPVL_contr_2");
			CharacterTurnByChr(sld, CharacterFromID("Blaze"));
			locCameraFromToPos(-5.73, 2.45, 5.75, true, -0.53, 0.40, 7.17);
			}
			link.l2 = "Jeśli ten tu to najbystrzejszy z was, aż strach pomyśleć, jaką głupotę mają w głowach pozostali!";
			link.l2.go = "Kontr Le Maren3";
		break;

		case "Kontr Le Maren3":
			dialog.text = "Zaraz wyrwę ci język, "+GetSexPhrase("bezczelny kundlu","brudna szmato")+", żebyś więcej nie szczekał"+GetSexPhrase("","a")+"!";
			link.l1 = "Wyrwiesz? No to spróbuj.";
			link.l1.go = "Kontr Le Maren Fight";
			CharacterTurnByChr(pchar, CharacterFromID("VPVL_contr_1"));
		break;
		
		case "Kontr Le Maren Fight":
			DialogExit();
			AddDialogExitQuest("VPVL_EveryoneFight");
			LAi_LocationFightDisable(&Locations[FindLocation("Shore39")], false);
			EndQuestMovie();
		break;
		
		case "murder":
			DialogExit();
			AddDialogExitQuest("VPVL_Pistol_Murder");
			locCameraFromToPos(-5.04, 2.62, 8.65, false, 20, -6, -15);
		break;
		
				case "PierFirstTalk":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+"... Proszę wybaczyć... Nic już nie rozumiem... Czy jesteś tu, by mnie zabić?";
			link.l1 = "Pan jest Pierre Carno?";
			link.l1.go = "Pier_1";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.VPVL_SetFlagLeMaren");
		break;

		case "Pier_1":
			dialog.text = "Tak, to ja. Zna pan"+GetSexPhrase("","i")+" moje imię?";
			link.l1 = "Oczywiście, w przeciwnym razie co bym tu robił"+GetSexPhrase("","a")+"...";
			link.l1.go = "Pier_2";
		break;

		case "Pier_2":
			dialog.text = "Proszę wybaczyć, nic nie rozumiem... Ból i głód odebrały mi zdolność jasnego myślenia... Dlaczego pan"+GetSexPhrase("","i")+" tu "+GetSexPhrase("przyszedł","przyszła");
			link.l1 = "To proste. Od chwili pana zaginięcia pańska wierna żona czuwa przy molo, wypatrując żagli 'Kormorana'. Jej rozpacz była tak przejmująca, że nie mogłem"+GetSexPhrase("","am")+" przejść obojętnie i postanowiłem"+GetSexPhrase("","am")+" wyruszyć na poszukiwania.";
			link.l1.go = "Pier_3";
		break;

		case "Pier_3":
			dialog.text = "Moja żona... moja droga Lea... Byłem pewien, że nigdy więcej jej nie zobaczę...";
			link.l1 = "To już za nami. Ona nadal czeka na pana przy przystani, nie tracąc nadziei. Chodźmy stąd. Pomogę panu wstać.";
			link.l1.go = "Pier_4";
		break;

		case "Pier_4":
			dialog.text = "Uff... Proszę wybaczyć, "+GetSexPhrase("Monsieur","Mademoiselle")+"... potrzebuję chwili... nogi odmawiają posłuszeństwa, całkowicie zdrętwiały... dziękuję z całego serca, gdyby nie pan"+GetSexPhrase("","i")+"... Sam Bóg chyba pan"+GetSexPhrase("a","i")+" zesłał... Nie "+GetSexPhrase("przedstawił się pan","przedstawiła się pani")+". Jak mogę się do pan"+GetSexPhrase("a","i")+" zwracać?";
			link.l1 = "Kapitan "+GetFullName(pchar)+". Proszę dojść do siebie i opowiedzieć, jak pan się tu znalazł? Czy miał pan zamiar prowadzić interesy z tymi... ludźmi?";
			link.l1.go = "Pier_5";
			LAi_Fade("VPVL_PierStay", "");
		break;

		case "Pier_5":
			dialog.text = "Skądże znowu, kapitanie. Nie zajmuję się takimi sprawami – jestem zwykłym rybakiem. Dzień zaczął się dobrze. Łowiłem ryby na zachodniej stronie zatoki. Połów był niesamowity\nTak się spieszyłem, by rozdzielić ryby do beczek i znowu zarzucić sieci, że zupełnie nie zauważyłem, jak łódź poniosło ku rafom. Burty ma jak skorupka – wystarczył lekki cios i woda wdarła się do środka. 'Kormoran', już ciężki od ryb, szybko poszedł na dno.";
			link.l1 = "A potem dopłynął pan do brzegu, i ci przemytnicy uznali pana za szpiega gubernatora?";
			link.l1.go = "Pier_6";
		break;

		case "Pier_6":
			dialog.text = "Dokładnie tak. Ledwo dotarłem do brzegu przez te przeklęte fale. Musiałem się wysuszyć, odpocząć i zebrać siły, zanim ruszę do miasta. Wszystko potoczyło się bardzo szybko... Gdy w końcu się zdecydowałem, natknąłem się na tych łotrów\nNatychmiast uznali mnie za agenta gubernatora. Nie zdążyłem nawet słowa powiedzieć, a już byłem związany i przyprowadzony tutaj. Przez dwa dni mnie torturowali i głodzili, żądając, bym zdradził wszystkich tajnych agentów gubernatora i jego plany. Ale jak mogłem wyjawić coś, o czym nie mam pojęcia?";
			link.l1 = "Rozumu tym drabom nie starczyło, więc w piachu już leżą. To już za nami. Jest pan wolny. Czas rozweselić pańską żonę – z pewnością jest wyczerpana zmartwieniem.";
			link.l1.go = "Pier_7";
		break;

		case "Pier_7":
			dialog.text = "Tak bardzo chcę ją znów objąć. Chyba już dam radę iść.";
			link.l1 = "W takim razie nie traćmy czasu.";
			link.l1.go = "exit_grot";
		break;
		
		case "exit_grot":
			DialogExit();  
			AddQuestRecord("VPVL", "4");
			AddDialogExitQuest("VPVL_PierFollow");
		break;
		
		case "PierInThePirs":
			dialog.text = "Kapitanie, proszę przyjść jutro wieczorem o szóstej do karczmy. Nie wybaczę sobie, jeśli nie podziękuję "+GetSexPhrase("panu","pani")+" należycie. Teraz... teraz nie potrafię znaleźć słów, które oddałyby moją wdzięczność. Proszę, przyjdź. To dla mnie bardzo ważne.";
			link.l1 = "Dobrze, Pierre, proszę się nie martwić, przyjdę.";
			link.l1.go = "GoHome";
			locCameraFromToPos(-8.28, 3.1, 82.93, false, 40, -15, 0);
		break;

		case "GoHome":
			DialogExit();
			AddQuestRecord("VPVL", "5");
			AddDialogExitQuest("VPVL_KarnoGoHome");
		break;

		case "PierTalkTavern":
			dialog.text = "Kapitanie! A jednak jesteś! Proszę usiąść.";
			link.l1 = "Z przyjemnością!";
			link.l1.go = "PierTalkTavern1";
			LAi_Fade("VPVL_SitOnTheTable", "");
			FreeSitLocator("FortFrance_Tavern", "sit6");  // Na wszelki wypadek
			DeleteAttribute(pchar, "questTemp.VPVL_Magor_Dialogue");
			pchar.questTemp.VPVL_DontSpawnSmugglersShipPier = true;
			DelLandQuestMark(npchar);
			AddDialogExitQuest("VPVL_KillCapitanOfSmuggler");
			locCameraFromToPos(-2.87, 1.37, -1.09, false, 0, -0.8, -0.90);
		break;

		case "PierTalkTavern1":
			dialog.text = "Wznieśmy więc kufle za pańskie zdrowie!";
			link.l1 = "Nie tylko za moje, ale i za pana! Wygląda pan o wiele lepiej niż wtedy w jaskini. Na zdrowie!";
			link.l1.go = "PierTalkTavern2";
		break;

		case "PierTalkTavern2":
			dialog.text = "Kapitanie, pozwól wyrazić moją bezgraniczną wdzięczność! Nie odwrócił"+GetSexPhrase("eś","aś")+" wzroku, nie przesz"+GetSexPhrase("edłeś","łaś")+" obojętnie, pomogł"+GetSexPhrase("eś","aś")+" zupełnie obcemu człowiekowi, zwykłemu rybakowi. Pańska szlachetność zasługuje na podziw i chcę wynagrodzić to wszystkim, co mam. Proszę. Weź. Tu jest dwadzieścia kawałków bursztynu i pięć rzadkich błękitnych. Znalazłem je przy zatopionym statku. Teraz należą do ciebie. A także chciałbym oddać tobie swoje morskie przyrządy. Póki nie będę miał nowej łodzi, nie będą mi potrzebne.";
			link.l1 = "Dziękuję, Pierre, bardzo mi się przydadzą. Ale najważniejsze, że jest pan znowu w domu, a pańska żona nie będzie już żyć w niepokoju. Teraz wszystko się ułoży.";
			link.l1.go = "PierTakeGift";
			link.l2 = "Pierre, dziękuję za hojność, ale proszę zatrzymać to dla siebie. Bardziej się panu przydadzą – trzeba naprawić łódź, kupić osprzęt, sieci, beczki. Mnie wystarczy pana wdzięczność i to, że znów jesteście razem z żoną. Dbajcie o siebie!";
			link.l2.go = "PierWontGift1";
		break;

		case "PierTakeGift":
			dialog.text = "Wciąż nie mogę uwierzyć, że to wszystko mi się przydarzyło. Wznieśmy toast za nowy rozdział w życiu mojej rodziny i za pańską szlachetność, kapitanie!";
			link.l1 = "I za szczęście, Pierre. Przyda się każdemu z nas!";
			link.l1.go = "ZastavkaVPVL";
			AddItems(PChar, "jewelry8", 20);
			AddItems(PChar, "jewelry7", 5);
			AddItems(PChar, "A_map_martiniqua", 1);
			AddItems(PChar, "spyglass3", 1);
			AddItems(PChar, "obereg_7", 1);
		break;
		
		case "PierWontGift1":
			dialog.text = "Kapitanie, po prostu nie mogę tak tego zostawić... Ocalił"+GetSexPhrase("","a")+" mi pan"+GetSexPhrase("","i")+" życie i jestem winien wszystko. Skoro nie przyjmiesz bursztynu i innych darów, pozwól chociaż nauczyć twoich ludzi łowić ryby na płytkich wodach. Będą mieli świeże jedzenie, a pan"+GetSexPhrase("","i")+" oszczędzi na zapasach. Co powiesz?";
			link.l1 = "To świetny pomysł! Jak mawiają – nie dawaj chleba za darmo, naucz orać, a sam się naje i innych nakarmi.";
			link.l1.go = "PierWontGift2";
			pchar.questTemp.VPVL_Food = true;
		break;

		case "PierWontGift2":
			dialog.text = "Mądre słowa, kapitanie! Cieszę się, że mogę być użyteczny. No, po kieliszeczku?";
			link.l1 = "Za pańskie zdrowie i pomyślność, Pierre!";
			link.l1.go = "ZastavkaVPVL";
		break;

		case "ZastavkaVPVL":
			DialogExit();
			SetLaunchFrameFormParam("Minęły cztery godziny...", "VPVL_SitOnTheTable", 2, 2);
			LaunchFrameForm();
			locCameraFromToPos(-2.87, 1.37, -1.09, false, 0, -0.8, -0.90);
			sld = CharacterFromID("VPVL_Pier_carno");
			sld.dialog.currentnode = "PierTalkTavern3";
			LAi_SetActorType(pchar);
			LAi_ActorDialog(pchar, sld, "", -1, 0);
		break;
		
		case "PierTalkTavern3":
			if(CheckAttribute(pchar, "questTemp.VPVL_Food"))
			{
				int foodDays = CalculateShipFood(&pchar);
				dialog.text = "Mocny trunek! Czuję, że jeszcze łyk, dwa i... hik... zaraz zacznę wyć szantę na całe miasto!";
				link.l1 = "Zostawmy pieśń na później, Pierre... na inną okazję. Bo... hik... pan mnie też rozgrzeje. A ja... eh... muszę ruszać, sprawy... zdaje się... czekają! Dbajcie o siebie... hik... i o żonę!";
				link.l1.go = "PierTalkTavern4";
				WaitDate("", 0, 0, 0, 4, 10);
				LAi_AlcoholSetDrunk(pchar, 71, 5600);
				notification("Zużycie prowiantu na statku -15%", "None");
			}
			else
			{
				dialog.text = "Mocny trunek! Czuję, że jeszcze łyk, dwa i... hik... zaraz zacznę wyć szantę na całe miasto!";
				link.l1 = "Zostawmy pieśń na później, Pierre... na inną okazję. Bo... hik... pan mnie też rozgrzeje. A ja... eh... muszę ruszać, sprawy... zdaje się... czekają! Dbajcie o siebie... hik... i o żonę!";
				link.l1.go = "PierTalkTavern4";
				WaitDate("", 0, 0, 0, 4, 10);
				LAi_AlcoholSetDrunk(pchar, 71, 5600);
			}
		break;

		case "PierTalkTavern4":
			dialog.text = "Ach, kapitanie... no wie pan"+GetSexPhrase("","i")+"... dziękuję za wszystko! Jestem pan"+GetSexPhrase("a","i")+" dłużnikiem, rozumie pan"+GetSexPhrase("","i")+"? Jeśli tylko znów się pojawicie... zawsze będziecie u nas mile widzian"+GetSexPhrase("y","a")+", jak... jak rodzina! Naprawdę! Ech... wypijemy jeszcze kiedyś!";
			link.l1 = "No to trzymajcie się tu, Pierre... a ja... hik... ruszam, zanim nogi odmówią posłuszeństwa!";
			npchar.dialog.currentnode = "RepeatTavern";
			link.l1.go = "Exit2";
			CloseQuestHeader("VPVL");
		break;

		case "Exit2":
			DialogExit()
			LAi_Fade("VPVL_ExitFromTableVPVL", "VPVL_PierLivingTavern");
			DeleteAttribute(pchar, "questTemp.VPVL_Delete_Ship_RemoveFlag");
		break;

		case "RepeatTavern":
			dialog.text = "Za mo-o-orze, i za wiatr... hik... za rybacki sza-a-ak o świcie!.. Diabli, co tam dalej było? Kapitanie!.. Nadal tu jesteś? Karczmarzu... hik... najlepszy rum na ten stół!";
			link.l1 = "Już wychodzę, Pierre! Hik... póki jeszcze znajdę mój statek!";
			link.l1.go = "Exit";
		break;

		case "MeetingInTneCity":
			dialog.text = ""+pchar.name+"! Jakże miło pan"+GetSexPhrase("a","ią")+" widzieć! Może po kieliszeczku rumu? Za spotkanie!";
			link.l1 = "I ja się cieszę, że pana widzę, Pierre. Ale niestety, tym razem muszę odmówić. Obowiązki nie pozwalają, a głowa musi być trzeźwa. Może następnym razem?";
			link.l1.go = "MeetingInTneCity1";
		break;

		case "MeetingInTneCity1":
			dialog.text = "Oczywiście, kapitanie. Najpierw obowiązki, potem przyjemności. Mam nadzieję, że jeszcze się spotkamy i wtedy na pewno wypijemy!";
			link.l1 = "Na pewno, Pierre. Do zobaczenia!";
			link.l1.go = "Exit";
			npchar.dialog.currentnode = "ExitRepeat";
		break;

		case "ExitRepeat":
			dialog.text = "Kapitanie! Czy już pan"+GetSexPhrase("","i")+" się uwolnił"+GetSexPhrase("","a")+" od obowiązków?";
			link.l1 = "Niestety, Pierre. Obowiązki wciąż mnie trzymają.";
			link.l1.go = "Exit";
		break;
	}
}   
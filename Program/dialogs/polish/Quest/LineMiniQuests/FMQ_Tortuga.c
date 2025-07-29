// Addon-2016 Jason, французские миниквесты (ФМК) Тортуга
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "To oczywisty błąd. Poinformuj o tym deweloperów.";
			link.l1 = "O, zrobię to.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "girl":
			DelMapQuestMarkCity("Tortuga");
			LAi_SetImmortal(npchar, false);
			DelLandQuestMark(npchar);
			LAi_RemoveLoginTime(npchar);
			FMQT_FillChest();
			PlaySound("Voice\English\Girls_1.wav");
			dialog.text = "O, witam monsieur! Witaj na Tortudze! Tacy szlachetni kapitanowie jak ty są tu rzadkimi gośćmi...";
			link.l1 = "Witaj, panienko. Dziękuję za ciepłe powitanie. Ale jak to? Myślałem, że tak ważny port zawsze był miejscem zainteresowania dla dżentelmenów fortuny znacznie szlachetniejszych ode mnie.";
			link.l1.go = "girl_1";
		break;
		
		case "girl_1":
			dialog.text = "Ach monsieur... Jesteś wyraźnie nowicjuszem, prawda? Sam się przekonasz. Nie masz pojęcia, jak trudno jest znaleźć godnych ludzi na bal w pałacu gubernatora. Może zechcesz mi towarzyszyć...?";
			link.l1 = "Jak mogę służyć tak pięknej kobiecie?";
			link.l1.go = "girl_2";
		break;
		
		case "girl_2":
			dialog.text = "Mój, o mój, cóż za galanteria! (chichot) Może zechciałbyś odwiedzić nas dziś wieczorem o szóstej? Żona naszego gubernatora regularnie organizuje nieformalne przyjęcia w kwaterach służby w pałacu. To rzadka okazja, by mieć tak intrygujące towarzystwo na takich wydarzeniach. Czy nas odwiedzisz? Proszę, przyjdź, bylibyśmy przeszczęśliwi.";
			link.l1 = "Byłbym zaszczycony, mademoiselle. Odwiedzę cię dziś wieczorem.";
			link.l1.go = "girl_3";
			link.l2 = "Proszę wybaczyć, panienko, ale mam pilne sprawy do załatwienia. Może innym razem?";
			link.l2.go = "girl_exit";
		break;
		
		case "girl_exit":
			dialog.text = "Co za szkoda. Będę musiała znaleźć kogoś innego, kto dotrzyma towarzystwa mnie i moim przyjaciółkom... Żegnam.";
			link.l1 = "Żegnaj.";
			link.l1.go = "girl_exit_1";
		break;
		
		case "girl_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 40.0);
			npchar.lifeday = 0;
			FMQT_ClearChest();
		break;
		
		case "girl_3":
			dialog.text = "Dziękuję! Obiecuję ci, że to będzie noc, której nigdy nie zapomnisz, monsieur! Au revoir!";
			link.l1 = "Do zobaczenia...";
			link.l1.go = "girl_4";
		break;
		
		case "girl_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 40.0);
			npchar.lifeday = 0;
			pchar.questTemp.FMQT = "begin_serveroom";
			FMQT_Begin();
			AddQuestRecord("FMQ_Tortuga", "1");
		break;
		
		case "girl_5":
			DelMapQuestMarkCity("Tortuga");
			LAi_SetImmortal(npchar, false);
			DelLandQuestMark(npchar);
			LAi_RemoveLoginTime(npchar);
			FMQT_FillChest();
			PlaySound("Voice\English\Girls_1.wav");
			dialog.text = "Hej tam, żeglarzu! Jaki to szczęśliwy wiatr przywiał cię dziś tutaj? Rzadko widujemy takich wspaniałych mężczyzn w Tortudze.";
			link.l1 = "Witaj również, mademoiselle, jesteś skłonna sprawić, że się zaczerwienię od twoich komplementów. Jestem kapitanem własnego statku i zajętym człowiekiem, ale jestem pewny, że ta wyspa może zaoferować wystarczająco dla dzikiego wędrowca takiego jak ja, aby pozostać rozbawionym.";
			link.l1.go = "girl_6";
		break;
		
		case "girl_6":
			dialog.text = "(chichot) Och tak, panie, jestem pewna, że możemy w tym pomóc! Tortuga zawsze ma coś do zaoferowania. Jak i ja... dlatego, jestem skłonna zrobić niemal *wszystko* po usłyszeniu dobrej morskiej opowieści. Tak bardzo je kocham! Pewien kapitan raz opowiedział mi niezwykłą historię o tym, jak udało mu się uniknąć pozostawienia na bezludnej wyspie, budując tratwę z żółwi morskich. Co za dzielny człowiek! Czy ty byś mógł?";
			link.l1 = "Co mógłbym zrobić?";
			link.l1.go = "girl_7";
		break;
		
		case "girl_7":
			dialog.text = "(chichot) Czy mógłbyś zrobić tratwę z żółwi morskich?";
			link.l1 = "Zrobię coś lepszego. Kiedyś jako uciekający czeladnik zdobyłem najszybszy statek w angielskiej marynarce używając jedynie toporka. Potrafię też wstrzymać oddech na dziesięć minut. Chcesz zobaczyć?";
			link.l1.go = "girl_8";
		break;
		
		case "girl_8":
			dialog.text = "Może później. Pracuję jako służąca w pałacu naszego gubernatora. Przyjdź tam dziś wieczorem o szóstej i znajdź mnie i mojego przyjaciela w altanie. Wtedy opowiesz nam o swoich przygodach...";
			link.l1 = "Brzmi jak zaproszenie do pokazu, którego nie mogę odmówić. Do zobaczenia o szóstej wieczorem.";
			link.l1.go = "girl_9";
			link.l2 = "Wkradanie się do pałacu gubernatora? To brzmi trochę zbyt ryzykownie dla mnie. Odpuszczę sobie, kochana. Znajdziesz mnie w karczmie, jeśli chcesz towarzystwa prawdziwego mężczyzny. Jo ho ho!";
			link.l2.go = "girl_exit_2";
		break;
		
		case "girl_exit_2":
			dialog.text = "Phi. Nieważne, znajdę sobie lepszego i większego mężczyznę niż ty. Twoja sakwa wygląda na zbyt małą. Niech cię piekło pochłonie.";
			link.l1 = "Nawet pancernik wyglądałby mały, gdyby płynął przez twoję przejście.";
			link.l1.go = "girl_exit_1";
		break;
		
		case "girl_9":
			dialog.text = "Nie mogę się doczekać!";
			link.l1 = "...";
			link.l1.go = "girl_10";
		break;
		
		case "girl_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 40.0);
			npchar.lifeday = 0;
			pchar.questTemp.FMQT = "begin_bedroom";
			FMQT_Begin();
			AddQuestRecord("FMQ_Tortuga", "2");
		break;
		
		case "wife":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_01.wav");
			dialog.text = "Ah, oto jesteś! Kapitanie "+GetFullName(pchar)+"! Bardzo się cieszę, że mogę cię spotkać, minęło już trochę czasu, odkąd zaszczycił mnie taki gość o takiej szlachetności i randze!";
			link.l1 = "To dla mnie wielki zaszczyt i przyjemność być tutaj w twoim towarzystwie, madame. Ale co z resztą gości? Czy przyszedłem za wcześnie?";
			link.l1.go = "wife_1";
		break;
		
		case "wife_1":
			dialog.text = "Och, są niedysponowani i nie mogą przybyć. Ale nie myśl o nich, napijmy się wina i porozmawiajmy... Ach, gdybyś tylko wiedział, jak nudno i samotnie się tu czuję! Tortuga to plugawa nora pełna szumowin, łotrów i piratów! Piraci! I wreszcie, godny dżentelmen w moim domu! Chciałabym, żeby mój mąż robił więcej interesów z ludźmi twojej klasy i talentów! Ale nie, nic tylko piraci, piraci wszędzie! Czy słyszałeś o tej nowej modzie, która staje się popularna w Paryżu na dworze królewskim Jego Królewskiej Mości? Jaka jest twoja opinia na ten temat?";
			link.l1 = "Przykro mi, moja opinia na temat czego dokładnie? Piratów? Czy mody?";
			link.l1.go = "wife_2";
		break;
		
		case "wife_2":
			dialog.text = "Och, panie, rozumiesz mnie tak dobrze! Nie mogę w to uwierzyć. Mój mąż daje mi grosze, podczas gdy zarabia MILIONY na swoich piratach, wyobraź sobie! Piraci! Muszę zamawiać suknie dostarczane tutaj do tej brudnej dziury, ale kiedy w końcu tu docierają, są już sześć miesięcy przestarzałe! Jak kobieta mojego statusu może nosić takie łachmany? Och, tak bardzo chcę zobaczyć i nosić te paryskie fasony! Myślisz, że wyglądałabym w nich uroczo?";
			link.l1 = "Madame, wyglądasz przepięknie. Nie potrzebujesz mody z Paryża, by to było oczywiste dla każdego mężczyzny tej pięknej wyspy.";
			link.l1.go = "wife_3";
		break;
		
		case "wife_3":
			dialog.text = "Jesteś dla mnie zbyt miły... Kapitanie, muszę wyznać, jestem w wielkich tarapatach. Ale pomożesz biednej kobiecie, prawda?";
			link.l1 = "Oczywiście, madame. Cokolwiek sobie życzysz.";
			link.l1.go = "wife_4";
		break;
		
		case "wife_4":
			dialog.text = "Ostrożnie tam, monsieur kapitanie, bo stracę głowę! (kokieteryjny chichot) Mój mąż ostatnio nie daje mi ani grosza. Ten brutal sprowadza do naszego domu pospolite ladacznice i zupełnie mnie ignoruje!\nWiem, gdzie trzyma część swojego nieuczciwie zdobytego skarbu, jest w skrzyni w jego biurze. To są moje pieniądze z prawa żony i kobiety. Pomóż mi odzyskać to, co mi się należy, a zostaniesz nagrodzony... Złotem i... innymi rozkosznymi rzeczami.";
			link.l1 = "To intrygująca oferta. Dobrze, madame, pomogę ci. Gdzie jest ta skrzynia i jak ją otworzyć?";
			link.l1.go = "wife_5";
			link.l2 = "Bardzo dobrze, madame, zdobędę zawartość skrzyni dla ciebie. Zdobędziemy pieniądze i będziemy mieli bardzo miłą 'rozmowę' po tym. Jaki mężczyzna może odrzucić taką ofertę? Gdzie jest ta skrzynia i jak ją otworzyć?";
			link.l2.go = "wife_6";
			link.l3 = "Madame, próbujesz mnie uwieść. Przykro mi, ale mój honor wymaga, bym odrzucił twoją propozycję. Masz moje współczucie, zasługujesz na coś lepszego, ale będziesz musiała znaleźć sobie innego aktora do swojej sztuki.";
			link.l3.go = "wife_exit";
		break;
		
		case "wife_exit":
			dialog.text = "Szkoda. Nie mamy już o czym rozmawiać, monsieur. Wyjdź i pamiętaj: powiesz o tym mojemu mężowi, a pożałujesz!";
			link.l1 = "Żegnaj.";
			link.l1.go = "wife_exit_1";
		break;
		
		case "wife_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "questTemp.FMQT.Common");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			pchar.questTemp.FMQT = "huber";
			pchar.quest.FMQT_late1.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late1.win_condition.l1.date.hour  = 18.0;
			pchar.quest.FMQT_late1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late1.function = "FMQT_HuberTime";
			AddQuestRecord("FMQ_Tortuga", "4");
		break;
		
		case "wife_5":
			pchar.questTemp.FMQT.Honour = "true"; // вар 1
			dialog.text = "Nie spodziewałam się tego po tobie... Skrzynia... Zostawmy to na później, najpierw musimy znaleźć duplikat klucza, który został skradziony przez brudnego pirata. Teraz baluje w lokalnej spelunce, pijąc jak świnia. Spiesz się i przynieś mi ten duplikat klucza. Będę na ciebie czekać.";
			link.l1 = "Nie traćmy czasu wtedy!";
			link.l1.go = "wife_7";
		break;
		
		case "wife_6":
			pchar.questTemp.FMQT.Bed = "true"; // вар 2 
			dialog.text = "Nie pożałujesz tego, kapitanie. Najpierw musimy znaleźć duplikat klucza, który został skradziony przez plugawego pirata. Teraz biesiaduje w miejscowej spelunce, pijąc jak świnia. Spiesz się i przynieś mi ten duplikat klucza. Będę na ciebie czekała.";
			link.l1 = "Nie traćmy czasu!";
			link.l1.go = "wife_7";
		break;
		
		case "wife_7":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "FMQT_PirateInTavern", 10.0);
			pchar.quest.FMQT_late2.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late2.win_condition.l1.date.hour  = 0.0;
			pchar.quest.FMQT_late2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late2.function = "FMQT_TavernTime";
			AddQuestRecord("FMQ_Tortuga", "6");
		break;
		
		case "wife_8":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_01.wav");
			dialog.text = "Kapitan "+GetFullName(pchar)+"! Prosze prosze! Co za mężczyzna w moich prywatnych komnatach! Jesteś zaskoczony? Jesteś jedynym gościem tej nocy. (chichot)";
			link.l1 = "Jestem zaskoczony, madame. Ale wcale mi to nie przeszkadza. Czy chodzi o interesy czy o przyjemność?";
			link.l1.go = "wife_9";
		break;
		
		case "wife_9":
			dialog.text = "Co za bezpośrednie podejście! Lubię takich mężczyzn jak ty. Mam dla ciebie propozycję biznesową, kapitanie. Znajdę sposób, aby wynagrodzić twoje starania, jeśli odniesiesz sukces.";
			link.l1 = "Kontynuuj.";
			link.l1.go = "wife_10";
		break;
		
		case "wife_10":
			dialog.text = "Ach... Mój mąż ma skrzynię pełną pieniędzy i biżuterii. Nienawidzę go i chcę większego zasiłku za moje cierpienia.";
			link.l1 = "Madame, wyglądasz uroczo. Nie potrzebujesz więcej klejnotów ani paryskich strojów, to już jest oczywiste dla każdego mężczyzny na Hispanioli.";
			link.l1.go = "wife_11";
		break;
		
		case "wife_11":
			dialog.text = "Jesteś dla mnie zbyt dobry... Kapitanie, muszę wyznać, że mam wielkie kłopoty. Czy pomożesz kobiecie w potrzebie??";
			link.l1 = "Oczywiście, madame. Honor tego wymaga. Cokolwiek sobie życzysz.";
			link.l1.go = "wife_12";
		break;
		
		case "wife_12":
			dialog.text = "Uważaj, monsieur kapitanie, bo stracę głowę! (kokieteryjny chichot) Mój mąż ostatnio nie daje mi ani grosza. Ten brutal sprowadza do naszego domu pospolite ladacznice i w ogóle mnie nie zauważa!\nWiem, gdzie ukrywa część swojego nielegalnie zdobytego skarbu, jest w skrzyni w jego biurze. To są moje pieniądze jako żony i kobiety. Pomóż mi odzyskać to, co mi się należy, a zostaniesz nagrodzony... Złotem i... innymi rozkosznymi rzeczami.";
			link.l1 = "Dobrze. Zrobię to. Gdzie jest ta skrzynia i jak ją otworzyć?";
			link.l1.go = "wife_13";
			link.l2 = "Ha! Nie mam pytań, mogę to zrobić dla takiej kobiety jak ty. Nie pożałujesz tego, moja droga. Zdobędziemy pieniądze i spędzimy razem bardzo przyjemny czas. Gdzie jest ta skrzynia i jak ją otworzyć?";
			link.l2.go = "wife_14";
			link.l3 = "Nie ja, madame. Nie jestem takim dżentelmenem, by w jedną noc przyprawić rogi i okraść człowieka. W każdym razie nie w ten sposób. Znajdź sobie innego aktora do tej sztuki.";
			link.l3.go = "wife_exit_2";
		break;
		
		case "wife_13":
			pchar.questTemp.FMQT.Honour = "true"; // вар 1
			dialog.text = "Och... Coraz bardziej mnie intrygujesz... Najpierw powinniśmy odzystać duplikat klucza, który został skradziony przez plugawego pirata. Teraz biesiaduje w miejscowej spelunce, pijąc jak świnia. Pośpiesz się i przynieś mi duplikat. Będę czekała.";
			link.l1 = "Nie traćmy więc czasu!";
			link.l1.go = "wife_7";
		break;
		
		case "wife_14":
			pchar.questTemp.FMQT.Bed = "true"; // вар 2 
			dialog.text = "Zachowaj spokój, monsieur, na to jeszcze przyjdzie czas. (chichot) Najpierw powinniśmy odzystać duplikat klucza, który został skradziony przez parszywego pirata. Bawi się w lokalnej spelunce, pijąc jak świnia. Pośpiesz się i przynieś mi duplikat. Będę na ciebie czekać. Jesteś pewny, że dasz sobie z tym radę?";
			link.l1 = "Nie wątp we mnie, już jestem w drodze.";
			link.l1.go = "wife_7";
		break;
		
		case "wife_exit_2":
			dialog.text = "Purytański draniu! Znikaj mi z oczu! I nawet nie myśl mówić o tym mojemu mężowi, bo pożałujesz!";
			link.l1 = "Żegnaj, kochanie.";
			link.l1.go = "wife_exit_1";
		break;
		
		case "wife_15":
			DelLandQuestMark(npchar);
			pchar.quest.FMQT_late3.over = "yes";
			dialog.text = "Kapitanie! Czy zdobyłeś klucz?";
			link.l1 = "Tak, mam to. Gdzie jest skrzynia?";
			link.l1.go = "wife_16";
		break;
		
		case "wife_16":
			dialog.text = "O! Czy mój nikczemny mąż naprawdę dostanie to, na co zasługuje? Jesteś niesamowitym człowiekiem, kapitanie! Masz przed sobą wielką przyszłość, wiesz o tym? Zapomnij o skrzyni. Sama się tym zajmę. Przyjdź do mnie jutro, by odebrać swoją nagrodę. Nie pożałujesz tego, kapitanie...";
			link.l1 = "Dobrze. Niech będzie po twojemu. Nie mogę się doczekać, by zobaczyć cię jutro.";
			link.l1.go = "wife_17";
			link.l2 = "Nie, jestem zajętym człowiekiem i nie chcę marnować czasu na czekanie. Dlaczego czekać? Powiedz mi, co trzeba zrobić, a ja to zrobię. Nie mogę pozwolić, by taka piękna kobieta psuła sobie delikatne rączki, bawiąc się z zamkiem i kluczem.";
			link.l2.go = "wife_18";
		break;
		
		case "wife_17":
			RemoveItems(pchar, "kaleuche_key", 1);
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key");
			dialog.text = "Przyjdź do mnie przed szóstą, mój dzielny rycerzu...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_Deceive");
		break;
		
		case "wife_18":
			dialog.text = "Jesteś pewien? To może być dla ciebie niebezpieczne. Dlaczego chcesz ryzykować swoje życie, kapitanie?";
			link.l1 = "Dobrze. Niech będzie po twojemu. Czekam na spotkanie z tobą jutro.";
			link.l1.go = "wife_17";
			link.l2 = "Podjąłem już decyzję. Co dokładnie powinienem zrobić?";
			link.l2.go = "wife_19";
		break;
		
		case "wife_19":
			dialog.text = "Lwie serce!... Idź do gabinetu mojego męża, znajdziesz tam skrzynię. Użyj duplikatu klucza. O tej porze nocą nikogo tam nie ma, więc się nie spiesz. W tej skrzyni są... diamenty. Duża ich ilość. Weź je wszystkie i wróć do mnie. Będę czekać. Nie zdradź mojego zaufania... proszę.";
			link.l1 = "Wkrótce wrócę.";
			link.l1.go = "wife_20";
		break;
		
		case "wife_20":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("FMQ_Tortuga", "11");
			sld = &Locations[FindLocation("Tortuga_townhallRoom")];
			sld.private2.key = "kaleuche_key"; // допуск к сундуку
			pchar.questTemp.FMQT = "chest";
		break;
		
		case "wife_21":
			DelLandQuestMark(npchar);
			pchar.quest.FMQT_GemsTimeOver.over = "yes";
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_02.wav");
			dialog.text = "O, kapitanie! Ja... Ty... Udało się? Och, a kto to jest?! A-ah!";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_MercenAttackRoom");
		break;
		
		case "wife_22":
			dialog.text = "O mój Boże! Kapitanie, uratowałeś mnie! Ty... ty jesteś moim bohaterem! To był zbir mojego męża, chciał cię zabić! Błagałam go, żeby tego nie robił! Czy jesteś ranny? Czy przyniosłeś diamenty?";
			link.l1 = "Ha. Naprawdę? Twój mąż to zazdrosny człowiek... Nieważne. Do diabła z nim, mam kamienie.";
			link.l1.go = "wife_23";
		break;
		
		case "wife_21x":
			DelLandQuestMark(npchar);
			pchar.quest.FMQT_GemsTimeOver.over = "yes";
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_02.wav");
			dialog.text = "O kapitanie! Ja... Ty... Udało się?";
			link.l1 = "Była drobna komplikacja, ale teraz jest załatwione. Dlaczego jesteś blada, madame? Wszystko w porządku? Mam klejnoty, to powinno cię rozweselić, prawda?";
			link.l1.go = "wife_23";
		break;
		
		case "wife_23":
			dialog.text = "Dzięki Bogu! Jestem pomszczona! Mój rycerzu! Ile tam było diamentów?";
			if (GetCharacterItem(pchar, "jewelry2") >= 100)
			{
				link.l1 = "Twój rycerz wrócił z przygody z pełnym workiem łupów. Zostawi połowę dla swojej damy, żeby mogła kupić najlepsze stroje z Paryża. Dotrzymałem ci obietnicy.";
				if (CheckAttribute(pchar, "questTemp.FMQT.Honour")) link.l1.go = "wife_25";
				else link.l1.go = "wife_26";
			}
			else
			{
				link.l1 = "Och, było tam mnóstwo diamentów, ale nie dostaniesz nic. Wynajęłaś mordercę, żeby mnie zabił, ty ladacznico! Naprawdę wierzysz, że podzieliłbym się z tobą po tym wszystkim? Powiesz o tym słowo, a twój mąż dowie się o twoim planie, by go okraść i zdradzić. Więc trzymaj język za zębami.";
				link.l1.go = "wife_24";
			}
		break;
		
		case "wife_24":
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_03.wav");
			dialog.text = "Łotrze! Drań! Nie ujdzie ci to na sucho!";
			link.l1 = "Słyszałem to już wcześniej.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_FinalNoJewelry");
		break;
		
		case "wife_25":
			RemoveItems(pchar, "jewelry2", 100);
			Log_Info("Przekazałeś diamenty");
			PlaySound("interface\important_item.wav");
			dialog.text = "Nie jesteś jak... reszta z nich. Osiągasz, co chcesz. Przed tobą świetlana przyszłość. Wiem, że jesteś zajętym człowiekiem, ale... Czy zostaniesz ze mną na chwilę? Nikt nam nie przeszkodzi, obiecuję.";
			link.l1 = "Zawsze mam czas dla pięknej kobiety takiej jak ty. Czy otworzyć butelkę wina twojego męża?";
			link.l1.go = "wife_sex";
		break;
		
		case "wife_sex":
			DialogExit();
			LAi_SetActorType(npchar);
			pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1;
			DoQuestCheckDelay("PlaySex_1", 1.0);
			
			// Rebbebion, для "Путеводной звезды"
			pchar.questTemp.FMQT.GiveDiamonds = true;
			pchar.questTemp.FMQT.Marceline = "Fuck"; 
		break;
		
		case "wife_26":
			RemoveItems(pchar, "jewelry2", 100);
			Log_Info("Przekazałeś diamenty");
			PlaySound("interface\important_item.wav");
			dialog.text = "Myślę, że mogę się bez nich obejść. Jest tu wiele sposobów, by wydać pieniądze. Tak wielu przystojnych i godnych mężczyzn na Tortudze... Dziękuję za wszystko, kapitanie. A propos, proszę zachowaj tę sprawę w tajemnicy, bo mój mąż każe cię powiesić na szubienicy. On nie jest dobrym człowiekiem. Żegnaj.";
			link.l1 = "Tak po prostu? To było pouczające doświadczenie. Żegnam, madame, również sugeruję, byś milczała o tym, ja też nie jestem dobrym człowiekiem. Ale już o tym wiesz, prawda?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_FinalNoSex");
			
			// Rebbebion, для "Путеводной звезды"
			pchar.questTemp.FMQT.GiveDiamonds = true;
			pchar.questTemp.FMQT.Marceline = "NoFuck"; 
		break;
		
		case "wife_27":
			PlaySound("Voice\English\Girls_2.wav");
			dialog.text = "Kim jesteś i co tu robisz?";
			link.l1 = "Co ty wyprawiasz? Mieliśmy umowę...";
			link.l1.go = "wife_28";
		break;
		
		case "wife_28":
			dialog.text = "Jaki układ, monsieur? Jestem zamężną kobietą, nie robię interesów z innymi mężczyznami! Opuść moje komnaty natychmiast albo zawołam mojego męża i jego strażników!";
			link.l1 = "Tak po prostu, co? Bardzo dobrze, wierzę, że w takim razie oświecę twego dobrego męża!";
			link.l1.go = "wife_29";
		break;
		
		case "wife_29":
			dialog.text = "Wyjdź teraz, ty bezczelny łotrze, albo moi ludzie wrzucą cię do lochu Fortu La Roche! Nie obchodzą mnie twoje groźby! Wynoś się!";
			link.l1 = "...";
			link.l1.go = "wife_30";
		break;
		
		case "wife_30":
			DialogExit();
			DoQuestReloadToLocation("Tortuga_town", "reload", "reload3", "FMQT_FinalFail");
			pchar.questTemp.FMQT.Marceline = "Deception"; // Rebbebion, для "Путеводной звезды"
		break;
		
		case "pirate":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\tavern\Pyanici-03.wav");
			pchar.quest.FMQT_late2.over = "yes";
			FreeSitLocator("Tortuga_tavern", "sit_base2");
			dialog.text = "Kim jesteś? Ach, nieważne. Nie ufaj kobietom, kumplu. Jak mówi Biblia... nawet najgłupsza z kobiet może cię wciągnąć na samo dno piekła swoimi manipulacjami. Siadaj, kumplu, napij się!";
			link.l1 = "Z przyjemnością!";
			link.l1.go = "pirate_1x";
		break;
		
		case "pirate_1x":
			DialogExit();
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "sit", "sit_base2");
			LAi_SetSitType(pchar);
			npchar.Dialog.currentnode = "pirate_1";
			LAi_SetActorType(npchar);
			LAi_ActorSetSitMode(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 2.0);
		break;
		
		case "pirate_1":
			PlaySound("Voice\English\tavern\Pyanici-05.wav");
			dialog.text = "Na co się gapisz? Polewaj!!";
			link.l1 = "Za twe zdrowie!.. Hej przyjacielu, nie zamierzam tu tracić czasu. Potrzebuję tego klucza, który masz na zbyciu, wiesz o czym mówię. Daj mi go, a nasze drogi się rozejdą: ty będziesz dalej popijał, a ja będę ratował damy w opałach.";
			link.l1.go = "pirate_2";
		break;
		
		case "pirate_2":
			dialog.text = "Aww kamracie! Nie słyszałeś, co właśnie powiedziałem! Musisz wyglądać mądrzej, niż naprawdę jesteś... pracując dla tej dziwki. Wiesz, kim jest jej mąż? Niedawno gubernator Levasseur wysłał swojego lojalnego murzyna Kampacho, żeby 'porozmawiał' z miejscowym, wysoko szanowanym kupcem. Czarny zatłukł biedaka na śmierć w jego własnym sklepie! Ten kupiec okazał pewien drobny brak szacunku dla żony gubernatora podczas balu czy coś. A ta sama suka uwiodła mnie swoim wyglądem i jego dublonami\nIstnieje duplikat klucza. Byłem kiedyś przyzwoitym włamywaczem we Francji, więc to była bułka z masłem. Gdyby nie córka komendanta Lyonu... nigdy nie zostałbym piratem. Bah! Pierdol to!";
			link.l1 = "To wszystko bardzo smutne, ale porozmawiajmy o interesach. Gdzie jest klucz?";
			link.l1.go = "pirate_3";
		break;
		
		case "pirate_3":
			dialog.text = "Słucham? Jestem poza grą, kumplu! Byłem na tyle sprytny, by zobaczyć, co nadchodzi! Opuszczam to miejsce na zawsze, jak tylko mój statek będzie gotowy do wypłynięcia. Chcesz klucz, zapłać za niego. Nie bądź skąpy, myślę, że niedługo nie będziesz potrzebować żadnych pieniędzy.";
			link.l1 = "Wiesz, masz rację. Nie chcę być zabawką kobiety. Dziękuję za radę i bądź bezpieczny na morzu!";
			link.l1.go = "pirate_4";
			link.l2 = "Płacić za to? Tobie? Jesteś żałosnym złodziejem i tchórzem. Powinieneś był zostać w tej dziurze w Lyonie. Kto wie, może miejscowy komendant ulitowałby się nad tobą i pozwolił zdegenerowanemu złodziejowi zostać swoim zięciem. Ja na pewno się nad tobą nie ulituję. Możesz oddać mi klucz po dobroci albo po złości, wybór należy do ciebie.";
			link.l2.go = "pirate_5";
			link.l3 = "(westchnienie) Ile?";
			link.l3.go = "pirate_6";
		break;
		
		case "pirate_4":
			dialog.text = "Bystry chłopak, to dobra decyzja, kamracie. Powodzenia. Mam nadzieję, że pewnego dnia znajdziesz prawdziwą i kochającą kobietę. Najlepiej rudą lub blondynkę, prawda?";
			link.l1 = "Żegnaj, kamracie...";
			link.l1.go = "pirate_exit";
		break;
		
		case "pirate_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "tables", "stay8");
			LAi_SetPlayerType(pchar);
			pchar.questTemp.FMQT = "huber";
			pchar.quest.FMQT_late1.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late1.win_condition.l1.date.hour  = 18.0;
			pchar.quest.FMQT_late1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late1.function = "FMQT_HuberTime";
			AddQuestRecord("FMQ_Tortuga", "9");
		break;
		
		case "pirate_5":
			dialog.text = "Obrażasz mnie!? Do broni, ty łajdaku!";
			link.l1 = "Zobaczymy, jak dobrze potrafisz otwierać sejfy bez rąk!";
			link.l1.go = "pirate_duel";
		break;
		
		case "pirate_duel":
			DialogExit();
			LAi_SetSitType(npchar);
			// ключ квестовый от Калеуче - вернуть назад
			GiveItem2Character(npchar, "kaleuche_key");
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key_FMQT");
			i = makeint(MOD_SKILL_ENEMY_RATE/4);
			pchar.questTemp.FMQT = "duel";
			PChar.questTemp.duel.enemy = NPChar.id;
			if (MOD_SKILL_ENEMY_RATE > 2) PChar.questTemp.duel.enemyQty = i;
			AddDialogExitQuestFunction("Duel_Prepare_Fight");
		break;
		
		case "pirate_6":
			dialog.text = "Jesteś człowiekiem interesu, muszę to przyznać. Może ci się faktycznie udać. Pięćdziesiąt dublonów. Na stół.";
			link.l1 = "Pół setki złotych monet? Za kawałek cyny? Do stu piorunów. Połóż klucz na stole. Teraz.";
			link.l1.go = "pirate_7";
			if (PCharDublonsTotal() >= 50)
			{
				link.l2 = "Dość wysoka cena... Dobrze. Weź je.";
				link.l2.go = "pirate_8";
			}
			else
			{
				link.l2 = "Całkiem niezła cena... Dobrze. Niedługo je przyniosę. Zostań tutaj.";
				link.l2.go = "pirate_wait";
			}
		break;
		
		case "pirate_wait":
			DialogExit();
			AddLandQuestMark(npchar, "questmarkmain");
			LAi_SetSitType(npchar);
			npchar.Dialog.currentnode = "pirate_dublon";
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "tables", "stay8");
			LAi_SetPlayerType(pchar);
		break;
		
		case "pirate_dublon":
			NextDiag.TempNode = "pirate_dublon"; // mitrokosta правка явного бага
			dialog.text = "Przyniosłeś pięćdziesiąt dublonów?";
			link.l1 = "Wiesz, myślę, że możesz się bez nich obejść. Klucz. Na stół.";
			link.l1.go = "pirate_7";
			if (PCharDublonsTotal() >= 50)
			{
				link.l2 = "Tak. Weź je.";
				link.l2.go = "pirate_8";
			}
			else
			{
				link.l2 = "Wciąż je zdobywam.";
				link.l2.go = "exit";
			}
		break;
		
		case "pirate_7":
			dialog.text = "Zatańczymy?";
			link.l1 = "Poprowadzę.";
			link.l1.go = "pirate_duel";
		break;
		
		case "pirate_8":
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(50);
			Log_Info("Przekazałeś 50 dublonów");
			PlaySound("interface\important_item.wav");
			dialog.text = "Dobrze. Użyj swojego rozumu, a może wyjdziesz z tego z kilkoma pesos i głową na karku. Weź klucz i posłuchaj mojej rady. Gratis. Kobieta Levasseura jest głupia jak ryba, ale wierzy, że jest przebiegła. Nie ufaj jej. Trzymaj ptaka w spodniach i pilnuj swoich kieszeni. Nie jest z niej wielki przeciwnik, po prostu bądź ostrożny i unikaj wciągania jej męża do tego\nJeszcze jedna rzecz - w jej buduarze jest skrzynia, gdzie trzyma swoje błyskotki, łatwo ją otworzyć wytrychem. Tam położy swoją działkę. Słyszałeś mnie. Bądź bezpieczny na morzu, bracie. Pamiętaj, bracia przed dziewkami.";
			link.l1 = "Pomóż Bóg, kamracie...";
			link.l1.go = "pirate_9";
		break;
		
		case "pirate_9":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "tables", "stay8");
			LAi_SetPlayerType(pchar);
			pchar.questTemp.FMQT = "key";
			pchar.questTemp.FMQT.Caution = "true";
			FMQT_KeyNextDay();
			pchar.quest.FMQT_late3.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late3.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.FMQT_late3.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late3.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late3.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late3.function = "FMQT_KeyTime";
			AddQuestRecord("FMQ_Tortuga", "10");
			// ключ квестовый от Калеуче - вернуть назад
			GiveItem2Character(pchar, "kaleuche_key");
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key_FMQT");
		break;
		
		case "mercen":
			PlaySound("Voice\English\EvilPirates10.wav");
			dialog.text = "Cholera! Nie spodziewałem się... do diabła z tą kobietą! Mój mistrz kazał mi unikać takich jak ona. Ale praca to praca. I tak cię dorwę.";
			link.l1 = "Prosze prosze, kolego... Wygląda na to, że chciała oszukać nas obu, nie mogę powiedzieć, że jestem zaskoczony. Dlaczego mielibyśmy dalej walczyć? Chcesz roboty? Mam jedną. Masz umiejętności, potrzebuję ludzi takich jak ty w mojej załodze. Jedzenie, koja, regularna płaca, rum i sprawiedliwy udział w łupach. Dam ci na to moje słowo. Co powiesz?";
			//if(CheckCharacterPerk(pchar, "IronWill") || CheckCharacterPerk(pchar, "HT2") || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34 || GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 20) link.l1.go = "mercen_1";
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34) link.l1.go = "mercen_1";
			else link.l1.go = "mercen_4";
		break;
		
		case "mercen_1":
			//if(CheckCharacterPerk(pchar, "IronWill")) notification("Masz żelazną wolę", "IronWill");
			//if(CheckCharacterPerk(pchar, "HT2")) notification("Mimicry", "Mimicry");
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34) notification("Skill Check Passed", SKILL_LEADERSHIP);
			//if(GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 20) notification("Skill Check Passed", SKILL_FORTUNE);
			dialog.text = "Masz gadane i twoja sława wyprzedza cię, kapitanie, muszę to przyznać. Aye, wchodzę w to. Jak nazywa się twój statek?";
			link.l1 = "'"+pchar.ship.name+"'. Porozmawiaj z bosmanem, znajdzie ci koję. Witamy na pokładzie!";
			link.l1.go = "mercen_2";
		break;
		
		case "mercen_2":
			dialog.text = "Ha! Pnę się w górę w hierarchii. Kopnij tę sukę ode mnie.";
			link.l1 = "...";
			link.l1.go = "mercen_3";
		break;
		
		case "mercen_3":
			DialogExit();
			LAi_group_Delete("EnemyFight");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "FMQT_MercenHire", 10.0);
			AddQuestRecord("FMQ_Tortuga", "17");
		break;
		
		case "mercen_4":
			//if(!CheckCharacterPerk(pchar, "IronWill")) notification("Nie posiadasz zdolności", "IronWill");
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 35) notification("Zbyt niska umiejętność (35)", SKILL_LEADERSHIP);
			//if(GetSummonSkillFromName(pchar, SKILL_FORTUNE) < 21) notification("Zbyt niska umiejętność (21)", SKILL_FORTUNE);
			dialog.text = "Pięknie gadasz. Ale nie wystarczająco pięknie, jeśli chcesz, by prawdziwi profesjonaliści dołączyli do twoich szeregów. Pamiętaj o tym na przyszłość. Jeśli ją masz.";
			link.l1 = "No dalej. Bądź szybki, mam spotkanie z damą.";
			link.l1.go = "mercen_5";
			link.l2 = "Nie będzie dziś drugiej szansy. Jestem zajętym człowiekiem, więc nie psujmy dywanu. Nie płacą ci wystarczająco, by umrzeć za jakąś małomiasteczkową putain. Jeśli w ogóle ci zapłacili.";
			link.l2.go = "mercen_6";
		break;
		
		case "mercen_5":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FMQT_MercenDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "mercen_6":
			dialog.text = "Masz rację. Nikt mi jeszcze nie zapłacił... Jeszcze. Zaraz to naprawię. Rób, co chcesz...";
			link.l1 = "...";
			link.l1.go = "mercen_7";
		break;
		
		case "mercen_7":
			DialogExit();
			LAi_SetCurHPMax(npchar); 
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_Delete("EnemyFight");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			AddQuestRecord("FMQ_Tortuga", "18");
			pchar.questTemp.FMQT.Roomfight = "true";
			FMQT_WifeFinalTalk();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

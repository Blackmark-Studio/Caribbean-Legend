// Джино Гвинейли - алхимик
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
		case "First time":
			// --> Страж истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "jino1")
			{
				dialog.text = "O! Dzień dobry, panie. Jak się tu pan znalazł?";
				link.l1 = "Dzień dobry, Gino. Poznajmy się. Jestem kapitan "+GetFullName(pchar)+" i jestem tutaj za pozwoleniem Johna. Wyrażę się jasno - potrzebuję twojej pomocy, ale mogę też pomóc tobie.";
				link.l1.go = "guardoftruth_0";
				npchar.quest.meeting = "1";
				DelLandQuestMark(npchar);
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "O! Dzień dobry, panie! Jak... jak się tu pan znalazł? A gdzie jest John?";
				link.l1 = "No proszę... A kto się tu ukrywał za zamkniętymi drzwiami? Interesujące... A co do Johna... on odszedł. A ten dom jest teraz mój. Ale nie martw się. Poznajmy się - kim jesteś i co tu robisz?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
				DelLandQuestMark(npchar);
			}
			else
			{
				// --> Страж истины
				if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "threeitems")
				{
					dialog.text = "Cześć, "+pchar.name+". Twój wyraz twarzy mówi mi, że znalazłeś coś ważnego. Czy masz wszystkie komponenty Strażnika Prawdy?";
					link.l1 = "Dokładnie tak! Mam przy sobie wszystkie trzy przedmioty: sztylet, mapę i kompas!";
					link.l1.go = "guardoftruth_34";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "jino")
				{
					dialog.text = "Cześć, "+pchar.name+" . Co się stało? Masz dziwny grymas na twarzy...";
					link.l1 = "Musimy o czymś porozmawiać, Gino. To trochę większy temat.";
					link.l1.go = "guardoftruth";
					break;
				}
				// Ксочитэм
				if (CheckAttribute(pchar, "questTemp.Ksochitam") && pchar.questTemp.Ksochitam == "begin")
				{
					dialog.text = TimeGreeting()+", "+pchar.name+". Tak, pamiętam, minęły dwa dni i chcesz wiedzieć o Strażniku Prawdy, mam rację?";
					link.l1 = "Tak! Czy udało ci się coś wykopać?";
					link.l1.go = "ksochitam";
					break;
				}
				//--> Португалец
				if (CheckAttribute(pchar, "questTemp.Portugal.Nomoney"))
				{
					dialog.text = "Przyniosłeś 5 000 pesos, "+pchar.name+"?";
					if (sti(pchar.money) >= 5000)
					{
						link.l1 = "Oczywiście. Weź pieniądze i kup wszystko, czego potrzebujesz.";
						link.l1.go = "Portugal_3";
						SetFunctionTimerCondition("Portugal_TreatmentOver", 0, 0, 1, false);
						DeleteAttribute(pchar, "questTemp.Portugal.Nomoney");
						pchar.quest.Portugal_Ill1.over = "yes";
						pchar.quest.Portugal_Ill.win_condition.l1 = "Timer";
						pchar.quest.Portugal_Ill.win_condition.l1.date.hour  = sti(GetTime());
						pchar.quest.Portugal_Ill.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
						pchar.quest.Portugal_Ill.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
						pchar.quest.Portugal_Ill.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
						pchar.quest.Portugal_Ill.function = "Portugal_ToAntiguaOver";
					}
					else
					{
						link.l1 = "Niestety, obecnie nie mam przy sobie pieniędzy.";
						link.l1.go = "Portugal_nomoney";
					}
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal.Die"))
				{
					dialog.text = "Niestety, "+pchar.name+", mam bardzo złe wieści... pacjent nie żyje. Jego stan zdrowia uległ nagłemu pogorszeniu, przynajmniej szybko odszedł.";
					link.l1 = "Szkoda... Niech Bóg zmiłuje się nad jego duszą!";
					link.l1.go = "exit";
					DeleteAttribute(pchar, "questTemp.Portugal.Die");
					pchar.quest.Remove_Avendel.win_condition.l1 = "Location_Type";
					pchar.quest.Remove_Avendel.win_condition.l1.location_type = "town";
					pchar.quest.Remove_Avendel.function = "RemoveAvendelnDoc";
					AddQuestRecord("Portugal", "6");
					CloseQuestHeader("Portugal");
					pchar.questTemp.Portugal = "end";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "ToAntigua")
				{
					dialog.text = "Cześć, "+pchar.name+". Czy coś się stało? Wyglądasz na bardzo zmartwionego...";
					link.l1 = "Gino, mam dla ciebie nietypową prośbę! Na moim statku leży człowiek z wysoką gorączką. Majaczy, jest nieprzytomny... czy możesz mu pomóc?";
					link.l1.go = "Portugal";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "Portugal_wait")
				{
					dialog.text = ""+pchar.name+", czekam na pacjenta. Pośpiesz się - im szybciej go tu przyprowadzisz, tym większa szansa, że będę w stanie go uratować.";
					link.l1 = "Tak, tak, natychmiast go dostarczę.";
					link.l1.go = "exit";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentStart")
				{
					dialog.text = "Przyprowadziłeś go w samą porę, "+pchar.name+". Niestety, jest w stanie krytycznym, ale nadal jest szansa. \nKapitanie, kończą mi się składniki i nie mamy czasu, by je zbierać w dżungli. Muszę kupić je wszystkie od miejscowych zielarzy za 5 000 pesos. Czy możesz dostarczyć tę sumę?";
					if (sti(pchar.money) >= 5000)
					{
					link.l1 = "Oczywiście. Proszę, weź pieniądze i kup wszystko, czego potrzebujesz.";
					link.l1.go = "Portugal_3";
					SetFunctionTimerCondition("Portugal_TreatmentOver", 0, 0, 1, false);
					}
					else
					{
						link.l1 = "Niestety,  nie mam teraz pieniędzy.";
						link.l1.go = "Portugal_nomoney";
						pchar.quest.Portugal_Ill.over = "yes";
						pchar.quest.Portugal_Ill1.win_condition.l1 = "Timer";
						pchar.quest.Portugal_Ill1.win_condition.l1.date.hour  = sti(GetTime());
						pchar.quest.Portugal_Ill1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
						pchar.quest.Portugal_Ill1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
						pchar.quest.Portugal_Ill1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
						pchar.quest.Portugal_Ill1.function = "Portugal_ToAntiguaOver";//не принесёт через 1 день - Португальцу капут
					}
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentCurrent")
				{
					dialog.text = "Nie mam teraz nic do powiedzenia, "+pchar.name+". Walczę o życie pacjenta. Jest jeszcze jakaś nadzieja. Wróć do mnie później - przypuszczam, że wkrótce będę mógł powiedzieć ci coś bardziej konkretnego.";
					link.l1 = "Dobrze, Gino, wrócę później.";
					link.l1.go = "exit";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentFinish")
				{
					pchar.quest.Portugal_Ill.over = "yes";
					dialog.text = "Mam dobrą wiadomość, "+pchar.name+"! Nie powiem, że twój człowiek ma się dobrze, ale cóż - żyje. Choroba ustępuje i widać postępy. Szczerze mówiąc, nie spodziewałem się, że moje mikstury aż tak mu pomogą...";
					link.l1 = "To wspaniałe wieści, Gino! Ale powiedz mi, kiedy będę mógł go zabrać? Mamy przed sobą długą drogę do przebycia, a czas ucieka.";
					link.l1.go = "Portugal_4";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "TreatmentComplete")
				{
					dialog.text = "Dzień dobry, Kapitanie. Miło cię widzieć.";
					link.l1 = "Jak się miewa nasz pacjent, Gino?";
					if (GetQuestPastDayParam("questTemp.Portugal_threedays") > 2) link.l1.go = "Portugal_9";
					else link.l1.go = "Portugal_threedays";
					break;
				}
				// <--Португалец
				dialog.text = "Dzień dobry, kapitanie. Jak się masz? Potrzebujesz mojej pomocy?";
				if (!CheckAttribute(npchar, "quest.rome"))
				{
					link.l1 = "Tak. Gino, podejrzewam, że jesteś erudytą i być może nawet znasz łacinę... zgadza się?";
					link.l1.go = "rome";
				}
				if (CheckCharacterItem(pchar, "chemistry"))
				{
					link.l2 = "Mam coś innego. Mały prezent dla ciebie. Spójrz na tę książkę.";
					link.l2.go = "chemistry";
				}
				if (CheckAttribute(npchar, "quest.colt") && CheckCharacterItem(pchar, "pistol7"))
				{
					link.l2 = "Tak, Gino. Chcę ci pokazać ten pistolet. Czy kiedykolwiek widziałeś coś podobnego?";
					link.l2.go = "colt";
				}
				if (CheckAttribute(npchar, "quest.sample") && CheckCharacterItem(pchar, "pistol7") && CheckCharacterItem(pchar, "GunCap_colt") && CheckCharacterItem(pchar, "shotgun_cartridge"))
				{
					link.l2 = "Przyniosłem ci przykładowy ładunek do mojego pistoletu.";
					link.l2.go = "colt_1";
				}
				if (CheckAttribute(npchar, "quest.cartridge"))
				{
					link.l2 = "Co z ładunkami do pistoletu? Masz już jakieś wskazówki?";
					link.l2.go = "cartridge";
				}
				// Addon 2016-1 Jason Пиратская линейка
				if (CheckAttribute(pchar, "questTemp.Mtraxx.Gord"))
				{
					link.l3 = "Gino, znalazłem nieznane dla mnie słowo 'gord' w dzienniku kapitana. Wiesz może, co to znaczy?";
					link.l3.go = "mtraxx";
				}
				link.l9 = "Dzień dobry, Gino. Mam się dobrze, nie potrzebuję pomocy. Chciałem tylko sprawdzić, jak u ciebie i trochę porozmawiać.";
				link.l9.go = "exit";	
			}
			NextDiag.TempNode = "First time";
		break;

		case "meeting":
			pchar.questTemp.HWIC.Jino = "true"; // Addon 2016-1 Jason Пиратская линейка
			dialog.text = "Nazywam się Gino. Gino Gvineili. Jestem naukowcem. Moim zadaniem jest tworzenie proszków, mieszanin i innych lekarstw dla pana Murdocka. Ale odkąd zniknął...";
			link.l1 = "No cóż, jestem "+GetFullName(pchar)+". Kapitan własnego okrętu. A więc jesteś alchemikiem?";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Nie tylko alchemikiem, ale i lekarzem. Posiadam niemałą wiedzę o medycynie. Znam się na wielu ziołach leczniczych i potrafię przyrządzać z nich mikstury i eliksiry. Ale moim prawdziwym powołaniem jest chemia - dużo eksperymentuję i niektóre z moich wynalazków mogą pomóc takim osobom jak ty. \nZnam łacinę, francuski, angielski i włoski. Moja pomoc będzie nieoceniona, jeśli planujesz prowadzić aptekę jak pan Murdock...";
			link.l1 = "Oho! Nie codziennie spotyka się tak wykształconego człowieka. Aptekarstwo to z pewnością dobry interes, ale ja jestem żeglarzem... Hmm, to brzmi dziwnie nawet dla mnie... W każdym razie, jestem pewien, że zostaniemy przyjaciółmi, Gino. Możesz dalej tu mieszkać i zajmować się swoimi naukowymi sprawami...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "";
			link.l1 = "I jeśli kiedykolwiek będę potrzebował pomocy od alchemika, uzdrowiciela lub naukowca - będę wiedział, do kogo się zwrócić... Powiedz mi, dlaczego cały czas przebywasz tutaj, w środku? Czy ty w ogole stąd nie wybywasz?";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Ależ wychodzę na zewnątrz, gdy muszę kupić jakieś składniki lub zioła do moich eksperymentów. Lubię mieszkać samotnie, to mój sposób życia. Poświęciłem życie nauce i nie interesuje mnie zwyczajne życie. Książki, pisma, probówki, retorty... \nPan Murdock dał mi taką możliwość w zamian za pomoc w produkcji leków.";
			link.l1 = "Teraz będziesz miał jeszcze więcej czasu, Gino. Ale będziesz musiał zrezygnować z części czasu na swoje eksperymenty, w razie gdybym potrzebował twojej pomocy, zgoda?";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "Jasne, Kapitanie. Nazwę cię Kapitanem, "+GetAddress_Form(NPChar)+", jeśli nie masz nic przeciwko? Zostawię wszystkie moje badania na wypadek, gdybyś potrzebował moich praktycznych umiejętności lub teoretycznej wiedzy.";
			link.l1 = "Wspaniale. Cieszę się, że tak szybko się zrozumieliśmy. Nie martw się o swoje wydatki, ja lub mój kwatermistrz zostawimy ci od czasu do czasu rozsądne sumy.";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "Dzięki, Kapitanie - nie potrzebuję wiele. Hmm, właściwie to mam pewien pomysł... może nauczysz się trochę alchemii? To może być naprawdę przydatne dla ciebie.";
			link.l1 = "Hmmm... Jak kiedyś powiedział mi brat - nie bądź wybredny, jeśli chodzi o naukę robienia rzeczy własnymi rękami. Więc pewnie, czemu nie. Co możesz mi pokazać?";
			link.l1.go = "meeting_6";
		break;
		
		case "meeting_6":
			dialog.text = "Cóż, z pewnością nie będziesz w stanie zamienić żelaza w złoto, to niemożliwe... jeszcze, ale możesz nauczyć się, jak mieszać składniki zgodnie z instrukcjami, aby uzyskać mikstury lub inne przydatne przedmioty. Proszę, weź tę torbę. Zawiera wszystko, czego początkujący alchemik będzie potrzebował. Probówki, kolby, retorty, alembiki, szpatułki, szklane rurki, palnik i tak dalej...";
			link.l1 = "Fascynujące!";
			link.l1.go = "meeting_7";
		break;
		
		case "meeting_7":
			Log_Info("Otrzymałeś zestaw alchemika");
			GiveItem2Character(pchar, "alchemy_tool");
			PlaySound("interface\important_item.wav");
			dialog.text = "Musisz znać przepis, aby przygotować miksturę lub przedmiot. Przepisy można kupić od kupców lub znaleźć wszędzie. Gdy już przestudiujesz przepis, powinieneś zebrać wszystkie potrzebne składniki i dokładnie zrobić to, co tam jest napisane. \nUżywaj swoich narzędzi alchemicznych, znajdź lub kup moździerz i tłuczek, poszukaj tygla, niestety, nie posiadam dodatkowego, aby ci go dać. Zioła, spirytusy, mikstury, minerały, nawet śmieci - wszystko się nada, pod warunkiem, że masz odpowiedni przepis i narzędzia.";
			link.l1 = "Rozumiem. Postaram się coś sporządzić w wolnym czasie. Dzięki, Gino! Możesz podać mi jakiś prosty przepis? Coś na początek?";
			link.l1.go = "meeting_8";
		break;
		
		case "meeting_8":
			dialog.text = "Oj, prostych to ja nie mam... ale weź ten - to przepis na antidotum. Zakładam, że potrafisz sobie z tym poradzić. Proszę bardzo.";
			link.l1 = "Dziękuję! Od razu wezmę się do nauki. A teraz żegnaj, Gino! I proszę, pilnuj mojego domu - obawiam się, że rzadko będę tu bywał, więc możesz korzystać nie tylko ze swojego pokoju, ale także z reszty budynku.";
			link.l1.go = "meeting_9";
		break;
		
		case "meeting_9":
			DialogExit();
			GiveItem2Character(pchar, "recipe_potion4"); // belamour legendary edition
			Log_Info("Otrzymałeś przepis na antidotum");
			PlaySound("interface\notebook.wav");
			Log_Info("Aby tworzyć mikstury, amulety i przedmioty, musisz posiadać umiejętność 'Alchemia'!");
			NextDiag.CurrentNode = "First time";
		break;
		
		case "rome":
			dialog.text = "Tak, Kapitanie, doskonale władam językiem starożytnych Rzymian. Każdy uczony - zwłaszcza uzdrowiciel czy alchemik, musi znać łacinę. Czy potrzebujesz mojej znajomości łaciny?";
			link.l1 = "Tak. Gino, nie bierz mnie za głupca, ale... cóż, jak to wyjaśnić...";
			link.l1.go = "rome_1";
		break;
		
		case "rome_1":
			dialog.text = "Mów wprost, kapitanie. Nie krępuj się.";
			link.l1 = "No dobra. Czy mógłbyś przygotować dla mnie listę różnych łacińskich aforyzmów? Mogą być od uczonych, filozofów albo z Pisma Świętego. Widzisz, jest pewien... człowiek, który wręcz uwielbia przechwalać się swoją 'erudycją'. Co jakiś czas rzuca jakimś łacińskim zwrotem, żeby mi wytknąć ignorancję. Coś w stylu... 'pasem bellum', czy jakoś tak....";
			link.l1.go = "rome_2";
		break;
		
		case "rome_2":
			dialog.text = "'Si vis pacem, para bellum', to masz na myśli?";
			link.l1 = "Tak, tak. Chcę się ich nauczyć, aby przyćmić mojego aroganckiego br... to znaczy, mojego przyjaciela.";
			link.l1.go = "rome_3";
		break;
		
		case "rome_3":
			AddQuestRecordInfo("Rome", "1");
			dialog.text = "Nie ma nic ani dziwnego, ani wstydliwego w twojej prośbie, Kapitanie. Znajomość aforyzmów starożytnych, którzy przeszli do historii, czyni z ciebie człowieka obytego i wykształconego. Proszę, weź ten tekst. To właśnie to, o co prosiłeś.";
			link.l1 = "Dzięki, Gino! Naprawdę, bardzo to doceniam! Przysiądę do tego w wolnym czasie...";
			link.l1.go = "exit";
			npchar.quest.rome = true;
			NextDiag.TempNode = "First time";
		break;
		
		case "chemistry":
			RemoveItems(pchar, "chemistry", 1);
			Log_Info("Podałeś podręcznik chemii autorstwa Lavoisiera.");
			dialog.text = "Pokaż mi... (czyta) Niemożliwe! Mówisz, że to tylko drobny prezent?! "+pchar.name+", ta książka jest bezcenna! Skąd ją w ogóle masz?! To jest... prawdziwy skarb!";
			link.l1 = "Widzę, że ci się bardzo spodobała. Cieszy mnie to.";
			link.l1.go = "chemistry_1";
		break;
		
		case "chemistry_1":
			dialog.text = "(Czytając) Niesamowite! Nigdy o tym nie słyszałem... a to? Nic z tego nie rozumiem... ale jeszcze zrozumiem, do licha! Zobaczysz, zaraz w moim laboratorium będzie aż wrzało od pracy! "+pchar.name+", nawet nie zdajesz sobie sprawy, co mi dałeś...";
			link.l1 = "Czemuż by nie? Wiem, co to - książka naukowa dla naukowca...";
			link.l1.go = "chemistry_2";
		break;
		
		case "chemistry_2":
			dialog.text = "A wiesz, kto jest autorem tego cudu? Jakiś Antoine-Laurent de Lavoisier, z Francji... Powiem ci, że nigdy o nim nie słyszałem. Ale czekaj! Co...?! Jak to możliwe? Rok wydania to... 1789? Ale jak...";
			link.l1 = "Nie mam pojęcia, dlaczego ten rok jest tam napisany. Albo może wiem. Tak czy siak radzę ci się nad tym zbytnio nie zastanawiać. Księga jest użyteczna i to wszystko, co się liczy.";
			link.l1.go = "chemistry_3";
		break;
		
		case "chemistry_3":
			dialog.text = "Oj, bardzo użyteczna! A ten rok pewnie jest jakimś błędem drukarskim... Nieważne. W każdym razie bardzo ci dziękuję, kapitanie!";
			link.l1 = "Miło było cię spotkać, Gino. Teraz ta książka należy do ciebie.";
			link.l1.go = "exit";
			if (CheckCharacterItem(pchar, "pistol7"))
			{
				link.l1 = "To nie wszystko, Gino. Chcę ci pokazać ten pistolet. Czy kiedykolwiek spotkałeś się z czymś takim?";
				link.l1.go = "colt";
			}
			npchar.quest.colt = true;
		break;
		
		case "colt":
			dialog.text = "Nie jestem rusznikarzem, ale rzucę okiem... nie, nigdy czegoś takiego nie widziałem. Dlaczego pytasz?";
			link.l1 = "Ten pistolet jest naprawdę potężny, wręcz sieje spustoszenie na polu walki. Ale jak widać, do jego użycia potrzebne są specjalne ładunki. Nic innego nie zadziała. I nie mam pojęcia, jak zrobić więcej nabojów do niego. Więc przyszedłem tu po twoją radę.";
			link.l1.go = "colt_1";
		break;
		
		case "colt_1":
			dialog.text = "Masz chociaż jeden nabój, by pokazać mi jako przykład? Jeśli nie, obawiam się, że nie będę w stanie pomóc.";
			if (CheckCharacterItem(pchar, "GunCap_colt") && CheckCharacterItem(pchar, "shotgun_cartridge"))
			{
				link.l1 = "Tak. Ładunek składa się z dwóch części: samego naboju z kulą i tej rzeczy, która zapala proch.";
				link.l1.go = "colt_2";
			}
			else
			{
				link.l1 = "O nie... Ale to spieprzyłem! Nie mam, co za wstyd! Eh... Dobrze, może jakimś cudem uda mi się znaleźć więcej - wtedy przyniosę je do ciebie.";
				link.l1.go = "exit";
				npchar.quest.sample = true;
			}
			DeleteAttribute(npchar, "quest.colt");
		break;
		
		case "colt_2":
			RemoveItems(pchar, "pistol7", 1);
			RemoveItems(pchar, "GunCap_colt", 1);
			RemoveItems(pchar, "shotgun_cartridge", 1);
			Log_Info("Podałeś nabój do rewolweru");
			Log_Info("Podałeś dziwną kapsułkę");
			PlaySound("interface\important_item.wav");
			dialog.text = "Niesamowite! To wygląda całkiem banalnie - w środku jest proch, a kula wchodzi z góry, choć przyznaję, że wygląda to nieco dziwnie. A to 'coś'... Hmm. Proch nie wybuchnie bez tego, prawda? Ciekawe... Dobra, na szybko i tak tego nie ogarniemy. Kapitanie, proszę, zostaw mi to wszystko: pistolet i ładunki. Przyjdź do mnie za miesiąc - potrzebuję czasu, żeby to rozgryźć.";
			link.l1 = "Świetnie! Spróbuj zrozumieć, jak to działa. Uwierz mi, że naprawdę chcę wypalić z tego pistoletu.";
			link.l1.go = "colt_3";
		break;
		
		case "colt_3":
			dialog.text = "Główny problem leży w tym, że nie wiadomo z czego zrobiona jest ta substancja, która detonuje proch. Może ta książka okaże się przydatna. Spróbuję to rozgryźć.";
			link.l1 = "Dobrze. Żegnaj, Gino!";
			link.l1.go = "colt_4";
		break;
		
		case "colt_4":
			DialogExit();
			DeleteAttribute(npchar, "quest.sample");
			SetFunctionTimerCondition("Colt_Timer", 0, 0, 30, false); // таймер
		break;
		
		case "cartridge":
			dialog.text = "Tak! Odkryłem, z czego są zrobione ładunki do pistoletu - i to wszystko dzięki książce, którą mi podarowałeś. Bez niej by się nie udało. Ale muszę cię ostrzec, Kapitanie. Stworzenie pocisków i kapiszonów do tej broni nie będzie łatwe.";
			link.l1 = "Kapiszonów?";
			link.l1.go = "cartridge_1";
		break;
		
		case "cartridge_1":
			dialog.text = "Kapiszon to jest ta 'kapsułka', która, jak rzekłeś, zapala proch. Ale zacznijmy od początku. Jesteś gotów?";
			link.l1 = "Tak! Słucham cię bardzo uważnie.";
			link.l1.go = "cartridge_2";
		break;
		
		case "cartridge_2":
			AddQuestRecordInfo("Recipe", "shotgun_bullet");
			SetAlchemyRecipeKnown("shotgun_bullet");
			dialog.text = "Więc najpierw musisz wykonać specjalną kulę. Zwykłe kule nie zadziałają. Musi mieć ona specjalny stożkowy kształt. Będziesz musiał znaleźć formę do takich kul - formę na pocisk, że tak to nazwę. Weź zwykłe ołowiane kule, stop je w tyglu i wlej stopiony ołów do tej specjalnej formy. Następnie schłódź odlew, poczekaj i wyjmij z niego gotową kulę. Ot, trochę zwykłego kowalstwa.";
			link.l1 = "A gdzie, u licha, mogę znaleźć taką formę do odlewu pocisków?";
			link.l1.go = "cartridge_3";
		break;
		
		case "cartridge_3":
			dialog.text = "Nie mam bladego pojęcia, Kapitanie. Jestem alchemikiem, a nie kowalem. Weź ten pocisk jako przykład, może dowiesz się, co z nim zrobić.";
			link.l1 = "Dobrze. W takim razie kontynuuj...";
			link.l1.go = "cartridge_4";
		break;
		
		case "cartridge_4":
			AddQuestRecordInfo("Recipe", "shotgun_cartridge");
			SetAlchemyRecipeKnown("shotgun_cartridge");
			dialog.text = "Następnie musisz stworzyć pojemnik na proch. Umieszczasz tam pocisk. Zresztą spisałem dla ciebie dokładną instrukcję. Przeczytaj ją i spróbuj.";
			link.l1 = "Dobrze...";
			link.l1.go = "cartridge_5";
		break;
		
		case "cartridge_5":
			AddQuestRecordInfo("Recipe", "GunCap_colt");
			SetAlchemyRecipeKnown("GunCap_colt");
			dialog.text = "Teraz musimy zdobyć kapiszony. Będziesz potrzebował bardzo cienkiej miedzianej blachy - wytwórz ją samodzielnie z miedzianej bryły. Wytnij w niej kręgi o tej samej średnicy co naboje. Następnie umieść w nich piorunian srebra, używając wosku.";
			link.l1 = "Piorunian srebra? Błagam cię, Gino... Co to jest, do diabła?!";
			link.l1.go = "cartridge_6";
		break;
		
		case "cartridge_6":
			dialog.text = "Do niedawna sam tego nie wiedziałem - ale tutaj znów ta książka okazała się przydatna. Fulminat to biały proszek, który można zrobić ze srebra, spirytusu i kwasu azotowego. Bardzo łatwo eksploduje przy pocieraniu lub potrząsaniu, dlatego świetnie się nada do zapłonu w twoim dziwnym pistolecie. Ale ostrzegam, że to cholernie nieprzyjemna rzecz - podczas moich eskeprymentów eksplodowała dwa razy... aż w końcu znalazłem przepis.";
			link.l1 = "Co za szczęście, że miałem tę książkę przy sobie!";
			link.l1.go = "cartridge_7";
		break;
		
		case "cartridge_7":
			dialog.text = "Bądź bardzo ostrożny, to gówno jest strasznie wybuchowe! Mógłbym sam zrobić trochę, ale przechowywanie piorunianu srebra jest zbyt niebezpieczne. Istotne jest, aby umieścić to w kapsułach zaraz po stworzeniu. Ale nie potrafię robić miedzianych kapsuł, bo nie jestem kowalem, jak ci już mówiłem.";
			link.l1 = "Dobrze. Daj mi przepis, nauczę się go sam.";
			link.l1.go = "cartridge_8";
		break;
		
		case "cartridge_8":
			AddQuestRecordInfo("Recipe", "OxyHydSilver");
			SetAlchemyRecipeKnown("OxyHydSilver");
			dialog.text = "Proszę bardzo. Dokładnie postępuj według przepisu i uważaj na kolejność procesu, bo inaczej wylecisz w powietrze razem ze swoimi flakonikami.";
			link.l1 = "Będę ostrożny.";
			link.l1.go = "cartridge_9";
		break;
		
		case "cartridge_9":
			dialog.text = "Weź również te dwie fiolki. W tej jest kwas azotowy, a w tej spirytus. Będziesz w stanie zrobić wystarczająco dużo piorunianu srebra, by napełnić około 20 kapiszonów.";
			link.l1 = "Dziękuję, Gino!";
			link.l1.go = "cartridge_10";
		break;
		
		case "cartridge_10":
			GiveItem2Character(pchar, "Mineral29");
			GiveItem2Character(pchar, "Mineral28");
			Log_Info("Otrzymałeś fiolkę z kwasem azotowym");
			Log_Info("Otrzymałeś fiolkę ze spirytusem");
			PlaySound("interface\important_item.wav");
			dialog.text = "Nie zapomnij zabrać też swojego pistoletu i przykładowego ładunku. Powodzenia, kapitanie, w tworzeniu pocisków. Mam nadzieję, że jakoś przetrwasz w jednym kawałku.";
			link.l1 = "Zrobię, co w mojej mocy, by się chronić. A, właśnie, Gino... czy mówiłem ci już, że jesteś cholernym geniuszem?";
			link.l1.go = "cartridge_11";
		break;
		
		case "cartridge_11":
			TakeNItems(pchar, "pistol7", 1);
			TakeNItems(pchar, "shotgun_cartridge", 3);
			TakeNItems(pchar, "GunCap_colt", 1);
			dialog.text = "Oj, Kapitanie, sprawiasz, że się rumienię. Serio...!";
			link.l1 = "W takim razie żegnaj, Gino! Jesteś moim najlepszym alchemikiem!";
			link.l1.go = "cartridge_12";
		break;
		
		case "cartridge_12":
			DialogExit();
			DeleteAttribute(npchar, "quest.cartridge");
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		case "mtraxx":
            dialog.text = "Gord, gord... Czy mógłbyś mi powiedzieć więcej o kapitanie? Skąd on pochodzi?";
			link.l1 = "Nie mam pojęcia, chociaż ten cały gord urodził się gdzieś na Północy. Czasami nazywali go Wikingiem.";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = "Wiking! Tak-tak, pamiętam, czytałem o tym w książce historycznej! Już tłumaczę: gord to nazwa dla ufortyfikowanego osiedla wolnego jarla.";
			link.l1 = "Wolny jarl? Któżby to mógł być?";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "To książę Normanów. Wolni jarłowie ze swoimi wojennymi drużynami niegdyś najeżdżali i plądrowali Europę na swoich statkach - drakkarach. Jak mniemam, można by ich nazwać piratami. Gordy były ich bazami i domami. Miejscami, gdzie mogli odpocząć, uprawiać ziemię i ucztować.";
			link.l1 = "Rozumiem. W takim razie ta szopa musi być jego pirackim legowiskiem... Dzięki wielkie, Gino!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekReadLogbookFourth");
		break;
		
	// ----------------------------------------- Португалец ----------------------------------------------------
		case "Portugal":
			dialog.text = "Gorączka i majaczenie, mówisz, to intrygujące. Przyprowadź go tutaj natychmiast! Zobaczę, co da się zrobić. Ale nie mogę ci nic obiecać, jeśli jego stan jest zbyt zły... Czy to twój oficer?";
			link.l1 = "Nie, dzięki Bogu, nie jest. Gino, właściwie dobrze by było, jakbyś nie pytał, kim on jest - tak będzie lepiej, naprawdę. Po prostu zrób, co możesz!";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "Dobrze, wprowadź go do domu, do swojego pokoju. Przygotuję kilka mikstur... Hmmm, może ten korzeń...";
			link.l1 = "Zaraz go tu dostarczę!";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			DialogExit();
			PChar.quest.Portugal_DoctorPodhodit.win_condition.l1 = "location";
			PChar.quest.Portugal_DoctorPodhodit.win_condition.l1.location = "SentJons_HouseF3";
			PChar.quest.Portugal_DoctorPodhodit.function = "Portugal_DoctorPodhodit";
		break;
		
		case "Portugal_nomoney":
			dialog.text = "W takim razie pośpiesz się. Nie będę mógł go wyleczyć bez lekarstw, a jeśli się nie sprężysz, może być już za późno.";
			link.l1 = "Dobrze, znajdę pieniądze.";
			link.l1.go = "exit";
			pchar.questTemp.Portugal.Nomoney = "true";
		break;
		
		case "Portugal_3":
			AddMoneyToCharacter(pchar, -5000);
			dialog.text = "Wspaniale, kapitanie. Teraz zajmę się przygotowaniem mikstur i zalecam opuszczenie mojego pacjenta. Wróć tu jutro.";
			link.l1 = "Dobrze, Gino. Mam zaufanie do twoich mikstur i geniuszu.";
			link.l1.go = "exit";
			pchar.questTemp.Portugal = "TreatmentCurrent";
			//pchar.GenQuest.CannotWait = true;//запрет ожидания
		break;
		
		case "Portugal_4":
			dialog.text = "Cóż, myślę, że za dwa tygodnie będzie w porządku. Nie mogę obiecać, że będzie mógł tańczyć, ale przynajmniej sam stanie na nogi, to pewne.";
			link.l1 = "Cholera, nie mam tych dwóch tygodni! Muszę... wyruszyć w morze jak najszybciej!";
			link.l1.go = "Portugal_5";
		break;
		
		case "Portugal_5":
			dialog.text = "Kapitanie, nie jestem pieprzonym czarodziejem, więc mogę cię zapewnić, że ten człowiek jest teraz zbyt słaby. Nie jestem pewien, czy przeżyje kilka dni na statku, nie możesz go ruszać!";
			link.l1 = "Dobrze, dobrze. Ale dwa tygodnie, nie, nawet jeden tydzień to za dużo!";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_6":
			dialog.text = "Trzy dni... tak, myślę, że za trzy dni możesz spróbować wypłynąć, ale będzie potrzebował opieki i leków, i będziesz musiał robić przystanki.";
			link.l1 = "Mam ma pokładzie lekarza, on się nim zajmie. Wrócę za trzy dni i go zabierzemy, to wszystko, na co mogę sobie pozwolić. Musimy ruszać, nawet z przystankami... tak, i jeszcze jedno - Gino, jesteś geniuszem!";
			link.l1.go = "Portugal_7";
		break;
		
		case "Portugal_7":
			dialog.text = "Dzięki, Kapitanie. Wróć po swojego przyjaciela za trzy dni, ale nie przeszkadzaj mu do tego czasu. Potrzebuje pełnego odpoczynku.";
			link.l1 = "Dobrze, rozumiem. Zabiorę go za trzy dni.";
			link.l1.go = "Portugal_8";
		break;
		
		case "Portugal_8":
			DialogExit();
			SaveCurrentQuestDateParam("questTemp.Portugal_threedays");
			pchar.quest.Portugal_Ill2.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Ill2.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Ill2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 5);
			pchar.quest.Portugal_Ill2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 5);
			pchar.quest.Portugal_Ill2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 5);
			pchar.quest.Portugal_Ill2.function = "Portugal_ToAntiguaOver";//чтобы не тянул
			pchar.questTemp.Portugal = "TreatmentComplete";
			pchar.quest.Avendel_room.win_condition.l1 = "location";
			pchar.quest.Avendel_room.win_condition.l1.location = "SentJons_HouseF3";
			pchar.quest.Avendel_room.function = "AvendelSpeach";
		break;
		
		case "Portugal_threedays":
			dialog.text = "Radzi sobie dobrze, ale mamy słabe postępy. To musi potrwać. Jeszcze nie można go zabrać.";
			link.l1 = "Tak, tak, Gino. Pamiętam. Trzy dni...";
			link.l1.go = "exit";
		break;
		
		case "Portugal_9":
			pchar.quest.Portugal_Ill2.over = "yes";
			dialog.text = "Nie pogorszył się, ale też nie poprawił. Nadal jest nieprzytomny, nie rozumie, gdzie jest i dlaczego tu jest, chociaż wydaje się, że nie za bardzo go to obchodzi. Ma nadal gorączkę, więc nie jestem pewien, czy zabranie go teraz na pokład to dobry pomysł.";
			link.l1 = "Nie mogę dłużej czekać, jesteśmy tu już za długo. Pakuj swoje mikstury, które pomogą mu w podróży i ruszamy. Mam nadzieję, że ten drań jest wystarczająco silny, by przetrwać wystarczająco długo, aby stawić czoła wyrokowi śmierci...";
			link.l1.go = "Portugal_10";
		break;
		
		case "Portugal_10":
			dialog.text = "Zaczekaj, kapitanie! Czy ja właśnie leczyłem skazańca? Co do diabła? Ogromna praca została tutaj wykonana, czy masz pojęcie, jak trudno jest zrobić suchy proch...";
			link.l1 = "Gino, nie musiałeś tego wiedzieć. Nie martw się zbytnio, on jest piratem i jednym z najstraszniejszych w swoim rodzaju. Muszę go jak najszybciej zabrać na Kurakao na spotkanie z władzami Kompanii. Kropka.";
			link.l1.go = "Portugal_11";
		break;
		
		case "Portugal_11":
			dialog.text = "Dobrze, wiesz lepiej. Pirat zatem... Curacao. Cokolwiek, ale posłuchaj mnie, będzie spał przez większość czasu, ale kołysanie statku i duszne gorąco mogą cofnąć cały proces. Zalecam zrobić postój po kilku dniach żeglugi i pozwolić twojemu... więźniowi odpocząć na lądzie. W przeciwnym razie istnieje ryzyko, że będą musieli powiesić trupa na Kurakao...";
			link.l1 = "Dobrze, zrobię to. Martynika będzie odpowiednia, jest prawie w połowie drogi do Kurakao. Mam nadzieję, że wiatr będzie pomyślny. Teraz go zabieram i wyruszamy. Jeszcze raz dziękuję, Gino.";
			link.l1.go = "Portugal_12";
		break;
		
		case "Portugal_12":
			dialog.text = "Jesteś mile widziany, Kapitanie. Pamiętaj, że masz cztery dni, no, pięć, ale nie więcej. I jeszcze jedna rzecz... wiesz, zazwyczaj leczę ludzi nie dlatego, że chcę, żeby zostali powieszeni po moim leczeniu. Lekarz jest odpowiedzialny za swoich pacjentów, nieważne kim są. I czuję się naprawdę źle...";
			link.l1 = "Przepraszam, że cię w to wszystko wciągnąłem, ale bez ciebie nie mieliśmy szans. Musimy teraz wypłynąć, bo inaczej portugalskie chłopaki zdążą zebrać się u naszych drzwi, by spotkać się ze swoim szefem.";
			link.l1.go = "Portugal_13";
		break;
		
		case "Portugal_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SentJons_HouseF3_Room", "goto", "goto2", "Portugal_JinoNorm", -1);//Джино в свою комнату
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			pchar.quest.Portugal_Ill3.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Ill3.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Ill3.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 5);
			pchar.quest.Portugal_Ill3.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 5);
			pchar.quest.Portugal_Ill3.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 5);
			pchar.quest.Portugal_Ill3.function = "Portugal_ToAntiguaOver";//5 дней до Мартиники
			pchar.questTemp.Portugal = "ToMartinique";
			pchar.quest.Avendel_room1.win_condition.l1 = "location";
			pchar.quest.Avendel_room1.win_condition.l1.location = "SentJons_HouseF3";
			pchar.quest.Avendel_room1.function = "AvendelSpeach";
			pchar.quest.Portugal_street.win_condition.l1 = "location";
			pchar.quest.Portugal_street.win_condition.l1.location = "SentJons_town";
			pchar.quest.Portugal_street.function = "PortugalOnStreet";
		break;
		// <-- Португалец
		case "guardoftruth_0":
			dialog.text = "Intrygujące... A jak możesz mi pomóc? Nie potrzebuję pomocy i nie prosiłem o nią...";
			link.l1 = "Ale będziesz jej potrzebował. Najpierw mnie wysłuchaj, a potem wyciągnij wnioski.";
			link.l1.go = "guardoftruth";
		break;
		
		case "guardoftruth":
			dialog.text = "Zamieniam się w słuch.";
			link.l1 = "Niedawno byłem w Santiago... odwiedzając ojca Vincento. Szukał swojego zaginionego sekretarza o imieniu... O Jezu, dlaczego zrobiłeś się taki blady, Gino?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Ty... widziałeś inkwizytora? Czy on...";
			link.l1 = "Nie martw się, Gino. W życiu bym cię nie zdradził, choć w zasadzie takie było jego polecenie: znaleźć cię i przyprowadzić do niego. Muszę zdobyć informacje o jednym Indianinie z ludu Itza. Opowiedz mi o Tayasal, jego skarbach i 'złu' z nim związanym.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Widzę, że jesteś dobrze poinformowany. Czy ojciec Vincento ci to powiedział?";
			link.l1 = "Dostałem od niego trochę informacji i trochę od innych ludzi. Ale chciałbym cię wysłuchać. Byłeś kiedyś jego sekretarzem, więc musisz mieć protokół z przesłuchania, prawda?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Nie możesz sobie wyobrazić, co on robił temu biednemu Indianinowi!.. Ciarki mnie przechodzą za każdym razem, gdy przypominam sobie to przesłuchanie.";
			link.l1 = "Ale mimo to, proszę, porozmawiajmy o tym. Kim był ten Indianin? Jak trafił w ręce ojca Vincento?";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "Był wśród Indianin z ludu Itza, którzy podróżowali z Tayasal w poszukiwaniu Maski Kukulkana - artefaktu prastarego boga Majów o tym właśnie imieniu. Niestety, w trakcie wędrówki Indianie napotkali grupkę białych awanturników prowadzoną przez niejakiego Archibalda Calhouna - łowcę skarbów ze Szkocji. Przeżył tylko jeden Indianin, nazywał się Ksatl Cha. Miał przy sobie trzy zadziwiające przedmioty, ale opowiem ci o nich później. \nCalhoun próbował zmusić więźnia, by wyśpiewał wszystko o skarbach, ale ten milczał. Dlatego właśnie  Szkot dostarczył go do Santiago, prosto w łapy ojca Vincento, a w zamian za to dostał roczne pozwolenie na odwiedzanie hiszpańskich kolonii. Wiedział, że inkwizytor bardzo interesuje się wszelkiego rodzaju lokalnymi tajemnicami i legendami. Vincento zmusił Indianina do mówienia. Zaczął mówić dużo, opowiedział nam wszystko, co wiedział, a informacje, które od niego uzyskaliśmy, zszokowały samego inkwizytora.";
			link.l1 = "Na Boga, nie mów! Co takiego mogłoby sprawić, że Jego Świątobliwość zadrży?";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Opowiem ci wszystko po kolei. W głębi dżungli Jukatanu znajduje się starożytne miasto Majów o nazwie Tayasal. Jest zamieszkane przez potomków Majów - lud Itza. Próbują żyć według zasad i tradycji swoich przodków. Z pewnością nie podoba im się stan współczesnego świata - mam na myśli kolonizacje, dominację białego człowieka i tak dalej.\nMarzą o starych dobrych czasach. I tu zaczyna się najciekawsze. Pewna grupa białych rozbójników przypadkowo zbliżyła się do Tayasal i tam porwała córkę najwyższego wodza ludu Itza. Stało się to prawie ćwierć wieku temu.\nWłaśnie wtedy przelała się czara goryczy - Kanek, owy wódz, wpadł w gniew. Postanowił przeprowadzić tajemniczy, najstraszliwszy i krwiożerczy rytuał Majów. Przywołanie pewnego bożka, który miał zetrzeć z ziemi wszystkich potomków białego człowieka...";
			link.l1 = "Ojej... To chyba musi być ten demon, o którym wspominał ojciec Vincento. Ale jak ten indiański bożek miałby sobie poradzić z białymi kolonistami? No co, ukaże się postaci smoka i wszystkich spali? (śmiech)";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "Och, "+pchar.name+", błagam cię - zachowaj te kpiny dla siebie! Choć tak właściwie, to wcale nie jesteś tak daleko od prawdy. Nasz przypadek jest jednak znacznie bardziej niebezpieczny. Wiemy dobrze, że nawet Potop nie powstrzymałby Europy przed ekspansją w Nowy Świat. Tak to jest, że jednego zabitego od razu zastępuje dziesięciu innych. Kanek nie chciał nas po prostu wyrżnąć. On chciał, by europejska kolonizacja nigdy się nie wydarzyła.";
			link.l1 = "Hmmm... Nigdy nie wydarzyła? Dosłownie, tak?.";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Dobrze kombinujesz, Kapitanie... Celem rytuału Kaneka nie było tylko wezwanie tej pradawnej abominacji, lecz także stworzenie dziury czasoprzestrzennej.";
			link.l1 = "...Co?";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "Starzy Majowie posiadali niemałą wiedzę, Kapitanie. Kanek znalazł opis rytuału, który pozwala... kontrolować czas.";
			link.l1 = "Czas?! Co ty opowiadasz...? Niewiarygodne!";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "Słuchaj. Ostatecznym celem rytuału jest zmiana przeszłości, aby uniemożliwić pojawienie się białego człowieka w Nowym Świecie. Aby to osiągnąć, zamierzają wysłać kogoś w przeszłość, kogoś, kto posiada władzę, autorytet i zdolność zmieniania losów ludzi. Ale co najważniejsze, taka osoba musi posiadać nowoczesną wiedzę.\nPomyśl o tym, "+pchar.name+", co by się stało z Kolumbem, gdyby jego karawelom naprzeciw wyszła indiańska flotylla fregat i galeonów uzbrojonych w nowoczesne armaty? A co jeśli arkebuzy białych żołnierzy nie stawiałyby czoła łukom i włóczniom, tylko moździerzom i muszkietom...?";
			link.l1 = "Przypuszczam, że Ameryki w ogóle by nie odkryto. To byłaby straszliwa klęska.";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			dialog.text = "Dokładnie! Pewno byłoby wręcz na odwrót - zgaduję, że  jakiś indiański 'Kolumb' odkryłby Europę, a my zostalibyśmy niewolnikami, których składanoby w ofierze.";
			link.l1 = "Możliwe. Tylko że kogo Kanek zamierza wysłać w przeszłość? Jednego z tych swoich nagich wojowników? Hah, wątpię, by był w stanie nauczyć czegokolwiek swoich przodków...";
			link.l1.go = "guardoftruth_11";
		break;
		
		case "guardoftruth_11":
			dialog.text = "Nie śmiej się, Kapitanie. Kanek nie trwonił lat w świątyniach Majów, czytając ich pisma. To sam bóg Indian musi zostać wysłany w przeszłość - i to w ludzkiej postaci...";
			link.l1 = "Gino, co za bzdury wygadujesz? Czy ty....";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			dialog.text = "Nawet Syn naszego Pana, Jezus Chrystus, przyszedł na ziemię w ludzkiej postaci i urodził się z ludzkiej kobiety, Świętej Dziewicy Maryi...";
			link.l1 = "Jezu, Gino... czy ty tak na poważnie?";
			link.l1.go = "guardoftruth_13";
		break;
		
		case "guardoftruth_13":
			dialog.text = "Niestety. Ksatl Cha był bardzo przekonujący...";
			link.l1 = "A którego Boga wybrał Kanek dla takiej 'szlachetnej' misji?";
			link.l1.go = "guardoftruth_14";
		break;
		
		case "guardoftruth_14":
			dialog.text = "Rytuał miał przywołać tylko jedno wysokie bóstwo. Pierzastego węża, Quetzalcoatla, Kukulkana...";
			if (CheckAttribute(pchar, "questTemp.Dolly")) link.l1 = "Kukulkan?! Już miałem nierozwagę spotkać się z jego 'duchem', który żyje w posągach. Teraz rozumiem... kontynuuj!";
			else link.l1 = "Kukulkan? Hmmm, chyba już słyszałem to imię od ojca Vincento... kontynuuj!";
			link.l1.go = "guardoftruth_15";
		break;
		
		case "guardoftruth_15":
			dialog.text = "Kanek postanowił wezwać Kukulkana, ponieważ Itza już posiadali starożytny artefakt tego boga - wspomnianą już maskę. Ten, kto posiada Maskę Kukulkana, jest w stanie przejść przez portal i tylko on zostanie zaakceptowany przez starożytnych Majów - jako żywy bóg.\nI to już się stało. Kapłan przeprowadził rytuał, wezwał Kukulkana, a ten wstąpił w ciało jakiegoś śmiertelnika. Stworzył także dziurę czasową, która przeniosła kilku przypadkowych ludzi z przyszłości tutaj, do naszych czasów.\nCelem tego było przedstawienie wcieleniu Kukulkana nie tylko wiedzy z naszych czasów, ale także z przyszłości. Ale coś poszło nie tak i wszyscy ci ludzie przybyli gdzie indziej, a nie do Tayasal. Hah! Nigdy nie spotkałem żadnego z nich.\nW obrębie archipelagu stworzono kilka portali, które miały transportować posiadaczy wiedzy przyszłości i agentów Itza po całym obszarze i do Tayasal. Ale te portale zawiodły. Z tego co mi wiadomo, nikt nie został przeniesiony do Tayasal w ciągu ostatnich 25 lat...";
			if (CheckAttribute(pchar, "questTemp.Dolly"))
			{
				link.l1 = "No tak... Ponieważ te cholerne portale właśnie tak działają, że przenoszą ludzi tylko między sobą!";
				link.l1.go = "guardoftruth_15a";
			}
			else
			{
				link.l1 = "Interesujące...";
				link.l1.go = "guardoftruth_16";
			}
		break;
		
		case "guardoftruth_15a":
			dialog.text = "Widziałeś te portale? Powiedz mi!";
			link.l1 = "Może później, Gino... Teraz skupmy się na twojej historii. Opowiadaj!";
			link.l1.go = "guardoftruth_16";
		break;
		
		case "guardoftruth_16":
			dialog.text = "Ojciec Vincento wie o wszystkim, co ci powiedziałem. To go oczywiście zmartwiło. Jeśli Kukulkan, wcielony w ludzką postać, dotrze do portalu wraz z Maską i całą wiedzą, którą zgromadził... Koniec czasów. Apokalipsa.\nJeśli przeszłość się zmieni - przyszłość uczyni to samo. Nasza rzeczywistość się zmieni, zniknie, rozpuści się. Ty i ja możemy nigdy się nie narodzić. Albo będziemy inni. Gdy tylko Kukulkan dotrze do przeszłości - przestaniemy istnieć.";
			link.l1 = "I kim jest wcielenie Kukulkana?";
			link.l1.go = "guardoftruth_17";
		break;
		
		case "guardoftruth_17":
			dialog.text = "Kto wie. Może być w każdym, kto urodził się ćwierć wieku temu, kiedy odprawiano rytuał. W tobie, na przykład... tylko żartuję. Ale wciąż mamy szansę. Po pierwsze, inkarnacja Kukulkana to tylko śmiertelnik, może utonąć, zostać zasztyletowany, zastrzelony lub umrzeć na febrę. A w takim przypadku, żadna apokalipsa nigdy się nie wydarzy.\nPo drugie, nie da się dotrzeć do przeszłości bez maski, Kanek ją dobrze ukrył, może nawet za dobrze. Może być, że nawet inkarnowany Kukulkan nie zdoła jej odnaleźć.";
			link.l1 = "Opowiedz mi więcej.";
			link.l1.go = "guardoftruth_18";
		break;
		
		case "guardoftruth_18":
			dialog.text = "Jakiś czas po rytuale grupa hiszpańskich konkwistadorów prawie dotarła do Tayasal i prawie dostała się do skarbca. Itza udało się zabić wszystkich z wyjątkiem jednego - silnego olbrzyma o wzroście siedmiu stóp.\nKanek obawiał się, że Maskę może skraść każdy obcy, więc postanowił chronić relikwię. Wymyślił własny rytuał, wykorzystując starożytną wiedzę Majów. Wziął trzy przedmioty, które, jak wierzył, posiadały moc białego człowieka. Sztylet, który niegdyś należał do samego Corteza, oraz kompas. Użył również tego sztyletu, by wyciąć kawałek skóry z pleców schwytanego hiszpańskiego olbrzyma jako trzeci przedmiot. Sam człowiek został złożony w ofierze na ołtarzu Kukulkana. Trzy przedmioty zostały użyte w rytuale.\nI z tego rytuału narodziła się nowa wyspa, na otwartym morzu, niedaleko Jukatanu. Nikt nie zna jej lokalizacji, ale Maska jest tam ukryta. Aby ją znaleźć, trzeba użyć sztyletu, kompasu i kawałka skóry. Poza tym, wszystkie przedmioty ze skarbca są przeklęte, żaden z nich nie może opuścić archipelagu.\nPróba ich wywiezienia spowoduje sztorm, który skieruje statek prosto na skały wyspy, gdzie ukryta jest maska. Nazywa się Ksocheatem. Sprytne, prawda?";
			link.l1 = "Może zbyt sprytny. Nie ma co do tego wątpliwości. Ale jakim cudem Ksatl Cha był tak dobrze poinformowany? Wątpię, by Kanek dzielił się taką wiedzą ze zwykłymi wojownikami...";
			link.l1.go = "guardoftruth_19";
		break;
		
		case "guardoftruth_19":
			dialog.text = "Rzecz w tym, że obecny wódz Itza, Urakan, syn Kaneka, opowiedział temu wojownikowi wszystko. Wysłał Ksatl Chę z grupą wojowników, by odnaleźć tajemniczą wyspę i Maskę Kukulkana. Dał mu Strażnika Prawdy, by tego dokonał, to nazwa trzech przedmiotów razem - sztylet, kompas i mape wykonaną z ludzkiej skóry.";
			link.l1 = "Mapa? A dlaczego Urakan potrzebował Maski? Postanowił sam zmienić przeszłość?";
			link.l1.go = "guardoftruth_20";
		break;
		
		case "guardoftruth_20":
			dialog.text = "Skóra ma kontury archipelagu, więc nazywają ją mapą. Urakan chciał Maski z bardzo prostego powodu - nie chce zniszczyć istniejącej rzeczywistości i poświęcać swojego życia oraz życia swojego ludu dla chwały starożytnych. Dlatego zamierzał zniszczyć Maskę za wszelką cenę. Ale Ksatl Cha został schwytany przez Calhouna i... cóż, znasz resztę opowieści. Nigdy nie dotarł do Ksocheatem.";
			link.l1 = "Więc można zapobiec końcu czasów, znajdując i niszcząc Maskę? A gdzie teraz jest ten... Strażnik Prawdy?";
			link.l1.go = "guardoftruth_21";
		break;
		
		case "guardoftruth_21":
			dialog.text = "Sztylet 'Szpon Wodza' i kompas 'Strzała Drogi' zostały przekazane Calhounowi, a mapa skórzana 'O dwóch obliczach' wciąż jest gdzieś u inkwizycji. Calhoun użył jej jako knebla, by zamknąć usta więźniowi. Nie miał pojęcia, do czego służą te przedmioty.";
			link.l1 = "Coś ty właśnie powiedział? 'Szpon Naczelnika'? Do diabła, ten sztylet jest teraz przy mnie! Fadey dał mi go w ramach spłaty długu wobec mojego brata! Spójrz!";
			link.l1.go = "guardoftruth_22";
		break;
		
		case "guardoftruth_22":
			dialog.text = "Niesamowite... Naprawdę tak jest. Pamiętam to.";
			link.l1 = "Gino, powiedz mi, co dokładnie ojciec Vincento wie o twojej historii?";
			link.l1.go = "guardoftruth_23";
		break;
		
		case "guardoftruth_23":
			dialog.text = "Wszystko, oprócz informacji dotyczących Strażnika Prawdy i sposobu, aby pokazał lokalizację tajemniczej wyspy, na której ukryta jest Maska Kukulkana. Ksatl Cha powiedział mi o tym, kiedy byliśmy sami tuż przed tym, jak podałem mu mieszankę trucizn, by zakończyć jego cierpienie. Zmarł z uśmiechem na twarzy.\nZ pewnością nie mogłem zostać w Santiago po tym, co zrobiłem. Miałem poważne podejrzenia, że stałem się ważnym i niebezpiecznym świadkiem dla inkwizytora. Ojciec Vincento zawsze dostaje, czego chce, bez względu na koszt. Ksatl Cha powiedział mu o skarbu w Tayasal.";
			link.l1 = "Te skarby już zostały odnalezione przez pewnego awanturnika imieniem Miguel Dichoso. Czy słyszałeś o nim?";
			link.l1.go = "guardoftruth_24";
		break;
		
		case "guardoftruth_24":
			dialog.text = "Nie. A gdzież on teraz jest ze swymi skarbami?";
			link.l1 = "Sam chcę się tego dowiedzieć. Dlatego przyszedłem do ciebie, szukam tego indiańskiego złota. Dichoso zabrał skarby do Europy i zniknął z nimi.";
			link.l1.go = "guardoftruth_25";
		break;
		
		case "guardoftruth_25":
			dialog.text = "Powiem ci, gdzie są skarby i sam Dichoso.";
			link.l1 = "Gino, zaskakujesz mnie. Skądże to wiesz?!";
			link.l1.go = "guardoftruth_26";
		break;
		
		case "guardoftruth_26":
			dialog.text = "Jesteś w stanie sam to rozgryźć z mojej opowieści, Kapitanie. Skarby Tayasal były przeklęte - żadna rzecz nie może być zabrana z archipelagu. Każdy statek...";
			link.l1 = "... zostanie złapany przez burzę i wyrzucony na wyspę, gdzie ukryta jest Maska Kukulkana! Byłem ślepy, ale teraz widzę. Wydaje się, że wiem wystarczająco, aby znaleźć Ksocheatem, skarby i samą Maskę!";
			link.l1.go = "guardoftruth_27";
		break;
		
		case "guardoftruth_27":
			dialog.text = "Chcesz uratować świat, kapitanie?";
			link.l1 = "Chcę odnaleźć mojego marnotrawnego brata... Gino, jak mogę sprawić, by Strażnik Prawdy pokazał lokalizację wyspy? Powiedziałeś, że wiesz jak!";
			link.l1.go = "guardoftruth_28";
		break;
		
		case "guardoftruth_28":
			dialog.text = "Znam metodę, ale nie znam szczegółów. Nie będę w stanie ci pomóc, dopóki nie będę miał wszystkich elementów Strażnika.";
			link.l1 = "Hm. Mamy już sztylet. Został tylko kompas i mapa. Calhoun ma kompas, a ojciec Vincento ma mapę...";
			link.l1.go = "guardoftruth_29";
		break;
		
		case "guardoftruth_29":
			dialog.text = "Czy zamierzasz wrócić do inkwizytora? Ale jak zamierzasz zdać relację o...";
			link.l1 = "Muszę przekonać ojca Vincento, że nie żyjesz, Gino. Tylko wtedy przestanie cię szukać. Powiedzmy, że dostałeś nagłego udaru, gdy mnie zobaczyłeś. Powinieneś dać mi przedmiot, którego będę mógł użyć jako dowód twojej śmierci.";
			link.l1.go = "guardoftruth_30";
		break;
		
		case "guardoftruth_30":
			dialog.text = "Vincento nie uwierzy w wersję o ataku serca, ale uwierzy ci, jeśli powiesz mu, że popełniłem samobójstwo, pijąc jakąś truciznę o zapachu migdałów. Daj mu mój almanach, on wie, że nigdy się z nim nie rozstaję.";
			link.l1 = "Dobrze. Bo potrzebuję tego połączenia z inkwizytorem. On prawdopodobnie wie dużo o naszej działalności.";
			link.l1.go = "guardoftruth_31";
		break;
		
		case "guardoftruth_31":
			dialog.text = "Uważaj na ojca Vincento. Jest niebezpieczny jak tygrys i prowadzi własną grę. Nie podzieli się z tobą ani skarbami, ani sławą.";
			link.l1 = "Rozumiem to. Dobrze, Gino, daj mi swój almanach i spróbuj sobie przypomnieć, co Indianin powiedział ci o Strażniku Prawdy, bo chcę go złożyć. Muszę znaleźć Ksocheatem, jestem pewien, że znajdę tam nie tylko maskę i skarby, ale także mojego drogiego brata.";
			link.l1.go = "guardoftruth_32";
		break;
		
		case "guardoftruth_32":
			dialog.text = "Weź to. Powodzenia, kapitanie!";
			link.l1 = "Nie mówię żegnaj, Gino...";
			link.l1.go = "guardoftruth_33";
		break;
		
		case "guardoftruth_33":
			DialogExit();
			Log_Info("Otrzymałeś almanach");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "Almanac");
			ChangeItemDescribe("Almanac", "itmdescr_jinobook");
			pchar.questTemp.Guardoftruth = "twoitems";
			AddQuestRecord("Guardoftruth", "37");
		break;
		
		case "guardoftruth_34":
			dialog.text = "Było ciężko, kapitanie?";
			link.l1 = "Nie rozmawiajmy o tym... Zbyt wielu ludzi zginęło, aby zdobyć te przedmioty. Zbyt wielu. Wygląda na to, że nie tylko ja pragnę odnaleźć tajemniczego Ksocheatema.";
			link.l1.go = "guardoftruth_35";
		break;
		
		case "guardoftruth_35":
			dialog.text = "Wyobrażam sobie... A tak przy okazji, jak się miewa ojciec Vincento? Czy regularnie z nim rozmawiasz?";
			link.l1 = "Jak na razie tak, ale myślę, że nie ma już potrzeby tego robić. Mam wszystkie komponenty Strażnika Prawdy, co oznacza, że posiadam klucz do lokalizacji Ksocheatem. Z jakiegoś powodu nie spieszę się, by zgłosić mój sukces Jego Eminencji.";
			link.l1.go = "guardoftruth_36";
		break;
		
		case "guardoftruth_36":
			dialog.text = "Bądź ostrożny, "+pchar.name+" Ojciec Vincento ma setki oczu i rąk. Bardzo długie ręce...";
			link.l1 = "Przeszedłem wiele w ciągu ostatnich miesięcy i w tym momencie z pewnością się nie boję, ani ojca Vincento, ani jego oczu i rąk. Cokolwiek. Czas, abyśmy znaleźli Ksocheatem używając komponentów Strażnika. Czy wiesz, jak to zrobić?";
			link.l1.go = "guardoftruth_37";
		break;
		
		case "guardoftruth_37":
			dialog.text = "Nie bardzo. Ksatl Cha był dość niejasny. Myślę, że Indianin tak naprawdę nie wiedział, jak uruchomić Strażnika. Zostaw mi te komponenty, a spróbuję to rozgryźć. Przyjdź do mnie za dwa dni, a być może rozwiążę tę zagadkę.";
			link.l1 = "W porządku, Gino. Liczę na ciebie. Proszę, weź je.";
			link.l1.go = "guardoftruth_38";
		break;
		
		case "guardoftruth_38":
			dialog.text = "Możesz być pewien, że będą ze mną bezpieczni i cali.";
			link.l1 = "Nie wątpię w to. Cóż, nie będę cię teraz niepokoił, Gino. Powodzenia w badaniach!";
			link.l1.go = "guardoftruth_39";
		break;
		
		case "guardoftruth_39":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			RemoveItems(pchar, "knife_01", 1);
			RemoveItems(pchar, "skinmap", 1);
			RemoveItems(pchar, "arrowway", 1);
			pchar.questTemp.Guardoftruth = "end";
			SetFunctionTimerCondition("Ksochitam_StartSearchIsland", 0, 0, 2, false);
			CloseQuestHeader("Guardoftruth");
			AddQuestRecord("Ksochitam", "1");
		break;
		
		case "ksochitam":
			dialog.text = "Częściowo. To znaczy, mam coś, ale nie wiem, jak to wszystko naprawdę zadziałać. Spróbujmy rozwiązać tę zagadkę razem.";
			link.l1 = "Spróbujmy! Daj mi swoje pomysły.";
			link.l1.go = "ksochitam_1";
		break;
		
		case "ksochitam_1":
			dialog.text = "Ksatl Cha powiedział coś takiego: 'Szpon Wodza sprawi, że mapa się ujawni. Strzała Drogi wskaże kierunek manifestacji.'";
			link.l1 = "A co udało ci się zrobić?";
			link.l1.go = "ksochitam_2";
		break;
		
		case "ksochitam_2":
			dialog.text = "Zgadłem, jak sprawić, by mapa się 'ujawniła'. Czy spojrzałeś na mapę Dwóch Wizerunków?";
			link.l1 = "Hm.  A czy było coś szczególnego?  Jakieś ukryte kontury archipelagu...";
			link.l1.go = "ksochitam_3";
		break;
		
		case "ksochitam_3":
			GiveItem2Character(pchar, "skinmap");
			dialog.text = "Weź to i przyjrzyj się jeszcze raz. Bądź uważny.";
			link.l1 = "No cóż, zróbmy to, skoro nalegasz.";
			link.l1.go = "ksochitam_4";
		break;
		
		case "ksochitam_4":
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_wait";
			pchar.questTemp.Ksochitam = "skinmap_1";
			chrDisableReloadToLocation = true;//закрыть локацию
		break;
		
		case "ksochitam_wait":
			dialog.text = "Nie spojrzałeś na mapę, "+pchar.name+"... ";
			link.l1 = "Tak-tak, zrobię to teraz...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_wait";
		break;
		
		case "ksochitam_5":
			dialog.text = "";
			link.l1 = "Mam. Nie widziałem nic nowego. Tylko jakieś zamazane kształty wysp i lądu. Co tam mam zobaczyć?";
			link.l1.go = "ksochitam_6";
		break;
		
		case "ksochitam_6":
			dialog.text = "Chwila moment. Teraz musisz sprawić, by mapa się ujawniła. Weź sztylet i delikatnie dotknij mapy jego ostrzem. Nie naciskaj, musimy unikać uszkodzeń. Weź sztylet. I uważnie obserwuj!";
			link.l1 = "Interesujące! Zobaczmy...";
			link.l1.go = "ksochitam_7";
		break;
		
		case "ksochitam_7":
			DialogExit();
			GiveItem2Character(pchar, "knife_01");
			NextDiag.CurrentNode = "ksochitam_wait";
			pchar.questTemp.Ksochitam = "skinmap_2";
			sld = ItemsFromID("skinmap");
			sld.mark = 2;
		break;
		
		case "ksochitam_8":
			dialog.text = "Cóż, widzisz teraz jakieś różnice?";
			link.l1 = "Tak. Gdy dotykasz mapy sztyletem, pojawiają się dwa znaki czaszek i zawsze są w tych samych miejscach...";
			link.l1.go = "ksochitam_9";
		break;
		
		case "ksochitam_9":
			dialog.text = "Na DWÓCH tych samych miejscach, "+pchar.name+"! Dlatego nazywano to mapą Dwóch Wizerunków!";
			link.l1 = "Co to znaczy?";
			link.l1.go = "ksochitam_10";
		break;
		
		case "ksochitam_10":
			dialog.text = "Dużo, tak myślę... Ale następne będą kolejne zagadki. Zakładam, że te czaszki to wcielenia, o których mówił Ksatl Cha. Więc kompas musi wskazywać właściwy kierunek do Ksocheatem od nich. Czy widziałeś kompas, "+pchar.name+"?";
			link.l1 = "Tak. Wygląda jak zwykły kompas morski, ale zachowuje się dziwnie, jego strzałka drga w różne strony lub zaczyna się kręcić z szaloną prędkością.";
			link.l1.go = "ksochitam_11";
		break;
		
		case "ksochitam_11":
			dialog.text = " Myślałem, że umieszczenie kompasu na czaszkach zatrzyma jego strzałkę i wskaże jakiś wyraźny kierunek na mapie. Aby to zrobić, umieściłem go na jednej czaszce, a potem na drugiej, dotykając mapy sztyletem.";
			link.l1 = "I?";
			link.l1.go = "ksochitam_12";
		break;
		 
		case "ksochitam_12":
			dialog.text = "Daremnie. Kompas nie zmienił swojego zachowania. Strzałka wciąż kręci się dziko. Wydaje się, że robię coś źle. Albo nie zrozumiałem słów Ksatl Cha poprawnie.";
			link.l1 = "Więc sztylet i mapa działają, a kompas nie?";
			link.l1.go = "ksochitam_13";
		break;
		
		case "ksochitam_13":
			dialog.text = "Strzała Drogi musi być na pewno operacyjna, tylko jeszcze nie wiemy, jak ją uruchomić."+pchar.name+",  znasz geografię archipelagu lepiej niż ja... Powiedz mi, jakie miejsca ujawnia mapa dwóch wyglądów?";
			link.l1 = "Chwileczkę! (rzucając okiem)...No, no... Wygląd po lewej to zachodni kontynent. Ten po prawej wygląda jak wyspa Dominika. Coś w tym stylu.";
			link.l1.go = "ksochitam_14";
		break;
		
		case "ksochitam_14":
			dialog.text = "I powiedz mi: Czy jest tam... coś godnego uwagi?";
			link.l1 = "Co masz na myśli?";
			link.l1.go = "ksochitam_15";
		break;
		
		case "ksochitam_15":
			dialog.text = "Nie jestem pewien sam... Cóż, coś specjalnego?";
			link.l1 = "Gino, nie mów zagadkami. Wyjaśnij to prosto.";
			link.l1.go = "ksochitam_16";
		break;
		
		case "ksochitam_16":
			dialog.text = "Mogę tylko przypuszczać, że te czaszki pokazują nam jakieś prawdziwe miejsca. Strzała Drogi nie działa, gdy jest umieszczona na odwzorowania mapy. Być może zadziała w pobliżu prawdziwych geograficznych odwzorowań, które ujawniła mapa?";
			link.l1 = "Gino, jesteś geniuszem! Zachodni Kontynent, Dominika? Czaszki są zbyt duże, by pokazać dokładne lokalizacje.";
			link.l1.go = "ksochitam_17";
		break;
		
		case "ksochitam_17":
			chrDisableReloadToLocation = false;//открыть локацию
			dialog.text = ""+pchar.name+" , zróbmy tak: Przynieś mi papierową mapę archipelagu, połącz ją z mapą Dwóch Objawień i zaznacz objawienia krzyżykami. Może to da Ci jakieś przypuszczenia?";
			if (CheckCharacterItem(pchar, "map_bad"))
			{
				link.l1 = "Mam tę starą mapę archipelagu.";
				link.l1.go = "ksochitam_17_1";
			}
			if (CheckCharacterItem(pchar, "map_normal"))
			{
				link.l2 = "Posiadam tę wspaniałą mapę archipelagu.";
				link.l2.go = "ksochitam_17_2";
			}
			if (CheckCharacterItem(pchar, "Map_Best"))
			{
				link.l3 = "Mam tę doskonałą mapę archipelagu.";
				link.l3.go = "ksochitam_17_3";
			}
			link.l4 = "Umowa stoi. Przyniosę ci mapę i będziemy kontynuować...";
			link.l4.go = "ksochitam_17_4";
		break;
		
		case "ksochitam_17_1":
			dialog.text = "Och, daj spokój, "+pchar.name+"! Ten pergamin z czasów Kolumba nie jest wiele lepszy od mapy na skórze. Jestem pewien, że na świecie jest coś lepszego niż ten szmelc. Przynieś mi inną mapę, młodszą!";
			link.l1 = "Dobrze...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_map_wait";
		break;
		
		case "ksochitam_17_2":
			dialog.text = "Znakomicie! Teraz oznacz miejsca ich manifestacji na niej. To ułatwi budowanie przypuszczeń.";
			link.l1 = "Za chwilkę, Gino!";
			link.l1.go = "ksochitam_18";
		break;
		
		case "ksochitam_17_3":
			dialog.text = "„Nie ma mowy, byśmy zniszczyli tak wspaniałą mapę naszymi oznaczeniami. Sam będziesz jej potrzebować, "+pchar.name+". Przynieś mi inną mapę, trochę skromniejszą!";
			link.l1 = "Dobrze...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_map_wait";
		break;
		
		case "ksochitam_17_4":
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_map_wait";
		break;
		
		case "ksochitam_map_wait":
			dialog.text = "Czy przyniosłeś mi mapę archipelagu, "+pchar.name+"?";
			if (CheckCharacterItem(pchar, "map_bad"))
			{
				link.l1 = "Mam tę starą mapę archipelagu.";
				link.l1.go = "ksochitam_17_1";
			}
			if (CheckCharacterItem(pchar, "map_normal"))
			{
				link.l2 = "Mam tę wspaniałą mapę archipelagu.";
				link.l2.go = "ksochitam_17_2";
			}
			if (CheckCharacterItem(pchar, "Map_Best"))
			{
				link.l3 = "Mam tę wyśmienitą mapę archipelagu.";
				link.l3.go = "ksochitam_17_3";
			}
			link.l4 = "Jeszcze nie, ale już to zamówiłem. Wkrótce to będę miał i będziemy kontynuować...";
			link.l4.go = "ksochitam_17_4";
		break;
		
		case "ksochitam_18":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_19";
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto1", "Ksochitam_SitTable", -1);
		break;
		
		case "ksochitam_19":
			dialog.text = "";
			link.l1 = "Zrobione... Stworzyłem oznaczenia, ale to wciąż niedokładne informacje. Pierwsze miejsce jest gdzieś na północny zachód od Blueweld. Drugie znajduje się w centrum wyspy Dominika.";
			link.l1.go = "ksochitam_20";
		break;
		
		case "ksochitam_20":
			dialog.text = "Jakieś pomysły?";
			link.l1 = "Nie. Ale myślę, że powinniśmy tam zabrać Strzałę Drogi i obserwować jej zachowanie. Oczywiście, to jak szukanie igły w stogu siana, ale i tak nie mamy lepszych pomysłów.";
			link.l1.go = "ksochitam_21";
		break;
		
		case "ksochitam_21":
			dialog.text = "Zgadzam się z tobą, "+pchar.name+" Czy pozwolisz mi z tobą żeglować?";
			link.l1 = "Jesteś zainteresowany sprawdzeniem swoich przypuszczeń? Byłby to zaszczyt mieć cię na pokładzie mojego statku, Gino. Spakuj swoje rzeczy!";
			link.l1.go = "ksochitam_22";
		break;
		
		case "ksochitam_22":
			dialog.text = "To nie zajmie dużo czasu. Będę gotowy za kilka godzin. Proszę, weź Strzałę Drogi.";
			link.l1 = "Witaj na pokładzie!";
			link.l1.go = "ksochitam_23";
		break;
		
		case "ksochitam_23":
			LAi_SetOwnerType(npchar);
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_24";
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetPlayerType(pchar);
			GiveItem2Character(pchar, "arrowway");
			pchar.questTemp.Ksochitam = "seekway";
			sld = ItemsFromID("skinmap");
			sld.mark = 1;
			pchar.quest.Ksochitam_room.win_condition.l1 = "ExitFromLocation";
			pchar.quest.Ksochitam_room.win_condition.l1.location = pchar.location;
			pchar.quest.Ksochitam_room.function = "Ksochitam_JinoPassenger";
			AddQuestRecord("Ksochitam", "2");
		break;
		
		case "ksochitam_24":
			dialog.text = "Tak-tak, "+pchar.name+", Przygotowuję się. Niedługo będę gotowy.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_24";
		break;
		
		case "ksochitam_25":
			dialog.text = "Więc co, "+pchar.name+". Czy mamy szczęście w naszych poszukiwaniach?";
			link.l1 = "Mieliśmy rację. To jest to. Indiański idol jest jednym z objawień.";
			link.l1.go = "ksochitam_26";
		break;
		
		case "ksochitam_26":
			dialog.text = "O! To musi być jeden z tych idoli, które miały teleportować ludzi do Tayasal! Mówiłem ci o nich, pamiętasz? Więc, w którą stronę skierowana jest Strzała Drogi?";
			link.l1 = "Jest skierowana na północny zachód. Zaznaczyłem kierunek na mapie. Chociaż narysowana linia przecina prawie całe Morze Karaibskie. Musimy znaleźć kolejne pojawienie się na Dominice, by odnaleźć Ksocheatem.";
			link.l1.go = "ksochitam_27";
		break;
		
		case "ksochitam_27":
			dialog.text = "Jestem pewien, że znajdziemy tam kolejny idol... zgadzasz się z moją hipotezą, "+pchar.name+"?";
			link.l1 = "Zgadzam się, Gino. Teraz nie traćmy czasu i zacznijmy szukać.";
			link.l1.go = "ksochitam_28";
		break;
		
		case "ksochitam_28":
			DialogExit();
			locations[FindLocation(pchar.location)].DisableEncounters = false; //энкаутеры открыть
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 20.0);
		break;
		
		case "ksochitam_29":
			dialog.text = "A więc co, "+pchar.name+", czy znalazłeś coś interesującego?";
			link.l1 = "Mieliśmy rację. To jest to. Indiański idol jest jednym z objawień.";
			link.l1.go = "ksochitam_30";
		break;
		
		case "ksochitam_30":
			dialog.text = "O! To musi być jeden z tych idoli, które miały teleportować ludzi do Tayasal! Mówiłem ci o nich, pamiętasz? No i co, gdzie wskazuje Strzała Drogi?";
			link.l1 = "Na północny zachód. Zaznaczyłem kierunek na mapie. Choć narysowana linia przecina prawie całe Morze Karaibskie. Musimy znaleźć kolejne pojawienie się na Kontynencie, aby odnaleźć Ksocheatem.";
			link.l1.go = "ksochitam_27";
		break;
		
		case "ksochitam_31":
			dialog.text = "Więc co, "+pchar.name+", czy znalazłeś drugi idol?";
			link.l1 = "Tak. Naszkicowałem kierunek wskazany przez Strzałę Drogi. Teraz znamy położenie Ksocheatem, to nie jest dokładna lokalizacja, ale wiemy, gdzie szukać! Przeszukam cały obszar, gdzie linie się krzyżują, i znajdę tę przeklętą wyspę!";
			link.l1.go = "ksochitam_32";
		break;
		
		case "ksochitam_32":
			dialog.text = "Cieszę się, słysząc tyle entuzjazmu w twoim głosie. Ale musimy się dobrze przygotować do nadchodzącej wyprawy, nie wiadomo, co tam napotkamy. Wątpię, że spotka nas tam miłe przyjęcie...";
			link.l1 = "Czy martwisz się czymś konkretnym, czy po prostu wyrażasz obawy?";
			link.l1.go = "ksochitam_33";
		break;
		
		case "ksochitam_33":
			dialog.text = "Pomyśl o tym, "+pchar.name+".. Ksocheatem został stworzony przez magię Majów wykonaną przez Kaneka. To nie jest naturalna formacja i ma w sobie złe i destrukcyjne moce. Nie wiadomo, co tam na nas czeka, wątpię, że znajdziemy tam słońce, spokojne morza, dziwki i łagodny wiatr.";
			link.l1 = "Dobrze, Gino. Rozważę twoje słowa i przygotuję się na wyprawę. Przygotuję mój statek i zadbam o mikstury oraz amunicję...";
			link.l1.go = "ksochitam_34";
		break;
		
		case "ksochitam_34":
			dialog.text = "Bardzo mądra decyzja. Cóż, wracamy na statek?";
			link.l1 = "Jasne! Chodźmy!";
			link.l1.go = "ksochitam_28";
		break;
		
		case "ksochitam_35":
			dialog.text = "Dotarliśmy, "+pchar.name+"! Uh, wiatr wyje!";
			link.l1 = "Tak, Gino, miałeś rację, nie ma słońca, które by nas przywitało... Nie widzę też żadnych dziwek. Właściwie to nie wiadomo, co nas tu w ogóle czeka.";
			link.l1.go = "ksochitam_36";
		break;
		
		case "ksochitam_36":
			dialog.text = "Cóż, wybrałeś takie złe miejsce do lądowania, Kapitanie! Wszędzie tylko skały i klify! A jak zamierzasz dostać się stąd do wnętrza wyspy?";
			link.l1 = "Nie widziałem żadnej innej odpowiedniej zatoki, gdzie można by wylądować na tej wyspie z powodu tej przeklętej burzy! Cokolwiek, to lepsze niż nic. Poradzę sobie znaleźć drogę wśród tych skał, miałem gorsze. Nie panikuj, przyjacielu!";
			link.l1.go = "ksochitam_37";
		break;
		
		case "ksochitam_37":
			dialog.text = "Nie lubię tej wyspy, "+pchar.name+"! To jest przerażające. A ta burza musi być związana z wyspą. To miejsce jest skazane na zagładę, to pewne!";
			link.l1 = "Ja też nie lubię tego miejsca, Gino! Ale ta wyspa istnieje, co oznacza, że historia o Kukulcanie jest prawdziwa. Wszyscy będziemy w niebezpieczeństwie, jeśli uda mu się dotrzeć do Tayasal z Maską...";
			link.l1.go = "ksochitam_38";
		break;
		
		case "ksochitam_38":
			dialog.text = "Spróbuj odnaleźć Maskę, Kapitanie! Jest ważniejsza niż wszystkie skarby świata! Musi być gdzieś w pobliżu! Gdy ją zdobędziemy, zniszczymy plany Kukulkana i nie pozwolimy mu zmienić przeszłości!";
			link.l1 = "A jak wygląda ta maska, wiesz?";
			link.l1.go = "ksochitam_39";
		break;
		
		case "ksochitam_39":
			dialog.text = "Nie mam pojęcia! Ale myślę, że ją rozpoznasz, to starożytny artefakt indiański, trudno go pomylić z czymkolwiek innym!";
			link.l1 = "Rozumiem. Będę mieć oczy szeroko otwarte! Dobrze, Gino, wracaj na statek! Nie musisz włóczyć się po wyspie, twoja głowa jest zbyt cenna, by ją ryzykować!";
			link.l1.go = "ksochitam_40";
		break;
		
		case "ksochitam_40":
			dialog.text = "Nie będę kłamał, Kapitanie, jestem kiepskim wojownikiem i nie czuję się tu komfortowo. Chcesz posłuchać rady? Każdy element Strażnika jest połączony z magią tej wyspy. Ksatl Cha wspomniał, że sztylet ma władzę nad miejscowymi mieszkańcami, choć nie wiem, co miał na myśli.\nZostanę na pokładzie. Zobaczysz mnie tam, jeśli będziesz potrzebował mojej pomocy.";
			link.l1 = "Dobrze. A teraz życz mi szczęścia, Gino!";
			link.l1.go = "ksochitam_41";
		break;
		
		case "ksochitam_41":
			dialog.text = "Powodzenia, "+pchar.name+"! Niech Bóg ci sprzyja i zachowa cię!";
			link.l1 = "... ";
			link.l1.go = "ksochitam_42";
		break;
		
		case "ksochitam_42":
			DialogExit();
			NextDiag.CurrentNode = "adversary";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "My_Campus", "quest", "quest1", "Ksochitam_JinoStay", 10.0);
			AddQuestRecord("Ksochitam", "6");
		break;
		
		case "adversary":
			dialog.text = "Jak się masz, "+pchar.name+". Potrzebujesz rady?";
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L1"))
			{
				link.l1 = "Ta cholernia wyspa roi się od nieumarłych, a te przeklęte szkielety są zaskakująco twarde. Nie mam pojęcia, jak z nimi walczyć.";
				link.l1.go = "adversary_1";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L2"))
			{
				link.l1 = "Jeśli pójdziesz w lewo od rozwidlenia, w końcu dotrzesz do groty. Ale dokąd mam się udać dalej? Obawiam się, że grota to ślepy zaułek...";
				link.l1.go = "adversary_2";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L3"))
			{
				link.l1 = "Znalazłem drogę do zalanej jaskini, możesz zanurkować do jej podwodnej części. Ale nie widzę tam żadnego wyjścia...";
				link.l1.go = "adversary_3";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L4"))
			{
				link.l1 = "Jeśli skręcisz w lewo na rozwidleniu, dotrzesz do groty. Ale dokąd powinienem iść dalej? Obawiam się, że grota to ślepy zaułek...";
				link.l1.go = "adversary_4";
			}
			if (CheckAttribute(pchar, "questTemp.Ksochitam.Adversary.L5"))
			{
				link.l1 = "Jest miejsce w dużej jaskini, gdzie możesz zanurkować do zalanej części. Ale wydaje się, że nie ma stamtąd wyjścia...";
				link.l1.go = "adversary_5";
			}
			link.l10 = "Wszystko jak dotąd w porządku, Gino, mam się dobrze.";
			link.l10.go = "exit";
			NextDiag.TempNode = "adversary";
		break;
		
		case "adversary_1":
			dialog.text = "Ksatl Cha wspomniał o Szponie Wodza. Spróbuj użyć go przeciwko szkieletom, Indianin powiedział, że ten sztylet ma władzę nad mieszkańcami Ksocheatem.";
			link.l1 = "Spróbuję na pewno!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L1");
		break;
		
		case "adversary_2":
			dialog.text = "Jak wygląda ta jaskinia?";
			link.l1 = "Cóż, to taka mała jaskinia w skale, jest zalana, a woda kołysze się na dnie niczym fale...";
			link.l1.go = "adversary_2_1";
		break;
		
		case "adversary_2_1":
			dialog.text = "Jeśli woda się kołysze, oznacza to, że jaskinia ma jakieś połączenie z morzem i nie może być ślepym zaułkiem. Szukaj przejścia, musi tam być.";
			link.l1 = "W drodze...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L2");
		break;
		
		case "adversary_3":
			dialog.text = "Jeśli istnieje droga do zalanej jaskini z głównej i jeśli woda kołysze się jak fala w głównej jaskini, to zalana jaskinia ma drugie przejście. Przeszukaj ją dokładniej, ale bądź ostrożny, bo się utopisz.";
			link.l1 = "Zaraz nurkuję...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L3");
		break;
		
		case "adversary_4":
			dialog.text = "A jak wygląda ta jaskinia?";
			link.l1 = "Cóż, jest dość duża z kilkoma jaskiniami, jest zalana i jest mała dziura z nieruchomą wodą...";
			link.l1.go = "adversary_4_1";
		break;
		
		case "adversary_4_1":
			dialog.text = "Jeśli woda jest spokojna, to jaskinia nie ma połączenia z morzem i może być ślepym zaułkiem.";
			link.l1 = "Myślałem tak samo. Szukałem tam długo i jest tylko jedno wejście, które jest również wyjściem...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L4");
		break;
		
		case "adversary_5":
			dialog.text = "Jeśli woda wciąż jest w jaskini, to może masz rację. Szukaj trochę dłużej, ale nie smuć się, jeśli nic nie znajdziesz. To prawdopodobnie ślepy zaułek.";
			link.l1 = "Widzę...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Ksochitam.Adversary.L5");
		break;
		
		case "adversary_6":
			dialog.text = ""+pchar.name+", Hiszpańskie statki nas atakują! To nie najlepszy czas na rozmowę!";
			link.l1 = "Tak, oczywiście...";
			link.l1.go = "exit";
			NextDiag.TempNode = "adversary_6";
		break;
		
		case "ksochitam_43":
			dialog.text = "Twoje szczęśliwe oczy mówią mi, że znalazłeś to, czego szukałeś.";
			link.l1 = "Tak. Skarby Miguela Dichoso i Maska Kukulkana. Teraz jego wcielenie nigdy nie będzie w stanie zmienić przyszłości!";
			link.l1.go = "ksochitam_44";
		break;
		
		case "ksochitam_44":
			dialog.text = "Niesamowite! Jesteś bohaterem, "+pchar.name+"... ";
			link.l1 = "Gino, jesteś pewien, że to wystarczy, by powstrzymać Kukulkana?";
			link.l1.go = "ksochitam_45";
		break;
		
		case "ksochitam_45":
			dialog.text = "Według Ksatl Cha - tak. I cytował Urakana. Jego ojciec Kanek był tym, który zaczął cały ten bałagan. Jakieś wątpliwości?";
			link.l1 = "Spotkałem w zatoce gościa z przeszłości - Alonso de Maldonado. Był w Tayasal, gdy Kanek odprawiał rytuał tworzenia Strażnika Prawdy. Został wciągnięty w dziurę czasoprzestrzenną, ale przeżył... Do dziś.";
			link.l1.go = "ksochitam_46";
		break;
		
		case "ksochitam_46":
			dialog.text = "";
			link.l1 = "Powiedział, że muszę zamknąć sam portal, aby na dobre chronić nasz świat. Aby to zrobić, muszę zniszczyć Maskę na jakimś ołtarzu w Tayasal.";
			link.l1.go = "ksochitam_47";
		break;
		
		case "ksochitam_47":
			dialog.text = "I ty zamierzasz iść do Tayasal? To szaleństwo! "+pchar.name+", masz maskę, a inkarnacja Kukulkana nie będzie w stanie nic zrobić! I sam Kanek jest tego pewien! Dlatego Urakan wysłał Ksatl Cha, aby znalazł Ksocheatem - aby zdobyć Maskę i ją zniszczyć.";
			link.l1 = "A co, jeśli ten Urakan planował zniszczyć maskę w Tayasal?";
			link.l1.go = "ksochitam_48";
		break;
		
		case "ksochitam_48":
			dialog.text = ""+pchar.name+", tylko jeden człowiek zdołał dotychczas uciec z Tayasal żywy i był to Miguel Dichoso. Także Maldonado, ale to był wyjątek. Nawet jeśli wcielenie Kukulkana przeniesie się w przeszłość, zostanie zabite przez starożytnych Majów!";
			link.l1 = "A co, jeśli go nie zabiją, ale rozpoznają?";
			link.l1.go = "ksochitam_49";
		break;
		
		case "ksochitam_49":
			dialog.text = "Więc planujesz wyprawę do Tayasal?";
			link.l1 = "Nie wiem, Gino. Naprawdę nie wiem...";
			link.l1.go = "ksochitam_50";
		break;
		
		case "ksochitam_50":
			dialog.text = "Więc zastanów się, po co byś to robił? Słyszałeś moją opinię. Teraz to zależy od ciebie..."+pchar.name+"  Czy zabierzesz mnie do St. John's?";
			link.l1 = "Oczywiście, Gino. Wypływamy jak najszybciej. Mam już dość tej okropnej wyspy.";
			link.l1.go = "ksochitam_51";
		break;
		
		case "ksochitam_51":
			DialogExit();
			NextDiag.CurrentNode = "ksochitam_52";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			AddQuestRecord("Ksochitam", "16");
			pchar.quest.Ksochitam_gohome.win_condition.l1 = "location";
			pchar.quest.Ksochitam_gohome.win_condition.l1.location = "sentjons_town";
			pchar.quest.Ksochitam_gohome.function = "Ksochitam_ArriveHome";
			pchar.questTemp.Ksochitam = "gohome";
		break;
		
		case "ksochitam_52":
			dialog.text = "Czy wkrótce będziemy w domu, "+pchar.name+"? Naprawdę tęsknię za moimi flakonami i probówkami...";
			link.l1 = "Tak-tak, Gino, wkrótce będziemy na Antigui.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ksochitam_52";
		break;
		
		case "ksochitam_53":
			dialog.text = "Cieszę się, że wreszcie wróciliśmy! Nie mogę sobie wyobrazić, jak wy, marynarze, spędzacie tyle czasu na swoich statkach...";
			link.l1 = "To kwestia nawyku, Gino.";
			link.l1.go = "ksochitam_54";
		break;
		
		case "ksochitam_54":
			dialog.text = "Położę się na moim łóżku stojąc na twardym gruncie z wielką przyjemnością... Mam nadzieję, "+pchar.name+", że oszczędziłeś sobie pomysłu odwiedzenia Tayasal?";
			link.l1 = "Jeszcze nie wiem, Gino. Szczerze mówiąc, wciąż nie jestem pewien.";
			link.l1.go = "ksochitam_55";
		break;
		
		case "ksochitam_55":
			dialog.text = "Zniszcz maskę Kukulcana i żyj bez trosk, Kapitanie. Jeśli chcesz, rozpuścimy maskę w najsilniejszym kwasie, jaki posiadam. Nie będę chował urazy za taką sprawę.";
			link.l1 = "Wiesz, poczekam trochę. Zawsze będziemy mieli czas, by to zniszczyć.";
			link.l1.go = "ksochitam_56";
		break;
		
		case "ksochitam_56":
			dialog.text = "To twój wybór. Jeśli zdecydujesz się oszczędzić ten świat od tego artefaktu - przyjdź do mnie. Wdzięczność za wspaniałą podróż, Kapitanie!";
			link.l1 = "Zawsze do usług, Gino. Do zobaczenia!";
			link.l1.go = "exit";
			NextDiag.TempNode = "first time";
			AddDialogExitQuestFunction("Ksochitam_TripComplete");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Jesteś "+GetSexPhrase("złodziej, panie! Strażnicy, łapcie go","złodziejka, dziewczyno! Strażnicy, złapcie ją ")+"!!!","Spójrz tylko na to! Ledwie się zamyśliłem, a ty postanowiłeś przeszukać moją skrzynię! Łapać złodzieja!!!","Straże! Napad! Łapcie złodzieja!!!");
			link.l1 = "Cholera!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}

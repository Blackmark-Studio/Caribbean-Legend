// Фадей Московит
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int rate;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Sharlie"))
			{
				if (pchar.questTemp.Sharlie == "fadey")
				{
					dialog.text = "Czym mogę służyć, Monsieur? Nie rozmawiam z osobami, których nie znam. Jeśli przybyłeś, by pogawędzić lub zapytać, kiedy w 1640 roku Hiszpański Srebrny Pociąg dotrze do Maricaibo, to muszę cię rozczarować. Nie marnuję czasu na puste rozmowy.";
					link.l1 = "Dzień dobry, Monsieur Fadey. Być może mnie jeszcze nie znasz, ale znasz mojego brata. Pozwól, że się przedstawię - Charles de Maure, brat Michela de Monper.";
					link.l1.go = "Sharlie";
					break;
				}
				if (pchar.questTemp.Sharlie == "takeknife" && !CheckAttribute(pchar, "questTemp.Persian"))
				{
					dialog.text = "Aha, znowu ty, Charles! Kak dela? Co tym razem?";
					link.l1 = "Powiedziałeś, że cię okradziono... Czy znalazłeś winowajców?";
					link.l1.go = "Sharlie_8";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "fadey")
				{
					dialog.text = "Więc Charles, czy rozmawiałeś już z tym dzikusem?";
					link.l1 = "Mam... Dlatego wróciłem do ciebie.";
					link.l1.go = "Tichingitu";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "dublon")
				{
					dialog.text = "Ach, to znowu ty, mój drogi przyjacielu! No, przyniosłeś okup w dublonach dla Indianina?";
					if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu80"))
					{
						if (PCharDublonsTotal() >= 80) // belamour legendary edition
						{
							link.l1 = "Tak. Oto twoje 80 dublonów.";
							link.l1.go = "Tichingitu_7";
						}
						else
						{
							link.l1 = "Nie, jeszcze nie zebrałem wystarczająco.";
							link.l1.go = "exit";
						}
					}
					else
					{
						if (PCharDublonsTotal() >= 100) // belamour legendary edition
						{
							link.l1 = "Tak. Oto twoje sto dublonów.";
							link.l1.go = "Tichingitu_7";
						}
						else
						{
							link.l1 = "Nie, jeszcze nie zebrałem wystarczająco dużo.";
							link.l1.go = "exit";
						}
					}
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "begin")
				{
					dialog.text = "Ha, cóż to sam Monsieur de Maure! Mówiłem, wchodź, nie stój tam! Co cię sprowadza do mego domu?";
					link.l1 = TimeGreeting()+"Fadey, mój brat kazał mi się do ciebie zwrócić. Powiedział, że pomożesz mi znaleźć pracę.";
					link.l1.go = "trial";
					// опоздал
					if (CheckAttribute(pchar, "questTemp.Trial.late")) {
						link.l1.go = "trial_late";
					}
					break;
				}
				if (pchar.questTemp.Sharlie == "trial" && !CheckAttribute(npchar, "quest.vodka"))
				{
					dialog.text = "Ha, to ty! Co cię tu sprowadza, Monsieur de Maure?";
					link.l1 = TimeGreeting()+", Fadey. Mój brat nalegał, żebym z tobą o tym nie rozmawiał, ale nie mogłem się powstrzymać... ";
					link.l1.go = "vodka";
					break;
				}
				// belamour legendary edition пиратская линейка -->
				if(CheckAttribute(pchar, "questTemp.Mtraxx.GiveMeSlaves") && pchar.questTemp.Mtraxx.GiveMeSlaves == "Baster")
				{
					dialog.text = "Ach, stary przyjacielu! Wejdź, wejdź, "+pchar.name+"! Jak się masz?";
					link.l1 = TimeGreeting()+", Fadey. Cieszę się, że cię widzę. Właściwie, mam do omówienia ważną sprawę. Czarne złoto.";
					link.l1.go = "Slaves";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Mtraxx.GiveMeSlaves") && pchar.questTemp.Mtraxx.GiveMeSlaves == "FindGold")
				{
					dialog.text = "Ach, to znowu ty, mój drogi przyjacielu! Masz łup? Znalazłeś wystarczająco dużo dublonów?";
					if(PCharDublonsTotal() >= 150)
					{
						link.l1 = "Tak, Monsieur Fadey! Oto twoje złoto.";
						link.l1.go = "Slaves_2";
					}
					else
					{
						link.l1 = "Nie, po prostu przyszedłem. Wciąż szukam odpowiedniej sumy.";
						link.l1.go = "exit";
					}
					
					link.l2 = "Fadey, właśnie wpadłem na pomysł. Już nie potrzebuję niewolników. Musisz mi wybaczyć, zobaczymy się później!";
					link.l2.go = "Slaves_3";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "Baster")
				{
					dialog.text = "Ach, mój stary przyjacielu! Wejdź, wejdź, "+pchar.name+"! Jak się masz?";
					if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves"))
					{
						if(pchar.questTemp.Mtraxx.GiveMeSlaves == "Deal" || pchar.questTemp.Mtraxx.GiveMeSlaves == "WithoutSlaves")
						{
							link.l1 = TimeGreeting()+", znów potrzebuję twojej pomocy.";
						}
					}
					else
					{
						link.l1 = TimeGreeting()+", Fadey. Cieszę się, że cię widzę. Mam z tobą interesy.";
					}
					link.l1.go = "pistols";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "FindMoney")
				{
					dialog.text = "Ach, to znowu ty, mój drogi przyjacielu! No cóż, znalazłeś pieniądze?";
					if(PCharDublonsTotal() >= 300)
					{
						link.l1 = "Mam, monsieur Fadey! Oto twoje 300 doblonów.";
						link.l1.go = "pistols_4D";
					}
					if(sti(Pchar.money) >= 40000)
					{
						link.l2 = "   Mam, monsieur Fadey! Oto twoje 40 000 pesos.";
						link.l2.go = "pistols_4P";
					}
					if(PCharDublonsTotal() < 300 || sti(Pchar.money) < 40000) 
					{
						link.l3 = "Nie, tylko odwiedzam. Wciąż szukam odpowiedniej kwoty.";
						link.l3.go = "exit";
					}
					link.l4 = "Przepraszam, Fadey, ale nie stać mnie na to. Spróbuję poradzić sobie sam. Do zobaczenia!";
					link.l4.go = "pistols_x";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "Today")
				{
					dialog.text = "Wejdź, wejdź, "+pchar.name+"Widzę w twych oczach, że chcesz usłyszeć o moich sukcesach.";
					link.l1 = "Dokładnie, Fadey. Ufaję, że masz to, czego pragnę.";
					link.l1.go = "pistols_5";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "FindMoney")
				{
					dialog.text = "Ach, to znowu ty, mój drogi przyjacielu! Więc, czy znalazłeś pieniądze?";
					if(PCharDublonsTotal() >= 300)
					{
						link.l1 = "Weź 300 doblonów. Poproszę marynarzy, żeby zanieśli tę skrzynię na mój statek. Och, co ja bym bez ciebie zrobił, Fadey?! Nie masz pojęcia, jak bardzo mi pomogłeś!";
						link.l1.go = "pistols_5D";
					}
					if(sti(Pchar.money) >= 40000)
					{
						link.l2 = "Weź 40 000 pesos. Poproszę marynarzy, aby zanieśli tę skrzynię na mój statek. Och, co bym bez ciebie zrobił, Fadey?! Nie masz pojęcia, jak bardzo mi pomogłeś!";
						link.l2.go = "pistols_5P";
					}
					if(PCharDublonsTotal() < 300 || sti(Pchar.money) < 40000) // возможность найти без отказа
					{
						link.l3 = "Nie, po prostu przeszedłem się. Wciąż próbuję zebrać wystarczająco.";
						link.l3.go = "exit";
					}
					link.l4 = "Przepraszam, Fadey, jestem spłukany. Zatrzymaj zaliczkę, mam nadzieję, że wystarczy, aby pokryć twoje wydatki związane z tą umową, a ja spróbuję poradzić sobie sam. Do zobaczenia!";
					link.l4.go = "pistols_x";
					break;
				}
				// <-- legendary edition
				if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && pchar.questTemp.Guardoftruth.Baster_church == "seek")
				{
					dialog.text = "Ach, Znaczony-Ja znaczy "+pchar.name+" ! No dalej, powiedz mi, co dla mnie masz!";
					link.l1 = TimeGreeting()+", Fadey. Miło cię widzieć. Przyszedłem porozmawiać z tobą o interesach.";
					link.l1.go = "guardoftruth";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && pchar.questTemp.Guardoftruth.Baster_church == "find" && !CheckAttribute(npchar, "quest.utensil"))
				{
					dialog.text = TimeGreeting()+", "+pchar.name+"Założę się, że jesteś niecierpliwy, by odkryć wyniki mojej rozmowy o poszukiwaniu duszy z księdzem.";
					link.l1 = "Oczywiście, że tak! Jak poszło?";
					link.l1.go = "guardoftruth_9";
					break;
				}
				if (CheckAttribute(npchar, "quest.utensil") && PCharDublonsTotal() >= 250)
				{
					dialog.text = "Ach, wybacz mi, jestem tak rozproszony przez brzęk w twoich kieszeniach!";
					link.l1 = "Taka chciwość, Fadey! Oto twój złoty.";
					link.l1.go = "guardoftruth_11";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "guadeloupe")
				{
					dialog.text = "Aha, mój stary przyjacielu! Wejdź, wejdź, "+pchar.name+"! Więc, masz coś nowego?";
					link.l1 = "Cześć, Fadeju. Ponownie proszę o twoje wsparcie.";
					link.l1.go = "guardoftruth_14";
					break;
				}
				dialog.text = "Czymże jesteś? Posągiem? Jeśli coś masz, gadaj, jeśli nie, to spadaj, "+pchar.name+"!";
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "start" && CheckNCountPersian() > 0)
				{// персидские клинки
					link.l2 = "Spójrz, Fadey. Przypuszczam, że to perski szamszir, być może jeden z tych skradzionych z twojej kolekcji?";
					link.l2.go = "persian";
				}
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "one" && CheckNCountPersian() > 0)
				{
					link.l2 = "Mam dla ciebie dobre wieści. Mam tutaj jeszcze jeden perski szamszir dla ciebie.";
					link.l2.go = "persian_6";
				}
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "two" && CheckNCountPersian() > 0)
				{
					link.l2 = "Mam trzeci perski szamszir. Tak jak prosiłeś, przywiozłem go, jak tylko mogłem.";
					link.l2.go = "persian_9";
				}
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "cirass")
				{
					link.l2 = "Przyszedłem w sprawie lekkiej zbroi, o której rozmawialiśmy.";
					link.l2.go = "persian_13";
				}
				if(CheckAttribute(npchar, "quest.ropes") && GetDataDay() == 20) // торговля канатами
				{
					link.l3 = "Fadey, chciałbym kupić trochę twojej słynnej liny.";
					link.l3.go = "ropes";
				}
				link.l1 = "Fadey, potrzebuję twojej pomocy.";
				link.l1.go = "help";
 				link.l9 = "Nie, nic na tę chwilę.";
				link.l9.go = "exit";
			}
			else
			{
				dialog.text = "Czym mogę służyć, monsieur? Nie rozmawiam z ludźmi, których nie znam.";
				link.l1 = "O, po prostu wpadłem zobaczyć, kto tu mieszka.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "Sharlie":
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("baster_town", "reload", "houseSp1");
			dialog.text = "Ach, więc ty jesteś młodszym bratem starego dobrego Michela! To zmienia sytuację! Proszę, proszę, Monsieur, usiądź. Czy chciałbyś wznieść kieliszek wódki za nasze spotkanie? Mam jeszcze kilka butelek i byłoby przyjemnością podzielić jedną z nich z bratem dobrego przyjaciela, da!";
			link.l1 = "Przebacz mi, Monsieur Fadey, ale picie dziś nie wchodzi w grę. Wolałbym od razu przejść do interesów.";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			dialog.text = "Co wy mówicie! Ten lokalny rum to słaba lurka w porównaniu z rosyjską wódką! Nie wiecie, co tracicie, niech mnie Morze pochłonie, jeśli kłamię! Dobrze, do rzeczy. Słucham, Charles.";
			link.l1 = "Panie, obawiam się, że to, co mam zamiar powiedzieć, będzie dość nieprzyjemne, ale niestety, obowiązek nakazuje mi to uczynić! Michel powiedział mi, że jesteś mu winien całkiem sporo pieniędzy z hazardu. Nakazał również, abyś przekazał mi te pieniądze, ponieważ mój brat jest... niezdolny, by osobiście się z tobą spotkać w tej chwili.";
			link.l1.go = "Sharlie_2";
		break;
		
		case "Sharlie_2":
			dialog.text = "O, młody człowieku! Oczywiście, że wszystko pamiętam i przyznaję, że jestem winien twojemu bratu. Hazardowy dług jest święty, honorowanie tego obowiązku to jedyna rzecz, która ratuje nas przed śmiertelnym chaosem i niebezpiecznymi bandytami! Ale błagam, zrozum moją sytuację! Niedawno przydarzyła mi się nieprzyjemna historia - zostałem okradziony w najbardziej bezczelny sposób!\nPrzeklęci złodzieje zabrali wszystko, co mogli, wszystko, co zarobiłem przez lata pracy, moje pieniądze i moją bezcenną kolekcję! Po prostu nie mogę teraz spłacić długu, nie\nAle, Monsieur de Maure, nie rezygnuję ze swoich zobowiązań! Proszę tylko, abyś spotkał mnie w połowie drogi. Ponieważ teraz nie mam żadnej monety w moim posiadaniu, oferuję ten doskonały rzadki sztylet. Spójrz na to!\nTo prawdziwe arcydzieło ze stali, duma mojej skradzionej kolekcji. Poza tym został zaczarowany przez indiańskich szamanów i ma silne ukryte moce! Indianie nazwali go Pazurem Wodza\nNigdy nie zgodziłbym się go oddać, ponieważ zapłaciłem za ten sztylet wielką sumę, znacznie większą niż mój dług, ale biorąc pod uwagę okoliczności i moją relację z twoim starszym bratem, jestem gotów ci go przekazać. Bierz, to bardzo dobra umowa!";
			link.l1 = "Wolałbym naprawdę pieniądze zamiast noża...";
			link.l1.go = "Sharlie_3";
		break;
		
		case "Sharlie_3":
			dialog.text = "Ale nie mam pieniędzy, a mam ten rzadki zaczarowany artefakt! Czy naprawdę myślisz, drogi przyjacielu, że zaoferowałbym ci ten wspaniały magiczny sztylet zamiast jakichś śmieciowych srebrnych monet w innych okolicznościach? Pesos można znaleźć wszędzie, nawet leżące na ulicy! Musisz przyznać, że jestem w tarapatach. Moje serce krwawi, gdy nawet myślę o rozstaniu się z tym niesamowitym dziełem sztuki, ale dług hazardowy to dług honorowy, więc jestem gotów dać go tylko tobie, chociaż jest mi bardzo drogi, ponieważ jesteś prawdziwym człowiekiem honoru i prawdziwym przyjacielem.";
			link.l1 = "Dobrze, skoro przysięgasz, że nie masz żadnych pieniędzy, wezmę ten twój magiczny sztylet. Mam nadzieję, że uda mi się go sprzedać za dobrą cenę...";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			dialog.text = "'Sprzedać to'!? Wynoś się stąd, stal-a znaczy się, Charles! Niech to szlag, ledwie mogę uwierzyć własnym uszom! Oddaję moje najdroższe posiadanie, za które dostałbym co najmniej dziesięć razy więcej w Europie, a ty bezczelnie stoisz i mówisz, że po prostu to zastawisz!? Dlaczego ten sztylet, młody człowieku, uratował życie człowieka! Pozwól, że ci opowiem-";
			link.l1 = "„A jaka jest ta ukryta moc, o której wspomniałeś?”";
			link.l1.go = "Sharlie_5";
		break;
		
		case "Sharlie_5":
			dialog.text = "O, ho ho! Teraz Charles, jestem dobrym chrześcijaninem, wiesz, nie jakimś indiańskim szamanem. Nie mam sposobu, by znać wszystkie ukryte właściwości tego ostrza. Ale one istnieją, oh tak! Trzymaj ten sztylet w ręce, a poczujesz moc w nim zawartą sam! Weź to, beri! Jak ci się podoba! Czujesz coś?";
			link.l1 = "Hm... Nic nie czuję. Chociaż dobrze leży w mojej dłoni.";
			link.l1.go = "Sharlie_6";
		break;
		
		case "Sharlie_6":
			dialog.text = "Ah ha! No proszę! Ale to zaledwie najmniejsza z jego cech. Jeśli będziesz dzierżyć ten sztylet w walce, jestem pewien, że pokaże swoją potęgę na wiele dramatycznych sposobów! No więc, bierzesz go?";
			link.l1 = "Cóż, czy mam wybór? Wezmę to, skoro nie masz monety...";
			link.l1.go = "Sharlie_7";
		break;
		
		case "Sharlie_7":
			GiveItem2Character(pchar, "knife_01");
			PlaySound("interface\important_item.wav");
			//Log_Info("You've received the Chief's Claw'");
			sld = ItemsFromID("knife_01");
			sld.Weight = 1.5;
			sld.price = 0;
			AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
			AddMapQuestMarkCity("FortFrance", false);
			dialog.text = "Dziękuję, Charles. Nie pożałujesz tego, och, z pewnością nie pożałujesz! Proszę bardzo. I nie zapomnij pozdrowić Michela ode mnie! Powiedz mu, żeby czasem wpadł, jak tylko będzie miał okazję.";
			link.l1 = "O, powiem mu...";
			link.l1.go = "exit";
			link.l2 = "Powiedziałeś, że zostałeś okradziony... Czy znalazłeś winowajców?";
			link.l2.go = "Sharlie_8";
			pchar.questTemp.Sharlie = "takeknife";
			AddQuestRecord("Sharlie", "18-1");
			sld = characterFromId("Mishelle");	
			sld.greeting = "mishelle_2";
			
			// Sinistra - Старт квеста "Деньги на деревьях"
			PChar.quest.MOT_BarbieSpawn.win_condition.l1 = "location";
			PChar.quest.MOT_BarbieSpawn.win_condition.l1.location = "BasTer_town";
			PChar.quest.MOT_BarbieSpawn.win_condition = "MOT_BarbieSpawn";
			//убрать запрет боёвок на Мартинике
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_town")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_townhall")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_prison")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_fort")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_ammo")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("LeFransua_town")], false);
			LocatorReloadEnterDisable("FortFrance_townhall", "reload2", false);
			LocatorReloadEnterDisable("FortFrance_townhall", "reload3", false);
			sld = &Locations[FindLocation("FortFrance_prison")];
			sld.locators_radius.item.detector1 = 0.5;
		break;
		
		case "Sharlie_8":
			dialog.text = "Problem w tym, że tego nie mam. Ci łotrzykowie wyczyścili cały dom, uciekli ze srebrem, złotem, moimi oszczędnościami z lat ciężkiej pracy. Zazwyczaj by mnie to nie martwiło, w końcu prawdziwy dżentelmen, nawet jeśli straci wszystko, co posiada, nie powinien okazywać emocji! Pieniądze muszą być tak daleko poniżej dżentelmena, że nie warto się nimi przejmować. Ale najgorsze jest to, że zagarnęli moją wspaniałą kolekcję perskich szamszirów! Nie ma takiej kolekcji ani w Nowym, ani w Starym Świecie. Naprawdę niezwykłe perskie szable kawaleryjskie...";
			link.l1 = "Perskie miecze, mówisz? Brzmi to całkiem interesująco. Więc jesteś kolekcjonerem?";
			link.l1.go = "Sharlie_9";
		break;
		
		case "Sharlie_9":
			dialog.text = "Cóż, lubię zbierać rzadkie rzeczy... Słuchaj, Charles, może mógłbyś mi pomóc w tej sprawie...";
			link.l1 = "Pomoc? Ale jak? Masz na myśli złapanie złodziei?";
			link.l1.go = "Sharlie_10";
		break;
		
		case "Sharlie_10":
			dialog.text = "Niet. Nie jestem szczególnie zainteresowany złodziejami. Chciałbym odzyskać moje perskie szable kawaleryjskie. Jeśli je znajdziesz, na pewno wynagrodzę ci to, obiecuję.";
			link.l1 = "Hm. Ale gdzież ja mam ich szukać? Po Karaibach? A może po całym świecie?";
			link.l1.go = "Sharlie_11";
		break;
		
		case "Sharlie_11":
			dialog.text = "Cóż, może zobaczysz je na wyspach u ulicznych handlarzy, ci łajdacy nie potrafią nawet pojąć wartości tych kawaleryjskich szabel i z pewnością sprzedadzą je za grosze. Więc jeśli gdziekolwiek zobaczysz perskie szable, przynieś je do mnie. Czy będziesz w stanie je rozpoznać?";
			link.l1 = "Myślę, że tak zrobię. Dobrze, będę mieć oczy szeroko otwarte i jeśli zobaczę jakieś niezwykłe ostrza pasujące do opisu, na pewno je do ciebie przyniosę.";
			link.l1.go = "Sharlie_12";
			link.l2 = "Wiesz, nie jestem ekspertem od wyrafinowanej broni. Obawiam się, że nie będę mógł ci pomóc. Byłoby nieuczciwe z mojej strony dawać ci fałszywą nadzieję.";
			link.l2.go = "Sharlie_13";
		break;
		
		case "Sharlie_12":
			dialog.text = "Horosho! Mam nadzieję, że będziesz miał szczęście i znajdziesz te artefakty, a ja ci to wynagrodzę. Powodzenia w łowach, stalker- to znaczy kapitanie! Da, Charles, możesz sobie wyobrazić, że ostatnio miałem kolejną próbę rabunku!\nZłodziej próbował dostać się do mojego domu zaledwie kilka dni temu\nTo było dla mnie za dużo! Tym razem jednak nie uciekł mi, udało mi się go złapać, dobrze obiłem i przekazałem strażnikom w więzieniu w mieście. Mam nadzieję, że wkrótce go powieszą!";
			link.l1 = "Czy myślisz, że to jeden z tych złodziei, którzy zwędzili twoje szamszиры?";
			link.l1.go = "Sharlie_14";
			pchar.questTemp.Persian = "start";
			// --> скимитар 021012
			pchar.questTemp.Persian.skimitar = "true";
			pchar.quest.Persian.win_condition.l1 = "item";
			pchar.quest.Persian.win_condition.l1.item = "blade_23";
			pchar.quest.Persian.function = "Persian_FindSkimitar";
		break;
		
		case "Sharlie_13":
			dialog.text = "Szkoda, ale nie ma co płakać nad rozlanym mlekiem. Da, Charles, wyobraź sobie, że niedawno miałem kolejną próbę rabunku!\nZłodziej próbował dostać się do mojego domu zaledwie kilka dni temu\nTo było dla mnie za wiele! Jednak nie uciekł przede mną: udało mi się go złapać, porządnie sprać i wysłać do lokalnego więzienia. Nie można być szczęśliwym kosztem czyjegoś nieszczęścia. Mam nadzieję, że wkrótce go powieszą!";
			link.l1 = "Czy myślisz, że to jeden z łotrów, którzy zwędzili twoje szamsziry?";
			link.l1.go = "Sharlie_14";
			pchar.questTemp.Persian = "end";
		break;
		
		case "Sharlie_14":
			dialog.text = "Nie, nie sądzę. On był za pieniądzem. Złapałem go w moim pokoju, przeszukującego moje skrzynie\nIndianin z jakiejś głębokiej dżungli na hiszpańskim wybrzeżu. Wygląda śmiesznie, inaczej niż ci lokalni tutaj. Cały pokryty wojennym malowaniem i ubrany w kolorowy kostium... Powinieneś odwiedzić loch i zobaczyć tego błazna na własne oczy, jeśli chcesz, póki jeszcze żyje.";
			link.l1 = "Hm... Może wpadnę do niego z wizytą.";
			link.l1.go = "Sharlie_15";
		break;
		
		case "Sharlie_15":
			dialog.text = "Śmiało, zerknij na ten cyrk dziwaków... No dobrze, Charles, to była miła pogawędka. Pomocnych wiatrów w drodze powrotnej na Martynikę, poputniy veter!";
			link.l1 = "Wszystkiego najlepszego, Fadey.";
			link.l1.go = "exit";
			SetQuestHeader("Tichingitu");
			AddQuestRecord("Tichingitu", "1");
			pchar.questTemp.Sharlie.Tichingitu = "true";
			AddDialogExitQuestFunction("SetTichingituJail");
			SetFunctionTimerCondition("FreeTichingituOver", 0, 0, 10, false);
			pchar.questTemp.Sharlie = "takeknife";
		break;
		
		case "Tichingitu":
			DelLandQuestMark(npchar);
			dialog.text = "Jakże interesujące! Słucham.";
			link.l1 = "Fadey, rozmawiałem z tym Indianinem. I przyszedłem do ciebie, by poprosić o pomoc w jego uwolnieniu. Biedny drań chciał tylko coś zjeść...";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "Hahaha, a ty uwierzyłeś w tę bajkę? Młodzieńcy dzisiaj są tacy łatwowierni...";
			link.l1 = "Fadey, mogę być młodszy od ciebie, ale nawet ja potrafię odróżnić prawdę od kłamstwa. Poza tym, naprawdę uważasz, że powieszenie to odpowiednia kara za takie przestępstwo? Wydaje się to przesadzone. W domu dostałbyś tylko kilka batów albo piętno za recydywę.";
			link.l1.go = "Tichingitu_2";
		break;
		
		case "Tichingitu_2":
			dialog.text = "Nadmierne!? Włamał się do mojego domu! Ten dzikus nigdy nie powinien tu przychodzić! Co byś zrobił na moim miejscu? Jestem pewien, że wywróciłbyś jego wnętrzności na zewnątrz i zrobił z niego pokarm dla robaków, co?!";
			link.l1 = "Nie, nie zrobiłbym tego, Fadey, Wciąż jesteś zły z powodu kradzieży twojej kolekcji szamszirów. Gdyby to się nie stało, byłbyś bardziej skłonny dać temu głupiemu czerwonoskóremu porządny łomot i kopniaka w zad, czyż nie mam racji?";
			link.l1.go = "Tichingitu_3";
		break;
		
		case "Tichingitu_3":
			dialog.text = "Ahhhh, Charles... Jesteś taki jak twój brat... Dobrze. Rozwiążemy to jak uczciwi biznesmeni. Skoro tak bardzo chcesz tego Indianina, zrekompensuj mi szkody moralne i materialne, które spowodował, a ja z kolei powiem komendantowi, że nie chcę wnosić oskarżeń. Jak ci się to podoba?";
			link.l1 = "Ile?";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			dialog.text = "Ha, już zaczynasz poznawać zwyczaje Karaibów, Charles. Sto pięćdziesiąt złotych dublonów, ani kopiejki mniej.";
			link.l1 = "O Fadeju, niech Bóg ma litość...";
			link.l1.go = "Tichingitu_5";
		break;
		
		case "Tichingitu_5":
			dialog.text = "Dobrze, dobrze. Sto złotych dublonów. Ale to moja ostateczna oferta. I mówimy o dublonach, nie peso. Nasz bankier z pewnością będzie w stanie wymyślić tę kwotę do wymiany.";
			if(PCharDublonsTotal() >= 100) // belamour legendary edition
			{
				link.l1 = "Mam teraz kwotę, której potrzebujesz. Proszę, oto twoje sto dublonów.";
				link.l1.go = "Tichingitu_7";
			}
			if(CheckCharacterPerk(pchar, "Trustworthy"))
			{
				notification("Trustworthy", "Trustworthy");
				link.l2 = " (Godny zaufania) Fadey, posłuchaj... Rozumiem twoje frustracje, ale jestem jedynym, kto jest gotów zrekompensować ci tę niedogodność prawdziwymi pieniędzmi.";
				link.l2.go = "Tichingitu_7_TW";
			}
			else notification("Perk Check Failed", "Trustworthy");
			link.l3 = "Dobrze, pójdę po to, czego potrzebujesz.";
			link.l3.go = "Tichingitu_6";
		break;
		
		case "Tichingitu_7_TW":
			dialog.text = "Masz tu przyszłość, przyjacielu, mogę ci to powiedzieć. Dobrze! Osiemdziesiąt złotych - i ani monety mniej!";
			link.l1 = "";
			link.l1.go = "Tichingitu_6";
			pchar.questTemp.Sharlie.Tichingitu80 = true;
		break;
		
		case "Tichingitu_6":
			dialog.text = "I pospiesz się, Charles! Masz tylko dziesięć dni do jego egzekucji.";
			link.l1 = "Będę o tym pamiętał. Żegnaj!";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie.Tichingitu = "dublon";
		break;
		
		case "Tichingitu_7":
			if(CheckAttribute(pchar,"questTemp.Sharlie.Tichingitu80"))
			{
				RemoveDublonsFromPCharTotal(80);
				DeleteAttribute(pchar,"questTemp.Sharlie.Tichingitu80");
			}
			else RemoveDublonsFromPCharTotal(100); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "Bardzo dobrze. Od razu napiszę notatkę i przystawię pieczęć, chwileczkę... proszę bardzo. Daj to komendantowi i możesz zabrać swojego Indianina. Nie wiem, czemu tak się o niego martwisz, ale to twój problem. Co zamierzasz zrobić, pokazać go na maskaradzie? Haha, co za pomysł!";
			link.l1 = "Pan Bóg wszystko widzi, Fadey. Ratowanie życia człowieka to szlachetny czyn.";
			link.l1.go = "Tichingitu_8";
		break;
		
		case "Tichingitu_8":
			GiveItem2Character(pchar, "letter_1");
			ChangeItemDescribe("letter_1", "itmdescr_letter_1_Fadey");
			PlaySound("interface\important_item.wav");
			dialog.text = "Zgadzam się z twoim pierwszym stwierdzeniem, ale drugie jest dyskusyjne, Charles. Co jeśli uratujesz mordercę lub gwałciciela przed sprawiedliwością, która czeka go na końcu sznura? Bah, nieważne, to już nie mój problem. Niech Bóg będzie z tobą. Udaj się do komendanta, zanim twój czerwonoskóry przyjaciel zbladnie z powodu pętli wokół szyi...";
			link.l1 = "Już idę. Do zobaczenia później, Fadey.";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie.Tichingitu = "pay";
			SetFunctionLocationCondition("Tichingitu_AddQuestMark", "baster_prison", false);
			QuestPointerToLoc("BasTer_town", "reload", "reload_jail");
			QuestPointerDelLoc("baster_town", "reload", "houseSp1");
		break;
		
		case "vodka":
			dialog.text = "Wyglądasz posępnie, przyjacielu! Domyślam się, że masz dla mnie złe wieści?";
			link.l1 = "Tak to się przedstawia, a jakże. Powiem ci wprost, Fadey: Michel powiedział, że nabrałeś mnie z tym 'szponem wodza', gównem jakimś. Powiedział, że to nie żaden artefakt, i że mógłbym to kupić od każdego ulicznego handlarza za parę setek pesos. Popytałem wśród ulicznych sprzedawców zajmujących się metalowymi wyrobami. Podali mi dokładnie taką cenę.";
			link.l1.go = "vodka_1";
			npchar.quest.vodka = "true";
		break;
		
		case "vodka_1":
			dialog.text = "Och, Monsieur de Maure... Jestem zraniony! Jestem zaskoczony przez twojego brata. Ci półgłówki na ulicy mogą gadać, co im się podoba, ale on! Powiedz mi, Charles, jeśli ktoś przyniósłby ci starą dwuręczną rycerską szablę z czasów Karola Wielkiego i zaoferował, że ci ją sprzeda, ile byś za nią dał?";
			link.l1 = "Czekaj, dwuręczny? Czy ty sobie ze mnie żartujesz, Fadey? Co ja miałbym zrobić z jakimś zardzewiałym toporem kata? To jest siedemnasty wiek Pana Jezusa Chrystusa! Nie dałbym za to ani jednego peso!";
			link.l1.go = "vodka_2";
		break;
		
		case "vodka_2":
			dialog.text = "Ach, teraz widzisz swoją krótkowzroczność, mój przyjacielu! Nigdy nie dojdziesz do celu z takim nastawieniem. A gdybyś przyniósł mi taki artefakt, zapłaciłbym za niego trzysta dublonów. Pytasz dlaczego? Ponieważ to antyk, historyczny skarb trudny do znalezienia w dzisiejszych czasach! Nie rozumiesz, a jednak osądzasz! \nZ Bogiem i Jego Błogosławioną Matką jako moimi świadkami, Pazur Wodza to mistrzowsko wykonany sztylet, moje źródła mówią, że należał do samego Corteza. TEGO Hernana Corteza! Legendarnego konkwistadora, który złupił Tenochtitlan i pojmał cesarza Azteków! A ty drwisz i mówisz, że to pospolite śmieci!\nPoza tym, już ci mówiłem, że to nie jest zwykły sztylet, to zaczarowany sztylet! Czy jesteś jeszcze tak zielony, że nie widziałeś wszystkich cudów Karaibów? Zaklęcia i magia, rytuały i klątwy? Charles, to jest Nowy Świat, ojczyzna Majów i Azteków, których wiedza na temat takich diabelskich sztuk osiągnęła wysokości niepojęte dla nas chrześcijan!\nTen sztylet ma ukryte moce. Niestety, nikt jeszcze nie wie, jakie to moce. Masz unikalną, niesamowitą szansę dowiedzieć się samemu, do czego jest zdolny, a ty wciąż twierdzisz, że to 'gówno' i twój biedny, stary przyjaciel Fadey próbował cię oszukać!\nGdybym tylko miał wystarczająco pieniędzy, by spłacić dług twojemu bratu, od razu wymieniłbym go z powrotem za twoje nikczemne monety... To jest bardzo cenny przedmiot i jego wartość jest mierzona w czymś więcej niż tylko w pieniądzach, da!";
			link.l1 = "Dobrze, dobrze, uspokój się Fadey. Wierzę ci. Twoje argumenty są całkiem przekonujące, a płomienny zapał, który pokazujesz, to albo świadectwo twojej szczerości, albo twojej niezrównanej przebiegłości.";
			link.l1.go = "vodka_3";
		break;
		
		case "vodka_3":
			dialog.text = "Dziękuję! Dobrze się spisałeś, Charles, że nie obraziłeś się i przyszedłeś bezpośrednio do mnie po wyjaśnienie. Ufajmy, że teraz sprawa jest załatwiona?";
			link.l1 = "Tak, Monsieur Fadey. Całkowicie. Teraz proszę, pozwól mi się oddalić...";
			link.l1.go = "vodka_4";
		break;
		
		case "vodka_4":
			PlaySound("Voice\English\sharlie\Fadey Moskovit-04.wav");
			dialog.text = "Stój, Charles! Szczerze mówiąc, podoba mi się twój styl. Może pewnego dnia moglibyśmy zostać najlepszymi przyjaciółmi. A czemu by nie zrobić pierwszego kroku ku tej przyjaźni już teraz? Schłodziłem dwie butelki doskonałej rosyjskiej wódki w lodowatej wodzie źródlanej na dole w piwnicy. Co ty na to, otworzymy butelkę za zdrowie twojego brata?";
			link.l1 = "Hm. Przykro mi, Monsieur Fadey, ale już czas, bym wypłynął na morze. Trochę się śpieszę.";
			link.l1.go = "vodka_no";
			link.l2 = "Ostatnim razem zaproponowałeś, a ja odmówiłem... Byłoby niegrzecznie odmówić dwa razy. Dobrze, Fadey. Wchodzę!";
			link.l2.go = "vodka_5";
		break;
		
		case "vodka_no":
			dialog.text = "To szkoda. W porównaniu do wódki, rum to tylko woda, tanie rozwodnienie. Ale skoro się spieszysz, nie będę cię dłużej zatrzymywał. Dobrych łowów, Charles!";
			link.l1 = "To samo dla ciebie, Monsieur Fadey...";
			link.l1.go = "exit";
		break;
		
		case "vodka_5":
			dialog.text = "To mi się podoba! Wspaniale! Usiądź i odpocznij! Proszę, Monsieur, czuj się jak u siebie w domu, a ja pójdę po wódkę. Och, jakże tęskniłem za popołudniowymi posiedzeniami z przyjaciółmi! Ach, wódka jest miła i zimna, na pewno ci się spodoba, na zdrowie! Pozwól, że podam trochę kiszonek i wędzonej szynki.";
			link.l1 = "...";
			link.l1.go = "vodka_6";
		break;
		
		case "vodka_6":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = true;
			sld.startLocation = "BasTer_houseSp1";
			sld.startLocator = "bottle";
			sld = ItemsFromID("lcheer");
			sld.shown = true;
			sld.startLocation = "BasTer_houseSp1";
			sld.startLocator = "sit2";
			DoQuestReloadToLocation("BasTer_houseSp1", "sit", "sit2", "Sharlie_DrinkWithFadey");
			NextDiag.CurrentNode = "vodka_7";
		break;
		
		case "vodka_7":
			dialog.text = "";
			link.l1 = "Whoa... Więc, powiedz mi, Fadey, j-jak to dz-iała? Hic! Wypiliśmy... d-dwie b-butle wód-ki... nawiasem mówiąc! - wyglądasz t-twardo t-trzeźwy, a ja... pijany jak bela. J-jak to możliwe, co?";
			link.l1.go = "vodka_8";
		break;
		
		case "vodka_8":
			dialog.text = "Charles, mój druh, zrelaksuj się. Co ma do tego skunks? Dopiero co opróżniliśmy butelkę wyśmienitej wódki. Połóż się spać, a obudzisz się jak nowo narodzony. Nawet głowa ci się rozjaśni bez kaca. Zobaczysz.";
			link.l1 = " T-tak, wódka...to... to absolutnie wspaniałe, ta wódka. Nigdy nie piłem czegoś podobnego.";
			link.l1.go = "vodka_9";
		break;
		
		case "vodka_9":
			dialog.text = "Ha! Masz absolutną rację! Taka wódka była robiona według tajnych receptur i sprowadzana z mojej ojczyzny, Rosji, a i tam nie każdy wie, jak ją odpowiednio zrobić. Kupuję tylko najlepsze! Jak ten trunek tutaj, którego ty i ja mieliśmy okazję skosztować.";
			link.l1 = "B-ale powiedz mi, Fadey: j-jak możesz p-pić t-tak dużo i nie upić się? J-jak to robisz, co? P-podziel się ze mną sekretem. M-może to się p-przyda później... Cz-k!";
			link.l1.go = "vodka_10";
		break;
		
		case "vodka_10":
			dialog.text = "Ha! Cóż, nie możesz porównywać nas, młody Charlsie! Spójrz tylko na siebie, chudy jak bat. Na dodatek, nie jesteś przyzwyczajony do poważnego picia, tak! Ale ponieważ jesteśmy prawdziwymi przyjaciółmi, podzielę się z tobą kilkoma sekretami, jak pić i nie zsikać się w portki.";
			link.l1 = "Pro-szę z-rób...hik!";
			link.l1.go = "vodka_11";
		break;
		
		case "vodka_11":
			dialog.text = "„Cóż, jeśli chcesz pić i nie zostać natychmiast powalonym, musisz przestrzegać kilku kluczowych zasad. Najważniejsze, nigdy nie pij, jeśli twój żołądek jest pusty. Zjedz coś treściwego, zanim zacznie się sesja picia\nPo drugie, nie zapomnij zjeść czegoś po każdym kieliszku. Mięso lub ryba będą najlepsze, coś miłego i słonego. Po trzecie, nie płucz wnętrza ust wódką, połykaj ją od razu\nRównież, mały – nie więcej niż pół pinty – strzał przed daniem głównym przygotuje twoje ciało na przyjęcie poważnych dawek alkoholu. Nie przesadzaj z tym przystawką, w przeciwnym razie efekt będzie zupełnie odwrotny i rozbijesz się przed wyruszeniem w rejs\nWreszcie, kluczowe jest zdyscyplinowane trening, regularne picie umiarkowanych ilości rumu lub innych rodzajów alkoholu zwiększy twoją odporność na nie.”";
			link.l1 = "Hm-mm... T-tak to się robi! Na pewno...hik!.. zapamiętam wszystkie twoje wsk-zówki, Fadey. D-dziękuję. A t-teraz myślę, że dobrze by było, gdybym się trochę zdrzemnął, bo teraz nie czuję się najlepiej.";
			link.l1.go = "vodka_12";
		break;
		
		case "vodka_12":
			dialog.text = "Odpocznij trochę, Charles. Mieliśmy miły wieczór, ty i ja! Dobrego polowania życzę!";
			link.l1 = "Do-do-świadania, Fadey! Idę do - hick! - Spełniacza Życzeń!";
			link.l1.go = "vodka_13";
		break;
		
		case "vodka_13":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = false;
			sld = ItemsFromID("lcheer");
			sld.shown = false;
			pchar.questTemp.CanDrink = true; // Шарль теперь знает секреты выпивки, это ему потом пригодится
			LAi_SetSitType(npchar);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			NextDiag.CurrentNode = "First time";
		break;
		
		case "trial":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("BasTer");
			pchar.quest.Sharlie_TrialOver.over = "yes"; //снять таймер
			dialog.text = "Co, naprawdę powiedział, że ci pomogę?";
			link.l1 = "„Cóż, mniej więcej. Czy dasz pomocną dłoń bratu twojego dawnego przyjaciela? To nie tak, że proszę o jałmużnę jak żebrak. Proszę cię, byś dał mi szansę zarobić trochę pieniędzy.”";
			link.l1.go = "trial_1";
		break;
		
		case "trial_late":
			dialog.text = "O, Charles! Jesteś spóźniony. Gdybyś przyszedł wcześniej, znalazłbym coś odpowiedniego dla ciebie, ale teraz - prosti. Nie martw się, przejdź się po miastach, porozmawiaj z ludźmi. W Karaibach jest dużo do zrobienia.";
			link.l1 = "Rozumiem, to godne pożałowania. Żegnaj!";
			link.l1.go = "trial_late_1";
		break;
		
		case "trial_late_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Trial");
		break;

		case "trial_1":
			dialog.text = "Hm. Niet, nie odmówię ci, oczywiście. Jeśli chcesz nakarmić człowieka, nie dawaj mu ryby, ale wędkę. Czy to nie prawda, Monsieur de Maure? Potrzebujesz pracy... To proste. Porozmawiam z człowiekiem, którego znam, i polecę cię mu. A reszta zależy od tego, jak dobrze wykonasz zadanie.";
			link.l1 = "Cudownie. Z kim muszę porozmawiać?";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			dialog.text = "Przyjdź jutro do sklepu. Czekać tam na ciebie będzie człowiek o imieniu Gerard LeCroix. On da ci trochę roboty. Będzie siedział w tej kolonii tylko do jutra wieczorem. Zobacz się z nim szybko i wykonaj robotę jak należy. Nie stawiaj mnie w niezręcznej sytuacji.";
			link.l1 = "Umowa stoi. Dziękuję, Fadey!";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			DialogExit();
			SetFunctionTimerCondition("Trial_StartLine", 0, 0, 1, false); // таймер
			pchar.questTemp.Trial = "start";
			AddQuestRecord("Trial", "1");
		break;
		// belamour legendary edition пиратская линейка -->
		case "Slaves":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(npchar);
			dialog.text = "Ach, jak mogę ci pomóc, mój przyjacielu?";
			link.l1 = "Fadey, słuchaj, naprawdę muszę kupić pięćdziesięciu niewolników od przemytników. Problem w tym, że jestem dla nich nieznanym i potrzebuję, byś mnie przedstawił. Bez ciebie nawet mnie nie wysłuchają, a to sprawa życia i śmierci dla bardzo ważnej osoby.";
			link.l1.go = "Slaves_1";
		break;
		
		case "Slaves_1":
			dialog.text = "Oh ho! Rozwijasz swój interes, widzę! Jakże to zyskowne! Pomogę ci, drogi przyjacielu. Ale jak wiesz, nie pracuję za darmo. Będzie to kosztować 150 złotych dublonów, aby przekonać sprzedawcę o twoich dobrych intencjach zakupu murzynów i, oczywiście, nieco więcej za moje pilne wysiłki...";
			if(PCharDublonsTotal() >= 150)
			{
				link.l1 = "Nie spodziewałem się niczego innego, Monsieur Fadey! Oto twoje złoto.";
				link.l1.go = "Slaves_2";
			}
			else
			{
				link.l1 = "Idę natychmiast do lichwiarza! Trzymaj się, Monsieur Fadey, zaraz wracam!";
				link.l1.go = "exit";
				pchar.questTemp.Mtraxx.GiveMeSlaves = "FindGold"; 
			}
			
			link.l2 = "Fadey, zdaje się, że coś wymyśliłem i już nie potrzebuję murzynów. Przepraszam. Do zobaczenia!";
			link.l2.go = "Slaves_3";
		break;
		
		case "Slaves_2":
			RemoveDublonsFromPCharTotal(150);
			pchar.questTemp.Mtraxx.GiveMeSlaves = "kapster";
			locations[FindLocation("Shore29")].DisableEncounters = true; //энкаутеры закрыть
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l1 = "Hour";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l1.start.hour = 22.00;
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l1.finish.hour = 23.00;
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2 = "Timer";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l3 = "location";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l3.location = "Shore29";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.function = "MtraxxGiveMeSlavesKapsterInShore"; // прибыли
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1 = "Timer";
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.hour  = 23.0; // не пришли, значит гудбай
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.function = "MtraxxGiveMeSlavesKapsterInShoreLate"; // опоздание
			AddQuestRecord("Roger_3", "23");
			dialog.text = "Doskonałe, przyjacielu. Ale jeśli chcesz mnie oszukać z potrzebą twojego zakupu i jest ona dla bezwartościowych celów, bardzo mnie rozgniewasz. Nie chcesz tego. Jutro o dziesiątej przy zachodzie słońca na plaży Capster zorganizuję ci spotkanie, nie wystawiaj mnie.";
			link.l1 = "Nie masz się czym martwić, wrócę po towar.";
			link.l1.go = "exit";
		break;
		
		case "Slaves_3":
			DialogExit();
			AddQuestRecord("Roger_3", "22");
			pchar.questTemp.Mtraxx.GiveMeSlaves = "WithoutSlaves";
		break;
		
		case "pistols":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(npchar);
			dialog.text = "Witaj, witaj! Powiedz mi, dobry człowieku, co cię sprowadza do mego skromnego domu?";
			link.l1 = "Potrzebuję broni. Lokalni kupcy nie są w stanie znaleźć ilości, której potrzebuję, ale myślę, że ty możesz mi pomóc.";
			link.l1.go = "pistols_1";
		break;
		
		case "pistols_1":
			dialog.text = "Po pierwsze, powiedz mi, drogi przyjacielu, czego dokładnie potrzebujesz. Potem powiem ci dokładnie, czy mogę ci pomóc.";
			link.l1 = "Potrzebuję 30 pistoletów żołnierskich, dwóch muszkietów lontowych, 70 naboi do nich i 90 mikstur leczniczych.";
			link.l1.go = "pistols_2";
		break;
		
		case "pistols_2":
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves"))
			{
				if(pchar.questTemp.Mtraxx.GiveMeSlaves == "Deal" || pchar.questTemp.Mtraxx.GiveMeSlaves == "WithoutSlaves")
				{
					dialog.text = pchar.name+", przerażasz mnie. Najpierw pięćdziesięciu Murzynów, teraz broń. Czy próbujesz wzniecić bunt niewolników, przyjacielu?";
					link.l1 = "Bardzo spostrzegawczy, Fadey. Jak już wcześniej mówiłem, to wszystko jest konieczne dla ocalenia jednej ważnej osoby. Nie martw się, zostanie wyrwana z objęć Hiszpanów, więc twoja reputacja tutaj nie ucierpi.";
					link.l1.go = "pistols_3";
					break;
				}
			}
			dialog.text = "To dobrze słyszeć. Mogę pomóc.";
			link.l1 = "Cieszę się, że to słyszę. Ile?";
			link.l1.go = "pistols_4";
		break;
		
		case "pistols_3":
			dialog.text = "Cieszę się, że się wytłumaczyłeś. I jeśli to naprawdę ma coś wspólnego z Hiszpanami, to ci pomogę. Ale jeśli okaże się, że mnie oszukałeś, będę bardzo zły.";
			link.l1 = "Ufaj mi trochę, Fadey. Ile?";
			link.l1.go = "pistols_4";
		break;
		
		case "pistols_4":
			dialog.text = "Dobrze, więc ... pistolety i parę muszkietów, z prochem i kulami do każdego... Dlatego ... nie mogę obiecać, że zdobędę absolutnie wszystko, o co prosiłeś, ale zrobię wszystko, co w mojej mocy. Tymczasem potrzebuję zaliczki w wysokości 40 000 pesos, lub 300 dublonów, jeśli wolisz.";
			if(PCharDublonsTotal() >= 300)
			{
				link.l1 = "Weź dublony, Fadey. Akurat mam przy sobie kilka.";
				link.l1.go = "pistols_4D";
			}
			if(sti(Pchar.money) >= 40000)
			{
				link.l2 = "Wszystkie moje dublony się skończyły, bierz pesos, Fadey.";
				link.l2.go = "pistols_4P";
			}
			if(PCharDublonsTotal() < 300 || sti(Pchar.money) < 40000) // возможность найти без отказа
			{
				link.l3 = "Muszę porozmawiać z moim bankierem. Zaraz wracam!";
				link.l3.go = "exit";
				pchar.questTemp.Mtraxx.MagicBox = "FindMoney";
			}
			link.l4 = "Przepraszam, Fadey, ale nie stać mnie na to. Spróbuję poradzić sobie sam. Do zobaczenia!";
			link.l4.go = "pistols_x";
		break;
		
		case "pistols_4D":
			SetFunctionTimerCondition("Mtraxx_MagicBoxready", 0, 0, 1, false);
			RemoveDublonsFromPCharTotal(300);
			pchar.questTemp.Mtraxx.MagicBox = "Tomorow";
            dialog.text = "Przyjdź jutro, "+pchar.name+", a ja zapewnię ci materiały, których potrzebujesz.";
			link.l1 = "Więc nie będę przeszkadzać. Do zobaczenia jutro!";
			link.l1.go = "exit";
		break;
		
		case "pistols_4P":
			AddMoneyToCharacter(pchar, -40000);
			SetFunctionTimerCondition("Mtraxx_MagicBoxready", 0, 0, 1, false);
            pchar.questTemp.Mtraxx.MagicBox = "Tomorow";
            dialog.text = "Przyjdź jutro, "+pchar.name+", a ja dostarczę ci materiały, których potrzebujesz.";
			link.l1 = "W takim razie nie będę przeszkadzać. Do zobaczenia jutro!";
			link.l1.go = "exit";
		break;
		
		case "pistols_X":
			DialogExit();
			DeleteAttribute(pchar,"questTemp.Mtraxx.MagicBox");
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves")) DeleteAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves");
		break;
		
		case "pistols_5":
			dialog.text = "Cóż, mój chłopcze, miałem szczęście znaleźć wszystko, o co prosiłeś, w tak krótkim czasie. Powinieneś być wdzięczny! Teraz, ostateczna zapłata. Daj mi dokładnie tyle samo, ile było dane jako zaliczka, i zabierz swoje bronie.";
			if(PCharDublonsTotal() >= 300)
			{
				link.l1 = "Weź 300 dubloonów. Moi ludzie zabiorą broń na mój statek. Co bym bez ciebie zrobił, Fadey? Nie masz pojęcia, jak bardzo mi pomogłeś!";
				link.l1.go = "pistols_5D";
			}
			if(sti(Pchar.money) >= 40000)
			{
				link.l2 = "Weź 40 000 pesos. Moi ludzie zabiorą broń na mój statek. Co bym bez ciebie zrobił, Fadey? Nie masz pojęcia, jak bardzo mi pomogłeś!";
				link.l2.go = "pistols_5P";
			}
			if(PCharDublonsTotal() < 300 || sti(Pchar.money) < 40000) // возможность найти без отказа
			{
				link.l3 = "No cóż, do diabła, jak mogłem zapomnieć o pieniądzach? Zaraz wracam.";
				link.l3.go = "exit";
				pchar.questTemp.Mtraxx.MagicBox = "FindMoney";
			}
			link.l4 = "Przepraszam, Fadey, jestem spłukany. Zatrzymaj zaliczkę, mam nadzieję, że wystarczy, by pokryć twoje wydatki związane z tą umową, a ja spróbuję sobie poradzić sam. Do zobaczenia!";
			link.l4.go = "pistols_x";
		break;
		
		case "pistols_5D":
			Log_Info("Fadey's weapons are loaded on the ship");
			RemoveDublonsFromPCharTotal(300);
			pchar.questTemp.Mtraxx.MagicBox = "Full";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves")) DeleteAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves");
            dialog.text = "Pomoc potrzebującym to honor. Pomoc tym, którzy płacą to przyjemność. Następnym razem, gdy będziesz w Basse-Terre, nie zapomnij mnie odwiedzić, by się przywitać.";
			link.l1 = "To absurd - być w Basse-Terre i nie zobaczyć mojego przyjaciela Fadeya! Do następnego razu!";
			link.l1.go = "exit";
		break;
		
		case "pistols_5P":
			Log_Info("Fadey's weapons are loaded on the ship");
			AddMoneyToCharacter(pchar, -40000);
			pchar.questTemp.Mtraxx.MagicBox = "Full";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves")) DeleteAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves");
            dialog.text = "Pomaganie potrzebującym to honor. Pomaganie tym, którzy płacą, to przyjemność. Następnym razem, gdy będziesz w Basse-Terre, koniecznie odwiedź mnie, by się przywitać.";
			link.l1 = "To absurd - być w Basse-Terre i nie zobaczyć się z moim przyjacielem Fadeyem! Do następnego razu!";
			link.l1.go = "exit";
		break;
		// <-- legendary edition

		case "guardoftruth":
			dialog.text = "No cóż, kto by wątpił, że przybywasz w interesach, przyjacielu! Niestety, nie mam teraz wódki, by ci zaoferować, wypiłem wszystko. Powiedz mi, w jakie teraz tarapaty wpadłeś.";
			link.l1 = "Do miejscowej parafii pewien kaper ofiarował złoty pektoral z lazurytem w zamian za przebaczenie jego grzechów. To unikalny i cenny przedmiot. Problem w tym, że ten krzyż został skradziony z innej parafii. Co więcej, podczas rabunku zamordowano księdza.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "O niepokalana Bogurodzico! Nie mówże!";
			link.l1 = "Aj. Reprezentuję okradzionych parafian i próbuję zwrócić krzyż jego pierwotnym właścicielom.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Szlachetny czyn, i bardzo pobożny. Próbujesz zdobyć punkty u Wszechmogącego?";
			link.l1 = "Ale lokalny ksiądz odmawia mi jego zwrotu, mimo wszystko, co mu powiedziałem. Nie pojmuję tego. Jak można spokojnie umieścić skradziony krzyż z krwią niewinnego człowieka na nim w Domu Bożym? To bluźnierstwo!";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "No cóż, technicznie rzecz biorąc, każdy poświęcony kielich nosi krew niewinnego Chrystusa...ale odbiegam od tematu. Rozumiem, że chcesz, bym ci pomógł?";
			link.l1 = "Tak! Masz niemały wpływ w Basse-Terre. Cieszycie się szacunkiem, więc być może kapłan wysłucha waszych napomnień.";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = ""+pchar.name+", czy opowiedziałeś naszemu księdzu dokładną historię tego skradzionego krzyża?";
			link.l1 = "Oczywiście! Odwołałem się do jego religijnych uczuć, do chrześcijańskiej solidarności, do jego przeklętego sumienia na miłość boską, ale zamknął uszy.";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Hm... Próbowałeś użyć innych metod, aby go przekonać?";
			link.l1 = "Masz na myśli przekupstwo? Nie zamierzam przekupywać księdza. Gdyby był bankierem, kupcem, a nawet gubernatorem, spróbowałbym rozwiązać problem w ten sposób, ale nie księdza!";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "Mój drogi naiwny przyjacielu, jeśli uszy księdza rzeczywiście są zamknięte na głos sumienia, to z pewnością jego ręce będą otwarte na złoto... Albo odwrotnie. Pomogę ci, myślę, że trzymanie takiego splugawionego skarbu tutaj z pewnością spowoduje większe kłopoty w przyszłości. Jednakże, to będzie wymagało pewnych wydatków."link.l1 ="Dlaczego mnie to nie dziwi? Ile tym razem?";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Przyjdź jutro, "+pchar.name+", nie mogę jeszcze określić ceny. Ale ten skradziony krzyż będziesz mieć, bądź pewien.";
			link.l1 = "Bardzo dobrze Fadey, nie będę ci już więcej przeszkadzać. Do zobaczenia jutro!";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			DialogExit();
			pchar.questTemp.Guardoftruth.Baster_church = "wait";
			SetFunctionTimerCondition("GuardOT_FadeyTimer", 0, 0, 1, false);
			AddQuestRecord("Guardoftruth", "29");
		break;
		
		case "guardoftruth_9":
			dialog.text = "Tak jak obiecałem, mam krzyż. Co do szczegółów... och, zapomnij o nich... wszelkie bzdury odpuszczone przez przelaną krew naszego Drogocennego Zbawiciela";
			link.l1 = "Ile jestem ci winien?";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			dialog.text = "Dwieście pięćdziesiąt dublonów. Na pokrycie moich wydatków, a oczywiście doceniłbym trochę ekstra za moją sprawiedliwą pomoc...";
			if(PCharDublonsTotal() >= 250) // belamour legendary edition
			{
				link.l1 = "Tak jest, Monsieur Fadey. Oto twoje złoto.";
				link.l1.go = "guardoftruth_11";
			}
			else
			{
				link.l1 = "Muszę przynieść złoto z mojej kajuty. Zaraz wracam.";
				link.l1.go = "exit";
				npchar.quest.utensil = "true";
			}
		break;
		
		case "guardoftruth_11":
			DeleteAttribute(npchar, "quest.utensil");
			dialog.text = "Dobrze.  Oto skradziony krzyż.";
			link.l1 = "Dziękuję, Fadey. Nawet nie możesz sobie wyobrazić, ile dla mnie zrobiłeś!";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			RemoveDublonsFromPCharTotal(250); // belamour legendary edition
			GiveItem2Character(pchar, "jewelry34");
			//Log_Info("You've received a golden cross with lazurite");
			PlaySound("interface\important_item.wav");
			dialog.text = "Zawsze cieszę się, mogąc pomóc życzliwemu - a co ważniejsze - hojnemu przyjacielowi. Zaglądaj częściej. Może napijemy się wódki, gdy zostanie mi dostarczona z ojczyzny.";
			link.l1 = "Z przyjemnością!";
			link.l1.go = "guardoftruth_13";
		break;
		
		case "guardoftruth_13":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Guardoftruth.Baster_church");
			AddQuestRecord("Guardoftruth", "30");
		break;
		
		case "guardoftruth_14":
			dialog.text = "Cóż, cóż, morze jeszcze cię nie pochłonęło! Opowiedz mi. Jakie nieszczęścia przywiodły cię tym razem do moich drzwi?";
			link.l1 = "Nie wiem, czy nazwać to nieszczęściem, czy nie, ale mimo wszystko jestem tutaj. Fadey, pierwszego dnia, kiedy się spotkaliśmy, dałeś mi rzadki sztylet, Pazur Wodza. Teraz wiem, że wcześniej należał do człowieka imieniem Archibald Calhoun. Proszę, powiedz mi, co wiesz o tym człowieku.";
			link.l1.go = "guardoftruth_15";
		break;
		
		case "guardoftruth_15":
			dialog.text = "Nic nie da się przed tobą ukryć, "+pchar.name+"  Widzisz wszystko na wylot, tak jak twój brat. Tak, wygrałem ten sztylet w grze w kości od Calhouna. Kto to jest? Sam nie mam pojęcia. Spotkaliśmy się przypadkiem w tawernie, zaczęliśmy rozmawiać, trochę wypiliśmy, a on zaczął opowiadać mi o jakichś grzechach z przeszłości, które go przytłaczają...";
			link.l1 = "Kim ty jesteś, jego spowiednikiem? Jakie grzechy?";
			link.l1.go = "guardoftruth_16";
		break;
		
		case "guardoftruth_16":
			dialog.text = "Archibald był pochłonięty wspomnieniem jakiegoś człowieka, który został zamęczony na śmierć przez Inkwizycję z jego powodu i innych niewinnych dusz, które zabił. Nazywał siebie Judaszem. Mówił, że Bóg go karze za grzechy, a Inkwizycja go ściga\nWspomniał, że sam hiszpański inkwizytor Vincento chce jego śmierci i wysłał najemników, aby go ścigali po Karaibach. Potem alkohol wygrał z jego zdrowym rozsądkiem i zagraliśmy o ten stary sztylet.";
			link.l1 = "Czy to wszystko? Nigdy więcej go nie widziałeś?";
			link.l1.go = "guardoftruth_17";
		break;
		
		case "guardoftruth_17":
			dialog.text = "Oczywiście, że nie, on już nie żyje. Banda nikczemnych piratów wysłała jego fluit do Skrzyni Daviego Jonesa, a całą załogę do Mictlantecuhtli. Prawdę mówiąc, plotki głosiły, że zostali zaatakowani przez profesjonalistów przebranych za piratów... agentów Inkwizycji. Mówią, że ojciec Vincento zawsze dopada swojego człowieka.";
			link.l1 = "Archibald Calhoun żyje. Widziałem go niedawno wraz z pewnym Williamem Patersonem. Służy jako jego pierwszy oficer.";
			link.l1.go = "guardoftruth_18";
		break;
		
		case "guardoftruth_18":
			dialog.text = "O ho, cóż za niespodzianka! Archibald przynajmniej może złapać oddech pod skrzydłami kapitana Patersona. Jest w dobrym towarzystwie. Hiszpanie boją się Pattersona jak zarazy. Nie odważą się spiskować przeciwko Archibaldowi, gdy jest pod opieką Pattersona.";
			link.l1 = "Czy znasz Patersona?";
			link.l1.go = "guardoftruth_19";
		break;
		
		case "guardoftruth_19":
			dialog.text = "Kto nie zna Williama Patersona!? On to nowicjusz na Karaibach, tak jak ty. I tak jak ty już zdobył ogromną reputację. Pan Patterson jest najbliższym przyjacielem pułkownika Foxa i ma dobre stosunki z samym lordem Windsor, generalnym gubernatorem wszystkich angielskich kolonii na Karaibach. Często odwiedza pałac gubernatora w Port Royal na Jamajce.";
			link.l1 = "Zrozumiałem. Dzięki za informacje, Fadey!";
			link.l1.go = "guardoftruth_20";
		break;
		
		case "guardoftruth_20":
			dialog.text = "Och, nie ma o czym mówić, przyjacielu. Odwiedź mnie kiedyś! Dobrego polowania!";
			link.l1 = "Zdecydowanie!";
			link.l1.go = "guardoftruth_21";
		break;
		
		case "guardoftruth_21":
			DialogExit();
			pchar.questTemp.Guardoftruth.Archy = "portroyal";
			AddQuestRecord("Guardoftruth", "62");
			// эскадру Патерсона - в Порт-Рояль
			Group_SetAddress("Willy_group", "Jamaica", "quest_ships", "quest_ship_1");
			pchar.quest.GuardOT_jamaica.win_condition.l1 = "location";
			pchar.quest.GuardOT_jamaica.win_condition.l1.location = "Jamaica";
			pchar.quest.GuardOT_jamaica.function = "GuardOT_PortRoyalArrive";
		break;
		
		// персидские клинки
		case "persian":
			dialog.text = "Rzućmy okiem, "+pchar.name+"... Da! To jedno z nich! To mój chłopak, zrobiłeś mi dzień! Gdzie to znalazłeś?";
			link.l1 = "To nie ma znaczenia. Ważne jest, że to wróciło do ciebie.";
			link.l1.go = "persian_1";
		break;
		
		case "persian_1":
			dialog.text = "Zapłacę dobrze za twoje dokładne dochodzenie. Trzysta złotych dublonów powinno być wystarczającą nagrodą za twoje trudy...";
			link.l1 = "Czy płacisz mi częścią z dublonów, które wcześniej ze mnie wycisnąłeś? Chociaż, oczywiście, ich nie odrzucę. Oto twój szamszir.";
			link.l1.go = "persian_2";
		break;
		
		case "persian_2":
			sTemp = CheckNIdentifyPersian();
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			pchar.questTemp.Persian = "one";
			dialog.text = "Dzięki, mój przyjacielu! Dziękuję za miecz i za twoje sarkastyczne słowa. Jesteś mądry ponad swoje lata, "+pchar.name+", ale ludzkie więzi przyjaźni przewyższają wartość złota. A skoro mowa o złocie, - zapłacę ci w pełni. Oto, weź swoje dublony.";
			link.l1 = "Dzięki.";
			link.l1.go = "persian_3";
		break;
		
		case "persian_3":
			TakeNItems(pchar, "gold_dublon", 300);
			//Log_Info("You've received 300 doubloons");
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
			dialog.text = "A skoro już mówimy o więzach przyjaźni, twojej i mojej w szczególności, "+pchar.name+" Mam coś, co cię bardzo zainteresuje.";
			link.l1 = "Niech zgadnę, więcej wódki?";
			link.l1.go = "persian_4";
		break;
		
		case "persian_4":
			dialog.text = "Ha! Wódka jest dobra, ale to nie jedyna rzecz, z której znana jest moja ojczyzna. Istnieje specjalny materiał, który produkuje tylko Rosja. Otrzymuję ten materiał od moich kontaktów w domu, aby handlować tutaj. Każdy kapitan go pragnie, ponieważ poprawia każdą łódź. Mówię o konopnych linach\nLiny odporne na wilgoć i sól morską. Mówią, że to najlepszy materiał do takielunku\nCo miesiąc otrzymuję pewną ilość z Rewalu. Zwykle mój magazyn ma kilkaset zwojów w połowie każdego miesiąca. Więc, "+pchar.name+", I am offering to sell you a batch of fifty coils. Ten doubloons a coil\nI have only two terms: first, I will keep your ropes until the 20th of every month; second, you can buy only the whole batch. Fifty coils for five hundred doubloons. Confidentially speaking, "+pchar.name+", they say that there are certain places where you can resell those ropes for a much greater price, but what do I know!\I am completely satisfied with the current state of my operation and don't need to find resellers myself. If you find a good merchant, you can turn a fine profit.";
			link.l1 = "Zrozumiano. To świetna oferta, Fadey! Myślę, że skorzystam z okazji, którą mi przedstawiłeś. Czyli, co dwudziestego dnia miesiąca, pięćset dublonów za pięćdziesiąt sztuk?";
			link.l1.go = "persian_5";
		break;
		
		case "persian_5":
			AddQuestRecordInfo("Unique_Goods", "2");
			dialog.text = "Tak. Idź odebrać swój zakup. Ale czekaj, czekaj, drogi przyjacielu! Oprócz tej szamszyry, którą zwróciłeś mi z prawdziwej dobroci, były jeszcze dwie inne. Błagam cię, jeśli je znajdziesz, przynieś je z powrotem do mnie, a zapłacę ci więcej niż uczciwą cenę za ich zwrot.";
			link.l1 = "Zdecydowanie, Fadey. Jeśli ich znajdę, przyprowadzę z powrotem.";
			link.l1.go = "exit";
			if (CheckNCountPersian() > 0)
			{
				link.l2 = "Dobre wieści dla ciebie. Mam kolejny perski szamszir.";
				link.l2.go = "persian_6";
			}
			npchar.quest.ropes = "true";
		break;
		
		case "persian_6":
			dialog.text = "O, mój drogi przyjacielu! Właśnie otarłeś moje łzy! Pozwól, że rzucę okiem... Da! To jest to, mój cenny szamszir! Oto, jak obiecałem, trzysta dubloonów nagrody za niego.";
			link.l1 = "Dziękuję!";
			link.l1.go = "persian_7";
		break;
		
		case "persian_7":
			TakeNItems(pchar, "gold_dublon", 300);
			//Log_Info("You've received 300 doubloons");
			sTemp = CheckNIdentifyPersian();
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			pchar.questTemp.Persian = "two";
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
			dialog.text = "Proszę, przyjmij moje podziękowania i skromny, ale bardzo przydatny dar. Nie potrzebuję go, ale ty albo twój cieśla okrętowy uznacie go za niezwykle pomocny\nSpójrz, oto ten piękny pierścień! Teraz jest twój. Ale to nie jest zwykły pierścień, to zaklęty pierścień. Pomaga w tkactwie i naprawie statków. Wielu rzemieślników chciałoby go mieć, ale trzymałem go na specjalną okazję. Weź go, przyjacielu, mam nadzieję, że ulży twoim ciężarom!";
			link.l1 = "Z pewnością nosisz ze sobą wiele interesujących artefaktów. Dzięki, Fadey!";
			link.l1.go = "persian_8";
		break;
		
		case "persian_8":
			GiveItem2Character(pchar, "talisman7");
			//Log_Info("You've received the Scarab amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "Została tylko jedna szamszira z mojej zaginionej kolekcji do odnalezienia. Liczę na ciebie, "+pchar.name+", a także na twoim szczęściu. Jeśli go znajdziesz, nie wahaj się wrócić do mnie pośpiesznie.";
			link.l1 = "Zdecydowanie! Do zobaczenia wkrótce...";
			link.l1.go = "exit";
			if (CheckNCountPersian() > 0)
			{
				link.l2 = "Po co mam się spieszyć? Miecz jest przy mnie.";
				link.l2.go = "persian_9";
			}
		break;
		
		case "persian_9":
			dialog.text = "O, dzięki Bogu, że poprosiłem o pomoc właśnie ciebie, "+pchar.name+"Jesteś cudotwórcą, mój przyjacielu! Pokaż mi to... Ohooo! To, to ona. Moja ukochana! Krasavitsa! Gramercy, dobry człowieku, składam ci pokłon! Oto twoje pieniądze. Czterysta dublonów i ani kopiejki mniej! Nie będę skąpy.";
			link.l1 = "Dziękuję, Fadey. Z przyjemnością pomogłem.";
			link.l1.go = "persian_10";
		break;
		
		case "persian_10":
			TakeNItems(pchar, "gold_dublon", 400);
			//Log_Info("You've received 400 doubloons");
			sTemp = CheckNIdentifyPersian();
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddCharacterExpToSkill(pchar, "Fortune", 250);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, FRANCE, 3);
			Achievment_Set("ach_65");
			dialog.text = "Moja kolekcja szamszirów znów jest w komplecie! Nikt nie odważy się jej ponownie ukraść, zadbam o to! Mam dla ciebie bardzo specjalną nagrodę, dobry człowieku. Za dwa tygodnie handlarz przyniesie mi zestaw doskonałej zbroi szermierczej z Europy. Na zamówienie szlachcica, jest to dość unikalny element zbroi\nWięc, jeśli chcesz, możesz go kupić za jedynie siedemset złotych dublonów. Powiem szlachcicowi, że zginęła w transporcie.";
			link.l1 = "Co takiego dobrego jest w tej zbroi?";
			link.l1.go = "persian_11";
		break;
		
		case "persian_11":
			dialog.text = "Jest bardzo wygodna i wytrzymała, a jednocześnie działa równie dobrze jak żelazna zbroja. A do tego świetnie wygląda! Powinieneś wrócić za kilka tygodni i rzucić na nią okiem. Ale nie zwlekaj dłużej niż miesiąc, bo sprzedam ją pierwotnemu klientowi.";
			link.l1 = "Umowa stoi. Zawitam do twego domu za dwa tygodnie.";
			link.l1.go = "persian_12";
		break;
		
		case "persian_12":
			DialogExit();
			pchar.questTemp.Persian = "time";
			SetFunctionTimerCondition("Persian_CirassLamport", 0, 0, 14, false); // таймер
		break;
		
		case "persian_13":
			dialog.text = "Tak, już zostało dostarczone i czeka na ciebie. Czy przyniosłeś pieniądze?";
			if(PCharDublonsTotal() >= 700) // belamour legendary edition
			{
				link.l1 = "Tak. Oto siedemset doblonów.";
				link.l1.go = "persian_14";
			}
			else
			{
				link.l1 = "Cholera. Zapomniałem pieniędzy na statku. Przyniosę je za chwilę!";
				link.l1.go = "exit";
			}
		break;
		
		case "persian_14":
			RemoveDublonsFromPCharTotal(700); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "cirass8"); 
			//Log_Info("You've received wicker armour");
			AddCharacterExpToSkill(pchar, "Sneak", 300);
			dialog.text = "Tak, mój dobry człowieku! Proszę, weź to. Ta wiklinowa zbroja dobrze ci posłuży, zapewniam cię. Nie ma nic podobnego, nie w całych Karaibach!";
			link.l1 = "Tak, widzę to. Dziękuję! Nie mogę się doczekać, by to przymierzyć...";
			link.l1.go = "persian_15";
		break;
		
		case "persian_15":
			dialog.text = "Czemu musisz czekać? Śmiało. Zobaczmy, jak to pasuje.";
			link.l1 = "Zrobię to. Do zobaczenia później, Monsieur Fadey!";
			link.l1.go = "persian_16";
		break;
		
		case "persian_16":
			DialogExit();
			pchar.questTemp.Persian = "end";
			pchar.quest.Persian_CirassLamportOver.over = "yes"; //снять прерывание
		break;
		
		// торговля канатами
		case "ropes":
			if (CheckAttribute(pchar, "questTemp.UpgradeRopes"))
			{
				dialog.text = "Wejdź, mój drogi przyjacielu. Towar jest gotowy do zakupu. 2125 dubloonów za dwieście pięćdziesiąt sztuk.";
				if (PCharDublonsTotal() >= 2125)
				{
					link.l1 = "Wszystko jest tak, jak się umówiliśmy. Weź pieniądze.";
					link.l1.go = "ropes_1";
				}
				else
				{
					link.l1 = "Pozwól mi tylko przynieść monety z mojej kajuty.";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Wejdź, mój drogi przyjacielu. Towar jest gotowy do zakupu. Pięćset dublonów za pięćdziesiąt sztuk.";
				if (PCharDublonsTotal() >= 500)
				{
					link.l1 = "Wszystko zgodnie z umową. Weź pieniądze.";
					link.l1.go = "ropes_1";
				}
				else
				{
					link.l1 = "Pozwól mi tylko przynieść monety z mojej kajuty.";
					link.l1.go = "exit";
				}
			}
			if(sti(pchar.questTemp.FadeyRopes) >= 1 && !CheckAttribute(pchar, "questTemp.FadeyRopesBlock")) // увеличить объём поставок канатами
			{
				link.l4 = "Fadieju, czy moglibyśmy zwiększyć wolumen naszych transakcji? Jestem "+GetSexPhrase("gotowy","gotowa")+" kupować od ciebie pięć razy więcej towaru! Myślę, że przyniesie to korzyści nam obojgu. Co o tym sądzisz?";
				link.l4.go = "UpgradeRopes";
			}
			if(sti(pchar.questTemp.FadeyRopes) >= 1 && CheckAttribute(pchar, "questTemp.FadeyRopesPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок канатами, если в первый раз не принесли
			{
				link.l4 = "Fadieju, "+GetSexPhrase("przyniosłem","przyniosłam")+" pieniądze! Trzy tysiące złotych dublonów, jak się umawialiśmy.";
				link.l4.go = "UpgradeRopes_Agreed";
			}
		break;
		
		case "ropes_1":
			if (CheckAttribute(pchar, "questTemp.UpgradeRopes")) RemoveDublonsFromPCharTotal(2125);
			else RemoveDublonsFromPCharTotal(500); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "Miło było z tobą robić interesy, "+pchar.name+"Rozkażę moim ludziom przenieść liny na twój statek.";
			link.l1 = "Dziękuję!";
			link.l1.go = "ropes_2";
		break;
		
		case "ropes_2":
			dialog.text = "Jeśli nadal potrzebujesz więcej lin, wróć za miesiąc.";
			link.l1 = "Dobrze, Fadey. Do zobaczenia później!";
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.UpgradeRopes")) AddCharacterGoods(pchar, GOOD_ROPES, 250);
			else AddCharacterGoods(pchar, GOOD_ROPES, 50);
			DeleteAttribute(npchar, "quest.ropes");
			SetFunctionTimerCondition("Ropes_FadeyAttrReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 200);
			pchar.questTemp.FadeyRopes = sti(pchar.questTemp.FadeyRopes) + 1; // счётчик покупок
		break;
		
		// уменьшение НЗГ
		case "help":
			if (!CheckAttribute(npchar, "quest.relation_info"))
			{
				dialog.text = "Co mogę dla ciebie zrobić, mój drogi przyjacielu?";
				link.l1 = "Jesteś wpływowym człowiekiem, Fadey. Przyjaciel gubernatora, a jak mówią plotki, masz koneksje na dworze. Czy mógłbyś wstawić się za mną u władz, jeśli wpadnę w kłopoty z prawem?";
				link.l1.go = "relation_info";
				break;
			}
			dialog.text = "Jak mogę ci pomóc, przyjacielu?";
			if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l1 = "Mam problem z angielskimi władzami.";
				link.l1.go = "relation";
				pchar.GenQuest.FadeyNation = ENGLAND;
			}
			if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l2 = "Natknąłem się na kłopoty z francuskimi władzami.";
				link.l2.go = "relation";
				pchar.GenQuest.FadeyNation = FRANCE;
			}
			if (ChangeContrabandRelation(pchar, 0) <= 5)
            {
                Link.l5 = "Mam ogromny problem z przemytnikami.";
				Link.l5.go = "contraband";
            }
			link.l9 = "Przepraszam, myślę, że dam sobie radę sam.";
			link.l9.go = "exit";
		break;
		
		case "relation_info":
			dialog.text = "O ho ho, mój dobry człowieku, kto ci to powiedział? Wszyscy kłamią. Ale ponieważ jesteś bratem Michela i dobrym przyjacielem moim, mogę spróbować naprawić sprawy dla ciebie. Mogę wstawić się za tobą jedynie do władz angielskich i francuskich, chociaż moje kontakty mają swoje granice. Nie robię interesów z Hiszpanami i Holendrami\nOstrzegam cię również, że mój wpływ wystarcza tylko, aby uratować cię od drobnych wykroczeń. Mogę ich przekonać, by ponownie rozważyli swoje nastawienie do ciebie w przypadku niewielkich przewinień lub złagodzić nieco gniew. Więc idź, rozpoczynaj wojnę i licz na to, że wyciągnę cię z ognia!\nNa dodatek mogę złagodzić tylko jedno państwo na raz: Francję lub Anglię. Nie mogę rozdzierać się na pół, żeby robić dwie rzeczy naraz. Oczywiście, potrzebne będą także monety, aby dać łapówki. Nie wahaj się przyjść do mnie po pomoc, jeśli moje warunki są dla ciebie do przyjęcia.";
			link.l1 = "Dzięki, Fadey. Będę to mieć na uwadze.";
			link.l1.go = "exit";
			npchar.quest.relation_info = "true";
		break;
		
		case "relation":
			rate = abs(ChangeCharacterNationReputation(pchar, sti(pchar.GenQuest.FadeyNation), 0));
			if (rate <= 10)
			{
				dialog.text = "Oczywiście. Z pewnością słyszałem o twoich przygodach - czy też nieprzygodach. Mogę zająć się twoim małym problemem, niczego, czego odpowiednia ilość złota nie mogłaby załatwić. Trzysta złotych dublonów i wyciągnę cię z kotła.";
				if (PCharDublonsTotal() >= 300) // belamour legendary edition
				{
					link.l1 = "Świetnie! Oto złoto.";
					link.l1.go = "agree";
					iTotalTemp = 300;
				}
				link.l2 = "W takim razie to idealny moment, by zdobyć monety.";
				link.l2.go = "exit";
			}
			else
			{
				if (rate <= 20)
				{
					dialog.text = "Oczywiście. Z pewnością słyszałem o twoich przygodach - lub nieprzygodach. Mogę zająć się twoim małym problemem, nic, czego odpowiednia ilość złota nie mogłaby rozwiązać. Sześćset złotych dublonów i wyciągnę cię z opałów.";
					if (PCharDublonsTotal() >= 600) // belamour legendary edition
					{
						link.l1 = "Świetnie! Oto złoto.";
						link.l1.go = "agree";
						iTotalTemp = 600;
					}
					link.l2 = "W takim razie to właśnie odpowiedni moment, by pójść po monety.";
					link.l2.go = "exit";
				}
				else
				{
					dialog.text = "Tak, jesteś w nie lada tarapatach! Nie mogę całkowicie rozwiązać tej sytuacji. Mogę jednak złagodzić uderzenie pioruna, który zaraz spadnie na twoją grzeszną głowę. A później w każdej chwili możemy znowu przedstawić łapówkę, jeśli masz pieniądze i chęć. Siedemset złotych dublonów i mogę zacząć łagodzić twoje kłopoty.";
					if (PCharDublonsTotal() >= 700) // belamour legendary edition
					{
						link.l1 = "Zmęczony jestem tymi łowcami piratów, co mnie ścigają. Oto złoto.";
						link.l1.go = "agree";
						iTotalTemp = 700;
					}
					link.l2 = "W takim razie to właśnie odpowiedni czas, bym poszedł po monety.";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "agree":
			RemoveDublonsFromPCharTotal(iTotalTemp); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "Dobrze, daj mi około dziesięciu do piętnastu dni. W międzyczasie umówię się na spotkanie i załatwię to i owo. Wszystko będzie gotowe za około dwa tygodnie. ";
			link.l1 = "Dziękuję, Fadey! Będę czekał...";
			link.l1.go = "agree_1";
		break;
		
		case "agree_1":
			DialogExit();
            rate = 10 + rand(5);
            rate = GetIntByCondition(HasShipTrait(pchar, "trait23"), rate, rate / 2);
			SetFunctionTimerCondition("ChangeNationRelationFromFadeyComplete", 0, 0, rate, false);
			pchar.GenQuest.FadeyNation.Rate = abs(ChangeCharacterNationReputation(pchar, sti(pchar.GenQuest.FadeyNation), 0));
			npchar.quest.relation = "true";
		break;
		
		case "contraband":
			dialog.Text = "Po cóż, mój dobry człowieku, musiałeś ich rozwścieczyć? Przemytnicy nie są najgorszymi ludźmi w tej części świata i mogą przynieść ci niezły zysk. Dobrze, pomogę ci, wiem, jak ich udobruchać... To będzie siedemset dublonów, bez targowania.";
			if (PCharDublonsTotal() >= 700) // belamour legendary edition
			{
				Link.l1 = "Bardzo dobrze, Fadeju, zgadzam się. Weź swoje złoto.";
				Link.l1.go = "Contraband_Agreed";
			}
			Link.l2 = "Nie mam teraz przy sobie tyle złota. Wrócę później!";
			Link.l2.go = "exit";
		break;
		
		case "Contraband_Agreed":
			dialog.Text = "Dobrze, załagodzę tę kłótnię, nie martw się. Będą znowu z tobą robić interesy, jak za dawnych czasów.";
			Link.l1 = "Dziękuję!";
			Link.l1.go = "exit";
			ChangeContrabandRelation(pchar, GetIntByCondition(HasShipTrait(pchar, "trait23"), 25, 40));
			RemoveDublonsFromPCharTotal(700); // belamour legendary edition
			PlaySound("interface\important_item.wav");
		break;
		
		case "UpgradeRopes":
			dialog.text = "Ho-ho, widzę, że interes idzie wam nie bez sensu, a apetyt rośnie! Wszystko się zgadza, towar mamy dobry, a ceny nie są zbyt wysokie. Pamiętaj jednak, potrzebne są tu inwestycje! Taka sprawa wymaga poważnego podejścia, żeby wszystko wyszło jak należy.";
			link.l1 = "Czy "+GetSexPhrase("przyszedłbym","przyszłabym")+" do ciebie z taką propozycją, nie mając w zapasie paru setek dublonów?";
			link.l1.go = "UpgradeRopes_1";
		break;
		
		case "UpgradeRopes_1":
			dialog.text = "Wiem, monety w twojej skrzyni są, i nie jedna para, a na pewno z pięćdziesiąt by się zmieściło! Ale nasz interes nie jest zwyczajny - tu nie chodzi tylko o przewożenie towaru, ale o znalezienie drogi... powiedzmy, tajnej. Dla takiej skali trzeba będzie nie tylko płacić, ale zainwestować ciężko, żeby z zyskiem było! I żeby potem twoje pieniądze w próżną ścieżkę nie poszły. Jeśli jesteś gotów/gotowa (пол игрока) oddać trzy tysiące złotych dublonów, to weź moje słowo, że z tobą, jak z dobrym przyjacielem, wszystko będzie zrobione, i ceną nie skrzywdzimy.";
			if (PCharDublonsTotal() >= 3000)
			{
				Link.l1 = "Trzy tysiące dublonów! Cóż, przyznaję, tak hojną ofertę rzadko słyszy nawet prosperujący negocjant, nawet w najbardziej fantastycznych historiach! Niewielu jest gotowych tak hojnie zainwestować w takie przedsięwzięcie. Ale ja, na szczęście, należę właśnie do ich grona. Oto pańskie pieniądze, panie Fadieju.";
				Link.l1.go = "UpgradeRopes_Agreed";
			}
			Link.l2 = "Trzy tysiące złotych dublonów! Na taką sumę nie jestem "+GetSexPhrase("gotowy","gotowa")+", Fadieju. Niestety. Przyjdę do ciebie później.";
			Link.l2.go = "UpgradeRopes_Potom";
			link.l3 = "Trzy tysiące, mówisz? Cóż... Prawdę mówiąc, taka suma budzi szacunek dla twojego rozmachu. Ale muszę przyznać - ta sprawa nie jest dla mnie.";
			link.l3.go = "UpgradeRopes_2";
		break;
		
		case "UpgradeRopes_2":
			dialog.text = "Co za zwrot! Przychodzisz z propozycją, a tu zaraz się wycofujesz! Przyznaję, jest frustracja, ale przyjaźni nie porzucę. Niech będzie po staremu: nasza poprzednia umowa jest mocna - pięćdziesiąt zwojów po dziesięć dublonów za każdy, co miesiąc, 20-go dnia.";
			link.l1 = "Dobrze, że mnie rozumiesz, Fadieju. Chętnie bym "+GetSexPhrase("zmienił","zmieniła")+" zdanie, ale takich wydatków nie udźwignę. Niestety, w tej kwestii moje możliwości są ograniczone.";
			link.l1.go = "UpgradeRopes_3";
		break;
		
		case "UpgradeRopes_3":
			dialog.text = "Cóż, skoro tak zdecydowałeś, to nie ma co dyskutować. Ten zwrot nie odwoła naszej przyjaźni. Wpadaj, "+GetSexPhrase("miły człowieku","miła panno")+".";
			link.l1 = "Wszystkiego dobrego.";
			link.l1.go = "exit";
			pchar.questTemp.FadeyRopesBlock = true;
		break;
		
		case "UpgradeRopes_Potom":
			DialogExit();
			pchar.questTemp.FadeyRopesBlock = true;
			pchar.questTemp.FadeyRopesPotom = true;
		break;
		
		case "UpgradeRopes_Agreed":
			dialog.text = "A to rozsądnie! Nie jesteś z tych, co tylko gadają, ale i działać potrafią. Dla ludzi interesu znajdzie się i rabacik! Piętnaście procent na wszystkie przyszłe partie! Taka będzie nasza umowa: 250 zwojów konopnych lin będę dla ciebie trzymał w gotowości każdego miesiąca. Odebrać je będziesz mógł/mogła (пол игрока), jak dawniej, 20-go dnia, płacąc 2125 dublonów za wszystko, bez reszty.";
			link.l1 = "Doskonale, Fadieju! Z tobą niesamowicie łatwo prowadzi się interesy. Jestem "+GetSexPhrase("pewien","pewna")+", że czeka nas powodzenie. Do rychłego zobaczenia!";
			link.l1.go = "exit";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "2_1");
			pchar.questTemp.UpgradeRopes = true;
			pchar.questTemp.FadeyRopesBlock = true;
			DeleteAttribute(pchar, "questTemp.FadeyRopesPotom");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
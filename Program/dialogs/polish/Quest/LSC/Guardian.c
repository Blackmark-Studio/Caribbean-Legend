// диалог протекторов, солдат и мушкетеров кланов LSC
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Czego do diabła chcesz?";
			link.l1 = "Nie, to nic.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
//------------------------------------- фразы гардов нарвалов --------------------------------------------
		// пост нарвалов на проход на Сан-Габриэль
		case "Narval_warning":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("Chłopcy, ostrożnie, to ten wariat! Do broni!","Wrogi jest tutaj! Do broni!","Ach, ty bękarcie! Teraz nauczymy cię lekcji!");
				link.l1 = "Cholera!";
				link.l1.go = "check_parol_fight";
				break;
			}
			ref location = &Locations[FindLocation(pchar.location)];
			if (!CheckAttribute(location, "nrv_parolinfo"))
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
				{
					dialog.text = "Stój, kumplu. Terytoria Narwali przed tobą, wstęp dla obcych zabroniony. Możesz przejść tylko z zaproszeniem. Znasz hasło?";
					link.l1 = "Tak.";
					link.l1.go = "Narval_warning_yes";
					link.l2 = "Nie.";
					link.l2.go = "Narval_warning_no";
				}
				else // если друг нарвалам
				{
					dialog.text = "A-ah, "+GetFullName(pchar)+"! Witaj, przyjacielu, ostrzegano nas, że możesz tu swobodnie chodzić. Witaj!";
					link.l1 = "Dzięki, przyjacielu!";
					link.l1.go = "exit";
				}
				location.nrv_parolinfo = "true";
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
				{
					dialog.text = "Mam nadzieję, że nie zapomniałeś hasła...";
					link.l1 = "Nie martw się...";
					link.l1.go = "exit";
				}
				else // если друг нарвалам
				{
					dialog.text = TimeGreeting()+", "+pchar.name+"! Jak się masz?";
					link.l1 = "Dobrze, dzięki!";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "Narval_warning_repeat";
			DeleteAttribute(npchar, "protector.CheckAlways");
		break;
		
		case "Narval_warning_yes":
			dialog.text = "To idź i powiedz to twardzielowi tam. Nie próbuj go oszukać, nasi chłopcy z muszkietami wiedzą, co robić. Więc jeśli planujesz jakieś sztuczki - lepiej się odwróć i odejdź. Teraz. Ostrzegałem cię.";
			link.l1 = "Dobrze, przyjacielu. Zrozumiałem.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_warning_repeat";
		break;
		
		case "Narval_warning_no":
			dialog.text = "Więc nie masz tu nic do roboty, jeśli nie zamierzasz kończyć swego żywota, oczywiście. Albo tylko żartujesz, co? Żartujesz sobie ze mnie? Właściwie, to mnie nie obchodzi. Idź na dół, moim zadaniem jest ostrzegać, a nie zatrzymywać. Nie wrócisz, jeśli nie znasz hasła.";
			link.l1 = "Dobrze, kumplu. Zrozumiałem.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_warning_repeat";
		break;
		
		case "Narval_warning_repeat":
			if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				dialog.text = "Czego jeszcze potrzebujesz? Zejdź na „San Gabriel” albo zgiń!";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Przykro mi, "+pchar.name+", ale jestem na służbie. Nie zawracaj mi głowy, kumpel. Idź dalej!";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Narval_warning_repeat";
		break;
		
		case "Narval_parol":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("Pany, uważajcie, tam jest świr! Do broni!","Wróg jest tutaj! Do broni!","Ach, jesteś bękartem! Teraz damy ci nauczkę!");
				link.l1 = "Cholera!";
				link.l1.go = "check_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				dialog.text = "Przepraszam, "+pchar.name+", ale jestem na służbie. Nie zawracaj mi głowy, kolego. Idź dalej!";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Narval_parol";
				break;
			}
			dialog.text = "Stój, gdzie stoisz! Nie jesteś jednym z nas!";
			link.l1 = "Stoję, stoję.";	
			link.l1.go = "check_parol";
		break;
		
		case "check_parol":
			dialog.text = "Powiedz hasło, jasno i głośno.";
			sTotalTemp = sNrvParol;
			if (CheckAttribute(pchar, "questTemp.LSC.NParol_bye"))
			{
				link.l1 = StringFromKey("QuestsUtilite_" + (281 + rand(11)));
				link.l1.go = "check_parol_wrong";
				link.l2 = StringFromKey("QuestsUtilite_" + (293 + rand(11)));
				link.l2.go = "check_parol_wrong";
				link.l3 = StringFromKey("QuestsUtilite_" + (305 + rand(11)));
				link.l3.go = "check_parol_wrong";
				link.l4 = StringFromKey("QuestsUtilite_" + (317 + rand(11)));
				link.l4.go = "check_parol_wrong";
				
				switch (rand(3))
				{
					case 0:
						link.l1 = sTotalTemp;
						link.l1.go = "check_parol_1";
					break;

					case 1:
						link.l2 = sTotalTemp;
						link.l2.go = "check_parol_1";
					break;

					case 2:
						link.l3 = sTotalTemp;
						link.l3.go = "check_parol_1";
					break;

					case 3:
						link.l4 = sTotalTemp;
						link.l4.go = "check_parol_1";
					break;
				}
			}
			else
			{
				link.l1 = "Jaki znowu kod? Przepuść mnie, bo inaczej...";
				link.l1.go = "check_parol_wrong";
			}
		break;
		
		case "check_parol_1":
			dialog.text = "Dobrze, możesz przejść dalej.";
			link.l1 = "Dzięki, kumplu...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_parol_repeat";
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_NARVAL");
			pchar.questTemp.LSC.parol_nrv = "true";
		break;
		
		case "check_parol_wrong":
			dialog.text = "Hm... Chłopaki! Mamy towarzystwo!";
			link.l1 = "Kurwa!";
			link.l1.go = "check_parol_fight";
		break;
		
		case "check_parol_fight":
			DialogExit();
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_NARVAL");
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "Narval_parol_repeat":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("Chłopcy, ostrożnie, to wariat! Do broni!","Wróg jest tutaj! Do broni!","Ach, jesteś bękartem! Teraz damy ci nauczkę!");
				link.l1 = "Cholera!";
				link.l1.go = "check_parol_fight";
				break;
			}
			dialog.text = "Idź dalej! Nie stój tutaj!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_parol_repeat";
		break;
		
		// у резиденции
		case "Narval_residence":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("Pobratymcy, ostrożnie, tam jest psychol! Do broni!","Wroga tutaj! Do broni!","Ach, ty łajdaku! Teraz nauczymy cię lekcji!");
				link.l1 = "Cholera!";
				link.l1.go = "check_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // диалог от времени суток. лесник
			    {
					dialog.text = TimeGreeting()+", "+pchar.name+"! Drzwi są otwarte, jeśli chcesz zobaczyć szefa.";
					link.l1 = "Dobrze...";
					link.l1.go = "exit";
					NextDiag.TempNode = "Narval_residence";
					DeleteAttribute(npchar, "protector.CheckAlways");
				}
				else
				{
                    dialog.text = TimeGreeting()+", "+pchar.name+"Jeśli chcesz zobaczyć szefa, to on już śpi. Wróć rano.";
					link.l1 = "Dobrze...";
					link.l1.go = "exit";
					NextDiag.TempNode = "Narval_residence";
					DeleteAttribute(npchar, "protector.CheckAlways");	
                }					
				break;	
			}
			if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend") && CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "Przyjaciele czarnych nie mają tu czego szukać. Prosty rozkaz od szefa!";
				if (CheckAttribute(pchar, "questTemp.LSC.Donald_enter"))
				{
					link.l1 = "On będzie musiał mnie zobaczyć. Macie prawdziwe kłopoty, chłopaki. Jestem tu na oficjalne rozkazy admirała. Więc otwórzcie te przeklęte drzwi!";
					link.l1.go = "negotiations";
				}
				else
				{
				link.l1 = "Nie mogę powiedzieć, że też chcę go zobaczyć...";
				link.l1.go = "exit";
				}
				NextDiag.TempNode = "Narval_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // лесник . диалог от времени суток .
			{
			dialog.text = "Chcesz zobaczyć szefa? Hm, no cóż, ruszaj dalej.";
			link.l1 = "Dzięki za pozwolenie na...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
			}
			else
			{
            dialog.text = "Chcesz zobaczyć szefa? Dziś już wizyt nie będzie. Wróć rano.";
			link.l1 = "Dobrze...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
            }			
		break;
		
		case "Narval_soldier":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("Chłopcy, uważajcie, to ten psychol! Do broni!","Wróg jest tutaj! Do broni!","Ach, ty łajdaku! Teraz damy ci nauczkę!");
				link.l1 = "Cholera!";
				link.l1.go = "check_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				dialog.text = TimeGreeting()+", "+pchar.name+"! Jak się masz?";
				link.l1 = "Jestem w porządku, dziękuję...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Słuchaj, kumplu, nie jestem w nastroju do rozmów. Idź dalej...";
				link.l1 = "Dobrze.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Narval_soldier";
		break;
		
		case "negotiations":
			dialog.text = "„No, no... Spokojnie. Powinieneś od razu powiedzieć, że jesteś od admirała. Widzisz, różni ludzie się tu kręcą...”";
			link.l1 = "Czy w końcu pozwolisz mi przejść? Dzięki!";
			link.l1.go = "negotiations_1";
		break;
		
		case "negotiations_1":
			DialogExit();
			NextDiag.CurrentNode = "negotiations_2";
			LocatorReloadEnterDisable("LostShipsCity_town", "reload48", false); // открыть вход к Дональду Гринспи
		break;
		
		case "negotiations_2":
			dialog.text = "Idź dalej, masz pozwolenie na...";
			link.l1 = "Naprawdę? Nie mogę w to uwierzyć.";
			link.l1.go = "exit";
			NextDiag.TempNode = "negotiations_2";
		break;
		
//------------------------------------- фразы гардов ривадос --------------------------------------------
		// пост ривадос на проход на Фурию и Веласко
		case "Rivados_warning":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("Chłopaki, ostrożnie, tam jest agresywny psychol! Do broni!","Wróg jest tutaj! Do broni!","Ach, ty chory łajdaku! Teraz nauczymy cię porządku!");
				link.l1 = "Cholera!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			location = &Locations[FindLocation(pchar.location)];
			if (!CheckAttribute(location, "rvd_parolinfo"))
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
				{
					dialog.text = "Stój! Terytoria za mną należą do klanu Rivados, żadni obcy jak ty nie mogą przechodzić bez zaproszenia. Znasz hasło?";
					link.l1 = "Tak.";
					link.l1.go = "Rivados_warning_yes";
					link.l2 = "Nie.";
					link.l2.go = "Rivados_warning_no";
				}
				else // если друг ривадос
				{
					dialog.text = "Ach, "+GetFullName(pchar)+" ! Cieszę się, że cię widzę! Powiedziano nam, że możesz się tu swobodnie poruszać. Witaj!";
					link.l1 = "Dzięki, przyjacielu!";
					link.l1.go = "exit";
				}
				location.rvd_parolinfo = "true";
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
				{
					dialog.text = "Mam nadzieję, że nie zapomniałeś hasła...";
					link.l1 = "Nie martw się...";
					link.l1.go = "exit";
				}
				else // если друг ривадос
				{
					dialog.text = TimeGreeting()+", "+pchar.name+"! Jak się masz?";
					link.l1 = "Jestem w porządku, dzięki...";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "Rivados_warning_repeat";
			DeleteAttribute(npchar, "protector.CheckAlways");
		break;
		
		case "Rivados_warning_yes":
			dialog.text = "Możesz wtedy iść. Ten chłopak zażąda od ciebie hasła. Lepiej odejdź teraz, jeśli masz jakiekolwiek myśli o oszukaniu nas. Ostrzegłem cię.";
			link.l1 = "Dobrze, kumplu. Zrozumiałem.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_warning_repeat";
		break;
		
		case "Rivados_warning_no":
			dialog.text = "Ho-ho! Albo jesteś bardzo odważny, albo bardzo głupi, jeśli zamierzasz nas odwiedzić bez hasła. Czy może żartujesz? No cóż, idź dalej. Jestem tu, by ostrzec, nie zatrzymać. Uważaj, jeśli naprawdę nie znasz hasła!";
			link.l1 = "Dobrze, przyjacielu. Zrozumiałem.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_warning_repeat";
		break;
		
		case "Rivados_warning_repeat":
			if (!CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "Czego chcesz? Ruszaj dalej albo zmykaj!";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Przykro mi, "+pchar.name+", ale jestem na służbie. Eddie nie chce, żebym za dużo gadał.";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Rivados_warning_repeat";
			DeleteAttribute(npchar, "protector.CheckAlways");
		break;
		
		case "Rivados_parol":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("Chłopcy, ostrożnie, to ten agresywny szaleniec! Do broni!","Wróg jest tutaj! Do broni!","Ach, ty chorowity draniu! Teraz nauczymy cię rozumu!");
				link.l1 = "Cholera!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "Przykro mi, "+pchar.name+", ale jestem na służbie. Eddie nie chce, żebym za dużo gadał.";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_parol";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			dialog.text = "Stój, gdzie stoisz! Nie jesteś z Rivados!";
			link.l1 = "Chcę przejść.";	
			link.l1.go = "Rcheck_parol";
		break;
		
		case "Rcheck_parol":
			dialog.text = "W takim razie powiedz hasło głośno i wyraźnie.";
			sTotalTemp = sRvdParol;
			if (CheckAttribute(pchar, "questTemp.LSC.RParol_bye"))
			{
				link.l1 = StringFromKey("QuestsUtilite_" + (281 + rand(11)));
				link.l1.go = "Rcheck_parol_wrong";

				link.l2 = StringFromKey("QuestsUtilite_" + (293 + rand(11)));
				link.l2.go = "Rcheck_parol_wrong";

				link.l3 = StringFromKey("QuestsUtilite_" + (305 + rand(11)));
				link.l3.go = "Rcheck_parol_wrong";

				link.l4 = StringFromKey("QuestsUtilite_" + (317 + rand(11)));
				link.l4.go = "Rcheck_parol_wrong";
				
				switch (rand(3))
				{
					case 0:
						link.l1 = sTotalTemp;
						link.l1.go = "Rcheck_parol_1";
					break;

					case 1:
						link.l2 = sTotalTemp;
						link.l2.go = "Rcheck_parol_1";
					break;

					case 2:
						link.l3 = sTotalTemp;
						link.l3.go = "Rcheck_parol_1";
					break;

					case 3:
						link.l4 = sTotalTemp;
						link.l4.go = "Rcheck_parol_1";
					break;
				}
			}
			else
			{
				link.l1 = "Jaki znowu kod? Przepuść mnie, bo inaczej...";
				link.l1.go = "Rcheck_parol_wrong";
			}
		break;
		
		case "Rcheck_parol_1":
			dialog.text = "Zgadza się. Idź dalej.";
			link.l1 = "Dzięki, kumplu...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_parol_repeat";
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_RIVADOS");
			pchar.questTemp.LSC.parol_rvd = "true";
		break;
		
		case "Rcheck_parol_wrong":
			dialog.text = "Ha-ha! Mamy gościa! Pokażmy mu, kim jesteśmy!";
			link.l1 = "Pierdole!";
			link.l1.go = "Rcheck_parol_fight";
		break;
		
		case "Rcheck_parol_fight":
			DialogExit();
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_RIVADOS");
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "Rivados_parol_repeat":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("Chłopaki, uważajcie, oto agresywny szaleniec! Do broni!","Wrogowie są tutaj! Do broni!","Ach, ty chory draniu! Teraz nauczymy cię lekcji, lekcji!");
				link.l1 = "Cholera!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			dialog.text = "Nie stój tutaj, ruszaj dalej!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_parol_repeat";
		break;
		
		// у резиденции
		case "Rivados_residence":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("Chłopaki, ostrożnie, oto agresywny psychol! Do broni!","Wróg jest tutaj! Do broni!","Ach, jesteś chorym draniem! Teraz cię nauczymy!");
				link.l1 = "Cholera!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // лесник . диалог от времени суток .
				{
				dialog.text = TimeGreeting()+", "+pchar.name+"! Drzwi są otwarte, jeśli chcesz zobaczyć Eddiego i Chimiset. Ucieszą się, gdy cię zobaczą.";
				link.l1 = "Dobrze...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				}
				else // лесник - режим пропуска 
				{	
				dialog.text = TimeGreeting()+", "+pchar.name+"„! Jeśli chcesz zobaczyć Eddiego i Chimiseta, już odpoczywają. Wróć rano, ucieszą się z twojego widoku.”";
				link.l1 = "Dobrze...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				}
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend") && !CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "Nic do roboty dla przyjaciół Narwali w kabinie Eddiego! To jego bezpośredni rozkaz. Zmykaj!";
				link.l1 = "Nie chciałem go też widzieć...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			if (GetCharacterIndex("Chimiset") == -1) // Чимисет убит
			{
				dialog.text = "Nie masz tu nic do roboty w kajucie Eddie'ego! To jego bezpośredni rozkaz. Zmiataj!";
				link.l1 = "Nie chciałem go też widzieć...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // лесник . диалог от времени суток .
			{
			dialog.text = "Chcesz zobaczyć Eddiego? Dobrze, idź dalej, przypuszczam, że poświęci ci chwilę.";
			link.l1 = "Dzięki za pozwolenie...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
			}
			else // лесник режим пропуска.
			{
            dialog.text = "Chcesz zobaczyć Eddiego? Dziś już nie ma odwiedzin, wróć rano, a on znajdzie dla ciebie chwilę.";
			link.l1 = "Dobrze...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
            }			
		break;
		
		case "Rivados_soldier":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("Chłopcy, ostrożnie, oto agresywny psychol! Do broni!","Wróg jest tutaj! Do broni!","Ach, ty chory draniu! Teraz nauczymy cię rozumu!");
				link.l1 = "Cholera!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = TimeGreeting()+", "+pchar.name+"! Jak się masz?";
				link.l1 = "Jestem w porządku, dzięki...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Słuchaj, kumpel, nie mam nastroju do rozmowy. Idź dalej...";
				link.l1 = "Dobrze.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Rivados_soldier";
		break;
//------------------------------------- фразы гардов пиратов --------------------------------------------	
		// у склада
		case "Shark_storage":
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				dialog.text = LinkRandPhrase("Chłopcy, ostrożnie, to uzbrojony psycho! Do broni!","Wróg jest tutaj! Do broni!","Ach, ty łajdaku! Teraz skopiemy ci tyłek!");
				link.l1 = "Cholera!";
				link.l1.go = "shark_guard_fight";
				break;
			}
			dialog.text = "Stój! To jest teren zamknięty!";
			link.l1 = "Dobrze, jak mówisz...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Shark_storage";
		break;
		
		// у резиденции
		case "Shark_residence":
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				dialog.text = LinkRandPhrase("Chłopcy, uważajcie, tam jest uzbrojony świr! Do broni!","Wróg jest tutaj! Na broń!","Ach, jesteś bękartem! Teraz skopiemy ci tyłek!");
				link.l1 = "Cholera!";
				link.l1.go = "shark_guard_fight";
				break;
			}
			if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00)
			{
				if (pchar.questTemp.LSC == "begin" || pchar.questTemp.LSC == "mary") // тока прибыл
				{
					dialog.text = "Stój! Nie jesteś jednym z naszych... Czy Rekin na ciebie czeka, czy po prostu włóczysz się bez celu?";
					link.l1 = "Rekin? Steve Dodson?";
					link.l1.go = "first_talk_day";
				}
				else
				{
				dialog.text = "Admirał cię przyjmie. Idź dalej.";
				link.l1 = "Dzięki!";
				link.l1.go = "exit";
			}
			}
			else
			{
				if (pchar.questTemp.LSC == "begin" || pchar.questTemp.LSC == "mary") // тока прибыл
				{
					dialog.text = "Dokąd się tak śpieszysz? Jest noc, nie widzisz! Czy naprawdę myślisz, że admirał obudzi się, aby osobiście cię przywitać? Przyjdź rano.";
					link.l1 = "Jak mówisz. A gdzie mogę odpocząć?";
					link.l1.go = "first_talk_night";
				}
			else
			{
				dialog.text = "Jest późno, admirał teraz nie przyjmuje. Wróć jutro.";
				link.l1 = "Dobrze...";
				link.l1.go = "exit";
			}
			}
			NextDiag.TempNode = "Shark_residence";
		break;
		
		case "Shark_soldier":
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				dialog.text = LinkRandPhrase("Chłopaki, ostrożnie, to uzbrojony psychol! Do broni!","Wróg jest tutaj! Do broni!","Ach, ty draniu! Teraz skopiemy ci tyłek!");
				link.l1 = "Cholera!";
				link.l1.go = "shark_guard_fight";
				break;
			}
			dialog.text = "Admirał nie będzie zadowolony, jeśli zobaczy, że rozmawiam. Idź dalej.";
			link.l1 = "Dobrze...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Shark_soldier";
		break;
		
		case "first_talk_night":
			dialog.text = NPCStringReactionRepeat("Czyś ty pijany? Zawróć i przejdź przez most, mijaj dwa statki, a potem znajdziesz kolejny most, który zaprowadzi cię do tawerny. Prześpij się tam.","Czy próbujesz mnie wkurzyć? Właśnie powiedziałem ci, co masz robić. Zmykaj!","Idź spać, pijany gębo...","Precz!!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Dzięki, panie. Mogłeś być bardziej uprzejmy, tak naprawdę...","Przepraszam, zapomniałem...","Nie jestem pijany!","Co?!",npchar,Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;
		
		case "first_talk_day":
			dialog.text = "Nie rób takich dużych oczu, chłopcze. Wszyscy wiedzą, że Steve Rekin jest naszym admirałem. Masz do niego jakieś sprawy?";
			link.l1 = "Tak, do diabła! Mam dla niego sprawę i jest to pilne.";
			link.l1.go = "first_talk_day_1";
		break;
		
		case "first_talk_day_1":
			dialog.text = "A jaki interes?";
			link.l1 = "Opowiem o tym tylko Rekinowi na osobności. Pracuję dla Jana Svensona, znasz go?";
			link.l1.go = "first_talk_day_2";
		break;
		
		case "first_talk_day_2":
			dialog.text = "Leśny Diabeł? Ha! Połowa Kontynentu zna tego człowieka. Słuchaj, chłopcze, nie bądź uparty. Albo wyjaśnij się, albo zmykaj, zanim się wkurzę. Rekin powiedział, żeby oszczędzać go od bezużytecznych ludzi i ja tylko wykonuję jego rozkaz.";
			link.l1 = "Dobrze. Spójrz na ten list, został napisany przez Leśnego Diabła do Rekina.";
			link.l1.go = "first_talk_day_3";
		break;
		
		case "first_talk_day_3":
			PlaySound("interface\important_item.wav");
			dialog.text = "(patrząc)... Dobrze. Przypuszczam, że Steve uzna to za interesujące. Ruszaj dalej.";
			link.l1 = "O, naprawdę? Oddaj list, jeśli to nie będzie dla ciebie zbyt trudne, proszę.";
			if (pchar.questTemp.LSC == "mary") link.l1.go = "first_talk_day_5";
			else link.l1.go = "first_talk_day_4";
		break;
		
		case "first_talk_day_4":
			PlaySound("interface\important_item.wav");
			npchar.dialog.currentnode = "First time";
			DialogExit();
			LSC_OpenSanAvgustinDoors(); // открываем Сан-Августин
			LocatorReloadEnterDisable("LostShipsCity_town", "reload2", true); //закрываем кладовку со стороны моря
			pchar.quest.LSC_entry_pantry.over = "yes"; //снять прерывание на арест
			pchar.quest.LSC_findMary.over = "yes"; //снять прерывание на Мэри
			pchar.questTemp.LSC = "entrance"; //меняем флаг
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "entrance";
			// закрываем вход к Мэри
			LocatorReloadEnterDisable("LostShipsCity_town", "reload60", true);
			LocatorReloadEnterDisable("LostShipsCity_town", "reload61", true);
		break;
		
		case "first_talk_day_5":
			PlaySound("interface\important_item.wav");
			npchar.dialog.currentnode = "First time";
			DialogExit();
			LSC_OpenSanAvgustinDoors(); // открываем Сан-Августин
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "entrance";
		break;
		
		case "shark_guard_fight":
			DialogExit();
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_SHARK");
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

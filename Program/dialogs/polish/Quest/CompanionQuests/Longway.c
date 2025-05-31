void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
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
		
		// Квест "Путеводная звезда"
		// Этап 0, ПРОЛОГ
		case "PZ_Alonso_1":
			dialog.text = "Przepraszam za najście do twojej kajuty, Wielmożny Panie Kapitanie, ale to jest bardzo ważne.";
			link.l1 = "Mam nadzieję, że tak, Alonso. Jeśli każdy z was zacznie tu wchodzić, jakby to było jego własne miejsce, będziemy mieli problem. Więc, co się dzieje?";
			link.l1.go = "PZ_Alonso_2";
		break;
		
		case "PZ_Alonso_2":
			dialog.text = "Stwierdziliśmy, że twoja szafka została przetrząśnięta.";
			link.l1 = "Co?! Poczekaj... Jak się tego domyśliłeś? I co wy wszyscy robiliście w mojej kajucie?";
			link.l1.go = "PZ_Alonso_3";
		break;
		
		case "PZ_Alonso_3":
			dialog.text = "„Sprzątamy twoje kajuty od czasu do czasu, gdy jesteś na zewnątrz – czy to w mieście, czy odpoczywasz na koje. Nigdy tego nie zauważyłeś? A może po prostu zapomniałeś?”";
			link.l1 = "„Och, to prawda. Cóż, możesz już iść.”";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_Tichingitu_1":
			dialog.text = "Kapitánie Charles, spójrz! Ktoś przetrząsał twoją dużą szufladę.";
			link.l1 = "Co? Kiedy to zauważyłeś? Wiesz, kto to był?";
			link.l1.go = "PZ_Tichingitu_2";
		break;
		
		case "PZ_Tichingitu_2":
			dialog.text = "Nie tak dawno, gdy przychodziłem, by Cię zobaczyć. Duchy milczą na temat, kim to może być.";
			link.l1 = "To miły gest, Tichingitu. A teraz, jeśli pozwolisz, muszę sprawdzić, czy niczego nie brakuje.";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_Duran_1":
			dialog.text = "„Hej, Kapitanie, na co patrzysz? Ktoś grzebał w twoich rzeczach. Nawet ja to zauważyłam.”";
			link.l1 = "To nie ty? W końcu nie płacę ci tak hojnie jak Francois.";
			link.l1.go = "PZ_Duran_2";
		break;
		
		case "PZ_Duran_2":
			dialog.text = "Heh, gdybym to ja był złodziejem, nie powiedziałbym ci, prawda? Wziąłbym kosztowności i posprzątał po sobie. Ten bałagan to nie mój styl.";
			link.l1 = "Nie lubię tego przyznawać, ale masz rację. Cóż, Claude, zostaw swoje złośliwości na później. Muszę sprawdzić, co złodziej zabrał.";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_Folke_1":
			dialog.text = "Wielmożny Panie Kapitanie, zauważyłem dziś, że ktoś przeszukał twoją skrzynię. Nie zauważyłeś?";
			link.l1 = "Co? Nie sprawdzam ciągle szafki, Folke, i nawet nie przebywam cały czas w kabinie. Powiedz mi szczerze - to byłeś ty? Znowu namieszałeś i wziąłeś więcej pożyczek, gdy ostatnio byliśmy na lądzie?";
			link.l1.go = "PZ_Folke_2";
		break;
		
		case "PZ_Folke_2":
			dialog.text = "Absolutnie nie, Kapitanie. Nie mam niczego, co należy do Ciebie, ani w kieszeniach, ani w mojej szafce. I nigdy nie będę miał.";
			link.l1 = "Mam nadzieję, że nie. Możesz iść - sprawdzę, czego brakuje.";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_OsmatrivaemKautu":
			DialogExit();
			
			if (npchar.id == "Tichingitu")
			{
				LAi_SetOfficerType(npchar);
				npchar.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
				npchar.Dialog.CurrentNode = "Tichingitu_officer";
			}
			if (npchar.id == "FMQT_mercen" || npchar.id == "Folke")
			{
				LAi_SetOfficerType(npchar);
				npchar.Dialog.Filename = "Enc_Officer_dialog.c";
				npchar.Dialog.CurrentNode = "hired";
			}
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "rld", "loc2", "PZ_OsmatrivaemSunduk", -1);
		break;
		
		case "PZ_LigaInJungle_1":
			dialog.text = "Charles de Maure, prawda?";
			link.l1 = "Po wyrazie twojej twarzy powiedziałbym, że już znasz odpowiedź. Więc, czego chcesz?";
			link.l1.go = "PZ_LigaInJungle_2";
		break;
		
		case "PZ_LigaInJungle_2":
			dialog.text = "Twoja głowa.";
			link.l1 = "Fascynujące! Muszę przyznać, że podoba mi się, jak zaczyna się ta rozmowa. Ale zanim pójdziemy dalej, czy mógłbyś przynajmniej powiedzieć mi, kogo skrzywdziłem? Może możemy negocjować.";
			link.l1.go = "PZ_LigaInJungle_3";
		break;
		
		case "PZ_LigaInJungle_3":
			dialog.text = "Nie jesteśmy amatorami, Monsieur de Maure. Nawet gdybyśmy ci powiedzieli, to by ci nie pomogło - nasz zleceniodawca już opuścił Archipelag. Nie możesz mu zaszkodzić ani przeprosić. Zostaliśmy opłaceni, a teraz czas wywiązać się z naszej części umowy.";
			link.l1 = "Jeśli już ci zapłacono, po co przelewać więcej krwi?";
			link.l1.go = "PZ_LigaInJungle_4";
		break;
		
		case "PZ_LigaInJungle_4":
			dialog.text = "Nie jesteśmy amatorami. Cenimy sobie naszą reputację.";
			link.l1 = "Obawiam się, że tym razem nie sprostasz temu.";
			link.l1.go = "PZ_LigaInJungle_5";
		break;
		
		case "PZ_LigaInJungle_5":
			dialog.text = "Zobaczymy, jak to będzie. Przeszukaj jego trupa, kiedy skończymy! Spal wszystko, co znajdziesz!";
			link.l1 = "Spalić co?..";
			link.l1.go = "PZ_LigaInJungle_6";
		break;
		
		case "PZ_LigaInJungle_6":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("LigaInJungle_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_LigaInJunglePosleBitvy");
			
			if (CharacterIsHere("Longway"))
			{
				sld = characterFromId("Longway");
				LAi_SetCheckMinHP(sld, 1, true, "");
			}
		break;
		
		case "PZ_Longway_1":
			dialog.text = "Co powiedział zamaskowany człowiek... Czy to możliwe...?";
			link.l1 = "Co się dzieje, Longway? To nie pierwszy raz, kiedy łowcy nagród mnie ścigają, ale wydajesz się niezwykle zaniepokojony.";
			link.l1.go = "PZ_Longway_2";
		break;
		
		case "PZ_Longway_2":
			dialog.text = "Longway myśli, że wie, kto wysłał tych ludzi za tobą, Wielmożny Panie Kapitanie.";
			link.l1 = "Coś, o czym powinienem wiedzieć?";
			link.l1.go = "PZ_Longway_3";
		break;
		
		case "PZ_Longway_3":
			dialog.text = "To sposób Lorda Rodenburga - eliminować tych, którzy mu pomogli, ale wiedzą zbyt wiele.";
			link.l1 = "„Naprawdę... Ten zamaskowany człowiek powiedział, że jego pracodawca niedawno opuścił Archipelag. Dokładnie to planował Lucas! Myślisz, że powinniśmy spodziewać się kolejnych ataków?”";
			link.l1.go = "PZ_Longway_4";
		break;
		
		case "PZ_Longway_4":
			dialog.text = "Mądrze jest być przygotowanym na wszystko, Wielmożny Panie Kapitanie.";
			link.l1 = "Mądre słowa. Będziemy. Ale czego szukał Lucas? Co myślał, że mam? Jakieś pomysły, Longway?";
			link.l1.go = "PZ_Longway_5";
		break;
		
		case "PZ_Longway_5":
			dialog.text = "Mm-mm, nie, Longway nie ma pojęcia, czym to może być.";
			link.l1 = "Szkoda. Ale dobrze, wyjdźmy stąd.";
			link.l1.go = "PZ_Longway_6";
		break;
		
		case "PZ_Longway_6":
			DialogExit();
			
			Return_LongwayOfficer();
			
			chrDisableReloadToLocation = false;
			pchar.questTemp.PZ_RazgovorGerrits = true;
			pchar.questTemp.PZ_PodozrenieLucas = true;
		break;
		
		// Этап 1, ВЕРНЫЙ КЛЯТВЕ
		case "PZ_Longway_11":
			dialog.text = "Wielmożny Panie Kapitanie, Longway pragnie z tobą porozmawiać. To bardzo ważne.";
			if (CheckAttribute(pchar, "questTemp.PZ_PodozrenieLucas"))
			{
				link.l1 = "Co jest, Longway? Martwisz się sposobem, w jaki Lucas się pożegnał, czy odkryłeś coś nowego?";
				link.l1.go = "PZ_Longway_12";
				AddCharacterExpToSkill(pchar, "Sneak", 100);
			}
			else
			{
				link.l1 = "Jasne! Co masz na myśli?";
				link.l1.go = "PZ_Longway_13";
			}
		break;
		
		case "PZ_Longway_12":
			dialog.text = "Niestety, nie.";
			link.l1 = "Więc o co chodzi, Longway?";
			link.l1.go = "PZ_Longway_13";
		break;
		
		case "PZ_Longway_13":
			dialog.text = "Longway nie może powiedzieć. Ale... chciałby prosić o pozwolenie na odejście.";
			link.l1 = "Zostawić? Na zawsze? Dlaczego, Longway? Jako twój kapitan, mam prawo znać powód.";
			link.l1.go = "PZ_Longway_14";
		break;
		
		case "PZ_Longway_14":
			dialog.text = "To prawda, Wielmożny Panie Kapitanie. Ale Longway nie jest ani robotnikiem, ani sługą. Przyszedł pomóc z własnej woli i może odejść w ten sam sposób. To nie będzie na zawsze - jest ważna sprawa do załatwienia. Longway ma nadzieję wrócić, gdy to zostanie zrobione.";
			link.l1 = "Co to za sprawa? Powiedz mi - jeśli nie jako swojemu kapitanowi, to jako komuś, kto przeszedł z tobą wiele.";
			link.l1.go = "PZ_Longway_15";
		break;
		
		case "PZ_Longway_15":
			dialog.text = "Wszystko, co Longway może powiedzieć, to to, że złożył przysięgę - dawno temu. Nadszedł czas, aby ją wypełnić. W przeciwnym razie... życie Longwaya nie ma sensu.";
			link.l1 = "Masz rację, Longway - nie jesteś więźniem, a ja nie jestem strażnikiem. Jesteś wolny. Niech cię Bóg prowadzi.";
			link.l1.go = "PZ_Longway_Otpustit_1";
			link.l2 = "Możesz iść, ale przynajmniej powiedz mi, dokąd zmierzasz. Mogę pomóc, nie zadając zbyt wielu pytań.";
			link.l2.go = "PZ_Longway_Pomoch_1";
			link.l3 = "„Mam również ważne zadanie – uratować mojego brata. Do tego potrzebuję każdego człowieka, w tym ciebie, Longway. Nie damy rady bez ciebie.”";
			link.l3.go = "PZ_Longway_NeOtpuskaem_1";
		break;
		
		case "PZ_Longway_NeOtpuskaem_1":
			dialog.text = "Nie próbuj grać na moim współczuciu ani poczuciu obowiązku. Doskonale rozumiem. Czy kiedykolwiek złożyłeś przysięgę, Wielmożny Panie Kapitanie?";
			link.l1 = "„Oczywiście, że tak. Więc opowiedz mi wszystko, jak jest, a moi ludzie i ja z pewnością ci pomożemy.”";
			link.l1.go = "PZ_Longway_NeOtpuskaem_2";
		break;
		
		case "PZ_Longway_NeOtpuskaem_2":
			dialog.text = "Longway nie może. Po prostu... nie może. To wielka tajemnica, i nie moja, by ją dzielić.";
			link.l1 = "To szkoda. Myślałem, że jest między nami zaufanie. Nie opuszczasz statku - mam teraz wszystkich oficerów po swojej stronie.";
			link.l1.go = "PZ_Longway_NeOtpuskaem_3";
			link.l2 = "Masz rację, Longway - nie jesteś więźniem, a ja nie jestem strażnikiem. Jesteś wolny. Niech cię Bóg prowadzi.";
			link.l2.go = "PZ_Longway_Otpustit_1";
		break;
		
		case "PZ_Longway_NeOtpuskaem_3":
			dialog.text = "Nie możesz tego zrobić!";
			link.l1 = "Niestety, mogę, Longway. Teraz wracaj do swoich obowiązków.";
			link.l1.go = "PZ_Longway_NeOtpuskaem_4";
		break;
		
		case "PZ_Longway_NeOtpuskaem_4":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			npchar.Dialog.CurrentNode = "Longway_officer";
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			PChar.quest.PZ_LongwayUhoditOtNasNavsegda.win_condition.l1 = "MapEnter";
			PChar.quest.PZ_LongwayUhoditOtNasNavsegda.win_condition = "PZ_LongwayUhoditOtNasNavsegda";
		break;
		
		case "PZ_Longway_Otpustit_1":
			dialog.text = "Nie sądziłam, że tak łatwo mnie puścisz. Dziękuję, Wielmożny Panie Kapitanie.";
			link.l1 = "Ach, to nic. Ale powiedz mi - gdzie mogę cię znaleźć, gdy skończysz swoje sprawy?";
			link.l1.go = "PZ_Longway_GdeIskat_1";
		break;
		
		case "PZ_Longway_Pomoch_1":
			dialog.text = "Longway naprawdę nie może powiedzieć, bez względu na to, jak bardzo by chciał. Ale docenia chęć pomocy Wielmożnego Pana Kapitana.";
			link.l1 = "Niech tak będzie. Gdzie mam cię szukać, gdy dotrzymasz przysięgi?";
			link.l1.go = "PZ_Longway_GdeIskat_1";
			pchar.questTemp.PZ_LongwayGood = true;
		break;
		
		case "PZ_Longway_GdeIskat_1":
			dialog.text = "Spodziewam się zakończyć moje sprawy w ciągu miesiąca. Po tym, Longway będzie czekał na ciebie przez kolejny tydzień w tawernie w Basse-Terre.";
			link.l1 = "„Cóż, cokolwiek powiesz, przyjacielu. To nie pożegnanie. Do zobaczenia w Basse-Terre.”";
			link.l1.go = "PZ_Longway_GdeIskat_2";
		break;
		
		case "PZ_Longway_GdeIskat_2":
			DialogExit();
			
			RemovePassenger(pchar, npchar);
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			LAi_SetImmortal(npchar, true);
			npchar.location = "None";
			
			SetQuestHeader("PZ");
			AddQuestRecord("PZ", "1");
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			SetTimerCondition("PZ_IshemLongway", 0, 0, 30, false);	// ВЕРНУТЬ 30 дней
		break;
		
		case "PZ_SharliePlennik_BadFinal_1":
			dialog.text = "„No, witaj, Kapitanie.”";
			link.l1 = "Nie podoba mi się twój uśmieszek, panie.";
			link.l1.go = "PZ_SharliePlennik_BadFinal_2";
		break;
		
		case "PZ_SharliePlennik_BadFinal_2":
			dialog.text = "Jestem zdruzgotany. Przyszedłem powiedzieć ci, że jesteś w końcu wolny. Ale jeśli chcesz zostać dłużej w tej luksusowej kajucie, to proszę bardzo.";
			link.l1 = "Nie, wcale nie. Więc, znaleziono Longwaya? Gdzie on jest? W jednej z cel?";
			link.l1.go = "PZ_SharliePlennik_BadFinal_3";
		break;
		
		case "PZ_SharliePlennik_BadFinal_3":
			dialog.text = "W innym świecie, bardziej jak ten - nie rozmawiałby z nikim z nas i ruszył prosto do bitwy.";
			link.l1 = "Do diabła! Mogłeś go po prostu pojmać.";
			link.l1.go = "PZ_SharliePlennik_BadFinal_4";
		break;
		
		case "PZ_SharliePlennik_BadFinal_4":
			dialog.text = "Niektórzy ludzie są znacznie łatwiejsi do zabicia niż pojmania, czyż nie wiesz? Powinieneś być wdzięczny, że nie mamy do Ciebie żadnych pretensji - Twój Chińczyk spowodował kolejną masakrę, i potrzebowaliśmy kilku dodatkowych jednostek ze strzelcami, aby sobie z nim poradzić.";
			link.l1 = "Tak, rzeczywiście. Dziękuję za to.";
			link.l1.go = "PZ_SharliePlennik_BadFinal_5";
		break;
		
		case "PZ_SharliePlennik_BadFinal_5":
			dialog.text = "Przy okazji, ponieważ był twoim przyjacielem, znaleźliśmy przy nim jakieś papiery. Nie zrozumieliśmy, czym są - ty pewnie lepiej wiesz. Na częściach niepokrytych krwią było jakieś bełkotliwe pismo.";
			link.l1 = "To jest... Cholera. Dziękuję za ich zwrócenie. Do widzenia, oficerze.";
			link.l1.go = "PZ_SharliePlennik_BadFinal_6";
		break;
		
		case "PZ_SharliePlennik_BadFinal_6":
			DialogExit();
			
			LAi_ActorGoToLocator(npchar, "goto", "goto22", "", -1);
			DoQuestCheckDelay("PZ_SharliePlennik_BadFinal_2", 3.0);
		break;
		
		case "PZ_BasTerStop":
			dialog.text = "Chodź z nami, Komendant chce z tobą porozmawiać.";
			link.l1 = "Domyślam się, że to ma związek z moimi poszukiwaniami Chińczyka?";
			link.l1.go = "PZ_BasTerStop_2";
		break;
		
		case "PZ_BasTerStop_2":
			dialog.text = "Zobaczysz sam, monsieur.";
			link.l1 = "Czy jestem o coś oskarżony?";
			link.l1.go = "PZ_BasTerStop_3";
		break;
		
		case "PZ_BasTerStop_3":
			dialog.text = "„Wcale nie. Nikt nie próbuje cię aresztować ani zatrzymać. Na razie. Kiedy powiedziałem, że Komendant chce z tobą rozmawiać, miałem na myśli dokładnie to.”";
			link.l1 = "„Och, cóż...”";
			link.l1.go = "PZ_BasTerStop_4";
		break;
		
		case "PZ_BasTerStop_4":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("BasTer_town")], false);
			DoQuestReloadToLocation("BasTer_prison", "goto", "goto17", "PZ_BasTer_TurmaPriveli");
		break;
		
		case "PZ_BasTer_OtryadPeshera_1":
			dialog.text = "Masz jakieś pomysły? Ten żółtoskóry człowiek jest śmiertelnie niebezpieczny. Nie jesteśmy pierwszym oddziałem, który tu wysłano. Rozkazy to rozkazy, ale nie chcę głupio zginąć, wchodząc bez solidnego planu.";
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				link.l1 = "„On tam jest zupełnie sam, a ja jestem z wami. Ja się nim zajmę - wy skoncentrujcie się na osłanianiu mnie. Damy radę.”";
				link.l1.go = "PZ_BasTer_OtryadPeshera_2";
				if (pchar.location.from_sea != "BasTer_Town")
				{
					link.l2 = "Mam jednego. Wszyscy tu zginiecie.";
					link.l2.go = "PZ_BasTer_OtryadPeshera_Kill_1";
				}
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				link.l1 = "Nie martw się, tylko zamierzamy z nim porozmawiać.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_2";
				if (pchar.location.from_sea != "BasTer_Town")
				{
					link.l2 = "Przykro mi, ale wszyscy dzisiaj zginiecie. I nie z rąk Chińczyka.";
					link.l2.go = "PZ_BasTer_OtryadPeshera_Kill_1";
				}
			}
		break;
		
		case "PZ_BasTer_OtryadPeshera_Kill_1":
			pchar.questTemp.PZ_Podelnik = true;
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "Więc nie jesteś łowcą nagród... Ale nawet jeśli nim jesteś, to jesteś przyjacielem tego przeklętego Chińczyka!";
				link.l1 = "To prawda. I tak musiałbym się ciebie pozbyć - nie ma sensu odwlekać nieuniknionego.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_Kill_2";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "Co masz na myśli?! Obiecałeś pomóc!";
				link.l1 = "Myślę, że i tak nie dałbyś nam spokojnej drogi wyjścia. To nic osobistego.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_Kill_2";
			}
		break;
		
		case "PZ_BasTer_OtryadPeshera_Kill_2":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			chrDisableReloadToLocation = true;
			
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			sld = CharacterFromID("PZ_BasTer_OtryadPesheraOff");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_BasTer_OtryadPeshera_Kill_3");
		break;
		
		case "PZ_BasTer_OtryadPeshera_2":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "Chciałabym w to uwierzyć.";
				link.l1 = "Spotkałem się już z gorszymi. Jeden Chińczyk nas nie pokona. Naprzód, chłopcy!";
				link.l1.go = "PZ_BasTer_OtryadPeshera_3";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "A co, jeśli rozmowa nie pójdzie zgodnie z planem?";
				link.l1 = "Nie chciałbym tego, ale wtedy będę musiał się bronić. Chodźmy.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_3";
			}
		break;
		
		case "PZ_BasTer_OtryadPeshera_3":
			DialogExit();
			
			DoQuestReloadToLocation("Guadeloupe_CaveEntrance", "reload", "reload2", "PZ_IshemLongway_OtryadUPeshery");
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway":
			dialog.text = "Wielmożny Panie Kapitanie?! Longway nie może uwierzyć, że jesteś z nimi!";
			link.l1 = "Nie, Longway, jestem tu tylko, by porozmawiać! To nie to, co myślisz!";
			link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_2";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_2":
			dialog.text = "Więc przyszedłbyś sam. Próbujesz uśpić moją czujność, żeby zaatakować mnie z pomocą tych żołnierzy!";
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayGood"))
			{
				link.l1 = "Jeśli bym mógł, to bym to zrobił. Tylko dzięki mnie jeszcze cię nie zaatakowali. Uspokój się i porozmawiajmy, tak, co nie?";
				link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_3";
			}
			else
			{
				link.l1 = "Przestań pieprzyć! Gdybym chciał, już bym cię zabił. Złóż broń, a porozmawiamy. To rozkaz od twojego kapitana.";
				link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_Bad_1";
			}
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_3":
			dialog.text = "Tak. Longway ufa tobie, Wielmożny Panie Kapitanie.";
			link.l1 = "„Tam, to lepiej. Teraz powiedz mi...”";
			link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_4";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_4":
			StartInstantDialog("PZ_BasTer_OtryadPesheraOff", "PZ_BasTer_SOtryadom_DialogLongway_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_5":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "Monsieur, co się dzieje? Co to za... wzruszające spotkanie? Miałeś nam pomóc wyeliminować tego chińskiego dzikusa, prawda?";
				link.l1 = "Tak. Zabieram go ze sobą, a to całe zabijanie się skończy. Powiesz komendantowi, że zabiliśmy go razem. Umowa?";
				link.l1.go = "PZ_BasTer_SOtryadomOhotnik_1";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "Dobra robota, Kapitanie! Złożył broń. Dobrze mieć cię z nami. Teraz zabierzmy go do komendanta.";
				link.l1 = "Po co miałbym to robić? Zapłaciłem grzywnę w złocie za czyny Longwaya - i to hojną. Twoi koledzy oficerowie byli świadkami - potwierdzą to. Komendant upoważnił mnie do zabrania mojego człowieka na statek.";
				link.l1.go = "PZ_BasTer_SOtryadomDrug_1";
			}
		break;
		
		case "PZ_BasTer_SOtryadomDrug_1":
			dialog.text = "Komendant może mieć dość tego krwawego złota, ale nie ja. Niektórzy z ludzi, których zabił w tej krwawej jaskini, byli moimi przyjaciółmi. Poza tym, wątpię, żeby go obchodziło, jeśli zabijemy tego Chińczyka tak czy inaczej.";
			link.l1 = "Na pewno chcesz się dowiedzieć? A o twoich przyjaciołach, którzy zginęli... słyszałeś kiedyś o tej zuchwałej bandzie zbirów? To musieli być oni.";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_2";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_2":
			StartInstantDialog("Longway", "PZ_BasTer_SOtryadomDrug_3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_BasTer_SOtryadomDrug_3":
			dialog.text = "";
			link.l1 = "Longway, nie zabiłeś tylu żołnierzy, ile twierdzą, prawda?";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_4";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_4":
			dialog.text = "„Zgadza się, Wielmożny Panie Kapitanie. Longway widział tę bandę. Ukryli się głębiej w jaskini, żeby go nie zauważyli. I Longway słyszał odgłosy rozmów, przekleństw i walki między bandytami a żołnierzami.”";
			link.l1 = "";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_5";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_5":
			StartInstantDialog("PZ_BasTer_OtryadPesheraOff", "PZ_BasTer_SOtryadomDrug_6", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_BasTer_SOtryadomDrug_6":
			dialog.text = "";
			link.l1 = "Widzicie? Wszystko się zgadza. Longway może mieć temperament, ale jest uczciwym człowiekiem. Odchodzimy. Jeśli nas dotkniecie, splamicie swój mundur. Do widzenia, panowie.";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_7";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_7":
			DialogExit();
			
			AddQuestRecord("PZ", "13");
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_CaveEntrance")], false);
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "PZ_BasTer_OtryadRazveli", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				LAi_CharacterDisableDialog(sld);
			}
			sld = CharacterFromID("PZ_BasTer_OtryadPesheraOff");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "PZ_BasTer_OtryadRazveli", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_CharacterDisableDialog(sld);
			
			sld = CharacterFromID("Longway");
			AddPassenger(pchar, sld, false);
			LAi_SetImmortal(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.Dialog.CurrentNode = "Longway_officer";
			
			DeleteQuestCondition("PZ_LongwayNelzyaUmeret");
			
			//Продолжение второго этапа
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition = "PZ_LongwayRazgovorVKaute";
		break;
		
		case "PZ_BasTer_SOtryadomOhotnik_1":
			dialog.text = "„Nie ma mowy, monsieur! Zabił całą masę naszych ludzi, a teraz mówisz, że mu to ujdzie na sucho?! Albo pomożesz nam zabić tego drania, albo przynajmniej trzymaj się z dala od naszej drogi!”";
			link.l1 = "Obawiam się, że muszę się wtrącić. Przepraszam, naprawdę.";
			link.l1.go = "PZ_BasTer_SOtryadomOhotnik_2";
		break;
		
		case "PZ_BasTer_SOtryadomOhotnik_2":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Longway");
			LAi_SetImmortal(sld, false);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_CharacterDisableDialog(sld);
			}
			sld = CharacterFromID("PZ_BasTer_OtryadPesheraOff");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_CharacterDisableDialog(sld);
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_IshemLongway_Zastupaemsya");
			
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1 = "NPC_Death";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1.character = "Longway";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition = "PZ_LongwayNelzyaUmeret";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_Bad_1":
			dialog.text = "Jeśli chciałeś tylko porozmawiać, nie prosiłbyś mnie o rozbrojenie. Ale tygrys to wciąż tygrys, nawet z pazurami schowanymi. Musiałeś już dawno zdecydować się zdradzić Longwaya - nie musisz kłamać. Broń się, Kapitanie!";
			link.l1 = "Kurwa!";
			link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_Bad_2";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_Bad_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_CaveEntrance")], false);
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				LAi_CharacterDisableDialog(sld);
			}
			
			sld = CharacterFromID("Longway");
			LAi_SetImmortal(sld, false);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_BasTer_MyUbilLongway_BadFinal");
		break;
		
		case "PZ_BasTer_SOtryadom_UbiliLongway":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "Nie mogę uwierzyć, że udało nam się go przechytrzyć! Ale powiedz mi, dlaczego nazywał cię Kapitanem?";
				link.l1 = "To bardziej skomplikowane, niż się wydaje, kumplu. Musiałem uspokoić twojego dowódcę. Ważne jest, by osiągnąć wynik, prawda? A wynik jest taki, że Longway nie żyje, i pomogłem ci w tym.";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_2";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "Nawet twoja obecność nie pomogła - i tak nas zaatakował. Przeklęty dzikus...";
				link.l1 = "Nie powinieneś tak o nim mówić. Zaatakował nas, bo był zdenerwowany i myślał, że jestem z tobą.";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_2";
			}
		break;
		
		case "PZ_BasTer_SOtryadom_UbiliLongway_2":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "Może. W takim razie, do widzenia, monsieur. Sami powiemy komendantowi, że Chińczyk wreszcie nie żyje.";
				link.l1 = "Jak najbardziej, dziękuję. Do widzenia, chłopcy.";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_3";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "No cóż, czy jest zdenerwowany czy dziki, to niczego nie zmienia - wcześniej zabił wielu naszych, pierwszy przelał krew.";
				link.l1 = "Coś musiało doprowadzić go do tego stanu. Ale nie rozwodźmy się nad tym. Ja już pójdę, a ty możesz wrócić do komendanta, kiedy uznasz za stosowne. Do widzenia.";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_3";
			}
		break;
		
		case "PZ_BasTer_SOtryadom_UbiliLongway_3":
			DialogExit();
			
			LAi_SetWarriorType(npchar);
			LAi_CharacterDisableDialog(npchar);
			ChangeCharacterNationReputation(pchar, FRANCE, 12);
			AddQuestRecord("PZ", "11");
			CloseQuestHeader("PZ");
			
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog":
			dialog.text = "Wielmożny Panie Kapitanie?";
			link.l1 = "Aj! Szukałem cię wszędzie, Longway. Narobiłeś niezłego zamieszania w mieście. Mamy wiele do omówienia, więc wracajmy natychmiast na statek.";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_2";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_2":
			dialog.text = "Tam!";
			link.l1 = "Widzę, że mamy towarzystwo. Wygląda na to, że będziemy trochę spóźnieni.";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_3";
			locCameraFromToPos(-12.27, 1.29, -8.89, true, -3.23, -1.20, -4.77);
			DoQuestCheckDelay("PZ_IshemLongway_SorraKomendant_Dialog_Povernutsya", 1.3);
			
			for (i=1; i<=5; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_BasTer_OtryadPeshera"+i, "sold_fra_"+(rand(7)+1), "man", "man", sti(pchar.rank), FRANCE, 0, true, "soldier"));
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
				LAi_SetHP(sld, 60.0, 60.0);
			}
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_3":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_CaveEntrance")], false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Longway");
			LAi_SetImmortal(sld, false);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_IshemLongway_SorraKomendant_Pobeda1");
			
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1 = "NPC_Death";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1.character = "Longway";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition = "PZ_LongwayNelzyaUmeret";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_4":
			dialog.text = "Nadchodzą więcej!";
			link.l1 = "Uparci dranie - to im trzeba przyznać. Jesteśmy tutaj zbyt na widoku. Ruszajmy do jaskini - łatwiej będzie się bronić.";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_5";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_5":
			DialogExit();
			pchar.questTemp.PZ_IshemLongway_SorraKomendant = true;
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			
			sld = CharacterFromID("Longway");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
			
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocation(pchar, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_6":
			dialog.text = "Nie możemy tu zostać na zawsze.";
			link.l1 = "„I to jest pierwsza rzecz, którą chcesz powiedzieć po tym wszystkim, co się wydarzyło, Longway? Nie sądzisz, że czas już wyjaśnić, co się dzieje?”";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_7";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_7":
			dialog.text = "Wielmożny Panie Kapitanie, Longway...";
			link.l1 = "Ale masz rację - nie możemy tu zostać. Ruszajmy, zanim pojawi się kolejna drużyna. Porozmawiamy na statku, gdy już wypłyniemy.";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_8";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_8":
			DoQuestReloadToLocation("Guadeloupe_CaveEntrance", "reload", "reload1", "PZ_IshemLongway_VyhodIsPeshery");
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_1":
			dialog.text = "Podstęp i złośliwość białego człowieka nie mają granic.";
			link.l1 = "„Hej, ja też jestem białym człowiekiem! Poza tym zabiłeś ich przyjaciół i towarzyszy broni - mają prawo się złościć.”";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_2";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_2":
			dialog.text = "„Czy rozgrzeszasz ich, Wielmożny Panie Kapitanie?”";
			link.l1 = "Rozgrzeszam cię, Longway. I nalegam, byś nie sądził ludzi po kolorze ich skóry. Ty, z wszystkich ludzi, powinieneś to rozumieć. Przerwano nam - gdzie skończyliśmy...?";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_3";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_3":
			dialog.text = "Kapitanie! Za tobą!";
			link.l1 = "Och, nie pozwolą nam dziś na porządną rozmowę...";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_4";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_4":
			DialogExit();
			LAi_SetCurHPMax(pchar);
			LAi_GetCharacterMaxEnergy(pchar);
			LAi_SetCurHPMax(sld);
			LAi_GetCharacterMaxEnergy(sld);
			
			sld = CharacterFromID("Longway");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			for (i=6; i<=10; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_BasTer_OtryadPeshera"+i, "sold_fra_"+(rand(7)+1), "man", "man", sti(pchar.rank), FRANCE, 0, true, "soldier"));
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_SetHP(sld, 60.0, 60.0);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_IshemLongway_Zastupaemsya_5");
			
			AddDialogExitQuest("MainHeroFightModeOn"); // Rebbebion, fix
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_6":
			dialog.text = "Czytelne, Wielmożny Panie Kapitanie.";
			link.l1 = "To dobrze, ale nie zatrzymujmy się tutaj. Ty i ja mamy wiele do omówienia. Chodź za mną - wracamy na statek.";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_7";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_7":
			DialogExit();
			
			sld = CharacterFromID("Longway");
			AddPassenger(pchar, sld, false);
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0;
			sld.Health.maxHP    = 60.0;
			SetCharacterPerk(sld, "ShipEscape");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.Dialog.CurrentNode = "Longway_officer";
			
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			AddQuestRecord("PZ", "14");
			DeleteQuestCondition("PZ_LongwayNelzyaUmeret");
			DeleteQuestCondition("PZ_KorablBuhta_BadFinal");
			
			//Продолжение второго этапа
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition = "PZ_LongwayRazgovorVKaute";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_1":
			dialog.text = "Wielmożny Panie Kapitanie, czy to naprawdę Ty...?";
			link.l1 = "Tak, Longway. Wszystko w porządku?";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_2";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_2":
			dialog.text = "Longway ma się dobrze. Dziękuję. Ale, Kapitanie! Spójrz!";
			link.l1 = "Biegnij do jaskini, pospiesz się! To dobra pozycja defensywna!";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_3";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_3":
			DialogExit();
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			
			sld = CharacterFromID("Longway");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
			
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocation(pchar, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
		break;
		
		case "PZ_IshemLongway_SrazuNashli_4":
			dialog.text = "Longway sprawdzi, czy żołnierze nadal nadchodzą.";
			link.l1 = "Pójdziemy razem - nie damy rady bronić się przed całym garnizonem.";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_5";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_5":
			dialog.text = "Tak, Wielmożny Panie Kapitanie?";
			link.l1 = "Mamy wiele do omówienia. Teraz chodź za mną - musimy natychmiast podnieść kotwicę.";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_6";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_6":
			DoQuestReloadToLocation("Guadeloupe_CaveEntrance", "reload", "reload1", "PZ_IshemLongway_VyhodIsPeshery");
		break;
		
		// Этап 2, СТРАНИЦЫ ИСТОРИИ
		case "PZ_LongwayRazgovorOProshlom":
			dialog.text = "Dziękuję ponownie za pomoc, Wielmożny Panie Kapitanie. Jestem pewien, że masz wiele pytań.";
			link.l1 = "„To łagodnie powiedziane. Dlaczego zabiłeś tych żołnierzy? Nie zabijasz dla przyjemności – wiem o tym.”";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_LongwayRazgovorOProshlom_2":
			dialog.text = "Nie, Longway nie chce tego. Żołnierze próbowali powstrzymać Longwaya, a więzienie nie było opcją. Nie słuchaliby Chińczyka - tylko biały człowiek dostaje taką uprzejmość.";
			link.l1 = "„Nie zawsze słuchają też innych białych, ale rozumiem, o co ci chodzi. Jednakże, zarzynać ich jak bydło w mieście? Co robiłeś w Basse-Terre?”";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_3";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_3":
			dialog.text = "Not only do white people often not listen to me; sometimes they won't even talk. And when they do, it's to call the guards. Longway didn't choose his skin or his eyes, but he's proud of who he is. When soldiers mock and threaten, Longway grows tired... and angry.";
			link.l1 = "Od teraz pracujmy razem. Ludzie rozmawiają ze mną zamiast wzywać straż... zazwyczaj. Ale poważnie, opowiedz mi o swojej misji. Pozwól mi ci pomóc.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_4";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_4":
			dialog.text = "Proszę, Wielmożny Panie Kapitanie, zrozum Longwaya. Złożył przysięgę, że zrobi to sam. Nie naciskaj go. Tyle jesteś mu winien.";
			link.l1 = "Jestem naprawdę wdzięczna, ale wtedy mogłam poradzić sobie z van Merdenem sama. Jednak od początku byliśmy kwita - powiedziałeś, że uratowałam ci twarz, a ty uratowałeś moje życie. Teraz znowu cię uratowałam.";
			if (CheckAttribute(pchar, "questTemp.PZ_NashliArhiv")) link.l1.go = "PZ_LongwayRazgovorOProshlom_5";
			else link.l1.go = "PZ_LongwayRazgovorOProshlom_Grubim_1";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_5":
			dialog.text = "Hmm... masz rację, Wielmożny Panie Kapitanie. Longway wierzy, że jesteś jego prawdziwym przyjacielem wśród białych ludzi. Kiedyś tak myślał, ale gorzko się pomylił. Pamiętasz Johna Murdocka? Johana van Merdena?";
			link.l1 = "Dziwne, że wspominasz o van Merdenie. Niedawno ktoś wyrwał kilka stron z jego archiwum tuż pod moim nosem. Czy to miało związek z twoją sprawą? Znalazłeś złodzieja?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_6";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_6":
			dialog.text = "Zrobiłem to. Złodziejem był... Longway. Bardzo przeprasza, Wielmożny Panie Kapitanie. Wtedy nie wiedział, czy może ci całkowicie zaufać.";
			if (sti(pchar.reputation.nobility) <= 60)
			{
				link.l1 = "Mówisz o przyjaźni, ale kradniesz mi za plecami? To jest pierwszy i ostatni raz, Longway. Czy rozumiesz?";
				link.l1.go = "PZ_LongwayRazgovorOProshlom_Grubim_1";
				notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(61))+")", "None");
			}
			else
			{
				link.l1 = "„A jak udało ci się to zrobić, Longway?”";
				link.l1.go = "PZ_LongwayRazgovorOProshlom_Proshaem_1";
				notification("Reputation Check Passed", "None");
			}
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Grubim_1":
			dialog.text = "Longway rozumie. Mówi to poważnie.";
			link.l1 = "Mam nadzieję. Teraz powiedz mi, jak doszedłeś do tego życia - jaką obietnicę złożyłeś, kiedy i komu.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_Grubim_2";
			if (CheckAttribute(pchar, "questTemp.PZ_NashliArhiv")) AddComplexSelfExpToScill(100, 100, 100, 100);
			notification("Longway disapproves", "Longway");
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Grubim_2":
			dialog.text = "Tak, Wielmożny Panie Kapitanie\nLongway poszukuje najważniejszej żyjącej dla niego osoby-Chang Xing.";
			link.l1 = "Chang Xing - czy to twój najlepszy przyjaciel?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_7";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Proshaem_1":
			dialog.text = "Dzięki twojej życzliwości reszta załogi szybko się do mnie przyzwyczaiła i zaczęła mi ufać.";
			link.l1 = "„Cóż, rozumiem. Nie przepadasz za pochwałami, ale dobra robota, Longway... jeśli posprzątałeś bałagan, który zostawiła twoja interwencja.”";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_Proshaem_2";
			AddComplexLandExpToScill(200, 200, 0);
			pchar.questTemp.PZ_FlagArhiv = true;
			notification("Longway approves", "Longway");
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Proshaem_2":
			dialog.text = "„Racja. Ale nie ma na to czasu.”";
			link.l1 = "Chyba nie. Ale postaraj się tego nie robić ponownie, tak, co nie? Jeśli potrzebujesz czegokolwiek, po prostu zapytaj. Możesz mi zaufać. Teraz, opowiedz mi o swojej przysiędze.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_Proshaem_3";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Proshaem_3":
			dialog.text = "„Oczywiście, Longway chętnie podzieli się swym ciężarem z Tobą, Wielmożny Panie Kapitanie.\nLongway poszukuje najważniejszej dla niego żyjącej osoby - Chang Xing.”";
			link.l1 = "Czy Chang Xing jest twoim najlepszym przyjacielem?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_7";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_7":
			dialog.text = "Chang Xing jest moją rodziną, moją siostrą. Zaginęła wiele lat temu. Aby ją odnaleźć, Longway szuka tych, którzy mogą wiedzieć, gdzie ona jest.";
			link.l1 = "Co to ma wspólnego z archiwum van Merdena? Czy to jest powiązane z zaginięciem twojej siostry?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_8";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_8":
			dialog.text = "Zgadza się. To wszystko jest połączone. Longway i Johan spotkali się wiele lat temu, w krainie, którą nazywacie Formoza, na długo zanim przybyłem na Archipelag.";
			link.l1 = "Znacie się od tylu lat? I van Merden był zamieszany? Co za historia! Jaki był jego związek z zaginięciem twojej siostry?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_9";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_9":
			dialog.text = "Pomógł mi w poszukiwaniach bardzo złych ludzi - nawet według standardów białych. Oliveiro Fermentelos, Antoon van Diemen i Joep van der Vink.";
			link.l1 = " Sądząc po ich imionach, jeden jest Portugalczykiem, a pozostałych dwóch to Holendrzy.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_10";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_10":
			dialog.text = "Tak, to prawda. Ale poszukiwania nie przyniosły sukcesu. Longway cierpliwie czekał na znak z niebios. Więc gdy zdobyłeś archiwum van Merdena, postanowiłem je przestudiować. Gdy znalazłem pierwsze strony wspominające Oliveiro, wyrwałem je i uciekłem z kabiny.";
			link.l1 = "Wszystko w końcu pasuje do opowieści.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_11";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_11":
			dialog.text = " Ale sama historia dopiero się zaczyna. Wielmożny Panie Kapitanie, czy chciałbyś poznać poszukiwania Longwaya od samego początku? Czy jesteś gotów usiąść i posłuchać?";
			link.l1 = "„Dokładnie dlatego wezwałem cię do kajuty. Kontynuuj.”";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_12";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_12":
			DialogExit();
			
			SetCurrentTime(12, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			SetMainCharacterIndex(GetCharacterIndex("Longway"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			DoQuestReloadToLocation("Formosa", "patrol", "patrol1", "PZ_Formosa_Start");
		break;
		
		case "PZ_Formosa_Tavern_1":
			dialog.text = "„Chińczycy nie są tu mile widziani. To szanowane miejsce, dla szanowanych ludzi, nie dla takich jak ty.”";
			link.l1 = "Ja mam tylko jedno pytanie. Pozwól mi je zadać, a odejdę.";
			link.l1.go = "PZ_Formosa_Tavern_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Formosa_Tavern_2":
			dialog.text = "Najpierw naucz się mówić poprawnie! Mówiłem ci - twojego rodzaju tutaj nie chcą.";
			link.l1 = "Gdzie mogę znaleźć Oliveiro Fermentelos? Powiedz mi, a już mnie tu nie będzie.";
			link.l1.go = "PZ_Formosa_Tavern_3";
		break;
		
		case "PZ_Formosa_Tavern_3":
			dialog.text = "Czy jesteś głuchy też? Nie testuj mojej cierpliwości, bo wkrótce cały ten pokój będzie śmierdział żółtymi flakami.";
			link.l1 = "„Moi ludzie żyją tutaj od tysięcy lat. To nasza wyspa, a nawet nie możemy wejść do zwykłej tawerny?”";
			link.l1.go = "PZ_Formosa_Tavern_4";
		break;
		
		case "PZ_Formosa_Tavern_4":
			dialog.text = "Oho, gadasz odważnie, co? Możesz za to zawisnąć. Wynocha!";
			link.l1 = "...";
			link.l1.go = "PZ_Formosa_Tavern_5";
		break;
		
		case "PZ_Formosa_Tavern_5":
			DialogExit();
			locCameraSleep(true);
			LAi_CharacterDisableDialog(npchar);
			
			sld = CharacterFromID("PZ_Formosa_smuggler");
			LAi_CharacterEnableDialog(sld);
			//AddLandQuestMark(sld, "questmarkmain");
			LAi_Fade("PZ_Formosa1_9", "");
		break;
		
		case "PZ_Formosa_smuggler_1":
			dialog.text = "Słyszałem o twoim wielkim problemie, mój mały przyjacielu. Nie powinieneś był być tak głośny - złe imię, złe miejsce.";
			link.l1 = "„Wiesz coś o tym człowieku?! Powiedz mi!”";
			link.l1.go = "PZ_Formosa_smuggler_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Formosa_smuggler_2":
			dialog.text = "Spokojnie, kamracie.";
			link.l1 = "Moje przeprosiny.";
			link.l1.go = "PZ_Formosa_smuggler_3";
		break;
		
		case "PZ_Formosa_smuggler_3":
			dialog.text = "„Nie chcę twoich przeprosin, ale chcę twoje pieniądze. Może wtedy ci pomogę. Jestem Marcelo Schulte. A ty? Masz pieniądze, prawda?”";
			link.l1 = "Nazywam się Chang Tu. Mam pieniądze. Czy to wystarczy?";
			link.l1.go = "PZ_Formosa_smuggler_4";
		break;
		
		case "PZ_Formosa_smuggler_4":
			dialog.text = "„(gwiżdże) Escudos, pesos, guldeny, dublony... i nawet te dziwne monety, które wy, ludzie, macie. To się nada. Dobrze, Chung Chung, zobaczę, co mogę dowiedzieć się o tym człowieku. Nie martw się, jestem tu prawie codziennie, więc twoje pieniądze są bezpieczne. Sprawdzaj codziennie, a na pewno się spotkamy.”";
			link.l1 = "Mam nadzieję. Nie mam już więcej pieniędzy...";
			link.l1.go = "PZ_Formosa_smuggler_5";
		break;
		
		case "PZ_Formosa_smuggler_5":
			DialogExit();
			LAi_SetStayType(pchar);
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("A few days have passed,"+ NewStr() +"April 4, 1645.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Formosa_tavern", "goto", "goto1", "PZ_Formosa_Spustya4Dnya");
			LaunchFrameForm();
		break;
		
		case "PZ_Formosa_smuggler_11":
			dialog.text = "Ach, Chang-Chang! Już tu jesteś.";
			link.l1 = "To Chang Tu.";
			link.l1.go = "PZ_Formosa_smuggler_12";
		break;
		
		case "PZ_Formosa_smuggler_12":
			dialog.text = "Nieważne, kumplu.";
			link.l1 = "„Czy dowiedziałeś się, gdzie jest Oliveiro?”";
			link.l1.go = "PZ_Formosa_smuggler_13";
		break;
		
		case "PZ_Formosa_smuggler_13":
			dialog.text = "Nie, nie mam najmniejszego pojęcia.";
			link.l1 = "Moje pieniądze!";
			link.l1.go = "PZ_Formosa_smuggler_14";
		break;
		
		case "PZ_Formosa_smuggler_14":
			dialog.text = "Nie bądź taki nerwowy! Czy miałbym odwagę podejść do ciebie ponownie, gdybym niczego się nie dowiedział? Przedstawię ci kogoś, kto wie. I masz szczęście, bo on kocha was, Azjatów. Ma nawet służących, którzy do was pasują - ba, nawet służące. Uczy się też waszego plugawskiego języka. Nazywa się Johan van Merden. Będzie na ciebie czekał w dwupiętrowym domu w pobliżu rezydencji.";
			link.l1 = "Moje podziękowania.";
			link.l1.go = "PZ_Formosa_smuggler_15";
		break;
		
		case "PZ_Formosa_smuggler_15":
			DialogExit();
			
			locCameraSleep(true);
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload1_back", "PZ_Formosa1_11", -1);
			LAi_ActorGoToLocation(npchar, "goto", "goto3", "", "", "", "", -1);
			npchar.location = "None";
			LocatorReloadEnterDisable("Formosa", "houseSp1", false);
		break;
		
		case "PZ_Formosa_JohanVanMerden_1":
			dialog.text = "Jesteś Chang Chang, tak? Wejdź, nie krępuj się.";
			link.l1 = "To Chang Tu.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_2";
			DelLandQuestMark(npchar);
			locCameraFromToPos(-1.91, 2.06, -1.75, true, 2.23, -0.85, 0.85);
		break;
		
		case "PZ_Formosa_JohanVanMerden_2":
			dialog.text = "Czyżby? Moje przeprosiny. Ten Marcelo i jego parada dowcipów... Szkoda, że tak niewielu interesuje się twoją kulturą. A wszystko to tylko z powodu innego języka i kształtu twoich oczu. Ale ty jesteś inteligentny. W przeciwieństwie do czarnych, hehehe.";
			link.l1 = "(w mandaryńskim) A więc przemytnik nie kłamał - naprawdę jesteś człowiekiem kultury. I naprawdę mówisz w naszym języku?";
			link.l1.go = "PZ_Formosa_JohanVanMerden_2a";
			link.l2 = "Serdecznie dziękuję za ciepłe słowa na temat mojej kultury. Czy jesteś Johan van Merden?";
			link.l2.go = "PZ_Formosa_JohanVanMerden_3";
		break;
		
		case "PZ_Formosa_JohanVanMerden_2a":
			dialog.text = "„Och... Zrozumiałem tylko kilka słów. Wciąż się uczę, widzisz. Czy mógłbyś kontynuować po niderlandzku?”";
			link.l1 = "Jak sobie życzysz. Jesteś Johan van Merden?";
			link.l1.go = "PZ_Formosa_JohanVanMerden_3";
		break;
		
		case "PZ_Formosa_JohanVanMerden_3":
			dialog.text = "„Tak, Chung Tu, to ja. Słyszałem, że szukasz Oliveiro Fermentelosa. Wiem, gdzie go znaleźć, ale najpierw powiedz mi – dlaczego go szukasz? Twoja odpowiedź zdecyduje o mojej.”";
			link.l1 = "On... porwał mojego ostatniego i najdroższego członka rodziny - moją siostrę, Chang Xing.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_4";
		break;
		
		case "PZ_Formosa_JohanVanMerden_4":
			dialog.text = "Zatem muszę cię rozczarować, Chang Tu. Prawdopodobnie nie ma już dla niej nadziei. Najpewniej została sprzedana w niewolę bogatemu plantatorowi lub do burdelu. Tak czy inaczej, nie będziesz w stanie jej ocalić.";
			link.l1 = "Wierzę, że Chang Xing wciąż żyje. Oliveiro na nią spojrzał. Dumnie mu odmówiła. Porwał ją, gdy nie było mnie w domu. I... zabił naszych rodziców.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_5";
		break;
		
		case "PZ_Formosa_JohanVanMerden_5":
			dialog.text = "Ja... bardzo mi przykro. Jeśli tak jest, Chang Xing-prawda?-może wciąż żyje. Oto, co zrobimy: daj mi trochę czasu, żeby dowiedzieć się dokładnie, gdzie Oliveiro jest teraz. Powiedzmy tydzień. Spotkamy się wtedy znowu. Spotkaj się ze mną za bramami miasta-kto wie, jakie oczy cię tutaj śledzą. Nie chcę angażować się bardziej, niż jestem przyzwyczajony, mam nadzieję, że rozumiesz.";
			link.l1 = "Jestem... Jestem głęboko wdzięczna, Mynheer van Merden. Czekam z niecierpliwością na nasze kolejne spotkanie.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_6";
		break;
		
		case "PZ_Formosa_JohanVanMerden_6":
			DialogExit();
			LAi_SetStayType(pchar);
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("A week has passed,"+ NewStr() +"April 11, 1645.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Formosa_ExitTown", "goto", "goto3", "PZ_Formosa_Spustya7Dney");
			LaunchFrameForm();
		break;
		
		case "PZ_Formosa_JohanVanMerden_11":
			dialog.text = "Witaj, Chung Tu. Widzę ogień w twoich oczach. Mam wieści, ale nie są dobre.";
			link.l1 = "Jakiekolwiek wieści są dla mnie niezwykle ważne. Proszę, powiedz mi, Mynheer van Merden.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_12";
		break;
		
		case "PZ_Formosa_JohanVanMerden_12":
			dialog.text = "„Aye... Fermentelos wyjechał do Batawii około miesiąc temu. To jedyny trop, jaki mam na jego temat. Dobrą wiadomością jest to, że planuje tam zostać przez jakiś czas, więc jeśli teraz wyruszysz, złapiesz go. Złą wiadomością? Jest bliskim przyjacielem Generalnego Gubernatora Anthony'ego van Diemena. Nie zbliżysz się do niego.”";
			link.l1 = "Te wieści są wystarczające. Moje pokorne podziękowania dla ciebie, Wielmożny Panie van Merden. Wyruszam natychmiast.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_13";
		break;
		
		case "PZ_Formosa_JohanVanMerden_13":
			dialog.text = "Coś mi mówiło, że tak powiesz, więc postanowiłam wyrównać szanse dla ciebie i Chang Xinga. Napisałam list do starego przyjaciela, Olivera Trusta. Prowadzi sklep w Batawii. Jest mi winien przysługę, więc ci pomoże.";
			link.l1 = "Ja... Nie wiem, co powiedzieć...";
			link.l1.go = "PZ_Formosa_JohanVanMerden_14";
			//Log_Info("Вы получили письмо");
			PlaySound("interface\important_item.wav");
		break;
		
		case "PZ_Formosa_JohanVanMerden_14":
			dialog.text = "Zwykłe „dziękuję” wystarczy. Jeśli nie możesz znaleźć Oliveiro w mieście, szukaj „Morning Star”. Zawsze możesz go namierzyć przez jego statek. Powodzenia, mój przyjacielu - tobie i twojej siostrze się przyda.";
			link.l1 = "Dziękuję z głębi mojego serca, Wielmożny Panie van Merden.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_15";
		break;
		
		case "PZ_Formosa_JohanVanMerden_15":
			DialogExit();
			LAi_SetStayType(pchar);
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("Batavia,"+ NewStr() +"May 29, 1645.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Batavia", "merchant", "mrcActive5", "PZ_Batavia_Puteshestvie");
			LaunchFrameForm();
		break;
		
		case "PZ_OliverTrust_1": //
			dialog.text = "Kim jesteś i co tu robisz? Nie handluję z takimi jak ty.";
			link.l1 = "Mam list dla ciebie.";
			link.l1.go = "PZ_OliverTrust_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_OliverTrust_2":
			dialog.text = "Ach, posłaniec! Choć nie spodziewałem się dziś żadnych listów. Zostań tutaj! Sprawdzę to.";
			link.l1 = "„Czy jesteś Oliver Trust? Van Merden mnie do ciebie przysłał.”";
			link.l1.go = "PZ_OliverTrust_3";
			//Log_Info("Вы отдали письмо");
			PlaySound("interface\important_item.wav");
		break;
		
		case "PZ_OliverTrust_3":
			dialog.text = "„Potrafię czytać, wiesz. Normalnie, odesłałbym cię, ale ludzie tacy jak van Merden nie przyjmują odmowy jako odpowiedzi. W końcu nadszedł czas, by wyrównać rachunki z van Diemenem.”";
			link.l1 = "Mój cel to Fermentelos. A co z van Diemenem?";
			link.l1.go = "PZ_OliverTrust_4";
		break;
		
		case "PZ_OliverTrust_4":
			dialog.text = "To nie twoja sprawa. Powinieneś być wdzięczny, że w ogóle ci pomagam. Teraz słuchaj uważnie, zanim zdecyduję, że to zły pomysł. Znam Fermentelosa. Był tu przez jakiś czas, ale już go tu nie ma. „Gwiazda Poranna” odpłynęła kilka tygodni temu. Bóg wie, kiedy wróci. Twój cel się zmienił, a jest nim przyjaciel Fermentelosa...";
			link.l1 = "... van Diemen.";
			link.l1.go = "PZ_OliverTrust_5";
		break;
		
		case "PZ_OliverTrust_5":
			dialog.text = "Tak. Wiesz o tym także? Zakładam, że Johan ci powiedział? Och, van Merden... jesteś śmiałym draniem. Ale skoro już wiesz o van Diemenie, to wiesz o jego wysokiej pozycji, prawda? Jaki jest twój mistrzowski plan, by dotrzeć do generalnego gubernatora? Na pewno nie przez szturmowanie jego rezydencji!";
			link.l1 = "Chang Tu jest utalentowanym wojownikiem.";
			link.l1.go = "PZ_OliverTrust_6";
		break;
		
		case "PZ_OliverTrust_6":
			dialog.text = "„Zręczny wojownik, co? Zdajesz sobie sprawę, że teraz jesteśmy w to wszystko wplątani? A co się stanie ze mną, jeśli cię pojmą? Będę musiał ci pomóc dla twojego i mojego bezpieczeństwa. Oprócz rezydencji, Van Diemen regularnie odwiedza plantację poza miastem i swoją kochankę Vette.”";
			link.l1 = " Wspomniałeś o pomocy dla mnie.";
			link.l1.go = "PZ_OliverTrust_12";
		break;
		
		case "PZ_OliverTrust_12":
			dialog.text = "Wierzę, że każdy powinien mieć pasję, hobby. Jeśli chodzi o mnie, zbieram rzadką i drogą broń. Czasami mają one historię, czasami nie, ale zawsze są śmiertelne. Moja kolekcja może być użyteczna dla twojej krucjaty. Powiedz mi więc, gdzie planujesz zasadzić się na van Diemena?";
			link.l1 = "„(Rezydencja) Skoro masz tak wiele dobrych broni, wezmę najlepszą klingę. Dzięki niej Chang Tu będzie niezrównany wśród białych ludzi.”";
			link.l1.go = "PZ_OliverTrust_resedinsia_1";
			link.l2 = "(Plantacja) Zaatakuję ich na drodze do plantacji - nie będą mieli gdzie uciec.";
			link.l2.go = "PZ_OliverTrust_Plantation1";
			link.l3 = "„Pani - nie będzie tam wielu ludzi, więc strażnicy nie zareagują na czas.”";
			link.l3.go = "PZ_OliverTrust_lubovnitsa_1";
			SetCharacterPerk(pchar, "Gunman");
			SetCharacterPerk(pchar, "GunProfessional");
			InterfaceStates.Buttons.Save.enable = false;
		break;
		
		// Rebbebion, ну, с Богом...
		case "PZ_OliverTrust_Plantation1":
			pchar.questTemp.PZ_Batavia_plantation_Go = true;
			
			dialog.text = "Dobry wybór! Jestem pod wrażeniem. Aby w pełni to wykorzystać, będziesz potrzebował dobrej broni palnej. Powiedz mi, jak daleko potrafisz celować, Chang Tu?";
			link.l1 = "By być szczerym... niedaleko, muszę się upewnić, że nie chybię."link.l1.go ="PZ_OliverTrust_Plantation_MediumDistance1";
			link.l2 = "Zaatakuję z daleka - mój wróg nawet nie zda sobie sprawy, skąd go uderzyłem.";
			link.l2.go = "PZ_OliverTrust_Plantation_FarDistance1";
			notification("Jager Unlocked", "Longway");
			SetCharacterPerk(pchar, "Jager");
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance1":
			// делаем Лонгвэя мушкетёром с одновременной выдачей мушкета
			/* pchar.model = "Longway_mush";
			pchar.model.animation = "mushketer"; */
			pchar.model = "Longway";
			pchar.model.animation = "Longway";
			Characters_RefreshModel(pchar);
			GiveItem2Character(pchar, "mushket6"); 
			EquipCharacterByItem(pchar, "mushket6");
			//Log_Info("Вы получили башенный мушкетон");
			PlaySound("interface\important_item.wav");
			
			AddItems(pchar, "grapeshot", 50);
			AddItems(pchar, "gunpowder", 50);
			LAi_SetCharacterUseBullet(pchar, GUN_ITEM_TYPE, "grapeshot");
			
			dialog.text = "Widzę. W takim razie, weź to! Antyczna portugalska wieżowa rusznica, strzelająca nabojem dużego kalibru. Takich już nie robią, nawet w Starym Świecie.";
			link.l1 = "Widziałem jednego jako dziecko...";
			link.l1.go = "PZ_OliverTrust_Plantation_MediumDistance2";
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance2":
			dialog.text = "Więc, wiesz jak się tym posługiwać?";
			link.l1 = "Nie...";
			link.l1.go = "PZ_OliverTrust_Plantation_MediumDistance3";
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance3":
			dialog.text = "Pamiętaj, że mechanizm wymienny z czasem zardzewiał. Żaden olej tego nie naprawi - jest już na dobre zepsuty. Ładowanie go jest trudne, więc zróbmy to teraz. Uważnie patrz - użyj trochę siły, tak jak tutaj. Ale nie za mocno, bo go złamiesz.";
			link.l1 = "„Tak to?”";
			link.l1.go = "PZ_OliverTrust_Plantation_MediumDistance4";
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance4":
			dialog.text = "Dokładnie.";
			link.l1 = "Zrozumiano.  Dziękuję bardzo!";
			link.l1.go = "PZ_OliverTrust_13";
		break;
		
		case "PZ_OliverTrust_Plantation_FarDistance1":
			// делаем Лонгвэя мушкетёром с одновременной выдачей мушкета
			/* pchar.model = "Longway_mush";
			pchar.model.animation = "mushketer"; */
			pchar.model = "Longway";
			pchar.model.animation = "Longway";
			Characters_RefreshModel(pchar);
			GiveItem2Character(pchar, "mushket2x2"); 
			EquipCharacterByItem(pchar, "mushket2x2");
			//Log_Info("Вы получили двуствольный штуцер");
			PlaySound("interface\important_item.wav");
			
			AddItems(pchar, "cartridge", 50);
			AddItems(pchar, "gunpowder", 50);
			LAi_SetCharacterUseBullet(pchar, GUN_ITEM_TYPE, "cartridge");
			
			dialog.text = "Prawdziwy myśliwy! Uważaj, to był prezent. To jeden z tych rzadkich przypadków, kiedy broń jest zarówno ozdobna, jak i śmiertelna. Dwulufowa strzelba myśliwska! Ciężka do trzymania, łatwa w użyciu. Czy już rozgryzłeś, jak z niej strzelać?";
			link.l1 = "Zrozumiano. Dziękuję bardzo!";
			link.l1.go = "PZ_OliverTrust_13";
		break;
		
		case "PZ_OliverTrust_lubovnitsa_1":
			dialog.text = "Masz rację co do strażników, ale nie lekceważ niebezpieczeństwa. Van Diemen nigdy nie chodzi po mieście bez swojego prawej ręki, Joepa van der Vink.";
			link.l1 = "„Więc, są razem z Vette...?”";
			link.l1.go = "PZ_OliverTrust_lubovnitsa_2";
			pchar.questTemp.PZ_Batavia_lubovnitsa_Go = true;
			AddCharacterSkillDontClearExp(pchar, "Sailing", 10);
			AddCharacterSkillDontClearExp(pchar, "Commerce", 10);
			AddCharacterSkillDontClearExp(pchar, "Repair", 10);
			notification("Naval Skills +", "Longway");
			notification("Rat Wolf Unlocked", "Longway");
			SetCharacterPerk(pchar, "RatsWolf");
		break;
		
		case "PZ_OliverTrust_lubovnitsa_2":
			dialog.text = "Co? Ha! Masz niezłą wyobraźnię, Chińczyku! Antoon to tchórz, a van der Vink jest tam, by go chronić, gdyby ktoś zakłócił ich „prywatny czas”. /nJoep zawsze nosi ciężką zbroję - nieprzeniknioną dla większości zimnych broni. Dlatego potrzebujesz czegoś specjalnego. Weź tę szpadę. Jest długa, mocniejsza niż większość innych mieczy i waży jak porządne ostrze.";
			link.l1 = "Szpada do walki z opancerzonymi wrogami...?";
			link.l1.go = "PZ_OliverTrust_lubovnitsa_3";
			//Log_Info("Вы получили асоледу");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "blade_26");
			EquipCharacterByItem(Pchar, "blade_26");
		break;
		
		case "PZ_OliverTrust_lubovnitsa_3":
			dialog.text = "Nie celuj w sam pancerz - to nie estok. Uderzaj w szczeliny i słabe punkty, takie jak krocze, pachy i gardło. Znuż go, narzucaj swoje warunki. Joep również dzierży ciężką siekierę, więc nie próbuj parować jego ciosów - unikaj zamiast tego. Na wypadek, gdybyś nie znalazł otwarcia, weź tę strzelbę. Zwykle jest naładowana śrutem, ale przygotowałem dla ciebie zestaw stalowych strzał.";
			link.l1 = "Strzały do muszkietu...?";
			link.l1.go = "PZ_OliverTrust_lubovnitsa_4";
			//Log_Info("Вы получили бландербуз");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "pistol8");
			EquipCharacterByItem(Pchar, "pistol8");
			AddItems(Pchar, "harpoon", 30);
			AddItems(Pchar, "gunpowder", 30);
			LAi_SetCharacterUseBullet(Pchar, GUN_ITEM_TYPE, "harpoon");
		break;
		
		case "PZ_OliverTrust_lubovnitsa_4":
			dialog.text = "Niezwykłe, prawda? Mieszanka starego i nowego. Jest zaprojektowany do strzału jedną ręką, ale jeśli jest zbyt ciężki, użyj obu. Wielu tak robi. A tutaj, spróbuj tej wiklinowej zbroi. Jest lżejsza niż kirys Joepa, ale nadal oferuje przyzwoitą ochronę. Nie pozwól, by jego topór trafił bezpośrednio - nawet mediolańska zbroja by nie wytrzymała takiej broni. Rozumiesz?";
			link.l1 = "Tak, rozumiem. Dziękuję, panie Trust!";
			link.l1.go = "PZ_OliverTrust_13";
			//Log_Info("Вы получили кожаный корсет");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "cirass5");
			EquipCharacterByItem(Pchar, "cirass5");
		break;
		
		case "PZ_OliverTrust_resedinsia_1":
			dialog.text = "Pewny siebie, co? Może za wcześnie opowiedziałem ci o mojej kolekcji. Ale... już się zaangażowałeś. Atak na rezydencję w biały dzień to odważny krok, którego się nie spodziewali. Ta klinga powinna odpowiadać twoim potrzebom. Nie jest najlepsza na świecie, ale idealna do dźgania, cięcia i siekania.";
			link.l1 = "Clewang! Rozpoznaję tę klingę. Mieszkańcy sąsiednich wysp często jej używają.";
			link.l1.go = "PZ_OliverTrust_resedinsia_2";
			pchar.questTemp.PZ_Batavia_resedinsia_Go = true;
			notification("Duelist Unlocked", "Longway");
			SetCharacterPerk(pchar, "FencingMaster");
			SetCharacterPerk(pchar, "HT1");
		break;
		
		case "PZ_OliverTrust_resedinsia_2":
			dialog.text = "Have you used one before? Good. You'll have little time and many enemies to face. Here, take this as well - a handgun with three barrels, beautifully inlaid. Load it now in front of me; you won't have time for that later. And wear this dueling waistcoat. It's light, it will give you the speed you'll need, and some protection.";
			link.l1 = "Dziękuję, Mynheer Trust!";
			link.l1.go = "PZ_OliverTrust_13";
			//Log_Info("Вы получили клеванг");
			//Log_Info("Вы получили трёхствольный дробовик");
			//Log_Info("Вы получили жилет бретера");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "blade_30");
			EquipCharacterByItem(Pchar, "blade_30");
			GiveItem2Character(PChar, "pistol2");
			EquipCharacterByItem(Pchar, "pistol2");
			GiveItem2Character(PChar, "cirass6");
			EquipCharacterByItem(Pchar, "cirass6");
			AddItems(Pchar, "grapeshot", 50);
			AddItems(Pchar, "gunpowder", 50);
			LAi_SetCharacterUseBullet(Pchar, GUN_ITEM_TYPE, "grapeshot");
		break;
		
		case "PZ_OliverTrust_13":
			dialog.text = "„Czekaj, jeszcze nie skończyliśmy. W naszym wspólnym interesie jest, abyś przeżył. Weź to lekarstwo, aby wyleczyć rany po bitwie. \nI ten eliksir też. Smakuje i pachnie okropnie, ale zabija każdą truciznę w twoim ciele. Joep van der Vink, ochroniarz Van Diemena, smaruje swoje bronie tym świństwem. Przemądrzały drań, więc będziesz miał przewagę.”";
			link.l1 = "Nie wiem, czy kiedykolwiek będę w stanie wystarczająco ci podziękować, Wielmożny Panie Kapitanie...";
			link.l1.go = "PZ_OliverTrust_14";
			//Log_Info("Вы получили 10 лечебных зелий");
			//Log_Info("Вы получили противоядие");
			PlaySound("interface\important_item.wav");
			AddItems(Pchar, "potion1", 10);
			AddItems(Pchar, "potion3", 1);
		break;
		
		case "PZ_OliverTrust_14":
			dialog.text = "Najlepszym podziękowaniem będzie nie wydanie mnie, jeśli cię złapią. Chociaż, najprawdopodobniej, po prostu cię zabiją na miejscu. Ale jeśli to przetrwasz, powiedz Van Diemenowi, że zawdzięcza mi swoją śmierć. Możesz to zrobić?";
			link.l1 = "Nie ma sprawy. Jeszcze raz dziękuję, Mynheer Trust. Do widzenia!";
			link.l1.go = "PZ_Batavia_NaOhotu";
		break;
		
		case "PZ_Batavia_NaOhotu":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_resedinsia_Go"))
			{
				DoQuestReloadToLocation("Batavia", "reload", "reload1", "PZ_Batavia_BitvaSoStrazhnikami");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_lubovnitsa_Go"))
			{
				DoQuestReloadToLocation("Batavia_HouseF3", "reload", "reload1", "PZ_Batavia_BitvaLubovnitsa");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_Plantation_Go"))
			{
				/*EndQuestMovie();
				sld = &Locations[FindLocation("Batavia_plantation")];
				sld.locators_radius.quest.detector4 = 3.0;
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1 = "locator";
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1.location = "Batavia_plantation";
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1.locator_group = "quest";
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1.locator = "detector4";
				PChar.quest.PZ_Batavia_plantation1.win_condition = "PZ_Batavia_plantation_selfdialog";*/
				DoQuestReloadToLocation("Batavia_plantation", "quest", "detector2", "PZ_Batavia_plantation_setguards");
			}
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_1":
			dialog.text = "Stój! Dokąd idziesz, Chińczyku?";
			link.l1 = "Do rezydencji.";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_2";
			locCameraFromToPos(-0.44, 7.45, 24.65, true, -1.90, 5.10, 18.50);
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_2":
			dialog.text = "„To było pytanie retoryczne, geniuszu. Co sprawia, że myślisz, że ktokolwiek pozwoliłby komuś takiemu jak ty tam wejść?”";
			link.l1 = "Mam interesy z Mynheerem Van Diemenem. Proszę, przepuść mnie.";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_3";
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_3":
			dialog.text = "Wiesz, jak się nazywa gubernator generalny? Cóż... powiedz mi, co cię tu sprowadza. Przekażę to dalej i wrócę do ciebie z odpowiedzią.";
			link.l1 = "Moja rozmowa jest tylko z Mynheer Van Diemenem. Czeka na mnie. Odsuń się, albo tego pożałujesz.";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_4";
			locCameraSleep(true);
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_4":
			dialog.text = "„No, no, nie pyskuj, skośnooki. Albo po mojemu, albo wcale.”";
			link.l1 = "Więc moja droga.";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_5";
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_5":
			DialogExit();
			LAi_SetActorType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_SoldResid_1"));
			LAi_group_MoveCharacter(pchar, LAI_GROUP_PLAYER);
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			
			sld = CharacterFromID("PZ_SoldResid_1");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
				
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			
			DoQuestCheckDelay("PZ_Batavia_resedinsia_1", 0.9);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_1":
			dialog.text = "Przeklęty chłopie! Kto cię wynajął? Zapłacę ci więcej niż oni!";
			link.l1 = "Wy, biali ludzie, tylko o złocie myślicie. Niech smoki przeklną wasz ród. Przyszedłem po informacje, ale wasi ludzie nie chcą mnie wpuścić.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_2";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_2":
			dialog.text = "Czego chcesz?!";
			link.l1 = "Fermentelos. Gdzie on teraz jest?";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_3";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_3":
			dialog.text = "Oliveiro? Ale po co do diabła ci on? Nic ci nie powiem!";
			link.l1 = "Zabił moją rodzinę i porwał moją siostrę. Moja rada dla ciebie: zacznij mówić. Dla własnego dobra.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_4";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_4":
			dialog.text = "Co zamierzasz mi zrobić? Cały garnizon zaraz tu będzie.";
			link.l1 = "Słyszałeś o Lynchy? To kara w mojej kulturze. Oznacza 'Śmierć przez Tysiąc Cięć.'";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_5";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_5":
			dialog.text = "Nie będziesz miał czasu, by zadać mi tyle cięć, ty imbecylu!";
			link.l1 = "„To tylko przenośnia. Kat zadaje cięcia, jedno po drugim. Albo odcina kawałki ciała. Robimy tyle, na ile mamy czas - chyba że zaczniesz mówić.”";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_6";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_6":
			DialogExit();
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Sepp", "mercen_26", "man", "man", sti(pchar.rank), HOLLAND, -1, false, "quest"));
			sld.name = "Joep";
			sld.lastname = "van der Vink";
			GiveItem2Character(sld, "topor_04");
			EquipCharacterByItem(sld, "topor_04");
			GiveItem2Character(sld, "pistol3");
			EquipCharacterByItem(sld, "pistol3");
			sld.CantLoot = true;
			LAi_SetHP(sld, 300.0, 300.0);
			ChangeCharacterAddressGroup(sld, "Batavia_townhallRoom", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			
			LAi_SetStayType(pchar);
			locCameraFromToPos(-3.06, 1.64, -0.43, true, 1.87, -1.20, 2.39);
			DoQuestCheckDelay("PZ_Batavia_BitvaResidensia_7", 2.5);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_7":
			dialog.text = "A-A-A!!! Stop! Stop, ty plugawy brutalu. Powiem ci, powiem ci wszystko. Tylko przestań. Joep! W końcu! Gdzie, do cholery, byłeś przez cały ten czas?!";
			link.l1 = "Co za niefart...";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_8";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_8":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Sepp");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_9";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_9":
			dialog.text = "Antoon? Musisz natychmiast zobaczyć się z lekarzem. Pomogę ci tam dotrzeć, gdy tylko tutaj skończę. Ty! Co do diabła robisz, ty żółty rzeźniku?!";
			link.l1 = "Żółty Rzeźnik? Podoba mi się to. Jest tylko jedno pytanie, na które potrzebuję odpowiedzi, ale nikt nie chce mi jej udzielić...";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_10";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_10":
			dialog.text = "Jakie pytanie?!";
			link.l1 = "Gdzie jest Oliveiro Fermentelos? Nie możesz po prostu tego powiedzieć?";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_11";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_11":
			dialog.text = "Nie obchodzi mnie Fermentelos! Kto dał ci pieniądze i informacje?!";
			link.l1 = "Olivier Trust. Przy okazji, chciał, żebym ci powiedział, że jesteś mu winien swoją śmierć.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_12";
			
			sld = CharacterFromID("PZ_AntoniOneDimen");
			LAi_ActorSetGroundSitMode(sld);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_12":
			dialog.text = "„Zaufanie?! Ha-ha-ha-ha-ha-ha-ha! Ten sknera, myśląc, że może się zemścić tylko dlatego, że zabraliśmy mu plantację? Wkrótce zabierzemy jego sklep i życie, jak tylko się z tobą rozprawię.”";
			link.l1 = "Marnujesz mój czas.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_13";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_13":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			
			PChar.quest.PZ_Batavia_BitvaResidensia_8.win_condition.l1 = "NPC_Death";
			PChar.quest.PZ_Batavia_BitvaResidensia_8.win_condition.l1.character = "PZ_Sepp";
			PChar.quest.PZ_Batavia_BitvaResidensia_8.win_condition = "PZ_Batavia_BitvaResidensia_8";
		break;
		
		case "PZ_Batavia_PlantationSelfDialog":
			dialog.text = "„(po mandaryńsku) Więc poszukajmy dobrego miejsca na zasadzkę.”";
			if (CheckCharacterItem(pchar, "mushket6"))
			{
				link.l1 = "„(po mandaryńsku) Z tym zardzewiałym czymś muszę podejść blisko. Szybka salwa - ostra i bezlitosna. Strach i panika zrobią resztę.”";
				link.l1.go = "Exit";
			}
			else
			{
				link.l1 = "„(po mandaryńsku) Tutaj. Na początku nawet mnie nie zobaczą. Najlepsze bitwy to te, które się nie zaczynają... albo kończą się szybko z niewielkim rozlewem krwi.”";
				link.l1.go = "Exit";
			}
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_Batavia_PlantationFight");
		break;
		
		case "PZ_Batavia_PlantationDimen1":
			if (!CharacterIsAlive("PZ_SoldPlantation_1") && !CharacterIsAlive("PZ_SoldPlantation_2") &&  !CharacterIsAlive("PZ_SoldPlantation_3") && !CharacterIsAlive("PZ_SoldPlantation_4") && !CharacterIsAlive("PZ_SoldPlantation_5") && !CharacterIsAlive("PZ_SoldPlantation_6"))
			{
				dialog.text = "Brudny brutal... Zbiegły niewolnik, prawda? Skąd masz taką broń? Ktoś cię wynajął...?";
				link.l1 = "Nie ma czasu! Powiedz mi, gdzie jest Oliveiro Fermentelos - teraz!";
				link.l1.go = "PZ_Batavia_PlantationDimen2";
			}
			else
			{
				dialog.text = RandSwear()+"";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_PlantationDimenSit");
			}
		break;
		
		case "PZ_Batavia_PlantationDimen2":
			dialog.text = "Hehehe, zabawne... Nie ma czasu - krew leje się z mojego brzucha. Płoń w piekle, poganinie...";
			link.l1 = "„(po mandaryńsku) Nie!!!”";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_Batavia_PlantationDimenDead1");
		break;
		
		case "PZ_Batavia_Plantation_DimenDeadSelfDialog":
			dialog.text = "„(po mandaryńsku) Dlaczego, dlaczego, dlaczego?! Jak mam teraz znaleźć Fermentelos?!”";
			link.l1 = "Ale najpierw muszę się ukryć - ktoś musiał już zgłosić tę rzeź...";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_1":
			dialog.text = "Hic! Chińczyk! Nie spodziewałem się, że ktoś taki jak ty zostanie tutaj zaproszony. Lubisz patrzeć, co? Hehe.";
			link.l1 = "„Dlaczego jest tu tyle ludzi...? I kim ty jesteś?”";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_2";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_2":
			dialog.text = "Nie poznajesz mnie po moim stroju? I uważaj na ton, kiedy rozmawiasz z Gubernatorem Generalnym! Hic!";
			link.l1 = "„Zatem, musisz być Mynheer Van Diemen. Przepraszam za moją ignorancję. Czy to tutaj odbywa się karnawał?”";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_3";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_3":
			dialog.text = "Zgadza się, mój dobry człowieku, i inaczej być nie może! Karnawał przebierańców! Ha-ha-ha! Nie tak źle, wieśniaku! Jestem pewien, że Luthers ba-a-ardzo chciałby założyć suknię Vette, ha ha ha!";
			link.l1 = "Luthers?..";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_4";
			locCameraFromToPos(-4.45, 2.11, 1.53, true, 0.47, -0.30, 2.74);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_4":
			dialog.text = "„Ta-a-aki żałosny pretekst na męża, który uwielbia podglądać z szafy, gdy jego droga żonka się zabawia. A ona nic sobie z tego nie robi!”";
			link.l1 = "";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_4_1";
			sld = CharacterFromID("PZ_Rubbe");
			CharacterTurnByChr(npchar, sld);
			CharacterTurnByChr(pchar, sld);
			CharacterTurnByChr(CharacterFromID("PZ_Brigitta"), sld);
			DoQuestCheckDelay("PZ_Batavia_BitvaLubovnitsa_4", 2.5);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_4_1":
			Event("QuestDelayExit","sl", "", 0);
			dialog.text = "„Prawda, Vette, moja droga? Heh-heh.”";
			link.l1 = "„(po mandaryńsku) Co się tu do diabła dzieje...”";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_5";
			sld = CharacterFromID("PZ_Rubbe");
			CharacterTurnByChr(npchar, CharacterFromID("PZ_Brigitta"));
			CharacterTurnByChr(pchar, npchar);
			CharacterTurnByChr(CharacterFromID("PZ_Brigitta"), npchar);
			locCameraFromToPos(-2.21, 1.90, 2.26, true, -0.81, -0.40, 4.36);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_5":
			dialog.text = "Hic! Nie wiem, co właśnie powiedziałeś, ale patrząc na twoje oczy i ton, zgadzasz się ze mną! Van Haan to cholerny zboczeniec. Więc, kim ty w ogóle jesteś? Pracownikiem? Vette cię zaprosił?";
			link.l1 = "„Ja...”";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_6";
			CharacterTurnByChr(pchar, npchar);
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(CharacterFromID("PZ_Brigitta"), pchar);
			locCameraFromToPos(-4.45, 2.11, 1.53, true, 0.47, -0.30, 2.74);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_6":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Sepp");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_7":
			dialog.text = "Zaproszenie tu robotnika to przesada, nawet dla Vette. On jest wyraźnie zagubiony i trafił nie tam, gdzie trzeba. Hej, ty. Wynoś się stąd i zapomnij wszystko, co widziałeś. Kto jest twoim panem? Skontaktujemy się z nim, a obaj dostaniecie zapłatę za milczenie. Może nawet pozwolą ci wrócić do rodziny na kontynencie. Odpowiedz mi i odejdź.";
			link.l1 = "Tak naprawdę, jestem tu w interesach.";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_8";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_8":
			dialog.text = "Heh, interesy. Jedynie Mynheer van Diemen tutaj robi „Interesy”. Moja praca to chronić go przed takimi jak ty. A Luthers... jest Luthers. Albo... czy Vette naprawdę cię tu zaprosił?";
			link.l1 = "„Nie, jestem tutaj, aby...”";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_9";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_9":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Rubbe");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_10";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_10":
			dialog.text = "Czyżby moja najdroższa Vette naprawdę zaprosiła tu tchórzliwego drania?! Wynoś się stąd!!!";
			link.l1 = "Nędzny rogacz...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_11";
			link.l2 = "Nikt do ciebie nie mówi. Zamknij gębę. Nie udawaj, że masz jaja lub godność.";
			link.l2.go = "PZ_Batavia_BitvaLubovnitsa_12";
			GiveItem2Character(npchar, "blade_06");
			EquipCharacterByItem(npchar, "blade_06");
			LAi_SetActorType(npchar);
			npchar.model.animation = "man";
			Characters_RefreshModel(npchar);
			SetCameraDialogMode(npchar);
			locCameraToPos(-1.88, 1.72, 0.27, false);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_11":
			dialog.text = "R-r-rogacz?! Nie, kocham ją bardziej niż siebie samego. Ha, głupi Chińczyk jak ty by tego nie zrozumiał!";
			link.l1 = "„Chory drań.”";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_13";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_12":
			dialog.text = "„Ko-kogut?! Jest w porządku! Tak! Po prostu wiem, że inni mężczyźni dają mojej drogiej Vette więcej przyjemności, to wszystko!”";
			link.l1 = "Jak mówimy w mojej ojczyźnie, człowiek pozostaje człowiekiem, dopóki ma choć jeden palec. Gdybyś był mężczyzną, zrozumiałbyś to.";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_13";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_13":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Brigitta");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_14";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_14":
			dialog.text = "Nie zaprosiłam go, oczywiście, ale, wiesz, jest całkiem miły. Może zostanie, gdy wszyscy odejdziecie. Już próbowałam to z naszym psem, ale nigdy nie robiłam tego z...";
			link.l1 = "Zamknij się, gdy mężczyźni rozmawiają, dziwko! Jesteś jedynym zwierzęciem tutaj. Jestem tu w interesach. Szukam Oliveiro Fermentelosa. Musicie być jego przyjaciółmi. Czy możesz mi powiedzieć, gdzie on może być, Mynheer Van Diemen?";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_15";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_15":
			dialog.text = "Antoon, on mnie obraził! Obraził mnie! Nie zostawisz tego tak, prawda?!";
			link.l1 = "...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_16";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_16":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_AntoniOneDimen");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_17":
			dialog.text = "Hehe, przepraszam, kumplu, ale dama jest wściekła. Będę musiał dać ci lekcję dobrych manier. Lekcja pierwsza.";
			link.l1 = "Ale czy możesz mi pomóc w poszukiwaniach Oliveiro?";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_18";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_18":
			dialog.text = "To nie pomoże martwemu robotnikowi.";
			link.l1 = "(w mandaryńskim) Do diabła z wami wszystkimi...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_19";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_19":
			DialogExit();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			PlaySound("Voice\Russian\hambit\Longway-02.wav");
			
			sld = CharacterFromID("PZ_AntoniOneDimen");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld = CharacterFromID("PZ_Sepp");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld = CharacterFromID("PZ_Rubbe");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_Batavia_BitvaLubovnitsa_3");
			
			sld = CharacterFromID("PZ_Brigitta");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			PlaySound("People Fight\Peace_woman_death_05.wav");
			DoQuestCheckDelay("PZ_Batavia_BitvaLubovnitsa_5", 3.0);	//Нужно ещё раз, а то не бежит
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_21":
			dialog.text = "„Do diabła! Niczego się nie dowiedziałem!”";
			link.l1 = "„(po mandaryńsku) Nigdy nie zapomnę tego dnia... Muszę stąd uciec, zanim przybędą strażnicy. Nie żeby ich obchodziły dźwięki dochodzące z tego domu wariatów...”";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_14":
			dialog.text = "„(w mandaryńskim) Bogowie przeklęli ten dzień! Van Diemen wykrwawił się na śmierć, gdy zajmowałem się jego pachołkiem...!”";
			link.l1 = "„(w mandaryńskim) Strażnicy nadchodzą. Będę musiał przebić się stąd siłą.”";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final":
			DialogExit();
			RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(PChar, MUSKET_ITEM_TYPE);
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_resedinsia_Go"))
			{
				TakeItemFromCharacter(pchar, "blade_30");
				TakeItemFromCharacter(pchar, "pistol2");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_lubovnitsa_Go"))
			{
				TakeItemFromCharacter(pchar, "blade_26");
				TakeItemFromCharacter(pchar, "pistol8");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_Plantation_Go"))
			{
				TakeItemFromCharacter(pchar, "mushket6");
				TakeItemFromCharacter(pchar, "mushket2x2");
			}
			EquipCharacterByItem(Pchar, "blade_11");
			pchar.model = "Longway";
			pchar.model.animation = "Longway";
			pchar.model.animation = "man";
			Characters_RefreshModel(pchar);
			
			
			SetCurrentTime(2, 30);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("Formosa,"+ NewStr() +"26 July 1645.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Formosa", "goto", "goto7", "PZ_Formosa2_Start");
			LaunchFrameForm();
		break;
		
		case "PZ_Formosa_smuggler_21":
			dialog.text = "„Och, to Chang Chang! Czego potrzebujesz pomocy tym razem, mój mały przyjacielu?”";
			link.l1 = "To Chang Tu... co masz na myśli?";
			link.l1.go = "PZ_Formosa_smuggler_22";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Formosa_smuggler_22":
			dialog.text = "Przepełnia cię pogarda do mnie, prawda? Nie przyszedłbyś tutaj, gdybyś czegoś nie potrzebował.";
			link.l1 = "Czy wiesz, gdzie jest van Merden? Czy jest w mieście? Nie ma go w domu. Muszę z nim porozmawiać.";
			link.l1.go = "PZ_Formosa_smuggler_23";
		break;
		
		case "PZ_Formosa_smuggler_23":
			dialog.text = "Mężczyzna nie może cały dzień siedzieć w domu, czekając, aż pojawi się jeden żółtoskóry człowiek. Ma interesy na wyspie. Wróci do miasta wieczorem, więc nie martw się, Chang Chang!";
			link.l1 = "Dziękuję. Do widzenia.";
			link.l1.go = "PZ_Formosa_smuggler_24";
		break;
		
		case "PZ_Formosa_smuggler_24":
			SetCurrentTime(1, 30);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			DoQuestReloadToLocation("Formosa", "goto", "goto7", "PZ_Formosa2_IshemMerden_3");
		break;
		
		case "PZ_Formosa_bandit_1":
			dialog.text = "„Hej, ty o wąskich oczach! Co za pośpiech o tej porze? Wszyscy przyzwoici ludzie już śpią.”";
			link.l1 = "W takim razie co z tobą?";
			link.l1.go = "PZ_Formosa_bandit_2";
		break;
		
		case "PZ_Formosa_bandit_2":
			dialog.text = "Dobrze powiedziane! Jesteśmy na patrolu! Mówią, że po mieście kręci się jakiś mały żółty gość, przeszkadzając bogobojnym ludziom.";
			link.l1 = "Któż to może być, proszę powiedzieć?";
			link.l1.go = "PZ_Formosa_bandit_3";
		break;
		
		case "PZ_Formosa_bandit_3":
			dialog.text = "Dosyć gadania - robi się późno, a ja zaczynam być śpiący.";
			link.l1 = "Wkrótce twój sen będzie wieczny.";
			link.l1.go = "PZ_Formosa_bandit_4";
		break;
		
		case "PZ_Formosa_bandit_4":
			DialogExit();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("PZ_JohanVanMerden");
			ChangeCharacterAddressGroup(sld, PChar.location, "patrol", "patrol7");
			GiveItem2Character(sld, "blade_31");
			EquipCharacterByItem(sld, "blade_31");
			LAi_SetActorType(sld);
			
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("PZ_FormosaBandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_Formosa2_IshemMerden_7");
			
			DoQuestCheckDelay("PZ_Formosa2_IshemMerden_6", 10.0);
		break;
		
		case "PZ_Formosa_JohanVanMerden_21":
			dialog.text = "Chang Tu, wszystko w porządku?";
			link.l1 = "„Mynheer van Merden! Jestem, dzięki twojej interwencji. Czy wszystko z tobą w porządku? To najważniejsze pytanie.”";
			link.l1.go = "PZ_Formosa_JohanVanMerden_22";
		break;
		
		case "PZ_Formosa_JohanVanMerden_22":
			dialog.text = "„Zawsze myślisz o innych, prawda? Mamy tę samą cechę. Nie mogłem bezczynnie stać, gdy widziałem, jak cię atakują, chociaż wiedziałem, że dasz sobie z nimi radę. Odpowiadając na twoje pytanie, mam się dobrze, tylko trochę zmęczony. Moje nogi są trochę chwiejne. Wejdźmy do środka, jeśli nie masz nic przeciwko. Tam możemy porozmawiać.”";
			link.l1 = "Oczywiście, Mynheer van Merden, w końcu to twój dom.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_23";
		break;
		
		case "PZ_Formosa_JohanVanMerden_23":
			DoQuestReloadToLocation("Formosa_houseSp1", "goto", "goto1", "PZ_Formosa2_IshemMerden_8");
		break;
		
		case "PZ_Formosa_JohanVanMerden_24":
			dialog.text = "Teraz możemy porozmawiać bez pośpiechu, w spokoju i ciszy. Powiedz mi, co cię do mnie sprowadza, Chang Tu?";
			link.l1 = "„Masz rację, Panie van Merden. Właśnie wróciłem z Batawii, i...”";
			link.l1.go = "PZ_Formosa_JohanVanMerden_25";
		break;
		
		case "PZ_Formosa_JohanVanMerden_25":
			dialog.text = "Czekaj. Czy to biedny Chang Xing...?";
			link.l1 = "Nie, wcale nie! Mam nadzieję, że nie. Niebo wciąż skrywa przede mną jej los. A co do Fermentelosa... nie ma go w Batawii. Van Diemen nie był pomocny.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_26";
		break;
		
		case "PZ_Formosa_JohanVanMerden_26":
			dialog.text = "Nie byłby, bo on i Oliveiro to starzy przyjaciele. Jak mówią Anglicy, przyjaciele i wspólnicy w zbrodni. Byłbym zaskoczony, gdyby dał ci coś użytecznego.";
			link.l1 = "Tak, dzięki zarówno tobie, jak i Trust, zdobyłem potężną broń. Zaatakowałem Van Diemena, by przesłuchać go i dowiedzieć się, gdzie jest Fermentelos. Ale zmarł, zanim zdążyłem się czegoś dowiedzieć...";
			link.l1.go = "PZ_Formosa_JohanVanMerden_28";
		break;
		
		case "PZ_Formosa_JohanVanMerden_28":
			dialog.text = "Imponujące. Zdałeś sobie sprawę, że ludzie nie zawsze chcą dzielić się tym, co wiedzą. Istnieją więc inne... metody perswazji, że tak powiem. Myślałam, że mogłeś dowiedzieć się o śmierci swojej siostry, i dlatego wpadłeś w szał. Ale co teraz sprowadza cię do mnie? Mówiłem ci, że nie wiem, dokąd udaje się Fermentelos, poza jego okazjonalnymi wizytami w Batawii. Z Van Diemenem nieobecnym, ten ostatni trop jest stracony.";
			link.l1 = "Ale znasz wiele rzeczy i ludzi. Pomyślałem, że możesz znów pomóc, może wypytać o Fermentelos, jak wcześniej. Byłeś pierwszym białym człowiekiem, który mnie dobrze traktował. Pierwszym... białym przyjacielem.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_29";
		break;
		
		case "PZ_Formosa_JohanVanMerden_29":
			dialog.text = "To jest... wzruszające.";
			link.l1 = "Mynheer van Merden, czemu się uśmiechasz...?";
			link.l1.go = "PZ_Formosa_JohanVanMerden_30";
		break;
		
		case "PZ_Formosa_JohanVanMerden_30":
			dialog.text = "Huh? Och, przepraszam, Chang Tu. Starzeję się, robię się sentymentalny i melancholijny z wiekiem. To szczery uśmiech - nie mogłem go ukryć. Cieszę się, że uważasz mnie za przyjaciela. Skoro jesteśmy przyjaciółmi, oczekuję, że będziesz mi czasami pomagać. W zamian, na pewno pomogę ci z Fermentelos. Nie martw się - nie wchodzisz w pułapkę.";
			link.l1 = "„Hmm, jak mogę ci pomóc?”";
			link.l1.go = "PZ_Formosa_JohanVanMerden_31";
		break;
		
		case "PZ_Formosa_JohanVanMerden_31":
			dialog.text = "Odkąd się ostatnio spotkaliśmy, pogłębiłem moją naukę waszego języka i kultury, zwłaszcza medycyny. Chciałbym, abyś od czasu do czasu znalazł dla mnie pewne relikwiarze. Zapłacę ci za nie hojnie, tak jak za każdą inną robotę. I mam nadzieję, że będziemy mogli czasem ćwiczyć nasze rozmowy po chińsku. Wstyd mi prosić o to moich służących, ale przyjaciel...";
			link.l1 = "Chang Tu zrobi wszystko, co w jego mocy, panie van Merden.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_32";
		break;
		
		case "PZ_Formosa_JohanVanMerden_32":
			dialog.text = "Dobrze. Ty i ja mamy przed sobą długą drogę, przyjacielu. Długą drogę. Ha! Myślę, że to byłoby dobre przykrycie dla ciebie. Przydatna praktyka mojego rzemiosła. Po holendersku to „Lange Afstand.” Anglicy mówią „Long Way.” Które wolisz?";
			link.l1 = "Lubię bardziej angielską wersję. Długa. Droga. Longway. Brzmi to całkiem odpowiednio w moim języku. Dziękuję, że wysłuchałeś mnie, Lordzie van Merden. Longway będzie oczekiwał twojego słowa i będzie gotowy, by ci pomóc i spełnić twoje prośby.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_33";
		break;
		
		case "PZ_Formosa_JohanVanMerden_33":
			DialogExit();
			
			SetCurrentTime(15, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			DeleteAttribute(pchar, "questTemp.lockedMusic");
			
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			
			bQuestDisableMapEnter = true;
			pchar.GenQuest.CabinLock = true;
			QuestToSeaLogin_Launch();
			QuestToSeaLogin_PrepareLoc("Guadeloupe", "Quest_Ships", "Quest_ship_8", false);
			DoQuestCheckDelay("PZ_SegodnyaVremya_2", 5.0);
		break;
		
		// Этап 3, СЛЕД ЗВЕЗДЫ
		case "PZ_Longway_PosleRasskaza":
			dialog.text = "Skoro już mowa o archiwum, Wielmożny Panie Kapitanie, masz je przy sobie? To wszystko, czego potrzebuję - znam szyfr na pamięć.";
			if (CheckCharacterItem(pchar, "MerdokArchive"))
			{
				notification("All Skills +", "Longway");
				AddCharacterExpToSkill(npchar, "Leadership", 50);
				AddCharacterExpToSkill(npchar, "FencingLight", 50);
				AddCharacterExpToSkill(npchar, "Fencing", 50);
				AddCharacterExpToSkill(npchar, "FencingHeavy", 50);
				AddCharacterExpToSkill(npchar, "Pistol", 50);
				AddCharacterExpToSkill(npchar, "Fortune", 50);
				AddCharacterExpToSkill(npchar, "Sneak", 50);
				AddCharacterExpToSkill(npchar, "Sailing", 50);
				AddCharacterExpToSkill(npchar, "Accuracy", 50);
				AddCharacterExpToSkill(npchar, "Cannons", 50);
				AddCharacterExpToSkill(npchar, "Grappling", 50);
				AddCharacterExpToSkill(npchar, "Defence", 50);
				AddCharacterExpToSkill(npchar, "Repair", 50);
				AddCharacterExpToSkill(npchar, "Commerce", 50);	
				
				link.l1 = "Tak, zatrzymałam to, myśląc, że może się kiedyś przydać.";
				link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_1";
			}
			else
			{
				link.l1 = "Niestety, nie.  Czy to była twoja ostatnia nadzieja na znalezienie siostry?";
				link.l1.go = "PZ_Longway_PosleRasskaza_2";
			}
		break;
		
		case "PZ_Longway_PosleRasskaza_2":
			dialog.text = "„Longway jest bardzo zadowolony, że Wielmożny Pan Kapitan się martwi. Na razie jest jeszcze nadzieja. Znalazłem nowy trop na Gwadelupie.”";
			link.l1 = "Dobrze, opowiedz mi, co ci się tam przydarzyło.";
			link.l1.go = "PZ_Longway_PosleRasskaza_3";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_1":
			dialog.text = "To była mądra decyzja. Być może znajdziemy tam coś, co pomoże nam w poszukiwaniach Chang Xing.";
			link.l1 = "Byłoby idealnie. Przestudiujmy to teraz.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_2";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_2":
			dialog.text = "Tak, zbadajmy to razem. Rok to... 1637. Antoon van Diemen sprzedał... sprzedał...";
			link.l1 = "Niewolnicy, prawda?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_3";
			AddQuestRecordInfo("PZ_ArchiveOneMerden", "1");
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_3":
			dialog.text = "Kobiety z mego ludu, sprzedane bogatym białym mężczyznom.";
			link.l1 = "To straszne.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_4";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_4":
			dialog.text = "Wielmożny Panie Kapitanie, nie wyglądasz na zaskoczonego. Czyżby los tych kobiet wcale Cię nie niepokoił?";
			link.l1 = "Longway, of course it sincerely troubles me. I've seen this filth from the inside. But I've always been an advocate for women... and a bit of a ladies' man, to be honest. It's good you killed van Diemen; he deserved it. Is there anything else?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_5";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_5":
			dialog.text = "Van Diemen współpracował tylko z tymi, którym całkowicie ufał - Joepem van der Vinkiem, jego prawą ręką, i tym przeklętym Oliveiro Fermentelosem. I... i...";
			link.l1 = "Co się stało? Zbladłeś, Longway.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_6";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_6":
			dialog.text = "Johan van Merden...";
			link.l1 = "Tak mi przykro. To straszne, ale dlaczego jesteś tak zszokowany? Wcześniej powiedziałeś, że wyrwałeś wszystkie strony wspominające Fermentelos. Czy wtedy nie znalazłeś wzmianki o van Merdenie?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_7";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_7":
			dialog.text = "„Longway się spieszył i musiał przeoczyć ten ważny fragment.”";
			link.l1 = "Widzę. Gdy będziesz gotowy, szukajmy dalej i znajdźmy wszystko, co możemy teraz wykorzystać.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_8";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_8":
			dialog.text = "Jest napisane, że Fermentelos wysyłał swoich ludzi, aby porywali kobiety, wymieniali je i niszczyli zapisy. Następnie Merden wysyłał je do Batawii, gdzie van der Vink i van Diemen sprzedawali nasze kobiety białym ludziom. Gdybym tylko dowiedział się tego wcześniej...";
			link.l1 = "„Więc na końcu wszyscy współpracowali. Nie obwiniaj się, Longway. Nie mogłeś tego wiedzieć. Archiwum trafiło do twoich rąk dopiero niedawno. Czy jest coś jeszcze?”";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_9";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_9":
			dialog.text = "Tak. Robią to już od prawie dziesięciu lat. Tyle kobiet straciło swoje rodziny, honor, nadzieję... Ale potem Fermentelos przestał współpracować z van Merdenem. To jedyny powód, dla którego mi pomógł - zawsze chciał tylko pozbyć się swojego byłego partnera.";
			link.l1 = "Jakie inne szczegóły ich plugawych czynów są tutaj zapisane?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_10";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_10":
			dialog.text = "Więcej mrocznych myśli van Merdena. Dowiedział się, że van Diemen go oszukuje na pieniądze. Więc wysłał mnie do Batawii, mając nadzieję, że tam zginę, ale również mając nadzieję, że zabiorę ze sobą van Diemena.";
			link.l1 = "Zimny. Ale również niesamowicie bystry.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_11";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_11":
			dialog.text = "Mogło być jeszcze gorzej. To van Merden wysłał tych łotrów do jego domu, żeby mnie zabić. Wtrącił się, żeby pomóc, dopiero gdy zorientował się, że mogę ich pokonać sama.";
			link.l1 = "Miał to wszystko przemyślane, bez wątpienia.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_12";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_12":
			dialog.text = "Po moim powrocie, musiał pomyśleć, że odkryłem jego prawdziwe zamiary i przybyłem po zemstę. Kiedy rozmawialiśmy, miał pistolet wycelowany pod stołem. Ale potem nazwałem go moim pierwszym białym przyjacielem... prawie pękł ze śmiechu...";
			link.l1 = "To okropne, Longway. To gorzkie uczucie zdać sobie sprawę, że ci, których uważaliśmy za przyjaciół, cały czas się z nas śmiali za naszymi plecami.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_13";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_13":
			dialog.text = "Longway nauczył się czegoś dawno temu, tuż przed przybyciem na to archipelag. Zostałem pojmany przez Portugalczyków i chcieli mnie powiesić. Pan Rodenburg uratował mi życie.";
			link.l1 = "Czy to w ten sposób wszedłeś na jego służbę? Lucas też był na Formosie?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_14";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_14":
			dialog.text = "„Tak, to prawda. I nie tylko on - Van Berg też. Van Merden powiedział mi, że to on poradził Rodenburgowi, by mnie oszczędził. Ale jakiś czas później Longway dowiedział się z podejrzanego źródła, że to właściwie Johan wysłał Portugalczyków za mną. Wtedy nie wierzyłam... ale teraz zdaję sobie sprawę, że to może być prawda...”";
			link.l1 = "Odrażający.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_15";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_15":
			dialog.text = "Jednakże, tamtego dnia w moim sercu zagościły wątpliwości. Zatem gdy dowiedziałem się, że Wielmożny Pan Kapitan i van Merden stanęli naprzeciw siebie, Longway pamiętał o twojej dobroci i opowiedział się po twojej stronie.";
			link.l1 = "„To była słuszna decyzja, Longway. Heh, okazuje się, że przez cały ten czas to ja byłem twoim pierwszym prawdziwym białym przyjacielem.”";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_16";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_16":
			dialog.text = "Tak się okazuje, Wielmożny Panie Kapitanie. Teraz rozumiem. Van Merden mówił, że jestem jego przyjacielem. Ale w rzeczywistości, Longway nie był dla niego niczym więcej niż kolejnym robotnikiem - po prostu bardziej użytecznym niż większość.\nTo wszystko. Inne strony dotyczą rachunkowości, a także szczegółów biznesowych między Van Bergiem a Rodenburgiem.";
			link.l1 = "Widzę. A teraz najwyższy czas, byś mi opowiedział, co robiłeś na Gwadelupie.";
			link.l1.go = "PZ_Longway_PosleRasskaza_3";
		break;
		
		case "PZ_Longway_PosleRasskaza_3":
			dialog.text = "Szukałem Gwiazdy Porannej. Jedna z wyrwanych stron archiwum mówiła, że ostatnio widziano ją w pobliżu St. Christopher's.";
			link.l1 = "Dlaczego tam? Umówiliśmy się na spotkanie na Gwadelupie, i tam cię znalazłem.";
			link.l1.go = "PZ_Longway_PosleRasskaza_4";
		break;
		
		case "PZ_Longway_PosleRasskaza_4":
			dialog.text = "Ponieważ St. Christopher's to dom Georges'a Gravela, jednego z informatorów van Merdena. Georges wierzy, że wciąż pracuję dla Johana. Co więcej, Gravel popełnił kiedyś poważne przestępstwo przeciwko van Merdenowi. A Longway pomógł to zatuszować.";
			link.l1 = "„A cóż to była za obraza?”";
			link.l1.go = "PZ_Longway_PosleRasskaza_5";
		break;
		
		case "PZ_Longway_PosleRasskaza_5":
			dialog.text = "To nie jest ważne. Ważne, że Georges był winien Longwayowi dług. Więc poszedłem do kościoła, gdzie Gravel pracuje jako asystent księdza. Czy Wielmożny Pan Kapitan jest gotów słuchać dalej? Wyglądasz na trochę rozkojarzonego.";
			link.l1 = "Przepraszam, rozproszyłam się. Tak, oczywiście, śmiało, Longway.";
			link.l1.go = "PZ_Longway_PosleRasskaza_6";
		break;
		
		case "PZ_Longway_PosleRasskaza_6":
			DialogExit();
			SetCurrentTime(9, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			SetMainCharacterIndex(GetCharacterIndex("Longway"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("Capsterville,"+ NewStr() +"St. Christopher Island.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Kapstervil", "patrol", "patrol12", "PZ_Kapstervil_Start");
			LaunchFrameForm();
		break;
		
		case "PZ_Zhorzh_1":
			dialog.text = "„Dobrze, że nie jesteś za późno. Nie chciałabym tu być dłużej, niż to konieczne, wiesz! Czego potrzebujesz tym razem, Longway?”";
			link.l1 = "Zmień ton, Gravel. Organizacja wymaga twoich usług.";
			link.l1.go = "PZ_Zhorzh_2";
		break;
		
		case "PZ_Zhorzh_2":
			dialog.text = "Muszę przyznać, że od dawna nie miałem od nich wieści. Czyżby o mnie zapomnieli?";
			link.l1 = "Mogę im przypomnieć. Może opowiadając Lordowi van Merden o tym, co zrobiłeś.";
			link.l1.go = "PZ_Zhorzh_3";
		break;
		
		case "PZ_Zhorzh_3":
			dialog.text = "W porządku, w porządku, nie ma potrzeby się tak złościć! Co mogę dla ciebie zrobić?";
			link.l1 = "Potrzebuję informacji o Gwiezdnej Jutrzenki. Cokolwiek znajdziesz. Im więcej, tym lepiej.";
			link.l1.go = "PZ_Zhorzh_4";
		break;
		
		case "PZ_Zhorzh_4":
			dialog.text = "Pewnie, ale to potrwa! Dwa dni! Co najmniej.";
			link.l1 = "Czemu tak długo?";
			link.l1.go = "PZ_Zhorzh_5";
		break;
		
		case "PZ_Zhorzh_5":
			dialog.text = "Zwykle biorę pieniądze z ofiarnej skrzynki, aby rozwiązać języki moich informatorów. Ale niedawno nas okradziono! Ojciec ogłosi nową zbiórkę darowizn oczywiście, ale wciąż musimy naprawić nasz dach - przecieka! To zajmie wiele darowizn, aby go naprawić.";
			link.l1 = "„Dwa dni. Nie mogę tu zostać na zawsze. Nie mam tyle czasu. Longway nie jest znany z cierpliwości. Lord van Merden tym bardziej. Czy mam ci o tym przypomnieć, Gravel?”";
			link.l1.go = "PZ_Zhorzh_6";
		break;
		
		case "PZ_Zhorzh_6":
			dialog.text = "Nie mogę kontrolować tego, co jest poza moim zasięgiem! Zrobię, co w mojej mocy. Chociaż, dowiedziałbym się znacznie szybciej, gdybyś znalazł tych łotrów i przyniósł nasze datki!";
			link.l1 = "Pomyślę o tym. Zacznij szukać. Dwa dni. Nie więcej. Spotkamy się w tym samym czasie i miejscu.";
			link.l1.go = "PZ_Zhorzh_7";
		break;
		
		case "PZ_Zhorzh_7":
			DialogExit(); 
			SetCurrentTime(12, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("A Day Later..."+ NewStr() +"In Search of the Church Robbers.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Kapstervil_Jungle", "goto", "goto1", "PZ_Kapstervil_Jungle");
			LaunchFrameForm();
		break;
		
		case "PZ_VorugaChurch_1":
			dialog.text = "„No proszę! Człowiek o wąskich oczach na naszej wyspie! Uciekasz od swoich panów, co? Przed kim się kryjesz, jeśli mogę zapytać?”";
			link.l1 = "Jestem wolnym człowiekiem.";
			link.l1.go = "PZ_VorugaChurch_2";
		break;
		
		case "PZ_VorugaChurch_2":
			dialog.text = "Ha! Na pewno tak jest. Ale wyglądasz na silnego i bystrego, nawet jeśli twoje oczy są trochę skośne. Chcesz dołączyć do naszej bandy? I tak nie sądzę, żebyś miał gdzie indziej pójść.";
			link.l1 = "„Longway myśli, że bardziej interesuje cię jego obrabowanie niż zwerbowanie.”";
			link.l1.go = "PZ_VorugaChurch_3";
		break;
		
		case "PZ_VorugaChurch_3":
			dialog.text = "Heh, uważaj się za szczęściarza. Niedawno okradliśmy kościół w mieście, możesz w to uwierzyć? Dlaczego? Bo kradzież od złodziei to nie naprawdę kradzież.";
			link.l1 = "Nie planowałem cię ścigać, ale cieszę się, że cię znalazłem.";
			link.l1.go = "PZ_VorugaChurch_4";
		break;
		
		case "PZ_VorugaChurch_4":
			dialog.text = "„Polujesz na nas? Aha, więc jesteś najemnikiem, a nie jakimś zbiegłym robotnikiem. Źle dla ciebie.”";
			link.l1 = "Dokładnie.";
			link.l1.go = "PZ_VorugaChurch_5";
		break;
		
		case "PZ_VorugaChurch_5":
			DialogExit();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			LAi_SetCheckMinHP(npchar, 1, true, "PZ_VorugaChurch_win");
			for (i=11; i<=14; i++)
			{
				sld = CharacterFromID("PZ_KapstervilBandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "PZ_VorugaChurch_6":
			if (!CharacterIsAlive("PZ_KapstervilBandit_11") && !CharacterIsAlive("PZ_KapstervilBandit_12") && !CharacterIsAlive("PZ_KapstervilBandit_13"))
			{
				dialog.text = "Cholera... Dlaczego mnie od razu nie zabiłeś? Czego ode mnie chcesz? Zamierzasz mnie zaciągnąć do więzienia?";
				link.l1 = "Nie interesuje mnie to. Po prostu powiedz mi, gdzie ukryłeś złoto.";
				link.l1.go = "PZ_VorugaChurch_7";
			}
			else
			{
				dialog.text = RandSwear()+"";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_VorugaChurch_win");	
			}
		break;
		
		case "PZ_VorugaChurch_7":
			dialog.text = "Heh... Ty żółtoskóry draniu...";
			link.l1 = "Cierpliwość Longwaya się kończy. I tak się dowiem. Pytanie tylko, jak długo będziesz cierpieć.";
			link.l1.go = "PZ_VorugaChurch_8";
			LAi_group_Delete("EnemyFight");
		break;
		
		case "PZ_VorugaChurch_8":
			dialog.text = "Dobrze, tak, co nie... Jest w jaskini. Wszystko tam jest. Pieniądze są twoje. Tylko... tylko mnie nie zabijaj, dobrze?";
			link.l1 = "Nie powiedziałem, że wcale nie będzie cierpienia...";
			link.l1.go = "PZ_VorugaChurch_9";
		break;
		
		case "PZ_VorugaChurch_9":
			DialogExit();
			
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Shot", "1", 1.5);
			DoQuestCheckDelay("PZ_VorugaChurch_win_2", 0.9);
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_0":
			StartQuestMovie(true, false, true);
			locCameraFromToPos(2.48, 0.87, 9.26, true, 6.72, -0.85, 6.05);
			dialog.text = "„(w mandaryńskim) Oto kryjówka bandytów.”";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_0_1";
			CharacterTurnToLoc(pchar, "box", "box1");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_0_1":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto2", "PZ_Kapstervil_Grot_1", -1);
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_1":
			dialog.text = "„(po mandaryńsku) To dużo!”";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_1_1";
			CharacterTurnToLoc(pchar, "box", "box1");
			locCameraFromToPos(6.83, 2.65, 6.62, true, 2.83, -1.00, 7.67);
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_1_1":
			dialog.text = "Słyszę kroki...";
			link.l1 = "„(po mandaryńsku) Jest tu ktoś jeszcze...”";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_2";
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_2":
			DialogExit();
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Kapstervil_GrotSoldier_1", "sold_fra_7", "man", "man", 5, FRANCE, -1, true, "soldier"));
			LAi_SetActorType(sld);
			sld.CantLoot = true;
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
			TeleportCharacterToPosAy(sld, 4.17, 0.65, -1.42, 0.00);
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Kapstervil_GrotSoldier_2", "sold_fra_5", "man", "man", 5, FRANCE, -1, true, "soldier"));
			LAi_SetActorType(sld);
			sld.CantLoot = true;
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
			TeleportCharacterToPosAy(sld, 4.10, 0.65, 0.30, 3.00);
			
			LAi_SetStayType(pchar);
			LAi_Fade("PZ_Kapstervil_Grot_2", "");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_3":
			dialog.text = "Co, do diabła, robimy tutaj? Nie ma tu już nikogo - upewniliśmy się, że wszyscy rabusie zniknęli.";
			link.l1 = "";
			link.l1.go = "exit";
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_Kapstervil_GrotSoldier_2"));
			AddDialogExitQuest("PZ_Kapstervil_Grot_4");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_5":
			dialog.text = "Na tym polega rzecz, idioto! Wrócą, a my przywitamy ich gorąco.";
			link.l1 = "";
			link.l1.go = "exit";
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_Kapstervil_GrotSoldier_1"));
			AddDialogExitQuest("PZ_Kapstervil_Grot_5");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_7":
			dialog.text = "Rozejrzę się tutaj i upewnię się, że nikt się nie ukrywa. I tak się nudzę...";
			link.l1 = " ";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_8";
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_Kapstervil_GrotSoldier_2"));
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_8":
			DialogExit();
			LAi_Fade("PZ_Kapstervil_Grot_5_1", "");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_9":
			dialog.text = "„(po mandaryńsku) Żołnierze! Co za nieszczęście... Co ja mam teraz zrobić?”";
			link.l1 = "„(w mandaryńskim) Potrzebuję tych pieniędzy bardziej niż biali żołnierze! Nie odejdę bez nich!”";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_10";
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_10":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("PZ_Kapstervil_GrotSoldier_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyWithRadius");
				LAi_group_SetRelation("EnemyWithRadius", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_SetLookRadius("EnemyWithRadius", 6.0);
				LAi_group_SetHearRadius("EnemyWithRadius", 2.0);
				LAi_group_SetSayRadius("EnemyWithRadius", 12.0);
				LAi_group_SetCheck("EnemyWithRadius", "PZ_Kapstervil_Grot_6");
			}
		break;
		
		case "PZ_Zhorzh_11":
			dialog.text = "Ach, monsieur Longway, wróciłeś!";
			link.l1 = "Oczywiście. Czy były jakieś wątpliwości? Dowiedziałeś się czegoś o Gwiazda Poranna, Georges?";
			link.l1.go = "PZ_Zhorzh_12";
		break;
		
		case "PZ_Zhorzh_12":
			dialog.text = "Tak, monsieur. To ciężki galeon, dowodzony przez Hiszpana, albo tak mówią...";
			link.l1 = "„On jest Portugalczykiem. Wy, biali, nawet nie potraficie odróżnić siebie nawzajem.”";
			link.l1.go = "PZ_Zhorzh_13";
		break;
		
		case "PZ_Zhorzh_13":
			dialog.text = "Och, racja. Mój błąd. W każdym razie, dowiedziałam się, że mocno zmodyfikował galeon, próbując udawać, że to statek handlowy, z działami małego kalibru i mniejszą załogą. Ale powiększył ładownię, wypełniając ją po brzegi - jest tak ciężki, że ledwo płynie.";
			link.l1 = "Więc postanowił zacząć nowe życie. Dobrze. A gdzie mogę go teraz znaleźć?";
			link.l1.go = "PZ_Zhorzh_14";
		break;
		
		case "PZ_Zhorzh_14":
			dialog.text = "To bardziej skomplikowane. Ciągle przemieszcza się między naszymi koloniami a angielskimi, ale tylko między Wyspami Nawietrznymi. Jednak dowiedziałem się, że obecnie jest w drodze do Basse-Terre z dużym ładunkiem wina.";
			link.l1 = "Muszę wymyślić, jak się tam szybko dostać.";
			link.l1.go = "PZ_Zhorzh_15";
		break;
		
		case "PZ_Zhorzh_15":
			dialog.text = "To twoja sprawa, monsieur Longway. Mam wystarczająco własnych problemów... jak naprawa tego przeklętego dachu.";
			link.l1 = "Mówiąc o zmartwieniach, znalazłem tych złodziei kościelnych. Oto twoje pieniądze z darowizny. Naprawcie dach - nie jest dobrze, aby wasz Bóg był bez dachu.";
			link.l1.go = "PZ_Zhorzh_16";
		break;
		
		case "PZ_Zhorzh_16":
			dialog.text = "Dziękuję ci bardzo, monsieur Longway! Nigdy bym nie pomyślała, że to ty to zrobisz.";
			link.l1 = "Też tak nie myślałem. Ale musiałem coś zrobić z tymi dwoma dniami.";
			link.l1.go = "PZ_Zhorzh_17";
		break;
		
		case "PZ_Zhorzh_17":
			dialog.text = "Więc, musisz dostać się na Gwadelupę? Znajdę dla ciebie statek w tamtą stronę. Spodziewaj się wkrótce wiadomości ode mnie!";
			link.l1 = "To byłoby pomocne. Dziękuję, Georges.";
			link.l1.go = "PZ_Zhorzh_18";
		break;
		
		case "PZ_Zhorzh_18":
			DialogExit();
			SetCurrentTime(9, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("The Next Morning..."+ NewStr() +"Capsterville", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Kapstervil", "goto", "goto19", "PZ_Kapstervil_PoiskZvezda");
			LaunchFrameForm();
		break;
		
		case "PZ_Kapstervil_Kurier_1":
			dialog.text = "Musisz być znajomym Georgesa? Poprosił mnie, abym ci to przekazał.";
			link.l1 = "Notatka? Moja wdzięczność. Skąd wiedziałeś, że to dla mnie?";
			link.l1.go = "PZ_Kapstervil_Kurier_2";
		break;
		
		case "PZ_Kapstervil_Kurier_2":
			dialog.text = "Serio?";
			link.l1 = "Ach, racja.";
			link.l1.go = "PZ_Kapstervil_Kurier_3";
		break;
		
		case "PZ_Kapstervil_Kurier_3":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("PZ_Kapstervil_ChitaemPismo", 1.5);
		break;
		
		case "PZ_Kapstervil_ChitaemPismo_Dialog":
			dialog.text = "(Czyta list) Monsieur Longway, pinasa „Provence” wypływa do Basse-Terre jutro rano. Kapitana, Mathieu Terugny, można znaleźć w tawernie. Przekaż moje pozdrowienia monsieur van Merdenowi. - Georges Gravel.";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_ChitaemPismo_Dialog_2";
		break;
		
		case "PZ_Kapstervil_ChitaemPismo_Dialog_2":
			DialogExit();
			LAi_RemoveCheckMinHP(pchar);
			chrDisableReloadToLocation = false;
			LAi_SetPlayerType(pchar);
			sld = characterFromId("PZ_Kapstervil_tavernkeeper");
			sld.dialog.currentnode = "PZ_TerunyiTavern1";
			LAi_SetBarmanType(sld);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "PZ_TerunyiTavern1":
			dialog.text = "Nie obsługujemy tutaj takich jak ty. A jeśli nie chcę słyszeć skarg na pchły, to i pokoju ci też nie wynajmę.";
			link.l1 = "Nie potrzebuję ani drinka, ani pokoju. I... Longway nie ma pcheł.";
			link.l1.go = "PZ_TerunyiTavern2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_TerunyiTavern2":
			dialog.text = "Skąd do diabła mam to wiedzieć? Dobra, wypluj to z siebie. Czego chcesz? A potem wynoś się.";
			link.l1 = "Zrobię to. Szukam kapitana Mathieu Terugny. Nie mogę go znaleźć. Wiesz, gdzie on jest?";
			link.l1.go = "PZ_TerunyiTavern3";
		break;
		
		case "PZ_TerunyiTavern3":
			dialog.text = "On jest zajęty przygotowywaniem swojego statku do wypłynięcia w lokalnym sklepie. To o wiele ważniejsze niż pogawędka z takim Chińczykiem jak ty, ale ty tego najwyraźniej nie rozumiesz.";
			link.l1 = "Właściwie, kiedyś byłem... Nieważne. Teraz to nieistotne.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_CreateTerunyi");
		break;
		
		case "PZ_Terunyi1":
			dialog.text = " Czego chcesz, Chińczyku? Nie widzisz, że jestem zajęty? Muszę przygotować mój statek.";
			link.l1 = "Kapitan Mathieu Terugny?";
			link.l1.go = "PZ_Terunyi2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Terunyi2":
			dialog.text = "„Cóż, to przestało być śmieszne. Skąd ktoś taki jak ty wie, kim jestem? Czy ktoś cię przysłał?”";
			link.l1 = "Nie ma potrzeby się martwić. Słyszałem, że płyniesz do Basse-Terre. Czy możesz mnie zabrać jako pasażera? Zapłacę.";
			link.l1.go = "PZ_Terunyi3";
		break;
		
		case "PZ_Terunyi3":
			dialog.text = "To się robi coraz lepsze. Zmierzam do St. Pierre, nie do Basse-Terre, ale to krótki objazd. To dobrze, bo nie będę musiał trzymać cię na statku dłużej niż to konieczne. Pięć tysięcy peso. Wyruszamy za trzy godziny. Zapłać na molo. Mimo że jestem kupcem, nie ma targowania. Zrozumiano?";
			link.l1 = "Tak. Dziękuję. Do zobaczenia na molo, Kapitanie Terugny.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TeleportToPier");
		break;
		
		case "PZ_Terunyi4":
			dialog.text = "„Jednak się pojawiłeś, żółtku. Myślałem, że nie dasz rady - nikt nigdy nie daje prawdziwych pieniędzy twojemu rodzajowi dobrowolnie.”";
			link.l1 = "Pięć tysięcy pesos, tak jak prosiłeś. Jesteś gotów do wypłynięcia?";
			link.l1.go = "PZ_Terunyi5";
		break;
		
		case "PZ_Terunyi5":
			AddMoneyToCharacter(pchar, -5000);
			
			dialog.text = "Nie, nie! To ja powinienem cię o to pytać. Ale rozumiem, że jesteś gotowy. Chodź. Ty będziesz wiosłować w łodzi. I nie oczekuj porządnej kajuty! Jesteś jedynym powodem, dla którego robimy ten objazd.";
			link.l1 = "Nie potrzebuję pocieszenia. Po prostu mnie tam zabierz.";
			link.l1.go = "PZ_Terunyi6";
		break;
		
		case "PZ_Terunyi6":
			DialogExit();
			
			SetCurrentTime(2, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			InterfaceStates.Buttons.Save.enable = true;
			
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			
			QuestToSeaLogin_Launch();
			QuestToSeaLogin_PrepareLoc("Guadeloupe", "Quest_Ships", "Quest_ship_8", false);
			DoQuestCheckDelay("PZ_Flashback_Final_1", 3.5);
		break;
		
		case "PZ_Longway_PosleRasskaza21":
			dialog.text = "...więc Longway nie mógł dokładnie ustalić, dokąd zmierza Poranna Gwiazda.";
			link.l1 = "Tak, widzę, jak wpakowałeś się w to całe bagno.";
			link.l1.go = "PZ_Longway_PosleRasskaza22";
		break;
		
		case "PZ_Longway_PosleRasskaza22":
			if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena")) sStr = "Helena";
			else sStr = "Alonso";
			dialog.text = "Widziałem bryg w wodach Gwadelupy. Może to był Banten. Spróbuję się dowiedzieć. Cóż, możesz już iść, Longway. Przynieś mi "+sStr+".";
			link.l1.go = "PZ_Longway_PosleRasskaza23";
		break;
		
		case "PZ_Longway_PosleRasskaza23":
			DialogExit();
			LAi_SetStayType(pchar);
			LAi_FadeLong("PZ_LongwayUhoditIzKauty", "PZ_HelenaOrAlonso");
		break;
		
		case "PZ_Helena_1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "Mój kapitanie, czy wszystko w porządku? Przybyłam, gdy tylko Longway powiedział, że mnie potrzebujesz.";
				link.l1 = "„Próbuję tylko wszystko poskładać. Czy pamiętasz nazwę tego brygu, który widzieliśmy przy wyspie?”";
				link.l1.go = "PZ_Helena_3";
			}
			else
			{
				dialog.text = "„Chciałeś mnie widzieć?”";
				link.l1 = "„Aye. Czy pamiętasz brygantynę, którą niedawno widzieliśmy? Dowiedz się, gdzie się znajduje i jak się nazywa.”";
				link.l1.go = "PZ_Helena_2";
			}
		break;
		
		case "PZ_Helena_2":
			dialog.text = "Pamiętam, ale skąd to nagłe zainteresowanie brygiem? Dowiedzenie się tego może zająć trochę czasu.";
			link.l1 = "Helen, po prostu zrób to, proszę. I tak, wiem, że to może zająć trochę czasu. Będę czekać.";
			link.l1.go = "PZ_PoiskBanten";
		break;
		
		case "PZ_Helena_3":
			dialog.text = "Nie, nie sprawdziłam. Dlaczego? To ważne?";
			link.l1 = "Mm-hmm. Czy możesz dowiedzieć się więcej? Muszę wiedzieć, gdzie teraz są zakotwiczeni, jeśli już nie opuścili wód Gwadelupy.";
			link.l1.go = "PZ_Helena_4";
		break;
		
		case "PZ_Helena_4":
			dialog.text = "Jak najbardziej. Tylko ostrzegam, to może trochę potrwać. Wezmę szalupę i kilku ludzi do pomocy, tak, co nie, Charles?";
			link.l1 = "Oczywiście, Helen, dziękuję. Będę czekał.";
			link.l1.go = "PZ_PoiskBanten";
		break;
		
		case "PZ_Alonso_11":
			dialog.text = "Wielmożny Panie Kapitanie, wołałeś?";
			link.l1 = "Tak, Alonso. Minęliśmy brygantynę na wodach przy wyspie, kiedy wracaliśmy po Longwaya. Czy udało ci się złapać jej nazwę?";
			link.l1.go = "PZ_Alonso_12";
		break;
		
		case "PZ_Alonso_12":
			dialog.text = "„Nie, moim zadaniem jest pilnowanie nowych rekrutów i udział w awangardzie abordażu. Poza tym, nie posiadam lunety, a nie byliśmy aż tak blisko.”";
			link.l1 = "Prawda. Ale muszę się dowiedzieć mimo wszystko. Załatw to.";
			link.l1.go = "PZ_Alonso_13";
		break;
		
		case "PZ_Alonso_13":
			dialog.text = "Tak jest, Kapitanie. Myślę, że mogę to zrobić w pół dnia.";
			link.l1 = "Pospiesz się. Będę czekać.";
			link.l1.go = "PZ_PoiskBanten";
		break;
		
		case "PZ_PoiskBanten":
			DialogExit();
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			LAi_SetStayType(pchar);
			SetLaunchFrameFormParam("Five hours later...", "PZ_PoiskBanten_2", 0, 4.0);
			LaunchFrameForm();
			locCameraSleep(true);
		break;
		
		case "PZ_Helena_5":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "Dowiedziałam się wszystkiego. Czy wszystko było w porządku, gdy mnie nie było, mój kapitanie?";
				link.l1 = "Tak, wszystko w porządku, dziękuję, Helen. Powiedz mi.";
				link.l1.go = "PZ_Helena_7";
			}
			else
			{
				dialog.text = "Uff, wróciłam. Znalazłam twój bryg.";
				link.l1 = "Witaj z powrotem. Gdzie ona jest i jak się nazywa?";
				link.l1.go = "PZ_Helena_6";
			}
		break;
		
		case "PZ_Helena_6":
			dialog.text = "„Banten. Ta nazwa coś ci mówi, prawda? Jest teraz przy latarni, a kilku członków jej załogi wyszło na ląd. Czy zaatakujemy ten statek?”";
			link.l1 = "Nie, musimy dokładnie ustalić, kto zszedł na ląd. Udajemy się do latarni od strony lądu. Biorąc pod uwagę, że już się opóźniliśmy, najwyższy czas opuścić port. Powinniśmy zakotwiczyć w jakimś odległym miejscu. Plaża Capster byłaby dobra. Pośpieszmy się, Helen.";
			link.l1.go = "PZ_BasTerMayak";
		break;
		
		case "PZ_Helena_7":
			dialog.text = "Cóż, bryg nazywa się Banten i jest zakotwiczony przy latarni morskiej. Część załogi wylądowała tam. Co zamierzasz zrobić?";
			link.l1 = "Żeby się dowiedzieć, musimy dotrzeć do latarni morskiej niezauważeni, a możemy to zrobić tylko pieszo. Nasz statek musi zakotwiczyć w bezpiecznym miejscu. Co powiesz na Plażę Capster?";
			link.l1.go = "PZ_Helena_8";
		break;
		
		case "PZ_Helena_8":
			dialog.text = "Dobry pomysł. Charles, chcesz, żebym poszła z tobą do latarni?";
			link.l1 = "Zastanowię się nad tym, podczas gdy przemieścimy statek - i tak jesteś już wystarczająco zmęczony.";
			link.l1.go = "PZ_BasTerMayak";
		break;
		
		case "PZ_Alonso_15":
			dialog.text = "Wracam, gdy tylko skończyłem, Señor Kapitanie.";
			link.l1 = "Bardzo dobrze. Zdaj raport, Alonso.";
			link.l1.go = "PZ_Alonso_16";
		break;
		
		case "PZ_Alonso_16":
			dialog.text = "Bryg wciąż jest przy wyspie - dokładnie przy latarni morskiej. Nazwa na rufie to Banten. Kilku z ich załogi zeszło na ląd.";
			link.l1 = "Dobra robota, Alonso. Przygotuj załogę do natychmiastowego podniesienia kotwicy.";
			link.l1.go = "PZ_Alonso_17";
		break;
		
		case "PZ_Alonso_17":
			dialog.text = "Przygotować się do abordażu, też?";
			link.l1 = "„Jeszcze nie. Jeśli ich kapitan zmierza do latarni, może ukryć się w mieście, jeśli zaatakujemy na morzu. Udajemy się na Plażę Capster, aby zabezpieczyć nasz statek, a potem podejdziemy do latarni pieszo.”";
			link.l1.go = "PZ_BasTerMayak";
		break;
		
		case "PZ_BasTerMayak":
			DialogExit();
			locCameraSleep(false);
			LAi_SetPlayerType(pchar);
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			chrDisableReloadToLocation = false;
			bDisableCharacterMenu = false;
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			Island_SetReloadEnableGlobal("Guadeloupe", true);
			
			AddQuestRecord("PZ", "15");
			PChar.quest.PZ_Banten_PlyazhKapster.win_condition.l1 = "location";
			PChar.quest.PZ_Banten_PlyazhKapster.win_condition.l1.location = "Shore29";
			PChar.quest.PZ_Banten_PlyazhKapster.win_condition = "PZ_Banten_PlyazhKapster";
			
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1 = "Timer";
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.hour = sti(GetTime() + 7);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition = "PZ_Banten_PlyazhKapster_Proval";
			
			if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
			{
				LAi_SetActorType(npchar);
				LAi_ActorFollow(npchar, pchar, "", -1);
				LAi_SetOfficerType(npchar);
				npchar.Dialog.Filename = "Quest\Saga\Helena.c";
				npchar.Dialog.CurrentNode = "Helena_officer";
			}
		break;
		
		case "PZ_Longway_21":
			dialog.text = "Wielmożny Panie Kapitanie, patrz! Ktoś jest w środku latarni.";
			link.l1 = "Dobrze, jesteśmy na czas! Pośpieszmy się i złapmy ich. Alonso będzie miał dziś dużo pracy.";
			link.l1.go = "PZ_Longway_22";
		break;
		
		case "PZ_Longway_22":
			dialog.text = "A co, jeśli umrą w trakcie?";
			link.l1 = "Co sugerujesz?";
			link.l1.go = "PZ_Longway_23";
		break;
		
		case "PZ_Longway_23":
			dialog.text = "„Zakradniemy się po cichu i najpierw podsłuchamy ich rozmowę.”";
			link.l1 = "Wątpię, czy uda nam się to zrobić, nie będąc widzianymi z okna. Ale spróbujmy.";
			link.l1.go = "PZ_Longway_24";
		break;
		
		case "PZ_Longway_24":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			npchar.Dialog.CurrentNode = "Longway_officer";
			LAi_SetCheckMinHP(npchar, 1, true, "SkritoeBessmertie");
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1 = "locator";
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1.location = "Mayak4";
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1.locator_group = "goto";
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1.locator = "goto31";
			PChar.quest.PZ_MayakPodslushivanie.win_condition = "PZ_MayakPodslushivanie";
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_1":
			dialog.text = "Pomyśl o tym, co powiedziałem. Pomyśl dobrze. Pieniądze nie stanowią problemu - w pewnych granicach, oczywiście. Ale nawet ten limit wyda się wam górą złota - Chińczyk musi umrzeć! Wcześniej wysyłałem za nim ludzi, ale bezskutecznie. Tym razem jednak, jeśli połączą siły z twoimi ludźmi...";
			link.l1 = "";
			link.l1.go = "PZ_MayakPodslushivanie_Dialog_1_1";
			CharacterTurnByChr(npchar, CharacterFromID("PZ_BasTerJailOff_Clone"));
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_1_1":
			StartInstantDialog("PZ_BasTerJailOff_Clone", "PZ_MayakPodslushivanie_Dialog_2", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_2":
			dialog.text = "Spójrz, jesteśmy obserwowani! To on! On i jego przeklęty kapitan!";
			link.l1 = "";
			link.l1.go = "PZ_MayakPodslushivanie_Dialog_3";
			CharacterTurnToLoc(npchar, "item", "flower5");
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_3":
			DialogExit();
			EndQuestMovie();
			locCameraSleep(false);
			locCameraToPos(1.52, 18.87, -9.55, true);
			DoQuestCheckDelay("CameraReset", 1.0);
			DeleteAttribute(pchar, "questTemp.NoFast");
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("PZ_Neznakomets");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			
			sld = CharacterFromID("PZ_BasTerJailOff_Clone");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetCheckMinHP(sld, 1, true, "PZ_MayakPodslushivanie_win");
			
			for (i=1; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_Neznakomets_Bandit_"+i, "citiz_" + (rand(9) + 41), "man", "man", sti(pchar.rank), PIRATE, -1, true, "pirate"));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "PZ_Mayak_KomendantSidit_1":
			if (!CharacterIsAlive("PZ_Neznakomets_Bandit_1") && !CharacterIsAlive("PZ_Neznakomets_Bandit_2") && !CharacterIsAlive("PZ_Neznakomets_Bandit_3")&& !CharacterIsAlive("PZ_Neznakomets_Bandit_4"))
			{
				dialog.text = "Cholera, ty parszywy Azjato... Musiałem znieść tak wiele przez ciebie. A teraz, za to wszystko, mam umrzeć...";
				link.l1 = "Zaprowadzimy cię do naszego medyka, Wielmożny Panie Komendancie. Po prostu powiedz nam, z kim rozmawiałeś - to bardzo ważne.";
				link.l1.go = "PZ_Mayak_KomendantSidit_2";
				LAi_group_Delete("EnemyFight");
			}
			else
			{
				dialog.text = RandSwear()+"";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_MayakPodslushivanie_win");	
			}
		break;
		
		case "PZ_Mayak_KomendantSidit_2":
			dialog.text = "Jego imię... to Joep van der Vink, on... kha...";
			link.l1 = "... to nie jest miejsce dla takiego jak ja, myślałem, że życie na morzu będzie inne.";
			link.l1.go = "PZ_Mayak_KomendantSidit_3";
		break;
		
		case "PZ_Mayak_KomendantSidit_3":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			DoQuestCheckDelay("PZ_Mayak_Longway", 1.5);
		break;
		
		case "PZ_Longway_25":
			dialog.text = "";
			link.l1 = "Nie żyje... Cóż, przynajmniej znamy imię. Longway...?";
			link.l1.go = "PZ_Longway_26";
		break;
		
		case "PZ_Longway_26":
			dialog.text = "To absolutnie nie może być...";
			link.l1 = "Wyglądasz trochę blado, Longway.";
			link.l1.go = "PZ_Longway_27";
		break;
		
		case "PZ_Longway_27":
			dialog.text = "Longway był całkiem pewny, że zabił van der Vinka dziesięć lat temu\nUciekają! Ich statek jest szybki!";
			link.l1 = "Tak, wspaniała brygantyna... niestety dla nas. Nawet jeśli dotrzemy do naszego statku na czas, znikną, zanim podniesiemy żagle i złapiemy wiatr.";
			link.l1.go = "PZ_Longway_28";
		break;
		
		case "PZ_Longway_28":
			dialog.text = "To może być koniec...";
			link.l1 = "Nie, Longway. Posłuchaj mnie. Jeśli planują zostać na Archipelagu, prędzej czy później na nich trafimy - świat jest mały, a Karaiby szczególnie. Gdy tylko znów natrafimy na ich ślad, rzucę wszystko i pójdę za nimi. Obiecuję ci to. Słyszysz mnie?";
			link.l1.go = "PZ_Longway_29";
		break;
		
		case "PZ_Longway_29":
			dialog.text = "Tak, Wielmożny Panie Kapitanie. Dziękuję.";
			link.l1 = "Trzymaj głowę wysoko, Longway. Musimy się spieszyć z powrotem na statek - śmierć Komendanta wkrótce będzie wielką nowiną.";
			link.l1.go = "PZ_Longway_30";
		break;
		
		case "PZ_Longway_30":
			DialogExit();
			
			Return_LongwayOfficer();
			LAi_RemoveCheckMinHP(npchar);
			AddQuestRecord("PZ", "17");
			sld = &Locations[FindLocation("Mayak4")];
			sld.locators_radius.goto.goto31 = 0.5;
			
			chrDisableReloadToLocation = false;
			QuestOpenSeaExit();
			
			pchar.questTemp.PZ_Etap4_Start = true;
		break;
		
		// Этап 4, Обманчивая Звезда
		case "PZ_PoterpKrushenie_1":
			dialog.text = "Monsieur! Chwila! Czy jesteś kapitanem?";
			link.l1 = "Może. Jak zgadłeś? A czego chcesz?";
			link.l1.go = "PZ_PoterpKrushenie_2";
		break;
		
		case "PZ_PoterpKrushenie_2":
			dialog.text = "Cóż, wokół są tylko góry i gęsta dżungla - żadnych dróg do miasta. A jednak tu jesteś. Nie jesteś tu tylko na wycieczce, prawda?";
			link.l1 = "Dobre spostrzeżenie. Ale nadal mi nie powiedziałeś, czego chcesz.";
			link.l1.go = "PZ_PoterpKrushenie_3";
		break;
		
		case "PZ_PoterpKrushenie_3":
			dialog.text = "Ach, racja! Kapitanie, nasz statek uderzył o skały tuż przy tej zatoce. Jesteśmy jedynymi, którzy to przeżyli...";
			link.l1 = "Przepraszam. Chcesz, żebym cię gdzieś zabrał, prawda?";
			link.l1.go = "PZ_PoterpKrushenie_4";
		break;
		
		case "PZ_PoterpKrushenie_4":
			dialog.text = "Tak... Nie sprawimy żadnych kłopotów, przysięgam. Po prostu wysadź nas w Belize, a dalej sobie poradzimy.";
			link.l1 = "To niedaleko, prawda? W takim razie, witaj na pokładzie.";
			link.l1.go = "PZ_PoterpKrushenie_5";
			link.l2 = "Przykro mi, ale idę w drugą stronę.";
			link.l2.go = "PZ_PoterpKrushenie_7";
		break;
		
		case "PZ_PoterpKrushenie_5":
			dialog.text = "Dziękuję, Kapitanie! Kto wie, jak długo byśmy tu utknęli bez Ciebie.";
			link.l1 = "Rzeczywiście. Nie traćmy czasu!";
			link.l1.go = "PZ_PoterpKrushenie_6";
		break;
		
		case "PZ_PoterpKrushenie_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			DeleteAttribute(&locations[FindLocation("Shore9")], "DisableEncounters");
			
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("PZ_PoterpKrushenie_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "sea", "", "", "", "", -1);
				sld.location = "None";
			}
			
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1 = "location";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1.location = "Beliz_town";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition = "PZ_Beliz_PoterpKrushenie";
			AddMapQuestMarkCity("Beliz", false);
			
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			
			SetTimerCondition("PZ_BelizFail", 0, 0, 30, false);
		break;
		
		case "PZ_PoterpKrushenie_7":
			dialog.text = "Ale Belize jest tak blisko! To nie zajmie dużo czasu, z pewnością?";
			link.l1 = "Spieszę się. Nie mogę sobie pozwolić na żadne objazdy.";
			link.l1.go = "PZ_PoterpKrushenie_8";
		break;
		
		case "PZ_PoterpKrushenie_8":
			dialog.text = "Choćby krótka? Tylko do Belize? Proszę, Kapitanie, nie zostawiaj nas na lodzie!";
			link.l1 = "Dobrze, mam nadzieję, że tego nie pożałuję. Wszyscy na pokład!";
			link.l1.go = "PZ_PoterpKrushenie_6";
			link.l2 = "„C'est la vie. Miłego dnia, moi przyjaciele.”";
			link.l2.go = "PZ_PoterpKrushenie_9";
		break;
		
		case "PZ_PoterpKrushenie_9":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			DeleteAttribute(&locations[FindLocation("Shore9")], "DisableEncounters");
			
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("PZ_PoterpKrushenie_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "", "", "", "", 10);
				sld.location = "None";
			}
			
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1 = "location";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1.location = "Beliz_town";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition = "PZ_Beliz_QuestCitizenDialog";
			
			AddMapQuestMarkCity("Beliz", false);
			
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddCharacterExpToSkill(pchar, "FencingL", 20);
			AddCharacterExpToSkill(pchar, "FencingS", 20);
			AddCharacterExpToSkill(pchar, "FencingH", 20);
			AddCharacterExpToSkill(pchar, "Pistol", 20);
			
			pchar.questTemp.PZ.Shipwreckers.Decline = true;
			
			SetTimerCondition("PZ_BelizFail", 0, 0, 30, false);
		break;
		
		case "PZ_PoterpKrushenie_11":
			dialog.text = "Dzięki jeszcze raz, Kapitanie! Jesteśmy tylko prostymi żeglarzami, więc nie mamy zbyt wiele do zaoferowania.";
			link.l1 = "Cóż, przynajmniej nie musieliśmy zbytnio zbaczać z drogi.";
			link.l1.go = "PZ_PoterpKrushenie_12";
		break;
		
		case "PZ_PoterpKrushenie_12":
			dialog.text = "Wznieśmy kielich za twe zdrowie i zapalmy świecę za ciebie w kościele.";
			link.l1 = "To lepsze niż nic. Na zdrowie, chłopcy!";
			link.l1.go = "PZ_PoterpKrushenie_13";
		break;
		
		case "PZ_PoterpKrushenie_13":
			DialogExit();
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("PZ_PoterpKrushenie_"+i);
				LAi_SetCitizenType(sld);
				LAi_CharacterDisableDialog(sld);
				sld.lifeday = 0;
				sld.location = "None";
			}
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_BelizZhitelNovosti", "citiz_4", "man", "man", 1, ENGLAND, 0, false, "quest"));
			ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto5");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_BelizZhitelNovosti_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "PZ_BelizZhitelNovosti_1":
			dialog.text = "Słyszałeś? W końcu go złapali! Nasze wody są wreszcie bezpieczne!";
			link.l1 = "To... dobre wieści? Ale kogo złapali?";
			link.l1.go = "PZ_BelizZhitelNovosti_2";
			DeleteQuestCondition("PZ_BelizFail");
		break;
		
		case "PZ_BelizZhitelNovosti_2":
			dialog.text = "Matthew Lutter, gaduła we własnej osobie!";
			link.l1 = "Nie znam - co on zrobił?";
			link.l1.go = "PZ_BelizZhitelNovosti_3";
		break;
		
		case "PZ_BelizZhitelNovosti_3":
			dialog.text = "Nie wiesz?! No cóż, wyraźnie nie jesteś Anglikiem, to widać. To pirat, który od lat plądruje nas i Hiszpanów na swoim statku, Mewa.";
			link.l1 = "Grabić zarówno Anglików, jak i Hiszpanów? To niecodzienne.";
			link.l1.go = "PZ_BelizZhitelNovosti_4";
		break;
		
		case "PZ_BelizZhitelNovosti_4":
			dialog.text = "Rzeczywiście. Straż przybrzeżna nigdy nie mogła go złapać, ale w końcu porwał się z motyką na słońce - przegrał z jakimś dziwnym statkiem kupieckim, jeśli można w to uwierzyć.";
			link.l1 = "To zabawne. Co było tak dziwnego w tym kupcu?";
			link.l1.go = "PZ_BelizZhitelNovosti_5";
		break;
		
		case "PZ_BelizZhitelNovosti_5":
			dialog.text = "„Cóż, to był tylko jeden ogromny, niezdarny galeon bez eskorty! Ale dzięki jej szalonemu kapitanowi, Lutter zaśpiewa dziś swoją ostatnią pieśń - wkrótce zostanie powieszony. Powinieneś to zobaczyć!”";
			link.l1 = "Może tak, ale na razie mam inne sprawy do załatwienia.";
			link.l1.go = "PZ_BelizZhitelNovosti_6";
		break;
		
		case "PZ_BelizZhitelNovosti_6":
			DialogExit();
			
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			
			sld = CharacterFromID("Longway");
			if (!CharacterIsHere("Longway"))
			{
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"));
			}
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Longway_31";
		break;
		
		case "PZ_Longway_31":
			dialog.text = "Wielmożny Panie Kapitanie!";
			link.l1 = "Hiszpański kupiec pokonujący zuchwałego pirata... Myślisz to, co myśli Longway, prawda?";
			link.l1.go = "PZ_Longway_32";
		break;
		
		case "PZ_Longway_32":
			dialog.text = "Gwiazda Poranna...";
			link.l1 = "Najprawdopodobniej - nie ma drugiego takiego kapitana handlowego w całym archipelagu.";
			link.l1.go = "PZ_Longway_33";
		break;
		
		case "PZ_Longway_33":
			dialog.text = "Musimy go natychmiast znaleźć!";
			link.l1 = "Racja. Ale nie widzę w porcie żadnego ciężkiego galeonu. Spróbujmy porozmawiać z Gadułą, zanim go powieszą. Zobaczymy, czy zasłużył na ten przydomek.";
			link.l1.go = "PZ_Longway_34";
		break;
		
		case "PZ_Longway_34":
			DialogExit();
			Return_LongwayOfficer();
			if (!CheckAttribute(pchar, "questTemp.PZ.Shipwreckers.Decline")) AddQuestRecord("PZ", "18");
			else AddQuestRecord("PZ", "18_1");
			pchar.questTemp.PZ_Beliz_Komendant = true;
			AddLandQuestMarkToPhantom("beliz_prison", "belizJailOff");
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
		break;
		
		case "PZ_Beliz_Komendant_8":
			dialog.text = "Czy on wciąż żyje? Czy możemy z nim porozmawiać?";
			link.l1 = "";
			link.l1.go = "PZ_Beliz_Komendant_9";
			CharacterTurnByChr(npchar, CharacterFromID("BelizJailOff"));
		break;
		
		case "PZ_Beliz_Komendant_9":
			StartInstantDialogNoType("BelizJailOff", "PZ_Beliz_Komendant_10", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Beliz_Komendant_10":
			dialog.text = "Co? Och, tak. On żyje - egzekucja jeszcze się nie odbyła. Możesz z nim porozmawiać - jest bardziej rozmowny niż kiedykolwiek. Ale ostatnio plecie bzdury, głównie rozmawia sam ze sobą. Gaduła oszalał... Nie mogę się doczekać, aż go powiesimy, zanim wszyscy oszalejemy od jego niekończących się gadek.";
			link.l1 = "";
			link.l1.go = "PZ_Beliz_Komendant_11";
		break;
		
		case "PZ_Beliz_Komendant_11":
			StartInstantDialog("Longway", "PZ_Beliz_Komendant_12", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Beliz_Komendant_12":
			dialog.text = "Dziękuję.";
			link.l1 = "";
			link.l1.go = "PZ_Beliz_Komendant_13";
			CharacterTurnByChr(npchar, CharacterFromID("BelizJailOff"));
		break;
		
		case "PZ_Beliz_Komendant_13":
			DialogExit();
			pchar.questTemp.jailCanMove = true;
			
			Return_LongwayOfficer();
			
			sld = CharacterFromID("BelizJailOff");
			LAi_SetHuberType(sld);
			sld.Dialog.Filename = "Common_Prison.c";
			sld.Dialog.CurrentNode = "First_officer";
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_MatthewLutter", "mercen_15", "man", "man", 1, ENGLAND, -1, false, "quest"));
			sld.name = "Matthew";
			sld.lastname = "Lutter";
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_MatthewLutter1";
			ChangeCharacterAddressGroup(sld, "Beliz_prison", "goto", "goto9");
			LAi_SetStayType(sld);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "PZ_MatthewLutter1":
			dialog.text = "On ukradł mój skarb!";
			link.l1 = "Matthew Lutter?";
			link.l1.go = "PZ_MatthewLutter2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_MatthewLutter2":
			dialog.text = "Mój skarb jest teraz związany z nim, wiesz, Z NIM! Nic nie możemy zrobić! Czego chcesz?! Chcesz zabrać nam coś jeszcze? Nic już nie zostało! Ona umrze! Albo gorzej!";
			link.l1 = "Kto ma umrzeć? Jaki skarb? Nieważne, to twoja własna wina - to ty zaatakowałeś ten galeon, a nie odwrotnie.";
			link.l1.go = "PZ_MatthewLutter3";
		break;
		
		case "PZ_MatthewLutter3":
			dialog.text = "Nie! Było odwrotnie! Do diabła z tym hidalgo! To przez niego wpadliśmy w to bagno! Podszedł do nas i strzelił z bliska! Potem nam ją zabrał!";
			link.l1 = "Naprawdę? To nie zaskakuje. Co jeszcze możesz nam o nim powiedzieć? I... co zabrał? Kim jest 'ona'?";
			link.l1.go = "PZ_MatthewLutter5";
		break;
		
		case "PZ_MatthewLutter5":
			dialog.text = "Ah-ah-ah!!! A-A-A-A!!!";
			link.l1 = "Rozumiem, tracę czas...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_BelizPrisonSoldierDialog");
		break;
		
		case "PZ_BelizPrisonQuestSoldier1":
			dialog.text = "Kapitánie, za pozwoleniem... Lutter! Precz! Koniec trasy, koleś.";
			link.l1 = "";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_BelizPrisonLongway_UvodyatNaKazn");
		break;
		
		case "PZ_Longway_35":
			dialog.text = "„Kapitanie, musimy dowiedzieć się więcej o Sotcie i Lutterze. Zapytajmy wokół.”";
			link.l1 = "Dobry pomysł, Longway. I tak nie dowiedzieliśmy się wiele od tego krzyczącego człowieka.";
			link.l1.go = "PZ_Longway_36";
		break;
		
		case "PZ_Longway_36":
			dialog.text = "Ale lepiej zacząć od Sotty.";
			link.l1 = "„Tak, to jego szukamy. Chodźmy.”";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_BelizPrisonLongwayBack");
		break;
		
		case "PZ_Longway_37":
			dialog.text = "Oni nic nie wiedzą!";
			link.l1 = "Oczywiście. Ale mamy wystarczająco, by zacząć myśleć samodzielnie. Z tego, co słyszałem, Sotta prawdopodobnie spróbuje sprzedać te strategiczne towary, które otrzymał w nagrodę, i to wkrótce.";
			link.l1.go = "PZ_Longway_38";
		break;
		
		case "PZ_Longway_38":
			dialog.text = "Dokładnie!";
			link.l1 = "Powinniśmy go przechwycić w drodze do Port Royal lub Capsterville. Jedynym pytaniem jest, dokąd zmierza i gdzie powinniśmy go zaatakować. A może złapiemy go na otwartym morzu.";
			link.l1.go = "PZ_Longway_39";
		break;
		
		case "PZ_Longway_39":
			dialog.text = "Nie! Longway myślał... Fermentelos to doświadczony kapitan. Walka na otwartym morzu mogłaby się potoczyć różnie. Mielibyśmy lepsze szanse, gdybyśmy zasadzili się na niego w porcie.";
			link.l1 = "Masz rację, przypuszczam. Niezależnie od tego, co naprawdę wydarzyło się między Mattem a nim, Sotta jest niebezpieczny i nie można go lekceważyć.";
			link.l1.go = "PZ_Longway_40";
		break;
		
		case "PZ_Longway_40":
			dialog.text = "Też nie możemy się doczekać!";
			link.l1 = "„Zgadza się, Longway. Zatem podnieśmy kotwicę natychmiast, a potem zaplanujemy nasz kolejny ruch.”";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LongwayBelizDialogBack");
			DelMapQuestMarkCity("Beliz");
		break;
		
		case "PZ_Longway_41":
			dialog.text = "Wielmożny Panie Kapitanie, Gwiazda Poranna jest w porcie!";
			link.l1 = "Tak, już zauważyłem.";
			link.l1.go = "PZ_Longway_42";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Longway_42":
			dialog.text = "Jaki masz plan?";
			link.l1 = "Jeszcze nie zdecydowałem. Próba abordażu pod działami fortu byłaby samobójstwem. A nawet jeśli zdobędziemy ich ciężki galeon, nie ucieknijmy na nim. Masz jakieś pomysły, Wielmożny Panie Kapitanie?";
			link.l1.go = "PZ_Longway_43";
		break;
		
		case "PZ_Longway_43":
			dialog.text = "Tak. Moglibyśmy zakotwiczyć przy bezpiecznej zatoce i podejść do galeonu łodzią pod osłoną nocy.";
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Kapstervil"))
			{
				link.l1 = "A co z Half Moon Bay, Longway?";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Yamaika"))
			{
				link.l1 = "Myślę, że Portland Cove byłoby dobrym wyborem - wystarczająco blisko i stosunkowo bezpieczne. Co o tym sądzisz?";
			}
			link.l1.go = "PZ_Longway_44";
		break;
		
		case "PZ_Longway_44":
			dialog.text = "Dobry wybór.";
			link.l1 = "Świetnie, to załatwione. Czy coś przeoczyliśmy?";
			link.l1.go = "PZ_Longway_45";
		break;
		
		case "PZ_Longway_45":
			dialog.text = "„Nie sądzę, Wielmożny Panie Kapitanie. Musimy być tylko dobrze przygotowani.”";
			link.l1 = "Absolutnie.";
			link.l1.go = "PZ_Longway_46";
		break;
		
		case "PZ_Longway_46":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.CabinLock");
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			bQuestDisableMapEnter = false;
			AddQuestRecord("PZ", "21");
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Kapstervil"))
			{
				AddQuestUserData("PZ", "sText", "Half Moon Bay");
				Island_SetReloadEnableGlobal("Nevis", true);
				
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1 = "location";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1.location = "Shore43";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition = "PZ_GotovimShlupki_Buhta";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Yamaika"))
			{
				AddQuestUserData("PZ", "sText", "Portland Cove");
				Island_SetReloadEnableGlobal("Jamaica", true);
				
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1 = "location";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1.location = "Shore36";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition = "PZ_GotovimShlupki_Buhta";
			}
			PChar.quest.PZ_ZvezdaUhodimNaGlobalkru_Proval.win_condition.l1 = "MapEnter";
			PChar.quest.PZ_ZvezdaUhodimNaGlobalkru_Proval.win_condition = "PZ_ZvezdaUhodimNaGlobalkru_Proval";
			
			sld = CharacterFromID("Longway");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.Dialog.CurrentNode = "Longway_officer";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan":
			dialog.text = "Kim do cholery jesteś, co się dzieje? Panie Holmes!";
			link.l1 = "Panie Holmes nie pracuje już tutaj. I uszczelniliśmy wszystkie włazy. Więc nie będziemy niepokojeni przez jakiś czas, Mynheer Fermentelos.";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_2";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_2":
			dialog.text = "Co? Fermentelos? Nazywam się Edgardo Sotta!";
			link.l1 = "Uh-huh, słyszałam to już wcześniej. Wiemy, że to nie jest twoje prawdziwe imię, Oliveiro.";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_3";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_3":
			dialog.text = "Fermentelos nie żyje!";
			link.l1 = "Po namyśle, rzeczywiście wyglądasz zbyt młodo. Oczywiście, nie mogłeś być kapitanem Gwiazdy Porannej dziesięć lat temu. Więc, co się stało z Oliveiro?";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_4";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_4":
			dialog.text = "Pozbyliśmy się go. Był tylko kolejnym problemem, który musieliśmy rozwiązać - tak jak ten stojący obok ciebie.";
			link.l1 = "„Cóż, skoro nie jesteś Fermentelosem, może jednak odpowiesz na nasze pytania. Szukamy kogoś, kogo zabrał od mojego przyjaciela.”";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_5";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_5":
			dialog.text = "Nie powiem ci niczego! Nigdy mi tego nie wybaczy.";
			link.l1 = "W tej chwili lepiej martw się, czy ci wybaczymy...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_SottaFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PZ_AnabelleLutter1":
			dialog.text = "W końcu nie żyje...";
			link.l1 = "That's right. And who are you, madam? Did he hold you against your will? I sympathize; you must have been through a terrible ordeal...";
			link.l1.go = "PZ_AnabelleLutter2";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_AnabelleLutter2":
			dialog.text = "Jestem Annabel Lutter. Dzięki Bogu, nie musiałam znieść zbyt wiele, ale doceniam twoją troskę, panie...?";
			link.l1 = "Kapitán Charles de Maure. Lutter, mówisz...";
			link.l1.go = "PZ_AnabelleLutter3";
		break;
		
		case "PZ_AnabelleLutter3":
			dialog.text = "Ach, musiałeś słyszeć o Macie? Biedny głupiec... Byłam jego... towarzyszką.";
			link.l1 = "Przykro mi z powodu twojej straty, pani Lutter. Teraz jesteś wdową. Jakie było pani nazwisko panieńskie, jeśli to nie tajemnica?";
			link.l1.go = "PZ_AnabelleLutter4";
		break;
		
		case "PZ_AnabelleLutter4":
			dialog.text = "Nie miałem żadnego. Spójrz na mnie uważniej. Moja biedna matka była ciemnoskórą niewolnicą piratów. Nikt nie wie, kim był mój ojciec, więc nie zawracali sobie głowy nadawaniem mi odpowiedniego imienia.";
			link.l1 = "Dlaczego nikt cię wtedy nie tknął? Nie zrozum mnie źle - cieszę się, że tak się nie stało. Ale mimo to, to... niezwykłe.";
			link.l1.go = "PZ_AnabelleLutter5";
		break;
		
		case "PZ_AnabelleLutter5":
			dialog.text = "You're right. But let's call things by their proper names. I'm not a pampered noblewoman; I'm the daughter of a slave. I won't faint from a heavy conversation.";
			link.l1 = "„Ahem, nie jestem też skory do rozpieszczania. Ale mów dalej, proszę. Dlaczego załoga nie tknęła córki niewolnicy? Nie znasz swego ojca, a on zdawał się nie przejmować.”";
			link.l1.go = "PZ_AnabelleLutter6";
		break;
		
		case "PZ_AnabelleLutter6":
			dialog.text = "Przypuszczam, że nie. Skoro wiesz o Mattcie, to czy wiesz, że pracował dla Levasseura przez jakiś czas?";
			link.l1 = "Tak, słyszałam o tym, gdy szukałam Porannej Gwiazdy. Ale co to ma z tym wspólnego? Opowiedz mi wszystko, proszę.";
			link.l1.go = "PZ_AnabelleLutter7";
		break;
		
		case "PZ_AnabelleLutter7":
			dialog.text = "Ty nadal nie rozumiesz, prawda? Najwidoczniej nie słyszałeś o... upodobaniach Levasseura?";
			link.l1 = "„Nie, ale z drugiej strony, co to ma wspólnego z...?”";
			link.l1.go = "PZ_AnabelleLutter8";
		break;
		
		case "PZ_AnabelleLutter8":
			dialog.text = "„Och, chyba będę musiała opowiedzieć ci o wszystkim. Usiądź, jeśli jesteś zbyt wrażliwy, panie. Rzecz w tym, że sypia z wieloma kobietami, i...”";
			if (pchar.questTemp.FMQT == "end")
			{
				link.l1 = "Jego żona nie jest daleko od niego, i sypia prawie z każdym.";
				link.l1.go = "PZ_AnabelleLutterKnow1";
			}
			else
			{
				link.l1 = "O nie.";
				link.l1.go = "PZ_AnabelleLutterDontKnow1";
			}
		break;
		
		case "PZ_AnabelleLutterKnow1":
			dialog.text = "„No cóż, jak mówią... jaki mąż, taka żona. Ale nie, jestem pewna, że on posunął się znacznie dalej.”";
			link.l1 = "I jak daleko?";
			link.l1.go = "PZ_AnabelleLutter9";
		break;
		
		case "PZ_AnabelleLutterDontKnow1":
			dialog.text = "Twój sarkazm jest tu nie na miejscu, panie. Nie masz pojęcia, o czym rozmawiamy.";
			link.l1 = "Dobrze, dobrze, przepraszam. Kontynuuj, proszę.";
			link.l1.go = "PZ_AnabelleLutter9";
		break;
		
		case "PZ_AnabelleLutter9":
			dialog.text = "To nie tylko zdradzanie małżonka. On zabiera kobiety wbrew ich woli. I to nie jest jednorazowe nadużycie. Porywa dziewczęta i trzyma je w jednej z piwnic, które posiada.";
			link.l1 = "„Czy on regularnie sprowadza sobie niewolnice? A ty miałaś być jedną z nich?”";
			link.l1.go = "PZ_AnabelleLutter10";
		break;
		
		case "PZ_AnabelleLutter10":
			dialog.text = "Masz rację co do tego drugiego. Ale, niestety, nie co do pierwszego. On nie potrzebuje niewolników. Levasseur jest szalony - na swój sposób, nie jak mój Matt. Francois chce całkowicie posiadać kobietę, ciało i duszę. I to oczywiście nie chodziło o miłość. Potrzebował wolnych kobiet, aby złamać ich wolę. Czerpał przyjemność z obserwowania, jak zmieniały się ich wygląd, zachowanie i sposób mówienia z czasem...";
			link.l1 = "Obrzydliwe...";
			link.l1.go = "PZ_AnabelleLutter11";
		break;
		
		case "PZ_AnabelleLutter11":
			dialog.text = "Już czujesz się trochę chory. Teraz wyobraź sobie, jak było tym kobietom. Słyszałem o tym wszystkim, i to nie tylko od Matta. Levasseur miał kiedyś portugalską szlachciankę...";
			link.l1 = "Odwróciłeś wzrok i milczałeś. Powiedz nam wszystko. Widziałem już najróżniejsze rzeczy w Starym Świecie i podczas pobytu w Archipelagu też. Nic mnie już nie zaskakuje.";
			link.l1.go = "PZ_AnabelleLutterWant1";
			link.l2 = "Przestań, nie chcę wiedzieć, co się z nią stało. Mam nadzieję, że te kobiety nie cierpiały zbyt długo w jego rękach.";
			link.l2.go = "PZ_AnabelleLutter12";
		break;
		
		case "PZ_AnabelleLutterWant1":
			dialog.text = "Ale nigdy o czymś takim nie słyszałeś. I mam nadzieję, że nigdy tego nie zobaczysz. Została do niego przywieziona wciąż dumna i nieugięta, chociaż, jak powiedział mi Matt, ludzie Levasseura gwałcili ją całą drogę do Tortugi po przejęciu plantacji jej męża koło Campeche - zmarł z powodu krwotoku po tym, jak te potwory postrzeliły go w oba kolana...";
			link.l1 = "Silna kobieta... Ale powiedziałeś, że Levasseur zwykle nie dotykał kobiet, które chciał dla siebie.";
			link.l1.go = "PZ_AnabelleLutterWant2";
		break;
		
		case "PZ_AnabelleLutterWant2":
			dialog.text = "Ci, o których prosił, zostali pozostawieni w spokoju. Ale Senora Leontina była prezentem. Niespodziewanym i przyjemnym dla nich wszystkich. Więc sobie dogadzali...";
			link.l1 = "Widzę...";
			link.l1.go = "PZ_AnabelleLutterWant3";
		break;
		
		case "PZ_AnabelleLutterWant3":
			dialog.text = "Chyba... Matt stał się jednym z ulubieńców Françoisa. Został zaproszony na jedną z tajnych uczt Lévasseura... Podczas uczty jeden z piratów narzekał, że brakuje kobiet. Lévasseur zaśmiał się, a potem...";
			link.l1 = "A potem? Co się stało?";
			link.l1.go = "PZ_AnabelleLutterWant4";
		break;
		
		case "PZ_AnabelleLutterWant4":
			dialog.text = "...potem ją wyprowadzono. Na smyczy! Pobitą, z porysowanymi plecami, z zasłoniętymi oczami i kneblem w ustach. Gdy usunęli knebel, wszystko, co powiedziała, to...";
			link.l1 = "Coś okropnego, wyobrażam sobie. Czy przeklęła go z całych sił?";
			link.l1.go = "PZ_AnabelleLutterWant5";
		break;
		
		case "PZ_AnabelleLutterWant5":
			dialog.text = "Gdyby tylko... Dona Leontina szepnęła po prostu: 'Czego życzy sobie mój pan?'";
			link.l1 = "Chyba zaraz zwymiotuję. Czy Matt opowiedział ci, co się z nią stało potem?";
			link.l1.go = "PZ_AnabelleLutterWant6";
		break;
		
		case "PZ_AnabelleLutterWant6":
			dialog.text = "Zamordowana, oczywiście. Ale nie z ręki Levasseura. Porzucił ją jak bezpańskiego psa. Jeden z jego kapitanów ją zastrzelił. Zanim umarła, wypowiedziała tylko jedno słowo...";
			link.l1 = "„Klątwa? Modlitwa?”";
			link.l1.go = "PZ_AnabelleLutterWant7";
		break;
		
		case "PZ_AnabelleLutterWant7":
			dialog.text = "Nie. 'Dziękuję...'";
			link.l1 = "Być wdzięcznym za śmierć po takich mękach... Co ona musiała wytrzymać... i inni jak ona w legowisku tego potwora...";
			link.l1.go = "PZ_AnabelleLutter12";
		break;
		
		case "PZ_AnabelleLutter12":
			dialog.text = "Levasseur szczególnie pogardzał niewolnikami i kobietami o ciemnej karnacji - twierdził, że nie ma w nich nic do złamania. Nie trwały przy nim długo, podobnie jak Indianie - z wyjątkiem kilku szczególnie upartych. Lecz dzikość i bunt również nie były odpowiedzią - zabijał tych, którzy próbowali mu się przypodobać zbyt szybko, i tych, którzy pozostali nieugięci zbyt długo.";
			link.l1 = "To przerażające... Powiedz mi, czy Levasseur miał kiedykolwiek kobiety z Azji?";
			link.l1.go = "PZ_AnabelleLutter13";
		break;
		
		case "PZ_AnabelleLutter13":
			dialog.text = "Nie, przynajmniej nic mi o tym nie wiadomo. Co do mnie... Już ci mówiłam, że on nie lubił kobiet o ciemnej skórze. Tak więc, gdy Matt pracował dla Francoisa, chodził ze mną otwarcie po ulicach Tortugi. Nawet raz zabrał mnie do rezydencji.";
			link.l1 = "Ale Levasseur i tak chciał uczynić cię jednym ze swoich niewolników...";
			link.l1.go = "PZ_AnabelleLutter14";
		break;
		
		case "PZ_AnabelleLutter14":
			dialog.text = "„Dokładnie... Nie wiem, dlaczego tak bardzo mnie lubił... Kiedy Matt się dowiedział, uciekł z wyspy, jak tylko mu powiedziano. Nigdy nie wrócił na Tortugę. Może był trochę szalony, ale mnie kochał. Nazywał mnie swoim skarbem...”";
			link.l1 = "Więc to miał na myśli, kiedy powiedział, że Sotta zabrał mu jego skarb!";
			link.l1.go = "PZ_AnabelleLutter15";
		break;
		
		case "PZ_AnabelleLutter15":
			dialog.text = "Heh, naprawdę to powiedział? Och, Matt... Ale wygląda na to, że nigdy nie mieliśmy się razem zestarzeć. Jeśli Levasseur postawił sobie za cel kobietę, zrobiłby wszystko, aby ją zdobyć, niezależnie od jej pochodzenia czy kosztów. Sotta był jednym z jego kapitanów i robił to, co mu kazano.";
			link.l1 = "Rozumiem. A co teraz zamierzasz zrobić, Annabel?";
			link.l1.go = "PZ_AnabelleLutter16";
		break;
		
		case "PZ_AnabelleLutter16":
			dialog.text = "Uciekaj. Gdzieś, gdzie ludzie Levasseura mnie nie dosięgną. Zmienić imię. Przebrać się...";
			link.l1 = " Mam nadzieję, że ci się uda. Życzę ci wszystkiego najlepszego, Annabel.";
			link.l1.go = "PZ_AnabelleLutter17";
			if (sti(pchar.Money) >= 10000)
			{
				link.l2 = "Potrzebujesz pieniędzy, by zorganizować przejazd. Weź to. Jest tu dziesięć tysięcy pesos.";
				link.l2.go = "PZ_AnabelleLutter17_Peso";
			}
			if (PCharDublonsTotal() >= 100)
			{
				link.l3 = "Potrzebujesz więcej niż tylko trochę pieniędzy. Nie każdy jest gotów pomóc dziewczynie o ciemnej skórze, nawet jeśli jest mieszańcem. Weź tu sto dublonów - znajdź statek i ukryj się.";
				link.l3.go = "PZ_AnabelleLutter17_Dublon";
			}
		break;
		
		case "PZ_AnabelleLutter17":
			dialog.text = "I ty również! Żegnaj, Kapitanie.";
			link.l1 = "Żegnaj.";
			link.l1.go = "Exit";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddDialogExitQuest("PZ_AnabelleGo");
		break;
		
		case "PZ_AnabelleLutter17_Peso":
			dialog.text = "Ja... Ja nie wiem, co powiedzieć. Nikt poza Mattem nie okazał mi takiej dobroci.";
			link.l1 = "Może to znak. Że w końcu zestarzejesz się szczęśliwie gdzieś. Żegnaj.";
			link.l1.go = "Exit";
			AddMoneyToCharacter(pchar, -10000);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddDialogExitQuest("PZ_AnabelleGo");
		break;
		
		case "PZ_AnabelleLutter17_Dublon":
			dialog.text = "Masz rację. Bardzo ci za to dziękuję. Będę cię wspominał w swoich modlitwach do końca życia.";
			link.l1 = "Dziękuję. Pomyślnych wiatrów.";
			link.l1.go = "Exit";
			RemoveDublonsFromPCharTotal(100);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			AddDialogExitQuest("PZ_AnabelleGo");
		break;
		
		case "PZ_Longway_47":
			dialog.text = "Ten człowiek... Nie, on już nie jest człowiekiem. To bestia. Potwór. Torturuje kobiety w taki sposób...";
			link.l1 = "Wiem, o czym myślisz, Longway. Ale słyszałeś - nigdy nie miał kobiet o żółtej skórze.";
			link.l1.go = "PZ_Longway_48";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Longway_48":
			dialog.text = "Ale on znał całą grupę! Van der Vink, Fermentelos, Sotta... Właśnie o tym czytaliśmy w jego dzienniku. A co, jeśli ta konkretna 'ona' to... ona?";
			link.l1 = "Kto wie... Kobieta żądna zemsty na Fermentelosie - łatwo zrozumieć, dlaczego tak myślisz. Ale to mogła być każda kobieta, której życie zniszczył Oliveiro. To nie musi być twoja siostra. To nawet nie musi być kobieta o żółtej skórze.";
			link.l1.go = "PZ_Longway_49";
		break;
		
		case "PZ_Longway_49":
			dialog.text = "Odmawiasz... spróbowania tego, Wielmożny Panie Kapitanie? W ostatniej chwili...?";
			link.l1 = "Nie, Longway. Ale jak to sobie wyobrażasz? Mało prawdopodobne, że Levasseur odpowie na któreś z naszych pytań. A węszenie po Tortudze w ten sposób jest zbyt niebezpieczne.";
			link.l1.go = "PZ_Longway_50";
		break;
		
		case "PZ_Longway_50":
			dialog.text = "Więc co sugerujesz?";
			link.l1 = "Poczekajmy. Wiemy, że Levasseur nie lubi kobiet takich jak twoja siostra. Więc możemy na razie oszczędzać nasze zasoby. Cierpliwość i siła. Francois to twardy orzech do zgryzienia, nie tylko ze względu na jego 'żółwia'. Ale z pomocą Svensona możemy porozmawiać z nim na naszych warunkach. Obiecałem ci, że pomogę znaleźć twoją siostrę i zamierzam dotrzymać słowa. Wierzysz mi, Longway?";
			link.l1.go = "PZ_Longway_51";
		break;
		
		case "PZ_Longway_51":
			dialog.text = "„Hmm... Aye aye, Wielmożny Panie Kapitanie. Ale Longway ma jeszcze jedną prośbę do ciebie.”";
			link.l1 = "Co się dzieje? Nie zamierzasz znowu wybrać się sam, prawda? Ostatnim razem nie skończyło się to zbyt dobrze.";
			link.l1.go = "PZ_Longway_52";
		break;
		
		case "PZ_Longway_52":
			dialog.text = "„Wcale nie, Wielmożny Panie Kapitanie. Teraz zdaję sobie sprawę, że niestety, człowiek taki jak ja nie może nic zrobić samodzielnie w świecie rządzonym przez białych ludzi. Longway prosi cię, abyś zacumował w Capsterville i dostarczył notatkę do Georges Gravel, prosząc go, by dowiedział się czegokolwiek, podczas gdy ty przygotowujesz się.”";
			link.l1 = "Rozsądny pomysł, Longway. Tak zrobimy.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TeleportToShore");
		break;
		
		case "PZ_Longway_53":
			dialog.text = "Wielmożny Panie Kapitanie, Longway ma coś do zapytania...";
			link.l1 = "Zapomniałeś napisać list? Możesz po prostu porozmawiać z Gravel.";
			link.l1.go = "PZ_Longway_54";
		break;
		
		case "PZ_Longway_54":
			dialog.text = "Nie, list jest gotowy. Ale Longway uznał, że lepiej nie kręcić się samemu po mieście. Wielmożny Panie Kapitanie... mógłbyś dostarczyć list do Georgesa w moim imieniu? Proszę?";
			link.l1 = "„Czy wyglądam jak kurier? Czy to ty jesteś tutaj kapitanem?”";
			link.l1.go = "PZ_Longway_55";
		break;
		
		case "PZ_Longway_55":
			dialog.text = "Wielmożny Panie Kapitanie...";
			link.l1 = "Ha ha ha, tylko żartuję, Longway! Przypomnij mi, gdzie znaleźć tego twojego Gravel?";
			link.l1.go = "PZ_Longway_56";
		break;
		
		case "PZ_Longway_56":
			dialog.text = "„Pracuje w kościele.”";
			link.l1 = "Dobrze, zajmę się tym.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_ToCapstervilleChurch");
			AddLandQuestMark(characterFromId("Charles_Priest"), "questmarkmain");
		break;
		
		// Этап 5
		case "PZ_Mary_Sharptown1":
			dialog.text = "Charles, mój drogi Charles, coś się stało? Wyglądasz na zmartwionego i... zmęczonego, tak, co nie?";
			link.l1 = "O, nie, nie, Mary, wszystko w porządku. To tylko... ten mój quest na Tortudze. Znów wydaje się być ślepym zaułkiem... I ta wola Sharpa zdecydowanie mnie wyczerpała, na miłość boską. Ale nieważne.";
			link.l1.go = "PZ_Mary_Sharptown2";
		break;
		
		case "PZ_Mary_Sharptown2":
			dialog.text = "Co? Jaka misja? I co to ma wspólnego z Sharpem? Niczego nie rozumiem!";
			link.l1 = "Za dużo pytań, Mary. To nie jest miejsce na takie rozmowy. Czy omówimy to w pokoju karczmy? Tak, jak lubisz, z dala od oczu i myśli. Opowiem ci, co robiłem przez ostatni rok.";
			link.l1.go = "PZ_Mary_Sharptown3";
		break;
		
		case "PZ_Mary_Sharptown3":
			dialog.text = "Dobrze! Ale bądź ostrzeżony: jeśli coś ukrywasz...";
			link.l1 = "Absolutnie nie! Chodźmy, mamy czas do zabicia i tak...";
			link.l1.go = "PZ_HelenaMary_Exit";
		break;
		
		case "PZ_Helena_Sharptown1":
			dialog.text = "Jakie to dziwne, prawda, Charles? Powinienem być właścicielem tej wyspy, ale wcale tego nie czuję.";
			link.l1 = "Myślisz?";
			link.l1.go = "PZ_Helena_Sharptown2";
		break;
		
		case "PZ_Helena_Sharptown2":
			dialog.text = "„Och, ten twój uśmiech... Umiesz traktować dziewczynę. Ale co z tobą nie tak? Twoja twarz wygląda dziwnie!”";
			link.l1 = "„Dlaczego? To moja zwykła twarz, bardzo przystojna zresztą.”";
			link.l1.go = "PZ_Helena_Sharptown3";
		break;
		
		case "PZ_Helena_Sharptown3":
			dialog.text = "Charles, słyszę to w twoim głosie - ostatnio jesteś przygnębiony.";
			link.l1 = "Mam dużo na głowie, zwłaszcza z Longwayem. Jestem po prostu wykończona. Ale jest za późno, by się poddać, zwłaszcza że złożyłam obietnicę jemu i mojemu ojcu.";
			link.l1.go = "PZ_Helena_Sharptown4";
		break;
		
		case "PZ_Helena_Sharptown4":
			dialog.text = "Nie rozumiem... Co ma z tym wspólnego Longway? I jakie obietnice złożyłeś?";
			link.l1 = "Jeśli mamy o tym rozmawiać, zróbmy to w tawernie, wynajmijmy pokój. Z dala od innych ludzi.";
			link.l1.go = "PZ_Helena_Sharptown5";
		break;
		
		case "PZ_Helena_Sharptown5":
			dialog.text = "Dobrze, chodźmy. I tak nie ma nic innego do roboty, więc przynajmniej możemy spędzić trochę czasu razem.";
			link.l1 = "Prowadź, kochanie!";
			link.l1.go = "PZ_HelenaMary_Exit";
		break;
		
		case "PZ_HelenaMary_Exit":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) Return_MaryOfficer();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) Return_HelenaOfficer();
			WaitDate("", 0, 0, 0, 2, 0);
			LAi_SetImmortal(npchar, true);
			ChangeCharacterAddressGroup(npchar, "Pirates_tavern_upstairs", "goto", "goto1");
			DoQuestReloadToLocation("Pirates_tavern_upstairs", "goto", "goto2", "PZ_Etap5_NaverhuTavernBandits");
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Spójrz, jak słodko śpią w swoich ramionach! Urocze!";
				link.l1 = "Zazdrosny?";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Wstawać i lśnić! Jak się spało, gołąbeczki?";
				link.l1 = "Dobrze, dzięki za pytanie. A jak wam się spało, chłopcy?";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_2";
			locCameraFromToPos(2.34, 1.92, 1.66, true, -1.66, -0.69, -0.02);
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "To głupie pytanie, nie sądzisz?";
				link.l1 = "Tak jest. I głupia rzecz z twojej strony. Chcesz wiedzieć dlaczego?";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Mówią, że masz cięty język, Charles de Maure.";
				link.l1 = "„I nie tylko mój język. Chcesz się przekonać? Ale powiedz mi, dlaczego nie zaatakowałeś, gdy spaliśmy?”";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_3";
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "A dlaczego tak jest?";
				link.l1 = "Nie powinieneś denerwować Mary rano. Wkrótce się dowiesz, dlaczego.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Proste! Jest ciemno, wiesz, więc nie mogliśmy powiedzieć, która z was była dziewczyną.";
				link.l1 = "Sukinsyn.";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_4";
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "W przeciwieństwie do ciebie, ja się kobiet nie boję. A skoro o tym mowa - chłopcy, zabierzcie ją całą i zdrową, bo inaczej ten hugenot zrobi z nas kobiety!";
				link.l1 = "Hu... kto?";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Przynajmniej wyglądam jak mężczyzna. Chłopcy, weźcie blondynkę żywcem - Hugenot na nią czeka.";
				link.l1 = "Hu... kto?";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_5";
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_5":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("PZ_NaverhuTavernBandits_"+i);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				
				LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
				LAi_group_SetCheck("EnemyFight", "PZ_Etap5_NaverhuTavernBandits_Win");
			}
		break;
		
		case "PZ_MaryHelena_BitvaNaverhu_1":
			DelLandQuestMark(npchar);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Kto to był, Charles? Kim, do diabła, jest ten hugenot? Czy to naprawdę...?";
				link.l1 = "Jest tylko jedna, Mary. Lepiej byśmy...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Charles... co to było? Hugenota? Czy to jest człowiek, o którym myślę?";
				link.l1 = "Obawiam się, że tak, Helen. Musimy...";
			}
			link.l1.go = "PZ_MaryHelena_BitvaNaverhu_2";
		break;
		
		case "PZ_MaryHelena_BitvaNaverhu_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Słyszysz to? Ktoś nadchodzi, tak, co nie? Pewnie przyjaciele tych umarlaków.";
				link.l1 = "Wtedy zobaczymy, jak do nich dołączają. Przygotuj się...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Słyszysz to? Kroki.";
				link.l1 = "Rzeczywiście, tak robię. Stań za mną.";
			}
			link.l1.go = "PZ_MaryHelena_BitvaNaverhu_3";
		break;
		
		case "PZ_MaryHelena_BitvaNaverhu_3":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) Return_MaryOfficer();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) Return_HelenaOfficer();
			sld = CharacterFromID("Longway");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Longway_61";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			RemovePassenger(pchar, sld);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "PZ_Longway_61":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Wielmożny Panie Kapitanie, pani "+sStr+".";
			link.l1 = "„Longway?! Myślisz, że możesz tak po prostu wejść do naszego pokoju? A gdybyśmy byli...?”";
			link.l1.go = "PZ_Longway_62";
			
			//заранее создаём заглушку для корабля
			sld = GetCharacter(NPC_GenerateCharacter("PZ_ShipStasis", "citiz_46", "man", "man", sti(pchar.rank), PIRATE, -1, false, "quest"));
			SetSPECIAL(sld, 1, 1, 1, 1, 1, 1, 1);
		break;
		
		case "PZ_Longway_62":
			dialog.text = "Hm, proszę o wybaczenie, Wielmożny Panie Kapitanie. Myślałem, że zamknąłbyś drzwi, gdybyś był tak zajęty. Ale Longway znalazł je otwarte.";
			link.l1 = "Złamani, nie otwarci. Ale powiedz mi, przyjacielu, dlaczego jesteś taki cholernie spokojny? Na podłodze leżą martwe ciała, jesteśmy uzbrojeni, a ty...";
			link.l1.go = "PZ_Longway_63";
		break;
		
		case "PZ_Longway_63":
			dialog.text = "„Cóż, jestem do tego przyzwyczajona.”";
			link.l1 = "„I nie możesz się z tym kłócić, co nie? Ale naprawdę, nie słyszałeś odgłosów walki w drodze tutaj? Nie widziałeś, jak te brutale wchodzą do tawerny i wspinają się po schodach tuż przed tobą?”";
			link.l1.go = "PZ_Longway_64";
		break;
		
		case "PZ_Longway_64":
			dialog.text = "Nie, Wielmożny Panie Kapitanie. Nie widziałem obcych w sali, kiedy szedłem tutaj.";
			link.l1 = "To absurdalny zbieg okoliczności. Czego chcesz, Longway?";
			link.l1.go = "PZ_Longway_65";
		break;
		
		case "PZ_Longway_65":
			dialog.text = "Pilnie potrzebuję statku i załogi, Wielmożny Panie Kapitanie.";
			link.l1 = "Co? Dlaczego? Czy w końcu wpadłeś na trop Chang Xing? W takim razie chodźmy po nią teraz, razem.";
			link.l1.go = "PZ_Longway_66";
		break;
		
		case "PZ_Longway_66":
			dialog.text = "Niestety, to nie Chang Xing. To... Joep van der Vink. Georges Gravel przesłał wiadomość, a ja ją otrzymałem, gdy spacerowałem po wiosce, podczas gdy ty... odpoczywałeś z damą.";
			link.l1 = "Tak, miałem wspaniały odpoczynek, to mogę ci powiedzieć. Ale dlaczego mielibyśmy się teraz rozdzielić, Longway? Mamy cholernie długą listę ważnych zadań do wykonania i niebezpiecznych ludzi do zabicia.";
			link.l1.go = "PZ_Longway_67";
		break;
		
		case "PZ_Longway_67":
			dialog.text = "Van der Vink nie jest tak niebezpieczny jak Levasseur. Poza tym, już raz go pokonałem. I pokonam go znowu. Tym razem, aby upewnić się, że jest martwy na dobre. Nie chcę, abyśmy wszyscy marnowali na niego cenny czas. Powinieneś udać się na Tortugę i zapytać ważnych ludzi o wszystko, czego potrzebujemy. Sam schwycę van der Vinka. Wielmożny Panie Kapitanie, to nie jest warte marnowania twojego czasu, a ja też kiedyś byłem Kapitanem. Poradzę sobie.";
			link.l1 = "„Hmm, masz rację, Longway. Van der Vink może nie jest tak niebezpieczny, ale 'Banten' to jeden z najszybszych statków w Archipelagu. Nie każdy statek nada się, by ją dogonić. A co z załogą? Jak planujesz zebrać ludzi tak szybko i na własną rękę?”";
			link.l1.go = "PZ_Longway_68";
		break;
		
		case "PZ_Longway_68":
			dialog.text = "Znam odpowiednie miejsce i mam tam pozycję w Kompanii. A przynajmniej mogę udawać, jak to robiłem z Georgesem. Kompania... Pan Rodenburg korzystał z ich usług, gdy pilnie potrzebował wojowników, profesjonalnych załóg, które nie zadają pytań.";
			link.l1 = "Załoga statku do wynajęcia, więc... Ma sens, że coś takiego istnieje. I ile to będzie kosztować?";
			link.l1.go = "PZ_Longway_69";
		break;
		
		case "PZ_Longway_69":
			dialog.text = "Dwa i pół tysiąca. Od razu i natychmiast.";
			link.l1 = "To wszystko? Trzeba więcej, by wynająć pełną załogę zwykłych marynarzy z tawerny, zwłaszcza dla dużego statku. Najwyraźniej Rodenburg i jego agenci mają specjalne ceny w specjalnych miejscach.";
			link.l1.go = "PZ_Longway_70";
		break;
		
		case "PZ_Longway_70":
			dialog.text = "Chodziło mi o dublony, Wielmożny Panie Kapitanie.";
			link.l1 = "CO?!";
			link.l1.go = "PZ_Longway_70_4";
		break;
		
		case "PZ_Longway_70_4":
			dialog.text = "Słyszałeś mnie dobrze, Wielmożny Panie Kapitanie. To ważne. Nie prosiłbym o taką sumę za błahostkę.";
			link.l1 = "Tak, słyszałam cię, ale wciąż nie mogę w to uwierzyć. Faktycznie specjalne ceny. Czy przyjmują peso?";
			link.l1.go = "PZ_Longway_70_5";
		break;
		
		case "PZ_Longway_70_5":
			dialog.text = "Tak... od białych ludzi. Longway może mieć z tym problem, ale... myślę, że będę w stanie ich przekonać, jeśli wystarczająco mocno poproszę. Zawsze jest jakiś sposób.";
			link.l1 = "Cóż, to coś. I to tylko dla załogi... A masz jeszcze statek, do którego trzeba dotrzeć. Pewnie też w jakimś 'specjalnym miejscu'? Obawiam się zapytać, ile to nas będzie kosztować...";
			link.l1.go = "PZ_Longway_70_6";
		break;
		
		case "PZ_Longway_70_6":
			dialog.text = "„Nie do końca tak, Wielmożny Panie Kapitanie. Załoga przybywa z własnym statkiem.”";
			link.l1 = "Ale?";
			link.l1.go = "PZ_Longway_70_7";
		break;
		
		case "PZ_Longway_70_7":
			dialog.text = "„Meifeng”. Może stać się decydującym czynnikiem - żadna inna jednostka na Archipelagu nie jest od niej szybsza. I ona... była moja, więc ją znam. Czy pożyczysz mi ją, Wielmożny Panie Kapitanie?";
			if (PCharDublonsTotal() >= 2500)
			{
				link.l1 = "„Tutaj. Dwa i pół tysiąca doublonów. Pod warunkiem, że przyniesiesz mi głowę van der Vinka na tacy z czystego złota, ha ha ha ha!”";
				link.l1.go = "PZ_Longway_Dublons_1";
			}
			if (sti(pchar.Money) >= 300000)
			{
				link.l2 = "Nie noszę tylu dublonów, Longway. I wątpię, czy miałbym ich tyle na statku - mówisz o stosie złota. Ale pesos, oczywiście. Trzysta tysięcy to właśnie to, czego potrzebujesz.";
				link.l2.go = "PZ_Longway_Peso_1";
			}
			link.l3 = "Wiesz co, Longway... Czy naprawdę sugerujesz, żebym zapłacił tyle pieniędzy, ile potrzeba na uzbrojenie floty oblężniczej, tylko po to, żebyś mógł walczyć z pospolitym zbirem?!";
			link.l3.go = "PZ_Longway_Otkaz";
		break;
				
		case "PZ_Longway_Dublons_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) AddQuestUserData("PZ", "sText", "Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) AddQuestUserData("PZ", "sText", "Helen");
			
			dialog.text = "Oh... Longway dziękuje z głębi serca, Wielmożny Panie Kapitanie! Ale wciąż, co z 'Meifeng'?";
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				link.l1 = "Co z nią? Przyjacielu, czy uderzyłeś się w głowę w drodze tutaj? Ona jest teraz w naszej flocie!";
				link.l1.go = "PZ_Longway_Mayfang1";
			}
			else
			{
				link.l1 = "Muszę to przemyśleć, Longway. Ile mamy czasu, by złapać van der Vinka?";
				link.l1.go = "PZ_Longway_NoMayfang1";
			}
			RemoveDublonsFromPCharTotal(2500);
			pchar.questTemp.PZ_FlagShipDublons = true;
			notification("Longway approves", "Longway");
		break;
		
		case "PZ_Longway_Peso_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) AddQuestUserData("PZ", "sText", "Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) AddQuestUserData("PZ", "sText", "Helen");
			
			dialog.text = "Wielmożny Panie Kapitanie, popełniłeś drobny błąd. To będzie dwieście pięćdziesiąt tysięcy pesos.";
			link.l1 = "I did not; it's Charles de Maure's special exchange rate when his friends need help, ha ha. I'm giving you extra so you'll have enough for everything.";
			link.l1.go = "PZ_Longway_Peso_2";
			AddMoneyToCharacter(pchar, -300000);
		break;
		
		case "PZ_Longway_Peso_2":
			dialog.text = "Dziękuję bardzo, Wielmożny Panie Kapitanie... Ale co z 'Meifeng'?";
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				link.l1 = "A co z nią? Przyjacielu, czy uderzyłeś się w głowę po drodze tutaj? Ona jest teraz w naszej flocie!";
				link.l1.go = "PZ_Longway_Mayfang1";
			}
			else
			{
				link.l1 = "Muszę to przemyśleć, Longway. Ile mamy czasu, żeby złapać van der Vinka?";
				link.l1.go = "PZ_Longway_NoMayfang1";
			}
		break;
		
		case "PZ_Longway_Otkaz":
			dialog.text = "Nie ma innej drogi, Wielmożny Panie Kapitanie, proszę się uspokoić...";
			link.l1 = "Ach, jeszcze nie zacząłem. Oto oferta. Pięćdziesiąt tysięcy pesos. To wystarczająco, by kupić bryg w stoczni, przygotować go do bitwy, a nawet wynająć załogę.";
			link.l1.go = "PZ_Longway_Otkaz_2";
			AddMoneyToCharacter(pchar, -50000);
			
			pchar.questTemp.PZ.LongwayBrig = true; // Лонгвэй будет на бриге
			notification("Longway disapproves", "Longway");
		break;
		
		case "PZ_Longway_Otkaz_2":
			dialog.text = "  Ale, Wielmożny Panie Kapitanie. To może wystarczyć dla białego kapitana! Nie każdy zgodzi się handlować z Longwayem. Będą się ostro targować, zanim mi cokolwiek sprzedadzą!  ";
			link.l1 = "Więc, bądź przekonujący! Jesteś całkiem biegły w targowaniu się, sądząc po twojej początkowej... propozycji. Czy nadal tu jesteś? Weź te pieniądze i idź, skoro to takie pilne, jak mówisz!";
			link.l1.go = "PZ_Longway_Otkaz_3";
		break;
		
		case "PZ_Longway_Otkaz_3":
			dialog.text = "„Tak jest, Wielmożny Panie Kapitanie...”";
			link.l1 = "I nie patrz na mnie tak. Do zobaczenia później na Tortudze. Powodzenia.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			AddQuestRecord("PZ", "58");
		break;
		
		case "PZ_Longway_Mayfang1":
			dialog.text = "„Ehem, nie, Wielmożny Panie Kapitanie. Oczywiście, że pamiętam. Longway tylko pytał, czy jesteś gotów podzielić się nią ze mną.”";
			link.l1 = "Tak jest. W końcu van der Vink jest równie zamieszany w nieszczęścia twojej siostry, jak inni ludzie z naszej listy. Złapanie go jest więc naprawdę ważne. Oddaję ci dowództwo nad Meifeng.";
			link.l1.go = "PZ_Longway_Mayfang2";
		break;
		
		case "PZ_Longway_Mayfang2":
			// если "Мейфенг" у ГГ
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							//pchar.questTemp.PZ.Mayfang.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Mayfang.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayMayfang = true;
			pchar.questTemp.PZ_FlagShip = true;
			
			dialog.text = "Nie mogę w to uwierzyć... Dziękuję, Wielmożny Panie Kapitanie!";
			link.l1 = "„Ach, to nic. Kiedyś to był twój statek, zawsze będę o tym pamiętać. No dalej. Zabij tego skurwysyna. Ja ruszam do Tortugi.”";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			AddQuestRecord("PZ", "59");
			notification("Longway approves", "Longway");
		break;
		
		
		case "PZ_Longway_NoMayfang1":
			dialog.text = "„Czasu jest mało, Wielmożny Panie Kapitanie. Nie powinniśmy go marnować - Chang Xing może potrzebować naszej pomocy...”";
			link.l1 = "„Wiem o tym, Longway. Ale ile dokładnie mamy czasu, żeby złapać van der Vinka?”";
			link.l1.go = "PZ_Longway_NoMayfang2";
		break;
		
		case "PZ_Longway_NoMayfang2":
			dialog.text = "„Kilka miesięcy - regularnie pływa tą trasą przez mniej więcej ten czas, zanim na chwilę znika. Taki już jego sposób, jak Gravel poinformował mnie w swoim liście.”";
			link.l1 = "Dobrze. W takim razie chodźmy na statek...";
			link.l1.go = "PZ_Longway_NoMayfang3";
		break;
		
		case "PZ_Longway_NoMayfang3":
			dialog.text = "Obawiam się, że moje przygotowania muszą rozpocząć się natychmiast, Wielmożny Panie Kapitanie. Tak abyśmy mogli od razu zacząć, gdy będę miał Meifenga. Muszę wcześniej negocjować z ludźmi.";
			link.l1 = "Więc gdzie się spotkamy?";
			link.l1.go = "PZ_Longway_NoMayfang4";
		break;
		
		case "PZ_Longway_NoMayfang4":
			AddQuestRecord("PZ", "60");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) AddQuestUserData("PZ", "sText", "Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) AddQuestUserData("PZ", "sText", "Helen");
			
			i = FindColony("Pirates");
			if (colonies[i].nation != ENGLAND)
			{
				dialog.text = "Tu właśnie. Ale możemy się spotkać przy stoczni, jeśli będzie ci wygodniej.";
				link.l1 = "I dlaczego tylko ja nie wiedziałam, że tutaj można zatrudnić całą załogę walczących ludzi za odpowiednią cenę?";
				link.l1.go = "PZ_Longway_NoMayfangIslaTesoro1";
			}
			else
			{
				dialog.text = "„Ci najemnicy mieli kiedyś miejsce na Isla Tesoro, ale zostali zmuszeni do przeniesienia się tutaj.”";
				link.l1 = "Widzę dlaczego. Więc gdzie mam cię szukać w La Vega?";
				link.l1.go = "PZ_Longway_NoMayfangLaVega1";
			}
		break;
		
		case "PZ_Longway_NoMayfangIslaTesoro1":
			dialog.text = "Ponieważ bardzo niewielu o tym wie. A jeszcze mniej może sobie na to pozwolić. Mynheer Rodenburg był ich jedynym klientem przez długi czas.";
			link.l1 = "Rozumiem. No dobrze, Longway. Do zobaczenia tam.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LongwayToPiratesShipyard");
		break;
		
		case "PZ_Longway_NoMayfangLaVega1":
			dialog.text = "„Karczma, Wielmożny Panie Kapitanie. Gdzież indziej miałbym być?”";
			link.l1 = "Zgadza się. Do zobaczenia później, Longway! Dbaj o siebie.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LongwayToLaVegaTavern");
		break;
		
		case "PZ_Longway_WaitForShip1":
			dialog.text = "Wielmożny Panie Kapitanie, mam zaszczyt poinformować, że załoga jest gotowa. Jest jeszcze jedna kwestia do załatwienia. Co z 'Meifeng'?";
			link.l1 = "Jak dotąd, nie wybrałem jeszcze statku godnego ciebie, Longway.";
			link.l1.go = "PZ_Longway_WaitForShip2";
			if ((FindCompanionShips(SHIP_SCHOONER_W)) || (FindCompanionShips(SHIP_BRIG)) || (FindCompanionShips(SHIP_CORVETTE)) || (FindCompanionShips(SHIP_POLACRE)) || (FindCompanionShips(SHIP_XebekVML)) || (FindCompanionShips(SHIP_BRIGANTINE)))
			{
				if (FindCompanionShips(SHIP_SCHOONER_W)) sStr = "War schooner";
				if (FindCompanionShips(SHIP_BRIG)) sStr = "Brig";
				if (FindCompanionShips(SHIP_CORVETTE)) sStr = "Corvette";
				if (FindCompanionShips(SHIP_POLACRE)) sStr = "Polacre";
				if (FindCompanionShips(SHIP_XebekVML)) sStr = "Xebek";
				if (FindCompanionShips(SHIP_BRIGANTINE)) sStr = "Brigantine";
				link.l2 = "'"+sStr+"„ należy do ciebie.”";
				link.l2.go = "PZ_Longway_NoQuestShip1";
			}
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				link.l3 = "Co z 'Meifeng'? Myślałeś, że pozwolę jej zmarnować się?";
				link.l3.go = "PZ_Longway_Mayfang3";
			}
			if (FindCompanionShips(SHIP_CURSED_FDM))
			{
				link.l4 = "Mam dla ciebie... specjalny statek, Longway. Szybki. I jeszcze bardziej zabójczy niż Meifeng. To wojenny galeon, 'Latające Serce'.";
				link.l4.go = "PZ_Longway_Caleuche1";
			}
			if (FindCompanionShips(SHIP_POLACRE_QUEST))
			{
				link.l5 = "„Lubisz dżonki, Longway. A co z polakrami? Zwłaszcza tą, 'Torero'. Oczywiście, nie jest zbudowana na regaty, ale jest całkiem potężna.”";
				link.l5.go = "PZ_Longway_Torero1";
			}
			if (FindCompanionShips(SHIP_ELCASADOR))
			{
				link.l6 = "Muszę przyznać, nie sądziłem, że pewnego dnia znajdzie się godne zastosowanie dla tego. Co sądzisz o tym galeonie? Potężny 'El Casador'!";
				link.l6.go = "PZ_Longway_ElCasador1";
			}
		break;
		
		case "PZ_Longway_NoQuestShip1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			
			// а теперь хором, дети: ненавижу костыли, ненавижу костыли, ненавижу костыли, нена... помогите!!!
			if ((FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_SCHOONER_W)
						{
							//pchar.questTemp.PZ.SchoonerW.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.SchoonerW.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwaySchoonerW = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_BRIG)
						{
							//pchar.questTemp.PZ.Brig.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Brig.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayBrig = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_CORVETTE)
						{
							//pchar.questTemp.PZ.Corvette.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Corvette.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayCorvette = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_POLACRE)
						{
							//pchar.questTemp.PZ.Polacre.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.Polacre.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayPolacre = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_XebekVML)
						{
							//pchar.questTemp.PZ.Xebek.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Xebek.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayXebek = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_BRIGANTINE)
						{
							//pchar.questTemp.PZ.Brigantine.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Brigantine.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayBrigantine = true;
			}
			
			dialog.text = "To nie jest 'Meifeng', Wielmożny Panie Kapitanie! Co się stało z Meifeng?";
			link.l1 = "Longway! "+sStr+" jest w niebezpieczeństwie! I twoja siostra też! A ty marudzisz, że nie masz takiego statku jak ten?! Każdy byłby zadowolony z takiego statku! Weź ją pod swoje dowództwo i pokaż van der Vinkowi, na co cię stać.";
			link.l1.go = "PZ_Longway_NoQuestShip2";
		break;
		
		case "PZ_Longway_NoQuestShip2":
			dialog.text = "„Dobrze... Mam nadzieję, że Niebo zesła mi szczęście. Tak samo jak życzę tego samego tobie na Tortudze. Do widzenia, Wielmożny Panie Kapitanie.”";
			link.l1 = "Jestem tego pewien. Żegnaj, Longway.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			pchar.questTemp.PZ_NoQuestShip = true;
		break;
		
		case "PZ_Longway_Mayfang3":
			// если "Мейфенг" у ГГ
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							//pchar.questTemp.PZ.Mayfang.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Mayfang.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayMayfang = true;
			pchar.questTemp.PZ_FlagShip = true;
			
			dialog.text = "„Ahem, nie, Wielmożny Panie Kapitanie. Oczywiście, że pamiętam. Longway tylko pytał, czy jesteś gotowy podzielić się nią ze mną.”";
			link.l1 = "Jestem. W końcu van der Vink jest tak samo zamieszany w nieszczęścia twojej siostry jak inni ludzie z naszej listy. Więc złapanie go jest naprawdę ważne. Przekazuję ci dowództwo nad 'Meifeng'.";
			link.l1.go = "PZ_Longway_Mayfang4";
		break;
		
		case "PZ_Longway_Mayfang4":
			dialog.text = "Nie mogę w to uwierzyć... Dziękuję, Wielmożny Panie Kapitanie!";
			link.l1 = "Ach, to nic. Ona kiedyś była twoim statkiem, zawsze będę to pamiętać. No dalej. Zabij tego skurwysyna. Ja wyruszam na Tortugę.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			notification("Longway approves", "Longway");
		break;
		
		case "PZ_Longway_Caleuche1":
			dialog.text = "Ja... Ja nie mogę dowodzić TYM, Wielmożny Panie Kapitanie. Longway wciąż troszczy się o swoje życie, duszę i zdrowie umysłowe.";
			link.l1 = "„Ha ha ha, Longway! No dalej, nie wiedziałam, że jesteś taki przesądny. Ale w każdym razie, klątwa została zdjęta, więc nie masz się czego bać.”";
			link.l1.go = "PZ_Longway_Caleuche2";
		break;
		
		case "PZ_Longway_Caleuche2":
			dialog.text = "„Ach... ale czy van der Vink o tym wie? Ucieknie jak przestraszony królik, jak tylko zobaczy ten statek.”";
			link.l1 = "Masz rację co do tego. Dobrze, znajdziemy coś innego dla ciebie.";
			link.l1.go = "PZ_Longway_WaitForShip2";
		break;
		
		case "PZ_Longway_Torero1":
			// если "Тореро" у ГГ
			if (FindCompanionShips(SHIP_POLACRE_QUEST))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_POLACRE_QUEST)
						{
							//pchar.questTemp.PZ.Torero.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Torero.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayTorero = true;
			if (CheckAttribute(pchar, "questTemp.PZ_FlagShipDublons"))
			{
				pchar.questTemp.PZ_FlagShip = true;
				notification("Longway approves", "Longway");
			}
			
			dialog.text = "Sam nigdy nie prowadziłem polakry. Jest interesująca, ale teraz najważniejsza jest prędkość, nie siła.";
			link.l1 = "„To prawda, ale to w końcu polakra. Może nie jest tak szybka jak 'Banten', lecz możesz łapać wiatr pod kątem, którego oni nie mogą. Nawet bardziej niż sama 'Meifeng' kiedykolwiek mogła. Więc wykorzystaj to.”";
			link.l1.go = "PZ_Longway_Torero2";
		break;
		
		case "PZ_Longway_Torero2":
			dialog.text = "Wciąż... 'Meifeng' była lepsza... Szkoda, że pozwoliłeś jej zmarnować się, Wielmożny Panie Kapitanie. Powodzenia na Tortudze.";
			link.l1 = "To samo do ciebie, Longway. Dziękuję.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
		break;
		
		case "PZ_Longway_ElCasador1":
			// если "Эль Касадор" у ГГ
			if (FindCompanionShips(SHIP_ELCASADOR))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_ELCASADOR)
						{
							//pchar.questTemp.PZ.ElCasador.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.ElCasador.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayElCasador = true;
			if (CheckAttribute(pchar, "questTemp.PZ_FlagShipDublons"))
			{
				pchar.questTemp.PZ_FlagShip = true;
				notification("Longway approves", "Longway");
			}
			
			dialog.text = "Wielmożny Panie Kapitanie, to może być najdziwniejszy galeon na Archipelagu. Dam sobie radę, ale jest wolniejszy niż 'Banten'...";
			link.l1 = "„Cóż, nie rywalizujesz z Joepem w regatach, prawda?”";
			link.l1.go = "PZ_Longway_ElCasador2";
		break;
		
		case "PZ_Longway_ElCasador2":
			dialog.text = "Cokolwiek mówisz. Ale 'Meifeng' była lepsza... Szkoda, że pozwoliłeś jej zmarnować się, Wielmożny Panie Kapitanie. Powodzenia na Tortudze.";
			link.l1 = "„Wzajemnie, Longway. Dziękuję.”";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
		break;
		
		case "PZ_Longway_WaitForShip2":
			NextDiag.TempNode = "PZ_Longway_WaitForShip1";
			
			dialog.text = "Doceniam twoją troskę, Wielmożny Panie Kapitanie, ale proszę, pospiesz się - nie mamy dużo czasu.";
			link.l1 = "Wiem. Ale nie chcesz gonić za czymś nieuchwytnym, prawda? Dobrze, znajdę ci odpowiedni statek.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaTortugaCabin_1":
			dialog.text = "Jesteśmy prawie na miejscu, Charles. Czy zdecydowałeś, od czego zacząć? Może warto byłoby zapytać ludzi na ulicach...";
			link.l1 = "„Może tak jest. Ale nie dla nas - dla mnie. Zostaniesz na pokładzie, Helen.”";
			link.l1.go = "PZ_HelenaTortugaCabin_2";
		break;
		
		case "PZ_HelenaTortugaCabin_2":
			dialog.text = "Charles, oczywiście, wciąż niepokoją mnie ci łajdacy i to, co powiedzieli, i sensowne jest, żebym pozostała pod ochroną załogi... Ale to, że idziesz samotnie do legowiska bestii, wcale nie sprawia, że czuję się bezpieczniej.";
			link.l1 = "Rozumiem. Ale jeśli coś pójdzie nie tak, o wiele łatwiej jest uciec samemu, wiedząc, że jesteś bezpieczna. To rozkaz, Helen. Poczekaj tu na mnie i postaraj się za bardzo nie martwić.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaCabin_Exit");
		break;
		
		case "PZ_MaryTortugaCabin_1":
			dialog.text = "Oto Tortuga, Charles, tak, co nie? Nie mogę się doczekać, by zapukać do kilku drzwi i zapytać, czego chciał ode mnie ten tłusty osioł...";
			link.l1 = "„Dlatego właśnie zostajesz na pokładzie, moja droga.”";
			link.l1.go = "PZ_MaryTortugaCabin_2";
			
			pchar.questTemp.MarySexBlock = true;
			pchar.quest.Mary_giveme_sex.over = "yes";
			pchar.quest.Mary_giveme_sex1.over = "yes";
		break;
		
		case "PZ_MaryTortugaCabin_2":
			dialog.text = "Nie ma mowy! Myślisz, że pozwolę ci zejść na ląd samemu?";
			link.l1 = " Myślę, że jeśli Levasseur zdecyduje się dokończyć to, czego nie udało się jego najemnikom, nie będziemy mieli szans się bronić. Nie chcę prowokować go niepotrzebnie, zwłaszcza że moim celem nie jest on, ale Joep van der Vink.";
			link.l1.go = "PZ_MaryTortugaCabin_3";
		break;
		
		case "PZ_MaryTortugaCabin_3":
			dialog.text = "Więc teraz jestem zamknięta, tak, co nie?";
			link.l1 = "  Nie rozkazuję ci, tylko proszę cię, Mary.";
			link.l1.go = "PZ_MaryTortugaCabin_4";
		break;
		
		case "PZ_MaryTortugaCabin_4":
			dialog.text = "Co jeśli coś ci się stanie w jakimś zaułku tej przeklętej wyspy?";
			link.l1 = "W takim razie obiecuję, że nie będę się bawił w bohatera. A świadomość, że jesteś bezpieczna, pozwoli mi biec szybciej. Poczekaj na mnie na statku i na Boga, nie schodź na ląd, cokolwiek się stanie.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaCabin_Exit");
		break;
		
		case "PZ_RobertMartin1":
			chrDisableReloadToLocation = true;
			
			dialog.text = "Kim jesteś? Wątpię, żebyś przeszedł przez plażę tylko po to, żeby pogadać.";
			link.l1 = "Zgadza się. Charles de Maure. Rober Martene?";
			link.l1.go = "PZ_RobertMartin2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_RobertMartin2":
			dialog.text = "Charles de Maure? Cholera, tylko nie mieszaj mnie w żadne ciemne sprawki. Tak, to ja. Więc, czego chcesz?";
			link.l1 = "Powiedziano mi, że jesteś przyjacielem Joepa van der Vinka, i...";
			link.l1.go = "PZ_RobertMartin3";
		break;
		
		case "PZ_RobertMartin3":
			dialog.text = "Kto ci to powiedział? Rozpruję im flaki. Cóż, znamy się, to wszystko. Nie chcę żadnych kłopotów, bo ci się naraził.";
			link.l1 = "„Heh, szybko rezygnujesz ze swoich przyjaciół...”";
			link.l1.go = "PZ_RobertMartin4";
		break;
		
		case "PZ_RobertMartin4":
			dialog.text = "Nie myśl tak. Nie boję się ciebie. Ale po co się trudzić, a nawet stwarzać problemy? Nie znam Joepa tak dobrze, jak ci powiedziano. Szukasz go?";
			link.l1 = "„Tak, coś w tym jest. Wiem, że już opuścił Tortugę, ale nie zaszkodzi dowiedzieć się o nim więcej - gdzie był, z kim rozmawiał. Możesz pomóc?”";
			link.l1.go = "PZ_RobertMartin5";
		break;
		
		case "PZ_RobertMartin5":
			dialog.text = "To i tak by ci nie pomogło, więc... czemu nie? Był w burdelu. W burdelu. Myślę, że możesz sobie na to pozwolić, więc ci o tym mówię.";
			link.l1 = "Nowy burdel? Jeden już ci nie wystarcza?";
			link.l1.go = "PZ_RobertMartin6";
		break;
		
		case "PZ_RobertMartin6":
			dialog.text = "„Cóż, nie nowy, ale niewielu o nim wie. I tylko nieliczni mogą sobie na to pozwolić. Myślę, że twój czas nadszedł. Ale ostrzegam - akceptowane są tylko dublony. Jeśli wciśniesz srebro, dostaniesz kopniaka w tyłek.”";
			link.l1 = "Tak myślałem. I gdzie powiedziałeś, że jest ten burdel?";
			link.l1.go = "PZ_RobertMartin7";
		break;
		
		case "PZ_RobertMartin7":
			dialog.text = "„Wiesz, ten budynek z kolumnami? To właśnie ten. I jaka tam gospodyni! Żółtawa skóra, taka piękna! Heh, widzę, że już cieknie ci ślinka, co?”";
			link.l1 = "Heh-heh, coś w tym jest. Dzięki, Rober. Dziś żadnych kłopotów dla ciebie - bardzo mi pomogłeś.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LighthouseMartinGo");
		break;
		
		case "PZ_MaryTortugaCabin_11":
			dialog.text = "W końcu wróciłeś, Charles! Nie mogłam znaleźć sobie miejsca, tak, co nie?";
			link.l1 = "Nie zajmie mi to długo, Mary. Mam małą sprawę do załatwienia... Nie będę cię trzymał w niepewności - to sprawa Longwaya. Muszę odwiedzić miejscowy burdel.";
			link.l1.go = "PZ_MaryTortugaCabin_12";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_MaryTortugaCabin_12":
			dialog.text = "Wiedziałam, że nie powinnam była pozwolić ci iść na brzeg samemu. Albo zapomniałeś założyć kapelusza i twoja głowa się zagrzała... Albo się uderzyłeś, tak, co nie?";
			link.l1 = "Mary, posłuchaj mnie. Możliwe, że właścicielka tego przybytku to siostra Longwaya. Aby się upewnić, musiałbym ją zobaczyć, ale to wszystko, co zrobię. Nie mogę tego zrobić bez wejścia do środka. Ale nie chcę, żebyś pomyślała coś, czego nie powinnaś.";
			link.l1.go = "PZ_MaryTortugaCabin_13";
		break;
		
		case "PZ_MaryTortugaCabin_13":
			dialog.text = "Jesteś pewien, że mnie nie okłamujesz, Charles?";
			link.l1 = "Mary, spójrz na to w ten sposób... Czy kiedykolwiek słyszałaś o mężczyźnie ostrzegającym swoją ukochaną o...?";
			link.l1.go = "PZ_MaryTortugaCabin_14";
		break;
		
		case "PZ_MaryTortugaCabin_14":
			dialog.text = "Po prostu przestań, Charles, nawet nie chcę o tym myśleć. Wierzę ci i ufam. I mam nadzieję, że nie zostaniesz tam dłużej, niż musisz.";
			link.l1 = "Nie dłużej niż minutkę, kochanie, obiecuję. Wchodzimy i wychodzimy, zobaczysz.";
			link.l1.go = "PZ_PredupredilNashuDevushku";
		break;
		
		case "PZ_HelenaTortugaCabin_11":
			dialog.text = "Charles! Wróciłeś nawet szybciej, niż się spodziewałam. Ale co się stało? Nie wyglądasz najlepiej... Dowiedziałeś się czegoś o Joepie van der Vink?";
			link.l1 = "„Jeszcze nie. Dowiedziałem się kilku rzeczy, ale by pójść dalej... muszę udać się do... burdelu. Nie z tych powodów, o których możesz pomyśleć, oczywiście.”";
			link.l1.go = "PZ_HelenaTortugaCabin_12";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_HelenaTortugaCabin_12":
			dialog.text = "Burdel? Nie wiedziałem, że te miejsca oferują coś poza oczywistością. Ш: Muszę porozmawiać z właścicielem, to wszystko. I to nie jest byle jaki burdel. Pogłoski mówią - to bardzo drogi przybytek, tylko dla członków wysokiego społeczeństwa...";
			link.l1 = "Obiecuję, że idę tam tylko w sprawie Longway'a. Jest całkiem możliwe, że właścicielka tego miejsca to jego siostra. Nie będę tam długo.";
			link.l1.go = "PZ_HelenaTortugaCabin_13";
		break;
				
		case "PZ_HelenaTortugaCabin_13":
			dialog.text = "„Cóż, to w sam raz dla ciebie, kochanie. Och, żartuję. Mimo to, nie jestem zachwycona, że tam idziesz. Ale... Jak sobie życzysz. Nie jesteś zobowiązany informować mnie o takich rzeczach. Nigdy nie obiecałam ci, że nie będę spać z innym mężczyzną. A jednak tego nie robię. Bo to coś, co uważam za oczywiste.”";
			link.l1 = "Pod innymi okolicznościami zabrałbym cię ze sobą, ale...";
			link.l1.go = "PZ_HelenaTortugaCabin_14";
		break;
		
		case "PZ_HelenaTortugaCabin_14":
			dialog.text = "Dzięki, ale nie, dzięki. Charles, nie martw się. Nie jestem jakąś głupią zazdrosną dziewczyną. No, może zazdrosną, ale nie głupią. I wierzę ci. Głupia ja!";
			link.l1 = "Dzięki, Helen. Zaraz wracam.";
			link.l1.go = "PZ_PredupredilNashuDevushku";
		break;
		
		case "PZ_PredupredilNashuDevushku":
			DialogExit();
			LAi_SetActorType(npchar);
			pchar.questTemp.PZ_PredupredilNashuDevushku = true;
		break;
		
		case "PZ_ElitaShluha_1":
			dialog.text = "O, nowa twarz w naszym przybytku? Witamy, monsieur. Jedzenie, stare wino, gorąca kąpiel - wszystko czeka na ciebie, jeśli możesz sobie pozwolić na spędzenie czasu z jednym z nas.";
			link.l1 = "Dziękuję za powitanie, mademoiselle. Ale nie dlatego tu jestem. Szukam kogoś...";
			link.l1.go = "PZ_ElitaShluha_2";
			
			// Убираем Мартэна с Маяка
			sld = characterFromID("PZ_RobertMartin");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			
			for (i=1; i<=3; i++)
			{
				sld = characterFromID("PZ_MayakPiraty_"+i);
				sld.lifeday = 0;
			}
			
			sld = characterFromID("PZ_RobertMartin_CloneMayakShip");
			sld.lifeday = 0;
			
			locations[FindLocation("Mayak6")].DisableEncounters = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Mayak6")], false);
			RemoveGeometryFromLocation("Mayak6", "smg");
		break;
		
		case "PZ_ElitaShluha_2":
			dialog.text = "It is only with the heart that one can see rightly; what is essential is invisible to the eye.";
			link.l1 = "Piękne. Nigdy wcześniej nie słyszałam tych słów.";
			link.l1.go = "PZ_ElitaShluha_3";
		break;
		
		case "PZ_ElitaShluha_3":
			dialog.text = "Jesteśmy tutaj wykształcone, nie tylko lalki. Hostessa uważa, że to istotne dla naszej placówki.";
			link.l1 = "Hostessa! To jej szukam. Słyszałem, że ma żółtą skórę. Powiedz mi, czy to prawda? Jak ma na imię, tak swoją drogą?";
			link.l1.go = "PZ_ElitaShluha_4";
		break;
		
		case "PZ_ElitaShluha_4":
			dialog.text = "„To prawda. Ale ma lepszy zmysł do interesów niż wiele białych kobiet. Nazywa się Belle Etoile. Ale dość gadania.”";
			link.l1 = "Dość rozmów, mówisz? Jestem tu dla rozmowy. Zadawam jeszcze kilka pytań i wtedy odchodzę.";
			link.l1.go = "PZ_ElitaShluha_5";
		break;
		
		case "PZ_ElitaShluha_5":
			dialog.text = "A co to za korzyść dla zakładu? Tutaj płacą nie za ciała, ale za czas. Chcesz porozmawiać? Proszę bardzo. Ale najpierw pieniądze. I będziemy szeptać w pokoju, z dala od ciekawskich uszu. Nie obchodzi mnie, co tam robimy - nie obchodzi mnie, czy zapalimy świece i będziemy się modlić. Klient raz poprosił mnie, bym pomógł mu napisać wiersz. Inny, by porozmawiać o swoich problemach, nazywając mnie swoim dobrym przyjacielem. A trzeci - tylko po to, by zapalić świece, aby potem...";
			link.l1 = "„Cóż, nie chcę wiedzieć - ostatnio usłyszałam coś nieprzyjemnego. Ile ci jestem winna?”";
			link.l1.go = "PZ_ElitaShluha_6";
		break;
		
		case "PZ_ElitaShluha_6":
			dialog.text = "Dwieście pięćdziesiąt dubloonów. Bez targów. Jeśli zorientujemy się, że mamy do czynienia z bezgroszowym pozerem, wyrzucimy go bez żalu. A jeśli jest bogaty, lecz skąpy, podnosimy cenę - i tak zapłaci.";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "Oto, dwieście pięćdziesiąt sztuk złota.";
				link.l1.go = "PZ_ElitaShluha_7";
			}
			link.l2 = "„O rany, to miejsce jest droższe niż ten burdel na Jamajce. Mogę wrócić później, jak zdobędę złoto?”";
			link.l2.go = "PZ_ElitaShluha_Otkaz_1";
		break;
		
		case "PZ_ElitaShluha_7":
			dialog.text = "Dobrze. Od czego zaczniemy? Kolacja, z czy bez świec, kąpiel, rozmowa?";
			link.l1 = "Nie mam zbyt wiele czasu, więc przejdźmy od razu do moich pytań. Prowadź.";
			link.l1.go = "PZ_ElitaShluha_IdemVKomnatu";
			RemoveDublonsFromPCharTotal(250);
		break;
		
		case "PZ_ElitaShluha_Otkaz_1":
			dialog.text = "Oczywiście, że możesz. Cierpliwość to jedna z cnót kurtyzany. Wyrzucenie żebraka to jedno. Pozwolić zamożnemu dżentelmenowi takiemu jak ty pójść po pieniądze, a nawet je pożyczyć, to zupełnie co innego.";
			link.l1 = "Cnoty kurtyzany... Ironia losu. Zaraz wracam.";
			link.l1.go = "PZ_ElitaShluha_Otkaz_2";
		break;
		
		case "PZ_ElitaShluha_Otkaz_2":
			DialogExit();
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_ElitaShluha_"+i);
				LAi_CharacterDisableDialog(sld);
			}
			LAi_CharacterEnableDialog(npchar);
			npchar.dialog.filename = "Quest\CompanionQuests\Longway.c";
			npchar.dialog.currentnode = "PZ_ElitaShluha_Again";
		break;
		
		case "PZ_ElitaShluha_Again":
			dialog.text = "Witaj z powrotem, monsieur! A więc, kim jesteś? Zamożnym dżentelmenem czy pozerem?";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "Oczywiście, jestem zamożnym dżentelmenem, mademoiselle. Oto twoje złoto - wszystkie dwieście pięćdziesiąt doublonów. Nie ma potrzeby ich liczyć.";
				link.l1.go = "PZ_ElitaShluha_Again_1";
			}
			link.l2 = "Jeszcze mi brakuje, po prostu daj mi chwilę.";
			link.l2.go = "exit";
			NextDiag.TempNode = "PZ_ElitaShluha_Again";
		break;
		
		case "PZ_ElitaShluha_Again_1":
			dialog.text = "Tu nie liczymy. Hmm, niektóre monety wyglądają na pogięte i złamane - pani tego nie polubi, ale przynajmniej to prawdziwe złoto.";
			link.l1 = "Co za... wdzięczna osoba z niej.";
			link.l1.go = "PZ_ElitaShluha_Again_2";
			RemoveDublonsFromPCharTotal(250);
		break;
		
		case "PZ_ElitaShluha_Again_2":
			dialog.text = "„Zgadza się. Pani Etoile potrafi być łagodna i troskliwa, potrafi być surowa, a czasem bezlitosna. Dlatego właśnie my się nie liczymy, przy okazji. Pani nie zawsze jest opłacana od razu, ale zawsze dostaje to, co jej się należy. Jeśli nie w złocie, to we krwi. Każdy dom tolerancji potrzebuje ochrony i patronów. A nasi odpowiadają statusowi przybytku.”";
			link.l1 = "Zapłaciłem, więc prowadź.";
			link.l1.go = "PZ_ElitaShluha_IdemVKomnatu";
		break;
		
		case "PZ_ElitaShluha_IdemVKomnatu":
			DialogExit();
			pchar.PZ_ElitaShluha = npchar.id;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload3", "PZ_ElitaShluha_VKomnate", -1);
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "", -1);
			bDisableCharacterMenu = true;
		break;
		
		case "PZ_ElitaShluha_8":
			dialog.text = "„Więc, jakie pytania masz, monsieur? Postaram się zaspokoić twoją... ciekawość.”";
			link.l1 = "Wiesz, co mnie interesuje, mademoiselle - twoja pani, Madame Etoile.";
			link.l1.go = "PZ_ElitaShluha_9";
		break;
		
		case "PZ_ElitaShluha_9":
			dialog.text = "Co mogę o niej powiedzieć? Pozostaje dla nas tajemnicą. Choć dba o nasze dobro, zdrowie i bezpieczeństwo, nie integruje się ani nie zbliża do żadnego z nas.";
			link.l1 = "Być może nie lubi długich rozmów. Powiedz mi, czy mówi z akcentem?";
			link.l1.go = "PZ_ElitaShluha_10";
		break;
		
		case "PZ_ElitaShluha_10":
			dialog.text = "Nie, dlaczego tak myślisz? Tylko dlatego, że ma żółtą skórę? Mówi czystym francuskim i kilkoma innymi językami. I potrafi prowadzić godzinną rozmowę na każdy temat z gośćmi i potencjalnymi partnerami.";
			link.l1 = "„Nie mów. Interesujące... Czy ona jest teraz tutaj? Jeśli tak, po prostu wejdę i ją zobaczę, i nie będę marnować więcej twojego prawdziwie... kosztownego czasu, żebyś mógł wrócić do pracy.”";
			link.l1.go = "PZ_ElitaShluha_11";
		break;
		
		case "PZ_ElitaShluha_11":
			dialog.text = "Nie ma zbyt wiele, do czego można wrócić - choć celem naszej gospodyni jest uczynienie tego miejsca najlepszym w Archipelagu. Elitarnego miejsca, gdzie żaden kupiec, szlachcic ani wykształcony człowiek nie wstydziłby się przyjść - bo oferujemy znacznie więcej niż nasze ciała.";
			link.l1 = "„Ale nie idzie jej to zbyt dobrze, prawda?”";
			link.l1.go = "PZ_ElitaShluha_12";
		break;
		
		case "PZ_ElitaShluha_12":
			dialog.text = "Jak to ująć... Ona postrzega każdego z nas nie tylko jako towar, jak w prostszych przybytkach, ale jako projekt. Drogie ubrania, medycyna, edukacja - inwestuje w każdego z nas. I gdybyśmy byli w wielkim mieście w Starym Świecie, odniosłaby sukces! Ale tutaj... Nawet utalentowany kupiec nic nie zarobi, jeśli towary są tak drogie, że prawie nikt nie może ich kupić. Nawet jeśli obniżymy ceny, jesteśmy skazani na bankructwo prędzej czy później.";
			link.l1 = "Przykro mi to słyszeć. Gdzie teraz jest twoja pani?";
			link.l1.go = "PZ_ElitaShluha_13";
		break;
		
		case "PZ_ElitaShluha_13":
			dialog.text = "Mamy tutaj jak dotąd dobre życie, mogę ci powiedzieć. To ma swoją cenę - zarabianie na nie i utrzymanie się na jej standardach... Co do damy, pojechała do Hispanioli, by omówić możliwość przeniesienia nas wszystkich do Port-au-Prince - w końcu tam krzyżuje się więcej szlaków handlowych, a nasz handel nie będzie tam stał bezczynny i cierpiał na niemal ciągłe straty.";
			link.l1 = "„Czyżby? Czy Levasseur nie zainwestował w to miejsce, by zapewnić mu stabilność?”";
			link.l1.go = "PZ_ElitaShluha_14";
		break;
		
		case "PZ_ElitaShluha_14":
			dialog.text = "„Niewiele. Przyszedł do nas i powiedział, że zainwestuje duże pieniądze, jeśli od czasu do czasu będziemy u niego bywać. Ale dama odmówiła stanowczo. Tak bardzo, że Jego Wysokość na chwilę stracił rezon. Nigdy nie widziałem jej ani jego w takim stanie.”";
			link.l1 = "Heh-heh, spójrz na to. Ona zdaje się wiedzieć... Odważna, bardzo odważna z niej kobieta.";
			link.l1.go = "PZ_ElitaShluha_15";
		break;
		
		case "PZ_ElitaShluha_15":
			dialog.text = "Wiesz co? Skoro już tak dobrze rozmawiamy, powiem ci coś jeszcze, ale to wielka tajemnica, więc nie mów o tym nikomu!";
			link.l1 = "„O nie, mademoiselle. Zapewniam cię, że nie zamierzam w żaden sposób skrzywdzić twojej pani. Proszę, kontynuuj.”";
			link.l1.go = "PZ_ElitaShluha_16";
		break;
		
		case "PZ_ElitaShluha_16":
			dialog.text = "Nie wiem nawet, czy mógłbyś jej zaszkodzić, bo Belle Etoile ćwiczy szermierkę każdego dnia i nie ma godnego przeciwnika w całym mieście. Oprócz Port-au-Prince planuje sama zaproponować Marcusowi Tyrexowi, by zainwestował! A raczej, by otrzymać od niego pożyczkę. Wyobrażasz to sobie?";
			link.l1 = "Tak, i czuję, że dziś będę mieć bardzo trudną rozmowę z inną kobietą, która regularnie ćwiczy szermierkę... Cóż, dziękuję za podzielenie się, mademoiselle. Życzę miłego dnia i hojnych klientów.";
			link.l1.go = "PZ_ElitaShluha_17";
		break;
		
		case "PZ_ElitaShluha_17":
			dialog.text = "Dziękuję. Ale czemu taki pośpiech? Zapłaciłeś w całości, a nie rozmawialiśmy tak długo. Poza tym, jest w tobie coś wyrafinowanego, monsieur. Coś o wiele więcej niż u tych rzadkich bogaczy, którzy odwiedzają nasz dom. Może naprawdę cieszmy się swoim towarzystwem?";
			link.l1 = "Wiesz... co do diabła? Dlaczego udaję i okłamuję siebie, jakbym tego nie chciał? Szansa z kobietą taką jak ty jest bardzo rzadka.";
			link.l1.go = "PZ_ElitaShluha_YesSex";
			link.l2 = "Och, niestety muszę powiedzieć nie, mademoiselle. Przyszedłem tu tylko porozmawiać. Poza tym... ktoś na mnie czeka.";
			link.l2.go = "PZ_ElitaShluha_NoSex";
		break;
		
		case "PZ_ElitaShluha_NoSex":
			dialog.text = "Jakby to kiedykolwiek kogoś powstrzymało. W tym przypadku, zasługujesz na szacunek, monsieur. Bardzo się cieszę z twojego 'kogoś'.";
			link.l1 = "Dziękuję ponownie, mademoiselle. Do widzenia.";
			link.l1.go = "PZ_ElitaShluha_NoSex_2";
		break;
		
		case "PZ_ElitaShluha_NoSex_2":
			DialogExit();
			AddQuestRecord("PZ", "30");
			chrDisableReloadToLocation = false;
			bDisableFastReload = true;
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_ElitaShluha_"+i);
				LAi_CharacterDisableDialog(sld);
			}
			npchar.lifeday = 0;
			
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1 = "location";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1.location = "Tortuga_town";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition = "PZ_TortugaKlemanLebren";
			DelMapQuestMarkCity("Tortuga");
			AddMapQuestMarkCity("LaVega", false);
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku"))
			{
				setCharacterShipLocation(pchar, "Tortuga_town");
				setWDMPointXZ("Tortuga_town");
			}
		break;
		
		case "PZ_ElitaShluha_YesSex":
			dialog.text = "Dziękuję. Może na początek wspólna gorąca kąpiel?";
			link.l1 = "Obie ręce za.";
			link.l1.go = "PZ_ElitaShluha_YesSex_2";
		break;
		
		case "PZ_ElitaShluha_YesSex_2":
			DialogExit();
			LAi_SetStayType(pchar);
			DoQuestCheckDelay("PlaySex_1", 1.0);
			DoQuestCheckDelay("PZ_ElitaShluha_Fuck", 1.0);
		break;
		
		case "PZ_ElitaShluha_After":
			dialog.text = "To było magiczne doświadczenie, monsieur. Nie sądziłam, że mężczyzna potrafi mnie tak zaskoczyć. Wiesz, jak sprawić przyjemność kobiecie...";
			link.l1 = "To zależy od kobiety.";
			link.l1.go = "PZ_ElitaShluha_After_2";
		break;
		
		case "PZ_ElitaShluha_After_2":
			dialog.text = "Żałujesz tego?";
			link.l1 = "„Zdecydowanie nie teraz. Żegnaj, mademoiselle.”";
			link.l1.go = "PZ_ElitaShluha_After_3";
		break;
		
		case "PZ_ElitaShluha_After_3":
			DialogExit();
			AddQuestRecord("PZ", "30");
			chrDisableReloadToLocation = false;
			bDisableFastReload = true;
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_ElitaShluha_"+i);
				LAi_CharacterDisableDialog(sld);
			}
			npchar.lifeday = 0;
			LAi_SetPlayerType(pchar);
			pchar.questTemp.PZ.EliteWhoreFucked = true; // флаг того, что секс был (понадобится для диалога с Тираксом)
			
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1 = "location";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1.location = "Tortuga_town";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition = "PZ_TortugaKlemanLebren";
			DelMapQuestMarkCity("Tortuga");
			AddMapQuestMarkCity("LaVega", false);
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku"))
			{
				setCharacterShipLocation(pchar, "Tortuga_town");
				setWDMPointXZ("Tortuga_town");
			}
		break;
		
		case "PZ_KlemanLebren_1":
			dialog.text = "Patrz, gdzie idziesz, pozerze!";
			link.l1 = "Uważaj na język!";
			link.l1.go = "PZ_KlemanLebren_2";
		break;
		
		case "PZ_KlemanLebren_2":
			dialog.text = "Patrzyłem, dokąd idę, podczas gdy ty liczyłeś wrony.";
			link.l1 = "Mogłeś obejść, gdybyś szukał, prawda?";
			link.l1.go = "PZ_KlemanLebren_3";
		break;
		
		case "PZ_KlemanLebren_3":
			dialog.text = "Dlaczego miałbym cię obchodzić?!";
			link.l1 = "Proponuję, byśmy dowiedzieli się poza miastem, kto komu i co jest winien.";
			link.l1.go = "PZ_KlemanLebren_4";
		break;
		
		case "PZ_KlemanLebren_4":
			dialog.text = "„Mm-mm, nie. Nie wiedziałam, że Wasza Lordowska Mość jest tak obrzydzona przypadkowym dotknięciem zwykłego człowieka.”";
			link.l1 = "Powiedz jeszcze raz?";
			link.l1.go = "PZ_KlemanLebren_5";
		break;
		
		case "PZ_KlemanLebren_5":
			dialog.text = "„Hmm, przepraszam. Nie miałem zamiaru cię popchnąć.”";
			link.l1 = "„To lepiej.”";
			link.l1.go = "PZ_KlemanLebren_6";
		break;
		
		case "PZ_KlemanLebren_6":
			DialogExit();
			
			LAi_LocationFightDisable(loadedLocation, false);
			chrDisableReloadToLocation = false;
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4", "", "", "", "", -1);
			npchar.location = "None";
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				sld = CharacterFromID("Mary");
				DelLandQuestMark(sld);
				if (CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku"))
				{
					PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1 = "location";
					PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1.location = "Tortuga";
					PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition = "PZ_TortugaRazgovorVKauteSDevushkoy";
				}
				else
				{
					ChangeCharacterAddressGroup(sld, "Tortuga_town", "rld", "loc0");
					sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
					sld.dialog.currentnode = "PZ_MaryRazgovorOBordeli_Bad_1";
					LAi_SetStayType(sld);
					CharacterTurnToLoc(sld, "quest", "quest1");
					sld.talker = 5;
					chrDisableReloadToLocation = true;
					LAi_LocationFightDisable(loadedLocation, true);
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				sld = CharacterFromID("Helena");
				DelLandQuestMark(sld);
				PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1 = "location";
				PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1.location = "Tortuga";
				PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition = "PZ_TortugaRazgovorVKauteSDevushkoy";
			}
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_1":
			dialog.text = "Jeśli spóźniłbyś się pół godziny, Charles, nasze kule armatnie rozniosłyby tę brudną norę na strzępy, tak, co nie? Znalazłeś to, czego szukałeś? Czy to ona, siostra Longweya? Widziałeś ją?";
			link.l1 = "„Cicho, Mary, nie mów tak. Nie, nie spotkałem się z Chang Xingiem...”";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_2";
			
			DeleteAttribute(pchar, "questTemp.MarySexBlock");
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_2":
			dialog.text = "A co do diabła tak długo cię zatrzymało?! Co tam robiłeś?";
			link.l1 = "Nie masz się czym martwić. Jak tylko dowiedziałem się wszystkiego, co mogłem, opuściłem tamto miejsce, tak jak ci obiecałem.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_3";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_3":
			dialog.text = "Po prostu wykrztuś to z siebie, tak, co nie?";
			link.l1 = "Właścicielki nie ma teraz na Tortudze. Popyt na jej usługi jest tu niski, ponieważ zatrudnia dobrze wykształcone damy w drogich strojach, a one akceptują tylko złoto jako zapłatę...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_4";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_4":
			dialog.text = "Też im zapłaciłeś?!";
			link.l1 = "Oni w ogóle by ze mną nie rozmawiali. Przy takim podejściu nic dziwnego, że nie mają wielu klientów. Madame postanowiła przenieść swój interes do Port-au-Prince, mając nadzieję przyciągnąć zamożniejszą klientelę. Ale najwyraźniej brakuje jej pieniędzy, skoro postanowiła zwrócić się do Marcusa Tyrexa o pożyczkę...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_5";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_5":
			dialog.text = "Czy on ją zna?";
			link.l1 = "Dowiemy się, gdy dotrzemy do La Vega. A jeśli się pospieszymy i przestaniemy marnować czas na niepotrzebne gadanie, złapiemy tę Azjatkę, kimkolwiek jest.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_6";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_6":
			dialog.text = "„Nie było potrzeby iść do tego burdelu, Charles. Jestem pewna, że moglibyśmy się wszystkiego dowiedzieć w tawernie lub na ulicach, gdybyśmy się wystarczająco postarali, tak, co nie?”";
			link.l1 = "Następnym razem zabiorę cię ze sobą, żebyś nie nabijała sobie tej ślicznej rudej główki bzdurami, co nie? A teraz, przejdźmy do interesów.";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_1":
			dialog.text = "O, widzę, że się trochę spóźniłam, tak, co nie? No, czekaj, ty łajdaku...";
			link.l1 = "Mary, co ty do diabła tutaj robisz?! Mówiłem ci, żebyś została na łodzi!";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_2";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_2":
			dialog.text = "Żebym ci nie przeszkadzała w zabawie z dziwkami?! Nawet nie próbuj zaprzeczać, Charles! Załoga cię tam widziała, tak, co nie?! Jak mogłeś?!";
			link.l1 = "Tego się spodziewałam. Chyba powinnam była zabrać ich ze sobą, żeby zobaczyli, co robię - a raczej, czego nie robię - i nie robili z tego wielkiego problemu...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_3";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_3":
			dialog.text = "„Oskarżasz naszych chłopców o kłamstwo? Po tym, co sam zrobiłeś, ty brutalu?”";
			link.l1 = "Obwiniam ich tylko o niezrównaną głupotę. Nie rozumiejąc sytuacji, ty...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_4";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_4":
			dialog.text = "„Och-och, Charles, nie sądzę, aby tobie i twoim dziwkom spodobało się, jak zrozumiałem sytuację, gdybym dotarł do tej dziury na czas. Ale masz szczęście - musiałem wiosłować tą cholerną łodzią całkiem sam...”";
			link.l1 = "„Mówią, że ciężka praca fizyczna oczyszcza głowę z niepotrzebnych myśli. Ale ty wciąż masz ich sporo, więc wracasz do wiosłowania.”";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_5";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_5":
			dialog.text = "Nie ruszam się, tak, co nie?";
			link.l1 = "„Mary, nie będziemy rozmawiać tutaj przed ludźmi Levasseura. Uspokój się, rozejrzyj się i podejmij decyzję. To ani czas, ani miejsce.”";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_6";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_6":
			dialog.text = "„Do diabła z tobą. Wciąż mam swoje rzeczy w kabinie... Ale nie myśl, że znowu będę wiosłować, tak, co nie! Musi w tobie pozostać coś ze szlachcica!”";
			link.l1 = "Jestem łajdakiem i brutusem, pamiętasz? Udowodnię to na statku, ale muszę tam najpierw dotrzeć. Więc twoje prośby są daremne.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_7";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_7":
			DialogExit();
			LAi_LocationFightDisable(loadedLocation, false);
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", Get_My_Cabin(), "rld", "loc1", "OpenTheDoors", -1);
			
			PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1 = "location";
			PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1.location = "Tortuga";
			PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition = "PZ_TortugaRazgovorVKauteSDevushkoy";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_8":
			dialog.text = "Cała załoga śmieje się z ciebie, tak, co nie?";
			link.l1 = "„Cóż, może i na ciebie też. Dawno nie widzieli takiego spektaklu. Teraz, gdy już trochę ochłonąłeś, pozwól mi opowiedzieć, co się stało.”";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_9";
			
			DeleteAttribute(pchar, "questTemp.MarySexBlock");
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_9":
			dialog.text = "Charles, słyszałam już wszystko. Mam tylko jedno pytanie: czy nie byłam dla ciebie wystarczająco dobra? Czy coś mi brakuje?";
			link.l1 = "„To niegrzeczne, ale odpowiem pytaniem: czy kiedykolwiek dałem ci powód, by mi nie ufać? Co? Nie pamiętam czegoś takiego. Więc weź oddech i posłuchaj mnie. Niewiele udało mi się dowiedzieć o Joepie van der Vinku poza tym, że odwiedził burdel. Nie ten przy 'Śpiewającym Kruku', ale inny, blisko nabrzeża. Nie wiedziałem o nim wcześniej... w przeciwieństwie do naszych marynarzy, którzy cię oświecili. Choć nie powinni byli mieć pozwolenia, by tam chodzić...”";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_10";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_10":
			dialog.text = "Jaki to burdel, który nie wpuszcza marynarzy, tak, co nie?";
			link.l1 = "„Dom publiczny, gdzie pracują damy odziane w jedwabie, które mają w głowach coś więcej niż tylko powietrze. A ich usługi opłacane są wyłącznie złotymi dublonami. To nie jest kaprys byle kogo, lecz rozkaz ich tajemniczej pani, Belle Etoile.”";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_11";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_11":
			dialog.text = "Tajemniczy, tak, co nie?";
			link.l1 = "To nie tylko to. Ona jest Azjatką.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_12";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_12":
			dialog.text = "Azjatka? Szefowa burdelu na Tortudze?";
			link.l1 = "Mogło to być Chang Xing. Dlatego tam poszedłem - chciałem zobaczyć ją na własne oczy. To wszystko.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_13";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_13":
			dialog.text = "Jaka ona jest?";
			link.l1 = "Nie mam pojęcia. Jej tam nie było, więc musiałem pogadać z inną... gwiazdą.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_14";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_14":
			dialog.text = "Czy ona też była Azjatką, tak, co nie?";
			link.l1 = "Nie, była biała. Powiedziała mi, że Belle Etoile ostatnio nie radzi sobie najlepiej, więc postanowiła przenieść się do Port-au-Prince. Ma to sens, bo ludzie tam są bogatsi. Madame musi być spłukana, skoro potrzebuje pożyczki, by otworzyć handel na Hispanioli, którą zamierza wziąć od Tyrexa. Więc jeśli się pospieszymy do La Vegi, możemy ją przechwycić, zanim spotka się z Markusem.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_15";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_15":
			dialog.text = "„Nie obchodzi mnie ona, Marcus ani nikt inny, tak, co nie? Charles, powiedz mi tylko jedno - byłeś z którąś z dziewczyn w jej burdelu?”";
			link.l1 = "Nie potrzebuję tego, Mary. Mam ciebie, najlepszą dziewczynę na świecie. Nie rozumiem, dlaczego tego nie dostrzegasz.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_16";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_16":
			dialog.text = "Właściwie to naprawdę łatwo dojść do prawdy, tak, co nie? Hee hee. Jeśli z nikim nie byłeś, to musisz być pełen energii teraz. To właśnie zamierzamy teraz sprawdzić, tak, co nie?";
			link.l1 = "Mary, proszę...";
			link.l1.go = "exit";
			pchar.quest.sex_partner = Npchar.id;
			AddDialogExitQuest("cabin_sex_go");
			pchar.questTemp.PZ_MaryRazgovorOBordeli = true;
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_17":
			DeleteAttribute(pchar, "questTemp.PZ_MaryRazgovorOBordeli");
			if (CheckAttribute(pchar, "questTemp.PZ.EliteWhoreFucked"))
			{
				if (IsCharacterPerkOn(pchar, "Medic"))
				{
					notification("Excellent Health", "Medic");
					dialog.text = "(Doskonałe Zdrowie) Uch... Wygląda na to, że nie kłamałeś, Charles, tak, co nie...";
					link.l1 = "Nie mam potrzeby cię oszukiwać, mój drogi...";
					link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_18";
				}
				else
				{
					notification("Perk check failed", "Medic");
					dialog.text = "Czy ty... czy ty mówisz serio, Charles?! Co to było?";
					link.l1 = "Och, ten upał mi nie służy. Ahem.";
					link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_19";
				}
			}
			else
			{
				dialog.text = "Ugh... Wygląda na to, że nie kłamałeś, Charles, tak, co nie...";
				link.l1 = "Nie mam potrzeby cię oszukiwać, mój drogi...";
				link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_18";
			}
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_18":
			dialog.text = "Ale tego rejsu w szalupie nie zapomnę przez długi czas!";
			link.l1 = "Ha!";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_19":
			dialog.text = "„Nigdy wcześniej na to nie narzekałeś, prawda?”";
			link.l1 = "Spróbuj pobiegać po tej przeklętej wyspie...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_20";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_20":
			dialog.text = "I burdele, tak, co nie! Czy naprawdę...";
			link.l1 = "Mary, przepraszam.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_21";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_21":
			dialog.text = "Co?! Więc jesteś...";
			link.l1 = "Nie żałuję tego. Cholera. Znaczy, nie byłam z nikim innym oprócz ciebie, mówiłam ci. Po prostu... nie mogłam uspokoić myśli, to wszystko. Trudno to zrobić, wiesz, kiedy działa La Roche’a patrzą na ciebie.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_22";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_22":
			dialog.text = "„To niezła wymówka, Charles. Dobrze, uwierzę ci. Tym razem... Ale wiedz, że nadal jestem na ciebie wściekła, tak, co nie!”";
			link.l1 = "Zasłużę na twoje przebaczenie, obiecuję.";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_1":
			dialog.text = "Cóż, kochasiu, powiedz mi, czego się dowiedziałeś. Czy było warto ryzykować moją łaską?";
			link.l1 = "Naprawdę nie potrafię stwierdzić, czy żartujesz, czy mówisz poważnie. Opłaciło się - chociaż nie widziałem gospodyni na własne oczy. Jest Azjatką, a jej imię to Belle Etoile - wspaniała gwiazda. Oczywiście to nie jest jej prawdziwe imię...";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_2";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_2":
			dialog.text = "„I dlatego musiałeś iść do burdelu? Nie mogłeś się tego dowiedzieć w karczmie? Ш: W mieście naprawdę nie rozmawiają o tym miejscu. Dlaczego? To dobre pytanie. Możesz zapytać samą Belle Etoile - wyjechała na Espanolę.”";
			link.l1 = "Nie mówi się o tym miejscu w mieście. Dlaczego? To dobre pytanie. Możesz zapytać samą Belle Etoile - wyjechała na Hispaniolę.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_3";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_3":
			dialog.text = " Tortuga nie była dla niej wystarczająca?";
			link.l1 = "„Handel, najwyraźniej, nie idzie tu dobrze. Nie zatrudnia zwykłych dziewczyn z portu, tylko bogato ubrane, wykształcone damy.”";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_4";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_4":
			dialog.text = "I dlaczego mieliby to zrobić?";
			link.l1 = "„To kolejne dobre pytanie. Tak czy inaczej, nasz mały ptaszek postanowił polecieć do Port-au-Prince, lenna de Mussaca. Ale pożyczka na to przedsięwzięcie miała zostać uzyskana od nie kogo innego jak Tyrex.”";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_5";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_5":
			dialog.text = "Chcę, aby ta historia jak najszybciej się skończyła. Nie traćmy czasu i obierzmy kurs na La Vega.";
			link.l1 = "Tak zrobimy.";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_1":
			dialog.text = "Jesteś odważnym człowiekiem, Charles, przyznaję to. Pojawiasz się tak swobodnie, z kamienną twarzą, jakby nic się nie stało.";
			link.l1 = "Mniemam, że któryś z członków załogi puścił parę z ust? Oczywiście bez kontekstu. Bo nic się naprawdę nie wydarzyło - przynajmniej nie to, co myślisz.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_2";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_2":
			dialog.text = "Cieszę się, że tego nie zaprzeczyłeś, Charles.";
			link.l1 = "Miałem ci wszystko powiedzieć, Helen.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_3";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_3":
			dialog.text = "Nie, Charles. Szczegóły mnie zbytnio nie interesują. Ale powody tak. Powiedz mi, czy coś jest ze mną nie tak?";
			link.l1 = "Zacznijmy od powodów. Dowiedziałem się, że na Tortudze są dwa burdele. Jeden jest dobrze znany. O drugim ludzie wiedzą, ale mało kto chce o nim mówić. Należy do azjatyckiej kobiety...";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_4";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_4":
			dialog.text = "Czy wymyślasz to na bieżąco?";
			link.l1 = "Dlaczego do diabła miałbym to zrobić, Helen?! Jeśli mi nie wierzysz, potwierdzą to na miejscu!";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_5";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_5":
			dialog.text = "Po pierwsze, powiedziałeś mi, żebym nie schodziła na ląd, więc nie ma mowy, żebym tam się dostała. Po drugie, kim, do diabła, myślisz, że jestem?! Nie zbliżę się do takiego miejsca! Po trzecie... po prostu idź dalej.";
			link.l1 = "Dobrze. Zdecydowałem się tam pójść, by zobaczyć Madame Étoile na własne oczy. To był mój jedyny zamiar, do diabła!";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_6";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_6":
			dialog.text = "Przypuszczam. Spotkałeś ją?";
			link.l1 = "Nie. Wyjechała do Hispanioli. Tutaj nie idzie jej najlepiej, więc postanowiła spróbować szczęścia w Port-au-Prince. Tam damy w jedwabiach, dobrze wykształcone, które pracują w jej przybytku, mogą przynieść jej więcej zysku niż na Tortudze...";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_7";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_7":
			dialog.text = "„Ubrani i wykształceni? Ho, cóż to życie może przynieść. Ale powinieneś ich lubić takimi, jakimi są.”";
			link.l1 = "Helen, przestań. Nic nie zrobiłem, by zasłużyć na twoje nieufność.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_8";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_8":
			dialog.text = "Prawda. Gdybyś próbował mnie oszukać, nie byłbyś tak spokojny. Ale powinieneś był mnie ostrzec o swoich planach, Charles.";
			link.l1 = "Masz rację, kochanie. Ale postanowiłam zaoszczędzić trochę czasu. Mój błąd.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_9";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_9":
			dialog.text = "Dobrze. Co teraz, obieramy kurs na Port-au-Prince?";
			link.l1 = "La Vega. Nie bądź zaskoczona, Helen. Madame Belle Etoile nie radzi sobie dobrze. Potrzebowała pożyczki, aby przenieść handel do Port-au-Prince, więc zdecydowała się pożyczyć ją od Marcusa. Jeśli się pospieszymy, możemy ją tam złapać. Więc nie traćmy ani minuty.";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_NaLaVega":
			DialogExit();
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) 
			{
				AddLandQuestMark(characterFromId("Terrax"), "questmarkmain");
				QuestSetCurrentNode("Terrax", "PZ1");
			}
			else 
			{
				AddLandQuestMark(characterFromId("Vensan"), "questmarkmain");
				QuestSetCurrentNode("Vensan", "PZ1");
			}
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			Island_SetReloadEnableGlobal("Tortuga", true);
			bQuestDisableMapEnter = false;
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				sld = CharacterFromID("Mary");
				AddPassenger(pchar, sld, false);
				Return_MaryOfficer();
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				sld = CharacterFromID("Helena");
				AddPassenger(pchar, sld, false);
				Return_HelenaOfficer();
			}
			if (!CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku")) AddQuestRecord("PZ", "31");
		break;
		
		case "PZ_KlemanLebren_7":
			dialog.text = "Nie mogę uwierzyć, że taki drań jak ty i twoja hołota nas pokonali!";
			link.l1 = "Ty...";
			link.l1.go = "PZ_KlemanLebren_8";
		break;
		
		case "PZ_KlemanLebren_8":
			dialog.text = "O, poznajesz mnie?";
			link.l1 = "Czy się spotkaliśmy?";
			link.l1.go = "PZ_KlemanLebren_9";
		break;
		
		case "PZ_KlemanLebren_9":
			dialog.text = "Co?! Czy sobie ze mnie kurwa żartujesz?!";
			link.l1 = "Nie pamiętam całego nieokrzesanego motłochu, którego spotykam. Lepiej powiedz nam, kto cię wysłał, by nas zabić. A może po prostu chcieli się ciebie pozbyć?";
			link.l1.go = "PZ_KlemanLebren_10";
		break;
		
		case "PZ_KlemanLebren_10":
			dialog.text = "Nie powiem nic komuś takiemu jak ty. Myślisz, że jesteś taki cholernie wspaniały! Zobaczymy, czy będziesz mógł to udowodnić ponownie po naszej małej przerwie tutaj.";
			link.l1 = "Szkoda. Jesteś odrażający, ale mogłem po prostu zostawić cię na innej wyspie. Teraz mogę jedynie wysłać cię na tamten świat.";
			link.l1.go = "PZ_KlemanLebren_11";
		break;
		
		case "PZ_KlemanLebren_11":
			pchar.questTemp.PZ.HeavyFrigateAbordage = true; // флаг - абордаж был
			
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PZ_Tichingitu_11":
			dialog.text = "Wzywałeś mnie, Kapitanie?";
			link.l1 = "Tak, kamracie. Zgłoś uszkodzenia.";
			link.l1.go = "PZ_Tichingitu_12";
		break;
		
		case "PZ_Tichingitu_12":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "There's a violent storm. The ship is creaking and cracking; it's wobbling badly.";
			link.l1 = "Tak, zauważyłem. Tichingitu, mój przyjacielu. Ja i "+sStr+"Zejdę na brzeg. Ty zostajesz na dowództwie. Zacznij natychmiast naprawy - dopóki burza nie ucichnie, nie ma sensu iść do stoczni. Poza tym, nie będziemy tu długo.";
			link.l1.go = "PZ_Tichingitu_13";
		break;
		
		case "PZ_Tichingitu_13":
			dialog.text = "Sprawię, że wszystko będzie wyglądało lepiej.";
			link.l1 = "Świetnie, dzięki. W takim razie bez obaw ruszamy do miasta.";
			link.l1.go = "PZ_Tichingitu_14";
		break;
		
		case "PZ_Tichingitu_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "PZ_PoP_Rain_4", -1);
		break;
		
		case "PZ_Matros_1":
			dialog.text = "Wielmożny Panie Kapitanie? To zaszczyt. Ale zazwyczaj w takich sytuacjach wzywasz Alonso. Czy wszystko w porządku, jeśli mogę zapytać?";
			link.l1 = "„Tak, wszystko w porządku. Ale nasz Alonso to bardziej człowiek od niszczenia, nie naprawiania czegokolwiek. W każdym tego słowa znaczeniu. Jak bardzo uszkodzony jest statek?”";
			link.l1.go = "PZ_Matros_2";
		break;
		
		case "PZ_Matros_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Alonso powiedziałby, że to kiepsko, nawet jeśli nie zatonęliśmy. Wspomniałeś o naprawach - zaczniemy je?";
			link.l1 = "Tak, zrób, co możesz. Ale nie planuj pracy na pełną skalę na dłuższy czas - wkrótce podniesiemy kotwicę, zaraz po tym, jak skończę swoje sprawy w mieście. Ja i "+sStr+"„nie będzie tam, więc w razie czego podejmuj wszystkie decyzje sam. Słuchaj Alonso we wszystkim.”";
			link.l1.go = "PZ_Matros_3";
		break;
		
		case "PZ_Matros_3":
			dialog.text = "Jak rozkażesz, Monsieur le Capitaine.";
			link.l1 = "Spocznij.";
			link.l1.go = "PZ_Matros_4";
		break;
		
		case "PZ_Matros_4":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			Island_SetReloadEnableGlobal("Hispaniola2", true);
			bQuestDisableMapEnter = false;
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "PZ_PoP_Rain_4", -1);
		break;
		
		case "PZ_AnriTibo_1":
			dialog.text = "Witaj, monsieur! Witaj w Port-au-Prince.";
			link.l1 = "„I dzień dobry panu, monsieur. Kim jesteś i czemu zawdzięczam to powitanie? Nie powiedziałbym, że mam nastrój na długą rozmowę w tym deszczu i po burzy.”";
			link.l1.go = "PZ_AnriTibo_2";
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_PoP_ChangShin", "Mei_Shin", "woman", "towngirl2", 30, FRANCE, 0, false, "quest"));
			FantomMakeCoolFighter(sld, 30, 80, 80, "blade_41", "", "", 0);
			sld.name = "Чанг";
			sld.lastname = "Шин";
			ChangeCharacterAddressGroup(sld, "PortPax_town", "goto", "goto16");
			EquipCharacterByItem(sld, "blade_41");
			GiveItem2Character(sld, "cirass8");
			EquipCharacterByItem(sld, "cirass8");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload8_back", "none", "", "", "", -1);
		break;
		
		case "PZ_AnriTibo_2":
			dialog.text = "O, nie zajmę ci dużo czasu, Monsieur de Maure.";
			link.l1 = "Czy my się znamy?";
			link.l1.go = "PZ_AnriTibo_3";
		break;
		
		case "PZ_AnriTibo_3":
			dialog.text = "„Och, nie, ale cały archipelag wie, kim jesteś. Ach, gdzie moje maniery! Henri Thibaut, do usług. Jestem posłańcem Jego Wysokości, Monsieur de Mussac. Jak tylko zauważył twój statek, kazał mi przywitać cię najcieplej, jak to możliwe, monsieur.”";
			link.l1 = "Cóż, to wiele wyjaśnia. Miło cię poznać, Monsieur Thibaut.";
			link.l1.go = "PZ_AnriTibo_4";
		break;
		
		case "PZ_AnriTibo_4":
			dialog.text = "„I przyjemność jest obopólna, Monsieur de Maure! Proszę za mną. To nie przystoi, aby człowiek o pańskim statusie i jego piękna towarzyszka byli zamknięci w tej śmierdzącej tawernie. Jego Lordowska Mość przydzielił wam dom w mieście i polecił mi pomóc wam we wszystkim. Proszę nie zapomnieć przekazać jego najlepszych życzeń Jego Ekscelencji Poincy.”";
			link.l1 = "Właściwie, moje zlecenie jest dyskretne. Wiecie, monsieur Thibaut, myślę, że...";
			link.l1.go = "PZ_AnriTibo_5";
		break;
		
		case "PZ_AnriTibo_5":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) StartInstantDialog("Helena", "PZ_HelenaPortPax1", "Quest\CompanionQuests\Longway.c");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) StartInstantDialog("Mary", "PZ_MaryPortPax1", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_HelenaPortPax1":
			dialog.text = "Charles. Rzadko proszę cię o cokolwiek, a tym bardziej przerywam, ale czy możemy skorzystać z ich oferty? Mam już dość moknięcia na deszczu. Czuję się też mdła i kręci mi się w głowie.";
			link.l1 = "Heh-heh, jesteś pewien, że to deszcz?";
			link.l1.go = "PZ_HelenaPortPax2";
		break;
		
		case "PZ_HelenaPortPax2":
			dialog.text = "Gryź się w język, Charles! Tak czy inaczej, chcę odpocząć. W dużym łóżku i bez fal.";
			link.l1 = "Dobrze. Wysuszymy się, odpoczniemy, a potem wrócimy do interesów.";
			link.l1.go = "PZ_AnriTibo_6";
		break;
		
		case "PZ_MaryPortPax1":
			dialog.text = "„Czy możemy odpocząć w tym domu? Nie czuję się dobrze, a także jestem... zmęczona, Charles. Tak, co nie?”";
			link.l1 = "Mary, kochanie, rozumiem, ale może powinniśmy pójść do tawerny. To wszystko źle pachnie, tak, co nie?";
			link.l1.go = "PZ_MaryPortPax2";
		break;
		
		case "PZ_MaryPortPax2":
			dialog.text = "Co mi się może stać? To nawet nie jest Tortuga.";
			link.l1 = "Tego się boję.";
			link.l1.go = "PZ_MaryPortPax3";
		break;
		
		case "PZ_MaryPortPax3":
			dialog.text = "„Proszę? W razie czego, ustawię obronę w pokoju - tak jak... wtedy, tak, co nie? Znasz mnie lepiej niż ktokolwiek inny, Charles, więc wiesz, że dam sobie radę.”";
			link.l1 = " Dobrze, dobrze. Mam nadzieję, że to nie będzie jak wtedy.";
			link.l1.go = "PZ_AnriTibo_6";
		break;
		
		case "PZ_AnriTibo_6":
			StartInstantDialog("Tibo", "PZ_AnriTibo_7", "Quest\CompanionQuests\Longway.c");
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) Return_MaryOfficer();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) Return_HelenaOfficer();
		break;
		
		case "PZ_AnriTibo_7":
			dialog.text = "Wiedziałem, że zmienisz zdanie, monsieur! Co do twoich obaw, doskonale rozumiem. Ale widzisz, Jego Ekscelencja Poincy i gubernator to starzy przyjaciele, a zatem jesteś mile widzianym gościem w naszym mieście, Monsieur de Maure!";
			link.l1 = "„Och, no cóż... Cóż, zatem zabierz nas do domu.”";
			link.l1.go = "PZ_AnriTibo_8";
		break;
		
		case "PZ_AnriTibo_8":
			dialog.text = "Oczywiście, monsieur! Proszę za mną.";
			link.l1 = "Dziękuję.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_GoToTiboHouse");
		break;
		
		case "PZ_AnriTibo_9":
			dialog.text = "Monsieur, gubernator czeka na ciebie. Poprosił, abyś przyszedł do niego, jak tylko będziesz mógł - chciałby porozmawiać z tobą na osobności.";
			link.l1 = "Czy on już o tym wie?";
			link.l1.go = "PZ_AnriTibo_10";
		break;
		
		case "PZ_AnriTibo_10":
			pchar.questTemp.PZ.PortPaxMayorTalk = true; // флаг для разговора с губернатором
			
			dialog.text = "Oczywiście, że wie! Dlatego na ciebie czeka. Niech twoja ukochana słodko śpi, podczas gdy ty pójdziesz spotkać się z monsieur de Mussac. Jakaś burza nie powstrzyma słynnego Charlesa de Maure, prawda? Ale Jego Lordowska Mość, jak rozumiesz, nie ma zbyt wiele czasu między spotkaniami...";
			link.l1 = "„Cóż, to prawda, Monsieur Thibaut.”";
			link.l1.go = "PZ_AnriTibo_11";
			
			for (i=1; i<=2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_PoP_Escort_"+i, "sold_fra_"+(rand(7)+1), "man", "man", sti(pchar.rank), FRANCE, -1, true, "soldier"));
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			}
		break;
		
		case "PZ_AnriTibo_11":
			StartInstantDialog("PZ_PoP_Escort_1", "PZ_AnriTibo_12", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_AnriTibo_12":
			dialog.text = "Pokażemy ci drogę, Kapitanie.";
			link.l1 = "„Och, więc mam nawet honorową eskortę... Cóż, prowadź drogę.”";
			link.l1.go = "PZ_AnriTibo_13";
		break;
		
		case "PZ_AnriTibo_13":
			DoQuestReloadToLocation("PortPax_town", "reload", "houseF1", "PZ_PoP_EscortToGuber");
		break;
		
		case "PZ_Longway_71":
			dialog.text = "Wielmożny Panie Kapitanie!";
			link.l1 = "„Longway! Na statek! Teraz!”";
			link.l1.go = "PZ_Longway_72";
		break;
		
		case "PZ_Longway_72":
			dialog.text = "Widziałem Chang Xinga!";
			link.l1 = "Co?! Gdzie? Kiedy? Czy ona jest na twoim statku?";
			link.l1.go = "PZ_Longway_73";
		break;
		
		case "PZ_Longway_73":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "„Nie! Tutaj, w mieście, Longway zobaczył ją z daleka. Nie ma czasu, by ją dogonić - wsiada na galeon, który właśnie odpłynął!”";
			link.l1 = "Dopadniemy galeon! Ale powiedz mi - widziałeś "+sStr+"gdziekolwiek?";
			link.l1.go = "PZ_Longway_74";
		break;
		
		case "PZ_Longway_74":
			dialog.text = "Nie! Czy coś się stało?";
			link.l1 = "Tak, coś się stało! Ona jest w niebezpieczeństwie! Widziałeś siostrzeńca Levasseura? Nazywa się Henri Thibaut! Wredny, chudy, długowłosy młodzieniec ze śmiesznym wąsem!";
			link.l1.go = "PZ_Longway_75";
		break;
		
		case "PZ_Longway_75":
			dialog.text = "(po mandaryńsku) Nie musisz mówić o śmiesznych wąsach, Kapitanie... (po łamanym francusku) Widziałem go! On i najemnicy również weszli na ten sam galeon.";
			link.l1 = "Pogońmy za nim natychmiast!";
			link.l1.go = "PZ_Longway_76";
		break;
		
		case "PZ_Longway_76":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Twoja łajba jest w opłakanym stanie, Wielmożny Panie Kapitanie!";
			link.l1 = "Nie obchodzi mnie to! "+sStr+"Życie jest na szali!";
			link.l1.go = "PZ_Longway_77";
		break;
		
		case "PZ_Longway_77":
			if (CheckAttribute(pchar, "questTemp.PZ.LongwayMayfang"))
			{
				dialog.text = "Moja... 'Twoja Meifeng' nas przez to przeprowadzi!";
				link.l1 = "O, na pewno! Pośpiesz się!";
				link.l1.go = "PZ_Longway_78";
			}
			else
			{
				dialog.text = "Nie rzucaj nas w samobójczy atak. Użyj statku, który dałeś mi wcześniej!";
				link.l1 = "Dobry pomysł, Longway! Pospieszmy się!";
				link.l1.go = "PZ_Longway_78";
			}
		break;
		
		case "PZ_Longway_78":
			DialogExit();
			chrDisableReloadToLocation = false;
			Island_SetReloadEnableGlobal("Hispaniola2", false);
			LocatorReloadEnterDisable("PortPax_town", "gate_back", true);
			SetCurrentTime(15, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			pchar.GenQuest.AbordageInStorm = true;	//Разрешить абордаж во время шторма
			SetLocationCapturedState("PortPax_town", false);

			LAi_LoginInCaptureTown(npchar, false);
			AddPassenger(pchar, npchar, false);
			Return_LongwayOfficer();
			
			if (GetCharacterIndex("Tichingitu") != -1)
			{
				sld = characterFromId("Tichingitu");
				AddPassenger(pchar, sld, false);
				Return_TichingituOfficer();
			}
			
			PChar.quest.PZ_PoP_Pogonya.win_condition.l1 = "location";
			PChar.quest.PZ_PoP_Pogonya.win_condition.l1.location = "Hispaniola2";
			PChar.quest.PZ_PoP_Pogonya.win_condition = "PZ_PoP_Pogonya";
			
			/*sld = GetCharacter(NPC_GenerateCharacter("PZ_ShipStasis", "panhandler_6", "man", "man", sti(pchar.rank), PIRATE, -1, false, "quest"));
			SetSPECIAL(sld, 1, 1, 1, 1, 1, 1, 1);
			SeaAI_SwapShipsAttributes(pchar, sld);
			if (CheckAttribute(pchar, "questTemp.PZ.LongwayMayfang"))	//Мейфенг
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_MAYFANG, true, pchar);
				pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS20;
				pchar.Ship.name = "Meifeng";
			}
			if (CheckAttribute(pchar, "questTemp.PZ.LongwayElCasador"))	//Эль Касадор
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_ELCASADOR, true, pchar);
				pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS32;
				pchar.Ship.name = "El Casador";
			}
			if (CheckAttribute(pchar, "questTemp.PZ.LongwayTorero"))	//Тореро
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_POLACRE_QUEST, true, pchar);
				pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS24;
				pchar.Ship.name = "Torero";
			}
			if (CheckAttribute(pchar, "questTemp.PZ.LongwaySchoonerW"))	//Военная шхуна
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_SCHOONER_W, true, pchar);
				pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS12;
				pchar.Ship.name = "Aztec";
			}
			if (CheckAttribute(pchar, "questTemp.PZ.LongwayBrig"))	//Бриг
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_BRIG, true, pchar);
				pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS16;
				pchar.Ship.name = "Aztec";
			}
			if (CheckAttribute(pchar, "questTemp.PZ.LongwayCorvette"))	//Корвет
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_CORVETTE, true, pchar);
				pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS16;
				pchar.Ship.name = "Aztec";
			}
			if (CheckAttribute(pchar, "questTemp.PZ.LongwayPolacre"))	//Полакр
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_POLACRE, true, pchar);
				pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS16;
				pchar.Ship.name = "Aztec";
			}
			if (CheckAttribute(pchar, "questTemp.PZ.LongwayXebek"))	//Шебека
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_XebekVML, true, pchar);
				pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS16;
				pchar.Ship.name = "Aztec";
			}
			if (CheckAttribute(pchar, "questTemp.PZ.LongwayBrigantine"))	//Бригантина
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_BRIGANTINE, true, pchar);
				pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS16;
				pchar.Ship.name = "Aztec";
			}
			SetBaseShipData(pchar);*/
			SeaAI_SwapShipsAttributes(pchar, CharacterFromID("PZ_ShipStasis"));
			AddCharacterGoodsSimple(pchar, GOOD_GRAPES, 300);
			AddCharacterGoodsSimple(pchar, GOOD_BOMBS, 200);
			AddCharacterGoodsSimple(pchar, GOOD_POWDER, 350);
			AddCharacterGoodsSimple(pchar, GOOD_FOOD, 150);
			AddCharacterGoodsSimple(pchar, GOOD_RUM, 50);
			AddCharacterGoodsSimple(pchar, GOOD_FOOD, 700);
			//SetCrewQuantityFull(pchar);
			pchar.ship.HP = sti(pchar.ship.HP) / 2;
			pchar.Ship.Crew.Quantity = sti(pchar.ship.Crew.Quantity) / 2;
			AddCrewMorale(Pchar, 100);
			ChangeCrewExp(pchar, "Sailors", 100);
			ChangeCrewExp(pchar, "Cannoners", 100);
			ChangeCrewExp(pchar, "Soldiers", 100);
			
			//Вражина
			sld = characterFromId("PZ_RobertMartin");
			sld.nation = PIRATE;
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				GiveItem2Character(sld, "blade_31");
				EquipCharacterByItem(sld, "blade_31");
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				GiveItem2Character(sld, "pirate_cutlass");
				EquipCharacterByItem(sld, "pirate_cutlass");
			}
			FantomMakeCoolSailor(sld, SHIP_GALEON_L, "Voltigeur", CANNON_TYPE_CANNON_LBS16, 50, 50, 50);
			sld.AlwaysEnemy = true;
			sld.AlwaysSandbankManeuver = true;
			sld.DontRansackCaptain = true;
			sld.ShipHideImmortal = 800;
			Group_FindOrCreateGroup("PZ_RM_Attack");
			Group_SetType("PZ_RM_Attack", "pirate");
			Group_AddCharacter("PZ_RM_Attack", "PZ_RobertMartin");
			Group_SetGroupCommander("PZ_RM_Attack", "PZ_RobertMartin");
			Group_SetTaskAttack("PZ_RM_Attack", PLAYER_GROUP);
			Group_SetAddress("PZ_RM_Attack", "Hispaniola2", "quest_ships", "Quest_ship_1");
			Ship_SetTaskAttack(SECONDARY_TASK, sti(sld.index), sti(pchar.index));
		break;
		
		case "PZ_RobertMartin_8":
			dialog.text = "Znowu ty... Wiedziałem, że powinienem był odmówić i pozwolić komuś innemu zająć się twoją dziewczyną.";
			link.l1 = " gdzie ona jest?! Powiedz mi! Nie... Zamknij gębę. Będziesz mówić tylko w ładowni, w kajdanach! Słyszysz mnie?!";
			link.l1.go = "PZ_RobertMartin_9";
		break;
		
		case "PZ_RobertMartin_9":
			dialog.text = "...";
			link.l1 = "Jej ostrze. Jeśli nie zaczniesz śpiewać teraz, pokroję cię nim na kawałki.";
			link.l1.go = "PZ_RobertMartin_10";
			/*RemoveAllCharacterItems(npchar, true);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) GiveItem2Character(pchar, "blade_31");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) GiveItem2Character(pchar, "pirate_cutlass");*/
		break;
		
		case "PZ_RobertMartin_10":
			dialog.text = "Ty... ty jesteś szalony do diabła!..";
			link.l1 = "Teraz zobaczysz moją nieprzyjemną stronę...";
			link.l1.go = "PZ_RobertMartin_11";
		break;
		
		case "PZ_RobertMartin_11":
			DialogExit();
			LAi_ReloadBoarding();
		break;
		
		case "PZ_RobertMartin_13":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "To wszystko?";
			link.l1 = "Znowu pytam! Gdzie jest "+sStr+"? ! Gdzie jest ta Chińska kobieta?! Gdzie jest Henri Thibaut?!";
			link.l1.go = "PZ_RobertMartin_14";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "beatmarten_idle_1", "", 0.3);
		break;
		
		case "PZ_RobertMartin_14":
			dialog.text = "(pluje krwią) Bijesz jak dziewczyna.";
			link.l1 = "Ty suko! Wydobędę z ciebie każde słowo!";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DoprosRobertMartin_Trum_6");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "beatmarten_idle_1", "", 0.3);
		break;
		
		case "PZ_RobertMartin_16":
			dialog.text = "Płaczliwe. Chociaż... Powiem to. Dlaczego nie, ha ha. Wszyscy są na innym statku, prosto na drogę do Tortugi. Jesteś za późno.";
			link.l1 = "Jeśli choćby włos spadnie z jej głowy...";
			link.l1.go = "PZ_RobertMartin_17";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "beatmarten_idle_2", "", 0.3);
			locCameraFromToPos(0.27, 14.52, -3.38, true, -1.80, 9.90, -1.76);
		break;
		
		case "PZ_RobertMartin_17":
			dialog.text = "A czyja to wina?! Zabiłeś Edgardo Sottę! Po raz pierwszy w życiu Levasseur zapragnął dziewczyny, a nie dostał jej od razu! Pierwszy raz nasza załoga nie wykonała jego bezpośredniego rozkazu! Ten człowiek potrafi być tak przerażający jak sam diabeł...";
			link.l1 = "Wtedy będę straszniejszy niż sam diabeł i zgotuję ci małe osobiste piekło, jeśli mi nie powiesz, czego chcę się dowiedzieć, słyszysz mnie?!";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) link.l1.go = "PZ_RobertMartin_Mary_1";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) link.l1.go = "PZ_RobertMartin_Helena_1";
		break;
		
		case "PZ_RobertMartin_Mary_1":
			dialog.text = "Nie obchodzi mnie twoje cierpienie - i tak jestem już martwy, sądząc po twoich szalonych oczach. Muszę jednak przyznać ci trochę racji, de Maure.";
			link.l1 = "O czym, do diabła, mówisz?";
			link.l1.go = "PZ_RobertMartin_Mary_2";
		break;
		
		case "PZ_RobertMartin_Mary_2":
			dialog.text = "Levasseur woli blondynki. Ale zawsze bardziej podobały mi się rude, tak jak ty, hehehe... Co za pikantna zdobycz!";
			link.l1 = "„Masz rację, nie przeżyjesz dnia...”";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DoprosRobertMartin_Trum_7");
		break;
		
		case "PZ_RobertMartin_Helena_1":
			dialog.text = "Nie obchodzi mnie, czego chcesz. Ale powiem ci, czego chce Levasseur - ładne blondynki, ha ha ha ha ha ha ha ha ha! Najpierw, on ma ją...";
			link.l1 = "A-AH!";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DoprosRobertMartin_Trum_7");
		break;
		
		case "PZ_RobertMartin_19":
			dialog.text = "Piskliwie wrzeszczeć i bić nieuzbrojonego człowieka - żałosne. To wszystko, co potrafisz. Przegrałeś, de Maure! Chcesz wiedzieć, kiedy naprawdę przegrałeś, ty żałosny kretynie?";
			link.l1 = "Oświeć mnie. Ale jeśli mnie nie zaimponujesz, stracisz palec. Albo ucho. Albo te zgniłe zęby z twojej śmierdzącej gęby. A może coś innego. Wybór należy do ciebie...";
			link.l1.go = "PZ_RobertMartin_20";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "beatmarten_idle_3", "", 0.3);
			//locCameraFromToPos(-1.75, 14.14, -0.31, true, 1.26, 11.00, -4.00);
			locCameraFromToPos(-2.47, 14.15, -0.01, true, 1.23, 10.92, -3.60);
		break;
		
		case "PZ_RobertMartin_20":
			dialog.text = "„Heh-heh, mam coś, czego ty nie masz. Myślisz, że Levasseur nie wiedział, co ten stary lis Poincy przeciw niemu knuł? Francois wie wszystko, wszystko! Nawet baronowie Bractwa nie ośmielają się mu przeciwstawić. A ty, mądralku, to zrobiłeś. Ale...”";
			link.l1 = "Co takiego?! Nie waż się tego przeciągać!! Zacznij mówić, albo zacznę łamać ci palce jeden po drugim!";
			link.l1.go = "PZ_RobertMartin_21";
		break;
		
		case "PZ_RobertMartin_21":
			dialog.text = "Ha-ha, odważny Kapitanie de Maure! Ale dobrze. Ja, Henri i żółtoskóra kobieta uznaliśmy, że najlepiej będzie zniszczyć cię tutaj. I zwalić winę na Tyreksa, żeby starzy głupcy w Bractwie rozpoczęli między sobą kolejną wojnę! A może na de Mussaca - wtykał nos tam, gdzie nie trzeba... Wiesz, wszyscy się ze mnie śmiali, że płynąłem galeonem, ale przetrwał burzę bez problemu, w przeciwieństwie do twojej kupy złomu.";
			link.l1 = "Dość! Gdzie Levasseur trzyma swoje ofiary?";
			link.l1.go = "PZ_RobertMartin_22";
		break;
		
		case "PZ_RobertMartin_22":
			dialog.text = "Więc wiesz o jego sekretnym miejscu, lochu? O tak, on jest prawdziwym władcą lochów, ha-ha-ha! Ale czy naprawdę możesz mu sprostać? Wątpię. Chcesz pokonać bestię? To sam stań się bestią. Zobacz, czy potrafisz złamać mnie tak, jak Francois łamie te dziewczyny. Jak wkrótce złamie twoją...";
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
			{
				link.l1 = "Alo-o-on-s-o-o!!!";
				link.l1.go = "PZ_RobertMartin_23";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "PZ_LongwayKaznDialog_1";
			}
		break;
		
		case "PZ_RobertMartin_23":
			DialogExit();
			LAi_SetStayType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
			LAi_Fade("PZ_AlonsoKazn", "");
		break;
		
		case "PZ_LongwayKaznDialog_1":
			DialogExit();
			LAi_SetStayType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
			DoQuestCheckDelay("PZ_LongwayKazn_1", 1.0);
		break;
		
		case "PZ_LongwayKaznDialog_2":
			dialog.text = "";
			link.l1 = "Powiedziałem ci, żebyś się nie fatygował, do cholery!..";
			link.l1.go = "PZ_LongwayKaznDialog_3";
		break;
		
		case "PZ_LongwayKaznDialog_3":
			DialogExit();
			LAi_SetStayType(pchar);
			LAi_Fade("PZ_LongwayKazn_3", "");
		break;
		
		case "PZ_LongwayKaznDialog_4":
			dialog.text = "Pozwól mi, Wielmożny Panie Kapitanie.";
			link.l1 = "Longway? Pozwolić na co?";
			link.l1.go = "PZ_LongwayKaznDialog_5";
		break;
		
		case "PZ_LongwayKaznDialog_5":
			dialog.text = "„Biali ludzie dręczą ciało. Moi ludzie wiedzą, że najpierw trzeba dręczyć nieszczęsną duszę, doprowadzić do szaleństwa przez odrobinę stałego bólu. Nie można po prostu wziąć i dręczyć bez przygotowania. Zawsze wymaga to specjalnego podejścia. Tutaj potrzeba... Lynchy'ego.”";
			link.l1 = "Lynchy?";
			link.l1.go = "PZ_LongwayKaznDialog_6";
		break;
		
		case "PZ_LongwayKaznDialog_6":
			dialog.text = "Tak, Wielmożny Panie Kapitanie. Śmierć przez tysiąc cięć.";
			link.l1 = "Zwaryowałeś?! Uderzyłeś się w głowę? O jakiej śmierci bredzisz?! Muszę go najpierw zmusić do mówienia!";
			link.l1.go = "PZ_LongwayKaznDialog_7";
		break;
		
		case "PZ_LongwayKaznDialog_7":
			dialog.text = "„Longway wie, Wielmożny Panie Kapitanie. Wie, co zrobić. Ten drań powie mi wszystko. Daj mi czas...”";
			link.l1 = "Czas? Czas?! Dobrze... Zrób to. Tylko błagam, wydobądź z niego wszystko, wszystko!";
			link.l1.go = "PZ_LongwayKaznDialog_8";
		break;
		
		case "PZ_LongwayKaznDialog_8":
			DialogExit();
			LAi_SetActorType(npchar);
			CharacterTurnByChr(npchar, CharacterFromID("PZ_RobertMartinPlennik"));
			LAi_SetStayType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
			LAi_FadeToBlackStart();
			DoQuestCheckDelay("PZ_LongwayKazn_4", 1.5);
		break;
		
		case "PZ_LongwayKaznDialog_9":
			dialog.text = "Zabij mnie, po prostu zabij, proszę... Czego jeszcze ode mnie chcesz?!";
			link.l1 = "Nic więcej. Zamknij gębę i zdychaj.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayKazn_11");
		break;//
		
		case "PZ_LongwayKaznDialog_9_1":
			DialogExit();
			sld = CharacterFromID("PZ_RobertMartinPlennik")
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Shot", "1", 1.5);
			DoQuestCheckDelay("PZ_LongwayKazn_9", 0.9);
		break;
		
		case "PZ_LongwayKaznDialog_10":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Shot", "1", 1.5);
			DoQuestCheckDelay("PZ_LongwayKazn_9", 0.9);
		break;
		
		case "PZ_LongwayKaznDialog_11":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Czysty strzał, Wielmożny Panie Kapitanie. Mówiłem, że to zadziała.";
			link.l1 = "„Tak. Dobra robota. A więc, do lochów. Stawiajcie wszystkie żagle! Kurs na Tortugę. I niech Bóg pomoże temu przeklętemu miastu, jeśli choć jeden włos spadnie z głowy”"+sStr+"   głowa...";
			link.l1.go = "PZ_LongwayKaznDialog_12";
		break;
		
		case "PZ_LongwayKaznDialog_12":
			DialogExit();
			ResetSound();
			chrDisableReloadToLocation = false;
			EndQuestMovie();
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			locCameraTarget(PChar);
			locCameraFollow();
			AddQuestRecord("PZ", "39");
			
			LAi_SetPlayerType(pchar);
			npchar.greeting = "Longway";
			Return_LongwayOfficer();
			
			bQuestDisableMapEnter = false;
			Island_SetReloadEnableGlobal("Hispaniola2", true);
			Island_SetReloadEnableLocal("Hispaniola2", "reload_2", true)
			Island_SetGotoEnableLocal("Hispaniola2", "reload_2", true);
			Island_SetReloadEnableLocal("Hispaniola2", "reload_3", true)
			Island_SetGotoEnableLocal("Hispaniola2", "reload_3", true);
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			DeleteAttribute(pchar,"questTemp.TimeLock");
			LocatorReloadEnterDisable("LaVega_ExitTown", "reload1_back", false);
			LocatorReloadEnterDisable("PortPax_town", "gate_back", false);
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			LAi_LocationFightDisable(&Locations[FindLocation("PortPax_town")], false);
			DeleteAttribute(pchar, "GenQuest.AbordageInStorm");
			
			PChar.quest.PZ_Etap6_Start.win_condition.l1 = "location";
			PChar.quest.PZ_Etap6_Start.win_condition.l1.location = "Tortuga";
			PChar.quest.PZ_Etap6_Start.win_condition = "PZ_Etap6_Start";
			locations[FindLocation("Shore58")].DisableEncounters = true;
			SetTimerCondition("PZ_Etap6_Opozdal", 0, 0, 7, false);
			DelMapQuestMarkCity("PortPax");
			AddMapQuestMarkShore("Shore58", true);
			pchar.questTemp.PZ_FlagMartinInfo = true;
			
			// Компаньон-заглушка входит в состав нашей экскадры
			sld = CharacterFromID("PZ_ShipStasis");
			SetCompanionIndex(pchar, -1, sti(sld.index));
			SetCharacterRemovable(sld, true);
			SetShipRemovable(sld, true);
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.quest.meeting = true;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			sld.Dialog.CurrentNode = "hired";
			sld.Payment = true;
			sld.ship.HP = sti(sld.ship.HP) / 2;
			
			//
			makearef(arTmp, pchar.questTemp.PZ_PoP_More.ShipPos);
			QuestToSeaLogin_Prepare(stf(arTmp.x), stf(arTmp.z), arTmp.Island);
			DeleteAttribute(pchar, "questTemp.PZ_PoP_More.ShipPos");
			QuestToSeaLogin_Launch();
		break;
		
		case "PZ_AlonsoKaznDialog_1":
			dialog.text = "Dios mio... Nigdy cię nie widziałem ani nie słyszałem... w ten sposób, señor Kapitanie.";
			link.l1 = "Jest cały twój, Alonso! Śmiało, pokaż mi, co Święta Inkwizycja robi z hugenotami i ich poplecznikami... A ja będę patrzył... Potem możesz zrobić z nim, co tylko zechcesz.";
			link.l1.go = "PZ_AlonsoKaznDialog_2";
		break;
		
		case "PZ_AlonsoKaznDialog_2":
			dialog.text = "Tak jest, señor Kapitanie...";
			link.l1 = "";
			link.l1.go = "PZ_AlonsoKaznDialog_3";
		break;
		
		case "PZ_AlonsoKaznDialog_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, CharacterFromID("PZ_RobertMartinPlennik"), "PZ_AlonsoKazn_2", -1);
		break;
		
		case "PZ_AlonsoKaznDialog_4":
			dialog.text = "To nie potrwa długo, señor Capitán...";
			link.l1 = "Zrób to, na miłość boską!";
			link.l1.go = "PZ_AlonsoKaznDialog_5";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_RobertMartinPlennik"));
			LAi_ActorAnimation(npchar, "Barman_idle", "1", 5);
		break;
		
		case "PZ_AlonsoKaznDialog_5":
			DialogExit();
			LAi_SetStayType(pchar);
			LAi_FadeToBlackStart();
			DoQuestCheckDelay("PZ_AlonsoKazn_3", 1.5);
		break;
		
		case "PZ_AlonsoKaznDialog_6":
			dialog.text = "Wstawaj, ty kawałku gówna. Wstawaj, powiedziałem!";
			link.l1 = "Czy on nie żyje? Martwy?!";
			link.l1.go = "PZ_AlonsoKaznDialog_7";
			CharacterTurnByChr(npchar, CharacterFromID("PZ_RobertMartinPlennik"));
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
		break;
		
		case "PZ_AlonsoKaznDialog_7":
			dialog.text = "Wygląda na to, kap...";
			link.l1 = "Co do diabła zrobiłeś?!";
			link.l1.go = "PZ_AlonsoKaznDialog_8";
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);
		break;
		
		case "PZ_AlonsoKaznDialog_8":
			dialog.text = "Kto by pomyślał, że ten głupiec okaże się takim słabeuszem! Nawet spodnie sobie poplamił, ten brudny drań! Niech to szlag, ogień był niepotrzebny...";
			link.l1 = "Ty... No cóż, za burtę z nim, na pożarcie rybom. Obierz kurs na Tortugę. Jeśli będzie trzeba, rozbiorę ją cegła po cegle - najpierw La Roche, a potem... Potem niech Bóg mi pomoże, jeśli jej nie znajdę żywej...";
			link.l1.go = "PZ_AlonsoKaznDialog_9";
		break;
		
		case "PZ_AlonsoKaznDialog_9":
			DialogExit();
			ResetSound();
			chrDisableReloadToLocation = false;
			EndQuestMovie();
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			locCameraTarget(PChar);
			locCameraFollow();
			AddQuestRecord("PZ", "38");
			
			LAi_SetPlayerType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "", "", "", "", -1);
			npchar.lifeday = 0;
			npchar.location = "None";
			
			bQuestDisableMapEnter = false;
			Island_SetReloadEnableGlobal("Hispaniola2", true);
			Island_SetReloadEnableLocal("Hispaniola2", "reload_2", true)
			Island_SetGotoEnableLocal("Hispaniola2", "reload_2", true);
			Island_SetReloadEnableLocal("Hispaniola2", "reload_3", true)
			Island_SetGotoEnableLocal("Hispaniola2", "reload_3", true);
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			DeleteAttribute(pchar,"questTemp.TimeLock");
			LocatorReloadEnterDisable("LaVega_ExitTown", "reload1_back", false);
			LocatorReloadEnterDisable("PortPax_town", "gate_back", false);
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			LAi_LocationFightDisable(&Locations[FindLocation("PortPax_town")], false);
			DeleteAttribute(pchar, "GenQuest.AbordageInStorm");
			
			PChar.quest.PZ_Etap6_Start.win_condition.l1 = "location";
			PChar.quest.PZ_Etap6_Start.win_condition.l1.location = "Tortuga";
			PChar.quest.PZ_Etap6_Start.win_condition = "PZ_Etap6_Start";
			locations[FindLocation("Shore58")].DisableEncounters = true;
			SetTimerCondition("PZ_Etap6_Opozdal", 0, 0, 7, false);
			DelMapQuestMarkCity("PortPax");
			AddMapQuestMarkShore("Shore58", true);
			
			// Компаньон-заглушка входит в состав нашей экскадры
			sld = CharacterFromID("PZ_ShipStasis");
			SetCompanionIndex(pchar, -1, sti(sld.index));
			SetCharacterRemovable(sld, true);
			SetShipRemovable(sld, true);
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.quest.meeting = true;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			sld.Dialog.CurrentNode = "hired";
			sld.Payment = true;
			sld.ship.HP = sti(sld.ship.HP) / 2;
			
			//
			makearef(arTmp, pchar.questTemp.PZ_PoP_More.ShipPos);
			QuestToSeaLogin_Prepare(stf(arTmp.x), stf(arTmp.z), arTmp.Island);
			DeleteAttribute(pchar, "questTemp.PZ_PoP_More.ShipPos");
			QuestToSeaLogin_Launch();
		break;
		
		case "PZ_Norman1":
			dialog.text = "W końcu. Ten tron jest teraz mój. Na tej skale zbuduję...";
			link.l1 = "Co do cholery... Serio?";
			link.l1.go = "PZ_Norman2";
		break;
		
		case "PZ_Norman2":
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
			else sTemp = "Shark";
			
			dialog.text = "... mój Kościół. Jestem teraz Papieżem Rzymu. Nie przysięgaj w Domu Bożym!";
			link.l1 = "A tutaj myślałem... No cóż, Wasza Świętobliwość, czy bylibyście łaskawi powiedzieć swoim wiernym, gdzie "+sTemp+"teraz jest?";
			link.l1.go = "PZ_Norman3";
		break;
		
		case "PZ_Norman3":
			dialog.text = "On wyruszył na świętą misję. Nową krucjatę, jeśli można to tak ująć. Zamierza zabrać pieniądze od niegodziwców i przynieść je do mnie.";
			link.l1 = "Do ciebie, prawda. Czy wspomniał, kiedy wróci?";
			link.l1.go = "PZ_Norman4";
		break;
		
		case "PZ_Norman4":
			NextDiag.TempNode = "PZ_NormanBlock";
			
			dialog.text = "Za miesiąc. Może trochę później. Czekam na jego powrót, razem z resztą naszej trzódki.";
			link.l1 = "Więc naprawdę jest na morzu. Lepiej odejdę, zanim złapię to, co masz.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_NormanBlock":
			NextDiag.TempNode = "PZ_NormanBlock";
			
			dialog.text = "Oczyść ich wszystkich w świętych płomieniach...";
			link.l1 = "Twoja głowa potrzebuje oczyszczenia...";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaIslaTesoro1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				// ох, какой же костыль, м-м-мать...
				sld = characterFromId("Mary");
				if (sld.location != "Pirates_townhall")
				{
					if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "with Marcus";
					else sTemp = "with Steve";
					
					dialog.text = "Charles! Co mogę dla ciebie zrobić?";
					link.l1 = "Cześć, Helen! Chcę z tobą porozmawiać "+sTemp+". Czy on jest na górze? Czy jest w tawernie?";
					link.l1.go = "PZ_HelenaIslaTesoroGood1";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
					else sTemp = "Steve";
					
					dialog.text = "Charles! I... Ach, cóż za miła niespodzianka. Co mogę dla was zrobić?";
					link.l1 = "„Witaj, Helen. Gdzie jest ”"+sTemp+"?";
					link.l1.go = "PZ_HelenaIslaTesoroGoodMaryHere1";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
				else sTemp = "Shark";
				
				dialog.text = TimeGreeting()+", Charles. Co cię tu sprowadza?";
				link.l1 = TimeGreeting()+", Helen. Szukam "+sTemp+" Czy wiesz, gdzie on jest?";
				link.l1.go = "PZ_HelenaIslaTesoroBad1";
			}
		break;
		
		case "PZ_HelenaIslaTesoroGood1":
			dialog.text = "Nie ma go, ale obawiam się, że długo nie wróci - wypłynął na morze, ściśle mówiąc.";
			link.l1 = "Cholera. Czy coś się stało? Czy powiedział, kiedy wróci?";
			link.l1.go = "PZ_HelenaIslaTesoroGood2";
		break;
		
		case "PZ_HelenaIslaTesoroGood2":
			dialog.text = "Nie zrobił tego, ale to nic poważnego - ma dobre tropy, jak zwykle. Zazwyczaj wraca po miesiącu, dwóch najwyżej. Wiem, jak to jest, czasem sam tęsknię za pokładem statku...";
			link.l1 = "„Zawsze możesz wypłynąć w morze. Byłoby miło zrobić to kiedyś razem - ty na 'Tęczy', ja na...”";
			link.l1.go = "PZ_HelenaIslaTesoroGood3";
		break;
		
		case "PZ_HelenaIslaTesoroGood3":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodBlock";
			
			dialog.text = "„Mogłoby. Ale twoja... dziewczyna może tego nie docenić. A ja nie chcę być trzecim kołem u wozu.”";
			link.l1 = "„Ekhm, przepraszam, Helen, nie chciałem cię urazić. Dzięki za rozmowę. Do zobaczenia później.”";
			link.l1.go = "Exit";
		break;
		
		// Синистра, не забудь снять эту заглушку и вернуть дефолтную после этого этапа, плиз
		case "PZ_HelenaIslaTesoroGoodBlock":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodBlock";
			
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
			else sTemp = "Steve";
			
			dialog.text = "Charles, wróciłeś. Czy mogę ci jeszcze w czymś pomóc?";
			link.l1 = "Nie, dziękuję, Helen. Po prostu chciałem sprawdzić, czy "+sTemp+"pojawił się.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaIslaTesoroBad1":
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Tyrex";
			else sTemp = "Steven";
			
			dialog.text = "Byłbym zaskoczony, gdybyś przyszedł mnie szukać. Co do "+sTemp+" , jest na morzu.";
			link.l1 = "O, naprawdę? Powiedział ci, kiedy wróci?";
			link.l1.go = "PZ_HelenaIslaTesoroBad2";
		break;
		
		case "PZ_HelenaIslaTesoroBad2":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroBadBlock";
			
			dialog.text = "Najwyraźniej zmęczyło go prowadzenie tego szamba i musi przypominać sobie, że wciąż jest kapitanem statku. Nie pierwszy raz. Zwykle wraca po miesiącu, może półtora.";
			link.l1 = "Cholera, czyli baronowie nie zawsze siedzą tak spokojnie? Dziękuję, Helen. Do widzenia.";
			link.l1.go = "Exit";
		break;
		
		// Синистра, не забудь снять эту заглушку и вернуть дефолтную после этого этапа, плиз
		case "PZ_HelenaIslaTesoroBadBlock":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroBadBlock";
			
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
			else sTemp = "Steven";
			
			dialog.text = ""+sTemp+"Charles wciąż nie wrócił";
			link.l1 = "Rozumiem, tylko sprawdzałem.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaIslaTesoroGoodMaryHere1":
			dialog.text = "„Jest wolnym człowiekiem, prawda? Może wypłynąć na morze, kiedy tylko zechce.”";
			link.l1 = "Oczywiście, że może. Więc, gdzie on jest?";
			link.l1.go = "PZ_HelenaIslaTesoroGoodMaryHere2";
		break;
		
		case "PZ_HelenaIslaTesoroGoodMaryHere2":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodMaryHereBlock";
			
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
			else sTemp = "the Shark";
			
			dialog.text = "Ale Charles, jeśli nie ma go na wyspie, to pewnie poszedł plądrować Hiszpanów. A teraz, jeśli pozwolisz, mam wiele do zrobienia. Zaglądaj od czasu do czasu – zazwyczaj, "+sTemp+"wraca za około miesiąc, czasami trochę później.";
			link.l1 = "Dobrze, Helen, dziękuję. Będziemy zajęci.";
			link.l1.go = "Exit";
		break;
		
		// Синистра, не забудь снять эту заглушку и вернуть дефолтную после этого этапа, плиз
		case "PZ_HelenaIslaTesoroGoodMaryHereBlock":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodMaryHereBlock";
			
			dialog.text = "Nie jestem teraz w nastroju. Może wróć innym razem, Charles?";
			link.l1 = "„Oczywiście, Helen. Przepraszam, że przeszkadzam. Trzymaj się.”";
			link.l1.go = "Exit";
		break;
		
		case "PZ_Longway_81":
			if (CheckAttribute(pchar, "questTemp.PZ_FlagMartinInfo"))
			{
				dialog.text = "Jesteśmy na miejscu, Wielmożny Panie Kapitanie. Pamiętasz drogę?";
				link.l1 = "Oczywiście, Longway. Miejmy tylko nadzieję, że nie zgubimy tego w tym przeklętym lochu...";
				link.l1.go = "PZ_Longway_FlagMartinInfo_1";		//Sinistra
			}
			else
			{
				dialog.text = "Jesteśmy na miejscu, Wielmożny Panie Kapitanie. Czy masz plan?";
				link.l1 = "Jeszcze nad tym pracuję... Dlaczego, masz coś na myśli?";
				link.l1.go = "PZ_Longway_NotMartinInfo_1";		//Rebbebion
			}
			DelLandQuestMark(npchar);
			LAi_SetCheckMinHP(npchar, 1, true, "");		//На 6 эпизод даём Лонгвею бессмертие
			
			LocatorReloadEnterDisable("Tortuga_town", "houseS4", false);
		break;
		
		case "PZ_Longway_NotMartinInfo_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "No cóż, myślę, że jeśli pośpieszymy się do Chang Xing...";
			link.l1 = "Longway... Rozumiem, jak bardzo chcesz zobaczyć swoją siostrę, ale "+sStr+" jest teraz w śmiertelnym niebezpieczeństwie i to nie tylko przenośnia! Musisz zrozumieć, że uratowanie jej to priorytet numer jeden!";
			link.l1.go = "PZ_Longway_NotMartinInfo_2";
		break;
		
		case "PZ_Longway_NotMartinInfo_2":
			dialog.text = "Wielmożny Panie Kapitanie, wątpię, czy naprawdę rozumiesz, przez co przechodziłem przez te dziesięć lat. Przez co przechodzę teraz.";
			link.l1 = "Wiesz, w pewnym sensie tak. Mój brat jest przetrzymywany w więzieniu. I chociaż jeszcze mu nie zaszkodzili, w każdej chwili mogą zrobić z nim, co tylko zechcą.";
			link.l1.go = "PZ_Longway_NotMartinInfo_3";
		break;
		
		case "PZ_Longway_NotMartinInfo_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Ale dokąd byś poszedł, gdyby to była tylko dama "+sStr+" kto potrzebował ratunku?";
			if (CheckAttribute(pchar, "questTemp.FMQT.GiveDiamonds") && !CheckAttribute(pchar, "questTemp.FMQT_ObchistilSunduk"))
			{
				link.l1 = "Jest jedno miejsce... jedna osoba... Ale nie kłopocz się tym, Longway - muszę się tym zająć sam.";
				link.l1.go = "PZ_GoMarceline1";
			}
			link.l2 = "Tak naprawdę nie wiem nawet, dokąd się udać. Jeśli będę lekkomyślnie szperał wszędzie, przyciągnę uwagę, a wtedy "+sStr+" jest definitywnie skończone. Więc... po prostu nie wiem.";
			link.l2.go = "PZ_GoTogether1";
		break;
		
		case "PZ_GoMarceline1":
			dialog.text = "Co? Dlaczego?";
			link.l1 = "Nie wpuszczą cię tam ot tak – to wyższe sfery, do diabła. Więc pójdę sam. W międzyczasie, udaj się do swojej siostry. Dołączę do ciebie, jak tylko będę mógł. Powodzenia, Longway!";
			link.l1.go = "PZ_GoMarceline2";
			RemovePassenger(pchar, npchar);
		break;
		
		case "PZ_GoMarceline2":
			dialog.text = "Tak! Dziękuję, Wielmożny Panie Kapitanie. I powodzenia również dla ciebie!";
			link.l1 = "Och, dziękuję - dziś bardzo tego potrzebuję. My wszyscy potrzebujemy.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_MarcelineLongwayGo");
		break;
		
		case "PZ_GoTogether1":
			dialog.text = "Wielmożny Panie Kapitanie...";
			link.l1 = "Nie ważne. Chodźmy do twojej siostry, Longway. Jeśli teraz się rozdzielimy - zginiemy. Pospieszmy się do twojej siostry i dowiedzmy się, gdzie jest legowisko Levasseura. Potem pójdziemy razem - teraz potrzebuję wszelkiej pomocy, jaką mogę dostać. Mam nadzieję, że nie jesteśmy za późno.";
			link.l1.go = "PZ_GoTogether2";
		break;
		
		case "PZ_GoTogether2":
			dialog.text = "Nie spóźnimy się, Wielmożny Panie Kapitanie. Nie zwlekajmy dłużej ani nie traćmy czasu na kłótnie. Ruszajmy do Chang Xing!";
			link.l1 = "Masz rację, pospieszmy się.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TogetherLongwayGo");
		break;
		
		case "PZ_FrenchSoldier1":
			dialog.text = "Dokąd, do diabła, idziesz? Czy wiesz w ogóle, dokąd prowadzą te drzwi?";
			link.l1 = "Wiem doskonale. Idę tam w interesach, a nie z pustej ciekawości czy aby kraść.";
			link.l1.go = "PZ_FrenchSoldier2";
		break;
		
		case "PZ_FrenchSoldier2":
			dialog.text = "Jaki interes? Madame Levasseur jest teraz niedostępna. Poza tym, jest zamężną kobietą - nie przystoi, aby ludzie kręcili się wokół jej domu.";
			link.l1 = "Zamężna, tak, co nie? Ale czasami urządza przyjęcia, co nie? W tym także prywatne. To jeden z takich razów. Ona mnie oczekuje, a ja się śpieszę.";
			link.l1.go = "PZ_FrenchSoldier3";
		break;
		
		case "PZ_FrenchSoldier3":
			dialog.text = "Ostrzegłaby mnie, gdyby tak było.";
			link.l1 = "Jestem gościem szczególnego rodzaju - takim, który nie potrzebuje zapowiedzi.";
			link.l1.go = "PZ_FrenchSoldier4";
		break;
		
		case "PZ_FrenchSoldier4":
			dialog.text = "Tak, taki gość, przez którego Jego Lordowska Mość każe mnie rozstrzelać. Albo sama Lady każę mnie obedrzeć ze skóry.";
			link.l1 = "Byłem już gościem Madame Marceline. Zapewniam cię, żołnierzu, nic ci się nie stanie potem.";
			link.l1.go = "PZ_FrenchSoldier5";
		break;
		
		case "PZ_FrenchSoldier5":
			dialog.text = "Ale oczywiście, pozostawanie ślepym i wpuszczanie wszystkich - to zadanie straży miejskiej.";
			link.l1 = "Nie mam na to czasu, ty uparty ośle...";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_FrenchSoldierFight");
		break;
		
		case "PZ_Marceline1":
			dialog.text = "Ty...";
			// начинаем проверять результат прохождения "Почти как дома"
			switch (pchar.questTemp.FMQT.Marceline)
			{
				// поделили алмазы и "охладили трахание, углепластики" (с)
				case "Fuck":
					link.l1 = "O tak, madam. Twój rycerz cieszy się, że znów cię spotyka. Widzę, że jesteś zaskoczona moim widokiem. Czy radość z tego spotkania... nie jest wzajemna?";
					link.l1.go = "PZ_MarcelineFuck1";
				break;
				
				// поделили алмазы, без трахания и углепластиков
				case "NoFuck":
					link.l1 = "Tak, zrobiłem to. Zdaję sobie sprawę, że mogę nie być najprzystojniejszym ani najbardziej godnym mężczyzną na tej wyspie, jak wspomniałaś podczas naszego ostatniego spotkania, lecz przynajmniej wiesz, że jestem uczciwym człowiekiem. Posłuchaj mnie, madame - nie zajmę wiele z twojego... cennego czasu.";
					link.l1.go = "PZ_MarcelineNoFuck1";
				break;
				
				// "сошлись вот где-то посередине" (с)
				case "Deception":
					link.l1 = "„Cisza, na miłość boską, przestań krzyczeć, madame. Nie przyszedłem tu, by się zemścić za oszukanie swego rycerza i ucieczkę ze skarbem smoka. I zapewniam cię, gdybym chciał cię zabić, po prostu bym cię zastrzelił i uciekł. To w końcu Tortuga! Ale myślę, że dobrze wiesz, że to poniżej mojej godności.”";
					link.l1.go = "PZ_MarcelineDeception1";
				break;
			}
		break;
		
		case "PZ_MarcelineFuck1":
			dialog.text = "O, nie! Ja tylko pomyślałam, że... Cóż, to nie ma znaczenia! Widzisz, złe języki rozprzestrzeniają brudne plotki o mnie - biednej kobiecie, która, nawet gdyby chciała, nie mogłaby nikogo skrzywdzić ani obronić się przed wrogami. Poza tym, minęło już tyle czasu... Myślałam, że przybywasz do mnie w złym duchu, a nie z dobrymi intencjami. Cieszę się, że się myliłam. Trudno jest żyć, gdy jesteś otoczona nieżyczliwymi ludźmi.";
			link.l1 = "Jakże bym mógł? Nawet gdybym coś takiego usłyszał, nie uwierzyłbym w ani jedno słowo. Ale masz rację - nie przyszedłem tu tylko po to, by cię zobaczyć. Choć cieszę się, że to zrobiłem. Wiem, że to zabrzmi nietypowo, ale... tym razem twój rycerz potrzebuje twojej pomocy, pani.";
			link.l1.go = "PZ_Marceline2";
		break;
		
		case "PZ_MarcelineNoFuck1":
			dialog.text = "A jesteś o wiele bardziej wrażliwy, niż myślałam. Jednakże, nie jesteś bez wad, Monsieur de Maure - spodziewałam się, że będziesz bardziej... wyrafinowany. W rzeczy samej... albo zawsze taki byłeś, albo Archipelag już cię zepsuł. Powinieneś na nowo nauczyć się, jak rozmawiać z damą. Ale masz rację - jesteś uczciwym człowiekiem, aczkolwiek... prostym.";
			link.l1 = "A ty jesteś dumna i mściwa kobieta. Twoje oczy, słowa i... czyny to zdradzają. Więc jeśli ktoś mnie zrozumie, to ty. Tak jak kiedyś ja zrozumiałem ciebie. Nie rozwlekajmy się już nad przeszłością. Czy możesz mi pomóc, pani?";
			link.l1.go = "PZ_Marceline2";
		break;
		
		case "PZ_MarcelineDeception1":
			dialog.text = "Oh... Przyznaję, że byłam dla ciebie nieuprzejma wtedy. Ale tylko dlatego, że nie byłam do końca pewna ciebie, nic więcej! Czy zabrałbyś mi wszystkie diamenty? Albo sprowadził mojego męża tutaj, mówiąc, że dowiedziałeś się od naszych służących, że ukradłam mu coś, zaprzeczając twojemu udziałowi w tym? W końcu wszyscy szukają jego łaski, a nie biednej kobiety jak ja... Teraz rozumiem, że myliłam się co do ciebie. Proszę, przyjmij moje przeprosiny... mój rycerzu.";
			link.l1 = "Nie wiem teraz, czy są szczerzy, czy nie. Ale to nie ma znaczenia. Potrzebuję twojej pomocy, Madame Marceline. To kwestia życia i śmierci. Proszę, nie odmawiaj.";
			link.l1.go = "PZ_Marceline2";
		break;
		
		case "PZ_Marceline2":
			dialog.text = "Moja pomoc...? Z pewnością nie jestem ostatnią kobietą w mieście, ale mój wpływ nie jest tak wielki, jak myślicie. Jestem królową, która panuje, a nie rządzi. Ale wysłucham cię. Co moja skromna osoba może dla ciebie zrobić?";
			link.l1 = "Rozumiem, że to dla pani nieprzyjemny temat, ale szukam pani męża i to jak najszybciej. Chodzi o to, że...";
			link.l1.go = "PZ_Marceline3";
		break;
		
		case "PZ_Marceline3":
			dialog.text = "„To jakiś żart? Nie ma go w rezydencji w tej chwili? Więc wyjechał w interesach. Nie mogę ci pomóc, Monsieur de Maure.”";
			link.l1 = "„Odwróciłeś wzrok. Wiesz. Ja też wiem. Muszę się tylko tam dostać. Proszę, nie udawaj, że pierwszy raz słyszysz o lochach - jesteś zbyt mądry, żeby nie wiedzieć.”";
			link.l1.go = "PZ_Marceline4";
		break;
		
		case "PZ_Marceline4":
			dialog.text = "„Och, czuję, że ta rozmowa doda mi kolejny siwy włos na głowie. Jakbym już nie miała pierwszych zmarszczek. Co ty na litość boską z nami wszystkimi robisz, Francois...”";
			link.l1 = "„Siwy włos doda ci tylko szlachetności i nie odejmie urody. Ale dobra, niewinna dziewczyna wpadła w ręce twojego męża. A teraz ryzykuje utratę swojej urody, zdrowia, a nawet życia!...! Wiesz, co się dzieje z tymi, którzy tam wpadają. Proszę, pani. Marcelino... Pomóż swojemu rycerzowi.”";
			link.l1.go = "PZ_Marceline5";
		break;
		
		case "PZ_Marceline5":
			dialog.text = "„Już nie jestem twoim rycerzem, prawda? Daj spokój, nie jestem głupia. Ale... pomogę ci, de Maure. W końcu to nie mogło trwać wiecznie. I pewnego dnia wszystko by wyszło na jaw. Teraz ważne dla mnie jest, aby wyjść na czas i we właściwy sposób. I... nie mogę cię skazać na wieczne cierpienie spowodowane tym, co mój 'mąż' zrobi twojej... znajomej.”";
			link.l1 = "Być może nie jestem już twoim rycerzem, pani. Ale i ty nigdy nie byłaś moją damą od samego początku. Jednakże, będę ci wdzięczny do końca życia. Więc gdzie jest to miejsce?";
			link.l1.go = "PZ_Marceline6";
		break;
		
		case "PZ_Marceline6":
			dialog.text = "Cóż, uwierzę ci na słowo, Charles. W miejskich lochach. W jednym z zaułków stoi duża beczka, a obok niej zaczyna się przejście prowadzące do legowiska tego potwora. Nie zaglądałem do środka. Podążałem za nim tylko raz, dawno temu. I przeraziłem się, gdy usłyszałem nieludzkie krzyki tych biednych istot.";
			link.l1 = "Ocaliłaś dziś wiele istnień, pani. Nie tylko moją ukochaną, ale i wszystkich, którzy mogliby w przyszłości paść ofiarą twego męża. Dziękuję.";
			link.l1.go = "PZ_Marceline7";
		break;
		
		case "PZ_Marceline7":
			dialog.text = "„Ach, zostaw mnie z tymi pustymi słowami, monsieur. Wiele ode mnie wymagałeś. I podjąłem wielkie ryzyko. Spróbuj teraz uczynić swoją nową misję w legowisku smoka sukcesem... mój rycerzu.”";
			link.l1 = "Zrobię, co w mojej mocy. Żegnaj, Marceline.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_MarcelineOver");
		break;
		
		case "PZ_ElitaShluha_18":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko") && !CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				dialog.text = "So, you're a bandit, monsieur...? We don't hire new girls like this; we all came here voluntarily. I'm going to have to ask you and your... accomplice to step out. And I'll make sure this girl gets treatment - otherwise, I'll report you to the authorities!";
				link.l1 = "Nie jesteśmy bandytami. Ale ta dziewczyna dorównuje każdemu z nich. Nie nosi szabli dla ozdoby. Jest po prostu ranna. Ten człowiek to mój przyjaciel i brat twojej pani. Więc pozwól nam ją zobaczyć.";
				link.l1.go = "PZ_ElitaShluha_WithLongwayAndGirl1";
			}
			else
			{
				dialog.text = "Miło cię znów widzieć, monsieur! Ale wiesz, że nie przyjmujemy gości... niskiej klasy tutaj. Nawet jeśli są polecani i opłaceni. Zwłaszcza żółtoskórych robotników czy niewolników murzyńskich. Obawiam się, że twój przyjaciel będzie musiał odejść.";
				link.l1 = "Nie mów tego przy swojej pani. Ona też ma żółtą skórę. I to nie jest robotnik, tylko jej brat. Nie przeszkodzisz w rodzinnych spotkaniach, prawda?";
				link.l1.go = "PZ_ElitaShluha_WithLongway1";
			}
		break;
		
		case "PZ_ElitaShluha_18_1":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko") && !CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				dialog.text = "It's getting worse by the hour. First the mad yellow laborer and now you. No, monsieur, we don't pay for the girls who are brought to us by force; they are all here of their own free will.";
				link.l1 = "Uratowałem tę dziewczynę, i nigdy nie będzie pracować w miejscu, które jest poniżej jej godności. Mówisz, że pracownik fizyczny?";
				link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithGirl1";
			}
			else
			{
				dialog.text = "O monsieur, cóż za pechowy moment! Dziś już nie przyjmujemy więcej gości - sam możesz zobaczyć, co się tutaj wydarzyło.";
				link.l1 = "„Dlatego tu jestem. To żółtoskóry człowiek to wszystko zorganizował, prawda?”";
				link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithoutGirl1";
			}
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithGirl1":
			dialog.text = "Tak, monsieur, robotnik! Ledwo rozumieliśmy, co mówił! Ten łachmaniarz wpadł i zażądał spotkania z panią. Twierdził, że jest jej bratem. Wezwaliśmy ludzi, ale...";
			link.l1 = "To dla niego żadna przeszkoda. Co się potem stało?";
			link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithGirl2";
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithGirl2":
			for (i = 1; i <= 4; i++)
			{
				sld = characterFromId("PZ_EliteBrothelMercenary" + i);
				sld.lifeday = 0;
			}
			
			dialog.text = "Okazało się, że nie kłamał. Pani wyszła do nas i go rozpoznała. W rzeczywistości wciąż rozmawiają w jej luksusowym miejscu.";
			link.l1 = "Kto wie, co siedzi mu w głowie. Wchodzimy tam - uratujemy ją, jeśli będzie trzeba. Nie rób zamieszania - zniszczy to reputację tego miejsca.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_EliteBrothelCreateChangShin");
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithoutGirl1":
			dialog.text = "Zgadza się, monsieur. Powiedział, że jest bratem damy.";
			link.l1 = "A ty go nie wpuściłeś...";
			link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithoutGirl2";
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithoutGirl2":
			dialog.text = "Oczywiście, że nie! Ta dama jest wykwintnie ubrana i mówi bez akcentu, w przeciwieństwie do tamtego robotnika. Próbowaliśmy go przegonić, a on powalił wszystkich strażników, możesz to sobie wyobrazić?!";
			link.l1 = "Łatwo to sobie wyobrazić. A gdzie on teraz jest?";
			link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithoutGirl3";
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithoutGirl3":
			for (i = 1; i <= 4; i++)
			{
				sld = characterFromId("PZ_EliteBrothelMercenary" + i);
				sld.lifeday = 0;
			}
			
			dialog.text = "„On i ta dama wciąż rozmawiają o czymś, ale nie możemy zrozumieć, o czym to jest – prawdopodobnie w ich własnym języku.”";
			link.l1 = "Podejdę do nich. Może twoja dama potrzebuje pomocy. Nie wołaj straży - jeśli to się rozniesie, nikt już nigdy nie zapuka do twoich drzwi.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_EliteBrothelCreateChangShin");
		break;
		
		case "PZ_ElitaShluha_WithLongway1":
			dialog.text = "Brat? Pani jest godna szacunku, co więcej niż mogę powiedzieć o tym ‘bracie’ jej. Nie ma potrzeby mącić jej w głowie ani próbować jej oszukać tym robotnikiem. Zabierz go.";
			link.l1 = "Powiedziałem ci, że stracili się dawno temu. On po prostu ma mniej szczęścia. Zapłacimy sami za nasz czas. Poinformuj teraz gospodynię.";
			link.l1.go = "PZ_ElitaShluha_WithLongway2";
		break;
		
		case "PZ_ElitaShluha_WithLongway2":
			dialog.text = "„Nie ma się czego obawiać z twojej strony. A twoja natarczywość mi się nie podoba. Chłopcy! Wyrzućcie tego robotnika! I jego zagubionego pana też!”";
			link.l1 = "Do diabła! Tyle arogancji u kurtyzany!";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_EliteBrothelFight");
		break;
		
		case "PZ_ElitaShluha_WithLongwayAndGirl1":
			dialog.text = "„Nie ma mowy! Aby dama była sama z całym tym dziwnym towarzystwem? Tylko jeśli pójdziesz tam sam, monsieur. A twoi... przyjaciele będą czekać na zewnątrz - mamy tutaj przyzwoity przybytek.”";
			link.l1 = " Dlaczego się o nią martwisz? Wszyscy wiedzą, że jest jednym z najlepszych szermierzy na Tortudze. A moi przyjaciele są bardziej porządni niż większość ludzi w tym mieście.";
			link.l1.go = "PZ_ElitaShluha_WithLongwayAndGirl2";
		break;
		
		case "PZ_ElitaShluha_WithLongwayAndGirl2":
			dialog.text = "Chłopcy! Jest tu ranny bandyta i brudny robotnik! Chcą czegoś od naszej pani! Zajmijcie się nimi!";
			link.l1 = "Co za poświęcenie, do diabła...";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_EliteBrothelFight");
		break;
		
		case "PZ_ChangShin1":
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
			
			// итак, снова проверка по результатам прохождения. Лонгвэй с нами, тян ещё в пыточной
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "Zakładam, że jesteś Charles de Maure? A to... Och.";
				link.l1 = "I ty musisz być Belle Etoile. A może powinnam powiedzieć Chang Xing? Tak, to twój brat. Szukał cię przez ponad dekadę. My oboje mamy do ciebie wiele, wiele pytań. I niewiele czasu.";
				link.l1.go = "PZ_ChangShin_WithLongway1";
			}
			// пришли с Лонгвэем и тян
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom") && CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				dialog.text = "Na litość boską, przeżyłaś. Masz całkiem niezłego obrońcę, nawet jeśli trochę się spóźnił. Lepszego niż ten, który najwyraźniej uważa mnie za swoją obrończynię i teraz stoi obok ciebie. Niebo ci sprzyja, moja droga dziewczyno.";
				link.l1 = "Widzę, że wiesz. To nawet lepiej - nie muszę tłumaczyć. Ale powiedz mi, z czego się śmiejesz, Chang Xing? Lubisz patrzeć, jak inne dziewczyny cierpią, prawda? W końcu je sprzedajesz.";
				link.l1.go = "PZ_ChangShin_WithLongwayAndGirl1";
			}
			// Лонгвэй с нами, тян на небесах
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom") && CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
				dialog.text = "Charles de Maure, prawda? Słyszałem, że chciałeś się ze mną spotkać. Co cię trapi? Nie podobała ci się obsługa w naszym przybytku, gdy ostatnio tu byłeś?";
				link.l1 = "Właśnie przyszedłem z innego twojego przybytku, Chang Xing."+sStr+", mój ukochany, nie żyje. I wiem, że ty też miałeś w tym swój udział.";
				link.l1.go = "PZ_ChangShin_GirlDied1";
			}
		break;
		
		case "PZ_ChangShin_WithLongway1":
			dialog.text = "Chang Xing... Minęło wiele czasu, odkąd słyszałam to imię. To było dawno temu. Biali ludzie... zawsze się spieszycie. Co powiecie na spokojne rodzinne spotkanie? Mnie to nie obchodzi. Przestałam polegać na innych lata temu. Czemu nic nie mówisz, mój bracie? Nie cieszysz się, że widzisz własną siostrę? W końcu tak nieustannie mnie szukałeś.";
			link.l1 = "    Mamy inne pilne i ważniejsze sprawy do załatwienia. Porozmawiaj ze swoją siostrą, Longway. Ale pamiętaj, dokąd musimy jeszcze iść. Musimy się spieszyć. I mam też pytania do niej.";
			link.l1.go = "PZ_Longway_SisterDialog1";
		break;
		
		case "PZ_Longway_SisterDialog1":
			locCameraFromToPos(0.65, 2.59, -3.06, true, 0.23, 0.34, -5.21);
			
			sld = characterFromId("Longway");
			ChangeCharacterAddressGroup(sld, "Tortuga_brothelElite_room2", "goto", "goto8");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("PZ_ChangShin"));
			
			sld = characterFromId("PZ_ChangShin");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("Longway"));
			
			dialog.text = "„(W mandaryńskim) Longway, co? Cóż, poza imieniem, niewiele się zmieniłeś... Chang Tu.”";
			link.l1 = "„(Po mandaryńsku) Ale bardzo się zmieniłaś, siostro. Co się stało? Twój wzrok był kiedyś ciepły jak południowe słońce. Teraz jest zimny i wyraża tylko pogardę. A twój głos? Kiedyś uwielbiałem cię rozśmieszać i słuchać, jak te srebrne dzwonki dzwonią... Teraz jest zimniejszy niż Goango zimą. I nosisz ich ubrania. I sama sprzedajesz kobiety, choć kiedyś zostałaś porwana przez Fermentelos.”";
			link.l1.go = "PZ_Longway_SisterDialog2";
		break;
		
		case "PZ_Longway_SisterDialog2":
			dialog.text = "Przychodzisz mnie pouczać, chociaż kiedyś pracowałeś dla Rodenburga, jednego z największych łajdaków archipelagu? Myślisz, że nie wiedziałam o tobie? Zawsze wiedziałam. To nie tobie osądzać, czym się stałam i dlaczego, mój zagubiony starszy bracie.";
			link.l1 = "Więc pozwól mi się dowiedzieć, Xing! I powiedz mi. Jeśli wiedziałaś, że jestem na Archipelagu, dlaczego nie chciałaś się ze mną spotkać po tylu latach? Poświęciłem całe życie na poszukiwanie ciebie...";
			link.l1.go = "PZ_Longway_SisterDialog3";
		break;
		
		case "PZ_Longway_SisterDialog3":
			dialog.text = "Bo ani ty, ani niebiosa nie uchroniły mnie przed najstraszliwszym losem. Wtedy zrozumiałam, że nikt na tym świecie nie potrzebuje nikogo innego. Możemy liczyć tylko na siebie. Cóż, powiem ci, jeśli chcesz wiedzieć. Ale będę mówić w jego języku. Jestem pewna, że on też chciałby to usłyszeć. Rozumiesz francuski, prawda, Tu?";
			link.l1 = "„(łamaną francuszczyzną): Tak, mówię tym językiem.”";
			link.l1.go = "PZ_Longway_SisterDialog4";
		break;
		
		case "PZ_Longway_SisterDialog4":
			dialog.text = "Ha ha ha, o, Niebiosa! Twój akcent jest okropny. To jednak nie twoja wina - francuska wymowa i pisownia są rzeczywiście trudne.";
			link.l1 = "Śmiejesz się teraz inaczej, siostro...";
			link.l1.go = "PZ_ChangShin_WithLongway3";
		break;
		
		/*case "PZ_Longway_SisterDialog5":
			Return_LongwayOfficer();
			
			StartInstantDialog("PZ_ChangShin", "PZ_ChangShin_WithLongway3", "Quest\CompanionQuests\Longway.c");
		break;*/
		
		case "PZ_ChangShin_WithLongway3":
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
			dialog.text = "Moi drogi bracie, chce wiedzieć, co się ze mną działo przez te lata. Myślę, że i tobie dobrze byłoby posłuchać - jak powiedziałeś, masz pytania. Więc nie martw się - opowiem ci o wszystkim po francusku.";
			link.l1 = "Powiedz mi tylko sedno - kiedy Longway opowiadał mi swoją historię życia, zajęło to dobrych kilka godzin. A teraz się śpieszę.";
			link.l1.go = "PZ_ChangShin_WithLongway4";
		break;
		
		case "PZ_ChangShin_WithLongway4":
			dialog.text = "Bądź cierpliwy. Trzymałem to wszystko dla siebie przez ponad rok. A jeśli mi przerwiesz, nie odpowiem na żadne z twoich pytań.";
			link.l1 = " W porządku... To idź dalej.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_ChangShin_WithLongwayAndGirl1":
			dialog.text = "Gdzie twoje maniery, Charles de Maure? Powiedziano mi, że jesteś człowiekiem o doskonałych manierach i wzorem dla kobiet. Tylko plotki, ale w rzeczywistości... klapa? Tak myślałam. I mylisz się - nienawidzę wszystkich mężczyzn i kobiet równo. W rzeczywistości nikomu nie ufam, niczego się nie dziwię, niczego nie oczekuję. Chętnie zmiażdżyłabym ci jądra, gdybym mogła cię dopaść. Ale usłyszenie mojego prawdziwego imienia po tylu latach było trochę... odświeżające.";
			link.l1 = "Jestem amantem dla dam, nie dla wiedźm takich jak ty. I tak czy inaczej, czego się spodziewałaś, skoro jesteś zamieszana w dręczenie osoby, na której mi najbardziej zależy? Ledwo się powstrzymuję, żeby czegoś ci nie zrobić. Nie najmniej z jego powodu. Longway jest moim przyjacielem. A ty jesteś jego rodziną. Szukał cię przez ponad dekadę. I zasługuje na rozmowę z tobą.";
			link.l1.go = "PZ_ChangShin_WithLongwayAndGirl2";
		break;
		
		case "PZ_ChangShin_WithLongwayAndGirl2":
			dialog.text = "Jakie to sentymentalne. I jakże smutne, że mnie to nie obchodzi. Ale teraz nie uciekniesz tak łatwo, prawda, Tu? Nie za to, że cię zabiję i wszystkich was za spóźnienie. Ale wiedząc... Myślę, że zasługujesz na to, by wiedzieć. Znałeś mnie, gdy nie byłem taki, bracie.";
			link.l1 = "Bez względu na to, co ci się przydarzyło... zawsze miałeś wybór, Chang Xing.";
			link.l1.go = "PZ_ChangShin_WithLongwayAndGirl3";
		break;
		
		case "PZ_ChangShin_WithLongwayAndGirl3":
			dialog.text = "Jesteś jeszcze młody i nie wiesz, jak działa świat, Charles de Maure. W życiu jest tylko jeden prawdziwy wybór: żyć lub umrzeć. Myślę, że dobrze by było, gdybyś też wiedział wszystko. Więc opowiem swoją historię po francusku. Mówisz po nim, prawda, Tu?";
			link.l1 = "„Z akcentem. Ale bardzo dobrze to rozumie. Możesz zaczynać.”";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_ChangShin_GirlDied1":
			dialog.text = "„A gdzieś ty był przez cały ten czas? Espanola jest zaledwie dzień lub dwa stąd. Jej śmierć to też twoja wina. I ty. Jesteś spóźniony o ponad dekadę. Nasi zbawcy, nasi obrońcy. Im szybciej kobieta nauczy się bronić, tym lepiej. Niektóre robią to na czas, inne nie. A ktoś nie ma wystarczająco oleju w głowie, żeby na to wpaść.”";
			link.l1 = "Uważaj na każde następne słowo. Jeszcze cię nie rozerwałem na strzępy tylko ze względu na mojego przyjaciela, twojego brata. Nie masz pojęcia, przez co przeszedł dla ciebie.";
			link.l1.go = "PZ_ChangShin_GirlDied2";
		break;
		
		case "PZ_ChangShin_GirlDied2":
			dialog.text = "Bardzo wątpię, że przeszedł przez cokolwiek choćby zbliżonego do tego, co ja przeżyłem.";
			link.l1 = "„Więc powiedz nam.”";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_ChangShin2":
			dialog.text = "„Cóż, cóż mogę powiedzieć, byłem wtedy młody, głupi i naiwny. I nietolerancyjny. Czy Tu już opowiedział Ci, jak zostałem porwany przez Oliverio Fermentelosa po tym, jak zabił moich rodziców i mnie?”";
			link.l1 = "„Zgadza się.”";
			link.l1.go = "PZ_ChangShin3";
		break;
		
		case "PZ_ChangShin3":
			dialog.text = "Zabiegał o moje względy i wyznał mi swoje uczucia, ale go odrzuciłam. I wtedy wymordował naszą rodzinę i porwał mnie. A potem...";
			link.l1 = "Mogę się domyślić.";
			link.l1.go = "PZ_ChangShin4";
		break;
		
		case "PZ_ChangShin4":
			dialog.text = "Chciałabym, żebyś mógł. Potem znów wyznał mi swoje uczucia, gorące i we łzach, mówiąc, że to jedyny sposób, bo moja rodzina nigdy nie pozwoliłaby mi z nim odejść.";
			link.l1 = "Szaleństwo...";
			link.l1.go = "PZ_ChangShin5";
		break;
		
		case "PZ_ChangShin5":
			dialog.text = "Heh, słowo, które opisuje całe moje życie od tamtego czasu. Odrzuciłam go ponownie. I tak to się toczyło przez jakiś czas. Ale jasno, nie mogło to trwać wiecznie, bo byłam całkowicie na jego łasce.";
			link.l1 = "Więc to się stało?";
			link.l1.go = "PZ_ChangShin6";
		break;
		
		case "PZ_ChangShin6":
			dialog.text = "Oczywiście. Wziął mnie siłą, brutalnie i bezlitośnie. Nie żeby to kiedykolwiek przeszkadzało gwałcicielom, ale czyż nie wyznał mi wcześniej ze łzami w oczach swojej wielkiej miłości? Phi! Miłość najwyraźniej się ulotniła. A wszystko to trwało dzień po dniu jak jakaś rutyna. Na początku krzyczałam i stawiałam opór, ale potem przestałam - jaki to miało sens w ogóle...";
			link.l1 = "Ale Fermentelos dostał to, na co zasłużył, a ty wylądowałeś tutaj. Jak to się stało?";
			link.l1.go = "PZ_ChangShin7";
		break;
		
		case "PZ_ChangShin7":
			dialog.text = "„Cóż, dość szybko miał mnie dosyć. To zabawne, prawda? Zabił moich i Tu rodziców, porwał mnie, regularnie mnie hańbił, tylko po to, by mnie na końcu porzucić. Przybył na to Archipelag i sprzedał mnie Levasseur jako niewolnicę.”";
			link.l1 = "Nie życzyłbym tego nawet wrogowi. Więc jak udało ci się przeżyć? I w ogóle jakim cudem jesteś wolna? Z tego, co słyszałem, Levasseur nigdy nie wypuszczał kobiet ze swojej kryjówki. Zawsze się ich pozbywał.";
			link.l1.go = "PZ_ChangShin8";
		break;
		
		case "PZ_ChangShin8":
			dialog.text = "„Tak to teraz wygląda. Wtedy Levasseur był inny. Nie, on zawsze był zwierzęciem. Ale na początku czasami porywał młodych miejscowych kolonistów, gwałcił ich w swojej piwnicy i prawie natychmiast się ich pozbywał, aby uniknąć płacenia za ich milczenie. Tylko rzadko trzymał ich dłużej niż kilka dni w tamtych latach. Ze mną, z drugiej strony, było inaczej od samego początku.”";
			link.l1 = "Bo byłeś niewolnikiem, prawda?";
			link.l1.go = "PZ_ChangShin9";
		break;
		
		case "PZ_ChangShin9":
			dialog.text = "„Dokładnie. Główne pragnienie Levasseura nie było tylko fizyczną przyjemnością. I nawet nie chwilowym poczuciem władzy nad jego ofiarami - w końcu ma je nad całą wyspą. Ale...”";
			link.l1 = "... przyjemność patrzenia, jak się łamią - ich wola, ich wygląd, ich głos, ich zachowanie.";
			link.l1.go = "PZ_ChangShin10";
		break;
		
		case "PZ_ChangShin10":
			dialog.text = "Tak. Widzę, że odrobiłeś swoją pracę domową, Kapitanie. Ale pod tym względem, nie byłam dla niego zabawą - Fermentelos przyprowadził mnie już złamaną. A Levasseur nie uważał mnie za piękną - nie lubi azjatyckich kobiet. Wiesz, z jakiegoś powodu to mnie bardzo dotknęło – zdaję sobie sprawę, że jestem atrakcyjna, ale nie uważam siebie za prawdziwie piękną. I nie wierzę, gdy ludzie mi to mówią. Nawet teraz, gdy ćwiczę, noszę jedwabie i spryskuję się wykwintnymi perfumami. Nie to, żebym potrzebowała aprobaty mojego oprawcy, ale...";
			link.l1 = "„Cóż, więc powtórzę moje pytanie – jak udało ci się przeżyć? Gdy tylko znudzi się kobietą, pozbywa się jej. Z tobą znudził się od samego początku, jak mówisz.”";
			link.l1.go = "PZ_ChangShin11";
		break;
		
		case "PZ_ChangShin11":
			dialog.text = "Domyślam się, że fakt, iż nudziłam go od samego początku, miał swoje znaczenie. I to, że byłam niewolnicą - nie mogłam nigdzie pójść ani nic powiedzieć. Dziewczęta niewolnice były tak traktowane od tysięcy lat. Zaczął myśleć, jak uczynić czas spędzany ze mną 'zabawą' dla siebie.";
			link.l1 = "Tak właśnie narodziły się jego uzależnienia, w ich obecnej formie.";
			link.l1.go = "PZ_ChangShin12";
		break;
		
		case "PZ_ChangShin12":
			dialog.text = "Dokładnie. Na początku były to bicie, plucie i inne poniżenia. I szyderstwa - zarówno z mojego wyglądu, jak i pochodzenia, mojej krwi. A potem przyszły pierwsze tortury - noże, szczypce, patelnia... Dlatego noszę takie zamknięte ubrania - całe moje ciało jest pokryte bliznami, poparzone i okaleczone. I dlatego nigdy więcej nie planuję rozbierać się przed mężczyzną. Nigdy więcej. Wtedy w końcu zrozumiałam, co powinnam była zrozumieć, kiedy Fermentelos mnie porwał.";
			link.l1 = "Co to było?";
			link.l1.go = "PZ_ChangShin13";
		break;
		
		case "PZ_ChangShin13":
			dialog.text = "„Że nie będę już bezradną marionetką. Przeciwnie, powinnam być panią swojego życia. W moim przypadku kobieta może zmienić swoje życie tylko wtedy, gdy kontroluje mężczyzn wokół siebie.”";
			link.l1 = "Nie powiedziałbym, że Levasseurem można kierować.";
			link.l1.go = "PZ_ChangShin14";
		break;
		
		case "PZ_ChangShin14":
			dialog.text = "I nie miałbyś racji. Ale można na niego wpłynąć, choć trzeba to robić ostrożnie. Levasseur równie mocno nie znosi całkowitego posłuszeństwa od samego początku, jak i sprzeczek czy błagania. Tak samo nie znosi pochlebstw - najwyraźniej zdając sobie sprawę, jakim naprawdę był świnią. Zdałam sobie z tego sprawę od razu, choć kosztowało mnie to dużo cierpienia. Ale kiedy był zadowolony po kolejnym wieczorze tortur i przemocy, można było z nim delikatnie porozmawiać. Może nie jestem szlachetnie urodzona, ale nie brak mi inteligencji.";
			link.l1 = "„O czym rozmawialiście?”";
			link.l1.go = "PZ_ChangShin15";
		break;
		
		case "PZ_ChangShin15":
			dialog.text = "Zainteresowałem go. Zasugerowałem pomysły na tortury, doradziłem, które narzędzia tortur lepiej nie używać, a od których warto zacząć. Na początku oczywiście wszystko wypróbował na mnie. Ale potem... zaczął mnie szanować, w swój pokręcony sposób. Co się dzieje w jego głowie? Próbowałem dowiedzieć się, jak stał się taki, ale znowu mnie pobił na pół śmierci. Potem sprowadził osobistego lekarza.";
			link.l1 = "To nawet bardziej dziwne i obrzydliwe niż to, co już o nim słyszałem.";
			link.l1.go = "PZ_ChangShin16";
		break;
		
		case "PZ_ChangShin16":
			dialog.text = "Już nie żądał, abym mu się oddała. Nazywał mnie uczennicą. Ale zawsze powtarzał, że jako jego projekt jestem całkowitym rozczarowaniem. Chyba po to, żeby mnie trzymać w napięciu. Więc zaczął mnie uczyć szermierki i języków. Mimo że trzymał mnie w piwnicy, to ja, a nie jego żona, dostawałam wszystkie drogie suknie.";
			link.l1 = "Rzeczywiście, projekt. Widać wyraźną paralelę z tym, jak prowadzisz to miejsce.";
			link.l1.go = "PZ_ChangShin17";
		break;
		
		case "PZ_ChangShin17":
			dialog.text = "Nie pomyślałem o tym, hmmm. I nie podoba mi się twoje porównanie, ponieważ nie torturuję moich pracownic. I nie pozwalam moim klientom tego robić. Chociaż nienawidzę tych dziwek i zazdroszczę im urody. I nie mam nic wspólnego z tym wieprzem, pamiętaj o tym.";
			link.l1 = "Jak zdobyłeś ten burdel?";
			link.l1.go = "PZ_ChangShin18";
		break;
		
		case "PZ_ChangShin18":
			dialog.text = "Oczywiście, od Levasseura. Przez jakiś czas trzymał mnie u siebie. Od czasu do czasu nawet pytał o radę, jak złamać tę czy inną dziewczynę. W końcu byłam dla niego wyjątkowa, nawet jeśli nigdy by tego nie przyznał. Byłam pierwsza. Widziałam wszystko.";
			link.l1 = "Kto się od kogo uczył, ponownie?";
			link.l1.go = "PZ_ChangShin19";
		break;
		
		case "PZ_ChangShin19":
			dialog.text = "Nie jestem taka! Nienawidzę z całej duszy każdego, kto wszystko miał podane na tacy! To niesprawiedliwe! Ten burdel to mój pomysł! Moje pracownice to córki kupców, urzędników i szlachciców, którzy czasami sprzyjali Levasseur. Poprosiłam go, by mi je oddał. Tortury i upokorzenia w tajemnej piwnicy to jedno. Ale publiczna działalność jako kurtyzana dla takich jak oni to zupełnie co innego!";
			link.l1 = "Nie powiedziałbym, że twoje pracujące kobiety wyglądają na tak upokorzone, nieszczęśliwe i złamane.";
			link.l1.go = "PZ_ChangShin20";
		break;
		
		case "PZ_ChangShin20":
			dialog.text = "Ponieważ wiedzą, co Levasseur lub nawet ja z nimi zrobimy, jeśli tylko pisną. Ale masz częściowo rację, oczywiście. Wino, jedzenie, jedwabie, brak codziennych tortur - wielu z nich zaczęło mnie postrzegać jako zbawcę. Głupcy przeklęci! Tylko nieliczni z nich nie są zadowoleni, że tu są. Niektórych oddał z ciężkim sercem. I chichotał, mówiąc, że zawsze mogę zwrócić mu któregokolwiek w zamian za rozwiązanie problemów finansowych mojego miejsca. Ale zawsze mówiłem nie. Przynajmniej w ten sposób przynosiliby złoto zamiast umierać w piwnicy na próżno. Byłoby to wyjście zbyt łatwe dla nich.";
			link.l1 = "Co za szkoda, że nie każdy poczuł się upokorzony, zamieniając klasztory gorsze niż Święta Inkwizycja na złotą klatkę jak twój burdel...";
			link.l1.go = "PZ_ChangShin21";
		break;
		
		case "PZ_ChangShin21":
			dialog.text = "Oceniasz mnie? Nie chciałam tylko przetrwać, ale też zbudować udany handel. Choć nieświadomie, Levasseur był mi wdzięczny. Mimo że nie byłam już niewolnicą, nie mógł mnie puścić. Nadal byłam zmuszona dla niego pracować i pomagać jego poplecznikom. Zwłaszcza jego chuderlawemu siostrzeńcowi, który ślinił się na mój widok za każdym razem, gdy mnie widział. Ale nie odważyłby się mnie zaatakować ani mówić do mnie w zły sposób. Obrzydliwe. Wiesz, mimo że nazywał mnie rozczarowaniem, byłam bardziej użyteczna niż Thibaut i Martene razem wzięci. Często im towarzyszyłam na jego rozkazy, tak jak wtedy w Port-au-Prince.";
			link.l1 = "To wszystko wiele wyjaśnia...";
			link.l1.go = "PZ_ChangShin22";
		break;
		
		case "PZ_ChangShin22":
			dialog.text = "„Zgadza się. Słuchaj. Nie torturowałem twojej ukochanej. Tak samo jak nie torturowałem żadnej dziewczyny tymi rękoma, nawet jeśli czasem doradzałem Levasseur. Ale skoro już o tym mówimy...”";
			link.l1 = "Co?";
			link.l1.go = "PZ_ChangShin23";
		break;
		
		case "PZ_ChangShin23":
			dialog.text = "Jak zapewne wiesz, Levasseur czasami żąda, aby przyprowadzić mu pewną dziewczynę, którą dostrzeżono na Tortudze, a potem opuściła wyspę. Albo ktoś go zaskoczy i przyprowadzi nieznajomą, żeby zyskać jego przychylność, tak jak było w moim przypadku. Porwanie twojej ukochanej było moim pomysłem.";
			link.l1 = "Coś ty właśnie powiedział...?";
			link.l1.go = "PZ_ChangShin24";
		break;
		
		case "PZ_ChangShin24":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "At first, we were considering capturing that blonde who used be so close to you. But since she is untouchable now, and because we have already promised him a girl, you redhead had to do.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "I heard rumors about your gorgeous companion who never leaves your side. Considering Levausser's love for blondes, I had very little trouble selling him this idea.";
			dialog.text = "Sotta, jego kundel, miał przyprowadzić mu mulatkę, żonę Luttera. Ale zabiłeś Sottę, więc - żadnej mulatki dla grubasa. Levasseur był wściekły. Wszyscy dostali po łbie - Thibaut, Martene, nawet ja. Nie wiem, kto mnie bardziej wkurzył: on, bo znowu mnie pobił, czy ty, który to spowodowałeś... "+sStr+" ";
			link.l1 = "„Więc to nawet nie z jego powodu... Ty to zrobiłeś.”";
			link.l1.go = "PZ_ChangShin25";
		break;
		
		case "PZ_ChangShin25":
			dialog.text = "Nie mam nadziei na twoje przebaczenie, a co więcej, nie potrzebuję go. Jeśli chcesz krwi, dostaniesz krew. I bardzo tego pożałujesz. Ale nie odmówię zrozumienia. Przydałoby mi się po raz pierwszy od dziesięciu długich lat. Wszystko, co kiedykolwiek robiłem, to starałem się jak najlepiej wydostać się z Tortugi pewnego dnia. Czy masz do mnie jakieś pytania, Charles de Maure?";
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo") && !CheckAttribute(pchar, "questTemp.PZ_FlagMarselinaInfo") && !CheckAttribute(pchar, "questTemp.PZ_FlagMartinInfo"))
			{
				link.l1 = " Ale byłeś zamieszany w porwanie. I wiesz, gdzie Levasseur trzyma swoje ofiary. Powiedz mi, gdzie to jest. A jeśli najgorsze się nie wydarzyło - zastanowię się poważnie nad tym, czy nie odpłacić ci pięknym za nadobne.";
				link.l1.go = "PZ_ChangShinDontKnow1";
			}
			else
			{
				link.l1 = "„Cóż, wszystko wreszcie się układa...”";
				link.l1.go = "PZ_ChangShin26";
			}
		break;
		
		case "PZ_ChangShinDontKnow1":
			dialog.text = "„Wiem, bo tam byłam. A jeśli masz wrażenie, że jestem z nim w jakiś sposób niezdrowo związana - to bardzo się mylisz. Byłabym szczęśliwa, widząc, jak ktoś nabija tę świnię na rożen.”";
			link.l1 = "„Nie mam czasu, Chang Xing. Gdzie to jest?”";
			link.l1.go = "PZ_ChangShinDontKnow2";
		break;
		
		case "PZ_ChangShinDontKnow2":
			dialog.text = "Wiesz o lokalnym lochu pod ulicami miasta? Tam właśnie idziesz. W jednym z zaułków stoi duża beczka wina, a obok niej zaczyna się tajemne przejście do jego pokoju uciech, jak to czasem nazywa.";
			link.l1 = "„Cóż, w końcu wszystko się układa...”";
			link.l1.go = "PZ_ChangShin26";
		break;
		
		case "PZ_ChangShin26":
			if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") && CheckAttribute(pchar, "questTemp.PZ_FlagShip")) StartInstantDialog("Longway", "PZ_Longway_SisterDialog6", "Quest\CompanionQuests\Longway.c");
			else
			{
				dialog.text = "Dobrze dla ciebie. Teraz wynoś się. Choć chciałam się wygadać po tylu latach, to świadomość, że znasz wszystkie moje tajemnice, wiesz, co mi zrobiono - jest obrzydliwa. Widok ciebie tylko mnie teraz złości. Aha, i Tu zostaje ze mną.";
				link.l1 = "Dlaczego tak jest?";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet1";
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet1":
			dialog.text = "„Może dlatego, że jestem jego rodziną? I dlatego, że widzę, jaki jest przy tobie - zbity, nieszczęśliwy mamroczący, który nawet nie miał czasu, by w pełni nauczyć się języka i zacząć mówić poprawnie. A jednak powiedział mi, że jesteście przyjaciółmi. Wyraźnie widać, jak na niego wpłynąłeś. Przynajmniej zrobię z niego mężczyznę.”";
			link.l1 = "A czy naprawdę jesteś zadowolony z siebie? W co go przemienisz? W okrutne, zgorzkniałe stworzenie, które handluje życiem?";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet2";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet2":
			StartInstantDialog("Longway", "PZ_Longway_SisterDialog_Ubezhdaet3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet3":
			if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") || CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
			{
				dialog.text = "Wielmożny Panie Kapitanie, proszę przestać. Proszę Cię, zostaw moją siostrę w spokoju. I... zostanę z nią.";
				link.l1 = "„Ty... co? Longway... ale dlaczego? Nie widzisz, czym się stała?”";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet4";
			}
			else
			{
				dialog.text = "Czy jesteś inny? Zmieniłeś się z czasem. Na gorsze. Początkowo byłeś uprzejmy i wyrozumiały. Ale potem stałeś się niegrzeczny, nawet bardziej niegrzeczny niż Rodenburg. A kiedy potrzebowałam dobrej łajby, by dogonić Van der Vinka, dałeś mi jakiś śmieć!";
				link.l1 = "Longway...";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet8";
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Raz wypłynąłem na morze i spędziłem wszystkie te lata, by odnaleźć i ocalić moją siostrę. A teraz jest tutaj i jest bezpieczna. Moja misja jest zakończona. I... Nazywam się Chang Tu. Longway to imię nadane mi przez zdrajcę Van Merdena, jeśli zapomniałeś. Ale Chang Tu jest wolnym człowiekiem. Długa podróż Chang Tu wreszcie dobiegła końca.";
			link.l1 = "Ona zmieni cię w sługę, jak kiedyś zrobił to Rodenburg. Będzie na ciebie naciskać, bo jesteś rodziną. I czy tak łatwo staniesz po stronie tej, która mnie skrzywdziła i "+sStr+" tyle bólu?";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet5";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet5":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Teraz to ty naciskasz na Chang Tu. Proszę, pozwól mi odejść. Jestem bardzo zmęczony. Jesteś dobrym człowiekiem, Kapitanie - Niebo może to potwierdzić. Ale nie jesteś moją rodziną. Ona jest. Jeśli nie zostanę, to wszystkie te lata pójdą na marne. Teraz będę jej gwiazdą przewodnią i rozpalę na nowo jej zgasły ogień - ciepły i kojący, nie spalający wszystko, czego dotknie.";
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				link.l1 = "„Hmm, masz rację. Może teraz za bardzo naciskam. Cóż, zawsze cię szanowałem. Życzę ci długo oczekiwanego spotkania z siostrą. Ale ostrzegam cię, nie znajdziesz z nią spokoju.”";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet6";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko") && !CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva")) 
				{
					pchar.questTemp.PZ_LongwayHochetMira = true;
					link.l1.go = "PZ_Longway_SisterDialog_ReactiaDevushek";
				}
				
			}
			else
			{
				link.l1 = "Nie możesz mnie teraz opuścić! Nadal muszę uratować "+sStr+"   od Levasseura! Chcesz, żebym poszła tam sama? Pomóż mi, Longway. A potem cię puszczę. Obiecuję ci.";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet6";
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet6":
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				dialog.text = "Mogę sobie z tym poradzić. Nie musisz się już o mnie martwić. Dziękuję.";
				link.l1 = "Wydaje się, że twoja siostra jest zła, że postanowiliśmy rozstać się pokojowo.";
			}
			else
			{
				dialog.text = "„Rozgryziesz to, Wielmożny Panie Kapitanie. Jesteś najinteligentniejszym człowiekiem, jakiego kiedykolwiek widziałem. Łatwo sobie poradzisz z tym robakiem, który tylko dręczy kobiety. Proszę cię, nie zmuszaj mnie. Moja siostra ma mi tyle do powiedzenia! A... nazywam się Chang Tu.”";
				link.l1 = "„Zdajesz sobie sprawę, że zostawiając mnie teraz, zdradzasz mnie?! Zwłaszcza zostając z nią - kobietą, która to wszystko zaczęła!”";
			}
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet7";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet7":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				dialog.text = "Nie lękaj się, Kapitanie. Choć mówi o mnie z lekceważeniem, jestem jej starszym bratem i ostatnim męskim krewnym. Możesz odejść. Nie pozwolę jej cię zabić. Żegnaj.";
				link.l1 = "Żegnaj... Chang Tu.";
				DeleteAttribute(pchar, "questTemp.PZ_LongwayRyadom");
				AddDialogExitQuest("PZ_BrothelTeleportVZal");	//Мирно разошлись
			}
			else
			{
				dialog.text = "Powiedziałem wszystko, co miałem do powiedzenia. Żegnaj, Kapitanie. I powodzenia. Chang Tu zawsze będzie wolnym człowiekiem. Nie zapomnij o tym.";
				link.l1 = "A to mam za to, że poświęciłam wszystko i pomogłam ci w poszukiwaniach?! Po tym, co oni robią "+sStr+" teraz?! Jesteś zdrajcą, Chang Tu. I zginiesz jako taki, obaj zginiecie, wy cholerni węże!";
				link.l1.go = "exit";
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				AddDialogExitQuest("MainHeroFightModeOn");
				AddDialogExitQuest("PZ_ChangShinAndLongwayFightMe");
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet8":
			dialog.text = "Nazywam się Chang Tu. Longway nie żyje. Zabiłeś go. Nie jesteś już moim Kapitanem. A teraz zginiesz. Moja rodzina wreszcie znajdzie spokój, a nasza gwiazda będzie jasno świecić na nocnym niebie.";
			if (IsCharacterPerkOn(pchar, "Trustworthy") && GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 85)
			{
				link.l1 = "(Godny zaufania) (Przywództwo) Longway... Chang Tu. Przestań. Wiem, że nie byłem dla ciebie idealnym Kapitanem. Ale czy naprawdę chcesz mnie za to tak bardzo zabić? Po tym wszystkim, przez co przeszliśmy? Najpierw Rodenburg, teraz poszukiwanie twojej siostry.";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet9";
				notification("Trustworthy", "Trustworthy");
				notification("Skill Check Passed", SKILL_LEADERSHIP);
			}
			else
			{
				link.l1 = "Wielmożny Panie Kapitanie, nie jestem twoją rodziną ani niańką. Wydaję rozkazy, nie zastanawiając się, czy przypadkiem cię nie obraziłem. Stawiasz żądania, jakbyśmy byli starymi małżonkami, na Boga...";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet15";
				if (!IsCharacterPerkOn(pchar, "Trustworthy")) notification("Perk Check Failed", "Trustworthy");
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 85) notification("Skill Check Failed (85)", SKILL_LEADERSHIP);
			}
			link.l2 = "Aj. Widzę to teraz. Jesteś tak samo zgniłą kanalią, która dba tylko o siebie... Longway. Tak jak twoja siostra. Moja rodzina przetrwa ten dzień. Twoja - nie. Idź do diabła!";
			link.l2.go = "PZ_Longway_SisterDialog_Ubezhdaet8_1";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet8_1":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetFightMode(pchar, true);
			DoQuestCheckDelay("PZ_ChangShinAndLongwayFightMe", 0.5);
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet9":
			dialog.text = "Jeśli mam wybierać między tobą a rodziną - wciąż wybieram rodzinę, nawet jeśli to trudny wybór.";
			link.l1 = "Rodzina, która nie kiwnęła palcem, gdy szukałeś jej przez te wszystkie lata? Och, ale wtedy nadeszła odpowiednia chwila! A ja porzuciłam wszystko, by ci pomóc. Ty, stojący tutaj, jesteś tego wynikiem. Do diabła, jestem dla ciebie większą rodziną niż ona, mój przyjacielu!";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet10";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet10":
			dialog.text = "„Masz rację. Jak zawsze, masz rację. Czy wybaczysz mi, Wielmożny Panie Kapitanie?”";
			link.l1 = "Nie ma za co wybaczać! Masz rację w jednym - nie zawsze byłem Kapitanem, na jakiego zasługujesz. Myślę, że teraz jesteśmy kwita. A tak przy okazji, jak mam się do ciebie zwracać od teraz? Longway? Czy może Chang Tu?";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet11";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet11":
			dialog.text = "Niech będzie Longway. Już się przyzwyczaiłem, że tak się do mnie zwracasz.";
			link.l1 = "„Zatem zapomnijmy o wszystkich nieporozumieniach i witamy ponownie na pokładzie, Longway.”";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet12";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet12":
			StartInstantDialog("PZ_ChangShin", "PZ_Longway_SisterDialog_Ubezhdaet13", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet13":
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			dialog.text = "Ty! Co ty mówisz?! Dlaczego przestałeś?! Zabij go! Dla niego zawsze będziesz tylko parobkiem! Twoją rodziną jestem ja i tylko ja!";
			link.l1 = "Jest taka zła, prawda, Longway? Nie jesteś już jego rodziną, Xing. To się skończyło, gdy dowiedziałaś się o przybyciu Longwaya na Archipelag i zdecydowałaś się to zignorować. Odchodzimy.";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet14";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet14":
			dialog.text = "Chyba nigdy nie miałem prawdziwej szansy wykorzenić w nim tej mentalności niewolnika. Nie mogę go uratować. W takim razie sam was oboje zabiję.";
			link.l1 = "„To ty jesteś tym, kogo nie da się uratować. Wiesz, byłam zbyt wyrozumiała i przebaczająca wobec ciebie. Ale to nawet lepiej. Myślę, że nawet Longway zrozumiał, jakim jesteś wężem. Nie będzie za tobą zbytnio tęsknił.”";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinFightWithLongway");
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet15":
			dialog.text = "Żarty są teraz nie na miejscu! Kryjesz za nimi swój strach i porażkę! Co tylko przekonuje mnie jeszcze bardziej. Broń się, de Maure! Bo Chang Tu nie ma zamiaru cię oszczędzać.";
			link.l1 = "Przykro mi, że tak to się skończyło. Ale jeśli tego właśnie chcesz, niech tak będzie. W takim razie nie otrzymasz ode mnie żadnej litości.";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinAndLongwayFightMe");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaDevushek":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) StartInstantDialog("Mary", "PZ_Longway_SisterDialog_ReactiaMary", "Quest\CompanionQuests\Longway.c");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) StartInstantDialog("Helena", "PZ_Longway_SisterDialog_ReactiaHelena", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayHochetMira"))
			{
				dialog.text = "Charles, posłuchaj...";
				link.l1 = "Helen?";
			}
			else
			{
				dialog.text = "Charles, Longway, przestań...";
				link.l1 = "Helen, lepiej schowaj się za mną teraz. Czułbym się bezpieczniej, gdybyś to zrobiła, na wypadek, gdyby nas zaatakowali.";
			}
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena2";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena2":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayHochetMira"))
			{
				dialog.text = "I'm so tired; I can hardly stand. I just want to get out of here. We're not going to drag Longway back to the ship if he doesn't want to come, are we? I'll be your navigator and first mate, my Captain. Hopefully, your most trusted and beloved too. Besides, he's got a point - we're not his family. She is, for better or worse.";
				link.l1 = "But what about her? She's the reason you were tortured; it was all her idea. And she's the one who kidnapped you.";
			}
			else
			{
				dialog.text = "  Ale oni nie będą, prawda? Po prostu wyjdźmy teraz, to wszystko. Jeśli to jest to, co on o nas myśli po wszystkim, co dla niego zrobiliśmy, nie ma sensu próbować zmieniać jego zdania. Czyny mówią głośniej niż słowa. Jeśli chce zostać ze swoją siostrą, niech zostanie. ";
				link.l1 = "Helen, tyle przez nią wycierpiałaś...";
			}
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena3";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena3":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayHochetMira"))
			{
				dialog.text = "Zostaw tę demonicę z jej demonami. Wkrótce pochłoną jej duszę. A nasze zasługują na dobry odpoczynek. Chodźmy.";
				link.l1 = "Tak. Chyba powinniśmy. Chodźmy stąd, mój aniele. A ty - Longway, czy Chang Tu - żegnaj.";
			}
			else
			{
				dialog.text = "Ale nie umarłem. I najgorsze się nie stało. Jestem tutaj, z tobą, i to jest najważniejsze. A Levasseur nie żyje. Bez niego, ona jest niczym. Jej miejsce traci pieniądze i wkrótce upadnie. A oni razem z nim. Chodźmy, mój kapitanie. Nie mamy tu już nic do roboty.";
				link.l1 = "Nie będę się kłócić, Helen.";
			}
			AddDialogExitQuest("PZ_BrothelTeleportVZal");		//Мирно разошлись
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena4":
			StartInstantDialog("Helena", "PZ_Longway_SisterDialog_ReactiaHelena5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena5":
			dialog.text = "„Dokąd idziesz?”";
			link.l1 = "Co, zaskoczony, że nie śpieszymy się, by rozlać twoje i twojej siostry wnętrzności, Longway? To jest różnica między nami. A ty wciąż myślisz, że to ja jestem złym facetem... Ale dobrze, spójrz. Jeśli chcesz mnie zabić, to znaczy, że będziesz musiał zabić także Helen. Jest ranna, kontuzjowana. Czy naprawdę chcesz to zrobić?";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena6";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena6":
			dialog.text = "Mhm.";
			link.l1 = "Widzę wątpliwości w twoich oczach, choć masz mnóstwo żalów do mnie. Ale weźmy przykład z Helen, dobrze? Nikt w naszej załodze nie jest milszy ani bardziej wyrozumiały od niej. Odchodzimy. I jeśli pozostało w tobie cokolwiek z dobroci lub rozsądku, nie staniesz nam na drodze.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena7";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena7":
			dialog.text = "Niech tak będzie. Przepraszam. Ale już nie jesteś moim Kapitanem.";
			link.l1 = "Jakoś to przeżyję. Życzę wam z siostrą wszystkiego najlepszego, mimo tego, co zrobiła. Żegnaj, Longway.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_BrothelTeleportVZal");		//Мирно разошлись
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary":
			dialog.text = "„Chodź, Charles, czas stłumić tę buntowniczą hołotę.”";
			link.l1 = "„Bóg wie, że nie chciałem tego robić... i nadal nie chcę.”";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary2";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary2":
			dialog.text = "„Nie?! Charles, posłuchaj mnie. Zrobiłeś dla niego tak wiele, a co dostałeś w zamian? Zdradę i podłe słowa, tak, co nie?! Naprawdę zamierzasz to puścić płazem?”";
			link.l1 = "Nie chcę przelewać krwi Longwaya. Nie zapomniałem, że kiedyś byliśmy przyjaciółmi.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary3";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary3":
			dialog.text = "Pierdolić takich przyjaciół - są gorsi niż wrogowie, tak, co nie? Charles, spójrz na mnie. Spójrz, co się ze mną stało - przez jego siostrę, która drwiła, obrażała i upokarzała mnie w drodze na tę cholerną wyspę!";
			link.l1 = "„Mary, rozumiem - jesteś teraz bardzo, bardzo zła...”";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary4";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary4":
			dialog.text = "O nie, Charles, nie jestem tylko zła, nie... jestem wściekła! I nie tylko z powodu tego, co ten nędzny mały drań ci powiedział! Popatrz na mnie jeszcze raz, Charles - i wyobraź sobie, ile więcej dziewcząt to przejdzie, jeśli tego nie zakończymy. Tutaj i teraz.";
			link.l1 = "Nie skrzywdzą już nikogo. Levasseur nie żyje.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary5";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary5":
			dialog.text = "Charles, czy naprawdę słuchałeś herezji, którą głosiła? Ona jest tak samo odpowiedzialna za to, co działo się w tej piwnicy, jak ten śmierdzący wieprz. Teraz spójrz na Longwaya - czy jak się teraz nazywa. Zobacz, jak szybko udało jej się przeciągnąć go na swoją stronę, tak, co nie? Kto wie, jakie jeszcze chory pomysły włoży mu do głowy ten zdrajca? Myślisz, że ta demonica będzie miała wiele trudności z popchnięciem go na drogę Levasseura? Nie myśl o tym, kim jest teraz, Charles. Pomyśl, jakim potworem może się stać za rok... albo nawet za miesiąc. Wiesz, że mam rację, prawda?";
			link.l1 = "Tak bardzo jak nienawidzę to przyznać, nie mam nic, co mogłoby ci zaprzeczyć, Mary...";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary6";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary6":
			StartInstantDialog("PZ_ChangShin", "PZ_Longway_SisterDialog_ReactiaMary7", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary7":
			dialog.text = "Ha-ha-ha! Fascynujące, cóż za występ. Dawno się tak serdecznie nie śmiałem. I trzeba przyznać, że ma odwagę.";
			link.l1 = "Zamknij mordę, suko.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary8";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary8":
			dialog.text = "To zabawne, prawda, de Maure? Chciałbym sam zobaczyć, jak Tu cię pokonuje. A twoja kobieta jest równie żądna krwi jak ja. Bardzo dobrze. Nie będę stał bezczynnie - szkoliłem się z Levasseur'em i niektórymi z najlepszych psów Tortugi. Zobaczmy, która para wyjdzie na wierzch.";
			link.l1 = "Nie miałeś zbyt dobrego nauczyciela. I wkurzyłeś Mary. Jesteś skończony. Nawet gdybym tu nie był, wasz duet nie miałby szans z nią.";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinAndLongwayFightMe");
		break;
		
		case "PZ_Longway_SisterDialog6":
			dialog.text = "„Tak. Nareszcie. Czy Longway może znów porozmawiać z moją siostrą, Wielmożny Panie Kapitanie? Niedługo.”";
			link.l1 = "Oczywiście. Tylko zrób to szybko - nie mamy dużo czasu.";
			link.l1.go = "PZ_Longway_SisterDialog7";
		break;
		
		case "PZ_Longway_SisterDialog7":
			dialog.text = "„Longway, zrób to szybko.”";
			link.l1 = "Dobrze.";
			link.l1.go = "PZ_Longway_SisterDialog7_1";
		break;
		
		case "PZ_ChangShin26":
			StartInstantDialog("СhangShin", "PZ_Longway_SisterDialog7_1", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog7_1":
			locCameraFromToPos(0.65, 2.59, -3.06, true, 0.23, 0.34, -5.21);
			
			sld = characterFromId("Longway");
			ChangeCharacterAddressGroup(sld, "Tortuga_brothelElite_room2", "goto", "goto8");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("PZ_ChangShin"));
			
			sld = characterFromId("PZ_ChangShin");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("Longway"));
			
			dialog.text = "A co chciałeś mi powiedzieć, bracie mój?";
			link.l1 = "„Ten Longway jest bardzo zawiedziony tobą, Xing.”";
			link.l1.go = "PZ_Longway_SisterDialog8";
		break;
		
		case "PZ_Longway_SisterDialog8":
			dialog.text = "(W mandaryńskim) Czemu nie mówisz w naszym języku skoro znowu chciałeś porozmawiać, Tu? Wstydzisz się go? Na twoim miejscu bardziej bym się wstydził twojego akcentu.";
			link.l1 = "„Nie. Longway nie ma tajemnic przed Wielmożnym Panem Kapitanem. Już nie.”";
			link.l1.go = "PZ_Longway_SisterDialog9";
		break;
		
		case "PZ_Longway_SisterDialog9":
			dialog.text = "„(po francusku) Najpierw Rodenburg, teraz de Maure. Zawsze potrzebujesz jakiegoś ‘monsieur’. Nie osiągnąłeś tu nic przez kilkanaście lat. Nie potrafisz nawet nauczyć się żadnego z ich języków. A są o wiele prostsze niż nasze! Jeśli ktoś jest rozczarowaniem, to ty.”";
			link.l1 = "Ale nie handluję kobietami. Nie biorę udziału w ich porywaniu i torturach.";
			link.l1.go = "PZ_Longway_SisterDialog10";
		break;
		
		case "PZ_Longway_SisterDialog10":
			dialog.text = "Jesteś poważny? Wyliczyć ci, co zrobiłeś dla Rodenburga? To, co ja robiłem, to przy tym dziecinna zabawa.";
			link.l1 = "Miałem cel - znaleźć ciebie. Ale ty nawet nie chciałaś mnie zobaczyć. A kiedy cię znalazłem, znalazłem potwora, a nie ciepłą, przewodnią gwiazdę, która kiedyś świeciła na mojej drodze.";
			link.l1.go = "PZ_Longway_SisterDialog11";
		break;
		
		case "PZ_Longway_SisterDialog11":
			dialog.text = "Potwór? Cóż, może masz rację. Nie jestem już tą radosną dziewczyną, którą znałeś. Gdybym taka pozostała, życie by mnie pożarło i wypluło. Musiałam wyhodować własne zęby. Moja gwiazda już dawno zgasła. Ale wciąż jestem twoją siostrą, Tu.";
			link.l1 = "Nie. Już nie jesteś moją siostrą.";
			link.l1.go = "PZ_Longway_SisterDialog12";
		break;
		
		case "PZ_Longway_SisterDialog12":
			dialog.text = "Tak łatwo się mnie poddajesz po tylu latach? Heh... A kto wie, może byłbym taki sam, gdybyś dotarł do domu na czas, by zabić Fermentelosa tamtego dnia?";
			link.l1 = "Masz rację. To także częściowo moja wina. To moja odpowiedzialność. I zakończę to. Wyzwolę cię z twojej udręki. Zakończę to żałosne istnienie.";
			link.l1.go = "PZ_Longway_SisterDialog13";
		break;
		
		case "PZ_Longway_SisterDialog13":
			dialog.text = "Naprawdę zamierzasz zabić własną siostrę, Chung Tu? Nie że ci się uda, ale fakt jest taki...";
			link.l1 = "Nie jesteś już moją siostrą. Xing umarła dziesięć lat temu. A dziś jest dzień, w którym Chung Tu w końcu umiera. Od teraz i na zawsze, nazywam się... Longway.";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinFightWithLongway");
		break;
		
		case "PZ_Longway_FlagMartinInfo_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Najpierw ratujemy Chang Xing.";
			link.l1 = "Co?! Nie wydaje się, żebyś to rozumiał, mój przyjacielu. Twoja siostra nie jest w bezpośrednim niebezpieczeństwie, ale "+sStr+" jest. I czy muszę Ci przypominać, że Chang Xing jest równie winny za to jak Martene i Thibaut?";
			link.l1.go = "PZ_Longway_FlagMartinInfo_2";
		break;
		
		case "PZ_Longway_FlagMartinInfo_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "To nieprawda! Ona jest...";
			link.l1 = "Masz jakiekolwiek pojęcie, co Levasseur może robić z "+sStr+"  podczas gdy my się tutaj kłócimy?";
			link.l1.go = "PZ_Longway_FlagMartinInfo_3";
		break;
		
		case "PZ_Longway_FlagMartinInfo_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Ale Chang Xing to wszystko, co mi zostało, Kapitanie... Twoja rodzina jest wciąż nienaruszona...";
			link.l1 = +sStr+" może nie być moją żoną, ale jest mi równie droga jak własna rodzina.";
			link.l1.go = "PZ_Longway_FlagMartinInfo_4";
		break;
		
		case "PZ_Longway_FlagMartinInfo_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Chang Xing jest moją ostatnią gwiazdą przewodnią, Kapitanie. Poza tym, jesteś mi winien za wyciągnięcie tego zeznania od Roberta Martena.";
			if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") && CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
			{
				link.l1 = "Pójdziemy za twoją siostrą, obiecuję. Ale Levasseur nie tknął jej przez cały ten czas."+sStr+" jest w o wiele większym niebezpieczeństwie niż Chang Xing. Pomóż mi ją najpierw ocalić, a będę ci bardzo wdzięczny.";
				link.l1.go = "PZ_Longway_FlagMartinInfo_VD1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") || CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
				{
					if (IsCharacterPerkOn(pchar, "Trustworthy") && GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 85)
					{
						link.l1 = "„(Godny zaufania) (Przywództwo) Ruszymy za twoją siostrą, obiecuję. Ale Levasseur nie tknął jej przez cały ten czas.”"+sStr+" jest w znacznie większym niebezpieczeństwie niż Chang Xing. Pomóż mi ją najpierw ocalić, a będę ci bardzo wdzięczny.";
						link.l1.go = "PZ_Longway_FlagMartinInfo_VD1";
						notification("Trustworthy", "Trustworthy");
						notification("Skill Check Passed", SKILL_LEADERSHIP);
					}
					else
					{
						link.l1 = "Słuchaj mnie! Twoja siostra jest bezpieczna. Ale "+sStr+" teraz jest w rękach zboczeńca, który może ją teraz torturować - albo gorzej! Czy myślisz, że Levasseur pozwoliłby twojej siostrze posiadać tak elegancki przybytek, gdyby traktował ją jak inne biedne dziewczęta w swoim lochu?!";
						link.l1.go = "PZ_Longway_FlagMartinInfo_netVD1";
						if (!IsCharacterPerkOn(pchar, "Trustworthy")) notification("Perk Check Failed", "Trustworthy");
						if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 85) notification("Skill Check Failed (85)", SKILL_LEADERSHIP);
					}
				}
			}
			link.l2 = "Nie będę tracił czasu na bezsensowne kłótnie. Każdy z nas ma swoje priorytety. Rozstaniemy się ponownie. Niech mój Bóg mi pomoże, a twój tobie.";
			link.l2.go = "PZ_Longway_FlagMartinInfo_Razdelimsya";
			link.l3 = "Masz rację. Jestem ci coś winna. Dobrze, niech będzie po twojemu. Poza tym, bez ciebie mogłabym nie poradzić sobie z Levasseurem i jego ludźmi. Ale jeśli coś się stanie "+sStr+"  podczas gdy zajmujemy się twoją siostrą...";
			link.l3.go = "PZ_Longway_FlagMartinInfo_IdemKSestreLongweya";
		break;
		
		case "PZ_Longway_FlagMartinInfo_Razdelimsya":
			dialog.text = "Dziękuję za zrozumienie, Wielmożny Panie Kapitanie. Powodzenia!";
			link.l1 = "I tobie, Longway.";
			link.l1.go = "PZ_Longway_FlagMartinInfo_SharleOdinVPodzemelie";
		break;
		
		case "PZ_Longway_FlagMartinInfo_IdemKSestreLongweya":
			dialog.text = "Puste groźby to czcze groźby, Wielmożny Panie Kapitanie. Musimy się spieszyć, aby zdążyć na czas.";
			link.l1 = "Mam nadzieję, że twój Bóg to słyszy. Chodźmy!";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TogetherLongwayGo");
		break;
		
		case "PZ_Longway_FlagMartinInfo_netVD1":
			dialog.text = "Z szacunku dla Ciebie, Wielmożny Panie Kapitanie, to puszczam płazem. Tylko tym razem. Następnym razem Cię uderzę. Teraz idę po moją siostrę, z Twoją zgodą lub bez niej.";
			link.l1 = "Nie będę tracić więcej czasu na kłótnie z tobą, Longway. W końcu wszyscy mamy coś, co jest nam droższe niż cokolwiek innego.";
			link.l1.go = "PZ_Longway_FlagMartinInfo_SharleOdinVPodzemelie";
		break;
		
		case "PZ_Longway_FlagMartinInfo_SharleOdinVPodzemelie":
			pchar.questTemp.PZ_DevushkaRanena_Legko = true;
			LAi_LocationDisableOfficersGen("Tortuga_Cave", true);
			DoQuestReloadToLocation("Tortuga_Cave", "reload", "reload2", "PZ_Etap6TortugaPodzemelie");
		break;
		
		case "PZ_Longway_FlagMartinInfo_VD1":
			dialog.text = "„Mm-hmm, dobrze, Wielmożny Panie Kapitanie. Ale wtedy musimy się śpieszyć.”";
			link.l1 = "Dobrze. Dziękuję, Longway.";
			link.l1.go = "PZ_Longway_FlagMartinInfo_VD2";
		break;
		
		case "PZ_Longway_FlagMartinInfo_VD2":
			pchar.questTemp.PZ_LongwayRyadom = true;
			pchar.questTemp.PZ_DevushkaRanena_Legko = true;
			LAi_LocationDisableOfficersGen("Tortuga_Cave", true);
			DoQuestReloadToLocation("Tortuga_Cave", "reload", "reload2", "PZ_Etap6TortugaPodzemelie");
		break;
		
		case "PZ_TortureRoom_Levasser_1":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "„No proszę, kogo my tu mamy... Cholera. Charles de Maure i jego skośnooki kundel.”";
				link.l1 = "Jest tu tylko jeden kundel. Jeśli chcesz go zobaczyć, spójrz w lustro, ty hugenocki bękarcie. Albo po prostu spójrz na swojego siostrzeńca. Chociaż on wygląda bardziej jak parszywy szczur.";
				link.l1.go = "PZ_TortureRoom_Levasser_2";
			}
			else
			{
				dialog.text = "Prosiłem, żebyś mi nie przeszkadzał! Ach, Charles de Maure, hehehe. Co za uparty mały szkodnik.";
				link.l1 = "Po prostu taki jestem. Teraz zamknij się do cholery i...";
				link.l1.go = "PZ_TortureRoom_Levasser_1_1";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne") || CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo") || CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal")) Achievment_Set("ach_CL_130");
			}
			locCameraSleep(true);
			sld = CharacterFromID("Tibo");
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto2");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("Levasser"));
		break;
		
		case "PZ_TortureRoom_Levasser_1_1":
			dialog.text = "Nie jesteś na swoim statku, szczeniaku! Jest tylko jeden człowiek na tej wyspie, i to ja!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_Etap6TortugaPytochnaya9");
		break;
		
		case "PZ_TortureRoom_Levasser_2":
			StartInstantDialog("Tibo", "PZ_TortureRoom_Levasser_3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_3":
			dialog.text = "Jak śmiesz, ty szumowino!";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_4";
			sld = CharacterFromID("Tibo");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_4":
			StartInstantDialog("Levasser", "PZ_TortureRoom_Levasser_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_5":
			dialog.text = "Spokojnie, siostrzeńcu! Pan de Maure zaraz dostanie lekcję dobrych manier.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_Etap6TortugaPytochnaya9");
			sld = CharacterFromID("Tibo");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("Levasser"));
		break;
		
		case "PZ_TortureRoom_Levasser_6":
			if (!CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal"))
			{
				dialog.text = "Czy dałem ci pozwolenie na piski?!";
			}
			else
			{
				dialog.text = "Gdzie się podział ten cały ogień, co, ślicznotko? Ah, chyba rozumiem...";
			}
			link.l1 = "Zostaw ją w spokoju, ty draniu!";
			link.l1.go = "PZ_TortureRoom_Levasser_7";
			LAi_SetActorType(npchar);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) LAi_ActorTurnToCharacter(npchar, CharacterFromID("Mary"));
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) LAi_ActorTurnToCharacter(npchar, CharacterFromID("Helena"));
		break;
		
		case "PZ_TortureRoom_Levasser_7":
			dialog.text = "Heh-heh-heh... Możesz krzyczeć i obrażać mnie ile chcesz, ale widzę, jak drżysz jak liść na wietrze. Widzę strach w twoich oczach. Ty i Henri macie to wspólne. Bez urazy, siostrzeńcze.";
			link.l1 = "Masz rację, to strach. Ale nie przed tobą, drań.";
			link.l1.go = "PZ_TortureRoom_Levasser_7_1";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_7_1":
			dialog.text = "Oczywiście, oczywiście. Słyszałem to już wcześniej - że nikogo się nie boisz, de Maure. Powiedziała mi to. 'O-o, Charles przyjdzie, Charles mnie uratuje... Charles to, Charles tamto...' Cóż, Charles jest tutaj. Charles ma miejsce w pierwszym rzędzie. Henri, zadbaj o wygodę naszego gościa.";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_8";
		break;
		
		case "PZ_TortureRoom_Levasser_8":
			StartInstantDialog("Tibo", "PZ_TortureRoom_Levasser_9", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_9":
			if (CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal"))
			{
				dialog.text = "Nie ma potrzeby, wujku. Obawiam się, że tym razem posunąłeś się trochę za daleko...";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "Wuju, będę potrzebować twojej pomocy w tej sprawie...";
				}
				else
				{
					dialog.text = "Powinienem go wykończyć, wujku, czy pozwolić mu najpierw popatrzeć?";
				}
			}
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_10";
			LAi_SetActorType(npchar);
			//LAi_ActorTurnToCharacter(npchar, CharacterFromID("Levasser"));
			LAi_ActorTurnToLocator(npchar, "goto", "goto8");
			locCameraFromToPos(-15.67, 2.57, -1.23, true, -17.49, 1.42, -3.26);
		break;
		
		case "PZ_TortureRoom_Levasser_10":
			StartInstantDialog("Levasser", "PZ_TortureRoom_Levasser_11", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_11":
			if (CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal"))
			{
				dialog.text = "To nie ja, to Monsieur Biały Rycerz tutaj zajął zbyt dużo czasu, aby przybyć na ratunek. Wygląda na to, że przedstawienie się skończyło, ha-ha-ha-ha!";
				link.l1 = "Boże, nie...";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_TortureRoom_Levasser_DevushkaMertva");
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "Tak myślałam. Jak udało ci się dożyć tego wieku? A tak przy okazji, to samo pytanie do ciebie, de Maure.";
					link.l1 = "Nie masz pojęcia, ile pytań mam do ciebie, rzeźniku!";
				}
				else
				{
					dialog.text = "Żałuję, że nasz mały występ nie ma publiczności... Ale nie sądzę, żeby Pan Uparciuch tutaj dał nam taką przyjemność.";
					link.l1 = "Jedyną przyjemność, jaką ktokolwiek dostaje, to ja - wypruwając ci flaki, rzeźniku!";
				}
				link.l1.go = "PZ_TortureRoom_Levasser_14";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				locCameraFromToPos(-16.74, 2.58, -0.51, true, -13.13, -0.72, 2.49);
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
			{
				locCameraFromToPos(-18.38, 1.77, 2.73, true, -20.53, 0.01, 0.32);
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
			{
				locCameraFromToPos(-16.97, 2.09, 3.98, true, -20.02, -0.17, 2.28);
			}
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Tibo"));
		break;
		
		case "PZ_TortureRoom_Levasser_12":
			dialog.text = "„Dalej, podnieś ją! Ha-ha-ha!”";
			link.l1 = "Przeklęte zwierzęta, sprawię, że pożałujecie, że się urodziliście!";
			link.l1.go = "PZ_TortureRoom_Levasser_13";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_13":
			DialogExit();
			EndQuestMovie();
			locCameraSleep(false);
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			LAi_SetPlayerType(pchar);
			locCameraTarget(PChar);
			locCameraFollow();
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				sld = CharacterFromID("Longway");
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
				Return_LongwayOfficer();
				PlaySound("VOICE\Russian\hambit\Longway-02.wav");
			}
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("Levasser");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld = CharacterFromID("Tibo");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "PZ_TortureRoom_Levasser_DevushkaMertva5");
		break;
		
		case "PZ_TortureRoom_Levasser_14":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Rzeźnik? Wolę myśleć o sobie jako o artyście, malarzu - czy przynajmniej spróbujesz zobaczyć to jako sztukę... Obserwuj. \nPodoba ci się moja praca? Prawdziwie jedno z moich arcydzieł. Mówiąc całkowicie szczerze, wolę blondynki, ale ona... Na koniec, wybaczyłem jej ten brzydki kolor włosów. To nie tylko włosy - dziewczyna jest jak ogień! Prawie się sparzyłem. Walczyła, gryzła, warczała jak dzikie zwierzę! Przypomniała mi czerwonoskórego dzikusa, z którym miałem dużo zabawy, nawet jeśli nie na długo...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Rzeźnik? Uważam siebie raczej za artystę, malarza - czy mógłbyś przynajmniej spróbować dostrzec w tym sztukę... Obserwuj.\nWidzisz, jeszcze z nią nie skończyłem - na tym płótnie jest jeszcze dużo pustego miejsca. Nie tylko jest piękna, ale też twarda jak skała i zimna jak lód. Musiałem nawet trochę się napocić, żeby zmusić ją do krzyku. Wytrzymała do końca, tylko po to, by nie dać mi przyjemności usłyszenia jej pięknego głosu.";
			}
			link.l1 = "Wypuść ją natychmiast, degeneracie.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_Etap6TortugaPytochnaya13");
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_15":
			dialog.text = "Dokąd myślisz, że się wybierasz? Ten kawał mięsa to teraz moja własność. Tak samo jak wszystko wokół - to miasto, ta twierdza... Ja jestem Tortuga. A ty i Poincy, ten śmierdzący stary indor, nigdy tego nie zmienicie.";
			link.l1 = "Levasseur, ty...";
			link.l1.go = "PZ_TortureRoom_Levasser_16";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_16":
			dialog.text = "Dla ciebie to Signor de René de Buaduflé de Lettre.";
			link.l1 = "Nie obchodzi mnie to. Wyciągnij swoją szablę i pokaż mi, ile jesteś wart w walce – z mężczyzną, a nie bezbronną dziewczyną.";
			link.l1.go = "PZ_TortureRoom_Levasser_17";
		break;
		
		case "PZ_TortureRoom_Levasser_17":
			dialog.text = "Ale z ciebie człowiek! Ale masz rację, sam jestem zmęczony tą całą gadką. Chcę wrócić do... mojej damy. Ale zadam ci jeszcze jedno pytanie. Jak się tu dostałeś? Kto zdradził położenie tego miejsca? Tylko garstka ludzi o nim wie.";
			if (CheckAttribute(pchar, "questTemp.PZ_FlagMartinInfo"))
			{
				link.l1 = "„Wasz wspólny przyjaciel, Martene, zaśpiewał jak słowik. A właściwie bardziej zapiszczał jak świnia w rzeźni...”";
				link.l1.go = "PZ_TortureRoom_Levasser_FlagMartinInfo_1";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_FlagMarselinaInfo"))
			{
				link.l2 = "Może lepiej zachować to w tajemnicy przed tobą. Obawiam się, że mogłoby to zranić twoje ego, Signor de René... coś tam.";
				link.l2.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_1";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
			{
				link.l3 = "Jedna z twoich ofiar, Levasseur.";
				link.l3.go = "PZ_TortureRoom_Levasser_FlagShinInfo_1";
			}
		break;
		
		case "PZ_TortureRoom_Levasser_FlagShinInfo_1":
			dialog.text = "Kłamca, łajdaku! Nikt nie opuszcza tych murów!";
			link.l1 = "Użyj pamięci, no dalej. Był jeden. Chang Xing.";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagShinInfo_2";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagShinInfo_2":
			dialog.text = "Nie ma mowy. Nie ona. Niektóre z moich pomysłów zrodziły się dzięki tej małej diablicy. O-o, wiele się od siebie nauczyliśmy, hehe. Czy postanowiła na koniec oczyścić swoje sumienie? Wątpię. Przecież wszystko z niej dawno temu wyryłem!";
			link.l1 = "Teraz będę cię osuszać. Kropla po kropli.";
			link.l1.go = "PZ_TortureRoom_Levasser_Bitva";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMartinInfo_1":
			dialog.text = "A ty nazywasz mnie rzeźnikiem, ty nędzny hipokryto! Heh-heh... Ale dopóki on płonie w piekle, nie mam się czego obawiać.";
			link.l1 = "Czeka tam na ciebie. I twój łajdak z siostrzeńca również. Nie zawiedźmy go.";
			link.l1.go = "PZ_TortureRoom_Levasser_Bitva";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_1":
			dialog.text = "Co powiesz na to, żebym trochę bardziej uszkodził tę zabawkę? Przeciął jej brzuch lub gardło i patrzył, jak wykrwawia się, podczas gdy ty próbujesz się do niej dostać...";
			link.l1 = "Cokolwiek powiesz, Levasseur, cokolwiek powiesz... Twoja żona przesyła pozdrowienia. A wraz z nimi, pożegnalny ukłon.";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_2";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_2":
			dialog.text = "CO?! Kha-kha... Cholera Marceline... Ty nędzna suka, suka, suka, suka!";
			link.l1 = "Tak właśnie jest. Jesteście siebie warci. Ona jednak trochę lepiej myśli trzeźwo. Na pierwszy rzut oka przynajmniej.";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_3";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_3":
			dialog.text = "Zamierzam wbić jej kurzą głowę na pal. Ale zanim to nastąpi... o-o, wiele, wiele rzeczy spotka tę dziwkę... Nawet dam mojej nowej zabawce chwilę odpocząć. Czekaj! Mam lepszy pomysł. Pożyczę ją Henremu. Na jakiś czas, oczywiście.";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_4";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_4":
			StartInstantDialog("Tibo", "PZ_TortureRoom_Levasser_FlagMarselinaInfo_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_5":
			dialog.text = "Naprawdę? Dziękuję, Wujku!";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_6";
			CharacterTurnByChr(npchar, CharacterFromID("Levasser"));
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_6":
			StartInstantDialog("Levasser", "PZ_TortureRoom_Levasser_FlagMarselinaInfo_7", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_7":
			dialog.text = "Najpierw zasłuż na to - pomóż mi z tym, co nie?";
			link.l1 = "Zaraz straci nad sobą panowanie.";
			link.l1.go = "PZ_TortureRoom_Levasser_Bitva";
			CharacterTurnByChr(npchar, CharacterFromID("Tibo"));
		break;
		
		case "PZ_TortureRoom_Levasser_Bitva":
			DialogExit();
			EndQuestMovie();
			locCameraSleep(false);
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			LAi_SetPlayerType(pchar);
			locCameraTarget(PChar);
			locCameraFollow();
			
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				sld = CharacterFromID("Longway");
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
				Return_LongwayOfficer();
				PlaySound("VOICE\Russian\hambit\Longway-02.wav");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = CharacterFromID("Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sld = CharacterFromID("Helena");
			LAi_SetImmortal(sld, true);
			
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("Levasser");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetCheckMinHP(sld, 1, true, "PZ_Etap6TortugaPytochnaya19");
			sld = CharacterFromID("Tibo");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		break;
		
		case "PZ_TortureRoom_Longway_1":
			dialog.text = "Wielmożny Panie Kapitanie... Longway składa swoje kondolencje. Zrobiliśmy wszystko, co w naszej mocy.";
			link.l1 = "Nie wszystko, nie wystarczająco dużo.";
			link.l1.go = "PZ_TortureRoom_Longway_2";
		break;
		
		case "PZ_TortureRoom_Longway_2":
			dialog.text = "Longway zamierza znaleźć Chang Xinga. Pójdziesz ze mną?";
			link.l1 = "„Tak, idę z tobą, Longway. Ale pamiętaj - twoja siostra również miała bardzo aktywną rolę w tym krwawym spektaklu. Będzie musiała się bardzo postarać, by przekonać mnie, żebym jej oszczędził. A ty jej nie pomożesz. No, chodź, czas to zakończyć.”";
			link.l1.go = "PZ_TortureRoom_Longway_3";
		break;
		
		case "PZ_TortureRoom_Longway_3":
			DialogExit();
			Return_LongwayOfficer();
			chrDisableReloadToLocation = false;
		break;
		
		case "PZ_TortureRoom_Devushka_1":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Charles, wiedziałam to, tak, co nie? Wiedziałam, że przyjdziesz! Zawsze to robisz, prawda?";
					link.l1 = "Nie chciałbym tego testować po raz czwarty, Mary... Ci łajdacy, oni...";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "„Och, mój Kapitanie, nie zdajesz sobie sprawy, jak bardzo jesteś na czas. Ci... ci potwory...”";
					link.l1 = "To już koniec, Helen. Już dobrze, wszystko się skończyło. O mój Boże, co oni ci zrobili...";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "„Charles, jesteś tutaj! Wiedziałam, wiedziałam, tak, co nie?”";
					link.l1 = "Płynąłem pod pełnymi żaglami, uciekając na złamanie karku, Mary. Ty... czy oni?..";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Mój Kapitanie... Jesteś tutaj... Już niemal straciłam nadzieję...";
					link.l1 = "Przyszedłem tak szybko, jak mogłem, Helen. Przepraszam, że to tak długo trwało.";
				}
				locCameraFromToPos(-15.32, 1.24, 1.31, true, -14.25, -1.00, -1.50);
			}
			link.l1.go = "PZ_TortureRoom_Devushka_2";
		break;
		
		case "PZ_TortureRoom_Devushka_2":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Nie, Charles, nie. Próbowali, ale walczyłam z nimi jak tylko mogłam. Dlatego tak mnie poturbowali... Proszę, Charles, wyjdźmy stąd... tak, co nie?";
					link.l1 = "Już się robi, moja droga. Jeszcze jedna rzecz do zrobienia.";
					link.l1.go = "PZ_TortureRoom_Devushka_3";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Nie zrobili tego, Charles! Nie zrobili. Reszta się zagoi. Proszę, zabierz mnie stąd.";
					link.l1 = "Oczywiście, moja droga. Została tu tylko jedna rzecz do zrobienia.";
					link.l1.go = "PZ_TortureRoom_Devushka_3";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Nie, Charles, nie. Próbowali, ale zdążyłeś w samą porę. Jak wtedy. Ile to już razy?";
					link.l1 = "Nie liczyłem, Mary. I nigdy nie będę.";
					link.l1.go = "PZ_TortureRoom_Devushka_2_1";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "„Dotarłeś tutaj... w samą porę. Najgorsze nie stało się. Teraz, proszę, wyjdźmy stąd. Gdziekolwiek.”";
					link.l1 = "Wstań, Helen. Idź na górę. Najpierw muszę zająć się tym draniem.";
					link.l1.go = "PZ_TortureRoom_Devushka_3";
				}
			}
		break;
		
		case "PZ_TortureRoom_Devushka_2_1":
			dialog.text = "I nie przestanę liczyć. Teraz opuśćmy to miejsce, proszę.";
			link.l1 = "Oczywiście, moja droga. Nie mamy tu nic więcej do zrobienia. Poza jedną rzeczą.";
			link.l1.go = "PZ_TortureRoom_Longway_3";
		break;
		
		case "PZ_TortureRoom_Devushka_3":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko")) AddPassenger(pchar, npchar, false);
			LAi_SetPlayerType(pchar);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) Return_MaryOfficer();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) Return_HelenaOfficer();
		break;
		
		case "PZ_TortureRoom_Levasser_18":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "Więc co, kha-kha, nie masz odwagi, smarkaczu? Poproś swojego żółtoskórego wieprza, żeby ci pomógł... Albo zrób to sam, a wtedy będziesz miał powód, żeby opowiedzieć Poincy, jaki jesteś odważny.";
				link.l1 = "Wolałbym raczej opowiedzieć wszystkim, jakim tchórzliwym gnojem byłeś.";
			}
			else
			{
				dialog.text = "„Co, naprawdę chcesz patrzeć, jak wykrwawiam się na śmierć? Czerpiesz z tego przyjemność, co? Opowiesz swojej kobiecie, jaki jesteś bohater. Widzisz ten szkielet na ścianie? Żona bankiera z Santiago... Jej mąż też myślał, że jest bohaterem, ale okazał się tylko dobrym krzykaczem - kiedy obracałem go na tym kole...”";
				link.l1 = "Mógłbym cię na to wrzucić, łajdaku, ale boję się, że nie utrzymałoby ciężaru twojego zadka.";
			}
			link.l1.go = "PZ_TortureRoom_Levasser_19";
		break;
		
		case "PZ_TortureRoom_Levasser_19":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "Tchórzliwy? Och, kha-kha, daj spokój...";
				link.l1 = "Okrucieństwo nie jest przeciwieństwem tchórzostwa. Ale ktoś taki jak ty nie rozpozna różnicy.";
				link.l1.go = "PZ_TortureRoom_Levasser_20";
			}
			else
			{
				dialog.text = "To bardzo sprytne. Zapamiętaj moje słowa, de Maure: umrzesz tak samo jak ten ważniak, ochrypły od własnych krzyków i głuchy od płaczu twoich...";
				link.l1 = "Spłoń w piekle, szumowino.";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_TortureRoom_Levasser_Mertv1");
			}
		break;
		
		case "PZ_TortureRoom_Levasser_20":
			dialog.text = "„Aye, nie jestem wielkim filozofem, przyznaję to. Widzisz ten szkielet na ścianie, de Maure? To wszystko, co zostało z żony bankiera Santiago. Też lubił dużo gadać, ale wszystko się skończyło, gdy zacząłem nawijać jego ciało na to koło. Zostało tylko krzyczenie, które prawie mnie ogłuszyło...”";
			link.l1 = "Załatwmy to i miejmy z głowy.";
			link.l1.go = "PZ_TortureRoom_Levasser_21";
		break;
		
		case "PZ_TortureRoom_Levasser_21":
			StartInstantDialog("Longway", "PZ_TortureRoom_Levasser_22", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_22":
			dialog.text = "Poczekaj chwilę, Wielmożny Panie Kapitanie... Nie bądź taki szybki.";
			link.l1 = "Co się stało, Longway?";
			link.l1.go = "PZ_TortureRoom_Levasser_23";
		break;
		
		case "PZ_TortureRoom_Levasser_23":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Nie zabijaj go. Zbyt proste. Zasługuje na coś gorszego.";
			link.l1 = "Jesteś wściekły na swoją siostrę, mój przyjacielu. A ja jestem wściekły na to, co on zrobił "+sStr+"... i co mógłby jej zrobić. Ale nie jestem zwierzęciem jak on. Mógłbym go przypalić węglem z tego koksownika, połamać mu kości na tym kole... Mógłbym go skuć kajdanami i pozwolić mu umrzeć z upływu krwi. Ale nie mogę ryzykować, że któryś z jego popleczników go uratuje. Nie mogę zaryzykować.";
			link.l1.go = "PZ_TortureRoom_Levasser_24";
		break;
		
		case "PZ_TortureRoom_Levasser_24":
			dialog.text = "„Poczekaj, Wielmożny Panie Kapitanie. Nie to miałem na myśli. Mówię o Poincym.”";
			link.l1 = "A co z nim?";
			link.l1.go = "PZ_TortureRoom_Levasser_25";
		break;
		
		case "PZ_TortureRoom_Levasser_25":
			dialog.text = "Pomyśl, jakby cię wynagrodził, gdybyś przyprowadził mu to zwierzę żywe. Obsypałby cię dublonami. A ten łotr wolałby tu umrzeć, niż gnić w lochu w Capsterville.";
			link.l1 = "„Możesz mieć rację, Longway. Ale nie wiem, co dokładnie zaszło między tym draniem a Kawalerem. Wierz mi, znam tę bandę lepiej niż ty. Jeśli chodzi tylko o pieniądze, jak mówią, ci dwaj mogą się dogadać. Poincy mógłby go puścić, a kolejna taka sala mogłaby pojawić się na jakiejś innej wyspie lub w jednym z miast Starego Świata.”";
			link.l1.go = "PZ_TortureRoom_Levasser_26";
			link.l2 = "Nie najgorszy pomysł, Longway. Wątpię jednak, czy Chevalier będzie aż tak hojny... To nie leży w jego naturze. Ale dla mnie to i tak nie chodzi o pieniądze. Podnieście go! I opatrzcie jego rany, żeby nie umarł przed czasem.";
			link.l2.go = "PZ_TortureRoom_Levasser_28";
		break;
		
		case "PZ_TortureRoom_Levasser_26":
			StartInstantDialogNoType("Levasser", "PZ_TortureRoom_Levasser_27", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_27":
			dialog.text = "„Ale najpierw przyjdę po was. I po twojego kumpla. Ciebie nie tknę, wąskooki człowieku - nie jesteś wart mojego czasu.”";
			link.l1 = "Widzisz, Longway? To wszystko musi się teraz skończyć. Tu i teraz.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_TortureRoom_Levasser_Mertv1");
		break;
		
		case "PZ_TortureRoom_Levasser_28":
			StartInstantDialogNoType("Levasser", "PZ_TortureRoom_Levasser_29", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_29":
			dialog.text = "Poczekaj chwilę, kapitanie, poczekaj chwilę, kha-kha.";
			link.l1 = "Co to jest, Monsieur były gubernatorze?";
			link.l1.go = "PZ_TortureRoom_Levasser_30";
		break;
		
		case "PZ_TortureRoom_Levasser_30":
			dialog.text = "Mój klucz jest gdzieś w tym pokoju. Otwiera skrzynię w moim gabinecie. Jest tam dwieście tysięcy w srebrze i piękna klinga. Jeśli to za mało, w sypialni mojej żony, w komodzie, jest kolekcja drogocennych kamieni.";
			link.l1 = "Hmm, a co chcesz w zamian?";
			link.l1.go = "PZ_TortureRoom_Levasser_31";
		break;
		
		case "PZ_TortureRoom_Levasser_31":
			dialog.text = " Kula. Wykończ mnie. Tu i teraz.";
			link.l1 = "Co z Kawalerem de Poincy? Słyszałem, że jesteście starymi przyjaciółmi... Nie chcesz się z nim zobaczyć?";
			link.l1.go = "PZ_TortureRoom_Levasser_32";
		break;
		
		case "PZ_TortureRoom_Levasser_32":
			dialog.text = "Do diabła z Poincy! Więc zgadzasz się, czy nie?";
			link.l1 = "Nie do końca, Monsieur de... Nie chcę wymieniać całego twojego nazwiska.";
			link.l1.go = "PZ_TortureRoom_Levasser_33";
		break;
		
		case "PZ_TortureRoom_Levasser_33":
			dialog.text = "Czy to nie wystarczy? Dobrze, jest więcej...";
			link.l1 = "Krzyki twoich ofiar musiały cię ogłuszyć, Levasseur. Mówiłem ci, to nie chodzi o pieniądze. Boisz się Poincy'ego nie bez powodu, co? Nawet nie chcę wiedzieć, co ci zrobi. Ale jeśli to będzie choć trochę odpłatą za twoje... rzemiosło, niech tak będzie.";
			link.l1.go = "PZ_TortureRoom_Levasser_34";
			pchar.questTemp.PZ_LevasserPlenen = true;
			pchar.questTemp.PZ_LevasserPobezhden = true;
		break;
		
		case "PZ_TortureRoom_Levasser_34":
			dialog.text = "Więc to jest to, kim naprawdę jesteś, kha-kha... Nie lepszy ode mnie.";
			link.l1 = "Dość. Longway - podnieś go!";
			link.l1.go = "PZ_TortureRoom_Levasser_35";
		break;
		
		case "PZ_TortureRoom_Levasser_35":
			DialogExit();
			
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1 = "locator";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1.location = "Tortuga_Torture_room";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1.locator_group = "reload";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1.locator = "reload1";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition = "PZ_TortureRoom_Levasser_ObratnoNaBereg";
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) Return_MaryOfficer();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) Return_HelenaOfficer();
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom")) Return_LongwayOfficer();
			sld = CharacterFromID("Levasser");
			sld.location = "None";
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
				{
					dialog.text = "Nasza łajba... Nigdy bym nie pomyślała, że tak się ucieszę na jej widok... tak, co nie? Nareszcie ten koszmar się skończył.";
				}
				else
				{
					dialog.text = "W końcu to koniec. Dokąd teraz, Charles?";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
				{
					dialog.text = "Nie mogę uwierzyć, że to już koniec... Co teraz robimy, mój Kapitanie?";
				}
				else
				{
					dialog.text = "„No cóż, to wszystko, mój Kapitanie. Co teraz robimy?”";
				}
			}
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
			{
				link.l1 = "Ach, to jeszcze nie koniec. Chang Xing... Ta historia naprawdę kończy się dopiero wtedy, gdy uzyskam od niej odpowiedzi.";
				link.l1.go = "PZ_Etap6_NaBeregu_DevaZdorovaya_2";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
				{
					link.l1 = "Obierz kurs na Capsterville. Czas, aby Monsieur Levasseur przeszedł do historii.";
				}
				else
				{
					link.l1 = "Misja Kawalera jest zakończona. Muszę mu o tym donieść. Jednakże pominę niektóre szczegóły. Mam tylko nadzieję, że dotrzyma słowa i Michel zostanie uwolniony...";
				}
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_Final_SdaemKvestPuansi");
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Ja też, tak, co nie? Więc idę z tobą. I nawet nie próbuj się ze mną kłócić, Charles.";
				link.l1 = "Mary, kochana, musisz odpocząć. Jesteś o krok od omdlenia...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Pójdę z tobą.";
				link.l1 = "Helen, prawie zginęłaś z rąk tego diabła. Ledwo stoisz na nogach...";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaZdorovaya_3";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Potrzebuję cię, Charles. A ty potrzebujesz mnie. I jeśli ktoś dziś wieczorem zemdleje, to będzie to Chang Xing. Na podłodze jej burdelu, z kulą między oczami!";
				link.l1 = "„Aye, Levasseur nie wybił z ciebie ducha walki. Wysłałbym cię z powrotem na statek, ale wiem, że i tak byś za mną poszedł...”";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "  Ale wciąż mogę trzymać ostrze. Charles, muszę tam być. Muszę zrozumieć, co ją do tego skłoniło. Czy rozumiesz, dlaczego to jest dla mnie takie ważne?";
				link.l1 = "Rozumiem, że potrzebujesz odpoczynku i leczenia. I to długiego.";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaZdorovaya_4";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Znasz mnie zbyt dobrze, Charles, tak, co nie? Więc darujmy sobie gadkę i dokończmy to.";
				link.l1 = "Rób, jak chcesz. Ale miej się na baczności. Nikt nie wie, jakie niespodzianki na nas czekają.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "To może poczekać. Przyszedłeś po mnie, a teraz idę z tobą. Czy tego chcesz, czy nie.";
				link.l1 = "Widzę, że nadal masz nerwy, Helen. Dobrze. Zostań za mną, i na miłość boską, bądź ostrożna.";
			}
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_SDevushkoyKShin");
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_1":
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Nasza łajba... Nie mogę uwierzyć, że znów na nią wejdę, tak, co nie...";
					link.l1 = "„Czeka na ciebie, Mary. Obfity posiłek i miękkie łóżko też...”";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Ugh... Nie sądziłam, że dotrę do łodzi na własnych nogach.";
					link.l1 = "Jesteś najbardziej wytrwałą osobą, jaką kiedykolwiek znałem, Helen. Teraz wejdź do środka i potem do łóżka...";
				}
				link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_2";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Nasza łajba... Nie mogę uwierzyć, że znowu na nią wejdę, tak, co nie...";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Ugh... Nie sądziłem, że uda mi się dotrzeć do łodzi na własnych nogach.";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
				{
					link.l1 = "Obierz kurs na Capsterville. Czas, by pan Levasseur stał się częścią historii.";
				}
				else
				{
					link.l1 = "Misja Kawalera została zakończona. Muszę mu o tym zameldować. Jednak niektóre szczegóły pominę. Mam tylko nadzieję, że dotrzyma słowa i Michel zostanie uwolniony...";
				}
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_Final_SdaemKvestPuansi");
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "„A ty, Charles... Dlaczego masz taki wyraz twarzy? Znowu coś knujesz, prawda?”";
				link.l1 = "Chang Xing. Muszę się do niej również dostać.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "A ty? Dokąd się wybierasz?";
				link.l1 = "Aby zobaczyć Chang Xing. Ona jest ostatnim rozdziałem tego koszmaru.";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_3";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "W takim razie idę z tobą! Jest mi dużo winna, tak, co nie?";
				link.l1 = "„Mary, droga, ledwo dotarłaś do łodzi. I teraz nie możesz trzymać ostrza. Sprawię, że zapłaci za to, co ci zrobiła, przysięgam na Boga. Ale będę się czuć znacznie lepiej, jeśli zostaniesz na statku, wiedząc, że jesteś bezpieczna.”";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Mój Kapitanie, tak bardzo chciałabym z tobą pójść... Proszę, bądź ostrożny. Kto wie, do czego jeszcze jest zdolna? Trzymała mnie, gdy ten szczeniak Thibaut...";
				link.l1 = "Najgorsze już za nami, Helen. Wkrótce to się skończy, obiecuję.";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_4";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "Cóż, przynajmniej Longway będzie się tobą opiekował pod moją nieobecność. Ale jeśli coś ci się stanie, sam poślę jego i Chang Xinga do piachu!";
					link.l1 = " Będzie dobrze. Teraz idź odpocząć. Wrócę, zanim się obejrzysz. ";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_7";
				}
				else
				{
					dialog.text = "Gdzie się podział Longway, Charles?";
					link.l1 = "„Poszedł za Chang Xingiem beze mnie. Nie mogłem go powstrzymać, ale co mogłem zrobić?”";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_5";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "„Cóż, przynajmniej Longway idzie z tobą. To jakaś pociecha, przynajmniej.”";
					link.l1 = "Widzisz? Nie ma potrzeby się martwić. Nie będę długo.";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_7";
				}
				else
				{
					dialog.text = "Gdzie jest Longway? Właśnie zauważyłem, że go tu nie ma.";
					link.l1 = "Poszedł do swojej siostry beze mnie. Nie obwiniam go. Czekał zbyt długo na tę chwilę.";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_5";
					
				}
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_5":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Charles, mam złe przeczucie co do tego...";
				link.l1 = "  Wiem.  Ten koszmar trwał zbyt długo, a koniec jest bliski. Najgorsze już za nami.  ";
				link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_6";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Kto wie, co on planuje, Charles? Miej oczy szeroko otwarte, tak, co nie?";
				link.l1 = "Zrobię to. Wrócę wkrótce, Helen."link.l1.go ="Nie mogę się doczekać, aż w końcu z tobą porozmawiam, Wielmożny Panie Kapitanie.";
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_6":
			dialog.text = "Obiecaj mi, że będziesz gotowy na wszystko.";
			link.l1 = "Jestem i będę. Wrócę niedługo, Mary.";
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_7";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_7":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom")) StartInstantDialog("Longway", "PZ_Etap6_NaBeregu_DevaBolnaya_8", "Quest\CompanionQuests\Longway.c");
			else
			{
				DialogExit();
				LAi_SetPlayerType(pchar);
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = CharacterFromID("Mary");
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sld = CharacterFromID("Helena");
				LAi_ActorRunToLocation(sld, "reload", "sea", "", "", "", "", -1);
				sld.location = "None";
				AddQuestRecord("PZ", "51");
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) AddQuestUserData("PZ", "sText", "Mary");
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) AddQuestUserData("PZ", "sText", "Helen");
				PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition.l1 = "location";
				PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition.l1.location = "Tortuga_brothelElite";
				PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition = "PZ_Etap6_BrothelPoiskSestry";
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_8":
			dialog.text = "„Longway  pomógł tobie, Kapitanie. Teraz to twoje słowo, by dotrzymać.”";
			link.l1 = "Słyszałeś wszystko, Longway. Chodźmy zobaczyć się z twoją siostrą.";
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_9";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_9":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Wielmożny Panie Kapitanie, Longway ma ostatnią prośbę: pozwól Chang Xing wyjaśnić się. Wysłuchaj jej, zanim podejmiesz jakiekolwiek decyzje.";
			link.l1 = "Co się stało z "+sStr+"jest na niej. Ale dam jej najpierw szansę na wyjaśnienie.";
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_10";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_10":
			dialog.text = "Longway ufa twojemu słowu, twojemu osądowi i twojej życzliwości.";
			link.l1 = "Kolego, w tym krwawym bałaganie nie ma miejsca na rozsądek ani dobroć. Najwyższy czas to zakończyć.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_SLongwayKShin");
		break;
		
		case "PZ_LongwayPrishelOdin":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sStr = "Helen";
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				dialog.text = "Wielmożny Panie Kapitanie...";
				link.l1 = +sStr+" nie żyje.";
				link.l1.go = "PZ_LongwayPrishelOdin2";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					dialog.text = "Kapitana, pani "+sStr+"„, to przyjemność cię widzieć. To jest... Chang Xing.”";
					link.l1 = "Domyśliłem się, Longway. Odsuń się. Miałeś mnóstwo czasu, aby porozmawiać z siostrą. Teraz musi odpowiedzieć przed "+sStr+"  za pomoc pachołkom Levasseura w porwaniu jej.";
					link.l1.go = "PZ_LongwayPrishelOdin7";
				}
				else
				{
					dialog.text = "Przyszedłeś... Gdzie jest dama "+sStr+"„? Czy ona...?”";
					link.l1 = "Nie, Longway. Dzięki Bogu, nie. Zabralem ją na statek. W przeciwnym razie, nie prowadziłbym teraz tej rozmowy. Jednakże, to wciąż nie będzie ani łatwe, ani przyjemne.";
					link.l1.go = "PZ_LongwayPrishelOdin12";
				}
			}
		break;
		
		case "PZ_LongwayPrishelOdin2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Chang Xing i ja składamy nasze kondolencje...";
			link.l1 = "Wyrazy współczucia od Chang Xinga?! Możesz równie dobrze złożyć kondolencje w imieniu Levasseura, Longway! Doskonale wiesz, że brała udział w porwaniu "+sStr+"  razem z innymi jego sługusami! A teraz jej nie ma...";
			link.l1.go = "PZ_LongwayPrishelOdin3";
		break;
		
		case "PZ_LongwayPrishelOdin3":
			dialog.text = "„My... Rozumiem, co teraz czujesz, Wielmożny Panie Kapitanie.”";
			link.l1 = "O, naprawdę?";
			link.l1.go = "PZ_LongwayPrishelOdin4";
		break;
		
		case "PZ_LongwayPrishelOdin4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Straciłem rodziców, jak pamiętasz. Jeśli w ogóle pamiętasz. Poza tym, to nie Chang Xing torturował i zabijał"+sStr+"Rozumiem twój ból, twój gniew. Ale wina mojej siostry nie jest tak wielka, byś ją rozważał. Proszę, wysłuchaj mnie.";
			link.l1 = "Pamiętam. Wysłucham twojej opowieści. Ale zrób to szybko! I wiedz, że nie mogę pozostawić czegoś takiego bez kary!";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayPrishelOdin_ChangShinNext");
		break;
		
		case "PZ_LongwayPrishelOdin5":
			dialog.text = "Więc lepiej opowiem to wszystko jeszcze raz, Monsieur de Maure. Nasz Tu mówi po francusku tak źle, że prawie go zaatakowałeś.";
			link.l1 = "Trzeba było trzymać język za zębami. Nie zamierzałem atakować Longwaya, ale ty... To przez ciebie ona zginęła.";
			link.l1.go = "PZ_LongwayPrishelOdin6";
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
		break;
		
		case "PZ_LongwayPrishelOdin6":
			dialog.text = "Sprzeczałbym się z tym, ale zdaję sobie sprawę, że wolałbym tego nie robić. Tu mówił o tobie jako o osobie godnej szacunku i zrozumienia. Ale czy tak naprawdę jest? Czy ma sens, abym w ogóle zaczynał rozmowę? Czy już podjąłeś decyzję?";
			link.l1 = "Znasz się na wchodzeniu do czyjejś głowy, mademoiselle. Naprawdę nie warto teraz się kłócić. Ale jeśli chcesz spróbować się usprawiedliwić... cóż, proszę bardzo. Ze względu na Longwaya, wysłucham cię.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_LongwayPrishelOdin7":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "„Ona może wszystko wyjaśnić, Wielmożny Panie Kapitanie... To nie jest to, co myślisz... Naprawdę nie...”";
			link.l1 = "W takim razie wyjaśnij to. Ale nie mnie."+sStr+"Spójrz w jej oczy. Spójrz na jej siniaki i rany. I powiedz jej, że nie było tak.";
			link.l1.go = "PZ_LongwayPrishelOdin8";
		break;
		
		case "PZ_LongwayPrishelOdin8":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Przepraszam w imieniu Xinga, Kapitanie...";
			link.l1 = "Patrząc na jej szyderczy uśmiech, robisz to na próżno. Ona nie zasługuje na twoje przeprosiny.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayPrishelOdin_ChangShinNext");
		break;
		
		case "PZ_LongwayPrishelOdin9":
			dialog.text = "Jesteś dla niego zbyt surowy, Monsieur de Maure. Choć pewnie jesteś przyzwyczajony do traktowania go w ten sposób - jak typowego żółtoskórego robotnika.";
			link.l1 = "„Próbujesz obrócić Longwaya przeciwko mnie? To nie zadziała. Zawsze traktowałem go z szacunkiem i on o tym wie. To wszystko, co się liczy. Zdaje sobie sprawę, że granie w gry to wszystko, co ci teraz zostało.”";
			link.l1.go = "PZ_LongwayPrishelOdin10";
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
		break;
		
		case "PZ_LongwayPrishelOdin10":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Co chcesz zrobić? Zabrać biednego Tu od jego rodziny? Kiedy w końcu ich odnalazł po dziesięciu latach?";
			link.l1 = "Krew nie zawsze tworzy rodzinę. Ale co proponujesz, żebyśmy zrobili? Pozwolić, żeby to, co zrobiłeś"+sStr+"ujść na sucho? I pozwolić Longwayowi czasami odwiedzać kobietę, która bez zastanowienia handluje innymi dziewczętami?";
			link.l1.go = "PZ_LongwayPrishelOdin11";
		break;
		
		case "PZ_LongwayPrishelOdin11":
			dialog.text = "„Cóż, na początek posłuchaj. W przeciwieństwie do niego, mogę opowiedzieć to, co właśnie mu powiedziałem, w doskonałym francuskim. Moją historię. Patrząc prosto w twoje oczy albo nawet w jej. I to wszystko bez akcentu, który zapewne już cię śmiertelnie męczy. W końcu, co mamy do stracenia?”";
			link.l1 = "I'm used to Longway's accent; it's part of who he is to me. I'll listen to you, but only for the sake of my friend. Go on.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_LongwayPrishelOdin12":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = " Czemuż by nie, Wielmożny Panie Kapitanie...?";
			link.l1 = "„Czy naprawdę musisz pytać? Była zamieszana w porwanie ”"+sStr+", czyż nie?";
			link.l1.go = "PZ_LongwayPrishelOdin13";
		break;
		
		case "PZ_LongwayPrishelOdin13":
			dialog.text = "Ja... szczerze przepraszam. To również moja wina, że nie mogłem ocalić mojej siostry dziesięć lat temu, uchronić jej przed tym wszystkim.";
			link.l1 = "„Nie powinieneś przepraszać za tych, którzy nie mają najmniejszego wyrzutu sumienia, Longway. Skończyłeś tutaj? Teraz moja kolej, by z nią porozmawiać.”";
			link.l1.go = "PZ_LongwayPrishelOdin14";
		break;
		
		case "PZ_LongwayPrishelOdin14":
			dialog.text = "Wielmożny Panie Kapitanie, czekaj! Chang Xing nie jest jak Levasseur. Nie całkiem. Opowie mi o swoim życiu przez te dziesięć lat. Pozwól, że i ja ci opowiem.";
			link.l1 = "W porządku, Longway. Słucham. Wiele zależy od tego, co mi powiesz.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayPrishelOdin_ChangShinNext");
		break;
		
		case "PZ_LongwayPrishelOdin15":
			dialog.text = "Jeśli to ty opowiadasz, wszyscy dostaniemy bólu głowy. Pozwól mi, Tu. Charles de Maure, jak mniemam?";
			link.l1 = "Zgadza się. A ty jesteś Belle Etoile, znana również jako Chang Xing. Odegrałaś rolę w porwaniu mojej miłości, razem z Thibautem i Martenem. I uśmiechasz się, gdy o tym wspominam. Miłe wspomnienia?";
			link.l1.go = "PZ_LongwayPrishelOdin16";
		break;
		
		case "PZ_LongwayPrishelOdin16":
			dialog.text = "To głupota zaprzeczać temu. Ale co z tego teraz? Zamierzasz mnie torturować na oczach mojego brata? A może nawet poprosisz go, by ci pomógł mnie torturować? Czy po prostu mnie zabijesz? Naprawdę byś mu to zrobił?";
			link.l1 = "Tak jak powiedziałem, pomimo wszystkiego, co chciałbym teraz zrobić, wciąż z tobą rozmawiam. Nie naciskaj. Powiedz mi, co mu wcześniej powiedziałeś. A potem zobaczymy, dokąd nas to zaprowadzi.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_Longway_91":
			if (!CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				dialog.text = "„Wciąż nie mogę uwierzyć, że Chang Xing mógł przekształcić się w... to.”";
				link.l1 = "Ludzie się zmieniają, Longway. Każdy może zostać złamany lub wypruty z ostatnich kropli dobroci i wiary.";
				link.l1.go = "PZ_Longway_ToGirl1";
			}
			else
			{
				dialog.text = "„Longway wciąż nie może uwierzyć, że moja siostra zmieniła się w... to. Dlaczego... dlaczego? Gdybym tylko był w domu tamtego dnia...”";
				link.l1 = "Nie dręcz się tym, co by było gdyby. Poza tym, nie siedziałeś bezczynnie przez te wszystkie lata - starałeś się cholernie mocno naprawić rzeczy.";
				link.l1.go = "PZ_Longway_ToShore1";
			}
		break;
		
		case "PZ_Longway_ToGirl1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Eh... Chyba tak to już jest, Wielmożny Panie Kapitanie.";
			link.l1 = "Wynośmy się stąd. Jeszcze musimy posprzątać bałagan, który zostawiła, i uratować "+sStr+"jak najszybciej.";
			link.l1.go = "PZ_Longway_ToGirl2";
		break;
		
		case "PZ_Longway_ToGirl2":
			dialog.text = "„Aye. Musimy się pospieszyć - to już zbyt długo się przeciąga przeze mnie.”";
			link.l1 = "To nie twoja wina, Longway. Pospieszmy się!";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LeaveEliteBrothel");
		break;
		
		case "PZ_Longway_ToShore1":
			dialog.text = "Tak. Dziękuję za wsparcie, Wielmożny Panie Kapitanie.";
			link.l1 = "Nie ma sprawy. Ona nie zasługiwała na twoje oddanie, tak czy owak - to nie ona cię szukała, nawet gdy mogła. Twoja gwiazda dawno już zgasła, a ona przestała być twoją rodziną dawno temu. Teraz my jesteśmy twoją rodziną, Longway.";
			link.l1.go = "PZ_Longway_ToShore2";
		break;
		
		case "PZ_Longway_ToShore2":
			dialog.text = "Aye... Tak właśnie jest. A ja byłem zbyt ślepy, by to dostrzec przez cały ten czas.";
			link.l1 = "Lepiej późno niż wcale. Teraz wracajmy do domu - nasz statek na nas czeka.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LeaveEliteBrothel");
		break;
		
		case "PZ_Mary_91":
			dialog.text = "„Tak, co nie? Nie masz pojęcia, jak bardzo tego pragnęłam.”";
			link.l1 = "Wydaje mi się, że tak. Jak się czujesz, Mary? Powód, dla którego chciałem uniknąć rozlewu krwi, to niepewność, czy będziesz w stanie trzymać swój miecz tak pewnie, jak zawsze - jeden z nich mógłby zyskać przewagę, podczas gdy ja byłbym zajęty innym.";
			link.l1.go = "PZ_Mary_92";
		break;
		
		case "PZ_Mary_92":
			dialog.text = "„Nie doceniasz mnie. Poza tym, gniew to piekielne lekarstwo. Nie miałam wątpliwości, że ruszysz mnie ratować - jak zawsze to robisz, tak, co nie? Wiesz, Charles... Nawet jeśli nazywasz mnie swoim Czerwonym Talizmanem, co jeśli ty jesteś moim? Zawsze dzieje się coś niesamowitego, gdy jesteśmy razem.”";
			link.l1 = "Jestem twoim talizmanem? No cóż, podoba mi się ten pomysł.";
			link.l1.go = "PZ_Mary_93";
		break;
		
		case "PZ_Mary_93":
			dialog.text = "„No proszę, już się uśmiechasz! Teraz wyjdźmy z tego obrzydliwego miejsca - pośpiesz się, raz-dwa, tak, co nie?”";
			link.l1 = "„Eh-heh, ta sytuacja mocno mnie uderzyła. Żałuję, że nie mogło się to skończyć inaczej.”";
			link.l1.go = "PZ_Mary_94";
		break;
		
		case "PZ_Mary_94":
			dialog.text = "Nie. Nie było jej ratunku, Charles. A ona pociągnęła Longwaya za sobą. Dokonał wyboru i nie zostawił nam wyboru. Pomyśl o wszystkich ludziach, którym dziś pomogliśmy.";
			link.l1 = "Po raz kolejny, nie mam nic, co mogłoby ci zaprzeczyć, Mary. I tym razem, nawet nie chcę. Chodź, mój Czerwony Talizmanie...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LeaveEliteBrothel");
		break;
		
		case "PZ_ElitaShluha_Final1":
			if (CheckAttribute(pchar, "questTemp.PZ_ChangShinMertva"))
			{
				dialog.text = "Co tam się stało, monsieur? Słyszeliśmy przekleństwa i krzyki. Ale nie śmieliśmy wzywać pomocy, dopóki się to nie skończyło.";
				link.l1 = "„I słusznie. Wasza gospodyni nie żyje. Jesteście wolne. Na waszym miejscu zabrałbym skarbiec przybytku, podzielił go i jak najszybciej uciekł z wyspy. Wiem, że jesteście honorowymi damami, a nie zwykłymi prostytutkami, więc czeka was przyszłość poza tym przeklętym miejscem.”";
				link.l1.go = "PZ_ElitaShluha_Final2";
			}
			else
			{
				dialog.text = "„Och, to ty, monsieur. Wiesz, kiedy gospodyni zejdzie na dół?”";
				link.l1 = "„Nieprędko. I na twoim miejscu odsunąłbym się od drzwi. I nigdy nie rozmawiaj z nią o tym wieczorze - niczego nie wyjawi, a ciekawskie koty tracą życie w jednej chwili. Wygląda na to, że twoja pani nie lubi, gdy ktoś węszy w jej sekretach.”";
				link.l1.go = "PZ_ElitaShluha_Final3";
			}
		break;
		
		case "PZ_ElitaShluha_Final2":
			dialog.text = "Zabiłeś ją?!";
			link.l1 = "Zrobiłem to. A jeśli się ociągniesz lub spróbujesz wezwać strażników, to będzie twój największy błąd. Nigdy nie była dla ciebie patronką - bez względu na to, ile jedwabiu i edukacji ci dała, byłaś tu więziona, zmuszana do oddawania się każdemu motłochowi, na którego wskazała. Życzę wam wszystkim powodzenia w wyjściu stąd. Żegnajcie, panie.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_ToTortugaStreets");
		break;
		
		case "PZ_ElitaShluha_Final3":
			dialog.text = "Czy ona naprawdę ma się dobrze? Czy możemy wejść? Czy musimy wezwać strażników?";
			link.l1 = "Ona nigdy nie będzie w porządku. Możesz spróbować zapytać ją sam... na własne ryzyko. Ona wciąż rozmawia z bratem. I nie sądzę, żeby byli zadowoleni z przerwania.";
			link.l1.go = "PZ_ElitaShluha_Final4";
		break;
		
		case "PZ_ElitaShluha_Final4":
			dialog.text = "Rozumiem... Cóż, odwiedź nas znowu kiedyś, monsieur.";
			link.l1 = "Nigdy. Żegnajcie, panie.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_ToTortugaStreets");
		break;
		
		case "PZ_TortugaSoldier1":
			dialog.text = "Stój! Zgłoszono krzyki i walkę dochodzące z miejsca Mademoiselle Etoile. Straż uważa, że masz z tym coś wspólnego. Oddaj broń i chodź z nami, monsieur.";
			if (!CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				link.l1 = "Prawda, ale to nie my zaczęliśmy tę bójkę, tylko ją zakończyliśmy. Najemnicy zbuntowali się z powodu opóźnionych płatności i zaatakowali Madame Etoile, by ją okraść. Zaufaj najemnikom, co nie? Wygraliśmy dzień, ale niestety, ona nie przeżyła.";
				link.l1.go = "PZ_TortugaSoldier2";
			}
			else
			{
				link.l1 = "Straciłem dziś miłość mojego życia, więc pozwól mi przejść, oficerze.";
				link.l1.go = "PZ_TortugaSoldierGirlDied1";
			}
		break;
		
		case "PZ_TortugaSoldier2":
			dialog.text = "„Zdajecie sobie sprawę, że nie możemy po prostu uwierzyć wam na słowo, prawda? Musimy was zatrzymać. Będziecie potrzebować świadków wśród pracownic. Zobaczymy, co one mają do powiedzenia.”";
			link.l1 = "Mój ukochany jest ciężko ranny. Ja też jestem śmiertelnie zmęczona. Czy nie możesz nas po prostu puścić, proszę?";
			link.l1.go = "PZ_TortugaSoldier3";
		break;
		
		case "PZ_TortugaSoldier3":
			dialog.text = "Postaramy się to rozwiązać jak najszybciej. Teraz podążaj za nami.";
			link.l1 = "Idź do diabła...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaSoldiersFight");
		break;
		
		case "PZ_TortugaSoldierGirlDied1":
			dialog.text = "Wyrazy współczucia, monsieur. I jeszcze nie jestem oficerem, ale... w każdym razie, nieważne. Czy mógłbyś pójść z nami i opowiedzieć, co się tam stało?";
			link.l1 = "Opowiem ci. Burdel tracił pieniądze, nie było już gotówki, by zapłacić najemnikom, którzy go pilnowali. Zdecydowali się zabrać wszystko, co zostało, akurat gdy tam byłem. Madame Etoile i ja odparliśmy ich, ale ona zmarła z powodu ran. Teraz, pozwól mi wreszcie przejść.";
			link.l1.go = "PZ_TortugaSoldierGirlDied2";
		break;
		
		case "PZ_TortugaSoldierGirlDied2":
			dialog.text = "Chciałbym, ale jest mnóstwo papierkowej roboty do załatwienia. I muszę przeprowadzić rozmowy z paniami, które tam pracują. Obawiam się, że będziesz musiał zostać w mieście przynajmniej jeden dzień, nawet jeśli mówisz prawdę, monsieur.";
			link.l1 = "Idź do diabła...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaSoldiersFight");
		break;
		
		case "PZ_Longway_101":
			dialog.text = "Longway ma coś dla ciebie, Wielmożny Panie Kapitanie.";
			link.l1 = "Jakie to piękne i kapryśne. Nigdy czegoś takiego nie widziałem. Co to jest?";
			link.l1.go = "PZ_Longway_102";
			GiveItem2Character(PChar, "talisman14");
			PlaySound("interface\important_item.wav");
		break;
		
		case "PZ_Longway_102":
			dialog.text = "To amulet Kapitana mojej Ojczyzny. A ponieważ Longway nie jest już Kapitanem, oddaję go tobie.";
			link.l1 = "Dziękuję, Longway. Śmierć van der Vinka to twoja zemsta na wszystkich, których chciałeś. Cieszę się, że wszystko tak się ułożyło.";
			link.l1.go = "PZ_Longway_103";
		break;
		
		case "PZ_Longway_103":
			dialog.text = "Gdybym tylko mógł przekonać Xinga, by znów był dobrym człowiekiem...";
			link.l1 = "Nie chciałaby już nikogo słuchać, nawet swojego brata. Zrobiłeś, co mogłeś. Wszyscy zrobiliśmy.";
			link.l1.go = "PZ_Longway_104";
		break;
		
		case "PZ_Longway_104":
			dialog.text = "„Aye... Dziękuję bardzo, Wielmożny Panie Kapitanie. Longway być wolny, i mieć dom i przyjaciół znowu.”";
			link.l1 = "Proszę bardzo, mój przyjacielu. A teraz, może pójdziesz ze mną odwiedzić mojego brata. Och, cóż za ironia!";
			link.l1.go = "PZ_Longway_105";
		break;
		
		case "PZ_Longway_105":
			DialogExit();
			DeleteAttribute(npchar, "CompanionDisable");//теперь можем и в компаньоны
			chrDisableReloadToLocation = false;
			Return_LongwayOfficer();
		break;
		
		case "PZ_PuansieDialogWithLevasser_1":
			dialog.text = "Oto jesteśmy znowu, François. Widzę, że życie dało ci w kość, hehe.";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_1_1";
			LAi_SetHuberType(npchar);
		break;
		case "PZ_PuansieDialogWithLevasser_1_1":
			StartInstantDialog("Levasser", "PZ_PuansieDialogWithLevasser_2", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_2":
			dialog.text = "Poincy, ty chciwy draniu... Prawie się zadławiłeś złotem, którym twoje kufry są pełne, a wciąż ci mało?";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_2_1";
			CharacterTurnByChr(npchar, CharacterFromID("Puancie"));
		break;
		case "PZ_PuansieDialogWithLevasser_2_1":
			StartInstantDialogNoType("Puancie", "PZ_PuansieDialogWithLevasser_3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_3":
			//LAi_SetActorType(npchar);
			//LAi_ActorSetHuberMode(npchar);
			dialog.text = "Podzielę się z tobą, François. Będziesz miał dość, uwierz mi.";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_3_1";
			//LAi_tmpl_SetDialog(npchar, pchar, -1.0);
		break;
		case "PZ_PuansieDialogWithLevasser_3_1":
			StartInstantDialog("Levasser", "PZ_PuansieDialogWithLevasser_4", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_4":
			dialog.text = "Co... co masz na myśli?";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_4_1";
			CharacterTurnByChr(npchar, CharacterFromID("Puancie"));
		break;
		case "PZ_PuansieDialogWithLevasser_4_1":
			StartInstantDialogNoType("Puancie", "PZ_PuansieDialogWithLevasser_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_5":
			dialog.text = "";
			link.l1 = "Gubernatorze generalny, czy zamierzasz...";
			link.l1.go = "PZ_PuansieDialogWithLevasser_6";
		break;
		
		case "PZ_PuansieDialogWithLevasser_6":
			dialog.text = "Charles, mój przyjacielu, wykonałeś swoją robotę i zrobiłeś to znakomicie! Co stanie się z tym człowiekiem, nie powinno cię obchodzić... Jednakże, będzie dla ciebie przydatne, Kapitanie, na wypadek gdyby twoja bystra głowa kiedyś wpadła na jakieś głupie pomysły. Naszego wspólnego przyjaciela czeka ciężka niestrawność, że tak powiem. Słyszałem, że złoto nie jest dobre dla żołądka... Mam nadzieję, że nie muszę tłumaczyć dalej.";
			link.l1 = "Nie, Gubernatorze-Generalny.";
			link.l1.go = "PZ_PuansieDialogWithLevasser_7";
		break;
		
		case "PZ_PuansieDialogWithLevasser_7":
			dialog.text = "W przeciwieństwie do Monsieur François, masz przed sobą wspaniałą przyszłość, Charles. Chłopcy, zaciągnijcie tego wieprza do więzienia!";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_7_1";
		break;
		case "PZ_PuansieDialogWithLevasser_7_1":
			StartInstantDialog("Levasser", "PZ_PuansieDialogWithLevasser_8", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_8":
			dialog.text = "Ręce precz, wy sukinsyny! Jesteś zadowolony, de Maure?! Pierdol się! Wszyscy spłoniemy w piekle, na tej samej patelni!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LevasserVGostyahUPuansie3");
			CharacterTurnByChr(npchar, CharacterFromID("Puancie"));
			sld = characterFromID("PZ_SoldFra_1");
			CharacterTurnByChr(sld, CharacterFromID("Levasser"));
			sld = characterFromID("PZ_SoldFra_2");
			CharacterTurnByChr(sld, CharacterFromID("Levasser"));
		break;
		
		case "PZ_Baker_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Kasper";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Sharp";
			dialog.text = "„Cóż, panie. Zbadałem pannę ”"+sStr+"...";
			link.l1 = "Jak źle to wygląda, Raymond?";
			link.l1.go = "PZ_Baker_2";
		break;
		
		case "PZ_Baker_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					dialog.text = "Nie ma się czym martwić, Kapitanie. Mary została ciężko ranna, oczywiście, ale ogólnie wszystko będzie w porządku. Powinna pozostać w łóżku przez kilka dni, a spodziewam się, że wróci do działania za dwa tygodnie.";
					link.l1 = "Rozumiem. Dzięki, Raymond. Wolny.";
					link.l1.go = "PZ_Baker_4";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "Mary porządnie oberwała, Kapitanie. Siniaki, skaleczenia... i oczywiście cały ten szok - choć stara się tego nie pokazywać.";
					link.l1 = "Zachowuje twardą twarz, jak zawsze. Ale myślę, że zdaje sobie sprawę, że lepiej jej teraz odpoczywać w łóżku. Jak długo jednak?";
					link.l1.go = "PZ_Baker_3";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "Nawet zawodowy żołnierz miałby trudności, by przeżyć to, przez co ona przeszła, Kapitanie. Zwichnięcia, nadwyrężenia, siniaki - mamy szczęście, że te łotry nie połamały jej kości. Jednak jej ścięgna są uszkodzone, więc nie będzie mogła posługiwać się bronią przynajmniej przez miesiąc.";
					link.l1 = "Do diabła z ostrzem. Kiedy ona stanie na nogi?";
					link.l1.go = "PZ_Baker_3";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					dialog.text = "Nie martw się, Kapitanie. Hellen jest ranna, ale nie ciężko. Na razie będzie musiała pozostać w łóżku, ale myślę, że w ciągu kilku tygodni całkowicie wyzdrowieje.";
					link.l1 = "Rozumiem. Dzięki, Raymond. Możesz odejść.";
					link.l1.go = "PZ_Baker_4";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "Została nieźle poturbowana, kapitanie. A obrażenia fizyczne to tylko część diagnozy... Pobyt w tym strasznym miejscu przypomniał jej koszmar, jaki przeżyła na Arbutusie.";
					link.l1 = "Oczywiście... cholera! Kiedy ona znowu stanie na nogi?";
					link.l1.go = "PZ_Baker_3";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "Helen chodziła po ostrzu noża, Kapitanie. Jestem zaskoczony, że przeżyła po tym wszystkim, co przeszła. Żadnych wewnętrznych rozcięć ani złamań, ale mnóstwo skręceń i nadwyrężeń.";
					link.l1 = "Biedactwo. Jak długo potrwa jej powrót do zdrowia?";
					link.l1.go = "PZ_Baker_3";
				}
			}
		break;
		
		case "PZ_Baker_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "Przynajmniej tydzień, sir. Jeśli będzie stosować się do moich zaleceń, powinna wrócić do akcji za około miesiąc.";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "Nie wcześniej niż za dwa tygodnie, sir. Potem pozwolę jej na krótkie spacery po pokładzie. Pełne wyzdrowienie potrwa co najmniej dwa miesiące.";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "Nie przeszkadzaj jej przez co najmniej tydzień, powiem ci to, panie. Pełne wyzdrowienie potrwa około miesiąca.";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "She should stay in bed for a fortnight; after that, she may be able to walk around the deck. But don't expect to see her back in action for at least two months.";
				}
			}
			link.l1 = "Rozumiem. Dzięki, Raymond. Wolne.";
			link.l1.go = "PZ_Baker_4";
		break;
		
		case "PZ_Baker_4":
			DialogExit();
			sld = CharacterFromID("Baker");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "PZ_RazgovorSVrachom_4", -1);
		break;
		
		case "PZ_DevushkaVstalaSKrovati_Dialog1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "To trudniejsze, niż myślałam, stanąć na własnych nogach po tak długim leżeniu, tak, co nie?";
				link.l1 = "Może nie powinnaś tak nagle przerywać odpoczynku w łóżku, kochanie.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Oh-h, moja głowa...";
				link.l1 = "Helen! Czyżbyś wstała za wcześnie? Ledwie się trzymasz na nogach!";
			}
			link.l1.go = "PZ_DevushkaVstalaSKrovati_Dialog2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_DevushkaVstalaSKrovati_Dialog2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Wolałbym spalić to cholernie łóżko, niż znowu w nim leżeć - przynajmniej dopóki nie przejdę się od dziobu do rufy i z powrotem!";
				link.l1 = "To przyjemne, wygodne łóżko. I to też nie jest zła łajba. Więc nie zamierzam cię powstrzymywać. Ale będę tam, aby upewnić się, że nie zrobisz nic głupiego.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Jestem w porządku, Kapitanie, chociaż nie całkiem. Jeszcze nie jestem gotowa do machania szablą, ale nienawidzę tego łóżka z całej duszy.";
				link.l1 = "„Cóż, krótki spacer po pokładzie pewnie ci nie zaszkodzi. Ale nawet nie myśl o zbliżaniu się do kabli!”";
			}
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DevushkaStoitVosstanovlenie");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Sex1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Charles, czy nie uważasz, że całkowicie o mnie zapomniałeś? Przypomnij mi, kiedy ostatnio razem spaliśmy, tak, co nie!";
				link.l1 = "„Wcześniej... Nie rozmawiajmy o tym, dobrze, Mary?”";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Mój Kapitanie, czy przestałam cię interesować jako kobieta?";
				link.l1 = "To niespodziewane, Helen. Zwykle to ja poruszam ten temat... ale nie byłem pewien, czy jesteś gotowa po...";
			}
			link.l1.go = "PZ_DevushkaSnovaOfficer_Sex2";
			DelLandQuestMark(npchar);
			pchar.questTemp.PZ_DevushkaSnovaOfficer = true;
			DeleteQuestCondition("PZ_DevushkaSnovaOfficer2");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Sex2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "W takim razie przynajmniej porozmawiajmy o mnie, tak, co nie? Czy stałam się dla ciebie niemiła po tym, jak ci dwaj dranie mnie pobili?";
				link.l1 = "To najgłupsza rzecz, jaką kiedykolwiek słyszałem. Po prostu nie chciałem ci przeszkadzać, dopóki nie będziesz gotowy. A skoro już jesteś...";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Sex3";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "„W porządku, Charles, naprawdę. Po prostu staram się o tym nie myśleć. A poza tym, uratowałeś mnie przed najgorszym. Więc przestańmy o tym rozmawiać i po prostu... nadrobić zaległości.”";
				link.l1 = "To cholernie dobry pomysł, Helen.";
				link.l1.go = "exit";
				pchar.quest.sex_partner = Npchar.id;
				AddDialogExitQuest("cabin_sex_go");
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Sex3":
				dialog.text = "„Charles, nie chcę tego, żądam tego, tak, co nie!”";
				link.l1 = "Nie ośmieliłbym się ci odmówić...";
				link.l1.go = "exit";
				pchar.quest.sex_partner = Npchar.id;
				AddDialogExitQuest("cabin_sex_go");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Charles, musimy porozmawiać, tak, co nie?";
				link.l1 = "„Coś się stało, Mary? Wyglądasz na dość niespokojną, a to zwykle nie wróży dobrze.”";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Mój kapitanie, muszę coś ci powiedzieć.";
				link.l1 = "Czyżby tak, Helen? Słucham.";
			}
			link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "„Właśnie tak! Czyż to nie dobrze, że jestem gotów wrócić do swoich obowiązków jako oficer?”";
				link.l1 = "Więc to tyle. Cóż, jeśli czujesz się wystarczająco silny, to nie tylko dobrze, to cudownie.";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog3";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Jestem zmęczona tym, że załoga gapi się na mnie, jakbym była jakąś słabą staruszką. Chcę wrócić za ster i rozciągnąć ramiona, ćwicząc z ostrzem...";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					link.l1 = "Jeśli masz na to ochotę, nie będę się sprzeciwiać, kochanie. Przygotuję twoje wyposażenie. I chętnie pozwolę ci przejąć ster. Ale bądź ostrożny w walce, tak, co nie?";
					link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog2_1";
				}
				else
				{
					link.l1 = "Brakowało cię na mostku, Helen. Co do ostrza, myślę, że nadszedł czas, byś je odzyskała.";
					link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog3";
				}
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog2_1":
			dialog.text = "Oczywiście, Mój Kapitanie, cokolwiek powiesz.";
			link.l1 = "Dobrze.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Cudownie, tak, co nie? Nie mogę się doczekać, by poćwiczyć z ostrzem...";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					link.l1 = "Cieszę się, że to słyszę, Mary. Ale jeszcze nie rzucaj się w wir wydarzeń... Ale komu ja to mówię?";
					link.l1.go = "exit";
					AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
				}
				else
				{
					link.l1 = "Domyślam się, że ucieszy cię widok tego pałasza z powrotem w pochwie...";
					link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog4";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Ja... Ja nie wiem, co powiedzieć, Charles. Dopiero teraz zrozumiałam, jak wiele znaczy dla mnie ta szabla...";
				link.l1 = "Wiedziałam o tym już dawno temu, dlatego czekało na ciebie całe i zdrowe.";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog4";
				notification("Gave Cutlass of Blaze", "None");
				PlaySound("interface\important_item.wav");
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Mój narwal, tak, co nie!!! Charles, uratowałeś go! Nie tylko jestem szczęśliwa, jestem zachwycona! Dziękuję, dziękuję! Bałam się, że został na statku Martina...";
				link.l1 = "Ten ostrze należy do twojej ręki, mój Czerwony Talizmanie. Wierzę, że znów go nie zgubisz... No cóż, nie będę przeszkadzał w waszym spotkaniu, ha-ha!";
				notification("Gave Narwhal", "None");
				PlaySound("interface\important_item.wav");
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Dziękuję, Charles. Wiesz, pewnie dlatego cię kocham...";
				link.l1 = "Za sprowadzanie zagubionych rzeczy? Ha ha ha ha...";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog5";
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog5":
			dialog.text = "„Śmiejesz się, ale mówię poważnie.”";
			link.l1 = "    Wiem, Helen. Też cię kocham, choć wciąż nie jestem pewien dlaczego.";
			link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog6";
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog6":
			dialog.text = "Może dlatego, że jeszcze nie użyłem na tobie tej szabli.";
			link.l1 = "Uratować się przed tym, idąc do łodzi. Poczekam na ciebie tam, Helen.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
		break;
	}
} 
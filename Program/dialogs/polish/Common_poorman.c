#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

	switch(Dialog.CurrentNode)
	{
		case "First time":
			// --> калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.SeekAmulet") && hrand(1) == 0 && sti(Pchar.money) >= 2000) 
			{
				dialog.text = "Spójrz, panie, może chciałbyś kupić jedną zabawną rzecz? To niedrogo, tylko kilka tysięcy peso...";
				link.l1 = "Hmm. Pewnie ukradłeś to 'małe coś', a teraz próbujesz się tego pozbyć?";
				link.l1.go = "caleuche";
				break;
			}
			// <-- калеуче
			if (npchar.quest.meeting == "0")
			{
				dialog.text = LinkRandPhrase("Witaj. Mam na imię "+GetFullName(npchar)+". Nie sądzę, żebyś był zadowolony z naszego spotkania, ale, być może, przynajmniej zapamiętasz moje imię...","Powitanie, "+GetAddress_Form(NPChar)+". Nazywam się "+GetFullName(npchar)+".","Mam na imię "+GetFullName(npchar)+", "+GetAddress_Form(NPChar)+". Miło cię poznać.");
				link.l1 = RandPhraseSimple("Pozdrowienia.","Witaj.");
				link.l1.go = "First time";
				// карибские нравы
				if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy_drink" && pchar.location == "portobello_town")
				{
					link.l2 = "Hej, słuchaj, chciałbyś zarobić parę tysięcy pesos zamiast tych żałosnych jałmużen?";
					link.l2.go = "trial";
				}
				// --> Тайна Бетси Прайс
				if (CheckAttribute(pchar, "questTemp.TBP_BuyKulon3") && pchar.location == "Villemstad_town")
				{
					link.l2 = "Ten wisiorek z kameą... Gdzie go znalazłeś?";
					link.l2.go = "TBP_Kulon_1";
				}
				// <-- Тайна Бетси Прайс
				npchar.quest.meeting = "1";
			}			
			else
			{
				dialog.text = NPCStringReactionRepeat("Patrz jak nisko upadłem...","Życie na jałmużnie nie jest łatwe...","Dałbym wszystko, żeby wydostać się z tej nędzy!","Ty znowu?..","block",1,npchar,Dialog.CurrentNode);

				link.l1 = HeroStringReactionRepeat("Rozumiem. Cóż, nic wielkiego.","Oczywiście. Wiesz, największy człowiek w historii był najbiedniejszy.","W takim razie powinieneś zacząć coś robić, a nie siedzieć tu cały dzień.","Aha. Już cię denerwuję?",npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "pester", npchar, Dialog.CurrentNode);
				link.l2 = RandPhraseSimple("Czego potrzebujesz?","Co chcesz?");
				link.l2.go = "Whants";
				// карибские нравы
				if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy_drink" && pchar.location == "portobello_town")
				{
					DelLandQuestMark(npchar);
					link.l2 = "Hej, posłuchaj, czy chciałbyś zarobić kilka tysięcy peso zamiast tych żałosnych jałmużn?";
					link.l2.go = "trial";
				}
				// --> Тайна Бетси Прайс
				if (CheckAttribute(pchar, "questTemp.TBP_BuyKulon3") && pchar.location == "Villemstad_town")
				{
					link.l2 = "Ten wisiorek z kameą... Gdzie go znalazłeś?";
					link.l2.go = "TBP_Kulon_1";
				}
				// <-- Тайна Бетси Прайс
				link.l3 = LinkRandPhrase("Czy możesz mi coś ciekawego opowiedzieć?","Co nowego w mieście?","Och, chciałbym usłyszeć najnowsze plotki...");
				link.l3.go = "rumours_poor";
			}
			NextDiag.TempNode = "First time";
		break;
		case "pester":
			dialog.text = RandPhraseSimple("Nie, dlaczego, już zdenerwowany? Jak widzisz, nie jestem szczególnie zajęty...","Po prostu mnie to męczy. Chociaż biedny, jestem wciąż mężczyzną.");
			link.l1 = "Heh, widzę...";
			link.l1.go = "exit";
		break;
		//выходы
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//милостыня
		case "Whants":
			if (!CheckAttribute(npchar, "wants_date") || GetNpcQuestPastDayParam(npchar, "wants_date") >= 1 || bBettaTestMode)
    		{
				dialog.text = PCharRepPhrase("Hmm, "+GetAddress_Form(NPChar)+", ludzie mówią o tobie wiele brzydkich rzeczy. Ale ja wciąż wierzę w ludzi - nawet w takich jak ty. Proszę, daj mi jałmużnę na chleb i wodę, zmiłuj się nade mną.","Proszę cię, "+GetAddress_Form(NPChar)+"! Proszę, nie odwracaj się od biednego człowieka, daj jałmużnę na posiłek...");
				link.l1 = RandPhraseSimple("Nie dam ci niczego.","Dasz radę bez pieniędzy.");
				link.l1.go = "exit";
				Link.l2 = "Dobrze, i ile dokładnie potrzebujesz?";
				Link.l2.go = "Whants_1";
			}
			else
			{
				dialog.text = PCharRepPhrase("Od ciebie? Nic.","Nie potrzebuję niczego, "+GetAddress_Form(NPChar)+", dzięki.");
				link.l1 = RandPhraseSimple("Hmm, w porządku.","Wygląda na to, że twoje życie wcale nie jest takie złe, kumplu.");
				link.l1.go = "exit";
			}
		break;
		case "Whants_1":
			dialog.text = "Nie odrzuciłbym nawet drobnej miedziaki,"+GetAddress_Form(NPChar)+". Tyle, ile twój portfel i twoja łaska mogą dać...";
			Link.l1.edit = 2;			
			link.l1 = "";
			link.l1.go = "Whants_2";
		break;
		case "Whants_2":
			SaveCurrentNpcQuestDateParam(npchar, "wants_date");
			int iTemp = sti(dialogEditStrings[2]);
			if (iTemp <= 0 || sti(pchar.money) < iTemp)
			{
				dialog.text = "Drwienie z słabych i znużonych to grzech...";
				link.l1 = "Ha-ha-ha! Myślałeś chociaż na moment, że dam ci pieniądze, ty szalony żebraku?!";
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", -2);
				break;
			}
			if (iTemp > 0 && iTemp <= 100)
			{
				dialog.text = "Dziękuję Ci za "+FindRussianMoneyString(iTemp)+", "+GetAddress_Form(NPChar)+". Teraz mogę kupić za te pieniądze chleb...";
				link.l1 = "Tutaj, włóczęgo - idź się trochę umocnić.";
				link.l1.go = "exit";
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
			if (iTemp > 100 && iTemp <= 500)
			{
				dialog.text = "Dziękuję, "+GetAddress_Form(NPChar)+". Teraz mogę żyć tydzień za te pieniądze!";
				link.l1 = "Było miło pomóc.";
				link.l1.go = "exit";
				OfficersReaction("good");
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
			if (iTemp > 500 && iTemp <= 1000)
			{
				dialog.text = "Dziękuję, "+GetAddress_Form(NPChar)+". Opowiem wszystkim o twojej dobroci!";
				link.l1 = "To naprawdę nie jest konieczne.";
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", iTemp/2000.0+0.5);
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
			if (iTemp > 1000 && iTemp <= 5000)
			{
				dialog.text = "Dziękuję Ci, szanowny "+GetSexPhrase("panie","pani")+" "+GetAddress_Form(NPChar)+". Niech Pan Bóg cię strzeże...";
				link.l1 = "Tak, jego ochrona na pewno by nie zaszkodziła!";
				link.l1.go = "exit";
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), iTemp/10000.0+0.5);
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
			if (iTemp > 5000 && iTemp <= 10000)
			{
				dialog.text = "Dziękuję, "+GetSexPhrase("najszanowniejszy panie","najszanowniejsza pani")+" "+GetAddress_Form(NPChar)+". Życzę ci wszystkiego najlepszego!";
				link.l1 = "Dziękuję, kumplu.";
				link.l1.go = "exit";
				AddCharacterExpToSkill(pchar, "Leadership", iTemp/5000.0);
				AddCharacterExpToSkill(pchar, "Fortune", iTemp/5000.0);
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
                 if (iTemp > 10000 && iTemp < 25000)
			{
				dialog.text = "Słuchaj, "+GetAddress_Form(NPChar)+", czy jesteś szalony, czy co? Dajesz mi "+FindRussianMoneyString(iTemp)+"! Nie mogę wziąć takich pieniędzy, na pewno jest jakiś haczyk... Zostaw mnie w spokoju!";
				link.l1 = "Cóż, jak sobie życzysz...";
				link.l1.go = "exit";
			}
                 if (iTemp == 25000)
			{
				dialog.text = "Dwadzieścia pięć tysięcy przyjętych ... Te pieniądze wystarczą na cały rok dla mnie i Lelya!";
				link.l1 = "Przeżyj najpierw ten rok...";
				link.l1.go = "exit";
			}
			if (iTemp > 25000)
			{
				dialog.text = "Słuchaj, "+GetAddress_Form(NPChar)+", czy ty jesteś szalony czy co? Dajesz mi "+FindRussianMoneyString(iTemp)+"! Nie mogę przyjąć takich pieniędzy, na pewno jest jakiś haczyk... Zostaw mnie w spokoju!";
				link.l1 = "No cóż, jak sobie życzysz...";
				link.l1.go = "exit";
			}
		break;
		
		case "trial":
			DelLandQuestMark(npchar);
			dialog.text = "Głupie pytanie, senorze! Oczywiście, że bym chciał! Ale... co będę musiał zrobić? Przecież nie dasz mi tych pieniędzy tylko za mój piękny uśmiech.";
			link.l1 = "Oczywiście, że nie. Słuchaj teraz. Działam w imieniu samego gubernatora. Jego Wysokość podejrzewa, że ktoś na stoczni celowo sabotuje wodowanie 'Alacantara', jego galeonu. A jego podejrzenia tylko się nasiliły, po tym jak niedawno złapano francuskiego szpiega...";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "";
			link.l1 = "Jego Wysokość już słyszał wymówki stoczniowca, ale nie jest pewien, czy mówił prawdę. Musimy dowiedzieć się, kto sabotuje prace i dlaczego. Udaj się do portu, rozejrzyj się i zapytaj pracowników, dlaczego do diabła 'Alacantara' nadal nie jest gotowa do żeglugi...";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			dialog.text = "";
			link.l1 = "Nikt cię nie podejrzewa, nawet możesz zdobyć stos tytoniu. Co do mnie, nikt mi nic nie powie. Wszyscy będą wiedzieć, dla kogo pracuję. Jeśli uda ci się dowiedzieć czegoś wartego, otrzymasz trzy tysiące pesos. Wystarczy, żeby porzucić swoją 'pracę' przynajmniej na miesiąc.";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			dialog.text = "Trzy tysiące pesos? Ale, szanowny panie...";
			link.l1 = "Czy targujesz się ze mną, czy co? Ach, a jeśli dowiesz się, kto stoi za tym całym zwlekanie, dostaniesz kolejne dwa tysiące. Umowa?";
			link.l1.go = "trial_4";
		break;
		
		case "trial_4":
			dialog.text = "Dobrze, senorze. Nie powinno być zbyt trudno - wielu moich starych kumpli pracuje obecnie na dokach. Hej, byłem marynarzem dawno temu, też. Jak, dziesięć lat temu...";
			link.l1 = "Opowiesz mi swoją historię życia później. Spotkajmy się na molo po jedenastej wieczorem. Teraz idź.";
			link.l1.go = "trial_5";
		break;
		
		case "trial_5":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload5_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.Trial = "spy_poorman";
			pchar.quest.trial_spy_poorman.win_condition.l1 = "Timer";
			pchar.quest.trial_spy_poorman.win_condition.l1.date.hour  = 22.00;
			pchar.quest.trial_spy_poorman.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.trial_spy_poorman.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.trial_spy_poorman.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.trial_spy_poorman.function = "Trial_SetPoormanInPort";
			pchar.quest.Trial_ReturnPoormanNorm.win_condition.l1 = "Timer";
			pchar.quest.Trial_ReturnPoormanNorm.win_condition.l1.date.hour  = 6.00;
			pchar.quest.Trial_ReturnPoormanNorm.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Trial_ReturnPoormanNorm.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Trial_ReturnPoormanNorm.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Trial_ReturnPoormanNorm.win_condition = "Trial_ReturnPoormanNorm";
			//SetTimerCondition("Trial_ReturnPoormanNorm", 0, 0, 1, false);
			AddQuestRecord("Trial", "15");
		break;
		
		case "trial_6":
			dialog.text = "Dobry wieczór, señor...";
			link.l1 = "No więc? Dowiedziałeś się czegoś?";
			link.l1.go = "trial_7";
			DelLandQuestMark(npchar);
		break;
		
		case "trial_7":
			dialog.text = "Zrobiłem, señor, Zrobiłem. Nie jestem pewien, jak to wszystko zgadza się z tym, co mi powiedziałeś... Czy przyniosłeś pieniądze? Pięć tysięcy pesos.";
			if (sti(pchar.money) >= 5000)
			{
				link.l1 = "Nie martw się. Oto twoje pieniądze. Teraz wykrztuś to.";
				link.l1.go = "trial_8";
			}
			else
			{
				link.l1 = "Najpierw informacje, a potem pieniądze. No dalej, nie marnuj mojego czasu!";
				link.l1.go = "trial_fail";
			}
		break;
		
		case "trial_fail":
			dialog.text = "Próbujesz mnie oszukać, senorze! Jeśli nie zamierzasz płacić - idź i zapytaj kogoś innego sam. I nawet nie myśl o sięgnięciu po swój miecz, bo wezwę straże!";
			link.l1 = "...";
			link.l1.go = "trial_fail_1";
		break;
		
		case "trial_fail_1":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.Trial = "spy_fail";
			AddQuestRecord("Trial", "16");
			sld = characterFromId("Florian");
			sld.DeckDialogNode = "florian_failspy_5";
		break;
		
		case "trial_8":
			AddMoneyToCharacter(pchar, -5000);
			dialog.text = "Więc to wygląda tak: 'Alcantara' była gotowa do żeglugi od dawna, ale nie została załadowana celowo, i to na rozkaz samego gubernatora. Przynajmniej tak mi powiedziano. A cieśle teraz wykonują wszelkiego rodzaju drobne prace, które nie wpływają na wypłynięcie statku.\nWszyscy czekają na przybycie jakiegoś barku z Cartageny. Chodzi o to, że 'Alcantara' ma, zdaniem jej kapitana, zbyt mały zapas prochu strzelniczego. Więc statek stoi tu i czeka całe dni, aż 'Puebla' przyniesie proch strzelniczy.\nAle wszyscy myślą, że to całe oczekiwanie to strata czasu, więc jeśli 'Puebla' nie przybędzie w ciągu trzech dni, 'Alcantara' podniesie kotwicę bez prochu...";
			link.l1 = "Czy tak? A kto ci to powiedział? Imię?";
			link.l1.go = "trial_9";
		break;
		
		case "trial_9":
			dialog.text = "Jeden z marynarzy z 'Alacantara' - Felipe Dabinho... Ale to wcale nie jest żadna tajemnica, a Jego Wysokość gubernator sam kazał...";
			link.l1 = "Rozumiem. To, czego się spodziewałem. Francuscy szpiedzy są w mieście, ale ci idioci plotkują jak handlarki, nie do wiary! Każdy przybysz może dowiedzieć się, co chce o planach Jego Miłosierdzia. Och, ten Felipe Dabinho jest teraz w poważnych tarapatach! I bosman 'Alacantary' także! To jego wina, że jego załoga nie wie nic o dyscyplinie!";
			link.l1.go = "trial_10";
			QuestPointerToLoc("PortoBello_Town", "reload", "gate_back");
			QuestPointerToLoc("PortoBello_ExitTown", "reload", "reload1_back");
			QuestPointerToLoc("PortoBello_Jungle_01", "reload", "reload2_back");
			QuestPointerToLoc("PortoBello_Jungle_02", "reload", "reload3_back");
			QuestPointerToLoc("shore47", "reload", "boat");
		break;
		
		case "trial_10":
			dialog.text = "Oh... Więc wiedziałeś to od początku? Ale dlaczego... To nie moja wina! Ty mi kazałeś to zrobić!";
			link.l1 = "To nie była twoja wina, nie powinieneś się tym przejmować, nikt cię nie ukarze. Teraz wiemy, że załoga 'Alacantara' może wygadać jakiekolwiek informacje wrogu - nawet te, które powinny pozostać tajemnicą. Dobrze, możesz iść teraz. Dzięki za twoją pomoc. Idź wydaj swoje pieniądze.";
			link.l1.go = "trial_11";
			// belamour legendary edition -->
			link.l2 = "Do widzenia. (Zabij go)";
			link.l2.go = "trial_11a";
		break;
		
		case "trial_11a":
			DialogExit();
			AddMoneyToCharacter(npchar, 5000);
			npchar.SaveItemsForDead  = true; 
			LAi_SetActorType(pchar);
			// если не надет пистоль или мушкет, то выдадим строевой 
			if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE) || !CheckAttribute(pchar,"equip."+MUSKET_ITEM_TYPE))
			{
				GiveItem2Character(pchar, "pistol1");
				EquipCharacterbyItem(pchar, "pistol1");
			}
			LAi_ActorAnimation(pchar, "Shot", "RIP_Bomzh", 1.0); 
		break;
		
		case "trial_11":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddCharacterExpToSkill(pchar, "Sneak", 50);
			// <-- legendary edition
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.Trial = "spy_win";
			AddQuestRecord("Trial", "17");
			sld = characterFromId("Florian");
			sld.DeckDialogNode = "florian_12";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		// --> калеуче
		case "Caleuche":
			dialog.text = "Przepraszam, dobry panie... Wygrałem to w grze w kości przeciwko jakiemuś nieznajomemu, myślałem, że to jest czarowany amulet leczniczy, ale się myliłem... Nie leczy chorób, a handlarze na targu nie są nim zainteresowani. A oto jesteś - żeglarz, kapitan, uczony człowiek. Spójrz na to, a może ci się przydać.\nDla ciebie ta para tysięcy to mała suma, ale dla mnie to kawałek chleba i łyk rumu na miesiąc. Spójrz, panie...";
			link.l1 = "Dobrze, pokaż...";
			link.l1.go = "Caleuche_1";
		break;
		
		case "Caleuche_1":
			Log_Info("You got a strange amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "Tutaj...";
			link.l1 = "Tak sobie... Ciekawa rzecz, zgadzam się. Jestem pewien, że zostało to skradzione z osad Indian. Dobrze, wezmę to. Oto twoje pieniądze.";
			link.l1.go = "Caleuche_2";
		break;
		
		case "Caleuche_2":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "Dziękuję Ci, panie! Mam nadzieję, że ta rzecz przyniesie Ci szczęście! Niech Pan Cię chroni!";
			link.l1 = "Powodzenia, kumplu. Nie wydawaj od razu wszystkich pieniędzy w karczmie.";
			link.l1.go = "Caleuche_3";
		break;
		
		case "Caleuche_3":
			DialogExit();
			GiveItem2Character(pchar, "kaleuche_amulet1"); 
		break;
		// <-- калеуче
		
		// --> Тайна Бетси Прайс
		case "TBP_Kulon_1":
			dialog.text = "Ech, "+GetAddress_Form(NPChar)+", co pan"+GetSexPhrase("u","i")+" do starej błyskotki?";
			link.l1 = "Jak przyłożę teraz butem w twoją głupią głowę, od razu zrozumiesz, jaki mam w tym interes.";
			link.l1.go = "TBP_Kulon_TO";
			if (CheckAttribute(pchar, "questTemp.TBP_BuyKulon2"))
			{
				link.l2 = "Ten wisiorek należał do Betsy Price. Więc gdzie go znalazłeś?";
				link.l2.go = "TBP_Kulon_leadership";
			}
			DeleteAttribute(pchar, "questTemp.TBP_BuyKulon3");
		break;
		
		case "TBP_Kulon_TO":
			dialog.text = "Leżał przy klombie obok domu z latarnią, "+GetAddress_Form(NPChar)+". Wdeptany w błoto przez gruby męski but. Ale w tym domu już od dawna nikt nie mieszka, więc uznałem, że nie ma właściciela...";
			link.l1 = "Hmm...";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "FencingH", 100);
			DeleteAttribute(pchar, "questTemp.TBP_BuyKulon2");
		break;
		
		case "TBP_Kulon_leadership":
			dialog.text = "Leżał przy klombie obok domu z latarnią, "+GetAddress_Form(NPChar)+". Wdeptany w błoto przez gruby męski but. Ale w tym domu już od dawna nikt nie mieszka, więc uznałem, że nie ma właściciela...";
			link.l1 = "Hmm...";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			DeleteAttribute(pchar, "questTemp.TBP_BuyKulon2");
		break;
		// <-- Тайна Бетси Прайс
	}
}

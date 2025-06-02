// диалог коменданта форта
void ProcessDialogEvent()
{
	int amount, iGunQty, iGunGoods, iGunPrice, iTemp;
	int iTest;
	ref NPChar, sld, location;
	ref arItem;
	ref rColony;
	aref Link, NextDiag;
	string sTemp;
	float locx, locy, locz;
	bool  ok;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
   /*NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Prison\" + NPChar.City + "_Prison.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}*/
    // вызов диалога по городам <--

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "NoMoreTalkExit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;
		
		case "First time":
			location = &Locations[FindLocation(pchar.location)];
			if (rand(4) == 4 && GetNpcQuestPastDayParam(location, "gun_date") > 365 && !CheckAttribute(pchar, "questTemp.PrisonGun"))
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple("Słuchaj, mam do ciebie ważną sprawę. Mam nadzieję, że będziesz mógł pomóc.","Kapitanie, czy mogę zainteresować cię dość lukratywną ofertą?"),RandPhraseSimple("Myslę, że moglibyście nam pomóc w jednej ważnej sprawie.","Kapitanie, mam dla ciebie delikatną propozycję, która mogłaby być dla nas obu dość zyskowna."));					
				link.l1 = "Cóż, mów co myślisz, a zobaczymy...";
				link.l1.go = "GiveTaskGun";
				location.quest.PrisonGun = "Target"; 
				SaveCurrentNpcQuestDateParam(location, "gun_date");
				break;
			}
		
			dialog.text = RandPhraseSimple("Jestem komendantem fortu. Czego tu potrzebujesz?","Na co cię stać? Dlaczego tu przyszedłeś?");
			link.l1 = "O, nic, po prostu rozglądam się po mieście i jego okolicach. Trafiłem tutaj tylko przez szczęśliwy przypadek.";
			//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
			// Офицер с патентом
			if(IsOfficerFullEquip())
			{
				dialog.text = "Witaj w forcie, kapitanie. Potrzebujesz czegoś?";
				link.l1 = "Nie, nic, po prostu przypadkowo wpadłem.";
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "Witaj Wiceadmirał! Czy masz jakieś rozkazy?";
				link.l1 = "Nie, oficerze, bez poleceń. Przyszedłem tylko zobaczyć fort.";
			}
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				dialog.text = "Gubernatorze Generale, Wasza Wysokość! Mam pełen porządek w forcie. Czy będą jakieś rozkazy?";
				link.l1 = "Cieszę się, że jesteś w porządku, oficerze. Bez rozkazów, tylko wpadłem sprawdzić fort.";
			}
			// <-- legendary edition
			link.l1.go = "exit";
			//Jason --> мини-квест Дефицитный товар
			if (CheckAttribute(pchar, "questTemp.Wine.bottle") && NPChar.location == pchar.questTemp.Wine.City + "_ammo" && GetQuestPastDayParam("questTemp.Wine_bottle") < 5)
			{
				link.l11 = "Mam dla ciebie jedną interesującą informację, oficerze. Jeden z twoich żołnierzy, "+pchar.questTemp.Wine.SName+" poprosił mnie o zakup wina w mieście za pośrednictwem mojej mediacji. Biorąc pod uwagę twoje rozkazy...";
				link.l11.go = "Wine_prison";
			}
			// <-- мини-квест Дефицитный товар
			// Карибские нравы
			if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "fraht" && NPChar.location == "portpax_ammo")
			{
				link.l11 = "Dzień dobry, oficerze. Przybywam z kolonii Basse-Terre, na polecenie pewnego mężczyzny o imieniu Gerard LeCroix. W mojej ładowni znajduje się ładunek prochu strzelniczego i bomb dla ciebie...";
				link.l11.go = "trial";
			}
			// Опасный груз -->
			if (pchar.location == "Cumana_Ammo")
			{
				if (pchar.questTemp.zpq != "begin" && pchar.questTemp.zpq != "failed" && pchar.questTemp.zpq != "completed")
				{
					link.l2 = "Wyglądasz zmartwiony, oficerze. Jak mogę ci pomóc?";
					link.l2.go = "zpq_prs1";
				}
				if (pchar.questTemp.zpq == "begin" && GetSquadronGoods(pchar, GOOD_POWDER) >= 15000 && GetQuestPastDayParam("pchar.questTemp.zpq") >= 7)
				{
					link.l3 = "Jestem gotowy zgłosić, że cała partia prochu jest dostarczona. Mój statek jest gotowy do rozładunku.";
					link.l3.go = "zpq_ex";
				}
				if (pchar.questTemp.zpq == "begin")
				{
					link.l4 = "Chcę odrzucić naszą umowę o prochu strzelniczym. To jest zbyt kłopotliwe.";
					link.l4.go = "zpq_fld2";
				}
			}
			// <-- Опасный груз
			NextDiag.TempNode = "First time";
		break;

		// --> Орудия для форта
		case "GiveTaskGun":
			dialog.Text = LinkRandPhrase("Widzisz, działa fortowe są dość zużyte. Skarbiec przyznał fundusze na ich wymianę, ale po prostu nie mam pojęcia, gdzie mogę zakupić nowe: po prostu nie ma sposobu znalezienia ich w naszej kolonii w wymaganej ilości. Więc pomyślałem, że działa z okrętów, które zdobyłeś, mogłyby nam tu być całkiem przydatne.","Muszę wymienić baterię dział w forcie. Fundusze już zostały przydzielone, ale, wiesz... Po prostu nie można kupić potrzebnej ilości w naszej kolonii.","Dostalem zadanie wymiany zuzytych dział fortu, ale nie mogę nigdzie znaleźć wystarczającej ilości.");
			Link.l1 = "Hmm... Czy mógłbyś podać trochę więcej szczegółów? Kaliber, ilość, cena?";
			Link.l1.go = "GiveTaskGun_1";
			pchar.questTemp.PrisonGun = true;
			SaveCurrentQuestDateParam("pchar.questTemp.PrisonGun");
		break;
			
		case "GiveTaskGun_1":
			GetGunType();
			pchar.questTemp.PrisonGun.Sum = makeint(sti(pchar.questTemp.PrisonGun.Price)*sti(pchar.questTemp.PrisonGun.Qty));
			pchar.questTemp.PrisonGun.Luck = rand(4);
			pchar.questTemp.PrisonGun.Id = npchar.location;
			dialog.Text = "Potrzebuję "+pchar.questTemp.PrisonGun.Text+", w ilości "+sti(pchar.questTemp.PrisonGun.Qty)+"  dokładnie jednostek. Będę płacił w złotych dublonach, "+sti(pchar.questTemp.PrisonGun.Price)+" za sztukę. To wyniesie "+FindRussianDublonString(sti(pchar.questTemp.PrisonGun.Sum))+" w sumie. Co odpowiesz? Ach, i jeszcze jedno - przyjmę całą partię, ale nie wcześniej niż za miesiąc - pieniądze jeszcze nie dotarły.";
			Link.l1 = RandPhraseSimple("Nie, oficerze, twoja oferta w ogóle mnie nie interesowała... Przykro mi.","To kuszące, ale chyba rezygnuję. Pozwól mi zachować swoje powody dla siebie.");
			Link.l1.go = "exit_gun";
			Link.l2 = RandPhraseSimple("Cóż, ta oferta jest na pewno interesująca. Uważaj to za umowę.","Chyba to wezmę. To nie jest takie trudne i wyraźnie opłacalne.");
			Link.l2.go = "GiveTaskGun_2";
		break;
			
		case "exit_gun":
			dialog.Text = "Jaka szkoda, kapitanie, liczyłem na ciebie. I... mam nadzieję, że ta rozmowa zostanie wewnątrz twierdzy?";
			Link.l1 = "Nie musisz mi o tym przypominać. Z poważaniem.";
			Link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
			
		case "GiveTaskGun_2":
			dialog.Text = "Cóż, to umowa! Nie ograniczam cię do pewnych warunków, ale proszę, staraj się nie przedłużać tego ponad pół roku. I mam nadzieję, że rozumiesz, że to jest ściśle poufne?";
			Link.l1 = "Oczywiście, że tak. Do zobaczenia, komendant.";
			Link.l1.go = "exit";
			ReOpenQuestHeader("PrisonGun");
			AddQuestRecord("PrisonGun", "1");
			AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("",""));
			AddQuestUserData("PrisonGun", "sName", GetFullName(npchar));
			AddQuestUserData("PrisonGun", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("PrisonGun", "sQty", makeint(pchar.questTemp.PrisonGun.Qty));
			AddQuestUserData("PrisonGun", "sSum", makeint(pchar.questTemp.PrisonGun.Sum));
			AddQuestUserData("PrisonGun", "sText", pchar.questTemp.PrisonGun.Text);
			NextDiag.TempNode = "First time";
		break;	
		
		case "CheckGun":
			if (GetQuestPastDayParam("pchar.questTemp.PrisonGun") < 30)
			{
				dialog.Text = "Powiedziałem ci, żebyś nie przychodził wcześniej niż za miesiąc!";
				Link.l1 = "Cholera! Byłem tak zajęty"+GetSexPhrase("","")+", że zgubiłem a"+GetSexPhrase("","")+" straciłem poczucie czasu ... Przepraszam, przyjdę później, zgodnie z umową.";
				Link.l1.go = "exit";
				NextDiag.TempNode = "First time";
				break;
			}
			if (GetQuestPastDayParam("pchar.questTemp.PrisonGun") > 180)
			{
				dialog.Text = "Hmm... Wiesz, minęło już ponad pół roku od dnia, kiedy zawarliśmy naszą 'umowę'. Już kupiłem działa. Naprawdę myślałeś, że będę na ciebie czekać wiecznie?";
				Link.l1 = "Cholera! I co teraz mam z nimi zrobić?";
				Link.l1.go = "TakeGun_late";
				break;
			}
			iGunGoods = pchar.questTemp.PrisonGun.Goods;
			amount = GetSquadronGoods(Pchar, iGunGoods) - sti(pchar.questTemp.PrisonGun.Qty);
			sTemp = sti(pchar.questTemp.PrisonGun.Qty);
			iTest = FindColony(NPChar.City); // город
			
			if (iTest != -1)
			{
				rColony = GetColonyByIndex(iTest);
			}
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				dialog.Text = "Tak, jesteś gotów mi pomóc?";
				if (amount < 0)
				{
					Link.l1 = "Nie, nadal w trakcie. Chciałem tylko upewnić się, że nasza umowa nadal obowiązuje.";
					Link.l1.go = "exit";
				}
				else
				{
					Link.l1 = "Jestem. Cała partia jest w ładowni - "+sTemp+" jednostek, zgodnie z umową.";
					Link.l1.go = "TakeGun";
				}
			}
			else 
			{
				dialog.text = "Nie widzę twojego statku w porcie. Czy sugerujesz przeciąganie tych dział przez dżunglę? Pośpiesz się do naszego portu i wróć.";
				link.l1 = "Mój statek jest po drugiej stronie wyspy. Przyprowadzę go do portu.";
				link.l1.go = "exit";
			}
		break;
		
		case "TakeGun":
			if (pchar.questTemp.PrisonGun.Luck == 4)
			{
				dialog.Text = RandPhraseSimple("Wiesz, to naprawdę kłopotliwe, ale muszę zrezygnować z naszej umowy. Właśnie mieliśmy kontrolę finansową, a wiesz jak skrupulatni są w takich sprawach. Po prostu nie mogę nic zrobić. Przepraszam.","Kapitanie, wiesz... No cóż, działa zostały nam wysłane z metropolii, a ja musiałem je oczywiście wykupić. Wygórowane ceny, ale... Naprawdę mi przykro, że cię zawiodłem... Też mi z tym nie po drodze.");
				Link.l1 = "Cholera! I co ja teraz mam z nimi zrobić?";
				Link.l1.go = "TakeGun_no";
			}
			else
			{
				dialog.Text = RandPhraseSimple("Doskonale. Wyślę oddział z garnizonu, aby je rozładowali.","Świetnie. Moi żołnierze pomogą ci rozładować działa.");
				Link.l1 = "Czy przygotowałeś płatność?";
				Link.l1.go = "TakeGun_1";
			}
		break;
		
		case "TakeGun_no":
			dialog.Text = "Nie wiem. Sprzedaj je w stoczni, wyposaż handlowy statek, zatop je... Naprawdę nie mam pojęcia. I proszę, nie mów nikomu o tej transakcji.";
			Link.l1 = "O, mówisz! Po prostu nie mam słów!";
            Link.l1.go = "exit";
			AddQuestRecord("PrisonGun", "3");
			CloseQuestHeader("PrisonGun");
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
		
		case "TakeGun_late":
			dialog.Text = "Nie mam pojęcia. To twój problem. Sprzedaj je, wyrzuć, zatop - naprawdę mi to wszystko jedno.";
			Link.l1 = "Och, to było po prostu marnowanie czasu...";
            Link.l1.go = "exit";
			AddQuestRecord("PrisonGun", "4");
			AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("",""));
			AddQuestUserData("PrisonGun", "sName", GetFullName(npchar));
			CloseQuestHeader("PrisonGun");
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
		
		case "TakeGun_1":
			iGunGoods = pchar.questTemp.PrisonGun.Goods;
			amount = sti(pchar.questTemp.PrisonGun.Qty);
			iTemp = sti(pchar.questTemp.PrisonGun.Sum);
			dialog.Text = "Oczywiście. Oto twoje złoto - rób, co chcesz.";
			Link.l1 = "Dzięki! To była przyjemność robić z tobą interesy!";
            Link.l1.go = "TakeGun_2";
			TakeNItems(pchar, "gold_dublon", iTemp);
			Log_Info("You have received "+FindRussianDublonString(sti(pchar.questTemp.WPU.Escort.Money))+"");
			PlaySound("interface\important_item.wav");
			RemoveCharacterGoods(Pchar, iGunGoods, amount);
		break;
		
		case "TakeGun_2":
			dialog.Text = "Uczucie jest wzajemne. Byłeś bardzo pomocny. I proszę cię, niech ta umowa zostanie w tym pokoju.";
			Link.l1 = "Oczywiście. Najlepsze życzenia dla ciebie.";
            Link.l1.go = "exit";
			AddQuestRecord("PrisonGun", "2");
			AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("PrisonGun");
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
		// <-- орудия для форта

		//Jason --> мини-квест Дефицитный товар
		case "Wine_prison":
			dialog.text = "Co?! Surowo zabroniłem picia na terenie fortu! No cóż, będzie musiał za to zapłacić. Odliczę 1000 pesos od jego wypłaty i przekażę je tobie jako nagrodę za czujność. A ten facet posiedzi w areszcie przez trzy dni.";
			link.l1 = "Dziękuję, "+GetAddress_FormToNPC(NPChar)+". Zatrzymanie takich naruszeń to nasz wspólny obowiązek.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 1000);
			ChangeCharacterComplexReputation(pchar,"nobility", -1); 
			DeleteAttribute(pchar, "questTemp.Wine.bottle");
			pchar.quest.Wine_Exchange.over = "yes";//снять прерывание
			pchar.quest.WineTraderQM.over = "yes";//снять прерывание
			WineTraderQMDel();
			sld = characterFromId(pchar.questTemp.Wine.id);
			sld.lifeday = 0;
			CloseQuestHeader("Wine");
			NextDiag.TempNode = "First time";
		break;
		// <-- мини-квест Дефицитный товар
		
		// Карибские нравы
		case "trial":
			iTest = FindColony(NPChar.City); // город
			QuestPointerDelLoc("portpax_town", "reload", "gate_back");
			QuestPointerDelLoc("portpax_exittown", "reload", "reload2_back");
			QuestPointerDelLoc("portpax_fort", "reload", "reload2");
			if (iTest != -1)
			{
				rColony = GetColonyByIndex(iTest);
			}
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				if (GetSquadronGoods(pchar, GOOD_BOMBS) < 2500 || GetSquadronGoods(pchar, GOOD_POWDER) < 2500)
				{
					dialog.text = "Hmm. Ale ta partia nie jest pełna! Jak to się stało?";
					link.l1 = "Cholera! Przepraszam, to moja wina. Natychmiast zakupię brakującą ilość i przekażę Ci całą partię, zgodnie z naszą umową.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Więc jesteś naszym kurierem? Dobrze. Uporządkujmy sprawy z ładunkiem, a potem otrzymasz dalsze instrukcje.";
					link.l1 = "Dobrze.";
					link.l1.go = "trial_1";
				}
			}
			else
			{
				dialog.text = "Nie widzę twojego statku w porcie. Czy sugerujesz ciągnięcie ładunku przez dżunglę? Pośpiesz się do naszego portu i wróć.";
				link.l1 = "Mój statek jest po drugiej stronie wyspy. Zawiozę go do portu.";
				link.l1.go = "exit";
			}
		break;
		
		case "trial_1":
			if(!bImCasual) pchar.quest.Trial_FrahtFail.over = "yes"; // belamour legendary edition если был - снять таймер
			dialog.text = "Dobrze, bomby i proch strzelniczy, 2500 jednostek każdego... Dobrze. Żołnierze rozładują ładunek, twoi ludzie mogą zrobić przerwę. Oto twoja zapłata za fracht - pięć tysięcy peso.";
			link.l1 = "Dzięki! Co powinienem zrobić dalej? Monsieur LeCroix powiedział...";
			link.l1.go = "trial_2";
			DelLandQuestMark(npchar);
		break;
		
		case "trial_2":
			AddMoneyToCharacter(pchar, 5000);
			RemoveCharacterGoods(pchar, GOOD_BOMBS, 2500);
			RemoveCharacterGoods(pchar, GOOD_POWDER, 2500);
			dialog.text = "Tak, tak, teraz otrzymasz swoje instrukcje. Jesteś gotowy zwrócić uwagę?";
			link.l1 = "Pewnie, oficerze.";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			dialog.text = "So, our military ship 'Warlike' is cruising near the Spanish colony Porto Bello, in the southern part of the Spanish Main. This vessel is under the command of Florian Shoke, who is preparing an ambush of a Spanish heavy galleon set to leave Porto Bello in two weeks.\nThe problem is that our frigate's cannons are suffering from a casting defect, and we need to replace fifteen cannons to save the mission; otherwise, the galleon will outnumber 'Warlike' in both guns and men. \nWithout the replacement, Florian Shoke will be forced to sail away with no result. Such a sequence of events is highly undesirable. Your task is to save the mission by delivering fifteen cannons within fourteen days.";
			link.l1 = "Czyli, muszę wziąć na pokład piętnaście dział, udać się do Portobello, poszukać fregaty 'Militant' i przekazać działa kapitanowi Florianowi Shoke?";
			link.l1.go = "trial_4";
		break;
		
		case "trial_4":
			dialog.text = "Dokładnie. Trafiłeś w dziesiątkę. Jesteś gotowy podjąć się tej misji?";
			link.l1 = "Co z zapłatą?";
			link.l1.go = "trial_5";
			link.l2 = "Przykro mi, oficerze, ale po prostu nie chcę się angażować. Proszę mnie wybaczyć.";
			link.l2.go = "trial_exit";
		break;
		
		case "trial_exit":
			dialog.text = "Masz swoje racje, ale liczyłem na twoją zgodę. Teraz będę musiał znaleźć innego kuriera, choć nie mam już wiele czasu... Cóż, nie zatrzymuję cię dłużej, kapitanie.";
			link.l1 = "Najlepsze pozdrowienia.";
			link.l1.go = "trial_exit_1";
		break;
		
		case "trial_exit_1":
			DialogExit();
			AddQuestRecord("Trial", "6");
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		
		case "trial_5":
			dialog.text = "Nie martw się o to. Florian Shoke zapłaci ci dwieście złotych dublonów z skarbca statku. Poza tym, jestem pewien, że chciałby wykorzystać ciebie i twój statek do swoich celów - oczywiście za twoją zgodą.";
			link.l1 = "Dobrze, jestem na tej misji! Gdzie są działa?";
			link.l1.go = "trial_6";
		break;
		
		case "trial_6":
			dialog.text = "Dam rozkaz żołnierzom, aby natychmiast załadowali je na twój statek. Wypływaj tak szybko, jak możesz, panie! Powodzenia!";
			link.l1 = "Dzięki. Szczęście na pewno nie zaszkodzi, a także wiatr w żagle...";
			link.l1.go = "trial_7";
		break;
		
		case "trial_7":
			DialogExit();
			AddQuestRecord("Trial", "7");
			pchar.questTemp.Trial = "cannon";
			// belamour legendary edition
			if(!bImCasual) SetFunctionTimerCondition("Trial_CannonFail", 0, 0, 21, false); 
			else NewGameTip("Exploration mode: timer is disabled.");
			SetCharacterGoods(pchar, GOOD_CANNON_24, GetCargoGoods(pchar, GOOD_CANNON_24)+15);
			if (MOD_SKILL_ENEMY_RATE >= 6)
			{
				EnemyNationHunterOnMap(true);//запуск перехватчиков
			}
			pchar.quest.Trial_cannon.win_condition.l1 = "location";
			pchar.quest.Trial_cannon.win_condition.l1.location = "Portobello";
			pchar.quest.Trial_cannon.function = "Trial_CreateFlorianFrigate";
			// Sinistra - квест "Встреча с Диего"
			bDisableFastReload = true;
			PChar.quest.VsD_GiumDyubua.win_condition.l1 = "location";
			PChar.quest.VsD_GiumDyubua.win_condition.l1.location = "PortPax_Fort";
			PChar.quest.VsD_GiumDyubua.win_condition = "VsD_GiumDyubua";
			AddMapQuestMarkShore("Shore47", false);
		break;
		
		// Опасный груз -->
		case "zpq_prs1":
			if(!isBadReputation(pchar, 70))
			{
				dialog.text = "Hm, być może. No cóż, z powodu twojej dobrej reputacji, zaryzykuję i zaufam ci. W innym przypadku, nawet bym o tym z tobą nie rozmawiał. Chodzi o to, że potrzebujemy dość dużej partii specjalnego ładunku, więc potrzebny ci będzie duży statek i gotowość do ryzyka. Musisz mi też dać słowo, że nie powiesz o tym nikomu.\nJeśli to ci przeszkadza, powiedz mi o tym teraz. Myślę, że jasno wyraziłem swoje stanowisko...";
				link.l1 = "Dźwięki intrygująco. Jestem w środku, jeśli zapłata jest dobra, chociaż nie mam pojęcia, o jakim ładunku mówisz. Masz moje słowo tak czy inaczej.";
				link.l1.go = "zpq_prs2";
				link.l2 = "Powiedziałbym nie, przypuszczam... gdybym dał ci słowo, musiałbym wykonywać pracę, która wydaje się dość kłopotliwa. Nie zrobię tego.";
				link.l2.go = "zpq_fld";
				notification("Reputation Check Passed", "None");
			}
			else
			{
				dialog.text = "Twoja reputacja jest dla mnie nie do przyjęcia. Proszę cię, opuść ten pokój. Potrafimy sami rozwiązać nasze problemy.";
				link.l1 = "Cokolwiek, rozwiąż je potem...";
				link.l1.go = "exit";
				notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(71))+")", "None");
			}		
		break;
		
		case "zpq_fld":
			dialog.text = "Cóż, przynajmniej odrzuciłeś w uczciwy sposób... Nie zatrzymuję cię już dłużej.";
			link.l1 = "Pożegnanie.";
			link.l1.go = "exit";
			pchar.questTemp.zpq = "failed";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Cumana");
		break;
		
		case "zpq_fld2":
			dialog.text = "Hm, właściwie nie spodziewałem się tego po tobie. Muszę cię prosić o wyjście... I pamiętaj o obietnicy nieujawniania żadnych informacji.";
			link.l1 = "Przykro mi...";
			link.l1.go = "exit";
    		ChangeCharacterComplexReputation(pchar,"nobility", -3);
			if (pchar.questTemp.zpq == "begin")
			{
				AddQuestRecord("zpq", "6");
				AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
				CloseQuestHeader("zpq");
			}
			pchar.questTemp.zpq = "failed";
		break;
		
		case "zpq_prs2":
			dialog.text = "Wspaniale. Wspaniale. Problem polega na tym, że niedawna burza uszkodziła nasze zapasy prochu do strzelby w arsenałach fortu. Mam nadzieję, że nie muszę tłumaczyć ci, że mamy tutaj delikatny kłopot. W razie długiego oblężenia fort nie będzie w stanie nic zrobić. Nie wytrzymamy długo.";
			link.l1 = "Teraz rozumiem. Jakiego ładunku potrzebujesz - i w jakiej ilości?";
			link.l1.go = "zpq_prs3";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Cumana");
		break;
		
		case "zpq_prs3":
			dialog.text = "Potrzebujemy 15 000 beczek prochu do strzelniczego. Zapłacę ci 100 000 peso... Musisz zrozumieć, że to bardzo dobra cena. Nasz obecny stan zmusza mnie do poniesienia takich kosztów, chociaż przekonanie skarbnika gubernatora do tego było problematyczne... Sezon burzowy nie pozwoli nam korzystać z naszych własnych linii zaopatrzeniowych i nie chcemy, aby wszyscy wiedzieli o tym problemie...";
			link.l1 = "Rozumiem... cena jest naprawdę atrakcyjna. Wspomniałeś o ryzyku...";
			link.l1.go = "zpq_prs4";
		break;
		
		case "zpq_prs4":
			dialog.text = "Chodziło mi o to, że taka duża ilość prochu strzelniczego może być bardzo niebezpieczna podczas transportu. Widziałem kilka eksplozji na własne oczy, czasami jedna iskra może zrobić robotę. Ale jeśli napotkasz burzę... Całe konwoje zazwyczaj trzymają dystans od potencjalnej łodzi z prochem. Jeśli wybuchnie, wszyscy są martwi!";
			link.l1 = "Rozumiem... Ale zawsze dotrzymuję słowa, uważaj to za zrobione.";
			link.l1.go = "zpq_prs5";
			link.l2 = "Cóż, señor... Opowiadałeś mi takie straszne rzeczy, że straciłem wszelką chęć do tej roboty.";
			link.l2.go = "zpq_fld2";
		break;
		
		case "zpq_prs5":
			dialog.text = "Dobrze, bardzo się cieszę, że doszliśmy do porozumienia. Zapłacę Ci, jak tylko przyniesiesz mi ładunek.\nBędę miał pieniądze za tydzień, nie wcześniej, więc nie spiesz się, ale prosiłbym Cię, abyś starał się nie zbytnio zwlekać.";
			link.l1 = "Rozumiem, senor. Zajmuję się tym.";
			link.l1.go = "zpq_prs5_ok";
		break;
		
		case "zpq_prs5_ok":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.zpq = "begin";
			pchar.questTemp.zpq.time = 20;
			AddQuestRecord("zpq", "1");
			AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
			SaveCurrentQuestDateParam("pchar.questTemp.zpq");
		break;
		
		case "zpq_ex":
			dialog.text = "Wreszcie! Myślałem, że już zapomniałeś o naszej umowie. Natychmiast kazałem moim żołnierzom rozpocząć rozładunek twojego statku. Praca z prochem to bardzo delikatne zajęcie, ha-ha!";
			link.l1 = "To wspaniałe, senorze, ale muszę przypomnieć Ci o zapłacie.";
			link.l1.go = "zpq_ex2";
			RemoveCharacterGoods(pchar, GOOD_POWDER, 15000);
			AddCharacterExpToSkill(pchar, "Sailing", 500);
			AddCharacterExpToSkill(pchar, "Fortune", 500);

            pchar.quest.zpq_sld1_fc.win_condition.l1 = "location";
            pchar.quest.zpq_sld1_fc.win_condition.l1.location = "Cumana_ExitTown";
            pchar.quest.zpq_sld1_fc.function = "zpq_sld1_fc";
		break;
		
		case "zpq_ex2":
			dialog.text = "Tak, oczywiście. Zapłacisz 50 000 pesos, jak się umówiliśmy.";
			link.l1 = "Pewnie żartujesz ze mnie, senor?! Mieliśmy umowę na 100 000 pesos!";
			link.l1.go = "zpq_ex3";
			if(CheckCharacterPerk(pchar, "Trustworthy"))
			{
				notification("Trustworthy", "Trustworthy");
				link.l2 = "(Zaufany) Zaczynam myśleć, że chcesz mnie oszukać, więc nie wyjdę stąd bez moich 125 000 pesos!";
				link.l2.go = "zpq_ex4";
			}
			link.l3 = "Hm.. Widzę, że okoliczności się zmieniły. No cóż, lepiej wezmę pieniądze i odejdę...";
			link.l3.go = "zpq_ex5";
		break;
		
		case "zpq_ex3":
			if (GetSummonSkillFromName(pchar, "Leadership") > 35)
			{
				notification("Skill Check Passed", "Leadership");
				dialog.text = "Ach, tak... Dokładnie! 100 000 pesos. Zapomniałem, przepraszam. To moja starość jest winna, skleroza wiesz... Oczywiście, oto twoje monety. Było mi miło z tobą robić interesy, kapitanie. Teraz przepraszam, ale mam dużo pracy do zrobienia...";
				link.l1 = "Podobnie tobie, senorze. Do zobaczenia.";
				link.l1.go = "exit";
				pchar.questTemp.zpq = "completed";
				AddQuestRecord("zpq", "2");
				AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
				CloseQuestHeader("zpq");
				pchar.questTemp.zpq.sum = 100000;
				AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
			}
			else
			{
				notification("Skill Check Failed (36)", "Leadership");
				dialog.text = "Co?! Weź swoje pieniądze i znikaj, albo zgnijesz w tej kazamacie!";
				link.l1 = "Jesteś takim kłamcą, señor! Radzę ci dać mi moje pieniądze w dobry sposób, albo zabiorę ładunek!";
				link.l1.go = "zpq_ex_agry";
				link.l2 = "Przepraszam... Dobrze, wezmę sumę, którą proponujesz i skończymy.";
				link.l2.go = "zpq_ex5";
				Log_info("Leadership skill is not sufficient");
			}
		break;
		
		case "zpq_ex4":
				dialog.text = "Takie niegrzeczność! Nie jestem psychicznie chory i dokładnie pamiętam, że oferowałem 100 000 pesos.\n Do diabła! Nie zamierzam grać w twoje gry!";
				link.l1 = "Uspokój się. Pomyśl o gotowym palniku wypełnionym prochem tuż przed twoją twierdzą. Jeśli powiem tylko słowo, twoja twierdza zamieni się w ruinę.";
				link.l1.go = "zpq_ex6";
		break;
		
		case "zpq_ex6":
			dialog.text = "Hm-Hm... mocny argument. Mówisz o 125 000 pesos? Proszę, weź je, a teraz wybacz, ale mam robotę do wykonania...";
			link.l1 = "Do widzenia, senorze. Do zobaczenia.";
			link.l1.go = "exit";
			pchar.questTemp.zpq = "completed";
            AddQuestRecord("zpq", "5");
			CloseQuestHeader("zpq");
			pchar.questTemp.zpq.sum = 125000;
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
			/*else
			{
				dialog.text = "Co?! Jestem wojskowym oficerem! Myślisz, że możesz mnie przestraszyć, dziecino?! Strażnicy, bierzcie "+GetSexPhrase("on","jej")+"!";
				link.l1 = "Powodzenia w próbach, szczury z kazamat...";
				link.l1.go = "zpq_ex_war";
			}*/
		break;
		
		case "zpq_ex5":
			dialog.text = "Wspaniale! Dokonałeś właściwego wyboru. Weź swoje monety i do widzenia. To była przyjemność!";
			link.l1 = "Żegnaj...";
			link.l1.go = "exit";
			pchar.questTemp.zpq = "completed";
            AddQuestRecord("zpq", "3");
			AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("zpq");
			pchar.questTemp.zpq.sum = 50000;
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
		break;
		
		case "zpq_ex_agry":
			dialog.text = "Ach ty łajdaku! Strażnicy, weźcie "+GetSexPhrase("on","ona")+"!";
			link.l1 = "Argh! Wygląda na to, że muszę wziąć moje pieniądze z twojego bezdechowego ciała...";
			link.l1.go = "zpq_ex_war";
		break;
		
        case "zpq_ex_war":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetFightMode(PChar, true);
			pchar.questTemp.zpq = "failed";
            AddQuestRecord("zpq", "4");
			CloseQuestHeader("zpq");
			pchar.questTemp.zpq.sum = 100000;
			AddMoneyToCharacter(npchar, makeint(sti(pchar.questTemp.zpq.sum)*2 + rand(5000)));
			GiveItem2Character(npchar, "blade_21");
			EquipCharacterbyItem(npchar, "blade_21");
			npchar.SaveItemsForDead  = true;
			npchar.DontClearDead = true;
			npchar.cirassId = Items_FindItemIdx("cirass3");
			chrDisableReloadToLocation = true;
			string slai_group = GetNationNameByType(sti(npchar.nation))  + "_citizens";
			LAi_group_AttackGroup(slai_group, LAI_GROUP_PLAYER);
			LAi_group_SetCheck(slai_group, "OpenTheDoors");
			AddSimpleRumour("Such terrible things happen here! They say that some prisoner has escaped from the casemates! He slaughtered all the guards, stole the treasury, and just went away! Wow!", SPAIN, 5, 1);
		break;
		// <-- Опасный груз
	}
}

void GetGunType()
{
	int iGunType;
	if(makeint(pchar.rank) < 6) iGunType = rand(1);	//18&&24
	if(makeint(pchar.rank) >= 6 && makeint(pchar.rank) < 15) iGunType = rand(2); //24&&32	
	if(makeint(pchar.rank) >= 15 && makeint(pchar.rank) < 24) iGunType = rand(2)+2; //32&&36&&42
	if(makeint(pchar.rank) >= 24) iGunType = 5-rand(1); //36clv&&42
	int iAdd = makeint(GetSummonSkillFromName(pchar, SKILL_COMMERCE)/20);
	
	switch (iGunType)
	{
		case 0:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_24;     					
			pchar.questTemp.PrisonGun.Price = 28 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*5+25+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "24 calibre cannons";
		break; 
		case 1:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CULVERINE_18;     					
			pchar.questTemp.PrisonGun.Price = 25 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*5+25+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "couleuvrines";
		break; 
		case 2:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_32;     					
			pchar.questTemp.PrisonGun.Price = 32 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*3+15+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "32 calibre cannons";
		break; 
		case 3:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_36;     					
			pchar.questTemp.PrisonGun.Price = 36 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*3+15+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "36 calibre cannons";
		break;
		case 4:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CULVERINE_36;     					
			pchar.questTemp.PrisonGun.Price = 49 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)+15+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "full couleuvrines";
		break; 
		case 5:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_42;     					
			pchar.questTemp.PrisonGun.Price = 40 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)+20+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "42 calibre cannons";
		break; 
	}
}

// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Czego chcesz? Pytaj śmiało.","Słucham cię, jakie masz pytanie?"),"To już drugi raz, kiedy próbujesz zapytać...","To już trzeci raz, gdy próbujesz zapytać...","Kiedy to się skończy?! Jestem zajętym człowiekiem, pracuję nad sprawami kolonii, a ty wciąż mnie niepokoisz!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniam zdanie...","Nie teraz. Złe miejsce i czas."),"Prawda... Ale później, nie teraz...","Spytam... Ale trochę później...","Przykro mi, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";

			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
				{
					link.l1 = "Chcę porozmawiać o twoim więźniu.";
					link.l1.go = "CapComission1";
					DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
				}	
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.PirateShips"))
				{
					link.l1 = "Cześć "+NPChar.name+"  Jestem tu w sprawie twojego więźnia.";
					link.l1.go = "CapComission3";
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
				{
					link.l1 = "Chcę porozmawiać o twoim więźniu.";
					link.l1.go = "CapComission6";
				}
			}
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin")
			{
				link.l1 = "Słyszałem, że zajmujesz się interesem związanym z więźniami...";
				link.l1.go = "Marginpassenger";
			}
		break;
		
		
		case "CapComission1":
			dialog.text = "Ha-ha. Myślisz, że mam tu tylko jednego więźnia? Podaj jego imię.";
			link.l1 = pchar.GenQuest.CaptainComission.SlaveName+"Jest tutaj?";
			link.l1.go = "CapComission2";
		break;

		case "CapComission2":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = "Był. Sprzedałem go właścicielowi plantacji z Barbadosu - pułkownikowi Bishopowi, gdy był tutaj tydzień temu.";
				link.l1 = "Cholera...";
				link.l1.go = "CapComission2_1";
			}
			else
			{
				pchar.quest.CaptainComission_SellSlave.over = "yes";
				dialog.text = "Ach, nareszcie. Już myślałem, żeby sprzedać go właścicielowi plantacji z Barbadosu, będzie tu za tydzień lub dwa... Masz okup?"+GetSexPhrase("","")+"?";
				link.l1 = "Spójrz, "+NPChar.name+" , jest mały problem... Właściwie, nie mam aż tyle pieniędzy. Ale jestem gotów do pracy.";
				link.l1.go = "CapComission2_2";
				if(makeint(pchar.money) > 150000)
				{
					link.l2 = "Dobrze, że go nie sprzedałeś. Oto twoje monety - 150.000 pesos. Gdzie mogę go dostać?"link.l2.go ="CapComission2_3";
				}	
			}
		break;
		
		case "CapComission2_1":
			dialog.text = "Byłeś zbyt wolny... I dlaczego ci na nim zależy? Negocjowałem tylko z jego krewnymi.";
			link.l1 = "Prosili mnie, żebym tu przyszedł.";
			link.l1.go = "CapComission2_11";
		break;
		
		case "CapComission2_11":
			dialog.text = "No, spóźniłeś się. Nic nie mogę zrobić.";
			link.l1 = "Słuchaj, za ile go sprzedałeś, jeśli to nie tajemnica?"; 
			link.l1.go = "CapComission2_12";
		break;
		
		case "CapComission2_12":
			dialog.text = "Eh, to nie jest. Ale ci nie powiem... Będziesz się śmiał, jeśli to zrobię. Ha-ha-ha-ha! Żegnaj.";
			link.l1 = "Do zobaczenia.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			CaptainComission_GenerateManager();
		break;
		
		case "CapComission2_2":
			if(rand(1) == 0)
			{
				dialog.text = "Cóż, cóż... Mam tu jedną sprawę... Nawet nie wiem, jak zacząć. Muszę zatopić jednego pirata, który zaszedł za daleko.";
				link.l1 = "Nie można go po prostu zabić w dżungli?";
				link.l1.go = "CapComission2_2_1";
			}
			else
			{
				dialog.text = "No cóż, "+pchar.name+", wiesz, to tak nie działa. Wróć z pieniędzmi, a dostaniesz swojego słabeusza, ha-ha.";
				link.l1 = "Dobrze, zatem żegnaj.";
				link.l1.go = "exit";
				if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
				{
					AddQuestRecord("CaptainComission1", "31");
					AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
				}	
				pchar.GenQuest.CaptainComission.RepeatSpeak = true;
			}
		break;

		case "CapComission2_2_1":
			dialog.text = "To nie tak, jak działa interes, wiesz... Nie potrzebuję jego śmierci, muszę nauczyć niektórych ludzi, by unikali zabierania mojej części łupu. Ale jeśli pójdzie nakarmić rekiny, nie będę zmartwiony.";
			link.l1 = "Czemu nie wyślesz za nim swoich ludzi?";
			link.l1.go = "CapComission2_2_2";
		break;
		
		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "Hm.. Cóż "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.UnknownPirateName,NAME_NOM)+"przekonał niektórych piratów, że ich część łupu zostanie przechowana w naszej skrytce niedaleko "+XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore+"Gen")+". Ich dwa statki '"+pchar.GenQuest.CaptainComission.ShipName1+"i"+pchar.GenQuest.CaptainComission.ShipName2+"podnieśli kotwice niedawno i odpłynęli do "+XI_ConvertString(pchar.GenQuest.CaptainComission.Island+"Abl")+"Teraz widzisz, dlaczego nie mogę zaufać moim ludziom, by wykonali tę robotę?";
			link.l1 = "Rozumiem. Ile mam czasu?";
			link.l1.go = "CapComission2_2_3";
		break;
		
		case "CapComission2_2_3":
			dialog.text = "12 do 15 dni, nie więcej. Ważne jest dla mnie, aby nie dotarli do skrytki, zatopienie ich z cennym ładunkiem byłoby nonsensem. W takim przypadku lepiej, żeby to oni przywieźli go tutaj...";
			link.l1 = "Dobrze, wchodzę w to. Spróbuję ich złapać.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Abl"));
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Dat"));
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);	
			pchar.GenQuest.CaptainComission.PirateShips = "goaway";	
		break;
		
		case "CapComission2_3":
			dialog.text = "Nie martw się. Moi ludzie dostarczą go na twój statek. A dlaczego się nim przejmujesz?";
			link.l1 = "Nie. Jego krewni poprosili mnie, bym go dostarczył.";
			link.l1.go = "CapComission2_31";
		break;
		
		case "CapComission2_31":
			dialog.text = "Ach, to dobrze. Prawie mi było żal, że dałem tak niską cenę za twojego człowieka. Ha-ha-ha-ha. Żegnaj.";
			link.l1 = "Do zobaczenia.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));			
			addMoneyToCharacter(pchar, -150000);
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission3":
			dialog.text = "Cóż, "+GetFullName(pchar)+", zatopiłeś mojego kumpla? He-he-he...";
			if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = "Nie. Nie udało mi się ich złapać. I nie spotkałem ich po powrocie.";
				link.l1.go = "CapComission4";
			}
			else
			{
				if(pchar.GenQuest.CaptainComission.PirateShips == "died")	
				{
					link.l1 = "Zrobiłem to. Wysłałem ich na karmienie rekinów.";
					link.l1.go = "CapComission5";
				}
			}	
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
		break;
		
		case "CapComission4":
			dialog.text = "Cholera! Nieważne, to teraz nie ma znaczenia! Jaka będzie twoja następna sugestia?";
			link.l1 = "Może masz dla mnie łatwiejsze zadanie?";
			link.l1.go = "CapComission4_1";
			link.l2 = "Słuchaj, "+NPChar.name+", obniż cenę za więźnia...";
			link.l2.go = "CapComission4_2";
		break;
		
		case "CapComission4_1":
			dialog.text = "Nie.";
			link.l1 = "Żegnaj zatem...";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");			
		break;
		
		case "CapComission4_2":
			dialog.text = "Obniżyć cenę?! Właśnie straciłem mój skarb przez twoją nieudolność! Teraz mogę podnieść cenę! Możesz go wziąć za 200.000 pesos, jeśli chcesz, albo możesz się stąd wynosić!";
			link.l1 = "To zbyt drogie... Żegnaj...";
			link.l1.go = "CapComission4_4";
			if(sti(pchar.money) >= 200000)
			{
				link.l2 = "Cholera, dobrze, weź swoją monetę.";
				link.l2.go = "CapComission4_5";
			}	
		break;
				
		case "CapComission4_4":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
		break;
		
		case "CapComission4_5":
			dialog.text = "Możesz wziąć tego słabeusza...";
			link.l1 = "Żegnaj.";
			link.l1.go = "exit";
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
				
		case "CapComission5":
			dialog.text = "Ho-ho! Dobra robota! Zabieraj swojego słabeusza i powodzenia.";
			link.l1 = "Dzięki. Żegnaj.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");
		break;
				
		case "CapComission6":
			dialog.text = "Czy przyniosłeś pieniądze, Charles? Nie żartowałem, sprzedając tamtego człowieka na plantację.";			
			link.l1 = "Słuchaj, "+NPChar.name+", jest pewien problem... Nie mam tyle pieniędzy. Ale jestem gotów do pracy.";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "Dobrze, że go nie sprzedałeś. Oto twoje monety - 150.000 peso. Gdzie mogę go znaleźć?"link.l2.go ="CapComission2_3";
			}			
		break;
		
		//Захват пассажиров
		case "Marginpassenger":
			dialog.text = " A dlaczego cię obchodzi, co robię? Wiesz, lepiej żebyś stąd odszedł...";
			link.l1 = "Tshh, uspokój się. Mam dla ciebie propozycję biznesową. Chodzi o twojego więźnia.";
			link.l1.go = "Marginpassenger_1";
		break;
		
		case "Marginpassenger_1":
			dialog.text = "Ach, dobrze. Kogo chcesz wykupić?";
			link.l1 = "Poczekaj. Nie przyszedłem się wykupić, przyszedłem zaoferować ci kupno więźnia. No i będziesz miał okazję otrzymać za niego okup.";
			link.l1.go = "Marginpassenger_2";
		break;
		
		case "Marginpassenger_2":
			dialog.text = "Hm. A dlaczego potrzebujesz mojej pomocy? Nie chcesz dostać pieniędzy bezpośrednio dla siebie?";
			link.l1 = "To dość ryzykowne dla mnie. Mogę mieć problemy z władzami.";
			link.l1.go = "Marginpassenger_3";
		break;
		
		case "Marginpassenger_3":
			dialog.text = "Ha-h... dobrze więc. Spójrzmy. Kto jest twoim więźniem?";
			link.l1 = "To jest "+pchar.GenQuest.Marginpassenger.Text+" "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City+"Gen")+".";
			link.l1.go = "Marginpassenger_4";
		break;
		
		case "Marginpassenger_4":
			int iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "Widzę. Byłby to dobry handel, jeśli nie kłamiesz. Przypuszczam, że mogę ci zapłacić za tego człowieka, "+iTemp+"pesos, albo dać ci jakieś ciekawe informacje w zamian. Wybór należy do ciebie.";
			link.l1 = "Lepiej wezmę tę monetę. Mam dość tego interesu...";
			link.l1.go = "Marginpassenger_money";
			link.l2 = "Ha! Opowiedz mi więcej. Jestem pewien, że dasz mi coś interesującego.";
			link.l2.go = "Marginpassenger_offer";
		break;
		
		case "Marginpassenger_money":
			dialog.text = "Pieniądze zatem. Weź je. Teraz to nie twój problem. Dostarcz przedmiot sprzedaży tutaj.";
			link.l1 = "On już musi być blisko bram miasta. Dzięki! Naprawdę mi pomogłeś.";
			link.l1.go = "Marginpassenger_money_1";
		break;
		
		case "Marginpassenger_money_1":
			iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "Nie ma za co, przynieś mi więcej... Do zobaczenia!";
			link.l1 = "Powodzenia...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, iTemp);
			ref sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			AddQuestRecord("Marginpassenger", "12");
			AddQuestUserData("Marginpassenger", "sSum", iTemp);
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
		break;
		
		case "Marginpassenger_offer":
			pchar.GenQuest.Marginpassenger.Goods = GOOD_EBONY + rand(makeint(GOOD_SANDAL - GOOD_EBONY));
			pchar.GenQuest.Marginpassenger.GoodsQty = 200+rand(10)*10;
			switch (hrand(1))
			{
				case 0: //бухта на южном мейне
					SelectSouthshore();
					while (!isLocationFreeForQuests(pchar.GenQuest.Marginpassenger.Shore)) SelectSouthshore();
					dialog.text = "Miło robić interesy z mądrym człowiekiem. Teraz słuchaj: za kilka dni do "+XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Tamto")+" hiszpańska ekspedycja przybędzie z Main, załadowana cennymi towarami. Będą czekać na statek, który ma zabrać ładunek. Jeśli dotrzesz tam w ciągu tygodnia, będziesz miał szansę zabrać ładunek dla siebie.\nNa twoim miejscu, już bym się ruszał na swój statek. I przyprowadź tu więźnia.";
					link.l1 = "Dzięki! Towary będą miłą rekompensatą za moje kłopoty. A mój pasażer musi być już blisko bram miasta. Zostanie do ciebie przyprowadzony.";
					link.l1.go = "Marginpassenger_offer_1";
				break;
				
				case 1: //просто кораблик
					SelectSouthcity();
					pchar.GenQuest.Marginpassenger.ShipName1 = GenerateRandomNameToShip(SPAIN);
					dialog.text = "Dobrze robić interesy z mądrym człowiekiem. Teraz słuchaj: za około tydzień hiszpańska brygantyna '"+pchar.GenQuest.Marginpassenger.ShipName1+"  załadowany wartościowym towarem popłynie z "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Ogólne")+" do "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Generał")+"Jeśli się pośpieszysz, złapiesz go łatwo.\nWciąż tu jesteś? Gdybym był tobą, już bym płynął na swój statek. I przyprowadź tu więźnia.";
					link.l1 = "Dzięki! Towary będą miłą rekompensatą za moje kłopoty. A mój pasażer musi być w pobliżu bram miasta. Zostanie przywieziony do ciebie.";
					link.l1.go = "Marginpassenger_offer_2";
				break;
			}
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			pchar.GenQuest.Marginpassenger = "final";
		break;
		
		case "Marginpassenger_offer_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "13");
			AddQuestUserData("Marginpassenger", "sShore", XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat"));
			SetFunctionTimerCondition("Marginpassenger_SouthshoreOver", 0, 0, 7, false);
			pchar.quest.Marginpassenger.win_condition.l1 = "location";
			pchar.quest.Marginpassenger.win_condition.l1.location = pchar.GenQuest.Marginpassenger.Shore;
			pchar.quest.Marginpassenger.function = "Marginpassenger_Southshore";
		break;
		
		case "Marginpassenger_offer_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "16");
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen"));
			AddQuestUserData("Marginpassenger", "sCity1", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Gen"));
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName1);
			SetFunctionTimerCondition("Marginpassenger_SouthshipInWorld", 0, 0, 5+rand(2), false);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

void SelectSouthshore()
{
	switch (rand(6))
	{
		case 0: pchar.GenQuest.Marginpassenger.Shore = "shore37"; break;
		case 1: pchar.GenQuest.Marginpassenger.Shore = "shore47"; break;
		case 2: pchar.GenQuest.Marginpassenger.Shore = "shore48"; break;
		case 3: pchar.GenQuest.Marginpassenger.Shore = "shore25"; break;
		case 4: pchar.GenQuest.Marginpassenger.Shore = "shore21"; break;
		case 5: pchar.GenQuest.Marginpassenger.Shore = "shore20"; break;
		case 6: pchar.GenQuest.Marginpassenger.Shore = "shore19"; break;
	}
}

void SelectSouthcity()
{
	switch (hrand(2))
	{
		case 0: 
			pchar.GenQuest.Marginpassenger.Southcity = "Maracaibo";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Havana"; 
		break;
		
		case 1:
			pchar.GenQuest.Marginpassenger.Southcity = "Cartahena";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santiago"; 
		break;
		
		case 2:
			pchar.GenQuest.Marginpassenger.Southcity = "Portobello";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santodomingo"; 
		break;
	}
}

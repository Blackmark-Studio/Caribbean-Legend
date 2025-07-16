//пассажир на доставку
void ProcessDialogEvent()
{
	ref NPChar, d;
	aref Link, Diag, arAll;
	string NPC_Meeting, sTemp, sTitle, sTavern;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		
		case "prepare_convoy_quest":
			if (isBadReputation(pchar, 40)) 
			{
				dialog.text = RandPhraseSimple("Ahhh, cholera! Wiem kim jesteś! Tylko kompletny idiota wsiadłby na twój statek jako pasażer! Żegnaj!","O, wiem kim jesteś! Nigdy nie postawię stopy na pokładzie twojego statku. Nie jestem głupcem...");
				link.l1 = RandPhraseSimple("Heh, co za tchórz!","Ludzie stali się takimi tchórzami w dzisiejszych czasach!");
				link.l1.go = "convoy_refused";
			}
			else
			{
				dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Jestem "+GetFullName(NPChar)+". Słyszałem, że bierzesz pasażerów?";
				link.l1 = "Być może. To zależy od mojego zysku.";
				link.l1.go = "prepare_convoy_quest_3";
			}
		break;
		
		case "prepare_convoy_quest_3":
			LookShipPassenger();
			GenerateConvoyPassengerQuest(npchar);
			dialog.text = "Muszę być dostarczony do tawerny "+XI_ConvertString("Kolonia"+npchar.GenQuest.GetPassenger_Destination+"Gen")+", że na "+XI_ConvertString(GetIslandByCityName(npchar.GenQuest.GetPassenger_Destination)+"To")+", dla "+FindRussianDaysString(sti(npchar.GenQuest.GetPassenger_Time))+", a za to zapłacę ci "+FindRussianMoneyString(sti(npchar.GenQuest.GetPassenger_Money))+". Czy zgadzasz się?";
			link.l1 = "Tak, robię.";
			link.l1.go = "convoy_agreeded";
			link.l2 = "Nie sądzę, żeby to była interesująca propozycja.";
			link.l2.go = "convoy_refused";
		break;
		
		case "convoy_refused":
			chrDisableReloadToLocation = false;
			sTemp = npchar.id + "_TimeOver";
			pchar.quest.(sTemp).over = "yes";
			sTemp = npchar.id + "_dead";
			pchar.quest.(sTemp).over = "yes";			
			DeleteAttribute(npchar, "GenQuest.GetPassenger");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		
		case "convoy_agreeded":
			sTitle = npchar.index + "convoy_passenger";
			AddQuestRecordEx(sTitle, "Gen_convoy_passenger", "1");
			sTemp = XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + ", which is on " + XI_ConvertString(GetIslandByCityName(npchar.GenQuest.GetPassenger_Destination) + "Dat") + ",";
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sDay", FindRussianDaysString(sti(npchar.GenQuest.GetPassenger_Time)));
            AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(npchar.GenQuest.GetPassenger_Money)));
            // по городу вернём его таверну
			sTavern = npchar.GenQuest.GetPassenger_Destination + "_tavern";
			sTemp = npchar.id + "_complited";
			pchar.quest.(sTemp).win_condition.l1 = "location";
			pchar.quest.(sTemp).win_condition.l1.location = sTavern;
			pchar.quest.(sTemp).win_condition = "AllPassangersComplited";	
			pchar.quest.(sTemp).Idx	= npchar.index; 
			if (rand(2) == 1) TraderHunterOnMap(false);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);			
			Diag.CurrentNode = "convoy_DeskTalk";
			DialogExit();
		break;
		
		case "complete_convoy_quest":
			dialog.text = "Dziękuję. Wypełniłeś swoje zobowiązania. Jestem w miejscu docelowym, oto twoja nagroda. Proszę.";
			Link.l1 = "Dziękuję.";
			link.l1.go = "complete_convoy_quest_1";
		break;

		case "complete_convoy_quest_1":
			//слухи
			AddSimpleRumour(LinkRandPhrase("One person by the name of " + GetFullName(npchar) + " says that captain " + GetMainCharacterNameDat() + " can be trusted, since "+ GetSexPhrase("he","she") +" had easily delivered him to " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + ".", 
				"Passenger named " + GetFullName(npchar) + " says that captain " + GetMainCharacterNameDat() + " can be trusted. "+ GetSexPhrase("He delivered","She delivered") +" him to " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + " absolutelly safely.", 
				"I heard that you are a captain who keeps his word given to passengers. Huckster named " + GetFullName(npchar) + " is giving high praises to you."), sti(npchar.nation), 40, 1);
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.ConvoyPassenger." + npchar.id); //извлекаем из структуры недовольных
			//--> смотрим Deck
    		makearef(arAll, pchar.GenQuest.ConvoyPassenger);
			if (GetAttributesNum(arAll) == 0) pchar.quest.ConvoyMapPassenger.over = "yes";
			//<-- смотрим Deck
			AddMoneyToCharacter(pchar, makeint(npchar.GenQuest.GetPassenger_Money));
			ChangeCharacterComplexReputation(pchar, "nobility",1);
			ChangeCharacterComplexReputation(pchar, "fame",1);
			RemovePassenger(PChar, npchar);
			OfficersReaction("good");						
			AddCharacterExpToSkill(pchar, "Sailing", 80);
			AddCharacterExpToSkill(pchar, "Leadership", 20);			
			sTitle = npchar.index + "convoy_passenger";
			AddQuestRecordEx(sTitle, "Gen_convoy_passenger", "4");			
            CloseQuestHeader(sTitle);	
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);	
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		
		case "convoy_DeskTalk":
			dialog.text = NPCStringReactionRepeat(LinkRandPhrase(RandSwear()+"Kapitanie, czas się skończył. Kiedy, do cholery, w końcu dostanę "+XI_ConvertString("Colony"+npchar.GenQuest.GetPassenger_Destination+"Acc")+"?",RandSwear()+"Kapitanie, jak długo jeszcze będziesz błąkać się Bóg wie gdzie?! Kiedy dotrzemy do "+XI_ConvertString("Kolonia"+npchar.GenQuest.GetPassenger_Destination+"Gen")+"?",RandSwear()+"Słuchaj, kapitanie, muszę dostać się do "+XI_ConvertString("Colonia"+npchar.GenQuest.GetPassenger_Destination+"Gen")+", i chcę dostać jasną i prostą odpowiedź, kiedy to nastąpi!"),RandPhraseSimple("Kapitanie, muszę ponownie otworzyć pytanie dotyczące twoich obowiązków. Kiedy dotrzemy do "+XI_ConvertString("Colonia"+npchar.GenQuest.GetPassenger_Destination+"Ogólny")+"?","Kapitanie, po raz drugi muszę poruszyć kwestię mojej podróży. Kiedy wreszcie ujrzymy wybrzeże "+XI_ConvertString("Kolonia"+npchar.GenQuest.GetPassenger_Destination+"Gen")+"?"),RandPhraseSimple(RandSwear()+"Kapitanie, pytam po raz trzeci - kiedy dotrzemy do "+XI_ConvertString("Kolonia"+npchar.GenQuest.GetPassenger_Destination+"Acc")+"?","Kapitanie, straciliśmy cholernie dużo czasu! Kiedy mnie zabierzesz do "+XI_ConvertString("Kolonia"+npchar.GenQuest.GetPassenger_Destination+"Acc")+"?"),"Słuchaj Kapitanie, to naprawdę za dużo!","block",0,npchar,Dialog.CurrentNode);
            if (sti(npchar.GenQuest.GetPassenger_Money) > 100)
            {
				link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Proszę, przepraszam, miałem tak wiele spraw do załatwienia... Za siedem dni na pewno będziesz tam, gdzie powinieneś być.","Przykro mi, "+GetAddress_Form(NPChar)+", naprawdę nie mogłem spełnić moich zobowiązań wobec ciebie. Ale nie martw się, dotrzemy za tydzień."),RandPhraseSimple("Muszę Ci jeszcze raz przeprosić. Dotrzemy do Twojego miejsca przeznaczenia za tydzień.","Ponownie przepraszam. Dotrzemy do twojego miejsca przeznaczenia za tydzień."),RandPhraseSimple("I znowu muszę prosić o twoje wybaczenie... Dotrzemy do twojego miejsca przeznaczenia za tydzień.","I znowu, przepraszam. Dotrzemy do twojego miejsca przeznaczenia za tydzień, obiecuję."),"Rozumiem, "+GetAddress_Form(NPChar)+", ale proszę, miej cierpliwość ... W ciągu najwyżej siedmiu dni dostarczę cię do miejsca docelowego!",npchar,Dialog.CurrentNode);
    			link.l1.go = "convoy_DeskTalk_1";
			}
			link.l2 = HeroStringReactionRepeat(RandPhraseSimple("Oh... pasażer... Zapomniałem o tobie... Myślę, że będzie ci wygodniej w ładowni, gdzie już nie będziesz mi dokuczać.","Cóż-cóż, nie mogę uwierzyć własnym oczom! Obcy jest na moim statku! Dobrze, to zamknij się i idź do mojego ładowni, teraz!"),"Po raz drugi? O, rzeczywiście... Ale wiesz, być może wyślę cię do ładowni na 'wycieczkę'.","Po raz trzeci? To naprawdę pechowe, he-he... No, kumple, witaj w moim ładowni. Nie powinieneś chodzić po pokładzie mojego statku i mi przeszkadzać.","Oh, rozumiem, to najwyższy stopień irytacji! Dobrze, dość tej farsy. Witaj w ładowni. "+GetAddress_Form(NPChar)+".",npchar,Dialog.CurrentNode);
			link.l2.go = "convoy_Prison_1";
			pchar.quest.Munity = "Deads"; //дверцы откроем
		break;
		
		case "convoy_DeskTalk_1":
			dialog.text = LinkRandPhrase("Dobrze, ale obniżę twoją zapłatę za opóźnienie.","Dobrze, postaram się ci uwierzyć... Ale pamiętaj, że obniżę twoją opłatę!","Cóż, nie mam dokąd iść, ale pamiętaj, że obniżę twoją wypłatę....");
			Link.l1 = LinkRandPhrase("W porządku.","Dobrze, w takim razie...","W porządku, jak mówisz.");
			link.l1.go = "convoy_DeskTalk_2";
		break;

		case "convoy_DeskTalk_2":
			dialog.text = RandPhraseSimple("Chciałbym wierzyć, że tym razem spełnisz swoje zobowiązania.","Mam nadzieję, że to nasza ostatnia rozmowa na ten nieprzyjemny temat.");
			Link.l1 = "Oczywiście.";
			link.l1.go = "convoy_DeskTalk_exit";
		break;

		case "convoy_DeskTalk_exit":
			DeleteAttribute(pchar, "GenQuest.ConvoyPassenger." + npchar.id); //извлекаем из структуры недовольных
			sTemp = npchar.id + "_TimeOver";
			SetTimerCondition(sTemp, 0, 0, 7, false);
			pchar.quest.(sTemp).win_condition              = "AllPassangersTimeOver";
			pchar.quest.(sTemp).Idx						   = npchar.index; 
			npchar.GenQuest.GetPassenger_Money = makeint(sti(npchar.GenQuest.GetPassenger_Money) / 1.5);			
			sTitle = npchar.index + "convoy_passenger";
			AddQuestRecordEx(sTitle, "Gen_convoy_passenger", "5");
			AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(npchar.GenQuest.GetPassenger_Money)));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 4.0);	
			Diag.CurrentNode = "convoy_DeskTalk";
			DialogExit();
		break;

		case "convoy_Prison_1":
			dialog.text = RandSwear()+"Jakie pomieszczenie ładunkowe? Nie rozumiem!";
			if (GetPrisonerQty() < PRISONER_MAX)
			{
    			Link.l1 = "I co jeszcze jest do zrozumienia? Od teraz jesteś moim więźniem! Do diabła z łapówką, ruszaj!";
    			link.l1.go = "convoy_Prison_2";
            }
			Link.l2 = "Tylko żart... Za siedem dni dotrzemy do twojego miasta.";
			link.l2.go = "convoy_DeskTalk_1";
		break;
		
		case "convoy_Prison_2":
			dialog.text = RandSwear()+"Zapłacisz za to, "+GetSexPhrase("szumowina","śmierdziel")+"!";
			Link.l1 = "Wszyscy tak mówią - ale na końcu wszyscy mi płacą!";
			link.l1.go = "convoy_Prison_3";
		break;
		
		case "convoy_Prison_3":
			AddSimpleRumour(LinkRandPhrase("It has been reported that a captain named " + GetFullName(pchar) + " obliged to deliver a passenger by the name of " + GetFullName(npchar) + ", but didn't stay true to "+ GetSexPhrase("his","her") +" word. Besides, "+ GetSexPhrase("he","she") +" imprisoned a poor guy. That's what happens when you trust strange people...", 
				"What's wrong with this world?! Captain " + GetFullName(pchar) + " imprisoned a poor guy by the name of " + GetFullName(npchar) + ", despite him being a passenger on his ship...", 
				"People say, captain, that you are "+ GetSexPhrase("a real scoundrel","a really vile bitch") +". They say that poor " + GetFullName(npchar) + " was taken prisoner on board your ship. And you promised to deliver him to " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + ". Very, very ugly ..."), sti(npchar.nation), 40, 1);
            RemovePassenger(PChar, NPChar);
        	LAi_SetActorType(NPChar);
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 5.0);
        	ChangeCharacterComplexReputation(pchar,"nobility", -5);
            OfficersReaction("bad");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(NPChar.nation)) + "hunter", GetIntByCondition(HasShipTrait(pchar, "trait23"), 10 + rand(10), 5 + rand(5)));// награда
			DeleteAttribute(pchar, "GenQuest.ConvoyPassenger." + npchar.id); //извлекаем из структуры недовольных
			sTemp = npchar.id + "_complited";
            pchar.quest.(sTemp).over = "yes";
			sTemp = npchar.id + "_dead";
			pchar.quest.(sTemp).over = "yes";
			sTemp = npchar.id + "_TimeOver";
			pchar.quest.(sTemp).over = "yes";
			sTitle = npchar.index + "convoy_passenger";
			AddQuestRecordEx(sTitle, "Gen_convoy_passenger", "6");			
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
            CloseQuestHeader(sTitle);			
			AddCharacterExpToSkill(pchar, "COMMERCE", 25);
            SetCharToPrisoner(NPChar);
        	DialogExit();
		break;
	}
} 

void GenerateConvoyPassengerQuest(ref npchar)
{
	int iTradeMoney, iNation, irank;
	string sTemp, sR;

	iNation = GetRelation2BaseNation(sti(npchar.nation)); //если привезти нужно во вражеский город
	npchar.GenQuest.GetPassenger_Destination = sGlobalTemp;
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.GetPassenger_City), GetArealByCityName(sGlobalTemp));
	if (sti(daysQty) > 14) daysQty = 14;
	npchar.GenQuest.GetPassenger_Time  = makeint(sti(daysQty)*(frand(1.3)+0.7));
	iTradeMoney = (sti(daysQty)*500*sti(pchar.GenQuest.GetPassenger.Shipmod)+rand(100))*sti(daysQty)/sti(npchar.GenQuest.GetPassenger_Time);
	if (iNation == RELATION_ENEMY && sti(npchar.nation != PIRATE)) iTradeMoney = makeint(iTradeMoney * 1.3); //то размер награды увеличивается
	npchar.GenQuest.GetPassenger_Money = iTradeMoney;

	//Log_Info(FindRussianDaysString(sti(daysQty)));
	//Log_Info(npchar.GenQuest.GetPassenger_Destination);
	//Log_Info(pchar.GenQuest.GetPassenger_City);
	

	sTemp = npchar.id + "_TimeOver";
	SetTimerCondition(sTemp, 0, 0, sti(npchar.GenQuest.GetPassenger_Time), false);
	pchar.quest.(sTemp).win_condition              = "AllPassangersTimeOver";
	pchar.quest.(sTemp).Idx						   = npchar.index; 

	sTemp = npchar.id + "_dead";
	pchar.quest.(sTemp).win_condition.l1           = "NPC_Death";
	pchar.quest.(sTemp).win_condition.l1.character = npchar.id;
	pchar.quest.(sTemp).win_condition              = "AllPassangersDead";
	pchar.quest.(sTemp).Idx						   = npchar.index; 	
}

void LookShipPassenger()
{
	switch(makeint(7-sti(RealShips[sti(Pchar.Ship.Type)].Class)))
	{
		case 0:
			pchar.GenQuest.GetPassenger.Shipmod = 0.8;
		break;
		case 1:
			pchar.GenQuest.GetPassenger.Shipmod = 1;
		break;
		case 2:
			pchar.GenQuest.GetPassenger.Shipmod = 1.2;
		break;
		case 3:
			pchar.GenQuest.GetPassenger.Shipmod = 1.5;
		break;
		case 4:
			pchar.GenQuest.GetPassenger.Shipmod = 2.2;
		break;
		case 5:
			pchar.GenQuest.GetPassenger.Shipmod = 3;
		break;
		case 6:
			pchar.GenQuest.GetPassenger.Shipmod = 3;
		break;
	}
}

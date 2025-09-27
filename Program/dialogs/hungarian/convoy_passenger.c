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
				dialog.text = RandPhraseSimple("Ahhh, a pokolba! Tudom, hogy ki vagy! Csak egy komplett idióta szállna fel a hajójára utasként! Viszontlátásra!", "Ó, tudom, hogy ki vagy! Soha nem teszem be a lábam a hajójára. Nem vagyok bolond...");
				link.l1 = RandPhraseSimple("Heh, micsoda gyáva!", "Az emberek manapság olyan gyávák lettek!");
				link.l1.go = "convoy_refused";
			}
			else
			{
				dialog.text = TimeGreeting() + ", "+GetAddress_Form(NPChar) + "! Én vagyok "+ GetFullName(NPChar) + ". Hallottam, hogy utasokat fogad?";
				link.l1 = "Talán. A nyereségemtôl függ.";
				link.l1.go = "prepare_convoy_quest_3";
			}
		break;
		
		case "prepare_convoy_quest_3":
			LookShipPassenger();
			GenerateConvoyPassengerQuest(npchar);
			dialog.text = "A " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + "kocsmába kell szállítani, hogy a " + XI_ConvertString(GetIslandByCityName(npchar.GenQuest.GetPassenger_Destination) + "Dat") +
                          ", a " + FindRussianDaysString(sti(npchar.GenQuest.GetPassenger_Time)) + ", és ezért fizetek neked " + FindRussianMoneyString(sti(npchar.GenQuest.GetPassenger_Money)) + ". Egyetértesz?";
			link.l1 = "Igen, egyetértek.";
			link.l1.go = "convoy_agreeded";
			link.l2 = "Nem hiszem, hogy ez egy érdekes ajánlat.";
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
			dialog.text = "Köszönöm. Köszönöm. Eleget tett a kötelezettségeinek. Elértem a célpontomat, itt a jutalmad. Tessék, tessék.";
			Link.l1 = "Köszönöm.";
			link.l1.go = "complete_convoy_quest_1";
		break;

		case "complete_convoy_quest_1":
			//слухи
			AddSimpleRumour(LinkRandPhrase("Egy " + GetFullName(npchar) + " nevû személy szerint a kapitány " + GetMainCharacterNameDat() + " megbízható, hiszen "+ GetSexPhrase("ô","ô") +" könnyen átadta ôt " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + ".", 
				"Utas nevû " + GetFullName(npchar) + " azt mondja, hogy a kapitány " + GetMainCharacterNameDat() + " megbízható. "+ GetSexPhrase("Ô szállította","Ô szállította") +" ôt " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + " abszolút biztonságban.", 
				"Hallottam, hogy ön olyan kapitány, aki betartja az utasoknak adott szavát. Huckster nevû " + GetFullName(npchar) + " nagy dicséretet mondott önnek."), sti(npchar.nation), 40, 1);
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
			dialog.text = NPCStringReactionRepeat(LinkRandPhrase(RandSwear() + "Kapitány, az idô lejárt. Mikor, a fenébe is, végre eljutok a " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Acc") + "?", 
						  RandSwear() + "Kapitány, meddig fogsz még bolyongani Isten tudja hol?! Mikor jutunk el a " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + "?" , 
						  RandSwear() + "Figyeljen, kapitány, el kell jutnom a " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + ", és világos és egyszerû választ akarok kapni, hogy ez mikor fog megtörténni!"), 
				RandPhraseSimple("Kapitány, ismét egy kérdést kell nyitnom a kötelezettségeivel kapcsolatban. Mikor jutunk el a " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + "?", "Kapitány úr, másodszor is fel kell tennem a kérdést az utazásommal kapcsolatban. Mikor fogjuk végre látni a " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + "partjait ?"), 
				RandPhraseSimple(RandSwear() + "Kapitány, harmadszorra kérdezem - mikor érünk el a " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Acc") + "?", "Kapitány, pokolian sok idôt vesztettünk! Mikor visznek el a " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Acc") + "?"), 
                "Figyeljen kapitány, ez tényleg túl sok!", "block", 0, npchar, Dialog.CurrentNode);
            if (sti(npchar.GenQuest.GetPassenger_Money) > 100)
            {
				link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Kérem, bocsánat, annyi dolgom volt... Hét nap múlva biztosan ott leszel, ahol lenned kell.", "Sajnálom, " + GetAddress_Form(NPChar) + ", tényleg nem tudtam eleget tenni a kötelezettségeimnek veled szemben. De ne aggódj, egy hét múlva megérkezünk."),
					RandPhraseSimple("Még egyszer elnézést kell kérnem tôled. Egy hét múlva megérkezünk a célállomásra.", "Még egyszer elnézést kérek. Egy hét múlva megérkezünk a célállomásra."),
					RandPhraseSimple("És még egyszer bocsánatot kell kérnem... Egy hét múlva érkezünk a célállomásra.", "És még egyszer sajnálom. Egy hét múlva megérkezünk a célállomásra, ígérem."),
					"Megértem, " + GetAddress_Form(NPChar) + ", de kérem, legyen türelemmel... Legfeljebb hét nap múlva el fogom szállítani a célpontra!", npchar, Dialog.CurrentNode);
    			link.l1.go = "convoy_DeskTalk_1";
			}
			link.l2 = HeroStringReactionRepeat(RandPhraseSimple("Ó... egy utas... Megfeledkeztem rólad... Azt hiszem, kényelmesebb lesz a raktérben, ahol nem fogsz többé zaklatni engem.", "Nos- nos, nem hiszek a saját szememnek! Idegen van a hajómon! Rendben, akkor fogd be a szád és menj a raktérbe, most!"),
				"Már másodszor? Ó, valóban... De tudod, lehet, hogy elküldelek a raktérbe egy 'exkurzióra'.",
				"harmadszorra? Ez nagyon rossz, he-he-he... Nos, haver, üdvözöllek a fogdámban. Nem kellett volna a hajóm fedélzetén mászkálnod és zaklatnod engem.",
				"Ó, értem, ez az ingerültség legmagasabb foka! Rendben, elég ebbôl a színjátékból. Üdvözöljük a raktérben. " + GetAddress_Form(NPChar) + ".", npchar, Dialog.CurrentNode);
			link.l2.go = "convoy_Prison_1";
			pchar.quest.Munity = "Deads"; //дверцы откроем
		break;
		
		case "convoy_DeskTalk_1":
			dialog.text = LinkRandPhrase("Rendben, de a késedelem miatt csökkentem a fizetését.", "Rendben, megpróbálok hinni neked... De ne feledd, hogy csökkenteni fogom a díjadat!", "Nos, úgysem tudok hova menni, de ne feledje, hogy csökkenteni fogom a fizetését....");
			Link.l1 = LinkRandPhrase("Jól van, rendben.", "Rendben, akkor...", "Rendben, ahogy mondod.");
			link.l1.go = "convoy_DeskTalk_2";
		break;

		case "convoy_DeskTalk_2":
			dialog.text = RandPhraseSimple("Szeretném hinni, hogy ezúttal eleget fog tenni a kötelezettségeinek.", "Remélem, hogy ez volt az utolsó beszélgetésünk errôl a kellemetlen témáról.");
			Link.l1 = "Hát persze.";
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
			dialog.text = RandSwear() + "Melyik tartás? Nem értem!";
			if (GetPrisonerQty() < PRISONER_MAX)
			{
    			Link.l1 = "És mit kell még megérteni? Mostantól kezdve a foglyom vagy! Menj az istenverte raktérbe, mozgás!";
    			link.l1.go = "convoy_Prison_2";
            }
			Link.l2 = "Csak vicceltem... Hét nap múlva megérkezünk a városodba.";
			link.l2.go = "convoy_DeskTalk_1";
		break;
		
		case "convoy_Prison_2":
			dialog.text = RandSwear() + "Ezért megfizetsz, "+ GetSexPhrase("söpredék","büdös") +"!";
			Link.l1 = "Mindenki ezt mondja - de a végén mindannyian fizetnek nekem!";
			link.l1.go = "convoy_Prison_3";
		break;
		
		case "convoy_Prison_3":
			AddSimpleRumour(LinkRandPhrase("Arról számoltak be, hogy egy " + GetFullName(pchar) + " nevû kapitány kötelezte magát, hogy leszállítja egy " + GetFullName(npchar) + "nevû utast, de nem maradt hû "+ GetSexPhrase("a","szavához") +" . Emellett "+ GetSexPhrase("ô","ô") +" bebörtönzött egy szerencsétlent. Ez történik, ha idegen emberekben bízol...", 
				"Mi a baj ezzel a világgal?! A kapitány " + GetFullName(pchar) + " bebörtönzött egy szegény fickót, akit " + GetFullName(npchar) + "hívnak, annak ellenére, hogy a hajójának utasa volt...", 
				"Az emberek azt mondják, kapitány, hogy maga "+ GetSexPhrase("egy igazi gazember","egy igazán aljas szuka") +". Azt mondják, hogy szegény " + GetFullName(npchar) + " fogságba esett a hajóján. És te megígérted, hogy átadod ôt " + XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen") + ". Nagyon, nagyon csúnya ..."), sti(npchar.nation), 40, 1);
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

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, arRld, arDis;
	int i, Qty;

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

		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//--------------------------------- леди в резиденции ---------------------------------
		case "ResWoman":
			NextDiag.TempNode = "ResWoman";
			if (LAi_grp_playeralarm <= 0 && CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2.Done") && !CheckAttribute(npchar, "quest.chickengod") && sti(npchar.nation) == SPAIN) {
				link.chickengod = "Senora, kérem, bocsásson meg, de megkértek, hogy mondjam el, hogy van... egy randi egy régi pogány piramisban.";
				link.chickengod.go = "chickengod";
			}
			if (isBadReputation(pchar, 30))
			{
				dialog.text = LinkRandPhrase("Jézusom! Egy ilyen aljas ember a szobámban! Takarodj innen, vagy hívom az ôrséget!", "Ez nem történhet meg... Ki engedte be ezt a patkányt a házamba? Takarodj innen te szemétláda! Nincs itt semmi keresnivalód! Takarodj innen!", "Ilyen furcsa idôk járnak. Patkányok jutnak be a hálószobámba! Menjetek innen!");
				link.l1 = RandPhraseSimple("Nyugalom...", "Vigyázz a szádra...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Mit csinálsz a hálószobámban? Tûnj innen!", "Micsoda szégyen! Megkérem, hogy azonnal hagyja el ezt a helyet!", "Elnézést, uram, de önt nem hívták ide. Kérem, hagyja el a szobámat!");
				link.l1 = RandPhraseSimple("Bocsásson meg... Elmegyek.", "Bocsánat, rossz ajtó. Mennem kell.");
				link.l1.go = "exit";
			}
		break;
		case "Woman_FackYou":
			dialog.text = "Ó, mi volt ez?! Mekkora egy bolond vagyok! Körbesétáltam, nem láttam semmit... Ôrök!!!";
			link.l1 = "Pofa be!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		//--------------------------------- слуга в резиденции ---------------------------------
		case "ResMan":
			NextDiag.TempNode = "ResMan";
			if (isBadReputation(pchar, 30))
			{
				dialog.text = LinkRandPhrase("Tûnj innen, patkány!", "Tûnj el a kormányzó birtokáról azonnal, patkány!", "Nem érdekel, hogy mit csinálsz a kormányzó otthonában " + XI_ConvertString("Colony" + npchar.city + "Gen") + "De azt tanácsolom, hogy tûnj el, most azonnal!");
				link.l1 = RandPhraseSimple("Csak nyugodtan, haver...", "Vigyázz a szavaidra!");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Üdvözletem! A kormányzó szolgája vagyok. A nevem " + GetFullName(NPChar) + ".", "ôrzöm ezt a helyet, " + GetAddress_Form(NPChar) + ".", "Tudod, " + GetAddress_Form(NPChar) + ", a kormányzó jó ember, és jól megfizet minket...");
				link.l1 = RandPhraseSimple("Szép.", "Hm, nagyon jó...");
				link.l1.go = "exit";
			}
		break;
		case "Man_FackYou":
			dialog.text = "Szóval úgy döntöttél, hogy kirabolod a kormányzót?! Ôrök, kapjátok el a tolvajt!!";
			link.l1 = "Fogd be a szád!";
			link.l1.go = "fight";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		//--------------------------------- солдат в резиденции ---------------------------------
		case "ResGuard":
			NextDiag.TempNode = "ResGuard";
			if (isBadReputation(pchar, 30))
			{
				dialog.text = LinkRandPhrase("Jobb, ha eltûnsz innen, "+ GetSexPhrase("haver","lány") +"...", "Menj el!", "elhibáztad az ajtót, "+ GetSexPhrase("haver","lány") +"? ? Ez a birtok a kormányzóé " + XI_ConvertString("Colony" + npchar.city + "Gen") + ".");
				link.l1 = RandPhraseSimple("Akkor megyek el, amikor akarok!", "Nem a te dolgod...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Ma parancsot kaptam, hogy itt szolgáljak. Szép hely...", "A " + GetAddress_Form(NPChar) + "birtokát védem.", "A parancsom az, hogy védjem a kormányzó birtokát.");
				link.l1 = RandPhraseSimple("Akkor sok szerencsét...", "Hmm, értem...");
				link.l1.go = "exit";
			}
		break;
		
		case "chickengod":
			pchar.questTemp.ChickenGod.Tasks.o2.Counter = sti(pchar.questTemp.ChickenGod.Tasks.o2.Counter) + 1;
			if (sti(pchar.questTemp.ChickenGod.Tasks.o2.Counter) >= 3) {
				dialog.text = "Ah, igen. Végre! Készen állok, hogy veled menjek, kapitány.";
				link.l1 = "Csak így? Senora, biztos, hogy ezt akarja?";
				link.l1.go = "chickengod_accept";
			} else {
				sld = CharacterFromID(npchar.city + "_Mayor");
				dialog.text = "Mi?! Részeg vagy, senor? Micsoda idióta vicc! Kérem, menjen el, könyörgöm! " + sld.name + "! Ôrség! Segítség!";
				link.l1 = "A francba, ideje menni.";
				link.l1.go = "chickengod_decline";
			}
			npchar.quest.chickengod = true;
		break;
		
		case "chickengod_accept":
			dialog.text = "Hát persze! Á, Senor Aruba és én már régóta levelezô kapcsolatban állunk!";
			link.l1 = "Ha már így alakult, kérem, jöjjön a fedélzetre!";
			link.l1.go = "chickengod_accept_take";
			link.l2 = "Nem, senora, ez nem fog menni. A becsületem nem engedi, hogy egy nôt veszélybe sodorjanak, és önt nyilvánvalóan félrevezették!";
			link.l2.go = "chickengod_accept_nottake";
		break;
		
		case "chickengod_accept_take":
			DialogExit();
			
			pchar.questTemp.ChickenGod.Tasks.o2.Done = true;
			pchar.questTemp.ChickenGod.Tasks.o2.Lady = npchar.id;
			AddDialogExitQuestFunction("ChickenGod_TakeLady");
		break;
		
		case "chickengod_accept_nottake":
			dialog.text = "Ebben az esetben, kedves kapitányom, fogja a vidéki becsületérzetét és dugja fel a seggébe! Várok egy másik hírvivôre, aki nem olyan szûklátókörû, mint maga!";
			link.l1 = "Elbûvölô!";
			link.l1.go = "exit";
			
			pchar.questTemp.ChickenGod.Tasks.o2.Done = true;
			SetFunctionTimerCondition("ChickenGod_NotTakeLadyConsequence", 0, 1, 0, false);
		break;
		
		case "chickengod_decline":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_LadyRefuse");
		break;
		
	}
}

void ProcessDialogEvent()
{	
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iRank, iMassive;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{		
		case "exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":
			dialog.text = LinkRandPhrase("O mój Panie, tak się cieszę, że cię spotkałem!","Wreszcie ktoś!","O mój Boże, jak się cieszę, że cię widzę!");
			Link.l1 = LinkRandPhrase("Co u ciebie, kochanie?","Jakieś problemy, kochanie?","Nie denerwuj się tak - to nie jest dobre dla zdrowia młodej damy. Teraz, po prostu mi powiedz - co się stało?");
			Link.l1.go = "Step_1";
		break;
		case "Step_1":
			dialog.text = LinkRandPhrase("Mój przyjaciel... ona jest taka odważna... weszła do opuszczonej studni!","Mój przyjaciel zszedł do opuszczonej studni i nadal nie wyszedł! Spędziła tam kilka godzin!","Mój przyjaciel właśnie zniknął w opuszczonym studni!");
			Link.l1 = "I dlaczego do diabła ona tam weszła?!";
			Link.l1.go = "Step_2";
		break;
		case "Step_2":
			dialog.text = "Och, wiesz, boi się absolutnie wszystkiego! Słyszała, że jest tam loch pełen złota, więc poszła tam... Ale ja nie jestem głupcem, nawet bym o tym nie pomyślał!";
			Link.l1 = "To prawda, nie ma dla ciebie nic do roboty w takim miejscu.";
			Link.l1.go = "Step_3";
		break;		
		case "Step_3":
			dialog.text = "Ale co teraz mam robić? Proszę, pomóż jej, na miłość boską!";
			Link.l1 = "Dobrze, wymyślę coś. A ty lepiej idź do domu, tutaj nie ma dla ciebie nic do roboty.";
			Link.l1.go = "Step_agree";
			Link.l2 = "To twoje problemy, nie chcę marnować swojego czasu. Żegnaj...";
			Link.l2.go = "Step_disAgree";
		break;

		case "Step_agree":
			pchar.quest.Enc_FriendGirl_after.over = "yes";
			if (rand(1))
			{ //бандюганы
				LAi_LocationDisableMonGenTimer(pchar.GenQuest.EncGirlF.locationId, 1); //монстров не генерить 1 день
				LAi_LocationDisableOffGenTimer(pchar.GenQuest.EncGirlF.locationId, 1); //офицеров не пускать 1 день
				LocatorReloadEnterDisable(pchar.GenQuest.EncGirlF.locationId, "reload2", true);
				pchar.GenQuest.OpenTheRopeExit = pchar.GenQuest.EncGirlF.locationId; //флаг для открытия релоада
				string model[10];
				model[0] = "citiz_41";
				model[1] = "citiz_42";
				model[2] = "citiz_43";
				model[3] = "citiz_44";
				model[4] = "citiz_45";
				model[5] = "citiz_46";
				model[6] = "citiz_47";
				model[7] = "citiz_48";
				model[8] = "citiz_49";
				model[9] = "citiz_50";
				i = 0;
				while(i < 3)
				{
					iMassive = rand(9);
					if (model[iMassive] != "")
					{
						iRank = sti(pchar.rank) - rand(5) + rand(5);
						if (iRank < 1) iRank = 1; 
						sld = GetCharacter(NPC_GenerateCharacter("CaveGandMan" + i, model[iMassive], "man", "man", iRank, PIRATE, 1, true, "marginal"));
						SetFantomParamFromRank(sld, iRank, true);
						sld.SaveItemsForDead = true;
						sld.DontClearDead = true; 
						LAi_CharacterDisableDialog(sld);
						sld.money = iRank*200+1000+rand(500);
						LAi_SetWarriorType(sld);
						LAi_warrior_SetStay(sld, true);
						//LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
						LAi_group_MoveCharacter(sld, LAI_GROUP_ENEMY);// лесник изменил группу чтобы ядом таино травить можно было
						LAi_group_Attack(sld, Pchar);// лесник добавил атаку на пчара а то у некоторых баг что они не нападают.
						ChangeCharacterAddressGroup(sld, pchar.GenQuest.EncGirlF.locationId, "quest", "quest" + i);
						i++;
						model[iMassive] = "";	
					}
				}
			}
			else
			{ //и правда девка 
				sld = GetCharacter(NPC_GenerateCharacter("UndergroundGirl", "women_"+(rand(5)+11), "woman", "towngirl", 5, PIRATE, 1, false, "citizen"));
				sld.dialog.filename = "Enc_FriendGirl_dialog.c";
				int iTemp = rand(1);
				sld.dialog.currentnode = "Underground"+ iTemp; //здесь рендом поведения девки: 0-помогите, 1-сама крутая// лесник - раскоментил itemp
				sld.greeting = "Enc_RapersGirl_" + (iTemp+1); //соотв. озвучка
			   // LAi_SetStayType(sld);
				LAi_SetCitizenType(sld);// чтоб ходила по пещере. лесник
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				GetCharacterPos(pchar, &locx, &locy, &locz); // и ниже - ищем ближейший локатор лесник.
	            ChangeCharacterAddressGroup(sld, pchar.GenQuest.EncGirlF.locationId, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			}
			LAi_SetActorTypeNoGroup(npchar);
            LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Step_disAgree":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			LAi_SetCitizenTypeNoGroup(npchar);
			pchar.quest.Enc_FriendGirl_after.over = "yes";
			NextDiag.CurrentNode = "FackYou";
			DialogExit();
		break;			
		case "FackYou":
            NextDiag.TempNode = "FackYou";
            dialog.text = "Nie chcę rozmawiać z takim bezdusznym "+GetSexPhrase("skrzep","dziewczyna")+". Spadaj!";
			Link.l1 = "Heh, jaka suka...";
			Link.l1.go = "exit";
		break;

		case "Underground0": //девка реально заблудилась
            dialog.text = "O mój Boże, tak się cieszę, że cię widzę!";
			Link.l1 = "Co u ciebie słychać, piękności?";
			Link.l1.go = "Underground0_1";
		break;
		case "Underground0_1": 
            dialog.text = "Zgubiłem się tutaj! O mój Boże, tak bardzo się boję!!!";
			Link.l1 = "Cóż, teraz jesteś w porządku. Idź za mną, pokażę ci drogę. Gdy tylko będziesz na powierzchni, biegnij do domu i módl się, żeby nigdy więcej cię tutaj nie widzieć!";
			Link.l1.go = "Underground0_2";
		break;
		case "Underground0_2": 
            dialog.text = "Jak mówisz, "+GetAddress_Form(NPChar)+".";
			Link.l1 = "Dobrze.";
			Link.l1.go = "exit";
			npchar.LifeDay = 0;
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			ChangeCharacterComplexReputation(pchar,"nobility", 4);
		break;

		case "Underground1": //крутая мочалка
            dialog.text = "Wow, wygląda na to, że ktoś inny zainteresował się tą loch!";
			Link.l1 = "Piękno, co tutaj robisz?";
			Link.l1.go = "Underground1_1";
		break;
		case "Underground1_1": 
            dialog.text = "To nie twoja sprawa!";
			Link.l1 = "O rany, to odpowiedź za milion pesos...";
			Link.l1.go = "Underground1_2";
		break;
		case "Underground1_2": 
            dialog.text = "Za dwa miliony. Po prostu pójdź swoją drogą? Nie obchodzi mnie ciebie.";
			Link.l1 = "Cóż, uczucie jest wzajemne, ale twój przyjaciel z góry niezmiernie się o ciebie martwił...";
			Link.l1.go = "Underground1_3";
		break;
		case "Underground1_3": 
            dialog.text = "Co za głupiec! Ona by się posikała ze strachu, a myśli, że jestem taki sam jak ona.";
			Link.l1 = "Oj, na pewno jej nie lubisz. Diabeł w spódnicy - to ty jesteś.";
			Link.l1.go = "Underground1_4";
		break;
		case "Underground1_4": 
            dialog.text = "Hej, wybieraj słowa! A jeszcze lepiej, po prostu spadaj.";
			Link.l1 = "No cóż, jeśli nie potrzebujesz mojej pomocy...";
			Link.l1.go = "Underground1_5";
		break;
		case "Underground1_5": 
            dialog.text = "Nie, nie robię!";
			Link.l1 = "W takim razie żegnaj i powodzenia.";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Underground1_again";
		break;
		case "Underground1_again": 
            dialog.text = "Znowu ty? Spadaj, nie chcę cię więcej widzieć...";
			Link.l1 = "Hmm...";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Underground1_again";
		break;

	}
}

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
			dialog.text = LinkRandPhrase("Ó, Uram, annyira örülök, hogy találkoztam veled!",
				"Végre valaki!",
				"Ó, Istenem, annyira örülök, hogy látlak!");
			Link.l1 = LinkRandPhrase("Mi a helyzet, bébi?",
				"Valami gond van, drágám?",
				"Ne izgulj ennyire - nem tesz jót a fiatal hölgy egészségének. Csak mondd el, mi történt?");
			Link.l1.go = "Step_1";
		break;
		case "Step_1":
			dialog.text = LinkRandPhrase("A barátom... olyan bátor... egy elhagyott kútba szállt be!",
				"A barátnôm egy elhagyatott kútba esett, és még mindig nem jött ki onnan! Több órát töltött ott!",
				"A barátom most tûnt el egy elhagyatott kútban!");
			Link.l1 = "És mi a fenéért került oda?!";
			Link.l1.go = "Step_2";
		break;
		case "Step_2":
			dialog.text = "Ó, tudod, ô mindentôl fél! Azt hallotta, hogy van ott egy börtön tele arannyal, ezért lement oda... De én nem vagyok bolond, eszembe sem jutna!";
			Link.l1 = "Így van, egy ilyen helyen nincs mit tenni.";
			Link.l1.go = "Step_3";
		break;		
		case "Step_3":
			dialog.text = "De most mit kellene tennem? Kérem, segítsen neki, az ég szerelmére!";
			Link.l1 = "Rendben, majd kitalálom. És jobb, ha hazamész, itt nincs semmi keresnivalód.";
			Link.l1.go = "Step_agree";
			Link.l2 = "Ezek a te problémáid, nem akarom az idômet vesztegetni. Viszontlátásra...";
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
            dialog.text = "Nem akarok beszélgetni egy ilyen érzéketlen "+ GetSexPhrase("röggel","szajhával") +". Tûnj el!";
			Link.l1 = "Heh, micsoda kurva...";
			Link.l1.go = "exit";
		break;

		case "Underground0": //девка реально заблудилась
            dialog.text = "Ó, Istenem, annyira örülök, hogy látlak!";
			Link.l1 = "Mi a helyzet, szépségem?";
			Link.l1.go = "Underground0_1";
		break;
		case "Underground0_1": 
            dialog.text = "Eltévedtem itt! Istenem, de meg vagyok rémülve!!!";
			Link.l1 = "Hát, most már jól vagy. Kövess engem, megmutatom az utat. Ha már a felszínen vagy, szaladj haza, és imádkozz, hogy soha többé ne lássalak itt!";
			Link.l1.go = "Underground0_2";
		break;
		case "Underground0_2": 
            dialog.text = "Ahogy mondod, " + GetAddress_Form(NPChar) + ".";
			Link.l1 = "Rendben.";
			Link.l1.go = "exit";
			npchar.LifeDay = 0;
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			ChangeCharacterComplexReputation(pchar,"nobility", 4);
		break;

		case "Underground1": //крутая мочалка
            dialog.text = "Wow, úgy tûnik, hogy valaki más is érdeklôdik a börtön iránt!";
			Link.l1 = "Szépség, mit keresel itt?";
			Link.l1.go = "Underground1_1";
		break;
		case "Underground1_1": 
            dialog.text = "Semmi közöd hozzá!";
			Link.l1 = "Hû, ez egy válasz egy millió pezóért...";
			Link.l1.go = "Underground1_2";
		break;
		case "Underground1_2": 
            dialog.text = "Kétmillióért. Elmész a saját utadon? Egyáltalán nem érdekelsz.";
			Link.l1 = "Nos, az érzés kölcsönös, de a barátod odafent betegre aggódta magát...";
			Link.l1.go = "Underground1_3";
		break;
		case "Underground1_3": 
            dialog.text = "Micsoda bolond! Összeszarta magát a rémülettôl, és azt hiszi, hogy én is ugyanolyan vagyok, mint ô.";
			Link.l1 = "Hû, te biztosan nem kedveled ôt. Az ördög szoknyában - ez vagy te.";
			Link.l1.go = "Underground1_4";
		break;
		case "Underground1_4": 
            dialog.text = "Hé, válogasd meg a szavaid! És még jobb lenne, ha eltûnnél.";
			Link.l1 = "Nos, ha nincs szükséged a segítségemre...";
			Link.l1.go = "Underground1_5";
		break;
		case "Underground1_5": 
            dialog.text = "Nem, nem kell!";
			Link.l1 = "Akkor viszlát és sok szerencsét.";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Underground1_again";
		break;
		case "Underground1_again": 
            dialog.text = "Már megint te? Tûnj el, nem akarlak többé látni...";
			Link.l1 = "Hmm...";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Underground1_again";
		break;

	}
}

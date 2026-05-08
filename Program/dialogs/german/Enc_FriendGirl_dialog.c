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
			dialog.text = LinkRandPhrase("Oh mein Herr, ich bin so froh, dass ich Sie getroffen habe!","Endlich jemand!","Oh mein Gott, ich bin so froh, dich zu sehen!");
			Link.l1 = LinkRandPhrase("Was ist los, Liebling?","Gibt es Probleme, Liebling?","Regen Sie sich nicht so auf - das ist nicht gut für die Gesundheit einer jungen Dame. Jetzt erzählen Sie mir einfach - was ist passiert?");
			Link.l1.go = "Step_1";
		break;
		case "Step_1":
			dialog.text = LinkRandPhrase("Mein Freund... sie ist so mutig... sie ist in einen verlassenen Brunnen gestiegen!","Mein Freund ist in einen verlassenen Brunnen hinabgestiegen, und sie ist immer noch nicht herausgekommen! Sie hat dort mehrere Stunden verbracht!","Mein Freund ist gerade in einem verlassenen Brunnen verschwunden!");
			Link.l1 = "Und warum zum Teufel ist sie da rein gekommen?!";
			Link.l1.go = "Step_2";
		break;
		case "Step_2":
			dialog.text = "Oh, du weißt, sie fürchtet absolut alles! Sie hörte, dass es einen Dungeon voller Gold gab, also ging sie hinunter... Aber ich bin kein Narr, ich würde nicht einmal daran denken!";
			Link.l1 = "Das stimmt, es gibt nichts für dich zu tun an so einem Ort.";
			Link.l1.go = "Step_3";
		break;		
		case "Step_3":
			dialog.text = "Aber was soll ich jetzt tun? Bitte, helft ihr, um Himmels willen!";
			Link.l1 = "Also gut, ich werde es herausfinden. Und du solltest besser nach Hause gehen, hier gibt es nichts für dich zu tun.";
			Link.l1.go = "Step_agree";
			Link.l2 = "Das sind deine Probleme, ich will meine Zeit nicht verschwenden. Lebewohl...";
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
            dialog.text = "Ich will nicht mit so einem gefühllosen reden "+GetSexPhrase("Trottel","Dirne")+". Verpiss dich!";
			Link.l1 = "Heh, was für eine Zicke...";
			Link.l1.go = "exit";
		break;

		case "Underground0": //девка реально заблудилась
            dialog.text = "Oh mein Gott, ich bin so froh dich zu sehen!";
			Link.l1 = "Was ist los, Schönheit?";
			Link.l1.go = "Underground0_1";
		break;
		case "Underground0_1": 
            dialog.text = "Ich habe mich hier verloren! Oh mein Gott, ich habe so schreckliche Angst!!!";
			Link.l1 = "Nun, dir geht es jetzt gut. Folge mir, ich zeige dir den Weg. Sobald du an der Oberfläche bist, renne nach Hause und bete, dass ich dich hier nie wieder sehe!";
			Link.l1.go = "Underground0_2";
		break;
		case "Underground0_2": 
            dialog.text = "Wie du sagst, "+GetAddress_Form(NPChar)+".";
			Link.l1 = "Gut.";
			Link.l1.go = "exit";
			npchar.LifeDay = 0;
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			ChangeCharacterComplexReputation(pchar,"nobility", 4);
		break;

		case "Underground1": //крутая мочалка
            dialog.text = "Wow, es scheint, dass jemand anderes Interesse an diesem Verlies gefunden hat!";
			Link.l1 = "Schönheit, was machst du hier?";
			Link.l1.go = "Underground1_1";
		break;
		case "Underground1_1": 
            dialog.text = "Das geht dich nichts an!";
			Link.l1 = "Wahnsinn, das ist eine Antwort für eine Million Pesos...";
			Link.l1.go = "Underground1_2";
		break;
		case "Underground1_2": 
            dialog.text = "Für zwei Millionen. Gehst du einfach deinen eigenen Weg? Du könntest mir nicht egaler sein.";
			Link.l1 = "Nun, das Gefühl ist gegenseitig, aber dein Freund da oben hat sich krank vor Sorge um dich gemacht...";
			Link.l1.go = "Underground1_3";
		break;
		case "Underground1_3": 
            dialog.text = "Was für ein Narr! Sie würde sich vor Schreck in die Hosen scheißen, und sie denkt, dass ich genauso bin wie sie.";
			Link.l1 = "Wow, du magst sie sicherlich nicht. Der Teufel im Rock - das bist du.";
			Link.l1.go = "Underground1_4";
		break;
		case "Underground1_4": 
            dialog.text = "He, wähle deine Worte! Und noch besser, verschwinde einfach.";
			Link.l1 = "Nun, wenn du meine Hilfe nicht brauchst...";
			Link.l1.go = "Underground1_5";
		break;
		case "Underground1_5": 
            dialog.text = "Nein, ich tue es nicht!";
			Link.l1 = "Dann Lebewohl und viel Glück für dich.";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Underground1_again";
		break;
		case "Underground1_again": 
            dialog.text = "Du schon wieder? Verschwinde, ich will dich nicht mehr sehen...";
			Link.l1 = "Hmm...";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Underground1_again";
		break;

	}
}

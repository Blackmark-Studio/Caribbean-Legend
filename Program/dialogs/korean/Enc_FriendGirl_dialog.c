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
			dialog.text = LinkRandPhrase("오, 나리, 이렇게 만나 뵙게 되어 정말 기쁩니다!","드디어, 누가 왔군!","오, 맙소사, 이렇게 다시 만나서 정말 기뻐요!");
			Link.l1 = LinkRandPhrase("무슨 일이야, 자기야?","문제 있어, 자기야?","그렇게 흥분하지 마시오 - 젊은 아가씨 건강에 좋지 않으니. 자, 이제 말해보시오 - 무슨 일이 있었소?");
			Link.l1.go = "Step_1";
		break;
		case "Step_1":
			dialog.text = LinkRandPhrase("내 친구가... 정말 용감해... 버려진 우물 속으로 내려갔어!","내 친구가 버려진 우물 안으로 내려갔는데, 아직도 안 나왔어! 몇 시간째 거기 있어!","내 친구가 방치된 우물에서 막 사라졌어!");
			Link.l1 = "도대체 왜 그녀가 거기로 들어간 거야?!";
			Link.l1.go = "Step_2";
		break;
		case "Step_2":
			dialog.text = "아, 있잖아, 걔는 뭐든 다 무서워해! 금으로 가득 찬 지하 감옥이 있다는 소문을 듣고 거기로 내려갔지... 하지만 나는 바보가 아니야, 그런 건 생각도 안 해!";
			Link.l1 = "그래, 이런 곳에서는 네가 할 일이 없어.";
			Link.l1.go = "Step_3";
		break;		
		case "Step_3":
			dialog.text = "하지만 이제 나는 어떻게 해야 하지? 제발, 하늘에 맹세코 그녀를 도와줘!";
			Link.l1 = "알겠어, 내가 알아서 할게. 그리고 너는 집에 가는 게 좋겠어, 여기서 네가 할 일은 없어.";
			Link.l1.go = "Step_agree";
			Link.l2 = "이건 네 문제야, 내 시간 낭비하고 싶지 않다. 잘 있어라...";
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
            dialog.text = "그렇게 냉정한 사람하고는 말하고 싶지 않아 "+GetSexPhrase("피떡","계집")+". 꺼져!";
			Link.l1 = "헤, 진짜 싸가지 없는 년이네...";
			Link.l1.go = "exit";
		break;

		case "Underground0": //девка реально заблудилась
            dialog.text = "맙소사, 이렇게 다시 만나서 정말 기뻐!";
			Link.l1 = "무슨 일이야, 이쁜이?";
			Link.l1.go = "Underground0_1";
		break;
		case "Underground0_1": 
            dialog.text = "여기서 길을 잃었어! 아이고 맙소사, 나 정말 너무 무서워!!!";
			Link.l1 = "이제 괜찮으니 따라와. 내가 길을 알려주지. 지상에 올라가면 곧장 집으로 달려가고, 다시는 여기서 너를 보지 않게 기도해!";
			Link.l1.go = "Underground0_2";
		break;
		case "Underground0_2": 
            dialog.text = "말씀대로 하겠습니다, "+GetAddress_Form(NPChar)+".";
			Link.l1 = "좋아.";
			Link.l1.go = "exit";
			npchar.LifeDay = 0;
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			ChangeCharacterComplexReputation(pchar,"nobility", 4);
		break;

		case "Underground1": //крутая мочалка
            dialog.text = "이런 젠장, 누군가 이 던전에 관심을 가진 것 같군!";
			Link.l1 = "아가씨, 여기서 뭐 하고 있어?";
			Link.l1.go = "Underground1_1";
		break;
		case "Underground1_1": 
            dialog.text = "네 알 바 아니야!";
			Link.l1 = "이런 젠장, 그건 백만 페소짜리 대답이군...";
			Link.l1.go = "Underground1_2";
		break;
		case "Underground1_2": 
            dialog.text = "이백만을 위해서라면. 그냥 네 갈 길 가라. 난 네가 뭐하든 신경도 안 써.";
			Link.l1 = "글쎄, 나도 같은 마음이지만, 위층에 있는 네 친구가 너 걱정에 아주 애가 타더라...";
			Link.l1.go = "Underground1_3";
		break;
		case "Underground1_3": 
            dialog.text = "정말 바보 같군! 걔는 겁에 질려서 똥이라도 쌀 텐데, 나도 자기랑 똑같다고 생각하다니.";
			Link.l1 = "이런 젠장, 넌 정말 그녀를 싫어하는구나. 치마 입은 악마라니, 딱 너한테 어울리는 말이야.";
			Link.l1.go = "Underground1_4";
		break;
		case "Underground1_4": 
            dialog.text = "이봐, 말 조심해! 그리고 차라리 꺼져.";
			Link.l1 = "글쎄, 내 도움이 필요 없다면...";
			Link.l1.go = "Underground1_5";
		break;
		case "Underground1_5": 
            dialog.text = "아니, 안 해!";
			Link.l1 = "그럼 작별이오, 행운을 빌겠소.";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Underground1_again";
		break;
		case "Underground1_again": 
            dialog.text = "또 너야? 꺼져, 더 이상 보고 싶지 않아...";
			Link.l1 = "흠...";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Underground1_again";
		break;

	}
}

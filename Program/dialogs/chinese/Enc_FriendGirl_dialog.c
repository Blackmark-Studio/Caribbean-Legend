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
			dialog.text = LinkRandPhrase("哦, 我的天, 很高兴遇到你! ",
				"终于有人来了! ",
				"哦, 上帝啊, 见到你真高兴! ");
			Link.l1 = LinkRandPhrase("怎么了, 姑娘? ",
				"有什么麻烦吗, 亲爱的? ",
				"别这么激动 --这对年轻女士的健康不好。 现在, 告诉我 --发生了什么? ");
			Link.l1.go = "Step_1";
		break;
		case "Step_1":
			dialog.text = LinkRandPhrase("我的朋友... 她太勇敢了... 她掉进了一口废弃的井里! ",
				"我的朋友下到一口废弃的井里, 到现在还没出来! 她已经在里面待了好几个小时了! ",
				"我的朋友刚在一口废弃的井里不见了! ");
			Link.l1 = "她到底为什么要进去? ! ";
			Link.l1.go = "Step_2";
		break;
		case "Step_2":
			dialog.text = "哦, 你知道, 她什么都怕! 她听说那里有个满是金子的地牢, 所以就下去了... 但我不是傻瓜, 我根本不会去想! ";
			Link.l1 = "没错, 那种地方你去了也没用。 ";
			Link.l1.go = "Step_3";
		break;		
		case "Step_3":
			dialog.text = "但我现在该怎么办? 看在上帝的份上, 请帮帮她! ";
			Link.l1 = "好吧, 我会想办法的。 你最好回家去, 这里没你什么事了。 ";
			Link.l1.go = "Step_agree";
			Link.l2 = "这是你的问题, 我不想浪费时间。 再见... ";
			Link.l2.go = "Step_disAgree";
		break;

		case "Step_agree":
			pchar.quest.Enc_FriendGirl_after.over = "yes";
			if (rand(1))
			{ //土匪
				LAi_LocationDisableMonGenTimer(pchar.GenQuest.EncGirlF.locationId, 1); //1天内不生成怪物
				LAi_LocationDisableOffGenTimer(pchar.GenQuest.EncGirlF.locationId, 1); //1天内不派遣军官
				LocatorReloadEnterDisable(pchar.GenQuest.EncGirlF.locationId, "reload2", true);
				pchar.GenQuest.OpenTheRopeExit = pchar.GenQuest.EncGirlF.locationId; //打开重新加载的标志
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
						LAi_group_MoveCharacter(sld, LAI_GROUP_ENEMY);// 林务员修改了组, 以便可以秘密用毒
						LAi_group_Attack(sld, Pchar);// 林务员添加了对玩家的攻击, 因为有些情况下他们不会攻击
						ChangeCharacterAddressGroup(sld, pchar.GenQuest.EncGirlF.locationId, "quest", "quest" + i);
						i++;
						model[iMassive] = "";	
					}
				}
			}
			else
			{ //确实是女孩 
				sld = GetCharacter(NPC_GenerateCharacter("UndergroundGirl", "women_"+(rand(5)+11), "woman", "towngirl", 5, PIRATE, 1, false, "citizen"));
				sld.dialog.filename = "Enc_FriendGirl_dialog.c";
				int iTemp = rand(1);
				sld.dialog.currentnode = "Underground"+ iTemp; //这里随机女孩的行为: 0-求助, 1-自己很厉害// 林务员 - 取消注释itemp
				sld.greeting = "Enc_RapersGirl_" + (iTemp+1); //相应的配音
			   // LAi_SetStayType(sld);
				LAi_SetCitizenType(sld);// 以便在洞穴中行走。 林务员
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				GetCharacterPos(pchar, &locx, &locy, &locz); // 及以下 - 寻找最近的定位器林务员。 
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
			dialog.text = "我不想和你这种冷漠的"+ GetSexPhrase("家伙","女人") +"说话。 滚开! ";
			Link.l1 = "呵, 真是个婊子... ";
			Link.l1.go = "exit";
		break;

		case "Underground0": //女孩真的迷路了
			dialog.text = "哦, 我的上帝, 见到你真高兴! ";
			Link.l1 = "怎么了, 美女? ";
			Link.l1.go = "Underground0_1";
		break;
		case "Underground0_1": 
			dialog.text = "我在这里迷路了! 哦, 我的上帝, 我太害怕了!! ";
			Link.l1 = "好了, 你现在安全了。 跟我来, 我给你指路。 一旦你到了地面, 就跑回家, 祈祷我再也不会在这里见到你! ";
			Link.l1.go = "Underground0_2";
		break;
		case "Underground0_2": 
			dialog.text = "如你所说, " + GetAddress_Form(NPChar) + "。 ";
			Link.l1 = "好的。 ";
			Link.l1.go = "exit";
			npchar.LifeDay = 0;
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			ChangeCharacterComplexReputation(pchar,"nobility", 4);
		break;

		case "Underground1": //厉害的小妞
			dialog.text = "哇, 看来还有人对这个地牢感兴趣! ";
			Link.l1 = "美女, 你在这里做什么? ";
			Link.l1.go = "Underground1_1";
		break;
		case "Underground1_1": 
			dialog.text = "不关你的事! ";
			Link.l1 = "哇, 这回答价值一百万比索... ";
			Link.l1.go = "Underground1_2";
		break;
		case "Underground1_2": 
			dialog.text = "给两百万。 你能走自己的路吗? 我根本不在乎你。 ";
			Link.l1 = "好吧, 我也一样, 但你上面的朋友正为你担心得要命... ";
			Link.l1.go = "Underground1_3";
		break;
		case "Underground1_3": 
			dialog.text = "真是个傻瓜! 她会吓得屁滚尿流, 还以为我和她一样。 ";
			Link.l1 = "哇, 你肯定不喜欢她。 你就是个穿着裙子的魔鬼 --说的就是你。 ";
			Link.l1.go = "Underground1_4";
		break;
		case "Underground1_4": 
			dialog.text = "嘿, 说话注意点! 最好还是滚开。 ";
			Link.l1 = "好吧, 如果你不需要我的帮助... ";
			Link.l1.go = "Underground1_5";
		break;
		case "Underground1_5": 
			dialog.text = "不, 我不需要! ";
			Link.l1 = "那再见, 祝你好运。 ";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Underground1_again";
		break;
		case "Underground1_again": 
			dialog.text = "你又来了? 滚开, 我再也不想见到你了... ";
			Link.l1 = "嗯... ";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Underground1_again";
		break;

	}
}
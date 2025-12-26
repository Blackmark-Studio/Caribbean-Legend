void ProcessDialogEvent()
{
	ref NPChar, TempChar, sld;
	aref Link, Diag;
	
	int i, iTemp;
	string sTemp, sTemp1;
	string sGroup;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		// -----------------------------------首次对话 - 第一次见面
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "First time":
			chrDisableReloadToLocation = false;
			//Lai_SetPlayerType(pchar);
			
			dialog.text = GetFullName(PChar) + "! " + "我们追踪你很久了, 终于抓到你了。 ";
			Link.l1 = "你们是谁, 想从我这里得到什么? ";
			Link.l1.go = "meeting"; 
			
			PChar.GenQuest.HunterStart = true;
		break;

		case "meeting":
			dialog.text = XI_ConvertString(Nations[sti(NPChar.nation)].Name) + "为你的人头悬赏了一笔可观的奖金, 我们必须把你送到它的任何一个殖民地, 不管你是死是活, 我们都会得到报酬。 ";
			Link.l1 = "听着, 如果你放过我, 我会付钱给你。 ";
			Link.l1.go = "Cost_Head"; 
            // boal 08.04.04 -->
            if (GetSummonSkillFromNameToOld(PChar, SKILL_SNEAK) > 2 || bBettaTestMode)
            {
				TempChar = characterFromID("Bug Fixer");
				SetRandomNameToCharacter(TempChar);
				Link.l2 = "" + GetSexPhrase("对不起, 但你们一定搞错了。 我是" + GetFullName(TempChar) + " - 这片土地上著名的商人。 ","对不起, 但你们一定搞错了。 我只是一个普通的女孩, 我父亲是" + GetFullName(TempChar) + " - 这片土地上著名的商人。 ") + "。 ";
				Link.l2.go = "lier";
			}
			Link.l3 = "好吧, 如果你们愿意, 可以试试运气。 ";
			Link.l3.go = "battle";
		break;
        
        case "lier":
            if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(150) || bBettaTestMode)
            {
				dialog.text = "哦! 我们可能确实搞错了。 请原谅我们, " + GetAddress_Form(NPChar) + "。 ";
				Link.l1 = "没关系, 别担心... ";
                Link.l1.go = "lier_2";
                AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
            }
            else
            {
				dialog.text = "我认为你在撒谎! ";
				Link.l1 = "听着, 如果你放过我, 我会付钱给你。 ";
				Link.l1.go = "Cost_Head";
				Link.l2 = "好吧, 如果你们愿意, 可以试试运气。 ";
				Link.l2.go = "battle";
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 50);
            }
            
        break;
        
        case "lier_2":
            AddDialogExitQuest("GoAway_Hunters_Land");
            DialogExit();
        break;
        // boal <--
        
        case "battle":
			AddDialogExitQuest("Battle_Hunters_Land");	// BOAL 我将所有国家的代码都移到了这里, 只是没有重命名
            DialogExit();
        break;

        case "Cost_Head2":
            AddMoneyToCharacter(pchar, -sti(PChar.HunterCost));

            AddDialogExitQuest("GoAway_Hunters_Land"); 
            DialogExit();
        break;

        case "Cost_Head":
			dialog.text = "我认为" + PChar.HunterCost + "比索对我们来说很合适。 ";
            if(makeint(Pchar.money) < sti(PChar.HunterCost))
            {
				Link.l1 = "但我没有这么多钱。 ";
                Link.l1.go = "NoMoney";
            }else{
				Link.l1 = "这是你的钱, 拿了就滚。 ";
                Link.l1.go = "Cost_Head2";
				Link.l2 = "给像你们这样的无赖这么多钱... 我想我宁愿在这里把你们都干掉! ";
                Link.l2.go = "battle";
            }
		break;

        case "NoMoney":
			dialog.text = "那样的话我们的谈话就结束了! ";
			Link.l1 = "你们永远抓不到活的我。 ";
			Link.l1.go = "battle"; 
		break;
		
		case "TreasureHunter":
			dialog.text = "等等, " + GetSexPhrase("伙计","姑娘") + "... 我觉得你身上有有趣的东西。 朋友之间应该分享找到的宝藏, 你不觉得吗? ";
			Link.l1 = "听着, 如果你放过我, 我会付钱给你。 ";
			Link.l1.go = "Cost_Head";
            // boal 08.04.04 -->
            if (GetSummonSkillFromNameToOld(PChar, SKILL_SNEAK) > 3)
            {
				TempChar = characterFromID("Bug Fixer");
				SetRandomNameToCharacter(TempChar);
				Link.l2 = "" + GetSexPhrase("对不起, 但你们一定搞错了。 我是" + GetFullName(TempChar) + " - 这片土地上的知名公民, 但肯定不是寻宝者。 ","对不起, 但你们一定搞错了。 我只是一个普通女孩, 不是寻宝者。 我父亲是" + GetFullName(TempChar) + " - 这片土地上的知名公民") + "! ";
				Link.l2.go = "TreasureHunterLier";
			}
			Link.l3 = "好吧, 看来是时候让你们身首异处了。 ";
			Link.l3.go = "battle";
		break;
		
		case "TreasureHunterLier":
            if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(150))
            {
				dialog.text = "哦! 那我们可能确实搞错了。 请原谅我们, " + GetAddress_Form(NPChar) + "。 ";
				Link.l1 = "没关系, 别担心... ";
                Link.l1.go = "lier_2";
                AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
            }
            else
            {
				dialog.text = "我认为你在撒谎! ";
				Link.l1 = "那就听听我刀刃的歌声吧。 ";
				Link.l1.go = "battle";
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 50);
            }
        break;
		
		case "TreasureCaptain":
			dialog.text = LinkRandPhrase("所以你就是那个拿了我藏宝图的人! 我想, 伙计, 是时候交出你拿走的所有东西了... ","哦, 一个竞争对手! 你走不远的, 你被我的宝藏压得走不动了... ","哼, 终于追上你了! 这个洞穴里的所有宝藏都属于我, 明白吗? 现在, 把口袋掏空, 朋友! ");
			Link.l1 = LinkRandPhrase("是时候让你见识我的刀刃了, 伙计! ","你的宝藏? 你是说它们曾经是你的, 因为现在它们是我的了! ","我宁愿用刀刃掏空你的肚子, 朋友。 ");
			Link.l1.go = "TreasureCaptain_fight"; 
		break;
		
		case "TreasureCaptain_fight":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//允许战斗 // patch-6
			for(i=1; i<=4; i++)
			{
				sld = characterFromId("Treasure_sailor_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "TreasureOfficer":
			dialog.text = LinkRandPhrase("所以, 上校是对的, 宝藏藏在这个山洞里... 把口袋掏空, 水手! ","经过在这片该死的丛林中穿过荆棘和沼泽的追踪, 我们终于追上你了。 现在, 混蛋, 你要把所有东西都给我们... ","嘿, 水手! 那个海盗的宝藏属于我们, 所以把你的脏手从上面拿开! ");
			Link.l1 = LinkRandPhrase("当然, 我没料到一个军官会这样! 但无论如何, 我会给你一个教训... ","看看他, 一个穿着军官制服的海盗... ","如今士兵和海盗确实没什么不同... ");
			Link.l1.go = "TreasureOfficer_fight"; 
		break;
		
		case "TreasureOfficer_fight":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//允许战斗 // patch-6
			for(i=1; i<=4; i++)
			{
				sld = characterFromId("Treasure_soldier_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// 生成器 "匆忙的理由"
		case "ReasonToFast_THunter_1":
			if(CheckAttribute(pchar,"GenQuest.CannotWait"))	DeleteAttribute(pchar, "GenQuest.CannotWait");
			dialog.text = "我们的金子来了。 至少我们的等待没有白费。 ";
			link.l1 = RandPhraseSimple("你们在说什么, 先生们? 我是荷兰西印度公司的代表, 只是路过这里! 我停下来欣赏海岸的景色! ","恐怕你们认错人了。 我是" + GetSexPhrase("弗朗库瓦.玛丽.帕加内尔, ","玛丽-特蕾莎, ") + "一位博物学家。 我在这里收集当地植物的样本。 想看看我的丝兰叶收藏吗? 我有几个非常有趣的! ");
			link.l1.go = "ReasonToFast_THunter_2";
			link.l2 = "你们想要什么? ! 别挡我的路! ";
			link.l2.go = "ReasonToFast_THunter_2";
		break;
		
		case "ReasonToFast_THunter_2":
			ReasonToFast_ClearTreasureBox(pchar.questTemp.ReasonToFast.Treasure.Location);
			dialog.text = "哦不, " + GetSexPhrase("我亲爱的朋友","我漂亮的女孩") + "。 那没用。 我们确定你拥有" + GetName( pchar.questTemp.ReasonToFast.mapIdx, pchar.questTemp.ReasonToFast.map, NAME_GEN) + "的地图。 他是个守财奴, 他的箱子都被钱撑破了。 所以我们不会空手而归。 ";
			link.l1 = "你说得对。 箱子确实装满了。 但你们得不到它们。 你们可以去那个洞穴看看, 应该还剩下几个破桶。 ";
			link.l1.go = "ReasonToFast_THunter_3";
			if(ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8)) >= sti(pchar.questTemp.ReasonToFast.p8) 
				&& ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7)) >= sti(pchar.questTemp.ReasonToFast.p7))
			{
				link.l2 = "你说得对。 你可以拥有你的宝藏。 记住, 它不会让你快乐, 因为它沾满了鲜血。 ";
				link.l2.go = "ReasonToFast_THunter_4";
			}	
		break;
		
		case "ReasonToFast_THunter_3":
			dialog.text = "" + GetSexPhrase("呵呵, 船长, 你还太年轻, 不想死吧... ","呵呵, 姑娘, 你还太年轻, 不想死吧... ") + "... ";
			link.l1 = "实际上, 我不打算死! ";
			link.l1.go = "ReasonToFastTHunter_Fight";
		break;
		
		case "ReasonToFast_THunter_4":
			dialog.text = "这才是理智的人说的话! ";
			link.l1 = "诅咒你和所有那些宝藏... ";
			link.l1.go = "ReasonToFast_THunter_GoAway";
		break;
		
		case "ReasonToFast_THunter_GoAway":			
			iTemp = ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8));
			if(iTemp > 0) 
			{
				ReasonToFast_GetTreasure("icollection", iTemp );
				Log_Info(XI_ConvertString("你给出物品"));
				PlayStereoSound("interface\important_item.wav");
			}	
			
			iTemp = ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7));
			if(iTemp > 0) 
			{
				ReasonToFast_GetTreasure("Chest", iTemp);
				Log_Info(XI_ConvertString("你给出物品"));
				PlayStereoSound("interface\important_item.wav");
			}	
			if(pchar.questTemp.ReasonToFast == "GetTreasure")
			{
				AddQuestRecord("ReasonToFast", "24");
				AddQuestUserData("ReasonToFast", "sName", GetName( pchar.questTemp.ReasonToFast.mapIdx, pchar.questTemp.ReasonToFast.map, NAME_GEN));
				CloseQuestHeader("ReasonToFast");	
			}
			DialogExit();	
			AddDialogExitQuest("ReasonToFast_GoAway_Hunters_Land");
		break;
		
		case "ReasonToFastTHunter_Fight":
			sGroup = "LAND_HUNTER";
			sTemp = "LandHunter0";
			iTemp = sti(pchar.HunterCost.Qty);
			chrDisableReloadToLocation = true;
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			for(i = 1; i <= iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, sGroup);
			}
			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			LAi_group_SetCheck(sGroup, "ReasonToFast_TrHuntersDied");	
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "ReasonToFast_HunterShore1":
			dialog.text = "嘿, " + GetSexPhrase("伙计","姑娘") + "! " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + "说你有东西给我们。 ";
			link.l1 = "你是什么意思? ";
			link.l1.go = "ReasonToFast_HunterShore11";
			pchar.quest.ReasonToFast_SetHunterPort_1.over = "yes";
			pchar.quest.ReasonToFast_SetHunterPort_2.over = "yes";
		break;

		case "ReasonToFast_HunterShore11":
			if(pchar.questTemp.ReasonToFast == "GetMap") 
			{
				dialog.text = "一张" + GetName( pchar.questTemp.ReasonToFast.mapIdx, pchar.questTemp.ReasonToFast.map, NAME_GEN) + "的地图。 ";
				link.l1 = "拿去吧, 向" + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT) + "问好。 告诉他我们很快会见面... ";
				link.l1.go = "ReasonToFast_HunterShore12_1";
				link.l2 = GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + "如果认为我会为他火中取栗, 那就大错特错了。 ";
				link.l2.go = "ReasonToFast_HunterShore23";
			}
			if(pchar.questTemp.ReasonToFast == "LakeyExitSuccess")
			{
				dialog.text = "你从总督那里偷来的珠宝。 ";
				if(ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8)) >= sti(pchar.questTemp.ReasonToFast.p8) 
					&& ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7)) >= sti(pchar.questTemp.ReasonToFast.p7))
				{
					link.l1 = "拿去吧, 向" + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT) + "问好。 告诉他我们很快会见面... ";
					link.l1.go = "ReasonToFast_HunterShore12_2";
				}	
				link.l2 = GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + "如果认为我会为他火中取栗, 那就大错特错了。 ";
				link.l2.go = "ReasonToFast_HunterShore23";				
			}
			pchar.quest.ReasonToFast_SetHunterPort_1.over = "yes";
			pchar.quest.ReasonToFast_SetHunterPort_2.over = "yes";
			chrDisableReloadToLocation = false;
		break;
		
		case "ReasonToFast_HunterShore12_1":
			TakeNItems(pchar, "mapQuest", -1); 
			AddQuestRecord("ReasonToFast", "20");
			AddQuestUserData("ReasonToFast", "sText", "a map of");
			AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
			CloseQuestHeader("ReasonToFast");
			DialogExit();	
			AddDialogExitQuest("ReasonToFast_GoAway_Hunters_Land");
		break;
		
		case "ReasonToFast_HunterShore12_2":
			iTemp = ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8));
			if(iTemp > 0) 
			{
				ReasonToFast_GetTreasure("icollection", iTemp );
				Log_Info(XI_ConvertString("你给出物品"));
				PlayStereoSound("interface\important_item.wav");
			}	
			
			iTemp = ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7));
			if(iTemp > 0) 
			{
				ReasonToFast_GetTreasure("Chest", iTemp);
				Log_Info(XI_ConvertString("你给出物品"));
				PlayStereoSound("interface\important_item.wav");
			}			
			AddQuestRecord("ReasonToFast", "20");
			AddQuestUserData("ReasonToFast", "sText", "treasures");
			AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
			CloseQuestHeader("ReasonToFast");
			DialogExit();	
			ReasonToFast_ClearTreasureBox(pchar.questTemp.ReasonToFast.city + "_townhall");
			ReasonToFast_ClearTreasureBox(pchar.questTemp.ReasonToFast.LakeyLocation);
			AddDialogExitQuest("ReasonToFast_GoAway_Hunters_Land");
		break;
		
		case "ReasonToFast_HunterShore2":
			dialog.text = "嘿, " + GetSexPhrase("伙计","姑娘") + "! " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN) + "有几个问题要问你。 ";
			link.l1 = "为什么他不自己问? ";
			link.l1.go = "ReasonToFast_HunterShore21";
			chrDisableReloadToLocation = false;
		break;
		
		case "ReasonToFast_HunterShore21":
			dialog.text = "根据他的身份不能。 你破坏了我们的行动, 因为你我们损失了" + sti(pchar.questTemp.ReasonToFast.p10) + "比索。 所以现在你有债务要偿还。 ";
			link.l1 = "拿去吧, 向" + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT) + "问好。 告诉他我们很快会见面... ";
			link.l1.go = "ReasonToFast_HunterShore22";
			link.l2 = GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + "如果认为我会为他火中取栗, 那就大错特错了。 ";
			link.l2.go = "ReasonToFast_HunterShore23";
		break;
		
		case "ReasonToFast_HunterShore22":
			if(makeint(pchar.money) >= sti(pchar.questTemp.ReasonToFast.p10))
			{
				AddMoneyToCharacter(pchar, -makeint(sti(pchar.questTemp.ReasonToFast.p10)));
				AddQuestRecord("ReasonToFast", "20");
				AddQuestUserData("ReasonToFast", "sText", "money");
				AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
				DialogExit();	
				AddDialogExitQuest("ReasonToFast_GoAway_Hunters_Land");
			}
			else
			{
				dialog.text = "哦, 你没有这么多钱! 好吧, 你已经做出了选择... ";
				link.l1 = "很久以前... ";
				link.l1.go = "ReasonToFastTHunter_Fight";	
				if(pchar.questTemp.ReasonToFast == "LakeyExitSuccess" || pchar.questTemp.ReasonToFast == "LakeyExitFail")
				{
					pchar.quest.ReasonToFast_SetPirateShip.win_condition.l1 = "MapEnter";
					pchar.quest.ReasonToFast_SetPirateShip.function = "ReasonToFast_PreparePirateShip";
				}
			}
		break;
		
		case "ReasonToFast_HunterShore23":
			dialog.text = "好吧, 你已经做出了选择... ";
			link.l1 = "很久以前... ";
			link.l1.go = "ReasonToFastTHunter_Fight";
			if(pchar.questTemp.ReasonToFast == "LakeyExitSuccess" || pchar.questTemp.ReasonToFast == "LakeyExitFail")
			{
				pchar.quest.ReasonToFast_SetPirateShip.win_condition.l1 = "MapEnter";
				pchar.quest.ReasonToFast_SetPirateShip.function = "ReasonToFast_PreparePirateShip";
			}
		break;
		// 生成器 "匆忙的理由"
	}
}

string GetLocHunterName()
{
	int nLoc = FindLocation(Pchar.location);
	string ret = "";

	if (CheckAttribute(&locations[nLoc],"islandId"))
	{
		if (locations[nLoc].islandId != "Mein")
		{
			ret = "island of " + GetIslandNameByID(locations[nLoc].islandId);
		}
		else
		{
			ret = "mainland of ";
		}
	}
	//
	if (CheckAttribute(&locations[nLoc],"fastreload"))
	{
		ret += " (" +GetCityName(locations[nLoc].fastreload) + ")";
	}

	return ret;	
}
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    ref chr, sld, rShip, rItm, rItem;
    float  fTemp;
    bool bOk;
	int i, iTemp;
	string sAttr, sGun, sBullet, attrL;
	aref rType;
    
	// 按案例生成IDX -->
	sAttr = Dialog.CurrentNode;
  	if (findsubstr(sAttr, "CabinCompanionTalk_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	PChar.GenQuest.CabinCompanionNum = strcut(sAttr, i+1, strlen(sAttr)-1); // 索引在末尾
 	    Dialog.CurrentNode = "Cabin_Companion_Talk";
 	}
	
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	PChar.GenQuest.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // 索引在末尾
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	PChar.GenQuest.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // 索引在末尾
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}
	
	if (findsubstr(sAttr, "tonzag_jail_" , 0) != -1) {
	 	pchar.questTemp.Tonzag.JailDialog.ID = strcut(sAttr, strlen("tonzag_jail_"), strlen(sAttr) - 1);
		DeleteAttribute(pchar, "questTemp.TonzagQuest.JailDialog." + pchar.questTemp.Tonzag.JailDialog.ID);
		AddDialogExitQuestFunction("Tonzag_InJailDialog");
 	    Dialog.CurrentNode = "exit";
 	}
 	// 按案例生成IDX <--

	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
		break;
		
		case "First time":
	      	NextDiag.TempNode = "First time";

	        Dialog.Text = "如果您读到这一行, 说明代码中存在错误";
			Link.l1 = "退出";
			Link.l1.go = "exit";
			
			//--> 为查理在船甲板上的入门教程
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_TrumDialogSamSoboi_1"))
			{
				dialog.text = "太刺激了, 该死的! 一场真正的海战! \n可惜我不能从这里看到战斗... 没关系。 我想我已经学到了足够的航海知识来想象它是如何进行的\n可能有五个海盗... 一艘大船, 几艘中型船, 还有一些小船。 正好适合我们的小艇。 这会成为一个很棒的故事 - 露露会喜欢的! ";
				link.l1 = "... ";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.SharlieTutorial_TrumDialogSamSoboi_1");
				pchar.wind.speed = 18.0;
				fWeatherSpeed = stf(18.0);
				//AddDialogExitQuestFunction("SharlieTutorial_StartShip");
				AddDialogExitQuestFunction("SharlieTutorial_TrumLoad_3");
			}
			//< —为查理在船甲板上的入门教程

			//--> 荷兰策略
			if (CheckAttribute(pchar, "questTemp.HWIC_FindIsland"))
    		{
    		    dialog.text = "所以, 我们在地图上找到了这个地方。 我应该标记它, 然后我们就可以去搜索了。 ";
    			link.l1 = "... ";
    			link.l1.go = "exit";
				AddDialogExitQuestFunction("SearchingForIslandOnMap");
    		}
			if (CheckAttribute(pchar, "questTemp.HWICMC") && pchar.questTemp.HWICMC == "Fleetwood")
    		{
    		    dialog.text = "好了, 我们到了。 我应该把我的船藏在南部海湾, 然后步行穿过丛林回来, 给弗利特伍德安排一个 nasty surprise。 ";
    			link.l1 = "... ";
    			link.l1.go = "exit";
				pchar.quest.Fleetwood_repeatShore.win_condition.l1 = "ExitFromLocation";
				pchar.quest.Fleetwood_repeatShore.win_condition.l1.location = pchar.location;
				pchar.quest.Fleetwood_repeatShore.function = "Fleetwood_repeatShore";
    		}
			//< —荷兰策略
			
			//--> 假线索
			if(CheckAttribute(pchar, "questTemp.FalseTrace") && pchar.questTemp.FalseTrace == "TalkCabinWoman" && PChar.location == Get_My_Cabin()) 
	        {
				dialog.text = "嗯... 相信这个无赖是危险的, 尽管他的故事看起来是真实的。 也许这次他没有撒谎。 但无论如何, 我应该和他的妻子谈谈... 水手长! 把那个被俘的女人带来! ";
    			link.l1 = "是, 船长! ";
	    		Link.l1.go = "exit";
				chr = characterFromId("FalseTraceWife");
				chr.dialog.currentnode = "FalseTrace_wife_6";
				pchar.questTemp.FalseTrace.CharID = "FalseTraceWife";
				AddDialogExitQuest("SetFalseTraceCharToCabin");
	    	}
			//< —假线索
			
			//--> 葡萄牙人
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "DigGems")
    		{
    		    dialog.text = "这似乎就是那个地方。 这是附近唯一一棵枯萎的树。 我应该在这里挖掘。 ";
    			link.l1 = "(挖出宝藏)";
    			link.l1.go = "exit";
				AddDialogExitQuest("FindPortugalGems");
    		}
			//< —葡萄牙人
			// 传奇故事
			if (CheckAttribute(pchar, "questTemp.Saga.JessSoul"))
    		{
    		    dialog.text = "发生了什么事? 我在哪里? 这是什么地方? ";
    			link.l1 = "... ";
    			link.l1.go = "exit";
				AddDialogExitQuest("Saga_JessikaSoul_2");
    		}
            //--> 迪芬杜拉门上的敲击技巧, LSC
			if (CheckAttribute(pchar, "questTemp.LSC.DiffIndoor"))
    		{
    		    dialog.text = "这是通往船内场所的门。 它被锁上了... 霍克一定在这里。 奥莱又提到了什么? 我应该使用秘密敲击方式。 ";
    			link.l1 = "敲两次。 ";
    			link.l1.go = "knock_2";
				link.l2 = "敲三次。 ";
    			link.l2.go = "knock_3";
				link.l3 = "敲一次, 停顿, 敲三次。 ";
    			link.l3.go = "knock_1_3";
				link.l4 = "敲两次, 停顿, 敲两次。 ";
    			link.l4.go = "knock_2_2";
				link.l5 = "敲三次, 停顿, 敲一次。 ";
    			link.l5.go = "knock_3_1";
    		}
			//< —迪芬杜拉门上的敲击技巧, LSC
			
			//--> 穿上潜水服, 切换到步行模式
			if (pchar.model == "protocusto")
    		{
    		    dialog.text = "哇! 那东西真的很重! ";
    			link.l1 = "";
    			link.l1.go = "exit";
    		}
			//< —潜水服
			// 拒绝传送
			if (IsCharacterInLocator(pchar, "item", "dolly1") || IsCharacterInLocator(pchar, "item", "dolly2") || IsCharacterInLocator(pchar, "item", "dolly3"))
    		{
    		    dialog.text = "不, 不, 不! 没门! 三次就足够了! ";
    			link.l1 = "... ";
    			link.l1.go = "exit";
    		}
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "roof")
    		{
    		    dialog.text = "完成了。 勒瓦瑟死了。 结果比我预期的要容易得多... 但有些事情不对劲。 蒂博甚至没有和马滕说话! 这意味着要么是罗伯特背叛了我, 要么是发生了意外\n但那个混蛋蒂博能跑到哪里去? 他一定在追捕凯瑟琳。 如果我想从他鼻子底下活捉那个女孩, 我必须迅速行动... ";
    			link.l1 = "";
    			link.l1.go = "terrapin";
    		}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "think")
    		{
    		    dialog.text = "宝藏, 宝藏... 一座印度城市... 我不相信这样的巧合... 我敢打赌, 我哥哥与迪乔索护卫舰的失踪有关。 他可能确保迪乔索永远不会再开口\n或者, 也许他在和他合作, 西班牙人一定有理由认为迪乔索在附近。 这毫无意义。 但我相信米歇尔运给德庞西的印度黄金, 以及米格尔.迪乔索的黄金, 是同一批黄金。 囚犯的故事与军官告诉我的关于我哥哥冒险的事情相符\n有趣的是, 米歇尔未能交付黄金, 米格尔也一样! 那么现在宝藏在哪里? 也许这就是我哥哥如此匆忙的原因\n因此, 找到黄金将意味着一石二鸟: 我将再次看到我哥哥那傲慢的眼神, 而且... 是的, 黄金总是好的。 但我究竟如何找到它? 看来, 是时候与西班牙人变得非常亲近了\n唐.拉蒙娜.门多萨已经不可能了, 我怀疑我能对付他, 但文森托神父, 男爵的死敌... 他会做的。 他的同类并不谨慎, 但爱钱和肮脏的手段\n迪乔索, 迪乔索... 我以前听过这个姓氏... 或者没有? 不管怎样, 去他的。 我应该去找军官, 索要那个西班牙囚犯。 然后我可以随时前往圣地亚哥。 ";
    			link.l1 = "";
    			link.l1.go = "exit";
    		}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "shore")
    		{
    		    dialog.text = "香草已经装上了大帆船, 她的帆早已消失在地平线之外 - 而这艘该死的大帆船并未驶向公海, 反而回到了港口。 我不能随船出现在港口 - 最好让他们认为我已经离开了瓜德罗普... 我想我会穿过丛林步行到镇上, 了解我亲爱的马沙伊... ";
    			link.l1 = "";
    			link.l1.go = "exit";
    		}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "galeon")
    		{
    		    dialog.text = "上甲板只有几个警卫, 都相当困倦。 我想我可以一个一个地把他们解决掉, 如果我从后面悄悄地来, 用指节套打他们的后脑勺... ";
    			link.l1 = "";
    			link.l1.go = "exit";
    		}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth_room"))
    		{
    		    dialog.text = "一栋未上锁的空房子, 二楼有一个舒适的房间, 而且在卡尔霍恩公寓附近... 这简直是少女的祈祷得到了回应... 如果我从窗户出去, 走在屋顶的遮阳篷上, 我会很容易地潜入阿奇的房间。 但这必须在晚上进行, 这样我才不会被抓住... ";
    			link.l1 = "";
    			link.l1.go = "exit";
				AddDialogExitQuest("GuardOT_FindWayToRoom");
    		}
			// 寻找克索奇特姆
			if (CheckAttribute(pchar, "questTemp.Ksochitam_Dolly") && pchar.questTemp.Ksochitam_Dolly == "half_pearl")
    		{
    		    dialog.text = "终于! 我找到了'显灵'指示的地点: 一个印度神像。 当靠近时,'道路之箭'停止摆动并指向一个方向。 嗯, 这似乎合乎逻辑 - 印度魔法和印度神像。 现在我应该在地图上标记'道路之箭'指示的位置, 然后我将前往多米尼加。 ";
    			link.l1 = "";
    			link.l1.go = "exit";
				AddDialogExitQuest("Ksochitam_FindFirstWay");
    		}
			if (CheckAttribute(pchar, "questTemp.Ksochitam_Dolly") && pchar.questTemp.Ksochitam_Dolly == "half_dominica")
    		{
    		    dialog.text = "终于! 我找到了'显灵'指示的地点: 一个印度神像。 当靠近时,'道路之箭'停止摆动并指向一个方向。 嗯, 这似乎合乎逻辑 - 印度魔法和印度神像。 现在我应该在地图上标记'道路之箭'指示的位置, 然后我将前往梅因。 ";
    			link.l1 = "";
    			link.l1.go = "exit";
				AddDialogExitQuest("Ksochitam_FindSecondWay");
    		}
			if (CheckAttribute(pchar, "questTemp.Ksochitam_Dolly") && pchar.questTemp.Ksochitam_Dolly == "full")
    		{
    		    dialog.text = "两个显灵都找到了! 现在我必须在地图上标记第二个方向。 这两个方向的交点将告诉我克索奇特姆岛的位置。 ";
    			link.l1 = "";
    			link.l1.go = "exit";
				AddDialogExitQuest("Ksochitam_FindFullWay");
    		}
			// 关于泰亚萨尔的思考
			if (CheckAttribute(pchar, "questTemp.Tieyasal_CabinTalk"))
    		{
				if (pchar.questTemp.Tieyasal_CabinTalk == "calendar")
				{
					dialog.text = "阿隆索.德.马尔多纳多说, 有一条通往泰亚萨尔的道路, 从尤卡坦北部开始。 这意味着我应该深入该地区的丛林。 但吉诺说, 传送雕像原本是要把人送到泰亚萨尔的\n而米斯基托的萨满蛇眼告诉我, 这些偶像被设计用来将'被吃掉的人'送到那个地方。 但为什么这些传送门会坏了呢? 嗯。 此外, 两个显灵的地图显示, 靠近米斯基托雕像的地方有一个奇怪的圆圈\n这到底是什么意思? 另一个魔法地点? 或者它表明那里的雕像有一些额外的功能? 我想, 我应该去拜访一下萨满。 或者我可以去梅因的西北部, 在当地的一个海湾寻找那条路。 ";
					link.l1 = "";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "阿隆索.德.马尔多纳多说, 从尤卡坦半岛的北部还有另一条通往泰亚萨尔的路。 这意味着我必须寻找一条进入丛林深处的道路。 很可能我需要的道路始于西北部梅因的一个海湾。 ";
					link.l1 = "";
					link.l1.go = "exit";
				}
				AddDialogExitQuest("Tieyasal_AfterCabinTalk");
    		}
			// 决定 - 头衔或自由模式 010912
			if (CheckAttribute(pchar, "questTemp.Tieyasal_final"))
    		{
				dialog.text = "完成了。 我漫长旅程的终点。 我无法想象, 把我哥哥从监狱里救出来意味着准备好与他进行最后的战斗! 我几乎 doomed 了我们的世界。 感谢上帝, 这一切都结束了\n加勒比海不再有什么能留住我了。 是时候回家了, 回法国。 但是... 我真的想这样吗? ";
				link.l1 = "是的, 我要返回欧洲。 ";
				link.l1.go = "final_1";
				link.l2 = "不, 我要留在加勒比海。 ";
				link.l2.go = "final_2";
    		}
			// 失败的结局 040912
			if (CheckAttribute(pchar, "questTemp.Europe"))
    		{
				PlaySound("Voice\English\military02.wav");
				dialog.text = "你听到上校的话了吗? 叛乱分子藏在那里! 搜查一切, 把房子翻个底朝天, 抓住你找到的每一个人! 开始行动! ";
				link.l1 = "... ";
				link.l1.go = "exit";
				AddDialogExitQuest("Europe_SharlieFinal_2");
    		}
			// Addon-2016 Jason, 法国迷你任务 (ФМК) 瓜德罗普
			/*if (CheckAttribute(pchar, "questTemp.FMQG.Info") && pchar.location == "Bridgetown_Plantation")
    		{
    		    dialog.text = "这是伏击的最佳地点。 我应该在这里等待皮内特的到来。 ";
    			link.l1 = "... ";
    			link.l1.go = "exit";
				AddDialogExitQuest("FMQG_KidnappingInfo");
    		}*/
			// Addon-2016 Jason, 法国迷你任务 (ФМК) 圣克里斯托弗
			if (CheckAttribute(pchar, "questTemp.FMQN.Choose") && pchar.location == "shore40")
    		{
				dialog.text = "嗯。 这个故事感觉不对劲。 我相信那艘来自圣琼斯的小帆船从来就没打算存在。 中尉是在把我拖进他的军事行动。 我为什么要那样做? 我没有和荷兰人开战... 我该怎么办? 我应该离开, 让英国人自己玩吗? 还是应该留下? ";
				link.l1 = "离开。 ";
				link.l1.go = "FMQN_1";
				link.l2 = "留下。 ";
				link.l2.go = "FMQN_2";
    		}
			// Addon 2016-1 Jason 海盗线
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Chest") && pchar.location == "shore37")
    		{
    		    dialog.text = "所以, 箱子准备好了。 我可以试着自己找到所有需要的物资, 但我宁愿去看看法迪。 他给我的印象是一个能买到任何东西的人。 ";
    			link.l1 = "*使用自言自语选项完成收集弹药*";
    			link.l1.go = "exit";
				AddDialogExitQuest("Mtraxx_PlantChestReadyExit");
    		}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Boats") && pchar.location == "Maracaibo_river")
    		{
    		    dialog.text = "所以, 我们必须建造六艘长船。 为此, 我需要一个木匠, 20块木板和10个皮革包";
    			link.l1 = "*使用自言自语选项开始建造长船*";
    			link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Mtraxx.Boats");
				AddQuestRecord("Roger_5", "11");
    		}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Powder") && pchar.location == "shore10")
    		{
    		    dialog.text = "所以, 我打算简单地把这堆老树炸上天。 为此, 我只需要300单位的火药, 只是为了确保。 ";
    			link.l1 = "*使用自言自语选项命令放置火药*";
    			link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Mtraxx.Retribution.Powder");
				pchar.questTemp.Mtraxx.Retribution = "powder";
				chrDisableReloadToLocation = false;
    		}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.ExitClosed") && pchar.location == "Judgement_dungeon_01")
    		{
    		    dialog.text = RandSwear()+" 出口被封了! 看来他们用重东西堵住了门! "+RandSwear()+"\n嘘... 到底怎么回事? ";
    			link.l1 = "";
    			link.l1.go = "mtraxx_dungeon";
				DeleteAttribute(pchar, "questTemp.Mtraxx.Retribution.ExitClosed");
    		}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Bead") && pchar.location == "Judgement_church")
    		{
    		    dialog.text = "就是这样... 终点线\n 看来恩里科先生是认真的: 这些地牢没有出路。 我有过片刻的希望, 当我在水位发现第二扇门时, 但现在... 我已经数不清时间了 - 我在这些黑暗的隧道里潜伏了多久? 半天, 一整天? 这个地方像棺材一样安静和可怕\n他们曾经在这里有一个教堂, 就在这里。 这是祈祷的完美地方。 我犯了很多罪, 太多了... 我会祈祷并在这里睡觉, 我的伤口和疲惫正在杀死我。 如果我幸运的话, 我永远不会起床... ";
    			link.l1 = "";
    			link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Mtraxx.Retribution.Bead");
				AddDialogExitQuestFunction("Mtraxx_RetributionBead");
    		}
			// belamour 传奇版 -->
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Choice") && pchar.questTemp.Mtraxx.Retribution.Choice == "to_choice")
			{
				dialog.text = "";
    			link.l1 = "我, 查尔斯.德.莫尔, 法国船长和贵族, 向自己和良心发誓, 我永远告别海盗生涯! ";
    			link.l1.go = "Good_Choice";
				link.l2 = "耶! 耶! 啊哈哈!! 我做到了, 我活下来了! 吃吧, 佐罗! 去死吧, 马库斯! 现在我靠自己了! 查理王子可能已经死了, 但查尔斯.德.莫尔谁也杀不了! ";
    			link.l2.go = "Bad_Choice";
			}
			// < —传奇版
			
			if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog")) {
				dialog.text = "我们该怎么办? ";
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.FirstTime")) {
					DeleteAttribute(pchar, "questTemp.TonzagQuest.JailDialog.FirstTime");
					dialog.text = "... 当然, 勒瓦瑟不是傻瓜。 否则, 他们为什么要在这个时候逮捕我们? \n而且他们一句话也没说! \n" + dialog.text;
				}
				
				DeleteAttribute(link, "l1");
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.Helena")) {
					link.l1 = "海伦, 你为什么这么安静? ";
					link.l1.go = "tonzag_jail_helena";
				}
				
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.Mary")) {
					link.l2 = "玛丽, 你为什么看起来这么高兴? ! ";
					link.l2.go = "tonzag_jail_mary";
				}
				
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.Tichingitu")) {
					link.l3 = "提钦吉图? 说些适合这种情况的话。 ";
					link.l3.go = "tonzag_jail_tichingitu";
				}
				
				if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailDialog.Tonzag")) {
					link.l4 = "赫拉克勒, 你能听到我吗? 我们要做什么? ";
					link.l4.go = "tonzag_jail_tonzag";
				}
				
				link.l5 = "没什么可做的。 我想我会暂时穿上米歇尔的鞋子。 ";
				link.l5.go = "tonzag_exit";
			}
			
			if (CheckAttribute(pchar, "questTemp.TonzagQuest.JailPanic")) {
				dialog.text = "";
				link.l1 = "哦, 我的上帝, 他们杀了赫拉克勒! ";
				link.l1.go = "exit";
				link.l2 = "你们这些混蛋! ";
				link.l2.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.TonzagQuest.JailPanic");
				AddDialogExitQuestFunction("Tonzag_GFAfterShot");
			}
			
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.RefusedGame")) {
				dialog.text = "多么美好的夜晚! 我为什么要听她的? 哥哥是对的 - 这里的女孩完全不同。 也许他们在朗姆酒里加了什么东西? ";
				link.l1 = "该睡觉了, 然后 - 去卡塔赫纳! ";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.HelenDrinking.RefusedGame");

				AddDialogExitQuestFunction("HelenDrinking_LightsOut1");
			}
			
			if (CheckAttribute(pchar, "questTemp.PZ_OsmatrivaemSunduk")) {
				dialog.text = "没有一件东西被偷, 尽管一切都散落在周围。 甚至贵重物品也完好无损。 ";
				link.l1 = "他们不是想抢劫我 - 他们在找特定的东西。 但什么? 更重要的是, 谁... ?";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.PZ_OsmatrivaemSunduk");

				AddDialogExitQuestFunction("PZ_OsmatrivaemSunduk_4");
			}
			
			if (CheckAttribute(pchar, "questTemp.PZ_GotovimShlupki")) {
				dialog.text = "让我们等到夜幕降临再进攻! ";
				link.l1 = "我们同时开始准备长船。 ";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.PZ_GotovimShlupki");

				AddDialogExitQuest("PZ_ShturmZvezdy");
			}
			
			if (CheckAttribute(pchar, "questTemp.PZ_TiboUkralDevu")) {
				dialog.text = "哦, 我的上帝... 不, 不, 不... ";
				link.l1 = "";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.PZ_TiboUkralDevu");
				
				LAi_SetActorType(pchar);
				LAi_ActorAnimation(pchar, "kneeling", "1", 7.5);
			}
			
			if (CheckAttribute(pchar, "questTemp.PZ_DevaMertva")) {
				dialog.text = "哦, 上帝, 哦, 上帝, 哦, 上帝... 为什么? 哦, 上帝, 为什么... 但我已经尽力了... ";
				link.l1 = "这都是我的错, 全是我的错。 我没有及时赶到这里。 我很抱歉... 请, 请原谅我。 ";
				link.l1.go = "exit";
				
				DeleteAttribute(pchar, "questTemp.PZ_DevaMertva");

				AddDialogExitQuest("PZ_TortureRoom_Levasser_DevushkaMertva8");
			}
		break;
		
		// boal -->
		case "TalkSelf_Main":
	   		NextDiag.TempNode = "First time";
//navy --> 酒馆决斗后
			if (CheckAttribute(pchar, "questTemp.LocationClone"))
			{
				Dialog.Text = RandPhraseSimple("那是一场该死的战斗... 现在我们可以称那些逃跑的人为懦夫... ", "哈! 那很容易。 那些菜鸟只是散开了! ");
				link.l1 = "... ";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.LocationClone");
				break;
			}
//navy <--
	        Dialog.Text = RandPhraseSimple("嗯... 那么我现在该做什么? ", "现在做什么? ");
	        if (!bDisableMapEnter && pchar.location == Get_My_Cabin())
	        {
				//navy --> 13.02.08
				if (!bDisableMapEnter && GetCompanionQuantity(PChar) > 1)
				{
    				link.l3 = "呼叫同伴。 ";
    				link.l3.go = "Cabin_CompanionSelect";
				}
				//navy <--
			}
			else 
			{   //使用线性任务, 任务#6, 在已付费房间过夜的可能性
				if (CheckAttribute(pchar, "questTemp.State.Open") && pchar.location == "Tortuga_tavern_upstairs")
				{
					if (makeint(environment.time) >= 22.0 || makeint(environment.time) < 10.0)
	    			{
	    				link.l1 = "休息到早上。 ";
	    				link.l1.go = "TalkSelf_room_day";
	    			}
	    			else
	    			{
	    				link.l1 = "休息到晚上。 ";
	    				link.l1.go = "TalkSelf_room_night";
	    				link.l2 = "休息到第二天早上。 ";
						link.l2.go = "TalkSelf_room_day";
	    			}
				}
			}
	        if (!bDisableMapEnter)//没有海战
	        {
	            if (GetCargoGoods(pchar, GOOD_SLAVES) > 0)
	            {
	                Link.l5 = "将奴隶编入船员。 ";
	        		Link.l5.go = "TalkSelf_SlavesToCrew";
	    		}
	        }
	        // 攻占城市
	        if (GetCharIDXForTownAttack(pchar.location) != -1 && !CheckAttribute(Pchar, "GenQuestFort.StartAttack") && !CheckAttribute(Pchar, "questTemp.Sharlie.DefendSP"))
	        {
	            Link.l6 = "开始攻占最近的城镇。 ";
	    		Link.l6.go = "TalkSelf_TownAttack";
	        }
	        
			bool bSeaBattle = (bDisableMapEnter) && (bSeaActive) && (!CheckAttribute(pchar, "GenQuest.MapClosedNoBattle"));
	        if(!bSeaBattle && PChar.location != "Deck_Near_Ship" && findsubstr(PChar.location, "_shipyard" , 0) == -1 && PChar.location != "CommonPackhouse_2" && !CheckAttribute(pchar, "GenQuest.CannotWait") && !CheckAttribute(loadedLocation, "CannotWait")) 
	        {
	        	Link.l7 = "我应该休息... ";
	    		Link.l7.go = "TalkSelf_StartWait";
	    	}
			
			if(CheckAttribute(pchar, "equip.gun"))
			{
				if(CheckAttribute(pchar, "chr_ai.gun.bulletNum") && sti(pchar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l8 = "我想更换火器的弹药。 ";
					Link.l8.go = "SetGunBullets";
				}	
			}
			
			if(CheckAttribute(pchar, "equip.musket"))
			{
				if(CheckAttribute(pchar, "chr_ai.musket.bulletNum") && sti(pchar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l9 = "我想更换步枪的弹药。 ";
					Link.l9.go = "SetMusketBullets";
				}
					Link.l10 = "我想选择战斗的优先武器。 ";
					Link.l10.go = "SetPriorityMode";
			}
			
			Link.l19 = "我想选择持续使用的药水。 ";
			Link.l19.go = "ChoosePotion";
			
			//--> 荷兰策略
			if(CheckAttribute(pchar, "questTemp.HWIC_Coordinates") && PChar.location == Get_My_Cabin()) 
	        {
	        	Link.l11 = "尝试通过地图上的坐标找到岛屿。 ";
	    		Link.l11.go = "Seek_AbyIsland";
	    	}
			//< —荷兰策略
			
			//--> 假线索
			if(CheckAttribute(pchar, "questTemp.FalseTrace") && pchar.questTemp.FalseTrace == "TalkCabin" && PChar.location == Get_My_Cabin()) 
	        {
	        	Link.l13 = "召唤亚当.雷纳。 ";
	    		Link.l13.go = "FalseTrace_Cabin";
	    	}
			if(CheckAttribute(pchar, "questTemp.FalseTrace") && pchar.questTemp.FalseTrace == "CatchAdam" && PChar.location == Get_My_Cabin()) 
	        {
	        	Link.l13 = "逮捕亚当.雷纳。 ";
	    		Link.l13.go = "FalseTrace_Cabin";
	    	}
			//< —假线索
			// Addon 2016-1 Jason 海盗线
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Ammo") && PChar.location == "Shore37") // 行程3
	        {
	        	Link.l17 = "清点箱子里的物品, 并决定完成皮卡德的弹药收集。 ";
	    		Link.l17.go = "mtraxx_ammo";
	    	}
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Mutiny") && pchar.location == "Maracaibo_Plantation" && stf(environment.time) >= 3.00 && stf(environment.time) < 4.00) 
	        {
	        	Link.l17 = "下令攻击马拉开波种植园。 ";
	    		Link.l17.go = "mtraxx_mutiny";
	    	}
			if(CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "merida_boats" && pchar.location == "Maracaibo_river") 
	        {
	        	Link.l17 = "下令建造长船。 ";
	    		Link.l17.go = "mtraxx_boats";
	    	}
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "powder" && pchar.location == "shore10") 
	        {
	        	Link.l17 = "下令将火药运送到死亡障碍物。 ";
	    		Link.l17.go = "mtraxx_powder";
	    	}
			// Jason 长久幸福
			if(CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "letter") 
	        {
	        	Link.l18 = "考虑婚礼。 ";
	    		Link.l18.go = "LH_marry";
	    	}
			if(CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "marry_offer" && LongHappy_CheckShore()) // 28-03-20
	        {
	        	Link.l18 = "提出结婚提议。 ";
	    		Link.l18.go = "LH_marry_3";
	    	}
			if(CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "toIslaTesoro" && pchar.location == "Pirates_town") 
	        {
	        	Link.l18 = "准备庆祝活动。 ";
	    		Link.l18.go = "LH_marry_4";
	    	}
			//--> 游戏结束
			if(CheckAttribute(pchar, "questTemp.Tieyasal_WinEnd")) // patch-9
	        {
	        	Link.l15 = "完成加勒比海的事务, 航行到欧洲。 ";
	    		Link.l15.go = "final_1";
	    	}
			//< —游戏结束
			Link.l20 = RandPhraseSimple("现在不行。 没有时间。 ", "没有时间, 要做的事情太多了。 ");
			Link.l20.go = "exit";
		break;
		
		case "tonzag_exit":
			DialogExit_Self();
			AddDialogExitQuestFunction("Tonzag_CreateKiller");
		break;
		
		
		case "SetGunBullets":
			Dialog.Text = "选择弹药类型:";
			sGun = GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(pchar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;
		
		case "SetGunBullets2":
			i = sti(PChar.GenQuest.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(pchar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(pchar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar,"GenQuest.SetGunBullets");
			DialogExit_Self();
		break;
		
		case "SetMusketBullets":
			Dialog.Text = "选择弹药类型:";
			sGun = GetCharacterEquipByGroup(pchar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(pchar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
				Link.(attrL).go = "SetMusketBullets1_" + i;
			}
		break;
		
		case "SetMusketBullets2":
			i = sti(PChar.GenQuest.SetMusketBullets) + 1; 
			sGun = GetCharacterEquipByGroup(pchar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(pchar, "musket", sBullet);
			LAi_GunSetUnload(pchar, "musket");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar,"GenQuest.SetMusketBullets");
			DialogExit_Self();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "战斗开始时我将使用:";
			Link.l1 = "刀刃";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "步枪";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
			pchar.PriorityMode = 1;
			DialogExit_Self();
		break;
		
		case "MusketPriorityMode":
			pchar.PriorityMode = 2;
			DialogExit_Self();
		break;
		
		case "ChoosePotion":
			Dialog.Text = "选择药水:";
	    	Link.l1 = "治疗药水。 ";
	    	Link.l1.go = "ChoosePotion1";
			Link.l2 = "长生不老药。 ";
	    	Link.l2.go = "ChoosePotion2";
			Link.l3 = "混合物。 ";
	    	Link.l3.go = "ChoosePotion3";
			Link.l4 = "姜根。 ";
	    	Link.l4.go = "ChoosePotion4";
			Link.l5 = "朗姆酒。 ";
	    	Link.l5.go = "ChoosePotion5";
			Link.l6 = "葡萄酒。 ";
	    	Link.l6.go = "ChoosePotion6";
			if (CheckAttribute(pchar, "GenQuest.Potion_choice"))
			{
				Link.l7 = "我想自动选择药水。 ";
				Link.l7.go = "ChoosePotion7";
			}
			Link.l8 = "等等, 我改变主意了..";
	    	Link.l8.go = "ChoosePotion8";
		break;
		
		case "ChoosePotion1":
			log_info("默认将使用治疗精华。 ");
			pchar.GenQuest.Potion_choice = "potion1";
			DialogExit_Self();
		break;
		
		case "ChoosePotion2":
			log_info("默认将使用长生不老药。 ");
			pchar.GenQuest.Potion_choice = "potion2";
			DialogExit_Self();
		break;
		
		case "ChoosePotion3":
			log_info("默认将使用混合物。 ");
			pchar.GenQuest.Potion_choice = "potion4";
			DialogExit_Self();
		break;
		
		case "ChoosePotion4":
			log_info("默认将使用姜根。 ");
			pchar.GenQuest.Potion_choice = "potion5";
			DialogExit_Self();
		break;
		
		case "ChoosePotion5":
			log_info("默认将使用朗姆酒。 ");
			pchar.GenQuest.Potion_choice = "potionrum";
			DialogExit_Self();
		break;
		
		case "ChoosePotion6":
			log_info("默认将使用葡萄酒。 ");
			pchar.GenQuest.Potion_choice = "potionwine";
			DialogExit_Self();
		break;
		
		case "ChoosePotion7":
			log_info("将自动选择药水。 ");
			DeleteAttribute(pchar, "GenQuest.Potion_choice");
			DialogExit_Self();
		break;
		
		case "ChoosePotion8":
			DialogExit_Self();
		break;
		
		case "TalkSelf_StartWait":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			PChar.GenQuest.CallFunctionParam = "LaunchTavernWaitScreen";
			DoQuestCheckDelay("CallFunctionParam", 0.1); // 需要延迟, 否则 - 玩家开始旋转
		break;
		
		case "TalkSelf_room_night":
			NextDiag.CurrentNode = NextDiag.TempNode;
			//AddDialogExitQuestFunction("TavernWaitDate_Night");
			TavernWaitDate("wait_night");
			DialogExit_Self();
		break;

		case "TalkSelf_room_day":
			NextDiag.CurrentNode = NextDiag.TempNode;
			//AddDialogExitQuestFunction("TavernWaitDate_Day");
			TavernWaitDate("wait_day");
			DialogExit_Self();
		break;
		// 攻占城市
		case "TalkSelf_TownAttack":
            int needCrew = 500;
			if(CheckOfficersPerk(pchar, "Troopers")) needCrew = 300;
            bOk = (GetPartyCrewQuantity(Pchar, true) >= needCrew) || bBettaTestMode;
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && bOk)
	        {
	            chr = GetCharacter(GetCharIDXForTownAttack(pchar.location));
	            if (chr.from_sea == Pchar.location.from_sea)
	            {
					Dialog.Text = "我们可以开始攻占城镇, 但船无法长时间承受堡垒大炮的轰击, 我们也无法派出登陆队。 ";
	    			Link.l1 = "... ";
	    			Link.l1.go = "exit";
	            }
	            else
	            {
					if (pchar.location == "Panama_ExitTown" || pchar.location == "Tortuga_ExitTown" || pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_ExitTown") // patch-5
					{
						Dialog.Text = "不, 我还没疯到那个程度..";
	    				Link.l1 = "... ";
	    				Link.l1.go = "exit";
					}
					else
					{
						if (pchar.location == "LosTeques_ExitTown")
						{
							Dialog.Text = "在没有首先收集关于那里开采的黄金和白银的信息的情况下, 攻击这个矿场是没有意义的。 否则, 我将派我的人去白白送死。 ";
							Link.l1 = "... ";
							Link.l1.go = "exit";
						}
						else
						{
							Dialog.Text = "攻击 " + GetCityName(chr.City) + "。 ";
							if (CheckAttribute(pchar, "questTemp.Patria.SanJoseAttack") && pchar.location == "PortSpein_ExitTown") // Jason НСО
							{
								Link.l1 = "别胡闹了! 停下! ";
								Link.l1.go = "exit";
								break;
							}
							if (CheckAttribute(pchar, "questTemp.Patria")) // Jason НСО
							{
								if (pchar.questTemp.Patria != "fail" || pchar.questTemp.Patria != "complete")
								{
									if (pchar.location == "Marigo_ExitTown" || pchar.location == "Villemstad_ExitTown")
									{
										Link.l1 = "别胡闹了! 停下! ";
										Link.l1.go = "exit";
										break;
									}
								}
							}
							Link.l1 = "武装起来! ";
							Link.l1.go = "TalkSelf_TownAttack_Start";
		    			Link.l2 = "停止! ";
							Link.l2.go = "exit";
						}
	    		}
	        }
	        }
	        else
	        {
				if(!CheckAttribute(Pchar, "GenQuestFort.StartAttack"))
				{
					Dialog.Text = "嘿! 船员人数不够; 我们至少需要 " + needCrew + " 人。 ";
					Link.l1 = "... ";
					Link.l1.go = "exit";
				}
				else
				{
					Dialog.Text = "不要散开! 继续进攻! ";
					Link.l2 = "... ";
					Link.l2.go = "exit";				
				}			
			}
	    break;

		case "TalkSelf_TownAttack_Start":
	        NextDiag.CurrentNode = NextDiag.TempNode;

			Pchar.GenQuestFort.StartAttack = true;
		    Pchar.GenQuestFort.fortCharacterIdx = GetCharIDXForTownAttack(pchar.location);
		    DeleteQuestAttribute("Union_with_Escadra");
	        chr = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
			if (isCityHasFort(chr.City))
			{
	        	SetLocationCapturedState(chr.from_sea, true);
	        }
	        else
	        {
	            SetLocationCapturedState(chr.Default, true); // 用于陆地
	        }
	        AddDialogExitQuest("Capture_Forts");
	        Ship_NationAgressive(chr, chr);
	        DialogExit_Self();
	    break;
// 将奴隶编入船员 -->
		case "TalkSelf_SlavesToCrew":
	        if (GetCurCrewEscadr() >= GetMaxCrewAble())
	        {
	            Dialog.Text = "没有奴隶愿意加入船员。 ";
	            Link.l1 = "去他们的! ";
	    		Link.l1.go = "exit";
	        }
	        else
	        {
	            if (GetCrewQuantity(pchar) >= GetMaxCrewQuantity(pchar))
	            {
	                Dialog.Text = "船上没有多余空间容纳新水手了。 ";
	                Link.l1 = "嘿! 我需要把部分船员转移到另一艘船。 ";
	        		Link.l1.go = "exit";
	            }
	            else
	            {
	                if (GetFreeCrewQuantity(pchar) <= GetCargoGoods(pchar, GOOD_SLAVES))
	                {
	                    pchar.GenQuest.SlavesToCrew = GetFreeCrewQuantity(pchar);
	                }
	                else
	                {
	                    pchar.GenQuest.SlavesToCrew = GetCargoGoods(pchar, GOOD_SLAVES);
	                }
	                Dialog.Text = "你的船员可以补充 " + pchar.GenQuest.SlavesToCrew + " 名愿意为你服务的奴隶。 你愿意接受吗? ";
	                Link.l1 = "是的";
	        		Link.l1.go = "TalkSelf_SlavesToCrew_1";
	        		Link.l2 = "不";
	        		Link.l2.go = "exit";
	    		}
			}
		break;

		case "TalkSelf_SlavesToCrew_1":
			bOk = ShipBonus2Artefact(pchar, SHIP_MEMENTO) && CheckAttribute(&RealShips[sti(pchar.Ship.Type)], "DeadSailors.RecruitSlaveBonus");
			if(!bOk)
			{
				// belamour legendary edition  perk 获得工作时间, 旧方法不适用
				if (GetOfficersPerkUsing(pchar, "IronWill"))
				{
					AddCrewMorale(pchar, -makeint(sti(pchar.GenQuest.SlavesToCrew) / 5.0))
				}
				else
				{
					AddCrewMorale(pchar, -makeint(sti(pchar.GenQuest.SlavesToCrew) / 3.0))
				}
			}
			ChangeCharacterComplexReputation(pchar,"authority", -0.5);
	        // 经验值下降 -->
	        fTemp =  stf(GetCrewQuantity(pchar) + sti(pchar.GenQuest.SlavesToCrew));
	        pchar.Ship.Crew.Exp.Sailors   = (stf(pchar.Ship.Crew.Exp.Sailors)*GetCrewQuantity(pchar) + 
			                                        stf(pchar.Ship.Crew.Exp.Sailors)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			pchar.Ship.Crew.Exp.Cannoners   = (stf(pchar.Ship.Crew.Exp.Cannoners)*GetCrewQuantity(pchar) + 
			                                        stf(pchar.Ship.Crew.Exp.Cannoners)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			pchar.Ship.Crew.Exp.Soldiers   = (stf(pchar.Ship.Crew.Exp.Soldiers)*GetCrewQuantity(pchar) + 
			                                        stf(pchar.Ship.Crew.Exp.Soldiers)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			// 经验值下降 < —
			pchar.Ship.Crew.Quantity = sti(pchar.Ship.Crew.Quantity) + sti(pchar.GenQuest.SlavesToCrew); 
	        RemoveCharacterGoodsSelf(pchar, GOOD_SLAVES, sti(pchar.GenQuest.SlavesToCrew));       
			                            
	        NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
		break;
		// 将奴隶编入船员  <--
		// boal <--

//navy 走私地铁 -->
		case "GenTravel_Main":
			NextDiag.TempNode = "First time";
			dialog.Text = "现在这艘漂亮的船是我的了, 我是这里的船长! 不过很遗憾, 我不得不杀了全体船员。 ";
			Link.l1 = "是时候上岸了... ";
			Link.l1.go = "exit";

			chr = CharacterFromID("Abracham_Gray");
			chr.location = "none";
			SeaExchangeCharactersShips(PChar, chr, false, false);
			SetCrewQuantity(PChar, 0);

			//将主角运送到需要的地方... 
			SetAnyReloadToLocation(pchar.GenQuest.contraTravel.destination.loc, pchar.GenQuest.contraTravel.destination.group, pchar.GenQuest.contraTravel.destination.locator, "", 0, 0, 0, 0);
			AddDialogExitQuest("AnyReloadToLocation");
            chrDisableReloadToLocation = false;
            
			CloseQuestHeader("Gen_ContrabandTravel");
			setCharacterShipLocation(PChar, pchar.GenQuest.contraTravel.destination.loc);
			setWDMPointXZ(pchar.GenQuest.contraTravel.destination.loc);

			//删除三个属性
			DeleteAttribute(PChar, "GenQuest.contraTravel");
			break;
//navy 走私地铁 <--

//navy --> 13.02.08
		case "Cabin_CompanionSelect":
			Dialog.Text = "召唤哪个同伴? ";
			for (i = 1; i < GetCompanionQuantity(PChar); i++)
			{
				chr = GetCharacter(GetCompanionIndex(PChar, i));
				if (!CheckAttribute(chr, "Tasks.Clone") && sti(chr.Payment) == true)
				{
					sAttr = "l" + i;
					rShip = GetRealShip(sti(chr.Ship.Type));
					link.(sAttr) = GetFullName(chr) + " - " + xiStr(rShip.BaseName) + "'" + chr.Ship.Name + "'。 ";
					link.(sAttr).go = "CabinCompanionTalk_" + i;
				}
			}
			link.l9 = "改天吧。 ";
			link.l9.go = "exit";
			break;

		case "Cabin_Companion_Talk":
			i = sti(PChar.GenQuest.CabinCompanionNum);
			PlaceCompanionCloneNearMChr(i, false);

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			break;
//navy <--

		//--> 荷兰策略
		case "Seek_AbyIsland":
			bOk = CheckCharacterItem(pchar, "bussol") && CheckCharacterItem(pchar, "clock2");
			bool bOk1 = CheckCharacterItem(pchar, "sextant2");
			if (bOk || bOk1)
			{
				DialogExit();
				DeleteAttribute(pchar, "questTemp.HWIC_Coordinates");
				pchar.questTemp.HWIC_FindIsland = "true";
				AddDialogExitQuestFunction("PrepareSearchingFor");
			}
			else
			{
				dialog.text = "可惜我没有必要的导航仪器来确定经纬度。 我得换个时间再找这个岛了。 ";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
		//< —荷兰策略
		
		//--> 假线索
		case "FalseTrace_Cabin":
			dialog.text = "水手长! 立刻把亚当.雷纳带到我这里来! ";
			link.l1 = "是, 船长! ";
			link.l1.go = "exit";
			chr = characterFromId("Mugger");
			if (pchar.questTemp.FalseTrace == "CatchAdam") chr.dialog.currentnode = "FalseTrace_17";
			else chr.dialog.currentnode = "FalseTrace_7";
			pchar.questTemp.FalseTrace.CharID = "Mugger";
			AddDialogExitQuest("SetFalseTraceCharToCabin");
		break;
		
		case "FalseTrace_Woman":
			DialogExit();
			chr = characterFromId("FalseTraceWife");
			chr.dialog.currentnode = "FalseTrace_wife_6";
			pchar.questTemp.FalseTrace.CharID = "FalseTraceWife";
			AddDialogExitQuest("SetFalseTraceCharToCabin");
		break;
		//< —假线索
		
		//--> LSC, 门上的敲击技巧
		case "knock_2":
			PlaySound("interface\knock_2.wav");
			dialog.text = "好, 我敲了, 现在等着回应... ";
			link.l1 = "(等待)";
			link.l1.go = "knock_wrong";
		break;
		
		case "knock_3":
			PlaySound("interface\knock.wav");
			dialog.text = "好, 我敲了, 现在等着回应... ";
			link.l1 = "(等待)";
			link.l1.go = "knock_wrong";
		break;
		
		case "knock_3_1":
			PlaySound("interface\knock_3_1.wav");
			dialog.text = "好, 我敲了, 现在等着回应... ";
			link.l1 = "(等待)";
			link.l1.go = "knock_wrong";
		break;
		
		case "knock_1_3":
			PlaySound("interface\knock_1_3.wav");
			dialog.text = "好, 我敲了, 现在等着回应... ";
			link.l1 = "(等待)";
			link.l1.go = "knock_wrong";
		break;
		
		case "knock_2_2":
			PlaySound("interface\knock_2_2.wav");
			dialog.text = "好, 我敲了, 现在等着回应... ";
			link.l1 = "(等待)";
			link.l1.go = "knock_right";
		break;
		
		case "knock_wrong":
			dialog.text = "他没开门... 我想我用错了秘密敲击方式。 好吧, 我明天再来试试。 今天他肯定不会开门的。 ";
			link.l1 = "(离开)";
			link.l1.go = "exit";
		break;
		
		case "knock_right":
			PlaySound("interface\key.wav");
			PlaySound("Voice\English\YouFace.wav");
			dialog.text = "哇! 他回应并开门了! 我现在可以进去了... ";
			link.l1 = "(进入)";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.LSC.DiffIndoor");
			LocatorReloadEnterDisable("LostShipsCity_town", "reload74", false);
		break;
		//< —LSC, 门上的敲击技巧
		
		// 海龟汤
		case "terrapin":
			PlaySound("Interface\Door_Kick.wav");
			PlaySound("Voice\English\EvilPirates02.wav");
			dialog.text = "天哪! 这就是勒瓦瑟的延迟后援... 我不可能从门出去... 好吧, 我就跟着蒂博的脚步 - 从窗户出去! 毕竟这个混蛋不知怎么溜出去了! ";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Terrapin_GoWindow");
		break;
		
		// 防守圣皮埃尔
		case "SP_defend":
			PlaySound("Voice\English\military02.wav");
			dialog.text = "那么, 我们的任务是击退该死的西班牙人的进攻, 拯救圣皮埃尔。 堡垒已被攻占, 街道上正在进行战斗。 圣皮埃尔湾有一支强大的中队, 他们有一艘旗舰级战列舰。 现在进攻它毫无意义, 堡垒和城市都在敌人控制下, 他们不会让我们在港口登陆\n因此, 我决定穿过丛林, 从城门后面攻击他们。 一旦堡垒和城市从西班牙人手中清除, 我们就对付中队。 没有堡垒的火力支援, 它会变得更加脆弱\n这并不容易, 所以我已下令除正常工资外, 额外支付十万比索分发给船员。 我们出发吧! ";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("DefendSP_GoJungle");
		break;
		
		// 游戏结局
		case "final_1": // Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor")) // 总督不会离开
			{
				dialog.text = "等等, 我要去哪里? 没有巴黎的许可, 我不能离开总督的职位! 否则回到法国时, 我肯定会因未经授权放弃委托的殖民地而被捕。 巴黎, 我会想念你的... ";
				link.l1 = "";
				link.l1.go = "exit";
				EndQuestMovie();
			}
			else
			{
				dialog.text = "那么我们不要再浪费时间了! 我太想念我亲爱的加斯科尼的田野了! 起航! ";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("Final_ReturnToEurope");
			}
		break;
		
		case "final_2":
			dialog.text = "我相信这是正确的决定! 当我在这里找到自己时, 古老的欧洲还有什么在等我? 此外, 我可以随时选择回到法国! ";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Final_StayInCarribean"); // 010912
			DeleteAttribute(pchar, "questTemp.Tieyasal_final");
		break;
		
		// Addon-2016 Jason, 法国迷你任务 (ФМК) 圣克里斯托弗
		case "FMQN_1":
			dialog.text = "这是最好的办法。 我应该上船离开这里。 ";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ChooseExit");
		break;
		
		case "FMQN_2":
			dialog.text = "不, 没门, 我要留下。 但是该死的, 我不会在这里等着天知道什么。 我应该航行到菲利普斯堡港, 调查情况。 我不喜欢被某个该死的说谎的英国人当工具使的想法。 ";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ChooseContinue");
		break;
		
		// Addon 2016-1 Jason 海盗线
		case "mtraxx_ammo":
			Mtraxx_PlantCheckShoreBox(); // 分析箱子内容
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Weapon.Blade") && !CheckAttribute(pchar, "questTemp.Mtraxx.Weapon.NoBlade")) // 收集了30把弯刀
			{
				dialog.text = "箱子里有三十把冷兵器! 我现在该停止了, 还是应该收集更多火器。 弹药和药水? ";
				link.l1 = "这足够了! ";
				link.l1.go = "mtraxx_ammo_1";
				link.l2 = "不, 我应该继续装满这个箱子。 ";
				link.l2.go = "exit";
				// belamour legendary edition
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "Full")
				{
					link.l3 = "用法迪箱子里的东西装满, 把多余的拿走。 "; 
					link.l3.go = "mtraxx_ammo_1";
				}
			}
			else
			{
				dialog.text = "还没收集到三十把冷兵器! 我应该带更多。 ";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
		
		case "mtraxx_ammo_1":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(characterFromId("Fadey"));
            dialog.text = "锁上箱子, 制定把它偷运到种植园的计划。 ";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantShoreBoxComplete");
		break;
		
		case "mtraxx_mutiny":
            dialog.text = "冲啊! 万岁! ";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantMutiny");
		break;
		
		case "mtraxx_boats":
            if (GetSquadronGoods(pchar, GOOD_PLANKS) >= 20 && GetSquadronGoods(pchar, GOOD_LEATHER) >= 10) // 材料充足
			{
				if (Mtraxx_MeridaCheckCarpenter()) // 有木匠
				{
					dialog.text = "所有所需材料已准备好, 我们应该立即开始建造长船。 ";
					link.l1 = "";
					link.l1.go = "exit";
					AddDialogExitQuestFunction("Mtraxx_MeridaBuildBoats");
				}
				else
				{
					dialog.text = "我没有有经验的木匠来执行这项工作。 我应该指派一名军官担任这个职位。 ";
					link.l1 = "";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "材料不足, 我们至少需要20包木板和10包皮革。 ";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
		
		case "mtraxx_powder":
            if (GetSquadronGoods(pchar, GOOD_POWDER) >= 300) // 有足够火药
			{
				if (GetCrewQuantity(pchar) >= 20) // 有足够船员
				{
					dialog.text = "一切准备就绪, 可以爆破了! ";
					link.l1 = "";
					link.l1.go = "exit";
					AddDialogExitQuestFunction("Mtraxx_RetributionBarrels");
				}
				else
				{
					dialog.text = "我至少需要20个人来运送火药。 ";
					link.l1 = "";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "火药不足, 至少需要300单位。 ";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
		
		case "mtraxx_dungeon":
			PlaySound("ambient\jail\jail_door2.wav");
            dialog.text = "那是门吗? ";
			link.l1 = "";
			link.l1.go = "mtraxx_dungeon_1";
		break;
		
		case "mtraxx_dungeon_1":
			PlaySound("ambient\jail\jail_door1.wav");
            dialog.text = "对! 我们有访客... 扬? ..";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionRunToEnrico");
		break;
		// belamour 传奇版 -->
		case "Good_Choice":
			pchar.questTemp.Mtraxx.Retribution.Choice = "good";
			DoQuestCheckDelay("Mtraxx_RetributionFreedom", 0.5); 
			DialogExit_Self();
		break;
		
		case "Bad_Choice":
			pchar.questTemp.Mtraxx.Retribution.Choice = "bad";
			Achievment_Set("ach_CL_97");
			bNoEatNoRats = false;
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Roger_10", "18");
			bQuestDisableMapEnter = false;//打开地图
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			pchar.quest.mtraxx_line_complete.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_line_complete.function = "Mtraxx_RetributionComplete";
			DialogExit_Self();
		break;
		// < —传奇版
		
		// Jason 长久幸福
		case "LH_marry":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			string sTemp = sld.name;
			dialog.text = "我和" + sTemp + "在一起很久了, 我们的关系比任何教会誓言都更牢固, 但我希望我们俩都记住这一刻。 因此, 我需要决定向她求婚的地点: ";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				link.l1 = "特索罗岛 - 这个岛在我们的故事中意义重大。 我想没有比这更好的地方了 - 萨博.马蒂拉峡的日落很美! ";
				link.l1.go = "LH_marry_1_1";
			}
			link.l2 = " 托尔图加 - 我们时代自由的象征, 从灯塔俯瞰托尔图海峡的景色值得任何画家挥毫! ";
			link.l2.go = "LH_marry_1_2";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l3 = "牙买加 - 它有太多值得欣赏的地方! 在波特兰峡欣赏黎明, 我把这想象成人间天堂。 ";
				link.l3.go = "LH_marry_1_3";
			}
		break;
		
		case "LH_marry_1_1":
			pchar.questTemp.LongHappy.Shore = "Shore_ship1";
			AddQuestRecord("LongHappy", "2_1");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName", sTemp);
			dialog.text = "但我们不能没有教会的庄严仪式 - 一切都应该按照所有教规进行, 这样我父亲就不得不接受我的选择。 因此, 我需要一位牧师, 除了本笃院长, 我看不到任何值得这个职位的人。 他是我父亲的老朋友, 我的新世界冒险就是从他开始的。 我想他会同意给我这个荣誉。 ";
			link.l1 = "";
			link.l1.go = "LH_marry_2";
		break;
		
		case "LH_marry_1_2":
			pchar.questTemp.LongHappy.Shore = "Mayak6";
			AddQuestRecord("LongHappy", "2_2");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName", sTemp);
			dialog.text = "但我们不能没有教会的庄严仪式 - 一切都应该按照所有教规进行, 这样我父亲就不得不接受我的选择。 因此, 我需要一位牧师, 除了本笃院长, 我看不到任何值得这个职位的人。 他是我父亲的老朋友, 我的新世界冒险就是从他开始的。 我想他会同意给我这个荣誉。 ";
			link.l1 = "";
			link.l1.go = "LH_marry_2";
		break;
		
		case "LH_marry_1_3":
			pchar.questTemp.LongHappy.Shore = "Shore36";
			AddQuestRecord("LongHappy", "2_3");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName", sTemp);
			dialog.text = "但我们不能没有教会的庄严仪式 - 一切都应该按照所有教规进行, 这样我父亲就不得不接受我的选择。 因此, 我需要一位牧师, 除了本笃院长, 我看不到任何值得这个职位的人。 他是我父亲的老朋友, 我的新世界冒险就是从他开始的。 我想他会同意给我这个荣誉。 ";
			link.l1 = "";
			link.l1.go = "LH_marry_2";
		break;
		
		case "LH_marry_2":
			AddQuestRecord("LongHappy", "3");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName", sTemp);
			dialog.text = "好吧, 这可以在没有人类庄严仪式的情况下发生。 不过我更愿意稍后和" + sTemp + "讨论这个问题。 ";
			link.l1 = "";
			link.l1.go = "exit";
			pchar.questTemp.LongHappy = "choose";
		break;
		
		case "LH_marry_3":
			dialog.text = "好吧, 我准备好了! ";
			link.l1 = "";
			link.l1.go = "exit";
			LongHappy_MarryOffer();
		break;
		
		case "LH_marry_4":
			if (LongHappy_CheckGoods())
			{
				dialog.text = "一切都准备好了! ";
				link.l1 = "";
				link.l1.go = "exit";
				LongHappy_OnIslaTesoro();
			}
			else
			{
				dialog.text = "还没有收集到必要的货物和硬币! ";
				link.l1 = "";
				link.l1.go = "exit";
			}
		break;
	}
}

void DialogExit_Self()
{
    SendMessage(PChar, "ls", MSG_CHARACTER_EX_MSG, "forceBlend");
    DialogExit();
	locCameraSleep(false); //boal
}
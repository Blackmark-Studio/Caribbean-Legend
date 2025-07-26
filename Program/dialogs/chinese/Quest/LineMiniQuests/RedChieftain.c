void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "这是一个漏洞。 请告知开发人员。 ";
			link.l1 = "我会的! ";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "RedChieftain":
			dialog.text = "你好, 白人。 我看到你是大独木舟的船长。 我是卡纳里。 我是开曼 --强大的阿拉瓦克部落的酋长。 我想和你谈谈。 ";
			link.l1 = "我在听, 酋长。 是什么麻烦让你来找我? ";
			link.l1.go = "RedChieftain_0";
			link.l2 = "你想从我这里得到什么, 你这个肮脏的红皮肤猿猴? 回到你的丛林里去, 不要用你的请求来打扰我。 ";
			link.l2.go = "RedChieftain_exit";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity(pchar.questTemp.RedChieftain.StartCity);
		break;
		
		case "RedChieftain_exit":
			dialog.text = "咕-呜! 白人船长没受过礼貌教育吗? 我本想给你一个提议。 你本可以赚很多贝壳串珠, 但现在我要走了。 再见, 白人。 ";
			link.l1 = "走吧, 滚吧... ";
			link.l1.go = "RedChieftain_exit_1";
		break;
		
		case "RedChieftain_exit_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.RedChieftain");
			chrDisableReloadToLocation = false;
			ChangeIndianRelation(-3.0);
		break;
		
		case "RedChieftain_0":
			dialog.text = "白人兄弟像猫头鹰一样有洞察力, 像蛇一样狡猾。 印第安人遇到了麻烦。 白人的大独木舟来到我的村庄。 他们带走了许多开曼人, 我的人民, 把他们放在他们的独木舟上, 带到众水之母那里... ";
			link.l1 = "等等... 你是说你的人民被船上的白人奴役了? ";
			if (sti(pchar.Basenation) == SPAIN) link.l1.go = "RedChieftain_2";
			else link.l1.go = "RedChieftain_1";
		break;
		
		case "RedChieftain_1":
			dialog.text = "你说得对, 白人兄弟。 我知道那些白人不是你的朋友。 这些是西班牙部落的残忍白人。 他们带走了我的人民。 但我找到了他们。 西班牙人让印第安人从黎明到黄昏工作, 潜入众水之母深处, 寻找装满神之泪的贝壳。 ";
			link.l1 = "采珠... 那是一项残酷的工作。 ";
			link.l1.go = "RedChieftain_3";
			pchar.questTemp.RedChieftain.Spa = "true";
			pchar.questTemp.RedChieftain.AttackNation = SPAIN;
		break;
		
		case "RedChieftain_2":
			dialog.text = "你说得对, 白人兄弟。 我知道那些人不是你的朋友。 他们是英国部落的。 他们带走了我的人民。 但我找到了他们。 英国人让印第安人从黎明到黄昏工作, 潜入众水之母深处, 寻找装满神之泪的贝壳。 ";
			link.l1 = "采珠... 这是一项艰苦的工作。 ";
			link.l1.go = "RedChieftain_3";
			pchar.questTemp.RedChieftain.Eng = "true";
			pchar.questTemp.RedChieftain.AttackNation = ENGLAND;
		break;
		
		case "RedChieftain_3":
			dialog.text = "印第安人因奴役而生病死亡。 白人对印第安人没有怜悯。 鞭打和手枪是白人对印第安人的法律。 我老了。 没有男人去战斗。 开曼阿拉瓦克是和平的民族, 我们发明了和平烟斗。 我请求你, 白人兄弟, 用鞭打和手枪对抗邪恶的白人, 拯救阿拉瓦克印第安人。 ";
			link.l1 = "你是在要求我宣战吗? 酋长, 你必须明白, 我的资源有限。 ";
			link.l1.go = "RedChieftain_4";
		break;
		
		case "RedChieftain_4":
			dialog.text = "不要走上战争之路。 解放印第安人。 我的人民。 我们会把独木舟上所有的神之泪都给你。 杀死邪恶的白人, 帮助印第安人, 获得神之泪, 把它们卖掉换很多很多贝壳串珠。 很多贝壳串珠";
			link.l1 = "啊, 我现在明白了。 不, 卡纳里, 我不能帮助你。 我现在不能这样做 --我的船需要修理, 没有补给了... ";
			link.l1.go = "RedChieftain_wait";
			link.l2 = "既然如此, 我很乐意。 让我们讨论一下细节。 你的人民在哪里? 你说你已经找到他们了... ";
			link.l2.go = "RedChieftain_5";
		break;
		
		case "RedChieftain_wait":
			dialog.text = "咕-呜! 我可以等, 白人兄弟... 我会在这个港口再待一个月, 寻找保护我人民的人。 当你准备好时, 到这里来找我。 ";
			link.l1 = "... ";
			link.l1.go = "RedChieftain_wait_1";
		break;
		
		case "RedChieftain_wait_1":
			DialogExit();
			//LAi_ActorGoToLocator(npchar, "quest", "quest1", "RedChieftainStay", -1);
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			SetFunctionTimerCondition("RedChieftainDelete", 0, 0, 30, false);
			
			sld = CharacterFromID("RedChieftain");
            //LAi_SetStayType(sld);
			sld.dialog.currentnode = "RedChieftain_wait_2";
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity(pchar.questTemp.RedChieftain.StartCity, false);
		break;
		
		case "RedChieftain_wait_2":
			dialog.text = "你回来了, 白人兄弟? 你会帮助我惩罚恶人并拯救印第安人吗? ";
			link.l1 = "我已经准备好了。 ";
			link.l1.go = "RedChieftain_wait_4";
			link.l2 = "我还需要做准备。 ";
			link.l2.go = "RedChieftain_wait_3";
		break;
		
		case "RedChieftain_wait_3":
			dialog.text = "我会在这里等你, 白人兄弟。 ";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.Tempnode = "RedChieftain_wait_2";
		break;
		
		case "RedChieftain_wait_4":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity(pchar.questTemp.RedChieftain.StartCity);
			dialog.text = "我很高兴你同意了, 白人兄弟! ";
			link.l1 = "让我们谈谈细节, 卡纳里。 你的人民在哪里? 你说你已经找到他们了... ";
			link.l1.go = "RedChieftain_5";
			pchar.quest.RedChieftainDelete.over = "yes"; // 移除计时器
		break;
		
		case "RedChieftain_5":
			if (CheckAttribute(pchar, "questTemp.RedChieftain.Spa"))
			{
				AddMapQuestMarkShore("Shore19", true);
				pchar.questTemp.RedChieftain.Island = "Cumana";
				pchar.questTemp.RedChieftain.Shore = "Shore19";
				pchar.questTemp.RedChieftain.Add1 = "西班牙人";
				pchar.questTemp.RedChieftain.Add2 = "卡鲁帕诺峡, 靠近库马纳";
				dialog.text = "他们在靠近西班牙营地库马纳的卡鲁帕诺峡的营地里。 每天他们都乘船出海, 潜入水中, 很深很深... ";
				link.l1 = "我明白了。 西班牙人在他们潜水时监视着他们吗? ";
				link.l1.go = "RedChieftain_6";
			}
			else
			{
				AddMapQuestMarkShore("Shore54", true);
				pchar.questTemp.RedChieftain.Island = "SantaCatalina";
				pchar.questTemp.RedChieftain.Shore = "Shore54";
				pchar.questTemp.RedChieftain.Add1 = "英国人";
				pchar.questTemp.RedChieftain.Add2 = "珍珠角, 靠近布鲁维尔德";
				dialog.text = "他们在靠近英国营地布鲁维尔德的珍珠角扎营。 每天他们都乘船出海, 潜入水中, 很深很深... ";
				link.l1 = "我明白了。 当然, 英国人在监视着他们? ";
				link.l1.go = "RedChieftain_6";
			}
		break;
		
		case "RedChieftain_6":
			dialog.text = "是的, 两艘载有火枪和大刀的白人独木舟。 岸上的营地也有守卫 --印第安人无法逃脱。 ";
			link.l1 = "什么样的船? 你能描述一下吗? 它们有多大? 什么样的帆? ";
			link.l1.go = "RedChieftain_7";
		break;
		
		case "RedChieftain_7":
			dialog.text = "这艘独木舟很大, 但卡纳里见过更大的。 前帆非常倾斜, 像这样做成三个边。 (他在泥土中画出三个三角帆和一个梯形帆) 顶部窄, 底部宽。 ";
			link.l1 = "听起来像双桅纵帆船... ";
			link.l1.go = "RedChieftain_8";
		break;
		
		case "RedChieftain_8":
			dialog.text = "卡纳里不知道那个词。 如果白人看到其他独木舟, 他们会让印第安人上岸, 直到其他独木舟驶离。 ";
			link.l1 = "谨慎的狗娘养的... 我怎么才能接近他们? ";
			link.l1.go = "RedChieftain_9";
		break;
		
		case "RedChieftain_9":
			dialog.text = "如果白人兄弟乘坐小独木舟, 那么他可以偷偷靠近岸边。 我带路。 但只能带一艘小独木舟, 否则白狗会看到并把印第安人从船上赶进丛林... ";
			link.l1 = "明白了。 我需要一艘纵帆船或单桅帆船来执行这个任务。 太好了。 一艘单桅帆船对抗两艘纵帆船... 上帝... 我还以为这会很容易呢! ";
			link.l1.go = "RedChieftain_10";
		break;
		
		case "RedChieftain_10":
			dialog.text = "我们走吗, 白人兄弟? 我们只剩下不到一个月的时间了。 ";
			link.l1 = "是的。 上我的船, 酋长。 我们不要浪费时间! ";
			link.l1.go = "RedChieftain_11";
		break;
		
		case "RedChieftain_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			pchar.quest.Red_Chieftain_2.win_condition.l1 = "location";
			pchar.quest.Red_Chieftain_2.win_condition.l1.location = pchar.questTemp.RedChieftain.Island;
			pchar.quest.Red_Chieftain_2.function = "RedChieftain_CreateShooner";
			if(bImCasual) NewGameTip("探索模式: 计时器未禁用。 请遵守最后期限! ");
			SetFunctionTimerCondition("RedChieftainOver", 0, 0, 30, false);
			AddQuestRecord("RedChieftain", "1");
			AddQuestUserData("RedChieftain", "sText1", pchar.questTemp.RedChieftain.Add1);
			AddQuestUserData("RedChieftain", "sText2", pchar.questTemp.RedChieftain.Add2);
		break;
		
		case "RedChieftain_pearl":
			dialog.text = "谢谢你, 白人兄弟! 你拯救了开曼阿拉瓦克部落! 我们欠你一大笔债。 道路上没有白狗, 印第安人可以在丛林中自由奔跑。 我们把船上剩下的所有神之泪都给你。 ";
			link.l1 = "好吧, 让我们看看你有什么... ";
			link.l1.go = "RedChieftain_pearl_1";
		break;
		
		case "RedChieftain_pearl_1":
			DialogExit();
			pchar.questTemp.RedChieftain.Ind = 1;
			AddDialogExitQuest("RedChieftain_Pearl");
		break;
		
		case "RedChieftain_pearl_give":
			int iSmallPearl = rand(200)+rand(250)+rand(200)+250;
			int iBigPearl = rand(100)+rand(100)+rand(50)+150;
			TakeNItems(pchar, "jewelry52", iBigPearl);
			TakeNItems(pchar, "jewelry53", iSmallPearl);
			PlaySound("interface\important_item.wav");
			Log_SetStringToLog("酋长给了你" + iSmallPearl + "颗小珍珠和" + iBigPearl + "颗大珍珠。 ");
			dialog.text = LinkRandPhrase("我很高兴神之泪属于你, 阿拉瓦克的兄弟! ", "印第安人感谢你, 勇敢的白人! ", "拿着我们的收获吧, 白人兄弟! ");
			link.l1 = LinkRandPhrase("很高兴帮助你! ", "谢谢, 红皮肤的兄弟! ", "太棒了! ");
			link.l1.go = "exit";
			pchar.questTemp.RedChieftain.Ind = sti(pchar.questTemp.RedChieftain.Ind)+1;
			AddDialogExitQuest("RedChieftain_Pearl");
		break;
		
		case "RedChieftain_final":
			chrDisableReloadToLocation = false;//открыть локацию
		// belamour legendary edition -->
			if(sti(pchar.questTemp.RedChieftain.Tartane) > 5)
			{
				dialog.text = "卡纳里再次感谢你, 白人兄弟! 你拯救了所有载有印第安人的独木舟! 对卡纳里来说, 拯救所有独木舟非常重要, 因为你还拯救了卡纳里的孙子, 他被邪恶的白人奴役。 小时候, 我的孙子非常喜欢游泳, 卡纳里给了他这个有魔力的护身符, 这样孙子就不会溺水。 现在孙子不再想游泳了, 把护身符给了我, 让我把它送给你, 白人兄弟。 我希望神之泪和这件礼物能充分回报你对阿拉瓦克生命的拯救。 现在我们说再见 --我们该回到我们的.native village了。 ";
				link.l1 = "祝你好运, 库纳里! 很高兴你的孙子幸存下来! 我祈祷这种邪恶再也不会降临到你身上! ";
				link.l1.go = "RedChieftain_final_1Obereg";
			}
			else
			{
				dialog.text = "卡纳里再次感谢你, 白人兄弟! 我希望神之泪能足够回报印第安人的生命。 现在再见, 我们回native village了。 ";
				link.l1 = "祝你好运, 库纳里! 再也不要陷入奴役了! ";
				link.l1.go = "RedChieftain_final_1";
			}
			if(SandBoxMode)
			{
				//if(CheckAttribute(pchar,"questTemp.SanBoxTarget"))
				//{
					//if(makeint(pchar.questTemp.SanBoxTarget) == 2 ||  makeint(pchar.questTemp.SanBoxTarget) == 5)
					//{
						pchar.questTemp.SanBoxTarget.RedChieftain = true;
						ChangeCharacterComplexReputation(pchar, "fame", 25);
					//}
				//}
			}
		break;
		
		case "RedChieftain_final_1Obereg":
			DialogExit();
			RemovePassenger(Pchar, npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			int n1 = pchar.questTemp.RedChieftain.Tartane;
			for (i=1; i <=n1; i++)
			{
				sld = characterFromId("RC_Indian_"+i);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			}
			InterfaceStates.Buttons.Save.enable = true;
			TakeNItems(pchar, "talisman10", 1);
			PlaySound("interface\important_item.wav");
			Log_Info("你收到了探索者的护身符");
			locations[FindLocation(pchar.questTemp.RedChieftain.Shore)].DisableEncounters = false; //энкаутeры открыть
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50); // 运气
			AddQuestRecord("RedChieftain", "9");
			CloseQuestHeader("RedChieftain");
			DeleteAttribute(pchar, "questTemp.RedChieftain");
		break;
		// <—— legendary edition
		
		case "RedChieftain_final_1":
			DialogExit();
			RemovePassenger(Pchar, npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			int n = pchar.questTemp.RedChieftain.Tartane;
			for (i=1; i <=n; i++)
			{
				sld = characterFromId("RC_Indian_"+i);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			}
			InterfaceStates.Buttons.Save.enable = true;
			locations[FindLocation(pchar.questTemp.RedChieftain.Shore)].DisableEncounters = false; //энкаутeры открыть
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50); // 运气
			AddQuestRecord("RedChieftain", "8");
			CloseQuestHeader("RedChieftain");
			DeleteAttribute(pchar, "questTemp.RedChieftain");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "你想干什么? ";
			link.l1 = "没什么。 ";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
        
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////---------------------------------------—— 奴隶商人 -----------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//--> 皮纳斯
		case "TakeShoreCap":
    		dialog.text = "混蛋! 让你大吃一惊! ";
    		link.l1 = "什么? ";
    		link.l1.go = "Node_1";
		break;
		
		case "Node_1":
			dialog.text = "哈哈! 这里没有奴隶! 你是为了他们来的, 对吗? ";
			link.l1 = "该死。 我还在想为什么这艘贸易轻舟上有这么多士兵... 是个陷阱! ";
			link.l1.go = "Node_2";
		break;
		
 		case "Node_2":
			dialog.text = "是的, 混蛋, 这是个陷阱。 我不是商人, 我是军官! 尽管你赢了战斗, 但你逃不过审判! ";
			link.l1 = "为什么? 我现在就杀了你, 沉了你的船, 没人会知道。 ";
			link.l1.go = "Node_3";
		break;
		
 		case "Node_3":
			dialog.text = "你错了。 你和那个银行家的交易被揭露了。 很快, 总督就会知道你的小动作, 你逃不过绞刑架。 但我会帮你个忙, 现在就在这里杀了你! ";
			link.l1 = "试试吧, 总督的狗! ";
			link.l1.go = "Node_4";
		break;
		
 		case "Node_4":
 		    pchar.questTemp.Slavetrader = "TakeShoreCap_end"; //这是任务状态, 用于任务发布者检查
            AddQuestRecord("Slavetrader", "13");
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
            pchar.quest.Slavetrader_DieHard.over = "yes";
			pchar.quest.Slavetrader_AfterBattle.over = "yes";
			pchar.quest.Slavetrader_ShoreShipsOver.over = "yes";
            Island_SetReloadEnableGlobal(pchar.questTemp.Slavetrader.Island, true);
		    LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Slave_arest":
			dialog.text = "" +GetFullName(pchar)+ ", 以法律的名义, 你被捕了! 放下武器, 跟我们走! ";
			link.l1 = "怎么回事, 军官? 凭什么逮捕我? ";
			link.l1.go = "Slave_arest_1";
		break;
		
		case "Slave_arest_1":
			dialog.text = "别装傻了, 船长! 你肮脏的勾当被揭露了。 因为你犯下的屠杀和击沉" + NationNameGenitive(sti(npchar.nation)) + "的船只, 我们会看着你被绞死! ";
			link.l1 = "好吧, 既然你这么说... 去你妈的! ";
			link.l1.go = "Slave_arest_2";
		break;
		
		case "Slave_arest_2":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorTypeNoGroup(npchar);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		//--> 屋里的老鼠
		case "Rat_bandos":
			dialog.text = "嘿, 你在这里干什么? ! ";
    		link.l1 = "为什么这么无礼, 先生? 那个叫龚蒂埃的老鼠藏在这里吗? ";
    		link.l1.go = "Node_rat_1";
		break;
			
		case "Node_rat_1":
			dialog.text = "不, 他不在! 出去! ";
			link.l1 = "看来你在撒谎。 我要搜查这房子, 看看... ";
			link.l1.go = "Node_rat_2";
		break;
		
 		case "Node_rat_2":
			dialog.text = "去你的! 弗朗索瓦! 快跑! 伙计们, 帮我! ";
			link.l1 = "妈的! ";
			link.l1.go = "Node_rat_3";
		break;
		
		case "Node_rat_3":
            LAi_SetPlayerType(pchar);
            LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Slavetrader_findTortugaRat1");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Rat_lover":
			dialog.text = "哦! 别强奸我! ";
    		link.l1 = "什么... ? 弗朗索瓦.龚蒂埃在哪里? 回答我, 你这个肮脏的荡妇, 否则我就像收拾你那些同伙一样收拾你! ";
    		link.l1.go = "Rat_lover_1";
		break;
			
		case "Rat_lover_1":
			dialog.text = "不, 不, 我什么都告诉你! 他从窗户跳出去, 跑到他的船上了。 ";
    		link.l1 = "什么船? 我知道港口没有他的船。 别骗我, 姑娘, 否则情况会更糟... ";
    		link.l1.go = "Rat_lover_2";
		break;
			
		case "Rat_lover_2":
			dialog.text = "我没撒谎, 我发誓! 他说他在一个小岛登陆, 乘长艇到了这里... 他一定在那里! 别伤害我! ";
    		link.l1 = "好吧, 看来你说的是实话。 待在这里, 安静点。 以后学着用更聪明的方式交朋友。 不过, 我从你眼里看出来, 你没什么脑子。 ";
    		link.l1.go = "Rat_lover_3";
			pchar.quest.Slavetrader_RatAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_RatAttack.win_condition.l1.location = "Tortuga";//送往该地点
            pchar.quest.Slavetrader_RatAttack.function = "Slavetrader_RatCorvette";//创建护卫舰
			if(bImCasual) NewGameTip("探索模式: 计时器未禁用。 请遵守最后期限! ");
			SetFunctionTimerCondition("Slavetrader_RatCorvetteOver", 0, 0, 1, false);
		break;
			
		case "Rat_lover_3":
 		    LAi_SetPlayerType(pchar);
            SetCharacterRemovable(npchar, false);
            LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Slavetrader", "21_9");
            DialogExit();
		break;
		
		//--> 逃跑的奴隶
		case "Slave_woman":
			dialog.text = "饶了我们! 仁慈点! 我们投降! ";
    		link.l1 = "哦, 是吗? 现在到货舱去! 谁敢耍花样我就开枪! ";
    		link.l1.go = "exit";
			AddDialogExitQuestFunction("Slavetrader_Slavewoman");
		break;
	//<--奴隶商人
			
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////---------------------------------------—— 生成器 -----------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//--> 杰森 ----------------------—— 可疑的提议 -------------------------------------------	
		int iCGood;
		case "Contraoffer_patrol":
			chrDisableReloadToLocation = false;
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			pchar.GenQuest.Contraoffer.Trader.PatrolSumm = sti(pchar.GenQuest.Contraoffer.Trader.Summ)/3;
			dialog.text = "嗯, 嗯... 我们在这里发现了什么? 你不知道在我们的殖民地, 与未经授权的人进行货物交易是被禁止的吗? ";
			link.l1 = "是吗, 军官? 说实话, 我第一次听说。 这个法令是最近通过的, 对吗? ";
			link.l1.go = "Contraoffer_patrol_1";
			link.l2 = "什么, 交易" + GetGoodsNameAlt(iCGood) + "? 我没看到任何" + GetGoodsNameAlt(iCGood) + ", 军官。 我只看到这些闪亮的硬币... 他也看到了。 你和你的士兵为什么不也看看我们的硬币? ";
			link.l2.go = "Contraoffer_patrol_pay1";
		break;
		
		case "Contraoffer_patrol_1":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > hrand(120))
			{
				dialog.text = "你不知道, 嗯? 嗯... 看来你没撒谎。 但你仍然违反了法律。 我不会逮捕你, 但我要让你交罚款。 至于货物... 我们会和交易的另一方谈谈。 ";
				link.l1 = "那罚款是多少? ";
				link.l1.go = "Contraoffer_patrol_pay2";
			}
			else
			{
				dialog.text = "别装傻了, 船长! 每个人都已经知道了, 而且已经很久了。 我要以走私罪逮捕你们俩, 你们的货物将被没收。 ";
				link.l1 = "我不喜欢禁闭室, 军官。 我喜欢公海... 而且我现在就要航行到那里。 但看来我只能跨过你的尸体了。 ";
				link.l1.go = "Contraoffer_patrol_fight";
				link.l2 = "我别无选择, 只能投降。 但我真的不知道! ";
				link.l2.go = "Contraoffer_patrol_jail";
			}
		break;
		
		case "Contraoffer_patrol_pay1":
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			if (GetSummonSkillFromName(pchar, SKILL_FORTUNE) > hrand(120))
			{
				dialog.text = "这就对了... 让我看看你的硬币... 我相信, 我听到了一个特定的数字 - " + FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ)) + "。 既然现在我们有三个参与者, 我想要" + FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.PatrolSumm)) + "。 这是你和你朋友的。 ";
				link.l1 = "当然, 军官。 这是我的闪亮硬币, 或者, 对不起, 你的闪亮硬币 - 你刚刚不小心掉在海滩上了... 这里没有" + GetGoodsNameAlt(iCGood) + ", 哈哈, 正如我告诉你的。 ";
				link.l1.go = "Contraoffer_patrol_complete1";
				link.l2 = "哇! 你太贪心了, 军官。 你妈妈没教过你贪心不好吗? 我想我用刀解决你会更便宜。 ";
				link.l2.go = "Contraoffer_patrol_fight";
			}
			else
			{
				dialog.text = "你在开玩笑吗, 船长? 你想贿赂我? 你被捕了! 抓住他! ";
				link.l1 = "好吧, 如果你不想看我的钱, 那就看我的剑! ";
				link.l1.go = "Contraoffer_patrol_fight";
				link.l2 = "我别无选择, 只能投降。 但我真的不知道! ";
				link.l2.go = "Contraoffer_patrol_jail";
			}
		break;
		
		case "Contraoffer_patrol_complete1":
			dialog.text = "是的, 看来你是对的... 这里除了几位先生和我的闪亮硬币外, 没有什么有趣的东西。 你可以走了, 船长, 我们会和你的伙伴谈谈。 ";
			link.l1 = "再见, 军官。 别伤害他。 ";
			link.l1.go = "Contraoffer_patrol_complete";
		break;
		
		case "Contraoffer_patrol_pay2":
			dialog.text = "" + FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.PatrolSumm)) + "。 感谢我的好心情。 ";
			link.l1 = "谢谢你, 军官。 我真的不知道... 给, 我准备好交罚款了。 ";
			link.l1.go = "Contraoffer_patrol_complete2";
			link.l2 = "我看你也不是那么诚实, 军官。 你的罚款太高了。 我想我会帮这个殖民地摆脱你的存在。 ";
			link.l2.go = "Contraoffer_patrol_fight";
		break;
		
		case "Contraoffer_patrol_complete2":
			dialog.text = "很好。 你现在可以走了。 我建议你学习当地法律, 以免将来遇到这种情况。 现在走吧, 我们必须处理这次交易的第二个参与者, 他肯定知道一切。 ";
			link.l1 = "既然如此, 日安, 军官。 ";
			link.l1.go = "Contraoffer_patrol_complete";
		break;
		
		case "Contraoffer_patrol_complete":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Contraoffer.Trader.PatrolSumm));
			AddQuestRecord("Contraoffer", "6");
			CloseQuestHeader("Contraoffer");
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;
		
		case "Contraoffer_patrol_fight":
			AddQuestRecord("Contraoffer", "7");
			CloseQuestHeader("Contraoffer");
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), -5);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorTypeNoGroup(npchar);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Contraoffer_patrol_jail":
			dialog.text = "指挥官会处理你。 跟我来! ";
			link.l1 = "... ";
			link.l1.go = "Contraoffer_patrol_jail_exit";
		break;
		
		case "Contraoffer_patrol_jail_exit":
			GoToPrison(pchar.GenQuest.Contraoffer.Trader.City, sti(pchar.GenQuest.Contraoffer.Trader.Summ), 7);
			DialogExit();
			AddQuestRecord("Contraoffer", "8");
			CloseQuestHeader("Contraoffer");
			pchar.GenQuest.Contraoffer.Jail = "true";
		break;
	//<—— 可疑的提议	
		
	//杰森 --> ---------------------------------—— 不幸的小偷 --------------------------------------------
		case "Device_poorman":
			dialog.text = "日安。 你想要什么? ";
			link.l1 = "我想要, 伙计。 我想你就是我要找的人。 是你从当地造船厂偷了" + pchar.GenQuest.Device.Shipyarder.Type + "? 一切都指向你, 所以别争辩了。 ";
			link.l1.go = "Device_poorman_1";
		break;
		
		case "Device_poorman_1":
			switch (sti(pchar.GenQuest.Device.Shipyarder.Chance3))
			{
				case 0://扔掉了
				if (sti(pchar.GenQuest.Device.Shipyarder.Chance2) != 1)
				{
					dialog.text = "求求你, 大人! 是的, 我从造船厂偷了这个奇怪的东西。 但我没卖掉, 没人需要这种东西。 所以我把它处理掉了。 饶了我吧, 先生, 怪我饿了, 不是我... 否则我绝不会偷东西! ";
					link.l1 = "这是个问题... 我也不需要你。 我需要找到那个" + pchar.GenQuest.Device.Shipyarder.Type + "。 告诉我你把它扔到哪里了? ";
					link.l1.go = "Device_poorman_0_1";
				}
				else //直接交给
				{
					dialog.text = "求求你, 大人! 是的, 我从造船厂偷了这个奇怪的东西。 但我没卖掉, 没人需要这种东西。 我会给你。 给, 拿着, 别伤害我, 别叫士兵! ";
					link.l1 = "好吧, 你可以活下去, 恶棍。 我不需要你的皮, 我需要那个工具。 马上给我, 然后滚! ";
					link.l1.go = "Device_poorman_0_2";
				}
				break;
				case 1://坚持, 狡猾或勇敢
					dialog.text = "你什么意思? " + pchar.GenQuest.Device.Shipyarder.Type + "是什么? 我不明白! ";
					link.l1 = "等我搜你身或搜你的尸体时你就明白了! 现在给我! ";
					link.l1.go = "Device_poorman_1_1";
				break;
				case 2://胆小
					dialog.text = "哦... " + pchar.GenQuest.Device.Shipyarder.Type + "是什么? 我... 它是什么? ";
					link.l1 = "别装傻或逃跑, 我反正会抓住你。 让我检查一下你的口袋... ";
					link.l1.go = "Device_poorman_2_1";
				break;
			}
		break;
		
		case "Device_poorman_0_1"://去寻找
			dialog.text = "就在城门外, 丛林附近。 求求你, 先生! 如果你真的需要那东西, 你可以自己去捡。 它肯定还在那里, 我确定。 ";
			link.l1 = "我应该逼你找到它并带给我, 但我担心找你比找" + pchar.GenQuest.Device.Shipyarder.Type + "花的时间还多。 我自己去。 但如果你骗我, 我会找到你! ";
			link.l1.go = "exit";
			AddQuestRecord("Device", "3");
			string sCity = pchar.GenQuest.Device.Shipyarder.City + "_ExitTown";
			ref rItm = ItemsFromID("Tool");
			rItm.shown = true;
			rItm.startLocation = sCity;
			rItm.startLocator = "item" + (rand(14)+1);
			Log_TestInfo("Device is at the locator " + rItm.startLocator);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Device_poorman_0_2"://得到了设备
			dialog.text = "给, 拿着。 谢谢你, 先生! ";
			link.l1 = "嗯, 这一定是我要找的... 哈! 你现在可以走了。 走吧。 下次小心点。 ";
			link.l1.go = "exit";
			TakeNItems(pchar, "Tool", 1);
			Log_Info("你收到了被盗的工具");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Device", "4");
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Device_poorman_1_1":
			pchar.GenQuest.Device.Shipyarder.Poorsumm = 1000+hrand(1000);
			dialog.text = "听着, 你是在说这个工具吗? 它是我的, 我没有偷! 我不会免费给你。 如果你想要, 给我" + FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Poorsumm)) + "。 ";
			if (sti(pchar.money) >= sti(pchar.GenQuest.Device.Shipyarder.Poorsumm))
			{
				link.l1 = "嗯... 好吧。 我给你。 这是你的硬币, 把工具给我! ";
				link.l1.go = "Device_poorman_1_2";
			}
			link.l2 = "哦, 真的吗? 你真以为我会相信你这个可怜的小偷? 现在把" + pchar.GenQuest.Device.Shipyarder.Type + "给我, 否则我就叫卫兵, 我们一起去造船厂, 看看这工具到底是谁的。 ";
			link.l2.go = "Device_poorman_1_3";
			link.l3 = "你是傻还是怎么了? 听着, 混蛋, 你有两个选择: 要么把" + pchar.GenQuest.Device.Shipyarder.Type + "给我, 要么我捅了你, 从你尸体上拿工具! ";
			link.l3.go = "Device_poorman_1_4";
		break;
		
		case "Device_poorman_1_2":
			dialog.text = "好交易, 船长! 我想我们都会获利, 嘿嘿... 拿着。 ";
			link.l1 = "少说废话, 小偷! 别以为你骗了我, 我只是想和平解决, 少点麻烦。 这些硬币对你也没什么好处。 滚! ";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Device.Shipyarder.Poorsumm));
			TakeNItems(pchar, "Tool", 1);
			Log_Info("你收到了被盗的工具");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Device", "5");
			AddQuestUserData("Device", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Poorsumm)));
			AddQuestUserData("Device", "sName", pchar.GenQuest.Device.Shipyarder.Type);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Device_poorman_1_3":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance2) == 0)//如果我们在城里
			{
				dialog.text = "不! 别叫卫兵! 我... 我会给你这个该死的工具。 给, 拿着! ";
				link.l1 = "现在这样好多了! 现在滚! 否则你早晚会被绞死。 ";
				link.l1.go = "exit_device";
			}
			else//遇到勇敢的
			{
				dialog.text = "什么卫兵, 船长? 这里只有你和我。 你争论太多了, 我得让你冷静下来... 用我的刀。 ";
				link.l1 = "你敢威胁我, 人渣? ! ";
				link.l1.go = "Device_poorman_fight";
			}
		break;
		
		case "Device_poorman_1_4":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance2) == 0)//如果我们在城里
			{
				dialog.text = "啊! 救命! 杀人了! ";
				link.l1 = "站住, 狗东西! ";
			link.l1.go = "exit";
				sld = characterFromId("Device_poorman");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
				sld.lifeday = 0;
				AddQuestRecord("Device", "7");
				CloseQuestHeader("Device");
				DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
			}
			else//遇到勇敢的
			{
				dialog.text = "好吧, 看看谁会捅谁, 船长! ";
				link.l1 = "你敢威胁我, 人渣? ! ";
				link.l1.go = "Device_poorman_fight";
			}
		break;
		
		case "Device_poorman_2_1":
			dialog.text = "搜查? 请吧, 先生! ";
			link.l1 = "现在听着, 要么你和平地把你刚从造船厂偷的东西给我, 要么我带你去指挥官办公室。 你反正会把这东西给我, 但你的脚后跟会先被烧红的烙铁烫。 也许之后他们甚至会绞死你。 你自己选。 ";
			link.l1.go = "Device_poorman_2_2";
			link.l2 = "马上把你偷的东西给我, 混蛋, 否则我就在你站的地方杀了你! ";
			link.l2.go = "Device_poorman_2_3";
		break;
		
		case "Device_poorman_2_2":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 2)//看运气
			{
				dialog.text = "好吧, 如果你想带我去指挥官办公室, 你得先抓住我... ";
				link.l1 = "站住, 狗东西! ";
				link.l1.go = "exit";
				AddQuestRecord("Device", "7");
				sld = characterFromId("Device_poorman");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
				sld.lifeday = 0;
				CloseQuestHeader("Device");
				DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
			}
			else
			{
				dialog.text = "不, 别带我去指挥官办公室! 我自己给! 给, 拿着, 你一定在找这个东西。 反正没人会买... ";
				link.l1 = "嗯, 我想我还是可以带你去堡垒... 好吧, 把工具给我, 滚蛋! ";
				link.l1.go = "exit_device";
			}
		break;
		
		case "Device_poorman_2_3"://恐吓
			dialog.text = "哎哟! 别伤害我, 我把所有东西都给你! 给, 拿着! ";
			link.l1 = "这就对了! 滚吧, 如果我再在这个镇上看到你, 就把你交给指挥官。 再见! ";
			link.l1.go = "exit_device";
		break;
		
		case "exit_device":
			npchar.lifeday = 0;
			TakeNItems(pchar, "Tool", 1);
			Log_Info("你收到了被盗的工具");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Device", "6");
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Device_poorman_fight":
			chrDisableReloadToLocation = true;
			sld = characterFromId("Device_poorman");
			TakeNItems(sld, "Tool", 1);
			sld.SaveItemsForDead = true; // 在尸体上保存物品
			sld.DontClearDead = true; // 200秒后不清除尸体
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			AddQuestRecord("Device", "8");
			AddComplexSelfExpToScill(30, 30, 30, 50);
		break;
	//<—— 不幸的小偷
//-------------------------------------------二级邮政生成器------------------------------------	
		case "PostGopHunters":
			dialog.text = "站住, 伙计! 我们需要你携带的东西。 把它给我们, 然后走你的路。 ";
			link.l1 = "你说的是什么东西? ";
			link.l1.go = "PostGopHunters_1";
			link.l2 = "现在这些街头混混太无礼了... 准备好, 混蛋! ";
			link.l2.go = "PostHunters_fight";
		break;
		
		case "PostGopHunters_1":
			dialog.text = "别装傻瓜! 把包裹给我们, 你就能活下去。 否则... 我们会从你的尸体上拿。 ";
			link.l1 = "你们占优势... 拿着, 混蛋, 我别无选择。 ";
			link.l1.go = "PostGopHunters_2";
			link.l2 = "好吧, 你们可以试试! ";
			link.l2.go = "PostHunters_fight";
		break;
		
		case "PostGopHunters_2":
			dialog.text = "注意你的舌头, 伙计... 你不挑战运气是明智的。 结果还是一样的, 哈哈! 你还能活一会儿... 再见。 ";
			link.l1 = "... ";
			link.l1.go = "exit_gophunter";
		break;
		
		case "PostProfHunters":
			dialog.text = "等等, " + GetAddress_Form(NPChar) + ", 别这么匆忙。 我有笔生意给你。 ";
			link.l1 = "什么生意? 我不认识你。 ";
			link.l1.go = "PostProfHunters_1";
		break;
		
		case "PostProfHunters_1":
			dialog.text = "我认识你, 船长。 现在直奔主题。 你刚刚在" + XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen") + "收到了" + pchar.questTemp.WPU.Current.Add + "。 别否认, 我们很清楚 - 毕竟, 我们已经找这份文件好几天了。 ";
			link.l1 = "现在我明白了。 那又怎样? ";
			link.l1.go = "PostProfHunters_2";
		break;
		
		case "PostProfHunters_2":
			dialog.text = "把包裹给我, 我们的短暂会面就结束了。 别想扮演英雄, 船长, 我们打算拿到这些文件, 而且我们准备好与城市驻军战斗\n如你所知, 如果冲突开始, 你会第一个死。 所以把文件给我们, 我们像朋友一样分手。 ";
			link.l1 = "你们占优势... 拿着, 混蛋, 我别无选择。 ";
			link.l1.go = "PostProfHunters_3";
			link.l2 = "你想吓唬我吗, 我见过比你更有战斗力的小鱼! 滚蛋。 ";
			link.l2.go = "PostProfHunters_4";
		break;
		
		case "PostProfHunters_3":
			dialog.text = "很高兴你很理智, 船长。 你接这个工作把自己置于极大的危险之中。 现在我要离开了, 如果你不介意的话。 ";
			link.l1 = "... ";
			link.l1.go = "exit_profhunter";
		break;
		
		case "PostProfHunters_4":
			dialog.text = "这是你的决定... ";
			link.l1 = "... ";
			link.l1.go = "PostHunters_fight";
			TraderHunterOnMap(false);//如果我们战斗 - 启动追捕AI
		break;
		
		case "PostHunters_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_gophunter":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("PostHunters"+i);	
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			}
			AddQuestRecord("Postcureer", "11");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			DialogExit();
		break;
		
		case "exit_profhunter":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("PostHunters"+i);	
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			}
			AddQuestRecord("Postcureer", "12");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Postcureer", "sSex1", GetSexPhrase("",""));
			pchar.questTemp.WPU.Postcureer.fail = "true";
			DialogExit();
		break;
		
		case "PostAgent":
			bDisableFastReload = true; 
			dialog.text = "等等, " + GetAddress_Form(NPChar) + ", 别这么匆忙。 我有笔生意给你。 ";
			link.l1 = "什么生意? 快说, 我赶时间。 ";
			link.l1.go = "PostAgent_1";
		break;
		
		case "PostAgent_1":
			dialog.text = "我知道你是谁。 我也知道你刚刚在" + XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen") + "收到了" + pchar.questTemp.WPU.Current.Add + "。 这些文件是我渴望与你交谈的原因。 ";
			link.l1 = "我不想和不认识的人讨论这件事。 你想要那些文件吗? 给我一个理由... ";
			link.l1.go = "PostAgent_2";
		break;
		
		case "PostAgent_2":
			dialog.text = "够了, 船长! 我看起来像强盗吗? 我是商人, 代表" + NationNameGenitive(sti(pchar.questTemp.WPU.Postcureer.EnemyNation)) + "的利益。 我想给你一个非常有利可图的交易, 但不是在这里。 我们去酒馆房间讨论这件事。 不会占用你太多时间。 ";
			link.l1 = "这太可疑了... 我不打算和你有任何生意往来, 先生! 滚蛋! ";
			link.l1.go = "PostAgent_getout";
			link.l2 = "嗯.. 让我看看你能给我什么。 但别试图攻击我, 不会有好结果的。 走吧, 我跟着你。 ";
			link.l2.go = "PostAgent_3";
		break;
		
		case "PostAgent_getout":
			dialog.text = "你是个固执愚蠢的人, 船长! 我给了你一个轻松赚钱的机会。 而你... 你会后悔的。 ";
			link.l1 = "滚蛋! ";
			link.l1.go = "PostAgent_getout_exit";
		break;
	
		case "PostAgent_3":
			dialog.text = "太好了! 跟我来。 ";
			link.l1 = "... ";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			NextDiag.TempNode = "PostAgent_inTavern";
			sld = characterFromId("PostAgent");	
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload4_back", pchar.questTemp.WPU.Postcureer.StartCity +"_tavern_upstairs", "goto", "goto1", "PostAgent_inTavern_Room", -1);
		break;
		
		case "PostAgent_getout_exit":
			bDisableFastReload = false; 
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			sld = characterFromId("PostAgent");	
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10);
			pchar.questTemp.WPU.Postcureer.AgentIslandID = GetCharacterCurrentIslandId(pchar);
			pchar.quest.Postcureer_Hunter.win_condition.l1 = "Location";
			pchar.quest.Postcureer_Hunter.win_condition.l1.location = pchar.questTemp.WPU.Postcureer.AgentIslandID;
			pchar.quest.Postcureer_Hunter.function = "PostcureerAgent_ShipAttack";
			AddQuestRecord("Postcureer", "13");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Postcureer", "sSex1", GetSexPhrase("",""));
			DialogExit();
		break;
		
		case "PostAgent_inTavern":
			dialog.text = "现在我们可以自由交谈了。 ";
			link.l1 = "你的提议是什么? ";
			link.l1.go = "PostAgent_inTavern_1";
		break;
		
		case "PostAgent_inTavern_1":
			dialog.text = "正如我所说, 这都是关于你在港口办公室收到的文件。 我所需要的只是它们的副本, 就这样\n你保留原件, 这样他们会为你的工作付钱。 没人会知道发生了什么, 此外我会给你丰厚的报酬。 ";
			link.l1 = "打扰一下... 但包裹是密封的。 你不打破封条就无法复制! ";
			link.l1.go = "PostAgent_inTavern_2";
		break;
		
		case "PostAgent_inTavern_2":
			dialog.text = "我预料到了这个问题。 我必须打破封条, 但别担心, 我会恢复它。 我当然有复制的印章和封蜡。 没人会注意到包裹被打开过。 ";
			link.l1 = "你有" + XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen") + "港口管理局的假印章? ";
			link.l1.go = "PostAgent_inTavern_3";
		break;
		
		case "PostAgent_inTavern_3":
			pchar.questTemp.WPU.Postcureer.AgentMoney = sti(pchar.rank)*3500;
			dialog.text = "你为什么问, 船长? 是的, 我有。 你真以为我只是在玩吗? 我给你" + FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.AgentMoney)) + ", 让我看看这些文件。 那么, 你终于会把包裹给我吗? 求你了。 ";
			link.l1 = "拿着, 但我需要它们被密封归还! ";
			link.l1.go = "PostAgent_inTavern_4";
			link.l2 = "你知道, 我不会。 我不喜欢这样。 ";
			link.l2.go = "PostAgent_inTavern_getout";
		break;
		
		case "PostAgent_inTavern_4":
			dialog.text = "别担心。 我是专业人士。 坐下休息一下。 大约需要一个小时。 ";
			link.l1 = "好的。 ";
			link.l1.go = "PostAgent_inTavern_5";
		break;
		
		case "PostAgent_inTavern_5":
			NextDiag.currentnode = "PostAgent_inTavern_6";
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			pchar.questTemp.WPU.Postcureer.AgentChance = hrand(4);//被揭穿的概率 - 20%
			DialogExit();
			AddDialogExitQuest("PostAgent_inTavern_Room_end");
		break;
		
		case "PostAgent_inTavern_getout":
			dialog.text = "嗯... 我没料到。 你太固执了, 船长, 所以我必须在这里杀了你, 免费拿走包裹。 祈祷吧, 因为我用刀和用假印章一样好。 ";
			link.l1 = "应该祈祷的是你, 间谍! ";
			link.l1.go = "PostAgent_inTavern_fight";
		break;
		
		case "PostAgent_inTavern_6":
			dialog.text = "完成了。 正如我所说, 做得非常准确。 拿着包裹和承诺的" + FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.AgentMoney)) + "。 我得走了。 祝你好运, 船长, 很高兴我们达成了交易。 ";
			link.l1 = "再见... ";
			link.l1.go = "PostAgent_inTavern_7";
		break;
		
		case "PostAgent_inTavern_7":
			DialogExit();
			bDisableFastReload = false;
			chrDisableReloadToLocation = false; 
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Postcureer.AgentMoney));
			GiveItem2Character(pchar, pchar.questTemp.WPU.Current.Item);
			sld = characterFromID("PostAgent");        
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 2);
			AddQuestRecord("Postcureer", "15");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.AgentMoney)));
		break;
		
		case "PostAgent_inTavern_fight":
			bDisableFastReload = false;
			sld = characterFromID("PostAgent"); 
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			AddQuestRecord("Postcureer", "16");
		break;
	//<—— 二级邮政生成器
		
	// --> -------------------------------—— 二级护送 --------------------------------------------------
		case "DisasterCap":
			dialog.text = "问候! 哦, 真高兴见到你! ";
			link.l1 = "日安。 嗯, 告诉我, 你不是" + pchar.questTemp.WPU.Escort.ShipName + "的指挥官吗? ";
			link.l1.go = "DisasterCap_1";
		break;
		
		case "DisasterCap_1":
			dialog.text = "哦! 你怎么知道" + pchar.questTemp.WPU.Escort.ShipName + "的? 是的, 我是她的船长。 或者说曾经是... 船在离这里不远的地方沉没了。 ";
			link.l1 = "啊, 那我找到你了... 让我自我介绍一下 - " +GetFullName(pchar)+ "。 我是应" + XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen") + "港口主任的要求来的。 他简要告诉我你们商队的麻烦, 并派我来找你们的船。 ";
			link.l1.go = "DisasterCap_2";
		break;
		
		case "DisasterCap_2":
			dialog.text = "那么你是救援队伍的船长? ";
			link.l1 = "差不多。 我的任务是找到你们的船, 或者证明她沉没了或无法航行。 不幸的是, 我没有找到船, 但船长还活着, 这肯定是件好事... ";
			link.l1.go = "DisasterCap_3";
		break;
		
		case "DisasterCap_3":
			dialog.text = "哦, 对不起, 我忘了介绍自己。 我是" + GetFullName(npchar) + "。 你已经知道我们是怎么到这里的吗? 风暴使我们的船失控\n几天后, 她在这个海湾附近触礁, 狂风在几分钟内摧毁了她。 我的船员只有几十人幸存。 其余的都沉到了海底。 我们每天都为他们的灵魂祈祷... ";
			link.l1 = "接受我的哀悼, " + GetFullName(npchar) + "船长。 我很抱歉。 ";
			link.l1.go = "DisasterCap_4";
		break;
		
		case "DisasterCap_4":
			dialog.text = "谢谢你... 幸存者在岸边建立了一个营地, 希望得到援助。 你来得正是时候, 船长! 当地好战的印第安人知道我们的存在, 如果他们攻击我们, 我们无法抵挡数百人\n还有一艘海盗船在这一地区巡航, 看起来他们在找我们。 你见过这个海盗吗, 船长? ";
			link.l1 = "不, 我没有。 ";
			link.l1.go = "DisasterCap_5";
		break;
		
		case "DisasterCap_5":
			dialog.text = "谢天谢地。 他是暴风雨前攻击我们的人之一。 像鬣狗一样, 他渴望完成受伤的猎物, 所以他来到了这个岛。 ";
			link.l1 = "我明白了。 现在是时候决定我们下一步做什么了。 ";
			link.l1.go = "DisasterCap_6";
		break;
		
		case "DisasterCap_6":
			dialog.text = "决定什么, 船长? 让我们上船, 离开这个诅咒的地方。 ";
			link.l1 = "绝对的。 我没能救船, 至少我会救她的船员。 收拾营地, 我会命令派长艇来这里。 欢迎上船! ";
			link.l1.go = "DisasterCap_7";
		break;
		
		case "DisasterCap_7":
			PlaySound("people fight\rifle_fire1.wav");
			PlaySound("people fight\player_man_shoot_01.wav");
			dialog.text = "谢谢, 船长! 不会太久。 等等... 什么鬼? 啊! 那些红皮肤的魔鬼又来找我们了! 警报! 准备战斗! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DisasterShipCrew_IndianAttack");
		break;
		
		case "DisasterCap_8":
			dialog.text = "呼, 我们成功了... 看, 船长, 我告诉过你这个海湾是地狱! 这已经是第三次印第安人攻击了! 我们必须尽快离开这里, 我们无法再承受一次攻击。 ";
			link.l1 = "是的, 你说得对。 集合所有活着的人, 到我的船上去! 我会立即命令派长艇来! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DisasterShipCrew_onBoard");
			AddQuestRecord("Escort", "38");
			AddQuestUserData("Escort", "sIsland", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID));
			AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
			AddQuestUserData("Escort", "sShore", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID.Shore));
		break;
	// <—— 二级护送
		
	//杰森 --> ------------------------—— 讨厌的贵族 ------------------------------------------------
		case "Badboy":
			dialog.text = "嗝... 你想从我这里得到什么? 滚开, 我不想和你说话。 ";
			link.l1 = "你是" + pchar.GenQuest.Badboy.Brothel.Name + "吗? ";
			link.l1.go = "Badboy_1";
		break;
		
		case "Badboy_1":
			dialog.text = "是的, 我是。 你有什么事? ";
			link.l1 = "很简单。 这个镇上有人受够了你的把戏。 这个人受够了。 现在我看着你, 我知道为什么。 别再出现在当地的妓院里, 否则你会有麻烦。 明白了吗? ";
			link.l1.go = "Badboy_2";
		break;
		
		case "Badboy_2":
			switch (sti(pchar.GenQuest.Badboy.Brothel.Type))
			{
				case 0://要么被吓到, 要么会反抗 - 取决于领导力
					if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 30)
					{
						dialog.text = "啊! 你... 敢威胁我, 混蛋? 我要把你钉在我的刀上, 把你像鸡一样烤在烤架上! ";
						link.l1 = "准备好, 混蛋! ";
						link.l1.go = "Badboy_fight_1";
						NextDiag.currentnode = "Badboy_after_fight";
					}
					else
					{
						dialog.text = "什么? 什么把戏? 没有什么把戏。 我喝醉了, 在妓院里狂欢了几次。 人无完人... 好吧, 好吧, 好吧... 我再也不会用他们的服务了。 现在满意了吗? 我向你保证。 ";
						link.l1 = "我希望荣誉对你来说意味着什么, 你也知道违背它的后果。 记住这一点。 现在再见。 ";
						link.l1.go = "exit";
						pchar.GenQuest.Badboy.Complete = "true";
						LAi_CharacterDisableDialog(npchar);
						npchar.lifeday = 0;
					}
				break;
				case 1://城外决斗
					dialog.text = "你真是个无礼的人, 先生! 我发誓, 日落前我会让你后悔你的话。 我挑战你! 我想我们最好私下战斗, 在安静的地方。 丛林就很好, 两小时后在那里见! ";
					link.l1 = "好主意! 至少藏你的尸体不会有问题。 ";
					link.l1.go = "Badboy_duel";
					NextDiag.currentnode = "Badboy_duel_1";
					break;
				case 2://叫来朋友帮忙
					dialog.text = "什么? 什么把戏? 没有任何把戏。 我喝醉了, 在妓院里狂欢了几次。 人无完人... 好吧, 好吧, 好吧... 我再也不会用他们的服务了。 现在满意了吗? 我向你保证。 ";
					link.l1 = "我希望荣誉对你来说意味着什么, 你也知道违背它的后果。 记住这一点。 现在再见。 ";
					link.l1.go = "exit_continue";
					pchar.GenQuest.Badboy.Continue = "true";
					NextDiag.currentnode = "Badboy_friends";
				break;
			}
		break;
		
		case "Badboy_fight_1":
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			sld = characterFromId("Badboy");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_SetCheckMinHP(npchar, 10.0, true, "Badboy_capture");
			DialogExit();
		break;
		
		case "Badboy_after_fight":
			dialog.text = "等等! 住手! 我投降! 饶了我! ";
			link.l1 = "现在你才这样说! ";
			link.l1.go = "Badboy_after_fight_1";
		break;
		
		case "Badboy_after_fight_1":
			dialog.text = "我求你, 求求你, 饶了我! 我会按你说的做! 我再也不会出现在那个妓院了! ";
			link.l1 = "这种姿态只适合你这样的人渣。 我希望这会成为你余生的教训。 在这个镇上规矩点。 ";
			link.l1.go = "Badboy_exit";
			link.l2 = "当然, 你不会。 你的诡计在这里就结束了。 ";
			link.l2.go = "Badboy_killed";
			pchar.GenQuest.Badboy.Complete = "true";
		break;
		
		case "Badboy_exit":
			LAi_SetPlayerType(pchar);
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			DialogExit();
		break;
		
		case "Badboy_killed":
		DialogExit();
		LAi_SetImmortal(npchar, false);
			//  belamour legendary edition 如果没戴手枪或步枪, 就给把制式 -->
			if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE))
			{
				GiveItem2Character(pchar, "pistol1");
				EquipCharacterbyItem(pchar, "pistol1");
			}
			// <—— legendary edition
		LAi_ActorAnimation(pchar, "shot", "Badboy_killed_end", 2.2);
		break;
		
		case "Badboy_duel":
			chrDisableReloadToLocation = true;//关闭地点
			LAi_LocationDisableOfficersGen(pchar.GenQuest.Badboy.Brothel.City + "_ExitTown", true);//不让军官进入
			locations[FindLocation(pchar.GenQuest.Badboy.Brothel.City + "_ExitTown")].DisableEncounters = true; //关闭遭遇战
			pchar.quest.BadboyDuelTimer.win_condition.l1 = "Timer";
			pchar.quest.BadboyDuelTimer.win_condition.l1.date.hour  = sti(GetTime() + 2);
			pchar.quest.BadboyDuelTimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.BadboyDuelTimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.BadboyDuelTimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.BadboyDuelTimer.function = "Badboy_duelstart";
			sld = characterFromId("Badboy");
			LAi_SetActorType(sld);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			TakeNItems(sld, "jewelry5", rand(10)); 
			TakeNItems(sld, "jewelry3", rand(10)); 
			TakeNItems(sld, "jewelry1", rand(10)); 
			sld.money = 24560;
			sld.SaveItemsForDead = true; // 在尸体上保存物品
			sld.DontClearDead = true; // 200秒后不清除尸体
			LAi_RemoveLoginTime(sld); //删除登录时间
			SetFunctionTimerCondition("Badboy_duelOver", 0, 0, 1, false);
			DialogExit();
		break;
		
		case "Badboy_duel_1":
			dialog.text = "是时候下地狱了, 混蛋! 为自己祈祷吧, 但动作快点, 我没时间浪费... ";
			link.l1 = "少说废话, 多打斗, 人渣! ";
			link.l1.go = "Badboy_duel_2";
		break;
		
		case "Badboy_duel_2":
			chrDisableReloadToLocation = true;
			LAi_SetPlayerType(pchar);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "Badboy_die");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_continue":
			sld = characterFromID("Badboy");        
			LAi_RemoveLoginTime(sld); // patch-6
			LAi_SetActorType(sld);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
			DialogExit();
		break;		
		
		case "Badboy_friends":
			dialog.text = "他在那儿, 这个无礼的混蛋! 让我们让他看看谁是这个镇的主人, 伙计们! ";
			link.l1 = "啊, 你真是个堕落的人! 但我警告过你。 你和你的猿猴们马上就会被送到地狱! ";
			link.l1.go = "Badboy_friends_fight";
		break;
		
		case "Badboy_friends_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			DeleteAttribute(pchar, "GenQuest.Badboy");
		break;
	//杰森 <—— 讨厌的贵族
		
	//杰森 --> -----------------------------—— 阳光之地 ----------------------------------------------
		case "Sunplace_Store":
			pchar.quest.SunplaceContinue_Over.over = "yes";
			dialog.text = "问候。 你想要什么? ";
			link.l1 = "你不是" + pchar.GenQuest.Sunplace.Trader.Enemyname + "吗? 你不会相信我, 哈哈。 我想要你的头。 ";
			link.l1.go = "Sunplace_Store_1";
			link.l2 = "嗯... 不... 没什么。 看来我认错人了。 打扰了。 ";
			link.l2.go = "Sunplace_Store_exit";
		break;
		
		case "Sunplace_Store_1":
			dialog.text = "多么愚蠢的笑话, 先生! 解释一下, 否则我会... ";
			link.l1 = "你要做什么, 可怜的鲱鱼? 你伤害了一个好人, 他很不高兴。 所以现在祈祷吧, 动作快点, 因为我赶时间。 ";
			link.l1.go = "Sunplace_Store_3";
		break;
		
		case "Sunplace_Store_3":
			dialog.text = "什么... 你在做什么, 先生! 救命! 有人吗! 杀人了! ";
			link.l1 = "我还以为你会把最后几秒用来祈祷, 至少你还有机会上天堂... ";
			link.l1.go = "Sunplace_Store_fight";
		break;
		
		case "Sunplace_Store_exit":
			sld = CharacterFromID("SunplaceTrader");
			sld.lifeday = 0;
			AddQuestRecord("Sunplace", "9");
			CloseQuestHeader("Sunplace");
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Sunplace.Trader");
			NextDiag.currentnode = "Sunplace_Store_repeat";
		break;
		
		case "Sunplace_Store_repeat":
			dialog.text = "又是你? 为什么不告诉我你想要什么? ";
			link.l1 = "没什么。 ";
			link.l1.go = "exit";
		break;
		
		case "Sunplace_Store_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			sld = CharacterFromID("SunplaceTrader");
			LAi_SetImmortal(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorAfraid(sld, Pchar, true);
			sld = characterFromId(pchar.GenQuest.Sunplace.Trader.CityT + "_trader");
			LAi_group_Attack(sld, Pchar);
			pchar.quest.Kill_SunplaceTrader.win_condition.l1 = "ExitFromLocation";
			pchar.quest.Kill_SunplaceTrader.win_condition.l1.location = pchar.location;
			pchar.quest.Kill_SunplaceTrader.function = "Kill_SunplaceTrader";
		break;
	// <—— 阳光之地
		
	//-----------------------------------—— 联盟杀手 -------------------------------------------------------
		case "LigaHunters":
			dialog.text = "";
			link.l1 = "啊? ! 什么? 你们在这里干什么, 该死的? 谁让你们进来的? ";
			link.l1.go = "LigaHunters_1";
		break;
		
		case "LigaHunters_1":
			dialog.text = "联盟需要你的命, 船长... ";
			link.l1 = "什么? 操! ";
			link.l1.go = "LigaHunters_2";
		break;
		
		case "LigaHunters_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("LigaHunter_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "LigaHunters_Dead");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
	// <—— 联盟杀手
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//关于公民看到裸露武器的评论
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
			dialog.text = NPCharSexPhrase(NPChar, "听着, 我是这个镇的公民, 我请你把刀收起来。 ", "听着, 我是这个镇的公民, 我请你把刀收起来。 ");
			link.l1 = LinkRandPhrase("好的。 ", "好的。 ", "当然... ");
			link.l1.go = "exit";
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "小心, " + GetSexPhrase("伙计", "姑娘") + ", 带着武器跑。 我会紧张... ", "我不喜欢有" + GetSexPhrase("男人", "人") + "拿着武器走在我前面。 这让我害怕... ");
				link.l1 = LinkRandPhrase("我知道了。 ", "没关系。 ", "别担心... ");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
			if (npchar.id == "Device_poorman") NextDiag.TempNode = "Device_poorman";
		break;
	}
}
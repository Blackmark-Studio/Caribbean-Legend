// BOAL 新的副官和同伴对话 21/06/06
void ProcessDialogEvent()
{
	ref NPChar, d;
	aref Link, Diag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);
	
	ref    	sld, rItm, rItem;
	string 	attr, attrLoc, sGun, sBullet, attrL, sAttr;
	int    	iTemp, iTax, iFortValue, i;
	aref 	rType;
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // 索引在末尾
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // 索引在末尾
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
        case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = RandPhraseSimple("嘿, 船长, 此刻一半的驻军都在追你。 现在肯定不是加入你船员的最佳时机! ", "还要一路杀回船上? 不, 船长, 换个时间吧... ");
				link.l1 = RandPhraseSimple("如你所愿... ", "其实, 我本来也没打算雇你。 "); 
				link.l1.go = "exit";
				break;
			}
			Diag.TempNode = "OnceAgain";
			dialog.text = "你需要一名副官吗, 船长? ";
			if (FindFreeRandomOfficer() > 0)
			{
    			Link.l1 = "一名副官? 你擅长什么? ";
    			Link.l1.go = "Node_2";
			}
			Link.l2 = "不, 我已经满员了。 ";
			Link.l2.go = "Exit";			
		break;
		
		case "CitizenNotBlade":
			dialog.text = "船长, 你在做什么? 把武器收起来, 免得惹出大麻烦! ";
			link.l1 = LinkRandPhrase("好吧。 ", "好吧。 ", "别担心, 我正在收起来... ");
			link.l1.go = "exit";
		break;
		
		case "hired":
			Diag.TempNode = "Hired";
			// 刚刚雇佣 -->
			if (IsCompanion(NPChar))
			{
				Dialog.text = "今天, 我们终于要起航了! ";
				link.l2 = "是啊... 我很高兴。 ";
				link.l2.go = "Exit";
				break;
			}
			if (Npchar.location.group == "sit" && !isShipInside(pchar.location))
			{
				dialog.text = "我先喝完这杯酒, 船长, 然后就去船上。 别担心 - 我会及时到的。 ";
				Link.l1 = "好的。 如果你迟到, 我就让你擦甲板! ";
				Link.l1.go = "Exit";
				break;
			}
			// 刚刚雇佣 <--
   			dialog.text = "你想要什么, 船长? ";
			// 船上同伴的对话.
			if (CheckAttribute(NPChar, "IsCompanionClone"))
			{
				Link.l2 = "我需要给你下达几个命令。 ";
				Link.l2.go = "Companion_Tasks";
				break;
			}
			
			// 在泰亚萨尔
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l66 = ""+npchar.name+", 我要去泰亚萨尔的一个古老印第安城镇。 这将是一次危险且不寻常的旅程 - 通过一个传送神像。 你愿意和我一起吗? ";
				if(npchar.id == "Folke")
				{
					Link.l66 = ""+npchar.name+", 我有一个严肃的请求给你 - 一个真正的交易, 虽然 suicidal ( suicidal 直译: 自杀式的, 这里意译为'九死一生') 但该死的有利可图。 我需要一个忠诚的人去一个古老的印第安城市执行任务。 你跟我来吗? ";
				}
				if(npchar.id == "Duran")
				{
					Link.l66 = "克劳德, 你曾经抱怨雇佣兵薪水太低。 ";
				}
				Link.l66.go = "tieyasal";
			}
			
			if (isOfficer(Npchar)) // 校园的检查, 那里是槽位副官
			{
				Link.l2 = "现在听我的命令! ";
				Link.l2.go = "stay_follow";
			}

           		// boal 船舶报告
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l8 = "给我一份全面的船舶报告, " + GetStrSmallRegister(XI_ConvertString("treasurer")) + "。 ";
			    Link.l8.go = "QMASTER_1";
			        
			    // 战舰。 自动采购货物
			    if(!CheckAttribute(PChar, "TransferGoods.Enable"))
			    {
				    Link.l11 = "我希望你在我们停留在殖民地期间采购货物。 ";
				    Link.l11.go = "TransferGoodsEnable";
			    }
			    else
			    {
				    Link.l11 = "你知道, 我们不再需要在殖民地采购货物了。 ";
				    Link.l11.go = "TransferGoodsDisable";
			    }
			}
			
			if (pchar.location != "My_Campus") // patch-5
			{
			Link.l4 = "副官, 不再需要你的服务了。 ";
			Link.l4.go = "AsYouWish";
			}
			
			
			// 根据当前位置确定是否可以在这里下令 -->
			if(IsEntity(&loadedLocation))
			{
				if(CheckAttribute(loadedLocation, "fastreload"))
				{
					iTemp = FindColony(loadedLocation.fastreload);
					if(iTemp != -1)
					{
						sld = GetColonyByIndex(iTemp);
						if(sti(sld.HeroOwn) == true && !CheckAttribute(sld, "OfficerIdx"))
						{
							NPChar.ColonyIdx = iTemp;
							Link.l7 = "我任命你为这个城镇的副手! ";
							Link.l7.go = "Gover_Hire";
						}
					}
				}
			}
			
			Link.l9 = "没什么。 稍息! ";
			Link.l9.go = "Exit";
		break;
		
		// 泰亚萨尔
		case "tieyasal":
			if(npchar.id == "Folke")
			{
				dialog.text = "该死的, 船长! 我以为你一有机会就会摆脱我, 但你总是让我惊讶。 我当然跟你去, 谢谢你给这个白痴真正的海狼生活! ";
				Link.l1 = "好样的, "+npchar.name+"! ";
				Link.l1.go = "folke_tieyasal";
				break;
			}
			if(npchar.id == "Duran")
			{
				dialog.text = "嗯? 我真的说过吗? ";
				Link.l1 = "你说过。 那时我仔细听了, 现在准备纠正这个不公。 ";
				Link.l1.go = "Duran_tieyasal";
				break;
			}
			dialog.text = LinkRandPhrase("抱歉, 船长, 但这不是我签约的内容。 别以为我是懦夫, 但我不想去面对必然的死亡。 我还没活够 - 至少现在没有。 如果你愿意, 可以解雇我。 ","船长, 恕我直言 - 不。 海洋。 登船。 敌城 - 都没问题, 但我不想碰那些印第安巫术。 如果你对我的回答不满, 可以取消我们的合同。 ","你想要不可能的事, 船长, 你也知道。 没人能活着回来, 包括你, 所以我放弃。 如果你认为我的拒绝违反了合同条款, 可以取消它。 ");
			link.l1 = LinkRandPhrase("我不怪你, 副官。 我完全理解。 ","可惜, 但我能理解你。 这就是为什么我事先告诉你。 ","我本来指望你... 但我能理解你的立场, 副官。 ");
			link.l1.go = "tieyasal_1";
		break;
		
		case "Duran_tieyasal":
			dialog.text = "嘿! 那你会给我加薪吗? ";
			Link.l1 = "没门! 我要去一个古老的印第安城市。 这工作九死一生, 但那里会有黄金... ";
			Link.l1.go = "Duran_tieyasal_2";
		break;
		
		case "Duran_tieyasal_2":
			dialog.text = "我对黄金不感兴趣。 我很荣幸帮助你, 船长, 就像你曾经帮助我一样。 我们什么时候出发? ";
			Link.l1 = "说得好, 克劳德! 做好充分准备 - 不会太久了。 ";
			Link.l1.go = "Duran_tieyasal_3";
		break;
		
		case "Duran_tieyasal_3":
			DialogExit();
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "folke_tieyasal":
			Achievment_Set("ach_CL_108");
			DialogExit();
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "tieyasal_1":
			DialogExit();
			npchar.quest.Tieyasal = "true";
		break;
		
		case "TransferGoodsEnable":
			if(sti(PChar.Ship.Type) == SHIP_NOTUSED)
	        {
				dialog.text = "船长, 什么货物? 我们首先需要找到一艘船! ";
				Link.l1 = "是的, 你说得对。 ";
				Link.l1.go = "Exit";
				Diag.TempNode = "Hired";
				break;
	        }
	        	
			PChar.TransferGoods.Enable = true;
		//	PChar.TransferGoods.TreasurerID = NPChar.id;
			Dialog.text = "遵命, " + GetSexPhrase("先生","小姐") + "船长! ";
			Link.l1 = "稍息。 ";
			Link.l1.go = "TransferGoodsEnable_2";
        break;
        	
		case "TransferGoodsEnable_2":
			Diag.CurrentNode = "Hired";
			DialogExit();
			LaunchTransferGoodsScreen(); // 货物自动采购界面
		break;
		
		case "TransferGoodsDisable":
			DeleteAttribute(PChar, "TransferGoods.Enable");
			Dialog.text = "遵命, " + GetSexPhrase("先生","小姐") + "船长! ";
			Link.l1 = "稍息。 ";
			Link.l1.go = "exit";
			Diag.TempNode = "Hired";
		break;
        
		case "ShowParam_exit":
			Diag.CurrentNode = "OnceAgain";
			NPChar.quest.meeting = true;
			DialogExit();
			
			PChar.SystemInfo.OnlyShowCharacter = true;
            LaunchCharacter(NPChar);
		break;
		
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();			
		break;

		case "exit_hire":
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
			if(CheckAttribute(pchar,"systeminfo.tutorial.Fighter") && Npchar.quest.officertype == "fighter")
			{
				DeleteAttribute(pchar,"systeminfo.tutorial.Fighter");
				LaunchTutorial("Fighter", 1);
			}
		break;

		case "exit_fire":
			//navy -->
			if (CheckAttribute(NPChar, "PGGAi"))
			{
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();			
				break;
			}
			//navy <--
			Diag.TempNode = "Fired";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");

			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;

			DialogExit();			
		break;
		
		// boal 29.05.04 副官想离开 -->
        case "WantToGo":
			if (npchar.id == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_SobytieKlodDuran"))
			{
				SetTimerCondition("SKD_DuranTavern", 0, 0, 30, false);
				pchar.questTemp.SKD_SobytieKlodDuran = true;
			}
			chrDisableReloadToLocation = false;
			Diag.TempNode = "Hired";
			dialog.text = LinkRandPhrase(LinkRandPhrase("船长, 你知道, 我... 嗯, 我想请你解除我的职务。 是时候安定下来, 结婚生子了。 我仍然没有自己的家, 等我老了, 没人会给我端杯水。 ","船长, 请让我辞职。 这些年来我一直在世界各地漂泊, 却什么也没真正见过。 我只想过一种新生活, 抛锚上岸, 从不同的角度看看这个世界。 ","船长, 海军服役固然是好事, 有不错的收益和冒险, 但现在是时候为自己考虑了。 你知道, 在一个安静的港口抛锚, 买个房子, 生儿育女。 请让我走吧。 "), LinkRandPhrase("船长, 你知道, 我真的很抱歉, 但我受够了所有这些职责。 值班和纪律。 你知道, 我只想至少暂时过一种自由的生活, 但我意识到你不会等我, 所以... 你能解雇我吗? ","船长, 你知道... 有一艘我买得起的小船, 所以... 我想可能是时候开始自己的生意了。 请让我走吧? ","船长, 我刚刚在港口得到一个职位。 实际上, 我渴望抛锚安定下来过婚姻生活已经有一段时间了。 请允许我离开。 我真的不能错过这样的机会。 "), LinkRandPhrase("船长, 我真的晕船。 医生一直说这是特质。 看在上帝的份上, 请让我走吧, 否则我迟早会跳海的。 ","船长, 我想是时候安定下来找个更安静的地方了。 你知道, 我害怕。 害怕流弹, 害怕在登船时死去。 我祈祷上帝保佑我活着, 当我闭上眼睛, 我看到所有我杀死的无辜灵魂。 他们在乞求我放过他们... 请发发慈悲, 让我走吧。 ","船长, 我的旧伤在痛, 最近的挫伤每天都在提醒我。 很快你就会解雇我, 之后谁会雇佣我呢? 请让我走, 我会养好伤, 找个更安静的地方。 "));
			Link.l1 = RandPhraseSimple(LinkRandPhrase("他们最终都会离开。 好吧, 你自由了。 ","我能理解你的理由。 凡事迟早都会结束。 好吧, 走吧... 如果我曾经冒犯过你, 请不要记恨。 ","又是这样? 你故意选了最不合时宜的时机离开, 对吧? 不管怎样。 再见。 "), LinkRandPhrase("很难相信你说的话... 好吧, 收拾东西走吧。 ","你? 我没想到... 经过这么多背靠背的战斗... 好吧, 我不拦你。 祝你好运。 ","你听起来很认真。 好吧, 祝你好运, 知道我会想念你。 "));				
			Link.l1.go = "WantToGo_free";
			if (sti(Pchar.money) >= sti(NPChar.rank)*250)
			{
				Link.l2 = LinkRandPhrase("我明白了... 原来是这样啊? 而我还指望你... 好吧, 如果你已经下定决心, 那我们就分道扬镳。 拿上" + sti(NPChar.rank)*250 + "比索作为你忠诚服务的报酬。 如果我曾经冒犯过你, 请不要记恨。 ", "好吧, 我不记恨也不记仇。 如果这是你的决定, 那就走吧。 拿上" + sti(NPChar.rank)*250 + "比索重新开始, 肯定会有用的。 ", "我明白了... 迟早会发生的。 我给你" + sti(NPChar.rank)*250 + "比索安顿生活。 也要照顾好你的健康, 海军服役充满艰辛... "); 
				Link.l2.go = "Im_kind_A2_1";
			}
			Link.l3 = LinkRandPhrase("所以你说... 你没意识到现在离开简直是在背后捅我一刀吗? 我现在不能让你走, 想都别想。 ", "这可是新闻! 你知道, 这种事应该提前通知我! 所以暂时忘了你的私人生活吧。 等时候到了, 我会建议你什么时候退休。 ", "不准辞职。 我把每个人都记在账上。 我不能让每个人都因为个人意愿就离开。 服役, 直到我认为你值得休假。 ");	
			Link.l3.go = "WantToGo_Stay";
		break;
		
		case "Im_kind_A2_1":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*250)));
			ChangeOfficersLoyality("good_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			dialog.text = "谢谢你, 船长! 真是意想不到的慷慨... 你知道, 我还有一些你的东西, 也许你想拿回去? ";
			Link.l1 = "也许... 现在找一把好刀不容易。 ";
			Link.l1.go = "Get_out_А2_chang";
			Link.l2 = "哦, 别麻烦了。 留着作为你服务的纪念吧。 ";
			Link.l2.go = "WantToGo_free";
		break;
		
		case "WantToGo_Stay":
			dialog.text = RandPhraseSimple("但怎么会这样, 船长? 即使是奴隶最终也会被送到岸上。 而我不是奴隶, 所以我可以决定自己的命运! ", "船长, 我一直忠实地为你服务。 我难道不该有权决定自己的命运吗? ");
			Link.l1 = LinkRandPhrase("我明白我现在留不住你。 好吧, 来点经济支持怎么样? 这不会有坏处, 你可以用这笔钱在安静的港口建一个舒适的家或照顾你的健康。 ", "好吧, 我们这样说。 你想要多少金额才能重新考虑你的决定? ", "你说得对。 但一次性的金钱补贴呢, 会改变你的想法吗? ");
			Link.l1.go = "WantToGo_Stay_2";
			Link.l2 = PCharRepPhrase(	
				RandPhraseSimple("哦, 不, 我的朋友, 你错了... 当你在酒馆里追着酒杯浪费时间时, 你可以自己做决定, 但一旦你踏上我的船, 你就把命运交到了我手中。 ", "嗯。 现在, 这是一个严肃的声明。 显然, 你忘了我是怎么在一个臭酒馆里找到你的, 口袋里连一个铜板都没有。 你甚至不能拿出一枚金币, 因为你会立刻把它变成朗姆酒.'决定我的命运...'噗! 真是个笑话! "),
				LinkRandPhrase("当你在我手下服务时, 由我做决定。 现在请你回到你的岗位, 在你太惹我生气之前! ", "嗯。 现在, 这是一个严肃的声明。 但你还没有还清预支给你的所有钱。 所以你的行为可以被视为勒索, 对吗? ", "哦, 我明白了... 船舶规章制度怎么说的? 看, 第二段:'任何未经允许试图离开的人将被流放到一个荒岛上, 只给一袋火药。 一 flask ( flask 直译: 烧瓶, 这里意译为'瓶') 水。 一把手枪和一颗子弹.'现在, 你觉得怎么样? "));	
			Link.l2.go = "WantToGo_Stay_force";
		break;
		
	case "WantToGo_Stay_2":
		dialog.text = LinkRandPhrase("嗯, 那就是另一回事了。 " + sti(NPChar.rank)*500 + "比索现款, 我就继续跟着你。 ", "嗯, 也许为了" + sti(NPChar.rank)*500 + "比索我可以留下, 我想。 ", "嗯, 如果你这么说, 为了" + sti(NPChar.rank)*500 + "比索我可以继续服务。 ");
		if (sti(Pchar.money) >= sti(NPChar.rank)*500)
		{
			Link.l1 = RandPhraseSimple("好吧, 同意。 ", "好吧。 虽然你可以少要点。 ", "你胃口不小啊! 但我已经答应了, 会信守诺言。 ");	
			Link.l1.go = "WantToGo_Stay_ForMoney";
		}
		Link.l2 = LinkRandPhrase("这太多了。 我可以用这笔钱雇两个副官。 也许, 让你走更简单。 ", "嗯, 你肯定对自己评价很高。 好吧, 我让你走。 但你自己会看到, 一旦你自由了, 你的生活不会像你期望的那样无忧无虑。 ", "我不会付这么多钱。 你可以走, 但别指望回来, 我不原谅背叛。 ");				
		Link.l2.go = "WantToGo_free";
	break;
	
	case "WantToGo_Stay_force":
		Npchar.loyality = makeint(Npchar.loyality) - 2;
		dialog.text = "好吧, 如果你这么说, 我会留下。 但要知道, 我这样做是违背自己意愿的。 ";
		Link.l1 = LinkRandPhrase("很好。 回到你的岗位, 我们稍后再继续这个谈话。 ", "回到船上。 下次要求退休前再好好想想。 ", "确实。 职责就是职责, 你还不应该沉溺于幻想。 ");
		Link.l1.go = "exit";
	break;
	
	case "WantToGo_Stay_ForMoney":
		Diag.TempNode = "Hired";
		NPChar.greeting = "Gr_Officer";
		if(NPChar.id == "Duran") NPChar.greeting = "Duran_officer";
		ChangeCharacterComplexReputation(pchar,"authority", 0.2);
		AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
		Npchar.loyality = makeint(Npchar.loyality) + 1;    
		Diag.CurrentNode = Diag.TempNode;
		NPChar.quest.meeting = true;
		DialogExit();
		NPChar.location = "none";
		LAi_SetOfficerType(NPChar);
	break;
	
	case "WantToGo_free":
		//navy -->
		if (CheckAttribute(NPChar, "PGGAi"))
		{	
			pchar.questTemp.FiringOfficerIDX = NPChar.index;
			AddDialogExitQuestFunction("PGG_FireOfficer");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();	
			break;
		}
		//navy <--
		Diag.TempNode = "WantToGo_free_Yet";
		Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
		AddDialogExitQuestFunction("LandEnc_OfficerFired");
		Diag.CurrentNode = Diag.TempNode;
		NPChar.quest.meeting = true;
		DialogExit();
	break;
	
	case "WantToGo_free_Yet":
		Diag.TempNode = "WantToGo_free_Yet";
		dialog.text = LinkRandPhrase ("真不敢相信! 谢谢你船长, 这让我如释重负。 ", "谢谢你, 船长, 没有试图留住我。 你知道, 我真的想尝试生活中的其他事情。 ", "嘿, 现在我得习惯我新获得的自由了。 直到现在我才开始意识到我有多厌倦舰队的服务。 "));	
		Link.l1 = RandPhraseSimple("好吧, 祝你好运。 ", "你现在自由了。 你的服务结束了。 ");
		Link.l1.go = "exit";
	break;
	// boal 29.05.04 副官想离开 <--
		
	// 乘客被玩家激怒并离开 -->
	case "WantToRemove":
		if (npchar.id == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_SobytieKlodDuran"))
		{
			SetTimerCondition("SKD_DuranTavern", 0, 0, 30, false);
			pchar.questTemp.SKD_SobytieKlodDuran = true;
		}
        chrDisableReloadToLocation = false;
		if (Npchar.alignment == "good")
		{
			dialog.text = RandPhraseSimple(LinkRandPhrase("船长, 我不想违背良心参与抢劫。 ","船长, 我不想再参与你的暴乱了。 我是一名副官, 不是屠夫。 ","船长, 你做生意的强盗方式让我无法在你的船员中待下去。 "), LinkRandPhrase("船长, 我必须承认, 受雇于你是一个令人失望的错误。 我不想为了任何钱牺牲我的声誉。 ","船长, 你在船上聚集了新世界最邪恶的恶棍。 一个体面的人甚至看一眼都觉得恶心。 我不想再和这样的船员一起服务了。 ","船长, 你雇佣了一整船的流氓, 没有一个像样的人可以聊天。 我鄙视这样的服务。 ")) + " 再见。 ";
			Link.l1 = "什么? ! 这是一艘军舰, 不是一所精修学校! 你可以下地狱了! ";
			Link.l1.go = "exit_fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "我知道你很快就会离开... 这服务不适合你。 但不要指责我什么。 这里有" + sti(NPChar.rank)*500 + "比索, 你找喜欢的工作时会用得上。 ";
				Link.l2.go = "Im_kind_A2";
			}
			Link.l3 = LinkRandPhrase("哦, 所以这就是你现在的调子。 那你每次抢劫分到的那份呢, 烧手吗? 还是你打算退休去修道院祈祷宽恕你的罪孽? 也帮我们说句话, 然后! 哈哈哈! ", "嗯。 现在, 这是一个严肃的声明。 当我们一起抢劫商人时, 你那无辜的良心在哪里看? 你打算怎么洗干净? 或者你打算告发我们, 让我们在体面的公司里上绞架? ", "哦, 太棒了! 显然, 你忘了我是怎么在一个臭酒馆里找到你的, 口袋里连一个铜板都没有。 作为一名副官, 你一文不值。 你毫无价值! ");
			Link.l3.go = "WantToGo_stop";
		}
		else
		{
            dialog.text = RandPhraseSimple(LinkRandPhrase("船长, 我真的不喜欢你的高尚游戏, 我不想为了你的宁静放弃我的习惯。 再见。 ","船长, 我不能再在你手下服务了。 我已经浪费了太多时间。 做一个简单的私掠者已经能让我发财了。 我要离开了。 ","船长, 你的人让我恶心。 没有一个像样的人, 只有穿着华丽衣服的人, 没有一个可以一起喝酒的人。 我要离开了。 "), LinkRandPhrase("船长, 我是一名资深副官, 而你的船看起来更像一艘货船。 我不喜欢这样的服务。 再见。 ","船长, 你的全体船员都是穿着华丽衣服的人, 没有一个可以一起喝酒或聊天的人。 我非常厌恶这样的服务。 再见。 ","船长, 我曾经以为我在为一个真正的海盗服务, 但我们所做的只是慈善! 我不想再浪费时间了。 我要离开了。 "));
			Link.l1 = RandPhraseSimple("我明白了。 考虑到你的态度, 这迟早会发生。 好吧, 我不会留住你。 ", "你的声明并不意外。 坦率地说, 我对你的态度不满意已经有一段时间了。 ") + " 祝你好运。 ";
			Link.l1.go = "exit_fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "我知道你很快就会离开... 这服务不适合你。 但不要指责我什么。 这里有" + sti(NPChar.rank)*500 + "比索, 你找新工作时会用得上。 ";
				Link.l2.go = "Im_kind_A2";
			}
			Link.l3 = RandPhraseSimple("嗯。 现在, 这是一个严肃的声明。 但你还没有还清预支给你的所有钱。 所以你的行为可以被视为勒索, 对吗? ", "哦, 我明白了... 船舶规章制度怎么说? 看, 第二段:'任何未经允许试图离开的人将被流放到一个荒岛上, 只给一袋火药。 一瓶水。 一把手枪和一颗子弹.'现在, 你觉得怎么样? ");
			Link.l3.go = "WantToGo_stop";
		}
		break;
		
		case "WantToGo_stop":
			if (Npchar.alignment == "good")
			{
				dialog.text = LinkRandPhrase("别想侮辱我! 我是为了钱工作, 但我仍然有权选择我喜欢的工作! ", "我是自由人! 我有权随时找新工作! ", "我不是为了食物工作的奴隶, 所以我的良心是清白的! 但我不会再参与抢劫了! ");
				Link.l1 = "嗯, 实际上, 你错了... 当你在酒馆喝酒时, 你可以选择任何你喜欢的工作... 但一旦你踏上我的船, 你唯一的回去的路就是一颗打碎你脖子的炮弹... 并且割掉你的舌头, 这样你在另一个世界就不会说什么了... ";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "WantToGo_stop_stay";
				}
				else
				{
					Link.l1.go = "WantToGo_stop_fight";	
				}
				Link.l2 = "好吧。 你可以走... 但上帝保佑你在公海遇到我。 我发誓, 你会后悔决定不留在我身边的那一刻。 ";
				Link.l2.go = "exit_fire_5";
			}
			else
			{
				dialog.text = LinkRandPhrase("别想恐吓我! 我是为了钱工作, 但我仍然有权选择我喜欢的工作! ", "我是自由人! 我有权随时找新工作! ", "我不是你的奴隶! 我不想在你的旧船上过悲惨的生活! ");
				Link.l1 = "嗯, 实际上, 你错了... 当你在酒馆喝酒时, 你可以选择任何你喜欢的工作... 但一旦你踏上我的船, 你唯一的回去的路就是一颗打碎你脖子的炮弹... 并且割掉你的舌头, 这样你在另一个世界就不会说什么了... ";
				// belamour legendary edition 可以恐吓副官 -->
				//if (makeint(Pchar.Rank) > makeint(NPchar.Rank) || CheckCharacterPerk(pchar, "IronWill"))
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "WantToGo_stop_stay";
				}
				else
				{
					Link.l1.go = "WantToGo_stop_fight";	
				}
				Link.l2 = "好吧。 你可以走... 但上帝保佑你在公海遇到我。 我发誓, 你会后悔决定不留在我身边的那一刻。 ";
				Link.l2.go = "exit_fire_5";
			}
		break;
		
		case "WantToGo_stop_stay":
			dialog.text = RandPhraseSimple("如果你这么说, 我会留下, 我只是别无选择。 但请记住, 我这样做不是出于自愿... ", "好吧, 如果你这么说, 我会留下。 但要知道, 我这样做是违背自己意愿的。 ");
			Link.l1 = RandPhraseSimple("没关系... 服务到我决定什么时候让你走。 ", "很好。 继续服务... 我会决定什么时候让你走。 ");
			Link.l1.go = "WantToGo_Munity"; // 这个链接导致副官逃跑
		break;
		
		case "WantToGo_stop_fight":
			dialog.text = NPCharRepPhrase(NPChar, "你永远不会强迫我重新考虑! 你没有权利把我当奴隶! 我要离开, 让开, 否则你就完了。 ", "你以为你能吓倒一名资深副官? ! 我不止一次死里逃生。 如果你这么说, 死在一场公平的战斗中比在一场血腥的掠夺中死去要好! "));
			Link.l1 = NPCharRepPhrase(NPChar, "好吧... 每个人都选择自己的命运。 我希望你在来找我之前已经祈祷过了。 ", "如果我知道在酒馆里捡到你会发生这种事, 我宁愿让你上绞架... 现在安排也不晚... "));
			Link.l1.go = "WantToGo_stop_fight_1";
			Link.l2 = NPCharRepPhrase(NPChar, "好吧, 如果你这么需要自由, 你可以离开。 但我不会给你任何推荐。 ", "好吧。 你可以走... 但上帝保佑你在公海遇到我。 我发誓, 你会后悔决定不留在我身边的那一刻。 "));
			Link.l2.go = "exit_fire_5";	
		break;
		
		case "WantToGo_stop_fight_1":
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			dialog.text = NPCharRepPhrase(NPChar, "别再恐吓我了! 你的哪个马屁精敢站出来反对我? 如果我是船长, 他们现在已经发财了! 在你从事所有这些慈善活动之后, 你害怕你的船员会站在我这边? ! ", "别再用你的方式了, 你吓不到我! 再见。 "));
			Link.l1 = NPCharRepPhrase(NPChar, "不, 伙计, 你活不到上绞架的时候。 你没那个福气... ", "别那么快, 伙计, 我们还没完, 你欠我的。 "));
			Link.l1.go = "Get_out_fight";
		break;	
		///////////////////////////////////////////////////////////////////////////////////
		case "WantToGo_Munity":	//zagolski。 副官逃跑的演绎
			Diag.TempNode = "Hired";
			// belamour legendary edition 最近因为害怕不适合
			/* if(CheckCharacterPerk(pchar, "IronWill"))
			{
				Npchar.loyality = makeint(Npchar.loyality) + 3 + hrand(sti(GetSummonSkillFromNameToOld(pchar,SKILL_FORTUNE)+GetSummonSkillFromNameToOld(pchar,SKILL_LEADERSHIP)));
				log_info(GetFullName(Npchar)+" 提高了他的忠诚度");
				log_testinfo("忠诚度变为: " + Npchar.loyality + " of " + MAX_LOYALITY);
			}
			else
			{ */
				if (!CheckAttribute(pchar, "questTemp.MutinyOfficerIDX"))
				{
					pchar.questTemp.MutinyOfficerIDX = npchar.index;
					npchar.quest.Mutiny = true; // mitrokosta 额外防止 bug
					SetFunctionTimerCondition("mOfficer_fc", 0, 0, 1, false);
				}
			//}
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.location = "none";
			LAi_SetOfficerType(NPChar);
			DialogExit();
		break;
		////////////////////////////////////////////////////////////////////
		// 乘客被玩家激怒并离开 <--
		
		case "Node_2":
			dialog.text = NPCharRepPhrase(Npchar, RandSwear() + "我是这片海域最好的" + XI_ConvertString(Npchar.quest.officertype) + "。 " + Npchar.quest.officertype_2 + "我准备帮你一个忙, 在你手下服务。 ",
                                    "嗯, 他们说我不是很差的" + XI_ConvertString(Npchar.quest.officertype) + "。 " + Npchar.quest.officertype_2 + "你可以让我上你的船, 船长, 自己看看。 "));
			Link.l1 = "你想要多少钱? ";
			Link.l1.go = "price";
			Link.l2 = "你是哪种专家? ";
			Link.l2.go = "ShowParam_exit";
			Link.l3 = "唉, 我已经有一个" + XI_ConvertString(Npchar.quest.officertype) + "了。 ";
			Link.l3.go = "Exit";
		break;

		case "OnceAgain":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = RandPhraseSimple("嘿, 船长, 一半的驻军都在追你。 现在肯定不是加入你船员的最佳时机! ", "还要一路杀回船上? 不, 船长, 换个时间吧... ");
				link.l1 = RandPhraseSimple("如你所愿... ", "实际上, 我本来也没打算雇你。 "); 
				link.l1.go = "exit";
				break;
			}
			Diag.TempNode = "OnceAgain";
			dialog.text = "你改变主意了吗, 船长? 决定一个新的" + XI_ConvertString(Npchar.quest.officertype) + "不会有坏处? ";
			// boal -->
			if (FindFreeRandomOfficer() > 0)
			{
                Link.l1 = "差不多。 你想要多少钱? ";
                Link.l1.go = "price";
			}
			Link.l2 = "你能做什么? ";
			Link.l2.go = "ShowParam_exit";
			// boal <--
			Link.l3 = "我已经满员了。 再见。 ";
			Link.l3.go = "exit";
		break;

		case "price":
			dialog.text = "我想我们可以达成" + Npchar.quest.OfficerPrice + "比索的协议。 ";
			if(Npchar.rank >= 15)
			{
				dialog.text = "我想我们可以达成" + (makeint(Npchar.quest.OfficerPrice) / 100 + 30) + "达布隆的协议。 ";
			}	
			Link.l1 = "这是不是有点多? ";
			Link.l1.go = "trade";
			Link.l2 = "我同意。 认为自己是船员的一部分。 ";
			Link.l2.go = "hire";
			Link.l3 = "你不值这个钱。 ";
			Link.l3.go = "exit";
		break;

		case "trade":
			if (GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE) >= Rand(12) && (sti(Npchar.quest.OfficerPrice) - GetCharacterSkillToOld(Pchar, "commerce")*100) >= sti(Npchar.quest.OfficerLowPrice))// bug 修复
			{
				Npchar.quest.OfficerPrice = makeint(makeint(Npchar.quest.OfficerPrice) - GetCharacterSkillToOld(Pchar, "commerce")*100); // 让玩家的商业技能直接生效
				dialog.text = "好吧... 我想我甚至可以接受" + Npchar.quest.OfficerPrice + "比索。 你觉得呢? ";
				if(Npchar.rank >= 15)
				{
					dialog.text = "我想我甚至可以接受" + (makeint(Npchar.quest.OfficerPrice) / 100 + 30) + "达布隆。 你觉得呢? ";
				}
				Link.l1 = "现在好多了。 你被录用了。 ";
				Link.l1.go = "hire";				
				Link.l2 = "我仍然觉得有点多。 再见。 ";
				Link.l2.go = "exit";
			}
			else
			{
				dialog.text = "对不起, 船长, 但我确实值我要的价。 如果对你来说太多了, 那就去找别人吧。 ";
				Link.l1 = "好吧, 我同意。 我雇你。 ";
				Link.l1.go = "hire";				
				Link.l2 = "那我就去这么做。 再见。 ";
				Link.l2.go = "exit";
			}
		break;

		case "hire":
			dialog.text = "我看你现金短缺, 船长! 对不起, 但我不赊账工作。 ";
			Link.l1 = "哦, 见鬼! ";
			Link.l1.go = "Exit";
			if(Npchar.rank < 15 && makeint(Pchar.money) >= makeint(Npchar.quest.OfficerPrice))
			{
				AddMoneyToCharacter(Pchar, -(makeint(Npchar.quest.OfficerPrice)));
				Diag.TempNode = "OnboardSoon";
				dialog.text = "谢谢你, 船长。 你不会后悔你的选择。 ";
				Link.l1 = "希望如此。 ";
				Link.l1.go = "Exit_hire";								
			}
			if(Npchar.rank >= 15 && PCharDublonsTotal() >= makeint((makeint(Npchar.quest.OfficerPrice) / 100 + 30)))
			{
				RemoveDublonsFromPCharTotal(makeint((makeint(Npchar.quest.OfficerPrice) / 100 + 30)));
				Diag.TempNode = "OnboardSoon";
				dialog.text = "谢谢你, 船长。 你不会后悔你的选择。 ";
				Link.l1 = "希望如此。 ";
				Link.l1.go = "Exit_hire";								
			}
		break;

		case "OnboardSoon":			
			Diag.TempNode = "OnboardSoon";
			dialog.text = "我先喝完这杯酒, 船长, 然后就去船上。 别担心, 我会及时到的。 ";
			Link.l1 = "好的。 如果你迟到, 我就让你擦甲板! ";
			Link.l1.go = "Exit";											
		break;
        
		case "QMASTER_1":
			if(sti(PChar.Ship.Type) == SHIP_NOTUSED)
			{
				dialog.text = "船长, 但你没有船! ";
				Link.l1 = "谢谢你提醒我... ";
				Link.l1.go = "Exit";
				Diag.TempNode = "Hired";
				break;
			}
			// Rebbebion, 添加了显示百分比符号的修复
			dialog.text = "航行中老鼠的最大活动量 " +
			FloatToString(50.0 / (2.0+GetSummonSkillFromNameToOld(PChar, SKILL_REPAIR) + GetSummonSkillFromNameToOld(PChar,SKILL_SNEAK)), 1) +
			"%% 的总货物量。 对于 " + GetCrewQuantity(PChar) + " 名水手, 我们每天需要 " + makeint((GetCrewQuantity(PChar)+6) / 10) + " 食物。 这还不包括运输的奴隶。 ";
			Link.l1 = "谢谢。 ";
			Link.l1.go = "Exit";
			Diag.TempNode = "Hired";
		break;
        
        // boal 05.09.03 副官需要前往登船 -->
        case "stay_follow":
            dialog.text = "你有什么命令? ";
            Link.l1 = "站在这里! ";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "跟着我, 别落后! ";
            Link.l2.go = "Boal_Follow";
            // boal 05.09.03 副官需要前往登船 <--
			if (npchar.id == "OffMushketer")
			{
				Link.l3 = "我希望你与目标保持一定距离。 ";
				Link.l3.go = "TargetDistance";
			}
			
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l4 = "我们需要为你的火器更换弹药类型。 ";
					Link.l4.go = "SetGunBullets";
				}	
			}
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l5 = "我们需要为你的步枪更换弹药类型。 ";
					Link.l5.go = "SetMusketBullets";
				}
					Link.l6 = "我们需要为战斗更换你的优先武器。 ";
					Link.l6.go = "SetPriorityMode";
			}
		break;

		case "SetGunBullets":
			Dialog.Text = "选择弹药类型: ";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			Diag.CurrentNode = Diag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;
		
		case "SetMusketBullets":
			Dialog.Text = "选择弹药类型: ";
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetMusketBullets1_" + i;
			}
		break;	

		case "SetMusketBullets2":
			i = sti(NPChar.SetMusketBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, MUSKET_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, MUSKET_ITEM_TYPE);
			Diag.CurrentNode = Diag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetMusketBullets");
			DialogExit();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "战斗开始时你将使用: ";
			Link.l1 = "刀剑";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "步枪";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
            SetPriorityMode(NPChar, 1);
			DialogExit();
		break;
		
		case "MusketPriorityMode":
			SetPriorityMode(NPChar, 2);
			DialogExit();
		break;
		
		case "TargetDistance":
			dialog.text = "到底多远, 船长? 以步为单位指示, 但不超过20步。 ";
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";			
		break;
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "船长, 你没事吧? ";
				link.l1 = "对不起, 是我不好... ";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "我会站在原地不动。 这就是你想要的吗, 船长? ";
				link.l1 = "是的。 这正是我需要你做的。 ";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "我想我告诉过你, 我不能站在离目标超过20步的地方。 ";
				link.l1 = "好吧, 保持20米的距离。 ";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "明白并已考虑。 ";
			link.l1 = "好的。 ";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;

		case "AsYouWish":
			// 海上检查 -->
			if (bSeaActive)
			{
				attr = Sea_FindNearColony();
				if (attr == "none")
				{
					dialog.text = "船长, 虽然我真的不理解你的理由, 但我们能在岸上谈吗? 或者你决定干脆把我扔到海里? ";
					Link.l1 = "嗯... 不, 我不是那个意思。 待在这里直到我们到达港口。 ";
					Link.l1.go = "Exit";	
					break;	
				}
			}
			// 海上检查 <--
			if (makeint(PChar.reputation.nobility) >= 41 && makeint(NPChar.reputation) < 41) // 英雄对恶棍
			{
				dialog.text = RandPhraseSimple(LinkRandPhrase("现在这是新情况! ","为什么, 天哪? ","原因是什么? ! "), RandPhraseSimple("船长, 你疯了吗? 无缘无故说这种话! ","哇! 我做了什么让你不高兴的事? "));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("我决定整顿船员。 我不喜欢你和同事的关系","你的优势不如雇佣时讨论的那么好。 所以, ","我团队里的暴徒和流氓不会留下! 所以, "), LinkRandPhrase("我得知你在偷朗姆酒, 秘密让我的船员习惯酗酒, 从而降低士气。 因此, ","我受够了你的强盗行为, 我不会再容忍了。 所以, ","你总是在中央舱室玩牌或骰子, 分散其他副官执行任务的注意力。 这不能无限期继续下去。 所以")) + " 收拾你的东西, 离开船。 ";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "Get_out_A1_peace";
				}
				else
				{
					Link.l1.go = "Get_out_A1_strife";
				}
				break;	
			}
			if (makeint(PChar.reputation.nobility) >= 41 && makeint(NPChar.reputation) >= 41) // 英雄对英雄
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple("我可以知道这个决定的原因吗? ","显然, 这个决定是经过深思熟虑的? "), RandPhraseSimple("解释一下, 船长","这太出乎意料了。 但我还是想知道原因。 "));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("我对你的工作态度完全不满意。 ","不幸的是, 你没有成为一名好副官, 而且可能永远不会... ","你是一名好副官, 你的服务是公平的, 但现在我们分道扬镳了。 别问我为什么。 "), LinkRandPhrase("我警告过你, 对朗姆酒的热爱会毁了你。 我怎么能信任一个在战斗中甚至无法把剑插入鞘中的人? ","你是个糟糕的水手和副官... 我想, 你在岸上会比在海上更多。 ","我对你的资格不满意, 但现在我终于找到了一个合适的替代者。 "));
				Link.l1.go = "Get_out_A2";
				break;	
			}
			if (makeint(PChar.reputation.nobility) < 41 && makeint(NPChar.reputation) >= 41) // 恶棍对英雄 
			{		
				dialog.text = RandPhraseSimple(RandPhraseSimple("嗯... 我可以知道原因吗? ","这是一个严肃的声明。 我可以知道你具体不满意什么吗? "), RandPhraseSimple("解释一下, 船长。 ","显然, 这样的声明是经过深思熟虑的? "));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("我对你的资格完全不满意, 因此","不幸的是, 你没有表现出自己是一名体面的副官。 所以, ","我受够了你的高尚行为。 我不会无限期容忍它们, 所以"), LinkRandPhrase("我得知你在煽动船员 disobedience ( disobedience 直译: 不服从, 这里意译为'叛乱') 。 我的船上不会有骚乱! 而且不要感谢我之前没有把你扔出去。 所以","你的高尚原则值得尊敬, 但它们与自由私掠者的强盗生活相悖。 所以","我不喜欢你对职责的态度。 所以")) + " 收拾你的东西, 离开船。 ";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "Get_out_A3_peace";
				}
				else
				{
					Link.l1.go = "Get_out_A3_strife";
				}	
				break;
	
			}
			if (makeint(PChar.reputation.nobility) < 41 && makeint(NPChar.reputation) < 41) // 恶棍对恶棍
			{	
				dialog.text = RandPhraseSimple(LinkRandPhrase("船长, 我真的没想到! 也许你可以解释一下发生了什么? ","船长, 你在发什么疯? ! ","你是什么意思, 船长? ! "), RandPhraseSimple("到底怎么了, 船长? ! 昨天一切似乎都很好, 现在我们在这里, 发生了什么? ","哇! 也许你可以解释一下自己? "));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("你是个十足的懒鬼, 连货船上的男孩都比你强。 我受够你了。 所以","我早就想解雇你了, 现在终于找到了一个合适的替代者。 所以","我得知你在偷朗姆酒, 秘密让我的船员习惯酗酒, 从而降低士气。 因此"), LinkRandPhrase("当我雇佣你时, 你吹嘘自己是整个舰队最好的副官, 但结果你只是个游手好闲的人, 所以","我警告过你, 你的饮酒习惯会有不好的结局。 为什么我要在我的船上保留一个无用的酒鬼? 所以","你不服务, 而是不断地到处游荡或玩牌或骰子。 我希望你没想过这可以永远持续下去? 所以")) + " 收拾你的东西, 离开船。 ";
				Link.l1.go = "Get_out_A4";
				break;
			}
		break;
	
		case "Get_out_A1_peace":
			dialog.text = RandPhraseSimple(LinkRandPhrase("你现在怎么说话呢! 好吧, 如你所愿。 但请放心: 即使我饿死, 也不会回到你身边! ","坦率地说, 我也不太喜欢你的高尚游戏。 所以再见... ", "哦, 去死吧! 和你的马屁精们待在一起。 真是个'英雄'! "), LinkRandPhrase("实际上, 我从不喜欢为你服务... 你那里有一艘货船, 不是一艘像样的船。 更像是一所精修学校... ","你知道, 我厌倦了你的船员, 都是些穿着华丽衣服的人, 只是些孩子, 没有一个真正的男人... ","好吧, 船长, 如你所说。 但天知道, 我一直工作得很好... "));
			Link.l1 = "等等。 目前我不能在没有副官的情况下离开这艘船。 但稍后我们会再谈这个。 ";
			Link.l1.go = "exit_bad";
			Link.l2 = "那就平静地走吧。 ";
			Link.l2.go = "Exit_Fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "别生气。 我为你准备了遣散费 - " + sti(NPChar.rank)*500 + "比索。 我希望这能消除所有问题。 ";
				Link.l3.go = "Get_out_А1_ForMoney";
			}
		break;

		case "Get_out_A1_strife":
			dialog.text = LinkRandPhrase("对不起! 你说'离开船'是什么意思? ! 我可不是为了让你想扔就扔而冒枪林弹雨的! ", "哈!'离开船'! 你真的认为我会让你像扔小猫一样扔我吗? ! ", "轻松点, 船长, 严肃的人不会这样解决问题。 我不会被当作新手对待。 ");
			Link.l1 = "好吧, 你现在可以留下 - 但只是直到我找到一个合适的替代者。 " ;
			Link.l1.go = "exit_bad";
			Link.l2 = "我重复一遍, 你的服务结束了。 你可以收拾东西了。 ";
			Link.l2.go = "Get_out_A1_strife_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "别生气。 我为你准备了" + sti(NPChar.rank)*500 + "比索。 我希望这能消除所有问题。 ";
				Link.l3.go = "Get_out_А1_ForMoney";
			}
		break;

		case "Get_out_A1_strife_1":
			dialog.text = RandPhraseSimple("实际上, 我也不想留在这里。 但我也不会不拿补偿就走! ", "现在, 我当然不会留在你的旧船上, 但首先你要补偿我! ") + " " + sti(NPChar.rank)*1000 + "比索, 我们就互相忘记。 ";
			Link.l1 = "我有点激动... 请接受我的道歉, 回到你的岗位。 ";
			Link.l1.go = "exit_bad1";
			Link.l2 = "你说什么钱, 如果你总是得到你应得的份额? 在我看来这像是勒索! ";
			Link.l2.go = "Get_out_А1_strife_battle";
			if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
			{
				Link.l3 = "好吧。 归还装备, 然后你会得到你要的。 ";
				Link.l3.go = "Get_out_А1_chang";
			}
		break;

		case "Get_out_А1_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			dialog.text = "现在这是另一回事了。 再见! ";
			Link.l1 = "我希望我们的道路永远不会再交叉。 ";
			Link.l1.go = "Exit_Fire_1";
		break;

		case "Get_out_А1_strife_battle":
			dialog.text = LinkRandPhrase("把这当作精神损失的补偿。 我不会容忍这种待遇, 任何敢这样对待我的人都会后悔! ", "这不是勒索, 而是对我浪费时间的补偿! 无论如何我都会得到它! ", "我在你这样的娘娘腔手下服务浪费了太多时间。 我本可以通过掠夺商船发财。 所以我只是想补偿我失去的利润。 ");
			if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
			{
				Link.l1 = "好吧。 这是你的钱... 现在滚蛋! ";
				Link.l1.go = "Get_out_А1_ForMoney_angry";
			}
			Link.l2 = "你似乎忘了你是谁! 我不会允许像你这样的傻瓜对我大喊大叫! ";
			Link.l2.go = "Get_out_А1_strife_death";
		break;

		case "Get_out_А1_strife_death":
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			OfficersReaction("good");
			dialog.text = "来吧, 船长! 展示你自己! ";
			Link.l1 = "天知道, 我不想这样! ";
			Link.l1.go = "Get_out_fight";
		break;
	
		case "Get_out_А1_ForMoney_angry":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			OfficersReaction("bad");
			dialog.text = "现在这是另一回事了。 再见! ";
			Link.l1 = "我希望我们的道路永远不会再交叉。 ";
			Link.l1.go = "Exit_Fire_1";
		break;

		case "Get_out_A2":
			dialog.text = RandPhraseSimple(LinkRandPhrase("好吧, 那就决定了。 再见, 船长, 别记恨... ","可惜, 船长。 但天知道, 我试过了。 再见。 ","好吧, 船长, 你真难取悦! 好吧, 祝你好运。 "), LinkRandPhrase("可惜, 船长。 你知道, 我喜欢为你工作。 ","是啊, 事情就是这样... 但我不记恨。 再见。 ","你对我不公平, 船长。 不过, 我尊重你的决定。 再见。 "));
			Link.l1 = "等等, 我改变主意了。 我们稍后再谈这个。 ";
			Link.l1.go = "exit_good";
			Link.l2 = "别难过。 祝你好运... ";
			Link.l2.go = "exit_fire_2";
			Link.l3 = "等等... 我给你装备得很好。 还给我, 我不想装备一群... ";
			Link.l3.go = "Return_items_A2";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l4 = "等等... 我不想让你空手走。 这里, 拿" + sti(NPChar.rank)*500 + "比索。 找新工作时会用得上。 ";
			}
			Link.l4.go = "Im_kind_A2";
		break;

		case "Return_items_A2":
			ChangeOfficersLoyality("bad_all", 1);
			dialog.text = "哦, 当然, 都拿回去... ";
			Link.l1 = "我知道你明白我的意思... ";
			Link.l1.go = "Get_out_А2_chang";
		break;

		case "Im_kind_A2":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeOfficersLoyality("good_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			dialog.text = "谢谢你, 船长! 真是意想不到的慷慨... 你知道, 我还有一些你的东西, 也许你想拿回去? ";
			Link.l1 = "也许... 现在找一把好刀不容易。 ";
			Link.l1.go = "Get_out_А2_chang";
			Link.l2 = "哦, 别担心。 留着作为你服务的纪念吧。 ";
			Link.l2.go = "exit_fire_2";
		break;

	case "Get_out_A3_peace":
			dialog.text = RandPhraseSimple(LinkRandPhrase("好吧, 如你所愿。 但请放心: 即使我饿死, 也不会回到你身边!! ","船长, 你做生意的强盗方式也让我恶心。 这迟早会发生。 没有必要编造理由。 ","那你就和你的恶棍们待在一起吧。 一个体面的人甚至不会出现在你船上的副官室。 你这简直是妓院, 上帝宽恕我! "), LinkRandPhrase("坦率地说, 我也不喜欢在你手下服务。 你雇佣了一整船的流氓, 没有一个像样的人可以聊天。 ","是的, 如果你对船员保持这种态度, 很快你就会孤身一人, 不需要编造任何理由。 ","我们的敌意是相互的, 这让我感到安慰。 再见。 "));
			Link.l1 = "等等。 现在不是你退休的最佳时机。 但所有主张仍然有效。 ";
			Link.l1.go = "exit_bad";
			Link.l2 = "走吧, 走吧。 没有你的说教我会过得很好。 ";
			Link.l2.go = "exit_fire_3";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "等等。 我会给你" + sti(NPChar.rank)*500 + "比索。 我不想你死在排水沟里, 让我感到内疚。 ";
				Link.l3.go = "Get_out_А3_ForMoney";
			}
		break;

		case "Get_out_А3_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			ChangeOfficersLoyality("good_all", 1);
			dialog.text = LinkRandPhrase("好吧, 谢谢。 再见... ", "感谢你的理解。 祝你好运。 ", "现在我们两清了。 祝你好运... ");
			Link.l1 = "我知道你明白我的意思。 ";
			Link.l1.go = "exit_fire_3";
		break;
	
		case "Get_out_A3_strife":
			dialog.text = LinkRandPhrase("但船长, 在这种情况下我会陷入困境。 你真的愿意把我从船上直接送到码头吗? ", "你对我不公平, 船长。 但如果我得到适当的补偿, 我不会记恨。 ", "这就是你对我所有战斗伤痕的感激吗? 好吧, 我想没有金钱补偿我是不行的。 ");
			Link.l1 = "好吧, 我改变主意了。 你可以留下, 但我们稍后再谈这个。 ";
			Link.l1.go = "exit_bad";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "哦, 别担心。 这里 - " + sti(NPChar.rank)*500 + "比索。 这将补偿你在我船上的时间。 ";
				Link.l2.go = "Get_out_А3_ForMoney";
				Link.l3 = "我会给你钱。 不过, 多亏了我, 你装备得很好, 我想你应该把东西还给我。 ";
				Link.l3.go = "Return_items_A3";
			}
			Link.l4 = "哦, 真的吗? 那你定期收到的份额呢? ! 我就知道最后会是唠叨和乞求奖金。 ";
			Link.l4.go = "Get_out_A3_strife_1";
		break;

		case "Return_items_A3":
			dialog.text = "我就知道你会这么说, 但你只有在收到" + sti(NPChar.rank)*1000 + "比索后才能拿回你的装备。 否则你只能从我尸体上拿! ";
			Link.l1 = "好吧, 那拿你的钱。 ";
			Link.l1.go = "Get_out_А3_chang";
			Link.l2 = "你疯了吗? ! 为了免费给你的东西要这么多钱? ! 我现在明白你的贪婪显然战胜了你假装的善良。 ";
			Link.l2.go = "Get_out_A3_strife_1";
		break;

		case "Get_out_A3_strife_1":
			dialog.text = "别敢侮辱我! 我可能不是海军中最好的, 但我仍然是一名战斗副官。 即使像你这样的粗人也应该尊重我! ";
			Link.l1 = "如果你还没明白, 我再重复一遍: 别再乞求了, 你不会从我这里得到任何东西。 ";
			Link.l1.go = "Get_out_А3_strife_death";
		break;

		case "Get_out_А3_strife_death":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			OfficersReaction("bad");
			dialog.text = "好吧, 我仍然会得到满足! ";
			Link.l1 = "哦, 这是挑战, 不是吗? 那就如你所愿... ";
			Link.l1.go = "Get_out_fight";
		break;

		case "Get_out_A4":
			dialog.text = RandPhraseSimple(LinkRandPhrase("这就是我的运气! 我全身心投入服务, 结果却被踢出去, 连服务福利都没有! ","多么不幸啊? ! 我刚被雇佣, 几乎马上就被踢走了。 这些天我都不知道该向哪位圣徒祈祷... ","哎呀! 今年第三次被解雇, 都是在星期一。 也许我不该在宿醉的时候出现在船长面前。 "), LinkRandPhrase("好吧, 如你所愿。 祈祷我们再也不要见面。 ","如你所愿。 不过请记住, 你永远找不到更好的副官。 ","好吧, 船长, 如你所说。 但天知道, 我一直工作得很好... "));
			Link.l1 = "等等。 现在不是你退休的最佳时机。 但所有主张仍然有效。 ";
			Link.l1.go = "exit_good";
			Link.l2 = RandPhraseSimple("现在滚吧。 感谢上帝, 今天我心情好。 ", "现在滚吧。 你这个副官和屎一样, 只能用来做子弹。 ");
			Link.l2.go = "exit_fire_4";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "等等。 我会给你" + sti(NPChar.rank)*500 + "比索。 我不想你死在排水沟里, 让我感到内疚。 ";
				Link.l3.go = "Get_out_А4_ForMoney";
			}
			Link.l4 = "等等... 我给你装备得很好, 把我的东西还给我。 ";
			Link.l4.go = "Return_items_A4";
		break;

		case "Get_out_А4_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			ChangeOfficersLoyality("good_all", 1);
			dialog.text = LinkRandPhrase("哦, 谢谢, 船长! 你真是太好了... ", "感谢你的理解。 祝你好运。 ", "现在我们两清了。 祝你好运... ");
			Link.l1 = "祝你好运。 我希望你不要在第一个酒馆就把钱全花光。 ";
			Link.l1.go = "exit_fire_4";
		break;

		case "Return_items_A4":
			if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
			{
				dialog.text = LinkRandPhrase("现在你还要拿走我的装备! 哦, 我的天, 去他的! 我发誓... ", "我看你是决定把我洗劫一空了。 哦, 好吧。 现在我只有一条路, 去码头... ", "哦, 非常感谢! 现在你决定抢劫我了。 哦, 多么残酷的命运... 拿去吧, 拿去吧! 我还能做什么呢... ");
				Link.l1 = "现在滚吧。 你这个副官和屎一样, 只能用来做子弹。 ";
				Link.l1.go = "Get_out_А4_chang_1";
			}
			else	
			{
				dialog.text = RandPhraseSimple("如你所愿, 船长, 但首先请你好心给我" + sti(NPChar.rank)*1000 + "比索。 让这作为精神损失的补偿。 ", "好吧。 但我仍然希望收到" + sti(NPChar.rank)*1000 + "比索, 作为我辛勤和忠诚服务的补偿。 ");
				if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
				{
					Link.l1 = "真是个恶棍! 好吧, 这是你的钱。 ";
					Link.l1.go = "Get_out_А4_chang";
				}
				Link.l2 = "你不是疯了吧? ! 竟敢为我自己给你的东西要这么多钱! ";
				Link.l2.go = "Get_out_A4_strife";
				Link.l3 = "啊哈! 我在开玩笑! 我怎么能踢走一个老朋友呢, 破帽子! ";
				Link.l3.go = "exit_bad1";
			}
		break;

		case "Get_out_A4_strife":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			ChangeOfficersLoyality("bad_all", 1);
			dialog.text = "那么你什么也得不到! 在我听到我的钱叮当作响之前, 我不会迈出一步! ";
			Link.l1 = RandPhraseSimple("你很快就会听到我的刀刃声! ", "那你将被抬着出去! ");
			Link.l1.go = "Get_out_fight";
		break;

		case "Get_out_fight":
			CheckForReleaseOfficer(GetCharacterIndex(Npchar.id));
			RemovePassenger(Pchar, Npchar);
			LAi_CharacterDisableDialog(NPChar);
			LAi_SetWarriorType(Npchar);
			LAi_group_MoveCharacter(Npchar, "TmpEnemy");
			LAi_group_SetHearRadius("TmpEnemy", 100.0);
			LAi_group_FightGroupsEx("TmpEnemy", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
			if (PChar.location == Get_My_Cabin() || findsubstr(PChar.location, "_tavern" , 0) != -1 || findsubstr(PChar.location, "_store" , 0) != -1)
            {
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				LAi_group_SetCheck("TmpEnemy", "CannotFightCurLocation");
				LAi_group_SetCheck("TmpEnemy", "MainHeroFightModeOff");
            }
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

	    case "Get_out_А1_chang": // 交换界面
			Diag.TempNode = "Fired_1";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;	
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А2_chang": // 交换界面
			Diag.TempNode = "Fired_2";
			LAi_CharacterDisableDialog(NPChar);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А3_chang": // 交换界面
			Diag.TempNode = "Fired_3";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А4_chang_1": // 交换界面
			Diag.TempNode = "Fired_4";
			LAi_CharacterDisableDialog(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;	
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А4_chang": // 交换界面
			Diag.TempNode = "Fired_4";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;	
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

	    case "exit_bad":
			Npchar.loyality = makeint(Npchar.loyality) - 3;
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_bad1":
			Npchar.loyality = makeint(Npchar.loyality) - 2;
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			Diag.CurrentNode = Diag.TempNode;			
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_good":
			Npchar.loyality = makeint(Npchar.loyality) - 1;
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_fire_1":	//navy -->			
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--		
			Diag.TempNode = "Fired_1";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_2":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");	
				DialogExit();
				break;
			}	//navy <--	
			Diag.TempNode = "Fired_2";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_3":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--	
			Diag.TempNode = "Fired_3";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_4":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");	
				DialogExit();
				break;
			}	//navy <--		
			Diag.TempNode = "Fired_4";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_5":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--	
			Diag.TempNode = "Fired_1";
			OfficersReaction("good");
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "Fired_1":
			Diag.TempNode = "Fired_1";      
			dialog.text = "现在又怎么了? ! 我们已经谈过所有事情了! 我再也不会踏上你的船了。 ";
			Link.l1 = RandPhraseSimple("现在滚吧。 毕竟不是什么大损失。 ", "好吧, 那走吧。 我不会留你。 ");	
			Link.l1.go = "Exit";
		break;

		case "Fired_2":
			Diag.TempNode = "Fired_2"; 
			dialog.text = "还有什么事吗, 船长? 我以为我们已经讨论过所有事情了... ";
			Link.l1 = "不, 没什么。 只是想说再见... ";	 
			Link.l1.go = "Exit";
		break;

		case "Fired_3":
			Diag.TempNode = "Fired_3"; 
			dialog.text = "船长, 我们已经讨论了所有事情并表达了我们的主张。 你不会说你改变主意了吧? ";
			Link.l1 = "好吧, 那走吧。 毕竟不是什么大损失。 ";	 
			Link.l1.go = "Exit";
		break;

		case "Fired_4":
			Diag.TempNode = "Fired_4"; 
			dialog.text = "船长, 还能有什么问题呢? 只是告诉你, 我很生气, 而且我没有任何回来的欲望... ";
			Link.l1 = "好吧, 那走吧。 我也不是那么需要你。 ";	 
			Link.l1.go = "Exit";
		break;
		
		// boal 05.09.03 副官需要前往登船 -->
	    case "Boal_Stay":
            //SetCharacterTask_Stay(Characters[Npchar.index]); // 这是神秘的, 但在这里不起作用 :(
            //Log_SetStringToLog(Npchar.id +" "+Npchar.index);
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
		    Diag.TempNode = "Hired";
		    dialog.text = "是, 船长! ";
		    Link.l1 = "稍息。 ";
		    Link.l1.go = "Exit";
		    Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
	    break;
		
	    case "Boal_Follow":
		    SetCharacterTask_FollowCharacter(Npchar, PChar); // 这里有效!!!
		    Diag.TempNode = "Hired";
		    dialog.text = "是, 船长! ";
		    Link.l1 = "稍息。 ";
		    Link.l1.go = "Exit";
	    break;
        // boal 05.09.03 副官需要前往登船 <--

		//////////////////////////////    副官-总督 -->
		case "Gover_Hire":
            dialog.Text = "船长! 这将是一种荣誉! ";
            Link.l1 = "维持秩序并让城市繁荣, 我会不时航行来收取关税。 ";
			Link.l1.go = "Exit_Gover_Hire";
            Link.l2 = "我改变主意了。 ";
            Link.l2.go = "Exit";
            Diag.TempNode = "Hired";
        break;

        case "Exit_Gover_Hire":
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
            attr = sld.id + "_townhall";

            // 移除乘客 -->
			CheckForReleaseOfficer(sti(NPChar.index));
			RemovePassenger(pchar, NPChar);
			// 移除乘客 <--
		    sld.OfficerIdx = sti(NPChar.index);
			ChangeCharacterAddressGroup(NPChar, attr, "sit", "sit1");
			LAi_SetHuberTypeNoGroup(NPChar);
            SaveCurrentNpcQuestDateParam(NPChar, "StartTaxDate");
            SaveCurrentNpcQuestDateParam(NPChar, "GoverTalkDate");
            LAi_LoginInCaptureTown(NPChar, true);
			//  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
            AddQuestRecordInfo("Gen_CityCapture", "t3_1");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + sld.id));
			AddQuestUserData("Gen_CityCapture", "sName", GetFullName(NPChar));
			//  СЖ <--
			Diag.CurrentNode = "Gover_Main";
            DialogExit();
        break;

        case "Gover_Main":
            iTemp = GetNpcQuestPastDayParam(NPChar, "GoverTalkDate");
            if (iTemp > 0)
            {
				dialog.Text = "你有什么命令? 上次你拜访我是在" + FindRussianDaysString(iTemp) + "前。 ";
			}
			else
			{
			    dialog.Text = "你有什么命令? ";
			}

            Link.l1 = "到目前为止你" + NPCharSexPhrase(NPChar, "收集了", "收集了") + "多少税款? ";
        	Link.l1.go = "Gover_Tax";
            Link.l8 = "船上需要你, 我解除你在镇上的职务。 ";
            Link.l8.go = "Gover_Fire";
			Link.l9 = "一切顺利。 ";
            Link.l9.go = "Exit";
            Diag.TempNode = "Gover_Main";
            SaveCurrentNpcQuestDateParam(NPChar, "GoverTalkDate");
        break;

        case "Gover_Tax":
            iTemp = GetNpcQuestPastDayParam(NPChar, "StartTaxDate");
            iTax  = makeint((GetCharacterSkillSimple(NPChar, SKILL_COMMERCE) + GetCharacterSkillSimple(NPChar, SKILL_LEADERSHIP)) / 2);
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
			if (CheckAttribute(sld, "FortValue"))
			{
			    iFortValue = sti(sld.FortValue);
			}
			else
			{
			    iFortValue = 20;
			}
			NPChar.Gover_Tax_Sum = iFortValue*iTax*iTemp;
			dialog.Text = "我的技能允许每天收取" + FindRussianMoneyString(iFortValue*iTax) + "。 在" + FindRussianDaysString(iTemp) + "期间, 我" + NPCharSexPhrase(NPChar, "收集了", "收集了") + " " + FindRussianMoneyString(sti(NPChar.Gover_Tax_Sum)) + "。 ";
			if (sti(NPChar.Gover_Tax_Sum) > 0)
			{
			    Link.l1 = "我想拿走所有收集的税款。 ";
            	Link.l1.go = "Gover_Tax_Get";
			}
			Link.l2 = "感谢你的服务! ";
            Link.l2.go = "Exit";
        break;

        case "Gover_Tax_Get":
            SaveCurrentNpcQuestDateParam(NPChar, "StartTaxDate");
            AddMoneyToCharacter(Pchar, sti(NPChar.Gover_Tax_Sum));

			Diag.CurrentNode = "Gover_Main";
            DialogExit();
        break;

        case "Gover_Fire":
            dialog.Text = "太好了! 你知道, 我不是旱鸭子。 ";
            Link.l8 = "那很好。 ";
            Link.l8.go = "exit_hire";
            Diag.TempNode = "Hired";
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
            DeleteAttribute(sld, "OfficerIdx");
            //  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
            AddQuestRecordInfo("Gen_CityCapture", "t3_2");
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + sld.id));
			AddQuestUserData("Gen_CityCapture", "sName", GetFullName(NPChar));
			//  СЖ <--
        break;
        //////////////////////////////    副官-总督 <--

		//给同伴的指示 19.02.08 -->
		case "Companion_Tasks":
			dialog.Text = "我在听你说。 ";
			Link.l1 = "这是关于登船的。 ";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "这是关于你的船的。 ";
			Link.l2.go = "Companion_TaskChange";
			if(bBettaTestMode) // 仅在测试版中
			{
			    Link.l3 = "我希望你暂时离开我的中队, 自己去寻找财富。 ";
			    Link.l3.go = "CompanionTravel";
			}
			Link.l8 = "到目前为止没什么。 ";
			Link.l8.go = "exit";
		break;
		
		case "Companion_TaskBoarding":
			dialog.Text = "那么你有什么愿望。 ";
			Link.l1 = "不要登敌船。 照顾好自己和船员。 ";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "我希望你登敌船。 ";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;
		
		case "Companion_TaskChange":
			dialog.Text = "那么你有什么愿望。 ";
			Link.l1 = "我希望你登船后不要把你的船换成另一艘。 它太有价值了。 ";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "当你登敌船时, 如果它们还不错, 你可以自己拿走。 ";
			Link.l2.go = "Companion_TaskChangeYes";
		break;
		
		case "Companion_TaskBoardingNo":
			dialog.Text = "是, 船长。 ";
			Link.l1 = "稍息。 ";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;
		
		case "Companion_TaskBoardingYes":
			dialog.Text = "遵命, 船长。 ";
			Link.l1 = "稍息。 ";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;
		
		case "Companion_TaskChangeNo":
			dialog.Text = "是, 船长。 ";
			Link.l1 = "稍息。 ";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;
		
		case "Companion_TaskChangeYes":
			dialog.Text = "遵命, 船长。 ";
			Link.l1 = "稍息。 ";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
		//<--
	
		// 同伴独自航行 -->
		case "CompanionTravel":
			if(GetAttrValue(PChar, "CompanionTravel") == 3) // 如果已经解雇了三个
			{
				dialog.Text = "船长, 我不会离开你的中队, 因为你已经解雇了三艘船。 ";
					Link.l1 = "是的, 也许你是对的。 ";
					Link.l1.go = "exit";
				break;
			}
		
			dialog.Text = "没问题, 船长。 我们在哪个城镇见面? ";
			for(iTemp=0; iTemp<MAX_COLONIES; iTemp++)
			{
				sld = &colonies[iTemp];
				attr = sld.ID;
				if(sld.nation == "none" || sld.nation == PIRATE || attr == "Panama" || attr == "FortOrange") continue;
				attrLoc = "l" + iTemp;
				Link.(attrLoc) = "在" + XI_ConvertString("Colony" + attr + "Dat");
				Link.(attrLoc).go = "CompanionTravelToColony_" + attr;
			}
				Link.l99 = "我改变主意了。 ";
				Link.l99.go = "exit";
		break;
			
		case "CompanionTravel_EnemyColony":
			dialog.Text = "船长, 但我不能在对我们敌对的殖民地等你! ";
				Link.l1 = "你知道, 忘了所有这些旅行吧... ";
				Link.l1.go = "exit";
		break;
			
		case "CompanionTravel_NoCrew":
			dialog.Text = "船长, 我们船员中几乎没有水手! 你说的什么旅行? ! ";
				Link.l1 = "没错, 我们确实缺少水手... ";
				Link.l1.go = "exit";
		break;
			
		case "CompanionTravel_NoFood":
			dialog.Text = "船长, 我船上没有足够的食物进行这样的旅行。 ";
				Link.l1 = "是的, 你说得对。 旅行可以等... ";
				Link.l1.go = "exit";
		break;
			
		case "CompanionTravel_NoHP":
			dialog.Text = "船长, 但我的船状况不佳。 在这种情况下独自航行是不明智的! ";
				Link.l1 = "是的, 你说得对。 你的船需要修理。 ";
				Link.l1.go = "exit";
		break;
		
		case "CompanionTravel_PrepareStart":
			dialog.Text = "我明白了。 到" + XI_ConvertString("Colony" + characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID + "Gen") + "需要航行" + sti(characters[sti(NPChar.realcompanionidx)].CompanionTravel.Days) + "天, 到达后我该做什么? ";
				Link.l1 = "在殖民地港口停泊一个月。 ";
				Link.l1.go = "CompanionTravel_PrepareStart_2";
				Link.l2 = "你知道, 我改变主意了。 留在我身边... ";
				Link.l2.go = "exit";
		break;
		
		case "CompanionTravel_PrepareStart_2":
			dialog.Text = "我明白了, 船长。 我马上出发。 ";
				Link.l1 = "是的, 请吧。 ";
				Link.l1.go = "CompanionTravel_Start";
		break;
			
		case "CompanionTravel_Start":
			Diag.CurrentNode = "CompanionTravel_LastNode";
			NPChar.quest.meeting = true;
			CompanionTravel_SetTraveller(NPChar);
			DialogExit();
		break;
			
		case "CompanionTravel_LastNode":
			Dialog.text = RandPhraseSimple("今天, 我将再次起航... ",
			"别忘了我们在" + XI_ConvertString("Colony" + characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID + "Dat") + "的会面。 ");
				link.l2 = "... ";
				link.l2.go = "Exit";
				Diag.TempNode = "CompanionTravel_LastNode";
		break;
			
		case "CompanionTravel_ToSquadron":
			if(GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				dialog.text = "我也希望如此。 从现在起, 我的船再次归你指挥, 船长。 ";
					Link.l1 = "很好。 ";
					Link.l1.go = "exit";
					Diag.TempNode = "hired";
					CompanionTravel_DeleteSpecialShipAttributes(NPChar);
					Group_DeleteAtEnd(NPChar.CompanionTravel.GroupID); // 删除群组
					SetCompanionIndex(PChar, -1, sti(NPChar.index));
					PChar.CompanionTravel = sti(PChar.CompanionTravel) - 1; // 这个同伴被重新加入中队
					DeleteAttribute(NPChar, "CompanionTravel");
			}
			else
			{
				dialog.text = "船长, 你的中队已经有五艘船了 - 你打算怎么处理第六艘? 嗯, 我想我宁愿在我的船上等你。 你的新同伴看起来不可靠。 他们的船很快就会沉没, 你会回来找我的。 ";
					Link.l1 = "嘿, 你不聪明吗? 你应该当舰队司令 , 而不仅仅是船长! ";
					Link.l1.go = "exit";
					Diag.TempNode = "CompanionTravel_ToSquadron_2";
					NPChar.DeckDialogNode = "CompanionTravel_ToSquadron_2"; // 再次设置这个节点
			}
		break;
			
		case "CompanionTravel_ToSquadron_2":
			dialog.text = "哦, 船长, 你回来了, 正如我说的。 那么, 你的中队现在有空位吗? ";
			if(GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				Link.l1 = "是的, " + NPChar.name+ ", 有一个。 欢迎加入中队。 ";
				Link.l1.go = "exit";
				Diag.TempNode = "hired";
				CompanionTravel_DeleteSpecialShipAttributes(NPChar);
				Group_DeleteAtEnd(NPChar.CompanionTravel.GroupID);
				SetCompanionIndex(PChar, -1, sti(NPChar.index));
				PChar.CompanionTravel = sti(PChar.CompanionTravel) - 1; // 这个同伴被重新加入中队
				DeleteAttribute(NPChar, "CompanionTravel");
			}
			else
			{
				Link.l1 = "不幸的是, 还没有。 ";
				Link.l1.go = "exit";
				Diag.TempNode = "CompanionTravel_ToSquadron_2";
				NPChar.DeckDialogNode = "CompanionTravel_ToSquadron_2";
			}
		break;
		// < —同伴独自航行
		
		case "tonzag_after_boarding":
			dialog.text = "船长, 情况糟透了! 敌人紧紧抓住我们, 恐怕他们不会放手, 直到我们死! 我们的人现在真的有麻烦了, 大多数炮手都被击倒了! ";
			link.l1 = "我会帮助他们。 指挥并带我们离开这里! ";
			link.l1.go = "tonzag_after_boarding_1";
			DelLandQuestMark(npchar);
		break;
		
		case "tonzag_after_boarding_1":
			dialog.text = "是, 先生! ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_GoToGunDeck");
		break;
		
		case "tonzag_after_victory":
			dialog.text = "胜利了, 船长! 登陆队已被摧毁, 敌人选择撤退并向南进发。 船的状况可以接受。 幸存船员: " + GetCrewQuantity(pchar) + "人。 报告完成! ";
			link.l1 = "谢谢你! 每人朗姆酒, 并加强警戒直到我们到达港口! ";
			link.l1.go = "tonzag_after_victory_1";
		break;
		
		case "tonzag_after_victory_1":
			dialog.text = "万岁! 是, 是! ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_AlonsoBoardingDialog");
		break;
	}
}
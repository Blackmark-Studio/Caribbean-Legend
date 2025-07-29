#include "DIALOGS\%language%\Common_Duel.c" //navy
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
    ref NPChar, d;
	aref Link, Diag;
	string NPC_Meeting, TempInfoCharacterID_1, TempInfoCharacterID_2, sQuestTitle, sStr;
	int DonationSize;
    	
	// 战舰 18.05.08
	int iLa_Puesta; // La puesta - 西班牙语意为赌注
    	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);
	
    ProcessCommonDialogRumors(NPChar, Link, Diag);//homo 25/06/06
    ProcessDuelDialog(NPChar, Link, Diag); //navy

	int iEnemyDice, iPCDice;
	int d1,d2,d3,d4;
	bool ok;
    ref sld;
    
	if (npchar.quest.Meeting != LastSpeakDate())
	{
		npchar.quest.Meeting = LastSpeakDate();
		npchar.money = 100 + rand(10) * makeint(50 * sti(PChar.rank) * (10.0 / MOD_SKILL_ENEMY_RATE));
		if (sti(npchar.money) < 150) npchar.money = 150;
        if (bBettaTestMode)
        {
            Dialog.CurrentNode = "Beta_test";
        }
	}
	switch (Dialog.CurrentNode)
	{
		// -----------------------------------首次对话 - 初次见面
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

        case "Beta_test":
            dialog.text = "醉汉类型选择 (测试版) ";
			link.l1 = "醉汉";
			link.l1.go = "Beta_test_alc";
            link.l2 = "纸牌赌徒";
			link.l2.go = "Beta_test_card";
			link.l3 = "骰子赌徒";
			link.l3.go = "Beta_test_dice";
		break;
		
		case "Beta_test_alc":
            dialog.text = "已选择醉汉";
			link.l1 = "继续";
			link.l1.go = "First time";
			npchar.quest.last_theme = 0;
		    npchar.quest.last_theme_game = 0;
		break;
		
		case "Beta_test_card":
            dialog.text = "纸牌赌徒 (30%概率立即反感) ";
			link.l1 = "继续";
			link.l1.go = "First time";
			npchar.quest.last_theme = 1;
		    npchar.quest.last_theme_game = 0;
		break;
		
		case "Beta_test_dice":
            dialog.text = "骰子赌徒 (30%概率立即反感) ";
			link.l1 = "继续";
			link.l1.go = "First time";
			npchar.quest.last_theme = 1;
		    npchar.quest.last_theme_game = 1;
		break;
		
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = LinkRandPhrase("我可能喝醉了, 但我不是傻瓜。 如果我现在和你喝酒, 第二天士兵就会抓我。 没门! ", "我不是自己城镇的敌人。 我不会和你喝酒! " , ""+ GetSexPhrase("伙计","姑娘") +", 你最好趁现在还能走的时候离开这里... ");
				link.l1 = RandPhraseSimple("好吧, 如你所愿... ", "嘿, 你知道, 我不需要喝那么多。 现在不是时候。 "); 
				link.l1.go = "exit";
				break;
			}
			if(CheckAttribute(pchar,"questTemp.HabitueSpeakDisable") && rand(1) == 0) // 如果是决斗者则每两次拒绝一次
			{
				dialog.text = "哈, 先生/女士, 当然, 我听说过你, 呵呵。 酒馆里的人说你是个爱挑逗的决斗者。 我说我们的人不容易被吓到, 但没人想为一杯朗姆酒送命。 我觉得坐在你旁边都害怕, 所以还是算了。 ";
				link.l1 = LinkRandPhrase("那太好了! ","趁我心情好, 快滚... ","滚吧, 鱼食! ");
				link.l1.go = "exit";
				link.l2 = "等等, 我想问个问题... .";
				link.l2.go = "talk_habitue_duel";
				break;
			}
			
            ok = CheckFreeSitFront(npchar);
            
            dialog.text = "别挡我的光, 我看不到杯子里的苍蝇了! ";
            link.l1 = "我没挡... ";
		    link.l1.go = "exit";
		    if (!chrDisableReloadToLocation)
		    {
	            switch (npchar.quest.last_theme)
				{
					case "0": //醉汉
						dialog.text = "嗝! 哦, "+ GetSexPhrase("伙计, 你肯定像个经验丰富的老水手","姑娘, 你肯定像个经验丰富的老水手") +"! 也许你能给我买杯朗姆酒? ";
						link.l1 = "我可能是个老水手, 但这不意味着我要给无赖买酒喝... ";
						link.l1.go = "exit";

						if (makeint(pchar.money) >= 100 && ok) // 只有老岛屿允许坐下
						{
							link.l2 = "我很乐意加入你的陪伴。 ";
							link.l2.go = "talk_with_alchogol";
						}
						else
						{
	                        link.l2 = "为什么? ";
							link.l2.go = "talk_with_alchogol_song";
						}
					break;

					case "1":
	                    if (rand(3) != 1 && ok)
	                    {
							switch (sti(npchar.quest.last_theme_game))
							{
							    case 0 :
									// 纸牌游戏 boal 20/05/05 -->
	                                if (CheckNPCQuestDate(npchar, "Card_date_begin"))
									{
										Dialog.text = RandPhraseSimple("玩纸牌怎么样? 很有趣的游戏! ", "我建议玩纸牌游戏。 你觉得呢? ");
										link.l1 = "为什么不呢? 当然, 我们玩。 ";
										link.l1.go = "Cards_begin";
										link.l2 = "你的游戏规则是什么? ";
										link.l2.go = "Cards_Rule";
										link.l3 = "现在不了。 ";
										link.l3.go = "exit";
									}
									else
					    			{
										Dialog.text = "不, 我不再和你玩纸牌了。 ";
						    			link.l1 = "如你所说。 ";
						    			link.l1.go = "exit";
									}
			                        // 纸牌游戏 boal 20/05/05 <--
		                        break;

								case 1:
								// 骰子
		    						// 骰子游戏 boal 13/07/05 -->
	                                if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
									{
										Dialog.text = RandPhraseSimple("玩骰子怎么样? 很有趣的游戏! ", "我建议掷骰子。 你觉得呢? ");
										link.l1 = "为什么不呢? 当然, 我们玩。 ";
										link.l1.go = "Dice_begin";
										link.l2 = "你的游戏规则是什么? ";
										link.l2.go = "Dice_Rule";
										link.l3 = "现在不了。 ";
										link.l3.go = "exit";
									}
									else
					    			{
										Dialog.text = "不, 我不再和你掷骰子了。 ";
					    				link.l1 = "如你所说。 ";
					    				link.l1.go = "exit";
									}
			                        // 骰子游戏 boal 13/07/05 <--
			                        //navy --> 决斗
									if (CheckAttribute(NPchar, "Quest.DiceCheats") && sti(NPchar.Quest.DiceCheats) >= 1) 
									{
					    				link.l9 = RandSwear() + " 你作弊!!! ";
					    				link.l9.go = "outraged";
									}
									//navy <--
			    				break;
	    					} 
						}
	        			else
	        			{
	                        dialog.text = RandPhraseSimple("离开我的桌子! 现在! ", " 哦? 什么? 那是谁? 嗝... 滚! ");
	                        link.l1 = RandPhraseSimple("喝酒会毁掉你有罪的灵魂! 清醒点! ", "别对我无礼。 ");
	        			    link.l1.go = "exit";
	        			    link.l2 = RandPhraseSimple("注意你的舌头, 你这杂种! 否则我会教你礼貌。 ", "如果我现在打你的头, 我想那会帮你清醒。 ");
	        	            link.l2.go = "tavern_keeper";
	        			}
					break;
				}
			}
			Diag.TempNode = "First time";
	    break;
	    
		case "talk_habitue_duel":
			dialog.text = "我什么都不会告诉你, 先生/女士! 而且我认为也不会有人告诉你, 因为那总是意味着麻烦。 但你知道, 人们往往记性不好, 所以一两个月后他们可能会忘记你的冒险, 当然, 如果你不再提醒他们的话, 呵呵! 再见, 先生/女士。 ";
			link.l1 = "好吧... ";
			link.l1.go = "exit";
		break;
		
	    // 纸牌 -->
	    case "Cards_Rule":
   			dialog.text = CARDS_RULE;
			link.l1 = "好吧, 那我们开始... ";
			link.l1.go = "Cards_begin";
			link.l3 = "不, 这不适合我... ";
			link.l3.go = "exit";
		break;
		
		case "Cards_begin":
			Diag.tempnode = "Cards_Node";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;

		case "Cards_Node":
			Diag.tempNode = "first time";

			Dialog.text = "我们先确定赌注 (输入赌注) 。 ";
			link.l1 = "100";
			link.l1.edit = 1;
			link.l1.go = "Cards_Node_2";
			link.l3 = "我想我得走了。 ";
			link.l3.go = "exit_sit";
		break;
		
		case "Cards_Node_2":
			iLa_Puesta = GetStrSmallRegister(dialogEditStrings[1]);
            if (!CheckCardsGameSmallRate())
		    {
                dialog.text = "你是个臭名昭著的骗子。 我不会和你赌博。 ";
                link.l1 = "都是谎言! 好吧, 不管了。 ";
			    link.l1.go = "exit_sit";
			    break;
		    }
		    
			if (sti(PCHar.Money) < sti(iLa_Puesta)*3)
		    {
                dialog.text = "我看你没钱了, 朋友/亲爱的。 等你有钱了再来。 ";
                link.l1 = "好吧。 ";
			    link.l1.go = "exit_sit";
			    break;
		    }
		
			if (sti(NPChar.Money) < sti(iLa_Puesta)*3)
		    {
                dialog.text = "我已经输光了所有东西。 今天不是我的幸运日。 ";
                link.l1 = "好吧。 ";
			    link.l1.go = "exit_sit";
			    break;
		    }
		else
		{
			if(sti(iLa_Puesta) < 50)
			{
				dialog.text = "你在嘲笑我吗? ! 玩50比索? ! 我们玩合理的赌注, 否则我退出! ";
				link.l1 = "是的, 你说得对。 我们需要提高一点赌注。 ";
				link.l1.go = "Cards_begin_2";
				link.l2 = "我改变主意了, 我不玩了。 ";
				link.l2.go = "exit_sit";
				break;
			}
			
			if(sti(iLa_Puesta) > 1000)
			{
				dialog.text = "玩这么大的钱? 不, 我退出, 除非我们改变赌注。 ";
				link.l1 = "是的, 你说得对。 我们需要降低一点赌注。 ";
				link.l1.go = "Cards_begin_2";
				link.l2 = "实际上, 我决定不玩了。 ";
				link.l2.go = "exit_sit";
				break;
			}
			dialog.text = "好吧, 我们玩" + iLa_Puesta + "硬币。 ";
			link.l1 = "发牌! ";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
			pchar.GenQuest.Cards.iRate     = sti(iLa_Puesta);
            pchar.GenQuest.Cards.SitType   = true;
		}
		break;
		
		case "Cards_begin_2":
			dialog.text = "那么赌注是多少? (输入赌注) ";
			link.l1 = "50";
			link.l1.edit = 1;
			link.l1.go = "Cards_Node_2";
			link.l2 = "我想我终究不会玩... ";
			link.l2.go = "exit_sit";
		break;
							
		case "Cards_begin_go":
            // 游戏当天 SetNPCQuestDate(npchar, "Card_date_begin");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
            LaunchCardsGame();
		break;
	    // 纸牌 <--
	    // 骰子 -->
	    case "Dice_Rule":
   			dialog.text = DICE_RULE;
			link.l1 = "好吧, 那我们开始... ";
			link.l1.go = "Dice_begin";
			link.l3 = "不, 这不适合我... ";
			link.l3.go = "exit";
		break;

		case "Dice_begin":
			Diag.tempnode = "Dice_Node";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;

		case "Dice_Node":
		    Diag.tempNode = "first time";		    
			Dialog.text = "我们确定赌注 (输入赌注) 。 ";
			link.l1 = "50";
			link.l1.edit = 1;
			link.l1.go = "Dice_Node_2";
			link.l3 = "我想我得走了。 ";
			link.l3.go = "exit_sit";
		break;

		case "Dice_Node_2":
			iLa_Puesta = GetStrSmallRegister(dialogEditStrings[1]);
            if (!CheckDiceGameSmallRate())
		    {
				dialog.text = "你是个臭名昭著的骗子。 我不会和你掷骰子。 ";
                link.l1 = "都是谎言! 好吧, 不管了。 ";
			    link.l1.go = "exit_sit";
			    break;
		    }

			if (sti(pchar.Money) < sti(iLa_Puesta)*6)
		    {
                dialog.text = "我看你没钱了, 朋友/亲爱的。 等你有钱了再来。 ";
                link.l1 = "好吧。 ";
			    link.l1.go = "exit_sit";
			    break;
		    }
			
			if (sti(npchar.Money) < sti(iLa_Puesta)*6)
		    {
                dialog.text = "我已经输光了所有东西。 今天不是我的幸运日。 ";
                link.l1 = "好吧。 ";
			    link.l1.go = "exit_sit";
			    break;
		    }
		else
		{
			if(sti(iLa_Puesta) < 50)
			{
				dialog.text = "你在嘲笑我吗? ! 每个骰子玩50比索? ! 我们玩合理的赌注, 否则我退出! ";
				link.l1 = "是的, 你说得对。 我们需要提高一点赌注。 ";
				link.l1.go = "Dice_begin_2";
				link.l2 = "我改变主意了, 我不玩了。 ";
				link.l2.go = "exit_sit";
				break;
			}
			
			if(sti(iLa_Puesta) > 1000)
			{
				dialog.text = "掷骰子玩这么大的钱? 不, 我退出, 除非我们改变赌注。 ";
				link.l1 = "是的, 你说得对。 我们需要降低一点赌注。 ";
				link.l1.go = "Dice_begin_2";
				link.l2 = "实际上, 我决定不玩了。 ";
				link.l2.go = "exit_sit";
				break;
			}
			dialog.text = "好吧, 我们每个骰子玩" + iLa_Puesta + "硬币。 ";
			link.l1 = "掷骰子! ";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
			pchar.GenQuest.Dice.iRate     = sti(iLa_Puesta);
            pchar.GenQuest.Dice.SitType   = true;
		}
		break;
		
		case "Dice_begin_2":
			dialog.text = "那么赌注是多少? (输入赌注) ";
			link.l1 = "50";
			link.l1.edit = 1;
			link.l1.go = "Dice_Node_2";
			link.l2 = "我想我终究不会玩... ";
			link.l2.go = "exit_sit";
			break;

		case "Dice_begin_go":
            // 游戏当天 SetNPCQuestDate(npchar, "Dice_date_begin");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
            LaunchDiceGame();
		break;
	    // 骰子 <--

		/////////////////////////////////////////////
        case "talk_with_alchogol_song":
			dialog.text = "嗯, 嗝! 事情很好。 嗝! 你没看到它来了。 嗝! 这朗姆酒不错。 牙买加黑朗姆酒。 嗝! \n来, 倒上! ";
			link.l1 = "好吧, 为什么不呢。 ";
			link.l1.go = "talk_with_alchogol_song_2";
			link.l2 = "抱歉朋友, 我得走了。 ";
			link.l2.go = "exit";
		break;
		
		case "talk_with_alchogol_song_2":
			dialog.text = "杯子和面孔来了又去... 嗝... 直到我摔倒在地。 我一直在喝酒... 嗝! 酒在哪里... 押韵是什么... ";
			link.l1 = "酒在这里, 女孩们很好, 都想要一个海盗, 但似乎只有朗姆酒是我的。 ";
			link.l1.go = "talk_with_alchogol_song_3";
			link.l2 = "我没时间做这个。 ";
			link.l2.go = "exit";
		break;
		
		case "talk_with_alchogol_song_3":
			dialog.text = "当你悲伤时, 不要尝试思考, 过来, 让我们喝酒! 一切都会好起来的, 我是你的朋友, 你是我的! ";
			link.l1 = "有朋友肯定很棒, 当你走了他会等, 有朋友就没有仇恨, 但当朗姆酒没了就只有争论。 所以让我们喝吧朋友, 在我离开迟到之前... ";
			link.l1.go = "exit";
		break;
		
		case "talk_with_alchogol":
			Diag.TempNode = "begin_sit";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;

		case "begin_sit":
			Diag.TempNode = "first time";
			dialog.snd = "Voice\HADI\HADI028";
			dialog.text = LinkRandPhrase("嗝! 现在好多了! 肯定好多了! 那么? 你会给我买些朗姆酒吗? ",
						"坐下, " + GetAddress_Form(npchar) + ", 我们喝杯好的牙买加朗姆酒。 这对健康没坏处。 如果你想知道发生了什么 - 你永远找不到比这更好的地方, 我向你保证。 一些钱, 几杯像样的朗姆酒 - 你就会知道你需要知道的一切, 甚至更多, 相信一个老顾客... ",
						"嘿, 请坐, " + GetSexPhrase("我的好朋友","小姐") + ", 我们喝一杯... 为什么不和好伙伴喝一杯呢? 如果你有耐心, 慢慢喝, 小口喝, 你会听到很多有趣的事情... 有船长吹嘘他们的冒险, 还有很多人当他们不再能控制自己时会说出重要的事情... 很多人在那里消磨时间, 很多人有话要说, 相信我, " + GetSexPhrase("我的好朋友","小姐") + "。 ");
			link.l1 = "为什么不呢! 酒保! 朗姆酒, 我们俩的! ";
			link.l1.go = "sit_2";
		break;

		// 教堂生成器。 任务#2 -->
		case "Alcogol_GenQuest_Church_2_1":
			dialog.text = "当然! 你听说过吗... 强盗甚至抢劫教堂! ";
				link.l1 = "嗯, 听起来像海盗, 还能有谁... ";
				link.l1.go = "Alcogol_GenQuest_Church_2_2";
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskAlcash");
			break;
			
		case "Alcogol_GenQuest_Church_2_2":
			dialog.text = "什么海盗? 只是普通的陆地lubbers, 肯定是当地的那些... 如果是访客, 他们不会知道教堂的金库什么时候满。 而且他们无论如何也不会卷入那种麻烦。 ";
				link.l1 = "大胆的家伙, 肯定是。 他们如此勇敢地打开了一扇脆弱的门闩... ";
				link.l1.go = "Alcogol_GenQuest_Church_2_3";
			break;
			
		case "Alcogol_GenQuest_Church_2_3":
			dialog.text = "啊哈。 而且也是聪明的家伙。 谁会这样暴露自己? ";
				link.l1 = "真的。 整个教区都在存钱捐给教堂, 现在这些聪明的家伙用它发了财? 他们肯定会被抓住的。 现在全世界都会在找他们。 ";
				link.l1.go = "Alcogol_GenQuest_Church_2_4";
			break;
			
		case "Alcogol_GenQuest_Church_2_4":
			dialog.text = "几乎不可能。 谁会去找? 他们只是抢了教堂然后离开了城镇, 消失得无影无踪。 丛林很大, 非常大, 你会在那里找到世界末日。 几个月后人们就会忘记这一切, 记住我的话! ";
				link.l1 = "我不这么认为。 这种事不能被原谅。 ";
				link.l1.go = "Alcogol_GenQuest_Church_2_5";
			break;
			
		case "Alcogol_GenQuest_Church_2_5":
			dialog.text = "人的记忆就像一艘漏水的小船。 人们会忘记和原谅。 但是上帝? ! 他看到一切。 那是你需要害怕的。 我说, 十年前我的一个老伙伴发生了可怕的事情。 他也缺乏对造物主的尊重, 几乎直接去找了海魔... ";
				link.l1 = "抱歉朋友, 我得走了。 我们下次再谈你的那个伙伴。 再见。 ";
				link.l1.go = "Alcogol_GenQuest_Church_2_6";
			break;
			
		case "Alcogol_GenQuest_Church_2_6":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");			
			string sGenLocation = QuestGetGangLocation(PChar.GenQuest.ChurchQuest_2.QuestTown);
			PChar.GenQuest.ChurchQuest_2.QuestGangJungle = sGenLocation;
			SetFunctionLocationCondition("Church_GenQuest2_GenerateBandits", sGenLocation, false);
			locations[FindLocation(sGenLocation)].DisableEncounters = true;
			PChar.GenQuest.ChurchQuest_2.WayOfShortVariant = true; // 短变体检查需要
			SetFunctionTimerConditionParam("Church_GenQuest2_TimeIsLeft", 0, 0, 1, MakeInt(24 - GetHour()), false);
			Log_TestInfo("抢劫教堂的匪徒将在位置 - " + sGenLocation + " 搜索时间 - 1天");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "2");
			break;
		// < —教堂生成器。 任务#2
		//--> 奴隶商人
			case "Jamaica_ratH_1":
				dialog.text = "哦弗朗索瓦! 当然, 我记得那个人... 不, 我不知道。 但是, 你知道, 你可以问我们的女服务员关于他的事。 只要他住在这里, 她每晚都和他在一起。 她肯定是个婊子。 也许他对她说了什么。 ";
				link.l1 = "谢谢你的建议, 朋友。 我会去和她谈谈。 ";
				link.l1.go = "exit_sit";
				pchar.questTemp.Slavetrader = "FindRatJamaica_W";
			break;
			
			case "EscapeSlave_Villemstad_H1":
				dialog.text = "是的, 在公海上有时会发生非常奇怪的事情。 在我最后一次航行中, 我看到了一些非常... ";
				link.l1 = "继续, 告诉我, 只是不要太夸张。 我同时再给你拿些朗姆酒。 ";
				link.l1.go = "EscapeSlave_Villemstad_H2";
			break;
			
			case "EscapeSlave_Villemstad_H2":
				dialog.text = "我向上帝发誓, 高贵的先生/女士 - 我亲眼所见... 一艘船在航行, 但上面没有水手, 而是一些巨型猿类... 或猕猴... 猴子, 你知道。 ";
				link.l1 = "什么? ! 告诉我, 朋友, 你也在值班时喝酒吗? ";
				link.l1.go = "EscapeSlave_Villemstad_H3";
			break;
			
			case "EscapeSlave_Villemstad_H3":
				dialog.text = "如果我撒谎就让我失明! 你从未听说过猴子虾吗? 去他的, 虾哈哈! ... 猴子船。 ";
				link.l1 = "什么猴子船? ";
				link.l1.go = "EscapeSlave_Villemstad_H4";
			break;
			
			case "EscapeSlave_Villemstad_H4":
				dialog.text = "哦嗬, 我说我亲眼所见。 当时正在暴风雨中。 什么也看不见, 然后船不知从哪里出现了。 帆破了。 前帆和主帆都断了, 该死的, 一切都断了! 然而她却逆风行驶! \n甲板上有猿类... 很多, 像... 海豹群! 一只纯大猩猩站在舵轮旁! 九英尺高, 红衬衫, 胸前没有十字架而是鲨鱼牙齿... 眼睛是红色的, 獠牙闪闪发光, 它看到我们并喊了些什么... ";
				link.l1 = "你在胡说八道, 朋友。 你知道, 喝醉了会产生幻觉。 接下来你会告诉我她是飞翔的荷兰人。 ";
				link.l1.go = "EscapeSlave_Villemstad_H5";
			break;
			
			case "EscapeSlave_Villemstad_H5":
				dialog.text = "不, 她不是荷兰人。 我告诉你真相! 那是一艘三桅帆船, 船尾有铭文 - " + pchar.questTemp.Slavetrader.ShipName + "。 ";
				link.l1 = "该死的! 我想我知道你说的'猴子'是什么了。 确实, 朗姆酒能让人开口 - 只需要倾听... ";
				link.l1.go = "EscapeSlave_Villemstad_H6";
			break;
			
			case "EscapeSlave_Villemstad_H6":
				dialog.text = "看 - 我告诉过你! 而你不相信我! ... 好吧, 让我们再喝最后一杯, 我就走。 ";
				link.l1 = "好吧, 谢谢你有趣的故事。 我得走了。 祝你好运, 朋友。 ";
				link.l1.go = "exit_sit";
				Pchar.quest.Slavetrader_EscapeSlave.win_condition.l1 = "location";
				Pchar.quest.Slavetrader_EscapeSlave.win_condition.l1.location = pchar.questTemp.Slavetrader.Island.Shore;
				Pchar.quest.Slavetrader_EscapeSlave.function = "Slavetrader_EscapeSlaveInShore";
				AddQuestRecord("Slavetrader", "22_4");
				AddQuestUserData("Slavetrader", "sAreal", pchar.questTemp.SlavetraderAreal.add);
				pchar.questTemp.Slavetrader = "FindMayak";
			break;
		
		//荷兰策略, 对抗所有人
		case "Lucas_Tavern":
			DelMarkInTavernHWIC();
			dialog.text = "不, 船长。 水手的生活不适合我。 你知道, 我曾经也有过一艘船, 但是... 我运气真的很差。 ";
			link.l1 = "听着 - 我看到一艘不寻常的船停在附近 -'美凤'是她的名字。 我从未见过这样的船。 谁是船主? 也许它在出售? 我想看看。 ";
			link.l1.go = "Lucas_Tavern_1";
		break;
		
		case "Lucas_Tavern_1":
			dialog.text = "哈! 几乎不可能, 船长。 我认为那个中国家伙不会把船卖给你或任何人。 ";
			link.l1 = "一个中国人? 库拉索有中国人? 甚至有自己船的船长? ";
			link.l1.go = "Lucas_Tavern_2";
		break;
		
		case "Lucas_Tavern_2":
			dialog.text = "是的, 如你所见。 但实际上这不是他的船 - 它属于贸易公司。 他们说, 副总裁兼现在的代理总督罗登堡先生拥有它。 ";
			link.l1 = "那么, 马蒂亚斯.贝克退休了? ";
			link.l1.go = "Lucas_Tavern_3";
		break;
		
		case "Lucas_Tavern_3":
			dialog.text = "哈! 先生, 你真的应该多访问陆地 - 或者至少关心一下新闻。 马蒂亚斯.贝克被解职并监禁, 直到所有情况澄清。 ";
			link.l1 = "你不是在说吧! 确实, 我在海上待的时间太长了。 那是什么时候发生的? ";
			link.l1.go = "Lucas_Tavern_4";
		break;
		
		case "Lucas_Tavern_4":
			dialog.text = "实际上, 就在几天前。 一艘信使双桅船抵达港口。 它状况不佳, 显然参与了激烈的战斗。 船长直接向罗登堡先生汇报, 几小时后, 马蒂亚斯.贝克就被罗登堡先生和指挥官以涉嫌勾结英国情报机构的罪名逮捕。 ";
			link.l1 = "你说的事情很可怕。 库拉索的总督怎么会是英国间谍? ";
			link.l1.go = "Lucas_Tavern_5";
		break;
		
		case "Lucas_Tavern_5":
			dialog.text = "坦率地说, 我也很难相信。 我听说公司董事彼得.斯特伊弗桑特本人很快就会到达这里。 显然, 他将亲自进行调查。 ";
			link.l1 = "那么你是对的。 现在打扰罗登堡先生可能有风险。 ";
			link.l1.go = "Lucas_Tavern_6";
		break;
		
		case "Lucas_Tavern_6":
			dialog.text = "好想法, 船长! 更重要的是,'美凤'目前正在装货。 她刚刚从大陆南部海岸航行归来, 很快就会再次起航。 而且, 我告诉你, 那里发生了奇怪的事情。 荷兰水手和公司的卫兵被解除了职务, 另一批船员正在组建。 我以我一生中喝过的所有朗姆酒发誓, 那些新志愿者完全不同, 全是海盗。 强盗和恶棍! ";
			link.l1 = "确实是奇迹! 好吧, 真遗憾! 这么好的船... 好吧, 命运如此... 谢谢你有趣的故事和消息! 很高兴和你交谈! ";
			link.l1.go = "Lucas_Tavern_7";
		break;
		
		case "Lucas_Tavern_7":
			dialog.text = "好吧, 谢谢你的陪伴和朗姆酒, 船长! 有空再来! ";
			link.l1 = "我肯定会的! ";
			link.l1.go = "exit_sit";
			AddQuestRecord("Holl_Gambit", "3-44");
			pchar.questTemp.HWIC.Self = "AttackMeifeng";
			//设置美凤出海的中断
			pchar.quest.HWIC_Meifeng.win_condition.l1 = "Timer";
			pchar.quest.HWIC_Meifeng.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.HWIC_Meifeng.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.HWIC_Meifeng.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.HWIC_Meifeng.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.HWIC_Meifeng.function = "CreateMeifengOnMap";
			if(bImCasual) NewGameTip("探索模式: 计时器未禁用。 遵守最后期限! ");
			SetFunctionTimerCondition("QuestShipsTerms_Over", 0, 0, 12, false); // 计时器
			pchar.quest.Meifeng_fail.over = "yes"; //取消中断
			Group_DelCharacter("Meifeng_Empty", "Longway");
			Group_DeleteGroup("Meifeng_Empty");//从港口删除美凤
		break;
		
			//Jason --> 寻找逃兵
		case "FindFugitiveHb":
			npchar.quest.fugitive = "true";
			if (npchar.location == pchar.GenQuest.FindFugitive.City+"_tavern" && sti(pchar.GenQuest.FindFugitive.Chance) == 2)
			{
				pchar.GenQuest.FindFugitive.Shore = SelectQuestShoreLocation();
				dialog.text = "哈! "+pchar.GenQuest.FindFugitive.Name+"? 我知道, 我知道... 他非常不爱交际, 你的那个同事。 可以说是独狼。 他整天驾着他的长船沿着岛的海岸航行直到晚上。 人们认为他是渔民, 但实际上他是采珠人... 呵呵! 我敢肯定! ";
				link.l1 = "呵呵! 那么... 你能告诉我在哪里可以找到他吗? ";
				link.l1.go = "FindFugitiveHb_1";
			}
			else
			{
				dialog.text = ""+pchar.GenQuest.FindFugitive.Name+"? 不, 我发誓我从未听说过他... 但你 - 嗝! 你可以问我们的酒保 - 他肯定知道! ";
				link.l1 = "嗯... 好吧, 我会再问问。 好吧, 朋友, 谢谢你的陪伴。 再见! ";
				link.l1.go = "exit_sit";
			}
		break;
		
		case "FindFugitiveHb_1":
			dialog.text = "当然, 我可以! 每天早上你都可以在岸边的"+XI_ConvertString(pchar.GenQuest.FindFugitive.Shore+"Gen")+"找到他。 尽早来, 否则他会起航, 你就得等到第二天早上。 ";
			link.l1 = "谢谢! 你帮了我很大的忙, 朋友! 再见! ";
			link.l1.go = "exit_sit";
			pchar.GenQuest.FindFugitive.Chance = 3; // 让别人不再说
			AddQuestRecord("MayorsQuestsList", "12-3");
			AddQuestUserData("MayorsQuestsList", "sShore", XI_ConvertString(pchar.GenQuest.FindFugitive.Shore+"Gen"));
			sld = characterFromId("Fugitive");
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, true);
			sld.dialog.currentnode = "Fugitive_shore";
			LAi_SetLoginTime(sld, 4.0, 6.0);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.FindFugitive.Shore, "goto", "goto1");
		break;
		//< —寻找逃兵
		
		// 加勒比风俗
		case "trial_spy":
			dialog.text = "他在我们的造船厂闲逛, 向造船工人问这问那。 这就是他的倒霉之处。 有人向指挥官报告了镇上有可疑人员, 所以他被拘留了, 后来发现他实际上根本不是商人。 ";
			link.l1 = "我猜, 他是想偷你们造船工人的秘密项目? ";
			link.l1.go = "trial_spy_1";
		break;
		
		case "trial_spy_1":
			dialog.text = "谁知道呢? 但我很确定他首先对大帆船'阿拉坎塔拉'感兴趣! 嗝! 我可以发誓! 这艘船是总督先生亲自装备的, 所以我敢打赌这个恶棍试图打探她的消息。 ";
			link.l1 = "哈! 很可能。 总督肯定会在她上面装载有价值的东西... ";
			link.l1.go = "trial_spy_2";
		break;
		
		case "trial_spy_2":
			dialog.text = "那是不言而喻的! 我告诉你, 那肯定是值得关注的东西! 哦, 人们说渔民在这些水域看到了一艘外国军舰... 很可能是护卫舰。 也许那就是间谍来的地方? ";
			link.l1 = "是的, 可能... 好吧, 朋友, 谢谢你的陪伴, 但我得走了! ";
			link.l1.go = "exit_sit";
			pchar.questTemp.Trial = "spy_drink";
			
			if(CheckAttribute(pchar,"questTemp.trialHabitueId"))
			{
				if (GetCharacterIndex(pchar.questTemp.trialHabitueId) != -1)
				{
					sld = characterFromId(pchar.questTemp.trialHabitueId);
					sld.lifeday = 0;
					DeleteAttribute(pchar,"questTemp.trialHabitueId");
					LAi_CharacterDisableDialog(sld);
					DelLandQuestMark(sld);
				}
			}
			// belamour 传奇版 -->
			if (GetCharacterIndex("PortoBello_Poorman") < 0)
			{
				// 新乞丐
				sld = GetCharacter(NPC_GenerateCharacter("PortoBello_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, SPAIN, -1, false, "slave"));
				sld.city = "PortoBello";
				sld.location	= "PortoBello_town";
				sld.location.group = "goto";
				sld.location.locator = "goto15";
				sld.forStay.locator = "goto15"; //停留时生成的位置
				sld.forSit.locator0 = "goto3";
				sld.forSit.locator1 = "goto25"; //三种坐下时生成的位置
				sld.forSit.locator2 = "goto12";
				LAi_SetLoginTime(sld, 9.0, 21.99);
				sld.Dialog.Filename = "Common_poorman.c";
				LAi_SetPoorType(sld);
				LAi_SetHP(sld, 50.0, 50.0);
				sld.greeting = "poorman_male";
				LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			}
			sld = characterFromId("PortoBello_Poorman");
			LAi_RemoveLoginTime(sld);
			ChangeCharacterAddressGroup(sld, "Portobello_town", "goto", "goto15");
			AddLandQuestMark(sld, "questmarkmain");
			DelLandQuestMark(characterFromId("portobello_tavernkeeper"));
			// < —传奇版
			AddQuestRecord("Trial", "14");
		break;
		
		case "sit_2":
			Statistic_AddValue(pchar, "TavernDrink", 1);
			AddMoneyToCharacter(pchar, -2);
			//navy --> 酒精 - 朗姆酒计数;
			if(!IsEquipCharacterByArtefact(pchar, "totem_01"))
			{
				if (CheckAttribute(pchar, "questTemp.Rum"))
				{
					pchar.questTemp.Rum = sti(pchar.questTemp.Rum) + 1;
				}
				else pchar.questTemp.Rum = 1;
			}
			else 
			{
				if(CheckAttribute(pchar, "questTemp.Rum")) DeleteAttribute(pchar, "questTemp.Rum");
			}				
			//< —navy
			if(!CheckAttribute(pchar, "questTemp.TimeLock")) WaitDate("",0,0,0, 0, 30);
			
			if (CheckAttribute(pchar, "questTemp.Rum"))
			{
				DeleteAttribute(pchar, "chr_ai.drunk");
				if (sti(pchar.questTemp.Rum) < 3) LAi_AlcoholSetDrunk(pchar, 51, 5600);
				else
				{
					LAi_AlcoholSetDrunk(pchar, 71, sti(pchar.questTemp.Rum)*2800);
					Pchar.GenQuest.CamShuttle = makeint(sti(pchar.questTemp.Rum)/2); // Jason
				}
			}
			
			// Sinistra - 任务"导航星" ==>
			if (CheckAttribute(pchar, "questTemp.PZ_BasTerAlkash") && npchar.city == "baster")
			{
				dialog.text = "为你的健康和慷慨干杯! ";
				link.l1 = "朋友, 你在镇上见过中国人吗? ";
				link.l1.go = "PZ_BasTerAlkash_1";
				break;
			}
			// <== 任务"导航星" - Sinistra
			
			dialog.text = LinkRandPhrase("你是个真正的朋友/很棒的姑娘! 很高兴见到你! 干杯! ",
										 "嗝! 那是很棒的朗姆酒! 嗝... 干杯! ",
										 "为你的健康和慷慨干杯! ");
			link.l1 = "嘿, 那朗姆酒真烈。 好吧, 我得走了。 玩得开心! ";
			link.l1.go = "exit_sit";
			if (makeint(pchar.money) >=2)
			{
				link.l2 = "再来一杯, 你介意吗? ";
				link.l2.go = "sit_3";
			}

			link.l4 = LinkRandPhrase("感觉我在海上度过了永恒。 有什么消息吗? ",
									"人们怎么说? 当然, 我会给你买酒。 ",
									"告诉我, 朋友, 现在酒馆里流行什么故事? ");
			link.l4.go = "rumours_habitue";
		break;

		case "sit_3":
			int iSituation;
			if(IsEquipCharacterByArtefact(pchar, "totem_01")) iSituation = makeint(rand(3));
			else iSituation = makeint(rand(5));
			switch (iSituation)
			{
				case 0:
					dialog.text = "哦! 好主意! ";
					link.l1 = "酒保! 再来朗姆酒! ";
					link.l1.go = "sit_2";
				break;

				case 1:
					dialog.text = "敬你! 哦, 见鬼! 那是谁? ";
					link.l1 = "嗯? 什么? 哪里? 我一定是看错了。 ";
					link.l1.go = "sit_2";// to_do "sit_case_5_exit";
				break;
				
                case 2:
	         		dialog.text = "那我们喝吧! 再来一杯? ";
					link.l1 = "来吧! ";
					link.l1.go = "sit_2";
                break;				
				
				case 3:
					if(rand(1) == 0)
					{
						dialog.text = RandPhraseSimple("嘿, 你, " + GetAddress_Form(NPChar) + ", 你肯定认为每个人都崇拜你, 对吧? 好吧, 如果你问我, 你只是个普通的土匪! .. 还有杀人犯!'高贵的海盗'! 哈! 土匪就是土匪... 嗝... 不管是在陆地上还是在海上..",
							"嗝! " + GetSexPhrase("滚... 混蛋","婊子... 贱货") + "! 你想让我喝到不省人事 - 嗝 - 然后偷我所有的钱! ");
						link.l1 = "我看你已经喝够了... 去睡吧... 我也得走了... ";
						link.l1.go = "exit_sit";						
						link.l2 = "我不喜欢你的语气, 朋友。 注意你的舌头, 好吗? ";
						link.l2.go = "sit_case_2_enemy";
						link.l3 = "你刚才叫谁土匪, 你这陆地lubber? ! 让我们看看你肚子上有个洞时会说什么! ";
						link.l3.go = "sit_case_2_enemy2";
					link.l4 = "冷静点! 你忘了吗? 我是你唯一的真正朋友! ";
					link.l4.go = "sit_case_2_friend";		
					}
					else
					{
						// 贝尔特罗普船长, 27.06.21, 新变体
						/* if (rand(1) == 0)
						{
							Diag.CurrentNode = Diag.TempNode;
							AddDialogExitQuestFunction("Tavern_SetBadHabitue");
							DialogExit();
						}
						else
						{ */
							dialog.text = RandPhraseSimple("你为什么盯着我? 你会等到我昏倒 - 嗝 - 然后偷我所有的钱! 这些乌合之众是从哪里来的? ! 嗝... 这个酒馆里没有正派人的位置? ",
								"你尊重我吗? .. 是的, 你! 你尊重我吗? ! 你小心点... 我不是好惹的... 眼睛中间一击... 你就死定了... ");
							link.l1 = "朋友, 你醉得像头猪。 回家睡吧... 我也得走了... ";	
							link.l1.go = "exit_sit";
							link.l2 = "等等, 朋友。 注意你在和谁说话。 ";
							link.l2.go = "sit_case_2_enemy1";
							link.l3 = "你刚才说什么? ! 我会给你一个教训! ";
							link.l3.go = "sit_case_2_enemy2";
							link.l4 = "冷静点! 你忘了我吗? 我是你唯一的真正朋友! ";
							link.l4.go = "sit_case_2_friend";	
						//}
					}
				break;

				case 4:
					dialog.text = "听着! 你是个好人! 也许你会帮我... 处理一件事? ";
					link.l1 = "不, 我想我现在得走了。 ";
					link.l1.go = "exit_sit";
					link.l2 = "当然! 嗝! 我们是朋友... 不是吗? 嗝! ";
					link.l2.go = "sit_case_3";
				break;

				case 5:
					if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(110) || CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
					{
						dialog.text = "... 然后我抓住了他的刀刃... ";
						link.l1 = "... 然后她说... ";
						link.l1.go = "sit_2";
					}
					else
					{
						dialog.text = "... 然后我抓住了他的刀刃... ";
						link.l1 = "... 嗝! ... 然后她说... ";
						link.l1.go = "sit_case_4_exit";
					}
				break;
			}
		break;

		case "sit_case_5_exit": // 决斗
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("fighting");
		break;

		case "sit_case_4_exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("without_memory");
		break;

		case "sit_case_3":
			dialog.snd = "Voice\HADI\HADI037";
			dialog.text = "关-关键是... 其-其中一个士兵侮辱了我。 就-是这样! ";
			link.l1 = "一-一个士兵? 不, 我想我还是算了。 ";
			link.l1.go = "exit_sit";
			link.l2 = "冷静点! 你忘了我吗? 我是你唯一的真正朋友! ";
			link.l2.go = "sit_2";
		break;

		case "sit_case_2_friend":
			dialog.snd = "Voice\HADI\HADI038";
			dialog.text = "你? 你算什么朋友? 不! 你... 你想杀我! 就-是这样! ";
			link.l1 = "好吧, 你肯定已经喝够了。 再见。 ";
			link.l1.go = "exit_sit";
			link.l2 = "什么? 我会证明给你看我不-不会杀你! 我... 我会砍掉你的手! ... 没-没有手你就不会被杀了! ... 嗝! ";
			link.l2.go = "sit_case_2_friend_2";
		break;

		case "sit_case_2_friend_2":
			dialog.snd = "Voice\HADI\HADI039";
			dialog.text = "啊! 把他/她带走! ";
			link.l1 = "冷静点... 嗝... 不会疼的! ... 比刮胡子还不疼! ";
			link.l1.go = "tavern_keeper";
		break;

		case "sit_case_2_enemy":
			dialog.snd = "Voice\HADI\HADI040";
			dialog.text = "别想吓我! 嗝! 我没那么容易被吓到! .. 而你 - 你应该被绞死... 和你所有的同类一起 - 嗝! 你可以竖起羽毛 - 但你仍然散发着烂鱼的气味! 我和你这种人说话时不会注意我的舌头! 你们都让我恶心! ";
			link.l1 = "啊, 我为什么要和这样的醉鬼说话... 我想我得去呼吸点新鲜空气... ";
			link.l1.go = "exit_sit1";
			link.l2 = "你太胆大了, 朋友。 我会把你的话塞回你的喉咙! ";
			link.l2.go = "sit_case_2_enemy3";
		break;

		case "sit_case_2_enemy1":		
			dialog.snd = "Voice\HADI\HADI040";
			dialog.text = "什-什么? ! 我会亲手勒死你! 嗝... 到目前为止还没有人能逃脱我 - 嗝! ";
			link.l1 = "你不是醉猪吗? 破坏这么美好的夜晚... 好吧, 去抓你的蟑螂吧 - 我走了。 ";
			link.l1.go = "exit_sit1";
			link.l2 = RandSwear() + "我看你不打算安静下来。 那么该上一堂礼貌课了。 ";
			link.l2.go = "sit_case_2_enemy3";
		break;
		
		case "sit_case_2_enemy2":	
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("靠近点, 你这个流氓! 你会得到应有的惩罚! ", RandSwear() + "我会给你应有的惩罚! ","哈! 好吧, 水手 - 让我们看看你在陆地上的表现! ");
				link.l1 = RandPhraseSimple(RandPhraseSimple("我发誓你会后悔的! ","我会把你该死的舌头剪短! "), RandPhraseSimple("我会像杀猪一样把你开膛破肚, 从你的屁股到你那所谓的嘴! ","我发誓我会让你闭嘴! "));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "嘿, 伙计们! 让我们把这个垃圾赶出我们的城镇! ";
				link.l1 = RandPhraseSimple(RandSwear() + "祈祷吧, 混蛋! ","哦, 所以你不是一个人? ! 好吧, 你在地狱里会有伴的! ");
				link.l1.go = "fight_right_now_1";
			}
		break;
		
		case "sit_case_2_enemy3":	
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("靠近点, 你这个流氓! 你会得到应有的惩罚! ", RandSwear() + "我会给你应有的惩罚! ","哈! 好吧, 水手 - 让我们看看你在陆地上的表现! ");
				link.l1 = RandPhraseSimple(RandPhraseSimple("我发誓你会后悔的! ","我会把你该死的舌头剪短! "), RandPhraseSimple("我会像杀猪一样把你开膛破肚, 从你的屁股到你那所谓的嘴! ","我发誓我会让你闭嘴! "));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "嘿, 伙计们! 让我们把这个垃圾赶出我们的城镇! ";
				link.l1 = RandPhraseSimple(RandSwear() + "祈祷吧, 混蛋! ","哦, 所以你不是一个人? ! 好吧, 你在地狱里会有伴的! ");
				link.l1.go = "fight_right_now_1";
			}
		break;		
		
		case "exit_sit":			
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;

		case "exit_sit1":
			ChangeCharacterComplexReputationToNeutral(pchar,"nobility", 2.0);			
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;
				
		case "tavern_keeper":			
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("tavern_keeper");
		break;
		
		// 贝尔特罗普船长, 27.06.21, 新变体
		case "bad_habitue":
			dialog.text = "嘿, 我有件事不明白! 我一转过街角, 某个新来的菜鸟就占了我的位置。 离开这里! ";
			link.l1 = "总是这样: 刚坐在桌子旁, 就发现已经有人了... 你占着座位吧, 我反正要走了。 ";
			link.l1.go = "bad_habitue1";
			link.l2 = "再从你肮脏的嘴里说一句这样的话, 那将是你这辈子说的最后一句话, 明白吗? ";
			link.l2.go = "bad_habitue2";
			link.l3 = "我不知道这是否真的是你的位置, 但我不会让你这样跟我说话。 注意你的言辞。 ";
			link.l3.go = "bad_habitue3";
		break;
		
		case "bad_habitue1":
			DialogExit();
			pchar.questTemp.BadHabitueSit = true; // 就座属性
			AddDialogExitQuest("exit_sit");
		break;
		
		case "bad_habitue2":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("来吧, 流氓们! 你们即将得到应有的惩罚! ", RandSwear() + "现在我要好好教训你们! ","哈! 来吧, 水手 - 让我们看看你在陆地上的本事! ") ;
				link.l1 = RandPhraseSimple(RandPhraseSimple("我发誓你会后悔的! ","我会把你该死的舌头剪短! "), RandPhraseSimple("我会像杀猪一样把你开膛破肚, 从你的屁股到你那所谓的嘴! ","我发誓我会让你闭嘴! "));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "来吧伙计们! 让我们把这个垃圾赶出我们的城镇! ";
				link.l1 = RandPhraseSimple(RandSwear() + "祈祷吧, 混蛋! ","哦, 你不是一个人! 好吧, 你在地狱里会有伴的! ");
				link.l1.go = "fight_right_now_1";
			}
		break;
		
		case "bad_habitue3":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("来吧, 小混混们! 你们马上就要吃不了兜着走了! ", RandSwear() + "现在我要好好收拾你们! ","哈! 来吧, 水手 —让我看看你在陆地上有什么本事! ");
				link.l1 = RandPhraseSimple(RandPhraseSimple("我发誓你会为此后悔的! ","我要割断你那该死的舌头! "), RandPhraseSimple("我要像杀猪一样剖开你, 从你的屁股一直剖到你那被称作嘴的臭洞! ","我发誓我会让你闭嘴的! "));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "来吧, 伙计们! 让我们把这个祸害从我们镇上清除出去! ";
				link.l1 = RandPhraseSimple(RandSwear() + "祈祷吧, 你们这些混蛋! ","哦, 你不是一个人! 好吧, 你在地狱里会有伴的! ");
				link.l1.go = "fight_right_now_1";
			}
		break;
		
		//--> Sinistra 旧罪的漫长阴影
		case "DTSG_NightIskat":
			dialog.text = "当... 当然, 我们都互相认识! 你为什么这么问? ";
            link.l1 = "我想去拜访那个放债人, 却发现他卖掉了老房子。 你知道他现在住在哪里吗? ";
            link.l1.go = "DTSG_NightIskat_2";
		break;
		
		case "DTSG_NightIskat_2":
			dialog.text = "你这么晚找他干嘛, 嗝? 早上再去银行不就行了! ";
            link.l1 = "我急需钱。 让那个守财奴也为他的钱干点活吧! 他们这种人总是说我们这些人只会乞讨。 抱怨, 而且从不还钱。 ";
            link.l1.go = "DTSG_NightIskat_3";
		break;
		
		case "DTSG_NightIskat_3":
			dialog.text = "哈哈哈哈, 嗝, 对, 让他干活! 你知道我们光荣的舰队伍德船长曾经住在哪里吗? ";
            link.l1 = "当然, 谁不认识理查德。 现在那个银行家住在哪里? ";
            link.l1.go = "DTSG_NightIskat_4";
		break;
		
		case "DTSG_NightIskat_4":
			dialog.text = "你说得对。 当你到了那里, 朋友 —告诉他, 他太得意忘形了。 ";
            link.l1 = "嘿嘿, 我一定会的。 再见。 ";
            link.l1.go = "DTSG_NightIskat_5";
		break;
		
		case "DTSG_NightIskat_5":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DTSG_NightIskat");
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuest("exit_sit");
			
			chrDisableReloadToLocation = true;
			sld = CharacterFromID("Knippel");
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Knippel_SluhSmertFleetWood";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		//< —旧罪的漫长阴影
		
		//--> 引路之星
		case "PZ_BasTerAlkash_1":
			dialog.text = "哈哈哈哈, 我见过中国人吗? 我们都见过! ";
			link.l1 = "有什么好笑的? 我不是在说一个巡回马戏团, 如果那是你所想的。 我在说一个战士, 一个海军军官。 ";
			link.l1.go = "PZ_BasTerAlkash_2";
		break;
		
		case "PZ_BasTerAlkash_2":
			dialog.text = "啊, 我明白你的意思了! 是的, 我见过他。 即使清醒之后, 我也无法停止想起他... 我忘不了! ";
			link.l1 = "这很有趣。 继续说。 再喝一杯 —你现在可能在喝酒是为了忘记这一切。 在你喝之前, 告诉我你看到了什么。 ";
			link.l1.go = "PZ_BasTerAlkash_3";
		break;
		
		case "PZ_BasTerAlkash_3":
			dialog.text = "什么巡回马戏团, 见鬼去吧! 他跳着。 旋转着, 挥舞着那把军刀 —我从未见过有人如此熟练。 如此可怕地使用武器。 ";
			link.l1 = "听起来像他。 他在和谁打架? 你还记得吗? ";
			link.l1.go = "PZ_BasTerAlkash_4";
		break;
		
		case "PZ_BasTerAlkash_4":
			dialog.text = "卫兵, 伙计! 他还眯着眼睛盯着他们! 不过, 我觉得他总是那样。 你怎么看? ";
			link.l1 = "我不知道, 伙计。 继续说。 他们认为他是间谍吗? 为什么卫兵要攻击他? ";
			link.l1.go = "PZ_BasTerAlkash_5";
		break;
		
		case "PZ_BasTerAlkash_5":
			dialog.text = "谁知道呢? 他们试图弄清楚他在镇上做什么... ";
			link.l1 = "那么, 他们逮捕他了吗? 还是... ";
			link.l1.go = "PZ_BasTerAlkash_6";
		break;
		
		case "PZ_BasTerAlkash_6":
			dialog.text = "哈, 别做梦了! 他们抓不到他。 他在城里砍倒了卫兵, 逃进了丛林。 他们派了好几队人去追他, 但没有一个回来。 你能想象吗? 他把那个洞穴变成了一个真正的堡垒! ";
			link.l1 = "真了不起。 休息一下, 试着忘记吧。 我想我现在该走了 —我的头在打转。 ";
			link.l1.go = "PZ_BasTerAlkash_7";
		break;
		
		case "PZ_BasTerAlkash_7":
			DialogExit();
			bDisableLandEncounters = true;
			DeleteAttribute(pchar, "questTemp.PZ_BasTerTavern");
			DeleteAttribute(pchar, "questTemp.PZ_BasTerAlkash");
			pchar.questTemp.PZ_BasTerAlkash2 = true;
			DeleteQuestCondition("PZ_BasTer_Opozdal");
			pchar.questTemp.PZ_BasTerTurma = true;
			AddLandQuestMarkToPhantom("baster_prison", "basterJailOff");
			DelMapQuestMarkIsland("Guadeloupe");
			AddQuestRecord("PZ", "3");
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuest("exit_sit");
			
			PChar.quest.PZ_BasTerPeshera.win_condition.l1 = "location";
			PChar.quest.PZ_BasTerPeshera.win_condition.l1.location = "瓜德罗普洞穴入口";
			PChar.quest.PZ_BasTerPeshera.win_condition = "PZ_BasTerPeshera";
			
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
		break;
		
		case "Sotta1":
			dialog.text = "我自己没见过他 —他一直在总督办公室附近晃悠, 嗯! 但他的船员在这里举行了一场盛大的派对。 ";
			link.l1 = "是这样吗? ";
			link.l1.go = "Sotta2";
		break;
		
		case "Sotta2":
			dialog.text = "大家都说他是个商人。 但我告诉你, 他的船员看起来可不像是酒馆里的垃圾! 他们的样子就好像... 好像... 怎么说呢... ?";
			link.l1 = "我明白了。 谢谢你的陪伴, 伙计。 放松点。 ";
			link.l1.go = "exit_sit";
			
			npchar.questTemp.Sotta = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Lutter1":
			dialog.text = "我在庆祝! 谁说我是一个人? 你在这里, 伙计! 至于马特, 这迟早会发生的。 ";
			link.l1 = "你为什么这么说? 我听说他是一个非常幸运的海盗, 多年来一直受到命运的眷顾! ";
			link.l1.go = "Lutter2";
		break;
		
		case "Lutter2":
			dialog.text = "哼, 不只是命运, 嗯! 他是个独行海盗, 不是兄弟会的成员! 而那些人不会长久... 不过, 我听说人们传言他曾经在勒瓦瑟的羽翼下。 ";
			link.l1 = "没错, 独行侠不会长久。 好吧, 庆祝吧。 我得走了, 伙计。 ";
			link.l1.go = "exit_sit";
			
			npchar.questTemp.Lutter = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Sepp1":
			dialog.text = "呃, 是的, 我从没见过他。 他是谁? ";
			link.l1 = "他是群岛上最快的船只之一'万丹'号双桅横帆船的船长。 听说过他吗? ";
			link.l1.go = "Sepp2";
		break;
		
		case "Sepp2":
			pchar.questTemp.PZ.TortugaHabitueBlock = true;
			
			dialog.text = "呃, 不, 我对船不感兴趣, 伙计, 呃! 我们再来一杯怎么样? ";
			link.l1 = "我不喝了。 反正我在这里没得到我想要的东西。 ";
			link.l1.go = "exit_sit";
		break;
		//< —引路之星
		
	}
}

bool CheckFreeSitFront(ref _npchar)
{
 	ref rCharacter; //ищeм
	int n;

	if (!CheckAttribute(_npchar, "Default.ToLocator")) return false;
	
	for (n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (CheckAttribute(rCharacter, "location") && rCharacter.location == _npchar.location)
		{
            if (rCharacter.location.locator == _npchar.Default.ToLocator)
                return  false;
		}
    }
    return  true;
}
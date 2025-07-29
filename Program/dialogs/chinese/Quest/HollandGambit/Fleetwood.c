// 理查德.弗利特伍德 - 英国船长
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				if (pchar.questTemp.HWIC.Eng == "Start_main")
				{
					dialog.text = "问候你, 船长! 别被我的样子分心, 我很好, 几乎失明, 但我很好。 让我自我介绍一下, 我是理查德.弗利特伍德。 ";
					link.l1 = "日安, 很高兴见到你, 我是" +GetFullName(pchar)+ "船长。 ";
					link.l1.go = "First_Task";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Eng == "GotoPortoffice")
				{
					if (sti(Pchar.Ship.Type) != SHIP_NOTUSED)
					{
						dialog.text = "我让你停泊你的船。 你甚至听我说吗? ";
						link.l1 = "当然, 我听了。 我会处理的。 ";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "那么, 你又来了。 指挥'瓦尔基里'号 - 我的船员已经被告知细节 - 航行到布里奇敦。 拜访城市里的每个相关人员, 传播我们谈过的流言。 然后准备好让那个混蛋攻击。 不要更换船只, 也不要组成中队, 否则他会怀疑有陷阱, 不会出现\n你必须登上他的船, 把她送到圣约翰。 必须找到海盗的日志, 因为这是我们能找到的卢卡斯.罗登堡参与的唯一证据。 我相信你会处理好的。 祝你好运, 船长。 ";
						link.l1 = "感谢! 我会按我们的计划完成任务。 ";
						link.l1.go = "First_Task_3";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
					}
					break;
				}
				if (pchar.questTemp.HWIC.Eng == "MirageTake")//现在开始检查船只
				{
					pchar.quest.ToAntiguaMirageOver.over = "yes"; //取消计时器
					int iMir = 0;
					int iVal = 0;
					for(i = 0; i < COMPANION_MAX; i++)
					{
						iTemp = GetCompanionIndex(PChar, i);
						if(iTemp > 0)
						{
							sld = GetCharacter(iTemp);
							pchar.questTemp.HWIC.Eng.CompanionIndex = sld.Index;
							if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MIRAGE)
							{
							iMir = 1;
							RealShips[sti(sld.Ship.Type)].ship.upgrades.hull = 1;//清洁船体
							SetShipSailsFromFile(sld, "ships/parus_silk.tga");
							SetSailsColor(sld, 0);//白色棉质帆
							DeleteAttribute(sld, "ship.sails");//修理帆
							DeleteAttribute(sld, "ship.masts");//返回桅杆
							}
							if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_VALCIRIA) iVal = 1;
						}
					}//设置中队中船只存在的标志。 
					if (iMir == 1 && iVal == 0)//失去瓦尔基里
					{
						dialog.text = "你回来了, 船长... 我已经知道你航行的一切。 ";
						link.l1 = "是吗? 那你一定知道... ";
						link.l1.go = "Fleetwood_lostVal";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
						break;
					}
					if (iMir == 0 && iVal == 1)//失去幻影
					{
						dialog.text = "你回来了, 船长... 我已经知道你航行的一切。 ";
						link.l1 = "是吗? 那你一定知道... ";
						link.l1.go = "Fleetwood_lostMir";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
						break;
					}
					if (iMir == 0 && iVal == 0)//这更糟
					{
						dialog.text = "你回来了, 船长... 我已经知道你航行的一切。 ";
						link.l1 = "是吗? 那你一定知道... ";
						link.l1.go = "Fleetwood_lostFull";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
						break;
					}
						dialog.text = "你回来了, 船长... 我已经知道你航行的一切。 ";
						link.l1 = "是吗? 那你一定知道... ";
					link.l1.go = "Fleetwood_complete";
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					break;
				}
				if (pchar.questTemp.HWIC.Eng == "toAntigua")
				{
					dialog.text = "问候你, 我的朋友! 很高兴见到你! 你的船上有阿比盖尔吗? ";
					link.l1 = "不幸的是, 没有, 理查德。 她拒绝和我一起去, 因为她的离开对她父亲来说是一个沉重的打击, 他已经失去了所有的钱。 我决定处理这个问题, 找到所罗门的钱和那个岛... ";
					link.l1.go = "Fleetwood_LastTask";
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					break;
				}
				dialog.text = "还有别的事吗, 船长? ";
				link.l1 = "没有, 我已经要走了。 ";
				link.l1.go = "exit";		
				NextDiag.TempNode = "First time";
			}
				dialog.text = "还有别的事吗, 船长? ";
				link.l1 = "没有, 我已经要走了。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Fleetwood_abordage":
			PlaySound("Voice\English\hambit\Richard Flitwood-03.wav");
			dialog.text = "该死的海盗! 你赢得了登船战斗, 但我仍会履行我的职责。 我已安排点燃火药室, 我的船很快就会和你的'幽灵船'一起爆炸。 你再也不能击沉任何英国船只了。 我将光荣地死去! ";
			link.l1 = "很遗憾让你失望, 但你错了, 弗利特伍德。 我的船上没有海盗, 我之前已经处理了他们。 我需要你, 这艘船是一个很好的陷阱。 \n客气话够了, 我还是得杀了你, 逃离你燃烧的 tub! ";
			link.l1.go = "Fleetwood_abordage_1";
		break;
		
		case "Fleetwood_abordage_1":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("PrepareToBoom"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.HWIC.Holl = "FleetwoodCapture";
			pchar.GenQuest.Detonation = true; // patch-4
		break;
		
		case "First_Task":
			dialog.text = "查理已经告诉我你成功拦截了敌人的贸易商队。 很高兴见到你, 英国需要这样勇敢的船长。 现在, 让我告诉你一些非常重要的事情。 ";
			link.l1 = "我在听, 弗利特伍德先生。 ";
			link.l1.go = "First_Task_1";			
		break;
		
		case "First_Task_1":
			dialog.text = "一个海盗在群岛上犯下暴力行为, 伪装成'飞翔的荷兰人', 一艘传奇的幽灵船。 他假装是'飞翔的荷兰人', 一艘传奇的幽灵船。 我确定他是荷兰人, 但他不会飞。 我倾向于认为这是荷兰西印度公司副董事卢卡斯.罗登堡的雇佣兵。 \n罗登堡已经对英国发动了一场影子贸易战 - 这艘'幽灵船'只攻击英国国旗的贸易船只。 公司在不打真正战争的情况下削弱我们在该地区的影响力至关重要。 \n我追捕这艘幽灵船有一段时间了, 但她的船长是一位非常有经验的水手, 他的船速度快且狡猾。 \n既然在公开战斗中无法抓住这只豺狼, 那么我们应该狡猾地行动, 最近对我的暗杀企图将对我们非常有利。 你怎么看, 船长? 你害怕吗? ";
			link.l1 = "不可能。 我很高兴帮助你追踪并击沉这个混蛋。 你打算让我这么做, 对吗? ";
			link.l1.go = "First_Task_2";	
		break;
		
		case "First_Task_2":
			dialog.text = "你说得对。 现在, 我们讨论细节。 我的人会散布谣言说我快死了, 并把我的船'瓦尔基里'卖给你。 接下来, 我们将继续我们的小骗局。 你将假装是一个从我这里买了双桅横帆船并摆脱了大部分大炮的商人。 \n因此, 你的任务是航行到巴巴多斯, 告诉那里的每个人, 你的货舱里装满了有价值的货物, 你的口袋里装满了硬币。 让他们知道你很快就要起航。 扮演一个贪婪。 简单但富有的商人角色。 \n我们该死的荷兰人通过布里奇敦获取关于贸易船的信息。 不知道到底是谁提供的。 每个人都受到怀疑 - 从当地商人到总督, 尽管最后一种可能性非常可怕。 \n指挥我的'瓦尔基里'号和她的船员。 但首先, 你应该把所有的船留在这里, 我已经和当地港口主管谈过了, 你的旗舰每月需要10,000比索。 \n一旦完成, 回到我这里, 我会安排。 啊, 船长, 别忘了拿走你捕获银色商队的分成和给港口主管的一万比索, 钱在抽屉的箱子里。 ";
			link.l1 = "我明白了, 弗利特伍德先生。 我要去见港口主管。 ";
			link.l1.go = "exit";	
			pchar.questTemp.HWIC.Eng = "GotoPortoffice";
			bDisableFastReload = false;//打开快速传送
			DeleteAttribute(pchar, "questTemp.HWIC.CanTake");//其他选项不再可能
			AddLandQuestMark(characterFromId("SentJons_PortMan"), "questmarkmain");
		break;
		
		case "First_Task_3":
			DialogExit();
			pchar.questTemp.HWIC.TakeQuestShip = "true";//所有港口不可用直到任务完成, 船也不能卖
			pchar.questTemp.HWIC.EngEquip = "true"; //士兵形式
			pchar.questTemp.HWIC.Eng = "GotoBridgetown";
			GetValckiriaToCharacter(pchar);
			pchar.quest.Knippel_Officer.win_condition.l1 = "location";
			pchar.quest.Knippel_Officer.win_condition.l1.location = "SentJons_houseSP3";
			pchar.quest.Knippel_Officer.function = "KnippelToOfficer";
			pchar.questTemp.HWIC.Eng.BridgeCounter = 0;//任务中访问布里奇敦信件的计数器
			AddQuestRecord("Holl_Gambit", "2-5");
			AddMapQuestMarkCity("Bridgetown", false);
			AddLandQuestMark(characterFromId("Bridgetown_trader"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_shipyarder"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_Mayor"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_tavernkeeper"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_usurer"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_PortMan"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_Hostess"), "questmarkmain");
		break;
		
		//夺取船只
		case "Fleetwood_lostMir":
			dialog.text = "是的, 我知道你未能完成捕获海盗船的任务。 我所有的计划都毁了。 我要把'瓦尔基里'从你那里拿走。 你现在可以走了, 我不需要你的服务。 ";
			link.l1 = "对此我很抱歉。 再见, 弗利特伍德先生。 ";
			link.l1.go = "Fleetwood_RemoveShip";
			pchar.questTemp.HWIC.Eng.ShipType = SHIP_VALCIRIA;
		break;
		
		case "Fleetwood_lostVal":
			dialog.text = "是的, 我知道你失去了'瓦尔基里'。 这是最不可接受的... 我要拿走捕获的海盗船。 你现在可以走了, 我不需要你的服务。 ";
			link.l1 = "对此我很抱歉。 再见, 弗利特伍德先生。 ";
			link.l1.go = "Fleetwood_RemoveShip";
			pchar.questTemp.HWIC.Eng.ShipType = SHIP_MIRAGE;
		break;
		
		case "Fleetwood_lostFull":
			dialog.text = "是的, 我知道你是个罕见的混乱者和笨拙者。 你没有捕获海盗船, 还失去了我的'瓦尔基里'。 我真的对你很失望。 滚出去! ";
			link.l1 = "对此我很抱歉。 再见, 弗利特伍德先生。 ";
			link.l1.go = "exit";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("Knippel");
			AddDialogExitQuestFunction("LandEnc_OfficerFired");//从军官中解雇克尼佩尔
			sld = characterFromId("Knippel");
			ChangeCharacterAddressGroup(sld, "SentJons_houseH1", "goto", "goto1");//克尼佩尔回家
			pchar.questTemp.HWIC.Eng = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//打开港口
			DeleteAttribute(pchar, "questTemp.HWIC.EngEquip");
			pchar.questTemp.HWIC.Detector = "eng_fail";
			AddSimpleRumourCity("他们说你失败了理查德.弗利特伍德的一些秘密任务。 好吧, 你现在在安提瓜无事可做... ", "SentJons", 20, 3, "");
		break;
		
		case "Fleetwood_RemoveShip":
			DialogExit();
			AddDialogExitQuestFunction("Fleetwood_RemoveShip");
			pchar.questTemp.HWIC.Eng = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//打开港口
			DeleteAttribute(pchar, "questTemp.HWIC.EngEquip");
			pchar.questTemp.HWIC.Detector = "eng_fail";
			AddSimpleRumourCity("他们说你失败了理查德.弗利特伍德的一些秘密任务。 好吧, 你现在在安提瓜无事可做... ", "SentJons", 20, 3, "");
		break;
		
		case "Fleetwood_complete":
			pchar.questTemp.HWIC.Eng.ShipType = SHIP_VALCIRIA;
			AddDialogExitQuestFunction("Fleetwood_RemoveShip");	
			if (CheckCharacterItem(pchar, "JacobJournal"))//检查日志
			{
				dialog.text = "是的, 我知道你成功完成了我们的计划。 你消灭了邪恶的海盗, 捕获了他的船。 她的真名是什么? ";
				link.l1 = "幻影";
				link.l1.go = "Abigile";
			}
			else//没有日志 - 任务没有继续
			{
				dialog.text = "是的, 我知道你成功完成了我们的计划。 你消灭了邪恶的海盗, 捕获了他的船。 我会把我的'瓦尔基里'拿回来。 你可以把海盗船作为战利品。 它也可以作为某种... 补偿。 你停泊在港口的船在码头起火时烧毁了。 对不起, " +pchar.name+ "... 我希望幽灵船能更好地为你服务。 \n我已下令将你新船的顽固污垢和海藻清理干净。 他们还会给你的美人穿上最好的棉布新帆。 \n最后, 请接受你10万比索的奖励和这个导航工具。 我一直想把它送给一位有价值的水手, 你在那里做得很好! 好吧, 是时候说再见了, 我在这里的事情已经完成, 应该返回欧洲。 祝你好运, 船长! ";
				link.l1 = "你也一样, 理查德! ";
				link.l1.go = "exit";
				LocatorReloadEnterDisable("SentJons_houseSP3", "reload2", true);//把弗利特伍德关在房间里, 让他坐在那里
				pchar.questTemp.HWIC.Eng = "end";
				pchar.questTemp.HWIC.Detector = "eng_win_half";
				CloseQuestHeader("Holl_Gambit");
			}
			AddMoneyToCharacter(pchar, 100000);
			GiveItem2Character(pchar, "bussol");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//打开港口
			DeleteAttribute(pchar, "questTemp.HWIC.EngEquip");
			AddSimpleRumourCity("他们说你和理查德.弗利特伍德计划了一些军事行动, 你亲自摧毁了那个一直抢劫我们贸易船的难以捉摸的海盗。 你是个真正的英雄, 船长! ", "SentJons", 20, 3, "");
		break;
		
		case "Abigile":
			dialog.text = "幻影? 我会说, 这是一个非常合适的名字... 我要把我的'瓦尔基里'从你那里拿回来, 因此你可以把海盗船作为战利品。 它也可以作为某种补偿。 你停泊在港口的船在码头起火时烧毁了。 对不起, " +pchar.name+ "... 我希望幽灵船能更好地为你服务。 \n我已下令将你新船的顽固污垢和海藻清理干净。 他们还会给你的美人穿上最好的棉布新帆。 \n最后, 接受你10万比索的奖励和这个导航工具, 我一直想把它交给一位有价值的水手... 你在那里做得很好, 我为你骄傲! 你有那个混蛋的日志吗? ";
			link.l1 = "是的, 当然。 给你, 拿着。 我想问你一件事, 卢卡斯.罗登堡的雇佣兵中有没有... 亚洲人? ";
			link.l1.go = "Abigile_1";			
		break;
		
		case "Abigile_1":
			RemoveItems(PChar, "JacobJournal", 1);
			dialog.text = "是的, 有。 中国的朗威, 他的私人船'美凤'的船长。 你从海盗日志里读到的吗? 让我们看看... (阅读) 好吧, 好吧。 正如我所料, 卢卡斯.罗登堡是这一切的幕后黑手! 好吧, 不管怎样, 现在这不关我们的事... 我们的总督会处理这个混蛋。 卢卡斯.罗登堡将不得不为他所做的一切负责! ";
			link.l1 = "嗯, 有趣, 英国总督将如何能够'处理'荷兰的臣民? ";
			link.l1.go = "Abigile_2";			
		break;
		
		case "Abigile_2":
			dialog.text = "总有政治手段可以利用, 我亲爱的朋友... 荷兰将不得不承认他们对英国发动了贸易战, 但他们不太可能这样做。 相反, 他们会把一切都归咎于罗登堡。 卢卡斯可能会失去他的职位, 也可能不会。 无论哪种方式, 他的职业生涯都将遭受沉重打击。 \n然而, 现在这不是我们的事, 船长。 你已经很好地完成了你的部分工作。 这就是为什么我还有另一件非常微妙的事情要你做。 ";
			link.l1 = "我在听, 理查德。 这次英国王室的下一个敌人是谁? ";
			link.l1.go = "Abigile_3";			
		break;
		
		case "Abigile_3":
			dialog.text = "不, 这次我想请你处理更个人化和和平的事情。 让我给你讲一个简短的故事, 顺便说一下, 这与你的'幻影'有关。 ";
			link.l1 = "继续。 ";
			link.l1.go = "Abigile_4";			
		break;
		
		case "Abigile_4":
			dialog.text = "在你我相遇的一个月前, 我正在进行一次突袭, 追捕幽灵船。 它在马提尼克岛以南, 靠近经度64度41分。 我们听到远处某处有战斗, 但风太弱, 所以我们没有及时赶到。 一艘英国长笛船在某个甚至没有在地图上标出的小岛附近被幽灵船击沉\n我没能抓住海盗, 决定访问那个岛, 希望能找到任何幸存者。 我找到了他们。 一对犹太难民, 父女。 女孩叫阿比盖尔, 她很漂亮! 一个活生生的奇迹... 我把他们带上船, 送到了库拉索, 尽管她的父亲所罗门对我没有多少同情\n据我所知, 他认为我是击沉他们船只的海盗, 老人对船只及其区别知之甚少。 在那次小航行中, 我和阿比盖尔成为了朋友, 或者, 说实话, 彼此相爱。 这不是一个故事吗? \n我最近发现, 那个混蛋罗登堡已经向我的阿比盖尔求爱了一段时间, 想想看! 我打算把她带到这里, 一旦我解决了她爸爸丢失的钱的问题, 我提到过他把所有的钱都藏在那个岛上。 我没能找到它的位置。 我们不能再等了\n由于我的健康仍然不允许我自己起航, 我请你去威廉斯塔德, 找到阿比盖尔, 把她带到这里。 提到我的名字, 她会信任你。 ";
			link.l1 = "在这件事上没有看到任何问题。 我现在准备起航。 ";
			link.l1.go = "Abigile_5";			
		break;
		
		case "Abigile_5":
			PlaySound("Voice\English\hambit\Richard Flitwood-02.wav");
			dialog.text = "太好了! 我很高兴可以指望你, " +pchar.name+ "。 你的工作会得到很好的报酬, 别担心。 ";
			link.l1 = "我不会让你等太久的。 很快见, 理查德! ";
			link.l1.go = "Abigile_6";			
		break;
		
		case "Abigile_6":
			DialogExit();
			npchar.greeting = "fleetwood_2";
			LocatorReloadEnterDisable("Villemstad_town", "houseSP2", false);//打开阿比的房子
			LocatorReloadEnterDisable("Villemstad_houseSp2", "reload2", true);//关闭阿比的卧室
			AddQuestRecord("Holl_Gambit", "2-16");
			pchar.questTemp.HWIC.Eng = "toAbigile";
			sld = characterFromId("Bridgetown_tavernkeeper");
			sld.model = "barmen_3";
			sld.name = "Harry";
			sld.lastname = "Fletcher";//重绘布里奇敦的酒保
			sld.greeting = "barmen_1";
			sld = characterFromId("Solomon");
			sld.greeting = "solomon_2";
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("Villemstad", false);
		break;
		
		case "Fleetwood_LastTask":
			dialog.text = "" +pchar.name+ ", 你真的决定找到那个岛了吗? 我对你的慷慨印象深刻。 你找到了吗? ";
			link.l1 = "是的, 找到了。 不幸的是, 这就是坏消息的开始。 我几乎没能活着逃离那个该死的地方... 现在想起来还发抖... ";
			link.l1.go = "Fleetwood_LastTask_1";
		break;
		
		case "Fleetwood_LastTask_1":
			dialog.text = "那里发生了什么? 告诉我, 我的朋友, 别让我悬着! ";
			link.l1 = "我来到岛上, 前往所罗门可能藏匿他箱子的洞穴。 它真的在那里。 但当我触摸它时, 某种未知的力量把我抛了起来。 我听到一声爆炸, 被扔到离箱子十英尺远的地上... ";
			link.l1.go = "Fleetwood_LastTask_2";
		break;
		
		case "Fleetwood_LastTask_2":
			dialog.text = "难以置信! ";
			link.l1 = "我勉强活了下来 - 我受了一些痛苦的擦伤。 当我恢复意识时, 一些可怕的声音在我脑海中嗡嗡作响, 一个可怕的生物从地下出现... 哦, 上帝, 那个怪物! ";
			link.l1.go = "Fleetwood_LastTask_3";
		break;
		
		case "Fleetwood_LastTask_3":
			dialog.text = "" +pchar.name+ "... ";
			link.l1 = "理查德, 我没有疯。 这真的发生了, 尽管我自己也很难相信。 那是一具完全干涸。 涂了颜料的印第安人尸体, 头上戴着一束羽毛。 这个怪物咕哝了什么, 然后拔出一根巨大的印第安棍棒攻击我! ";
			link.l1.go = "Fleetwood_LastTask_4";
		break;
		
		case "Fleetwood_LastTask_4":
			dialog.text = "";
			link.l1 = "上帝啊... 我仍然不明白我是如何对付那个东西的... 我打了它很多次, 足以杀死十几个人, 它仍然站着... 当我喘口气后, 我打开了那个倒霉的箱子... 里面没有钱, 但有别的东西。 看看, 一个非常有趣的物品! ";
			link.l1.go = "Fleetwood_LastTask_5";
		break;
		
		case "Fleetwood_LastTask_5":
			RemoveItems(PChar, "GastonHead", 1);
			dialog.text = "B-r-r... 可怕... " +pchar.name+ ", 等等... 肯定是他! 这是那个试图用胡椒弄瞎我眼睛的混蛋的头! ";
			link.l1 = "你认识他? 名字是加斯顿, 布里奇敦的酒保, 也是幽灵船船长范伯格的支持者。 我立刻认出了他, 但我不知道是谁杀了他, 以及他被割下的头是如何出现在未知岛上所罗门的箱子里的! ";
			link.l1.go = "Fleetwood_LastTask_6";
		break;
		
		case "Fleetwood_LastTask_6":
			dialog.text = "你说得对, 这确实是一个令人毛骨悚然和模糊的故事。 神秘... ";
			link.l1 = "正是。 由于没有钱, 回到阿比盖尔身边也没有意义。 所以我来告诉你这件事。 也许你, 理查德会理解这一团糟... ";
			link.l1.go = "Fleetwood_LastTask_7";
		break;
		
		case "Fleetwood_LastTask_7":
			dialog.text = "我? 我和你一样什么都不知道... 但我可以肯定地告诉你 - 我对此有一种不好的感觉... " +pchar.name+ ", 现在听我说。 去检查布里奇敦, 确保... 加斯顿已经永远消失了。 然后, 我请你在20天内到库拉索的布兰卡泻湖。 查理.克尼佩尔会在那里等你。 我会为阿比盖尔的父亲筹集资金。 我会把它交给查理, 你会把它带给所罗门, 把阿比盖尔送到安提瓜。 这次不会有任何障碍, 你必须明白这一点。 去吧, 我的朋友! ";
			link.l1 = "好的, 理查德。 我会立即起航。 ";
			link.l1.go = "Fleetwood_LastTask_8";
		break;
		
		case "Fleetwood_LastTask_8":
			DialogExit();
			pchar.questTemp.HWIC.Eng = "toBarbados";
			AddQuestRecord("Holl_Gambit", "2-21");
			SetFunctionTimerCondition("HWICEng_toBarbadosOver", 0, 0, 20, false);//以免拖延
			AddSimpleRumourCity("哦, 船长, 我听说理查德.弗利特伍德真的很欣赏你。 相信我, 他的赞美价值不菲。 你一定是个非常重要的人... ", "SentJons", 20, 3, "");
			AddMapQuestMarkCity("Bridgetown", false);
			AddLandQuestMark(characterFromId("Bridgetown_tavernkeeper"), "questmarkmain");
		break;
		
//---------------------------------------------对抗所有人-----------------------------------------------
		
		case "InTerksShore":
			DelLandQuestMark(npchar);
			pchar.quest.Fleetwood_ShoreOver.over = "yes";//取消计时器
			dialog.text = "我认为你就是绑架了我的阿比盖尔的混蛋。 查理没有回到我身边, 所以也必须是你负责。 ";
			link.l1 = "你说得对, 弗利特伍德先生。 是我。 查理帮助我通过你写给她的信赢得了阿比盖尔的信任。 但直截了当... 你带钱了吗? ";
			link.l1.go = "InTerksShore_1";
		break;
		
		case "InTerksShore_1":
			dialog.text = "我带了。 但我想先见阿比盖尔。 我必须确信她还活着, 没有受到伤害, 因为我不会相信混蛋的话。 ";
			link.l1 = "先生, 你不认为你现在没有资格规定条件吗? ";
			link.l1.go = "InTerksShore_2";
			// belamour legendary edition -->
			link.l2 = "我不想再玩这个游戏了。 阿比会和我在一起, 而你在这个海滩上! 开火! ";
			link.l2.go = "InTerksShore_2a";
		break;

		case "InTerksShore_2a"://在无人岛上的大规模战斗
			AddCharacterExpToSkill(pchar, "FencingL", 60);
			AddCharacterExpToSkill(pchar, "FencingS", 60);
			AddCharacterExpToSkill(pchar, "FencingH", 60);
			AddCharacterExpToSkill(pchar, "Pistol", 60);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//允许战斗
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=3; i++)//弗利特伍德的军官
			{
				sld = characterFromId("FlOfficer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			for (i=1; i<=7; i++)//弗利特伍德的伏击
			{
				sld = GetCharacter(NPC_GenerateCharacter("EnemySailor_"+i, "sold_eng_"+i, "man", "man", 18, ENGLAND, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, 18, 30, 30, "blade_19", "pistol2", "bullet", 40);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				if (i >= 1 && i < 3) ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto2");
				else ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto9");
			}
			for (i=1; i<=7; i++)//我们的人 - 战斗! 
			{
				sld = characterFromId("OwrSailor_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "FleetwoodDiedInShore");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;

		case "InTerksShore_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			// < —legendary edition
			dialog.text = "我明白, 但我也不是傻瓜。 在我见到阿比盖尔之前不谈钱。 那么? 我在等。 ";
			link.l1 = "好的。 现在是时候摊牌了, 弗利特伍德船长。 我在这里组织我们的会面不是因为钱。 好吧, 当然, 我想拿走它, 但我首先需要你。 ";
			link.l1.go = "InTerksShore_3";
		break;
		
		case "InTerksShore_3":
			dialog.text = "我? 这变得非常有趣... 我想, 我开始明白这里到底发生了什么。 告诉我, 阿比盖尔还活着吗? 她活着还是你杀了她, 混蛋? ";
			link.l1 = "我想, 我会让你对她的命运一无所知。 你只需要知道一件事 - 她不在这里。 她扮演了她的角色, 你在我手中。 爱是如此美妙的事情... 否则我怎么能把狐狸从洞里引到开阔的地面上? 哈哈哈! ";
			link.l1.go = "InTerksShore_4";
		break;
		
		case "InTerksShore_4":
			dialog.text = "别高兴得太早, 流氓。 我在这个岛上为你组织了一个很好的问候, 谁在谁的手中还不知道呢! 所以准备好, 你有很多事情要告诉我 - 关于阿比盖尔, 关于查理, 你会为伤害他们付出代价! ";
			link.l1 = "我已经吓得发抖了! 是时候结束我们的谈话了, 先生。 准备下地狱吧, 因为天堂没有你的位置。 ";
			link.l1.go = "InTerksShore_5";
		break;
		
		case "InTerksShore_5"://在无人岛上的大规模战斗
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//允许战斗
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=3; i++)//弗利特伍德的军官
			{
				sld = characterFromId("FlOfficer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			for (i=1; i<=7; i++)//弗利特伍德的伏击
			{
				sld = GetCharacter(NPC_GenerateCharacter("EnemySailor_"+i, "sold_eng_"+i, "man", "man", 18, ENGLAND, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, 18, 30, 30, "blade_19", "pistol2", "bullet", 40);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				if (i >= 1 && i < 3) ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto2");
				else ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto9");
			}
			for (i=1; i<=7; i++)//我们的人 - 战斗! 
			{
				sld = characterFromId("OwrSailor_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "FleetwoodDiedInShore");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
	}
}
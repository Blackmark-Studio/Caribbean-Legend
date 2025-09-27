// 女服务员对话
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk1, bOk2;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	// 按城市调用对话 -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Tavern\" + NPChar.City + "_Waitress.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	// 按城市调用对话 <--
	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			//--> Jason 查科特金的价格
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") || SandBoxMode)
			{
				bOk1 = (pchar.questTemp.HWIC.Detector == "holl_win") || (pchar.questTemp.HWIC.Detector == "eng_win") || (pchar.questTemp.HWIC.Detector == "self_win") || SandBoxMode;
				if (sti(pchar.rank) > 6 && npchar.location == "PortSpein_tavern" && !CheckAttribute(npchar, "quest.Consumption")  && bOk1)
				{
					dialog.text = "您想要什么, 先生? 抱歉我只是...'抽泣'... 哦... 对不起。 ";
					link.l1 = "你为什么这么难过, 女士? 美丽的脸上挂着泪水? 发生了什么事? ";
					link.l1.go = "Consumption";
					break;
				}
			}
			//< —查科特金的价格
			
			// Addon-2016 Jason, 法国迷你任务 ("ЊЉ) 佐尔特 佐伦斯
			if (npchar.location == "PortPax_tavern" && CheckAttribute(pchar, "questTemp.FMQP") && pchar.questTemp.FMQP == "begin")
            {
				DelMapQuestMarkCity("PortPax");
				DelLandQuestMark(npchar);
				PlaySound("Voice\English\Enc_RapersGirl_1.wav");
				dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+"! "+UpperFirst(GetAddress_Form(NPChar))+", 救命! 杀人啦! ";
				link.l1 = "嗯? 杀谁? 在哪里? 这是玩笑吗, 亲爱的? ";
				link.l1.go = "FMQP";
				break;
			}
			
			//--> 贝琪.普莱斯的秘密
			if (npchar.location == "Villemstad_tavern" && CheckAttribute(pchar, "questTemp.TBP_BetsiPrice") && !CheckAttribute(pchar, "questTemp.TBP_BetsiPrice_Sex"))
			{
				bOk1 = CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && IsOfficer(characterFromId("Mary"));
				bOk2 = CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && IsOfficer(characterFromId("Helena"));
				if (bOk1 || bOk2)
				{
					switch (rand(1))
					{
						case 0:
							dialog.text = "" +pchar.name+ "! 很高兴再次见到你... 感谢你顺路来访... 但恐怕现在不是我们谈话的最佳时机。 等你独自一人时再来。 到时候我们可以讨论... 更私人的事情。 ";
							link.l1 = "聊天总是令人愉快, 但我该走了。 也许我们会再见面。 ";
							link.l1.go = "exit";
						break;

						case 1:
							dialog.text = "" +pchar.name+ "... 我开始以为你忘了来我们酒馆的路了。 可惜你不是一个人。 我本希望我们可以私下谈谈。 ";
							link.l1 = "我想命运仍会给我们私下交谈的机会。 ";
							link.l1.go = "exit";
						break;
					}
				}
				else
				{
					switch (rand(1))
					{
						case 0:
							dialog.text = "" +pchar.name+ "! 我就知道你不会让我等太久。 我不想再浪费时间了。 楼上的房间是空的... 只为我们准备。 你不会拒绝吧? ";
							link.l1 = "你知道如何吸引我... 好吧, 我没有理由拒绝。 我们走? ";
							link.l1.go = "TBP_BetsiPriceSex1";
							link.l2 = "恐怕我今天真的有重要的事情要处理。 但我保证, 下次我会补偿你。 ";
							link.l2.go = "exit";
						break;

						case 1:
							dialog.text = "" +pchar.name+ "! 我开始觉得你喜欢让我等待。 你不会只是像雕像一样站在那里吧? 有很多更好的方式来度过这段时间。 ";
							link.l1 = "没人能抗拒你的魅力... 没必要浪费时间 - 我现在就上楼。 ";
							link.l1.go = "TBP_BetsiPriceSex1";
							link.l2 = "你真是个诱人的女人, 贝琪... 但遗憾的是, 我现在必须去别的地方。 ";
							link.l2.go = "exit";
						break;
					}
				}
				link.l9 = "我想问你几个问题。 ";
				link.l9.go = "quests";
				break;
			}
			//< —贝琪.普莱斯的秘密
            NextDiag.TempNode = "First time";
			if (CheckAttribute(pchar, "questTemp.different.FackWaitress"))
			{
				if (pchar.questTemp.different == "FackWaitress_toRoom" || pchar.questTemp.different == "FackWaitress_toRoomUp")
				{
					dialog.text = "我已经让你上楼了。 别在这里待着引人注意。 ";
					link.l1 = "好吧, 我走, 不想给你惹麻烦... ";
					link.l1.go = "exit";
				}
				if (pchar.questTemp.different == "FackWaitress_noMoney" || pchar.questTemp.different == "FackWaitress_fighted")
				{
					dialog.text = "我是新来的, 所以请不要打扰我工作。 我还不太习惯... ";
					link.l1 = "那之前在这里工作的女服务员呢? 我记得叫" + pchar.questTemp.different.FackWaitress.Name + "... ";
					link.l1.go = "Love_IDN";
				}
				if (pchar.questTemp.different == "FackWaitress_facking")
				{					
					dialog.text = "下次再来, 亲爱的。 我们也许可以再找点乐子。 如果我有更多空闲时间的话... ";
					link.l1 = "当然会, 你很棒! ";
					link.l1.go = "exit";
				}
				if (pchar.questTemp.different == "FackWaitress_fackNoMoney")
				{					
					dialog.text = "我不认识你, 别烦我... ";
					link.l1 = "我的钱呢? ! ";
					link.l1.go = "Love_IDN_1";
				}
				break;
			}
			switch (Rand(4))
			{
				case 0:
					dialog.text = "抱歉, " + GetSexPhrase("帅哥","美女") + ", 我现在太忙了。 酒馆生意正好, 但没时间聊天! ";
					link.l1 = "... ";
					link.l1.go = "exit";
				break;

				case 1:
					dialog.text = "拜托, 船长, 别在这里打架! 打扫这里很辛苦。 ";
					link.l1 = "" + GetSexPhrase("嗯... 我根本没打算打。 ","我看起来像个找架打的醉鬼吗? 我和你一样是个姑娘, 别担心。 ") + "";
					link.l1.go = "exit";
				break;

				case 2:
					if (hrand(1) == 0) // Addon-2016 Jason
					{
						dialog.text = "" + GetSexPhrase("哦, 船长! 你今天想和我共度一晚吗? 我不想自夸但是... ","请坐, 船长。 很高兴见到像你这样真正的海狼。 ") + "";
						link.l1 = "可惜我现在赶时间。 下次吧! ";
						link.l1.go = "exit";
						bool bOk = (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) || (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) || npchar.city == GetLadyBethCity(); // 291112
						if (pchar.questTemp.different == "free" && !CheckAttribute(pchar, "questTemp.different.FackWaitress") && PChar.sex != "woman" && pchar.GenQuest.EncGirl != "HorseToTavern" && !bOk)
						{
							link.l2 = "非常乐意, 宝贝! ";
							link.l2.go = "Love_1";
						}
					}
					else
					{
						dialog.text = "请坐, 船长。 尝尝我们的朗姆酒, 玩牌或掷骰子。 就像在自己家一样! 很高兴见到像你这样真正的海狼。 ";
						link.l1 = "谢谢你, 美女。 ";
						link.l1.go = "exit";
					}
				break;

				case 3:
					dialog.text = "如果你想点东西, 跟老板说。 他在吧台后面。 ";
					link.l1 = "谢谢你的建议。 ";
					link.l1.go = "exit";
				break;

				case 4:
					dialog.text = "如果你想休息和恢复健康 - 那就租个房间。 在大厅里过一整晚帮助不大。 ";
					link.l1 = "谢谢。 ";
					link.l1.go = "exit";
				break;
			}			
			link.l9 = "我想问你几个问题。 ";
			link.l9.go = "quests";//(转发到城市文件)
		break;
		
        case "Love_1":
			dialog.text = "听着。 在酒馆里租个房间。 去那里等我。 我稍后会溜过去... ";
			link.l1 = "哈! 我会搞定的, 亲爱的! 我等你! ";
			link.l1.go = "exit";
			pchar.questTemp.different = "FackWaitress_toRoom";
			SetTimerFunction("WaitressFack_null", 0, 0, 1); //释放次日迷你任务的许可
			//如果随机数为0, 就有机会被偷。 这也是她从口袋里掏出多少钱的除数
			pchar.questTemp.different.FackWaitress.Kick = hrand(2); 
			pchar.questTemp.different.FackWaitress.Name = GetFullName(npchar); //记住女服务员的名字
			pchar.questTemp.different.FackWaitress.City = npchar.city;
			//制作女服务员的克隆
			sld = GetCharacter(NPC_GenerateCharacter("WairessQuest", npchar.model, "woman", npchar.model.animation, 5, sti(npchar.nation), 3, false, "citizen"));
			sld.name = npchar.name;
			sld.lastname = npchar.lastname;
			sld.dialog.Filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "Waitress";	
			Pchar.quest.WaitressFack_inRoom.win_condition.l1 = "location";
			Pchar.quest.WaitressFack_inRoom.win_condition.l1.location = npchar.city + "_tavern_upstairs";
			Pchar.quest.WaitressFack_inRoom.function = "WaitressFack_inRoom";
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
		break;
		
        case "Love_IDN":
			dialog.text = "她不再在这里工作了, 她退休了... 抱歉, 我得干活了。 ";
			link.l1 = "好吧... ";
			link.l1.go = "exit";
		break;
		
        case "Love_IDN_1":
			dialog.text = "听着, 好色的白痴。 我不知道你的钱在哪里! 如果你再逼我, 我就叫卫兵, 你会发现自己进监狱! ";
			link.l1 = "好吧, 不需要卫兵... 真是个傻瓜... ";
			link.l1.go = "Love_IDN_2";
		break;
		
        case "Love_IDN_2":
			dialog.text = "没错, 真是个傻瓜。 下次你会更聪明和体面些。 ";
			link.l1 = "我会试试... (低声说) 该死的婊子... ";
			link.l1.go = "exit";
		break;

		case "without_money":
			NextDiag.TempNode = "first time";
			dialog.text = "你能听见我说话吗? ";
			link.l1 = "呃... ";
			link.l1.go = "without_money_2";
		break;

		case "without_money_2":
			dialog.text = "感觉不舒服? 头疼吗? ";
			link.l1 = "该死... 我在哪? ";
			link.l1.go = "without_money_3";
		break;

		case "without_money_3":
			dialog.text = "你不记得了? 他们抢了你。 ";
			link.l1 = "什么? 哦... 我的头... 谁这么大胆? ! ";
			link.l1.go = "without_money_4";
		break;

		case "without_money_4":
			dialog.text = "我怎么会知道? 他们冲进来, 威胁要杀人, 翻了你的口袋就走了。 ";
			link.l2 = "我明白了... 该死... 我想要点水... 谢谢你。 ";
			link.l2.go = "exit";
		break;
		
		//--> Jason 查科特金的价格
		case "Consumption":
			npchar.quest.Consumption = "true";
			dialog.text = "不, 没事的, 先生... 感谢您的好意, 但我... (哭泣) ";
			link.l1 = "有人冒犯你了? 冷静点, 美人, 告诉我一切。 ";
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			dialog.text = "不, 不, 先生, 没什么。 请原谅我的失态, 只是... 是我的哥哥, 他们说他死了, 但我不相信。 我不知道该相信什么, 但我心里觉得他遇到了大麻烦。 父母去世后, 除了安杰洛我没有别人了... (哭泣) ";
			link.l1 = "我理解, 但请你冷静下来。 你哥哥怎么了? ";
			link.l1.go = "Consumption_2";
		break;
		
		case "Consumption_2":
			dialog.text = "先生... 请别误会, 但像您这样的船长为什么要关心 一 个普通酒馆里的谦逊女孩呢? 我甚至没有什么可以承诺您的帮助... ";
			link.l1 = "实际上, 你说得对。 无私不是我的风格, 所以坚强点, 我们都会失去亲人。 正如我们法国人所说: 这就是生活... ";
			link.l1.go = "exit";
			link.l2 = "女人总能找到感谢男人的方法... 。 哈哈。 现在, 别哭了, 告诉我你的问题。 ";
			link.l2.go = "Consumption_3_1";
			link.l3 = "年轻的小姐, 你不知道我们的教会教导我们要互相帮助吗? 如果我能做到, 我会尽力帮助你。 ";
			link.l3.go = "Consumption_3_2";
		break;
		
		case "Consumption_3_1":
			if(sti(pchar.reputation.nobility) > 36)
			{
				dialog.text = "这是在'暗示'吗? 对不起, 和你说话是我的错! 再见,'骑士'... ";
				link.l1 = "如你所愿, 甜心。 ";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "好吧... 至少你对自己的愿望很诚实。 我保证, 如果你找到安杰洛或者告诉我他到底发生了什么, 你会得到你想要的... ";
				link.l1 = "亲爱的小姐, 和你做生意很愉快... 现在让我们直接谈谈你哥哥的事。 ";
				link.l1.go = "Consumption_4";
				npchar.quest.Consumption.sex = "true";
			}
		break;
		
		case "Consumption_3_2":
			dialog.text = "你在开玩笑吗? 你真的想免费帮我? ";
			link.l1 = "只有坏人才不会帮助哭泣的女孩。 别担心, 我真的想帮助你。 安杰洛到底怎么了? ";
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = "很好, 先生。 我的哥哥, 他... 哦, 对我来说忍住眼泪不容易, 对不起... 我们真的很穷, 也许是因为我的... 工作上的谦逊。 安杰洛开始和当地的走私者一起工作。 他认为他的小渔船在逃避海关的情况下运送货物能赚更多钱。 ";
			link.l1 = "简单地说, 你哥哥成了罪犯, 对吧? ";
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			dialog.text = "不, 先生, 你不明白... 他不是那样的! 他这么做是为了我! 为了让我不必在这里靠出卖自己赚钱... 你懂我的意思。 我们负债累累, 他这么做是为了我的荣誉和灵魂。 然后... 他被抓住了。 这不是什么大问题, 我甚至借了更多钱来保释他... 但他们说他死了。 ";
			link.l1 = "他们说? 谁说的? 你为什么不相信他们? 他死在监狱里? ";
			link.l1.go = "Consumption_6";
		break;
		
		case "Consumption_6":
			dialog.text = "是的。 当我带钱去保释他时, 指挥官告诉我安杰洛死于肺结核。 想想看! 他进去时身体很好, 两周后就死在那些牢房里。 他们... 他们甚至不让我看尸体。 他们说为了避免流行病, 囚犯被埋在堡垒附近的海湾。 ";
			link.l1 = "流行病? 听起来很可信。 所以你只是不想相信, 还是有更严重的原因? ";
			link.l1.go = "Consumption_7";
		break;
		
		case "Consumption_7":
			dialog.text = "不... 不! (哭泣) 我知道这听起来很傻, 但我确定如果他死了我会知道的。 看, 安杰洛一直很强壮 - 一个真正的水手。 但还有一件事\n我祖父在我小时候死于肺结核, 他一个老人, 与病魔斗争了好几年! 我知道这病的情况, 肺结核不会在几天内致人死亡, 相信我! ";
			link.l1 = "嗯... 你也让我怀疑了, 这里面肯定有问题。 我不能承诺什么, 但我会试着了解更多。 ";
			link.l1.go = "Consumption_8";
		break;
		
		case "Consumption_8":
			dialog.text = "即使是一个简单的承诺也比我期望的要多! 您真好, 先生! 我会在这里等您! ";
			link.l1 = "哦, 青春! 感情如此多变... 美丽的小姐, 能把我的手还给我吗, 我还需要它哈哈... 那好吧, 我去四处打听一下。 ";
			link.l1.go = "Consumption_9";
		break;
		
		case "Consumption_9":
			DialogExit();
			npchar.dialog.filename = "Quest\LineMiniQuests\Consumption.c";
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Consumption = "begin";
			AddQuestRecord("Consumption", "1");
		break;
		//< —查科特金的价格
		
		// Addon-2016 Jason, 法国迷你任务 ("ЊЉ) 佐尔特 佐伦斯
		case "FMQP":
			dialog.text = "不, 不是开玩笑! 楼上! 两个暴徒正在谋杀一位贵族绅士! 救命, 船长! 这里只有你一个人有武器! ";
			link.l1 = "跑到外面去, 叫卫兵! 我上楼去! ";
			link.l1.go = "FMQP_1";
			link.l2 = "亲爱的, 你一定把我当成卫兵了。 如果发生谋杀就叫巡逻队。 ";
			link.l2.go = "FMQP_exit";
		break;
		
		case "FMQP_exit":
			dialog.text = "啊-啊, 卫兵! 救命啊! ";
			link.l1 = "... ";
			link.l1.go = "FMQP_exit_1";
		break;
		
		case "FMQP_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoQuestReloadToLocation("Portpax_town", "reload", "reload4", "");
			LocatorReloadEnterDisable("Portpax_town", "reload4_back", true);
			SetFunctionTimerCondition("FMQP_Remove", 0, 0, 1, false);
		break;
		
		case "FMQP_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			pchar.quest.FMQP_room.win_condition.l1 = "locator";
			pchar.quest.FMQP_room.win_condition.l1.location = "Portpax_tavern";
			pchar.quest.FMQP_room.win_condition.l1.locator_group = "reload";
			pchar.quest.FMQP_room.win_condition.l1.locator = "reload2_back";
			pchar.quest.FMQP_room.function = "FMQP_InRoom";
		break;
	}
}
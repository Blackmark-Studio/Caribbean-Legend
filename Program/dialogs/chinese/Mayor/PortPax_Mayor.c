// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("你想要什么? 问吧。 ", "我在听, 你有什么问题? "), "这是你第二次尝试提问... ", "这是你第三次尝试提问... ",
                          "这要到什么时候才结束? ! 我是个忙人, 在处理殖民地事务, 而你还在烦我! ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了... ", "现在不了。 地点和时间不对。 "), "确实... 但以后吧, 不是现在... ",
                      "我会问的... 但过一会儿... ", "抱歉, " + GetAddress_FormToNPC(NPChar) + "... ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// 杰森 圣马丁岛
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_2" && !CheckAttribute(npchar, "quest.patria") && !CheckAttribute(pchar, "questTemp.Patria.Visiter_Late"))
			{
				link.l1 = TimeGreeting()+" 先生。 我是奉总督谢瓦利埃.德.潘西之命来此。 我的任务是将诺埃尔.福盖男爵护送到托尔图加, 他从宗主国抵达, 肩负视察殖民地的任务, 其主要目的是成立法属西印度贸易公司。 请允许我为您介绍他... 他会亲自解释所有细节。 ";
                link.l1.go = "patria_portpax";
			}
			// Rebbebion, 任务'导航星'
			if (CheckAttribute(pchar, "questTemp.PZ.PortPaxMayorTalk"))
			{
				link.l1 = "大人, 您想见我? ";
				link.l1.go = "PZ1";
			}
			// 失窃的记忆
			if (CheckAttribute(pchar, "questTemp.UV_DialogMayor"))
			{
				link.l1 = "大人, 我带来一则极为敏感的消息, 需要您的关注。 ";
				link.l1.go = "UV_1";
			}
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("你已经拿走了所有东西。 还想要什么? ", "还有什么是你没拿的吗? ");
            link.l1 = RandPhraseSimple("只是四处看看... ", "只是检查一下, 我可能忘了拿什么... ");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		// 杰森 圣马丁岛
		case "patria_portpax":
			dialog.text = "很高兴见到您, 查尔斯.德.莫尔船长, 还有男爵。 我会尽一切努力让福盖先生在我们殖民地的停留尽可能舒适。 趁着如此高级别的先生来访, 我想请您帮个忙。 ";
			link.l1 = "非常有趣! 请告诉我们您的事, 大人。 ";
			link.l1.go = "patria_portpax_1";
		break;
		
		case "patria_portpax_1":
			dialog.text = "最近几个月, 我们殖民地没有任何总督代表来访, 就好像圣基茨的人完全忘记了我们! 与此同时, 渴望将整个伊斯帕尼奥拉岛变成纯粹西班牙领地的西班牙人, 把岛上西部的法国定居者和海盗视为主要麻烦, 正在准备进攻! 我的巡逻官。 我们的贸易船长甚至普通渔民都报告说, 一支强大的西班牙舰队正在圣地亚哥集结, 准备进攻太子港! ";
			link.l1 = "证据足够清楚吗, 大人? ";
			link.l1.go = "patria_portpax_2";
		break;
		
		case "patria_portpax_2":
			dialog.text = "我没有准确的情报, 但来自完全不相关人士的如此多信息不可能只是谣言。 我们的殖民地对法国非常重要, 我们这里有最好的种植园, 男爵可以亲自看看。 失去这个殖民地, 甚至让它面临被掠夺的风险, 都是不可接受的! ";
			link.l1 = "我会考虑您的证据, 并告知谢瓦利埃.德.潘西。 我相信他会立即采取措施。 ";
			link.l1.go = "patria_portpax_3";
		break;
		
		case "patria_portpax_3":
			dialog.text = "谢谢你, 船长... ";
			link.l1 = "";
			link.l1.go = "patria_portpax_4";
		break;
		
		case "patria_portpax_4":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_9";
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "governor1");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
			npchar.quest.patria = "true";
		break;
		
		case "PZ1":
			DeleteAttribute(pchar, "questTemp.PZ.PortPaxMayorTalk");
			dialog.text = "不, 我没有召见你, 先生。 你有事吗? ";
			link.l1 = "我怎么会呢? 但您的信使遇见了我们; 他说您为我准备了镇上的一所房子... ";
			link.l1.go = "PZ2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ2":
			dialog.text = "什么房子, 什么信使, 这算什么无礼行为? ! ";
			link.l1 = "您说什么信使... 他叫亨利.蒂博, 而且... ";
			link.l1.go = "PZ3";
		break;
		
		case "PZ3":
			dialog.text = "什么? 你知道他是谁吗? 显然不知道。 但这不重要。 勒瓦瑟的侄子在我的镇上做什么? ";
			link.l1 = "哦, 我的上帝... ";
			link.l1.go = "PZ4";
		break;
		
		case "PZ4":
			dialog.text = "德.莫尔, 你能听到我吗? 先生? ";
			link.l1 = "... ";
			link.l1.go = "PZ5";
		break;
		
		case "PZ5":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocator(pchar, "reload", "reload1", "PZ_SharleBezhitObratno", -1);
			bDisableCharacterMenu = true;
			InterfaceStates.Buttons.Save.enable = false;
			SetMusic("music_teleport");
			pchar.questTemp.lockedMusic = true;
		break;
		
		//--> 失窃的记忆
		case "UV_1":
			dialog.text = "你说一件敏感的事? 这引起了我的兴趣, 船长。 请继续 —我全神贯注听你说。 ";
			link.l1 = "这件事与您的侄女朱莉有关。 她雇我帮她找回一条从她那里偷走的项链。 ";
			link.l1.go = "UV_2";
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			DelLandQuestMark(npchar);
		break;

		case "UV_2":
			dialog.text = "一条项链? 奇怪。 我不记得她的物品中有这样一件东西。 ";
			link.l1 = "请允许我按顺序陈述事实, 总督。 我已成功找回相关项链。 我的调查显示, 小偷是您侄女的女仆吉赛尔。 从对购买赃物的商人的观察来看, 我强烈怀疑这既不是她第一次也不是最后一次此类越轨行为。 ";
			link.l1.go = "UV_3";
		break;

		case "UV_3":
			dialog.text = "很有启发性。 请继续你的叙述。 ";
			link.l1 = "大人, 引起我注意的是, 朱莉选择不向您寻求帮助。 看来, 这条项链是一个您明确禁止她交往的人送的礼物。 鉴于您的限制出于最明智和最具保护性的意图, 我觉得有义务将此事提请您注意, 并将项链直接归还给您。 ";
			link.l1.go = "UV_4";
			TakeItemFromCharacter(pchar, "SM_necklace_Julie");
		break;

		case "UV_4":
			dialog.text = "你的判断证明是正确的"+GetSexPhrase(", 船长","")+"。 我赞赏你直接来找我而不是纵容我侄女年轻轻率行为的谨慎态度。 ";
			link.l1 = "我这样做只是为了她的福祉, 总督。 我毫不怀疑您的指导同样源于关心和智慧。 ";
			link.l1.go = "UV_5";
		break;

		case "UV_5":
			dialog.text = "确实如此, 船长。 作为她的叔叔和监护人, 她的福祉是我最关心的。 请接受这一百五十枚达布隆作为我对您谨慎态度的感谢。 我还赠您这枚导航罗盘 —愿它指引您安全穿越危险水域。 ";
			link.l1 = "承蒙您的慷慨, 大人, 尽管这种奖励是不必要的。 遗憾的是, 我现在必须向您告别 —潮水不等人, 我的船需要我去照料。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("UV_End");
			AddItems(pchar, "gold_dublon", 150);
			GiveItem2Character(PChar, "compass1");
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
		break;
		//<-- 失窃的记忆
	}
	UnloadSegment(NPChar.FileDialog2);  // 如果switch内部有通过return退出的情况, 别忘了执行此卸载
}
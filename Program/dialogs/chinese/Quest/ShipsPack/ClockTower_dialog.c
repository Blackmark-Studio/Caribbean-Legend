int iClockSP4PseudoGlobal = SOUND_INVALID_ID;

void ProcessDialogEvent()
{
	ref NPChar, sld, realShip;
	aref Link, NextDiag, arTmp;
	int i, n, NextMonth, idx;
	string sTemp, sStr, Month, NationName, shipType;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	if (HasSubStr(Dialog.CurrentNode, "chosenIdx/"))
	{
		Dialog.tmpIdx = FindStringAfterChar(Dialog.CurrentNode, "/");
		Dialog.CurrentNode = FindStringBeforeChar(Dialog.CurrentNode, "/");
	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Что вам надо?";
			link.l1 = "Ничего.";
			link.l1.go = "exit";
		break;
		
		// Диалог с Йоханом
		case "ClockTower_Johan_1":
			dialog.text = "站住, "+GetTitle(NPChar, true)+"。再往前不能走了。";
			link.l1 = "为什么?";
			link.l1.go = "ClockTower_Johan_2";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Johan_2":
			dialog.text = "看见那座塔了吗? 荷兰西印度公司办事处。 船只登记部门和档案馆。 只有预约才能进入。";
			link.l1 = "那怎么才能预约上?";
			link.l1.go = "ClockTower_Johan_3";
		break;

		case "ClockTower_Johan_3":
			dialog.text = "该知道的人自然知道。主管先生可不是什么人都接待的。";
			link.l1 = "'主管先生'? 那是谁?";
			link.l1.go = "ClockTower_Johan_4";
		break;

		case "ClockTower_Johan_4":
			dialog.text = "van Doorn管事。也许他并不完全算主管, 但大家都这么叫他。 他在这里工作十年了 —— 把一切都整顿得井井有条。 现在加勒比海上的所有船只都要经过他的办事处。";
			link.l1 = "所有船只? 连战舰也包括在内?";
			link.l1.go = "ClockTower_Johan_5";
		break;

		case "ClockTower_Johan_5":
			dialog.text = "只有最好的船只和最富有的船长。能成为我们办事处的客户可是莫大的荣幸!";
			link.l1 = "你们提供什么服务?";
			link.l1.go = "ClockTower_Johan_6";
		break;

		case "ClockTower_Johan_6":
			dialog.text = "我不清楚具体细节——我只负责守门。不过我听说, 人们出来的时候都很满意。";
			link.l1 = "令人印象深刻。";
			link.l1.go = "ClockTower_Johan_7";
		break;

		case "ClockTower_Johan_7":
			dialog.text = "我再告诉你一件事。看见那座钟了吗? 欧洲的奇迹 —— 在我们这穷乡僻壤可找不到这样的东西。 主管先生亲自照看着它。";
			link.l1 = "也许我们可以商量商量?";
			link.l1.go = "ClockTower_Johan_8_1";
			link.l2 = "难道我真的没办法进去吗?";
			link.l2.go = "ClockTower_Johan_8_2";
		break;

		case "ClockTower_Johan_8_1":
			dialog.text = "我不收贿赂!";
			link.l1 = "抱歉。你是个好人。叫什么名字?";
			link.l1.go = "ClockTower_Johan_9";
		break;

		case "ClockTower_Johan_9":
			dialog.text = ""+npchar.name+"…… 听着…… 我明白, 你不是本地人。 但这里讲规矩。 主管先生总是说: 一旦松懈, 我们的塔就会倒塌。 想进去? 帮助这座城市 —— 你就会被注意到。";
			link.l1 = "明白了。保重, 士兵。";
			link.l1.go = "ClockTower_Johan_11";
		break;

		case "ClockTower_Johan_8_2":
			dialog.text = "嗯, 我也不太清楚。 主管先生会奖励Willemstad的朋友。 帮助这座城市——你就会被注意到。 我明白, 你不是本地人。 但这里讲规矩。 主管先生总是说: 一旦松懈, 我们的塔就会倒塌。";
			link.l1 = "明白了。 你叫什么名字?";
			link.l1.go = "ClockTower_Johan_10";
		break;

		case "ClockTower_Johan_10":
			dialog.text = ""+npchar.name+", "+GetTitle(NPChar, true)+".";
			link.l1 = "而我是"+GetTitle(NPChar, false)+" "+GetFullName(pchar)+".保重, 士兵。";
			link.l1.go = "ClockTower_Johan_11";
		break;
		
		case "ClockTower_Johan_11":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_Quest_1");
		break;
		
		case "ClockTower_Johan_repeat":
			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) >= 51)
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"!";
				link.l1 = "发生什么事了?";
				link.l1.go = "ClockTower_Johan_22";
				Notification_ReputationNation(true, 51, HOLLAND);
			}
			else 
			{
				dialog.text = ""+Greeting(true)+", "+GetTitle(NPChar, true)+". 我能帮您什么吗?";
				link.l1 = "不用了, "+npchar.name+". 继续值班吧。";
				link.l1.go = "exit";
				NextDiag.TempNode = "ClockTower_Johan_repeat";
				Notification_ReputationNation(false, 51, HOLLAND);
			}
		break;
		
		case "ClockTower_Johan_21":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"!";
			link.l1 = "发生什么事了?";
			link.l1.go = "ClockTower_Johan_22";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Johan_22":
			dialog.text = "恭喜您。您的会面已经安排好了。";
			link.l1 = "会面? 跟谁?";
			link.l1.go = "ClockTower_Johan_23";
		break;

		case "ClockTower_Johan_23":
			dialog.text = "跟主管先生的副手。他听说了您对这座城市的帮助, 命令我邀请您。";
			link.l1 = "那主管本人呢?";
			link.l1.go = "ClockTower_Johan_24";
		break;

		case "ClockTower_Johan_24":
			dialog.text = "呃……我没有权限告诉您这些。祝您好运, 船长先生。";
			link.l1 = "谢谢。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_InvitationToTheTower");
		break;
		
		// Диалог с Маартеном Виссером, заместителем директора
		case "ClockTower_Visser_1":
			dialog.text = "欢迎来到荷兰西印度公司船只登记部门。 "+UpperFirst(GetTitle(NPChar, false))+"?..";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "ClockTower_Visser_2";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_2":
			dialog.text = ""+GetFullName(NPChar)+", 副主管。\n"+
						 "我听说您为Willemstad帮了不少忙。也许我们办事处也能为您提供帮助。";
			link.l1 = "这就是我来这里的原因。";
			link.l1.go = "ClockTower_Visser_3_1";
			link.l2 = "我很高兴能为库拉索的首府效劳。";
			link.l2.go = "ClockTower_Visser_3_2";
		break;

		case "ClockTower_Visser_3_1":
			dialog.text = "任何船长——法国的、西班牙的、荷兰的——都可以向我们订购船只审计。我们检查索具、火炮、帆缆。找出薄弱环节，提供建议。";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_4";
		break;

		case "ClockTower_Visser_3_2":
			dialog.text = "任何船长——法国的、西班牙的、荷兰的——都可以向我们订购船只审计。我们检查索具、火炮、帆缆。找出薄弱环节，提供建议。";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_4";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;

		case "ClockTower_Visser_4":
			dialog.text = "如果一次审计还不够，我们还可以搞到新的船只文件。换句话说，我们办事处的工作会让您的船变得更好——而不用花费宝贵的红木和丝绸。";
			link.l1 = "这怎么可能？";
			link.l1.go = "ClockTower_Visser_4_1";
		break;

		case "ClockTower_Visser_4_1":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+"，您根本想象不到您进入的是一个多么强大的地方，以及一个简单的签名能成就多少事情。";
			link.l1 = "用金币，我猜？";
			link.l1.go = "ClockTower_Visser_5";
		break;

		case "ClockTower_Visser_5":
			dialog.text = "当然。我们的服务不便宜，而且取决于您船只的大小。但总是物有所值。经过我们这里的船长很少会失败\n"+
						 "不过，我们不仅拿走您的黄金，还给您赚钱的机会。海盗如此猖獗，即使在小安的列斯群岛，船长们也不得不组建舰队来驱赶这些害虫。带来消灭他们的证据——您就能得到同样的金币作为报酬。";
			link.l1 = "什么样的证据？";
			link.l1.go = "ClockTower_Visser_6";
		break;

		case "ClockTower_Visser_6":
			dialog.text = "航海日志。即使是那些渣滓也必须保存某种文件——否则连双桅帆船都指挥不好。除了日志是罪行的确凿证据外，它们在我们的档案中也总有一席之地。在保险纠纷中很有用\n"+
						 "如果您对我们的服务感兴趣，我们的客户名单上空出了一个位置——其中一位船长最近结束了合作。完成任务——位置就是您的。";
			link.l1 = "为什么要这么麻烦？我的金币还不够吗？";
			link.l1.go = "ClockTower_Visser_7";
		break;

		case "ClockTower_Visser_7":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+"，我们注重质量，而非数量。我们办事处的每位客户都能获得最好的服务和主管先生本人的关注。而后者，相信我，即使对我们这家远非贫困的公司来说，也要花费相当可观的资金。因为一个月只有三十天，所以我们只能接待三十位客户。";
			link.l1 = "需要做什么？";
			link.l1.go = "ClockTower_Visser_8";
		break;

		case "ClockTower_Visser_8":
			dialog.text = "带来五本海盗航海日志——这将证明您的效率。奖励取决于他们主人的危险程度。";
			link.l1 = "好的。我会做的。";
			link.l1.go = "ClockTower_Visser_9_1";
			link.l2 = "我需要考虑一下。";
			link.l2.go = "ClockTower_Visser_9_2";
			link.l3 = "那主管本人在哪里？";
			link.l3.go = "ClockTower_Visser_9_3";
		break;

		case "ClockTower_Visser_9_1":
			dialog.text = "很好。我期待结果，也期待我们的合作。";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "ClockTower_Visser_13_exit";
		break;

		case "ClockTower_Visser_9_2":
			dialog.text = "随您便。提议依然有效。但您的位置可能比您想的更快被占据。";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "ClockTower_Visser_13_exit";
		break;

		case "ClockTower_Visser_9_3":
			dialog.text = "在海上。Mynheer van Doorn既管理办事处，又指挥旗舰。";
			link.l1 = "他是怎么做到的？";
			link.l1.go = "ClockTower_Visser_10";
		break;

		case "ClockTower_Visser_10":
			dialog.text = "他每天工作十八个小时。就睡在这里，楼上的办公室里。他说睡觉是浪费时间。四个小时对他来说就够了。";
			link.l1 = "那那些巨大的钟表机械的轰鸣声呢？这里怎么能睡得着觉？";
			link.l1.go = "ClockTower_Visser_11";
		break;

		case "ClockTower_Visser_11":
			dialog.text = "您可以亲自问他，也许还能学到些东西。他总是很乐意与客户交谈。我们明白彼此的意思吗？";
			link.l1 = "完全明白。";
			link.l1.go = "ClockTower_Visser_12";
			link.l2 = "不完全明白……";
			link.l2.go = "ClockTower_Visser_12";
		break;

		case "ClockTower_Visser_12":
			dialog.text = "祝您愉快，"+GetTitle(NPChar, false)+".";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "ClockTower_Visser_13_exit";
		break;

		case "ClockTower_Visser_13_exit":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_Quest_2");
		break;
		
		// Йохан спрашивает про журналы
		case "ClockTower_Johan_31":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"！您带日志了吗？";
			link.l1 = "看来你消息很灵通，Johan。";
			link.l1.go = "ClockTower_Johan_32";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Johan_32":
			if (!CheckAttribute(npchar, "questTemp.ClockTower_Johan_journal"))
			{
				dialog.text = "哈！这里不是码头也不是城门，而我也不是普通的值班卫兵，我是公司员工。";
				npchar.questTemp.ClockTower_Johan_journal = true;
			}
			else
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"！您带日志了吗？";
			}
			if (ClockTower_JournalsQty() >= 5 || bBettaTestMode)
			{
				link.l1 = "我带来了日志。让我过去吗？";
				link.l1.go = "ClockTower_Johan_33";
			}
			link.l2 = "下次吧。";
			link.l2.go = "ClockTower_Johan_34";
		break;

		case "ClockTower_Johan_33":
			dialog.text = "很高兴成功了！请进，他们在等您。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_InvitationToTheTower_2");
		break;
		
		case "ClockTower_Johan_34":
			dialog.text = "祝您愉快, "+GetTitle(NPChar, true)+".";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Johan_32";
		break;
		
		case "ClockTower_Visser_21":
			dialog.text = "船长！您回来了。日志带来了吗？";
			if (ClockTower_JournalsQty() >= 5 || bBettaTestMode)
			{
				link.l1 = "是的。全部五本。";
				link.l1.go = "ClockTower_Visser_22";
				DelLandQuestMark(npchar);
			}
			else
			{
				link.l1 = "改天吧。";
				link.l1.go = "exit";
				NextDiag.TempNode = "ClockTower_Visser_21";
			}
		break;

		case "ClockTower_Visser_22":
			dialog.text = "很好。让我看看。\n"+
						"是的，一切正常。这些都是真正的海盗船。工作做得很好。您应得#количество_дублонов金币。\n"+
						"请收下。还请在这里签个字。";
			link.l1 = "那我算是在名单上了？";
			link.l1.go = "ClockTower_Visser_23";
			//RemoveItemsFromPCharTotal("ClockTower_PirateJournal", 5);      
		break;

		case "ClockTower_Visser_23":
			dialog.text = "差不多了。首先需要办理文件。需要几分钟。\n"+
						"全名？";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "ClockTower_Visser_24";
		break;

		case "ClockTower_Visser_24":
			dialog.text = "国籍？";
			link.l1 = ""+NationNameNominative(sti(pchar.baseNation))+".";
			link.l1.go = "ClockTower_Visser_25";
		break;

		case "ClockTower_Visser_25":
			dialog.text = "您的船名？";
			link.l1 = ""+PChar.Ship.Name+".";
			link.l1.go = "ClockTower_Visser_26";
		break;

		case "ClockTower_Visser_26":
			shipType = XI_ConvertString(GetShipTypeName(pchar));
			dialog.text = "船只类型？";
			link.l1 = ""+shipType+".";
			link.l1.go = "ClockTower_Visser_27";
		break;

		case "ClockTower_Visser_27":
			dialog.text = "炮数？";
			link.l1 = ""+GetCannonQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_28";
		break;

		case "ClockTower_Visser_28":
			dialog.text = "船员人数？";
			link.l1 = ""+GetMaxCrewQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_29";
		break;

		case "ClockTower_Visser_29":
			dialog.text = "好的。现在在这里签名。这里。还有这里也签一下。";
			link.l1 = "就这样？";
			link.l1.go = "ClockTower_Visser_30";
		break;

		case "ClockTower_Visser_30":
			dialog.text = "差不多了。只剩下把您登记到名册里。当然，主管先生应该先亲自见见您……但这只是个形式——我有权接受新客户。\n"+
					"...但我又跑题了。请允许我再次向您介绍我们的服务清单。\n"+
					"保险。很贵，但任何海军舰队都不会碰公司承保的船只。您可以在港口管理处保管任意数量的船只，而不用担心在殖民地围攻时失去它们。\n"+
					"船只审计——在不花费战略物资的情况下略微提高所有特性。我们会检查一切：索具、货舱、船员舱室。提供建议。价格取决于船只大小。\n"+
					"将船只登记到我们的名册中。提高船只在加勒比地区的安全性，赏金猎人、海盗和军队在攻击您之前都会三思而后行。\n"+
					"审计和登记只能对特定船只进行一次。所以如果您已经花了钱，就要好好保护您的船只。您都不知道，当船长们草率对待自己的船只，像换手套一样换船时，我的上司有多恼火！\n"+
					"但我又跑题了。现在关于可重复的服务……\n"+
					"更换文件。您知道船只可以有不同的专业化方向。但您甚至都不知道，这主要取决于船只是如何登记的。如果您不喜欢您的战舰被登记为围攻堡垒用途，您知道该找谁。\n"+
					"嗯，关于上缴海盗航海日志的奖励您已经听说过了……海盗越危险，我们为他的日志支付的报酬就越多。";
			link.l1 = "令人印象深刻。我必须说，mynheer Visser，您的办事处真的……";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_AmsterdamInTheHarbor");
		break;

		case "ClockTower_Visser_31":
			dialog.text = "'"+GetShipName("Amsterdam")+"'号在港口！主管先生回来了！";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_31_add";
			CharacterTurnByChr(CharacterFromID("ClockTower_Johan_Clone"), CharacterFromID("ClockTower_Visser"));
			ClockTower_AmsterdamInTheHarbor_2();
		break;

		case "ClockTower_Visser_31_add":
			StartInstantDialogNoType("ClockTower_Visser", "ClockTower_Visser_32", "Quest\ShipsPack\ClockTower_dialog.c");
		break;

		case "ClockTower_Visser_32":
			dialog.text = "什么？！这么快？！但他应该三天后才回来！";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_32_add";
		break;

		case "ClockTower_Visser_32_add":
			StartInstantDialog("ClockTower_Johan_clone", "ClockTower_Visser_33", "Quest\ShipsPack\ClockTower_dialog.c");
		break;

		case "ClockTower_Visser_33":
			dialog.text = "主管先生已经上岸了！正往这边走！";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_33_add";
			CharacterTurnByChr(CharacterFromID("ClockTower_Johan_Clone"), CharacterFromID("ClockTower_Visser"));
		break;

		case "ClockTower_Visser_33_add":
			StartInstantDialogNoType("ClockTower_Visser", "ClockTower_Visser_34", "Quest\ShipsPack\ClockTower_dialog.c");
		break;

		case "ClockTower_Visser_34":
			dialog.text = "天哪……如果他看到您……";
			link.l1 = "有什么问题？您自己刚才还说您有权接受新客户。";
			link.l1.go = "ClockTower_Visser_35";
		break;

		case "ClockTower_Visser_35":
			dialog.text = "有！但他不喜欢……算了。船长，在外面等着。在入口处。主管先生会想和您谈谈。";
			link.l1 = "和我？";
			link.l1.go = "ClockTower_Visser_36";
		break;

		case "ClockTower_Visser_36":
			dialog.text = "他亲自审查每一位新客户。总是如此。快走！";
			link.l1 = "日志的金币我可不会还回去！";
			link.l1.go = "ClockTower_Visser_36_1";
			link.l2 = "可惜，我倒想留下来听听。";
			link.l2.go = "ClockTower_Visser_36_2";
		break;
		
		case "ClockTower_Visser_36_1":
			DialogExit();
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			AddDialogExitQuestFunction("ClockTower_AmsterdamInTheHarbor_Kino_1");
		break;
		
		case "ClockTower_Visser_36_2":
			DialogExit();
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddDialogExitQuestFunction("ClockTower_AmsterdamInTheHarbor_Kino_1");
		break;
		
		// диалог с Йоханом, после того как мы вышли из башни
		case "ClockTower_Johan_41":
			dialog.text = "...";
			link.l1 = "那是怎么回事, Johan?";
			link.l1.go = "ClockTower_Johan_42";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Johan_42":
			dialog.text = "主管先生回来了。";
			link.l1 = "这有什么可怕的?";
			link.l1.go = "ClockTower_Johan_43";
		break;

		case "ClockTower_Johan_43":
			dialog.text = "没什么可怕的! 只是…… 主管先生不喜欢意外。 一切都必须按计划进行。 而这里有个他还没审查过的新客户。";
			link.l1 = "Maarten说他有权把我登记到名册里。";
			link.l1.go = "ClockTower_Johan_44";
		break;

		case "ClockTower_Johan_44":
			dialog.text = "不, 不是这个问题。 主管先生只是…… 嗯, 他想亲自控制一切。 每一个细节。 他说否则一切都会崩溃。 您等着瞧, 现在他又要开始担心他的钟了。";
			link.l1 = "什么?";
			link.l1.go = "ClockTower_Johan_45";
		break;

		case "ClockTower_Johan_45":
			dialog.text = "Mynheer van Doorn一旦恼火, 就会停下钟, 开始摆弄它。有时整座城市半天都没有时间。而这种事……";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_45_1";
		break;

		case "ClockTower_Johan_45_1":
			dialog.text = "哦……听到了吗? 开始了。";
			link.l1 = "老板回来了。平常事。";
			link.l1.go = "ClockTower_Johan_46_1";
			link.l2 = "听得一清二楚。他们正在痛骂Maarten呢。";
			link.l2.go = "ClockTower_Johan_46_2";
			iClockSP4PseudoGlobal = ClockTower_PlaySound_rh2("Location/SP4_quest2");
		break;

		case "ClockTower_Johan_46_1":
			dialog.text = "不幸的是, 现在已经是平常事了。";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_47";

			if (iClockSP4PseudoGlobal != SOUND_INVALID_ID)
				SendMessage(Sound, "lll", MSG_SOUND_EVENT_STOP, iClockSP4PseudoGlobal, 0);
			ClockTower_PlaySound_rh2("Location/SP4_quest3");
		break;

		case "ClockTower_Johan_46_2":
			dialog.text = "您不该这么说。 依我看, 这不公平。";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_47";	
			ChangeCharacterComplexReputation(pchar, "nobility", -2);

			if (iClockSP4PseudoGlobal != SOUND_INVALID_ID)
				SendMessage(Sound, "lll", MSG_SOUND_EVENT_STOP, iClockSP4PseudoGlobal, 0);
			ClockTower_PlaySound_rh2("Location/SP4_quest3");
		break;

		case "ClockTower_Johan_47":
			dialog.text = "好像安静下来了。马上就会请您进去。";
			link.l1 = "我会有麻烦吗?";
			link.l1.go = "ClockTower_Johan_48";
		break;

		case "ClockTower_Johan_48":
			dialog.text = "别担心。您又没做错什么。";
			link.l1 = "真让人安心。";
			link.l1.go = "ClockTower_Johan_49";
		break;

		case "ClockTower_Johan_49":
			dialog.text = "别这样嘛! 主管先生有时确实过于严厉…… 但他慷慨又有礼貌…… 哦, 我就说嘛!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_50";
		break;

		case "ClockTower_Johan_50":
			dialog.text = "哦, 我就说嘛!";
			link.l1 = "...";
			link.l1.go = "exit";
			ClockTower_VisserComingTowardsUs();
		break;

		case "ClockTower_Visser_37":
			dialog.text = "主管先生在里面等您。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_VisserComingTowardsUs_2");
			DelLandQuestMark(npchar);
		break;
		
		// Первое знакомство с ван Дорном
		case "ClockTower_VanDoorn_1":
			NationName = GetSexPhrase(""+NationNameMan(sti(pchar.baseNation))+"",""+NationNameWoman(sti(pchar.baseNation))+"");
			shipType = LowerFirst(XI_ConvertString(GetShipTypeName(pchar)));
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" "+GetFullName(pchar)+", "+NationName+". 您的船——'"+PChar.Ship.Name+"'，"+shipType+"。"+GetCannonQuantity(pchar)+"门炮和"+GetMaxCrewQuantity(pchar)+"名船员。";
			link.l1 = "完全正确。";
			link.l1.go = "ClockTower_VanDoorn_2";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_VanDoorn_2":
			shipType = XI_ConvertString(GetShipTypeName(npchar));
			dialog.text = "看来你消息很灵通，Johan。Hendrik van Doorn。荷兰西印度公司加勒比地区登记部门主管。护卫舰Amsterdam号指挥官。"+shipType+"。"+GetCannonQuantity(npchar)+"门炮和"+GetMaxCrewQuantity(npchar)+"名船员。";
			link.l1 = "很高兴认识您。";
			link.l1.go = "ClockTower_VanDoorn_3";
		break;

		case "ClockTower_VanDoorn_3":
			dialog.text = "您获得了五本海盗航海日志。我的副手对您评价很高，将您登记到客户名册中，并向您介绍了我办事处的服务。\n"+
						"但准入的最终决定权始终在我。亲自决定。在面谈之后。Maarten只能提议候选人——仅此而已。";
			link.l1 = "那么，我们开始吧。";
			link.l1.go = "ClockTower_VanDoorn_4";
		break;

		case "ClockTower_VanDoorn_4":
			if (!CheckAttribute(npchar, "ClockTower_option"))
			{
				dialog.text = "我需要能有效打击海盗，同时在商业上足够成功、能负担得起我们服务的船长。您符合这些标准吗？";
			}
			else dialog.text = "";
			if (!CheckAttribute(npchar, "ClockTower_option_1") && CheckAttribute(pchar, "questTemp.DiegoDeLanda_Memento"))
			{
				link.l1 = "我消灭了Mortimer Grimm。双桅横帆船Memento号的船长。";
				link.l1.go = "ClockTower_VanDoorn_option_1";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_2") && CheckAttribute(pchar, "questTemp.DiegoDeLanda_LadyBeth"))
			{
				link.l2 = "我想您的公司高度评价了我战胜Albert Blackwood的胜利。双桅纵帆船Lady Beth号是个强大的对手。";
				link.l2.go = "ClockTower_VanDoorn_option_2";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_3") && CheckAttribute(pchar, "questTemp.DiegoDeLanda_SantaMisericordia"))
			{
				link.l3 = "Fernando de Alamida不是海盗，但是…";
				link.l3.go = "ClockTower_VanDoorn_option_3";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_4") && CheckAttribute(pchar, "questTemp.KhaelRoa"))
			{
				link.l4 = "我击败了所有航海者的恐惧。您一定知道。";
				link.l4.go = "ClockTower_VanDoorn_option_4";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_5") && GetCharacterShipClass(PChar) <= 3)
			{
				link.l5 = "您刚刚把我的船登记到名册里。您认为一个不称职的船长能维护它吗？";
				link.l5.go = "ClockTower_VanDoorn_option_5";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_6") && sti(pchar.Money) >= 1000000)
			{
				link.l6 = "我干得很好，而且在加勒比海，钱长在树上。";
				link.l6.go = "ClockTower_VanDoorn_option_6";
			}
			link.l7 = "Mynheer Visser已经验证了我的能力。您自己副手的评估还不够吗？";
			link.l7.go = "ClockTower_VanDoorn_5";
			npchar.ClockTower_option = true;
		break;
		
		case "ClockTower_VanDoorn_option_1":
			dialog.text = "Grimm？我们组织从未对Grimm有过任何不满，恰恰相反。但对取代他位置的那个人……我知道他是谁，以及他最初来到加勒比海的目的。这样的恶行没有诉讼时效，我很高兴您惩罚了这个罪犯和我国真正的敌人。";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_1 = true;
		break;

		case "ClockTower_VanDoorn_option_2":
			dialog.text = "如果我没记错关于开曼事件的报告，您并没有机会验证这一点。在我看来，情况并不完全明确，但您的胜利无疑是称职的。";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_2 = true;
		break;

		case "ClockTower_VanDoorn_option_3":
			dialog.text = "但他本可以变成更糟糕的东西，没错。一个值得尊敬的敌人，尽管他输的不是您，而是他那些忘恩负义的上司。我是荷兰人，所以在涉及与卡斯蒂利亚的战争时，我知道自己在说什么。";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_3 = true;
		break;

		case "ClockTower_VanDoorn_option_4":
			dialog.text = "飞翔之心号。我至今仍然惊讶，诚实的人们看到那个怪物进港时为什么不四散逃跑。这个故事中有很多让我惊讶的地方，船长。但总有一天它会在我们的书中找到自己的位置，失去所有的神秘感。至于您……您使自己不朽了。";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_4 = true;
		break;

		case "ClockTower_VanDoorn_option_5":
			dialog.text = "您会感到惊讶的。但在您的情况下，毫无疑问，确实如此。";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_5 = true;
		break;

		case "ClockTower_VanDoorn_option_6":
			dialog.text = "因此一文不值。除非是金币，当然。";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_6 = true;
		break;

		case "ClockTower_VanDoorn_5":
			dialog.text = "\n您已获准使用办事处的服务。欢迎加入尊贵的荷兰西印度公司客户名册。";
			link.l1 = "谢谢。";
			link.l1.go = "ClockTower_VanDoorn_6";
		break;

		case "ClockTower_VanDoorn_6":
			dialog.text = "这是互惠互利的合作。您可以使用加勒比海最好的服务。我们获得了可靠的合作伙伴。";
			link.l1 = "好的。";
			link.l1.go = "ClockTower_VanDoorn_7";
		break;

		case "ClockTower_VanDoorn_7":
			dialog.text = "等等！您听到了吗？";
			link.l1 = "我什么都没听到。";
			link.l1.go = "ClockTower_VanDoorn_8";
			// звук часов останавливается
			i = FindSoundEventId("Location/clocks_mechanism_inside");
			SetSoundEventPauseState(i, true);
			DelEventHandler("NextHour", "Villemstad_BigClock_Above");
		break;

		case "ClockTower_VanDoorn_8":
			dialog.text = "问题就在这里！离开一周就……";
			link.l1 = "有什么不对吗？";
			link.l1.go = "ClockTower_VanDoorn_9";
		break;

		case "ClockTower_VanDoorn_9":
			dialog.text = "钟出了问题。需要检查机械装置。抱歉。这……很重要。";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
		break;

		case "ClockTower_VanDoorn_10":
			if (!CheckAttribute(npchar, "ClockTower_question"))
			{
				dialog.text = "看起来一切正常了。再次抱歉。您有问题吗？";
				LAi_Fade("", "");
				// звук обратно
				i = FindSoundEventId("Location/clocks_mechanism_inside");
				SetSoundEventPauseState(i, false);
				SetEventHandler("NextHour", "Villemstad_BigClock_Above", 0);
			}
			else dialog.text = "还有问题吗？";
			if (!CheckAttribute(npchar, "ClockTower_question_1"))
			{
				link.l1 = "您的副手详细解释了办事处的服务。这一切究竟是怎么做到的？";
				link.l1.go = "ClockTower_VanDoorn_question_1";
			}
			if (!CheckAttribute(npchar, "ClockTower_question_2"))
			{
				link.l2 = "您如何兼任两个职位？船长和主管？";
				link.l2.go = "ClockTower_VanDoorn_question_2";
			}
			if (!CheckAttribute(npchar, "ClockTower_question_3"))
			{
				link.l3 = "您如何在这样的条件下工作？钟表机械的轰鸣声、黑暗，还有被厚重窗帘遮住的窗户。";
				link.l3.go = "ClockTower_VanDoorn_question_3";
			}
			link.l4 = "不，谢谢您的时间。那么办事处的服务呢？";
			link.l4.go = "ClockTower_VanDoorn_11";
			npchar.ClockTower_question = true;
		break;

		case "ClockTower_VanDoorn_question_1":
			dialog.text = "这里没有任何巫术，船长。笔和墨水统治着世界。教会记录人的出生、洗礼、婚姻和死亡。改变哪怕一行——他的命运就会改变。船只稍微复杂一些，但即使在它的情况下，一笔签名也能改变很多。我不隐瞒，我为自己取得的成就感到自豪。然而我仍然知道可以做得更好。如果我们不仅把船只和人登记到账簿中，而是整个世界呢？";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
			npchar.ClockTower_question_1 = true;
		break;

		case "ClockTower_VanDoorn_question_2":
			dialog.text = "因为必须有人这么做。Amsterdam号的前任船长在与来自安提瓜的团伙的战斗中阵亡。公司找不到合适的替代者。我自荐了。接受了培训。通过了考试。获得了任命书。\n是的，我是个糟糕的船长。比您差得多——这是肯定的。但一个好的管理者可以指挥任何东西，而不仅仅是船只。学会指挥三个人很难。但一旦学会了，就能指挥三千人。办公室、船只、城市，甚至庞大的公司——没有限制，只要您找到有才能的人并信任他们代表您……后者是最困难的。真正的诅咒。";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
			npchar.ClockTower_question_2 = true;
		break;

		case "ClockTower_VanDoorn_question_3":
			dialog.text = "而且这里几乎没有空气可呼吸。船长，人会塑造自己的环境。在这里没有任何事物和任何人分散我的注意力，一切都触手可及，只服从于我和时间。如果可以的话，我会只通过纸张与外界交流。不幸的是，这不可能。请别往心里去，船长。最好是独处，但不孤独。如果您明白我的意思。";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
			npchar.ClockTower_question_3 = true;
		break;

		case "ClockTower_VanDoorn_11":
			// pchar.quest.ClockTower.date = rand(27)+1;
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			dialog.text = "我们只接受预约。您的预约时间是……#дата。如果您在指定日期没来，也没关系。联系Johan，他会告诉您下一个可用的预约时间。";
			link.l1 = "为什么要这么麻烦？";
			link.l1.go = "ClockTower_VanDoorn_12";
		break;

		case "ClockTower_VanDoorn_12":
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			dialog.text = "我们的工作很昂贵，因为我们创造真正的奇迹，为客户带来巨大的利益。利益冲突是不可能的，因此我们将整个工作日专门用于满足特定人员的需求。您的下一个可用日期：#дата。\n如果您见到Visser……Maarten提议您的候选资格是正确的。告诉他这一点。他是个好副手。让他不要怀疑。";
			link.l1 = "好的。";
			link.l1.go = "ClockTower_VanDoorn_13";
		break;

		case "ClockTower_VanDoorn_13":
			dialog.text = "祝您愉快，#полное_имя_ГГ。";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_VanDoornInCabinet_3");
		break;
		
		case "ClockTower_Visser_41":
			dialog.text = "进行得怎么样？";
			link.l1 = "今天过得很漫长，不过van Doorn确认了你的决定。";
			link.l1.go = "ClockTower_Visser_42";
		break;

		case "ClockTower_Visser_42":
			dialog.text = "感谢上帝。这么说我做对了。";
			link.l1 = "他让我转告你，你是个好deputy。";
			link.l1.go = "ClockTower_Visser_43";
		break;

		case "ClockTower_Visser_43":
			dialog.text = "真的？他……这么说的？";
			link.l1 = "是的。他确实这么说了。";
			link.l1.go = "ClockTower_Visser_44";
		break;

		case "ClockTower_Visser_44":
			dialog.text = "该死。他不该说这话的。现在我会觉得自己像个忘恩负义的混蛋。还是说他早就料到了，把一切都算计好了？";
			link.l1 = "Mynheer deputy，你突然变得不像你自己了。";
			link.l1.go = "ClockTower_Visser_45";
		break;

		case "ClockTower_Visser_45":
			dialog.text = "Captain，我是个生意人，你也是，所以我就直说了。\n"+
						 "Mynheer director早就不为我们工作了。";
			link.l1 = "什么，您说什么？！";
			link.l1.go = "ClockTower_Visser_46";
		break;

		case "ClockTower_Visser_46":
			dialog.text = "他是签约来到这里的，只有一个目标——建立船只登记部门的运作体系。他完成得相当出色，培养了接班人，提拔了我……就这样。";
			link.l1 = "什么，就这样？";
			link.l1.go = "ClockTower_Visser_47";
		break;

		case "ClockTower_Visser_47":
			dialog.text = "他的合同早就到期了。我们不知道确切时间，但完全确定这个人已经没有权利继续担任这个职位了。";
			link.l1 = "明白了。这栋楼中央区的大人物们开始紧张了。";
			link.l1.go = "ClockTower_Visser_48_1";
			link.l2 = "明白了。你等不及他把位子让给你了。";
			link.l2.go = "ClockTower_Visser_48_2";
		break;

		case "ClockTower_Visser_48_1":
			dialog.text = "没错！而且他们对此束手无策！";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_49";
		break;

		case "ClockTower_Visser_48_2":
			dialog.text = "我不会撒谎。我真的累了。见鬼，van Doorn提拔我就是为了让我在合同结束时接替他！";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_49";
		break;

		case "ClockTower_Visser_49":
			dialog.text = "但即便如此，我也绝不会仅仅因为觉得自己被骗了就去撼动那该死的位子！上帝作证，我心怀感激，敬佩这个人！";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_50";
		break;

		case "ClockTower_Visser_50":
			dialog.text = "不，mynheer。想要赶走van Doorn的是我们共同的上级。就是那些坐在塔楼墙后——这栋建筑中央区的人！但连他们都无法管住他！";
			link.l1 = "这有什么难的？van Doorn肯定没有Stuyvesant重要。";
			link.l1.go = "ClockTower_Visser_51";
		break;

		case "ClockTower_Visser_51":
			dialog.text = "这不是一艘船，也不是王室宫廷，captain。我们的公司是一种全新的组织形式。你不能只是指着某人就解雇这样一位有价值的人。\n"+
						 "首先，没人知道van Doorn合同原件在哪里。因此，没有任何解雇的依据。要是我们这么做，他会派来一帮律师，到头来我们还得欠他的。\n"+
						 "其次，管理层犯了个错误，给了van Doorn Amsterdam号的commission。他也许不是个出色的captain，但他组建的船员是整个地区最好的。只要他下令，公司的精锐士兵会毫不犹豫地占领这栋建筑。\n"+
						 "第三，他的妻子非常爱他。尽管他已经好几年没见过她了。De Witt自己的女儿能为心爱的丈夫做很多事。而十七人议会不得不接受这一点。\n"+
						 "换句话说，董事会会为你的帮助支付丰厚的报酬。并且会保留你在船只登记处的特权。";
			link.l1 = "令人印象深刻。你真是个生意人，Maarten。你向我兜售背叛，用的正是不久前你推销办事处服务时的那种专业手法。";
			link.l1.go = "ClockTower_Visser_57";
		break;

		case "ClockTower_Visser_57":
			dialog.text = "当van Doorn亲自教你谈判艺术，而你又真诚相信自己所说的话时，这并不难。";
			link.l1 = "那么你想要我做什么？";
			link.l1.go = "ClockTower_Visser_58";
		break;

		case "ClockTower_Visser_58":
			dialog.text = "只有外人才能做的事。晚上潜入办公室，找到van Doorn的合同原件。我会确保门是开着的。";
			link.l1 = "你为什么不自己做？又是什么阻止我现在就去把一切告诉你的上司？";
			link.l1.go = "ClockTower_Visser_59";
		break;

		case "ClockTower_Visser_59":
			dialog.text = "因为van Doorn习惯在夜里接待任何人，除了公司员工。如果有人看到你在不寻常的时间离开这座塔楼，不会有人感到惊讶。";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_60";
		break;

		case "ClockTower_Visser_60":
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			dialog.text = "至于你的威胁……你现在见不到director，你约的是另一天。#дата，对吧？到那时候，消息的紧迫性就会降低不少。而且，director从不奖励告密者。他总是保护自己的员工。";
			link.l1 = "对你来说倒是方便。";
			link.l1.go = "ClockTower_Visser_61";
		break;

		case "ClockTower_Visser_61":
			dialog.text = "这不是背叛，captain。我们只是想遵守合同，保护公司的安全。还有Willemstad，顺便说一句，你帮了它很多。";
			link.l1 = "我会考虑的。但我什么都不承诺。";
			link.l1.go = "ClockTower_Visser_62";
		break;

		case "ClockTower_Visser_62":
			dialog.text = "我对你的要求不过如此，captain。首先，你是我们的客户。无论结果如何，我都非常自豪，正是我找到了你，并把你录入了办事处的登记册。";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_63";
		break;

		case "ClockTower_Visser_63":
			dialog.text = "你随时可以在中央区找到我。祝你愉快。";
			link.l1 = "再见。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_Quest_3");
		break;
		
		case "ClockTower_Visser_64":
			dialog.text = "你好， "+GetTitle(NPChar, false)+". 有消息吗？";
			link.l1 = "还没有。";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Visser_64";
		break;
		
		case "ClockTower_Johan_51":
			if (GetHour() >= 6 && GetHour() < 24)
			{
				if (pchar.quest.ClockTower.date <= GetDataDay())
				{
					NextMonth = GetDataMonth() + 1;
					if (NextMonth == 13) NextMonth = 1;
				}
				else NextMonth = GetDataMonth();
				Month = XI_ConvertString("MonthGen_" + NextMonth);
				if (pchar.quest.ClockTower.date == GetDataDay() && CheckAttribute(pchar, "questTemp.ClockTower_NoToday"))
				{
					if (!CheckAttribute(npchar, "ClockTower_repeat"))
					{
						dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"，今天是您的日子。请进。";
						npchar.ClockTower_repeat = true;
						SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
						
						ClockTower_RightDay();
					}
					else
					{
						dialog.text = "祝您愉快, "+GetTitle(NPChar, false)+"!";
					}
				}
				else
				{
					if (!CheckAttribute(npchar, "ClockTower_repeat"))
					{
						dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"，您约的是另一天。我们很高兴在 "+pchar.quest.ClockTower.date+" "+month+" 见到您。";
						npchar.ClockTower_repeat = true;
						SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
					}
					else
					{
						dialog.text = "祝您愉快, "+GetTitle(NPChar, false)+"!";
					}
				}
				link.l1 = "谢谢你，Johan。";
				link.l1.go = "exit";
				NextDiag.TempNode = "ClockTower_Johan_51";
			}
			else
			{
				if (!CheckAttribute(npchar, "ClockTower_repeatnight"))
				{	// первая ночная встреча с Йоханом
					dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"，您来得有点晚了。办事处已经关门了。";
					link.l1 = "你好， "+npchar.name+". 我听说它甚至在夜里也营业。";
					link.l1.go = "ClockTower_Johan_52";
					npchar.ClockTower_repeatnight = true;
					SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
				}
				else
				{
					dialog.text = ""+TimeGreeting()+", "+GetTitle(NPChar, false)+"!";
					link.l1 = "";
					link.l1.go = "ClockTower_Johan_53";
				}
			}
		break;
		
		case "ClockTower_Johan_52":
			dialog.text = "没错。什么人都有。甚至神父有时也会来，嘿嘿。但他们都必须先经过我。而关于你，我没有收到任何指示。";
			link.l1 = "等等，你在这里日夜站岗？这怎么可能？";
			link.l1.go = "ClockTower_Johan_53";
		break;

		case "ClockTower_Johan_53":
			if (!CheckAttribute(npchar, "ClockTower_repeatnight_2"))
			{
				dialog.text = "是的。Mynheer director刚下了命令。他是怎么做到的，我不知道，但我的时间还是够用的，既能休息又能值班。而且他们还给我涨了工资——真没什么可抱怨的！";
				npchar.ClockTower_repeatnight_2 = true;
			}
			else
			{
				dialog.text = "还有别的吗？";
			}
			if (!CheckAttribute(pchar, "questTemp.ClockTower_NightFree"))
			{
				link.l1 = "你应该让我过去。我为公司的高层管理人员工作。";
				link.l1.go = "ClockTower_Johan_54";
				link.l2 = "(杀了他)";
				link.l2.go = "ClockTower_Johan_KillHim";
			}
			link.l3 = "继续保持，士兵。";
			link.l3.go = "ClockTower_Johan_NightExit";
		break;

		case "ClockTower_Johan_KillHim":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_KillToJohan");
		break;

		case "ClockTower_Johan_NightExit":
			DialogExit();
			NextDiag.CurrentNode = "ClockTower_Johan_51";
		break;

		case "ClockTower_Johan_54":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 80)
			{
				dialog.text = "呃。您想从我这儿得到什么，mynheer captain？我只是个普通士兵，什么都不知道。";
				link.l1 = "你什么都知道，Johan。别这么谦虚。高层办公室里的先生们也许不用向你汇报，但你肯定听说过他们之间的矛盾。";
				link.l1.go = "ClockTower_Johan_55";
				Notification_Skill(true, 80, SKILL_LEADERSHIP);
			}
			else
			{
				dialog.text = "我只是个小人物，但我不会越过直属上司。抱歉，mynheer captain。";
				link.l1 = "我们还会再谈这个话题的。";
				link.l1.go = "ClockTower_Johan_NightExit";
				Notification_Skill(false, 80, SKILL_LEADERSHIP);
			}
		break;

		case "ClockTower_Johan_55":
			Achievment_Set("ach_CL_197");
			dialog.text = "没错，mynheer captain。Mynheer director待得太久了。暴风雨即将来临。";
			link.l1 = "你听说了什么？";
			link.l1.go = "ClockTower_Johan_56";
		break;

		case "ClockTower_Johan_56":
			dialog.text = "所有人都担心，如果不是今天，那明天他就会夺权。对我们这个偏僻之地来说，他这个人太重要了。他用检查让所有人喘不过气来，每个签名都要经过他。\n我跟您说实话，您自己也看到了：每次Amsterdam号进港时，立刻就会出现不祥的骚动。";
			link.l1 = "我可以解决这个问题，但你必须让我进去。";
			link.l1.go = "ClockTower_Johan_57";
		break;

		case "ClockTower_Johan_57":
			dialog.text = "请进，mynheer captain。只求您别害我：如果mynheer director知道了，我就没命了，而我还有家人要养活。";
			link.l1 = "我会尽力的。";
			link.l1.go = "ClockTower_Johan_58_hint";
		break;

		case "ClockTower_Johan_58_hint":
			ClockTower_AddBook();
			dialog.text = "您是个好人，mynheer captain。也许我能帮到您：我知道mynheer director在其中一本书里藏着一把钥匙。是干什么用的——我不知道，但也许会有用。";
			link.l1 = "谢谢你，Johan。";
			link.l1.go = "ClockTower_Johan_NightSuccess";
		break;
		
		case "ClockTower_Johan_NightSuccess":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_NightFree");
			NextDiag.CurrentNode = "ClockTower_Johan_51";
			// if (sti(pchar.reputation.nobility) < 71) Notification_Reputation(false, 71, "low");
		break;
		
		case "ClockTower_Peter_50":
			dialog.text = "站住。您在荷兰西印度公司的地盘上。船只登记部门和档案馆。仅凭预约入内。";
			link.l1 = "我是"+GetTitle(NPChar, false)+" "+pchar.name+".";
			link.l1.go = "ClockTower_Peter_51";
			DelLandQuestMark(npchar);
		break;
		
		case "ClockTower_Peter_51":
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			if (pchar.quest.ClockTower.date == GetDataDay() && CheckAttribute(pchar, "questTemp.ClockTower_NoToday"))
			{
				if (!CheckAttribute(npchar, "ClockTower_repeat"))
				{
					dialog.text = "您有预约吗？请进。";
					npchar.ClockTower_repeat = true;
					SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
					
					ClockTower_RightDay();
				}
				else
				{
					dialog.text = "...";
				}
			}
			else
			{
				if (!CheckAttribute(npchar, "ClockTower_repeat"))
				{
					dialog.text = "您的预约在另一天： "+pchar.quest.ClockTower.date+" "+month+".";
					npchar.ClockTower_repeat = true;
					SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
				}
				else
				{
					dialog.text = "...";
				}
			}
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Peter_51";
		break;
		
		case "ClockTower_Visser_71":
			dialog.text = "你好，"+GetTitle(NPChar, false)+"。有消息吗？";
			link.l1 = "是的。合同在这里。";
			link.l1.go = "ClockTower_Visser_72";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_72":
			dialog.text = "难以置信……七年前就到期了！";
			link.l1 = "所以这就是你需要的？";
			link.l1.go = "ClockTower_Visser_73";
		break;

		case "ClockTower_Visser_73":
			dialog.text = "没错！有了这份文件，公司就能合法地召回他。没有漏洞。没有借口。时间到了——就这样。";
			link.l1 = "接下来呢？";
			link.l1.go = "ClockTower_Visser_74";
		break;

		case "ClockTower_Visser_74":
			dialog.text = "我会把合同送到阿姆斯特丹。十七人议会会做出决定。Doorn会被命令回去。他无法拒绝。";
			link.l1 = "如果他拒绝呢？";
			link.l1.go = "ClockTower_Visser_75";
		break;

		case "ClockTower_Visser_75":
			dialog.text = "他做不到。虽然他的妻子是股东、大议长的女儿，但就连她父亲也不会对抗议会。而Catharina本人……她已经等了十年。如果她知道他可以回去却拒绝了——这会要了她的命。";
			link.l1 = "真残酷。";
			link.l1.go = "ClockTower_Visser_76";
		break;

		case "ClockTower_Visser_76":
			dialog.text = "是的。但这是唯一的办法。谢谢你，captain。你做了一件重要的事。";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_77";
		break;

		case "ClockTower_Visser_77":
			if (CharacterIsAlive("ClockTower_Johan"))
			{
				dialog.text = "你的报酬——五百杜布隆。我向你保证：两三个月后，当我坐上director的位子时，你将获得办事处服务的无限使用权。不用排队。不用预约。随时都可以。";
				AddItems(pchar, "gold_dublon", 500);
			}
			else
			{
				dialog.text = "而且你杀了Johan。我已经背叛了一个我敬佩、欠他一切的人。现在又是这个。\n"+
							 "也许在你的船上，人命如草芥，但公司珍视自己的员工。而我对自己成为谋杀的帮凶感到恶心。\n"+
							 "你的杜布隆会给Johan的家人，但我会履行交易的第二部分。\n"+
							 "我向你保证：两三个月后，当我坐上director的位子时，你将获得办事处服务的无限使用权。";
			}
			link.l1 = "我相信你的承诺。祝你愉快。";
			link.l1.go = "ClockTower_Visser_78";
		break;

		case "ClockTower_Visser_78":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_WaitFewMonths");
		break;

		case "ClockTower_Visser_79":
			dialog.text = "你好，"+GetTitle(NPChar, false)+"。目前还没有新闻。别担心，我记得我们的协议。";
			link.l1 = "希望如此。";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Visser_79";
		break;

		case "ClockTower_Visser_81":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+"！请进，请进。很高兴见到你。";
			link.l1 = "恭喜你获得任命。";
			link.l1.go = "ClockTower_Visser_82";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_82":
			dialog.text = "谢谢。十七人议会的决定比我预期的要快。合同被证明是充分的证据。Mynheer van Doorn被解除了办事处的管理职务。";
			link.l1 = "他是怎么接受的？";
			link.l1.go = "ClockTower_Visser_83";
		break;

		case "ClockTower_Visser_83":
			dialog.text = "他懂得如何接受失败。只是从办公室收拾了私人物品就离开了。不过他真的输了吗？\n"+
						 "他们保留了他对Amsterdam号的指挥权。在这一点上，公司确实犯了个错误。当时就不应该把那艘船给他。\n"+
						 "我们低估了他。希望最终结果不会更糟。";
			link.l1 = "还能有多糟？";
			link.l1.go = "ClockTower_Visser_84";
		break;

		case "ClockTower_Visser_84":
			dialog.text = "Mynheer van Doorn知道是谁从他办公室拿走了合同。";
			link.l1 = "怎么会？！";
			link.l1.go = "ClockTower_Visser_85";
		break;

		case "ClockTower_Visser_85":
			dialog.text = "别这样看我！我什么都没告诉他。他自己弄明白了。";
			link.l1 = "现在怎么办？";
			link.l1.go = "ClockTower_Visser_86";
		break;

		case "ClockTower_Visser_86":
			dialog.text = "现在他把你当成敌人。但只要你不对七省联合共和国构成威胁——他就不会动你。\n"+
						 "Van Doorn总是知道如何区分公私。问题是，你能做到吗？";
			link.l1 = "如果我做不到呢？";
			link.l1.go = "ClockTower_Visser_87";
		break;

		case "ClockTower_Visser_87":
			dialog.text = "那他就会找到你。并完成他的工作。别给他理由。";
			link.l1 = "我会努力的。";
			link.l1.go = "ClockTower_Visser_88";
		break;

		case "ClockTower_Visser_88":
			dialog.text = "祝你愉快，"+GetTitle(NPChar, false)+"。随时可以使用我们的……我的办事处的服务。";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_VillemstadStreet");
		break;
		
		case "ClockTower_Johan_61":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+", 您被期待着。Mynheer Visser命令所有客户可以自由进入。他说旧规矩太严格了。";
			link.l1 = "谢谢你，Johan。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_FreeAccess_2");
			DelLandQuestMark(npchar);
		break;
		
		case "ClockTower_Peter_61":
			dialog.text = "请在任何工作时间进入。预约已经取消。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_FreeAccess_2");
			DelLandQuestMark(npchar);
		break;
		
		case "ClockTower_Helena_1":
			dialog.text = "你有空吗？";
			link.l1 = "为了你——随时都有。";
			link.l1.go = "ClockTower_Helena_2";
		break;

		case "ClockTower_Helena_2":
			dialog.text = "啊，要是真的就好了，我的captain。你生活中还有其他的激情。比如现在，占据你英俊脑袋的就不是我，对吧？";
			link.l1 = "...";
			link.l1.go = "ClockTower_Helena_3";
		break;

		case "ClockTower_Helena_3":
			dialog.text = "我就知道。我很了解我的男人。而水手的激情——我更熟悉。所以直说吧，亲爱的……\n"+
						 "夺取尊贵的荷兰西印度贸易公司旗舰会让我们付出什么代价？";
			link.l1 = "要让van Doorn亲自来找我们，我就必须成为Willemstad的敌人。";
			link.l1.go = "ClockTower_Helena_4";
		break;

		case "ClockTower_Helena_4":
			dialog.text = "哦，我的captain……所以就这样了。不是第一次了，对吧？";
			link.l1 = "好像你不赞成似的。";
			link.l1.go = "ClockTower_Helena_5";
		break;

		case "ClockTower_Helena_5":
			dialog.text = "我爱上的就是真实的你。我永远站在你这边。只是记住我们……也就是你对自己的人承担的责任。";
			link.l1 = "不过，为此我们有Alonso。他会提醒你的。";
			link.l1.go = "ClockTower_Helena_6";
		break;

		case "ClockTower_Helena_6":
			dialog.text = "我们一出海就告诉他，我的captain。";
			link.l1 = "那我们就别拖延了，亲爱的。";
			link.l1.go = "ClockTower_Girl_End";
		break;
		
		case "ClockTower_Mary_1":
			dialog.text = "Charles？我想问你点事。";
			link.l1 = "当然，Mary。怎么了？";
			link.l1.go = "ClockTower_Mary_2";
		break;

		case "ClockTower_Mary_2":
			dialog.text = "我……我为你担心，真的。我认得这种眼神。你在想不好的事。";
			link.l1 = "胡说八道。我自己都不记得刚才在想什么。你怎么知道？";
			link.l1.go = "ClockTower_Mary_3";
		break;

		case "ClockTower_Mary_3":
			dialog.text = "我就是知道！我看到了那艘Amsterdam号，真的。漂亮的船。非常漂亮。但是……\n"+
						 "你已经决定好了一切……就像以前一样，对吧？";
			link.l1 = "Van Doorn会亲自来找我们，但为此我必须成为Willemstad的敌人。";
			link.l1.go = "ClockTower_Mary_4";
		break;

		case "ClockTower_Mary_4":
			dialog.text = "值得吗，Charles？";
			link.l1 = "我不知道，Mary。";
			link.l1.go = "ClockTower_Mary_5";
		break;

		case "ClockTower_Mary_5":
			dialog.text = "我希望你快乐，真的。但我还是会请Alonso再劝劝你放弃这件事，好吗！";
			link.l1 = "这倒像他的作风。走吧，亲爱的。";
			link.l1.go = "ClockTower_Girl_End";
		break;
		
		case "ClockTower_Girl_End":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_Girl_DlgExit");
		break;
		
		case "ClockTower_Alonso_1":
			dialog.text = "Cap，我们得谈谈。";
			link.l1 = "我在听。";
			link.l1.go = "ClockTower_Alonso_2";
			link.l2 = "现在不行，Alonso。";
			link.l2.go = "ClockTower_Alonso_2";
		break;

		case "ClockTower_Alonso_2":
			dialog.text = "事情是这样的，cap，但你必须听我说。这是，呃，怎么说来着……\n"+
						 "紧急情况——就是这个！\n"+
						 "总之，有只小鸟告诉我，您亲自把公司的一位director从他舒适的位子上赶了下来，而他怀恨在心，现在正开着他那艘漂亮的护卫舰追杀我们。";
			link.l1 = "这明显是夸大其词。";
			link.l1.go = "ClockTower_Alonso_3";
		break;

		case "ClockTower_Alonso_3":
			dialog.text = "您知道人们有多爱嚼舌根，cap。让谣言酝酿一周——您就会听说van Doorn被种植园主的女儿迷住了，Amsterdam号上有活死人船员，货舱里藏着Cortés本人的宝藏。\n"+
						 "但我更关心真实情况。那么，cap，会有战斗还是不会？";
			link.l1 = "...";
			if (CheckPassengerInCharacter(pchar, "Irons")) // Tommy
			{
				link.l1.go = "ClockTower_Alonso_4_1";
			}
			else
			{
				link.l1.go = "ClockTower_Alonso_4_5";
			}
		break;

		case "ClockTower_Alonso_4_1":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_TommyInCabin");
		break;

		case "ClockTower_Alonso_4_2":
			dialog.text = "顺便说一句，这他妈的会很有趣，我不反对！荷兰旗舰！哈！我能想象那些吃奶酪的家伙们的表情，当我们……";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_4_3";
		break;

		case "ClockTower_Alonso_4_3":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_TommyInCabin_2");
		break;

		case "ClockTower_Alonso_4_4":
			dialog.text = "Tommy，闭嘴。";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_4_5";
		break;

		case "ClockTower_Alonso_4_5":
			dialog.text = "...";
			link.l1 = "如果真要打，也不会很快。Van Doorn不会寻求报复，他不是那种人。首先我们得好好激怒荷兰人。";
			link.l1.go = "ClockTower_Alonso_4_6";
			CharacterTurnByChr(npchar, pchar);
		break;

		case "ClockTower_Alonso_4_6":
			dialog.text = "谢谢，cap，这会让船员们安心。";
			link.l1 = "那你呢？";
			link.l1.go = "ClockTower_Alonso_5";
		break;

		case "ClockTower_Alonso_5":
			dialog.text = "我的职责是保护船员。保护他们不受自己伤害，还有……如果可能的话，不受您伤害。反正您会做您计划好的事。";
			if (CheckPassengerInCharacter(pchar, "Irons")) // Tommy
			{
				link.l1 = "...";
				link.l1.go = "ClockTower_Alonso_5_add";
			}
			else
			{
				link.l1 = "继续保持，Alonso。";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("ClockTower_CuracaoInCabin_4_DlgExit");
			}
		break;

		case "ClockTower_Alonso_5_add":
			StartInstantDialogTurnToNPC("Irons", "ClockTower_Alonso_6", "Quest\ShipsPack\ClockTower_dialog.c", "ClockTower_Alonso");
		break;

		case "ClockTower_Alonso_6":
			dialog.text = "像西班牙骡子一样倔！";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_6_add";
		break;

		case "ClockTower_Alonso_6_add":
			StartInstantDialogTurnToNPC("ClockTower_Alonso", "ClockTower_Alonso_7", "Quest\ShipsPack\ClockTower_dialog.c", "Irons");
		break;

		case "ClockTower_Alonso_7":
			dialog.text = "上帝啊，为什么是我。";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_7_add";
		break;

		case "ClockTower_Alonso_7_add":
			StartInstantDialogTurnToNPC("Irons", "ClockTower_Alonso_8", "Quest\ShipsPack\ClockTower_dialog.c", "ClockTower_Alonso");
		break;

		case "ClockTower_Alonso_8":
			dialog.text = "你把一切都搞复杂了！Cap想要一艘漂亮的船——我们就给他弄一艘漂亮的船！我们是一个团队！";
			link.l1 = "继续保持，Alonso。Tommy，出去。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_CuracaoInCabin_4_DlgExit");
		break;
		
		// Абордаж Амстердама, перед боем с Ван Дормом
		case "ClockTower_VanDoorn_21":
			NationName = GetSexPhrase(""+NationNameMan(sti(pchar.baseNation))+"",""+NationNameWoman(sti(pchar.baseNation))+"");
			shipType = LowerFirst(XI_ConvertString(GetShipTypeName(pchar)));
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" "+GetFullName(pchar)+", "+NationName+". 您的船——'"+PChar.Ship.Name+"'，"+shipType+"。"+GetCannonQuantity(pchar)+"门炮和"+GetMaxCrewQuantity(pchar)+"名船员。";
			link.l1 = "您一如既往地精确，mynheer director。";
			link.l1.go = "ClockTower_VanDoorn_22";
		break;

		case "ClockTower_VanDoorn_22":
			dialog.text = "这个头衔已经不属于我了——多亏了您的努力。但别以为我攻击您是出于小气的报复心理。我只是在履行职责。\n"+
						 "显然我失败了。我也不可能成功：我曾经告诉过您，您是比我优秀得多的captain。";
			link.l1 = "这重担是您自己揽下的！您的合同七年前就到期了。是什么阻止您回家？";
			link.l1.go = "ClockTower_VanDoorn_23";
		break;

		case "ClockTower_VanDoorn_23":
			dialog.text = "是什么阻止您做同样的事？您知道答案，captain。您有梦想。您没有别的生活。而一旦放松控制——一切就会崩塌。\n"+
						 "我本可以给这片地区带来秩序。终止无休止的暴力循环。如果我没有放松控制。如果我压制住恐惧，做了早该做的事。\n"+
						 "但够了，别那么悲壮了。我作为战士和作为captain一样糟糕，但我懂得挑选手下。您自己让自己成了我的最后一项工作，captain。今天办事处登记册上会少两个captain！";
			if (CheckCharacterItem(PChar, "CatharinaLetter"))
			{
				link.l1 = "您刚才说了些关于恐惧的话。那就读读这封信吧。";
				link.l1.go = "ClockTower_VanDoorn_24";
			}
			link.l2 = "只会少一个。开战！";
			link.l2.go = "ClockTower_cabinFight";
		break;

		case "ClockTower_VanDoorn_24":
			dialog.text = "来自Catharina的？！您怎么敢把私事和公事混在一起？！";
			link.l1 = "如您所见，信还是封着的。我在等。";
			link.l1.go = "ClockTower_VanDoorn_25";
			TakeItemFromCharacter(pchar, "CatharinaLetter");
			pchar.questTemp.ClockTower_GaveCatharinaLetter = true;
		break;

		case "ClockTower_VanDoorn_25":
			dialog.text = "……她再也等不下去了……会去找别人……如果我不回去的话？！";
			link.l1 = "您已经失去了办事处。您的船员正在死去。您准备好连家人也失去吗？";
			link.l1.go = "ClockTower_VanDoorn_26";
		break;

		case "ClockTower_VanDoorn_26":
			dialog.text = "不能这样。Captain，您接受我的投降吗？";
			link.l1 = "是的。滚出我的船。";
			link.l1.go = "ClockTower_VanDoorn_27";
			link.l2 = "不。这是对死刑犯的最后礼遇。开战！";
			link.l2.go = "ClockTower_cabinFight";
		break;

		case "ClockTower_VanDoorn_27":
			dialog.text = "那么恭喜您获胜，Captain #полное_имя_гг。今天登记册上只会少一个captain。再见。";
			link.l1 = "...";
			link.l1.go = "ClockTower_cabinPeace";
			GiveItem2Character(PChar, "pistol15");
			RemoveCharacterEquip(npchar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(npchar, GUN_ITEM_TYPE);
			TakeItemFromCharacter(npchar, "pistol15");
		break;
		
		// Финальный диалог с Маартеном
		case "ClockTower_Visser_101":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" "+GetFullName(pchar)+". 我没想到您敢来这里。";
			link.l1 = "为什么不呢？我仍然是您的客户，而且我需要办事处的服务。";
			link.l1.go = "ClockTower_Visser_102";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_102":
			dialog.text = "服务？服务？！在您做了那些事之后？您是尊贵的荷兰西印度公司的敌人！另一个captain会取代您的客户位置！";
			link.l1 = "不太可能。看看我在van Doorn的文件里找到了什么。";
			link.l1.go = "ClockTower_Visser_103";
		break;

		case "ClockTower_Visser_103":
			dialog.text = "...";
			link.l1 = "您的前任认为使用这份文件有损他的尊严——即使在他的位子开始动摇时也是如此。";
			link.l1.go = "ClockTower_Visser_104";
			TakeItemFromCharacter(pchar, "Visser_Key");
		break;

		case "ClockTower_Visser_104":
			dialog.text = "...";
			link.l1 = "您很幸运有这样的上司。因为这种把戏，您本该面临审判——这还是最好的情况。";
			link.l1.go = "ClockTower_Visser_105";
		break;

		case "ClockTower_Visser_105":
			dialog.text = "...";
			link.l1 = "您是个生意人。您知道我要说什么。";
			link.l1.go = "ClockTower_Visser_106";
		break;

		case "ClockTower_Visser_106":
			dialog.text = "您……您在登记册上的位置已恢复。";
			link.l1 = "唉，Maarten。您想要占据director的位置，尽管他给了您一切。他把您从审判中救了出来，甚至不认为有必要告诉您。";
			link.l1.go = "ClockTower_Visser_107";
		break;

		case "ClockTower_Visser_107":
			dialog.text = "...";
			link.l1 = "这个小罪过永远不会让您更上一层楼，而会让您生活在持续的恐惧中。";
			link.l1.go = "ClockTower_Visser_108";
		break;

		case "ClockTower_Visser_108":
			dialog.text = "...";
			link.l1 = "现在轮到您被束缚在这个地方了。但您肯定不会有像van Doorn那样的deputy。";
			link.l1.go = "ClockTower_Visser_109";
		break;

		case "ClockTower_Visser_109":
			dialog.text = "够了。您想彻底摧毁我吗？！";
			link.l1 = "不完全是。我要您把我的新船登记在册。我不想有任何误解。";
			link.l1.go = "ClockTower_Visser_110";
		break;

		case "ClockTower_Visser_110":
			dialog.text = "您的船是Amsterdam号。荷兰西印度公司旗舰。它不能就这么……重新登记。";
			link.l1 = "为什么不行？纸张能容纳一切。您的系统不就是这样运作的吗？";
			link.l1.go = "ClockTower_Visser_111";
		break;

		case "ClockTower_Visser_111":
			dialog.text = "天哪，但凡事都有个限度！";
			link.l1 = "我相信这个地方的力量。您也应该相信。";
			link.l1.go = "ClockTower_Visser_112";
		break;

		case "ClockTower_Visser_112":
			dialog.text = "...";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_113";
		break;
		
		case "ClockTower_Visser_113":
			dialog.text = "全名？";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "ClockTower_Visser_114";
		break;

		case "ClockTower_Visser_114":
			dialog.text = "国籍？";
			link.l1 = ""+NationNameNominative(sti(pchar.baseNation))+".";
			link.l1.go = "ClockTower_Visser_115";
		break;

		case "ClockTower_Visser_115":
			dialog.text = "您的船名？";
			link.l1 = ""+PChar.Ship.Name+".";
			link.l1.go = "ClockTower_Visser_116";
		break;

		case "ClockTower_Visser_116":
			shipType = XI_ConvertString(GetShipTypeName(pchar));
			dialog.text = "船只类型？";
			link.l1 = ""+shipType+".";
			link.l1.go = "ClockTower_Visser_117";
		break;

		case "ClockTower_Visser_117":
			dialog.text = "炮数？";
			link.l1 = ""+GetCannonQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_118";
		break;

		case "ClockTower_Visser_118":
			dialog.text = "船员人数？";
			link.l1 = ""+GetMaxCrewQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_119";
		break;

		case "ClockTower_Visser_119":
			dialog.text = "好。现在在这里签名。这里。还有这里也要签。";
			link.l1 = "就这样？";
			link.l1.go = "ClockTower_Visser_120";
		break;

		case "ClockTower_Visser_120":
			dialog.text = "就这样。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_Visser_pausa_1");
		break;

		case "ClockTower_Visser_121":
			dialog.text = "...";
			link.l1 = "您忘了说些什么。";
			link.l1.go = "ClockTower_Visser_122";
		break;

		case "ClockTower_Visser_122":
			dialog.text = "\n欢迎加入尊贵的荷兰西印度公司客户登记册。";
			link.l1 = "再见，mynheer director。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_FINAL");
		break;
		

		//------------------Услуги конторы------------------//
		case "ClockTower_OfficeServices":
			if (npchar.id == "ClockTower_VanDoorn")
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" "+pchar.name+". 我和我的办事处今天能为您做些什么？";
			}
			if (npchar.id == "ClockTower_Visser")
			{
				if (CharacterIsAlive("ClockTower_VanDoorn"))
				{
					dialog.text = "很高兴见到您，"+GetTitle(NPChar, false)+"! 随时为您服务。您今天对什么感兴趣？";
				}
				else
				{
					dialog.text = "那么？您今天对什么感兴趣？";
				}
			}
			link.l1 = "您能对我的船进行审计吗？我想提升它的特性。";
			link.l1.go = "ClockTower_OfficeServices_audit"; // Аудит
			link.l2 = "我对我的船的专业化不满意。您能弄到新文件吗？";
			link.l2.go = "ClockTower_OfficeServices_changeTrait"; // Смена документов
			link.l3 = "您能把我的船登记到公司登记册吗？让海盗和猎人三思而行。";
			link.l3.go = "ClockTower_OfficeServices_buffSpec"; // Занесение в реестр
			if (!CheckAttribute(pchar, "questTemp.ShipInsurance"))
			{
				link.l4 = "我想为存放在港口管理处的船只投保。现在的和将来的。";
				link.l4.go = "ClockTower_OfficeServices_Insurance"; // Страховка (пропадает после оплаты)
			}
			if(!CheckAttributeEqualTo(npchar, "last_logbook_date", LastSpeakDate()) && ClockTower_JournalsQty() > 0)
			{
				link.l5 = "您接受海盗captain的航海日志，对吧？";
				link.l5.go = "ClockTower_OfficeServices_logbook"; // Награда за пиратов (раз в сутки)
			}
			link.l6 = "也许今天不行。祝您愉快。";
			link.l6.go = "ClockTower_OfficeServices_exit"; // Отказ
		break;

		// Аудит
		case "ClockTower_OfficeServices_audit":
			if (!IsShipInPort(npchar.city))
			{
				ClockTower_NoShipInPort(link);
				break;
			}
			n = 0;
			dialog.text = "费用取决于船的大小。我们说的是哪艘船？";
			for (i = 0; i < COMPANION_MAX; i++)
			{
				idx = GetCompanionIndex(pchar, i);
				if (idx < 0) continue;

				sld = GetCharacter(idx);
				realShip = GetRealShip(GetCharacterShipType(sld));
				if (CheckAttribute(realShip, "tuning.Audit")) continue;
				if (!IsFellowOurCrew(sld)) continue;

				n++;
				sTemp = "l"+n;
				link.(sTemp) = XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName) + " '" + sld.Ship.Name + "'.";
				link.(sTemp).go = Dialog.currentNode + "_chosenIdx/" + idx;
			}

			if (n == 0)
			{
				dialog.text = "遗憾的是，审计是针对每艘船的一次性服务。还有别的吗？";
				link.l1 = "那么下次再说吧。";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_audit_chosenIdx":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			sTemp = "";
			if (CanUpgradeShip(sld, &sTemp, "Audit"))
			{
				n = GetAuditShipCost(sld);
				dialog.text = "让我看看……这将花费**#цена**杜布隆。";
				if (PCharDublonsTotal() > n)
				{
					link.l1 = "开始吧。";
					link.l1.go = "ClockTower_OfficeServices_audit_upgradeShip";
				}
				link.l2 = "不过……下次再说吧。";
				link.l2.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "Kaleuche")
			{
				dialog.text = "恐怕我不得不拒绝您。根据登记册，您的船多年前已经葬身海魔之口，这样的时间幽灵无法靠一纸文书改变。在我们能够合作之前，您需要先将它修复。据说伊斯拉·特索罗上有一位工匠愿意接下这样的工作。";
				link.l1 = "明白，谢谢。";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "alreadyUpgraded")
			{
				dialog.text = "$船只已经完成改进。";
				link.l1 = "明白，谢谢。";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_audit_upgradeShip":
			Achievment_Set("ach_CL_199");
			sld = GetCharacter(sti(Dialog.tmpIdx));
			RemoveDublonsFromPCharTotal(GetAuditShipCost(sld));
			UpgradeShipAudit(sld);
			dialog.text = "完成。";
			link.l1 = "谢谢。";
			link.l1.go = "ClockTower_OfficeServices_exit";
		break;

		// Улучшение специализации
		case "ClockTower_OfficeServices_buffSpec":
			if (!IsShipInPort(npchar.city))
			{
				ClockTower_NoShipInPort(link);
				break;
			}
			n = 0;
			dialog.text = "费用取决于船的大小。我们说的是哪艘船？";
			for (i = 0; i < COMPANION_MAX; i++)
			{
				idx = GetCompanionIndex(pchar, i);
				if (idx < 0) continue;

				sld = GetCharacter(idx);
				realShip = GetRealShip(GetCharacterShipType(sld));
				if (CheckAttribute(realShip, "tuning.SpecialityUpgrade")) continue;
				if (!IsFellowOurCrew(sld)) continue;

				n++;
				sTemp = "l"+n;
				link.(sTemp) = XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName) + " '" + sld.Ship.Name + "'.";
				link.(sTemp).go = Dialog.currentNode + "_chosenIdx/" + idx;
			}

			if (n == 0)
			{
				dialog.text = "遗憾的是，登记是针对每艘船的一次性服务。还有别的吗？";
				link.l1 = "那么下次再说吧。";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_buffSpec_chosenIdx":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			sTemp = "";
			if (CanUpgradeShip(sld, &sTemp, "SpecialityUpgrade"))
			{
				n = GetSpecialityUpgradeShipCost(sld);
				dialog.text = "让我看看……这将花费**#цена**杜布隆。";
				if (PCharDublonsTotal() > n)
				{
					link.l1 = "开始吧。";
					link.l1.go = "ClockTower_OfficeServices_buffSpec_upgradeShip";
				}
				link.l2 = "不过……下次再说吧。";
				link.l2.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "Kaleuche")
			{
				dialog.text = "恐怕我不得不拒绝您。根据登记册，您的船多年前已经葬身海魔之口，这样的时间幽灵无法靠一纸文书改变。在我们能够合作之前，您需要先将它修复。据说伊斯拉·特索罗上有一位工匠愿意接下这样的工作。";
				link.l1 = "明白，谢谢。";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "alreadyUpgraded")
			{
				dialog.text = "$船只已经完成改进。";
				link.l1 = "明白，谢谢。";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_buffSpec_upgradeShip":
			Achievment_Set("ach_CL_199");
			sld = GetCharacter(sti(Dialog.tmpIdx));
			RemoveDublonsFromPCharTotal(GetSpecialityUpgradeShipCost(sld));
			UpgradeShipSpeciality(sld);
			dialog.text = "完成。";
			link.l1 = "谢谢。";
			link.l1.go = "ClockTower_OfficeServices_exit";
		break;

		// Смена трейта корабля
		case "ClockTower_OfficeServices_changeTrait":
			if (!IsShipInPort(npchar.city))
			{
				ClockTower_NoShipInPort(link);
				break;
			}
			n = 0;
			dialog.text = "费用取决于船的大小。我们说的是哪艘船？";
			for (i = 0; i < COMPANION_MAX; i++)
			{
				idx = GetCompanionIndex(pchar, i);
				if (idx < 0) continue;

				sld = GetCharacter(idx);
				realShip = GetRealShip(GetCharacterShipType(sld));
				sTemp = "";
				ShipTraitCanBeChanged(sld, &sTemp);
				if (sTemp == "EmptyShip" || sTemp == "QuestCompanion") continue;

				n++;
				sTemp = "l"+n;
				link.(sTemp) = XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName) + " '" + sld.Ship.Name + "'.";
				link.(sTemp).go = Dialog.currentNode + "_chosenIdx/" + idx;
			}

			if (n == 0)
			{
				dialog.text = "嗯……我在港口看不到您的船只。";
				link.l1 = "那么下次再说吧。";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_changeTrait_chosenIdx":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			sTemp = "";

			if (ShipTraitCanBeChanged(sld, &sTemp))
			{
				n = GetChangeShipTraitCost(sld);
				dialog.text = "让我看看……这将花费**#цена**杜布隆。";
				if (PCharDublonsTotal() > n)
				{
					link.l1 = "开始吧。";
					link.l1.go = "ClockTower_OfficeServices_changeTrait_upgradeShip";
				}
				link.l2 = "不过……下次再说吧。";
				link.l2.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "QuestSP")
			{
				dialog.text = "抱歉，这是不可能的。您的船是一件独一无二的珍品，充满传奇色彩。画笔无力改变这一点。";
				link.l1 = "明白，谢谢。";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
			else
			{
				dialog.text = "您指的是什么专业化？您的船只通用型，并没有特殊属性。";
				link.l1 = "知道了，谢谢。";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_changeTrait_upgradeShip":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			NextDiag.CurrentNode = "ClockTower_OfficeServices";
			DialogExit();
			LaunchChangeShipTraitScreen(sld);
		break;

		// Страховка
		case "ClockTower_OfficeServices_Insurance":
			n = GetInsuranceCost();
			dialog.text = "让我看看……这将花费**#цена**杜布隆。";
			if (PCharDublonsTotal() > n)
			{
				link.l1 = "开始吧。";
				link.l1.go = "ClockTower_OfficeServices_Insurance_done";
			}
			link.l2 = "不过……下次再说吧。";
			link.l2.go = "ClockTower_OfficeServices_exit";
		break;

		case "ClockTower_OfficeServices_Insurance_done":
			pchar.questTemp.ShipInsurance = true;
			RemoveDublonsFromPCharTotal(GetInsuranceCost());
			dialog.text = "完成。";
			link.l1 = "谢谢。";
			link.l1.go = "ClockTower_OfficeServices_exit";
			Achievment_Set("ach_CL_199");
		break;
		
		case "ClockTower_OfficeServices_logbook":
			dialog.text = "完全正确。奖励取决于日志的数量以及其主人的相对危险程度。\n" +
						  "您带来了多少本日志？";
			link.l1 = "" + ClockTower_JournalsQty();
			link.l1.go = "ClockTower_OfficeServices_logbook_1";
		break;

		case "ClockTower_OfficeServices_logbook_1":
			dialog.text = "公司感谢您的工作。您应得**#количество**杜布隆。请收下并在这里签名。";
			link.l1 = "谢谢。";
			link.l1.go = "ClockTower_OfficeServices_exit";
			npchar.last_logbook_date = LastSpeakDate();
			Achievment_Set("ach_CL_199");
		break;

		case "ClockTower_OfficeServices_exit":
			DialogExit();
			NextDiag.CurrentNode = "ClockTower_OfficeServices";
		break;

		case "ClockTower_cabinFight":
			QuestAboardCabinDialogExitWithBattle("");
			DialogExit();
			ClockTower_CabinFight2();
		break;
		
		case "ClockTower_cabinPeace":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_cabinPeace");
		break;
	}
}

void ClockTower_NoShipInPort(ref link)
{
	dialog.text = "我没看到你的船在港口。";
	link.l1 = "那么下次再说吧。";
	link.l1.go = "ClockTower_OfficeServices_exit";
}

int ClockTower_PlaySound_rh2(string name)
{
    float x = stf(loadedLocation.locators.reload.houseO2.x);
    float y = stf(loadedLocation.locators.reload.houseO2.y);
    float z = stf(loadedLocation.locators.reload.houseO2.z);
    return SendMessage(Sound, "lslfff", MSG_SOUND_EVENT_PLAY, name, 0, x, y, z);
}

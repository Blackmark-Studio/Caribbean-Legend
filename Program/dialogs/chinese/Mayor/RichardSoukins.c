// 波多黎各的苏金
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		// ---------------------------------—— 首次对话 - 初次见面
		case "First time":
            dialog.text = "你找我有事吗? 没有的话就滚出去! ";
			link.l1 = "我这就走。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";


					if (npchar.city == sti(pchar.HeroParam.Location))
					{
						if(!CheckAttribute(PChar, "questTemp.pirateStartQuest"))
						{
							link.l2 = "你有什么工作给我吗? ";
							link.l2.go = "pirateStartQuest";
						}
						else
						{
							if(pchar.questTemp.pirateStartQuest == "3" && !CheckAttribute(PChar, "questTemp.pirateStartQuest.many"))
							{
								link.l2 = "我找到了线索, 但需要一些钱 --3万比索来把那只老鼠从洞里引出来。 ";
								link.l2.go = "pirateStartQuest_many";	
							}
							if(pchar.questTemp.pirateStartQuest == "3" && GetCharacterItem(pchar, "letter_open") > 0)
							{
								link.l2 = "给, 看看这封我在走私者尸体上找到的信。 ";
								link.l2.go = "pirateStartQuest_info_1";	
							}
							if(pchar.questTemp.pirateStartQuest == "5")
							{
								link.l2 = "搞定了。 诺曼.维戈和他的船都喂了海怪。 ";
								link.l2.go = "pirateStartQuest_final";	
							}
						}
					}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		//标题。 初始海盗任务 ===================================
		case "pirateStartQuest":
			dialog.text = "嗯... 工作, 你说? 其实你问我正好。 我需要一个外面的人。 我想在附近的镇上打听点事, 但我的人在那里很出名。 不能保证给你很多, 但你会得到一些报酬。 ";
			link.l1 = "好! 什么任务? ";
			link.l1.go = "pirateStartQuest_1";
			link.l2 = "抱歉, 但我不会为了一点小钱去冒险。 再见。 ";
			link.l2.go = "exit";
			pchar.questTemp.pirateStartQuest = "0";
		break;
		case "pirateStartQuest_1":
			dialog.text = "那你听着, 一个月前我和‘圣蓝号’纵帆船的船长做了一笔交易, 要运送200个奴隶。 我想把他们卖给当地的种植园主。 时间过去了, 客户开始担心, 但昨天有人告诉我说在岛附近看到了那艘纵帆船。 但是! 船长没有出现。 今天, 我的客户要求我退还预付款, 还说有人向他提议从另一个卖家那里买奴隶。 更贵, 但能一次性买到全部奴隶。 ";
			link.l1 = "然后呢? 我得在几天内找到200个奴隶, 帮你保住预付款? 就为了一点钱? ";
			link.l1.go = "pirateStartQuest_2";
		break;
		case "pirateStartQuest_2":
			dialog.text = "当然不是。 我看起来像个傻瓜吗? 反正我是不会还他预付款的。 但我需要证明卖给他的那些奴隶是我的。 找到跟他做新交易的人, 你就能得到1万比索。 成交? ";
			link.l1 = "我干。 你有怀疑对象吗? 可能是谁干的? ";
			link.l1.go = "pirateStartQuest_3";
			link.l2 = "没门。 找别人吧。 就给1万? 抱歉, 不行。 ";
			link.l2.go = "exit";
		break;
		case "pirateStartQuest_3":
			dialog.text = "如果我有线索, 就不会用你的服务了。 那些人早就死了。 但我很想知道他们是怎么知道‘圣蓝号’的货物和我的客户的。 看起来他们很容易就知道了。 明白了吗? ";
			link.l1 = "是的, 有人出卖了你。 ";
			link.l1.go = "pirateStartQuest_4";

			pchar.questTemp.pirateStartQuest = "1";
			pchar.questTemp.pirateStartQuest.City = npchar.city;
			pchar.questTemp.pirateStartQuest.Areal = GetArealByCityName(pchar.questTemp.pirateStartQuest.City);
			pchar.questTemp.pirateStartQuest.Name = GetFullName(npchar);

			AddQuestRecord("pSQ", "1");
			AddQuestUserData("pSQ", "sCity", XI_ConvertString("Colony" + pchar.questTemp.pirateStartQuest.City + "Gen"));
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);
		break;
		case "pirateStartQuest_4":
			dialog.text = "没错! 我在找他。 杀死我的竞争对手和夺回我的奴隶不是你的首要任务。 我需要那只老鼠, 说实话, 我想要他的脑袋插在烤肉叉上。 现在明白了吧, 为什么我的人不应该知道你任务的任何事情? 在找到泄密者之前, 我会怀疑每个人。 而我真的不想那样... ";
			link.l1 = "我明白。 那我会保持低调。 我这就去。 ";
			link.l1.go = "exit";
		break;

		case "pirateStartQuest_many":
			dialog.text = "你说三万? 那可是一大笔钱... 我现在只能给你5000比索, 这是我所有的钱了。 别想着拿了钱就跑, 否则我会找到你, 把你挂在最近的篱笆上! 明白了吗? ";
			link.l1 = "好吧, 那就给我五千... ";
			link.l1.go = "pirateStartQuest_many_1";
		break;
		case "pirateStartQuest_many_1":
			dialog.text = "拿着。 我等着你的调查结果。 ";
			link.l1 = "一切都会顺利的。 ";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 5000);
			pchar.questTemp.pirateStartQuest.many = "";
		break;

		//------------------------------------
		case "pirateStartQuest_info_1":
			dialog.text = "哈! 好消息! 我就知道你能行。 我得到了一些有趣的信息。 ";
			link.l1 = "我完成了工作, 我想要我的一万比索。 ";
			link.l1.go = "pirateStartQuest_info_2";
			TakeItemFromCharacter(pchar, "letter_open");
		break;
		case "pirateStartQuest_info_2":
			dialog.text = "当然, 这是你的报酬。 但别跑, 我还有一个任务给你。 \n法伊弗是诺曼.维戈的‘塞普提玛号’小帆船的船员。 我确定诺曼.维戈就是那只老鼠, 即使他是我们的人。 最近有人在岛附近的水域看到过他。 你的任务是把这只老鼠喂海怪。 你第一次没让我失望, 所以我想让你也处理这件事。 我会付你1.5万比索。 成交? ";
			link.l1 = "包在我身上! 就当叛徒诺曼.维戈已经死了。 ";
			link.l1.go = "pirateStartQuest_info_3";
			link.l2 = "你知道吗, 我不想参与这件事... 反正我也没时间。 抱歉, 我得走了。 ";
			link.l2.go = "pirateStartQuest_info_noex";
			AddMoneyToCharacter(pchar, 10000);
		break;
		case "pirateStartQuest_info_noex":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
		break;
		case "pirateStartQuest_info_3":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "4";

			AddQuestRecord("pSQ", "7");
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);

			pchar.quest.zpq_seaBattle.win_condition.l1 = "location";
			pchar.quest.zpq_seaBattle.win_condition.l1.location = pchar.questTemp.pirateStartQuest.Areal;
			pchar.quest.zpq_seaBattle.function = "pirateStartQuest_seaBattle";
		break;

		case "pirateStartQuest_final":
			dialog.text = "我知道, 我知道。 我的人一直在观察战斗, 已经报告了你的完美胜利。 很好, 你做得很好。 这是我答应你的1.5万比索。 谢谢你, 你帮了我大忙。 ";
			link.l1 = "没关系, 我很乐意帮忙! 但我现在得走了, 我在这里待太久了, 还有很多事情要做。 再见! ";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
			group_DeleteGroup("pirateStartQuest_Smuggler_group");
		break;


	}
}
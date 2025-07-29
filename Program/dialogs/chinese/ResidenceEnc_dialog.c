void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, arRld, arDis;
	int i, Qty;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//------------------------------- —官邸中的夫人 ---------------------------------
		case "ResWoman":
			NextDiag.TempNode = "ResWoman";
			if (LAi_grp_playeralarm <= 0 && CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2.Done") && !CheckAttribute(npchar, "quest.chickengod") && sti(npchar.nation) == SPAIN) {
				link.chickengod = "夫人, 请原谅, 但有人让我告诉您, 您有... 一个在古老异教金字塔内的约会。 ";
				link.chickengod.go = "chickengod";
			}
			if (isBadReputation(pchar, 30))
			{
				dialog.text = LinkRandPhrase("天哪! 我房间里怎么会有这种卑鄙小人! 滚出去, 不然我叫卫兵了! ", "这怎么可能... 谁让这只老鼠进来的? 滚出去你这混蛋! 你不该来这! 快走! ", "真是世风日下, 老鼠都跑进我卧室了! 滚出去! ");
				link.l1 = RandPhraseSimple("冷静点... ", "说话注意点... ");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("你在我卧室里做什么? 快滚出去! ", "真丢人! 我请你立刻离开这里! ", "抱歉, 先生, 您未被邀请。 请离开我的房间! ");
				link.l1 = RandPhraseSimple("抱歉... 我这就走。 ", "对不起, 走错门了, 我得走了。 ");
				link.l1.go = "exit";
			}
		break;
		case "Woman_FackYou":
			dialog.text = "哦, 那是什么? ! 我真是个傻瓜! 到处走, 什么都没看见... 卫兵!!! ";
			link.l1 = "闭嘴! ";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		//------------------------------- —官邸中的仆人 ---------------------------------
		case "ResMan":
			NextDiag.TempNode = "ResMan";
			if (isBadReputation(pchar, 30))
			{
				dialog.text = LinkRandPhrase("滚出去, 老鼠! ", "立刻从总督的庄园滚出去, 老鼠! ", "我不管你在" + XI_ConvertString("Colony" + npchar.city + "Gen") + "总督的家里做什么, 但我的建议是现在就滚! ");
				link.l1 = RandPhraseSimple("冷静点, 伙计... ", "注意你的言辞! ");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("您好! 我是总督的仆人, 我叫" + GetFullName(NPChar) + "。 ", "我负责看管这里, " + GetAddress_Form(NPChar) + "。 ", "你知道吗, " + GetAddress_Form(NPChar) + ", 我们的总督是个好人, 给我们的薪水也很丰厚... ");
				link.l1 = RandPhraseSimple("不错。 ", "嗯, 很好... ");
				link.l1.go = "exit";
			}
		break;
		case "Man_FackYou":
			dialog.text = "所以你决定抢劫总督? ! 卫兵, 抓小偷!! ";
			link.l1 = "闭嘴! ";
			link.l1.go = "fight";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		//------------------------------- —官邸中的士兵 ---------------------------------
		case "ResGuard":
			NextDiag.TempNode = "ResGuard";
			if (isBadReputation(pchar, 30))
			{
				dialog.text = LinkRandPhrase("你最好离开这里, " + GetSexPhrase("伙计","姑娘") + "... ", "走开! ", "走错门了吧, " + GetSexPhrase("伙计","姑娘") + "? 这里是" + XI_ConvertString("Colony" + npchar.city + "Gen") + "总督的庄园。 ");
				link.l1 = RandPhraseSimple("我想走的时候自然会走! ", "这不关你的事... ");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("今天我被派到这里执勤, 这地方不错... ", "我负责保护" + GetAddress_Form(NPChar) + "的庄园。 ", "我的任务是保护总督的庄园。 ");
				link.l1 = RandPhraseSimple("那祝你好运... ", "嗯, 我知道了... ");
				link.l1.go = "exit";
			}
		break;
		
		case "chickengod":
			pchar.questTemp.ChickenGod.Tasks.o2.Counter = sti(pchar.questTemp.ChickenGod.Tasks.o2.Counter) + 1;
			if (sti(pchar.questTemp.ChickenGod.Tasks.o2.Counter) >= 3) {
				dialog.text = "啊, 对了! 终于! 我准备好跟你走了, 船长。 ";
				link.l1 = "就这样? 夫人, 你确定这是你想要的吗? ";
				link.l1.go = "chickengod_accept";
			} else {
				sld = CharacterFromID(npchar.city + "_Mayor");
				dialog.text = "什么? ! 你喝醉了吗, 先生? 这笑话太愚蠢了! 请走开, 我求你了! " + sld.name + "! 卫兵! 救命! ";
				link.l1 = "该死, 该走了。 ";
				link.l1.go = "chickengod_decline";
			}
			npchar.quest.chickengod = true;
		break;
		
		case "chickengod_accept":
			dialog.text = "嗯, 当然! 啊, 我和阿鲁巴先生已经通信很久了! ";
			link.l1 = "既然如此, 请上船吧! ";
			link.l1.go = "chickengod_accept_take";
			link.l2 = "不, 夫人, 这不行。 我的荣誉不允许让女人置身险境, 而且你显然被误导了! ";
			link.l2.go = "chickengod_accept_nottake";
		break;
		
		case "chickengod_accept_take":
			DialogExit();
			
			pchar.questTemp.ChickenGod.Tasks.o2.Done = true;
			pchar.questTemp.ChickenGod.Tasks.o2.Lady = npchar.id;
			AddDialogExitQuestFunction("ChickenGod_TakeLady");
		break;
		
		case "chickengod_accept_nottake":
			dialog.text = "既然如此, 我亲爱的船长, 带着你那乡巴佬的荣誉感滚吧! 我会等另一个信使, 找个不像你这么狭隘的人! ";
			link.l1 = "真迷人! ";
			link.l1.go = "exit";
			
			pchar.questTemp.ChickenGod.Tasks.o2.Done = true;
			SetFunctionTimerCondition("ChickenGod_NotTakeLadyConsequence", 0, 1, 0, false);
		break;
		
		case "chickengod_decline":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_LadyRefuse");
		break;
		
	}
}
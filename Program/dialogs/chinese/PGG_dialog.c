#include "DIALOGS\%language%\Common_Duel.c"

#define MAX_PGG_STORIES 		9
#define MAX_PGG_QUEST_STORIES 	3
#define MAX_PGG_MEET_REP 		5

string PGG_Stories[MAX_PGG_STORIES] = {
"... 只有魔鬼和我知道地点, 最后站着的人将拿走一切!\n",
"... 梅纳德说:'我不指望仁慈, 所以你也不应该指望.'\n",
"... 他喝得酩酊大醉, 提议就在那里安排一个特别的地狱, 看看我们中谁能坚持更久。 \n",
"... 我波尔图贝洛的老朋友的有趣故事... \n",
"... 不, 先生们, 那些是蹩脚的轶事。 我有一些好故事可以让你们听个够\n",
"... 我不能多说'飞翔的荷兰人'。 从未见过。 有一次我登上了一艘奇怪的双桅帆船, 空无一人。 你猜怎么着? 货舱里有1700桶美酒! ... 这就是我所说的运气! \n",
"... 我倾向于认为'飞翔的荷兰人'之类的鬼话是假的\n",
"... 听说过我在基韦斯特被震晕的事吗? 虽然没有明显的损伤, 但我躺了两个月。 然后我的良知说服我去忏悔。 他们说, 在上帝的帮助下, 事情会好起来的... 好吧, 我去了, 神父问:'我的孩子, 你杀了很多人吗?''沉了多少艘船?'-'很多'- 我回答。 他不罢休:'你勾引了很多妻子吗?'然后我说:'神父, 我不是来这里吹嘘的.'哈哈哈\n",
"... 但在圣克鲁斯有一次停泊时发生了一件事。 随着一声'小心!'我的水手甩出鞭子, 直接打在当地旁观者的额头上! 那人尖叫着失去知觉倒下。 水手吓坏了, 没等跳板就跳到码头上, 给那个可怜的家伙喂了些水。 最后他醒了过来, 对水手说:'危险来临时你应该喊'注意', 而不是'小心', 你这个白痴!'哈哈哈! " 
};

string PGG_QuestStories[MAX_PGG_QUEST_STORIES] = {
"... 有一次被困在佛罗里达... ",
"... 我不能多说'飞翔的荷兰人'。 从未见过。 有一次我登上了一艘奇怪的双桅帆船, 空无一人。 你猜怎么着? 货舱里有1700桶美酒! ... 这就是我所说的运气! ... ",
"... 她在酒馆中央杀了那个可怜的混蛋, 因为他建议上楼测试她的'军官技能'... "
}

string PGG_Meet_GoodRep[MAX_PGG_MEET_REP] = {
"在这些水域, 正派的船长是稀有品种。 ",
"如今贵族已经过时了。 ",
"哦, 现在有一位正派的船长, 一点也不像你们这些恶棍! 嘿嘿! ",
"先生们, 我们桌上有一位正派的船长, 他经历过无数次战火。 那么, 尊敬的船长, 你能告诉我们什么? ",
"现在又来了一位光荣的海盗, 他不习惯走皇家道路。 " 
};

string PGG_Meet_BadRep[MAX_PGG_MEET_REP] = {
"现在又来了一个海盗! ",
"先生们, 我猜我们桌上有一位幸运的绅士? ",
"我闻到了火药和血腥味! 一名海盗在船上! ",
"哦, 先生们, 这是一位经验丰富的海盗, 他肯定会在美酒陪伴下讲些故事... 你想加入我们吗? ",
"哦, 我闻到了火药味... 先生们, 现在我们这里又来了一位光荣的海盗, 他肯定会在忏悔时讲很多故事... 哈哈哈! ",
};

void ProcessDialogEvent()
{
	int i, n;
	int iRnd = -1;
	int iAns;
	bool bOk;
   	float locx, locy, locz;
	string sTmp, sLoc;
	ref NPChar, sld;
	aref link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    ProcessDuelDialog(NPChar, link, NextDiag);

	if (Dialog.CurrentNode == "First time" && CheckAttribute(NPChar, "meeting")) Dialog.CurrentNode = "Second time";
	switch(Dialog.CurrentNode)
	{
	//Dialog.Text = "Вы видитe баг... сообщитe о нём АТ, для Navy.";
	//link.l1 = "Certainly!";
	//link.l1.go = "exit.";
	case "First time":
		if (CheckAttribute(NPChar, "PGGAi.location.town.back") && CheckAttribute(pchar, "questTemp.PGGContra.Know"))
		{
			Dialog.text = "嘿, 滚开, 听见没有! 如果你毁了我的交易, 我会把你的心挖出来! ";
			link.l1 = RandPhraseSimple("你敢威胁我, 杂种? ! ", "我会让你噎住自己的话, 恶棍! ");
			link.l1.go = "Exit_Smugglers_Fight";
			link.l2 = "哦, 我明白了。 生意就是生意。 祝你好运。 ";
			link.l2.go = "Exit";
			break;
		}
		//Dialog.Text = "Good afternoon, my name is " + GetFullName(NPChar) + ", and yours?";
		if(rand(10) == 3)
		{
			iRnd = rand(MAX_PGG_QUEST_STORIES - 1);
			Dialog.Text = PGG_QuestStories[iRnd];
		}
		else
		{
			iRnd = rand(MAX_PGG_STORIES - 1);
			iAns = rand(MAX_PGG_MEET_REP - 1);
			Dialog.Text = PGG_Stories[iRnd] + PCharRepPhrase(PGG_Meet_GoodRep[iAns], PGG_Meet_BadRep[iAns]);
		}		 
		//link.l1 = "My name is " +GetFullName(pchar)+ ".";
		link.l1 = PCharRepPhrase(RandSwear() + RandPhraseSimple("请大家喝酒! 我是" +GetFullName(pchar)+ "船长。 ", 
					"我是'" + PChar.Ship.Name + "'号和几百个真正魔鬼的船长! 嘿嘿! 我叫" +GetFullName(pchar)+ "。 "), 
				RandPhraseSimple("请允许我介绍自己, 先生们。 我是" +GetFullName(pchar)+ "船长。 ", 
					"我们还没有介绍过。 我是'" + PChar.Ship.Name + "'号在" + NationNameGenitive(sti(PChar.nation)) + "旗下的船长。 我叫" +GetFullName(pchar)+ "。 "));
		link.l1.go = "Meeting";
		break;

	case "Meeting":
		Dialog.Text = "嗯, 这里的每个人都认识我! 我是" + GetFullName(NPChar) + "。 很高兴见到你! 我能为你做什么? ";
		link.l1 = RandPhraseSimple("我和你有生意! ", "我想和你谈谈... ");
		link.l1.go = "quest";
		if (sti(pchar.Ship.Type) != SHIP_NOTUSED && sti(NPChar.Ship.Type) != SHIP_NOTUSED)
		{
			sld = GetRealShip(sti(NPChar.Ship.Type));
			
			Dialog.Text = "嗯, 这里的每个人都认识我! 我是" + GetFullName(NPChar) + ", " + xiStr(sld.BaseName + "Acc") + " " + NPChar.Ship.Name + "号船长。 ";
			link.l2 = "你加入我怎么样? 两艘船总比一艘好。 我们可以一起做正经生意。 ";
			link.l2.go = "companion";
		}
		if (sti(NPChar.Ship.Type) == SHIP_NOTUSED)
		{
			link.l3 = RandPhraseSimple("你想在我的船上当军官吗? ", "我觉得你在我的船上当军官会做得很好。 你觉得呢? ");
			link.l3.go = "officer";
		}
		if (bBettaTestMode)
		{
			link.l7 = "(测试版) 任务。 ";
			link.l7.go = "BT_Quest";
			link.l8 = "(测试版) 决斗。 ";
			link.l8.go = "outraged";
		}
		link.l9 = "没什么。 ";
		link.l9.go = "exit";
		NextDiag.TempNode = "Second time";
		NPChar.meeting = true;
		break;

	case "Second time":
		if (CheckAttribute(NPChar, "PGGAi.location.town.back") && CheckAttribute(pchar, "questTemp.PGGContra.Know"))
		{
			Dialog.text = "嘿, 滚开, 听见没有! 如果你毁了我的交易, 我会把你的心挖出来! ";
			link.l1 = RandPhraseSimple("你敢威胁我, 杂种? ! ", "我会让你噎住自己的话, 恶棍! ");
			link.l1.go = "Exit_Smugglers_Fight";
			link.l2 = "哦, 我明白了。 生意就是生意。 祝你好运。 ";
			link.l2.go = "Exit";
			break;
		}

		if (CheckAttribute(NPChar, "QuestTalk") && GetNpcQuestPastDayParam(NPChar, "QuestTalk") < 1)
		{
			Dialog.Text = "我今天已经把一切都告诉你了! ";
			link.l1 = "哦, 是吗... ";
			link.l1.go = "exit";
			break;
		}

		Dialog.text = RandPhraseSimple(GetFullName(pchar) + ", 你需要什么? ", "那是谁? 哦, 是你... 滚开, 我没心情... ");
		link.l1 = RandPhraseSimple("生意怎么样? ", "我想和你谈谈... ");
		link.l1.go = "quest";

		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) > 49)
		{
//			Dialog.Text = RandPhraseSimple("Oh, look who's here! It's " + GetFullName(pchar) + "。 Any news?", "How are you doing? What can I do for you?");
			if(rand(10) == 3)
			{
				iRnd = rand(MAX_PGG_QUEST_STORIES - 1);
				Dialog.Text = PGG_QuestStories[iRnd] + PCharRepPhrase(" 有什么消息? ", " 群岛上有什么消息? ");
			}
			else
			{
				iRnd = rand(MAX_PGG_STORIES - 1);
				iAns = rand(MAX_PGG_MEET_REP - 1);
				Dialog.Text = PGG_Stories[iRnd] + PCharRepPhrase(PGG_Meet_GoodRep[iAns] + " 有什么消息? ", PGG_Meet_BadRep[iAns] + " 群岛上有什么消息? ");
			}		
			if (sti(pchar.Ship.Type) != SHIP_NOTUSED && sti(NPChar.Ship.Type) != SHIP_NOTUSED)
			{
				link.l2 = RandPhraseSimple("你加入我怎么样? 两艘船总比一艘好。 我们可以一起做正经生意。 ", "你看起来像个经验丰富的船长。 想在我的旗下航行吗? ");
				link.l2.go = "companion";
			}
			if (sti(NPChar.Ship.Type) == SHIP_NOTUSED)
			{
				Dialog.Text = RandPhraseSimple("哦, 我真倒霉... 我的船沉了! ", "看谁来了? ! 什么风把你吹来了? 顺便说一句, 我的船丢了... ");
				link.l3 = RandPhraseSimple("真遗憾。 也许下次你会有更好的运气。 ", "你不说... 好吧, 我该走了。 再见。 ");
				link.l3.go = "exit";
				if (FindFreeRandomOfficer() > 0)
				{
					link.l3 = RandPhraseSimple("你想在我的船上当军官吗? ", "我觉得你在我的船上当军官会做得很好。 你觉得呢? ");
					link.l3.go = "officer";
				}
			}
//			link.l4 = "What's the news?";
//			link.l4.go = "rumours_capitan";
		}
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 20 || bBettaTestMode)
		{
			link.l8 = PCharRepPhrase("多么丑陋的鼻子。 简直欠揍。 ", "哦, 我们的'朋友'。 你想在胸口添几个新洞吗? ");
			link.l8.go = "outraged";
		}
		link.l9 = "没什么。 ";
		link.l9.go = "exit";
		NextDiag.TempNode = "Second time";
		break;

	case "no_ship":
		break;

//==================================================
// 军官 
//==================================================
	case "officer":
		//每天一次
		if (CheckAttribute(NPChar, "Officer_Talk") && GetNpcQuestPastDayParam(NPChar, "Officer_Talk") < 1 && !bPGGLogShow)
		{
			Dialog.Text = RandPhraseSimple("我已经告诉过你我不感兴趣。 ", "我以为我们已经讨论过所有事情了。 ");
			link.l1 = RandPhraseSimple("我怎么会忘记? ", "好吧。 再见。 ");
			link.l1.go = "exit";
			break;
		}
		//如果已经是军官, 就拒绝
		if (CheckAttribute(NPChar, "PGGAi.Officer"))
		{
			Dialog.Text = RandPhraseSimple("嗯... 也许不。 不会有第二次了。 ", "你以为我会两次上钩吗? ! ");
			link.l1 = RandPhraseSimple("好吧, 如你所愿... ", "好吧。 那再见。 ");
			link.l1.go = "exit";
			break;
		}
		//如果关系低于70, 70%的概率会拒绝
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 70 && rand(100) < 70)
		{
			Dialog.Text = RandPhraseSimple("嗯... 不, 我想不会。 ", "不, 我是船长, 我不想当军官。 ");
			link.l1 = RandPhraseSimple("好吧, 如你所愿... ", "好吧。 那再见。 ");
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(NPChar, "Officer_Talk");
			break;
		}
		//检查海盗, 没有! :) //navy 04.04.07
		if (FindFreeRandomOfficer() < 1)
		{
			Dialog.Text = RandPhraseSimple("你已经满员了。 ", "我认为你还没准备好给我下命令。 ");
			link.l1 = RandPhraseSimple("可惜... ", "好吧, 命运另有安排。 ");
			link.l1.go = "exit";
			break;
		}
		if (!CheckAttribute(NPChar, "Quest.Officer.Price"))
		{
			NPChar.Quest.Officer.Price = 10000 + sti(NPChar.rank)*500*MOD_SKILL_ENEMY_RATE - MakeInt(GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE)*1000);
		}
		Dialog.Text = NPCharRepPhrase(NPChar, RandSwear() + 
				RandPhraseSimple("这正是我需要的! 我们的刀刃将品尝敌人的鲜血! 但有一个问题 - 我还需要" + NPChar.Quest.Officer.Price + "比索来偿还债务。 ", 
								"你看起来像个真正的老手。 如果你愿意支付" + NPChar.Quest.Officer.Price + "比索, 我们可能会合作得很好。 "), 
				LinkRandPhrase("你的提议让我相当受宠若惊。 我同意为你工作, 收取相当适度的" + NPChar.Quest.Officer.Price + "比索费用。 ", 
							"嗯... 你看起来像个经验丰富的水手。 也许, 如果您愿意支付我" + NPChar.Quest.Officer.Price + "比索, 我应该接受您的提议。 ", 
							"我认为我们会合作得很好, 船长。 只要" + NPChar.Quest.Officer.Price + "比索, 你就有了一个交易。 "));

		MakeRandomLinkOrderTwo(link, PCharRepPhrase(RandSwear() + RandPhraseSimple("这很适合我。 我只希望你不会每天都收费。 ", "这很贵, 但我希望你物有所值。 "), 
				LinkRandPhrase("我同意。 认为自己是船员的一部分。 ", "嗯... 我想我能负担得起。 ", "看起来你值得。 拿硬币! ")), "officer_hired",
									PCharRepPhrase(RandSwear() + RandPhraseSimple("你不值那么多。 再见... ", "对我来说太贵了。 "), 
				LinkRandPhrase("是的... 贪婪不是罪... ", "你在嘲笑我吗? 我可以用这些钱买一打像你这样的人。 ", "这是敲竹杠。 我该去哪里找这么多钱? ")), "exit");
		link.l3 = "嗯... 你到底有多合格? ";
		link.l3.go = "Exit_ShowParam";
		break;

	case "officer_hired":
		if (sti(pchar.money) < sti(NPChar.Quest.Officer.Price))
		{
			Dialog.Text = "我认为你现金有问题, 船长。 ";
			link.l1 = "哦... 确实。 ";
			link.l1.go = "exit";
			break;
		}
		pchar.questTemp.HiringOfficerIDX = NPChar.index;
		AddMoneyToCharacter(pchar, -(makeint(NPChar.Quest.Officer.Price)));
		AddDialogExitQuestFunction("PGG_BecomeHiredOfficer");
		NPChar.loyality = MakeInt(PGG_ChangeRelation2MainCharacter(NPChar, 0)*0.3)

		DeleteAttribute(NPChar, "Quest.Officer");
		DeleteAttribute(NPChar, "PGGAi.Task");
		DeleteAttribute(NPChar, "PGGAi.LockService");

		Dialog.Text = RandPhraseSimple("优秀! ", "我从不怀疑你, 船长。 ");
		link.l1 = "出发不要迟到。 ";
		link.l1.go = "exit";
		break;

//==================================================
// 同伴 
//==================================================
	case "companion":
		Dialog.Text = "发现一个漏洞, 通知开发人员";
		link.l1 = "我会的! ";
		link.l1.go = "exit";
		//每天一次
		if (CheckAttribute(NPChar, "Companion_Talk") && GetNpcQuestPastDayParam(NPChar, "Companion_Talk") < 1 && !bPGGLogShow)
		{
			Dialog.Text = RandPhraseSimple("我已经告诉过你我不感兴趣。 ", "我以为我们已经讨论过所有事情了。 ");
			link.l1 = RandPhraseSimple("我怎么会忘记? ", "好吧。 再见。 ");
			link.l1.go = "exit";
			break;
		}
		//船级差一级... 不白给
		if (GetCharacterShipClass(NPChar) < GetCharacterShipClass(PChar)-1)
		{
			Dialog.Text = RandPhraseSimple("和你一起航行? ! 先长大一点! ", "我想我对此不感兴趣! ");
			link.l1 = RandPhraseSimple("好吧, 如你所愿... ", "好吧。 那再见。 ");
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(NPChar, "Companion_Talk");
			break;
		}
		//如果关系低于70, 70%的概率会拒绝
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 70 && rand(100) < 70)
		{
			Dialog.Text = RandPhraseSimple("嗯... 不, 我想不会。 ", "不, 谢谢。 我不喜欢在任何人手下服务。 ");
			link.l1 = RandPhraseSimple("好吧, 如你所愿... ", "好吧。 那再见。 ");
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(NPChar, "Companion_Talk");
			break;
		}
		//有同伴的位置吗
		if (SetCompanionIndex(pchar, -1, sti(NPChar.index)) != -1)
		{
			Dialog.Text = NPCharRepPhrase(NPChar, RandSwear() + 
					RandPhraseSimple("我喜欢你! 你有了一个交易! 我已经能听到我们口袋里比索的叮当声了! ", "你是个聪明的" + GetSexPhrase("家伙","姑娘") + "... 我们应该合作得很好! "), 
					LinkRandPhrase("我喜欢你的提议。 我同意。 ", 
					"那很有趣。 你知道, 我认为我们在一起可以做更多事情! ", "那应该很有趣。 你有了一个交易! "));
			link.l1 = RandPhraseSimple("太好了! 我会在海上等你! ", "成交! 我们会成为一个伟大的船员。 ");
			link.l1.go = "exit";
			NPChar.PGGAi.IsPGG = false;
			NPChar.PGGAi.location.town = "none";
			NPChar.Dialog.TempNode = "hired";
			NPChar.Dialog.FileName = "Enc_Officer_dialog.c";
            NPChar.Payment = true;
            NPChar.Money   = 0;
            
            SetBaseShipData(NPChar);
            DeleteAttribute(NPChar,"ship.sails");
			DeleteAttribute(NPChar,"ship.masts");
			DeleteAttribute(NPChar,"ship.blots");
			DeleteAttribute(NPChar,"ship.hulls");
			
			Fantom_SetCannons(NPChar, "pirate");
			Fantom_SetBalls(NPChar, "pirate");
    
			DeleteAttribute(NPChar, "PGGAi.Task");
			DeleteAttribute(NPChar, "PGGAi.LockService");
			SetCharacterRemovable(NPChar, true);
			SaveCurrentNpcQuestDateParam(NPChar, "Companion.CheckRelation");
		}
		else
		{
			Dialog.Text = RandPhraseSimple("我认为你已经有足够的同伴了。 ", "你已经有足够的船了 - 为什么还需要更多? ");
			link.l1 = "是啊... 也许你是对的。 ";
			link.l1.go = "exit";
		}
		break;

	case "companion_leave":
		Dialog.Text = RandSwear() + " " + NPCharRepPhrase(NPChar,
					RandPhraseSimple("我受够你了!!! 我要离开你的中队! ", "我的耐心用完了! 我要走了。 "), 
					RandPhraseSimple("我厌倦了你的冒险,'舰队司令'... 请允许我告辞。 ", "我受够了你的指挥, 我要离开你的中队。 "));
		link.l1 = PCharRepPhrase(RandPhraseSimple("好的, 那就滚吧。 ", "好吧, 你想去哪就去哪。 "),
					RandPhraseSimple("好的。 我不会挽留你。 ", "那是你的选择。 祝你一帆风顺。 "));
		link.l1.go = "Exit_Companion_Leave";
		link.l2 = PCharRepPhrase(RandPhraseSimple("呃... 加点奖金怎么样? ", "天啊! 哦, 见鬼, 也许你会留下来? 我甚至可以给你的船员多加点钱! "),
					RandPhraseSimple("我不想和你分手... 也许一点补偿可以解决我们的分歧? ", "增加你的工资怎么样? "));
		link.l2.go = "companion_stay";
		break;

	case "companion_stay":
		if (CheckAttribute(NPChar, "Quest.Companion"))
		{
			Dialog.Text = RandPhraseSimple("一次就够了。 我再也不会相信你的承诺了! ", "你不能用金钱诱惑我! 我的决定是最终的! ");
			link.l1 = RandPhraseSimple("好吧, 祝你好运。 ", "那就滚吧, 确保我再也见不到你! ");
			link.l1.go = "Exit_Companion_Leave";
			break;
		}
		NPChar.Quest.Companion.Price = 2*GetSalaryForShip(NPChar);
		Dialog.Text = RandSwear() + " " + NPCharRepPhrase(NPChar,
					RandPhraseSimple("奖金? 好的! " + NPChar.Quest.Companion.Price + "比索就够了。 ", 
						"好吧, 如果你准备给我的船员" + NPChar.Quest.Companion.Price + "比索, 我可以说服他们留下。 "), 
					RandPhraseSimple("好吧! 我可以留下一小笔" + NPChar.Quest.Companion.Price + "比索的奖金! ",
						NPChar.Quest.Companion.Price + "会让我和我的船员满意一段时间。 "));
		link.l1 = PCharRepPhrase(RandPhraseSimple("你在嘲笑我还是怎么了? ! 现在就滚! ", "哈! 我宁愿把这些钱花在更有用的东西上! "),
					RandPhraseSimple("哦不。 我没那么富有! ", "再见。 我不会付这么多。 "));
		link.l1.go = "Exit_Companion_Leave";
		if (sti(pchar.money) >= sti(NPChar.Quest.Companion.Price))
		{
			link.l2 = PCharRepPhrase(RandPhraseSimple("太好了! 这是你的奖金! ", "我从不怀疑, 这一切都是关于钱的! "),
					RandPhraseSimple("太好了! 很高兴你留下。 ", "这是我承诺的。 "));
			link.l2.go = "Exit_Companion_Stay";
		}
		break;

	case "Exit_Companion_Leave":
		chrDisableReloadToLocation = false;
		RemoveCharacterCompanion(pchar, NPChar);

		NPChar.PGGAi.IsPGG = true;
		NPChar.RebirthPhantom = true;
		NPChar.PGGAi.location.town = GetCurrentTown();

		LAi_SetWarriorTypeNoGroup(NPChar);
		NextDiag.CurrentNode = "Second Time";
		DialogExit();
		break;

	case "Exit_Companion_Stay":
        GetCharacterPos(NPChar, &locx, &locy, &locz);
        sTmp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
		LAi_ActorGoToLocation(NPChar, "reload", sTmp, "none", "", "", "", 5.0);

		AddMoneyToCharacter(pchar, -(makeint(NPChar.Quest.Companion.Price)));
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

//==================================================
// 任务
//==================================================
//==== 测试版 ====
	case "BT_Quest":
		Dialog.Text = "选择模板! ";
		link.l1 = "任务1模板 - 海上。 ";
		link.l1.go = "BT_Quest_1";
		link.l2 = "已选择! 任务1模板 - 陆地。 ";
		link.l2.go = "BT_Quest_2";
		break;

	case "BT_Quest_1":
		NPChar.PGGAi.ActiveQuest.QstNumber = 0;
		NPChar.PGGAi.ActiveQuest.QstNumber.Template = 1;
		Dialog.Text = "任务1模板 - 海上。 ";
		link.l1 = "哦, 是啊... ";
		link.l1.go = "quest";
		break;
	case "BT_Quest_2":
		NPChar.PGGAi.ActiveQuest.QstNumber = 0;
		NPChar.PGGAi.ActiveQuest.QstNumber.Template = 0;
		Dialog.Text = "已选择! 任务1模板 - 陆地。 ";
		link.l1 = "哦, 是啊... ";
		link.l1.go = "quest";
		break;
//==== 测试版 ====

	case "quest":
		chrDisableReloadToLocation = false;
		if (CheckAttribute(NPChar, "QuestTalk") && GetNpcQuestPastDayParam(NPChar, "QuestTalk") < 1)
		{
			Dialog.Text = "我已经把一切都告诉你了! ";
			link.l1 = "哦, 是啊... ";
			link.l1.go = "exit";
			break;
		}
		Dialog.Text = RandPhraseSimple("什么生意? .. 嗝! 你没看见吗 - 我和朋友们正玩得开心! .. 嗝... ",
									"呃... 今天没有生意! ");
		link.l1 = "我明白了... ";
		link.l1.go = "exit";
		if (!PGG_IsQuestAvaible()) break; //不能接受任务
		//if (!CheckAttribute(NPChar, "PGGAi.ActiveQuest") && !bBettaTestMode) break; //для рeлиза возможно надо будeт закрыть。 eсли закомeнтить, то ГГ сам можeт прeдложить дeло
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest.QstNumber")) iRnd = sti(NPChar.PGGAi.ActiveQuest.QstNumber); //тип квeста, который хочeт от нас ПГГ
		if (iRnd == -1 && !CheckAttribute(pchar, "GenQuest.PGG_Quest")) iRnd = rand(1); // можeт и нe быть
		switch (iRnd)
		{
		case 0:
			if (sti(NPChar.Ship.Type) != SHIP_NOTUSED && sti(PChar.Ship.Type) != SHIP_NOTUSED && GetCharacterShipClass(PChar) <= 4 && GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				//квeст от ПГГ
				/*if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
				{ */
				if (!CheckAttribute(pchar, "GenQuest.PGG_Quest"))
				{  // 不被其他PGG任务占用
					Dialog.Text = "谈什么? 不过, 你来得正是时候。 说到生意, 我总是准备好了! ";
					link.l1 = "嗯。 你在说什么? ";
					link.l1.go = "Quest_1_Work";
					NPChar.PGGAi.ActiveQuest = 1; // 让他用自己的名字说话
					PChar.GenQuest.PGG_Quest = 1; // 防止其他PGG打扰
				}
				/* }
				//квeст от ГГ
				else
				{
					if ()
					{
						Log_TestInfo("The test sentence of the protagonist");

						Dialog.Text = LinkRandPhrase("... only me and the devil know that place, and the last one to stay alive shall get everything!..", 
							 "... and Meinard replied:'I expect no quarter from you and will give you none, either'", 
							 "... and once in the open sea, when he was already a bit tipsy, he suggested:'Let's make hell for ourselves there and see who stands to the last'.") + 
							 PCharRepPhrase(LinkRandPhrase("Now there's another pirate!",
									"Gentlemen, we have a gentleman of fortune at our table, I guess?",
									"I smell gunpowder and blood! A filibuster astarboard!"), 
								LinkRandPhrase("Decent captains are rare breed in these waters.",
									"Nobility is out of fashion these days.",
									"Oh, now there's a decent captain, not like you at all, cutthroats! He-he!"));
						link.l1 = "I am not shouting, I am telling you - there's a profitable deal!";
						link.l1.go = "Quest_1_Work";
					}
				}  */
			}
			break;
		}
		SaveCurrentNpcQuestDateParam(NPChar, "QuestTalk");
		break;

	case "quest_onStay": // PGG自己靠近
		chrDisableReloadToLocation = false;
		Dialog.Text = "小心, 小心! 哦! 我认识你。 你是" +GetFullName(pchar)+ "。 我听说过很多关于你的事。 ";
		if (!CheckAttribute(NPChar, "meeting") || !sti(NPChar.meeting))
		{
			link.l1 = PCharRepPhrase(RandSwear() + RandPhraseSimple("我是" +GetFullName(pchar)+ "船长。 ", 
						"我是'" + PChar.Ship.Name + "和几百个真正魔鬼的船长! 嘿嘿! 我叫" +GetFullName(pchar)+ "。 ") + " 但我不记得你了。 ", 
					RandPhraseSimple("请允许我介绍自己, 先生们。 我是" +GetFullName(pchar)+ "船长。 ", 
						"我们还没有介绍过。 我是'" + PChar.Ship.Name + "在" + NationNameGenitive(sti(PChar.nation)) + "旗下的船长。 我叫" +GetFullName(pchar)+ "。 ") + " 但我不记得你了。 ");
			//link.l1 = "Hmm... and just who are you? I don't remember you.";
			link.l1.go = "Quest_1_Meeting";
		}
		else
		{
			link.l1 = "嗨, " + GetFullName(NPChar) + "。 生活怎么样? ";
			link.l1.go = "Quest_1_Work";
		}
		SaveCurrentNpcQuestDateParam(NPChar, "QuestTalk");
		break;

	//=========== 第一个任务 ==========
	case "Quest_1_Meeting":
		sld = GetRealShip(sti(NPChar.Ship.Type));
		Dialog.Text = "我是" + GetFullName(NPChar) + ", " + xiStr(sld.BaseName + "Acc") + " " + NPChar.Ship.Name + NPCharRepPhrase(NPChar, "。 整个西班牙海域最臭名昭著的海盗。 ", "。 只是个水手。 ");
		link.l1 = "是的, 现在我会记住你。 ";
		link.l1.go = "Quest_1_Work";
		NPChar.meeting = true;
		break;

	case "Quest_1_Work":
		PChar.GenQuest.PGG_Quest.Template = rand(1);
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest.QstNumber.Template"))
		{
			PChar.GenQuest.PGG_Quest.Template = NPChar.PGGAi.ActiveQuest.QstNumber.Template;
		}
		PChar.GenQuest.PGG_Quest.Parts = GetCompanionQuantity(PChar)+1;
		PChar.GenQuest.PGG_Quest.Nation = rand(NON_PIRATES);
		PChar.GenQuest.PGG_Quest.Island = GetRandIslandId();
		while(PChar.GenQuest.PGG_Quest.Island == Islands[GetCharacterCurrentIsland(pchar)].id)
		{
			PChar.GenQuest.PGG_Quest.Island = GetRandIslandId();
		}
		PChar.GenQuest.PGG_Quest.Island.Shore = GetIslandRandomShoreId(PChar.GenQuest.PGG_Quest.Island);
		while(PChar.GenQuest.PGG_Quest.Island.Shore == "")
		{
			PChar.GenQuest.PGG_Quest.Island = GetRandIslandId();
			PChar.GenQuest.PGG_Quest.Island.Shore = GetIslandRandomShoreId(PChar.GenQuest.PGG_Quest.Island);
			if (sti(PChar.GenQuest.PGG_Quest.Template)) 
			{
				if (!isLocationFreeForQuests(PChar.GenQuest.PGG_Quest.Island)) PChar.GenQuest.PGG_Quest.Island.Shore = "";
			}
			else
			{
				if (!isLocationFreeForQuests(PChar.GenQuest.PGG_Quest.Island.Shore)) PChar.GenQuest.PGG_Quest.Island.Shore = "";
			}
		}
		PChar.GenQuest.PGG_Quest.Island.Town = FindTownOnIsland(PChar.GenQuest.PGG_Quest.Island);
		PChar.GenQuest.PGG_Quest.Days = 3 + GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(pchar)].id, PChar.GenQuest.PGG_Quest.Island);
		PChar.GenQuest.PGG_Quest.Goods = GetRandomGood(FLAG_GOODS_TYPE_CROWN, FLAG_GOODS_NONE);
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
//			Dialog.Text = "I have business with you, "+ GetSexPhrase("mate","lass") +"。 I know that I can trust you, but I just can't discuss it at the tavern - too many wrong ears。 I'll be waiting for you on board of my ship。 The name of my old tub is'" + NPChar.Ship.Name + "'.";
//			link.l1 = "Spit it out now, I have no time for visits.";
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("我和你以及你的恶棍们有件有趣的事。 ", 
								"如果我们联手, 我们可能会赢得一个真正的大奖! 当然, 我们必须在此过程中杀个人。 嘿嘿。 "), 
							RandPhraseSimple("我有一个给你的商业提议, 船长。 ", 
							"船长, 你的声誉是无与伦比的, 因此我邀请你参与一个诱人的事情。 ")) + 
						RandPhraseSimple("就我们俩之间。 我们今天在'" + NPChar.Ship.Name + "'的会议室里讨论一下, 喝着最好的麦芽酒。 ", "我们不应该在那里讨论, 让我们在'" + NPChar.Ship.Name + "上安静地协商细节。 请不要太久。 ");
			link.l1 = PCharRepPhrase(RandSwear() + RandPhraseSimple("去他的拖延! 如果是好事, 我现在就想知道, 如果是坏事, 就更想知道了! ", 
								"没有必要这么简短! 酒馆里有一个合适的房间 - 我们去那里! "), 
							RandPhraseSimple("我们为什么不能现在就在酒馆的房间里讨论你的提议? ", 
								"我恐怕不太想去参观你的船。 如果你需要什么, 就在这里说出来! "));
		}
		else
		{
			PChar.GenQuest.PGG_Quest.Nation = FindEnemyNation2NationWithoutPirates(sti(PChar.Nation));
			Dialog.Text = "嘘... 我们不应该在酒馆里讨论生意 - 太多不该听的耳朵。 我在我的船'" + NPChar.Ship.Name + "上等你。 我们在那里谈。 ";
			link.l1 = "我没有时间, 也不喜欢拜访。 ";
		}
		link.l1.go = "Quest_1_Work_1";
		link.l2 = PCharRepPhrase(RandPhraseSimple("我会来的。 但如果你只是在浪费我的时间, 我会把你的舌头扯出来! ", 
					RandSwear() + "好吧, 等我。 我希望你的提议值得。 别想耍什么花招! "), 
				RandPhraseSimple("我会很高兴接受你的邀请, 船长。 ", 
					"你引起了我的兴趣。 当然, 我会来。 "));
		link.l2.go = "Exit_Quest_1_AfterTavernTalk";
		break;

	case "Quest_1_Work_1":
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("哦, 你晕船了, 是吗? 跑去躲在你妈妈的裙子下面! ", 
					"太害怕了? ! 滚开! "), 
				RandPhraseSimple("不能这么做。 如果你不关心黄金, 那是你的选择。 ", 
					"只能这样。 如果你不想要 - 好的, 还有很多其他人。 "));
		link.l1 = PCharRepPhrase(RandPhraseSimple("哈! 你很勇敢, 不是吗? 好吧, 我会来! ", 
					"我看你能坚持自己的立场, 船长。 好吧, 等我。 "), 
				RandPhraseSimple("好的, 我同意。 ", 
					"你很会说话。 我准备在你的船上讨论生意。 "));
		link.l1.go = "Exit_Quest_1_AfterTavernTalk";
		link.l2 = PCharRepPhrase(RandPhraseSimple("哈! 你想引诱我到你的船上杀了我? 那不行! ", 
					"你的话一文不值! 我不会和你有任何生意! "), "可疑的提议。 我不得不拒绝。 ");
		link.l2.go = "Quest_1_NotWork";
		break;

	case "Quest_1_NotWork":
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("给我来朗姆酒! 你从我的视线里消失! ", 
					"我们不是已经讨论过所有事情了吗? "), 
				RandPhraseSimple("去做你自己的事吧。 我有事情要做。 ", 
					"我认为我们没有什么可讨论的。 "));
		link.l1 = RandSwear();
		link.l1.go = "exit_2";
		break;

	case "Quest_1_Work_2":
		Dialog.Text = "我告诉过你我会在我的船上等你! ";
		link.l1 = "哦... 当然... ";
		link.l1.go = "exit";
		NextDiag.TempNode = "Quest_1_Work_2";
		break;

	case "Exit_Quest_1_AfterTavernTalk":
		PChar.GenQuest.PGG_Quest = 1;
		PChar.GenQuest.PGG_Quest.Stage = 0;
		PChar.GenQuest.PGG_Quest.PGGid = NPChar.id;

		Group_AddCharacter("PGGQuest", NPChar.id);
		Group_SetGroupCommander("PGGQuest", NPChar.id);
		Group_SetAddress("PGGQuest", Islands[GetCharacterCurrentIsland(PChar)].id, "Quest_Ships", "Quest_Ship_1");
		Group_SetTaskNone("PGGQuest");

		SetTimerConditionParam("PGGQuest1_RemoveShip_Timer", "PGGQuest1_RemoveShip_Timer", 0, 0, 0, MakeInt(GetHour() + 6), false);
		PChar.Quest.PGGQuest1_RemoveShip_Timer.function = "PGG_Q1RemoveShip";

		NPChar.Ship.Mode = "Pirate";
		NPChar.DeckDialogNode = "Quest_1_Ship";
		NPChar.Nation.Bak = NPChar.Nation;
		NPChar.Nation = GetCityNation(GetCurrentTown());
		NPChar.AlwaysFriend = true;
		NPChar.Abordage.Enable = false; //不能进行登船
		SetCharacterRelationBoth(sti(PChar.index), sti(NPChar.index), RELATION_FRIEND);

		ReOpenQuestHeader("Gen_PGGQuest1");
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Tavern");
		}
		else
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Tavern_1");
			AddQuestUserData("Gen_PGGQuest1", "sSex", GetSexPhrase("",""));
		}
		AddQuestUserData("Gen_PGGQuest1", "sShipName", NPChar.Ship.Name);

		NextDiag.CurrentNode = "Quest_1_Work_2";
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;

	case "Quest_1_Ship":
		PChar.Quest.PGGQuest1_RemoveShip_Timer.Over = "yes";
		if (GetCompanionQuantity(PChar) == COMPANION_MAX)
		{
			Dialog.Text = RandPhraseSimple("哦, 不, 那不行... 对你来说, " + GetSexPhrase("兄弟","姑娘") + ", 船是不是太多了? ", 
					"哈! 在这么大的公司里, 没有办法保守秘密。 滚开。 ");
			link.l1 = RandPhraseSimple("如你所愿! ", 
					"好吧。 我不在乎。 ");
			link.l1.go = "Exit";
			PChar.Quest.PGGQuest1_RemoveEnd.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_RemoveEnd.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_RemoveEnd.function = "PGG_Q1RemoveShip";
			break;
		}
		PChar.GenQuest.PGG_Quest.Stage = 1;
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
//			Dialog.Text = "Great。 Now I am certain that there are no wrong ears around, and my sailors have already been informed。 So my offer is to acquire some ownerless stuff.";
//			link.l1 = "And what's so hard about it? Why would you need me for that, in the first place?";
			Dialog.Text = RandPhraseSimple("欢迎登船, 船长! ", 
					"太好了。 现在我确定周围没有不该听的耳朵, 我的水手已经被告知了。 所以我的提议是获取一些无主的东西。 ") + 
					" 所以我的提议是获取一些无主的东西。 ";
			link.l1 = RandPhraseSimple("这有什么难的? 首先, 你为什么需要我? ", 
					"无主的? ! 你一定是在开玩笑! ");
		}
		else
		{
			Dialog.Text = "现在我确定周围没有不该听的耳朵 - 说吧! ";
			link.l1 = "所以我的提议是获取一些无主的东西。 ";
		}
		link.l1.go = "Quest_1_Ship_1";
		break;

	case "Quest_1_Ship_1":
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			Dialog.Text = RandPhraseSimple("嗯, 有人认为那是他们的, 需要说服他们不是。 ", 
					"当然, 需要杀个人 - 但这肯定不是问题吧? ");
			link.l1 = PCharRepPhrase(RandSwear() + RandPhraseSimple("谈正事! ", 
					"这闻起来像一场屠杀! 他们在哪里? "), 
				RandPhraseSimple("我想知道你提议的更多细节。 ", 
					"你到底给我提供了什么? "));
			link.l1.go = "Quest_1_Ship_Detail";
			link.l2 = PCharRepPhrase(RandPhraseSimple("你在骗我。 我不会参与的! ", 
					"那看起来很容易, 但我不信任你! 你想让我为你火中取栗? 好吧, 我不同意! "), 
				RandPhraseSimple("听起来很有希望, 但我会错过。 ", 
					"不, 我不偷, 我喜欢他们给我礼物。 "));
			link.l2.go = "Quest_1_Ship_Refuse";
		}
		else
		{
			Dialog.Text = "这有什么难的? 你为什么需要我? ";
			link.l1 = "嗯, 有人认为那是他们的, 需要说服他们不是。 ";
			link.l1.go = "Quest_1_Ship_Detail";
		}
		break;

	case "Quest_1_Ship_Detail":
		sTmp = "属于" + NationNameGenitive(sti(PChar.GenQuest.PGG_Quest.Nation)) + "的商队, 运输";
		if (sti(PChar.GenQuest.PGG_Quest.Goods) == GOOD_SLAVES)
		{
			sTmp += "奴隶";
			PChar.GenQuest.PGG_Quest.Goods.Text = "奴隶";
		}
		else
		{
			sTmp += XI_ConvertString(Goods[sti(PChar.GenQuest.PGG_Quest.Goods)].Name);
			PChar.GenQuest.PGG_Quest.Goods.Text = XI_ConvertString(Goods[sti(PChar.GenQuest.PGG_Quest.Goods)].Name);
		}

		if (PChar.GenQuest.PGG_Quest.Island.Town == "" || PChar.GenQuest.PGG_Quest.Island.Town == "Caiman" ||
			PChar.GenQuest.PGG_Quest.Island.Town == "Terks" || PChar.GenQuest.PGG_Quest.Island.Town == "Dominica")
		{
			sLoc = GetConvertStr(PChar.GenQuest.PGG_Quest.Island, "LocLables.txt") + "";
		}
		else
		{
			sLoc = XI_ConvertString("Colony" + PChar.GenQuest.PGG_Quest.Island.Town + "Gen");
		}
		
		if (sti(PChar.GenQuest.PGG_Quest.Template)) 
		{
			sTmp +=	", 在" + sLoc + "附近的" + GetConvertStr(PChar.GenQuest.PGG_Quest.Island.Shore, "LocLables.txt") + "海湾停靠补给。 ";
		}
		else
		{
			sTmp += ", 在" + sLoc + "附近遭遇风暴沉没。 但他们设法保护了部分货物, 并在" + GetConvertStr(PChar.GenQuest.PGG_Quest.Island.Shore, "LocLables.txt") +
				"海湾登陆。 现在他们在等待他们的中队到来。 ";
		}
		
		Dialog.Text = sTmp;
		link.l1 = PCharRepPhrase(RandSwear() + RandPhraseSimple("别拖了, 快说! ", 
					"我就知道你, 还有什么你知道的? "), 
				RandPhraseSimple("那很有趣, 请继续! ", 
					"我" + GetSexPhrase("全神贯注","全神贯注") + "听着! "));
		link.l1.go = "Quest_1_Ship_Detail_1";

		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			link.l2 = PCharRepPhrase(RandPhraseSimple("那听起来是个诱人的事情, 但我仍然拒绝。 我不需要和" + NationNameAblative(sti(PChar.GenQuest.PGG_Quest.Nation)) + "争吵。 ", 
					"商队? 无主的? ! 应该有一千名士兵守卫它! 不, 不行。 我要走了。 "), 
				RandPhraseSimple("不, 我没有和" + NationNameAblative(sti(PChar.GenQuest.PGG_Quest.Nation)) + "开战, 所以我不感兴趣。 ", 
					"我的答案是不! 我不想破坏与" + NationNameAblative(sti(PChar.GenQuest.PGG_Quest.Nation)) + "的关系! "));
			link.l2.go = NPCharRepPhrase(NPChar, "Quest_1_Ship_BadWay", "Quest_1_Ship_Refuse");
		}
		else
		{
			Dialog.Text = "这闻起来像一场屠杀! 细节呢? ";
			link.l1 = sTmp;
		}
		if (sti(PChar.GenQuest.PGG_Quest.Template)) 
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Detail_A");
		}
		else
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Detail_B");
		}
		AddQuestUserData("Gen_PGGQuest1", "sNation", NationNameGenitive(sti(PChar.GenQuest.PGG_Quest.Nation)));
		AddQuestUserData("Gen_PGGQuest1", "sGoods", PChar.GenQuest.PGG_Quest.Goods.Text));
		AddQuestUserData("Gen_PGGQuest1", "sColony", sLoc);
		AddQuestUserData("Gen_PGGQuest1", "sShore", GetConvertStr(PChar.GenQuest.PGG_Quest.Island.Shore, "LocLables.txt"));
		break;

	case "Quest_1_Ship_Detail_1":
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
//			Dialog.Text = "We only have " + FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)) + " to intercept them.";
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("在" + FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)) + "天内商队会走得太远, 我们无法追上。 ", 
						"我们正好有" + FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)) + "天来杀了他们并拿到战利品! "), 
					RandPhraseSimple("我们只有" + FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)) + "天来完成整个行动。 ", 
						"我们得快点, " +pchar.name+ "。 我们只有" + FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)) + "天。 "));
			link.l1 = RandPhraseSimple("我们会及时赶到的! 我们今天就起航。 ", "那我们不要浪费时间了。 下令今天起航。 ");
			link.l1.go = "Exit_Quest_1_Accept";
			AddQuestRecord("Gen_PGGQuest1", "q1_Accept");
		}
		else
		{
			Dialog.Text = "那很有趣, 请继续。 ";
			link.l1 = "我们只有" + FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)) + "天来拦截他们。 ";
			link.l1.go = "Quest_1_Ship_Accept";
			AddQuestRecord("Gen_PGGQuest1", "q1_Accept_1");
		}
		AddQuestUserData("Gen_PGGQuest1", "nDays", FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)));
		break;

	case "Quest_1_Ship_Accept":
		Dialog.Text = "我们不要浪费时间了! 出发! ";
		link.l1 = "出发! ";
		link.l1.go = "Exit_Quest_1_Accept";
		break;

	case "Exit_Quest_1_Accept":
		if (sti(PChar.GenQuest.PGG_Quest.Stage) < 2)
		{
			PChar.GenQuest.PGG_Quest.Stage = 2;
			PGG_Q1RemoveShip("");

			if (sti(PChar.GenQuest.PGG_Quest.Template)) 
			{
				PGG_Q1PlaceShipsNearIsland();
			}
			else
			{
				Locations[FindLocation(PChar.GenQuest.PGG_Quest.Island.Shore)].DisableEncounters = true;

				PChar.Quest.PGGQuest1_CheckStartState.win_condition.l1 = "Location";
				PChar.Quest.PGGQuest1_CheckStartState.win_condition.l1.Location = PChar.GenQuest.PGG_Quest.Island.Shore;
				PChar.Quest.PGGQuest1_CheckStartState.function = "PGG_Q1CheckStartState";
			}
			PChar.Quest.PGGQuest1_PGGDead.win_condition.l1 = "NPC_Death";
			PChar.Quest.PGGQuest1_PGGDead.win_condition.l1.Character = PChar.GenQuest.PGG_Quest.PGGid;
			PChar.Quest.PGGQuest1_PGGDead.function = "PGG_Q1PGGDead";

			SetTimerCondition("PGGQuest1_Time2Late", 0, 0, sti(PChar.GenQuest.PGG_Quest.Days), false);
			PChar.Quest.PGGQuest1_Time2Late.function = "PGG_Q1Time2Late";

			NPChar.PGGAi.IsPGG = false;
			NPChar.PGGAi.location.town = "none";
			DeleteAttribute(NPChar, "PGGAi.Task");
			DeleteAttribute(NPChar, "PGGAi.LockService");
			DeleteAttribute(NPChar, "AlwaysFriend");

			SetCompanionIndex(PChar, -1, sti(NPChar.index));
			SetCharacterRemovable(NPChar, false);
			
			SetBaseShipData(NPChar);
            DeleteAttribute(NPChar,"ship.sails");
			DeleteAttribute(NPChar,"ship.masts");
			DeleteAttribute(NPChar,"ship.blots");
			DeleteAttribute(NPChar,"ship.hulls");
			
			Fantom_SetCannons(NPChar, "pirate");
			Fantom_SetBalls(NPChar, "pirate");
		}
		NextDiag.CurrentNode = "Quest_1_Ship_Accept";
		DialogExit();
		break;

	case "Quest_1_Ship_Refuse":
		Dialog.Text = RandSwear() + "你让我失望了, 船长。 你以为我会邀请你参加" + RandPhraseSimple("主日弥撒? ! ", "儿童剧! ??"));
		link.l1 = PCharRepPhrase(RandPhraseSimple("那是你的事。 由我决定。 ", 
					"我不会为了几个比索而上绞架。 "), 
				RandPhraseSimple("我的决定是最终的, 船长。 ", 
					"我们没有更多可讨论的了。 "));
		link.l1.go = "Exit_Quest_1_Refuse";
		break;

	case "Exit_Quest_1_Refuse":
		if (sti(PChar.GenQuest.PGG_Quest.Stage) != -1)
		{
			PChar.GenQuest.PGG_Quest.Stage = -1;
			PChar.Quest.PGGQuest1_RemoveShip.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_RemoveShip.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_RemoveShip.function = "PGG_Q1RemoveShip";

			AddQuestRecord("Gen_PGGQuest1", "q1_Close");
			AddQuestUserData("Gen_PGGQuest1", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Gen_PGGQuest1");
			DeleteAttribute(NPChar, "AlwaysFriend");
		}
		NPChar.Dialog.CurrentNode = "Quest_1_Ship_Refuse";
		NPChar.DeckDialogNode = "Quest_1_Ship_Refuse";
		DialogExit();
		break;

	case "Quest_1_Ship_BadWay":
		Dialog.Text = PCharRepPhrase("哦, 来吧! 一切都会顺利进行, 没有人会知道任何事情。 我们会杀了所有人。 "), 
				RandPhraseSimple("你要去哪里, 船长? 也许是去当局? ", 
					"走进虎穴却以为能轻易脱身, 这是很不明智的。 "));
		link.l1 = PCharRepPhrase(RandSwear() + RandPhraseSimple("去吻海魔吧! 我是" +GetFullName(pchar)+ "船长, 我不在乎你! 我要走了! ", 
					"我发誓, 你真的让我发疯了! "), 
				RandPhraseSimple("你的提议对我没有任何兴趣, 我们没有更多可讨论的了。 再见。 ", 
					"我认为我们之间没有更多可讨论的了。 对不起, 我很忙, 我需要走了。 "));
		link.l1.go = "Quest_1_Ship_BadWay_1";
		break;

	case "Quest_1_Ship_BadWay_1":
		Dialog.Text = RandSwear() + PCharRepPhrase(RandPhraseSimple("抓住" + GetSexPhrase("他","她") + "! 把" + GetSexPhrase("他","她") + "绑在大炮上! 让我们看看" + GetSexPhrase("他","她") + "的胆子是什么颜色的!!! ", 
					"嘿! 约翰尼! 亨德森! 抓住那个" + GetSexPhrase("恶棍","姑娘") + "! 别让" + GetSexPhrase("他","她") + "上救生艇!!! "), 
				RandPhraseSimple("真遗憾, 船长! 不过我希望你会喜欢我们的船舱。 然后我们会决定怎么处置你。 ", 
					"白奴活不了多久, 船长, 所以你选择: 要么亨德斯朝你头上开枪, 要么你在采石场度过余生。 "));
		link.l1 = PCharRepPhrase(RandPhraseSimple("我会让你吃掉你肮脏的胆子, " + GetFullName(NPChar) + "!!! ", 
					"让开! 恶棍! 我会当场杀了你! "), 
				RandPhraseSimple("你的提议不可接受... 而且非常不明智!!! ", 
					"你看起来不太好客... 让开!!! "));
		link.l1.go = "Exit_Quest_1_DeckFight";
		break;

	case "Exit_Quest_1_DeckFight":
        GetCharacterPos(NPChar, &locx, &locy, &locz);
		DeleteAttribute(NPChar, "AlwaysFriend");
        sTmp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
		LAi_SetImmortal(NPChar, true);
		LAi_SetActorType(NPChar);
		LAi_ActorRunToLocation(NPChar, "reload", sTmp, "none", "", "", "", 5.0);

		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		//группа можeт быть занята, а провeрок по группам у нас нeт... :(
		if (!CheckAttribute(pchar, "questTemp.PGGContra.Know"))
		{
			sTmp = "PGGTmp";
		}
		else
		{
			sTmp = "PGGQst";
		}
		PChar.GenQuest.PGG_Quest.GrpID = sTmp;

		for (i=1; i<5; i++)
		{
			sld = CharacterFromID("saylor_0" + i);
			LAi_group_MoveCharacter(sld, sTmp);
		}
		LAi_group_FightGroups(LAI_GROUP_PLAYER, sTmp, true);
		LAi_group_SetCheck(sTmp, "PGG_Q1AfterDeckFight");
		chrDisableReloadToLocation = true;

		PGG_ChangeRelation2MainCharacter(NPChar, -20);
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		LAi_SetFightMode(pchar, true);
		break;

	case "Quest_1_Time2Late":
		chrDisableReloadToLocation = false;

		//移到这里.. х.з。 似乎会更好 (Изгоя的bug.)
		PChar.Quest.PGGQuest1_PGGDead.Over = "Yes";
		PChar.Quest.PGGQuest1_GroupDead.Over = "Yes";
		PChar.Quest.PGGQuest1_CheckStartState.Over = "Yes";

//		Dialog.Text = "So, " +GetFullName(pchar)+ ", I see that I made a mistake by getting mixed up with you。 Now there's no loot for us。 Farewell!";
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("该死的! 我们迟到了 - 都是因为那些懒惰的蠢货! 现在没有战利品和你分享了, " +GetFullName(pchar)+ "。 升起支索帆! 我们离开这里! ", 
					"所以, " +GetFullName(pchar)+ ", 我看和你混在一起是个错误。 现在我们没有战利品了。 再见! "), 
				RandPhraseSimple("他们消失了 - 都是因为你的拖延! 现在我们分道扬镳, " +GetFullName(pchar)+ "。 ", 
					"现在肯定追不上商队了。 和你混在一起是个错误。 再见! "));
		link.l1 = PCharRepPhrase(RandPhraseSimple("让那商队见鬼去吧! 采珠人更好, 而且没有风险! ", 
					"幸运与我们同在, 明天又是新的一天! 海上有很多可怜的商人等着我们拿他们的钱! "), 
				RandPhraseSimple("确实可惜, 如此出色的行动竟以彻底失败告终! 再见! ", 
					"谋事在人, 成事在天... 再见! "));
		link.l1.go = "Exit_Quest_1_2Late";

		AddQuestRecord("Gen_PGGQuest1", "q1_Time2Late");
		CloseQuestHeader("Gen_PGGQuest1");
		break;

	case "Exit_Quest_1_2Late":
        LAi_SetPlayerType(PChar);
		if (sti(PChar.GenQuest.PGG_Quest.Stage) != -1)
		{
			PChar.GenQuest.PGG_Quest.Stage = -1;
			RemoveCharacterCompanion(pchar, NPChar);

			NPChar.PGGAi.IsPGG = true;
			NPChar.RebirthPhantom = true;

			LAi_SetWarriorTypeNoGroup(NPChar);
			LAi_group_MoveCharacter(NPChar, "GroupDeck");

			PChar.Quest.PGGQuest1_Clear.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_Clear.win_condition.l1.Location = PChar.location;
			if (PChar.location == "Ship_deck")
			{
/*				PChar.Quest.PGGQuest1_RemoveShip.win_condition.l1 = "ExitFromSea";
				PChar.Quest.PGGQuest1_RemoveShip.function = "PGG_Q1RemoveShip";
				PChar.Quest.PGGQuest1_Clear.win_condition.l1 = "ExitFromSea";
*/				PChar.quest.Munity = "Deads";
			}
			PChar.Quest.PGGQuest1_Clear.function = "PGG_Q1EndClear";
		}
		NextDiag.CurrentNode = "Quest_1_Failed";
		DialogExit();
		break;

	case "Quest_1_CheckResult":
		if (PChar.location == PChar.GenQuest.PGG_Quest.Island.Shore)
		{
			Locations[FindLocation(PChar.GenQuest.PGG_Quest.Island.Shore)].DisableEncounters = false;
		}
		else
		{
			PChar.quest.Munity = "Deads";
		}
		chrDisableReloadToLocation = false;

		//没拿到货物... 
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			PChar.GenQuest.PGG_Quest.FailedPaySum = sti(PChar.GenQuest.PGG_Quest.Days)*10000;
//			Dialog.Text = "Oh, why in hell have I mixed up with you。 You've ruined everything。 So, now you must pay me a penalty of " + FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)) + ".";
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("嗜血的" + GetSexPhrase("恶棍","败类") + "! 一切都沉入海底了! 马上给我" + FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)) + "比索, 从我的视线消失! ", 
						"你以为自己是纳尔逊上将吗? 把所有战利品都沉了, " + GetSexPhrase("白痴","蠢女人") + "! 现在给我" + FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)) + "比索, 滚蛋! "), 
					RandPhraseSimple("你决定在这里开战! 这完全不可接受! 但我想, 如果你付给我们" + FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)) + "比索, 我们可以忘记这件事。 ", 
						"你的方法完全不可接受! 你毁了整个事情! 立即付给我们我们的份额, 金额为" + FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)) + "比索, 然后想去哪就去哪! "));
			link.l1 = PCharRepPhrase(RandPhraseSimple("如果不是我, 你现在已经在喂螃蟹了, 贪婪的混蛋! ", 
						"哦, 是的, 我应该让他们的旗舰登你的船 - 那样你现在就不会在这里污染空气了, 在桅杆上晃荡! "), 
					RandPhraseSimple("你的要求不合适, 你的暗示是侮辱性的! ", 
						"我们没有同意罚款, 所以我不会付你任何东西! "));
			link.l1.go = "Quest_1_NotPay";
			if (sti(pchar.money) >= sti(PChar.GenQuest.PGG_Quest.FailedPaySum))
			{
				link.l2 = PCharRepPhrase(RandPhraseSimple("我现在不能和你战斗, 你知道的! 噎死你的比索吧! ", 
								"比索? ! 好吧, 今天幸运女神肯定没对我微笑。 我同意。 "), 
							RandPhraseSimple("你的要求太过分了, 但我想我别无选择。 ", 
								"你的胃口太大了, 但我不得不同意! "));
				link.l2.go = "Exit_Quest_1_Failed";
			}
		}
		else
		{
			PChar.GenQuest.PGG_Quest.Stage = -1;
			Dialog.Text = "哦, 我到底为什么和你混在一起。 你毁了一切。 ";
			link.l1 = "哦, 得了吧! 你自己也看到了, 没有其他办法。 ";
			link.l1.go = "Exit_Quest_1_Failed";
		}

		//至少拿了三分之一, 如果拿到了, 那就好! 
		if (sti(PChar.GenQuest.PGG_Quest.Goods.Taken) > MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Qty)/3))
		{
			PChar.GenQuest.PGG_Quest.Ok = 1;
//			Dialog.Text = "So, our loot makes up " + PChar.GenQuest.PGG_Quest.Goods.Taken + " " + PChar.GenQuest.PGG_Quest.Goods.Text + "。 Let's split.";
			Dialog.Text = PCharRepPhrase("那是笔热门交易! 所以, 我们的战利品有" + PChar.GenQuest.PGG_Quest.Goods.Taken + " " + PChar.GenQuest.PGG_Quest.Goods.Text + "。 ", 
					"干得好, 船长! 我们的战利品有" + PChar.GenQuest.PGG_Quest.Goods.Taken + " " + PChar.GenQuest.PGG_Quest.Goods.Text + "。 ");
			i = sti(PChar.GenQuest.PGG_Quest.Parts);
			PChar.GenQuest.PGG_Quest.Goods.Part = MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Taken) / i);
			if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
			{
				Dialog.Text = Dialog.Text + PCharRepPhrase(" 我的份额是 ", " 我的船的份额 - ");
			}
			else
			{
				Dialog.Text = Dialog.Text + " 你的份额是 ";
			}
			Dialog.Text = Dialog.Text + PChar.GenQuest.PGG_Quest.Goods.Part + "。 ";
			link.l1 = PCharRepPhrase(RandPhraseSimple("完全正确! 船已经在装货了! ", "是的, 一切正确。 一言为定。 "), 
					RandPhraseSimple("你的计算是正确的。 我同意。 ", "说到分赃, 你无可指责。 "));
			link.l1.go = "Exit_Quest_1_End";
			link.l2 = PCharRepPhrase(RandPhraseSimple("你敢要求你的份额? 你应该马上被吊死在桅杆上! ", 
						"你的份额? 这里每个人都为自己。 如果没有给你留下什么, 那是你的麻烦! "), 
					RandPhraseSimple("我认为你不能指望任何份额。 ", 
						"我的答案是不! 我不会和你这样的恶棍分享! "));
			link.l2.go = "Quest_1_NotPay";
		}
		else
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Fail");
		}
		break;

	case "Quest_1_NotPay":
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("好吧, 那我不争论了! 再见! ", 
					"我们不要流血, 让事情变得更糟! 下次我们会有更好的运气! "), 
				RandPhraseSimple("好吧, 再见, 船长, 我没有立场提出要求... ", 
					"我的船的损失和损坏不允许我坚持公正的决定。 我把它留给你的良心, 船长! "));
		link.l1 = PCharRepPhrase(RandPhraseSimple("祝你顺风! ", "龙骨下七英尺! "), 
				RandPhraseSimple("再见! 我希望新鲜的海风对你有好处! ", 
					"我希望我们的不幸不会让你变得更难以忍受, 船长! 再见! "));
		link.l1.go = "Exit_Quest_1_Failed";
		PChar.GenQuest.PGG_Quest.Stage = -1;

		bOk = makeint(NPChar.reputation) < 41 && PGG_ChangeRelation2MainCharacter(NPChar, 0) < 75;
		if (bOk || CheckAttribute(PChar, "GenQuest.PGG_Quest.Ok"))
		{
			PChar.GenQuest.PGG_Quest.Stage = 4;
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("你不明白吗! 你本可以用钱买命的! 抓住那个混蛋! ", 
						"或者你认为我们在和你玩游戏? 好吧, 一旦我们把你 keelhaul (拖在船底) , 你应该会变得更顺从! "), 
					RandPhraseSimple("那么我们不得不缩短你的生命了, 船长! 如果你不友好地离开, 很快你就会见到圣马丁! ", 
						"你让我别无选择, " +GetFullName(pchar)+ "! 我会拿走我的东西, 不管你喜不喜欢! "));
			link.l1 = PCharRepPhrase(RandPhraseSimple("我对魔鬼发誓, 你会为此付出代价的! ", 
						"哟嗬! 那就来抓我吧, " +GetFullName(pchar)+ "船长! "), 
					RandPhraseSimple("这一刀会又长又深! ", 
						"你想快点死还是受点苦? "));
			link.l1.go = "Exit_Quest_1_FailedFight";
		}
		break;

	case "Exit_Quest_1_Failed":
		if (sti(PChar.GenQuest.PGG_Quest.Stage) != -1)
		{
			AddMoneyToCharacter(PChar, -(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)));
			AddQuestRecord("Gen_PGGQuest1", "q1_FailPay");
		AddQuestUserData("Gen_PGGQuest1", "sSex", GetSexPhrase("",""));
		AddQuestUserData("Gen_PGGQuest1", "sSex1", GetSexPhrase("",""));
		}
		CloseQuestHeader("Gen_PGGQuest1");
		RemoveCharacterCompanion(pchar, NPChar);

		if (PChar.Location == "Ship_deck")
		{
			PChar.Quest.PGGQuest1_FailedExitSea.win_condition.l1 = "ExitFromSea";
			PChar.Quest.PGGQuest1_FailedExitSea.function = "PGG_Q1EndClear";
		}
		else
		{
			PChar.Quest.PGGQuest1_FailedExitLoc.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_FailedExitLoc.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_FailedExitLoc.function = "PGG_Q1EndClear";
		}
		PGG_ChangeRelation2MainCharacter(NPChar, -5);

		LAi_SetImmortal(NPChar, true);
		//为了不让护卫被打.
		for (i = 1; i < sti(PChar.GenQuest.PGG_Quest.GrpID.Qty); i++)
		{
			sld = CharacterFromID("pirate_" + i);
			LAi_SetImmortal(sld, true);
		}

		NextDiag.CurrentNode = "Quest_1_Failed";
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;

	case "Quest_1_Failed":
		Dialog.Text = "我不想再和你打交道了! ";
		link.l1 = "完全没问题。 ";
		link.l1.go = "Exit";
		NextDiag.TempNode = "Quest_1_Failed";
		break;

	case "Quest_1_End":
		Dialog.Text = "和你做生意很愉快。 祝你好运。 ";
		link.l1 = "你也一样。 ";
		link.l1.go = "Exit";
		NextDiag.TempNode = "Quest_1_End";
		break;

	case "Exit_Quest_1_FailedFight":
		RemoveCharacterCompanion(pchar, NPChar);

		LAi_LockFightMode(pchar, false);
		LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
		LAi_group_SetRelation("PGGTmp", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);	
		LAi_group_FightGroups(LAI_GROUP_PLAYER, "PGGTmp", true);
		LAi_group_SetCheck("PGGTmp", "PGG_Q1AfterDeckFight");
	
		PChar.GenQuest.PGG_Quest.GrpID = "PGGTmp";
		chrDisableReloadToLocation = true;

		Group_AddCharacter("PGGQuest", NPChar.id);
		Group_SetGroupCommander("PGGQuest", NPChar.id);
		Group_SetAddress("PGGQuest", PChar.GenQuest.PGG_Quest.GrpLocation, "Quest_Ships", PChar.GenQuest.PGG_Quest.GrpLoc);
		Group_SetTaskNone("PGGQuest");

		PGG_ChangeRelation2MainCharacter(NPChar, -15);

		GetCharacterPos(NPChar, &locx, &locy, &locz);
        sTmp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
		NextDiag.CurrentNode = "Second Time";
		DialogExit();

		Log_TestInfo("go to loc " + sTmp + " " + NPChar.location);
		NPChar.location = PChar.location;
		if (PChar.location != "Ship_Deck") sTmp = "reload1_back";

		PChar.questTemp.Chr2Remove = NPChar.id;
		LAi_ActorRunToLocator(NPChar, "reload", sTmp, "RemoveCharacterFromLocation", 5.0);

		LAi_SetImmortal(NPChar, true);
		LAi_SetFightMode(pchar, true);
		break;

	case "Exit_Quest_1_End":
		RemoveCharacterCompanion(PChar, NPChar);

		i = sti(PChar.GenQuest.PGG_Quest.Goods.Part);
/*		i *= (sti(PChar.GenQuest.PGG_Quest.Parts)-1);
		i += sti(PChar.GenQuest.PGG_Quest.StartGoods);
		n = GetCompanionQuantity(PChar);
		SetCharacterGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods), i);
		for (i = 1; i < n; i++)
		{
			iRnd = GetCompanionIndex(PChar, i);
			if (iRnd != -1)
			{
				sld = GetCharacter(iRnd);
				if (GetRemovable(sld))
				{
					Log_TestInfo("" + sld.id);
					SetCharacterGoods(sld, sti(PChar.GenQuest.PGG_Quest.Goods), 0);
				}
			}
		}
*/
		RemoveCharacterGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods), i);
/*		if (PChar.Location == "Ship_deck")
		{
			PChar.Quest.PGGQuest1_EndExitSea.win_condition.l1 = "ExitFromSea";
			PChar.Quest.PGGQuest1_EndExitSea.function = "PGG_Q1EndClear";
		}
		else
		{*/
			PChar.Quest.PGGQuest1_EndExitLoc.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_EndExitLoc.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_EndExitLoc.function = "PGG_Q1EndClear";
		//}
		AddQuestRecord("Gen_PGGQuest1", "q1_OkShare");
		CloseQuestHeader("Gen_PGGQuest1");

		//为了不让护卫被打.
		for (i = 1; i < sti(PChar.GenQuest.PGG_Quest.GrpID.Qty); i++)
		{
			sld = CharacterFromID("pirate_" + i);
			LAi_SetImmortal(sld, true);
		}

		LAi_SetImmortal(NPChar, true);
		NextDiag.CurrentNode = "Quest_1_End";
		DialogExit();
  		LAi_SetWarriorType(NPChar); // 重置玩家组
		LAi_group_MoveCharacter(NPChar, LAI_GROUP_PLAYER);
		break;

	case "Quest_1_SharePrise":
		chrDisableReloadToLocation = false;
		Dialog.Text = PCharRepPhrase("那真是一场屠杀! 可惜他们没有带女人! 战利品有" + PChar.GenQuest.PGG_Quest.Goods.Taken + " " + PChar.GenQuest.PGG_Quest.Goods.Text + "。 ", "不错, 船长! 战利品有" + PChar.GenQuest.PGG_Quest.Goods.Taken + " " + PChar.GenQuest.PGG_Quest.Goods.Text + "。 ");

		i = sti(PChar.GenQuest.PGG_Quest.Parts);
		PChar.GenQuest.PGG_Quest.Goods.Part = MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Taken) / i);
        SetCharacterGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods), sti(PChar.GenQuest.PGG_Quest.Goods.Taken) + GetCargoGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods)));
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			Dialog.Text = Dialog.Text + " 我的份额是 ";
		}
		else
		{
			Dialog.Text = Dialog.Text + " 你的份额是 ";
		}
		Dialog.Text = Dialog.Text + PChar.GenQuest.PGG_Quest.Goods.Part + "。 ";
		link.l1 = PCharRepPhrase(RandPhraseSimple("完全公正, 该死的! ", "一切完全正确, 该死的! "), 
			RandPhraseSimple("你的计算是正确的。 我同意。 ", "说到分赃, 你无可指责。 "));
		link.l1.go = "Exit_Quest_1_End";
		break;
//===================================
//              Exits 
//===================================
	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;
		
	case "Exit_2":
		if (CheckAttribute(pchar, "GenQuest.PGG_Quest")) DeleteAttribute(pchar, "GenQuest.PGG_Quest"); //fix
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;		

	case "Exit_Smugglers_Fight":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();

		LAi_group_FightGroups(LAI_GROUP_PLAYER, "PGGTmp", true);
		LAi_SetFightMode(pchar, true);
		break;

	case "Exit_ShowParam":
		NextDiag.CurrentNode = "Second Time";
//		NPChar.quest.meeting = true;
		DialogExit();

		PChar.SystemInfo.OnlyShowCharacter = true;
		LaunchCharacter(NPChar);
		break;
	}
}
/* TEMPLATE
		Dialog.Text = "";
		link.l1 = "";
		link.l1.go = "";
		link.l2 = "";
		link.l2.go = "";
		link.l3 = "";
		link.l3.go = "";
*/

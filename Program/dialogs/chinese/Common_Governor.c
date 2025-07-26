// boal 25/04/04 总督通用对话
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// 按城市调用对话 -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Governor\" + NationShortName(sti(NPChar.nation)) + "_Governor.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	// 按城市调用对话 <--
    
    ref offref, sld;
    int i, cn;
    int qty;
    int iSumm;
    string attrLoc;

	/// 赎回殖民地
    ref CaptGovenor, FortColony;
    int f, colony_money;

    int k = 1000;
    if (CheckAttribute(Nations[sti(NPChar.nation)], "Fort"))
    {
        k = (300 - sti(Nations[sti(NPChar.nation)].Fort)*10);
    }
	bool ok;
	
	attrLoc = Dialog.CurrentNode;
	if (findsubstr(attrLoc, "CityGive_" , 0) != -1)
	{
        i = findsubstr(attrLoc, "_" , 0);
		NPChar.quest.CityIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // 末尾的索引
		Dialog.CurrentNode = "ColonyGive";
	}
	
	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "First time":
            NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("你竟敢在总督府露面? ! 你真是疯了... ", "这些懒骨头怎么会让敌人闯进我的住所? 我真是想不通... ", "如果连某个流浪汉都能在我住所里乱逛, 那我的卫兵简直一文不值... "), 
					LinkRandPhrase("你想要什么, " + GetSexPhrase("爬虫","讨厌鬼") + "? ! 我的士兵已经在追踪你了, " + GetSexPhrase("肮脏的海盗","讨厌鬼") + "! ", "" + GetSexPhrase("肮脏的","肮脏的") + "凶手, 马上离开我的住所! 卫兵! ", "我不怕你, " + GetSexPhrase("恶棍","无赖") + "! 很快你就会被吊死在我们的堡垒里, 你逃不远的... "));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("士兵们一文不值... ", "你永远抓不到我。 "), 
					RandPhraseSimple("闭嘴, 伙计, 不然我就扯出你那肮脏的舌头! ", "我告诉你, 伙计: 安静坐着, 否则我就砍下你的头, 从那扇门扔给你的看门狗... "));
				link.l1.go = "fight";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "我听说你一直坚持要求觐见。 我叫" + GetFullName(npchar) +
                              "。 我是" + NationNameGenitive(sti(NPChar.nation)) + "殖民地的总督, 是" + NationKingsName(npchar) +
                              "在这些海域的王室代表。 现在, 请你告诉我, " + GetAddress_Form(NPChar) + ", 你来访的目的是什么。 ";
				link.l1 = "我叫" +GetFullName(pchar)+ "。 ";
				link.l1.go = "node_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = RandPhraseSimple("哦, 又是你? 那么, 这次你想从" + NationNameGenitive(sti(NPChar.nation)) + "的总督这里得到什么? ",
                              "你又来打扰我处理国家大事了? 你想要什么, " + GetAddress_Form(NPChar) + "? ");
				link.l1 = "我想和你谈谈为" + NationNameGenitive(sti(NPChar.nation)) + "王室效力的事。 ";
				link.l1.go = "work";
				link.l2 = "我需要和你谈一件重要的事。 ";
				link.l2.go = "quests"; // 国家文件
				//Jason --> 帆船赛
				if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
				{
					link.l3 = "我是应邀请来参加帆船赛的。 这是我的邀请函。 ";
					link.l3.go = "Regata";
				}
				//<—— 帆船赛
				link.l10 = "抱歉, 我还有些事要做。 ";
				link.l10.go = "exit";
			}
		break;
		
		case "node_1":
			dialog.text = "那么, 你为什么来这里打扰我处理国家大事? ";
			link.l1 = "我想和你谈谈为" + NationNameGenitive(sti(NPChar.nation)) + "王室效力的事。 ";
			link.l1.go = "work";
			link.l2 = "我本来想和你谈一件重要的事。 ";
			link.l2.go = "quests";
			//Jason --> 帆船赛
			if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
			{
				link.l3 = "我是来参加帆船赛的。 这是我的邀请函。 ";
				link.l3.go = "Regata";
			}
			//<—— 帆船赛
			link.l10 = "只是礼节性拜访, 没别的事, " + GetAddress_FormToNPC(NPChar);
			link.l10.go = "node_2";
		break;

		case "node_2":
			dialog.text = "如果是这样, 我请你离开我的办公室, 别再打扰我工作。 ";
			link.l1 = "是, 是, 当然。 抱歉打扰你了。 ";
			link.l1.go = "exit";
		break;
		
		case "work":
			dialog.text = "如果你在找工作, 去和殖民地的总督们谈谈。 他们经常需要聪明勇敢的船长。 ";
			link.l1 = "我会记住的。 谢谢你。 ";
			link.l1.go = "exit";
		break;
		
		//--> Jason 帆船赛
		case "Regata":
			dialog.text = "哦, 太好了, 很高兴见到你, 船长! 你来得正是时候 --帆船赛几天后就要开始了。 你读过信使交给你的那封信里的帆船赛规则了吗? ";
			link.l1 = "是的, 先生, 我读过了。 ";
			link.l1.go = "Regata_1";
			RemoveItems(PChar, "letter_open", 1);//移除信件
			TakeNationLicence(HOLLAND);//移除许可证
			DeleteAttribute(pchar, "questTemp.Regata.ToPortRoyal"); // patch-5
		break;
		
		case "Regata_1":
			dialog.text = "你准备好50000比索的参赛费了吗? 这笔费用将用于奖金池。 ";
			if (makeint(Pchar.money) >= 50000)
			{
				link.l1 = "是的, 当然。 请收下我的参赛费。 ";
				link.l1.go = "Regata_2";
			}
			link.l2 = "我现在钱有点不够。 但我一定会尽快把钱带来。 ";
			link.l2.go = "Regata_nomoney";
		break;
		
		case "Regata_2":
			dialog.text = "很好。 如果你赢了, 你的钱会以五倍的数额返还给你。 现在, 你应该知道如何不违反帆船赛的规则。 \n和亨利.史蒂文森谈谈细节, 他一定在官邸的房间里。 去见他, 他会解释一切。 ";
			link.l1 = "好的。 我会照你说的做。 ";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -50000);
			pchar.quest.Regata_Guber.win_condition.l1 = "location";
			pchar.quest.Regata_Guber.win_condition.l1.location = "Portroyal_Roomtownhall";
			pchar.quest.Regata_Guber.function = "PrepareToRegataInPortroyal";
			pchar.questTemp.Regata.Begin = "true";
			NextDiag.TempNode = "First time";
		break;
		
		case "Regata_nomoney":
			dialog.text = "好吧, 但请不要太久, 船长。 帆船赛很快就要开始了。 ";
			link.l1 = "我明白。 我会尽量在帆船赛开始前把钱带来。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_1";
			pchar.questTemp.Regata.nomoney = "true";
		break;
		
		//帆船赛-决赛
		case "Regata_Final":
			dialog.text = "这就是帆船赛的冠军! 你好, " +GetFullName(pchar)+ "船长! 请允许我祝贺你获得这一当之无愧的成功! 帆船赛的冠军在英国殖民地总是很受欢迎, 实至名归。 ";
			link.l1 = "谢谢你, 先生! ";
			link.l1.go = "Regata_complete";
		break;
		
		case "Regata_complete":
			dialog.text = "现在让我们直接进入你最期待的部分 --颁奖仪式。 一等奖奖金是250000比索。 给你! ";
			link.l1 = "谢谢! ";
			link.l1.go = "Regata_complete_1";
		break;
		
		case "Regata_complete_1":
			AddMoneyToCharacter(pchar, 250000);
			int iGift;
			string sItem1, sItem2, sItem3, sAdd;
			
			iGift = 3;
			switch (iGift)
			{
				case 0:
					sItem1 = "blade_10";//短刀
					sItem2 = "cirass6";
					sItem3 = "bussol";
					sAdd = "短刀。 决斗者背心和罗盘";
				break;
				
				case 1:
					sItem1 = "blade_15";//马里内拉剑
					sItem2 = "cirass2";//轻骑兵盔甲
					sItem3 = "bussol";
					sAdd = "马里内拉剑。 轻骑兵盔甲和罗盘";
				break;
				
				case 2:
					sItem1 = "blade_17";//布雷塔剑
					sItem2 = "cirass7";//卡拉塞纳盔甲
					sItem3 = "bussol";
					sAdd = "布雷塔剑。 卡拉塞纳盔甲和罗盘";
				break;
				
				case 3://
					sItem1 = "blade_20";//麦当娜剑
					sItem2 = "cirass2";//军官胸甲
					sItem3 = "bussol";
					sAdd = "‘麦当娜’剑。 军官胸甲和罗盘";
				break;
			}
			GiveItem2Character(pchar, sItem1);
			GiveItem2Character(pchar, sItem2);
			GiveItem2Character(pchar, sItem3);
			dialog.text = "此外, 你还有资格获得一套珍贵的奖品: " + sAdd + "。 现在都是你的了。 ";
			link.l1 = "我很高兴, 先生! 真的, 我完全没想到。 ";
			link.l1.go = "Regata_complete_2";
		break;
		
		case "Regata_complete_2":
			dialog.text = "我代表所有英国殖民地, 很高兴感谢你参加帆船赛, 并再次祝贺你的胜利! 如果你下了赌注, 现在是去见亨利.史蒂文森爵士并领取奖金的最佳时机, 如果你还没这么做的话。 祝你好运, 船长! ";
			link.l1 = "谢谢你的亲切话语, 先生! 反过来, 请允许我感谢你为我提供参加如此盛大活动的机会。 现在, 请允许我道别并离开。 ";
			link.l1.go = "Regata_complete_3";
		break;
		
		case "Regata_complete_3":
			DialogExit();
			NextDiag.CurrentNode = "First time";
		break;
		//<-- 帆船赛
	}
}
// 杰森 市民通用对话
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // 按城市调用对话 -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // 按城市调用对话 <--
    ProcessCommonDialogRumors(NPChar, Link, NextDiag);
    int iTest, iTemp;
    iTest = FindColony(NPChar.City);
    ref rColony;
    string sTemp, sCity;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	String attrLoc = Dialog.CurrentNode;
	
	if(HasSubStr(attrLoc, "RumourAboutOwners_"))
	{
		NPChar.RumourOwnerType = FindStringAfterChar(attrLoc, "_");
		Dialog.CurrentNode = "RumourAboutOwners_TakeRumour";
	}
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
            LAi_group_Attack(NPChar, Pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			if (sti(NPChar.nation) == PIRATE)
			{
				if (sti(rColony.HeroOwn) == true) // 我们的市民
				{
				    dialog.text = RandPhraseSimple("他们说你拥有这个城镇, " + GetSexPhrase("先生", "小姐") + "。 ", "真是愉快的相遇! 真是愉快的相遇! 总督本人在和我说话! ");
					link.l1 = RandPhraseSimple("我改变主意了。 祝你好运! ", "只是在城里走走。 再见。 ");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("我有个问题要问你。 ", "我需要一些信息。 ");
					link.l2.go = "quests";//(转发到城市文件)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("我想讨论财务问题。 ", "关于财务... ");
							link.l3.go = "LoanForAll";//(转发到贷款生成器)
						}
					}
					break;
				}
				else
				{ // 海盗, 不是我们的
				    dialog.text = RandPhraseSimple("你想要什么? 走开。 ", "别挡我的路, 滚蛋。 ");
					link.l1 = RandPhraseSimple("你在做什么? ", "冷静点。 否则我会帮你冷静。 ");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("我想问你。 ", "请给我一点时间。 一个问题。 ");
					link.l2.go = "quests";//(转发到城市文件)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("我想讨论财务问题。 ", "关于财务... ");
							link.l3.go = "LoanForAll";//(转发到贷款生成器)
						}
					}
					break;
				}
			}
            if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				dialog.Text =NPCharRepPhrase(npchar,
                LinkRandPhrase("我是", "我的名字是", "你可以叫我")
                +GetFullName(npchar)
                +LinkRandPhrase("。 你想要什么? ", "。 我以前没见过你"
                +", 你是谁? ", "。 你是谁, 想从我这里得到什么? "),
        		LinkRandPhrase("问候, " + GetAddress_Form(NPChar) + "。 我的名字是" + GetFullName(npchar) + "。 你叫什么名字? ",
                "你好" + GetAddress_Form(NPChar) + "! 我是" + GetFullName(npchar) + "。 我能知道你的名字吗? ",
                "是的, " + GetAddress_Form(NPChar) + "。 你想要什么? 顺便说一下, 我的名字是" + GetFullName(npchar) + "。 你叫什么名字? "));
				Link.l1 = pcharrepphrase(
                LinkRandPhrase("该死的! ", "该死! ", "该死的你! ") + "是的, 我是船长" +GetFullName(Pchar)+ LinkRandPhrase(", 你没听说过我吗, 混蛋? ", ", 是海上最著名的海盗" + GetSexPhrase("", "女海盗") + "! ", ", 如果我错了就该死! "),
                LinkRandPhrase("我是" +GetFullName(Pchar)+ ", 船长。 ", "我的名字是" +GetFullName(Pchar)+ ".", "你可以叫我" +GetFullName(Pchar)+ "船长。 "));
				Link.l1.go = "Meeting";
				
				//==> 圣慈悲修道院来了检查员
				if (CheckAttribute(pchar, "questTemp.SantaMisericordia.ColonyZapret") && pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_town")
				{
					dialog.Text = LinkRandPhrase(LinkRandPhrase("整个城市都紧张不安 —皇家检查员费尔南多.德.阿拉米达来了。 你知道, 我在这里见过很多, 但这... 改变人们的不是悲伤, 而是他们如何应对悲伤。 据说他父亲去世后, 他变成了另一个人。 现在整个群岛都找不到比他更廉洁。 更... 无情的王室仆人了。 ", "看看‘圣慈悲修道院’! 据说国王亲自下令按特殊设计建造。 注意 —没有一丝划痕。 就像圣母玛利亚亲自保护它一样。 不过我听到传闻... 也许保护它的根本不是圣母。 ", "你知道他们多少次试图杀死费尔南多先生吗? 仅去年一年, 在公海上就有十二次袭击! 嗯, 有这么忠诚和训练有素的船员, 在主的保护下 —他也会挺过第十三次的! "), LinkRandPhrase("你听说了吗? 费尔南多.德.阿拉米达先生已经到了我们城市, 据说他现在就在街上的某个地方。 真想亲眼见见他... ", "这个费尔南多先生是个复杂的人。 有人说他是救世主, 为祖国清除污垢。 另一些人则私下说, 他父亲去世后, 他内心有什么东西破碎了, 很快我们都会哭泣。 但我告诉你: 不要怕他。 怕那些把他变成这样的人。 ", "这个费尔南多先生真英俊! 但你知道奇怪的是什么吗? 他好像谁都不在意。 只有职责和服务。 我听说有个女孩... 但在遇到某个牧师后, 他完全拒绝了世俗的享乐。 好像发了誓一样。 "), RandPhraseSimple(RandPhraseSimple("该死的检查员! 他在这里的时候, 城市就像死了一样。 没有贸易, 没有乐趣。 甚至呼吸似乎都得更轻。 你知道最可怕的是什么吗? 每个港口都是这样。 像时钟一样。 陛下不可能故意为我们发明这种折磨! ", "费尔南多先生又去了孤儿院。 捐赠慷慨, 祈祷数小时。 这样的好人应该成为那些被诅咒的贪污者的榜样! "), RandPhraseSimple("哈! ‘圣’费尔南多又关闭了所有妓院。 好吧, 没关系, 他很快就会起航, 它们又会重新开张。 ", "检... 检查员来了, 就是这样! 费尔南多.德.阿尔梅达先生, 或者他叫什么, 阿拉米达! 重要到总督本人都对他小心翼翼。 据说他看着你的眼睛, 就能立刻看到你所有的罪孽。 太可怕了! ")));
					link.l1 = "... ";
					link.l1.go = "exit";
				}
				//<== 圣慈悲修道院来了检查员
				//==> 贝丝女士在城市港口
				if (CheckAttribute(pchar, "questTemp.LadyBeth.CaptainInColony") && pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_town")
				{
					dialog.Text = findLedyBethRumour(npchar);
					link.l1 = "... ";
					link.l1.go = "exit";
				}
				//<== 贝丝女士在城市港口
			}
			else
			{
				link.l1 = "只是想谈谈这个城镇。 ";
				link.l1.go = "new question";
 				link.l2 = RandPhraseSimple("我有个问题要问你。 ", "我需要一些信息。 ");
				if (CheckCharacterItem(pchar, "CaptainBook"))				
				{
					if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
					{
						link.l2.go = "ShipLetters_7";// 生成器 "找到的文件"
					}
					else
					{
						link.l2.go = "quests";
					}	
				}
				else
				{
					link.l2.go = "quests";//(转发到城市文件)
				}	
				if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
	            {
	                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
	                {
						link.l3 = RandPhraseSimple("我想讨论财务问题。 ", "关于财务... ");
						link.l3.go = "LoanForAll";//(转发到贷款生成器)
					}
				}
				//杰森 --> 倒霉小偷生成器
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = "听着, 我希望你能帮助我。 我想买一个" + pchar.GenQuest.Device.Shipyarder.Type + ", 有人告诉我这个东西在你们镇上卖过。 嗯, 有人在街头市场卖过。 你知道什么吗? ";
					link.l16.go = "Device_Citizen";
				}
				// < —倒霉小偷生成器
				
				// 牧师任务生成器。 任务2。 战船 -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	            {
					link.l5 = LinkRandPhrase("你知道", "你是否知道", "你听说过") + "当地教堂最近被抢劫了吗? ");
					link.l5.go = "Citiz_GenQuest_Church_2_1";
				}
				// < —牧师任务生成器。 任务2.
				
                dialog.Text = NPCharRepPhrase(npchar,
		                PCharRepPhrase(LinkRandPhrase("啊, 是你" + GetFullName(Pchar)
                        + " " + GetSexPhrase("- 老朋友! ", "- 漂亮的人! ") + " ", "很高兴见到你, " + GetSexPhrase("老朋友! ", "漂亮的人! ") + " "
                        +Pchar.name, "哦, 那是" + GetSexPhrase("船长本人", "女船长本人") + " "
                         +GetFullName(Pchar))
						+RandPhraseSimple("。 我以为你死了! ", "。 也许" + GetSexPhrase("像往常一样喝醉了。 ", "有点醉了。 "))
						+LinkRandPhrase(" 继续, 你需要什么? ", " 这次是什么? ", " 又来烦我? "),
						LinkRandPhrase(TimeGreeting() + ", 船长", "日安, " + GetAddress_Form(NPChar) + " ", "问候, 船长") + GetFullName(Pchar)
						+LinkRandPhrase("。 我该如何帮助" + GetSexPhrase("这样有价值的男人", "这样有价值的女孩") + ", 像你这样的? ", "。 你为什么在这里? ", "。 你这次想知道什么? ")),             
                        PCharRepPhrase(LinkRandPhrase("你好, 船长", "问候, 啊, 是你" + GetAddress_Form(NPChar) + " ", "啊, 船长")
						+GetFullName(Pchar)
						+LinkRandPhrase(", 我以为我们再也不会见面了, 并且",
										 ", 我不会说很高兴见到你, 但是", ", 我看到你还活着, 真遗憾, 并且")
						+LinkRandPhrase(" 你想要什么? ", " 你为什么在这里? ", " 我如何帮助你? "),
						LinkRandPhrase(TimeGreeting() + ", " +GetFullName(Pchar)+ "船长。 我能帮你什么? ",
						"哦, 那是" +GetFullName(Pchar)+ "船长! 我能帮你什么? ",
						"问候, " + GetAddress_Form(NPChar) + " " + Pchar.lastname + "。 你想要什么吗? "))
						);  
	   			link.l6 = PCharRepPhrase(RandPhraseSimple("你的耳朵骗了你。 我得走了。 ", "不, 没什么, 我正要去酒馆。 "),
						RandPhraseSimple("好吧, 不管怎样。 祝你好运! ", "只是在城里走走。 再见。 "));
				link.l6.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "ShipLetters_7":
			dialog.text = "有什么问题吗? ";
			link.l1 = "文件上的这个名字你有印象吗? ";
			link.l1.go = "ShipLetters_8";
		break;
		
		case "ShipLetters_8":
			dialog.text = LinkRandPhrase("我他妈不在乎什么陌生文件, 而且我也不识字。 去找高利贷者吧, 据说他知道怎么读那些鬼画符。 ",
			"我不知道你在说什么, 问问镇上的其他市民吧, " +GetFullName(Pchar)+ "船长。 ", 
			"我甚至不知道怎么帮你, " +GetFullName(Pchar)+ "船长。 试试去找高利贷者谈谈, 他可能知道。 ");
			link.l1 = "我会很乐意接受你的建议! ";
			link.l1.go = "exit";
		break;
		
		case "Meeting":
		    dialog.Text  = NPCharRepPhrase(npchar, LinkRandPhrase("你没在撒谎吧, " +GetFullName(Pchar)+ "船长? ",
            "那又怎样, " +PChar.name+ "? ",
            "我会记住你的, " +GetFullName(Pchar)+ "。 ")
            + " 现在告诉我你想要什么? ",
            LinkRandPhrase("很高兴见到你, " +PChar.name+ "船长",
            "很高兴我们相遇, " + GetAddress_Form(NPChar) + " " + PChar.lastname,
            "很荣幸, " +PChar.name+ "船长") + "。 但我怀疑你不只是想知道我的名字, 对吧? ");
            link.l1 = PCharRepPhrase("我只是想问些关于这个你称之为‘城镇’的破地方的事。 ", "我想问你一些关于这个城镇的事。 ");
			link.l1.go = "new question";
            Link.l2 = RandPhraseSimple("我有个问题要问你。 ", "我需要一些信息。 ");
			if (CheckCharacterItem(pchar, "CaptainBook"))				
			{
				if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l2.go = "ShipLetters_7";// 生成器 "找到的文件"
				}
				else
				{
					Link.l2.go = "quests";
				}	
			}
			else
			{
					link.l2.go = "quests";//(转发到城市文件)
			}			
			if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
            {
                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
                {
					link.l3 = RandPhraseSimple("我想讨论财务问题。 ", "关于财务... ");
					link.l3.go = "LoanForAll";//(转发到贷款生成器)
				}
			}
			
			//杰森 --> 倒霉小偷生成器
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "听着, 我希望你能帮我。 我想买一个" + pchar.GenQuest.Device.Shipyarder.Type + ", 有人告诉我这东西在你们镇上卖过。 嗯, 有人在街上卖过。 你知道什么吗? ";
				link.l16.go = "Device_Citizen";
			}
			// < —倒霉小偷生成器

			// 牧师任务生成器。 任务 №2。 战船 -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	        {
				link.l5 = RandPhraseSimple("你知道", "你是否了解", "你听说过") + "当地教堂最近被抢劫了吗? ");
				link.l5.go = "Citiz_GenQuest_Church_2_1";
			}
			// < —牧师任务生成器。 任务 №2.
			Link.l6 = PCharRepPhrase(RandPhraseSimple("你的耳朵骗了你。 我得走了。 ", "没什么, 我正要去酒馆。 "),
            RandPhraseSimple("好吧, 没什么。 祝你好运! ", "只是在城里走走。 再见。 "));
			Link.l6.go = "exit";
		break;
		
		case "new question":
            dialog.text = NPCharRepPhrase(npchar,
		    PCharRepPhrase(LinkRandPhrase("哦, 见到你就像见到酒一样让我高兴, 想问什么就问吧。 ", "喜欢聊天吗, 船长? 我也是... 尤其是边喝朗姆酒边聊。 ", "是的, " +pchar.name+ "? "),
            RandPhraseSimple("你还想要什么? ", "我猜, " +PChar.name+ "船长, 你喜欢聊天? ")),
		    PCharRepPhrase(LinkRandPhrase("你还想要什么, " + GetAddress_Form(NPChar) + "? ", "我在听, 船长。 ", "我得走了, 所以快点问我, 船长。 "),
            LinkRandPhrase("我总是很高兴有愉快的陪伴, " + GetAddress_Form(NPChar) + " " + PChar.lastname + "。 说吧。 ",
            "是的, " + GetAddress_Form(NPChar) + "? ",
            "喜欢聊天吗, 船长? 我也是... ")));
			link.l1 = LinkRandPhrase ("这个镇上有什么谣言? ", "这片土地上有什么新闻? ", "陆地生活怎么样? ");
			link.l1.go = "rumours_towngirl";
			link.l2 = LinkRandPhrase("你能给我指路吗? ", "我找不到去一个地方的路... ", "帮我到一个地方... ");
			link.l2.go = "town";  //(转发到城市文件)
			link.l3 = RandPhraseSimple("我想知道人们怎么评价一个人。 ", "你知道人们怎么评价一个人吗? ");
			link.l3.go = "info"; //(转发到城市文件)
			link.l4 = RandPhraseSimple("我想更多地了解当地人。 ", "你能告诉我一些关于当地人的事吗? ");
			link.l4.go = "RumourAboutOwners";
			link.l5 = PCharRepPhrase(RandPhraseSimple("你的耳朵骗了你。 我得走了。 ", "没什么, 我正要去酒馆。 "),
            RandPhraseSimple("好吧, 没什么。 祝你好运! ", "只是在城里走走。 再见。 "));
			link.l5.go = "exit";
		break;
		
		case "RumourAboutOwners":
			Dialog.Text = "你对谁感兴趣? ";
			if(GetCharacterIndex(NPChar.city + "_Mayor") != -1)
			{
				link.l1 = "想更多地了解总督。 ";
				link.l1.go = "RumourAboutOwners_Mayor";
			}
			if(GetCharacterIndex(NPChar.city + "_TavernKeeper") != -1)
			{
				link.l2 = "想更多地了解当地酒馆的老板。 ";
				link.l2.go = "RumourAboutOwners_TavernKeeper";
			}
			if(GetCharacterIndex(NPChar.city + "_ShipYarder") != -1)
			{
				link.l3 = "想更多地了解当地造船厂的师傅。 ";
				link.l3.go = "RumourAboutOwners_ShipYarder";
			}
			if(GetCharacterIndex(NPChar.city + "_Trader") != -1)
			{
				link.l4 = "想更多地了解当地商店的老板。 ";
				link.l4.go = "RumourAboutOwners_Trader";
			}
			link.l9 = "没什么。 忘了吧。 ";
			link.l9.go = "exit";
		break;
			
		case "RumourAboutOwners_TakeRumour":
			sTemp = sRumourAboutOwners_CityRumour(NPChar.City, NPChar.RumourOwnerType);
			Dialog.Text = sTemp;
			link.l1 = "谢谢。 ";
			link.l1.go = "exit";
			//这里可以根据任务检查得到了哪个传闻
			DeleteAttribute(PChar, "QuestTemp.RumoursAboutOwners");
		break;
		
		//杰森 --> 倒霉小偷生成器
		case "Device_Citizen":
           dialog.text = "嗯, " + pchar.GenQuest.Device.Shipyarder.Type + "? 从没听说过... 我在这里住了很久, 从没见过那样的东西。 ";
			link.l1 = "嗯, 那是一种造船工具, " + pchar.GenQuest.Device.Shipyarder.Describe + "。 镇上有人卖过类似的东西吗? 或者有人带着它走来走去, 你注意到了吗? ";
			link.l1.go = "Device_Citizen_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Citizen_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 3 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 6 && npchar.sex != "woman")
			{
				dialog.text = "嗯... 是的, 几个小时前我看到一个男人拿着那样的东西。 他在街上走着。 那是个有趣的工具。 ";
				link.l1 = "他长什么样, 要去哪里? 我真的需要那样的东西。 ";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "不, 我没见过那样的东西。 ";
				link.l1 = "我明白了。 那我继续问别人。 ";
				link.l1.go = "exit";
			}
		break;
		
		//=================== 牧师任务节点。 寻找抢劫者 (任务 №2) ==================
		case "Citiz_GenQuest_Church_2_1":
			if(rand(3) != 1)
			{
				dialog.text = LinkRandPhrase("不, 我对此一无所知。 ", "不, 我得走了。 ", "我什么都不知道。 ");
					link.l1 = LinkRandPhrase("好吧, 谢谢。 ", "我明白了, 谢谢。 ", "好吧, 打扰了。 ");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple("我对此一无所知, 但你可以试着问问酒馆里的常客, 他们肯定会告诉你更多。 ", "我什么都不能告诉你, 去问酒馆里的人吧。 ");
				link.l1 = "谢谢你的建议。 ";
				link.l1.go = "exit";
			}
			NPChar.GenQuest.ChurchQuest_2.AskedPeople = true;
		break;		
		
		//关于出鞘武器的评论
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "听着, 作为这个城镇的公民, 我要求你把刀收起来。 ", "听着, 作为这个城镇的公民, 我要求你把刀收起来。 ");
				link.l1 = LinkRandPhrase("好吧。 ", "如你所愿。 ", "如你所说... ");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "拿着武器跑的时候要小心。 我会紧张的... ", "我不喜欢有陌生男人拿着出鞘的武器走在我前面。 这让我害怕... ");
				link.l1 = RandPhraseSimple("我知道了。 ", "别担心。 ");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

	}
}

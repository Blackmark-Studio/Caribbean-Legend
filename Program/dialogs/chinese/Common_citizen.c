// boal 25/04/04 市民通用对话
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // 调用城市对话 -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // 调用城市对话 <--
    ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06
    int iTest, iTemp;
    iTest = FindColony(NPChar.City); // 城市
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
            /*if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				dialog.text = RandPhraseSimple("间谍? 卫兵! ", "警报! 有入侵者! ");
				link.l1 = "闭嘴。 我这就走。 ";
				link.l1.go = "fight";
				break;
			}*/
			
			if (sti(NPChar.nation) == PIRATE)
			{
				if (sti(rColony.HeroOwn) == true) // 我们的市民
				{
				    dialog.text = RandPhraseSimple("据说您就是统治这座城镇的人, " + GetSexPhrase("先生", "小姐") + "。 ", "真荣幸, 城主亲自向我询问。 ");
					link.l1 = RandPhraseSimple("我改变主意了。 ", "我只是在探索这座城镇。 再见。 ");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("我有个问题想问您。 ", "我需要一些信息。 ");
					link.l2.go = "quests";//(转发到城市文件)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("我想谈谈生意。 ", "关于财务方面... ");
							link.l3.go = "LoanForAll";//(转发到贷款生成器)
						}
					}
					break;
				}
				else
				{ // 海盗, 非我方
				    dialog.text = RandPhraseSimple("你想要什么? 走开。 ", "别挡路, 滚蛋! ");
					link.l1 = RandPhraseSimple("嘿, 别嚷嚷了, 好吗? ", "冷静点, 不然你会后悔的! ");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("我有个问题想问您。 ", "请稍等, 我有个问题。 ");
					link.l2.go = "quests";//(转发到城市文件)
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple("我想谈谈生意。 ", "关于财务方面... ");
							link.l3.go = "LoanForAll";//(转发到贷款生成器)
						}
					}
					break;
				}
			}
            if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";

                // homo 05/08/06
				dialog.Text =NPCharRepPhrase(npchar,
                                LinkRandPhrase("我的名字是 ", "我的名字是 ", "你可以叫我 ")
                                +GetFullName(npchar)
                                +LinkRandPhrase("。 你需要什么? ", "。 我还没 "
                                +NPCharSexPhrase(NPChar, "在这里见过你", "在那里见过你")
                                +", 你是谁? ", "。 你是谁, 需要我做什么? "),

        		                LinkRandPhrase("问候您, " + GetAddress_Form(NPChar) + "。 我叫" + GetFullName(npchar) + "。 您是? ",
                                 "您好, " + GetAddress_Form(NPChar) + "! 我是" + GetFullName(npchar) + "。 能告诉我您的名字吗? ",
                                 "是的, " + GetAddress_Form(NPChar) + "。 你想要什么? 顺便说一下, 我叫" + GetFullName(npchar) + "。 你呢? "));

				Link.l1 = pcharrepphrase(
                                LinkRandPhrase("哎呀! ", "该死的! ", "真该死! ") + "是的, 我是" +GetFullName(Pchar)+ LinkRandPhrase("船长, 你真的没听说过我" + NPCharSexPhrase(NPChar, ", 无赖? ", "? "), ", 是这片海域最臭名昭著的海盗! ", ", 如果不是的话我愿下地狱! "),
                                LinkRandPhrase("我是" +GetFullName(Pchar)+ "船长。 ", "我的名字是" +GetFullName(Pchar)+ "。 ", "你可以叫我" +GetFullName(Pchar)+ "船长"));

                //LinkRandPhrase("我是" +GetFullName(Pchar)+ "船长。 ", "我的名字是" +GetFullName(Pchar)+ "。 ", "你可以叫我" +GetFullName(Pchar)+ "船长");
				Link.l1.go = "Meeting";
			}
			else
			{
				if(rand(5) == 1 && NPChar.sex == "woman" && !CheckAttribute(NPChar, "CitizenFindItem.NoQuest") && !CheckAttribute(PChar, "GenQuest.CitizenFindItem.StartQuest") && CheckAttribute(NPChar, "City"))
				{
					dialog.Text = "船长, 你能帮我个忙吗? ";
					link.l1 = LinkRandPhrase("抱歉, 不行。 我没多少时间。 ", "抱歉, 我不能。 太忙了。 ", "不, 我不能。 我有紧急的事情要处理。 ");
					link.l1.go = "CitizenFindItem_NoQuest";
					link.l2 = LinkRandPhrase("当然可以。 怎么了? ", "是的, 我会帮你。 告诉我更多关于这件事的情况。 ", "告诉我更多关于这件事的情况... ");
					link.l2.go = "CitizenFindItem_1";
					NextDiag.TempNode = "First time";
					break;
				}
				
				if(CheckAttribute(PChar, "GenQuest.CitizenFindItem.CitizenID") && PChar.GenQuest.CitizenFindItem.CitizenID == NPChar.ID && CheckCharacterItem(PChar, "DOjeronRing"))
				{
					dialog.Text = "是的, 船长, 我在听。 ";
					link.l1 = NPChar.name+ ", 我找到你的结婚戒指了。 ";
					link.l1.go = "CitizenFindItem_Complete_1";
					break;
				}
			
				link.l1 = PCharRepPhrase("我想了解更多关于这个城镇的信息。 ", "告诉我关于这个城镇的情况。 ");
				link.l1.go = "new question";
 				link.l2 = RandPhraseSimple("我有个问题想问你。 ", "我需要信息。 ");
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
						link.l3 = RandPhraseSimple("我想谈谈生意。 ", "关于财务方面... ");
						link.l3.go = "LoanForAll";//(转发到贷款生成器)
					}
				}
				// --> 市长任务生成器, 在街上寻找间谍。 eddy
				if (CheckAttribute(pchar, "GenQuest.SeekSpy.City") && pchar.location == (npchar.city + "_town"))
	            {
					link.l4 = NPCharSexPhrase(npchar, LinkRandPhrase("等等! 告诉我你是谁 --马上! 我受" + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + "总督的委托寻找敌方间谍! ", 
						"站住! 我受" + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + "总督的命令行事。 我在城里搜寻敌对特工。 ", 
						"停下, 朋友! 当地总督" + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname + "想在镇上找到一名间谍。 "), 
						LinkRandPhrase("等等, 女士! 告诉我你是谁 --马上! 我受" + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + "总督的委托寻找敌方间谍! ", 
						"女士, 我必须拘留你! 我受" + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + "总督的命令行事。 我在城里搜寻敌对特工", 
						"站住, 美女! 当地总督" + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname + "想在镇上找到一名间谍... "));
					link.l4.go = "SitySpy";
				}
				// <—— 市长任务生成器, 在街上寻找间谍
				
				//Jason --> 失败的小偷生成器
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = "也许你能给我一些建议。 我想购买" + pchar.GenQuest.Device.Shipyarder.Type + ", 有人告诉我在你们镇上有卖。 嗯, 有人在街上卖这个。 你知道什么吗? ";
					link.l16.go = "Device_Citizen";
				}
				// <—— 失败的小偷生成器
				
				// 神父任务生成器。 任务#2。 Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	            {
					link.l5 = LinkRandPhrase("你知道", "你听说", "你听说") + "最近当地教堂被袭击了吗? ");
					link.l5.go = "Citiz_GenQuest_Church_2_1";
				}
				// <—— 神父任务生成器。 任务#2.
				
                dialog.Text = NPCharRepPhrase(npchar,
		                PCharRepPhrase(LinkRandPhrase("哦, 是你啊, " + GetFullName(Pchar)
                        +" "+ GetSexPhrase(", 老恶棍", "- 厉害的女士") + "", "很高兴再次见到你, " + GetSexPhrase("老伙计", "美女") + " "
                        +Pchar.name, "哦, 是老" + GetSexPhrase("船长", "女士") + " "
                         +GetFullName(Pchar))
                                        +LinkRandPhrase("。 我以为你死了! ", "。 当然, " + GetSexPhrase("还是老样子喝得烂醉。 ", "已经醉了。 ") + "", "。 我看你还自由着! ")
                                        +LinkRandPhrase(" 那么, 说吧 --你需要什么? ", " 这次你需要什么? ", " 你又来烦我了? "),
                                        LinkRandPhrase(TimeGreeting() + ", 船长 ", "你好, " + GetAddress_Form(NPChar) + " ", "向你致敬, 船长 ") + GetFullName(Pchar)
                                        +LinkRandPhrase("。 像" + GetSexPhrase("这样勇敢的绅士", "这样时髦的女士") + "会需要什么? 你可能需要我做什么吗? ", "。 你为了什么而来? ", "。 这次你想知道什么? ")

                                        ),
                                        
                        PCharRepPhrase(LinkRandPhrase("你好, 船长 ", "你好。 哦, 是你 " + GetAddress_Form(NPChar) + " ", "哦, 船长 ")
                                        +GetFullName(Pchar)
                                        +LinkRandPhrase(", 我以为" + NPCharSexPhrase(NPChar, " ", " ") + "我们再也不会见面了, ",
                                                         ", 不能说很高兴" + NPCharSexPhrase(NPChar, " ", " ") + "见到你, 但是", ", 我看你还活着。 真遗憾。 那么")
                                        +LinkRandPhrase(" 你需要什么? ", " 你为了什么而来? ", " 我能" + NPCharSexPhrase(NPChar, "帮你什么? ", "帮你什么? ")),
                                        LinkRandPhrase(TimeGreeting() + ", 船长" +GetFullName(Pchar)+ "。 我能帮你什么? ",
                                        "哦, 这不是" + GetSexPhrase("","") + "船长" +GetFullName(Pchar)+ "! 你这次想知道什么? ",
                                        "你好, " + GetAddress_Form(NPChar) + " " + Pchar.lastname + "。 你想要什么? "))
                                        );                         
	   			link.l6 = PCharRepPhrase(RandPhraseSimple("不, 你听错了。 我现在就走。 ", "不, 没什么 --我正要去酒馆。 "),
                                        RandPhraseSimple("不, 没什么。 祝你好运! ", "只是四处看看。 再见。 "));
				link.l6.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "ShipLetters_7":
			dialog.text = "什么问题? ";
			link.l1 = "这些文件里的名字你有印象吗? ";
			link.l1.go = "ShipLetters_8";
		break;
		
		case "ShipLetters_8":
			dialog.text = LinkRandPhrase("我不关心不熟悉的文件。 而且, 我不识字。 去找放高利贷的吧, 那个魔鬼肯定知道怎么读写。 ",
										"我完全不知道你在说什么。 问问镇上的人吧, " +GetFullName(Pchar)+ "船长。 ", 
										"我真的不知道怎么帮你, " +GetFullName(Pchar)+ "船长。 试试问问放高利贷的 --也许他知道。 ");
			link.l1 = "我会很高兴听从你的建议! ";
			link.l1.go = "exit";
		break;
		
		case "Meeting":
		    dialog.Text  = NPCharRepPhrase(npchar, LinkRandPhrase("但你不是在撒谎吗, " +GetFullName(Pchar)+"船长? ",
                                                                    "那又怎样, " +PChar.name+"? ",
                                                                    "我会记住你的, " + GetFullName(Pchar)+"."),
                                                                     +"现在, 你需要什么? ",
                                                    LinkRandPhrase("很高兴认识你, " +PChar.name+ "船长",
                                                                    "很高兴"+NPCharSexPhrase(NPChar, " ", " ")+"认识你, " + GetAddress_Form(NPChar) + " " + PChar.lastname,
                                                                     "很高兴认识你, " +PChar.name+ "船长") + "。 但我猜, 你不只是来知道我的名字吧? ");

            link.l1 = PCharRepPhrase("我想" + GetSexPhrase("","") + "了解一下这个被你称为城镇的地方! ", "我想" + GetSexPhrase("","") + "了解一下这个城镇。 ");
			link.l1.go = "new question";
            Link.l2 = RandPhraseSimple("我有个问题想问你。 ", "我需要信息。 ");
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
					link.l3 = RandPhraseSimple("我想谈谈生意。 ", "关于财务方面... ");
					link.l3.go = "LoanForAll";//(转发到贷款生成器)
				}
			}
			
			//Jason --> 失败的小偷生成器
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "也许你能给我一些建议。 我想购买" + pchar.GenQuest.Device.Shipyarder.Type + ", 有人告诉我在你们镇上有卖。 嗯, 有人在街上卖这个。 你知道什么吗? ";
				link.l16.go = "Device_Citizen";
			}
			// <—— 失败的小偷生成器
			
			// --> 市长任务生成器, 在街上寻找间谍。 eddy
			if (CheckAttribute(pchar, "GenQuest.SeekSpy.City") && pchar.location == (npchar.city + "_town"))
	        {
				link.l4 = NPCharSexPhrase(npchar, LinkRandPhrase("等等! 告诉我你是谁 --马上! 我受" + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + "总督的委托寻找敌方间谍! ", 
					"站住! 我受" + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + "总督的命令行事。 我在城里搜寻敌对特工。 ", 
					"停下, 朋友! 当地总督" + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname + "想在镇上找到一名间谍。 "), 
					LinkRandPhrase("等等, 女士! 告诉我你是谁 --马上! 我受" + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + "总督的委托寻找敌方间谍! ", 
					"女士, 我必须拘留你! 我受" + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + "总督的命令行事。 我在城里搜寻敌对特工。 ", 
					"站住, 美女! 当地总督" + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname + "想在镇上找到一名间谍... "));
				link.l4.go = "SitySpy";
			}
			// <—— 市长任务生成器, 在街上寻找间谍
			// 神父任务生成器。 任务#2。 Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	        {
				link.l5 = LinkRandPhrase("你知道", "你听说", "你听说") + "最近当地教堂被袭击了吗? ");
				link.l5.go = "Citiz_GenQuest_Church_2_1";
			}
			// <—— 神父任务生成器。 任务#2.
			
			Link.l6 = PCharRepPhrase(RandPhraseSimple("不, 你听错了。 我现在就走。 ", "不, 没什么 --我正要去酒馆。 "),
                                        RandPhraseSimple("不, 没什么。 祝你好运! ", "只是四处看看。 再见。 "));
			Link.l6.go = "exit";
		break;
		
		case "new question":
            dialog.text = NPCharRepPhrase(npchar,
		                PCharRepPhrase(LinkRandPhrase("哦, 是的, 我几乎和喜欢一杯酒一样高兴见到你。 想问什么就问吧。 ", "你喜欢说话, 船长? 嗯, 我也是... 尤其是边喝朗姆酒边聊。 ", "是的, " +pchar.name+ "? "),
                                        LinkRandPhrase("你需要什么? ", "我知道了, " +PChar.name+ "船长。 你很" + GetSexPhrase("","") + "健谈。 ", "你已经让我厌倦了" + GetSexPhrase("","") + "你的问题, 船长。 最好帮我拿朗姆酒。 ")),
		                PCharRepPhrase(LinkRandPhrase("你想知道什么, " + GetAddress_Form(NPChar) + "? ", "我在听你说, 船长。 ", "我得走了, 所以请快点, 船长。 "),
                                        LinkRandPhrase("总是很高兴" + NPCharSexPhrase(NPChar, " ", " ") + "有好伙伴, " + GetAddress_Form(NPChar) + " " + PChar.lastname + "。 说吧。 ",
                                                        "是的, " + GetAddress_Form(NPChar) + "? ",
                                                        "你喜欢聊天, 船长? 嗯, 我也是... "))
                            );

            // homo 25/06/06
			link.l1 = LinkRandPhrase ("当地酒馆里流行什么八卦? ",
                                    "这些地方发生了什么事? ",
                                    "岸上有什么新鲜事? ");
			link.l1.go = "rumours_citizen";
			link.l2 = LinkRandPhrase("你能告诉我怎么走吗? ", "我找不到去某个地方的路... ", "你能指指路吗... ? ");
			link.l2.go = "town";  //(转发到城市文件)
			if(Rand(1)==0)
			{
				link.l3 = LinkRandPhrase("我想知道人们对某个人的评价。 ", "你不知道人们对某个人的评价吗? ", "我想了解一下当地人。 ");
				if(rand(1) == 0 || PChar.location == "LaVega_Town" || PChar.location == "PuertoPrincipe_town"
				|| PChar.location == "Pirates_town" || PChar.location == "Panama_town" || !CheckAttribute(NPChar, "City"))
				{
					link.l3.go = "info"; //(转发到城市文件)
				}
				else
				{
					link.l3.go = "RumourAboutOwners"; // Warship。 换了种方式 - 每个城市的居民都会有自己的对话。 
				}
			}
			else
			{
				link.l3 = "请告诉我更多关于你们殖民地的情况。 ";
				link.l3.go = "colony";
			}
            link.l4 = RandPhraseSimple("我有重要的事! ", "我和你有生意。 ");
			link.l4.go = "quests";  //(转发到城市文件)
			link.l5 = PCharRepPhrase(RandPhraseSimple("不, 你听错了。 我现在就走。 ", "不, 没什么 --我正要去酒馆。 "),
                                        RandPhraseSimple("不, 没什么。 祝你好运! ", "只是四处看看。 再见。 "));
			link.l5.go = "exit";
		break;
		
		case "RumourAboutOwners":
			Dialog.Text = "你想了解谁? ";
			if(GetCharacterIndex(NPChar.city + "_Mayor") != -1)
			{
				link.l1 = "关于总督。 ";
				link.l1.go = "RumourAboutOwners_Mayor";
			}
			if(GetCharacterIndex(NPChar.city + "_TavernKeeper") != -1)
			{
				link.l2 = "关于当地酒馆的老板。 ";
				link.l2.go = "RumourAboutOwners_TavernKeeper";
			}
			if(GetCharacterIndex(NPChar.city + "_ShipYarder") != -1)
			{
				link.l3 = "关于港口负责人。 ";
				link.l3.go = "RumourAboutOwners_ShipYarder";
			}
			if(GetCharacterIndex(NPChar.city + "_Trader") != -1)
			{
				link.l4 = "关于当地商店的老板。 ";
				link.l4.go = "RumourAboutOwners_Trader";
			}
			link.l9 = "没关系, 忘了吧。 ";
			link.l9.go = "exit";
			break;
			
		case "RumourAboutOwners_TakeRumour":
			sTemp = sRumourAboutOwners_CityRumour(NPChar.City, NPChar.RumourOwnerType);
			Dialog.Text = sTemp;
			link.l1 = "谢谢。 ";
			link.l1.go = "exit";
			// 这里可以根据任务检查, 触发了哪个传闻
			DeleteAttribute(PChar, "QuestTemp.RumoursAboutOwners");
			break;
		
		case "colony":
			dialog.text = LinkRandPhrase("老实说, 我知道的不多, 但还是可以告诉你一些。 ",
                           "你对我们的殖民地哪方面感兴趣? ", "当然。 你想知道什么? ");
            switch(Rand(1))
			{
				case 0:
					link.l1 = "这是个什么样的城镇? ";
					link.l1.go = "colony_town";
				break;

				case 1:
					link.l1 = "你对保卫城镇的堡垒了解多少? ";
					link.l1.go = "fort";
				break;
            }
			link.l2 = "我们换个话题吧。 ";
			link.l2.go = "new question";
		break;
	  // 待办
		case "colony_town":
            dialog.text = "你在开玩笑吗? 或者闹着玩? 看看你屏幕的右上角。 ";
			link.l1 = "是的, 我的错。 ";
		    link.l1.go = "exit";
		break;
		
		case "fort":
            dialog.text = "我对此一无所知。 ";
			link.l1 = "可惜。 ";
		    link.l1.go = "exit";
		break;
		
		//Jason --> 失败的小偷生成器
		case "Device_Citizen":
           dialog.text = "嗯, " + pchar.GenQuest.Device.Shipyarder.Type + "? 以前从没听说过... 它到底是什么? 我这辈子" + NPCharSexPhrase(npchar, "","") + "都没听说过这种东西。 ";
			link.l1 = "嗯, 这是一个造船工具, " + pchar.GenQuest.Device.Shipyarder.Describe + "。 有人在镇上卖过这种东西吗? 也许。 你注意到有人身上带着这种东西吗? ";
			link.l1.go = "Device_Citizen_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Citizen_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 3 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 6 && npchar.sex != "woman")
			{
				dialog.text = "嗯... 是的, 我想我见过一个人带着类似的东西。 他几个小时前还在那边拿着它。 当然, 是个有趣的装置。 ";
				link.l1 = "他长什么样, 去哪里了? 我非常需要那个工具。 ";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "不, 我没见过那样的东西。 ";
				link.l1 = "我知道了。 好吧 --该四处问问了! ";
				link.l1.go = "exit";
			}
		break;
		
		//============================ 市长生成器。 在街上搜寻间谍的任务 ============================
		case "SitySpy":
			dialog.text = NPCStringReactionRepeat(NPCharSexPhrase(npchar, "这和我有什么关系? 我是本地人! ", "你为什么拿这个来烦我? 我住在这个城市, 对此一无所知! "), 
				NPCharSexPhrase(npchar, "你又想从我这里得到什么? 我不是间谍, 不是已经告诉过你了吗? ! ", "我不是已经告诉过你了吗? 我是本地人! "), 
				NPCharSexPhrase(npchar, "亲爱的, 又是你! 别烦我 --我是本地人! ", "你为什么又用你那些愚蠢的问题来烦我? "), 
				NPCharSexPhrase(npchar, "又是你! 这太过分了! ", "听着, 别烦我了, 好吗? 求你了! "), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("谁能证实你的说法? ", "哦, 对不起 --我已经问过你了... ",
                      "抱歉, 人太多了... ", "好了, 好了... ", npchar, Dialog.CurrentNode);
		    link.l1.go = DialogGoNodeRepeat("SitySpy_1", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
			// ==> 选择确认者
			int num = FindNearCharacters(npchar, 20.0, -1.0, -1.0, 1.0, false, true);
			if(num > 0)
			{
				for(i = 0; i < num; i++)
				{
					iTemp = chrFindNearCharacters[i].index;
					if (CheckAttribute(&characters[iTemp], "CityType"))
					{
						if(characters[iTemp].CityType == "soldier" || characters[iTemp].CityType == "citizen")
						{
							break;
						}
					}
				}
				pchar.GenQuest.SeekSpy.Idx = chrFindNearCharacters[i].index; // 选中的索引
				pchar.GenQuest.SeekSpy.Type = characters[sti(pchar.GenQuest.SeekSpy.Idx)].chr_ai.type; // 帮助者类型
				pchar.GenQuest.SeekSpy.BaseIdx = npchar.index; // 索引
			}
		break;
		case "SitySpy_1":
			if (sti(pchar.GenQuest.SeekSpy.Idx) == -1 || sti(pchar.GenQuest.SeekSpy.Idx) == 1) // 以防万一
			{
				dialog.text = "任何人都可以! 听着, 你为什么一直纠缠我? ! 如果你有问题, 去找总督解决! ",
				link.l1 = "嗯... 最好不要为这种小事打扰他。 我相信你。 ";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "这个镇上的任何人都可以! " + NPCharSexPhrase(npchar, GetFullName(&characters[sti(pchar.GenQuest.SeekSpy.Idx)]) + "就可以, 比如, 现在" + NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.Idx)], "他", "她") + "就在那里。 ",
				"哦, 主啊, 比如, " + NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.Idx)], GetAddress_FormToNPC(NPChar) + " " + characters[sti(pchar.GenQuest.SeekSpy.Idx)].lastname, GetFullName(&characters[sti(pchar.GenQuest.SeekSpy.Idx)])) + "就可以。 ");				
			link.l1 = "好吧, 那我们看看。 ";
		    link.l1.go = "SitySpy_2";
			sld = &characters[sti(pchar.GenQuest.SeekSpy.Idx)];
			sld.dialog.currentnode = "SeekSpy_Checking";
			pchar.GenQuest.SeekSpy.time = 4.0; // 跑过去的时间
			if (sld.chr_ai.type == "merchant") pchar.GenQuest.SeekSpy.time = 0.0; // 商人立刻讨价还价
            LAi_SetActorTypeNoGroup(sld);
		break;
		case "SitySpy_2":
			sld = &characters[sti(pchar.GenQuest.SeekSpy.Idx)];
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorTurnToCharacter(npchar, sld);
			LAi_ActorDialog(sld, pchar, "", stf(pchar.GenQuest.SeekSpy.time), 0); 
			DialogExit();
		break;
		//=================== 市长任务节点。 在街上寻找间谍, 询问证人 ==================
		case "SeekSpy_Checking":
			dialog.text = "是的, " + NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.BaseIdx)], "确实是本地人。 ", "确实是本地人。 ");
			link.l1 = RandPhraseSimple("我知道" + GetSexPhrase("","") + "了。 谢谢你的帮助。 ", "清楚了。 谢谢你的帮助。 ");
			link.l1.go = "SeekSpy_Checking_1";
		break;
		case "SeekSpy_Checking_1":
			switch (pchar.GenQuest.SeekSpy.Type)
			{
				case "guardian": LAi_SetGuardianTypeNoGroup(npchar); break;
				case "patrol":   LAi_SetPatrolTypeNoGroup(npchar);   break;
				case "citizen":  LAi_SetCitizenTypeNoGroup(npchar);  break;
				case "merchant": LAi_SetMerchantTypeNoGroup(npchar); break;
			}
			LAi_SetCitizenTypeNoGroup(&characters[sti(pchar.GenQuest.SeekSpy.BaseIdx)]);
			NextDiag.CurrentNode = "First Time";
			DialogExit();
		break;
		
		// 寻找结婚戒指的迷你任务 -->
		case "CitizenFindItem_1":
			dialog.text = "你看, 昨天我出城散步, 弄丢了我的结婚戒指... " + GetSexPhrase("船长, 你能帮我找找吗? ", "女士, 请帮我找找吧! ") + "";
			link.l1 = "当然" + GetSexPhrase("可以! 为了你这样漂亮的女孩, 我什么都愿意做! ", "我会帮你。 教会教导我们要帮助有需要的人。 ") + "";
			link.l1.go = "CitizenFindItem_2";
			link.l2 = LinkRandPhrase("不, 我不能。 对不起。 我有太多事情要做。 ", "对不起, 我不能。 我刚想起来" + GetSexPhrase("","") + ", 我还有没完成的事... ", "我时间很少, 所以不能帮你... ");
			link.l2.go = "CitizenFindItem_NoQuest";
			break;
			
		case "CitizenFindItem_2":
			dialog.text = "" + GetSexPhrase("船长", "女士") + ", 那太好了! 请帮我找到这枚戒指, 我丈夫再过" + sti(NPChar.LifeDay) + "天就到了, 我不想让他看到我没有结婚戒指。 ";
			link.l1 = RandPhraseSimple("你说在哪里弄丢的? ", "那你到底在哪里弄丢的? ");
			link.l1.go = "CitizenFindItem_3";
		break;
			
		case "CitizenFindItem_3":
			dialog.text = "就在城门外... ";
			link.l1 = "好吧, 那我现在就去找... ";
			link.l1.go = "CitizenFindItem_4";
		break;
			
		case "CitizenFindItem_4":
			dialog.text = "好的, 拜托了。 快点 --记住你只有" + sti(NPChar.LifeDay) + "天时间。 ";
			link.l1 = "我记住了。 ";
			link.l1.go = "exit";
			PChar.GenQuest.CitizenFindItem.StartQuest = true;
			PChar.GenQuest.CitizenFindItem.City = NPChar.City;
			PChar.GenQuest.CitizenFindItem.CitizenID = NPChar.ID;
				
			sCity = NPChar.City + "_ExitTown";
				
			//sTemp = "randitem" + (rand(1)+1); // 也就是说, 可能根本找不到。 这很好。 
			sTemp = "randitem1";
			Log_TestInfo("戒指将在定位器 - " + sTemp);
			PChar.GenQuest.CitizenFindItem.ItemLocator = sTemp;
			ChangeItemDescribe("DOjeronRing", "itmdescr_WeddingRing");			
			items[FindItem("DOjeronRing")].Name = "itmname_WeddingRing";
			items[FindItem("DOjeronRing")].City = XI_ConvertString("Colony" + NPChar.City + "Gen");
			SetFunctionTimerCondition("CitizenFindItemMiniQuest_Timer", 0, 0, sti(NPChar.LifeDay), false);
			PChar.GenQuestRandItem.(sCity).(sTemp) = "DOjeronRing";
			SetGameModeCondition("CitizenFindItemMiniQuest_CheckItem");			
		break;
			
		case "CitizenFindItem_NoQuest":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			NPChar.CitizenFindItem.NoQuest = true; // 这个女孩不会再给任务了
		break;
			
		case "CitizenFindItem_Complete_1":
			dialog.text = "" + GetSexPhrase("船长", "小姐") + "! 我太高兴了! 我该怎么感谢你? ";
			link.l1 = "哦, 不用感谢 --我这么做完全是无私的。 ";
			link.l1.go = "CitizenFindItem_Complete_2";
			link.l2 = "几百比索肯定不会有什么损失... ";
			link.l2.go = "CitizenFindItem_Complete_3";
			RemoveItems(PChar, "DOjeronRing", 1);
			DeleteAttribute(PChar, "GenQuest.CitizenFindItem");
			NPChar.CitizenFindItem.NoQuest = true;
			PChar.Quest.CitizenFindItemMiniQuest_Timer.over = "yes";
			BackItemDescribe("DOjeronRing");
			items[FindItem("DOjeronRing")].Name = "itmname_DOjeronRing";
			DeleteAttribute(&items[FindItem("DOjeronRing")], "City");
		break;
			
		case "CitizenFindItem_Complete_2":
			dialog.text = "哦, " + GetSexPhrase("船长, 你真是个高尚的人", "小姐, 你真高尚") + "! 我一定会在教堂为你祈祷! 再见... ";
			link.l1 = "再见, " + NPChar.name+ ".";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(PChar,"nobility" ,1);
			AddCharacterExpToSkill(PChar, "Leadership", 10);
			AddCharacterExpToSkill(PChar, "Fortune", 10);
		break;
			
		case "CitizenFindItem_Complete_3":
			iTemp = (rand(3)+1)*50;
			dialog.text = "哦, 当然。 给你 --" + FindRussianMoneyString(iTemp) + "。 这是我所有的钱。 请收下这钱... 再见。 ";
			link.l1 = "再见, " + GetFullName(NPChar) + ".";
			link.l1.go = "exit";
			AddMoneyToCharacter(PChar, iTemp);
		break;
		// <—— 寻找结婚戒指的迷你任务
		
		//=================== 神父任务节点。 寻找抢劫者 (任务#2)==================
		case "Citiz_GenQuest_Church_2_1":
			if(rand(3) != 1)
			{
				dialog.text = LinkRandPhrase("不, 我对此一无所知。 ", "在这方面我什么都不知道。 ", "我什么都不知道。 ");
					link.l1 = LinkRandPhrase("好吧, 谢谢。 ", "我知道了, 谢谢。 ", "好的, 请原谅我。 ");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("我对此一无所知, 但你可以问问酒馆的顾客 --他们肯定会告诉你一些事情。 ", "我不能告诉你什么。 去酒馆问问。 ", "我不知道具体的事情, 但我听说酒馆里有传言。 ");
				link.l1 = "好吧, 至少这是个线索。 ";
				link.l1.go = "exit";
			}
			
			NPChar.GenQuest.ChurchQuest_2.AskedPeople = true;
		break;		
		
		// 关于露出武器的注意事项
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "听着 --作为这个城镇的市民, 我必须请你不要带着出鞘的刀刃走动。 ", "听着 --作为这个城镇的市民, 我必须请你不要带着出鞘的刀刃走动。 ");
				link.l1 = LinkRandPhrase("好的。 ", "好的。 ", "如你所说... ");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "拿着武器到处跑的时候悠着点" + GetSexPhrase("伙计", "姑娘") + "。 这让我紧张... ", "我不喜欢" + GetSexPhrase("男人", "任何人") + "拿着武器走动。 这吓到我了... ");
				link.l1 = RandPhraseSimple("知道了。 ", "我会收起来。 ");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

	}
}
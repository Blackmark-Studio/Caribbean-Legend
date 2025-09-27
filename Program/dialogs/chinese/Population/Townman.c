//杰森市民通用对话
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
    ref NPChar, sld;
    aref Link, NextDiag;

    DeleteAttribute(&Dialog,"Links");

    makeref(NPChar,CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);

    // 调用城市相关对话 -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
    {
        ProcessCommonDialog(NPChar, Link, NextDiag);
        UnloadSegment(NPChar.FileDialog2);
    }
    // 调用城市相关对话 <--
    ProcessCommonDialogRumors(NPChar, Link, NextDiag);
    int iTest, iTemp;
    iTest = FindColony(NPChar.City);
    ref rColony;
    string sTemp, sCity, sTitle;
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
                    dialog.text = RandPhraseSimple("他们说你拥有这个城镇, " + GetSexPhrase("先生","小姐") + "。 ", "很高兴见到你, " + GetSexPhrase("先生","小姐") + "! ");
                    link.l1 = RandPhraseSimple("我改变主意了。 祝你好运! ", "只是在镇上走走。 再见。 ");
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
                    if (sti(pchar.GenQuest.Piratekill) > 20)
                    {
                        dialog.text = RandPhraseSimple("警报! 有武装疯子在这里! 拿起武器! ", "拿起武器! 有武装疯子在这里! ");
                        link.l1 = RandPhraseSimple("什么? ! ", "你在做什么? ! ");
                        link.l1.go = "pirate_fight";
                    }
                    else
                    {
                        dialog.text = RandPhraseSimple("你想要什么? 走开。 ", "别挡我的路, 滚开。 ");
                        link.l1 = RandPhraseSimple("你知道吗? 别嚷嚷! ", "冷静点。 否则我来帮你冷静! ");
                        link.l1.go = "exit";
                        link.l2 = RandPhraseSimple("我想问你。 ", "请你注意一下, 就一个问题。 ");
                        link.l2.go = "quests";//(转发到城市文件)
                        if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
                        {
                            if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
                            {
                                link.l3 = RandPhraseSimple("我想讨论财务问题。 ", "关于财务... ");
                                link.l3.go = "LoanForAll";//(转发到贷款生成器)
                            }
                        }
                    }
                }
                break;
            }
            if(NPChar.quest.meeting == "0")
            {
                NPChar.quest.meeting = "1";
                // 检查港口是否有船
                bool ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
                if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && 4-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0 && or(IsWarShipType(pchar), IsRaiderShipType(pchar))) ok = false;
                if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Townpassenger") && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)//市民乘客
                {
                    dialog.text = "日安, " + GetAddress_Form(NPChar) + "。 我看你是一艘船的船长。 我想请你帮个忙... ";
                    link.l1 = "我在听, " + GetAddress_FormToNPC(NPChar) + "。 你想要什么? ";
                    link.l1.go = "passenger";
                    link.l2 = "对不起, " + GetAddress_FormToNPC(NPChar) + ", 但我很匆忙。 ";
                    link.l2.go = "exit";
                    npchar.quest.meeting = "1";
                    DeleteAttribute(npchar, "talker"); //移除对话标记
                    break;
                }

                // homo 05/08/06
                dialog.Text = NPCharRepPhrase(npchar,
                LinkRandPhrase("我是", "我的名字是", "你可以叫我")
                + GetFullName(npchar)
                + LinkRandPhrase("。 你想要什么? ", "。 我以前没见过你。 你是谁? ", "。 你是谁, 你想从我这里得到什么? "),

                LinkRandPhrase("问候你, " + GetAddress_Form(NPChar) + "。 我叫" + GetFullName(npchar) + "。 你叫什么名字? ",
                    "你好, " + GetAddress_Form(NPChar) + "! 我是" + GetFullName(npchar) + "。 我能知道你的名字吗? ",
                    "是的, " + GetAddress_Form(NPChar) + "。 你想要什么? 顺便说一下, 我的名字是" + GetFullName(npchar) + "。 你叫什么名字? "));

                Link.l1 = pcharrepphrase(
                LinkRandPhrase("该死的! ", "该死! ", "去你的! ") + "是的, 我是船长" +GetFullName(pchar)+ LinkRandPhrase(", 你没听说过" + NPCharSexPhrase(NPChar,", 混蛋? ","? "), "和海上最著名的海盗" + GetSexPhrase("", "女海盗") + "! ", "如果我错了, 就让我见鬼去吧! "),
                LinkRandPhrase("我是" +GetFullName(pchar)+ ", 船长。 ", "我的名字是" +GetFullName(pchar)+ "。 ", "你可以叫我" +GetFullName(pchar)+ "船长。 "));
                Link.l1.go = "Meeting";
                
                //==> 圣慈悲号上的检查团抵达
                if (CheckAttribute(pchar, "questTemp.SantaMisericordia.ColonyZapret") && pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_town")
                {
                    dialog.Text = LinkRandPhrase(LinkRandPhrase("整个城市都紧张不安 —皇家监察官费尔南多.德.阿拉米达来了。 你知道, 我在这里见过很多, 但这... 改变人的不是悲伤, 而是他们如何应对悲伤。 据说他父亲去世后, 他变成了另一个人。 现在整个群岛再也找不到比他更廉洁。 更... 无情的王室仆人了。 ", "看看‘圣慈悲号’! 据说国王亲自下令按特殊设计建造。 注意看 —没有一丝划痕。 就像圣母玛利亚亲自保护它一样。 不过我听到传言... 也许保护它的根本不是圣母。 ", "你知道他们试图杀死费尔南多先生多少次吗? 仅去年一年, 在公海上就有十二次袭击! 嗯, 有这样忠诚训练有素的船员, 在主的保佑下 —他也会挺过第十三次的! "), LinkRandPhrase("你听说了吗? 费尔南多.德.阿拉米达先生已经抵达我们的城市, 据说他现在就在街上的某个地方。 真想亲眼见见他... ", "这个费尔南多先生是个复杂的人。 有人说他是救世主, 为祖国清除污垢。 也有人私下说, 他父亲死后, 他内心崩溃了, 很快我们都会哭泣。 但我告诉你: 不要怕他。 怕那些把他变成这样的人。 ", "这个费尔南多先生真英俊! 但你知道奇怪的是什么吗? 好像他谁都不在意。 满是职责和服务。 我听说有个女孩... 但在和某个牧师见面后, 他完全拒绝了世俗的享乐。 好像他发了誓一样。 "), RandPhraseSimple(RandPhraseSimple("该死的监察官! 他在这里的时候, 城市就像死了一样。 没有贸易, 没有乐趣。 甚至呼吸似乎都得更轻。 你知道最可怕的是什么吗? 每个港口都是这样。 就像时钟一样。 陛下不可能是故意为我们所有人发明这种折磨的! ", "费尔南多先生又去了孤儿院。 慷慨捐赠, 祈祷数小时。 这样的好人应该成为那些该死的贪污者的榜样! "), RandPhraseSimple("哈! ‘圣’费尔南多又关闭了所有妓院。 好吧, 没关系, 他很快就会启航, 它们又会重新开张。 ", "监... 监察官来了, 就是这样! 费尔南多.德.阿尔梅达, 或者, 他叫什么来着, 阿拉米达! 重要到连总督本人都对他蹑手蹑脚。 据说他看着你的眼睛, 就能立刻看到你所有的罪孽。 太可怕了! ")));
                    link.l1 = "... ";
                    link.l1.go = "exit";
                }
                //<== 圣慈悲号上的检查团抵达
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
                link.l1 = PCharRepPhrase("我只是想问一下这个你称之为‘城镇’的破地方。 ", "我想问你一些关于这个城镇的事情。 ");
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
                    link.l16 = "听着, 我希望你能帮我。 我想买一个" + pchar.GenQuest.Device.Shipyarder.Type + ", 有人告诉我这东西在你的镇上卖过。 嗯, 有人在街上卖过。 你知道什么吗? ";
                    link.l16.go = "Device_Citizen";
                }
                // < —倒霉小偷生成器
                
                // 牧师任务生成器。 任务2。 战船 -->
                if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
                {
                    link.l5 = LinkRandPhrase("你知道", "你是否知道", "你听说过") + "当地教堂最近被抢劫了吗? ";
                    link.l5.go = "Citiz_GenQuest_Church_2_1";
                }
                // < —牧师任务生成器。 任务2.
				
                dialog.Text = NPCharRepPhrase(npchar,
                        PCharRepPhrase(LinkRandPhrase("啊, 是你" + GetFullName(Pchar)
                        + GetSexPhrase("- 老朋友! ", "- 美人! ") + "", "很高兴见到你, " + GetSexPhrase("老朋友! ", "美人! ") + " "
                        +pchar.name, "哦, 那是" + GetSexPhrase("船长本人", "女船长") + " "
                         + GetFullName(Pchar))
						+ RandPhraseSimple("。 我还以为你死了! ", "。 也许" + GetSexPhrase("还是像往常一样喝醉了。 ", "有点醉了。 "))
						+ LinkRandPhrase(" 继续, 你需要什么? ", " 这次是什么? ", " 又来烦我? "),
						LinkRandPhrase(TimeGreeting() + ", 船长 ", "日安, " + GetAddress_Form(NPChar) + " ", "问候, 船长 ") + GetFullName(Pchar)
						+ LinkRandPhrase("。 我如何帮助" + GetSexPhrase("像你这样有价值的男人", "像你这样有价值的女人") + "? ", "。 你为什么来这里? ", "。 你这次想知道什么? ")),             
                        PCharRepPhrase(LinkRandPhrase("你好, 船长 ", "问候, 啊, 是你" + GetAddress_Form(NPChar) + " ", "啊, 船长 ")
						+ GetFullName(Pchar)
						+ LinkRandPhrase(", 我以为我们再也不会见面了, 而且",
										 ", 我不会说很高兴见到你, 但是", ", 我看你还活着, 真遗憾, 而且")
						+ LinkRandPhrase(" 你想要什么? ", " 你为什么来这里? ", " 我如何帮助你? "),
						LinkRandPhrase(TimeGreeting() + ", " +GetFullName(pchar)+ "船长。 我如何帮助你? ",
						"哦, 那是" +GetFullName(pchar)+ "船长! 我如何帮助你? ",
						"问候, " + GetAddress_Form(NPChar) + " " + Pchar.lastname + "。 你想要什么? "))
						);  
	   			link.l6 = PCharRepPhrase(RandPhraseSimple("你听错了。 我得走了。 ", "不, 没什么, 我正要去酒馆。 "),
						RandPhraseSimple("好吧, 不管怎样。 祝你好运! ", "只是在城里走走。 再见。 "));
				link.l6.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "ShipLetters_7":
			dialog.text = "问题? ";
			link.l1 = "这些文件上的名字对你有什么意义吗? ";
			link.l1.go = "ShipLetters_8";
		break;
		
		case "ShipLetters_8":
			dialog.text = LinkRandPhrase("我他妈才不在乎什么随机文件, 而且我也不知道怎么读。 去找放贷人吧, 他们说他知道怎么处理信件, 哈! ",
			"我不清楚你在说什么, 去问别人吧, " +GetFullName(pchar)+ "船长。 ", 
			"我不知该如何帮你, " +GetFullName(pchar)+ "船长。 你可以试试去找放贷人, 他或许知道。 ");
			link.l1 = "谢谢。 ";
			link.l1.go = "exit";
		break;
		
		case "Meeting":
		    dialog.Text  = NPCharRepPhrase(npchar, LinkRandPhrase("你没在撒谎吧, " +GetFullName(pchar)+ "船长? ",
				"那又怎样, " +pchar.name+ "? ",
				"我会记住你的, " +GetFullName(pchar)+ "。 ")
				 + "现在告诉我你想要什么? ",
				LinkRandPhrase("很高兴见到你, " +pchar.name+ "船长",
				"很高兴与你相遇, " + GetAddress_Form(NPChar) + " " + PChar.lastname,
				 "很荣幸, " +pchar.name+ "船长") + "。 但我怀疑你不只是想知道我的名字, 对吗? "));
            link.l1 = PCharRepPhrase("我只是想问一下这个你称之为‘城镇’的烂地方。 ", "我想问你一些关于这个城镇的事。 ");
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
   				link.l16 = "听着, 希望你能帮我。 我想买一个" + pchar.GenQuest.Device.Shipyarder.Type + ", 有人说这东西在你们镇上卖过。 嗯, 有人在街上兜售过。 你知道相关情况吗? ";
				link.l16.go = "Device_Citizen";
			}
			// < —倒霉小偷生成器
			
			// 牧师任务生成器。 任务2。 战船 -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople") && !CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.AskedPeople") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_town")
	        {
				link.l5 = LinkRandPhrase("你知道", "你是否了解", "你听说过") + "当地教堂最近被抢劫的事吗? ";
				link.l5.go = "Citiz_GenQuest_Church_2_1";
			}
			// < —牧师任务生成器。 任务2.
			
			Link.l6 = PCharRepPhrase(RandPhraseSimple("你听错了。 我得走了。 ", "没什么, 我正要去酒馆。 "),
                                        RandPhraseSimple("好吧, 没什么。 祝你好运! ", "只是在城里走走。 再见。 "));
			Link.l6.go = "exit";
		break;
		
		case "new question":
            dialog.text = NPCharRepPhrase(npchar,
				PCharRepPhrase(LinkRandPhrase("哦, 见到你就像见到酒一样让我高兴, 想问什么就问吧。 ", "喜欢聊天吗, 船长? 我也是... 尤其是边喝朗姆酒边聊。 ", "是的, " +pchar.name+ "? "),
				LinkRandPhrase("你还想知道什么? ", "我猜你很喜欢聊天吧, " +pchar.name+ "船长。 ")),
		        PCharRepPhrase(LinkRandPhrase("你还想知道什么, " + GetAddress_Form(NPChar) + "? ", "我在听, 船长。 ", "我得走了, 有话快问, 船长。 "),
                LinkRandPhrase("很高兴有你这样的伙伴, " + GetAddress_Form(NPChar) + " " + PChar.lastname + "。 说吧。 ",
                "怎么了, " + GetAddress_Form(NPChar) + "? ",
                "喜欢聊天吗, 船长? 我也是... ")));
			link.l1 = LinkRandPhrase ("这个镇上有什么传言? ", "这片土地上有什么新闻? ", "这里的生活怎么样? ");
			link.l1.go = "rumours_townman";
			link.l2 = LinkRandPhrase("你能给我指指路吗? ", "我找不到去一个地方的路... ", "帮我找一下去某个地方的路... ");
			link.l2.go = "town";  //(转发到城市文件)
			link.l3 = RandPhraseSimple("我想知道人们怎么评价某个人。 ", "你知道人们怎么谈论某个人吗? ");
			link.l3.go = "info"; //(转发到城市文件)
			link.l4 = RandPhraseSimple("我想了解更多当地人的情况。 ", "你能告诉我一些关于当地人的事吗? ");
			link.l4.go = "RumourAboutOwners";
			link.l5 = PCharRepPhrase(RandPhraseSimple("你听错了。 我得走了。 ", "没什么, 我正要去酒馆。 "),
            RandPhraseSimple("好吧, 没什么。 祝你好运! ", "只是在镇上走走。 再见。 "));
			link.l5.go = "exit";
		break;
		
		case "RumourAboutOwners":
			Dialog.Text = "你对谁感兴趣? ";
			if(GetCharacterIndex(NPChar.city + "_Mayor") != -1)
			{
				link.l1 = "想了解更多关于镇长的事。 ";
				link.l1.go = "RumourAboutOwners_Mayor";
			}
			if(GetCharacterIndex(NPChar.city + "_TavernKeeper") != -1)
			{
				link.l2 = "想了解更多关于当地酒馆老板的事。 ";
				link.l2.go = "RumourAboutOwners_TavernKeeper";
			}
			if(GetCharacterIndex(NPChar.city + "_ShipYarder") != -1)
			{
				link.l3 = "想了解更多关于当地造船厂老板的事。 ";
				link.l3.go = "RumourAboutOwners_ShipYarder";
			}
			if(GetCharacterIndex(NPChar.city + "_Trader") != -1)
			{
				link.l4 = "想了解更多关于当地商店老板的事。 ";
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
			// 这里可以根据任务检查触发了哪个谣言
			DeleteAttribute(PChar, "QuestTemp.RumoursAboutOwners");
		break;
		
		//杰森 --> 倒霉小偷生成器
		case "Device_Citizen":
           dialog.text = "嗯, " + pchar.GenQuest.Device.Shipyarder.Type + "? 从没听说过... 我在这儿住了很久, 从没见过这种东西。 ";
			link.l1 = "嗯, 这是个造船工具, " + pchar.GenQuest.Device.Shipyarder.Describe + "。 镇上有人卖过类似的东西吗? 或者有人带着它走来走去, 你注意到了吗? ";
			link.l1.go = "Device_Citizen_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Citizen_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 3 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 6 && npchar.sex != "woman")
			{
				dialog.text = "嗯... 是的, 几小时前我看到一个男人拿着那东西。 他在街上走。 那工具挺有意思的。 ";
				link.l1 = "他长什么样, 往哪儿去了? 我真的需要这样的东西。 ";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "没有, 我没见过类似的东西。 ";
				link.l1 = "我知道了。 那我继续问问。 ";
				link.l1.go = "exit";
			}
		break;
		
		//=================== 牧师任务节点: 寻找抢劫者 (任务2) ==================
		case "Citiz_GenQuest_Church_2_1":
			if(rand(3) != 1)
			{
				dialog.text = LinkRandPhrase("不, 我对此一无所知。 ", "不, 我该走了。 ", "我什么都不知道。 ");
					link.l1 = LinkRandPhrase("好吧, 谢谢。 ", "我知道了, 谢谢。 ", "好的, 打扰了。 ");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("我对此一无所知, 但你可以试试问问酒馆里的常客, 他们肯定会告诉你更多。 ", "我什么也说不出来, 去酒馆问问别人吧。 ");
				link.l1 = "谢谢你告诉我。 ";
				link.l1.go = "exit";
			}
			
			NPChar.GenQuest.ChurchQuest_2.AskedPeople = true;
		break;		
		
		//-------------------------------市民乘客----------------------------------------------
		case "passenger":
			if (hrand(19) > 9) SetPassengerParameter("Townpassenger", false);
			else SetPassengerParameter("Townpassenger", true);
			if (!CheckAttribute(pchar, "GenQuest.Townpassenger.Enemycity"))
			{
				dialog.text = "船长, 我需要尽快到达名为" + XI_ConvertString("Colony"+pchar.GenQuest.Townpassenger.City) + "的殖民地, 它在" + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Townpassenger.City)+"Dat") + "上, 需要" + FindRussianDaysString(sti(pchar.GenQuest.Townpassenger.DaysQty)) + "。 与这里航行的大多数小船相比, 你的船看起来很坚固。 我可以付你" + FindRussianMoneyString(sti(pchar.GenQuest.Townpassenger.Money)) + "。 你觉得怎么样? ";
			}
			else
			{
				dialog.text = "船长, 我需要到达" + XI_ConvertString("Colony"+pchar.GenQuest.Townpassenger.City) + "殖民地, 它在" + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Townpassenger.City)+"Voc") + "上, 需要" + FindRussianDaysString(sti(pchar.GenQuest.Townpassenger.DaysQty)) + "。 我知道这听起来极其危险, 但也许" + FindRussianDublonString(sti(pchar.GenQuest.Townpassenger.Money)) + "对你来说是个不错的激励? ";
			}
			link.l1 = "嗯。 我也正往这个方向去, 所以我准备按这些条件让你上船。 ";
			link.l1.go = "passenger_1";
			link.l2 = "对不起, " + GetAddress_FormToNPC(NPChar) + ", 但我正朝不同的方向航行。 我帮不了你。 ";
			link.l2.go = "passenger_exit";
		break;
		
		case "passenger_exit":
			dialog.text = "太遗憾了。 好吧, 我会等另一艘船。 再见。 ";
			link.l1 = "再见。 ";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Townpassenger");
		break;
		
		case "passenger_1":
			dialog.text = "太好了, 因为我等得不耐烦了。 我们到了那里你就会拿到报酬。 ";
			link.l1 = "到我的船上来, " + GetAddress_FormToNPC(NPChar) + "。 我们很快就出发。 ";
			link.l1.go = "passenger_2";
		break;
		
		case "passenger_2":
			DialogExit();
			pchar.GenQuest.Townpassenger.id = npchar.id;
			LAi_SetImmortal(npchar, true);
			DeleteAttribute(npchar, "LifeDay");
			LAi_RemoveLoginTime(npchar);
			DeleteAttribute(npchar, "CityType");//删除幽灵标志, 否则会出现空城市
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sTitle = npchar.index+"Citizpassenger";

// LDH 13Sep17 - 不要添加到现有的Citizpassenger记录 -->
// 通过将任务记录复制到新名称并删除旧记录来"重命名"任务记录
			if (CheckAttribute(pchar, "questinfo."+sTitle))
			{
				string sTempLDH = frand(1);
				sTempLDH = strcut(sTempLDH, 2, 5);    // 4位随机数字
				string sTitle1 = sTitle+sTempLDH;

				aref arTo, arFrom;
				makearef(arFrom, pchar.questinfo.(sTitle));
				makearef(arTo,   pchar.questinfo.(sTitle1));
				CopyAttributes(arTo, arFrom);
				pchar.questinfo.(sTitle1) = "";

				DeleteAttribute(pchar, "questinfo."+sTitle);

				Trace("重复的Citizpassenger记录" + sTitle + "已复制到" + sTitle1 + " **");
			}
// <--

			AddQuestRecordEx(sTitle, "Citizpassenger", "1");
			AddQuestUserDataForTitle(sTitle, "sType", "公民");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			sTemp = XI_ConvertString("Colony" +pchar.GenQuest.Townpassenger.City) + ", 它在" + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Townpassenger.City)+"Voc") + "上。 "; // belamour gen
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sDays", FindRussianDaysString(sti(pchar.GenQuest.Townpassenger.DaysQty)));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
            if (!CheckAttribute(pchar, "GenQuest.Townpassenger.Enemycity")) AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Townpassenger.Money)));
			else AddQuestUserData(sTitle, "sMoney", FindRussianDublonString(sti(pchar.GenQuest.Townpassenger.Money)));
			pchar.quest.Townpassenger.win_condition.l1 = "location";
			pchar.quest.Townpassenger.win_condition.l1.location = pchar.GenQuest.Townpassenger.City+"_town";
			pchar.quest.Townpassenger.function = "Townpassenger_complete";
			SetFunctionTimerCondition("Townpassenger_Over", 0, 0, sti(pchar.GenQuest.Townpassenger.DaysQty), false);
		break;
		
		case "passenger_3":
			pchar.quest.Townpassenger_Over.over = "yes"; //取消定时器
			dialog.text = "我们到了, 太棒了! 这次乘你的船旅行非常满意。 感谢你, 先生。 请收下钱。 ";
			link.l1 = "祝你好运, " + GetAddress_FormToNPC(NPChar) + "! 再见。 ";
			link.l1.go = "passenger_4";
		break;
		
		case "passenger_4":
			chrDisableReloadToLocation = false;//开启位置加载
			DialogExit();
			npchar.lifeday = 0;
			RemovePassenger(Pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
			OfficersReaction("good");				
			AddCharacterExpToSkill(pchar, "Sailing", 80);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			if (CheckAttribute(pchar, "GenQuest.Townpassenger.Enemycity"))
			{
				AddCharacterExpToSkill(pchar, "Sneak", 50);
				TakeNItems(pchar, "gold_dublon", sti(pchar.GenQuest.Townpassenger.Money));
			}
			else AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Townpassenger.Money));
			sTitle = npchar.index+"Citizpassenger";
			AddQuestRecordEx(sTitle, "Citizpassenger", "3");
			CloseQuestHeader(sTitle);
			DeleteAttribute(Pchar, "GenQuest.Townpassenger");
		break;
//<--市民乘客
		
		//关于外露武器的提醒
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "听着, 作为这个镇的市民, 我请求你收起刀刃。 ", "听着, 作为这个镇的市民, 我请求你收起刀刃。 ");
				link.l1 = LinkRandPhrase("好的。 ", "如你所愿。 ", "如你所说... ");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "携带武器跑动时请小心, 我可能会紧张... ", "我不喜欢有陌生人在我面前拿着出鞘的剑... ");
				link.l1 = RandPhraseSimple("明白了。 ", "别担心。 ");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		case "pirate_fight":
			DialogExit();
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_Attack(NPChar, Pchar);
			DoQuestFunctionDelay("TownPirate_battle", 0.5);
		break;

	}
}
// 放贷人通用对话
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, chr, sld;
	aref Link, NextDiag;
	string NPC_Area, sTemp, sTitle, sDepositType1, sDepositType2;
	int LoanSum, LoanInterest, LoanPeriod, LoanResult, iPastMonths, DepositSum, DepositInterest, DepositResult, iNum, iTemp, iTotalDublonQty;
	int iRes, iPer, iDep;
	float fPer;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	string iDay, iMonth, s1;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;

	NPC_Area = Npchar.City;
	sDepositType1 = NPC_Area + "_Type1";
	sDepositType2 = NPC_Area + "_Type2";
 
	if(!CheckAttribute(npchar, "quest.item_date"))
	{
		npchar.quest.item_date = "";
	} 
 
	// 按城市调用对话 -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Usurer\" + NPChar.City + "_Usurer.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // 按城市调用对话 <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06

	if (!CheckAttribute(npchar, "quest.trade_date"))
    {
        npchar.quest.trade_date = "";
    }
    if (!CheckAttribute(npchar, "quest.FindCitizenNoShip"))
    {
        npchar.quest.FindCitizenNoShip = 0;
    }

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "First time":
			if (LAi_group_GetPlayerAlarm() > 0)
			{
				//--> 奴隶贩子
				if(pchar.questTemp.Slavetrader == "After_enterSoldiers" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
				{
					dialog.text = "结束了。 现在离开这个地方, " +pchar.name+ "。 我会清理这一切烂摊子。 ";
					link.l1 = "好吧, 我会扬帆起航! ";
					link.l1.go = "exit";
					break;
				}
				//< —奴隶贩子
			
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("全镇都处于警戒状态, 他们到处都在搜捕你! 如果我是你, 我不会在这里久留。 ", "所有卫兵都在找你。 我又不傻, 不会冒着风险和你说话! ", "快跑, " + GetSexPhrase("伙计", "姑娘") + ", 趁士兵们还没把你打成筛子..."), 
					LinkRandPhrase("你想要什么, 卑鄙的家伙? ! 镇卫兵已经知道了你的位置, 你跑不掉的, " + GetSexPhrase("肮脏的海盗", "你这个海盗婊子") + "! ", "肮脏的杀人犯, 离我的地方远点! 卫兵! ", "我不怕你, 卑鄙的家伙! 很快你就会被绞死在我们的堡垒里, 你逃不掉的..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("哼, 这对我来说不是问题...", "他们永远抓不到我。 "), 
					RandPhraseSimple("闭嘴, " + GetWorkTypeOfMan(npchar, "") + ", 否则我就割断你该死的舌头! ", "哼, " + GetWorkTypeOfMan(npchar, "") + ", 也想抓海盗? 听着, 小子, 乖乖坐在这里, 你还能活命..."));
				link.l1.go = "fight";
				break;
			}
		//Jason ---------------------------------------加斯科涅人的负担------------------------------------
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.location == "Fortfrance_bank")
			{
				dialog.text = "需要什么吗, 先生? ";
				Link.l1 = "我需要信息...我想问你一些事情。 ";
				Link.l1.go = "quests";
				Link.l2 = "来一笔小额贷款怎么样? ";
				Link.l2.go = "sharlie_credit";
				Link.l3 = "不, 我改变主意了。 ";
				Link.l3.go = "exit";
				if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
				{
					link.l4 = "看看这些耳环, 先生。 我在丛林里一个强盗的口袋里找到的。 这显然是一位优秀珠宝匠的作品, 我敢肯定不是来自这片荒野。 你怎么看? ";
					link.l4.go = "Sharlie_junglejew";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskiper")
				{
					link.l1 = "我知道你有一个叫福尔克.德吕克的债务人。 告诉我, 他的...拖欠情况有多严重? ";
					link.l1.go = "Sharlie";
				}	
				if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipermoney")
				{
					link.l1 = "我是来处理福尔克.德吕克的债务的。 ";
					link.l1.go = "Sharlie_repeat";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipercaptive")
				{
					link.l1 = "我完成了你的任务, 先生。 这是你的...西班牙朋友。 ";
					link.l1.go = "Sharlie_14";
				}
				break;
			}			
		//< —加斯科涅人的负担
			
			//--> 奴隶贩子
			if (pchar.questTemp.Slavetrader == "canTakeQuest" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "好吧, 终于有一位值得信赖的船长光顾我的地方了, 那些认为我只是把他们的杜布隆和几内亚金币种在地里, 每个月收获一次来支付他们利息的白痴真让我厌烦\n他们盯着每一分钱, 却不知道这个可怜的放贷人为了避免自己饿死, 同时又要给他们提供在圣诞节买只鹅的机会, 不得不耍各种花招。 ";
				Link.l1 = "我想你的客户听到他们的钱的保管人说出这样的话不会高兴的。 ";
				Link.l1.go = "GiveTaskSlave";
				npchar.quest.slave = "current";//以免被石头砸
				break;
			}	
			
			if (pchar.questTemp.Slavetrader == "TakeShoreCap_end" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "...";
				Link.l1 = "听着, 老仓鼠, 你现在真的得尽力向我解释清楚! 那艘船上根本没有奴隶, 只有一队士兵! 对付他们可真是个艰巨的任务! 我非常生气, 所以你最好解释一下! ";
				Link.l1.go = "Slaveshore_5";
				break;
			}	
			if (pchar.questTemp.Slavetrader == "Win_HavanaFort" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "啊, 你终于来了! 整个群岛都在谈论你那次大胆的袭击。 很高兴见到你! ";
				Link.l1 = "我宁愿默默无闻也不愿有那种名声...太危险了。 ";
				Link.l1.go = "Win_Havana_Fort";
				break;
			}	
			if (pchar.questTemp.Slavetrader == "Havana_seekslaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "你带来我的五千名奴隶了吗? ";
				if (GetSquadronGoods(Pchar, GOOD_SLAVES) >= 5000)
				{
					Link.l1 = "带来了。 他们在我的货舱里。 ";
					Link.l1.go = "Havana_Fort_yesA";
				}
				else
				{
					Link.l1 = "没有, 我还在处理这件事。 ";
					Link.l1.go = "exit";
				}
				break;
			}	
			
			if (pchar.questTemp.Slavetrader == "End_quest_bad" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "嗯...你还活着? 真奇怪。 但这不会持续太久。 士兵们! 救命! 这里有个强盗! ";
				link.l1 = "真是个混蛋! ";
				link.l1.go = "exit";
				LAi_group_Attack(NPChar, Pchar);
				break;
			}
			
			if(pchar.questTemp.Slavetrader == "wait_6" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_6") > 6 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "日安。 我叫" + GetFullName(npchar) + "。 我能为您做些什么? ";
				link.l1 = "哦! 你在这里做什么, 先生? ";
				link.l1.go = "Usurer_Escape";
				break;
			}
			//< —奴隶贩子
			// FMK-瓜德罗普岛
			if(CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "killers" && npchar.location == "BasTer_bank")
			{
				dialog.Text = "...";
				link.l1 = "嘿, 你这个混蛋。 你有什么好主意吗? 雇了暴徒来杀我? 想让我闭嘴? 说, 现在! ";
				link.l1.go = "FMQG_x";
				break;
			}
			// 贝丝女士 -->
			if (pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_Bank" && !CheckAttribute(pchar, "questTemp.LadyBeth_Usurer")) // 布莱克伍德在城里
			{
				dialog.Text = "哦, 船长! 请看我今天得到了什么。 有些物品是我从布莱克伍德的手下那里得到的。 他们需要钱进行新的探险, 而对我们来说 —是利润, 对吧? ";
				link.l1 = "布莱克伍德知道他的手下在卖他们的发现吗? ";
				link.l1.go = "LadyBeth_Usurer_1";
				break;
			}
			// 贝丝女士 <--
			if(NPChar.quest.meeting == "0")
			{
				dialog.Text = LinkRandPhrase(LinkRandPhrase("日安, " + GetAddress_Form(NPChar) + "。 我能为您做些什么? 我认识您吗? ", "请进, 船长。 我叫" + GetFullName(npchar) + ", 是当地的银行家。 ", "很高兴见到您, " + GetAddress_Form(NPChar) + "! 我是当地的银行家, 如果您有资金问题, 我可以帮助您。 "), LinkRandPhrase("我们以前见过面吗, 船长? 我是" + GetFullName(npchar) + ", 是当地的银行家。 ", "请进, 船长。 我叫" + GetFullName(npchar) + ", 是当地的银行家。 ", "问候您, " + GetAddress_Form(NPChar) + "。 我是" + GetFullName(npchar) + ", 当地的银行家。 "), LinkRandPhrase("很高兴见到您, " + GetAddress_Form(NPChar) + ", 我是" + GetFullName(npchar) + ", 只是这个美妙城镇里一个谦逊的银行家。 ", "这由您决定, 船长! 想从我这里借些钱还是把钱存起来赚利息? ", "尊敬的船长! 我很高兴您光临我的简陋办公室! "));
				link.l1 = RandPhraseSimple(LinkRandPhrase("我的荣幸! 我只是在镇上散步, 决定来拜访您。 ", "我的荣幸, 我是" + GetFullName(pchar) + ", 很高兴见到您。 ", "" + GetFullName(pchar) + ", " + pchar.ship.name + "号船的船长, 很高兴见到您。 这是一家银行, 对吧? "), RandPhraseSimple("很高兴见到您。 我是" + GetFullName(pchar) + "。 " + pchar.ship.name + "号船的船长。 我只是想认识您。 ", "啊哈, 那么您在这里有一家银行, 对吧? 很高兴见到您, 我是" + GetFullName(pchar) + ", 自己船只的船长。 "));
				link.l1.go = "next";
				NPChar.quest.meeting = "1";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_bank")
				{
					dialog.text = "麦克阿瑟夫人, 欢迎, 请进。 ";
					link.l1 = "也向您问好, " + npchar.lastname;
					link.l1.go = "Helen_next";
				}
			}
			else
			{
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("是你! 你想要什么, " + GetAddress_Form(NPChar) + "? ", "你在这里有什么事, 船长? 对不起, 但您的名声让您不是一个非常受欢迎的客户。 ", "啊哈, 又一个客户! 起初我还以为你是个强盗...哈哈, 我只是在开玩笑。 "),LinkRandPhrase("哦! 你想要什么? 这是银行, 不是酒馆。 ", "日安, 船长。 我必须通知您, 我在选择客户时相当挑剔。 ", "你想要什么, " + GetFullName(pchar) + "? 我希望您记得, 您的声望不会让您获得大额贷款? "),LinkRandPhrase("我希望您是想投资, " + GetAddress_Form(NPChar) + "? 对您来说获得贷款并不容易。 ", "船长" + GetFullName(pchar) + ", 您想从这个谦逊的银行家这里得到什么? 对不起, 但我无法为您安排贷款。 您只能把钱借给我赚取利息。 ", "请进, " + GetAddress_Form(NPChar) + "。 很抱歉通知您, 您不是最受欢迎的客户, 但我通常不会立即拒绝别人。 ")),LinkRandPhrase(LinkRandPhrase("您好, " + GetFullName(pchar) + "先生! 我随时准备帮助您解决业务问题。 ", "您好, " + GetAddress_Form(NPChar) + "先生。 我随时准备提供贷款或接受任何投资。 ", "亲爱的" + GetFullName(pchar) + "! 很高兴见到您! 您有什么愿望? "),LinkRandPhrase("船长" + GetFullName(pchar) + "! 我随时为您服务。 想贷款还是投资赚取利息? ", "向您问好, 船长! 您在这里始终是受欢迎的客户。 您有极好的商业声誉! ", "日安, " + GetFullName(pchar) + "。 很高兴您再次来访。 希望您是来达成一项有利可图的商业协议的? "),LinkRandPhrase("日安, 船长! 您想要什么? 想贷款还是投资? ", "船长" + GetFullName(pchar) + "! 您想以有利的条件借钱吗? 我总是很高兴见到如此受人尊敬的客户。 ", "很高兴再次见到您, 船长! 我随时准备帮助您, 无论是贷款还是投资。 ")));
				link.l1 = pcharrepphrase(RandPhraseSimple(LinkRandPhrase("别开玩笑了, 银行家, 我在这里有生意。 ", "废话太多, 伙计。 让我们直接谈正事。 ", "您听说过钱是没有臭味的吗? 所以闭上您的鼻子, 让我们开始谈生意吧。 "), LinkRandPhrase("您就是这样接待客户的吗? 幸运的是我今天心情不错。 ", "哈! 您见到我不高兴吗, 嗯? 难道我不是一枚金色的杜布隆, 不能给您留下好印象吗? 不管怎样, 让我们谈生意吧, 放贷人。 ", "呃, 我真想教教您一些礼貌, 但我没时间。 还是谈谈钱吧。 ")),
				RandPhraseSimple(LinkRandPhrase("很高兴见到我的老朋友! ", "来这里总是一种乐趣, 朋友。 让我们直接谈生意吧。 ", "我也很高兴。 让我们谈生意吧, 朋友。 "),LinkRandPhrase("真的很高兴见到您。 金融界有什么新消息? ", "很高兴您还记得我。 我赶时间, 所以让我们直接谈生意吧。 ", "你好, 老朋友! 很高兴再次见到您! ")));
				link.l1.go = "next";
			}
			break;
			
			case "next":
			dialog.text = NPCStringReactionRepeat("我能为您做些什么? ", 
				"您这次想要什么? ", 
				"嗯...您有什么问题? ",
                "呃, " + GetAddress_Form(npchar) + ", 您无法想象客户会有多烦人..." , "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("不, 谢谢, 我只是四处走走, 聊聊天。 ", 
				"又是我。 只是想和您聊聊天。 ",
                "是的, 又是我。 没什么严肃的, 只是想和您聊聊天。 ", 
				"是的, 做银行家有时并不容易。 只是想聊聊天...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			link.l2 = "我想讨论一下我们的财务问题。 ";
			link.l2.go = "LoanUsurer";//(到贷款生成器)
			link.l3 = "我对珠宝和不寻常的偶像或宝石感兴趣。 ";
			if (!isMultiObjectKnown("gold_dublon"))
			{
				link.l3.go = "items_0";
			}
			else
			{
				link.l3.go = "items_1";
			}	
			link.l4 = "我需要一些信息。 嗯, 我有一些事情要问您。 ";
			link.l4.go = "quests";//(转发到城市文件)
//Jason, 二级邮政信使生成器
			if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
			{
				if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					link.l12 = "我给您带来了来自" + XI_ConvertString("Colony" + pchar.questTemp.WPU.Postcureer.StartCity + "Gen") + "的商业文件。 ";
					link.l12.go = "Postcureer_LevelUp_ForAll";
				}
			}
			//市长任务, 潜入敌对城市
  			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //市长任务 - 与我们的间谍联系
			{
				link.l7 = RandPhraseSimple("我是奉一个人的命令来的。 他是总督" + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + "。 ", 
					GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + "派我来这里。 我必须从您这里得到一些东西。 ");
				link.l7.go = "IntelligenceForAll";
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "usurer_keeper")
			{
				link.l9 = "日安, 我是您儿子邀请来的。 "; 
				link.l9.go = "EncGirl_4";
				pchar.quest.EncGirl_GetLoverFather.over = "yes";
			}	
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer"))
			{
				link.l10 = "我想知道这份文件的主人是谁。 ";
				link.l10.go = "ShipLetters_Usurer1";			
			}
			
			//--> 家族遗物 // 樵夫从npchar重写到char 
			if (CheckAttribute(pchar, "GenQuest.Noblelombard") && npchar.city == pchar.GenQuest.Noblelombard.City && !CheckAttribute(pchar, "quest.noblelombard"))// 就在这里 
			{
				link.l11 = "我想谈谈您客户的债务。 他的名字是" + pchar.GenQuest.Noblelombard.Name + "。 他抵押了他的家族遗物。 我在这里代表他的利益, 我有权与您讨论归还它的问题。 ";
				link.l11.go = "Noblelombard";			
			}
			if (CheckAttribute(pchar, "GenQuest.Noblelombard.Giveregard") && npchar.city == pchar.GenQuest.Noblelombard.City)
			{
				link.l11 = "我们三个月前见过面, 谈过一个人的遗物。 他的名字是" + pchar.GenQuest.Noblelombard.Name + "。 还记得吗? 他必须以我的名义开一个存款账户。 金额是" + FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Regard)) + "...";
				link.l11.go = "Noblelombard_5";			
			}
			//< —家族遗物
			
			//-->奴隶贩子
			if (pchar.questTemp.Slavetrader == "Seek_slaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id) 
			{
				link.l8 = "是关于您的...奴隶任务。 ";
				link.l8.go = "Checkslaves";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "日安, " + NPChar.name + ", 让我们谈谈您的任务。 ";
				link.l8.go = "Takeslaves_4_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway_pinas" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "日安, " + NPChar.name + ", 让我们谈谈您的任务。 ";
				link.l8.go = "Pinas_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "died" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "日安, " + NPChar.name + ", 让我们谈谈您的任务。 ";
				link.l8.go = "Takeslaves_4_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait") > 20 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "我来了, 按照我们的约定。 有工作给我吗? ";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "waitship" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "我按承诺来了。 有工作吗? ";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_1" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_1") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "日安, " + npchar.name+ "。 您近况如何? 有新任务给我吗? ";
				link.l8.go = "EscapeSlave";
				break;
			}
			if(pchar.questTemp.Slavetrader == "escapeslave_win" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "您的任务完成了。 我找到了那些逃跑的奴隶。 不过这并不容易。 ";
				link.l8.go = "Escape_slaves_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_2" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_2") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "日安, " + npchar.name+ "。 我来是为了一个新的有利可图的任务。 ";
				link.l8.go = "Slaveshore";
				break;
			}			
			
			if(pchar.questTemp.Slavetrader == "goodbye" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "坏消息, " + npchar.name+ "。 我没能得到那艘双桅帆船。 ";
				link.l8.go = "Brig_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goodbye_1" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "看, " + npchar.name+ "。 我追上了那艘双桅帆船, 但我没有找到文件。 您确定它们在那里吗? ";
				link.l8.go = "Letter_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "winbrig" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "好消息, " + npchar.name+ "。 我成功追上了那艘双桅帆船并找到了文件。 在这里。 ";
				link.l8.go = "Brig_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_3" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_3") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "日安, " + npchar.name+ "。 您为我准备好新任务了吗? ";
				link.l8.go = "SlaveGalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wingalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "" + npchar.name+ ", 我成功拦截了那艘所谓的'大帆船'。 ";
				link.l8.go = "Wingalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostgalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "" + npchar.name+ ", 我很抱歉, 但我没能登上那艘大帆船。 ";
				link.l8.go = "Lostgalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_4" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_4") > 4 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "日安, " + npchar.name+ "。 我来拿我的钱。 ";
				link.l8.go = "FindRat";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wincorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "" + npchar.name+ ", 您的任务完成了。 那个混蛋贡捷尔和他的船员都死了。 ";
				link.l8.go = "Wincorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostcorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "" + npchar.name+ ", 我很抱歉, 但我没能抓住弗朗索瓦.贡捷尔, 尽管我一直跟踪他到托尔图加。 他设法乘他的护卫舰从我手中逃脱了。 ";
				link.l8.go = "lostcorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_5" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_5") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "日安, " + npchar.name+ "。 告诉我您为我准备的那个新任务。 ";
				link.l8.go = "Havana_fort";
				break;
			}
			//<--奴隶贩子
			NextDiag.TempNode = "First time";
		break;
		
		case "Helen_next":
			dialog.text = NPCStringReactionRepeat("我不会说您需要钱或寻求增加财富。 是什么风把您吹到我的办公室来了? ", 
				"您这次想要什么? ", 
				"嗯...您有什么问题? ",
                "呃, " + GetAddress_Form(npchar) + ", 您无法想象客户会有多烦人..." , "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("不, 谢谢, 我只是四处走走, 聊聊天。 ", 
				"又是我。 只是想和您聊聊天。 ",
                "是的, 又是我。 没什么严肃的, 只是想和您聊聊天。 ", 
				"是的, 做银行家有时并不容易。 只是想聊聊天...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			link.l2 = "我想讨论一下我们的财务问题。 ";
			link.l2.go = "LoanUsurer";//(到贷款生成器)
			link.l3 = "我对珠宝和不寻常的偶像或宝石感兴趣。 ";
			if (!isMultiObjectKnown("gold_dublon"))
			{
				link.l3.go = "items_0";
			}
			else
			{
				link.l3.go = "items_1";
			}	
			link.l4 = "我需要一些信息。 嗯, 我有一些事情要问您。 ";
			link.l4.go = "quests";//(转发到城市文件)
//Jason, 二级邮政信使生成器
			if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
			{
				if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					link.l12 = "我给您带来了来自" + XI_ConvertString("Colony" + pchar.questTemp.WPU.Postcureer.StartCity + "Gen") + "的商业文件。 ";
					link.l12.go = "Postcureer_LevelUp_ForAll";
				}
			}
			//市长任务, 潜入敌对城市
  			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //市长任务 - 与我们的间谍联系
			{
				link.l7 = RandPhraseSimple("我是奉一个人的命令来的。 他是总督" + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + "。 ", 
					GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + "派我来这里。 我必须从您这里得到一些东西。 ");
				link.l7.go = "IntelligenceForAll";
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "usurer_keeper")
			{
				link.l9 = "日安, 我是您儿子邀请来的。 "; 
				link.l9.go = "EncGirl_4";
				pchar.quest.EncGirl_GetLoverFather.over = "yes";
			}	
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer"))
			{
				link.l10 = "我想知道这份文件的主人是谁。 ";
				link.l10.go = "ShipLetters_Usurer1";			
			}
			
			//--> 家族遗物 // 樵夫从npchar重写到char 
			if (CheckAttribute(pchar, "GenQuest.Noblelombard") && npchar.city == pchar.GenQuest.Noblelombard.City && !CheckAttribute(pchar, "quest.noblelombard"))// 就在这里 
			{
				link.l11 = "我想谈谈您客户的债务。 他的名字是" + pchar.GenQuest.Noblelombard.Name + "。 他抵押了他的家族遗物。 我在这里代表他的利益, 我有权与您讨论归还它的问题。 ";
				link.l11.go = "Noblelombard";			
			}
			if (CheckAttribute(pchar, "GenQuest.Noblelombard.Giveregard") && npchar.city == pchar.GenQuest.Noblelombard.City)
			{
				link.l11 = "我们三个月前见过面, 谈过一个人的遗物。 他的名字是" + pchar.GenQuest.Noblelombard.Name + "。 还记得吗? 他必须以我的名义开一个存款账户。 金额是" + FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Regard)) + "...";
				link.l11.go = "Noblelombard_5";			
			}
			//< —家族遗物
			
			//-->奴隶贩子
			if (pchar.questTemp.Slavetrader == "Seek_slaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id) 
			{
				link.l8 = "是关于您的...奴隶任务。 ";
				link.l8.go = "Checkslaves";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "日安, " + NPChar.name + ", 让我们谈谈您的任务。 ";
				link.l8.go = "Takeslaves_4_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway_pinas" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "日安, " + NPChar.name + ", 让我们谈谈您的任务。 ";
				link.l8.go = "Pinas_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "died" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "日安, " + NPChar.name + ", 让我们谈谈您的任务。 ";
				link.l8.go = "Takeslaves_4_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait") > 20 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "我来了, 按照我们的约定。 有工作给我吗? ";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "waitship" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "我按承诺来了。 有工作吗? ";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_1" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_1") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "日安, " + npchar.name+ "。 您近况如何? 有新任务给我吗? ";
				link.l8.go = "EscapeSlave";
				break;
			}
			if(pchar.questTemp.Slavetrader == "escapeslave_win" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "您的任务完成了。 我找到了那些逃跑的奴隶。 不过这并不容易。 ";
				link.l8.go = "Escape_slaves_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_2" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_2") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "日安, " + npchar.name+ "。 我来是为了一个新的有利可图的任务。 ";
				link.l8.go = "Slaveshore";
				break;
			}			
			
			if(pchar.questTemp.Slavetrader == "goodbye" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "坏消息, " + npchar.name+ "。 我没能得到那艘双桅帆船。 ";
				link.l8.go = "Brig_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goodbye_1" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "看, " + npchar.name+ "。 我追上了那艘双桅帆船, 但我没有找到文件。 您确定它们在那里吗? ";
				link.l8.go = "Letter_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "winbrig" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "好消息, " + npchar.name+ "。 我成功追上了那艘双桅帆船并找到了文件。 在这里。 ";
				link.l8.go = "Brig_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_3" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_3") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "日安, " + npchar.name+ "。 您为我准备好新任务了吗? ";
				link.l8.go = "SlaveGalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wingalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "" + npchar.name+ ", 我成功拦截了那艘所谓的'大帆船'。 ";
				link.l8.go = "Wingalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostgalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "" + npchar.name+ ", 我很抱歉, 但我没能登上那艘大帆船。 ";
				link.l8.go = "Lostgalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_4" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_4") > 4 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "日安, " + npchar.name+ "。 我来拿我的钱。 ";
				link.l8.go = "FindRat";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wincorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "" + npchar.name+ ", 您的任务完成了。 那个混蛋贡捷尔和他的船员都死了。 ";
				link.l8.go = "Wincorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostcorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "" + npchar.name+ ", 我很抱歉, 但我没能抓住弗朗索瓦.贡捷尔, 尽管我一直跟踪他到托尔图加。 他设法乘他的护卫舰从我手中逃脱了。 ";
				link.l8.go = "lostcorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_5" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_5") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "日安, " + npchar.name+ "。 告诉我您为我准备的那个新任务。 ";
				link.l8.go = "Havana_fort";
				break;
			}
			//<--奴隶贩子
			NextDiag.TempNode = "First time";
		break;

		case "items_0":
			dialog.text = "想买些金杜布隆或装它们的箱子吗? 相信我, 这是一项非常有价值的投资。 ";
			link.l1 = "是的, 非常有趣。 ";
			link.l1.go = "items";
			AddQuestRecordInfo("Recipe", "Gold_dublon");
			SetAlchemyRecipeKnown("gold_dublon");
			SetAlchemyRecipeKnown("Chest");
			npchar.quest.meeting = "1"; 			
		break;
		
		case "items_1":
			dialog.text = "您想用比索还是杜布隆交易? ";
			link.l1 = "用比索。 ";
			link.l1.go = "items";
			link.l2 = "用杜布隆。 ";
			link.l2.go = "items_dub";
		break;
		
		case "items":
			if (npchar.quest.item_date != lastspeak_date)
			{
				GiveItemToTrader(npchar);
				npchar.quest.item_date = lastspeak_date;
			}
			if(CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu")) AddItems(npchar, "gold_dublon", 100);
			if(CheckAttribute(pchar, "questTemp.Del_Rostovshik_repeat")) AddItems(npchar, "gold_dublon", 100);
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
		break;
		
		case "items_dub":
			if (npchar.quest.item_date != lastspeak_date)
			{
				GiveItemToTrader(npchar);
				npchar.quest.item_date = lastspeak_date;
			}
			if(CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu")) AddItems(npchar, "gold_dublon", 100);
			if(CheckAttribute(pchar, "questTemp.Del_Rostovshik_repeat")) AddItems(npchar, "gold_dublon", 100);
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 1);
		break;
		
		//<<<<----------生成器 -"航运文件"。 ------		
		case "ShipLetters_Usurer1":
			pchar.questTemp.different.GiveShipLetters.speakUsurer = true;
			dialog.text = "阅读这些文件将花费我大量时间, 而我的时间是很宝贵的。 ";
			link.l1 = "也许" + sti(pchar.questTemp.different.GiveShipLetters.price1) + "比索能补偿您的时间? ";
			link.l1.go = "ShipLetters_Usurer2";
			link.l2 = "随您便。 再见! ";
			link.l2.go = "exit";
		break;
		
		case "ShipLetters_Usurer2":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.GiveShipLetters.price1));
			pchar.questTemp.different.GiveShipLetters.speakUsurer_1 = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "让我看看! 不, 我从未见过这个名字。 把它们拿给我们的港口主管看吧。 ";
				link.l1 = "对不起, 但我们有协议! 您答应过告诉我关于这位船长的事情! ";
				link.l1.go = "ShipLetters_Usurer2_1";
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
			{
				s1 = "嗯...我知道这艘船的主人。 他不是一个非常富有的人, 但他有一些财富。 ";
				dialog.text = s1 + " 据说他是一个成功的走私者。 这是您想听到的吗? ";
				link.l1 = "似乎是这样...";
				link.l1.go = "ShipLetters_Usurer2_2";
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
			{
				s1 = "嗯...我不确定我能恭喜您找到这个。 ";
				dialog.text = s1 + "这些文件是为我们的殖民巡逻船签署的, 它的船长以坚定的原则著称。 ";
				link.l1 = "巡逻船? 在指挥官的指挥下? ";
				link.l1.go = "ShipLetters_Usurer2_3";
			}
		break;
		
		case "ShipLetters_Usurer2_1":
			dialog.text = "我答应过您看这些文件, 仅此而已。 您可以走了。 ";
			link.l1 = "谢谢...我想。 ";
			link.l1.go = "exit";
		break;
		
		case "ShipLetters_Usurer2_2":
			dialog.text = "这由您决定。 我们的指挥官对这个人已经'感兴趣'很久了。 您已经有什么想法了吗? 而这里我们有一些没有标记的提货单...";
			link.l1 = "我明白了。 谢谢! ";
			link.l1.go = "exit";		
		break;
		
		case "ShipLetters_Usurer2_3":
			s1 = "正是。 顺便说一下, 我们的走私者对这位船长怀恨在心。 ";
			dialog.text = s1 + "正如我之前提到的, 文件的主人是一个有原则的人, 并不真正喜欢当地的犯罪行为。 ";
			link.l1 = "我明白了。 谢谢! ";
			link.l1.go = "exit";		
		break;

		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "啊, 我猜您就是那位带了我那浪子儿子和他年轻新娘的船长? ";
				link.l1 = "是的, 是我帮助他们逃脱的。 ";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "啊, 您来了, 我的恩人。 我想您是在等报酬吧? ";
				link.l1 = "至少您的感谢会很好...";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "我真的很感激您帮助我的孩子, 没有让他陷入那种麻烦的境地。 请允许我尽我所能感谢您。 接受这笔微薄的钱和我送的一件小礼物。 ";
			link.l1 = "谢谢。 能帮助这对年轻夫妇是我的荣幸。 ";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "感谢? 为了什么? 这个笨蛋半年都没工作, 却已经有时间找个女孩了! 我在他这个年纪已经经营自己的生意了。 有一位可嫁的总督女儿, 他却把这个妓女带到这里, 主啊, 请原谅我这么说! 现在他还在寻求我的祝福! ";
			link.l1 = "我猜您不相信感情? ";
			link.l1.go = "EncGirl_6_1";		
		break;
		
		case "EncGirl_5_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.EncGirl.sum));
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item); 
			AddQuestRecord("JungleGirl", "18");
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "EncGirl_6_1":
			dialog.text = "感情? 什么样的感情? 您是个成年人了, 还在谈论这些感情? 帮年轻人拉皮条, 真丢脸。 把女孩从她父母身边带走, 毁了我儿子的生活。 您别想从我这里得到任何感谢。 再见。 ";
			link.l1 = "那么再见...";
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("saw","saw"));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		贷款生成器 Loan
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "LoanUsurer":
			if (npchar.id == "Panama_Usurer")
			{
				if (sti(pchar.reputation.nobility) > 70 && ChangeCharacterNationReputation(pchar, SPAIN, 0) >= 80 && !CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold"))
				{
					dialog.text = "让我们讨论一下。 我在听。 ";
				}
				else
				{
					dialog.text = "呃, 呃。 恐怕我必须拒绝您, " + GetAddress_Form(NPChar) + "。 对不起, 但我的银行不向西班牙的敌人提供服务。 ";
					link.l1 = "金钱没有国籍, 西班牙银行家先生。 ";
					if (CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold"))
					{
						if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)) && makeint(Pchar.Quest.Deposits.(sDepositType1)) == true)
						{
							dialog.text = "嗯哼, " + GetAddress_Form(NPChar) + "。 我必须通知您, 您的存款不再有效。 ";
							Link.l1 = "基于什么理由? ! ";
							Link.l1.go = "Panama_Deposit_SgorelVklad";
							DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
							break;						
						}
						else
						{
							link.l1.go = "Panama_Deposit_Cartahena";
							break;
						}
					}
					if (sti(pchar.reputation.nobility) < 71 || ChangeCharacterNationReputation(pchar, SPAIN, 0) < 80)
					{
						link.l1.go = "Panama_Deposit_NoReputation";
						break;
					}
				}
			}
			dialog.text = "让我们讨论一下。 我在听。 ";
			//贷款
            if(CheckAttribute(Pchar, "Quest.Loans." + (NPC_Area)) && makeint(Pchar.Quest.Loans.(NPC_Area)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Loans.(NPC_Area).StartYear),makeint(Pchar.Quest.Loans.(NPC_Area).StartMonth),makeint(Pchar.Quest.Loans.(NPC_Area).StartDay), makefloat(Pchar.Quest.Loans.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				Pchar.Quest.Loans.(NPC_Area).Result = makeint(Pchar.Quest.Loans.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Loans.(NPC_Area).Sum)/100)*makefloat(Pchar.Quest.Loans.(NPC_Area).Interest))*(iPastMonths+1);// boal 23.01.2004
				if(makeint(PChar.money) >= makeint(Pchar.Quest.Loans.(NPC_Area).Result))
				{
					Link.l5 = "我欠您" + FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).Result)) + LinkRandPhrase(", 我准备好归还您的钱", "。 我想偿还债务。 ", "。 终于, 是时候还清了。 ");
					Link.l5.go = "loan_return";	
					sTemp = "credit";
				}					
			}
			else
			{
				Link.l6 = LinkRandPhrase("我想借些钱。 ", "我真的需要一些比索。 ", "来一笔小额贷款怎么样? ");
				Link.l6.go = "loan";					
				if(makeint(Pchar.money) >= 100)
				{
					Link.l7 = LinkRandPhrase("我想把我的钱存起来赚取利息。 ", "您愿意保管几袋我的银子吗? ", "我可以把一些银子留给您以备不时之需吗? "); // patch
					Link.l7.go = "deposit";				
				}			
				if(CheckUseDublons(NPChar))
				{
					Link.l8 = "我想存一些杜布隆赚取利息。 ";
					Link.l8.go = "deposit_dub";				
				}
			}
			
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)) && makeint(Pchar.Quest.Deposits.(sDepositType1)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Deposits.(sDepositType1).StartYear),makeint(Pchar.Quest.Deposits.(sDepositType1).StartMonth),makeint(Pchar.Quest.Deposits.(sDepositType1).StartDay), makefloat(Pchar.Quest.Deposits.(sDepositType1).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)+ ".Rem"))
				{
					Pchar.Quest.Deposits.(sDepositType1).Result = makeint(Pchar.Quest.Deposits.(sDepositType1).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType1).Sum)/100)*makefloat(Pchar.Quest.Deposits.(sDepositType1).Interest))*iPastMonths+sti(Pchar.Quest.Deposits.(sDepositType1).Rem);
				}
				else
				{
					Pchar.Quest.Deposits.(sDepositType1).Result = makeint(Pchar.Quest.Deposits.(sDepositType1).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType1).Sum)/100)*makefloat(Pchar.Quest.Deposits.(sDepositType1).Interest))*iPastMonths;
				}
				Link.l9 = LinkRandPhrase("我来取回我的投资, 用比索。 ", "是时候拿回你欠我的银子了。 ", "我需要用比索拿回我的投资和所有利息。 ");
				Link.l9.go = "Deposit_return";									
			}
			
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)) && makeint(Pchar.Quest.Deposits.(sDepositType2)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Deposits.(sDepositType2).StartYear),makeint(Pchar.Quest.Deposits.(sDepositType2).StartMonth),makeint(Pchar.Quest.Deposits.(sDepositType2).StartDay), makefloat(Pchar.Quest.Deposits.(sDepositType2).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)+ ".Rem"))
				{
					Pchar.Quest.Deposits.(sDepositType2).Result = makeint(Pchar.Quest.Deposits.(sDepositType2).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType2).Sum)/100)*makeint(Pchar.Quest.Deposits.(sDepositType2).Interest))*iPastMonths+sti(Pchar.Quest.Deposits.(sDepositType2).Rem);
				}
				else
				{
					Pchar.Quest.Deposits.(sDepositType2).Result = makeint(Pchar.Quest.Deposits.(sDepositType2).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType2).Sum)/100)*makeint(Pchar.Quest.Deposits.(sDepositType2).Interest))*iPastMonths;
				}
				Link.l10 = LinkRandPhrase("我想以杜布隆的形式取回我的投资。 ", "是时候拿回你欠我的金子了。 ", "我需要以杜布隆的形式拿回我的投资和所有利息。 ");
				Link.l10.go = "Deposit_return_dub";									
			}
/*			
			
*/			
			//退出
			if (sTemp == "credit")
			{
				link.l11 = "我记得我的债务, 但我还没准备好偿还...";
				link.l11.go = "Loan_Remind";
			}
			else
			{
				link.l11 = "我的错, 我和您没有任何财务问题。 再见。 ";
				link.l11.go = "exit";
			}
		break;
		
		//============== 贷款 ===============
		case "loan":
            if (sti(NPChar.nation) == PIRATE)
            {
                dialog.text = "不, 我不能帮助您。 在这个麻烦的地方, 我只能接受投资。 您可以投资银比索或金杜布隆。 ";				
                if(makeint(Pchar.money) >= 100)
				{
	                Link.l1 = "我想投资比索, 让我们谈谈金额。 ";
	                Link.l1.go = "deposit";
				}				
				if(CheckUseDublons(NPChar))
				{
					Link.l2 = "我想投资杜布隆。 让我们确定一下金额。 ";
					Link.l2.go = "deposit_dub";
				}
                Link.l3 = "不感兴趣。 ";
				link.l3.go = "exit";
                break;
            }
			// 检查职业适用性 -->
            if (isBadReputation(pchar, 42))
            {
                dialog.text = RandSwear() + "您的名字是" + GetFullName(pchar) + ", 对吧? 您有" +
                              RandPhraseSimple("坏名声", "坏名声") + ", 我不想和您做生意。 ";
				link.l1 = RandPhraseSimple("一个人就不能犯个错误吗? ", RandSwear() + "随便! ");
				link.l1.go = "exit";
                break;
            }
            // 检查职业适用性 <--
			Dialog.snd = "voice\USDI\USDI016";
			dialog.text = "哦, 您随时欢迎。 您需要多少金额? ";
			Link.l1 = "小额的。 ";
			Link.l1.go = "Small";
			Link.l2 = "中等的。 ";
			Link.l2.go = "Medium";
			Link.l3 = "尽可能大的。 ";
			Link.l3.go = "Large";
		break;

		case "small":
			Pchar.Quest.Loans.(NPC_Area).Sum = 500*makeint(Pchar.rank)+125*GetSummonSkillFromName(pchar,SKILL_COMMERCE);
			Dialog.snd = "voice\USDI\USDI017";
			dialog.text = "太好了! 处理小额款项总是容易得多 - 对双方来说风险都更小。 我可以给您" + FindRussianMoneyString(sti(Pchar.Quest.loans.(NPC_Area).sum)) + "...";
			Link.l1 = "成交。 您的利息是多少? ";
			Link.l1.go = "Interest";
			Link.l2 = "这对我不起作用。 让我们换一个。 ";
			Link.l2.go = "Loan";
			Link.l3 = "我想对我来说最好还是不要负债。 再见。 ";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Medium":
			Pchar.Quest.Loans.(NPC_Area).Sum = 1500*makeint(Pchar.rank)+325*GetSummonSkillFromName(pchar,SKILL_COMMERCE);
			Dialog.snd = "voice\USDI\USDI018";
			dialog.text = "没问题。 我希望" + FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).sum)) + "能帮助您解决问题。 这是一笔相当可观的金额。 ";
			Link.l1 = "成交。 您的利息是多少? ";
			Link.l1.go = "Interest";
			Link.l2 = "这对我不起作用。 让我们换一个。 ";
			Link.l2.go = "Loan";
			Link.l3 = "我想对我来说最好还是远离债务。 再见。 ";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Large":
			Pchar.Quest.Loans.(NPC_Area).Sum = 4000*makeint(Pchar.rank)+600*GetSummonSkillFromName(pchar,SKILL_COMMERCE);
			Dialog.snd = "voice\USDI\USDI019";
			dialog.text = "嗯... 这有风险。 好吧, 我准备为你提供一笔贷款, 金额为" + FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).sum)) + "。 我希望你明白, 船长, 这是一笔相当可观的数目。 我请你认真对待。 ";
			Link.l1 = "成交。 你的利息是多少? ";
			Link.l1.go = "Interest";
			Link.l2 = "这对我来说不行。 我们换一下。 ";
			Link.l2.go = "Loan";
			Link.l3 = "我想我最好还是远离债务。 再见。 ";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Interest":
		    Pchar.Quest.Loans.(NPC_Area).Interest = 4.0 + (makeint((((6.0 - 4.0) * (GetSummonSkillFromName(pchar, "Commerce") + GetSummonSkillFromName(pchar, "Leadership")) / 200) ) / 0.5 + 0.5)) * 0.5;
			//Pchar.Quest.Loans.(NPC_Area).Interest = 16 - makeint(Pchar.skill.commerce);
			// Rebbebion, 添加了百分比符号显示修复
			Dialog.snd = "voice\USDI\USDI020";
			dialog.text = ""+ fts(stf(Pchar.Quest.Loans.(NPC_Area).Interest), 1) + "%% 每月。 根据我对你的了解, 我无法提供更好的条件。 "; 
			Link.l1 = "对我来说可行。 我们谈谈时间吧。 ";
			Link.l1.go = "Period";
			Link.l3 = "我想我最好还是远离债务。 再见。 ";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Period":
			Pchar.Quest.Loans.(NPC_Area).Period = makeint(makeint(Pchar.reputation.nobility)/20) + 1;			
			Dialog.snd = "voice\USDI\USDI021";
			dialog.text = "考虑到我对你的了解, " + Pchar.name + ", 我会等待你在" + FindRussianMonthString(sti(Pchar.Quest.Loans.(NPC_Area).Period)) + "内偿还这笔贷款。 之后我会采取某些措施。 希望你明白这一点。 "; 
			Link.l1 = "我很高兴接受你的条件... 还有你的金币。 ";
			Link.l1.go = "LoanGranted";
			Link.l3 = "抱歉, 这对我来说不行。 再见。 ";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "LoanGranted":
			Dialog.snd = "voice\USDI\USDI022";
			dialog.text = "我由衷地高兴。 但让我提醒你。 我做这行很久了, 知道如何收回我的投资。 所以如果你有任何愚蠢的想法, 我建议你打消它们\n无意冒犯, 只是提醒。 ";
			Link.l1 = "嗯... 好吧。 再见。 ";
			Link.l1.go = "LoanGranted_exit";
		break;

		case "Loan_Remind":
			Dialog.snd = "voice\USDI\USDI023";
			dialog.text = "这是你的选择, 船长。 我的利息在增长, 而你没有那么多时间了。 ";
			Link.l1 = "别担心。 再见。 ";
			Link.l1.go = "exit";
		break;

		case "loan_return":
			addMoneyToCharacter(Pchar, -(makeint(Pchar.Quest.Loans.(NPC_Area).Result)));
			// boal 27.01.2004 -->
            if (npchar.quest.trade_date != lastspeak_date) // 存在升级漏洞
            {
    			AddCharacterExpToSkill(Pchar, "Commerce", makeint(Pchar.Quest.Loans.(NPC_Area).Result) / 350);
    			AddCharacterExpToSkill(Pchar, "Leadership", makeint(Pchar.Quest.Loans.(NPC_Area).Result) / 700);
			}
			// boal 27.01.2004 <--
			DeleteAttribute(PChar, "quest.Loans_" + NPC_Area); // 漏洞修复
			DeleteAttribute(PChar, "quest.Loans." + NPC_Area);
			Dialog.snd1 = "voice\USDI\USDI024";
			Dialog.snd2 = "voice\USDI\USDI025";
			Dialog.snd3 = "voice\USDI\USDI026";
			dialog.text = LinkRandPhrase("太棒了! 当你需要金币时来找我。 我随时为你服务。 ", "感谢你。 与能够及时偿还债务的人打交道总是令人愉快的。 你知道, 有时会发生一些事情, 我可以理解... 但我更喜欢问题得到解决。 ", "哦, 我信任你是对的, " + GetAddress_Form(NPChar) + "! 我希望这不是你最后一次使用我的服务。 也许我们甚至可以为你达成更好的交易, 因为现在我知道你是一个诚实的人。 ");
			Link.l1 = LinkRandPhrase("我想借些钱。 ", "我真的需要一些比索。 ", "小额贷款怎么样? ");
			Link.l1.go = "loan";			
			if(makeint(PChar.money) >= 100)
			{
				Link.l2 = LinkRandPhrase("我想投资我的钱。 ", "你会保留一些海盗赃物吗? ", "我可以给你留一些银币以备不时之需吗? ");
				Link.l2.go = "deposit";				
			}		
			if(CheckUseDublons(NPChar))	
			{
				Link.l3 = "我想投资一些达布隆以获取利息";
				Link.l3.go = "deposit_dub";				
			}
			Link.l4 = "再见, " + NPchar.name + "。 ";
			Link.l4.go = "ExitDelLoan1";
		break;

		case "deposit":
			dialog.text = LinkRandPhrase("我看到一个明智的人! 你想投资多少金额? ", "很好。 相信我, 这笔钱会安全地在这里等待你, 并带着所有利息。 ", "我看你知道这辈子什么才是真正重要的。 你想投资多少? ");
			link.l1.edit = 3;
			link.l1 = "";	
			Link.l1.go = "result";
		break;
		
		case "result":
			Pchar.QuestTemp.Deposits.(sDepositType1).Interest = GetDepositRate();
			Pchar.QuestTemp.Deposits.(sDepositType1).Sum = dialogEditStrings[3];
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp <= 0)
			{
				dialog.text = "开玩笑吗? ";
				link.l1 = "我的错。 ";
				link.l1.go = "exit";
				break;
			}
			if (iTemp > sti(pchar.money))
			{
				dialog.text = "嗯, 不幸的是你没有那么多钱。 我们认真点... ";
				link.l1 = "好吧。 ";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "好的。 我可以给你... 比如说... " + fts(stf(Pchar.QuestTemp.Deposits.(sDepositType1).Interest), 1) + " %。 当然是每月。 ";
			Link.l1 = "这对我来说可行。 ";
			Link.l1.go = "Deposit_placed";
			Link.l2 = "我最好改变金额。 ";
			Link.l2.go = "Deposit";
			Link.l3 = "看来这是个坏主意... 再见。 ";
			Link.l3.go = "Exit";
		break;

		case "Deposit_placed":
			Dialog.snd = "voice\USDI\USDI033";
			if ( !CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)+".Result"))
			{
			    Pchar.Quest.Deposits.(sDepositType1).Result = 0;//修复
			}
			// boal 限制
			if ( (sti(Pchar.Quest.Deposits.(sDepositType1).Result) + sti(Pchar.QuestTemp.Deposits.(sDepositType1).Sum)) > sti(NPChar.UsurerDeposit)*1000)
			{
			    dialog.text = "抱歉, 船长, 但这笔金额对我的殖民地银行来说太大了。 我无法支付你的利息。 而且缺乏可靠的守卫... 希望你能理解。 无论如何, 我能接受你的最大金额是" +
						FindRussianMoneyString(MakeMoneyShow(sti(NPChar.UsurerDeposit)*1000, MONEY_SIGN,MONEY_DELIVER)) + "。 ";
				Link.l1 = "太糟糕了, 我得找另一个银行家了。 ";
				Link.l1.go = "Exit";
			}
			else
			{
				dialog.text = "现在你可以放心, 即使是最强的风暴也不会让你身无分文。 ";
				Link.l1 = "好的。 再见。 ";
				Link.l1.go = "Deposit_Exit";
			}
		break;
		
		case "Deposit_return":
			Dialog.snd = "voice\USDI\USDI034";
			dialog.text = "考虑到承诺的利息和经过的时间, 我欠你" + FindRussianMoneyString(sti(Pchar.Quest.Deposits.(sDepositType1).Result)) + "... 你确定要取钱吗? ";
			Link.l1 = "绝对确定。 给我吧。 ";			
			Link.l1.go = "Deposit_return_1";		
			Link.l2 = "我想取一部分钱。 ";			
			Link.l2.go = "Deposit_return_part";
			Link.l3 = "你说得对。 我让它在你这里再放一段时间。 祝你有美好的一天。 ";			
			Link.l3.go = "Exit";		
		break;		
		
		case "Deposit_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)+ ".Rem"))
			{
				DeleteAttribute(Pchar,"Quest.Deposits." + (sDepositType1)+ ".Rem");
			}
			Pchar.Quest.Deposits.(sDepositType1).Interest = stf(Pchar.QuestTemp.Deposits.(sDepositType1).Interest);
			Pchar.Quest.Deposits.(sDepositType1).Sum      = sti(Pchar.QuestTemp.Deposits.(sDepositType1).Sum);
			Pchar.Quest.Deposits.(sDepositType1).city 	  = NPC_Area;	

			AddMoneyToCharacter(Pchar, -(makeint(Pchar.Quest.Deposits.(sDepositType1).Sum)));
			// 总债务
			Pchar.Quest.Deposits.(sDepositType1).Sum = sti(Pchar.Quest.Deposits.(sDepositType1).Result) + sti(Pchar.Quest.Deposits.(sDepositType1).Sum);
			Pchar.Quest.Deposits.(sDepositType1) = true;
			Pchar.Quest.Deposits.(sDepositType1).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType1).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType1).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType1).StartTime 	= getTime();
			DialogExit();
		break;
		
		//--> Jason 部分取款
		case "Deposit_return_part":
			dialog.text = "那取多少? ";
			link.l1.edit = 4;
			link.l1 = "";	
			Link.l1.go = "result_part";
		break;

		case "result_part":
			iTemp = sti(dialogEditStrings[4]);
			if (iTemp <= 0)
			{
				dialog.text = "这玩笑太愚蠢了, 先生! ";			
				link.l1 = "该死! 非常抱歉... 我们换个金额吧。 ";	
				Link.l1.go = "Deposit_return_part";
				break;
			}
			if (iTemp > sti(Pchar.Quest.Deposits.(sDepositType1).Result))
			{
				dialog.text = "你的账户上没有那么多钱。 ";			
				link.l1 = "该死! 我的错。 我们换个金额吧。 ";	
				Link.l1.go = "Deposit_return_part";
				break;
			}
			if (iTemp == sti(Pchar.Quest.Deposits.(sDepositType1).Result))
			{
				dialog.text = "全部取走? 好吧, 如你所说。 这是你的钱。 ";			
				link.l1 = "感谢! ";	
				Link.l1.go = "Deposit_return_all";
				break;
			}
			dialog.text = "好的。 拿着。 这是你的钱。 ";			
			link.l1 = "谢谢! ";	
			Link.l1.go = "result_part_1";
		break;
		
		case "result_part_1":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			addMoneyToCharacter(Pchar, iTemp);
			iRes = sti(Pchar.Quest.Deposits.(sDepositType1).Result)-iTemp; //账户余额
			fPer = stf(Pchar.Quest.Deposits.(sDepositType1).Interest);
			iDep = sti(Pchar.Quest.Deposits.(sDepositType1).Sum); //初始金额
			if (iRes <= sti(Pchar.Quest.Deposits.(sDepositType1).Sum)) // 变得小于初始金额
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
				Pchar.Quest.Deposits.(sDepositType1).Interest = fPer;
				Pchar.Quest.Deposits.(sDepositType1).Sum = iRes;
				Pchar.Quest.Deposits.(sDepositType1).Result = 0;
			}
			else // 如果余额大于初始金额 - 利息继续从初始金额计算, 而不是余额, 因为没必要, 差额会加到应计利息上 - 银行家 Jason :) 
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
				Pchar.Quest.Deposits.(sDepositType1).Interest = fPer;
				Pchar.Quest.Deposits.(sDepositType1).Sum = iDep;
				Pchar.Quest.Deposits.(sDepositType1).Rem = iRes-iDep;
			}
			Pchar.Quest.Deposits.(sDepositType1).city 	  	= NPC_Area;	
			Pchar.Quest.Deposits.(sDepositType1) 			= true;
			Pchar.Quest.Deposits.(sDepositType1).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType1).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType1).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType1).StartTime 	= getTime();
		break;
		
		case "Deposit_return_all":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			addMoneyToCharacter(Pchar, iTemp);
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
		break;
		//< —部分取款		
		
		case "Deposit_return_1":
			addMoneyToCharacter(Pchar, makeint(Pchar.Quest.Deposits.(sDepositType1).Result));
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "哦... 失去它真是太难了。 我真的已经习惯了这笔钱。 无论如何, 再来吧。 ";			
			Link.l1 = "如果需要, 我会的。 再见。 ";			
			Link.l1.go = "Exit";
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
		break;
		
		//  ugeen -> 达布隆存款	
		case "deposit_dub":
			dialog.text = LinkRandPhrase("我看到一个明智的人! 你想投资多少金额? ", "很好。 相信我, 这笔钱会安全地在这里等待你, 并带着所有你的利息。 ", "我看你知道这辈子什么才是真正重要的。 你想投资多少? ");
			link.l1.edit = 3;
			link.l1 = "";	
			Link.l1.go = "result_dub";
		break;
		
		case "result_dub":		
			iTotalDublonQty = GetCharacterItem(pchar,"gold_dublon") + CheckItemMyCabin("gold_dublon");		
			Pchar.QuestTemp.Deposits.(sDepositType2).Interest = 1;
			Pchar.QuestTemp.Deposits.(sDepositType2).Sum = dialogEditStrings[3];
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp <= 0)
			{
				dialog.text = "开玩笑吗? ";
				link.l1 = "嗯, 我的错... ";
				link.l1.go = "exit";
				break;
			}						
			if (iTemp > iTotalDublonQty)
			{
				dialog.text = "嗯, 不幸的是你没有那么多钱。 我们认真点... ";
				link.l1 = "嗯... 好的。 ";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "好的。 我可以给你... 比如说... " + Pchar.QuestTemp.Deposits.(sDepositType2).Interest + " %。 当然是每月。 ";
			Link.l1 = "这对我来说可行。 ";
			Link.l1.go = "Deposit_placed_dub";
			Link.l2 = "我最好改变金额。 ";
			Link.l2.go = "Deposit_dub";
			Link.l3 = "我想我最好还是保留我的黄金。 再见。 ";
			Link.l3.go = "Exit";
		break;
		
		case "Deposit_placed_dub":
			Dialog.snd = "voice\USDI\USDI033";
			if ( !CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)+".Result"))
			{
			    Pchar.Quest.Deposits.(sDepositType2).Result = 0;//修复
			}
			// boal 限制
			if ( (sti(Pchar.Quest.Deposits.(sDepositType2).Result) + sti(Pchar.QuestTemp.Deposits.(sDepositType2).Sum)) > sti(NPChar.UsurerDeposit)*10)
			{
			    dialog.text = "抱歉, 船长, 但这笔金额对我的殖民地银行来说太大了。 我无法支付你的利息。 而且缺乏可靠的守卫... 希望你能理解。 无论如何, 我能接受你的最大金额是" +
						FindRussianDublonString(MakeMoneyShow(sti(NPChar.UsurerDeposit)*10, MONEY_SIGN,MONEY_DELIVER)) + "。 ";
				Link.l1 = "太糟糕了, 我得找另一个银行家了。 ";
				Link.l1.go = "Exit";
			}
			else
			{
				dialog.text = "现在你可以放心, 即使是最强的风暴也不会让你身无分文。 ";
				Link.l1 = "不错。 再见。 ";
				Link.l1.go = "Deposit_Exit_dub";
			}
		break;
		
		case "Deposit_return_dub":
			Dialog.snd = "voice\USDI\USDI034";
			dialog.text = "考虑到承诺的利息和经过的时间, 我欠你" + FindRussianDublonString(sti(Pchar.Quest.Deposits.(sDepositType2).Result)) + "... 你确定要取钱吗? ";
			Link.l1 = "绝对确定。 给我吧。 ";			
			Link.l1.go = "Deposit_return_dub_1";		
			Link.l2 = "我想取一部分钱。 ";			
			Link.l2.go = "Deposit_return_dub_part";
			Link.l3 = "你说得对。 我让它在你这里再放一段时间。 祝你有美好的一天。 ";			
			Link.l3.go = "Exit";		
		break;	

		case "Deposit_exit_dub":
			NextDiag.CurrentNode = NextDiag.TempNode;		
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)+ ".Rem"))
			{
				DeleteAttribute(Pchar,"Quest.Deposits." + (sDepositType2)+ ".Rem");
			}	
			Pchar.Quest.Deposits.(sDepositType2).Interest = sti(Pchar.QuestTemp.Deposits.(sDepositType2).Interest);
			Pchar.Quest.Deposits.(sDepositType2).Sum      = sti(Pchar.QuestTemp.Deposits.(sDepositType2).Sum);
			Pchar.Quest.Deposits.(sDepositType2).city 	  = NPC_Area;	
			
			iTemp = GetCharacterItem(pchar,"gold_dublon");
			if(iTemp > sti(Pchar.Quest.Deposits.(sDepositType2).Sum))
			{
				TakeNItems(pchar,"gold_dublon", -sti(Pchar.Quest.Deposits.(sDepositType2).Sum));
			}
			else
			{
				TakeNItems(pchar,"gold_dublon", -iTemp));
				iTemp = sti(Pchar.Quest.Deposits.(sDepositType2).Sum) - iTemp;
				GetItemMyCabin("gold_dublon", iTemp);
			}
						
			// 总债务
			Pchar.Quest.Deposits.(sDepositType2).Sum = sti(Pchar.Quest.Deposits.(sDepositType2).Result) + sti(Pchar.Quest.Deposits.(sDepositType2).Sum);
			Pchar.Quest.Deposits.(sDepositType2) = true;
			Pchar.Quest.Deposits.(sDepositType2).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType2).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType2).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType2).StartTime 	= getTime();
			DialogExit();
		break;	
		
		//-->达布隆部分取款
		case "Deposit_return_dub_part":
			dialog.text = "那取多少? ";
			link.l1.edit = 4;
			link.l1 = "";	
			Link.l1.go = "result_dub_part";
		break;
		
		case "result_dub_part":
			iTemp = sti(dialogEditStrings[4]);
			if (iTemp <= 0)
			{
				dialog.text = "这玩笑太愚蠢了, 先生! ";			
				link.l1 = "该死! 非常抱歉... 我们换个金额吧... ";	
				Link.l1.go = "Deposit_return_dub_part";
				break;
			}			
			if (iTemp > sti(Pchar.Quest.Deposits.(sDepositType2).Result))
			{
				dialog.text = "你的账户上没有那么多黄金, 先生。 ";			
				link.l1 = "该死! 我的错。 我们换个金额吧... ";	
				Link.l1.go = "Deposit_return_dub_part";
				break;
			}			
			if (iTemp == sti(Pchar.Quest.Deposits.(sDepositType2).Result))
			{
				dialog.text = "全部取走? 好吧, 如你所说。 这是你的钱。 ";			
				link.l1 = "谢谢! ";	
				Link.l1.go = "Deposit_return_dub_all";
				break;
			}
			dialog.text = "好的。 拿着。 这是你的钱。 ";			
			link.l1 = "感谢! ";	
			Link.l1.go = "result_dub_part_1";
		break;
		
		case "result_dub_part_1":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			TakeNItems(pchar,"gold_dublon", iTemp);
			iRes = sti(Pchar.Quest.Deposits.(sDepositType2).Result)-iTemp; //账户余额
			iPer = sti(Pchar.Quest.Deposits.(sDepositType2).Interest);
			iDep = sti(Pchar.Quest.Deposits.(sDepositType2).Sum); //初始金额
			if (iRes <= sti(Pchar.Quest.Deposits.(sDepositType2).Sum)) // 变得小于初始金额
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
				Pchar.Quest.Deposits.(sDepositType2).Interest = iPer;
				Pchar.Quest.Deposits.(sDepositType2).Sum = iRes;
				Pchar.Quest.Deposits.(sDepositType2).Result = 0;
			}
			else // 如果余额大于初始金额 - 利息继续从初始金额计算, 而不是余额, 因为没必要, 差额会加到应计利息上 - 银行家 Jason :) 
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
				Pchar.Quest.Deposits.(sDepositType2).Interest = iPer;
				Pchar.Quest.Deposits.(sDepositType2).Sum = iDep;
				Pchar.Quest.Deposits.(sDepositType2).Rem = iRes-iDep;
			}
			Pchar.Quest.Deposits.(sDepositType2).city 	  	= NPC_Area;	
			Pchar.Quest.Deposits.(sDepositType2) 			= true;
			Pchar.Quest.Deposits.(sDepositType2).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType2).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType2).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType2).StartTime 	= getTime();
		break;
		
		case "Deposit_return_dub_all":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			TakeNItems(pchar,"gold_dublon", iTemp);
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
		break;
		//< —部分取款		
		
		case "Deposit_return_dub_1":
			TakeNItems(pchar,"gold_dublon", sti(Pchar.Quest.Deposits.(sDepositType2).Result));
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "哦... 失去它真是太难了。 我真的已经习惯了这笔钱。 无论如何, 再来吧。 ";			
			Link.l1 = "如果需要, 我会的。 再见。 ";			
			Link.l1.go = "Exit";
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
		break;
		//  ugeen <- 达布隆存款	
		
		case "DeadMotherfucker":
			Dialog.TempNode = "DeadMotherFucker_1";
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "你还活着? 也许想还我的钱? 去你的! 我损失了这么多钱, 你永远也还不清! 在看到你 lifeless 的身体之前, 我不会安息! ";
            Link.l1 = "我只是想以和平的方式解决问题。 ";
			Link.l1.go = "LoanRestore_1";
			Link.l2 = LinkRandPhrase("很好, 那就看看吧! 要知道你也不是免受死亡威胁的! ", "威胁? 那就看看你要做什么... ", "钱不是我们生活中最重要的东西。 不要为了它过度悲伤和杀人, 来吧, 我敢你。 ");
			Link.l2.go = "ExitDelLoan2";
		break;

		case "DeadMotherFucker_1":			
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "滚出去! 我希望再也不要见到你。 ";			
			Link.l1 = "... ";			
			Link.l1.go = "ExitDelLoan2";
            Dialog.TempNode = "DeadMotherFucker_1";
		break;
		// boal 可恢复性错误 -->
		case "LoanRestore_1":
            iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Loans.(NPC_Area).StartYear),makeint(Pchar.Quest.Loans.(NPC_Area).StartMonth),makeint(Pchar.Quest.Loans.(NPC_Area).StartDay), makefloat(Pchar.Quest.Loans.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
			Pchar.Quest.Loans.(NPC_Area).Result = makeint(Pchar.Quest.Loans.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Loans.(NPC_Area).Sum)/100)*makefloat(Pchar.Quest.Loans.(NPC_Area).Interest))*(iPastMonths+1);
			dialog.text = "哦, 真的吗? 你有什么打算? ";
			Link.l1 = "今天我欠你" + FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).Result)) + "。 我把这笔钱给你。 ";
			Link.l1.go = "DeadMotherFucker_1";
            if (sti(Pchar.Money) >= 2*sti(Pchar.Quest.Loans.(NPC_Area).Result))
            {
    			Link.l2 = "我提议用我的债务来重建与你的良好关系。 金额是" + FindRussianMoneyString(2*sti(Pchar.Quest.Loans.(NPC_Area).Result)) + "。 ";
    			Link.l2.go = "LoanRestore_2";
			}
		break;
		
		case "LoanRestore_2":
			dialog.text = "现在我们在谈了! 毕竟我可以和你做生意。 ";
			Link.l1 = "谢谢。 我不会再让你失望了。 ";
			Link.l1.go = "ExitDelLoan2";
			NextDiag.TempNode = "First time";			
			addMoneyToCharacter(Pchar, -2*sti(Pchar.Quest.Loans.(NPC_Area).Result));
			DeleteAttribute(PChar, "quest.Loans_" + NPC_Area);
			DeleteAttribute(PChar, "quest.Loans." + NPC_Area);
			ChangeCharacterHunterScore(PChar, NationShortName(sti(NPChar.nation)) + "hunter", -30);
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
		break;

		case "ExitDelLoan1":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteAttribute(Pchar, "quest.Loans." + (NPC_Area));
		break;

		case "ExitDelLoan2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteAttribute(Pchar, "quest.Loans." + (NPC_Area));
			DeleteAttribute(Pchar, "quest.Deposits." + (NPC_Area));
		break;
		
        case "LoanGranted_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;

			AddMoneyToCharacter(Pchar, makeint(Pchar.Quest.Loans.(NPC_Area).Sum));
			Pchar.Quest.Loans.(NPC_Area) = true;
			Pchar.Quest.Loans.(NPC_Area).StartDay = getDataDay();
			Pchar.Quest.Loans.(NPC_Area).StartMonth = getDataMonth();
			Pchar.Quest.Loans.(NPC_Area).StartYear = getDataYear();
			Pchar.Quest.Loans.(NPC_Area).StartTime = getTime();

			sTemp = "Loans_" + NPC_Area;			
			SetTimerCondition(sTemp, 0, makeint(Pchar.Quest.Loans.(NPC_Area).Period), 0, false);
			pchar.quest.(sTemp).CityId = NPC_Area;
			pchar.quest.(sTemp).win_condition = "LoansForAll";
			
			DialogExit();
			npchar.quest.trade_date = lastspeak_date; // 存在升级漏洞
		break;
        
		//奴隶商人
		int iSlaveMoney;
		int amount;
		case "GiveTaskSlave":
			pchar.questTemp.Slavetrader.iSlaveQuantity = 100;
			pchar.questTemp.Slavetrader.iSlaveMoney = sti(pchar.questTemp.Slavetrader.iSlaveQuantity) * 250;
			dialog.Text = "啊, 来吧! 我们是认真的人, 你和我, 我们比那些准备为一个达布隆而死, 却从不想用它赚两个达布隆的白痴更好\n我在寻找一个可以提供严肃生意的人。 一个勇敢。 积极。 诚实。 守时, 但不被... 嗯... 太多道德困境所困扰的人。 我希望你就是我要找的人。 ";
			Link.l1 = "这将取决于你要给我提供什么样的‘交易’。 ";
			Link.l1.go = "GiveTaskSlave_1";
		break;
			
		case "GiveTaskSlave_1":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity(npchar.city);
			dialog.Text = "很好, 那就听着。 奴隶制是现在加勒比地区最赚钱的生意。 我不是种植园主, 但我有值得信赖的客户\n所以, 我需要以下数量的奴隶 - " + pchar.questTemp.Slavetrader.iSlaveQuantity + " 个。 我准备每个给你 250 比索。 相信我, 这是个好价格。 总共你将赚" + FindRussianMoneyString(sti(pchar.questTemp.Slavetrader.iSlaveMoney)) + "。 ";
			Link.l1 = "不, 我不是奴隶贩子。 你自己找另一个不在乎良心的助手吧。 ";
			Link.l1.go = "exit_slaves";
			Link.l2 = "一个诱人的提议。 我想做。 你多久需要这些奴隶? ";
			Link.l2.go = "GiveTaskSlave_2";
		break;
			
		case "exit_slaves":
			dialog.Text = "嗯, 看来没有人愿意动屁股去拿脚下的金子。 我很失望, 非常。 再见, 甚至不要想传播关于我们谈话的流言。 我的手臂很长... ";
			Link.l1 = "你的手‘脏’... 就像你的舌头一样。 再见。 ";
			Link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "End_quest";
			DeleteAttribute(npchar, "quest.slave");
		break;
			
		case "GiveTaskSlave_2":
			dialog.Text = "我不会限制你的时间, 但尽量尽快完成你的任务。 对‘黑色象牙’的需求很大。 如果你做得好, 我以后会经常给你这样的工作。 ";
			Link.l1 = "听起来不错。 好吧, 等待好消息。 ";
			Link.l1.go = "exit";						
			pchar.questTemp.Slavetrader = "Seek_slaves"; // 这是任务名称和任务状态的输入
			AddQuestRecord("Slavetrader", "1");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("Slavetrader", "sQty", makeint(pchar.questTemp.Slavetrader.iSlaveQuantity));
			AddQuestUserData("Slavetrader", "sSum", makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			LAi_LocationDisableOfficersGen(&Locations[FindLocation(pchar.location)], true); // 2015 年阻止官员进入
		break;
			
		case "Checkslaves":
			amount = GetSquadronGoods(Pchar, GOOD_SLAVES) - sti(pchar.questTemp.Slavetrader.iSlaveQuantity);
			dialog.Text = "你成功获得那批‘黑色象牙’了吗? ";
            if (amount < 0)
			{
				Link.l1 = "还没有。 只是检查我们的协议是否仍然有效。 ";
            	Link.l1.go = "exit";
			}
			else
			{
				Link.l1 = "我有。 它们都在我的货物里。 ";
            	Link.l1.go = "Takeslaves";
			}
		break;
		
		case "Takeslaves":
			amount = sti(pchar.questTemp.Slavetrader.iSlaveQuantity);
			dialog.Text = "太好了。 我的人会带走它们... 不用担心海关或堡垒的指挥官。 我在这里经营着一个庞大的业务, 所以不要指望会有任何麻烦, 也没有人会指控你走私。 ";
			Link.l1 = "看来你在这里有很强的地位... 那么我的付款呢? ";
            Link.l1.go = "Takeslaves_1";
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, amount);
		break;
		
		case "Takeslaves_1":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			dialog.Text = "给你。 我不空谈。 和我在一起, 船长, 很快你就会拥有足够多的黄金, 需要一艘大帆船来搬运! ";
			Link.l1 = "那太好了哈哈... 接下来呢? ";
            Link.l1.go = "Takeslaves_2";
		break;
		
		case "Takeslaves_2":
			dialog.Text = "接下来? 三周后再来这里。 我现在正在准备一笔交易, 大约那时应该准备好了。 ";
			Link.l1 = "很好, 成交。 再见。 ";
            Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "2");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.questTemp.Slavetrader = "wait";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait");//记住日期
		break;
		
		case "Takeslaves_3":
			if (4-sti(RealShips[sti(pchar.ship.type)].Class) < 0)//检查船的等级
			{
				dialog.Text = "我有工作, 但你的船太弱了。 我不想让你失败, 也不想送你去死。 还有时间, 所以至少给自己找一艘更大的船, 如巴尔肯廷帆船。 布里甘廷帆船。 双桅横帆船或长笛帆船。 不要浪费时间! ";
				Link.l1 = "我明白, 我会处理的。 再见。 ";
            	Link.l1.go = "Takeslaves_3_smallship";
			}
			else
			{
				dialog.Text = "终于! 我在等你。 现在我们直奔主题。 如你所知, 任何生意都有竞争对手... 我也有我的竞争对手。 这些贪婪和不择手段的混蛋总是渴望从我这里抢走客户! 实际上, 我想除掉其中一个, 同时赚一笔好钱。 ";
				Link.l1 = "我洗耳恭听。 ";
            	Link.l1.go = "Takeslaves_4";
			}
		break;
		
		case "Takeslaves_3_smallship":
			pchar.questTemp.Slavetrader = "waitship";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Takeslaves_4":
			Slavetrader_GetRandomShore();//选择海湾
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.questTemp.Slavetrader.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "非常好。 现在听着。 这个叫" + GetName( NAMETYPE_ORIG, pchar.questTemp.Slavetrader.UnknownPirateName, NAME_NOM) + "的流氓从非洲带来了奴隶, 并在" + XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore + "Gen") + "抛锚了, 它在一个叫" + XI_ConvertString(pchar.questTemp.Slavetrader.Island) + "的岛上。 他在那里等待走私者。 他的大帆船叫‘" + pchar.questTemp.Slavetrader.ShipName + "’。 他们的交易必须不惜一切代价打破! ";
			link.l1 = "那奴隶呢? 沉没它们太浪费了! ";
			link.l1.go = "Takeslaves_5";
		break;
		
		case "Takeslaves_5":
			dialog.Text = "你为什么要那样做? 没有必要。 " + GetName( NAMETYPE_ORIG, pchar.questTemp.Slavetrader.UnknownPirateName, NAME_NOM) + "名声不好, 没有人会为他的消失而难过。 登上他的大帆船, 杀了那个人, 确保他死透, 把货物带给我, 我会卖掉它。 根据我的消息, 大约有一千五百个奴隶。 ";
			Link.l1 = "哇。 数量相当多。 我的付款呢? ";
            Link.l1.go = "Takeslaves_6";
			Link.l2 = "不, 先生, 这种阴谋不适合我。 我为什么要破坏与走私者的关系? ";
            Link.l2.go = "exit_slaves_1";
		break;
		
		case "exit_slaves_1":
			dialog.Text = "嗯... 看来我看错你了... 再见, 忘了我们的谈话。 不要散布你在这里听到的流言。 我拥有这个城镇。 如果你打算为自己登上‘" + pchar.questTemp.Slavetrader.ShipName + "’... 我会确保你最终上绞架。 考虑一下。 ";
			Link.l1 = "别担心, 我不会向当局报告, 我也不需要你的大帆船。 再见。 ";
            Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase(" agreed"," agreed"));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";//任务结束
		break;
		
		case "Takeslaves_6":
			dialog.Text = "考虑到我给了你货物的位置, 你不需要航行寻找‘奖品’, 付款略低 - 每个头 200 比索。 即便如此, 成功的话也是一大笔钱 - 三十万比索, 还有这艘船。 ";
			Link.l1 = "成交。 我有多少时间? ";
            Link.l1.go = "Takeslaves_7";
			Link.l2 = "呵呵! 你说得好像那些奴隶会自己游到我的船上, 希望尽快进入我的货物一样! 你真的想让我的人为了这么点钱冒生命危险吗? 增加我的奖励, 否则我退出这门生意。 ";
            Link.l2.go = "exit_slaves_1";
		break;
		
		case "Takeslaves_7":
			dialog.text = "你有两周时间。 不要迟到, 否则他会转移货物, 一切都完了。 ";
			link.l1 = "那得赶紧了。 期待我带来好消息。 ";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "3");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
			AddQuestUserData("Slavetrader", "sShoreName", XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore + "Dat")); // belamour gen
			AddQuestUserData("Slavetrader", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.questTemp.Slavetrader.Island) + "Voc")); // belamour gen
			pchar.quest.Slavetrader_ShipsAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_ShipsAttack.win_condition.l1.location = pchar.questTemp.Slavetrader.Island;
            pchar.quest.Slavetrader_ShipsAttack.function = "Slavetrader_CreateSlaveShips";//创建船只
			SetFunctionTimerCondition("Slavetrader_SlaveShipsOver", 0, 0, 15, false);	//定时器
			pchar.questTemp.Slavetrader = "wait1";	//这是占位符
		break;
		
		case "Takeslaves_4_lose":
			dialog.text = "那么, " + GetFullName(pchar) + ", 我们的任务怎么样了? 你那愁眉苦脸的样子告诉我你失败了。 ";
			link.l1 = "该死, 你说得对... 我... 嗯, 你知道... 我迟到了。 好像他已经离开了那个地方, 因为我在那里一个人也没找到。 一路上不得不顺风航行, 该死的... ";
			link.l1.go = "Takeslaves_5_lose";
		break;
		
		case "Takeslaves_4_win":
			dialog.text = "那么, " + GetFullName(pchar) + ", 你今天的收获是什么? 他们告诉我" + GetName( NAMETYPE_ORIG, pchar.questTemp.Slavetrader.UnknownPirateName, NAME_NOM) + "喂鱼了! 哈哈哈! ";
			link.l1 = "是的, 我刚好及时赶到! " + GetName( NAMETYPE_ORIG, pchar.questTemp.Slavetrader.UnknownPirateName, NAME_NOM) + "正在把奴隶转移到走私者的船上。 我不得不登上他们两艘船, 把他们都送到戴维.琼斯那里, 所以你现在的竞争对手更少了。 ";
			link.l1.go = "Takeslaves_5_win";
		break;
		
		case "Takeslaves_5_lose":
			dialog.text = "是的, 我想我看错你了。 你迟到了? 还是太害怕不敢战斗? 不管怎样, 现在都没有意义了。 滚开。 我和你完了。 忘记你在这里看到或听到的一切。 ";
			link.l1 = "那么再见。 ";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "5_5");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
		
		case "Takeslaves_5_win":
			pchar.questTemp.Slavetrader.Nation = npchar.nation;
			amount = 1600 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			if (amount < 0)
			{
				dialog.text = "我没看错你 —" + GetSexPhrase("你是个潇洒的暴徒", "你是个凶猛的少女") + "! 我需要像你这样的人。 你以最出色的方式完成了任务 —你带来了一千五百多个奴隶! 不幸的是, 我只能支付你一千六百个奴隶的钱。 我没有足够的硬币支付剩下的, 所以你得自己卖掉它们。 你的奖励是32万比索。 ";
				link.l1 = "感谢。 和你做生意很愉快, " + npchar.name+ "! ";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, 320000);
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, 1600);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", 1600);
				AddQuestUserData("Slavetrader", "sMoney", 320000);
				break;
			}
			if (amount >= 0 && amount < 200)
			{
				dialog.text = "我没看错你 —" + GetSexPhrase("你是个潇洒的暴徒", "你是个凶猛的少女") + "! 我需要像你这样的人。 你以最出色的方式完成了任务 —你给我带来了" + sTemp + "个奴隶。 你的奖励是" + FindRussianMoneyString(iSlaveMoney) + "。 ";
				link.l1 = "感谢。 和你做生意很愉快, " + npchar.name+ "! ";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 200 && amount < 600)
			{
				dialog.text = "至少你以全部荣誉在最困难的情况下幸存下来了。 虽然奖品比我预期的少, 但我仍然满意。 你带来了" + sTemp + "个奴隶。 你的奖励是" + FindRussianMoneyString(iSlaveMoney) + "";
				link.l1 = "感谢。 和你做生意很愉快, " + npchar.name+ "! ";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 600 && amount < 1100)
			{
				dialog.text = "我明白了... 我能理解, 但我期望的远不止这些。 你只带来了" + sTemp + "个奴隶。 至少你摧毁了我的竞争对手, 这也算有点价值。 你的奖励是" + FindRussianMoneyString(iSlaveMoney) + "。 ";
				link.l1 = "多谢。 感谢你的理解, " + npchar.name+ "! ";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 1100 && amount < 1600)
			{
				dialog.text = "听起来不错, 但是... 嗯。 看起来我看错你了。 你带来了什么? " + sTemp + "个奴隶? 剩下的呢? 别告诉我你把它们沉了。 我肯定你把它们卖给走私者了, 或者更糟 —卖给那个混蛋拉瓦锡了。 滚出去, 我不想再和你有任何生意往来了! ";
				link.l1 = "如你所愿, 再见。 ";
				link.l1.go = "node_hanter_1";
				break;
			}
			dialog.text = "听起来不错, 但是... 我们的奴隶在哪里? 我们的货物在哪里? 别告诉我你把它沉了。 你一定是把它卖给走私者了, 或者更糟, 卖给伊斯拉-特索罗的那个混蛋拉瓦锡了。 滚开, 我和你完了。 ";
			link.l1 = "如你所愿, 再见。 ";
			link.l1.go = "node_hanter_1";
		break;
		
		case "node_hanter_1":
			dialog.text = "这还没完。 没人敢愚弄我! 你会为你的尝试付出代价 —我会确保你遇到麻烦。 现在从这里出去! ";
			link.l1 = "去你的和你的奴隶贸易! 我应该在你站的地方砍了你, 但我比你好得多。 ";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 30);
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Takeslaves_6_win":
			dialog.text = "看起来我们一起合作得很好, " +pchar.name+ "。 我很高兴。 一个月后见, 也许我会给你找一份专门为你准备的工作。 我已经有几个想法了。 ";
			link.l1 = "当然, 一个月后见。 和你一起工作非常有利可图。 ";
			link.l1.go = "Takeslaves_7_win";
		break;
			
		case "Takeslaves_7_win":
			dialog.text = "这会让你发财的... 最后一个问题, " +pchar.name+ ", 你在大帆船的船舱里发现什么不寻常的东西了吗? ";
			link.l1 = "真的没什么特别的... 我错过了什么吗? ";
			link.l1.go = "Nostatue";
			if (CheckCharacterItem(pchar, "talisman8"))
			{
				link.l2 = "你是说这个旧搭扣, 某个‘蝎子’护身符? ";
				link.l2.go = "Yestatue";
			}
		break;
			
		case "Nostatue":
			dialog.text = "也许你错过了, 也许没有... 现在没关系了。 一个月后见。 再见! ";
			link.l1 = "再见, " + npchar.name+ "。 ";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Yestatue":
			dialog.text = "正是! 这是美第奇扣针... 你听说过它们吗? 这意味着它真的在那个混蛋的船舱里... 我可以看一下吗? ";
			link.l1 = "当然, 拿去吧。 ";
			link.l1.go = "Yestatue_1";
			RemoveItems(PChar, "talisman8", 1);
		break;
			
		case "Yestatue_1":
			Log_Info("你给了一个护身符");
			PlaySound("interface\important_item.wav");
			dialog.text = "嗯嗯... 确实是。 听着, " +pchar.name+ ", 把它卖给我。 我准备付十万比索。 ";
			link.l1 = "十万? 嗯... 我同意。 给你! ";
			link.l1.go = "Buystatue";
			link.l2 = "不, 我不会卖的。 这个扣针的真正价值不能用银或金来衡量。 我知道这种东西的价值。 ";
			link.l2.go = "Nobuystatue";
		break;
			
		case "Buystatue":
			dialog.text = "完美! 很高兴我们达成了交易。 拿你的钱。 期待一个月后见到你。 ";
			link.l1 = "再见, " + npchar.name+ "。 ";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 100000);
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Nobuystatue":
			dialog.text = "你看, 我急需这个扣针! 我完全同意你的看法, 它不能用金钱来衡量, 任何愚蠢的推销员甚至不会付你五千比索。 但看来你真的知道它能做什么, 因为你拒绝以这样的价格出售它。 \n如果你不想要钱, 我可以给你提供一个交换。 我有一些你可能会感兴趣的东西。 看, 拿去吧。 一件令人惊叹的轻甲! 自己看看! 我用它来交换扣针\n顺便说一下, 它不是独一无二的。 你们水手, 总是可以自己找到更多, 而我不能。 你现在同意了吗? ";
			link.l1 = "呵呵... 我想是的。 把盔甲给我, 拿这个扣针吧。 ";
			link.l1.go = "Nobuystatue_yes";
			link.l2 = "不, 这个扣针对我来说比这件盔甲更有价值。 我要自己留着。 ";
			link.l2.go = "Nobuystatue_no";
		break;
			
		case "Nobuystatue_yes":
			dialog.text = "太好了! 很高兴我们达成了交易。 这是你的盔甲了。 拿着吧。 一个月后见。 再见。 ";
			link.l1 = "再见, " + npchar.name+ "。 ";
			link.l1.go = "exit";
			TakeNItems(pchar, "cirass7", 1);
			Log_Info("你收到了一件步兵盔甲");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Nobuystatue_no":
			dialog.text = "太遗憾了... 真的很遗憾。 好吧, 拿着吧。 我不评判你。 一个月后见。 再见。 ";
			link.l1 = "再见。 ";
			link.l1.go = "exit";
			TakeNItems(pchar, "talisman8", 1);
			Log_Info("你收到了一个护身符");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "EscapeSlave":
			dialog.text = "你来得正好, " +pchar.name+ "。 如果你准备好开始, 我有一个任务给你。 ";
			link.l1 = "当然, 我准备好了。 ";
			link.l1.go = "EscapeSlave_1";
		break;
			
		case "EscapeSlave_1":
			dialog.text = "太好了! 现在, 直奔主题。 你听到最新消息了吗? ";
			link.l1 = "嗯, 你是什么意思? 每天都有很多消息。 ";
			link.l1.go = "EscapeSlave_2";
		break;
			
		case "EscapeSlave_2":
			dialog.text = "这个消息全是关于我们的生意的。 这是新世界历史上最大的奴隶逃亡! 超过一千人逃脱了, 同时他们摧毁并烧毁了荷兰的几个前哨站。 ";
			link.l1 = "有趣。 继续说。 ";
			link.l1.go = "EscapeSlave_3";
		break;
			
		case "EscapeSlave_3":
			dialog.text = "但他们不只是逃跑了, 不知怎么的, 他们设法离开了岛屿! 没有留下任何痕迹。 马蒂亚斯.贝克很愤怒。 但这不是重点... 重点是, 我请你航行到库拉索岛, 了解那里发生了什么, 找到难民并抓住他们\n当然, 把他们从荷兰司法的手中救出来, 荷兰司法对他们会很无情。 我会按每人300比索支付 —我听说他们是非常好的奴隶。 ";
			link.l1 = "明白了。 我要去库拉索岛。 等我的好消息。 ";
			link.l1.go = "EscapeSlave_yes";
			link.l2 = "你知道, 我不会接受这个任务。 我不会剥夺人们的自由。 他们冒着生命危险去争取自由。 他们应得的。 ";
			link.l2.go = "EscapeSlave_no";
		break;
			
		case "EscapeSlave_no":
			dialog.text = "真遗憾... 我没想到你会这样... 而且在最不合适的时候。 我想, 你很清楚我们的合作结束了。 再见。 ";
			link.l1 = "祝你今天愉快。 ";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "EscapeSlave_yes":
			Slavetrader_GetEscapeShore();
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(HOLLAND);
			pchar.questTemp.Slavetrader = "EscapeSlave_Villemstad";
			AddQuestRecord("Slavetrader", "22_1");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			DialogExit();
		break;
			
		case "Escape_slaves_win":
			int iSlaveMoneyH;
			string sNum;
			amount = 1100 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*300;
			sNum = GetSquadronGoods(Pchar, GOOD_SLAVES) - 1100;
			iSlaveMoneyH = makeint(sNum)*100;
			if (amount < 0)
			{
				dialog.text = "哈! 你不仅成功完成了艰巨的任务, 还带来了比我要求更多的奴隶 —" + sTemp + "个奴隶。 但是" + sNum + "个奴隶不是从库拉索岛逃出来的。 我按每人100比索支付你。 我想这对你来说行得通。 你的奖励是33万比索和" + FindRussianMoneyString(iSlaveMoneyH) + "的额外费用, 哈哈。 ";
				link.l1 = "哈! 你绝对骗不了。 我同意, 不管你说什么, " + npchar.name+ "! ";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, 330000);
				AddMoneyToCharacter(pchar, makeint(iSlaveMoneyH));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_5");
				AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoneyH));
				break;
			}
			if (amount < 101 && amount >= 0)
			{
				dialog.text = "你以最出色的方式完成了那项艰巨的任务, 给我带来了" + sTemp + "个奴隶。 你的奖励是" + FindRussianMoneyString(iSlaveMoney) + "。 ";
				link.l1 = "多谢。 和你做生意很愉快, " + npchar.name+ "! ";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 100 && amount < 600)
			{
				dialog.text = "你成功完成了那项艰巨的任务。 奖品没有我预期的那么丰厚, 但我仍然满意。 所以你带来了" + sTemp + "个奴隶。 你的奖励是" + FindRussianMoneyString(iSlaveMoney) + "。 ";
				link.l1 = "谢谢。 和你做生意很愉快, " + npchar.name+ "! ";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 600 && amount < 1100)
			{
				dialog.text = "你找到他们了? 嗯... 你给我带来了什么? " + sTemp + "个奴隶? 剩下的货物呢? 甚至不要试图告诉我你把它沉了。 你一定是把它卖给走私者了, 或者更糟 —卖给伊斯拉-特索罗的那个混蛋拉瓦锡了。 离开这里, 我不想再和你合作了。 ";
				link.l1 = "再见。 ";
				link.l1.go = "node_hanter_1";
				break;
			}
			dialog.text = "找到他们了? 那奴隶呢? 我们的货物在哪里? 甚至不要试图告诉我你把它沉了。 你一定是把它卖给走私者了, 或者更糟 —卖给伊斯拉-特索罗的那个混蛋拉瓦锡了。 离开这里, 我不想再和你合作了。 ";
			link.l1 = "再见。 ";
			link.l1.go = "node_hanter_1";
		break;
		
		case "Escape_slaves_win_1":
			dialog.text = "我真的很欣赏你, " +pchar.name+ "。 真的。 一个月后再来这里, 我会准备一个对我们双方都有利可图的新业务。 ";
			link.l1 = "我也对我们的合作感到满意, " + npchar.name+ "。 一个月后见。 ";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_2");
			pchar.questTemp.Slavetrader = "wait_2";
		break;
			
		case "Slaveshore":
			dialog.text = "你来得正好, " +pchar.name+ "。 我正在寻找一个勇敢且无所顾忌的水手, 哈哈。 你准备好处理我的工作了吗? ";
			link.l1 = "我洗耳恭听。 ";
			link.l1.go = "Slaveshore_1";
		break;
			
		case "Slaveshore_1":
			pchar.questTemp.Slavetrader.Island = Islands[GetCharacterCurrentIsland(pchar)].id;
			pchar.questTemp.Slavetrader.Island.Shore = GetIslandRandomShoreId(pchar.questTemp.Slavetrader.Island);
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.questTemp.Slavetrader.Nation = NPChar.nation;
			dialog.text = "这次很简单。 今天, 一艘名为'" + pchar.questTemp.Slavetrader.ShipName + " 的轻帆船在" + NationNameGenitive(sti(npchar.nation)) + "的旗帜下, 在" + XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore + "Gen") + "湾抛锚了。 它在当地走私者的帮助下装载了一大批‘乌木’。 不少于两千人\n船员中没有士兵, 船长是个商人。 总的来说, 一点威胁都没有。 登上这艘船, 把货物带给我。 像往常一样, 每人200比索。 ";
			link.l1 = "嗯... 这和上一份工作不一样。 你建议我攻击你自己国家的船! ";
			link.l1.go = "Slaveshore_2";
		break;
			
		case "Slaveshore_2":
			dialog.text = "我不明白, " +pchar.name+ "。 船的旗帜重要吗? 你真的在乎吗? ";
			link.l1 = "我在乎吗? 不, 我不在乎, 黄金没有国籍。 只是有点出乎意料... ";
			link.l1.go = "Slaveshore_3_yes";
			link.l2 = "我在乎。 我不想让" + NationNameAblative(sti(npchar.nation)) + "成为我的敌人之一。 ";
			link.l2.go = "Slaveshore_3_no";
		break;
			
		case "Slaveshore_3_no":
			dialog.text = "你是认真的吗? 你一定是在开玩笑, 现在不能相信任何人... 既然如此, 走开。 忘记你在这里看到或听到的一切! ";
			link.l1 = "再见, " + npchar.name+ "。 ";
			link.l1.go = "node_hanter_1";
		break;
			
		case "Slaveshore_3_yes":
			dialog.text = "你为什么感到惊讶? 因为我不在乎硬币的国籍? 我向你保证, 我确实不在乎。 说实话, 爱国主义对一个专业的银行家来说是不好的, 除非他想有一天破产\n但哲学讲得够多了。 我们直奔主题吧 —这艘船会在这里停留到午夜, 所以你没有多少时间了。 你准备好继续了吗? ";
			link.l1 = "是的, " + npchar.name+ ", 我这就去。 ";
			link.l1.go = "Slaveshore_4";
		break;
			
		case "Slaveshore_4":
			dialog.text = "太好了。 我毫不怀疑你会成功完成我们的任务。 祝你好运。 " +pchar.name+ "。 ";
			link.l1 = "谢谢! 再见。 ";
			link.l1.go = "exit";
            AddQuestRecord("Slavetrader", "10");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShip", pchar.questTemp.Slavetrader.ShipName);
			pchar.quest.Slavetrader_ShoreAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_ShoreAttack.win_condition.l1.location = pchar.questTemp.Slavetrader.Island;//发送到该位置
            pchar.quest.Slavetrader_ShoreAttack.function = "Slavetrader_CreateShoreShips";//创建船只
			SetFunctionTimerCondition("Slavetrader_ShoreShipsOver", 0, 0, 1, false);	//定时器
			pchar.questTemp.Slavetrader = "wait1";	//占位符
		break;
			
		case "Pinas_lose":
		dialog.text = "那么, " + GetFullName(pchar) + ", 你的任务怎么样了? 你那愁眉苦脸的样子告诉我你失败了。 ";
			link.l1 = "你说得对... 我... 嗯... 我太晚了。 我在酒馆里, 当我出海时, 海上没有人了。 ";
			link.l1.go = "Takeslaves_5_lose";
		break;
			
		case "Slaveshore_5":
			dialog.text = "" +pchar.name+ ", 请冷静下来。 这不是我的错! 该死, 我收到报告太晚了... 有背叛! 我信任的一个人出卖了我! ";
			link.l1 = "好吧, 我看你说的是实话。 你很幸运, 轻帆船的船长告诉我我们的‘生意’被发现了。 如果他没有泄露, 我可能已经杀了你。 但是你, 他妈的一袋钱, 一直告诉我你‘拥有这个城镇’! ";
			link.l1.go = "Slaveshore_6";
		break;
			
		case "Slaveshore_6":
			dialog.text = "伏击不是当地当局组织的, 否则我会知道... " +pchar.name+ ", 现在不是争吵的时候。 我们俩都有危险, 我的一个前承包商陷害了我们\n我设法查明, 所有收集到的证据 —一包裹文件 —正在被运往我们的总督那里。 如果他拿到了, 我们就完了! 顺便说一下, 你将遭受最大的损失。 ";
			link.l1 = "现在我明白那个混蛋船长是什么意思了! ";
			link.l1.go = "Slaveshore_7";
		break;
			
		case "Slaveshore_7": //选择船只将前往的岛屿
			switch (sti(NPChar.nation))
            {
                case HOLLAND :
					pchar.questTemp.Slavetraderbrig.Island = "Curacao";
                break;
                case FRANCE :
					pchar.questTemp.Slavetraderbrig.Island = "Nevis";
                break;
                case SPAIN :
					pchar.questTemp.Slavetraderbrig.Island = "Cuba2";  
                break;
                case ENGLAND :
					pchar.questTemp.Slavetraderbrig.Island = "Jamaica";     
                break;
			}
			pchar.questTemp.Slavetraderbrig.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));// brigantine的名字
			pchar.questTemp.Slavetrader.Nation = NPChar.nation;
			dialog.text = "仔细听着。 我们还有机会。 包裹被送上了名为'" + pchar.questTemp.Slavetraderbrig.ShipName + " 的双桅帆船。 这是我唯一确定的事情。 文件正在被送到总督在" + XI_ConvertString(pchar.questTemp.Slavetraderbrig.Island) + "的官邸。 你必须拦截它, 登上它, 找到那些诽谤性的证据。 ";
			link.l1 = "在这里我没有太多选择。 为我祈祷, 为你自己祈祷, 希望我能抓住它。 等我回来我们再谈所有这些。 别以为我会就此罢休。 ";
			link.l1.go = "Slaveshore_8";
			AddQuestRecord("Slavetrader", "14");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetraderbrig.ShipName);
			AddQuestUserData("Slavetrader", "sIsland", XI_ConvertString(GetIslandByArealName(pchar.questTemp.Slavetraderbrig.Island)));
			pchar.quest.Slavetrader_BrigAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_BrigAttack.win_condition.l1.location = pchar.questTemp.Slavetraderbrig.Island;//发送到该位置
            pchar.quest.Slavetrader_BrigAttack.function = "Slavetrader_CreateBrig";//创建双桅帆船
			SetFunctionTimerCondition("Slavetrader_BrigOver", 0, 0, 15, false);	//定时器
			pchar.questTemp.Slavetrader = "wait1";	//这是等待节点, 空的
		break;
		
		case "Slaveshore_8":
			dialog.text = "拿到这个包裹是你的首要任务! 在你把它交给我之前, 我无法确定自己的安全... 该死的... " +pchar.name+ ", 看来我们这里有麻烦了... ";
			link.l1 = "是什么? ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Slavetrader_enterSoldiers");
			break;
			
		case "Brig_lose":
			dialog.text = "该死... 我本来指望你, " +pchar.name+ "。 那好吧。 但我们再也不会有任何生意往来了。 如果我不能贿赂调查员, 我就得逃跑。 我不建议你留在这里 —士兵随时可能来这里。 再见。 ";
			link.l1 = "再见, " + npchar.name+ "。 ";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Letter_lose":
			dialog.text = "他们在那里。 好吧, 我们不能再一起做生意了, 现在不再安全了。 再见。 ";
			link.l1 = "再见, " + npchar.name+ "。 ";
			link.l1.go = "exit";
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Brig_win":
			dialog.text = "太棒了! 我从不怀疑你, " +pchar.name+ "。 请把那些文件给我, 我太紧张了。 ";
			link.l1 = "拿去吧。 ";
			link.l1.go = "Brig_win_1";
		break;
			
		case "Brig_win_1":
			RemoveItems(PChar, "letter_1", 1);
			dialog.text = "很好... 现在我安全了。 总督什么也不会知道, 我已经解决了和当地当局的所有问题, 但我告诉你, 这代价很高。 ";
			link.l1 = "听起来不错, 但你不认为你应该补偿我因为你轻率的行为而带来的麻烦吗? ";
			link.l1.go = "Brig_win_2";
		break;
			
		case "Brig_win_2":
			dialog.text = "当然, " +pchar.name+ "。 甚至更多, 我欠你很多。 我真的希望继续我们的生意。 但我请你理解我 —我花了一大笔钱 —总督和指挥官的忠诚花费了很多。 而且我还得处理我银行里整个巡逻队被谋杀的事情... ";
			link.l1 = "你的意思是你不会补偿我的费用? ! ";
			link.l1.go = "Brig_win_3";
		break;
			
		case "Brig_win_3":
			dialog.text = "别那么苛刻, " +pchar.name+ "。 我现在真的没钱了, 所以我给你提供另一种付款方式。 ";
			link.l1 = "那我听你说。 ";
			link.l1.go = "Brig_win_4";
		break;
			
		case "Brig_win_4":
			dialog.text = "一年前, 我和我的同伴在大陆南岸附近遇到了风暴。 我们的船被抛到了蛇口海岸的岩石上, 尽管它们很快就沉没了, 我们还是设法把货物拖到了岸上。 装满宝石和珠宝的箱子。 这个海湾看起来很舒适, 所以我们毫不费力地隐藏了宝藏\n但第二天早上, 风暴一结束, 我们就遭到了印第安人的袭击。 大多数幸存者就是这样死去的, 包括我的同伴。 我和几个水手设法乘长艇逃脱了\n我们安全到达了库马纳, 但我不敢回去取宝藏。 我相信当地的野蛮人仍在保护他们的海岸以及我的箱子。 但你可以对付那一群红皮肤的人\n你在那里找到的珠宝足够支付你所有的费用, 包括前往南部大陆的探险费用。 ";
			link.l1 = "嗯... 好吧。 那我就去库马纳";
			link.l1.go = "Brig_win_5";
		break;
			
		case "Brig_win_5":
			dialog.text = "你可以放心, " +pchar.name+ ", 我所说的一切都是真的。 我期待一个月后见到你。 我已经想到了另一笔交易, 以及我应该如何帮助我摇摇欲坠的生意。 再见。 ";
			link.l1 = "再见, " + npchar.name+ "。 ";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_3");
			pchar.questTemp.Slavetrader = "wait_3";
			Pchar.quest.Slavetrader_Bonanza.win_condition.l1 = "location";
            Pchar.quest.Slavetrader_Bonanza.win_condition.l1.location = "Shore18";
            Pchar.quest.Slavetrader_Bonanza.function = "Slavetrader_Bonanza";
		break;
			
		case "SlaveGalleon":
			dialog.text = "你来了, " +pchar.name+ "。 很好, 你总是来得正好。 在给你下一个任务之前, 我想给你更多关于加勒比奴隶市场的信息。 你知道‘分配制度’这个词是什么意思吗? ";
			link.l1 = "嗯, 不知道, " + npchar.name+ ", 我不知道。 但我想这是关于从某人那里拿走东西的。 对吗? ";
			link.l1.go = "SlaveGalleon_1";
		break;
			
		case "SlaveGalleon_end":
			dialog.text = "你让我惊讶。 你对我有什么期望? 走开! ";
			link.l1 = "非法生意对我的道德来说太艰难了。 尤其是奴隶贸易。 ";
			link.l1.go = "node_hanter_1";
		break;
			
		case "SlaveGalleon_1":
			dialog.text = "你几乎说对了, " +pchar.name+ "。 夺走某人的自由。 分配制度是一种狡猾而合法的奴役当地印第安人的方式。 可以这么说。 西班牙当局用它来对付大陆的原住民。 你有兴趣了解更多吗? ";
			link.l1 = "为什么不呢? ";
			link.l1.go = "SlaveGalleon_2";
		break;
			
		case "SlaveGalleon_2":
			dialog.text = "西班牙王室的代表访问印第安人定居点。 他们使用冷酷的欺骗和直接威胁, 迫使印第安人以惊人的价格购买各种垃圾, 如腐烂的肉和旧剃刀。 赊账\n一段时间后, 比如说一年, 代表们回来要求付款。 如果印第安人无法偿还, 通常情况就是这样, 西班牙人就会带走一部分有工作能力的人, 据说要‘教他们如何耕种土地’\n如你所知, 他们再也不会回到自己的定居点。 我们信任的红皮肤就是这样进入甘蔗种植园和红木工厂的。 ";
			link.l1 = "该死... 真的... 印第安人对此做了什么? 当西班牙人奴役他们时, 他们反抗了吗? 还是他们只是不明白发生了什么? ";
			link.l1.go = "SlaveGalleon_3";
		break;
			
		case "SlaveGalleon_3":
			dialog.text = "我想他们总是预见到这一点, 但只有少数人敢于公开反对, 尤其是当西班牙人出示带有酋长指纹的文件时。 当然, 这种策略通常适用于阿拉瓦克或米斯基托等和平部落。 这种诡计对好战的伊察或阿考伊不起作用\n好吧, 我们来谈谈你的任务。 ";
			link.l1 = "我已经闻到了很多硬币的味道! 我在听你说, " + npchar.name+ "。 ";
			link.l1.go = "SlaveGalleon_4";
		break;
			
		case "SlaveGalleon_4":
			Slavetrader_GetHispanShore();
			sTemp = pchar.questTemp.SlavetraderAreal.add; 
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(SPAIN);
			dialog.text = "很快从加拉加斯将驶出一艘重型大帆船。 它叫'" + pchar.questTemp.Slavetrader.ShipName + " 。 它载有大量奴隶 —大约3000人 —奥里诺科河的印第安人, 根据分配制度政策捕获的。 这艘大帆船正驶往圣地亚哥, 古巴的甘蔗种植园需要大量工人。 你必须捕获这艘大帆船和她的货物。 如果我是你, 我会至少带两艘船, 他们说这艘大帆船是同类中最好的。 工资率保持不变 —每人200比索。 ";
			link.l1 = "嘿! 听起来不错。 我同意。 ";
			link.l1.go = "SlaveGalleon_5";
			link.l2 = "你知道我不喜欢你的分配制度。 这太愤世嫉俗了。 我不打算这么做。 ";
			link.l2.go = "SlaveGalleon_end";
		break;
			
		case "SlaveGalleon_5":
			sTemp = pchar.questTemp.SlavetraderAreal.add; 
			dialog.text = "那祝你好运。 要知道这艘大帆船的船长是 一 位非常熟练和有经验的战航海员。 这不会是一场轻松的战斗, 所以做好准备。 不要浪费时间, 他到达" + sTemp + "圣地亚哥需要十五到二十天。 尽量不要错过, 尽管这艘大帆船真的很难错过\n是的! 差点忘了! 船上有很多印第安小饰品, 红皮肤经常用他们的宗教物品和手工艺品来偿还债务。 把你找到的任何特别的东西带给我, 你带来的每一件有价值的物品, 我都会给你一大笔钱。 ";
			link.l1 = "我明白了。 ";
			link.l1.go = "exit";
			SlavetraderGalleonInWorld();
			if(bImCasual) NewGameTip("探索模式: 计时器未禁用。 遵守最后期限! ");
			SetFunctionTimerCondition("Slavetrader_SlaveGalleonOver", 0, 0, 20, false);
			pchar.questTemp.Slavetrader = "wait1";
			AddQuestRecord("Slavetrader", "18");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
			AddQuestUserData("Slavetrader", "sAreal", sTemp);
		break;
			
		case "Lostgalleon":
			dialog.text = "那么, " +pchar.name+ ", 这是我最后的希望了... 这就是为什么我把这份工作给了你。 除了你, 没有人能做到... 我看你也做不到。 那么我们说再见吧。 在最后一次失败和所有那些流言蜚语之后, 我所有的客户都走了。 我几乎破产了, 也许我得离开这个城镇。 我不怪你 —这份工作太难了。 唉... 再见, " +pchar.name+ "。 ";
			link.l1 = "我很抱歉, " + npchar.name+ ", 事情发展得太过分了。 我真的很抱歉。 也许一切都会解决的。 再见。 ";
			link.l1.go = "exit";
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Wingalleon":
			pchar.questTemp.Slavetrader.Nation = npchar.nation;
			amount = 3000 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			if(amount < 1) 
			{
				dialog.text = "呼, 我现在感觉好多了... 我信任你是对的... 这种讽刺是从哪里来的? 怎么了? ";
				link.l1 = "亲爱的先生, 那不是一艘大帆船... 或者是一艘非常大的大帆船... 该死! 那是一艘战列舰! 你甚至没有警告我! 但我设法登上了她。 我有" + sTemp + "个奴隶, 我准备把它们转移给你。 根据我们的协议, 你欠我 —" + FindRussianMoneyString(iSlaveMoney) + "。 如果你能为你的错误信息提供一些补偿, 那就太好了。 ";
				link.l1.go = "Wingalleon_1";
			}
			else
			{
			dialog.text = "你找到大帆船了吗? 奴隶呢? 应该有三千个, 不少于! 该死的, 每个人都是叛徒! 我没想到你会这样... 你是我最后的希望\n很好... 我发誓, 我会花光我剩下的每一枚硬币来摧毁你, 杀死你! 整个" + NationNameGenitive(sti(npchar.nation)) + "舰队都会追捕你! 离开这里! ";
				link.l1 = "好吧... ";
				link.l1.go = "Wingalleon_goaway";
			}
		break;
			
		case "Wingalleon_goaway":
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 70);
			pchar.questTemp.Slavetrader = "End_quest";
			DialogExit();
		break;
			
		case "Wingalleon_1":
			dialog.text = "你不说我也知道! 我发誓, 我不知道。 本应是一艘重型大帆船起航, 而不是一艘该死的战列舰! 看来他们在最后一刻改变了计划... 但你还是成功了! \n我完全同意你关于钱和补偿你费用的说法, 问题是我现在没有这么多钱。 你知道我最近的麻烦... 但别生气, " +pchar.name+ ", 看在上帝的份上。 你把货物给我, 我会卖掉它, 我的客户已经在等了\n我五天后就会有全部款项, 所以你会得到你应得的。 你可以信任我。 给, 把我现在所有的现金都拿去吧。 ";
			link.l1 = "嗯... 我本希望现在就能收到钱。 你知道我经历了怎样的战斗吗! 啊, 不管了... 我会同情你的。 但记住, 如果你想骗我, 我就算在欧洲也会找到你! ";
			link.l1.go = "Wingalleon_yes";
			link.l2 = "你知道, " + npchar.name+ ", 去你的! 这不是交易。 你甚至无法想象我不得不经历怎样的战斗。 我把所有的奴隶都留给自己, 没有你的中介就把它们卖掉。 ";
			link.l2.go = "Wingalleon_no";
		break;
			
		case "Wingalleon_no":
			dialog.text = "所以, 现在你说话了! 看来毫无戒心的" + npchar.name+ "只是一头可以挤奶的牛, 一个简单的延迟就足以让你骗我, 自己开始行动。 看来你已经忘记了是我给了你这份工作, 给了你关于战利品的提示\n很好... 我发誓, 我会花光我剩下的每一枚硬币来摧毁你, 杀死你! 整个" + NationNameGenitive(sti(npchar.nation)) + "舰队都会追捕你! 从我的视线中消失! ";
			link.l1 = "别敢吓唬我, 一个空钱箱。 我会击沉你所有的舰队, 用它来喂螃蟹。 ";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 70);
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Wingalleon_yes":
			dialog.text = "感谢你的理解, " +pchar.name+ "。 我保证一切都会好起来的, 不需要你的威胁\n把这个作为预付款。 十五个箱子。 其中五个将作为精神损失的补偿。 五天后来看我, 拿到剩下的钱。 \n别忘了把你在船上找到的所有印第安物品带来... 当然, 如果你真的找到了。 反正我也没什么钱付给你。 ";
			link.l1 = "五天后, " + npchar.name+ "。 五天后... ";
			link.l1.go = "Wingalleon_yes_1";
		break;
			
		case "Wingalleon_yes_1":
			TakeNItems(pchar, "chest", 15);
			Log_Info("你收到了信用箱");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_4");
			pchar.questTemp.Slavetrader = "wait_4";
			AddQuestRecord("Slavetrader", "20");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			pchar.questTemp.Slavetrader.iSlaveMoney = makeint(sTemp)*200-120000;
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
			DialogExit();
		break;
	
		case "FindRat":
			dialog.text = "正如我承诺的, " +pchar.name+ ", 我准备付钱给你。 奴隶已经卖掉了, 客户很高兴, 我们也很高兴。 扣除预付款后, 你的奖励是" + FindRussianMoneyString(sti(pchar.questTemp.Slavetrader.iSlaveMoney)) + "。 请拿你的钱。 ";
			link.l1 = "太好了, " + npchar.name+ "。 和一个能信守诺言的人打交道真好... ";
			link.l1.go = "FindRat_1";
		break;
			
		case "FindRat_1":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			dialog.text = "你可以永远相信我的话, " +pchar.name+ "。 我从未给过你任何怀疑我的理由。 合作伙伴必须彼此诚实, 这是生意的关键\n现在让我们谈谈印第安文物。 给我看看你有什么, 别让像我这样的收藏家等待。 ";
			link.l1 = "嗯... 看看吧。 ";
			link.l1.go = "FindRat_2";
		break;
			
		case "FindRat_2":
			if (CheckCharacterItem(pchar, "talisman16"))
			{
				dialog.text = "是的! 太棒了! 一把金色的仪式刀! 这是罕见的东西。 我一直想在我的收藏中拥有这样的东西。 我给你3万比索, 或者用一个‘埃赫卡特’护身符来交换。 反正我有两个。 ";
				link.l1 = "我要拿钱。 ";
				link.l1.go = "BG_money";
				link.l2 = "我想用一个‘埃赫卡特’护身符来交换。 ";
				link.l2.go = "BG_change";
				link.l3 = "我最好自己留着这把刀。 ";
				link.l3.go = "BG_no";
			}
			else
			{
				dialog.text = "让我看看..不幸的是, 你没有什么我感兴趣的东西。 ";
				link.l1 = "随你怎么说。 ";
				link.l1.go = "BG_PF";
			}
		break;
			
		case "BG_money":
			dialog.text = "太好了。 拿你的3万比索, 这把印第安刀现在是我的了。 ";
			link.l1 = "好的。 这就是你感兴趣的全部吗... ";
			link.l1.go = "BG_PF";
			AddMoneyToCharacter(pchar, 30000);
			Log_Info("你给了一把金色的刀");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "talisman16", 1);
		break;
			
		case "BG_change":
			dialog.text = "太好了! 这是你的护身符, 这把印第安刀现在是我的了。 ";
			link.l1 = "好的。 这就是你感兴趣的全部吗... ";
			link.l1.go = "BG_PF";
			Log_Info("你给了一把金色的刀");
			Log_Info("你收到了一个‘埃赫卡特’护身符");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "talisman16", 1);
			TakeNItems(pchar, "obereg_9", 1);
		break;
			
		case "BG_no":
			dialog.text = "不管怎样。 但这仍然是一个遗憾... ";
			link.l1 = "好的。 这就是你感兴趣的全部吗... ";
			link.l1.go = "BG_PF";
		break;
			
		case "BG_PF":
			dialog.text = "等等! 让我再看一遍... ";
			link.l1 = "当然。 过来看看, 选择你想要的。 ";
			link.l1.go = "PF_check";
		break;
			
		case "PF_check":
			if (CheckCharacterItem(pchar, "mineral31"))
			{
				dialog.text = "这个! 我一开始甚至没有注意到它。 我对这个带铜环的骨头感兴趣。 我告诉你, 这是一件有趣的东西... 我可以付你2万比索, 或者用一个‘西玛鲁塔’护身符来交换。 ";
				link.l1 = "我要拿钱。 ";
				link.l1.go = "PF_money";
				link.l2 = "我想用一个‘西玛鲁塔’护身符来交换。 ";
				link.l2.go = "PF_change";
				link.l3 = "我要自己留着这件文物。 ";
			link.l3.go = "PF_no";
			}
			else
			{
				dialog.text = "不... 你这里没有其他感兴趣的东西了。 ";
				link.l1 = "不管怎样! ";
				link.l1.go = "FindRat_3";
			}
		break;
			
		case "PF_money":
			dialog.text = "太好了! 这是你的2万比索, 这根骨头现在是我的了。 ";
			link.l1 = "不错。 我对我们的交易感觉很好。 ";
			link.l1.go = "FindRat_3";
			AddMoneyToCharacter(pchar, 20000);
			Log_Info("你给了一根魔法骨头");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "mineral31", 1);
		break;
			
		case "PF_change":
			dialog.text = "太好了! 这是你的护身符, 这根骨头现在是我的了。 ";
			link.l1 = "不错。 我对我们的交易感觉很好。 ";
			link.l1.go = "FindRat_3";
			Log_Info("你给了一根魔法骨头");
			Log_Info("我收到了一个‘西玛鲁塔’护身符");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "mineral31", 1);
			TakeNItems(pchar, "amulet_11", 1);
		break;
			
		case "PF_no":
			dialog.text = "不管怎样。 但这仍然是一个遗憾... ";
			link.l1 = "我自己需要那根骨头, 很抱歉。 ";
			link.l1.go = "FindRat_3";
		break;
			
		case "FindRat_3":
			dialog.text = "嗯... 通过登上大帆船, 哦, 对不起, 战列舰, 你救了我。 我真的很欣赏我们的合作, " +pchar.name+ "。 你是我最好的代理人。 ";
			link.l1 = "我受宠若惊。 你太高估我的成就了... ";
			link.l1.go = "FindRat_4";
		break;
			
		case "FindRat_4":
			dialog.text = "我是完全认真的。 由于你非凡的技能和我信任你, 我要请你完成另一项任务。 ";
			link.l1 = "嘿! 令人惊讶! 我在听。 另一艘载有奴隶的大帆船在哪里? ";
			link.l1.go = "FindRat_5";
		break;
			
		case "FindRat_5":
			dialog.text = "这次不是关于奴隶的事。 惊讶吗? 我会为这个任务给你丰厚的报酬... 非常丰厚。 ";
			link.l1 = "直奔主题吧。 ";
			link.l1.go = "FindRat_6";
		break;
			
		case "FindRat_6":
			dialog.text = "这件事与你也参与的最近事件有关... 所以, 如你所知, 我做的是相当非法的生意 —奴隶贸易。 你可能也知道, 我雇佣像你这样的私掠者来完成各种任务\n我的一个人不久前出于未知原因背叛了我。 他收集了证据, 并向当局做了报告。 你有幸亲眼看到了后果。 一艘载有士兵的船来到了这里... 你知道剩下的\n我花了相当大的努力才解决了这个局面。 如你可能理解的, 我不能让这种背叛得不到回应。 此外, 我不能在知道那只老鼠还活着的情况下和平地生活和工作。 我派了赏金猎人, 但至今没有结果\n我请你亲自处理这件事。 更重要的是, 他的行为也影响了你。 ";
			link.l1 = "嗯... 这个混蛋必须被吊死在桅杆上! 告诉我更多关于他的事情, 当然还有我做这项工作的报酬。 ";
			link.l1.go = "FindRat_7";
		break;
			
		case "FindRat_7":
			dialog.text = "别担心那个。 我会为他的消灭支付一大笔钱, 我说的不仅仅是钱。 我不会吝惜我收藏中的最好物品。 我们来谈谈这个人。 他的名字是弗朗索瓦.贡捷\n他知道我在追捕他, 所以他卖掉了他的护卫舰以隐藏他的踪迹。 我的同事告诉我, 他在巴拿马被看到过。 我相信你应该从那里开始你的搜索。 ";
			link.l1 = "好吧, 那我就上路了。 ";
			link.l1.go = "FindRat_8";
		break;
			
		case "FindRat_8":
			dialog.text = "那祝你好运。 要知道这个贡捷是一位非常有经验的水手, 他的船员都是肆无忌惮的亡命之徒 。 他已经一无所有, 所以会以非常拼命的方式战斗。 ";
			link.l1 = "我不怕像他这样的人, 但我会考虑你说的话。 再见, 放心吧, 即使他在地狱我也会抓到他。 ";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(SPAIN);
			AddQuestRecord("Slavetrader", "21");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.questTemp.Slavetrader = "FindRatPanama";
		break;
			
		case "Wincorvette":
			dialog.text = "太棒了! 现在他可以给水母写报告了。 没人敢惹我。 感谢你, " +pchar.name+ ", 你是不可或缺的人。 ";
			link.l1 = "谢谢你, " + npchar.name+ ", 谢谢你对我行动的高度评价。 我的报酬呢? ";
			link.l1.go = "Wincorvette_1";
		break;
			
		case "Wincorvette_1":
			dialog.text = "当然。 我会为这么困难的工作支付合适的价格。 首先, 我送给你这个出色的望远镜。 ";
			link.l1 = "哇, 这么好的礼物! ";
			link.l1.go = "Wincorvette_2";
		break;
			
		case "Wincorvette_2":
			dialog.text = "此外, 这里有10万比索作为你的主要报酬, 还有5万比索作为你自己费用的补偿。 ";
			link.l1 = "谢谢, " + npchar.name+ "。 我再说一遍, 和你打交道真是一种享受。 ";
			link.l1.go = "Wincorvette_3";
			Log_Info("你收到了一个出色的望远镜");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "spyglass4", 1);
		break;
			
		case "Wincorvette_3":
			dialog.text = "我会像往常一样等你一个月。 这是一笔非常大的交易, 你需要一支装备精良的中队。 我请你理解这一点并做好准备。 如果我的计划成功, 我们会发财的。 ";
			link.l1 = "好的, " + npchar.name+ "。 我准备好后会回来。 ";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 150000);
			AddQuestRecord("Slavetrader", "21_13");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_5");
			pchar.questTemp.Slavetrader = "wait_5";
		break;
			
		case "Lostcorvette":
			dialog.text = "可惜, 真遗憾... 好吧, 别难过, 你不是第一个被那个混蛋愚弄的人。 反正我总有一天会抓住他的\n至于你, 一个月后来看我。 这将是一笔大买卖, 所以召集一支装备精良。 武装齐全的中队。 请认真对待, 尽你最大的努力做好准备。 如果我的计划成功, 我们会发财的。 ";
			link.l1 = "好的, " + npchar.name+ "。 我准备好后会回来。 ";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_14");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_5");
			pchar.questTemp.Slavetrader = "wait_5";
		break;
		
		case "Havana_fort":
			dialog.text = "你来得正好, " +pchar.name+ "! 我差点开始担心了, 我正要派人去找你\n我们开始吧! 你现在的任务真的很重大且危险, 但报酬是足够的。 任务完成后你将收到超过一百万比索。 ";
			link.l1 = "这才像话! 我在听, " + npchar.name+ "。 ";
			link.l1.go = "Havana_fort_1";
		break;
		
		case "Havana_fort_1":
			dialog.text = "被奴役的印第安人正被 一 小批 一 小批地从整个大陆运往哈瓦那, 还有几艘从非洲来的大帆船也在卸货。 到目前为止, 哈瓦那堡垒的高墙后面已经有将近五千名奴隶了。 ";
			link.l1 = "我有种感觉, 这笔交易是关于突袭哈瓦那的。 ";
			link.l1.go = "Havana_fort_2";
		break;
		
		case "Havana_fort_2":
			dialog.text = "你的感觉是对的, " +pchar.name+ "。 这正是我想请你做的。 你, 只有你。 我怀疑我的其他代理人中有没有人能做到这一点\n我相信你会加入? ";
			link.l1 = "说实话, " + npchar.name+ ", 我现在有点目瞪口呆。 我不知道你的活动如此... 大规模。 当然, 我加入。 " + RandSwear() + "";
			link.l1.go = "Havana_fort_3";
			link.l2 = "你知道吗, " + npchar.name+ ", 这太过分了。 我受够了你的这些惊喜。 下次你的贪婪会让我向西班牙宣战, 而我将不得不独自与他们战斗。 如果你真的需要那些奴隶, 那就自己突袭哈瓦那吧。 ";
			link.l2.go = "Havana_fort_not";
		break;
		
		case "Havana_fort_not":
			dialog.text = "没想到你会这样... 该死, 我该怎么跟我的客户说? 好吧。 这是你的选择, 我得找个新伙伴了。 再见, " +pchar.name+ "。 我以后不会再用你的服务了。 记住, 你放弃了一个能让你的子孙七代都富有的交易。 ";
			link.l1 = "你不能得到世界上所有的钱, 你贪多嚼不烂。 再见, " + npchar.name+ "。 ";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
		
		case "Havana_fort_3":
			dialog.text = "我就知道你会同意。 现在, 听细节。 哈瓦那的堡垒一直是个硬目标, 但现在更难了\n有两艘战列舰在守卫古巴的海岸, 你在突袭堡垒之前必须先对付它们... ";
			link.l1 = "我明白了。 这不会是我第一次和战列舰战斗, 哈哈。 我有多少时间? ";
			link.l1.go = "Havana_fort_4";
		break;
		
		case "Havana_fort_4":
			dialog.text = "不多。 不超过三周, 之后奴隶将被转移到古巴的西班牙前哨。 你得赶紧了。 ";
			link.l1 = "那我们别浪费时间了。 我这就去! ";
			link.l1.go = "Havana_fort_5";
		break;
		
		case "Havana_fort_5":
			dialog.text = "等一下! " +pchar.name+ ", 你我之间从未有过任何误解和分歧。 尽管如此, 我想让你知道这里发生了什么。 我指望你, 客户也指望我\n我们在这次行动中投入了大量的精力和金钱。 每一个奴隶, 整整五千个, 都必须交给我\n否则, 我们将对你采取非常激进的措施。 无意冒犯, 这只是一个警告。 ";
			link.l1 = "别担心, " + npchar.name+ ", 我知道什么是生意, 这就是为什么你也应该记住, 一旦我把他们送来, 你也要记得付钱给我。 再见。 ";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "24");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.quest.Slavetrader_HavanaAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_HavanaAttack.win_condition.l1.location = "Cuba2";//发送到该位置
            pchar.quest.Slavetrader_HavanaAttack.function = "Slavetrader_CreateLineShips";//创建战列舰
			SetFunctionTimerCondition("Slavetrader_HavanaOver", 0, 0, 20, false);	//定时器
			characters[GetCharacterIndex("Havana_Mayor")].dialog.captureNode = "Slavetrader_HavanaAttack"; //市长的投降节点
			pchar.questTemp.Slavetrader = "wait1";
		break;
		
		case "Win_Havana_Fort":
			pchar.quest.Slavetrader_FiveTSlavesOver.over = "yes";
			amount = 5000 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			if (amount < 1)
			{
				dialog.text = "那么... 你的胜利奖品呢? ";
				link.l1 = "我有" + sTemp + "个奴隶。 ";
				link.l1.go = "Havana_Fort_yes";
				break;
			}
			if (amount < 4500 && amount >= 1)
			{
				dialog.text = "好吧, 好吧。 你忘了我说的话吗? 你必须给我带来不少于五千个奴隶, 而你只有" + sTemp + "个。 为什么? ";
				link.l1 = "嗯... 他们中的一部分在从哈瓦那来的路上没有幸存下来... 食物和药品快用完了。 ";
				link.l1.go = "Havana_Fort_no";
				break;
			}
			dialog.text = "嗯嗯... 你想骗我吗? 你忘了我说的话吗? 我的奴隶在哪里, 我问你! 他们在哪里? ! ";
			link.l1 = "嗯... 你看... ";
			link.l1.go = "Havana_Fort_no";
		break;
		
		case "Havana_Fort_no":
			dialog.text = "好吧。 我不需要你的解释。 我们有过协议, 我会给你一周时间弄到不少于五千个奴隶。 否则你会有很多麻烦。 ";
			link.l1 = "好的, 好的, 放松点, 我会给你弄到的。 ";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "29");
			if(bImCasual)
			{
				NewGameTip("探索模式: 任务持续时间加倍");
				SetFunctionTimerCondition("Slavetrader_HavanaSeekOver", 0, 0, 14, false);
			} 
			else SetFunctionTimerCondition("Slavetrader_HavanaSeekOver", 0, 0, 7, false);
			pchar.questTemp.Slavetrader = "Havana_seekslaves";
		break;
		
		case "Havana_Fort_yes":
			dialog.text = "太棒了! 你一如既往地完成了我的任务。 我对你非常满意。 ";
			link.l1 = "我也是... 但当我收到货物的钱时, 我会更满意。 ";
			link.l1.go = "Havana_Fort_yes_1";
		break;
		
		case "Havana_Fort_yesA":
		dialog.text = "我为此非常高兴。 你迟到了, 但你以最出色的方式完成了我的任务。 ";
			link.l1 = "现在我想拿到货物的钱。 ";
			link.l1.go = "Havana_Fort_yes_1";
			pchar.quest.Slavetrader_HavanaSeekOver.over = "yes";
		break;
		
		case "Havana_Fort_yes_1":
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			dialog.text = "当然。 我打算把奴隶卖给我的客户, 他会付钱, 你就会得到你的硬币。 就像上次一样。 让我们看看, 你带来了" + sTemp + "个奴隶。 总数是" + FindRussianMoneyString(iSlaveMoney) + "。 一周后到这里来取钱。 ";
			link.l1 = "好的, " + npchar.name+ ", 我们说定了。 我一周后到这里来。 但要非常小心... ";
			link.l1.go = "Havana_Fort_yes_2";
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
		break;
		
		case "Havana_Fort_yes_2":
			dialog.text = "" +pchar.name+ ", 请不要这样。 我们是合作伙伴, 我们之间没有欺骗和不信任的空间。 我答应过你很多硬币, 你也得到了。 我答应过你有趣的任务, 你也得到了。 即使在我生意最黑暗的日子里, 我也一直在补偿你的费用。 我难道没有信守诺言吗? ";
			link.l1 = "嗯... 不... 我只是想拿到钱, 就这样。 ";
			link.l1.go = "Havana_Fort_yes_3";
		break;
		
		case "Havana_Fort_yes_3":
			dialog.text = "现在明白了... " +pchar.name+ ", 你是我最好的代理人, 我指望将来再和你做生意。 ";
			link.l1 = "好的, " + npchar.name+ "。 但你也必须理解我 —一百万比索是一大笔钱。 ";
			link.l1.go = "Havana_Fort_yes_4";
		break;
		
		case "Havana_Fort_yes_4":
			dialog.text = "我非常理解你, 但我必须先卖掉奴隶, 然后才能收到钱。 ";
			link.l1 = "好的。 我想我们互相理解了。 ";
			link.l1.go = "Havana_Fort_yes_5";
		break;
		
		case "Havana_Fort_yes_5":
			dialog.text = "太好了。 一周后见。 现在我得准备一下, 然后去和我的客户交易。 ";
			link.l1 = "那我就不打扰你了。 一周后见, " + npchar.name+ "。 ";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader.Name = npchar.name;
			AddQuestRecord("Slavetrader", "32");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_6");
			SetFunctionTimerCondition("Slavetrader_UsurerEscape", 0, 0, 8, false);
			pchar.questTemp.Slavetrader = "wait_6";
			pchar.questTemp.Slavetrader.Cityname = npchar.city +"_town";
			LocatorReloadEnterDisable(npchar.city +"_town", "reload8_back", true);//为了整整一周都不在这里
		break;

		case "Usurer_Escape":
			dialog.text = "我在这里做什么? 嗯... 这是我的银行。 我两天前买的。 你是我的第一个客户, 我可以给你提供非常诱人的信贷条件... ";
			link.l1 = "去他的信贷! " + pchar.questTemp.Slavetrader.Name + "在哪里? ";
			link.l1.go = "Usurer_Escape_1";
		break;

		case "Usurer_Escape_1":
			dialog.text = "请冷静! 他很久以前就跑了。 ";
			link.l1 = "怎么跑的? ";
			link.l1.go = "Usurer_Escape_2";
		break;
		
		case "Usurer_Escape_2":
			dialog.text = "你不知道吗? 他一周前就消失了。 原来他拿走了所有客户的投资。 据说甚至总督也受到了损失。 这所房子被留下了, 我从殖民地买了下来。 ";
			link.l1 = "消失了? 怎么消失的? ";
			link.l1.go = "Usurer_Escape_3";
		break;
		
		case "Usurer_Escape_3":
			dialog.text = "我听说他从我们的殖民地逃跑了... 我想他也欠你钱。 很多? ";
			link.l1 = "超过一百万! 但我无论如何都会抓到那只老鼠! 他去哪里了? 他的船名是什么? ";
			link.l1.go = "Usurer_Escape_4";
		break;
		
		case "Usurer_Escape_4":
			dialog.text = "没人知道。 说真的。 他就这么走了。 那天有一艘名为‘毛里求斯’或‘毛尔迪乌斯’的船开走了, 也许他用它逃跑了。 ";
			link.l1 = "该死! 我竟然信任那个混蛋! 从第一天起他就有叛徒的味道! 而我却愚蠢到相信我们是真正的合作伙伴! 但总有一天我会让他后悔的... 好吧, " + npchar.name+ ", 我为我的行为道歉... 如果你是个好人, 我将来一定会和你打交道, 放心吧, 但现在, 再见。 ";
			link.l1.go = "Usurer_Escape_5";
		break;
		
		case "Usurer_Escape_5":
			string sColony;
			sColony = npchar.city;
			SetNull2Deposit(sColony);
			dialog.text = "没关系。 我理解。 如果你需要钱或者想投资, 我随时为你服务。 ";
			link.l1 = "谢谢。 但我最好把钱留给自己。 再见。 ";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "33");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "wait1";
			pchar.questTemp.SanBoxTarget.Slavetrader = true;
			ChangeCharacterComplexReputation(pchar, "fame", 25);
			LAi_LocationDisableOfficersGen(&Locations[FindLocation(pchar.location)], false); // 解锁军官进入 2015
		break;
	//<--奴隶商人	

	//--> 家族遗物
		case "Noblelombard":
			dialog.text = "哦, 真的吗? 看来他不想亲自和我谈... 好吧, 我们和你讨论这件事。 "+pchar.GenQuest.Noblelombard.Name+"欠我"+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Summ))+": "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Money))+", 还有我的利息 —三个月的"+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Percent))+"。 如果我最近几天看不到钱, 那么我就会卖掉他的遗物, 我不在乎它对他有什么价值。 生意就是生意。 ";
			if(sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Summ))
			{
				link.l1 = "太好了! 既然如此, 我现在就把全部款项连同所有利息一起付给你 —"+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Summ))+"。 他会自己拿走他的遗物。 这是你的钱。 ";
				link.l1.go = "Noblelombard_1";
			}
			if(sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Percent)*2)
			{
				link.l2 = "我的客户三个月后会有钱。 我们做个交易吧, 我付给你过去三个月和未来三个月的利息。 "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Percent)*2)+"。 债务本身稍后会付给你。 ";
				link.l2.go = "Noblelombard_2";
			}
			if(sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Percent))
			{
				link.l3 = "我的客户三个月后会有钱。 我付给你过去三个月的利息, 你等我的客户有足够的钱怎么样? ";
				link.l3.go = "Noblelombard_3";
			}
			link.l4 = "这件珍品价值连城! 看来我的客户必须自己付钱了。 ";
			link.l4.go = "Noblelombard_4";
			pchar.quest.noblelombard = "true";//从NPC到玩家的樵夫
		break;
		
		case "Noblelombard_1":
			dialog.text = "太好了! 一切都很顺利, 我拿到了我的钱, "+pchar.GenQuest.Noblelombard.Name+"也会拿回他的遗物。 ";
			link.l1 = "和你做生意很愉快, "+npchar.name+"! 现在再见。 ";
			link.l1.go = "exit";
			pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Summ)*2;
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Summ));
			pchar.GenQuest.Noblelombard = "full";
			AddCharacterExpToSkill(pchar, "Leadership", 150);
	
		break;
		
		case "Noblelombard_2":
			if(sti(pchar.GenQuest.Noblelombard.Chance) < 7)
			{
				dialog.text = "嗯..好吧。 这对我来说可行。 但是如果"+pchar.GenQuest.Noblelombard.Name+"三个月内找不到钱, 那么我不会再拖延了。 确保他知道这一点。 ";
				link.l1 = "我会的! 很高兴我们达成了协议。 现在再见。 ";
				link.l1.go = "exit";
				pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Percent)*4;
				AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Percent)*2);
				pchar.GenQuest.Noblelombard = "maxpercent";
				AddCharacterExpToSkill(pchar, "Leadership", 50);
				AddCharacterExpToSkill(pchar, "Fortune", 70);
			
			}
			else
			{
				dialog.text = "不。 这不行。 我需要全部款项, 而且要在日落前。 确保你的‘客户’知道这一点。 我没有更多要告诉你的了。 ";
				link.l1 = "嗯... 好吧。 真遗憾你不想妥协。 ";
				link.l1.go = "Noblelombard_4";
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			
			}
		break;
		
		case "Noblelombard_3":
			if(sti(pchar.GenQuest.Noblelombard.Chance) < 3)
			{
				dialog.text = "嗯..好吧。 我接受, 只是因为我尊重你的客户。 但是如果"+pchar.GenQuest.Noblelombard.Name+"三个月内找不到钱, 那么我不会再拖延了。 确保他知道这一点。 ";
				link.l1 = "我会的! 很高兴我们达成了协议。 现在再见。 ";
				link.l1.go = "exit";
				pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Percent)*2;
				AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Percent));
				pchar.GenQuest.Noblelombard = "minpercent";
				AddCharacterExpToSkill(pchar, "Leadership", 50);
				AddCharacterExpToSkill(pchar, "Fortune", 150);
			}
			else
			{
				dialog.text = "不。 这不行。 我需要全部款项, 而且要在日落前。 确保你的‘客户’知道这一点。 我没有更多要告诉你的了。 ";
				link.l1 = "嗯... 好吧。 真遗憾你不想妥协。 ";
				link.l1.go = "Noblelombard_4";
				AddCharacterExpToSkill(pchar, "Fortune", 60);
	
			}
		break;
		
		case "Noblelombard_4":
			DialogExit();
			pchar.GenQuest.Noblelombard = "fail";
		break;
		
		case "Noblelombard_5":
			if(sti(pchar.GenQuest.Noblelombard.Chance) == 9)
			{
				dialog.text = "你不说我也知道! "+pchar.GenQuest.Noblelombard.Name+"没有为你的名字开设存款。 他甚至不在我们的殖民地 —航行到欧洲去了。 我告诉你, 我从未见过如此不诚实的人。 他想骗我, 但失败了 —我有自己的一些技巧... ";
				link.l1 = "混蛋! 他向我保证过... ";
				link.l1.go = "Noblelombard_6";
			}
			else
			{	// Addon-2016 Jason 减少杜布隆的发放
				dialog.text = "正确。 "+pchar.GenQuest.Noblelombard.Name+"已经为你的名字做了存款。 请拿去吧... ";
				link.l1 = "太好了! 再见, "+npchar.name+"。 ";
				link.l1.go = "Noblelombard_9";
			}
		break;
		
		case "Noblelombard_6":
			dialog.text = "像"+pchar.GenQuest.Noblelombard.Name+"这样的人是没有荣誉和良心的。 我想他骗了你? ";
			link.l1 = "我想是的。 不管怎样, "+npchar.name+", 我也不打算在这里久留, 欧洲很小... 也许, 我们有一天会见面。 再见! ";
			link.l1.go = "Noblelombard_7";
		break;
		
		case "Noblelombard_7":
			DialogExit();
			AddDialogExitQuestFunction("Noblelombard_Usurer_bad");
		break;
		
		case "Noblelombard_9":
			DialogExit();
			AddDialogExitQuestFunction("Noblelombard_Usurer_good");
		break;
//< —家族遗物

		// 加斯科涅人的负担
		case "sharlie_credit":
			dialog.text = "先生, 我不认识你。 我只借钱给当地居民或船长。 请原谅我... ";
			link.l1 = "我明白了。 不过太遗憾了。 ";
			link.l1.go = "exit";
		break;
		// 加斯科涅人的负担
		
		// Addon-2016 Jason, 法国迷你任务 (FMC)
		// FMC-瓜德罗普
		case "FMQG_x":
			DelLandQuestMark(npchar);
			dialog.text = "什-什么... 你是什么意思? ";
			link.l1 = "你是个该死的叛徒! 现在仔细听我说: 我没那么蠢。 皮内特写了两封信。 我给了你一封, 第二封在我信任的代理人手里。 如果我有什么不测 —我的人会把它直接送到总督手里... ";
			link.l1.go = "FMQG_x1";
		break;
		
		case "FMQG_x1":
			dialog.text = "";
			link.l1 = "所以我建议你每天早上在教堂做礼拜时为我的健康祈祷, 而不是派刺客来取我的命。 最后一次警告! 对我采取行动, 你就完了。 明白了吗? 好的。 深吸一口气, 继续数你的杜布隆吧。 ";
			link.l1.go = "FMQG_x2";
		break;
		
		case "FMQG_x2":
			DialogExit();
			pchar.questTemp.FMQG = "end";
			FMQ_Count();
			AddQuestRecord("FMQ_Guadeloupe", "27");
			CloseQuestHeader("FMQ_Guadeloupe");
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			AddCharacterExpToSkill(pchar, "Sneak", 400);
			AddCharacterExpToSkill(pchar, "Sailing", 200);
			bQuestDisableMapEnter = false;//打开地图
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		// 其他
		case "NeHochuRazgovarivat":
			dialog.text = "我不想和你说话。 ";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		// 贝丝女士 -->
		case "LadyBeth_Usurer_1":
			dialog.text = "当然! 很多人只是想拿到钱就离开。 尤其是考虑到最近的传言... ";
			link.l1 = "什么传言? ";
			link.l1.go = "LadyBeth_Usurer_2";
		break;
		
		case "LadyBeth_Usurer_2":
			dialog.text = "他们说船员的条件越来越差。 布莱克伍德先生甚至开始容忍定期的损失 —这是以前从未发生过的。 但那不是我的事。 我只是卖货。 那么你对什么感兴趣? ";
			link.l1 = "我们言归正传吧。 ";
			link.l1.go = "next";
			npchar.quest.item_date = "LadyBeth";
			pchar.questTemp.LadyBeth_Usurer = true;
		break;
		// 贝丝女士 <--
	}	
}

// ugeen 检查, 我们是否可以使用杜布隆作为存款
bool CheckUseDublons(ref NPChar)
{
	int iTest 	= FindColony(NPChar.City); // 银行城市
	if(iTest == -1) return false;
	
	ref rColony = GetColonyByIndex(iTest);
	 	 
	bool bOk1 = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea); 
	bool bOk2 = (GetCharacterItem(pchar,"gold_dublon") > 10) || (CheckItemMyCabin("gold_dublon") > 10);
	
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && bOk1 && bOk2) return true;

	return false;
}

void SlavetraderGalleonInWorld()
{
	//创建载有奴隶的大帆船
	ref sld;
	string sName;
	sName = pchar.questTemp.Slavetrader.ShipName;
	sld = GetCharacter(NPC_GenerateCharacter("GaleonCap", "", "man", "man", 45, SPAIN, 20, true, "quest"));
	FantomMakeCoolSailor(sld, SHIP_LINESHIP, sName, CANNON_TYPE_CANNON_LBS42, 100, 100, 100);
	FantomMakeCoolFighter(sld, 45, 100, 100, "blade_21", "pistol5", "bullet", 100);
	sld.Ship.Mode = "war";	
	SetCaptanModelByEncType(sld, "war");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;
	sld.DontRansackCaptain = true;
	sld.WatchFort = true;
	sld.AlwaysEnemy = true;


	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterGoods(sld, GOOD_SLAVES, 3000 + rand(200));//把奴隶放进货舱
	sld.ship.Crew.Morale = 100;
	ChangeCrewExp(sld, "Sailors", 100);
	ChangeCrewExp(sld, "Cannoners", 100);
	ChangeCrewExp(sld, "Soldiers", 100);
	//加入船长的海上集团
	string sGroup = "SlaveGalleon";
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	pchar.quest.SlaveHalleon_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.SlaveHalleon_AfterBattle.win_condition.l1.group = "SlaveGalleon";
	pchar.quest.SlaveHalleon_AfterBattle.function = "Slavetrader_SlaveHalleon_AfterBattle";
	sld.city = pchar.questTemp.Slavetrader.Island; //确定他将从哪个海湾出发的殖民地
	sld.cityShore = pchar.questTemp.Slavetrader.Island.Shore;
	sld.quest.targetCity = "Santiago"; //确定他将到达哪个海湾的殖民地
	sld.quest.targetShore = GetIslandRandomShoreId(GetArealByCityName(sld.quest.targetCity));
	//Log_TestInfo("大帆船的船长从 " + sld.city + " 起航, 前往 " + sld.quest.targetShore);
	//==> 到地图上
	sld.mapEnc.type = "trade";
	//选择地图上的船只类型
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = "大帆船'" + sName + "'";
	int daysQty = 20; //给足够的天数到达
	Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, daysQty);//这就是它, 启动遭遇战
}

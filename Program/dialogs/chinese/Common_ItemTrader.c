#include "DIALOGS\%language%\Rumours\Common_rumours.c" //Jason
void ProcessDialogEvent()
{
 	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// 调用城市对话 -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\ItemTrader\" + NPChar.City + "_ItemTrader.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // 调用城市对话 <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
// ============================================================================
// ============================= 愤怒模块 ==========>>>>>>>>>>>>>>>>>>>>>>>>>
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //首次触发陷阱
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
			
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= 愤怒模块 ===================================
// ============================================================================	   
	switch(Dialog.CurrentNode)
	{
		// -----------------------------------首次对话 - 第一次见面
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
			dialog.text = NPCharSexPhrase(npchar, "船长, 您想为自己或军官购买装备吗? 如果是, 那您来对地方了! ", "哦, 船长, 我就知道您会来找我! 我可以为您和您的军官提供装备, 还有许多其他有用的东西。 ");
			link.l1 = "给我看看你有什么。 ";
			link.l1.go = "Trade_exit";
			
   			/*link.l2 = "我来有别的事。 ";
			link.l2.go = "quests";*/
			// -->曼加罗萨
			if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "find" && npchar.Merchant.type == "potion" && !CheckAttribute(npchar, "quest.mangarosa"))
			{
				link.l4 = "嘿, 我在附近发现了一种有趣的植物。 您能告诉我它是否可以用来酿造药水或汤药吗? 我只是觉得有趣。 您能看看吗? ";
				link.l4.go = "mangarosa";
			}
			// <--曼加罗萨
			

			//Jason --> 迷你任务 短缺商品
			if (CheckAttribute(pchar, "questTemp.Wine.bottle") && NPChar.location == pchar.questTemp.Wine.City + "_town" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
   				link.l4 = "说起来, 您能卖给我一瓶优质的欧洲葡萄酒吗? ";
				link.l4.go = "Wine_ItemTrader";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.bottles") && NPChar.location == pchar.questTemp.Wine.City + "_town" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
   				link.l4 = "听着, 我知道您在卖欧洲葡萄酒。 我需要六十瓶。 ";
				link.l4.go = "Wine_Bottles";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.Repeat1") && NPChar.location == pchar.questTemp.Wine.City + "_town" && npchar.id == pchar.questTemp.Wine.ItemTraderID && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
   				link.l4 = "又是我。 这到底是什么意思, 嗯? ";
				link.l4.go = "Wine_Repeat1";
			}
			// <—— 迷你任务 短缺商品
			
			//Sinistra --> 迷你任务 "结识印第安人"
			if (CheckAttribute(pchar, "questTemp.ZsI_PokupaemPistolety") && npchar.Merchant.type == "armourer")
			{
   				link.l4 = "我需要两把手枪, 以及二十发子弹和火药。 ";
				link.l4.go = "ZsI_PokupaemPistolety";
			}
			// <—— 迷你任务 "结识印第安人"
			
			// --> 查科酒的价格
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l4 = "听着,'胡安'这个名字您有印象吗? ";
				link.l4.go = "Consumption";
			}
			// <—— 查科酒的价格
			
			//--> 被盗的记忆
			if(CheckAttribute(pchar, "questTemp.UV_Lavochniki") && !CheckAttribute(npchar, "quest.UV_Vopros") && npchar.city == "PortPax")
			{
				link.l4 = "好商人, 我在寻找一件品质非凡的物品。 不是满足大多数人的普通饰品, 而是真正精致的物件 --或许是一对工艺精湛的耳环或一件值得贵族品味的优雅吊坠。 我需要一件能取悦出身高贵女士的礼物。 ";
				link.l4.go = "UV_Lavochniki_1";
			}
			if(CheckAttribute(pchar, "questTemp.UV_Lavochniki_2") && !CheckAttribute(npchar, "quest.UV_Vopros") && npchar.city == "PortPax")
			{
				link.l4 = "我想知道在您的库存中是否有什么贵重物品? 我寻找的是能满足最挑剔贵族女性品味的东西 --独特而精致, 远非普通市民所喜爱的。 或许是一件工艺非凡的吊坠或设计精美的手镯? ";
				link.l4.go = "UV_Lavochniki_2";
			}
			if(CheckAttribute(pchar, "questTemp.UV_Lavochniki_3") && !CheckAttribute(npchar, "quest.UV_Vopros") && npchar.city == "PortPax")
			{
				link.l4 = "告诉我, 好商人, 您对精美珠宝有研究吗? 我想找一件非凡的礼物送给一位有身份的女士。 坦率地说, 我对普通饰品不感兴趣。 我需要的是真正华丽的东西: 也许是一枚镶嵌宝石的胸针或一枚工艺无与伦比的戒指。 ";
				link.l4.go = "UV_Lavochniki_3";
			}
			//<—— 被盗的记忆
			
			//Jason --> 生成器 不幸的小偷
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l5 = "听着, 您在买卖各种商品... 昨天或今天 - 有没有人主动向您出售" + pchar.GenQuest.Device.Shipyarder.Type + "? ";
				link.l5.go = "Device_ItemTrader";
			}
			//<—— 生成器 不幸的小偷

			link.l9 = "谢谢, 不感兴趣。 ";
			link.l9.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Trade_exit":
            if (CheckNPCQuestDate(npchar, "Item_date"))
			{
				SetNPCQuestDate(npchar, "Item_date");
				GiveItemToTrader(npchar);
			}
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchItemsTrade(npchar, 0);
		break;
		
		//Jason --> 迷你任务 短缺商品
		case "Wine_ItemTrader":
			dialog.text = "当然。 每瓶七百比索。 ";
			if (makeint(Pchar.money) >= 700)
			{
				link.l1 = "太好了。 拿钱给我吧。 ";
				link.l1.go = "Wine_ItemTrader_1";
			}
			link.l2 = "太好了! 我决定买的时候会回来的。 ";
			link.l2.go = "exit";
		break;
		
		case "Wine_ItemTrader_1":
			dialog.text = "请拿好您的酒。 ";
			link.l1 = "谢谢! ";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -700);
			TakeNItems(pchar, "potionwine", 1);
			PlaySound("interface\important_item.wav");
			DeleteAttribute(pchar, "questTemp.Wine.bottle");
			AddQuestRecord("Wine", "1_1");
			WineTraderQMDel();
		break;
		
		case "Wine_Bottles":
			dialog.text = "哈! 我只是个零售商, 不是批发商。 卖那么多瓶我得卖半年多 - 那酒很稀有又贵, 不是谁都买得起的, 您知道的。 我没有那么多。 ";
			link.l1 = "好吧, 您没有 - 没问题。 但您自己是从某处进货的, 对吧? 也许您可以告诉我您供应商的名字, 我直接从他那里买。 或者酒是从欧洲运来的? ";
			link.l1.go = "Wine_Bottles_1";
		break;
		
		case "Wine_Bottles_1":
			dialog.text = "不, 不是。 我在这里进货。 但我不会就这样告诉您我的供应商。 但给一千比索... 也许可以... ";
			if (makeint(Pchar.money) >= 1000)
            {
				link.l1 = "好吧。 这是您的一千比索 - 现在告诉我, 您的供应商是谁。 ";
				link.l1.go = "Wine_Bottles_2";
			}
			link.l2 = "现在你们这些小贩太厚颜无耻了! 对您来说是不是太好了? 谢谢, 我不用您的供应商也能行。 ";
			link.l2.go = "Wine_Bottles_fail";
		break;
		
		case "Wine_Bottles_free":
			dialog.text = "我想... 好吧。 这是您的便条, 希望您以后能回报这份人情。 ";
			link.l1 = "... ";
			link.l1.go = "Wine_Bottles_free_1";
		break;
		
		case "Wine_Bottles_free_1":
			pchar.questTemp.Wine.TraderID = pchar.questTemp.Wine.City +"_trader";
			sld = characterFromId(pchar.questTemp.Wine.TraderID);
			pchar.questTemp.Wine.Name = GetFullName(sld);
			pchar.questTemp.Wine.ItemTraderID = npchar.id;
			dialog.text = "我葡萄酒供应商的名字是" + pchar.questTemp.Wine.Name + ", 他拥有当地的商店。 ";
			link.l1 = "知道了! 谢谢! ";
			link.l1.go = "exit";
			//pchar.questTemp.Wine.Trader = "true";
			DeleteAttribute(pchar, "questTemp.Wine.bottles");
			pchar.questTemp.Wine.Repeat2 = "true";
			TakeNItems(pchar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_1");
			PlaySound("interface\important_item.wav");
		break;
		
		case "Wine_Bottles_2":
    		AddMoneyToCharacter(pchar, -1000);
			pchar.questTemp.Wine.TraderID = pchar.questTemp.Wine.City +"_trader";
			sld = characterFromId(pchar.questTemp.Wine.TraderID);
			AddLandQuestMark(sld, "questmarkmain");
			pchar.questTemp.Wine.Name = GetFullName(sld);
			pchar.questTemp.Wine.ItemTraderID = npchar.id;
			dialog.text = "我葡萄酒供应商的名字是" + pchar.questTemp.Wine.Name + ", 他拥有当地的商店。 ";
			link.l1 = "知道了! 谢谢! ";
			link.l1.go = "exit";
			pchar.questTemp.Wine.Trader = "true";
			DeleteAttribute(pchar, "questTemp.Wine.bottles");
			AddQuestRecord("Wine", "3");
			AddQuestUserData("Wine", "sName", pchar.questTemp.Wine.Name);
			WineTraderQMDel();
		break;
		
		case "Wine_Bottles_fail":
			dialog.text = "如您所愿, 船长。 祝您一切顺利。 ";
			link.l1 = "再见。 ";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Wine.bottles");
			AddQuestRecord("Wine", "4");
			WineTraderQMDel();
		break;
		
		case "Wine_Repeat1":
			DeleteAttribute(pchar, "questTemp.Wine.Repeat1");
			dialog.text = "您这是什么意思? 解释一下。 ";
			link.l1 = "你骗了我, 你这个无赖! 我刚去过商店, " + pchar.questTemp.Wine.Name + "根本不卖酒, 他自己跟我说的! 把钱还给我! ";
			link.l1.go = "Wine_Repeat1_fail";
			link.l2 = "有个误会... 我去找了店主, " + pchar.questTemp.Wine.Name + "声称他从不卖酒。 你怎么解释? ";
			link.l2.go = "Wine_Repeat1_1";
		break;
		
		case "Wine_Repeat1_1":
			dialog.text = "嘿! 他当然卖酒, 千真万确。 只是他不随便卖给任何人 - 就像其他一些商品一样。 这有几个原因... 如果您想从他那里买酒, 我可以给他写张便条。 他认识我和我的笔迹, 所以他看完后会卖给您酒。 当然, 这个忙也不是免费的。 ";
			link.l1 = "太离谱了! 你刚从我这里拿了一千比索! ";
			link.l1.go = "Wine_Repeat1_2";
		break;
		
		case "Wine_Repeat1_2":
			dialog.text = "我拿了您一千比索作为信息费。 而写封信您得另外付两千比索, 而且不能少于这个数。 ";
			if (makeint(Pchar.money) >= 2000)
			{
				link.l1 = "哦... 你们这些商人太贪婪了。 难怪没人喜欢你们这种人。 好吧, 这是您的钱, 写便条吧。 ";
				link.l1.go = "Wine_Bottles_3";
			}
			if(CheckCharacterPerk(pchar, "Trustworthy"))
			{
				notification("Trustworthy", "Trustworthy");
				link.l2 = "(值得信赖) 我们做个妥协吧。 您现在免费提供推荐, 我以后也会免费为您提供推荐。 这笔葡萄酒交易只是个开始。 ";
				link.l2.go = "Wine_Bottles_free";
			}
			link.l3 = "这太过分了! 我宁愿放弃整个事情, 也不会让你这个狡猾的守财奴发财。 我说的就是你。 再见。 ";
			link.l3.go = "Wine_Repeat1_goaway";
		break;
		case "Wine_Bottles_free":
			dialog.text = "我想... 好吧。 这是您的便条, 希望您以后能回报这份人情。 ";
			link.l1 = "... ";
			link.l1.go = "Wine_Bottles_free_1";
		break;
		
		case "Wine_Bottles_free_1":
			pchar.questTemp.Wine.Repeat2 = "true";
			TakeNItems(pchar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_1");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Wine", "6_1");
			DelLandQuestMark(npchar);
			sld = characterFromId(pchar.questTemp.Wine.TraderID);
			AddLandQuestMark(sld, "questmarkmain");
			DialogExit();
		break;
		
		case "Wine_Bottles_3":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "您真是个奇怪的人, 船长! 当然, 我知道您的财务由 purser 负责, 但您也应该自己动动脑筋。 您将有机会以批发价购买大量葡萄酒, 没有我的加价, 从而获得可观的利润。 所以我们不要互相妨碍赚钱, 因为现在看起来您才是贪婪的那个。 \n对... (写字) 拿着这封信 - " + pchar.questTemp.Wine.Name + " 会毫无问题地卖给您葡萄酒。 ";
			link.l1 = "我希望如此... 如果再出问题, 我会回来的。 再见! ";
			link.l1.go = "Wine_Bottles_4";
		break;
		
		case "Wine_Bottles_4":
			pchar.questTemp.Wine.Repeat2 = "true";
			TakeNItems(pchar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_1");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Wine", "6");
			DelLandQuestMark(npchar);
			sld = characterFromId(pchar.questTemp.Wine.TraderID);
			AddLandQuestMark(sld, "questmarkmain");
			DialogExit();
		break;
		
		case "Wine_Repeat1_goaway":
			dialog.text = "如您所愿, 船长。 再见。 ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddQuestRecord("Wine", "4");
			DelLandQuestMark(npchar);
		break;
		
		case "Wine_Repeat1_fail":
			dialog.text = "哦, 所以您来这里是为了威胁我和无礼? 那我叫卫兵了! 嘿, 卫兵! 这里! ";
			link.l1 = "哦, 闭嘴! 你赢了, 我走! 诅咒你" + NPCharSexPhrase(npchar, "","") + ", 贪婪的家伙, 愿你破产! ";
			link.l1.go = "exit";
			AddQuestRecord("Wine", "7");
			DelLandQuestMark(npchar);
		break;
		// <—— 迷你任务 短缺商品
		
		//Sinistra --> 迷你任务 "结识印第安人"
		case "ZsI_PokupaemPistolety":
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				dialog.text = "啊, 我明白了。 和当地人做交易? 我听说这已经让您花了不少钱, 哈哈! ";
			}
			else
			{
				dialog.text = "期待麻烦吗, 船长? 还是计划丛林探险? 哈哈! ";
			}
			link.l1 = "那么, 我们可以成交吗? ";
			link.l1.go = "ZsI_PokupaemPistolety_1";
			DelLandQuestMark(npchar);
		break;
		
		case "ZsI_PokupaemPistolety_1":
			dialog.text = "当然! 随时欢迎顾客。 三千比索, 您将得到可靠的手枪。 子弹和所需的火药。 ";
			if (sti(pchar.Money) > 2999)
			{
				link.l1 = "贵是贵, 但好吧。 我买了。 ";
				link.l1.go = "ZsI_PokupaemPistolety_2";
			}
			if (sti(pchar.Money) > 2299)
			{
				link.l2 = "价格似乎不公平。 作为法迪.莫斯科维特的朋友, 能打折吗? ";
				link.l2.go = "ZsI_Torg";
			}
			link.l3 = "三千? 这是抢劫! 再见, 先生! ";
			link.l3.go = "ZsI_NetDeneg";
		break;
		
		case "ZsI_NetDeneg":
			DialogExit();
			
			LocatorReloadEnterDisable("BasTer_town", "gate_back", false);
			PChar.quest.ZsI_Timer.over = "yes";
			sld = CharacterFromID("ListKakao");
			sld.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.ZsI_PokupaemPistolety");
		break;
		
		case "ZsI_PokupaemPistolety_2":
			dialog.text = "祝您在那里一切顺利, 船长! ";
			link.l1 = "再见, 先生。 ";
			link.l1.go = "ZsI_PokupaemPistolety_3";
			AddMoneyToCharacter(pchar, -3000);
			Log_info("您已获得可可叶所需的手枪");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "ZsI_PokupaemPistolety_3":
			DialogExit();
			
			LocatorReloadEnterDisable("BasTer_town", "gate_back", false);
			DeleteAttribute(pchar, "questTemp.ZsI_PokupaemPistolety");
			PChar.quest.ZsI_Patrul.win_condition.l1 = "location";
			PChar.quest.ZsI_Patrul.win_condition.l1.location = "BasTer_ExitTown";
			PChar.quest.ZsI_Patrul.win_condition = "ZsI_Patrul";
		break;
		
		case "ZsI_Torg":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) > 18)
			{
				notification("技能检查通过", SKILL_COMMERCE);
				dialog.text = "确实, 船长。 法迪的朋友在这里总是受欢迎的。 两千三百比索如何? ";
				link.l1 = "这听起来更好。 我买了。 ";
				link.l1.go = "ZsI_Torg_2";
				AddCharacterExpToSkill(pchar, "Commerce", 30);
			}
			else
			{
				notification("技能检查失败 (19)", SKILL_COMMERCE); 
				dialog.text = "法迪先生的朋友总是受欢迎的, 但价格不讲情面。 三千比索, 船长。 ";
				if (sti(pchar.Money) > 2999)
				{
					link.l1 = "贵是贵, 但好吧。 我买了。 ";
					link.l1.go = "ZsI_PokupaemPistolety_2";
				}
				link.l2 = "三千? 这是抢劫! 再见, 先生! ";
				link.l2.go = "ZsI_NetDeneg";
				//Log_info("交易技能不足");
				AddCharacterExpToSkill(pchar, "Commerce", -30);
			}
		break;
		
		case "ZsI_Torg_2":
			dialog.text = "祝您在那里一切顺利, 船长! ";
			link.l1 = "再见, 先生。 ";
			link.l1.go = "ZsI_PokupaemPistolety_3";
			AddMoneyToCharacter(pchar, -2300);
			Log_info("您已获得可可叶所需的手枪");
			PlaySound("Interface\important_item.wav");
		break;
		// <—— 迷你任务 "结识印第安人"
		
		// --> 查科酒的价格
		case "Consumption":
			dialog.text = "不记得... 现在, 请不要打扰我, 我很忙... 多么愚蠢的问题... ";
			link.l1 = "我明白了。 抱歉浪费您的时间... ";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
		// <—— 查科酒的价格
		//Jason --> 生成器 不幸的小偷
		case "Device_ItemTrader":
			dialog.text = "嗯, " + pchar.GenQuest.Device.Shipyarder.Type + "? 以前从没听说过... 那到底是什么? 我这辈子都没听说过这种东西" + NPCharSexPhrase(npchar, "","") + "。 ";
			link.l1 = "嗯, 这是一种造船工具, " + pchar.GenQuest.Device.Shipyarder.Describe + "。 有没有人向您提供过类似的东西? ";
			link.l1.go = "Device_ItemTrader_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_ItemTrader_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 0 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 4 && npchar.location.group == "merchant" && npchar.location.locator == "merchant"+sti(pchar.GenQuest.Device.Shipyarder.Chance1))
			{
				dialog.text = "嗯... 是的, 有一个奇怪的家伙。 但他没告诉我那是什么, 只是想卖给我。 但如果我不知道那是什么, 我要它干什么? 我怎么转卖? 所以, 我拒绝了" + NPCharSexPhrase(npchar, "","") + ", 他就走了";
				link.l1 = "他长什么样, 去哪里了? 我急需那个工具。 ";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "不, 没有这样的东西。 抱歉, 我帮不了您。 问问别人吧。 ";
				link.l1 = "我知道了。 好吧, 是时候问问别人了! ";
				link.l1.go = "exit";
			}
		break;
		// <—— 生成器 不幸的小偷
		
		// 曼加罗萨
		case "mangarosa":
			// 这里靠运气
			if (sti(pchar.questTemp.Mangarosa.m_count) == 5 || GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 10+hrand(30)+hrand(40, "1"))
			{
				dialog.text = "给我看看... 是的, 这是一种有趣的植物。 而且非常非常稀有。 它叫曼加罗萨。 我不知道它有什么用, 但有一个与之相关的有趣事实... ";
				link.l1 = "您是什么意思? ";
				link.l1.go = "mangarosa_1";
			}
			else
			{
				dialog.text = LinkRandPhrase("给我看看... 是的, 这是一种有趣的植物。 但不幸的是, 我只能告诉您这些。 如果它确实有什么用途, 我也不知道。 ","让我看看... 嗯... 它看起来像一种药用植物, 但我对它一无所知。 抱歉, 帮不了您。 ","它在哪里? 嗯... 我从没见过这种植物。 它看起来确实很有趣, 但我不知道它有什么用... ");
				link.l1 = "我明白了。 好吧, 我再问问别人。 抱歉。 ";
				link.l1.go = "mangarosa_exit";
			}
		break;
		
		case "mangarosa_exit":
			DialogExit();
			pchar.questTemp.Mangarosa.m_count = sti(pchar.questTemp.Mangarosa.m_count)+1;
			npchar.quest.mangarosa = "true";
		break;
		
		case "mangarosa_1":
			dialog.text = "流浪的吉普赛人和野蛮人对这些植物表现出极大的兴趣。 我曾经看到一个吉普赛人为了这样一根茎付了一把金子。 但我不知道他们为什么需要它。 ";
			link.l1 = "我明白了... 至少知道了些! 现在我知道该去哪里进一步询问了。 非常感谢! ";
			link.l1.go = "mangarosa_2";
		break;
		
		case "mangarosa_2":
			DialogExit();
			npchar.quest.mangarosa = "true";
			DeleteAttribute(pchar, "questTemp.Mangarosa.m_count");
			pchar.questTemp.Mangarosa = "gipsy";
			AddQuestRecord("Mangarosa", "2");
		break;
		
		//--> 被盗的记忆
		case "UV_Lavochniki_1":
			dialog.text = "遗憾的是, " + GetAddress_Form(NPChar) + ", 我的店里已经好几个月没有这样的精美商品了。 在这些困难时期, 对奢侈品的需求已经减弱。 光顾我店的普通人只能买得起普通饰品, 而贵族很少屈尊浏览我简陋的商品。 ";
			link.l1 = "很好... ";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.UV_Lavochniki");
			pchar.questTemp.UV_Lavochniki_2 = true;
			npchar.quest.UV_Vopros;
		break;

		case "UV_Lavochniki_2":
			dialog.text = "很遗憾, 船长, 这样的精美物品已经很久没有出现在我的店里了。 这个港口的富裕顾客很少光顾我这简陋的商店, 我的常客只寻求他们微薄钱包能负担的东西。 ";
			link.l1 = "很好... ";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.UV_Lavochniki_2");
			pchar.questTemp.UV_Lavochniki_3 = true;
			npchar.quest.UV_Vopros;
		break;

		case "UV_Lavochniki_3":
			dialog.text = "啊, 船长, 您的时机太不巧了... 就在几小时前, 我卖掉了一条真正华丽的项链 - 被另一位财力雄厚的船长买走了。 我的店定期收购能够融化最挑剔女士心的物品\n也许您明天再来? 吉赛尔... 也就是说... 我的供应商... 很可能会为您采购一件能让您永远赢得爱慕对象芳心的珍宝。 ";
			link.l1 = "时间是我不具备的奢侈品; 我需要立即得到这样的物品。 请告诉我, 购买您所说项链的幸运船长叫什么名字? ";
			link.l1.go = "UV_Lavochniki_3_1";
		break;

		case "UV_Lavochniki_3_1":
			dialog.text = "特里斯坦.雷尼尔,'金海鸥'号的船长。 他的船还锚泊在我们的港口。 但我必须承认, 我怀疑他是否会放弃这样的奖品。 如果他不愿意, 明天再来找我。 我以名誉担保, 船长, 您会发现这个安排非常令人满意。 ";
			link.l1 = "... ";
			link.l1.go = "UV_Lavochniki_exit";
			DeleteAttribute(pchar, "questTemp.UV_Lavochniki_3");
			AddDialogExitQuestFunction("UV_GoldSeagull");
		break;
		
		case "UV_Lavochniki_exit":
			DialogExit();
			AddQuestRecord("UV", "3");
			/*AddQuestUserData("UV", "sSex", NPCharSexPhrase(NPChar,"ца","ки"));
			AddQuestUserData("UV", "sSex1", NPCharSexPhrase(NPChar,"eц","ка"));
			AddQuestUserData("UV", "sSex2", NPCharSexPhrase(NPChar,"","а"));*/
		break;
		//<—— 被盗的记忆
		
// ======================== 愤怒节点模块 ===============>>>>>>>>>>>>>>>

////////////////////////////////////////////////////////////////////////////////////////////////
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok")
		break;

// <<<<<<<<<<<<============= 愤怒节点模块 =============================
	}
}
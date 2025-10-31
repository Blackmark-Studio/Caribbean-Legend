// 杰森 吉普赛人通用对话
// ugeen <-- 添加了出售地板下的鼠药功能
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	int poison_price;

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
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "啊, 你好, 亲爱的。 你想要什么? ";
			link.l1 = "我想没什么事。 ";
			link.l1.go = "exit";
			link.l2 = RandPhraseSimple("我有个问题要问你。 ", "我需要些信息。 ");
			link.l2.go = "quests";//(转发到城市文件)
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = LinkRandPhrase("亲爱的, 能行行好分享些金币吗? 我会告诉你的未来。 ", "嘿, 水手, 别那么匆忙! 想知道未来吗? ", "给我些烟草和几枚银币吧, 勇敢的年轻人。 我会看看你的未来。 (眨眼) 想听听吉普赛的秘密魔法吗? ");
				link.l1 = "抱歉, 我得走了。 ";
				link.l1.go = "exit";
				// --> 曼加罗莎
				if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "gipsy" && !CheckAttribute(npchar, "quest.mangarosa"))
				{
					link.l5 = "听着, 补锅匠女士, 我知道你们族人是药水和毒药方面的专家。 有人说你可能对这种植物感兴趣。 看看吧, 你觉得如何? ";
					link.l5.go = "mangarosa";
				}
				if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "gipsy_trade" && !CheckAttribute(npchar, "quest.mangarosa"))
				{
					link.l5 = "嘿, 黑眼睛的, 我有东西给你... 这是曼加罗莎。 想买点吗? ";
					link.l5.go = "mangarosa_trade1";
				}
				// < —曼加罗莎
				link.l2 = "你能为我算命吗? ";
				link.l2.go = "guess";
				link.l3 = RandPhraseSimple("我有个问题要问你。 ", "我需要些信息。 ");
				link.l3.go = "quests";//(转发到城市文件)
				npchar.quest.meeting = "1";
			}
			// --> 黑暗之水治疗
			if (CheckAttribute(pchar, "questTemp.DWH_Start") && !CheckAttribute(pchar, "questTemp.DWH_gipsy") && npchar.city == "SentJons")
			{
				link.l6 = "我在找一位照顾病人的吉普赛女人。 是你吗? ";
				link.l6.go = "dwh_ne_ta";
			}
			// < —黑暗之水治疗

			if (!CheckAttribute(npchar, "quest.poison_price") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && rand(2) == 0)
			{
				link.l4 = "嘿, 黑眼睛的, 你有灭鼠的毒药吗? 它们在我船上真是该死的麻烦。 ";
				link.l4.go = "get_poison_1";
			}
			NextDiag.TempNode = "First time";
		break;

//-------------------------------------------------算命-------------------------------------------------
		case "guess":
			dialog.text = "当然, 帅哥。 给我些硬币, 让我看看你的右手。 我会告诉你的未来, 并帮你避开灾难。 我从不骗人! 不满意退款! ";
			link.l1 = "我觉得这时候你的同伙该偷我口袋了... 我改变主意了, 没心情了。 ";
			link.l1.go = "exit";
			link.l2 = "你想要多少钱? ";
			link.l2.go = "guess_1";
		break;
		
		case "guess_1":
			dialog.text = "啊, 亲爱的, 就像你的钱包能承受且你内心渴望的那么多。 八里亚尔越多, 我能看到的未来就越远! ";
			link.l1 = "100比索";
			link.l1.go = "guess_rate_1";
			link.l2 = "500比索";
			link.l2.go = "guess_rate_2";
			link.l3 = "1000比索";
			link.l3.go = "guess_rate_3";
			link.l4 = "5000比索";
			link.l4.go = "guess_rate_4";
		break;
		
		sTemp = GuessText();
		case "guess_rate_1"://没有任何加成
			if (sti(pchar.money) >= 100)
			{
				AddMoneyToCharacter(pchar, -100);
				dialog.text = "啊, 感谢你的慷慨, 我英俊的年轻猎鹰! 现在听着:   "+sTemp+"";
				link.l1 = LinkRandPhrase("呵! 真有趣。 我会考虑的... ", "真的吗? 我会考虑的... ", "哦, 真的吗? 你是认真的? 我会记住的... ");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "最丑陋且无法避免的不幸在等着你。 诅咒那个嘲弄者! 让乌云笼罩你, 让惩罚找到你! ";
				link.l1 = "哈哈! 你真以为我会给你钱吗, 你这个吉普赛女巫? 给我让开! 希望宗教裁判所把你抓走! ";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_2"://一点运气或隐匿能力
			if (sti(pchar.money) >= 500)
			{
				AddMoneyToCharacter(pchar, -500);
				dialog.text = "啊, 谢谢你, 我英俊的年轻猎鹰! 现在听着: "+sTemp+"";
				link.l1 = LinkRandPhrase("呵! 真有趣。 我会考虑的... ", "真的吗? 我会考虑的... ", "哦, 真的吗? 你是认真的? 好吧, 我会记住的... ", "嘿, 我已经感觉好多了! ");
				link.l1.go = "exit";
				if (hrand(1) == 0) AddCharacterExpToSkill(pchar, "Fortune", 30+rand(10));//运气
				else AddCharacterExpToSkill(pchar, "Sneak", 30+rand(10));//隐匿
			}
			else
			{
				dialog.text = "最丑陋且无法避免的不幸在等着你。 诅咒那个嘲弄者! 让乌云笼罩你, 让惩罚找到你! ";
				link.l1 = "哈哈! 你真以为我会给你钱吗, 你这个吉普赛女巫? 给我让开! 希望宗教裁判所把你抓走! ";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_3"://健康 + 运气或隐匿能力。 魅力
			if (sti(pchar.money) >= 1000)
			{
				AddMoneyToCharacter(pchar, -1000);
				dialog.text = "啊, 感谢你的银币, 我英俊的年轻猎鹰! 现在听着: "+sTemp+"";
				link.l1 = LinkRandPhrase("呵! 真有趣。 我会考虑的... ", "真的吗? 我会考虑的... ", "哦, 真的吗? 你是认真的? 好吧, 我会记住的... ");
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 1);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				if (hrand(1) == 0) AddCharacterExpToSkill(pchar, "Fortune", 50+rand(20));//运气
				else AddCharacterExpToSkill(pchar, "Sneak", 50+rand(20));//隐匿
			}
			else
			{
				dialog.text = "最丑陋且无法避免的不幸在等着你。 诅咒那个嘲弄者! 让乌云笼罩你, 让惩罚找到你! ";
				link.l1 = "哈哈! 你真以为我会给你钱吗, 你这个吉普赛女巫? 给我让开! 希望宗教裁判所把你抓走! ";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_4"://武器技能。 运气+隐匿。 健康。 魅力
			if (sti(pchar.money) >= 5000)
			{
				AddMoneyToCharacter(pchar, -5000);
				dialog.text = "哦啦啦! 感谢你的慷慨, 我英俊的年轻猎鹰! 现在听着: "+sTemp+"";
				link.l1 = LinkRandPhrase("呵! 真有趣。 我会考虑的... ", "真的吗? 我会考虑的... ", "哦, 真的吗? 你是认真的? 好吧, 我会记住的... ");
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 2);
				AddCharacterExpToSkill(pchar, "Leadership", 40);
				AddCharacterExpToSkill(pchar, "Fortune", 50+rand(100));//运气
				AddCharacterExpToSkill(pchar, "Sneak", 50+rand(50));//隐匿
				AddComplexSelfExpToScill(20, 20, 20, 20);
			}
			else
			{
				dialog.text = "最丑陋且无法避免的不幸在等着你。 诅咒那个嘲弄者! 让乌云笼罩你, 让惩罚找到你! ";
				link.l1 = "哈哈! 你真以为我会给你钱吗, 你这个吉普赛女巫? 给我让开! 希望宗教裁判所把你抓走! ";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_exit":
			DialogExit();
			AddCharacterHealth(pchar, -10);
			LAi_CharacterDisableDialog(npchar);
		break;
//< —算命

// --> 出售鼠药
		case "get_poison_1" :
			npchar.quest.poison_price = (hrand(3) + 1) * 10;
			if(hrand(10) == 3 || IsCharacterPerkOn(pchar, "Trustworthy"))
			{				
				dialog.text = LinkRandPhrase("哦, 我不确定, 帅哥! 不久前有个家伙请求帮忙灭鼠, 然后堡垒里的士兵就被人下毒了。 当卫兵审问我们两周直到找到凶手时, 岛上的我们族人日子很难过。 他是个敌方间谍。 ",
				                             "我怎么能确定你的目的呢? 也许你只是想毒死某个你不敢在荣誉决斗中对抗的贵族? ",
											 "我听说有人在酒馆里毒死了某个商人, 偷走了他所有的财物。 那个人在临死前痛苦了很久。 他口吐白沫, 脸色紫得像茄子... 亲爱的, 那是你干的吗? ");
				link.l1 = "你们这些吉普赛女人确实喜欢分享观点! 别担心, 姑娘, 我不打算毒死人。 那是女人的杀人方式, 不是我的风格。 对付男人我有剑, 但我对付不了那些该死的老鼠。 ";
				link.l1.go = "get_poison_2";
				if (IsCharacterPerkOn(pchar, "Trustworthy")) Notification_Perk(true, "Trustworthy");
			}
			else
			{
				dialog.text = "你想陷害我! 不, 先生, 我没有任何毒药。 我只有植物和药水, 没有毒药。 ";
				link.l1 = "那随便吧。 别对我施邪恶之眼。 ";
				link.l1.go = "exit";
				Notification_Perk(false, "Trustworthy");
			}	
		break;
		
		case "get_poison_2" :
			dialog.text = "哦, 帅哥, 真是个勇敢的男人! (低语) 给我"+sti(npchar.quest.poison_price)+"杜布隆。 ";
			if (PCharDublonsTotal() >= sti(npchar.quest.poison_price))
			{				
				link.l1 = "真贵... 这东西最好有用。 ";
				link.l1.go = "get_poison_4";
			}
			else
			{
				link.l1 = "没门! 我在老家花五个比索就能买到同样的东西! 花那么多钱我自己都能抓住所有老鼠了! ";
				link.l1.go = "get_poison_3";
			}
		break;
		
		case "get_poison_3" :
			dialog.text = "那你自己抓吧, 别烦我。 下次我叫卫兵了。 ";
			link.l1 = "没必要叫卫兵, 女巫, 我这就走。 ";
			link.l1.go = "exit";
		break;
		
		case "get_poison_4" :
			PlaySound("interface\important_item.wav");
			RemoveDublonsFromPCharTotal(sti(npchar.quest.poison_price));
			TakeNItems(pchar, "rat_poison", 1);
			DialogExit();
		break;
// < —出售鼠药

	// --> 曼加罗莎
		case "mangarosa":
			dialog.text = LinkRandPhrase("给我看看那植物, 亲爱的... 嗯... 我想我可以从你这买。 三百八里亚尔, 同意吗? ","给我看看, 帅哥... 嘿... 好吧, 我可以出二百五十。 ","让我看看... 哦! 一个有趣的样本! 二百比索! 成交? ")"";
			link.l1 = LinkRandPhrase("哦, 上帝... 黑眼睛的, 我不是什么乡巴佬。 我知道这植物。 这是曼加罗莎... ","哦, 真的吗? 这是完美的曼加罗莎样本。 别想骗我, 吉普赛人。 ","啊哈, 你以为我会为了这么点钱把这曼加罗莎给你。 ");
			link.l1.go = "mangarosa_1";
		break;
		
		case "mangarosa_1":
			dialog.text = "好吧, 好吧, 帅哥。 我看你对这植物有所了解。 五十杜布隆。 给我吧。 ";
			link.l1 = "等等! 我想知道它能怎么用。 用来做什么。 你能告诉我吗? 你们所有人都愿意为这小灌木付很多金币! ";
			link.l1.go = "mangarosa_2";
		break;
		
		case "mangarosa_2":
			// 这里魅力值起作用
			if (sti(pchar.questTemp.Mangarosa.g_count) == 5 || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 10+hrand(25)+hrand(30, "1"))
			{
				dialog.text = "嗯... 我想如果我稍微告诉你一些关于它的事情也无妨。 没有特殊技能, 你用这种植物也做不了什么。 ";
				link.l1 = "我在听。 ";
				link.l1.go = "mangarosa_3";
			}
			else
			{
				dialog.text = LinkRandPhrase("我的族人可能会花很多金币, 但他们绝不会泄露秘密。 ", "金币是金币, 秘密是秘密, 年轻人... ", "是的, 我们愿意付钱, 但不会说出来。 ") + "那么你要把曼加罗莎卖给我吗? 五十杜布隆是我们的收购价, 没人会给你更高的价格。 ";
				link.l1 = "哦, 好吧... 反正对我也有用。 五十杜布隆, 拿去吧。 ";
				link.l1.go = "mangarosa_trade";
				link.l2 = "听着, 我不想卖。 我想知道你们为什么需要它。 和我分享你的知识, 我就免费把它给你。 ";
				link.l2.go = "mangarosa_exit";
			}
		break;
		
		case "mangarosa_trade":
			RemoveItems(pchar, "cannabis7", 1);
			TakeNItems(pchar, "gold_dublon", 50);
			PlaySound("interface\important_item.wav");
			dialog.text = "拿着你的金币, 年轻的猎鹰。 还有一件事, 给我们带更多这种植物来。 但我们一次只能买一株, 因为我们不会随身携带大量钱财。 卫兵不信任我们这种人, 总爱骚扰我们... ";
			link.l1 = "好的。 如果我找到更多, 我会带来的。 ";
			link.l1.go = "mangarosa_trade_exit";
		break;
		
		case "mangarosa_trade_exit":
			DialogExit();
			npchar.quest.mangarosa = "true";
			DeleteAttribute(pchar, "questTemp.Mangarosa.g_count");
			pchar.questTemp.Mangarosa = "gipsy_trade";
			AddQuestRecord("Mangarosa", "3");
		break;
		
		case "mangarosa_exit":
			dialog.text = LinkRandPhrase("没门! 如果你不想卖, 那就别卖。 我什么都不会告诉你。 ", "我不会向一个愚蠢的外人泄露我们的秘密! (吐口水) 不想卖? 去你的。 ", "朋友, 这不是你该听的。 不想卖五十杜布隆? 去卖给那个贸易女孩换二百比索吧。 ");
			link.l1 = LinkRandPhrase("那对你太可惜了! 反正你们族里的其他人会告诉我的。 她还会得到这株植物作为礼物。 再见! ", "为什么这么固执? 如果你不告诉我, 别人会的。 她还会免费得到这株曼加罗莎。 再见。 ", "你嘴里有大蒜味。 我最终会得到我想要的。 你们族里会有更健谈的人, 她会免费得到这株植物。 再见。 ");
			link.l1.go = "exit";
			npchar.quest.mangarosa = "true";
			pchar.questTemp.Mangarosa.g_count = sti(pchar.questTemp.Mangarosa.g_count)+1;
		break;
		
		case "mangarosa_trade1":
			dialog.text = "你为什么问这个, 猎鹰? ! 当然! 把它给我。 ";
			link.l1 = "给我五十杜布隆。 ";
			link.l1.go = "mangarosa_trade1_1";
			link.l2 = "哎呀! 看来我把它弄丢了, 或者忘在船上了。 太可惜了。 再见... ";
			link.l2.go = "exit";
			npchar.quest.mangarosa = "true";
		break;
		
		case "mangarosa_trade1_1":
			RemoveItems(pchar, "cannabis7", 1);
			TakeNItems(pchar, "gold_dublon", 50);
			PlaySound("interface\important_item.wav");
			dialog.text = "别担心, 我不会骗你的。 拿着你的金币。 ";
			link.l1 = "拿好你的曼加罗莎。 如果我找到更多, 会再带来的。 ";
			link.l1.go = "exit";
		break;
		
		case "mangarosa_3":
			dialog.text = "我们用这种特殊的方法研磨花蕾, 然后晾干, 挑出种子和茎, 再与烟草混合, 塞进烟斗, 然后吸食这种混合物。 我们会得到一种... 难忘的效果。 就像喝醉了酒, 但之后不会头痛。 一株植物足够抽二十多斗。 ";
			link.l1 = "我明白了! 你能教我这个秘密技巧吗? 我可以给你丰厚的报酬... ";
			link.l1.go = "mangarosa_4";
		break;
		
		case "mangarosa_4":
			dialog.text = "年轻的猎鹰, 相信我, 你不需要这个。 别卷入其中, 这种植物会毁了你的。 它会使大脑迟钝, 让人发胖。 甚至别问我。 但是... 我面前是一个勇敢的人, 带着剑, 一个海上的男人... 也许还是个船长? ";
			link.l1 = "你说得对。 ";
			link.l1.go = "mangarosa_5";
		break;
		
		case "mangarosa_5":
			dialog.text = "那就听好了。 曼加罗莎可以用于更高尚的事情, 你可能会发现它很有用。 我们有一位治疗师知道它的所有秘密。 她就是你需要的人。 把植物给我, 我会告诉你她的名字和在哪里可以找到她。 不过说服她和你分享她的秘密将是你的问题。 ";
			link.l1 = "好的。 拿走植物, 告诉我怎么找到你们的吉普赛魔法师。 ";
			link.l1.go = "mangarosa_6";
		break;
		
		case "mangarosa_6":
			RemoveItems(pchar, "cannabis7", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "她叫阿梅莉亚。 她独自住在沙丘中的一所小房子里, 离海不远, 据智者说, 在西班牙大陆西南海岸的某个地方。 ";
			link.l1 = "哦, 看在上帝的份上, 你能说得更具体一点吗? ";
			link.l1.go = "mangarosa_7";
		break;
		
		case "mangarosa_7":
			dialog.text = "你是个水手, 勇敢的猎鹰, 而我不是。 在我所说的地方找她。 她的家离海岸很近。 就在西班牙大陆西南的一个海湾附近 - 水手们一定知道。 ";
			link.l1 = "好吧, 我会试着找到它... ";
			link.l1.go = "mangarosa_8";
		break;
		
		case "mangarosa_8":
			dialog.text = "给她带一株曼加罗莎, 否则她甚至不会和你说话。 也别忘了带杜布隆, 别以为她会免费教你! ";
			link.l1 = "如此贪婪。 我会考虑的。 谢谢你的故事! ";
			link.l1.go = "mangarosa_9";
		break;
		
		case "mangarosa_9":
			DialogExit();
			npchar.quest.mangarosa = "true";
			DeleteAttribute(pchar, "questTemp.Mangarosa.g_count");
			pchar.questTemp.Mangarosa = "amelia";
			pchar.questTemp.Mangarosa.Tell = "true"; // 治疗者
			AddQuestRecord("Mangarosa", "4");
			// 创建并放置阿梅莉亚
			sld = GetCharacter(NPC_GenerateCharacter("Amelia", "gipsy_3", "woman", "towngirl", 10, PIRATE, -1, true, "citizen"));
			SetFantomParamFromRank(sld, 10, true);
			sld.name = "阿梅莉亚";
			sld.lastname = "";
			sld.dialog.FileName = "Quest\Mangarosa.c";
			sld.dialog.currentnode = "amelia";
			//sld.greeting = "";
			LAi_SetOwnerType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Amelia_house", "barmen", "stay");
		break;
		
		// --> 黑暗之水治疗
		case "dwh_ne_ta":
			sld = CharacterFromID("DWH_gypsy");
			dialog.text = "不, " + GetSexPhrase("亲爱的", "美人") + ", 我不是你要找的人, 是" + sld.name + "。 她现在就在城里。 我最近见过她。 ";
			link.l1 = "谢谢你。 ";
			link.l1.go = "exit";
		break;
		// < —黑暗之水治疗
		
		// 市民类型角色对露出武器的评论
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "听我说, 勇敢的猎鹰, 我可能是个吉普赛人, 但即使是我们也谴责公开的暴力。 请把剑收起来。 ", "听我说, 勇敢的猎鹰, 作为这个城镇的市民, 我请求你把剑收起来。 ");
			link.l1 = LinkRandPhrase("好的。 ", "如你所愿。 ", "如你所说... ");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string GuessText()
{
	string sText;
	switch (hrand(19))
	{
		case 0: sText = "你会有好运的, 勇敢的年轻人, 明天你打牌会很幸运! "; break;
		case 1: sText = "命运会眷顾你的商业活动, 船长! "; break;
		case 2: sText = "公海上有不幸在等着你, 它就在那里等着你, 等三天! "; break;
		case 3: sText = "我看到你需要向最亲近的人寻求帮助, 下一场战斗你一个人应付不来! "; break;
		case 4: sText = "去教堂点支蜡烛吧, 你被敌人诅咒了。 没有上帝的帮助你撑不过去! "; break;
		case 5: sText = "我的猎鹰, 你很快会有很大的损失, 但不要绝望, 相信自己, 向朋友寻求帮助... "; break;
		case 6: sText = "海上有沉重的损失在等着你, 但我看到, 船长, 即使你得不到你想要的, 你也能挺过去。 "; break;
		case 7: sText = "船长, 你已经成为不幸的目标! 去妓院休息一下吧。 "; break;
		case 8: sText = "你会得到你想要的, 船长, 但别指望会有什么好结果。 你如此热切渴望的一切, 船长, 只会带来坏事, 所以你最好改变计划。 "; break;
		case 9: sText = "我看到你的脸上有一个标志, 终极幸运的标志。 你会得到比你期望更多的东西, 年轻人! "; break;
		case 10: sText = "你需要再次评估你的愿望并做出决定。 你真的需要它吗? 你的命运给了你重新思考的机会。 "; break;
		case 11: sText = "这是罕见的运气, 不是每天我们都有机会重新思考。 休息几天, 明眸的人, 想想事情。 别急着去送死! "; break;
		case 12: sText = "虽然你所有的努力都不会给你预期的结果, 但不要绝望, 年轻的猎鹰, 巨大的幸运在最意想不到的日子等着你, 不要错过它! "; break;
		case 13: sText = "你的问题不会以积极的方式解决, 但你是个固执的人, 你会得到你想要的, 但也许不是从你预期的地方。 "; break;
		case 14: sText = "你最好忘记你正在从事的事情。 在这件事上你永远不会幸运, 如果你继续下去, 也许你最亲近的人会受伤或被杀。 "; break;
		case 15: sText = "有一个事件在等着你, 船长, 它将彻底改变你的生活。 在那之后, 你最近的担忧对你来说将失去所有意义。 "; break;
		case 16: sText = "在你实现梦想的道路上有危险, 船长, 如果你能在不遭受重大损失的情况下得到你想要的, 那你一定非常幸运。 最好转身忘记你那无法实现的梦想。 或者, 也许, 如果你现在在牌局或骰子中输了, 这个命运可以被欺骗... "; break;
		case 17: sText = "我在你身上看到一种像岩石一样强大的力量, 以及像北极星一样明亮的光芒, 指引着人们。 好消息在等着你! "; break;
		case 18: sText = "一个坏兆头正在你的道路上升起, 提防邪恶之眼, 让忠诚的人留在你身边。 "; break;
		case 19: sText = "一个幸运的事件正在你的身后升起。 寻找即将到来的美好, 不要追逐无法实现的东西。 "; break;
	}
	return sText;
}
#include "DIALOGS\%language%\Rumours\Common_rumours.c" //Jason
// Jason 灯塔看守通用对话
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // 按城市调用对话 -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Lighthouse\" + NPChar.City + "_Lighthouse.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // 按城市调用对话 <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
    int iTest, iTemp;
	string sTemp;
	bool ok;
    iTest = FindColony(NPChar.City); // 城市
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("镇上拉起了警报。 看来我也该拿起武器了... ", "镇卫兵没在追你吧? ", "你在这儿找不到庇护所, 但可能在肋骨下找到几英寸冷钢! "), 
					LinkRandPhrase("你需要什么, " + GetSexPhrase("恶棍","无赖") + "? 卫兵在追踪你, 你跑不远的, " + GetSexPhrase("肮脏的海盗","臭家伙") + "! ", "" + GetSexPhrase("肮脏的","肮脏的") + "凶手! 卫兵!!! ", "我不怕你, " + GetSexPhrase("爬虫","臭家伙") + "! 很快你就会在我们的堡垒被吊死, 你跑不远的... "));
				link.l1 = PCharRepPhrase(RandPhraseSimple("看来你活腻了... ", "看来在" + XI_ConvertString("Colony" + npchar.city + "Gen") + "没有安分的人, 每个人都想当英雄! "), 
					RandPhraseSimple("去死吧! ", "呵, 这将是你生命的最后几秒... "));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			//belamour legendary edtion 加勒比习俗
			if(npchar.quest.meeting != "0" && CheckAttribute(npchar, "quest.trial_usurer"))
			{
				dialog.text = "这次是什么风把你吹来的? ";
				link.l1 = "我相信你认识一位叫热拉尔.勒克罗瓦的先生? 他应该给我留了份报酬... ";
				link.l1.go = "Trial";
				DelLandQuestMark(npchar);
				break;
			}
			// < —legendary edition
			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple("下午好, 水手! 我叫" + GetFullName(npchar) + ", 是这座灯塔的看守。 什么风把你吹到这儿来的? ", "你好! 距离上次在我灯塔见到新面孔已经很久了... 请允许我自我介绍 - " + GetFullName(npchar) + ", 这座灯塔是我的家和工作场所。 有什么能为你效劳的? ");
				link.l1 = "你好, " + npchar.name+ "! 我叫" +GetFullName(pchar)+ ", 是一名船长。 我在这片美丽的海湾散步, 决定顺道看看谁住在这里。 ";
				link.l1.go = "Lightman_meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "哦, 我的老朋友, " +GetFullName(pchar)+ "船长! 请进, 请进! 这次是什么风把你吹来的? ";
				link.l1 = "你好啊, 老水手! 你在这灯塔里不会孤单得哀嚎吧? ";
				link.l1.go = "Lightman_talk";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "Lightman_meeting":
			dialog.text = "现在你知道了。 我以前和你一样是水手, 但我最后一次踏上船甲板已经是很久以前的事了。 现在这座灯塔由我负责, 我也卖些东西... ";
			link.l1 = "你具体卖些什么? ";
			link.l1.go = "trade_info";
			NextDiag.TempNode = "First time";
		break;
		
		case "Lightman_talk":
			dialog.text = "这次是什么风把你吹来的? ";
			link.l1 = RandPhraseSimple("你能告诉我, 最近你的殖民地发生了什么有趣的事吗? ", "我很久没上岸了... 这里发生了什么? ");
			link.l1.go = "rumours_lighthouse";
			link.l2 = "让我看看你卖些什么。 ";
			link.l2.go = "Trade_lighthouse";
			if (CheckAttribute(npchar, "artefact"))
			{
				if (CheckAttribute(npchar, "quest.art"))
				{
					link.l3 = "那么, " + npchar.name+ ", 我的护身符到了吗? ";
					link.l3.go = "Trade_artefact_3";
				}
				else
				{
					link.l3 = "" + npchar.name+ ", 我想向你订购一个护身符。 ";
					link.l3.go = "Trade_artefact_1";
				}
				// 卡莱乌切
				if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "amulet" && !CheckAttribute(npchar, "quest.Caleuche"))
				{
					link.l5 = "听着, " + npchar.name+ ", 我知道你从事按订单运送护身符的生意。 所以你肯定对它们很了解。 请看一下这个小东西 - 你能告诉我什么? ";
					link.l5.go = "Caleuche";
				}
				if (npchar.id == pchar.questTemp.Caleuche.Amuletmaster && CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "mayak")
				{
					link.l5 = "朋友, 我又来问你关于那些奇怪护身符的事了";
					link.l5.go = "Caleuche_9";
				}
			}
			link.l4 = "有件事我想问你... ";
			link.l4.go = "quests";
			link.l9 = "我只是看看... ";
			link.l9.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "trade_info":
			dialog.text = "有时我去岸边收集贝壳, 附近有个漂亮的地方, 所以你可以随时从我这里买珍珠。 每场风暴都会带来琥珀, 我也卖这个, 虽然价格不菲。 \n有时海浪会从沉船上带来各种有趣的小饰品, 我的老伙计们也会给我带来特殊物品。 我对魔法护身符感兴趣, 智者会为它们出高价。 \n特殊情况下我也提供武器, 别问我从哪弄来的。 镇上的商人会买走我所有的破烂, 好东西我自己修理清洁后出售。 \n我对朗姆酒感兴趣。 我说的不是当地酒馆卖的两比索一杯的劣酒。 我说的是真正的瓶装牙买加朗姆酒。 它能治愈和复活人。 你带来的每瓶我都愿意出十倍的价格。 考虑一下。 ";
			link.l1 = "听着, " + npchar.name+ ", 你说你有老水手朋友, 他们给你带来魔法护身符。 我能向你订购特定的护身符吗? 我会出高价。 ";
			link.l1.go = "Trade_artefact";
		break;
		
		case "Trade_lighthouse":
			//有时售卖船用货物 // Addon-2016 Jason
			npchar.quest.goods = GOOD_COFFEE + hrand(sti(GOOD_PAPRIKA - GOOD_COFFEE));
			npchar.quest.goodsqty = 50+hrand(100);
			if (sti(npchar.quest.goods) == GOOD_EBONY || sti(npchar.quest.goods) == GOOD_MAHOGANY) npchar.quest.goodsqty = 25+hrand(50);
			npchar.quest.goodsprice = makeint(sti(Goods[sti(npchar.quest.goods)].Cost)/4);//单位商品价格
			npchar.quest.goodscost = sti(npchar.quest.goodsprice)*sti(npchar.quest.goodsqty);//商品总价
			ok = (!CheckAttribute(npchar, "goods_date")) || (GetNpcQuestPastDayParam(npchar, "goods_date") >= 10)
			if (hrand(4) == 1 && makeint(GetCharacterFreeSpace(pchar, sti(npchar.quest.goods))) > sti(npchar.quest.goodsqty) && sti(pchar.money) >= sti(npchar.quest.goodscost) && ok)
			{
				dialog.text = "船长, 最近有一批货物被冲上岸 - " + GetGoodsNameAlt(sti(npchar.quest.goods)) + "。 有些被盐水损坏了, 但" + FindRussianQtyString(sti(npchar.quest.goodsqty)) + "我设法完好保存了下来。 想买点吗? 我便宜卖, 每单位只要" + FindRussianMoneyString(sti(npchar.quest.goodsprice)) + "。 ";
				link.l1 = "不。 给我看看你最近的收藏。 ";
				link.l1.go = "Trade_lighthouse_double";
				link.l2 = "嗯... 诚邀, 我同意。 我想我可以转卖赚点利润。 让我看看... 总共是" + FindRussianMoneyString(sti(npchar.quest.goodscost)) + "。 对吗? ";
				link.l2.go = "Trade_goods";
				SaveCurrentNpcQuestDateParam(npchar, "goods_date");
			}
			else
			{
				DialogExit();
				if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
				{
					GiveItemToTrader(npchar);
					SaveCurrentNpcQuestDateParam(npchar, "trade_date");
				}
				LaunchItemsTrade(npchar, 0);
			}
		break;
		
		case "Trade_lighthouse_double":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
		case "Trade_goods":
			AddCharacterGoods(pchar, sti(npchar.quest.goods), sti(npchar.quest.goodsqty));
			AddMoneyToCharacter(pchar, -sti(npchar.quest.goodscost));
			AddMoneyToCharacter(npchar, sti(npchar.quest.goodscost));
			dialog.text = "你说得对, 船长。 一笔好交易! 我们都从中获利了... ";
			link.l1 = "好的。 我会派水手把货物送到我的船上。 现在给我看看你要卖的东西。 ";
			link.l1.go = "Trade_lighthouse_double";
		break;
//------------------------------------------------订购手工艺品------------------------------------------------
		case "Trade_artefact":
			if (CheckAttribute(npchar, "artefact")) // Addon-2016 Jason 用杜布隆
			{
				dialog.text = "嗯, 不是所有的, 但有些小饰品比其他的更常被带来, 所以我想我可以帮你。 但我警告你: 以这种方式订购的所有护身符都要花你100杜布隆。 你应该理解... ";
				link.l1 = "价格不是问题。 你能提供什么护身符? ";
				link.l1.go = "Trade_artefact_1";
				link.l2 = "呸! 那钱都能买艘船了。 太贵了。 我想我自己能行... ";
				link.l2.go = "exit_artefact";
			}
			else
			{
				dialog.text = "不, 船长。 这种东西纯粹是偶然发现的, 所以不可能提前订购。 而且你得等上比永远少一点的时间... ";
				link.l1 = "好吧, 如果是这样, 那就没什么可做的了。 ";
				link.l1.go = "exit_artefact";
			}
		break;
		
		case "exit_artefact":
			if (CheckAttribute(npchar, "artefact")) dialog.text = "如你所愿。 如果你改变主意, 就来找我。 ";
			else dialog.text = "船长, 想看看我今天卖什么吗? 如果没找到满意的, 过段时间再来 - 我可能有别的东西出售。 ";
			// belamour legendary edition 加勒比习俗 -->
			if(CheckAttribute(npchar, "quest.trial_usurer"))
			{
				link.l1 = "当然, 这些都很好, 但我想问的是 - 我想你认识一位叫热拉尔.勒克罗瓦的先生? 他应该给我留了份报酬... ";
				link.l1.go = "Trial";
				DelLandQuestMark(npchar);
				break;
			}
			// < —legendary edition
			link.l1 = "给我看看你的物品。 ";
			link.l1.go = "Trade_lighthouse";
			link.l2 = "只是告诉我, 你的殖民地最近发生了什么有趣的事? ";
			link.l2.go = "rumours_lighthouse";
			link.l3 = "买卖归买卖, 但我想问点事。 ";
			link.l3.go = "quests";
			link.l4 = "祝你愉快, " + npchar.name+ "! 很高兴见到你! 我改日再来... ";
			link.l4.go = "exit";
		break;
		
		case "Trade_artefact_1":
			dialog.text = "选一个吧。 ";
			iTemp = 1;
			string sArt;
			if (CheckAttribute(npchar, "artefact.indian")) sArt = "indian_";
			if (CheckAttribute(npchar, "artefact.amulet")) sArt = "amulet_";
			if (CheckAttribute(npchar, "artefact.obereg")) sArt = "obereg_";
			for (i=11; i>=1; i--)
			{
				sTemp = "l"+iTemp;
				link.(sTemp) = XI_ConvertString(sArt+i);
				link.(sTemp).go = sArt+i;
				iTemp++;
			}
			link.l12 = "遗憾的是, 目前这个列表里没有我感兴趣的。 ";
			link.l12.go = "exit";
		break;
		
		//indian组
		case "indian_1":
			dialog.text = "一个巫毒娃娃? 你喜欢火器? 很好... ";
			link.l1 = "我什么时候来取货? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_1";
		break;
		
		case "indian_2":
			dialog.text = "一个火药测试器? 任何小规模战斗中精准射击都是成功的关键。 不错... ";
			link.l1 = "我什么时候来取货? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_2";
		break;
		
		case "indian_3":
			dialog.text = "一把仪式刀? 你喜欢用沉重的阔剑有力地砍杀敌人? 那这个适合你。 很好... ";
			link.l1 = "我什么时候来取货? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_3";
		break;
		
		case "indian_4":
			dialog.text = "一把 长柄斧? 巨大斧头的自上而下的一击将粉碎任何敌人! 很好... ";
			link.l1 = "我什么时候来取货? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_4";
		break;
		
		case "indian_5":
			dialog.text = "一个 干缩头颅? 那东西甚至能吓跑最鲁莽的海盗。 很好... ";
			link.l1 = "我什么时候来取货? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_5";
		break;
		
		case "indian_6":
			dialog.text = "一个珊瑚头? 你大炮的葡萄弹将直飞目标! 很好... ";
			link.l1 = "我什么时候来取货? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_6";
		break;
		
		case "indian_7":
			dialog.text = "座头鲸? 不知疲倦是战士最好的朋友。 很好... ";
			link.l1 = "我什么时候来取货? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_7";
		break;
		
		case "indian_8":
			dialog.text = "修特库特利? 让敌舰的船体碎成尘埃! 很好... ";
			link.l1 = "我什么时候来取货? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_8";
		break;
		
		case "indian_9":
			dialog.text = "Baldo? 戴上Baldo - 所有炮弹都将直飞目标! 很好... ";
			link.l1 = "我什么时候来取货? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_9";
		break;
		
		case "indian_10":
			dialog.text = "卡斯卡维拉? 蛇的毒液是最危险的东西。 很好... ";
			link.l1 = "我什么时候来取货? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_10";
		break;
		
		case "indian_11":
			dialog.text = "恩戈姆博面具? 放下敌人的警惕, 哈哈哈! 很好... ";
			link.l1 = "我什么时候来取货? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_11";
		break;
		
		//amulet组
		case "amulet_1":
			dialog.text = "恩戈姆博盾牌? 如果你没能躲开子弹, 这个护身符可以救你一命。 很好... ";
			link.l1 = "我什么时候来取货? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_1";
		break;
		
		case "amulet_2":
			dialog.text = "圣礼书? 一个好的祈祷甚至可以让子弹转向。 很好... ";
			link.l1 = "我什么时候来取货? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_2";
		break;
		
		case "amulet_3":
			dialog.text = "一个十字架? 这个将极大地帮助基督徒在近距离战斗中。 很好... ";
			link.l1 = "我什么时候来取货? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_3";
		break;
		
		case "amulet_4":
			dialog.text = "埃尔特罗佐? 这会让致命伤变成擦伤。 很好... ";
			link.l1 = "我什么时候来取货? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_4";
		break;
		
		case "amulet_5":
			dialog.text = "索格博? 让大炮永远准备好战斗! 很好... ";
			link.l1 = "我什么时候来取货? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_5";
		break;
		
		case "amulet_6":
			dialog.text = "圣母像? 圣母的面容拥有强大的治愈能力。 很好... ";
			link.l1 = "我什么时候来取货? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_6";
		break;
		
		case "amulet_7":
			dialog.text = "圣水? 即使是弱者洒上圣水也会成为史诗英雄! 很好... ";
			link.l1 = "我什么时候来取货? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_7";
		break;
		
		case "amulet_8":
			dialog.text = "一个锚? 愿你的船即使在炮弹齐射下也能漂浮, 哈哈哈! 很好... ";
			link.l1 = "我什么时候来取货? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_8";
		break;
		
		case "amulet_9":
			dialog.text = "圣像勋章? 只要你拥有这个护身符, 你的帆就不怕风。 很好... ";
			link.l1 = "我什么时候来取货? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_9";
		break;
		
		case "amulet_10":
			dialog.text = "奇迹创造者? 愿主在陆地和海上都保佑你的船员! 很好... ";
			link.l1 = "我什么时候来取货? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_10";
		break;
		
		case "amulet_11":
			dialog.text = "Cimaruta? 火枪子弹将从你头顶飞过, 不会造成伤害! 很好... ";
			link.l1 = "我什么时候来取货? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_11";
		break;
		
		//obereg组
		case "obereg_1":
			dialog.text = "船蛆? 每个造船匠都梦想拥有那个。 很好... ";
			link.l1 = "我什么时候来取货? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_1";
		break;
		
		case "obereg_2":
			dialog.text = "索奇皮利? 那将节省缝补帆的时间。 很好... ";
			link.l1 = "我什么时候来取货? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_2";
		break;
		
		case "obereg_3":
			dialog.text = "一只猴子? 我想说, 像头驮骡! 很好... ";
			link.l1 = "我什么时候来取货? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_3";
		break;
		
		case "obereg_4":
			dialog.text = "吉普赛扇? 给巡逻者蒙上眼罩! 很好... ";
			link.l1 = "我什么时候来取货? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_4";
		break;
		
		case "obereg_5":
			dialog.text = "一个玉龟? 那是你牌局中的王牌! 很好... ";
			link.l1 = "我什么时候来取货? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_5";
		break;
		
		case "obereg_6":
			dialog.text = "一个水手结? 正如他们所说 - 让他们尊重你! 很好... ";
			link.l1 = "我什么时候来取货? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_6";
		break;
		
		case "obereg_7":
			dialog.text = "一个渔夫? 那是每个航海家的梦想。 很好... ";
			link.l1 = "我什么时候来取货? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_7";
		break;
		
		case "obereg_8":
			dialog.text = "商人的念珠? 钱喜欢被数, 不是吗? 很好... ";
			link.l1 = "我什么时候来取货? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_8";
		break;
		
		case "obereg_9":
			dialog.text = "埃赫卡特尔? 任何低速的旧船都会比风还快! 很好... ";
			link.l1 = "我什么时候来取货? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_9";
		break;
		
		case "obereg_10":
			dialog.text = "海员的耳环? 把那个给你的舵手! 很好... ";
			link.l1 = "我什么时候来取货? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_10";
		break;
		
		case "obereg_11":
			dialog.text = "朝圣者? 逆风变顺风。 很好... ";
			link.l1 = "我什么时候来取货? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_11";
		break;
		
		case "Trade_artefact_2":
			dialog.text = "两个月, 不早于。 我想那时他们会给我带来。 所以两个月后我等你带钱来。 ";
			link.l1 = "太好了! 我会来的! 谢谢你, " + npchar.name+ "! ";
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "art_date");
			npchar.quest.artday = rand(20)+50;
			sTemp = "Amulet_"+npchar.location;
			AddQuestRecord(sTemp, "1");
			ReOpenQuestHeader(sTemp);
			AddQuestUserData(sTemp, "sAml", XI_ConvertString(npchar.quest.art)); // dlc
		break;
		
		case "Trade_artefact_3":
			if (CheckAttribute(npchar, "art_date") && GetNpcQuestPastDayParam(npchar, "art_date") >= sti(npchar.quest.artday))
			{
			dialog.text = "是的, 我有。 你准备好100杜布隆了吗, 船长? "; // Addon-2016 Jason
				// belamour legendary edition -->
				if(PCharDublonsTotal() >= 100) 
				{
					link.l1 = "当然! 给你, 如约定。 ";
					link.l1.go = "Trade_artefact_4";
				}
				else
				{
					link.l1 = "哦, 我把钱忘在船上了! 我很快带来。 ";
					link.l1.go = "exit";
				}
				// < —legendary edition
			}
			else
			{
			dialog.text = "还没有。 过段时间再来。 别担心 - 你的护身符肯定会到的。 ";
			link.l1 = "好的。 ";
			link.l1.go = "exit";
			}
		break;
		
		case "Trade_artefact_4":
			RemoveDublonsFromPCharTotal(100); // Addon-2016 Jason
			Log_Info("你已支付100杜布隆");
			dialog.text = "一切似乎没问题。 这是你的护身符。 祝你好运! ";
			link.l1 = "谢谢你, " + npchar.name+ "! ";
			link.l1.go = "Trade_artefact_5";
		break;
		
		case "Trade_artefact_5":
			DialogExit();
			Log_Info("你已获得" + XI_ConvertString(npchar.quest.art) + "");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, npchar.quest.art, 1);
			DeleteAttribute(npchar, "quest.art");
			sTemp = "Amulet_"+npchar.location;
			AddQuestRecord(sTemp, "2");
			CloseQuestHeader(sTemp);
		break;
		
		// --> 卡莱乌切
		case "caleuche":
			PlaySound("interface\important_item.wav");
			dialog.text = "给我看看你那里的东西。 ";
			link.l1 = "给, 看起来像一个古老的印第安护身符。 但我不知道如何使用它或它的隐藏力量。 ";
			link.l1.go = "caleuche_1";
			npchar.quest.caleuche = "true";
		break;
		
		case "caleuche_1":
			if (npchar.id == pchar.questTemp.Caleuche.Amuletmaster)
			{
				dialog.text = "嗯嗯。 你是第三个给我看这种东西的人, 伙计。 这个护身符是从南美荒野带来的。 巴拿马附近有印第安人, 他们戴着像这样的小饰品。 红皮肤说这是他们‘伟大祖先’的遗产。 \n我不知道他们的祖先是谁或留下了什么遗产, 但我可以给你建议去哪里询问。 感兴趣吗? ";
				link.l1 = "当然! ";
				link.l1.go = "caleuche_2";
				DelLandQuestMark(npchar);
				if (npchar.id == "BasTer_Lightman") DelMapQuestMarkShore("Mayak4");
				if (npchar.id == "Santiago_Lightman") DelMapQuestMarkShore("Mayak9");
			}
			else
			{
				dialog.text = "嗯... 我手里拿过很多护身符, 但这个在加勒比还是第一次见到。 抱歉, 伙计, 我帮不了你; 我不了解这种东西。 但这不是简单的东西; 这是事实。 问问别人吧。 我确定还有其他像我这样的灯塔看守, 他们对护身符的了解不少。 ";
				link.l1 = "打扰了... 那我继续问问。 ";
				link.l1.go = "exit";
			}
		break;
		
		case "caleuche_2":
			dialog.text = "多米尼加有一个加勒比村庄, 当地酋长叫Moknitekuvri。 他们有一个叫Tuttuathapak的萨满, 是一位备受尊敬的印第安人。 他不是加勒比人; 他来自我已经告诉你的那个地方。 他能告诉你关于这个护身符的事比我多。 但要小心 - Tuttuathapak讨厌白人。 他真的很讨厌。 毕竟, 他们曾经奴役他并把他从家乡带走... ";
			link.l1 = "我猜他就是这样到加勒比的? ";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "是的。 这是一个很有趣的故事。 运载印第安奴隶的船在玛丽加朗特附近遭遇无风带, 一半船员死于突发高烧。 然而没有一个印第安人生病! \n后来船长发疯了, 放火烧了船。 结果被囚禁的印第安人发动叛乱, 屠杀了船员。 你猜谁是他们的领袖? ";
			link.l1 = "我猜... ";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "就是这样。 我打赌是萨满的咒语让大海风平浪静, 并让船员感染了致命疾病。 这个印第安人非常聪明且危险。 如果你去找他 - 举止礼貌, 注意言辞 - 否则你会有很多麻烦。 此外, 没有给他的祭品, 他甚至不会和你说话。 ";
			link.l1 = "他可能需要什么样的祭品? ";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "你不能用垃圾贿赂他。 据我所知, 他派加勒比士兵到白人定居点购买火器。 给他带一支滑膛枪作为礼物, 然后我想他会高兴并给你一点关注。 ";
			link.l1 = "谢谢你! 我会照你说的做... 说吧, 伙计, 你怎么知道这些的? ";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "我的朋友是那艘倒霉船上的水手。 幸运的是, 他在那场地狱中幸存下来... 我在他身上看到过一个像你这样的护身符, 似乎已故船长也抢了印第安人的财物。 我确定你的护身符来自他的收藏 - 当船长发疯放火烧船时, 他的水手杀了他, 然后抢劫了船舱里的箱子。 ";
			link.l1 = "明白了。 那我只需要带着礼物去多米尼加。 谢谢你的帮助和有趣的故事! ";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "祝你好运, 我的朋友, 小心那个红皮肤恶魔... ";
			link.l1 = "... ";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			DialogExit();
			AddQuestRecord("Caleuche", "2");
			pchar.questTemp.Caleuche = "dominica"; 
			Caleuche_CreateShamane();
		break;
		
		case "caleuche_9":
			dialog.text = "是吗? 你和Tuttuathapak谈过了, 对吗? ";
			link.l1 = "正是。 现在我想找到另外两个护身符。 你说我是第三个给你看这个神器的人。 另外两个是谁? ";
			link.l1.go = "caleuche_10";
			DelLandQuestMark(npchar);
		break;
		
		case "caleuche_10":
			dialog.text = "一个是我的朋友, 那艘把Tuttuathapak带到加勒比群岛的船上的水手。 自那次事件后, 他再也没踏上过任何船的甲板。 我有一段时间没见过他了, 但我知道他住在哪里。 去西大陆的伯利兹找他 - 他是个猎人, 现在在丛林里游荡。 名叫弗格斯.胡珀。 ";
			link.l1 = "好的。 第二个呢? ";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			dialog.text = "我对第二个只知道一点。 他叫杰克, 或杰克逊, 是私掠者, 或小商人, 或只是冒险家。 他拥有一艘名字奇怪的三桅小帆船... 嗯... 她的名字是... 该死, 我忘了! 但名字有点恶魔般的。 我问他是什么意思, 他说是海神像生的鸟女。 呸! 不信神的... ";
			link.l1 = "书呆子... 那你不记得她的名字了? ";
			link.l1.go = "caleuche_12";
		break;
		
		case "caleuche_12":
			dialog.text = "不, 我不记得了, 老天作证。 哦, 他自我介绍时提到他来自巴巴多斯。 ";
			link.l1 = "有点线索! 好的, 我会试着找到这个羽毛女爱好者, 直到被别人找到... 谢谢你, 伙计, 你帮了我很多! ";
			link.l1.go = "caleuche_13";
		break;
		
		case "caleuche_13":
			dialog.text = "不客气, 船长, 有空来坐坐。 ";
			link.l1 = "一定! ";
			link.l1.go = "caleuche_14";
		break;
		
		case "caleuche_14":
			DialogExit();
			AddQuestRecord("Caleuche", "7");
			pchar.questTemp.Caleuche = "hunting"; 
			pchar.questTemp.Caleuche.Belizterms = rand(4)+3;
			pchar.quest.caleuche_prepare_beliz.win_condition.l1 = "location";
			pchar.quest.caleuche_prepare_beliz.win_condition.l1.location = "Beliz";
			pchar.quest.caleuche_prepare_beliz.function = "Caleuche_PrepareBeliz";
			AddLandQuestMark(characterFromId("Bridgetown_Portman"), "questmarkmain");
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_SetOwnerType(NPChar); // belamour 否则永远生气		   
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Man_FackYou"://对试图打开箱子的反应
			dialog.text = LinkRandPhrase("你是" + GetSexPhrase("小偷, 亲爱的! 卫兵, 抓住他","小偷! 卫兵抓住她") + "!!! ", "哇! 我稍微看了一眼, 你就已经把头伸进箱子里了! 抓住小偷! ", "卫兵! 抢劫! 阻止小偷! ");
			link.l1 = "啊, 该死! ";
			link.l1.go = "fight";
		break;
		
		// belamour legendary edition 加勒比习俗
		case "Trial":
			dialog.text = "啊, 原来你就是那位船长! 是的, 我一直在等你。 热拉尔也在等, 但他需要紧急去参加某种探险, 所以他让我把报酬转给你。 他说你一定要来。 这里有90杜布隆, 请收下。 ";
			link.l1 = "谢谢你! 和诚实的人打交道真好。 ";
			link.l1.go = "Trial_1";
		break;
		
		case "Trial_1":
			DialogExit();
			TakeNItems(pchar, "gold_dublon", 90);
            NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar, "questTemp.Trial");
			DeleteAttribute(npchar, "quest.trial_usurer");
			pchar.questTemp.IslamonaSpaOfficer = true;
			CloseQuestHeader("Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		// <-- legendary edition
	}
}
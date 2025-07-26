// 矿场主对话
void ProcessDialogEvent()
{
	ref NPChar, sld, location;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		location = &Locations[FindLocation(pchar.location)];
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("你竟敢在这儿露面? ! 不知道你是勇敢还是愚蠢... ", "这些懒骨头怎么让敌人闯进我的住所? 真搞不懂... ", "显然我的守卫连一个子儿都不值, 如果这种混蛋能在这儿晃荡... "), 
					LinkRandPhrase("你想要什么, "+ GetSexPhrase("无赖","臭家伙") +"? ! 我的士兵已经在追捕你了, "+ GetSexPhrase(", 肮脏的海盗","") +"! ", "肮脏的杀人犯, 立刻离开我的住所! 卫兵! ", "我不怕你, "+ GetSexPhrase("老鼠","荡妇") +"! 很快你就会在我们的堡垒被绞死, 之后你就跑不了多远了... "));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("这些士兵连一个比索都不值... ", "他们永远抓不到我。 "), 
					RandPhraseSimple("闭上你的臭嘴, " + GetWorkTypeOfMan(npchar, "") + ", 否则我就撕掉你那脏舌头! ", "我建议你安静地坐着, 也许你还能活着挺过去... "));
				link.l1.go = "fight";
				break;
			}
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
				dialog.text = "矿场里有敌人! 警报! ";
				link.l1 = "啊哈, 魔鬼! ";
				link.l1.go = "fight"; 
				break;
			}	
			dialog.text = LinkRandPhrase(""+TimeGreeting()+", 先生。 我是"+GetFullName(npchar)+", 洛斯泰克斯矿场的采矿工程师。 你在这里有什么事吗? ","你好, 先生。 你想要什么? ","嗯... 你有什么事要找我吗, 先生? 我在听。 ");
			if (!CheckAttribute(location, "quest.info"))
			{
				link.l9 = "我是新来的, 想了解更多关于这个矿场的信息... ";
				link.l9.go = "info";
			}
			if (GetSquadronGoods(pchar, GOOD_SLAVES) > 4)
			{
				link.l2 = "我的船舱里有一批货物可能会让你感兴趣。 确切地说, 是给你矿场的奴隶。 想讨价还价吗? ";
				if (!CheckAttribute(location, "quest.slaves")) link.l2.go = "slaves_0";
				else link.l2.go = "slaves";
			}
			link.l1 = "我只是来打个招呼, 马上就走。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "info":
			dialog.text = "洛斯泰克斯矿场为西班牙王室开采黄金。 我们开采的一切都属于西班牙。 我们在这里不仅能找到黄金, 还能找到银块和珍贵的宝石。 我们这里不销售黄金, 开采的一切都在加强护卫下运往旧世界\n但对于金块和银块有两个例外。 第一, 你可以在我们当地的商店从军需官那里购买一些。 有时薪水不能及时送到, 所以我们必须在这里保留一些硬币储备以备这种情况, 这就是为什么允许当地交易\n第二, 我们一直需要人力, 所以我们用金块换奴隶。 因此, 如果你有什么要提供的, 就和我谈谈, 我们可以做生意\n我相信矿场的行为规则是显而易见的: 不要偷窃, 不要分散罪犯的注意力, 不要打扰士兵, 否则你不会喜欢后果的。 ";
			link.l1 = "好的, 谢谢! ";			
			link.l1.go = "exit";
			location.quest.info = "true";
		break;
		
		// 奴隶买卖生成器
		case "slaves_0":
			location.quest.slaves.qty = 200; // 初始需求量
			dialog.text = "当然, 先生! 你有多少? ";
			link.l1 = "我有"+FindRussianQtyString(GetSquadronGoods(pchar, GOOD_SLAVES))+"。 ";
			link.l1.go = "slaves_1";
		break;
		
		case "slaves":
			location.quest.slaves.qty = sti(location.quest.slaves.qty)+GetNpcQuestPastDayParam(location, "slave_date"); // 每天增加1点需求
			if (sti(location.quest.slaves.qty) > 350) location.quest.slaves.qty = 350; // 需求最大值
			if (sti(location.quest.slaves.qty) < 5)
			{
				dialog.text = "先生, 不幸的是, 目前我们不需要更多的奴隶了。 但情况随时可能改变, 所以过几周或其他时间再来看看。 ";
				link.l1 = "好的, 先生, 我明白。 你现在不需要, 但将来可能需要。 ";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "当然, 先生! 你有多少? ";
				link.l1 = "我有"+FindRussianQtyString(GetSquadronGoods(pchar, GOOD_SLAVES))+"。 ";
				link.l1.go = "slaves_1";
			}
		break;
		
		case "slaves_1":
			dialog.text = "每一个奴隶, 我愿意付给你一块金锭或两块银锭。 你选哪一种? ";
			link.l1 = "金锭。 ";
			link.l1.go = "slaves_g";
			link.l2 = "银锭。 ";
			link.l2.go = "slaves_s";
			link.l3 = "对不起, 先生, 但我刚改变主意了。 下次吧。 ";
			link.l3.go = "slaves_exit";
		break;
		
		case "slaves_g":
			location.quest.slaves.type = "gold";
			dialog.text = "好的。 你要卖给我多少奴隶? ";
			link.l1 = "";
			link.l1.edit = 6;
			link.l1.go = "slaves_trade";
		break;
		
		case "slaves_s":
			location.quest.slaves.type = "silver";
			dialog.text = "好的。 你要卖给我多少奴隶? ";
			link.l1 = "";
			link.l1.edit = 6;
			link.l1.go = "slaves_trade";
		break;
		
		case "slaves_trade":
			iTotalTemp = sti(dialogEditStrings[6]);
			if (iTotalTemp < 1)
			{
				dialog.text = "先生, 我没时间开愚蠢的玩笑。 如果你想开玩笑, 就去酒馆! ";
				link.l1 = "嗯... ";
				link.l1.go = "slaves_exit";
				break;
			}
			if (iTotalTemp > GetSquadronGoods(pchar, GOOD_SLAVES))
			{
				dialog.text = "先生, 我想你需要休息一下。 也许你很累或者中暑了。 去酒馆好好休息一下, 然后我们再继续讨价还价。 ";
				link.l1 = "嗯... ";
				link.l1.go = "slaves_exit";
				break;
			}
			if (iTotalTemp > sti(location.quest.slaves.qty))
			{
				dialog.text = "不幸的是, 先生, 目前我们不需要那么多奴隶。 矿场目前需要"+FindRussianQtyString(sti(location.quest.slaves.qty))+"。 你要卖那么多吗? ";
				link.l1 = "是的, 当然! ";
				link.l1.go = "slaves_max";
				link.l2 = "嗯... 我想不卖了。 ";
				link.l2.go = "slaves_exit";
				break;
			}
			dialog.text = ""+FindRussianQtyString(iTotalTemp)+"? 太好了。 请下令把他们带到城门。 我会派我的人去接他们。 ";
			link.l1 = "别担心, 先生。 你的奴隶会及时送到的。 我马上就下达所有相关命令。 ";
			link.l1.go = "slaves_calk";
		break;
		
		case "slaves_max":
			iTotalTemp = sti(location.quest.slaves.qty);
			dialog.text = "太好了。 请下令把他们带到城门。 我会派我的人去接他们。 ";
			link.l1 = "别担心, 先生。 你的奴隶会及时送到的。 我马上就下达所有相关命令。 ";
			link.l1.go = "slaves_calk";
		break;
		
		case "slaves_calk":
			DialogExit();
			Log_Info("奴隶换金锭的交易已完成");
			PlaySound("interface\important_item.wav");
			LAi_Fade("", "");
			WaitDate("",0,0,0,5,10);
			RemoveCharacterGoods(pchar, GOOD_SLAVES, iTotalTemp);
			if (location.quest.slaves.type == "gold") TakeNItems(pchar, "jewelry5", iTotalTemp);
			else TakeNItems(pchar, "jewelry6", iTotalTemp*2);
			DeleteAttribute(location, "slave_date");
			SaveCurrentNpcQuestDateParam(location, "slave_date");
			location.quest.slaves.qty = sti(location.quest.slaves.qty)-iTotalTemp;
		break;
		
		case "slaves_exit":
			DialogExit();
			DeleteAttribute(location, "slave_date");
			SaveCurrentNpcQuestDateParam(location, "slave_date");
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // 幻影士兵
			if (i != -1)
			{
				LAi_group_Attack(&Characters[i], Pchar);
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
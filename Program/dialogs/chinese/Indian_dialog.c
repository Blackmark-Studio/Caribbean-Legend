// 定居点印第安人对话
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "我们没什么好谈的! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		// ==> 定居点印第安人
		case "IndianMan":
			NextDiag.TempNode = "IndianMan";
			dialog.text = NPCStringReactionRepeat(""+ GetSexPhrase("白皮肤","白女人") +"想说话? ", 
				"又是你, " + GetSexPhrase("白皮肤","白女人") +"。 ", 
				"" + GetSexPhrase("白皮肤喜欢说话, 像个女人。 ","白女人喜欢说话。 ") +"",
                "神灵把我的白皮肤" + GetSexPhrase("兄弟","姐妹") +"带到了我面前。 ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("是的。 ", 
				"嗯, 又是我。 ",
                "很有诗意。 ", 
				"我也很高兴见到你。 ", npchar, Dialog.CurrentNode);
			link.l1.go = "IndPearlMan_1";
		break;
		
		case "IndPearlMan_1":
			dialog.text = "说吧, 白皮肤, 你来干什么? ";
			link.l1 = "哦, 没什么特别的, 只是想听听你要说什么... ";
			link.l1.go = "exit";
		break;
		
		case "IndianWoman":
			NextDiag.TempNode = "IndianWoman";
			dialog.text = NPCStringReactionRepeat("白人想说话? ", 
				"又是你, 白皮肤? ", 
				"白皮肤喜欢说话。 ",
                "神灵把我的白皮肤兄弟带到了我面前。 ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("是的。 ", 
				"嗯, 又是我。 ",
                "很有诗意。 ", 
				"我也很高兴见到你。 ", npchar, Dialog.CurrentNode);
			link.l1.go = "IndianWoman_1";
		break;
		
		case "IndianWoman_1":
			dialog.text = LinkRandPhrase(npchar.name+ "听你说, 海洋之子。 ", "你想从" + npchar.name+ "这里得到什么, 白皮肤? ", "我的耳朵为你的话语敞开, 陌生人。 ");
			if (CheckIndianGift() && !CheckAttribute(npchar, "quest.gift"))
			{
				link.l1 = LinkRandPhrase("我有东西给你。 想看看吗? ", "想看看真正有趣的东西吗? 你肯定会喜欢... ", "我有东西会让你高兴, 丛林之子。 想看看吗? ");
				link.l1.go = "gift";
			}
			link.l9 = "哦, 没什么特别的, 只是想听听你要说什么... ";
			link.l9.go = "exit";
		break;
		
		case "gift":
			iTemp = 2;
			dialog.text = RandPhraseSimple(npchar.name+ "想看看。 展示吧。 ", npchar.name+ "很感兴趣。 给我看。 ");
			if (CheckCharacterItem(pchar, "mineral6"))
			{
				link.l1 = "给一面镜子。 ";
				link.l1.go = "gift_1";
			}
			for (i=50; i>=47; i--)
			{
				if (CheckCharacterItem(pchar, "jewelry"+i))
				{
					sTemp = "l"+iTemp;
					link.(sTemp) = "给" + XI_ConvertString("jewelry"+i) + "。 ";
					link.(sTemp).go = "gift_"+i;
					iTemp++;				
				}
			}
		break;
		
		case "gift_1":
			RemoveItems(pchar, "mineral6", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "哦! 现在" + npchar.name+ "不仅可以在河水中看到自己了! 谢谢你, 善良的陌生人! ";
			link.l1 = "当然, 现在你可以尽情欣赏自己的容貌了... ";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_47":
			RemoveItems(pchar, "jewelry47", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "哦! 真漂亮! 这个手镯是给" + npchar.name+ "的? 谢谢你, 善良的陌生人! ";
			link.l1 = "戴在你黝黑的手上, 美人, 你会看起来棒极了... ";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_48":
			RemoveItems(pchar, "jewelry48", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "哦! 多漂亮的戒指? 是给" + npchar.name+ "的, 对吗? 谢谢你, 善良的陌生人! ";
			link.l1 = "戴在你的手指上, 所有朋友都会嫉妒... ";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_49":
			RemoveItems(pchar, "jewelry49", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "哦! 那些漂亮的绿色珠子是给" + npchar.name+ "的? 太美了! 谢谢你, 善良的陌生人! ";
			link.l1 = "用它们装饰你的脖子, 丛林的女儿。 每个人都会欣赏你... ";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_50":
			RemoveItems(pchar, "jewelry50", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "哦, 多漂亮的绿色戒指! 这是给" + npchar.name+ "的礼物? 谢谢你, 善良的陌生人! ";
			link.l1 = "戴在你手上会很好看, 美人... ";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_exit":
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Women")) // Addon 2016-1 Jason 海盗系列
			{
				dialog.text = "想问" + npchar.name+ "什么吗, 海洋之子? ";
				link.l1 = "你说得对, 美人。 我和我无畏的战士们要去丛林, 去山里的西班牙定居点, 我们在找向导。 我会慷慨对待他本人, 也会对待他的妻子。 我有很多财富: 漂亮的枪。 魔法眼镜。 镜子。 项链。 手镯和戒指。 也许你丈夫可以成为我们要找的向导? ";
				link.l1.go = "hayamee";
			}
			else
			{
				DialogExit();
			}
			ChangeIndianRelation(1.00);
			npchar.quest.gift = true;
		break;
		
		// Addon 2016-1 Jason 海盗系列
		// 库姆瓦纳, 洛科诺部落的酋长
		case "cumvana":
			dialog.text = "问候你, 海洋之子。 我是库姆瓦纳, 洛科诺部落龟族的酋长。 什么风把你吹到我的村庄来? ";
			if (GetCharacterFreeItem(pchar, "pistol5") > 0 || CheckCharacterItem(pchar, "compass1") || GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l1 = "我给你带来了礼物, 酋长。 看看吧, 你会喜欢的。 ";
				link.l1.go = "cumvana_2";
			}
			else 
			{
				link.l1 = "酋长, 我来请求你的帮助。 我想到达一个叫梅里达的西班牙定居点, 它位于你们丛林的群山之中, 问题是我不知道怎么去那里。 ";
				link.l1.go = "cumvana_no";
			}
			DelLandQuestMark(npchar);
		break;
		
		case "cumvana_no":
			dialog.text = "你不知道去那里的路, 这对你很好, 海洋之子。 它穿过一片森林, 那是无畏的卡蓬部落的土地。 他们是真正的美洲虎, 哦-哎! 我从未去过那个西班牙地方。 我的人民是和平的人民, 我们不去卡蓬的土地。 库姆瓦纳无法给你建议。 路途太危险了。 ";
			link.l1 = "但西班牙人找到了路! 而且我不怕那些卡蓬人... ";
			link.l1.go = "cumvana_no_1";
		break;
		
		case "cumvana_no_1":
			dialog.text = "但你应该怕。 他们是残忍的人。 他们在森林里杀了我很多族人。 库姆瓦纳已经说完了。 ";
			link.l1 = "好吧, 该死... ";
			link.l1.go = "cumvana_no_2";
		break;
		
		case "cumvana_no_2":
			DialogExit();
			AddQuestRecord("Roger_5", "5");
			npchar.dialog.currentnode = "cumvana_1";
		break;
		
		case "cumvana_1":
			dialog.text = "哦-哎! 又是你, 海洋之子。 你想对库姆瓦纳说什么? ";
			if (GetCharacterFreeItem(pchar, "pistol5") > 0 || CheckCharacterItem(pchar, "compass1") || GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l1 = "我给你带来了礼物, 酋长。 看看吧, 你会喜欢的。 ";
				link.l1.go = "cumvana_2";
			}
			else 
			{
				link.l1 = "我仍然希望找到梅里达... ";
				link.l1.go = "cumvana_1_1";
			}
		break;
		
		case "cumvana_1_1":
			DialogExit();
			npchar.dialog.currentnode = "cumvana_1";
		break;
		
		case "cumvana_2":
			dialog.text = "洛科诺总是很高兴见到好朋友。 ";
			if (GetCharacterFreeItem(pchar, "pistol5") > 0)
			{
				link.l1 = "赠送手枪。 "; // 5
				link.l1.go = "cumvana_2_1";
			}
			if (CheckCharacterItem(pchar, "compass1")) // 3
			{
				link.l2 = "赠送指南针。 ";
				link.l2.go = "cumvana_2_2";
			}
			if (GetCharacterFreeItem(pchar, "spyglass1") > 0)
			{
				link.l3 = "赠送便宜的望远镜。 ";
				link.l3.go = "cumvana_2_3";
			}
			if (GetCharacterFreeItem(pchar, "spyglass2") > 0)
			{
				link.l4 = "赠送普通望远镜。 "; // 2
				link.l4.go = "cumvana_2_4";
			}
			if (GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l5 = "赠送优质望远镜。 "; // 4
				link.l5.go = "cumvana_2_5";
			}
		break;
		
		case "cumvana_2_1":
			Log_Info("你赠送了一把手枪");
			//Log_Info("你获得了护身符");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "pistol5", 1);
			GiveItem2Character(pchar, "obereg_9");
			GiveItem2Character(pchar, "indian_7");
			GiveItem2Character(pchar, "obereg_3");
			dialog.text = "哦-哎! 多漂亮的白皮肤武器! 库姆瓦纳接受你的礼物! 你也接受库姆瓦纳和洛科诺人民的礼物, 海洋之子。 ";
			link.l1 = "感谢你, 酋长! ..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_2":
			Log_Info("你赠送了一个指南针");
			//Log_Info("你获得了护身符");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "compass1", 1);
			GiveItem2Character(pchar, "indian_10");
			GiveItem2Character(pchar, "indian_6");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = "哦-哎! 白皮肤的魔法护身符! 库姆瓦纳接受你的礼物! 你也接受库姆瓦纳和洛科诺人民的礼物, 海洋之子。 ";
			link.l1 = "感谢你, 酋长! ..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_3":
			Log_Info("你赠送了一个便宜的望远镜");
			//Log_Info("你获得了护身符");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass1", 1);
			GiveItem2Character(pchar, "obereg_2");
			GiveItem2Character(pchar, "indian_5");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = "哦-哎! 白皮肤的魔法管! 库姆瓦纳接受你的礼物! 你也接受库姆瓦纳和洛科诺人民的礼物, 海洋之子。 ";
			link.l1 = "感谢你, 酋长! ..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_4":
			Log_Info("你赠送了一个普通望远镜");
			//Log_Info("你获得了护身符");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass2", 1);
			GiveItem2Character(pchar, "obereg_6");
			GiveItem2Character(pchar, "indian_6");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = "哦-哎! 白皮肤的魔法管! 库姆瓦纳接受你的礼物! 你也接受库姆瓦纳和洛科诺人民的礼物, 海洋之子。 ";
			link.l1 = "感谢你, 酋长! ..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_5":
			Log_Info("你赠送了一个优质望远镜");
			//Log_Info("你获得了护身符");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass3", 1);
			GiveItem2Character(pchar, "obereg_9");
			GiveItem2Character(pchar, "indian_7");
			GiveItem2Character(pchar, "obereg_5");
			dialog.text = "哦-哎! 白皮肤的魔法管! 库姆瓦纳接受你的礼物! 你也接受库姆瓦纳和洛科诺人民的礼物, 海洋之子。 ";
			link.l1 = "感谢你, 酋长! ..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_3":
			dialog.text = "什么风把你吹到我们村庄来, 海洋之子? ";
			link.l1 = "酋长, 我来请求你的帮助。 我想到达一个叫梅里达的西班牙定居点, 它位于你们丛林的群山之中, 问题是我不知道怎么去那里。 也许你能给我派一个勇敢的战士, 给我们指路? ";
			link.l1.go = "cumvana_4";
		break;
		
		case "cumvana_4":
			dialog.text = "哦-哎! 路途危险, 非常危险。 去那里的路穿过一片森林, 那是无畏的卡蓬部落的土地。 他们是真正的美洲虎, 哦-哎! 我从未去过那个西班牙地方。 我的人民是和平的人民, 我们不去卡蓬的土地。 ";
			link.l1 = "我真的必须到达梅里达。 库姆瓦纳, 请问问你的人, 也许有人会同意加入我的队伍? 我的战士们经验丰富, 装备精良, 无所畏惧, 甚至不怕魔鬼。 我们会保护向导, 并在结束后慷慨奖励他。 ";
			link.l1.go = "cumvana_5";
		break;
		
		case "cumvana_5":
			dialog.text = "很好, 海洋之子。 我会召集一群战士, 告诉他们你的愿望。 明天黎明后再来见我。 ";
			link.l1 = "感谢你, 酋长! ";
			link.l1.go = "cumvana_6";
		break;
		
		case "cumvana_6":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_SetStayType(pchar);
			npchar.dialog.currentnode = "cumvana_7";
			//AddQuestRecord("Roger_5", "6");
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			SetLaunchFrameFormParam("第二天... ", "Mtraxx_MeridaVozhdDialog", 0, 4.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 1, 0, 0);
			RecalculateJumpTable();
		break;
		
		case "cumvana_7":
			dialog.text = "哦-哎! 又是你, 海洋之子。 你想对库姆瓦纳说什么? ";
			link.l1 = "暂时没什么, 酋长。 ";
			link.l1.go = "cumvana_7x";
			if(CheckAttribute(pchar,"questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "merida_hayamee")
			{
				link.l2 = "听着, 库姆瓦纳。 我和我的人真的需要过河到达那个该死的小镇。 让我解释这对我们有多重要。 ";
				link.l2.go = "cumvana_hard";
			}
		break;
		
		case "cumvana_hard":
			dialog.text = "我的猎人已经告诉你了... ";
			link.l1 = "没必要重复, 库姆瓦纳。 但看看外面 - 别高估你的能力。 我那些来这里寻找西班牙宝石的勇敢伙伴们现在分散在你的村庄里。 他们的耐心正在耗尽。 当耐心耗尽时会发生什么, 你最好不知道 - 相信我。 ";
			link.l1.go = "cumvana_medium_1";
			link.l2 = "闭嘴听着, 红皮肤的猿猴。 我的人比这些该死的卡蓬人可怕得多。 别被我们现在的善良欺骗。 我给你一个简单的选择: 要么在二十四小时内找到向导, 要么我们把你们都绑起来, 让你们在我们队伍前面穿过丛林。 如果你们带错路, 你们自己会在沼泽中灭亡, 或者被绑着去和卡蓬人战斗。 明白了吗? ";
			link.l2.go = "cumvana_hard_1";
			link.l3 = "库姆瓦纳, 我需要这个向导。 我们走了很长的路, 我真的不想告诉我的人这是徒劳的。 ";
			link.l3.go = "cumvana_good_1";
			pchar.questTemp.Mtraxx_MeridaZapugivanieIndeets = true;
		break;
		
		case "cumvana_good_1":
			dialog.text = "库姆瓦纳已经说过, 没有洛科诺人想和白皮肤一起去。 ";
			link.l1 = "你就不能做点什么吗? 亲自问问。 毕竟你是酋长, 不是吗? ";
			link.l1.go = "cumvana_good_2";
		break;
		
		case "cumvana_good_2":
			dialog.text = "酋长不强迫印第安人。 酋长统治并希望他的人民和平。 印第安人知道 - 卡蓬人会看到洛科诺人带白皮肤来。 他们的头会被卡奈马抓走。 他们会来报复洛科诺人。 卡蓬人会杀人。 抓走洛科诺人, 让他们成为奴隶。 ";
			link.l1 = "谁抓走了你们的头? 什么灵魂或恶魔让印第安人变成如此懦弱的蛆虫? 好吧, 也许我真的不得不放弃对梅里达的行动。 但记住, 酋长。 每当有人问我对洛科诺人的看法时, 我总会回答 - 他们是一个毫无价值的懦夫部落。 由一个像他们一样懦弱和短视的统治者领导, 他的脸一想起卡蓬人就会因恐惧而扭曲。 你不会在印第安人中获得荣耀, 也不会在我们白皮肤中获得尊重。 ";
			link.l1.go = "cumvana_good_3";
		break;
		
		case "cumvana_good_3":
			dialog.text = "白皮肤不知道印第安人的习俗... ";
			link.l1 = "我知道的足够多, 知道印第安人叫谁懦夫, 叫谁勇敢的战士。 再见, 库姆瓦纳。 记住我的话。 你是一个懦弱和短视的统治者。 ";
			link.l1.go = "cumvana_good_4";
		break;
		
		case "cumvana_good_4":
			DialogExit();
			ChangeIndianRelation(5.00);
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Women")) DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			pchar.questTemp.Mtraxx = "fail";
			
			pchar.quest.Mtraxx_MeridaHayameeGoodDialog.win_condition.l1 = "location";
			pchar.quest.Mtraxx_MeridaHayameeGoodDialog.win_condition.l1.location = "Locono_village";
			pchar.quest.Mtraxx_MeridaHayameeGoodDialog.function = "Mtraxx_MeridaHayameeGoodDialog";
		break;
		
		case "cumvana_medium_1":
			dialog.text = "为什么要这样威胁我? 我们认为你是好人... ";
			link.l1 = "只要你合作, 我就是好人, 明白吗? 你有一天时间。 相信我, 我的人会做我命令的任何事。 我们更强壮。 如果你怀疑... 我见过你的妻子和女儿。 我想你现在明白了。 ";
			link.l1.go = "cumvana_hard_2";
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;
		
		case "cumvana_hard_1":
			dialog.text = "为什么要这样威胁我? 我们认为你是好人... ";
			link.l1 = "只要你合作, 我就是好人, 明白吗? 你有一天时间。 相信我, 我的人会做我命令的任何事。 我们更强壮。 如果你怀疑... 我见过你的妻子和女儿。 我想你现在明白了。 ";
			link.l1.go = "cumvana_hard_2";
		break;
		
		case "cumvana_hard_2":
			dialog.text = "库姆瓦纳明白了, 白皮肤。 村子里有个叫塔戈法的猎人。 也许他可以带你到定居点... ";
			link.l1 = "我二十四小时后回来。 查理.普林斯没什么可说的了, 野蛮人。 ";
			link.l1.go = "cumvana_hard_3";
		break;
		
		case "cumvana_hard_3":
			DialogExit();
			ref Hayam = characterFromId("Hayamee");
			ChangeCharacterAddressGroup(Hayam, "none", "", "");
			Hayam.lifeday = 0;
			pchar.questTemp.Mtraxx = "merida_hayamee_hard";
			npchar.dialog.currentnode = "cumvana_7";
			SetFunctionTimerCondition("Mtraxx_MeridaHayameeHardTagofaWait", 0, 0, 1, false);
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Women")) DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			ChangeCharacterComplexReputation(pchar, "nobility", -80);
			ChangeOfficersLoyality("bad", 5);
			ChangeIndianRelation(-50.0);
			//log_Info("印第安人的态度下降了");
			AddQuestRecord("Roger_5", "8a");
			pchar.GenQuest.CannotWait = true; // 禁止休息
			
			pchar.quest.Mtraxx_MeridaHayameeHardLepriconDialog.win_condition.l1 = "location";
			pchar.quest.Mtraxx_MeridaHayameeHardLepriconDialog.win_condition.l1.location = "Locono_village";
			pchar.quest.Mtraxx_MeridaHayameeHardLepriconDialog.function = "Mtraxx_MeridaHayameeHardLepriconDialog";
		break;
		
		case "cumvana_7x":
			DialogExit();
			npchar.dialog.currentnode = "cumvana_7";
		break;
		
		case "cumvana_8":
			dialog.text = "海洋之子, 是你。 库姆瓦纳和洛科诺的战士们谈过了。 ";
			link.l1 = "然后呢? 有志愿者吗? ";
			link.l1.go = "cumvana_9";
		break;
		
		case "cumvana_9":
			dialog.text = "我们周围有几个猎人去过那里。 但他们害怕卡蓬人, 这些美洲虎正在开战。 他们说卡蓬人会杀了你的队伍, 所以他们不去。 他们不怕白皮肤。 ";
			link.l1 = "我的战士比他们任何一个都强! 我的部分队员在丛林里度过了一生! 我们不是业余爱好者! ";
			link.l1.go = "cumvana_10";
		break;
		
		case "cumvana_10":
			dialog.text = "对不起, 海洋之子。 我的猎人害怕, 卡蓬人很危险, 非常非常危险。 ";
			link.l1 = "好吧, 也许他们可以解释怎么去那里? 详细地说。 ";
			link.l1.go = "cumvana_11";
		break;
		
		case "cumvana_11":
			dialog.text = "要到达那里, 你应该在河上航行, 然后在特定的地方下船。 如果地方不对, 你会陷入沼泽并死亡。 我们的丛林充满危险。 你自己找不到地方, 海洋之子。 ";
			link.l1 = RandSwear() + "那我该怎么办? 如何说服你的猎人? ";
			link.l1.go = "cumvana_12";
		break;
		
		case "cumvana_12":
			dialog.text = "库姆瓦纳不再说了, 海洋之子。 ";
			link.l1 = "好吧... ";
			link.l1.go = "cumvana_13";
		break;
		
		case "cumvana_13":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetPlayerType(pchar);
			npchar.dialog.currentnode = "cumvana_7";
			AddQuestRecord("Roger_5", "7");
			pchar.questTemp.Mtraxx = "merida_advice";
			LAi_SetHuberType(npchar);
			AddLandQuestMark(characterFromId("Lepricon"), "questmarkmain");
		break;
		
		// 海雅米
		case "hayamee":
			if (npchar.id == "Hayamee")
			{
				dialog.text = "我丈夫塔戈法是部落里最好的猎人。 哦-哎! " + npchar.name+ "为丈夫感到骄傲。 " + npchar.name+ "经常和塔戈法一起去丛林。 走得很远。 塔戈法知道西班牙定居点在哪里。 ";
				if (IsCharacterPerkOn(pchar, "Trustworthy") && stf(pchar.questTemp.Indian.relation) >= 40.0)
				{
					link.l1 = "塔戈法知道去西班牙人称为梅里达的城市的路吗? ";
					link.l1.go = "hayamee_1";
				}
				else
				{
					link.l1 = "嗯, 嗯... 塔戈法知道怎么去西班牙城市吗? ";
					link.l1.go = "hayamee_bad_1";
				}
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple("我丈夫不去丛林, 海洋之子。 他捕鱼。 是个好渔夫, 哦-哎! ", "我丈夫是个好猎人, 哦-哎, 但他不深入丛林。 "), RandPhraseSimple("美洲虎在狩猎中伤了我丈夫。 现在他坐在村子里, 制作箭头, 哦-哎! ", "六个月前, 三个卡蓬人袭击了我丈夫。 现在他不离开村子太远去打猎。 再也不! 哦-哎! "));
				link.l1 = LinkRandPhrase("可惜... ", "太糟了... ", "真遗憾... "));
				link.l1.go = "exit";
			}
		break;
		
		case "hayamee_bad_1":
			dialog.text = "塔戈法在这片丛林中长大。 他知道周围的每一棵树和每一块石头! ";
			link.l1 = "如果他带我们去那里, 我会给你和塔戈法很多礼物。 珠宝。 武器, 任何东西。 任何你想要的。 当然, 在合理范围内, 呵呵。 我怎么和你丈夫谈谈? ";
			link.l1.go = "hayamee_bad_2";
		break;
		
		case "hayamee_bad_2":
			dialog.text = "塔戈法不会和白皮肤一起去。 塔戈法会留在村子里。 去打猎。 不与卡蓬人战斗。 ";
			link.l1 = "他不必与卡蓬人战斗。 只要他看到他们, 就可以躲起来。 只有我的人会战斗。 ";
			link.l1.go = "hayamee_bad_3";
		break;
		
		case "hayamee_bad_3":
			dialog.text = "不, 亚拉瑙伊。 白皮肤从不遵守诺言。 白皮肤说话 - 话语立即飞入虚空。 卡蓬人会杀了塔戈法, 然后来到我们的村庄, 杀死洛科诺人。 ";
			link.l1 = "你认为这些卡蓬人是你唯一需要担心的吗? 你大错特错了... ";
			link.l1.go = "hayamee_bad_4";
			if (stf(pchar.questTemp.Indian.relation) < 40.0) notification("印第安人不尊重你 " + stf(pchar.questTemp.Indian.relation) + "/40", "None");
			if (!IsCharacterPerkOn(pchar, "Trustworthy")) notification("特质检查失败", "Trustworthy");
		break;
		
		case "hayamee_bad_4":
			dialog.text = "雅哈胡进入白皮肤! 海雅米不再和亚拉瑙伊说话。 ";
			link.l1 = "好吧-好吧... ";
			link.l1.go = "hayamee_bad_5";
		break;
		
		case "hayamee_bad_5":
			DialogExit();
			pchar.questTemp.Mtraxx = "merida_hayamee";
			DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			LAi_CharacterDisableDialog(npchar);
		break;
		case "hayamee_1":
			dialog.text = "塔戈法一天前去打猎了。 答应明天太阳落山时回来。 明天来吧, 海洋之子, 我会和塔戈法在那间小屋里, 你走进村子时向右走。 我会问他是否和你一起去。 ";
			link.l1 = "告诉塔戈法我会送他最漂亮的手枪。 而你, 我会送很多珠宝。 ";
link.l1.go = "hayamee_1_1";
		break;
		
		case "hayamee_1_1":
			dialog.text = "洛科诺人不信任雅拉瑙伊。 雅拉瑙伊欺骗印第安人, 让印第安人成为奴隶。 但洛科诺人听说了你的名字, 白皮肤。 我信任你。 明天日落后来吧, 海洋之子。 我会和塔戈法在那间小屋里。 我会问他是否和你一起去。 ";
			link.l1 = "告诉塔戈法我会给他我最漂亮的手枪。 给你我有很多珠宝。 ";
			link.l1.go = "hayamee_2";
			notification("印第安人尊重你 " + stf(pchar.questTemp.Indian.relation) + "/40", "None");
			notification("可信赖", "Trustworthy");
		break;
		
		case "hayamee_2":
			dialog.text = "哦-哎! ";
			link.l1 = "... ";
			link.l1.go = "hayamee_3";
		break;
		
		case "hayamee_3":
			DialogExit();
			AddQuestRecord("Roger_5", "9");
			DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			LAi_CharacterDisableDialog(npchar);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.hour  = 22.0;
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.function = "Mtraxx_MeridaHayameeTimer";
		break;
		
		case "hayamee_4":
			pchar.quest.Mtraxx_MeridaPotionLate.over = "yes";
			dialog.text = "" + npchar.name+ "很高兴见到海洋之子。 塔戈法回来了。 但他喝了太多卡西里酒, 睡着了。 别叫醒他, 塔戈法在休息。 我来谈谈。 ";
			link.l1 = "很好, " + npchar.name+ "。 你丈夫会带我们去梅里达吗? ";
			link.l1.go = "hayamee_5";
		break;
		
		case "hayamee_5":
			dialog.text = "塔戈法同意带领你的战士穿过丛林到西班牙村庄。 但有条件... ";
			link.l1 = "什么条件? ";
			link.l1.go = "hayamee_6";
		break;
		
		case "hayamee_6":
			dialog.text = "你要保护塔戈法免受卡蓬战士的伤害。 塔戈法不与西班牙人或卡蓬人战斗。 如果他面临危险, 他会逃跑, 没人能找到他, 他是最好的洛科诺猎人。 ";
			link.l1 = "我明白。 你担心你的男人, 这可以理解。 我向你保证, 我们会自己处理所有那些卡蓬人。 ";
			link.l1.go = "hayamee_7";
		break;
		
		case "hayamee_7":
			dialog.text = "哦-哎! 塔戈法想要海洋之子的礼物: 一把可以发射许多子弹的小手枪和一把发射一颗子弹的大手枪, 要漂亮的。 还要每把枪的子弹: 双手手指数量的三倍。 ";
			link.l1 = "哇! 你男人懂枪, 嗯? 很好。 还有什么? ";
			link.l1.go = "hayamee_8";
		break;
		
		case "hayamee_8":
			dialog.text = "塔戈法还想要一个漂亮的白皮肤魔法眼睛。 ";
			link.l1 = "一个望远镜? 好的。 还有什么? ";
			link.l1.go = "hayamee_9";
		break;
		
		case "hayamee_9":
			dialog.text = "塔戈法没有其他要求了。 " + npchar.name+ "想要漂亮的东西。 带大红宝石的金戒指, 和许多绿色石头的珠子。 " + npchar.name+ "在马拉开波的白玛丽身上见过。 ";
			link.l1 = "带红宝石的金戒指和玉珠? ";
			link.l1.go = "hayamee_10";
		break;
		
		case "hayamee_10":
			dialog.text = "不是玉。 它是闪亮的, 白人很看重它。 ";
			link.l1 = "祖母绿? 祖母绿珠子? ";
			link.l1.go = "hayamee_11";
		break;
		
		case "hayamee_11":
			dialog.text = "哦-哎! ";
			link.l1 = "呵, " + npchar.name+ "懂珠宝! 很好, 你会得到的。 ";
			link.l1.go = "hayamee_12";
		break;
		
		case "hayamee_12":
			dialog.text = "把" + npchar.name+ "和塔戈法要的东西一起带来, 海洋之子。 然后塔戈法会带领你和你的战士。 不要浪费时间, 半个月后塔戈法和我会去邻村。 参加一个重要的节日。 现在走吧, " + npchar.name+ "想睡觉了。 ";
			link.l1 = "我不会让你等太久的。 再见。 ";
			link.l1.go = "hayamee_13";
		break;
		
		case "hayamee_13":
			DialogExit();
			AddQuestRecord("Roger_5", "10");
			LAi_CharacterDisableDialog(npchar);
			SetFunctionTimerCondition("Mtraxx_MeridaHayameeLate", 0, 0, 15, false); // 定时器
			// 塔戈法处于坐下状态
			pchar.quest.mtraxx_merida_wait2.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.hour  = 9.0;
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.function = "Mtraxx_MeridaTagofaHide";
		break;
		
		case "hayamee_14":
			bOk = GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0;
			dialog.text = "你带来了" + npchar.name+ "和塔戈法要的东西吗? ";
			if (bOk && GetCharacterFreeItem(pchar, "pistol3") > 0 && GetCharacterFreeItem(pchar, "pistol5") > 0 && GetCharacterItem(pchar, "bullet") >= 30 && GetCharacterItem(pchar, "grapeshot") >= 30 && GetCharacterItem(pchar, "gunpowder") >= 60 && CheckCharacterItem(pchar, "jewelry41") && CheckCharacterItem(pchar, "jewelry42"))
			{
				link.l1 = "是的。 一切按你的清单。 ";
				link.l1.go = "hayamee_15";
			}
			else
			{
				link.l1 = "没有, 我还在准备。 ";
				link.l1.go = "hayamee_14x";
			}
		break;
		
		case "hayamee_14x":
			DialogExit();
			npchar.dialog.currentnode = "hayamee_14";
		break;
		
		case "hayamee_15":
			pchar.quest.Mtraxx_MeridaHayameeLate.over = "yes";
			Mtraxx_MeridaRemoveGifts();
			dialog.text = "" + npchar.name+ "很高兴, 海洋之子。 我现在叫丈夫。 他和你一起去。 但记住你对" + npchar.name+ "的承诺! ";
			link.l1 = "是-是, 我什么都记得。 我会保护他, 别担心。 ";
			link.l1.go = "hayamee_16";
		break;
		
		case "hayamee_16":
			DialogExit();
			pchar.questTemp.Mtraxx = "merida_hayamee_peace";
			chrDisableReloadToLocation = true;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 7.0);
			DoQuestFunctionDelay("Mtraxx_MeridaTagofaEnter", 20.0);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
			
		case "CitizenNotBlade":
			dialog.text = "收起你的武器, 白皮肤, 否则我们会强迫你这么做! ";
			link.l1 = LinkRandPhrase("好的。 ", "好的。 ", "别担心, 我正在收起来... ");
			link.l1.go = "exit";
		break;  

	}
}
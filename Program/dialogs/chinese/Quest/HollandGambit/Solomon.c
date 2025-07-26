// 所罗门.施努尔 - 老犹太人
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
//--------------------------------------前往荷兰------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
				if (pchar.questTemp.HWIC.Holl == "AbbyFather")
				{
					dialog.text = "年轻人, 你想从这个老犹太人这里得到什么? ";
					link.l1 = "所罗门, 我需要你仔细回想一下你遭遇海难的那个失落岛屿。 你在那里藏了一批宝藏。 我和你女儿谈过了。 我的老板卢卡斯.罗登堡授权我为了你们家族的利益行事。 在我看来, 目前对你最重要的是找回家族的资产, 而没有我的帮助, 你连那些金子的影子都摸不到。 ";
					link.l1.go = "SolomonBonanza";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "AbbyFindScull" && makeint(Pchar.money) >= 200000)
				{
					dialog.text = "哦, 年轻人, 是你吗? 你不能告诉我点好消息吗? 你们基督徒又来折磨这个可怜的老犹太人, 问东问西了? ";
					if (CheckCharacterItem(pchar, "SkullAztec"))
					{
						link.l1 = "我找到了那个岛, 虽然过程相当艰难。 我还找到了你装钱的箱子和这个头骨。 我猜这就是你一直说的你祖父族长的头骨吧。 ";
						link.l1.go = "SolomonBonanza_2";
					}
					link.l2 = "我找到了那个岛, 虽然并不容易。 我也找到了你装钱的箱子。 但箱子里没有头骨。 ";
					link.l2.go = "SolomonBonanza_3";
					link.l3 = "不, 我现在没有问题要问。 ";
					link.l3.go = "exit";
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "GiveLucasMoney" && GetQuestPastDayParam("questTemp.HWIC.Holl.LucasMoney") > 7)
				{
					dialog.text = "哦, 年轻人, 是你吗? 你能告诉我点好消息吗? 还是又来折磨这个可怜的老犹太人, 问东问西? ";
					link.l1 = "我找到了那个岛, 虽然过程相当艰难。 我还找到了你装钱的箱子。 给你。 ";
					link.l1.go = "SolomonBonanza_5";
					break;
				}
				dialog.text = "你好, 年轻人。 你想从这个可怜的老犹太人这里得到什么? ";
				link.l1 = "下午好。 不, 没什么, 我只是来打个招呼。 ";
				link.l1.go = "exit";
				break;
			}
//----------------------------------------前往英国-----------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				if (pchar.questTemp.HWIC.Eng == "toAbigile")
				{
					dialog.text = "下午好, 年轻人。 我看你是有目的而来... 你想要什么? 我能从中得到什么吗, 还是我漏掉了什么? ";
					link.l1 = "下午好, 所罗门。 我想和阿比盖尔谈谈。 ";
					link.l1.go = "Solomon_treasure";
					DelLandQuestMark(npchar);
					break;
				}
				dialog.text = "你好, 年轻人。 你想从这个可怜的老犹太人这里得到什么? ";
				link.l1 = "下午好, 所罗门。 没什么, 我只是来打个招呼。 ";
				link.l1.go = "exit";
				break;
			}
//-----------------------------------------对抗所有人-------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "toVillemstad")
				{
					dialog.text = "下午好, 年轻人。 我看你是有目的而来... 你想要什么? 我能从中得到什么吗, 还是我漏掉了什么? ";
					link.l1 = "我需要和阿比盖尔谈谈。 我有封信给她。 ";
					link.l1.go = "Abigile_kidnap";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileNextDayOver")
				{
					dialog.text = "你好, 年轻人。 你想要什么? 又给我女儿带信? ";
					link.l1 = "不。 阿比盖尔在哪里? ";
					link.l1.go = "Abigile_GoOver";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistory")
				{
					dialog.text = "唉... 年轻人, 你是在说我的钱吗? ";
					link.l1 = "是的, 先生。 关于你藏在某个岛上的钱。 你和阿比盖尔真的不记得位置了吗? ";
					link.l1.go = "Solomon_history";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistoryAfter")
				{
					dialog.text = "好吧。 我记得那艘快速帆船和它的船长。 我以前在阿姆斯特丹甚至见过他一次。 那艘快速帆船叫‘莱顿’, 船长叫托夫.凯勒。 ";
					link.l1 = "这是个开始! 我现在有线索了。 ";
					link.l1.go = "Solomon_history_3";
					pchar.questTemp.HWIC.Self = "SolomonHistoryEnd";
					break;
				}
				dialog.text = "哎呀, 这次你想从这个可怜的老犹太人这里得到什么? ";
				link.l1 = "下午好。 不, 没什么, 我只是来打个招呼。 ";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "哎呀, 这次你想从这个可怜的老犹太人这里得到什么? ";
			link.l1 = "下午好。 不, 没什么, 我只是来打个招呼。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

//-----------------------------------------------前往荷兰-----------------------------------
		case "SolomonBonanza":
			PlaySound("Voice\English\hambit\Solomon Shneur-03.wav");
			dialog.text = "你想从我这里得到什么? 你觉得我像知道什么的人吗? 我怎么会知道在那样一个天谴之日, 到底哪里有一块土地, 上面有现成的货物和金子? 你想想, 街上那些外邦人, 有多少想骗过我这样的犹太人, 把我的钱拿走! \n有一个岛。 除了我和阿比, 那里一个人都没有。 一个人都没有。 完全没有人。 岛中间有个洞穴。 我把箱子放在那里, 免得被那些海盗外邦人阿梅莱克抢走! 箱子里装满了金子, 没有一件破烂! 我从旧大陆一路拖着它! 我血汗挣来的一切都在里面。 还有我祖父的头骨... 相信我, 那东西救了我们, 是的是的\n哦吼吼, 那是一个充满塔木德魔法的古老护身符! 上帝保佑我们远离阿梅莱克! 哎呀, 在这个外邦人的时代重新开始太难了! 年轻人, 你要是知道就好了! 哦, 你要是知道就好了! ";
			link.l1 = "你到底在胡扯什么, 你这个疯子? 谁在乎。 我自己处理。 再见! ";
			link.l1.go = "SolomonBonanza_1";
		break;
		
		case "SolomonBonanza_1":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "AbbySeekIsland";
			pchar.quest.Joakim_meeteng.win_condition.l1 = "location";
			pchar.quest.Joakim_meeteng.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Joakim_meeteng.function = "Create_Joakim";
		break;
		
		case "SolomonBonanza_2"://归还所有物品
			dialog.text = "哦, 上帝存在, 你是个真正的好人! 你不仅带回了我的金子, 还挽回了施努尔家族的名誉! 你避免了多大的耻辱啊! 罗登堡先生可以自豪地拥有你这样的船长。 我会把这个头骨交给罗登堡先生, 他答应为此支付一大笔钱。 我想亲自感谢你, 你是个善良的外邦人 --请接受这个护身符, 作为这个犹太人的一点心意。 ";
			link.l1 = "呃, 我想谢谢你。 ";
			link.l1.go = "SolomonBonanza_4";
			RemoveItems(PChar, "SkullAztec", 1);
			AddMoneyToCharacter(pchar, -200000);
			GiveItem2Character(pchar, "amulet_7"); 
			AddDialogExitQuestFunction("DeleteJoakimFromRoom");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			SetFunctionTimerCondition("Caleuche_StartTotal", 0, 0, 180, false); // 卡勒幽船的计时器
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Joakim"));
			pchar.questTemp.Caleuche.SolomonSkul = true;
		break;
		
		case "SolomonBonanza_3":
			dialog.text = "哦, 上帝存在, 你是个真正的好人! 你不仅带回了我的金子, 还挽回了施努尔家族的名誉! 你避免了多大的耻辱啊! 至于头骨 --哦, 好吧, 没关系, 他本来就是个疯疯癫癫的混蛋! 罗登堡先生可以自豪地拥有你这样的船长。 我想亲自感谢你, 你是个善良的外邦人 --请接受这个护身符作为纪念。 ";
			link.l1 = "呃, 我想谢谢你。 ";
			link.l1.go = "SolomonBonanza_4";
			AddMoneyToCharacter(pchar, -200000);
			GiveItem2Character(pchar, "obereg_10");
			pchar.questTemp.HWIC.Holl.ScullnotReturn = "true";//给卢卡斯的标志
			ChangeCharacterComplexReputation(pchar, "nobility", -8);
			DelLandQuestMark(npchar);
		break;
		
		case "SolomonBonanza_4":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "AbbyLeavesMarried";//现在可以和阿比说话了
			AddQuestRecord("Holl_Gambit", "1-32");
			AddLandQuestMark(characterFromId("Abigile"), "questmarkmain");
		break;
		
		case "SolomonBonanza_5":
			dialog.text = "什么? 你在说什么, 年轻人? 这是真的吗? 让我看看... ";
			link.l1 = "这是你的钱。 它属于你和阿比盖尔。 但可惜, 我没有找到你祖父的头骨。 ";
			link.l1.go = "SolomonBonanza_6";
		break;
		
		case "SolomonBonanza_6":
			AddMoneyToCharacter(pchar, -200000);
			GiveItem2Character(pchar, "amulet_7"); 
			dialog.text = "哦, 钱啊钱啊钱, 美妙的钱... 嗯, 这看起来不像我的钱, 不过... 闻起来也不像我可爱的财富。 但话说回来 --钱都是一样的, 年轻人, 不是吗? 我不会抱怨的。 就像我们常说的, ‘不要对送上门的外邦人吹毛求疵’! 非常感谢你把我的积蓄还回来。 我也想感谢你, 请接受这个护身符。 现在去告诉阿比这个好消息吧。 我需要数一数这些钱。 ";
			link.l1 = "愿你多福, 所罗门。 ";
			link.l1.go = "SolomonBonanza_4";
			pchar.questTemp.HWIC.Holl.LucasMoney = "true";//给卢卡斯的标志
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

//-------------------------------------------前往英国------------------------------------------------
		
		case "Solomon_treasure":
			dialog.text = "哎呀, 小心点! 罗登堡先生差一点就成了我的外邦女婿。 如果我呼救, 驻军的所有士兵马上就会到这里! ";
			link.l1 = "你他妈的是谁? ";
			link.l1.go = "Solomon_treasure_1";
		break;
		
		case "Solomon_treasure_1":
			dialog.text = "听着, 船长。 我是她的父亲所罗门。 做正确的事, 把我丢失的硬币和她曾祖父的玉头骨带给我。 这个老犹太人可能不像你那么狡猾, 但他也知道你想从他女儿那里得到什么\n也许你是被某个认识我的船长派来的, 别担心, 我会把一切都告诉阿比。 她现在不在家, 她在为你这样的外邦罪人祈祷。 ";
			link.l1 = "这几乎没什么意义... 该死的, 你真是个麻烦。 再见, 你这个老吝啬鬼。 ";
			link.l1.go = "Solomon_treasure_2";
		break;
		
		case "Solomon_treasure_2":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-17");
			pchar.questTemp.HWIC.Eng = "AbigileInChurch";
			sld = characterFromId("Abigile");
			sld.greeting = "abigile_3";
			ChangeCharacterAddressGroup(sld, "Villemstad_church", "goto", "goto1");//阿比在教堂
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
//----------------------------------------------对抗所有人---------------------------------------------	
		
		case "Abigile_kidnap":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Villemstad");
			dialog.text = "一封信? 你说什么! 听着, 外邦人, 罗登堡先生差一点就成了我的女婿。 你可以滚蛋了, 因为我喜欢他! ";
			link.l1 = "听着, 我不在乎你的女婿是谁。 我有义务把这封信交给阿比盖尔。 你知道我在哪里可以找到她吗? 你到底是谁? ";
			link.l1.go = "Abigile_kidnap_1";
		break;
		
		case "Abigile_kidnap_1":
			dialog.text = "我是谁? 我是她的父亲所罗门... 而且我不喜欢你, 外邦人。 ";
			link.l1 = "如果你说你喜欢我, 我会更担心。 现在你是要继续光顾我, 还是去叫阿比盖尔? 我再说一遍, 我是信使! 我有封信给你女儿! ";
			link.l1.go = "Abigile_kidnap_2";
		break;
		
		case "Abigile_kidnap_2":
			dialog.text = "把这封信给我。 我会交给我女儿。 ";
			link.l1 = "在我把信交给你之前, 我会剃掉你的卷发, 拧你的鼻子。 我接到的命令是亲自把这条消息交给她。 没人告诉我她父亲的事, 我也不在乎。 我在哪里可以找到阿比盖尔? ";
			link.l1.go = "Abigile_kidnap_3";
		break;
		
		case "Abigile_kidnap_3":
			dialog.text = "年轻人, 我一喊, 镇上的每个士兵都会立刻到这里。 别这么固执, 你看我掌握着所有的牌。 ";
			link.l1 = "耶稣。 马利亚和约瑟夫! 真的吗? 然后呢? 你指望他们因为我送封信就把我铐起来? 别荒谬了! ";
			link.l1.go = "Abigile_kidnap_4";
		break;
		
		case "Abigile_kidnap_4":
			DialogExit();
			sld = characterFromId("Abigile");
			ChangeCharacterAddressGroup(sld, "Villemstad_houseSP2", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Abigile_GoOver":
			dialog.text = "你疯了吗? 你那封信把我可怜的女儿吓得半死... 她决定去追那个英国船长混蛋! 她乘第一艘可用的船航行了! 哎呀, 我可怜的女儿! 这个老犹太人现在该怎么办? 我的生活毁了! 这是耻辱! 让我沉浸在痛苦中, 或者留下来幸灾乐祸, 我不在乎! 哦, 我可怜的阿比盖尔! 你让你父亲的白头陷入了绝望! ";
			link.l1 = "好吧, 看看! 看来她一刻也等不及了。 再见, 所罗门! ";
			link.l1.go = "Abigile_GoOver_1";
		break;
		
		case "Abigile_GoOver_1":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-69");
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Self = "end";
			pchar.questTemp.HWIC.Detector = "self_fail";
		break;
		
		case "Solomon_history":
			PlaySound("Voice\English\hambit\Solomon Shneur-03.wav");
			dialog.text = "看起来像什么? 那只是一个除了我和阿比盖尔之外没有人的岛。 我在那里藏了我的箱子, 以防海盗外邦人阿梅莱克拿走它。 我血汗挣来的一切都在那个箱子里... ";
			link.l1 = "告诉我, 所罗门, 也许你能想起你女儿提到的那艘快速帆船的名字? 还有她的船长叫什么? ";
			link.l1.go = "Solomon_history_1";
		break;
		
		case "Solomon_history_1":
			dialog.text = "嗯... 好吧, 我不知道。 这个可怜的老犹太人的脑子像一盘鱼丸一样混乱! 你为什么问这个, 年轻人? ";
			link.l1 = "我只是想帮助你女儿, 所罗门。 我不能保证什么, 但我想试试。 我以前的老板对她不好, 在那之后, 我认为我有义务帮助她安顿下来。 ";
			link.l1.go = "Solomon_history_2";
		break;
		
		case "Solomon_history_2":
			dialog.text = "哎呀, 如果是这样的话... ";
			link.l1 = "";
			link.l1.go = "Solomon_history_3";
			pchar.questTemp.HWIC.Self = "SolomonHistoryNext";
		break;
		
		case "Solomon_history_3":
			DialogExit();
			sld = characterFromId("Abigile");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Solomon_thanks":
			dialog.text = "年轻人! 等等! ";
			link.l1 = "什么事? ";
			link.l1.go = "Solomon_thanks_1";
		break;
		
		case "Solomon_thanks_1":
			dialog.text = "年轻的好人! 我想感谢你为我和我女儿所做的一切。 你救了我们。 很抱歉我们第一次见面时给你一个难堪的欢迎, 也抱歉我怀疑你帮助我们的真诚愿望。 请原谅这个老犹太人。 你真是外邦人中的有福之人。 现在告诉我, 除了我的钱, 你在洞穴里没找到别的东西吗? ";
			link.l1 = "没有, 所罗门。 除了钱什么都没有。 我不得不和范伯格的暴徒战斗 --几个月前正是他击沉了你的船。 可能他们已经偷了什么东西... 那里应该还有什么? ";
			link.l1.go = "Solomon_thanks_2";
		break;
		
		case "Solomon_thanks_2":
			dialog.text = "哦, 没什么重要的... 一件古老的家族遗物... 好吧, 没关系! 忘了它吧, 他本来就是个混蛋! 还有... 年轻人, 还有一件事... ";
			link.l1 = "说吧。 ";
			link.l1.go = "Solomon_thanks_3";
		break;
		
		case "Solomon_thanks_3":
			dialog.text = "你... 好吧, 我了解了一些关于你的事。 我们的总督很看重你, 你是个著名的船长。 我告诉你一个秘密... 我女儿很喜欢你。 她自己告诉我的。 也许... 你会考虑一下吗? 阿比盖尔是个非常好的女孩, 我向你保证, 比你在旅途中遇到的任何外邦荡妇都好。 ";
			link.l1 = "哎呀... 没那么简单, 所罗门。 你女儿确实是个罕见的珍宝。 你好好照顾她。 ";
			link.l1.go = "Solomon_thanks_4";
		break;
		
		case "Solomon_thanks_4":
			dialog.text = "考虑一下, 年轻人。 再考虑一下, 回来! 我们很乐意再见到你! ";
			link.l1 = "当然... 再见, 所罗门。 ";
			link.l1.go = "Solomon_thanks_5";
		break;
		
		case "Solomon_thanks_5":
			DialogExit();
			LocatorReloadEnterDisable("Villemstad_houseSp2", "reload1", false);
			AddQuestRecord("Holl_Gambit", "3-65");
			NextDiag.CurrentNode = "First time";
		break;
		
		case "Solomon_poor":
			dialog.text = "唉... 年轻人, 有时候开始新生活是不可能的。 生活在贫困中 --对我这样的老傻瓜来说, 还有什么比这更糟糕的呢? ";
			link.l1 = "对不起, 所罗门。 坚持下去, 寻求基督。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Solomon_poor";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> 处理试图打开箱子的反应块
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("你是个" + GetSexPhrase("小偷, 先生! 卫兵, 抓住他","小偷, 小姐! 卫兵, 抓住她") + "!!!", "看看那个! 我刚陷入沉思, 你就想检查我的箱子! 抓住小偷!!! ", "卫兵! 抢劫! 抓住小偷!!! ");
			link.l1 = "该死的! ";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- 处理试图打开箱子的反应块
	}
}
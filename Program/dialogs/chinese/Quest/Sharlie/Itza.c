// 乌拉坎. 卡内克和其他伊察印第安人的对话
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "你有什么需要吗? ";
			link.l1 = "不, 没什么。 ";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// 伊察市民
		case "itza_ctz":
			dialog.text = LinkRandPhrase("又一个白脸... 大祭司会很高兴挖出你的心脏... ","白脸知道怎么来塔亚萨尔, 但没人能离开这座城市! ","我很惊讶, 白脸: 你还没去灵魂之地... 趁你还能走的时候走吧, 很快你就能见到你的祖先了。 ");
			link.l1 = LinkRandPhrase("好吧, 好吧。 我们走着瞧... ","别想吓唬我, 红皮肤的战士。 我见过比这更可怕的。 ","去去, 试着吓唬孩子们吧。 ");
			link.l1.go = "exit";
			NextDiag.TempNode = "itza_ctz";
		break;
		
		case "itza_ctz_1":
			dialog.text = LinkRandPhrase("祝福我与敌人战斗吧, 伟大的卡维尔! ","伟大的卡维尔和伟大的库库尔坎亲临此地! 即使在古玛雅时期这也未曾发生! ","我们会把卡维尔和库库尔坎的伟大战役传说传给我们的孩子! ");
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "itza_ctz_1";
		break;
		
		// 乌拉坎 - 伊察领袖
		case "urakan":
			dialog.text = "你是伟大的战士, 白脸。 我们将把你的血献给神灵。 你将尊严地死去。 ";
			link.l1 = "冷静点, 红皮肤的战士。 我不会让你们的卡内克把我作为祭品献给库库尔坎或其他任何人。 你们的战士没能抓住我, 他们每一个都已在战斗中倒下。 ";
			link.l1.go = "urakan_1";
		break;
		
		case "urakan_1":
			dialog.text = "是的, 你这位高尚的战士, 白脸。 但你无法抵挡数百名塔亚萨尔伊察战士。 不过, 你说了个有趣的词。 你怎么知道伟大的卡内克和库库尔坎的? ";
			link.l1 = "让我猜猜... 既然你不是卡内克, 你的名字一定是乌拉坎, 你是祭司卡内克的儿子? ";
			link.l1.go = "urakan_2";
		break;
		
		case "urakan_2":
			dialog.text = "你说的是事实, 白脸。 我是乌拉坎, 我很惊讶。 ";
			link.l1 = "当你看到这个时会更惊讶... 看。 ";
			link.l1.go = "urakan_3";
		break;
		
		case "urakan_3":
			dialog.text = "哦, 众神! 如果白脸有面具, 那就意味着时机已到... 你就是库库尔坎所说的那个人。 他命令当你到达塔亚萨尔时把你带到他面前。 他知道你会来。 ";
			link.l1 = "库库尔坎? ! 他在塔亚萨尔? ";
			link.l1.go = "urakan_4";
		break;
		
		case "urakan_4":
			dialog.text = "是的, 白皮肤的战士。 羽蛇神来到了塔亚萨尔。 不久他将离去, 为祖先 --伟大的玛雅城市带来光明。 ";
			link.l1 = "该死! 所以他已经在这里了... (压低声音) 乌拉坎, 我知道一切。 我知道是你派克萨特.查带着真理守护者去寻找克索切特姆和库库尔坎的面具... ";
			link.l1.go = "urakan_5";
		break;
		
		case "urakan_5":
			dialog.text = "";
			link.l1 = "我从你眼中看到了惊讶, 但也有怀疑, 伟大的首领乌拉坎。 你对库库尔坎并不满意, 对吗? ";
			link.l1.go = "urakan_6";
		break;
		
		case "urakan_6":
			dialog.text = "每个伊察战士都为伟大的库库尔坎到来而高兴, 白皮肤的战士。 你必须站在库库尔坎面前。 他等了你很多个夜晚。 他是伟大的先知, 能预知一切。 去找飞蛇吧, 你别无选择。 我们不会让你离开塔亚萨尔。 ";
			link.l1 = "你难道不明白吗? 一旦库库尔坎穿过时间之门离开, 你们所有人, 包括你自己, 都将不复存在? 最妙的是你们会以另一种形态。 另一个身体重生... 也许是普通战士, 甚至可能是残废或乞丐... ";
			link.l1.go = "urakan_7";
		break;
		
		case "urakan_7":
			dialog.text = "去吧, 白皮肤的战士。 你会在伊察战士的大神庙找到库库尔坎。 直走穿过桥, 直到看到大金字塔。 进入神庙的下门, 靠近圣所。 ";
			link.l1 = "好吧。 我会去找库库尔坎, 因为我知道我们无法逃避这次相遇。 但我已经警告过你了。 ";
			link.l1.go = "urakan_8";
		break;
		
		case "urakan_8":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetWarriorType(npchar);
			LAi_warrior_SetStay(npchar, true);
			LAi_warrior_DialogEnable(npchar, true);
			NextDiag.CurrentNode = "urakan_9";
			DeleteAttribute(pchar, "GenQuest.Notsearchbody");
			AddQuestRecord("Tieyasal", "25");
			pchar.quest.Tieyasal_Templegreat.win_condition.l1 = "location";
			pchar.quest.Tieyasal_Templegreat.win_condition.l1.location = "Temple_great";
			pchar.quest.Tieyasal_Templegreat.function = "Tieyasal_InGreatTemple";
			// 战斗经验
			AddComplexSelfExpToScill(300, 300, 300, 300);
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddCharacterExpToSkill(pchar, "Fortune", 300);
		break;
		
		case "urakan_9":
			dialog.text = "去吧, 白皮肤的战士。 库库尔坎在等你。 ";
			link.l1 = "我这就去... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "urakan_9";
		break;
		
		case "urakan_10":
			PlaySound("Voice\English\Complete.wav");
			dialog.text = "预言成真了! 当我看到你与库库尔坎战斗时, 我知道你就是卡维尔本人。 你来到塔亚萨尔是为了拯救伊察人民免于因我父亲和库库尔坎而灭亡。 我的父亲, 伟大的祭司卡内克, 为了荣耀早已逝去的玛雅祖先而将伊察人民置于死地。 \n我是战首领乌拉坎, 多年来一直保护伊察人民。 没有一个白脸能活着离开塔亚萨尔。 我和战士们确保伊察人民在未来许多年里得到保护和生存。 我不想牺牲我所有的人民。 ";
			link.l1 = "我就知道, 乌拉坎。 我之前在桥上请你帮助我。 ";
			link.l1.go = "urakan_11";
		break;
		
		case "urakan_11":
			dialog.text = "没有什么能逃过伟大卡维尔的眼睛。 请原谅乌拉坎之前没有认出你是谁。 ";
			link.l1 = "别担心, 首领。 我已经击败了库库尔坎的凡胎肉身, 但我们还有第二项重要任务 --关闭通往过去的大门。 这个不自然的时间漏洞必须被消除。 你会帮助我吗? ";
			link.l1.go = "urakan_12";
		break;
		
		case "urakan_12":
			dialog.text = "乌拉坎能帮你做什么, 哦, 卡维尔? ";
			link.l1 = "你派克萨特.查带着真理守护者去寻找克索切特姆和库库尔坎的面具。 所以你知道它可以用来关闭时间之门。 你父亲告诉过你吗? ";
			link.l1.go = "urakan_13";
		break;
		
		case "urakan_13":
			dialog.text = "父亲没有说。 我在知识与智慧神庙研究过铭文, 但很多内容乌拉坎并不清楚。 也许, 卡维尔能明白? ";
			link.l1 = "你具体发现了什么? ";
			link.l1.go = "urakan_14";
		break;
		
		case "urakan_14":
			dialog.text = "我熟记于心。 铭文宣称: ‘当太阳逆雨升起, 火在它们之间形成三角时, 让托希尔的腿相互碰撞, 并在时间祭坛上焚烧库库尔坎的面具。 然后封印伊察姆纳的时间之门, 直到末日。 ’";
			link.l1 = "什么。 ";
			link.l1.go = "urakan_15";
		break;
		
		case "urakan_15":
			dialog.text = "是的。 ";
			link.l1 = "天啊... 带我去看那扇门。 ";
			link.l1.go = "urakan_16";
		break;
		
		case "urakan_16":
			dialog.text = "它们位于库库尔坎神庙。 但那里的门是锁着的。 只有我父亲能锁上和打开。 当他打开库库尔坎神庙的门时, 他说: ‘太阳升起又落下, 水涨又退, 火燃又熄, 战争与和平交替, 但只有天堂是永恒的。 超越时间的只有天堂。 ’";
			link.l1 = "有意思... 让我们记住这个, 看看能做些什么... ";
			link.l1.go = "urakan_17";
		break;
		
		case "urakan_17":
			dialog.text = "我留在这里, 在下面, 靠近时间祭坛。 从内部可以看到塔亚萨尔的每座金字塔和建筑。 寻找钥匙, 我留在这里。 ";
			link.l1 = "如果我有任何重要问题, 一定会来找你。 ";
			link.l1.go = "urakan_18";
		break;
		
		case "urakan_18":
			DialogExit();
			NextDiag.CurrentNode = "urakan_adv";
			DeleteAttribute(pchar, "GenQuest.Notsearchbody");
			pchar.quest.Tieyasal_UrakanTemple.win_condition.l1 = "location";
			pchar.quest.Tieyasal_UrakanTemple.win_condition.l1.location = "Tenochtitlan";
			pchar.quest.Tieyasal_UrakanTemple.function = "Tieyasal_UrakanInTemple";
			AddQuestRecord("Tieyasal", "26");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "quest", "urakan", "", -1);
			// 战斗经验
			AddComplexSelfExpToScill(1000, 1000, 1000, 1000);
			AddCharacterExpToSkill(pchar, "Leadership", 3000);
			AddCharacterExpToSkill(pchar, "Fortune", 1500);
		break;
		
		case "urakan_adv":
			dialog.text = "乌拉坎能为伟大的卡维尔提供建议或行动帮助吗? ";
			if (Tieyasal_CheckTablets() && !CheckAttribute(npchar, "quest.tablets"))
			{
				link.l1 = "看看我找到的这块石板。 从发现的地点判断, 它一定和你父亲有关, 而且显然不是普通物品... ";
				link.l1.go = "tablets";
			}
			if (CheckAttribute(npchar, "quest.treasureentrance"))
			{
				link.l1 = "我在大神庙顶部发现了另一个入口, 但它被封住了。 我怎么进去? 也许我要找的东西在里面。 ";
				link.l1.go = "treasure";
			}
			link.l9 = "现在没什么事, 乌拉坎。 我自己能处理... ";
			link.l9.go = "exit";
			NextDiag.TempNode = "urakan_adv";
		break;
		
		case "tablets":
			dialog.text = "众神石板。 父亲有几块不同的碎片, 它们对他来说非常珍贵。 古代塔亚萨尔的建造者用石板来激活隐藏机制。 开关门, 甚至进行魔法仪式。 \n如果放在正确的位置, 它们就会起作用 --这就是我父亲所做的。 但我和你一样是个战士, 不知道如何正确使用它们。 也许卡维尔知道? ";
			link.l1 = "我们一定会弄清楚的... ";
			link.l1.go = "exit";
			npchar.quest.tablets = "true";
			NextDiag.TempNode = "urakan_adv";
			AddQuestRecord("Tieyasal", "31");
		break;
		
		case "treasure":
			dialog.text = "这是通往塔亚萨尔宝藏的门。 里面躺着伊察印第安人的财富。 只有我父亲能打开和关闭里面的门。 没有他, 没人敢进入宝藏, 甚至我也不行。 ";
			link.l1 = "你父亲是怎么打开入口的? ";
			link.l1.go = "treasure_1";
		break;
		
		case "treasure_1":
			dialog.text = "我父亲说: ‘任何财富都有两面。 只有知道这两面的人才能进入塔亚萨尔的宝藏。 ’这是什么意思 --我不知道。 也许, 卡维尔能猜到? ";
			link.l1 = "我们也会弄清楚这个... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "urakan_adv";
			DeleteAttribute(npchar, "quest.treasureentrance");
			AddQuestRecord("Tieyasal", "32");
		break;
		
		case "urakan_19":
			PlaySound("Voice\English\Complete.wav");
			dialog.text = "你做到了, 哦伟大的卡维尔! 伊察人民现在安全了。 我, 乌拉坎, 卡内克的儿子, 向你保证, 我不会辜负你给予的荣誉, 我将以你的名义保护塔亚萨尔免受任何不光彩的白脸入侵。 ";
			link.l1 = "我完全相信, 首领。 现在我们可以庆祝了: 我们已经阻止了库库尔坎的 treacherous 计划。 他再也无法实现时间革命了。 ";
			link.l1.go = "urakan_20";
		break;
		
		case "urakan_20":
			PlaySound("interface\abordage_wining.wav");
			dialog.text = "荣耀属于伟大的卡维尔! 我和我这一代人有幸在塔亚萨尔见到两位神灵。 我们会把这段历史写下来传给我们的孩子。 他们会知道塔亚萨尔的神灵之战! 荣耀属于卡维尔! 荣耀! ";
			link.l1 = "我需要喝一杯... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_Win_IndianBead");
		break;
		
		// 卡内克 - 伊察祭司
		case "kanek":
			dialog.text = "你站在羽蛇神面前, 白脸。 强大的库库尔坎在人间的化身之灵。 你很幸运能通过他化身的父亲成为他的兄弟, 就像我幸运地成为他母亲的父亲, 生下他的女人的父亲。 这是巨大的荣誉。 也许这就是为什么你成为了强大的战士并且还活着。 \n但你的时间不多了, 白脸。 我们将开启新的时代, 伟大的玛雅时代。 我们将建立自己的政权, 永远不让白脸进入我们的世界。 很快。 我, 祭司卡内克, 将开始仪式! ";
			link.l1 = "太棒了... ";
			link.l1.go = "kanek_1";
		break;
		
		case "kanek_1":
			DialogExit();
			sld = characterFromId("Mishelle");
			sld.dialog.currentnode = "kukulkan_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.7);
		break;
		
		case "kanek_2":
			dialog.text = "乌拉坎, 你听到我们的主说的话了。 现在投降! ";
			link.l1 = "当伟大者互相争斗时, 我们这些凡人最好站在一边远远观看, 父亲... ";
			link.l1.go = "kanek_3";
		break;
		
		case "kanek_3":
			dialog.text = "什么? ! 清醒点, 儿子! ";
			link.l1 = "这个人是库库尔坎的兄弟, 是伟大的战士。 我在他身上看到了卡维尔本人的化身! 除了他, 没有人能承受那样的神灵。 父亲, 神灵之间的决斗可不是闹着玩的! 如果你向库库尔坎献祭, 我的战士们会把血献给卡维尔! ";
			link.l1.go = "kanek_4";
		break;
		
		case "kanek_4":
			dialog.text = "你脑子清醒吗, 乌拉坎? ";
			link.l1 = "多年来, 我, 以飓风命名的人, 成功地以卡维尔的名义保护我们的土地免受外族人的入侵。 数百人倒在我们的棍棒下, 没有人离开塔亚萨尔。 但我这辈子从未见过像这个白脸这样强壮敏捷的战士。 如果他能打败库库尔坎, 那他就是卡维尔之灵的化身! ";
			link.l1.go = "kanek_5";
		break;
		
		case "kanek_5":
			DialogExit();
			sld = characterFromId("Mishelle");
			sld.dialog.currentnode = "kukulkan_win_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
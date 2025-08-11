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
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "你想要什么? ";
			link.l1 = "没什么。 ";
			link.l1.go = "exit";
		break;

		case "Poorman_1":
			if (pchar.sex == "woman")
			{
				dialog.text = "嘿, 美人, 为你的女士收藏添一件精美饰品如何? 真正的宝藏! 你能收获羡慕的目光, 我能换几个买面包和朗姆酒的硬币。 ";
			}
			else
			{
				dialog.text = "嘿, 船长, 给你的女士买件精美礼物如何? 真正的宝藏! 你能得到她的温柔感激, 我能换几个买面包和朗姆酒的硬币。 ";
			}
			link.l1 = "这样一小时后士兵就会来找我, 把我扔进监狱吗? 你从哪里弄来的, 流浪汉? ";
			link.l1.go = "Poorman_2_fortune";
			link.l2 = "精美礼物? 像你这样无家可归的人, 从哪里弄到这种东西? ";
			link.l2.go = "Poorman_2_leadership";
			if (npchar.quest.meeting == "0") npchar.quest.meeting = "1";
		break;

		case "Poorman_2_fortune":
			dialog.text = ""+GetSexPhrase("船长, 我","我")+"发现了这个带浮雕的美丽吊坠, 千真万确! 如果撒谎我就沉海! 它就躺在那里, 无人问津。 我总不能把这样的美丽留在泥土里吧? ";
			link.l1 = "好吧。 给我看看你手里的东西。 ";
			link.l1.go = "Poorman_3";
			link.l2 = "谁会相信你这样‘可敬’的先生的话? 去找更易受骗的人吧。 ";
			link.l2.go = "Poorman_exit";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "Poorman_2_leadership":
			dialog.text = ""+GetSexPhrase("船长, 我","我")+"发现了这个带浮雕的美丽吊坠, 千真万确! 如果撒谎我就沉海! 它就躺在那里, 无人问津。 我总不能把这样的美丽留在泥土里吧? ";
			link.l1 = "好吧。 给我看看你手里的东西。 ";
			link.l1.go = "Poorman_3";
			link.l2 = "谁会相信你这样‘可敬’的先生的话? 去找更易受骗的人吧。 ";
			link.l2.go = "Poorman_exit";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Poorman_exit":
			DialogExit();
			AddDialogExitQuestFunction("TBP_PismoVDome");
		break;
		
		case "Poorman_3":
			dialog.text = "看... 这东西很不错! 我在花坛里发现的, 带灯笼的房子旁边, 酒馆附近。 但那里很久没人了, 所以也没人可以归还。 ";
			link.l1 = "奇怪的小饰品。 你想要多少钱? ";
			link.l1.go = "Poorman_4";
		break;

		case "Poorman_4":
			dialog.text = "只要一百比索"+GetSexPhrase(", 船长","")+"... 对你这样的人来说只是小钱! 对我来说却是一整个星期不用担心面包从哪来。 看看它 —多漂亮! ";
			if (sti(pchar.Money) >= 100)
			{
				link.l1 = "好吧, 给你一百比索。 ";
				link.l1.go = "Poorman_5";
			}
			link.l2 = "我想我还是算了。 去碰别人的运气吧。 ";
			link.l2.go = "Poorman_exit";
		break;

		case "Poorman_5":
			dialog.text = "谢谢你, "+GetAddress_Form(NPChar)+"! 现在幸运一定会眷顾你! 你是个好人, 显而易见。 ";
			link.l1 = "... ";
			link.l1.go = "Poorman_exit";
			GiveItem2Character(PChar, "jewelry24");
			pchar.questTemp.TBP_BuyKulon = true;
			pchar.questTemp.TBP_BuyKulonOtdatBetsy = true;
		break;
		
		case "Pirate_1":
			if (pchar.sex == "woman")
			{
				dialog.text = "哦-哦-哦, 谁来拜访我们了? 看来你没走错门, 甜心... 进来, 进来! 脱下衣服, 别拘束。 ";
				link.l1 = "嗯, 嗯... 我们这儿有谁? 你们不就是给贝琪留了‘温柔’恐吓信的那些无赖吗? ";
			}
			else
			{
				dialog.text = "这是哪来的乌合之众? 你走错门了吧, 蠢蛋? 在我把你开膛破肚之前滚出去! ";
				link.l1 = "嗯, 嗯... 我们这儿有谁? 你们不就是给贝琪留了漂亮恐吓信的那些傻瓜吗? ";
			}
			link.l1.go = "Pirate_2";
		break;

		case "Pirate_2":
			if (pchar.sex == "woman")
			{
				dialog.text = "贝琪? 去他的贝琪! 更有趣的是你在这儿做什么, 甜心... 既然来了 —不用急着走, 我们会想办法让你‘忙起来’... ";
			}
			else
			{
				dialog.text = "什么鬼贝琪? 别找死, 蠢货。 趁你还能自己走 —离开。 否则我们就得把你碎尸万段, 用桶把你抬出去! ";
			}
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_2");
		break;

		case "BetsiPrice_1":
			dialog.text = "救命! 救命, 我求你了! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_3");
			locCameraFromToPos(1.40, 1.62, 1.14, false, 2.58, -0.30, -1.64);
		break;
		
		case "Pirate_3":
			dialog.text = "... ";
			link.l1 = "她在那儿。 你麻烦大了, 朋友, 如果你不想这成为你最后的错误, 我建议你立刻放了她。 ";
			link.l1.go = "Pirate_4";
		break;

		case "Pirate_4":
			dialog.text = "哈! 听到了吗, 雷吉? "+GetSexPhrase("他在","她在")+"威胁我们呢。 "+GetSexPhrase("真是个自大的混蛋","真是个自大的垃圾")+"。 嘿, 让我们让"+GetSexPhrase("这个新贵看看他的胆子是什么颜色","这个新贵知道什么是真正的痛苦")+"。 ";
			link.l1 = "这是你自找的。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_4");
		break;

		case "Pirate_5":
			if (!CharacterIsAlive("TBP_Bandit_1"))
			{
				dialog.text = "... ";
				link.l1 = "现在放了女孩。 否则你就躺在你朋友旁边。 ";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("TBP_HouseBetsi_6");
			}
			else
			{
				dialog.text = "... ";
				link.l1 = "... ";
				link.l1.go = "exit";
				NextDiag.TempNode = "Pirate_5";
			}
		break;

		case "BetsiPrice_2":
			dialog.text = "该死的狗东西! 你以为我会保持沉默? ! ";
			link.l1 = "... ";
			link.l1.go = "BetsiPrice_2_1";
			sld = CharacterFromID("TBP_Bandit_2");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("TBP_BetsiPrice"));
			CharacterTurnByChr(npchar, sld);
		break;

		case "BetsiPrice_2_1":
			dialog.text = "还有你... 你好像不是他们一伙的。 你是谁? ";
			link.l1 = "船长"+GetFullName(pchar)+", 为你效劳。 ";
			link.l1.go = "BetsiPrice_2_2";
			CharacterTurnByChr(npchar, pchar);
		break;

		case "BetsiPrice_2_2":
			dialog.text = "那么, 我欠你一条命? ";
			link.l1 = "看起来是这样。 但现在更重要的是 —这些人是谁, 你卷入了什么事? ";
			link.l1.go = "BetsiPrice_3";
		break;
		
		case "BetsiPrice_3":
			dialog.text = "这些人... 他们是被一位重要的英国官员派来的。 他曾经和我很亲近... 而现在, 如你所见, 他希望我死。 ";
			link.l1 = "我想我开始理解你的故事了。 你曾是他的情妇, 但在某个时候你决定利用这一点。 想吓唬他... 告诉他的家人? ";
			link.l1.go = "BetsiPrice_4";
		break;

		case "BetsiPrice_4":
			dialog.text = "你惊人地接近"+GetSexPhrase("真相, 帅哥","真相, 美女")+"... 但同时也差得很远。 如果是那样, 我现在已经死了。 是的, 我曾是他的情妇, 但我从未想过制造家庭闹剧\n事情要复杂得多: 有一天我发现他找了新欢, 决定摆脱我, 让我一无所有。 就像扔垃圾一样把我抛弃。 嗯, 我不习惯空手离开\n所以我拿走了真正有价值的东西 —可能毁掉他生活的文件 —逃到了新大陆。 然后我提出交易: 用他的秘密换取我的安全和丰厚补偿\n这就是我还活着的原因 —他们需要文件。 而我不急于透露藏在哪里。 ";
			link.l1 = "嗯, 你不仅漂亮, 还狡猾得像魔鬼。 你玩得很大, 但说实话 —这场游戏已经超出了你的控制。 也许是时候考虑另一个选择了, 趁还有机会退出? 如果他们在这里找到你, 你可能无法再躲到其他地方。 你的运气迟早会用完。 ";
			link.l1.go = "BetsiPrice_5";
		break;

		case "BetsiPrice_5":
			dialog.text = "你在建议什么? 就把文件给他, 然后空手离开? 在我经历了这一切之后? ";
			link.l1 = "你应该知道, 对他们来说你只是个需要清除的麻烦。 他们不会停止, 直到得到想要的东西。 但你还有选择。 把文件给那边那个蠢货。 让他转交给主人, 并向他保证你已经放弃了意图, 只是想让这一切结束。 ";
			link.l1.go = "BetsiPrice_6";
		break;

		case "BetsiPrice_6":
			dialog.text = "如果这是我唯一的机会... 好吧, 我准备冒险。 我一直把文件带在身上。 我把它们缝在紧身胸衣里, 一刻也不离开。 等一下... ";
			link.l1 = "... ";
			link.l1.go = "BetsiPrice_7";
		break;

		case "BetsiPrice_7":
			dialog.text = "给, 拿着。 这是我所有的文件。 你能给那个家伙说几句告别的话吗? 你知道如何有说服力, 对吧? ";
			link.l1 = "我想他已经吸取了主要教训。 现在我们只需要让他清楚该做什么。 ";
			link.l1.go = "exit";
			notification(StringFromKey("Neutral_15"), "BoxMinus");
			PlaySound("interface\important_item.wav");
			AddDialogExitQuestFunction("TBP_HouseBetsi_11");
		break;
		
		case "Pirate_6":
			dialog.text = "... ";
			link.l1 = "站起来。 仔细听我说, 混蛋。 这是你被派来取的文件。 把它们带给你的主人, 告诉他: 如果他继续派杀手追贝琪, 他们会和你的朋友一样下场。 告诉他她永远离开他的生活了 —他没有理由再追她。 让他把这当作她自愿和解的举动。 你都明白了吗, 还是需要我把这些信息塞进你脑子里? ";
			link.l1.go = "Pirate_7";
			notification(StringFromKey("Neutral_16"), "BoxMinus");
			PlaySound("interface\important_item.wav");
		break;

		case "Pirate_7":
			dialog.text = "我明白了, "+GetAddress_Form(NPChar)+"... ";
			link.l1 = "那就滚吧。 别想着逗留 —如果我再在这里看到你, 你不会有第二次机会。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_12");
		break;

		case "BetsiPrice_8":
			dialog.text = "嗯, "+GetSexPhrase("我的英雄","我的狂怒")+", 看来我甚至忘了感谢你... 都是因为太激动了。 不是每天都会被俘虏, 然后多亏如此勇敢的"+GetSexPhrase("救星","救星")+"重获自由。 告诉我, 这是你的习惯吗 —从麻烦中拯救女士, 还是我只是极其幸运? ";
			link.l1 = "怎么说呢, 贝琪, 我对戏剧性的出场和"+GetSexPhrase("美丽女士","各种冒险")+"没有抵抗力。 ";
			link.l1.go = "BetsiPrice_9";
		break;

		case "BetsiPrice_9":
			dialog.text = "我叫米兰达。 米兰达.贝尔。 不得不消失时我取了贝琪这个名字 —新生活, 新名字, 你懂的。 我匆忙逃离欧洲, 只抓了几枚硬币和几件珠宝\n其余的可能都落入了追捕我的那些混蛋手中。 现在没有豪华招待会和昂贵服饰 —只有郊区的破屋和酒馆的工作。 我从没想过有一天我会端朗姆酒, 而不是在好伙伴中品尝葡萄酒... ";
			link.l1 = "即使如此, 你看起来仿佛掌控着命运。 也许这才是你真正的天赋所在。 ";
			link.l1.go = "BetsiPrice_10";
		break;

		case "BetsiPrice_10":
			dialog.text = ""+GetSexPhrase("奉承者。 但你知道, 这很适合你","你过奖了")+"... 经历这一切后, 我有些不安。 要是他们已经在拐角等我怎么办? 送我回家吧, 再做一会儿我的"+GetSexPhrase("救世主","救世主")+"。 ";
			link.l1 = "我不是半途而废的人。 那么, 女士, 我听候差遣。 我们走吧。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma");
		break;

		case "BetsiPrice_11":
			dialog.text = "我们到了。 你知道吗, 我甚至没问是什么风把你吹到那所房子的? ";
			if (CheckAttribute(pchar, "questTemp.TBP_BuyKulonOtdatBetsy") && pchar.questTemp.TBP_BuyKulonOtdatBetsy == true)
            {
			link.l2 = "我不是偶然去的。 这个吊坠带我去的。 拿着。 酒馆老板似乎对你的失踪非常不安, 让我查明发生了什么。 嗯, 我有拒绝的选择吗? 抛弃陷入困境的女士, 这不配船长的行为。 ";
			link.l2.go = "BetsiPrice_12_otdal_kulon";
			}
			else
			{
			link.l1 = "我不是偶然去的。 酒馆老板似乎对你的失踪非常不安, 让我查明发生了什么。 嗯, 我有拒绝的选择吗? 抛弃陷入困境的女士, 这不配船长的行为。 ";
			link.l1.go = "BetsiPrice_12";
			}
		break;
		
		case "BetsiPrice_12":
			dialog.text = "啊, 太高尚了, "+pchar.name+"船长! 不过, 我敢肯定酒馆老板更关心他的利润而不是我。 不幸的是, 今天不能请你进去了 —我需要恢复一下。 在地下室待的时间没让我变得更漂亮。 但如果我们不再见面 —我不会原谅你的。 所以明天来酒馆吧, 我会准备一个... 礼物给你。 ";
			link.l1 = "嗯, 现在我又多了一个拜访的理由。 再见, 米... 贝琪。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_3");
		break;
		
		case "BetsiPrice_12_otdal_kulon":
			dialog.text = "啊, 太高尚了, "+pchar.name+"船长! 不过, 我敢肯定酒馆老板更关心他的利润而不是我。 不幸的是, 今天不能请你进去了 —我需要恢复一下。 在地下室待的时间没让我变得更漂亮。 但如果我们不再见面 —我不会原谅你的。 所以明天来酒馆吧, 我会准备一个... 礼物给你。 ";
			link.l1 = "嗯, 现在我又多了一个拜访的理由。 再见, 米... 贝琪。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_3");
			TakeItemFromCharacter(pchar, "jewelry24");
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
		break;

		case "TBP_Helena_1":
			dialog.text = "嗯, 嗯... 多么甜蜜的告别。 这位衣冠不整的女士是谁? 她看起来像在地下室坐了一个星期, 但这也没阻止你用眼睛‘吃掉’她, 对吧, "+pchar.name+"? ";
			link.l1 = "不是你想的那样。 这女孩陷入了困境, 我帮她摆脱了。 就这样。 ";
			link.l1.go = "TBP_Helena_2";
		break;

		case "TBP_Helena_2":
			dialog.text = "你当然决定成为她的白衣骑士了? ";
			link.l1 = "你知道, 当有人遇到危险时, 我不能袖手旁观。 ";
			link.l1.go = "TBP_Helena_3";
		break;

		case "TBP_Helena_3":
			dialog.text = "好吧。 但下次, "+pchar.name+", 小心点... 别给我吃醋的理由。 ";
			link.l1 = "当然, 亲爱的。 我们离开这里吧, 还有很多事要做。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_5");
		break;

		case "TBP_Mary_1":
			dialog.text = "嗯, 嗯... 多么甜蜜的告别。 如此关心, 如此温柔的承诺... 你甚至如此亲切地叫她的名字, 好吧。 也许我也该消失几天, 让你用同样的急切寻找我? ";
			link.l1 = "玛丽, 你知道你是我的护身符, 而她... 只是个陷入麻烦的女孩。 ";
			link.l1.go = "TBP_Mary_2";
		break;

		case "TBP_Mary_2":
			dialog.text = "啊, 当然! 只是个需要骑士的可怜人! 还有你的眼神 —那也是出于礼貌吗? 你几乎用眼睛把她扒光了! ";
			link.l1 = "玛丽, 你夸张了! 看看我怎么看你? 看到区别了吗? 还是需要我... 近距离提醒你? ";
			link.l1.go = "TBP_Mary_3";
		break;

		case "TBP_Mary_3":
			dialog.text = "好吧, "+pchar.name+", 这次你逃过一劫, 好吧。 但如果我再看到这样的场景... ";
			link.l1 = "那我就得再次提醒你, 谁在我心中占据唯一的位置。 来吧, 亲爱的, 还有很多事要做。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_5");
		break;
		
		case "BetsiPrice_sex_1":

			switch (rand(1))
			{
				case 0:
					dialog.text = "嗯... 当我如此靠近你时, 你无法想象我脑子里在想什么... 以及我多想让它们成真。 ";
					link.l1 = "那就别只是想想... 一一展示给我。 ";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 1:
					dialog.text = "啊, 我亲爱的"+GetSexPhrase("","")+"... 你靠近时, 我很难保持克制... ";
					link.l1 = "那就别再甜蜜折磨了... 到我这里来... ";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;
			}
			AddDialogExitQuestFunction("TBP_Betsi_sex_3");
		break;

		case "BetsiPrice_sex_2":
			switch (rand(1))
			{
				case 0:
					dialog.text = "啊, "+GetSexPhrase("我亲爱的船长","我亲爱的"+pchar.name+"")+"... 我仍沉浸在这甜蜜的疯狂中。 ";
					link.l1 = "也许这疯狂值得铭记... 甚至有一天重复。 ";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 1:
					dialog.text = "哦, "+pchar.name+"... 如果我说这很惊人, 你不会太得意"+GetSexPhrase(", 对吧? ","。 对吧? ")+"?";
					link.l1 = "除非你答应再用耳语说一遍... ";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;
			}
			AddDialogExitQuestFunction("TBP_Betsi_sex_7");
		break;

		
		
		
		
		
		
		
	}
}
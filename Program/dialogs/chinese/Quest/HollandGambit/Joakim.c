// 若阿金.梅里曼 - 葡萄牙神秘天才
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
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
				if (pchar.questTemp.HWIC.Holl == "AbbySeekIsland" && !CheckAttribute(npchar, "quest.HWICHoll.Task"))
				{
					dialog.text = "日安, 先生! 我是约阿希姆.梅里曼博士。 有幸与" +GetFullName(pchar)+ "船长交谈吗? ";
					link.l1 = "是的, 是我。 你究竟怎么知道我的名字? 我不记得以前见过你。 ";
					link.l1.go = "JoakimSeekSkull";
					break;
				}
				if (CheckCharacterItem(pchar, "SkullAztec"))
				{
					dialog.text = "很高兴见到你, 船长。 从你轻快的步伐我能看出, 你即将让我非常高兴。 你有尤姆.西米利的头骨吗? ";
					link.l1 = "我有你说的那个头骨。 它散发着能量, 像燃烧的熔炉一样噼啪作响。 ";
					link.l1.go = "JoakimFindSkull";
					break;
				}
				dialog.text = "你还有别的事吗, 船长? ";
				link.l1 = "没有, 梅里曼先生。 我告辞了..";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "JoakimMeeting" && !CheckAttribute(npchar, "quest.HWICHoll.Task"))
				{
					dialog.text = "日安, 先生! 我是约阿希姆.梅里曼博士。 有幸与" +GetFullName(pchar)+ "船长交谈吗? ";
					link.l1 = "是的, 是我。 你究竟怎么知道我的名字? 我不记得以前见过你。 ";
					link.l1.go = "JoakimSeekSkull";
					break;
				}
				if (CheckCharacterItem(pchar, "SkullAztec"))
				{
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("Villemstad");
					dialog.text = "很高兴见到你, 船长。 从你轻快的步伐我能看出, 你即将让我非常高兴。 你有尤姆.西米利的头骨吗? ";
					link.l1 = "我有你说的那个头骨。 它散发着能量, 像燃烧的熔炉一样噼啪作响。 ";
					link.l1.go = "JoakimFindSkull";
					break;
				}
				dialog.text = "你还有别的要补充吗, 船长? ";
				link.l1 = "没有, 梅里曼博士。 我告辞了。 ";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "日安。 你想从我这里得到什么吗? ";
			link.l1 = "不, 抱歉。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Landlady"://房屋女主人
			dialog.text = "如果你是来看梅里曼博士的, 他不在这里。 他不再住这里了。 ";
			link.l1 = "我知道了。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Landlady";
		break;
		
		case "Landlady_1"://房屋女主人
			dialog.text = "如果你是来看梅里曼博士的, 那我得告诉你他不在家。 他现在外出旅行了, 我不知道他什么时候回来。 ";
			link.l1 = "我知道了。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Landlady_1";
		break;
		
		case "Landlady_2"://房屋女主人
			dialog.text = "如果你是来看梅里曼博士的, 他不在这里。 他不再住这里了。 ";
			link.l1 = "我知道了。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Landlady_2";
		break;
		
		case "JoakimSeekSkull":
			PlaySound("Voice\English\hambit\Joakim Merriman-01.wav");
			dialog.text = "你的事并不像你想象的那么私密, 船长! 但别惊慌, 我有个提议给你! 我是个科学工作者, 某种意义上的自然哲学家, 研究西班牙大陆和西印度群岛印第安异教徒的迷人文化。 你能行行好跟我到我家, 在我的客厅里讨论可能非常有利可图的细节吗? ";
			link.l1 = "你引起了我的好奇心和关注。 带路吧。 ";
			link.l1.go = "JoakimSeekSkull_1";
		break;
		
		case "JoakimSeekSkull_1":
			dialog.text = "你不会拒绝的, 先生! 我家离这儿不远。 跟我来! ";
			link.l1 = "... ";
			link.l1.go = "JoakimSeekSkull_2";
		break;
		
		case "JoakimSeekSkull_2":
			DialogExit();
			AddLandQuestMark(npchar, "questmarkmain");
			LAi_ActorGoToLocation(npchar, "reload", "houseSp1", "Villemstad_houseSp1_room", "goto", "goto1", "JoakimInRoom", -1);
		break;
		
		case "JoakimSeekSkull_3":
			PlaySound("Voice\English\hambit\Joakim Merriman-01.wav");
			dialog.text = "我们可以在这里交谈, 不用担心被偷听。 你最近拜访了我的邻居所罗门.施努尔。 我刚好路过, 船长, 请原谅, 不小心听到了你和所罗门谈话的一些细节。 太有趣了, 我不得不听完整件事! ";
			link.l1 = "一个害怕被别人偷听的偷听者, 嗯? ";
			link.l1.go = "JoakimSeekSkull_4";
		break;
		
		case "JoakimSeekSkull_4":
			dialog.text = "好了, 好了, 船长! 完全不是那样的! 所罗门是我的邻居, 他经常来看我。 尽管我们有宗教分歧, 我们还是好朋友! 我知道他的不幸遭遇... 就像威廉斯塔德的每个人一样! 所罗门从早到晚向任何愿意听的人诉说他的烦恼。 但够了。 老犹太人一定已经告诉你了, 一个古老的玉头骨和他的金子藏在某个未知的岛上。 他告诉你了吗? ";
			link.l1 = "他告诉我一个头骨, 没说它是玉做的。 他还说这是他祖父的头骨, 说实话, 我以为这要么是某种卡巴拉恐怖之物, 要么是这个老傻瓜脑子有问题。 ";
			link.l1.go = "JoakimSeekSkull_5";
		break;
		
		case "JoakimSeekSkull_5":
			dialog.text = "不, 船长, 所罗门很清醒, 只是有点古怪。 头骨确实存在。 这是一件古老的印第安宝藏, 尤姆.西米利的玉头骨! 我不知道老犹太人是怎么得到它的。 我已经找了半辈子了\n寻找所罗门藏他家钱的那个岛。 头骨一定在他的箱子里。 把那个玉头骨交给我, 我会付你五十万比索。 ";
			link.l1 = "五百? 这几乎不值得我花时间-等一下... 你是说五十万八里亚尔? 你在开玩笑吗? 我这辈子从来没见过那么多钱放在一个地方! ";
			link.l1.go = "JoakimSeekSkull_6";
		break;
		
		case "JoakimSeekSkull_6":
			dialog.text = "你还是个年轻人, 船长... 那么你加入吗? 你把玉头骨给我, 作为回报, 我给你五十万八里亚尔。 成交? ";
			link.l1 = "哈, 一个老头骨换一笔财富? 我当然加入。 ";
			link.l1.go = "JoakimSeekSkull_7";
		break;
		
		case "JoakimSeekSkull_7":
			dialog.text = "太好了。 与懂得利润的人合作总是令人愉快。 如果你需要我, 可以在我家找到我。 祝你好运! ";
			link.l1 = "谢谢你, 梅里曼博士。 我不会让你等太久的。 ";
			link.l1.go = "exit";
			npchar.quest.HWICHoll.Task = "true";
			LAi_SetOwnerType(npchar);
			AddDialogExitQuestFunction("CheckIslandCoordinates");//就是在这里我们将检查我们是否有岛屿的坐标, 并根据结果继续。 
		break;
		
		case "JoakimFindSkull":
			PlaySound("Voice\English\hambit\Joakim Merriman-02.wav");
			dialog.text = "哦, 是的! 你肯定对它的力量说得对... 但话够多了, 让我看看, 我不耐烦得发抖。 ";
			link.l1 = "给, 请拿去吧。 希望我没弄错? ";
			link.l1.go = "JoakimFindSkull_1";
			DelLandQuestMark(npchar);
		break;
		
		case "JoakimFindSkull_1":
			RemoveItems(PChar, "SkullAztec", 1);
			dialog.text = "啊, 不可思议! 是的, 就是它。 太好了, 船长, 非常好! 终于! 我终于拥有它了! 我等这一刻等了这么多年! ";
			link.l1 = "你答应的钱呢, 梅里曼博士? ";
			link.l1.go = "JoakimFindSkull_2";
		break;
		
		case "JoakimFindSkull_2":
			AddMoneyToCharacter(pchar, 500000);
			dialog.text = "哦, 是的, 当然! 五十万八里亚尔。 拿着, 你应得的。 ";
			link.l1 = "很高兴与你做生意。 很难相信这么小的东西能值这么多钱... ";
			link.l1.go = "JoakimFindSkull_3";
		break;
		
		case "JoakimFindSkull_3":
			dialog.text = "小东西? 你不知道你在说什么。 这是... bah, 你这庸俗的头脑几乎无法理解这个珍贵头骨背后不可思议的力量的重要性。 说实话, 我反正也没有时间可浪费\n谢谢你, 船长, 谢谢你所做的一切。 现在该说再见了。 我必须走了。 ";
			link.l1 = "再见, 梅里曼博士。 也许我们会再见面。 ";
			link.l1.go = "JoakimFindSkull_4";
		break;
		
		case "JoakimFindSkull_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			sld = characterFromId("Landlady");
			sld.Dialog.Filename = "Quest\HollandGambit\Joakim.c";
			sld.dialog.currentnode = "Landlady_2";
			SetFunctionTimerCondition("Caleuche_StartTotal", 0, 0, 180, false); // 卡莱乌切计时器
		break;
		
		case "JoakimSeekSkull_8":
			PlaySound("Voice\English\hambit\Joakim Merriman-01.wav");
			DelLandQuestMark(npchar);
			dialog.text = "我们可以在这里谈谈, 船长。 我知道你是我邻居所罗门的女儿阿比盖尔.施努尔的亲密伙伴。 她已经乘你的船去见她的情人了... 但那真的没关系。 ";
			link.l1 = "你想说什么, 博士? ";
			link.l1.go = "JoakimSeekSkull_9";
		break;
		
		case "JoakimSeekSkull_9":
			dialog.text = "如果你认识所罗门, 你一定知道他的沉船故事和他藏在某个未知岛上的失落宝藏。 他已经把这个故事告诉了威廉斯塔德的每个人。 ";
			link.l1 = "你为什么认为我既听说过又关心那个老犹太人的不幸? ";
			link.l1.go = "JoakimSeekSkull_10";
		break;
		
		case "JoakimSeekSkull_10":
			dialog.text = "你不喜欢所罗门吗? 我向你保证, 他只是一个无害的老怪人。 忘了他吧。 我们谈生意\n我和所罗门谈了好几次。 你无法想象当我发现这个老犹太人拥有一件我寻找多年的古老无价之宝时的感受! 这个疯狂的老人把它和他可怜的钱藏在某个岛上, 他甚至不记得位置\n我需要这件神器。 把它带给我, 我会付你五十万八里亚尔。 ";
			link.l1 = "五十万八里亚尔? 你一定是在开玩笑, 博士。 我这辈子从来没见过那么多钱放在一个地方! ";
			link.l1.go = "JoakimSeekSkull_11";
		break;
		
		case "JoakimSeekSkull_11":
			dialog.text = "你还年轻。 那么你加入吗? 你把 skull 给我, 作为回报, 我给你五十万八里亚尔。 除此之外, 你还可以拿走所罗门的钱。 根据老人的话, 那里一定有大约二十万比索... 所以你总共能得到七十万八里亚尔。 成交吗, 船长? ";
			link.l1 = "真让我死! 这当然是个交易! 但我该怎么找到这个岛? ";
			link.l1.go = "JoakimSeekSkull_12";
		break;
		
		case "JoakimSeekSkull_12":
			dialog.text = "和阿比盖尔谈谈。 也许她记得什么。 问问所罗门。 看, 如果我知道在哪里可以找到这个岛, 我就不会首先请求你的帮助了。 ";
			link.l1 = "我明白了。 抱歉问了个愚蠢的问题。 现在去找这个岛。 一定要等着给我付款。 ";
			link.l1.go = "JoakimSeekSkull_13";
		break;
		
		case "JoakimSeekSkull_13":
			dialog.text = "正是。 很高兴我们相互理解, 船长。 祝你搜索顺利。 你总能在我家找到我。 ";
			link.l1 = "我不会让你等太久的, 梅里曼博士。 再见! ";
			link.l1.go = "JoakimSeekSkull_14";
		break;
		
		case "JoakimSeekSkull_14":
			DialogExit();
			pchar.questTemp.HWIC.Self = "SeekAbiIsland";
			AddQuestRecord("Holl_Gambit", "3-55");
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload3", true);//关闭阿比的房间
			npchar.quest.HWICHoll.Task = "true";
			LAi_SetOwnerType(npchar);
			NextDiag.CurrentNode = "First time";
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
			AddMapQuestMarkCity("SentJons", false);
		break;
		
		// 卡莱乌切
		case "caleuche":
			PlaySound("Voice\English\LSC\Chymiset-03.wav");
			dialog.text = "是的。 祭祀的石头被我敌人的血染红了! 尤姆.西米利赐予了我指挥死者的力量! 有了这种力量, 我很快就会统治生者! ";
			link.l1 = "很有戏剧性, 梅里曼。 你打算用你的行尸军队做什么? 你在扮演凯撒, 试图征服世界吗? ";
			link.l1.go = "caleuche_1";
			CreateLocationParticles("large_smoke", "goto", "goto37", 0.5, 0, 0, "");
		break;
		
		case "caleuche_1":
			dialog.text = "安静, 你这个傻瓜! 你指望我在独白中透露我的秘密计划吗? 好吧, 我觉得没有理由不, 你不会在这次遭遇中幸存下来的! 我的不死军团将首先占领加勒比海所有黑暗的洞穴和地牢。 我的前哨将位于每个村庄, 等待我的信号。 当时机成熟时, 我的行尸将出征并覆盖生者的土地! \n可惜你活不到看到它了, 你这个可怜的伪君子, 你这个想成为主角的人! 你进入了我的圣所- 你不会活着出去的! 我将领导我的黑暗军队! ";
			link.l1 = "听着, 伙计, 你除了杰克和狗屎什么都领导不了, 杰克刚离开城镇。 ";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			PlaySound("Types\warrior04.wav");
			dialog.text = "哦吼吼! 你竟敢挑战我和我的骷髅仆人? ! 那就看看我到底是谁, 然后害怕吧! ";
			link.l1 = "来试试。 ";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			npchar.model = "Meriman_2";
			Characters_RefreshModel(npchar);
			PlaySound("Ambient\Teno_inside\teleporter.wav");
			dialog.text = "";
			link.l1 = "啊! 亲爱的耶稣! ";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			PlaySound("Voice\English\hambit\Joakim Merriman-04.wav");
			dialog.text = "现在你明白站在你面前的是谁了吗, 你这个呜咽的蛆虫? ! 我有笔账要和你算! 尤姆.西米利本人支持我! 我会吞下你的灵魂! ";
			link.l1 = "好吧, 笨蛋。 我们来跳舞。 ";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto37", "none", "", "", "Caleuche_MerrimanTeleport", -1);
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "goto", "goto37");
			pchar.questTemp.Caleuche.Merriman_hide = "true";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> 处理尝试打开箱子的反应块
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("你是个"+ GetSexPhrase("小偷, 先生! 卫兵, 抓住他","小偷, 小姐! 卫兵, 抓住她") +"!!! ", "看看那个! 我一转身, 你就决定检查我的箱子! 抓住小偷!!! ", "卫兵! 抢劫! 抓住小偷!!! ");
			link.l1 = "该死的! ";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- 处理尝试打开箱子的反应块
	}
}
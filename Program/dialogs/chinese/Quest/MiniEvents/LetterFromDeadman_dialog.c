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
			link.l1 = "没什么。";
			link.l1.go = "exit";
		break;
		
		case "Sailor_1":
			dialog.text = "你想干什么, "+GetSexPhrase("伙计","姑娘")+"? 要是你请我喝朗姆酒, 俺可不会拒绝。俺在这鬼地方的镇子里转了多少圈, 腿都快打结了。你叫什么名字? ";
			link.l1 = "船长"+GetFullName(pchar)+"。你不是‘Eagle’号的人吧? ";
			link.l1.go = "Sailor_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Sailor_2":
			if (pchar.sex == "man")
			{
				dialog.text = "而我——"+GetFullName(npchar)+"。没错, 我来自‘Eagle’号。船长, 你喜欢我们的船吗? ";
			}
			else
			{
				dialog.text = "船长? 呵呵……咳咳……我是安东尼奥·维伦塔。没错, 我是‘鹰号’上的人。我们的船吸引了你的注意吗, 船长? ";
			}
			link.l1 = "船就是船。你最好赶紧上船, 别在镇上闲逛——你们船长已经气得冒烟了。他打算在退潮前离港, 俺敢打赌, 小子, 他可不会等你。";
			link.l1.go = "Sailor_3";
		break;
		
		case "Sailor_3":
			dialog.text = "该死……我知道, 我知道……可我在这座城市还有些事没办完。想赚点杜布隆金币吗, 船长? ";
			link.l1 = "达布隆金币从不嫌多。不过, 赚金币是一回事, 惹麻烦又是另一回事。什么活儿? 快说吧。";
			link.l1.go = "Sailor_4";
		break;
		
		case "Sailor_4":
			dialog.text = "你看啊, 我在卸货舱的时候, 偶然发现了一封信。它看起来并不是故意藏起来的, 就那样躺在一些旧木桶中间。我们的弗吕特船可经历过不止一次登船劫掠, 谁也说不准这信是从哪儿来的。";
			link.l1 = "所以你找到了那封信, 但那又怎样? ";
			link.l1.go = "Sailor_5";
		break;
		
		case "Sailor_5":
			dialog.text = "这封信是写给来自波多贝罗的玛丽莎·卡尔德拉的。封口还用蜡封着……俺有种预感, 这事儿可不简单。也许是船长写的, 也许是商人写的……但绝对不是像俺这样的普通水手能收到的! 只是, 俺可没时间去找收信人——咱们的船长可不是爱开玩笑的人。你不想把它从俺手里买下吗? 一千比索就卖给你。你可是船长, 找这个小姐对你来说应该不难。谁知道呢, 说不定她会用黄金或者别的什么来报答你……你懂俺的意思吧? ";
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = "那好吧, 也许我会找到你的Marisa。反正我也没什么可失去的。 除了一千比索 把信交出来。";
				link.l1.go = "Sailor_6";
			}
			else
			{
				Notification_Money(false, 1000, "peso");
			}
			link.l2 = "抱歉, 伙计, 你得找别人了。我有更重要的事要做, 没空送信。";
			link.l2.go = "Sailor_end";
		break;
		
		case "Sailor_end":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Sailor_end");
		break;
		
		case "Sailor_6":
			dialog.text = "给你。好了, 保重, "+GetSexPhrase("伙计","姑娘")+", 我该走了——可不想让我的东西跟着‘鹰号’一起跑了。";
			link.l1 = "...";
			link.l1.go = "Sailor_accept";
			GiveItem2Character(PChar, "LFD_letter");
			AddMoneyToCharacter(pchar, -1000);
		break;
		
		case "Sailor_accept":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Sailor_accept");
			AddQuestRecord("LFD", "2");
		break;
		
		case "Dolores_1":
			dialog.text = "你是谁? 你想干什么? ";
			link.l1 = "我叫"+GetFullName(pchar)+"船长。我在找Marisa Caldera。";
			link.l1.go = "Dolores_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Dolores_2":
			sld = CharacterFromID("PortoBello_priest");
			dialog.text = "我不认识什么Marisa。你找错门了。现在赶紧走, 不然我就叫卫兵——他们会立刻把你扔出去。";
			link.l1 = "" + sld.name+"神父告诉我你是她的朋友。我有一封写给她的信。看这信的样子, 已经很晚了。我想亲自把它交给她。";
			link.l1.go = "Dolores_3";
		break;
		
		case "Dolores_3":
			dialog.text = "唉, 神父……他对所有人都太好了, 但很少看错人。你可以把信留给我。我会确保她能收到。";
			link.l1 = "请原谅, 小姐, 但我更愿意亲自送去。她可能会问我是如何得到它的, 以及为什么花了这么久才送到。";
			link.l1.go = "Dolores_4";
		break;
		
		case "Dolores_4":
			dialog.text = "你就指望我轻易相信你的善意? 我见过太多道貌岸然的无赖了。把信留下, 或者赶紧走人。";
			link.l1 = "我以船长的名义向你保证, 我不会伤害你或玛丽莎。而且, 你可以邀请卫兵或任何擅长武器的人参加我们的会面。我此行别无他意, 只是要亲自把这封信交给玛丽莎。";
			link.l1.go = "Dolores_5";
		break;
		
		case "Dolores_5":
			dialog.text = "好吧。明天晚上十一点以后再来。我不能保证她会同意见面, 但我会把你说的都转达给她。";
			link.l1 = "我会去的。很快见。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Dolores_1");
		break;
		
		case "Marisa_1":
			dialog.text = "你好, "+pchar.lastname+GetAddress_Form(NPChar)+"。你在找我吧, 我这不就来了。多洛雷斯说你有封信要给我? ";
			link.l1 = "您好, Caldera夫人。没错, 给您。唉, 看起来花了很长时间才送到您手上。";
			link.l1.go = "Marisa_2";
			DelLandQuestMark(npchar);
			TakeItemFromCharacter(pchar, "LFD_letter");
			notification("已交出: 给玛丽萨·卡尔德拉的信", "None");
		break;
		
		case "Marisa_2":
			dialog.text = "多洛雷斯……这是他的笔迹……拉米罗的笔迹! ";
			link.l1 = "...";
			link.l1.go = "Marisa_2_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
			sld = CharacterFromID("LFD_Dolores");
			LAi_CharacterEnableDialog(sld);
		break;
		case "Marisa_2_1":
			StartInstantDialog("LFD_Dolores", "Marisa_3", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_3":
			dialog.text = "但是这怎么可能? 已经两年了! ";
			link.l1 = "...";
			link.l1.go = "Marisa_3_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_3_1":
			StartInstantDialog("LFD_Marisa", "Marisa_4", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_4":
			dialog.text = "" + UpperFirst(GetAddress_Form(NPChar))+"船长……你是怎么得到它的? 你是在哪找到的? 我必须知道一切! 请把你知道的全部都告诉我。";
			link.l1 = "这封信是一个水手交给我的。他在自己船舱的黑暗角落里发现了它, 本想亲自交给你, 但因急事不得不匆忙返回自己的船。所以他让我来找你, 我这不就来了。我知道的就这些……";
			link.l1.go = "Marisa_5";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Marisa_5":
			dialog.text = "谢谢您, "+GetAddress_Form(NPChar)+"! 太感谢了! 请别走。我还想再和你聊聊, 不过首先……我得读这封信。";
			link.l1 = "当然, Caldera女士。我会在这里。";
			link.l1.go = "Marisa_6";
		break;
		
		case "Marisa_6":
			DialogExit();
			SetLaunchFrameFormParam("过了二十分钟, 玛丽萨读了信。", "Run_Function", 0, 4.0);
			SetLaunchFrameRunFunctionParam("LFD_Dolores_3", 0.0);
			LaunchFrameForm();
		break;
		
		case "Marisa_11":
			dialog.text = "Dolores……他是在最后一次航行前写的这封信。他想告诉我, 他有机会从伯利兹的一位商人那里购买一大批黑檀木, 但他的钱不够。于是他才借了这笔钱……两百枚达布隆金币……也正因为如此, 我现在无法安宁。";
			link.l1 = "...";
			link.l1.go = "Marisa_11_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_11_1":
			StartInstantDialog("LFD_Dolores", "Marisa_12", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_12":
			dialog.text = "这就说得通了……但可惜, 这并不能减轻你的负担。坚强点, Marisa。黑暗不会永远持续, 这笔债也不会一直缠着你。";
			link.l1 = "...";
			link.l1.go = "Marisa_12_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_12_1":
			StartInstantDialog("LFD_Marisa", "Marisa_13", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_13":
			dialog.text = "不, Dolores, 不会有的! Ramiro写信说他有一笔私藏……就在我们的老地方。如果还没人动过, 也许我能还清债务, 终于逃离这个噩梦。";
			link.l1 = "...";
			link.l1.go = "Marisa_13_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_13_1":
			StartInstantDialog("LFD_Dolores", "Marisa_14", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_14":
			dialog.text = "上主对你施予了仁慈! 祂听见了我们的祈祷……";
			link.l1 = "...";
			link.l1.go = "Marisa_14_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_14_1":
			StartInstantDialog("LFD_Marisa", "Marisa_15", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_15":
			dialog.text = "船长, 再次感谢您把这封信带给我。这对我意义重大……但我还得再请求您帮我一个忙。您看, 我的丈夫拉米罗曾是我的一切, 我从未寻求过其他男人的庇护。如今他离世, 我已无依无靠, 也没有自己的家人。\n我必须去到他的藏身之处——就在城外。但我太害怕独自前往, 亡夫的债主们正在追我。您能找到我并把信交给我, 已经表现得很有荣誉感……请, 再帮我一次吧。";
			link.l1 = "当然, Marisa, 我会护送你。你想什么时候出发? ";
			link.l1.go = "Marisa_16";
			link.l2 = "很抱歉, 女士, 但我在你们城市逗留的时间已经太长了。乡间散步并不在我的计划之内。";
			link.l2.go = "Marisa_end_1";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Marisa_end_1":
			dialog.text = "我明白了……你已经为我做的, 比我所期望的还要多。谢谢你, 船长, 祝你一路顺风。";
			link.l1 = "再见。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_end");
		break;
		
		case "Marisa_16":
			dialog.text = "谢谢您, 船长。明天黎明时分, 也就是七点之前来。我会准备好的。";
			link.l1 = "那就下次再见, 女士。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_1");
		break;
		
		case "Marisa_21":
			if (GetHour() >= 7 && GetHour() <= 19)
			{
				if (pchar.sex == "man")
				{
					dialog.text = "先生, 你来了……你真是个有荣誉感的人! 我们出发吧。我们的路要穿过丛林, 前往离蚊子湾不远的洞穴。";
				}
				else
				{
					dialog.text = "船长, 你来了……我就知道你会来。你知道吗, 这是我第一次见到一位指挥自己船只的女人。而且我已经看出来, 你无论荣誉还是高贵, 都丝毫不逊于任何男人! ";
				}
				link.l1 = "很好, 女士。那我们就别浪费时间了。紧跟着, 千万别走开。";
				link.l1.go = "Marisa_go_cove";
				if (startHeroType == 4) // если ГГ Элен
				{
					link.l1 = "谢谢你, Marisa。我的父亲曾是一名船长, 也是个正直的人——从小他就把这些理想灌输给我。";
					link.l1.go = "Marisa_22";
				}
			}
			else
			{
				dialog.text = "黎明时分来, 七点之前。我会准备好的。";
				link.l1 = "到时候见, 女士。";
				link.l1.go = "exit";
				NextDiag.TempNode = "Marisa_21";
			}
		break;
		
		case "Marisa_22":
			dialog.text = "是吗? 他和我的拉米罗遭遇了同样的命运吗? ";
			link.l1 = "他肯定更愿意手持利剑, 或在风暴中迎接终结。但命运另有安排——最终让他丧命的, 是一种他从未向任何人提起过的疾病。";
			link.l1.go = "Marisa_23";
		break;
		
		case "Marisa_23":
			dialog.text = "很遗憾你失去了亲人, "+pchar.name+"。主总是带走我们中最优秀的人……虽然我们未必总能明白原因, 但这都是祂的旨意。我们所能做的, 就是为他们不朽的灵魂安息祈祷。";
			link.l1 = "...";
			link.l1.go = "Marisa_24";
		break;
		
		case "Marisa_24":
			dialog.text = "我们走吧。我们的路要穿过丛林, 前往离蚊子湾不远的洞穴。";
			link.l1 = "当然。待在我身边, 一刻也别走远。";
			link.l1.go = "Marisa_go_cove";
		break;
		
		case "Marisa_go_cove":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Marisa_2");
		break;
		
		case "Marisa_31":
			dialog.text = "我们到了……以前下雨的时候, Ramiro和我曾在这里避雨, 那时我们还年轻, 他还不是我的丈夫。就在那时, 他告诉我, 无论付出什么代价, 他都要赢得我的心。";
			link.l1 = "很抱歉您得独自一人来到这里, 没有您的丈夫, 夫人。这种地方承载着许多回忆。我们四处看看吧——也许, 除了回忆之外, 还能找到拉米罗为最艰难时刻留下的东西。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_4");
		break;
		
		case "Marisa_32":
			dialog.text = "" + GetSexPhrase("+pchar.lastname+","+pchar.name+")+"……你找到什么了吗? 那是拉米罗留下的吗? 我都不知道哪种情况更让我害怕——是空的, 还是不够还债……";
			if (PCharDublonsTotal() >= 400 && GetCharacterItem(pchar, "jewelry2") >= 10 && GetCharacterItem(pchar, "jewelry3") >= 10 && CheckCharacterItem(PChar, "mushket1"))
			{
				link.l1 = "(shows) 给你, 这就是箱子里所有的东西。希望这些足以让你的命运变得更好。";
				link.l1.go = "Marisa_33";
				DelLandQuestMark(npchar);
			}
			else
			{
				link.l1 = "我还在翻找箱子。";
				link.l1.go = "exit";
				NextDiag.TempNode = "Marisa_32";
			}
		break;
		
		case "Marisa_33":
			dialog.text = "啊, 船长! 当然! 这就足够了! 但我不能让您的帮助没有回报。拿上一百枚达布隆金币吧。如果不是您, 我根本不会知道这个藏匿点, 还会一直躲着拉米罗债主派来的人……";
			link.l1 = "您真慷慨, 女士, 谢谢您。在我们这行, 黄金从不浪费。";
			link.l1.go = "Marisa_34";
			link.l2 = "不, 女士。你比我更需要这笔钱。重要的是你现在可以抛开烦恼, 安稳生活。对我来说, 这就足够了。";
			link.l2.go = "Marisa_35";
			RemoveDublonsFromPCharTotal(400);
			RemoveItems(pchar, "jewelry2", 10);
			RemoveItems(pchar, "jewelry3", 10);
			TakeItemFromCharacter(pchar, "mushket1");
			TakeItemFromCharacter(pchar, "obereg_7");
			TakeItemFromCharacter(pchar, "amulet_11");
			notification("已交出:护身符'奇玛鲁塔'", "None");
			notification("已交出: 护身符'渔夫'", "None");
			notification("已交出: 火绳滑膛枪", "None");
			notification("已交出: 钻石 (10)", "None");
			notification("已交出: 红宝石 (10)", "None");
		break;
		
		case "Marisa_34":
			dialog.text = "那么, "+GetSexPhrase("先生"," + pchar.name+")+", 我们该动身了。如果我在镇上被人发现, 可能有人在跟踪我们。最好别在这里逗留。";
			link.l1 = "你说得对, Marisa。我们走吧。";
			link.l1.go = "Marisa_naemnik";
			TakeNItems(pchar, "gold_dublon", 100);
		break;
		
		case "Marisa_35":
			dialog.text = "船长, 请……我丈夫一直保留这把武器是为了保护我们的家, 我相信——在您手中, 它一定会用于正义之事。拉米罗若知道它交到了在我绝望时救了我的人手里, 他一定会感到欣慰。";
			link.l1 = "好吧, Marisa, 谢谢你。你是个善良而正直的女人, 我真的很遗憾命运如此残酷地对待了你。";
			link.l1.go = "Marisa_36";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Marisa_36":
			dialog.text = "有时候, 上主会赐予我们艰难的日子, 甚至是艰难的岁月, 以考验我们的信仰, 但祂从不会抛弃那些走在正义道路上的人。祂派你来帮助我, 现在, 我希望我最大的麻烦很快就会过去。\n不过现在, 是时候回去了。我们在这里待得够久了, 继续留在这儿可能会有危险, 因为他们还在找我。";
			link.l1 = "当然, 女士, 我们走吧。";
			link.l1.go = "Marisa_naemnik";
			GiveItem2Character(pchar, "mushket1");
			GiveItem2Character(pchar, "obereg_7");
			GiveItem2Character(pchar, "amulet_11");
		break;
		
		case "Marisa_naemnik":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Marisa_6");
		break;
		
		case "Naemnik_1":
			dialog.text = "哈! 原来我们要找的人在这儿! 你真以为能像老鼠一样躲在这个破洞里, 让我找不到你吗? 我把整个镇子翻了好几遍, 结果你一直就在这儿"+GetSexPhrase(", 还敢背着我跟哪个小崽子约会。我的钱呢, 你个小骚货? 最好现在就交出来, 不然这洞就是你的埋骨之地。","。")+"";
			link.l1 = "...";
			link.l1.go = "Naemnik_1_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Naemnik"));
			CharacterTurnByChr(CharacterFromID("LFD_Naemnik"), CharacterFromID("LFD_Marisa"));
		break;
		case "Naemnik_1_1":
			StartInstantDialog("LFD_Marisa", "Naemnik_2", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Naemnik_2":
			dialog.text = "你……";
			link.l1 = "...";
			link.l1.go = "Naemnik_2_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Naemnik"));
			CharacterTurnByChr(CharacterFromID("LFD_Naemnik"), CharacterFromID("LFD_Marisa"));
		break;
		case "Naemnik_2_1":
			StartInstantDialog("LFD_Naemnik", "Naemnik_3", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Naemnik_3":
			dialog.text = "...";
			link.l1 = "所以你就是靠向女人讨债混饭吃的家伙? 看你选的行当, 脑子肯定不怎么灵光。你能自己找到这儿, 真是个奇迹——没跟着比你聪明的人走, 比如你自己的靴子, 简直不可思议。";
			link.l1.go = "Naemnik_4";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Naemnik_4":
			if (pchar.sex == "man")
			{
				dialog.text = "闭嘴, 英雄。轮到你之前, 我先处理她。她欠了五百二十五达布隆——这是她连本带利的债务。要么一次还清, 要么永远留在这儿——喂虫子。不过既然你这么正义, 你可以替她还钱, 那我就走人。";
				if (PCharDublonsTotal() >= 525)
				{
					link.l1 = "你以为自己能就这么闯进来, 侮辱一位女士, 无视我, 然后还能带着金币安然离开? 看起来你脑子不太灵光。不过我不会在女人面前动手。所以我的条件是: 你向Caldera夫人道歉, 拿上你的金币, 然后赶紧滚出去。否则, 老子就得好好教教你什么叫规矩了。";
					link.l1.go = "Naemnik_5";
					Notification_Money(true, 525, "dublon");
				}
				else
				{
					Notification_Money(false, 525, "dublon");
				}
			}
			else
			{
				dialog.text = "闭嘴, 等着轮到你。等我收拾完这个可怜虫再说。她欠了五百二十五枚达布隆——这是连本带利的债。既然你这么正义, 那你就替她还钱吧, 我这就走人。";
				if (PCharDublonsTotal() >= 525)
				{
					link.l1 = "好吧, 我可以原谅你粗鲁的举止, 甚至对我无礼的态度。但如果你想拿到你的金币并安然离开这里, 你必须向Caldera女士道歉。否则, 就看谁的武器更厉害了。相信我, 我可不是为了好看才带武器的。";
					link.l1.go = "Naemnik_5";
					Notification_Money(true, 525, "dublon");
				}
				else
				{
					Notification_Money(false, 525, "dublon");
				}
			}
			link.l2 = "很明显, 你脑子不太灵光, 居然以为我会乖乖等着轮到我。更别说你还真以为我会对你和你那帮人给卡尔德拉夫人带来的麻烦视而不见。";
			link.l2.go = "Naemnik_bitva";
		break;
		
		case "Naemnik_5":
			dialog.text = "那好吧, 随你。只要能不冒不必要的风险拿到钱, 我可没理由去拼命。把金币交出来——然后滚吧。";
			link.l1 = "首先, 向这位女士道歉。";
			link.l1.go = "Naemnik_6";
		break;
		
		case "Naemnik_6":
			dialog.text = "请原谅我, 女士。恶魔占了我的上风。";
			link.l1 = "...";
			link.l1.go = "Naemnik_7";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Naemnik"));
			CharacterTurnByChr(CharacterFromID("LFD_Naemnik"), CharacterFromID("LFD_Marisa"));
		break;
		
		case "Naemnik_7":
			dialog.text = "开心"+GetSexPhrase("","")+"? 把金子交出来, 老子就走。老子还有一堆事要忙, 没工夫在这儿跟你闲扯。";
			link.l1 = "拿上你的达布隆金币, 滚出去。";
			link.l1.go = "Naemnik_7_1";
			CharacterTurnByChr(npchar, pchar);
			RemoveDublonsFromPCharTotal(525);
		break;
		
		case "Naemnik_7_1":
			StartInstantDialog("LFD_Marisa", "Marisa_37", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterNationReputation(pchar, SPAIN, 10);
		break;
		
		case "Marisa_37":
			dialog.text = "船长, 真的, 我不明白……这是什么意思? ";
			link.l1 = "这意味着你现在不再欠债。你自由了。";
			link.l1.go = "Marisa_38";
			CharacterTurnByChr(npchar, pchar);
			
			sld = CharacterFromID("LFD_Naemnik");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", 5);
			sld.lifeday = 0;
		break;
		
		case "Marisa_38":
			dialog.text = "但是……我现在还凑不齐全部的钱还你。如果你能再等等……";
			link.l1 = "你不明白, Marisa。你不欠我什么。你也不再欠任何人什么了。你找到的钱对你会很有用。回到你以前的生活吧——教堂在等着你。";
			link.l1.go = "Marisa_39";
		break;
		
		case "Marisa_39":
			dialog.text = "我……我简直不敢相信。这样的事怎么可能发生, "+GetSexPhrase("先生","小姐")+"! 你为我花了那么多钱……就这么简单? 现在一切都结束了? 没有债务, 没有追捕? 告诉我, 这是真的吗? ";
			link.l1 = "的确如此, 女士。一切都结束了。你再也不欠任何人什么了。";
			link.l1.go = "Marisa_40";
		break;
		
		case "Marisa_40":
			dialog.text = "哦, 船长, 您真是高尚! 我觉得您仿佛是上帝派来的! 可我都不知道该怎么感谢您。您……彻底改变了我的人生, 而我……我还能为您做些什么呢? ";
			link.l1 = "你什么都不用做, Marisa。只要好好活着。不要害怕, 不要被过去的枷锁束缚。回到你的旧生活, 在其中寻找幸福——那才是对我最好的感谢。来吧, 我送你去镇上。";
			link.l1.go = "Naemnik_mir";
		break;
		
		case "Naemnik_bitva":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Naemnik_bitva");
		break;
		
		case "Naemnik_mir":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Naemnik_mir");
		break;
		
		case "Marisa_41":
			dialog.text = "你做了什么, 船长, 你把他杀了! ";
			link.l1 = "没错, 女士。我必须保护你和你的名誉……";
			link.l1.go = "Marisa_42";
		break;
		
		case "Marisa_42":
			dialog.text = "哎呀, 船长, 哪怕是像他那样的人, 夺取一条性命也是极其可怕且沉重的罪孽! 你得日夜祈祷, 才能稍稍洗净你那不朽灵魂上的污点。以上帝为证, 我本可以把我所有的东西都给他, 他就会离开……可现在……现在他的鲜血沾在你的手上, 只有天国才能决定你是否能被宽恕! ";
			link.l1 = "也许这是上帝的旨意。但咱们别再纠结这个了, 还是赶紧离开这个洞穴吧。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Naemnik_bitva_3");
		break;
		
		case "Marisa_51":
			dialog.text = "船长, 请允许我再次感谢您! 我会为您的健康与平安祈祷, "+pchar.name+"。请来我们的教堂——愿主宽恕您的所有罪孽, 并赐予您祝福。";
			link.l1 = "也许哪天我会去看看。还有记住, Marisa, 要是到时候见不到你那张开心的脸, 我可会很失望的。";
			link.l1.go = "Marisa_52";
		break;
		
		case "Marisa_52":
			dialog.text = "啊, "+GetAddress_Form(NPChar)+"……你对我真好。我真的很期待在我们的城镇再次见到你。不过现在, 请原谅我, 我迫不及待想整理好自己的生活, 并把这个好消息告诉多洛雷斯。";
			link.l1 = "当然, Marisa。再见。保重。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_In_Church");
		break;
		
		case "Marisa_54":
			dialog.text = "船长, 请允许我再次表达我无尽的感激! 您为我做了不可能完成的事! 为了报答您的善良与高尚, 我想告诉您这两年来我是如何躲避那些雇佣兵的。也许有一天, 这些经验对您也会有所帮助。";
			link.l1 = "谢谢您, 女士。在这种事情上, 知识和黄金一样珍贵。我在听。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Finish_In_Town_NaemnikAlive_2");
		break;
		
		case "Marisa_55":
			dialog.text = "这就是我这两年是怎么过的。在这个实力为尊的世界里, 懂得如何隐藏自己, 就能获得别人做梦都想不到的机会。";
			link.l1 = "谢谢你分享你的故事, Marisa。你经历了许多, 你的经验真的非常宝贵。";
			link.l1.go = "Marisa_56";
			AddCharacterExpToSkill(pchar, "Sneak", 500);
		break;
		
		case "Marisa_56":
			dialog.text = "我真心希望再次在我们的城镇见到你。请来我们的教堂——愿主宽恕你所有的罪孽, 并赐予你祂的祝福。";
			link.l1 = "也许哪天我会去看看。还有记住, Marisa, 要是我见不到你那张笑脸, 我可会很失望的。";
			link.l1.go = "Marisa_57";
		break;
		
		case "Marisa_57":
			dialog.text = "啊, 船长……您对我真好。不过现在, 请原谅, 我迫不及待想整理好自己的生活, 把这个好消息告诉多洛雷斯。";
			link.l1 = "当然, Marisa。再见。保重自己。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_In_Church");
			
			//слухи
			AddSimpleRumourCity(""+GetSexPhrase("你听说了吗?"+GetFullName(pchar)+"船长自己掏腰包帮寡妇卡尔德拉还清了债! 很少有人愿意为了别人舍下这么大一笔钱。在西班牙, 真正的骑士还没有绝迹! ","看到西班牙不仅有值得尊敬的骑士, 还有那些勇气与荣誉丝毫不输于男人的女子, 真让人心里高兴。")+"", "PortoBello", 7, 1, "");
			AddSimpleRumourCity("听说有个船长拿出自己的钱, 帮寡妇卡尔德拉清偿了亡夫留下的债务! 可不是谁都能做出这么高尚的事。真正的君子, 不是吗?", "PortoBello", 7, 1, "");
		break;
		
		case "Marisa_61":
			if (CheckAttribute(pchar, "questTemp.LFD_NaemnikDead"))
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = "船长, 真高兴又见到您! 我一直希望您能来。也许今天您有时间多待一会儿, 一起祈祷? ";
						link.l1 = "很高兴"+GetSexPhrase("","")+"见到你, Marisa。不过恐怕我现在不能久留。我记得自己对上主的职责, 但祈祷只能等一等了。";
						link.l1.go = "Marisa_62";
					break;

					case 1:
						dialog.text = "船长, 又是你! 总是很高兴见到你。看来上主不让你忘记去教堂的路……也许你最终还是会抽空祈祷吧? ";
						link.l1 = "Marisa, 见到你真好。但是我不能久留——我的事情刻不容缓。我相信主即使没有祷告也知晓我的心思。";
						link.l1.go = "Marisa_63";
					break;
				}
			}
			else
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = "船长, 能再次见到您真是太高兴了! 我每天都感谢上帝赐予您的善良。自从您帮助我后, 世界都变得明亮了。";
						link.l1 = "很高兴"+GetSexPhrase("","")+"见到你身体健康, Marisa。希望生活没有再给你带来什么不愉快的惊喜。你看起来开心多了。";
						link.l1.go = "Marisa_64";
					break;

					case 1:
						dialog.text = "船长, 见到您我太高兴了! 每次您来到我们的教堂, 我都感到心安。您带来了善行的光芒。";
						link.l1 = "我也很高兴"+GetSexPhrase("","")+"见到你真好, Marisa。你已经习惯了平静的生活, 还是偶尔会回首往昔? ";
						link.l1.go = "Marisa_65";
					break;
				}
			}
			SetTimerFunction("LFD_Marisa_HelloAgain", 0, 0, 1);
		break;
		
		case "Marisa_62":	
			dialog.text = "" + pchar.name+", 如果人人都一再推迟祈祷, 这个世界早就陷入黑暗了。暂时放下你的忧虑——忏悔会给予你继续前行的力量。";
			link.l1 = "我明白, Marisa, 但我现在真的做不到。我相信即使不说话, 主也会听见我的心声。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_62_1";
		break;
		
		case "Marisa_62_1":	
			dialog.text = "" + pchar.name+", 你改变主意了吗? 罪孽不会自行消失, 拖得越久, 它们就越沉重。";
			link.l1 = "唉, 我得走了。不过下次我保证会祈祷的。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_62_1";
		break;
		
		case "Marisa_63":	
			dialog.text = "但是信仰不仅仅是知道, 更在于行动! 你不能一直拖延救赎之路。难道你不想感受摆脱罪恶重负后的轻松吗? ";
			link.l1 = "也许吧, 但不是现在。愿主聆听我的祈祷, 即使这祷告必须等待。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_63_1";
		break;
		
		case "Marisa_63_1":	
			dialog.text = "船长, 你不觉得拖延忏悔本身就是一种罪吗? 有一天可能就来不及了。";
			link.l1 = "也许吧, 但恐怕我今天没有时间。信仰与我同在, 主即使没有祷告也能看到我的忏悔。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_63_1";
		break;
		
		case "Marisa_64":	
			dialog.text = "是的, 多亏了你, 我又能自由呼吸了。愿上主保佑你和你的旅途。也许你愿意和我一起祈祷吗? ";
			link.l1 = "我相信你的祈祷已经足够有力量了。最重要的是, 你现在身边只有善意。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_64_1";
		break;
		
		case "Marisa_64_1":	
			dialog.text = "" + pchar.name+", 你最终改变主意了吗? 我们要向造物主祈祷吗? ";
			link.l1 = "很遗憾, Marisa, 我现在得走了, 还有事情要做。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_64_1";
		break;
		
		case "Marisa_65":	
			dialog.text = "我只想向前看。现在我有了未来, 这一切都多亏了你。也许我们应该一起感谢上帝? ";
			link.l1 = "我觉得你会比我做得更好。最重要的是, 你的祈祷能带给你内心的平静。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_65_1";
		break;
		
		case "Marisa_65_1":	
			dialog.text = "" + pchar.name+", 也许我能劝你至少念一遍祷告? ";
			link.l1 = "原谅我, Marisa, 但遗憾的是, 我现在实在没有时间。也请为我祈祷吧。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_65_1";
		break;
		
		case "Marisa_Ne_Ta_Peshera":	
			dialog.text = "船长, 这里不是地方。我们要找的洞穴在蚊子湾附近。";
			link.l1 = "...";
			link.l1.go = "Marisa_Ne_Ta_Peshera_1";
		break;
		
		case "Marisa_Ne_Ta_Peshera_1":	
			DialogExit();
			NextDiag.TempNode = "Marisa_31";
			DeleteQuestCondition("LFD_Ne_Ta_Peshera");
			
			sld = CharacterFromID("LFD_Marisa");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
	}
}
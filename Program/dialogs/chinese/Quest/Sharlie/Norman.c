// 亚伯拉罕.诺曼
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
		
		case "norman_us":
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				dialog.text = LinkRandPhrase("你需要什么, 伙计? 走你的路, 忙你的事。 别烦我。 ","嘿, 嘿, 伙计。 去散步吗? 好吧, 你继续走, 别打扰亚伯拉罕先生。 他也去散步了, 呼吸点新鲜海风。 ","你好, 朋友。 想聊天? 但有个问题: 我没心情聊天。 所以去找别人麻烦吧, 去酒馆喝点朗姆酒... ");
				link.l1 = "听着, 亚伯拉罕, 你最近在宝藏岛有没有遇到一个叫米格尔.迪乔索的人? 他在这里挺有名的。 ";
				link.l1.go = "tieyasal";
				break;
			}
			dialog.text = NPCStringReactionRepeat(LinkRandPhrase("你需要什么, 伙计? 走你的路, 忙你的事。 别烦我。 ","嘿, 嘿, 伙计。 去散步吗? 好吧, 你继续走, 别打扰亚伯拉罕先生。 他也去散步了, 呼吸点新鲜海风。 ","你好, 伙计。 想聊天? 但有个问题: 我没心情聊天。 所以去找别人麻烦吧, 去酒馆喝点朗姆酒... "), LinkRandPhrase("嘿, 水手。 怎么, 你头铁吗? 我以为我说得很清楚了。 ","伙计, 去休息吧。 你好像有点耳背。 ","嘿伙计, 怎么, 你傻吗? 我已经跟你说得很清楚了。 "), "兄弟, 别惹我生气。 我这辈子宰过太多陆地佬了, 多一个少一个没区别。 ", "好吧, 你惹毛我了。 现在要么拔出你生锈的剑, 要么赶紧跑。 我推荐第二个选择... ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("好吧, 朋友。 我不打扰你了。 ", "好, 好。 我知道了... ", "哇, 你看起来像海上的雷神! 好吧, 我走了。 ", "什么? ! ", npchar, Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "norman_us";
		break;
		
		case "norman_fes":
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				dialog.text = LinkRandPhrase("你需要什么, 伙计? 走你的路, 忙你的事。 别烦我。 ","嘿, 嘿, 伙计。 去散步吗? 好吧, 你继续走, 别打扰亚伯拉罕先生。 他也去散步了, 呼吸点新鲜海风。 ","你好, 伙计。 想聊天? 但有个问题: 我没心情聊天。 所以去找别人麻烦吧, 去酒馆喝点朗姆酒... ");
				link.l1 = "听着, 亚伯拉罕, 你最近在宝藏岛有没有遇到一个叫米格尔.迪乔索的人? 他在这里挺有名的。 ";
				link.l1.go = "tieyasal";
				break;
			}
			switch (hrand(5))
			{
				case 0:
					dialog.text = "站住! 我是这个岛的总督。 怎么, 你不相信我? ! ";
					link.l1 = "我当然信! 谁不认识宝藏岛的总督... ";
					link.l1.go = "norman_fes0_fight";
					link.l2 = "哈, 你干脆自称舰队司令得了, 我肯定信! ";
					link.l2.go = "norman_fes0_peace";
				break;
				
				case 1:
					dialog.text = "立正! 看 —巴巴里戈上将! 你不认识我这把著名的骑兵剑吗? ";
					link.l1 = "抱歉, 上将先生! 从现在起, 我会更留心的。 ";
					link.l1.go = "norman_fes1_peace";
					link.l2 = "你的骑兵剑确实有名。 可惜握在一个傻瓜手里。 ";
					link.l2.go = "norman_fes1_fight";
				break;
				
				case 2:
					dialog.text = "如你所见, 我正在流放中。 我在等待 Monk 将军的进一步通知。 请不要泄露我隐藏的皇室身份。 克伦威尔的情报部门耳目众多。 ";
					link.l1 = "当然, 陛下。 没人会知道查理二世躲在西印度。 ";
					link.l1.go = "norman_fes2_fight";
					link.l2 = "那我就是英诺森十世教皇了。 ";
					link.l2.go = "norman_fes2_peace";
				break;
				
				case 3:
					dialog.text = "你怎么了, Blaze? 我找了你两天。 你完全忘了你父亲尼古拉斯! ";
					link.l1 = "我没时间陪你, 父亲! 我忙得很。 ";
					link.l1.go = "norman_fes3_peace";
					link.l2 = "你认错人了, 先生。 我叫" +GetFullName(pchar)+ "。 ";
					link.l2.go = "norman_fes3_fight";
				break;
				
				case 4:
					dialog.text = "嘘... 我是戴维.琼斯。 告诉我, 你害怕死亡吗? ";
					link.l1 = "我当然怕, 琼斯先生。 尤其是宿醉之后。 ";
					link.l1.go = "norman_fes4_fight";
					link.l2 = "一人之死是悲剧, 千人之死只是统计数字。 ";
					link.l2.go = "norman_fes4_peace";
				break;
				
				case 5:
					dialog.text = "我急着完成我的新剧本。 你必须帮我完成这句话‘生存还是毁灭’?!";
					link.l1 = "这是个问题! 我们是忍受冒犯继续前行... ";
					link.l1.go = "norman_fes5_fight";
					link.l2 = "当然是喝酒。 但在妓院染上病我也不奇怪! ";
					link.l2.go = "norman_fes5_peace";
				break;
			}
		break;
		
		case "norman_fes0_fight":
			dialog.text = "你到底在说什么? ‘宝藏岛’? 你还不如叫它百慕大! 这个岛以我命名, 叫诺曼岛, 你别忘了! 我得教教你地理... ";
			link.l1 = "哈! 你什么意思? ! ";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes0_peace":
			dialog.text = "你说得对, 水手。 我确实是巴巴里戈上将, 但这是我们之间的秘密。 准备行军, 我们很快出发, 这对你有好处。 ";
			link.l1 = "我非常感激! ";
			link.l1.go = "norman_fes0_exit";
		break;
		
		case "norman_fes0_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 12)
			{
				GiveItem2Character(pchar, "pistol2");
				Log_Info("你获得了一把三管霰弹枪");
			}
			else
			{
				if (GetDataDay() == 23 && GetDataMonth() == 2)
				{
					GiveItem2Character(pchar, "mushket1");
					Log_Info("你获得了一把火绳滑膛枪");
				}
				else
				{
					GiveItem2Character(pchar, "cartridge");
					Log_Info("你获得了一个纸弹药筒");
				}
			}
		break;
		
		case "norman_fes1_fight":
			dialog.text = "现在我们看看谁是傻瓜。 接招! ";
			link.l1 = "你认真的? ! ";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes1_peace":
			dialog.text = "我怎么跟你说的! 来, 为我的健康干杯。 ";
			link.l1 = "干杯, 上将! ";
			link.l1.go = "norman_fes1_exit";
		break;
		
		case "norman_fes1_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 13)
			{
				GiveItem2Character(pchar, "gold_dublon");
				Log_Info("你获得了一枚金杜布隆");
			}
			else
			{
				if (GetDataDay() == 1 && GetDataMonth() == 4)
				{
					GiveItem2Character(pchar, "chest");
					Log_Info("你获得了一箱杜布隆");
				}
				else
				{
					AddMoneyToCharacter(pchar, 5);
				}
			}
		break;
		
		case "norman_fes2_fight":
			dialog.text = "我让你不要泄露我的名字! 现在我得把你这个危险的证人处理掉... ";
			link.l1 = "哦, 我等这个很久了! ";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes2_peace":
			dialog.text = "原谅我, 大人! 我没认出你这身装扮。 请接受这个来自真正天主教徒的小礼物。 ";
			link.l1 = "真是疯言疯语... ";
			link.l1.go = "norman_fes2_exit";
		break;
		
		case "norman_fes2_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 14)
			{
				GiveItem2Character(pchar, "amulet_10");
				Log_Info("你获得了奇迹工作者护身符");
			}
			else
			{
				if (GetDataDay() == 25 && GetDataMonth() == 12)
				{
					GiveItem2Character(pchar, "totem_04");
					Log_Info("你获得了帮凶护身符");
				}
				else
				{
					GiveItem2Character(pchar, "Mineral3");
					Log_Info("你获得了一支蜂蜡蜡烛");
				}
			}
		break;
		
		case "norman_fes3_fight":
			dialog.text = "所有人都针对我! 我抓到一个长得像我儿子的间谍! 肯定是托马斯派他来打瞎我另一只眼的! ";
			link.l1 = "滚开, 傻瓜! ";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes3_peace":
			dialog.text = "你累了, 气色也不好, 小家伙。 去接受治疗吧。 ";
			link.l1 = "谢谢! ";
			link.l1.go = "norman_fes3_exit";
		break;
		
		case "norman_fes3_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 15)
			{
				GiveItem2Character(pchar, "potion4");
				Log_Info("你获得了一瓶药水");
			}
			else
			{
				if (GetDataDay() == 19 && GetDataMonth() == 6)
				{
					GiveItem2Character(pchar, "talisman8");
					Log_Info("你获得了蝎子护身符");
				}
				else
				{
					GiveItem2Character(pchar, "potion1");
					Log_Info("你获得了治疗精华")
				}
			}
		break;
		
		case "norman_fes4_fight":
			dialog.text = "别害怕, 伙计。 看, 死亡一点都不可怕... ";
			link.l1 = "看来你不是在开玩笑! ";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes4_peace":
			dialog.text = "显然你不怕。 我就知道。 这就是勇气! ";
			link.l1 = "你是个有趣的老头... ";
			link.l1.go = "norman_fes4_exit";
		break;
		
		case "norman_fes4_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 17)
			{
				GiveItem2Character(pchar, "cirass6");
				Log_Info("你获得了食火者背心");
			}
			else
			{
				if (GetDataDay() == 1 && GetDataMonth() == 1)
				{
					GiveItem2Character(pchar, "cirass3");
					Log_Info("你获得了一件阅兵胸甲");
				}
				else
				{
					GiveItem2Character(pchar, "Mineral18");
					Log_Info("你获得了一些烟草");
				}
			}
		break;
		
		case "norman_fes5_fight":
			dialog.text = "你是个蹩脚的诗人, 水手。 难道你的剑比舌头更灵活? ";
			link.l1 = "天哪! 你那把骑兵剑可不是假的! ";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes5_peace":
			dialog.text = " dang! 你过得挺顺利嘛! 你的想象力怎么样! ";
			link.l1 = "再说一遍。 ";
			link.l1.go = "norman_fes5_exit";
		break;
		
		case "norman_fes5_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 16)
			{
				GiveItem2Character(pchar, "potionrum");
				Log_Info("你获得了一瓶朗姆酒");
			}
			else
			{
				if (GetDataDay() == 28 && GetDataMonth() == 11)
				{
					GiveItem2Character(pchar, "totem_01");
					Log_Info("你获得了铁喉护身符");
				}
				else
				{
					GiveItem2Character(pchar, "Mineral17");
					Log_Info("你获得了一个玻璃烧瓶");
				}
			}
		break;
		
		case "norman_fight_again":
			dialog.text = "啊哈, 我认出你了! 哈哈! ";
			link.l1 = "又来... ";
			link.l1.go = "fight";
		break;
		
		case "norman_fes_again":
			dialog.text = "好了, 伙计, 我们聊完了。 现在走吧。 ";
			link.l1 = "如你所说... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "norman_fes_again";
		break;
		
		case "tieyasal":
			dialog.text = "迪乔索? 你找他干什么, 嗯? ";
			link.l1 = "我需要他, 就是需要他。 你见过他吗? ";
			link.l1.go = "tieyasal_1";
			link.l2 = "你问我需要他干什么? 米格尔是我的老伙计, 可以说是朋友。 他应该... ";
			link.l2.go = "tieyasal_2";
			link.l3 = "我想让他像之前给‘鲨鱼’多德森那样, 帮我弄艘新船。 ";
			link.l3.go = "tieyasal_3";
			if (CheckAttribute(pchar, "questTemp.Ksochitam.SQCapBookRead")) // 读过圣塔-奎特里亚日志
			{
				link.l4 = "米格尔.迪乔索杀了人, 所以我在找他。 ";
				link.l4.go = "tieyasal_4";
			}
			npchar.quest.Tieyasal = "true";
		break;
		
		case "tieyasal_1":
			dialog.text = "你就是需要他... 你就只是需要他! 你只需要米格尔.迪乔索! 不, 我没见过他, 很久没见了。 我帮不了你, 水手。 ";
			link.l1 = "嗯... 好吧, 再见。 ";
			link.l1.go = "exit";
		break;
		
		case "tieyasal_2":
			dialog.text = "你说是朋友... 他好像交了一大堆朋友。 他很快就会少一个朋友了... ";
			link.l1 = "嘿, 老头。 你怎么了? ";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "tieyasal_3":
			dialog.text = "是的, 无论怎么看, 迪乔索都是这方面的行家。 但我不知道他在哪里。 他来过又走了。 所以去亚历克苏斯那里吧, 水手。 他会为你拼一艘很棒的船。 ";
			link.l1 = "嗯... 谢谢你的建议, 伙计。 ";
			link.l1.go = "exit";
		break;
		
		case "tieyasal_4":
			dialog.text = "迪乔索杀了谁, 让你这么找他, 嗯伙计? ";
			link.l1 = "";
			Link.l1.edit = 8;
			link.l1.go = "tieyasal_5";
		break;
		
		case "tieyasal_4_1":
			dialog.text = "你什么意思? 他到底杀了哪个Sharp? 你知道, Sharp家的人很多。 ";
			link.l1 = "";
			Link.l1.edit = 8;
			link.l1.go = "tieyasal_5";
		break;
		
		case "tieyasal_5":
			sTemp = GetStrSmallRegister(dialogEditStrings[8]);
			if (sTemp == "blaze sharp")
			{
				dialog.text = "嘘... (环顾四周) 所以你也认为Blaze Sharp是被迪乔索杀的? ";
				link.l1 = "是的。 我不仅有怀疑, 还有确凿证据。 他日志里的记录... ";
				link.l1.go = "tieyasal_6";
				break;
			}
			if (sTemp == "sharp")
			{
				dialog.text = "继续说, 小水手... ";
				link.l1 = "你什么意思? 告诉我更多。 ";
				link.l1.go = "tieyasal_4_1";
				break;
			}
			dialog.text = "啊... 好吧。 他杀了人, 就这样。 你知道这里有多少杀手吗? 遍地都是! 不, 水手。 我很久没见过迪乔索了, 帮不了你。 ";
			link.l1 = "可惜... ";
			link.l1.go = "exit";
		break;
		
		case "tieyasal_6":
			dialog.text = "安静点, 伙计。 你叫什么名字, 嗯? 我好像忘了... ";
			link.l1 = pchar.name+ "船长。 ";
			link.l1.go = "tieyasal_7";
		break;
		
		case "tieyasal_7":
			dialog.text = "听着, " +pchar.name+ "。 迪乔索杀了可怜的Blaze, 我亲眼所见, 是的。 但他们不相信我, 他们觉得我疯了。 我曾经是Nicholas Sharp船队里最好的登船官! 好时光! 但最终我失去了爪子。 蹄子和镜片, 被困住了。 \n什么? 啊, 对! 所有人都以为是‘鲨鱼’干的, 但不是。 不, 不是。 那里有一颗鲨鱼牙, 多德森的护身符, 但却是迪乔索栽赃的。 \n他肯定是在和多德森一起乘‘财富号’护卫舰航行时偷的。 那天我没睡好, 出去散步, 看到迪乔索溜进Sharp的住所, 听到有人尖叫然后呻吟。 不久迪乔索离开住所, 手上有血。 \n他们不相信我, 因为那天岛上没有迪乔索, 而‘鲨鱼’在。 他们找到了他的牙齿。 但我看到了迪乔索, 我确定。 没人知道他那天在岛上。 ‘幸运儿’是个非常狡猾可怕的人... ";
			link.l1 = "你不是第一个叫迪乔索‘幸运儿’的人。 为什么? 这是他的绰号吗? ";
			link.l1.go = "tieyasal_8";
		break;
		
		case "tieyasal_8":
			dialog.text = "你不懂西班牙语吗, 伙计? ‘Dichoso’在天主教语言里是‘幸运’的意思。 幸运的米格尔, 米格尔.幸运。 他的名字就是这个意思。 ";
			link.l1 = "米格尔.幸运? ... 嗯, 这让我想起了什么。 嗯, 这个短语听起来很熟悉... ";
			link.l1.go = "tieyasal_9";
		break;
		
		case "tieyasal_9":
			dialog.text = "好吧, 尽管他姓迪乔索, 但我还是不认为他是西班牙人。 不, 不, 他不是西班牙人, 虽然他看起来像西班牙人。 ";
			link.l1 = "那他可能是什么人? 英国人, 法国人? ";
			link.l1.go = "tieyasal_10";
		break;
		
		case "tieyasal_10":
			dialog.text = "我不是这个意思, 水手... 哦, 原谅我, 船长。 是的, 迪乔索法语说得非常好, 不比你差, 英语也一样。 但他血管里流着印第安人的血, 我这辈子见过很多这样的人。 虽然不容易看出来, 但他是混血儿, 我向你保证。 ";
			link.l1 = "他说印第安语吗? ";
			link.l1.go = "tieyasal_11";
		break;
		
		case "tieyasal_11":
			dialog.text = "哦, 天知道。 也许吧。 不过, 等等, 他确实说! 他过去经常用某种奇怪的语言说些奇怪的句子, 还做着可怕的圣人脸, 说的时候鼓起腮帮子。 比如, 他会说‘cogito ergo sum!’然后翻白眼, 观察水手们的反应。 或者他会惊呼‘aut Caesar, aut nihil!’他还说了很多其他的, 我不记得所有内容了。 ";
			link.l1 = "那不是印第安语, 那是拉丁语。 拉丁语... 拉丁语? ! 我的天! ";
			link.l1.go = "tieyasal_12";
		break;
		
		case "tieyasal_12":
			dialog.text = "你为什么这么激动, 伙计? 你喊什么? 被蛇咬了还是怎么了? 蛇去哪了? ";
			link.l1 = "为什么我一开始没看出来! 一切都明摆在我面前! 拉丁语! 米格尔... 米格尔.幸运!!! ";
			link.l1.go = "tieyasal_13";
		break;
		
		case "tieyasal_13":
			dialog.text = "嘿, 伙计。 你能不能别喊了, 人们都在看我们。 你怎么了, 水手... 抱歉, 船长? ";
			link.l1 = "我知道米格尔.迪乔索到底是谁了。 他不是西班牙人, 他是法国人! 哦, 我太盲目了! ";
			link.l1.go = "tieyasal_14";
		break;
		
		case "tieyasal_14":
			dialog.text = "不, 笨蛋。 他不是法国人, 他是混血儿。 他的白人父亲和一个加勒比的阿拉瓦克或米斯基托小印第安女孩, 甚至可能是伊察人, 搞在一起, 于是神圣的米格尔.迪乔索就诞生了。 你看不出来, 但我看得出来, 他眼睛里写着呢... ";
			link.l1 = "我们先把他的出身问题放在一边, 亚伯拉罕? ! 他在哪里? 他来过这里吗? ! ";
			link.l1.go = "tieyasal_15";
		break;
		
		case "tieyasal_15":
			dialog.text = "嘘... 是的, 他来过, 但他走了, 现在不在宝藏岛了。 ";
			link.l1 = "他来这里干什么? 他有什么船? ";
			link.l1.go = "tieyasal_16";
		break;
		
		case "tieyasal_16":
			dialog.text = "他的船是一艘大帆船, 一艘大型战帆。 他来这里干什么... 嗯, 他四处打听问题。 但我偷听了他的谈话, 是的! 他在找某个查尔斯.德.莫尔。 对, 就是这个名字, 查尔斯.德.莫尔。 等等, 那是你, 查尔斯.德.莫尔! 他在找你, 伙计。 ";
			link.l1 = "你知道为什么吗? ";
			link.l1.go = "tieyasal_17";
		break;
		
		case "tieyasal_17":
			dialog.text = "当然不是来酒馆和你喝朗姆酒的。 他一直在说要抓住你, 是的, 抓住你! 你有大麻烦了, 船长! ";
			link.l1 = "我不怀疑... ";
			link.l1.go = "tieyasal_18";
		break;
		
		case "tieyasal_18":
			dialog.text = "那你呢? 为什么找他? 哦, 我明白了, 明白了: 杀了他! 杀了那个混蛋! 为Blaze Sharp报仇! Blaze是个了不起的人, 我记得他, 小时候就像尼古拉斯一样。 ";
			link.l1 = "迪乔索去哪了? ";
			link.l1.go = "tieyasal_19";
		break;
		
		case "tieyasal_19":
			dialog.text = "他去了布鲁维尔德。 他说查尔斯.德.莫尔应该在森林恶魔的翅膀下寻找。 但他留下了人在这里... 等等, 我想你已经被注意到了! ";
			link.l1 = "谁注意到我了? ";
			link.l1.go = "tieyasal_20";
		break;
		
		case "tieyasal_20":
			dialog.text = "迪乔索的人。 他下令在这里监视你。 哦, 我知道, 我知道! 小心, 船长: 宝藏岛的礁石周围有船, 他们在那里等你的脑袋。 船长狡猾得像只狐狸, 别被他骗了。 ";
			link.l1 = "我会尽力... ";
			link.l1.go = "tieyasal_21";
		break;
		
		case "tieyasal_21":
			dialog.text = "还有一件事: 给, 拿着我的骑兵剑。 拿着, 拿着, 你会需要的。 这正是巴巴里戈船长的剑, 一把出色的 blade, 群岛上最好的。 别不好意思, 拿着。 为Blaze Sharp报仇! ";
			link.l1 = "谢谢你, 亚伯拉罕。 ";
			link.l1.go = "tieyasal_22";
		break;
		
		case "tieyasal_22":
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			RemoveItems(npchar, "blade_29", 1);
			sTemp = GetBestGeneratedItem("blade_29");
			GiveItem2Character(pchar, sTemp);
			sld = ItemsFromID(sTemp);
			sld.Balance = 2.0;
			GiveItem2Character(npchar, "blade_19"); 
			EquipCharacterbyItem(npchar, "blade_19");
			Log_Info("你获得了巴巴里戈之剑");
			PlaySound("interface\important_item.wav");
			dialog.text = "现在走吧, 你被监视了。 表现得聪明点, 或者愚蠢点, 没关系, 只要小心! ";
			link.l1 = "谢谢, 伙计。 你都不知道你帮了我多大的忙。 祝你好运! ";
			link.l1.go = "tieyasal_23";
		break;
		
		case "tieyasal_23":
			DialogExit();
			pchar.questTemp.Tieyasal.MigelKnow = "true";
			AddQuestRecord("Tieyasal", "4");
			pchar.quest.Tieyasal_ITAttack.win_condition.l1 = "location";
			pchar.quest.Tieyasal_ITAttack.win_condition.l1.location = "Bermudes";
			pchar.quest.Tieyasal_ITAttack.function = "Tieyasal_CreateITShips";
			pchar.questTemp.Tieyasal = "islatesoro";
		break;
		
		case "fight":
			iTemp = 20-sti(GetCharacterItem(npchar, "potion2"));
			TakeNItems(npchar, "potion2", iTemp);
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
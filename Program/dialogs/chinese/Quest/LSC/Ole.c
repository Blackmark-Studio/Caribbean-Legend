// 奥莱.克里斯蒂安森 - 白男孩
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "你想要什么? ";
			link.l1 = "没什么。 ";
			NextDiag.TempNode = "First time";
		break;
		
		// 在商店 - 首次见面
		case "store":
			dialog.text = "哎呀... 你好, 大叔。 你有白色珠子吗? 给我白色珠子... ";
			link.l1 = "嗯。 日安。 你是... 白男孩吗? ";
			link.l1.go = "store_1";
		break;
		
		case "store_1":
			dialog.text = "珠子! 给白男孩的白色珠子! 你有白色珠子吗, 大叔? ";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "嗯, 我没有珠子, 但我可以给你这颗珍珠。 它是白色的, 就像珠子一样。 你觉得可以吗? ";
				link.l1.go = "store_2";
			}
			link.l2 = "不, 我没有白色或红色的珠子。 我不是戴珠子的女孩或印第安人。 告诉我... ";
			link.l2.go = "pearl";
			sld = characterFromId("Axel");
			sld.quest.ole_pearl = "true";
		break;
		
		case "pearl":
			dialog.text = "珠子! 白色珠子! 没珠子 - 不说话。 坏大叔... 给我珠子! ";
			link.l1 = "该死! 真是个疯子! 蛇眼和奇米塞特说得对 - 他脑子不好使... 他到底需要什么样的珠子? ";
			link.l1.go = "exit";
			NextDiag.TempNode = "pearl_repeat";
		break;
		
		case "pearl_repeat":
			dialog.text = "给个珠子吧, 大叔。 好大叔... 白色珠子! ";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "给, 拿好你的珠子。 这是你想要的吗? ";
				link.l1.go = "store_2";
			}
			link.l2 = "哦, 该死的... ";
			link.l2.go = "exit";
			NextDiag.TempNode = "pearl_repeat";
		break;
		
		case "store_2":
			RemoveItems(pchar, "jewelry52", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "是的, 是的! 就是这个! 大叔给了珠子! 谢谢, 好人! 现在奥莱又多了一颗珠子。 很快就能见到妈妈了... ";
			link.l1 = "为你高兴。 那么, 我们现在可以谈谈了吗? ";
			link.l1.go = "store_3";
			sld = characterFromId("Axel");
			DeleteAttribute(sld, "quest.ole_pearl");
		break;
		
		case "store_3":
			dialog.text = "当然, 好人。 你是好人吗, 大叔? 我们会成为朋友。 奥莱很高兴聊天。 你叫什么名字? ";
			link.l1 = "我叫" +pchar.name+ "。 奥莱, 有个人跟我提起过你, 他现在不在这里了。 他说你帮过他, 也能帮我。 ";
			link.l1.go = "store_4";
		break;
		
		case "store_4":
			dialog.text = "大叔给奥莱珠子 - 是好大叔。 奥莱喜欢帮助好人。 好人不多 - 到处都是坏大叔。 我会帮你, 当然。 我喜欢帮助别人。 ";
			link.l1 = "太好了! 我们现在是朋友了。 奥莱, 告诉我, 你还记得一个红皮肤。 戴华丽羽毛帽子的人吗? 他说你很久以前救过他。 ";
			link.l1.go = "store_5";
		break;
		
		case "store_5":
			dialog.text = "我记得那个大叔。 他是好人。 我救了他。 我带他去了雕像那里。 最近我又从装食物的货舱里救了另一个好人。 我把他从坏舰队司令的大叔们手里救了出来。 他们会杀了他的。 我想带他去雕像那里, 但他完全拒绝了。 ";
			link.l1 = "从货舱里? 呵, 我想我知道你说的是谁... 我也认识这个大叔。 告诉我, 奥莱, 你救的那个人是谁? ";
			link.l1.go = "store_6";
		break;
		
		case "store_6":
			dialog.text = "他叫内森大叔。 他病得很重, 非常非常重。 奥莱找到他时, 他几乎走不动路。 ";
			link.l1 = "确实... 奇怪的是他居然还能做到。 ";
			link.l1.go = "store_7";
		break;
		
		case "store_7":
			dialog.text = "不, 这不奇怪。 我找到他, 给了他一些火朗姆酒。 我从洞里游进去, 因为那艘船上有食物。 坏人把门锁了, 但我总能打开。 嘿嘿... 愚蠢的坏人。 他们引诱螃蟹, 我知道。 坏人\n我到了那里, 找到了内森。 他感觉不舒服。 我有火朗姆酒 - 给了他喝, 他就好多了。 然后我给了他酊剂, 我总是带着一瓶, 以防可怕的螃蟹咬奥莱。 好大叔奇米塞特告诉我要这样做... ";
			link.l1 = "你给他解毒剂和朗姆酒了? 呵, 你不像他们想的那么傻。 干得好, 奥莱。 ";
			link.l1.go = "store_8";
		break;
		
		case "store_8":
			dialog.text = "坏大叔们认为奥莱是傻瓜, 还嘲笑他: 傻瓜奥莱... 奥莱不傻, 只是需要收集所有白色珠子, 否则妈妈会把他赶走。 你以后再给我一颗珠子好吗? ";
			link.l1 = "嗯... 当然, 奥莱, 我们是朋友。 告诉我, 你打算怎么把霍克... 内森大叔送到雕像那里。 奇米塞特大叔告诉我它和船一起沉了... ";
			link.l1.go = "store_9";
		break;
		
		case "store_9":
			dialog.text = "雕像在海底。 奥莱知道。 但那里不深, 好大叔亨利克可以送内森大叔去那里。 亨利克大叔知道如何在水下行走。 但那里有很多可怕的螃蟹。 奥莱怕它们。 它们咬得很疼。 ";
			link.l1 = "亨利克大叔? 他是谁? ";
			link.l1.go = "store_10";
		break;
		
		case "store_10":
			dialog.text = "亨利克大叔住在坏大叔独角鲸帮中间。 每个人都认识他。 他可以在水下行走, 还教独角鲸帮的大叔们如何潜水。 亨利克大叔很善良, 他给了奥莱一颗白色珠子。 ";
			link.l1 = "那独角鲸帮怎么让你进去的? 还是说他们的地盘对你开放? ";
			link.l1.go = "store_11";
		break;
		
		case "store_11":
			dialog.text = "嘻嘻... 坏大叔们不让奥莱进去, 但奥莱晚上可以进入他们船上的任何房间。 他们又大又吵, 但奥莱很安静很小心。 我是在亨利克大叔用来潜水的船周围游泳时遇到他的。 亨利克大叔给了奥莱一颗白色珠子, 我们就成了朋友。 ";
			link.l1 = "有意思... 我也想成为亨利克大叔的朋友。 ";
			link.l1.go = "store_12";
		break;
		
		case "store_12":
			dialog.text = "你想潜水去雕像那里? 它在老船的残骸里。 那里有很多又大又可怕的螃蟹。 你不怕它们吗? 它们会咬人。 ";
			link.l1 = "不, 我不怕它们。 我已经杀了一只, 所以它们最好怕我。 ";
			link.l1.go = "store_13";
		break;
		
		case "store_13":
			dialog.text = "哦, " +pchar.name+ "真勇敢! 那你应该去找亨利克大叔, 他会教你如何在海底行走, 你可以杀死那里的每一只螃蟹。 你还会在那里给奥莱再找一颗大珠子, 对吗? ";
			link.l1 = "当然, 我会的。 但我得先找到亨利克大叔。 ";
			link.l1.go = "store_14";
		break;
		
		case "store_14":
			dialog.text = "为什么要找他? 他住在一艘叫‘圣盖博’的船上, 在车间里。 但坏大叔独角鲸帮可能不会欢迎你。 ";
			link.l1 = "我会自己对付那些坏大叔。 最后一个问题, 内森大叔现在在哪里? 我一直在找他, 他是我来这里的原因。 ";
			link.l1.go = "store_15";
		break;
		
		case "store_15":
			dialog.text = "我把内森大叔藏在‘费尔南达’号上我的避难所里。 那里很远, 没人住。 大家都认为它很快就会沉, 但奥莱知道相反。 我救了内森大叔, 把他带到了那里\n他仍然病得很重, 一直喝火朗姆酒。 他几乎走不动路, 拿不动五磅以上的东西。 我为内森大叔感到难过, 我从箱子里给他拿火朗姆酒, 从坏舰队司令手下的货舱里拿食物。 我还给他煮我抓的老鼠。 非常美味的老鼠! ";
			link.l1 = "美味的老鼠? 我明白了。 那么内森是在那艘叫... 你说什么 - ‘费尔南达’号上? 我不认识她... ";
			link.l1.go = "store_16";
		break;
		
		case "store_16":
			dialog.text = ""+ PChar.name+ "大叔, 我刚告诉你离这里不远。 你得游泳过去。 船尾有扇门, 但内森大叔不开。 奥莱让他不要开。 但如果你是内森大叔的朋友, 我就告诉你怎么打开。 像这样敲门: 敲-敲... 敲-敲。 然后他就会开门。 ";
			link.l1 = "我会记住的。 谢谢, 奥莱! 你真的帮了我大忙! 我不知道该怎么好好感谢你。 ";
			link.l1.go = "store_17";
		break;
		
		case "store_17":
			dialog.text = "再给我一颗白色珠子。 如果你能找到的话, 当然。 ";
			link.l1 = "啊, 对! 白色珠子! 好的。 再见, 奥莱! ";
			link.l1.go = "store_18";
		break;
		
		case "store_18":
			DialogExit();
			LAi_SetLoginTime(npchar, 12.0, 21.99);
			LAi_SetCitizenType(npchar);
			LAi_group_MoveCharacter(npchar, "LSC_CITIZEN");
			sld = characterFromId("Nathaniel");
			sld.dialog.currentnode = "diffindoor";
			sld.greeting = "Nathaniel_ill"; // 给内森设置节点和虚弱状态
			pchar.questTemp.LSC.DiffIndoor = "true"; // 访问内森的属性
			pchar.questTemp.LSC = "mechanic"; // 与机械师对话的标志
			NextDiag.CurrentNode = "ole";
			AddQuestRecord("LSC", "6");
		break;
		
		case "ole":
			dialog.text = "啊, " +pchar.name+ "大叔! 很高兴见到你! 你好吗? ";
			link.l1 = "谢谢, 奥莱, 我很好。 我也很高兴见到你。 ";
			link.l1.go = "exit";
			link.l2 = "听着, 奥莱, 你说舰队司令的海盗把货舱的门锁了, 而你总能打开... 那里所有的箱子都是锁着的, 你说你从里面拿朗姆酒给内森大叔。 你是怎么做到的? ";
			link.l2.go = "lock";
			NextDiag.TempNode = "ole";
		break;
		
		case "lock":
			dialog.text = "奥莱有一套很好的钥匙。 它们可以打开任何门或箱子。 嗯, 不是全部。 有些打不开, 但大多数可以。 奥莱是在坏大叔尤尔根的船舱里找到的。 他每天都在炉子旁用锤子干活。 他制作锁和钥匙。 他还为坏独角鲸帮制作又大又可怕的火枪。 ";
			link.l1 = "我明白了。 奥莱, 你能把这些钥匙卖给我吗? 我可以付钱... ";
			link.l1.go = "lock_1";
		break;
		
		case "lock_1":
			dialog.text = "好的, " +pchar.name+ "大叔, 我把钥匙卖给你。 我只留下一把。 它能打开舰队司令的房间。 那里有很多给内森大叔的食物和朗姆酒。 反正箱子里也没有更多的珠子和朗姆酒了。 ";
			link.l1 = "你想要多少钱? ";
			link.l1.go = "lock_2";
		break;
		
		case "lock_2":
			dialog.text = "首先, 告诉我, " +pchar.name+ "大叔, 你有大船吗? ";
			link.l1 = "是的, 我有。 但她不在这里, 她在外环。 但我很快就会离开这个岛, 我会乘我的大船回来接内森大叔。 ";
			link.l1.go = "lock_3";
		break;
		
		case "lock_3":
			dialog.text = "接内森大叔? 哦, 太好了! 那么听着, 答应我乘你的大船带我离开这里, 让我随你航行多久都行。 我会有用的。 我可以抓老鼠。 煮老鼠... 另外, 给我五颗白色珠子。 我就把钥匙给你。 ";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l1 = "当然! 这是你的珠子。 拿着。 ";
				link.l1.go = "lock_4";
			}
			link.l2 = "抓老鼠。 煮老鼠? 呵! 有趣的技能。 当然, 奥莱, 我们成交。 我会给你五颗珠子, 并且说到做到。 ";
			link.l2.go = "exit";
			NextDiag.TempNode = "ole_1";
		break;
		
		case "ole_1":
			dialog.text = "啊, " +pchar.name+ "大叔! 很高兴见到你! 你好吗? ";
			link.l1 = "谢谢, 奥莱, 我很好。 我也很高兴见到你。 ";
			link.l1.go = "exit";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l2 = "我给你带来了五颗白色珠子换你的钥匙。 ";
				link.l2.go = "lock_4";
			}
			NextDiag.TempNode = "ole_1";
		break;
		
		case "lock_4":
			RemoveItems(pchar, "jewelry52", 5);
			PlaySound("interface\important_item.wav");
			dialog.text = "珠子! 白色珠子! " +pchar.name+ "大叔把珠子给奥莱了! 很快就能见到你了, 妈妈... " +pchar.name+ "大叔, 你答应过回来时带我离开这里, 对吗? ";
			link.l1 = "我答应你, 奥莱。 我还没吃过老鼠呢。 我会带你一起走。 ";
			link.l1.go = "lock_5";
		break;
		
		case "lock_5":
			GiveItem2Character(pchar, "keys_skel");
			AddCharacterExpToSkill(pchar, "Sneak", 200);
			dialog.text = "谢谢你, 谢谢你, 好" +pchar.name+ "大叔! 拿好你的钥匙。 使用起来很简单, 只要把它们一个一个插进去试试。 其中一把最终会打开你需要的锁。 如果不行, 那锁就太复杂了, 你肯定需要一把特殊的钥匙。 ";
			link.l1 = "我明白了。 我想我能处理。 ";
			link.l1.go = "lock_6";
		break;
		
		case "lock_6":
			dialog.text = "等等, " +pchar.name+ "大叔! 我还有一把钥匙。 它很漂亮很精巧。 坏大叔尤尔根不做这样的钥匙。 我不知道它能开什么, 但也许你会弄清楚。 看, 这把钥匙很漂亮, 你肯定没见过这样的。 ";
			link.l1 = "给我看看... 是的, 这把钥匙很有趣。 但如果你不知道它能开什么, 有什么用呢? ";
			link.l1.go = "lock_7";
		break;
		
		case "lock_7":
			dialog.text = ""+ PChar.name+ "大叔, 你真奇怪。 有什么用? 如果有钥匙, 就一定有锁。 如果有锁, 就一定有金币。 我在岛上找到的钥匙。 这意味着锁也在这里。 毫无疑问。 这是一把精巧的钥匙, 只有非常贵重的物品才会用这样的钥匙锁起来。 奥莱知道。 ";
			link.l1 = "说实话, 你真有趣, 奥莱。 好吧, 我买了。 你想要珠子吗? ";
			link.l1.go = "lock_8";
		break;
		
		case "lock_8":
			dialog.text = "是的, 奥莱想要五颗珠子。 你会给我吗, " +pchar.name+ "大叔? ";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l1 = "给, 拿好你的珠子。 ";
				link.l1.go = "key";
			}
			link.l2 = "我没有, 但我肯定会给你带来珠子的。 ";
			link.l2.go = "exit";
			NextDiag.TempNode = "ole_2";
		break;
		
		case "key":
			RemoveItems(pchar, "jewelry52", 5);
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "sant_anna_key");
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = "珠子! 给白男孩的白色珠子! 给妈妈的! 给你, " +pchar.name+ "大叔, 拿好钥匙。 你会找到锁的, 奥莱知道。 你很勇敢, 连可怕的螃蟹都不怕。 ";
			link.l1 = "哦, 别让我笑了, 奥莱! 谢谢你的钥匙。 回头见! ";
			link.l1.go = "exit";
			NextDiag.TempNode = "ole_3";
		break;
		
		case "ole_2":
			dialog.text = "啊, " +pchar.name+ "大叔! 很高兴见到你! 你好吗? ";
			link.l1 = "谢谢, 奥莱, 我很好。 我也很高兴见到你。 ";
			link.l1.go = "exit";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l2 = "我给你带来了五颗白色珠子换你的钥匙。 ";
				link.l2.go = "key";
			}
			NextDiag.TempNode = "ole_2";
		break;
		
		case "ole_3":
			dialog.text = "啊, " +pchar.name+ "大叔! 很高兴见到你! 你好吗? ";
			link.l1 = "谢谢, 奥莱, 我很好。 我也很高兴见到你。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "ole_3";
		break;
		
		case "return":
			dialog.text = "哦, " +pchar.name+ "大叔, 你回来了! 你乘大船回来了! 你会带我离开这里吗? " +pchar.name+ "大叔, 你答应过我的, 记得吗? ";
			link.l1 = "当然, 我记得, 奥莱。 欢迎上船! 我想老鼠们有麻烦了, 哈哈! ";
			link.l1.go = "return_1";
			link.l2 = "真的吗? 我什么时候答应过你? 我不记得有这样的承诺... ";
			link.l2.go = "return_3";
		break;
		
		case "return_1":
			dialog.text = "谢谢, 大叔! 奥莱会有用的, 你会看到的! 哦, 也许我会见到妈妈? 我现在就来! ";
			link.l1 = "别这么着急, 奥莱。 你可以收拾一下东西。 我不会马上起航。 ";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LSC_SetOlePassenger", 10.0);
		break;
		
		case "return_3":
			dialog.text = "你答应过我的, 你答应过! 你答应过带奥莱离开这里! 坏大叔! 你骗了奥莱! 坏大叔! ";
			link.l1 = "... ";
			link.l1.go = "return_4";
		break;
		
		case "return_4":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload45", "none", "", "", "", 20.0);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "authority", -3);
			if (GetCharacterIndex("Mary") != -1) // 玛丽
			{
				sld = characterFromId("Mary");
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else // 否则结束
			{
				chrDisableReloadToLocation = false;
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			}
		break;
		
		// 迷途之子
		case "givemepearl":
			dialog.text = "大叔, 大叔... 我还需要一颗白色珠子。 请给奥莱一颗白色珠子! ";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "我就知道你会要。 给, 拿好你的珠子。 满意了吗? ";
				link.l1.go = "givemepearl_yes";
			}
			link.l2 = "哦, 真是麻烦... 我没有更多的珠子了, 奥莱, 没有了! ";
			link.l2.go = "givemepearl_no";
			DeleteAttribute(npchar, "pearl_date");
		break;
		
		case "givemepearl_yes":
			RemoveItems(pchar, "jewelry52", 1);
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			dialog.text = "谢谢你! 好, 好" +pchar.name+ "大叔! 奥莱又多了一颗珠子, 剩下的珠子不多了! 我要去找妈妈了... ";
			link.l1 = "哦, 你为什么这么奇怪... ";
			link.l1.go = "givemepearl_yes_1";
		break;
		
		case "givemepearl_yes_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			SaveCurrentNpcQuestDateParam(npchar, "pearl_date");
			npchar.quest.pearlqty = sti(npchar.quest.pearlqty)+1;
			NextDiag.CurrentNode = "givemepearl_repeat";
		break;
		
		case "givemepearl_repeat":
			dialog.text = "谢谢你的珠子, 好" +pchar.name+ "大叔! ";
			link.l1 = "不客气... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "givemepearl_repeat";
		break;
		
		case "givemepearl_no":
			dialog.text = "没珠子? 怎么会这样, " +pchar.name+ "大叔? ! 就差几颗了... 我得收集它们。 这样的话我就下船。 我会去找珠子... ";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "你打算去哪里? 一个人怎么办? 不, 我不想为你的命运负责。 等等, 我检查一下口袋... 给! 拿好你的珠子, 跟我待在一起。 满意了吗? ";
				link.l1.go = "givemepearl_yes";
			}
			link.l2 = "这是你的权利, 奥莱。 如果你跟我航行腻了, 我也不会阻止你。 我们有过约定。 不过你抓那些老鼠抓得很好... ";
			link.l2.go = "givemepearl_no_1";
		break;
		
		case "givemepearl_no_1":
			dialog.text = "再见, " +pchar.name+ "大叔。 奥莱需要白色珠子, 否则永远回不了家见妈妈... ";
			link.l1 = "哦, 我为你感到难过, 但我能做什么呢? 去吧, 奥莱。 祝你好运。 ";
			link.l1.go = "givemepearl_exit";
		break;
		
		case "givemepearl_exit": // 奥莱离开 - 任务未完成
			DialogExit();
			RemovePassenger(Pchar, npchar);
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			DeleteAttribute(pchar, "GenQuest.Ole");
		break;
		
		case "mother":
			dialog.text = ""+ PChar.name+ "大叔! 我还需要一颗白色珠子。 最后一颗。 请给奥莱吧! ";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "我就知道你会要。 给, 拿好你的珠子。 满意了吗? ";
				link.l1.go = "mother_1";
			}
			link.l2 = "哦, 真是麻烦... 我没有更多的珠子了, 奥莱, 没有了! ";
			link.l2.go = "givemepearl_no_1";
		break;
		
		case "mother_1":
			RemoveItems(pchar, "jewelry52", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "谢谢你, 谢谢你, 好" +pchar.name+ "大叔! 现在奥莱有所有的珠子了。 是的, 所有的! 现在奥莱可以把它们带给妈妈, 她就不会把奥莱赶走了... ";
			link.l1 = "听着, 你总是说的那个妈妈是谁? 最后给我解释一下你为什么需要那些珍珠... 白色珠子? 你说‘都收集齐了’是什么意思? ";
			link.l1.go = "mother_2";
		break;
		
		case "mother_2":
			dialog.text = "好" +pchar.name+ "大叔帮奥莱收集了给妈妈的珠子... 奥莱小时候扯断了妈妈的白色珠子项链。 它们都掉进了水里。 妈妈对奥莱很生气, 他不收集所有丢失的珠子就不能回家\n我记得有多少颗。 五十颗。 现在奥莱都收集齐了。 " +pchar.name+ "大叔, 请带我回家! 我想让妈妈高兴, 把珠子还给她。 带我回家! ";
			link.l1 = "天啊, 多么不可思议的故事... 你还是个孩子的时候就到了这个岛。 就因为扯断了妈妈的珍珠项链就被赶走了? 太可怕了... ";
			link.l1.go = "mother_3";
		break;
		
		case "mother_3":
			dialog.text = "带我回家见妈妈, 好" +pchar.name+ "大叔。 我想见她。 她看到珠子会高兴的。 ";
			link.l1 = "我很想, 但你知道你家在哪里吗? 你妈妈住在哪里? ";
			link.l1.go = "mother_4";
		break;
		
		case "mother_4":
			dialog.text = "她住在岛上, 红屋顶的房子里。 ";
			link.l1 = "真的! 你知道这里有多少个岛, 有多少红屋顶的房子吗? 那个岛叫什么名字? 给我详细信息... ";
			link.l1.go = "mother_5";
		break;
		
		case "mother_5":
			dialog.text = "我不知道它的名字。 我知道那是个岛, 妈妈告诉爸爸我们在岛上! 我们住在红屋顶的房子里。 漂亮的房子, 很大的。 带我去见妈妈, " +pchar.name+ "大叔。 求你了... ";
			link.l1 = "哦, 好吧。 我们会在每个岛上找这样的房子, 问问你妈妈。 她叫什么名字? ";
			link.l1.go = "mother_6";
		break;
		
		case "mother_6":
			dialog.text = "她的名字? 你真奇怪, " +pchar.name+ "大叔。 妈妈的名字就是妈妈。 你妈妈的名字不一样吗? ";
			link.l1 = "哦, 上帝, 请赐给我一些耐心... 好吧, 奥莱。 我们会试着找到你的家。 现在去船上吧。 ";
			link.l1.go = "mother_7";
		break;
		
		case "mother_7":
			dialog.text = "谢谢你, " +pchar.name+ "大叔。 你非常非常善良和友好! 奥莱很快就能见到妈妈了! ";
			link.l1 = "哦... ";
			link.l1.go = "mother_8";
		break;
		
		case "mother_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			DeleteAttribute(npchar, "pearl_date");
			// 设置阿格尼丝.克里斯蒂安森并打开她在马里戈的家
			LocatorReloadEnterDisable("Marigo_town", "houseSp2", false);
			sld = GetCharacter(NPC_GenerateCharacter("Agnes", "women_18", "woman", "towngirl", 10, HOLLAND, -1, true, "quest"));
			SetFantomParamFromRank(sld, 10, true);
			sld.name = "Agnes";
			sld.lastname = "Christiansen";
			sld.dialog.FileName = "Quest\LSC\OtherNPC.c";
			sld.dialog.currentnode = "agnes";
			//sld.greeting = "";
			LAi_SetOwnerType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Marigo_houseSp2", "barmen", "stay");
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
		break;
		
		case "home":
			dialog.text = "妈妈... 妈妈, 妈妈! 我回来了! ";
			link.l1 = "儿子... ";
			link.l1.go = "home_1";
		break;
		
		case "home_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			SetMusic("music_romantic");
			bDisableCharacterMenu = true;// 锁定界面
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.005, 0.0, 2.0, 0.0, 1000);
			Pchar.FuncCameraFly = "";
			DoQuestFunctionDelay("LSC_OleReturnHome", 18.0);
		break;
		
		case "home_2":
			dialog.text = "妈妈, 我给你带来了白色珠子! 我都收集齐了! 你还在生我的气吗? ";
			link.l1 = "上帝... (哭泣) 奥莱! 儿子, 为什么? 你为什么离开? 我不在乎那些珍珠! ";
			link.l1.go = "home_3";
		break;
		
		case "home_3":
			sld = characterFromId("Blaze");
			dialog.text = "妈妈, 给... 拿着。 我收集了很久。 好大叔们一直在帮我, 特别是" + sld.name + "大叔。 他让我上了他的大船, 帮我收集珠子, 还把我带回家... ";
			link.l1 = "奥莱... 你真的长大了, 但你还是个孩子... 让我抱抱你, 儿子! 对不起, 请原谅我那条该死的项链! 我再也不会离开你了, 永远! 我们会住在一起, 我会照顾你... 我会补偿的, 我保证! ... ";
			link.l1.go = "home_4";
		break;
		
		case "home_4":
			dialog.text = "妈妈, 我想你... 我想和你在一起。 你还在生我的气吗? 你为什么哭? ";
			link.l1 = "(哭泣) 不, 不... 我很抱歉, 请原谅我, 儿子! ... ";
			link.l1.go = "home_5";
		break;
		
		case "home_5": // 转移pchar
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Agnes");
			sld.dialog.currentnode = "agnes_11";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "final":
			dialog.text = ""+ PChar.name+ "大叔! 你来了真好! 谢谢你带我回家见妈妈。 和她在一起真好... 回家真好, 不是吗, " +pchar.name+ "大叔? ";
			link.l1 = "是的, 奥莱。 是的。 我很高兴你快乐。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "final";
		break;
		
//--------------------------------------- —特殊反应 -----------------------------------------------
		// 注意到露出的武器
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("听着, 你最好把武器收起来。 它让我紧张。 ", "你知道, 在这里挥舞武器是不被容忍的。 收起来。 ", "听着, 别扮演中世纪骑士到处挥剑。 收起来, 这不适合你... ");
			link.l1 = LinkRandPhrase("好的。 ", "好的。 ", "如你所说... ");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "听着, 我是这个城市的公民, 我请你收剑。 ", "听着, 我是这个城市的公民, 我请你收剑。 ");
				link.l1 = LinkRandPhrase("好的。 ", "好的。 ", "如你所说... ");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "小心点, 朋友, 带着武器跑。 我可能会紧张... ", "我不喜欢男人在我面前拿着武器。 这让我害怕... ");
				link.l1 = RandPhraseSimple("知道了。 ", "我收起来。 ");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// < —特殊反应
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
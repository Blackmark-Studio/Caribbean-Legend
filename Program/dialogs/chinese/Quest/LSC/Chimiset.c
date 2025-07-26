// 巫师里瓦多斯 - 奇米塞特
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "想要点什么? ";
			link.l1 = "不, 没什么。 ";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		//-------------------------------------在塔塔罗斯监狱里-----------------------------
		// 选项 R
		case "KillChad":
			dialog.text = "等等! 住手... 我请求你在犯错误之前听我说。 ";
			link.l1 = "我在听... 希望你有合理的理由阻止我... ";
			link.l1.go = "KillChad_1";
			LAi_RemoveCheckMinHP(npchar); // 移除检查者, 如果还存在
		break;
		
		case "KillChad_1":
			dialog.text = "阻止你杀我, 对吗? 我听到你和楼上的查德谈话了, 我不怪你 - 任何人可能都会这么做。 但你认为杀了我后查德会放你走, 这是错误的。 ";
			link.l1 = "嗯... 有意思, 为什么不会? 我只知道如果不杀你, 我就得费很大力气才能离开这里。 ";
			link.l1.go = "KillChad_2";
		break;
		
		case "KillChad_2":
			dialog.text = "如果你杀了我, 你根本不会有任何未来。 听着, 独角鲸帮和查德都想除掉我, 但他们太害怕我了, 不敢自己动手 - 杀我的人会被永远诅咒。 所以他们想让你做所有肮脏的工作\n查德知道你不是里瓦多斯, 他在耍你。 一旦你杀了我 - 他们会对你做同样的事, 用你的尸体来愚弄鲨鱼。 ";
			link.l1 = "鲨鱼? 史蒂夫.多德森? 他真的在这里吗? 最后给我解释一下 - 那些里瓦多斯到底是谁? ";
			link.l1.go = "KillChad_3";
		break;
		
		case "KillChad_3":
			dialog.text = "呵, 看来你确实不住在这里... 但现在不是讲故事的时候。 我们得救自己。 我有个计划。 ";
			link.l1 = "知道吗, 巫师, 我最近穿过一个神秘的传送门, 勉强活了下来, 所以你的诅咒吓不到我。 我受够了 - 是时候解决你了。 ";
			link.l1.go = "KillChad_fightfail";
			link.l2 = "好吧, 我相信你。 计划是什么? ";
			link.l2.go = "KillChad_4";
		break;
		
		case "KillChad_fightfail":
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "afraid", "", -1);
			LAi_SetImmortal(npchar, false);
			pchar.quest.LSC_fightfail.win_condition.l1 = "NPC_Death";
			pchar.quest.LSC_fightfail.win_condition.l1.character = "Chimiset";
			pchar.quest.LSC_fightfail.function = "LSC_Fightfail_Final";
		break;
		
		case "KillChad_4":
			dialog.text = "那边有个箱子。 里面有不错的武器和药水。 它是锁着的, 但锁又旧又坏, 所以找个撬棍把它撬开\n从箱子里拿所有东西, 武装自己, 然后去楼梯。 那是个很好的防御位置, 他们将被迫一个接一个地和你战斗, 只要注意火枪手\n我希望你擅长用剑, 我太老了, 不能帮你战斗。 如果你能杀了他们所有人并活下来 - 我保证里瓦多斯家族会保护你... ";
			link.l1 = "好的。 为我祈祷吧 - 这场战斗会很艰难。 楼上的那些家伙看起来很认真。 ";
			link.l1.go = "KillChad_5";
		break;
		
		case "KillChad_5":
			DialogExit();
			pchar.quest.LSC_fightfail.over = "yes"; // 移除中断
			LAi_SetImmortal(npchar, true);
			ref location = &Locations[FindLocation(pchar.location)];
			location.private1.key = "crowbar";
			location.private1.key.delItem = true;
			NextDiag.CurrentNode = "KillChad_6";
		break;
		
		case "KillChad_6":
			dialog.text = "别浪费时间! 快点撬锁... ";
			link.l1 = "是是, 我这就去。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "KillChad_6";
		break;
		
		case "Chad_die":
			dialog.text = "干得好! 你真是击剑大师。 我欠你一个人情, 陌生人。 告诉我, 你叫什么名字? ";
			link.l1 = ""+pchar.name+"。 "+GetFullName(pchar)+"。 你叫什么? ";
			link.l1.go = "Chad_die_1";
		break;
		
		case "Chad_die_1":
			dialog.text = "我叫奇米塞特, 我是里瓦多斯的萨满, 我们酋长黑埃迪的顾问。 他会很高兴知道你救了我, 让我重获自由。 你是奇米塞特。 黑埃迪和所有里瓦多斯的朋友。 从现在起, 你在我们的守护者号上永远是受欢迎的客人... ";
			link.l1 = "等等... 奇米塞特, 如果你还不明白, 我到这里才几个小时。 你能解释一下我在哪里, 里瓦多斯是谁, 我在哪里可以找到鲨鱼多德森吗? ";
			link.l1.go = "Chad_die_2";
		break;
		
		case "Chad_die_2":
			dialog.text = "这个地方叫做废弃船只之城。 虽然这听起来更像是一种嘲讽。 它算不上一座城市。 这个地方是由数百艘废弃船只形成的岛屿。 中心适合居住。 居住在这里的人是那些在无法解释的风暴中幸存下来的人, 风暴导致他们的船只失事并来到这里\n里瓦多斯是一个帮派, 一群长期生活在一起的人。 这里还有其他三个群体: 独角鲸帮派, 他们是我们的敌人, 鲨鱼多德森的海盗和普通人。 鲨鱼基本上是这个岛的首领, 他自称舰队司令\n他最近才到, 用暴力夺取了权力。 他占领了我们储存粮食的'圣奥古斯丁号'。 现在我们不得不以鲨鱼指定的价格购买粮食。 看来你已经去过那个仓库了\n查德.卡珀是鲨鱼的水手长和监狱长。 莱顿.德克斯特曾经是鲨鱼的大副, 他也有一定的影响力。 这三个人和他们的海盗是岛上的主导力量, 对抗里瓦多斯和独角鲸帮。 ";
			link.l1 = "为什么查德.卡珀要我杀你? ";
			link.l1.go = "Chad_die_3";
		break;
		
		case "Chad_die_3":
			dialog.text = "查德已经与我们的敌人独角鲸帮建立了联系。 他打算在他们的帮助下杀死鲨鱼, 取而代之。 独角鲸帮因为前首领艾伦.米尔罗的死而对舰队司令怀恨在心。 他们认为鲨鱼对此负责, 但他们错了。 我知道是谁干的。 是查德干的。 我是这起罪行的唯一证人\n这就是为什么查德不能让我自由, 但他也害怕伤害我。 海盗在战斗中无所畏惧, 但他们非常迷信。 所以他想利用你。 查德和独角鲸帮会杀了鲨鱼, 并嫁祸给里瓦多斯。 ";
			link.l1 = "是这样吗? 告诉我为什么... ";
			link.l1.go = "Chad_die_4";
		break;
		
		case "Chad_die_4":
			dialog.text = ""+pchar.name+", 我的朋友, 我们以后再谈。 我们得快点, 在鲨鱼的海盗出现之前。 搜索查德的尸体, 拿走他的钥匙。 但首先, 检查他的桌子, 他可能有有趣的文件在那里\n去找鲨鱼多德森, 你会在'圣奥古斯丁号'找到他, 那是一艘与其他船只相距较远的大船, 从名为'冥王星'的船有一座桥通向它。 告诉他查德在策划背叛, 并说这一切都是独角鲸帮在背后搞鬼, 而我们里瓦多斯与此无关\n一旦你到达我们在守护者号上的住所, 我很乐意告诉你任何你需要的关于这个岛。 我的帮派和其他人的信息。 我们离开这里吧! ";
			link.l1 = "好的, 奇米塞特。 我稍后会在...'守护者号'找你。 我们离开这里吧! ";
			link.l1.go = "Chad_die_5";
		break;
		
		case "Chad_die_5":
			dialog.text = "还有一件事。 我们的船, 包括'守护者号', 对陌生人是限制进入的。 你必须是里瓦多斯或知道密码才能进入。 我本想告诉你, 但密码每周都在变化, 我在这里太久了, 不知道当前的密码\n你应该先去'圣奥古斯丁号'。 我会告诉我们的人你是谁, 当你和鲨鱼谈话时, 他们会期待你的到来。 但现在不要去'守护者号', 先和鲨鱼谈谈, 让我先和我的人见面, 否则里瓦多斯会对你有敌意";
			link.l1 = "我明白了。 我要去'圣奥古斯丁号'。 再见! ";
			link.l1.go = "Chad_die_6";
		break;
		
		case "Chad_die_6":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Notsearchbody");
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			pchar.quest.LSC_LetterChad.win_condition.l1 = "item";
			pchar.quest.LSC_LetterChad.win_condition.l1.item = "letter_chad";
			pchar.quest.LSC_LetterChad.function = "LSC_LetterChad_Find";
			sld = characterFromId("SharkMush_17");
			sld.lifeday = 0;
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("SharkSold_1"+(i+3));
				sld.lifeday = 0;
			}
			AddSimpleRumourCityTip("哈, 他们说你是里瓦多斯帮派的朋友。 这很有趣。 恭喜... ", "LostShipsCity", 5, 1, "LSC", "");
			AddSimpleRumourCityTip("他们说你从'塔塔罗斯'救出了里瓦多斯巫师奇米塞特。 现在你在他们的船上是受欢迎的客人。 ", "LostShipsCity", 5, 1, "LSC", "");
			AddSimpleRumourCityTip("原来就是你放了奇米塞特! 有意思。 现在你是里瓦多斯的朋友, 但却是独角鲸帮的敌人。 我不确定是该恭喜你还是同情你... ", "LostShipsCity", 5, 1, "LSC", "");
		break;
		
		// 选项 N
		case "prisoner":
			dialog.text = "你想从我这里得到什么, 陌生人? ";
			link.l1 = "你叫奇米塞特, 对吧? ";
			link.l1.go = "prisoner_1";
		break;
		
		case "prisoner_1":
			dialog.text = "是的, 是我。 你是有事情找我还是只是想聊聊? ";
			link.l1 = "我有事情要谈。 我从舰队司令鲨鱼多德森那里来。 我带来了释放你的命令, 但有一个条件: 你必须回答我几个问题。 ";
			link.l1.go = "prisoner_2";
		break;
		
		case "prisoner_2":
			dialog.text = "多德森决定释放我了? 很高兴听到这个。 问你的问题吧。 我希望这不是诡计, 否则我的兴奋就白费了。 ";
			link.l1 = "没有诡计, 我只需要你的帮助。 告诉我, 奇米塞特, 这个岛上有一个奇怪的石偶像吗? 它在午夜会变成金子。 别以为我疯了... ";
			link.l1.go = "Friend_2";
		break;
		
		case "prisoner_3":
			dialog.text = "还有其他问题吗? ";
			link.l1 = "是的。 你认识一个叫白小子的人吗? ";
			link.l1.go = "prisoner_4";
		break;
		
		case "prisoner_4":
			dialog.text = "白小子? 当然, 我认识他。 这是奥勒.克里斯蒂安森的绰号, 我们当地的傻瓜。 他现在成年了, 看起来不再像个男孩了, 尽管他的心智仍然幼稚。 ";
			link.l1 = "是这样吗? 告诉我, 我在哪里可以找到他? ";
			link.l1.go = "prisoner_5";
		break;
		
		case "prisoner_5":
			dialog.text = "在我们城市的任何地方。 他经常在商店。 酒馆或街上被找到。 他有一头白发, 你会认出他的。 ";
			link.l1 = "太好了! 还有一个问题: 你在这里见过一个叫纳撒尼尔.霍克的人吗? 他一定是最近出现在这里, 他可能病得很重。 ";
			link.l1.go = "prisoner_6";
		break;
		
		case "prisoner_6":
			dialog.text = "在这方面我帮不了你, 陌生人。 我不认识叫这个名字的人。 我可以向你保证, 他不在里瓦多斯的船上, 也不应该在中立区。 不过, 关于独角鲸帮的领土, 我就不敢说了, 里瓦多斯不去那里。 ";
			link.l1 = "好吧, 无论如何谢谢你... 你帮了我很多, 奇米塞特! ";
			link.l1.go = "prisoner_7";
		break;
		
		case "prisoner_7":
			dialog.text = "就这样? 现在鲨鱼会释放我吗? ";
			link.l1 = "是的。 我没有别的要问你了。 查德.卡珀会释放你。 好了, 我得走了... ";
			link.l1.go = "prisoner_8";
		break;
		
		case "prisoner_8":
			dialog.text = "停下! 等等... 回来。 ";
			link.l1 = "有什么要告诉我的吗? ";
			link.l1.go = "prisoner_9";
		break;
		
		case "prisoner_9":
			dialog.text = "不完全是... (压低声音) 我看你不是卡珀的人。 不要相信他。 他是个肮脏的人渣。 不久前, 他用宽剑冷酷地杀死了手无寸铁的艾伦.米尔罗。 他是独角鲸帮派的首领。 我没料到会这样, 查德只是走近他的牢房并处决了他\n此外, 我听到一些传言说舰队司令自己的人计划暗杀他。 告诉鲨鱼这件事。 告诉他我们面对面谈时我会说更多。 ";
			link.l1 = "嗯。 好的, 我会告诉多德森的。 再见! ";
			link.l1.go = "prisoner_10";
		break;
		
		case "prisoner_10":
			DialogExit();
			sld = characterFromId("Capper");
			sld.quest.chimiset_talk = "true"; // 与奇米塞特的谈话已发生
			if (!CheckAttribute(npchar, "quest.capper_talk")) chrDisableReloadToLocation = true;// 关闭位置
			else chrDisableReloadToLocation = false;// 打开位置
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "entrance_10"; // 鲨鱼的节点
			LSC_SetWhiteBoy(); // 设置白小子
			NextDiag.CurrentNode = "prisoner_11";
			AddQuestRecord("SharkHunt", "20");
		break;
		
		case "prisoner_11":
			dialog.text = "去找鲨鱼, 把我告诉你的一切都告诉他。 嗯, 我希望他们很快打开这个笼子... ";
			link.l1 = "是是。 我这就去。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "prisoner_11";
		break;
		
		//------------------------在守护者号上的对话, 如果通过塔塔罗斯开始-----------------
		case "Friend":
			dialog.text = "你来了, 我亲爱的朋友。 再次感谢你救了我, 相信我, 而不是卡珀。 我会给你这些护身符作为奖励。 我相信你会发现它们有用。 ";
			link.l1 = "谢谢你! 我没想到... ";
			link.l1.go = "Friend_1";
		break;
		
		case "Friend_1":
			GiveItem2Character(pchar, "indian_1");
			GiveItem2Character(pchar, "indian_11");
			GiveItem2Character(pchar, "amulet_1");
			PlaySound("interface\important_item.wav");
			dialog.text = "现在我准备好听你说了。 你想问我什么, 对吗? ";
			link.l1 = "你说得对, 奇米塞特。 我需要你的帮助。 首先, 我需要知道这个岛上有一个奇怪的石偶像吗? 它在午夜会变成金子。 别以为我疯了... ";
			link.l1.go = "Friend_2";
		break;
		
		// 交叉节点
		case "Friend_2":
			dialog.text = "是的, 我明白你的意思, 我的朋友。 我亲眼见过这个印度神的雕像。 不过它只在早晨的阳光照射下变成金色, 而不是月光... 我们多次献祭邪恶的独角鲸帮成员, 神吞噬了他们所有人。 但它现在不在岛上了。 ";
			link.l1 = "怎么会不在了? ! 你是说它突然消失了? ! ";
			link.l1.go = "Friend_3";
		break;
		
		case "Friend_3":
			dialog.text = "不完全是这样。 这座雕像在'圣赫罗尼莫号'里面。 几年前, 这艘船和雕像一起沉没了。 ";
			link.l1 = "运气真差! 看来现在不可能离开这个岛了... 那艘船在哪里? ";
			link.l1.go = "Friend_4";
		break;
		
		case "Friend_4":
			dialog.text = "离独角鲸帮领土不远, 在名为'凤凰号'的船只残骸附近。 天气好的时候, 你可以看到那艘船躺在海底。 ";
			link.l1 = "哈! 那么它躺在浅滩上? 那我可以游过去... ";
			link.l1.go = "Friend_5";
		break;
		
		case "Friend_5":
			dialog.text = "你不能, 我的朋友。 首先, 那里太深了; 其次, 有很多巨型螃蟹。 在你到达'圣赫罗尼莫号'之前, 它们会把你撕碎。 ";
			link.l1 = "嗯。 好吧, 我会考虑的。 至少我知道雕像存在, 这是最重要的。 ";
			if (CheckAttribute(npchar, "quest.chimiset_die")) link.l1.go = "prisoner_3";
			else
			{	
				if (CheckAttribute(pchar, "questTemp.LSC.Mary")) link.l1.go = "freedom_1";
				else link.l1.go = "Friend_6";
			}
			AddQuestRecord("LSC", "4");
		break;
		// 交叉节点
		
		case "Friend_6":
			dialog.text = "我看你还有更多问题。 随便问吧, 我的朋友。 ";
			link.l1 = "鲨鱼多德森让我找出查德的同谋。 我在查德的箱子里发现了一封信。 里面提到了某个狙击手和一把枪。 看起来他们想从远处暗杀鲨鱼。 你有什么想法吗? ";
			link.l1.go = "Friend_7";
		break;
		
		case "Friend_7":
			dialog.text = "嗯。 他们要射杀舰队司令? 我得想想... 问题是,舰队司令几乎从不离开他的住所, 当他离开时, 有半打海盗保护他。 但他有一个习惯, 喜欢在傍晚时分在船尾散步\n有两个狙击手可以射击舰队司令住所的位置 -'圣弗洛伦蒂娜号'的船首和'愤怒号'的桅杆。 但狙击手仍然无法从这些位置杀死舰队司令, 他必须是个鹰眼射手才能进行这样的射击。 此外, 他需要一把出色的步枪。 你应该在岛上问问谁有机会获得这种火器。 ";
			link.l1 = "呵, 看来你是对的, 信里确实提到了枪... 你见过有人有这样的枪吗? ";
			link.l1.go = "Friend_8";
		break;
		
		case "Friend_8":
			dialog.text = "没有。 我这辈子都没见过这样的枪。 问问别人, 也许有人会告诉你。 ";
			link.l1 = "好吧... 不管怎样, 你的信息很有价值, 谢谢你! 好了, 现在最后一个问题, 不过我不指望你回答... 你听说过白小子吗? ";
			link.l1.go = "Friend_9";
		break;
		
		case "Friend_9":
			dialog.text = "白小子? 当然, 我认识他。 这是奥勒.克里斯蒂安森的绰号, 我们当地的傻瓜。 他现在成年了, 看起来不再像个男孩了, 尽管他的心智仍然幼稚。 ";
			link.l1 = "是这样吗? 告诉我在哪里可以找到他? ";
			link.l1.go = "Friend_10";
		break;
		
		case "Friend_10":
			dialog.text = "在我们城市的任何地方。 他经常在商店。 酒馆或街上被找到。 他有一头白发 - 你肯定会认出他的。 ";
			link.l1 = "太好了! 谢谢你, 奇米塞特, 你帮了我很多! ";
			link.l1.go = "Friend_11";
		break;
		
		case "Friend_11":
			dialog.text = "我总是乐意帮忙! 如果你有更多问题, 来找我。 ";
			link.l1 = "当然! 我现在得走了。 再见! ";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary")) link.l1.go = "freedom_2";
			else link.l1.go = "Friend_12";
		break;
		
		case "Friend_12":
			DialogExit();
			NextDiag.CurrentNode = "Chimiset_wait";
			LSC_SetWhiteBoy(); // 在商店设置白小子
			pchar.questTemp.Saga.SharkHunt = "search_mush_1"; // 商店标记 - 寻找滑膛枪
			AddQuestRecord("SharkHunt", "11");
		break;
		
		case "freedom":
			dialog.text = "这就是我亲爱的朋友, 我欠你自由, 甚至可能是我的生命。 感谢你帮助我的兄弟们把我从肮脏的卡珀那里救出来。 我会给你这些护身符作为奖励。 我相信你会发现它们有用。 ";
			link.l1 = "谢谢你! 我没想到... ";
			link.l1.go = "Friend_1";
		break;
		
		case "freedom_1":
			dialog.text = "你还有别的要问吗, 白人朋友? ";
			link.l1 = "告诉我, 奇米塞特, 你认识白小子吗? ";
			link.l1.go = "Friend_9";
		break;
		
		case "freedom_2":
			DialogExit();
			NextDiag.CurrentNode = "Chimiset_wait";
			LSC_SetWhiteBoy(); // 设置白小子在商店
		break;
		
		//--> 信息块
		case "Chimiset_wait": // 成为朋友
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "哦! 我的白人朋友"+pchar.name+"! 你没淹死吗? spirits 救了你, 我知道... ";
				link.l1 = "我很好, 还活着, 奇米塞特。 Spirits? 也许你是对的, 这一切都是因为库库尔坎... ";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			dialog.text = "什么风把你吹来的, 我的好朋友? ";
			/*if (!CheckAttribute(npchar, "quest.story"))
			{
				link.l1 = "告诉我独角鲸首领是怎么死的。 你是唯一看到的人。 ";
				link.l1.go = "story";
			}*/
			if (!CheckAttribute(npchar, "quest.crab"))
			{
				link.l2 = "你提到过'圣赫罗尼莫号'附近海底的螃蟹。 你能描述一下那些怪物吗? ";
				link.l2.go = "crab";
			}
			link.l9 = "没什么特别的, 奇米塞特。 只是想见见你。 ";
			link.l9.go = "exit";
			NextDiag.TempNode = "Chimiset_wait";
		break;
		
		case "story":
			dialog.text = "艾伦.米尔罗之死的故事将在这里书写。 ";
			link.l1 = "好的! ";
			link.l1.go = "exit";
			npchar.quest.story = "true";
			NextDiag.TempNode = "Chimiset_wait";
		break;
		
		case "crab":
			dialog.text = "没有人知道它们从哪里来, 也不知道它们为什么长到如此巨大的体型。 我们对这些野兽了解不多。 它们存在, 很多人见过它们。 在浅水区的船只残骸中可以找到成群的它们。 它们在海底潜行, 捕食鱼类, 吃我们倾倒的所有垃圾\n它们是真正的威胁。 它们的钳子可以造成严重的伤口, 它们的颚还会释放一种危险的毒药, 类似于海洋鱼类的毒药。 如果中毒后不治疗, 人就会死亡。 幸运的是, 这种毒素可以用当地草药制成的解毒剂中和\n我们中有一个捕蟹人。 他过去常常带来它们的肉, 非常美味的菜肴。 但最重要的是: 他经常带来这些怪物的爪子和带毒的颚。 它们是我某些药水的主要成分。 可惜, 很久没有人给我带来这些了... ";
			link.l1 = "那个捕蟹人现在在哪里? ";
			link.l1.go = "crab_1";
		break;
		
		case "crab_1":
			dialog.text = "想想吧。 你必须准备好成为猎物, 同时捕猎这些野兽。 有一天他就再也没有回来。 这就是为什么我警告你在这些生物周围要小心和注意。 ";
			link.l1 = "我明白了... ";
			link.l1.go = "exit";
			npchar.quest.crab = "true";
			NextDiag.TempNode = "Chimiset_wait";
		break;
		//<—— 信息块
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
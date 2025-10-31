// 格莱迪斯.麦克阿瑟 - 海伦的养母
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
			if(pchar.questTemp.Saga == "helena1")
			{
				dialog.text = "啊, 船长! 你知道吗, 我把一切都告诉海伦了。 你无法想象我心里的负担减轻了多少! ";
				link.l1 = "你做得很对, 麦克阿瑟小姐。 这女孩需要知道真相。 我来这里也是为了她。 ";
				link.l1.go = "Helena_hire";
			}
			else
			{
				dialog.text = "问候你, "+pchar.name+"! 很高兴见到你! 来些朗姆酒吗? ";
				link.l1 = "谢谢你, 麦克阿瑟小姐, 但我现在太忙了。 ";
				link.l1.go = "exit";			
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "FindHelena":
			dialog.text = "你想要什么, 先生? ";
			link.l1 = "你是格莱迪斯.麦克阿瑟吗? ";
			link.l1.go = "FindHelena_1";
		break;
		
		case "FindHelena_1":
			dialog.text = "我是。 我不记得你了, 年轻人。 你能解释一下想从我这里得到什么吗? ";
			link.l1 = "我对你女儿失踪的故事很感兴趣, 麦克阿瑟小姐。 你为什么认为她失踪了? 我听说海伦有一支非常熟练的船员... ";
			link.l1.go = "FindHelena_2";
		break;
		
		case "FindHelena_2":
			dialog.text = "啊, 我绝对肯定! 看, 我已故丈夫的忌日就在五天前。 海伦爱她的父亲, 她绝不会错过这个日子。 她只离开几天去从友好的米斯基托人那里接收一批红木。 \n印第安人尊敬并害怕我们的庇护人扬.斯文森, 他们绝不会伤害她。 斯文森先生已经和他们谈过了。 木头当天就装船了。 从那以后就没人见过海伦。 ";
			link.l1 = "也许是海盗袭击了她? ";
			link.l1.go = "FindHelena_3";
		break;
		
		case "FindHelena_3":
			dialog.text = "胡说! 你肯定已经知道斯文森先生是五位海盗男爵之一, 也是海岸兄弟会理事会的成员。 没有他的允许, 这里不允许任何海盗活动。 不过也可能是新来的海盗... ";
			link.l1 = "那西班牙人呢? 她会遇到西班牙巡逻队吗? ";
			link.l1.go = "FindHelena_4";
		break;
		
		case "FindHelena_4":
			dialog.text = "我不擅长政治, 但他们说当地的金银矿已经完全枯竭了, 没有多少宝藏值得高贵的西班牙绅士们冒生命危险。 所以他们很少来这里。 此外, 印第安人对他们有敌意。 \n与西班牙巡逻队的偶然相遇对海伦来说不会有坏处, 从他们的角度来看, 她没有做任何非法的事情。 ‘彩虹号’悬挂着荷兰国旗, 海伦的所有文件都齐全, 包括贸易许可证。 ";
			link.l1 = "在她最后一次航行前发生过什么特别的事情吗? 也许是你忽略的某个奇怪事件? ";
			link.l1.go = "FindHelena_5";
		break;
		
		case "FindHelena_5":
			dialog.text = "啊, 没有! 感谢上帝, 我们在这里过着平静的生活。 然而, 几周前海伦收到了另一封不请自来的爱慕者的信, 请求约会。 她是个漂亮的女孩, 但并不富有。 \n所以她有很多爱慕者, 尽管她不喜欢他们中的任何一个, 也不想结婚。 她已经用这种方式愚弄了很多人。 太轻浮了, 就像她母亲一样! ";
			link.l1 = "你看起来不像那种女人, 麦克阿瑟小姐... ";
			link.l1.go = "FindHelena_6";
		break;
		
		case "FindHelena_6":
			dialog.text = "什么? 啊, 不管了, 我很伤心。 我刚才说到哪了? 啊, 对, 信。 不管怎样, 那封信是吉米.希金斯写的。 他是杰克曼的人, 住在马龙镇。 他经常访问我们的镇子。 杰克曼也是海盗男爵, 但斯文森先生不喜欢他, 我不知道为什么。 ";
			link.l1 = "那海伦呢? ";
			link.l1.go = "FindHelena_7";
		break;
		
		case "FindHelena_7":
			dialog.text = "哦, 她笑得很大声。 一天前她收到了一位英国护卫舰船长的求婚, 她甚至拒绝了他。 现在这个海盗旧船上的普通水手... 不可能, 肖恩.麦克阿瑟的女儿需要一个更有气势的丈夫! ";
			link.l1 = "那英国船长叫什么名字? ";
			link.l1.go = "FindHelena_8";
		break;
		
		case "FindHelena_8":
			dialog.text = "哦, 我怎么会知道? 真正的绅士很少来这里。 对不起, 我不是有意冒犯你。 去问那个希金斯吧。 他一定记得他的名字。 吉米曾试图为海伦和那个船长决斗。 他的伙伴们勉强阻止了他。 但他们俩都在海伦启航前几天离开了布鲁维尔德。 ";
			link.l1 = "好吧, 谢谢你的故事。 我会尽力找到你爱的人。 如果我知道了什么, 我会告诉你或斯文森先生。 我希望能找到你的女儿, 她还活着, 安然无恙。 ";
			link.l1.go = "FindHelena_9";
		break;
		
		case "FindHelena_9":
			dialog.text = "你要去找她吗? 上帝与你同在, 让他指引你, 强化你的手! 我会为你祈祷! 告诉我你的名字, 可敬的人? ";
			link.l1 = ""+pchar.name+"。 "+GetFullName(pchar)+"。 我希望很快带着好消息回来, 麦克阿瑟小姐。 再见! ";
			link.l1.go = "FindHelena_10";
		break;
		
		case "FindHelena_10":
			DialogExit();
			NextDiag.CurrentNode = "FindHelena_wait";
			AddQuestRecord("Saga", "1");
			pchar.questTemp.Saga = "maruntown";// 前往杰克曼处
			SetFunctionTimerCondition("Gladis_SetHome", 0, 0, 1, false);
			int iTime = 25-MOD_SKILL_ENEMY_RATE;
			if(bImCasual)
			{
				NewGameTip("探索模式: 任务持续时间加倍");
				SetFunctionTimerCondition("Helena_AntiguaOver", 0, 0, iTime*2, false);
			}
			else SetFunctionTimerCondition("Helena_AntiguaOver", 0, 0, iTime, false);
		break;
		
		case "FindHelena_wait":
			dialog.text = "你有关于我可怜女儿的新消息吗, "+pchar.name+"? ";
			link.l1 = "对不起, 麦克阿瑟小姐, 到目前为止我没有什么新消息要告诉你, 但不要绝望。 我会继续搜索。 没有坏消息本身也是好消息。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "FindHelena_wait";
		break;
		
		case "Helena_die":
			dialog.text = "你来得太晚了, 船长。 我可怜女儿的尸体在安提瓜的海岸被发现了。 主啊, 他们在她死前是如何折磨她的! 我没能保护好我美丽的女孩... ";
			link.l1 = "我很抱歉。 我无能为力... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_exit";
		break;
		
		case "Gladis_exit":
			dialog.text = "啊, 年轻人, 请让我独自悲伤... ";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_exit";
		break;
		
		case "Gladis_regard":
			dialog.text = "我甚至不知道如何感谢你, 船长, 感谢你救了我的女儿。 她把一切都告诉我了, 我钦佩你的勇敢和荣誉。 拿着这些金达布隆。 虽然不多, 但我是真心诚意地提供的。 甚至不要考虑拒绝! ";
			link.l1 = "好吧, 格莱迪斯, 我不会拒绝。 但我救你女儿不是为了金币, 我希望你知道这一点。 ";
			link.l1.go = "Gladis_regard_1";
			link.l2 = "把这些钱留给你自己吧, 格莱迪斯。 你比我更需要它。 ";
			link.l2.go = "Gladis_regard_2";
			sld = characterFromId("Helena");
			LAi_SetStayType(sld);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			// 打开城市
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", false);
		break;
		
		case "Gladis_regard_1":
			TakeNItems(pchar, "gold_dublon", 100);
			dialog.text = "我很高兴能够以某种方式回报你高尚的行为。 我家的大门永远为你敞开。 海伦和我随时都很高兴见到你。 ";
			link.l1 = "谢谢你, 麦克阿瑟小姐。 有机会我会来看你和海伦。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_wait";
		break;
		
		case "Gladis_regard_2":
			dialog.text = "啊, 求你了... 我只是想回报你高尚的行为。 要知道我家的大门永远为你敞开。 海伦和我随时都很高兴见到你。 ";
			link.l1 = "谢谢你, 麦克阿瑟小姐。 有机会我会来看你和海伦。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_wait";
			pchar.questTemp.Saga.Helena_friend = "true";// 海伦未来行为的属性
		break;
		
		case "Gladis_wait":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Gladys")) {
				dialog.text = "船长, 我们家永远欢迎你! 你是为海伦来的吗? 恐怕她把自己锁在房间里了 - 一定是这几天累坏了。 别担心, 她有时会这样。 ";
				link.l1 = "真的吗? 你确定她没事吗? ";
				link.l1.go = "after_drinking";
				
				DeleteAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Gladys");
				break;
			}
		
			dialog.text = "啊, 德莫尔先生! 我总是很高兴在我家见到我女儿的救星。 你想见海伦吗? 她在楼上她的房间里。 在失去‘彩虹号’和她被奇妙地营救后, 她避免外出。 这是我第一次看到她如此困惑... ";
			link.l1 = "谢谢你, 麦克阿瑟小姐。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_wait";
		break;
		
		case "Gladis_history":
			dialog.text = "啊, 德莫尔先生! 我总是很高兴在我家见到我女儿的救星。 你想见海伦吗? ";
			link.l1 = "不。 我想问你几个问题, 我真的希望你能坦诚相告。 海伦的安全取决于此。 你熟悉这枚戒指吗? ";
			link.l1.go = "Gladis_history_1";
		break;
		
		case "Gladis_history_1":
			RemoveItems(pchar, "bucher_ring", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "我的上帝! 这是... 她父亲的戒指! ";
			link.l1 = "麦克阿瑟先生的? ";
			link.l1.go = "Gladis_history_2";
		break;
		
		case "Gladis_history_2":
			dialog.text = "不。 海伦是我们的继女, 但她不知道, 她的父母去世了, 所以我决定把她当作自己的孩子收养。 肖恩收养了她, 但即使是他也不知道她不是我的女儿。 ";
			link.l1 = "那么她的亲生父母是谁? ";
			link.l1.go = "Gladis_history_3";
		break;
		
		case "Gladis_history_3":
			dialog.text = "我知道她的父亲是一名海盗, 在护卫舰‘Neptune’上被称为‘屠夫’。 我只见过他两次。 她的母亲是一位美丽的年轻女子, 红头发, 穿着男人的衣服。 这几乎是我能告诉你的关于她的全部, 除了她是个坏母亲。 \n我永远不会把这样一个婴儿留在陌生人手中。 他们俩都死得很悲惨。 而承诺的信使二十年后才出现, 结果就是你。 是屠夫派你来的吗? 他还活着吗? ";
			link.l1 = "冷静点, 格莱迪斯小姐! 没有理由怀疑屠夫复活了, 尽管你是第二个有这个想法的人。 我最近遇到了一个本该给你看这枚戒指的人... ";
			link.l1.go = "Gladis_history_4";
		break;
		
		case "Gladis_history_4":
			dialog.text = "...";
			link.l1 = "一个简单的事件阻止了他及时这样做, 他一生都因为未能完成船长的最后命令而痛苦。 他不久前去世了, 而且... 好吧, 悲伤的消息够多了。 告诉我, 格莱迪斯, 海伦的母亲没有给她的孩子留下任何纪念她的信物吗? 也许是某个小东西? ";
			link.l1.go = "Gladis_history_5";
		break;
		
		case "Gladis_history_5":
			dialog.text = "她给我留了一块奇怪的旧地图。 开玩笑说这是她的遗产。 那张纸能有什么用? 我相信这只是一个恶意的玩笑。 她当时很兴奋, 有点神志不清。 但我保留了这个‘礼物’。 \n谁知道呢... 如果你想要, 我可以把它给你, 如果你答应有一天告诉我整个故事。 ";
			link.l1 = "绝对可以, 麦克阿瑟小姐。 我会把这片碎片带走一段时间。 我需要和斯文森先生谈谈。 ";
			link.l1.go = "Gladis_history_6";
		break;
		
		case "Gladis_history_6":
			GiveItem2Character(pchar, "map_half_beatriss"); // 地图的一半
			PlaySound("interface\important_item.wav");
			dialog.text = "你又帮了我们一次, 德莫尔先生! 而我不知道如何感谢你。 至少拿走我丈夫的手枪吧。 他总是为它感到自豪, 并告诉我它非常罕见。 它在这里躺了很长时间了。 让它为你服务! 拿着, 拿着! ";
			link.l1 = "谢谢, 格莱迪斯。 这把手枪真的很棒。 谢谢你, 再见。 ";
			link.l1.go = "Gladis_history_7";
			if (CheckCharacterItem(pchar, "chest"))
			{
				link.l2 = "让这把手枪为海伦服务吧。 我有足够的武器了。 ";
				link.l2.go = "Gladis_history_8_1";
			}
		break;
		
		case "Gladis_history_7":
			DialogExit();
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "pistol5");
			pchar.questTemp.Saga = "svenson2";
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(pchar, "questTemp.Saga.Helena_friend");
			AddQuestRecord("Saga", "22");
			AddCharacterExpToSkill(pchar, "Leadership", 50);
		break;
		
		case "Gladis_history_8_1":
			dialog.text = "但你为什么一直拒绝我的礼物? 你让我难过... ";
			link.l1 = "我想我现在能让你高兴了。 我要把信使本应交给你的金币还给你, 以感谢你对屠夫船长女儿的宝贵照顾。 当然, 这些达布隆无法回报你所有的爱和忠诚, 但它们本来就属于你。 你可以用它们做任何你想做的事。 ";
			link.l1.go = "Gladis_history_8";
		break;
		
		case "Gladis_history_8":
			dialog.text = "啊, 船长! 我不知道该说什么... 我无法想象竟然存在如此... 高尚的人! 去找我女儿, 告诉她这个好消息! ";
			link.l1 = "我这就去, 麦克阿瑟小姐。 ";
			link.l1.go = "Gladis_history_9";
		break;
		
		case "Gladis_history_9":
			DialogExit();
			RemoveItems(pchar, "chest", 1);
			pchar.questTemp.Saga = "svenson2";
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Saga", "22");
			sld = characterFromId("Helena");
			GiveItem2Character(sld, "pistol5");
			EquipCharacterbyItem(sld, "pistol5");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
		break;
		
		case "Helena_hire":
			dialog.text = "你是认真的吗? 你是什么意思? ";
			link.l1 = "根据斯文森先生的要求, 我打算雇佣海伦在我的船上担任军官。 她处于极大的危险之中。 当扬和我处理这件事时, 海伦需要可靠的保护。 我希望我能提供这样的保护。 ";
			link.l1.go = "Helena_hire_1";
		break;
		
		case "Helena_hire_1":
			dialog.text = "啊, 太好了! 我自己都不敢向你要求这个。 这将是对我女儿最好的保护。 海伦会很高兴再次航行的! ";
			link.l1 = "谢谢你的称赞, 麦克阿瑟小姐。 现在我得去见你的... 继女了。 ";
			link.l1.go = "exit";
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", false);// 打开海伦的卧室
			sld = characterFromId("Helena");
			sld.dialog.currentnode = "Helena_hire";
			pchar.questTemp.Saga = "helena2";
		break;
		
		case "saw_sex":
			dialog.text = "哦, 上帝! 我的小女儿! ";
			link.l1 = "格莱迪斯, 你不知道要敲门吗? ! ";
			link.l1.go = "saw_sex_1";
		break;
		
		case "saw_sex_1":
			dialog.text = "哦, 请原谅我, 年轻人! 我这就走! 海伦, 记住我告诉你的话! ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveGladysTalk");
		break;
		
		case "after_drinking":
			dialog.text = "我想这次她只是工作过度了。 她把一切都告诉我了, 船长! 谢谢你昨天帮她选了一艘新船! ";
			link.l1 = "嗯? 嗯, 不客气。 再见, 麦克阿瑟夫人。 ";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Gladis_wait";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
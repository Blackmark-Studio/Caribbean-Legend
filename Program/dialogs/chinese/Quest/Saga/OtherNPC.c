// 萨迦任务其他NPC的对话
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
			dialog.text = "想要点什么? ";
			link.l1 = "不, 没什么。 ";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
//---------------------------------------------吉米在马龙镇的房子里------------------------------------
		case "Jimmy":
			dialog.text = "你想要什么? 没看见我正伤心吗! 在我把你踢下楼梯之前滚开! ";
			link.l1 = "好吧, 买个更大带楼梯的房子吧。 到时候我们再聊把人踢下楼梯的事, 英雄... ";
			link.l1.go = "Jimmy_1_1";
			link.l2 = "你为什么这么沮丧, 吉米? 如果不是因为某个漂亮女人, 我这辈子都不喝朗姆酒! 只有女人才会让你这样的老海狼威胁老朋友... ";
			link.l2.go = "Jimmy_1_2";
		break;
		
		case "Jimmy_1_1":
			dialog.text = "我讨厌像你这样挑剔的人! 你总是拿到更好的蛋糕。 他们不让我杀那个暴发户, 所以我要把怒火发泄在你身上! ";
			link.l1 = "... ";
			link.l1.go = "Jimmy_fight";
		break;
		
		case "Jimmy_fight":
			DialogExit();
			AddDialogExitQuestFunction("Saga_Jimmy_fight");
		break;
		
		case "Jimmy_1_2":
			dialog.text = "是吗? 我认识你吗? 该死的, 我不记得你了... ";
			link.l1 = "是我, "+pchar.name+"! 在你差点把那个穿外套的傲慢家伙开膛破肚之后, 我们在布鲁维尔德度过了一段美好时光。 他叫什么来着? 我忘了... 不管怎样, 如果我在海上遇到他, 我才不在乎他双桅横帆船的大炮! ";
			link.l1.go = "Jimmy_2";
		break;
		
		case "Jimmy_2":
			dialog.text = "他叫亚瑟! 亚瑟.多诺万, ‘杨梅’号双桅横帆船的船长! 肮脏的混蛋! 所以你同意我差点把他送去见魔鬼? ";
			link.l1 = "当然! 他完全没有机会, 但你的伙伴们干涉了。 原谅他们, 他们不想让你因为谋杀海军军官而被绞死。 ";
			link.l1.go = "Jimmy_3";
		break;
		
		case "Jimmy_3":
			dialog.text = "啊! 要是我有船就好了! 那个混蛋在安提瓜附近很容易追踪... 哈! 如果你把他送入海底, 我欠你一个人情! ";
			link.l1 = "成交, 哈哈! 顺便问一下, 伦巴真的值得你这么痛苦吗? ";
			link.l1.go = "Jimmy_4";
		break;
		
		case "Jimmy_4":
			dialog.text = "当然! 我从未见过比她更好的人。 但她只是在嘲笑我。 每个人都想要那个美人鱼。 一些水手偷偷告诉我, 我们的雅各布在找一个长得像我伦巴的女孩。 他也想要她! 我现在怎么能听从他的命令? ";
			link.l1 = "安静点, 伙计! 隔墙有耳... 你为什么认为杰克曼在找伦巴? ";
			link.l1.go = "Jimmy_5";
		break;
		
		case "Jimmy_5":
			dialog.text = "他肯定在找! 他在找某个刽子手亨利和一个二十岁。 金发蓝眼的女孩。 来自伯利兹的某个格莱迪斯.钱德勒一定是她的监护人。 ";
			link.l1 = "等等! 格莱迪斯的姓不一样。 而且她是她的母亲! ";
			link.l1.go = "Jimmy_6";
		break;
		
		case "Jimmy_6":
			dialog.text = "杰克曼很狡猾! 你不能毫无准备地抓住他! 我追求伦巴有一段时间了, 发现格莱迪斯正好在二十年前嫁给了肖恩.麦克阿瑟。 在那之前, 她住在伯利兹。 她的第一任丈夫叫皮特.钱德勒。 \n可怜的皮特在一场醉酒斗殴中被杀。 他们说麦克阿瑟本人对此负责, 因为他当时对丰满的格莱迪斯有好感。 她成了寡妇, 手里还带着一个婴儿。 孩子没比爸爸多活多久, 不久就死于发烧。 \n就在格莱迪斯和肖恩带着一个女孩出现在布鲁维尔德的几个月后, 他们声称是麦克阿瑟的女儿。 那么, 格莱迪斯怎么可能这么快又生下一个孩子? 你明白吗? ";
			link.l1 = "你告诉过别人这件事吗? ";
			link.l1.go = "Jimmy_7";
		break;
		
		case "Jimmy_7":
			dialog.text = "还没有。 闭上你的嘴, 否则... 。 好吧, 你了解我! ";
			link.l1 = "是的, 我了解。 你有个烂舌头, 会把秘密告诉任何人。 伦巴把你赶走是对的, 多嘴的人... ";
			link.l1.go = "Jimmy_8_1";
			link.l2 = "当然! 我会守口如瓶! 现在我得走了。 再见, 吉米。 ";
			link.l2.go = "Jimmy_8_2";
		break;
		
		case "Jimmy_8_1":
			dialog.text = "你... 你说什么? ! ";
			link.l1 = "你不会有机会告诉别人了... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Saga_KillToJimmy_kino");
		break;
		
		case "Jimmy_8_2":
			DialogExit();
			AddDialogExitQuestFunction("Saga_Jimmy_DlgExit");
		break;
// < —吉米 
		
//-------------------------------------------多诺万的双桅横帆船, 登船-----------------------------------------
		//多诺万
		case "Donovan_abordage":
			PlaySound("Voice\English\saga\Artur Donovan.wav");
			dialog.text = "啊, 你这个怪物! ";
			link.l1 = "你在和自己说话吗, 先生? 伦巴在哪里? ";
			link.l1.go = "Donovan_abordage_1";
		break;
		
		case "Donovan_abordage_1":
			dialog.text = "什么伦巴? 我的船上没有带绰号的人渣。 这是英国海军舰艇! ";
			link.l1 = "别跟我装傻, 多诺万。 你完全明白我在说谁。 那个女孩在哪里? 海伦在哪里? 回答我, 你这个肮脏的混蛋... ";
			link.l1.go = "Donovan_abordage_2";
		break;
		
		case "Donovan_abordage_2":
			dialog.text = "海伦? 我的船上没有陆地妓女, 你这个狗屎! ";
			link.l1 = "没有陆地妓女? 很难相信, 因为其中一个此刻就站在我面前... 我想继续我们的谈话没有意义了。 去死吧, 你这个可怜的蠕虫! ";
			link.l1.go = "Donovan_abordage_3";
		break;
		
		case "Donovan_abordage_3":
			chrDisableReloadToLocation = true;//关闭地点
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Saga_AfterDonovanBoarding");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Takehelen = "true";//标志, 已登船
		break;
		
		//我们的水手
		case "Tempsailor":
			dialog.text = "船长, 我们按照您的吩咐搜索了所有船舱和货舱。 我们在货舱里发现了一个被锁链锁住的女孩... ";
			link.l1 = "真是个混蛋! 正如我所想... 你们给女孩解开锁链了吗? ";
			link.l1.go = "Tempsailor_1";
		break;
		
		case "Tempsailor_1":
			dialog.text = "当然, 船长。 她已被安全带到您的船上。 ";
			link.l1 = "做得好! 把她带到我的船舱, 等我们结束这里的事情, 我想和她谈谈。 ";
			link.l1.go = "Tempsailor_2";
		break;
		
		case "Tempsailor_2":
			dialog.text = "是, 船长! ";
			link.l1 = "... ";
			link.l1.go = "Tempsailor_3";
		break;
		
		case "Tempsailor_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
		break;
		//< —登多诺万的双桅横帆船
		
//----------------------------------------寻找恩里克.贡萨莱斯, 卡塔赫纳----------------------------------
		//假贡萨莱斯#1, 房子
		case "GonsalesA":
			dialog.text = "想要点什么? ";
			link.l1 = "你好, 刽子手! 屠夫船长向你问好。 ";
			link.l1.go = "GonsalesA_1_1";
			link.l2 = "我叫查尔斯.德.莫尔。 我代表她的老朋友寻找恩里克, 贡萨莱斯夫人的儿子。 我认为你就是他... ";
			link.l2.go = "GonsalesA_2_1";
		break;
		
		case "GonsalesA_1_1":
			dialog.text = "搞什么鬼! 我不认识什么屠夫! ";
			link.l1 = "得了吧, 亨利。 告诉我为什么杰克曼的海盗在找你, 我就不伤害你。 ";
			link.l1.go = "GonsalesA_1_2";
		break;
		
		case "GonsalesA_1_2":
			dialog.text = "救命! 海盗! 杀人了! ";
			link.l1 = "闭嘴, 白痴! 你的叫喊会引来半个镇子的人。 啊, 这就是你想要的? ! ";
			link.l1.go = "GonsalesA_1_fight";
		break;
		
		case "GonsalesA_1_fight":
			DialogExit();
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_MoveCharacter(NPChar, "EnemyFight");
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetCheck("EnemyFight", "Saga_KillGonsalesA");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Trap = "true";
		break;
		
		case "GonsalesA_2_1":
			dialog.text = "嗯... 先生, 你一定弄错了。 我在一个外国家庭长大, 不记得我的生母。 我沿用了监护人的姓氏。 我不知道我母亲的名字, 但我怀疑是贡萨莱斯。 你可以打听我, 任何老居民都会证实我的话。 我的继父是个名人, 他自己没有孩子, 所以我继承了这所房子和... ";
			link.l1 = "对不起。 看来我弄错了。 再见。 ";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) link.l1.go = "GonsalesA_3_1";
			else link.l1.go = "GonsalesA_2_2";
		break;
		
		case "GonsalesA_2_2":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			chrDisableReloadToLocation = false;//打开地点
			AddQuestRecord("Saga", "17");
		break;
		
		// belamour参与了卡塔赫纳事件 -->
		case "GonsalesA_3_1":
			dialog.text = "我不这么认为。 ";
			link.l1 = "什么? ";
			link.l1.go = "GonsalesA_3_2";
		break;
		
		case "GonsalesA_3_2":
			dialog.text = "你知道, 最近我们的殖民地遭到了海盗的猛烈袭击。 我相信你听说过? 由于这次袭击, 无数人受苦。 我没有受伤, 但我继承的生意现在正处于艰难时期。 而所有这些灾难的罪魁祸首是这些海盗的首领, 一个名叫查理.普林斯的恶棍。 ";
			link.l1 = "我很抱歉, 但这和我有什么关系? ";
			link.l1.go = "GonsalesA_3_3";
		break;
		
		case "GonsalesA_3_3":
			dialog.text = "哈哈, 看看这只无辜的羔羊! 我建议你赔偿我的损失, 因为你是罪魁祸首。 给我一万五千比索, 我就当你从没来过我家。 ";
			if (sti(pchar.money) >= 15000)
			{
				link.l1 = "你们都这么记仇... 这是你的钱。 记住, 如果有人发现我来过这个镇子, 我会回来找你。 ";
				link.l1.go = "GonsalesA_3_4";
			}
			link.l2 = "一万五千? 嗯... 我觉得你的命不值那么多。 所以, 我想直接杀了你让你闭嘴更便宜。 ";
			link.l2.go = "GonsalesA_3_5";
		break;
		
		case "GonsalesA_3_4":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			chrDisableReloadToLocation = false;//打开地点
			AddQuestRecord("Saga", "171");
		break;
		
		case "GonsalesA_3_5":
			dialog.text = "卫兵! 海盗! 杀人了! ";
			link.l1 = "闭嘴, 白痴! ";
			link.l1.go = "GonsalesA_3_6";
		break;
		
		case "GonsalesA_3_6":
			DialogExit();
			iTemp = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE - 2;
			for (i=1; i<=2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("SpSold"+i, "sold_" + NationShortName(SPAIN) + "_" + (rand(1) + 1), "man", "man", iTemp, SPAIN, 0, true, "soldier"));
				SetFantomParamFromRank(sld, iTemp, true);         
				LAi_SetWarriorType(sld); 
				LAi_warrior_DialogEnable(sld, false);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			}
			sld = GetCharacter(NPC_GenerateCharacter("SpOfficer", "off_" + NationShortName(SPAIN) + "_" + (rand(1) + 1), "man", "man", iTemp, SPAIN, 0, true, "quest"));
			FantomMakeCoolFighter(sld, 25, 100, 100, "blade_13", "pistol6", "bullet", 150);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_MoveCharacter(NPChar, "EnemyFight");
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetCheck("EnemyFight", "Saga_KillGonsalesAK");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Trap = "true";
		break;
		// < —参与了卡塔赫纳事件
		
		// 假贡萨莱斯#2, 街道
		case "GonsalesB":
			PlaySound("Voice\English\citizen\Pirati v Gorode-08.wav");
			dialog.text = "我看你喜欢我的弯刀。 如果你想要, 我可以卖给你。 我不会要太多, 我很想喝些朗姆酒, 但我口袋空空。 ";
			link.l1 = "我到底为什么需要它? 森林魔鬼让我向你问好。 ";
			link.l1.go = "GonsalesB_1_1";
			if (sti(pchar.money) >= 1000)
			{
				link.l2 = "嗯, 是的。 你确实有一把好弯刀。 多少钱? ";
				link.l2.go = "GonsalesB_2_1";
			}
		break;
		
		case "GonsalesB_1_1":
			dialog.text = "他最好给我几百比索! ";
			link.l1 = "所以你认识斯文森? ";
			link.l1.go = "GonsalesB_1_2";
		break;
		
		case "GonsalesB_1_2":
			dialog.text = "去你妈的, 去你妈的斯文森, 送他去见魔鬼。 去森林魔鬼还是海魔鬼, 我不在乎。 如果你不愿意通过买我的弯刀来帮助一个病人, 那我就免费把它插进你屁股里。 ";
			link.l1 = "真的吗? 让我看看你怎么做到, 混蛋! ";
			link.l1.go = "GonsalesB_1_fight";
		break;
		
		case "GonsalesB_1_fight":
			chrDisableReloadToLocation = true;
			DialogExit();
			LAi_group_MoveCharacter(NPChar, "EnemyFight");
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetCheck("EnemyFight", "Saga_KillGonsalesB");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Trap = "true";
		break;
		
		case "GonsalesB_2_1":
			dialog.text = "我看你是个有经验的人! 一千比索, 它就是你的了。 ";
			link.l1 = "成交! ";
			link.l1.go = "GonsalesB_2_2";
		break;
		
		case "GonsalesB_2_2":
			AddMoneyToCharacter(pchar, -1000);
			GiveItem2Character(pchar, "blade_10");
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			dialog.text = "在卡塔赫纳只有两把这样的弯刀 - 我的和灯塔的老阿尔瓦雷斯的。 但他不会卖他的。 他是个伪君子, 我一英里外就能闻到前海盗的味道。 这把刀对他来说是某种护身符。 \n看来这个可怜的灵魂在哀叹他想忘记的事情。 这一定是他每个月都去教堂的原因, 因为罪孽让他无法入睡。 ";
			link.l1 = "我看你也有一些历史。 这一定是斯文森说的那个人。 他说如果我在卡塔赫纳遇见你, 就向你问好。 ";
			link.l1.go = "GonsalesB_2_3";
		break;
		
		case "GonsalesB_2_3":
			dialog.text = "斯文森? 从没听说过。 我叫恩里克.加拉多。 但如果你的斯文森有一瓶朗姆酒给我, 我愿意为他当亨利。 你想叫我什么都行, 只要别叫我吃饭迟到。 那么, 我们走吗? ";
			link.l1 = "今天不行。 斯文森很远, 但酒馆在附近。 你的口袋不再空空如也了, 所以保重, 恩里克。 ";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) link.l1.go = "GonsalesB_3_1";
			else link.l1.go = "GonsalesB_2_4";
		break;
		
		case "GonsalesB_2_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "19");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega();
		break;
		
		// belamour参与了卡塔赫纳事件 -->
		case "GonsalesB_3_1":
			dialog.text = "但它们还没完全满。 我想要更多。 你会付给我。 ";
			link.l1 = "我很困惑... 你不珍惜自己的生命吗? 你打算在城市中间抢劫我? 在你刚刚把武器卖给我之后? ";
			link.l1.go = "GonsalesB_3_2";
		break;
		
		case "GonsalesB_3_2":
			dialog.text = "不, 你会自己付给我。 你知道为什么吗? ";
			link.l1 = "好奇听听。 ";
			link.l1.go = "GonsalesB_3_3";
		break;
		
		case "GonsalesB_3_3":
			dialog.text = "我认出你了。 我因为在酒馆醉酒斗殴被关在地牢里, 这时你的人冲进监狱, 砍倒了所有卫兵。 我设法拿到了卫兵尸体上的钥匙, 逃到了街上。 城市着火了, 到处是尸体。 鲜血和火药味... 就像登船时一样! 透过烟雾, 我看到你从总督官邸出来。 很有诗意, 不是吗? 哟-嗬-嗬, 你好, 查理.普林斯! ";
			link.l1 = "别那样大喊大叫! 知道你所知道的, 你尤其不应该试图敲诈我。 你甚至意识到我能对你做什么吗? ";
			link.l1.go = "GonsalesB_3_4";
		break;
		
		case "GonsalesB_3_4":
			dialog.text = "在你曾经抢劫过的城市中间? 你什么也做不了。 所以, 总结一下... 我们这样做: 你现在给我... 比如说, 一万比索。 我想这足够一个月了。 然后你走你的路! 不管是去找你亲爱的亨利, 去斯文森那里, 还是去找你选择的任何其他魔鬼... 如果你不给, 我只需要大喊, 他们就会把你拖进一个专门准备的。 装满酷刑工具的私人房间。 ";
			if (sti(pchar.money) >= 10000)
			{
				link.l1 = "该死的, 拿上你的一万比索, 从我的视线中消失! 上帝保佑, 我再也不想见到你。 ";
				link.l1.go = "GonsalesB_3_5";
			}
			link.l2 = "够了, 我受够了。 你的武器是我的, 所以你没有机会, 人渣。 ";
			link.l2.go = "GonsalesB_3_7";
			link.l3 = "哈哈, 你很好! 你知道吗? 现在我早就把其他人从肚子到喉咙切开了。 但像你这样的人我需要。 这样如何: 我给你一万比索, 还给你‘绞刑者’, 每月再额外给三千 - 应该足够买酒了 - 你成为我船上的登船员。 ";
			link.l3.go = "GonsalesB_3_9";
		break;
		
		case "GonsalesB_3_5":
			dialog.text = "好吧, 好吧, 我已经走了! 祝你搜索顺利, 查理.普林斯! ";
			link.l1 = "... ";
			link.l1.go = "GonsalesB_3_6";
		break;
		
		case "GonsalesB_3_6":
			AddMoneyToCharacter(pchar, -10000);
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "191");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega();
		break;
		
		case "GonsalesB_3_7":
			dialog.text = "卫兵! 卫兵!!! 这是查理.普林斯!!! ";
			link.l1 = "你这个混蛋! ";
			link.l1.go = "GonsalesB_3_8";
		break;
		
		case "GonsalesB_3_8":
			DialogExit();
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			LAi_group_AttackGroup("Spain_citizens", LAI_GROUP_PLAYER);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "192");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega(); 
		break;
		
		case "GonsalesB_3_9":
			dialog.text = "你是建议我加入你的船员? ";
			link.l1 = "正是。 但这是一次性报价。 那么, 你说什么? 同意, 否则我就把你开膛破肚。 你不会真的认为你能轻易敲诈查理.普林斯, 对吧? ";
			link.l1.go = "GonsalesB_3_10";
		break;
		
		case "GonsalesB_3_10":
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34 && makeint(pchar.reputation.nobility) < 48)
			{
				dialog.text = "魔鬼! 查理.普林斯本人邀请我加入他的船员! 该死的, 我同意! 把我的刀和一万比索还给我。 从没想过会是这样! ";
				link.l1 = "给。 闭上你的嘴: 这个城市里没人需要知道我是谁, 明白吗? ";
				link.l1.go = "GonsalesB_3_11";
				break;
			}
			if(makeint(pchar.reputation.nobility) > 47)
			{
				dialog.text = "不。 你可能是个不错的船长, 但在我看来你有点太紧张了。 是的, 你曾经通过对卡塔赫纳的大胆突袭让西班牙人害怕 - 但那都是在马库斯.泰雷克斯的帮助下。 你没有勇气自己进行诚实的掠夺。 所以, 把钱交出来! ";
			}
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 35)
			{
				dialog.text = "不。 你确实是个臭名昭著的海盗, 但作为船长, 你看起来并不令人印象深刻。 你只是在马库斯.泰雷克斯的帮助下才设法掠夺了殖民地 - 你自己甚至不敢登上一艘破旧的单桅帆船。 所以, 把钱交出来! ";
			}
			if (sti(pchar.money) >= 10000)
			{
				link.l1 = "该死的, 拿上你的一万比索, 从我的视线中消失! 上帝保佑, 我再也不想见到你。 ";
				link.l1.go = "GonsalesB_3_5";
			}
			link.l2 = "够了, 我受够了。 你的武器是我的, 所以你没有机会, 人渣。 ";
			link.l2.go = "GonsalesB_3_7";
		break;
		
		case "GonsalesB_3_11":
			dialog.text = "明白, 我不是傻瓜。 ";
			link.l1 = "很好。 ";
			link.l1.go = "GonsalesB_3_12";
		break;
		
		case "GonsalesB_3_12":
			DialogExit();
			AddMoneyToCharacter(pchar, -10000);
			LAi_RemoveLoginTime(npchar);
			npchar.quest.OfficerPrice = 3000;
			npchar.reputation.nobility = 30;
			npchar.dialog.FileName = "Enc_Officer_dialog.c";
			npchar.loyality = MAX_LOYALITY;
			GiveItem2Character(npchar, "blade_10");
			EquipCharacterByItem(npchar, "blade_10");
			TakeItemFromCharacter(pchar, "blade_10");
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			AddQuestRecord("Saga", "193");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega(); 
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
		break;
		// < —参与了卡塔赫纳事件
		
		//真正的贡萨莱斯 - 奥尔特加, 灯塔
		case "Ortega":
			dialog.text = "我今天和任何其他日子都不期待客人。 你想要什么? ";
			link.l1 = "你好, 刽子手。 森林魔鬼派我来的。 幸好我在杰克曼的人之前找到你。 他的人在整个加勒比海找你。 你很幸运, 亨利, 只有斯文森知道你出生在哪里。 他让我警告你。 ";
			link.l1.go = "Ortega_1";
		break;
		
		case "Ortega_1":
			dialog.text = "我现在明白了... 看来斯文森还活着, 没有忘记他的老朋友。 自从我第一次看到他作为新手站在受损的双桅横帆船上, 已经流过很多血了... 时光飞逝, 我剩下的时间不多了\n我想在这片荒地上自然死亡, 远离人类, 靠近大海。 但如果杰克曼回到加勒比海, 他不会放过我。 这不是我的错, 但我欠他的主人。 无论如何, 现在谁会相信我。 \n我不怕死亡, 只怕痛苦。 而杰克曼知道很多关于痛苦的事情。 一想到它, 我的心就停止跳动, 一切都变得黑暗。 ";
			link.l1 = "但屠夫二十年前就被绞死了, 所以你不必偿还任何人的债务。 如果你害怕杰克曼, 可以把债务给我。 我想你无论如何都会见到他。 ";
			link.l1.go = "Ortega_2";
		break;
		
		case "Ortega_2":
			dialog.text = "绞死像屠夫这样的人并不容易。 圣约翰的前刽子手可以告诉你很多关于从地狱回来的死者的有趣故事。 而雅各布被他的船长教导得很好, 所以我不确定我最害怕谁。 ";
			link.l1 = "杰克曼为什么需要你? ";
			link.l1.go = "Ortega_3";
		break;
		
		case "Ortega_3":
			dialog.text = "我不得不把黄金交给一个寡妇, 作为保护屠夫女儿安全的报酬。 你为什么那样看着我? 是的, 她在‘Neptune’号沉没前不久出生。 他没能及时回来接她, 所以派我来照顾婴儿和她的监护人。 ";
			link.l1 = "监护人的名字是格莱迪斯.钱德勒吗? ";
			link.l1.go = "Ortega_4";
		break;
		
		case "Ortega_4":
			dialog.text = "别装傻。 如果杰克曼在找我, 那是因为他需要屠夫的女儿。 你一定已经知道他在找一个来自伯利兹。 名叫格莱迪斯和她养女的女人。 对我诚实, 我可能会信任你。 ";
			link.l1 = "你应该告诉格莱迪斯什么? ";
			link.l1.go = "Ortega_5";
		break;
		
		case "Ortega_5":
			dialog.text = "没什么。 我应该给她看屠夫的戒指, 这样她就知道我是船长派来的信使。 我还得给她一箱达布隆作为婴儿的生活费。 我不得不杀了一个混蛋才拿到戒指。 这让我在安提瓜多待了一个月。 \n当我终于到达伯利兹时, 格莱迪斯已经走了, 城市被西班牙人烧毁和掠夺。 她设法卖掉了房子, 和她的新男友及婴儿海伦一起逃跑了。 我希望她照顾好了她, 没有把女孩卖给吉普赛人或妓院。 ";
			link.l1 = "屠夫女儿的名字是海伦, 对吗? ";
			link.l1.go = "Ortega_6";
		break;
		
		case "Ortega_6":
			dialog.text = "正是。 以屠夫母亲的名字命名。 如果你不怕活死人, 不怕用死人眼睛看着你的海盗, 那么我可以把戒指和黄金给你。 我从未碰过它们。 我快饿死了, 但我没有碰它们。 你想怎么处理都行。 作为回报, 我请求你... ";
			link.l1 = "发生了什么, 亨利? ! ";
			link.l1.go = "Ortega_7";
		break;
		
		case "Ortega_7":
			dialog.text = "你... u... 我请... 哦! ";
			link.l1 = "不! ";
			link.l1.go = "Ortega_8";
		break;
		
		case "Ortega_8":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			AddQuestRecord("Saga", "20");
			pchar.questTemp.Saga = "svenson1";
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "chest");
			GiveItem2Character(pchar, "bucher_ring"); //屠夫的戒指
			//灯塔看守返回计时器
			SetFunctionTimerCondition("Saga_LightmanReturn", 0, 0, 10, false);
			//如果主角在城市有继承, 设置中断
			if (CheckAttribute(pchar, "questTemp.Saga.Trap"))
			{
				pchar.quest.Saga_Trap.win_condition.l1 = "location";
				pchar.quest.Saga_Trap.win_condition.l1.location = "Mayak11";
				pchar.quest.Saga_Trap.function = "Saga_CreateTrapBandos";
				TraderHunterOnMap(true);
			}
			AddCharacterExpToSkill(pchar, "Sneak", 50);//隐蔽
			
			DeleteAttribute(pchar, "questTemp.HelenDrinking.Dialogs");
			//pchar.questTemp.HelenDrinking = "end_henry";
		break;
		
		//寻找贡萨莱斯的土匪, 灯塔
		case "saga_trap":
			dialog.text = "啊-啊, 我们好奇的朋友来了! 你终于找到贡萨莱斯了? 做得好, 你把我们带到了他那里... 我们不再需要你了。 伙计们, 杀了这个小丑! ";
			link.l1 = "去死吧, 蟹肉! ";
			link.l1.go = "saga_trap_1";
		break;
		
		case "saga_trap_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//允许战斗
			int n = makeint(MOD_SKILL_ENEMY_RATE/3);
			for (i=1; i<=3+n; i++)
			{	
				sld = characterFromId("sagatrap_sold_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		//< —寻找贡萨莱斯, 卡塔赫纳
		
//--------------------------------------------男爵回归任务的NPC---------------------------------
		
		// 多米尼加首领
		case "DominicaHead":
			dialog.text = "呜-啊! 呜-啊! 伟大的库库尔坎需要新的祭品! 哦-呃! 过去强大战士的灵魂来到我们村庄, 将被献祭给伟大的库库尔坎! 哦-呃! 所有人都向强大的战士灵魂鞠躬! ";
			link.l1 = "(微弱地) 搞什么鬼, 我在哪里? ";
			link.l1.go = "DominicaHead_1";
			NextDiag.TempNode = "DominicaHead";
			if (CheckCharacterItem(pchar, "Ultimate_potion"))
			{
				pchar.systeminfo.NoNotifications = true;
				RemoveItems(pchar, "Ultimate_potion", 1);
				DeleteAttribute(pchar,"systeminfo.NoNotifications");
				notification("使用了科曼奇药水", "None");
				LAi_SetCurHPMax(PChar);
				AddCharacterHealth(pchar, 50);
				DeleteAttribute(pchar, "chr_ai.poison");
				notification("你感觉健康恢复了! ", "None");
				//Log_Info("使用了科曼奇药水");
				//Log_Info("你感觉健康恢复了! ");
				//PlaySound("Ambient\Tavern\glotok_001.wav");
				PlaySound("Ambient\Horror\Fear_breath_01.wav");
			}
		break;
		
		case "DominicaHead_1":
			dialog.text = "哦-呃! 伟大的战士想被伟大的库库尔坎吃掉! 太阳升起, 阴影变短! 伟大的库库尔坎很快就会活过来! 我们带你去见他, 哦, 伟大的战士, 你将继续穿过祖先的土地! ";
			link.l1 = "(微弱地) 胡说八道... 又是库库尔坎? 嘿, 酋长, 我是和平来的! 我来这里是为了... ";
			link.l1.go = "DominicaHead_2";
		break;
		
		case "DominicaHead_2":
			dialog.text = "哦-呃! 伟大的战士说他想立即被献祭给库库尔坎。 哦, 伟大的战士! 我们现在去库库尔坎那里, 等待他的降临! 战士们! 我们有幸将祖先的灵魂带到库库尔坎面前! ";
			link.l1 = "(微弱地) 白痴... 好吧, 我得跟他们走。 幸好他们还没攻击我, 我现在这个样子无法自卫... ";
			link.l1.go = "DominicaHead_3";
		break;
		
		case "DominicaHead_3":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload1_back", "Saga_DominicaDollyReload", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
			for (i=2; i<=10; i++)
			{
				sld = characterFromId("Dominica_ind_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, npchar, "", -1);
			}
		break;
		
		case "DominicaHead_4":
			dialog.text = "我们来到库库尔坎面前, 伟大的祖先灵魂。 很快太阳下山, 阴影变长, 库库尔坎将降临我们。 等待, 伟大的战士... ";
			link.l1 = "(微弱地) 现在我明白了, 印第安战酋... ";
			link.l1.go = "DominicaHead_5";
		break;
		
		case "DominicaHead_5":
			DialogExit();
			bDisableCharacterMenu = true;//锁定F2
			AddQuestRecord("BaronReturn", "7");
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_DominicaDollyWait", 5.0);
			pchar.questTemp.Saga.BaronReturn = "third_teleport";
		break;
		
		case "DominicaHead_6":
			dialog.text = "库库尔坎活了! 库库尔坎与我们同在! 伟大的战士可以被献祭给库库尔坎! 战士们, 向伟大的祖先灵魂鞠躬! ";
			link.l1 = "(微弱地) 离远点, 酋长。 我自己来。 这不是我第一次... ";
			link.l1.go = "DominicaHead_7";
		break;
		
		case "DominicaHead_7":
			DialogExit();
			bDisableCharacterMenu = false;//解锁F2
			AddQuestRecord("BaronReturn", "8");
			for (i=2; i<=10; i++)
			{
				sld = characterFromId("Dominica_ind_"+i);
				LAi_SetActorType(sld);
			}
		break;
		
//----------------------------------------巴尔巴宗的诱惑任务NPC----------------------------------
		// 偷丝绸的渔船船长, 海上
		case "BarbCapBarkas":
			dialog.text = "有什么可以帮助您的, 先生? ";
			link.l1 = "嗯, 嗯.. 告诉我, 伙计, 你在这里做什么? ";
			link.l1.go = "BarbCapBarkas_1";
		break;
		
		case "BarbCapBarkas_1":
			dialog.text = "我在这里做什么? 我是个渔夫, 我在这里钓鱼。 你他妈的为什么用这种语气审问我? ";
			link.l1 = "别对我撒谎, 伙计。 也许你真的是个渔夫, 但你在这里不是钓鱼。 有价值的船用丝绸被扔进了海里, 就在这个位置。 而你的出现对我来说很可疑。 ";
			link.l1.go = "BarbCapBarkas_2";
		break;
		
		case "BarbCapBarkas_2":
			dialog.text = "什么胡说八道? 你在说什么丝绸? ";
			link.l1 = "什么丝绸? 中国丝绸... 别装傻! 现在听我说: 要么你立即从货舱里把丝绸拿出来给我, 要么我自己拿。 但是, 首先, 我的登船队会处理你和你的人。 那么? 要我叫我的人吗? ";
			link.l1.go = "BarbCapBarkas_3";
		break;
		
		case "BarbCapBarkas_3":
			dialog.text = "不! 先生, 我不知道... 那些包裹只是漂浮在周围, 所以我决定... ";
			link.l1 = "把丝绸带到我的船上。 快点! ";
			link.l1.go = "BarbCapBarkas_4";
		break;
		
		case "BarbCapBarkas_4":
			dialog.text = "是, 是, 当然。 我们马上就去做, 只是别拿我的船! ";
			link.l1 = "快动起来! 我没时间... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Saga_BarbBarkasSilk");
		break;
		
		case "BarbCapBarkas_5":
			dialog.text = "给, 我们把找到的所有东西都带来了 - 全部九包。 这就是全部, 我发誓... ";
			link.l1 = "很好。 你可以继续钓鱼, 但以后不要觊觎别人的东西! ";
			link.l1.go = "BarbCapBarkas_6";
		break;
		
		case "BarbCapBarkas_6":
			DialogExit();
			npchar.DontDeskTalk = true;
			npchar.lifeday = 0;
			LAi_SetStayType(npchar);
			pchar.quest.BarbBarkas_Sink.over = "yes"; //移除中断
			pchar.quest.BarbBarkas_Abordage.over = "yes"; //移除中断
			NextDiag.CurrentNode = "BarbCapBarkas_7";
			AddQuestRecord("BarbTemptation", "6");
			pchar.questTemp.Saga.BarbTemptation = "give_silk";
			AddCharacterExpToSkill(pchar, "Fortune", 100);//运气
			AddCharacterExpToSkill(pchar, "Sneak", 50);//隐蔽
		break;
		
		case "BarbCapBarkas_7":
			dialog.text = "你已经得到了你想要的。 我什么都没有了! 你还需要什么? ";
			link.l1 = "放松, 伙计。 我要走了。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "BarbCapBarkas_7";
		break;
		
		// 莫雷尔, 沉没船只的船长, 监狱
		case "Morelle":
			dialog.text = "如果你是巴尔巴宗派来的, 那么告诉他我不想自己离开监狱。 我宁愿等待审判。 即使荷兰的麻绳套在我脖子上, 也比他的‘好意’强。 ";
			link.l1 = "别胡说八道了。 你的领航员告诉雅克你死了。 他派我来寻找你扔进海里的丝绸。 你的双桅帆船上有多少? ";
			link.l1.go = "Morelle_1";
		break;
		
		case "Morelle_1":
			dialog.text = "是我的错, 该死的。 信使带来了九包给巴尔巴宗的丝绸。 我下令追踪他。 他吵吵嚷嚷, 所以我们不得不割开他的喉咙。 他的藏匿处还有额外的三包, 我自己拿了, 藏在我的藏匿处。 但似乎我们引起了不必要的注意。 \n他们很快找到了我们, 一支荷兰巡逻队在公海等待‘盐狗’号。 我们没能逃脱。 如果你不告诉巴尔巴宗关于我的事, 你可以自己拿走丝绸。 藏匿处在大凯斯海滩的石头之间靠近死胡同的地方。 我可能再也不需要它了。 ";
			link.l1 = "很好。 我不会告诉巴尔巴宗你还活着。 如果关于他的传言是真的, 那么你被荷兰人绞死更好。 或者, 也许你会幸运, 他们判你服苦役。 ";
			link.l1.go = "Morelle_2";
		break;
		
		case "Morelle_2":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
            npchar.lifeday = 0;
			// 计时器 - 模型
			//int m = Findlocation("Shore40");
			//locations[m].models.always.Roll = "Roll_of_rolls";
			//Locations[m].models.always.Roll.locator.group = "quest";
			//Locations[m].models.always.Roll.locator.name = "quest1";
			pchar.quest.Saga_MorelGoods.win_condition.l1 = "locator";
			pchar.quest.Saga_MorelGoods.win_condition.l1.location = "Shore40";
			pchar.quest.Saga_MorelGoods.win_condition.l1.locator_group = "quest";
			pchar.quest.Saga_MorelGoods.win_condition.l1.locator = "quest1";
			pchar.quest.Saga_MorelGoods.function = "Saga_SetMorelGoods";
			AddCharacterExpToSkill(pchar, "Fortune", 200);//运气
			AddCharacterExpToSkill(pchar, "Sneak", 200);//隐蔽
		break;
		
		// 男仆, 杰克曼在卡斯特维尔的兄弟
		case "valet":
			dialog.text = "我在等那个知道白鲨狩猎何时开始的人。 ";
			link.l1 = "狩猎已经开始。 ";
			link.l1.go = "valet_1";
		break;
		
		case "valet_1":
			dialog.text = "终于! 现在仔细听着。 你必须去拉维加拜访马库斯.泰雷克斯, 告诉他双桅横帆船‘分离器’号在特克斯岛附近被袭击, 现在藏在南湾。 她的船长受了重伤, 船员在等待帮助。 你救了‘分离器’号的一名水手, 他告诉了你所有情况。 他现在死了。 这就是你所知道的。 明白了吗? ";
			link.l1 = "你为什么需要我做这个? 我等了这么久就为了这个... ";
			link.l1.go = "valet_2";
		break;
		
		case "valet_2":
			dialog.text = "你拿钱办事, 不是来问问题的。 不过你说得对。 我得警告你, 泰雷克斯在确定你说的是实话之前不会让你走。 但一旦他弄清楚一切, 他会好好付你钱。 如果他能做到的话... ";
			link.l1 = "你在骗我, 先生... 为什么你不想亲自接受他的感谢? ";
			link.l1.go = "valet_3";
		break;
		
		case "valet_3":
			dialog.text = "天哪! 我不喜欢你的好奇心! 你的废话总有一天会把你送进坟墓。 ";
			link.l1 = "是啊, 有时候我就是忍不住。 尤其是当我看到有人想骗我的时候。 不, 伙计, 现在我们按我的规则来。 你他妈的主人是谁? 回答, 否则我让你说! ";
			link.l1.go = "valet_4";
		break;
		
		case "valet_4":
			dialog.text = "你... 混蛋! 巴尔巴宗会为此付出代价, 你这个吃屎的! ";
			link.l1 = "哈! 我就知道。 准备好, 恶棍! ";
			link.l1.go = "valet_5";
		break;
		
		case "valet_5":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//允许战斗
			chrDisableReloadToLocation = true;//关闭地点
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_ValetDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "vensan":
			// Addon 2016-1 Jason 海盗系列补丁17/1
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
			{
				dialog.text = "查理.普林斯? 你在这里做什么? 啊-啊, 该死的, 是你! 这都是你的所作所为! ";
				link.l1 = "放松伯尼。 我站在你这边。 埋伏已经解除, 你和你的船安全了。 ";
				link.l1.go = "vensan_8";
			}
			else
			{
				dialog.text = "你是谁, 该死的? 你怎么到这里来的? 现在离开, 我的船被布雷了, 岸上的混蛋可以一炮炸掉它。 ";
				link.l1 = "别担心, 先生。 岸上的埋伏已经被清除。 只要你不在甲板上点烟斗, 你的船现在就安全了。 你叫什么名字? ";
				link.l1.go = "vensan_1";
			}
		break;
		
		case "vensan_1":
			dialog.text = "文森特。 伯纳德.文森特。 你叫什么名字? ";
			link.l1 = "船长"+GetFullName(pchar)+"。 我会割断这些绳子, 让你自由... ";
			link.l1.go = "vensan_2";
		break;
		
		case "vensan_2":
			LAi_SetStayType(npchar);
			dialog.text = "哦... 感谢你。 我该如何感谢你? ";
			link.l1 = "还没结束, 先生。 你的船员还有人活着吗? ";
			link.l1.go = "vensan_3";
		break;
		
		case "vensan_3":
			dialog.text = "我的三十名船员被锁在货舱里... ";
			link.l1 = "释放他们, 立即离开这里。 ";
			link.l1.go = "vensan_4";
		break;
		
		case "vensan_4":
			dialog.text = "但是... ";
			link.l1 = "别浪费时间, 伯纳德。 你可以稍后在拉维加感谢我... 泰雷克斯可能也会感谢我。 ";
			link.l1.go = "vensan_5";
		break;
		
		case "vensan_5":
			dialog.text = "那么, 你不是偶然来这里的? 你什么都知道? ";
			link.l1 = "是的, 我知道。 我设法揭露了杰克曼的阴谋和他杀死马库斯的计划。 哦, 让泰雷克斯坐着别动, 他的干预会把杰克曼吓跑。 ";
			link.l1.go = "vensan_6";
		break;
		
		case "vensan_6":
			dialog.text = "我一定会告诉他! 你现在要走了吗? ";
			link.l1 = "是的。 你也应该快点。 ";
			link.l1.go = "vensan_7";
		break;
		
		case "vensan_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto2", "none", "", "", "", 5.0);
			Ship_SetTaskRunaway(SECONDARY_TASK, GetCharacterIndex("Cap_Vensan"), GetMainCharacterIndex());
			pchar.questTemp.Saga.BarbTemptation.Vensan_free = "true";
			if (!CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.vensan_attack"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = characterFromId("Mary");
				else sld = characterFromId("Helena");
				sld.dialog.currentnode = "sea_bomb"; 
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto6");
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			AddCharacterExpToSkill(pchar, "Leadership", 100);//领导力
			AddCharacterExpToSkill(pchar, "Fortune", 100);//运气
			AddCharacterExpToSkill(pchar, "Sneak", 50);//隐蔽
			sld = characterFromId("Cap_Vensan");
			sld.lifeday = 1;
			sld.DontDeskTalk = true;
		break;
		
		// Addon 2016-1 Jason 海盗系列补丁17/1
		case "vensan_8":
			dialog.text = "真的吗? 听着, 我很抱歉, 兄弟... ";
			link.l1 = "忘了吧。 让我割断绳子, 让你自由。 ";
			link.l1.go = "vensan_9";
		break;
		
		case "vensan_9":
			LAi_SetStayType(npchar);
			dialog.text = "操... 我感觉不到我的手... ";
			link.l1 = "伯尼, 船上还有幸存者吗? ";
			link.l1.go = "vensan_10";
		break;
		
		case "vensan_10":
			dialog.text = "三十人被锁在货舱里... ";
			link.l1 = "释放他们, 赶紧离开这里。 现在! ";
			link.l1.go = "vensan_11";
		break;
		
		case "vensan_11":
			dialog.text = "但是... ";
			link.l1 = "立即航行到拉维加。 把这堆烂摊子的全部细节告诉马库斯。 ";
			link.l1.go = "vensan_12";
		break;
		
		case "vensan_12":
			dialog.text = "马库斯派你来的? ";
			link.l1 = "他没有。 我设法揭露了一个混蛋的阴谋。 他计划通过这个阴谋除掉马库斯。 让他暂时坐着别动, 不要干预... 我稍后会亲自向他解释一切。 请告诉他别再生我的气了。 ";
			link.l1.go = "vensan_7";
		break;
		
 //--------------------------------------Sharp遗嘱任务的NPC--------------------------------------------------
		// 海胆, 保罗.莫利根
		case "molligan":
			dialog.text = "先生, 你在我的船上想要什么? ";
			link.l1 = "日安, 保罗。 你的名字是保罗.莫利根, 对吗? ";
			link.l1.go = "molligan_0";
		break;
		
		case "molligan_0":
			dialog.text = "是的, 是我。 我能为你做什么? ";
			link.l1 = "我叫"+GetFullName(pchar)+", 扬.斯文森派我来的。 ";
			link.l1.go = "molligan_1";
		break;
		
		case "molligan_1":
			dialog.text = "扬? 啊-啊, 我记得你。 当然! 你最近经常去他家。 那么扬想从我这里得到什么? ";
			link.l1 = "你匆忙从布鲁维尔德起航。 扬想让你的船额外装载两百中心的桃花心木, 运到布里奇敦的威洛比勋爵那里。 把你的船准备好, 我的人会把桃花心木装进你的货舱。 ";
			link.l1.go = "molligan_2";
		break;
		
		case "molligan_2":
			dialog.text = "桃花心木? 扬这么说的? 嗯。 你为什么不自己运到巴巴多斯? 为什么是我? ";
			link.l1 = "因为你要航行到那里, 而我不是。 我有斯文森的紧急任务, 所以我不能浪费时间也航行到布里奇敦。 此外, 扬不信任我与威洛比勋爵做生意, 他希望你去做。 抱歉。 现在让我们装货, 我得走了。 ";
			link.l1.go = "molligan_3";
		break;
		
		case "molligan_3":
			dialog.text = "听着, 我的货舱里没有任何空余空间了。 尽管我很想帮忙, 但我没法按简的要求去做。 ";
			link.l1 = "没空间? 奇怪... 简告诉我你还有些空位。 ";
			link.l1.go = "molligan_4";
		break;
		
		case "molligan_4":
			dialog.text = "确实, 但简不知道我给‘牡蛎号’装备了更重的加农炮。 我没法装载比现在更多的货物了。 所以你自己把木材运到巴巴多斯吧, 伙计? 告诉简我做不到。 和威洛比打交道很简单: 去见他, 把货物交给他, 然后拿收据。 足够简单。 ";
			link.l1 = "嗯。 这不是我的计划... 我们检查一下你的货舱, 好吗? 我的军需官非常擅长打包货物, 他能把货物装进你的货舱, 甚至还能给你留些空间... ";
			link.l1.go = "molligan_5";
		break;
		
		case "molligan_5":
			dialog.text = "伙计, 我不能再装其他货物了。 你想让我扔掉加农炮, 让‘牡蛎号’失去防护吗? ";
			link.l1 = "好吧, 如果你这么确定... 但简要不高兴了, 考虑一下! ";
			link.l1.go = "molligan_6";
		break;
		
		case "molligan_6":
			dialog.text = "我会向斯文森解释的, 别担心。 毕竟, 这是他的错, 他没问过我船的吨位。 ";
			link.l1 = "唉, 现在我得一路把那些原木运到巴巴多斯, 该死的... 再见, 伙计。 ";
			link.l1.go = "molligan_7";
		break;
		
		case "molligan_7":
			DialogExit();
			// 设置隐藏检查
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > (10+hrand(50)))
			{
				pchar.questTemp.Saga.Molligan.friend = "true"; // 会有葡萄弹暴击的机会
				sTemp = "这个恶棍仍然毫无察觉。 我应该靠近点, 用葡萄弹射击他。 突然袭击在任何战斗中总是能获胜。 ";
				log_Testinfo("Friends");
				AddCharacterExpToSkill(pchar, "Fortune", 200);// 运气
				AddCharacterExpToSkill(pchar, "Sneak", 300);// 隐藏
			}
			else
			{
				pchar.questTemp.Saga.Molligan.enemy = "true"; // 会攻击
				sTemp = "";
				log_Testinfo("Enemies");
				AddCharacterExpToSkill(pchar, "Sneak", 150);// 隐藏
			}
			AddQuestRecord("Testament", "7");
			AddQuestUserData("Saga", "sText", sTemp);
			NextDiag.CurrentNode = "molligan_8";
			npchar.DontDeskTalk = true; // patch-5
		break;
		
		case "molligan_8":
			dialog.text = "我们说清楚了, 不是吗? ";
			link.l1 = "是的, 是的。 我要回我的船了。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "molligan_8";
		break;
		
	//-----------------------------------------过去阴影的NPC--------------------------------------------
		// 吉姆.本森, 醉醺醺的梅吉
		case "benson":
			dialog.text = "你想从我这里得到什么? 我不喜欢闲聊和赌博。 而且我独自喝朗姆酒。 另外, 上次航行后我心情很糟糕。 ";
			link.l1 = "那你上次航行期间发生了什么特别的事? ";
			link.l1.go = "benson_1";
		break;
		
		case "benson_1":
			dialog.text = "一个好人信任我, 我却因为船员的要求把他扔下了船。 ";
			link.l1 = "那他有什么过错? ";
			link.l1.go = "benson_2";
		break;
		
		case "benson_2":
			dialog.text = "我是新来的, 在这里认识的人不多。 所以我雇了那个善良的胖子做医生, 却不知道他的过去。 自从我们离开巴巴多斯, 海盗就一直在追我们。 他们为什么需要我的破船? \n多亏了一场强风, 我们才勉强逃脱。 为此喝了一杯。 而那个胖傻瓜想不出更好的办法, 只能告诉大家海盗很可能在追他, 因为他是前刽子手, 知道一些不该知道的事情。 \n当然, 我的船员们非常生气。 真的吗? 船上有个刽子手, 还当医生! 而且也没人想惹海盗... 所以我不得不让那个可怜的人下船。 都是他的错, 他就不该开口。 但我为那个乡巴佬感到难过, 他是个出色的医生。 他只花了一分钟就治好了我的宿醉。 ";
			link.l1 = "该死! 你那位医生的名字是雷蒙德.贝克, 对吗? ";
			link.l1.go = "benson_3";
		break;
		
		case "benson_3":
			dialog.text = "是的。 没错。 你怎么知道的? 你在追我吗? ";
			link.l1 = "不, 不是我。 我只是需要那个人, 他是个伟大的医生。 你让他在哪里下船的? ";
			link.l1.go = "benson_4";
		break;
		
		case "benson_4":
			dialog.text = "北纬15度28分, 西经63度28分。 快点, 先生! 他一定还活着, 如果你救了他, 就能把责任从我身上移开! ";
			link.l1 = "我马上起锚! ";
			link.l1.go = "benson_5";
		break;
		
		case "benson_5":
			DialogExit();
			NextDiag.CurrentNode = "benson_6";
			AddQuestRecord("Shadows", "3");
			npchar.lifeday = 0;
			bQuestDisableMapEnter = false;
			pchar.quest.Saga_Shadows_Baker.win_condition.l1 = "location";
			pchar.quest.Saga_Shadows_Baker.win_condition.l1.location = "Dominica";
			pchar.quest.Saga_Shadows_Baker.function = "Saga_SetBakerBoat";
			DeleteAttribute(pchar, "Cheats.SeaTeleport");
		break;
		
		case "benson_6":
			dialog.text = "船长, 快点! 他一定还活着! ";
			link.l1 = "是, 是, 我这就去... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "benson_6";
		break;
		
	//---------------------------------------杰克曼矿场的强盗-----------------------------------------------
		case "mine_bandit":
			locCameraFromToPos(6.21, 2.31, 8.46, true, -2.26, -1.10, 4.99);
			if (CheckAttribute(pchar, "questTemp.Saga.MineAttack"))
			{
				dialog.text = "嘿! 待在那里! 别动。 这片区域已被封锁! ";
				link.l1 = "别太苛刻了, 伙计! 朋友! 杰克曼派我们来的。 我们需要去矿场。 主人的命令... ";
				link.l1.go = "mine_attack";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "嘿! 待在那里! 别动。 这片区域已被封锁! ";
				link.l1 = "嗯。 但我想过去... 你他妈的为什么拦住我? ";
				link.l1.go = "mine_bandit_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "啊-啊, 又是你? 我看你不明白... 伙计们, 开火!! ";
				link.l1 = "... ";
				link.l1.go = "mine_bandit_fire";
			}
		break;
		
		case "mine_bandit_0":
			dialog.text = "来吧, 往前走! ";
			link.l1 = "好吧... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "mine_bandit_0";
		break;
		
		case "mine_bandit_1":
			dialog.text = "因为我身后的矿场是私有财产, 我在这里阻止任何像你这样的陌生人通过。 你最好转身离开这个地方, 陌生人。 我们的加农炮装着葡萄弹, 再走一步你就会变成一滩血水。 ";
			link.l1 = "呵, 我明白了。 你的矿场守卫很森严。 好吧, 我走。 ";
			link.l1.go = "mine_bandit_exit";
			link.l2 = "你这个混蛋! 好吧, 我们走着瞧谁会变成一滩水! ";
			link.l2.go = "mine_bandit_2";
		break;
		
		case "mine_bandit_exit":
			DialogExit();
			LAi_SetGuardianType(npchar);
			LAi_group_MoveCharacter(npchar, "PIRATE_CITIZENS");
			chrDisableReloadToLocation = false;// 打开位置
			DoQuestReloadToLocation("Mine_02", "reload", "reload3", "");
		break;
		
		case "mine_bandit_2":
			dialog.text = "我给过你机会... 伙计们, 开火!! ";
			link.l1 = "... ";
			link.l1.go = "mine_bandit_fire";
		break;
		
		case "mine_bandit_fire":
			DialogExit();
			DoQuestCheckDelay("Saga_MineBanditsFire", 1.5);
		break;
		
		case "mine_banditx":
			locCameraFromToPos(6.21, 2.31, 8.46, true, -2.26, -1.10, 4.99);
			if (CheckAttribute(pchar, "questTemp.Saga.MineAttack"))
			{
				dialog.text = "嘿! 走开! 这片区域已被封锁! ";
				link.l1 = "嘿, 放松点, 伙计! 杰克曼派我们来的。 我们需要去矿场。 主人的命令... ";
				link.l1.go = "mine_attackx";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "嘿! 走开! 这片区域已被封锁! ";
				link.l1 = "嗯。 那里面有什么? ";
				link.l1.go = "mine_banditx_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "啊-啊, 又是你? 我看你不明白... 伙计们, 开火!! ";
				link.l1 = "... ";
				link.l1.go = "mine_banditx_fire";
			}
		break;
		
		case "mine_banditx_1":
			dialog.text = "与你无关。 滚蛋, 否则我们就开枪了, 我发誓! ";
			link.l1 = "冷静点。 我这就走。 ";
			link.l1.go = "mine_banditx_exit";
			link.l2 = "你这个混蛋! 好吧, 我们走着瞧谁会开枪! ";
			link.l2.go = "mine_banditx_2";
		break;
		
		case "mine_banditx_exit":
			DialogExit();
			LAi_SetGuardianType(npchar);
			LAi_group_MoveCharacter(npchar, "PIRATE_CITIZENS");
			DoQuestReloadToLocation("Mine_04", "reload", "reload3", "");
		break;
		
		case "mine_banditx_2":
			dialog.text = "我给过你机会... 火枪准备! 开火!! ";
			link.l1 = "... ";
			link.l1.go = "mine_banditx_fire";
		break;
		
		case "mine_banditx_fire":
			DialogExit();
			DoQuestCheckDelay("Saga_MineBanditsxFire", 0.6);
		break;
		
		case "mine_attackx":
			dialog.text = "真的吗? 那你一定知道密码。 说出来, 如果你撒谎, 你会后悔的... ";
			link.l1 = "特里同";
			link.l1.go = "mine_wrongx_password";
			link.l2 = "海王星";
			link.l2.go = "mine_attackx_1";
			link.l3 = "百夫长";
			link.l3.go = "mine_wrongx_password";
			link.l4 = "鱼叉";
			link.l4.go = "mine_wrongx_password";
		break;
		
		case "mine_attackx_1":
			dialog.text = "正确。 但你, 伙计, 从错误的一侧来了。 他们没警告过你吗? 回去, 从枯井走左边的路。 然后绕过小山, 你就会看到正门。 ";
			link.l1 = "我不能从这里进吗? ";
			link.l1.go = "mine_attackx_2";
		break;
		
		case "mine_wrongx_password":
			dialog.text = "伙计们, 有探子! 火枪准备! 开火!! ";
			link.l1 = "... ";
			link.l1.go = "mine_banditx_fire";
		break;
		
		case "mine_attackx_2":
			dialog.text = "不行。 只能从中央入口进。 ";
			link.l1 = "好吧, 伙计... 嘿! 看! 栅栏顶上那他妈的是什么? ";
			link.l1.go = "mine_attackx_3";
		break;
		
		case "mine_attackx_3":
			DialogExit();
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Mine_banditx_"+i);
				LAi_RemoveCheckMinHP(sld);
			}
			sld = characterFromId("Svensons_sold_12");
			LAi_SetActorType(sld);
			LAi_ActorTurnToLocator(sld, "soldiers", "soldier1");
			LAi_ActorAnimation(sld, "shot", "Saga_MineBanditxDie", 1.0);
		break;
		
		case "mine_attack":
			dialog.text = "真的吗? 那你应该知道密码。 说出来, 让我听到。 如果你想骗我, 那将是你这辈子对别人开的最后一个玩笑。 ";
			link.l1 = "特里同";
			link.l1.go = "mine_wrong_password";
			link.l2 = "海王星";
			link.l2.go = "mine_attack_1";
			link.l3 = "百夫长";
			link.l3.go = "mine_wrong_password";
			link.l4 = "鱼叉";
			link.l4.go = "mine_wrong_password";
		break;
		
		case "mine_attack_1":
			dialog.text = "正确。 往前走。 营地的头儿在矿场入口左边的房子里。 去见他。 ";
			link.l1 = "好的, 伙计... ";
			link.l1.go = "mine_attack_2";
		break;
		
		case "mine_wrong_password":
			dialog.text = "伙计们, 有探子! 加农炮, 开火!! ";
			link.l1 = "... ";
			link.l1.go = "mine_bandit_fire";
		break;
		
		case "mine_attack_2":
			DialogExit();
			locCameraFollowEx(true);
			NextDiag.CurrentNode = "mine_attack_3";
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "ActorDialog_Any2Pchar", -1);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetActorDialogAny2Pchar(npchar.id, "", 0.0, 0.0);
		break;
		
		case "mine_attack_3":
			dialog.text = "还有什么? 你忘了什么吗? ";
			link.l1 = "是的。 有人让我向你问好。 ";
			link.l1.go = "mine_attack_4";
		break;
		
		case "mine_attack_4":
			dialog.text = "向我? 哈哈! 谁让你问好的? ";
			link.l1 = "简.斯文森, 你这个混蛋! ";
			link.l1.go = "mine_attack_5";
		break;
		
		case "mine_attack_5":
			DialogExit();
			AddDialogExitQuestFunction("Saga_MineAttack");
		break;
		
	// --------------------------- —袭击强盗矿场时的NPC对话 -------------------------------
		case "Svensons_off":
			dialog.text = LinkRandPhrase("我们会把那些混蛋撕碎! ", "我期待着打败那些混蛋! ", "杰克曼的奴才无权在西海域存在! 我们会把他们从这里赶走! ");
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Svensons_off";
		break;
		
		case "Svensons_sold":
			dialog.text = LinkRandPhrase("我们准备好战斗了! ", "我们会让他们看看! ", "他们甚至不知道自己在惹谁! ");
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Svensons_sold";
		break;
		
		case "gunner":
			PlaySound("Voice\English\evilpirates01.wav");
			dialog.text = "指挥官, 加农炮准备好了。 已经按你命令装了炸弹。 ";
			link.l1 = "我想这里没人料到我们会来... 是时候介绍我们自己了。 简告诉我他们的营地在这座山后面。 你能打到吗? ";
			link.l1.go = "gunner_0_1";
		break;
		
		case "gunner_0_1":
			dialog.text = "很简单, 指挥官。 让我们把炮管抬高一点, 应该就行了... 好了。 \n准备好! .. 开火!! ";
			link.l1 = "... ";
			link.l1.go = "gunner_0_2";
			npchar.quest.canonada = "1";
		break;
		
		case "gunner_0_2":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_Gunfire", 3.0);
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
		break;
		
		case "gunner_1":
			dialog.text = "";
			link.l1 = "嗯。 伦道夫, 你觉得我们打中什么了吗? 我想听听你的意见。 ";
			link.l1.go = "gunner_1_1";
		break;
		
		case "gunner_1_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");
			dialog.text = "指挥官, 我们确实打中了什么人或东西, 但我无法更具体了... 这该死的山挡住了视线。 我会改变角度。 \n准备! 开火! ";
			link.l1 = "... ";
			link.l1.go = "gunner_0_2";
			npchar.quest.canonada = "2";
		break;
		
		case "gunner_2":
			PlaySound("interface\abordage_wining.wav");
			PlaySound("types\warrior03.wav");
			dialog.text = "哈! 看, 指挥官! 有烟! 该死, 我们一定是打中了某个强盗的谷仓! 乌拉-啊! ";
			link.l1 = "是的, 我看到烟了... 毫无疑问, 这已经是一场史诗般的胜利了。 重新装弹, 瞄准小路, 看来我们的客人要来了。 我们会好好迎接他们的! ";
			link.l1.go = "gunner_2_1";
		break;
		
		case "gunner_2_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");
			dialog.text = "是, 是, 指挥官! 装炸弹! 炮手准备! 引信准备! 听我命令开火! ";
			link.l1 = "... ";
			link.l1.go = "gunner_2_2";
			npchar.quest.canonada = "3";
		break;
		
		case "gunner_2_2":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_LoginBandos_01", 6.0);
			LAi_ActorTurnToLocator(pchar, "goto", "goto14");
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
		break;
		
		case "gunner_3":
			PlaySound("interface\abordage_wining.wav");
			PlaySound("types\warrior03.wav");
			PlaySound("Voice\English\evilpirates05.wav");
			dialog.text = "哈哈, 那一定很疼! ";
			link.l1 = "别放松! 装弹! 我觉得他们还没受够。 更多人来了! ";
			link.l1.go = "gunner_3_1";
		break;
		
		case "gunner_3_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");//
			dialog.text = "是, 是, 指挥官! 装炸弹! 准备! 听我命令开火! ";
			link.l1 = "... ";
			link.l1.go = "gunner_3_2";
			npchar.quest.canonada = "4";
		break;
		
		case "gunner_3_2":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_LoginBandos_02", 5.0);
			LAi_ActorTurnToLocator(pchar, "goto", "goto14");
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
		break;
		
		case "gunner_5":
			PlaySound("types\warrior04.wav");
			PlaySound("Voice\English\evilpirates06.wav");
			dialog.text = "哈哈哈, 混蛋们向我们展示了他们的背影! 狗娘养的! 葡萄弹在这么近的距离把他们打得粉碎! 看来他们没有勇气再攻击我们了! ";
			link.l1 = "现在轮到我们了。 伦道夫, 你待在加农炮附近。 朝小路开几炮, 然后瞄准烟雾 —烧毁他们的巢穴! 只是别打到我们。 ";
			link.l1.go = "gunner_5_1";
		break;
		
		case "gunner_5_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");
			dialog.text = "是, 是, 指挥官! 准备加农炮! 装炸弹! ";
			link.l1 = "弟兄们! 拿起武器! 跟我来, 进攻! 乌拉!! ";
			link.l1.go = "attack";
		break;
		
		case "attack":
			DialogExit();
			n = Findlocation("mine");
			Locations[n].hidden_fire = true;
			PlaySound("interface\abordage_wining.wav");
			PlaySound("interface\abordage_wining.wav");
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
			if (GetCharacterIndex("Svensons_sold_12") != -1 && pchar.questTemp.Saga.MineAttack == "soldiers")
			{
				sld = characterFromId("Svensons_sold_12");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i=1; i<=8; i++)
			{
				if (GetCharacterIndex("Ourmine_sold_"+i) != -1)
				{
					sld = characterFromId("Ourmine_sold_"+i);
					if (i == 1) sld.MusketerDistance = 10; 
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				}
			}
			LAi_group_SetRelation("EnemyFight", "TMP_FRIEND", LAI_GROUP_NEITRAL);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_MineBandos_05Die");
			AddDialogExitQuest("MainHeroFightModeOn");	
			DoQuestCheckDelay("Saga_MineSetMusic", 0.3);
			// 启动10次自动射击
			iTotalTemp = 0;
			DoQuestCheckDelay("Saga_GunAutoFire", 7.0);
			bDisableCharacterMenu = false;// 解锁界面
			InterfaceStates.Buttons.Save.enable = true;// 允许保存
		break;
		
		case "convict":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = LinkRandPhrase("别伤害我, 我不是他们中的一员! 杀了那些强盗! ", "救我们, 伙计! 把他们都杀了! ", "砍他们, 朋友, 砍他们! 让他们死! ");
				link.l1 = "哈! 别担心, 我们现在就在这么做。 ";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("我们的奴役结束了吗? 你会释放我们吗? ", "呵, 我真的能活到看到这一天吗? ", "混蛋们把我们的血都榨干了... .");
				link.l1 = "我想你很快就能享受自由了, 伙计... ";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "convict";
		break;
		
		// 简.斯文森的妻子
		case "js_girl":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "你最好离开这个地方, 先生。 我们不包庇罪犯, 也不需要与殖民地当局发生冲突。 ";
				link.l1 = "好吧, 我这就走... ";
				link.l1.go = "exit";
				NextDiag.TempNode = "js_girl";
				break;
			}
			if(NPChar.quest.meeting == "0")
			{
				// 与海伦的第一次对话
				if(startHeroType == 4)
				{
					dialog.text = "啊, 海伦。 你在来见简之前本可以穿得更体面一点, 而不是展示你的真面目。 可惜他不相信我。 ";
					link.l1 = "我到底是什么样的? 他从小就帮着抚养我, 比任何人都了解我。 我对他没有秘密。 我从小就受这炎热的折磨, 所以我不得不以自己的方式应对, 仅此而已。 ";
					link.l1.go = "js_helen_ft";
					NextDiag.TempNode = "js_girl";
					NPChar.quest.meeting = "1";
					break;
				}
				dialog.text = TimeGreeting()+", 先生。 你想见简吗? ";
				link.l1 = "日安。 很高兴见到你, 小姐? ..";
				link.l1.go = "js_girl_1";
			}
			else
			{
				// 海伦的占位符
				if(startHeroType == 4)
				{
					dialog.text = "简在里面。 去吧, 没什么可看的, 你让我心烦。 ";
					link.l1 = "反正我也没什么心情。 ";
					link.l1.go = "exit";
					NextDiag.TempNode = "js_girl";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Joan")) {
					dialog.text = "Grr!";
					link.l1 = "也祝你身体健康, 斯文森夫人。 ";
					link.l1.go = "exit";
					break;
				}
				
				if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "blueveld")
				{
					dialog.text = TimeGreeting()+", " +GetFullName(pchar)+ "船长。 如果你是来找简的, 那我不得不让你失望了 —他不在这里。 他出去处理一些重要事务了。 ";
					link.l1 = "该死! 我需要他! 告诉我, 斯文森夫人, 他告诉你什么时候回来了吗? ";
					link.l1.go = "js_girl_3";
					break;
				}
				dialog.text = "啊-啊, 又是你, " +GetFullName(pchar)+ "船长... 往前走, 简像往常一样在楼上。 ";
				link.l1 = "谢谢你, 斯文森夫人... ";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "js_girl";
		break;
		
		case "js_girl_1":
			dialog.text = "夫人, 乔安娜.斯文森夫人。 ";
			link.l1 = "" +GetFullName(pchar)+ "船长。 ";
			link.l1.go = "js_girl_2";
		break;
		
		case "js_girl_2":
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "blueveld")
			{
				dialog.text = "船长? 好吧, 很高兴欢迎你到我家来。 但如果你是来找简的, 那我不得不让你失望了 —他不在这里。 他出去处理一些重要事务了。 ";
				link.l1 = "该死! 我需要他! 告诉我, 斯文森夫人, 他告诉你什么时候回来了吗? ";
				link.l1.go = "js_girl_3";
				break;
			}
			dialog.text = "船长? 好吧, 很高兴欢迎你到我家来。 我丈夫在二楼他的办公室里。 上楼吧。 ";
			link.l1 = "我知道了, 斯文森夫人... ";
			link.l1.go = "exit";
			NPChar.quest.meeting = "1";
			NextDiag.TempNode = "js_girl";
		break;
		
		case "js_girl_3":
			dialog.text = "没有。 他甚至没告诉我确切的返回日期, 因为他自己也不知道搜索需要多长时间。 ";
			link.l1 = "很抱歉打扰, 但我真的需要他... 他在进行什么搜索? ";
			link.l1.go = "js_girl_4";
		break;
		
		case "js_girl_4":
			dialog.text = "我告诉你吧。 可爱的海伦, 也被称为伦巴, 是他已故朋友肖恩.麦卡瑟的女儿, 失踪了。 简对待这个小捣蛋鬼就像对待自己的女儿一样。 她让他想起了他的旧爱, 有着同样鲁莽的脾气。 至少我认为这是魅力的原因。 \n不管怎样, 这个女孩一周前和她的纵帆船‘彩虹号’及其全体船员一起失踪了。 肖恩.麦卡瑟教她航海术, ‘彩虹号’是根据他的遗嘱传给她的。 现在她扮演起了船长... ";
			link.l1 = "她可能发生了什么事? ";
			link.l1.go = "js_girl_5";
		break;
		
		case "js_girl_5":
			dialog.text = "谁知道呢... 一周不算太长, 但麦卡瑟的遗孀确信她女儿出了什么事, 并且她也设法让简相信了这一点。 他召集了他的人, 自己开始寻找她, 但至今没有结果。 就我个人而言, 我认为海伦没事, 简只是在无缘无故地折磨自己。 \n他听了那个又老又胖的女人的胡话, 惊慌失措了。 这个女孩很可能此刻正在某个安全的地方, 远离人们的视线, 和另一个男朋友玩乐。 她一饿就会回来的。 ";
			link.l1 = "乔安娜, 我在哪里可以找到格拉迪斯? 我想和她谈谈... ";
			link.l1.go = "js_girl_6";
		break;
		
		case "js_girl_6":
			dialog.text = "她的房子在码头附近, 左边。 但她很可能不在那里。 她每天都站在堡垒的墙上, 寻找她宝贵的女儿。 ";
			link.l1 = "我明白了。 非常感谢你的信息! ";
			link.l1.go = "js_girl_7";
		break;
		
		case "js_girl_7":
			DialogExit();
			NextDiag.CurrentNode = "js_girl_8";
			sld = characterFromId("Gladis"); // 设置格拉迪斯在堡垒
			ChangeCharacterAddressGroup(sld, "SantaCatalina_fort", "goto", "goto53");
			LAi_SetStayType(sld);
			sld.dialog.currentnode = "FindHelena";
			pchar.questTemp.Saga = "gladis";
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("SantaCatalina_tavernkeeper"));
			DelMapQuestMarkCity("SantaCatalina");
		break;
		
		case "js_girl_8":
			dialog.text = "简还不在这里, 船长, 所以过会儿再来吧。 ";
			link.l1 = "我知道了... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "js_girl_8";
		break;
		
		case "js_helen_ft":
			dialog.text = "我得说, 你总是很热情。 你应该去教堂; 我几乎没见过你在那里。 ";
			link.l1 = "我的良心是清白的 —我没有什么需要忏悔的。 还在为他帮我供应船只而不是给你买另一件衣服而耿耿于怀吗, 乔安娜? ";
			link.l1.go = "js_helen_ft_1";
		break;
		
		case "js_helen_ft_1":
			dialog.text = "我? 耿耿于怀? 你不值得。 只是一切对你来说都太容易了, 而你不配。 ";
			link.l1 = "但我一得到那艘船, 就开始自己挣钱了。 自从他像捡流浪猫一样把你捡回来, 你就没工作过一天。 那么到底是谁在靠他生活? ";
			link.l1.go = "js_helen_ft_2";
		break;
		
		case "js_helen_ft_2":
			dialog.text = "你再这样说话, 总有一天会得到应有的报应。 简和格拉迪斯应该教过你一些礼貌。 好吧, 继续, 说你想说的 —然后滚出我的视线, 海伦。 他在里面。 ";
			link.l1 = "愚蠢的母鸡。 当然, 会的。 ";
			link.l1.go = "exit";
		break;
		
		// 亚历克斯的强盗
		case "Alexs_bandos":
			dialog.text = "嘿! 你在这里做什么? ";
			link.l1 = "我也想问你同样的问题 —你和你的伙伴在这里, 在我的地牢里做什么? ";
			link.l1.go = "Alexs_bandos_1";
		break;
		
		case "Alexs_bandos_1":
			dialog.text = "哈! 你的地牢? 它什么时候成你的了, 同性恋? ";
			link.l1 = "从你父亲犯了和你母亲上床的错误那一天起。 ";
			link.l1.go = "Alexs_bandos_2";
		break;
		
		case "Alexs_bandos_2":
			dialog.text = "你在自找麻烦吗? ";
			link.l1 = "听着, 伙计, 我给你最后一次机会离开这个地方。 这是我的地牢, 我不会让任何人随意进来, 明白吗? 我只需要吹一声口哨, 伊斯莱索罗的一半海盗一分钟内就会到这里。 ";
			link.l1.go = "Alexs_bandos_3";
		break;
		
		case "Alexs_bandos_3":
			dialog.text = "好吧, 那我们就试试让你闭嘴! ";
			link.l1 = "哈哈! 你真可悲, 垃圾! ";
			link.l1.go = "Alexs_bandos_4";
		break;
		
		case "Alexs_bandos_4":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Bermudes_Dungeon")], false);
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Alexs_bandos_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+5;
			int iScl = 25+2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("Alexs_bandos_5", "mush_ctz_8", "man", "mushketer", iRank, PIRATE, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "bullet", iScl*2+50);
			ChangeCharacterAddressGroup(sld, "Bermudes_Dungeon", "monsters", "monster8");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "AlexClock_BandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "helendrinking_gypsy":
			dialog.text = "等一下, 猎鹰! ";
			link.l1 = "时机不太好, 甜心。 ";
			link.l1.go = "helendrinking_gypsy_1";
		break;
		
		case "helendrinking_gypsy_1":
			dialog.text = "哦, 你错了, 帅哥。 这个女孩喜欢你, 我看得出来你也喜欢她。 ";
			link.l1 = "这不是最好的推荐... 好吧, 你想要什么? 施舍? ";
			link.l1.go = "helendrinking_gypsy_2";
		break;
		
		case "helendrinking_gypsy_2":
			dialog.text = "我想在你具有挑战性的事业中为你提供支持。 看这里! 一个魔法杯子和一种禁忌药膏。 杯子会帮助你在饮酒方面, 药膏会帮助你在爱情方面。 你会选哪个? 只要两千! ";
			link.l1 = "我什么都不需要 —我已经给了你们这类人一大笔银子了。 ";
			link.l1.go = "helendrinking_gypsy_refuse";
			if (sti(pchar.money) >= 2000) {
				link.l2 = "你说禁忌药膏? 好吧, 我承认我不是圣人。 给我。 ";
				link.l2.go = "helendrinking_gypsy_fuck";
				link.l3 = "一个杯子? 我看起来像个酒鬼吗? 好吧, 我是谁啊... 我要了! ";
				link.l3.go = "helendrinking_gypsy_drink";
			}
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_gypsy_refuse":
			dialog.text = "英俊但愚蠢。 那就飞走吧, 猎鹰。 ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_gypsy_drink":
			dialog.text = "哦, 别把它藏在你那无底的口袋里! 飞走吧, 猎鹰, 别犯罪! ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddMoneyToCharacter(pchar, -2000);
			GiveItem2Character(pchar, "totem_01");
			Log_Info("获得护身符'铁喉'! ");
			PlaySound("interface\important_item.wav");
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_gypsy_fuck":
			dialog.text = "哦, 别把它藏在你那无底的口袋里! 飞走吧, 猎鹰, 别犯罪! ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddMoneyToCharacter(pchar, -2000);
			GiveItem2Character(pchar, "totem_03");
			Log_Info("获得护身符'丘比特香膏'! ");
			PlaySound("interface\important_item.wav");
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
			Notification_Approve(false, "Helena");
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_joan":
			dialog.text = "啊! 滚出去, 你这个恶棍! 我告诉过你多少次不要爬进我的房子! 这是谁? ";
			link.l1 = "夫人, 我们已经认识了。 ";
			link.l1.go = "helendrinking_joan_1";
		break;
		
		case "helendrinking_joan_1":
			dialog.text = "德莫尔先生? 太好了! 这就是你和我丈夫做生意的方式吗? 我就知道! 我警告过简: 总有一天这个荡妇会开始带坏他的人! 你手里拿着什么? ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JoanDialog1");
		break;
		
		case "helendrinking_joan_2":
			dialog.text = "哇-哇-哇? ! 你怎么敢, 坏蛋? ! 你哪里也别想去; 我丈夫马上就到, 他会教你如何与长辈说话! ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JoanDialog3");
		break;
		
		case "helendrinking_fort_officer":
			dialog.text = "这里发生了什么事? 麦卡瑟小姐! 我对你父亲非常尊敬, 斯文森先生是我们的朋友... 但你不记得上次的结果了吗? \n这很令人失望, 以军官的名义, 令人失望! 你本可以邀请我们的! ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog");
		break;
		
		case "helendrinking_fort_officer_1":
			dialog.text = "感谢你的款待, 麦卡瑟小姐。 让我说, 我们都很高兴看到你回来。 发生的事情是一个巨大的谜团, 但镇上的人知道这件事并不奇怪。 不过, 我可以向你保证, 没有人会闲聊。 我为我们一位船长最近的行为表示诚挚的歉意。 我还想特别感谢你, 德莫尔先生。 ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog3");
		break;
		
		case "helendrinking_fort_officer_2":
			dialog.text = "一切都会好的, 小姐。 德莫尔先生, 我说实话 —尽管多诺万表现得像个真正的恶棍和强盗, 但舰队永远不会公开谴责他。 更有可能的是, 他们甚至会保护他。 你的小探险被写入了报告, 严重复杂化了我们两国之间的关系。 然而, 考虑到斯文森先生的影响力, 以及卡普斯特维尔对你做出的显著让步, 你没有什么可担心的。 ";
			link.l1 = "那太好了。 我说我们为此干杯! ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog1");
		break;
		
		case "helendrinking_poorman":
			dialog.text = "不好意思, 那工作怎么样了? ";
			link.l1 = "你还在这里? ";
			link.l1.go = "helendrinking_poorman_1";
		break;
		
		case "helendrinking_poorman_1":
			dialog.text = "亲爱的先生, 我还能去哪里? 只是去方便一下, 无意中听到了你们的伤感谈话, 有点激动。 我是说情绪上! ";
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.BoughtRainbow")) {
				link.l1 = "天哪! 好吧, 既然我答应了你, 也没办法。 去, 接管吧。 ";
				link.l1.go = "helendrinking_poorman_bought";
			} else {
				link.l1 = "我没有工作给你, 先生。 ";
				link.l1.go = "helendrinking_poorman_notbought";
			}
		break;
		
		case "helendrinking_poorman_bought":
			dialog.text = "是, 是, 船长! ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AddRainbow");
			AddDialogExitQuestFunction("HelenDrinking_LightsOut1NoArg");
		break;
		
		case "helendrinking_poorman_notbought":
			dialog.text = "太可惜了! 不管怎样, 谢谢你的款待, 船长! ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AddRainbow");
			AddDialogExitQuestFunction("HelenDrinking_LightsOut1NoArg");
		break;
		
		case "helensleep_amelia_mary":
			dialog.text = "奉父。 子。 圣灵之名... 进来吧, 我的孩子。 ";
			if (HelenSleep_TalkedToAmelia()) {
				link.l1 = "你好, 阿米莉亚妈妈。 你也要对我大喊大叫吗? ";
				link.l1.go = "helensleep_amelia_mary_know";
			} else {
				link.l1 = "消失! 这是什么噩梦? 发生了什么事? 我在做梦吗? ";
				link.l1.go = "helensleep_amelia_mary_notknow";
			}
		break;
		
		case "helensleep_amelia_mary_know":
			dialog.text = "不, 我的小猎鹰。 原谅简 —这个可怜的人情绪激动。 但是的, 我确实想骂你。 你为什么来教堂? 是为了忏悔你的罪孽? 还是为了那个红头发的? ";
			link.l1 = "我自己也不知道... ";
			link.l1.go = "helensleep_amelia";
			link.l2 = "你也看到她了吗? 她吸引了我的目光。 ";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia_mary_notknow":
			dialog.text = "你自己消失吧。 我们本应该已经见过面了, 但你一直在拖延。 你为什么来教堂? 是为了忏悔你的罪孽? 还是为了那个红头发的? ";
			link.l1 = "我自己也不知道... ";
			link.l1.go = "helensleep_amelia";
			link.l2 = "你也看到她了吗? 她吸引了我的目光。 ";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia_helen":
			dialog.text = "早上好, 我的猎鹰。 接待还没有开始, 请排队等候。 ";
			if (HelenSleep_TalkedToAmelia()) {
				link.l1 = "你好, 阁下。 你也要对我大喊大叫吗? ";
				link.l1.go = "helensleep_amelia_helen_know";
			} else {
				link.l1 = "消失! 这是什么噩梦? 发生了什么事? 我在做梦吗? ";
				link.l1.go = "helensleep_amelia_helen_notknow";
			}
		break;
		
		case "helensleep_amelia_helen_know":
			dialog.text = "不, 我的猎鹰。 原谅简, 这个可怜的人情绪激动。 不需要骂你; 你做得很对 —没有跟着那个红头发的去教堂。 好孩子! ";
			link.l1 = "被表扬很好。 尤其是清楚为什么被表扬。 ";
			link.l1.go = "helensleep_amelia";
			link.l2 = "你也看到她了吗? 她吸引了我的目光。 ";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia_helen_notknow":
			dialog.text = "你自己消失吧。 我们本应该已经见过面了, 但你一直在拖延。 过来, 我要表扬你 —没有跟着那个红头发的去教堂。 好孩子! ";
			link.l1 = "被表扬很好。 尤其是清楚为什么被表扬。 ";
			link.l1.go = "helensleep_amelia";
			link.l2 = "你也看到她了吗? 她吸引了我的目光。 ";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia":
			dialog.text = "我不会用细节来打扰你, 傻瓜, 但我要告诉你: 你注定要成为一个伟大的人。 你将带来很多邪恶, 但更多的是善良。 但幸福并不保证属于你。 幸福, 我的猎鹰, 只给予那些走自己的路而不偏离的人。 一个忠诚的女人会帮助你不偏离。 \n你会有两个这样的女人, 她们都将带来幸福, 但你需要选择那个金发的。 ";
			link.l1 = "为什么会这样? 我会自己决定! ";
			link.l1.go = "helensleep_amelia_1";
		break;
		
		case "helensleep_amelia_1":
			dialog.text = "当然, 你自己选择, 但金发的更好。 我们是这样决定的。 ";
			link.l1 = "我们是谁? ";
			link.l1.go = "helensleep_amelia_2";
		break;
		
		case "helensleep_amelia_2":
			dialog.text = "那个不幸的人甚至不知道她的真名。 说出它, 她就会是你的。 据说如此。 ";
			link.l1 = "我现在什么都不明白了。 ";
			link.l1.go = "helensleep_amelia_3";
		break;
		
		case "helensleep_amelia_3":
			dialog.text = "听到敲门声了吗? 打开, 不要弄错。 ";
			link.l1 = "确实, 有人在敲门... 进来! ";
			link.l1.go = "exit";
			
			PlaySound("interface\knock.wav");
			
			AddDialogExitQuestFunction("HelenSleep_WakeUp");
		break;
		
		case "helendrinking_notifier":
			dialog.text = "先生, 斯文森先生请你抽出一点时间见他。 ";
			link.l1 = "该死, 这不是好兆头。 我会试试, 但不保证。 ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_End");
		break;
		
		case "islatesoro_pirate1":
			dialog.text = "幸运的一天, 伙计们! 我告诉过你们她迟早会来这里, 不是吗? 好了, 甜心, 交出武器, 跟我们走。 ";
			link.l1 = "你们搞错了, 伙计们。 她和我在一起。 ";
			link.l1.go = "islatesoro_pirate1_1";
		break;
		
		case "islatesoro_pirate1_1":
			dialog.text = "别插手, 否则我会像狗一样开枪打死你。 有人出高价买这个女孩, 我们是饥饿的家伙, 缺乏原则。 ";
			link.l1 = "继续用那种语气跟我说话, 我会永久解决你的饥饿问题。 ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroSpawnSecond");
		break;
		
		case "islatesoro_pirate1_2":
			dialog.text = "你完全疯了吗, 幸运? 我们先找到她的! 最好有个好理由对我胡说八道! ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog1");
		break;
		
		case "islatesoro_pirate1_3":
			dialog.text = "你才是这里的老鼠! 我们刚把一个大胖西班牙人撕成碎片; 我们可以坐吃一年! ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog3");
		break;
		
		case "islatesoro_pirate2":
			dialog.text = "嗯, 看看我们找到了谁。 好了, 其他人都走开, 你, 夫人, 跟我们走。 ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog");
		break;
		
		case "islatesoro_pirate2_1":
			dialog.text = "我们人数比你多, 而且我们更强大, 丹麦人。 你还需要什么其他理由, 你这个舱底老鼠? 你已经六个月没有像样的战利品了, 一直在吃瓦齐桌子上的面包屑! ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog2");
		break;
		
		case "islatesoro_pirate2_2":
			dialog.text = "";
			link.l1 = "看来这里不会有和平解决的办法了。 ";
			link.l1.go = "islatesoro_pirate_a";
			if (!CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedB")) {
				link.l2 = "你说什么? 幸运? 我听说谣言说他和瓦齐合谋给你错误的提示。 这解释了你在海上的一连串坏运气。 ";
				link.l2.go = "islatesoro_pirate_b";
			}
			bOk = (!CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Choice")) || (pchar.questTemp.Mtraxx.Retribution.Choice == "bad");
			if (!CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedC") && CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold") && bOk) {
				link.l3 = "我厌倦了这场闹剧。 伊斯莱索罗, 听我说! 谁和我一起在卡塔赫纳? 谁和我一起烧毁了梅里达? 这些老鼠竟敢攻击查理.普林斯本人! 让我们给他们点颜色看看, 伙计们! ";
				link.l3.go = "islatesoro_pirate_c";
			}
		break;
		
		case "islatesoro_pirate_a":
			dialog.text = "你还在这里, 水母? 好吧, 伙计们, 我们走: 把船长绑起来, 我们稍后再处理那个女孩, 明白吗? ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog4");
		break;
		
		case "islatesoro_pirate_a_1":
			dialog.text = "当然, 至少让我们流点血吧。 呵呵。 ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroA");
		break;
		
		case "islatesoro_pirate_b":
			pchar.questTemp.HelenDrinking.IslaTesoroAmbush.TriedB = true;
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 60) {
				dialog.text = "什么? ! 魔鬼, 我就知道你和那个戴眼镜的恶棍勾结! 把他们都砍了, 伙计们, 我们稍后再去抓那个女孩! ";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("HelenDrinking_IslaTesoroB");
			} else {
				dialog.text = "你在胡说八道什么, 船长? 在体面人讨论事情的时候滚开。 ";
				link.l1 = "";
				link.l1.go = "islatesoro_pirate2_2";
			}
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "islatesoro_pirate_c":
			pchar.questTemp.HelenDrinking.IslaTesoroAmbush.TriedC = true;
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 50) {
				DialogExit();
				AddDialogExitQuestFunction("HelenDrinking_IslaTesoroC");
			} else {
				dialog.text = "你在胡说八道什么, 船长? 我见过查理.普林斯, 你比不上他。 在体面人讨论事情的时候滚开。 ";
				link.l1 = "";
				link.l1.go = "islatesoro_pirate2_2";
			}
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "francois":
			dialog.text = "查尔斯.德莫尔? 亨利.德蒙佩的儿子? ";
			link.l1 = "没错, 先生。 你是谁? ";
			link.l1.go = "francois_1";
		break;
		
		case "francois_1":
			dialog.text = "弗朗索瓦.德塔万上校。 你可以认为这是一个直接的挑战, 先生; 决斗的挑战已经发出。 我甚至不想弄脏我的手, 但我发誓, 我的剑会品尝你的血! ";
			link.l1 = "决斗? 在这种情况下, 你得更努力才行, 上校。 现在, 你只能被误认为是强盗, 在这些地方, 和他们这种人说话很简短! 解释一下你自己! ";
			link.l1.go = "francois_2";
		break;
		
		case "francois_2":
			dialog.text = "你勾引了我的妻子, 先生! 当我为国王和国家流血时, 你... 你却在和我的妻子寻欢作乐! ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog");
		break;
		
		case "francois_3":
			dialog.text = "安静, 夫人。 你大胆的穿着玷污了任何女人的荣誉, 尽管你和这个不配勾引贵族女人的人站在一起似乎很合适! ";
			link.l1 = "这仍然不足以成为决斗的理由, 上校。 我可以指出, 你在这里的行为也同样不值得尊重。 ";
			link.l1.go = "francois_4";
		break;
		
		case "francois_4":
			dialog.text = "这还不够吗? 我已经调查过了 —现在站在我这个位置的可能是十几个贵族丈夫, 先生。 但如果你想要细节, 那么我羞愧地承认, 你的激情之一是露露.德塔万, 最美丽和诚实的女人! ";
			link.l1 = "你说露露... 她怎么样了? ";
			link.l1.go = "francois_5";
		break;
		
		case "francois_5":
			dialog.text = "安静! 我的妻子, 无法忍受你带来的折磨, 最近去世了! 我花了将近一年的时间和一大笔财富来寻找你, 恶棍! 够了! 要么接受挑战, 要么我就像狗一样杀了你。 理查德! 做我的证人! ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog2");
		break;
		
		case "francois_6":
			dialog.text = "安静, 先生! 接受挑战, 否则就失去你可能还剩下的任何荣誉! ";
			if (pchar.HeroParam.HeroType == "HeroType_1") {
				link.l1 = "决斗就是决斗。 说实话, 我喜欢那些。 船长, 转告上校, 是时候让他订购一个合适的棺材了。 ";
			} else {
				link.l1 = "想打架? 你会得到的! 船长, 转告上校, 是时候让他订购一个合适的棺材了。 ";
			}
			link.l1.go = "francois_duel";
			link.l2 = "这不是欧洲, 上校。 加勒比海的荣誉更难赢得, 但也不是那么容易失去。 我拒绝你的决斗, 因为我只是不想。 ";
			link.l2.go = "francois_refuse";
		break;
		
		case "francois_7":
			dialog.text = "你父亲已经离坟墓只有一步之遥了, 你这个人渣! 我会确保他知道你的懦弱! ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog7");
		break;
		
		case "richard":
			dialog.text = "上校, 我确认你有权决斗, 但我不会允许纯粹的强盗行为! 德莫尔先生, 我是理查德.斯莫尔船长。 你愿意满足德塔万上校的要求吗? ";
			link.l1 = "等一下, 船长。 我很了解露露... 而且她... 倾向于频繁更换爱慕者, 她的健康状况比我还好... 她是怎么死的, 上校? 在你回家之前还是之后? ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog3");
		break;
		
		case "richard_1":
			dialog.text = "请, 弗朗索瓦, 让我来。 德莫尔先生, 你已经被挑战了。 布鲁维尔德的军官协会承认德塔万上校要求满足是合理的。 接受挑战或失去你的荣誉。 ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog5");
		break;
		
		case "richard_2":
			dialog.text = "查尔斯, 求你了, 我们这里都是贵族。 这不合适。 上校不远万里来见你! 这是一个丑闻! ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog8");
		break;
		
		case "richard_3":
			dialog.text = "是-是的, 当然, 小姐。 但我会... ";
			link.l1 = "";
			link.l1.go = "exit";
			CharacterTurnToLoc(npchar, "quest", "helen");
			
			AddDialogExitQuestFunction("HelenDrinking_AfterFrancoisDeath1");
		break;
		
		case "richard_4":
			dialog.text = "德莫尔船长, 今天是你的! 虽然不是最恰当的战斗, 但你今天捍卫了你的荣誉。 ";
			link.l1 = "你说什么, 船长? 我今天的日程表上也许还能挤出另一场决斗。 ";
			link.l1.go = "richard_5";
		break;
		
		case "richard_5":
			dialog.text = "抱歉, 船长。 只是有点紧张! ";
			link.l1 = "我认为这里不再需要你了。 ";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_DuelVictory");
		break;
		
		case "richard_duel":
			dialog.text = "一个公平的决定! 尽管表达方式不太体面... 先生们! 开始吧! ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SetupDuel");
		break;
		
		case "alonso":
			dialog.text = "船长, 我可能听不懂这些达官贵人说的那些漂亮话, 但你知道, 如果有人被称为懦夫, 通常不会放过他们。 揍那家伙, 船长, 否则我们的船员会担心的。 ";
			link.l1 = "你想要血? 生活太无聊, 没刺激? 你会得到血的, 你们这些禽兽! ";
			link.l1.go = "francois_duel";
			link.l2 = "呜呜, 我好害怕。 你们说完了吗, 先生们? 我还有地方要去。 ";
			link.l2.go = "alonso_refuse";
		break;
		
		case "alonso_1":
			dialog.text = "如果我们的船长在公开挑战面前退缩, 那可不好看。 给那个贵族好好一击; 我们知道你剑术很棒! ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog9");
		break;
		
		case "alonso_refuse":
			DialogExit();
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog6");
		break;
		
		case "francois_refuse":
			dialog.text = "懦夫! 浪荡子! 耗子! 你害怕了吗, 恶棍? 你们都看到了吗? ! 理查德, 我还是会杀了他! ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog4");
		break;
		
		case "francois_duel":
			DialogExit();
			
			AddDialogExitQuestFunction("HelenDrinking_SetupDuelDialog");
		break;
		
		case "francois_sit":
			dialog.text = "你... 你这个恶棍! 这没关系, 我习惯了受伤。 我会恢复的, 而且... ";
			link.l1 = "听起来像威胁, 上校。 我可不喜欢被威胁。 ";
			link.l1.go = "francois_sit_kill";
			link.l2 = "等你恢复了, 别忘了向军官圈子吹嘘你受伤的情况。 ";
			link.l2.go = "francois_sit_taunt";
		break;
		
		case "francois_sit_kill":
			DialogExit();
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
			Notification_Approve(false, "Helena");
			
			AddDialogExitQuestFunction("HelenDrinking_FinishFrancois");
		break;
		
		case "francois_sit_taunt":
			DialogExit();
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
			Notification_Approve(true, "Helena");
			AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 300);
			AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 300);
			
			AddDialogExitQuestFunction("HelenDrinking_SpareFrancois");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

bool HelenSleep_TalkedToAmelia() {
	if (GetCharacterIndex("Amelia") < 0) {
		return false;
	}
	
	sld = CharacterFromID("Amelia");
	if (sld.dialog.currentnode == "amelia") {
		return false;
	}
	
	return true;
}

// Диего де Монтойя
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
			dialog.text = "你有啥事吗? ";
			link.l1 = "没有, 什么都没有。";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "patrol":
			dialog.text = TimeGreeting() + ", " + GetFullName(npchar) + ", 圣何塞巡逻队队长。 我们收到消息, 说这个城镇外围有可疑活动。 你能行行好, 向我们解释一下你是谁, 来这里干什么吗?";
			link.l1 = "上尉" +GetFullName(pchar)+ ", 高级军官。 我是奉宗教裁判所的文森特神父的直接命令来到这里的。 这是证明我授权的文件。";
			link.l1.go = "patrol_1";
		break;
		
		case "patrol_1":
			dialog.text = "好吧……一切看起来都没问题。文件填写得很规范, 还有宗教裁判官的签名。刚才多有怀疑, 还请见谅。你来灯塔做什么? ";
			link.l1 = "我无权回答这样的问题。如果您真的想了解我为宗教裁判官工作的目的, 建议您直接去圣地亚哥向他本人询问以获得解释。您身为军官, 想必也明白军务和公务的机密。老实说, 我唯一能告诉您的, 就是我正在调查一艘西班牙船只失事的情况。";
			link.l1.go = "patrol_2";
		break;
		
		case "patrol_2":
			dialog.text = "请允许我再次致歉, 先生。我绝不敢再耽搁您……啊, 请等一下! 我刚才是不是瞥见了寒光一闪, 还是我眼花了? 您的匕首可真有趣! 能让我看看吗? ";
			link.l1 = "一定要记得还给我。这对我来说非常重要。";
			link.l1.go = "patrol_3";
		break;
		
		case "patrol_3":
			dialog.text = "天啊! 这把匕首我认识, 我在图书馆的书里见过! 这是Cortes本人用过的匕首! 你看, 这里还有烙印……先生, 求您别拒绝, 让我把这把匕首收下吧! 我专门收藏古代和定制武器, 这可真是不可多得的珍品。我一定会出高价购买。";
			link.l1 = "先生, 这把匕首不卖。是别人送给我的礼物, 俺可没打算随便卖给谁。请把它还给俺。";
			link.l1.go = "patrol_4";
		break;
		
		case "patrol_4":
			dialog.text = "五百金达布隆你都不满意? 那可是一大笔钱啊, 够买艘船了! ";
			link.l1 = "不行。我已经有船了, 这把匕首独一无二, 老子不会卖的。";
			link.l1.go = "patrol_5";
		break;
		
		case "patrol_5":
			dialog.text = "唉, 那真可惜……好吧, 把你的宝贝拿走吧。老子可不敢再打扰你了。祝你好运! ";
			link.l1 = "一切顺利, 军官。";
			link.l1.go = "patrol_6";
		break;
		
		case "patrol_6":
			DialogExit();
			AddQuestRecord("Guardoftruth", "42");
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "GuardOT_ClearMayakPatrol", 12.0);
			for(i=1; i<=3; i++)
			{
				sld = characterFromId("GOT_spamayaksold_"+i);
				sld.lifeday = 0;
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", 10.0);
			}
		break;
		
		case "shore":
			PlaySound("Voice\English\Sharlie\Diego De Montoya.wav");
			dialog.text = "够了! 老子要跟他好好谈谈……";
			link.l1 = "所以, 眼前这位就是Diego de Montoya本人……不过, 抱歉, senor。咱们以前见过面吧? 哦, 对了, 特立尼达, 当地的灯塔。可我记得你那时候用的可不是这个名字……";
			link.l1.go = "shore_1";
		break;
		
		case "shore_1":
			dialog.text = "您的记性不错, 先生。哼, 能在暗地里搅风搅雨的, 可不止您一个。我早就知道您一直惦记着要见我。怎么样, 如您所愿, 现在如愿以偿了。";
			link.l1 = "这可不是老子期望的那种邂逅, senor。";
			link.l1.go = "shore_2";
		break;
		
		case "shore_2":
			dialog.text = "嗯, 事情就是这样。 但是如果你把你的匕首给我, 我会给你一个活着离开这里的机会。 ";
			link.l1 = "你的收藏癖真的让你这么疯狂了吗, 骑士先生, 以至于你不得不为我准备这么精心策划的陷阱? 哦, 我不这么认为。 是'真理守护者'让你这么做的吗, 还是我离题太远了? ";
			link.l1.go = "shore_3";
		break;
		
		case "shore_3":
			dialog.text = "我不知道你在说什么。 这把匕首必须回到它所属的地方, 这就是你需要知道的一切。 你不愿意为了金子放弃它, 所以现在你要为了自己的生命放弃它。 ";
			link.l1 = "你真的认为, 先生, 我会相信你刚才告诉我的话吗? 你已经决定我不会离开这个海湾了, 不是吗? ";
			link.l1.go = "shore_4";
		break;
		
		case "shore_4":
			dialog.text = "那如果老子给你承诺呢? ";
			link.l1 = "‘吃青蛙的’这个词? 嗯……";
			link.l1.go = "shore_5";
		break;
		
		case "shore_5":
			dialog.text = "先生, 我再给您最后一次机会。 要么交出我感兴趣的那把匕首, 否则几分钟后我就会从您的尸体上搜刮它。 抵抗是徒劳的, 我们在人数上有压倒性优势。 ";
			if (CheckAttribute (pchar, "questTemp.Guardoftruth.SanAntonio")) link.l1 = "说真的, 先生, 您确实让我感到意外。 您真以为我是那种鲁莽的蠢货, 会不先抓住鱼叉就把头伸进鲨鱼嘴里吗? 伙计们, 干掉他们! ";
			else link.l1 = "真正的力量不在于人数, 而在于技巧, 先生! ";
			link.l1.go = "shore_6";
		break;
		
		case "shore_6":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto5", "none", "", "", "", 10.0);
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.SanAntonio"))
			{
				PlaySound("interface\abordage_wining.wav");
				PlaySound("interface\abordage_wining.wav");
				for(i=1; i<=10; i++)
				{
					sld = characterFromId("GuardOT_Oursoldier_"+i);
					LAi_SetWarriorType(sld);
					ChangeCharacterAddressGroup(sld, "Shore15", "reload", "reload1_back");
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				}
			}
			sld = CharacterFromID("spa_baseprisoner");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			for(i=1; i<=13; i++)
			{
				sld = characterFromId("GOT_spashore_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_DiegoShoreGuardDie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
